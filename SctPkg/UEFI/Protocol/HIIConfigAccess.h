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

  HIIConfigAccess.h

Abstract:

  HII Configuration Access Protocol from the UEFI 2.1 specification.

--*/

#ifndef _HII_CONFIG_ACCESS_PROTOCOL_H_
#define _HII_CONFIG_ACCESS_PROTOCOL_H_

//
// Global ID for the HII Configuration Access Protocol
//
#define EFI_HII_CONFIG_ACCESS_PROTOCOL_GUID \
  {0x330d4706, 0xf2a0, 0x4e4f, {0xa3, 0x69, 0xb6, 0x6f, 0xa8, 0xd5, 0x43, 0x85 }}

typedef struct _EFI_HII_CONFIG_ACCESS_PROTOCOL EFI_HII_CONFIG_ACCESS_PROTOCOL;;

#define EFI_BROWSER_ACTION_REQUEST_NONE    0
#define EFI_BROWSER_ACTION_REQUEST_RESET   1
#define EFI_BROWSER_ACTION_REQUEST_SUBMIT  2
#define EFI_BROWSER_ACTION_REQUEST_EXIT    3

#define EFI_BROWSER_ACTION_REQUEST_CHANGING  0
#define EFI_BROWSER_ACTION_REQUEST_CHANGED   1

typedef UINTN   EFI_BROWSER_ACTION;
typedef UINT16  EFI_QUESTION_ID;
typedef UINTN   EFI_BROWSER_ACTION_REQUEST;

typedef
EFI_STATUS
(EFIAPI *EFI_HII_ACCESS_EXTRACT_CONFIG ) (
IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL    *This,
IN CONST EFI_STRING                        Request,
OUT EFI_STRING                             *Progress,
OUT EFI_STRING                             *Results
);


typedef
EFI_STATUS
(EFIAPI *EFI_HII_ACCESS_ROUTE_CONFIG ) (
IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL    *This,
IN CONST EFI_STRING                        Configuration,
OUT EFI_STRING                             *Progress
);


typedef
EFI_STATUS
(EFIAPI *EFI_HII_ACCESS_FORM_CALLBACK) (
IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL    *This,
IN EFI_BROWSER_ACTION                      *Action,
IN EFI_QUESTION_ID                         QuestionId,
IN UINT8                                   Type,
IN EFI_IFR_TYPE_VALUE                      *Value,
OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest
);

//
// Interface structure for the HII Configuration Access Protocol
//

struct  _EFI_HII_CONFIG_ACCESS_PROTOCOL {
EFI_HII_ACCESS_EXTRACT_CONFIG  ExtractConfig;
EFI_HII_ACCESS_ROUTE_CONFIG    RouteConfig;
EFI_HII_ACCESS_FORM_CALLBACK   CallBack;
};

extern EFI_GUID  gBlackBoxEfiHIIConfigAccessProtocolGuid; 

#endif
