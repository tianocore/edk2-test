/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  HIIConfigRoutingBBTestMain.c

Abstract:

  Test Driver of HII Config Routing Protocol

--*/

#include "HIIConfigRoutingBBTestMain.h"

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_CONFIG_ROUTING_PROTOCOL_TEST_REVISION,
  EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID,
  L"HII Config Routing Protocol Test",
  L"UEFI HII Config Routing Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  /*
  //Use for unit test only
  {
    { 0x2a74c7ae, 0xa43c, 0x4eb8, { 0xa3, 0xaf, 0x78, 0x32, 0xf8, 0xc4, 0xcf, 0xf3 } },
    L"Unit Test Only",
    L"Verify the Assistant Function",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestUnitAutoTest
  },
  */
  {
    HII_CONFIG_ROUTING_PROTOCOL_EXTRACT_CONFIG_FUNCTION_AUTO_GUID,
    L"ExtractConfig_Func",
    L"Invoke ExtractConfig() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExtractConfigFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_EXPORT_CONFIG_FUNCTION_AUTO_GUID,
    L"ExportConfig_Func",
    L"Invoke ExportConfig() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExportConfigFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_ROUTE_CONFIG_FUNCTION_AUTO_GUID,
    L"RouteConfig_Func",
    L"Invoke RouteConfig() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestRouteConfigFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_BLOCK_TO_CONFIG_FUNCTION_AUTO_GUID,
    L"BlockToConfig_Func",
    L"Invoke BlockToConfig() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBlockToConfigFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_CONFIG_TO_BLOCK_FUNCTION_AUTO_GUID,
    L"ConfigToBlock_Func",
    L"Invoke ConfigToBlock() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestConfigToBlockFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_GET_ALT_CFG_FUNCTION_AUTO_GUID,
    L"GetAltCfg_Func",
    L"Invoke GetAltCfg() and verify interface correctness within test case",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetAltCfgFunctionAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_EXTRACT_CONFIG_CONFORMANCE_AUTO_GUID,
    L"ExtractConfig_Conf",
    L"Test whether ExtractConfig() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExtractConfigConformanceAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_EXPORT_CONFIG_CONFORMANCE_AUTO_GUID,
    L"ExportConfig_Conf",
    L"Test whether ExportConfig() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestExportConfigConformanceAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_ROUTE_CONFIG_CONFORMANCE_AUTO_GUID,
    L"RouteConfig_Conf",
    L"Test whether RouteConfig() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestRouteConfigConformanceAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_BLOCK_TO_CONFIG_CONFORMANCE_AUTO_GUID,
    L"BlockToConfig_Conf",
    L"Test whether BlockToConfig() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestBlockToConfigConformanceAutoTest
  },

  {
    HII_CONFIG_ROUTING_PROTOCOL_CONFIG_TO_BLOCK_CONFORMANCE_AUTO_GUID,
    L"ConfigToBlock_Conf",
    L"Test whether ConfigToBlock() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestConfigToBlockConformanceAutoTest
  },
  
  {
    HII_CONFIG_ROUTING_PROTOCOL_GET_ALT_CFG_CONFORMANCE_AUTO_GUID,
    L"GetAltCfg_Conf",
    L"Test whether GetAltCfg() performs enough parameter checking",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestGetAltCfgConformanceAutoTest
  },
  
  0
};



/**
 *  HII Config Routing Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
EFIAPI
InitializeBBTestHIIConfigRouting (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);
  SctInitializeLib (ImageHandle, SystemTable);


  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestHIIConfigRoutingProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestHIIConfigRoutingProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}


//
// Assistant Function 
//
EFI_STATUS
MultiAltRespToMultiReq (
  IN       EFI_STRING                           Resp,
  IN OUT   EFI_STRING                           Req
  )
{
  EFI_STRING Pointer1 = Resp;      
  EFI_STRING Pointer2 = NULL;
  EFI_STRING Pointer3 = Req;
  EFI_STRING CfgHdr = NULL;
  EFI_STRING FreePtr = NULL;
  CHAR8      Flag = 0;

  if (SctStrnCmp (Pointer1, L"GUID=", 5) != 0) {    
    return EFI_INVALID_PARAMETER;
  }

  Pointer2 = (EFI_STRING) SctAllocateZeroPool (2 * SctStrLen (Resp) + 2);
  if (Pointer2 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FreePtr = Pointer2;
  
  while (*Pointer1) {
    if (SctStrnCmp (Pointer1, L"GUID=", 5) == 0) {
      CfgHdr = Pointer2;
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&GUID=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      CfgHdr = Pointer2;
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&NAME=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&PATH=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
      if (NULL == SctStrStr (Req, CfgHdr)){
        if (*Req == L'G')
          *(Pointer3++) = L'&';
          SctStrCat (Req, CfgHdr);
          Pointer3 += SctStrLen (CfgHdr);
          Flag = 1;
        } else {
          Flag = 0;
      }  
    }
    while ((Flag == 1) && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0) && *Pointer1) {
      if (SctStrnCmp (Pointer1, L"&OFFSET=", 8) == 0) {
        *(Pointer3++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
          *(Pointer3++) = *(Pointer1++);
        }
      }
      if (SctStrnCmp (Pointer1, L"&WIDTH=", 7) == 0) {
        *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'&') {
          *(Pointer3++) = *(Pointer1++);
        }
      }
      if (SctStrnCmp (Pointer1, L"&VALUE=", 7) == 0) {
        Pointer1 += 7;
        while (*Pointer1 != L'&' && *Pointer1) {
          Pointer1++;
        }
      }
      if (SctStrnCmp (Pointer1, L"&ALTCFG=", 8) == 0) {
        Pointer1 += 8;
        while (*Pointer1 != L'&' && *Pointer1) {
          Pointer1++;
        }
      }
      if ((*Pointer1 == L'&') && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0) && 
        (SctStrnCmp (Pointer1, L"&OFFSET=", 8) != 0) && (SctStrnCmp (Pointer1, L"&WIDTH=", 7) != 0)) {
           *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'=') {
          *(Pointer3++) = *(Pointer1++);
        }
        while (*Pointer1 != L'&' && *Pointer1) {
          Pointer1++;
        }
      }
    }
    Pointer1++;
  }

  SctFreePool (FreePtr);
  
  return EFI_SUCCESS;
}


EFI_STATUS
MultiAltRespToMultiResp (
  IN       EFI_STRING                           Resp1,
  IN OUT   EFI_STRING                           Resp2
  )
{
  EFI_STRING Pointer1 = Resp1;      
  EFI_STRING Pointer2 = NULL;
  EFI_STRING Pointer3 = Resp2;
  EFI_STRING CfgHdr = NULL;
  EFI_STRING FreePtr = NULL;
  CHAR8      Flag = 0;

  if (SctStrnCmp (Pointer1, L"GUID=", 5) != 0) {    
    return EFI_INVALID_PARAMETER;
  }

  Pointer2 = (EFI_STRING) SctAllocateZeroPool (2 * SctStrLen (Resp1) + 2);
  if (Pointer2 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  FreePtr = Pointer2;
  
  while (*Pointer1) {
    if (SctStrnCmp (Pointer1, L"GUID=", 5) == 0) {
      CfgHdr = Pointer2;
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&GUID=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      CfgHdr = Pointer2;
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&NAME=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
    }
    if (SctStrnCmp (Pointer1, L"&PATH=", 6) == 0) {
      *(Pointer2++) = *(Pointer1++);
      while (*Pointer1 != L'&') {
        *(Pointer2++) = *(Pointer1++);
      }
      if (NULL == SctStrStr (Resp2, CfgHdr)){
        if (*Resp2 == L'G')
          *(Pointer3++) = L'&';
        SctStrCat (Resp2, CfgHdr);
        Pointer3 += SctStrLen (CfgHdr);
        Flag = 1;
      } else {
        Flag = 0;
      }  
    }
    while ((Flag == 1) && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0) && *Pointer1) {
      if (SctStrnCmp (Pointer1, L"&OFFSET=", 8) == 0) {
        *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'&') {
          *(Pointer3++) = *(Pointer1++);
        }
      }
      if (SctStrnCmp (Pointer1, L"&WIDTH=", 7) == 0) {
        *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'&') {
          *(Pointer3++) = *(Pointer1++);
        }
      }
      if (SctStrnCmp (Pointer1, L"&VALUE=", 7) == 0) {
        *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'&' && *Pointer1) {
          *(Pointer3++) = *(Pointer1++);
        }
      }
      if (SctStrnCmp (Pointer1, L"&ALTCFG=", 8) == 0) {
        Pointer1 += 8;
        while (*Pointer1 != L'&' && *Pointer1) {
          Pointer1++;
        }
      }
      if ((*Pointer1 == L'&') && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0)) {
        *(Pointer3++) = *(Pointer1++);
        while (*Pointer1 != L'=') {
          *(Pointer3++) = *(Pointer1++);
        }
        while (*Pointer1 != L'&' && *Pointer1) {
          *(Pointer3++) = *(Pointer1++);
        }
      }
    }
    Pointer1++;
  }

  SctFreePool (FreePtr);
  
  return EFI_SUCCESS;
}


EFI_STATUS
MultiAltRespToReq(
  IN       EFI_STRING                           Resp,
  IN OUT   EFI_STRING                           Req
  )
{
  EFI_STRING Pointer1 = Resp;
  EFI_STRING Pointer2 = Req;
  EFI_STRING Pointer3 = NULL; 
  EFI_STRING FreePtr = NULL;

  if (SctStrnCmp (Pointer1, L"GUID=", 5) != 0) {    
    return EFI_INVALID_PARAMETER;
  }
  
  Pointer3 = (EFI_STRING) SctAllocateZeroPool (2 * SctStrLen (Resp) + 2);
  if (Pointer3 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FreePtr = Pointer3;
  
  while ((*Pointer1 != 0) && (SctStrnCmp (Pointer1, L"&ALTCFG=", 8) != 0) && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0)) {
    *(Pointer3++) = *(Pointer1++);
  }

  Pointer3 = FreePtr;

  while (*Pointer3 != 0) {

    if (SctStrnCmp (Pointer3, L"&", 1) != 0)
      *(Pointer2++) = *(Pointer3++);
    else if ((SctStrnCmp (Pointer3, L"&NAME=", 6) == 0) || (SctStrnCmp (Pointer3, L"&PATH=", 6) == 0) ||
        (SctStrnCmp (Pointer3, L"&OFFSET=", 8) == 0) || (SctStrnCmp (Pointer3, L"&WIDTH=", 7) == 0))
      *(Pointer2++) = *(Pointer3++);
    else if (SctStrnCmp (Pointer3, L"&VALUE=", 7) == 0) {
      Pointer3++;
      while (*Pointer3 && *Pointer3 != L'&')
        Pointer3++;
      if (*Pointer3 == L'&')
        continue;
      break;
    }
    else {
      while (*Pointer3) {
        while (*Pointer3 != L'=')
          *(Pointer2++) = *(Pointer3++);
        while (*Pointer3 != L'&' && *Pointer3 )
          Pointer3++;
      }
      break;
    }
  }

  SctFreePool (FreePtr);
 
  return EFI_SUCCESS;
}


EFI_STATUS
MultiAltRespToResp (
  IN       EFI_STRING                           Resp1,
  IN OUT   EFI_STRING                           Resp2
  )
{
  EFI_STRING Pointer1 = Resp1;
  EFI_STRING Pointer2 = Resp2;

  if (SctStrnCmp (Pointer1, L"GUID=", 5) != 0) {    
    return EFI_INVALID_PARAMETER;
  }
  
  while ((*Pointer1 != 0) && (SctStrnCmp (Pointer1, L"&ALTCFG=", 8) != 0) && (SctStrnCmp (Pointer1, L"&GUID=", 6) != 0)) {
    *(Pointer2++) = *(Pointer1++);
  }
   
  return EFI_SUCCESS;
}

