# 
#  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
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
CaseGuid        AAEEC5F0-B4B2-48d9-A1CB-1696C932E931
CaseName        GetInfo.Func1.Case1
CaseCategory    MTFTP6
CaseDescription {Test the GetInfo Function of MtftP6 -Invoke GetInfo()  \
                 with valid parameters.EFI_SUCCESS should be returned.
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
EndScope _MTFTP6_GETINFO_FUNC1_CASE1_

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

BeginScope _MTFTP6_GETINFO_FUNC1_CASE1_

EUTSetup

UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                    \
                "Mtftp6SB.CreateChild - Create Child "                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Initialization on ENTS side.
#
LocalEther  $DEF_OS_MAC_ADDR
RemoteEther $DEF_EUT_MAC_ADDR
LocalIPv6   $DEF_OS_IP_ADDR
RemoteIPv6  $DEF_EUT_IP_ADDR

#
# Check Point: Call Configure function with valid parameters. 
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "2002::4321" 
SetVar            R_Mtftp6ConfigData.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          3
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call GetInfo function with valid parameters.
#              EFI_SUCCESS should be returned. 
#
EFI_MTFTP6_OVERRIDE_DATA         R_OverrideData

SetIpv6Address    R_OverrideData.ServerIp       "2002::2"
SetVar            R_OverrideData.ServerPort     1781
SetVar            R_OverrideData.TryCount       3
SetVar            R_OverrideData.TimeoutValue   1000

CHAR8                            R_Filename(20)
SetVar R_Filename                "Shell.efi"

UINT8                            R_OptionCount
SetVar R_OptionCount             2

EFI_MTFTP6_OPTION                R_OptionList(8)

CHAR8                            R_OptionStr0(10)
CHAR8                            R_OptionVal0(10)
SetVar R_OptionStr0              "timeout"
SetVar R_OptionVal0              "2"
SetVar R_OptionList(0).OptionStr &@R_OptionStr0
SetVar R_OptionList(0).ValueStr  &@R_OptionVal0
CHAR8                            R_OptionStr1(10)
CHAR8                            R_OptionVal1(10)
SetVar R_OptionStr1              "tsize"
SetVar R_OptionVal1              "0"
SetVar R_OptionList(1).OptionStr &@R_OptionStr1
SetVar R_OptionList(1).ValueStr  &@R_OptionVal1

UINT32                           R_PacketLength
POINTER                          R_Packet

#
# Start capture
#
set L_Filter "ether proto 0x86dd"
StartCapture CCB $L_Filter

Mtftp6->GetInfo "&@R_OverrideData, &@R_Filename, NULL, @R_OptionCount, \
                                     &@R_OptionList, &@R_PacketLength, &@R_Packet, &@R_Status"

ReceiveCcbPacket CCB Mtftp6Packet 10
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
GetAck
set assert fail
RecordAssertion $assert $GenericAssertionGuid    \
                  "Mtftp6.GetInfo -conf- No packet received."

CleanUpEutEnvironment
return
}

DumpPacket Mtftp6Packet
#
# If have captured the packet. Send back an MTFTPv6 OACK packet.
#
ParsePacket Mtftp6Packet -t udp -udp_sp client_port -udp_dp server_port
set client_prt $client_port

set option_value_array(tsize)   "0"
set option_value_len(tsize)     1
set option_value_array(timeout) "2"
set option_value_len(timeout)   1
SendPacket [ Mtftp6CreateOack $client_prt $EFI_MTFTP6_OPCODE_OACK]

#
# Capture the Ack for OACK
#
ReceiveCcbPacket CCB TempPacket1 10
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp6.GetInfo - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}

GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6GetInfoFunc1AssertionGuid001    \
                "Mtftp6.GetInfo -Func- Call GetInfo with valid parameters"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: the Packet returned should include the valid info of "timeout"\
#              and "tsize"
#
UINT32                      R_Count
POINTER                     R_List

Mtftp6->ParseOptions "@R_PacketLength, @R_Packet, &@R_Count, &@R_List, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6GetInfoFunc1AssertionGuid002           \
               "Mtftp6.ParseOptions() -Func- Call ParseOption with valid parameters."   \
               "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

GetVar R_Count
set assert pass
if {$R_Count != 2} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                          \
                "There are two Options in the returned packet."

EFI_MTFTP6_OPTION   R_OptList(2)
UINTN               R_CopyLen
SetVar  R_CopyLen   [Sizeof R_OptList]
GetVar  R_CopyLen
BS->CopyMem "&@R_OptList, @R_List, @R_CopyLen, &@R_Status"
GetAck

GetVar  R_OptList(0)
GetVar  R_OptList(1)

EFI_MTFTP6_OPTION   R_Option1
EFI_MTFTP6_OPTION   R_Option2
SetVar  R_CopyLen   [Sizeof R_Option1]
BS->CopyMem "&@R_Option1, &@R_OptList(0), @R_CopyLen, &@R_Status"
GetAck
BS->CopyMem "&@R_Option2, &@R_OptList(1), @R_CopyLen, &@R_Status"
GetAck

GetVar R_Option1.ValueStr
GetVar R_Option2.ValueStr

UINT8  R_Val1
UINT8  R_Val2
SetVar R_CopyLen   [Sizeof R_Val1]
BS->CopyMem "&@R_Val1, @R_Option1.ValueStr, @R_CopyLen, &@R_Status"
GetAck
BS->CopyMem "&@R_Val2, @R_Option2.ValueStr, @R_CopyLen, &@R_Status"
GetAck

GetVar R_Val1
GetVar R_Val2

# In the struct of EFI_MTFTP6_OPTION,the member OptionStr is the pointer      \
# to the ASCIIZ MTFTPv6 option string; Member ValueStr is the pointer to      \
# the ASCIIZ MTFTPv6 value string.In ASCII table the character'2' is 32 in Hex.
set assert pass
if { ${R_Val1} != 0x32} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid   \
                "The timeout value should be 2."

set assert pass
if { ${R_Val2} != 0x30} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid   \
                "The tsize value should be 0."
CleanUpEutEnvironment
