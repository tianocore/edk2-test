/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsStr.c

Abstract:

  Ents String implementations.

--*/
#include "Efi.h"
#include <Library/EntsLib.h>
#include "SctLib.h"

#define IsDigit(c)    ((c) >= L'0' && (c) <= L'9')
#define SctIsHexDigit(c) (((c) >= L'a' && (c) <= L'f') || ((c) >= L'A' && (c) <= L'F'))

struct {
  EFI_STATUS  Status;
  CHAR16      *String;
}
EntsStatusString[] = {
  {
    EFI_SUCCESS,
    L"EFI_SUCCESS"
  },
  {
    EFI_LOAD_ERROR,
    L"EFI_LOAD_ERROR"
  },
  {
    EFI_INVALID_PARAMETER,
    L"EFI_INVALID_PARAMETER"
  },
  {
    EFI_UNSUPPORTED,
    L"EFI_UNSUPPORTED"
  },
  {
    EFI_BAD_BUFFER_SIZE,
    L"EFI_BAD_BUFFER_SIZE"
  },
  {
    EFI_BUFFER_TOO_SMALL,
    L"EFI_BUFFER_TOO_SMALL"
  },
  {
    EFI_NOT_READY,
    L"EFI_NOT_READY"
  },
  {
    EFI_DEVICE_ERROR,
    L"EFI_DEVICE_ERROR"
  },
  {
    EFI_WRITE_PROTECTED,
    L"EFI_WRITE_PROTECTED"
  },
  {
    EFI_OUT_OF_RESOURCES,
    L"EFI_OUT_OF_RESOURCES"
  },
  {
    EFI_VOLUME_CORRUPTED,
    L"EFI_VOLUME_CORRUPTED"
  },
  {
    EFI_VOLUME_FULL,
    L"EFI_VOLUME_FULL"
  },
  {
    EFI_NO_MEDIA,
    L"EFI_NO_MEDIA"
  },
  {
    EFI_MEDIA_CHANGED,
    L"EFI_MEDIA_CHANGED"
  },
  {
    EFI_NOT_FOUND,
    L"EFI_NOT_FOUND"
  },
  {
    EFI_ACCESS_DENIED,
    L"EFI_ACCESS_DENIED"
  },
  {
    EFI_NO_RESPONSE,
    L"EFI_NO_RESPONSE"
  },
  {
    EFI_NO_MAPPING,
    L"EFI_NO_MAPPING"
  },
  {
    EFI_TIMEOUT,
    L"EFI_TIMEOUT"
  },
  {
    EFI_NOT_STARTED,
    L"EFI_NOT_STARTED"
  },
  {
    EFI_ALREADY_STARTED,
    L"EFI_ALREADY_STARTED"
  },
  {
    EFI_ABORTED,
    L"EFI_ABORTED"
  },
  {
    EFI_ICMP_ERROR,
    L"EFI_ICMP_ERROR"
  },
  {
    EFI_TFTP_ERROR,
    L"EFI_TFTP_ERROR"
  },
  {
    EFI_PROTOCOL_ERROR,
    L"EFI_PROTOCOL_ERROR"
  },
  {
    EFI_INCOMPATIBLE_VERSION,
    L"EFI_INCOMPATIBLE_VERSION"
  },
  {
    EFI_SECURITY_VIOLATION,
    L"EFI_SECURITY_VIOLATION"
  },
  {
    EFI_CRC_ERROR,
    L"EFI_CRC_ERROR"
  },
  {
    EFI_NOT_AVAILABLE_YET,
    L"EFI_NOT_AVAILABLE_YET"
  },
#if (EFI_SPECIFICATION_VERSION < 0x00020028)
  {
    EFI_UNLOAD_IMAGE,
    L"EFI_UNLOAD_IMAGE"
  },
#endif
  {
    EFI_WARN_UNKNOWN_GLYPH,
    L"EFI_WARN_UNKNOWN_GLYPH"
  },
  {
    EFI_WARN_DELETE_FAILURE,
    L"EFI_WARN_DELETE_FAILURE"
  },
  {
    EFI_WARN_WRITE_FAILURE,
    L"EFI_WARN_WRITE_FAILURE"
  },
  {
    EFI_WARN_BUFFER_TOO_SMALL,
    L"EFI_WARN_BUFFER_TOO_SMALL"
  },
#if (EFI_SPECIFICATION_VERSION < 0x00020028)
  {
    EFI_WARN_RETURN_FROM_LONG_JUMP,
    L"EFI_WARN_RETURN_FROM_LONG_JUMP"
  },
#endif
  {
    EFI_MAX_BIT,
    NULL
  }
};

CHAR16  *___strtok_line   = NULL;
CHAR16  *___strtok_arg    = NULL;
CHAR16  *___strtok_field  = NULL;

INTN
EntsStrCmp (
  IN CHAR16   *s1,
  IN CHAR16   *s2
  )
{
  while (*s1) {
    if (*s1 != *s2) {
      break;
    }

    s1 += 1;
    s2 += 1;
  }

  return *s1 -*s2;
}

VOID
EntsStrCpy (
  IN CHAR16   *Dest,
  IN CHAR16   *Src
  )
{
  while (*Src) {
    *(Dest++) = *(Src++);
  }

  *Dest = 0;
}

VOID
EntsStrCat (
  IN CHAR16   *Dest,
  IN CHAR16   *Src
  )
{
  EntsStrCpy (Dest + EntsStrLen (Dest), Src);
}

UINTN
EntsStrLen (
  IN CHAR16   *s1
  )
{
  UINTN len;

  for (len = 0; *s1; s1 += 1, len += 1)
    ;
  return len;
}



VOID
EntsStrTrim (
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

  for (p1 = str + EntsStrLen (str) - 1; p1 >= str && *p1 == c; p1--) {
    ;
  }

  if (p1 != str + EntsStrLen (str) - 1) {
    *(p1 + 1) = 0;
  }
}

CHAR16 *
EntsStrDuplicate (
  IN CHAR16   *Src
  )
{
  CHAR16  *Dest;
  UINTN   Size;

  Size  = SctStrSize (Src);
  Dest  = EntsAllocatePool (Size);
  if (Dest) {
    EntsCopyMem (Dest, Src, Size);
  }

  return Dest;
}

INTN
EFIAPI
EntsLibStubStriCmp (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *s1,
  IN CHAR16                           *s2
  )
{
  return EntsStrCmp (s1, s2);
}

VOID
EFIAPI
EntsLibStubStrLwrUpr (
    IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
    IN CHAR16                           *Str
    )
{
	return;
}

BOOLEAN
EFIAPI
EntsLibStubMetaiMatch (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN CHAR16                           *Pattern
  )
{
  return SctMetaMatch (String, Pattern);
}

EFI_STATUS
Char16ToChar8 (
  IN  CHAR16 *Src,
  OUT CHAR8  *Dest,
  OUT UINTN  Size
  )
/*++

Routine Description:

  Convert a NULL-ended string of CHAR16 to CHAR8.

Arguments:

  Src   - NULL ended string of CHAR16.
  Dest  - String of CHAR8.
  Size  - The length of CHAR8 string

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  Others      - Some failure happened.

--*/
{
  CHAR8   *Tmp8;
  CHAR16  *Tmp16;

  if ((Src == NULL) || (Dest == NULL) || (Size < EntsStrLen(Src))) {
    return EFI_INVALID_PARAMETER;
  }

  EntsZeroMem (Dest, Size + 1);

  for (Tmp16 = Src; *Tmp16; Tmp16++) {
    Tmp8  = (CHAR8 *) Tmp16;
    *Dest  = *Tmp8;
    Dest++;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
Char8ToChar16 (
  IN  CHAR8  *Src,
  IN  UINTN  Size,
  OUT CHAR16 *Dest
  )
/*++

Routine Description:

  Convert a NULL-ended string of CHAR8 to CHAR16.

Arguments:

  Src   - String of CHAR8 which is not necessarily null ended.
  Size  - The byte number of CHAR8 string.
  Dest  - String of coresponding CHAR16,

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  CHAR8 *Tmp8;
  CHAR8 *Ptr;

  if ((Src == NULL) || (Dest == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  EntsZeroMem (Dest, Size * 2 + 2);

  Tmp8  = Src;
  Ptr   = (CHAR8 *) Dest;
  while (Size) {
    *Ptr++  = *Tmp8;
    *Ptr++  = 0;
    Size--;
    Tmp8++;
  }

  return EFI_SUCCESS;
}

CHAR16 *
EntsStrChr (
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

UINTN
EntsStrStr (
  IN  CHAR16  *Str,
  IN  CHAR16  *Pat
  )
/*++

Routine Description:

  Search Pat in Str.

Arguments:

  Str - String to be searched.
  Pat - Search pattern.

Returns:
  
  0 : not found
  >= 1 : found position + 1

--*/
{
  INTN  *Failure;
  INTN  i;
  INTN  j;
  INTN  Lenp;
  INTN  Lens;

  //
  // this function copies from some lib
  //
  Lenp        = EntsStrLen (Pat);
  Lens        = EntsStrLen (Str);

  Failure     = EntsAllocatePool (Lenp * sizeof (INTN));
  Failure[0]  = -1;

  for (j = 1; j < Lenp; j++) {
    i = Failure[j - 1];
    while ((Pat[j] != Pat[i + 1]) && (i >= 0)) {
      i = Failure[i];
    }

    if (Pat[i] == Pat[i + 1]) {
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

  EntsFreePool (Failure);

  //
  // 0: not found
  // >= 1: found position + 1
  //
  return ((j == Lenp) ? (i - Lenp) : -1) + 1;

}

CHAR16 *
strtok_line (
  CHAR16       *s,
  const CHAR16 *ct
  )
{
  CHAR16  *sbegin;

  CHAR16  *send;

  sbegin = s ? s : ___strtok_line;
  if (!sbegin) {
    return NULL;
  }

  sbegin += strspn (sbegin, ct);
  if (*sbegin == '\0') {
    ___strtok_line = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___strtok_line = send;
  return sbegin;
}

CHAR16 *
strtok_arg (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string
  Tokens are separated by separators defined in "ct"
  If enclosed in double quotations, other separators are invalid. Then token is 
  the content in the quotations.

--*/
{
  CHAR16  *sbegin;

  CHAR16  *send;
  INT32   l;

  sbegin = s ? s : ___strtok_arg;
  if (!sbegin) {
    return NULL;
  }

  sbegin += strspn (sbegin, ct);

  //
  // extract string enclosed in double quotation marks
  //
  if ((*sbegin == '"') || (*sbegin == 'L' && *(sbegin + 1) == '"')) {
    l = (*sbegin == 'L') ? 2 : 1;
    sbegin += l;
    if (!sbegin) {
      return NULL;
    }

    send = strpbrk (sbegin, L"\"");
    if (send && (*send != '\0')) {
      *send++ = '\0';
    }

    ___strtok_arg = send;
    return sbegin - l;
  }
  //
  // extract string separated per ct
  //
  if (*sbegin == '\0') {
    ___strtok_arg = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___strtok_arg = send;
  return sbegin;
}

CHAR16 *
strtok_field (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string.

--*/
{
  CHAR16  *sbegin;

  CHAR16  *send;

  sbegin = s ? s : ___strtok_field;
  if (!sbegin) {
    return NULL;
  }
  //
  // sbegin += strspn (sbegin, ct);
  // Different with strtok_line()
  // do not find the first substring, just use this char as sbegin
  //
  if (*sbegin == '\0') {
    ___strtok_field = NULL;
    return NULL;
  }

  send = strpbrk (sbegin, ct);
  if (send && (*send != '\0')) {
    *send++ = '\0';
  }

  ___strtok_field = send;
  return sbegin;
}

UINTN
strspn (
  const CHAR16 *s,
  const CHAR16 *accept
  )
/*++

Routine Description:

  Find the first substring.

--*/
{
  const CHAR16  *p;
  const CHAR16  *a;
  UINTN         count;

  count = 0;
  for (p = s; *p != '\0'; ++p) {
    for (a = accept; *a != '\0'; ++a) {
      if (*p == *a) {
        break;
      }
    }

    if (*a == '\0') {
      return count;
    }

    ++count;
  }

  return count;
}

CHAR16 *
strpbrk (
  const CHAR16 *cs,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Scan strings for characters in specified character sets.

--*/
{
  const CHAR16  *sc1;

  const CHAR16  *sc2;

  for (sc1 = cs; *sc1 != '\0'; ++sc1) {
    for (sc2 = ct; *sc2 != '\0'; ++sc2) {
      if (*sc1 == *sc2) {
        return (CHAR16 *) sc1;
      }
    }
  }

  return NULL;
}

EFI_STATUS
EntsStrToValue (
  IN CHAR16             *Buffer,
  OUT UINTN             *Value
  )
/*++

Routine Description:

  Convert a string to a value.

Arguments:

  Buffer  - String buffer.
  Value   - Pointer to receive the converted value.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Convert a string to a value
  //
  if (Buffer[0] == L'-') {
    *Value = (UINTN) (0 - SctAtoi (Buffer + 1));
  } else {
    *Value = SctAtoi (Buffer);
  }

  return EFI_SUCCESS;
}

INTN
EntsStrToUINTN (
  IN CHAR16        *Str,
  IN OUT UINTN     *Value
  )
{
  INTN  Index;
  UINTN Temp;

  Index = 0;
  Temp  = 0;

  if (Str[Index] == L'0' && (Str[Index + 1] == L'x' || Str[Index + 1] == L'X')) {
    Index += 2;
    while (IsDigit (Str[Index]) || SctIsHexDigit (Str[Index])) {
      if (a2i (Str[Index]) < 0) {
        return -1;
      }

      Temp = Temp * 0x10 + a2i (Str[Index]);
      Index++;
    }

    *Value = Temp;
    return Index;
  }

  while (IsDigit (Str[Index])) {
    if (a2i (Str[Index]) < 0) {
      return -1;
    }

    Temp = Temp * 10 + a2i (Str[Index]);
    Index++;
  }

  *Value = Temp;
  return Index;
}

INTN
EntsHexStrToUINTN (
  IN CHAR16        *Str,
  IN OUT UINTN     *Value
  )
{
  INTN  Index;
  UINTN Temp;

  Index = 0;
  Temp  = 0;

  while (IsDigit (Str[Index]) || SctIsHexDigit (Str[Index])) {
    if (a2i (Str[Index]) < 0) {
      return -1;
    }

    Temp = Temp * 0x10 + a2i (Str[Index]);
    Index++;
  }

  *Value = Temp;
  return Index;
}

EFI_STATUS
EntsHexValueToStr (
  IN UINTN              Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a hexadecimal value to a string.

Arguments:

  Value   - Value to be converted.
  Buffer  - Pointer to string receive buffer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Convert a value to a string
  //
  EntsSPrint (Buffer, 0, L"0x%x", Value);

  return EFI_SUCCESS;
}

EFI_STATUS
EntsStrToHexValue (
  IN CHAR16             *Buffer,
  OUT UINTN             *Value
  )
/*++

Routine Description:

  Convert a string to a hexadecimal value.

Arguments:

  Buffer  - String buffer to be converted.
  Value   - Receive value pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  CHAR16  c;

  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // skip preceeding white space
  //
  while (*Buffer && *Buffer == ' ') {
    Buffer += 1;
  }
  //
  // skip preceeding zeros
  //
  while (*Buffer && *Buffer == '0') {
    Buffer += 1;
  }
  //
  // skip preceeding white space
  //
  if (*Buffer && (*Buffer == 'x' || *Buffer == 'X')) {
    Buffer += 1;
  }

  *Value  = 0;
  c       = *(Buffer++);
  while (c) {
    if (c >= 'a' && c <= 'f') {
      c -= 'a' - 'A';
    }

    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')) {
      *Value = (*Value << 4) | (c - (c >= 'A' ? 'A' - 10 : '0'));
    } else {
      break;
    }

    c = *(Buffer++);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsBooleanToStr (
  IN BOOLEAN            Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a boolean to a string.

Arguments:

  Value   - Boolean value.
  Buffer  - Receive string buffer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Convert a boolean to a string
  //
  if (Value) {
    EntsStrCpy (Buffer, L"True");
  } else {
    EntsStrCpy (Buffer, L"False");
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsStrToBoolean (
  IN CHAR16             *Buffer,
  OUT BOOLEAN           *Value
  )
/*++

Routine Description:

  Convert a string to a boolean.

Arguments:

  Buffer  - String buffer to be converted.
  Value   - Receive value pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_UNSUPPORTED - String not supported.
  EFI_SUCCESS - Operation succeeded.
  
--*/
{
  if ((Buffer == NULL) || (Value == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (SctStriCmp (Buffer, L"True") == 0) {
    *Value = TRUE;
  } else if (SctStriCmp (Buffer, L"False") == 0) {
    *Value = FALSE;
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

BOOLEAN
EntStrBeginWith (
  IN CHAR16             *Str,
  IN CHAR16             *SubStr
  )
/*++

Routine Description:

  Test if the string is begin with the sub string.

Arguments:

  Str     - The pointer to the string being tested
  SubStr  - The pointer to the sub string

Returns:

  TRUE    - The Str is begin with SubStr.
  FALSE   - The Str not begin with SubStr.

--*/
{
  CHAR16  *Temp;

  if ((Str == NULL) || (SubStr == NULL) || (EntsStrLen (Str) < EntsStrLen (SubStr))) {
    return FALSE;
  }
  //
  // Remove the pre-space characters
  //
  Temp = SubStr;

  while (*Temp == L' ') {
    Temp = Temp + 1;
  }
  //
  // Compare
  //
  if (SctStrnCmp (Str, Temp, EntsStrLen (Temp)) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

BOOLEAN
EntsStrEndWith (
  IN CHAR16             *Str,
  IN CHAR16             *SubStr
  )
/*++

Routine Description:

  Test if the string is end with the sub string.

Arguments:

  Str     - NULL ended string.
  SubStr  - NULL ended string.

Returns:

  TRUE    - Str ends with SubStr.
  FALSE   - Str does not end with SubStr.

--*/
{
  CHAR16  *Temp;

  if ((Str == NULL) || (SubStr == NULL) || (EntsStrLen (Str) < EntsStrLen (SubStr))) {
    return FALSE;
  }

  Temp = Str + EntsStrLen (Str) - EntsStrLen (SubStr);

  //
  // Compare
  //
  if (SctStriCmp (Temp, SubStr) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}
//
// Internal functions implementations
//
EFI_STATUS
EntsValueToStr (
  IN UINTN              Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a value to a string.

Arguments:

  Value   - Value to be converted.
  Buffer  - Receive string buffer pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
{
  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Convert a value to a string
  //
  EntsSPrint (Buffer, 0, L"%d", Value);

  return EFI_SUCCESS;
}

UINTN
HexStringToValue (
  IN CHAR16             *String,
  IN UINTN              Length
  )
/*++

Routine Description:

  Convert a hex string to a value.

Arguments:

  String  - Hex string buffer.
  Length  - Hex string length.

Returns:

  Converted value.

--*/
{
  UINTN Index;
  UINTN Value;

  Value = 0;

  for (Index = 0; Index < Length; Index++) {
    if ((String[Index] >= L'0') && (String[Index] <= L'9')) {
      Value = (Value << 4) + (String[Index] - L'0');
    } else if ((String[Index] >= L'A') && (String[Index] <= L'F')) {
      Value = (Value << 4) + (String[Index] - L'A' + 10);
    } else if ((String[Index] >= L'a') && (String[Index] <= L'f')) {
      Value = (Value << 4) + (String[Index] - L'a' + 10);
    } else {
      return 0;
    }
  }

  return Value;
}

INTN
a2i (
  IN CHAR16       Ch
  )
{
  if (Ch >= L'0' && Ch <= L'9') {
    return Ch - L'0';
  }

  if (Ch >= L'a' && Ch <= L'f') {
    return Ch - L'a' + 0xa;
  }

  if (Ch >= L'A' && Ch <= L'F') {
    return Ch - L'A' + 0xA;
  }

  return -1;
}

CHAR16
i2A (
  UINTN    x
  )
{
  if (x >= 0 && x <= 9) {
    return (CHAR16) (x + '0');
  }

  if (x >= 10 && x <= 15) {
    return (CHAR16) (x - 10 + 'A');
  }

  return 0;
}

CHAR16
i2a (
  UINTN    x
  )
{
  if (x >= 0 && x <= 9) {
    return (CHAR16) (x + '0');
  }

  if (x >= 10 && x <= 15) {
    return (CHAR16) (x - 10 + 'a');
  }

  return 0;
}

EFI_STATUS
EntsStrToIp (
  IN CHAR16              *Str,
  IN OUT EFI_IP_ADDRESS  *IpAddr
  )
{
  UINT8   i;
  INTN    templen;
  CHAR16  *s;
  UINTN   temp;

  templen = 0;
  s       = Str;
  temp    = 0;

  EntsSetMem (IpAddr, sizeof (EFI_IP_ADDRESS), 0);
  for (i = 0; i < 4; i++) {
    templen = EntsStrToUINTN (s, &temp);
    if ((templen < 0) || (temp > 255)) {
      return EFI_INVALID_PARAMETER;
    }

    IpAddr->v4.Addr[i] = (UINT8) temp;
    if (i == 3) {
      break;
    }

    if (s[templen] != L'.') {
      return EFI_INVALID_PARAMETER;
    }

    s = &s[templen + 1];
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsIpToStr (
  IN EFI_IP_ADDRESS       *IpAddr,
  IN UINTN                StrSize,
  OUT CHAR16              *Str
  )
{
  EntsSPrint (
    Str,
    StrSize,
    L"%d.%d.%d.%d",
    IpAddr->v4.Addr[0],
    IpAddr->v4.Addr[1],
    IpAddr->v4.Addr[2],
    IpAddr->v4.Addr[3]
    );

  return EFI_SUCCESS;
}

EFI_STATUS
EntsStrToMac (
  IN CHAR16              *Str,
  IN OUT EFI_MAC_ADDRESS *MacAddr
  )
{
  UINT8   i;
  INTN    templen;
  CHAR16  *s;
  UINTN   temp;

  templen = 0;
  s       = Str;
  temp    = 0;

  EntsSetMem (MacAddr, sizeof (EFI_MAC_ADDRESS), 0);
  for (i = 0; i < 6; i++) {
    templen = EntsHexStrToUINTN (s, &temp);
    if ((templen < 0) || (temp > 255)) {
      return EFI_INVALID_PARAMETER;
    }

    MacAddr->Addr[i] = (UINT8) temp;
    if (i == 5) {
      break;
    }

    if (s[templen] != L':') {
      return EFI_INVALID_PARAMETER;
    }

    s = &s[templen + 1];
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EntsMacToStr (
  IN OUT EFI_MAC_ADDRESS *MacAddr,
  IN UINTN               StrSize,
  OUT CHAR16             *Str
  )
{
  EntsSPrint (
    Str,
    StrSize,
    L"%02x:%02x:%02x:%02x:%02x:%02x",
    MacAddr->Addr[0],
    MacAddr->Addr[1],
    MacAddr->Addr[2],
    MacAddr->Addr[3],
    MacAddr->Addr[4],
    MacAddr->Addr[5]
    );

  return EFI_SUCCESS;
}

EFI_STATUS
EntsTimeToStr (
  IN EFI_TIME            *Time,
  IN UINTN               StrSize,
  IN OUT CHAR16          *Str
  )
{
  EntsSPrint (
    Str,
    StrSize,
    L"%02d-%02d-%04d,%02d:%02d:%02d",
    Time->Day,
    Time->Month,
    Time->Year,
    Time->Hour,
    Time->Minute,
    Time->Second
    );

  return EFI_SUCCESS;
}

EFI_STATUS
EntsStatusToStr (
  IN EFI_STATUS          Status,
  IN UINTN               StrSize,
  IN OUT CHAR16          *Str
  )
{
  BOOLEAN Found;
  UINTN   Index;

  Found = FALSE;
  Index = 0;
  while (Found != TRUE) {
    if ((Status == EntsStatusString[Index].Status) || (EFI_MAX_BIT == EntsStatusString[Index].Status)) {
      Found = TRUE;
      EntsSPrint (Str, StrSize, L"%s", EntsStatusString[Index].String);
      break;
    } else {
      Index++;
    }
  }

  return EFI_SUCCESS;
}

CHAR8
M2S (
  IN CHAR8                     Ch
  )
{
  if (Ch <= 0x09) {
    return Ch + '0';
  }

  if (Ch >= 0xa && Ch <= 0xf) {
    return Ch - 0xa + 'a';
  }

  return 0xff;
}

EFI_STATUS
MemToString (
  IN VOID                      *Mem,
  IN OUT CHAR16                *String,
  IN UINT32                    MemSize
  )
/*++

Routine Description:

  Convert Memory to a Unicode string.

Arguments:

  Mem     - Memory buffer to be converted.
  String  - Receive string buffer pointer.
  MemSize - Memory buffer size.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  UINT32  Index;

  for (Index = 0; Index < MemSize; Index++) {
    *((CHAR16 *) String + Index * 2)      = (CHAR16) M2S ((*((CHAR8 *) Mem + Index) & 0xF0) >> 4);
    *((CHAR16 *) String + Index * 2 + 1)  = (CHAR16) M2S (*((CHAR8 *) Mem + Index) & 0x0F);
  }

  *(String + Index * 2) = L'\0';

  return EFI_SUCCESS;
}

CHAR8
S2M (
  IN CHAR8                     Ch
  )
{
  if (Ch >= '0' && Ch <= '9') {
    return Ch - '0';
  }

  if (Ch >= 'a' && Ch <= 'f') {
    return Ch - 'a' + 0xa;
  }

  if (Ch >= 'A' && Ch <= 'F') {
    return Ch - 'A' + 0xa;
  }

  return 0xff;
}

EFI_STATUS
StringToMem (
  IN CHAR16                    *String,
  IN OUT VOID                  *Mem,
  IN UINT32                    MemSize
  )
/*++

Routine Description:

  Convert a Unicode string to Memory.

Arguments:

  String  - Unicode string buffer.
  Mem     - Receive memory buffer pointer.
  MemSize - Receive memory buffer size.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  UINT32  Index;

  for (Index = 0; (Index < MemSize) && (*(String + Index * 2) != L'\0'); Index++) {
    *((CHAR8 *) Mem + Index) = 0;
    *((CHAR8 *) Mem + Index) |= S2M ((CHAR8) *((CHAR16 *) String + Index * 2)) << 4;
    *((CHAR8 *) Mem + Index) |= S2M ((CHAR8) *((CHAR16 *) String + Index * 2 + 1));
  }

  return EFI_SUCCESS;
}

