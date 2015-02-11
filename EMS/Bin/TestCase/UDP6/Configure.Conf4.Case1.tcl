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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        15E02530-BD84-43f1-9E0A-1474D14A914C
CaseName        Configure.Conf4.Case1
CaseCategory    UDP6
CaseDescription {Test the Configure Conformance of UDP6 - Invoke Configure()    \ 
                 when StationPort has already been used by another Udp6 instance.\
                 EFI_ACCESS_DENIED should be returned.}
################################################################################

Include  UDP6/include/Udp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope _UDP6_CONFIGURE_CONF4_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle1
UINTN                            R_Handle2
EFI_UDP6_CONFIG_DATA             R_Udp6ConfigData1

#
# Create child1.
#
Udp6ServiceBinding->CreateChild "&@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                  \
                "Udp6SB.CreateChild - Create Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle1

# 
# Check point: Call Configure function first time with valid parameters.\
#              EFI_SUCCESS should be returned.
#
SetVar  R_Udp6ConfigData1.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData1.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData1.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData1.TrafficClass           0
SetVar  R_Udp6ConfigData1.HopLimit               64
SetVar  R_Udp6ConfigData1.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData1.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData1.StationAddress "::"
SetVar  R_Udp6ConfigData1.StationPort            1780
SetIpv6Address  R_Udp6ConfigData1.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData1.RemotePort             666
  
Udp6->Configure "&@R_Udp6ConfigData1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid    \
                "Udp6.Configure - Configure Child 1"                   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Check point: Create child2
#
Udp6ServiceBinding->CreateChild "&@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                \
                "Udp6SB.CreateChild- Conf- Create child 2"             \
                "ReturnStatus-$R_Status, ExpectedStatus-$EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle2

#
# Check point: Call Configure() to configure child2 with the same StationPort(1780) \
#              and AllowDuplicatePort(FALSE).EFI_ACCESS_DENIED should be returned.
#
EFI_UDP6_CONFIG_DATA             R_Udp6ConfigData2
SetVar  R_Udp6ConfigData2.AcceptPromiscuous      FALSE
SetVar  R_Udp6ConfigData2.AcceptAnyPort          FALSE
SetVar  R_Udp6ConfigData2.AllowDuplicatePort     FALSE
SetVar  R_Udp6ConfigData2.TrafficClass           0
SetVar  R_Udp6ConfigData2.HopLimit               64
SetVar  R_Udp6ConfigData2.ReceiveTimeout         50000
SetVar  R_Udp6ConfigData2.TransmitTimeout        50000
SetIpv6Address  R_Udp6ConfigData2.StationAddress "::"
SetVar  R_Udp6ConfigData2.StationPort            1780
SetIpv6Address  R_Udp6ConfigData2.RemoteAddress  "2002::2"
SetVar  R_Udp6ConfigData2.RemotePort             1781

Udp6->Configure "&@R_Udp6ConfigData2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Udp6ConfigureConf4AssertionGuid001 \
                "Udp6.Configure - Call Configure with the same StationPort(1780) as child1."   \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Destroy child1.
#
Udp6ServiceBinding->DestroyChild "@R_Handle1, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child1"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

#
# Destroy child2.
#
Udp6ServiceBinding->DestroyChild "@R_Handle2, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                 \
                "Udp6SB.DestroyChild - Destroy Child 2"                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# EndScope
#
EndScope    _UDP6_CONFIGURE_CONF4_
#
# End Log 
#
EndLog