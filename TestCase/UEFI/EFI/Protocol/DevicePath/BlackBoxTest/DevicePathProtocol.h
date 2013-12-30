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
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  DevicePathProtocol.h

Abstract:

--*/

#ifndef _DEVICE_PATH_FOR_TEST_H_
#define _DEVICE_PATH_FOR_TEST_H_

//
// Device Path protocol
//
#ifndef EFI_DEVICE_PATH_PROTOCOL_GUID
#define EFI_DEVICE_PATH_PROTOCOL_GUID \
  { \
    0x9576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b \
  }
#endif

//#ifndef EFI_END_ENTIRE_DEVICE_PATH
//#define EFI_END_ENTIRE_DEVICE_PATH  0xff
//#endif

#ifndef EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE
#define EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE  0xff
#endif

#ifndef EFI_END_INSTANCE_DEVICE_PATH
#define EFI_END_INSTANCE_DEVICE_PATH  0x01
#endif

#ifndef EFI_END_DEVICE_PATH_LENGTH
#define EFI_END_DEVICE_PATH_LENGTH  (sizeof (EFI_DEVICE_PATH_PROTOCOL))
#endif

#ifndef EfiDevicePathNodeLength
#define EfiDevicePathNodeLength(a)  (((a)->Length[0]) | ((a)->Length[1] << 8))
#endif

#ifndef EfiNextDevicePathNode
#define EfiNextDevicePathNode(a)  ((EFI_DEVICE_PATH_PROTOCOL *) (((UINT8 *) (a)) + EfiDevicePathNodeLength (a)))
#endif

#ifndef EfiDevicePathType
#define EfiDevicePathType(a)  (((a)->Type) & 0x7f)
#endif

#ifndef EfiDevicePathSubType
#define EfiDevicePathSubType(a) ((a)->SubType)
#endif

#ifndef EfiIsDevicePathEndType
#define EfiIsDevicePathEndType(a) (EfiDevicePathType (a) == 0x7f)
#endif

#ifndef EfiIsDevicePathEndSubType
#define EfiIsDevicePathEndSubType(a)  ((a)->SubType == EFI_END_ENTIRE_DEVICE_PATH_SUBTYPE)
#endif

#ifndef EfiIsDevicePathEndInstanceSubType
#define EfiIsDevicePathEndInstanceSubType(a)  ((a)->SubType == EFI_END_INSTANCE_DEVICE_PATH)
#endif

#ifndef EfiIsDevicePathEnd
#define EfiIsDevicePathEnd(a) (EfiIsDevicePathEndType (a) && EfiIsDevicePathEndSubType (a))
#endif

#ifndef EfiIsDevicePathEndInstance
#define EfiIsDevicePathEndInstance(a) (EfiIsDevicePathEndType (a) && EfiIsDevicePathEndInstanceSubType (a))
#endif

///
/// VLAN Device Path SubType
///
#define MSG_VLAN_DP               0x14
#ifndef EFIARM
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  ///
  /// VLAN identifier (0-4094)
  ///
  UINT16                          VlanId;
} VLAN_DEVICE_PATH;
#endif


#define MSG_IPV6_DP               0x0d
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  EFI_IPv6_ADDRESS                LocalIpAddress;
  EFI_IPv6_ADDRESS                RemoteIpAddress;
  UINT16                          LocalPort;
  UINT16                          RemotePort;
  UINT16                          Protocol;
  UINT8                           IPAddressOrigin;
  UINT8                           PrefixLength;
  EFI_IPv6_ADDRESS                GatewayIPAddress;
} IPV6_DEVICE_PATH;

#define MSG_IPV4_DP               0x0c
typedef struct {
  EFI_DEVICE_PATH_PROTOCOL        Header;
  EFI_IPv4_ADDRESS                LocalIpAddress;
  EFI_IPv4_ADDRESS                RemoteIpAddress;
  UINT16                          LocalPort;
  UINT16                          RemotePort;
  UINT16                          Protocol;
  BOOLEAN                         StaticIpAddress;
  EFI_IPv4_ADDRESS                GatewayIPAddress;
  EFI_IPv4_ADDRESS                SubnetMask;
} IPV4_DEVICE_PATH;

extern EFI_GUID gEfiDevicePathProtocolGuid;

#endif /* _DEVICE_PATH_FOR_TEST_H_ */
