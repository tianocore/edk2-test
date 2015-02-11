Name
LocalIpv6 - Set/Display the default local Ipv6 address
Usage
LocalIpv6 [Ipv6Address]
Description
Ipv6Address 
  Specify the default local IPv6 address, this address will 
be used in all IPv6 packets created by command CreatePacket as
IPv6 source address. If none argument specified, this command 
will display the current configuration.
Notes
If the option ¨CIpv6_src is specified in creating IPv6 packet, 
this value will be overridden. 
Example 
LocalIPv6  ac:10:d2:a3::

