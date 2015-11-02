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

BOOLEAN
SctMetaMatch (
    IN CHAR16   *String,
    IN CHAR16   *Pattern
    )
{
    CHAR16  c, p, l;

    for (; ;) {
        p = *Pattern;
        Pattern += 1;

        switch (p) {
        case 0:
            // End of pattern.  If end of string, TRUE match
            return (BOOLEAN)(*String ? FALSE : TRUE);

        case '*':
            // Match zero or more chars
            while (*String) {
                if (SctMetaMatch (String, Pattern)) {
                    return TRUE;
                }
                String += 1;
            }
            return SctMetaMatch (String, Pattern);

        case '?':
            // Match any one char
            if (!*String) {
                return FALSE;
            }
            String += 1;
            break;

        case '[':
            // Match char set
            c = *String;
            if (!c) {
                return FALSE;                       // syntax problem
            }

            l = 0;
            p = *Pattern++;
            while ( p ) {
                if (p == ']') {
                    return FALSE;
                }

                if (p == '-') {                     // if range of chars,
                    p = *Pattern;                   // get high range
                    if (p == 0 || p == ']') {
                        return FALSE;               // syntax problem
                    }

                    if (c >= l && c <= p) {         // if in range,
                        break;                      // it's a match
                    }
                }

                l = p;
                if (c == p) {                       // if char matches
                    break;                          // move on
                }
                p = *Pattern++;
            }

            // skip to end of match char set
            while (p && p != ']') {
                p = *Pattern;
                Pattern += 1;
            }

            String += 1;
            break;

        default:
            c = *String;
            if (c != p) {
                return FALSE;
            }

            String += 1;
            break;
        }
    }
}

BOOLEAN
SctMetaiMatch (
    IN CHAR16   *String,
    IN CHAR16   *Pattern
    )
{
    return UnicodeInterface->MetaiMatch(UnicodeInterface, String, Pattern);
}
