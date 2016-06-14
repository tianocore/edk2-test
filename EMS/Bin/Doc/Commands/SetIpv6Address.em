Name
SetIpv6Address - Set a Ipv6Address to a variable
Usage
SetIpv6Address VariableName Ipv6Address
Description
VariableName
  A variable which will use to save the value of Ipv6 Address. 
This variable MUST be the type of EFI_IPv6_ADDRESS.
Ipv6Address
  The Ipv6 address.
Example 
EFI_IPv6_ADDRESS  TempIPV6
SetIpv6Address TempIPV6  ::ac:10:d2:a2

