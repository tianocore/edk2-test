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

  EfiUi.h

Abstract:

  Protocol used to build User Interface (UI) stuff.

  This protocol is just data. It is a multi dimentional array.
  For each string there is an array of UI_STRING_ENTRY. Each string
  is for a different language translation of the same string. The list
  is terminated by a NULL UiString. There can be any number of
  UI_STRING_ENTRY arrays. A NULL array terminates the list. A NULL array
  entry contains all zeros.

  Thus the shortest possible EFI_UI_PROTOCOL has three UI_STRING_ENTRY.
  The String, it's NULL terminator, and the NULL terminator for the entire
  thing.

--*/

#ifndef _EFI_UI_H
#define _EFI_UI_H

#define EFI_UI_PROTOCOL \
  { 0x32dd7981, 0x2d27, 0x11d4, 0xbc, 0x8b, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81 }

//
// International Language
//

typedef UINT8   ISO_639_2;
#define ISO_639_2_ENTRY_SIZE    3


typedef enum {
  UiDeviceString,
  UiVendorString,
  UiMaxString
} UI_STRING_TYPE;

typedef struct {
  ISO_639_2   *LangCode;
  CHAR16      *UiString;
} UI_STRING_ENTRY;

#define EFI_UI_VERSION      0x00010000

typedef struct _UI_INTERFACE {
  UINT32          Version;
  UI_STRING_ENTRY *Entry;
} UI_INTERFACE;

#endif
