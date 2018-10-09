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
if {[info exist UDP6_INC_TCL] == 1} {
  return
}

set UDP6_INC_TCL 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include MNP/Include/Mnp.inc.tcl
Include MNP/Include/Mnp.proc.tcl
Include SNP/Include/Snp.inc.tcl
Include IP6/Include/Ip6.inc.tcl
Include IP6Config/Include/Ip6Config.inc.tcl
Include UDP6/Include/Udp6.proc.tcl
Include UDP6/Include/Udp6.Define.tcl
Include UDP6/Include/Udp6AssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

###################################################################
# Function Declaration
###################################################################
Func Udp6ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Udp6ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Udp6->GetModeData {
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
}

Func Udp6->Configure {
  POINTER
  POINTER
}

Func Udp6->Groups {
  BOOLEAN
  POINTER
  POINTER
}

Func Udp6->Poll {
  POINTER
}

Func Udp6->Receive {
  POINTER
  POINTER
}

Func Udp6->Transmit {
  POINTER
  POINTER
}

Func Udp6->Cancel {
  POINTER
  POINTER
}

Func Udp6->SignalRecycleEvent {
  POINTER
  POINTER
}

##################################################
#   EFI_UDP6_CONFIG_DATA
##################################################
Struct EFI_UDP6_CONFIG_DATA {
BOOLEAN            AcceptPromiscuous;
BOOLEAN            AcceptAnyPort;
BOOLEAN            AllowDuplicatePort;

UINT8              TrafficClass;
UINT8              HopLimit;
UINT32             ReceiveTimeout;
UINT32             TransmitTimeout;

EFI_IPv6_ADDRESS   StationAddress;
UINT16             StationPort;
EFI_IPv6_ADDRESS   RemoteAddress;
UINT16             RemotePort;
};

##################################################
#      EFI_UDP6_FRAGMENT_DATA
##################################################
Struct EFI_UDP6_FRAGMENT_DATA {
  UINT32        FragmentLength;
  POINTER       FragmentBuffer;
};

##################################################
#      EFI_UDP6_SESSION_DATA
##################################################
Struct EFI_UDP6_SESSION_DATA {
  EFI_IPv6_ADDRESS   SourceAddress;
  UINT16             SourcePort;
  EFI_IPv6_ADDRESS   DestinationAddress;
  UINT16             DestinationPort;
};

##################################################
#      EFI_UDP6_TRANSMIT_DATA
##################################################
Struct EFI_UDP6_TRANSMIT_DATA {
  POINTER                    UdpSessionData;
  UINT32                     DataLength;
  UINT32                     FragmentCount;
  EFI_UDP6_FRAGMENT_DATA     FragmentTable; 
};
Struct EFI_UDP6_TRANSMIT_DATA_P2 {
  POINTER                    UdpSessionData;
  UINT32                     DataLength;
  UINT32                     FragmentCount;
  EFI_UDP6_FRAGMENT_DATA     FragmentTable(2); 
};
##################################################
#      EFI_UDP6_RECEIVE_DATA
##################################################
Struct EFI_UDP6_RECEIVE_DATA {
  EFI_TIME                TimeStamp;
  UINTN                   RecycleSignal;
  EFI_UDP6_SESSION_DATA   UdpSession;
  UINT32                  DataLength;
  UINT32                  FragmentCount;
  EFI_UDP6_FRAGMENT_DATA  FragmentTable
};

##################################################
#      EFI_UDP6_COMPLETION_TOKEN 
##################################################
Struct EFI_UDP6_COMPLETION_TOKEN {
  UINTN                   Event;
  UINTN                   Status;
  POINTER                 Packet;
}; 

##################################################
#      EFI_UDP6_HEADER 
##################################################
Pack 1
Struct EFI_UDP6_HEADER {
  UINT16     Udp6SrcPort;
  UINT16     Udp6DstPort;
  UINT16     Udp6Length;
  UINT16     Udp6CheckSum;  
};
Pack




