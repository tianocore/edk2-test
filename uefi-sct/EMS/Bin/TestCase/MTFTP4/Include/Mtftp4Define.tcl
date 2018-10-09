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
if {[info exist MTFTP4_DEFINES_TCL] == 1} {
  return
}
set MTFTP4_DEFINES_TCL 1

#
#MTFTP4 packet opcode definition
#
set EFI_MTFTP4_OPCODE_RRQ      1
set EFI_MTFTP4_OPCODE_WRQ      2
set EFI_MTFTP4_OPCODE_DATA     3
set EFI_MTFTP4_OPCODE_ACK      4
set EFI_MTFTP4_OPCODE_ERROR    5
set EFI_MTFTP4_OPCODE_OACK     6
set EFI_MTFTP4_OPCODE_DIR      7
#
# MTFP4 Data8 type  should be ignored and treated as reserved
# set EFI_MTFTP4_OPCODE_DATA8    8
# MTFP4 Ack8 type  should be ignored and treated as reserved
# set EFI_MTFTP4_OPCODE_ACK8     9
#

#
#MTFTP4 error code definition
#
set EFI_MTFTP4_ERRORCODE_NOT_DEFINED           0
set EFI_MTFTP4_ERRORCODE_FILE_NOT_FOUND        1
set EFI_MTFTP4_ERRORCODE_ACCESS_VIOLATION      2
set EFI_MTFTP4_ERRORCODE_DISK_FULL             3
set EFI_MTFTP4_ERRORCODE_ILLEGAL_OPERATION     4
set EFI_MTFTP4_ERRORCODE_UNKNOWN_TRANSFER_ID   5
set EFI_MTFTP4_ERRORCODE_FILE_ALREADY_EXISTS   6
set EFI_MTFTP4_ERRORCODE_NO_SUCH_USER          7
set EFI_MTFTP4_ERRORCODE_REQUEST_DENIED        8

set DEF_EUT_IP_ADDR   192.168.88.88
set DEF_EUT_MAC_ADDR  [GetTargetMac]

set DEF_OS_IP_ADDR    192.168.88.1
set DEF_OS_MAC_ADDR   [GetHostMac]

set DEF_ENTS_IP_ADDR  192.168.88.1
set DEF_ENTS_MAC_ADDR [GetHostMac]

set DEF_DEST_PRT      2048
set DEF_SRC_PRT       4096
set DEF_SERVER_PRT    69

#end of MTFTP4_DEFINES_TCL
