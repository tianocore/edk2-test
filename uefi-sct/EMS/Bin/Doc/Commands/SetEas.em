Name
SetEas - specify the MAC address of communication peer, and setup control channel with the peer.
Usage
SetEas -T target
Description
target		MAC address of the communication peer.
Notes
If you specify target, only if the target is alive and send response in time, the communication channel can be setup. If you want to send control information out, you must OpenDev at first
Example
OpenDev "eth0"
SetEas -T 0:7:1F:C3:2D:10
See also
OpenDev SetEas
