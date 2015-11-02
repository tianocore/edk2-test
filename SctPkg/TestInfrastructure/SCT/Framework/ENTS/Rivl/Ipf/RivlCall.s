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

