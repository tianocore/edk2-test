Name
OpenDev - open a control channel, can be serial or network.
Usage
OpenDev devicename
Description
devicename:  "/dev/ttyS0" or "eth0"
Return 
Notes
Currently only "/dev/ttyS0" and "eth0" are supported. After communication peer found (See BindEas or SetEas), the control information can be sent to specified EAS.
Example
OpenDev "eth0"
BindEas -t 10
See also
BindEas SetEas
