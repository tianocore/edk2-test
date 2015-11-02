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

  Mtftp6.h

Abstract:
  EFI Multicast Trivial File Tranfer Protocol Definition
  
--*/

#ifndef __PROTOCOL_MTFTP6_H__
#define __PROTOCOL_MTFTP6_H__

#include <Protocol/ServiceBinding.h>
#include <UEFI/Protocol/SimpleNetwork.h>
#include <UEFI/Protocol/ManagedNetwork.h>
#include <UEFI/Protocol/Ip6.h>

typedef EFI_SERVICE_BINDING_PROTOCOL EFI_MTFTP6_SERVICE_BINDING_PROTOCOL;

#define EFI_MTFTP6_SERVICE_BINDING_PROTOCOL_GUID \
    { 0xd9760ff3, 0x3cca, 0x4267, 0x80, 0xf9, 0x75, 0x27, 0xfa, 0xfa, 0x42, 0x23 };

#define EFI_MTFTP6_PROTOCOL_GUID \
    { 0xbf0a78ba, 0xec29, 0x49cf, 0xa1, 0xc9, 0x7a, 0xe5, 0x4e, 0xab, 0x6a, 0x51 }

typedef struct _EFI_MTFTP6_PROTOCOL EFI_MTFTP6_PROTOCOL;
typedef struct _EFI_MTFTP6_TOKEN EFI_MTFTP6_TOKEN;

extern EFI_GUID gBlackBoxEfiMtftp6ServiceBindingProtocolGuid;
extern EFI_GUID gBlackBoxEfiMtftp6ProtocolGuid;


//
//MTFTP6 packet opcode definition
//
#define EFI_MTFTP6_OPCODE_RRQ      1
#define EFI_MTFTP6_OPCODE_WRQ      2
#define EFI_MTFTP6_OPCODE_DATA     3
#define EFI_MTFTP6_OPCODE_ACK      4
#define EFI_MTFTP6_OPCODE_ERROR    5
#define EFI_MTFTP6_OPCODE_OACK     6
#define EFI_MTFTP6_OPCODE_DIR      7
// This type  should be ignored and treated as reserved
#define EFI_MTFTP6_OPCODE_DATA8    8
// This type  should be ignored and treated as reserved
#define EFI_MTFTP6_OPCODE_ACK8     9

//
//MTFTP6 error code definition
//
#define EFI_MTFTP6_ERRORCODE_NOT_DEFINED           0
#define EFI_MTFTP6_ERRORCODE_FILE_NOT_FOUND        1
#define EFI_MTFTP6_ERRORCODE_ACCESS_VIOLATION      2
#define EFI_MTFTP6_ERRORCODE_DISK_FULL             3
#define EFI_MTFTP6_ERRORCODE_ILLEGAL_OPERATION     4
#define EFI_MTFTP6_ERRORCODE_UNKNOWN_TRANSFER_ID   5
#define EFI_MTFTP6_ERRORCODE_FILE_ALREADY_EXISTS   6
#define EFI_MTFTP6_ERRORCODE_NO_SUCH_USER          7
#define EFI_MTFTP6_ERRORCODE_REQUEST_DENIED        8


//
//MTFTP6 pacekt definition
//
#pragma pack(1)

typedef struct {
  UINT16    OpCode;
  UINT8     Filename[1];
} EFI_MTFTP6_REQ_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT8     Data[1];
} EFI_MTFTP6_OACK_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    Block;
  UINT8     Data[1];
} EFI_MTFTP6_DATA_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    Block[1];
} EFI_MTFTP6_ACK_HEADER;

// This structure should be ignored and treated as reserved
typedef struct {
  UINT16    OpCode;
  UINT64    Block;
  UINT8     Data[1];
} EFI_MTFTP6_DATA8_HEADER;

// This structure should be ignored and treated as reserved
typedef struct {
  UINT16    OpCode;
  UINT64    Block[1];
} EFI_MTFTP6_ACK8_HEADER;

typedef struct {
  UINT16    OpCode;
  UINT16    ErrorCode;
  UINT8     ErrorMessage[1];
} EFI_MTFTP6_ERROR_HEADER;

typedef union {
  UINT16                    OpCode;
  EFI_MTFTP6_REQ_HEADER     Rrq;
  EFI_MTFTP6_REQ_HEADER     Wrq;
  EFI_MTFTP6_OACK_HEADER    Oack;
  EFI_MTFTP6_DATA_HEADER    Data;
  EFI_MTFTP6_ACK_HEADER     Ack;
  // This field should be ignored and treated as reserved
  EFI_MTFTP6_DATA8_HEADER   Data8;
  // This field should be ignored and treated as reserved
  EFI_MTFTP6_ACK8_HEADER    Ack8;
  EFI_MTFTP6_ERROR_HEADER   Error;
} EFI_MTFTP6_PACKET;

#pragma pack()

//
//MTFTP6 option definition
//
typedef struct {
  UINT8                   *OptionStr;
  UINT8                   *ValueStr;
} EFI_MTFTP6_OPTION;

//
//MTFTP6 config data
//
typedef struct {
  EFI_IPv6_ADDRESS StationIp;
  UINT16           LocalPort;
  EFI_IPv6_ADDRESS ServerIp;
  UINT16           InitialServerPort;
  UINT16           TryCount;
  UINT16           TimeoutValue;
} EFI_MTFTP6_CONFIG_DATA;

//
//MTFTP6Mode data
//
typedef struct {
  EFI_MTFTP6_CONFIG_DATA     ConfigData;
  UINT8                      SupportedOptionCount;  
  UINT8                      **SupportedOptoins;
} EFI_MTFTP6_MODE_DATA;


//
//MTFTP6 override data
//
typedef struct {
  EFI_IPv6_ADDRESS ServerIp;
  UINT16           ServerPort;
  UINT16           TryCount;
  UINT16           TimeoutValue;
} EFI_MTFTP6_OVERRIDE_DATA;


//
//Packet checking function
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_CHECK_PACKET) ( 
  IN EFI_MTFTP6_PROTOCOL    *This,
  IN EFI_MTFTP6_TOKEN       *Token,
  IN UINT16                 PacketLen,
  IN EFI_MTFTP6_PACKET      *Paket
  );

//
//Timeout callback funtion
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_TIMEOUT_CALLBACK) ( 
  IN EFI_MTFTP6_PROTOCOL    *This,
  IN EFI_MTFTP6_TOKEN       *Token
  );

//
//Packet needed function
//
typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_PACKET_NEEDED) ( 
  IN EFI_MTFTP6_PROTOCOL    *This,
  IN EFI_MTFTP6_TOKEN       *Token,
  IN OUT UINT16             *Length,
  OUT VOID                  **Buffer
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_GET_MODE_DATA) (
  IN EFI_MTFTP6_PROTOCOL      *This,
  OUT EFI_MTFTP6_MODE_DATA    *ModeData
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_CONFIGURE) (
  IN EFI_MTFTP6_PROTOCOL      *This,
  IN EFI_MTFTP6_CONFIG_DATA   *MtftpConfigData OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_GET_INFO) (
  IN EFI_MTFTP6_PROTOCOL        *This,
  IN EFI_MTFTP6_OVERRIDE_DATA   *OverrideData   OPTIONAL,
  IN UINT8                      *Filename,
  IN UINT8                      *ModeStr        OPTIONAL,
  IN UINT8                      OptionCount,
  IN EFI_MTFTP6_OPTION          *OptionList     OPTIONAL,
  OUT UINT32                    *PacketLength,
  OUT EFI_MTFTP6_PACKET         **Packet        OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_PARSE_OPTIONS) (
  IN EFI_MTFTP6_PROTOCOL      *This,
  IN UINT32                   PacketLen,
  IN EFI_MTFTP6_PACKET        *Packet,
  OUT UINT32                  *OptionCount,
  OUT EFI_MTFTP6_OPTION       **OptionList      OPTIONAL
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_READ_FILE) (
  IN EFI_MTFTP6_PROTOCOL     *This,
  IN EFI_MTFTP6_TOKEN        *Token
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_WRITE_FILE) (
  IN EFI_MTFTP6_PROTOCOL     *This,
  IN EFI_MTFTP6_TOKEN        *Token
  );


typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_READ_DIRECTORY) (
  IN EFI_MTFTP6_PROTOCOL  *This,
  IN EFI_MTFTP6_TOKEN     *Token
  );

typedef
EFI_STATUS
(EFIAPI *EFI_MTFTP6_POLL) (
  IN EFI_MTFTP6_PROTOCOL        *This
);


struct _EFI_MTFTP6_PROTOCOL {
  EFI_MTFTP6_GET_MODE_DATA    GetModeData;
  EFI_MTFTP6_CONFIGURE        Configure;
  EFI_MTFTP6_GET_INFO         GetInfo;
  EFI_MTFTP6_PARSE_OPTIONS    ParseOptions;
  EFI_MTFTP6_READ_FILE        ReadFile;
  EFI_MTFTP6_WRITE_FILE       WriteFile;
  EFI_MTFTP6_READ_DIRECTORY   ReadDirectory;
  EFI_MTFTP6_POLL             Poll;
};

//
//MTFTP6 token data
//
struct _EFI_MTFTP6_TOKEN{
  IN OUT EFI_STATUS               Status;
  IN EFI_EVENT                    Event;
  IN EFI_MTFTP6_OVERRIDE_DATA     *OverrideData      OPTIONAL;
  IN UINT8                        *Filename;
  IN UINT8                        *ModeStr           OPTIONAL;
  IN UINT32                       OptionCount;
  IN EFI_MTFTP6_OPTION            *OptionList        OPTIONAL;
  IN UINT64                       BufferSize;
  OUT VOID                        *Buffer            OPTIONAL;
  OUT VOID                        *Context           OPTIONAL;
  IN EFI_MTFTP6_CHECK_PACKET      CheckPacket        OPTIONAL;
  IN EFI_MTFTP6_TIMEOUT_CALLBACK  TimeoutCallback    OPTIONAL;
  IN EFI_MTFTP6_PACKET_NEEDED     PacketNeeded       OPTIONAL;
};

#endif

