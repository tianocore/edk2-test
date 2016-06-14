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
CaseGuid        B0A892C2-F3EF-4172-AD83-22FBE100FF66
CaseName        Configure.Func1.Case1
CaseCategory    UDP6

CaseDescription {Test the Configure Function of UdP6 - Invoke Configure()     \
                 with valid parameters and EFI_SUCCESS should be returned.
                }
################################################################################

Include UdP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _UDP6_CONFIGURE_FUNC1_

EUTSetup

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Check point: Create child.
#
Udp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid  \
                "Udp6SB.CreateChild - Create Child "                          \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check Point:Call Configure with valid parameters.EFI_SUCCESS should be returned.
#
EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData
SetVar  R_Udp6ConfigData.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData.TrafficClass           0
SetVar  R_Udp6ConfigData.HopLimit               64
SetVar  R_Udp6ConfigData.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData.StationAddress "::"
SetVar  R_Udp6ConfigData.StationPort            1780
SetIpv6Address  R_Udp6ConfigData.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData.RemotePort             1781
  
Udp6->Configure "&@R_Udp6ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6ConfigureFunc1AssertionGuid001  \
                "Udp6.Configure - Configure Child with valid parameters"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EFI_UDP6_CONFIG_DATA                            R_Udp6ConfigData1
EFI_IP6_MODE_DATA                               R_Ip6ModeData
EFI_MANAGED_NETWORK_CONFIG_DATA                 R_MnpConfigData
EFI_SIMPLE_NETWORK_MODE                         R_SnpModeData

Udp6->GetModeData "&@R_Udp6ConfigData1, &@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6ConfigureFunc1AssertionGuid002      \
                "Udp6.GetModeData-Func-Call GetModeData with valid parameters" \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"

GetVar R_Ip6ModeData.IsConfigured
set assert fail
if { ${R_Ip6ModeData.IsConfigured} == true} {
    set assert pass
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003          \
                "Udp6.GetModeData - Func - Udp6ModeData.IsConfigured should be TRUE"

GetVar R_Udp6ConfigData1
set assert pass
if { ${R_Udp6ConfigData1.AcceptPromiscuous} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AcceptPromiscuous should be FALSE as previous set."

set assert pass
if { ${R_Udp6ConfigData1.AcceptAnyPort} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AcceptAnyPort should be FALSE as previous set."

set assert pass
if { ${R_Udp6ConfigData1.AllowDuplicatePort} != false} {
    set assert fail  
}
RecordAssertion $assert $Udp6GetModeDataFunc1AssertionGuid003                        \
                "ConfigData.AllowDuplicatePort should be FALSE as previous set."

set assert pass
if {${R_Udp6ConfigData1.TrafficClass} != 0} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.TrafficClass should be 0 as previous set."

set assert pass
if {${R_Udp6ConfigData1.HopLimit} != 64} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.HopLimit should be 64 as previous set."

set assert pass
if {${R_Udp6ConfigData1.ReceiveTimeout} != 50000} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.ReceiveTimeout should be 50000 as previous set."

set assert pass
if {${R_Udp6ConfigData1.TransmitTimeout} != 50000} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.TransmitTimeout should be 50000 as previous set."

SetIpv6Address  R_Udp6ConfigData.StationAddress  "2002::4321"
set assert pass
set S1 [GetIpv6Address R_Udp6ConfigData1.StationAddress]
set S2 [GetIpv6Address R_Udp6ConfigData.StationAddress]

set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.StationAddress should be the same as previous set."

set assert pass
if {${R_Udp6ConfigData1.StationPort} != 1780} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.StationPort should be 1780 as previous set."

set assert pass
set S1 [GetIpv6Address R_Udp6ConfigData1.RemoteAddress]
set S2 [GetIpv6Address R_Udp6ConfigData.RemoteAddress]
set temp [string compare $S1 $S2]
if {$temp != 0} {
   set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.RemoteAddress should be 2002::2 as previous set."

set assert pass
if {${R_Udp6ConfigData1.RemotePort} != 1781} {
    set assert fail
}
RecordAssertion  $assert $Udp6GetModeDataFunc1AssertionGuid003                       \
                 "Udp6ConfigData.RemotePort should be 1781 as previous set."

Udp6->Configure "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $Udp6ConfigureFunc1AssertionGuid004  \
                "Udp6.Configure - Configure Child with NULL"      \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

Udp6->GetModeData "&@R_Udp6ConfigData1, &@R_Ip6ModeData, &@R_MnpConfigData, &@R_SnpModeData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Udp6ConfigureFunc1AssertionGuid005      \
                "Udp6.GetModeData-Func-Call GetModeData with valid parameters" \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_NOT_STARTED"
#
# Check point: Destroy child.
#
Udp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                         \
                "Udp6SB.DestroyChild - Destroy Child."                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EUTClose
				
#
# EndScope
#
EndScope    _UDP6_CONFIGURE_FUNC1_
#
# End Log 
#
EndLog