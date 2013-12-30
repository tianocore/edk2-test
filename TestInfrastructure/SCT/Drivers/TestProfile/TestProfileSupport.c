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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  TestProfileSupport.c

Abstract:

  Provides the support services for the test profile library driver.

--*/
#include "Efi.h"
#include "TestProfileSupport.h"

extern EFI_BOOT_SERVICES *gBS;

VOID *
MemSet(
  VOID        *b,
  INTN        c,
  UINTN       len
  )
{
  CHAR8 *p;
  UINTN i;

  p = b;
  for (i = 0; i < len; i++) {
    p[i] = (CHAR8)c;
  }
  return (p);
}

VOID *
Calloc(
  UINTN       NMemb,
  UINTN       MembSize
  )
{
  UINTN NewSize;
  VOID *NewMem;

  NewSize = NMemb * MembSize;
  NewMem = Malloc (NewSize);
  if (NewMem) {
    MemSet (NewMem, 0, NewSize);
  }

  return NewMem;
}

VOID*
Malloc (
  UINTN       size
  )
{
  VOID  *pMem;

  if (gBS->AllocatePool (EfiBootServicesData, size, &pMem) != EFI_SUCCESS) {
    return NULL;
  }
  return pMem;
}

VOID
Free (
  VOID        *addr
  )
{
  gBS->FreePool (addr);
}

INTN
MemCmp(
  VOID        *s1,
  VOID        *s2,
  UINTN       n
  )
{
  CHAR8 *p1, *p2;

  p1 = s1;
  p2 = s2;
  if (n != 0) {
    do {
      if (*p1++ != *p2++)
        return (*--p1 - *--p2);
    } while (--n != 0);
  }
  return (0);
}

VOID *
MemCpy(
  VOID        *dst,
  VOID        *src,
  UINTN       len
  )
{
  CHAR8 *d, *s;

  d = dst;
  s = src;
  while (len--) {
    *(d++) = *(s++);
  }
  return dst;
}

CHAR8 *
StrChr(
  CHAR8       *p,
  INTN        ch
  )
{
  for (; ; ++p) {
    if (*p == ch)
      return((CHAR8 *)p);
    if (!*p)
      return((CHAR8 *)NULL);
  }
  /* NOTREACHED */
}

INTN
StrCmp(
  CHAR8       *s1,
  CHAR8       *s2
  )
{
  while (*s1 == *s2++) {
    if (*s1++ == 0)
      return 0;
  }
  return (*s1 - *s2 - 1);
}

INTN
StriCmp(
  CHAR8       *s1,
  CHAR8       *s2
  )
{
  while (toupper(*s1) == toupper(*s2)) {
    s2++;
    if (*s1++ == 0)
      return (0);
  }
  return (*s1 - *s2);
}

CHAR8 *
StrCpy(
  CHAR8       *to,
  CHAR8       *from
  )
{
  CHAR8 *save;

  save = to;
  for (; (*to = *from) != 0 ; ++from, ++to)
    ;
  return(save);
}

CHAR8 *
StrnCpy(
  CHAR8       *dst,
  CHAR8       *src,
  UINTN       n
  )
{
  CHAR8 *d;
  CHAR8 *s;

  d = dst;
  s = src;
  if (n != 0) {
    do {
      if ((*d++ = *s++) == 0) {
        /* NUL pad the remaining n-1 bytes */
        while (--n != 0)
          *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  return (dst);
}

UINTN
StrLen(
  CHAR8       *str
  )
{
  CHAR8 *s;

  for (s = str; *s; ++s)
    ;
  return (UINTN)(s - str);
}

CHAR8 *
StrDup(
  CHAR8       *str
)
{
  CHAR8 *copy;

  if (str != NULL) {
    copy = Malloc(StrLen(str) + 1);
    if (copy != NULL)
      return StrCpy(copy, str);
  }
  return NULL;
}

CHAR8 *
StrCat(
  CHAR8       *s,
  CHAR8       *append
)
{
  CHAR8 *save;

  save = s;
  for (; *s; ++s)
    ;
  while ( (*s++ = *append++) != 0)
    ;
  return(save);
}

CHAR16 *
WcsDup (
  CHAR16      *str
)
{
  CHAR16 *copy;

  if (str != NULL) {
    copy = Calloc(WcsLen(str) + 1, sizeof(CHAR16));
    if (copy != NULL)
      return WcsCpy(copy, str);
  }
  return NULL;
}

CHAR16 *
WcsChr(
  CHAR16      *p,
  INTN        ch
  )
{
  for (;; ++p) {
    if (*p == ch)
      return((CHAR16 *)p);
    if (!*p)
      return((CHAR16 *)NULL);
  }
  /* NOTREACHED */
}

CHAR16 *
WcsCpy(
  CHAR16      *to,
  CHAR16      *from
  )
{
  CHAR16 *save;

  save = to;
  for (; (*to = *from) != 0; ++from, ++to)
    ;
  return(save);
}

UINTN
WcsLen(
  CHAR16      *str
  )
{
  CHAR16 *s;

  for (s = str; *s; ++s)
    ;
  return (UINTN)(s - str);
}

UINTN
WcsToMbs(
  CHAR8       *s,
  CHAR16      *pwcs,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *s = (CHAR8) (*pwcs++ & 0x00ff);
    if (*s++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}

UINTN
MbsToWcs(
  CHAR16      *pwcs,
  CHAR8       *s,
  UINTN       n
  )
{
  UINTN cnt;

  cnt = 0;
  if (!pwcs || !s)
    return (UINTN)-1;

  while (n-- > 0) {
    *pwcs = (CHAR16)(*s++ & 0x00ff);
    if (*pwcs++ == 0) {
      break;
    }
    ++cnt;
  }
  return (cnt);
}
