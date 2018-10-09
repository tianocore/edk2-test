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
if {[info exist IP6_DEFINES_TCL] == 1} {
  return
}
set IP6_DEFINES_TCL 1

#
# EUT/ENTS Connection Definition
#
set DEF_EUT_IP_ADDR   "2002:0000:0000:0000:0000:0000:0000:4321"
set DEF_EUT_MAC_ADDR  [GetTargetMac]
set DEF_EUT_PRT       0

set DEF_ENTS_IP_ADDR  "2002:0000:0000:0000:0000:0000:0000:0002"
set DEF_ENTS_MAC_ADDR [GetHostMac]
set DEF_ENTS_PRT      8888

puts $DEF_EUT_IP_ADDR
puts $DEF_ENTS_IP_ADDR