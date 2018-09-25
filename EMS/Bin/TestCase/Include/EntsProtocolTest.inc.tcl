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
if {[info exist ENTS_PROTOCOL_INC] == 1} {
  return
}
set ENTS_PROTOCOL_INC 1

set EMS_PLATFORM_TYPE [GetTargetBits]

if {$EMS_PLATFORM_TYPE == "64"} {
  set EFI_SUCCESS                    0x0       
	set EFI_LOAD_ERROR                 0x8000000000000001
	set EFI_INVALID_PARAMETER          0x8000000000000002
	set EFI_UNSUPPORTED                0x8000000000000003
	set EFI_BAD_BUFFER_SIZE            0x8000000000000004
	set EFI_BUFFER_TOO_SMALL           0x8000000000000005
	set EFI_NOT_READY                  0x8000000000000006
	set EFI_DEVICE_ERROR               0x8000000000000007
	set EFI_WRITE_PROTECTED            0x8000000000000008
	set EFI_OUT_OF_RESOURCES           0x8000000000000009
	set EFI_VOLUME_CORRUPTED           0x800000000000000a
	set EFI_VOLUME_FULL                0x800000000000000b
	set EFI_NO_MEDIA                   0x800000000000000c
	set EFI_MEDIA_CHANGED              0x800000000000000d
	set EFI_NOT_FOUND                  0x800000000000000e
	set EFI_ACCESS_DENIED              0x800000000000000f
	set EFI_NO_RESPONSE                0x8000000000000010
	set EFI_NO_MAPPING                 0x8000000000000011
	set EFI_TIMEOUT                    0x8000000000000012
	set EFI_NOT_STARTED                0x8000000000000013
	set EFI_ALREADY_STARTED            0x8000000000000014
	set EFI_ABORTED                    0x8000000000000015
	set EFI_ICMP_ERROR                 0x8000000000000016
	set EFI_TFTP_ERROR                 0x8000000000000017
	set EFI_PROTOCOL_ERROR             0x8000000000000018
	set EFI_INCOMPATIBLE_VERSION       0x8000000000000019
	set EFI_SECURITY_VIOLATION         0x800000000000001a
	set EFI_CRC_ERROR                  0x800000000000001b
	set EFI_NOT_AVAILABLE_YET          0x800000000000001c
	set EFI_UNLOAD_IMAGE               0x800000000000001d
	set EFI_NETWORK_UNREACHABLE        0x8000000000000064
	set EFI_HOST_UNREACHABLE           0x8000000000000065
	set EFI_PROTOCOL_UNREACHABLE       0x8000000000000066
	set EFI_PORT_UNREACHABLE           0x8000000000000067
	set EFI_CONNECTION_FIN             0x8000000000000068
	set EFI_CONNECTION_RESET           0x8000000000000069
	set EFI_CONNECTION_REFUSED         0x800000000000006a  
} else {
  set EFI_SUCCESS                    0x0       
	set EFI_LOAD_ERROR                 0x80000001
	set EFI_INVALID_PARAMETER          0x80000002
	set EFI_UNSUPPORTED                0x80000003
	set EFI_BAD_BUFFER_SIZE            0x80000004
	set EFI_BUFFER_TOO_SMALL           0x80000005
	set EFI_NOT_READY                  0x80000006
	set EFI_DEVICE_ERROR               0x80000007
	set EFI_WRITE_PROTECTED            0x80000008
	set EFI_OUT_OF_RESOURCES           0x80000009
	set EFI_VOLUME_CORRUPTED           0x8000000a
	set EFI_VOLUME_FULL                0x8000000b
	set EFI_NO_MEDIA                   0x8000000c
	set EFI_MEDIA_CHANGED              0x8000000d
	set EFI_NOT_FOUND                  0x8000000e
	set EFI_ACCESS_DENIED              0x8000000f
	set EFI_NO_RESPONSE                0x80000010
	set EFI_NO_MAPPING                 0x80000011
	set EFI_TIMEOUT                    0x80000012
	set EFI_NOT_STARTED                0x80000013
	set EFI_ALREADY_STARTED            0x80000014
	set EFI_ABORTED                    0x80000015
	set EFI_ICMP_ERROR                 0x80000016
	set EFI_TFTP_ERROR                 0x80000017
	set EFI_PROTOCOL_ERROR             0x80000018
	set EFI_INCOMPATIBLE_VERSION       0x80000019
	set EFI_SECURITY_VIOLATION         0x8000001a
	set EFI_CRC_ERROR                  0x8000001b
	set EFI_NOT_AVAILABLE_YET          0x8000001c
	set EFI_UNLOAD_IMAGE               0x8000001d
	set EFI_NETWORK_UNREACHABLE        0x80000064
	set EFI_HOST_UNREACHABLE           0x80000065
	set EFI_PROTOCOL_UNREACHABLE       0x80000066
	set EFI_PORT_UNREACHABLE           0x80000067
	set EFI_CONNECTION_FIN             0x80000068
	set EFI_CONNECTION_RESET           0x80000069
	set EFI_CONNECTION_REFUSED         0x8000006a  
}
                                             
set EFI_WARN_UNKNOWN_GLYPH         0x1       
set EFI_WARN_DELETE_FAILURE        0x2       
set EFI_WARN_WRITE_FAILURE         0x3       
set EFI_WARN_BUFFER_TOO_SMALL      0x4       
set EFI_WARN_RETURN_FROM_LONG_JUMP 0x5       

set DEF_ENTS_IP_ADDR  192.168.88.1
set DEF_ENTS_MAC_ADDR [GetMac]
set DEF_ENTS_MASK     255.255.255.0
set DEF_ENTS_PRT      8888

Struct EFI_IPv4_ADDRESS {
  UINT8             Addr(4);
}

Struct EFI_IPv6_ADDRESS {
  UINT8             Addr(16);
}

Union EFI_IP_ADDRESS {
  UINT32            Addr(4);
  EFI_IPv4_ADDRESS  v4;
  EFI_IPv6_ADDRESS  v6;
}

Struct EFI_MAC_ADDRESS {
  UINT8             Addr(32);
}

Struct EFI_GUID {
  UINT32            Data1;
  UINT16            Data2;
  UINT16            Data3;
  UINT8             Data4(8);
}

Struct EFI_TIME {
  UINT16            Year; 
  UINT8             Month;
  UINT8             Day; 
  UINT8             Hour;
  UINT8             Minute;
  UINT8             Second;
  UINT8             Pad1;
  UINT32            Nanosecond;
  INT16             TimeZone; 
  UINT8             Daylight;
  UINT8             Pad2;
}

Struct EFI_EVENT {
  POINTER           Event;
}

#CurrentChild  
set       ENTS_CUR_CHILD  CurrentChild
UINTN     [subst $ENTS_CUR_CHILD]
set       FUNC_DELAY_TIME DelayTime
set       EXEC_TIME_NAME  ExecTime

proc SetCurrentChild {handle} {
global  CurrentChild

  SetVar  CurrentChild    $handle
}

proc GetCurrentChild {} {
  global  CurrentChild
  
  GetVar  CurrentChild
  return  $CurrentChild
}              
