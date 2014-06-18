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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  EntsPrint.c

Abstract:

  Ents String implementations.

--*/
#include "Efi.h"
#include <Library/EntsLib.h>

#define LEFT_JUSTIFY  0x01
#define PREFIX_SIGN   0x02
#define PREFIX_BLANK  0x04
#define COMMA_TYPE    0x08
#define LONG_TYPE     0x10
#define PREFIX_ZERO   0x20

#define PRINT_STRING_LEN      1024
#define PRINT_ITEM_BUFFER_LEN 100

typedef struct {
  BOOLEAN Ascii;
  UINTN   Index;
  union {
    CHAR16  *pw;
    CHAR8   *pc;
  } u;
} POINTER;

typedef struct _pitem {

  POINTER Item;
  CHAR16  *Scratch;
  UINTN   Width;
  UINTN   FieldWidth;
  UINTN   *WidthParse;
  CHAR16  Pad;
  BOOLEAN PadBefore;
  BOOLEAN Comma;
  BOOLEAN Long;
} PRINT_ITEM;

typedef struct _pstate {
  //
  // Input
  //
  POINTER fmt;
  VA_LIST args;

  //
  // Output
  //
  CHAR16  *Buffer;
  CHAR16  *End;
  CHAR16  *Pos;
  UINTN   Len;

  UINTN   Attr;
  UINTN   RestoreAttr;

  UINTN   AttrNorm;
  UINTN   AttrHighlight;
  UINTN   AttrError;

  INTN (*Output) (VOID *context, CHAR16 *str);
  INTN (*SetAttr) (VOID *context, UINTN attr);
  VOID          *Context;

  //
  // Current item being formatted
  //
  struct _pitem *Item;
} PRINT_STATE;

typedef struct {
  BOOLEAN PageBreak;
  BOOLEAN AutoWrap;
  INTN    MaxRow;
  INTN    MaxColumn;
  INTN    InitRow;
  INTN    Row;
  INTN    Column;
  BOOLEAN OmitPrint;
} PRINT_MODE;

static PRINT_MODE mPrintMode;

//
// Internal fucntions
//
STATIC
UINTN
_Print (
  IN PRINT_STATE     *ps
  );

STATIC
UINTN
_IPrint (
  IN UINTN                            Column,
  IN UINTN                            Row,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Out,
  IN CHAR16                           *fmt,
  IN CHAR8                            *fmta,
  IN VA_LIST                          args
  );

STATIC
VOID
PFLUSH (
  IN OUT PRINT_STATE     *ps
  );

STATIC
VOID
FlushWithPageBreak (
  IN OUT PRINT_STATE     *ps
  );

STATIC
VOID
PPUTC (
  IN OUT PRINT_STATE     *ps,
  IN CHAR16              c
  );

STATIC
VOID
PITEM (
  IN OUT PRINT_STATE  *ps
  );

STATIC
CHAR16
PGETC (
  IN POINTER      *p
  );

STATIC
VOID
PSETATTR (
  IN OUT PRINT_STATE   *ps,
  IN UINTN             Attr
  );

static
INTN
_SPrint (
  IN VOID     *Context,
  IN CHAR16   *Buffer
  )
{
  UINTN       len;
  ENTS_POOL_PRINT  *spc;

  spc = Context;
  len = EntsStrLen (Buffer);

  //
  // Is the string is over the max truncate it
  //
  if (spc->len + len > spc->maxlen) {
    len = spc->maxlen - spc->len;
  }
  //
  // Append the new text
  //
  EntsCopyMem (spc->str + spc->len, Buffer, len * sizeof (CHAR16));
  spc->len += len;

  //
  // Null terminate it
  //
  if (spc->len < spc->maxlen) {
    spc->str[spc->len] = 0;
  } else if (spc->maxlen) {
    spc->str[spc->maxlen - 1] = 0;
  }

  return 0;
}

STATIC
INTN
_PoolPrint (
  IN VOID     *Context,
  IN CHAR16   *Buffer
  )
{
  UINTN       newlen;
  ENTS_POOL_PRINT  *spc;

  spc     = Context;
  newlen  = spc->len + EntsStrLen (Buffer) + 1;

  //
  // Is the string is over the max, grow the buffer
  //
  if (newlen > spc->maxlen) {
    //
    // Grow the pool buffer
    //
    newlen += PRINT_STRING_LEN;
    spc->maxlen = newlen;
    spc->str = EntsReallocatePool (
                spc->str,
                spc->len * sizeof (CHAR16),
                spc->maxlen * sizeof (CHAR16)
                );

    if (!spc->str) {
      spc->len    = 0;
      spc->maxlen = 0;
    }
  }
  //
  // Append the new text
  //
  return _SPrint (Context, Buffer);
}

STATIC
VOID
_PoolCatPrint (
  IN CHAR16            *fmt,
  IN VA_LIST           args,
  IN OUT ENTS_POOL_PRINT    *spc,
  IN INTN              (*Output)(VOID *context, CHAR16 *str)
)
{
  PRINT_STATE ps;

  EntsZeroMem (&ps, sizeof (ps));
  ps.Output   = Output;
  ps.Context  = spc;
  ps.fmt.u.pw = fmt;
  ps.args     = args;
  _Print (&ps);
}

UINTN
EntsSPrint (
  OUT CHAR16  *Str,
  IN UINTN    StrSize,
  IN CHAR16   *fmt,
  ...
  )
/*++

Routine Description:

    Prints a formatted unicode string to a buffer

Arguments:

    Str         - Output buffer to print the formatted string into

    StrSize     - Size of Str.  String is truncated to this size.
                  A size of 0 means there is no limit

    fmt         - The format string
    ...         - Variables.

Returns:

    String length returned in buffer

--*/
{
  ENTS_POOL_PRINT  spc;
  VA_LIST     args;

  VA_START (args, fmt);
  spc.str     = Str;
  spc.maxlen  = StrSize / sizeof (CHAR16) - 1;
  spc.len     = 0;

  _PoolCatPrint (fmt, args, &spc, _SPrint);
  return spc.len;
}

UINTN
EntsVSPrint (
  OUT CHAR16  *Str,
  IN UINTN    StrSize,
  IN CHAR16   *fmt,
  IN VA_LIST  vargs
  )
/*++

Routine Description:

    Prints a formatted unicode string to a buffer

Arguments:

    Str         - Output buffer to print the formatted string into
    StrSize     - Size of Str.  String is truncated to this size.
      A size of 0 means there is no limit
    fmt         - The format string
    vargs       - Variable list.

Returns:

    String length returned in buffer

--*/
{
  ENTS_POOL_PRINT  spc;

  spc.str     = Str;
  spc.maxlen  = StrSize / sizeof (CHAR16) - 1;
  spc.len     = 0;

  _PoolCatPrint (fmt, vargs, &spc, _SPrint);
  return spc.len;
}

CHAR16 *
EntsPoolPrint (
  IN CHAR16           *fmt,
  ...
  )
/*++

Routine Description:

    Prints a formatted unicode string to allocated pool.  The caller
    must free the resulting buffer.

Arguments:

    fmt         - The format string
    ...         - Variables.

Returns:

    Allocated buffer with the formatted string printed in it.
    The caller must free the allocated buffer.   The buffer
    allocation is not packed.

--*/
{
  ENTS_POOL_PRINT  spc;
  VA_LIST     args;

  EntsZeroMem (&spc, sizeof (spc));
  VA_START (args, fmt);
  _PoolCatPrint (fmt, args, &spc, _PoolPrint);
  return spc.str;
}

UINTN
EntsPrint (
  IN CHAR16   *fmt,
  ...
  )
/*++

Routine Description:

    Prints a formatted unicode string to the default console

Arguments:

    fmt         - Format string
    ...         - Variables.

Returns:

    Length of string printed to the console

--*/
{
  VA_LIST args;

  VA_START (args, fmt);
  return _IPrint ((UINTN) -1, (UINTN) -1, gntST->ConOut, fmt, NULL, args);
}


UINTN
EntsNoPrint (
  IN CHAR16                         *fmt,
  ...
  )
{
  (VOID) fmt;
  return 0;
}



UINTN
_IPrint (
  IN UINTN                            Column,
  IN UINTN                            Row,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Out,
  IN CHAR16                           *fmt,
  IN CHAR8                            *fmta,
  IN VA_LIST                          args
  )
{
  PRINT_STATE ps;
  UINTN       back;

  ASSERT (NULL != Out);

  EntsZeroMem (&ps, sizeof (ps));
  ps.Context  = Out;
  ps.Output   = (INTN (*) (VOID *, CHAR16 *)) Out->OutputString;
  ps.SetAttr  = (INTN (*) (VOID *, UINTN)) Out->SetAttribute;
  ASSERT (NULL != Out->Mode);
  ps.Attr           = Out->Mode->Attribute;

  back              = (ps.Attr >> 4) & 0xF;
  ps.AttrNorm       = EFI_TEXT_ATTR (EFI_LIGHTGRAY, back);
  ps.AttrHighlight  = EFI_TEXT_ATTR (EFI_WHITE, back);
  ps.AttrError      = EFI_TEXT_ATTR (EFI_YELLOW, back);

  if (fmt) {
    ps.fmt.u.pw = fmt;
  } else {
    ps.fmt.Ascii  = TRUE;
    ps.fmt.u.pc   = fmta;
  }

  ps.args = args;

  if (Column != (UINTN) -1) {
    Out->SetCursorPosition (Out, Column, Row);
  }

  return _Print (&ps);
}

STATIC
VOID
PFLUSH (
  IN OUT PRINT_STATE     *ps
  )
{
  *ps->Pos = 0;
  if (((UINTN) ps->Context == (UINTN) gntST->ConOut) && mPrintMode.PageBreak) {
    FlushWithPageBreak (ps);
  } else {
    ps->Output (ps->Context, ps->Buffer);
  }

  ps->Pos = ps->Buffer;
}

STATIC
VOID
PSETATTR (
  IN OUT PRINT_STATE   *ps,
  IN UINTN             Attr
  )
{
  PFLUSH (ps);

  ps->RestoreAttr = ps->Attr;
  if (ps->SetAttr) {
    ps->SetAttr (ps->Context, Attr);
  }

  ps->Attr = Attr;
}

STATIC
VOID
PPUTC (
  IN OUT PRINT_STATE     *ps,
  IN CHAR16              c
  )
{
  //
  // If Omit print to ConOut, then return.
  //
  if (mPrintMode.OmitPrint && ((UINTN) ps->Context == (UINTN) gntST->ConOut)) {
    return ;
  }
  //
  // if this is a newline and carriage return does not exist,
  // add a carriage return
  //
  if (c == '\n' && ps->Pos > ps->Buffer && (CHAR16) *(ps->Pos - 1) != '\r') {
    PPUTC (ps, '\r');
  }

  if (c == '\n' && ps->Pos == ps->Buffer) {
    PPUTC (ps, '\r');
  }

  *ps->Pos = c;
  ps->Pos += 1;
  ps->Len += 1;

  //
  // if at the end of the buffer, flush it
  //
  if (ps->Pos >= ps->End) {
    PFLUSH (ps);
  }
}

STATIC
CHAR16
PGETC (
  IN POINTER      *p
  )
{
  CHAR16  c;

  c = (CHAR16) (p->Ascii ? p->u.pc[p->Index] : p->u.pw[p->Index]);
  p->Index += 1;

  return c;
}

STATIC
VOID
PITEM (
  IN OUT PRINT_STATE  *ps
  )
{
  UINTN       Len;

  UINTN       i;
  PRINT_ITEM  *Item;
  CHAR16      c;

  //
  // Get the length of the item
  //
  Item              = ps->Item;
  Item->Item.Index  = 0;
  while (Item->Item.Index < Item->FieldWidth) {
    c = PGETC (&Item->Item);
    if (!c) {
      Item->Item.Index -= 1;
      break;
    }
  }

  Len = Item->Item.Index;

  //
  // if there is no item field width, use the items width
  //
  if (Item->FieldWidth == (UINTN) -1) {
    Item->FieldWidth = Len;
  }
  //
  // if item is larger then width, update width
  //
  if (Len > Item->Width) {
    Item->Width = Len;
  }
  //
  // if pad field before, add pad char
  //
  if (Item->PadBefore) {
    for (i = Item->Width; i < Item->FieldWidth; i += 1) {
      PPUTC (ps, ' ');
    }
  }
  //
  // pad item
  //
  for (i = Len; i < Item->Width; i++) {
    PPUTC (ps, Item->Pad);
  }
  //
  // add the item
  //
  Item->Item.Index = 0;
  while (Item->Item.Index < Len) {
    PPUTC (ps, PGETC (&Item->Item));
  }
  //
  // If pad at the end, add pad char
  //
  if (!Item->PadBefore) {
    for (i = Item->Width; i < Item->FieldWidth; i += 1) {
      PPUTC (ps, ' ');
    }
  }
}

STATIC
VOID
EntsValueToString (
  IN CHAR16   *Buffer,
  IN BOOLEAN  Comma,
  IN INT64    v
  )
{
  STATIC CHAR8  ca[] = { 3, 1, 2 };
  CHAR8         str[40];
  CHAR8         *p1;
  CHAR16        *p2;
  UINTN         c;
  UINTN         r;

  if (!v) {
    Buffer[0] = '0';
    Buffer[1] = 0;
    return ;
  }

  p1  = str;
  p2  = Buffer;

  if (v < 0) {
    *(p2++) = '-';
    v       = -v;
  }

  while (v) {
    v       = (INT64) SctDivU64x32 ((UINT64) v, 10, &r);
    *(p1++) = (CHAR8) ((CHAR8) r + '0');
  }

  c = (Comma ? ca[(p1 - str) % 3] : 999) + 1;
  while (p1 != str) {

    c -= 1;
    if (!c) {
      *(p2++) = ',';
      c       = 3;
    }

    *(p2++) = *(--p1);
  }

  *p2 = 0;
}

STATIC
VOID
EntsTimeToString (
  OUT CHAR16      *Buffer,
  IN EFI_TIME     *Time
  )
{
  UINTN   Hour;

  UINTN   Year;
  CHAR16  AmPm;

  AmPm  = 'a';
  Hour  = Time->Hour;
  if (Time->Hour == 0) {
    Hour = 12;
  } else if (Time->Hour >= 12) {
    AmPm = 'p';
    if (Time->Hour >= 13) {
      Hour -= 12;
    }
  }

  Year = Time->Year % 100;

  //
  // bugbug: for now just print it any old way
  //
  EntsSPrint (
    Buffer,
    0,
    L"%02d/%02d/%02d  %02d:%02d%c",
    Time->Month,
    Time->Day,
    Year,
    Hour,
    Time->Minute,
    AmPm
    );
}

STATIC CHAR8  Hex[] = {
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  'A',
  'B',
  'C',
  'D',
  'E',
  'F'
};

STATIC
VOID
EntsValueToHex (
  IN CHAR16   *Buffer,
  IN UINT64   v
  )
{
  CHAR8   str[30];

  CHAR8   *p1;
  CHAR16  *p2;

  if (!v) {
    Buffer[0] = '0';
    Buffer[1] = 0;
    return ;
  }

  p1  = str;
  p2  = Buffer;

  while (v) {
    *(p1++) = Hex[v & 0xf];
    v       = SctRShiftU64 (v, 4);
  }

  while (p1 != str) {
    *(p2++) = *(--p1);
  }

  *p2 = 0;
}

STATIC
VOID
EntsStatusToString (
  OUT CHAR16          *Buffer,
  IN EFI_STATUS       Status
  )
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
{
  CHAR16  *EMsg;

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
    EntsStrCpy (Buffer, EMsg);
  } else {
    EntsSPrint (Buffer, 0, L"%X", Status);
  }
}

STATIC
UINTN
_Print (
  IN PRINT_STATE     *ps
  )
/*++

Routine Description:

    %w.lF   -   w = width
                l = field width
                F = format of arg

  Args F:
    ps      -   Point to PRINT_STATE instance.
    0       -   pad with zeros
    -       -   justify on left (default is on right)
    ,       -   add comma's to field
    *       -   width provided on stack
    n       -   Set output attribute to normal (for this field only)
    h       -   Set output attribute to highlight (for this field only)
    e       -   Set output attribute to error (for this field only)
    l       -   Value is 64 bits

    a       -   ascii string
    s       -   unicode string
    X       -   fixed 8 byte value in hex
    x       -   hex value
    d       -   value as decimal
    c       -   Unicode char
    t       -   EFI time structure
    g       -   Pointer to GUID
    r       -   EFI status code (result code)

    N       -   Set output attribute to normal
    H       -   Set output attribute to highlight
    E       -   Set output attribute to error
    %       -   Print a %

Arguments:

    SystemTable     - The system table

Returns:

    Number of charactors written

--*/
{
  CHAR16      c;
  UINTN       Attr;
  PRINT_ITEM  Item;
  CHAR16      *Buffer;
  EFI_GUID    *TmpGUID;

  //
  // If Omit print to ConOut, then return 0.
  //
  if (mPrintMode.OmitPrint && ((UINTN) ps->Context == (UINTN) gntST->ConOut)) {
    return 0;
  }

  Item.Scratch  = EntsAllocateZeroPool (sizeof (CHAR16) * PRINT_ITEM_BUFFER_LEN);
  Buffer        = EntsAllocateZeroPool (sizeof (CHAR16) * PRINT_STRING_LEN);

  if (!Item.Scratch || !Buffer) {
    return 0;
  }

  ps->Len       = 0;
  ps->Buffer    = Buffer;
  ps->Pos       = Buffer;
  ps->End       = Buffer + PRINT_STRING_LEN - 1;
  ps->Item      = &Item;

  ps->fmt.Index = 0;
  c             = PGETC (&ps->fmt);
  while (c) {

    if (c != '%') {
      PPUTC (ps, c);
      c = PGETC (&ps->fmt);
      continue;
    }
    //
    // setup for new item
    Item.FieldWidth = (UINTN) -1;
    Item.Width      = 0;
    Item.WidthParse = &Item.Width;
    Item.Pad        = ' ';
    Item.PadBefore  = TRUE;
    Item.Comma      = FALSE;
    Item.Long       = FALSE;
    Item.Item.Ascii = FALSE;
    Item.Item.u.pw  = NULL;
    ps->RestoreAttr = 0;
    Attr            = 0;

    c               = PGETC (&ps->fmt);
    while (c) {

      switch (c) {

      case '%':
        //
        // %% -> %
        //
        Item.Item.u.pw    = Item.Scratch;
        Item.Item.u.pw[0] = '%';
        Item.Item.u.pw[1] = 0;
        break;

      case '0':
        Item.Pad = '0';
        break;

      case '-':
        Item.PadBefore = FALSE;
        break;

      case ',':
        Item.Comma = TRUE;
        break;

      case '.':
        Item.WidthParse = &Item.FieldWidth;
        break;

      case '*':
        *Item.WidthParse = VA_ARG (ps->args, UINTN);
        break;

      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        *Item.WidthParse = 0;
        do {
          *Item.WidthParse  = *Item.WidthParse * 10 + c - '0';
          c                 = PGETC (&ps->fmt);
        } while (c >= '0' && c <= '9');
        ps->fmt.Index -= 1;
        break;

      case 'a':
        Item.Item.u.pc  = VA_ARG (ps->args, CHAR8 *);
        Item.Item.Ascii = TRUE;
        if (!Item.Item.u.pc) {
          Item.Item.u.pc = "(null)";
        }
        break;

      case 's':
        Item.Item.u.pw = VA_ARG (ps->args, CHAR16 *);
        if (!Item.Item.u.pw) {
          Item.Item.u.pw = L"(null)";
        }
        break;

      case 'c':
        Item.Item.u.pw    = Item.Scratch;
        Item.Item.u.pw[0] = (CHAR16) VA_ARG (ps->args, UINTN);
        Item.Item.u.pw[1] = 0;
        break;

      case 'l':
        Item.Long = TRUE;
        break;

      case 'X':
        Item.Width  = Item.Long ? 16 : 8;
        Item.Pad    = '0';

      case 'x':
        Item.Item.u.pw = Item.Scratch;
        EntsValueToHex (
          Item.Item.u.pw,
          Item.Long ? VA_ARG (ps->args,
                      UINT64) : VA_ARG (ps->args,
                    UINTN)
          );

        break;

      case 'g':
        TmpGUID = VA_ARG (ps->args, EFI_GUID *);
        if (TmpGUID != NULL) {
          Item.Item.u.pw = Item.Scratch;
          EntsGuidToString (Item.Item.u.pw, TmpGUID);
        }
        break;

      case 'd':
        Item.Item.u.pw = Item.Scratch;
        EntsValueToString (
          Item.Item.u.pw,
          Item.Comma,
          Item.Long ? VA_ARG (ps->args,
                      UINT64) : VA_ARG (ps->args,
                    UINTN)
          );
        break;

      case 't':
        Item.Item.u.pw = Item.Scratch;
        EntsTimeToString (Item.Item.u.pw, VA_ARG (ps->args, EFI_TIME *));
        break;

      case 'r':
        Item.Item.u.pw = Item.Scratch;
        EntsStatusToString (Item.Item.u.pw, VA_ARG (ps->args, EFI_STATUS));
        break;

      case 'n':
        PSETATTR (ps, ps->AttrNorm);
        break;

      case 'h':
        PSETATTR (ps, ps->AttrHighlight);
        break;

      case 'e':
        PSETATTR (ps, ps->AttrError);
        break;

      case 'N':
        Attr = ps->AttrNorm;
        break;

      case 'H':
        Attr = ps->AttrHighlight;
        break;

      case 'E':
        Attr = ps->AttrError;
        break;

      default:
        Item.Item.u.pw    = Item.Scratch;
        Item.Item.u.pw[0] = '?';
        Item.Item.u.pw[1] = 0;
        break;
      }
      //
      // if we have an Item
      //
      if (Item.Item.u.pw) {
        PITEM (ps);
        break;
      }
      //
      // if we have an Attr set
      //
      if (Attr) {
        PSETATTR (ps, Attr);
        ps->RestoreAttr = 0;
        break;
      }

      c = PGETC (&ps->fmt);
    }

    if (ps->RestoreAttr) {
      PSETATTR (ps, ps->RestoreAttr);
    }

    c = PGETC (&ps->fmt);
  }
  //
  // Flush buffer
  //
  PFLUSH (ps);

  EntsFreePool (Item.Scratch);
  EntsFreePool (Buffer);

  return ps->Len;
}

STATIC
BOOLEAN
SetPageBreak (
  IN OUT PRINT_STATE     *ps
  )
{
  EFI_INPUT_KEY Key;
  CHAR16        Str[3];

  ps->Output (ps->Context, L"Press ENTER to continue, 'q' to exit:");

  //
  // Wait for user input
  //
  Str[0]  = ' ';
  Str[1]  = 0;
  Str[2]  = 0;
  for (;;) {
    EntsWaitForSingleEvent (gntST->ConIn->WaitForKey, 0);
    gntST->ConIn->ReadKeyStroke (gntST->ConIn, &Key);

    //
    // handle control keys
    //
    if (Key.UnicodeChar == CHAR_NULL) {
      if (Key.ScanCode == SCAN_ESC) {
        ps->Output (ps->Context, L"\r\n");
        mPrintMode.OmitPrint = TRUE;
        break;
      }

      continue;
    }

    if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
      ps->Output (ps->Context, L"\r\n");
      mPrintMode.Row = mPrintMode.InitRow;
      break;
    }
    //
    // Echo input
    //
    Str[1] = Key.UnicodeChar;
    if (Str[1] == CHAR_BACKSPACE) {
      continue;
    }

    ps->Output (ps->Context, Str);

    if ((Str[1] == L'q') || (Str[1] == L'Q')) {
      mPrintMode.OmitPrint = TRUE;
    } else {
      mPrintMode.OmitPrint = FALSE;
    }

    Str[0] = CHAR_BACKSPACE;
  }

  return mPrintMode.OmitPrint;
}

STATIC
VOID
FlushWithPageBreak (
  IN OUT PRINT_STATE     *ps
  )
{
  CHAR16  *Pos;
  CHAR16  *LineStart;
  CHAR16  LineEndChar;

  Pos       = ps->Buffer;
  LineStart = Pos;
  while ((*Pos != 0) && (Pos < ps->Pos)) {
    if ((*Pos == L'\n') && (*(Pos - 1) == L'\r')) {
      //
      // Output one line
      //
      LineEndChar = *(Pos + 1);
      *(Pos + 1)  = 0;
      ps->Output (ps->Context, LineStart);
      *(Pos + 1) = LineEndChar;
      //
      // restore line end char
      //
      LineStart         = Pos + 1;
      mPrintMode.Column = 0;
      mPrintMode.Row++;
      if (mPrintMode.Row == mPrintMode.MaxRow) {
        if (SetPageBreak (ps)) {
          return ;
        }
      }
    } else {
      if (*Pos == CHAR_BACKSPACE) {
        mPrintMode.Column--;
      } else {
        mPrintMode.Column++;
      }
      //
      // If column is at the end of line, output a new line feed.
      //
      if ((mPrintMode.Column == mPrintMode.MaxColumn) && (*Pos != L'\n') && (*Pos != L'\r')) {

        LineEndChar = *(Pos + 1);
        *(Pos + 1)  = 0;
        ps->Output (ps->Context, LineStart);
        *(Pos + 1) = LineEndChar;
        //
        // restore line end char
        //
        if (mPrintMode.AutoWrap) {
          ps->Output (ps->Context, L"\r\n");
        }

        LineStart         = Pos + 1;
        mPrintMode.Column = 0;
        mPrintMode.Row++;
        if (mPrintMode.Row == mPrintMode.MaxRow) {
          if (SetPageBreak (ps)) {
            return ;
          }
        }
      }
    }

    Pos++;
  }

  if (*LineStart != 0) {
    ps->Output (ps->Context, LineStart);
  }
}

UINTN
EntsAvSPrint (
  OUT CHAR8         *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8   *FormatString,
  IN  VA_LIST       Marker
  )
{
  UINTN   Index;
  CHAR16  UnicodeFormat[320];
  CHAR16  UnicodeResult[320];

  for (Index = 0; Index < 320 && FormatString[Index] != '\0'; Index++) {
    UnicodeFormat[Index] = (CHAR16) FormatString[Index];
  }
  UnicodeFormat[Index]  = L'\0';

  Index                 = EntsVSPrint (UnicodeResult, 320, UnicodeFormat, Marker);

  for (Index = 0; (Index < (BufferSize - 1)) && UnicodeResult[Index] != L'\0'; Index++) {
    Buffer[Index] = (CHAR8) UnicodeResult[Index];
  }

  Buffer[Index] = '\0';

  return Index++;

}

UINTN
EntsASPrint (
  OUT CHAR8         *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8   *Format,
  ...
  )
{
  UINTN   Return;
  VA_LIST Marker;

  VA_START (Marker, Format);
  Return = EntsAvSPrint (Buffer, BufferSize, Format, Marker);
  VA_END (Marker);

  return Return;
}


CHAR16 *
EntsCatPrint (
  IN OUT ENTS_POOL_PRINT     *Str,
  IN CHAR16             *fmt,
  ...
  )
{
  VA_LIST args;

  VA_START (args, fmt);
  _PoolCatPrint (fmt, args, Str, _PoolPrint);
  return Str->str;
}
