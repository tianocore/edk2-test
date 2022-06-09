/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ManagedNetworkMonitor.c

Abstract:

  Managed Network Monitor services implementations.

--*/
#include "SctLib.h"
#include <Library/EntsLib.h>
#include "ManagedNetworkMonitor.h"
#include <Protocol/ServiceBinding.h>

#define EAS_QUERY_MSG           "EAS_QURY"
#define EAS_START_MSG           "EAS_STAT"
#define EAS_ACK_MSG             "EAS_ACK "
#define EAS_NON_ACK_MSG         "EAS_NACK"

#define WAIT_ACK_TIMER          3

#define EAS_MNP_PROT_RIVL_TYPE  0x1234

//
// global variables
//
//
EFI_SERVICE_BINDING_PROTOCOL                *MnpSb                  = NULL;
EFI_HANDLE                                  mMnpInstanceHandle      = 0;

STATIC EFI_MANAGED_NETWORK_PROTOCOL         *Mnp;
STATIC UINTN                                Context;
STATIC EFI_EVENT                            ResendTimeEvent;
STATIC EFI_MANAGED_NETWORK_COMPLETION_TOKEN TxToken;
STATIC EFI_MANAGED_NETWORK_COMPLETION_TOKEN TxLLToken;
STATIC EFI_MANAGED_NETWORK_COMPLETION_TOKEN RxToken;
STATIC EFI_MANAGED_NETWORK_TRANSMIT_DATA    TxData;
STATIC EFI_MANAGED_NETWORK_TRANSMIT_DATA    TxLLData;
STATIC EFI_MANAGED_NETWORK_TRANSMIT_DATA    TxProbeResp;
STATIC EFI_MANAGED_NETWORK_RECEIVE_DATA     *RxData;
STATIC BOOLEAN                              HasReceivePacket        = FALSE;

STATIC UINT32                               ExpectReceiveSequence   = 0xFFFFFFFF;
STATIC UINT32                               LastReceiveSequence     = 0xFFFFFFFF;
STATIC UINT32                               LastSendSequence        = 0;
STATIC UINT32                               AppSequence             = 0;

STATIC UINT32                               SendSequenceSavedForResend     = 0xFFFFFFFE;
STATIC UINT32                               AppSequenceSavedForResend      = 0xFFFFFFFF;

STATIC UINT64                               LastCleanupPktTimeStamp = 0x0; 

STATIC LINK_LAYER_STATUS                    LinkStatus              = WaitForPacket;

STATIC UINT32                               mCurrentReceiveOffset;
STATIC UINT32                               mCurrentOpCode;
STATIC UINT32                               mCurrentSeqId;
STATIC UINT32                               mCurrentPacketLength;

EFI_MAC_ADDRESS                             mDestinationAddress     = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
EFI_MAC_ADDRESS                             mSourceAddress          = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

EFI_MANAGED_NETWORK_CONFIG_DATA             mMnpConfigDataTemplate = {
  //
  //  3600u * 1000u * 1000u,       // ReceivedQueueTimeoutValue
  //  10 * 1000 * 1000,            // TransmitQueueTimeoutValue
  //
  0,                      // ReceivedQueueTimeoutValue
  0,                      // TransmitQueueTimeoutValue
  EAS_MNP_PROT_RIVL_TYPE, // ProtocolTypeFilter
  TRUE,                   // EnableUnicastReceive
  FALSE,                  // EnableMulticastReceive
  TRUE,                   // EnableBroadcastReceive
  FALSE,                  // EnablePromiscuousReceive
  FALSE,                  // EnableReceiveTimestamps
  FALSE                   // DisableBackgroundPolling
};

EFI_MANAGED_NETWORK_TRANSMIT_DATA           mMnpTxDataTemplate = {
  &mDestinationAddress,   // DestinationAddress
  &mSourceAddress,        // SourceAddress
  EAS_MNP_PROT_RIVL_TYPE, // ProtocolType
  0,                      // DataLength
  0,                      // HeaderLength
  1,                      // FragmentCount
  {
    0,
    NULL
  }                       // FragmentTable
};

EFI_MANAGED_NETWORK_RECEIVE_DATA            mMnpRxDataTemplate = {
  {
    0
  },                      // Timestamp
  NULL,                   // RecycleEvent
  0,                      // PacketLength
  0,                      // HeaderLength
  6,                      // AddressLength
  0,                      // DataLength
  TRUE,                   // BroadcastFlag
  FALSE,                  // MulticastFlag
  FALSE,                  // PromiscuousFlag
  EAS_MNP_PROT_RIVL_TYPE, // ProtocolType
  NULL,                   // DestinationAddress
  NULL,                   // SourceAddress
  NULL,                   // MediaHeader
  NULL                    // PacketData
};

CHAR8                                       MnpBufferIn[MNP_BUFFER_IN_MAX];
CHAR8                                       *MnpBufferOut;
UINTN                                       MnpBufferOutSize;

EFI_ENTS_MONITOR_PROTOCOL                   *gManagedNetworkMonitorInterface = NULL;

//
// Local Functions Declaration
//
STATIC
EFI_STATUS
StartInitMnp (
  IN EFI_MANAGED_NETWORK_PROTOCOL  *Mnp
  );

EFI_STATUS
MnpSendPacketOut (
  IN CHAR8     *Buffer,
  IN UINT32    Sequence,
  IN UINTN     Size
  );

VOID
NotifyFunctionSend (
  EFI_EVENT Event,
  VOID      *Context
  );

VOID
NotifyFunctionListen (
  EFI_EVENT Event,
  VOID      *Context
  );

EFI_STATUS
StartRivlMnp (
  IN EFI_MANAGED_NETWORK_PROTOCOL  *Mnp
  );

EFI_STATUS
SendOutAck (
  IN UINT32                         SeqId,
  IN UINT32                         Type
  );

VOID
MnpNetWorkPoll (
  VOID
  );

EFI_STATUS
CancelResendTimer (
  VOID
  );

EFI_STATUS
SetResendTimer (
  IN  UINTN uSec
  );

VOID
ReSendTimer (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

EFI_STATUS
EFIAPI
ManagedNetworkMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  );

//
// External functions implementations
//
EFI_STATUS
EFIAPI
ManagedNetworkMonitorEntryPoint (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point of ManagedNetworkMonitor.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);
  mImageHandle = ImageHandle;

  tBS->HandleProtocol (
        ImageHandle,
        &gEfiLoadedImageProtocolGuid,
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = ManagedNetworkMonitorUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_MONITOR_PROTOCOL),
                  (VOID **)&gManagedNetworkMonitorInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gManagedNetworkMonitorInterface->MonitorName            = ENTS_MNP_MONITOR_NAME;
  gManagedNetworkMonitorInterface->MonitorIo              = NULL;
  gManagedNetworkMonitorInterface->CleanUpEnvironmentFlag = FALSE;
  gManagedNetworkMonitorInterface->InitMonitor            = InitManagedNetwork;
  gManagedNetworkMonitorInterface->ResetMonitor           = ResetManagedNetwork;
  gManagedNetworkMonitorInterface->MonitorListener        = ManagedNetworkListener;
  gManagedNetworkMonitorInterface->MonitorSender          = ManagedNetworkSender;
  gManagedNetworkMonitorInterface->MonitorSaveContext     = ManagedNetworkSaveContext;
  gManagedNetworkMonitorInterface->MonitorRestoreContext  = ManagedNetworkRestoreContext;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  gManagedNetworkMonitorInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gManagedNetworkMonitorInterface != NULL) {
    tBS->FreePool (gManagedNetworkMonitorInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
ManagedNetworkMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  )
/*++

Routine Description:

  Unload ManagedNetworkMonitor.

Arguments:

  ImageHandle           - The image handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  Status = tBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  gManagedNetworkMonitorInterface,
                  NULL
                  );

  if (gManagedNetworkMonitorInterface != NULL) {
    tBS->FreePool (gManagedNetworkMonitorInterface);
  }

  return Status;
}
//
// External functions implementations
//

EFI_STATUS
EFIAPI
InitManagedNetwork (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Initialize MNP Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                    Status;
  EFI_MAC_ADDRESS               Data;
  EFI_HANDLE                    ControllerHandle;
  UINTN                         DataSize;

  //
  // Get the wanted Mnp service binding protocol
  //
  Status = EntsNetworkServiceBindingGetControllerHandle (
             &gEfiManagedNetworkServiceBindingProtocolGuid,
             &ControllerHandle
             );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = tBS->HandleProtocol (
                  ControllerHandle,
                  &gEfiManagedNetworkServiceBindingProtocolGuid,
                  (VOID **) &MnpSb
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Create MNP instance
  //
  mMnpInstanceHandle = 0;
  Status = MnpSb->CreateChild (
                    MnpSb,
                    &mMnpInstanceHandle
                    );
  if (EFI_ERROR (Status)) {
    EntsPrint(L"CreateChild Error\n");
    return Status;
  }

  //
  // Open the ManagedNetwork Protocol from ChildHandle
  //
  Status = tBS->OpenProtocol (
                  mMnpInstanceHandle,
                  &gEfiManagedNetworkProtocolGuid,
                  (VOID **) &Mnp,
                  mImageHandle,
                  mMnpInstanceHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"OpenProtocol ManagedNetwork Error\n"));
    goto InitError;
  }

  //
  // Start Init Mnp
  //
  Status = StartInitMnp (Mnp);
  if (EFI_ERROR (Status)) {
    goto InitError;
  }

  This->MonitorIo = Mnp;

  //
  // Get Server MacAddress variable. If can not get the 
  // mDestinationAddress will be all ff:ff:ff:ff:ff:ff
  //
  DataSize = sizeof(EFI_MAC_ADDRESS);
  Status = GetContextRecord(
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_SERVER_MAC_ADDRESS_NAME,
             &DataSize,
             &Data
             );
  if(!EFI_ERROR(Status)) {
    EntsCopyMem (&mDestinationAddress, &Data, sizeof (EFI_MAC_ADDRESS));
  }

  return EFI_SUCCESS;
InitError:
  MnpSb->DestroyChild (
           MnpSb,
           mMnpInstanceHandle
           );
  mMnpInstanceHandle = NULL;
  return Status;
}

EFI_STATUS
EFIAPI
ResetManagedNetwork (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Reset MNP Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                    Status;

  This->MonitorIo = NULL;

  //
  // Close the ManagedNetwork Protocol from ChildHandle
  //
  Status = tBS->CloseProtocol (
                  mMnpInstanceHandle,
                  &gEfiManagedNetworkProtocolGuid,
                  mImageHandle,
                  mMnpInstanceHandle
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CloseProtocol Error"));
    return Status;
  }

  //
  // Close all the events
  //
  tBS->CloseEvent (TxToken.Event);
  tBS->CloseEvent (RxToken.Event);
  tBS->CloseEvent (TxLLToken.Event);
  CancelResendTimer ();
  tBS->CloseEvent (ResendTimeEvent);

  //
  // Destroy MNP instance
  //
  Status = MnpSb->DestroyChild (
                    MnpSb,
                    mMnpInstanceHandle
                    );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"DestroyChild Error"));
    return Status;
  }

  MnpSb              = NULL;
  mMnpInstanceHandle = NULL;

  return EFI_SUCCESS;
}

VOID
RecycleRxBuffer (
  VOID
  )
/*++

Routine Description:

  Callback function to RecycleRxBuffer.

Arguments:

  None

Returns:

  

--*/
{
  tBS->SignalEvent (RxToken.Packet.RxData->RecycleEvent);
  return ;
}

VOID
RecycleTxBuffer (
  UINT8             *FragmentBuffer
  )
/*++

Routine Description:

  Callback function to RecycleTxBuffer.

Arguments:

  None

Returns:

  

--*/
{
  if (NULL != FragmentBuffer) {
    EntsFreePool(FragmentBuffer);
  }
  TxData.FragmentTable[0].FragmentBuffer  = NULL;
  TxData.FragmentTable[0].FragmentLength  = 0;
  return ;
}

VOID
MnpNetWorkPoll (
  VOID
  )
/*++

Routine Description:

  MNP polling.

Arguments:

  None

Returns:

  

--*/
{
  Mnp->Poll (Mnp);
}

EFI_STATUS
EFIAPI
ManagedNetworkSaveContext (
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  )
{
  EFI_STATUS                                   Status;

  //
  // Save the Server MacAddress
  //
  Status = SetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_SERVER_MAC_ADDRESS_NAME,
             sizeof(EFI_MAC_ADDRESS),
             &mDestinationAddress
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Can not Save the Destination MAC ADDRESS - %r", Status));
    return Status;
  }

  //
  // Save the AppSequence
  //
  Status = SetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_APP_SEQUENCE_NAME,
             sizeof(UINT32),
             &AppSequenceSavedForResend
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Can not set AppSequence - %r", Status));
    return Status;
  }

  //
  // Save the LinkSequence
  //
  Status = SetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_LINK_SEQUENCE_NAME,
             sizeof(UINT32),
             &SendSequenceSavedForResend
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Can not set SendSequence - %r\n", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ManagedNetworkRestoreContext (
  IN EFI_ENTS_MONITOR_PROTOCOL                 *This
  )
{
  EFI_STATUS                                   Status;
  UINTN                                        BufSize;

  //
  // Get the Server MacAddress
  //
  BufSize = sizeof(EFI_MAC_ADDRESS);
  Status = GetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_SERVER_MAC_ADDRESS_NAME,
             &BufSize,
             &mDestinationAddress
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"Can not get the Server MacAddress"));
    EntsZeroMem (&mDestinationAddress, sizeof(EFI_MAC_ADDRESS));
  }

  //
  // Record the AppSequence (From EFI Management Side) for test resume use.
  //
  BufSize = sizeof(UINT32);
  Status = GetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_APP_SEQUENCE_NAME,
             &BufSize,
             &AppSequenceSavedForResend
             );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"Can not get the AppSequence"));
    AppSequenceSavedForResend = 0;
  }

  //
  // get the LinkSequence (From EFI Management Side) into variable for restart use.
  //
  BufSize = sizeof(UINT32);
  Status = GetContextRecord (
             gntDevicePath,
             SCT_PASSIVE_MODE_RECORD_FILE,
             ENTS_LINK_SEQUENCE_NAME,
             &BufSize,
             &SendSequenceSavedForResend
             );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_TRACE, L"Can not get the SendSequenceSavedForResend"));
    SendSequenceSavedForResend = 0;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ManagedNetworkListener (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN OUT UINTN                     *Size,
  OUT CHAR16                       **Buffer
  )
/*++

Routine Description:

  This func is to read data from MNP network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Size    - To indicate buffer length
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  EntsOutput (L"MNP listen ...\n");

  while (!HasReceivePacket) {
    MnpNetWorkPoll ();
  }

  *Size = mCurrentPacketLength;

  //
  // Retrieve the packet
  //
  *Buffer = EntsAllocatePool(*Size * 2 + 2);
  if (*Buffer == NULL) {
  	return EFI_OUT_OF_RESOURCES;
  }
  Status            = Char8ToChar16 (MnpBufferIn, *Size, *Buffer);
  HasReceivePacket  = FALSE;
  return Status;
}

EFI_STATUS
EFIAPI
ManagedNetworkSender (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN CHAR16                        *Buffer
  )
/*++

Routine Description:

  This func is to write data to MNP network.

Arguments:

  This    - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.
  Buffer  - A buffer to return data to. It must be null before entering this func.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_ACCESS_DENIED    - Cannot send out packet in state SendOutPacket.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.
  
--*/
{
  EFI_STATUS                    Status;

  EntsOutput (L"MNP Send ...\n");
  if (LinkStatus == SendoutPacket) {
    //
    // Try to send out packet in state SendOutPacket
    //
    return EFI_ACCESS_DENIED;
  }

  tBS->Stall (1000);

  MnpBufferOutSize = EntsStrLen(Buffer);
  MnpBufferOut = EntsAllocatePool (MnpBufferOutSize + 1);
  if (MnpBufferOut == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status        = Char16ToChar8 (Buffer, MnpBufferOut, MnpBufferOutSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Retrieve LastSendSequence to act as the link sequence in case the
  // restart happens during the test.
  //
  LastSendSequence = SendSequenceSavedForResend;
  LastSendSequence += 1;
  LinkStatus = SendoutPacket;

  MnpSendPacketOut (MnpBufferOut, LastSendSequence, MnpBufferOutSize);

  Status = SetResendTimer (LL_TIMEOUT);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Set resend timer error"));
    return Status;
  }

  while (LinkStatus == SendoutPacket) {
    MnpNetWorkPoll ();
  }

  EntsFreePool (MnpBufferOut);
  MnpBufferOutSize = 0;

  return Status;
}

EFI_STATUS
MnpSendPacketOut (
  IN CHAR8     *Buffer,
  IN UINT32    Sequence,
  IN UINTN     Size
  )
/*++

Routine Description:

  This func is to send a data packet out to managed network.

Arguments:

  Buffer    - A buffer for writing.
  Sequence  - The Sequence Id of the packet to send.
  Size      - The size of the buffer to send.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
{
  BOOLEAN           IsOver;
  EAS_MNP_FRAG_FLAG FragFlag;
  EAS_APP_FLAG      AppFlag;
  UINTN             BufferSize;
  UINT32            PacketLength;
  UINT32            PacketStartPoint;
  EFI_STATUS        Status;
  UINT8             *FragmentBuffer;

  if (0 == Size) {
    return EFI_SUCCESS;
  }

  IsOver = FALSE;
  FragFlag.LLFlag ^= FragFlag.LLFlag;
  FragFlag.Flag.SeqId   = HTONL (Sequence);
  FragFlag.Flag.OpCode  = LINK_OPERATION_DATA;
  BufferSize            = Size;
  PacketStartPoint      = 0;
  FragmentBuffer        = NULL;

  while (!IsOver) {
    //
    // Build Fragment Flag
    //
    if (BufferSize <= MAX_PACKET_LENGTH) {
      IsOver = TRUE;
      CLR_FLAG_MF (FragFlag.LLFlag);
      PacketLength          = (UINT32) BufferSize;
      FragFlag.Flag.Offset  = HTONS (PacketStartPoint);
    } else {
      //
      // Need more fragement
      //
      IsOver = FALSE;
      SET_FLAG_MF (FragFlag.LLFlag);
      PacketLength          = MAX_PACKET_LENGTH;
      FragFlag.Flag.Offset  = HTONS (PacketStartPoint);
      BufferSize -= MAX_PACKET_LENGTH;
    }
    //
    // Build App Flag
    //
    AppFlag.LLFlag ^= AppFlag.LLFlag;
    AppSequence = AppSequenceSavedForResend;
    AppFlag.Flag.SeqId = HTONL(AppSequence);
    //
    // Build data
    //
    FragmentBuffer = EntsAllocatePool (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
    if(NULL == FragmentBuffer) {
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsAllocatePool Error"));
      return EFI_OUT_OF_RESOURCES;
    }

    EntsCopyMem (&TxData, &mMnpTxDataTemplate, sizeof (EFI_MANAGED_NETWORK_TRANSMIT_DATA));
    TxData.DataLength = (UINT32) (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
    TxData.FragmentTable[0].FragmentLength = (UINT32) (PacketLength + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG));
    TxData.FragmentTable[0].FragmentBuffer = FragmentBuffer;

    EntsCopyMem (
      (UINT8 *) TxData.FragmentTable[0].FragmentBuffer + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG),
      (CHAR8 *) Buffer + PacketStartPoint,
      PacketLength
      );
    EntsCopyMem (
      (UINT8 *) TxData.FragmentTable[0].FragmentBuffer + sizeof (EAS_MNP_FRAG_FLAG),
      &AppFlag.LLFlag,
      sizeof (EAS_APP_FLAG)
      );
    EntsCopyMem (
      TxData.FragmentTable[0].FragmentBuffer,
      &FragFlag.LLFlag,
      sizeof (EAS_MNP_FRAG_FLAG)
      );
    PacketStartPoint += PacketLength;

    TxToken.Packet.TxData = &TxData;

    //
    // Ready to send buffer
    //
    Context = 0;
    Status  = Mnp->Transmit (Mnp, &TxToken);
    if (EFI_ERROR (Status)) {
      RecycleTxBuffer(FragmentBuffer);
      EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Mnp->Transmit Error"));
      return Status;
    }
    //
    // Check the event ( Omitted...)
    //
    RecycleTxBuffer(FragmentBuffer);
  }

  return EFI_SUCCESS;
}

//
// Internal functions implementations
//
STATIC
EFI_STATUS
StartInitMnp (
  IN EFI_MANAGED_NETWORK_PROTOCOL  *MnpProtocol
  )
/*++

Routine Description:

  Initialize MNP.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.
  
--*/
{
  EFI_STATUS              Status;
  EFI_SIMPLE_NETWORK_MODE SnpModeData;

  Status = MnpProtocol->Configure (
                          MnpProtocol,
                          &mMnpConfigDataTemplate
                          );

  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"StartInitMnp: Mnp->Configure fail - %r", Status));
    return Status;
  }

  Status = MnpProtocol->GetModeData (
                          MnpProtocol,
                          NULL,
                          &SnpModeData
                          );
  if (EFI_ERROR (Status) && (Status != EFI_NOT_STARTED)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"StartInitMnp: Mnp->GetModeData fail - %r", Status));
    return Status;
  }

  EntsCopyMem (&mSourceAddress, &SnpModeData.CurrentAddress, sizeof (EFI_MAC_ADDRESS));
  EFI_ENTS_DEBUG ((EFI_ENTS_D_TRACE, L"mSourceAddress : %x:%x:%x:%x:%x:%x", 
  mSourceAddress.Addr[0], mSourceAddress.Addr[1], 
  mSourceAddress.Addr[2], mSourceAddress.Addr[3], 
  mSourceAddress.Addr[4], mSourceAddress.Addr[5]));
  mMnpConfigDataTemplate.ProtocolTypeFilter = EAS_MNP_PROT_RIVL_TYPE;

  RxToken.Packet.RxData = NULL;
  RxToken.Event         = NULL;

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunctionListen,
                  NULL,
                  &RxToken.Event
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateEvent Error"));
    return Status;
  }

  Status = MnpProtocol->Receive (MnpProtocol, &RxToken);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Mnp Receive Error"));
    goto Error1;
  }

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunctionSend,
                  &Context,
                  &TxToken.Event
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateEvent Error"));
    goto Error1;
  }

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunctionSend,
                  &Context,
                  &TxLLToken.Event
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateEvent Error"));
    goto Error2;
  }

  Status = tBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) ReSendTimer,
                  NULL,
                  &ResendTimeEvent
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Create resend timer error"));
    goto Error3;
  }

  return EFI_SUCCESS;

Error3:
  tBS->CloseEvent (TxLLToken.Event);
Error2:
  tBS->CloseEvent (TxToken.Event);
Error1:
  tBS->CloseEvent (RxToken.Event);
  return Status;
}

VOID
NotifyFunctionSend (
  EFI_EVENT Event,
  VOID      *EventContext
  )
/*++

Routine Description:

  Callback function on sending packet.

Arguments:

  Event        - Event to be singaled.
  EventContext - EventContext.

Returns:

  

--*/
{
  UINTN *NotifyTimes;

  if (EventContext == NULL) {
    return ;
  }

  NotifyTimes = (UINTN *) EventContext;
  (*NotifyTimes)++;

  return ;
}

STATIC
UINT64
GetPktTimeStamp(
  IN  UINT64 *Num
  )
{
  union {
    UINT64  Num;
    UINT8   Raw[8];
  } u;

  UINT8 Tmp;

  u.Num     = *Num;
  Tmp = u.Raw[0]; u.Raw[0] = u.Raw[7]; u.Raw[7] = Tmp;
  Tmp = u.Raw[1]; u.Raw[1] = u.Raw[6]; u.Raw[6] = Tmp;
  Tmp = u.Raw[2]; u.Raw[2] = u.Raw[5]; u.Raw[5] = Tmp;
  Tmp = u.Raw[3]; u.Raw[3] = u.Raw[4]; u.Raw[4]  = Tmp;
  return u.Num;
}


VOID
ManagedNetworkRefresh(
  VOID
  )
{
  LastReceiveSequence     = 0xFFFFFFFF;
  ExpectReceiveSequence   = 0xFFFFFFFF;
  LastSendSequence        = 0;
  AppSequence             = 0;
}

VOID
NotifyFunctionListen (
  EFI_EVENT Event,
  VOID      *EventContext
  )
/*++

Routine Description:

  Callback function on receiving packet.

Arguments:

  Event        - Event to be singaled.
  EventContext - EventContext.

Returns:


--*/
{
  EAS_MNP_FRAG_FLAG FragFlag;
  EAS_APP_FLAG      AppFlag;
  EFI_STATUS        Status;
  BOOLEAN           IsOver;
  UINT32            PacketStartPoint;
  UINT32            PacketLength;
  UINT32            OpCode;
  UINT32            SequenceId;
  UINT64            TimeStamp;

  if (RxToken.Status == EFI_ABORTED) {
    return;
  }

  if (EFI_ERROR (RxToken.Status)) {
    //
    // Restart the receiving if any other error Status occurs.
    //
    goto RESTART_RECEIVE;
  }

  if (HasReceivePacket) {
    //
    // Don't receive any new packet when HasReceivePacket is still TRUE
    //
    goto RESTART_RECEIVE;
  }

  IsOver = FALSE;
  FragFlag.LLFlag ^= FragFlag.LLFlag;

  RxData = RxToken.Packet.RxData;
  if (RxData->DataLength < sizeof (EAS_MNP_FRAG_FLAG)) {
    goto RESTART_RECEIVE;
  }

  //
  // Build Fragment Flag
  //
  EntsCopyMem (&FragFlag.LLFlag, RxData->PacketData, sizeof (EAS_MNP_FRAG_FLAG));
  SequenceId        = NTOHL (FragFlag.Flag.SeqId);
  PacketStartPoint  = NTOHS (FragFlag.Flag.Offset);
  PacketLength      = RxData->DataLength - sizeof (EAS_MNP_FRAG_FLAG);
  IsOver            = HAS_FLAG_MF (FragFlag.LLFlag) ? FALSE : TRUE;
  OpCode            = FragFlag.Flag.OpCode;

  //
  // Record the LinkSequence (From EFI Management Side) into variable for resend use.
  //
  SendSequenceSavedForResend = LastSendSequence;

  //
  // Build App Flag
  //
  EntsCopyMem (&AppFlag.LLFlag, (UINT8 *) RxData->PacketData + sizeof (EAS_MNP_FRAG_FLAG), sizeof (EAS_APP_FLAG));
  AppSequence = NTOHL (AppFlag.Flag.SeqId);
  PacketLength -= sizeof (EAS_APP_FLAG);

  if (PacketStartPoint == 0) {
    //
    // Record the Destination address (EFI Management Side) into variable for late use.
    //
    if ((mDestinationAddress.Addr[0] != ((CHAR8 *)(RxData->SourceAddress))[0]) ||
        (mDestinationAddress.Addr[1] != ((CHAR8 *)(RxData->SourceAddress))[1]) ||
        (mDestinationAddress.Addr[2] != ((CHAR8 *)(RxData->SourceAddress))[2]) ||
        (mDestinationAddress.Addr[3] != ((CHAR8 *)(RxData->SourceAddress))[3]) ||
        (mDestinationAddress.Addr[4] != ((CHAR8 *)(RxData->SourceAddress))[4]) ||
        (mDestinationAddress.Addr[5] != ((CHAR8 *)(RxData->SourceAddress))[5])
        ) {
      EntsCopyMem(&mDestinationAddress, RxData->SourceAddress, sizeof(EFI_MAC_ADDRESS));
      Status = SetContextRecord(
                 gntDevicePath,
                 SCT_PASSIVE_MODE_RECORD_FILE,
                 ENTS_SERVER_MAC_ADDRESS_NAME,
                 sizeof(EFI_MAC_ADDRESS),
                 &mDestinationAddress
                 );
      if (EFI_ERROR(Status)) {
        EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Can not Save the MAC ADDRESS\n"));
        return ;
      }
    }
    mCurrentReceiveOffset = PacketLength;
    mCurrentOpCode        = OpCode;
    mCurrentSeqId         = SequenceId;
  } else if ((PacketStartPoint != mCurrentReceiveOffset) || 
                                     (OpCode != mCurrentOpCode) || 
                                     (SequenceId != mCurrentSeqId)) {
    goto RESTART_RECEIVE;
  } else {
    mCurrentReceiveOffset += PacketLength;
  }
  
  //
  // Build data
  //
  if (mCurrentReceiveOffset > MNP_BUFFER_IN_MAX) {
    //
    // Too long packet
    //
    mCurrentReceiveOffset = 0;
    goto RESTART_RECEIVE;
  }

  if (!IsOver) {
    goto RESTART_RECEIVE;
  }


  //
  // Receive a complete packet
  //
  switch (OpCode) {
  case LINK_OPERATION_PROBE:
    //
    // Send out probe ack
    //
    SendOutAck (SequenceId, LINK_OPERATION_PROBE_ACK);
    break;

  case LINK_OPERATION_DATA:

    EntsCopyMem (
      MnpBufferIn + PacketStartPoint,
      (CHAR8 *) RxData->PacketData + sizeof (EAS_MNP_FRAG_FLAG) + sizeof (EAS_APP_FLAG),
      PacketLength
      );
    MnpBufferIn[mCurrentReceiveOffset] = '\0';

    switch (LinkStatus) {
    case SendoutPacket:
      //
      // treat the new rpc command as the ACK for ACK_P 
      //
      if (SequenceId == ExpectReceiveSequence)
        CancelResendTimer ();
    case WaitForPacket:
      if (ExpectReceiveSequence == 0xFFFFFFFF)
        ExpectReceiveSequence = SequenceId;

      if (SequenceId == ExpectReceiveSequence) {
        //
        // Receive a new data packet
        //
        AppSequenceSavedForResend  = AppSequence;
        LastReceiveSequence        = SequenceId;
        SendOutAck (LastReceiveSequence, LINK_OPERATION_DATA_ACK);
        ExpectReceiveSequence      = LastReceiveSequence + 1;
        mCurrentPacketLength       = mCurrentReceiveOffset;
        HasReceivePacket           = TRUE;
        LinkStatus                 = WaitForPacket;
      }
      else
      {
        if (SequenceId == LastReceiveSequence) {
          //
          // Resend ACK out
          //
          SendOutAck (LastReceiveSequence, LINK_OPERATION_DATA_ACK);
          LinkStatus = WaitForPacket;
        }
      }
      break;
    default:
      //
      // Something wrong!!!
      //
      break;
    }
    break;

  case LINK_OPERATION_DATA_ACK:
    switch (LinkStatus) {
    case WaitForPacket:
      //
      // Something wrong lost DATA_ACK package
      //
      LinkStatus = WaitForPacket;
      break;

    case SendoutPacket:
      if (SequenceId == LastSendSequence) {
        //
        // Receive the acknowledgement
        //
        CancelResendTimer ();
        LinkStatus = WaitForPacket;
      } else {
        //
        // The sequence is wrong
        //
      }
      break;

    default:
      //
      // Something wrong!!!
      //
      break;
    }
    break;

  case LINK_OPERATION_CLEANUP:
    EntsCopyMem (
      MnpBufferIn + PacketStartPoint,
      (CHAR8 *) RxData->PacketData + sizeof (EAS_MNP_FRAG_FLAG),
      PacketLength
      );
    MnpBufferIn[mCurrentReceiveOffset] = '\0';
      
    //
    // Check the valid of the Reset message.
    //
    TimeStamp = GetPktTimeStamp((UINT64 *)(MnpBufferIn + PacketStartPoint));

    if (LastCleanupPktTimeStamp < TimeStamp)
    {
      //
      // Set CleanUpEnvironmentFlag to trigger Eas to cleanup environment.
      //
      gManagedNetworkMonitorInterface->CleanUpEnvironmentFlag = TRUE;

      //
      // Cleanup environment for MNP monitor.
      //
      ManagedNetworkRefresh();
      HasReceivePacket        = TRUE;
      //
      // Save the new cleanup package
      //
      LastCleanupPktTimeStamp = TimeStamp;
    }
    LinkStatus                = WaitForPacket;
    SendOutAck(SequenceId, LINK_OPERATION_CLEANUP_ACK);

    break;
  case LINK_OPERATION_CLEANUP_ACK:
    //
    // Something wrong, ignore the packet.
    //
    break;
    
  default:
    //
    // Other frames!
    //
    break;
  }

  mCurrentReceiveOffset = 0;

RESTART_RECEIVE:
  RecycleRxBuffer ();
  Status = Mnp->Receive (Mnp, &RxToken);
  return ;
}

VOID
ReSendTimer (
  IN EFI_EVENT    Event,
  IN VOID         *EventContext
  )
/*++

Routine Description:

  Callback function to resend packet.

Arguments:

  Event        - Event to be singaled.
  EventContext - EventContext.

Returns:

  

--*/
{
  MnpSendPacketOut (MnpBufferOut, LastSendSequence, MnpBufferOutSize);
}

EFI_STATUS
SetResendTimer (
  IN  UINTN uSec
  )
/*++

Routine Description:

  Set resending timer.

Arguments:

  uSec  - Timer value.

Returns:


--*/
{
  EFI_STATUS  Status;

  Status = tBS->SetTimer (
                  ResendTimeEvent,
                  TimerPeriodic,
                  uSec * 10
                  );
  return Status;
}

EFI_STATUS
CancelResendTimer (
  VOID
  )
/*++

Routine Description:

  Cancel resending timer.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;
  Status = tBS->SetTimer (
                  ResendTimeEvent,
                  TimerCancel,
                  0
                  );
  return Status;
}

EFI_STATUS
SendOutAck (
  IN UINT32                         SeqId,
  IN UINT32                         Type
  )
/*++

Routine Description:

  Send data or ack packet.

Arguments:

  SeqId - Sequence ID.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.
  EFI_OUT_OF_RESOURCES - Memory allocation failure.

--*/
{
  EFI_STATUS                            Status;
  EAS_MNP_FRAG_FLAG                     FragFlag;
  UINT8                                 *Buffer;

  Buffer = EntsAllocatePool (sizeof (EAS_MNP_FRAG_FLAG));
  if(Buffer == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsAllocatePool Error"));
    return EFI_OUT_OF_RESOURCES;
  }

  FragFlag.LLFlag       ^= FragFlag.LLFlag;
  FragFlag.Flag.SeqId   = HTONL (SeqId);
  FragFlag.Flag.OpCode  = Type;

  //
  // Build data
  //
  EntsCopyMem (&TxLLData, &mMnpTxDataTemplate, sizeof (EFI_MANAGED_NETWORK_TRANSMIT_DATA));
  TxLLData.DataLength                       = (UINT32) (sizeof (EAS_MNP_FRAG_FLAG));
  TxLLData.FragmentTable[0].FragmentLength  = (UINT32) (sizeof (EAS_MNP_FRAG_FLAG));
  TxLLData.FragmentTable[0].FragmentBuffer  = Buffer;

  EntsCopyMem (TxLLData.FragmentTable[0].FragmentBuffer, &FragFlag.LLFlag, sizeof (EAS_MNP_FRAG_FLAG));

  //
  // Ready to send buffer
  //
  TxLLToken.Packet.TxData = &TxLLData;
  Context                 = 0;

  Status                  = Mnp->Transmit (Mnp, &TxLLToken);
  if (EFI_ERROR (Status)) {
    RecycleTxBuffer(Buffer);
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Mnp->Transmit Error"));
    return Status;
  }

  RecycleTxBuffer(Buffer);

  return EFI_SUCCESS;
}
