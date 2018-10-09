Name
CreatePayload - Create a data block
Usage
CreatePayload payloadname pattern length value...
Description
This command is used to create a data block.

payloadname
This argument is used to specify the name of the data block to create. 
pattern
This argument is used to indicate the pattern to create the block. It MUST be 
one of the following values:
"Const"   -	 
"Incr"    -	
"Decr"    -	
"Data"    -	
"String"  -	
Length
Length of the block to create in bytes.
Value
It is used as the base value to create the block.
Return value
None
Notes
Payloads and packets are stored in the same space. 
Example
CreatePayload payload0 Const  16 0x0
CreatePayload payload1 Incr   16 0x01
CreatePayload payload2 Decr   16 0xFF
CreatePayload payload3 Data   16 0x00 0x04 0x08 0x10 0x99 
CreatePayload payload1 String 16 {Tristan&Coco}

See also
ConcatPayload SplitPayload CompPayload XorPayload CreatePacket DestroyPacket
