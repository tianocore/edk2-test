//@file
// 
//  Copyright 2006 - 2017 Unified EFI, Inc.<BR> 
//  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
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
// Module Name:
//
//   RivlCall.s
//
// Abstract:
//
//    RivlCall
//
//--*/
//-------------------------------------------------------------------------------------------------------
// UINTN RivlCall (VOID *FuncAddr, UINTN CallingType, UINTN Number, UINTN *StackTop, UINTN *StackBottom);
//-------------------------------------------------------------------------------------------------------

.text
.type RivlCall, @function
.proc RivlCall
RivlCall::

     alloc              loc1 = ar.pfs,5,10,8,0
     mov                loc0 = b0
     mov                loc8 = ar.lc
     mov                loc9 = sp
     mov                loc2 = gp ;;

     mov                loc3 = in3 ;;
     ld8                out0 = [loc3],8 ;;
     ld8                out1 = [loc3],8 ;;
     ld8                out2 = [loc3],8 ;;
     ld8                out3 = [loc3],8 ;;
     ld8                out4 = [loc3],8 ;;
     ld8                out5 = [loc3],8 ;;
     ld8                out6 = [loc3],8 ;;
     ld8                out7 = [loc3],8 ;;
     mov                loc7 = 8 ;;
     cmp.leu            p6,p7 = in2,loc7 ;;
 (p6)br.cond.sptk       ready ;;

     //
     // if arg num > 8, save it in memory
     //
     adds               loc6 = -0x8,sp
     adds               loc7 = -8,in2 ;;
     mov                ar.lc = loc7 ;;
tomem:
     ld8                loc7 = [loc3],8 ;;
     st8                [loc6] = loc7,-0x8 ;;
     br.cloop.sptk      tomem ;;
     adds               sp = -0x8,loc6;;

ready:
     mov                loc4 = in0 ;;
     ld8                loc5 = [loc4],8 ;;
     ld8                gp = [loc4] ;;
     mov                b5 = loc5 ;;
     br.call.sptk       b0 = b5 ;;

     mov                gp = loc2
     mov                sp = loc9
     mov                ar.lc = loc8
     mov                b0 = loc0 
     mov                ar.pfs = loc1 ;;
     br.ret.sptk        b0 ;;

.endp RivlCall

