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
if {[info exist IP6CONFIG_INC] == 1} {
  return
}
set IP6CONFIG_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl

Include IP6/Include/Ip6.inc.tcl
Include IP6Config/Include/Ip6ConfigDefine.tcl
Include IP6Config/Include/Ip6Config.proc.tcl
Include IP6Config/Include/Ip6ConfigAssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

###################################################################
# Function Declaration
###################################################################
Func Ip6Config->SetData {
    UINT32
    UINTN
    POINTER
    POINTER
}

Func Ip6Config->GetData {
    UINT32
    POINTER
    POINTER
    POINTER
}

Func Ip6Config->RegisterDataNotify {
    UINT32
    UINTN
    POINTER
}

Func Ip6Config->UnregisterDataNotify {
    UINT32
    UINTN
    POINTER
}


###################################################################
# EFI_IP6_CONFIG_INTERFACE_INFO
###################################################################
Struct EFI_IP6_CONFIG_INTERFACE_INFO {
  CHAR16                Name(32);
  UINT8                 IfType;
  UINT32                HwAddressSize;
  EFI_MAC_ADDRESS       HwAddress;
  UINT32                AddressInfoCount;
  POINTER               AddressInfo;
  UINT32                RouteCount;
  POINTER               RouteTable;
}

###################################################################
# EFI_IP6_CONFIG_INTERFACE_ID
###################################################################
Struct EFI_IP6_CONFIG_INTERFACE_ID {
  UINT8                 Id(8);
}

###################################################################
# EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS
###################################################################
Struct EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS {
  UINT32                DupAddrDetectTransmits;
}

###################################################################
# EFI_IP6_CONFIG_MANUAL_ADDRESS
###################################################################
Struct EFI_IP6_CONFIG_MANUAL_ADDRESS {
  EFI_IPv6_ADDRESS      Address;
  BOOLEAN               IsAnycast;
  UINT8                 PrefixLength;
}

