# 
#  Copyright 2006 - 2017 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
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
CaseGuid        f7d1a72e-50aa-4623-a36c-886d084c6792
CaseName        Configure.Conf3.Case1
CaseCategory    DHCP4
CaseDescription {This case is to test the Conformance - EFI_INVALID_PATAMETER  \
	              -- A). DiscoverTryCount > 0 and DiscoverTimeout is NULL.       \
                   B). RequestTryCount > 0 and RequestTimeout is NULL.         \
                   C). OptionCount >0 and OptionList is NULL.                  \
                   D). ClientAddress is not a valid unicast address.           \
                   - 255.255.255.255}

################################################################################

Include DHCP4/include/Dhcp4.inc.tcl

proc CleanUpEutEnvironment {} {
  Dhcp4ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
  GetAck

  EndScope _DHCP4_CONFIGURE_CONF3
  EndLog
}

#
# Begin log ...
#
BeginLog
BeginScope  _DHCP4_CONFIGURE_CONF3

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                            R_Status
UINTN                            R_Handle

EFI_DHCP4_CONFIG_DATA            R_ConfigData
UINT32                           R_Timeout(2)

#
# Call [DHCP4SBP] -> CreateChild to create child.
#
Dhcp4ServiceBinding->CreateChild {&@R_Handle, &@R_Status}
GetAck
set assert [VerifyReturnStatus R_Status $EFI_SUCCESS]
RecordAssertion $assert $GenericAssertionGuid                                  \
                "Dhcp4SBP.CreateChild - Create Child 1"                        \
                "ReturnStatus - $R_Status, ExpectedStatus - $EFI_SUCCESS"
SetVar     [subst $ENTS_CUR_CHILD]  @R_Handle

#
# Call [DHCP4] -> Configure with the following parameters
#   A). DiscoverTryCount > 0 and DiscoverTimeout is NULL.
#   B). RequestTryCount > 0 and RequestTimeout is NULL.
#   C). OptionCount >0 and OptionList is NULL.
#   D). ClientAddress is not a valid unicast address. - 192.168.1.255,234.0.0.1
#
SetVar    R_ConfigData.DiscoverTryCount   2
SetVar    R_ConfigData.DiscoverTimeout    0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with DiscoverTryCount > 0 and  DiscoverTimeout is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid001                   \
                "Dhcp4.Configure - DiscoverTryCount > 0 and                    \
                DiscoverTimeout is NULL"                                       \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

SetVar    R_Timeout(0)                    2
SetVar    R_Timeout(1)                    5
SetVar    R_ConfigData.DiscoverTimeout    &@R_Timeout
SetVar    R_ConfigData.RequestTryCount    2
SetVar    R_ConfigData.RequestTimeout     0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with Dhcp4.Configure - RequestTryCount > 0 and 
#              RequestTimeout is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid002                   \
                "Dhcp4.Configure - RequestTryCount > 0 and                     \
                RequestTimeout is NULL"                                        \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"

SetVar    R_ConfigData.RequestTimeout     &@R_Timeout
SetVar    R_ConfigData.OptionCount        1
SetVar    R_ConfigData.OptionList         0

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with Dhcp4.Configure - OptionCount > 0 and OptionList is NULL.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid003                   \
                "Dhcp4.Configure - OptionCount > 0 and                         \
                OptionList is NULL"                                            \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"
#
# Build an option of ClientIdentifier
#
UINT8          R_ClientIdOpt(9)
SetVar         R_ClientIdOpt(0)           61  ;#Code
SetVar         R_ClientIdOpt(1)           7   ;#Len
SetVar         R_ClientIdOpt(2)           1   ;#Hardware type & Hardware address
SetVar         R_ClientIdOpt(3)           00
SetVar         R_ClientIdOpt(4)           01
SetVar         R_ClientIdOpt(6)           03
SetVar         R_ClientIdOpt(5)           02
SetVar         R_ClientIdOpt(7)           04
SetVar         R_ClientIdOpt(8)           05

POINTER        R_OptionPtr
SetVar         R_OptionPtr                &@R_ClientIdOpt
SetVar         R_ConfigData.OptionList    &@R_OptionPtr
SetIpv4Address R_ConfigData.ClientAddress "255.255.255.255"

#
# Check Point: Call Dhcp4.Configure for an DHCP instance,
#              with a invalid unicast address.
#
Dhcp4->Configure "&@R_ConfigData, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp4ConfigureConf3AssertionGuid004                   \
                "Dhcp4.Configure - ClientAddress = 255.255.255.255"            \
                "ReturnStatus - $R_Status, ExpectedStatus -                    \
                $EFI_INVALID_PARAMETER"


#
# Clean up the environment on EUT side.
#
CleanUpEutEnvironment