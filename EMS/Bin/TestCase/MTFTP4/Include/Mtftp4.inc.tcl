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
if {[info exist MTFTP_INC] == 1} {
  return
}
set MTFTP_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include Include/GenericAssertionGuid.tcl

Include SNP/Include/Snp.inc.tcl
Include MNP/Include/Mnp.inc.tcl
Include ARP/Include/Arp.inc.tcl
Include IP4/Include/Ip4.inc.tcl
Include Udp4/Include/Udp4.inc.tcl
Include MTFTP4/Include/Mtftp4AssertionGuid.tcl
Include MTFTP4/Include/Mtftp4Define.tcl
Include MTFTP4/Include/Mtftp4.proc.tcl

Func Mtftp4ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Mtftp4ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Mtftp4->GetModeData {
  POINTER
  POINTER
  }

Func Mtftp4->Configure {
  POINTER 
  POINTER
  }

Func Mtftp4->GetInfo {
  POINTER
  POINTER
  POINTER
  UINT8
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Mtftp4->ParseOptions {
  UINT32 
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func Mtftp4->ReadFile {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
  }

Func Mtftp4->WriteFile {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
  }

Func Mtftp4->ReadDirectory {
  POINTER
  UINTN
  UINTN
  UINTN
  POINTER
 }

Func Mtftp4->Poll {
  POINTER
 }

###################################################################
# EFI_MTFTP4_CONFIG_DATA
###################################################################
Struct EFI_MTFTP4_CONFIG_DATA {
  BOOLEAN                 UseDefaultSetting;
  EFI_IPv4_ADDRESS        StationIp;
  EFI_IPv4_ADDRESS        SubnetMask;
  UINT16                  LocalPort;
  EFI_IPv4_ADDRESS        GatewayIp;
  EFI_IPv4_ADDRESS        ServerIp;
  UINT16                  InitialServerPort;
  UINT16                  TryCount;
  UINT16                  TimeoutValue;
}


###################################################################
# EFI_MTFTP4_MODE_DATA
###################################################################
Struct EFI_MTFTP4_MODE_DATA {
  EFI_MTFTP4_CONFIG_DATA  ConfigData;
  UINT8                   SupportedOptionCount;
  POINTER                 SupportedOptions;
  UINT8                   UnsupportedOptionCount;
  POINTER                 UnsupportedOptions;
}


###################################################################
# EFI_MTFTP4_OVERRIDE_DATA
###################################################################
Struct EFI_MTFTP4_OVERRIDE_DATA {
  EFI_IPv4_ADDRESS        GatewayIp;
  EFI_IPv4_ADDRESS        ServerIp;
  UINT16                  ServerPort;
  UINT16                  TryCount;
  UINT16                  TimeoutValue;
}


###################################################################
# EFI_MTFTP4_OPTION
###################################################################
Struct EFI_MTFTP4_OPTION {
  POINTER                 OptionStr;
  POINTER                 ValueStr;
}


###################################################################
#
# EFI_MTFTP4_PACKET and Related Definitions
#
###################################################################
Struct EFI_MTFTP4_REQ_HEADER {
  UINT16                  OpCode;
  UINT8                   Filename(300);
}


Struct EFI_MTFTP4_OACK_HEADER {
  UINT16                  OpCode;
  UINT8                   Data(300);
}


Struct EFI_MTFTP4_DATA_HEADER {
  UINT16                  OpCode;
  UINT16                  Block;
  UINT8                   Data(2000);
}

# MTFP4 Data8 field  should be ignored and treated as reserved
Struct EFI_MTFTP4_DATA8_HEADER {
  UINT16                  OpCode;
  UINT64                  Block;
  UINT8                   Data(2000);
}


# MTFP4 Ack8 field  should be ignored and treated as reserved
Struct EFI_MTFTP4_ACK8_HEADER {
  UINT16                  OpCode;
  UINT64                  Block(300);
}


Struct EFI_MTFTP4_ERROR_HEADER {
  UINT16                  OpCode;
  UINT16                  ErrorCode;
  UINT8                   ErrorMessage(300);
}


Struct EFI_MTFTP4_HEADER_ACK {
  UINT16                  Opcode;
  UINT16                  Block(300);
}

#############################################################
#   MTFP4 Data8 field  should be ignored and treated as reserved
#   MTFP4 Ack8 field  should be ignored and treated as reserved
#############################################################
Union EFI_MTFTP4_PACKET {
  UINT16                  OpCode;
  EFI_MTFTP4_REQ_HEADER   Rrq;
  EFI_MTFTP4_REQ_HEADER   Wrq;
  EFI_MTFTP4_OACK_HEADER  Oack;
  EFI_MTFTP4_DATA_HEADER  Data;
  EFI_MTFTP4_HEADER_ACK   Ack;
  EFI_MTFTP4_DATA8_HEADER Data8;
  EFI_MTFTP4_ACK8_HEADER  Ack8;
  EFI_MTFTP4_ERROR_HEADER Error;
}


###################################################################
# EFI_MTFTP4_TOKEN
###################################################################
Struct EFI_MTFTP4_TOKEN {
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
