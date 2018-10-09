# 
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
# 
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
if {[info exist DHCP4_INC] == 1} {
  return
}

set DHCP4_INC 1

Include Include/EntsProtocolTest.inc.tcl
Include Include/EntsConfigure.tcl
Include Include/EfiBootService.inc.tcl
Include Include/EfiGenericService.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include DHCP4/Include/Dhcp4.proc.tcl
Include DHCP4/Include/Dhcp4AssertionGuid.tcl
Include Include/GenericAssertionGuid.tcl

###################################################################
# Function Declaration
###################################################################
Func Dhcp4ServiceBinding->CreateChild {
  POINTER
  POINTER
}

Func Dhcp4ServiceBinding->DestroyChild {
  UINTN
  POINTER
}

Func Dhcp4->GetModeData {
  POINTER
  POINTER
}

Func Dhcp4->Configure {
  POINTER
  POINTER
}

Func Dhcp4->Start {
  UINTN
  POINTER
}

Func Dhcp4->RenewRebind {
  BOOLEAN
  UINTN
  POINTER
}

Func Dhcp4->Release {
  POINTER
}

Func Dhcp4->Stop {
  POINTER
}

Func Dhcp4->Build {
  POINTER
  UINT32
  POINTER
  UINT32
  POINTER
  POINTER
  POINTER
}

Func Dhcp4->TransmitReceive {
  POINTER
  POINTER
}

Func Dhcp4->Parse {
  POINTER
  POINTER
  POINTER
  POINTER
}

###################################################################
# DHCP4 Packet Option
###################################################################
Pack	1
Struct EFI_DHCP4_PACKET_OPTION {
  UINT8       OpCode;
  UINT8       Length;
  UINT8       Data(30);
};
Pack

###################################################################
# DHCP4 Header Data Structure
###################################################################
Pack	1
Struct EFI_DHCP4_HEADER {
    UINT8             OpCode;
    UINT8             HwType;
    UINT8             HwAddrLen;
    UINT8             Hops;
    UINT32            Xid;
    UINT16            Seconds;
    UINT16            Reserved;
    EFI_IPv4_ADDRESS  ClientAddr; 
    EFI_IPv4_ADDRESS  YourAddr;   
    EFI_IPv4_ADDRESS  ServerAddr;  
    EFI_IPv4_ADDRESS  GwAddr;     
    UINT8             ClientHwAddr(16); 
    CHAR8             ServerName(64);   
    CHAR8             BootFileName(128);
};
Pack

###################################################################
# DHCP4 Packet Data Structure
###################################################################
Pack 1
Struct EFI_RAW_DHCP4_PACKET {
  EFI_DHCP4_HEADER    Header;
  UINT32              Magik;
  UINT8               Option(312);
};
Struct EFI_DHCP4_PACKET {
  UINT32                Size;
  UINT32                Length;
  EFI_RAW_DHCP4_PACKET  Dhcp4;
};
Pack

###################################################################
# EFI_DHCP4_STATE
###################################################################
set Dhcp4Stopped 	      0;
set Dhcp4Init     	    1;
set Dhcp4Selecting 	    2;
set Dhcp4Requesting 	  3;
set Dhcp4Bound 		      4;
set Dhcp4Renewing 	    5;
set Dhcp4Rebinding 	    6;
set Dhcp4InitReboot 	  7;
set Dhcp4Rebooting 	    8;

###################################################################
# EFI_DHCP4_EVENT
###################################################################
set  Dhcp4SendDiscover    1;
set  Dhcp4RcvdOffer       2;
set  Dhcp4SelectOffer     3;
set  Dhcp4SendRequest  	  5;
set  Dhcp4RcvdAck	        6;
set  Dhcp4RcvdNak	        7;
set  Dhcp4SendDecline	    8;
set  Dhcp4BoundCompleted  9;
set  Dhcp4EnterRenewing	  0x0a;
set  Dhcp4EnterRebinding  0x0b;
set  Dhcp4AddressLost	    0x0c;
set  Dhcp4Fail            0x0d;

###################################################################
# EFI_DHCP4_CONFIG_DATA
###################################################################
Struct EFI_DHCP4_CONFIG_DATA {
  UINT32                DiscoverTryCount;
  POINTER               DiscoverTimeout;
  UINT32                RequestTryCount;
  POINTER               RequestTimeout;
  EFI_IPv4_ADDRESS      ClientAddress;
  POINTER               Dhcp4Callback;
  POINTER               CallbackContext;
  UINT32                OptionCount;
  POINTER               OptionList;
};

###################################################################
# EFI_DHCP4_MODE_DATA   
###################################################################
Struct EFI_DHCP4_MODE_DATA {
  UINTN                	              State;
  EFI_DHCP4_CONFIG_DATA 	            ConfigData;
  EFI_IPv4_ADDRESS    	              ClientAddress;
  EFI_MAC_ADDRESS     	              ClientMacAddress;
  EFI_IPv4_ADDRESS             	      ServerAddress;
  EFI_IPv4_ADDRESS    	              RouterAddress;
  EFI_IPv4_ADDRESS    		            SubnetMask;
  UINT32                              LeaseTime;
  POINTER                             ReplyPacket;
}

###################################################################
# EFI_DHCP4_LISTEN_POINT                                                     
###################################################################
Struct EFI_DHCP4_LISTEN_POINT {
  EFI_IPv4_ADDRESS           ListenAddress;
  EFI_IPv4_ADDRESS           SubnetMask;
  UINT16                     ListenPort;
};

###################################################################
# EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN                                           
###################################################################
Struct EFI_DHCP4_TRANSMIT_RECEIVE_TOKEN {
  UINTN                  Status;
  UINTN                  CompletionEvent;
  EFI_IPv4_ADDRESS       RemoteAddress;
  UINT16                 RemotePort;
  EFI_IPv4_ADDRESS       GatewayAddress;
  UINT32                 ListenPointCount;
  POINTER                ListenPoints;
  UINT32                 TimeoutValue;
  POINTER                Packet;
  UINT32                 ResponseCount;
  POINTER                ResponseList;   
}