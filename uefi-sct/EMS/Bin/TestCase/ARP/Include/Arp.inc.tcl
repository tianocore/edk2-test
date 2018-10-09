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
if {[info exist ARP_INC] == 1} {
  return
}
set ARP_INC 1

Include include/GenericAssertionGuid.tcl
Include EfiUtil/EfiInclude.tcl
Include include/EntsProtocolTest.inc.tcl
Include include/EfiBootService.inc.tcl
Include ARP/include/ArpAssertionGuid.tcl

Func ArpServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func ArpServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Arp->Configure {
  POINTER
  POINTER
}

Func Arp->Add {
  BOOLEAN
  POINTER
  POINTER
  UINTN
  BOOLEAN
  POINTER
  }

Func Arp->Find {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  POINTER
  BOOLEAN
  POINTER
  }

Func Arp->Delete {
  BOOLEAN
  POINTER
  POINTER
  }

Func Arp->Flush {
  POINTER
  }

Func Arp->Request {
  POINTER
  UINTN
  POINTER
  POINTER
  }

Func Arp->Cancel {
  POINTER
  UINTN
  POINTER
  }

#*************************************************
# EFI_ARP_CONFIG_DATA
#*************************************************
Struct EFI_ARP_CONFIG_DATA {
  UINT16                    SwAddressType;
  UINT8                     SwAddressLength;
  POINTER                   StationAddress;
  UINT32                    EntryTimeOut;
  UINT32                    RetryCount;
  UINT32                    RetryTimeOut;
}

#*************************************************
# EFI_ARP_FIND_DATA
#*************************************************
Struct EFI_ARP_FIND_DATA {
  UINT32               Size;
  BOOLEAN              DenyFlag;
  BOOLEAN              StaticFlag;
  UINT16               HwAddressType;
  UINT16               SwAddressType;
  UINT8                HwAddressLength;
  UINT8                SwAddressLength;
}

