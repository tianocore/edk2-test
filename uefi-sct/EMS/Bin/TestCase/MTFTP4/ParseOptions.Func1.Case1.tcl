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
CaseGuid        618678D8-7612-432b-A65A-EF5F74CB10C3
CaseName        ParseOptions.Func1.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the function of Mtftp4.ParseOptions with \
                the packet being an OACK packet.}
################################################################################
#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_PARSEOPTIONS_FUNCTION1_CASE1_
#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData
UINT32                           R_PacketLen
EFI_MTFTP4_PACKET                R_Packet
UINT32                           R_OptionCount
POINTER                          R_OptionList
CHAR8                            R_BlkSize(8)
CHAR8                            R_BlkSizeValue(5)
POINTER                          R_Temp

#
# Mtftp4
#
Mtftp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_MtftpConfigData.UseDefaultSetting   FALSE
SetIpv4Address R_MtftpConfigData.StationIp   "192.168.88.88"
SetIpv4Address R_MtftpConfigData.SubnetMask  "255.255.255.0"
SetVar R_MtftpConfigData.LocalPort           2048
SetIpv4Address R_MtftpConfigData.GatewayIp   "0.0.0.0"
SetIpv4Address R_MtftpConfigData.ServerIp    "192.168.88.1"
SetVar R_MtftpConfigData.InitialServerPort   69
SetVar R_MtftpConfigData.TryCount            10
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# check point
#
SetVar R_PacketLen          15
SetVar R_Packet.OpCode      0x600
SetVar R_Packet.Oack.OpCode 0x600
SetVar R_BlkSize            "blksize"
SetVar R_BlkSizeValue       "1428"

BS->CopyMem {&@R_Packet.Oack.Data, &@R_BlkSize, 8, &@R_Status}
GetAck

SetVar R_Temp &@R_Packet.Oack.Data
GetVar R_Temp
set tmp $R_Temp
set tmp [expr $tmp + 8]
SetVar R_Temp $tmp
BS->CopyMem {@R_Temp, &@R_BlkSizeValue, 5, &@R_Status}
GetAck

Mtftp4->ParseOptions {@R_PacketLen, &@R_Packet, &@R_OptionCount, &@R_OptionList,\
                     &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]

GetVar R_OptionCount
if {$R_OptionCount != 1} {
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.ParseOptions - The return OptionCount is wrong.      \
                   OptionCount - $R_OptionCount, ExpectOptionCount - 1"
}

RecordAssertion $assert $Mtftp4ParseOptionsFuncAssertionGuid001                \
                "Mtftp4.ParseOptions - OACK packet."                           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

BS->FreePool {@R_OptionList, &@R_Status}
GetAck

Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP4_PARSEOPTIONS_FUNCTION1_CASE1_

#
# End Log
#
EndLog
