# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist IP6CONFIG_INC] == 1} {
  return
}
set IP6CONFIG_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl

Include IP6/Include/Ip6.inc.tcl
Include IP6Config/Include/Ip6ConfigDefine.tcl
Include IP6Config/Include/Ip6Config.proc.tcl
Include IP6Config/Include/Ip6ConfigAssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

###################################################################
# Function Declaration
###################################################################
Func Ip6Config->SetData {
    UINT32
    UINTN
    POINTER
    POINTER
}

Func Ip6Config->GetData {
    UINT32
    POINTER
    POINTER
    POINTER
}

Func Ip6Config->RegisterDataNotify {
    UINT32
    UINTN
    POINTER
}

Func Ip6Config->UnregisterDataNotify {
    UINT32
    UINTN
    POINTER
}


###################################################################
# EFI_IP6_CONFIG_INTERFACE_INFO
###################################################################
Struct EFI_IP6_CONFIG_INTERFACE_INFO {
  CHAR16                Name(32);
  UINT8                 IfType;
  UINT32                HwAddressSize;
  EFI_MAC_ADDRESS       HwAddress;
  UINT32                AddressInfoCount;
  POINTER               AddressInfo;
  UINT32                RouteCount;
  POINTER               RouteTable;
}

###################################################################
# EFI_IP6_CONFIG_INTERFACE_ID
###################################################################
Struct EFI_IP6_CONFIG_INTERFACE_ID {
  UINT8                 Id(8);
}

###################################################################
# EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS
###################################################################
Struct EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS {
  UINT32                DupAddrDetectTransmits;
}

###################################################################
# EFI_IP6_CONFIG_MANUAL_ADDRESS
###################################################################
Struct EFI_IP6_CONFIG_MANUAL_ADDRESS {
  EFI_IPv6_ADDRESS      Address;
  BOOLEAN               IsAnycast;
  UINT8                 PrefixLength;
}

