/** @file
 
  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:
  
    EmsNet.h
    
Abstract:

    Incude header files for libnet library

--*/

#ifndef __EMS_NET_H__
#define __EMS_NET_H__

#include <libnet.h>

#ifndef HAVE_SNPRINTF
#define HAVE_SNPRINTF
#endif

#ifndef HAVE_VSNPRINTF
#define HAVE_VSNPRINTF
#endif

#include <Pcap-int.h>

#if defined(__WIN32__) || defined(WIN32)
#include <iphlpapi.h>
#endif

#endif
