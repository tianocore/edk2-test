/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DeviceIoBBTestSupport.c

Abstract:

  BB test support source file of Device Io Interface.

--*/

#include "SctLib.h"
#include "DeviceIoBBTestMain.h"
#include "DeviceIoBBTestSupport.h"

EFI_DEVICE_PATH_PROTOCOL        *gDevicePath     = NULL;
CHAR16                          *gFilePath       = NULL;
DEVIO_DEVICE                    *gDevIoDevices   = NULL;
UINTN                           gDevIoDevNumber  = 0;
EFI_HANDLE                      gDeviceHandle ;
static BOOLEAN                  mInitialized = FALSE;

//
//WidthCode String
//

WIDTHCODE  WidthCode[]  = {
  L"IO_UINT8",
  L"IO_UINT16",
  L"IO_UINT32",
  L"IO_UINT64",
  L"MMIO_COPY_UINT8",
  L"MMIO_COPY_UINT16",
  L"MMIO_COPY_UINT32",
  L"MMIO_COPY_UINT64",
  L"IO_MAXIMUM"
};

//
//test support functions.
//
EFI_STATUS
InitializeSupportEnvironment (
  VOID
  )
{
  if (mInitialized) {
    return EFI_SUCCESS;
  } else {

    CreateAllDevIoDevices ();
    mInitialized = TRUE;
    return EFI_SUCCESS;
  }
}

/**
 *  create all the Dev Io Devices in this system.
 *  @return EFI_SUCCESS the all the devices were gotten successfully.
 */
EFI_STATUS
CreateAllDevIoDevices (
  VOID
  )
{
  EFI_STATUS                          Status;
  UINTN                                HandleNum;
  EFI_HANDLE                          *HandleBuffer;
  EFI_DEVICE_IO_PROTOCOL              *DeviceIo;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  UINTN                               Index;


  //
  //get all Device Io Protocol Interface.
  //

  HandleNum     = 0;
  HandleBuffer = NULL;

  Status      = SctLocateHandle (
                  ByProtocol,
                  &gBlackBoxEfiDeviceIoProtocolGuid,
                  NULL,
                  &HandleNum,
                  &HandleBuffer
                  );

  if (EFI_ERROR(Status) || HandleNum == 0) {
    return EFI_ABORTED;
  }

  gDevIoDevices = (DEVIO_DEVICE *)SctAllocateZeroPool (
                                    sizeof (DEVIO_DEVICE) * HandleNum
                                    );

  if (gDevIoDevices == NULL) {
    SctFreePool (HandleBuffer);
    return EFI_OUT_OF_RESOURCES;
  }

  for (Index = 0; Index < HandleNum; Index++) {

    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gBlackBoxEfiDeviceIoProtocolGuid,
                     &DeviceIo
                     );

    if (EFI_ERROR(Status)) {
      SctFreePool (HandleBuffer);
      SctFreePool (gDevIoDevices);
      return Status;
    }

    gDevIoDevices[Index].DeviceIo = DeviceIo;

    Status = gtBS->HandleProtocol (
                     HandleBuffer[Index],
                     &gEfiDevicePathProtocolGuid,
                     &DevicePath
                     );

    if (EFI_ERROR(Status)) {
      SctFreePool (HandleBuffer);
      SctFreePool (gDevIoDevices);
      return Status;
    }

    gDevIoDevices[Index].DevicePath = DevicePath;
  }
  SctPrint (L"found %d DeviceIo interface.", HandleNum);

  gDevIoDevNumber = HandleNum;

  SctFreePool (HandleBuffer);

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}

/**
 *  Print the Device Path and return it if DevPathStr not NULL.
 *  @param DevIo the device Io protocol instance pointer.
 *  @param DevPathStr the returned Device Path String pointer.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
GetDevIoDevicePathStr (
  IN  EFI_DEVICE_IO_PROTOCOL  *DevIo,
  IN  CHAR16                  **DevPathStr OPTIONAL
  )
{
  UINTN            Index;
  DEVIO_DEVICE     *Dev;
  CHAR16           *TempStr;

  TempStr = NULL;
  Dev     = NULL;

  for (Index = 0; Index < gDevIoDevNumber; Index++) {
    if (gDevIoDevices[Index].DeviceIo == DevIo) {
      Dev = &gDevIoDevices[Index];
      break;
    }
  }

  if (Dev == NULL) {
    return EFI_NOT_FOUND;
  }

  TempStr = SctDevicePathToStr (Dev->DevicePath);

  if (TempStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //print the device path.
  //

  gtST->ConOut->OutputString (gtST->ConOut, L"This DevIo Device Path:\r\n");
  gtST->ConOut->OutputString (gtST->ConOut, TempStr);
  gtST->ConOut->OutputString (gtST->ConOut, L"\r\n");

  if (DevPathStr != NULL) {
    *DevPathStr = TempStr;
    return EFI_SUCCESS;
  } else {
    gtBS->FreePool (TempStr);
    return EFI_SUCCESS;
  }
}

/**
 *  Support function - Get test support protocol library.
 *  @param SupportHandle  A handle containing support protocols.
 *  @param StandardLib    A pointer to Standard Test Support Protocol.
 *  @param ProfileLib    A pointer to Test Profile Support Protocol.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
GetTestSupportLibrary (
  IN EFI_HANDLE                           SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL  **ProfileLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  if (StandardLib != NULL) {
    *StandardLib = NULL;
    Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiStandardTestLibraryGuid,
                     StandardLib
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  // Get the test profile support library interface
  //
  if (ProfileLib != NULL) {
    *ProfileLib = NULL;
    Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiTestProfileLibraryGuid,
                     ProfileLib
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
  //
  // Done
  //
  return EFI_SUCCESS;
}


/**
 *  Support function - Open Cpu IO Test .ini file.
 *  @param ProfileLib    A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @param FileHandle     A pointer to EFI_INI_FILE_HANDLE instance.
 *  @return EFI_SUCCESS   Successfully.
 *  @return Other value   Something failed.
 */
EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  )
{
  CHAR16     *FilePath;
  EFI_STATUS Status;

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, DEVICE_IO_TEST_INI_FILE);

  if (FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  //open the profile.
  //
  Status =ProfileLib->EfiIniOpen (
                        ProfileLib,
                        gDevicePath,
                        FilePath,
                        FileHandle
                        );

  //
  //free the file path not to be used.
  //

  gtBS->FreePool (FilePath);

  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //done successfully.
  //
  return EFI_SUCCESS;
}

/**
 *  Support Function - Close the test ini file.
 *  @param ProfileLib    A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @param FileHandle the ini File Handle to be closed.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
CloseTestIniFile (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                FileHandle
  )
{
 return ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );

}

EFI_STATUS
GetSystemDevicePathStrByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT CHAR16              **DevicePathStr
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  CHAR16          *TempStr;

  if (SectionName == NULL || DevicePathStr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DevicePath",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  TempStr = NULL;
  TempStr = SctStrDuplicate (Buffer);
  if (TempStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  *DevicePathStr = TempStr;

  return EFI_SUCCESS;
}


/**
 *  get the Valid Base Address from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param Address the returned Base Address.
 *  @return EFI_SUCCESS the Address was get successfully.
 */
EFI_STATUS
GetValidBaseAddressByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *Address
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || Address == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"ValidBaseAddress",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  (UINT64)(*Address) = XToUint64 (Buffer);

  return EFI_SUCCESS;
}

/**
 *  get the Invalid Base Address from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param Address the returned Invalid Base Address for this system.
 *  @return EFI_SUCCESS the Invalid Address was get successfully.
 */
EFI_STATUS
GetInvalidBaseAddressByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT64              *Address
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || Address == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"InvalidBaseAddress",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  *Address = (UINT64)XToUint64 (Buffer);

  return EFI_SUCCESS;
}

/**
 *  get the Address Length from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param AddressLength the returned Address Length.
 *  @return EFI_SUCCESS the Address Length was get successfully.
 */
EFI_STATUS
GetAddressLengthByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  OUT UINT32              *AddressLength
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || AddressLength == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"Length",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  *AddressLength = (UINT32)SctXtoi (Buffer);

  return EFI_SUCCESS;
}

/**
 *  get the Valid Efi Io Width from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param EfiIoWidth the returned EFI_IO_WIDTH.
 *  @return EFI_SUCCESS the Cpu Io Width was gotten successfully.
 */
EFI_STATUS
GetValidEfiIoWidthByFile (
  IN EFI_INI_FILE_HANDLE          FileHandle,
  IN CHAR16                       *SectionName,
  IN UINTN                        Order,
  OUT EFI_IO_WIDTH                *EfiIoWidth
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  UINTN           Index;

  if (SectionName == NULL || EfiIoWidth == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"ValidEfiIoWidth",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index <= IO_UINT64; Index++) {
    if (SctStriCmp (WidthCode[Index], Buffer) == 0) {
      *EfiIoWidth = (EFI_IO_WIDTH)Index;
      return EFI_SUCCESS;
    }
  }

  //
  //not found
  //
  return EFI_NOT_FOUND;
}

/**
 *  get the Invalid Efi Io Width from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param EfiIoWidth the returned EFI_IO_WIDTH.
 *  @return EFI_SUCCESS the Cpu Io Width was gotten successfully.
 */
EFI_STATUS
GetInvalidEfiIoWidthByFile (
  IN EFI_INI_FILE_HANDLE          FileHandle,
  IN CHAR16                       *SectionName,
  IN UINTN                        Order,
  OUT EFI_IO_WIDTH                *EfiIoWidth
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  UINTN           Index;

  if (SectionName == NULL || EfiIoWidth == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"InvalidEfiIoWidth",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  for (Index = 0; Index <= IO_UINT64; Index++) {
    if (SctStriCmp (WidthCode[Index], Buffer) == 0) {
      *EfiIoWidth = (EFI_IO_WIDTH)Index;
      return EFI_SUCCESS;
    }
  }

  //
  //not found
  //
  return EFI_NOT_FOUND;
}

/*

 *  get the system device path and file path.

 *  @param ProfileLib the Profile Library Protocol instance.

 *  @return EFI_SUCCESS the system device path and file path were gotten successfully.

 */

EFI_STATUS
GetSystemData (
  IN EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  CHAR16                      *TempFilePath;
  EFI_STATUS                  Status;

  //
  // If gFilePath and gDevicePath has been assigned, return directly.
  //
  if ((gFilePath != NULL) && (gDevicePath != NULL)) {
    return EFI_SUCCESS;
  }

  //
  // Free gFilePath or gDevicePath
  //
  if (gFilePath != NULL) {
    gtBS->FreePool (gFilePath);
    gFilePath = NULL;
  }

  if (gDevicePath != NULL) {
    gtBS->FreePool (gDevicePath);
    gDevicePath = NULL;
  }

  //
  //Get system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &TempDevicePath,
                         &TempFilePath
                         );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // make up the file path.
  //
  gFilePath = NULL;
  gFilePath = SctPoolPrint (L"%s\\%s", TempFilePath, DEPENDECY_DIR_NAME);
  gtBS->FreePool (TempFilePath);
  if (gFilePath == NULL) {
    gtBS->FreePool (TempDevicePath);
    return EFI_OUT_OF_RESOURCES;
  }

  gDevicePath = TempDevicePath;
  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}


/*

 *  get the device handle.

 *  @param ImageHandle the Image Handle instance.

 *  @return EFI_SUCCESS the device handle was gotten successfully.

 */

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  )
{

  EFI_STATUS                  Status;
  EFI_LOADED_IMAGE_PROTOCOL   *Image;

  //
  // Get the image instance from the image handle
  //
  Status = gtBS->HandleProtocol (
                   ImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   &Image
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  gDeviceHandle = Image->DeviceHandle;

  //
  // Done, return status code EFI_SUCCESS
  //
  return EFI_SUCCESS;
}


/**
 *  get the Data Units from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param Order the order of the section.
 *  @param Length the Data Units Length.
 *  @param DataUnits returned Data Units pointer.
 *  @return EFI_SUCCESS the DataUnits was get successfully.
 */
EFI_STATUS
GetDataUnitsByFile (
  IN EFI_INI_FILE_HANDLE  FileHandle,
  IN CHAR16               *SectionName,
  IN UINTN                Order,
  UINTN                   Length,
  OUT UINT8               **DataUnits
  )
{
  CHAR16          Buffer[1024];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  UINT8           *ReturnBuffer;

  if (SectionName == NULL || DataUnits == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  MaxLen    = 1024;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         L"DataUnits",
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }
  ReturnBuffer = NULL;

  Status = ConvertStringToHex (
             Buffer,
             (UINT32)Length,
             &ReturnBuffer
             );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  *DataUnits = ReturnBuffer;

  return EFI_SUCCESS;
}

/**
 *  convert the sring value into hex value.
 *  @param SrcBuffer the input string buffer.
 *  @param Length return buffer length
 *  @param RetBuffer the return Buffer pointer.
 *  @return EFI_SUCCESS the string was converted into hex value successfully.
 */
EFI_STATUS
ConvertStringToHex (
  IN CHAR16             *SrcBuffer,
  IN UINT32             Length,
  OUT UINT8             **RetBuffer
  )
{
  UINTN               Index;
  UINTN               ConvertBytes;
  CHAR16              Buffer[4];
  UINT8               *TempBuffer;
  CHAR16              *StrPtr;

  if (SrcBuffer == NULL || RetBuffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  StrPtr = SrcBuffer;

  //
  //skip the space if it really has.
  //

  while (*StrPtr == L' ') {
    StrPtr = StrPtr + 1;
  }

  //
  //skip the "0x" prefix if it really has.
  //

  if (SctStrLen (StrPtr) >= 2) {
    if (StrPtr[0] == L'0' && (StrPtr[1] == L'x' || StrPtr[1] == L'X')) {
      StrPtr = StrPtr + 2;
    }
  }

  ConvertBytes = SctStrLen (StrPtr) / 2;
  if (ConvertBytes > Length) {
    ConvertBytes = Length;
  }

  TempBuffer = NULL;
  TempBuffer = SctAllocatePool (Length);
  if (TempBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Buffer[2] =0x00;

  //
  //convert string to hex value.
  //

  for (Index = 0; Index < ConvertBytes; Index++) {
    Buffer[0] = StrPtr[Index * 2];
    Buffer[1] = StrPtr[Index * 2 + 1];
    TempBuffer[Index] = (UINT8) XToUint64 (Buffer);
  }

  if (ConvertBytes < Length) {
    for (Index = ConvertBytes; Index < Length; Index++) {
      TempBuffer[Index] = (UINT8) (Index & 0xFF);
    }
  }

  *RetBuffer = TempBuffer;

  return EFI_SUCCESS;
}


/**
 *  caculate UINT64 from a string.
 *  @param str the String to be parsed.
 *  @return Caculate UINT64 Value.
 */
UINT64
XToUint64 (
  IN CHAR16  *str
  )
{
  UINT64      U64;
  CHAR16      Char;

  //
  //skip preceeding white space
  //
  while (*str && *str == ' ') {
      str += 1;
  }

  //
  // skip preceeding zeros
  //
  while (*str && *str == '0') {
    str += 1;
  }

  //
  // skip preceeding white space
  //
  if (*str && (*str == 'x' || *str == 'X')) {
    str += 1;
  }

  //
  // convert hex digits
  //
  U64 = 0;
  Char = *(str++);
  while (Char) {
    if (Char >= 'a'  &&  Char <= 'f') {
      Char -= 'a' - 'A';
    }

    if ((Char >= '0'  &&  Char <= '9')  ||  (Char >= 'A'  &&  Char <= 'F')) {
      U64 = SctLShiftU64 (U64, 4)  |  Char - (Char >= 'A' ? 'A'-10 : '0');
    } else {
      break;
    }
    Char = *(str++);
  }

  return U64;
}
