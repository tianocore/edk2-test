Name
SetFilter - Set filter for packet capturer.
Usage
SetFilter filter
Description
Notes
The syntax of the filter is identical to that of tcpdump in UNIX, whose manual 
can be found at www.tcpdump.org.
Example
SetFilter "ip proto \\igmp"
See also
CapturePacket
