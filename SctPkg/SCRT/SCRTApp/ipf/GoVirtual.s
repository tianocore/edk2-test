// @file
//
//  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
//  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
//
//  This program and the accompanying materials
//  are licensed and made available under the terms and conditions of the BSD License
//  which accompanies this distribution.  The full text of the license may be found at 
//  http://opensource.org/licenses/bsd-license.php
// 
//  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
//  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
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

