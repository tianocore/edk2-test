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
#
#Copyright (c)  1999 - 2003 Intel Corporation. All rights reserved
##This software and associated documentation (if any) is furnished
#under a license and may only be used or copied in accordance
#with the terms of the license. Except as permitted by such
#license, no part of this software or documentation may be
#reproduced, stored in a retrieval system, or transmitted in any
#form or by any means without the express written consent of
#Intel Corporation.
#
#
#Module Name:
#
#  EfiInclude.tcl
#
#Abstract:
#
#   This file includes the definitions for EFI related data types
#
#References:
#
#Revision History
#   Init  2004/04/15
#

if {[info exist EFI_INC] == 1} {
  return
}
set EFI_INC 1

# Procedure Name
#   SetIpv4Address 
# Procedure Description:
#   Set a value to a RIVL variable, whose type is EFI_IPv4_ADDRESS
# Arguments:
#   @variable : IN The name of the RIVL variable
#   @value    : IN The value to be set.
#                X.X.X.X
# Returns:
#   1 - SUCCESS
#   0 - FAIL
#
proc SetIpv4Address {variable value} {
#
# Check if variable exists and its type is EFI_IPv4_ADDRESS
#

#
# Split value in to a list and check its length should be 4
#
  set temp_list [split $value .]
  set temp_num  [llength $temp_list ]
  if { $temp_num != 4 } {
    puts $temp_num
    return 0
  }

  UINT8  temp_addr(4)
#
# Assign the value.
#   
  for {set i 0} {$i < 4} {incr i} {
   SetVar temp_addr($i) [lindex $temp_list $i]
  }

  SetVar $variable.Addr @temp_addr
#
# Delete the temp RIVL variable 
#
  DelVar temp_addr
  return 1
}
# Procedure Name
#   SetIpv6Address 
# Procedure Description:
#   Set a value to a RIVL variable, whose type is EFI_IPv6_ADDRESS
# Arguments:
#   @variable : IN The name of the RIVL variable
#   @value    : IN The value to be set.
#                xx:xx:xx:xx:xx:xx:xx:xx or ::xx:xx:xx or xx::xx:xx or xx:xx::
# Returns:
#   1 - SUCCESS
#   0 - FAIL
#
proc SetIpv6Address {variable value } {
    puts "SetIpv6Address Begins"
    set val_length [string length $value]
    set str_index [string first "::" $value ]
    if {$str_index != -1 } {
        if {$str_index == 0 || $str_index == [expr $val_length - 2]} {
           set  temp_value [string trim $value "::"]
           set  temp_list [split $temp_value ":"]
           set  temp_num [llength $temp_list]
           set  addr_list $temp_list
           if {$str_index == 0} {
               for {set i 0} { $i < [expr 8 - $temp_num]} {incr i} {
                   set addr_list [linsert $addr_list 0 "0000"]
               }
           } else {
               for {set i 0} { $i < [expr 8 - $temp_num]} {incr i} {
                   lappend addr_list  "0000"
               }
           }
        } else {
            set addr_list1 [split [string range $value 0 [expr $str_index - 1]] :]
            set addr_list2 [split [string range $value [expr $str_index + 2 ] [expr $val_length - 1]] :]
            set addr_num1 [llength $addr_list1]
            set addr_num2 [llength $addr_list2]
            set addr_list $addr_list1
            
            for {set i 0} {$i < [expr 8 - $addr_num1 - $addr_num2]} {incr i} {
               lappend addr_list "0000"
            }
            
            for {set i 0} {$i < $addr_num2} {incr i} {
                lappend addr_list [lindex $addr_list2 $i]
           }
        }
    } else {
        set addr_list [split $value :]
    }
    list ex_addr_list 
    for {set i 0} { $i < 8 } {incr i} {
          set str_len [string length [lindex $addr_list $i]]
          switch $str_len {
              1 {
                  lappend ex_addr_list "0x0"
                  lappend ex_addr_list [format "0x%s"  [lindex $addr_list $i]]
              }
              
              2 {
                  lappend ex_addr_list "0x0"
                  lappend ex_addr_list [format "0x%s" [lindex $addr_list $i]]
              }
               
              3 {
                  lappend ex_addr_list [format "0x%s" [string index [lindex $addr_list $i] 0]]
                  lappend ex_addr_list [format "0x%s" [string range [lindex $addr_list $i] 1 2]]
              }
                           
              4 {
                  lappend ex_addr_list [format "0x%s" [string range [lindex $addr_list $i] 0 1]]
                  lappend ex_addr_list [format "0x%s" [string range [lindex $addr_list $i] 2 3]]
              }
          }
    }
   puts $ex_addr_list
   UINT8  temp_addr(16)
   #
   # Assign the value.
   #   
   for {set i 0} {$i < 16} {incr i} {
       SetVar temp_addr($i) [lindex $ex_addr_list $i]
   }
   SetVar $variable.Addr @temp_addr
   #
   # Delete the temp RIVL variable 
   #
   DelVar temp_addr
   return 1
}

# Procedure Name
#   GetIpv4Address 
# Procedure Description:
#   Get a value from a RIVL variable, whose type is EFI_IPv4_ADDRESS
# Arguments:
#   @variable : IN The name of the RIVL variable
# Returns:
#   0 - FAIL
#   X.X.X.X - SUCCESS
#


proc GetIpv4Address {variable } {

global $variable.Addr
#
# Check if variable exists and its type is EFI_IPv4_ADDRESS
#

#
# Remote get the value and concat it using format X.X.X.X
#
  GetVar $variable
  set temp_list [array get $variable.Addr 0]
  set num [lindex $temp_list 1]
  set temp_value [format %d $num]

  for {set i 1} {$i < 4} {incr i} {
    set temp_list [array get $variable.Addr $i]
    set num [lindex $temp_list 1]
    set num [format %d $num]
    set temp_value $temp_value.$num
  }
  return $temp_value
}


proc GetIpv6Address {variable } {

global $variable.Addr
#
# Check if variable exists and its type is EFI_IPv6_ADDRESS
#

#
# Remote get the value and concat it using format xx:xx:xx:xx:xx:xx:xx:xx:xx
#
  puts "GetIpv6Address Begins"
  GetVar $variable
  set ipv6_addr ""
  for {set i 0} {$i < 8} {incr i} {
    set high_bit_list [array get $variable.Addr [expr 2*$i]]
    set low_bit_list [array get $variable.Addr [expr [expr 2*$i] + 1]]
    set high_bit [lindex $high_bit_list 1]
    set low_bit [lindex $low_bit_list 1]

	set ipv6_addr [format "%s%02x%02x" $ipv6_addr $high_bit $low_bit]
    if {$i != 7} {
        set ipv6_addr $ipv6_addr:
    }
  }
  return $ipv6_addr
}

# Procedure Name
#   SetEthMacAddress 
# Procedure Description:
#   Set a value to a RIVL variable, whose type is EFI_MAC_ADDRESS
# Arguments:
#   @variable : IN The name of the RIVL variable
#   @value    : IN The value to be set.
#                X:X:X:X:X:X
# Returns:
#   1 - SUCCESS
#   0 - FAIL
#
proc SetEthMacAddress {variable value} {
#
# Check if variable exists and its type is EFI_MAC_ADDRESS
#

#
# Split value in to a list and check its length should be 4
#
  set temp_list [split $value :]
  set temp_num [llength $temp_list ]
  if { $temp_num != 6 } {
    puts $temp_num
    return 0
  }

  UINT8  temp_mac_addr(32)

#
# Assign the value.
#   
  for {set i 0} {$i < 6} {incr i} {
    set temp [lindex $temp_list $i]
    SetVar temp_mac_addr($i) 0x$temp
  }

  SetVar $variable.Addr @temp_mac_addr

#
# Delete the temp RIVL variable 
#
  DelVar temp_mac_addr
  return 1
}


# Procedure Name
#   GetEthMacAddress 
# Procedure Description:
#   Get a value from a RIVL variable, whose type is EFI_MAC_ADDRESS
# Arguments:
#   @variable : IN The name of the RIVL variable
# Returns:
#   0 - FAIL
#   X.X.X.X - SUCCESS
#


proc GetEthMacAddress {variable } {

global $variable.Addr
#
# Check if variable exists and its type is EFI_IPv4_ADDRESS
#

#
# Remote get the value and concat it using format X.X.X.X
#
  GetVar $variable
  set temp_list [array get $variable.Addr 0]
  set num [lindex $temp_list 1]
  set temp_value [format %02X $num]

  for {set i 1} {$i < 6} {incr i} {
    set temp_list [array get $variable.Addr $i]
    set num [lindex $temp_list 1]
    set num [format %02X $num]
    set temp_value $temp_value:$num
  }
  return $temp_value
}

# Procedure Name
#   SetGuid
# Procedure Description:
#   Set a value to a RIVL variable, whose type is EFI_GUID
# Arguments:
#   @variable : IN The name of the RIVL variable
#   @value    : IN The value to be set.
#               XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
# Returns:
#   1 - SUCCESS
#   0 - FAIL
#
proc SetGuid {variable value} {
#
# Check if variable exists and its type is EFI_GUID
#

#
# Split value in to a list and check its length should be 4
#
  set temp_list [split $value -]
  set num [llength $temp_list ]

  if { $num != 5 } {
    return 0
  }

  set temp [lindex $temp_list 0]
  SetVar $variable.Data1 0x$temp
  set temp [lindex $temp_list 1]
  SetVar $variable.Data2 0x$temp
  set temp [lindex $temp_list 2]
  SetVar $variable.Data3 0x$temp
  
  set temp [lindex $temp_list 3]
  set temp1 [string range $temp 0 1]
  SetVar $variable.Data4(0) 0x$temp1
  set temp1 [string range $temp 2 3]
  SetVar $variable.Data4(1) 0x$temp1
  
  set temp [lindex $temp_list 4]
  set temp1 [string range $temp 0 1]
  SetVar $variable.Data4(2) 0x$temp1
  set temp1 [string range $temp 2 3]
  SetVar $variable.Data4(3) 0x$temp1
  set temp1 [string range $temp 4 5]
  SetVar $variable.Data4(4) 0x$temp1
  set temp1 [string range $temp 6 7]
  SetVar $variable.Data4(5) 0x$temp1
  set temp1 [string range $temp 8 9]
  SetVar $variable.Data4(6) 0x$temp1
  set temp1 [string range $temp 10 11]
  SetVar $variable.Data4(7) 0x$temp1

  return 1
}

# Procedure Name
#   GetGuid
# Procedure Description:
#   Get a value from a RIVL variable, whose type is EFI_GUID
# Arguments:
#   @variable : IN The name of the RIVL variable
# Returns:
#   0                                       - FAIL
#   XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX    - SUCCESS
#


proc GetGuid {variable } {

global $variable.Data1
global $variable.Data2
global $variable.Data3
global $variable.Data4
#
# Check if variable exists and its type is EFI_IPv4_ADDRESS
#

#
# Remote get the value and concat it using format 
#    XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX  
#
  GetVar $variable
  set var   "{$variable.Data1}"
  set value [format %X [subst "$$var"] ]
  set var   "{$variable.Data2}"
  set temp  [format %X [subst "$$var"] ]
  set value $value-$temp  
  set var   "{$variable.Data3}"
  set temp  [format %X [subst "$$var"] ]
  set value $value-$temp  
  
  for {set i 0} {$i < 8} {incr i} {
    set temp_list [array get $variable.Data4 $i]
    set num       [lindex $temp_list 1]
    set temp$i    [format %X $num]
  }
  
  set value $value-$temp0$temp1-$temp2$temp3$temp4$temp5$temp6$temp7

  return $value
}

# Procedure Name
#   Htonl
# Procedure Description:
#   convert unsigned integer hostlong from host byte order to network byte order
# Arguments:
#   @variable : IN the hostlong which is to be converted
# Returns:
#   0                                       - FAIL
#   Converted Value                         - SUCCESS
#

proc Htonl { value } { 
  if { $value > 0xffffffff } {
    return  0
  }
  set temp [format "0x%X" [expr "(($value & 0xff)<<24)+(($value&0xff000000)>>24)\
           +(($value&0xff00)<<8)+(($value&0xff0000)>>8)"]]
  
  return $temp
  
}

# Procedure Name
#   Htons
# Procedure Description:
#   convert unsigned short integer from host byte order to network byte order
# Arguments:
#   @variable : IN the short which is to be converted
# Returns:
#   0                                       - FAIL
#   Converted Value                         - SUCCESS
#

proc Htons { value } { 
  if { $value > 0xffff } {
    return  0
  }
  
  set temp [expr "(($value & 0xff)<<8) + (($value&0xff00)>>8)"]
  
  return $temp
}

# Procedure Name
#   Ntohl
# Procedure Description:
#   convert unsigned integer from network byte order to host byte order
# Arguments:
#   @variable : IN the long which is to be converted
# Returns:
#   0                                       - FAIL
#   Converted Value                         - SUCCESS
#
proc Ntohl { value } {
  if { $value > 0xffffffff } {
    return  0
  }
  
  set temp [expr "(($value & 0xff)<<24) + (($value&0xff000000)>>24) + \
           (($value&0xff00)<<8) + (($value&0xff0000)>>8)"]
  
  return $temp

}

# Procedure Name
#   Ntohs
# Procedure Description:
#   convert unsigned short integer from network byte order to host byte order
# Arguments:
#   @variable : IN the short which is to be converted
# Returns:
#   0                                       - FAIL
#   Converted Value                         - SUCCESS
#
proc Ntohs { value } {
  if { $value > 0xffff } {
    return  0
  }
  
  set temp [expr "(($value & 0xff)<<8) + (($value&0xff00)>>8)"]
  
  return $temp
}

proc VerifyRemoteIntVal {variable expect} {
global $variable

  GetVar  $variable

  set value [subst $${variable}]
  if {$value == $expect} {
    set temp pass
  } else {
    set temp fail
  }
  return $temp
}

proc VerifyReturnStatus {status expect} {
  VerifyRemoteIntVal  $status $expect
}

proc VerifyOpResult {opresult expect} {
global $opresult

  if {[string compare -nocase [subst $$opresult] $expect] == 0} {
    set temp pass
  } else {
    set temp fail
  }
  return $temp
}

#
# Procedure Name
#   ArrayToPayload
# Procedure Description:
#   Transfer the content of a TCL array to a payload
# Arguments:
#   @array   : IN  The name of the TCL array variable
#   @payload : OUT The name of the destination payload
# Returns:
#   N/A
#


proc ArrayToPayload { array  payload  } {
  upvar 1 $array local_array

  set local_size [array size local_array]
  
  CreatePayload $payload  CONST $local_size 0
  
  for {set i 0} {$i < $local_size } {incr i} {
    SetToPayload $payload $i $local_array($i)
  }
  unset local_size
}

#
# Procedure Name
#   PayloadToArray
# Procedure Description:
#   Transfer the content a payload to a a TCL array
# Arguments:
#   @payload : IN   The name of the payload
#   @array   : OUT  The name of the TCL array variable
# Returns:
#   N/A
#
proc PayloadToArray { payload array } {
  upvar 1 $array local_array

  set local_size [LenOfPayload $payload ]
  
  for {set i 0} {$i < $local_size } {incr i} {
    set local_array($i) [GetFromPayload $payload $i]
  }
  unset local_size
}

#
# Procedure Name
#   SendPacketDelay
# Procedure Description:
#   Send the appointed packet after the appointed time 
# Arguments:
#   @packetname : IN   The name of the packet
#   @delaytime  : IN   The delaytime of sending packet, the delay time is caculate in millisecond
# Returns:
#   N/A
#
proc SendPacketDelay {packetname delaytime} {
	global tk_version
	set TKVersion [info exist tk_version]

	if {$TKVersion == 1} {
		after $delaytime [list SendPacket $packetname ]
	} else {
		SendPacket $packetname -d $delaytime
  }
}