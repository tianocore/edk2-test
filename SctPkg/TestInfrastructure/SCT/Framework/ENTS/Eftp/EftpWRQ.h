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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
 
  EftpWRQ.h
 
Abstract:

  WRQ procedure
 
--*/

#ifndef _EFI_EFTP_WRQ_H_
#define _EFI_EFTP_WRQ_H_

//
// Init a silent shutdown.
// A silent shutdown will discard any incoming packet, and send nothing
//
#define WRQ_SILENT_SHUTDOWN(Private) \
  do { \
    (Private)->State = EFTP_TIME_WAIT; \
    EftpSetTimer ((Private), 0, EFTP_TIMEWAIT_TIME); \
  } while (0)

  //
  // Init a loud shutdown
  // A loud shutdown will discard any incoming packet, and send out last control packet
  //
#define WRQ_LOUD_SHUTDOWN(Private) \
  do { \
    ASSERT ((Private)->State != EFTP_TIME_WAIT); \
    (Private)->State = EFTP_WRQ_CLOSEING; \
    EftpSetTimer ((Private), EFTP_CLOSEING_TIME, 0); \
  } while (0)


//
// Vars specific to WRQ
//
typedef struct _EFTP_WRQ_STATE {
  EFTP_PACKET_BUFFER  *LastData;  // saved for retransmission
} EFTP_WRQ_STATE;

EFTP_WRQ_STATE  *
EftpInitWrqState (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Init a Eftp instance for WRQ, or uploading

Arguments:

  Private - Eftp instance private data

Returns:

  NULL: Failed to allocate buffer for WRQ state
  Point to the newly allocated WRQ data structure: On success

--*/
;

VOID
EftpWrqRxCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Callback function by UDP when it receives packets for the instance.
  It will dispatch the packet to different routines for process.

Arguments:

  Event   : Event signalled by UDP
  Context : Event's context, it is a point to EFTP_COMPLETION_TOKEN

Returns:

  None 

--*/
;

EFI_STATUS
EftpBuildWrq (
  IN EFTP_IO_PRIVATE*Private
  )
/*++

Routine Description:

  Build a WRQ packet from the user info, and save it at Private->Request

Arguments:

  Private - Eftp instance private data

Returns:

  EFI_OUT_OF_RESOURCES: Failed to allocate buffer for WRQ packet
  EFI_SUCCESS : WRQ packet allocated and initialized

--*/
;

VOID
EftpWrqTimer (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
/*++

Routine Description:

  Timer function when timeout happened during uploading.
  It will either retransmit the last packet, transit the state,
  or clean up the instance
  
Arguments:

  Event   : Timer event got signaled
  Context : The event's context. It is a point to EFTP_IO_PRIVATE

Returns:

  Event callback returns nothing

--*/
;

VOID
EftpWrqCleanUp (
  IN EFTP_IO_PRIVATE*private
  )
/*++

Routine Description:

  Gracefully shutdown the Eftp instance: release various resources
  and signal the user event

Arguments:

  Private : Eftp instance private data

Returns:

  None

--*/
;

#endif
