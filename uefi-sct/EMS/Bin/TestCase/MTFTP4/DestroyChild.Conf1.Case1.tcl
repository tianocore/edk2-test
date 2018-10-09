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
CaseGuid        E840B007-A8F9-46d2-9197-25EA90ABC923
CaseName        DestroyChild.Conf1.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the DestroyChild Conformance of Mtftp4SB -\
                 destroy a NULL child, Mtftp4ServiceBinding.DestroyChild should \
                 return EFI_INVALID_PARAMETER.}
################################################################################

Include MTFTP4/include/Mtftp4.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MTFTP4_DESTROYCHILD_CONFORMANCE1_CASE1_


#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

#
# Destroy un-existed child
#
Mtftp4ServiceBinding->DestroyChild {0, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4DestroyChildConfAssertionGuid001                \
                "Mtftp4SB.DestroyChild - Destroy NULL Child "                  \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy un-existed child
#
Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Mtftp4DestroyChildConfAssertionGuid002                \
                "Mtftp4SB.DestroyChild - returns EFI_INVALID_PARAMETER for     \
                 having Destroyed un-existed child "                           \
                "ReturnStatus - $R_Status,ExpectedStatus - $EFI_INVALID_PARAMETER"
                
EndScope _MTFTP4_DESTROYCHILD_CONFORMANCE1_CASE1_

#
# End log ...
#
EndLog
