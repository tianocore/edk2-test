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
  
    EmsProtoIp.c
    
Abstract:

    Implementation for functions for protocol IP

--*/

#include "EmsNet.h"
#include "EmsTclInit.h"
#include "EmsPktMain.h"
#include "EmsPktCreate.h"
#include "EmsProtocols.h"
#include "EmsProtoEth.h"
#include "EmsProtoIp.h"
#include "EmsUtilityString.h"

STATIC
libnet_t            *
IpCreatePacket (
  IN INT32 Argc,
  IN INT8  *Argv[]
  );

STATIC
FIELD_T             *
IpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  );

STATIC Tcl_CmdProc  TclConfigIp;

STATIC
VOID_P
IpTclInit (
  IN Tcl_Interp *Interp
  );

PROTOCOL_ENTRY_T    IpProtocol = {
  "IP",           /* name */
  IpCreatePacket, /* Create packet routine */
  IpUnpackPacket, /* Unpacket routine */
  IpTclInit       /* IP TCL initialzation routine*/
};

UINT32              LocalIp;
UINT32              RemoteIp;

STATIC UINT8        Ipv4Ver;
STATIC UINT8        Ipv4Ihl;
STATIC UINT16       Ipv4Len;
STATIC UINT8        Ipv4Tos;
STATIC UINT16       Ipv4Id;
STATIC UINT16       Ipv4Frag;
STATIC UINT8        Ipv4Ttl;
STATIC UINT8        Ipv4Prot;
STATIC UINT16       Ipv4Sum;
STATIC UINT32       Ipv4Src;
STATIC UINT32       Ipv4Dst;
STATIC PAYLOAD_T    Ipv4Opts  = { NULL, 0 };
STATIC PAYLOAD_T    Ipv4Pld   = { NULL, 0 };

#define DEF_VER   0x04
#define DEF_IHL   0x05
#define DEF_SUM   0x00
#define DEF_TTL   0x40
#define DEF_TOS   0x00
#define DEF_FRAG  0x00

STATIC BOOLEAN      VerOk;
STATIC BOOLEAN      IhlOk;
STATIC BOOLEAN      LenOk;
STATIC BOOLEAN      TosOk;
STATIC BOOLEAN      IdOk;
STATIC BOOLEAN      FragOk;
STATIC BOOLEAN      TtlOk;
STATIC BOOLEAN      ProtOk;
STATIC BOOLEAN      SumOk;
STATIC BOOLEAN      SrcOk;
STATIC BOOLEAN      DstOk;
STATIC BOOLEAN      OptsOk;
STATIC BOOLEAN      PldOk;

FIELD_T             IpField[] = {
  /* name         type         value     Mandatory Isset?*/
  {
    "Ipv4_ver",
    OCTET1,
    &Ipv4Ver,
    FALSE,
    &VerOk
  },
  {
    "Ipv4_ihl",
    OCTET1,
    &Ipv4Ihl,
    FALSE,
    &IhlOk
  },
  {
    "Ipv4_len",
    OCTET2,
    &Ipv4Len,
    FALSE,
    &LenOk
  },
  {
    "Ipv4_tos",
    OCTET1,
    &Ipv4Tos,
    FALSE,
    &TosOk
  },
  {
    "Ipv4_id",
    OCTET2,
    &Ipv4Id,
    FALSE,
    &IdOk
  },
  {
    "Ipv4_frag",
    OCTET2,
    &Ipv4Frag,
    FALSE,
    &FragOk
  },
  {
    "Ipv4_ttl",
    OCTET1,
    &Ipv4Ttl,
    FALSE,
    &TtlOk
  },
  {
    "Ipv4_prot",
    OCTET1,
    &Ipv4Prot,
    TRUE,
    &ProtOk
  },
  {
    "Ipv4_sum",
    OCTET2,
    &Ipv4Sum,
    FALSE,
    &SumOk
  },
  {
    "Ipv4_src",
    IPADDR,
    &Ipv4Src,
    FALSE,
    &SrcOk
  },
  {
    "Ipv4_dst",
    IPADDR,
    &Ipv4Dst,
    FALSE,
    &DstOk
  },
  {
    "Ipv4_opts",
    PAYLOAD,
    &Ipv4Opts,
    FALSE,
    &OptsOk
  },
  {
    "Ipv4_payload",
    PAYLOAD,
    &Ipv4Pld,
    FALSE,
    &PldOk
  },
  {
    NULL
  }
};

STATIC
libnet_t *
IpCreatePacket (
  INT32 Argc,
  INT8  *Argv[]
  )
/*++

Routine Description:

  Create an IP packet

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
  for (Index = 0; IpField[Index].Name; Index++) {
    *IpField[Index].IsOk  = FALSE;
    Status                = GetValueByName (&IpField[Index], Argc, Argv);
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
  Len = LIBNET_IPV4_H;
  Len += OptsOk ? Ipv4Opts.Len : 0;
  Len += PldOk ? Ipv4Pld.Len : 0;

  Tag = libnet_build_ipv4 (
          LenOk ? Ipv4Len : Len,
          /* length */TosOk ? Ipv4Tos : DEF_TOS,
          /* TOS    */IdOk ? Ipv4Id : GetIpId (),
          /* IP ID */FragOk ? Ipv4Frag : DEF_FRAG,
          /* IP Frag */TtlOk ? Ipv4Ttl : DEF_TTL,
          /* TTL */Ipv4Prot,
          /* protocol */SumOk ? Ipv4Sum : DEF_SUM,
          /* checksum */SrcOk ? htonl (Ipv4Src) : htonl (LocalIp),
          /* source IP */DstOk ? htonl (Ipv4Dst) : htonl (RemoteIp),
          /* destination IP */PldOk ? Ipv4Pld.Payload : NULL,
          /* payload */PldOk ? Ipv4Pld.Len : 0,
          /* payload size */l,
          /* libnet handle */0
          );
  if (-1 == Tag) {
    return NULL;
  }

  Tag = libnet_build_ethernet (
          RemoteEthaddr,
          /* ethernet destination */LocalEthaddr,
          /* ethernet source */ETHERTYPE_IP,
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
IpUnpackPacket (
  IN UINT8  *Packet,
  IN UINT32 Length
  )
/*++

Routine Description:

  Unpack an IP packet

Arguments:

  Packet  - The packet should be unpacked
  Length  - The size of the packet

Returns:

  NULL if error occurs
  The pointer to a FIELD_T type's object

--*/
{
  IP_HEADER *Header;
  UINT32    PayloadLen;

  if (Length < (sizeof (IP_HEADER) + sizeof (ETH_HEADER))) {
    return NULL;
  }

  Header    = (IP_HEADER *) (Packet + sizeof (ETH_HEADER));

  Ipv4Ver   = (UINT8) Header->IpVer;
  Ipv4Ihl   = (UINT8) Header->IpIhl;
  Ipv4Len   = ntohs (Header->IpLen);
  Ipv4Tos   = Header->IpTos;
  Ipv4Id    = ntohs (Header->IpId);
  Ipv4Frag  = ntohs (Header->IpFrag);
  Ipv4Ttl   = Header->IpTtl;
  Ipv4Prot  = Header->IpProto;
  Ipv4Sum   = ntohs (Header->IpSum);
  Ipv4Src   = ntohl (Header->IpSrc);
  Ipv4Dst   = ntohl (Header->IpDst);

  if (NULL != Ipv4Pld.Payload) {
    free (Ipv4Pld.Payload);
    Ipv4Pld.Payload = NULL;
    Ipv4Pld.Len     = 0;
  }

  PayloadLen = Length - sizeof (IP_HEADER) - sizeof (ETH_HEADER);
  if (PayloadLen) {
    Ipv4Pld.Payload = malloc (PayloadLen);
    memcpy (Ipv4Pld.Payload, Packet + sizeof (IP_HEADER) + sizeof (ETH_HEADER), PayloadLen);
    Ipv4Pld.Len = PayloadLen;
  }

  return IpField;
}

VOID_P
IpTclInit (
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
    "LocalIp",
    TclConfigIp,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  Tcl_CreateCommand (
    Interp,
    "RemoteIp",
    TclConfigIp,
    (ClientData) NULL,
    (Tcl_CmdDeleteProc *) NULL
    );
  //
  // Link Packet related TCL variables
  //
}

STATIC
INT32
TclConfigIp (
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
  INT8    *Arg;
  UINT32  Addr;

  if (Argc == 1) {
    goto WrongArg;
  };

  Arg = (INT8 *) Argv[1];
  if (AsciiStringToIpv4 (Arg, &Addr) <= 0) {
    goto WrongArg;
  };

  if (0 == strcmp_i ((INT8 *) Argv[0], "localip")) {
    LocalIp = Addr;
  } else {
    RemoteIp = Addr;
  }

  return TCL_OK;
WrongArg:
  /* Say somethine here */
  return TCL_ERROR;
}

UINT16
GetIpId (
  VOID_P
  )
/*++

Routine Description:

  Get a IP Id

Arguments:

  None

Returns:

  Return the IP Id

--*/
{
  STATIC UINT16 Id = 0;
  return Id++;
}
