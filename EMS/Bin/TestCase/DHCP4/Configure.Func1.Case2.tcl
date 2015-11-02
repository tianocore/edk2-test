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
CaseGuid        e60b8113-9e34-4d2e-b485-dc472722c5d6
CaseName        Configure.Func1.Case2
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Validate the Configure Data effect before and after call    \
                Dhcp->start to start the Configuration, Call Dhcp->stop before \
                Call Dhcp->start again.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

proc CleanUpEutEnvironment {} {
  Dhcp4->Stop "&@R_Status"
  GetAck

  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndCapture
  EndScope _DHCP4_CONFIGURE_FUNC1
  EndLog
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope _DHCP4_CONFIGURE_FUNC1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

EFI_DHCP4_MODE_DATA              R_ModeData

EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)

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
# Get Startup Configuration
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck

#
# Verify Startup Configuration
#
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] != 0 } {
  set assert fail
} else {
  GetVar  R_ModeData
  puts "Startup DHCP Mode Data"
  puts "State:                    ${R_ModeData.State}"
  puts "DiscoverTryCount:         ${R_ModeData.ConfigData.DiscoverTryCount}"
  puts "RequestTryCount:          ${R_ModeData.ConfigData.RequestTryCount}"
  puts "OptionCount:              ${R_ModeData.ConfigData.OptionCount}"
  puts "ClientAddress:            [GetIpv4Address R_ModeData.ClientAddress]"
  puts "ServerAddress:            [GetIpv4Address R_ModeData.ServerAddress]"
  puts "RouterAddress:            [GetIpv4Address R_ModeData.RouterAddress]"
  puts "SubnetMask:               [GetIpv4Address R_ModeData.SubnetMask]"
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Startup Configuation"                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4]->Configure to initialize the child with the following parameters
# o	DiscoverRetryCount=2, DiscoverTimeout=5,10
# o	RequestRetryCount=2, RequestTimeout=5,10
# o	ClientAddress=0.0.0.0
# o	Dhcp4CallBack=NULL
# o	OptionCount=1, OptionList=ClientIdentifier
#
SetVar         R_Timeout(0)                       5
SetVar         R_Timeout(1)                       10
SetVar         R_ConfigData.DiscoverTryCount      2
SetVar         R_ConfigData.RequestTryCount       2
SetVar         R_ConfigData.DiscoverTimeout       &@R_Timeout
SetVar         R_ConfigData.RequestTimeout        &@R_Timeout
SetVar         R_ConfigData.Dhcp4Callback         0
SetVar         R_ConfigData.OptionCount           1

#
# Build an option of ClientIdentifier
#
UINT8          R_ClientIdOpt(9)
SetVar         R_ClientIdOpt                      { 61 7 1 0 1 2 3 4 5 }
POINTER        R_OptionPtr                        
SetVar         R_OptionPtr                        &@R_ClientIdOpt
SetVar         R_ConfigData.OptionList            &@R_OptionPtr
SetIpv4Address R_ConfigData.ClientAddress         "0.0.0.0"

#
# Check Point: Call Dhcp4.Configure Configure Child 1.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc1AssertionGuid002                   \
                "Dhcp4.Configure - Start Child configuration."                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> GetModeData () to get its configuration data
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck

#
# Verify Configured Parameters
#
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS];
puts "the assert is a $assert"
if { [string compare -nocase $assert "pass"] == 0} {
  GetVar R_ModeData.ConfigData.DiscoverTryCount
  puts "DiscoverTryCount: ${R_ModeData.ConfigData.DiscoverTryCount}"
  if { ${R_ModeData.ConfigData.DiscoverTryCount} != 2 } {
    set assert fail
    puts "DiscoverTryCount ${R_ModeData.ConfigData.DiscoverTryCount}!=2"
  } else {
    GetVar R_ModeData.ConfigData.RequestTryCount
    puts "RequestTryCount: ${R_ModeData.ConfigData.RequestTryCount}"
    if { ${R_ModeData.ConfigData.RequestTryCount} != 2 } {
      puts "RequestTryCount ${R_ModeData.ConfigData.RequestTryCount}!=2"
      set assert fail
    } else {
      set tempClientAddr [GetIpv4Address R_ModeData.ClientAddress]
      puts "the client: $tempClientAddr"
      if { [string compare $tempClientAddr "0.0.0.0"] != 0} {
        set assert fail
      }
    }
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Configured Configuation"              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "ReturnDiscoverTryCount -                                      \
                ${R_ModeData.ConfigData.DiscoverTryCount},                     \
                ExpectedDiscoverTryCount - 2, ReturnRequestTryCount -          \
                ${R_ModeData.ConfigData.RequestTryCount},                      \
                ExpectedRequestTryCount - 2, ReturnClientAddr - $tempClientAddr\
                , ExpectedClientAddr - 0.0.0.0"

#               
# Call [DHCP4] -> Start () to start DHCP configuration process. 
# Not specify CompletionEvent parameter
#
set L_Filter "udp src port 68 and ether host $targetmac"
StartCapture CCB $L_Filter

Dhcp4->Start  "0, &@R_Status"

ReceiveCcbPacket CCB  DiscoverPacket_1   15

#
# Validate Packet (type=dhcp/DHCPDISCOVER) 
#
if { ${CCB.received} == 0 } {
  set assert fail

  CleanUpEutEnvironment 
  return
} else {
  set assert pass
  CreateDhcpOpt opt1 mesg_type  1
  ParsePacket DiscoverPacket_1 -t dhcp -dhcp_op op -dhcp_htype htype           \
  -dhcp_ciaddr ciaddr -dhcp_options options1
  puts "Ciaddr: $ciaddr"
  puts "Op:     $op"
  set result1 [DhcpOptOpt options1 opt1]
  if { $result1 != 0 } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"
#
# wait until the configuration process have finished
#
Stall         30      
GetAck
set assert [VerifyReturnStatus R_Status $EFI_TIMEOUT]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Check the config data effect."                  \
                "DiscoverTryCount=2, DiscoverTimeout=(2,5)"                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_TIMEOUT"

#
# Call [DHCP4]-> GetModeData() to Verify in the Dhcp4Init State.
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
if { [string compare -nocase $assert "pass"] == 0 } {
  GetVar    R_ModeData.State
  if { ${R_ModeData.State} != $Dhcp4Init } {
    set assert fail
  }
}
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Get Mode Data in Dhcp4Selecting State"    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "Cur State - ${R_ModeData.State}, Expected State - $Dhcp4Init"

#
# Call [DHCP4] -> Stop to stop the DHCP Driver
#
Dhcp4->Stop "&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Stop - Stop Driver."                                    \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call [DHCP4]-> Configure() to change DHCP4 operational parameter.
#
SetVar         R_ConfigData.DiscoverTryCount      0
SetVar         R_ConfigData.DiscoverTimeout       0
SetIpv4Address R_ConfigData.ClientAddress         "192.168.2.3"
GetVar         R_ConfigData.ClientAddress

Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Dhcp4ConfigureFunc1AssertionGuid002                   \
                "Dhcp4.Configure - Change Parameter of Config Data"            \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Call [DHCP4] -> GetModeData to get DHCP configuration data
#
Dhcp4->GetModeData "&@R_ModeData, &@R_Status"
GetAck

#
# Verify Configured Parameters
#
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS];

if { [string compare -nocase $assert "pass"] == 0} {
  GetVar    R_ModeData
  puts "DiscoverTryCount: ${R_ModeData.ConfigData.DiscoverTryCount}"
  if { ${R_ModeData.ConfigData.DiscoverTryCount} != 0 } {	
    set assert fail
  } else {
  	  set temp [GetIpv4Address R_ModeData.ConfigData.ClientAddress]
      if { [string compare $temp "192.168.2.3"] != 0} {
        set assert fail
      }
    }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.GetModeData - Check Startup Config Data"                \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"      \
                "ReturnDiscoverTryCount -                                      \
                ${R_ModeData.ConfigData.DiscoverTryCount},                     \
                ExpectedDiscoverTryCount - 0"

#
# Call [DHCP4] -> Start () to start DHCP configuration process:
#
EndCapture
StartCapture CCB $L_Filter
Dhcp4->Start  "0, &@R_Status"

ReceiveCcbPacket CCB  RequestPacket_1   15

#
# Validate Packet (type=dhcp/DHCPREQUEST) 
#
if { ${CCB.received} == 0 } {
	set assert fail

	CleanUpEutEnvironment 
  return
} else {
  set assert pass
  CreateDhcpOpt opt1 mesg_type  3 
  ParsePacket RequestPacket_1 -t dhcp -dhcp_op op -dhcp_htype htype            \
  -dhcp_ciaddr ciaddr -dhcp_options options1
  puts "Ciaddr: $ciaddr"
  puts "Op:     $op"
  set result1 [DhcpOptOpt options1 opt1]
  if { $result1 != 0 } {
    set assert fail
  }
}

RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Verify having received DHCPDISCOVER Packets"

#
# wait until the configuration process have finished
#

Stall         30
GetAck
set assert [VerifyReturnStatus R_Status $EFI_TIMEOUT]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4.Start - Check the config data effect."                  \
                "DiscoverTryCount=0, DiscoverTimeout=0"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_TIMEOUT"

#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment