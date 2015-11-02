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
if {[info exist TCP4_PROC_TCL] == 1} {
  return
}
set TCP4_PROC_TCL 1

proc AddEntryInArpCache { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR
	BeginScope _PROC_ADD_ENTRY_IN_ARP_CACHE_
  
  EFI_IP_ADDRESS                   R_Proc_StationAddress
  EFI_ARP_CONFIG_DATA              R_Proc_ArpConfigData
  EFI_IP_ADDRESS                   R_Proc_TargetSwAddress
  EFI_MAC_ADDRESS                  R_Proc_TargetHwAddress
  UINTN                            R_Proc_ArpStatus
  UINTN                            R_Proc_ArpHandle
  
  ArpServiceBinding->CreateChild "&@R_Proc_ArpHandle, &@R_Proc_ArpStatus"
  GetAck
  SetVar     [subst $ENTS_CUR_CHILD]  @R_Proc_ArpHandle
  
  SetIpv4Address R_Proc_StationAddress.v4     $DEF_EUT_IP_ADDR
  SetVar R_Proc_ArpConfigData.SwAddressType   0x800
  SetVar R_Proc_ArpConfigData.SwAddressLength 4
  SetVar R_Proc_ArpConfigData.StationAddress  &@R_Proc_StationAddress
  SetVar R_Proc_ArpConfigData.EntryTimeOut    0
  SetVar R_Proc_ArpConfigData.RetryCount      0
  SetVar R_Proc_ArpConfigData.RetryTimeOut    0
  
  Arp->Configure {&@R_Proc_ArpConfigData, &@R_Proc_ArpStatus}
  GetAck
  
  SetIpv4Address   R_Proc_TargetSwAddress.v4 $DEF_ENTS_IP_ADDR
  SetEthMacAddress R_Proc_TargetHwAddress $DEF_ENTS_MAC_ADDR
  
  #
  # check point
  #
  Arp->Add {FALSE, &@R_Proc_TargetSwAddress, &@R_Proc_TargetHwAddress, 0, TRUE, &@R_Proc_ArpStatus}
  GetAck
}


# Procedure Name
#   DelEntryInArpCache
# Procedure Description:
#   Call ARP.Delete() to delete an entry in ARP cache.
# Arguments:
#   EutStationAddress  - EUT station IP address.
#   EntsSwAddress      - ENTS IP address.
#   EntsHwAddress      - ENTS MAC address.
# Returns:
#   Nothing.
#
proc DelEntryInArpCache { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR
  UINTN TempCurChild
  
  SetVar TempCurChild @[subst $ENTS_CUR_CHILD]
  SetVar [subst $ENTS_CUR_CHILD]  @R_Proc_ArpHandle
  
  Arp->Delete {TRUE, &@R_Proc_TargetSwAddress, &@R_Proc_ArpStatus}
  GetAck

  ArpServiceBinding->DestroyChild {@R_Proc_ArpHandle, &@R_Proc_ArpStatus}
  GetAck

  SetVar [subst $ENTS_CUR_CHILD]  @TempCurChild
  
  EndScope _PROC_ADD_ENTRY_IN_ARP_CACHE_
}