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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
################################################################################
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          C25EE790-B35F-4a5e-A2AD-1439B4898565
CaseName          Connect.Conf6.Case1
CaseCategory      TCP6
CaseDescription   {This case is to test the conformance - EFI_CONNECTION_REFUSED.   \
                   -- When TCB in SYN-RCVD state & recevie a RST. }
################################################################################

Include TCP6/include/Tcp6.inc.tcl

proc CleanUpEUTEnvironmentBegin {} {
  #
  # Destroy TCP6 child
  #
  Tcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck
  
  #
  # Close transmittion mechanism for EUT
  #
  EUTClose

}

proc CleanUpEUTEnvironmentEnd {} {

  DestroyPacket
  EndCapture
  EndScope _TCP6_CONNECT_CONF6_CASE1_
  EndLog
}


#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_CONNECT_CONF6_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context
UINTN                            R_Context1

EFI_TCP6_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP6_CONFIG_DATA             R_Configure_Tcp6ConfigData

EFI_TCP6_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP6_CONNECTION_TOKEN        R_Connect_ConnectionToken


#
# Create Tcp6 Child.
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure Tcp6 Instance
#
SetIpv6Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetVar          R_Configure_AccessPoint.StationPort        6666
SetIpv6Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         TRUE


SetVar R_Configure_Tcp6ConfigData.TrafficClass        0
SetVar R_Configure_Tcp6ConfigData.HopLimit            128
SetVar R_Configure_Tcp6ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp6ConfigData.ControlOption       0

Tcp6->Configure {&@R_Configure_Tcp6ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Tcp6.Configure - Call Configure() with valid config data"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Tcp6.Connect() in active mode with valid parameters. 
#              The instance's state should go to TCP_SYN_SENT.
#
SetVar R_Context 0
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                               \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar R_Connect_CompletionToken.Status $EFI_INCOMPATIBLE_VERSION
SetVar R_Connect_ConnectionToken.CompletionToken @R_Connect_CompletionToken

#
# Start Capture
#
set L_Filter "ether src $DEF_EUT_MAC_ADDR and tcp"
StartCapture CCB $L_Filter
#
# Setup the packet sending parameters
#
LocalIPv6           $DEF_ENTS_IP_ADDR
RemoteIPv6          $DEF_EUT_IP_ADDR
LocalEther          $DEF_ENTS_MAC_ADDR
RemoteEther         $DEF_EUT_MAC_ADDR

Tcp6->Connect {&@R_Connect_ConnectionToken, &@R_Status}
GetAck

#
# simulate a simultaneous connection 
#

#
# receive SYN from target
#
#
# EUT : SYN
#
ReceiveCcbPacket CCB L_Packet 5

if { ${CCB.received} == 0} {    
  set assert fail
  puts "EUT doesn't send out any segment."
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "EUT doesn't send out any segment."
  #
  # Close Events
  #
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
  RecordAssertion $assert $GenericAssertionGuid                                  \
                  "BS.DestroyEvent. "                         \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                    
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  
  return
}

ParsePacket L_Packet -t IPv6 -IPv6_payload L_Tcp6Packet
set L_Flag [lrange $L_Tcp6Packet 13 13]
set L_Flag [expr {$L_Flag & 0x37}]
set L_Flag [format "%#04x" $L_Flag]

if {[string compare $L_Flag $SYN] != 0} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid  \
                  "Tcp6.Connect-No SYN sent."
  #
  # Close Events
  #
  BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
  GetAck
  set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
  RecordAssertion $assert $GenericAssertionGuid                                  \
                  "BS.DestroyEvent. "                         \
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                    
  CleanUpEUTEnvironmentBegin
  CleanUpEUTEnvironmentEnd
  
  return
}

#
# send a SYN immediately to chang Target TCB state to SYN-RCVD
#
set L_FlagAck [expr {$SYN}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $DEF_ENTS_PRT -tcp_dp 6666 -tcp_control $L_FlagAck -IP_ver 0x06
SendPacket P_Tcp6PacketAck -c 1


Stall 5

#
# send a RST to cause this connection signal user EFI_CONNECTION_REFUSED
#
set L_FlagAck [expr {$RST}]
CreatePacket P_Tcp6PacketAck -t tcp -tcp_sp $DEF_ENTS_PRT -tcp_seq 1 -tcp_dp 6666 -tcp_control $L_FlagAck -IP_ver 0x06
SendPacket P_Tcp6PacketAck -c 1

while {1} { 
  Stall 1                                                                                    
  GetVar R_Connect_ConnectionToken.CompletionToken.Status                                    
                                                                                                                                                                
  if { ${R_Connect_ConnectionToken.CompletionToken.Status} != $EFI_INCOMPATIBLE_VERSION} { 
    if { ${R_Connect_ConnectionToken.CompletionToken.Status} != $EFI_CONNECTION_REFUSED} {
      set assert fail                                                                        
      break
    } else {
      set assert pass
      break     
    }         
  }      
}   


RecordAssertion $assert $Tcp6ConnectConf6AssertionGuid001                            \
                      "Connection with Active Open. Receive RST in SYN-RCVD state   \
                       CompletionStatus - ${R_Connect_ConnectionToken.CompletionToken.Status}, ExpectedStatus - $EFI_CONNECTION_REFUSED"


 
#
# Close Events
#
BS->CloseEvent {@R_Connect_CompletionToken.Event, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.DestroyEvent. "                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
                  
CleanUpEUTEnvironmentBegin
CleanUpEUTEnvironmentEnd
