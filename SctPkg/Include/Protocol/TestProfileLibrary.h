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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestProfileLibrary.h

Abstract:

  This file defines the EFI Test Profile Library Protocol.

--*/

#ifndef _EFI_TEST_PROFILE_LIBRARY_H_
#define _EFI_TEST_PROFILE_LIBRARY_H_

//
// Includes
//

#include EFI_PROTOCOL_DEFINITION (DevicePath)

//
// EFI Test Profile Library Protocol Definitions
//

#define EFI_TEST_PROFILE_LIBRARY_GUID       \
  { 0x832c9023, 0x8e67, 0x453f, 0x83, 0xea, 0xdf, 0x71, 0x05, 0xfa, 0x74, 0x66 }

#define EFI_TEST_PROFILE_LIBRARY_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_INI_FILE EFI_INI_FILE;
typedef struct _EFI_TEST_PROFILE_LIBRARY_PROTOCOL EFI_TEST_PROFILE_LIBRARY_PROTOCOL;
typedef struct _EFI_INI_FILE *EFI_INI_FILE_HANDLE;



//
// EFI INI File API - Flush
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_FLUSH) (
  IN  EFI_INI_FILE                      *This
  )
/*++

Routine Description:

  Flushes all modified data associated with the INI file to the storage device.
  Remember to invoke this function before of system reset if some modified data
  was not flushed.

Arguments:

  This          - EFI_INI_FILE protocol instance.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetString
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETSTRING) (
  IN     EFI_INI_FILE                   *This,
  IN     CHAR16                         *Section,
  IN     CHAR16                         *Entry,
     OUT CHAR16                         *String,
  IN OUT UINT32                         *MaxLength
  )
/*++

Routine Description:

  Reads a Unicode string from the specific section and entry in the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string which is read.

  MaxLength     - On input, the length of the Unicode string. On output, the
                  length of string returned in String.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - SetString
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_SETSTRING) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section,
  IN  CHAR16                            *Entry,
  IN  CHAR16                            *String
  )
/*++

Routine Description:

  Writes a Unicode string to the specific section and entry in the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - RmSection
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_RMSECTION) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section
  )
/*++

Routine Description:

  Removes a section from the INI file.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetStringByOrder
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETSTRING_BYORDER) (
  IN     EFI_INI_FILE                   *This,
  IN     UINT32                         Order,
  IN     CHAR16                         *Section,
  IN     CHAR16                         *Entry,
     OUT CHAR16                         *String,
  IN OUT UINT32                         *MaxLength
  )
/*++

Routine Description:

  Reads a Unicode string from the specific section and entry in the INI file. It
  can be used to deal with more than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be read. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string which is read.

  MaxLength     - On input, the length of the Unicode string. On output, the
                  length of string returned in String.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - SetStringByOrder
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_SETSTRING_BYORDER) (
  IN  EFI_INI_FILE                      *This,
  IN  UINT32                            Order,
  IN  CHAR16                            *Section,
  IN  CHAR16                            *Entry,
  IN  CHAR16                            *String
  )
/*++

Routine Description:

  Writes a Unicode string to the specific section and entry in the INI file. It
  can be used to deal with more than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be written. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

  Entry         - The Null-terminated Unicode string of entry name.

  String        - The Null-terminated Unicode string to be written.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - RmSectionByOrder
typedef
EFI_STATUS
(EFIAPI *EFI_INI_RMSECTION_BYORDER) (
  IN  EFI_INI_FILE                      *This,
  IN  UINT32                            Order,
  IN  CHAR16                            *Section
  )
/*++

Routine Description:

  Removes a section from the INI file. It can be used to deal with more than
  one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Order         - The index of section to be removed. 0 stands for the first
                  section.

  Section       - The Null-terminated Unicode string of section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File API - GetOrderNum
//
typedef
EFI_STATUS
(EFIAPI *EFI_INI_GETORDERNUM) (
  IN  EFI_INI_FILE                      *This,
  IN  CHAR16                            *Section,
  OUT UINT32                            *OrderNum
  )
/*++

Routine Description:

  Gets the number of sections in the input name. It is used when there are more
  than one section with same name.

Arguments:

  This          - EFI_INI_FILE protocol instance.

  Section       - The Null-terminated Unicode string of section name.

  OrderNum      - The number of sections with this section name.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI INI File
//

struct _EFI_INI_FILE {
  UINT64                                Revision;
  EFI_INI_GETSTRING                     GetString;
  EFI_INI_SETSTRING                     SetString;
  EFI_INI_RMSECTION                     RmSection;
  EFI_INI_GETSTRING_BYORDER             GetStringByOrder;
  EFI_INI_SETSTRING_BYORDER             SetStringByOrder;
  EFI_INI_RMSECTION_BYORDER             RmSectionByOrder;
  EFI_INI_GETORDERNUM                   GetOrderNum;
  EFI_INI_FLUSH                         Flush;
};

//
// EFI Test Profile Library Protocol API - IniOpen
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_OPEN) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  OUT EFI_INI_FILE                              **FileHandle
  )
/*++

Routine Description:

  Opens an INI file.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the file to be opened.

  FileName      - The name of the file to be opened.

  FileHandle    - The pointer to the opened file handle.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - IniCreate
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_CREATE) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FileName,
  OUT EFI_INI_FILE                              **FileHandle
  )
/*++

Routine Description:

  Creates an INI file.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the file to be created.

  FileName      - The name of the file to be created.

  FileHandle    - The pointer to the opened file handle.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - IniFlush
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_FLUSH) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_INI_FILE                              *FileHandle
  )
/*++

Routine Description:

  Flush an INI file.

Arguments:

  This          - Test profile library protocol instance.

  FileHandle    - The file handle to be flushed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - IniClose
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_INI_CLOSE) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_INI_FILE                              *FileHandle
  )
/*++

Routine Description:

  Closes an INI file.

Arguments:

  This          - Test profile library protocol instance.

  FileHandle    - The file handle to be closed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - GetSystemDevicePath
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_GET_SYSTEM_DEVICE_PATH) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  OUT EFI_DEVICE_PATH_PROTOCOL                  **DevicePath,
  OUT CHAR16                                    **FilePath
  )
/*++

Routine Description:

  Gets the test system device path. With this function, the test case needs not
  to care about the INI file's absolute path or the current working directory.
  The returned DevicePath and FilePath are the copy of system data. It is
  caller's responsibility to free them.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the test management system.

  FilePath      - The file path of the test management system.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol API - SetSystemDevicePath
//
typedef
EFI_STATUS
(EFIAPI *EFI_TPL_SET_SYSTEM_DEVICE_PATH) (
  IN  EFI_TEST_PROFILE_LIBRARY_PROTOCOL         *This,
  IN  EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN  CHAR16                                    *FilePath
  )
/*++

Routine Description:

  Sets the test system device path. This function should only be called by
  the test management system. Any test cases should not call this function to
  change the test system device path.

Arguments:

  This          - Test profile library protocol instance.

  DevicePath    - The device path of the test management system.

  FilePath      - The file path of the test management system.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI Test Profile Library Protocol
//

struct _EFI_TEST_PROFILE_LIBRARY_PROTOCOL {
  UINT64                                LibraryRevision;
  CHAR16                                *Name;
  CHAR16                                *Description;
  EFI_TPL_INI_OPEN                      EfiIniOpen;
  EFI_TPL_INI_CREATE                    EfiIniCreate;
  EFI_TPL_INI_FLUSH                     EfiIniFlush;
  EFI_TPL_INI_CLOSE                     EfiIniClose;
  EFI_TPL_GET_SYSTEM_DEVICE_PATH        EfiGetSystemDevicePath;
  EFI_TPL_SET_SYSTEM_DEVICE_PATH        EfiSetSystemDevicePath;
};

//
// Global ID for EFI Test Profile Library Protocol
//

extern EFI_GUID gEfiTestProfileLibraryGuid;

#endif
