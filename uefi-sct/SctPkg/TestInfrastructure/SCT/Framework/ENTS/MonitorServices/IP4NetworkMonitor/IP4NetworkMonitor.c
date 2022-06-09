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

  IP4NetworkMonitor.c

Abstract:

  IP4 Network Monitor services implementations.

--*/

#include "SctLib.h"
#include <Library/EntsLib.h>
#include <Protocol/ServiceBinding.h>
#include "IP4NetworkMonitor.h"

#define EAS_QUERY_MSG           "EAS_QURY"
#define EAS_START_MSG           "EAS_STAT"
#define EAS_ACK_MSG             "EAS_ACK "
#define EAS_NON_ACK_MSG         "EAS_NACK"

#define WAIT_ACK_TIMER          3

#define EAS_IP4_PROT_INIT_TYPE  234
#define EAS_IP4_PROT_RIVL_TYPE  235

//
// global variables
//
//
EFI_GUID                        gEntsVendorGuid     = ENTS_VENDOR_GUID;
EFI_HANDLE                      mIp4InstanceHandle  = 0;

STATIC EFI_IP4_PROTOCOL         *Ip4;

STATIC EFI_EVENT                ResendTimeEvent;
STATIC EFI_IP4_COMPLETION_TOKEN TxToken;
STATIC EFI_IP4_COMPLETION_TOKEN TxLLToken;
STATIC EFI_IP4_COMPLETION_TOKEN RxToken;
STATIC EFI_IP4_TRANSMIT_DATA    TxData;
STATIC EFI_IP4_TRANSMIT_DATA    TxLLData;
STATIC EFI_IP4_RECEIVE_DATA     *RxData;
STATIC BOOLEAN                  HasReceivePacket    = FALSE;

STATIC UINT32                   LastReceiveSequence = 0xFFFFFFFF;
STATIC UINT32                   LastSendSequence    = 0;

STATIC UINT32                   SendSequenceSavedForResend = 0xFFFFFFFF;

STATIC LINK_LAYER_STATUS        LinkStatus          = WaitForPacket;

#define DESTINATION_ADDRESS \
  { \
    255, 255, 255, 255 \
  }
#define STATION_ADDRESS \
  { \
    0, 0, 0, 0 \
  }
#define SUBNET_MASK \
  { \
    0, 0, 0, 0 \
  }

EFI_IP4_CONFIG_DATA             mIp4ConfigDataTemplate = {
  EAS_IP4_PROT_RIVL_TYPE, // DefaultProtocol
  FALSE,                  // AcceptAnyProtocol
  FALSE,                  // AcceptIcmpErrors
  TRUE,                   // AcceptBroadcast
  FALSE,                  // AcceptPromiscuous
  TRUE,                   // UseDefaultAddress
  STATION_ADDRESS,        // StationAddress
  SUBNET_MASK,            // SubnetMask
  0,                      // TypeOfService
  8,                      // TimeToLive
  FALSE,                  // DoNotFragment
  FALSE,                  // RawData
  0,                      // ReceiveTimeout
  0,                      // TransmitTimeout
  //  3600u * 1000u * 1000u,       // ReceiveTimeout
  //  10 * 1000 * 1000,            // TransmitTimeout
  //
};

EFI_IP4_TRANSMIT_DATA           mIp4TxDataTemplate = {
  DESTINATION_ADDRESS,  // DestinationAddress
  NULL,                 // OverrideData
  0,                    // OptionsLength
  NULL,                 // OptionsBuffer
  0,                    // TotalDataLength
  1,                    // FragmentCount
  {
    0,
    NULL
  }                     // FragmentTable
};

EFI_IP4_RECEIVE_DATA            mIp4RxDataTemplate = {
  {
    0
  },                    // Timestamp
  NULL,                 // RecycleSignal
  20,                   // HeaderLength
  NULL,                 // Header
  0,                    // OptionsLength
  NULL,                 // Options
  0,                    // DataLength
  1,                    // FragmentCount
  {
    0,
    NULL
  }                     // FragmentTable
};

#define IP4_BUFFER_OUT_MAX  4096
CHAR8                           Ip4BufferOut[IP4_BUFFER_OUT_MAX];
UINTN                           Ip4PacketLen;

EFI_ENTS_MONITOR_PROTOCOL       *gIP4NetworkMonitorInterface = NULL;

//
// Local Functions Declaration
//
EFI_STATUS
StartInitIp4 (
  VOID
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
SendOutAck (
  IN UINT32                         SeqId
  );

VOID
Ip4NetworkPoll (
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
IP4NetworkMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  );

//
// External functions implementations
//
EFI_STATUS
EFIAPI
IP4NetworkMonitorEntryPoint (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point of IP4NetworkMonitor.
  
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

  LoadedImage->Unload = IP4NetworkMonitorUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_MONITOR_PROTOCOL),
                  (VOID **)&gIP4NetworkMonitorInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gIP4NetworkMonitorInterface->MonitorName           = ENTS_IP4_MONITOR_NAME;
  gIP4NetworkMonitorInterface->MonitorIo             = NULL;
  gIP4NetworkMonitorInterface->InitMonitor           = InitIP4Network;
  gIP4NetworkMonitorInterface->ResetMonitor          = ResetIP4Network;
  gIP4NetworkMonitorInterface->MonitorListener       = IP4NetworkListener;
  gIP4NetworkMonitorInterface->MonitorSender         = IP4NetworkSender;
  gIP4NetworkMonitorInterface->MonitorSaveContext    = IP4NetworkSaveContext;
  gIP4NetworkMonitorInterface->MonitorRestoreContext = IP4NetworkRestoreContext;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsMonitorProtocolGuid,
                  gIP4NetworkMonitorInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gIP4NetworkMonitorInterface != NULL) {
    tBS->FreePool (gIP4NetworkMonitorInterface);
  }

  return Status;
}

EFI_STATUS
EFIAPI
IP4NetworkMonitorUnload (
  IN EFI_HANDLE                ImageHandle
  )
/*++

Routine Description:

  Unload IP4NetworkMonitor.

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
                  gIP4NetworkMonitorInterface,
                  NULL
                  );

  if (gIP4NetworkMonitorInterface != NULL) {
    tBS->FreePool (gIP4NetworkMonitorInterface);
  }

  return Status;
}

//
// External functions implementations
//
EFI_STATUS
EFIAPI
InitIP4Network (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Initialize IP4 Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                    Status;
  EFI_SERVICE_BINDING_PROTOCOL  *Ip4Sb;
  UINTN                         DataSize;
  EFI_IPv4_ADDRESS              Data;

  //
  // Find IP4 service binding protocol
  //
  Status = tBS->LocateProtocol (
                  &gEfiIp4ServiceBindingProtocolGuid,
                  NULL,
                  (VOID **) &Ip4Sb
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Locate Ip4Sb Error"));
    return Status;
  }

  mIp4InstanceHandle = 0;

  //
  // Create IP4 instance
  //
  Status = Ip4Sb->CreateChild (
                    Ip4Sb,
                    &mIp4InstanceHandle
                    );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateChild Error"));
    return Status;
  }
  //
  // Open the IP4 Protocol from ChildHandle
  //
  Status = tBS->OpenProtocol (
                  mIp4InstanceHandle,
                  &gEfiIp4ProtocolGuid,
                  (VOID **) &Ip4,
                  mImageHandle,
                  mIp4InstanceHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"OpenProtocol Error"));
    Status = Ip4Sb->DestroyChild (
                      Ip4Sb,
                      mIp4InstanceHandle
                      );
    mIp4InstanceHandle = NULL;
    return Status;
  }
  //
  // Get Server IPv4Address variable
  //
  DataSize = sizeof (EFI_IPv4_ADDRESS);
  EntsSetMem (&Data, sizeof (EFI_IPv4_ADDRESS), 0);
  Status = tRT->GetVariable (
                  ENTS_SERVER_IPV4_ADDRESS_NAME,
                  &gEntsVendorGuid,
                  NULL,
                  &DataSize,
                  &Data
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Found it
    //
    EntsCopyMem (&mIp4TxDataTemplate.DestinationAddress, &Data, sizeof (EFI_IPv4_ADDRESS));
  }
  //
  // Start Ip4
  //
  Status = StartInitIp4 ();
  if (EFI_ERROR (Status)) {
    Status = Ip4Sb->DestroyChild (
                      Ip4Sb,
                      mIp4InstanceHandle
                      );
    mIp4InstanceHandle = NULL;
    return Status;
  }

  This->MonitorIo = Ip4;

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ResetIP4Network (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This
  )
/*++

Routine Description:

  Reset IP4 Network.

Arguments:

  This  - Pointer to the EFI_ENTS_MONITOR_PROTOCOL instance.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                    Status;
  EFI_SERVICE_BINDING_PROTOCOL  *Ip4Sb;

  This->MonitorIo = NULL;

  //
  // Close the IP4 Protocol from ChildHandle
  //
  Status = tBS->CloseProtocol (
                  mIp4InstanceHandle,
                  &gEfiIp4ProtocolGuid,
                  mImageHandle,
                  mIp4InstanceHandle
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CloseProtocol Error"));
    return Status;
  }
  //
  // Find IP4 service binding protocol
  //
  Status = tBS->LocateProtocol (
                  &gEfiIp4ServiceBindingProtocolGuid,
                  NULL,
                  (VOID **) &Ip4Sb
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Locate Ip4Sb Error"));
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
  // Destroy IP4 instance
  //
  Status = Ip4Sb->DestroyChild (
                    Ip4Sb,
                    mIp4InstanceHandle
                    );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"DestroyChild Error"));
    return Status;
  }

  mIp4InstanceHandle = NULL;

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
  tBS->SignalEvent (RxToken.Packet.RxData->RecycleSignal);
  return ;
}

VOID
RecycleTxBuffer (
  VOID
  )
/*++

Routine Description:

  Callback function to RecycleTxBuffer.

Arguments:

  None

Returns:

  

--*/
{
  if (TxData.FragmentTable[0].FragmentBuffer == NULL) {
    return ;
  }

  tBS->FreePool (TxData.FragmentTable[0].FragmentBuffer);
  TxData.FragmentTable[0].FragmentBuffer  = NULL;
  TxData.FragmentTable[0].FragmentLength  = 0;
  return ;
}

VOID
Ip4NetworkPoll (
  VOID
  )
/*++

Routine Description:

  Ip4 polling.

Arguments:

  None

Returns:

  

--*/
{
  Ip4->Poll (Ip4);
}

EFI_STATUS
EFIAPI
IP4NetworkSaveContext(
  EFI_ENTS_MONITOR_PROTOCOL     *This
  )
{
  EFI_STATUS    Status;

  Status = tRT->SetVariable (
                  ENTS_LINK_SEQUENCE_NAME,
                  &gEntsVendorGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof(UINT32),
                  &SendSequenceSavedForResend
                  );
  if (EFI_ERROR(Status)) {
    EFI_ENTS_DEBUG((EFI_ENTS_D_ERROR, L"Can not set SendSequence variable:%r\n", Status));
	EntsPrint(L"Can not set SendSequence variable:%r\n", Status);
	return Status;
  }
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
IP4NetworkRestoreContext(
  IN EFI_ENTS_MONITOR_PROTOCOL *This
  )
{
  EFI_STATUS Status;
  UINTN      DataSize;
  
  //
  // get the LinkSequence (From EFI Management Side) into variable for restart use.
  //
  DataSize = sizeof(UINT32);
  Status = tRT->GetVariable (
                  ENTS_LINK_SEQUENCE_NAME,
                  &gEntsVendorGuid,
                  NULL,
                  &DataSize,
                  &SendSequenceSavedForResend
                  );
  if (EFI_ERROR (Status)) {
    SendSequenceSavedForResend = 0;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
IP4NetworkListener (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN OUT UINTN                     *Size,
  OUT CHAR16                       **Buffer
  )
/*++

Routine Description:

  This func is to read data from IP4 network.

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
  //
  // UINTN                                 PacketLength;
  // UINTN                                 Index;
  //
  EntsPrint (L"IP4 listen ...\n");

  while (!HasReceivePacket) {
    Ip4NetworkPoll ();
  }

  RxData = RxToken.Packet.RxData;

  EntsCopyMem (
    &mIp4TxDataTemplate.DestinationAddress,
    &((RxData->Header)->SourceAddress),
    sizeof (EFI_IPv4_ADDRESS)
    );

  *Size   = Ip4PacketLen;
  *Buffer = EntsAllocatePool(*Size + 1);
  if (*Buffer == NULL) {
  	return EFI_OUT_OF_RESOURCES;
  }
  Status  = Char8ToChar16 (Ip4BufferOut, *Size, *Buffer);
  if (EFI_ERROR (Status)) {
    HasReceivePacket = FALSE;
    return Status;
  }

  HasReceivePacket = FALSE;
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
IP4NetworkSender (
  IN EFI_ENTS_MONITOR_PROTOCOL     *This,
  IN CHAR16                        *Buffer
  )
/*++

Routine Description:

  This func is to write data to IP4 network.

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
  EFI_STATUS        Status;
  UINTN             BufferSize;
  CHAR8             *BufferTmp;
  EAS_IP4_FRAG_FLAG FragFlag;
  UINTN             PacketLength;

  EntsPrint (L"IP4 Send ...\n");

  if (LinkStatus == SendoutPacket) {
    //
    // Try to send out packet in state SendOutPacket
    //
    EntsPrint (L" Try to send out packet in state SendOutPacket\n\r");
    return EFI_ACCESS_DENIED;
  }

  tBS->Stall (1000);

  BufferSize = EntsStrLen(Buffer);
  BufferTmp = EntsAllocatePool(BufferSize + 1);
  if (BufferTmp == NULL) {
  	return EFI_OUT_OF_RESOURCES;
  }
  Status    = Char16ToChar8 (Buffer, BufferTmp, BufferSize);
  if (EFI_ERROR (Status)) {
    EntsPrint (L" Error in Char16ToChar8\n\r");
    return Status;
  }

  FragFlag.LLFlag ^= FragFlag.LLFlag;

  //
  // Build Fragment Flag
  //
  LastSendSequence = SendSequenceSavedForResend;
  LastSendSequence += 1;
  FragFlag.Flag.SeqId   = HTONL (LastSendSequence);
  FragFlag.Flag.OpCode  = LINK_OPERATION_DATA;

  PacketLength          = BufferSize;

  //
  // Build data
  //
  EntsCopyMem (&TxData, &mIp4TxDataTemplate, sizeof (EFI_IP4_TRANSMIT_DATA));
  TxData.TotalDataLength                  = (UINT32) (PacketLength + sizeof (EAS_IP4_FRAG_FLAG));
  TxData.FragmentTable[0].FragmentLength  = (UINT32) (PacketLength + sizeof (EAS_IP4_FRAG_FLAG));
  TxData.FragmentTable[0].FragmentBuffer  = EntsAllocatePool (PacketLength + sizeof (EAS_IP4_FRAG_FLAG));
  if (TxData.FragmentTable[0].FragmentBuffer == NULL) {
    tBS->FreePool (BufferTmp);
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsAllocatePool Error"));
    return EFI_OUT_OF_RESOURCES;
  }

  EntsCopyMem (
    (UINT8 *) TxData.FragmentTable[0].FragmentBuffer + sizeof (EAS_IP4_FRAG_FLAG),
    (CHAR8 *) BufferTmp,
    PacketLength
    );
  tBS->FreePool (BufferTmp);

  EntsCopyMem (TxData.FragmentTable[0].FragmentBuffer, &FragFlag.LLFlag, sizeof (EAS_IP4_FRAG_FLAG));

  //
  // Ready to send buffer
  //
  Status = Ip4->Transmit (Ip4, &TxToken);

  if (EFI_ERROR (Status)) {
    EntsPrint (L" Error in Transmit()\n\r");
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Ip4->Transmit Error"));
    return Status;
  }

  LinkStatus  = SendoutPacket;

  Status      = SetResendTimer (LL_TIMEOUT);
  if (EFI_ERROR (Status)) {
    EntsPrint (L" Error in SetResendTimer\n\r");
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Set resend timer error"));
    return Status;
  }

  while (LinkStatus == SendoutPacket) {
    Ip4NetworkPoll ();
  }

  return Status;
}
//
// Internal functions implementations
//
EFI_STATUS
StartInitIp4 (
  VOID
  )
/*++

Routine Description:

  Initialize Ip4.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.
  
--*/
{
  EFI_STATUS  Status;
  Status = Ip4->Configure (
                  Ip4,
                  &mIp4ConfigDataTemplate
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Ip4->Configure Error"));
    return Status;
  }

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

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunctionSend,
                  NULL,
                  &TxToken.Event
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateEvent Error"));
    tBS->CloseEvent (RxToken.Event);
    return Status;
  }

  Status = tBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) NotifyFunctionSend,
                  NULL,
                  &TxLLToken.Event
                  );
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"CreateEvent Error"));
    tBS->CloseEvent (RxToken.Event);
    tBS->CloseEvent (TxToken.Event);
    return Status;
  }

  TxData.FragmentTable[0].FragmentBuffer    = NULL;
  TxData.FragmentTable[0].FragmentLength    = 0;
  TxToken.Packet.TxData                     = &TxData;

  TxLLData.FragmentTable[0].FragmentBuffer  = NULL;
  TxLLData.FragmentTable[0].FragmentLength  = 0;
  TxLLToken.Packet.TxData                   = &TxLLData;

  Status = Ip4->Receive (Ip4, &RxToken);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Ip4 Receive Error"));
    tBS->CloseEvent (RxToken.Event);
    tBS->CloseEvent (TxToken.Event);
    return Status;
  }

  Status = tBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  (EFI_EVENT_NOTIFY) ReSendTimer,
                  NULL,
                  &ResendTimeEvent
                  );

  return EFI_SUCCESS;
}

VOID
NotifyFunctionSend (
  EFI_EVENT Event,
  VOID      *Context
  )
/*++

Routine Description:

  Callback function on sending packet.

Arguments:

  Event   - Event to be singaled.
  Context - Context.

Returns:

  

--*/
{
  return ;
}

VOID
NotifyFunctionListen (
  EFI_EVENT Event,
  VOID      *Context
  )
/*++

Routine Description:

  Callback function on receiving packet.

Arguments:

  Event   - Event to be singaled.
  Context - Context.

Returns:


--*/
{
  EAS_IP4_FRAG_FLAG FragFlag;
  EFI_STATUS        Status;
  UINT32            SequenceID;
  UINTN             Index;

  //
  // Timeout occur, continue
  //
  if (RxToken.Status == EFI_TIMEOUT) {
    Status = Ip4->Receive (Ip4, &RxToken);
    return ;
  }

  RxData = RxToken.Packet.RxData;

  if ((RxData->DataLength <= sizeof (EAS_IP4_FRAG_FLAG)) ||
      (RxData->FragmentTable[0].FragmentLength <= sizeof (EAS_IP4_FRAG_FLAG))
      ) {
    //
    // Receive a too small frame
    //
    RecycleRxBuffer ();
    return ;
  }
  //
  // Build Fragment Flag
  //
  EntsCopyMem (&FragFlag.LLFlag, RxData->FragmentTable[0].FragmentBuffer, sizeof (EAS_IP4_FRAG_FLAG));
  SequenceID = NTOHL (FragFlag.Flag.SeqId);

  if (FragFlag.Flag.OpCode == LINK_OPERATION_DATA) {
    //
    // Record Received data packet
    //
    EntsCopyMem (
      Ip4BufferOut,
      (CHAR8 *) RxData->FragmentTable[0].FragmentBuffer + sizeof (EAS_IP4_FRAG_FLAG),
      RxData->FragmentTable[0].FragmentLength - sizeof (EAS_IP4_FRAG_FLAG)
      );
    for (Index = 1; Index < RxData->FragmentCount; Index++) {
      EntsCopyMem (
        Ip4BufferOut + RxData->FragmentTable[Index - 1].FragmentLength,
        (CHAR8 *) RxData->FragmentTable[Index].FragmentBuffer,
        RxData->FragmentTable[Index].FragmentLength
        );
    }

    Ip4PacketLen = RxData->DataLength - sizeof (EAS_IP4_FRAG_FLAG);
  }

  switch (FragFlag.Flag.OpCode) {
  case LINK_OPERATION_PROBE:
    //
    // Send out probe ack
    //
    // SendOutProbeAck(SequenceID);
    //
    RecycleRxBuffer ();
    break;

  case LINK_OPERATION_DATA:
    if (HasReceivePacket) {
      //
      // Receive a data packet when HasReceivePacket is still TRUE
      //
      break;
    }

    switch (LinkStatus) {
    case WaitForPacket:
      if (SequenceID == LastReceiveSequence) {
        //
        // Resend ACK out
        //
        SendOutAck (LastReceiveSequence);
        LinkStatus = WaitForPacket;
      } else {
        //
        // Receive a new data packet
        //
        LastReceiveSequence = SequenceID;
        SendOutAck (LastReceiveSequence);
        HasReceivePacket  = TRUE;
        LinkStatus        = WaitForPacket;
      }

      RecycleRxBuffer ();
      break;

    case SendoutPacket:
      //
      // The last ACK has been lost
      //
      CancelResendTimer ();
      RecycleTxBuffer ();
      //
      // Recycle the Tx Buffer
      //
      LastReceiveSequence = SequenceID;
      SendOutAck (LastReceiveSequence);
      HasReceivePacket  = TRUE;
      LinkStatus        = WaitForPacket;
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
      // Something wrong
      //
      RecycleRxBuffer ();
      LinkStatus = WaitForPacket;
      break;

    case SendoutPacket:
      if (SequenceID == LastSendSequence) {
        //
        // Receive the acknowledgement
        //
        CancelResendTimer ();
        RecycleRxBuffer ();
        RecycleTxBuffer ();
        //
        // Recycle the Tx Buffer
        //
        LinkStatus = WaitForPacket;
      } else {
        //
        // The sequence is wrong
        //
        RecycleRxBuffer ();
      }
      break;

    default:
      //
      // Something wrong!!!
      //
      break;
    }
    break;

  default:
    //
    // Other frames!
    //
    RecycleRxBuffer ();
    break;
  }

  Status = Ip4->Receive (Ip4, &RxToken);

  return ;
}

VOID
ReSendTimer (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
/*++

Routine Description:

  Callback function to resend packet.

Arguments:

  Event   - Event to be singaled.
  Context - Context.

Returns:

  

--*/
{
  Ip4->Transmit (Ip4, &TxToken);
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
  IN UINT32    SeqId
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
  EFI_STATUS        Status;
  EAS_IP4_FRAG_FLAG FragFlag;

  FragFlag.LLFlag ^= FragFlag.LLFlag;
  FragFlag.Flag.SeqId   = HTONL (SeqId);
  FragFlag.Flag.OpCode  = LINK_OPERATION_DATA_ACK;

  //
  // Build data
  //
  EntsCopyMem (&TxLLData, &mIp4TxDataTemplate, sizeof (EFI_IP4_TRANSMIT_DATA));
  TxLLData.TotalDataLength                  = (UINT32) (sizeof (EAS_IP4_FRAG_FLAG));
  TxLLData.FragmentTable[0].FragmentLength  = (UINT32) (sizeof (EAS_IP4_FRAG_FLAG));
  TxLLData.FragmentTable[0].FragmentBuffer  = EntsAllocatePool (sizeof (EAS_IP4_FRAG_FLAG));
  if (TxLLData.FragmentTable[0].FragmentBuffer == NULL) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"EntsAllocatePool Error"));
    return EFI_OUT_OF_RESOURCES;
  }

  EntsCopyMem (TxLLData.FragmentTable[0].FragmentBuffer, &FragFlag.LLFlag, sizeof (EAS_IP4_FRAG_FLAG));

  //
  // Ready to send buffer
  //
  Status = Ip4->Transmit (Ip4, &TxLLToken);
  if (EFI_ERROR (Status)) {
    EFI_ENTS_DEBUG ((EFI_ENTS_D_ERROR, L"Ip4->Transmit Error"));
    return Status;
  }

  return EFI_SUCCESS;
}
