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
if {[info exist TCP6_PROC_TCL] == 1} {
  return
}
set TCP6_PROC_TCL 1

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
  puts TCPEUTSetup
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
  SetIpv6Address R_Proc_Ip6ConfigData.StationAddress         "::"
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

# Procedure Name
#   Hex2Dec
# Procedure Description:
#   Translate Hex Strings (0x.. 0x..) to Dec format
# Arguments:
#   L_Proc_Hex
# Returns:
#   Dec format of L_Proc_Hex
#
proc Hex2Dec { L_Proc_Hex } {
  set L_Proc_Sum 0
  set L_Proc_Shift [expr {[llength $L_Proc_Hex]-1}]
  for {set i 0} { $i < [ llength $L_Proc_Hex] } { incr i } {
    set L_Proc_Temp1 [lindex $L_Proc_Hex $i]
    set L_Proc_Temp2 [expr {8*($L_Proc_Shift-$i)}]
    set L_Proc_Sum [expr {$L_Proc_Sum+[expr {$L_Proc_Temp1<<$L_Proc_Temp2}]}]
  }
  return $L_Proc_Sum
}


