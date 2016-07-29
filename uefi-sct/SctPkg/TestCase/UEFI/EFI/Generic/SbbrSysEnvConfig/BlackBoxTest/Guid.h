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

  Copyright 2006 - 2016 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2016, ARM Corporation. All rights reserved.<BR>

--*/
/*++

Module Name:

  Guid.h

Abstract:

  Definitions of GUIDs used for test progress assertions.

--*/

#ifndef _SYSENVCONFIG_GUID_H_
#define _SYSENVCONFIG_GUID_H_

#define SYSENVCONFIG_ASSERTION_001_GUID \
{0xcc5c4f70, 0xbfc9, 0x48be, {0x97, 0xf8, 0xca, 0xac, 0xfd, 0x8b, 0x97, 0x5e}}

extern EFI_GUID gSysEnvConfigAssertion001Guid;

#define SYSENVCONFIG_ASSERTION_002_GUID \
{0x6e3f022e, 0x425b, 0x42cd, {0x83, 0x07, 0xb5, 0x67, 0xb9, 0xdb, 0x3d, 0x5d}}

extern EFI_GUID gSysEnvConfigAssertion002Guid;

#define SYSENVCONFIG_ASSERTION_003_GUID \
{0x91d5b963, 0x1da8, 0x4c1d, {0x91, 0x3e, 0xd3, 0x4b, 0xb3, 0xa7, 0x3a, 0x1c}}

extern EFI_GUID gSysEnvConfigAssertion003Guid;

#define SYSENVCONFIG_ASSERTION_004_GUID \
{0x9f0b093e, 0x7606, 0x4c94, {0xa1, 0xaa, 0x85, 0x56, 0x7f, 0xd4, 0xbf, 0x15}}

extern EFI_GUID gSysEnvConfigAssertion004Guid;

#endif /* _SYSENVCONFIG_GUID_H_ */
