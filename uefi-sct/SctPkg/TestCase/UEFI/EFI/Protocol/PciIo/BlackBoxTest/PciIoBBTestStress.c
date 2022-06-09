/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  PciIoBBTestStress.c

Abstract:

  stress test case source file for PciIo protocol

--*/

#include "SctLib.h"
#include "PciIoBBTestMain.h"
#include "PciIoBBTestSupport.h"

/**
 *  Entrypoint for PciIo->Attributes() stress test.
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
EFIAPI
Attributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_STATUS                            Status1;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINT64                                SupportedAttributes;
  UINT64                                CurrentAttributes;
  UINT64                                OriginalAttributes;
  UINT64                                CommonAttributes;
  UINTN                                 Index;
  UINTN                                 PciIoAttributesNumber;
  UINT64                                ThisAttribute;
  CHAR16                               *DevicePathStr;



  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }

  InitializeCaseEnvironment ();

  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }
  //
  //print the device path of pci device.
  //
//  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
//  if (EFI_ERROR(Status)) {
//    return Status;
//  }


  DevicePathStr = SctDevicePathToStr (PciIoDevice->DevicePath);
  if (DevicePathStr == NULL) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCannot get DevicePath"
                   );
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: %s",
                   DevicePathStr
                   );
    gtBS->FreePool (DevicePathStr);
  }
  //
  //call Attributes with operation EfiPciIoAttributeOperationGet to
  //get current attributes.
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &OriginalAttributes
           );

  //
  //call Attribtes with operation EfiPciIoAttributeOperationSupported to
  //get the supported attributes of the pci controller.
  //

  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationSupported,
           0,
           &SupportedAttributes
           );

  //
  //for each pci io attributes call Attributes with EfiPciIoAttributeOperationSet
  //
  PciIoAttributesNumber = 19;
  for (Index = 0; Index < PciIoAttributesNumber; Index++) {

    //
    //first get current attributes.
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CurrentAttributes
             );

    ThisAttribute = (UINT64) (1 << Index);

    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationSet,
                      ThisAttribute,
                      NULL
                      );

    //
    //get current attributes after Call Set
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CommonAttributes
             );

    //
    //call Attributes to set the orininal value before output to console
    //
    Status1 =  PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        OriginalAttributes,
                        NULL
                        );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestStressAssertionGuid017,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1
                     );
      return Status1;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if (ThisAttribute & SupportedAttributes) {
      if (!EFI_ERROR(Status) || (Status == EFI_UNSUPPORTED)) {
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
                     gPciIoBBTestStressAssertionGuid001,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set Supported attribute status must be EFI_SUCCESS or EFI_UNSUPPORTED.",
                     L"%a:%d:Status - %r, Set Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );

      if (!EFI_ERROR(Status)) {
        //
        //verify the attributes was really set.
        //
        if (CommonAttributes == ThisAttribute) {
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
                       gPciIoBBTestStressAssertionGuid002,
                       L"EFI_PCI_IO_PROTOCOL.Attributes - Supported attribute are really set",
                       L"%a:%d:Set Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                       __FILE__,
                       (UINTN)__LINE__,
                       ThisAttribute,
                       SupportedAttributes,
                       CurrentAttributes,
                       CommonAttributes
                       );
      }
    } else {
      //
      //unsupported attributes.
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
                     gPciIoBBTestStressAssertionGuid003,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set UnSupported attribute status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );

      //
      //verify the attributes remain unchanged
      //
      if (CommonAttributes == CurrentAttributes) {
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
                     gPciIoBBTestStressAssertionGuid004,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - set UnSupported attribute the Attributes can not been changed",
                     L"%a:%d:Set Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     ThisAttribute,
                     SupportedAttributes,
                     CurrentAttributes,
                     CommonAttributes
                     );

    }
  }

  //
  //call Attributes to set the orininal value
  //
  Status =  PciIo->Attributes (
                     PciIo,
                     EfiPciIoAttributeOperationSet,
                     OriginalAttributes,
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
                 gPciIoBBTestStressAssertionGuid005,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call get attributes to verify.
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &CommonAttributes
           );

  if (CommonAttributes == OriginalAttributes) {
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
                 gPciIoBBTestStressAssertionGuid006,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Attributes must be really set.",
                 L"%a:%d:Set attributes - %lXh, gotted attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 CommonAttributes
                 );

  //
  //for each pci io attributes call Attributes with EfiPciIoAttributeOperationDisable.
  //
  PciIoAttributesNumber = 19;
  for (Index = 0; Index < PciIoAttributesNumber; Index++) {
    //
    //first get current attributes.
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CurrentAttributes
             );

    ThisAttribute = (UINT64) (1 << Index);

    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationDisable,
                      ThisAttribute,
                      NULL
                      );
    //
    //get current attributes
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CommonAttributes
             );

    //
    //call Attributes to set the orininal value before output to console
    //
    Status1 =  PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        OriginalAttributes,
                        NULL
                        );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestStressAssertionGuid017,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1
                     );
      return Status;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {

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
                     gPciIoBBTestStressAssertionGuid007,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - disable Supported attribute status must be EFI_SUCCESS",
                     L"%a:%d:Status - %r, Disabled Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );

      //
      //verify the attributes really disabled
      //
      if ((ThisAttribute & CommonAttributes) != ThisAttribute) {
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
                     gPciIoBBTestStressAssertionGuid008,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - disable Supported attribute are really diabled",
                     L"%a:%d:Disable Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     ThisAttribute,
                     SupportedAttributes,
                     CurrentAttributes,
                     CommonAttributes
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
                     gPciIoBBTestStressAssertionGuid009,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - disable UnSupported attribute status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Disabled Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );

      //
      //verify the attributes remain unchanged after Disable operation
      //
      if (CommonAttributes == CurrentAttributes) {
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
                     gPciIoBBTestStressAssertionGuid010,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - disable UnSupported attribute the Attributes can not been changed",
                     L"%a:%d:Disable Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     ThisAttribute,
                     SupportedAttributes,
                     CurrentAttributes,
                     CommonAttributes
                     );

    }
  }

  //
  //call Attributes to set the orininal value
  //
  Status =  PciIo->Attributes (
                     PciIo,
                     EfiPciIoAttributeOperationSet,
                     OriginalAttributes,
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
                 gPciIoBBTestStressAssertionGuid011,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call get attributes to verify.
  //
  PciIo->Attributes (
           PciIo,
           EfiPciIoAttributeOperationGet,
           0,
           &CommonAttributes
           );

  if (CommonAttributes == OriginalAttributes) {
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
                 gPciIoBBTestStressAssertionGuid012,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Attributes must be really set.",
                 L"%a:%d:Set Attributes - %lXh, gotted attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 CommonAttributes
                 );

  //
  //for each pci io attributes call Attributes with EfiPciIoAttributeOperationEnable.
  //
  PciIoAttributesNumber = 19;
  for (Index = 1; Index <= PciIoAttributesNumber; Index++) {
    //
    //first get current attributes.
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CurrentAttributes
             );

    ThisAttribute = (UINT64) (1 << Index);

    Status = PciIo->Attributes (
                      PciIo,
                      EfiPciIoAttributeOperationEnable,
                      ThisAttribute,
                      &CommonAttributes
                      );
    //
    //get current attributes after Enable
    //
    PciIo->Attributes (
             PciIo,
             EfiPciIoAttributeOperationGet,
             0,
             &CommonAttributes
             );

    //
    //call Attributes to set the orininal value before output to console
    //
    Status1 =  PciIo->Attributes (
                        PciIo,
                        EfiPciIoAttributeOperationSet,
                        OriginalAttributes,
                        NULL
                        );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
      //
      //record assertion
      //
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gPciIoBBTestStressAssertionGuid017,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status1
                     );
      return Status1;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    if ((ThisAttribute & SupportedAttributes) == ThisAttribute) {
      if (!EFI_ERROR(Status) || (Status == EFI_UNSUPPORTED)) {
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
                     gPciIoBBTestStressAssertionGuid013,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - enable Supported attribute status must be EFI_SUCCESS or EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Enabled Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );

      if (!EFI_ERROR(Status)) {
        //
        //verify the attributes really enabled
        //
        if ((ThisAttribute & CommonAttributes) == ThisAttribute) {
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
                       gPciIoBBTestStressAssertionGuid014,
                       L"EFI_PCI_IO_PROTOCOL.Attributes - enable Supported attribute are really enabled",
                       L"%a:%d:Enable Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                       __FILE__,
                       (UINTN)__LINE__,
                       ThisAttribute,
                       SupportedAttributes,
                       CurrentAttributes,
                       CommonAttributes
                       );
      }
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
                     gPciIoBBTestStressAssertionGuid015,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - enable UnSupported attribute status must be EFI_UNSUPPORTED",
                     L"%a:%d:Status - %r, Enabled Attributes - %lXh, Supported Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     ThisAttribute,
                     SupportedAttributes
                     );

      //
      //verify the attributes remain unchanged
      //
      if (CommonAttributes == CurrentAttributes) {
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
                     gPciIoBBTestStressAssertionGuid016,
                     L"EFI_PCI_IO_PROTOCOL.Attributes - enable UnSupported attribute the Attributes can not been changed",
                     L"%a:%d:Enalbe Attributes - %lXh, Supported Attributes - %lXh, Original Attribute - %lXh, Current Attributes - %lXh",
                     __FILE__,
                     (UINTN)__LINE__,
                     ThisAttribute,
                     SupportedAttributes,
                     CurrentAttributes,
                     CommonAttributes
                     );

    }
  }

  //
  //call Attributes to set the orininal value
  //
  Status =  PciIo->Attributes (
                     PciIo,
                     EfiPciIoAttributeOperationSet,
                     OriginalAttributes,
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
                 gPciIoBBTestStressAssertionGuid017,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Status Must be EFI_SUCCESS",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );
  //
  //call get attributes to verify.
  //
  Status =  PciIo->Attributes (
                     PciIo,
                     EfiPciIoAttributeOperationGet,
                     0,
                     &CommonAttributes
                     );

  if (CommonAttributes == OriginalAttributes) {
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
                 gPciIoBBTestStressAssertionGuid018,
                 L"EFI_PCI_IO_PROTOCOL.Attributes - Set Original Supported attribute the Attributes must be really set.",
                 L"%a:%d:Set Attributes - %lXh, gotted attributes - %lXh",
                 __FILE__,
                 (UINTN)__LINE__,
                 OriginalAttributes,
                 CommonAttributes
                 );

  //
  //done successfully
  //
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for PciIo->GetBarAttributes() and PciIo->SetBarAttributes()
 *  stress Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
//TDS 4.3.2
//
EFI_STATUS
EFIAPI
GetAndSetBarAttributes_Stress (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STATUS                            Status;
  PCI_IO_PROTOCOL_DEVICE                *PciIoDevice;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL    *StandardLib;
  EFI_TEST_ASSERTION                    AssertionType;
  UINTN                                 Index;
  UINTN                                 SubIndex;
  UINT8                                 BarIndex;
  UINT64                                DevSupportedAttributes;
  UINT64                                BarOriginalAttributes;
  UINT64                                AddressOffset;
  UINT64                                AddressLength;
  VOID                                  *Resources;
  UINTN                                 PciIoAttributesNumber;
  UINT64                                ThisAttribute;


  //
  //get tested interface.
  //
  PciIo = (EFI_PCI_IO_PROTOCOL *)ClientInterface;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    return Status;
  }
  //
  //get PciIoDevice struct pointer.
  //
  PciIoDevice = NULL;
  PciIoDevice = GetPciIoDevice (PciIo);
  if (PciIoDevice == NULL) {
    return EFI_ABORTED;
  }

  InitializeCaseEnvironment ();

  //
  //print the device path of pci device.
  //
  Status = PrintPciIoDevice (PciIoDevice->DevicePath);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  Status = PciIo->Attributes (
                    PciIo,
                    EfiPciIoAttributeOperationSupported,
                    0,
                    &DevSupportedAttributes
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
                 L"EFI_PCI_IO_PROTOCOL.Attributes - return status must be EFI_SUCCESS.",
                 L"%a:%d:Status - %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  for (Index = 0; Index < REGNUM; Index++) {

    BarIndex = (UINT8)Index;
    Resources = 0;
    Status = PciIo->GetBarAttributes (
                      PciIo,
                      BarIndex,
                      &BarOriginalAttributes,
                      &Resources
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
                   gPciIoBBTestStressAssertionGuid019,
                   L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - return status must be EFI_SUCCESS.",
                   L"%a:%d:Status - %r, BarIndex - %d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   BarIndex
                   );

    if (IsValidResourceDescrptor (Resources)) {
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
                   gPciIoBBTestStressAssertionGuid020,
                   L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - the Resource Descriptor List must be valid",
                   L"%a:%d",
                   __FILE__,
                   (UINTN)__LINE__
                   );
    //
    //free the resources if necessory.
    //
    if (Status == EFI_SUCCESS) {
      gtBS->FreePool (Resources);
    }

    //
    //the attribute supported by this bar must be in the device supported attributes range.
    //
    if ((BarOriginalAttributes & DevSupportedAttributes) == BarOriginalAttributes) {
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
                   gPciIoBBTestStressAssertionGuid021,
                   L"EFI_PCI_IO_PROTOCOL.GetBarAttributes - Bar supported attributes must in the range of Device supported attributes",
                   L"%a:%d:Bar Supported - %lXh, Dev Supported - %lXh",
                   __FILE__,
                   (UINTN)__LINE__,
                   BarOriginalAttributes,
                   DevSupportedAttributes
                   );
    //
    //Invalid bar then continue;
    //
    if (!PciIoDevice->BarHasEffect[BarIndex]) {
      continue;
    }

    AddressOffset = 0;
    AddressLength = PciIoDevice->BarLength[BarIndex];
    PciIoAttributesNumber = 19;

    //
    //for each attributes call SetBarAttributes
    //
    for (SubIndex = 0; SubIndex < PciIoAttributesNumber; SubIndex++) {

      ThisAttribute = (UINT64) (1 << SubIndex);

      Status = PciIo->SetBarAttributes (
                        PciIo,
                        ThisAttribute,
                        BarIndex,
                        &AddressOffset,
                        &AddressLength
                        );

      if ((ThisAttribute & BarOriginalAttributes) == ThisAttribute) {

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
                       gPciIoBBTestStressAssertionGuid022,
                       L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - Set Bar supported attributes return Staus Must be EFI_SUCCESS",
                       L"%a:%d:Set Attribute - %lXh, Supported Attributes - %lXh",
                       __FILE__,
                       (UINTN)__LINE__,
                       ThisAttribute,
                       BarOriginalAttributes
                       );

      } else {
        //
        //Unsupported attributes
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
                       gPciIoBBTestStressAssertionGuid023,
                       L"EFI_PCI_IO_PROTOCOL.SetBarAttributes - Set Unsupported attributes status must be EFI_UNSUPPORTED.",
                       L"%a:%d:Set Attribute - %lXh, Supported Attributes - %lXh",
                       __FILE__,
                       (UINTN)__LINE__,
                       ThisAttribute,
                       BarOriginalAttributes
                       );

      }
    }
  }

  //
  //done successfully
  //
  return EFI_SUCCESS;
}
