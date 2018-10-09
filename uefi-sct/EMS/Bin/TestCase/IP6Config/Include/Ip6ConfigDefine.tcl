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
if {[info exist IP6CONFIG_DEFINE] == 1} {
  return
}
set IP6CONFIG_DEFINE 1

#
# EUT/ENTS Connection Definition
#
#set DEF_EUT_IP_ADDR   "2002:0000:0000:0000:0000:0000:0000:0001"
#set DEF_EUT_MAC_ADDR  [GetTargetMac]
#set DEF_EUT_PRT       0

#set DEF_ENTS_IP_ADDR  "2002:0000:0000:0000:0000:0000:0000:4321"
#set DEF_ENTS_MAC_ADDR [GetHostMac]
#set DEF_ENTS_PRT      8888

#
# EFI_IP6_CONFIG_DATA_TYPE
#
set IP6CDT(InterfaceInfo) 0
set IP6CDT(AltInterfaceId) 1
set IP6CDT(Policy) 2
set IP6CDT(DupAddrDetectTransmits) 3
set IP6CDT(ManualAddress) 4
set IP6CDT(Gateway) 5
set IP6CDT(DnsServer) 6
set IP6CDT(Maximum) 7

#
# EFI_IP6_CONFIG_POLICY
#
set IP6CP(Manual) 0
set IP6CP(Automatic) 1

#
# Timers
#
set i 0
set L_TimeOut 30
