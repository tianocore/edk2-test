# 
#  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
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

