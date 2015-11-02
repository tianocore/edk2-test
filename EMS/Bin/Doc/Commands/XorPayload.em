Name
XorPayload - Do a bitwise exclusive OR operation on two payloads
Usage
XorPayload dst src1 src2
Description
The command XorPayload does a bitwise exclusive OR operation on the src1 and 
src2 payloads and stores the result in dst payload. The old data in dst payload 
will be destroyed. If dst payload does not exist, one new payload named dst will 
be create.

dst
This argument is used to specify the name of the destination payload.
Src1
This argument is used to indicate the first source payload.
Src2
This argument is used to indicate the second source payload.

Return value
None
Notes
The length of the two source payload MUST be same.
Example
XorPayload Dest1 Src1 Src2        ;# Dest1 := Src1^Src2
See also
CreatePayload ConcatPayload CompPayload SplitPayload DestroyPacket

