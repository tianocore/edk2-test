/*++

Copyright (c) 2004 - 2008, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

Copyright (c) 2014, ARM Ltd. All rights reserved.

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

Module Name:

  EfiDriverModelLib.c

Abstract:

  Light weight lib to support EFI drivers.

--*/

#include "SctLibInternal.h"

#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (ComponentName2)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration2)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics2)

#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
#include <Protocol/DriverConfiguration.h>
#endif

EFI_STATUS
SctInstallDriverBinding (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL  *DriverBinding,
  IN EFI_HANDLE                   DriverBindingHandle
  )
/*++

Routine Description:

  Intialize a driver by installing the Driver Binding Protocol onto the
  driver's DriverBindingHandle.  This is typically the same as the driver's
  ImageHandle, but it can be different if the driver produces multiple
  DriverBinding Protocols.  This function also initializes the EFI Driver
  Library that initializes the global variables tST, tBS, tRT.

Arguments:

  ImageHandle         - The image handle of the driver

  SystemTable         - The EFI System Table that was passed to the driver's entry point

  DriverBinding       - A Driver Binding Protocol instance that this driver is producing

  DriverBindingHandle - The handle that DriverBinding is to be installe onto.  If this
                        parameter is NULL, then a new handle is created.

Returns:

  EFI_SUCCESS is DriverBinding is installed onto DriverBindingHandle

  Otherwise, then return status from tBS->InstallProtocolInterface()

--*/
{
  SctInitializeDriver (ImageHandle, SystemTable);

  DriverBinding->ImageHandle          = ImageHandle;

  DriverBinding->DriverBindingHandle  = DriverBindingHandle;

  return tBS->InstallProtocolInterface (
                &DriverBinding->DriverBindingHandle,
                &gEfiDriverBindingProtocolGuid,
                EFI_NATIVE_INTERFACE,
                DriverBinding
                );
}

EFI_STATUS
SctInstallAllDriverProtocolsWorker (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL        * DriverBinding,
  IN EFI_HANDLE                         DriverBindingHandle,
  IN EFI_COMPONENT_NAME_PROTOCOL        * ComponentName, OPTIONAL
  IN EFI_COMPONENT_NAME2_PROTOCOL       * ComponentName2, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL  * DriverConfiguration, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION2_PROTOCOL * DriverConfiguration2, OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL    * DriverDiagnostics, OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL   * DriverDiagnostics2 OPTIONAL
  )
/*++

Routine Description:

  Intialize a driver by installing the Driver Binding Protocol onto the
  driver's DriverBindingHandle.  This is typically the same as the driver's
  ImageHandle, but it can be different if the driver produces multiple
  DriverBinding Protocols.  This function also initializes the EFI Driver
  Library that initializes the global variables tST, tBS, tRT.

Arguments:

  ImageHandle         - The image handle of the driver

  SystemTable         - The EFI System Table that was passed to the driver's entry point

  DriverBinding       - A Driver Binding Protocol instance that this driver is producing

  DriverBindingHandle - The handle that DriverBinding is to be installe onto.  If this
                        parameter is NULL, then a new handle is created.

  ComponentName       - A Component Name Protocol instance that this driver is producing

  ComponentName2      - A Component Name2 Protocol instance that this driver is producing

  DriverConfiguration - A Driver Configuration Protocol instance that this driver is producing

  DriverConfiguration2- A Driver Configuration2 Protocol instance that this driver is producing

  DriverDiagnostics   - A Driver Diagnostics Protocol instance that this driver is producing

  DriverDiagnostics2  - A Driver Diagnostics2 Protocol instance that this driver is producing

Returns:

  EFI_SUCCESS if all the protocols were installed onto DriverBindingHandle

  Otherwise, then return status from tBS->InstallProtocolInterface()

--*/
{
  EFI_STATUS  Status;

  Status = SctInstallDriverBinding (ImageHandle, SystemTable, DriverBinding, DriverBindingHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (ComponentName != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiComponentNameProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    ComponentName
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (ComponentName2 != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiComponentName2ProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    ComponentName2
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (DriverConfiguration != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiDriverConfigurationProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    DriverConfiguration
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (DriverConfiguration2 != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiDriverConfiguration2ProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    DriverConfiguration2
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (DriverDiagnostics != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiDriverDiagnosticsProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    DriverDiagnostics
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (DriverDiagnostics2 != NULL) {
    Status = tBS->InstallProtocolInterface (
                    &DriverBinding->DriverBindingHandle,
                    &gEfiDriverDiagnostics2ProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    DriverDiagnostics2
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  return EFI_SUCCESS;
}

EFI_STATUS
SctInstallAllDriverProtocols (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN VOID* DriverBindingProtocol,
  IN EFI_HANDLE                         DriverBindingHandle,
  IN VOID* ComponentNameProtocol, OPTIONAL
  IN VOID* DriverConfigurationProtocol, OPTIONAL
  IN VOID* DriverDiagnosticsProtocol OPTIONAL
  )
/*++

Routine Description:

  Intialize a driver by installing the Driver Binding Protocol onto the
  driver's DriverBindingHandle.  This is typically the same as the driver's
  ImageHandle, but it can be different if the driver produces multiple
  DriverBinding Protocols.  This function also initializes the EFI Driver
  Library that initializes the global variables tST, tBS, tRT.

Arguments:

  ImageHandle         - The image handle of the driver

  SystemTable         - The EFI System Table that was passed to the driver's entry point

  DriverBinding       - A Driver Binding Protocol instance that this driver is producing

  DriverBindingHandle - The handle that DriverBinding is to be installe onto.  If this
                        parameter is NULL, then a new handle is created.

  ComponentName       - A Component Name Protocol instance that this driver is producing

  DriverConfiguration - A Driver Configuration Protocol instance that this driver is producing

  DriverDiagnostics   - A Driver Diagnostics Protocol instance that this driver is producing

Returns:

  EFI_SUCCESS if all the protocols were installed onto DriverBindingHandle

  Otherwise, then return status from tBS->InstallProtocolInterface()

--*/
{
  return SctInstallAllDriverProtocolsWorker (
           ImageHandle,
           SystemTable,
           DriverBindingProtocol,
           DriverBindingHandle,
           ComponentNameProtocol,
           NULL,
           DriverConfigurationProtocol,
           NULL,
           DriverDiagnosticsProtocol,
           NULL
           );
}

EFI_STATUS
SctInstallAllDriverProtocols2 (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN VOID* DriverBindingProtocol,
  IN EFI_HANDLE                         DriverBindingHandle,
  IN VOID* ComponentName2Protocol, OPTIONAL
  IN VOID* DriverConfiguration2Protocol, OPTIONAL
  IN VOID* DriverDiagnostics2Protocol OPTIONAL
  )
/*++

Routine Description:

  Intialize a driver by installing the Driver Binding Protocol onto the
  driver's DriverBindingHandle.  This is typically the same as the driver's
  ImageHandle, but it can be different if the driver produces multiple
  DriverBinding Protocols.  This function also initializes the EFI Driver
  Library that initializes the global variables tST, tBS, tRT.

Arguments:

  ImageHandle         - The image handle of the driver

  SystemTable         - The EFI System Table that was passed to the driver's entry point

  DriverBinding       - A Driver Binding Protocol instance that this driver is producing

  DriverBindingHandle - The handle that DriverBinding is to be installe onto.  If this
                        parameter is NULL, then a new handle is created.

  ComponentName2      - A Component Name2 Protocol instance that this driver is producing

  DriverConfiguration2- A Driver Configuration2 Protocol instance that this driver is producing

  DriverDiagnostics2  - A Driver Diagnostics2 Protocol instance that this driver is producing

Returns:

  EFI_SUCCESS if all the protocols were installed onto DriverBindingHandle

  Otherwise, then return status from tBS->InstallProtocolInterface()

--*/
{
  return SctInstallAllDriverProtocolsWorker (
           ImageHandle,
           SystemTable,
           DriverBindingProtocol,
           DriverBindingHandle,
           NULL,
           ComponentName2Protocol,
           NULL,
           DriverConfiguration2Protocol,
           NULL,
           DriverDiagnostics2Protocol
           );
}
