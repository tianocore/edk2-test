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
