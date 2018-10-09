Name
RemoteRecv - Receive response message from EFI Side.
Usage
RemoteRecv [-t timeout]
Description: 


This routines allow TCL script to get response message from EFI-Side acrosss the
serial. When RemoteRecv is called,  once reponse message is received within 
timeout, its relative elet operation result is returned in the variable of 
'elet_result', the relative log information is loged locally, AND other out 
parameters is also returned.

-t timeout: The parameter is used to define the timeout.The unit used in timeout
            is second.

Notes
Elet: a kind of EFI Appllication.
Example
RemoteRecv -t 10
See also
RemoteCall
