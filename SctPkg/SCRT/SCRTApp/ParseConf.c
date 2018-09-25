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

  ParseConf.c

--*/

#include "ParseConf.h"

STATIC
CHAR8 *
EFIAPI
AsciiStrtok(
  IN CHAR8     *s,
  IN CHAR8     *delim
  )
/*++

Routine Description:
  
  Find the next token in a string.
  
Arguments: 
  
  s      - String containing token(s). 
  delim  - Set of delimiter characters. 
  
Returns:

   Return a pointer to the next token found in strToken.

--*/    
{
  CHAR8 *spanp;
  UINTN c, sc;
  CHAR8 *tok;
  static char *last;
  
  if (s == NULL && (s = last) == NULL) {
    return (NULL);
  }       
                
cont:
    
  c = *s++;
  for (spanp = (char *)delim; (sc = *spanp++) != 0;) {
    if (c == sc) {
      goto cont;
    } 
  }
  
  if (c == 0) {
    last = NULL;
    return (NULL);
  }
  tok = s - 1;
  
  for (; ;) {
    c = *s++;
    spanp = (char *)delim;
    do {
      if ((sc = *spanp++) == c) {
        if (c == 0) {
          s = NULL;
        } else {
          s[-1] = 0;
        }
        last = s;
        return (tok);
      }
    } while (sc != 0);
  }
}

STATIC
CHAR8 *
AsciiReadLine (
  IN MEMORY_FILE    *InputFile,
  IN OUT CHAR8      *InputBuffer,
  IN UINTN          MaxLength
  )
/*++

Routine Description:

  This function reads a line, stripping any comments.
  The function reads a string from the input stream argument and stores it in 
  the input string. ReadLine reads characters from the current file position 
  to and including the first newline character, to the end of the stream, or 
  until the number of characters read is equal to MaxLength - 1, whichever 
  comes first.  The newline character, if read, is replaced with a \0. 

Arguments:

  InputFile   -  Memory file image.
  InputBuffer -  Buffer to read into, must be _MAX_PATH size.
  MaxLength   -  The maximum size of the input buffer.

Returns:

   NULL          if error or EOF

--*/
{
  CHAR8 *CharPtr;
  CHAR8 *EndOfLine;
  UINTN CharsToCopy;


  //
  // Check for end of file condition
  //
  if (InputFile->CurrentFilePointer >= InputFile->Eof) {
    return NULL;
  }
  //
  // Find the next newline char
  //
  EndOfLine = SctAsciiStrChr (InputFile->CurrentFilePointer, '\n');

  //
  // Determine the number of characters to copy.
  //
  if (EndOfLine == 0) {
    //
    // If no newline found, copy to the end of the file.
    //
    CharsToCopy = InputFile->Eof - InputFile->CurrentFilePointer;
  } else if (EndOfLine >= InputFile->Eof) {
    //
    // If the newline found was beyond the end of file, copy to the eof.
    //
    CharsToCopy = InputFile->Eof - InputFile->CurrentFilePointer;
  } else {
    //
    // Newline found in the file.
    //
    CharsToCopy = EndOfLine - InputFile->CurrentFilePointer;
  }
  //
  // If the end of line is too big for the current buffer, set it to the max
  // size of the buffer (leaving room for the \0.
  //
  if (CharsToCopy > MaxLength - 1) {
    CharsToCopy = MaxLength - 1;
  }
  //
  // Copy the line.
  //
  SctCopyMem (InputBuffer, InputFile->CurrentFilePointer, CharsToCopy);

  //
  // Add the null termination over the 0x0D
  //
  InputBuffer[CharsToCopy - 1] = '\0';

  //
  // Increment the current file pointer (include the 0x0A)
  //
  InputFile->CurrentFilePointer += CharsToCopy + 1;

  //
  // Strip any comments
  //
  CharPtr = SctAsciiStrStr (InputBuffer, "//");
  if (CharPtr != 0) {
    CharPtr[0] = 0;
  }
  //
  // Return the string
  //
  return InputBuffer;
}


STATIC
BOOLEAN
AsciiFindSection (
  IN MEMORY_FILE    *InputFile,
  IN CHAR8          *Section
  )
/*++

Routine Description:

  This function parses a file from the beginning to find a section.
  The section string may be anywhere within a line.

Arguments:

  InputFile  -   Memory file image.
  Section    -   Section to search for

Returns:

  FALSE if error or EOF
  TRUE if section found

--*/
{
  CHAR8 InputBuffer[_MAX_PATH];
  CHAR8 *CurrentToken;

  //
  // Rewind to beginning of file
  //
  InputFile->CurrentFilePointer = (CHAR8 *)InputFile->FileImage;

  //
  // Read lines until the section is found
  //
  while (InputFile->CurrentFilePointer < InputFile->Eof) {
    //
    // Read a line
    //
    AsciiReadLine (InputFile, InputBuffer, _MAX_PATH);

    //
    // Check if the section is found
    //
    CurrentToken = SctAsciiStrStr (InputBuffer, Section);
    if (CurrentToken != NULL) {
      return TRUE;
    }
  }

  return FALSE;
}



STATIC
EFI_STATUS
AsciiFindToken (
  IN MEMORY_FILE    *InputFile,
  IN CHAR8          *Section,
  IN CHAR8          *Token,
  IN UINTN          Instance,
  OUT CHAR8         *Value
  )
/*++

Routine Description:

  Finds a token value given the section and token to search for.

Arguments:

  InputFile  -  Memory file image.
  Section    -  The section to search for, a string within [].
  Token      -  The token to search for, e.g. EFI_PEIM_RECOVERY, followed by an = in the INF file.
  Instance   -  The instance of the token to search for.  Zero is the first instance.
  Value      -  The string that holds the value following the =.  Must be _MAX_PATH in size.

Returns:

  EFI_SUCCESS             Value found.
  EFI_ABORTED             Format error detected in INF file.
  EFI_INVALID_PARAMETER   Input argument was null.
  EFI_LOAD_ERROR          Error reading from the file.
  EFI_NOT_FOUND           Section/Token/Value not found.

--*/
{
  CHAR8   InputBuffer[_MAX_PATH];
  CHAR8   *CurrentToken;
  BOOLEAN ParseError;
  BOOLEAN ReadError;
  UINTN   Occurrance;

  //
  // Check input parameters
  //
  if (InputFile->FileImage == NULL ||
      InputFile->Eof == NULL ||
      InputFile->CurrentFilePointer == NULL ||
      Section == NULL ||
      SctAsciiStrLen (Section) == 0 ||
      Token == NULL ||
      SctAsciiStrLen (Token) == 0 ||
      Value == NULL
      ) {
    return EFI_INVALID_PARAMETER;
  }
  //
  // Initialize error codes
  //
  ParseError  = FALSE;
  ReadError   = FALSE;

  //
  // Initialize our instance counter for the search token
  //
  Occurrance = 0;

  if (AsciiFindSection (InputFile, Section)) {
    //
    // Found the desired section, find and read the desired token
    //
    do {
      //
      // Read a line from the file
      //
      if (AsciiReadLine (InputFile, InputBuffer, _MAX_PATH) == NULL) {
        //
        // Error reading from input file
        //
        ReadError = TRUE;
        break;
      }
      //
      // Get the first non-whitespace string
      //
      CurrentToken = AsciiStrtok (InputBuffer, " \t\n");
      if (CurrentToken == NULL) {
        //
        // Whitespace line found (or comment) so continue
        //
        CurrentToken = InputBuffer;
        continue;
      }
      //
      // Make sure we have not reached the end of the current section
      //
      if (CurrentToken[0] == '[') {
        break;
      }
      //
      // Compare the current token with the desired token
      //
      if (SctAsciiStrCmp (CurrentToken, Token) == 0) {
        //
        // Found it
        //
        //
        // Check if it is the correct instance
        //
        if (Instance == Occurrance) {
          //
          // Copy the contents following the =
          //
          CurrentToken = AsciiStrtok (NULL, "= \t\n");
          if (CurrentToken == NULL) {
            //
            // Nothing found, parsing error
            //
            ParseError = TRUE;
          } else {
            //
            // Copy the current token to the output value
            //
            SctAsciiStrCpy (Value, CurrentToken);
            return EFI_SUCCESS;
          }
        } else {
          //
          // Increment the occurrance found
          //
          Occurrance++;
        }
      }
    } while (
      !ParseError &&
      !ReadError &&
      InputFile->CurrentFilePointer < InputFile->Eof &&
      CurrentToken[0] != '[' &&
      Occurrance <= Instance
    );
  }
  //
  // Distinguish between read errors and INF file format errors.
  //
  if (ReadError) {
    return EFI_LOAD_ERROR;
  }

  if (ParseError) {
    return EFI_ABORTED;
  }

  return EFI_NOT_FOUND;
}


VOID
ParseConf (
  IN MEMORY_FILE  *InfFile,
  IN CONF_INFO    *FileInfo
  )
/*++

Routine Description:

  This function parses a configuration file and copies info into a CONF_INFO structure.

Arguments:

  InfFile    -     Memory file image.
  FileInfo   -     Information read from INF file.
  
Returns:

  NONE
  
--*/
{
  CHAR8       Value[_MAX_PATH];
  EFI_STATUS  Status;

  //
  // Initialize Configuration info
  //
  SctZeroMem (FileInfo, sizeof (CONF_INFO));

  FileInfo->BitMap.Signature = CONFIGURE_INFO_SIGNATURE;
  //
  // Read the GetVariableString token
  //
  Status = AsciiFindToken (InfFile, VARIABLE_SECTION_STRING, GET_VARIABLE_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.GetVariable = 0x1;
    } 
  }
  
  //
  // Read the SetVariableString token
  //
  Status = AsciiFindToken (InfFile, VARIABLE_SECTION_STRING, SET_VARIABLE_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.SetVariable = 0x1;
    } 
  }


  //
  // Read the GetNextVariableName token
  //
  Status = AsciiFindToken (InfFile, VARIABLE_SECTION_STRING, GET_NEXT_VARIABLE_NAME_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.GetNextVariable = 0x1;
    } 
  }


  //
  // Read the QueryVariableInfo token
  //
  Status = AsciiFindToken (InfFile, VARIABLE_SECTION_STRING, QUERY_VARIABLE_INFO_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.QueryVariable = 0x1;
    } 
  }


  //
  // Read the GetTime token
  //
  Status = AsciiFindToken (InfFile, TIME_SECTION_STRING, GET_TIME_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.GetTime = 0x1;
    } 
  }


  //
  // Read the SetTime token
  //
  Status = AsciiFindToken (InfFile, TIME_SECTION_STRING, SET_TIME_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.SetTime = 0x1;
    } 
  }


  //
  // Read the GetWakeupTime token
  //
  Status = AsciiFindToken (InfFile, TIME_SECTION_STRING, GET_WAKEUP_TIME_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.GetWakeupTime = 0x1;
    } 
  }


  //
  // Read the SetWakeupTime token
  //
  Status = AsciiFindToken (InfFile, TIME_SECTION_STRING, SET_WAKEUP_TIME_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.SetWakeupTime = 0x1;
    } 
  }


  //
  // Read the UpdateCapsule token
  //
  Status = AsciiFindToken (InfFile, CAPSULE_SECTION_STRING, UPDATE_CAPSULE_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.UpdateCapsule  = 0x1;
    } 
  }


  //
  // Read the QueryCapsuleCapabilities token
  //
  Status = AsciiFindToken (InfFile, CAPSULE_SECTION_STRING, QUERY_CAPSULE_CAPABILITIES_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.QueryCapsule = 0x1;
    } 
  }


  //
  // Read the GetNextHighMonotonicCount token
  //
  Status = AsciiFindToken (InfFile, MONOTONICCOUNT_SECTION_STRING, GET_NEXT_HIGH_MONOTONIC_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.GetNextCount = 0x1;
    } 
  }

  //
  // Read the ColdReset token
  //
  Status = AsciiFindToken (InfFile, RESET_SECTION_STRING, COLD_RESET_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.ColdReset = 0x1;
    } 
  }

  //
  // Read the WarmReset token
  //
  Status = AsciiFindToken (InfFile, RESET_SECTION_STRING, WARM_RESET_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.WarmReset = 0x1;
    } 
  }

  //
  // Read the ShutDown token
  //
  Status = AsciiFindToken (InfFile, RESET_SECTION_STRING, SHUT_DOWN_STRING, 0, Value);

  if (Status == EFI_SUCCESS) {
    //
    // Update attribute
    //
    if (SctAsciiStrCmp (Value, TRUE_STRING) == 0) {
      FileInfo->BitMap.ShutDown = 0x1;
    } 
  }

}

