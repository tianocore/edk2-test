/** @file

  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TslInit.h

Abstract:

  This file defines the EFI Test Support Library Initiation Interface.

  This interface provides a union format to install, uninstall, and initialize
  the test support library protocols. Using this interface the test management
  system can detect any test support libraries automatically.

--*/

#ifndef _EFI_TSL_INIT_H_
#define _EFI_TSL_INIT_H_

//
// Includes
//

//
// EFI TSL Initiation Interface Definitions
//

#define EFI_TSL_INIT_INTERFACE_GUID       \
  { 0x625c0828, 0xa47d, 0x493d, { 0xb7, 0x97, 0x97, 0x85, 0x55, 0x72, 0xdb, 0xc8 }}

#define EFI_TSL_INIT_INTERFACE_REVISION   0x00010000

//
// Forward reference for pure ANSI compatibility
//

typedef struct _EFI_TSL_INIT_INTERFACE EFI_TSL_INIT_INTERFACE;

//
// EFI TSL Initiation Interface API - Open
//
typedef
EFI_STATUS
(EFIAPI *EFI_TSL_OPEN) (
  IN     EFI_TSL_INIT_INTERFACE         *This,
  IN OUT EFI_HANDLE                     *LibHandle,
     OUT VOID                           **PrivateInterface
  )
/*++

Routine Description:

  Opens the test support library to get the handle with the public interface
  and the private interface.

Arguments:

  This              - TSL Initiation Interface instance.

  LibHandle         - The pointer to the handle on which the public interface
                      is installed.

  PrivateInterface  - The private interface of the test support library.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI TSL Initiation Interface API - Close
//
typedef
EFI_STATUS
(EFIAPI *EFI_TSL_CLOSE) (
  IN EFI_TSL_INIT_INTERFACE             *This,
  IN EFI_HANDLE                         LibHandle
  )
/*++

Routine Description:

  Closes the test support library to free the public interface.

Arguments:

  This              - TSL Initiation Interface instance.

  LibHandle         - The handle on which the public interface was installed.

Returns:

  EFI_SUCCESS if everything is correct.

--*/
;

//
// EFI TSL Initiation Interface
//

struct _EFI_TSL_INIT_INTERFACE {
  UINT64                                Revision;
  EFI_GUID                              LibraryGuid;
  EFI_TSL_OPEN                          Open;
  EFI_TSL_CLOSE                         Close;
};

//
// Global ID for EFI TSL Initiation Interface
//

extern EFI_GUID gEfiTslInitInterfaceGuid;

#endif
