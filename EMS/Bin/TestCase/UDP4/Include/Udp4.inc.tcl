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
if {[info exist UDP_INC_TCL] == 1} {
  return
}

set UDP_INC_TCL 1

Include EfiUtil/EfiInclude.tcl
Include Include/EntsProtocolTest.inc.tcl
Include Include/EfiBootService.inc.tcl
Include MNP/Include/Mnp.inc.tcl
Include MNP/Include/Mnp.proc.tcl
Include SNP/Include/Snp.inc.tcl
Include IP4/Include/Ip4.inc.tcl
Include ARP/Include/Arp.inc.tcl
Include UDP4/Include/Udp4.proc.tcl

Include Include/GenericAssertionGuid.tcl
Include UDP4/Include/Udp4AssertionGuid.tcl


Func Udp4ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Udp4ServiceBinding->DestroyChild {
  UINTN
  POINTER
}
#*************************************************
#      EFI_UDP4_FRAGMENT_DATA                    *
#*************************************************
Struct EFI_UDP4_FRAGMENT_DATA {
  UINT32        FragmentLength;
  POINTER       FragmentBuffer;
};

#*************************************************
#      EFI_UDP4_SESSION_DATA                     *
#*************************************************
Struct EFI_UDP4_SESSION_DATA {
  EFI_IPv4_ADDRESS   SourceAddress;
  UINT16             SourcePort;
  EFI_IPv4_ADDRESS   DestinationAddress;
  UINT16             DestinationPort;
};

#************************************************
#           EFI_UDP4_HEADER                                            *
#************************************************
Pack 1
Struct EFI_UDP4_HEADER {
  UINT16     SourcePortNum;
  UINT16     DestinationPortNum;
  UINT16     UdpLength;
  UINT16     UdpCheckSum;
};
Pack

#************************************************
#      EFI_UDP4_CONFIG_DATA                     *
#************************************************
Struct EFI_UDP4_CONFIG_DATA {
  BOOLEAN               AcceptBroadcast;
  BOOLEAN               AcceptPromiscuous;
  BOOLEAN               AcceptAnyPort;
  BOOLEAN               AllowDuplicatePort;
  UINT8                 TypeOfService;
  UINT8                 TimeToLive;
  BOOLEAN               DoNotFragment;
  UINT32                ReceiveTimeout;
  UINT32                TransmitTimeout;
  BOOLEAN               UseDefaultAddress;
  EFI_IPv4_ADDRESS      StationAddress;
  EFI_IPv4_ADDRESS      SubnetMask;
  UINT16                StationPort;
  EFI_IPv4_ADDRESS      RemoteAddress;
  UINT16                RemotePort;
}

#*******************************************************
#               EFI_UDP4_TRANSMIT_DATA                 *
#*******************************************************
Struct EFI_UDP4_TRANSMIT_DATA {
  POINTER                    UdpSessionData;
  POINTER                    GatewayAddress;
  UINT32                     DataLength;
  UINT32                     FragmentCount;
  EFI_UDP4_FRAGMENT_DATA     FragmentTable;
} ;

Struct EFI_UDP4_TRANSMIT_DATA_P4 {
  POINTER                    UdpSessionData;
  POINTER                    GatewayAddress;
  UINT32                     DataLength;
  UINT32                     FragmentCount;
  EFI_UDP4_FRAGMENT_DATA     FragmentTable(4);
} ;

#*******************************************************
#           EFI_UDP4_RECEIVE_DATA                      *
#*******************************************************
Struct EFI_UDP4_RECEIVE_DATA {
  EFI_TIME                  TimeStamp;
  POINTER                   RecycleSignal;
  EFI_UDP4_SESSION_DATA     UdpSession;
  UINT32                    DataLength;
  UINT32                    FragmentCount;
  EFI_UDP4_FRAGMENT_DATA    FragmentTable;
} ;

Struct EFI_UDP4_RECEIVE_DATA_P4 {
  EFI_TIME                  TimeStamp;
  POINTER                   RecycleSignal;
  EFI_UDP4_SESSION_DATA     UdpSession;
  UINT32                    DataLength;
  UINT32                    FragmentCount;
  EFI_UDP4_FRAGMENT_DATA    FragmentTable(4);
} ;

#*******************************************************
#           EFI_UDP4_COMPLETION_TOKEN                  *
#*******************************************************
Union EFI_UDP4_COMPLETION_TOKEN_PACKET {
    POINTER               RxData;
    POINTER               TxData;
} ;


Struct EFI_UDP4_COMPLETION_TOKEN {
  UINTN                                 Event;
  UINTN                                 Status;
  POINTER                               Packet;
}


Func Udp4->GetModeData {
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
}
Func Udp4->Configure {
  POINTER
  POINTER
}
Func Udp4->Groups {
  BOOLEAN
  POINTER
  POINTER
}
Func Udp4->Routes {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  POINTER
}
Func Udp4->Poll {
  POINTER
}
Func Udp4->Receive {
  POINTER
  POINTER
}
Func Udp4->Transmit {
  POINTER
  POINTER
}
Func Udp4->Cancel {
  POINTER
  POINTER
}

Func Udp4->SignalRecycleEvent {
  POINTER
  POINTER
}

