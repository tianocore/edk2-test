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
    IPsecConfigBBTestConformance.c

Abstract:
    for EFI Driver IPsec Config Protocol's conformance Test

--*/
#include "SctLib.h"
#include "IPsecConfigBBTestMain.h"


EFI_STATUS
EFIAPI
BBTestSetDataConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );


EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );  
  
//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC_CONFIG_PROTOCOL             *IPsecConfig;

  //
  // init
  //
  IPsecConfig = (EFI_IPSEC_CONFIG_PROTOCOL*)ClientInterface;

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
  //Call check points
  //
  BBTestSetDataConformanceTestCheckpoint1( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC_CONFIG_PROTOCOL             *IPsecConfig;

  //
  // init
  //
  IPsecConfig = (EFI_IPSEC_CONFIG_PROTOCOL*)ClientInterface;

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
  //Call check points
  //
  BBTestGetDataConformanceTestCheckpoint1( StandardLib, IPsecConfig );
  
  BBTestGetDataConformanceTestCheckpoint2( StandardLib, IPsecConfig );
  
  BBTestGetDataConformanceTestCheckpoint3( StandardLib, IPsecConfig );

  BBTestGetDataConformanceTestCheckpoint4( StandardLib, IPsecConfig );
  
  BBTestGetDataConformanceTestCheckpoint5( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC_CONFIG_PROTOCOL             *IPsecConfig;

  //
  // init
  //
  IPsecConfig = (EFI_IPSEC_CONFIG_PROTOCOL*)ClientInterface;

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
  //Call check points
  //
  BBTestGetNextSelectorConformanceTestCheckpoint1( StandardLib, IPsecConfig );
  
  BBTestGetNextSelectorConformanceTestCheckpoint2( StandardLib, IPsecConfig );

  BBTestGetNextSelectorConformanceTestCheckpoint3( StandardLib, IPsecConfig );

  BBTestGetNextSelectorConformanceTestCheckpoint4( StandardLib, IPsecConfig );

  BBTestGetNextSelectorConformanceTestCheckpoint5( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC_CONFIG_PROTOCOL             *IPsecConfig;

  //
  // init
  //
  IPsecConfig = (EFI_IPSEC_CONFIG_PROTOCOL*)ClientInterface;

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
  //Call check points
  //
  BBTestRegisterDataNotifyConformanceTestCheckpoint1( StandardLib, IPsecConfig );
  
  BBTestRegisterDataNotifyConformanceTestCheckpoint2( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_STATUS                            Status;
  EFI_IPSEC_CONFIG_PROTOCOL             *IPsecConfig;

  //
  // init
  //
  IPsecConfig = (EFI_IPSEC_CONFIG_PROTOCOL*)ClientInterface;

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
  //Call check points
  //
  BBTestUnregisterDataNotifyConformanceTestCheckpoint1( StandardLib, IPsecConfig );
  
  BBTestUnregisterDataNotifyConformanceTestCheckpoint2( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestSetDataConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_SPD_SELECTOR        Selector;
  EFI_IPSEC_SPD_DATA            Data;
  EFI_IPSEC_PROCESS_POLICY      ProcessingPolicy;
  EFI_IP_ADDRESS_INFO           LocalAddress;
  EFI_IP_ADDRESS_INFO           RemoteAddress;
  
  DataType = IPsecConfigDataTypeMaximum;

  LocalAddress.PrefixLength = 0x20;
  LocalAddress.Address.v4.Addr[0] = 192;
  LocalAddress.Address.v4.Addr[1] = 168;
  LocalAddress.Address.v4.Addr[2] = 200;
  LocalAddress.Address.v4.Addr[3] = 101;
  RemoteAddress.PrefixLength = 0x20;
  RemoteAddress.Address.v4.Addr[0] = 192;
  RemoteAddress.Address.v4.Addr[1] = 168;
  RemoteAddress.Address.v4.Addr[2] = 200;
  RemoteAddress.Address.v4.Addr[3] = 1;
  
  Selector.LocalAddress = &LocalAddress;
  Selector.LocalAddressCount = 1;
  Selector.RemoteAddress = &RemoteAddress;
  Selector.RemoteAddressCount = 1;
  Selector.NextLayerProtocol = 0x11;
  Selector.LocalPort = 0x010e;
  Selector.LocalPortRange = 0;
  Selector.RemotePort = 0x010e;
  Selector.RemotePortRange = 0;

  ProcessingPolicy.ExtSeqNum = FALSE;
  ProcessingPolicy.SeqOverflow = FALSE;
  ProcessingPolicy.FragCheck = FALSE;
  ProcessingPolicy.SaLifetime.ByteCount = 0;
  ProcessingPolicy.SaLifetime.SoftLifetime = 0;
  ProcessingPolicy.SaLifetime.HardLifetime = 0;
  ProcessingPolicy.Mode = EfiIPsecTransport;
  ProcessingPolicy.TunnelOption = NULL;
  ProcessingPolicy.Proto = EfiIPsecESP;
  ProcessingPolicy.Proto = IKE_AALG_SHA1HMAC;
  ProcessingPolicy.Proto = IKE_EALG_3DESCBC;

  Data.PackageFlag = 0x0;
  Data.TrafficDirection = EfiIPsecInBound;
  Data.Action = EfiIPsecActionProtect;
  Data.ProcessingPolicy = &ProcessingPolicy;
  Data.SaIdCount = 1;
  Data.SaId[0].Spi = 0;
  Data.SaId[0].Proto = 0;
  Data.SaId[0].DestAddress.v4.Addr[0] = 0;
  Data.SaId[0].DestAddress.v4.Addr[1] = 0;
  Data.SaId[0].DestAddress.v4.Addr[2] = 0;
  Data.SaId[0].DestAddress.v4.Addr[3] = 0;
  //
  // Call SetData with an invalid DataType (>2) 
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          IPsecConfigDataTypeMaximum,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );

  if ( EFI_UNSUPPORTED != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid001,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_UNSUPPORTED with an invalid DataType (>2).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  UINTN                         DataSize;
  CHAR8                         Data[1000];         


  DataSize = 1000;

  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++) {
    //
    // Call GetData with NULL Selector 
    //
    Status = IPsecConfig->GetData(
                            IPsecConfig,
                            DataType,
                            NULL,
                            &DataSize,
                            Data
                            );


    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid002,
                   L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL Selector.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  UINTN                         DataSize;
  CHAR8                         Data[1000];        
  EFI_IPSEC_CONFIG_SELECTOR     Selector;

  DataSize = 1000;
  DataType = IPsecConfigDataTypeMaximum;
  //
  // Call GetData with invalid DataType(>2) 
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          &Selector,
                          &DataSize,
                          Data
                          );


  if ( EFI_UNSUPPORTED != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid003,
                   L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_UNSUPPORTED with invalid DataType(>2).",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_SPD_SELECTOR        Selector;
  UINTN                         DataSize;
  EFI_IPSEC_SPD_DATA            Data;

  EFI_IP_ADDRESS_INFO         LocalAddress;
  EFI_IP_ADDRESS_INFO         RemoteAddress;
  EFI_IPSEC_PROCESS_POLICY    ProcessingPolicy;


  LocalAddress.PrefixLength = 0x20;
  LocalAddress.Address.v4.Addr[0] = 192;
  LocalAddress.Address.v4.Addr[1] = 168;
  LocalAddress.Address.v4.Addr[2] = 200;
  LocalAddress.Address.v4.Addr[3] = 101;
  RemoteAddress.PrefixLength = 0x20;
  RemoteAddress.Address.v4.Addr[0] = 192;
  RemoteAddress.Address.v4.Addr[1] = 168;
  RemoteAddress.Address.v4.Addr[2] = 200;
  RemoteAddress.Address.v4.Addr[3] = 1;

  DataType = IPsecConfigDataTypeSpd;

  Selector.LocalAddressCount = 1;                
  Selector.LocalAddress = &LocalAddress;
  Selector.RemoteAddressCount = 1;                
  Selector.RemoteAddress = &RemoteAddress;
  Selector.NextLayerProtocol = 0x11;             
  Selector.LocalPort = 0x010e;           
  Selector.LocalPortRange = 0;                
  Selector.RemotePort = 0x010e;           
  Selector.RemotePortRange = 0;                

  ProcessingPolicy.ExtSeqNum = FALSE;
  ProcessingPolicy.SeqOverflow = FALSE;
  ProcessingPolicy.FragCheck = FALSE;
  ProcessingPolicy.SaLifetime.ByteCount = 0;
  ProcessingPolicy.SaLifetime.SoftLifetime = 0;
  ProcessingPolicy.SaLifetime.HardLifetime = 0;
  ProcessingPolicy.Mode = EfiIPsecTransport;
  ProcessingPolicy.TunnelOption = 0;
  ProcessingPolicy.Proto = EfiIPsecESP;
  ProcessingPolicy.AuthAlgoId = IKE_AALG_SHA1HMAC;
  ProcessingPolicy.EncAlgoId = IKE_EALG_3DESCBC;

  Data.PackageFlag = 0x0;
  Data.TrafficDirection = EfiIPsecInBound;
  Data.Action = EfiIPsecActionProtect;
  Data.ProcessingPolicy = &ProcessingPolicy;
  Data.SaIdCount = 1;
  Data.SaId[0].Spi = 0;
  Data.SaId[0].Proto = EfiIPsecESP;
  Data.SaId[0].DestAddress.v4.Addr[0] = 0;
  Data.SaId[0].DestAddress.v4.Addr[1] = 0;
  Data.SaId[0].DestAddress.v4.Addr[2] = 0;
  Data.SaId[0].DestAddress.v4.Addr[3] = 0;

  DataSize = 1000;

  //
  // Prepare Environment: Call SetData with valid DataType(0)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(0)/Selector/Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  //
  // CheckPoint 1: Call GetData with the same DataType(0)/Selector and NULL Data.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          NULL
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid004,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 2: Call GetData with the same DataType(0)/Selector and NULL DataSize.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          &Data
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid005,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 3: Call GetData with the same DataType(0)/Selector, non-NULL Data and small DataSize.
  //
  DataSize = 10;

  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          &Data
                          );


  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid006,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_BUFFER_TOO_SMALL with small DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(0)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(0)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_SA_ID               Selector;
  UINTN                         DataSize;
  EFI_IPSEC_SA_DATA             Data;
  EFI_IPSEC_SA_DATA2            Data2;

  EFI_IP_ADDRESS_INFO         LocalAddress;
  EFI_IP_ADDRESS_INFO         RemoteAddress;
  EFI_IPSEC_SPD_SELECTOR      SpdSelector;


  CHAR8  EncKey[128]; 
  CHAR8  AuthKey[128];


  Selector.Spi = 0;
  Selector.Proto = EfiIPsecESP;
  Selector.DestAddress.v4.Addr[0] = 192;
  Selector.DestAddress.v4.Addr[1] = 168;
  Selector.DestAddress.v4.Addr[2] = 88;
  Selector.DestAddress.v4.Addr[3] = 1;

  LocalAddress.PrefixLength = 0x20;
  LocalAddress.Address.v4.Addr[0] = 192;
  LocalAddress.Address.v4.Addr[1] = 168;
  LocalAddress.Address.v4.Addr[2] = 88;
  LocalAddress.Address.v4.Addr[3] = 1;
  RemoteAddress.PrefixLength = 0x20;
  RemoteAddress.Address.v4.Addr[0] = 192;
  RemoteAddress.Address.v4.Addr[1] = 168;
  RemoteAddress.Address.v4.Addr[2] = 88;
  RemoteAddress.Address.v4.Addr[3] = 2;

  DataType = IPsecConfigDataTypeSad;

  SpdSelector.LocalAddressCount = 1;                
  SpdSelector.LocalAddress = &LocalAddress;
  SpdSelector.RemoteAddressCount = 1;                
  SpdSelector.RemoteAddress = &RemoteAddress;
  SpdSelector.NextLayerProtocol = 0x11;             
  SpdSelector.LocalPort = 0x010e;           
  SpdSelector.LocalPortRange = 0;                
  SpdSelector.RemotePort = 0x010e;           
  SpdSelector.RemotePortRange = 0;                

  Data.Mode = EfiIPsecTransport;
  Data.SNCount = 0;
  Data.AntiReplayWindows = 0;
  Data.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  Data.AlgoInfo.EspAlgoInfo.EncKeyLength = 128;
  Data.AlgoInfo.EspAlgoInfo.EncKey = EncKey;
  Data.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  Data.AlgoInfo.EspAlgoInfo.AuthKeyLength = 128;
  Data.AlgoInfo.EspAlgoInfo.AuthKey = AuthKey;
  Data.SaLifetime.ByteCount = 0;
  Data.SaLifetime.SoftLifetime = 0;
  Data.SaLifetime.HardLifetime = 0;
  Data.PathMTU = 1000;
  Data.SpdSelector = &SpdSelector;
  Data.ManualSet = FALSE;


  DataSize = 1000;

  //
  // Call SetData with valid DataType(1)/Selector/SA_DATA.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/SA_DATA fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  //
  // CheckPoint 1: Call GetData with the same DataType(1)/Selector and NULL SA_DATA.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          NULL
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid007,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL SA_DATA.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 2: Call GetData with the same DataType(1)/Selector/Data and NULL DataSize.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          &Data
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid008,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 3: Call GetData with the same DataType(1)/Selector, non-NULL Data and small DataSize.
  //
  DataSize = 10;

  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          &Data
                          );


  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid009,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_BUFFER_TOO_SMALL with small DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(1)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  //
  // Create SA_DATA2 for test
  //
  Data2.Mode = EfiIPsecTunnel;
  Data2.SNCount = 0;
  Data2.AntiReplayWindows = 0;
  Data2.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  Data2.AlgoInfo.EspAlgoInfo.EncKeyLength = 128;
  Data2.AlgoInfo.EspAlgoInfo.EncKey = EncKey;
  Data2.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  Data2.AlgoInfo.EspAlgoInfo.AuthKeyLength = 128;
  Data2.AlgoInfo.EspAlgoInfo.AuthKey = AuthKey;
  Data2.SaLifetime.ByteCount = 0;
  Data2.SaLifetime.SoftLifetime = 0;
  Data2.SaLifetime.HardLifetime = 0;
  Data2.PathMTU = 1000;
  Data2.SpdSelector = &SpdSelector;
  Data2.ManualSet = FALSE;
  Data2.TunnelSourceAddress.v4.Addr[0] = 192;
  Data2.TunnelSourceAddress.v4.Addr[1] = 168;
  Data2.TunnelSourceAddress.v4.Addr[2] = 88;
  Data2.TunnelSourceAddress.v4.Addr[3] = 1;
  Data2.TunnelDestinationAddress.v4.Addr[0] = 192;
  Data2.TunnelDestinationAddress.v4.Addr[1] = 168;
  Data2.TunnelDestinationAddress.v4.Addr[2] = 88;
  Data2.TunnelDestinationAddress.v4.Addr[3] = 2;


  DataSize = 1000;

  //
  // Call SetData with valid DataType(1)/Selector/SA_DATA2.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data2,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/SA_Data2 fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  //
  // CheckPoint 1: Call GetData with the same DataType(1)/Selector and NULL Data.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          NULL
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid023,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL SA_DATA2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 2: Call GetData with the same DataType(1)/Selector/Data and NULL DataSize.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          &Data2
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid024,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 3: Call GetData with the same DataType(1)/Selector, non-NULL Data and small DataSize.
  //
  DataSize = 10;

  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          &Data
                          );


  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid025,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_BUFFER_TOO_SMALL with small DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(1)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/NULL data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }
  
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestGetDataConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_PAD_ID              Selector;
  UINTN                         DataSize;
  EFI_IPSEC_PAD_DATA            Data;

  EFI_IP_ADDRESS_INFO         IPAddress;

  CHAR8  AuthData[100]; 
  CHAR8  RevocationData[100];

  IPAddress.PrefixLength = 0x20;
  IPAddress.Address.v4.Addr[0] = 192;
  IPAddress.Address.v4.Addr[1] = 168;
  IPAddress.Address.v4.Addr[2] = 88;
  IPAddress.Address.v4.Addr[3] = 1;

  Selector.PeerIdValid = FALSE;
  Selector.Id.IpAddress = &IPAddress;

  DataType = IPsecConfigDataTypePad;             

  Data.AuthProtocol = EfiIPsecAuthProtocolIKEv1;
  Data.AuthMethod = EfiIPsecAuthMethodPreSharedSecret;
  Data.IkeIdFlag = TRUE;
  Data.AuthDataSize = 100;
  Data.AuthData = AuthData;
  Data.RevocationDataSize = 100;
  Data.RevocationData = RevocationData;

  DataSize = 1000;

  //
  // Call SetData with valid DataType(2)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(2)/Selector/Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  //
  // CheckPoint 1: Call GetData with the same DataType(2)/Selector and NULL Data.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          NULL
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid010,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 2: Call GetData with the same DataType(2)/Selector and NULL DataSize.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          &Data
                          );


  if ( EFI_INVALID_PARAMETER != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid011,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_INVALID_PARAMETER with NULL DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // CheckPoint 3: Call GetData with the same DataType(2)/Selector, non-NULL Data and small DataSize.
  //
  DataSize = 10;

  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          &Data
                          );


  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid012,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_BUFFER_TOO_SMALL with small DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(2)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(2)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_CONFIG_SELECTOR     Selector;
  UINTN                         SelectorSize;

  DataType = IPsecConfigDataTypeMaximum;
  SelectorSize = 1000;
  
  //
  // CheckPoint 1: Call GetNextSelector with an invalid DataType(>2).
  //
  Status = IPsecConfig->GetNextSelector(
                          IPsecConfig,
                          DataType,
                          &SelectorSize,
                          &Selector
                          ); 

  
  if ( EFI_UNSUPPORTED != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid013,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_UNSUPPORTED with an invalid DataType (>2).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_CONFIG_SELECTOR     Selector;
  UINTN                         SelectorSize;

  SelectorSize = 1000;

  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++) {
    //
    // CheckPoint1: Call GetNextSelector with NULL SelectorSize 
    //
    Status = IPsecConfig->GetNextSelector(
                            IPsecConfig,
                            DataType,
                            NULL,
                            &Selector
                            );

    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid014,
                   L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_INVALID_PARAMETER with NULL SelectorSize.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );



    //
    // CheckPoint2: Call GetNextSelector with NULL Selector 
    //
    Status = IPsecConfig->GetNextSelector(
                            IPsecConfig,
                            DataType,
                            &SelectorSize,
                            NULL
                            );

    if ( EFI_INVALID_PARAMETER != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid015,
                   L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_INVALID_PARAMETER with NULL Selector.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_SPD_SELECTOR        Selector;
  UINTN                         SelectorSize;
  EFI_IPSEC_SPD_DATA            Data;
  EFI_IPSEC_PROCESS_POLICY      ProcessingPolicy;
  EFI_IP_ADDRESS_INFO           LocalAddress;
  EFI_IP_ADDRESS_INFO           RemoteAddress;

  CHAR8                         SelectorBuffer[1000];
  UINT32                        Index;

  DataType = IPsecConfigDataTypeSpd;
  
  LocalAddress.PrefixLength = 0x20;
  LocalAddress.Address.v4.Addr[0] = 192;
  LocalAddress.Address.v4.Addr[1] = 168;
  LocalAddress.Address.v4.Addr[2] = 200;
  LocalAddress.Address.v4.Addr[3] = 101;
  RemoteAddress.PrefixLength = 0x20;
  RemoteAddress.Address.v4.Addr[0] = 192;
  RemoteAddress.Address.v4.Addr[1] = 168;
  RemoteAddress.Address.v4.Addr[2] = 200;
  RemoteAddress.Address.v4.Addr[3] = 1;
  
  Selector.LocalAddress = &LocalAddress;
  Selector.LocalAddressCount = 1;
  Selector.RemoteAddress = &RemoteAddress;
  Selector.RemoteAddressCount = 1;
  Selector.NextLayerProtocol = 0x11;
  Selector.LocalPort = 0x010e;
  Selector.LocalPortRange = 0;
  Selector.RemotePort = 0x010e;
  Selector.RemotePortRange = 0;

  ProcessingPolicy.ExtSeqNum = FALSE;
  ProcessingPolicy.SeqOverflow = FALSE;
  ProcessingPolicy.FragCheck = FALSE;
  ProcessingPolicy.SaLifetime.ByteCount = 0;
  ProcessingPolicy.SaLifetime.SoftLifetime = 0;
  ProcessingPolicy.SaLifetime.HardLifetime = 0;
  ProcessingPolicy.Mode = EfiIPsecTransport;
  ProcessingPolicy.TunnelOption = NULL;
  ProcessingPolicy.Proto = EfiIPsecESP;
  ProcessingPolicy.Proto = IKE_AALG_SHA1HMAC;
  ProcessingPolicy.Proto = IKE_EALG_3DESCBC;

  Data.PackageFlag = 0x0;
  Data.TrafficDirection = EfiIPsecInBound;
  Data.Action = EfiIPsecActionProtect;
  Data.ProcessingPolicy = &ProcessingPolicy;
  Data.SaIdCount = 1;
  Data.SaId[0].Spi = 0;
  Data.SaId[0].Proto = 0;
  Data.SaId[0].DestAddress.v4.Addr[0] = 0;
  Data.SaId[0].DestAddress.v4.Addr[1] = 0;
  Data.SaId[0].DestAddress.v4.Addr[2] = 0;
  Data.SaId[0].DestAddress.v4.Addr[3] = 0;

  //
  // Prepare Environment: Call SetData with valid DataType(0)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(0)/Selector/Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }
  
  //
  // CheckPoint 1: Call GetNextSelector with valid DataType(0)/Selector and SelectorSize is 0.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }
  SelectorSize = 0;
  
  Status = IPsecConfig->GetNextSelector(
                          IPsecConfig,
                          DataType,
                          &SelectorSize,
                          (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                          ); 

  
  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid016,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_BUFFER_TOO_SMALL valid DataType(0)/Selector and SelectorSize is 0.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(0)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(0)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_SA_ID               Selector;
  UINTN                         SelectorSize; 
  EFI_IPSEC_SA_DATA             Data;

  EFI_IP_ADDRESS_INFO           LocalAddress;
  EFI_IP_ADDRESS_INFO           RemoteAddress;
  EFI_IPSEC_SPD_SELECTOR        SpdSelector;

  CHAR8                         SelectorBuffer[1000];
  UINT32                        Index;

  CHAR8  EncKey[128]; 
  CHAR8  AuthKey[128];


  Selector.Spi = 0;
  Selector.Proto = EfiIPsecESP;
  Selector.DestAddress.v4.Addr[0] = 192;
  Selector.DestAddress.v4.Addr[1] = 168;
  Selector.DestAddress.v4.Addr[2] = 88;
  Selector.DestAddress.v4.Addr[3] = 1;

  LocalAddress.PrefixLength = 0x20;
  LocalAddress.Address.v4.Addr[0] = 192;
  LocalAddress.Address.v4.Addr[1] = 168;
  LocalAddress.Address.v4.Addr[2] = 88;
  LocalAddress.Address.v4.Addr[3] = 1;
  RemoteAddress.PrefixLength = 0x20;
  RemoteAddress.Address.v4.Addr[0] = 192;
  RemoteAddress.Address.v4.Addr[1] = 168;
  RemoteAddress.Address.v4.Addr[2] = 88;
  RemoteAddress.Address.v4.Addr[3] = 2;

  DataType = IPsecConfigDataTypeSad;

  SpdSelector.LocalAddressCount = 1;                
  SpdSelector.LocalAddress = &LocalAddress;
  SpdSelector.RemoteAddressCount = 1;                
  SpdSelector.RemoteAddress = &RemoteAddress;
  SpdSelector.NextLayerProtocol = 0x11;             
  SpdSelector.LocalPort = 0x010e;           
  SpdSelector.LocalPortRange = 0;                
  SpdSelector.RemotePort = 0x010e;           
  SpdSelector.RemotePortRange = 0;                

  Data.Mode = EfiIPsecTransport;
  Data.SNCount = 0;
  Data.AntiReplayWindows = 0;
  Data.AlgoInfo.EspAlgoInfo.EncAlgoId = IKE_EALG_3DESCBC;
  Data.AlgoInfo.EspAlgoInfo.EncKeyLength = 128;
  Data.AlgoInfo.EspAlgoInfo.EncKey = EncKey;
  Data.AlgoInfo.EspAlgoInfo.AuthAlgoId = IKE_AALG_SHA1HMAC;
  Data.AlgoInfo.EspAlgoInfo.AuthKeyLength = 128;
  Data.AlgoInfo.EspAlgoInfo.AuthKey = AuthKey;
  Data.SaLifetime.ByteCount = 0;
  Data.SaLifetime.SoftLifetime = 0;
  Data.SaLifetime.HardLifetime = 0;
  Data.PathMTU = 1000;
  Data.SpdSelector = &SpdSelector;
  Data.ManualSet = FALSE;

  //
  // Prepare Environment: Call SetData with valid DataType(1)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }
  
  //
  // CheckPoint 1: Call GetNextSelector with valid DataType(1)/Selector and SelectorSize is 0.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }
  SelectorSize = 0;
  
  Status = IPsecConfig->GetNextSelector(
                          IPsecConfig,
                          DataType,
                          &SelectorSize,
                          (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                          ); 

  
  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid017,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_BUFFER_TOO_SMALL valid DataType(1)/Selector and SelectorSize is 0.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(1)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(1)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorConformanceTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_IPSEC_PAD_ID              Selector;
  UINTN                         SelectorSize;  
  EFI_IPSEC_PAD_DATA            Data;

  CHAR8                         SelectorBuffer[1000];
  UINT32                        Index;

  EFI_IP_ADDRESS_INFO           IPAddress;

  CHAR8  AuthData[100]; 
  CHAR8  RevocationData[100];

  IPAddress.PrefixLength = 0x20;
  IPAddress.Address.v4.Addr[0] = 192;
  IPAddress.Address.v4.Addr[1] = 168;
  IPAddress.Address.v4.Addr[2] = 88;
  IPAddress.Address.v4.Addr[3] = 1;

  Selector.PeerIdValid = FALSE;
  Selector.Id.IpAddress = &IPAddress;

  DataType = IPsecConfigDataTypePad;             

  Data.AuthProtocol = EfiIPsecAuthProtocolIKEv1;
  Data.AuthMethod = EfiIPsecAuthMethodPreSharedSecret;
  Data.IkeIdFlag = TRUE;
  Data.AuthDataSize = 100;
  Data.AuthData = AuthData;
  Data.RevocationDataSize = 100;
  Data.RevocationData = RevocationData;


  //
  // Prepare Environment: Call SetData with valid DataType(2)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(2)/Selector/Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }
  
  //
  // CheckPoint 1: Call GetNextSelector with valid DataType(2)/Selector and SelectorSize is 0.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }
  SelectorSize = 0;
  
  Status = IPsecConfig->GetNextSelector(
                          IPsecConfig,
                          DataType,
                          &SelectorSize,
                          (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                          ); 

  
  if ( EFI_BUFFER_TOO_SMALL != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid018,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_BUFFER_TOO_SMALL valid DataType(2)/Selector and SelectorSize is 0.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //  Clean Environment: Call IPsec->SetData with the same DataType(2)/Selector.  
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"SetData with valid DataType(2)/Selector/NULL Data fail",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
      return Status;   
  }

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;

  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++) {
    //
    // Call RegisterDataNotify with NULL Event 
    //
    Status = IPsecConfig->RegisterDataNotify(
                            IPsecConfig,
                            DataType,
                            NULL
                            );


    if ( EFI_INVALID_PARAMETER != Status && EFI_UNSUPPORTED != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid019,
                   L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() returns EFI_INVALID_PARAMETER with NULL Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_EVENT             Event;
  
  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  
  DataType = IPsecConfigDataTypeMaximum;
  
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   (EFI_EVENT_NOTIFY) EventNotifyFunc,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\r\n"
                   L"%a:%d.\r\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  
  //
  // Call RegisterDataNotify with an invalid DataType(>2)
  //
  Status = IPsecConfig->RegisterDataNotify(
                          IPsecConfig,
                          DataType,
                          Event
                          );

  if ( EFI_UNSUPPORTED != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid020,
                 L"VLAN_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() returns EFI_UNSUPPORTED with invalid DataType(>2).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->CloseEvent ( Event );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;

  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++) {
    //
    // Call RegisterDataNotify with NULL Event 
    //
    Status = IPsecConfig->UnregisterDataNotify(
                            IPsecConfig,
                            DataType,
                            NULL
                            );


    if ( EFI_INVALID_PARAMETER != Status && EFI_UNSUPPORTED != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestConformanceAssertionGuid021,
                   L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() returns EFI_INVALID_PARAMETER with NULL Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyConformanceTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;
  EFI_EVENT             Event;
  
  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  
  DataType = IPsecConfigDataTypeMaximum;
  
  Status = gtBS->CreateEvent (
                   EVT_NOTIFY_SIGNAL,
                   TPL_NOTIFY,
                   (EFI_EVENT_NOTIFY) EventNotifyFunc,
                   NULL,
                   &Event
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"tBS->CreateEvent() error().\r\n"
                   L"%a:%d.\r\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    return Status;
  }

  
  //
  // Call RegisterDataNotify with an invalid DataType(>2)
  //
  Status = IPsecConfig->UnregisterDataNotify(
                          IPsecConfig,
                          DataType,
                          Event
                          );

  if ( EFI_UNSUPPORTED != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestConformanceAssertionGuid022,
                 L"VLAN_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() returns EFI_UNSUPPORTED with invalid DataType(>2).",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  gtBS->CloseEvent ( Event );

  return EFI_SUCCESS;
}
