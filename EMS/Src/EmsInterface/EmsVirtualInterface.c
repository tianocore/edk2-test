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
  
    EmsVirtualInterface.c
    
Abstract:

    Implementation for virtual interface related TCL commands

--*/

#include <EmsNet.h>
#include "EmsTypes.h"
#include "EmsTclInit.h"
#include "EmsUtilityString.h"
#include "EmsInterface.h"

#define ADAPTER_NAME_TCL_VAR  "EmsAdapterName"
#define ADAPTER_DESC_TCL_VAR  "EmsAdapterDesc"

#define MAX_VIF_NUMBER        20

typedef struct {
  ULONG Context;
} Vif;

Vif   VifTable[MAX_VIF_NUMBER] = {{0}, };

//
// The index of the interface to connect target machine
//
DWORD EmsIfIndex;
INT8  *EmsInterface = NULL;

INT32
TclVifUp (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "Showif" implementation routine  
  VifUp Number Ipaddr [Netmask]

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32   Number;
  //
  // Virtual interface No
  //
  INT8    ErrorBuff[MAX_ERRBUFF_LEN];
  UINT32  Dummy;
  BOOLEAN ConfigMask;
  IPAddr  Addr;
  IPMask  Mask;
  ULONG   Context;
  ULONG   Inst;

  //
  // Check argumems
  //
  if ((Argc < 3) || (Argc > 4)) {
    goto WrongArg;
  };

  if (strlen (Argv[1]) != AsciiStringToUint32 ((INT8 *) Argv[1], &Number)) {
    goto WrongArg;
  }

  if (AsciiStringToIpv4 ((INT8 *) Argv[2], &Dummy) <= 0) {
    goto WrongArg;
  };

  if (Argc == 4) {
    if (AsciiStringToIpv4 ((INT8 *) Argv[3], &Dummy) <= 0) {
      goto WrongArg;
    };
    ConfigMask = TRUE;
  } else {
    ConfigMask = FALSE;
  }

  Addr = inet_addr (Argv[2]);

  if (ConfigMask) {
    Mask = inet_addr (Argv[3]);
  } else {
    Mask = inet_addr ("255.255.255.0");
  }

  AddIPAddress (Addr, Mask, EmsIfIndex, &Context, &Inst);

  VifTable[Number].Context = Context;
  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "VifUp:  VifUp Number Ipaddr [Netmask]");
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclVifDown (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "VifDown" implementation routine  
  VifDown Number 

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT32 Number;
  //
  // Virtual interface No
  //
  INT8  ErrorBuff[MAX_ERRBUFF_LEN];

  //
  // Check argumems
  //
  if (Argc != 2) {
    goto WrongArg;
  };

  if (strlen (Argv[1]) != AsciiStringToUint32 ((INT8 *) Argv[1], &Number)) {
    goto WrongArg;
  }

  if (Number >= MAX_VIF_NUMBER) {
    sprintf (ErrorBuff, "VifDown: The max virtual interface Number is %d", MAX_VIF_NUMBER);
    goto ErrorExit;
  }

  DeleteIPAddress (VifTable[Number].Context);
  VifTable[Number].Context = 0;

  return TCL_OK;

WrongArg:
  sprintf (ErrorBuff, "VifDown:  VifDown Number");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

VOID
VifDownAll(
  VOID
  )
/*++

Routine Description:

  Shutdown all the virtual interface

Arguments:

  None

Returns:

  None

--*/
{
  INT32 Index;
  for(Index = 0; Index < MAX_VIF_NUMBER; Index++)
  {
    if(VifTable[Index].Context != 0)
    {
      DeleteIPAddress (VifTable[Index].Context);
	  VifTable[Index].Context = 0;
    }
  }  
}

INT32
TclShowIf (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "Showif" implementation routine  
  ShowIf
  This command is used to show all the network adapter in system. All the 
  information will be returned in the command's result. In addition, two 
  tcl array variable ADAPTER_NAME_TCL_VAR ADAPTER_DESC_TCL_VAR will be 
  initialized to store these information also.

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8              ErrorBuff[MAX_ERRBUFF_LEN];
  DWORD             Index;

  PIP_ADAPTER_INFO  pInfo;
  PIP_ADAPTER_INFO  pInfoTemp;

  ULONG             ulSize;
  pInfo     = NULL;
  pInfoTemp = NULL;
  ulSize    = 0;

  Tcl_UnsetVar (Interp, ADAPTER_NAME_TCL_VAR, TCL_GLOBAL_ONLY);
  Tcl_UnsetVar (Interp, ADAPTER_DESC_TCL_VAR, TCL_GLOBAL_ONLY);

  GetAdaptersInfo (pInfo, &ulSize);
  pInfoTemp = pInfo = (PIP_ADAPTER_INFO) malloc (ulSize * sizeof (INT8));
  GetAdaptersInfo (pInfo, &ulSize);

  //
  // Show all the network adapter in system.
  //
  while (pInfo) {
    Index = pInfo->Index;
    sprintf (ErrorBuff, "Index: %d\n", Index);
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    Tcl_AppendResult (Interp, "adapter name: ", pInfo->AdapterName, "\n", (INT8 *) NULL);
    Tcl_AppendResult (Interp, "description: ", pInfo->Description, "\n", (INT8 *) NULL);

    sprintf (ErrorBuff, "%s(%d)", ADAPTER_NAME_TCL_VAR, Index);
    Tcl_SetVar (Interp, ErrorBuff, pInfo->AdapterName, TCL_GLOBAL_ONLY);
    sprintf (ErrorBuff, "%s(%d)", ADAPTER_DESC_TCL_VAR, Index);
    Tcl_SetVar (Interp, ErrorBuff, pInfo->Description, TCL_GLOBAL_ONLY);
    pInfo = pInfo->Next;
  }

  free (pInfoTemp);
  return TCL_OK;
}

INT32
TclSetIf (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "Interface " implementation routine  
  Interface ifindex
  This command is used to specify the adapter connected to the target machine. 
  The argument "ifindex" is its index in OS.

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

  if (Argc != 3) {
    sprintf (ErrorBuff, "Interface: Interface ifindex ifname\n");
    goto WrongArg;
  }

  EmsIfIndex = atoi (Argv[1]);

  if (EmsInterface) {
    free (EmsInterface);
  }

  EmsInterface = _strdup (Argv[2]);
  return TCL_OK;

WrongArg:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}

INT32
TclGetMac (
  IN ClientData      clientData,
  IN Tcl_Interp      *Interp,
  IN INT32           Argc,
  IN CONST84 INT8    *Argv[]
  )
/*++

Routine Description:

  TCL command "GetMac" implementation routine  
  GetMac [Ifname]

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter.
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR

--*/
{
  INT8              ErrorBuff[MAX_ERRBUFF_LEN];
  PIP_ADAPTER_INFO  pInfo;
  PIP_ADAPTER_INFO  pInfoTemp;
  ULONG             ulSize;

  pInfo     = NULL;
  pInfoTemp = NULL;
  ulSize    = 0;
  //
  // Check argumems
  //
  if (Argc >= 2) {
    goto WrongArg;
  };

  GetAdaptersInfo (pInfo, &ulSize);
  pInfoTemp = pInfo = (PIP_ADAPTER_INFO) malloc (ulSize * sizeof (INT8));
  GetAdaptersInfo (pInfo, &ulSize);

  //
  // Get Mac address.
  //
  while (pInfo) {
    if (pInfo->Index != EmsIfIndex) {
      pInfo = pInfo->Next;
      continue;
    }

    MacToAsciiString (
      ErrorBuff,
      pInfo->Address
      );
    Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
    free (pInfoTemp);
    return TCL_OK;
  }

  free (pInfoTemp);
  sprintf (ErrorBuff, "GetMac: No such adapter!");
  goto ErrorExit;

WrongArg:
  sprintf (ErrorBuff, "GetMac: GetMac");

ErrorExit:
  Tcl_AppendResult (Interp, ErrorBuff, (INT8 *) NULL);
  return TCL_ERROR;
}
