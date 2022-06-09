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

  HIIConfigAccessBBTestMain.c

Abstract:

  Test Driver of HII Configuration Access Protocol

--*/

#include "HIIConfigAccessBBTestMain.h"

//
// Global variables
//
EFI_HANDLE mImageHandle;

EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_REVISION,
  EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID,
  L"HII Configuration Access Protocol Test",
  L"UEFI HII Configuration Access  Protocol Black-Box Test"
};

EFI_GUID gSupportProtocolGuid[] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  /*
  //Use for unit test only
  {
    { 0x8cdda816, 0x3f97, 0x4155, { 0xa6, 0x73, 0x86, 0x93, 0x79, 0x8f, 0xb0, 0x6d } },
	L"Unit Test Only",
	L"Verify the Assistant Function",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestUnitTest
  },
  */
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0101,
    L"ExtractConfigFunction",
    L"Function auto test for HII Configuration Access Protocol ExtractConfig().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestExtractConfigFunctionTest
  },
  
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0102,
    L"RouteConfigFunction",
    L"Function auto test for HII Configuration Access Protocol RouteConfig().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRouteConfigFunctionTest
  },
  /*
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0103,
    L"CallBackFunction",
    L"Function auto test for HII Configuration Access Protocol CallBack().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCallBackFunctionTest
  },
  */
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0201,
    L"ExtractConfigConformance",
    L"Conformance auto test for HII Configuration Access Protocol ExtractConfig().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestExtractConfigConformanceTest
  },
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0202,
    L"RouteConfigConformance",
    L"Conformance auto test for HII Configuration Access Protocol RouteConfig().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestRouteConfigConformanceTest
  },
  /*
  {
    EFI_HII_CONFIG_ACCESS_PROTOCOL_TEST_ENTRY_GUID0203,
    L"CallBackConformance",
    L"Conformance auto test for HII Configuration Access Protocol CallBack().",
    EFI_TEST_LEVEL_MINIMAL,
    gSupportProtocolGuid,
    EFI_TEST_CASE_AUTO,
    BBTestCallBackConformanceTest
  },
  */
  0
};




EFI_STATUS
EFIAPI
InitializeHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  //
  // initialize test utility lib
  //

  SctInitializeLib (ImageHandle, SystemTable);

  mImageHandle = ImageHandle;

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           UnloadHIIConfigAccessBBTest,
           &gBBTestProtocolInterface
           );
}


EFI_STATUS
UnloadHIIConfigAccessBBTest (
  IN EFI_HANDLE                   ImageHandle
  )
{
  return EfiUninstallAndFreeBBTestInterface (
           ImageHandle,
           gBBTestProtocolInterface
           );
}


// Assistance Function
UINTN
EfiDevicePathSize (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
/*++

Routine Description:

  Calculate the space size of a device path.

Arguments:

  DevicePath  - A specified device path

Returns:

  The size.

--*/
{
  EFI_DEVICE_PATH_PROTOCOL  *Start;

  if (DevicePath == NULL) {
    return 0;
  }

  //
  // Search for the end of the device path structure
  //
  Start = DevicePath;
  while (!SctIsDevicePathEnd (DevicePath)) {
    DevicePath = SctNextDevicePathNode (DevicePath);
  }

  //
  // Compute the size and add back in the size of the end device path structure
  //
  return ((UINTN) DevicePath - (UINTN) Start) + sizeof (EFI_DEVICE_PATH_PROTOCOL);
}


STATIC
CHAR16
NibbleToHexCharPrivate (
  IN UINT8                         Nibble
  )
/*++

  Routine Description:
    Converts the low nibble of a byte to hex unicode character.

  Arguments:
    Nibble - lower nibble of a byte.

  Returns:
    Hex unicode character between L'0' to L'f'.

--*/
{
  Nibble &= 0x0F;

  if (Nibble <= 0x9) {
    return (CHAR16)(Nibble + L'0');
  }

  return (CHAR16)(Nibble - 0xA + L'a');
}


STATIC
EFI_STATUS
BufToHexStringPrivate (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                     Len,
  IN     BOOLEAN                   Flag
  )
/*++

  Routine Description:
    Converts binary buffer to Unicode string.
    At a minimum, any blob of data could be represented as a hex string.

  Arguments:
    Str                   - Pointer to the string.
    HexStringBufferLength - Length in bytes of buffer to hold the hex string. Includes tailing '\0' character.
                            If routine return with EFI_SUCCESS, containing length of hex string buffer.
                            If routine return with EFI_BUFFER_TOO_SMALL, containg length of hex string buffer desired.
    Buf                   - Buffer to be converted from.
    Len                   - Length in bytes of the buffer to be converted.
    Flag                  - If TRUE, encode the data in the same order as the it 
                            resides in the Buf. Else encode it in the reverse direction.

  Returns:
    EFI_SUCCESS           - Routine  success.
    EFI_BUFFER_TOO_SMALL  - The hex string buffer is too small.

--*/
{
  UINTN       Idx;
  UINT8       Byte;
  UINTN       StrLen;

  //
  // Make sure string is either passed or allocate enough.
  // It takes 2 Unicode characters (4 bytes) to represent 1 byte of the binary buffer.
  // Plus the Unicode termination character.
  //
  StrLen = Len * 2;
  if ((*HexStringBufferLength) < (StrLen + 1) * sizeof (CHAR16)) {
    *HexStringBufferLength = (StrLen + 1) * sizeof (CHAR16);
    return EFI_BUFFER_TOO_SMALL;
  }

  *HexStringBufferLength = (StrLen + 1) * sizeof (CHAR16);
  
  //
  // Ends the string.
  //
  Str[StrLen] = 0;

  for (Idx = 0; Idx < Len; Idx++) {

    Byte = Buf[Idx];
    if (Flag) {
      Str[Idx * 2]     = NibbleToHexCharPrivate ((UINT8)(Byte >> 4));
      Str[Idx * 2 + 1] = NibbleToHexCharPrivate (Byte);
    } else {
      Str[StrLen - 1 - Idx * 2] = NibbleToHexCharPrivate (Byte);
      Str[StrLen - 2 - Idx * 2] = NibbleToHexCharPrivate ((UINT8)(Byte >> 4));
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
GetDevicePath (
  IN  EFI_HII_CONFIG_ACCESS_PROTOCOL    *ConfigAccess,
  OUT EFI_STRING                        *DevicePathStr
  )
{
  EFI_STATUS                        Status;
  UINTN                             Index;
  UINTN                             NoHandles;
  EFI_HANDLE                        *HandleBuffer;
  EFI_HANDLE                        ConfigAccessHandle = NULL;
  EFI_HII_CONFIG_ACCESS_PROTOCOL    *TestedConfigAccess;
  EFI_DEVICE_PATH_PROTOCOL          *DevicePath;
  UINTN                             Length;
  UINTN                             PathHdrSize;

  //
  // locate all Hii Configuration Access Protocol Instances
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiHIIConfigAccessProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || (NoHandles == 0)) {
    return EFI_NOT_FOUND;
  }

  //
  // scan for the handle that matched with the Hii Configuration Access Protocol that
  // passed in by the test framework
  //
  for (Index = 0; Index < NoHandles; Index++) {
    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiHIIConfigAccessProtocolGuid,
                     (VOID **) &TestedConfigAccess
                     );
    if (EFI_ERROR(Status)) {
      continue;
    }

    if (TestedConfigAccess == ConfigAccess) {
      ConfigAccessHandle = HandleBuffer[Index];
      break;
    }
  }

  gtBS->FreePool (HandleBuffer);

  if (ConfigAccessHandle == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // find controller handles managed by the component name handle.
  //
  Status = gtBS->HandleProtocol (
                   ConfigAccessHandle,
                   &gBlackBoxEfiDevicePathProtocolGuid,
                   (void **)&DevicePath
                   );

  //
  // Convert the device path binary to hex UNICODE %02x bytes in the same order
  // as the device path resides in RAM memory.
  //
  Length = EfiDevicePathSize (DevicePath);
  PathHdrSize = (Length * 2 + 1) * sizeof (CHAR16);
  *DevicePathStr = (EFI_STRING) SctAllocateZeroPool (PathHdrSize);
  if (*DevicePathStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status = BufToHexStringPrivate (*DevicePathStr, &PathHdrSize, (UINT8 *) DevicePath, Length, TRUE);

  return Status;
}


EFI_STATUS
GetCorrespondingRequest (
  IN     EFI_STRING    MultiConfigAltResp,
  IN     EFI_STRING    DevicePath,
  IN OUT EFI_STRING    Request
  )
{
  EFI_STRING    RespPtr;
  EFI_STRING    ReqPtr;
  EFI_STRING    SingleResp;
  EFI_STRING    SingleRespPtr;
  UINTN         Len;
  
  ReqPtr = Request;
  RespPtr = MultiConfigAltResp;

  Len = SctStrLen (MultiConfigAltResp);
  
  if (SctStrnCmp (MultiConfigAltResp, L"GUID=", 5) != 0) {
    return EFI_INVALID_PARAMETER;
  }
  
  if (SctStrStr (MultiConfigAltResp, DevicePath) == NULL) {
    return EFI_NOT_FOUND;
  }

  SingleResp = (EFI_STRING) SctAllocateZeroPool ( 2 * SctStrLen (MultiConfigAltResp) + 2 );
  if (SingleResp == NULL) {
	return EFI_OUT_OF_RESOURCES;
  }
  SingleRespPtr = SingleResp;

  while (*MultiConfigAltResp != 0) {
    while ((*MultiConfigAltResp != 0) && (SctStrnCmp (MultiConfigAltResp, L"&GUID=", 6) != 0)) {
      *(SingleResp++) = *(MultiConfigAltResp++);
    }
	SingleResp = SingleRespPtr;
	if (SctStrStr (SingleResp, DevicePath) != NULL)
      break;
	SctZeroMem (SingleRespPtr, 2 * Len + 2);
	if (*MultiConfigAltResp != 0)
      MultiConfigAltResp++;
  }

  if (SctStrStr (SingleResp, DevicePath) == NULL)
  	return EFI_NOT_FOUND;

  if (SctStrStr (SingleResp, L"VALUE=") == NULL){
    while (*SingleResp != 0) {
      while ((*SingleResp != 0) && (SctStrnCmp (SingleResp, L"&PATH=", 6) != 0)) {
        *(Request++) = *(SingleResp++);
	  }
	  *(Request++) = *(SingleResp++);
	  while ((*SingleResp != 0) && (*SingleResp != L'&')) {
        *(Request++) = *(SingleResp++);
      }
	  while (*SingleResp != 0){
        if (*SingleResp != L'=') {
          *(Request++) = *(SingleResp++);
		} else {
          while ((*SingleResp != 0) && (*SingleResp != L'&')) {
            SingleResp++;
          }
        }
      }
    }
  } else {
    while (*SingleResp != 0) {
      while ((*SingleResp != 0) && (SctStrnCmp (SingleResp, L"&VALUE=", 7)) != 0) {
        *(Request++) = *(SingleResp++);
      }
	  SingleResp++;
	  while ((*SingleResp != 0) && (*SingleResp != L'&'))
        SingleResp++;
    }

  }

  *Request = 0;

  gtBS->FreePool (SingleRespPtr);
  return EFI_SUCCESS;
}


EFI_STATUS
GetCorrespondingResp (
  IN     EFI_STRING    MultiConfigAltResp,
  IN     EFI_STRING    DevicePath,
  IN OUT EFI_STRING    Resp
  )
{
  EFI_STRING    RespPtr;
  EFI_STRING    ReqPtr;
  UINTN         Len;
  
  ReqPtr = Resp;
  RespPtr = MultiConfigAltResp;

  Len = SctStrLen (MultiConfigAltResp);
  
  if (SctStrnCmp (MultiConfigAltResp, L"GUID=", 5) != 0) {
    return EFI_INVALID_PARAMETER;
  }
  
  if (SctStrStr (MultiConfigAltResp, DevicePath) == NULL) {
    return EFI_NOT_FOUND;
  }

  while (*MultiConfigAltResp != 0) {
    while ((*MultiConfigAltResp != 0) && (SctStrnCmp (MultiConfigAltResp, L"&GUID=", 6) != 0)) {
      *(Resp++) = *(MultiConfigAltResp++);
    }
	Resp = ReqPtr;
	if (SctStrStr (Resp, DevicePath) != NULL)
      break;
	SctZeroMem (ReqPtr, 2 * Len + 2);
	if (*MultiConfigAltResp != 0)
      MultiConfigAltResp++;
  }

  if (SctStrStr (Resp, DevicePath) == NULL)
  	return EFI_NOT_FOUND;
  
  return EFI_SUCCESS;
}



EFI_STATUS
GetHIIConfigRoutingInterface (
  OUT EFI_HII_CONFIG_ROUTING_PROTOCOL    **HIIConfigRouting
  )
{
  UINTN                                 NoHandles;
  EFI_HANDLE                            *HandleBuffer;
  EFI_STATUS                            Status;
  
  //
  // Get the HII Database Protocol interface
  //
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &gBlackBoxEfiHIIConfigRoutingProtocolGuid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if ( EFI_ERROR(Status) ) {
    return Status;
  }
  
  if ( NoHandles <= 0 ) {
    return EFI_DEVICE_ERROR;
  }
  
  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gBlackBoxEfiHIIConfigRoutingProtocolGuid,
                   (VOID **) HIIConfigRouting
                   );
  if ( EFI_ERROR(Status) ) {
    gtBS->FreePool ( HandleBuffer );
    return Status;
  }
  
  gtBS->FreePool ( HandleBuffer );
  
  return EFI_SUCCESS;
}

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
