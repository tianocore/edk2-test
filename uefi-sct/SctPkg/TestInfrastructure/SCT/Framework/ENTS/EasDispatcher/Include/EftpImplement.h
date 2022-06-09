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

  EftpImplement.h

Abstract:

  Eftp implementation declaration.

--*/

#ifndef _EFTP_IMPLEMENT_H_
#define _EFTP_IMPLEMENT_H_

//
// 5M Octets for initialization
//
#define MAX_REAL_FILE_SIZE          10485760
#define EFTP_DEFAULT_TIMEOUT_VALUE  3
#define EFTP_DEFAULT_RETRY_VALUE    5
#define MAX_FILENAME_LEN            50
#define MAX_MODE_STR_LEN            10

//
// External functions declarations
//
EFI_STATUS
EFIAPI
EftpDispatchFileTransferComd (
  ENTS_CMD_TYPE Operation
  )
/*++

Routine Description:

  Dispatch an get_file command, download file from SCT management side.

Arguments:

  Operation - Operation type, defined in ENTS_CMD_TYPE.

Returns:

  EFI_SUCCESS           - Operation succeeded.
  EFI_UNSUPPORTED       - File was not supported.
  Others                - Some failure happened.

--*/
;

#endif
