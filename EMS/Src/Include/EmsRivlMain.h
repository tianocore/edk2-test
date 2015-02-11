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
  
    EmsRivlMain.h
    
Abstract:

    Incude header files for RIVL implementation functions

--*/

#ifndef _EMS_RIVL_H_
#define _EMS_RIVL_H_

#include "EmsMain.h"
#include "EmsTypes.h"
#include "EmsRivlNameScope.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsLogCommand.h"

#ifndef INTSIZE_32
#define INTSIZE_32
#endif

#ifdef INTSIZE_32
#define SZ_INTN sizeof (INT32)
#define SZ_PTR  4
#else
#define SZ_INTN sizeof (INT64)
#define SZ_PTR  8
#endif
//
// Remote Interface valdation language related TCL command
//
extern Tcl_CmdProc  TclTypeDef;       // Typedef
extern Tcl_CmdProc  TclViewType;      // ViewType
extern Tcl_CmdProc  TclVarDeclareInternal;
extern Tcl_CmdProc  TclVarDeclareExternal;
extern Tcl_CmdProc  TclFuncDeclare;   //
extern Tcl_CmdProc  TclDumpVar;       // DumpVar
extern Tcl_CmdProc  TclGetVar;        // GetVar
extern Tcl_CmdProc  TclFuncDef;       // Func
extern Tcl_CmdProc  TclTestAbort;     // Exit
extern Tcl_CmdProc  TclGetAck;        // GetAck
extern Tcl_CmdProc  TclRemoteDelType; // DelType
extern Tcl_CmdProc  TclRemoteDelVar;  // DelVar
extern Tcl_CmdProc  TclSizeof;        // Sizeof
extern Tcl_CmdProc  TclSetVar;        // SetVar
extern Tcl_CmdProc  TclTypeof;        // Typeof
extern Tcl_CmdProc  TclRemoteDelFunc; // DelFunc
extern Tcl_CmdProc  TclPack;          // Pack
extern Tcl_CmdProc  TclDelTclVar;     // DelTclVar
extern Tcl_CmdProc  TclExec;          // Exec
extern Tcl_CmdProc  TclGetFile;       // GetFile
extern Tcl_CmdProc  TclPutFile;       // PutFile
extern Tcl_CmdProc  TclSetTargetBits; // TargetBits
extern Tcl_CmdProc  TclGetTargetBits; // TargetBits
extern Tcl_CmdProc  TclBeginScope;
extern Tcl_CmdProc  TclEndScope;

#define MAX_VARNAME_LEN     64
#define MAX_TYPENAME_LEN    64
#define MAX_VAL_LEN         128

#define MAX_STRING_LEN      2048
#define DEFAULT_ALIGNMENT   8
#define MAX_TCL_VARNAME_LEN 256

#define MAX_FUNTIONNAME_LEN 64
#define MAX_ARG_NUM         32

#define MAX_MESSAGE_LEN     4096

//
// Internal type validate routine
//
typedef
BOOLEAN
VALIDATE_VALUE_T (
  INT8          *Value,   // value to validate
  UINT32        *Num,     // number of array member
  INT8          *ErrBuff, // error message
  INT8          *StripValue
  );

//
// Internal type convert value routine
//
typedef
BOOLEAN
CONVERT_VALUE_T (
  IN     INT8          *Src,
  OUT    INT8          *Dst,
  IN     INT32         Num
  );

//
// type definition of RIVL intertal data type
//
typedef struct _INTERNAL_TYPE {
  INT8              *Name;      // name
  VALIDATE_VALUE_T  *Validate;  // validation routine
  CONVERT_VALUE_T   *Convert;
  UINT32            Size;       // size
} INTERNAL_TYPE;

//
// RIVL structure member
//
typedef struct _RIVL_MEMBER {
  INT8    Name[MAX_VARNAME_LEN];  // name
  INT8    Type[MAX_TYPENAME_LEN]; // type
  BOOLEAN IsArray;                // Is it a array
  BOOLEAN IsPtr;
  UINT32  ArrayNum;               // Array Number, 1 if it is not array
  UINT32  Offset;                 // Offset in structure
} RIVL_MEMBER;

//
// RIVL external type
//
typedef struct _RIVL_TYPE {
  INT8              Name[MAX_TYPENAME_LEN]; // name
  UINT32            Size;                   // size
  UINT32            MemberNum;              // how may members in this structure
  UINT32            TotalMemberNum;         // Total number of members, including sub-structures' members
  RIVL_MEMBER       *Members;               // members
  BOOLEAN           IsUnion;                // is it union definition?
  UINT32            Align;                  // Alignment bytes
  struct _RIVL_TYPE *Next;                  // next
} RIVL_TYPE;

//
// RIVL variable value, only for internal type
//
typedef struct _RIVL_VARIABLE_VALUE {
  INT8          Name[MAX_VARNAME_LEN];  // name
  INTERNAL_TYPE *Type;                  // type
  INT8          *Value;                 // value
} RIVL_VARIABLE_VALUE;

//
// RIVL variable
//
typedef struct _RIVL_VARIABLE {
  INT8                  Name[MAX_VARNAME_LEN];  // name
  BOOLEAN               Internal;               // internal type or user defined type
  INTERNAL_TYPE         *IType;                 // pointer to internal type
  RIVL_TYPE             *EType;                 // pointer to external type
  BOOLEAN               IsArray;                // Is it array
  UINT32                ArrayNum;               // Array Number, 1 if it is not array
  RIVL_VARIABLE_VALUE   *Value;                 // Members' Value list
  INT8                  *InternalValue;         // If it is an internal type of variable
  VOID_P                *Address;               // Address in EAS
  BOOLEAN               IsPtr;
  BOOLEAN               IsRefer;                // If this variable is reference var
  struct _RIVL_VARIABLE *Next;                  // next
  RIVL_SCOPE            *Scope;                 // Name scope
  struct _RIVL_VARIABLE *NextByScope;           // next by scope
} RIVL_VARIABLE;

//
// Definition for RIVL function
//
typedef struct _RIVL_FUNCTION {
  INT8                  Name[MAX_FUNTIONNAME_LEN];  // Function name
  UINT32                Argc;                       // Function argument number
  INT8                  *arg_type[MAX_ARG_NUM];     // Type of argumems
  struct _RIVL_FUNCTION *Next;
} RIVL_FUNCTION;

typedef struct _RIVL_TCL_VARIABLE {
  INT8                      Name[MAX_VARNAME_LEN];
  struct _RIVL_TCL_VARIABLE *Next;
} RIVL_TCL_VARIABLE;

typedef struct _RIVL_TCL_VARIABLES {
  INT8                        Name[MAX_VARNAME_LEN];
  RIVL_TCL_VARIABLE           *Head;
  struct _RIVL_TCL_VARIABLES  *Next;
} RIVL_TCL_VARIABLES;

extern INTERNAL_TYPE  InternalTypes[];
extern RIVL_TYPE      *ExternalTypes;

BOOLEAN
IsInternalType (
  INT8 *Name
  )
/*++

Routine Description:

  Check the variable type is Rivl internal type

Arguments:

  Name  - The type name

Returns:

  TRUE or FALSE

--*/
;

BOOLEAN
IsExternalType (
  INT8 *Name
  )
/*++

Routine Description:

  Check whether the type is an external type

Arguments:

  Name  - The type name

Returns:

  TRUE or FALSE

--*/
;

VOID_P
RivlTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet capture related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
;

#endif
