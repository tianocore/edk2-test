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




