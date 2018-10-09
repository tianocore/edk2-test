Name
SendPacket - Send a specified packet.
Usage
SendPacket packetname [-c repeat] [-d delay]
Description
repeat  The times to send the packet out.
Delay		Delay time to send the packet out. The unit is milli-second.
Notes
This command only can be used to send those packets created by command 
CreatePacket. If no repeat specified, the packet will be sent out only 
Once. If delay specified, the packet will be delayed sent out.

Example
CreatePacket packet1 -t eth -eth_type 0x0801
puts [SendPacket packet1 -c 20] ;# It will puts "20"
See also
CreatePacket
