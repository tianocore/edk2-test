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
Include include/EntsProtocolTest.inc.tcl
Include EfiUtil/EfiInclude.tcl
Include MNP/include/Mnp.inc.tcl
Include SNP/include/Snp.inc.tcl

if {[info exist MNP_PROC] == 1} {
  return
}
set MNP_PROC 1

proc SetMnpConfigData \
{conf rcvqt xmitqt prot ucast mcast bcast promis flushq rcvtime bpoll} {
  SetVar $conf.ReceivedQueueTimeoutValue		     $rcvqt
  SetVar $conf.TransmitQueueTimeoutValue		     $xmitqt
  SetVar $conf.ProtocolTypeFilter                $prot
  SetVar $conf.EnableUnicastReceive              $ucast
  SetVar $conf.EnableMulticastReceive            $mcast
  SetVar $conf.EnableBroadcastReceive            $bcast
  SetVar $conf.EnablePromiscuousReceive          $promis
  SetVar $conf.FlushQueuesOnReset                $flushq
  SetVar $conf.EnableReceiveTimestamps           $rcvtime
  SetVar $conf.DisableBackgroundPolling          $bpoll
}

proc ShowMnpConf {R_MnpConfData} {
global  $R_MnpConfData.ReceivedQueueTimeoutValue
global  $R_MnpConfData.TransmitQueueTimeoutValue
global  $R_MnpConfData.ProtocolTypeFilter
global  $R_MnpConfData.EnableUnicastReceive
global  $R_MnpConfData.EnableMulticastReceive
global  $R_MnpConfData.EnableBroadcastReceive
global  $R_MnpConfData.EnablePromiscuousReceive
global  $R_MnpConfData.FlushQueuesOnReset
global  $R_MnpConfData.EnableReceiveTimestamps
global  $R_MnpConfData.DisableBackgroundPolling

  puts "\[MNP Conf\]"
  puts "------------"
  puts "ReceivedQueueTimeoutValue:   ${R_MnpConfData.ReceivedQueueTimeoutValue}"
  puts "TransmitQueueTimeoutValue:   ${R_MnpConfData.TransmitQueueTimeoutValue}"
  puts "ProtocolTypeFilter:          ${R_MnpConfData.ProtocolTypeFilter}"
  puts "EnableUnicastReceive:        ${R_MnpConfData.EnableUnicastReceive}"
  puts "EnableMulticastReceive:      ${R_MnpConfData.EnableMulticastReceive}"
  puts "EnableBroadcastReceive:      ${R_MnpConfData.EnableBroadcastReceive}"
  puts "EnablePromiscuousReceive:    ${R_MnpConfData.EnablePromiscuousReceive}"
  puts "FlushQueuesOnReset:          ${R_MnpConfData.FlushQueuesOnReset}"
  puts "EnableReceiveTimestamps:     ${R_MnpConfData.EnableReceiveTimestamps}"
  puts "DisableBackgroundPolling:    ${R_MnpConfData.DisableBackgroundPolling}"
}

proc ShowSnpMode {R_SnpModeData} {
global $R_SnpModeData.State
global $R_SnpModeData.HwAddressSize
global $R_SnpModeData.MediaHeaderSize
global $R_SnpModeData.MaxPacketSize
global $R_SnpModeData.NvRamSize
global $R_SnpModeData.NvRamAccessSize
global $R_SnpModeData.ReceiveFilterMask
global $R_SnpModeData.ReceiveFilterSetting
global $R_SnpModeData.CurrentAddress
global $R_SnpModeData.BroadcastAddress
global $R_SnpModeData.PermanentAddress

  puts "\[SNP MODE\]"
  puts "------------"
  puts "State                ${R_SnpModeData.State}"
  puts "HwAddressSize:       ${R_SnpModeData.HwAddressSize}"
  puts "MediaHeaderSize:     ${R_SnpModeData.MediaHeaderSize}"
  puts "MaxPacketSize:       ${R_SnpModeData.MaxPacketSize}"
  puts "NvRamSize:           ${R_SnpModeData.NvRamSize}"
  puts "NvRamAccessSize:     ${R_SnpModeData.NvRamAccessSize}"
  puts "ReceiveFilterMask:   ${R_SnpModeData.ReceiveFilterMask}"
  puts "ReceiveFilterSetting:${R_SnpModeData.ReceiveFilterSetting}"
  puts "MaxMCastFilterCount: ${R_SnpModeData.MaxMCastFilterCount}"
}

proc VerifyMnpConfData {MnpConfData1 MnpConfData2} {
global  $MnpConfData1.ReceivedQueueTimeoutValue
global  $MnpConfData1.TransmitQueueTimeoutValue
global  $MnpConfData1.ProtocolTypeFilter
global  $MnpConfData1.EnableUnicastReceive
global  $MnpConfData1.EnableMulticastReceive
global  $MnpConfData1.EnableBroadcastReceive
global  $MnpConfData1.EnablePromiscuousReceive
global  $MnpConfData1.FlushQueuesOnReset
global  $MnpConfData1.EnableReceiveTimestamps
global  $MnpConfData1.DisableBackgroundPolling
global  $MnpConfData2.ReceivedQueueTimeoutValue
global  $MnpConfData2.TransmitQueueTimeoutValue
global  $MnpConfData2.ProtocolTypeFilter
global  $MnpConfData2.EnableUnicastReceive
global  $MnpConfData2.EnableMulticastReceive
global  $MnpConfData2.EnableBroadcastReceive
global  $MnpConfData2.EnablePromiscuousReceive
global  $MnpConfData2.FlushQueuesOnReset
global  $MnpConfData2.EnableReceiveTimestamps
global  $MnpConfData2.DisableBackgroundPolling
  set temp pass
  
  set var1 "{$MnpConfData2.ReceivedQueueTimeoutValue}"
  set var2 "{$MnpConfData1.ReceivedQueueTimeoutValue}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.TransmitQueueTimeoutValue}"
  set var2 "{$MnpConfData1.TransmitQueueTimeoutValue}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.EnableBroadcastReceive}"
  set var2 "{$MnpConfData1.EnableBroadcastReceive}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.EnableUnicastReceive}"
  set var2 "{$MnpConfData1.EnableUnicastReceive}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.EnableMulticastReceive}"
  set var2 "{$MnpConfData1.EnableMulticastReceive}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.EnablePromiscuousReceive}"
  set var2 "{$MnpConfData1.EnablePromiscuousReceive}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }
  
  set var1 "{$MnpConfData2.FlushQueuesOnReset}"
  set var2 "{$MnpConfData1.FlushQueuesOnReset}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }  

  set var1 "{$MnpConfData2.EnableReceiveTimestamps}"
  set var2 "{$MnpConfData1.EnableReceiveTimestamps}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.DisableBackgroundPolling}"
  set var2 "{$MnpConfData1.DisableBackgroundPolling}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }

  set var1 "{$MnpConfData2.DisableBackgroundPolling}"
  set var2 "{$MnpConfData1.DisableBackgroundPolling}"
  if {[subst $$var1] != [subst $$var2]} {
    set temp fail
    return $temp
  }
  return $temp
}
proc abcd {MnpConfData1 MnpConfData2} {

  
set var "{$MnpConfData1.ReceivedQueueTimeoutValue}"
puts "$MnpConfData1.ReceivedQueueTimeoutValue: [subst $$var]"
  if {$MnpConfData1.ReceivedQueueTimeoutValue !=
      $MnpConfData2.ReceivedQueueTimeoutValue} {
    set temp fail
    return $temp
  }
  
  if {$MnpConfData1.TransmitQueueTimeoutValue !=
      $MnpConfData2.TransmitQueueTimeoutValue} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.ProtocolTypeFilter !=
      $MnpConfData2.ProtocolTypeFilter} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.EnableUnicastReceive !=
      $MnpConfData2.EnableUnicastReceive} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.EnableMulticastReceive !=
      $MnpConfData2.EnableMulticastReceive} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.EnableBroadcastReceive !=
      $MnpConfData2.EnableBroadcastReceive} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.EnablePromiscuousReceive !=
      $MnpConfData2.EnablePromiscuousReceive} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.FlushQueuesOnReset !=
      $MnpConfData2.FlushQueuesOnReset} {
    set temp fail
    return $temp
  }
  
  if {$MnpConfData1.EnableReceiveTimestamps !=
      $MnpConfData2.EnableReceiveTimestamps} {
    set temp fail
    return $temp
  }
  if {$MnpConfData1.DisableBackgroundPolling !=
      $MnpConfData2.DisableBackgroundPolling} {
    set temp fail
    return $temp
  }
  
  return $temp
}

proc SetFragmentTable {FragmentTable value} {
global $FragmentTable

  set length 0
  return $length
}


proc SetDataLength {variable value} {
  SetVar $variable		     $value 
}

proc SetTxData {variable dest src type datalen hdrlen fragcnt fragtbl} {
  
}

proc SetRawBuff {buff len val} {
  
  
}
proc SetTxBuff {txbuff dest src type} {
  
}
proc SetMacInPacket {variable value} {
  set temp_list [split $value :]
  set temp_num [llength $temp_list]
  if { $temp_num != 6 } {
    puts $temp_num
    return 0
  }

  set temp1 [lindex $temp_list 0]
  set temp2 [lindex $temp_list 1]
  set temp3 [lindex $temp_list 2]
  set temp4 [lindex $temp_list 3]
  set temp5 [lindex $temp_list 4]
  set temp6 [lindex $temp_list 5]

  SetVar $variable "0x$temp1 0x$temp2 0x$temp3 0x$temp4 0x$temp5 0x$temp6"
}

#
# Input:
#   DestAddr  -   In the format of XX:XX:XX:XX:XX:XX
#
proc SetEtherTestPacket { Body DestAddr SrcAddr } {
  SetMacInPacket $Body.DstAddr $DestAddr
  SetMacInPacket $Body.SrcAddr $SrcAddr

  SetVar  $Body.Protocol              0x0800
  SetVar  $Body.Body.Test.Packet      0x00
  SetVar  $Body.Body.Test.NotPacket   0xffffffffffffffff
}

proc DestructVar {first {second ""} args} {
  if {$second == ""} {
    DelVar  $first
  } else {
    if {$args == ""} {
      DelVar      $first
      DelVar      $second
    } else {
      DelVar      $first
      DelVar      $second
      set temp [split $args " "]
      foreach var $temp {
        DelVar  $var
      }
    }
  }
}

proc BuildEthPacket {Name SrcMac DstMac} {
  CreatePayload aaa const 512 0x01
  CreatePacket $Name -t eth -eth_type 0x0800 -eth_payload -eth_src $SrcMac \
               -eth_dst $DstMac aaa
}
