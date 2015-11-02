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
ImageTestNotifyFunction (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

VOID
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
