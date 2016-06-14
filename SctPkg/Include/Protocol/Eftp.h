/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2015 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2015, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Eftp.h

Abstract:

  Ents File Tranfer Protocol Definition
  
--*/

#ifndef __PROTOCOL_EFTP_H__
#define __PROTOCOL_EFTP_H__

#include <Library/NetLib.h>

#define EFI_EFTP_SERVICE_BINDING_PROTOCOL_GUID \
  { \
    0x67739d1a, 0x065c, 0x4b90, { 0x90, 0xfb, 0xca, 0x4a, 0xab, 0x4c, 0x46, 0xc1 } \
  }

#define EFI_EFTP_PROTOCOL_GUID \
  { \
    0x53228ef0, 0x04eb, 0x46bd, { 0x99, 0xe2, 0x7d, 0x09, 0x4e, 0x8f, 0x8e, 0x5d } \
  }

typedef struct _EFI_EFTP_PROTOCOL EFI_EFTP_PROTOCOL;
typedef struct _EFI_EFTP_TOKEN EFI_EFTP_TOKEN;

extern EFI_GUID gEfiEftpServiceBindingProtocolGuid;
extern EFI_GUID gEfiEftpProtocolGuid;

//
// EFTP packet opcode definition
//
#define EFI_EFTP_OPCODE_RRQ   1
#define EFI_EFTP_OPCODE_WRQ   2
#define EFI_EFTP_OPCODE_DATA  3
#define EFI_EFTP_OPCODE_ACK   4
#define EFI_EFTP_OPCODE_ERROR 5
#define EFI_EFTP_OPCODE_OACK  6

//
// EFTP error code definition
//
#define EFI_EFTP_ERRORCODE_NOT_DEFINED          0
#define EFI_EFTP_ERRORCODE_FILE_NOT_FOUND       1
#define EFI_EFTP_ERRORCODE_ACCESS_VIOLATION     2
#define EFI_EFTP_ERRORCODE_DISK_FULL            3
#define EFI_EFTP_ERRORCODE_ILLEGAL_OPERATION    4
#define EFI_EFTP_ERRORCODE_UNKNOWN_TRANSFER_ID  5
#define EFI_EFTP_ERRORCODE_FILE_ALREADY_EXISTS  6
#define EFI_EFTP_ERRORCODE_NO_SUCH_USER         7
#define EFI_EFTP_ERRORCODE_REQUEST_DENIED       8
#define EFI_EFTP_ERRORCODE_TRY_LATTER           9

#define ENTS_FILE_TRANSER_PROTOCOL_MNP_TYPE     0x8888  // Host Byte Order
#define ENTS_FILE_TRANSER_PROTOCOL_IP4_TYPE     0x88

#pragma pack(1)
typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  CodeVar;
} EFTP_HEADER;
#pragma pack()
//
// EFTP pacekt definition
//
#pragma pack(1)

typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  Rsvd;
  CHAR8   Filename[1];
} EFI_EFTP_REQ_HEADER;

typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  Rsvd;
  UINT8   Data[1];
} EFI_EFTP_OACK_HEADER;

typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  Block;
  UINT8   Data[1];
} EFI_EFTP_DATA_HEADER;

typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  Block;
} EFI_EFTP_ACK_HEADER;

typedef struct {
  UINT16  Length;
  UINT16  CheckSum;
  UINT16  OpCode;
  UINT16  ErrorCode;
  CHAR8   ErrorMessage[1];
} EFI_EFTP_ERROR_HEADER;

typedef union {
  EFTP_HEADER           Hdr;
  EFI_EFTP_REQ_HEADER   Rrq;
  EFI_EFTP_REQ_HEADER   Wrq;
  EFI_EFTP_OACK_HEADER  Oack;
  EFI_EFTP_DATA_HEADER  Data;
  EFI_EFTP_ACK_HEADER   Ack;
  EFI_EFTP_ERROR_HEADER Error;
} EFI_EFTP_PACKET;

#pragma pack()
//
// EFTP option definition
//
typedef struct {
  CHAR8 *OptionStr;
  CHAR8 *ValueStr;
} EFI_EFTP_OPTION;

//
// EFTP config data
//
typedef struct {
  UINT8   DstMac[NET_ETHER_ADDR_LEN];
  UINT8   SrcMac[NET_ETHER_ADDR_LEN];
  UINT16  TryCount;
  UINT16  TimeoutValue;
} EFI_EFTP_CONFIG_DATA;

//
// EFTP Mode data
//
typedef struct {
  EFI_EFTP_CONFIG_DATA  ConfigData;
  UINT8                 SupportedOptionCount;
  CHAR8                 **SupportedOptoins;
  UINT8                 UnsupportedOptionCount;
  CHAR8                 **UnsupportedOptoins;
} EFI_EFTP_MODE_DATA;

//
// EFTP override data
//
typedef struct {
  UINT16  TryCount;
  UINT16  TimeoutValue;
} EFI_EFTP_OVERRIDE_DATA;

//
// Packet checking function
//
typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_CHECK_PACKET) (
  IN EFI_EFTP_PROTOCOL     * This,
  IN EFI_EFTP_TOKEN        * Token,
  IN UINT16                PacketLen,
  IN EFI_EFTP_PACKET       * Paket
  );

//
// Timeout callback funtion
//
typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_TIMEOUT_CALLBACK) (
  IN EFI_EFTP_PROTOCOL     * This,
  IN EFI_EFTP_TOKEN        * Token
  );

//
// Packet needed function
//
typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_PACKET_NEEDED) (
  IN EFI_EFTP_PROTOCOL     * This,
  IN EFI_EFTP_TOKEN        * Token,
  IN OUT UINT16            *Length,
  OUT VOID                 **Buffer
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_GET_MODE_DATA) (
  IN EFI_EFTP_PROTOCOL     * This,
  OUT EFI_EFTP_MODE_DATA   * ModeData
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_CONFIGURE) (
  IN EFI_EFTP_PROTOCOL     * This,
  IN EFI_EFTP_CONFIG_DATA  * EftpConfigData OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_GET_INFO) (
  IN EFI_EFTP_PROTOCOL      * This,
  IN EFI_EFTP_OVERRIDE_DATA * OverrideData OPTIONAL,
  IN CHAR8                  *Filename,
  IN CHAR8                  *ModeStr OPTIONAL,
  IN UINT8                  OptionCount,
  IN EFI_EFTP_OPTION        * OptionList,
  OUT UINT32                *PacketLength,
  OUT EFI_EFTP_PACKET       **Packet OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_PARSE_OPTIONS) (
  IN EFI_EFTP_PROTOCOL      * This,
  IN UINT32                 PacketLen,
  IN EFI_EFTP_PACKET        * Packet,
  OUT UINT32                *OptionCount,
  OUT EFI_EFTP_OPTION       **OptionList OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_READ_FILE) (
  IN EFI_EFTP_PROTOCOL      * This,
  IN EFI_EFTP_TOKEN         * Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_WRITE_FILE) (
  IN EFI_EFTP_PROTOCOL      * This,
  IN EFI_EFTP_TOKEN         * Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_READ_DIRECTORY) (
  IN EFI_EFTP_PROTOCOL      * This,
  IN EFI_EFTP_TOKEN         * Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_EFTP_POLL) (
  IN EFI_EFTP_PROTOCOL      * This
  );

struct _EFI_EFTP_PROTOCOL {
  EFI_EFTP_GET_MODE_DATA  GetModeData;
  EFI_EFTP_CONFIGURE      Configure;
  EFI_EFTP_GET_INFO       GetInfo;
  EFI_EFTP_PARSE_OPTIONS  ParseOptions;
  EFI_EFTP_READ_FILE      ReadFile;
  EFI_EFTP_WRITE_FILE     WriteFile;
  EFI_EFTP_READ_DIRECTORY ReadDirectory;
  EFI_EFTP_POLL           Poll;
};

//
// EFTP token data
//
struct _EFI_EFTP_TOKEN {
  IN OUT EFI_STATUS   Status;
  IN EFI_EVENT Event  OPTIONAL;
  IN EFI_EFTP_OVERRIDE_DATA * OverrideData OPTIONAL;
  IN CHAR8  *Filename;
  IN CHAR8 *ModeStr OPTIONAL;
  IN UINT32 OptionCount;
  IN EFI_EFTP_OPTION * OptionList OPTIONAL;
  IN OUT UINT64 BufferSize;
  IN OUT VOID *Buffer OPTIONAL;
  IN VOID *Context OPTIONAL;
  IN EFI_EFTP_CHECK_PACKET CheckPacket          OPTIONAL;
  IN EFI_EFTP_TIMEOUT_CALLBACK TimeoutCallback  OPTIONAL;
  IN EFI_EFTP_PACKET_NEEDED PacketNeeded        OPTIONAL;
};

#endif
