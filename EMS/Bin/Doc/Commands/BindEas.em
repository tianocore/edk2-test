Name
BindEas - send Query out, collect response from alive EAS, and select one as communication peer.
Usage
BindEas -t timeout [-T target]
Description
timeout     total time used to collect response and selecting communication peer.
target		MAC address of the communication peer.
Notes
If you specify target, only if the target is alive and send response in time, the communication channel can be setup. If you want to send control information out, you must OpenDev at first
Example
OpenDev "eth0"
BindEas -t 10
See also
OpenDev SetEas
