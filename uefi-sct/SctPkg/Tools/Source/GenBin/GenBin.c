/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010 Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2018 ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++


Module Name:

  GenBin.c

Abstract:

  Generate a binary file.

--*/

//
// Includes
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//
// Definitions
//

#define MAX_LINE_LENGTH           2048
#define MAX_BUFFER_SIZE           2048

//
// Internal functions declaration
//

void
PrintUsage (
  void
  );

char *
Trim (
  char        *String
  );

int
GetLine (
  FILE        *Profile,
  char        *String,
  int         *LineNo
  );

int
WriteBlock (
  FILE        *BinFile,
  long        Start,
  long        End,
  void        *Buffer,
  int         BufferSize
  );

int
GenBin (
  FILE        *Profile,
  FILE        *BinFile
  );


//
// External functions implementation
//

int
main (
  int         Argc,
  char        **Argv
  )
{
  int     Result;
  FILE    *Profile;
  FILE    *BinFile;

  //
  // Check parameters
  //
  if (Argc != 3) {
    PrintUsage ();
    return -1;
  }

  //
  // Open the profile
  //
  Profile = fopen (Argv[1], "r");
  if (Profile == NULL) {
    printf ("Error: Cannot open the profile\n");
    return -1;
  }

  //
  // Open the binary file
  //
  BinFile = fopen (Argv[2], "wb");
  if (BinFile == NULL) {
    printf ("Error: Cannot create the binary file\n");
    fclose (Profile);
    return -1;
  }

  //
  // Generate the binary file
  //
  Result = GenBin (Profile, BinFile);
  if (Result != 0) {
    printf ("Error: Cannot generate the binary file\n");
    fclose (Profile);
    fclose (BinFile);
    return -1;
  }

  //
  // Close the profile and binary file
  //
  fclose (Profile);
  fclose (BinFile);

  //
  // Done
  //
  return 0;
}

//
// Internal functions implementation
//

void
PrintUsage (
  void
  )
{
  printf (
    "Generate a binary file. Version 0.1\n"
    "\n"
    "Usage: GenBin <Profile> <Binary File>\n"
    "\n"
    );
}


char *
Trim (
  char        *String
  )
{
  int   Length;
  char  *end;

  Length = strlen (String);

  if (!Length) {
    return String;
  }

  end = String + Length - 1;

  //
  // Remove the space characters from the end of this string
  //
  while (end >= String && isspace (*end)) {
    end--;
  }

  *(end + 1) = '\0';

  //
  // Remove the space characters from the beginning of this string
  //
  while (*String && isspace (*String)) {
    String++;
  }

  //
  // Done
  //
  return String;
}


int
GetLine (
  FILE        *Profile,
  char        *String,
  int         *LineNo
  )
{
  char    *Result;

  //
  // While get a useful line
  //
  for ( ; ; ) {
    //
    // Get a string from the profile
    //
    Result = fgets (String, MAX_LINE_LENGTH, Profile);
    if (Result == NULL) {
      return -1;
    }

    (*LineNo)++;

    //
    // Remove the beginning and ending space characters
    //
    String = Trim (Result);

    //
    // Skip the empty line and comment line
    //
    if ((String[0] == '\0') ||
        (String[0] == '#' )) {
      continue;
    }
  }

  //
  // Done
  //
  return 0;
}


int
WriteBlock (
  FILE        *BinFile,
  long        Start,
  long        End,
  void        *Buffer,
  int         BufferSize
  )
{
  int   Result;
  long  Size;

  //
  // Move the file pointer to the start position
  //
  Result = fseek (BinFile, Start, SEEK_SET);
  if (Result != 0) {
    return -1;
  }

  //
  // Write the buffer one by one
  //
  Size = End - Start + 1;
  while (Size > 0) {
    if (Size < BufferSize) {
      Result = fwrite (Buffer, 1, Size, BinFile);
    }
    else {
      Result = fwrite (Buffer, 1, BufferSize, BinFile);
    }

    if (Result == 0) {
      return -1;
    }

    Size -= Result;
  }

  //
  // Done
  //
  return 0;
}


int
GenBin (
  FILE        *Profile,
  FILE        *BinFile
  )
{
  int   Result;
  int   LineNo;
  long  Start;
  long  End;
  char  String[MAX_LINE_LENGTH];
  char  *NumPtr;
  char  *EndPtr;
  char  Buffer[MAX_BUFFER_SIZE];
  int   BufferSize;

  LineNo = 0;

  //
  // While it is not end of file
  //
  for ( ; ; ) {
    //
    // Get a line
    //
    Result = GetLine (Profile, String, &LineNo);
    if (Result != 0) {
      break;
    }

    //
    // Get the start address and end address
    //
    NumPtr = String;
    Start = strtol (NumPtr, &EndPtr, 16);
    if ((EndPtr == NumPtr) || (EndPtr == NULL)) {
      printf ("Error: Invalid format (Line %d)\n", LineNo);
      return -1;
    }

    NumPtr = EndPtr;
    End = strtol (NumPtr, &EndPtr, 16);
    if ((EndPtr == NumPtr) || (EndPtr == NULL)) {
      printf ("Error: Invalid format (Line %d)\n", LineNo);
      return -1;
    }

    //
    // Get the data buffer
    //
    BufferSize = 0;

    while (BufferSize < MAX_BUFFER_SIZE) {
      NumPtr = EndPtr;
      Buffer[BufferSize] = (char) strtol (NumPtr, &EndPtr, 16);
      if ((EndPtr == NumPtr) || (EndPtr == NULL)) {
        break;
      }

      BufferSize++;
    }

    //
    // Buffer size cannot be zero
    //
    if (BufferSize == 0) {
      printf ("Error: Invalid format (Line %d)\n", LineNo);
      return -1;
    }

    //
    // Write this buffer
    //
    Result = WriteBlock (BinFile, Start, End, Buffer, BufferSize);
    if (Result != 0) {
      printf ("Error: Cannot write in format (Line %d)\n", LineNo);
      return -1;
    }
  }

  //
  // Done
  //
  return 0;
}
