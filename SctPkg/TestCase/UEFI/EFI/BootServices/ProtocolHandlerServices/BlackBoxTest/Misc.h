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

  Misc.h

Abstract:

  Include for Misc.h

--*/

#ifndef _PROTOCOL_HANDLER_MISC_H
#define _PROTOCOL_HANDLER_MISC_H

#include "ProtocolHandlerBBTest.h"
#include "ProtocolDefinition.h"

typedef struct {
  VOID          *Registration;
  EFI_STATUS    Status;
  UINTN         NoHandles;
} NOTIFY_CONTEXT_2;

VOID
InitializeTestProtocol1 (
  OUT TEST_PROTOCOL_1     *TestProtocol1
  );

EFI_STATUS
TestProtocol1Func1(
  IN TEST_PROTOCOL_1   *This
);

VOID
InitializeTestProtocol2 (
  OUT TEST_PROTOCOL_2     *TestProtocol2
  );

EFI_STATUS
TestProtocol2Func1(
  IN TEST_PROTOCOL_2   *This
  );

VOID
Protocol1ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_1   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol1 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_1     *InterfaceFunctionTestProtocol1
  );

VOID
Protocol2ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_2   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol2 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_2     *InterfaceFunctionTestProtocol2
  );

VOID
Protocol3ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_3   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol3 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_3     *InterfaceFunctionTestProtocol3
  );

VOID
Protocol4ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_4   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol4 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_4     *InterfaceFunctionTestProtocol4
  );

VOID
Protocol5ReportProtocolAttributes(
  IN INTERFACE_FUNCTION_TEST_PROTOCOL_5   *This,
  OUT PROTOCOL_ATTRIBUTES   *ProtocolAttributes
  );

VOID
InitializeInterfaceFunctionTestProtocol5 (
  OUT INTERFACE_FUNCTION_TEST_PROTOCOL_5     *InterfaceFunctionTestProtocol5
  );

VOID
CreateInvalidHandle (
  OUT EFI_HANDLE  *InvalidHandle
  );

VOID
ReleaseInvalidHandle (
  IN EFI_HANDLE    InvalidHandle
  );

VOID
CreateVendorDevicePath (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
CreateVendorDevicePathNode (
  OUT EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN  EFI_GUID                  Guid
  );

VOID
FreeVendorDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

VOID
FreeVendorDevicePathNode (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePathNode
  );

VOID
TestNotifyFunction0 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

VOID
TestNotifyFunction1 (
  IN     EFI_EVENT Event,
  IN OUT VOID      *Context
  );

VOID
TestNotifyFunction2 (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

BOOLEAN
IsNodeInDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *Node,
  IN EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  );

EFI_STATUS
LoadStartImage (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_HANDLE                          CurrentImageHandle,
  IN CHAR16                              *FileName,
  IN EFI_HANDLE                          *StartImage
  );

EFI_STATUS
GetPlatformOverrideDriverImages (
  IN  EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN  EFI_HANDLE                          CurrentImageHandle,
  IN  EFI_HANDLE                          ControllerHandle,
  OUT EFI_HANDLE                          **ImageHandleBuffer,
  OUT UINTN                               *HandleNo
 );

EFI_STATUS
AliasLocateHandleBuffer (
  IN EFI_GUID  *Guid
  );

EFI_STATUS
CheckForCleanEnvironment (
  OUT UINTN                               *Numbers
  );
#endif
