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
    IPsecConfigBBTestFunction.c

Abstract:
    for EFI Driver IPsec Config Protocol's function Test

--*/
#include "SctLib.h"
#include "IPsecConfigBBTestMain.h"

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint4 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint5 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint6 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );
  
EFI_STATUS
EFIAPI
BBTestGetNextSelectorFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetNextSelectorFunctionTestCheckpoint2 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestGetNextSelectorFunctionTestCheckpoint3 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  );

//
//Test Cases
//
EFI_STATUS
EFIAPI
BBTestSetDataFunctionTest (
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
  BBTestSetDataFunctionTestCheckpoint1( StandardLib, IPsecConfig );

  BBTestSetDataFunctionTestCheckpoint2( StandardLib, IPsecConfig );

  BBTestSetDataFunctionTestCheckpoint3( StandardLib, IPsecConfig );

  BBTestSetDataFunctionTestCheckpoint4( StandardLib, IPsecConfig );

  BBTestSetDataFunctionTestCheckpoint5( StandardLib, IPsecConfig );  

  BBTestSetDataFunctionTestCheckpoint6( StandardLib, IPsecConfig );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTest (
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
  BBTestGetDataFunctionTestCheckpoint1( StandardLib, IPsecConfig );

  BBTestGetDataFunctionTestCheckpoint2( StandardLib, IPsecConfig );

  BBTestGetDataFunctionTestCheckpoint3( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetNextSelectorFunctionTest (
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
  BBTestGetNextSelectorFunctionTestCheckpoint1( StandardLib, IPsecConfig );

  BBTestGetNextSelectorFunctionTestCheckpoint2( StandardLib, IPsecConfig );

  BBTestGetNextSelectorFunctionTestCheckpoint3( StandardLib, IPsecConfig );  

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestRegisterDataNotifyFunctionTest (
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
  BBTestRegisterDataNotifyFunctionTestCheckpoint1( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyFunctionTest (
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
  BBTestUnregisterDataNotifyFunctionTestCheckpoint1( StandardLib, IPsecConfig );
  
  return EFI_SUCCESS;
}


//
//Check Points
//
EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint1 (
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
  CHAR8                         DataBuffer[1000];

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
  // Check Point 1: Call SetData with valid DataType(0)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid001,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(0)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(0)/Selector and NULL Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid002,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(0)/Selector and NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(0)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid003,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush given selector configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(0)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint2 (
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
  CHAR8                         DataBuffer[1000];  

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
  // Check Point 1: Call SetData with valid DataType(1)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
   
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid004,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(1)/Selector and NULL Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid005,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector and NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(1)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid006,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush given selector configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(1)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Create SA_DATA2 datastructure
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

  
  //
  // Check Point 4: Call SetData with valid DataType(1)/Selector/SA_Data2.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data2,
                          NULL
                          );  
   
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid037,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector/SA_Data2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 5: Call SetData with valid DataType(1)/Selector and NULL SA_Data2.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid038,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector and NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 6: Call GetData with the same DataType(1)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid039,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush given selector configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(1)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint3 (
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
  CHAR8                         DataBuffer[1000];

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
  // Check Point 1: Call SetData with valid DataType(2)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid007,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(2)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(2)/Selector and NULL Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          NULL,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid008,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(2)/Selector and NULL Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(2)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid009,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush given selector configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(2)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint4 (
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
  CHAR8                         DataBuffer[1000];

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
  // Check Point 1: Call SetData with valid DataType(0)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid010,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(0)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(0)/Data and NULL Selector.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          NULL,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid011,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(0)/Data and NULL Selector.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(0)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid012,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush entire configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(0)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint5 (
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
  CHAR8                         DataBuffer[1000];

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
  // Check Point 1: Call SetData with valid DataType(1)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid013,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(1)/Data and NULL Selector.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          NULL,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid014,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Data and NULL Selector.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(1)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid015,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush entire configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(1)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestSetDataFunctionTestCheckpoint6 (
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
  CHAR8                         DataBuffer[1000];

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
  // Check Point 1: Call SetData with valid DataType(2)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid016,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(2)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 2: Call SetData with valid DataType(2)/Data and NULL Selector.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          NULL,
                          &Data,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid017,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(2)/Data and NULL Selector.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 3: Call GetData with the same DataType(2)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid018,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - After flush entire configuration by SetData, GetData() returns EFI_NOT_FOUND valid DataType(2)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
BBTestGetDataFunctionTestCheckpoint1 (
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

  EFI_IP_ADDRESS_INFO           LocalAddress;
  EFI_IP_ADDRESS_INFO           RemoteAddress;
  EFI_IPSEC_PROCESS_POLICY      ProcessingPolicy;

  CHAR8                         DataBuffer[1000];

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
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(0)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 1: Call GetData with the same DataType(0)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid019,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_SUCCESS valid DataType(0)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( ((EFI_IPSEC_SPD_DATA *)DataBuffer)->PackageFlag != 0x0 || 
  	   ((EFI_IPSEC_SPD_DATA *)DataBuffer)->TrafficDirection != EfiIPsecInBound || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->Action != EfiIPsecActionProtect || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->ExtSeqNum != FALSE || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->SeqOverflow != FALSE || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->FragCheck != FALSE || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->Mode != EfiIPsecTransport || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->TunnelOption != 0 || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->Proto != EfiIPsecESP || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->AuthAlgoId != IKE_AALG_SHA1HMAC || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->EncAlgoId != IKE_EALG_3DESCBC || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->SaLifetime.ByteCount != 0 || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->SaLifetime.SoftLifetime != 0 || 
       ((EFI_IPSEC_SPD_DATA *)DataBuffer)->ProcessingPolicy->SaLifetime.HardLifetime != 0 ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;    
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid020,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns the right values which are set before.",
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
BBTestGetDataFunctionTestCheckpoint2 (
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
  CHAR8                         DataBuffer[1000];  

  EFI_IP_ADDRESS_INFO           LocalAddress;
  EFI_IP_ADDRESS_INFO           RemoteAddress;
  EFI_IPSEC_SPD_SELECTOR        SpdSelector;

  UINT8                         Index;

  UINT8  EncKey[128]; 
  UINT8  AuthKey[128];
  VOID   *EncKey1;
  VOID   *AuthKey1;


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

  for (Index=0; Index<128; Index++) {
    EncKey[Index] = Index;
    AuthKey[Index] = Index;
  }

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
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector/SA_DATA.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 1: Call GetData with the same DataType(1)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid021,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_SUCCESS valid DataType(1)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( ((EFI_IPSEC_SA_DATA *)DataBuffer)->Mode != EfiIPsecTransport || 
  	   ((EFI_IPSEC_SA_DATA *)DataBuffer)->SNCount != 0 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->AntiReplayWindows != 0 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncAlgoId != IKE_EALG_3DESCBC || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncKeyLength != 128 || 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->AlgoInfo.EspAlgoInfo.EncKey != EncKey || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthAlgoId != IKE_AALG_SHA1HMAC || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthKeyLength != 128 || 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->AlgoInfo.EspAlgoInfo.AuthKey != AuthKey || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->SaLifetime.ByteCount != 0 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->SaLifetime.SoftLifetime != 0 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->SaLifetime.HardLifetime != 0 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->PathMTU != 1000 || 
       ((EFI_IPSEC_SA_DATA *)DataBuffer)->ManualSet != FALSE ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;    
  } else {
    EncKey1 = ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncKey;
    AuthKey1 = ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthKey;  
    for (Index=0; Index<128; Index++) {
      if ( ((UINT8 *)EncKey1)[Index] != Index || ((UINT8 *)AuthKey1)[Index] != Index ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED; 
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      }
    }
  }

  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid022,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns the right SA_DATA which are set before.",
                 L"%a:%d: Status - %r datasize %d sizeof %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 DataSize, 
                 sizeof(EFI_IPSEC_SA_DATA)
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
  // Prepare Environment: Call SetData with valid DataType(1)/Selector/Data.
  //
  Status = IPsecConfig->SetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &Data2,
                          NULL
                          );  
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(1)/Selector/SA_DATA2.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 4: Call GetData with the same DataType(1)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid040,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_SUCCESS valid DataType(1)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( DataSize != (sizeof(EFI_IPSEC_SA_DATA2) 
                  + Data.AlgoInfo.EspAlgoInfo.AuthKeyLength 
                  + Data.AlgoInfo.EspAlgoInfo.EncKeyLength) ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->Mode != EfiIPsecTunnel || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->SNCount != 0 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->AntiReplayWindows != 0 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncAlgoId != IKE_EALG_3DESCBC || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncKeyLength != 128 || 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->AlgoInfo.EspAlgoInfo.EncKey != EncKey || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthAlgoId != IKE_AALG_SHA1HMAC || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthKeyLength != 128 || 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->AlgoInfo.EspAlgoInfo.AuthKey != AuthKey || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->SaLifetime.ByteCount != 0 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->SaLifetime.SoftLifetime != 0 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->SaLifetime.HardLifetime != 0 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->PathMTU != 1000 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->ManualSet != FALSE ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelSourceAddress.v4.Addr[0] != 192 ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelSourceAddress.v4.Addr[1] != 168 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelSourceAddress.v4.Addr[2] != 88  ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelSourceAddress.v4.Addr[3] != 1 ||      
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelDestinationAddress.v4.Addr[0] != 192 ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelDestinationAddress.v4.Addr[1] != 168 || 
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelDestinationAddress.v4.Addr[2] != 88  ||
       ((EFI_IPSEC_SA_DATA2 *)DataBuffer)->TunnelDestinationAddress.v4.Addr[3] != 2 ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;    
  } else {
    EncKey1 = ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.EncKey;
    AuthKey1 = ((EFI_IPSEC_SA_DATA *)DataBuffer)->AlgoInfo.EspAlgoInfo.AuthKey;  
    for (Index=0; Index<128; Index++) {
      if ( ((UINT8 *)EncKey1)[Index] != Index || ((UINT8 *)AuthKey1)[Index] != Index ) {
        AssertionType = EFI_TEST_ASSERTION_FAILED; 
      } else {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
     }
    }
  }

  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid041,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns the right SA_DATA2 which are set before.",
                 L"%a:%d: Status - %r  datasize %d sizeof %d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 DataSize,
                 sizeof(EFI_IPSEC_SA_DATA2)
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
BBTestGetDataFunctionTestCheckpoint3 (
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
  CHAR8                         DataBuffer[1000];

  EFI_IP_ADDRESS_INFO           IPAddress;

  UINT8  AuthData[100]; 
  UINT8  RevocationData[100];
  VOID   *AuthData1;
  VOID   *RevocationData1;
  UINT8  Index;

  IPAddress.PrefixLength = 0x20;
  IPAddress.Address.v4.Addr[0] = 192;
  IPAddress.Address.v4.Addr[1] = 168;
  IPAddress.Address.v4.Addr[2] = 88;
  IPAddress.Address.v4.Addr[3] = 1;

  Selector.PeerIdValid = FALSE;
  Selector.Id.IpAddress = &IPAddress;

  DataType = IPsecConfigDataTypePad;             

  for (Index=0; Index<100; Index++) {
    AuthData[Index] = Index;
    RevocationData[Index] = Index;
  }

  Data.AuthProtocol = EfiIPsecAuthProtocolIKEv1;
  Data.AuthMethod = EfiIPsecAuthMethodPreSharedSecret;
  Data.IkeIdFlag = TRUE;
  Data.AuthDataSize = 100;
  Data.AuthData = AuthData;
  Data.RevocationDataSize = 100;
  Data.RevocationData = RevocationData;
  
  
  DataSize = 1000;

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
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"IPSEC_CONFIG_PROTOCOL.SetData - SetData() returns EFI_SUCCESS valid DataType(2)/Selector/Data.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Check Point 1: Call GetData with the same DataType(2)/Selector.
  //
  Status = IPsecConfig->GetData(
                          IPsecConfig,
                          DataType,
                          (EFI_IPSEC_CONFIG_SELECTOR *) &Selector,
                          &DataSize,
                          DataBuffer
                          );
  if ( EFI_SUCCESS != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid023,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns EFI_SUCCESS valid DataType(2)/Selector/DataSize.",
                 L"%a:%d: Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  if ( ((EFI_IPSEC_PAD_DATA *)DataBuffer)->AuthProtocol != EfiIPsecAuthProtocolIKEv1 || 
  	   ((EFI_IPSEC_PAD_DATA *)DataBuffer)->AuthMethod != EfiIPsecAuthMethodPreSharedSecret || 
       ((EFI_IPSEC_PAD_DATA *)DataBuffer)->IkeIdFlag != TRUE || 
       ((EFI_IPSEC_PAD_DATA *)DataBuffer)->AuthDataSize != 100 || 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->AuthData != AuthData || 
       ((EFI_IPSEC_PAD_DATA *)DataBuffer)->RevocationDataSize != 100 
//       (EFI_IPSEC_SA_DATA *)DataBuffer->RevocationData != RevocationData
    ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;    
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  AuthData1 = ((EFI_IPSEC_PAD_DATA *)DataBuffer)->AuthData;
  RevocationData1 = ((EFI_IPSEC_PAD_DATA *)DataBuffer)->RevocationData;  
  for (Index=0; Index<100; Index++) {
    if ( ((UINT8 *)AuthData1)[Index] != Index || ((UINT8 *)RevocationData1)[Index] != Index ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED; 
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
  	}
  }
  
  StandardLib->RecordAssertion(
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid024,
                 L"IPSEC_CONFIG_PROTOCOL.GetData - GetData() returns the right values which are set before.",
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
BBTestGetNextSelectorFunctionTestCheckpoint1 (
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
  // CheckPoint 1: Call GetNextSelector with valid DataType(0)/Selector and SelectorSize.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }

  Index = 0;
  while ( EFI_SUCCESS == Status ) {
  	SelectorSize = 1000;

    Status = IPsecConfig->GetNextSelector(
                            IPsecConfig,
                            DataType,
                            &SelectorSize,
                            (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                            ); 

    if ( Index == 0 ) {
      if ( EFI_SUCCESS == Status ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if ( ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalAddress->PrefixLength != 0x20 || 
             ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalAddress->Address.v4.Addr[0] != 192 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalAddress->Address.v4.Addr[1] != 168 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalAddress->Address.v4.Addr[2] != 200 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalAddress->Address.v4.Addr[3] != 101 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemoteAddress->PrefixLength != 0x20 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemoteAddress->Address.v4.Addr[0] != 192 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemoteAddress->Address.v4.Addr[1] != 168 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemoteAddress->Address.v4.Addr[2] != 200 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemoteAddress->Address.v4.Addr[3] != 1 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->NextLayerProtocol != 0x11 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalPort != 0x010e || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->LocalPortRange != 0 || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemotePort != 0x010e || 
			 ((EFI_IPSEC_SPD_SELECTOR *)SelectorBuffer)->RemotePortRange != 0
        ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED; 
        }
	  } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;        
	  }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIPsecConfigBBTestFunctionAssertionGuid025,
                     L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_SUCCESS valid DataType(0)/Selector and SelectorSize.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
  
    }
      
    Index++;
  } 
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid026,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_NOT_FOUND valid DataType(0)/Selector and SelectorSize.",
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
BBTestGetNextSelectorFunctionTestCheckpoint2 (
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
  // CheckPoint 1: Call GetNextSelector with valid DataType(1)/Selector and SelectorSize.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }

  Index = 0;
  while ( EFI_SUCCESS == Status ) {
  	SelectorSize = 1000;
    Status = IPsecConfig->GetNextSelector(
                            IPsecConfig,
                            DataType,
                            &SelectorSize,
                            (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                            ); 

    if ( Index == 0 ) {
      if ( EFI_SUCCESS == Status ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if ( ((EFI_IPSEC_SA_ID *)SelectorBuffer)->Spi != 0 || 
             ((EFI_IPSEC_SA_ID *)SelectorBuffer)->Proto != EfiIPsecESP || 
			 ((EFI_IPSEC_SA_ID *)SelectorBuffer)->DestAddress.v4.Addr[0] != 192 ||              
			 ((EFI_IPSEC_SA_ID *)SelectorBuffer)->DestAddress.v4.Addr[1] != 168 || 
			 ((EFI_IPSEC_SA_ID *)SelectorBuffer)->DestAddress.v4.Addr[2] != 88 || 
			 ((EFI_IPSEC_SA_ID *)SelectorBuffer)->DestAddress.v4.Addr[3] != 1 
        ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED; 
        }        
	  } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;        
	  }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIPsecConfigBBTestFunctionAssertionGuid027,
                     L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_SUCCESS valid DataType(1)/Selector and SelectorSize.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
  
    }
      
    Index++;
  } 
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid028,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_NOT_FOUND valid DataType(1)/Selector and SelectorSize.",
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
BBTestGetNextSelectorFunctionTestCheckpoint3 (
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
  // CheckPoint 1: Call GetNextSelector with valid DataType(2)/Selector and SelectorSize.
  //
  for (Index=0; Index<1000; Index++) {
    SelectorBuffer[Index] = 0;
  }

  Index = 0;
  while ( EFI_SUCCESS == Status ) {
  	SelectorSize = 1000;
    Status = IPsecConfig->GetNextSelector(
                            IPsecConfig,
                            DataType,
                            &SelectorSize,
                            (EFI_IPSEC_CONFIG_SELECTOR *) SelectorBuffer
                            ); 

    if ( Index == 0 ) {
      if ( EFI_SUCCESS == Status ) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
        if ( ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->PeerIdValid != FALSE ||
             ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->Id.IpAddress->PrefixLength	!= 0x20 || 
             ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->Id.IpAddress->Address.v4.Addr[0] != 192 || 
			 ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->Id.IpAddress->Address.v4.Addr[1] != 168 ||              
			 ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->Id.IpAddress->Address.v4.Addr[2] != 88 || 
			 ((EFI_IPSEC_PAD_ID *)SelectorBuffer)->Id.IpAddress->Address.v4.Addr[3] != 1 
        ) {
          AssertionType = EFI_TEST_ASSERTION_FAILED; 
        }         
	  } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;        
	  }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gIPsecConfigBBTestFunctionAssertionGuid029,
                     L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_SUCCESS valid DataType(2)/Selector and SelectorSize.",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
  
    }
      
    Index++;
  } 
  
  if ( EFI_NOT_FOUND != Status ) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gIPsecConfigBBTestFunctionAssertionGuid030,
                 L"IPSEC_CONFIG_PROTOCOL.GetNextSelector - GetNextSelector() returns EFI_NOT_FOUND valid DataType(2)/Selector and SelectorSize.",
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
BBTestRegisterDataNotifyFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_EVENT                     Event;
  
  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++ ) {
  	
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
      break;
    }

    //
    // Call RegisterDataNotify with Event 
    //
    Status = IPsecConfig->RegisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_UNSUPPORTED == Status ) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify() is not supported.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      gtBS->CloseEvent ( Event );
      continue;
    }
	
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid031,
                   L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() returns EFI_SUCCESS with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if ( EFI_SUCCESS != Status ) {
      gtBS->CloseEvent ( Event );	
      continue;
    }
    //
    // Call RegisterDataNotify with same Event 
    //
    Status = IPsecConfig->RegisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_ACCESS_DENIED != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid032,
                   L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() returns EFI_ACCESS_DENIED with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if ( EFI_ACCESS_DENIED != Status ) {
      IPsecConfig->UnregisterDataNotify(
                     IPsecConfig,
                     DataType,
                     Event
                     );
      gtBS->CloseEvent ( Event );
      continue;
    }

    Status = IPsecConfig->UnregisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_SUCCESS != Status ) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() ",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseEvent ( Event );
      continue;        
    }	

    Status = IPsecConfig->RegisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid033,
                   L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() returns EFI_SUCCESS with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    if ( EFI_SUCCESS == Status ) {
      IPsecConfig->UnregisterDataNotify(
                     IPsecConfig,
                     DataType,
                     Event
                     );
    }

    gtBS->CloseEvent ( Event );		
  }

  return EFI_SUCCESS;

}

EFI_STATUS
EFIAPI
BBTestUnregisterDataNotifyFunctionTestCheckpoint1 (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL         *StandardLib,
  IN EFI_IPSEC_CONFIG_PROTOCOL                  *IPsecConfig
  )
{
  EFI_STATUS            Status;
  EFI_TEST_ASSERTION    AssertionType;

  EFI_IPSEC_CONFIG_DATA_TYPE    DataType;
  EFI_EVENT                     Event;

  for ( DataType = IPsecConfigDataTypeSpd; DataType < IPsecConfigDataTypeMaximum; DataType++ ) {
  	
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
      break;
    }

    //
    // Call UnregisterDataNotify with Event which has not been registered.
    //
    Status = IPsecConfig->UnregisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_UNSUPPORTED == Status ) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify() is not supported.\r\n"
                     L"%a:%d.\r\n",
                     __FILE__,
                     (UINTN)__LINE__
                     );
      gtBS->CloseEvent ( Event );
      continue;
    }
	
    if ( EFI_NOT_FOUND != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid034,
                   L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() returns EFI_NOT_FOUND with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if ( EFI_NOT_FOUND != Status ) {
      gtBS->CloseEvent ( Event );
      continue;
    }
	
    //
    // Call RegisterDataNotify with same Event 
    //
    Status = IPsecConfig->RegisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    if ( EFI_SUCCESS != Status ) {	
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"IPSEC_CONFIG_PROTOCOL.RegisterDataNotify - RegisterDataNotify() ",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      gtBS->CloseEvent ( Event );
	  continue;
    }

    Status = IPsecConfig->UnregisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
	
    if ( EFI_SUCCESS != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }    	

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid035,
                   L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() returns EFI_SUCCESS with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

	if ( EFI_SUCCESS != Status ) {
      gtBS->CloseEvent ( Event );
      continue;        
    }	

    Status = IPsecConfig->UnregisterDataNotify(
                            IPsecConfig,
                            DataType,
                            Event
                            );
    if ( EFI_NOT_FOUND != Status ) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion(
                   StandardLib,
                   AssertionType,
                   gIPsecConfigBBTestFunctionAssertionGuid036,
                   L"IPSEC_CONFIG_PROTOCOL.UnregisterDataNotify - UnregisterDataNotify() returns EFI_NOT_FOUND with valid DataType/Event.",
                   L"%a:%d: Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );

    gtBS->CloseEvent ( Event );		
  }

  return EFI_SUCCESS;

}
