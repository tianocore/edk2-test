Name
ValidatePacket - Validate the packet.
Usage
ValidatePacket packetname -t type pattern
Description
packetname
	Specify the packet to validate. This name should be identical to that 
	specified in command CapturePacket .
type
	Specify the protocol type of the packet. It decides how to unpack this 
	packet. Supported types are listed in command CreatePacket .
pattern
	This argument is used to specify the validate expression. All the 
	variables in the expression must be the field name of the protocol 
	specified by type. All the field names of different protocols are 
	listed in command CreatePacket. The logical operators supported 
	in this expression include "AND", "OR" and "NOT".
	Pattern example: 
	(Igmp_type=0x01)AND(Igmp_MaxResTime=600)AND(Igmp_ip=224.1.1.1)
Return value
This command will return "0" if validation result is pass, or "1" if validation 
result is fail.
Notes
Example
if {[ValidatePacket packet1 -t ip (ipv4_src=192.168.88.1)AND(ipv4_ver=4)] == 0} {
  бн ;#Pass
} else {
  бн ;#Fail
}
See also
CapturePacket ParsePacket DumpPacket
