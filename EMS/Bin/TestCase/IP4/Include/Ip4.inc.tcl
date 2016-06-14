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
