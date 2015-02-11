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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
if {[info exist MTFTP6_PROC_TCL] == 1} {
  return
}
set MTFTP6_PROC_TCL 1

# Procedure Name
#   Mtftp6CreateOack
# Procedure Description:
#   Mtftp6CreateOack a MTFTPv6 OACK packet.
# Arguments:
#   dest_port
#   opcode
# Returns:
#   The OACK packet.
#
proc Mtftp6CreateOack { {dest_port $DEF_DEST_PRT} 
                           {opcode $EFI_MTFTP6_OPCODE_OACK}} {
  global option_value_array option_value_len DEF_SRC_PRT EFI_MTFTP6_OPCODE_OACK
  set opt_count 0

  CreatePayload inteval_1 Const  1 0x00
  set multi_flag   0
  set timeout_flag 0
  
  if {[info exists option_value_array(multicast)] == 1 } {
    set multi_flag 1
    CreatePayload option_multi string 9 multicast
    CreatePayload value_multi string $option_value_len(multicast)              \
                              $option_value_array(multicast)
    ConcatPayload MultiOpt option_multi inteval_1 value_multi
    unset option_value_array(multicast)
  }
  
  if {[info exists option_value_array(timeout)] == 1 } {
    set timeout_flag 1
    CreatePayload option_timeout string 7 timeout
    CreatePayload value_timeout string $option_value_len(timeout)              \
                             $option_value_array(timeout)
    ConcatPayload TimeoutOpt option_timeout inteval_1 value_timeout
    unset option_value_array(timeout)
  }

  if { $multi_flag == 1 && $timeout_flag == 1 } {
    ConcatPayload option_pld MultiOpt inteval_1 TimeoutOpt
  } elseif { $multi_flag == 1 && $timeout_flag == 0 } {
    ConcatPayload option_pld MultiOpt
  } elseif { $multi_flag == 0 && $timeout_flag == 1 } {
    ConcatPayload option_pld TimeoutOpt
  }
  
  #
  # Parse the option_value_array
  #
  if { [info exists option_value_array(tsize)] == 1 } {
    set  OptionList(0)      "tsize"
    set  OptionLenList(0)   5
    set  OptionValueList(0) $option_value_array(tsize)
    set  ValueLenList(0)    $option_value_len(tsize)
    incr opt_count
    CreatePayload _Option string $OptionLenList(0) $OptionList(0)
    CreatePayload _Value  string $ValueLenList(0) $OptionValueList(0)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value
    unset option_value_array(tsize)
  }
  if { [info exists option_value_array(blksize)] == 1 } {
    set  OptionList(1)      "blksize"
    set  OptionLenList(1)   7
    set  OptionValueList(1) $option_value_array(blksize)
    set  ValueLenList(1)    $option_value_len(blksize)
    CreatePayload _Option string $OptionLenList(1) $OptionList(1)
    CreatePayload _Value  string $ValueLenList(1) $OptionValueList(1)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value
    unset option_value_array(blksize)
  }
  if { [info exists option_value_array(bigblk#)] == 1 } {
    set  OptionList(2)      "bigblk#"
    set  OptionLenList(2)   7
    set  OptionValueList(2) $option_value_array(bigblk#)
    set  ValueLenList(2)    $option_value_len(bigblk#)
    CreatePayload _Option string $OptionLenList(2) $OptionList(2)
    CreatePayload _Value  string $ValueLenList(2) $OptionValueList(2)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value
    unset option_value_array(bigblk#)
  }
  if { [info exists option_value_array(stream)] == 1 } {
    set  OptionList(3)      "stream"
    set  OptionLenList(3)   6
    set  OptionValueList(3) $option_value_array(stream)
    set  ValueLenList(3)    $option_value_len(stream)
    CreatePayload _Option string $OptionLenList(3) $OptionList(3)
    CreatePayload _Value  string $ValueLenList(3) $OptionValueList(3)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value
    unset option_value_array(stream)
  }
  if { [info exists option_value_array(pktdelay)] == 1 } {
    set  OptionList(4)      "pktdelay"
    set  OptionLenList(4)   8
    set  OptionValueList(4) $option_value_array(pktdelay)
    set  ValueLenList(4)    $option_value_len(pktdelay)
    CreatePayload _Option string $OptionLenList(4) $OptionList(4)
    CreatePayload _Value  string $ValueLenList(4) $OptionValueList(4)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value 
    unset option_value_array(pktdelay)
  }
  if { [info exists option_value_array(session)] == 1 } {
    set  OptionList(5)      "session"
    set  OptionLenList(5)   7
    set  OptionValueList(5) $option_value_array(session)
    set  ValueLenList(5)    $option_value_len(session)
    CreatePayload _Option string $OptionLenList(5) $OptionList(5)
    CreatePayload _Value  string $ValueLenList(5) $OptionValueList(5)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value 
    unset option_value_array(session)
  }
  if { [info exists option_value_array(restart)] == 1 } {
    set  OptionList(6)      "restart"
    set  OptionLenList(6)   7
    set  OptionValueList(6) $option_value_array(restart)
    set  ValueLenList(6)    $option_value_len(restart)
    CreatePayload _Option string $OptionLenList(6) $OptionList(6)
    CreatePayload _Value  string $ValueLenList(6) $OptionValueList(6)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value  
    unset option_value_array(restart)
  }
  if { [info exists option_value_array(unknown)] == 1 } {
    set  OptionList(7)      "unknown"
    set  OptionLenList(7)   7
    set  OptionValueList(7) $option_value_array(unknown)
    set  ValueLenList(7)    $option_value_len(unknown)
    CreatePayload _Option string $OptionLenList(7) $OptionList(7)
    CreatePayload _Value  string $ValueLenList(7) $OptionValueList(7)
    ConcatPayload option_pld option_pld inteval_1 _Option inteval_1 _Value  
    unset option_value_array(unknown)
  }

  CreatePayload EndOfPacket const 1 0x00
  CreatePayload OpCode Data 2 0x00 $opcode
  ConcatPayload mtftp_oack_pld OpCode option_pld EndOfPacket
  CreatePacket  mtftp6_oack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port -Udp_len 33 \
                   -udp_payload mtftp_oack_pld -IP_ver 6

  return mtftp6_oack
}

# Procedure Name
#   Mtftp6CreateAck
# Procedure Description:
#   Mtftp6CreateAck create a MTFTPv6 ACK packet.
# Arguments:
#   dest_port
#   blk_number
# Returns:
#   The ACK packet.
#
proc Mtftp6CreateAck { {dest_port $DEF_DEST_PRT} {blk_number}} {
  global DEF_SRC_PRT EFI_MTFTP6_OPCODE_ACK

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP6_OPCODE_ACK
  CreatePayload _blk_number Data 2 0x00 $blk_number
  ConcatPayload mtftp6_ack_pld OpCode _blk_number
  CreatePacket  mtftp6_ack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port      \
                -udp_payload mtftp6_ack_pld -IP_ver 6
  return mtftp6_ack
}

# Procedure Name
#   Mtftp6CreateError
# Procedure Description:
#   GMtftp6Create a MTFTPv6 ERROR packet.
# Arguments:
#   dest_port
#   ErrorCodes
#   ErrorMsg
# Returns:
#   The error packet.
#
proc Mtftp6CreateError { {dest_port $DEF_DEST_PRT} 
                         {ErrorCodes $EFI_MTFTP6_ERRORCODE_NOT_DEFINED} 
                         {ErrorMsg "Not defined ErrorType"} } {
  global EFI_MTFTP6_OPCODE_ERROR DEF_DEST_PRT EFI_MTFTP6_ERRORCODE_NOT_DEFINED 
  global DEF_SRC_PRT

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP6_OPCODE_ERROR
  CreatePayload EndOfPacket const 1 0x00
  CreatePayload _ErrorCodes Data 2 0x00 $ErrorCodes
  CreatePayload _ErrorMsg string 22 $ErrorMsg
  ConcatPayload mtftp6_error_pld OpCode _ErrorCodes _ErrorMsg EndOfPacket
  CreatePacket  mtftp6_error -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port    \
                 -udp_payload mtftp6_error_pld -IP_ver 6
  return mtftp6_error
}

# Procedure Name
#   Mtftp6CreateData
# Procedure Description:
#   Mtftp6Create create a MTFTPv6 data packet.
# Arguments:
#   dest_port
#   opcode
#   block       : block number
#   data_length
# Returns:
#   The DATA packet.
#
proc Mtftp6CreateData { {dest_port $DEF_DEST_PRT} 
                        {opcode $EFI_MTFTP6_OPCODE_DATA} 
                        {block} 
                        {data_length} } {
  global DEF_SRC_PRT EFI_MTFTP6_OPCODE_DATA

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP6_OPCODE_DATA
  CreatePayload _block Data 2 0x00 $block
  CreatePayload _data  const $data_length 0x5a
  ConcatPayload mtftp6_data_pld OpCode _block _data
  CreatePacket  mtftp6_data -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
                -udp_payload mtftp6_data_pld -IP_ver 6
  return mtftp6_data
}

# Procedure Name
#   Icmp6Unreach
# Procedure Description:
#   Icmp6Unreach creates a ICMPv6 unreachable packet.
# Arguments:
#   DestIp6Addr
#   SrcIp6Addr
# Returns:
#   The Icmp6Unreach error packet.
#
proc Icmp6Unreach { {DestIp6Addr $DEF_EUT_IP_ADDR}
                           {SrcIp6Addr $DEF_OS_IP_ADDR}
                           {IcmpCode}} {
  global DEF_EUT_IP_ADDR DEF_OS_IP_ADDR
  set Icmp6Type "0x01" 
  set Icmp6Code $IcmpCode
  set CheckSum  "0x00 0x00"
  set Reserved  "0x00 0x00 0x00 0x00"
  set Icmp6Data "0x60 0x00 0x00 0x00 0x00 0x31 0x11 0x80 0x20 0x02 0x00 0x00 0x00 0x00 0x00 0x00   \
                                     0x00 0x00 0x00 0x00 0x00 0x00 0x43 0x21 0x20 0x02 0x00 0x00 0x00 0x00 0x00 0x00   \
                                     0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x02 0x06 0xf4 0x00 0x45 0x00 0x31 0xe7 0x65   \
                                     0x00 0x07 0x53 0xaf 0xaf 0xaf 0x70 0x74 0x61 0x6c 0x1c 0x00 0x6f 0x63 0x74 0x65       \
                                     0x74 0x00 0x62 0x6c 0x6b 0x73 0x69 0x7a 0x65 0x00 0x31 0x30 0x32 0x34 0x00 0x74  \
                                     0x69 0x6d 0x65 0x6f 0x75 0x74 0x00 0x32 0x00"
  # Calculate the Icmpv6 checksum
  set Icmp6Payload [concat $Icmp6Type $Icmp6Code $CheckSum $Reserved $Icmp6Data]
  puts $Icmp6Payload

  set PayloadDataLength 97
  set i 0
  set sum 0
  while { $i < $PayloadDataLength } {
   set sum [ expr { $sum + [ expr { [lindex $Icmp6Payload $i] << 8 } ] } ]
   incr i
   if { $i < $PayloadDataLength } {
       set sum [ expr { $sum + [lindex $Icmp6Payload $i] } ]
       incr i        
    }
  }

#
# Check sum adds Pseudo header: two IPs and Payloadlength and Next header (0x3a)
#
  set TempList1 [split $DestIp6Addr :]
  set TempList2 [split $SrcIp6Addr :]
  set TempList [concat $TempList1 $TempList2 "61" "3a"]
  set sum2 0
  for {set i 0} { $i < [ llength $TempList] } { incr i } {
    set temp [ format "0x0%s" [ lindex $TempList $i]]
    set sum2 [expr {$sum2 + $temp}]
  }
  set sum2 [format "0x%x" $sum2]
  set sum [expr {$sum + $sum2}]
  set sum [format "0x%x" $sum]

  while {[expr {$sum >> 16}] != 0} {
    set sumLow16Bit [expr {$sum & 0xffff}]
    set sumHigh16Bit [expr {$sum >> 16}]
    set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
  }
  set sum [expr {~ $sum}]
  set sum [format "0x%x" $sum]

  set checksum1 [expr { $sum & 0xff}]
  set checksum1 [format "0x%x" $checksum1]
  set checksum2 [expr [expr { $sum >> 8}] & 0xff]
  set checksum2 [format "0x%x" $checksum2]

  set Icmp6Payload [lreplace $Icmp6Payload 2 3 $checksum2 $checksum1]
  puts $Icmp6Payload
  CreatePayload Icmp6ErrorPayload List $PayloadDataLength $Icmp6Payload

#
#Create Icmp6 Unreachable packet
#
  CreatePacket DstUnreach -t IPv6 -IPv6_ver 0x06 -IPv6_tc 0x00 -IPv6_fl 0x00  \
                        -IPv6_pl $PayloadDataLength -IPv6_nh 0x3a -IPv6_hl 255 \
                        -IPv6_payload Icmp6ErrorPayload

  return DstUnreach
}

# Procedure Name
#   Icmp6DstPortUnreach
# Procedure Description:
#   Icmp6DstPortUnreach creates a ICMPv6 destination unreachable packet.
# Arguments:
#   DestIp6Addr
#   SrcIp6Addr
# Returns:
#   The Icmp6DstPortUnreach error packet.
#
proc Icmp6DstPortUnreach { {DestIp6Addr $DEF_EUT_IP_ADDR}
                           {SrcIp6Addr $DEF_OS_IP_ADDR}
                           } {
  global DEF_EUT_IP_ADDR DEF_OS_IP_ADDR
  return [Icmp6Unreach $DEF_EUT_IP_ADDR $DEF_OS_IP_ADDR 0x04]
}

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
  puts MTFTP6EUTSetup
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
