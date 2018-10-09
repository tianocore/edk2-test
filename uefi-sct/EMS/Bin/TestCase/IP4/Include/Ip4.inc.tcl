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
if {[info exist IP4_INC] == 1} {
  return
}
set IP4_INC 1

Include EfiUtil/EfiInclude.tcl
Include Include/EntsProtocolTest.inc.tcl
Include Include/EfiBootService.inc.tcl
Include MNP/Include/Mnp.inc.tcl
Include SNP/Include/Snp.inc.tcl

Include Include/GenericAssertionGuid.tcl
Include IP4/Include/Ip4AssertionGuid.tcl

Func Ip4ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Ip4ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Ip4->Configure {
  POINTER
  POINTER
}

Func Ip4->GetModeData {
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Ip4->Groups {
  BOOLEAN
  POINTER
  POINTER
  }

Func Ip4->Routes {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Ip4->Transmit {
  POINTER
  POINTER
  }

Func Ip4->Receive {
  POINTER
  POINTER
  }

Func Ip4->Cancel {
  POINTER
  POINTER
}

Func Ip4->Poll {
  POINTER
  }


#**********************************************
# EFI_IP4_CONFIG_DATA 
#**********************************************
Struct EFI_IP4_CONFIG_DATA {
  UINT8              DefaultProtocol;
  BOOLEAN            AcceptAnyProtocol;
  BOOLEAN            AcceptIcmpErrors;
  BOOLEAN            AcceptBroadcast;
  BOOLEAN            AcceptPromiscuous;
  BOOLEAN            UseDefaultAddress;
  EFI_IPv4_ADDRESS   StationAddress;
  EFI_IPv4_ADDRESS   SubnetMask;
  UINT8              TypeOfService;
  UINT8              TimeToLive;
  BOOLEAN            DoNotFragment;
  BOOLEAN            RawData;
  UINT32             ReceiveTimeout;
  UINT32             TransmitTimeout;
}

#**********************************************
# EFI_IP4_ROUTE_TABLE 
#**********************************************
Struct EFI_IP4_ROUTE_TABLE {
  EFI_IPv4_ADDRESS        SubnetAddress;
  EFI_IPv4_ADDRESS        SubnetMask;
  EFI_IPv4_ADDRESS        GatewayAddress;
}

#**********************************************
# EFI_IP4_ICMP_TYPE 
#**********************************************
Struct EFI_IP4_ICMP_TYPE {
  UINT8                Type;
  UINT8                Code;
}

#**********************************************
# EFI_IP4_MODE_DATA 
#**********************************************
Struct EFI_IP4_MODE_DATA {
  BOOLEAN               IsStarted;
  UINT32                MaxPacketSize;
  EFI_IP4_CONFIG_DATA   ConfigData;
  BOOLEAN               IsConfigured;
  UINT32                GroupCount;
  POINTER               GroupTable;
  UINT32                RouteCount;
  POINTER               RouteTable;
  UINT32                IcmpTypeCount;
  POINTER               IcmpTypeList;
}

#**********************************************
# EFI_IP4_HEADER 
#**********************************************
Pack 1
Struct EFI_IP4_HEADER {
  UINT8               Version_HeaderLength;
  UINT8               TypeOfService;
  UINT16              TotalLength;
  UINT16              Identification;
  UINT16              Fragmentation;
  UINT8               TimeToLive;
  UINT8               Protocol;
  UINT16              Checksum;
  EFI_IPv4_ADDRESS    SourceAddress;
  EFI_IPv4_ADDRESS    DestinationAddress;
}
Pack

#**********************************************
# EFI_IP4_FRAGMENT_DATA 
#**********************************************
Struct EFI_IP4_FRAGMENT_DATA {
  UINT32        FragmentLength;
  POINTER       FragmentBuffer;
}

#**********************************************
# EFI_IP4_RECEIVE_DATA 
#**********************************************
Struct EFI_IP4_RECEIVE_DATA {
  EFI_TIME               TimeStamp;
  UINTN                  RecycleSignal;
  UINT32                 HeaderLength;
  POINTER                Header;
  UINT32                 OptionsLength;
  POINTER                Options;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable;
}

Struct EFI_IP4_RECEIVE_DATA_P4 {
  EFI_TIME               TimeStamp;
  UINTN                  RecycleSignal;
  UINT32                 HeaderLength;
  POINTER                Header;
  UINT32                 OptionsLength;
  POINTER                Options;
  UINT32                 DataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable(4);
}

#**********************************************
# EFI_IP4_OVERRIDE_DATA 
#**********************************************
Struct EFI_IP4_OVERRIDE_DATA {
  EFI_IPv4_ADDRESS       SourceAddress;
  EFI_IPv4_ADDRESS       GatewayAddress;
  UINT8                  Protocol;
  UINT8                  TypeOfService;
  UINT8                  TimeToLive;
  BOOLEAN                DoNotFragment;
  BOOLEAN                RawData;
}

#**********************************************
# EFI_IP4_TRANSMIT_DATA 
#**********************************************
Struct EFI_IP4_TRANSMIT_DATA {
  EFI_IPv4_ADDRESS       DestinationAddress;
  POINTER                OverrideData;
  UINT32                 OptionsLength;
  POINTER                OptionsBuffer;
  UINT32                 TotalDataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable;
}

Struct EFI_IP4_TRANSMIT_DATA_P4 {
  EFI_IPv4_ADDRESS       DestinationAddress;
  POINTER                OverrideData;
  UINT32                 OptionsLength;
  POINTER                OptionsBuffer;
  UINT32                 TotalDataLength;
  UINT32                 FragmentCount;
  EFI_IP4_FRAGMENT_DATA  FragmentTable(4);
}

#**********************************************
# EFI_IP4_COMPLETION_TOKEN 
#**********************************************
Struct EFI_IP4_COMPLETION_TOKEN {
  UINTN                                 Event;
  UINTN                                 Status;
  POINTER                               Packet;
}
