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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PXEBaseCodeENTSTestCase.h

Abstract:

--*/

#ifndef _PXEBASECODE_ENTS_TESTCASE_H_
#define _PXEBASECODE_ENTS_TESTCASE_H_

#include <Base.h>
#include "SctLib.h"
#include "Eas.h"

EFI_STATUS
PXEBaseCodeStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStart Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeDhcp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDhcp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeDiscover_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDiscover Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeMtftp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMtftp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeUdpWrite_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWrite Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeUdpRead_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpRead Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeSetIpFilter_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetIpFilter Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeArp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeArp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeSetParameters_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetParameters Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeSetStationIp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetStationIp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeSetPackets_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetPackets Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeMode_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMode Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeUdpWritePattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWritePattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
PXEBaseCodeUdpReadPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpReadPattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

extern CHAR16         *gPXEBaseCodeEntsRuntimeInfo;
extern UINTN          gPXEBaseCodeEntsRuntimeInfoSize;

extern ENTS_ARG_FIELD gPXEBaseCodeStartArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeStopArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeDhcpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeDiscoverArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeMtftpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpWriteArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpReadArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetIpFilterArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeArpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetParametersArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetStationIpArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeSetPacketsArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeModeArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpWritePattern1ArgField[];
extern ENTS_ARG_FIELD gPXEBaseCodeUdpReadPattern1ArgField[];

#endif // _PXEBASECODE_ENTS_TESTCASE_H_
