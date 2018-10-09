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
if {[info exist MNP_INC] == 1} {
  return
}
set MNP_INC 1
set ETH_HDR_LEN   14

Include Include/EntsProtocolTest.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include Include/EfiBootService.inc.tcl
Include SNP/Include/Snp.inc.tcl
Include MNP/Include/Mnp.proc.tcl
Include MNP/Include/MnpAssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl
Include Include/EfiBootService.inc.tcl

Func MnpServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func MnpServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Mnp->Configure {
  POINTER
  POINTER
}

Func Mnp->GetModeData {
  POINTER
  POINTER
  POINTER
  }

Func Mnp->MCastIpToMac {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  }

Func Mnp->Groups {
  BOOLEAN
  POINTER
  POINTER
  }

Func Mnp->Group {
  BOOLEAN
  POINTER
  POINTER
  }

Func Mnp->Transmit {
  POINTER
  POINTER
  }

Func Mnp->Receive {
  POINTER
  POINTER
  }

Func Mnp->Poll {
  POINTER
  }

Func Mnp->TransmitMultiPacket {
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Mnp->PollPattern1 {
  UINTN
  POINTER
  }
  
Func Mnp->Cancel {
  POINTER
  POINTER
}
###################################################################
# EFI_MANAGED_NETWORK_CONFIG_DATA
###################################################################
Struct EFI_MANAGED_NETWORK_CONFIG_DATA {
  UINT32     ReceivedQueueTimeoutValue;
  UINT32     TransmitQueueTimeoutValue;
  UINT16     ProtocolTypeFilter;
  BOOLEAN    EnableUnicastReceive;
  BOOLEAN    EnableMulticastReceive;
  BOOLEAN    EnableBroadcastReceive;
  BOOLEAN    EnablePromiscuousReceive;
  BOOLEAN    FlushQueuesOnReset;
  BOOLEAN    EnableReceiveTimestamps;
  BOOLEAN    DisableBackgroundPolling;
}

###################################################################
# EFI_MANAGED_NETWORK_RECEIVE_DATA 
###################################################################
Struct EFI_MANAGED_NETWORK_RECEIVE_DATA {
  EFI_TIME      Timestamp;
  POINTER       RecycleEvent;
  UINT32        PacketLength;
  UINT32        HeaderLength;
  UINT32        AddressLength;
  UINT32        DataLength;
  BOOLEAN       BroadcastFlag;
  BOOLEAN       MulticastFlag;
  BOOLEAN       PromiscuousFlag;
  UINT16        ProtocolType;
  POINTER       DestinationAddress;
  POINTER       SourceAddress;
  POINTER       MediaHeader;
  POINTER       PacketData;
}

###################################################################
# EFI_MANAGED_NETWORK_FRAGMENT_DATA 
###################################################################
Struct EFI_MANAGED_NETWORK_FRAGMENT_DATA {
  UINT32        FragmentLength;
  POINTER       FragmentBuffer;
}

###################################################################
# EFI_MANAGED_NETWORK_TRANSMIT_DATA 
###################################################################
Struct EFI_MANAGED_NETWORK_TRANSMIT_DATA {
  POINTER                           DestinationAddress;
  POINTER                           SourceAddress;
  UINT16                            ProtocolType;
  UINT32                            DataLength;
  UINT16                            HeaderLength;
  UINT16                            FragmentCount;
  EFI_MANAGED_NETWORK_FRAGMENT_DATA FragmentTable;
}

###################################################################
# EFI_MANAGED_NETWORK_COMPLETION_TOKEN 
###################################################################
Union TOKEN_PACKET {
    POINTER                         RxData;
    POINTER                         TxData;
}
Struct EFI_MANAGED_NETWORK_COMPLETION_TOKEN {
  UINTN                             Event;
  UINTN                             Status;
  TOKEN_PACKET                      Packet;
}

###################################################################
# RAW_ETH_PACKET_BODY_PACKET 
###################################################################
Pack  1
Struct RAW_ETH_PACKET_BODY_PACKET {
  UINT64      Packet
  UINT64      NotPacket
}

Struct RAW_ETH_PACKET_BODY_ARP {
  UINT16    MediaType;
  UINT16    ProtocolType;
  UINT8     MediaAddressLen;
  UINT8     ProtocolAddressLen;
  UINT16    OpCode;
  UINT8     Data(1);
}

Union RAW_ETH_PACKET_BODY_BODY {
  RAW_ETH_PACKET_BODY_PACKET    Test;
  RAW_ETH_PACKET_BODY_ARP       Arp;
}

Struct RAW_ETH_PACKET_BODY {
  UINT8                     DstAddr(6);
  UINT8                     SrcAddr(6);
  UINT16                    Protocol;
  RAW_ETH_PACKET_BODY_BODY  Body;
}

Struct RAW_PACKET_BODY {
  UINT8         Data(256)
}

Pack
