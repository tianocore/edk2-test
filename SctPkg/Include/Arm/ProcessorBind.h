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
                                                                
  Copyright (c) 2011, 2012, ARM Ltd. All rights reserved.    
   
--*/
/*++
  Processor or Compiler specific defines and types for ARM.         

--*/

#ifndef __PROCESSOR_BIND_H__
#define __PROCESSOR_BIND_H__

///
/// Define the processor type so other code can make processor based choices
///
#define MDE_CPU_ARM

//
// Make sure we are using the correct packing rules per EFI specification
//
#ifndef __GNUC__
#pragma pack()
#endif

#if _MSC_EXTENSIONS 
  //
  // use Microsoft* C complier dependent interger width types 
  //
  typedef unsigned __int64    UINT64;
  typedef __int64             INT64;
  typedef unsigned __int32    UINT32;
  typedef __int32             INT32;
  typedef unsigned short      UINT16;
  typedef unsigned short      CHAR16;
  typedef short               INT16;
  typedef unsigned char       BOOLEAN;
  typedef unsigned char       UINT8;
  typedef char                CHAR8;
  typedef char                INT8;
#else
  //
  // Assume standard ARM alignment. 
  // Need to check portability of long long
  //
  typedef unsigned long long  UINT64;
  typedef long long           INT64;
  typedef unsigned int        UINT32;
  typedef int                 INT32;
  typedef unsigned short      UINT16;
  typedef unsigned short      CHAR16;
  typedef short               INT16;
  typedef unsigned char       BOOLEAN;
  typedef unsigned char       UINT8;
  typedef char                CHAR8;
  typedef char                INT8;
#endif

///
/// Unsigned value of native width.  (4 bytes on supported 32-bit processor instructions,
/// 8 bytes on supported 64-bit processor instructions)
///
typedef UINT32  UINTN;

///
/// Signed value of native width.  (4 bytes on supported 32-bit processor instructions,
/// 8 bytes on supported 64-bit processor instructions)
///
typedef INT32   INTN;

//
// Processor specific defines
//

///
/// A value of native width with the highest bit set.
///
#define MAX_BIT      0x80000000

///
/// A value of native width with the two highest bits set.
///
#define MAX_2_BITS   0xC0000000

///
/// Maximum legal ARM address
///
#define MAX_ADDRESS  0xFFFFFFFF

///
/// The stack alignment required for ARM
///
#define CPU_STACK_ALIGNMENT  sizeof(UINT64)

//
// Modifier to ensure that all protocol member functions and EFI intrinsics
// use the correct C calling convention. All protocol member functions and
// EFI intrinsics are required to modify their member functions with EFIAPI.
//
#define EFIAPI    

#if defined(__GNUC__)
  ///
  /// For GNU assembly code, .global or .globl can declare global symbols.
  /// Define this macro to unify the usage.
  ///
  #define ASM_GLOBAL .globl

  #if !defined(__APPLE__)
    ///
    /// ARM EABI defines that the linker should not manipulate call relocations
    /// (do bl/blx conversion) unless the target symbol has function type.
    /// CodeSourcery 2010.09 started requiring the .type to function properly
    ///
    #define INTERWORK_FUNC(func__)   .type ASM_PFX(func__), %function

    #define GCC_ASM_EXPORT(func__)  \
             .global  _CONCATENATE (__USER_LABEL_PREFIX__, func__)    ;\
             .type ASM_PFX(func__), %function  

    #define GCC_ASM_IMPORT(func__)  \
             .extern  _CONCATENATE (__USER_LABEL_PREFIX__, func__)
             
  #else
    //
    // .type not supported by Apple Xcode tools 
    //
    #define INTERWORK_FUNC(func__)  

    #define GCC_ASM_EXPORT(func__)  \
             .globl  _CONCATENATE (__USER_LABEL_PREFIX__, func__)    \
  
    #define GCC_ASM_IMPORT(name)  

  #endif
#endif

/**
  Return the pointer to the first instruction of a function given a function pointer.
  On ARM CPU architectures, these two pointer values are the same, 
  so the implementation of this macro is very simple.
  
  @param  FunctionPointer   A pointer to a function.

  @return The pointer to the first instruction of a function given a function pointer.
  
**/
#define FUNCTION_ENTRY_POINT(FunctionPointer) (VOID *)(UINTN)(FunctionPointer)

#endif


