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
  
    EmsTypes.h
    
Abstract:

    Incude header files for type definitions

--*/

#ifndef __EMS_TYPES_H__
#define __EMS_TYPES_H__

/*
 * data types
 */

//
// bugbug: In windows only
//
#ifndef __int8_t_defined
#define __int8_t_defined
typedef char INT8;
typedef short int INT16;
typedef int INT32;
typedef long long int INT64;
#endif

typedef unsigned char UINT8;
typedef unsigned short int UINT16;
typedef unsigned int UINT32;
typedef unsigned long long int UINT64;

typedef UINT8 BOOLEAN;

//
// Modifiers to absract standard types to aid in debug of problems
//
#define CONST     const
#define STATIC    static
#define VOID_P    void
#define VOLATILE  volatile

//
// EFI Constants. They may exist in other build structures, so #ifndef them.
//
#ifndef TRUE
#define TRUE  ((BOOLEAN) 1 == 1)
#endif

#ifndef FALSE
#define FALSE ((BOOLEAN) 0 == 1)
#endif

#ifndef IN
//
// Some other envirnmems use this construct, so #ifndef to prevent
// mulitple definition.
//
#define IN
#define OUT
#define OPTIONAL
#endif

typedef struct libnet_in6_addr EMS_IPV6_ADDR;
typedef INT8  EMS_STATUS;
typedef unsigned long EFI_STATUS;

typedef struct {
  UINT16  Year;
  UINT8   Month;
  UINT8   Day;
  UINT8   Hour;
  UINT8   Minute;
  UINT8   Second;
  UINT8   Pad1;
  UINT32  NanoSecond;
  INT16   TimeZone;
  UINT8   DayLight;
  UINT8   Pad2;
} EFI_TIME;

typedef struct {
  UINT32  Data1;
  UINT16  Data2;
  UINT16  Data3;
  UINT8   Data4;
  UINT8   Data5;
  UINT8   Data6;
  UINT8   Data7;
  UINT8   Data8;
  UINT8   Data9;
  UINT8   Data10;
  UINT8   Data11;
} EFI_GUID;

typedef struct _PAYLOAD_T {
  UINT8   *Payload;
  UINT32  Len;
} PAYLOAD_T;

//
// Error status value
//
#define NOERROR           0
#define ERROR_WRONGFORMAT 1
#define ERROR_WRONGARG    2
#define ERROR_LACKOFARG   3
#define ERROR_DUPARG      4
#define ERROR_NOVALUE     5
#define ERROR_INTERNAL    6

#define IsError(e)        (e != 0)

#define MAX_ERRBUFF_LEN   2048

#endif
