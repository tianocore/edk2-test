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

  SimpleNetwork.h

Abstract:

--*/

#ifndef _SIMPLE_NETWORK_H_
#define _SIMPLE_NETWORK_H_

#define EFI_SIMPLE_NETWORK_PROTOCOL_GUID \
  { 0xA19832B9, 0xAC25, 0x11D3, 0x9A, 0x2D, 0x00, 0x90, 0x27, 0x3F, 0xC1, 0x4D }

#define EFI_SIMPLE_NETWORK_PROTOCOL_REVISION   0x00010000

EFI_FORWARD_DECLARATION (EFI_SIMPLE_NETWORK_PROTOCOL);

//*******************************************************
// MAX_MCAST_FILTER_CNT
//*******************************************************
#define MAX_MCAST_FILTER_CNT    16

//*******************************************************
// EFI_SIMPLE_NETWORK_MODE
//
// Note that the fields in this data structure are read-only and
// are updated by the code that produces the EFI_SIMPLE_NETWORK
// protocol functions. All these fields must be discovered
// during driver initialization.
//*******************************************************
typedef struct {
  UINT32                      State;
  UINT32                      HwAddressSize;
  UINT32                      MediaHeaderSize;
  UINT32                      MaxPacketSize;
  UINT32                      NvRamSize;
  UINT32                      NvRamAccessSize;
  UINT32                      ReceiveFilterMask;
  UINT32                      ReceiveFilterSetting;
  UINT32                      MaxMCastFilterCount;
  UINT32                      MCastFilterCount;
  EFI_MAC_ADDRESS             MCastFilter[MAX_MCAST_FILTER_CNT];
  EFI_MAC_ADDRESS             CurrentAddress;
  EFI_MAC_ADDRESS             BroadcastAddress;
  EFI_MAC_ADDRESS             PermanentAddress;
  UINT8                       IfType;
  BOOLEAN                     MacAddressChangeable;
  BOOLEAN                     MultipleTxSupported;
  BOOLEAN                     MediaPresentSupported;
  BOOLEAN                     MediaPresent;
} EFI_SIMPLE_NETWORK_MODE;

//*******************************************************
// EFI_SIMPLE_NETWORK_STATE
//*******************************************************
typedef enum {
  EfiSimpleNetworkStopped,
  EfiSimpleNetworkStarted,
  EfiSimpleNetworkInitialized,
  EfiSimpleNetworkMaxState
} EFI_SIMPLE_NETWORK_STATE;

//*******************************************************
// Bit Mask Values for ReceiveFilterSetting. bit mask values
//
// Note that all other bit values are reserved.
//*******************************************************
#define EFI_SIMPLE_NETWORK_RECEIVE_UNICAST               0x01
#define EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST             0x02
#define EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST             0x04
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS           0x08
#define EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST 0x10

//*******************************************************
// EFI_NETWORK_STATISTICS
//
// Any statistic value that is C1 is not available
// on the device and is to be ignored.
//*******************************************************
typedef struct {
  UINT64  RxTotalFrames;
  UINT64  RxGoodFrames;
  UINT64  RxUndersizeFrames;
  UINT64  RxOversizeFrames;
  UINT64  RxDroppedFrames;
  UINT64  RxUnicastFrames;
  UINT64  RxBroadcastFrames;
  UINT64  RxMulticastFrames;
  UINT64  RxCrcErrorFrames;
  UINT64  RxTotalBytes;
  UINT64  TxTotalFrames;
  UINT64  TxGoodFrames;
  UINT64  TxUndersizeFrames;
  UINT64  TxOversizeFrames;
  UINT64  TxDroppedFrames;
  UINT64  TxUnicastFrames;
  UINT64  TxBroadcastFrames;
  UINT64  TxMulticastFrames;
  UINT64  TxCrcErrorFrames;
  UINT64  TxTotalBytes;
  UINT64  Collisions;
  UINT64  UnsupportedProtocol;
} EFI_NETWORK_STATISTICS;

//*******************************************************
// Interrupt Bit Mask Settings for InterruptStatus.
// Note that all other bit values are reserved.
//*******************************************************
#define EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT        0x01
#define EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT       0x02
#define EFI_SIMPLE_NETWORK_COMMAND_INTERRUPT        0x04
#define EFI_SIMPLE_NETWORK_SOFTWARE_INTERRUPT       0x08

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_START) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_STOP) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_INITIALIZE) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN UINTN                        ExtraRxBufferSize  OPTIONAL,
  IN UINTN                        ExtraTxBufferSize  OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_RESET) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                      ExtendedVerification
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_SHUTDOWN) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE_FILTERS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN UINT32                       Enable,
  IN UINT32                       Disable,
  IN BOOLEAN                      ResetMCastFilter,
  IN UINTN                        MCastFilterCnt     OPTIONAL,
  IN EFI_MAC_ADDRESS              *MCastFilter       OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_STATION_ADDRESS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                      Reset,
  IN EFI_MAC_ADDRESS              *New      OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_STATISTICS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                      Reset,
  IN OUT UINTN                    *StatisticsSize   OPTIONAL,
  OUT EFI_NETWORK_STATISTICS      *StatisticsTable  OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                      IPv6,
  IN EFI_IP_ADDRESS               *IP,
  OUT EFI_MAC_ADDRESS             *MAC
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_NVDATA) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN BOOLEAN                      ReadWrite,
  IN UINTN                        Offset,
  IN UINTN                        BufferSize,
  IN OUT VOID                     *Buffer
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_GET_STATUS) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  OUT UINT32                      *InterruptStatus  OPTIONAL,
  OUT VOID                        **TxBuf           OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_TRANSMIT) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  IN UINTN                        HeaderSize,
  IN UINTN                        BufferSize,
  IN VOID                         *Buffer,
  IN EFI_MAC_ADDRESS              *SrcAddr     OPTIONAL,
  IN EFI_MAC_ADDRESS              *DestAddr    OPTIONAL,
  IN UINT16                       *Protocol    OPTIONAL
  );

typedef 
EFI_STATUS 
(EFIAPI *EFI_SIMPLE_NETWORK_RECEIVE) (
  IN EFI_SIMPLE_NETWORK_PROTOCOL  *This,
  OUT UINTN                       *HeaderSize  OPTIONAL,
  IN OUT UINTN                    *BufferSize,
  OUT VOID                        *Buffer,
  OUT EFI_MAC_ADDRESS             *SrcAddr     OPTIONAL,
  OUT EFI_MAC_ADDRESS             *DestAddr    OPTIONAL,
  OUT UINT16                      *Protocol    OPTIONAL
  );

struct _EFI_SIMPLE_NETWORK_PROTOCOL {
  UINT64                              Revision;
  EFI_SIMPLE_NETWORK_START            Start;
  EFI_SIMPLE_NETWORK_STOP             Stop;
  EFI_SIMPLE_NETWORK_INITIALIZE       Initialize;
  EFI_SIMPLE_NETWORK_RESET            Reset;
  EFI_SIMPLE_NETWORK_SHUTDOWN         Shutdown;
  EFI_SIMPLE_NETWORK_RECEIVE_FILTERS  ReceiveFilters;
  EFI_SIMPLE_NETWORK_STATION_ADDRESS  StationAddress;
  EFI_SIMPLE_NETWORK_STATISTICS       Statistics;
  EFI_SIMPLE_NETWORK_MCAST_IP_TO_MAC  MCastIpToMac;
  EFI_SIMPLE_NETWORK_NVDATA           NvData;
  EFI_SIMPLE_NETWORK_GET_STATUS       GetStatus;
  EFI_SIMPLE_NETWORK_TRANSMIT         Transmit;
  EFI_SIMPLE_NETWORK_RECEIVE          Receive;
  EFI_EVENT                           WaitForPacket;
  EFI_SIMPLE_NETWORK_MODE             *Mode;
};

extern EFI_GUID gEfiSimpleNetworkProtocolGuid;

#endif
