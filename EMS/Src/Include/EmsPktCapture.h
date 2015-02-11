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
  
    EmsPktCapture.h
    
Abstract:

    Data definition for packet capture function

--*/

#ifndef __EMS_CAPTURE_H__
#define __EMS_CAPTURE_H__

#include <EmsTypes.h>
#include <EmsTclInit.h>
#include <EmsNet.h>

#include "EmsVtcpNamedList.h"

extern
VOID_P
CaptureTclInit (
  IN Tcl_Interp *Interp
  )
/*++

Routine Description:

  Packet capture related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None.

--*/
;

//
// This struct is used for capturing one packet.
// Transfer between the parent and child processes
//
typedef struct {
  BOOLEAN         GotOne;   // Capture one packet?
  UINT8           *Packet;  // Packet content
  UINT32          Len;      // The length of the packet
  struct timeval  Time;     // When got the packet?
} CAP_INFO;

//
// This struct is used for capturing multiple packets
// Transfer between the parent and child processes
// Generally, we captures multiple packets only in performance test.
//
typedef struct {
  UINT32  Count;  // Only the number will be return from chile process
} MULTI_CAP_INFO;

#define MAX_FILTER_LEN  256

//
// This struct is used for defining the capture control block
//
typedef struct {
  UINT32          Received;     // Received
  UINT8           *ReceiveBuff; // Buffer the lasted packet received
  UINT32          ReceiveLen;   // the length of the received packet
  pcap_t          *Capturer;    //
  UINT8           CaptureFilter[MAX_FILTER_LEN];
  struct timeval  Time;
} CCB;

extern NL_LIST  CcbList;

VOID
EmsCaptureEndAll(
  VOID
  )
/*++

Routine Description:

  Close all the EMS capture

Arguments:

  None

Returns:

  None

--*/
;

#endif // _EMS_CAPTURE_H_
