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
//  IpfIvaHand.s
//
//--*/ 

.file  "IpfIvaHand.s"

#include  "IpfMacro.i"
#include  "IpfDefines.h"

#define   USING_MEMMAP_ENTRIES        0x80
#define   IVT_SIZE_PLUS_TABLE         0x8000
#define   MEMMAP_SIZE                 0x2000       
#define   STORAGE_SIZE                0X800
//#define   VIRT_TO_PHYS_OFFSET         0x10000000000
#define VIRT_TO_PHYS_OFFSET            (0x10000000000000)
#define   PAGE_SIZE_64K               0x10


//-----------------------------------------------------------------------------
//++
// Purge existing translation register entries
//
// Arguments :
//
// On Entry :
//      in0 = virtual address
//      in1 = range size
//
// Return Value:
//      Never returns
//
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (PurgeTlb)

  NESTED_SETUP (2,2,0,0);;
  
  ptr.i in0, in1;;
  ptr.d in0, in1;;
  
  mf;;
  
  srlz.d;;
  
  srlz.i;;
  
  NESTED_RETURN

PROCEDURE_EXIT (PurgeTlb)


//-----------------------------------------------------------------------------
//++
// Initialize processor interrupt control registers
//
//--
//---------------------------------------------------------------------------
        PROCEDURE_ENTRY (InitializeInterruptControlRegisters)

        NESTED_SETUP (0,3,0,0)
        rsm         0x4000                      // Make sure interrupts are masked
        ssm         0x2000                      // Allow interrupt collection
                                                // for faults etc.
        srlz.d;;
        mov         loc2 = (1<<0x10);;
        mov         cr.itv = loc2               // Disable timer
        mov         cr.tpr = r0                 // Allow all interrupts 
        srlz.d;;
        
        NESTED_RETURN

        PROCEDURE_EXIT (InitializeInterruptControlRegisters)

//-----------------------------------------------------------------------------
//++
// Get the base of interurpt vector table
//
//  EFI_PHYSICAL_ADDRESS
//  GetIva (
//    VOID
//    );

//--
//---------------------------------------------------------------------------
        PROCEDURE_ENTRY (GetIva)

        NESTED_SETUP (0,2,0,0)
        mov         r8=cr.iva;;
        NESTED_RETURN
        ;;
        PROCEDURE_EXIT (GetIva)
//-----------------------------------------------------------------------------
//++
// Set TR
//
// Arguments : 
//  in0 - TR number
//  in1 - properly aligned physical base address
//  in2 - Encoded page size (ITIR.PS)
//
// Return Value: 
//  None
//--
//---------------------------------------------------------------------------
        PROCEDURE_ENTRY (SetTR)

        NESTED_SETUP (3,7,0,0)
        mov         loc4 = psr
        rsm         0x6000                      // Make sure interrupts are masked
        srlz.i;;

        movl        loc5 = VIRT_TO_PHYS_OFFSET;;
//
// Set up RID[0], ve=0
//
        dep.z       loc3 = in2, RR_PS, RR_PS_LEN              // Fill in preferred page size
        mov         loc2 = (SAL_RID >> 8);;
        dep         loc3 = loc2, loc3, RR_RID+8, RR_RID_LEN-8 // Fill in RID
        mov         loc2 = SAL_RR_REG;;
        mov         rr[loc2] = loc3
        srlz.i;;

        dep.z       loc3 = in2, ITIR_PS, ITIR_PS_LEN;;      // Fill in page size
        mov         cr.itir = loc3;;
        dep         loc3 = SAL_RR_REG, in1, 61, 3;;
        add         loc3 = loc3, loc5;;                     // change physical to virtual address
        mov         cr.ifa = loc3;;                         // VPN including RID

        mov         loc3 = in1                              // Physical address
        mov         loc2 = ATTR_DEF_BITS;;                  // Get default bits such as Present, etc.
        or          loc3 = loc3, loc2                       // Fill in PPN

        mov         loc2 = in0;;
        itr.i       itr[loc2] = loc3;;                      // Insert TR entry to cover Interrupt handlers
        srlz.i;;

        itr.d       dtr[loc2] = loc3;;                     // Insert DTR
        srlz.d;;
        srlz.i;;

        mov         psr.l = loc4;;
        srlz.i;;
        srlz.d;;
        
        NESTED_RETURN

PROCEDURE_EXIT (SetTR)


//-----------------------------------------------------------------------------
//++
// Set the base of interurpt vector table.
//
// Arguments : 
//  in0 - properly aligned physical IVA base address
//
// Return Value: 
//  None
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (SetIVA)

        NESTED_SETUP (1,5,0,0)
        mov         loc4 = psr
        rsm         0x6000                      // Make sure interrupts are masked
        mov         cr.iva=in0;;
        srlz.i;;
        mov         psr.l = loc4;;
        srlz.i;;
        srlz.d;;
 
        NESTED_RETURN

PROCEDURE_EXIT (SetIVA)


//-----------------------------------------------------------------------------
//++
// Entry point of an interrupt/fault handler. This is merely a stub that
// gets copied to various places in the IVT. It jumps to the actual handler.
// The actual handlers lie outside IVT.
//
// Arguments : 
//  None
//
// Return Value: 
//  None
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY (IvtStub)

        mov         r29 =ip;;
        mov         r30 = b0;;

//Dealoop::
//        br.sptk.few Dealoop;;   
     

//
// Get the runtime address of the Handler in r31 using
// IP relative addressing
// 
myIp::
        mov         r31 = ip;;
        add         r31 = (HandlerAddress - myIp), r31;;
        ld8         r31= [r31];;

        add         r29 = r31, r29;;
        mov         b0 = r29;;

//          
// Branch to the actual handler.
//

        br          b0;;

PROCEDURE_EXIT (IvtStub)

PROCEDURE_ENTRY (IvtStubEnd)
PROCEDURE_EXIT (IvtStubEnd)

//
// Offset of the handler from the start of IvtStub is 
// stored here
//

HandlerAddress::
        data8 0
        data8 0                           // Needed to align the next proc on a 16 byte boundary


//
// Signal start of Interrupt handlers
//

INTERRUPT_HANDLER_BLOCK_BEGIN

//
// Signal start of Instruction TLB fault handler Code
//

INTERRUPT_HANDLER_BEGIN (InstructionTlbFault)
//-----------------------------------------------------------------------------
//++
// Alternate Instrution TLB fault handler
//
// Arguments : 
//  r30 = old b0
//
// Return Value: 
//  None
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY(AltItlbEntry)

      mov          b0 = r30;;                    // Restore B0 from r10
     
      mov         r27 = cr.ifa;;                 
      movl        r28 = 0xffffffffffff0000;;           
      and         r27 = r27, r28;;              // align 64K 
      mov         cr.ifa = r27;;

      mov         r26 = r27;;
      movl        r29 = VIRT_TO_PHYS_OFFSET;;
      sub         r27 = r27, r29;;

      dep.z       r28 = PAGE_SIZE_64K, ITIR_PS, ITIR_PS_LEN;;  //PageSize is 64K to minimize I-TLB miss
      mov         cr.itir = r28;;                          // Fill in page size

      mov         r30 = r28;;

      mov         r28 = ATTR_IPAGE;;

      dep         r29 = r28, r27, 0, 12;;         // fill bits 47:0
      movl        r31 = 0x0003FFFFFFFFFFFF;;      // clear ED bit, reserved bits 63:50
      and         r29 = r31, r29;;
      ptr.i       r26, r30;;                      // firstly purge the overlap entry
      itc.i       r29;;                           // Install the ITC
      
      rfi;;                                       // RFI is serializing

PROCEDURE_EXIT(AltItlbEntry)

//
// Signal end of Instruction TLB fault handler Code
//

INTERRUPT_HANDLER_END(InstructionTlbFault)



//
// Signal start of Data TLB fault handler Code
//
INTERRUPT_HANDLER_BEGIN(DataTlbFault)


//-----------------------------------------------------------------------------
//++
// Alternate Data TLB fault handler
//
// Arguments : 
//  r30 = old b0
//
// Return Value: 
//  None
//--
//---------------------------------------------------------------------------
PROCEDURE_ENTRY(AltDtlbEntry)
      mov         b0 = r30;;                    // Restore B0 from r10

      mov     r28 = pr;;                          // Save the predicates
      mov     r31 = r2;;                          // save r2

//
//      Check whether the LD was speculative and, if so, set IPSR.ed bit
//

      mov         r25 = cr.ipsr;;
      mov         r24 = cr.isr;;
      tbit.nz     p6, p7 = r24, ISR_SP;;      
 (p6) br.sptk.many AltDtlbSp

        mov         r24 = USING_MEMMAP_ENTRIES;;
        mov         r25 = cr.iva;;                  // Get IVT address
        mov         r26 = IVT_SIZE_PLUS_TABLE;;
        add         r25 = r25, r26;;              // Pointer to memory map table

        mov         r29 = cr.ifa;;              // get faulting address
        dep         r29 = 0, r29, 61, 3;;       // Get rid of Region # for comparisons with physical addresses in MDT

        movl        r26 = VIRT_TO_PHYS_OFFSET;;
        sub         r29 = r29,r26;;             // virtual address is changed to physical address
LoopTLB:
        ld8         r26 = [r25], 8;;
        ld8         r27 = [r25], 8;;
  
//
//  Test whether the faulting address (in r29) is within the current entry
//

      cmp.ltu     p1, p2 = r29, r26;;           // If less than our entry, error
 (p1) br.sptk.few  BadMDT;;
        ;;
      cmp.ltu     p3, p4 = r29, r27;;           // Found if less than ending addrss+1
 (p3) br.sptk.few  FoundTLB;;

//
//  Advance to next MDT entry.Error if all entries are exhausted
//

        mov         r26 = 0x10;;
        add         r25 = r25, r26;;            // Skip attributes and page size fields
  
      add         r24 = -1, r24;;
      cmp.eq      p5, p6 = r24, r0;;            // Is loop count = 0 after decrement?

 (p5) br.sptk.few BadMDT;;
 (p6) br.sptk.few LoopTLB;;


FoundTLB:        
//    Live registers:
//                  r29 = cr.ifa without Region # (Already changed to physical address)
//                  r28, r31 = preserved PR & r2
//                  r25 points to the attribute field
//                  r26 start of the block
//                  r27 end address of the block


      ld8     r24 = [r25], 8;;                // Attributes
      dep.z   r30 = r24, 2, 3;;                 // Mem Attribute into bits 2-4

      mov     r24 = ATTR_DEF_BITS;;             // Get default bits such as Present, etc.
      or      r30 = r30, r24;;                    // ar, pl, d, a, ma, p fields in r30 set up

      mov     r24 = cr.itir;;                   // Need to revise page size in ITIR
      ld8     r2 = [r25];;                        // Get page size
      mov     r25 = -1;;
      shl     r25 = r25, r2;;                     // get zeros into low order bits
                                                // depending on page size
      movl    r27 = 0x0003FFFFFFFFFFFF;;          // clear bits 50-63. 
      and     r25 = r25, r27;;                    // Clear some low order bits.
                                                // r25 has the corect mask to
                                                // get vpn xx:43 where xx is >= 12                                       
      and     r25 = r25, r29;;                    // get bits 12-43 of vpn into r25
      or      r30 = r25, r30;;                    // move PPN into r30
      dep     r24 = r2, r24, ITIR_PS, ITIR_PS_LEN;;  // Replace page size from RR with MDT value
   
      movl    r29 = VIRT_TO_PHYS_OFFSET;;
      add     r25 = r30, r29;;                  // r25 is virtual address
      ptr.d   r25, r24;;                        //purge virtual address
      srlz.d;;
      
      
      mov     cr.itir = r24;;                     // with one from MDT

      itc.d   r30;;                               // Install the Data TC
//
//      Check whether the LD was speculative and, if so, set IPSR.ed bit
//

AltDtlbSp:
      mov         r25 = cr.ipsr;;
      mov         r24 = cr.isr;;
      tbit.nz     p6, p7 = r24, ISR_SP;;      
 (p6) dep         r25 = 1, r25, PSR_ED, 1;;     // set IPSR.ed, if ISR.sp=1

      mov         cr.ipsr = r25;;
      mov         r2 = r31;;
      mov         pr = r28;;
  
      rfi;;                                       // RFI is serializing

BadMDT:
        br          BadMDT;;

PROCEDURE_EXIT(AltDtlbEntry)

//
// Signal end of Data TLB fault handler Code
//

INTERRUPT_HANDLER_END(DataTlbFault)

//
// Finally, signal end of all interrupt handlers
//
INTERRUPT_HANDLER_BLOCK_END
