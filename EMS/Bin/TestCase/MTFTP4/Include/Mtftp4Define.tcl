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
