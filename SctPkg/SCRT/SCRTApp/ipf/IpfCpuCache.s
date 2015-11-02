//
// The material contained herein is not a license, either      
// expressly or impliedly, to any intellectual property owned  
// or controlled by any of the authors or developers of this   
// material or to any contribution thereto. The material       
// contained herein is provided on an "AS IS" basis and, to the
// maximum extent permitted by applicable law, this information
// is provided AS IS AND WITH ALL FAULTS, and the authors and  
// developers of this material hereby disclaim all other       
// warranties and conditions, either express, implied or       
// statutory, including, but not limited to, any (if any)      
// implied warranties, duties or conditions of merchantability,
// of fitness for a particular purpose, of accuracy or         
// completeness of responses, of results, of workmanlike       
// effort, of lack of viruses and of lack of negligence, all   
// with regard to this material and any contribution thereto.  
// Designers must not rely on the absence or characteristics of
// any features or instructions marked "reserved" or           
// "undefined." The Unified EFI Forum, Inc. reserves any       
// features or instructions so marked for future definition and
// shall have no responsibility whatsoever for conflicts or    
// incompatibilities arising from future changes to them. ALSO,
// THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
// QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
// NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
// CONTRIBUTION THERETO.                                       
//                                                             
// IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
// ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
// THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
// PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
// CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
// UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
// WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
// DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
// THE POSSIBILITY OF SUCH DAMAGES.                            
//                                                             
// Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
// Rights Reserved, subject to all existing rights in all      
// matters included within this Test Suite, to which United    
// EFI, Inc. makes no claim of right.                          
//                                                             
// Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
//
//
///*++
//
//Module Name:
//
//  IpfCpuCache.s
//
//--*/ 

.file  "IpfCpuCache.s"

#include  "IpfMacro.i"
#include  "IpfDefines.h"

//-----------------------------------------------------------------------------
//++
// Flush Cache
//
// Arguments : 

// Input = in0 = Starting Address to Flush.
// Input = in1 = Length in bytes.
// Input = b0 = return branch register.
// On Entry :
//
// Return Value: 
//
//  VOID
//  FlushCache (
//    IN UINT64   BaseToFlush,
//    IN UINT64   LengthToFlush
//    );
//
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (FlushCache)

      NESTED_SETUP (5,8,0,0)
            
      mov         loc2 = ar.lc
      
      mov         loc3 = in0                  // Start address.
      mov         loc4 = in1;;                // Length in bytes.
      
      cmp.eq  p6,p7 = loc4, r0;;               // If Length is zero then don't flush any cache
      (p6)  br.spnt.many DoneFlushingC;;         
      
      add         loc4 = loc4,loc3 
      mov         loc5 = 1;;
      sub         loc4 = loc4, loc5 ;; // the End address to flush
                                         
      dep         loc3 = r0,loc3,0,5          
      dep         loc4 = r0,loc4,0,5;;         
      shr         loc3 = loc3,5             
      shr         loc4 = loc4,5;;    // 32 byte cache line
      
      sub         loc4 = loc4,loc3;; // total flush count, It should be add 1 but 
                                     // the br.cloop will first execute one time 
      mov         loc3 = in0                  
      mov         loc5 = 32      
      mov         ar.lc = loc4;;

StillFlushingC:
      fc          loc3;; 
      sync.i;;
      srlz.i;;
      add         loc3 = loc5,loc3;;
      br.cloop.sptk.few StillFlushingC;;

DoneFlushingC:      
      mov         ar.lc = loc2     
      NESTED_RETURN

PROCEDURE_EXIT (FlushCache)

