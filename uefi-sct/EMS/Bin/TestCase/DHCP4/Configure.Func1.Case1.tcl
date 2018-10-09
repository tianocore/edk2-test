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
CaseGuid        5eb01a45-e540-4b7f-923d-6a08a658894c
CaseName        Configure.Func1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Functionality.                       \
                -- Validate the Configure Data effect before and after call    \
                Dhcp->start to start the Configuration. }

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
RecordAssertion $assert $Dhcp4ConfigureFunc1AssertionGuid001                   \
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
                "CurState - ${R_ModeData.State}, Expected State - $Dhcp4Init"

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
RecordAssertion $assert $Dhcp4ConfigureFunc1AssertionGuid001                   \
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
Dhcp4->Start  "0, &@R_Status"

ReceiveCcbPacket CCB  DiscoverPacket_2   15

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
  ParsePacket DiscoverPacket_2 -t dhcp -dhcp_op op -dhcp_htype htype           \
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