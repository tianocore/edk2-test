#
# The material contained herein is not a license, either      
# expressly or impliedly, to any intellectual property owned  
# or controlled by any of the authors or developers of this   
# material or to any contribution thereto. The material       
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and  
# developers of this material hereby disclaim all other       
# warranties and conditions, either express, implied or       
# statutory, including, but not limited to, any (if any)      
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or         
# completeness of responses, of results, of workmanlike       
# effort, of lack of viruses and of lack of negligence, all   
# with regard to this material and any contribution thereto.  
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or           
# "undefined." The Unified EFI Forum, Inc. reserves any       
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or    
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
# CONTRIBUTION THERETO.                                       
#                                                             
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
# THE POSSIBILITY OF SUCH DAMAGES.                            
#                                                             
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
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
