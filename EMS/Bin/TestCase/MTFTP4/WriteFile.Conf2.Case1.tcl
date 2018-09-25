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
CaseGuid        8D8F2F20-3EE3-45b3-BE4C-DF6709B56842
CaseName        WriteFile.Conf2.Case1
CaseCategory    MTFTP4
CaseDescription {This case is to test the EFI_NOT_STARTED conformance of       \
                 Mtftp4.WriteFile, with the EFI MTFTPv4 Protocol driver having \
                 not been started.}
################################################################################

#
# Begin log ...
#
BeginLog

Include MTFTP4/include/Mtftp4.inc.tcl

BeginScope _MTFTP4_WRITEFILE_CONFORMANCE2_CASE1_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local ENTS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

EFI_MTFTP4_TOKEN                 R_Token
CHAR8                            R_NameOfFile(20)

Mtftp4ServiceBinding->CreateChild "&@R_Handle, &@R_Status"
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.CreateChild - Create Child 1"                       \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
#
# check point
#
SetVar R_NameOfFile         "TestFile"

SetVar R_Token.OverrideData 0
SetVar R_Token.ModeStr      0
SetVar R_Token.Filename     &@R_NameOfFile
SetVar R_Token.OptionCount  0
SetVar R_Token.OptionList   0
SetVar R_Token.BufferSize   0
SetVar R_Token.Buffer       0

Mtftp4->WriteFile {&@R_Token, 1, 1, 1, &@R_Status}

GetAck

set assert [VerifyReturnStatus R_Status $EFI_NOT_STARTED]
RecordAssertion $assert $Mtftp4WriteFileConfAssertionGuid008                   \
                "Mtftp4.WriteFile - returns EFI_NOT_STARTED with the EFI       \
                 MTFTPv4 Protocol driver having not been started."             \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_NOT_STARTED"

Mtftp4ServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck

set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Mtftp4SBP.DestroyChild - Destroy Child 1"                     \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"

EndScope _MTFTP4_WRITEFILE_CONFORMANCE2_CASE1_

#
# End Log
#
EndLog