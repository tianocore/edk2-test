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

  DevicePathUtilitiesBBTestFunction.c

Abstract:

  Interface Function Test Cases of Device Path Utilities Protocol

--*/

#include "SctLib.h"
#include "DevicePathUtilitiesBBTestMain.h"

#define PCINodeType         1
#define PCINodeSubType      1
#define PCINodeLength       6

#define PCIRootNodeType     2
#define PCIRootNodeSubType  1
#define PCIRootNodeLength   12

#define USBNodeType         3
#define USBNodeSubType      5
#define USBNodeLength       6

#define InvalidNodeLength   3

//
// TDS 3.3.1
//
EFI_STATUS
DevicePathUtilitiesCreateDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.1.2.1
  //
  pDevicePath = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  if ((SctDevicePathType (pDevicePath) == PCINodeType) &&
      (SctDevicePathSubType (pDevicePath) == PCINodeSubType) &&
      (SctDevicePathNodeLength (pDevicePath) == PCINodeLength)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid051,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - CreatDeviceNode must correctly set Type, SubType and Length in the return EFI_DEVICE_PATH structure",
                L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                __FILE__,
                (UINTN)__LINE__,
                SctDevicePathType (pDevicePath),
                SctDevicePathSubType (pDevicePath),
                SctDevicePathNodeLength (pDevicePath)
                );
  //
  // TDS 3.3.1.2.2
  //
  pDevicePath = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  if ((SctDevicePathType (pDevicePath) == PCIRootNodeType) &&
      (SctDevicePathSubType (pDevicePath) == PCIRootNodeSubType) &&
      (SctDevicePathNodeLength (pDevicePath) == PCIRootNodeLength)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath);

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid066,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - CreatDeviceNode must correctly set Type, SubType and Length in the return EFI_DEVICE_PATH structure",
                L"%a:%d:Type - %d, Subtype - %d, Length - %d",
                __FILE__,
                (UINTN)__LINE__,
                SctDevicePathType (pDevicePath),
                SctDevicePathSubType (pDevicePath),
                SctDevicePathNodeLength (pDevicePath)
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.2
//
EFI_STATUS
DevicePathUtilitiesAppendDeviceNodeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.2.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  if ((SctDevicePathType (pDevicePath3) == PCIRootNodeType) &&
      (SctDevicePathSubType (pDevicePath3) == PCIRootNodeSubType) &&
      (SctDevicePathNodeLength (pDevicePath3) == PCIRootNodeLength)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid053,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDeviceNode called by the end-of-device-path node must correctly set Type, SubType and Length in the first device path node in the return EFI_DEVICE_PATH structure",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );
  //
  // TDS 3.3.2.2.2
  //
  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath1  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath2);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath2);
  if ((SctDevicePathType (SctNextDevicePathNode (pDevicePath1)) == PCINodeType) &&
      (SctDevicePathSubType (SctNextDevicePathNode (pDevicePath1)) == PCINodeSubType) &&
      (SctDevicePathNodeLength (SctNextDevicePathNode (pDevicePath1)) == PCINodeLength)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath1);
  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid067,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDeviceNode must correctly set Type, SubType and Length in the last but the end-of-device-path node in the return EFI_DEVICE_PATH structure",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.3
//
EFI_STATUS
DevicePathUtilitiesGetDevicePathSizeFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.3.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  pDevicePath2    = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath3    = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  DevicePathLen2  = DevicePathUtilities->GetDevicePathSize (pDevicePath3);
  if ((DevicePathLen1 == (UINTN) 4) &&
      ((DevicePathLen2 - DevicePathLen1) == (UINTN) (SctDevicePathNodeLength (pDevicePath2)))
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath3);
  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid056,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - GetDevicePathSize() should return the correct value and the return value should increase correctly after AppendDeviceNode called",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.4
//
EFI_STATUS
DevicePathUtilitiesDuplicateDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.4.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  pDevicePath2    = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3    = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath2);
  pDevicePath1    = DevicePathUtilities->DuplicateDevicePath (pDevicePath2);
  DevicePathLen2  = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  if ((DevicePathLen1 == DevicePathLen2) && (SctCompareMem (pDevicePath1, pDevicePath2, DevicePathLen1) == 0)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid057,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - DupilicateDevicePath must correctly set the return EFI_DEVICE_PATH structure the same as the original one",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );
  return EFI_SUCCESS;
}
//
// TDS 3.3.5
//
EFI_STATUS
DevicePathUtilitiesAppendDevicePathFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  UINTN                               DevicePathLen3;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.5.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  pDevicePath2    = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3    = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen1  = DevicePathUtilities->GetDevicePathSize (pDevicePath2);

  pDevicePath1    = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath3  = DevicePathUtilities->CreateDeviceNode (USBNodeType, USBNodeSubType, USBNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath3);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath3);
  DevicePathLen2  = DevicePathUtilities->GetDevicePathSize (pDevicePath4);

  pDevicePath1    = DevicePathUtilities->AppendDevicePath (pDevicePath2, pDevicePath4);
  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath4);
  DevicePathLen3 = DevicePathUtilities->GetDevicePathSize (pDevicePath1);
  SctFreePool (pDevicePath1);
  if (DevicePathLen3 == DevicePathLen1 + DevicePathLen2 - END_DEVICE_PATH_LENGTH) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid058,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - SctAppendDevicePath must correctly set the return EFI_DEVICE_PATH structure as the new device path that appends the second device path to the first",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.6
//
EFI_STATUS
DevicePathUtilitiesAppendDevicePathInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  UINTN                               DevicePathInstanceSize;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.6.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath3  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath3);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath3);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath4, pDevicePath1);
  SctFreePool (pDevicePath4);
  SctFreePool (pDevicePath1);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (USBNodeType, USBNodeSubType, USBNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);

  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen1 = DevicePathUtilities->GetDevicePathSize (pDevicePath2);
  //
  // (SctNextDevicePathNode(SctNextDevicePathNode(pDevicePath2)))->SubType = END_INSTANCE_DEVICE_PATH_SUBTYPE;
  //
  pDevicePath1  = DevicePathUtilities->AppendDevicePathInstance (pDevicePath4, pDevicePath2);
  pDevicePath3  = pDevicePath1;
  SctFreePool (pDevicePath4);
  pDevicePath4 = DevicePathUtilities->GetNextDevicePathInstance (&pDevicePath1, &DevicePathInstanceSize);
  SctFreePool (pDevicePath4);
  DevicePathLen2 = DevicePathUtilities->GetDevicePathSize (pDevicePath1);

  if ((DevicePathLen1 == DevicePathLen2) &&
      (SctCompareMem (pDevicePath1, pDevicePath2, DevicePathLen1 /*-END_DEVICE_PATH_LENGTH*/ ) == 0)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath3);
  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid061,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - AppendDevicePathInstance must correctly set the return EFI_DEVICE_PATH structure as the new device path that appends the specific device path instance to the specific device path",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.7
//
EFI_STATUS
DevicePathUtilitiesGetNextDevicePathInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;
  UINTN                               DevicePathLen1;
  UINTN                               DevicePathLen2;
  UINTN                               DevicePathLen3;
  UINTN                               DevicePathInstanceSize;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.7.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath3  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath3);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath3);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath4, pDevicePath1);
  SctFreePool (pDevicePath4);
  SctFreePool (pDevicePath1);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (USBNodeType, USBNodeSubType, USBNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen3  = DevicePathUtilities->GetDevicePathSize (pDevicePath4);

  pDevicePath1    = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  DevicePathLen1 = DevicePathUtilities->GetDevicePathSize (pDevicePath2);
  //
  // (SctNextDevicePathNode(SctNextDevicePathNode(pDevicePath2)))->SubType = END_INSTANCE_DEVICE_PATH_SUBTYPE;
  //
  pDevicePath1  = DevicePathUtilities->AppendDevicePathInstance (pDevicePath4, pDevicePath2);
  pDevicePath3  = pDevicePath1;
  SctFreePool (pDevicePath4);
  pDevicePath4 = DevicePathUtilities->GetNextDevicePathInstance (&pDevicePath1, &DevicePathInstanceSize);
  SctFreePool (pDevicePath4);
  DevicePathLen2 = DevicePathUtilities->GetDevicePathSize (pDevicePath1);

  if ((DevicePathLen1 == DevicePathLen2) &&
      (SctCompareMem (pDevicePath1, pDevicePath2, DevicePathLen1 /*-END_DEVICE_PATH_LENGTH*/ ) == 0) &&
      (DevicePathInstanceSize == DevicePathLen3)
      ) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  SctFreePool (pDevicePath2);
  SctFreePool (pDevicePath3);
  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid063,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - GetNextDevicePathInstance must correctly get the next device path instance and return a pointer to the copy of the current device path instance",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
//
// TDS 3.3.8
//
EFI_STATUS
DevicePathUtilitiesIsDevicePathMultiInstanceFunctionTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib;
  EFI_STATUS                          Status;
  EFI_DEVICE_PATH_UTILITIES_PROTOCOL  *DevicePathUtilities;
  EFI_TEST_ASSERTION                  AssertionType;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath1;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath2;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath3;
  EFI_DEVICE_PATH_PROTOCOL            *pDevicePath4;
  BOOLEAN                             MultiInstance1;
  BOOLEAN                             MultiInstance2;
  BOOLEAN                             MultiInstance3;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                  SupportHandle,
                  &gEfiStandardTestLibraryGuid,
                  &StandardLib
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  DevicePathUtilities = (EFI_DEVICE_PATH_UTILITIES_PROTOCOL *) ClientInterface;

  //
  // TDS 3.3.8.2.1
  //
  pDevicePath1 = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  MultiInstance1  = DevicePathUtilities->IsDevicePathMultiInstance (pDevicePath1);

  pDevicePath3    = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath4    = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath3);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath3);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath4, pDevicePath1);
  SctFreePool (pDevicePath4);
  SctFreePool (pDevicePath1);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (USBNodeType, USBNodeSubType, USBNodeLength);
  pDevicePath4  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  MultiInstance2  = DevicePathUtilities->IsDevicePathMultiInstance (pDevicePath4);

  pDevicePath1    = (EFI_DEVICE_PATH *) SctAllocatePool (END_DEVICE_PATH_LENGTH);
  if (pDevicePath1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  SctSetDevicePathEndNode (pDevicePath1);
  pDevicePath2  = DevicePathUtilities->CreateDeviceNode (PCIRootNodeType, PCIRootNodeSubType, PCIRootNodeLength);
  pDevicePath3  = DevicePathUtilities->AppendDeviceNode (pDevicePath1, pDevicePath2);
  SctFreePool (pDevicePath1);
  SctFreePool (pDevicePath2);
  pDevicePath1  = DevicePathUtilities->CreateDeviceNode (PCINodeType, PCINodeSubType, PCINodeLength);
  pDevicePath2  = DevicePathUtilities->AppendDeviceNode (pDevicePath3, pDevicePath1);
  SctFreePool (pDevicePath3);
  SctFreePool (pDevicePath1);
  //
  // (SctNextDevicePathNode(SctNextDevicePathNode(pDevicePath2)))->SubType = END_INSTANCE_DEVICE_PATH_SUBTYPE;
  //
  pDevicePath1 = DevicePathUtilities->AppendDevicePathInstance (pDevicePath4, pDevicePath2);
  SctFreePool (pDevicePath4);
  SctFreePool (pDevicePath2);
  MultiInstance3 = DevicePathUtilities->IsDevicePathMultiInstance (pDevicePath1);
  SctFreePool (pDevicePath1);

  if ((MultiInstance1 == FALSE) && (MultiInstance2 == FALSE) && (MultiInstance3 == TRUE)) {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  }

  Status = EFI_SUCCESS;

  StandardLib->RecordAssertion (
                StandardLib,
                AssertionType,
                gDevicePathUtilitiesBBTestFunctionAssertionGuid065,
                L"EFI_DEVICE_PATH_UTILITIES_PROTOCOL - IsDevicePathMultiInstance must correctly judge whether a device path is multi-instance",
                L"%a:%d:Status - %r",
                __FILE__,
                (UINTN)__LINE__,
                Status
                );

  return EFI_SUCCESS;
}
