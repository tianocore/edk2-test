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
CaseGuid        0D35F523-993F-4fbb-9D15-4448CA1B6F3E
CaseName        WriteFile.Func2.Case4
CaseCategory    MTFTP4
CaseDescription {This case is to test the function of Mtftp4.WriteFile, Server \
                 replies WRQ with an error ACK(BufferLen < sizeof(UINT16))     \
                 instead of OACK, client should ignore this packet and continue\
                 the normal process.}
################################################################################

proc CleanUpEutEnvironment {} {

#
# DelEntryInArpCache
#
  DelEntryInArpCache
  
  Mtftp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
  GetAck

  EndCapture
  EndScope _MTFTP4_WRITEFILE_FUNCTION2_CASE4_
  EndLog
}

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_WRITEFILE_FUNCTION2_CASE4_

UINTN                            R_Status
UINTN                            R_Handle1
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

UINTN                            R_Context
EFI_MTFTP4_TOKEN                 R_Token

UINT64                           R_BufferSize
CHAR8                            R_Buffer(100)

CHAR8                            R_NameOfFile(20)
EFI_MTFTP4_OPTION                R_OptionList(8)
CHAR8                            R_OptionStr0(10)
CHAR8                            R_ValueStr0(10)
CHAR8                            R_OptionStr1(10)
CHAR8                            R_ValueStr1(10)
CHAR8                            R_ModeStr(8)

#
# Add an entry in ARP cache.
#
AddEntryInArpCache

#
# Mtftp4
#
LocalEther          [GetHostMac]
RemoteEther         [GetTargetMac]
LocalIp             192.168.88.1
RemoteIp            192.168.88.88

Mtftp4ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1
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
SetVar R_MtftpConfigData.TryCount            2
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_NameOfFile               "temp"
SetVar R_ModeStr                  "octet"
SetVar R_BufferSize               100

SetVar R_OptionStr0               "timeout"
SetVar R_ValueStr0                "2"
SetVar R_OptionList(0).OptionStr  &@R_OptionStr0
SetVar R_OptionList(0).ValueStr   &@R_ValueStr0
SetVar R_OptionStr1               "blksize"
SetVar R_ValueStr1                "1024"
SetVar R_OptionList(1).OptionStr  &@R_OptionStr1
SetVar R_OptionList(1).ValueStr   &@R_ValueStr1

SetVar R_Token.OverrideData       0
SetVar R_Token.ModeStr            &@R_ModeStr
SetVar R_Token.Filename           &@R_NameOfFile
SetVar R_Token.OptionCount        2
SetVar R_Token.OptionList         &@R_OptionList
SetVar R_Token.BufferSize         @R_BufferSize
SetVar R_Token.Buffer             &@R_Buffer
SetVar R_Token.Context            NULL


set L_Filter "udp and src host 192.168.88.88"
StartCapture CCB $L_Filter

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}


ReceiveCcbPacket CCB TempPacket1 20
if { ${CCB.received} == 0 } {

#
# If have not captured the packet. Fail
#
  GetAck
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.WriteFile - It should transfer a packet, but not."
  
  CleanUpEutEnvironment
  return
}

#
# If have captured the packet. upload a packet with override configuration data.
#
set client_prt [ Mtftp4GetSrcPort TempPacket1 ]

set option_value_array(timeout) "2"
set option_value_len(timeout) 1

set option_value_array(blksize) "1024"
set option_value_len(blksize) 4

SendPacket [ Mtftp4CreateOack $client_prt $EFI_MTFTP4_OPCODE_OACK]

#
# Capture data packet and check it, then respond with an ACK packet.
#
ReceiveCcbPacket CCB TempPacket2 20
if { ${CCB.received} == 0 } {

#
# If have not captured the packet. Fail
#
  GetAck
  set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.WriteFile - Server responses with normal ACK packet."\
                  "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.WriteFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}
ValidateData TempPacket2

#
# If have captured the packet. Server reply WRQ with an error ACK(BufferLen <
# sizeof(UINT16)) instead of OACK, client should ignore this packet and continue
# the normal process.
#
set blk_number 0
CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_ACK
CreatePayload _blk_number Data 1 $blk_number
ConcatPayload mtftp4_ack_pld OpCode _blk_number
CreatePacket  mtftp4_ack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $client_prt       \
              -udp_payload mtftp4_ack_pld

SendPacket mtftp4_ack

set blk_number 1
SendPacket [ Mtftp4CreateAck $client_prt $blk_number] 

GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp4WriteFileFuncAssertionGuid007                   \
                "Mtftp4.WriteFile - Server replies DATA packet with an error ACK\
                (BufferLen < sizeof(UINT16)) instead of OACK, client should    \
                ignore this packet and continue the normal process."           \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

CleanUpEutEnvironment
