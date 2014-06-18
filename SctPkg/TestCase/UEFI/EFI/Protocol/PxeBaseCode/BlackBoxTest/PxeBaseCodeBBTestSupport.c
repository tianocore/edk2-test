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

  PxeBaseCodeBBTestSupport.c

Abstract:

  Common function used in PXE Base Code test.

--*/
#include "SctLib.h"
#include "PxeBaseCodeBBTestMain.h"
#include "PxeBaseCodeBBTestSupport.h"

EFI_DEVICE_PATH_PROTOCOL        *gDevicePath     = NULL;
CHAR16                          *gFilePath       = NULL;

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
  IN  EFI_HANDLE                          SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL  **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL   **ProfileLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL   **LoggingLib
  )
{
  EFI_STATUS            Status;

  //
  // Get the standard test support library interface
  //
  if (NULL != StandardLib)
  {
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
  if (NULL != ProfileLib)
  {
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
  // Get the test profile support library interface
  //
  if (NULL != LoggingLib)
  {
    *LoggingLib = NULL;
    Status = gtBS->HandleProtocol (
                     SupportHandle,
                     &gEfiTestLoggingLibraryGuid,
                     LoggingLib
                     );
    if (EFI_ERROR(Status)) {
      return Status;
    }
  }
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
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  )
{
  CHAR16     *FilePath;
  EFI_STATUS Status;

  FilePath = NULL;
  FilePath = SctPoolPrint (L"%s\\%s", gFilePath, PXE_BC_TEST_INI_FILE);

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
 *  get the device path and file path.
 *  @param ImageHandle the Image Handle instance.
 *  @return EFI_SUCCESS the device path and file path were gotten successfully.
 */
EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  )
{
  EFI_STATUS                  Status;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  CHAR16                      *TempFilePath;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib;

  //
  // Use profile lib at here just for less effect on the current system. It is
  // dependent on the implementation of test framework. So need to be updated
  // later.
  //
  Status = gtBS->LocateProtocol (
                   &gEfiTestProfileLibraryGuid,
                   NULL,
                   &ProfileLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the system device path and file path
  //
  Status = ProfileLib->EfiGetSystemDevicePath (
                         ProfileLib,
                         &TempDevicePath,
                         &TempFilePath
                         );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  //make up the file path.
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

/**
 *  Support Function - Close the test ini file.
 *  @param ProfileLib    A pointer to EFI_TEST_PROFILE_LIBRARY_PROTOCOL
 *                        instance.
 *  @param FileHandle the ini File Handle to be closed.
 *  @return EFI_SUCCESS.
 */
EFI_STATUS
CloseTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                FileHandle
  )
{
 return ProfileLib->EfiIniClose (
                      ProfileLib,
                      FileHandle
                      );

}
/**
 *  get the Invalid Base Address from the profile.
 *  @param FileHandle the EFI_INI_FILE_HANDLE instance.
 *  @param SectionName the Section Name string pointer.
 *  @param ItemName: the Item Name string pointer.
 *  @param Ip: returned EFI_IP_ADDRESS instance.
 *  @return EFI_SUCCESS the Invalid Address was get successfully.
 */
EFI_STATUS
GetIpAddrFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT EFI_IP_ADDRESS        *Ip
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;
  CHAR16*         Addr[4];
  UINTN           i, j, Len;

  if (SectionName == NULL || ItemName == NULL || Ip == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = L'\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status))
    return Status;

  //NP_Print (L"Buffer: %s\n", Buffer);

  i = 0;
  Addr[i] = Buffer;
  Len = SctStrLen (Buffer);
  for (j=1; j < Len; j++)
  {
    //NP_Print (L"i=%d, Buffer[%d]=%c\n", i, j, Buffer[j]);
    if (Buffer[j] == L'.')
    {
      i++;
      if (i<4)
      {
        NP_Print (L"i=%d \n", i);
        Addr[i] = Buffer + j + 1;
        Buffer[j] = L'\0';
      } else {
        SctPrint (L"i=%d \n", i);
        return EFI_INVALID_PARAMETER;
      }
    }
  }

  if (i==3)
  {
    NP_Print (L"i=%d, Addr[0]=%s, Addr[1]=%s, Addr[2]=%s, Addr[3]=%s\n",
              i, Addr[0], Addr[1], Addr[2], Addr[3]);
    Ip->v4.Addr[0] = (UINT8)SctAtoi (Addr[0]);
    Ip->v4.Addr[1] = (UINT8)SctAtoi (Addr[1]);
    Ip->v4.Addr[2] = (UINT8)SctAtoi (Addr[2]);
    Ip->v4.Addr[3] = (UINT8)SctAtoi (Addr[3]);

    return EFI_SUCCESS;
  }

  return EFI_INVALID_PARAMETER; // ip address must be in the format of XX.XX.XX.XX
}

EFI_STATUS
GetBooleanVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT BOOLEAN               *Val
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || ItemName== NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  if (SctStriCmp (Buffer, L"TRUE"))
    *Val = FALSE;
  else
    *Val = TRUE;

  return EFI_SUCCESS;
}

EFI_STATUS
GetUINT32VarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT32                *Val
  )
{
  CHAR16          Buffer[MAX_STRING_LEN];
  EFI_STATUS      Status;
  UINT32          MaxLen;


  if (SectionName == NULL || ItemName== NULL || Val ==NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         (UINT32 *)&MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  *Val = STR_TO_INT (Buffer);

  NP_Print (L"Val: %d\n", *Val);

  return EFI_SUCCESS;
}

EFI_STATUS
GetUINTNVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINTN                 *Val
  )
{
  return GetUINT32VarFromFile (FileHandle, SectionName, ItemName, 0, (UINT32*)Val);;
}

EFI_STATUS
GetUINT16ValFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT16                *Val
  )
{
  EFI_STATUS Status;
  UINTN TempData;

  Status = GetUINTNVarFromFile (FileHandle, SectionName, ItemName, 0, &TempData);
  if (EFI_ERROR(Status))
    return Status;

  *Val = (UINT16)TempData;
  return EFI_SUCCESS;
}

EFI_STATUS
GetUdpPortFromFile (
  IN  EFI_INI_FILE_HANDLE           FileHandle,
  IN  CHAR16                        *SectionName,
  IN  CHAR16                        *ItemName,
  IN  UINT32                        Order,
  OUT EFI_PXE_BASE_CODE_UDP_PORT    *Val
  )
{
  return GetUINT16ValFromFile (FileHandle, SectionName, ItemName, 0, Val);
}

EFI_STATUS
GetAsciiStringFromFile (
  IN     EFI_INI_FILE_HANDLE    FileHandle,
  IN     CHAR16                 *SectionName,
  IN     CHAR16                 *ItemName,
  IN     UINT32                 Order,
  IN OUT CHAR8                  **String
  )
{
  CHAR16              Buffer[MAX_STRING_LEN];
  EFI_STATUS          Status;
  UINT32              MaxLen;
  CHAR8*              TempStr;
  UINTN               i;

  if (SectionName == NULL || ItemName == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         &MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  // Allocate Pool
  TempStr = NULL;
  TempStr = SctAllocatePool (SctStrLen (Buffer)+1);
  if (TempStr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  for (i=0; i< SctStrLen (Buffer);i++)
  {
    TempStr[i] = (CHAR8)(Buffer[i]);
    NP_Print (L"%c", TempStr[i]);
  }
  TempStr[i] = '\0';
  *String = TempStr;

  SctPrint (L"\n");
  return EFI_SUCCESS;
}

EFI_STATUS
GetUnicodeStringFromFile (
  IN      EFI_INI_FILE_HANDLE   FileHandle,
  IN      CHAR16                *SectionName,
  IN      CHAR16                *ItemName,
  IN      UINT32                Order,
  IN OUT  CHAR16                **String
  )
{
  CHAR16              Buffer[MAX_STRING_LEN];
  EFI_STATUS          Status;
  UINT32              MaxLen;
  CHAR16             *TempStr;

  if (SectionName == NULL || ItemName == NULL || String == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         &MaxLen
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

  *String = TempStr;

  return EFI_SUCCESS;
}

EFI_STATUS
GetRawDataFromFile (
  IN      EFI_INI_FILE_HANDLE FileHandle,
  IN      CHAR16              *SectionName,
  IN      CHAR16              *ItemName,
  IN      UINT32              Order,
  IN OUT  UINTN               *BufferSize,
  IN OUT  VOID                *BufferPtr
)
{
  CHAR16            Buffer[MAX_STRING_LEN];
  EFI_STATUS        Status;
  UINT32            MaxLen;
  UINTN             i;
  CHAR16            TempData[3];
  UINT8             TempVal, *TempPtr;

  if (SectionName == NULL || ItemName == NULL || BufferPtr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MaxLen    = MAX_STRING_LEN;
  Buffer[0] = '\0';

  Status = FileHandle->GetStringByOrder (
                         FileHandle,
                         (UINT32)Order,
                         SectionName,
                         ItemName,
                         Buffer,
                         &MaxLen
                         );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  if (SctStrLen (Buffer) == 0) {
    return EFI_NOT_FOUND;
  }

  TempData[2]='\0';
  TempPtr = BufferPtr;
  for (i=0;i<SctStrLen (Buffer);i+=2)
  {
    TempData[0] = Buffer[i];
    TempData[1] = Buffer[i+1];
    TempVal = (UINT8)(SctXtoi (TempData));
    TempPtr[i/2] = TempVal;
    NP_Print (L"TempPtr[%d]=%d\n", i/2, TempPtr[i/2]);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ReadMtftpFile (
  IN OUT VOID   **Buffer,
  IN OUT UINTN  *Size
  )
{
  return EFI_SUCCESS;
}

