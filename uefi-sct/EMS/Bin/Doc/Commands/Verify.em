Name
Verify - Veriry signature of hashed data
Usage
Verify hash_handle key_handle signature
Description
[in] hash_handle: The name of the hash handle to be signed.
[in] key_handle : The key handle to store the key used in signature.
[in] signature  : The signature data to be verified. 
Notes
Example
CreatePayload src string 3 abc
GenHash sha sha_hash_handle
Hash sha_hash_handle src sha_hash_value
Sign rsa sha_hash_handle sha_sign_value key_handle2
DumpPacket sha_sign_value
puts [Verify sha_hash_handle key_handle2 sha_sign_value]
See also
GenHash Hash Sign
