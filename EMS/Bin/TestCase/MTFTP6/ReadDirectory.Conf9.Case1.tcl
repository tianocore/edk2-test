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
CaseGuid        9959729E-9B57-4c81-B662-2C4DE065B306
CaseName        ReadDirectory.Conf9.Case1
CaseCategory    MTFTP6
CaseDescription {Test ReadDirectory conformance of MTFTP6,invoke ReadDirectory()    \
                 when aborted by user for synchronous calling.  \
                 EFI_ABORTED should be returned. 
                }
################################################################################

proc CleanUpEutEnvironment {} {

#
# Destroy Child 
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

EUTClose

DestroyPacket
EndCapture
EndScope _MTFTP6_READDIRECTORY_CONFORMANCE9_CASE1_

#
# End Log
#
EndLog
}

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_READDIRECTORY_CONFORMANCE9_CASE1_

EUTSetup

UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                      \
                "Mtftp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Initialize the environment
#
set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]
RemoteEther    $targetmac
LocalEther     $hostmac
set LocalIP    "2002::2"
set RemoteIp   "2002::4321"
LocalIPv6      $LocalIP
RemoteIPv6     $RemoteIp

#
# Check Point: Call Configure function with valid parameters. 
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "2002::4321" 
SetVar            R_Mtftp6ConfigData.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          1
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call ReadDirectory when aborted by user for synchronous calling. \
#              EFI_ABORTED should be returned.
# 
EFI_MTFTP6_TOKEN                             R_Token

SetVar R_Token.Status                        $EFI_SUCCESS
SetVar R_Token.Event                         0
SetVar         R_Token.OverrideData          0
CHAR8                                        R_NameOfFile
SetVar         R_NameOfFile                  "Shell.efi"
SetVar         R_Token.Filename              &@R_NameOfFile
SetVar         R_Token.ModeStr               0
SetVar         R_Token.OptionCount           2
EFI_MTFTP6_OPTION                            R_OptionList(3)
CHAR8                                        R_OptionStr1(10)
CHAR8                                        R_OptionVal1(10)
SetVar         R_OptionStr1                  "blksize"
SetVar         R_OptionVal1                  "1024"
SetVar         R_OptionList(0).OptionStr     &@R_OptionStr1
SetVar         R_OptionList(0).ValueStr      &@R_OptionVal1
CHAR8                                        R_OptionStr2(10)
CHAR8                                        R_OptionVal2(10)
SetVar         R_OptionStr2                   "timeout"
SetVar         R_OptionVal2                   "2"
SetVar         R_OptionList(1).OptionStr     &@R_OptionStr2
SetVar         R_OptionList(1).ValueStr      &@R_OptionVal2
SetVar         R_Token.OptionList            &@R_OptionList
SetVar         R_Token.BufferSize            3
CHAR8                                        R_Buffer(3)
SetVar         R_Token.Buffer                &@R_Buffer
SetVar         R_Token.Context               0

#
# Start capture
#
set L_Filter "ether proto 0x86dd"
StartCapture CCB $L_Filter
Mtftp6->ReadDirectory "&@R_Token, 2, 1, 1, &@R_Status"

ReceiveCcbPacket CCB Mtftp6Packet 10
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
GetAck
set assert fail
RecordAssertion $assert $GenericAssertionGuid    \
                  "Mtftp6.ReadDirectory -conf- No packet received."

CleanUpEutEnvironment
return
}

#
# If have captured the packet. Test the conformance - EFI_ABORTED of 
# Mtftp6.ReadDirectroy, Client is passive client
# Need to set the option array as the following:
# set option_value_array(blksize) "1024"
# set option_value_len(blksize) 4
#
ParsePacket Mtftp6Packet -t udp -udp_sp client_port -udp_dp server_port
set client_prt $client_port

set option_value_array(blksize) "1024"
set option_value_len(blksize)   4
set option_value_array(timeout) "2"
set option_value_len(timeout)   1
SendPacket [ Mtftp6CreateOack $client_prt $EFI_MTFTP6_OPCODE_OACK]

#
# Capture the Ack for OACK
#
ReceiveCcbPacket CCB TempPacket1 20
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp6.ReadDirectory - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}

SendPacket [ Mtftp6CreateData 1780 $EFI_MTFTP6_OPCODE_DATA 1 8]

GetAck
set assert [VerifyReturnStatus R_Status $EFI_ABORTED]
RecordAssertion $assert $Mtftp6ReadDirectoryConf9AssertionGuid001       \
                "Mtftp6.ReadDirectory -Conf- Call ReadDirectory when aborted by user for synchronous calling."  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ABORTED"

CleanUpEutEnvironment