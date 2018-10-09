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
CaseLevel         FUNCTION
CaseAttribute     AUTO
CaseVerboseLevel  DEFAULT
set reportfile    report.csv

#
# test case Name, category, description, GUID...
#
CaseGuid        3F3C9CBE-6CDE-4389-8A96-3329021D659C
CaseName        GetModeData.Func2.Case2
CaseCategory    MNP
CaseDescription {Test the Function of MNP.GetModeData - Call MNP.GetModeData() \
	               with the parameter MnpConfData being NULL.}
################################################################################

Include MNP/include/Mnp.inc.tcl

#
# Begin log ...
#
BeginLog
BeginScope _MNP_GETMODEDATA_FUNCTION2_CASE2_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                             R_Status
UINTN                             R_Handle
EFI_MANAGED_NETWORK_CONFIG_DATA   R_MnpConfData
EFI_MANAGED_NETWORK_CONFIG_DATA   R_SampleMnpConfData
EFI_SIMPLE_NETWORK_MODE           R_SnpModeData

MnpServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Create Child"                               \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"     

SetMnpConfigData R_MnpConfData 0 0 0 TRUE FALSE TRUE TRUE FALSE FALSE TRUE
SetVar  R_SampleMnpConfData @R_MnpConfData
Mnp->Configure {&@R_MnpConfData, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Configure"                                  \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"       
#      
# R_MnpConfData=NULL
#      
Mnp->GetModeData {NULL,&@R_SnpModeData, &@R_Status}
GetAck 
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $MnpGetModeDataFunc2AssertionGuid002                   \
                "MNP.GetModeData - Basic Func - Call GetModeData() with the    \
                parameter  R_MnpConfData=NULL"                                 \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
       

MnpServiceBinding->DestroyChild {@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "MNP.GetModeData - Destroy Child"                              \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"  

EndScope _MNP_GETMODEDATA_FUNCTION2_CASE2_

#
# End log
#
EndLog
                            