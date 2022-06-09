/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
    SimpleFileSystemTest.h

Abstract:
    head file of test driver of EFI Simple File System Protocol
    and EFI_FILE Protocol Test

--*/

#ifndef _SIMPLE_FILE_SYSTEM_TEST_H
#define _SIMPLE_FILE_SYSTEM_TEST_H

#include <Base.h>
#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include <UEFI/Protocol/BlockIo.h>
#include <UEFI/Protocol/SimpleFileSystem.h>
#include <UEFI/Guid/FileInfo.h>
#include <UEFI/Guid/FileSystemInfo.h>
#include <UEFI/Guid/FileSystemVolumeLabelInfo.h>
#include <Protocol/DevicePath.h>
#include "Guid.h"

//----------------------------------//
//
//  This macro is used for a sub-set test (to save time)
//
#define FILE_SYSTEM_SIMPLE_TEST 1
//
//---------------------------------//



#define SIMPLE_FILE_SYSTEM_TEST_REVISION 0x00010000

#define MAX_STRING_LENGTH         266

#define OPEN_R_W_MODE       (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE)
#define CREATE_FILE_MODE    (OPEN_R_W_MODE | EFI_FILE_MODE_CREATE)

#define TPL_ARRAY_SIZE 2

extern EFI_TPL TplArray [TPL_ARRAY_SIZE];

extern EFI_HANDLE   mImageHandle;

#if EFI_FILE_HANDLE_REVISION >= 0x00020000

extern EFI_EVENT       TimerEvent;

//
//
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE                          *FileIo;
  EFI_FILE_IO_TOKEN                 FileIoToken;
  EFI_TPL                           Tpl;
  UINT64                            SetPosition;
  UINT64                            PositionAfterRead;
  UINTN                             ReadLength;
  SCT_LIST_ENTRY                    ListEntry;
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIo_Task;

//
// record every  SimpleFileSystem Async Read Directory call status
//
typedef struct {
  UINTN                             Signature;
  EFI_FILE                          *FileIo;
  EFI_FILE_IO_TOKEN                 FileIoToken;
  EFI_TPL                           Tpl;
  UINTN                             Index;
  SCT_LIST_ENTRY                    ListEntry;
  EFI_STATUS                        StatusAsync;
  EFI_TEST_ASSERTION                AssertionType;
} FileIoDir_Task;
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Basic Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0101 \
 {0x3e59fed4, 0x426a, 0x4e00, {0x87, 0x87, 0x68, 0xa2, 0xf, 0x80, 0xb0, 0xb7} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0102 \
 {0xa6b309b3, 0xa0ad, 0x409d, {0xa5, 0x0, 0xff, 0x34, 0x3e, 0x49, 0x7, 0x40} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0103 \
 {0x3eaea622, 0x167, 0x4213, {0xb6, 0xd9, 0xa, 0xd3, 0xd0, 0x6, 0x66, 0x79} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0104 \
 {0xb709d88f, 0x18f0, 0x4dba, {0xa5, 0x3c, 0x7c, 0x4d, 0x81, 0xc4, 0x96, 0xd8} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0105 \
 {0x2582c031, 0x21e7, 0x4a7b, {0xaf, 0x80, 0x8a, 0x67, 0xb3, 0xe1, 0xd7, 0xd8} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0106 \
 {0x22372dd8, 0xaa00, 0x4eda, {0x99, 0xe8, 0x6f, 0xc1, 0x4a, 0xb1, 0xfb, 0x3c} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0107 \
 {0x11f22aeb, 0x5fa8, 0x412a, {0xa1, 0x2a, 0xe3, 0xd4, 0x60, 0x15, 0x36, 0x8c} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0108 \
 {0x4867091f, 0x5988, 0x4a0c, {0x9f, 0x21, 0x44, 0x7, 0x55, 0x47, 0x9a, 0x1b} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0109 \
 {0x38150ebd, 0x8835, 0x46c5, {0xb0, 0x85, 0x6a, 0x6c, 0x62, 0x6e, 0xa9, 0x72} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0110 \
 {0xee14a4db, 0xbc9f, 0x49eb, {0x8c, 0x72, 0x4b, 0xc6, 0x55, 0x42, 0x7d, 0x97} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0111 \
 {0xeba448e7, 0x59e6, 0x474a, {0x87, 0x5e, 0x56, 0xdd, 0xee, 0x9e, 0x3b, 0xfe} }
//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for FunctionEx Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0112 \
{0x7e68498e, 0x343b, 0x4b61, { 0x8e, 0x3f, 0xfa, 0xe2, 0x85, 0xd9, 0x19, 0xf5 } }


#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0113 \
{0xc54b642d, 0x4d3e, 0x4897, { 0x9d, 0xd5, 0x1f, 0x72, 0x21, 0x65, 0xe0, 0xe } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0114 \
{0x44b63e71, 0x6a74, 0x4a23, { 0x9c, 0x2d, 0xed, 0x33, 0x3d, 0xd5, 0xdd, 0xe2 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0115 \
{0xb2af35d8, 0x8e2b, 0x48b1, { 0xa3, 0xfc, 0xb4, 0xc6, 0x7d, 0x80, 0xf9, 0x9d } }



//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Conformance Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0201 \
 {0xba666cb, 0xb43a, 0x4691, {0x82, 0xe8, 0xb2, 0x24, 0x1e, 0xb9, 0xa9, 0xf9} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0202 \
 {0x77cfb820, 0xd535, 0x4a9c, {0xb8, 0x8b, 0x6e, 0xf3, 0xdc, 0x21, 0x73, 0x46} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0203 \
 {0xaec76679, 0x3a6e, 0x4347, {0xbb, 0xe4, 0xfc, 0x9b, 0xbc, 0x3f, 0xdd, 0x5c} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0204 \
 {0x41e00d7c, 0xe0f7, 0x455f, {0xa6, 0x17, 0xfc, 0x63, 0x56, 0x18, 0x24, 0x14} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0205 \
 {0xa2fdc63e, 0x2d01, 0x4aab, {0x88, 0x80, 0xe6, 0x2c, 0x1e, 0x8, 0xd9, 0x30} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0206 \
 {0x8a2f13c7, 0xa01c, 0x4949, {0x81, 0xc9, 0x46, 0xb3, 0xff, 0x34, 0x9f, 0x92} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0207 \
 {0x8b16c09d, 0x5321, 0x4a63, {0xb1, 0x68, 0x8e, 0x59, 0x59, 0xa, 0x43, 0x6d} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0208 \
 {0x44bec963, 0xdabd, 0x43e1, {0xb3, 0x8a, 0x95, 0x5a, 0xba, 0x3b, 0x18, 0xff} }
 
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0209 \
 {0x614cf090, 0xe3a6, 0x49b6, { 0xaf, 0x93, 0x31, 0xba, 0xba, 0x7, 0x61, 0xb4 } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0210 \
 {0xbffe42d6, 0xce26, 0x4b63, { 0x86, 0x9, 0x51, 0xe6, 0x9a, 0x16, 0x68, 0xa1 } }


#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0211 \
 {0xb2ef8d8c, 0x3662, 0x462f, { 0x90, 0x11, 0xcd, 0xdd, 0x5d, 0xc0, 0x3c, 0x6b } }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0212 \
{ 0xb877944f, 0x7d05, 0x427f, { 0xbb, 0x9c, 0xbc, 0xcf, 0x78, 0x7, 0x34, 0x88 } }

//////////////////////////////////////////////////////////////////////////////
//
// Entry GUIDs for Automatic Extensive Test
//
#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0301 \
 {0x8cc2dcc3, 0x1717, 0x4385, {0xb9, 0x64, 0x0, 0xdf, 0x80, 0xa5, 0x1f, 0x19} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0302 \
 {0xae826fc7, 0x29f, 0x4ca4, {0x8e, 0x7f, 0xb0, 0xfb, 0xc, 0x66, 0x67, 0x9b} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0303 \
 {0x923d26df, 0x3348, 0x4a64, {0x81, 0x33, 0xa6, 0x17, 0x1d, 0xbf, 0x52, 0x9e} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0304 \
 {0xe7e4ea69, 0x10d4, 0x4d26, {0xad, 0xd4, 0x77, 0x6c, 0xc6, 0x8a, 0xd3, 0x8b} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0305 \
 {0x3dc4153d, 0x8d5a, 0x46b3, {0xb4, 0x8f, 0x38, 0x29, 0x2a, 0xbb, 0x29, 0xbc} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0306 \
 {0x15d3ecf2, 0x9b70, 0x416d, {0x92, 0x3b, 0xc6, 0xd5, 0xa7, 0x66, 0x91, 0x5b} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0307 \
 {0xfb006a, 0x627e, 0x460f, {0xaa, 0x5c, 0xb9, 0x9d, 0x31, 0x14, 0xae, 0x5c} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0308 \
 {0xbb9fb2c8, 0xcd7c, 0x41cb, {0xbd, 0x2b, 0xdf, 0x0, 0xd5, 0x1b, 0xfa, 0xea} }

#define SIMPLE_FILE_SYSTEM_PROTOCOL_TEST_ENTRY_GUID0309 \
 {0x6280b5e9, 0xc05, 0x4b05, {0x95, 0x7, 0xd2, 0xf8, 0xda, 0x8e, 0x27, 0x35} }

//////////////////////////////////////////////////////////////////////////////

//
// functions declaration
//

EFI_STATUS
EFIAPI
InitializeBBTestSimpleFileSystem (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
EFIAPI
BBTestSimpleFileSystemUnload (
  IN EFI_HANDLE       ImageHandle
  );

//
// Basic test functions
//

//
// TDS 5.1.1
//
EFI_STATUS
EFIAPI
BBTestOpenVolumeBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.2
//
EFI_STATUS
EFIAPI
BBTestOpenBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.3
//
EFI_STATUS
EFIAPI
BBTestCloseBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.4
//
EFI_STATUS
EFIAPI
BBTestDeleteBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.5
//
EFI_STATUS
EFIAPI
BBTestReadBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.6
//
EFI_STATUS
EFIAPI
BBTestWriteBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.7
//
EFI_STATUS
EFIAPI
BBTestFlushBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.8
//
EFI_STATUS
EFIAPI
BBTestSetPositionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.9
//
EFI_STATUS
EFIAPI
BBTestGetPositionBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.10
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.11
//
EFI_STATUS
EFIAPI
BBTestSetInfoBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functionExs for basic tests
//

//
// TDS 5.1.12
//
EFI_STATUS
EFIAPI
BBTestOpenExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.13
//
EFI_STATUS
EFIAPI
BBTestReadExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.14
//
EFI_STATUS
EFIAPI
BBTestWriteExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.1.15
//
EFI_STATUS
EFIAPI
BBTestFlushExBasicTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Checkpoint functions for basic tests
//

//
// TDS 5.1.1.2.1
//
EFI_STATUS
EFIAPI
BBTestOpenVolumeBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.2.2.1
//
EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.2.2.2
//
EFI_STATUS
EFIAPI
BBTestOpenBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.3.2.1
//
EFI_STATUS
EFIAPI
BBTestCloseBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.1
//
EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.2
//
EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.4.2.3
//
EFI_STATUS
EFIAPI
BBTestDeleteBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.5.2.1
//
EFI_STATUS
EFIAPI
BBTestReadBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.5.2.2
//
EFI_STATUS
EFIAPI
BBTestReadBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.6.2.1
//
EFI_STATUS
EFIAPI
BBTestWriteBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.7.2.1
//
EFI_STATUS
EFIAPI
BBTestFlushBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.7.2.2
//
EFI_STATUS
EFIAPI
BBTestFlushBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.8.2.1
//
EFI_STATUS
EFIAPI
BBTestSetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *v
  );

//
// TDS 5.1.8.2.2
//
EFI_STATUS
EFIAPI
BBTestSetPositionBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.9.2.1
//
EFI_STATUS
EFIAPI
BBTestGetPositionBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *v
  );

//
// TDS 5.1.10.2.1
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.10.2.2
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );


//
// TDS 5.1.10.2.3
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.10.2.4
//
EFI_STATUS
EFIAPI
BBTestGetInfoBasicTestCheckpoint4 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.11.2.1
//
EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint1 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem,
  BOOLEAN                               IsStress
  );

//
// TDS 5.1.11.2.2
//
EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint2 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.1.11.2.3
//
EFI_STATUS
EFIAPI
BBTestSetInfoBasicTestCheckpoint3 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// Conformance test functions
//

//
// TDS 5.2.1
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.2
//
EFI_STATUS
EFIAPI
BBTestDeleteConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.3
//
EFI_STATUS
EFIAPI
BBTestWriteConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.4
//
EFI_STATUS
EFIAPI
BBTestFlushConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.5
//
EFI_STATUS
EFIAPI
BBTestSetPositionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.6
//
EFI_STATUS
EFIAPI
BBTestGetPositionConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.7
//
EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.8
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.9
//
EFI_STATUS
EFIAPI
BBTestOpenExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.10
//
EFI_STATUS
EFIAPI
BBTestWriteExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// TDS 5.2.11
//
EFI_STATUS
EFIAPI
BBTestFlushExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.2.12
//
EFI_STATUS
EFIAPI
BBTestReadExConformanceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Checkpoint functions for Conformance tests
//

//
// TDS 5.2.1.2.1
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.2
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.3
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.4
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.5
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint5(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.1.2.6
//
EFI_STATUS
EFIAPI
BBTestOpenConformanceTestCheckpoint6(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.2.2.1
//
EFI_STATUS
EFIAPI
BBTestDeleteConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.1
//
EFI_STATUS
EFIAPI
BBTestWriteConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.2
//
EFI_STATUS
EFIAPI
BBTestWriteConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.3.2.3
//
EFI_STATUS
EFIAPI
BBTestWriteConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.4.2.1
//
EFI_STATUS
EFIAPI
BBTestFlushConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.4.2.2
//
EFI_STATUS
EFIAPI
BBTestFlushConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.5.2.1
//
EFI_STATUS
EFIAPI
BBTestSetPositionConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.6.2.1
//
EFI_STATUS
EFIAPI
BBTestGetPositionConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.7.2.1
//
EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.7.2.2
//
EFI_STATUS
EFIAPI
BBTestGetInfoConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.1
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint1(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.2
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint2(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.3
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint3(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.4
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint4(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

//
// TDS 5.2.8.2.5
//
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint5(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint6(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.8.2.7
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint7(
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );

// TDS 5.2.8.2.8
EFI_STATUS
EFIAPI
BBTestSetInfoConformanceTestCheckpoint8 (
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib,
  EFI_SIMPLE_FILE_SYSTEM_PROTOCOL       *SimpleFileSystem
  );



//
// Automatic Extensive test functions
//

//
// TDS 5.3.1
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest1 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.2
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest2 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.3
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest3 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.4
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest4 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.5
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest5 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.6
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemExtensiveTest6 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.7
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemOpenStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.8
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemGetInfoStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// TDS 5.3.9
//
EFI_STATUS
EFIAPI
BBTestSimpleFileSytemSetInfoStress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// some internal functions
//
EFI_STATUS
InternalGetInfo (
  EFI_FILE      *FileHandle,
  VOID          **InfoBuffer,
  UINTN         *BufferSize,
  EFI_GUID      *InfoId
  );

EFI_STATUS
InternalSetFileSize (
  EFI_FILE      *FileHandle,
  UINT64        FileSize
  );

EFI_STATUS
InternalSetFileAttribute (
  EFI_FILE      *FileHandle,
  UINT64        Attribute
  );



#endif
