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
CaseGuid        EA832B53-E782-4539-88CE-D986ED9AC651
CaseName        Configure.Func1.Case1
CaseCategory    MTFTP6
CaseDescription {Test the Configure Function of MtftP6 -Invoke Configure()  \
                 with valid parameters.EFI_SUCCESS should be returned.
                }
################################################################################

Include MTFTP6/include/Mtftp6.inc.tcl
#
# Begin log ...
#
BeginLog

BeginScope _MTFTP6_CONFIGURE_FUNC1_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
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
# Check Point: Call Configure function with valid parameters for the first time. 
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData
SetIpv6Address    R_Mtftp6ConfigData.StationIp         "::" 
SetVar            R_Mtftp6ConfigData.LocalPort         0
SetIpv6Address    R_Mtftp6ConfigData.ServerIp          "2002::2"
SetVar            R_Mtftp6ConfigData.InitialServerPort 0
SetVar            R_Mtftp6ConfigData.TryCount          3
SetVar            R_Mtftp6ConfigData.TimeoutValue      3

Mtftp6->Configure "&@R_Mtftp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6ConfigureFunc1AssertionGuid001  \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Call Configure function when Mtftp6ConfigData is NULL. 
#
Mtftp6->Configure "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6ConfigureFunc1AssertionGuid002          \
                "Mtftp6.Configure -conf- Call Configure when Mtftp6ConfigData is NULL"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call Configure function with valid parameters for the second time.
#              EFI_SUCCESS should be returned.
#
EFI_MTFTP6_CONFIG_DATA      R_Mtftp6ConfigData1
SetIpv6Address    R_Mtftp6ConfigData1.StationIp         "::" 
SetVar            R_Mtftp6ConfigData1.LocalPort         1780
SetIpv6Address    R_Mtftp6ConfigData1.ServerIp          "2002::3"
SetVar            R_Mtftp6ConfigData1.InitialServerPort 1781
SetVar            R_Mtftp6ConfigData1.TryCount          4
SetVar            R_Mtftp6ConfigData1.TimeoutValue      4

Mtftp6->Configure "&@R_Mtftp6ConfigData1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Mtftp6ConfigureFunc1AssertionGuid003  \
                "Mtftp6.Configure -conf- Call Configure with valid parameters"  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check Point: Call GetModeData function with valid parameters.
#              EFI_SUCCESS should be returned. 
#
EFI_MTFTP6_MODE_DATA         R_Mtftp6ModeData

Mtftp6->GetModeData "&@R_Mtftp6ModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                          \
                "Mtftp6.GetModeData -Func- Call GetModeData with valid parameters."    \
                "ReturnStatus -$R_Status, ExpectedStatus -$EFI_SUCCESS"

GetVar R_Mtftp6ModeData
#
# Check Point:Mtftp6ModeData.ConfigData should be the same as previous set.
#
EFI_MTFTP6_CONFIG_DATA       R_ConfigData
UINTN                        R_CopyLen
SetVar R_CopyLen [Sizeof R_ConfigData]
GetVar R_CopyLen
BS->CopyMem "&@R_ConfigData, &@R_Mtftp6ModeData.ConfigData, @R_CopyLen, &@R_Status"
GetAck

EFI_MTFTP6_CONFIG_DATA       R_ConfigData1
SetIpv6Address               R_ConfigData1.StationIp  "::"
set assert pass
set S1 [GetIpv6Address R_ConfigData1.StationIp]
set S2 [GetIpv6Address R_ConfigData.StationIp]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                          \
                 "Mtftp6ModeData.ConfigData.StationIp should be the same as previous set."

GetVar R_ConfigData.LocalPort
set assert pass
if { ${R_ConfigData.LocalPort} != 1780} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                            \
                "ConfigData.LocalPort should be the same as previous set."

SetIpv6Address  R_ConfigData1.ServerIp  "2002::3"
set assert pass
set S1 [GetIpv6Address R_ConfigData1.ServerIp]
set S2 [GetIpv6Address R_ConfigData.ServerIp]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                          \
                 "Mtftp6ModeData.ConfigData.ServerIp should be the same as previous set."

GetVar R_ConfigData.InitialServerPort
set assert pass 
if { ${R_ConfigData.InitialServerPort} != 1781 } {
   set assert fail
}
RecordAssertion  $assert $GenericAssertionGuid                                \
                 "Mtftp6ModeData.ConfigData.InitialServerPort should be the same as previous set."

GetVar R_ConfigData.TryCount
set assert pass
if { ${R_ConfigData.TryCount} != 4} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                             \
                "TryCount should be the same as previous set equals 4"

GetVar R_ConfigData.TimeoutValue
set assert pass
if { ${R_ConfigData.TimeoutValue} != 4} {
   set assert fail
}
RecordAssertion $assert $GenericAssertionGuid                             \
                "TimeoutValue should be the same as previous set equals 4"

#
# Destroy child
#
Mtftp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                   \
                "Mtftp6SB.DestroyChild - Destroy Child "                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP6_CONFIGURE_FUNC1_CASE1_

#
# End Log
#
EndLog