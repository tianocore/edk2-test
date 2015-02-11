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
