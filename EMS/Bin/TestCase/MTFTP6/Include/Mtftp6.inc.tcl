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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
if {[info exist MTFTP6_INC] == 1} {
  return
}
set MTFTP6_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include SNP/Include/Snp.inc.tcl
Include MNP/Include/Mnp.inc.tcl
Include MNP/Include/Mnp.proc.tcl
Include IP6/Include/Ip6.inc.tcl
Include Udp6/Include/Udp6.inc.tcl
Include IP6Config/Include/Ip6Config.inc.tcl
Include MTFTP6/Include/Mtftp6Define.tcl
Include MTFTP6/Include/Mtftp6.proc.tcl
Include Include/GenericAssertionGuid.tcl
Include MTFTP6/Include/Mtftp6AssertionGuid.tcl

############################################################################
# Function Declaration
############################################################################

Func Mtftp6ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Mtftp6ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Mtftp6->GetModeData {
  POINTER
  POINTER
  }

Func Mtftp6->Configure {
  POINTER 
  POINTER
  }

Func Mtftp6->GetInfo {
  POINTER
  POINTER
  POINTER
  UINT8
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Mtftp6->ParseOptions {
  UINT32 
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Mtftp6->ReadFile {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
  }

Func Mtftp6->WriteFile {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
  }

Func Mtftp6->ReadDirectory {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
 }

Func Mtftp6->Poll {
  POINTER
 }

###################################################################
# EFI_MTFTP6_CONFIG_DATA
###################################################################
Struct EFI_MTFTP6_CONFIG_DATA {
  EFI_IPv6_ADDRESS        StationIp;
  UINT16                  LocalPort;
  EFI_IPv6_ADDRESS        ServerIp;
  UINT16                  InitialServerPort;
  UINT16                  TryCount;
  UINT16                  TimeoutValue;
}

###################################################################
# EFI_MTFTP6_MODE_DATA
###################################################################
Struct EFI_MTFTP6_MODE_DATA {
  EFI_MTFTP6_CONFIG_DATA  ConfigData;
  UINT8                   SupportedOptionCount;
  POINTER                 SupportedOptions;
}

###################################################################
# EFI_MTFTP6_OVERRIDE_DATA
###################################################################
Struct EFI_MTFTP6_OVERRIDE_DATA {
  EFI_IPv6_ADDRESS        ServerIp;
  UINT16                  ServerPort;
  UINT16                  TryCount;
  UINT16                  TimeoutValue;
}

###################################################################
# EFI_MTFTP6_OPTION
###################################################################
Struct EFI_MTFTP6_OPTION {
  POINTER                 OptionStr;
  POINTER                 ValueStr;
}

###################################################################
#
# EFI_MTFTP6_PACKET and Related Definitions
#
###################################################################
Struct EFI_MTFTP6_REQ_HEADER {
  UINT16                  OpCode;
  UINT8                   Filename(300);
}

Struct EFI_MTFTP6_OACK_HEADER {
  UINT16                  OpCode;
  UINT8                   Data(300);
}

Struct EFI_MTFTP6_DATA_HEADER {
  UINT16                  OpCode;
  UINT16                  Block;
  UINT8                   Data(2000);
}

# MTFP6 Data8 field  should be ignored and treated as reserved
Struct EFI_MTFTP6_DATA8_HEADER {
  UINT16                  OpCode;
  UINT64                  Block;
  UINT8                   Data(2000);
}

# MTFP6 Ack8 field  should be ignored and treated as reserved
Struct EFI_MTFTP6_ACK8_HEADER {
  UINT16                  OpCode;
  UINT64                  Block(300);
}

Struct EFI_MTFTP6_ERROR_HEADER {
  UINT16                  OpCode;
  UINT16                  ErrorCode;
  UINT8                   ErrorMessage(300);
}

Struct EFI_MTFTP6_ACK_HEADER {
  UINT16                  Opcode;
  UINT16                  Block(300);
}

###################################################################
# EFI_MTFTP6_TOKEN
###################################################################
Struct EFI_MTFTP6_TOKEN {
  UINTN                       Status;
  UINTN                       Event;
  POINTER                     OverrideData;
  POINTER                     Filename;
  POINTER                     ModeStr;
  UINT32                      OptionCount;
  POINTER                     OptionList;
  UINT64                      BufferSize;
  POINTER                     Buffer;
  POINTER                     Context;
  POINTER                     CheckPacket;
  POINTER                     TimeoutCallback;
  POINTER                     PacketNeeded;
}

##################################################################
# MTFP6 Data8 field  should be ignored and treated as reserved
# MTFP6 Ack8 field  should be ignored and treated as reserved
##################################################################
Union EFI_MTFTP6_PACKET {
  UINT16                  OpCode;
  EFI_MTFTP6_REQ_HEADER   Rrq;
  EFI_MTFTP6_REQ_HEADER   Wrq;
  EFI_MTFTP6_OACK_HEADER  Oack;
  EFI_MTFTP6_DATA_HEADER  Data;
  EFI_MTFTP6_ACK_HEADER   Ack;
  EFI_MTFTP6_DATA8_HEADER Data8;
  EFI_MTFTP6_ACK8_HEADER  Ack8;
  EFI_MTFTP6_ERROR_HEADER Error;
}

