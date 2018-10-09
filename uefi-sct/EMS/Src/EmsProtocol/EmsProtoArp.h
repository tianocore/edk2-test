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
  
    EmsProtoArp.h
    
Abstract:

    Incude header files for protocol ARP

--*/

#ifndef __EMS_ARP_H__
#define __EMS_ARP_H__

#define ARP_OPER_REQUEST              1
#define ARP_OPER_REPLY                2
#define ARP_OPER_REVREQUEST           3
#define ARP_OPER_REVREPLY             4
#define ARP_OPER_DRARP_REQUEST        5
#define ARP_OPER_DRARP_REPLY          6
#define ARP_OPER_DRARP_ERROR          7
#define ARP_OPER_INARP_REQUEST        8
#define ARP_OPER_INARP_REPLY          9
#define ARP_OPER_ARP_NAK              10
#define ARP_OPER_MARS_REQUEST         11
#define ARP_OPER_MARS_MULTI           12
#define ARP_OPER_MARS_MSERV           13
#define ARP_OPER_MARS_JOIN            14
#define ARP_OPER_MARS_LEAVE           15
#define ARP_OPER_MARS_UNSERV          16
#define ARP_OPER_MARS_SJOIN           17
#define ARP_OPER_MARS_SLEAVE          18
#define ARP_OPER_MARS_GRPLST_REQUEST  19
#define ARP_OPER_MARS_GRPLST_REPLY    20
#define ARP_OPER_MARS_GRPLST_MAP      21
#define ARP_OPER_MARS_REDIRECT_MAP    22
#define ARP_OPER_MAPOS_UNARP          23

#define ARP_HTYPE_ETHERNET            1
#define ARP_HTYPE_EXP_ETHERNET        2
#define ARP_HTYPE_AMATEUR_RADIO_AX25  3
#define ARP_HTYPE_PRONET_TOKEN_RING   4
#define ARP_HTYPE_CHAOS               5
#define ARP_HTYPE_IEEE802             6
#define ARP_HTYPE_ARCNET              7
#define ARP_HTYPE_HYPERCHANNEL        8
#define ARP_HTYPE_LANSTAR             9
#define ARP_HTYPE_AUTONET_SHORT_ADDR  10
#define ARP_HTYPE_LOCALTALK           11
#define ARP_HTYPE_LOCALNET            12
#define ARP_HTYPE_ULTRA_LINK          13
#define ARP_HTYPE_SMDS                14
#define ARP_HTYPE_FRAME_RELAY         15
#define ARP_HTYPE_ATM                 16
#define ARP_HTYPE_HDLC                17
#define ARP_HTYPE_FIBRE_CHANNEL       18
#define ARP_HTYPE_ATM2                19
#define ARP_HTYPE_SERIAL_LINE         20
#define ARP_HTYPE_ATM3                21
#define ARP_HTYPE_MIL_STD             22
#define ARP_HTYPE_METRICOM            23
#define ARP_HTYPE_IEEE1394            24
#define ARP_HTYPE_MAPOS               25
#define ARP_HTYPE_TWINAXIAL           26
#define ARP_HTYPE_EUI_64              27
#define ARP_HTYPE_HIPARP              28
#define ARP_HTYPE_ISO7816_3           29
#define ARP_HTYPE_ARPSEC              30
#define ARP_HTYPE_IPSEC_TUNNEL        31
#define ARP_HTYPE_INFINIBAND          32

#define ARP_PTYPE_IP                  0x0800

#define DEF_HTYPE                     ARP_HTYPE_ETHERNET
#define DEF_PTYPE                     ARP_PTYPE_IP
#define DEF_HLEN                      6
#define DEF_PLEN                      4

extern PROTOCOL_ENTRY_T ArpProtocol;

typedef struct _ARP_HEADER {
  UINT16  HType;
  UINT16  PType;
  UINT8   HLen;
  UINT8   PLen;
  UINT16  Oper;
  UINT8   Sha[6];
  UINT8   Spa[4];
  UINT8   Tha[6];
  UINT8   Tpa[4];
} ARP_HEADER;

#endif
