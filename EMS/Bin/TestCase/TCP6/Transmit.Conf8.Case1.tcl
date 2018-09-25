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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT

#
# test case Name, category, description, GUID...
#
CaseGuid           069573BD-322D-44b0-94B2-71288178D2B1
CaseName           Transmit.Conf8.Case1
CaseCategory       TCP6
CaseDescription    {This case is to test the conformance - EFI_ACCESS_DENIED.     \
                   -- Transmit must not succeed when instance has not connected in active mode.}
################################################################################

Include Tcp6/include/Tcp6.inc.tcl

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
  EndScope _TCP6_TRANSMIT_CONF8_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _TCP6_TRANSMIT_CONF8_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
UINTN                            R_Context

EFI_TCP6_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP6_CONFIG_DATA             R_Configure_Tcp6ConfigData

EFI_TCP6_COMPLETION_TOKEN        R_Connect_CompletionToken
EFI_TCP6_CONNECTION_TOKEN        R_Connect_ConnectionToken

EFI_TCP6_IO_TOKEN                R_Transmit_IOToken
EFI_TCP6_COMPLETION_TOKEN        R_Transmit_CompletionToken

set  L_FragmentLength            64
Packet                           R_Packet_Buffer
EFI_TCP6_TRANSMIT_DATA           R_TxData
EFI_TCP6_FRAGMENT_DATA           R_FragmentTable
CHAR8                            R_FragmentBuffer($L_FragmentLength)

#
# Create Child for TCP6 protocol
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
               
#
# Configure Tcp6 Instance in active mode
#
SetIpv6Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetVar          R_Configure_AccessPoint.StationPort        $DEF_EUT_PRT
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
                "Tcp6.Configure - Call Configure() in active mode with valid config data"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Tcp6.Transmit() to transmit a packet,
#             when the instance has not connected in active mode
#

set L_TCPTransmitPayload "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF"
SetVar R_TxData.Push                      FALSE
SetVar R_TxData.Urgent                    FALSE
SetVar R_TxData.DataLength                $L_FragmentLength
SetVar R_TxData.FragmentCount             1

SetVar R_FragmentBuffer                   $L_TCPTransmitPayload
SetVar R_FragmentTable.FragmentLength     $L_FragmentLength
SetVar R_FragmentTable.FragmentBuffer     &@R_FragmentBuffer
SetVar R_TxData.FragmentTable(0)          @R_FragmentTable

SetVar R_Packet_Buffer.TxData             &@R_TxData

BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Context,        \
                 &@R_Transmit_CompletionToken.Event, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.CreateEvent."                                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_Transmit_IOToken.CompletionToken @R_Transmit_CompletionToken
SetVar R_Transmit_IOToken.Packet_Buffer   @R_Packet_Buffer

Tcp6->Transmit {&@R_Transmit_IOToken, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Tcp6TransmitConf8AssertionGuid001                     \
                "Tcp6.Transmit - Call Transmit() with the instance has not connected in active mode ."     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

BS->CloseEvent {@R_Transmit_CompletionToken.Event, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "BS.DestroyEvent. "                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

CleanUpEUTEnvironmentBegin
CleanUpEUTEnvironmentEnd
