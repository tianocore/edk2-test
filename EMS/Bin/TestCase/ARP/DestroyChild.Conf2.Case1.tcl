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
CaseLevel         CONFORMANCE
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#                                                                
# test case Name, category, description, GUID...
#
CaseGuid        78F8B3B6-AB67-4b82-BD6E-44396DA55ED0
CaseName        DestroyChild.Conf2.Case1
CaseCategory    ARP
CaseDescription {This case is to test the DestroyChild Conformance of ARPSB -  \
                 destroy a NULL child, ArpServiceBinding.DestroyChild should   \
                 return EFI_INVALID_PARAMETER.}
################################################################################

#
# Begin log ...
#
BeginLog

Include ARP/include/Arp.inc.tcl

set hostmac    [GetHostMac]
set targetmac  [GetTargetMac]

VifUp 0 172.16.210.162 255.255.255.0
BeginScope _ARP_SPEC_CONFORMANCE_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Destroy a NULL child
#
ArpServiceBinding->DestroyChild {0, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpDestroyChildConfAssertionGuid002                   \
                "Mtftp4SB.DestroyChild - Destroy NULL Child "                  \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"
#
# Destroy un-existed child
#
ArpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $ArpDestroyChildConfAssertionGuid003                   \
                "Mtftp4SB.DestroyChild - Destroy un-existed Child "            \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"\
                
EndScope _ARP_SPEC_CONFORMANCE_
VifDown 0

#
# End Log
#
EndLog