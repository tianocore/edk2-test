#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
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
