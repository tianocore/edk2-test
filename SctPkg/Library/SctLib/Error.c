/** @file

  Copyright 2006 - 2014 Unified EFI, Inc.<BR>
  Copyright (c) 2013 - 2014, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#include "SctLibInternal.h"

/*++

Routine Description:

  Function that converts an EFI status to a string

Arguments:

  Buffer           - On return, a pointer to the buffer containing the string
  Status           - A status value

Returns:

  none

Notes:

  An IF construct is used rather than a pre-initialized array because the
  EFI status codes are UINTN values which are not constants when compiling
  for EBC. As such, the values cannot be used in pre-initialized structures.

--*/
VOID
StatusToString (
  OUT CHAR16          *Buffer,
  IN EFI_STATUS       Status
  )
{
  CHAR16          *EMsg;

  if (Status == EFI_SUCCESS) {
    EMsg = L"Success";
  } else if (Status == EFI_LOAD_ERROR) {
    EMsg = L"Load Error";
  } else if (Status == EFI_INVALID_PARAMETER) {
    EMsg = L"Invalid Parameter";
  } else if (Status == EFI_UNSUPPORTED) {
    EMsg = L"Unsupported";
  } else if (Status == EFI_BAD_BUFFER_SIZE) {
    EMsg = L"Bad Buffer Size";
  } else if (Status == EFI_BUFFER_TOO_SMALL) {
    EMsg = L"Buffer Too Small";
  } else if (Status == EFI_NOT_READY) {
    EMsg = L"Not Ready";
  } else if (Status == EFI_DEVICE_ERROR) {
    EMsg = L"Device Error";
  } else if (Status == EFI_WRITE_PROTECTED) {
    EMsg = L"Write Protected";
  } else if (Status == EFI_OUT_OF_RESOURCES) {
    EMsg = L"Out of Resources";
  } else if (Status == EFI_VOLUME_CORRUPTED) {
    EMsg = L"Volume Corrupt";
  } else if (Status == EFI_VOLUME_FULL) {
    EMsg = L"Volume Full";
  } else if (Status == EFI_NO_MEDIA) {
    EMsg = L"No Media";
  } else if (Status == EFI_MEDIA_CHANGED) {
    EMsg = L"Media changed";
  } else if (Status == EFI_NOT_FOUND) {
    EMsg = L"Not Found";
  } else if (Status == EFI_ACCESS_DENIED) {
    EMsg = L"Access Denied";
  } else if (Status == EFI_NO_RESPONSE) {
    EMsg = L"No Response";
  } else if (Status == EFI_NO_MAPPING) {
    EMsg = L"No mapping";
  } else if (Status == EFI_TIMEOUT) {
    EMsg = L"Time out";
  } else if (Status == EFI_NOT_STARTED) {
    EMsg = L"Not started";
  } else if (Status == EFI_ALREADY_STARTED) {
    EMsg = L"Already started";
  } else if (Status == EFI_ABORTED) {
    EMsg = L"Aborted";
  } else if (Status == EFI_ICMP_ERROR) {
    EMsg = L"ICMP Error";
  } else if (Status == EFI_TFTP_ERROR) {
    EMsg = L"TFTP Error";
  } else if (Status == EFI_PROTOCOL_ERROR) {
    EMsg = L"Protocol Error";
  } else if (Status == EFI_WARN_UNKNOWN_GLYPH) {
    EMsg = L"Warning Unknown Glyph";
  } else if (Status == EFI_WARN_DELETE_FAILURE) {
    EMsg = L"Warning Delete Failure";
  } else if (Status == EFI_WARN_WRITE_FAILURE) {
    EMsg = L"Warning Write Failure";
  } else if (Status == EFI_WARN_BUFFER_TOO_SMALL) {
    EMsg = L"Warning Buffer Too Small";
  } else {
    EMsg = NULL;
  }
  //
  // If we found a match, then copy it to the user's buffer.
  // Otherwise SctSPrint the hex value into their buffer.
  //
  if (EMsg != NULL) {
    SctStrCpy (Buffer, EMsg);
  } else {
    SctSPrint (Buffer, 0, L"%X", Status);
  }
}
