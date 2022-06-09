/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SimpleNetworkENTSTestCase.c

Abstract:

--*/

#include "SimpleNetworkENTSTestCase.h"

static EFI_TIME Epoch = { .Year = 1970, .Month = 1, .Day = 1 };

//
// SimpleNetwork.Start
//
static EFI_STATUS *StartStatus;
ENTS_ARG_FIELD    gSimpleNetworkStartArgField[] = {
  {
    POINTER,
    &StartStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Start Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *StartStatus  = SimpleNetwork->Start (SimpleNetwork);
  RecordMessage (
    &gSimpleNetworkEntsRuntimeInfo,
    &gSimpleNetworkEntsRuntimeInfoSize,
    L"Status - %r",
    *StartStatus
    );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Stop
//
static EFI_STATUS *StopStatus;

ENTS_ARG_FIELD    gSimpleNetworkStopArgField[] = {
  {
    POINTER,
    &StopStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Stop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *StopStatus   = SimpleNetwork->Stop (SimpleNetwork);
  RecordMessage (
    &gSimpleNetworkEntsRuntimeInfo,
    &gSimpleNetworkEntsRuntimeInfoSize,
    L"Status - %r",
    *StopStatus
    );

  return EFI_SUCCESS;
}

//
// SimpleNetwork.Initialize
//
static UINTN      InitializeExtraRxBufferSize;
static UINTN      InitializeExtraTxBufferSize;
static EFI_STATUS *InitializeStatus;

ENTS_ARG_FIELD    gSimpleNetworkInitializeArgField[] = {
  {
    OCTETN,
    &InitializeExtraRxBufferSize
  },
  {
    OCTETN,
    &InitializeExtraTxBufferSize
  },
  {
    POINTER,
    &InitializeStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkInitialize_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Initialize Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *InitializeStatus = SimpleNetwork->Initialize (
                                      SimpleNetwork,
                                      InitializeExtraRxBufferSize,
                                      InitializeExtraTxBufferSize
                                      );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Reset
//
static BOOLEAN    ResetExtendedVerification;
static EFI_STATUS *ResetStatus;

ENTS_ARG_FIELD    gSimpleNetworkResetArgField[] = {
  {
    BOOL,
    &ResetExtendedVerification
  },
  {
    POINTER,
    &ResetStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkReset_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Reset Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *ResetStatus = SimpleNetwork->Reset (
                                  SimpleNetwork,
                                  ResetExtendedVerification
                                  );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Shutdown
//
static EFI_STATUS *ShutdownStatus;

ENTS_ARG_FIELD    gSimpleNetworkShutdownArgField[] = {
  {
    POINTER,
    &ShutdownStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkShutdown_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Shutdown Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork   = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *ShutdownStatus = SimpleNetwork->Shutdown (SimpleNetwork);
  return EFI_SUCCESS;
}

//
// SimpleNetwork.ReceiveFilters
//
static UINT32           ReceiveFiltersEnable;
static UINT32           ReceiveFiltersDisable;
static BOOLEAN          ReceiveFiltersResetMCastFilter;
static UINTN            ReceiveFiltersMCastFilterCnt;
static EFI_MAC_ADDRESS  *ReceiveFiltersMCastFilter;
static EFI_STATUS       *ReceiveFiltersStatus;

ENTS_ARG_FIELD          gSimpleNetworkReceiveFiltersArgField[] = {
  {
    OCTET4,
    &ReceiveFiltersEnable
  },
  {
    OCTET4,
    &ReceiveFiltersDisable
  },
  {
    BOOL,
    &ReceiveFiltersResetMCastFilter
  },
  {
    OCTETN,
    &ReceiveFiltersMCastFilterCnt
  },
  {
    POINTER,
    &ReceiveFiltersMCastFilter
  },
  {
    POINTER,
    &ReceiveFiltersStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkReceiveFilters_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork ReceiveFilters Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *ReceiveFiltersStatus = SimpleNetwork->ReceiveFilters (
                                          SimpleNetwork,
                                          ReceiveFiltersEnable,
                                          ReceiveFiltersDisable,
                                          ReceiveFiltersResetMCastFilter,
                                          ReceiveFiltersMCastFilterCnt,
                                          ReceiveFiltersMCastFilter
                                          );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.StationAddress
//
static BOOLEAN          StationAddressReset;
static EFI_MAC_ADDRESS  *StationAddressNew;
static EFI_STATUS       *StationAddressStatus;

ENTS_ARG_FIELD          gSimpleNetworkStationAddressArgField[] = {
  {
    BOOL,
    &StationAddressReset
  },
  {
    POINTER,
    &StationAddressNew
  },
  {
    POINTER,
    &StationAddressStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkStationAddress_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork StationAddress Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *StationAddressStatus = SimpleNetwork->StationAddress (
                                          SimpleNetwork,
                                          StationAddressReset,
                                          StationAddressNew
                                          );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Statistics
//
static BOOLEAN                StatisticsReset;
static UINTN                  *StatisticsSize;
static EFI_NETWORK_STATISTICS *StatisticsTable;
static EFI_STATUS             *StatisticsStatus;

ENTS_ARG_FIELD                gSimpleNetworkStatisticsArgField[] = {
  {
    BOOL,
    &StatisticsReset
  },
  {
    POINTER,
    &StatisticsSize
  },
  {
    POINTER,
    &StatisticsTable
  },
  {
    POINTER,
    &StatisticsStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkStatistics_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Statistics Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *StatisticsStatus = SimpleNetwork->Statistics (
                                      SimpleNetwork,
                                      StatisticsReset,
                                      StatisticsSize,
                                      StatisticsTable
                                      );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.MCastIPToMAC
//
static BOOLEAN          MCastIPToMACIPv6;
static EFI_IP_ADDRESS   *MCastIPToMACIP;
static EFI_MAC_ADDRESS  *MCastIPToMACMAC;
static EFI_STATUS       *MCastIPToMACStatus;

ENTS_ARG_FIELD          gSimpleNetworkMCastIPToMACArgField[] = {
  {
    BOOL,
    &MCastIPToMACIPv6
  },
  {
    POINTER,
    &MCastIPToMACIP
  },
  {
    POINTER,
    &MCastIPToMACMAC
  },
  {
    POINTER,
    &MCastIPToMACStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkMCastIPToMAC_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork MCastIPToMAC Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *MCastIPToMACStatus = SimpleNetwork->MCastIpToMac (
                                        SimpleNetwork,
                                        MCastIPToMACIPv6,
                                        MCastIPToMACIP,
                                        MCastIPToMACMAC
                                        );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.NvData
//
static BOOLEAN    NvDataReadWrite;
static UINTN      NvDataOffset;
static UINTN      NvDataBufferSize;
static VOID       *NvDataBuffer;
static EFI_STATUS *NvDataStatus;

ENTS_ARG_FIELD    gSimpleNetworkNvDataArgField[] = {
  {
    BOOL,
    &NvDataReadWrite
  },
  {
    OCTETN,
    &NvDataOffset
  },
  {
    OCTETN,
    &NvDataBufferSize
  },
  {
    POINTER,
    &NvDataBuffer
  },
  {
    POINTER,
    &NvDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkNvData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork NvData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *NvDataStatus = SimpleNetwork->NvData (
                                  SimpleNetwork,
                                  NvDataReadWrite,
                                  NvDataOffset,
                                  NvDataBufferSize,
                                  NvDataBuffer
                                  );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.GetStatus
//
static UINT32     *GetStatusInterruptStatus;
static VOID       **GetStatusTxBuf;
static EFI_STATUS *GetStatusStatus;

ENTS_ARG_FIELD    gSimpleNetworkGetStatusArgField[] = {
  {
    POINTER,
    &GetStatusInterruptStatus
  },
  {
    POINTER,
    &GetStatusTxBuf
  },
  {
    POINTER,
    &GetStatusStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkGetStatus_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork GetStatus Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *GetStatusStatus = SimpleNetwork->GetStatus (
                                      SimpleNetwork,
                                      GetStatusInterruptStatus,
                                      GetStatusTxBuf
                                      );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Transmit
//
static UINTN            TransmitHeaderSize;
static UINTN            TransmitBufferSize;
static VOID             *TransmitBuffer;
static EFI_MAC_ADDRESS  *TransmitSrcAddr;
static EFI_MAC_ADDRESS  *TransmitDestAddr;
static UINT16           *TransmitProtocol;
static EFI_STATUS       *TransmitStatus;

ENTS_ARG_FIELD          gSimpleNetworkTransmitArgField[] = {
  {
    OCTETN,
    &TransmitHeaderSize
  },
  {
    OCTETN,
    &TransmitBufferSize
  },
  {
    POINTER,
    &TransmitBuffer
  },
  {
    POINTER,
    &TransmitSrcAddr
  },
  {
    POINTER,
    &TransmitDestAddr
  },
  {
    POINTER,
    &TransmitProtocol
  },
  {
    POINTER,
    &TransmitStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkTransmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *TransmitStatus = SimpleNetwork->Transmit (
                                    SimpleNetwork,
                                    TransmitHeaderSize,
                                    TransmitBufferSize,
                                    TransmitBuffer,
                                    TransmitSrcAddr,
                                    TransmitDestAddr,
                                    TransmitProtocol
                                    );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Receive
//
static UINTN            *ReceiveHeaderSize;
static UINTN            *ReceiveBufferSize;
static VOID             *ReceiveBuffer;
static EFI_MAC_ADDRESS  *ReceiveSrcAddr;
static EFI_MAC_ADDRESS  *ReceiveDestAddr;
static UINT16           *ReceiveProtocol;
static EFI_STATUS       *ReceiveStatus;

ENTS_ARG_FIELD          gSimpleNetworkReceiveArgField[] = {
  {
    POINTER,
    &ReceiveHeaderSize
  },
  {
    POINTER,
    &ReceiveBufferSize
  },
  {
    POINTER,
    &ReceiveBuffer
  },
  {
    POINTER,
    &ReceiveSrcAddr
  },
  {
    POINTER,
    &ReceiveDestAddr
  },
  {
    POINTER,
    &ReceiveProtocol
  },
  {
    POINTER,
    &ReceiveStatus
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  *ReceiveStatus = SimpleNetwork->Receive (
                                    SimpleNetwork,
                                    ReceiveHeaderSize,
                                    ReceiveBufferSize,
                                    ReceiveBuffer,
                                    ReceiveSrcAddr,
                                    ReceiveDestAddr,
                                    ReceiveProtocol
                                    );
  return EFI_SUCCESS;
}

//
// SimpleNetwork.Mode
//
static EFI_SIMPLE_NETWORK_MODE  *Mode;

ENTS_ARG_FIELD                  gSimpleNetworkModeArgField[] = {
  {
    POINTER,
    &Mode
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkMode_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork Mode Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  EntsCopyMem (Mode, SimpleNetwork->Mode, sizeof (EFI_SIMPLE_NETWORK_MODE));

  return EFI_SUCCESS;
}

//
// SimpleNetwork.TransmitPattern1
//
static UINTN            TransmitPattern1Number;
static UINTN            TransmitPattern1HeaderSize;
static UINTN            TransmitPattern1BufferSize;
static VOID             *TransmitPattern1Buffer;
static EFI_MAC_ADDRESS  *TransmitPattern1SrcAddr;
static EFI_MAC_ADDRESS  *TransmitPattern1DestAddr;
static UINT16           *TransmitPattern1Protocol;
static EFI_STATUS       *TransmitPattern1Status;
static UINTN            *TransmitPattern1ElapsedTime;

ENTS_ARG_FIELD          gSimpleNetworkTransmitPattern1ArgField[] = {
  {
    OCTETN,
    &TransmitPattern1Number
  },
  {
    OCTETN,
    &TransmitPattern1HeaderSize
  },
  {
    OCTETN,
    &TransmitPattern1BufferSize
  },
  {
    POINTER,
    &TransmitPattern1Buffer
  },
  {
    POINTER,
    &TransmitPattern1SrcAddr
  },
  {
    POINTER,
    &TransmitPattern1DestAddr
  },
  {
    POINTER,
    &TransmitPattern1Protocol
  },
  {
    POINTER,
    &TransmitPattern1Status
  },
  {
    POINTER,
    &TransmitPattern1Status
  },
  {
    POINTER,
    &TransmitPattern1ElapsedTime
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkTransmitPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;
  UINTN                       Index;
  EFI_STATUS                  Status;
  UINT32                      InterruptStatus;
  VOID                        *TxBuf;
  EFI_TIME                    BeginTime;
  EFI_TIME                    EndTime;

  InterruptStatus = 0;
  TxBuf           = NULL;

  SimpleNetwork   = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  Status          = EFI_SUCCESS;
  tBS->Stall (5000);

  if (tRT->GetTime (&BeginTime, NULL) != EFI_SUCCESS)
    BeginTime = Epoch;
  for (Index = 0; Index < 1;) {
    Status = SimpleNetwork->Transmit (
                              SimpleNetwork,
                              TransmitPattern1HeaderSize,
                              TransmitPattern1BufferSize,
                              TransmitPattern1Buffer,
                              TransmitPattern1SrcAddr,
                              TransmitPattern1DestAddr,
                              TransmitPattern1Protocol
                              );
    if (Status == EFI_NOT_READY) {
      continue;
    } else if (EFI_ERROR (Status)) {
      break;
    }

    ++Index;

    while (1) {
      Status = SimpleNetwork->GetStatus (
                                SimpleNetwork,
                                &InterruptStatus,
                                &TxBuf
                                );
      if (EFI_ERROR (Status)) {
        goto End;
      }

      if (TxBuf != NULL) {
        TxBuf = NULL;
        break;
      }
    }
  }

  if (tRT->GetTime (&BeginTime, NULL) != EFI_SUCCESS)
    BeginTime = Epoch;

  for (Index = 1; Index < TransmitPattern1Number;) {
    Status = SimpleNetwork->Transmit (
                              SimpleNetwork,
                              TransmitPattern1HeaderSize,
                              TransmitPattern1BufferSize,
                              TransmitPattern1Buffer,
                              TransmitPattern1SrcAddr,
                              TransmitPattern1DestAddr,
                              TransmitPattern1Protocol
                              );
    if (Status == EFI_NOT_READY) {
      continue;
    } else if (EFI_ERROR (Status)) {
      break;
    }

    ++Index;

    while (1) {
      Status = SimpleNetwork->GetStatus (
                                SimpleNetwork,
                                &InterruptStatus,
                                &TxBuf
                                );
      if (EFI_ERROR (Status)) {
        goto End;
      }

      if (TxBuf != NULL) {
        TxBuf = NULL;
        break;
      }
    }
  }

End:
  if (tRT->GetTime (&EndTime, NULL) != EFI_SUCCESS)
    EndTime = Epoch;

  *TransmitPattern1Status = Status;

  *TransmitPattern1ElapsedTime = EntsSecondsElapsedFromBaseYear (
                                  BeginTime.Year,
                                  EndTime.Year,
                                  EndTime.Month,
                                  EndTime.Day,
                                  EndTime.Hour,
                                  EndTime.Minute,
                                  EndTime.Second
                                  ) - EntsSecondsElapsedFromBaseYear (
        BeginTime.Year,
        BeginTime.Year,
        BeginTime.Month,
        BeginTime.Day,
        BeginTime.Hour,
        BeginTime.Minute,
        BeginTime.Second
        );

  return EFI_SUCCESS;
}

//
// SimpleNetwork.TransmitPattern2
//
static UINTN            TransmitPattern2Number;
static UINTN            TransmitPattern2HeaderSize;
static UINTN            TransmitPattern2BufferSizeMin;
static UINTN            TransmitPattern2BufferSizeMax;
static VOID             *TransmitPattern2Buffer;
static EFI_MAC_ADDRESS  *TransmitPattern2SrcAddr;
static EFI_MAC_ADDRESS  *TransmitPattern2DestAddr;
static UINT16           *TransmitPattern2Protocol;
static EFI_STATUS       *TransmitPattern2Status;
static UINTN            *TransmitPattern2ElapsedTime;

ENTS_ARG_FIELD          gSimpleNetworkTransmitPattern2ArgField[] = {
  {
    OCTETN,
    &TransmitPattern2Number
  },
  {
    OCTETN,
    &TransmitPattern2HeaderSize
  },
  {
    OCTETN,
    &TransmitPattern2BufferSizeMin
  },
  {
    OCTETN,
    &TransmitPattern2BufferSizeMax
  },
  {
    POINTER,
    &TransmitPattern2Buffer
  },
  {
    POINTER,
    &TransmitPattern2SrcAddr
  },
  {
    POINTER,
    &TransmitPattern2DestAddr
  },
  {
    POINTER,
    &TransmitPattern2Protocol
  },
  {
    POINTER,
    &TransmitPattern2Status
  },
  {
    POINTER,
    &TransmitPattern2Status
  },
  {
    POINTER,
    &TransmitPattern2ElapsedTime
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkTransmitPattern2_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern2 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;
  UINTN                       Index;
  EFI_STATUS                  Status;
  UINT32                      InterruptStatus;
  VOID                        *TxBuf;
  EFI_TIME                    BeginTime;
  EFI_TIME                    EndTime;

  InterruptStatus = 0;
  TxBuf           = NULL;

  SimpleNetwork   = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  Status          = EFI_SUCCESS;
  tBS->Stall (5000);

  if (tRT->GetTime (&BeginTime, NULL) != EFI_SUCCESS)
    BeginTime = Epoch;
  for (Index = 0; Index < 1;) {
    Status = SimpleNetwork->Transmit (
                              SimpleNetwork,
                              TransmitPattern2HeaderSize,
                              (Index % 2 == 0) ? TransmitPattern2BufferSizeMin : TransmitPattern2BufferSizeMax,
                              TransmitPattern2Buffer,
                              TransmitPattern2SrcAddr,
                              TransmitPattern2DestAddr,
                              TransmitPattern2Protocol
                              );
    if (Status == EFI_NOT_READY) {
      continue;
    } else if (EFI_ERROR (Status)) {
      break;
    }

    ++Index;

    while (1) {
      Status = SimpleNetwork->GetStatus (
                                SimpleNetwork,
                                &InterruptStatus,
                                &TxBuf
                                );
      if (EFI_ERROR (Status)) {
        goto End;
      }

      if (TxBuf != NULL) {
        TxBuf = NULL;
        break;
      }
    }
  }

  if (tRT->GetTime (&BeginTime, NULL) != EFI_SUCCESS)
    BeginTime = Epoch;

  for (Index = 1; Index < TransmitPattern2Number;) {
    Status = SimpleNetwork->Transmit (
                              SimpleNetwork,
                              TransmitPattern2HeaderSize,
                              (Index % 2 == 0) ? TransmitPattern2BufferSizeMin : TransmitPattern2BufferSizeMax,
                              TransmitPattern2Buffer,
                              TransmitPattern2SrcAddr,
                              TransmitPattern2DestAddr,
                              TransmitPattern2Protocol
                              );
    if (Status == EFI_NOT_READY) {
      continue;
    } else if (EFI_ERROR (Status)) {
      break;
    }

    ++Index;

    while (1) {
      Status = SimpleNetwork->GetStatus (
                                SimpleNetwork,
                                &InterruptStatus,
                                &TxBuf
                                );
      if (EFI_ERROR (Status)) {
        goto End;
      }

      if (TxBuf != NULL) {
        TxBuf = NULL;
        break;
      }
    }
  }

End:
  if (tRT->GetTime (&EndTime, NULL) != EFI_SUCCESS)
    EndTime = Epoch;

  *TransmitPattern1Status = Status;

  *TransmitPattern1ElapsedTime = EntsSecondsElapsedFromBaseYear (
                                  BeginTime.Year,
                                  EndTime.Year,
                                  EndTime.Month,
                                  EndTime.Day,
                                  EndTime.Hour,
                                  EndTime.Minute,
                                  EndTime.Second
                                  ) - EntsSecondsElapsedFromBaseYear (
        BeginTime.Year,
        BeginTime.Year,
        BeginTime.Month,
        BeginTime.Day,
        BeginTime.Hour,
        BeginTime.Minute,
        BeginTime.Second
        );

  return EFI_SUCCESS;
}

//
// SimpleNetwork.ReceivePattern1
//
static UINTN            ReceivePattern1Number;
static UINTN            *ReceivePattern1HeaderSize;
static UINTN            *ReceivePattern1BufferSize;
static VOID             *ReceivePattern1Buffer;
static EFI_MAC_ADDRESS  *ReceivePattern1SrcAddr;
static EFI_MAC_ADDRESS  *ReceivePattern1DestAddr;
static UINT16           *ReceivePattern1Protocol;
static EFI_STATUS       *ReceivePattern1Status;
static UINTN            *ReceivePattern1ElapsedTime;

ENTS_ARG_FIELD          gSimpleNetworkReceivePattern1ArgField[] = {
  {
    OCTETN,
    &ReceivePattern1Number
  },
  {
    POINTER,
    &ReceivePattern1HeaderSize
  },
  {
    POINTER,
    &ReceivePattern1BufferSize
  },
  {
    POINTER,
    &ReceivePattern1Buffer
  },
  {
    POINTER,
    &ReceivePattern1SrcAddr
  },
  {
    POINTER,
    &ReceivePattern1DestAddr
  },
  {
    POINTER,
    &ReceivePattern1Protocol
  },
  {
    POINTER,
    &ReceivePattern1Status
  },
  {
    POINTER,
    &ReceivePattern1ElapsedTime
  },
  0
};

EFI_STATUS
EFIAPI
SimpleNetworkReceivePattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SimpleNetwork TransmitPattern3 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_SIMPLE_NETWORK_PROTOCOL *SimpleNetwork;
  UINTN                       Index;
  EFI_STATUS                  Status;
  UINTN                       BufferSizeOrg;
  EFI_TIME                    BeginTime;
  EFI_TIME                    EndTime;

  SimpleNetwork = (EFI_SIMPLE_NETWORK_PROTOCOL *) ClientInterface;

  Status        = EFI_SUCCESS;
  BufferSizeOrg = *ReceivePattern1BufferSize;
  for (Index = 0; Index < 1;) {
    *ReceivePattern1BufferSize = BufferSizeOrg;
    Status = SimpleNetwork->Receive (
                              SimpleNetwork,
                              ReceivePattern1HeaderSize,
                              ReceivePattern1BufferSize,
                              ReceivePattern1Buffer,
                              ReceivePattern1SrcAddr,
                              ReceivePattern1DestAddr,
                              ReceivePattern1Protocol
                              );
    if (Status == EFI_SUCCESS) {
      ++Index;
    } else if (Status != EFI_NOT_READY) {
      break;
    }
  }

  if (tRT->GetTime (&BeginTime, NULL) != EFI_SUCCESS)
    BeginTime = Epoch;

  for (Index = 1; Index < ReceivePattern1Number;) {
    *ReceivePattern1BufferSize = BufferSizeOrg;
    Status = SimpleNetwork->Receive (
                              SimpleNetwork,
                              ReceivePattern1HeaderSize,
                              ReceivePattern1BufferSize,
                              ReceivePattern1Buffer,
                              ReceivePattern1SrcAddr,
                              ReceivePattern1DestAddr,
                              ReceivePattern1Protocol
                              );
    if (Status == EFI_SUCCESS) {
      ++Index;
    } else if (Status != EFI_NOT_READY) {
      break;
    }
  }

  if (tRT->GetTime (&EndTime, NULL) != EFI_SUCCESS)
    EndTime = Epoch;

  *ReceivePattern1Status = Status;

  *ReceivePattern1ElapsedTime = EntsSecondsElapsedFromBaseYear (
                                  BeginTime.Year,
                                  EndTime.Year,
                                  EndTime.Month,
                                  EndTime.Day,
                                  EndTime.Hour,
                                  EndTime.Minute,
                                  EndTime.Second
                                  ) - EntsSecondsElapsedFromBaseYear (
        BeginTime.Year,
        BeginTime.Year,
        BeginTime.Month,
        BeginTime.Day,
        BeginTime.Hour,
        BeginTime.Minute,
        BeginTime.Second
        );

  return EFI_SUCCESS;
}
