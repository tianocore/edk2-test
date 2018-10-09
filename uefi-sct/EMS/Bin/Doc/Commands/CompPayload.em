Name
CompPayload - Comapre two data blocks
Usage
CompPayload Payload1 Payload2 [Len]
Description
The command CompPayload compare two payload in "Len" of bytes.

Return value
0,  if the payloads are identical
-1, if the payloads are not identical
Notes

Example
if { [CompPayload P1 P2] == 0 } {
  puts "P1 == P2"
}
See also
CreatePayload SplitPayload ConcatPayload XorPayload DestroyPacket
