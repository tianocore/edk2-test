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

  CpuIoBBTestSupport.h

Abstract:

  BB test support head file of Cpu Io Interface.

--*/

#ifndef _PXE_BASE_CODE_BBTEST_SUPPORT_H
#define _PXE_BASE_CODE_BBTEST_SUPPORT_H

#define MAX_STRING_LEN                256
#define DEPENDECY_DIR_NAME            L"dependency\\PxeBaseCodeBBTest"
#define PXE_BC_TEST_INI_FILE          L"PxeBaseCodeBBTest.ini"

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;

#define STR_TO_UINT8(Buffer) \
        1 ? \
        (UINT8)(SctXtoi (Buffer)) : (UINT8)(SctAtoi (Buffer))

#define STR_TO_INT(Buffer) \
        (Buffer[0] == '0' && ((Buffer[1] == 'x') || (Buffer[1] == 'X'))) ? \
        (UINT32)SctXtoi (Buffer) : (UINT32)SctAtoi (Buffer)

//
//suppot function protypes.
//

EFI_STATUS
GetTestSupportLibrary (
  IN  EFI_HANDLE                            SupportHandle,
  OUT EFI_STANDARD_TEST_LIBRARY_PROTOCOL    **StandardLib,
  OUT EFI_TEST_PROFILE_LIBRARY_PROTOCOL     **ProfileLib,
  OUT EFI_TEST_LOGGING_LIBRARY_PROTOCOL     **LoggingLib
  );

EFI_STATUS
GetSystemDevicePathAndFilePath (
  IN EFI_HANDLE           ImageHandle
  );

EFI_STATUS
OpenTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                *FileHandle
  );

EFI_STATUS
CloseTestIniFile (
  IN   EFI_TEST_PROFILE_LIBRARY_PROTOCOL  *ProfileLib,
  OUT  EFI_INI_FILE_HANDLE                FileHandle
  );

EFI_STATUS
GetIpAddrFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT EFI_IP_ADDRESS        *Ip
  );

EFI_STATUS
GetBooleanVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT BOOLEAN               *Val
  );

EFI_STATUS
GetUINTNVarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINTN*                Val
  );

EFI_STATUS
GetUINT32VarFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT32                *Val
  );

EFI_STATUS
GetUINT16ValFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT UINT16                *Val
  );

EFI_STATUS
GetUdpPortFromFile (
  IN  EFI_INI_FILE_HANDLE           FileHandle,
  IN  CHAR16                        *SectionName,
  IN  CHAR16                        *ItemName,
  IN  UINT32                        Order,
  OUT EFI_PXE_BASE_CODE_UDP_PORT*   Val
  );

EFI_STATUS
GetUnicodeStringFromFile (
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT CHAR16                **String
  );

EFI_STATUS
GetAsciiStringFromFile(
  IN  EFI_INI_FILE_HANDLE   FileHandle,
  IN  CHAR16                *SectionName,
  IN  CHAR16                *ItemName,
  IN  UINT32                Order,
  OUT CHAR8                 **String
  );

EFI_STATUS
GetRawDataFromFile (
  IN     EFI_INI_FILE_HANDLE  FileHandle,
  IN     CHAR16               *SectionName,
  IN     CHAR16               *ItemName,
  IN     UINT32               Order,
  IN OUT UINTN                *BufferSize,
  IN OUT VOID                 *BufferPtr
);

EFI_STATUS
ReadMtftpFile (
  IN OUT VOID   **Buffer,
  IN OUT UINTN  *Size
  );

#endif
