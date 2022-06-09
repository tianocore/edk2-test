/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Misc.h

Abstract:

  Include for Misc.c

--*/

#ifndef _IMAGE_TEST_MISC_H
#define _IMAGE_TEST_MISC_H

#include "ImageBBTest.h"
#include "ProtocolDefinition.h"

typedef struct {
  VOID          *Registration;
  UINTN         NotifyTimes;
} IMAGE_TEST_NOTIFY_CONTEXT;

typedef enum {
  TypeApplication,
  TypeBootDriver,
  TypeRuntimeDriver
} LOAD_FILE_TYPE;

VOID
ImageTestCreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  );

VOID
ImageTestReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  );

VOID
ImageTestCreateNewHandle (
  OUT EFI_HANDLE  *NewHandle
  );

VOID
ImageTestReleaseNewHandle (
  IN EFI_HANDLE    NewHandle
  );

BOOLEAN
ImageTestImageLoadableDevicePath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

VOID
ImageTestLocateNonFilePath (
  OUT EFI_DEVICE_PATH_PROTOCOL **IrrelevantFilePath
  );

VOID
ImageTestCreateNonExistentDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **NonExistentDevicePath
  );

VOID
ImageTestCreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
ImageTestCreateCombinedNonExistentDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **CombinedNonExistentDevicePath
  );

VOID
ImageTestCreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

EFI_STATUS
ImageTestRetrieveCurrentMapKey (
  OUT UINTN        *MapKey
  );

EFI_STATUS
ImageTestComposeSimpleFilePath (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT EFI_DEVICE_PATH_PROTOCOL            **FilePath
  );

EFI_STATUS
ImageTestComposeFvPaths (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_GUID                            FileNameGuid,
  OUT EFI_DEVICE_PATH_PROTOCOL            ***FvFilePathArray,
  OUT UINTN                               *NumberOfFvPaths
  );

EFI_STATUS
ImageTestCopySimpleFileToMemory (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib OPTIONAL,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  CHAR16                              *FileName,
  OUT UINT8                               **SourceBuffer,
  OUT UINTN                               *SourceBufferSize
  );

VOID
EFIAPI
ImageTestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

VOID
EFIAPI
ImageTestNotifyFunctionForCombinationTest1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

EFI_STATUS
ImageTestCheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  );

EFI_STATUS
GetImageDevicePath (
  IN  EFI_HANDLE                   ImageHandle,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  );

EFI_STATUS
InitializeGlobalData (
  VOID
  );

VOID
ReleaseGlobalData (
  VOID
  );

EFI_STATUS
StartLoadFileTestDriver (
  OUT EFI_HANDLE      *DriverImageHandle
  );

VOID
StopLoadFileTestDriver (
  IN EFI_HANDLE        DriverImageHandle
  );

EFI_STATUS
ImageTestComposeLoadFilePath (
  OUT EFI_DEVICE_PATH_PROTOCOL      **FilePath,
  IN  LOAD_FILE_TYPE                Type
  );

#endif
