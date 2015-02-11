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
if {[info exist MTFTP4_PROC_TCL] == 1} {
  return
}
set MTFTP4_PROC_TCL 1

Include include/GenericAssertionGuid.tcl
Include include/EntsProtocolTest.inc.tcl
# Procedure Name
#   Mtftp4GetSrcPort
# Procedure Description:
#   Mtftp4GetSrcPort parse the packet of client, extract the source port.
# Arguments:
#   packet
# Returns:
#   The source port of the client
#
proc Mtftp4GetSrcPort { packet } {
  global client_port server_port DEF_SERVER_PRT GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_sp client_port -udp_dp server_port
  if {$server_port == $DEF_SERVER_PRT} {
    set assert pass
  } else {
    set assert fail
  }
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Destination port in client packet - $server_port, Expected  \
                   Port == $DEF_SERVER_PRT"

  return $client_port
}


# Procedure Name
#   Mtftp4ParseReq
# Procedure Description:
#   Mtftp4ParseReq an Udp packet, get Mtftp4 Options
# Arguments:
#   packet
# Returns:
#   The array of Mtftp4 Options
#
proc Mtftp4ParseReq { packet } {
  global udp_length mtftp_options
  
  ParsePacket $packet -t udp -udp_len udp_length -udp_payload udp_pld
  set mtftp_len expr[$udp_length - 8]

  set zero_cnt 0

  for {set i 0} {$i < $mtftp_len} {incr i} {
    set tmp_value [ GetFromPayload udp_pld $i ]
    if {$tmp_value == 0} {
      incr zero_cnt
      if {[$zero_cnt % 2] == 0} {
        set begin_of_option $i
      } elseif {[$zero_cnt > 1} {
        set end_of_option   $i
        set begin_of_value  $i
        SplitPayload _option udp_pld $begin_of_option $end_of_option
        incr i
        set tmp_value [ GetFromPayload udp_pld $i ]
        while {$tmp_value != 0} {
          incr i
          set tmp_value [ GetFromPayload udp_pld $i ]
        }
        set end_of_value $i
        incr i -1
        SplitPayload _value udp_pld $begin_of_value $end_of_value
        set mtftp_options($_option) $_value
      }
    }
  }
  
  return mtftp_options  ;# need return?
}


# Procedure Name
#   Mtftp4CreateOack
# Procedure Description:
#   Mtftp4CreateOack a MTFTPv4 OACK packet.
# Arguments:
#   dest_port
#   opcode
# Returns:
#   The OACK packet.
#
proc Mtftp4CreateOack { {dest_port $DEF_DEST_PRT} 
	                      {opcode $EFI_MTFTP4_OPCODE_OACK}} {
  global option_value_array option_value_len DEF_SRC_PRT EFI_MTFTP4_OPCODE_OACK
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
  CreatePacket  mtftp4_oack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
                   -udp_payload mtftp_oack_pld

  return mtftp4_oack
}



# Procedure Name
#   Mtftp4CreateEmptyOack
# Procedure Description:
#   Mtftp4CreateEmptyOack create a MTFTPv4 empty OACK packet.
# Arguments:
#   dest_port
# Returns:
#   The empty OACK packet.
#
proc Mtftp4CreateEmptyOack { {dest_port $DEF_DEST_PRT} } {
  global EFI_MTFTP4_OPCODE_OACK DEF_DEST_PRT DEF_SRC_PRT

  CreatePayload EndOfPacket const 1 0x00
  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_OACK
  ConcatPayload mtftp_oack_pld OpCode EndOfPacket
  CreatePacket  mtftp4_oack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
                   -udp_payload mtftp_oack_pld
                  
  return mtftp4_oack
} 
  
  

# Procedure Name
#   Mtftp4CreateError
# Procedure Description:
#   GMtftp4Create a MTFTPv4 ERROR packet.
# Arguments:
#   dest_port
#   ErrorCodes
#   ErrorMsg
# Returns:
#   The error packet.
#
proc Mtftp4CreateError { {dest_port $DEF_DEST_PRT} 
	                       {ErrorCodes $EFI_MTFTP4_ERRORCODE_NOT_DEFINED} 
	                       {ErrorMsg "Not defined ErrorType"} } {
  global EFI_MTFTP4_OPCODE_ERROR DEF_DEST_PRT EFI_MTFTP4_ERRORCODE_NOT_DEFINED 
  global DEF_SRC_PRT

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_ERROR
  CreatePayload EndOfPacket const 1 0x00
  CreatePayload _ErrorCodes Data 2 0x00 $ErrorCodes
  CreatePayload _ErrorMsg string 22 $ErrorMsg
  ConcatPayload mtftp4_error_pld OpCode _ErrorCodes _ErrorMsg EndOfPacket
  CreatePacket  mtftp4_error -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port    \
                 -udp_payload mtftp4_error_pld
  return mtftp4_error
}


# MTFP4 Ack8 field  should be ignored and treated as reserved
#
# Procedure Name
#   Mtftp4CreateAck8
# Procedure Description:
#   Mtftp4CreateAck8 create a MTFTPv4 ACK8 packet.
# Arguments:
#   dest_port
#   blk_number
# Returns:
#   The ACK8 packet.
#
# proc Mtftp4CreateAck8 { {dest_port $DEF_DEST_PRT} {blk_number}} {
#   global DEF_SRC_PRT EFI_MTFTP4_OPCODE_ACK8
# 
#   CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_ACK8
#   CreatePayload _blk_number Data 8 0x00 0x00 0x00 0x00 0x00 0x00 0x00 $blk_number
#   ConcatPayload mtftp4_ack8_pld OpCode _blk_number
#   CreatePacket  mtftp4_ack8 -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
#                 -udp_payload mtftp4_ack8_pld
#   return mtftp4_ack8
# }


# Procedure Name
#   Mtftp4CreateAck
# Procedure Description:
#   Mtftp4CreateAck create a MTFTPv4 ACK packet.
# Arguments:
#   dest_port
#   blk_number
# Returns:
#   The ACK packet.
#
proc Mtftp4CreateAck { {dest_port $DEF_DEST_PRT} {blk_number}} {
  global DEF_SRC_PRT EFI_MTFTP4_OPCODE_ACK

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_ACK
  CreatePayload _blk_number Data 2 0x00 $blk_number
  ConcatPayload mtftp4_ack_pld OpCode _blk_number
  CreatePacket  mtftp4_ack -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port      \
                -udp_payload mtftp4_ack_pld
  return mtftp4_ack
}



# Procedure Name
#   Mtftp4CreateData
# Procedure Description:
#   Mtftp4Create create a MTFTPv4 data packet.
# Arguments:
#   dest_port
#   opcode
#   block       : block number
#   data_length
# Returns:
#   The DATA packet.
#
proc Mtftp4CreateData { {dest_port $DEF_DEST_PRT} 
	                      {opcode $EFI_MTFTP4_OPCODE_DATA} 
	                      {block} 
	                      {data_length} } {
  global DEF_SRC_PRT EFI_MTFTP4_OPCODE_DATA

  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_DATA
  CreatePayload _block Data 2 0x00 $block
  CreatePayload _data  const $data_length 0x5a
  ConcatPayload mtftp4_data_pld OpCode _block _data
  CreatePacket  mtftp4_data -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
                -udp_payload mtftp4_data_pld
  return mtftp4_data
}


# MTFTP4 Data8 field  should be ignored and treated as reserved
#
# Procedure Name
#   Mtftp4CreateData8
# Procedure Description:
#   Mtftp4Create create a MTFTPv4 data8 packet.
# Arguments:
#   dest_port
#   opcode
#   block       : block number
#   data_length
# Returns:
#   The DATA packet.
#
#
# proc Mtftp4CreateData8 { {dest_port $DEF_DEST_PRT} 
#	                       {opcode $EFI_MTFTP4_OPCODE_DATA8} {block} 
#	                       {data_length} } {
#  global DEF_SRC_PRT EFI_MTFTP4_OPCODE_DATA8
#
#  CreatePayload OpCode Data 2 0x00 $EFI_MTFTP4_OPCODE_DATA8
#  CreatePayload _block Data 8 0x00 0x00 0x00 0x00 0x00 0x00 0x00 $block
#  CreatePayload _data  const $data_length 0x5a
#  ConcatPayload mtftp4_data_pld OpCode _block _data
#  CreatePacket  mtftp4_data -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port     \
#                 -udp_payload mtftp4_data_pld
#  return mtftp4_data
# }


# Procedure Name
#   Mtftp4CreateUnexpect
# Procedure Description:
#   Mtftp4CreateUnexpect create an unexpected MTFTPv4 packet
# Arguments:
#   dest_port
# Returns:
#   The error packet.
#
proc Mtftp4CreateUnexpect { {dest_port $DEF_DEST_PRT} } {
  global DEF_DEST_PRT DEF_SRC_PRT
  
  CreatePayload OpCode Data 2 0x00 0x01
  CreatePayload EndOfPacket const 1 0x00
  ConcatPayload mtftp_unexpect_pld OpCode EndOfPacket
  CreatePacket  mtftp_unexpect -t udp -udp_sp $DEF_SRC_PRT -udp_dp $dest_port  \
                -udp_payload mtftp_unexpect_pld
  return mtftp_unexpect
}


# Procedure Name
#   ValidateAck
# Procedure Description:
#   ValidateAck validate a received mtftp4 ack packet.
# Arguments:
#   packet
#   blk_number
# Returns:
#   
#
proc ValidateAck { {packet} {blk_number} } {
  global client_port server_port ack_payload block GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_sp client_port -udp_dp server_port           \
                -udp_payload ack_payload
  SplitPayload block ack_payload 2 3
  set tmp_block [ GetFromPayload block 1 ]
  if {$tmp_block == $blk_number} {
    set assert pass
  } else {
    set assert fail
  }
  RecordAssertion $assert $GenericAssertionGuid                                \
                  "Receive mtftp4 ack, block number is - $tmp_block, Expected  \
                   block == $blk_number"
}


# MTFP4 Ack8 field  should be ignored and treated as reserved
#
# Procedure Name
#   ValidateAck8
# Procedure Description:
#   ValidateAck8 validate a received mtftp4 ack8 packet.
# Arguments:
#   packet
#   blk_number
# Returns:
#   
#
# proc ValidateAck8 { {packet} {blk_number} } {
#   global client_port server_port ack_payload block GenericAssertionGuid
#   
#   ParsePacket $packet -t udp -udp_sp client_port -udp_dp server_port           \
#                 -udp_payload ack_payload
#   SplitPayload block ack_payload 8 9
#   set tmp_block [ GetFromPayload block 1 ]
#   if {$tmp_block == $blk_number} {
#     set assert pass
#  } else {
#    set assert fail
#  }
#  RecordAssertion $assert $GenericAssertionGuid                                \
#                  "Receive mtftp4 ack8, block number is - $tmp_block, Expected \
#                   block == $blk_number"
# }


# Procedure Name
#   ValidateMultiAck
# Procedure Description:
#   ValidateMultiAck validate a received mtftp4 ack packet when using streaming 
#   option.
# Arguments:
#   packet
#   blk_number_start
#   blk_number_end
# Returns:
#   
#
proc ValidateMultiAck { {packet} {blk_number_start} {blk_number_end} } {
  global client_port server_port ack_payload block GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_sp client_port -udp_dp server_port           \
               -udp_payload ack_payload
  set j 2
  set k 3
  for {set i $blk_number_start} {$i <= $blk_number_end} {incr i} {
    SplitPayload block ack_payload $j $k
    set tmp_block [ GetFromPayload block 1 ]
    incr j 2
    incr k 2
    if {$tmp_block == $i} {
      set assert pass
    } else {
      set assert fail
    }
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 ack, block number is - $tmp_block, Expected\
                     block == $i"
  }
}


# Procedure Name
#   ValidateError
# Procedure Description:
#   ValidateError validate whether a received mtftp4 packet is an error packet 
#   or not.
# Arguments:
#   packet
# Returns:
#   
#
proc ValidateError { {packet} } {
  global EFI_MTFTP4_OPCODE_ERROR ack_payload error_code GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_payload ack_payload
  SplitPayload error_code ack_payload 0 1
  set code [ GetFromPayload error_code 1 ]
  if {$code == $EFI_MTFTP4_OPCODE_ERROR} {
    set assert pass
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 packet is an error packet as expected."
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 packet is not an error packet as expected."
  }
}



# Procedure Name
#   ValidateDataBlk
# Procedure Description:
#   ValidateDataBlk validate the block number in the Data packet is correct or 
#   not.
# Arguments:
#   packet
# Returns:
#   
#
proc ValidateDataBlk { {packet} {blk_num} } {
  global EFI_MTFTP4_OPCODE_DATA data_payload opcode GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_payload data_payload
  SplitPayload opcode data_payload 0 1
  set code [ GetFromPayload opcode 1 ]
  if {$code == $EFI_MTFTP4_OPCODE_DATA} {
    SplitPayload block_number data_payload 2 3
    set block [ GetFromPayload block_number 1 ]
    if {$block == $blk_num} {
      set assert pass
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Receive mtftp4 packet is a DATA packet as expected."
    } else {
      set assert fail
      RecordAssertion $assert $GenericAssertionGuid                            \
                      "Receive mtftp4 packet is not a expected DATA packet."
    }
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 packet is not a DATA packet."
  }
}


# Procedure Name
#   ValidateData
# Procedure Description:
#   ValidateDatavalidate whether a received mtftp4 packet is a DATA packet or not.
# Arguments:
#   packet
# Returns:
#   
#
proc ValidateData { {packet} } {
  global EFI_MTFTP4_OPCODE_DATA data_payload opcode GenericAssertionGuid
  
  ParsePacket $packet -t udp -udp_payload data_payload
  SplitPayload opcode data_payload 0 1
  set code [ GetFromPayload opcode 1 ]
  if {$code == $EFI_MTFTP4_OPCODE_DATA} {
    set assert pass
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 packet is a DATA packet as expected."
  } else {
    set assert fail
    RecordAssertion $assert $GenericAssertionGuid                              \
                    "Receive mtftp4 packet is not a DATA packet as expected."
  }
}


# MTFTP4  Data8 field  should be ignored and treated as reserved
#
# Procedure Name
#   ValidateData8
# Procedure Description:
#   ValidateData8 validate whether a received mtftp4 packet is a DATA8 packet 
#    or not.
# Arguments:
#   packet
# Returns:
#   
# proc ValidateData8 { {packet} } {
#   global EFI_MTFTP4_OPCODE_DATA8 data8_payload opcode GenericAssertionGuid
#    
#   ParsePacket $packet -t udp -udp_payload data8_payload
#    SplitPayload opcode data8_payload 0 1
#   set code [ GetFromPayload opcode 1 ]
#    if {$code == $EFI_MTFTP4_OPCODE_DATA8} {
#      set assert pass
#      RecordAssertion $assert $GenericAssertionGuid                              \
#                      "Receive mtftp4 packet is a DATA8 packet as expected."
#   } else {
#      set assert fail
#    RecordAssertion $assert $GenericAssertionGuid                              \
#                    "Receive mtftp4 packet is not a DATA8 packet as expected."
#   }
# }


# Procedure Name
#   AddEntryInArpCache
# Procedure Description:
#   Call ARP.Add() to add an entry in ARP cache.
# Arguments:
#   EutStationAddress  - EUT station IP address.
#   EntsSwAddress      - ENTS IP address.
#   EntsHwAddress      - ENTS MAC address.
# Returns:
#   Nothing.
#
proc AddEntryInArpCache { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR
  
	BeginScope _PROC_ADD_ENTRY_IN_ARP_CACHE_
  
  EFI_IP_ADDRESS                   R_Proc_StationAddress
  EFI_ARP_CONFIG_DATA              R_Proc_ArpConfigData
  EFI_IP_ADDRESS                   R_Proc_TargetSwAddress
  EFI_MAC_ADDRESS                  R_Proc_TargetHwAddress
  UINTN                            R_Proc_ArpStatus
  UINTN                            R_Proc_ArpHandle
  
  ArpServiceBinding->CreateChild "&@R_Proc_ArpHandle, &@R_Proc_ArpStatus"
  GetAck
  SetVar     [subst $ENTS_CUR_CHILD]  @R_Proc_ArpHandle
  
  SetIpv4Address R_Proc_StationAddress.v4     $DEF_EUT_IP_ADDR
  SetVar R_Proc_ArpConfigData.SwAddressType   0x800
  SetVar R_Proc_ArpConfigData.SwAddressLength 4
  SetVar R_Proc_ArpConfigData.StationAddress  &@R_Proc_StationAddress
  SetVar R_Proc_ArpConfigData.EntryTimeOut    0
  SetVar R_Proc_ArpConfigData.RetryCount      0
  SetVar R_Proc_ArpConfigData.RetryTimeOut    0
  
  Arp->Configure {&@R_Proc_ArpConfigData, &@R_Proc_ArpStatus}
  GetAck
  
  SetIpv4Address   R_Proc_TargetSwAddress.v4 $DEF_ENTS_IP_ADDR
  SetEthMacAddress R_Proc_TargetHwAddress $DEF_ENTS_MAC_ADDR
  
  #
  # check point
  #
  Arp->Add {FALSE, &@R_Proc_TargetSwAddress, &@R_Proc_TargetHwAddress, 0, TRUE,\
  	        &@R_Proc_ArpStatus}
  GetAck
}


# Procedure Name
#   DelEntryInArpCache
# Procedure Description:
#   Call ARP.Delete() to delete an entry in ARP cache.
# Arguments:
#   EutStationAddress  - EUT station IP address.
#   EntsSwAddress      - ENTS IP address.
#   EntsHwAddress      - ENTS MAC address.
# Returns:
#   Nothing.
#
proc DelEntryInArpCache { } {
  global ENTS_CUR_CHILD DEF_EUT_IP_ADDR DEF_ENTS_IP_ADDR DEF_ENTS_MAC_ADDR
  UINTN TempCurChild
  
  SetVar TempCurChild @[subst $ENTS_CUR_CHILD]
  SetVar [subst $ENTS_CUR_CHILD]  @R_Proc_ArpHandle
  
  Arp->Delete {TRUE, &@R_Proc_TargetSwAddress, &@R_Proc_ArpStatus}
  GetAck

  ArpServiceBinding->DestroyChild {@R_Proc_ArpHandle, &@R_Proc_ArpStatus}
  GetAck

  SetVar [subst $ENTS_CUR_CHILD]  @TempCurChild
  
  EndScope _PROC_ADD_ENTRY_IN_ARP_CACHE_
}

#
# end of MTFTP4_PROC_TCL
#
