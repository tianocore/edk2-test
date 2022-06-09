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

  Include for Misc.h

--*/

#ifndef _PROTOCOL_HANDLER_MISC_H
#define _PROTOCOL_HANDLER_MISC_H

#include "ProtocolHandlerBBTest.h"
#include "ProtocolDefinition.h"

typedef struct {
  VOID          *Registration;
  EFI_STATUS    Status;
  UINTN         NoHandles;
} NOTIFY_CONTEXT_2;

VOID
EFIAPI
InitializeTestProtocol1 (
  OUT TEST_PROTOCOL_1     *TestProtocol1
  );

EFI_STATUS
EFIAPI
TestProtocol1Func1(
  IN TEST_PROTOCOL_1   *This
);

VOID
EFIAPI
InitializeTestProtocol2 (
  OUT TEST_PROTOCOL_2     *TestProtocol2
  );

EFI_STATUS
EFIAPI
TestProtocol2Func1(
  IN TEST_PROTOCOL_2   *This
  );

VOID
EFIAPI
Protocol1ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_1   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol1 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_1     *InterfaceFunctionTestProtocol1
  );

VOID
EFIAPI
Protocol2ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol2 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  );

VOID
EFIAPI
Protocol3ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol3 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  );

VOID
EFIAPI
Protocol4ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_4   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol4 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_4     *InterfaceFunctionTestProtocol4
  );

VOID
EFIAPI
Protocol5ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_5   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol5 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_5     *InterfaceFunctionTestProtocol5
  );

VOID
EFIAPI
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  );

VOID
EFIAPI
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  );

VOID
EFIAPI
CreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
EFIAPI
CreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
EFIAPI
FreeVendorDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

VOID
EFIAPI
FreeVendorDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode
  );

VOID
EFIAPI
TestNotifyFunction0 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

VOID
EFIAPI
TestNotifyFunction1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

VOID
EFIAPI
TestNotifyFunction2 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

BOOLEAN
IsNodeInDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Node,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

EFI_STATUS
EFIAPI
LoadStartImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_HANDLE                          CurrentImageHandle,
  IN CHAR16                              *FileName,
  IN EFI_HANDLE                          *StartImage
  );

EFI_STATUS
EFIAPI
GetPlatformOverrideDriverImages (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  EFI_HANDLE                          ControllerHandle,
  OUT EFI_HANDLE                          **ImageHandleBuffer,
  OUT UINTN                               *HandleNo
 );

EFI_STATUS
EFIAPI
AliasLocateHandleBuffer (
  IN EFI_GUID  *Guid
  );

EFI_STATUS
EFIAPI
CheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  );
#endif
