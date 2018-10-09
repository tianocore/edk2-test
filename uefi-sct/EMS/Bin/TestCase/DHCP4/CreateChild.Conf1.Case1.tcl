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
CaseGuid        b3700cff-5723-4744-98c9-4d6072253b89
CaseName        CreateChild.Conf1.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PATAMETER  \
	              -- ChildHandle is Null.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_CREATECHILD_CONF1

UINTN                             R_Status

#
# Check Point: Call [DHCP4SBP] -> CreateChild with NULL Handle Pointer
#
Dhcp4ServiceBinding->CreateChild "NULL, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4CreateChildConf1AssertionGuid001                 \
                "Dhcp4.CreateChild - Call with ChildHandle=NULL."              \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

EndScope    _DHCP4_CREATECHILD_CONF1
#
# End Log 
#
EndLog