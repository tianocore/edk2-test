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
  
    EmsProtocols.c
    
Abstract:

    Implementation for protocol related common functions

--*/

#include <EmsUtilityString.h>

#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoIgmp.h"
#include "EmsProtoArp.h"
#include "EmsProtoUdp.h"
#include "EmsProtoIcmp.h"
#include "EmsProtoDhcp.h"
#include "EmsProtoTcp.h"
#include "EmsProtoIPv6.h"

PROTOCOL_ENTRY_T  *Protocols[] = {
  &EthProtocol,
  &IpProtocol,
  &IgmpProtocol,
  &ArpProtocol,
  &UdpProtocol,
  &IcmpProtocol,
  &DhcpProtocol,
  &TcpProtocol,
  &IPv6Protocol,
  NULL
};

PROTOCOL_ENTRY_T *
GetProtocolByName (
  IN INT8 *Name
  )
/*++

Routine Description:

  Get the protocol entry by specified name

Arguments:

  Name  - Protocl name

Returns:

  The protocol entry or NULL.

--*/
{
  UINT32  Index;

  for (Index = 0; Protocols[Index]; Index++) {
    if (0 == strcmp_i (Protocols[Index]->Name, Name)) {
      return Protocols[Index];
    }
  }

  return NULL;
}

VOID_P
EmsFieldDump (
  IN OUT  INT8     *Buff,
  IN      FIELD_T  *Fields
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
{
  UINT32  Index;
  INT8    Log[100];
  Buff[0] = '\0';
  for (Index = 0; Fields[Index].Name; Index++) {
    strcat (Buff, Fields[Index].Name);
    switch (Fields[Index].Type) {
    case OCTET1:
      sprintf (Log, "=0x%02x ", *(UINT8 *) Fields[Index].Value);
      break;

    case OCTET2:
      sprintf (Log, "=0x%04x ", *(UINT16 *) Fields[Index].Value);
      break;

    case OCTET4:
      sprintf (Log, "=0x%08x ", *(UINT32 *) Fields[Index].Value);
      break;

    case IPADDR:
      Log[0] = '=';
      Ipv4ToAsciiString (&Log[1], *(UINT32 *) Fields[Index].Value);
      break;

	case IPV6ADDR:
      Log[0] = '=';
      Ipv6ToAsciiString (&Log[1], (EMS_IPV6_ADDR*)Fields[Index].Value);
      break;  

    case MACADDR:
      Log[0] = '=';
      MacToAsciiString (&Log[1], ((UINT8 *) Fields[Index].Value));
      break;

    case STRING:
      Log[0] = '=';
      sprintf (Log, "=%s ", *((UINT8 **) Fields[Index].Value));
      break;

    default:
      sprintf (Log, " ");
      break;
    }

    strcat (Buff, Log);
  }

  return ;
}
