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
CaseGuid          D19BB885-B2D4-4b09-BB07-BCD814358151
CaseName          GetInfo.Conf7.Case1
CaseCategory      MTFTP4
CaseDescription   {This case is to test the EFI_UNSUPPORTED conformance of  \
	                 Mtftp4.GetInfo - one or more options in the optionlist are in\
	                 the unsupported list of structure EFI_MTFTP4_MODE_DATA.}
################################################################################

proc CleanUpEutEnvironment {} {
  DelEntryInArpCache
  
  Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
  GetAck

  EndCapture
  EndScope _MTFTP4_GETINFO_CONFORMANCE7_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_GETINFO_CONFORMANCE7_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData
EFI_MTFTP4_OVERRIDE_DATA         R_OverrideData
UINT8                            R_OptionCount
EFI_MTFTP4_OPTION                R_OptionList(8)
UINT32                           R_PacketLength
POINTER                          R_Packet

CHAR8                            R_NameOfFile(20)
CHAR8                            R_OptionStr0(10)
CHAR8                            R_ValueStr0(10)
CHAR8                            R_OptionStr1(10)
CHAR8                            R_ValueStr1(10)

#
# Initialization on ENTS side.
#
LocalEther  $DEF_OS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIp     $DEF_OS_IP_ADDR
RemoteIp    $DEF_EUT_IP_ADDR

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

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
# Check point
# - ModeStr is set to NULL
#

SetVar R_NameOfFile                         "TestFile"
SetVar R_OptionCount                         2
                                            
SetVar R_OptionStr0                         "restart"
SetVar R_ValueStr0                          "5"
SetVar R_OptionList(0).OptionStr            &@R_OptionStr0
SetVar R_OptionList(0).ValueStr             &@R_ValueStr0
SetVar R_OptionStr1                         "session"
SetVar R_ValueStr1                          "42"
SetVar R_OptionList(1).OptionStr            &@R_OptionStr1
SetVar R_OptionList(1).ValueStr             &@R_ValueStr1


SetIpv4Address R_OverrideData.GatewayIp      "0.0.0.0"
SetIpv4Address R_OverrideData.ServerIp       "192.168.88.1"
SetVar R_OverrideData.ServerPort             0
SetVar R_OverrideData.TryCount               0
SetVar R_OverrideData.TimeoutValue           0

set L_Filter "udp and src host 192.168.88.88"
StartCapture CCB $L_Filter

Mtftp4->GetInfo {&@R_OverrideData, &@R_NameOfFile, NULL, @R_OptionCount,       \
                 &@R_OptionList, &@R_PacketLength, &@R_Packet, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_UNSUPPORTED]
RecordAssertion $assert $Mtftp4GetInfoConfAssertionGuid012                     \
                "Mtftp4.GetInfo() - returns EFI_UNSUPPORTED with one or more   \
                 options in the optionlist are in the unsupported list of      \
                 structure EFI_MTFTP4_MODE_DATA."                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_UNSUPPORTED"

#
# Clean up the environment
#   
CleanUpEutEnvironment