/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  console.c

Abstract:

  Console operation functions

--*/

#include "SctLibInternal.h"

#if 0
VOID
Output (
    IN CHAR16   *Str
    )
// Write a string to the console at the current cursor location
{
    tST->ConOut->OutputString (tST->ConOut, Str);
}
#endif

STATIC
VOID
ConMoveCursorBackward (
  IN     UINTN                   LineLength,
  IN OUT UINTN                   *Column,
  IN OUT UINTN                   *Row
)
/*++

Routine Description:
  Move the cursor position one character backward.

Arguments:
  LineLength       Length of a line. Get it by calling QueryMode
  Column           Current column of the cursor position
  Row              Current row of the cursor position

Returns:

--*/
{
  //
  // If current column is 0, move to the last column of the previous line,
  // otherwise, just decrement column.
  //
  if (*Column == 0) {
    (*Column) = LineLength - 1;
    if (*Row > 0) {
      (*Row) --;
    }
  } else {
    (*Column) --;
  }
}

STATIC
VOID
ConMoveCursorForward (
  IN     UINTN                   LineLength,
  IN     UINTN                   TotalRow,
  IN OUT UINTN                   *Column,
  IN OUT UINTN                   *Row
)
/*++

Routine Description:
  Move the cursor position one character backward.

Arguments:
  LineLength       Length of a line. Get it by calling QueryMode
  TotalRow         Total row of a screen, get by calling QueryMode
  Column           Current column of the cursor position
  Row              Current row of the cursor position

Returns:

--*/
{
  //
  // If current column is at line end, move to the first column of the nest
  // line, otherwise, just increment column.
  //
  (*Column) ++;
  if (*Column >= LineLength) {
    (*Column) = 0;
    if ((*Row) < TotalRow - 1) {
      (*Row) ++;
    }
  }
}

STATIC
VOID
IInput (
    IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *ConOut,
    IN EFI_SIMPLE_TEXT_IN_PROTOCOL      *ConIn,
    IN CHAR16                           *Prompt OPTIONAL,
    OUT CHAR16                          *InStr,
    IN UINTN                            StrLength
    )
/*++

Routine Description:
  Input a string at the current cursor location, for StrLength

Arguments:
  ConOut           Console output protocol
  ConIn            Console input protocol
  Prompt           Prompt string
  InStr            Buffer to hold the input string
  StrLength        Length of the buffer

Returns:

--*/
{
  BOOLEAN                         Done;
  UINTN                           Column;
  UINTN                           Row;
  UINTN                           StartColumn;
  UINTN                           Update;
  UINTN                           Delete;
  UINTN                           Len;
  UINTN                           StrPos;
  UINTN                           Index;
  UINTN                           LineLength;
  UINTN                           TotalRow;
  UINTN                           SkipLength;
  UINTN                           OutputLength;
  UINTN                           TailRow;
  UINTN                           TailColumn;
  EFI_INPUT_KEY                   Key;
  BOOLEAN                         InsertMode;

  if (Prompt) {
    ConOut->OutputString (ConOut, Prompt);
  }

  //
  // Read a line from the console
  //
  Len = 0;
  StrPos = 0;
  OutputLength = 0;
  Update = 0;
  Delete = 0;
  InsertMode = TRUE;

  //
  // If buffer is not large enough to hold a CHAR16, do nothing.
  //
  if (StrLength < 1) {
    return;
  }

  //
  // Get the screen setting and the current cursor location
  //
  StartColumn = ConOut->Mode->CursorColumn;
  Column = StartColumn;
  Row = ConOut->Mode->CursorRow;
  ConOut->QueryMode (ConOut, ConOut->Mode->Mode, &LineLength, &TotalRow);
  if (LineLength == 0) {
    return;
  }

  SctZeroMem (InStr, StrLength * sizeof(CHAR16));
  Done = FALSE;
  do {
    //
    // Read a key
    //
    SctWaitForSingleEvent(ConIn->WaitForKey, 0);
    ConIn->ReadKeyStroke(ConIn, &Key);

    switch (Key.UnicodeChar) {
    case CHAR_CARRIAGE_RETURN:
      //
      // All done, print a newline at the end of the string
      //
      TailRow = Row + (Len - StrPos + Column) / LineLength;
      TailColumn = (Len - StrPos + Column) % LineLength;
      Done = TRUE;
      break;

    case CHAR_BACKSPACE:
      if (StrPos) {
        //
        // If not move back beyond string beginning, move all characters behind
        // the current position one character forward
        //
        StrPos -= 1;
        Update = StrPos;
        Delete = 1;
        SctCopyMem (InStr+StrPos, InStr+StrPos+1, sizeof(CHAR16) * (Len-StrPos));

        //
        // Adjust the current column and row
        //
        ConMoveCursorBackward (LineLength, &Column, &Row);
      }
      break;

    default:
      if (Key.UnicodeChar >= ' ') {
        //
        // If we are at the buffer's end, drop the key
        //
        if (Len == StrLength-1 && (InsertMode || StrPos == Len)) {
          break;
        }

        //
        // If in insert mode, move all characters behind the current position
        // one character backward to make space for this character. Then store
        // the character.
        //
        if (InsertMode) {
          for (Index=Len; Index > StrPos; Index -= 1) {
            InStr[Index] = InStr[Index-1];
          }
        }

        InStr[StrPos] = Key.UnicodeChar;
        Update = StrPos;

        StrPos += 1;
        OutputLength = 1;
      }
      break;

    case 0:
      switch (Key.ScanCode) {
      case SCAN_DELETE:
        //
        // Move characters behind current position one character forward
        //
        if (Len) {
          Update = StrPos;
          Delete = 1;
          SctCopyMem (InStr+StrPos, InStr+StrPos+1, sizeof(CHAR16) * (Len-StrPos));
        }
        break;

      case SCAN_LEFT:
        //
        // Adjust current cursor position
        //
        if (StrPos) {
          StrPos -= 1;
          ConMoveCursorBackward (LineLength, &Column, &Row);
        }
        break;

      case SCAN_RIGHT:
        //
        // Adjust current cursor position
        //
        if (StrPos < Len) {
          StrPos += 1;
          ConMoveCursorForward (LineLength, TotalRow, &Column, &Row);
        }
        break;

      case SCAN_HOME:
        //
        // Move current cursor position to the beginning of the command line
        //
        Row -= (StrPos + StartColumn) / LineLength;
        Column = StartColumn;
        StrPos = 0;
        break;

      case SCAN_END:
        //
        // Move current cursor position to the end of the command line
        //
        TailRow = Row + (Len - StrPos + Column) / LineLength;
        TailColumn = (Len - StrPos + Column) % LineLength;
        Row = TailRow;
        Column = TailColumn;
        StrPos = Len;
        break;

      case SCAN_ESC:
        //
        // Prepare to clear the current command line
        //
        InStr[0] = 0;
        Update = 0;
        Delete = Len;
        Row -= (StrPos + StartColumn) / LineLength;
        Column = StartColumn;
        OutputLength = 0;
        break;

      case SCAN_INSERT:
        //
        // Toggle the SEnvInsertMode flag
        //
        InsertMode = (BOOLEAN)!InsertMode;
        break;
      }
    }

    if (Done) {
      break;
    }


    //
    // If we need to update the output do so now
    //
    if (Update != -1) {
      SctPrintAt (Column, Row, L"%s%.*s", InStr + Update, Delete, L"");
      Len = SctStrLen (InStr);

      if (Delete) {
        SctSetMem (InStr+Len, Delete * sizeof(CHAR16), 0x00);
      }

      if (StrPos > Len) {
        StrPos = Len;
      }

      Update = (UINTN)-1;

      //
      // After using print to reflect newly updates, if we're not using
      // BACKSPACE and DELETE, we need to move the cursor position forward,
      // so adjust row and column here.
      //
      if (Key.UnicodeChar != CHAR_BACKSPACE &&
        ! (Key.UnicodeChar == 0 && Key.ScanCode == SCAN_DELETE)) {
        //
        // Calulate row and column of the tail of current string
        //
        TailRow = Row + (Len - StrPos + Column + OutputLength) / LineLength;
        TailColumn = (Len - StrPos + Column + OutputLength) % LineLength;

        //
        // If the tail of string reaches screen end, screen rolls up, so if
        // Row does not equal TailRow, Row should be decremented
        //
        // (if we are recalling commands using UPPER and DOWN key, and if the
        // old command is too long to fit the screen, TailColumn must be 79.
        //
        if (TailColumn == 0 && TailRow >= TotalRow && Row != TailRow) {
          Row --;
        }

        //
        // Calculate the cursor position after current operation. If cursor
        // reaches line end, update both row and column, otherwise, only
        // column will be changed.
        //
        if (Column + OutputLength >= LineLength) {
          SkipLength = OutputLength - (LineLength - Column);

          Row += SkipLength / LineLength + 1;
          if (Row > TotalRow - 1) {
            Row = TotalRow - 1;
          }
          Column = SkipLength % LineLength;
        } else {
          Column += OutputLength;
        }
      }
      Delete = 0;
    }

    //
    // Set the cursor position for this key
    //
    ConOut->SetCursorPosition (ConOut, Column, Row);
  } while (!Done);


  //
  // Return the data to the caller
  //
  return;
}

VOID
SctInput (
    IN CHAR16    *Prompt OPTIONAL,
    OUT CHAR16   *InStr,
    IN UINTN     StrLen
    )
// Input a string at the current cursor location, for StrLen
{
    IInput (
        tST->ConOut,
        tST->ConIn,
        Prompt,
        InStr,
        StrLen
        );
}

EFI_STATUS
SctStallForKey (
  IN UINTN             Seconds,
  OUT EFI_INPUT_KEY    *Key
  )
{
  EFI_STATUS      Status;
  EFI_EVENT       TimerEvent;
  EFI_EVENT       WaitList[2];
  UINTN           WaitIndex;
  EFI_INPUT_KEY   TempKey;

  //
  // Create timer event
  //
  Status = tBS->CreateEvent (
                 EFI_EVENT_TIMER,
                 0,
                 (EFI_EVENT_NOTIFY) NULL,
                 NULL,
                 &TimerEvent
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Create event. %a:%d:%r\n", __FILE__, __LINE__, Status));
    return Status;
  }

  //
  // Set up the timer
  //
  Status = tBS->SetTimer (
                 TimerEvent,
                 TimerPeriodic,
                 10000000                   // 1 second
                 );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Set timer. %a:%d:%r\n", __FILE__, __LINE__, Status));
    tBS->CloseEvent (TimerEvent);
    return Status;
  }

  //
  // Set up waiting list
  //
  WaitList[0] = tST->ConIn->WaitForKey;
  WaitList[1] = TimerEvent;

  //
  // Do it until timeout
  //
  while (Seconds != 0) {
    //
    // Wait for timeout or key input
    //
    Status = tBS->WaitForEvent (
                   2,
                   WaitList,
                   &WaitIndex
                   );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "Wait for event. %a:%d:%r\n", __FILE__, __LINE__, Status));
      break;
    }

    //
    // Check the triggered event
    //
    if (WaitIndex == 0) {
      //
      // Key input event is triggered
      //
      if (NULL == Key) {
        Key = &TempKey;
      }
      Key->ScanCode = SCAN_NULL;
      Status = tST->ConIn->ReadKeyStroke (tST->ConIn, Key);
      if (!EFI_ERROR (Status)) {
        break;
      }

      DEBUG ((EFI_D_ERROR, "Read key stroke. %a:%d:%r\n", __FILE__, __LINE__, Status));
    } else {
      //
      // Timer event is triggered
      //
      Seconds --;
    }
  }

  //
  // Close the timer event
  //
  tBS->CloseEvent (TimerEvent);

  //
  // Done
  //
  if (Seconds == 0) {
    return EFI_TIMEOUT;
  } else {
    return EFI_SUCCESS;
  }
}
