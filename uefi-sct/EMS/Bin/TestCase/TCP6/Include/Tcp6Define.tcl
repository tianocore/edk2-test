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
if {[info exist TCP6_DEFINES_TCL] == 1} {
  return
}
set TCP6_DEFINES_TCL 1

#
# TCP6 Flags Definition
#
set FIN              0x01
set SYN              0x02
set RST              0x04
set PSH              0x08
set ACK              0x10
set URG              0x20

#
# EUT/ENTS Connection Definition
#
set DEF_EUT_IP_ADDR   "2002:0000:0000:0000:0000:0000:0000:4321"
set DEF_EUT_MAC_ADDR  [GetTargetMac]
set DEF_EUT_PRT       0

set DEF_ENTS_IP_ADDR  "2002:0000:0000:0000:0000:0000:0000:0002"
set DEF_ENTS_MAC_ADDR [GetHostMac]
set DEF_ENTS_PRT      8888

#
# EFI_TCP6_CONNECTION_STATE 
#
set TCS(Closed)      0
set TCS(Listen)      1
set TCS(SynSent)     2
set TCS(SynReceived) 3
set TCS(Established) 4
set TCS(FinWait1)    5
set TCS(FinWait2)    6
set TCS(Closing)     7
set TCS(TimeWait)    8
set TCS(CloseWait)   9
set TCS(LastAck)    10

#
# Timers
#
set i 0
set L_TimeOut 30

#end of TCP6_DEFINES_TCL
