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
  
    EmsProtoIpv6.c
    
Abstract:

    Implementation for functions for protocol IP

--*/

#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIpv6.h"
#include "EmsUtilityString.h"

STATIC
libnet_t            *
IPv6CreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T             *
IPv6UnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC Tcl_CmdProc  TclConfigIPV6;

STATIC
VOID_P
IPv6TclInit (
  IN Tcl_Interp *Interp
  );

PROTOCOL_ENTRY_T    IPv6Protocol = {
  "IPv6",           /* name */
  IPv6CreatePacket, /* Create packet routine */
  IPv6UnpackPacket, /* Unpacket routine */
  IPv6TclInit       /* IP TCL initialzation routine*/
};

EMS_IPV6_ADDR       LocalIPv6;
EMS_IPV6_ADDR       RemoteIPv6;

STATIC UINT8               IPv6Ver;
STATIC UINT8               IPv6TC;
STATIC UINT32              IPv6FL;
STATIC UINT16              IPv6PldLen;
STATIC UINT8               IPv6NH;
STATIC UINT8               IPv6HL;
STATIC EMS_IPV6_ADDR       IPv6Src;
STATIC EMS_IPV6_ADDR       IPv6Dst;
STATIC PAYLOAD_T           IPv6Pld   = { NULL, 0 };

#define DEF_VER   0x06
#define DEF_TC    0x00
#define DEF_FL    0x00
#define DEF_NH    0x59
#define DEF_HL    0xFF

STATIC BOOLEAN      VerOk;
STATIC BOOLEAN      TcOk;
STATIC BOOLEAN      FlOk;
STATIC BOOLEAN      PldLenOk;
STATIC BOOLEAN      NHOk;
STATIC BOOLEAN      HLOk;
STATIC BOOLEAN      SrcOk;
STATIC BOOLEAN      DstOk;
STATIC BOOLEAN      PldOK;


FIELD_T             IPv6Field[] = {
  /* name         type         value     Mandatory Isset?*/
  {
    "IPv6_ver",  // Version
    OCTET1,
    &IPv6Ver,
    FALSE,
    &VerOk
  },
  {
    "IPv6_tc",  // Traffic Class
    OCTET1,
    &IPv6TC,
    FALSE,
    &TcOk
  },
  {
    "IPv6_fl",  // Flow Label
    OCTET4,
    &IPv6FL,
    FALSE,
    &FlOk
  },
  {
    "IPv6_pl",  // PayLoad Length
    OCTET2,
    &IPv6PldLen,
    FALSE,
    &PldLenOk
  },
  {
    "IPv6_nh",  // Next Header
    OCTET1,
    &IPv6NH,
    FALSE,
    &NHOk
  },
  {
    "IPv6_hl",  // Hop Limit
    OCTET1,
    &IPv6HL,
    FALSE,
    &HLOk
  },
  {
    "IPv6_src",  // Source Address
    IPV6ADDR,
    &IPv6Src,
    FALSE,
    &SrcOk
  },
  {
    "IPv6_dst",  // Destination Address
    IPV6ADDR,
    &IPv6Dst,
    FALSE,
    &DstOk
  },
  {
    "IPv6_payload", // payload
    PAYLOAD,
    &IPv6Pld,
    FALSE,
    &PldOK
  },
  {
    NULL
  }
};


STATIC
libnet_t *
IPv6CreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create an IPv6 packet

Arguments:

  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  NULL if error occurs
  The pointer to a libnet_t type's object if successfully

--*/
{
  libnet_t      *l;
  libnet_ptag_t Tag;
  UINT32        Index;
  INT8          ErrBuf[LIBNET_ERRBUF_SIZE];
  UINT32        Len;
  EMS_STATUS    Status;
  //
  // Initialize all the local variables
  //
  for (Index = 0; IPv6Field[Index].Name; Index++) {
    *IPv6Field[Index].IsOk  = FALSE;
    Status                = GetValueByName (&IPv6Field[Index], Argc, Argv);
    if (IsError (Status)) {
      return NULL;
    }
  }
  //
  //  Initialize the libnet
  //
  l = libnet_init (
        LIBNET_LINK,
        /* injection type */EmsInterface,
        /* network interface */ErrBuf /* errbuf */
        );
  if (NULL == l) {
    return NULL;
  }

  /* 
 * If options has been configured. Add here!!!
 */

  /*
 * Build IP packet
 */
  Len = LIBNET_IPV6_H;
  Len += PldLenOk ? IPv6PldLen : 0;
/* Build IPv6 Packet
 * @param tc traffic class
 * @param fl flow label
 * @param len total length of the IP packet
 * @param nh next header
 * @param hl hop limit
 * @param src source IPv6 address
 * @param dst destination IPv6 address
 * @param payload optional payload or NULL
 * @param payload_s payload length or 0
 * @param l pointer to a libnet context
 * @param ptag protocol tag to modify an existing header, 0 to build a new one
 * @return protocol tag value on success, -1 on error
 */

  Tag = libnet_build_ipv6 (
          /* Traffic Class*/TcOk ? IPv6TC : DEF_TC,
          /* flow label */FlOk ? IPv6FL : DEF_FL,
          /* total length of the IP packet */PldLenOk ? IPv6PldLen: Len,
          /* nh next header */NHOk ? IPv6NH : DEF_NH,
          /* hl hop limit*/HLOk ? IPv6HL : DEF_HL,
          /* src source IPv6 address */SrcOk ? EmsIPv6htons (IPv6Src) : EmsIPv6htons(LocalIPv6),
          /* dst destination IPv6 address*/DstOk ? EmsIPv6htons(IPv6Dst) : EmsIPv6htons(RemoteIPv6),
          /* payload optiona payload or NULL*/PldLenOk ? IPv6Pld.Payload : NULL,
          /* payload_s payload length or 0 */PldLenOk ?  IPv6Pld.Len: 0,
          /* l pointer to a libnet context */l,
          /* ptay, 0 to build a new one */0
          );
  if (-1 == Tag) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          RemoteEthaddr,
          /* ethernet destination */LocalEthaddr,
          /* ethernet source */0x86dd,
          /* protocol type */NULL,
          /* payload */0,
          /* payload size */l,
          /* libnet handle */0  /* libnet id */
          );
  if (-1 == Tag) {
    return NULL;
  }

  return l;
}

/*++
Routine Description:
  
Argumems:
  @
Returns:
  @return      : 
--*/
STATIC
FIELD_T *
IPv6UnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an IPv6 packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  NULL if error occurs
  The pointer to a FIELD_T type's object

--*/
{
  IPV6_HEADER *Header;
  UINT32    PayloadLen;
  UINT32    temp;

  if (Length < (sizeof (IPV6_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  Header    = (IPV6_HEADER *) (Packet + sizeof (ETH_HEADER));
  temp = ntohl (Header->IPV6First32);
  IPv6Ver = (UINT8)(temp >> 28);
  IPv6TC  = (UINT8)((temp & 0x0ff00000) >> 20);
  IPv6FL  = temp & 0x000fffff;
  //IPv6TC    = (UINT8) Header->IPv6TC;
  //IPv6FL    = (UINT32)Header->IPv6FL;
  IPv6PldLen= ntohs (Header->IPv6PldLen);
  IPv6NH    = Header->IPv6NH;
  IPv6HL    = Header->IPv6HL;
  IPv6Src   = EmsIPv6ntohs(Header->IPv6Src);
  IPv6Dst   = EmsIPv6ntohs(Header->IPv6Dst);

  if (NULL != IPv6Pld.Payload) {
    free (IPv6Pld.Payload);
    IPv6Pld.Payload = NULL;
    IPv6Pld.Len     = 0;
  }

  PayloadLen = Length - sizeof (IPV6_HEADER) - sizeof (ETH_HEADER);
  if (PayloadLen) {
    IPv6Pld.Payload = malloc (PayloadLen);
    memcpy (IPv6Pld.Payload, Packet + sizeof (IPV6_HEADER) + sizeof (ETH_HEADER), PayloadLen);
    IPv6Pld.Len = PayloadLen;
  }

  return IPv6Field;
}

VOID_P
IPv6TclInit (
  Tcl_Interp *Interp
  )
/*++

Routine Description:

  EMS IP related TCL initialization.

Arguments:

  Interp      - TCL intepreter.

Returns:

  None

--*/
{
  //
  // Create Packet related TCL commands
  //
  Tcl_CreateCommand (
    Interp,
    "LocalIPv6",
    TclConfigIPV6,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  Tcl_CreateCommand (
    Interp,
    "RemoteIPv6",
    TclConfigIPV6,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  //
  // Link Packet related TCL variables
  //
}

STATIC
INT32
TclConfigIPV6 (
  IN ClientData        clientData,
  IN Tcl_Interp        *Interp,
  IN INT32             Argc,
  IN CONST84 INT8      *Argv[]
  )
/*++

Routine Description:

  TCL command "LocalIp" implementation routine  

Arguments:

  clientData  - Private data, if any.
  Interp      - TCL intepreter
  Argc        - Argument counter.
  Argv        - Argument value pointer array.

Returns:

  TCL_OK or TCL_ERROR
--*/
{
  INT8          *Arg;
  EMS_IPV6_ADDR IPv6Addr;

  if (Argc == 1) {
    goto WrongArg;
  };

  Arg = (INT8 *) Argv[1];
  if (AsciiStringToIpv6 (Arg, &IPv6Addr) <= 0) {
    goto WrongArg;
  };

  if (0 == strcmp_i ((INT8 *) Argv[0], "localipv6")) {
    LocalIPv6 = IPv6Addr;
  } else {
    RemoteIPv6 = IPv6Addr;
  }

  return TCL_OK;
WrongArg:
  /* Say somethine here */
  return TCL_ERROR;
}

EMS_IPV6_ADDR
EmsIPv6htons(
  EMS_IPV6_ADDR hostIPv6
)
/*++

Routine Description:

 This function takes a IPv6 Address
 in host byte order and returns a IPv6 Address
 in network byte order used in TCP/IP networks

Arguments:

  EMS_IPV6_ADDR hostIpv6 : The IPV6 Address in host byte order

Returns:

  Return the IP Id

--*/
{
  EMS_IPV6_ADDR netIPv6;
  UINT8 Index;

  for (Index = 0; Index < 8 ; Index++) {
    netIPv6.__u6_addr.__u6_addr16[Index] = htons (hostIPv6.__u6_addr.__u6_addr16[Index]);
  }
  return netIPv6;
}
EMS_IPV6_ADDR
EmsIPv6ntohs (
  EMS_IPV6_ADDR netIPv6
)
/*++

Routine Description:

 This function takes a IPv6 Address
 in TCP/IP networks and returns a IPv6 Address
 in network byte order used in host byte order 

Arguments:

  EMS_IPV6_ADDR netIpv6 : The IPV6 Address n TCP/IP networks

Returns:

  Return the EMS_IPV6_ADDR in  TCP/IP networks

--*/
{
  EMS_IPV6_ADDR hostIPv6;
  UINT8 Index;

  for (Index = 0; Index < 8 ; Index++) {
    hostIPv6.__u6_addr.__u6_addr16[Index] = ntohs (netIPv6.__u6_addr.__u6_addr16[Index]);
  }
  return hostIPv6;
}


UINT32
EmsCalPHeaderSum16(
  IN EMS_IPV6_ADDR localIPv6,
  IN EMS_IPV6_ADDR remoteIPv6,
  IN UINT8 nh,
  IN UINT32 len
)
/*++		

Routine Description:				

 This function calculate the sum for
 Pesudo IPv6 Header.

Arguments:

  EMS_IPV6_ADDR localIPv6     : The local IPV6 Address in host byte order
  EMS_IPV6_ADDR remoetIPv6 : The remote IPV6 Address in host byte order 
  UINT8 nh			           : Flag for next header
  UINT32 len				    : Length of TCP/UDP payload
  
Returns:

  UINT32 sum			           : 32bit sum 

--*/
{
	UINT32 Sum = 0;
	EMS_IPV6_ADDR TempIPv6;
	UINT32 Index;

	TempIPv6 = EmsIPv6htons(localIPv6);
	for( Index = 0; Index<16; ) {
		Sum += TempIPv6.__u6_addr.__u6_addr8[Index++] << 8;
		Sum += TempIPv6.__u6_addr.__u6_addr8[Index++];
	}
	TempIPv6 = EmsIPv6htons(remoteIPv6);
	for( Index = 0; Index<16; ) {
		Sum += TempIPv6.__u6_addr.__u6_addr8[Index++] << 8;
		Sum += TempIPv6.__u6_addr.__u6_addr8[Index++];
	}
	Sum += nh;
	Sum += (len & 0x00ff);
	Sum += (len>>8)<<8;

	return Sum;
}
;

UINT32 
EmsCalBufSum16(
  IN UINT32 offset,
  IN u_int8_t *payload,
  IN UINT32 len
)
/*++		

Routine Description:				

 This function calculate the sum for
 a buffer. If the buffer starts with odd
 byte, extra calcualtion will be done

Arguments:

  UINT32 offset			    : Offset of the start byte
  UINT8 *payload			    : Buffer pointer
  UINT32 len				    : Buffer length
  
Returns:

  UINT32 sum			           : 32bit sum

--*/
{
	UINT32 Index;
	UINT32 Sum = 0;

	Index = 0;
	if( offset & 0x01 ){
		Sum += *(payload+Index);
		Index ++;
	}

	while( Index < len ) {
		Sum += (*(payload+Index) << 8);
		Index ++;
		if( Index < len ) {
			Sum += *(payload+Index);
			Index ++;
		}
	}
	
	return Sum;
}
;

UINT16
EmsCalCheckSum16(
  IN UINT32 sum
)
/*++		

Routine Description:				

 This function generate 16bit checksum from
 32bit sum

Arguments:

  UINT32 sum   			    : 32bit sum
  
Returns:

  UINT16 checksum			    : 16bit checksum

--*/
{
	UINT16 CheckSum;
	
  	while (sum >> 16) {
    		sum = (sum & 0xffff) + (sum >> 16);
  	}
	CheckSum = (UINT16) sum;
	
	return (UINT16) (~CheckSum);
}
;