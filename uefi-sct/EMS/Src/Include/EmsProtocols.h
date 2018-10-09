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
