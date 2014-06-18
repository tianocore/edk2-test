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

// compare strings
INTN
SctStrCmp (
  IN CONST CHAR16   *s1,
  IN CONST CHAR16   *s2
  )
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

// compare strings
INTN
SctStrnCmp (
  IN CONST CHAR16   *s1,
  IN CONST CHAR16   *s2,
  IN UINTN    len
  )
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


// compare strings
INTN
SctStriCmp (
  IN CONST CHAR16   *s1,
  IN CONST CHAR16   *s2
  )
{
  return UnicodeInterface->StriColl(UnicodeInterface, (CHAR16 *)s1, (CHAR16 *)s2);
}

// lower case string
VOID
SctStrLwr (
  IN CHAR16                   *Str
  )
{
  UnicodeInterface->StrLwr (UnicodeInterface, Str);
}

// upper case string
VOID
SctStrUpr (
  IN CHAR16                   *Str
  )
{
  UnicodeInterface->StrUpr (UnicodeInterface, Str);
}

// copy strings
VOID
SctStrCpy (
    IN CHAR16   *Dest,
    IN CONST CHAR16   *Src
    )
{
  while (*Src) {
      *(Dest++) = *(Src++);
  }
  *Dest = 0;
}

/*++

Routine Description:
  Copy a string from source to destination

Arguments:
  Destination      Destination string
  Source           Source string
  Length           Max number of chars to copy

Returns:

--*/
VOID
SctStrnCpy (
  OUT CHAR16                   *Destination,
  IN  CONST CHAR16             *Source,
  IN  UINTN                    Length
  )
{
  if (Length == 0) {
    return;
  }

  //
  // Destination cannot be NULL if Length is not zero
  //
  ASSERT (Destination != NULL);
  ASSERT (((UINTN) Destination & 1) == 0);

  //
  // Destination and source cannot overlap
  //
  ASSERT ((UINTN)(Destination - Source) > SctStrLen (Source));
  ASSERT ((UINTN)(Source - Destination) >= Length);

  while ((*Source != L'\0') && (Length > 0)) {
    *(Destination++) = *(Source++);
    Length--;
  }

  SctZeroMem (Destination, Length * sizeof (*Destination));
}

VOID
SctStrTrim (
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

  for (p1 = str + SctStrLen (str) - 1; p1 >= str && *p1 == c; p1--) {
    ;
  }

  if (p1 != str + SctStrLen (str) - 1) {
    *(p1 + 1) = 0;
  }
}

VOID
SctStrCat (
    IN CHAR16   *Dest,
    IN CONST CHAR16   *Src
    )
{
  SctStrCpy (Dest+SctStrLen (Dest), Src);
}

CHAR16 *
SctStrChr (
  IN  CHAR16  *Str,
  IN  CHAR16  c
  )
{
  ASSERT (Str != NULL);

  for (; *Str != c; ++Str) {
    if (*Str == L'\0') {
      return NULL;
    }
  }

  return (CHAR16 *) Str;
}

CHAR8 *
SctSctAsciiStrChr (
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

// string length
UINTN
SctStrLen (
  IN CONST CHAR16   *s1
  )
{
  UINTN        len;

  for (len=0; *s1; s1+=1, len+=1) ;
  return len;
}

// string size
UINTN
SctStrSize (
  IN CONST CHAR16   *s1
  )
{
  UINTN        len;

  for (len=0; *s1; s1+=1, len+=1) ;
  return (len + 1) * sizeof(CHAR16);
}

// duplicate a string
CHAR16 *
SctStrDuplicate (
  IN CONST CHAR16   *Src
  )
{
  CHAR16      *Dest;
  UINTN       Size;

  Size = SctStrSize (Src);
  Dest = SctAllocatePool (Size);
  if (Dest) {
      SctCopyMem (Dest, Src, Size);
  }
  return Dest;
}

CHAR16*
SctStrStr (
  IN  CONST CHAR16  *Str,
  IN  CONST CHAR16  *Pat
  )
{
  //
  // Name:
  //    StrStr -- Search Pat in Str
  // In:
  //    Str -- mother string
  //    Pat -- search pattern
  // Out:
  //     0 : not found
  //    >= 1 : found position + 1
  //
  INTN  *Failure;
  INTN  i;
  INTN  j;
  INTN  Lenp;
  INTN  Lens;

  ASSERT (Pat != NULL);
  ASSERT (Str != NULL);

  //
  // this function copies from some lib
  //
  Lenp  = SctStrLen (Pat);
  Lens  = SctStrLen (Str);

  if (0 == Lenp || 0 == Lens) {
    return 0;
  }

  Failure     = SctAllocatePool (Lenp * sizeof (INTN));
  Failure[0]  = -1;

  for (j = 1; j < Lenp; j++) {
    i = Failure[j - 1];
    while ((Pat[j] != Pat[i + 1]) && (i >= 0)) {
      i = Failure[i];
    }

    if (Pat[j] == Pat[i + 1]) {
      Failure[j] = i + 1;
    } else {
      Failure[j] = -1;
    }
  }

  i = 0;
  j = 0;
  while (i < Lens && j < Lenp) {
    if (Str[i] == Pat[j]) {
      i++;
      j++;
    } else if (j == 0) {
      i++;
    } else {
      j = Failure[j - 1] + 1;
    }
  }

  SctFreePool (Failure);

  //
  // 0: not found
  // >= 1: found position + 1
  //
  if (j == Lenp) {
    return (CHAR16 *) Str + ((i - Lenp) + 1);
  } else {
    return NULL;
  }
}

CHAR8 *
SctAsciiStrDuplicate (
  CONST CHAR8       *str
  )
{
  CHAR8 *copy;

  if (str != NULL) {
    copy = SctAllocatePool (SctAsciiStrLen (str) + 1);
    if (copy != NULL)
      return SctAsciiStrCpy (copy, str);
  }
  return NULL;
}

/**
  Copies one Null-terminated ASCII string to another Null-terminated ASCII
  string and returns the new ASCII string.

  This function copies the contents of the ASCII string Source to the ASCII
  string Destination, and returns Destination. If Source and Destination
  overlap, then the results are undefined.

  If Destination is NULL, then ASSERT().
  If Source is NULL, then ASSERT().
  If Source and Destination overlap, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and Source contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().

  @param  Destination A pointer to a Null-terminated ASCII string.
  @param  Source      A pointer to a Null-terminated ASCII string.

  @return Destination

**/
CHAR8 *
EFIAPI
SctAsciiStrCpy (
  OUT     CHAR8                     *Destination,
  IN      CONST CHAR8               *Source
  )
{
  CHAR8                             *ReturnValue;

  //
  // Destination cannot be NULL
  //
  ASSERT (Destination != NULL);

  //
  // Destination and source cannot overlap
  //
  ASSERT ((UINTN)(Destination - Source) > SctAsciiStrLen (Source));
  ASSERT ((UINTN)(Source - Destination) > SctAsciiStrLen (Source));

  ReturnValue = Destination;
  while (*Source != 0) {
    *(Destination++) = *(Source++);
  }
  *Destination = 0;
  return ReturnValue;
}

CHAR8 *
SctAsciiStrnCpy (
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  )
{
  CHAR8 *d;
  CHAR8 *s;

  d = dst;
  s = src;
  if (n != 0) {
    do {
      if ((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while (--n != 0)
          *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  return (dst);
}

UINTN
EFIAPI
SctAsciiStrLen (
  IN      CONST CHAR8               *String
  )
{
  UINTN        Length;

  for (Length = 0; *String; String += 1, Length += 1) ;
  return Length;
}

/*++

Routine Description:
  Return the number bytes in the Ascii String. This is not the same as
  the length of the string in characters. The string size includes the NULL

Arguments:
  String - String to process

Returns:
  Number of bytes in String

--*/
UINTN
SctAsciiStrSize (
  IN CONST CHAR8   *String
  )
{
  return (SctAsciiStrLen (String) + 1);
}


STATIC
CHAR8
AsciiToUpper (
  CHAR8 Chr
  )
{
  return (UINT8) ((Chr >= 'a' && Chr <= 'z') ? Chr - ('a' - 'A') : Chr);
}

/**
  Performs a case insensitive comparison of two Null-terminated ASCII strings,
  and returns the difference between the first mismatched ASCII characters.

  This function performs a case insensitive comparison of the Null-terminated
  ASCII string FirstString to the Null-terminated ASCII string SecondString. If
  FirstString is identical to SecondString, then 0 is returned. Otherwise, the
  value returned is the first mismatched lower case ASCII character in
  SecondString subtracted from the first mismatched lower case ASCII character
  in FirstString.

  If FirstString is NULL, then ASSERT().
  If SecondString is NULL, then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and FirstString contains more than
  PcdMaximumAsciiStringLength ASCII characters, not including the Null-terminator,
  then ASSERT().
  If PcdMaximumAsciiStringLength is not zero and SecondString contains more
  than PcdMaximumAsciiStringLength ASCII characters, not including the
  Null-terminator, then ASSERT().

  @param  FirstString   A pointer to a Null-terminated ASCII string.
  @param  SecondString  A pointer to a Null-terminated ASCII string.

  @retval ==0    FirstString is identical to SecondString using case insensitive
                 comparisons.
  @retval !=0    FirstString is not identical to SecondString using case
                 insensitive comparisons.

**/
INTN
SctAsciiStriCmp (
  IN      CONST CHAR8               *FirstString,
  IN      CONST CHAR8               *SecondString
  )
{
  CHAR8  UpperFirstString;
  CHAR8  UpperSecondString;

  //
  // ASSERT both strings are less long than PcdMaximumAsciiStringLength
  //
  ASSERT (SctAsciiStrSize (FirstString));
  ASSERT (SctAsciiStrSize (SecondString));

  UpperFirstString  = AsciiToUpper (*FirstString);
  UpperSecondString = AsciiToUpper (*SecondString);
  while ((*FirstString != '\0') && (UpperFirstString == UpperSecondString)) {
    FirstString++;
    SecondString++;
    UpperFirstString  = AsciiToUpper (*FirstString);
    UpperSecondString = AsciiToUpper (*SecondString);
  }

  return UpperFirstString - UpperSecondString;
}

CHAR8 *
EFIAPI
SctAsciiStrCat (
  IN OUT CHAR8    *Destination,
  IN CONST CHAR8  *Source
  )
{
  return SctAsciiStrCpy (Destination + SctAsciiStrLen (Destination), Source);
}

/*++

Routine Description:

  Find a character in a string.

Arguments:

  String      - Null-terminated source string. .
  c           - Character to be located.

Returns:

  Returns a pointer to the first occurrence of c in string.

--*/
CHAR8*
EFIAPI
SctAsciiStrChr (
  IN  CHAR8  *String,
  IN  CHAR8  c
  )
{
  while (*String != '\0') {
    if (*String == c) {
      return String;
    }
    String ++;
  }
  return NULL;
}

/*++

Routine Description:

  Find a Ascii substring.

Arguments:

  String      - Null-terminated Ascii string to search.
  StrCharSet  - Null-terminated Ascii string to search for.

Returns:

  The address of the first occurrence of the matching Ascii substring if successful, or NULL otherwise.

--*/
CHAR8*
EFIAPI
SctAsciiStrStr (
  IN  CHAR8  *String,
  IN  CHAR8  *StrCharSet
  )
{
  CHAR8 *Src;
  CHAR8 *Sub;

  Src = String;
  Sub = StrCharSet;

  while ((*String != '\0') && (*StrCharSet != '\0')) {
    if (*String++ != *StrCharSet++) {
      String = ++Src;
      StrCharSet = Sub;
    }
  }
  if (*StrCharSet == '\0') {
    return Src;
  } else {
    return NULL;
  }
}

UINTN
SctUnicodeToAscii (
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *s = (CHAR8) (*pwcs++ & 0x00ff);
    if (*s++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}

UINTN
SctAsciiToUnicode (
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *pwcs = (CHAR16)(*s++ & 0x00ff);
    if (*pwcs++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}

// compare strings
UINTN
SctAsciiStrCmp (
    IN CHAR8    *s1,
    IN CHAR8    *s2
    )
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

// compare strings
UINTN
SctAsciiStrnCmp (
    IN CHAR8    *s1,
    IN CHAR8    *s2,
    IN UINTN    len
    )
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

// convert hex string to uint
UINTN
SctXtoi (
    CHAR16  *str
    )
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

// convert hex string to uint
UINTN
SctAtoi (
    CHAR16  *str
    )
{
  UINTN       u;
  CHAR16      c;

  // skip preceeding white space
  while (*str && *str == L' ') {
      str += 1;
  }

  // convert digits
  u = 0;
  c = *(str++);
  while (c) {
      if (c >= L'0' && c <= L'9') {
          u = (u * 10) + c - L'0';
      } else {
          break;
      }
      c = *(str++);
  }

  return u;
}

UINTN
SctStrToUInt (
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

  SctStrTrim (Str, L' ');

  Len     = SctStrLen (Str);
  StrTail = Str + Len - 1;
  //
  // Check hex prefix '0x'
  //
  if (Len >= 2 && *Str == L'0' && (*(Str + 1) == L'x' || *(Str + 1) == L'X')) {
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

    if (Base == 16 && c >= L'a' && c <= L'f') {
      c = (CHAR16) (c - L'a' + L'A');
    }

    if (Base == 16 && c >= L'A' && c <= L'F') {
      Value += (c - L'A') + 10;
    } else if (c >= L'0' && c <= L'9') {
      Value += (c - L'0');
    } else {
      return 0;
    }
  }

  return Value;
}

VOID
SctStrToUInt64 (
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

  SctStrTrim (Str, L' ');

  Len     = SctStrLen (Str);
  StrTail = Str + Len - 1;
  //
  // Check hex prefix '0x'
  //
  if (Len >= 2 && *Str == L'0' && (*(Str + 1) == L'x' || *(Str + 1) == L'X')) {
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
      if (SctRShiftU64 (Value, 60)) {
        //
        // Overflow here x16
        //
        return ;
      }

      NewValue = SctLShiftU64 (Value, 4);
    } else {
      if (SctRShiftU64 (Value, 61)) {
        //
        // Overflow here x8
        //
        return ;
      }

      NewValue  = SctLShiftU64 (Value, 3);
      Value     = SctLShiftU64 (Value, 1);
      NewValue += Value;
      if (NewValue < Value) {
        //
        // Overflow here
        //
        return ;
      }
    }

    Value = NewValue;

    if (Base == 16 && c >= L'a' && c <= L'f') {
      c = (CHAR16) (c - L'a' + L'A');
    }

    if (Base == 16 && c >= L'A' && c <= L'F') {
      Value += (c - L'A') + 10;
    } else if (c >= L'0' && c <= L'9') {
      Value += (c - L'0');
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
SctStrToAscii (
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
SctSplitStr (
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
SctAsciiSplitStr (
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
SctStrToIPv4Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv4_ADDRESS *IPv4Addr
  )
{
  UINTN  Index;

  for (Index = 0; Index < 4; Index++) {
    IPv4Addr->Addr[Index] = (UINT8) SctAtoi (SctSplitStr (Str, L'.'));
  }
}

VOID
SctStrToIPv6Addr (
  IN OUT CHAR16           **Str,
  OUT    EFI_IPv6_ADDRESS *IPv6Addr
  )
{
  UINTN  Index;
  UINT16 Data;

  for (Index = 0; Index < 8; Index++) {
    Data = (UINT16) SctXtoi (SctSplitStr (Str, L':'));
    IPv6Addr->Addr[Index * 2] = (UINT8) (Data >> 8);
    IPv6Addr->Addr[Index * 2 + 1] = (UINT8) (Data & 0xff);
  }
}

CONST CHAR8 mHex[] = {'0','1','2','3','4','5','6','7',
                      '8','9','A','B','C','D','E','F'};

VOID
SctValueToHexStr (
  IN CHAR16      *Buffer,
  IN UINT64      v,
  IN UINTN       Flags,
  IN UINTN       Width
  )
{
    CHAR8           str[30], *p1;
    CHAR16          *p2;

    if (!v) {
        Buffer[0] = L'0';
        Buffer[1] = 0;
        return ;
    }

    p1 = str;
    p2 = Buffer;

    while (v) {
        *(p1++) = mHex[v & 0xf];
        v = SctRShiftU64 (v, 4);
    }

    while (p1 != str) {
        *(p2++) = *(--p1);
    }
    *p2 = 0;
}
BOOLEAN
SctIsHexDigit (
  OUT UINT8      *Digit,
  IN  CHAR16      Char
  )
/*++

  Routine Description:
    Determines if a Unicode character is a hexadecimal digit.
    The test is case insensitive.

  Arguments:
    Digit - Pointer to byte that receives the value of the hex character.
    Char  - Unicode character to test.

  Returns:
    TRUE  - If the character is a hexadecimal digit.
    FALSE - Otherwise.

--*/
{
  if ((Char >= L'0') && (Char <= L'9')) {
    *Digit = (UINT8) (Char - L'0');
    return TRUE;
  }

  if ((Char >= L'A') && (Char <= L'F')) {
    *Digit = (UINT8) (Char - L'A' + 0x0A);
    return TRUE;
  }

  if ((Char >= L'a') && (Char <= L'f')) {
    *Digit = (UINT8) (Char - L'a' + 0x0A);
    return TRUE;
  }

  return FALSE;
}

CHAR16
SctNibbleToHexChar (
  IN UINT8      Nibble
  )
/*++

  Routine Description:
    Converts the low nibble of a byte  to hex unicode character.

  Arguments:
    Nibble - lower nibble of a byte.

  Returns:
    Hex unicode character.

--*/
{
  Nibble &= 0x0F;
  if (Nibble <= 0x9) {
    return (CHAR16)(Nibble + L'0');
  }

  return (CHAR16)(Nibble - 0xA + L'A');
}

EFI_STATUS
SctHexStringToBuf (
  IN OUT UINT8                     *Buf,
  IN OUT UINTN                    *Len,
  IN     CHAR16                    *Str,
  OUT    UINTN                     *ConvertedStrLen  OPTIONAL
  )
/*++

  Routine Description:
    Converts Unicode string to binary buffer.
    The conversion may be partial.
    The first character in the string that is not hex digit stops the conversion.
    At a minimum, any blob of data could be represented as a hex string.

  Arguments:
    Buf    - Pointer to buffer that receives the data.
    Len    - Length in bytes of the buffer to hold converted data.
                If routine return with EFI_SUCCESS, containing length of converted data.
                If routine return with EFI_BUFFER_TOO_SMALL, containg length of buffer desired.
    Str    - String to be converted from.
    ConvertedStrLen - Length of the Hex String consumed.

  Returns:
    EFI_SUCCESS: Routine Success.
    EFI_BUFFER_TOO_SMALL: The buffer is too small to hold converted data.
    EFI_

--*/
{
  UINTN       HexCnt;
  UINTN       Idx;
  UINTN       BufferLength;
  UINT8       Digit;
  UINT8       Byte;

  //
  // Find out how many hex characters the string has.
  //
  for (Idx = 0, HexCnt = 0; SctIsHexDigit (&Digit, Str[Idx]); Idx++, HexCnt++);

  if (HexCnt == 0) {
    *Len = 0;
    return EFI_SUCCESS;
  }
  //
  // Two Unicode characters make up 1 buffer byte. Round up.
  //
  BufferLength = (HexCnt + 1) / 2;

  //
  // Test if  buffer is passed enough.
  //
  if (BufferLength > (*Len)) {
    *Len = BufferLength;
    return EFI_BUFFER_TOO_SMALL;
  }

  *Len = BufferLength;

  for (Idx = 0; Idx < HexCnt; Idx++) {

    SctIsHexDigit (&Digit, Str[HexCnt - 1 - Idx]);

    //
    // For odd charaters, write the lower nibble for each buffer byte,
    // and for even characters, the upper nibble.
    //
    if ((Idx & 1) == 0) {
      Byte = Digit;
    } else {
      Byte = Buf[Idx / 2];
      Byte &= 0x0F;
      Byte = (UINT8)(Byte | (Digit << 4));
    }

    Buf[Idx / 2] = Byte;
  }

  if (ConvertedStrLen != NULL) {
    *ConvertedStrLen = HexCnt;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
SctBufToHexString (
  IN OUT CHAR16                    *Str,
  IN OUT UINTN                     *HexStringBufferLength,
  IN     UINT8                     *Buf,
  IN     UINTN                      Len
  )
/*++

  Routine Description:
    Converts binary buffer to Unicode string.
    At a minimum, any blob of data could be represented as a hex string.

  Arguments:
    Str - Pointer to the string.
    HexStringBufferLength - Length in bytes of buffer to hold the hex string. Includes tailing '\0' character.
                                        If routine return with EFI_SUCCESS, containing length of hex string buffer.
                                        If routine return with EFI_BUFFER_TOO_SMALL, containg length of hex string buffer desired.
    Buf - Buffer to be converted from.
    Len - Length in bytes of the buffer to be converted.

  Returns:
    EFI_SUCCESS: Routine success.
    EFI_BUFFER_TOO_SMALL: The hex string buffer is too small.

--*/
{
  UINTN       Idx;
  UINT8       Byte;
  UINTN       StrLen;

  //
  // Make sure string is either passed or allocate enough.
  // It takes 2 Unicode characters (4 bytes) to represent 1 byte of the binary buffer.
  // Plus the Unicode termination character.
  //
  StrLen = Len * 2;
  if (StrLen > ((*HexStringBufferLength) - 1)) {
    *HexStringBufferLength = StrLen + 1;
    return EFI_BUFFER_TOO_SMALL;
  }

  *HexStringBufferLength = StrLen + 1;
  //
  // Ends the string.
  //
  Str[StrLen] = L'\0';

  for (Idx = 0; Idx < Len; Idx++) {

    Byte = Buf[Idx];
    Str[StrLen - 1 - Idx * 2] = SctNibbleToHexChar (Byte);
    Str[StrLen - 2 - Idx * 2] = SctNibbleToHexChar ((UINT8)(Byte >> 4));
  }

  return EFI_SUCCESS;
}
