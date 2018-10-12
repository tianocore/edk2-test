# 
#  Copyright (c) 2018, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist HTTP_INC] == 1} {
  return
}
set HTTP_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include Http/Include/HttpAssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl



Func HttpServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func HttpServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Http->GetModeData {
  POINTER
  POINTER
}

Func Http->Configure {
  POINTER 
  POINTER
}

Func Http->Request {
  POINTER
  POINTER
}

Func Http->Cancel {
  POINTER
  POINTER
}

Func Http->Response {
  POINTER
  POINTER
}
Func Http->Poll {
  POINTER
}



###################################################################
# EFI_HTTPv4_ACCESS_POINT
###################################################################
Struct EFI_HTTPv4_ACCESS_POINT {
  BOOLEAN                       UseDefaultAddress;
  EFI_IPv4_ADDRESS              LocalAddress;
  EFI_IPv4_ADDRESS              LocalSubnet;
  UINT16                        LocalPort;
}

###################################################################
# EFI_HTTPv6_ACCESS_POINT
###################################################################
Struct EFI_HTTPv6_ACCESS_POINT {
   EFI_IPv6_ADDRESS              LocalAddress;
   UINT16                        LocalPort;
}

 set  HTTP_STATUS_UNSUPPORTED_STATUS  0;
 set  HTTP_STATUS_100_CONTINUE 1;
 set  HTTP_STATUS_101_SWITCHING_PROTOCOLS 2;
 set  HTTP_STATUS_200_OK 3;
 set  HTTP_STATUS_201_CREATED 4;
 set  HTTP_STATUS_202_ACCEPTED 5;
 set  HTTP_STATUS_203_NON_AUTHORITATIVE_INFORMATION 6;
 set  HTTP_STATUS_204_NO_CONTENT 7;
 set  HTTP_STATUS_205_RESET_CONTENT 8;
 set  HTTP_STATUS_206_PARTIAL_CONTENT 9;
 set  HTTP_STATUS_300_MULTIPLE_CHIOCES 10;
 set  HTTP_STATUS_301_MOVED_PERMANENTLY 11;
 set  HTTP_STATUS_302_FOUND 12;
 set  HTTP_STATUS_303_SEE_OTHER 13;
 set  HTTP_STATUS_304_NOT_MODIFIED 14;
 set  HTTP_STATUS_305_USE_PROXY 15;
 set  HTTP_STATUS_307_TEMPORARY_REDIRECT 16;
 set  HTTP_STATUS_400_BAD_REQUEST 17;
 set  HTTP_STATUS_401_UNAUTHORIZED 18;
 set  HTTP_STATUS_402_PAYMENT_REQUIRED 19;
 set  HTTP_STATUS_403_FORBIDDEN 20;
 set  HTTP_STATUS_404_NOT_FOUND 21;
 set  HTTP_STATUS_405_METHOD_NOT_ALLOWED 22;
 set  HTTP_STATUS_406_NOT_ACCEPTABLE 23;
 set  HTTP_STATUS_407_PROXY_AUTHENTICATION_REQUIRED 24;
 set  HTTP_STATUS_408_REQUEST_TIME_OUT 25;
 set  HTTP_STATUS_409_CONFLICT 26;
 set  HTTP_STATUS_410_GONE 27;
 set  HTTP_STATUS_411_LENGTH_REQUIRED 28;
 set  HTTP_STATUS_412_PRECONDITION_FAILED 29;
 set  HTTP_STATUS_413_REQUEST_ENTITY_TOO_LARGE 30;
 set  HTTP_STATUS_414_REQUEST_URI_TOO_LARGE 31;
 set  HTTP_STATUS_415_UNSUPPORETD_MEDIA_TYPE 32;
 set  HTTP_STATUS_416_REQUESTED_RANGE_NOT_SATISFIED 33;
 set  HTTP_STATUS_417_EXPECTATION_FAILED 34;
 set  HTTP_STATUS_500_INTERNAL_SERVER_ERROR 35;
 set  HTTP_STATUS_501_NOT_IMIPLEMENTED 36;
 set  HTTP_STATUS_502_BAD_GATEWAY 37;
 set  HTTP_STATUS_503_SERVICE_UNAVAILABLE 38;
 set  HTTP_STATUS_504_GATEWAY_TIME_OUT 39;
 set  HTTP_STATUS_505_HTTP_VERSION_NOT_SUPPORTED 40;
 
 set  HttpVersion10 0;
 set  HttpVersion11 1;
 set  HttpVersionUnsupported 2;
 
 set  HttpMethodGet 0;
 set  HttpMethodPost 1;
 set  HttpMethodPatch 2;
 set  HttpMethodOptions 3;
 set  HttpMethodConnect 4;
 set  HttpMethodHead 5;
 set  HttpMethodPut 6;
 set  HttpMethodDelete 7;
 set  HttpMethodTrace 8;
 

####################################################################
# EFI_HTTP_RESPONSE_DATA
#####################################################################
Struct EFI_HTTP_RESPONSE_DATA {
  UINT32        StatusCode;
}

###################################################################
# EFI_HTTP_CONFIG_DATA
###################################################################
Union EFI_HTTP_CONFIG_DATA_ACCESSPOINT {
  POINTER        IPv4Node;
  POINTER        IPv6Node;
}

Struct EFI_HTTP_CONFIG_DATA {
  UINT32                              HttpVersion;
  UINT32                              TimeOutMillisec;
  BOOLEAN                             LocalAddressIsIPv6;
  EFI_HTTP_CONFIG_DATA_ACCESSPOINT    AccessPoint;
}

####################################################################
# EFI_HTTP_REQUEST_DATA
#####################################################################
Struct EFI_HTTP_REQUEST_DATA {
  UINT32         Method;
  POINTER        Url;
}
 
####################################################################
# EFI_HTTP_HEADER
#####################################################################
Struct EFI_HTTP_HEADER {
  POINTER        FieldName;
  POINTER        FieldValue;
}

###################################################################
# EFI_HTTP_MESSAGE
###################################################################
Union EFI_HTTP_MESSAGE_DATA {
  POINTER        Request;
  POINTER        Response;
};
Struct EFI_HTTP_MESSAGE {
  EFI_HTTP_MESSAGE_DATA        Data;
  UINTN                        HeaderCount;
  POINTER                      Headers;
  UINTN                        BodyLength;
  POINTER                      Body;
}
 
###################################################################
# EFI_HTTP_TOKEN
###################################################################
Struct EFI_HTTP_TOKEN {
  UINTN          Event;
  UINTN          Status;
  POINTER        Message;
}
