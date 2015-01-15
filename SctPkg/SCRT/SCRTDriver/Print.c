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
                                                                
  Copyright 2006 - 2014 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Print.c

Abstract:

  Provide a method to print text message to COM1 and COM2 synchronously. Printf() enables
  very simple implemenation to support debug. 

  You can not Print more than EFI_DRIVER_LIB_MAX_PRINT_BUFFER characters at a 
  time. This makes the implementation very simple.

  Printf, SPrint format specification has the follwoing form

  %[flags][width]type

  flags:
    '-' - Left justify
    '+' - Prefix a sign
    ' ' - Prefix a blank
    ',' - Place commas in numberss
    '0' - Prefix for width with zeros
    'l' - UINT64
    'L' - UINT64

  width:
    '*' - Get width from a UINTN argumnet from the argument list
    Decimal number that represents width of print

  type:
    'X' - argument is a UINTN hex number, prefix '0'
    'x' - argument is a hex number
    'd' - argument is a decimal number
    'a' - argument is an ascii string 
    'S','s' - argument is an Unicode string
    'g' - argument is a pointer to an EFI_GUID
    't' - argument is a pointer to an EFI_TIME structure
    'c' - argument is an ascii character
    'r' - argument is EFI_STATUS
    '%' - Print a %

--*/

#include "SCRTDriver.h"


#define LEFT_JUSTIFY  0x01
#define PREFIX_SIGN   0x02
#define PREFIX_BLANK  0x04
#define COMMA_TYPE    0x08
#define LONG_TYPE     0x10
#define PREFIX_ZERO   0x20
#define STRING_W(_s)   _s
//
// Length of temp string buffer to store value string.
//
#define CHARACTER_NUMBER_FOR_VALUE   30
#define EFI_MAX_PRINT_BUFFER         1024


#ifndef VA_START
typedef CHAR8 *VA_LIST;
#define VA_START(ap, v) (ap = (VA_LIST) & (v) + _EFI_INT_SIZE_OF (v))
#define VA_ARG(ap, t)   (*(t *) ((ap += _EFI_INT_SIZE_OF (t)) - _EFI_INT_SIZE_OF (t)))
#define VA_END(ap)      (ap = (VA_LIST) 0)
#endif

static CHAR8 mHexStr[] = { '0', '1', '2', '3', '4', '5', '6', '7',
                            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
STATIC
CHAR8 *
GetFlagsAndWidth (
  IN  CHAR8      *Format, 
  OUT UINTN       *Flags, 
  OUT UINTN       *Width,
  IN OUT  VA_LIST *Marker
  )
/*++

Routine Description:

  VSPrint worker function that parses flag and width information from the 
  Format string and returns the next index into the Format string that needs
  to be parsed. See file headed for details of Flag and Width.

Arguments:

  Format - Current location in the VSPrint format string.

  Flags  - Returns flags

  Width  - Returns width of element

  Marker - Vararg list that may be paritally consumed and returned.

Returns: 

  Pointer indexed into the Format string for all the information parsed
  by this routine.

--*/  
;

STATIC
UINTN
GuidToString (
  IN  EFI_GUID  *Guid,
  IN OUT CHAR8 *Buffer,
  IN  UINTN     BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints an EFI_GUID.

Arguments:

  Guid       - Pointer to GUID to print.

  Buffer     - Buffe to print Guid into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
;

STATIC
UINTN
TimeToString (
  IN  EFI_TIME  *Time,
  IN OUT CHAR8 *Buffer,
  IN  UINTN     BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints EFI_TIME.

Arguments:

  Time       - Pointer to EFI_TIME sturcture to print.

  Buffer     - Buffer to print Time into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
;

STATIC
UINTN
EfiStatusToString (
  IN EFI_STATUS   Status,
  OUT CHAR8      *Buffer,
  IN  UINTN       BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints EFI_STATUS as a string. If string is
  not known a hex value will be printed.

Arguments:

  Status     -  EFI_STATUS sturcture to print.

  Buffer     - Buffer to print EFI_STATUS message string into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
;

STATIC
UINTN
VSPrint (
  OUT CHAR8        *StartOfBuffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8  *FormatString,
  IN  VA_LIST       Marker
  )
/*++

Routine Description:

  VSPrint function to process format and place the results in Buffer. Since a 
  VA_LIST is used this rountine allows the nesting of Vararg routines. Thus 
  this is the main print working routine

Arguments:

  StartOfBuffer - String buffer to print the results of the parsing of Format into.

  BufferSize    - Maximum number of characters to put into buffer. Zero means 
                  no limit.

  FormatString  - String format string see file header for more details.

  Marker        - Vararg list consumed by processing Format.

Returns: 

  Number of characters printed.

--*/  
;

STATIC
UINTN
SPrint (
  OUT CHAR8        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8  *Format,
  ...
  )
/*++

Routine Description:

  SPrint function to process format and place the results in Buffer.

Arguments:

  Buffer     - Wide char buffer to print the results of the parsing of Format into.

  BufferSize - Maximum number of characters to put into buffer. Zero means no 
               limit.

  Format     - Format string see file header for more details.

  ...        - Vararg list consumed by processing Format.

Returns: 

  Number of characters printed.

--*/  
;

STATIC
UINTN
ValueToHexStr (
  IN  OUT CHAR8  *Buffer, 
  IN  UINT64      Value, 
  IN  UINTN       Flags, 
  IN  UINTN       Width
  )
/*++

Routine Description:

  VSPrint worker function that prints a Value as a hex number in Buffer

Arguments:

  Buffer - Location to place ascii hex string of Value.

  Value  - Hex value to convert to a string in Buffer.

  Flags  - Flags to use in printing Hex string, see file header for details.

  Width  - Width of hex value.

Returns: 

  Number of characters printed.  

--*/  
;

STATIC
UINTN
ValueToString (
  IN  OUT CHAR8  *Buffer, 
  IN  INT64       Value, 
  IN  UINTN       Flags,
  IN  UINTN       Width
  )
/*++

Routine Description:

  VSPrint worker function that prints a Value as a decimal number in Buffer

Arguments:

  Buffer - Location to place ascii decimal number string of Value.

  Value  - Decimal value to convert to a string in Buffer.

  Flags  - Flags to use in printing decimal string, see file header for details.

  Width  - Width of hex value.

Returns: 

  Number of characters printed.  

--*/  
;


STATIC
UINTN
SPrint (
  OUT CHAR8        *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8  *Format,
  ...
  )
/*++

Routine Description:

  SPrint function to process format and place the results in Buffer.

Arguments:

  Buffer     - Wide char buffer to print the results of the parsing of Format into.

  BufferSize - Maximum number of characters to put into buffer. Zero means no 
               limit.

  Format     - Format string see file header for more details.

  ...        - Vararg list consumed by processing Format.

Returns: 

  Number of characters printed.

--*/  
{
  UINTN   Return;
  VA_LIST Marker;

  VA_START (Marker, Format);
  Return = VSPrint (Buffer, BufferSize, Format, Marker);
  VA_END (Marker);
  
  return Return;
}


STATIC
UINTN
ValueToHexStr (
  IN  OUT CHAR8  *Buffer, 
  IN  UINT64      Value, 
  IN  UINTN       Flags, 
  IN  UINTN       Width
  )
/*++

Routine Description:

  VSPrint worker function that prints a Value as a hex number in Buffer

Arguments:

  Buffer - Location to place ascii hex string of Value.

  Value  - Hex value to convert to a string in Buffer.

  Flags  - Flags to use in printing Hex string, see file header for details.

  Width  - Width of hex value.

Returns: 

  Number of characters printed.  

--*/  
{
  CHAR8  TempBuffer[CHARACTER_NUMBER_FOR_VALUE];
  CHAR8  *TempStr;
  CHAR8  Prefix;
  CHAR8  *BufferPtr;
  UINTN   Count;
  UINTN   Index;

  TempStr   = TempBuffer;
  BufferPtr = Buffer;

  //
  // Count starts at one since we will null terminate. Each iteration of the
  // loop picks off one nibble. Oh yea TempStr ends up backwards
  //
  Count = 0;
  
  if (Width > CHARACTER_NUMBER_FOR_VALUE - 1) {
    Width = CHARACTER_NUMBER_FOR_VALUE - 1;
  }

  do {
    Index = ((UINTN)Value & 0xf);
    *(TempStr++) = mHexStr[Index];
    Value = RShiftU64 (Value, 4);
    Count++;
  } while (Value != 0);

  if (Flags & PREFIX_ZERO) {
    Prefix = '0';
  } else { 
    Prefix = ' ';
  }

  Index = Count;
  if (!(Flags & LEFT_JUSTIFY)) {
    for (; Index < Width; Index++) {
      *(TempStr++) = Prefix;
    }
  }

  //
  // Reverse temp string into Buffer.
  //
  if (Width > 0 && (UINTN) (TempStr - TempBuffer) > Width) {
    TempStr = TempBuffer + Width;
  }
  Index = 0;
  while (TempStr != TempBuffer) {
    *(BufferPtr++) = *(--TempStr);
    Index++;
  }
    
  *BufferPtr = 0;
  return Index;
}


STATIC
UINTN
ValueToString (
  IN  OUT CHAR8  *Buffer, 
  IN  INT64       Value, 
  IN  UINTN       Flags,
  IN  UINTN       Width
  )
/*++

Routine Description:

  VSPrint worker function that prints a Value as a decimal number in Buffer

Arguments:

  Buffer - Location to place ascii decimal number string of Value.

  Value  - Decimal value to convert to a string in Buffer.

  Flags  - Flags to use in printing decimal string, see file header for details.

  Width  - Width of hex value.

Returns: 

  Number of characters printed.  

--*/  
{
  CHAR8    TempBuffer[CHARACTER_NUMBER_FOR_VALUE];
  CHAR8    *TempStr;
  CHAR8    *BufferPtr;
  UINTN     Count;
  UINTN     ValueCharNum;
  UINTN     Remainder;
  CHAR8     Prefix;
  UINTN     Index;
  BOOLEAN   ValueIsNegative;

  TempStr         = TempBuffer;
  BufferPtr       = Buffer;
  Count           = 0;
  ValueCharNum    = 0;
  ValueIsNegative = FALSE;

  if (Width > CHARACTER_NUMBER_FOR_VALUE - 1) {
    Width = CHARACTER_NUMBER_FOR_VALUE - 1;
  }

  if (Value < 0) {
    Value           = -Value;
    ValueIsNegative = TRUE;
  }

  do {
    Value = (UINT64)SctDivU64x32 ((UINT64)Value, 10, &Remainder);
    *(TempStr) = (CHAR8)(Remainder + '0');
    TempStr++;
    ValueCharNum++;
    Count++;
    if ((Flags & COMMA_TYPE) == COMMA_TYPE) {
      if (ValueCharNum % 3 == 0 && Value != 0) {
        *(TempStr++) = ',';
        Count++;
      }
    }
  } while (Value != 0);

  if (ValueIsNegative) {
    *(TempStr)    = '-';
    TempStr++;
    Count++;
  }

  if ((Flags & PREFIX_ZERO) && !ValueIsNegative) {
    Prefix = '0';
  } else { 
    Prefix = ' ';
  }                   

  Index = Count;
  if (!(Flags & LEFT_JUSTIFY)) {
    for (; Index < Width; Index++) {
      *(TempStr) = Prefix;
      TempStr++;
    }
  }

  //
  // Reverse temp string into Buffer.
  //
  if (Width > 0 && (UINTN) (TempStr - TempBuffer) > Width) {
    TempStr = TempBuffer + Width;
  }
  Index = 0;
  while (TempStr != TempBuffer) {
    --TempStr;
    *(BufferPtr) = *(TempStr);
    BufferPtr++;
    Index++;
  }

  *BufferPtr = 0;
  return Index;
}


STATIC
UINTN
VSPrint (
  OUT CHAR8        *StartOfBuffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8  *FormatString,
  IN  VA_LIST       Marker
  )
/*++

Routine Description:

  VSPrint function to process format and place the results in Buffer. Since a 
  VA_LIST is used this rountine allows the nesting of Vararg routines. Thus 
  this is the main print working routine

Arguments:

  StartOfBuffer - String buffer to print the results of the parsing of Format into.

  BufferSize    - Maximum number of characters to put into buffer. Zero means 
                  no limit.

  FormatString  - String format string see file header for more details.

  Marker        - Vararg list consumed by processing Format.

Returns: 

  Number of characters printed.

--*/  
{
  CHAR8    TempBuffer[CHARACTER_NUMBER_FOR_VALUE];
  CHAR8    *Buffer;
  CHAR8     *AsciiStr;
  CHAR8     *HexStr;
  CHAR8    *Format;
  UINTN     Index;
  UINTN     Flags;
  UINTN     Width;
  UINTN     Count;
  UINTN     NumberOfCharacters;
  UINTN     BufferLeft;
  UINT64    Value;
  EFI_GUID  *TmpGUID;

  //
  // Process the format string. Stop if Buffer is over run.
  //

  Buffer = StartOfBuffer;
  Format = (CHAR8 *)FormatString; 
  NumberOfCharacters = BufferSize/sizeof(CHAR8);
  BufferLeft = BufferSize;
  for (Index = 0; (*Format != '\0') && (Index < NumberOfCharacters - 1); Format++) {
    if (*Format != '%') {
      if ((*Format == '\n') && (Index < NumberOfCharacters - 2)) {                  
        //
        // If carage return add line feed
        //
        Buffer[Index++] = '\r';
        BufferLeft -= sizeof(CHAR8);
      }
      Buffer[Index++] = *Format;
      BufferLeft -= sizeof(CHAR8);
    } else {
      
      //
      // Now it's time to parse what follows after %
      //
      Format = GetFlagsAndWidth (Format, &Flags, &Width, &Marker);
      switch (*Format) {
      case 'X':
        Flags |= PREFIX_ZERO;
        Width = sizeof (UINT64) * 2;
        //
        // break skiped on purpose
        //
      case 'x':
        if ((Flags & LONG_TYPE) == LONG_TYPE) {
          Value = VA_ARG (Marker, UINT64);
        } else {
          Value = VA_ARG (Marker, UINTN);
        }

        ValueToHexStr (TempBuffer, Value, Flags, Width);
        HexStr = TempBuffer;

        for ( ;(*HexStr != '\0') && (Index < NumberOfCharacters - 1); HexStr++) {
          Buffer[Index++] = *HexStr;
        }
        break;

      case 'd':
        if ((Flags & LONG_TYPE) == LONG_TYPE) {
          Value = VA_ARG (Marker, UINT64);
        } else {
          Value = (UINTN)VA_ARG (Marker, UINTN);
          Value = (UINT64)(UINT32)Value;
        }

        ValueToString (TempBuffer, Value, Flags, Width);
        HexStr = TempBuffer;                              

        for ( ;(*HexStr != '\0') && (Index < NumberOfCharacters - 1); HexStr++) {
          Buffer[Index++] = *HexStr;
        }
        break;

      case 's':
      case 'S':
        HexStr = (CHAR8 *)VA_ARG (Marker, CHAR8 *);
        if (HexStr == NULL) {
          HexStr = "<null string>";
        }
        for (Count = 0 ;(*HexStr != '\0') && (Index < NumberOfCharacters - 1); HexStr++, Count++) {
          Buffer[Index++] = *HexStr;
        }
        //
        // Add padding if needed
        //
        for (; (Count < Width) && (Index < NumberOfCharacters - 1); Count++) {
          Buffer[Index++] = ' ';
        }

        break;

      case 'a':
        AsciiStr = (CHAR8 *)VA_ARG (Marker, CHAR8 *);
        if (AsciiStr == NULL) {
          AsciiStr = "<null string>";
        }
        for (Count = 0 ;(*AsciiStr != '\0') && (Index < NumberOfCharacters - 1); AsciiStr++, Count++) {
          Buffer[Index++] = (CHAR8)*AsciiStr;
        }
        //
        // Add padding if needed
        //
        for (;(Count < Width) && (Index < NumberOfCharacters - 1); Count++) {
          Buffer[Index++] = ' ';
        }
        break;

      case 'c':
        Buffer[Index++] = (CHAR8)VA_ARG (Marker, UINTN);
        break;

      case 'g':
        TmpGUID = VA_ARG (Marker, EFI_GUID *); 
        if (TmpGUID != NULL) {
          Index += GuidToString (
                    TmpGUID, 
                    &Buffer[Index], 
                    BufferLeft
                    );
        }
        break;

      case 't':
        Index += TimeToString (
                  VA_ARG (Marker, EFI_TIME *), 
                  &Buffer[Index], 
                  BufferLeft
                  );
        break;

      case 'r':
        Index += EfiStatusToString (
                  VA_ARG (Marker, EFI_STATUS), 
                  &Buffer[Index], 
                  BufferLeft
                  );
        break;

      case '%':
        Buffer[Index++] = *Format;
        break;
    
      default:
        //
        // if the type is unknown print it to the screen
        //
        Buffer[Index++] = *Format;
      }
      BufferLeft = BufferSize - Index * sizeof(CHAR8) ;
    } 
  }
  Buffer[Index++] = '\0'; 
   
  return &Buffer[Index] - StartOfBuffer;
}



STATIC
CHAR8 *
GetFlagsAndWidth (
  IN  CHAR8      *Format, 
  OUT UINTN       *Flags, 
  OUT UINTN       *Width,
  IN OUT  VA_LIST *Marker
  )
/*++

Routine Description:

  VSPrint worker function that parses flag and width information from the 
  Format string and returns the next index into the Format string that needs
  to be parsed. See file headed for details of Flag and Width.

Arguments:

  Format - Current location in the VSPrint format string.

  Flags  - Returns flags

  Width  - Returns width of element

  Marker - Vararg list that may be paritally consumed and returned.

Returns: 

  Pointer indexed into the Format string for all the information parsed
  by this routine.

--*/  
{
  UINTN   Count;
  BOOLEAN Done;

  *Flags = 0;
  *Width = 0;
  for (Done = FALSE; !Done; ) {
    Format++;

    switch (*Format) {

    case '-': *Flags |= LEFT_JUSTIFY; break;
    case '+': *Flags |= PREFIX_SIGN;  break;
    case ' ': *Flags |= PREFIX_BLANK; break;
    case ',': *Flags |= COMMA_TYPE;   break;
    case 'L':
    case 'l': *Flags |= LONG_TYPE;    break;

    case '*':
      *Width = VA_ARG (*Marker, UINTN);
      break;

    case '0':
      *Flags |= PREFIX_ZERO;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      Count = 0;
      do {
        Count = (Count * 10) + *Format - '0';
        Format++;
      } while ((*Format >= '0')  &&  (*Format <= '9'));
      Format--;
      *Width = Count;
      break;

    default:
      Done = TRUE;
    }
  }
  return Format;
}

STATIC
UINTN
GuidToString (
  IN  EFI_GUID  *Guid,
  IN  CHAR8    *Buffer,
  IN  UINTN     BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints an EFI_GUID.

Arguments:

  Guid       - Pointer to GUID to print.

  Buffer     - Buffe to print Guid into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
{
  UINTN Size;

  Size = SPrint (
            Buffer,
            BufferSize, 
            STRING_W ("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
            (UINTN)Guid->Data1,                    
            (UINTN)Guid->Data2,
            (UINTN)Guid->Data3,
            (UINTN)Guid->Data4[0],
            (UINTN)Guid->Data4[1],
            (UINTN)Guid->Data4[2],
            (UINTN)Guid->Data4[3],
            (UINTN)Guid->Data4[4],
            (UINTN)Guid->Data4[5],
            (UINTN)Guid->Data4[6],
            (UINTN)Guid->Data4[7]
            );

  //
  // SPrint will null terminate the string. The -1 skips the null
  //
  return Size - 1;
}


STATIC
UINTN
TimeToString (
  IN EFI_TIME   *Time,
  OUT CHAR8    *Buffer,
  IN  UINTN     BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints EFI_TIME.

Arguments:

  Time       - Pointer to EFI_TIME sturcture to print.

  Buffer     - Buffer to print Time into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
{ 
  UINTN Size;

  Size = SPrint (
            Buffer,
            BufferSize, 
            STRING_W ("%02d/%02d/%04d  %02d:%02d"),
            (UINTN)Time->Month,
            (UINTN)Time->Day,
            (UINTN)Time->Year,
            (UINTN)Time->Hour,
            (UINTN)Time->Minute
            );

  //
  // SPrint will null terminate the string. The -1 skips the null
  //
  return Size - 1;
} 

STATIC
UINTN
EfiStatusToString (
  IN EFI_STATUS   Status,
  OUT CHAR8      *Buffer,
  IN  UINTN       BufferSize
  )
/*++

Routine Description:

  VSPrint worker function that prints EFI_STATUS as a string. If string is
  not known a hex value will be printed.

Arguments:

  Status     -  EFI_STATUS sturcture to print.

  Buffer     - Buffer to print EFI_STATUS message string into.
  
  BufferSize - Size of Buffer.

Returns: 

  Number of characters printed.  

--*/  
{
  UINTN   Size;
  CHAR8   *Desc;
  
  Desc = NULL;

  //
  // Can't use global Status String Array as UINTN is not constant for EBC
  //
  if (Status == EFI_SUCCESS) { Desc = "Success"; } else 
  if (Status == EFI_LOAD_ERROR) { Desc = "Load Error"; } else
  if (Status == EFI_INVALID_PARAMETER) { Desc = "Invalid Parameter"; } else
  if (Status == EFI_UNSUPPORTED) { Desc = "Unsupported"; } else
  if (Status == EFI_BAD_BUFFER_SIZE) { Desc = "Bad Buffer Size"; } else
  if (Status == EFI_BUFFER_TOO_SMALL) { Desc = "Buffer Too Small"; } else
  if (Status == EFI_NOT_READY) { Desc = "Not Ready"; } else
  if (Status == EFI_DEVICE_ERROR) { Desc = "Device Error"; } else
  if (Status == EFI_WRITE_PROTECTED) { Desc = "Write Protected"; } else
  if (Status == EFI_OUT_OF_RESOURCES) { Desc = "Out of Resources"; } else
  if (Status == EFI_VOLUME_CORRUPTED) { Desc = "Volume Corrupt"; } else
  if (Status == EFI_VOLUME_FULL) { Desc = "Volume Full"; } else
  if (Status == EFI_NO_MEDIA) { Desc = "No Media"; } else
  if (Status == EFI_MEDIA_CHANGED) { Desc = "Media changed"; } else
  if (Status == EFI_NOT_FOUND) { Desc = "Not Found"; } else
  if (Status == EFI_ACCESS_DENIED) { Desc = "Access Denied"; } else
  if (Status == EFI_NO_RESPONSE) { Desc = "No Response"; } else
  if (Status == EFI_NO_MAPPING) { Desc = "No mapping"; } else
  if (Status == EFI_TIMEOUT) { Desc = "Time out"; } else
  if (Status == EFI_NOT_STARTED) { Desc = "Not started"; } else
  if (Status == EFI_ALREADY_STARTED) { Desc = "Already started"; } else
  if (Status == EFI_ABORTED) { Desc = "Aborted"; } else
  if (Status == EFI_ICMP_ERROR) { Desc = "ICMP Error"; } else
  if (Status == EFI_TFTP_ERROR) { Desc = "TFTP Error"; } else
  if (Status == EFI_PROTOCOL_ERROR) { Desc = "Protocol Error"; } else
  if (Status == EFI_WARN_UNKNOWN_GLYPH) { Desc = "Warning Unknown Glyph"; } else
  if (Status == EFI_WARN_DELETE_FAILURE) { Desc = "Warning Delete Failure"; } else
  if (Status == EFI_WARN_WRITE_FAILURE) { Desc = "Warning Write Failure"; } else
  if (Status == EFI_WARN_BUFFER_TOO_SMALL) { Desc = "Warning Buffer Too Small"; } 
  
  //
  // If we found a match, copy the message to the user's buffer. Otherwise
  // sprint the hex status code to their buffer.
  //
  if (Desc != NULL) {
    Size = SPrint (Buffer, BufferSize, STRING_W ("%a"), Desc);
  } else {
    Size = SPrint (Buffer, BufferSize, STRING_W ("%X"), Status);
  }
  return Size - 1;
}


STATIC
VOID
TestStrCpy (
  IN CHAR8   *Destination,
  IN CHAR8   *Source
  )
/*++

Routine Description:

  Copy the string Source to Destination.

Arguments:

  Destination - Location to copy string
  Source      - String to copy

Returns:

  NONE

--*/  
{
  while (*Source) {
    *(Destination++) = *(Source++);
  }
  *Destination = 0;
}

STATIC
UINTN
TestStrLen (
  IN CHAR8   *String
  )
/*++

Routine Description:

  Return the number of Ascii characters in String. This is not the same as
  the length of the string in bytes.

Arguments:

  String - String to process

Returns:

  Number of Ascii characters in String

--*/  
{
  UINTN Length;
  
  for (Length=0; *String; String++, Length++);
  return Length;
}


STATIC  
VOID
TestStrCat (
  IN CHAR8   *Destination,
  IN CHAR8   *Source
  )
/*++

Routine Description:

  Concatinate Source on the end of Destination

Arguments:

  Destination - String to added to the end of.
  Source      - String to concatinate.

Returns:

  NONE

--*/  
{   
  TestStrCpy (Destination + TestStrLen (Destination), Source);
}



EFI_STATUS
LocalPrintf (
  IN CHAR8     *String
  )
/*++

Routine Description:

  Print text message to COM1 and COM2 synchronously.

Arguments:

  String  - Pointer to text message.

Returns:

--*/  
{
  return DebugWorker(String);
}


VOID 
Printf (
  IN   CHAR8  *Format,
  ...
  )
/*++

Routine Description:

  Print a formatted string to COM1 and COM2 synchronously.

Arguments:

  Format  - Format string.
  ...     - Vararg list consumed by processing Format.
 
Returns:

  NONE

--*/  
{
  VA_LIST Marker;
  CHAR8   Buffer[EFI_MAX_PRINT_BUFFER];

  VA_START (Marker, Format);
  VSPrint (Buffer, EFI_MAX_PRINT_BUFFER, Format, Marker);
  VA_END (Marker);

  LocalPrintf(Buffer);

}


VOID 
RecordAssertion (
  IN   EFI_TEST_ASSERTION    Status,
  IN   EFI_GUID              EventId,
  IN   CHAR8                *Description,
  IN   CHAR8                *Format,
  ...
  )
/*++

Routine Description:

  Print a formatted string specially for checkpoint to COM1 and COM2 synchronously.

Arguments:

  Status           - Checkpoint Status.
  EventId          - Checkpoint related unique GUID
  Description      - Checkpoint concise description
  Format           - Format string
  ...              - Vararg list consumed by processing Format.
  
Returns:

  NONE

--*/  
{
  VA_LIST Marker;
  CHAR8   AssertionType[10];
  CHAR8   Buffer1[EFI_MAX_PRINT_BUFFER];
  CHAR8   Buffer2[EFI_MAX_PRINT_BUFFER];
  CHAR8   Buffer3[EFI_MAX_PRINT_BUFFER];

  switch (Status) {
  case EFI_TEST_ASSERTION_PASSED:
    TestStrCpy (AssertionType, "PASS");
    break;
  default:
    TestStrCpy (AssertionType, "FAILURE");
    break;
  }

  SPrint (Buffer1, EFI_MAX_PRINT_BUFFER, "%s -- %s\n", Description, AssertionType);
  SPrint (Buffer2, EFI_MAX_PRINT_BUFFER, "%g\n", &EventId);

  VA_START (Marker, Format);
  VSPrint (Buffer3, EFI_MAX_PRINT_BUFFER, Format, Marker);
  VA_END (Marker);

  if (TestStrLen (Buffer3) + 5 < EFI_MAX_PRINT_BUFFER ) {
    TestStrCat (Buffer3, "\r\n\r\n");
  }

  LocalPrintf(Buffer1);
  LocalPrintf(Buffer2);
  LocalPrintf(Buffer3);
}
