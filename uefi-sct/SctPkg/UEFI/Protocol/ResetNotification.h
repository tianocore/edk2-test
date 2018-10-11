/** @file

  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++           

Module Name:

  ResetNotification.h

Abstract:

  Reset Notification protocol from the UEFI specification.

--*/

#ifndef _RESET_NOTIFICATION_PROTOCOL_H_
#define _RESET_NOTIFICATION_PROTOCOL_H_


#define EFI_RESET_NOTIFICATION_PROTOCOL_GUID \
{ 0x9da34ae0, 0xeaf9, 0x4bbf, { 0x8e, 0xc3, 0xfd, 0x60, 0x22, 0x6c, 0x44, 0xbe } }


typedef struct _EFI_RESET_NOTIFICATION_PROTOCOL EFI_RESET_NOTIFICATION_PROTOCOL;

/**
  Register a notification function to be called when ResetSystem() is called.

  The RegisterResetNotify() function registers a notification function that is called when
  ResetSystem()is called and prior to completing the reset of the platform.
  The registered functions must not perform a platform reset themselves. These
  notifications are intended only for the notification of components which may need some
  special-purpose maintenance prior to the platform resetting.
  The list of registered reset notification functions are processed if ResetSystem()is called
  before ExitBootServices(). The list of registered reset notification functions is ignored if
  ResetSystem()is called after ExitBootServices().

  @param[in]  This              A pointer to the EFI_RESET_NOTIFICATION_PROTOCOL instance.
  @param[in]  ResetFunction     Points to the function to be called when a ResetSystem() is executed.

  @retval EFI_SUCCESS           The reset notification function was successfully registered.
  @retval EFI_INVALID_PARAMETER ResetFunction is NULL.
  @retval EFI_OUT_OF_RESOURCES  There are not enough resources available to register the reset notification function.
  @retval EFI_ALREADY_STARTED   The reset notification function specified by ResetFunction has already been registered.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_RESET_NOTIFY) (
  IN EFI_RESET_NOTIFICATION_PROTOCOL *This,
  IN EFI_RESET_SYSTEM                ResetFunction
);

/**
  Unregister a notification function.

  The UnregisterResetNotify() function removes the previously registered
  notification using RegisterResetNotify().

  @param[in]  This              A pointer to the EFI_RESET_NOTIFICATION_PROTOCOL instance.
  @param[in]  ResetFunction     The pointer to the ResetFunction being unregistered.

  @retval EFI_SUCCESS           The reset notification function was unregistered.
  @retval EFI_INVALID_PARAMETER ResetFunction is NULL.
  @retval EFI_INVALID_PARAMETER The reset notification function specified by ResetFunction was not previously
                                registered using RegisterResetNotify().

**/
typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_RESET_NOTIFY) (
  IN EFI_RESET_NOTIFICATION_PROTOCOL *This,
  IN EFI_RESET_SYSTEM                ResetFunction
);

typedef struct _EFI_RESET_NOTIFICATION_PROTOCOL {
  EFI_REGISTER_RESET_NOTIFY   RegisterResetNotify;
  EFI_UNREGISTER_RESET_NOTIFY UnregisterResetNotify;
} EFI_RESET_NOTIFICATION_PROTOCOL;


extern EFI_GUID gBlackBoxEfiResetNotificationProtocolGuid;

#endif
