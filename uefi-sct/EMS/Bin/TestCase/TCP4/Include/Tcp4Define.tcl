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
if {[info exist TCP4_DEFINES_TCL] == 1} {
  return
}
set TCP4_DEFINES_TCL 1

#
# TCP4 Flags Definition
#
set FIN              0x01
set SYN              0x02
set RST              0x04
set PSH              0x08
set ACK              0x10
set URG              0x20

#
# TCB Connection Definition
#
set DEF_EUT_IP_ADDR   192.168.88.88
set DEF_EUT_MAC_ADDR  [GetTargetMac]
set DEF_EUT_MASK      255.255.255.0
set DEF_EUT_PRT       6666

set DEF_ENTS_IP_ADDR  192.168.88.1
set DEF_ENTS_MAC_ADDR [GetHostMac]
set DEF_ENTS_MASK     255.255.255.0
set DEF_ENTS_PRT      8888

#end of TCP4_DEFINES_TCL