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
