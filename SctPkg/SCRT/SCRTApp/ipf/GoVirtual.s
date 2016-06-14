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
//  GoVirtual.S
//
//--*/ 
.file  "GoVirtual.s"

#include  "IpfMacro.i"
#include  "IpfDefines.h"

//#define VIRT_TO_PHYS_OFFSET           0x10000000000
#define VIRT_TO_PHYS_OFFSET            (0x10000000000000)

//-----------------------------------------------------------------------------
//++
// Enter virtual mode
//
// Arguments :
//
// On Entry :
//          in0 - virtual to physical offset
//          in1 - pointer to the continuation function
//          in2 - Configuration Info Data
// Return Value:
//          Never returns
//
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (GoVirtual)

      NESTED_SETUP (3,4,5,0)
      rsm  0x6000;;                      // Clear psr.ic and psr.i
      srlz.i;;
      srlz.d;;

//
// Reserve the targeted ip and gp, after transfering to virtual mode, jump there.
//
      ld8     r7  = [in1], 8;;
      ld8     r8  = [in1];;
      mov     r10 = in2;;

//
//  call rfi to transfer the mode to virtual mode
//
      movl    loc3 = ((1 << PSR_IT)|(1 << PSR_IC)|(1 << PSR_DT)|(1 << PSR_RT)|(1 << PSR_BN)|(1 << PSR_DI));;
      mov     cr.ipsr = loc3;;
    
BeforeJumpVir:
      mov         r9 = ip;;
      add         r9 = (AfterJumpVir - BeforeJumpVir),r9;;
      add         r9 = in0, r9;;
      mov         cr.ifs = r0;;               
      mov         cr.iip = r9;;


      //
      // The following code is to translate RSE to virtual mode.
      //
      flushrs;;

      mov         r29 = sp;;
      mov         r30 = gp;;
      mov         r31 = ar.bspstore;;

      add         r29 = r29, in0;;
      add         r30 = r30, in0;;
      add         r31 = r31, in0;;      
      
      alloc       r11=0,0,0,0;;               // Set 0-size frame

      mov         r28 = RSC_KERNEL_DISABLED;; // for rse disable
      mov         ar.rsc = r28;;              // turn off RSE

      mov         sp = r29;;
      mov         gp = r30;;
      mov         ar.bspstore = r31;;           // switch to EFI BSP
      invala;;                                  // change of ar.bspstore needs invala.

      mov         r28 = RSC_KERNEL_LAZ;;        // RSC enabled, Lazy mode
      mov         ar.rsc = r28;;                // turn rse on, in kernel mode
     
      //
      // Finally go to virutal mode
      // 
      rfi;;

AfterJumpVir::   
     //
     // Here we are in virtual mode.
     //

     //
     // Alloc the out in the new environment to construct out0 to pass the arg.
     //            
        alloc   r11 = 0,0,1,0 ;;          
        mov     out0 = r10 ;;

        mov   b2   = r7;;
        mov   gp   = r8;;
          
        br.call.sptk.few  b0 = b2;; //This will incur I-TLB miss exception
 
      //NESTED_RETURN

PROCEDURE_EXIT (GoVirtual)

