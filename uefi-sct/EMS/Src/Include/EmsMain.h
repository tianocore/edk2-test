/** @file
 
  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
