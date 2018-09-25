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
