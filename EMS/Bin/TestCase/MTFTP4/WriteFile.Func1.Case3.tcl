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
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        2321ADC7-041B-4b48-9C6D-286E5BA88DF6
CaseName        WriteFile.Func1.Case3
CaseCategory    MTFTP4
CaseDescription {This case is to test the function of Mtftp4.WriteFile - upload \
                 a packet with override configuration data.}
################################################################################

proc CleanUpEutEnvironment {} {

#
# DelEntryInArpCache
#
  DelEntryInArpCache
  
  Mtftp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
  GetAck

  EndCapture
  EndScope _MTFTP4_WRITEFILE_FUNCTION1_CASE3_
  EndLog
}

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_WRITEFILE_FUNCTION1_CASE3_

UINTN                            R_Status
UINTN                            R_Handle1
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

UINTN                            R_Context
EFI_MTFTP4_TOKEN                 R_Token
EFI_MTFTP4_OVERRIDE_DATA         OverrideData

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
SetIpv4Address R_MtftpConfigData.ServerIp    "192.168.88.2"
SetVar R_MtftpConfigData.InitialServerPort   69
SetVar R_MtftpConfigData.TryCount            2
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

SetVar R_NameOfFile                          "temp"
SetVar R_ModeStr                             "octet"
SetVar R_BufferSize                          100
                                           
SetVar R_OptionStr0                          "timeout"
SetVar R_ValueStr0                           "2"
SetVar R_OptionList(0).OptionStr             &@R_OptionStr0
SetVar R_OptionList(0).ValueStr              &@R_ValueStr0
SetVar R_OptionStr1                          "blksize"
SetVar R_ValueStr1                           "1024"
SetVar R_OptionList(1).OptionStr             &@R_OptionStr1
SetVar R_OptionList(1).ValueStr              &@R_ValueStr1

SetIpv4Address OverrideData.GatewayIp        "0.0.0.0"
SetIpv4Address OverrideData.ServerIp         "192.168.88.1"
SetVar OverrideData.ServerPort               0
SetVar OverrideData.TryCount                 0
SetVar OverrideData.TimeoutValue             0

SetVar R_Token.OverrideData                  &@OverrideData
SetVar R_Token.ModeStr                       &@R_ModeStr
SetVar R_Token.Filename                      &@R_NameOfFile
SetVar R_Token.OptionCount                   2
SetVar R_Token.OptionList                    &@R_OptionList
SetVar R_Token.BufferSize                    @R_BufferSize
SetVar R_Token.Buffer                        &@R_Buffer
SetVar R_Token.Context                       NULL

set L_Filter "udp and src host 192.168.88.88"
StartCapture CCB $L_Filter

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}

ReceiveCcbPacket CCB TempPacket1 20
if { ${CCB.received} == 0 } {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
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
# Capture data packet and check it, then response with an ACK packet.
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

set blk_number 1
SendPacket [ Mtftp4CreateAck $client_prt $blk_number]

GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp4WriteFileFuncAssertionGuid003                   \
                "Mtftp4.WriteFile - upload a packet with override configuration\
                 data."                                                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

CleanUpEutEnvironment
