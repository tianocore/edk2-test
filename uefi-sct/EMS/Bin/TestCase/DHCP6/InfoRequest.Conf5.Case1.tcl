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
CaseGuid        7C7B7014-0D8E-459e-A01D-FA5777D61F0D
CaseName        InfoRequest.Conf5.Case1
CaseCategory    DHCP6
CaseDescription {Test the InfoRequest Conformance of DHCP6 - Invoke InfoRequest() \
                 with Retransmission.Mrd and Retransmission.Mrt both zero. \
                 EFI_INVALID_PARAMETER should be returned.
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
BeginScope  _DHCP6_INFOREQUEST_CONF5_

#
# Parameter Definition
# R_ represents "Remote EFI Side Parameter"
# L_ represents "Local OS Side Parameter"
#
UINTN                                   R_Status
UINTN                                   R_Handle

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

BOOLEAN                                 R_SendClientId
SetVar R_SendClientId                   FALSE

#
# Build the Option Request Option
#
EFI_DHCP6_PACKET_OPTION                 R_OptionRequest
SetVar R_OptionRequest.OpCode           $Dhcp6OptRequestOption
SetVar R_OptionRequest.OpLen            4
UINT8                                   R_OptRequestData(4)
SetVar R_OptRequestData                 {0x00 0x17 0x00 0x18}
SetVar R_OptionRequest.Data             @R_OptRequestData

UINT32                                  R_OptionCount
SetVar R_OptionCount                    0

POINTER                                 R_OptionList
SetVar R_OptionList                     0

UINT32                                  R_Retransmission(4)
#
# Retransmission parameters
# Irt 1
# Mrc 0
# Mrt 3
# Mrd 0
#
SetVar R_Retransmission                 {1 0 3 0}

UINTN                                   R_ReplyCallback
UINTN                                   R_CallbackContext
#0: NULL 1: Abort 2: DoNothing
SetVar R_ReplyCallback                 2

#
# Check point: Call InfoRequest() with Retransmission.Mrd and Retransmission.Mrt both zero.
#              EFI_INVALID_PARAMETER should be returned.
#
Dhcp6->InfoRequest "@R_SendClientId, &@R_OptionRequest, @R_OptionCount, @R_OptionList, \
                                                    &@R_Retransmission, 0, @R_ReplyCallback, &@R_CallbackContext, &@R_Status"
GetAck
set assert [VerifyReturnStatus R_Status $EFI_INVALID_PARAMETER]
RecordAssertion $assert $Dhcp6InfoRequestConf5AssertionGuid001                       \
                        "Dhcp6.InfoRequest - Retransmission.Mrd and Retransmission.Mrt are both zero" \
                        "ReturnStatus - $R_Status, ExpectedStatus - $EFI_INVALID_PARAMETER"

#
# Destroy child.
#
Dhcp6ServiceBinding->DestroyChild "@R_Handle, &@R_Status"
GetAck

#
# EndScope
#
EndScope _DHCP6_INFOREQUEST_CONF5_
#
# End Log 
#
EndLog