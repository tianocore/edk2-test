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
                                                                
  Copyright 2006 -2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  str.c

Abstract:

  String operation functions

--*/

#include "lib.h"


INTN
StrCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2
    )
// compare strings
{
    while (*s1) {
        if (*s1 != *s2) {
            break;
        }

        s1 += 1;
        s2 += 1;
    }

    return *s1 - *s2;
}

INTN
StrnCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2,
    IN UINTN    len
    )
// compare strings
{
    while (*s1  &&  len) {
        if (*s1 != *s2) {
            break;
        }

        s1  += 1;
        s2  += 1;
        len -= 1;
    }

    return len ? *s1 - *s2 : 0;
}


INTN
LibStubStriCmp (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *s1,
    IN CHAR16                           *s2
    )
{
    return StrCmp (s1, s2);
}

VOID
LibStubStrLwrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *Str
    )
{
}

INTN
StriCmp (
    IN CHAR16   *s1,
    IN CHAR16   *s2
    )
// compare strings
{
    return UnicodeInterface->StriColl(UnicodeInterface, s1, s2);
}

VOID
StrLwr (
    IN CHAR16   *Str
    )
// lwoer case string
{
    UnicodeInterface->StrLwr(UnicodeInterface, Str);
}

VOID
StrUpr (
    IN CHAR16   *Str
    )
// upper case string
{
    UnicodeInterface->StrUpr(UnicodeInterface, Str);
}

VOID
StrCpy (
    IN CHAR16   *Dest,
    IN CHAR16   *Src
    )
// copy strings
{
    while (*Src) {
        *(Dest++) = *(Src++);
    }
    *Dest = 0;
}

VOID
StrnCpy (
  OUT CHAR16                   *Dst,
  IN  CHAR16                   *Src,
  IN  UINTN                    Length
  )
/*++

Routine Description:
  Copy a string from source to destination

Arguments:
  Dst              Destination string
  Src              Source string
  Length           Length of destination string

Returns:

--*/
{
  UINTN SrcIndex;
  UINTN DstIndex;

  ASSERT (Dst != NULL);
  ASSERT (Src != NULL);
  

  SrcIndex = DstIndex = 0;
  while (DstIndex < Length) {
    Dst[DstIndex] = Src[SrcIndex];
    DstIndex++;
    SrcIndex++;
  }
  Dst[DstIndex] = 0;
}

VOID
StrTrim (
  IN OUT CHAR16   *str,
  IN     CHAR16   c
  )
{
  CHAR16  *p1;
  CHAR16  *p2;
 
  ASSERT (str != NULL);

  if (*str == 0) {
    return ;
  }
  //
  // Trim off the leading characters c
  //
  for (p1 = str; *p1 && *p1 == c; p1++) {
    ;
  }

  p2 = str;
  if (p2 == p1) {
    while (*p1) {
      p2++;
      p1++;
    }
  } else {
    while (*p1) {
      *p2 = *p1;
      p1++;
      p2++;
    }

    *p2 = 0;
  }

  for (p1 = str + StrLen (str) - 1; p1 >= str && *p1 == c; p1--) {
    ;
  }

  if (p1 != str + StrLen (str) - 1) {
    *(p1 + 1) = 0;
  }
}

VOID
StrCat (
    IN CHAR16   *Dest,
    IN CHAR16   *Src
    )
{
    StrCpy(Dest+StrLen(Dest), Src);
}

CHAR16 *
StrChr (
  IN  CHAR16  *Str,
  IN  CHAR16  c
  )
{
  ASSERT (Str != NULL);
  
  for (; *Str != c; ++Str) {
    if (*Str == '\0') {
      return NULL;
    }
  }

  return (CHAR16 *) Str;
}

CHAR8 *
StrChrAscii (
  IN  CHAR8  *Str,
  IN  CHAR8  c
  )
{
  ASSERT (Str != NULL);
  
  for (; *Str != c; ++Str) {
    if (*Str == '\0') {
      return NULL;
    }
  }

  return (CHAR8 *) Str;
}

UINTN
StrLen (
    IN CHAR16   *s1
    )
// string length
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return len;
}

UINTN
StrSize (
    IN CHAR16   *s1
    )
// string size
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return (len + 1) * sizeof(CHAR16);
}

CHAR16 *
StrDuplicate (
    IN CHAR16   *Src
    )
// duplicate a string
{
    CHAR16      *Dest;
    UINTN       Size;

    Size = StrSize(Src);
    Dest = AllocatePool (Size);
    if (Dest) {
        CopyMem (Dest, Src, Size);
    }
    return Dest;
}

UINTN
strlena (
    IN CHAR8    *s1
    )
// string length
{
    UINTN        len;

    for (len=0; *s1; s1+=1, len+=1) ;
    return len;
}

UINTN
strcmpa (
    IN CHAR8    *s1,
    IN CHAR8    *s2
    )
// compare strings
{
    while (*s1) {
        if (*s1 != *s2) {
            break;
        }

        s1 += 1;
        s2 += 1;
    }

    return *s1 - *s2;
}

UINTN
strncmpa (
    IN CHAR8    *s1,
    IN CHAR8    *s2,
    IN UINTN    len
    )
// compare strings
{
    while (*s1  &&  len) {
        if (*s1 != *s2) {
            break;
        }

        s1  += 1;
        s2  += 1;
        len -= 1;
    }

    return len ? *s1 - *s2 : 0;
}



UINTN
xtoi (
    CHAR16  *str
    )
// convert hex string to uint
{
    UINTN       u;
    CHAR16      c;

    // skip preceeding white space
    while (*str && *str == ' ') {
        str += 1;
    }

    // skip preceeding zeros
    while (*str && *str == '0') {
        str += 1;
    }

    // skip preceeding white space
    if (*str && (*str == 'x' || *str == 'X')) {
        str += 1;
    }

    // convert hex digits
    u = 0;
    c = *(str++);
    while (c) {
        if (c >= 'a'  &&  c <= 'f') {
            c -= 'a' - 'A';
        }

        if ((c >= '0'  &&  c <= '9')  ||  (c >= 'A'  &&  c <= 'F')) {
            u = (u << 4)  |  (c - (c >= 'A' ? 'A'-10 : '0'));
        } else {
            break;
        }
        c = *(str++);
    }

    return u;
}

UINTN
Atoi (
    CHAR16  *str
    )
// convert hex string to uint
{
    UINTN       u;
    CHAR16      c;

    // skip preceeding white space
    while (*str && *str == ' ') {
        str += 1;
    }

    // convert digits
    u = 0;
    c = *(str++);
    while (c) {
        if (c >= '0' && c <= '9') {
            u = (u * 10) + c - '0';
        } else {
            break;
        }
        c = *(str++);
    }

    return u;
}

UINTN
StrToUInt (
  IN  CHAR16       *Str
  )
{
  UINTN   Base;
  UINTN   Value;
  UINTN   NewValue;
  CHAR16  *StrTail;
  CHAR16  c;
  UINTN   Len;

  Base    = 10;
  Value   = 0;

  if (!*Str) {
    return 0;
  }

  StrTrim (Str, L' ');

  Len     = StrLen (Str);
  StrTail = Str + Len - 1;
  //
  // Check hex prefix '0x'
  //
  if (Len >= 2 && *Str == '0' && (*(Str + 1) == 'x' || *(Str + 1) == 'X')) {
    Str += 2;
    Len -= 2;
    Base = 16;
  }

  if (!Len) {
    return 0;
  }
  //
  // Convert the string to value
  //
  for (; Str <= StrTail; Str++) {

    c = *Str;

    if (Base == 16) {
      NewValue = Value * 16;
    } else {
      NewValue = Value * 8;
	  Value    = Value * 2;
      NewValue += Value;
      if (NewValue < Value) {
        //
        // Overflow here
        //
        return 0;
      }
    }

    Value = NewValue;

    if (Base == 16 && c >= 'a' && c <= 'f') {
      c = (CHAR16) (c - 'a' + 'A');
    }

    if (Base == 16 && c >= 'A' && c <= 'F') {
      Value += (c - 'A') + 10;
    } else if (c >= '0' && c <= '9') {
      Value += (c - '0');
    } else {
      return 0;
    }
  }

  return Value;
}

VOID
StrToUInt64 (
  IN  CHAR16       *Str,
  OUT UINT64       *Result
  )
{
  UINTN   Base;
  UINT64  Value;
  UINT64  NewValue;
  CHAR16  *StrTail;
  CHAR16  c;
  UINTN   Len;

  Base = 10;
  *Result = 0;

  if (!*Str) {
    return ;
  }

  StrTrim (Str, L' ');

  Len     = StrLen (Str);
  StrTail = Str + Len - 1;
  //
  // Check hex prefix '0x'
  //
  if (Len >= 2 && *Str == '0' && (*(Str + 1) == 'x' || *(Str + 1) == 'X')) {
    Str += 2;
    Len -= 2;
    Base = 16;
  }

  if (!Len) {
    return ;
  }
  //
  // Convert the string to value
  //
  for (Value = 0; Str <= StrTail; Str++) {

    c = *Str;

    if (Base == 16) {
      if (RShiftU64 (Value, 60)) {
        //
        // Overflow here x16
        //
        return ;
      }

      NewValue = LShiftU64 (Value, 4);
    } else {
      if (RShiftU64 (Value, 61)) {
        //
        // Overflow here x8
        //
        return ;
      }

      NewValue  = LShiftU64 (Value, 3);
      Value     = LShiftU64 (Value, 1);
      NewValue += Value;
      if (NewValue < Value) {
        //
        // Overflow here
        //
        return ;
      }
    }

    Value = NewValue;

    if (Base == 16 && c >= 'a' && c <= 'f') {
      c = (CHAR16) (c - 'a' + 'A');
    }

    if (Base == 16 && c >= 'A' && c <= 'F') {
      Value += (c - 'A') + 10;
    } else if (c >= '0' && c <= '9') {
      Value += (c - '0');
    } else {
      //
      // Unexpected char is encountered
      //
      return ;
    }
  }

  *Result = Value;
}

VOID
StrToAscii (
  IN CHAR16 *Str,
  IN CHAR8  *AsciiStr
  )
{
  ASSERT (AsciiStr != NULL);

  while (*Str != L'\0') {
    *(AsciiStr++) = (CHAR8) *(Str++);
  }
  *AsciiStr = 0;
}

CHAR16 *
SplitStr (
  IN OUT CHAR16 **List,
  IN     CHAR16 Separator
  )
{
  CHAR16  *Str;
  CHAR16  *ReturnStr;

  Str = *List;
  ReturnStr = Str;

  if (*Str == L'\0') {
    return ReturnStr;
  }

  //
  // Find first occurrence of the separator
  //
  while (*Str != L'\0') {
    if (*Str == Separator) {
      break;
    }
    Str++;
  }

  if (*Str == Separator) {
    //
    // Find a sub-string, terminate it
    //
    *Str = L'\0';
    Str++;
  }

  //
  // Move to next sub-string
  //
  *List = Str;

  return ReturnStr;
}

CHAR8 *
SplitStrAscii (
  IN OUT CHAR8 **List,
  IN     CHAR8 Separator
  )
{
  CHAR8 *Str;
  CHAR8  *ReturnStr;

  Str = *List;
  ReturnStr = Str;

  if (Str == NULL) {
    return ReturnStr;
  }

  //
  // Find first occurrence of the separator
  //
  while (*Str != '\0') {
    if (*Str == Separator) {
      break;
    }
    Str++;
  }

  if (*Str == Separator) {
    //
    // Find a sub-string, terminate it
    //
    *Str = '\0';
    Str++;
  }

  //
  // Move to next sub-string
  //
  *List = Str;

  return ReturnStr;
}

VOID
StrToIPv4Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv4_ADDRESS *IPv4Addr
  )
{
  UINTN  Index;

  for (Index = 0; Index < 4; Index++) {
    IPv4Addr->Addr[Index] = (UINT8) Atoi (SplitStr (Str, L'.'));
  }
}

VOID
StrToIPv6Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv6_ADDRESS *IPv6Addr
  )
{
  UINTN  Index;
  UINT16 Data;

  for (Index = 0; Index < 8; Index++) {
    Data = (UINT16) xtoi (SplitStr (Str, L':'));
    IPv6Addr->Addr[Index * 2] = (UINT8) (Data >> 8);
    IPv6Addr->Addr[Index * 2 + 1] = (UINT8) (Data & 0xff);
  }
}

BOOLEAN
MetaMatch (
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
                if (MetaMatch (String, Pattern)) {
                    return TRUE;
                }
                String += 1;
            }
            return MetaMatch (String, Pattern);

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
LibStubMetaiMatch (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *String,
    IN CHAR16                           *Pattern
    )
{
    return MetaMatch (String, Pattern);
}


BOOLEAN
MetaiMatch (
    IN CHAR16   *String,
    IN CHAR16   *Pattern
    )
{
    return UnicodeInterface->MetaiMatch(UnicodeInterface, String, Pattern);
}
