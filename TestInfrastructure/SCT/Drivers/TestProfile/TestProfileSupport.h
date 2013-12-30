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

  TestProfileSupport.h

Abstract:

  Provides the support services for the test profile library driver.

--*/

#ifndef _EFI_TEST_PROFILE_SUPPORT_H_
#define _EFI_TEST_PROFILE_SUPPORT_H_


#define  toupper(c)  (((c <= 'z') && (c >= 'a')) ? (c + 'A' - 'a') : c)
#define  tolower(c)  (((c <= 'Z') && (c >= 'A')) ? (c - 'A' + 'a') : c)

VOID *
MemSet(
  VOID        *b,
  INTN        c,
  UINTN       len
  );

VOID *
Calloc(
  UINTN       NMemb,
  UINTN       MembSize
  );

VOID*
Malloc(
  UINTN       size
  );

VOID
Free(
  VOID        *addr
  );

INTN
MemCmp(
  VOID        *s1,
  VOID        *s2,
  UINTN       n
  );

VOID *
MemCpy(
  VOID        *dst,
  VOID        *src,
  UINTN       len
  );

INTN
StrCmp(
  CHAR8       *s1,
  CHAR8       *s2
  );

INTN
StriCmp(
  CHAR8       *s1,
  CHAR8       *s2
  );

CHAR8 *
StrChr(
  CHAR8       *p,
  INTN        ch
  );

CHAR8 *
StrCpy(
  CHAR8       *to,
  CHAR8       *from
  );

CHAR8 *
StrnCpy(
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  );

CHAR8 *
StrCat(
  CHAR8       *s,
  CHAR8       *append
  );

UINTN
StrLen(
  CHAR8       *str
  );

CHAR8 *
StrDup(
  CHAR8       *str
);

CHAR16 *
WcsDup (
  CHAR16      *str
);

CHAR16 *
WcsChr(
  CHAR16      *p,
  INTN        ch
  );

CHAR16 *
WcsCpy(
  CHAR16      *to,
  CHAR16      *from
  );

UINTN
WcsLen(
  CHAR16      *str
  );

UINTN
WcsToMbs(
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  );

UINTN
MbsToWcs(
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  );

#endif
