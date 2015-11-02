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

  ScsiIoProtocol.h

Abstract:

--*/


#ifndef _SCSI_IO_FOR_TEST_H_
#define _SCSI_IO_FOR_TEST_H_

#define EFI_SCSI_IO_PROTOCOL_GUID \
  { 0x932f47E6, 0x2362, 0x4002, 0x80, 0x3e, 0x3c, 0xd5, 0x4b, 0x13, 0x8f, 0x85 }

//
// Forward reference for pure ANSI compatability
//
typedef struct _EFI_SCSI_IO_PROTOCOL EFI_SCSI_IO_PROTOCOL;;

#define TARGET_MAX_BYTES                                       0x10

//
// SCSI Data Direction definition
//
#define EFI_SCSI_IO_DATA_DIRECTION_READ                        0
#define EFI_SCSI_IO_DATA_DIRECTION_WRITE                       1
#define EFI_SCSI_IO_DATA_DIRECTION_BIDIRECTIONAL               2

//
// SCSI Host Adapter Status definition
//
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_OK                     0x00
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND        0x09    // timeout when processing the command
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_TIMEOUT                0x0b    // timeout when waiting for the command processing
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_MESSAGE_REJECT         0x0d    // a message reject was received when processing command
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_BUS_RESET              0x0e    // a bus reset was detected
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_PARITY_ERROR           0x0f
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_REQUEST_SENSE_FAILED   0x10    // the adapter failed in issuing request sense command
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_SELECTION_TIMEOUT      0x11    // selection timeout
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_DATA_OVERRUN_UNDERRUN  0x12    // data overrun or data underrun
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_BUS_FREE               0x13    // Unexepected bus free
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_PHASE_ERROR            0x14    // Target bus phase sequence failure
#define EFI_SCSI_IO_STATUS_HOST_ADAPTER_OTHER                  0x7f


//
// SCSI Target Status definition
//
#define EFI_SCSI_IO_STATUS_TARGET_GOOD                         0x00
#define EFI_SCSI_IO_STATUS_TARGET_CHECK_CONDITION              0x02    // check condition
#define EFI_SCSI_IO_STATUS_TARGET_CONDITION_MET                0x04    // condition met
#define EFI_SCSI_IO_STATUS_TARGET_BUSY                         0x08    // busy
#define EFI_SCSI_IO_STATUS_TARGET_INTERMEDIATE                 0x10    // intermediate
#define EFI_SCSI_IO_STATUS_TARGET_INTERMEDIATE_CONDITION_MET   0x14    // intermediate-condition met
#define EFI_SCSI_IO_STATUS_TARGET_RESERVATION_CONFLICT         0x18    // reservation conflict
#define EFI_SCSI_IO_STATUS_TARGET_COMMOND_TERMINATED           0x22    // command terminated
#define EFI_SCSI_IO_STATUS_TARGET_QUEUE_FULL                   0x28    // queue full

#define EFI_SCSI_STALL_1_SECOND       10000000
#define EfiScsiStallSeconds(a)        (a) * EFI_SCSI_STALL_1_SECOND

typedef struct {
  UINT64                              Timeout;
  VOID                                *InDataBuffer;
  VOID                                *OutDataBuffer;
  VOID                                *SenseData;
  VOID                                *Cdb;
  UINT32                              InTransferLength;
  UINT32                              OutTransferLength;
  UINT8                               CdbLength;
  UINT8                               DataDirection;
  UINT8                               HostAdapterStatus;
  UINT8                               TargetStatus;
  UINT8                               SenseDataLength;
} EFI_SCSI_IO_SCSI_REQUEST_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_SCSI_IO_PROTOCOL_GET_DEVICE_TYPE) (
  IN  EFI_SCSI_IO_PROTOCOL            *This,
  OUT UINT8                           *DeviceType
  )
/*++

  Routine Description:
    Retrieves the device type information of the SCSI Controller.

  Arguments:
    This       - Protocol instance pointer.
    DeviceType - A pointer to the device type information
                 retrieved from the SCSI Controller.

  Returns:
    EFI_SUCCESS           - Retrieves the device type information successfully.
    EFI_INVALID_PARAMETER - The DeviceType is NULL.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION) (
  IN EFI_SCSI_IO_PROTOCOL           *This,
  IN OUT UINT8                      **Target,
  OUT UINT64                        *Lun
  )
/*++

  Routine Description:
    Retrieves the device location in the SCSI channel.

  Arguments:
    This    - Protocol instance pointer.
    Target  - A pointer to the Target Array which represents ID of a SCSI device
              on the SCSI channel.
    Lun     - A pointer to the LUN of the SCSI device on
              the SCSI channel.

  Returns:
    EFI_SUCCESS           - Retrieves the device location successfully.
    EFI_INVALID_PARAMETER - The Target or Lun is NULL.
   
--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SCSI_IO_PROTOCOL_RESET_BUS) (
  IN EFI_SCSI_IO_PROTOCOL     *This
  )
/*++

  Routine Description:
    Resets the SCSI Bus that the SCSI Controller is attached to.

  Arguments:
    This  - This Protocol instance pointer.

  Returns:
    EFI_SUCCESS      - The SCSI bus is reset successfully.
    EFI_DEVICE_ERROR - Errors encountered when resetting the SCSI bus.
    EFI_UNSUPPORTED  - The bus reset operation is not supported by the
                       SCSI Host Controller.
    EFI_TIMEOUT      - A timeout occurred while attempting to reset
                       the SCSI bus.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SCSI_IO_PROTOCOL_RESET_DEVICE) (
  IN EFI_SCSI_IO_PROTOCOL     *This
  )
/*++

  Routine Description:
    Resets the SCSI Controller that the device handle specifies.

  Arguments:
    This - Protocol instance pointer.

  Returns:
    EFI_SUCCESS       - Reset the SCSI controller successfully.
    EFI_DEVICE_ERROR  - Errors are encountered when resetting the
                        SCSI Controller.
    EFI_UNSUPPORTED   - The SCSI bus does not support a device
                        reset operation.
    EFI_TIMEOUT       - A timeout occurred while attempting to
                        reset the SCSI Controller.

--*/
;

typedef
EFI_STATUS
(EFIAPI *EFI_SCSI_IO_PROTOCOL_EXEC_SCSI_COMMAND) (
  IN EFI_SCSI_IO_PROTOCOL                   *This,
  IN OUT  EFI_SCSI_IO_SCSI_REQUEST_PACKET   *Packet,
  IN EFI_EVENT                              Event  OPTIONAL
  )
/*++

  Routine Description:
    Sends a SCSI Request Packet to the SCSI Controller for execution.

  Arguments:
    This    - Protocol instance pointer.
    Packet  - The SCSI request packet to send to the SCSI
              Controller specified by the device handle.
    Event   - If the SCSI bus where the SCSI device is attached
              does not support non-blocking I/O, then Event is
              ignored, and blocking I/O is performed.
              If Event is NULL, then blocking I/O is performed.
              If Event is not NULL and non-blocking I/O is
              supported, then non-blocking I/O is performed,
              and Event will be signaled when the SCSI Request
              Packet completes.

  Returns:
    EFI_SUCCESS                - The SCSI Request Packet was sent by the host
                                 successfully, and TransferLength bytes were
                                 transferred to/from DataBuffer.See
                                 HostAdapterStatus, TargetStatus,
                                 SenseDataLength, and SenseData in that order
                                 for additional status information.
    EFI_WARN_BUFFER_TOO_SMALL  - The SCSI Request Packet was executed,
                                 but the entire DataBuffer could not be transferred.
                                 The actual number of bytes transferred is returned
                                 in TransferLength. See HostAdapterStatus,
                                 TargetStatus, SenseDataLength, and SenseData in
                                 that order for additional status information.
    EFI_NOT_READY              - The SCSI Request Packet could not be sent because
                                 there are too many SCSI Command Packets already
                                 queued.The caller may retry again later.
    EFI_DEVICE_ERROR           - A device error occurred while attempting to send
                                 the SCSI Request Packet. See HostAdapterStatus,
                                 TargetStatus, SenseDataLength, and SenseData in
                                 that order for additional status information.
    EFI_INVALID_PARAMETER      - The contents of CommandPacket are invalid.
                                 The SCSI Request Packet was not sent, so no
                                 additional status information is available.
    EFI_UNSUPPORTED            - The command described by the SCSI Request Packet
                                 is not supported by the SCSI initiator(i.e., SCSI
                                 Host Controller). The SCSI Request Packet was not
                                 sent, so no additional status information is
                                 available.
    EFI_TIMEOUT                - A timeout occurred while waiting for the SCSI
                                 Request Packet to execute. See HostAdapterStatus,
                                 TargetStatus, SenseDataLength, and SenseData in
                                 that order for additional status information.
--*/
;

struct _EFI_SCSI_IO_PROTOCOL {
  EFI_SCSI_IO_PROTOCOL_GET_DEVICE_TYPE      GetDeviceType;
  EFI_SCSI_IO_PROTOCOL_GET_DEVICE_LOCATION  GetDeviceLocation;
  EFI_SCSI_IO_PROTOCOL_RESET_BUS            ResetBus;
  EFI_SCSI_IO_PROTOCOL_RESET_DEVICE         ResetDevice;
  EFI_SCSI_IO_PROTOCOL_EXEC_SCSI_COMMAND    ExecuteScsiCommand;    
  UINT32                                    IoAlign;
};

extern EFI_GUID gBlackBoxEfiScsiIoProtocolGuid;

#endif /* _SCSI_IO_FOR_TEST_H_ */

