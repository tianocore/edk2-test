# 
#  Copyright 2017 Unified EFI, Inc.<BR> 
#  Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist IP4CONFIG2_DEFINE] == 1} {
  return
}
set IP4CONFIG2_DEFINE 1

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
# EFI_IP4_CONFIG2_DATA_TYPE
#
set IP4C2DT(InterfaceInfo) 0
set IP4C2DT(Policy) 1
set IP4C2DT(ManualAddress) 2
set IP4C2DT(Gateway) 3
set IP4C2DT(DnsServer) 4
set IP4C2DT(Maximum) 5

#
# EFI_IP4_CONFIG2_POLICY
#
set IP4C2P(Static) 0
set IP4C2P(Dhcp) 1
set IP4C2P(Max) 2

#
# Timers
#
set i 0
set L_TimeOut 30
