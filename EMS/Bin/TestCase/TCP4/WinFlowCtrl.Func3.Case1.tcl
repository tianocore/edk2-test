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
################################################################################
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid          B2BA2224-F102-4add-BE00-4717008F0310
CaseName          WinFlowCtrl.Func3.Case1
CaseCategory      TCP
CaseDescription   {This item is to test the [EUT] correctly handles the bulk   \
                   data flow, the [EUT] should not respond with an             \
                   acknowledgement segment for each of the received segments.}
################################################################################

Include TCP4/include/Tcp4.inc.tcl

proc CleanUpEutEnvironmentBegin {} {
  global RST
 
  UpdateTcpSendBuffer TCB -c $RST
  SendTcpPacket TCB
 
  DestroyTcb
  DestroyPacket
  DelEntryInArpCache

  Tcp4ServiceBinding->DestroyChild "@R_Tcp4Handle, &@R_Status"
  GetAck
 
}

proc CleanUpEutEnvironmentEnd {} {
  EndLogPacket
  EndScope _TCP4_RFC_COMPATIBILITY_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope on OS.
#
BeginScope _TCP4_RFC_COMPATIBILITY_

BeginLogPacket WinFlowCtrl.Func3.Case1 "host $DEF_EUT_IP_ADDR and host         \
                                             $DEF_ENTS_IP_ADDR"

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Tcp4Handle
UINTN                            R_Context

EFI_TCP4_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP4_CONFIG_DATA             R_Configure_Tcp4ConfigData

EFI_TCP4_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP4_CONNECTION_TOKEN        R_Connect_ConnectionToken

#
# Initialization of TCB related on OS side.
#
CreateTcb TCB $DEF_ENTS_IP_ADDR $DEF_ENTS_PRT $DEF_EUT_IP_ADDR $DEF_EUT_PRT
BuildTcpOptions MssOption -m 1024
CreatePayload FullSizePayload Incr 1024 0x00

LocalEther  $DEF_ENTS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_ENTS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Create Tcp4 Child.
#
Tcp4ServiceBinding->CreateChild "&@R_Tcp4Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Tcp4Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4SBP.CreateChild - Create Child 1."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure TCP instance.
#
SetVar R_Configure_AccessPoint.UseDefaultAddress      FALSE
SetIpv4Address R_Configure_AccessPoint.StationAddress $DEF_EUT_IP_ADDR
SetIpv4Address R_Configure_AccessPoint.SubnetMask     $DEF_EUT_MASK
SetVar R_Configure_AccessPoint.StationPort            $DEF_EUT_PRT
SetIpv4Address R_Configure_AccessPoint.RemoteAddress  $DEF_ENTS_IP_ADDR
SetVar R_Configure_AccessPoint.RemotePort             $DEF_ENTS_PRT
SetVar R_Configure_AccessPoint.ActiveFlag             TRUE

SetVar R_Configure_Tcp4ConfigData.TypeOfService       0
SetVar R_Configure_Tcp4ConfigData.TimeToLive          128
SetVar R_Configure_Tcp4ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp4ConfigData.ControlOption       0

Tcp4->Configure {&@R_Configure_Tcp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp4.Configure - Configure Child 1."                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call Tcp4.Connect for an active TCP instance.
#
BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Connect_ConnectionToken.CompletionToken @R_Connect_CompletionToken
SetVar R_Connect_ConnectionToken.CompletionToken.Status $EFI_INCOMPATIBLE_VERSION

Tcp4->Connect {&@R_Connect_ConnectionToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Tcp4WinFlowCtrlFunc3AssertionGuid001                  \
                "Tcp4.Connect - Open an active connection."                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Handles the three-way handshake.
#
ReceiveTcpPacket TCB 5

set L_TcpFlag [expr $SYN | $ACK]
UpdateTcpSendBuffer TCB -c $L_TcpFlag -o MssOption
SendTcpPacket TCB

ReceiveTcpPacket TCB 5

#
# Make the [OS] send ten full-sized and consecutive segments and capture the
# responded segments.
# The [EUT] should not respond with an acknowledgement segment for each of the
# received segments. There should be an acknowledgement segment for at least
# every second segment.
#
UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

UpdateTcpSendBuffer TCB -c $ACK -p FullSizePayload
SendTcpPacket TCB

#
# Clean up the environment on EUT side.
#

CleanUpEutEnvironmentBegin
BS->CloseEvent "@R_Connect_CompletionToken.Event, &@R_Status"
GetAck
CleanUpEutEnvironmentEnd
