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

  Misc.c

Abstract:

  Internal functions

--*/

#include "Misc.h"

//
// global variable
//
EFI_DEVICE_PATH_PROTOCOL    *mDevicePath;
CHAR16                      *mFilePath;

///////////////////////////////////////////////////////////////////////////////
//
// TestProtocol1 Functions
//
VOID
EFIAPI
InitializeTestProtocol1 (
  OUT TEST_PROTOCOL_1     *TestProtocol1
  )
{
  gtBS->SetMem (TestProtocol1, sizeof (TEST_PROTOCOL_1), 0);

  TestProtocol1->TestProtocol1Func1 = TestProtocol1Func1;
}

EFI_STATUS
EFIAPI
TestProtocol1Func1 (
  IN TEST_PROTOCOL_1   *This
  )
{
  return EFI_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// TestProtocol2 Functions
//
VOID
EFIAPI
InitializeTestProtocol2 (
  OUT TEST_PROTOCOL_2     *TestProtocol2
  )
{
  gtBS->SetMem (TestProtocol2, sizeof (TEST_PROTOCOL_2), 0);

  TestProtocol2->TestProtocol2Func1 = TestProtocol2Func1;
}

EFI_STATUS
EFIAPI
TestProtocol2Func1 (
  IN TEST_PROTOCOL_2   *This
  )
{
  return EFI_SUCCESS;
}


///////////////////////////////////////////////////////////////////////////////
//
// InterfaceFunctionTestProtocol1 Functions
//
VOID
EFIAPI
Protocol1ReportProtocolAttributes (
  IN  INTERFACE_FUNCTION_TEST_PROTOCOL_1   *This,
  OUT PROTOCOL_ATTRIBUTES                  *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol1 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_1     *InterfaceFunctionTestProtocol1
  )
{
  InterfaceFunctionTestProtocol1->ReportProtocolAttributes = Protocol1ReportProtocolAttributes;
  InterfaceFunctionTestProtocol1->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol1Id;
  InterfaceFunctionTestProtocol1->ProtocolAttributes.ReinstallField = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// InterfaceFunctionTestProtocol2 Functions
//

VOID
EFIAPI
Protocol2ReportProtocolAttributes (
  IN  INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES                  *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol2 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  )
{
  InterfaceFunctionTestProtocol2->ReportProtocolAttributes = Protocol2ReportProtocolAttributes;
  InterfaceFunctionTestProtocol2->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol2Id;
  InterfaceFunctionTestProtocol2->ProtocolAttributes.ReinstallField = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// InterfaceFunctionTestProtocol3 Functions
//

VOID
EFIAPI
Protocol3ReportProtocolAttributes (
  IN  INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES                  *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol3 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  )
{
  InterfaceFunctionTestProtocol3->ReportProtocolAttributes = Protocol3ReportProtocolAttributes;
  InterfaceFunctionTestProtocol3->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol3Id;
  InterfaceFunctionTestProtocol3->ProtocolAttributes.ReinstallField = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// InterfaceFunctionTestProtocol4 Functions
//

VOID
EFIAPI
Protocol4ReportProtocolAttributes (
  IN  INTERFACE_FUNCTION_TEST_PROTOCOL_4   *This,
  OUT PROTOCOL_ATTRIBUTES                  *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol4 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_4     *InterfaceFunctionTestProtocol4
  )
{
  InterfaceFunctionTestProtocol4->ReportProtocolAttributes = Protocol4ReportProtocolAttributes;
  InterfaceFunctionTestProtocol4->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol4Id;
  InterfaceFunctionTestProtocol4->ProtocolAttributes.ReinstallField = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// InterfaceFunctionTestProtocol5 Functions
//

VOID
EFIAPI
Protocol5ReportProtocolAttributes (
  IN  INTERFACE_FUNCTION_TEST_PROTOCOL_5   *This,
  OUT PROTOCOL_ATTRIBUTES                  *ProtocolAttributes
  )
{
  *ProtocolAttributes = This->ProtocolAttributes;
}

VOID
EFIAPI
InitializeInterfaceFunctionTestProtocol5 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_5     *InterfaceFunctionTestProtocol5
  )
{
  InterfaceFunctionTestProtocol5->ReportProtocolAttributes = Protocol5ReportProtocolAttributes;
  InterfaceFunctionTestProtocol5->ProtocolAttributes.ProtocolId = InterfaceFunctionTestProtocol5Id;
  InterfaceFunctionTestProtocol5->ProtocolAttributes.ReinstallField = 0;
}


//////////////////////////////////////////////////////////////////////////////
//
// Others
//

/**
 *  @brief This function create an invalid handle. To avoid memory leak,
 *         it is stronggly recommended to use with ReleaseInvalidHandle.
 *  @see ReleaseInvalidHandle.
 */
VOID
EFIAPI
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  )
{
  EFI_HANDLE                  Handle = NULL;
  EFI_STATUS                  Status;

  Status = gtBS->InstallProtocolInterface (
                   &Handle,
                   &mTestNoInterfaceProtocol1Guid,
                   EFI_NATIVE_INTERFACE,
                   NULL
                   );
  if (EFI_ERROR(Status)) {
    *InvalidHandle = NULL;
  } else {
    //
    // When restore the environment, the valid handle should be
    // (EFI_HANDLE)((UINT8*)InvalidHandle + 8)
    //
    *InvalidHandle = (EFI_HANDLE)((UINT8*)Handle + 8);
  }
}

VOID
EFIAPI
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  )
{
  EFI_HANDLE              ValidHandle;

  if (InvalidHandle == NULL) {
    return;
  }

  ValidHandle = (EFI_HANDLE)((UINT8*)InvalidHandle - 8);

  gtBS->UninstallProtocolInterface (ValidHandle, &mTestNoInterfaceProtocol1Guid, NULL);
}

VOID
EFIAPI
CreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  )
{
  UINTN                       Length;
  EFI_DEVICE_PATH_PROTOCOL    *DevicePathNode;
  EFI_DEVICE_PATH_PROTOCOL    *DevPointer;
  EFI_STATUS                  Status;

  //
  // init
  //
  *DevicePath = NULL;
  Length = sizeof (VENDOR_DEVICE_PATH) + sizeof (EFI_DEVICE_PATH_PROTOCOL);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Length,
                   (VOID**)DevicePath
                   );
  if (EFI_ERROR(Status)) {
    return;
  }

  DevicePathNode = NULL;
  CreateVendorDevicePathNode (&DevicePathNode, Guid);

  DevPointer = *DevicePath;

  gtBS->CopyMem (DevPointer, DevicePathNode, sizeof (VENDOR_DEVICE_PATH));

  //
  // points to next node
  //
  DevPointer = (EFI_DEVICE_PATH_PROTOCOL*)((UINT8*)DevPointer + sizeof (VENDOR_DEVICE_PATH));
  //
  // End Node
  //
  SctSetDevicePathEndNode (DevPointer);

  //
  // release resource
  //
  FreeVendorDevicePathNode (DevicePathNode);

  return;
}

VOID
EFIAPI
CreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  )
{
  UINTN      Length;
  EFI_DEVICE_PATH_PROTOCOL    *DevPointer;
  EFI_STATUS                  Status;
  VENDOR_DEVICE_PATH          VendorDevicePathNode;

  if (DevicePath == NULL) {
    return;
  }

  //
  // init
  //
  *DevicePath = NULL;
  Length = sizeof (VENDOR_DEVICE_PATH);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Length,
                   (VOID**)DevicePath
                   );
  if (EFI_ERROR(Status)) {
    //
    // record FAIL assertion (generic)
    //
    return;
  }

  DevPointer = *DevicePath;

  //
  // Vendor device path node
  //
  VendorDevicePathNode.Header.Type = HARDWARE_DEVICE_PATH;
  VendorDevicePathNode.Header.SubType = HW_VENDOR_DP;
  VendorDevicePathNode.Header.Length[0] = sizeof (VENDOR_DEVICE_PATH);
  VendorDevicePathNode.Header.Length[1] = 0;
  gtBS->CopyMem (&VendorDevicePathNode.Guid, &Guid, sizeof (EFI_GUID));
  gtBS->CopyMem (DevPointer, &VendorDevicePathNode, sizeof (VENDOR_DEVICE_PATH));

  return;
}

VOID
EFIAPI
FreeVendorDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  if (DevicePath == NULL) {
    return;
  }
  gtBS->FreePool (DevicePath);
}

VOID
EFIAPI
FreeVendorDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode
  )
{
  if (DevicePathNode == NULL) {
    return;
  }
  gtBS->FreePool (DevicePathNode);
}

VOID
EFIAPI
TestNotifyFunction0 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  //
  // do nothing
  //
  return;
}

VOID
EFIAPI
TestNotifyFunction1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  )
{
  UINTN     *NotifyTimes;

  NotifyTimes = (UINTN*)Context;

  (*NotifyTimes)++;
}

VOID
EFIAPI
TestNotifyFunction2 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  NOTIFY_CONTEXT_2    *NotifyContext2;
  EFI_HANDLE          *HandleBuffer;

  HandleBuffer = NULL;

  NotifyContext2 = (NOTIFY_CONTEXT_2*)Context;

  NotifyContext2->Status = gtBS->LocateHandleBuffer (
                                   ByRegisterNotify,
                                   NULL,
                                   NotifyContext2->Registration,
                                   &NotifyContext2->NoHandles,
                                   &HandleBuffer
                                   );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }
}

BOOLEAN
IsNodeInDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Node,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *DevPath;
  UINTN                       Length;

  DevPath = DevicePath;
  while (!SctIsDevicePathEndType (DevPath)) {

    Length = (UINTN)(DevPath->Length[1] << 8 | DevPath->Length[0]);

    if (!SctCompareMem (DevPath, Node, Length)) {
      return TRUE;
    }

    DevPath = SctNextDevicePathNode (DevPath);
  }

  return FALSE;
}

////////////////////////////
EFI_STATUS
EFIAPI
LoadStartImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_HANDLE                          CurrentImageHandle,
  IN CHAR16                              *FileName,
  IN EFI_HANDLE                          *StartImage
  )
{
  EFI_STATUS                    Status;
  CHAR16                        *EntireFileName;
  EFI_LOADED_IMAGE_PROTOCOL     *LoadImage;
  EFI_DEVICE_PATH_PROTOCOL      *FilePath;

  Status = gtBS->HandleProtocol (
                   CurrentImageHandle,
                   &gEfiLoadedImageProtocolGuid,
                   (VOID **) &LoadImage
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  EntireFileName = NULL;
  EntireFileName = SctPoolPrint (L"%s\\%s", mFilePath, FileName);

  FilePath = SctFileDevicePath (LoadImage->DeviceHandle, EntireFileName);
  if (FilePath == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Status = gtBS->LoadImage (
                   FALSE,
                   CurrentImageHandle,
                   FilePath,
                   NULL,
                   0,
                   StartImage
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LoadImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    gtBS->FreePool (EntireFileName);
    gtBS->FreePool (FilePath);
    return Status;
  }

  Status = gtBS->StartImage (*StartImage, 0, NULL);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.StartImage - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  gtBS->FreePool (EntireFileName);
  gtBS->FreePool (FilePath);
  return Status;
}


EFI_STATUS
EFIAPI
GetPlatformOverrideDriverImages (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  EFI_HANDLE                          ControllerHandle,
  OUT EFI_HANDLE                          **ImageHandleBuffer,
  OUT UINTN                               *HandleNo
  )
{
  EFI_STATUS                  Status;
  EFI_HANDLE                  *HandleBuffer;
  UINTN                       NoHandles;
  EFI_HANDLE                  *DriverImageHandleBuffer;
  EFI_DEVICE_PATH_PROTOCOL    *DriverImagePath;
  UINTN                       Index;
  EFI_HANDLE                  ImageHandle;

  EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL   *PlatformDriverOverrideInterface;

  HandleBuffer = NULL;

  *HandleNo = 2;
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   *HandleNo * sizeof (EFI_HANDLE),
                   (VOID**)ImageHandleBuffer
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.ConnectController - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  DriverImageHandleBuffer = *ImageHandleBuffer;

  //
  // locate the EFI Platform Driver Override Protocol
  //
  HandleBuffer = NULL;
  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   &mPlatformOverrideDriver1Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (EFI_ERROR(Status) || NoHandles != 1) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateHandleBuffer - build environment",
                   L"%a:%d:Status - %r, NoHandles - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   NoHandles
                   );
    goto Done;
  }

  Status = gtBS->HandleProtocol (
                   HandleBuffer[0],
                   &gEfiPlatformDriverOverrideProtocolGuid,
                   (VOID **) &PlatformDriverOverrideInterface
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - build environment",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    goto Done;
  }

  //
  // load and start those drivers returned by Platform Driver Override Protocol
  //
  DriverImagePath = NULL;
  for (Index = 0; Index < 2; Index++) {

    Status = PlatformDriverOverrideInterface->GetDriverPath (
                                                PlatformDriverOverrideInterface,
                                                ControllerHandle,
                                                &DriverImagePath
                                                );
    if (EFI_ERROR(Status)) {
      break;
    }

    Status = gtBS->LoadImage (
                     FALSE,
                     CurrentImageHandle,
                     DriverImagePath,
                     NULL,
                     0,
                     &ImageHandle
                     );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.LoadImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    DriverImageHandleBuffer[Index] = ImageHandle;

    Status = gtBS->StartImage (ImageHandle, NULL, NULL);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.StartImage - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }

    Status = PlatformDriverOverrideInterface->DriverLoaded (
                                                PlatformDriverOverrideInterface,
                                                ControllerHandle,
                                                DriverImagePath,
                                                ImageHandle
                                                );
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"PlatformDriverOverrideInterface - build environment",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      goto Done;
    }
  }

  Status = EFI_SUCCESS;
Done:

  if (EFI_ERROR(Status)) {
    *HandleNo = 0;
    *ImageHandleBuffer = NULL;
  }

  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
AliasLocateHandleBuffer (
  IN EFI_GUID  *Guid
  )
{
  EFI_HANDLE        *HandleBuffer;
  UINTN             NoHandles;
  EFI_STATUS        Status;

  NoHandles = 0;
  HandleBuffer = NULL;

  Status = gtBS->LocateHandleBuffer (
                   ByProtocol,
                   Guid,
                   NULL,
                   &NoHandles,
                   &HandleBuffer
                   );
  if (HandleBuffer != NULL) {
    gtBS->FreePool (HandleBuffer);
  }

  return Status;
}

EFI_STATUS
EFIAPI
CheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  )
{
  EFI_STATUS        Status;
  UINTN             Counts;

  //
  // init
  //
  Counts = 0;

  //
  // Probe mTestProtocol1Guid
  //
  Status = AliasLocateHandleBuffer (&mTestProtocol1Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mTestProtocol2Guid
  //
  Status = AliasLocateHandleBuffer (&mTestProtocol2Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol1Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol1Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol2Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol2Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol3Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol3Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol4Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol4Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol5Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol5Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol6Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol6Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol7Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol7Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol8Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol8Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol9Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol9Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol10Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol10Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol10Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol10Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mInterfaceFunctionTestProtocol11Guid
  //
  Status = AliasLocateHandleBuffer (&mInterfaceFunctionTestProtocol11Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mExternalDriverProtocol1Guid
  //
  Status = AliasLocateHandleBuffer (&mExternalDriverProtocol1Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mTestNoInterfaceProtocol1Guid
  //
  Status = AliasLocateHandleBuffer (&mTestNoInterfaceProtocol1Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mTestNoInterfaceProtocol2Guid
  //
  Status = AliasLocateHandleBuffer (&mTestNoInterfaceProtocol2Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  //
  // Probe mBusDriver3Guid
  //
  Status = AliasLocateHandleBuffer (&mBusDriver3Guid);
  if (!EFI_ERROR(Status)) {
    Counts++;
  }

  *Numbers = Counts;

  if (Counts != 0) {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

