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
if {[info exist UDP6_PROC_TCL] == 1} {
  return
}
set UDP6_PROC_TCL 1

# Procedure Name
#   EUTSetup
# Procedure Description:
#   Add Entry for Remote Address in Neighbour Cache
# Arguments:
#   Nothing.
# Returns:
#   Nothing.
#
proc EUTSetup { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR

  BeginScope _PROC_EUT_SETUP_
  puts UDP6EUTSetup
  #
  # Parameter Defination 0: Common
  #
  UINTN          R_Proc_Ip6Status
  
  #
  # Parameter Defination 1: Configuration
  #
  EFI_IP6_CONFIG_DATA       R_Proc_Ip6ConfigData
  
  #
  # Parameter Defination 2: Neighbour
  #
  EFI_IPv6_ADDRESS          R_Proc_RemoteAddress
  EFI_MAC_ADDRESS           R_Proc_RemoteMAC
  BOOLEAN                   R_Proc_DeleteFlag
  UINT32                    R_Proc_TimeOut
  BOOLEAN                   R_Proc_Override     
  UINTN                     R_Proc_Ip6Handle

  #
  # Parameter Defination 3: Address Configuration
  #
  UINTN                                       R_Proc_Ip6ConfigDataSize
  UINT32                                      R_Proc_Ip6ConfigDataType
  UINT32                                      R_Proc_Ip6ConfigPolicy
  EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS    R_Proc_Ip6ConfigDadTransmits
  EFI_IP6_CONFIG_MANUAL_ADDRESS               R_Proc_Ip6ConfigManualAddress
  
  #
  # Create Ipv6 child controller
  #
  Ip6ServiceBinding->CreateChild "&@R_Proc_Ip6Handle, &@R_Proc_Ip6Status"
  GetAck
  SetVar     [subst $ENTS_CUR_CHILD]  @R_Proc_Ip6Handle

  #
  # Address Configuration
  #
  SetVar R_Proc_Ip6ConfigDataType   2
  SetVar R_Proc_Ip6ConfigDataSize   4
  SetVar R_Proc_Ip6ConfigPolicy     0
  
  Ip6Config->SetData "@R_Proc_Ip6ConfigDataType,@R_Proc_Ip6ConfigDataSize,&@R_Proc_Ip6ConfigPolicy,&@R_Proc_Ip6Status"
  GetAck
  
  SetVar R_Proc_Ip6ConfigDataType   3
  SetVar R_Proc_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_DUP_ADDR_DETECT_TRANSMITS]
  SetVar R_Proc_Ip6ConfigDadTransmits.DupAddrDetectTransmits 0
  
  Ip6Config->SetData "@R_Proc_Ip6ConfigDataType,@R_Proc_Ip6ConfigDataSize,&@R_Proc_Ip6ConfigDadTransmits,&@R_Proc_Ip6Status"
  GetAck
  
  SetVar R_Proc_Ip6ConfigDataType   4
  SetVar R_Proc_Ip6ConfigDataSize   [Sizeof EFI_IP6_CONFIG_MANUAL_ADDRESS]
  SetVar R_Proc_Ip6ConfigManualAddress.IsAnycast    FALSE
  SetVar R_Proc_Ip6ConfigManualAddress.PrefixLength 64
  SetIpv6Address R_Proc_Ip6ConfigManualAddress.Address $DEF_EUT_IP_ADDR
  
  Ip6Config->SetData "@R_Proc_Ip6ConfigDataType,@R_Proc_Ip6ConfigDataSize,&@R_Proc_Ip6ConfigManualAddress,&@R_Proc_Ip6Status"
  GetAck
  
  #
  # Configurate Ipv6 child controller : Caution, only for trigger the setting of 
  #                                                    the instance, all the parameters are invalid
  #                                                    and would be flushed by TCP6 transmittion
  SetVar R_Proc_Ip6ConfigData.DefaultProtocol                0x11;        
  SetVar R_Proc_Ip6ConfigData.AcceptAnyProtocol              FALSE
  SetVar R_Proc_Ip6ConfigData.AcceptIcmpErrors               TRUE
  SetVar R_Proc_Ip6ConfigData.AcceptPromiscuous              TRUE
  SetIpv6Address R_Proc_Ip6ConfigData.DestinationAddress     "::"
  SetIpv6Address R_Proc_Ip6ConfigData.StationAddress         $DEF_EUT_IP_ADDR
  SetVar R_Proc_Ip6ConfigData.TrafficClass                   0
  SetVar R_Proc_Ip6ConfigData.HopLimit                       128
  SetVar R_Proc_Ip6ConfigData.FlowLabel                      0
  SetVar R_Proc_Ip6ConfigData.ReceiveTimeout                 50000
  SetVar R_Proc_Ip6ConfigData.TransmitTimeout                50000

  Ip6->Configure "&@R_Proc_Ip6ConfigData, &@R_Proc_Ip6Status"
  GetAck
  
  #
  # Add Entry for Remote Address in Neighbour Cache
  #
  SetIpv6Address   R_Proc_RemoteAddress      $DEF_ENTS_IP_ADDR
  SetEthMacAddress R_Proc_RemoteMAC          $DEF_ENTS_MAC_ADDR
  SetVar R_Proc_DeleteFlag    FALSE
  SetVar R_Proc_TimeOut       0
  SetVar R_Proc_Override      TRUE

  Ip6->Neighbors "@R_Proc_DeleteFlag, &@R_Proc_RemoteAddress, &@R_Proc_RemoteMAC, @R_Proc_TimeOut, @R_Proc_Override, &@R_Proc_Ip6Status"
  GetAck
  
}


# Procedure Name
#   EUTClose
# Procedure Description:
#   Delete Entry for Remote Address in Neighbour Cache
# Arguments:
#   Nothing.
# Returns:
#   Nothing.
#
proc EUTClose { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR

  SetVar [subst $ENTS_CUR_CHILD]  @R_Proc_Ip6Handle

  #
  # Delete Entry for Remote Address from Neighbour Cache
  #
  SetVar R_Proc_DeleteFlag TRUE
  Ip6->Neighbors "@R_Proc_DeleteFlag, &@R_Proc_RemoteAddress, &@R_Proc_RemoteMAC, @R_Proc_TimeOut, @R_Proc_Override, &@R_Proc_Ip6Status"
  GetAck

  Ip6ServiceBinding->DestroyChild "@R_Proc_Ip6Handle, &@R_Proc_Ip6Status"
  GetAck
  
  EndScope _PROC_EUT_SETUP_
}

# Procedure Name
#   EUTEndSession
# Procedure Description:
#   EUT Closes the TCP link initiatively
# Arguments:
#   Nothing.
# Returns:
#   Nothing.
# Caution:
#   $ENTS_CUR_CHILD should be the current effective TCP6 child
#
proc EUTEndSession { } {
  global EFI_INCOMPATIBLE_VERSION EVT_NOTIFY_SIGNAL EFI_TPL_CALLBACK
  
  EFI_TCP6_CLOSE_TOKEN             R_Proc_Close_CloseToken
  EFI_TCP6_COMPLETION_TOKEN        R_Proc_Close_CompletionToken
  UINTN                            R_Proc_Context
  UINTN                            R_Proc_Status
  
  BS->CreateEvent "$EVT_NOTIFY_SIGNAL, $EFI_TPL_CALLBACK, 1, &@R_Proc_Context,        \
                   &@R_Proc_Close_CompletionToken.Event, &@R_Proc_Status"
  GetAck
  
  SetVar R_Proc_Close_CompletionToken.Status    $EFI_INCOMPATIBLE_VERSION
  SetVar R_Proc_Close_CloseToken.CompletionToken @R_Proc_Close_CompletionToken
  SetVar R_Proc_Close_CloseToken.AbortOnClose   TRUE
  SetVar R_Proc_Context 0
  
  Tcp6->Close {&@R_Proc_Close_CloseToken, &@R_Proc_Status}
  GetAck
  BS->CloseEvent {@R_Proc_Close_CompletionToken.Event, &@R_Proc_Status}
  GetAck
}
