Name
GenRandom - Generate random data block
Usage
GenRandom payload bytes
Description
The command generates a random data block of size bytes and stores the result in
payload. The old data in dst payload will be destroyed. If the payload does not 
exist, one new payload named dst will be create.

bytes   : [IN]  Size of the random data block to generate.
payload : [OUT] The name of the destination payload.

Return value
None
Notes
Example
GenRandom test_payload 32 
See also
CreatePayload DumpPayload DestroyPayload