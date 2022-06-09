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

  SimpleNetworkBBTestMain.c

Abstract:

  Test Driver of SimpleNetwork Protocol

--*/

#include "SctLib.h"
#include "PxeBaseCodeBBTestMain.h"
#include "PxeBaseCodeBBTestSupport.h"

EFI_EVENT                       TimerEvent;
UINTN                           gCallBackInvoked;
EFI_PXE_BASE_CODE_FUNCTION      gFunction;
EFI_PXE_CALLBACK                gOldCallBack;
EFI_HANDLE                      gHandle;

EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL NewCallBackProtocol = {
  EFI_PXE_BASE_CODE_CALLBACK_INTERFACE_REVISION,
  NewCallBack
};

EFI_BB_TEST_PROTOCOL_FIELD gEfiPxeBcTestProtField = {
  PXE_BASE_CODE_TEST_REVISION,
  EFI_PXE_BASE_CODE_PROTOCOL_GUID,
  L"PXE Base Code Protocol Test",
  L"Test PXE Base Code Protocol"
};

EFI_GUID gSupportProtocolGuid1[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gPxeTestEntryField[] = {
  {
    PXE_START_FUNCTION_TEST_GUID,
    L"Start_Func",
    L"Function Test of Start",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNewStartFunctionTest
  },
  {
    PXE_STOP_FUNCTION_TEST_GUID,
    L"Stop_Func",
    L"Function Test of Stop",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNewStopFunctionTest
  },
  {
    PXE_SETIPFILTER_FUNCTION_TEST_GUID,
    L"SetIpFilter_Func",
    L"Function Test of SetIpFilter",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetIpFilterFunctionTest
  },
  {
    PXE_START_CONFORMANCE_TEST_GUID,
    L"Start_Conf",
    L"Conformance Test for Start",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNewStartConformanceTest
  },
  {
    PXE_STOP_CONFORMANCE_TEST_GUID,
    L"Stop_Conf",
    L"Conformance Test for Stop",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestNewStopConformanceTest
  },
  {
    PXE_ARP_CONFORMANCE_AUTO_TEST_GUID,
    L"Arp_Conf",
    L"Auto Conformance Test for Arp",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestArpConformanceAutoTest
  },
  
#ifdef EFI_TEST_EXHAUSTIVE  	     //Switch off the 5 old test case
    PXE_START_FUNCTION_TEST_GUID,
    L"Start_Func",
    L"Function Test of Start",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartFunctionTest
  },
  {
    PXE_STOP_FUNCTION_TEST_GUID,
    L"Stop_Func",
    L"Function Test of Stop",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStopFunctionTest
  },
  {
    PXE_SETIPFILTER_FUNCTION_TEST_GUID,
    L"SetIpFilter_Func",
    L"Function Test of SetIpFilter",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestSetIpFilterFunctionTest
  },
  {
    PXE_START_CONFORMANCE_TEST_GUID,
    L"Start_Conf",
    L"Conformance Test for Start",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStartConformanceTest
  },
  {
    PXE_STOP_CONFORMANCE_TEST_GUID,
    L"Stop_Conf",
    L"Conformance Test for Stop",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStopConformanceTest
  },

//#ifdef EFI_TEST_EXHAUSTIVE
  {
    PXE_DHCP_FUNCTION_TEST_GUID,
    L"Dhcp_Func_Manual",
    L"Manual Function Test of Dhcp",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestDhcpFunctionTest
  },
  {
    PXE_DISCOVER_FUNCTION_TEST_GUID,
    L"Discover_Func_Manual",
    L"Manual Function Test of Discover",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestDiscoverFunctionTest
  },
  {
    PXE_MTFTP_FUNCTION_TEST_GUID,
    L"Mtftp_Func_Manual",
    L"Manual Function Test of Mtftp",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestMtftpFunctionTest
  },
  {
    PXE_UDPWRITE_FUNCTION_TEST_GUID,
    L"UdpWrite_Func_Manual",
    L"Manual Function Test of UdpWrite",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestUdpWriteFunctionTest
  },
  {
    PXE_UDPREAD_FUNCTION_TEST_GUID,
    L"UdpRead_Func_Manual",
    L"Manual Function Test of UdpRead",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestUdpReadFunctionTest
  },
  {
    PXE_ARP_FUNCTION_TEST_GUID,
    L"Arp_Func_Manual",
    L"Manual Function Test of Arp",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestArpFunctionTest
  },
  {
    PXE_SETPARAMETERS_FUNCTION_TEST_GUID,
    L"SetParameters_Func_Manual",
    L"Manual Function Test of SetParameters",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetParametersFunctionTest
  },
  {
    PXE_SETSTATIONIP_FUNCTION_TEST_GUID,
    L"SetStationIp_Func_Manual",
    L"Manual Function Test of SetStationIp",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetStationIpFunctionTest
  },
  {
    PXE_SETPACKETS_FUNCTION_TEST_GUID,
    L"SetPackets_Func_Manual",
    L"Manual Function Test of SetPackets",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetPacketsFunctionTest
  },
  {
    PXE_DHCP_CONFORMANCE_TEST_GUID,
    L"Dhcp_Conf_Manual",
    L"Manual Conformance Test for Dhcp",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestDhcpConformanceTest
  },
  {
    PXE_DISCOVER_CONFORMANCE_TEST_GUID,
    L"Discover_Conf_Manual",
    L"Manual Conformance Test for Discover",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestDiscoverConformanceTest
  },
  {
    PXE_Mtftp_CONFORMANCE_TEST_GUID,
    L"Mtftp_Conf_Manual",
    L"Manual Conformance Test for Mtftp",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestMtftpConformanceTest
  },
  {
    PXE_UDPWRITE_CONFORMANCE_TEST_GUID,
    L"Dhcp_Conf_Manual",
    L"Manual Conformance Test for UdpWrite",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestUdpWriteConformanceTest
  },
  {
    PXE_UDPREAD_CONFORMANCE_TEST_GUID,
    L"UdpRead_Conf_Manual",
    L"Manual Conformance Test for UdpRead",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestUdpReadConformanceTest
  },
  {
    PXE_SETIPFILTER_CONFORMANCE_TEST_GUID,
    L"SetIpFilter_Conf_Manual",
    L"Manual Conformance Test for SetIpFilter",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetIpFilterConformanceTest
  },
  {
    PXE_ARP_CONFORMANCE_MANUAL_TEST_GUID,
    L"ARP_Conf_Manual",
    L"Manual Conformance Test for ARP",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestArpConformanceManualTest
  },
  {
    PXE_SETPARAMETERS_CONFORMANCE_TEST_GUID,
    L"SetParameters_Conf_Manual",
    L"Manual Conformance Test for SetParameters",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetParametersConformanceTest
  },
  {
    PXE_SETSTATIONIP_CONFORMANCE_TEST_GUID,
    L"SetStationIp_Conf_Manual",
    L"Manual Conformance Test for SetStationIp",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetStationIpConformanceTest
  },
  {
    PXE_SETPACKETS_CONFORMANCE_TEST_GUID,
    L"SetPackets_Conf_Manual",
    L"Manual Conformance Test for SetPackets",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_MANUAL,
    BBTestSetPacketsConformanceTest
  },
#endif

  EFI_NULL_GUID
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestPxeBcUnload (
  IN EFI_HANDLE       ImageHandle
  );

/**
 *  Creates/installs the BlackBox Interface and eminating Entry Point node list.
 *  @param  ImageHandle The test driver image handle
 *  @param  SystemTable Pointer to System Table
 *  @return EFI_SUCCESS Indicates the interface was installed
 *  @return EFI_OUT_OF_RESOURCES Indicates space for the new handle could not be allocated
 *  @return EFI_INVALID_PARAMETER: One of the parameters has an invalid value.
 */
EFI_STATUS
EFIAPI
InitializeBBTestPxeBCProtocol (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS Status;

  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);
  SctInitializeDriver (ImageHandle, SystemTable);

  Status = gtBS->CreateEvent (EVT_TIMER, 0, (EFI_EVENT_NOTIFY) NULL, NULL, &TimerEvent);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = GetSystemDevicePathAndFilePath (ImageHandle);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gEfiPxeBcTestProtField,
           gPxeTestEntryField,
           BBTestPxeBcUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestPxeBcUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
  }

  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
  }

  Status = gtBS->CloseEvent (TimerEvent);
  if (EFI_ERROR(Status)) {

  }

  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}

/******************************* Internal Function ************************************/
/**
 *  Change state of PXE Base Code Protocol.
 *  @param PxeInterface a pointer of EFI_PXE_BASE_CODE_PROTOCOL.
 *  @param UsingIpv6: if IPV6 is used while start().
 *  @param Cur: current state of PXE.
 *  @param Nxt: state what PXE state will change to.
 *  @TRUE means PXE is started.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
EFI_STATUS
ChangePxeState (
  IN EFI_PXE_BASE_CODE_PROTOCOL     *PxeInterface,
  IN BOOLEAN                        UsingIpv6,
  IN BOOLEAN                        Cur,
  IN BOOLEAN                        Nxt
  )
{
  if (Cur==Nxt) {
    return EFI_SUCCESS;
  }

  if (Cur == TRUE) {
    return PxeInterface->Stop (PxeInterface);
  }

  return PxeInterface->Start (PxeInterface, UsingIpv6);
}

EFI_STATUS
ReInitPxeBaseCode (
  IN EFI_PXE_BASE_CODE_PROTOCOL    *BcInterface
)
{
  EFI_STATUS     Status;

  // Re-initialize the EFI_PXE_BASE_CODE_PROTOCOL
  if (BcInterface->Mode->Started == TRUE)
  {
    Status = BcInterface->Stop (BcInterface);
    if (EFI_ERROR(Status)){
      return Status;
    }
  }

  Status = BcInterface->Start (BcInterface, FALSE);
  if (EFI_ERROR(Status)){
    return Status;
  }

  return EFI_SUCCESS;
}

/**
 *  Waiting for user complete operation, and type any key to indicate it.
 *  @return TRUE to indicate user operation complete.
 */
BOOLEAN
WaitForAnyInput ()
{
  UINTN                   NoWait = 1, WaitIndex;
  EFI_EVENT               WaitList[1];
  EFI_STATUS              Status;
  EFI_INPUT_KEY           Key;

  SctPrint (L"Press any key to continue...");

  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //
  NoWait = 0;
  WaitList[NoWait++] = gtST->ConIn->WaitForKey;

  //
  // Wait for either
  //
  while (NoWait) {
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        //
        // Read the key
        //
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        if (EFI_SUCCESS == Status)
          NoWait = 0;
        break;

      default:
        break;
    }
  }
  SctPrint (L"\r\n");

  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return TRUE;

}


BOOLEAN
WaitForUserCheck ()
{
  UINTN                   NoWait = 1, WaitIndex;
  EFI_EVENT               WaitList[1];
  EFI_STATUS              Status;
  EFI_INPUT_KEY           Key;
  BOOLEAN                 PressYes=FALSE;

  SctPrint (L"\r\nPress \"Y\" or \"N\"...");

  //
  // Set 1 second periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerPeriodic, 10000000);

  //
  // Set up a wait list for a key and the timer
  //
  NoWait = 0;
  WaitList[NoWait++] = gtST->ConIn->WaitForKey;

  //
  // Wait for either
  //
  while (NoWait) {
    Status = gtBS->WaitForEvent (NoWait, WaitList, &WaitIndex);

    switch (WaitIndex) {
      case 0:
        //
        // Read the key
        //
        Status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key);
        SctAPrint ((char *)(&Key.UnicodeChar));
        switch (Key.UnicodeChar) {
          case 'Y':
          case 'y':
            NoWait = 0;
            PressYes = TRUE;
            break;

          case 'N':
          case 'n':
            NoWait = 0;
            PressYes = FALSE;
            break;

          default :
            SctPrint (L"\n");
            break;
        }
        break;

      default:
        break;
    }
  }
  SctPrint (L"\r\n");

  //
  // Done, cancle periodic timer
  //
  Status = gtBS->SetTimer (TimerEvent, TimerCancel, 0);

  return PressYes;

}

EFI_PXE_BASE_CODE_CALLBACK_STATUS
EFIAPI
NewCallBack (
  IN EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL  *This,
  IN EFI_PXE_BASE_CODE_FUNCTION           Function,
  IN BOOLEAN                              Received,
  IN UINT32                               PacketLen,
  IN EFI_PXE_BASE_CODE_PACKET             *Packet OPTIONAL
  )
{
  if (Function == gFunction) {
    gCallBackInvoked ++;
    return EFI_PXE_BASE_CODE_CALLBACK_STATUS_ABORT;
  } else if (gOldCallBack != NULL) {
    return gOldCallBack (This, Function, Received, PacketLen, Packet);
  } else {
    return EFI_PXE_BASE_CODE_CALLBACK_STATUS_CONTINUE;
  }
}

EFI_STATUS
HookReturnAbortCallBack (
  IN EFI_PXE_BASE_CODE_FUNCTION         FuncNum,
  IN EFI_PXE_BASE_CODE_PROTOCOL         *BcInterface
  )
{
  EFI_STATUS                          Status;
  EFI_HANDLE                          *HandleBuffer;
  UINTN                               HandleCount;
  UINTN                               Index;
  EFI_PXE_BASE_CODE_PROTOCOL          *Interface;
  EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL *BcCallBack;
  BOOLEAN                             NewMakeCallback;

  //
  // init global variables
  //
  gCallBackInvoked = 0;
  gFunction = FuncNum;
  gOldCallBack = NULL;

  //
  // Locate all handles of Pxe protocol
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiPxeBaseCodeProtocolGuid,
                   NULL,
                   &HandleCount,
                   &HandleBuffer
                   );
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }

  //
  // Looking for the handle corresponding to the BcInterface
  //
  gHandle = NULL;
  for (Index = 0; Index < HandleCount; Index += 1) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiPxeBaseCodeProtocolGuid,
                     (VOID **)&Interface
                   );
    if (BcInterface == Interface) {
      gHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (gHandle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Is Pxe Callback probocol installed?
  //
  Status = gtBS->HandleProtocol (
                   gHandle,
                   &gBlackBoxEfiPxeBaseCodeCallbackProtocolGuid,
                   (VOID **)&BcCallBack
                   );
  if (Status == EFI_SUCCESS) {
    // Replace the previous call back function
    gOldCallBack = BcCallBack->Callback;
    BcCallBack->Callback = NewCallBack;
  } else {
    //
    // Install a call back protocol
    //
    Status = gtBS->InstallProtocolInterface (
                     &gHandle,
                     &gBlackBoxEfiPxeBaseCodeCallbackProtocolGuid,
                     EFI_NATIVE_INTERFACE,
                     &NewCallBackProtocol
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
    //
    // Enable PXE to use call back
    //
    NewMakeCallback = TRUE;
    Status = BcInterface->SetParameters (
                            BcInterface,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            &NewMakeCallback
                            );
    if (EFI_ERROR(Status)) {
      gtBS->UninstallProtocolInterface (
              gHandle,
              &gBlackBoxEfiPxeBaseCodeCallbackProtocolGuid,
              &NewCallBackProtocol
              );
      return Status;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
UnHookReturnAbortCallBack (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface
  )
{
  EFI_STATUS                          Status;
  EFI_PXE_BASE_CODE_CALLBACK_PROTOCOL *BcCallBack;
  BOOLEAN                             NewMakeCallback;

  if (gOldCallBack != NULL) {
    Status = gtBS->HandleProtocol (
                     gHandle,
                     &gBlackBoxEfiPxeBaseCodeCallbackProtocolGuid,
                     (VOID **)&BcCallBack
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
    // restore the previous call back function
    BcCallBack->Callback = gOldCallBack;
    gOldCallBack = NULL;
  } else {
    //
    // Disable PXE to use call back
    //
    NewMakeCallback = FALSE;
    Status = BcInterface->SetParameters (
                            BcInterface,
                            NULL,
                            NULL,
                            NULL,
                            NULL,
                            &NewMakeCallback
                            );
    if (EFI_ERROR(Status)) {
      return Status;
    }
    Status = gtBS->UninstallProtocolInterface (
                     gHandle,
                     &gBlackBoxEfiPxeBaseCodeCallbackProtocolGuid,
                     &NewCallBackProtocol
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

BOOLEAN
IsPxePacketValid (
  IN EFI_PXE_PACKET_TYPE         PacketType,
  IN EFI_PXE_BASE_CODE_PACKET    *Packet
  )
{
  //BootpOpCode
  switch (PacketType)
  {
    case EFI_PXE_PACKET_TYPE_DHCP_DISCOVER:
      return TRUE;

    case EFI_PXE_PACKET_TYPE_DHCP_ACK:
      return TRUE;

    case EFI_PXE_PACKET_TYPE_PROXY_OFFER:
      return TRUE;

    case EFI_PXE_PACKET_TYPE_PXE_DISCOVER:
      return TRUE;

    case EFI_PXE_PACKET_TYPE_PXE_OFFER:
      return TRUE;

    default:
      return FALSE;
  }
}

BOOLEAN
IsBufZeroed (
  IN CHAR8                *Buf,
  IN UINTN                 Len
  )
{
  UINTN i;

  for (i=0; i<Len; i++) {
    if (0 != *(Buf + i)) {
      return FALSE;
    }
  }

  return TRUE;
}


EFI_STATUS
PrintPxePacket (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN CHAR16                            *Title,
  IN EFI_PXE_BASE_CODE_PACKET          *Packet
  )
{
  UINT16                                TempUint16;

  if (NULL == Packet || NULL == LoggingLib)
    return EFI_INVALID_PARAMETER;

  // print the packet type
  LOG_CHAR16_ASCII_DFLT(LoggingLib, Title, SctStrLen (Title));

  // print the raw packet
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Raw Packet]", SctStrLen (L"[Raw Packet]"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*) (Packet->Raw),1472/2);

  TempUint16 = (UINT16)Packet->Dhcpv4.BootpOpcode;
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Opcode]", SctStrLen (L"[Bootp Opcode]"));
  LOG_UINT16_HEX_DFLT(LoggingLib, TempUint16);

  TempUint16 = (UINT16)Packet->Dhcpv4.BootpHwType;
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Hw Type]", SctStrLen (L"[Bootp Hw Type]"));
  LOG_UINT16_HEX_DFLT(LoggingLib, TempUint16);

  TempUint16 = (UINT16)Packet->Dhcpv4.BootpHwAddrLen;
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Hw Addr Len]", SctStrLen (L"[Bootp Hw Addr Len]"));
  LOG_UINT16_HEX_DFLT(LoggingLib, TempUint16);

  TempUint16 = (UINT16)Packet->Dhcpv4.BootpGateHops;
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Gate Hop]", SctStrLen (L"[Bootp Gate Hop]"));
  LOG_UINT16_HEX_DFLT(LoggingLib, TempUint16);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Iden]", SctStrLen (L"[Bootp Iden]"));
  LOG_UINT32_HEX_DFLT(LoggingLib, (Packet->Dhcpv4.BootpIdent));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Seconds]", SctStrLen (L"[Bootp Seconds]"));
  LOG_UINT16_HEX_DFLT(LoggingLib,Packet->Dhcpv4.BootpSeconds);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Flags]", SctStrLen (L"[Bootp Flags]"));
  LOG_UINT16_HEX_DFLT(LoggingLib,(Packet->Dhcpv4.BootpFlags));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp CiAddr]", SctStrLen (L"[Bootp CiAddr]"));
  LOG_IP_HEX_DFLT(LoggingLib, Packet->Dhcpv4.BootpCiAddr);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp YiAddr]", SctStrLen (L"[Bootp YiAddr]"));
  LOG_IP_HEX_DFLT(LoggingLib, Packet->Dhcpv4.BootpYiAddr);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp SiAddr]", SctStrLen (L"[Bootp SiAddr]"));
  LOG_IP_HEX_DFLT(LoggingLib, Packet->Dhcpv4.BootpSiAddr);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp GiAddr]", SctStrLen (L"[Bootp GiAddr]"));
  LOG_IP_HEX_DFLT(LoggingLib, Packet->Dhcpv4.BootpGiAddr);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp HwAddr]", SctStrLen (L"[Bootp HwAddr]"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(Packet->Dhcpv4.BootpSrvName), 32);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp SrvName]", SctStrLen (L"[Bootp SrvName]"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(Packet->Dhcpv4.BootpHwAddr), 8);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp BootFile]", SctStrLen (L"[Bootp BootFile]"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(Packet->Dhcpv4.BootpBootFile), 64);

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Bootp Magik]", SctStrLen (L"[Bootp Magik]"));
  LOG_UINT32_HEX_DFLT(LoggingLib, Packet->Dhcpv4.DhcpMagik);

  return EFI_SUCCESS;
}

EFI_STATUS
PrintArpTable (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN EFI_PXE_BASE_CODE_MODE            *Mode
  )
{
  UINTN                  i, cnt;
  CHAR16                *Buffer;

  LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, L"Arp Entry is", (UINT32)SctStrLen (L"Arp Entry is"), EFI_DUMP_ASCII);
  cnt = 0;
  for (i = 0; i < EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES; i++)
  {
    if (FALSE == IsBufZeroed ((CHAR8 *)(&Mode->ArpCache[i]), sizeof (EFI_PXE_BASE_CODE_ARP_ENTRY)))
    {
      cnt ++;
      Buffer = (CHAR16 *)(&Mode->ArpCache[i]);
      LoggingLib->DumpBuf (LoggingLib, EFI_VERBOSE_LEVEL_DEFAULT, Buffer, (UINT32)SctStrLen (Buffer), EFI_DUMP_HEX);
    }
  }

  if (cnt == Mode->ArpCacheEntries)
    return EFI_SUCCESS;

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Arp Cache Unmatched", SctStrLen (L"Arp Cache Unmatched"));
  return EFI_INVALID_PARAMETER;
}

EFI_STATUS
SetIpAndMask(
  IN EFI_IP_ADDRESS       *EfiIp,
  IN EFI_IP_ADDRESS       *EfiMask,
  IN UINT32               NumIpv4,
  IN UINT32               NumMask
  )
{
  EFI_STATUS             Status;

  if (NULL != EfiIp)
  {
    Status = SetIpAddress (EfiIp, NumIpv4);
    if (EFI_ERROR(Status))
      return Status;
  }

  if (NULL != EfiMask)
  {
    Status = SetIpAddress (EfiMask, NumMask);
    if (EFI_ERROR(Status))
      return Status;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
SetIpAddress (
  IN OUT EFI_IP_ADDRESS *EfiIp,
  IN     UINT32         NumIpv4
  )
{
  if (NULL == EfiIp)
    return EFI_INVALID_PARAMETER;

  EfiIp->v4.Addr[0] = (UINT8)(NumIpv4 >> 24);
  EfiIp->v4.Addr[1] = (UINT8)((NumIpv4 & 0xff0000) >> 16);
  EfiIp->v4.Addr[2] = (UINT8)((NumIpv4 & 0xff00) >> 8);
  EfiIp->v4.Addr[3] = (UINT8)(NumIpv4 & 0xff);

  return EFI_SUCCESS;
}

BOOLEAN
IsIpMaskEqual (
  IN EFI_IP_ADDRESS *NewStationIp,
  IN EFI_IP_ADDRESS *NewSubnetMask,
  IN EFI_IP_ADDRESS *OldStationIp,
  IN EFI_IP_ADDRESS *OldSubnetMask
  )
{
  if (NULL != NewStationIp){
    if (FALSE == (0 == SctCompareMem (NewStationIp, OldStationIp, sizeof (EFI_IP_ADDRESS)))) {
      return FALSE;
    }
  }

  if (NULL != NewSubnetMask){
    if (FALSE == (0 == SctCompareMem (NewSubnetMask, OldSubnetMask, sizeof (EFI_IP_ADDRESS)))){
      return FALSE;
    }
  }
  return TRUE;
}

EFI_STATUS
CopyPxePacket (
  IN EFI_PXE_BASE_CODE_PACKET *DestPacket,
  IN EFI_PXE_BASE_CODE_PACKET *SrcPacket
  )
{
  if (NULL == DestPacket) {
    return EFI_SUCCESS;
  }

  if (NULL == SrcPacket) {
    return EFI_INVALID_PARAMETER;
  }

  SctCopyMem (DestPacket, SrcPacket, sizeof (EFI_PXE_BASE_CODE_PACKET));
  return EFI_SUCCESS;
}

BOOLEAN
IsPxePacketEqual (
  IN EFI_PXE_BASE_CODE_PACKET *DestPacket,
  IN EFI_PXE_BASE_CODE_PACKET *SrcPacket
  )
{
  if (NULL == DestPacket && NULL == SrcPacket) {
    return TRUE;
  }
  if (0==SctCompareMem (DestPacket, SrcPacket, sizeof (EFI_PXE_BASE_CODE_PACKET))){
    return TRUE;
  }
  return FALSE;
}

BOOLEAN
IsIpFilterEqual (
  IN EFI_PXE_BASE_CODE_IP_FILTER *SrcIpFilter,
  IN EFI_PXE_BASE_CODE_IP_FILTER *DstIpFilter
  )
{
  if (NULL == SrcIpFilter && NULL == DstIpFilter) {
    return TRUE;
  }

  if (NULL != SrcIpFilter && NULL != DstIpFilter)
  {
    if (SrcIpFilter->IpCnt != DstIpFilter->IpCnt) {
      return FALSE;
    }

    if (0==SctCompareMem (SrcIpFilter->IpList, DstIpFilter->IpList, sizeof (EFI_IP_ADDRESS) * SrcIpFilter->IpCnt)){
      return TRUE;
    }
  }
  return FALSE;
}

EFI_STATUS
LogUdpPacket (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL *LoggingLib,
  IN EFI_IP_ADDRESS                    *DestIp,
  IN EFI_PXE_BASE_CODE_UDP_PORT        *DestPort,
  IN EFI_IP_ADDRESS                    *SrcIp,
  IN EFI_PXE_BASE_CODE_UDP_PORT        *SrcPort,
  IN UINTN                              BufferSize,
  IN VOID                              *BufferPtr
  )
{
  if (NULL!=DestIp)
  {
    LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Dest IP]", SctStrLen (L"[Dest IP]"));
    //LOG_IP_HEX_DFLT (LoggingLib, DestIp->v4.Addr);
    LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)&DestIp, sizeof (EFI_IP_ADDRESS)/2);
  }

  if (NULL != DestPort)
  {
    LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Dest Port]", SctStrLen (L"[Dest Port]"));
    LOG_UINT16_HEX_DFLT(LoggingLib, *DestPort);
  }

  if (NULL != SrcIp)
  {
    LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Src IP]", SctStrLen (L"[Src IP]"));
    //LOG_IP_HEX_DFLT (LoggingLib, SrcIp->v4.Addr);
    LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)&SrcIp, sizeof (EFI_IP_ADDRESS)/2);
  }

  if (NULL != SrcPort)
  {
    LOG_CHAR16_ASCII_DFLT(LoggingLib, L"[Src Port]", SctStrLen (L"[Src Port]"));
    LOG_UINT16_HEX_DFLT(LoggingLib, *SrcPort);
  }
  if (0!=BufferSize)
  {
    LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Received UDP Packet", SctStrLen (L"Received UDP Packet"));
    LOG_BUF_HEX_DFLT(LoggingLib, BufferPtr, BufferSize);
  }
  return EFI_SUCCESS;
}

EFI_STATUS
LogChar8String (
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL           *LoggingLib,
  IN CHAR8                                       *Buffer,
  IN UINTN                                        Len
  )
{
  EFI_STATUS           Status;
  CHAR16              *TempBuffer;

  if (NULL == Buffer) {
    return EFI_INVALID_PARAMETER;
  }

  Status = gtBS->AllocatePool (EfiRuntimeServicesData, Len * sizeof (CHAR16), (VOID **) &TempBuffer);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  SctZeroMem (&TempBuffer, Len * sizeof (CHAR16));

  LOG_CHAR16_ASCII_DFLT (LoggingLib, TempBuffer, Len);

  gtBS->FreePool (TempBuffer);
  return EFI_SUCCESS;
}
