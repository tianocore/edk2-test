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
  
    EmsRivlEndian.c
    
Abstract:

    Implementation of RIVL endian related functions

--*/

#include "EmsRivlMain.h"
#include "EmsRivlEndian.h"

BOOLEAN RivlLittleEndian = TRUE;

UINT64  Lak;

UINT16
RivlSwap16 (
  UINT16  N
  )
/*++

Routine Description:

  Swap the bytes of a INT16

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
{
  UINT16  M;
  UINT8   *B;
  B = (UINT8 *) &N;
  if (RivlLittleEndian) {
    M = (UINT16) (B[0] << 8 | B[1]);
  } else {
    M = N;
  }

  return M;
}

UINT32
RivlSwap32 (
  UINT32  N
  )
/*++

Routine Description:

  Swap the bytes of a INT32

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
{
  UINT32  M;
  UINT8   *B;
  B = (UINT8 *) &N;

  if (RivlLittleEndian) {
    M = (UINT32) (B[0] << 24 | B[1] << 16 | B[2] << 8 | B[3]);
  } else {
    M = N;
  }

  return M;
}

UINT64
RivlSwap64 (
  UINT64  N
  )
/*++

Routine Description:

  Swap the bytes of a INT64

Arguments:

  N - The number should be swapped

Returns:

  The result

--*/
{
  union {
    UINT64  N;
    UINT8   B[8];
  } U;

  UINT8 T;
  U.N = N;

  if (RivlLittleEndian) {

    T       = U.B[0];
    U.B[0]  = U.B[7];
    U.B[7]  = T;

    T       = U.B[1];
    U.B[1]  = U.B[6];
    U.B[6]  = T;

    T       = U.B[2];
    U.B[2]  = U.B[5];
    U.B[5]  = T;

    T       = U.B[3];
    U.B[3]  = U.B[4];
    U.B[4]  = T;
  }

  return U.N;
}
