/** @file

  Copyright 2006 - 2026 Unified EFI, Inc.<BR>
  Copyright (c) 2026, AMD Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
/*++

Module Name:

  RestEx.h

Abstract:

  EFI REST EX Protocol from the UEFI 2.8 specification.

--*/

#ifndef _REST_EX_PROTOCOL_H_
#define _REST_EX_PROTOCOL_H_

#include <Protocol/Http.h>

#define EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID \
  { \
    0x456bbe01, 0x99d0, 0x45ea, {0xbb, 0x5f, 0x16, 0xd8, 0x4b, 0xed, 0xc5, 0x59 } \
  }

#define EFI_REST_EX_PROTOCOL_GUID \
  { \
    0x55648b91, 0xe7d, 0x40a3, {0xa9, 0xb3, 0xa8, 0x15, 0xd7, 0xea, 0xdf, 0x97 } \
  }

typedef struct _EFI_REST_EX_PROTOCOL EFI_REST_EX_PROTOCOL;

typedef struct {
  UINT8    Major;
  UINT8    Minor;
} EFI_REST_EX_SERVICE_INFO_VER;

typedef struct {
  UINT32                          Length;
  EFI_REST_EX_SERVICE_INFO_VER    RestServiceInfoVer;
} EFI_REST_EX_SERVICE_INFO_HEADER;

typedef enum {
  EfiRestExServiceUnspecific = 1,
  EfiRestExServiceRedfish,
  EfiRestExServiceOdata,
  EfiRestExServiceVendorSpecific = 0xff,
  EfiRestExServiceTypeMax
} EFI_REST_EX_SERVICE_TYPE;

typedef enum {
  EfiRestExServiceInBandAccess    = 1,
  EfiRestExServiceOutOfBandAccess = 2,
  EfiRestExServiceModeMax
} EFI_REST_EX_SERVICE_ACCESS_MODE;

typedef enum {
  EfiRestExConfigHttp,
  EfiRestExConfigUnspecific,
  EfiRestExConfigTypeMax
} EFI_REST_EX_CONFIG_TYPE;

typedef struct {
  EFI_REST_EX_SERVICE_INFO_HEADER    EfiRestExServiceInfoHeader;
  EFI_REST_EX_SERVICE_TYPE           RestServiceType;
  EFI_REST_EX_SERVICE_ACCESS_MODE    RestServiceAccessMode;
  EFI_GUID                           VendorRestServiceName;
  UINT32                             VendorSpecificDataLength;
  UINT8                              *VendorSpecifcData;
  EFI_REST_EX_CONFIG_TYPE            RestExConfigType;
  UINT8                              RestExConfigDataLength;
} EFI_REST_EX_SERVICE_INFO_V_1_0;

typedef union {
  EFI_REST_EX_SERVICE_INFO_HEADER    EfiRestExServiceInfoHeader;
  EFI_REST_EX_SERVICE_INFO_V_1_0     EfiRestExServiceInfoV10;
} EFI_REST_EX_SERVICE_INFO;

typedef struct {
  EFI_HTTP_CONFIG_DATA    HttpConfigData;
  UINT32                  SendReceiveTimeout;
} EFI_REST_EX_HTTP_CONFIG_DATA;

typedef UINT8 *EFI_REST_EX_CONFIG_DATA;

typedef struct {
  EFI_EVENT           Event;
  EFI_STATUS          Status;
  EFI_HTTP_MESSAGE    *ResponseMessage;
} EFI_REST_EX_TOKEN;

typedef
EFI_STATUS
(EFIAPI *EFI_REST_SEND_RECEIVE)(
  IN      EFI_REST_EX_PROTOCOL   *This,
  IN      EFI_HTTP_MESSAGE       *RequestMessage,
  OUT     EFI_HTTP_MESSAGE       *ResponseMessage
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_GET_TIME)(
  IN      EFI_REST_EX_PROTOCOL   *This,
  OUT     EFI_TIME               *Time
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_EX_GET_SERVICE)(
  IN   EFI_REST_EX_PROTOCOL      *This,
  OUT  EFI_REST_EX_SERVICE_INFO  **RestExServiceInfo
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_EX_GET_MODE_DATA)(
  IN  EFI_REST_EX_PROTOCOL    *This,
  OUT EFI_REST_EX_CONFIG_DATA *RestExConfigData
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_EX_CONFIGURE)(
  IN  EFI_REST_EX_PROTOCOL    *This,
  IN  EFI_REST_EX_CONFIG_DATA RestExConfigData
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_EX_ASYNC_SEND_RECEIVE)(
  IN      EFI_REST_EX_PROTOCOL   *This,
  IN      EFI_HTTP_MESSAGE       *RequestMessage OPTIONAL,
  IN      EFI_REST_EX_TOKEN      *RestExToken,
  IN      UINTN                  *TimeOutInMilliSeconds OPTIONAL
  );

typedef
EFI_STATUS
(EFIAPI *EFI_REST_EX_EVENT_SERVICE)(
  IN      EFI_REST_EX_PROTOCOL   *This,
  IN      EFI_HTTP_MESSAGE       *RequestMessage OPTIONAL,
  IN      EFI_REST_EX_TOKEN      *RestExToken
  );

struct _EFI_REST_EX_PROTOCOL {
  EFI_REST_SEND_RECEIVE             SendReceive;
  EFI_REST_GET_TIME                 GetServiceTime;
  EFI_REST_EX_GET_SERVICE           GetService;
  EFI_REST_EX_GET_MODE_DATA         GetModeData;
  EFI_REST_EX_CONFIGURE             Configure;
  EFI_REST_EX_ASYNC_SEND_RECEIVE    AyncSendReceive;
  EFI_REST_EX_EVENT_SERVICE         EventService;
};

extern EFI_GUID  gEfiRestExServiceBindingProtocolGuid;
extern EFI_GUID  gEfiRestExProtocolGuid;

#endif
