Name
CaptureMultiPacket - Capture multiple packets in specified time.
Usage
CaptureMultiPacket number -t timeout
Description
This command is used to capture multiple packet in specified time.  SetFilter 
MUST have been invoked before this command.

number
This argument is used to specify the number of packets to capture.
timeout
This argument is used to specify the timeout value. Once the number of packets 
matching the configured filter has been captured or the timer expires, it will 
return. 
Return value
This command will return the count of captured packets
Notes
Example
SetFilter "ip"
set count [CapturePacket 10 -t 10]
if { $count == 10} {
RecordAssertion pass "Example" "Got 10 IP packets"
} else {
RecordAssertion fail "Example" " Got $count IP packets "
}
See also
SetFilter ValidatePacket ParsePacket CapturePacket
