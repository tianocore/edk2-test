Name
RemoteIp - Set/display the default remote IP address
Usage
RemoteIp [IpAddress]
Description
IpAddress 
Specify the default remote IP address, this address will be used in all IP packets
created by command CreatePacket as IP destination address.
If none argument specified, this command will display the current configuration.
Notes
If the option -Ip_dst is specified in creating IP packet, this value will be 
overridden. 
Example
RemoteIp 192.168.8.1
See also
LocalIp CreatePacket 
