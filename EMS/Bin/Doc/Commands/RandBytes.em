Name
RandBytes - Generate random data block
Usage
RandBytes bytes dst
Description
The command RandBytes generates a random data block of size bytes and stores the 
result in dst payload. The old data in dst payload will be destroyed. If dst 
payload does not exist, one new payload named dst will be create.

bytes
Size of the random data block to generate.
dst
This argument is used to specify the name of the destination payload.
Return value
None
Notes

Example
Random 32 SessionKey  
See also
