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
if {[info exist TCP6_INC] == 1} {
  return
}
set TCP6_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include Snp/Include/Snp.inc.tcl
Include Mnp/Include/Mnp.inc.tcl
Include Ip6/Include/Ip6.inc.tcl
Include IP6Config/Include/Ip6Config.inc.tcl
Include TCP6/Include/Tcp6Define.tcl
Include TCP6/Include/Tcp6.proc.tcl
Include TCP6/Include/Tcp6AssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

Func Tcp6ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Tcp6ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Tcp6->GetModeData {
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
}

Func Tcp6->Configure {
  POINTER 
  POINTER
}

Func Tcp6->Routes {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  POINTER
}

Func Tcp6->Connect {
  POINTER
  POINTER
}

Func Tcp6->Accept {
  POINTER
  POINTER
}

Func Tcp6->Transmit {
  POINTER
  POINTER
}

Func Tcp6->Receive {
  POINTER
  POINTER
}

Func Tcp6->Close {
  POINTER
  POINTER
}

Func Tcp6->Cancel {
  POINTER
  POINTER
}

Func Tcp6->Poll {
  POINTER
}


###################################################################
# EFI_TCP6_SERVICE_POINT 
###################################################################
Struct EFI_TCP6_SERVICE_POINT {
  POINTER                     InstanceHandle;
  EFI_IPv6_ADDRESS            LocalAddress;
  UINT16                      LocalPort;
  EFI_IPv6_ADDRESS            RemoteAddress;
  UINT16                      RemotePort;
}
 

###################################################################
# EFI_TCP6_DATA_REGISTRY_ENTRY
###################################################################
Struct EFI_TCP6_DATA_REGISTRY_ENTRY {
  EFI_GUID                    ProtocolGuid;
  POINTER                     DriverHandle;
  UINT32                      ServiceCount;
  EFI_TCP6_SERVICE_POINT      Services(10);
}


###################################################################
# EFI_TCP6_ACCESS_POINT
###################################################################
Struct EFI_TCP6_ACCESS_POINT {
  EFI_IPv6_ADDRESS            StationAddress;
  UINT16                      StationPort;
  EFI_IPv6_ADDRESS            RemoteAddress;
  UINT16                      RemotePort;
  BOOLEAN                     ActiveFlag;
}
 
###################################################################
# EFI_TCP6_OPTION
###################################################################
Struct EFI_TCP6_OPTION {
  UINT32                       ReceiveBufferSize;
  UINT32                       SendBufferSize;
  UINT32                       MaxSynBackLog;
  UINT32                       ConnectionTimeout;
  UINT32                       DataRetries;
  UINT32                       FinTimeout;
  UINT32                       TimeWaitTimeout;
  UINT32                       KeepAliveProbes;
  UINT32                       KeepAliveTime;
  UINT32                       KeepAliveInterval;
  BOOLEAN                      EnableNagle;
  BOOLEAN                      EnableTimeStamp;
  BOOLEAN                      EnableWindowScaling;
  BOOLEAN                      EnableSelectiveAck;
  BOOLEAN                      EnablePathMtuDiscovery;
}

set Tcp6StateClosed           0;
set Tcp6StateListen           1;
set Tcp6StateSynSent          2;
set Tcp6StateSynReceived      3;
set Tcp6StateEstablished      4;
set Tcp6StateFinWait1         5;
set Tcp6StateFinWait2         6;
set Tcp6StateClosing          7;
set Tcp6StateTimeWait         8;
set Tcp6StateCloseWait        9;
set Tcp6StateLastAck         10;

###################################################################
# EFI_TCP6_CONFIG_DATA
###################################################################
Struct EFI_TCP6_CONFIG_DATA {
  UINT8                       TrafficClass;
  UINT8                       HopLimit;
  EFI_TCP6_ACCESS_POINT       AccessPoint; 
  POINTER                     ControlOption;
}


###################################################################
# EFI_TCP6_COMPLETION_TOKEN
###################################################################
Struct EFI_TCP6_COMPLETION_TOKEN {
  UINTN                       Event;
  UINTN                       Status;
}
 
###################################################################
# EFI_TCP6_CONNECTION_TOKEN
###################################################################
Struct EFI_TCP6_CONNECTION_TOKEN {
  EFI_TCP6_COMPLETION_TOKEN   CompletionToken;
}
 
###################################################################
# EFI_TCP6_LISTEN_TOKEN
###################################################################
Struct EFI_TCP6_LISTEN_TOKEN {
  EFI_TCP6_COMPLETION_TOKEN   CompletionToken;
  POINTER                     NewChildHandle;
}
 
###################################################################
# EFI_TCP6_FRAGMENT_DATA
###################################################################
Struct EFI_TCP6_FRAGMENT_DATA {
  UINT32                      FragmentLength;
  POINTER                     FragmentBuffer;
}
 
 
###################################################################
# EFI_TCP6_RECEIVE_DATA
###################################################################
Struct EFI_TCP6_RECEIVE_DATA {
  BOOLEAN                     UrgentFlag;
  UINT32                      DataLength;
  UINT32                      FragmentCount;
  EFI_TCP6_FRAGMENT_DATA      FragmentTable(10);
}
 
###################################################################
# EFI_TCP6_TRANSMIT_DATA
###################################################################
Struct EFI_TCP6_TRANSMIT_DATA {
  BOOLEAN                     Push;
  BOOLEAN                     Urgent;
  UINT32                      DataLength;
  UINT32                      FragmentCount;
  EFI_TCP6_FRAGMENT_DATA      FragmentTable(10);
}
 
###################################################################
# EFI_TCP6_IO_TOKEN
###################################################################
Union Packet {
  POINTER                     RxData;
  POINTER                     TxData;
}

Struct EFI_TCP6_IO_TOKEN {
  EFI_TCP6_COMPLETION_TOKEN   CompletionToken;
  Packet                      Packet_Buffer;
}
  
###################################################################
# EFI_TCP6_CLOSE_TOKEN 
###################################################################
Struct EFI_TCP6_CLOSE_TOKEN { 
  EFI_TCP6_COMPLETION_TOKEN    CompletionToken;
  BOOLEAN                      AbortOnClose;
}
