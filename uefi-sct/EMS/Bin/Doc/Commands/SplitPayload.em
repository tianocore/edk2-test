Name
SplitPayload - Split a payload and extract a part from it
Usage
SplitPayload dst src head tail
Description
The command SplitPayload extracts a part of the src payload and stores the 
result in dst payload. The old data in dst payload will be destroyed. If dst 
payload does not exist, one new payload named dst will be create.

dst
This argument is used to specify the name of the destination payload.
src
This argument is used to indicate the source payload.
Head
This argument should be a number or "Start", used to indicate the start point to
extract.
Tail
This argument should be a number or "End", used to indicate the end point to 
extract.
Return value
None
Notes

Example
SplitPayload Dest1 Src1 0 9       ;# Dest1 := Src1[0..9]
SplitPayload Dest1 Src1 Start 9   ;# Dest1 := Src1[0..9]
SplitPayload Dest1 Dst1 10 End    ;# Dest1 := Src1[10..sizeof(Src1)]

See also
CreatePayload ConcatPayload CompPayload XorPayload DestroyPacket

