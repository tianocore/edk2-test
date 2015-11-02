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

  ExtScsiPassThruProtocol.h

Abstract:

--*/


#ifndef _EXT_SCSI_PASS_THRU_FOR_TEST_H_
#define _EXT_SCSI_PASS_THRU_FOR_TEST_H_

#define EFI_EXT_SCSI_PASS_THRU_PROTOCOL_GUID \
  { \
    0x143b7632, 0xb81b, 0x4cb7, {0xab, 0xd3, 0xb6, 0x25, 0xa5, 0xb9, 0xbf, 0xfe } \
  }

typedef struct _EFI_EXT_SCSI_PASS_THRU_PROTOCOL EFI_EXT_SCSI_PASS_THRU_PROTOCOL;

#define TARGET_MAX_BYTES                             0x10

#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_PHYSICAL   0x0001
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_LOGICAL    0x0002
#define EFI_EXT_SCSI_PASS_THRU_ATTRIBUTES_NONBLOCKIO 0x0004

//
// DataDirection
//
#define EFI_EXT_SCSI_DATA_DIRECTION_READ             0
#define EFI_EXT_SCSI_DATA_DIRECTION_WRITE            1
#define EFI_EXT_SCSI_DATA_DIRECTION_BIDIRECTIONAL    2
//
// HostAdapterStatus
//
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OK                    0x00
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT_COMMAND       0x09
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_TIMEOUT               0x0b
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_MESSAGE_REJECT        0x0d
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_RESET             0x0e
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PARITY_ERROR          0x0f
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_REQUEST_SENSE_FAILED  0x10
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_SELECTION_TIMEOUT     0x11
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_DATA_OVERRUN_UNDERRUN 0x12
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_BUS_FREE              0x13
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_PHASE_ERROR           0x14
#define EFI_EXT_SCSI_STATUS_HOST_ADAPTER_OTHER                 0x7f
//
// TargetStatus
//
#define EFI_EXT_SCSI_STATUS_TARGET_GOOD                        0x00
#define EFI_EXT_SCSI_STATUS_TARGET_CHECK_CONDITION             0x02
#define EFI_EXT_SCSI_STATUS_TARGET_CONDITION_MET               0x04
#define EFI_EXT_SCSI_STATUS_TARGET_BUSY                        0x08
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE                0x10
#define EFI_EXT_SCSI_STATUS_TARGET_INTERMEDIATE_CONDITION_MET  0x14
#define EFI_EXT_SCSI_STATUS_TARGET_RESERVATION_CONFLICT        0x18
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_SET_FULL               0x28
#define EFI_EXT_SCSI_STATUS_TARGET_ACA_ACTIVE                  0x30
#define EFI_EXT_SCSI_STATUS_TARGET_TASK_ABORTED                0x40


#define EFI_SCSI_STALL_1_SECOND       10000000
#define EfiScsiStallSeconds(a)        (a) * EFI_SCSI_STALL_1_SECOND

typedef struct {
  UINT32 AdapterId;
  UINT32 Attributes;
  UINT32 IoAlign;
} EFI_EXT_SCSI_PASS_THRU_MODE;

typedef struct {
  UINT64 Timeout;
  VOID   *InDataBuffer;
  VOID   *OutDataBuffer;
  VOID   *SenseData;
  VOID   *Cdb;
  UINT32 InTransferLength;
  UINT32 OutTransferLength;
  UINT8  CdbLength;
  UINT8  DataDirection;
  UINT8  HostAdapterStatus;
  UINT8  TargetStatus;
  UINT8  SenseDataLength;
} EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET;

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_PASSTHRU) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL                *This,
  IN UINT8                                          *Target,
  IN UINT64                                         Lun,
  IN OUT EFI_EXT_SCSI_PASS_THRU_SCSI_REQUEST_PACKET *Packet,
  IN EFI_EVENT                                      Event     OPTIONAL
  )
/*++

  Routine Description:
    Sends a SCSI Request Packet to a SCSI device that is attached to the SCSI channel. This function   
    supports both blocking I/O and nonblocking I/O. The blocking I/O functionality is required, and the
    nonblocking I/O functionality is optional.                                                             
  
  Arguments:
    This   - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.
    Target - The Target is an array of size TARGET_MAX_BYTES and it represents
             the id of the SCSI device to send the SCSI Request Packet. Each
             transport driver may chose to utilize a subset of this size to suit the needs
             of transport target representation. For example, a Fibre Channel driver
             may use only 8 bytes (WWN) to represent an FC target.
    Lun    - The LUN of the SCSI device to send the SCSI Request Packet.
    Packet - A pointer to the SCSI Request Packet to send to the SCSI device
             specified by Target and Lun.
    Event  - If nonblocking I/O is not supported then Event is ignored, and blocking
             I/O is performed. If Event is NULL, then blocking I/O is performed. If
             Event is not NULL and non blocking I/O is supported, then
             nonblocking I/O is performed, and Event will be signaled when the
             SCSI Request Packet completes.

  Returns:
    EFI_SUCCESS          - The SCSI Request Packet was sent by the host. For bi-directional
                           commands, InTransferLength bytes were transferred from
                           InDataBuffer. For write and bi-directional commands,
                           OutTransferLength bytes were transferred by
                           OutDataBuffer.
    EFI_BAD_BUFFER_SIZE  - The SCSI Request Packet was not executed. The number of bytes that
                           could be transferred is returned in InTransferLength. For write
                           and bi-directional commands, OutTransferLength bytes were
                           transferred by OutDataBuffer.
    EFI_NOT_READY        - The SCSI Request Packet could not be sent because there are too many
                           SCSI Request Packets already queued. The caller may retry again later.
    EFI_DEVICE_ERROR     - A device error occurred while attempting to send the SCSI Request
                           Packet.
    EFI_INVALID_PARAMETER- Target, Lun, or the contents of ScsiRequestPacket are invalid.
    EFI_UNSUPPORTED      - The command described by the SCSI Request Packet is not supported
                           by the host adapter. This includes the case of Bi-directional SCSI
                           commands not supported by the implementation. The SCSI Request
                           Packet was not sent, so no additional status information is available.
    EFI_TIMEOUT          - A timeout occurred while waiting for the SCSI Request Packet to execute.

--*/
;      

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL                *This,
  IN OUT UINT8                                      **Target,
  IN OUT UINT64                                     *Lun
  )
/*++
  Routine Description:
    Used to retrieve the list of legal Target IDs and LUNs for SCSI devices on a SCSI channel. These       
    can either be the list SCSI devices that are actually present on the SCSI channel, or the list of legal
    Target Ids and LUNs for the SCSI channel. Regardless, the caller of this function must probe the       
    Target ID and LUN returned to see if a SCSI device is actually present at that location on the SCSI    
    channel.                                                                                               
  
  Arguments:
    This    - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance
    Target  - On input, a pointer to the Target ID (an array of size
              TARGET_MAX_BYTES) of a SCSI device present on the SCSI channel.
              On output, a pointer to the Target ID (an array of
              TARGET_MAX_BYTES) of the next SCSI device present on a SCSI
              channel. An input value of 0xF(all bytes in the array are 0xF) in the
              Target array retrieves the Target ID of the first SCSI device present on
              a SCSI channel.
    Lun     - On input, a pointer to the LUN of a SCSI device present on the SCSI
              channel. On output, a pointer to the LUN of the next SCSI device present
              on a SCSI channel.
  
  Returns:
    EFI_SUCCESS           - The Target ID and LUN of the next SCSI device on the SCSI
                            channel was returned in Target and Lun.
    EFI_INVALID_PARAMETER - Target array is not all 0xF, and Target and Lun were
                            not returned on a previous call to GetNextTargetLun().
    EFI_NOT_FOUND         - There are no more SCSI devices on this SCSI channel.

--*/
;   

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
  IN UINT8                                         *Target,
  IN UINT64                                        Lun,
  IN OUT EFI_DEVICE_PATH_PROTOCOL                  **DevicePath
  )
/*++

  Routine Description:
    Used to allocate and build a device path node for a SCSI device on a SCSI channel.

  Arguments:
    This       - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.
    Target     - The Target is an array of size TARGET_MAX_BYTES and it specifies the
                 Target ID of the SCSI device for which a device path node is to be
                 allocated and built. Transport drivers may chose to utilize a subset of
                 this size to suit the representation of targets. For example, a Fibre
                 Channel driver may use only 8 bytes (WWN) in the array to represent a
                 FC target.
    Lun        - The LUN of the SCSI device for which a device path node is to be
                 allocated and built.
                 
    DevicePath - A pointer to a single device path node that describes the SCSI device
                 specified by Target and Lun. This function is responsible for
                 allocating the buffer DevicePath with the boot service
                 SctAllocatePool (). It is the caller's responsibility to free
                 DevicePath when the caller is finished with DevicePath.

  Returns:
    EFI_SUCCESS           - The device path node that describes the SCSI device specified by
                            Target and Lun was allocated and returned in
                            DevicePath.
    EFI_INVALID_PARAMETER - DevicePath is NULL.
    EFI_NOT_FOUND         - The SCSI devices specified by Target and Lun does not exist
                            on the SCSI channel.
    EFI_OUT_OF_RESOURCES  - There are not enough resources to allocate DevicePath.

--*/
;     

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
  IN EFI_DEVICE_PATH_PROTOCOL                      *DevicePath,
  OUT UINT8                                        **Target,
  OUT UINT64                                       *Lun
  )
/*++

  Routine Description:
    Used to translate a device path node to a Target ID and LUN.

  Arguments:
    This       - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.
    DevicePath - A pointer to a single device path node that describes the SCSI device
                 on the SCSI channel.
    Target     - A pointer to the Target Array which represents the ID of a SCSI device
                 on the SCSI channel.
    Lun        - A pointer to the LUN of a SCSI device on the SCSI channel.

  Returns:
    EFI_SUCCESS           - DevicePath was successfully translated to a Target ID and
                            LUN, and they were returned in Target and Lun.
    EFI_INVALID_PARAMETER - DevicePath or Target or Lun is NULL.
    EFI_NOT_FOUND         - A valid translation from DevicePath to a Target ID and LUN
                            does not exist.
    EFI_UNSUPPORTED       - This driver does not support the device path node type in
                                    DevicePath.

--*/
;       

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This
  )
/*++

  Routine Description:
    Resets a SCSI channel. This operation resets all the SCSI devices connected to the SCSI channel.

  Arguments:
    This          - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.

  Returns:
    EFI_SUCCESS      - The SCSI channel was reset.
    EFI_DEVICE_ERROR - A device error occurred while attempting to reset the SCSI channel.
    EFI_TIMEOUT      - A timeout occurred while attempting to reset the SCSI channel.
    EFI_UNSUPPORTED  - The SCSI channel does not support a channel reset operation.

--*/
;    
  
typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
  IN UINT8                                         *Target,
  IN UINT64                                        Lun
  )
/*++

  Routine Description:
    Resets a SCSI logical unit that is connected to a SCSI channel.

  Arguments:
    This   A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.
    Target The Target is an array of size TARGET_MAX_BYTE and it represents the
           target port ID of the SCSI device containing the SCSI logical unit to
           reset. Transport drivers may chose to utilize a subset of this array to suit
           the representation of their targets.
    Lun    The LUN of the SCSI device to reset.
  
  Returns:
    EFI_SUCCESS           - The SCSI device specified by Target and Lun was reset.
    EFI_INVALID_PARAMETER - Target or Lun is NULL.
    EFI_TIMEOUT           - A timeout occurred while attempting to reset the SCSI device
                            specified by Target and Lun.
    EFI_UNSUPPORTED       - The SCSI channel does not support a target reset operation.
    EFI_DEVICE_ERROR      - A device error occurred while attempting to reset the SCSI device
                            specified by Target and Lun.
   
--*/
;         

typedef
EFI_STATUS
(EFIAPI *EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET) (
  IN EFI_EXT_SCSI_PASS_THRU_PROTOCOL               *This,
  IN OUT UINT8                                     **Target
  )
/*++

  Routine Description:
    Used to retrieve the list of legal Target IDs for SCSI devices on a SCSI channel. These can either     
    be the list SCSI devices that are actually present on the SCSI channel, or the list of legal Target IDs
    for the SCSI channel. Regardless, the caller of this function must probe the Target ID returned to     
    see if a SCSI device is actually present at that location on the SCSI channel.                         

  Arguments:
    This   - A pointer to the EFI_EXT_SCSI_PASS_THRU_PROTOCOL instance.
    Target - (TARGET_MAX_BYTES) of a SCSI device present on the SCSI channel.
             On output, a pointer to the Target ID (an array of
             TARGET_MAX_BYTES) of the next SCSI device present on a SCSI
             channel. An input value of 0xF(all bytes in the array are 0xF) in the
             Target array retrieves the Target ID of the first SCSI device present on a
             SCSI channel.

  Returns:
    EFI_SUCCESS           - The Target ID of the next SCSI device on the SCSI
                            channel was returned in Target.
    EFI_INVALID_PARAMETER - Target or Lun is NULL.
    EFI_TIMEOUT           - Target array is not all 0xF, and Target were not
                            returned on a previous call to GetNextTarget().
    EFI_NOT_FOUND         - There are no more SCSI devices on this SCSI channel.

--*/
;          
  
struct _EFI_EXT_SCSI_PASS_THRU_PROTOCOL {
  EFI_EXT_SCSI_PASS_THRU_MODE                *Mode;
  EFI_EXT_SCSI_PASS_THRU_PASSTHRU            PassThru;
  EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET_LUN GetNextTargetLun;
  EFI_EXT_SCSI_PASS_THRU_BUILD_DEVICE_PATH   BuildDevicePath;
  EFI_EXT_SCSI_PASS_THRU_GET_TARGET_LUN      GetTargetLun;
  EFI_EXT_SCSI_PASS_THRU_RESET_CHANNEL       ResetChannel;
  EFI_EXT_SCSI_PASS_THRU_RESET_TARGET_LUN    ResetTargetLun;
  EFI_EXT_SCSI_PASS_THRU_GET_NEXT_TARGET     GetNextTarget;
};

extern EFI_GUID gBlackBoxEfiExtScsiPassThruProtocolGuid;

#endif /* _EXT_SCSI_PASS_THRU_FOR_TEST_H_ */

