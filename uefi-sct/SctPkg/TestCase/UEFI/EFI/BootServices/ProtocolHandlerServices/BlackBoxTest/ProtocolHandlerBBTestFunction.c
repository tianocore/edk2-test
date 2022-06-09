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

  ProtocolHandlerBBTestFunction.c

Abstract:

  for Protocol Handler Boot Services' Interface Function Test

--*/

#include "SctLib.h"
#include "Misc.h"

/**
 *  @brief Entrypoint for gtBS->InstallProtocolInterface() Interface Function
           Test.5 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.1
//
EFI_STATUS
EFIAPI
BBTestInstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.1.2.1  InstallProtocolInterface must succeed
  // when install an EFI_NATIVE_INTERFACE type protocol to a new handle.
  //
  BBTestInstallProtocolInterfaceInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.1.2.2  InstallProtocolInterface must succeed
  // when install an EFI_NATIVE_INTERFACE type protocol to an existed handle.
  //
  BBTestInstallProtocolInterfaceInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.1.2.3  InstallProtocolInterface must succeed
  // when invoked multiple times to install the same protocol onto different handles.
  //
  BBTestInstallProtocolInterfaceInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.1.2.4  InstallProtocolInterface must succeed
  // when install multiple protocols onto the same handle.
  //
  BBTestInstallProtocolInterfaceInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.1.2.5  InstallProtocolInterface must succeed
  // when install a protocol with NULL interface.
  //
  BBTestInstallProtocolInterfaceInterfaceTestCheckPoint5 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->UninstallProtocolInterface() Interface Function
 *         Test. 10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.2
//
EFI_STATUS
EFIAPI
BBTestUninstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.2.2.1  Uninstall one non-reference protocol from a handle should succeed.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.2.2.2  Uninstall all non-reference protocols
  // from a handle should succeed.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.2.2.3  Uninstall a protocol should succeed
  // even if this protocol is still opened BY_HANDLE_PROTOCOL.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.2.2.4  Uninstall a protocol should succeed
  // even if this protocol is still opened GET_PROTOCOL.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.2.2.5  Uninstall a protocol should succeed
  // even if this protocol is still opened TEST_PROTOCOL.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.2.2.6  Uninstall a protocol should succeed
  // if the protocol is still opened BY_CHILD_CONTROLLER.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.2.2.7  Uninstall a protocol should not succeed
  // if the protocol is still opened EXCLUSIVE.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.2.2.8  Uninstall a protocol should not succeed
  // if the protocol is still opened BY_DRIVER.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.2.2.9  Uninstall a protocol should not succeed
  // if the protocol is still opened BY_DRIVER | EXCLUSIVE.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.2.2.10 Uninstall a NULL interface protocol should succeed.
  //
  BBTestUninstallProtocolInterfaceInterfaceTestCheckPoint10 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ReinstallProtocolInterface() Interface Function
 *         Test.10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.3
//
EFI_STATUS
EFIAPI
BBTestReinstallProtocolInterfaceInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.3.2.1  ReinstallProtocolInterface must succeed
  // when reinstall a non-reference protocol with new interface = old interface.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.3.2.2  ReinstallProtocolInterface must succeed
  // when reinstall a non-reference protocol with
  // new interface != old interface.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.3.2.3  ReinstallProtocolInterface must succeed
  // when reinstall a protocol being opened BY_HANDLE_PROTOCOL.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.3.2.4  ReinstallProtocolInterface must succeed
  // when reinstall a protocol being opened GET_PROTOCOL.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.3.2.5  ReinstallProtocolInterface must succeed
  // when reinstall a protocol being opened TEST_PROTOCOL.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.3.2.6  ReinstallProtocolInterface must succeed when
  // reinstall a protocol being opened BY_CHILD_CONTROLLER.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.3.2.7  ReinstallProtocolInterface should not succeed
  // when reinstall a protocol still being opened BY_DRIVER.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.3.2.8  ReinstallProtocolInterface should not succeed
  // when reinstall a protocol still being opened EXCLUSIVE.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.3.2.9  ReinstallProtocolInterface should not succeed
  // when reinstall a protocol still being opened BY_DRIVER | EXCLUSIVE.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.3.2.10 ReinstallProtocolInterface must succeed
  // when reinstall a NULL interface protocol.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint10 (StandardLib);

  //
  // Checkpoint 11:
  // 4.3.2.11  ReinstallProtocolInterface must succeed
  // when reinstall a NULL interface to a non-NULL interface.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint11 (StandardLib);
  //
  // Checkpoint 12:
  // 4.3.2.12  ReinstallProtocolInterface must succeed
  // when reinstall a non-NULL interface to a NULL interface.
  //
  BBTestReinstallProtocolInterfaceInterfaceTestCheckPoint12 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->RegisterProtocolNotify() Interface Function Test.
 *         7 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.4
//
EFI_STATUS
EFIAPI
BBTestRegisterProtocolNotifyInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.4.2.1  RegisterProtocolNotify should succeed
  // for valid parameter combination.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.4.2.2  Events that have registered for a protocol installation
  // should be signaled after the protocol has been installed/reinstalled
  // successfully at TPL_APPLICATION.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.4.2.3  Events that have registered for a protocol installation
  // with notify function TPL > TPL_CALLBACK should be signaled
  // after the protocol has been installed/reinstalled successfully at TPL_CALLBACK.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.4.2.4  Events that have registered for a protocol installation
  // with notify function TPL > TPL_NOTIFY should be signaled after
  // the protocol has been installed/reinstalled successfully at TPL_NOTIFY.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.4.2.5  After a successful installation of a protocol at TPL_APPLICATON,
  // its notification LocateHandle must succeed when the search type is
  // ByRegisterNotify and a valid search key is passed as an argument.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.4.2.6  After a successful installation of a protocol at TPL_CALLBACK,
  // its notification LocateHandle must succeed when the search type is
  // ByRegisterNotify and a valid search key is passed as an argument.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.4.2.7  After a successful installation of a protocol at TPL_NOTIFY,
  // its notification LocateHandle must succeed when the search type is
  // ByRegisterNotify and a valid search key is passed as an argument.
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint7 (StandardLib);


  //
  // Checkpoint 8:
  // Events that have been registered for protocol interface notification 
  // can be unregistered by calling CloseEvent().
  //
  BBTestRegisterProtocolNotifyInterfaceTestCheckPoint8 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->InstallMultipleProtocolInterfaces() Interface
 *         Function Test. 8 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.5
//
EFI_STATUS
EFIAPI
BBTestInstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.5.2.1  InstallMultipleProtocolInterfaces should succeed
  // when install one protocol onto a new handle.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.5.2.2  InstallMultipleProtocolInterfaces should succeed
  // when install one protocol onto an existed handle.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.5.2.3  InstallMultipleProtocolInterfaces should succeed
  // when install multiple protocols onto a new handle.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.5.2.4  InstallMultipleProtocolInterfaces should succeed
  // when install multiple protocols onto an existed handle.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.5.2.5  InstallMultipleProtocolInterfaces should not install any protocol
  // onto a handle when any of the protocols' installation was failed.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.5.2.6  InstallMultipleProtocolInterfaces at TPL_APPLICAITON will cause
  // associate events signaled that were registered by RegisterProtocolNotify.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.5.2.7  InstallMultipleProtocolInterfaces at TPL_CALLBACK will cause
  // associated events signaled that were registered by RegisterProtocolNotify.
  //
  BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.5.2.8  InstallMultipleProtocolInterfaces at TPL_NOTIFY will cause
  // associated events signaled that were registered by RegisterProtocolNotify.
  //
  //BBTestInstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->UninstallMultipleProtocolInterfaces() Interface
 *         Function Test. 10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.6
//
EFI_STATUS
EFIAPI
BBTestUninstallMultipleProtocolInterfacesInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.6.2.1  Uninstall one non-reference protocol from a handle should succeed.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.6.2.2  Uninstall all non-reference protocols from a handle
  // should succeed.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.6.2.3  Uninstall two protocol should succeed even if
  // one protocol is still opened BY_HANDLE_PROTOCOL.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.6.2.4  Uninstall two protocol should succeed
  // even if one protocol is still opened GET _PROTOCOL.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.6.2.5  Uninstall two protocol should succeed
  // even if one protocol is still opened TEST _PROTOCOL.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.6.2.6  Uninstall two protocol should succeed
  // if one protocol is still opened BY_CHILD_CONTROLLER.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.6.2.7  Uninstall two protocol should not succeed
  // if one protocol is still opened EXCLUSIVE.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.6.2.8  Uninstall two protocol should not succeed
  // if one protocol is still opened BY_DRIVER.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.6.2.9  Uninstall two protocol should not succeed
  // if one protocol is still opened BY_DRIVER | EXCLUSIVE.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.6.2.10 Uninstall two NULL interface protocol should succeed.
  //
  BBTestUninstallMultipleProtocolInterfacesInterfaceTestCheckPoint10 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->LocateHandle () Interface Function Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.7
//
EFI_STATUS
EFIAPI
BBTestLocateHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.7.2.1  Locate handle via search type "AllHandles" should retrieve
  // all handles present in the system.
  //
  BBTestLocateHandleInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.7.2.2  Locate handle via search type "ByRegisterNotify" should succeed
  // when a valid search key is passed in.
  //
  BBTestLocateHandleInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.7.2.3  Locate handle via search type "ByProtocol" should retrieve
  // all handles of a specific protocol .
  //
  BBTestLocateHandleInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.7.2.4  Locate handle via search type "ByRegisterNotify" should succeed
  // in a particular case.
  //
  BBTestLocateHandleInterfaceTestCheckPoint4 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->LocateHandleBuffer() Interface Function Test.
 *         3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.8
//
EFI_STATUS
EFIAPI
BBTestLocateHandleBufferInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.8.2.1  Locate handle via search type "AllHandles" should retrieve
  // all handles present in the system.
  //
  BBTestLocateHandleBufferInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.8.2.2  Locate handle via search type "ByRegisterNotify" should succeed
  // when a valid search key is passed in.
  //
  BBTestLocateHandleBufferInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.8.2.3  Locate handle via search type "ByProtocol" should retrieve
  // all handles of a specific protocol .
  //
  BBTestLocateHandleBufferInterfaceTestCheckPoint3 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->HandleProtocol() Interface Function Test.
 *         1 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.9
//
EFI_STATUS
EFIAPI
BBTestHandleProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.9.2.1  After a successful installation of a protocol,
  // the protocol could be retrieved by HandleProtocol.
  //
  BBTestHandleProtocolInterfaceTestCheckPoint1 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->LocateProtocol () Interface Function Test.
 *         2 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.10
//
EFI_STATUS
EFIAPI
BBTestLocateProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.10.2.1 LocateProtocol should succeed on
  // retrieving an existed protocol instance.
  //
  BBTestLocateProtocolInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.10.2.2 After a successful installation of a protocol
  // and its notification, LocateProtocol should succeed
  // when the valid registration key is passed in as parameter .
  //
  BBTestLocateProtocolInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.10.2.3 LocateProtocol should succeed on
  // retrieving an existed protocol instance with NULL interface.
  //
  BBTestLocateProtocolInterfaceTestCheckPoint3 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->LocateDevicePath() Interface Function Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.11
//
EFI_STATUS
EFIAPI
BBTestLocateDevicePathInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.11.2.1 LocateDevicePath should succeed
  // on retrieving an existed protocol instance.
  //
  BBTestLocateDevicePathInterfaceTestCheckPoint1 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ProtocolsPerHandle() Interface Function Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.12
//
EFI_STATUS
EFIAPI
BBTestProtocolsPerHandleInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.12.2.1 ProtocolsPerHandle should return correct number and GUID array
  // of protocols on a handle.
  //
  BBTestProtocolsPerHandleInterfaceTestCheckPoint1 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->OpenProtocol() function test within test case only.
 *         10 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.13
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest111 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // 4.13.2.1 OpenProtocol should succeed when opening a protocol
  // with Attributes = BY_HANDLE_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.13.2.2 OpenProtocol should succeed when opening a protocol with
  // Attributes = GET_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.13.2.3 OpenProtocol should succeed when opening a protocol with
  // Attributes = TEST_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.13.2.4 OpenProtocol should succeed when opening a protocol with
  // Attributes = BY_CHILD_CONTROLLER and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.13.2.5 OpenProtocol should succeed when opening a protocol
  // the first time with Attributes = EXCLUSIVE and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.13.2.6 OpenProtocol should succeed when opening a protocol
  // the first time with Attributes = BY_DRIVER and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.13.2.7 OpenProtocol should succeed when opening a protocol
  // the first time with Attributes = BY_DRIVER | EXCLUSIVE
  // and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint7 (StandardLib);

  //
  // Checkpoint 8:
  // 4.13.2.8 OpenProtocol should not succeed with Attributes BY_DRIVER
  // when opening a protocol already opened BY_DRIVER,
  // EXCLUSIVE, BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.13.2.9 OpenProtocol should not succeed with Attributes EXCLUSIVE
  // when opening a protocol already opened BY_DRIVER, EXCLUSIVE,
  // BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.13.2.10  OpenProtocol should not succeed with Attributes
  // BY_DRIVER | EXCLUSIVE when opening a protocol already opened BY_DRIVER,
  // EXCLUSIVE, BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest111CheckPoint10 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->OpenProtocol() function test with
 *         non-EFI driver model driver. 7 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.14
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest222 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // 4.14.2.1 OpenProtocol should succeed when opening a protocol
  // with Attributes = BY_HANDLE_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.14.2.2 OpenProtocol should succeed when opening a protocol with
  // Attributes = GET_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.14.2.3 OpenProtocol should succeed when opening a protocol with
  // Attributes = TEST_PROTOCOL and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.14.2.4 OpenProtocol should succeed when opening a protocol with
  // Attributes = BY_CHILD_CONTROLLER and other valid parameters.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.14.2.5 OpenProtocol should not succeed with Attributes BY_DRIVER
  // when opening a protocol already opened BY_DRIVER, EXCLUSIVE,
  // BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.14.2.6 OpenProtocol should not succeed with Attributes EXCLUSIVE
  // when opening a protocol already opened BY_DRIVER, EXCLUSIVE,
  // BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.14.2.7 OpenProtocol should not succeed with
  // Attributes BY_DRIVER | EXCLUSIVE when opening a protocol already opened
  // BY_DRIVER, EXCLUSIVE, BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest222CheckPoint7 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->OpenProtocol() function test with test drivers
 *         following EFI driver model. 3 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.15
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInterfaceTest333 (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // 4.15.2.1 OpenProtocol should not succeed with Attributes BY_DRIVER
  // when opening a protocol already opened BY_DRIVER, EXCLUSIVE,
  // BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest333CheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.15.2.2 OpenProtocol should not succeed with Attributes EXCLUSIVE
  // when opening a protocol already opened BY_DRIVER, EXCLUSIVE,
  // BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest333CheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.15.2.3 OpenProtocol should not succeed with Attributes
  // BY_DRIVER | EXCLUSIVE when opening a protocol already opened BY_DRIVER,
  // EXCLUSIVE, BY_DRIVER | EXCLUSIVE.
  //
  BBTestOpenProtocolInterfaceTest333CheckPoint3 (StandardLib);

  return EFI_SUCCESS;
}

/**
 *  @brief Entrypoint for gtBS->CloseProtocol() Interface Function Test.
 *         7 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.16
//
EFI_STATUS
EFIAPI
BBTestCloseProtocolInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.16.2.1 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously opened
  // BY_HANDLE_PROTOCOL.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.16.2.2 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened GET_PROTOCOL.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.16.2.3 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened TEST_PROTOCOL.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.16.2.4 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened BY_CHILD_CONTROLLER.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.16.2.5 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened BY_DRIVER.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.16.2.6 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened EXCLUSIVE.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.16.2.7 CloseProtocol should succeed with valid parameters
  // when the first time closing a protocol that was previously
  // opened BY_DRIVER | EXCLUSIVE.
  //
  BBTestCloseProtocolInterfaceTestCheckPoint7 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->OpenProtocolInformation() Interface Funtion Test.
 *         1 checkpoint will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.17
//
EFI_STATUS
EFIAPI
BBTestOpenProtocolInformationInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.17.2.1 OpenProtocolInformation should retrieve correct information
  // when open a protocol with all valid parameters.
  //
  BBTestOpenProtocolInformationInterfaceTestCheckPoint1 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->ConnectController() Interface Function Test.
 *         9 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.18
//
EFI_STATUS
EFIAPI
BBTestConnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.18.2.1 ConnectController should succeed when no driver was connected
  // to the ControllerHandle but RemainingDevicePath is an End Device Path Node.
  //
  BBTestConnectControllerInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.18.2.2 ConnectController should succeed when one device driver is found
  // for the specified handle and the driver's Start() function
  // returns EFI_SUCCESS.
  //
  BBTestConnectControllerInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.18.2.3 ConnectController should succeed when one bus driver is found
  // for the specified handle and the driver's Start() function
  // returns EFI_SUCCESS.
  //
  BBTestConnectControllerInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.18.2.4 ConnectController non-recursively for a specified bus handle
  // should not connect the child handles with their associated device drivers.
  //
  BBTestConnectControllerInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.18.2.5 ConnectController recursively for a specified bus handle
  // should connect the child handles with their associated device drivers.
  //
  BBTestConnectControllerInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.18.2.6 All drivers associated with a specified handle will be connected
  // to the handle whether ConnectController recursively or non-recursively.
  //
  BBTestConnectControllerInterfaceTestCheckPoint6 (StandardLib);

  //
  // Checkpoint 7:
  // 4.18.2.7 ConnectController should treat the DriverImageHandle list
  // in order.(first element has the highest priority).
  //
  //
  // Checkpoint 13:
  // 4.18.2.13  DriverImageHandle list's priority is higher than Driver Binding
  // version when ConnectController is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint7_13 (StandardLib);

  //
  // Checkpoint 8:
  // 4.18.2.8 ConnectController should treat the Driver list returned
  // by EFI Platform Driver Override Protocol in order.
  // (first element has the highest priority).
  //
  BBTestConnectControllerInterfaceTestCheckPoint8 (StandardLib);

  //
  // Checkpoint 9:
  // 4.18.2.9 ConnectController should treat the Driver list returned
  // by EFI Bus Specific Driver Override Protocol in order.
  // (first element has the highest priority).
  //
  BBTestConnectControllerInterfaceTestCheckPoint9 (StandardLib);

  //
  // Checkpoint 10:
  // 4.18.2.10  ConnectController should connect the driver first with
  // higher Driver Binding version.
  //
  BBTestConnectControllerInterfaceTestCheckPoint10 (StandardLib);

  //
  // Checkpoint 11:
  // 4.18.2.11  DriverImageHandle list's priority is higher than the image list
  // returned by EFI Platform Driver Override Protocol when ConnectController
  // is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint11 (StandardLib);

  //
  // Checkpoint 12:
  // 4.18.2.12  DriverImageHandle list's priority is higher than the image list
  // returned by EFI Bus Specific Driver Override Protocol when
  // ConnectController is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint12 (StandardLib);

  //
  // Checkpoint 14:
  // 4.18.2.14  The priority of the image list returned by EFI Platform Driver
  // Override Protocol is higher than the priority of the image list returned
  // by EFI Bus Specific Driver Override Protocol when ConnectController
  // is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint14 (StandardLib);

  //
  // Checkpoint 15:
  // 4.18.2.15  The priority of the image list returned by EFI Platform Driver
  // Override Protocol is higher than the priority of Driver Binding version
  // when ConnectController is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint15 (StandardLib);

  //
  // Checkpoint 16:
  // 4.18.2.16  The priority of the image list returned by EFI Bus Specific
  // Driver Override Protocol is higher than the priority of Driver Binding
  // version when ConnectController is called.
  //
  BBTestConnectControllerInterfaceTestCheckPoint16 (StandardLib);

  return EFI_SUCCESS;
}


/**
 *  @brief Entrypoint for gtBS->DisconnectController() Interface Function Test.
 *         7 checkpoints will be tested.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL
 *  @param ClientInterface A pointer to the interface array under test
 *  @param TestLevel Test "thoroughness" control
 *  @param SupportHandle A handle containing protocols required
 *  @return EFI_SUCCESS
 *  @return EFI_NOT_FOUND
 */
//
// TDS 4.19
//
EFI_STATUS
EFIAPI
BBTestDisconnectControllerInterfaceTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;

  //
  // Init
  //
  StandardLib = NULL;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //
  // Checkpoint 1:
  // 4.19.2.1 DisconnectController should succeed when disconnect a handle
  // which no driver is managing.
  //
  BBTestDisconnectControllerInterfaceTestCheckPoint1 (StandardLib);

  //
  // Checkpoint 2:
  // 4.19.2.2 DisconnectController should succeed when disconnect a handle
  // which is not managed by the driver specified by DriverImageHandle.
  //

  // Reference SCR #2644
  //BBTestDisconnectControllerInterfaceTestCheckPoint2 (StandardLib);

  //
  // Checkpoint 3:
  // 4.19.2.3 DisconnectController should succeed when disconnect a driver
  // with a handle which is managed by multiple drivers.
  //
  BBTestDisconnectControllerInterfaceTestCheckPoint3 (StandardLib);

  //
  // Checkpoint 4:
  // 4.19.2.4 DisconnectController should succeed when disconnect all drivers
  // with a handle which is managed by multiple drivers.
  //
  BBTestDisconnectControllerInterfaceTestCheckPoint4 (StandardLib);

  //
  // Checkpoint 5:
  // 4.19.2.5 When a bus driver is disconnected from its handle with
  // ChildHandle = NULL, all child handles will be destroyed.
  //
  BBTestDisconnectControllerInterfaceTestCheckPoint5 (StandardLib);

  //
  // Checkpoint 6:
  // 4.19.2.6 When a bus driver is disconnected with ChildHandle specified,
  // only the specified child handle will be destroyed.
  //
  BBTestDisconnectControllerInterfaceTestCheckPoint6 (StandardLib);

  return EFI_SUCCESS;
}

