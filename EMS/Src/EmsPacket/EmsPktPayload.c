/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsPktPayload.c
    
Abstract:

    Implementation for payload related TCL commands

--*/

#include <stdlib.h>
#include <time.h>
#include "EmsTypes.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsPktMain.h"
#include "EmsPktPayload.h"
#include "EmsProtocols.h"
#include "EmsLogUtility.h"
#include "EmsLogCommand.h"

#define ISPRINT(c)  (c >= ' ' && c <= '~')

extern
INT8
DhcpBuildOption (
  INT8 *Type,
  INT8 *Value,
  INT8 **Options
  );

extern
BOOLEAN
UnpackDhcpPayload (
  IN  UINT32       PayloadLen,
  IN  INT8         *PayloadPtr,
  OUT UINT32       *OptionCnt,
  OUT INT8         **OptionList
  );

extern
BOOLEAN
DhcpOptionListInclude (
  UINT32      HeyStackCount,
  UINT8       *HeyStackOptList,
  UINT32      NeedleCount,
  UINT8       *NeedleOptList
  );

STATIC Tcl_CmdProc  TclCreatePayload;
STATIC Tcl_CmdProc  TclConcatPayload;
STATIC Tcl_CmdProc  TclSplitPayload;
STATIC Tcl_CmdProc  TclXorPayload;
STATIC Tcl_CmdProc  TclComparePayload;
STATIC Tcl_CmdProc  TclGetfromPayload;
STATIC Tcl_CmdProc  TclSettoPayload;
STATIC Tcl_CmdProc  TclCreateDhcpOption;
STATIC Tcl_CmdProc  TclOptionOption;
STATIC Tcl_CmdProc  TclDumpPayload;
STATIC Tcl_CmdProc  TclPayloadLen;

STATIC TCL_CMD_TBL  TclCmds[] = {
  {
    "CreatePayload",
    TclCreatePayload
  },
  {
    "ConcatPayload",
    TclConcatPayload
  },
  {
    "SplitPayload",
    TclSplitPayload
  },
  {
    "XorPayload",
    TclXorPayload
  },
  {
    "CompPayload",
    TclComparePayload
  },
  {
    "GetFromPayload",
    TclGetfromPayload
  },
  {
    "SetToPayload",
    TclSettoPayload
  },
  {
    "CreateDhcpOpt",
    TclCreateDhcpOption
  },
  {
    "DhcpOptOpt",
    TclOptionOption
  },
  {
    "DumpPayload",
    TclDumpPayload
  },
  {
    "LenOfPayload",
    TclPayloadLen
  },
  //
  //  {"SetCaseRoot"    , tcl_split_payload},
  //
  {
    NULL,
    NULL
  }
};

STATIC
INT8
GetPatternByName (
  INT8 *Name
  );

#define PAYLOAD_CONSTANT  0
#define PAYLOAD_INCREASE  1
#define PAYLOAD_DECREASE  2
#define PAYLOAD_DATA      3
#define PAYLOAD_STRING    4
#define PAYLOAD_LIST      5

STATIC struct       PAYLOAD_PATTERNS {
  INT8  *Name;
  UINT8 Pattern;
}
Patterns[] = {
  {
    "Const",
    PAYLOAD_CONSTANT
  },
  {
    "Incr",
    PAYLOAD_INCREASE
  },
  {
    "Decr",
    PAYLOAD_DECREASE
  },
  {
    "Data",
    PAYLOAD_DATA
  },
  {
    "String",
    PAYLOAD_STRING
  },
  {
    "List",
    PAYLOAD_LIST
  },
  {
    NULL
  }
};

VOID_P
PayloadTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
{
  UINT32  Index;
  //
  // Create internal TCL commands
  //
  for (Index = 0; TclCmds[Index].Cmd; Index++) {
    Tcl_CreateCommand (
      Interp,
      TclCmds[Index].Cmd,
      TclCmds[Index].Proc,
      (ClientData) NULL,
      (Tcl_CmdDeleteProc *) NULL
      );
  }
  //
  // Link Packet related TCL variables
  //
}

STATIC
INT32
TclCreatePayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CreatePayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32          Index;
  INT8            *Name;
  INT8            Pattern;
  UINT32          Len;
  UINT8           *Data;
  UINT32          Value;
  PACKET_T        *PacketPointer;
  INT8            *TempPointer;
  struct timeval  Time;
  //
  // The time when create the payload. UserStr
  //
  LogCurrentCommand (Argc, Argv);

  if (Argc < 5) {
    Tcl_AppendResult (
      Interp,
      "CreatePayload PayloadName Pattern Len Value ... ",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is packet name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;

  }

  Pattern = GetPatternByName ((INT8 *) Argv[2]);

  if (Pattern < 0) {
    Tcl_AppendResult (
      Interp,
      "Pattern ",
      (INT8 *) Argv[2],
      " is not supported",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (0 >= AsciiStringToUint32 ((INT8 *) Argv[3], &Len)) {
    Tcl_AppendResult (
      Interp,
      "Length ",
      Argv[3],
      " is invalid",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }
  //
  // bugbug
  //  gettimeofday(&time, NULL);
  //
  Data = calloc (sizeof (UINT8), Len);

  switch (Pattern) {
  case PAYLOAD_CONSTANT:
    AsciiStringToUint32 ((INT8 *) Argv[4], &Value);
    for (Index = 0; Index < Len; Index++) {
      Data[Index] = (UINT8) Value;
    }
    break;

  case PAYLOAD_INCREASE:
    AsciiStringToUint32 ((INT8 *) Argv[4], &Value);
    for (Index = 0; Index < Len; Index++) {
      Data[Index] = (UINT8) Value + Index;
    }
    break;

  case PAYLOAD_DECREASE:
    AsciiStringToUint32 ((INT8 *) Argv[4], &Value);
    for (Index = 0; Index < Len; Index++) {
      Data[Index] = (UINT8) Value - Index;
    }
    break;

  case PAYLOAD_DATA:
    for (Index = 0; (Index < Len) && (Index + 4 < (UINT32) Argc); Index++) {
      AsciiStringToUint32 ((INT8 *) Argv[4 + Index], &Value);
      Data[Index] = (UINT8) Value;
    }
    break;

  case PAYLOAD_STRING:
    strncpy ((INT8 *) Data, (INT8 *) Argv[4], Len);
    break;

  case PAYLOAD_LIST:
    TempPointer = (INT8 *)Argv[4];
    for (Index = 0; Index < Len; Index++) {
      while ((*TempPointer)==' ')//Skip the blank       
          TempPointer++;
      TempPointer += AsciiStringToUint32 ( TempPointer, &Value);
      Data[Index] = (UINT8) Value;
    }
    break;

  default:
    break;
  }
  //
  // If a packet named "name" exists ...
  //
  PacketPointer = EmsPacketFindByName (Name);
  if (PacketPointer) {
    EmsPacketRemove (PacketPointer);
    EmsPacketDestroy (PacketPointer);
  }

  PacketPointer = EmsPacketCreate (Name, Data, Len, &Time);
  free(Data);
  EmsPacketAdd (PacketPointer);
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT8
GetPatternByName (
  INT8 *Name
  )
/*++

Routine Description:

  Get pattern by name string.

Arguments:

  Name  - Name string.

Returns:

  Pattent - When found.
  -1      - Not found. 

--*/
{
  INT32 Index;
  for (Index = 0; Patterns[Index].Name; Index++) {
    if (0 == strcmp_i (Name, Patterns[Index].Name)) {
      return Patterns[Index].Pattern;
    }
  }

  return -1;
}

STATIC
INT32
TclConcatPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "ConcatPayload" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32           Index;
  INT8            *Name;
  UINT32          TotalLen;
  UINT32          Offset;
  UINT8           *Data;
  PACKET_T        *Src;
  PACKET_T        *Dst;
  struct timeval  Time;
  //
  // The time when create the payload. UserStr
  //
  LogCurrentCommand (Argc, Argv);

  if (Argc < 2) {
    Tcl_AppendResult (
      Interp,
      "ConcatPayload Dest Src [...] ",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is dest payload name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;

  }
  //
  // Make sure all the source payload exist.
  //
  for (Index = 2; Index < Argc; Index++) {
    Src = EmsPacketFindByName ((INT8 *) Argv[Index]);
    if (NULL == Src) {
      Tcl_AppendResult (
        Interp,
        "ConcatPayload: Payload ",
        Argv[Index],
        " does not exist.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }
  }
  //
  // bugbug
  //  gettimeofday(&time, NULL);
  //
  Dst = EmsPacketFindByName (Name);
  if (NULL == Dst) {
    //
    // If the destination payload does not exit, then create new one.
    //
    Dst = EmsPacketCreate (Name, NULL, 0, &Time);
    EmsPacketAdd (Dst);
  }
  //
  //  total_len = dst->datalen;
  //
  TotalLen = 0;
  for (Index = 2; Index < Argc; Index++) {
    Src = EmsPacketFindByName ((INT8 *) Argv[Index]);
    TotalLen += Src->DataLen;
  }

  Data    = calloc (sizeof (UINT8), TotalLen);
  Offset  = 0;

  //
  //  if (dst->data) {
  //      memcpy(data, dst->data, dst->datalen);
  //  }
  //  offset += dst->datalen;
  //
  for (Index = 2; Index < Argc; Index++) {
    Src = EmsPacketFindByName ((INT8 *) Argv[Index]);
    memcpy (&Data[Offset], Src->Data, Src->DataLen);
    Offset += Src->DataLen;
  }

  if (Dst->Data) {
    free (Dst->Data);
  }

  Dst->Data     = Data;
  Dst->DataLen  = TotalLen;
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

/*++
Routine Description:
    
    CreatePayload PayloadName Pattern Len Value ...
Argumems:
  @clientData IN : private data, if any.
  @interp     IN : TCL intepreter
  @argc       IN : 
  @argv       IN : 
Returns:
  @return      : 
--*/
STATIC
INT32
TclSplitPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SplitPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8            *Name;
  UINT32          Len;
  UINT32          Start;
  UINT32          End;
  UINT8           *Data;
  PACKET_T        *Src;
  PACKET_T        *Dst;
  struct timeval  Time;
  //
  // The time when create the payload. UserStr
  //
  LogCurrentCommand (Argc, Argv);

  if (Argc != 5) {
    Tcl_AppendResult (
      Interp,
      "SplitPayload Dest Src Head Tail",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is dest payload name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[2];
  if (Name[0] == '-') {
    goto ErrorExit;

  }
  //
  // Make sure the source payload exist.
  //
  Src = EmsPacketFindByName ((INT8 *) Argv[2]);
  if (NULL == Src) {
    Tcl_AppendResult (
      Interp,
      "SplitPayload: Payload ",
      Argv[2],
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (0 == strcmp_i ((INT8 *) Argv[3], "Start")) {
    Start = 0;
  } else {
    if (strlen (Argv[3]) != AsciiStringToUint32 ((INT8 *) Argv[3], &Start)) {
      Tcl_AppendResult (
        Interp,
        "SplitPayload: Error in argument 'Start'.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }
  }

  if (0 == strcmp_i ((INT8 *) Argv[4], "End")) {
    End = Src->DataLen - 1;
  } else {
    if (strlen (Argv[4]) != AsciiStringToUint32 ((INT8 *) Argv[4], &End)) {
      Tcl_AppendResult (
        Interp,
        "SplitPayload: Error in argument 'End'.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }
  }

  if (Start > End) {
    Tcl_AppendResult (
      Interp,
      "SplitPayload: End should be larger than Start.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Len = End - Start + 1;
  if (End >= Src->DataLen) {
    Tcl_AppendResult (
      Interp,
      "SplitPayload: End is out of range.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }
  //
  // bugbug
  //  gettimeofday(&time, NULL);
  //
  Name  = (INT8 *) Argv[1];
  Dst   = EmsPacketFindByName (Name);
  if (NULL == Dst) {
    //
    // If the destination payload does not exit, then create new one.
    //
    Dst = EmsPacketCreate (Name, NULL, 0, &Time);
    EmsPacketAdd (Dst);
  }

  Data = calloc (sizeof (UINT8), Len);
  memcpy (Data, &Src->Data[Start], Len);

  if (Dst->Data) {
    free (Dst->Data);
  }

  Dst->Data     = Data;
  Dst->DataLen  = Len;
  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

static
INT32
TclXorPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "XorPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32          Index;
  INT8            *Name;
  UINT8           *Data;
  PACKET_T        *Src1;
  PACKET_T        *Src2;
  PACKET_T        *Dst;
  struct timeval  Time;
  //
  // The time when create the payload. UserStr
  //
  LogCurrentCommand (Argc, Argv);

  if (Argc != 4) {
    Tcl_AppendResult (
      Interp,
      "XorPayload Dest Src1 Src2",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is dest payload name
  //
  for (Index = 0; Index < 4; Index++) {
    Name = (INT8 *) Argv[Index];
    if (Name[0] == '-') {
      goto ErrorExit;
    }
  }
  //
  // Make sure all the source payload exist.
  //
  Src1  = EmsPacketFindByName ((INT8 *) Argv[2]);
  Src2  = EmsPacketFindByName ((INT8 *) Argv[3]);

  if (NULL == Src1) {
    Tcl_AppendResult (
      Interp,
      "XorPayload: Payload ",
      Argv[2],
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (NULL == Src2) {
    Tcl_AppendResult (
      Interp,
      "XorPayload: Payload ",
      Argv[3],
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Src1->DataLen != Src2->DataLen) {
    Tcl_AppendResult (
      Interp,
      "XorPayload: The two Source payloads should have same Length.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }
  //
  // bugbug
  //  gettimeofday(&time, NULL);
  //
  Name  = (INT8 *) Argv[1];
  Dst   = EmsPacketFindByName (Name);
  if (NULL == Dst) {
    //
    // If the destination payload does not exit, then create new one.
    //
    Dst = EmsPacketCreate (Name, NULL, 0, &Time);
    EmsPacketAdd (Dst);
  }

  Data = calloc (sizeof (UINT8), Src1->DataLen);

  for (Index = 0; Index < Src1->DataLen; Index++) {
    Data[Index] = (Src1->Data[Index]) ^ (Src2->Data[Index]);
  }

  if (Dst->Data) {
    free (Dst->Data);
  }

  Dst->Data     = Data;
  Dst->DataLen  = Src1->DataLen;
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclComparePayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CompPayload" implementation routine 

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  UINT32    Index;
  INT8      *Name;
  UINT32    Length;
  PACKET_T  *Payload1;
  PACKET_T  *Payload2;

  LogCurrentCommand (Argc, Argv);

  if ((Argc != 3) && (Argc != 4)) {
    Tcl_AppendResult (
      Interp,
      "CompPayload: CompPayload Payload1 Payload2 [Len]",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first&second argument are payload names
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;
  }
  //
  // Make sure payload1 exists.
  //
  Payload1 = EmsPacketFindByName (Name);
  if (NULL == Payload1) {
    Tcl_AppendResult (
      Interp,
      "CompPayload: Payload ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[2];
  if (Name[0] == '-') {
    goto ErrorExit;
  }
  //
  // Make sure payload2 exists.
  //
  Payload2 = EmsPacketFindByName (Name);
  if (NULL == Payload2) {
    Tcl_AppendResult (
      Interp,
      "CompPayload: Payload ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Argc == 3) {
    if (Payload1->DataLen != Payload2->DataLen) {
      goto different;
    }

    Length = Payload1->DataLen;
  } else {
    if (strlen (Argv[3]) != AsciiStringToUint32 ((INT8 *) Argv[3], &Length)) {
      Tcl_AppendResult (
        Interp,
        "CompPayload: Error in argument 'Len'.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }

    if ((Length > Payload1->DataLen) || (Length > Payload2->DataLen)) {
      Tcl_AppendResult (
        Interp,
        "CompPayload: Len is too large.",
        (INT8 *) NULL
        );
      goto ErrorExit;
    }
  }

  for (Index = 0; Index < Length; Index++) {
    if (Payload1->Data[Index] == Payload2->Data[Index]) {
      continue;
    } else {
      goto different;
    }
  }

  goto same;

different:
  Tcl_AppendResult (
    Interp,
    "-1",
    (INT8 *) NULL
    );
  return TCL_OK;
same:
  Tcl_AppendResult (
    Interp,
    "0",
    (INT8 *) NULL
    );
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclGetfromPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "GetFromPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *Name;
  UINT32    Offset;
  PACKET_T  *Payload;
  INT8      Buff[16];

  LogCurrentCommand (Argc, Argv);

  if (Argc != 3) {
    Tcl_AppendResult (
      Interp,
      "GetFromPayload: GetFromPayload Payload Offset",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is payload name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;
  }
  //
  // Make sure payload1 exists.
  //
  Payload = EmsPacketFindByName (Name);
  if (NULL == Payload) {
    Tcl_AppendResult (
      Interp,
      "GetFromPayload: Payload ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[2]) != AsciiStringToUint32 ((INT8 *) Argv[2], &Offset)) {
    Tcl_AppendResult (
      Interp,
      "GetFromPayload: Error in argument 'Offset'.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Offset > Payload->DataLen) {
    Tcl_AppendResult (
      Interp,
      "GetFromPayload: Offset is too large.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  sprintf (Buff, "%d", Payload->Data[Offset]);
  Tcl_AppendResult (
    Interp,
    Buff,
    (INT8 *) NULL
    );
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclSettoPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "SetToPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *Name;
  UINT32    Offset;
  UINT32    Value;
  PACKET_T  *Payload;
  INT8      Buff[16];

  LogCurrentCommand (Argc, Argv);

  if (Argc != 4) {
    Tcl_AppendResult (
      Interp,
      "SetToPayload: SetToPayload Payload Offset Value",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };

  //
  // The first argument is payload name
  //
  Name = (INT8 *) Argv[1];
  if (Name[0] == '-') {
    goto ErrorExit;
  }
  //
  // Make sure payload1 exists.
  //
  Payload = EmsPacketFindByName (Name);
  if (NULL == Payload) {
    Tcl_AppendResult (
      Interp,
      "SetToPayload: Payload ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[2]) != AsciiStringToUint32 ((INT8 *) Argv[2], &Offset)) {
    Tcl_AppendResult (
      Interp,
      "SetToPayload: Error in argument 'Offset'.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (Offset > Payload->DataLen) {
    Tcl_AppendResult (
      Interp,
      "SetToPayload: Offset is too large.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  if (strlen (Argv[3]) != AsciiStringToUint32 ((INT8 *) Argv[3], &Value)) {
    Tcl_AppendResult (
      Interp,
      "SetToPayload: Error in argument 'Value'.",
      (INT8 *) NULL
      );
    goto ErrorExit;
  }

  Payload->Data[Offset] = (UINT8) Value;
  sprintf (Buff, "%d", Payload->Data[Offset]);
  Tcl_AppendResult (
    Interp,
    Buff,
    (INT8 *) NULL
    );
  return TCL_OK;
ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclCreateDhcpOption (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "CreateDhcpOpt" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8            ErrorBuff[1024];
  INT8            *Name;
  INT8            Len;
  INT8            Index;
  INT8            *Value;
  PACKET_T        *PacketPointer;
  struct timeval  Time;
  Value = NULL;
  //
  // The time when create the payload. UserStr
  //
  LogCurrentCommand (Argc, Argv);
  if (Argc != 4) {
    Tcl_AppendResult (
      Interp,
      "Syntax Error - CreateDhcpOpt PayloadName CodeNum Value\n",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  Name = (INT8 *) Argv[1];
  //
  // Build this dhcp options
  //
  Len = DhcpBuildOption ((INT8 *) Argv[2], (INT8 *) Argv[3], &Value);
  if (Len == 0) {
    Tcl_AppendResult (
      Interp,
      "CreateDhcpOpt: Build option error\n",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }
  //
  // Dump value
  //
  for (Index = 0; Index < Len; Index++) {
    printf ("%x ", (UINT8) Value[Index]);
  }

  printf ("\n");
  //
  // If a packet named "name" exists ...
  //
  PacketPointer = EmsPacketFindByName (Name);
  if (PacketPointer) {
    EmsPacketRemove (PacketPointer);
    EmsPacketDestroy (PacketPointer);
  }

  PacketPointer = EmsPacketCreate (Name, Value, Len, &Time);
  if (!PacketPointer) {
    free (Value);
    Tcl_AppendResult (
      Interp,
      "CreateDhcpOpt: create Packet error\n",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  EmsPacketAdd (PacketPointer);
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;
}

STATIC
INT32
TclOptionOption (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DhcpOptOpt" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  PACKET_T  *HeyStackPayload;
  PACKET_T  *NeedlePayload;
  UINT32    Count1;
  UINT32    Count2;
  INT8      *OptList1;
  INT8      *OptList2;

  LogCurrentCommand (Argc, Argv);

  if (Argc != 3) {
    Tcl_AppendResult (
      Interp,
      "DhcpOptOpt: DhcpOptOpt Heystack Needle",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  };

  //
  // Make sure all the payloads exists.
  //
  HeyStackPayload = EmsPacketFindByName ((INT8 *) Argv[1]);
  NeedlePayload   = EmsPacketFindByName ((INT8 *) Argv[2]);
  if (!HeyStackPayload || !NeedlePayload) {
    Tcl_AppendResult (
      Interp,
      "DhcpOptOpt: One or two of Payload ",
      Argv[1],
      Argv[2],
      " does not exist.",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  if ((FALSE == UnpackDhcpPayload (HeyStackPayload->DataLen, HeyStackPayload->Data, &Count1, &OptList1)) ||
      (FALSE == UnpackDhcpPayload (NeedlePayload->DataLen, NeedlePayload->Data, &Count2, &OptList2))
      ) {
    Tcl_AppendResult (
      Interp,
      "DhcpOptOpt: Invalid DHCP Payload",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  if (TRUE == DhcpOptionListInclude (Count1, OptList1, Count2, OptList2)) {
    Tcl_AppendResult (Interp, "0", (INT8 *) NULL);
  } else {
    Tcl_AppendResult (Interp, "1", (INT8 *) NULL);
  }

  return TCL_OK;
}

STATIC
INT32
TclDumpPayload (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "DumpPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *Name;
  PACKET_T  *PacketPointer;
  INT8      Buff[100];
  INT8      AscBuff[100];
  INT8      Str[100];
  INT8      Ch;
  UINT32    Index;
  UINT32    Line;

  LogCurrentCommand (Argc, Argv);

  if (Argc == 1) {
    Tcl_AppendResult (
      Interp,
      "DumpPacket PacketName",
      (INT8 *) NULL
      );
    goto ErrorExit;
  };
  Name          = (INT8 *) Argv[1];
  PacketPointer = EmsPacketFindByName (Name);
  if (NULL == PacketPointer) {
    Tcl_AppendResult (
      Interp,
      "EMS: DumpPacket: Packet ",
      Name,
      " does not exist.",
      (INT8 *) NULL
      );
    return TCL_OK;
  }
  //
  // Packet name, time, ...
  //
  sprintf (
    Buff,
    "EMS: DumpPacket\nName: %s\n Len: %d",
    PacketPointer->Name,
    PacketPointer->DataLen
    );
  RecordMessage (
    EMS_VERBOSE_LEVEL_QUIET,
    "%a",
    Buff
    );

  for (Line = 0; Line < PacketPointer->DataLen / 16; Line++) {
    Buff[0]     = '\0';
    AscBuff[0]  = '\0';
    for (Index = Line * 16; Index < Line * 16 + 16; Index++) {
      sprintf (Str, "%02x ", PacketPointer->Data[Index]);
      strcat (Buff, Str);
      Ch = ISPRINT (PacketPointer->Data[Index]) ? PacketPointer->Data[Index] : '.';
      sprintf (AscBuff, "%s%c", AscBuff, Ch);
    }

    strcat (Buff, AscBuff);
    RecordMessage (
      EMS_VERBOSE_LEVEL_QUIET,
      "%a",
      Buff
      );
  }

  Buff[0]     = '\0';
  AscBuff[0]  = '\0';
  for (Index = Line * 16; Index < PacketPointer->DataLen; Index++) {
    sprintf (Str, "%02x ", PacketPointer->Data[Index]);
    strcat (Buff, Str);
    Ch = ISPRINT (PacketPointer->Data[Index]) ? PacketPointer->Data[Index] : '.';
    sprintf (AscBuff, "%s%c", AscBuff, Ch);
  }

  for (Index = strlen (Buff); Index < 48; Index++) {
    Buff[Index] = ' ';
  }

  Buff[Index] = '\0';
  strcat (Buff, AscBuff);
  RecordMessage (
    EMS_VERBOSE_LEVEL_QUIET,
    "%a",
    Buff
    );

  return TCL_OK;

ErrorExit:
  return TCL_ERROR;
}

STATIC
INT32
TclPayloadLen (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "LenOfPayload" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8      *Name;
  PACKET_T  *PacketPointer;
  INT8      Buff[100];

  LogCurrentCommand (Argc, Argv);

  if (Argc != 2) {
    Tcl_AppendResult (
      Interp,
      "LenOfPayload : Usage LenOfPayload payload_name",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  };
  Name          = (INT8 *) Argv[1];
  PacketPointer = EmsPacketFindByName (Name);
  if (NULL == PacketPointer) {
    Tcl_AppendResult (
      Interp,
      "LenOfPayload: Payload ",
      Name,
      " does not exist",
      (INT8 *) NULL
      );
    return TCL_ERROR;
  }

  sprintf (Buff, "%d", PacketPointer->DataLen);
  Tcl_AppendResult (
    Interp,
    Buff,
    (INT8 *) NULL
    );
  return TCL_OK;
}
