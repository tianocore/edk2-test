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
    IPsec2BBTestConformance.c

Abstract:
    for EFI Driver IPsec2 Protocol's conformance Test

--*/
#include "SctLib.h"
#include "IPsec2BBTestMain.h"

EFI_STATUS
EFIAPI
BBTestProcessExtConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  );
 
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestProcessExtConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC2_PROTOCOL                   *IPsec2 = NULL;
  EFI_IPSEC_CONFIG_PROTOCOL             *IpSecConf = NULL;
  EFI_IP4_HEADER                        *Ip4Head = NULL;


  //
  // init
  //
  IPsec2 = (EFI_IPSEC2_PROTOCOL*)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  //
  // Open IPSEC_CONFIG_PROTOCOL
  //
  SctLocateProtocol(
    &gBlackBoxEfiIPsecConfigProtocolGuid,
    (VOID**) &IpSecConf
    );

  if (IpSecConf != NULL) {
  
     
    //
    // Config SPD/SAD through IPSEC_CONFIG_PROTOCOL 
    //
    //
    // Initialize IP Sec Configuration Data
    //
    Ip4Head = (EFI_IP4_HEADER *)Ip4Packet;
    Ip4InitIPsecConfigDataTransport (Ip4Head);  

    //
    // OutBound SPD
    //    
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          &OutBoundSpdIp4Transport,
                          NULL
                          );

    //
    // OutBound SAD
    // 
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSad,
                          &OutBoundSadSelectorIp4Transport,
                          &OutBoundSadIp4Transport,
                          NULL
                          );
    //
    //Call check points 1
    //
    BBTestProcessExtConformanceTestCheckpoint1( StandardLib, IPsec2);

    //
    // Remove SPD/SAD configuration through IPSEC_CONFIG_PROTOCOL
    //
    Status = IpSecConf->SetData(
                          IpSecConf,
                          IPsecConfigDataTypeSpd,
                          &OutBoundSpdSelectorIp4Transport,
                          NULL,
                          NULL
                          );


  }
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestProcessExtConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC2_PROTOCOL                        *IPsec2
  )
{  
  EFI_STATUS                           Status;  
  EFI_TEST_ASSERTION                   AssertionType;
  EFI_EVENT                            RecycleEvent = NULL;
  EFI_IP4_HEADER                       *Ip4Head = NULL;
  UINT8                                *OptionsBuffer = NULL;
  UINT32                               OptionLen;
  EFI_IPSEC_FRAGMENT_DATA              *FragmentTable = NULL;
  UINT32                               FragmentCount;
  EFI_IPSEC_FRAGMENT_DATA              *OriginalFragmentTable = NULL;
  EFI_HANDLE                           *NicHandleBuffer = NULL;
  UINTN                                NoHandles;
  UINTN                                i;
  UINT8                                *Ip4PacketTemp = NULL;
  
  //
  // Allocate a NIC handle  which has Udp4 service binding protocol installed
  // IPSEC2.ProcessExt may need Upd4/Udp6 in ike negotiation process
  // 
  Status = gtBS->LocateHandleBuffer(
                   ByProtocol, 
                   &gBlackBoxEfiUdp4ServiceBindingProtocolGuid, 
                   NULL, 
                   &NoHandles,
                   &NicHandleBuffer
                   );
  if (Status != EFI_SUCCESS) {
    
    goto FUNC_EXIT; 
  }

  //
  // Create a temp Ip4 packet buffer for test 
  // to make sure orignal test patten unchanged 
  //
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Ip4PacketSize, 
                   (VOID **)&Ip4PacketTemp
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"AllocatePool - Allocate IP4 Packet space for testing",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto FUNC_EXIT;
  }
  SctCopyMem (Ip4PacketTemp, Ip4Packet, Ip4PacketSize);
  
  // Create One IP4 Packet comprise of {IP4Head, OptionBuffer, FragmentTable}
  //
  Status = IP4ProcessPacket(
             StandardLib, 
             Ip4PacketTemp, 
             Ip4PacketSize,
             &Ip4Head, 
             (VOID**) &OptionsBuffer,
             &OptionLen,
             &FragmentTable, 
             &FragmentCount
             );

  if (Status != EFI_SUCCESS) {
    goto FUNC_EXIT; 
  }
  
  for (i = 0; i < NoHandles; i++) {
    //
    // Save Fragment Table address, Since ProcessExt will change its value 
    // 
    OriginalFragmentTable = FragmentTable;

    //
    // Null OptionsBuffer Input
    // 
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) NULL,
                       &OptionLen,
                       &FragmentTable,
                       &FragmentCount,
                       EfiIPsecOutBound,
                       &RecycleEvent
                       );
    
    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestConformanceAssertionGuid001,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Null OptionsBuffer Input",
                   L"%a:%d:Status=%r Expected Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );
    if (OriginalFragmentTable != FragmentTable) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = OriginalFragmentTable;
    }

    
    //
    // Null OptionsLength Input
    // 
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       NULL,
                       &FragmentTable,
                       &FragmentCount,
                       EfiIPsecOutBound,
                       &RecycleEvent
                       );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestConformanceAssertionGuid002,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Null OptionsLength Input",
                   L"%a:%d:Status=%r Expected Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );

    if (OriginalFragmentTable != FragmentTable) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = OriginalFragmentTable;
    }
  
    //
    // NULL FragmentTable Input
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       NULL,
                       &FragmentCount,
                       EfiIPsecOutBound,
                       &RecycleEvent
                       );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestConformanceAssertionGuid003,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Null FragmentTable Input",
                   L"%a:%d:Status=%r Expected Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );

    //
    // NULL FragmentCount Input
    //
    Status = IPsec2->ProcessExt (
                       IPsec2,
                       NicHandleBuffer[i],
                       IP_VERSION_4,
                       Ip4Head,
                       &(Ip4Head->Protocol),
                       (VOID **) &OptionsBuffer,
                       &OptionLen,
                       &FragmentTable,
                       NULL,
                       EfiIPsecOutBound,
                       &RecycleEvent
                       );

    if (Status == EFI_INVALID_PARAMETER) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIpSec2BBTestConformanceAssertionGuid004,
                   L"EFI_IPSEC2_PROTOCOL.ProcessExt - Null FragmentCount Input",
                   L"%a:%d:Status=%r Expected Status=%r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   EFI_INVALID_PARAMETER
                   );

    if (OriginalFragmentTable != FragmentTable) {
      gtBS->FreePool (FragmentTable);
      FragmentTable = OriginalFragmentTable;
    }
  }


FUNC_EXIT:

  //
  // Free all allocated resources 
  //
  if (Ip4Head != NULL) {
    gtBS->FreePool (Ip4Head);
  }

  if (OptionsBuffer != NULL) {
    gtBS->FreePool (OptionsBuffer);
  }

  if (OriginalFragmentTable != NULL) {
    gtBS->FreePool (OriginalFragmentTable);
  }

  if (Ip4PacketTemp != NULL) {
    gtBS->FreePool (Ip4PacketTemp);
  }
  
  if (NicHandleBuffer != NULL) {
    gtBS->FreePool (NicHandleBuffer);
  }

 

  
  return EFI_SUCCESS;
}
