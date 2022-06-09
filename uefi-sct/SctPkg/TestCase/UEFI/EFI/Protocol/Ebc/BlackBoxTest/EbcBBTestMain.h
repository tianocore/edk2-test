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

  EbcBBTestMain.h

Abstract:

  BB test header file of Ebc Protocol

--*/


#ifndef _EBC_H_
#define _EBC_H_

#include <Base.h>
#include "SctLib.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/Ebc.h>
#include <UEFI/Protocol/SimpleFileSystem.h>
#include <UEFI/Protocol/LoadedImage.h>

#include <Guid/HobList.h>

#include <Protocol/PeiPeCoffLoader.h>
#include <Protocol/PeiFlushInstructionCache.h>

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)

#define EBC_TEST_REVISION 0x00010000

extern EFI_PEI_FLUSH_INSTRUCTION_CACHE_PROTOCOL  *gEfiPeiFlushInstructionCache;
extern EFI_PEI_PE_COFF_LOADER_PROTOCOL           *gEfiPeiPeCoffLoader;
extern EFI_HANDLE                                gDummyImageHandle;

extern EFI_DEVICE_PATH_PROTOCOL        *gDevicePath;
extern CHAR16                          *gFilePath;

extern BOOLEAN                         gFlushICache;

#define DEPENDECY_DIR_NAME            L"dependency\\EbcBBTest"
#define EBC_DRIVER_NAME               L"EbcDriver.efi"

#define IMAGE_FILE_HANDLE_SIGNATURE       EFI_SIGNATURE_32('s','r','d','d')
typedef struct {
  UINTN               Signature;
  BOOLEAN             FreeBuffer;
  VOID                *Source;
  UINTN               SourceSize;
} IMAGE_FILE_HANDLE;

#define EBC_DRIVER_TEST_PROTOCOL \
  { 0xf01547c5, 0x6f06, 0x4c6d, {0xb6, 0x10, 0x88, 0x91, 0xe7, 0x74, 0x36, 0x45 }}

extern EFI_GUID gBlackBoxEfiEbcDriverProtocolGuid;

//
// Prototypes of Basic Test
//

//
// TDS 3.1
//
EFI_STATUS
EFIAPI
BBTestCreateThunkBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.2
//
EFI_STATUS
EFIAPI
BBTestUnloadImageBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.3
//
EFI_STATUS
EFIAPI
BBTestRegisterICacheFlushBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 3.4
//
EFI_STATUS
EFIAPI
BBTestGetVersionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Conformance Test
//

//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestCreateThunkConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestUnloadImageConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestGetVersionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Prototypes of Internal Functions
//
EFI_STATUS
ReadEbcDriver (
  IN OUT VOID    **Buffer,
  IN OUT UINTN   *Size
  );

EFI_STATUS
ReadImageFile (
  IN     VOID    *UserHandle,
  IN     UINTN   Offset,
  IN OUT UINTN   *ReadSize,
  OUT    VOID    *Buffer
  );

EFI_STATUS
EFIAPI
FlushICache (
  IN EFI_PHYSICAL_ADDRESS     Start,
  IN UINT64                   Length
  );

EFI_STATUS
EFIAPI
TestFlushICache (
  IN EFI_PHYSICAL_ADDRESS     Start,
  IN UINT64                   Length
  );

EFI_STATUS
LoadEbcDriver (
  IN OUT VOID                 **EntryPoint
);

EFI_STATUS
UnloadEbcDriver ();

//
// Entry GUIDs
//

#define EBC_CREATETHUNK_BASIC_TEST_GUID \
  { 0x22bcc713, 0x3bb2, 0x4e2a, {0x81, 0x2e, 0x1a, 0x92, 0x17, 0x50, 0xf3, 0x27 }}

#define EBC_UNLOADIMAGE_BASIC_TEST_GUID \
  { 0xf78efd0a, 0x1e10, 0x46ad, {0x87, 0x49, 0xbd, 0xd5, 0x8, 0x1a, 0x9c, 0xe }}

#define EBC_REGISTERICACHEFLUSH_BASIC_TEST_GUID \
  { 0x2543b8fd, 0x6ae9, 0x45c0, {0xb3, 0xb6, 0xc5, 0x16, 0x4b, 0xe5, 0xaa, 0xff }}

#define EBC_GETVERSION_BASIC_TEST_GUID \
  { 0xe6a2a946, 0x7351, 0x40e7, {0x93, 0xdb, 0x9c, 0x33, 0x5a, 0x2d, 0x13, 0xc1 }}

#define EBC_CREATETHUNK_CONFORMANCE_TEST_GUID \
  { 0x364aeafe, 0x6531, 0x4a8e, {0x83, 0x31, 0x63, 0x67, 0x54, 0x9d, 0xe0, 0xd3 }}

#define EBC_UNLOADIMAGE_CONFORMANCE_TEST_GUID \
  { 0x532caf60, 0xd2b5, 0x4d3d, {0x88, 0xdc, 0xa, 0xa1, 0xf5, 0x5, 0x90, 0xd4 }}

#define EBC_GETVERSION_CONFORMANCE_TEST_GUID \
  { 0x404465d3, 0xaa0d, 0x4f70, {0xa4, 0x86, 0x8b, 0x8a, 0xe7, 0xf4, 0xbc, 0xd8 }}

#endif
