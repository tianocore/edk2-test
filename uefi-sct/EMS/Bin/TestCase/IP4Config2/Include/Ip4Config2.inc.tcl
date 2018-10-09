# 
#  Copyright 2017 Unified EFI, Inc.<BR> 
#  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist IP4CONFIG2_INC] == 1} {
  return
}
set IP4CONFIG2_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl

Include IP4/Include/Ip4.inc.tcl
Include IP4Config2/Include/Ip4Config2Define.tcl
Include IP4Config2/Include/Ip4Config2.proc.tcl
Include IP4Config2/Include/Ip4Config2AssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

###################################################################
# Function Declaration
###################################################################
Func Ip4Config2->SetData {
    UINT32
    UINTN
    POINTER
    POINTER
}

Func Ip4Config2->GetData {
    UINT32
    POINTER
    POINTER
    POINTER
}

Func Ip4Config2->RegisterDataNotify {
    UINT32
    UINTN
    POINTER
}

Func Ip4Config2->UnregisterDataNotify {
    UINT32
    UINTN
    POINTER
}

###################################################################
# EFI_IP4_CONFIG2_INTERFACE_INFO
###################################################################
Struct EFI_IP4_CONFIG2_INTERFACE_INFO {
  CHAR16                Name(32);
  UINT8                 IfType;
  UINT32                HwAddressSize;
  EFI_MAC_ADDRESS       HwAddress;
  EFI_IPv4_ADDRESS      StationAddress;
  EFI_IPv4_ADDRESS      SubnetMask;
  UINT32                RouteTableSize;
  POINTER               RouteTable;
}

###################################################################
# EFI_IP4_CONFIG2_MANUAL_ADDRESS
###################################################################
Struct EFI_IP4_CONFIG2_MANUAL_ADDRESS {
  EFI_IPv4_ADDRESS      Address;
  EFI_IPv4_ADDRESS      SubnetMask;
}

