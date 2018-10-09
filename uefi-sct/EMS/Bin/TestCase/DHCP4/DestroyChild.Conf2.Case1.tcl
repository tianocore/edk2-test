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
CaseGuid        8550a617-73a9-49a6-9853-8ac4b032e833
CaseName        DestroyChild.Conf2.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PATAMETER  \
	              -- ChildHandle is invaild.}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_DESTROYCHILD_CONF2

UINTN       R_Status

#
# Check Point: Destroy Child with Null ChildHandle.
#
Dhcp4ServiceBinding->DestroyChild "0, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4DestroyChildConf2AssertionGuid001                \
                "Dhcp4.DestroyChild - Call Destroy with Null ChildHandle."     \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

EndScope _DHCP4_DESTROYCHILD_CONF2
#
# End Log 
#
EndLog