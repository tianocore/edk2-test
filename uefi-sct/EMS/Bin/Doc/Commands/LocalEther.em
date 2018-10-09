Name
LocalEther - Set/display the default local Ethernet address
Usage
LocalEther [MacAddress]
Description
MacAddress - XX:X:XX:XX:XX:XX 
Specify the default local Ethernet address in hexadecimal format, this address 
will be used in all packets created by command CreatePacket as Ethernet source 
address.
If none argument specified, this command will display the current configuration.
Notes
If the option -Eth_src is specified in creating Ethernet packet, this value will
be overridden. 
Example
LocalEther 12:23:34:45:56:67
See also
RemoteEther CreatePacket
