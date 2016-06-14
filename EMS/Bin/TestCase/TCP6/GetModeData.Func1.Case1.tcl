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
CaseGuid        2F3C6470-013D-4ba6-AC16-B9AF3FDFEC74
CaseName        GetModeData.Func1.Case1
CaseCategory    TCP6
CaseDescription {GetModeData must succeed with valid parameters.}
################################################################################
Include TCP6/include/Tcp6.inc.tcl
# Procedure Name
#   ValidateModeData
# Procedure Description:
#   Validate mode data to be the same with the configuration
# Arguments:
#   L_Proc_CheckState
#       Whether to check the connection state
#   L_Proc_CheckConfigure
#       Whether to check the configure data
# Returns:
#    None
#
proc CheckModeData { L_Proc_CheckState L_Proc_CheckConfigure } {
  global TCS DEF_EUT_IP_ADDR DEF_EUT_MAC_ADDR DEF_EUT_PRT DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR DEF_ENTS_PRT
  global assert
  global R_Configure_Tcp6ConnectionState
  global R_Configure_Tcp6ConfigData
  global {R_Configure_Tcp6ConfigData.TrafficClass}
  global {R_Configure_Tcp6ConfigData.HopLimit}
  global {R_Configure_Tcp6ConfigData.ControlOption}
  global {R_Configure_Tcp6ConfigData.AccessPoint}
  global {R_Proc_AccessPoint.StationPort}
  global {R_Proc_AccessPoint.RemotePort}
  global {R_Proc_AccessPoint.ActiveFlag}
  global {R_Proc_AccessPoint.StationAddress}
  global {R_Proc_AccessPoint.RemoteAddress}

  
  if { $L_Proc_CheckState == 1} {
    GetVar  R_Configure_Tcp6ConnectionState 
    if { [expr $R_Configure_Tcp6ConnectionState] != $TCS(Listen) } {
      set assert fail
      return
    }
  }
  
  if { $L_Proc_CheckConfigure == 1} {
    GetVar  R_Configure_Tcp6ConfigData
    if { ${R_Configure_Tcp6ConfigData.TrafficClass} != 0 } {
      set assert fail
      return
    }
    if { ${R_Configure_Tcp6ConfigData.HopLimit} != 128 } {
      set assert fail
      return
    }
    if { ${R_Configure_Tcp6ConfigData.ControlOption} != 0 } {
      set assert fail
      return
    }
    EFI_TCP6_ACCESS_POINT R_Proc_AccessPoint
    UINTN R_Proc_MemSize
    UINTN R_Proc_Status
    SetVar R_Proc_MemSize  [Sizeof R_Proc_AccessPoint]
    BS->CopyMem " &@R_Proc_AccessPoint, &@R_Configure_Tcp6ConfigData.AccessPoint, @R_Proc_MemSize, &@R_Proc_Status"
    GetAck
    GetVar R_Proc_AccessPoint
    if { ${R_Proc_AccessPoint.RemotePort} != $DEF_ENTS_PRT } {
      set assert fail
      DelVar R_Proc_AccessPoint
      DelVar R_Proc_MemSize
      DelVar R_Proc_Status
      return
    }
    if { ${R_Proc_AccessPoint.StationPort} != 6666 } {
      set assert fail
      DelVar R_Proc_AccessPoint
      DelVar R_Proc_MemSize
      DelVar R_Proc_Status
      return
    }
    if { [string compare ${R_Proc_AccessPoint.ActiveFlag} false] != 0 } {
      set assert fail
      DelVar R_Proc_AccessPoint
      DelVar R_Proc_MemSize
      DelVar R_Proc_Status
      return
    }
    set L_Proc_Ipv6Address [GetIpv6Address {R_Proc_AccessPoint.StationAddress}]
    if { [string compare $L_Proc_Ipv6Address $DEF_EUT_IP_ADDR] != 0} {
      set assert fail
      DelVar R_Proc_AccessPoint
      DelVar R_Proc_MemSize
      DelVar R_Proc_Status
      return
    }
    set L_Proc_Ipv6Address [GetIpv6Address {R_Proc_AccessPoint.RemoteAddress}]
    if { [string compare $L_Proc_Ipv6Address $DEF_ENTS_IP_ADDR] != 0} {
      set assert fail
      DelVar R_Proc_AccessPoint
      DelVar R_Proc_MemSize
      DelVar R_Proc_Status
      return
    }
    DelVar R_Proc_AccessPoint
    DelVar R_Proc_MemSize
    DelVar R_Proc_Status
  }
  return
}

#
# Begin log ...
#
BeginLog

#
# BeginScope
#
BeginScope  _TCP6_GETMODEDATA_FUNC1_CASE1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle
EFI_TCP6_ACCESS_POINT            R_Configure_AccessPoint
EFI_TCP6_CONFIG_DATA             R_Configure_Tcp6ConfigData
UINT32                           R_Configure_Tcp6ConnectionState
EFI_IP6_MODE_DATA                R_Configure_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA  R_Configure_MnpConfigData
EFI_SIMPLE_NETWORK_MODE          R_Configure_SnpModeData

#
# Create Child for TCP6 protocol
#
Tcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.CreateChild - Create Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Configure the instance with valid parameters
#
SetIpv6Address  R_Configure_AccessPoint.StationAddress     $DEF_EUT_IP_ADDR
SetVar          R_Configure_AccessPoint.StationPort        6666
SetIpv6Address  R_Configure_AccessPoint.RemoteAddress      $DEF_ENTS_IP_ADDR
SetVar          R_Configure_AccessPoint.RemotePort         $DEF_ENTS_PRT
SetVar          R_Configure_AccessPoint.ActiveFlag         FALSE


SetVar R_Configure_Tcp6ConfigData.TrafficClass        0
SetVar R_Configure_Tcp6ConfigData.HopLimit            128
SetVar R_Configure_Tcp6ConfigData.AccessPoint         @R_Configure_AccessPoint
SetVar R_Configure_Tcp6ConfigData.ControlOption       0

Tcp6->Configure {&@R_Configure_Tcp6ConfigData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Tcp6.Configure - Call Configure() with valid config data"         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"


#
# Check Point: Call Get Mode Data with validate parameters
#
Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, &@R_Configure_Tcp6ConfigData,     \
                   &@R_Configure_Ip6ModeData,&@R_Configure_MnpConfigData,      \
                   &@R_Configure_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 1 1
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid001         \
                "Tcp6 - GetModeData with 0 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {NULL,NULL,     \
                   NULL,NULL,      \
                   NULL,&@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 0 0
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid002         \
                "Tcp6 - GetModeData with 5 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {NULL, &@R_Configure_Tcp6ConfigData,     \
                   &@R_Configure_Ip6ModeData,&@R_Configure_MnpConfigData,      \
                   &@R_Configure_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 0 1
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid003         \
                "Tcp6 - GetModeData with 1 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, NULL,     \
                   &@R_Configure_Ip6ModeData,&@R_Configure_MnpConfigData,      \
                   &@R_Configure_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 1 0
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid004         \
                "Tcp6 - GetModeData with 1 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, &@R_Configure_Tcp6ConfigData,     \
                   NULL,&@R_Configure_MnpConfigData,      \
                   &@R_Configure_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 1 1
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid005         \
                "Tcp6 - GetModeData with 1 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, &@R_Configure_Tcp6ConfigData,     \
                   &@R_Configure_Ip6ModeData,NULL,      \
                   &@R_Configure_SnpModeData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 1 1
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid006         \
                "Tcp6 - GetModeData with 1 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

Tcp6->GetModeData {&@R_Configure_Tcp6ConnectionState, &@R_Configure_Tcp6ConfigData,     \
                   &@R_Configure_Ip6ModeData,&@R_Configure_MnpConfigData,      \
                   NULL, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
CheckModeData 1 1
RecordAssertion $assert $Tcp6GetModeDataFunc1AssertionGuid007         \
                "Tcp6 - GetModeData with 1 parameters NULL"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"
#
# Destroy Child
#
Tcp6ServiceBinding->DestroyChild "@R_Handle,&@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Tcp6SBP.DestroyChild - Destroy Child"                         \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS and data retrieved correct"

EUTClose

#
# EndScope
#
EndScope  _TCP6_GETMODEDATA_FUNC1_CASE1_

#
# End log
#
EndLog
