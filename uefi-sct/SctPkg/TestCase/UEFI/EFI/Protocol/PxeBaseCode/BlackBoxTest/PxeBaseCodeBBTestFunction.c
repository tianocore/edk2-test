/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2022, ARM Limited. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  PxeBaseCodeBBTestFunction.c

Abstract:

  Function Test Cases of SimpleNetwork Protocol

--*/

#include "SctLib.h"
#include "PxeBaseCodeBBTestMain.h"
#include "PxeBaseCodeBBTestSupport.h"

EFI_STATUS
EFIAPI
BBTestTftpGetFileSize (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_INI_FILE_HANDLE                 FileHandle,
  OUT UINTN                             *Size
  );

EFI_STATUS
EFIAPI
BBTestTftpReadFile  (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  );


EFI_STATUS
EFIAPI
BBTestTftpWriteFile    (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );


EFI_STATUS
EFIAPI
BBTestTftpGetDirectorySize (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  OUT UINTN                                *Size
  );



EFI_STATUS
EFIAPI
BBTestTftpReadDirectory (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  );


EFI_STATUS
EFIAPI
BBTestMtftpReadFile (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  );


EFI_STATUS
EFIAPI
BBTestMtftpReadDirectory (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  );

EFI_STATUS
EFIAPI
BBTestMtftpGetFileSize (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  OUT UINTN                                *Size
  );

EFI_STATUS
EFIAPI
BBTestSetStationIp (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_IP_ADDRESS                     *NewStationIp,
  IN EFI_IP_ADDRESS                     *NewSubnetMask,
  IN UINT32                              Ipv4,
  IN UINT32                              Mask
  );

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncBasic (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncFrag (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncPrependHeader (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncThrGateway (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  );

EFI_STATUS
EFIAPI
BBTestUdpReadFuncBasic (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  );

EFI_STATUS
EFIAPI
BBTestUdpReadFuncDesIpFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  );

EFI_STATUS
EFIAPI
BBTestUdpReadFuncDestPortFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  );

EFI_STATUS
EFIAPI
BBTestUdpReadFuncSrcIpFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  );

EFI_STATUS
EFIAPI
BBTestUdpReadFuncSrcPortFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  );

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Start() Function Test.
 *  It is the new case to add IPv6 into the test scope. The original test case is switched off.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
EFI_STATUS
EFIAPI
BBTestNewStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;

  UINT32                                Index;
  CHAR8                                 *TempPointer;

  Index       = 0;
  TempPointer = NULL;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
  //
  if (BcInterface->Mode->Started) {
    Status = BcInterface->Stop (BcInterface);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
  }

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in Ipv4
  //
  Status = BcInterface->Start (BcInterface, FALSE);
  if ((Status == EFI_SUCCESS)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else if ((Status == EFI_DEVICE_ERROR) || (Status == EFI_OUT_OF_RESOURCES)){
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestNewFunctionAssertionGuid001,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Using IPv4 - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    if (BcInterface->Mode->Started != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->Started - %s\r\n",
                     BcInterface->Mode->Started ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->UsingIpv6 != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->UsingIpv6 - %s\r\n",
                     BcInterface->Mode->UsingIpv6 ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->AutoArp != TRUE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->AutoArp - %s\r\n",
                     BcInterface->Mode->AutoArp ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->SendGUID != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->SendGUID - %s\r\n",
                     BcInterface->Mode->SendGUID ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->DhcpDiscoverValid != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->DhcpDiscoverValid - %s\r\n",
                     BcInterface->Mode->DhcpDiscoverValid ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->DhcpAckReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->DhcpAckReceived - %s\r\n",
                     BcInterface->Mode->DhcpAckReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->ProxyOfferReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->ProxyOfferReceived - %s\r\n",
                     BcInterface->Mode->ProxyOfferReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->PxeDiscoverValid != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->PxeDiscoverValid - %s\r\n",
                     BcInterface->Mode->PxeDiscoverValid ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->PxeReplyReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->PxeReplyReceived - %s\r\n",
                     BcInterface->Mode->PxeReplyReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->PxeBisReplyReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->PxeBisReplyReceived - %s\r\n",
                     BcInterface->Mode->PxeBisReplyReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->IcmpErrorReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->IcmpErrorReceived - %s\r\n",
                     BcInterface->Mode->IcmpErrorReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->TftpErrorReceived != FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->TftpErrorReceived - %s\r\n",
                     BcInterface->Mode->TftpErrorReceived ? L"TRUE" : L"FALSE"
                     );
    }
    if (BcInterface->Mode->TTL != DEFAULT_TTL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->TTL - %d\r\n",
                     BcInterface->Mode->TTL
                     );
    }
    if (BcInterface->Mode->ToS != DEFAULT_ToS) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->ToS - %d\r\n",
                     BcInterface->Mode->ToS
                     );
    }
    if (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->StationIp) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_IP_ADDRESS_ZEROED(Mode->StationIp) - Fail\r\n"
                     );
    }
    if (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->SubnetMask) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_IP_ADDRESS_ZEROED(Mode->SubnetMask) - Fail\r\n"
                     );
    }
    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpDiscover) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->DhcpDiscover) - Fail\r\n"
                     );
    }
    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpAck) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->DhcpAck) - Fail\r\n"
                     );
    }
    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->ProxyOffer) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->ProxyOffer) - Fail\r\n"
                     );
    }

    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeDiscover) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->PxeDiscover) - Fail\r\n"
                     );
    }
    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeReply) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->PxeReply) - Fail\r\n"
                     );
    }
    if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeBisReply) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_PXE_PACKET_ZEROED(Mode->PxeBisReply) - Fail\r\n"
                     );
    }
    if ((0 != BcInterface->Mode->IpFilter.Filters) || (0 != BcInterface->Mode->IpFilter.IpCnt)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"The Mode->IpFilter.Filters or Mode->IpFilter.IpCnt field is not 0\r\n"
                     );
    }
    if (BcInterface->Mode->ArpCacheEntries != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->ArpCacheEntries - %d\r\n",
                     BcInterface->Mode->ArpCacheEntries
                     );
    }
    if (BcInterface->Mode->ArpCache != NULL) {
      TempPointer = (CHAR8 *) BcInterface->Mode->ArpCache;
      for (Index = 0; Index < sizeof (EFI_PXE_BASE_CODE_ARP_ENTRY) * EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES; Index ++ ) {
        if (*TempPointer != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Mode->ArpCache- %d\r\n",
                         BcInterface->Mode->ArpCache
                         );
          break;
        }
        TempPointer++;
      }
    }
    if (BcInterface->Mode->ArpCache == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->ArpCache- %d\r\n",
                     BcInterface->Mode->ArpCache
                     );
    }
    if (BcInterface->Mode->RouteTableEntries != 0) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->RouteTableEntries - %d\r\n",
                     BcInterface->Mode->RouteTableEntries
                     );
    }
    if (BcInterface->Mode->RouteTable != NULL) {
      TempPointer = (CHAR8 *) BcInterface->Mode->RouteTable;
      for (Index = 0; Index < sizeof (EFI_PXE_BASE_CODE_ROUTE_ENTRY) * EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES; Index ++ ) {
        if (*TempPointer != 0) {
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          StandardLib->RecordMessage (
                         StandardLib,
                         EFI_VERBOSE_LEVEL_DEFAULT,
                         L"Mode->RouteTable- %d\r\n",
                         BcInterface->Mode->RouteTable
                         );
          break;
        }
        TempPointer++;
      }
    }
    if (BcInterface->Mode->RouteTable == NULL) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Mode->RouteTable- %d\r\n",
                     BcInterface->Mode->RouteTable
                     );
    }
    if (IS_ICMP_ERROR_ZEROED(&BcInterface->Mode->IcmpError) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_ICMP_ERROR_ZEROED(Mode->IcmpError) - Fail\r\n"
                     );
    }
    if (IS_TFTP_ERROR_ZEROED(&BcInterface->Mode->TftpError) == FALSE) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IS_TFTP_ERROR_ZEROED(Mode->TftpError) - Fail\r\n"
                     );
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestNewFunctionAssertionGuid002,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Using IPv4 - Check Mode",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  if (BcInterface->Mode->Ipv6Available && BcInterface->Mode->Ipv6Supported) {
    //
    // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
    //
    if (BcInterface->Mode->Started) {
      Status = BcInterface->Stop (BcInterface);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
    }

    //
    // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in IPv6
    //
    Status = BcInterface->Start (BcInterface, TRUE);
    if ((Status == EFI_SUCCESS)) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else if ((Status == EFI_DEVICE_ERROR) || (Status == EFI_OUT_OF_RESOURCES)){
      AssertionType = EFI_TEST_ASSERTION_WARNING;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestNewFunctionAssertionGuid003,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Using IPv6 - Check Return Code",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );


    if (AssertionType == EFI_TEST_ASSERTION_PASSED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      if (BcInterface->Mode->Started != TRUE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->Started - %s\r\n",
                       BcInterface->Mode->Started ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->UsingIpv6 != TRUE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->UsingIpv6 - %s\r\n",
                       BcInterface->Mode->UsingIpv6 ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->AutoArp != TRUE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->AutoArp - %s\r\n",
                       BcInterface->Mode->AutoArp ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->SendGUID != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->SendGUID - %s\r\n",
                       BcInterface->Mode->SendGUID ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->DhcpDiscoverValid != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->DhcpDiscoverValid - %s\r\n",
                       BcInterface->Mode->DhcpDiscoverValid ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->DhcpAckReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->DhcpAckReceived - %s\r\n",
                       BcInterface->Mode->DhcpAckReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->ProxyOfferReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->ProxyOfferReceived - %s\r\n",
                       BcInterface->Mode->ProxyOfferReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->PxeDiscoverValid != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->PxeDiscoverValid - %s\r\n",
                       BcInterface->Mode->PxeDiscoverValid ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->PxeReplyReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->PxeReplyReceived - %s\r\n",
                       BcInterface->Mode->PxeReplyReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->PxeBisReplyReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->PxeBisReplyReceived - %s\r\n",
                       BcInterface->Mode->PxeBisReplyReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->IcmpErrorReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->IcmpErrorReceived - %s\r\n",
                       BcInterface->Mode->IcmpErrorReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->TftpErrorReceived != FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->TftpErrorReceived - %s\r\n",
                       BcInterface->Mode->TftpErrorReceived ? L"TRUE" : L"FALSE"
                       );
      }
      if (BcInterface->Mode->TTL != DEFAULT_TTL) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->TTL - %d\r\n",
                       BcInterface->Mode->TTL
                       );
      }
      if (BcInterface->Mode->ToS != DEFAULT_ToS) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->ToS - %d\r\n",
                       BcInterface->Mode->ToS
                       );
      }
      if (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->StationIp) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_IP_ADDRESS_ZEROED(Mode->StationIp) - Fail\r\n"
                       );
      }
      if (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->SubnetMask) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_IP_ADDRESS_ZEROED(Mode->SubnetMask) - Fail\r\n"
                       );
      }
      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpDiscover) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->DhcpDiscover) - Fail\r\n"
                       );
      }
      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpAck) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->DhcpAck) - Fail\r\n"
                       );
      }
      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->ProxyOffer) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->ProxyOffer) - Fail\r\n"
                       );
      }

      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeDiscover) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->PxeDiscover) - Fail\r\n"
                       );
      }
      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeReply) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->PxeReply) - Fail\r\n"
                       );
      }
      if (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeBisReply) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_PXE_PACKET_ZEROED(Mode->PxeBisReply) - Fail\r\n"
                       );
      }
      if ((0 != BcInterface->Mode->IpFilter.Filters) || (0 != BcInterface->Mode->IpFilter.IpCnt)) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"The Mode->IpFilter.Filters or Mode->IpFilter.IpCnt field is not 0\r\n"
                       );
      }
      if (BcInterface->Mode->ArpCacheEntries != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->ArpCacheEntries - %d\r\n",
                       BcInterface->Mode->ArpCacheEntries
                       );
      }
      if (BcInterface->Mode->ArpCache != NULL) {
        TempPointer = (CHAR8 *) BcInterface->Mode->ArpCache;
        for (Index = 0; Index < sizeof (EFI_PXE_BASE_CODE_ARP_ENTRY) * EFI_PXE_BASE_CODE_MAX_ARP_ENTRIES; Index ++ ) {
          if (*TempPointer != 0) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"Mode->ArpCache- %d\r\n",
                           BcInterface->Mode->ArpCache
                           );
            break;
          }
          TempPointer++;
        }
      }
      if (BcInterface->Mode->ArpCache == NULL) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->ArpCache- %d\r\n",
                       BcInterface->Mode->ArpCache
                       );
      }
      if (BcInterface->Mode->RouteTableEntries != 0) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->RouteTableEntries - %d\r\n",
                       BcInterface->Mode->RouteTableEntries
                       );
      }
      if (BcInterface->Mode->RouteTable != NULL) {
        TempPointer = (CHAR8 *) BcInterface->Mode->RouteTable;
        for (Index = 0; Index < sizeof (EFI_PXE_BASE_CODE_ROUTE_ENTRY) * EFI_PXE_BASE_CODE_MAX_ROUTE_ENTRIES; Index ++ ) {
          if (*TempPointer != 0) {
            AssertionType = EFI_TEST_ASSERTION_FAILED;
            StandardLib->RecordMessage (
                           StandardLib,
                           EFI_VERBOSE_LEVEL_DEFAULT,
                           L"Mode->RouteTable- %d\r\n",
                           BcInterface->Mode->RouteTable
                           );
            break;
          }
          TempPointer++;
        }
      }
      if (BcInterface->Mode->RouteTable == NULL) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"Mode->RouteTable- %d\r\n",
                       BcInterface->Mode->RouteTable
                       );
      }
      if (IS_ICMP_ERROR_ZEROED(&BcInterface->Mode->IcmpError) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_ICMP_ERROR_ZEROED(Mode->IcmpError) - Fail\r\n"
                       );
      }
      if (IS_TFTP_ERROR_ZEROED(&BcInterface->Mode->TftpError) == FALSE) {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        StandardLib->RecordMessage (
                       StandardLib,
                       EFI_VERBOSE_LEVEL_DEFAULT,
                       L"IS_TFTP_ERROR_ZEROED(Mode->TftpError) - Fail\r\n"
                       );
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPxeBaseCodeBBTestNewFunctionAssertionGuid004,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Using IPv6 - Check Mode",
                     L"%a:%d:",
                     __FILE__,
                     (UINTN)__LINE__
                     );
    }
  }

  //
  // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
  //
  if (BcInterface->Mode->Started) {
    Status = BcInterface->Stop (BcInterface);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }
  }

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Statistics() Function Test.
 *  It is the new case to add IPv6 into the test scope. The original test case is switched off.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
EFI_STATUS
EFIAPI
BBTestNewSetIpFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_STATUS                             Status;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_PXE_BASE_CODE_IP_FILTER            BcIpFilter;
  UINT8                                  Index;

  Index = 0;

  //
  // Get the Standard Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             NULL,
             &LoggingLib
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
  //
  if (BcInterface->Mode->Started) {
    Status = BcInterface->Stop (BcInterface);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
  }

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in IPv4
  //
  Status = BcInterface->Start (BcInterface, FALSE);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Can't change the PXE state to enabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SctSetMem (&BcIpFilter, sizeof (BcIpFilter), 0);
  BcIpFilter.Filters = EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP;
  BcIpFilter.IpCnt = 2;
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[0]), 0x12345678);
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[1]), 0x87654321);

  Status = BcInterface->SetIpFilter (BcInterface, &BcIpFilter);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestNewFunctionAssertionGuid007,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (TRUE == IsIpFilterEqual (&BcIpFilter, &(BcInterface->Mode->IpFilter))){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestNewFunctionAssertionGuid008,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (BcInterface->Mode->Ipv6Supported && BcInterface->Mode->Ipv6Available) {
    //
    // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
    //
    if (BcInterface->Mode->Started) {
      Status = BcInterface->Stop (BcInterface);
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
    }

    //
    // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in IPv6
    //
    Status = BcInterface->Start (BcInterface, TRUE);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Can't change the PXE state to enabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }

    SctSetMem (&BcIpFilter, sizeof (BcIpFilter), 0);
    BcIpFilter.Filters = EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP;
    BcIpFilter.IpCnt = 2;

    for (Index = 0; Index < 16; Index++) {
      BcIpFilter.IpList[0].v6.Addr[Index] = Index;
      BcIpFilter.IpList[1].v6.Addr[Index] = 16 - Index;
    }

    Status = BcInterface->SetIpFilter (BcInterface, &BcIpFilter);
    if (Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestNewFunctionAssertionGuid009,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Return Code",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if (TRUE == IsIpFilterEqual (&BcIpFilter, &(BcInterface->Mode->IpFilter))){
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestNewFunctionAssertionGuid010,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Mode",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Stop() Function Test.
 *  It is the new case to add IPv6 into the test scope. The original test case is switched off.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
EFI_STATUS
EFIAPI
BBTestNewStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
  //
  if (BcInterface->Mode->Started) {
    Status = BcInterface->Stop (BcInterface);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Can't change the PXE state to disabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
  }

  if (BcInterface->Mode->Ipv6Supported && BcInterface->Mode->Ipv6Available) {
    //
    // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in Ipv6
    //
    Status = BcInterface->Start (BcInterface, TRUE);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Can't change the PXE state to enabled",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
    }

    //
    // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
    //
    Status = BcInterface->Stop (BcInterface);
    if ((Status == EFI_SUCCESS) && !BcInterface ->Mode->Started) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestNewFunctionAssertionGuid005,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Basic Function in IPv6",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface in Ipv4
  //
  Status = BcInterface->Start (BcInterface, FALSE);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Can't change the PXE state to enabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Disable EFI_PXE_BASE_CODE_PROTOCOL Protocol interface
  //
  Status = BcInterface->Stop (BcInterface);
  if ((Status == EFI_SUCCESS) && !BcInterface ->Mode->Started) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestNewFunctionAssertionGuid006,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Basic Function in IPv4",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Start() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestStartFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, FALSE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start() - Could not Change PXE state",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = BcInterface->Start (BcInterface, FALSE);
  if ((Status == EFI_SUCCESS)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    //
    // Change FAIL to WARNING, because it is device-dependent.
    // For example, if NIC does not connect to the network, the other status
    // returned is acceptable.
    //
    AssertionType = EFI_TEST_ASSERTION_WARNING;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid001,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Not Using IPv6 - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Do not check Mode if start() fails.
  //
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  //
  // Check other expected behavior
  // NOTE: If we use the definition in EFI11 spec, this check point may fail
  // because the EFI_PXE_BASE_CODE_PACKET structure definition adds 8-bytes
  // Alignment, which is not compatible with previous PXE implementation.
  // So we remove the 8-bytes Alignment in EFI_PXE_BASE_CODE_PACKET structure
  // definition also.
  //
  AssertionType = EFI_TEST_ASSERTION_PASSED;
  if  (BcInterface->Mode->Started != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->Started - %s\r\n",
                   BcInterface->Mode->Started ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->UsingIpv6 != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->UsingIpv6 - %s\r\n",
                   BcInterface->Mode->UsingIpv6 ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->AutoArp != TRUE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->AutoArp - %s\r\n",
                   BcInterface->Mode->AutoArp ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->SendGUID != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->SendGUID - %s\r\n",
                   BcInterface->Mode->SendGUID ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->DhcpDiscoverValid != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->DhcpDiscoverValid - %s\r\n",
                   BcInterface->Mode->DhcpDiscoverValid ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->DhcpAckReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->DhcpAckReceived - %s\r\n",
                   BcInterface->Mode->DhcpAckReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->ProxyOfferReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->ProxyOfferReceived - %s\r\n",
                   BcInterface->Mode->ProxyOfferReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->PxeDiscoverValid != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->PxeDiscoverValid - %s\r\n",
                   BcInterface->Mode->PxeDiscoverValid ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->PxeReplyReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->PxeReplyReceived - %s\r\n",
                   BcInterface->Mode->PxeReplyReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->PxeBisReplyReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->PxeBisReplyReceived - %s\r\n",
                   BcInterface->Mode->PxeBisReplyReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->IcmpErrorReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->PxeBisReplyReceived - %s\r\n",
                   BcInterface->Mode->PxeBisReplyReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->TftpErrorReceived != FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->PxeBisReplyReceived - %s\r\n",
                   BcInterface->Mode->PxeBisReplyReceived ? L"TRUE" : L"FALSE"
                   );
  }
  if  (BcInterface->Mode->TTL != DEFAULT_TTL) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->TTL - %d\r\n",
                   BcInterface->Mode->TTL
                   );
  }
  if  (BcInterface->Mode->ToS != DEFAULT_ToS) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->ToS - %d\r\n",
                   BcInterface->Mode->ToS
                   );
  }
  if  (BcInterface->Mode->ArpCacheEntries != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->ArpCacheEntries - %d\r\n",
                   BcInterface->Mode->ArpCacheEntries
                   );
  }
  if  (BcInterface->Mode->RouteTableEntries != 0) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Mode->RouteTableEntries - %d\r\n",
                   BcInterface->Mode->RouteTableEntries
                   );
  }
  if  (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->StationIp) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_IP_ADDRESS_ZEROED(Mode->StationIp) - Fail\r\n"
                   );
  }
  if  (IS_IP_ADDRESS_ZEROED(&BcInterface->Mode->SubnetMask) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_IP_ADDRESS_ZEROED(Mode->SubnetMask) - Fail\r\n"
                   );
  }
  if  (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpDiscover) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_PXE_PACKET_ZEROED(Mode->DhcpDiscover) - Fail\r\n"
                   );
  }
  if  (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->DhcpAck) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_PXE_PACKET_ZEROED(Mode->DhcpAck) - Fail\r\n"
                   );
  }
  if  (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->ProxyOffer) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_PXE_PACKET_ZEROED(Mode->ProxyOffer) - Fail\r\n"
                   );
  }
  if  (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeDiscover) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_PXE_PACKET_ZEROED(Mode->PxeDiscover) - Fail\r\n"
                   );
  }
  if  (IS_PXE_PACKET_ZEROED(&BcInterface->Mode->PxeReply) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_PXE_PACKET_ZEROED(Mode->PxeReply) - Fail\r\n"
                   );
  }
  if  (IS_ICMP_ERROR_ZEROED(&BcInterface->Mode->IcmpError) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_ICMP_ERROR_ZEROED(Mode->IcmpError) - Fail\r\n"
                   );
  }
  if  (IS_TFTP_ERROR_ZEROED(&BcInterface->Mode->TftpError) == FALSE) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"IS_TFTP_ERROR_ZEROED(Mode->TftpError) - Fail\r\n"
                   );
  }
  if  ((0 != BcInterface->Mode->IpFilter.Filters) || (0 != BcInterface->Mode->IpFilter.IpCnt)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"The Mode->IpFilter.Filters or Mode->IpFilter.IpCnt field is not 0\r\n");
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid002,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Not Using IPv6 - Check Mode",
                 L"%a:%d:",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, FALSE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start() - Could not Change PXE state",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // If IPV6 is not supported, check the return status with IpV6
  //
  if (!BcInterface->Mode->Ipv6Supported) {
    Status = BcInterface->Start (BcInterface, TRUE);
    if (Status == EFI_UNSUPPORTED) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestFunctionAssertionGuid001,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Start - Not Using IPv6 - Check Return Code",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Stop() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestStopFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  //
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = BcInterface->Stop (BcInterface);

  if ((Status == EFI_SUCCESS) && (BcInterface ->Mode->Started == FALSE)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid003,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Stop - Basic Function",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Initialize() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestDhcpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;
  BOOLEAN                               ret;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Get the Logging Library Interface
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Wait for user to input any key to continue
  SctPrint (L"\r\nConfigure and Start DHCP Server\r\n");
  WaitForAnyInput ();

  Status = BcInterface->Dhcp (
                          BcInterface,
                          FALSE
                          );

  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid004,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Dhcp - not sorting packet - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check other field in Mode
  if ((BcInterface->Mode->DhcpDiscoverValid == FALSE)                     ||
      (IsPxePacketValid(EFI_PXE_PACKET_TYPE_DHCP_DISCOVER, &BcInterface->Mode->DhcpDiscover) == FALSE) ||
      (BcInterface->Mode->DhcpAckReceived == FALSE)                       ||
      (IsPxePacketValid (EFI_PXE_PACKET_TYPE_DHCP_ACK, &BcInterface->Mode->DhcpAck) == FALSE) ||
      (BcInterface->Mode->ProxyOfferReceived == TRUE && (IsPxePacketValid (EFI_PXE_PACKET_TYPE_PROXY_OFFER, &BcInterface->Mode->ProxyOffer) == FALSE)))
  {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestFunctionAssertionGuid005,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Dhcp - not sorting packet - Check Mode",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  LOG_CHAR16_ASCII_DFLT1(StandardLib, L"abcdefghijklmnopqrst");
  PrintPxePacket (LoggingLib, L"DHCP Discover", &BcInterface->Mode->DhcpDiscover);
  PrintPxePacket (LoggingLib, L"DHCP ACK", &BcInterface->Mode->DhcpAck);
  if (BcInterface->Mode->ProxyOfferReceived==TRUE)
        PrintPxePacket (LoggingLib, L"Proxy Offer", &BcInterface->Mode->ProxyOffer);

  SctPrint (L"\r\nPlease Check if the DHCP Packets correct?");
  ret = WaitForUserCheck ();
  if (ret==FALSE) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestFunctionAssertionGuid006,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Dhcp - Packet incorrect",
                   L"%a:%d:",
                   __FILE__,
                   (UINTN)__LINE__
                   );
  }

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Reset() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestDiscoverFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;
  UINT16                                Layer;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  // Get the Logging Library Interface
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestLoggingLibraryGuid,
                   (VOID **) &LoggingLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestDiscoverFunctionTest: Initialize PXE Protocol ...... failed"
                   );
    return Status;
  }

  // Call Dhcp() to initialize DhcpAck & ProxyOffer field
  SctPrint (L"\r\nPlease Setup DHCP Server\r\n");
  WaitForAnyInput ();
  Status = BcInterface->Dhcp (BcInterface, FALSE);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestDiscoverFunctionTest: Call Dhcp() to DhcpAck & ProxyOffer field ...... failed"
                   );
    return Status;
  }

  Layer = 0;
  Status = BcInterface->Discover (
                          BcInterface,
                          EFI_PXE_BASE_CODE_BOOT_TYPE_BOOTSTRAP,
                          &Layer,
                          FALSE,
                          NULL
                          );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid007,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Discover - basic function",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // check other field
    if (BcInterface->Mode->PxeDiscoverValid == FALSE ||
      IsPxePacketValid (EFI_PXE_PACKET_TYPE_PXE_DISCOVER, &BcInterface->Mode->PxeDiscover) == FALSE||
      BcInterface->Mode->PxeReplyReceived == FALSE ||
      IsPxePacketValid (EFI_PXE_PACKET_TYPE_PXE_OFFER, &BcInterface->Mode->PxeReply) == FALSE
      )
     {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
     }
     else
     {
       PrintPxePacket (LoggingLib, L"PXE Discover", &BcInterface->Mode->PxeDiscover);
       PrintPxePacket (LoggingLib, L"PXE Reply", &BcInterface->Mode->PxeReply);
       if (TRUE == WaitForUserCheck ()) {
         AssertionType = EFI_TEST_ASSERTION_PASSED;
       } else {
         AssertionType = EFI_TEST_ASSERTION_FAILED;
       }
     }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gPxeBaseCodeBBTestFunctionAssertionGuid008,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Discover - basic function - check packet",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Mtftp() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestMtftpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_INI_FILE_HANDLE                    FileHandle;
  EFI_STATUS                             Status;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  UINTN                                  FileSize;
  EFI_TEST_ASSERTION                     AssertionType;

  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - Get Support Library Failed",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the interface of the INI file.
  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);
  if (EFI_ERROR(Status))  {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  // Enable EFI_PXE_BASE_CODE_PROTOCOL protocol if needed
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Call SNP Interface to Reset Current MAC Address
  //
  Status = gtBS->LocateProtocol (
                   &gBlackBoxEfiSimpleNetworkProtocolGuid,
                   NULL,
                   (VOID **)&SnpInterface
                   );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Interface for SNP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if (EFI_ERROR(Status)) {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Reset Current MAC",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16*)&SnpInterface->Mode->CurrentAddress,
                    3*sizeof (EFI_MAC_ADDRESS)/2);
  //
  // Get IP Address From DHCP Server
  //
  SctPrint (L"\r\nSetup DHCP Server\r\n");
  WaitForAnyInput ();
  Status = BcInterface->Dhcp (BcInterface, FALSE);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Can't DHCP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16*)&BcInterface->Mode->StationIp, sizeof (EFI_IP_ADDRESS)/2);


  //
  // Test TFTP Get File Size
  //
  Status = BBTestTftpGetFileSize (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, &FileSize);
  //
  // Test TFTP Read File
  //
  if (EFI_SUCCESS == Status) {
    BBTestTftpReadFile (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, FileSize);
  } else {
    BBTestTftpReadFile (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, MAX_FILE_SIZE);
  }

  //
  // Test TFTP Read Directory
  //
  BBTestTftpReadDirectory (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, MAX_DIRECTORY_SIZE);

  //
  // Test TFTP Write File
  //
  BBTestTftpWriteFile      (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle);

  //
  // Test MTFTP Get File Size
  //
  Status = BBTestMtftpGetFileSize (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, &FileSize);

  //
  // Test MTFTP Read File
  //
  if (EFI_SUCCESS == Status)
  {
    BBTestMtftpReadFile (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, FileSize);
  }
  //
  // Test MTFTP Read Directory
  //
  BBTestMtftpReadDirectory (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle, MAX_DIRECTORY_SIZE);

  return CloseTestIniFile (ProfileLib, FileHandle);
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.ReceiveFilter() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.6
//
EFI_STATUS
EFIAPI
BBTestUdpWriteFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_INI_FILE_HANDLE                    FileHandle;
  EFI_STATUS                             Status;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_TEST_ASSERTION                    AssertionType;

  //
  // Get the Standard Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Get Support Library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the interface of the INI file.
  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Get INI file handler",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  //
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - PXE not enabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Call SNP Interface to Reset Current MAC Address
  //
  Status = gtBS->LocateProtocol (
                   &gBlackBoxEfiSimpleNetworkProtocolGuid,
                   NULL,
                   (VOID **)&SnpInterface
                   );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Interface for SNP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if (EFI_ERROR(Status)) {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Reset Current MAC",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16*)&SnpInterface->Mode->CurrentAddress,
                    3*sizeof (EFI_MAC_ADDRESS)/2);
  //
  // Get IP Address
  //
  SctPrint (L"\r\nSetup DHCP Server\r\n");
  WaitForAnyInput ();
  Status = BcInterface->Dhcp (BcInterface, FALSE);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Can't DHCP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16*)&BcInterface->Mode->StationIp, sizeof (EFI_IP_ADDRESS)/2);

  // 4.6.4.1 Basic Function (no fragmentation)
  BBTestUdpWriteFuncBasic (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle);

  // 4.6.4.2 Basic Function (with fragmentation)
  BBTestUdpWriteFuncFrag (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle);

  // 4.6.4.3 Prepend Header (with fragmentation)
  BBTestUdpWriteFuncPrependHeader (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle);

  // 4.6.4.3 Through Gateway
  BBTestUdpWriteFuncThrGateway (BcInterface, StandardLib, ProfileLib, LoggingLib, FileHandle);

  return CloseTestIniFile (ProfileLib, FileHandle);
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.StationAddress() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.7
//
EFI_STATUS
EFIAPI
BBTestUdpReadFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_INI_FILE_HANDLE                    FileHandle;
  EFI_STATUS                             Status;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_PXE_BASE_CODE_IP_FILTER            BcIpFilter;
  EFI_SIMPLE_NETWORK_PROTOCOL           *SnpInterface;
  EFI_TEST_ASSERTION                     AssertionType;

  //
  // Get the Support Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Get Support Library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  // Re - initialize EFI_PXE_BASE_CODE_PROTOCOL
  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Re-initialize PXE",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  // Set IPFilter to our sample setting
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Set New Filter: ", SctStrLen (L"Set New Filter: "));
  BcIpFilter.Filters = EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP;
  BcIpFilter.IpCnt = 2;
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[0]), 0x12345678);
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[1]), 0x87654321);
  Status = BcInterface->SetIpFilter (BcInterface, &BcIpFilter);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Set Sample IPFilter",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  //
  // Call SNP Interface to Reset Current MAC Address
  //
  Status = gtBS->LocateProtocol (
                   &gBlackBoxEfiSimpleNetworkProtocolGuid,
                   NULL,
                   (VOID **)&SnpInterface
                   );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Interface for SNP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if (EFI_ERROR(Status)) {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Reset Current MAC",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  // Basic Function
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"UdpRead: basic test", SctStrLen (L"UdpRead: basic test"));
  BBTestUdpReadFuncBasic(BcInterface, StandardLib, LoggingLib, &BcIpFilter);

 // Dest IP Filter
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"UdpRead: Dest Ip Filter", SctStrLen (L"UdpRead: Dest Ip Filter"));
  COPY_IP_FILTER (&BcIpFilter, &BcInterface->Mode->IpFilter);
  BBTestUdpReadFuncDesIpFilter (BcInterface, StandardLib, LoggingLib, &BcIpFilter);

  // Dest Port Filter
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"UdpRead: Dest Port Filter", SctStrLen (L"UdpRead: Dest Port Filter"));
  COPY_IP_FILTER (&BcIpFilter, &BcInterface->Mode->IpFilter);
  BBTestUdpReadFuncDestPortFilter (BcInterface, StandardLib, LoggingLib, &BcIpFilter);

  // Source IP Filter
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"UdpRead: Source Ip Filter", SctStrLen (L"UdpRead: Source Ip Filter"));
  COPY_IP_FILTER (&BcIpFilter, &BcInterface->Mode->IpFilter);
  BBTestUdpReadFuncSrcIpFilter (BcInterface, StandardLib, LoggingLib, FileHandle, &BcIpFilter);

  // Source Port Filter
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"UdpRead: Source Port Filter", SctStrLen (L"UdpRead: Source Port Filter"));
  COPY_IP_FILTER (&BcIpFilter, &BcInterface->Mode->IpFilter);
  BBTestUdpReadFuncSrcPortFilter (BcInterface, StandardLib, LoggingLib, &BcIpFilter);

  return CloseTestIniFile (ProfileLib, FileHandle);
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Statistics() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.8
//
EFI_STATUS
EFIAPI
BBTestSetIpFilterFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_STATUS                             Status;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_PXE_BASE_CODE_IP_FILTER            BcIpFilter;

  //
  // Get the Standard Library Interface
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             NULL,
             &LoggingLib
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  //
  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Re-init PXE",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  SctSetMem (&BcIpFilter, sizeof (BcIpFilter), 0);
  BcIpFilter.Filters = EFI_PXE_BASE_CODE_IP_FILTER_STATION_IP;
  BcIpFilter.IpCnt = 2;
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[0]), 0x12345678);
  SetIpAddress ((EFI_IP_ADDRESS *)&(BcIpFilter.IpList[1]), 0x87654321);

  Status = BcInterface->SetIpFilter (BcInterface, &BcIpFilter);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid009,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16 *)&BcIpFilter, sizeof(BcIpFilter)/2);
  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16 *)&(BcInterface->Mode->IpFilter), sizeof (BcIpFilter)/2);
  if (TRUE == IsIpFilterEqual (&BcIpFilter, &(BcInterface->Mode->IpFilter))){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid010,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetIpFilter - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

   return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.MCastIpToMac() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.9
//
EFI_STATUS
EFIAPI
BBTestArpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_INI_FILE_HANDLE                    FileHandle;
  EFI_STATUS                             Status;
  EFI_TEST_ASSERTION                     AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface;
  EFI_IP_ADDRESS                         IpAddr;
  EFI_MAC_ADDRESS                        MacAddr;
  EFI_SIMPLE_NETWORK_PROTOCOL            *SnpInterface;

  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             &ProfileLib,
             &LoggingLib
             );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Support Library Failed",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Initialize PXE Protocol",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }


  //
  // Get the interface of the INI file.
  //
  Status = OpenTestIniFile (ProfileLib, &FileHandle);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Instance of INI File",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  // Get IP to be resolved From configuration file
  Status = GetIpAddrFromFile (FileHandle, L"ARP_FUNC", L"IP_Addr", 0, &IpAddr);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get IP from config file",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  Status = gtBS->LocateProtocol (
                   &gBlackBoxEfiSimpleNetworkProtocolGuid,
                   NULL,
                   (VOID **)&SnpInterface
                   );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Get Interface for SNP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  Status = SnpInterface->StationAddress (SnpInterface, TRUE, NULL);
  if (EFI_ERROR(Status)) {
    if (EFI_UNSUPPORTED == Status) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Reset Current MAC",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }

  LOG_BUF_HEX_DFLT (LoggingLib, (CHAR16*)&SnpInterface->Mode->CurrentAddress,
                    3*sizeof (EFI_MAC_ADDRESS)/2);
  //
  // Get IP Address
  //
  SctPrint (L"\r\nSetup DHCP Server\r\n");
  WaitForAnyInput ();
  Status = BcInterface->Dhcp (BcInterface, FALSE);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP - Can't DHCP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  // Call ARP() to get the specified mac
  SctSetMem (&MacAddr, sizeof (MacAddr), 0);
  Status = BcInterface->Arp (BcInterface, &IpAddr, &MacAddr);
  if (EFI_UNSUPPORTED == Status)
  {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.ARP ... Function not support",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    CloseTestIniFile (ProfileLib, FileHandle);
    return Status;
  }
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid011,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Arp - basic - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Print Returned MAC address
  LOG_CHAR16_ASCII_DFLT (LoggingLib, L"Returned MAC", SctStrLen (L"Returned MAC"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(&MacAddr), sizeof (EFI_MAC_ADDRESS)/2);

  SctPrint (L"\r\n Is the returned MAC correct?");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid012,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Arp - basic - Check Returned MAC",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check ArpCachEntries and ArpCache
  Status = PrintArpTable (LoggingLib, BcInterface->Mode);
  if (EFI_ERROR(Status))
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_WARNING,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.Arp - Print ARP Table",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return CloseTestIniFile (ProfileLib, FileHandle);
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.NVData() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.10
//
EFI_STATUS
EFIAPI
BBTestSetParametersFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;
  BOOLEAN                               OrigAutoArp, NewAutoArp;
  UINT8                                 OrigTTL, NewTTL;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  //
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - PXE not enabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Basic Function of SetParameter
  //
  OrigAutoArp = BcInterface->Mode->AutoArp;
  OrigTTL = BcInterface->Mode->TTL;
//  OrigSendGUID = BcInterface->Mode->SendGUID;
//  OrigToS = BcInterface->Mode->ToS;
//  OrigMakeCallback = BcInterface->Mode->MakeCallbacks;

  NewTTL = (UINT8)(OrigTTL + 1);
  if (OrigAutoArp==TRUE) {
    NewAutoArp=FALSE;
  }else {
    NewAutoArp=TRUE;
  }
  /*
  Note: OrigSendGUID, OrigMakeCallback doesn't support in code.

  NewToS = (UINT8)(OrigToS + 1);
  if (OrigSendGUID==TRUE) {
    NewSendGUID=FALSE;
  }else {
    NewSendGUID=TRUE;
  }
  if (OrigMakeCallback==TRUE) {
    NewMakeCallback=FALSE;
  }else {
    NewMakeCallback=TRUE;
  }
  */
  // set new parameters
//  Status = BcInterface->SetParameters (BcInterface, &NewAutoArp, &NewSendGUID, &NewTTL, &NewToS, &NewMakeCallback);
  Status = BcInterface->SetParameters (BcInterface, &NewAutoArp, NULL, &NewTTL, NULL, NULL);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid013,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetParameters - Basic - Check Status Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  /*
      BcInterface->Mode->SendGUID == NewSendGUID        &&
      BcInterface->Mode->ToS == NewToS                  &&
      BcInterface->Mode->MakeCallbacks == NewMakeCallback){
  */
  if (BcInterface->Mode->AutoArp == NewAutoArp          &&
      BcInterface->Mode->TTL == NewTTL){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid014,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetParameters - Basic - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // recover original parameter
//  Status = BcInterface->SetParameters (BcInterface, &OrigAutoArp, &OrigSendGUID, &OrigTTL, &OrigToS, &OrigMakeCallback);
  Status = BcInterface->SetParameters (BcInterface, &OrigAutoArp, NULL, &OrigTTL, NULL, NULL);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetParameters - Recover Original Setting",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  // Disable AutoARP
  NewAutoArp = FALSE;
  Status = BcInterface->SetParameters (BcInterface, &NewAutoArp, NULL, NULL, NULL, NULL);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetParameters - Disable AUTO ARP",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  // Call Mtftp() to get packet from unknown host   TBD
  {
    UINT64 Size;
    UINTN  BlockSize = 512;
    EFI_IP_ADDRESS ServerIp;

    SetIpAddress (&ServerIp, 0x01010101);
    BcInterface->Mtftp (
                   BcInterface,
                   EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE,
                   NULL,
                   FALSE,
                   &Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) "a.txt",
                   NULL,
                   FALSE
                   );
  }
  // Wait for user to see if ARP packet is send.
  SctPrint (L"\r\nIs AutoARP disabled?");

  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid015,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetParameters - Disable Auto ARP",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.GetStatus() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.11
//
EFI_STATUS
EFIAPI
BBTestSetStationIpFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;
  EFI_IP_ADDRESS                        NewStationIp, NewSubnetMask;

  //
  // Get support library (Standard Lib, Profile Lib, Logging Lib)
  //
  Status = GetTestSupportLibrary (
             SupportHandle,
             &StandardLib,
             NULL,
             &LoggingLib
             );
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetStationIp - Get Support Library Failed",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  //
  // Enable EFI_PXE_BASE_CODE_PROTOCOL if needed
  //
  Status = ChangePxeState (BcInterface, FALSE, BcInterface->Mode->Started, TRUE);
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - PXE not enabled",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  // IP address = 192.168.0.1, NetMask = 255.255.255.0
  Status = BBTestSetStationIp (BcInterface, StandardLib, LoggingLib, &NewStationIp,
                              &NewSubnetMask, 0xc0a80001, 0xffffff00);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid016,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetStationIp - Set IP & Mask",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // IP address = 192.168.0.2
  Status = BBTestSetStationIp (BcInterface, StandardLib, LoggingLib, &NewStationIp,
                              NULL, 0xc0a80002, 0);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid017,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetStationIp - Only Set IP",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // NetMask = 255.255.255.240
  Status = BBTestSetStationIp (BcInterface, StandardLib, LoggingLib, NULL,
                              &NewSubnetMask, 0, 0xfffffff0);
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid018,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetStationIp - Only Set Mask",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  return Status;
}

/**
 *  Entrypoint for EFI_PXE_BASE_CODE_PROTOCOL.Transmit() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.12
//
EFI_STATUS
EFIAPI
BBTestSetPacketsFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL              TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  EFI_PXE_BASE_CODE_PROTOCOL           *BcInterface;
  BOOLEAN                               NewDhcpDiscoverValid;
  BOOLEAN                               NewDhcpAckReceived;
  BOOLEAN                               NewProxyOfferReceived ;
  BOOLEAN                               NewPxeDiscoverValid;
  BOOLEAN                               NewPxeReplyReceived;
  BOOLEAN                               NewPxeBisReplyReceived;
  EFI_PXE_BASE_CODE_PACKET             *NewDhcpDiscover=NULL;
  EFI_PXE_BASE_CODE_PACKET             *NewDhcpAck=NULL;
  EFI_PXE_BASE_CODE_PACKET             *NewProxyOffer=NULL;
  EFI_PXE_BASE_CODE_PACKET             *NewPxeDiscover=NULL;
  EFI_PXE_BASE_CODE_PACKET             *NewPxeReply=NULL;
  EFI_PXE_BASE_CODE_PACKET             *NewPxeBisReply=NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Get the EFI_PXE_BASE_CODE_PROTOCOL Protocol interface to be tested
  //
  BcInterface = (EFI_PXE_BASE_CODE_PROTOCOL *)ClientInterface;

  // Re-initialize the EFI_PXE_BASE_CODE_PROTOCOL
  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetPackets - re-initialize PXE(1)",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  // Call Dhcp() function to fill the fields
  SctPrint (L"\r\n Start DHCP Server\n");
  Status = BcInterface->Dhcp (BcInterface, FALSE);
  if (EFI_ERROR(Status)) {
    return Status;
  }
  // Copy fields from current mode
  NewDhcpDiscoverValid = BcInterface->Mode->DhcpDiscoverValid;
  NewDhcpAckReceived = BcInterface->Mode->DhcpAckReceived;
  NewProxyOfferReceived = BcInterface->Mode->ProxyOfferReceived;
  NewPxeDiscoverValid = BcInterface->Mode->PxeDiscoverValid;
  NewPxeReplyReceived = BcInterface->Mode->PxeReplyReceived;
  NewPxeBisReplyReceived = BcInterface->Mode->PxeBisReplyReceived;

  // Allocate Pool for PXE Packet
  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewDhcpDiscover);
  if (EFI_ERROR(Status)){
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewDhcpAck);
  if (EFI_ERROR(Status))
  {
    gtBS->FreePool (NewDhcpDiscover);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewProxyOffer);
  if (EFI_ERROR(Status))
  {
    gtBS->FreePool (NewDhcpDiscover);
    gtBS->FreePool (NewDhcpAck);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewPxeDiscover);
  if (EFI_ERROR(Status))
  {
    gtBS->FreePool (NewDhcpDiscover);
    gtBS->FreePool (NewDhcpAck);
    gtBS->FreePool (NewProxyOffer);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewPxeReply);
  if (EFI_ERROR(Status))
  {
    gtBS->FreePool (NewDhcpDiscover);
    gtBS->FreePool (NewDhcpAck);
    gtBS->FreePool (NewProxyOffer);
    gtBS->FreePool (NewPxeDiscover);
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, sizeof (EFI_PXE_BASE_CODE_PACKET), (VOID **) &NewPxeBisReply);
  if (EFI_ERROR(Status))
  {
    gtBS->FreePool (NewDhcpDiscover);
    gtBS->FreePool (NewDhcpAck);
    gtBS->FreePool (NewProxyOffer);
    gtBS->FreePool (NewPxeDiscover);
    gtBS->FreePool (NewPxeReply);
    return Status;
  }

  CopyPxePacket (NewDhcpDiscover, &BcInterface->Mode->DhcpDiscover);
  CopyPxePacket (NewDhcpAck, &BcInterface->Mode->DhcpAck);
  CopyPxePacket (NewProxyOffer, &BcInterface->Mode->ProxyOffer);
  CopyPxePacket (NewPxeDiscover, &BcInterface->Mode->PxeDiscover);
  CopyPxePacket (NewPxeReply, &BcInterface->Mode->PxeReply);
  CopyPxePacket (NewPxeBisReply, &BcInterface->Mode->PxeBisReply);

  // Re-initialize PXE protocol
  Status = ReInitPxeBaseCode (BcInterface);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.SetPackets - re-initialize PXE(2)",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (NewDhcpDiscover);
    gtBS->FreePool (NewDhcpAck);
    gtBS->FreePool (NewProxyOffer);
    gtBS->FreePool (NewPxeDiscover);
    gtBS->FreePool (NewPxeReply);
    gtBS->FreePool (NewPxeBisReply);
    return Status;
  }

  Status = BcInterface->SetPackets (
                          BcInterface,
                          &NewDhcpDiscoverValid,
                          &NewDhcpAckReceived,
                          &NewProxyOfferReceived,
                          &NewPxeDiscoverValid,
                          &NewPxeReplyReceived,
                          &NewPxeBisReplyReceived,
                          NewDhcpDiscover,
                          NewDhcpAck,
                          NewProxyOffer,
                          NewPxeDiscover,
                          NewPxeReply,
                          NewPxeBisReply
                          );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid019,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetPackets - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Mode
  if (BcInterface->Mode->DhcpDiscoverValid == NewDhcpDiscoverValid              &&
      BcInterface->Mode->DhcpAckReceived == NewDhcpAckReceived                  &&
      BcInterface->Mode->PxeDiscoverValid == NewPxeDiscoverValid                &&
      BcInterface->Mode->PxeReplyReceived == NewPxeReplyReceived                &&
      BcInterface->Mode->ProxyOfferReceived == NewProxyOfferReceived            &&
      BcInterface->Mode->PxeBisReplyReceived == NewPxeReplyReceived             &&
      (TRUE == IsPxePacketEqual (NewDhcpDiscover, &BcInterface->Mode->DhcpDiscover)) &&
      (TRUE == IsPxePacketEqual (NewDhcpAck, &BcInterface->Mode->DhcpAck))      &&
      (TRUE == IsPxePacketEqual (NewProxyOffer, &BcInterface->Mode->ProxyOffer))&&
      (TRUE == IsPxePacketEqual (NewPxeDiscover, &BcInterface->Mode->PxeDiscover))&&
      (TRUE == IsPxePacketEqual (NewPxeReply, &BcInterface->Mode->PxeReply))    &&
      (TRUE == IsPxePacketEqual (NewPxeBisReply, &BcInterface->Mode->PxeBisReply))){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid020,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.SetPackets - Check Mode",
                 L"%a:%d:",
                 __FILE__,
                 (UINTN)__LINE__
                 );

  gtBS->FreePool (NewDhcpDiscover);
  gtBS->FreePool (NewDhcpAck);
  gtBS->FreePool (NewProxyOffer);
  gtBS->FreePool (NewPxeDiscover);
  gtBS->FreePool (NewPxeReply);
  gtBS->FreePool (NewPxeBisReply);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestMtftpGetInfoParam (
  IN EFI_INI_FILE_HANDLE              FileHandle,
  IN EFI_PXE_BASE_CODE_MTFTP_INFO    *Info
  )
{
  EFI_STATUS Status;

  if (NULL == Info)
    return EFI_INVALID_PARAMETER;

  Status = GetIpAddrFromFile (FileHandle, L"MTFTP_INFO", L"MCast_Ip", 0, &(Info->MCastIp));
  if (EFI_ERROR(Status)){
    return Status;
  }

  Status = GetUdpPortFromFile (FileHandle, L"MTFTP_INFO", L"CPort", 0, &(Info->CPort));
  if (EFI_ERROR(Status)){
    return Status;
  }

  Status = GetUdpPortFromFile (FileHandle, L"MTFTP_INFO", L"SPort", 0, &(Info->SPort));
  if (EFI_ERROR(Status)){
    return Status;
  }

  Status = GetUINT16ValFromFile (FileHandle, L"MTFTP_INFO", L"Listen_Timeout", 0, &(Info->ListenTimeout));
  if (EFI_ERROR(Status)){
    return Status;
  }

  return GetUINT16ValFromFile (FileHandle, L"MTFTP_INFO", L"Transmit_Timeout", 0, &(Info->TransmitTimeout));
}

EFI_STATUS
EFIAPI
BBTestTftpGetFileSize (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_INI_FILE_HANDLE                 FileHandle,
  OUT UINTN                             *Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;

  // Get Server IP from Configuration File
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"TFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpGetFileSize: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Read_File_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpGetFileSize: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  // Display Server IP and File Name
  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Server Ip", SctStrLen (L"Server Ip"));
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)&ServerIp, sizeof (EFI_IP_ADDRESS)/2);
  //LOG_IP_HEX_DFLT(LoggingLib, ServerIp.v4.Addr);

  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_TFTP_GET_FILE_SIZE,
                   NULL,
                   FALSE,
                   (UINT64*)Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   NULL,
                   FALSE
                   );
  if (EFI_ERROR(Status)){
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid021,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Get File Size - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // check if the returned file size is correct
  SctPrint (L"\r\nReturned File Len: %d", *Size);
  SctPrint (L"\r\nIs the result is right?");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid022,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Get File Size - Check return value",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Free string, FileName
  SctFreePool (FileName);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestTftpReadFile  (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;
  VOID                           *BufferPtr;
  UINT64                          RetSize;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"TFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpGetFileSize: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Read_File_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, Size, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Allocate Buffer ...... failed",
                   L"Status: \r",
                   Status
                   );
    return Status;
  }

  RetSize = Size - 1;
  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_TFTP_READ_FILE,
                   BufferPtr,
                   FALSE,
                   &RetSize,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   NULL,
                   FALSE
                   );
  if ((Status == EFI_BUFFER_TOO_SMALL) && (RetSize == Size)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid023,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Read File - Not enough buffer",
                 L"%a:%d:Status - %r, Size - %d, RetSize - %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 Size,
                 RetSize
                   );

  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_TFTP_READ_FILE,
                   BufferPtr,
                   FALSE,
                   (UINT64*)&Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   NULL,
                   FALSE
                   );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid024,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Read File - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                   );

  // check if the returned file size is correct
  SctPrint (L"\r\n Check the returned file\n");

  //LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Name", SctStrLen (L"File Name"));
  //LOG_CHAR8_ASCII_DFLT (LoggingLib, FileName, strlen(FileName));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Size", SctStrLen (L"File Size"));
  LOG_UINT32_HEX_DFLT  (LoggingLib, Size);

  SctPrint (L"\r\n Is the returned file correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid025,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Read File - Check file",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  SctFreePool (FileName);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestTftpWriteFile    (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;
  VOID                           *BufferPtr;
  UINTN                           BufferSize;
  UINT64                          Size;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"TFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Write_File_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  // Get Len of Raw Data
  Status = GetUINTNVarFromFile (FileHandle, L"MTFTP_FUNC", L"Raw_Data_Len", 0, &BufferSize);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read Len of Raw Data From config file ...... failed"
                   );
    return Status;
  }
  // Malloc resource for Raw Data
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Malloc for Raw Data ...... failed"
                   );
    return Status;
  }
  // Get Raw Data from config file
  Status = GetRawDataFromFile (FileHandle, L"MTFTP_FUNC", L"Raw_Data", 0, &BufferSize, BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read Raw Data From config file ...... failed"
                   );
    gtBS->FreePool (BufferPtr);
    return Status;
  }

  // Call Mtftp
  Size = (UINT64)BufferSize;
  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_TFTP_WRITE_FILE,
                   BufferPtr,
                   TRUE,
                   (UINT64*)&Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   NULL,
                   FALSE
                   );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid026,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Write File - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  SctPrint (L"\r\n If the file be written to TFTP Server?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid027,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Write File - Check file",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  SctFreePool (FileName);
  // Get Raw Data
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestTftpReadDirectory (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;
  VOID                           *BufferPtr;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"TFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpGetFileSize: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Directory_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, Size, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Allocate Buffer ...... failed",
                   L"Status: \r",
                   Status
                   );
    return Status;
  }
  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_TFTP_READ_DIRECTORY,
                   BufferPtr,
                   FALSE,
                   (UINT64*)Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   NULL,
                   FALSE
                   );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid028,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Read Directory - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                   );

  // check if the returned file size is correct
  SctPrint (L"\r\n Check the returned file\n");

  //LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Directory Name", SctStrLen (L"Directory Name"));
  //LOG_CHAR8_ASCII_DFLT(LoggingLib, FileName, strlen(FileName));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"Size", SctStrLen (L"Size"));
  LOG_UINT32_HEX_DFLT(LoggingLib, Size);

  SctPrint (L"\r\n Is the returned directory correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid029,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - TFTP Read Directory - Check file",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  SctFreePool (FileName);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestMtftpGetFileSize (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  OUT UINTN                                *Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  EFI_PXE_BASE_CODE_MTFTP_INFO    Info;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"MTFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Read_File_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpWriteFile: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  // Get MTFTP Info
  Status = BBTestMtftpGetInfoParam (FileHandle, &Info);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpGetFileSize: Read Mtftp Info From config file ...... failed"
                   );
    return Status;
  }

  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_MTFTP_GET_FILE_SIZE,
                   NULL,
                   FALSE,
                   (UINT64*)Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   &Info,
                   FALSE
                   );
  if (EFI_ERROR(Status)){
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid030,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Get File Size - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_UNSUPPORTED == Status){
    return Status;
  }
  // check if the returned file size is correct
  SctPrint (L"\r\n Len of %s: %d", FileName, *Size);
  SctPrint (L"\r\n Is the result is right?");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid031,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Get File Size - Check return value",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  SctFreePool (FileName);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestMtftpReadFile (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;
  VOID                           *BufferPtr;
  EFI_PXE_BASE_CODE_MTFTP_INFO    Info;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"TFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpGetFileSize: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Read_File_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Read File Name From config file ...... failed"
                   );
    return Status;
  }

  // Get MTFTP Info
  Status = BBTestMtftpGetInfoParam (FileHandle, &Info);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpGetFileSize: Read Mtftp Info From config file ...... failed"
                   );
    return Status;
  }

  // Allocate Pool for receviced file
  Status = gtBS->AllocatePool (EfiBootServicesData, Size, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestTftpReadFile: Allocate Buffer ...... failed",
                   L"Status: \r",
                   Status
                   );
    return Status;
  }

  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_MTFTP_READ_FILE,
                   BufferPtr,
                   FALSE,
                   (UINT64*)Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   &Info,
                   FALSE
                   );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid032,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Read File - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // check if the returned file size is correct
  SctPrint (L"\r\n Check the returned file\n");

  //LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Name", SctStrLen (L"File Name"));
  //LOG_CHAR8_ASCII_DFLT(LoggingLib, FileName, strlen(FileName));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Size", SctStrLen (L"File Size"));
  LOG_UINT32_HEX_DFLT(LoggingLib, Size);

  SctPrint (L"\r\n Is the returned file correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid033,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Read File - Check file",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  SctFreePool (FileName);

  return Status;
}


EFI_STATUS
EFIAPI
BBTestMtftpReadDirectory (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle,
  IN UINTN                                  Size
  )
{
  EFI_TEST_ASSERTION              AssertionType;
  EFI_STATUS                      Status;
  UINTN                           BlockSize = 512;
  EFI_IP_ADDRESS                  ServerIp;
  CHAR8                          *FileName;
  VOID                           *BufferPtr;
  EFI_PXE_BASE_CODE_MTFTP_INFO    Info;

  // Get Server IP Address from configuration file
  Status = GetIpAddrFromFile (FileHandle,  L"MTFTP_FUNC",  L"MTFTP_Server_IP", 0, &ServerIp);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpReadDirectory: Read Server IP From config file ...... failed"
                   );
    return Status;
  }

  // Get File Name from Configuration File
  Status = GetAsciiStringFromFile (FileHandle, L"MTFTP_FUNC", L"Directory_Name", 0, &FileName);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpReadDirectory: Read Directory Name From config file ...... failed"
                   );
    return Status;
  }

  // Get MTFTP Info
  Status = BBTestMtftpGetInfoParam (FileHandle, &Info);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpReadDirectory: Read Mtftp Info From config file ...... failed"
                   );
    return Status;
  }

  // Allocate Pool for receviced file
  Status = gtBS->AllocatePool (EfiBootServicesData, Size, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
  {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"BBTestMtftpReadDirectory: Allocate Buffer ...... failed",
                   L"Status: \r",
                   Status
                   );
    return Status;
  }

  Status = This->Mtftp (
                   This,
                   EFI_PXE_BASE_CODE_MTFTP_READ_DIRECTORY,
                   BufferPtr,
                   FALSE,
                   (UINT64*)Size,
                   &BlockSize,
                   &ServerIp,
                   (UINT8 *) FileName,
                   &Info,
                   FALSE
                   );
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid034,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Read Directory - Check return code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if (EFI_UNSUPPORTED == Status)
    return Status;
  // check if the returned file size is correct
  SctPrint (L"\r\n Check the returned file\n");

  //LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Name", SctStrLen (L"File Name"));
  //LOG_CHAR8_ASCII_DFLT(LoggingLib, FileName, strlen(FileName));

  LOG_CHAR16_ASCII_DFLT(LoggingLib, L"File Size", SctStrLen (L"File Size"));
  LOG_UINT32_HEX_DFLT(LoggingLib, Size);

  // Log MTFTP Info

  SctPrint (L"\r\n Is the returned file correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
    Status = EFI_TFTP_ERROR;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid035,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.Mtftp - MTFTP Read Directory - Check file",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  SctFreePool (FileName);

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpWriteGetConfPara (
  IN EFI_INI_FILE_HANDLE              FileHandle,
  IN EFI_IP_ADDRESS                  *DestIp,
  IN EFI_PXE_BASE_CODE_UDP_PORT      *DestPort,
  IN EFI_IP_ADDRESS                  *GatewayIp,
  IN EFI_IP_ADDRESS                  *SrcIp,
  IN OUT EFI_PXE_BASE_CODE_UDP_PORT  *SrcPort,
  IN UINTN                           *HeaderSize,
  IN VOID                           **HeaderPtr,
  IN UINTN                           *BufferSize,
  IN VOID                           **BufferPtr
  )
{
  EFI_STATUS              Status;
  UINT32                  TempVal;

  // Get Dest Ip
  if (NULL != DestIp)
  {
    NP_Print (L"Get Dest Ip Address\n");
    Status = GetIpAddrFromFile (FileHandle, L"UDPWRITE_FUNC", L"Dest_Ip", 0, DestIp);
    if (EFI_ERROR(Status))
      return Status;
  }

  //Get Dest Port
  if (NULL != DestPort)
  {
    NP_Print (L"Get Dest Port Number\n");
    Status = GetUINT32VarFromFile (FileHandle, L"UDPWRITE_FUNC", L"Dest_Port", 0, &TempVal);
    if (EFI_ERROR(Status))
      return Status;
    *DestPort = (UINT16)TempVal;
  }

  // Get Src Ip
  if (NULL != SrcIp)
  {
    NP_Print (L"Get Src Ip Address\n");
    Status = GetIpAddrFromFile (FileHandle, L"UDPWRITE_FUNC", L"Src_Ip", 0, SrcIp);
    if (EFI_ERROR(Status))
      return Status;
  }

  // Get Src Port
  if (NULL != SrcPort)
  {
    NP_Print (L"Get Src Port Number\n");
    Status = GetUINT32VarFromFile (FileHandle, L"UDPWRITE_FUNC", L"Src_Port", 0, &TempVal);
    if (EFI_ERROR(Status))
      return Status;
    *SrcPort = (UINT16)TempVal;
  }

  // Get Gateway Ip
  if (NULL != GatewayIp)
  {
    NP_Print (L"Get Gateway Ip Address\n");
    Status = GetIpAddrFromFile (FileHandle, L"UDPWRITE_FUNC", L"Src_Ip", 0, GatewayIp);
    if (EFI_ERROR(Status))
      return Status;
  }

  // Get Raw Header
  if (NULL != HeaderSize)
  {
    NP_Print (L"Get Raw Header Len\n");
    Status = GetUINTNVarFromFile (FileHandle, L"UDPWRITE_FUNC", L"Header_Size", 0, HeaderSize);
    if (EFI_ERROR(Status))
      return Status;
    Status = gtBS->AllocatePool (EfiBootServicesData, *HeaderSize, (VOID **) HeaderPtr);
    if (EFI_ERROR(Status))
      return EFI_OUT_OF_RESOURCES;
    Status = GetRawDataFromFile (FileHandle, L"UDPWRITE_FUNC", L"Raw_Header", 0, HeaderSize, (*HeaderPtr));
    if (EFI_ERROR(Status))
      return Status;
  }

  // Get Raw Packet; This param always needed
  NP_Print (L"Get Raw_Date Size\n");
  Status = GetUINTNVarFromFile (FileHandle, L"UDPWRITE_FUNC", L"Packet_Size", 0, BufferSize);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = gtBS->AllocatePool (EfiBootServicesData, *BufferSize, (VOID **) BufferPtr);
  if (EFI_ERROR(Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  NP_Print (L"Get Raw_Date\n");
  Status = GetRawDataFromFile (FileHandle, L"UDPWRITE_FUNC", L"Raw_Packet", 0, BufferSize, (*BufferPtr));
  if (EFI_ERROR(Status)){
    return Status;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncThrGateway (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
{
  EFI_STATUS                        Status;
  EFI_TEST_ASSERTION                AssertionType;
  EFI_IP_ADDRESS                    DestIp;
  EFI_PXE_BASE_CODE_UDP_PORT        DestPort;
  EFI_IP_ADDRESS                    GatewayIp;
  UINTN                             BufferSize;
  VOID                             *BufferPtr;

  Status = BBTestUdpWriteGetConfPara (FileHandle, &DestIp, &DestPort, &GatewayIp, NULL, NULL, NULL, NULL, &BufferSize, &BufferPtr);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.BBTestUdpWriteFuncThrGateway - Get Para ",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = This->UdpWrite (This, 0, &DestIp, &DestPort, &GatewayIp, NULL, NULL, NULL, NULL, &BufferSize, BufferPtr);

  // Check Return Code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid036,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Thr Gateway - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // User Check the actually sent packet
  SctPrint (L"\r\n Please Check the actually sent packet\n");
  SctPrint (L"\r Is the packet correct\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid037,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Thr Gateway - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}


EFI_STATUS
EFIAPI
BBTestUdpWriteFuncPrependHeader (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
{
  EFI_STATUS                     Status;
  EFI_TEST_ASSERTION             AssertionType;
  EFI_IP_ADDRESS                 DestIp;
  EFI_PXE_BASE_CODE_UDP_PORT     DestPort;
  UINTN                          HeaderSize;
  VOID                          *HeaderPtr;
  UINTN                          BufferSize;
  VOID                          *BufferPtr;

  Status = BBTestUdpWriteGetConfPara (FileHandle, &DestIp, &DestPort, NULL, NULL, NULL,
                &HeaderSize, &HeaderPtr, &BufferSize, &BufferPtr);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.BBTestUdpWriteFuncBasic - Get Para ",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = This->UdpWrite (This, 0, &DestIp, &DestPort, NULL, NULL, NULL, &HeaderSize, HeaderPtr, &BufferSize, BufferPtr);

  // Check Return Code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid038,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Prepend Header - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // User Check the actually sent packet
  SctPrint (L"\r\n Please Check the actually sent packet\n");
  SctPrint (L"\r Is the packet correct\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid039,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Prepend Header - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpWriteFuncFrag (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
{
  EFI_STATUS                         Status;
  EFI_TEST_ASSERTION                 AssertionType;
  UINT16                             OpFlags;
  EFI_IP_ADDRESS                     DestIp;
  EFI_PXE_BASE_CODE_UDP_PORT         DestPort;
  UINTN                              BufferSize;
  VOID                              *BufferPtr;

  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_MAY_FRAGMENT;

  Status = BBTestUdpWriteGetConfPara (FileHandle, &DestIp, &DestPort, NULL, NULL, NULL, NULL, NULL, &BufferSize, &BufferPtr);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.BBTestUdpWriteFuncBasic - Get Para ",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = This->UdpWrite (This, OpFlags, &DestIp, &DestPort, NULL, NULL, NULL, NULL, NULL, &BufferSize, BufferPtr);

  // Check Return Code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid040,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Frag - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // User Check the actually sent packet
  SctPrint (L"\r\n Please Check the actually sent packet\n");
  SctPrint (L"\r Is the packet correct\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid041,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Frag - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}


EFI_STATUS
EFIAPI
BBTestUdpWriteFuncBasic (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL    *ProfileLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_INI_FILE_HANDLE                    FileHandle
  )
{
  EFI_STATUS                  Status;
  EFI_TEST_ASSERTION          AssertionType;
  UINT16                      OpFlags;
  EFI_IP_ADDRESS              DestIp;
  EFI_PXE_BASE_CODE_UDP_PORT  DestPort;
  UINTN                       BufferSize;
  VOID                       *BufferPtr;

  OpFlags = 0;

  Status = BBTestUdpWriteGetConfPara (FileHandle, &DestIp, &DestPort, NULL, NULL,
                                      NULL, NULL, NULL, &BufferSize, &BufferPtr);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.BBTestUdpWriteFuncBasic - Get Para ",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = This->UdpWrite (This, OpFlags, &DestIp, &DestPort, NULL, NULL, NULL,
                          NULL, NULL, &BufferSize, BufferPtr);

  // Check Return Code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid042,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Basic - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // User Check the actually sent packet
  SctPrint (L"\r\n Please Check the actually sent packet\n");
  SctPrint (L"\r Is the packet correct\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid043,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpWrite - Basic - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return Status;
}


EFI_STATUS
EFIAPI
BBTestSetStationIp (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *This,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_IP_ADDRESS                     *NewStationIp,
  IN EFI_IP_ADDRESS                     *NewSubnetMask,
  IN UINT32                              Ipv4,
  IN UINT32                              Mask
  )
{
  EFI_STATUS                  Status;
  EFI_IP_ADDRESS              OldStationIp, OldSubnetMask;

  Status = SetIpAndMask (NewStationIp, NewSubnetMask, Ipv4, Mask);
  if (EFI_ERROR(Status)){
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"EFI_PXE_BASE_CODE_PROTOCOL.BBTestSetStationIp - Fill Para ",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  Status = This->SetStationIp (This, NewStationIp, NewSubnetMask);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  SctCopyMem (&OldStationIp, &(This->Mode->StationIp), sizeof (EFI_IP_ADDRESS));
  SctCopyMem (&OldSubnetMask, &(This->Mode->SubnetMask), sizeof (EFI_IP_ADDRESS));

  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(&OldStationIp), sizeof (EFI_IP_ADDRESS)/2);
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)NewStationIp, sizeof (EFI_IP_ADDRESS)/2);

  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)(&OldSubnetMask), sizeof (EFI_IP_ADDRESS)/2);
  LOG_BUF_HEX_DFLT(LoggingLib, (CHAR16*)NewSubnetMask, sizeof (EFI_IP_ADDRESS)/2);

  if (TRUE == IsIpMaskEqual (NewStationIp, NewSubnetMask, &OldStationIp, &OldSubnetMask))
    return EFI_SUCCESS;

  return EFI_INVALID_PARAMETER;//shouldn't be this value
}

EFI_STATUS
EFIAPI
BBTestUdpReadFuncBasic (
  IN EFI_PXE_BASE_CODE_PROTOCOL          *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL   *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER         *OrigIpFilter
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                OpFlags;
  EFI_PXE_BASE_CODE_UDP_PORT            DestPort;
  EFI_IP_ADDRESS                        SrcIp;
  EFI_PXE_BASE_CODE_UDP_PORT            SrcPort;
  UINTN                                 BufferSize;
  VOID                                 *BufferPtr;

  //Wait for user send packet
  SctPrint (L"\r\nSend UDP Packet to this host\n");
  WaitForAnyInput ();

  // Malloc for data
  BufferSize = MAX_UDP_SIZE;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
    return EFI_OUT_OF_RESOURCES;

  BufferSize = 0;
  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;

  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          NULL,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid044,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - EFI_BUFFER_TOO_SMALL",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check BufferSize
  SctPrint (L"\r\nBufferSize=%d, is the returned BufferSize correct?\n", BufferSize);
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid045,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - The returned BufferSize is correct",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Set OPFLAGS TO Let filter
  BufferSize = MAX_UDP_SIZE;
  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;

  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          NULL,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );
  // Check Return Status Code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid046,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Basic - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //Display Dst Port, Src Ip, Src Port
  if (EFI_ERROR(Status))
    BufferSize = 0;
  LogUdpPacket (LoggingLib, NULL, &DestPort, &SrcIp, &SrcPort, BufferSize, BufferPtr);
  // Check Packet
  SctPrint (L"\r\nIs the received Packet correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid047,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Basic - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check if IPFilter changed
  if (TRUE==IsIpFilterEqual (OrigIpFilter, &(BcInterface->Mode->IpFilter)))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid048,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Basic - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  gtBS->FreePool (BufferPtr);
  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpReadFuncDesIpFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER        *OrigIpFilter
)
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                OpFlags;
  EFI_PXE_BASE_CODE_UDP_PORT            DestPort;
  EFI_IP_ADDRESS                        SrcIp;
  EFI_PXE_BASE_CODE_UDP_PORT            SrcPort;
  UINTN                                 BufferSize;
  VOID                                 *BufferPtr;

  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_DEST_PORT;

  // Malloc for data
  BufferSize = MAX_UDP_SIZE;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
    return EFI_OUT_OF_RESOURCES;

  // Send UDP Packet dest for this host
  SctPrint (L"\r\nSend UDP packet to this host\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );


  // Send UDP Packet dest for other host
  SctPrint (L"\r\nSend UDP packet to other host\n");
  WaitForAnyInput ();

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid049,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest IP filter(1) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check packet
  if (EFI_ERROR(Status)){
    BufferSize = 0;
  }
  LogUdpPacket (LoggingLib, NULL, &DestPort, &SrcIp, &SrcPort, BufferSize, BufferPtr);
  SctPrint (L"\r\nIs the received Packet correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid050,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest Ip Filter (1) - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Mode
  if (TRUE==IsIpFilterEqual (OrigIpFilter, &(BcInterface->Mode->IpFilter)))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid051,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest IP filter(1) - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid052,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest IP filter(2) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpReadFuncDestPortFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER        *OrigIpFilter
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                OpFlags;
  EFI_PXE_BASE_CODE_UDP_PORT            DestPort;
  EFI_IP_ADDRESS                        SrcIp;
  EFI_PXE_BASE_CODE_UDP_PORT            SrcPort;
  UINTN                                 BufferSize;
  VOID                                 *BufferPtr;

  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;
  DestPort = 69;

  // Malloc for data
  BufferSize = MAX_UDP_SIZE;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
    return EFI_OUT_OF_RESOURCES;

  // Send UDP Packet dest for this host
  SctPrint (L"\r\nSend UDP packet to this host:80\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );


  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid053,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest Port filter(1) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check packet
  if (EFI_ERROR(Status)){
    BufferSize = 0;
  }
  LogUdpPacket (LoggingLib, NULL, NULL, &SrcIp, &SrcPort, BufferSize, BufferPtr);
  SctPrint (L"\r\nIs the received Packet correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid054,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest Port Filter (1) - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Mode
  if (TRUE==IsIpFilterEqual (OrigIpFilter, &(BcInterface->Mode->IpFilter))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid055,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest IP filter(1) - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Send UDP Packet dest for this host, port 69
  SctPrint (L"\r\nSend UDP packet to this host:69\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid056,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Dest Port filter(2) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpReadFuncSrcIpFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL         *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL  *LoggingLib,
  IN EFI_INI_FILE_HANDLE                 FileHandle,
  IN EFI_PXE_BASE_CODE_IP_FILTER        *OrigIpFilter
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                OpFlags;
  EFI_PXE_BASE_CODE_UDP_PORT            DestPort;
  EFI_IP_ADDRESS                        SrcIp;
  EFI_PXE_BASE_CODE_UDP_PORT            SrcPort;
  UINTN                                 BufferSize;
  VOID                                 *BufferPtr;

  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;

  Status = GetIpAddrFromFile (FileHandle, L"UDPREAD_FUNC", L"Filter_Src_Ip", 0, &SrcIp);
  if (EFI_ERROR(Status))
    return Status;

  // Malloc for data
  BufferSize = MAX_UDP_SIZE;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status))
    return EFI_OUT_OF_RESOURCES;

  // Send UDP Packet dest for this host
  SctPrint (L"\r\nSend UDP packet from allowed host\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid057,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Ip filter(1) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check packet
  if (EFI_ERROR(Status)){
    BufferSize = 0;
  }
  LogUdpPacket (LoggingLib, NULL, &DestPort, NULL, &SrcPort, BufferSize, BufferPtr);
  SctPrint (L"\r\nIs the received Packet correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid058,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Ip Filter (1) - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Mode
  if (TRUE==IsIpFilterEqual (OrigIpFilter, &(BcInterface->Mode->IpFilter)))
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  else
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid059,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Ip filter(1) - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Send UDP Packet dest for this host, port 69
  SctPrint (L"\r\nSend UDP packet from unallowed host\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid060,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Ip filter(2) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  return Status;
}

EFI_STATUS
EFIAPI
BBTestUdpReadFuncSrcPortFilter (
  IN EFI_PXE_BASE_CODE_PROTOCOL            *BcInterface,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  IN EFI_TEST_LOGGING_LIBRARY_PROTOCOL     *LoggingLib,
  IN EFI_PXE_BASE_CODE_IP_FILTER           *OrigIpFilter
  )
{
  EFI_STATUS                            Status;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT16                                OpFlags;
  EFI_PXE_BASE_CODE_UDP_PORT            DestPort;
  EFI_IP_ADDRESS                        SrcIp;
  EFI_PXE_BASE_CODE_UDP_PORT            SrcPort;
  UINTN                                 BufferSize;
  VOID                                 *BufferPtr;

  OpFlags = EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_IP |
            EFI_PXE_BASE_CODE_UDP_OPFLAGS_ANY_SRC_PORT;
  SrcPort = 69;

  // Malloc for data
  BufferSize = MAX_UDP_SIZE;
  Status = gtBS->AllocatePool (EfiBootServicesData, BufferSize, (VOID **) &BufferPtr);
  if (EFI_ERROR(Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Send UDP Packet dest for this host
  SctPrint (L"\r\nSend UDP packet (src_port = 80)\n");
  WaitForAnyInput ();

  // Call UdpRead () to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid061,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Port filter(1) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check packet
  if (EFI_ERROR(Status)){
    BufferSize = 0;
  }
  LogUdpPacket (LoggingLib, NULL, &DestPort, &SrcIp, NULL, BufferSize, BufferPtr);
  SctPrint (L"\r\nIs the received Packet correct?\n");
  if (TRUE == WaitForUserCheck ()){
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid062,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Port Filter (1) - Check Packet",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Check Mode
  if (TRUE==IsIpFilterEqual (OrigIpFilter, &(BcInterface->Mode->IpFilter))) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid063,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Port filter(1) - Check Mode",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  // Send UDP Packet dest for this host, port 69
  SctPrint (L"\r\nSend UDP packet (src_port = 69)\n");
  WaitForAnyInput ();

  // Call UdpRead() to read UDP Packet
  Status = BcInterface->UdpRead (
                          BcInterface,
                          OpFlags,
                          &BcInterface->Mode->StationIp,
                          &DestPort,
                          &SrcIp,
                          &SrcPort,
                          NULL,
                          NULL,
                          &BufferSize,
                          BufferPtr
                          );

  // Check return code
  if (Status == EFI_SUCCESS) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gPxeBaseCodeBBTestFunctionAssertionGuid064,
                 L"EFI_PXE_BASE_CODE_PROTOCOL.UdpRead - Src Port filter(2) - Check Return Code",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->FreePool (BufferPtr);
  return Status;
}
