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
CaseGuid        4EED8DE8-2ED9-4da9-B4A3-175DEC1F57EF
CaseName        RenewRebind.Conf1.Case1
CaseCategory    DHCP6
CaseDescription {Test the RenewRebind Conformance of DHCP6 - Invoke RenewRebind() \
                 when the instance has not been configured. \
                 EFI_ACCESS_DENIED should be returned.
                }
################################################################################

Include DHCP6/include/Dhcp6.inc.tcl

#
# Begin log ...
#
BeginLog
#
# BeginScope
#
BeginScope  _DHCP6_RENEWREBIND_CONF1

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Create child.
#
Dhcp6ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                       \
                "Dhcp6SB.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Check point: Try to call RenewRebind while the instance has not been configured.
#              EFI_ACCESS_DENIED should be returned.
#
Dhcp6->RenewRebind "TRUE, &@R_Status"
GetAck
set assert    [VerifyReturnStatus R_Status $EFI_ACCESS_DENIED]
RecordAssertion $assert $Dhcp6RenewRebindConf1AssertionGuid001                   \
                "Dhcp6.RenewRebind - Call RenewRebind when the instance has not been configured" \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_ACCESS_DENIED"

#
# Destroy child.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# EndScope
#
EndScope _DHCP6_RENEWREBIND_CONF1
#
# End Log 
#
EndLog
