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
  
    EmsProtoIcmp.h
    
Abstract:

    Incude header files for protocol ICMP

--*/

#ifndef __EMS_ICMP_H__
#define __EMS_ICMP_H__

#define ICMP_TYPE_ECHO_REPLY  0
//
//      ICMP_TYPE_RESERVED             1
//      ICMP_TYPE_RESERVED             2
//
#define ICMP_TYPE_DEST_UNREACHABLE  3
#define ICMP_TYPE_SOURCE_QUENCH     4
#define ICMP_TYPE_REDIRECT          5
#define ICMP_TYPE_ALT_HOST_ADDRESS  6
//
//      ICMP_TYPE_RESERVED             7
//
#define ICMP_TYPE_ECHO_REQUEST          8
#define ICMP_TYPE_ROUTER_ADVERTISEMENT  9
#define ICMP_TYPE_ROUTER_SOLICITATION   10
#define ICMP_TYPE_TIME_EXCEEDED         11
#define ICMP_TYPE_PARAMETER_PROBLEM     12
#define ICMP_TYPE_TIMESTAMP_REQUEST     13
#define ICMP_TYPE_TIMESTAMP_REPLY       14
#define ICMP_TYPE_INFORMATION_REQUEST   15
#define ICMP_TYPE_INFORMATION_REPLY     16
#define ICMP_TYPE_ADDRESS_MASK_REQUEST  17
#define ICMP_TYPE_ADDRESS_MASK_REPLY    18
//
//      ICMP_TYPE_RESERVED             19    (for security)
//      ICMP_TYPE_RESERVED             20-29 (for robustness exp.)
//
#define ICMP_TYPE_TRACEROUTE            30
#define ICMP_TYPE_CONVERSION_ERROR      31
#define ICMP_TYPE_MOBILE_HOST_REDIRECT  32
#define ICMP_TYPE_IPV6_WHERE_ARE_YOU    33
#define ICMP_TYPE_IPV6_I_AM_HERE        34
#define ICMP_TYPE_MOBILE_REG_REQUEST    35
#define ICMP_TYPE_MOBILE_REG_REPLY      36
#define ICMP_TYPE_DOMAIN_NAME_REQUEST   37
#define ICMP_TYPE_DOMAIN_NAME_REPLY     38
#define ICMP_TYPE_SKIP_ALGO_DISCOVERY   39
#define ICMP_TYPE_PHOTURIS_SEC_FAILURE  40
//
//      ICMP_TYPE_RESERVED             41-255
// Type 8 or 0: Echo Request or Reply
//
#define ICMP_CODE_ECHO  0

//
// Type 3: Destination Unreachable
//
#define ICMP_CODE_NETWORK_UNREACH           0
#define ICMP_CODE_HOST_UNREACH              1
#define ICMP_CODE_PROTOCOL_UNREACH          2
#define ICMP_CODE_PORT_UNREACH              3
#define ICMP_CODE_DATAGRAM_TOO_BIG          4
#define ICMP_CODE_SOURCE_ROUTE_FAILED       5
#define ICMP_CODE_DEST_NETWORK_UNKNOWN      6
#define ICMP_CODE_DEST_HOST_UNKNOWN         7
#define ICMP_CODE_SOURCE_HOST_ISOLATED      8
#define ICMP_CODE_DEST_NET_PROHIBITED       9
#define ICMP_CODE_DEST_HOST_PROHIBITED      10
#define ICMP_CODE_NETWORK_TOS_UNREACH       11
#define ICMP_CODE_HOST_TOS_UNREACH          12
#define ICMP_CODE_COMMUNICATION_UNREACH     13
#define ICMP_CODE_HOST_PRECEDENCE_VIOLATION 14
#define ICMP_CODE_PRECEDENCE_CUTOFF         15

//
// Type 4: Source Quench
//
#define ICMP_CODE_SOURCE_QUENCH 0

//
// Type 5: Redirect
//
#define ICMP_CODE_REDIRECT_NET_ERROR      0
#define ICMP_CODE_REDIRECT_HOST_ERROR     1
#define ICMP_CODE_TOS_REDIRECT_NET_ERROR  2
#define ICMP_CODE_TOS_REDIRECT_HOST_ERROR 3

//
// Type 9: Router Advertisement
//
#define ICMP_CODE_NORMAL_ROUTER_ADVERTISE 0
//
//      ICMP_CODE_RESERVE                   1-15
//
#define ICMP_CODE_NOT_ROUTE_COMMON_TRAFFIC  16
//
//      ICMP_CODE_RESERVE                   17-255
// Type 10: Router Solicitation
//
#define ICMP_CODE_ROUTER_SOLICITATION 0

//
// Type 11: Time Exceeded
//
#define ICMP_CODE_TTL_EQUAL_0             0
#define ICMP_CODE_FRAG_REASSAMBLY_TIMEOUT 1

//
// Type 12: Parameter Problem
//
#define ICMP_CODE_IP_HEADER_INVALID       0
#define ICMP_CODE_REQUIRED_OPTION_MISSING 1

//
// Type 13 or 14: Timestamp Request or Reply
//
#define ICMP_CODE_TIMESTAMP 0

//
// Type 15 or 16: Information Request or Reply
//
#define ICMP_CODE_INFORMATION 0

//
// Type 17 or 18: Address Mask Request or Reply
//
#define ICMP_CODE_ADDRESS_MASK  0

//
// Type 30: Traceroute
//
#define ICMP_CODE_OUTBOUND_PACKET_FORWARDED 0
#define ICMP_CODE_OUTBOUND_PACKET_DISCARDED 0

//
// Type 31: Conversion Error
//
#define ICMP_CODE_UNKNOWN_ERROR                       0
#define ICMP_CODE_NOT_CONVERT_OPTION                  1
#define ICMP_CODE_UNKNOWN_MANDATORY_OPTION            2
#define ICMP_CODE_KNOWN_UNSUPPORTED_OPTION            3
#define ICMP_CODE_UNSUPPORT_TRANSPORT_PROT            4
#define ICMP_CODE_OVERALL_LENGTH_EXCEEDED             5
#define ICMP_CODE_IP_HEADER_LENGTH_EXCEEDED           6
#define ICMP_CODE_TRANSPORT_PROT_GT255                7
#define ICMP_CODE_PORT_CONVERSION_OUT_RANGE           8
#define ICMP_CODE_TRANSPORT_HEAD_LEN_EXCEED           9
#define ICMP_CODE_ROLLOVER_MISSING_ACK_SET            10
#define ICMP_CODE_UNKNOWN_MANDATORY_TRANSPORT_OPTION  11

//
// Type 37 or 38: Domain Name Request or Reply
//
#define ICMP_CODE_DOMAIN_NAME 0

//
// Type 40: Photuris, Security Failures
//
#define ICMP_CODE_BAD_SPI               0
#define ICMP_CODE_AUTHENTICATION_FAILED 1
#define ICMP_CODE_DECOMPRESSION_FAILED  2
#define ICMP_CODE_DECRYPTION_FAILED     3
#define ICMP_CODE_NEED_AUTHENTICATION   4
#define ICMP_CODE_NEED_AUTHORIZATION    5

extern PROTOCOL_ENTRY_T IcmpProtocol;

typedef struct _ICMP_ECHO_HEADER {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT16  Id;
  UINT16  Seq;
} ICMP_ECHO_HEADER;

typedef struct _ICMP_ADDRESS_MASK_HEADER {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT16  Id;
  UINT16  Seq;
  UINT32  Mask;
} ICMP_ADDRESS_MASK_HEADER;

typedef struct _ICMP_DEST_UNREACH_HEADER {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT16  Unused;
  UINT16  NextHopMtu;
  UINT8   OrigVerIhl;
  UINT8   OrigTos;
  UINT16  OrigLen;
  UINT16  OrigId;
  UINT16  OrigFrag;
  UINT8   OrigTtl;
  UINT8   OrigProt;
  UINT16  OrigCheck;
  UINT32  OrigSrc;
  UINT32  OrigDst;
} ICMP_DEST_UNREACH_HEADER;

typedef struct _ICMP_REDIRECT_HEADER {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT32  GateWay;
  UINT8   OrigVerIhl;
  UINT8   OrigTos;
  UINT16  OrigLen;
  UINT16  OrigId;
  UINT16  OrigFrag;
  UINT8   OrigTtl;
  UINT8   OrigProt;
  UINT16  OrigCheck;
  UINT32  OrigSrc;
  UINT32  OrigDst;
} ICMP_REDIRECT_HEADER;

typedef struct _ICMP_TIME_EXCEEDED_HEADER {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT32  Unused;
  UINT8   OrigVerIhl;
  UINT8   OrigTos;
  UINT16  OrigLen;
  UINT16  OrigId;
  UINT16  OrigFrag;
  UINT8   OrigTtl;
  UINT8   OrigProt;
  UINT16  OrigCheck;
  UINT32  OrigSrc;
  UINT32  OrigDst;
} ICMP_TIME_EXCEEDED_HEADER;

typedef struct _icmp_timestamp_header {
  UINT8   Type;
  UINT8   Code;
  UINT16  ChhkSum;
  UINT16  Id;
  UINT16  Seq;
  n_time  OTime;
  n_time  RTime;
  n_time  TTime;
} ICMP_TIMESTAMP_HEADER;

#endif
