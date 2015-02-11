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
if {[info exist DHCP6_PROC] == 1} {
  return
}
set DHCP6_PROC 1

#
# CreateDHCP6AdvertisePayloadData to create payload for Solicit packet with one Ipv6 \
# address assigned to client.
#
proc CreateDHCP6AdvertisePayloadData { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Advertise payload. 
# Fixed Length should be 0xe7 (231) DUID Type 1 - 3, 0xeb (235) DUID Type 4
#

set MessageType 0x02
set DuidType [lrange $TransId_and_ClientId 7 8]


#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f 0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Domain Search List
#
set DomainSearchList "\
0x00 0x18 0x00 0x0d 0x07 0x65 0x78 0x61 0x6d 0x70 0x6c 0x65 0x03 0x63 0x6f 0x6d 0x00"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

#
# DHCPv6 Option: Identity Association for Non-temporary Address
#
set IAforNA "\
0x00 0x03 0x00 0x79 0x00 0x00 0x00 0x01 0x00 0x00 0x07 0xd0 0x00 0x00 0x0b 0xb8 \
0x00 0x05 0x00 0x18 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 \
0x01 0x47 0x52 0x7d 0x00 0x00 0x0e 0x10 0x00 0x00 0x1c 0x20 0x00 0x0d 0x00 0x4d \
0x00 0x00 0x31 0x20 0x61 0x64 0x64 0x72 0x20 0x67 0x72 0x61 0x6e 0x74 0x65 0x64 \
0x2e 0x20 0x4e 0x65 0x78 0x74 0x20 0x74 0x69 0x6d 0x65 0x20 0x79 0x6f 0x75 0x20 \
0x6d 0x69 0x67 0x68 0x74 0x20 0x63 0x6f 0x6e 0x73 0x69 0x64 0x65 0x72 0x20 0x69 \
0x6e 0x63 0x6c 0x75 0x64 0x69 0x6e 0x67 0x20 0x49 0x41 0x41 0x44 0x44 0x52 0x20 \
0x69 0x6e 0x20 0x49 0x41 0x20 0x6f 0x70 0x74 0x69 0x6f 0x6e 0x2e"

#
# DHCPv6 Option: Preference
set Preference "0x00 0x07 0x00 0x01 0x00"

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0xe7"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0xeb"
}
  
# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated

set AdvertisePayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $IAforNA $DNSServer $DomainSearchList \
                 $ServerId $Preference]

#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 231
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 235
}
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $AdvertisePayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $AdvertisePayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]

if {$DuidType != "0x00 0x04"} {
  set TempList [concat $TempList1 $TempList2 "e7" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "eb" "11"]
}
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

set AdvertisePayloadData [lreplace $AdvertisePayloadData 6 7 $checksum2 $checksum1]
puts $AdvertisePayloadData

return $AdvertisePayloadData  
}

#
# CreateDHCP6AdvertisePayloadData2 to create payload for Solicit packet with two Ipv6 \
# addresses assigned to client.
#
proc CreateDHCP6AdvertisePayloadData2 { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Advertise payload. 
# Fixed Length should be 0x01 0x03 (259) DUID Type 1 - 3, 0x01 0x07 (263) DUID Type 4
#
set MessageType 0x02
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f 0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Domain Search List
#
set DomainSearchList "\
0x00 0x18 0x00 0x0d 0x07 0x65 0x78 0x61 0x6d 0x70 0x6c 0x65 0x03 0x63 0x6f 0x6d 0x00"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

#
# DHCPv6 Option: Identity Association for Non-temporary Address with two Ipv6 addresses\
# count from 0,(B2-3)Optionlength for IANA=149,(B16-43)info of first Ipv6 address,\
# (B44-71)info of second Ipv6 address 
set IAforNA "\
0x00 0x03 0x00 0x95 0x00 0x00 0x00 0x01 0x00 0x00 0x07 0xd0 0x00 0x00 0x0b 0xb8 \
0x00 0x05 0x00 0x18 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 \
0x01 0x47 0x52 0x7d 0x00 0x00 0x0e 0x10 0x00 0x00 0x1c 0x20 0x00 0x05 0x00 0x18 \
0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 0x01 0x47 0x52 0x7c \
0x00 0x00 0x0e 0x10 0x00 0x00 0x1c 0x20 0x00 0x0d 0x00 0x4d 0x00 0x00 0x31 0x20 \
0x61 0x64 0x64 0x72 0x20 0x67 0x72 0x61 0x6e 0x74 0x65 0x64 0x2e 0x20 0x4e 0x65 \
0x78 0x74 0x20 0x74 0x69 0x6d 0x65 0x20 0x79 0x6f  0x75 0x20 0x6d 0x69 0x67  0x68 \
0x74 0x20 0x63 0x6f  0x6e 0x73 0x69 0x64 0x65 0x72 0x20 0x69 0x6e 0x63 0x6c 0x75 \
0x64 0x69 0x6e 0x67 0x20 0x49 0x41 0x41 0x44 0x44 0x52 0x20  0x69 0x6e 0x20 0x49 \
0x41 0x20 0x6f  0x70 0x74 0x69 0x6f 0x6e 0x2e"

#
# DHCPv6 Option: Preference
#
set Preference "0x00 0x07 0x00 0x01 0x00"

if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x01 0x03"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x01 0x07"
}

# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated after calculated

set AdvertisePayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $IAforNA $DNSServer $DomainSearchList \
                 $ServerId $Preference]

#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 259
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 263
}
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $AdvertisePayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $AdvertisePayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]

if {$DuidType != "0x00 0x04"} {
  set TempList [concat $TempList1 $TempList2 "103" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "107" "11"]
}
  
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

set AdvertisePayloadData [lreplace $AdvertisePayloadData 6 7 $checksum2 $checksum1]
puts $AdvertisePayloadData

return $AdvertisePayloadData  
}

#
# CreateDHCP6ReplyPayloadData for request message with one Ipv6 address assigned to client.
#
proc CreateDHCP6ReplyPayloadData { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Reply payload. 
# Fixed Length 0xb3 (179) for GuidType 1 - 3, 0xb7(183) for GuidType 4
#
set MessageType 0x07
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f 0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Domain Search List
#
set DomainSearchList "\
0x00 0x18 0x00 0x0d 0x07 0x65 0x78 0x61 0x6d 0x70 0x6c 0x65 0x03 0x63 0x6f 0x6d 0x00"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

#
# DHCPv6 Option: Identity Association for Non-temporary Address
# (count from 0)T1(B8-11)=10,(B12-15)T2=15,(B36-39)preferred lifetime=18,\
# (B40-43)valid lifetime=36
set IAforNA "\
 0x00 0x03 0x00 0x4a 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x0a 0x00 0x00 0x00 0x0f \
 0x00 0x05 0x00 0x18 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 \
 0x01 0x47 0x52 0x7d 0x00 0x00 0x00 0x12 0x00 0x00 0x00 0x24 0x00 0x0d 0x00 0x1e \
 0x00 0x00 0x41 0x6c 0x6c 0x20 0x61 0x64 0x64 0x72 0x65 0x73 0x73 0x65 0x73 0x20 \
 0x77 0x65 0x72 0x65 0x20 0x61 0x73 0x73 0x69 0x67 0x6e 0x65 0x64 0x2e"

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0xb3"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0xb7"
}

# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated after calculated 

set ReplyPayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $IAforNA $ServerId $DNSServer \
                 $DomainSearchList]

puts $ReplyPayloadData
#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 179
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 183
}
  
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $ReplyPayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $ReplyPayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]

if {$DuidType != "0x00 0x04"} {
  set TempList [concat $TempList1 $TempList2 "b3" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "b7" "11"]
}
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

set ReplyPayloadData [lreplace $ReplyPayloadData 6 7 $checksum2 $checksum1]
puts $ReplyPayloadData

return $ReplyPayloadData  
}

#
# CreateDHCP6ReplyPayloadData2 for request message with two Ipv6 addresses assigned to client.
#
proc CreateDHCP6ReplyPayloadData2 { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Reply payload. 
# Fixed Length should be 0xcf (207) DUID Type 1 - 3. 0xd3 (211) DUID Type 4 
#
set MessageType 0x07
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f 0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Domain Search List
#
set DomainSearchList "\
0x00 0x18 0x00 0x0d 0x07 0x65 0x78 0x61 0x6d 0x70 0x6c 0x65 0x03 0x63 0x6f 0x6d 0x00"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

#
# DHCPv6 Option: Identity Association for Non-temporary Address
# count from 0:(B2-3)option length=102,(B8-11)T1=2000,(B12-15)T2=3000,(B16-43)info of first Ipv6 address,\ 
# (B44-71)info of second Ipv6 address,[(B36-39)preferred 
# lifetime=3600,(B40-43)valid lifetime=7200]
set IAforNA "\
 0x00 0x03 0x00 0x66 0x00 0x00 0x00 0x01 0x00 0x00 0x07 0xd0 0x00 0x00 0x0b 0xb8 \
 0x00 0x05 0x00 0x18 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 \
 0x01 0x47 0x52 0x7d 0x00 0x00 0x0e 0x10 0x00 0x00 0x1c 0x20 0x00 0x05 0x00 0x18 \
 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 0x01 0x47 0x52 0x7c \
 0x00 0x00 0x0e 0x10 0x00 0x00 0x1c 0x20 0x00 0x0d 0x00 0x1e 0x00 0x00 0x41 0x6c \
 0x6c 0x20 0x61 0x64 0x64 0x72 0x65 0x73 0x73 0x65 0x73 0x20  0x77  0x65 0x72 0x65 \
 0x20 0x61 0x73 0x73 0x69 0x67 0x6e 0x65 0x64 0x2e"

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0xcf"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0xd3"
}

# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated

set ReplyPayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $IAforNA $ServerId $DNSServer \
                 $DomainSearchList]

puts $ReplyPayloadData
#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 207
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 211
}
  
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $ReplyPayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $ReplyPayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]
if {$DuidType != "0x00 0x04"} {
  set TempList [concat $TempList1 $TempList2 "cf" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "d3" "11"]
}
  
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

set ReplyPayloadData [lreplace $ReplyPayloadData 6 7 $checksum2 $checksum1]
puts $ReplyPayloadData

return $ReplyPayloadData  
}

#
# Create Dhcp6InfoReqReplyPayloadData to reply Dhcp6InfoRequest message
#
proc CreateDHCP6InfoReqReplyPayloadData { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Reply payload. 
# Fixed Length 0x68 (104) DUID Type 1 - 3. 0x6c(108) DUID Type 4
#
set MessageType 0x07
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x01 0x10 0x41 0x8a 0x34 0x00 0x11 0x11 0x34  0xb8 0xcf"

#
# DHCPv6 Option: DHCP option 51
#
set DHCPoption51 "0x00 0x33 0x00 0x10 0xfe 0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x02 0x11 0x11 0xff 0xfe 0x34 0xb8 0xcf"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0x68"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0x6c"
}
# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated after calculated 

set InfoReqReplyPayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $DNSServer $DHCPoption51 $ServerId \
                 ]

puts $InfoReqReplyPayloadData
#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 104
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 108
}
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $InfoReqReplyPayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $InfoReqReplyPayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]

if {$DuidType != "0x00 0x04"} {
  #
  # "68" is Payload length and "11" is next header(UDP)
  #
  set TempList [concat $TempList1 $TempList2 "68" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "6c" "11"]
}
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

#Update checksum,replace 0x00 0x00 to what we have calculated checksum2 and checksum1
set InfoReqReplyPayloadData [lreplace $InfoReqReplyPayloadData 6 7 $checksum2 $checksum1]
puts $InfoReqReplyPayloadData

return $InfoReqReplyPayloadData  
}

#
# Create Dhcp6RenewReplyPayloadData to reply Dhcp6Renew message
#
proc CreateDHCP6RenewReplyPayloadData { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 RenwReply payload. 
# Fixed Length 0x92 (146) DUID Type 1 - 3. 0x96 (150) DUID Type 4
#
set MessageType 0x07
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f  0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Identity Association for Non-temporary Address
#
set IAforNA "\
0x00 0x03 0x00 0x5e 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x14 0x00 0x00 0x00 0x1e \
0x00 0x05 0x00 0x18 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x14 0xda 0xd8 0x37 \
0x01 0x47 0x52 0x7d 0x00 0x00 0x00 0x24 0x00 0x00 0x00 0x48 0x00 0x0d 0x00 0x32 \
0x00 0x00 0x41 0x64 0x64 0x72 0x65 0x73 0x73 0x28 0x65 0x73 0x29 0x20 0x72 0x65 \
0x6e 0x65 0x77 0x65 0x64 0x2e 0x20 0x47 0x72 0x65 0x65 0x74 0x69 0x6e 0x67 0x73 \
0x20 0x66 0x72 0x6f 0x6d 0x20 0x70 0x6c 0x61 0x6e 0x65 0x74 0x20 0x45 0x61 0x72 \
0x74 0x68"

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0x92"
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0x96"
}
  
# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated after calculated 

set RenewReplyPayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                           $MessageType $TransId_and_ClientId $ServerId $IAforNA ]

puts $RenewReplyPayloadData
#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 146
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 150
}
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $RenewReplyPayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $RenewReplyPayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]

if {$DuidType != "0x00 0x04"} {
  #
  # "92" is Payload length and "11" is next header(UDP)
  #
  set TempList [concat $TempList1 $TempList2 "92" "11"]
} else {
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "96" "11"]
}
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

#Update checksum,replace 0x00 0x00 to what we have calculated checksum2 and checksum1
set RenewReplyPayloadData [lreplace $RenewReplyPayloadData 6 7 $checksum2 $checksum1]
puts $RenewReplyPayloadData

return $RenewReplyPayloadData  
}

#
# CreateDHCP6DeclineReplyPayloadData for Decline message with all Ipv6 address assigned being declined.
#
proc CreateDHCP6DeclineReplyPayloadData { RemoteIP LocalIP TransId_and_ClientId } { 

#
# Create DHCP6 Reply payload. 
# Fixed Length 0x97 (151) DUID Type 1 - 3. 0x9b (155) DUID Type 4
#
set MessageType 0x07
set DuidType [lrange $TransId_and_ClientId 7 8]

#
# DHCPv6 Option: Server Identifier
#
set ServerId "0x00 0x02 0x00 0x0e 0x00 0x01 0x00 0x06 0x0f 0x7b 0x6c 0xdc 0x00 0x10 0xc6 0xab  0xee 0xe0"

#
# DHCPv6 Option: Domain Search List
#
set DomainSearchList "\
0x00 0x18 0x00 0x0d 0x07 0x65 0x78 0x61 0x6d 0x70 0x6c 0x65 0x03 0x63 0x6f 0x6d 0x00"

#
# DHCPv6 Option: DNS recursive name server
#
set DNSServer "\
0x00 0x17 0x00 0x20 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xff 0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 \
 0x00 0x00 0x00 0xfe" 

#
# DHCPV6 Option:Identity Association for Non-temporary Address with no IA address option.
#
 set IAforNA "\
 0x00 0x03 0x00 0x2e 0x00 0x00 0x00 0x01 0x00 0x00 0x00 0x0a 0x00 0x00 0x00 0x0f \
 0x00 0x0d 0x00 0x1e 0x00 0x00 0x41 0x6c 0x6c 0x20 0x61 0x64 0x64 0x72 0x65 0x73 \
 0x73 0x65 0x73 0x20  0x77 0x65 0x72 0x65 0x20 0x61 0x73 0x73 0x69 0x67 0x6e 0x65 \
 0x64 0x2e"

# Fixed Length for this implemention
if {$DuidType != "0x00 0x04"} {
  set UdpLength     "0x00 0x97"
} else { 
  #
  # New DHCP6 DUID-UUID type
  #
  set UdpLength     "0x00 0x9b"
}
# Checksum will be calculate below
set UdpCheckSum   "0x00 0x00"; # to be updated

set ReplyPayloadData [concat 0x02 0x23 0x02 0x22 $UdpLength $UdpCheckSum \
                 $MessageType $TransId_and_ClientId $IAforNA $ServerId $DNSServer \
                 $DomainSearchList]

puts $ReplyPayloadData
#
# Calculate the checksum: UDP header and UDP payload. Pseudo header will be added below
#
if {$DuidType != "0x00 0x04"} {
  set PayloadDataLength 151
} else {  
  #
  # New DHCP6 DUID-UUID type
  #
  set PayloadDataLength 155
}
set i 0
set sum 0
while { $i < $PayloadDataLength } {
  set sum [ expr { $sum + [ expr { [lindex $ReplyPayloadData $i] << 8 } ] } ]   
  incr i
  if { $i < $PayloadDataLength } {
    set sum [ expr { $sum + [lindex $ReplyPayloadData $i] } ]
    incr i        
  }
}

puts "part of the check sum: $sum"

#
# Check sum adds Pseudo header: two IPs and UDP-length and Next header (0x11)
#
set TempList1 [split $LocalIP :]

set TempList2 [split $RemoteIP :]
if {$DuidType != "0x00 0x04"} {
  set TempList [concat $TempList1 $TempList2 "97" "11"]
} else {  
  #
  # New DHCP6 DUID-UUID type
  #
  set TempList [concat $TempList1 $TempList2 "9b" "11"]
}
set sum2 0
for {set i 0} { $i < [ llength $TempList] } { incr i } {
  set temp [ format "0x0%s" [ lindex $TempList $i]]
  set sum2 [expr {$sum2 + $temp}]
}
set sum2 [format "0x%x" $sum2]
set sum [expr {$sum + $sum2}]
set sum [format "0x%x" $sum]
puts $sum

while {[expr {$sum >> 16}] != 0} {
  set sumLow16Bit [expr {$sum & 0xffff}]
  set sumHigh16Bit [expr {$sum >> 16}]
  set sum [expr {$sumLow16Bit + $sumHigh16Bit}]
}
set sum [expr {~ $sum}]
set sum [format "0x%x" $sum]
puts "Final Check sum:"
puts $sum

set checksum1 [expr { $sum & 0xff}]
set checksum1 [format "0x%x" $checksum1]
puts $checksum1
set checksum2 [expr [expr { $sum >> 8}] & 0xff]
set checksum2 [format "0x%x" $checksum2]
puts $checksum2

set ReplyPayloadData [lreplace $ReplyPayloadData 6 7 $checksum2 $checksum1]
puts $ReplyPayloadData

return $ReplyPayloadData  
}
