/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  VariableENTSTestCase.c

Abstract:

--*/

#include "SctLib.h"
#include "VariableENTSTestCase.h"

//
// RT.GetVariable
//
static CHAR16     *RTGetVariableVariableName;
static EFI_GUID   *RTGetVariableVendorGuid;
static UINT32     *RTGetVariableAttributes;
static UINTN      *RTGetVariableDataSize;
static VOID       *RTGetVariableData;
static EFI_STATUS *RTGetVariableStatus;

ENTS_ARG_FIELD    tRTGetVariableArgField[] = {
  {
    POINTER,
    &RTGetVariableVariableName
  },
  {
    POINTER,
    &RTGetVariableVendorGuid
  },
  {
    POINTER,
    &RTGetVariableAttributes
  },
  {
    POINTER,
    &RTGetVariableDataSize
  },
  {
    POINTER,
    &RTGetVariableData
  },
  {
    POINTER,
    &RTGetVariableStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_GetVariable_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  RT GetVariable Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetVariableStatus = RuntimeService->GetVariable (
                                          RTGetVariableVariableName,
                                          RTGetVariableVendorGuid,
                                          RTGetVariableAttributes,
                                          RTGetVariableDataSize,
                                          RTGetVariableData
                                          );
  return EFI_SUCCESS;
}

//
// RT.GetNextVariableName
//
static UINTN      *RTGetNextVariableNameVariableNameSize;
static CHAR16     *RTGetNextVariableNameVariableName;
static EFI_GUID   *RTGetNextVariableNameVendorGuid;
static EFI_STATUS *RTGetNextVariableNameStatus;

ENTS_ARG_FIELD    tRTGetNextVariableNameArgField[] = {
  {
    POINTER,
    &RTGetNextVariableNameVariableNameSize
  },
  {
    POINTER,
    &RTGetNextVariableNameVariableName
  },
  {
    POINTER,
    &RTGetNextVariableNameVendorGuid
  },
  {
    POINTER,
    &RTGetNextVariableNameStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_GetNextVariableName_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  GetNextVariableName Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTGetNextVariableNameStatus = RuntimeService->GetNextVariableName (
                                                  RTGetNextVariableNameVariableNameSize,
                                                  RTGetNextVariableNameVariableName,
                                                  RTGetNextVariableNameVendorGuid
                                                  );
  return EFI_SUCCESS;
}

//
// RT.SetVariable
//
static CHAR16     *RTSetVariableVariableName;
static EFI_GUID   *RTSetVariableVendorGuid;
static UINT32     RTSetVariableAttributes;
static UINTN      RTSetVariableDataSize;
static VOID       *RTSetVariableData;
static EFI_STATUS *RTSetVariableStatus;

ENTS_ARG_FIELD    tRTSetVariableArgField[] = {
  {
    POINTER,
    &RTSetVariableVariableName
  },
  {
    POINTER,
    &RTSetVariableVendorGuid
  },
  {
    OCTET4,
    &RTSetVariableAttributes
  },
  {
    OCTETN,
    &RTSetVariableDataSize
  },
  {
    POINTER,
    &RTSetVariableData
  },
  {
    POINTER,
    &RTSetVariableStatus
  },
  0
};

EFI_STATUS
EFIAPI
RT_SetVariable_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  SetVariable Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_RUNTIME_SERVICES  *RuntimeService;

  RuntimeService = (EFI_RUNTIME_SERVICES *) ClientInterface;

  *RTSetVariableStatus = RuntimeService->SetVariable (
                                          RTSetVariableVariableName,
                                          RTSetVariableVendorGuid,
                                          RTSetVariableAttributes,
                                          RTSetVariableDataSize,
                                          RTSetVariableData
                                          );
  return EFI_SUCCESS;
}
