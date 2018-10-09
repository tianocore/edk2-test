Name
ParsePacket - Parse the specified packet according to specified type.
Usage
ParsePacket PacketName -t Type [-FieldName VarName]бн
Description
Return value
This command will return the count of the fields being parsed.
Notes
1. The FieldName MUST be one of the options as described in command CreatePacket .
2. The variables created by this command are all Read-Only, so MUST NOT modify them. 
   Once one of them useless, please unset it as soon as possible.
Example
if {[ ParsePacket packet1 -t ip -ipv4_ver version -ipv4_src source] != 2} {
  бн ;# Something wring in parsing packet
}
if {$version != 4} {
  бн
} else if { [string compare -nocase $source 172.16.220.28] != 0 } {
  бн
}
See also
CapturePacket ValidatePacket
