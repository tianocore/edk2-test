Name
LocalIp - Set/display the default local IP address
Usage
LocalIp [IpAddress]
Description
IpAddress 
Specify the default local IP address, this address will be used in all IP packets
created by command CreatePacket as IP source address.
If none argument specified, this command will display the current configuration.
Notes
If the option -Ip_src is specified in creating IP packet, this value will be 
overridden. 
Example
LocalIp 192.168.8.1
See also
RemoteIp CreatePacket
