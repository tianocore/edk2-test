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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
    EmsMain.h
    
Abstract:

    Data definition for EMS library

--*/

#ifndef __EMS_H__
#define __EMS_H__

#include "EmsTypes.h"

#ifdef _ASM_IA64_TYPES_H
#define BITS_PER_LONG 64
#else
#define BITS_PER_LONG 32
#endif

#define EFI_MAX_BIT                     (1L << (BITS_PER_LONG - 1))
#define EFIERR(a)                       ((a) | EFI_MAX_BIT)
#define EFIWARN(a)                      (a)

#define EFI_ERROR(a)                    (((long) (a)) < 0)

#define EFI_SUCCESS                     0L
#define EFI_LOAD_ERROR                  EFIERR (1L)
#define EFI_INVALID_PARAMETER           EFIERR (2L)
#define EFI_UNSUPPORTED                 EFIERR (3L)
#define EFI_BAD_BUFFER_SIZE             EFIERR (4L)
#define EFI_BUFFER_TOO_SMALL            EFIERR (5L)
#define EFI_NOT_READY                   EFIERR (6L)
#define EFI_DEVICE_ERROR                EFIERR (7L)
#define EFI_WRITE_PROTECTED             EFIERR (8L)
#define EFI_OUT_OF_RESOURCES            EFIERR (9L)
#define EFI_VOLUME_CORRUPTED            EFIERR (10L)
#define EFI_VOLUME_FULL                 EFIERR (11L)
#define EFI_NO_MEDIA                    EFIERR (12L)
#define EFI_MEDIA_CHANGED               EFIERR (13L)
#define EFI_NOT_FOUND                   EFIERR (14L)
#define EFI_ACCESS_DENIED               EFIERR (15L)
#define EFI_NO_RESPONSE                 EFIERR (16L)
#define EFI_NO_MAPPING                  EFIERR (17L)
#define EFI_TIMEOUT                     EFIERR (18L)
#define EFI_NOT_STARTED                 EFIERR (19L)
#define EFI_ALREADY_STARTED             EFIERR (20L)
#define EFI_ABORTED                     EFIERR (21L)
#define EFI_ICMP_ERROR                  EFIERR (22L)
#define EFI_TFTP_ERROR                  EFIERR (23L)
#define EFI_PROTOCOL_ERROR              EFIERR (24L)
#define EFI_INCOMPATIBLE_VERSION        EFIERR (25L)
#define EFI_SECURITY_VIOLATION          EFIERR (26L)
#define EFI_CRC_ERROR                   EFIERR (27L)
#define EFI_NOT_AVAILABLE_YET           EFIERR (28L)
#define EFI_UNLOAD_IMAGE                EFIERR (29L)
#define EFI_CREATE_ERROR                EFIERR (30L)
#define EFI_NETWORK_UNREACHABLE         EFIERR (100L)
#define EFI_HOST_UNREACHABLE            EFIERR (101L)
#define EFI_PROTOCOL_UNREACHABLE        EFIERR (102L)
#define EFI_PORT_UNREACHABLE            EFIERR (103L)
#define EFI_CONNECTION_REFUSED          EFIERR (106L)  

#define EFI_WARN_UNKNOWN_GLYPH          EFIWARN (1)
#define EFI_WARN_DELETE_FAILURE         EFIWARN (2)
#define EFI_WARN_WRITE_FAILURE          EFIWARN (3)
#define EFI_WARN_BUFFER_TOO_SMALL       EFIWARN (4)
#define EFI_WARN_RETURN_FROM_LONG_JUMP  EFIWARN (5)

#endif
