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
if {[info exist UDP4_PROC_TCL] == 1} {
  return
}
set UDP4_PROC_TCL 1

set DEF_EUT_IP_ADDR   192.168.88.1
set DEF_EUT_MAC_ADDR  [GetTargetMac]
set DEF_EUT_MASK      255.255.255.0

set DEF_ENTS_IP_ADDR  192.168.88.2
set DEF_ENTS_MAC_ADDR [GetHostMac]
set DEF_ENTS_MASK     255.255.255.0

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
