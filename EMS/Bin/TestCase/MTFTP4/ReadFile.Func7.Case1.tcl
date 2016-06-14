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
CaseGuid        CFCE49F5-BE6C-4949-989F-6F41EE0B759E
CaseName        ReadFile.Func7.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the Function of Mtftp4.ReadFile, Active  \
                 client receive an MTFTPv4 OACK packet.}
################################################################################

proc CleanUpEutEnvironment {} {
#
# DelEntryInArpCache
#
  DelEntryInArpCache
  
  Mtftp4ServiceBinding->DestroyChild {@R_Handle1, &@R_Status}
  GetAck

  EndCapture
  EndScope _MTFTP4_READFILE_FUNCTION7_CASE1_
  EndLog
}

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_READFILE_FUNCTION7_CASE1_

UINTN                            R_Status
UINTN                            R_Handle1
EFI_MTFTP4_CONFIG_DATA           R_MtftpConfigData

UINTN                            R_Context
EFI_MTFTP4_TOKEN                 R_Token

CHAR8                            R_NameOfFile(20)
EFI_MTFTP4_OPTION                R_OptionList(8)
CHAR8                            R_OptionStr0(10)
CHAR8                            R_ValueStr0(10)
CHAR8                            R_OptionStr1(10)
CHAR8                            R_ValueStr1(10)
CHAR8                            R_OptionStr2(10)
CHAR8                            R_ValueStr2(10)
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
SetVar R_MtftpConfigData.TryCount            10
SetVar R_MtftpConfigData.TimeoutValue        2

Mtftp4->Configure {&@R_MtftpConfigData, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4.Configure - Normal operation."                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


SetVar R_NameOfFile               "TestFile"
SetVar R_ModeStr                  "octet"

SetVar R_OptionStr0               "multicast"
SetVar R_ValueStr0                ""
SetVar R_OptionList(0).OptionStr  &@R_OptionStr0
SetVar R_OptionList(0).ValueStr   &@R_ValueStr0
SetVar R_OptionStr1               "timeout"
SetVar R_ValueStr1                "2"
SetVar R_OptionList(1).OptionStr  &@R_OptionStr1
SetVar R_OptionList(1).ValueStr   &@R_ValueStr1
SetVar R_OptionStr2               "blksize"
SetVar R_ValueStr2                "1024"
SetVar R_OptionList(2).OptionStr  &@R_OptionStr2
SetVar R_OptionList(2).ValueStr   &@R_ValueStr2

SetVar R_Token.OverrideData       0
SetVar R_Token.ModeStr            &@R_ModeStr
SetVar R_Token.Filename           &@R_NameOfFile
SetVar R_Token.OptionCount        3
SetVar R_Token.OptionList         &@R_OptionList
SetVar R_Token.BufferSize         0
SetVar R_Token.Buffer             0
SetVar R_Token.Context            NULL

set L_Filter "udp and src host 192.168.88.88"
StartCapture CCB $L_Filter

Mtftp4->ReadFile {&@R_Token, 1, 1, 1, &@R_Status}

ReceiveCcbPacket CCB TempPacket1 20
if { ${CCB.received} == 0 } {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.ReadFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}

#
# If have captured the packet, Active client receive an MTFTPv4 OACK packet.
# Need to set the option array as the following:
# set option_value_array(blksize) "1024"
# set option_value_len(blksize) 4
#
set client_prt [ Mtftp4GetSrcPort TempPacket1 ]

set option_value_array(multicast) "234.5.6.7,1234,1"
set option_value_len(multicast) 16

set option_value_array(timeout) "2"
set option_value_len(timeout) 1

set option_value_array(blksize) "1024"
set option_value_len(blksize) 4

SendPacket [ Mtftp4CreateOack $client_prt $EFI_MTFTP4_OPCODE_OACK]

#
# Capture ack and response with data packet.(only one data packet)
#
ReceiveCcbPacket CCB TempPacket2 20
if { ${CCB.received} == 0 } {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.ReadFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}
#
# the second parameter indicates the block number.
#
ValidateAck TempPacket2 0 ;

RemoteIp            192.168.88.88
RemoteEther         [GetTargetMac]
SendPacket [ Mtftp4CreateOack $client_prt $EFI_MTFTP4_OPCODE_OACK] 

ReceiveCcbPacket CCB TempPacket3 20
if { ${CCB.received} == 0 } {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.ReadFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}
#
# the second parameter indicates the block number.
#
ValidateAck TempPacket3 0 

RemoteIp            234.5.6.7
RemoteEther         01:00:5e:05:06:07

SendPacket [ Mtftp4CreateData 1234 $EFI_MTFTP4_OPCODE_DATA 1 100]

ReceiveCcbPacket CCB TempPacket4 20
if { ${CCB.received} == 0 } {
#
# If have not captured the packet. Fail
#
  GetAck
  GetVar R_Status
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp4.ReadFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}

#
# the second parameter indicates the block number.
#
ValidateAck TempPacket4 1 

GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp4ReadFileFuncAssertionGuid014                    \
                "Mtftp4.ReadFile - Active client receive an MTFTPv4 OACK packet."\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

CleanUpEutEnvironment