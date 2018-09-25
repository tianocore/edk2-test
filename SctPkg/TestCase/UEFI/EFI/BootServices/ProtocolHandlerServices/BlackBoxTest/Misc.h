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
InitializeTestProtocol1 (
  OUT TEST_PROTOCOL_1     *TestProtocol1
  );

EFI_STATUS
TestProtocol1Func1(
  IN TEST_PROTOCOL_1   *This
);

VOID
InitializeTestProtocol2 (
  OUT TEST_PROTOCOL_2     *TestProtocol2
  );

EFI_STATUS
TestProtocol2Func1(
  IN TEST_PROTOCOL_2   *This
  );

VOID
Protocol1ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_1   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol1 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_1     *InterfaceFunctionTestProtocol1
  );

VOID
Protocol2ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol2 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  );

VOID
Protocol3ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol3 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  );

VOID
Protocol4ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_4   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol4 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_4     *InterfaceFunctionTestProtocol4
  );

VOID
Protocol5ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_5   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol5 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_5     *InterfaceFunctionTestProtocol5
  );

VOID
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  );

VOID
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  );

VOID
CreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
CreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
FreeVendorDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

VOID
FreeVendorDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode
  );

VOID
TestNotifyFunction0 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

VOID
TestNotifyFunction1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

VOID
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
LoadStartImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_HANDLE                          CurrentImageHandle,
  IN CHAR16                              *FileName,
  IN EFI_HANDLE                          *StartImage
  );

EFI_STATUS
GetPlatformOverrideDriverImages (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  EFI_HANDLE                          ControllerHandle,
  OUT EFI_HANDLE                          **ImageHandleBuffer,
  OUT UINTN                               *HandleNo
 );

EFI_STATUS
AliasLocateHandleBuffer (
  IN EFI_GUID  *Guid
  );

EFI_STATUS
CheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  );
#endif
