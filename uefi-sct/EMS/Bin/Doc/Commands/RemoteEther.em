Name
RemoteEther - Set/display the default remote Ethernet address 
Usage
RemoteEther [MacAddress]
Description
MacAddress - XX:XX:XX:XX:XX:XX
Specify the default remote Ethernet address in hexadecimal format, this address 
will be used in all packets created by command CreatePacket as Ethernet destination 
address.
If none argument specified, this command will display the current configuration.

Notes
If the option -Eth_dst is specified in creating Ethernet packet, this value will be
overridden. 
In the IGMP packets, this value will be overridden by that worked out from specified 
destination IP address.
Example
RemoteEther 12:23:34:45:56:67
See also
LocalEther CreatePacket
