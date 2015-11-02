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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Mtftp4.h

Abstract:
  EFI Multicast Trivial File Tranfer Protocol Definition
  
--*/

#ifndef __PROTOCOL_MTFTP4_H__
#define __PROTOCOL_MTFTP4_H__

#include <Protocol/ServiceBinding.h>
#include <UEFI/Protocol/Ip4.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_MTFTP4_SERVICE_BINDING_PROTOCOL;

#define EFI_MTFTP4_SERVICE_BINDING_PROTOCOL_GUID \
    { 0x2FE800BE, 0x8F01, 0x4aa6, 0x94, 0x6B, 0xD7, 0x13, 0x88, 0xE1, 0x83, 0x3F };

#define EFI_MTFTP4_PROTOCOL_GUID \
    { 0x78247c57, 0x63db, 0x4708, 0x99, 0xc2, 0xa8, 0xb4, 0xa9, 0xa6, 0x1f, 0x6b }

typedef struct _EFI_MTFTP4_PROTOCOL EFI_MTFTP4_PROTOCOL;
typedef struct _EFI_MTFTP4_TOKEN EFI_MTFTP4_TOKEN;

extern EFI_GUID gBlackBoxEfiMtftp4ServiceBindingProtocolGuid;
extern EFI_GUID gBlackBoxEfiMtftp4ProtocolGuid;


//
//MTFTP4 packet opcode definition
//
#define EFI_MTFTP4_OPCODE_RRQ      1
#define EFI_MTFTP4_OPCODE_WRQ      2
#define EFI_MTFTP4_OPCODE_DATA     3
#define EFI_MTFTP4_OPCODE_ACK      4
#define EFI_MTFTP4_OPCODE_ERROR    5
#define EFI_MTFTP4_OPCODE_OACK     6
#define EFI_MTFTP4_OPCODE_DIR      7
// This type  should be ignored and treated as reserved
#define EFI_MTFTP4_OPCODE_DATA8    8
// This type  should be ignored and treated as reserved
#define EFI_MTFTP4_OPCODE_ACK8     9

//
//MTFTP4 error code definition
//
#define EFI_MTFTP4_ERRORCODE_NOT_DEFINED           0
#define EFI_MTFTP4_ERRORCODE_FILE_NOT_FOUND        1
#define EFI_MTFTP4_ERRORCODE_ACCESS_VIOLATION      2
#define EFI_MTFTP4_ERRORCODE_DISK_FULL             3
#define EFI_MTFTP4_ERRORCODE_ILLEGAL_OPERATION     4
#define EFI_MTFTP4_ERRORCODE_UNKNOWN_TRANSFER_ID   5
#define EFI_MTFTP4_ERRORCODE_FILE_ALREADY_EXISTS   6
#define EFI_MTFTP4_ERRORCODE_NO_SUCH_USER          7
#define EFI_MTFTP4_ERRORCODE_REQUEST_DENIED        8
#define EFI_MTFTP4_ERRORCODE_TRY_LATTER            9

//
//MTFTP4 pacekt definition
//
#pragma pack(1)

typedef struct {
  UINT16    OpCode;
  UINT8     Filename[1];
} EFI_MTFTP4_REQ_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT8     Data[1];
} EFI_MTFTP4_OACK_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    Block;
  UINT8     Data[1];
} EFI_MTFTP4_DATA_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    Block[1];
} EFI_MTFTP4_ACK_HEADER;

// This structure  should be ignored and treated as reserved
typedef struct {
  UINT16    OpCode;
  UINT64    Block;
  UINT8     Data[1];
} EFI_MTFTP4_DATA8_HEADER;

// This structure  should be ignored and treated as reserved
typedef struct {
  UINT16    OpCode;
  UINT64    Block[1];
} EFI_MTFTP4_ACK8_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    ErrorCode;
  UINT8     ErrorMessage[1];
} EFI_MTFTP4_ERROR_HEADER;

typedef union {
  UINT16                    OpCode;
  EFI_MTFTP4_REQ_HEADER     Rrq;
  EFI_MTFTP4_REQ_HEADER     Wrq;
  EFI_MTFTP4_OACK_HEADER    Oack;
  EFI_MTFTP4_DATA_HEADER    Data;
  EFI_MTFTP4_ACK_HEADER     Ack;
  // This field should be ignored and treated as reserved
  EFI_MTFTP4_DATA8_HEADER   Data8;
  // This field should be ignored and treated as reserved
  EFI_MTFTP4_ACK8_HEADER    Ack8;
  EFI_MTFTP4_ERROR_HEADER   Error;
} EFI_MTFTP4_PACKET;

#pragma pack()

//
//MTFTP4 option definition
//
typedef struct {
  UINT8                   *OptionStr;
  UINT8                   *ValueStr;
} EFI_MTFTP4_OPTION;

//
//MTFTP4 config data
//
typedef struct {
  BOOLEAN          UseDefaultSetting;
  EFI_IPv4_ADDRESS StationIp;
  EFI_IPv4_ADDRESS SubnetMask;
  UINT16           LocalPort;
  EFI_IPv4_ADDRESS GatewayIp;
  EFI_IPv4_ADDRESS ServerIp;
  UINT16           InitialServerPort;
  UINT16           TryCount;
  UINT16           TimeoutValue;
} EFI_MTFTP4_CONFIG_DATA;

//
//MTFTP4 Mode data
//
typedef struct {
  EFI_MTFTP4_CONFIG_DATA     ConfigData;
  UINT8                      SupportedOptionCount;  
  UINT8                      **SupportedOptoins;
  UINT8                      UnsupportedOptionCount;  
  UINT8                      **UnsupportedOptoins;
} EFI_MTFTP4_MODE_DATA;


//
//MTFTP4 override data
//
typedef struct {
  EFI_IPv4_ADDRESS GatewayIp;
  EFI_IPv4_ADDRESS ServerIp;
  UINT16           ServerPort;
  UINT16           TryCount;
  UINT16           TimeoutValue;
} EFI_MTFTP4_OVERRIDE_DATA;


//
//Packet checking function
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_CHECK_PACKET) ( 
  IN EFI_MTFTP4_PROTOCOL    *This,
  IN EFI_MTFTP4_TOKEN       *Token,
  IN UINT16                 PacketLen,
  IN EFI_MTFTP4_PACKET      *Paket
  );

//
//Timeout callback funtion
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_TIMEOUT_CALLBACK) ( 
  IN EFI_MTFTP4_PROTOCOL    *This,
  IN EFI_MTFTP4_TOKEN       *Token
  );

//
//Packet needed function
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_PACKET_NEEDED) ( 
  IN EFI_MTFTP4_PROTOCOL    *This,
  IN EFI_MTFTP4_TOKEN       *Token,
  IN OUT UINT16             *Length,
  OUT VOID                  **Buffer
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_GET_MODE_DATA) (
  IN EFI_MTFTP4_PROTOCOL      *This,
  OUT EFI_MTFTP4_MODE_DATA    *ModeData
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_CONFIGURE) (
  IN EFI_MTFTP4_PROTOCOL      *This,
  IN EFI_MTFTP4_CONFIG_DATA   *MtftpConfigData OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_GET_INFO) (
  IN EFI_MTFTP4_PROTOCOL        *This,
  IN EFI_MTFTP4_OVERRIDE_DATA   *OverrideData   OPTIONAL,
  IN UINT8                      *Filename,
  IN UINT8                      *ModeStr        OPTIONAL,
  IN UINT8                      OptionCount,
  IN EFI_MTFTP4_OPTION          *OptionList     OPTIONAL,
  OUT UINT32                    *PacketLength,
  OUT EFI_MTFTP4_PACKET         **Packet        OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_PARSE_OPTIONS) (
  IN EFI_MTFTP4_PROTOCOL      *This,
  IN UINT32                   PacketLen,
  IN EFI_MTFTP4_PACKET        *Packet,
  OUT UINT32                  *OptionCount,
  OUT EFI_MTFTP4_OPTION       **OptionList      OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_READ_FILE) (
  IN EFI_MTFTP4_PROTOCOL     *This,
  IN EFI_MTFTP4_TOKEN        *Token
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_WRITE_FILE) (
  IN EFI_MTFTP4_PROTOCOL     *This,
  IN EFI_MTFTP4_TOKEN        *Token
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_READ_DIRECTORY) (
  IN EFI_MTFTP4_PROTOCOL  *This,
  IN EFI_MTFTP4_TOKEN     *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP4_POLL) (
  IN EFI_MTFTP4_PROTOCOL        *This
);


struct _EFI_MTFTP4_PROTOCOL {
  EFI_MTFTP4_GET_MODE_DATA    GetModeData;
  EFI_MTFTP4_CONFIGURE        Configure;
  EFI_MTFTP4_GET_INFO         GetInfo;
  EFI_MTFTP4_PARSE_OPTIONS    ParseOptions;
  EFI_MTFTP4_READ_FILE        ReadFile;
  EFI_MTFTP4_WRITE_FILE       WriteFile;
  EFI_MTFTP4_READ_DIRECTORY   ReadDirectory;
  EFI_MTFTP4_POLL             Poll;
};

//
//MTFTP4 token data
//
struct _EFI_MTFTP4_TOKEN{
  IN OUT EFI_STATUS               Status;
  IN EFI_EVENT                    Event;
  IN EFI_MTFTP4_OVERRIDE_DATA     *OverrideData      OPTIONAL;
  IN UINT8                        *Filename;
  IN UINT8                        *ModeStr           OPTIONAL;
  IN UINT32                       OptionCount;
  IN EFI_MTFTP4_OPTION            *OptionList        OPTIONAL;
  IN UINT64                       BufferSize;
  OUT VOID                        *Buffer            OPTIONAL;
  IN VOID                         *Context;
  IN EFI_MTFTP4_CHECK_PACKET      CheckPacket        OPTIONAL;
  IN EFI_MTFTP4_TIMEOUT_CALLBACK  TimeoutCallback    OPTIONAL;
  IN EFI_MTFTP4_PACKET_NEEDED     PacketNeeded       OPTIONAL;
};

#endif

