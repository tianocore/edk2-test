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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT 
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        1253C922-40DB-4bcd-9D81-19EC13DD2E4A
CaseName        CreateChild.Func1.Case1
CaseCategory    Udp4
CaseDescription {Test the CreateChild Function of UDP4 - Invoke CreateChild()\
                 to create three instances.}
################################################################################

Include UDP4/include/Udp4.inc.tcl

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _UDP4_CREATECHILD_FUNCTION1_CASE1_


UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
UINTN                            R_Handle3
EFI_UDP4_CONFIG_DATA             R_Udp4ConfigData

SetVar R_Udp4ConfigData.AcceptBroadcast             TRUE
SetVar R_Udp4ConfigData.AcceptPromiscuous           TRUE
SetVar R_Udp4ConfigData.AcceptAnyPort               TRUE
SetVar R_Udp4ConfigData.AllowDuplicatePort          TRUE
SetVar R_Udp4ConfigData.TypeOfService               0
SetVar R_Udp4ConfigData.TimeToLive                  8
SetVar R_Udp4ConfigData.DoNotFragment               TRUE
SetVar R_Udp4ConfigData.ReceiveTimeout              2
SetVar R_Udp4ConfigData.TransmitTimeout             2
SetVar R_Udp4ConfigData.UseDefaultAddress           FALSE
SetIpv4Address R_Udp4ConfigData.StationAddress      "192.168.88.1"
SetIpv4Address R_Udp4ConfigData.SubnetMask          "255.255.255.0"
SetVar R_Udp4ConfigData.StationPort                 999
SetIpv4Address R_Udp4ConfigData.RemoteAddress       "192.168.88.2"
SetVar R_Udp4ConfigData.RemotePort                  666


Udp4ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Create Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Create Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure "&@R_Udp4ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->CreateChild "&@R_Handle3, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle3
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp4CreateChildFunc1AssertionGuid001                  \
                "Udp4SB.CreateChild - Func - Create Child 3"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4->Configure {&@R_Udp4ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.CreateChild - Func - Config Child 3"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"  

Udp4ServiceBinding->DestroyChild {@R_Handle2, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 2"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp4ServiceBinding->DestroyChild {@R_Handle3, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Udp4SB.DestroyChild - Destroy Child 3"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - EFI_SUCCESS" 

#
# End scope
#
EndScope  _UDP4_CREATECHILD_FUNCTION1_CASE1_

#
# EndLog
#
EndLog
                                                                                                                                                                                                                                                             
