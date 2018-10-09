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
################################################################################
CaseLevel          CONFORMANCE
CaseAttribute      AUTO
CaseVerboseLevel   DEFAULT
set reportfile     report.csv

#
# Test Case Name, Category, Description, GUID ...
#
CaseGuid           A1BC810D-3096-4c51-9749-7EECC486DBA6
CaseName           Transmit.Conf9.Case1
CaseCategory       IP6
CaseDescription    {  Test the Transmit Function of IP6 - invoke Transmit()  \
                      when Token->Packet.TxData->DataLength is zero.        \
                      EFI_INVALID_PARAMETER should be returned.      
                   }
################################################################################

Include IP6/include/Ip6.inc.tcl

#
# Begin  log ...
#
BeginLog
#
# Begin Scope ...
#
BeginScope          IP6_TRANSMIT_CONF9_CASE1_

# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle 

#
# Create Child
#
Ip6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert       [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion  $assert $GenericAssertionGuid               \
                 "Ip6SB->CreateChild - Conf - Create Child "             \
                 "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"
SetVar  [subst $ENTS_CUR_CHILD]    @R_Handle

EFI_IP6_CONFIG_DATA                R_Ip6ConfigData
SetVar R_Ip6ConfigData.DefaultProtocol                0x11;        #Next Header: UDP
SetVar R_Ip6ConfigData.AcceptAnyProtocol              FALSE
SetVar R_Ip6ConfigData.AcceptIcmpErrors               TRUE
SetVar R_Ip6ConfigData.AcceptPromiscuous              FALSE
SetIpv6Address R_Ip6ConfigData.DestinationAddress     "::"
SetIpv6Address R_Ip6ConfigData.StationAddress         "::"
SetVar R_Ip6ConfigData.TrafficClass                   0
SetVar R_Ip6ConfigData.HopLimit                       64
SetVar R_Ip6ConfigData.FlowLabel                      0
SetVar R_Ip6ConfigData.ReceiveTimeout                 50000
SetVar R_Ip6ConfigData.TransmitTimeout                50000

#
# Configure Child with valid parameters
#
Ip6->Configure  "&@R_Ip6ConfigData, &@R_Status"
GetAck
set assert      [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Ip6->Configure - Conf - Configure Child  "               \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

EFI_IP6_COMPLETION_TOKEN                     R_Token
UINTN                                        R_NotifyContext
SetVar               R_NotifyContext         0

#
# Create an Event
#
BS->CreateEvent      "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert           [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion      $assert          $GenericAssertionGuid           \
                     "BS->CreateEvent -Conf- Create an Event "                  \
                     "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

SetVar                R_Token.Status                   "$EFI_SUCCESS"
EFI_IP6_TRANSMIT_DATA                                  R_TxData
SetIpv6Address        R_TxData.DestinationAddress      "2002::5"
SetVar                R_TxData.OverrideData            0
SetVar                R_TxData.ExtHdrsLength           0
SetVar                R_TxData.ExtHdrs                 0
SetVar                R_TxData.NextHeader              0
SetVar                R_TxData.DataLength              0
SetVar                R_TxData.FragmentCount           1

EFI_IP6_FRAGMENT_DATA                                  R_FragmentTable
SetVar                R_FragmentTable.FragmentLength   60
CHAR8                 R_FragmentBuffer(1600)
SetVar                R_FragmentBuffer                 "TransmitTest"
SetVar                R_TxData.FragmentTable           @R_FragmentTable
SetVar                R_Token.Packet                   &@R_TxData

#
# Check point:Call Transmit Function when Token->packet.TxData->DataLength is Zero.
#             EFI_INVALID_PARAMETER should be returned.
#
Ip6->Transmit        " &@R_Token, &@R_Status"
GetAck
set assert           [VerifyReturnStatus  R_Status  $EFI_INVALID_PARAMETER]
RecordAssertion      $assert           $Ip6TransmitConf9AssertionGuid001   \
                     "Ip6->Transmit -Conf- Call the function Transmit  withToken->Packet.TxData->DataLength is Zero " \
                     "ReturnStatus -$R_Status, ExpectedStatus -$EFI_INVALID_PARAMETER" 

#
# Destroy Child 
#
Ip6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert        [VerifyReturnStatus  R_Status $EFI_SUCCESS]
RecordAssertion   $assert  $GenericAssertionGuid                 \
                  "Ip6SB->DestroyChild - Conf - Destroy Child"              \
                  "RetrunStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# Close Event
#
BS->CloseEvent    "@R_Token.Event, &@R_Status"
GetAck
set assert        [VerifyReturnStatus   R_Status   $EFI_SUCCESS]
RecordAssertion   $assert     $GenericAssertionGuid             \
                  "BS->CloseEvent -Conf- Close the Event we created before"  \
                  "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

#
# End scope
#
EndScope          IP6_TRANSMIT_CONF9_CASE1_
#
# End log
#
EndLog
