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
if {[info exist IP6_INC] == 1} {
  return
}
set IP6_INC 1

Include EfiUtil/EfiInclude.tcl
Include Include/EntsProtocolTest.inc.tcl
Include Include/EfiBootService.inc.tcl
Include MNP/Include/Mnp.inc.tcl
Include SNP/Include/Snp.inc.tcl
Include IP6/Include/Ip6Define.tcl
Include IP6Config/Include/Ip6Config.inc.tcl

Include Include/GenericAssertionGuid.tcl
Include IP6/Include/Ip6AssertionGuid.tcl


###################################################################
# Function Declaration
###################################################################
Func Ip6ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Ip6ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Ip6->GetModeData {
  POINTER
  POINTER
  POINTER
  POINTER
}

Func Ip6->Configure {
  POINTER
  POINTER
}

Func Ip6->Groups {
  BOOLEAN
  POINTER
  POINTER
}

Func Ip6->Routes {
  BOOLEAN
  POINTER
  UINT8
  POINTER
  POINTER
}

Func Ip6->Neighbors {
  BOOLEAN
  POINTER
  POINTER
  UINT32
  BOOLEAN
  POINTER
}

Func Ip6->Transmit {
  POINTER
  POINTER
}

Func Ip6->Receive {
  POINTER
  POINTER
}

Func Ip6->Cancel {
  POINTER
  POINTER
}

Func Ip6->Poll {
  POINTER
}

#**********************************************
# EFI_IP6_CONFIG_DATA 
#**********************************************
Struct EFI_IP6_CONFIG_DATA {
  UINT8              DefaultProtocol;
  BOOLEAN            AcceptAnyProtocol;
  BOOLEAN            AcceptIcmpErrors;
  BOOLEAN            AcceptPromiscuous;
  EFI_IPv6_ADDRESS   DestinationAddress;
  EFI_IPv6_ADDRESS   StationAddress;
  UINT8              TrafficClass;
  UINT8              HopLimit;
  UINT32             FlowLabel;
  UINT32             ReceiveTimeout;
  UINT32             TransmitTimeout;
}

#**********************************************
# EFI_IP6_ADDRESS_INFO
#**********************************************
Struct EFI_IP6_ADDRESS_INFO {
  EFI_IPv6_ADDRESS        Address;
  UINT8                   PrefixLength;
}

#**********************************************
# EFI_IP6_ROUTE_TABLE 
#**********************************************
Struct EFI_IP6_ROUTE_TABLE {
  EFI_IPv6_ADDRESS        Gateway;
  EFI_IPv6_ADDRESS        Destination;
  UINT8                   PrefixLength;
}

#**********************************************
# EFI_IP6_NEIGHBOR_CACHE 
#**********************************************
Struct EFI_IP6_NEIGHBOR_CACHE {
  EFI_IPv6_ADDRESS        Neighbor;
  EFI_MAC_ADDRESS         LinkAddress;
  UINTN                   State;
}

#**********************************************
# EFI_IP6_ICMP_TYPE 
#**********************************************
Struct EFI_IP6_ICMP_TYPE {
  UINT8                Type;
  UINT8                Code;
}

#**********************************************
# EFI_IP6_MODE_DATA 
#**********************************************
Struct EFI_IP6_MODE_DATA {
  BOOLEAN               IsStarted;
  UINT32                MaxPacketSize;
  EFI_IP6_CONFIG_DATA   ConfigData;
  BOOLEAN               IsConfigured;
  UINT32                AddressCount;  
  POINTER               AddressList;
  UINT32                GroupCount;
  POINTER               GroupTable;
  UINT32                RouteCount;
  POINTER               RouteTable;
  UINT32                NeighborCount;
  POINTER               NeighborCache;
  UINT32                PrefixCount;
  POINTER               PrefixTable;
  UINT32                IcmpTypeCount;
  POINTER               IcmpTypeList;  
}

#**********************************************
# EFI_IP6_HEADER 
#**********************************************
Pack 1
Struct EFI_IP6_HEADER {
  UINT32              Version_TrafficClass_FlowLabel;
  UINT16              PayloadLength;
  UINT8               NextHeader;
  UINT8               HopLimit;  
  EFI_IPv6_ADDRESS    SourceAddress;
  EFI_IPv6_ADDRESS    DestinationAddress;
}
Pack

#**********************************************
# EFI_IP6_FRAGMENT_DATA 
#**********************************************
Struct EFI_IP6_FRAGMENT_DATA {
  UINT32        FragmentLength;
  POINTER       FragmentBuffer;
}

#**********************************************
# EFI_IP6_RECEIVE_DATA 
#**********************************************
Struct EFI_IP6_RECEIVE_DATA {
  EFI_TIME               TimeStamp;
  UINTN                  RecycleSignal;
  UINT32                 HeaderLength;
  POINTER                Header;
  UINT32                 DataLength;
  UINT32                 FragmentCount;  
  EFI_IP6_FRAGMENT_DATA  FragmentTable;
}

Struct EFI_IP6_RECEIVE_DATA_P4 {
  EFI_TIME               TimeStamp;
  UINTN                  RecycleSignal;
  UINT32                 HeaderLength;
  POINTER                Header;
  UINT32                 DataLength;
  UINT32                 FragmentCount;  
  EFI_IP6_FRAGMENT_DATA  FragmentTable(4);
}

#**********************************************
# EFI_IP6_OVERRIDE_DATA 
#**********************************************
Struct EFI_IP6_OVERRIDE_DATA {
  UINT8                  Protocol;
  UINT8                  HopLimit;
  UINT32                 FlowLabel;
}

#**********************************************
# EFI_IP6_TRANSMIT_DATA 
#**********************************************
Struct EFI_IP6_TRANSMIT_DATA {
  EFI_IPv6_ADDRESS       DestinationAddress;
  POINTER                OverrideData;
  UINT32                 ExtHdrsLength;
  POINTER                ExtHdrs;
  UINT8                  NextHeader;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP6_FRAGMENT_DATA  FragmentTable;
}

Struct EFI_IP6_TRANSMIT_DATA_P2 {
  EFI_IPv6_ADDRESS       DestinationAddress;
  POINTER                OverrideData;
  UINT32                 ExtHdrsLength;
  POINTER                ExtHdrs;
  UINT8                  NextHeader;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP6_FRAGMENT_DATA  FragmentTable(2);
}

Struct EFI_IP6_TRANSMIT_DATA_P4 {
  EFI_IPv6_ADDRESS       DestinationAddress;
  POINTER                OverrideData;
  UINT32                 ExtHdrsLength;
  POINTER                ExtHdrs;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP6_FRAGMENT_DATA  FragmentTable(4);
}

#**********************************************
# EFI_IP6_COMPLETION_TOKEN 
#**********************************************
Struct EFI_IP6_COMPLETION_TOKEN {
  UINTN                   Event;
  UINTN                   Status;
  POINTER                 Packet;
}
