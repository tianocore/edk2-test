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
if {[info exist DHCP6_INC] == 1} {
  return
}

set DHCP6_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include DHCP6/Include/Dhcp6.proc.tcl
Include DHCP6/Include/Dhcp6AssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

Include Include/Dhcp6.proc.tcl

###################################################################
# Function Declaration
###################################################################
Func Dhcp6ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Dhcp6ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Dhcp6->GetModeData {
  POINTER
  POINTER
  POINTER
}

Func Dhcp6->Configure {
  POINTER
  POINTER
}

Func Dhcp6->Start {
  POINTER
}

Func Dhcp6->InfoRequest {
  BOOLEAN
  POINTER
  UINT32
  POINTER
  POINTER
  UINTN
  UINTN
  POINTER
  POINTER
}

Func Dhcp6->RenewRebind {
  BOOLEAN
  POINTER
}

Func Dhcp6->Decline {
  UINT32
  POINTER
  POINTER
}

Func Dhcp6->Release {
  UINT32
  POINTER
  POINTER
}

Func Dhcp6->Stop {
  POINTER
}

Func Dhcp6->Parse {
  POINTER
  POINTER
  POINTER
  POINTER
}

###################################################################
# DHCP6 Packet Option
###################################################################
Pack 1
Struct EFI_DHCP6_PACKET_OPTION {
  UINT16    OpCode;
  UINT16    OpLen;
  UINT8     Data(300);
};
Pack

###################################################################
# DHCP6 Header Data Structure
###################################################################
Pack 1
Struct EFI_DHCP6_HEADER {
  UINT8    MessageType;
  UINT8    TransactionId(3);
};
Pack

###################################################################
# DHCP6 Packet Data Structure
###################################################################
Pack 1
Struct EFI_RAW_DHCP6_PACKET {
  EFI_DHCP6_HEADER    Header;
  UINT8               Option(312);
};
Struct EFI_DHCP6_PACKET {
  UINT32                  Size;
  UINT32                  Length;
  EFI_RAW_DHCP6_PACKET    Dhcp6;
};
Pack

###################################################################
# DHCP6 DUID Structure
###################################################################
Pack 1
Struct EFI_DHCP6_DUID {
  UINT16    Length;
  UINT8     Duid(300)
}
Pack

###################################################################
# EFI_DHCP6_RETRANSMISSION
###################################################################
Struct EFI_DHCP6_RETRANSMISSION {
  UINT32    Irt;
  UINT32    Mrc;
  UINT32    Mrt;
  UINT32    Mrd
}

###################################################################
# EFI_DHCP6_IA_ADDRESS
###################################################################
Struct EFI_DHCP6_IA_ADDRESS {
  EFI_IPv6_ADDRESS    IpAddress;
  UINT32              PreferredLifetime;
  UINT32              ValidLifetime
}

###################################################################
# EFI_DHCP6_IA_DESCRIPTOR
###################################################################
Struct EFI_DHCP6_IA_DESCRIPTOR {
  UINT16    Type;
  UINT32    IaId
}

###################################################################
# EFI_DHCP6_IA
###################################################################
Struct EFI_DHCP6_IA {
  EFI_DHCP6_IA_DESCRIPTOR    Descriptor;
  UINTN                      State;
  POINTER                    ReplyPacket;
  UINT32                     IaAddressCount;
  EFI_DHCP6_IA_ADDRESS       IaAddress(30)
}

###################################################################
# EFI_DHCP6_MODE_DATA
###################################################################
Struct EFI_DHCP6_MODE_DATA {
  POINTER    ClientId;
  POINTER    Ia
}

###################################################################
# EFI_DHCP6_CONFIG_DATA
###################################################################
Struct EFI_DHCP6_CONFIG_DATA {
  UINTN                      Dhcp6Callback;
  POINTER                    CallbackContext;
  UINT32                     OptionCount;
  POINTER                    OptionList;
  EFI_DHCP6_IA_DESCRIPTOR    IaDescriptor;
  UINTN                      IaInfoEvent;
  BOOLEAN                    ReconfigureAccept;
  BOOLEAN                    RapidCommit;
  POINTER                    SolicitRetransmission
}

###################################################################
# EFI_DHCP6_STATE
###################################################################
set  Dhcp6Init          0x0;
set  Dhcp6Selecting     0x1;
set  Dhcp6Requesting    0x2;
set  Dhcp6Declining     0x3;
set  Dhcp6Confirming    0x4;
set  Dhcp6Releasing     0x5;
set  Dhcp6Bound         0x6;
set  Dhcp6Renewing      0x7;
set  Dhcp6Rebinding     0x8;     

###################################################################
# EFI_DHCP6_EVENT
###################################################################
set  Dhcp6SendSolicit        0x0;
set  Dhcp6RcvdAdvertise      0x1;
set  Dhcp6SelectAdvertise    0x2;
set  Dhcp6SendRequest        0x3;
set  Dhcp6RcvdReply          0x4;
set  Dhcp6RcvdReconfigure    0x5;
set  Dhcp6SendDecline        0x6;
set  Dhcp6SendConfirm        0x7;
set  Dhcp6SendRelease        0x8;
set  Dhcp6EnterRenewing      0x9;
set  Dhcp6EnterRebinding     0xa;

###################################################################
# EFI_OPTION_TYPE
###################################################################
set Dhcp6OptClientID           1;
set Dhcp6OptServerID           2;
set Dhcp6OptIANA               3;
set Dhcp6OptIATA               4;
set Dhcp6OptIaAddr             5;
set Dhcp6OptRequestOption      6;
set Dhcp6OptPreference         7;
set Dhcp6OptElapsedTime        8;
set Dhcp6OptRelayMessage       9;
set Dhcp6OptAuthentication     11;
set Dhcp6OptServerUnicast      12;
set Dhcp6OptStatusCode         13;
set Dhcp6OptRapidCommit        14;
set Dhcp6OptUserClass          15;
set Dhcp6OptVendorClass        16;
set Dhcp6OptVendorInfo         17;
set Dhcp6OptInterfaceID        18;
set Dhcp6OptReconfigMessage    19;
set Dhcp6OptReconfigAccept     20;

set Dhcp6IATypeNA              3;
set Dhcp6IATypeTA              4;