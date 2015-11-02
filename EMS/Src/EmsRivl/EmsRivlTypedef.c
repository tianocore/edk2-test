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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsRivlTypedef.c
    
Abstract:

    Implementation of RIVL type declaration
    
    This file implement TCL commands for type definition 'Struct' & 'Union'
    They are designed for user to define a type of C-like structures.
    Syntax:
      Union/Struct Struct_name {
          type1    member1
          type2    member2
      }
    Notes:
    Structure cannot be used as its member directly. The following definition
    is forbidden.
      Union  union_name {
          type1    member1
          struct {            // WRONG
            type1  member2
            type2  member3
          }
      }
    
    Correct usage:
     Struct  struct1 {
          type1  member2      // RIGHT         /
          type2  member3                      /
     }                                       /
     Union   union_name {                   /
          type1    member1              \  /
          struct1  member2               \/
     }
    
--*/

#include "stdlib.h"
#include "EmsRivlType.h"
#include "EmsRivlMain.h"
#include "EmsRpcMain.h"

#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))

#define MAX_MEMBER_NUM  100

STATIC RIVL_MEMBER  MemberPairs[MAX_MEMBER_NUM];
UINT32              RivlAlignments = DEFAULT_ALIGNMENT;

STATIC
UINT32
StringToPairs (
  IN  INT8        *Str,
  OUT RIVL_MEMBER *Members
  );

BOOLEAN
RivlBuildType (
  INT8           *Message,
  RIVL_TYPE      *Type
  );

INT32
TclPack (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Typedef" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];

  LogCurrentCommand (Argc, Argv);

  if ((Argc != 2) && (Argc != 1)) {
    sprintf (ErrorBuff, "%s: Syntax error.\n", Argv[0]);
    goto ErrorExit;
  }

  if (Argc == 1) {
    RivlAlignments = DEFAULT_ALIGNMENT;
  } else {
    if (atoi (Argv[1]) == 1) {
      RivlAlignments = 1;
    } else {
      sprintf (ErrorBuff, "%s: Unsupport alignment", Argv[0]);
    }
  }

  return TCL_OK;

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclTypeDef (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Typedef" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          *Name;
  INT8          *MemberDefine;
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  UINT32        MemberNum;
  UINT32        TotlaMemberNum;
  UINT32        TotalSize;
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;
  UINT32        TempNum;
  RIVL_MEMBER   *Members;
  RIVL_TYPE     *NewType;
  UINT32        Index;
  UINT32        Index2;
  BOOLEAN       DefUnion;
  //
  // struct or union ?
  //
  UINT32        Align;
  UINT32        TempSize;
  INT8          Message[MAX_MESSAGE_LEN];
  INT32         Length;
  BOOLEAN       Pass;
  INT8          *Out;
  INT8          *Log;

  LogCurrentCommand (Argc, Argv);

  if (0 == strcmp (Argv[0], "Union")) {
    DefUnion = TRUE;
    //
    // Union
    //
  } else {
    DefUnion = FALSE;
    //
    // Struct
    //
  }
  //
  // Parse argument
  //
  if (Argc != 3) {
    sprintf (ErrorBuff, "%s: Syntax error.\n", Argv[0]);
    goto ErrorExit;
  }

  Name = (INT8 *) Argv[1];
  if (strlen (Name) >= MAX_TYPENAME_LEN) {
    sprintf (ErrorBuff, "%s: Type Name is too long.\n", Argv[0]);
    goto ErrorExit;
  }
  //
  // Check if this type has existed. If yes, give a warning and return
  //
  if ((RivlInternalTypeFindByName (Name)) || (RivlTypeFindByName (Name))) {
    sprintf (ErrorBuff, "%s: Type '%s' redefined.\n", Argv[0], Name);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    return TCL_OK;
  }
  //
  // Split argv[2] into type/member pairs
  //
  MemberDefine  = (INT8 *) Argv[2];
  MemberNum     = StringToPairs (MemberDefine, &MemberPairs[0]);
  if (MemberNum <= 0) {
    sprintf (ErrorBuff, "%s: syntax error.\n", Argv[0]);
    goto ErrorExit;
  }
  //
  // Check if there are duplicate members
  //
  for (Index = 0; Index < MemberNum; Index++) {
    for (Index2 = Index + 1; Index2 < MemberNum; Index2++) {
      if (0 == strcmp (MemberPairs[Index].Name, MemberPairs[Index2].Name)) {
        sprintf (
          ErrorBuff,
          "%s: '%s' is duplicated.\n",
          Argv[0],
          MemberPairs[Index].Name
          );
        goto ErrorExit;
      }
    }
  }
  //
  // Poll the pairs
  // Check the type in the pair, if not exist, give an error and return
  // Calculate the total member num and alignment
  //
  TotlaMemberNum  = 0;
  TotalSize       = 0;
  Align           = 0;

  for (Index = 0; Index < MemberNum; Index++) {
    //
    // Internal type
    //
    IType = RivlInternalTypeFindByName (MemberPairs[Index].Type);
    if (IType) {
      TempNum = MemberPairs[Index].IsArray ? MemberPairs[Index].ArrayNum : 1;
      TotlaMemberNum += TempNum;
      Align = MAX (Align, IType->Size);
      continue;
    }
    //
    // External type
    //
    EType = RivlTypeFindByName (MemberPairs[Index].Type);
    if (EType) {
      TempNum = MemberPairs[Index].IsArray ? MemberPairs[Index].ArrayNum : 1;
      TempNum = (EType->TotalMemberNum) * TempNum;
      TotlaMemberNum += TempNum;
      Align = MAX (Align, EType->Align);
      continue;
    }

    sprintf (
      ErrorBuff,
      "%s: Type '%s' undefined.\n",
      Argv[0],
      MemberPairs[Index].Type
      );
    goto ErrorExit;
  }

  Align     = MIN (Align, RivlAlignments);
  TotalSize = 0;
  //
  // Poll the pairs
  // Check the type in the pair, if not exist, give an error and return
  // Calculate the total size and the members' offset
  //
  // For union, all the offsets should be 0
  //
  for (Index = 0; Index < MemberNum; Index++) {
    //
    //     member_pairs[i].offset = total_size;
    //
    TempSize = 0;

    //
    // Internal type
    //
    IType = RivlInternalTypeFindByName (MemberPairs[Index].Type);
    if (IType) {
      TempNum = MemberPairs[Index].IsArray ? MemberPairs[Index].ArrayNum : 1;
      //
      // temp_size = temp_num * i_type -> size; //2004-4-19 23:26 by Ruth
      //
      TempSize = TempNum * (MemberPairs[Index].IsPtr ? SZ_PTR : (IType->Size));
      if (DefUnion) {
        TotalSize                 = MAX (TotalSize, TempSize);
        MemberPairs[Index].Offset = 0;
      } else {
        if (TotalSize % (IType->Size) == 0) {
          MemberPairs[Index].Offset = TotalSize;
          TotalSize += TempSize;
        } else {
          TotalSize                 = TotalSize + IType->Size - TotalSize % (IType->Size);
          MemberPairs[Index].Offset = TotalSize;
          TotalSize += TempSize;
        }
        //
        //         if (temp_size%align) {
        //           temp_size = temp_size + align - temp_size%align;
        //         }
        //         total_size += temp_size;
        //
      }

      continue;
    }
    //
    // External type
    //
    EType = RivlTypeFindByName (MemberPairs[Index].Type);
    if (EType) {
      TempNum = MemberPairs[Index].IsArray ? MemberPairs[Index].ArrayNum : 1;
      //
      // temp_size = temp_num * (e_type -> size); 2004-4-19 23:28 by Ruth
      //
      TempSize = TempNum * (MemberPairs[Index].IsPtr ? SZ_PTR : (EType->Size));

      if (DefUnion) {
        TotalSize                 = MAX (TotalSize, TempSize);
        MemberPairs[Index].Offset = 0;
      } else {
        if (TotalSize % (EType->Align) == 0) {
          MemberPairs[Index].Offset = TotalSize;
          TotalSize += TempSize;
        } else {
          TotalSize                 = TotalSize + EType->Align - TotalSize % (EType->Align);
          MemberPairs[Index].Offset = TotalSize;
          TotalSize += TempSize;
        }
        //
        //         if (temp_size%align) {
        //           temp_size = temp_size + align - temp_size%align;
        //         }
        //         total_size += temp_size;
        //
      }

      continue;
    }

    sprintf (
      ErrorBuff,
      "%s: Type '%s' undefined.\n",
      Argv[0],
      MemberPairs[Index].Type
      );
    goto ErrorExit;
  }

  NewType = (RIVL_TYPE *) malloc (sizeof (RIVL_TYPE));
  if (NULL == NewType) {
    sprintf (
      ErrorBuff,
      "%s: Alloc memory fail. \n",
      Argv[0]
      );
    goto ErrorExit;
  }

  Members = (RIVL_MEMBER *) malloc (sizeof (RIVL_MEMBER) * MemberNum);
  if (NULL == Members) {
    sprintf (ErrorBuff, "%s: Alloc memory fail. \n", Argv[0]);
    goto ErrorExit;
  }

  memcpy (Members, &MemberPairs[0], sizeof (RIVL_MEMBER) * MemberNum);

  strcpy (NewType->Name, Name);
  NewType->MemberNum      = MemberNum;
  NewType->TotalMemberNum = TotlaMemberNum;
  NewType->Members        = Members;
  NewType->IsUnion        = DefUnion;
  Align                   = MIN (Align, RivlAlignments);
  NewType->Align          = Align;
  if (TotalSize % Align) {
    NewType->Size = TotalSize - TotalSize % Align + Align;
  } else {
    NewType->Size = TotalSize;
  }

  NewType->Next = NULL;

  RivlTypeAdd (NewType);

  Tcl_CreateCommand (
    TestCaseInterp,
    Name,
    TclVarDeclareExternal,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );

  //
  // 1). Build message  2). sent Out 3). recv response
  //
  if (FALSE == RivlBuildType (Message, NewType)) {
    sprintf (
      ErrorBuff,
      "Something ErrorExit!"
      );
    goto ErrorExit;
  }

  Length = strlen (Message);

  RpcSendMessage (Length, Message);
  Message[0]  = '\0';

  Length      = RpcRecvMessage (-1, MAX_MESSAGE_LEN, Message);

  if ((FALSE == ParseAckMessage (Length, Message, &Pass, &Out, &Log)) || (FALSE == Pass)) {
    sprintf (
      ErrorBuff,
      "EAS: CRTTYPE %s failed!",
      Name
      );
    goto ErrorExit;
  }

  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

UINT32
StringToPairs (
  IN  INT8        *Str,
  OUT RIVL_MEMBER *Members
  )
/*++

Routine Description:

  Make the type and name to be pairs

Arguments:

  Str     - The string to be processed
  Members - Return the pairs

Returns:

  The number of pairs

--*/
{
  INT8    *Ptr;
  INT8    *TempPtr;
  INT8    *TempPtr1;
  UINT32  Len;
  UINT32  Len1;
  UINT32  Number;
  UINT32  ArrayNumber;

  Number  = 0;
  Ptr     = Str;
  while (*Ptr) {
    //
    // Skip space
    //
    while (*Ptr && ((*Ptr == ';') || (*Ptr == '\t') || (*Ptr == ' ') || (*Ptr == 0x0a) || (*Ptr == 0x0d))) {
      Ptr++;
    }

    if (*Ptr == '\0') {
      return Number;

    }
    //
    // Get a word as type
    //
    TempPtr = Ptr;
    Len     = 0;
    while (*Ptr && (*Ptr != ';') && (*Ptr != ' ') && (*Ptr != 0x0a) && (*Ptr != 0x0d)) {
      Ptr++;
      Len++;
    }

    if (*Ptr == ';') {
      return 0;
      //
      // Type should not be terminated with ';'
      //
    }

    strncpy (Members[Number].Type, TempPtr, Len);
    Members[Number].Type[Len] = '\0';

    //
    // Skip space
    //
    while (*Ptr && ((*Ptr == '\t') || (*Ptr == ' ') || (*Ptr == 0x0a) || (*Ptr == 0x0d))) {
      Ptr++;
    }

    if (*Ptr == '\0') {
      return 0;
      //
      // No variable 's name
      //
    }
    //
    // Get a word as type
    //
    TempPtr = Ptr;
    Len     = 0;
    while (*Ptr && (*Ptr != ';') && (*Ptr != ' ') && (*Ptr != 0x0a) && (*Ptr != 0x0d)) {
      Ptr++;
      Len++;
    }

    if (*(Ptr - 1) == ')') {
      //
      // Maybe it defines a Array
      //
      Len1 = 0;
      for (TempPtr1 = Ptr; (*TempPtr1 != '(') && (TempPtr1 != TempPtr); TempPtr1--) {
        Len1++;
        Len--;
      }

      if (0 == Len) {
        return 0;
        //
        // No '(' found
        //
      }
      //
      //      len --;
      //
      if ((Len1 - 2) != AsciiStringToUint32 (TempPtr1 + 1, &ArrayNumber)) {
        return 0;
        //
        // Error in Array label
        //
      }

      Members[Number].IsArray   = TRUE;
      Members[Number].ArrayNum  = ArrayNumber;
    } else {
      Members[Number].IsArray   = FALSE;
      Members[Number].ArrayNum  = 1;
    }

    if (Members[Number].Name[0] == '*') {
      Members[Number].IsPtr = TRUE;
      strncpy (Members[Number].Name, TempPtr + 1, Len - 1);
      Members[Number].Name[Len - 1] = '\0';
    } else {
      strncpy (Members[Number].Name, TempPtr, Len);
      Members[Number].Name[Len] = '\0';
    }

    Number++;
  }

  return Number;
}

INT32
TclViewType (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "ViewType" implementation routine

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8          *Name;
  INT8          ErrorBuff[MAX_ERRBUFF_LEN];
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;
  UINT32        Index;

  LogCurrentCommand (Argc, Argv);

  //
  // Parse argument
  //
  if (Argc != 2) {
    sprintf (ErrorBuff, "ViewType: ViewType typename");
  }

  Name = (INT8 *) Argv[1];

  //
  // Internal type
  //
  IType = RivlInternalTypeFindByName (Name);
  if (IType) {
    sprintf (ErrorBuff, "%s is an Internal Data Type\n", Name);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Size is %d!", IType->Size);
    goto End;
  }
  //
  // External type
  //
  EType = RivlTypeFindByName (Name);
  if (EType) {
    sprintf (ErrorBuff, "NAME               :  %s\n", Name);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Total Size         :  %d\n", EType->Size);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Member Number      :  %d\n", EType->MemberNum);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Total Member Number:  %d\n", EType->TotalMemberNum);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Memory Size        :  %d\n", EType->Size);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    sprintf (ErrorBuff, "Members\n");
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);

    for (Index = 0; Index < EType->MemberNum; Index++) {
      sprintf (
        ErrorBuff,
        "Name:\t%s\ttype:\t%s\tArray?:\t%s\tItems:%d\tOffset:%d\n",
        EType->Members[Index].Name,
        EType->Members[Index].Type,
        EType->Members[Index].IsArray ? "YES" : "NO",
        EType->Members[Index].ArrayNum,
        EType->Members[Index].Offset
        );
      Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    }

    return TCL_OK;
  }

  goto ErrorExit;
End:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_OK;
ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

BOOLEAN
RivlBuildType (
  INT8           *Message,
  RIVL_TYPE      *Type
  )
/*++

Routine Description:

  Build a rpc message for create type

Arguments:

  Message - The message to be built
  Type    - Return the new type

Returns:

  TRUE

--*/
{
  RIVL_MEMBER   *member;
  INTERNAL_TYPE *IType;
  RIVL_TYPE     *EType;
  INT8          TempBuff[8];
  UINT32        Index;

  //
  // COMMANDNAME typename total_size member_number [name type size offset] 
  //
  sprintf (Message, "RIVL_DEFTYPE ");
  strcat (Message, Type->Name);
  strcat (Message, " ");
  memset (TempBuff, 0, 8);
  sprintf (TempBuff, "%d", Type->Size);
  strcat (Message, TempBuff);
  strcat (Message, " ");
  memset (TempBuff, 0, 8);
  sprintf (TempBuff, "%d", Type->MemberNum);
  strcat (Message, TempBuff);
  strcat (Message, " ");

  for (Index = 0; Index < Type->MemberNum; Index++) {
    member = Type->Members + Index;
    strcat (Message, member->Name);
    strcat (Message, " ");
    strcat (Message, member->Type);
    strcat (Message, " ");
    memset (TempBuff, 0, 8);
    IType = RivlInternalTypeFindByName (member->Type);
    if (IType) {
      sprintf (TempBuff, "%d", (IType->Size) * (member->ArrayNum));
      strcat (Message, TempBuff);
    } else {
      EType = RivlTypeFindByName (member->Type);
      if (EType) {
        sprintf (TempBuff, "%d", (EType->Size) * (member->ArrayNum));
        strcat (Message, TempBuff);
      }
    }

    strcat (Message, " ");
    memset (TempBuff, 0, 8);
    sprintf (TempBuff, "%d ", member->Offset);
    strcat (Message, TempBuff);
    strcat (Message, " ");
  }

  return TRUE;
}
