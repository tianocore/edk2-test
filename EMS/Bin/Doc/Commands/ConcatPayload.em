Name
ConcatPayload - Concatenate multiple data blocks
Usage
ConcatPayload dst src...
Description
The command ConcatPayload concatenates the multiple src payloads and store the 
result in dst payload. The old data in dst payload will be destroyed. If dst 
payload does not exist, one new payload named dst will be create.

dst
This argument is used to specify the name of the destination payload.
src
This argument is used to indicate the source payload.
Return value
None
Notes

Example
ConcatPayload Dest1 Src1 Src2  ;# Dest1 := Src1|Src2
ConcatPayload Dest1 Dest1 Src1 ;# Dest1 := Dest1|Src1
ConcatPayload Dest1 Src1       ;# Dest1 := Src1

See also
CreatePayload SplitPayload CompPayload XorPayload DestroyPacket
