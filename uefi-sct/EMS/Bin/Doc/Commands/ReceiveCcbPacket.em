Name
ReceiveCcbPacket - Receive a packet from the received capture control block
Usage
ReceiveCcbPacket Name PacketName timeout
Description
Name  
  The name of capture control block. The command should only use the capture 
control block created by startCapture command.
Timeout
  This argument is used to specify the timeout value. Once a packet matching
the configured filter has been captured or the timer expires, it will return.
PacketName
  The name you want to indicate the received packet, and the packet will add
to the EMS packet queue.
Example 
ReceiveCcbPacket  CCB  Ipv6Packet 10
