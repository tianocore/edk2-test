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
CaseGuid        3675C9C1-1B23-40de-B5F8-70F346CEA5FA
CaseName        ReadFile.Func2.Case1
CaseCategory    MTFTP6
CaseDescription {Test ReadFile function of MTFTP6,invoke ReadFile()with valid\
                 parameters for asynchronous calling.EFI_SUCCESS should be returned.
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
EndScope _MTFTP6_READFILE_FUNCTION2_CASE1_

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

BeginScope _MTFTP6_READFILE_FUNCTION2_CASE1_

EUTSetup

UINTN                            R_Status
UINTN                            R_Handle

#
# Create child
#
Mtftp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

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
# Check Point: Call ReadFile with valid parameters for asynchronous \
#              calling.EFI_SUCCESS should be returned.
# 
EFI_MTFTP6_TOKEN                             R_Token

UINTN                                        R_NotifyContext
SetVar               R_NotifyContext         0
#
# Create an Event
#
BS->CreateEvent      "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_NotifyContext, &@R_Token.Event, &@R_Status"
GetAck
set assert           [VerifyReturnStatus  R_Status  $EFI_SUCCESS]
RecordAssertion      $assert          $GenericAssertionGuid           \
                     "BS->CreateEvent -Func- Create an Event "                  \
                     "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

SetVar R_Token.Status                        $EFI_SUCCESS
SetVar         R_Token.OverrideData          0
CHAR8                                        R_NameOfFile(20)
SetVar         R_NameOfFile                  "Shell.efi"
SetVar         R_Token.Filename              &@R_NameOfFile
SetVar         R_Token.ModeStr               0
SetVar         R_Token.OptionCount           2
EFI_MTFTP6_OPTION                            R_OptionList(2)
CHAR8                                        R_OptionStr1(10)
CHAR8                                        R_OptionVal1(10)
SetVar         R_OptionStr1                   "blksize"
SetVar         R_OptionVal1                   "1024"
SetVar         R_OptionList(0).OptionStr     &@R_OptionStr1
SetVar         R_OptionList(0).ValueStr      &@R_OptionVal1
CHAR8                                        R_OptionStr2(10)
CHAR8                                        R_OptionVal2(10)
SetVar         R_OptionStr2                   "timeout"
SetVar         R_OptionVal2                   "6"
SetVar         R_OptionList(1).OptionStr     &@R_OptionStr2
SetVar         R_OptionList(1).ValueStr      &@R_OptionVal2
SetVar         R_Token.OptionList            &@R_OptionList
SetVar         R_Token.BufferSize            13
SetVar         R_Token.Buffer                0
EFI_MTFTP6_DATA_HEADER                       R_Context
SetVar         R_Token.Context               &@R_Context

#
# Start capture
#
set L_Filter "ether proto 0x86dd"
StartCapture CCB $L_Filter

Mtftp6->ReadFile "&@R_Token, 1, 4, 4, &@R_Status"
GetAck

ReceiveCcbPacket CCB Mtftp6Packet 10
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
set assert fail
RecordAssertion $assert $GenericAssertionGuid    \
                  "Mtftp6.ReadFile -conf- No packet received."

CleanUpEutEnvironment
return
}

#
# If have captured the packet. Server response with a normal OACK packet 
# Need to set the option array as the following:
# set option_value_array(blksize) "1024"
# set option_value_len(blksize) 4
#
ParsePacket Mtftp6Packet -t udp -udp_sp client_port -udp_dp server_port
EndCapture
set client_prt $client_port

set option_value_array(blksize) "1024"
set option_value_len(blksize)   4
set option_value_array(timeout) "6"
set option_value_len(timeout)   1
SendPacket [ Mtftp6CreateOack $client_prt $EFI_MTFTP6_OPCODE_OACK]

#
# Capture the Ack for OACK
#
StartCapture CCB $L_Filter
ReceiveCcbPacket CCB TempPacket1 10
if { ${CCB.received} == 0} {
#
# If have not captured the packet. Fail
#
  set assert fail
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Mtftp6.ReadFile - It should transfer a packet, but not."

  CleanUpEutEnvironment
  return
}

SendPacket [ Mtftp6CreateData 1780 $EFI_MTFTP6_OPCODE_DATA 1 8]
Stall 5

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6ReadFileFunc2AssertionGuid001    \
                "Mtftp6.ReadFile -Conf- Call ReadFile with valid parameters for asynchronous calling"\
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


set assert pass
GetVar R_NotifyContext 
if {$R_NotifyContext != 1} {
   set assert fail
}
RecordAssertion $assert $Mtftp6ReadFileFunc2AssertionGuid002     \
                "When received data,the event will be signaled and the value of R_NotifyContext will increase."

set assert pass
GetVar R_Token.Status
if {${R_Token.Status} != $EFI_SUCCESS} {
   set assert fail
}
RecordAssertion $assert $Mtftp6ReadFileFunc2AssertionGuid003       \
                "When returned, the R_Token.Status should be EFI_SUCCESS"

CleanUpEutEnvironment
