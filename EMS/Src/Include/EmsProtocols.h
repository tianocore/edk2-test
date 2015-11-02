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
  
    EmsProtocols.h
    
Abstract:

    Incude header files for network protocol

--*/

#ifndef __EMS_PROTOCOLS_H__
#define __EMS_PROTOCOLS_H__

#include <tcl.h>
#include <EmsTypes.h>
#include <EmsNet.h>

/*
 * Information of each protocol field.
 * Used for packing a packet of specified protocol type.
 */
typedef struct _Field_T {
  INT8    *Name;      /* Field name */
  UINT8   Type;       /* Field type OCTET1, IPADDR, MACADDR, PAYLOAD ...*/
  VOID_P  *Value;     /* Actual value  */
  BOOLEAN Mandatory;  /* If true, this field MUST be set*/
  BOOLEAN *IsOk;      /* If this field has been set*/
} FIELD_T;

VOID_P
EmsFieldDump (
  INT8     *Buff,
  FIELD_T  *Fields
  )
/*++

Routine Description:

  Dump the field information into a specified buffer.

Arguments:

  Buff    - The buffer for the fields
  Fields  - The pointer to the fields

Returns:

  None

--*/
;

#define OCTET1  0x01
#define OCTET2  0x02
#define OCTET4  0x03
#define IPADDR  0x04
#define MACADDR 0x05
#define PAYLOAD 0x06
#define STRING  0x07
#define IPV6ADDR 0x08

typedef
libnet_t  *
CREATE_PROC_T (
  IN INT32  Argc,
  IN INT8   *Argv[]
  );

typedef
FIELD_T   *
UNPACK_PROC_T (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

typedef
VOID_P
TCL_INIT_PROC_T (
  IN Tcl_Interp *Interp
  );

typedef struct _PROTOCOL_ENTRY_T {
  INT8            *Name;          /* Protocol name */
  CREATE_PROC_T   *CreatePacket;  /* Callback routine for create packet */
  UNPACK_PROC_T   *UnpackPacket;  /* Callback routine for unpack packet */
  TCL_INIT_PROC_T *TclInit;       /* Create protocol specified tcl commands 
                                * in this routine */
} PROTOCOL_ENTRY_T;

extern PROTOCOL_ENTRY_T *Protocols[];

extern INT8             *EmsInterface;

extern
PROTOCOL_ENTRY_T        *
GetProtocolByName (
  INT8 *Name
  )
/*++

Routine Description:

  Get the protocol entry by specified name

Arguments:

  Name  - Protocl name

Returns:

  The protocol entry or NULL.

--*/
;
#endif
