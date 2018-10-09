Name
CapturePacket - Capture a packet and assign it a name.
Usage
CapturePacket packetname -t timeout
Description
This command is used to capture a packet in specified time.  SetFilter MUST have
been invoked before this command.

packetname
	This argument is used to specify the name of the captured packet. It can
	be used for command ValidatePacket or ParsePacket etc..
timeout
	This argument is used to specify the timeout value. Once a packet matching
	the configured filter has been captured or the timer expires, it will 
	return. 
Return value
This command will return the count of captured packets, "0" or "1".
Notes
Example
SetFilter "ip proto \\igmp"
if {[ CapturePacket p1 -t 10] == 1} {
RecordAssertion pass "Example" "Got an IGMP packet"
} else {
RecordAssertion fail "Example" "Cannot see any IGMP packet"
}
See also
SetFilter ValidatePacket ParsePacket CaptureMultiPacket
