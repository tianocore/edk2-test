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

  Copyright 2006 - 2012 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

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
