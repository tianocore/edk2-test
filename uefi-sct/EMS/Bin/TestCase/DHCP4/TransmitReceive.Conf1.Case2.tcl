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
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        fec026ea-0ceb-468c-bd2f-71069fe5c11a
CaseName        TransmitReceive.Conf1.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PARAMETER  \
                -- Packet is NULL}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_TRANSMITRECEIVE_CONF1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_TRANSMITRECEIVE_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                               R_Status
UINTN                               R_Handle
                                    
EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN    R_Token
EFI_DHCP4_LISTEN_POINT              R_ListenPoint
EFI_DHCP4_PACKET                    R_Packet

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Call [DHCP4] -> TransmitReceive with the invalid parameters
# o	RemoteAddress is ZERO
#
SetIpv4Address  R_ListenPoint.ListenAddress   "0.0.0.0"
SetIpv4Address  R_ListenPoint.SubnetMask      "255.255.255.255"
SetVar          R_ListenPoint.ListenPort      68

SetVar  R_Token.Status                        0
SetVar  R_Token.CompletionEvent               0
SetIpv4Address  R_Token.RemoteAddress         "192.168.1.34" 
SetVar  R_Token.RemotePort                    0
SetVar  R_Token.ListenPointCount              1
SetVar  R_Token.ListenPoints                  &@R_ListenPoint
SetVar  R_Token.TimeoutValue                  10;   #TimeoutValue is 10s
SetVar  R_Token.Packet                        0

#
# Check Point: Call Dhcp4.TransmitReceive while RemoteAddress is ZERO.
#
Dhcp4->TransmitReceive "&@R_Token, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4TransmitReceiveConf1AssertionGuid002             \
                "Dhcp4.TransmitReceive - Call TransmitReceive while            \
                Packet is NULL"                                                \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment
