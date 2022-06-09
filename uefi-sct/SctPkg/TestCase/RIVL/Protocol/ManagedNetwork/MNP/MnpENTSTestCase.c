/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  MnpENTSTestCase.c

Abstract:

--*/

#include "MnpENTSTestCase.h"

typedef struct _MNP_TEST_RXINFO {
  UINTN                                 TotalNumber;
  UINTN                                 ReceivedNumber;
  EFI_MANAGED_NETWORK_PROTOCOL          *Mnp;
  EFI_MANAGED_NETWORK_COMPLETION_TOKEN  Token[100];
} MNP_TEST_RXINFO;
MNP_TEST_RXINFO                         RxInfo;

VOID
RegenerateToken (
  EFI_EVENT Event,
  VOID      *Context
  );

VOID
EFIAPI
MnpCallBackFunction0 (
  EFI_EVENT Event,
  VOID      *Context
  );

VOID
EFIAPI
MnpCallBackFunction1 (
  EFI_EVENT Event,
  VOID      *Context
  );

static EFI_EVENT_NOTIFY                 BSCallBackFunc[] = {
  MnpCallBackFunction0,
  MnpCallBackFunction1
};

//
// Mnp.Config
//
static EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpConfigData;
static EFI_STATUS                       *MnpConfigStatus;

ENTS_ARG_FIELD                          gMnpConfigArgField[] = {
  {
    POINTER,
    &MnpConfigData
  },
  {
    POINTER,
    &MnpConfigStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpConfig_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Config Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpConfigStatus = Mnp->Configure (
                            Mnp,
                            (EFI_MANAGED_NETWORK_CONFIG_DATA *) MnpConfigData
                            );
  return EFI_SUCCESS;
}

//
// Mnp.GetModeData
//
static EFI_MANAGED_NETWORK_CONFIG_DATA  *MnpGetModeDataConfigData;
static EFI_SIMPLE_NETWORK_MODE          *SnpGetModeDataModeData;
static EFI_STATUS                       *MnpGetModeDataStatus;

ENTS_ARG_FIELD                          gMnpGetModeDataArgField[] = {
  {
    POINTER,
    &MnpGetModeDataConfigData
  },
  {
    POINTER,
    &SnpGetModeDataModeData
  },
  {
    POINTER,
    &MnpGetModeDataStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpGetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpGetModeDataStatus = Mnp->GetModeData (
                                Mnp,
                                MnpGetModeDataConfigData,
                                SnpGetModeDataModeData
                                );
  return EFI_SUCCESS;
}

//
// Mnp.MCastIpToMac
//
static BOOLEAN          MnpMCastIpToMacIpv6Flag;
static EFI_IP_ADDRESS   *MnpMCastIpToMacIpAddr;
static EFI_MAC_ADDRESS  *MnpMCastIpToMacMacAddress;
static EFI_STATUS       *MnpMCastIpToMacStatus;

ENTS_ARG_FIELD          gMnpMCastIpToMacArgField[] = {
  {
    BOOL,
    &MnpMCastIpToMacIpv6Flag
  },
  {
    POINTER,
    &MnpMCastIpToMacIpAddr
  },
  {
    POINTER,
    &MnpMCastIpToMacMacAddress
  },
  {
    POINTER,
    &MnpMCastIpToMacStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpMCastIpToMac_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp MCastIpToMac Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpMCastIpToMacStatus = Mnp->McastIpToMac (
                                  Mnp,
                                  MnpMCastIpToMacIpv6Flag,
                                  MnpMCastIpToMacIpAddr,
                                  MnpMCastIpToMacMacAddress
                                  );
  return EFI_SUCCESS;
}

//
// Mnp.Group
//
static BOOLEAN          MnpGroupJoinFlag;
static EFI_MAC_ADDRESS  *MnpGroupMacAddress;
static EFI_STATUS       *MnpGroupStatus;

ENTS_ARG_FIELD          gMnpGroupArgField[] = {
  {
    BOOL,
    &MnpGroupJoinFlag
  },
  {
    POINTER,
    &MnpGroupMacAddress
  },
  {
    POINTER,
    &MnpGroupStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpGroup_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Group Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpGroupStatus = Mnp->Groups (
                          Mnp,
                          MnpGroupJoinFlag,
                          MnpGroupMacAddress
                          );
  return EFI_SUCCESS;
}

//
// Mnp.Transmit
//
static EFI_MANAGED_NETWORK_COMPLETION_TOKEN *MnpTransmitToken;
static EFI_STATUS                           *MnpTransmitStatus;
ENTS_ARG_FIELD                              gMnpTransmitArgField[] = {
  {
    POINTER,
    &MnpTransmitToken
  },
  {
    POINTER,
    &MnpTransmitStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpTransmit_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Transmit Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;
  *MnpTransmitStatus = Mnp->Transmit (
                              Mnp,
                              MnpTransmitToken
                              );
  return EFI_SUCCESS;
}

static BOOLEAN                              BeNotified;

//
// Mnp.TransmitMultiPacket
// Send the same packets multi times.
//
static EFI_MANAGED_NETWORK_COMPLETION_TOKEN *MnpTransmitMultiPacketToken;
static UINTN                                *MnpTransmitMultiPacketCnt;
static VOID                                 *BSCreateEventNotifyContext;
static EFI_STATUS                           *MnpTransmitMultiPacketStatus;
ENTS_ARG_FIELD                              gMnpTransmitMultiPacketArgField[] = {
  {
    POINTER,
    &MnpTransmitMultiPacketToken
  },
  {
    POINTER,
    &MnpTransmitMultiPacketCnt
  },
  {
    POINTER,
    &BSCreateEventNotifyContext
  },
  {
    POINTER,
    &MnpTransmitMultiPacketStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpTransmitMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp TransmitMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_DEVICE_ERROR - Some error happens.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;
  UINTN                         CntOfXMit;
  EFI_STATUS                    Status;
  int                           CallBackIndex;
  UINTN                         i;

  *MnpTransmitStatus  = EFI_SUCCESS;
  CntOfXMit           = 0;
  CallBackIndex       = 0;
  if (BSCreateEventNotifyContext) {
    CallBackIndex = 1;
  }

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  for (i = 0; i < *MnpTransmitMultiPacketCnt; i++) {
    tBS->Stall (20);
    Status = tBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    (EFI_EVENT_NOTIFY) BSCallBackFunc[CallBackIndex],
                    BSCreateEventNotifyContext,
                    &MnpTransmitMultiPacketToken->Event
                    );
    BeNotified = FALSE;

    if (EFI_ERROR (Status)) {
      *MnpTransmitMultiPacketCnt    = CntOfXMit;
      *MnpTransmitMultiPacketStatus = Status;
      return EFI_SUCCESS;
    }

    Status = Mnp->Transmit (
                    Mnp,
                    MnpTransmitMultiPacketToken
                    );
    if (EFI_ERROR (Status)) {
      *MnpTransmitMultiPacketStatus = Status;
      tBS->CloseEvent (MnpTransmitMultiPacketToken->Event);
      return EFI_SUCCESS;
    }

    while (FALSE == BeNotified) {
      Status = Mnp->Poll (Mnp);
      if (EFI_ERROR (Status)) {
        *MnpTransmitMultiPacketStatus = Status;
        tBS->CloseEvent (MnpTransmitMultiPacketToken->Event);
        return EFI_SUCCESS;
      }
    }
    //
    // Check Token->Status
    //
    if (MnpTransmitMultiPacketToken->Status == EFI_SUCCESS) {
      CntOfXMit++;
      tBS->CloseEvent (MnpTransmitMultiPacketToken->Event);
    } else if (MnpTransmitMultiPacketToken->Status == EFI_TIMEOUT) {
      continue;
    } else if (MnpTransmitMultiPacketToken->Status == EFI_DEVICE_ERROR) {
      *MnpTransmitMultiPacketCnt    = CntOfXMit;
      *MnpTransmitMultiPacketStatus = MnpTransmitMultiPacketToken->Status;
      return EFI_SUCCESS;
    } else {
      *MnpTransmitMultiPacketCnt    = CntOfXMit;
      *MnpTransmitMultiPacketStatus = MnpTransmitMultiPacketToken->Status;
      return EFI_DEVICE_ERROR;
    }
  }

  *MnpTransmitMultiPacketCnt    = CntOfXMit;
  *MnpTransmitMultiPacketStatus = EFI_SUCCESS;
  return EFI_SUCCESS;
}

VOID
RegenerateToken (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  UINTN RxIndex;

  RxIndex = (UINTN) Context;
  RxInfo.ReceivedNumber++;

  tBS->SignalEvent (RxInfo.Token[RxIndex].Packet.RxData->RecycleEvent);

  if (RxInfo.ReceivedNumber < RxInfo.TotalNumber) {
    RxInfo.Mnp->Receive (RxInfo.Mnp, &RxInfo.Token[RxIndex]);
  }
}

VOID
EFIAPI
MnpCallBackFunction0 (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  BeNotified = TRUE;
  return ;
}

VOID
EFIAPI
MnpCallBackFunction1 (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  UINTN *NotifyTimes;

  BeNotified = TRUE;

  if (Context == NULL) {
    return ;
  }

  NotifyTimes = (UINTN *) Context;
  (*NotifyTimes)++;

  return ;
}

//
// Mnp.Receive
//
static EFI_MANAGED_NETWORK_COMPLETION_TOKEN *MnpReceiveToken;
static EFI_STATUS                           *MnpReceiveStatus;

ENTS_ARG_FIELD                              gMnpReceiveArgField[] = {
  {
    POINTER,
    &MnpReceiveToken
  },
  {
    POINTER,
    &MnpReceiveStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpReceive_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Receive Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpReceiveStatus = Mnp->Receive (
                            Mnp,
                            MnpReceiveToken
                            );
  return EFI_SUCCESS;
}

//
// Mnp.ReceiveMultiPacket
//
static UINTN      MnpReceiveMultiPacketTotalNumber;
static UINTN      *MnpReceiveMultiPacketReceivedNumbber;
static UINTN      MnpReceiveMultiPacketPollTime;
static EFI_STATUS *MnpReceiveMultiPacketStatus;
ENTS_ARG_FIELD    gMnpReceiveMultiArgField[] = {
  {
    OCTETN,
    &MnpReceiveMultiPacketTotalNumber
  },
  {
    POINTER,
    &MnpReceiveMultiPacketReceivedNumbber
  },
  {
    OCTETN,
    &MnpReceiveMultiPacketPollTime
  },
  {
    POINTER,
    &MnpReceiveMultiPacketStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpReceiveMultiPacket_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp ReceiveMultiPacket Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;
  EFI_EVENT                     TimerEvent;
  EFI_STATUS                    Status;
  UINTN                         Index;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  RxInfo.Mnp = Mnp;
  RxInfo.TotalNumber = MnpReceiveMultiPacketTotalNumber;
  RxInfo.ReceivedNumber = 0;
  *MnpReceiveMultiPacketReceivedNumbber = 0;
  //
  // Create 100 token
  //
  for (Index = 0; Index < 100; Index++) {
    tBS->CreateEvent (
          EVT_NOTIFY_SIGNAL,
          TPL_CALLBACK,
          (EFI_EVENT_NOTIFY) RegenerateToken,
          (VOID *) Index,
          &RxInfo.Token[Index].Event
          );
    //
    // SctPrint (L"Create 100 Token\n");
    //
  }
  //
  // SctPrint (L"BF Receive 100 Token\n");
  //
  for (Index = 0; Index < 100; Index++) {
    Status = Mnp->Receive (Mnp, &RxInfo.Token[Index]);
    if (EFI_ERROR (Status)) {
      *MnpReceiveMultiPacketStatus = Status;
      return EFI_SUCCESS;
    }
  }

  Status = tBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);
  if (EFI_ERROR (Status)) {
    *MnpReceiveMultiPacketStatus          = Status;
    *MnpReceiveMultiPacketReceivedNumbber = RxInfo.ReceivedNumber;
    return EFI_SUCCESS;
  }

  Status = tBS->SetTimer (
                  TimerEvent,
                  TimerPeriodic,
                  (UINT64) (MnpReceiveMultiPacketPollTime * 1000000)
                  );
  if (EFI_ERROR (Status)) {
    *MnpReceiveMultiPacketReceivedNumbber = RxInfo.ReceivedNumber;
    *MnpReceiveMultiPacketStatus          = Status;
    return EFI_SUCCESS;
  }
  //
  // Wait for either
  //
  while (1) {
    *MnpReceiveMultiPacketStatus = Mnp->Poll (Mnp);
  }

  Status = tBS->CloseEvent (TimerEvent);
  if (EFI_ERROR (Status)) {
    *MnpReceiveMultiPacketReceivedNumbber = RxInfo.ReceivedNumber;
    return EFI_SUCCESS;
  }

  *MnpReceiveMultiPacketReceivedNumbber = RxInfo.ReceivedNumber;
  return EFI_SUCCESS;
}

//
// Mnp.Poll
//
static EFI_STATUS *MnpPollStatus;

ENTS_ARG_FIELD    gMnpPollArgField[] = {
  {
    POINTER,
    &MnpPollStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpPoll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp             = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpPollStatus  = Mnp->Poll (Mnp);
  return EFI_SUCCESS;
}

//
// Mnp.PollPattern1
//
static UINTN      MnpPollPattern1Timeout;
static EFI_STATUS *MnpPollPattern1Status;
ENTS_ARG_FIELD    gMnpPollPattern1ArgField[] = {
  {
    OCTETN,
    &MnpPollPattern1Timeout
  },
  {
    POINTER,
    &MnpPollPattern1Status
  },
  0
};

EFI_STATUS
EFIAPI
MnpPollPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Poll Pattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;
  EFI_EVENT                     TimerEvent;
  EFI_STATUS                    Status;
  int                           run;

  Mnp     = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;
  Status  = tBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);
  if (EFI_ERROR (Status)) {
    *MnpPollPattern1Status = Status;
    return EFI_SUCCESS;
  }

  Status = tBS->SetTimer (
                  TimerEvent,
                  TimerPeriodic,
                  (UINT64) (MnpPollPattern1Timeout * 10000000)
                  );
  if (EFI_ERROR (Status)) {
    *MnpPollPattern1Status = Status;
    tBS->CloseEvent (TimerEvent);
    return EFI_SUCCESS;
  }
  //
  // Wait for either
  //
  run = 1;
  while (run) {
    *MnpPollPattern1Status = Mnp->Poll (Mnp);
    if (!EFI_ERROR (tBS->CheckEvent (TimerEvent))) {
      run = 0;
    }
  }
  //
  // Done, cancle periodic timer
  //
  Status = tBS->SetTimer (TimerEvent, TimerCancel, 0);
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  return EFI_SUCCESS;
}

static EFI_MANAGED_NETWORK_COMPLETION_TOKEN *MnpCancelToken;
static EFI_STATUS                           *MnpCancelStatus;
ENTS_ARG_FIELD                              gMnpCancelArgField[] = {
  {
    POINTER,
    &MnpCancelToken
  },
  {
    POINTER,
    &MnpCancelStatus
  },
  0
};

EFI_STATUS
EFIAPI
MnpCancel_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mnp Cancel Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MANAGED_NETWORK_PROTOCOL  *Mnp;

  Mnp = (EFI_MANAGED_NETWORK_PROTOCOL *) ClientInterface;

  *MnpCancelStatus = Mnp->Cancel (
                            Mnp,
                            MnpCancelToken
                            );

  return EFI_SUCCESS;
}
