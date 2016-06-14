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

  Guid.h

Abstract:

  GUIDs for SCRT test assertion.

--*/
#ifndef __GUID_H__
#define __GUID_H__


#define EFI_TEST_SCRT_ASSERTION_11_GUID \
{ 0xbff7e548, 0xf13a, 0x497c, { 0x8e, 0x21, 0xae, 0xc2, 0x37, 0xa6, 0xcc, 0xe3 } }

extern EFI_GUID gSCRTAssertionGuid11;

#define EFI_TEST_SCRT_ASSERTION_12_GUID \
{ 0xf556b5ad, 0xaace, 0x4bf0, { 0xb7, 0x24, 0xe1, 0x29, 0xee, 0x0, 0xea, 0x37 } }

extern EFI_GUID gSCRTAssertionGuid12;

#define EFI_TEST_SCRT_ASSERTION_21_GUID \
{ 0xd66e4a7f, 0x6d54, 0x4cc0, { 0xb9, 0x3b, 0xf6, 0x2f, 0x48, 0x57, 0xa6, 0xff } }

extern EFI_GUID gSCRTAssertionGuid21;

#define EFI_TEST_SCRT_ASSERTION_22_GUID \
{ 0xaa5c5763, 0x36cd, 0x4f00, { 0x84, 0x36, 0xf4, 0xa9, 0xd5, 0xaf, 0x12, 0xfb } }

extern EFI_GUID gSCRTAssertionGuid22;

#define EFI_TEST_SCRT_ASSERTION_23_GUID \
{ 0xbac20972, 0x9662, 0x4f24, { 0x8a, 0xac, 0x66, 0x41, 0x42, 0xb5, 0x6d, 0xde } }

extern EFI_GUID gSCRTAssertionGuid23;

#define EFI_TEST_SCRT_ASSERTION_31_GUID \
{ 0x8bcda7a3, 0x2848, 0x413d, { 0xbf, 0x5, 0x7, 0xe1, 0x9, 0x8d, 0x42, 0xd2 } }

extern EFI_GUID gSCRTAssertionGuid31;

#define EFI_TEST_SCRT_ASSERTION_32_GUID \
{ 0x67b4e72a, 0xc792, 0x4f74, { 0x92, 0x1d, 0xea, 0xb3, 0x66, 0x4f, 0x95, 0x3b } }

extern EFI_GUID gSCRTAssertionGuid32;

#define EFI_TEST_SCRT_ASSERTION_33_GUID \
{ 0xdbb5195f, 0x3584, 0x427d, { 0xa1, 0x68, 0x3f, 0x5e, 0x1d, 0x24, 0x3b, 0xb9 } }

extern EFI_GUID gSCRTAssertionGuid33;

#define EFI_TEST_SCRT_ASSERTION_41_GUID \
{ 0x8e75d9a9, 0x3c14, 0x4095, { 0xbe, 0x76, 0xad, 0xcf, 0x55, 0xab, 0x8e, 0x6c } }

extern EFI_GUID gSCRTAssertionGuid41;

#define EFI_TEST_SCRT_ASSERTION_51_GUID \
{ 0xe8cd357a, 0xd254, 0x4f7b, { 0x92, 0xc3, 0x23, 0xfd, 0x4d, 0xd6, 0xc0, 0xa3 } }

extern EFI_GUID gSCRTAssertionGuid51;

#define EFI_TEST_SCRT_ASSERTION_61_GUID \
{ 0x6417f479, 0xa174, 0x4614, { 0x80, 0xcd, 0xe6, 0x96, 0x85, 0x8c, 0xd9, 0xfa } }

extern EFI_GUID gSCRTAssertionGuid61;

#define EFI_TEST_SCRT_ASSERTION_62_GUID \
{ 0xd6a3c41a, 0xe6cf, 0x42fc, { 0xa0, 0x39, 0x68, 0xf8, 0x39, 0xbb, 0xbf, 0xe3 } }

extern EFI_GUID gSCRTAssertionGuid62;

#define EFI_TEST_SCRT_ASSERTION_71_GUID \
{ 0xd6b952a9, 0x3d54, 0x4277, { 0xbf, 0x60, 0xab, 0xfb, 0x3, 0x71, 0x5, 0xd5 } }

extern EFI_GUID gSCRTAssertionGuid71;

#define EFI_TEST_SCRT_ASSERTION_72_GUID \
{ 0x3f65c680, 0xae51, 0x4830, { 0xb3, 0xd1, 0xd7, 0xc9, 0x2a, 0xcd, 0x14, 0x8a } }

extern EFI_GUID gSCRTAssertionGuid72;

#define EFI_TEST_SCRT_ASSERTION_81_GUID \
{ 0x4611524b, 0xbfd2, 0x42d4, { 0x85, 0xa8, 0x9b, 0xf, 0xd1, 0xc6, 0x27, 0xd3 } }

extern EFI_GUID gSCRTAssertionGuid81;

#define EFI_TEST_SCRT_ASSERTION_91_GUID \
{ 0x5c2cbd54, 0x1388, 0x4e87, { 0xab, 0x11, 0x2c, 0x12, 0x3d, 0x24, 0x5, 0xbd } }

extern EFI_GUID gSCRTAssertionGuid91;

#define EFI_TEST_SCRT_ASSERTION_A1_GUID \
{ 0x9e39a3e3, 0xcbb6, 0x4fcc, { 0xb2, 0x21, 0x73, 0x24, 0x79, 0xf1, 0x21, 0x77 } }

extern EFI_GUID gSCRTAssertionGuidA1;

#define EFI_TEST_SCRT_ASSERTION_B1_GUID \
{ 0xda790c1e, 0xdcbf, 0x4c0e, { 0xaf, 0xf7, 0x46, 0x3a, 0xc4, 0x47, 0xb0, 0x6e } }

extern EFI_GUID gSCRTAssertionGuidB1;

#define EFI_TEST_SCRT_ASSERTION_C1_GUID \
{ 0x1bc049bb, 0xc371, 0x46cc, { 0x8d, 0x98, 0xef, 0x56, 0xc, 0x35, 0x7f, 0x1 } }

extern EFI_GUID gSCRTAssertionGuidC1;

#define EFI_TEST_SCRT_ASSERTION_C2_GUID \
{ 0x11a541a4, 0xf75d, 0x42e0, { 0xa8, 0x97, 0xe7, 0x92, 0xd4, 0x37, 0xc2, 0xfc } }

extern EFI_GUID gSCRTAssertionGuidC2;

#define EFI_TEST_SCRT_ASSERTION_C3_GUID \
{ 0xe5818568, 0x4723, 0x473f, { 0xbc, 0x8f, 0xb5, 0x86, 0x2e, 0xd2, 0x5e, 0xb1 } }

extern EFI_GUID gSCRTAssertionGuidC3;

#endif
