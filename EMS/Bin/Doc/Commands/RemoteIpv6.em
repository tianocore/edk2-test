Name
RemoteIpv6 - Set/display the default remote IPv6 address
Usage
RemoteIpv6 [Ipv6Address]
Description
Ipv6Address 
  Specify the default remote IPv6 address, this address will 
be used in all IPv6 packets created by command CreatePacket as 
IPv6 destination address. If none argument specified, this 
command will display the current configuration.
Notes
If the option ¨CIpv6_dst is specified in creating IPv6 packet, 
this value will be overridden. 
Example 
RemoteIPv6  ac:10:d2:a3::

