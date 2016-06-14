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
  
    EmsProtoDhcp.c
    
Abstract:

    Implementation for functions for protocol DHCP

--*/

#include <stdlib.h>
#include "EmsUtilityMain.h"
#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsProtoUdp.h"
#include "EmsProtoDhcp.h"
#include "EmsUtilityString.h"

STATIC
libnet_t          *
DhcpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T           *
DhcpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

PROTOCOL_ENTRY_T  DhcpProtocol = {
  "DHCP",                         /* name */
  DhcpCreatePacket,               /* Create packet routine */
  DhcpUnpackPacket,               /* Unpacket routine */
  NULL                            /* IP TCL initialzation routine*/
};

STATIC BOOLEAN    OpOk;
STATIC BOOLEAN    HTypeOk;
STATIC BOOLEAN    HLenOk;
STATIC BOOLEAN    HopsOk;
STATIC BOOLEAN    XidOk;
STATIC BOOLEAN    SecsOk;
STATIC BOOLEAN    FlagsOk;
STATIC BOOLEAN    CIaddrOk;
STATIC BOOLEAN    YIaddrOk;
STATIC BOOLEAN    SIaddrOk;
STATIC BOOLEAN    GIaddrOk;
STATIC BOOLEAN    ChAddrOk;
STATIC BOOLEAN    SnameOk;
STATIC BOOLEAN    FileOk;
STATIC BOOLEAN    MagicOk;
STATIC BOOLEAN    OptionsOk;
STATIC BOOLEAN    SportOk;
STATIC BOOLEAN    DportOk;

STATIC UINT8      DhcpOp;         // opcode
STATIC UINT8      DhcpHType;      // hardware address type
STATIC UINT8      DhcpHLen;       // hardware address length
STATIC UINT8      DhcpHops;       // used by proxy servers
STATIC UINT32     DhcpXid;        // transaction ID
STATIC UINT16     DhcpSecs;       // number of seconds since trying to bootstrap
STATIC UINT16     DhcpFlags;      // flags for DHCP, unused for BOOTP
STATIC UINT32     DhcpCIaddr;     // client's IP
STATIC UINT32     DhcpYIaddr;     // your IP
STATIC UINT32     DhcpSIaddr;     // server's IP
STATIC UINT32     DhcpGIaddr;     // gateway IP
STATIC UINT8      DhcpChAddr[16]; // client hardware address
STATIC UINT8      *DhcpSName;     // server host name  64
STATIC UINT8      *DhcpFile;      // boot file name  128
STATIC UINT32     DhcpMagic;      // BOOTP magic header
STATIC PAYLOAD_T  DhcpOptions = { NULL, 0 };
STATIC UINT16     DhcpSPort;      // Source Port used by udp
STATIC UINT16     DhcpDPort;      // Destination Port used by udp
STATIC UINT8      DhcpRemoteEth[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

FIELD_T           DhcpField[] = {
  /* name        type    value         M      IsSet?*/
  {
    "Dhcp_op",
    OCTET1,
    &DhcpOp,
    TRUE,
    &OpOk
  },
  {
    "Dhcp_htype",
    OCTET1,
    &DhcpHType,
    FALSE,
    &HTypeOk
  },
  {
    "Dhcp_hlen",
    OCTET1,
    &DhcpHLen,
    FALSE,
    &HLenOk
  },
  {
    "Dhcp_hops",
    OCTET1,
    &DhcpHops,
    FALSE,
    &HopsOk
  },
  {
    "Dhcp_xid",
    OCTET4,
    &DhcpXid,
    TRUE,
    &XidOk
  },
  {
    "Dhcp_secs",
    OCTET2,
    &DhcpSecs,
    FALSE,
    &SecsOk
  },
  {
    "Dhcp_flags",
    OCTET2,
    &DhcpFlags,
    FALSE,
    &FlagsOk
  },
  {
    "Dhcp_ciaddr",
    IPADDR,
    &DhcpCIaddr,
    FALSE,
    &CIaddrOk
  },
  {
    "Dhcp_yiaddr",
    IPADDR,
    &DhcpYIaddr,
    FALSE,
    &YIaddrOk
  },
  {
    "Dhcp_siaddr",
    IPADDR,
    &DhcpSIaddr,
    FALSE,
    &SIaddrOk
  },
  {
    "Dhcp_giaddr",
    IPADDR,
    &DhcpGIaddr,
    FALSE,
    &GIaddrOk
  },
  {
    "Dhcp_chaddr",
    MACADDR,
    DhcpChAddr,
    FALSE,
    &ChAddrOk
  },
  {
    "Dhcp_sname",
    STRING,
    &DhcpSName,
    FALSE,
    &SnameOk
  },
  {
    "Dhcp_file",
    STRING,
    &DhcpFile,
    FALSE,
    &FileOk
  },
  {
    "Dhcp_magic",
    OCTET4,
    &DhcpMagic,
    FALSE,
    &MagicOk
  },
  {
    "Dhcp_options",
    PAYLOAD,
    &DhcpOptions,
    FALSE,
    &OptionsOk
  },
  {
    "Dhcp_sport",
    OCTET2,
    &DhcpSPort,
    FALSE,
    &SportOk
  },
  {
    "Dhcp_dport",
    OCTET2,
    &DhcpDPort,
    FALSE,
    &DportOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
DhcpCreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create a DHCP packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  The pointer to the libnet structure

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  UINT32        Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;
  UINT8         *OptData;
  UINT32        OptLen;

  EMS_STATUS    Status;
  //
  // Initialize all the local variables
  //
  for (Index = 0; DhcpField[Index].Name; Index++) {
    *DhcpField[Index].IsOk  = FALSE;
    Status                  = GetValueByName (&DhcpField[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }

  /*
  *  Initialize the libnet
  */
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );

  if (NULL == l) {
    return NULL;
  }
  //
  // Append End Option
  //
  OptLen  = (OptionsOk ? DhcpOptions.Len : 0) + 1;
  OptData = calloc (sizeof (UINT8), OptLen);
  if (OptionsOk) {
    memcpy (OptData, DhcpOptions.Payload, DhcpOptions.Len);
  }

  OptData[OptLen - 1] = 0xff;

  //
  // LIBNET_DHCP_REQUEST
  //
  Tag = libnet_build_dhcpv4 (
          DhcpOp,                                 // op
          HTypeOk ? DhcpHType : 1,                // hardware type
          HLenOk ? DhcpHLen : 6,                  // hardware address length
          HopsOk ? DhcpHops : 0,                  // hops
          DhcpXid,                                // xid
          SecsOk ? (DhcpSecs) : 0,                // seconds since bootstrap
          FlagsOk ? (DhcpFlags) : (0x8000),       // flags
          CIaddrOk ? (DhcpCIaddr) : 0,            // client ip
          YIaddrOk ? (DhcpYIaddr) : 0,            // your ip
          SIaddrOk ? (DhcpSIaddr) : 0,            // server ip
          GIaddrOk ? (DhcpGIaddr) : 0,            // gateway ip
          ChAddrOk ? DhcpChAddr : RemoteEthaddr,  // client hardware addr
          SnameOk ? DhcpSName : NULL,             // server host name
          FileOk ? DhcpFile : NULL,               // boot file
          OptData,                                // options ptr
          OptLen,                                 // options length
          // OptionsOk?dhcp_options.payload : NULL, // dhcp options stuck // OptionsOk?dhcp_options.len : 0,          // length of options
          l,  // libnet handle
          0   // libnet id
          );

  if (-1 == Tag) {
    return NULL;
  }

  Len = LIBNET_UDP_H + LIBNET_DHCPV4_H + OptLen;

  //
  // wrap it into UDP
  //
  Tag = libnet_build_udp (
          SportOk ? DhcpSPort : 67, // source port
          DportOk ? DhcpDPort : 68, // destination port
          Len,                      // packet size
          0,                        // checksum
          NULL,
          0,
          l,
          0
          );

  Len = LIBNET_IPV4_H + LIBNET_UDP_H + LIBNET_DHCPV4_H + OptLen;

  Tag = libnet_build_ipv4 (
          Len,
          0x10,
          GetIpId (),
          0,
          16,
          IPPROTO_UDP,
          0,
          htonl (LocalIp),
          htonl (0xFFFFFFFF),
          NULL,
          0,
          l,
          0
          );
  if (-1 == Tag) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          DhcpRemoteEth,
          /* ethernet destination */LocalEthaddr,
          /* ethernet source */ETHERTYPE_IP,
          /* protocol type */NULL,
          /* payload */0,
          /* payload size */l,
          /* libnet handle */0
          );  /* libnet id */

  if (-1 == Tag) {
    return NULL;
  }

  return l;
}

STATIC
FIELD_T *
DhcpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack a DHCP packet

Arguments:

  Packet  - The pointer to the packet
  Length  - The size of the packet

Returns:

  The pointer to the libnet structure

--*/
{
  DHCP_HEADER *Header;
  UINT32      PayloadLen;

  if (Length < (sizeof (DHCP_HEADER) + sizeof (UDP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  Header      = (DHCP_HEADER *) (Packet + sizeof (ETH_HEADER) + sizeof (IP_HEADER) + sizeof (UDP_HEADER));
  DhcpOp      = Header->DhcpOp;
  DhcpHType   = Header->DhcpHType;
  DhcpHLen    = Header->DhcpHLen;
  DhcpHops    = Header->DhcpHops;
  DhcpXid     = ntohl (Header->DhcpXid);
  DhcpSecs    = ntohs (Header->DhcpSecs);
  DhcpFlags   = ntohs (Header->DhcpFlags);
  DhcpCIaddr  = ntohl (Header->DhcpCIaddr);
  DhcpYIaddr  = ntohl (Header->DhcpYIaddr);
  DhcpSIaddr  = ntohl (Header->DhcpSIaddr);
  DhcpGIaddr  = ntohl (Header->DhcpGIaddr);
  memcpy (DhcpChAddr, Header->DhcpChAddr, 16);
  DhcpSName = _strdup (Header->DhcpSName);
  DhcpFile  = _strdup (Header->DhcpFile);
  DhcpMagic = Header->DhcpMagic;
  //
  //  dhcp_options
  //
  if (NULL != DhcpOptions.Payload) {
    free (DhcpOptions.Payload);
    DhcpOptions.Payload = NULL;
    DhcpOptions.Len     = 0;
  }

  PayloadLen = Length - sizeof (DHCP_HEADER) - sizeof (UDP_HEADER) - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
  if (PayloadLen) {
    DhcpOptions.Payload = malloc (PayloadLen);
    memcpy (
      DhcpOptions.Payload,
      Packet + sizeof (DHCP_HEADER) + sizeof (UDP_HEADER) + sizeof (IP_HEADER) + sizeof (ETH_HEADER),
      PayloadLen
      );
    DhcpOptions.Len = PayloadLen;
  }

  return DhcpField;
}

STATIC
DHCP_OPTION         *
GetDhcpOptionFromName (
  INT8    *OptName
  );

STATIC
INT32
GetIpAddressValue (
  INT8          *Value, // value to validate
  INT8          *StripValue
  );

STATIC
INT32
GetUint32Value (
  INT8          *Value, // value to validate
  INT8          *StripValue
  );

STATIC
INT32
GetUint8Value (
  INT8          *Value, // value to validate
  INT8          *StripValue
  );

STATIC
INT8                *
GetNextOption (
  INT32       *RemainLen,
  INT8        **RemainPtr
  );

STATIC DHCP_OPTION  DhcpOpts[] = {
  {
    "Subnet_Mask",
    1,
    4,
    GetIpAddressValue,
    NULL
  },
  {
    "Req_Ip_Addr",
    50,
    4,
    GetIpAddressValue,
    NULL
  },
  {
    "Server_Id",
    54,
    4,
    GetIpAddressValue,
    NULL
  },
  {
    "IP_Lease_T",
    51,
    4,
    GetUint32Value,
    NULL
  },
  {
    "Renew_Time",
    58,
    4,
    GetUint32Value,
    NULL
  },
  {
    "Rebind_Time",
    59,
    4,
    GetUint32Value,
    NULL
  },
  {
    "Mesg_Type",
    53,
    1,
    GetUint8Value,
    NULL
  },
  {
    NULL
  }
};

STATIC
INT32
GetIpAddressValue (
  INT8          *Value, // value to validate
  INT8          *StripValue
  )
/*++

Routine Description:

  Get IP address

Arguments:

  Value      - Return the IP address value
  StripValue - Return the Striped IP address value

Returns:

  0 Failure
  4 Success

--*/
{
  UINT32  Temp;

  //
  // the input value should be "XX.XX.XX.XX"
  //
  if (AsciiStringToIpv4 (Value, &Temp) <= 0) {
    return 0;
  }

  * (UINT32 *) StripValue = htonl (Temp);
  return 4;
}

STATIC
INT32
GetUint32Value (
  INT8          *Value, // value to validate
  INT8          *StripValue
  )
/*++

Routine Description:

  Get UINT32 value

Arguments:

  Value      - Return the UINT32 value
  StripValue - Return the Striped INT32 value

Returns:

  0 Failure
  4 Success

--*/
{
  UINT32  Temp;

  if (AsciiStringToUint32 (Value, &Temp) > 4) {
    return 0;
  }

  * (UINT32 *) StripValue = htonl (Temp);
  return 4;
}

STATIC
INT32
GetUint8Value (
  INT8          *Value, // value to validate
  INT8          *StripValue
  )
/*++

Routine Description:

  Get UINT8 value

Arguments:

  Value      - Return the UINT8 value
  StripValue - Return the Striped UINT8 value

Returns:

  0 Failure
  1 Success

--*/
{
  UINT32  Temp;

  if (1 != AsciiStringToUint32 (Value, &Temp)) {
    return 0;
  }

  *StripValue = (INT8) Temp;

  return 1;
}

INT8
DhcpBuildOption (
  INT8 *Type,
  INT8 *Value,
  INT8 **Options
  )
/*++

Routine Description:

  Build DHCP option

Arguments:

  Type    - The type of the DHCP option
  Value   - The value of the option
  Options - Return the option result

Returns:

  The size of the option

--*/
{
  DHCP_OPTION *DHCP_OPTION;
  DHCP_OPTION = GetDhcpOptionFromName (Type);
  if (DHCP_OPTION == NULL) {
    return 0;
  }

  *Options = calloc (DHCP_OPTION->Len + 2, 1);
  if (*Options == NULL) {
    return 0;
  }

  *(*Options)     = DHCP_OPTION->Code;
  *(*Options + 1) = DHCP_OPTION->Len;
  if (!DHCP_OPTION->Validate (Value, *Options + 2)) {
    free (*Options);
    return 0;
  }

  return DHCP_OPTION->Len + 2;
}

STATIC
DHCP_OPTION *
GetDhcpOptionFromName (
  INT8    *OptName
  )
/*++

Routine Description:

  Get DHCP option accroding to name

Arguments:

  OptName  - The option name

Returns:

  The pointer to the DHCP option

--*/
{
  INT32 Index;
  for (Index = 0; Index < (sizeof (DhcpOpts) / sizeof (DHCP_OPTION) - 1); Index++) {
    if (strcmp_i (OptName, DhcpOpts[Index].Name) == 0) {
      return &DhcpOpts[Index];
    }
  }

  return NULL;
}

/*++
Routine Description:
    
Argumems:
  @ Input:  Len/Ptr, Raw Packet
  @ Output: List of T-L-V, Raw Packet not changed, Malloc a list of ptr
  
Returns:
  @return      : if succeed, return true, else return false
--*/
BOOLEAN
UnpackDhcpPayload (
  IN  UINT32       PayloadLen,
  IN  INT8         *PayloadPtr,
  OUT UINT32       *OptionCnt,
  OUT INT8         **OptionList
  )
/*++

Routine Description:

  Unpack the DHCP raw packet

Arguments:

  PayloadLen - The size of the raw packet
  PayloadPtr - The raw packet
  OptionCnt  - Return the count of options
  OptionList - Return the list of options

Returns:

  TRUE or FALSE

--*/
{
  UINT32          Count;
  INT8            *PacketPointer;
  INT8            *option;
  UINT32          RemainLen;
  DHCP_OPTION_TLV *tlv;
  UINT32          Index;

  //
  // get option count
  //
  RemainLen    = PayloadLen;
  Count         = 0;
  PacketPointer = PayloadPtr;
  while (RemainLen) {
    if (GetNextOption (&RemainLen, &PacketPointer)) {
      Count++;
    } else {
      //
      // If (remain_len != 0) && (no valid option in the remain_len)
      //
      if (RemainLen != 0) {
        //
        // the last option can be end option, code = 255
        //
        if ((RemainLen != 1) || PacketPointer[0] != -1) {
          printf ("%d\n", PacketPointer[0]);
          return FALSE;
        } else {
          break;
        }
      }
    }
  }
  //
  // assign option list
  //
  PacketPointer = PayloadPtr;
  *OptionCnt    = Count;
  *OptionList   = malloc (Count * sizeof (DHCP_OPTION_TLV));
  for (Index = 0; Index < Count; Index++) {
    tlv         = (DHCP_OPTION_TLV *) (*OptionList + sizeof (DHCP_OPTION_TLV) * Index);
    RemainLen  = PayloadLen;
    option      = GetNextOption (&RemainLen, &PacketPointer);
    tlv->Type   = *(option);
    tlv->Len    = *(option + 1);
    tlv->Value  = option + 2;
  }

  return TRUE;
}

/*++
Routine Description:  get_next_option
    
Argumems:
  @ remain_len
  @ remain_ptr
  
Returns:
  @return      : pointer to next option
--*/
STATIC
INT8 *
GetNextOption (
  INT32       *RemainLen,
  INT8        **RemainPtr
  )
/*++

Routine Description:

  Get the next option

Arguments:

  RemainLen  - The remain length
  RemainPtr  - The pointer to the remain options

Returns:

  The pointer to the option

--*/
{
  INT8  Len;
  INT8  *option;

  option = *RemainPtr;
  if (*RemainLen <= 0 || !option) {
    return NULL;
  }
  //
  // Filter pad option,
  // pad option is only used to cause subsequent field to align on word boundary
  //
  while (*RemainLen > 0) {
    if (*option == 0) {
      option++;
      (*RemainLen)--;
    } else {
      break;
    }
  }
  //
  // check if valid option existed in the remain_len
  //
  if (*RemainLen <= 2) {
    return NULL;
  }
  //
  // option = *remain_ptr;
  //
  Len = *(option + 1);
  if (Len > *RemainLen) {
    return NULL;
  }

  *RemainPtr = (option + 2 + Len);
  *RemainLen -= (2 + Len);
  return option;
}

/*++
Routine Description:  dhcp_option_list_include
    check if the needle is subset of heystack
    
Argumems:
  @ heystack_count, heystack_opt_list: option list in heystack
  @ needle_count, needle_opt_list: option list in needle
  
Returns:
  @return      : if the needle is subset of heystack, return true;
                 else return false;
--*/
BOOLEAN
DhcpOptionListInclude (
  UINT32      HeyStackCount,
  UINT8       *HeyStackOptList,
  UINT32      NeedleCount,
  UINT8       *NeedleOptList
  )
/*++

Routine Description:

  check if the needle is subset of heystack

Arguments:

  HeyStackCount    - The count of the heystack
  HeyStackOptList  - The option list of the heystack
  NeedleCount      - The count of the needle
  NeedleOptList    - The option list of the needle

Returns:

  TRUE or FALSE

--*/
{
  UINT32          Index;

  UINT32          Index2;
  DHCP_OPTION_TLV *heystack;
  DHCP_OPTION_TLV *needle;

  if (NeedleCount > HeyStackCount) {
    return FALSE;
  }

  heystack  = (DHCP_OPTION_TLV *) HeyStackOptList;
  needle    = (DHCP_OPTION_TLV *) NeedleOptList;
  for (Index = 0; Index < NeedleCount; Index++) {
    for (Index2 = 0; Index2 < HeyStackCount; Index2++) {
      if (needle[Index].Type == heystack[Index2].Type) {
        if ((needle[Index].Len != heystack[Index2].Len) ||
            (memcmp (needle[Index].Value, heystack[Index2].Value, needle[Index].Len)) != 0
            ) {
          return FALSE;
        } else {
          break;
        }
      }
    }
    //
    // can't find needle[i] in heystack
    //
    if (Index2 == HeyStackCount) {
      return FALSE;
    }
  }

  return TRUE;
}
