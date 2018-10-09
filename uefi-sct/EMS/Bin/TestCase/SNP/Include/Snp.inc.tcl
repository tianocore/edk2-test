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
if {[info exist SIMPLE_NETWORK_INC] == 1} {
  return
}

Include include/EntsProtocolTest.inc.tcl
Include EfiUtil/EFI_inc.tcl

set SIMPLE_NETWORK_INC 1

Func SimpleNetwork->Start {
  POINTER
  }

Func SimpleNetwork->Stop {
  POINTER
  }

Func SimpleNetwork->Initialize {
  UINTN
  UINTN
  POINTER
  }

Func SimpleNetwork->Reset {
  BOOLEAN
  POINTER
  }

Func SimpleNetwork->Shutdown {
  POINTER
  }

Func SimpleNetwork->ReceiveFilters {
  UINT32
  UINT32
  BOOLEAN
  UINTN
  POINTER
  POINTER
  }

Func SimpleNetwork->StationAddress {
  BOOLEAN
  POINTER
  POINTER
  }

Func SimpleNetwork->Statistics {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->MCastIPtoMAC {
  BOOLEAN
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->NvData {
  BOOLEAN
  UINTN
  UINTN
  POINTER
  POINTER
  }

Func SimpleNetwork->GetStatus {
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->TransmitPattern1 {
  UINTN
  UINTN
  UINTN
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }


Func SimpleNetwork->TransmitPattern2 {
  UINTN
  UINTN
  UINTN
  UINTN
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->Transmit {
  UINTN
  UINTN
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->ReceivePattern1 {
  UINTN
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->Receive {
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  POINTER
  }

Func SimpleNetwork->Mode {
  POINTER
}
Struct EFI_IPv4_ADDRESS {
  UINT8  Addr(4);
}

Struct EFI_IPv6_ADDRESS {
  UINT8  Addr(16);
}

Union EFI_IP_ADDRESS {
  UINT32           Addr(4);
  EFI_IPv4_ADDRESS v4;
  EFI_IPv6_ADDRESS v6;
}

Struct EFI_MAC_ADDRESS {
  UINT8  Addr(32);
}

Struct EFI_NETWORK_STATISTICS {
  UINT64 RxTotalFrames;
  UINT64 RxGoodFrames;
  UINT64 RxUndersizeFrames;
  UINT64 RxOversizeFrames;
  UINT64 RxDroppedFrames;
  UINT64 RxUnicastFrames;
  UINT64 RxBroadcastFrames;
  UINT64 RxMulticastFrames;
  UINT64 RxCrcErrorFrames;
  UINT64 RxTotalBytes;
  UINT64 TxTotalFrames;
  UINT64 TxGoodFrames;
  UINT64 TxUndersizeFrames;
  UINT64 TxOversizeFrames;
  UINT64 TxDroppedFrames;
  UINT64 TxUnicastFrames;
  UINT64 TxBroadcastFrames;
  UINT64 TxMulticastFrames;
  UINT64 TxCrcErrorFrames;
  UINT64 TxTotalBytes;
  UINT64 Collisions;
  UINT64 UnsupportedProtocol;
}

Struct EFI_SIMPLE_NETWORK_MODE {
  UINT32          State;
  UINT32          HwAddressSize;
  UINT32          MediaHeaderSize;
  UINT32          MaxPacketSize;
  UINT32          NvRamSize;
  UINT32          NvRamAccessSize;
  UINT32          ReceiveFilterMask;
  UINT32          ReceiveFilterSetting;
  UINT32          MaxMCastFilterCount;
  UINT32          MCastFilterCount;
  EFI_MAC_ADDRESS MCastFilter(16);
  EFI_MAC_ADDRESS CurrentAddress;
  EFI_MAC_ADDRESS BroadcastAddress;
  EFI_MAC_ADDRESS PermanentAddress;
  UINT8           IfType;
  BOOLEAN         MacAddressChangeable;
  BOOLEAN         MultipleTxSupported;
  BOOLEAN         MediaPresentSupported;
  BOOLEAN         MediaPresent;
}
