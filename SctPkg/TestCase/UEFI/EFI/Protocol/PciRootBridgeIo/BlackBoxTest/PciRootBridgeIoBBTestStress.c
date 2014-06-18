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

  PciRootBridgeIoBBTestStress.c

Abstract:

 Stress test case source file for Pci Root Bridge Io Protocol

--*/
#include "SctLib.h"
#include "PciRootBridgeIoBBTestMain.h"
#include "PciRootBridgeIoBBTestSupport.h"




/**
 *  Stress test SetAttributes automatically.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.3.1
//
EFI_STATUS
SetAttributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                  SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_PCI_ROOT_BRIDGE_IO_DEVICE         *RBDev;
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL       *RootBridgeIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                SupportedAttributes;
  UINT64                                CommonAttributes;
  UINT64                                CurrentAttributes;
  UINT64                                ResourceBase;
  UINT64                                ResourceLength;
  UINTN                                 Index;
  UINTN                                 AttributesNumber;
  UINT64                                ThisAttribute;


  UINT64          AllAttributes[11] = {
    EFI_PCI_ATTRIBUTE_ISA_MOTHERBOARD_IO,
    EFI_PCI_ATTRIBUTE_ISA_IO,
    EFI_PCI_ATTRIBUTE_VGA_PALETTE_IO,
    EFI_PCI_ATTRIBUTE_VGA_MEMORY,
    EFI_PCI_ATTRIBUTE_VGA_IO,
    EFI_PCI_ATTRIBUTE_IDE_PRIMARY_IO,
    EFI_PCI_ATTRIBUTE_IDE_SECONDARY_IO,
    EFI_PCI_ATTRIBUTE_MEMORY_WRITE_COMBINE,
    EFI_PCI_ATTRIBUTE_MEMORY_CACHED,
    EFI_PCI_ATTRIBUTE_MEMORY_DISABLE,
    EFI_PCI_ATTRIBUTE_DUAL_ADDRESS_CYCLE
  };

  //
  //get tested interface.
  //

  RootBridgeIo = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get RootBridgeIoDevice struct pointer.
  //

  RBDev = NULL;
  RBDev = GetRootBridgeIoDevice (RootBridgeIo);

  if (RBDev == NULL) {
    return EFI_ABORTED;
  }

  //
  //print the device path of root Bridge
  //

  Status = PrintRootBridgeDevPath (RBDev->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  //
  //get some valid memory resource controlled by this Root Bridge.
  //
  Status = GetSomeMemeryResource (
             RBDev,
             &ResourceBase,
             &ResourceLength
             );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes-not found valid memory resource.\n"
                   L"%a:%d.\n",
                   __FILE__,
                   (UINTN)__LINE__
                   );

    return EFI_SUCCESS;
  }
  if (ResourceLength > 0x1000) {
    ResourceLength = 0x1000;
  }


  //
  //call GetAttributes to get current supported attributes.
  //

  Status = RootBridgeIo->GetAttributes (
                           RootBridgeIo,
                           &SupportedAttributes,
                           NULL
                           );

  if (!EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  //
  //record assertion
  //
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.GetAttributes - Get Supported attribute status must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  //for each atributes call Setattributes.
  //
  AttributesNumber = 11;
  for (Index = 0; Index < AttributesNumber; Index ++) {

    ThisAttribute = AllAttributes[Index];
    //
    //first get current attributes before call SetAttributes.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CurrentAttributes
                    );

    //
    //call SetAttributes to set this attributes
    //
    Status = RootBridgeIo->SetAttributes (
                             RootBridgeIo,
                             ThisAttribute,
                             &ResourceBase,
                             &ResourceLength
                             );

    //
    //call get Attributes after SetAttributes () to get current attributes.
    //
    RootBridgeIo->GetAttributes (
                    RootBridgeIo,
                    NULL,
                    &CommonAttributes
                    );

    if ((ThisAttribute & SupportedAttributes)) {
      //
      //supported attributes
      //
      if (!EFI_ERROR(Status)) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciRootBridgeIoBBTestStressAssertionGuid031,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Supported attribute status must be EFI_SUCCESS",
                     L"%a:%d:Status - %r,Set Attributes -%LXh,Supported Attributes -%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );
      //
      //the attributes should be really set.
      //
      if (ThisAttribute & CommonAttributes) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciRootBridgeIoBBTestStressAssertionGuid032,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set Supported attribute the attributes should be really set.",
                     L"%a:%d:Attributes before Set -%LXh,Set Attributes -%LXh,Attributes after Set -%LXh,Supported Attributes -%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     CurrentAttributes,
                     ThisAttribute,
                     CommonAttributes,
                     SupportedAttributes
                     );

    } else {
      //
      //unsupported attributes
      //
      if (Status == EFI_UNSUPPORTED) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciRootBridgeIoBBTestStressAssertionGuid033,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set UnSupported attribute status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r,Set Attributes -%LXh,Supported Attributes -%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );
      //
      //the attributes should be remain unchanged.
      //
      if (CurrentAttributes == CommonAttributes) {
        AssertionType = EFI_TEST_ASSERTION_PASSED;
      } else {
        AssertionType = EFI_TEST_ASSERTION_FAILED;
      }

      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciRootBridgeIoBBTestStressAssertionGuid034,
                     L"EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL.SetAttributes - Set UnSupported attribute the attributes should remain unchanged",
                     L"%a:%d:Attributes before Set -%LXh,Set Attributes -%LXh,Attributes after Set -%LXh,Supported Attributes -%LXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     CurrentAttributes,
                     ThisAttribute,
                     CommonAttributes,
                     SupportedAttributes
                     );
    }
  }


  //
  //done successfully
  //
  return EFI_SUCCESS;
}

