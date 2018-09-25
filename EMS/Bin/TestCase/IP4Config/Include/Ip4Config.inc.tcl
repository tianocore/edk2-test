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
if {[info exist IP4CONFIG_INC] == 1} {
  return
}
set IP4CONFIG_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include IP4Config/Include/Ip4ConfigAssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

Include IP4/Include/Ip4.inc.tcl

###################################################################
# Function Declaration
###################################################################
Func Ip4Config->Start {
  UINTN
  UINTN
  POINTER
}

Func Ip4Config->Stop {
  POINTER
  }

Func Ip4Config->GetData {
  POINTER
  POINTER
  POINTER
  }

#**********************************************
# EFI_IP4_IPCONFIG_DATA 
#**********************************************
Struct EFI_IP4_IPCONFIG_DATA {
  EFI_IPv4_ADDRESS        StationAddress;
  EFI_IPv4_ADDRESS        SubnetMask;
  UINT32                  RouteTableSize;
  POINTER                 RouteTable;
}
