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

  DevicePathUtilitiesProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_UTILITIES_PROTOCOL_H_
#define _DEVICE_PATH_UTILITIES_PROTOCOL_H_

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID \
  { \
    0x379be4e, 0xd706, 0x437d, 0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4 \
  }

typedef EFI_DEVICE_PATH_PROTOCOL  EFI_DEVICE_PATH;

typedef
UINTN
(EFIAPI *EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE) (
  IN CONST EFI_DEVICE_PATH* DevicePath
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH) (IN CONST EFI_DEVICE_PATH *DevicePath);

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_PATH)
  (
    IN CONST EFI_DEVICE_PATH *Src1,
    IN CONST EFI_DEVICE_PATH *Src2
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_NODE)
  (
    IN CONST EFI_DEVICE_PATH *DevicePath,
    IN CONST EFI_DEVICE_PATH *DeviceNode
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE)
  (
    IN CONST EFI_DEVICE_PATH *DevicePath,
    IN CONST EFI_DEVICE_PATH *DevicePathInstance
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE)
  (
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePathInstance,
    OUT UINTN *DevicePathInstanceSize
  );

typedef EFI_DEVICE_PATH * (EFIAPI *EFI_DEVICE_PATH_UTILS_CREATE_NODE)
  (
    IN UINT8 NodeType,
    IN UINT8 NodeSubType,
    IN UINT16 NodeLength
  );

typedef
BOOLEAN
(EFIAPI *EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE) (
  IN CONST EFI_DEVICE_PATH* DevicePath
  );

typedef struct _EFI_DEVICE_PATH_UTILITIES_PROTOCOL {
  EFI_DEVICE_PATH_UTILS_GET_DEVICE_PATH_SIZE  GetDevicePathSize;
  EFI_DEVICE_PATH_UTILS_DUP_DEVICE_PATH       DuplicateDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_PATH           AppendDevicePath;
  EFI_DEVICE_PATH_UTILS_APPEND_NODE           AppendDeviceNode;
  EFI_DEVICE_PATH_UTILS_APPEND_INSTANCE       AppendDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_GET_NEXT_INSTANCE     GetNextDevicePathInstance;
  EFI_DEVICE_PATH_UTILS_IS_MULTI_INSTANCE     IsDevicePathMultiInstance;
  EFI_DEVICE_PATH_UTILS_CREATE_NODE           CreateDeviceNode;
} EFI_DEVICE_PATH_UTILITIES_PROTOCOL;

#endif
