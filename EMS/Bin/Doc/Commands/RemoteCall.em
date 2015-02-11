Name
RemoteCall - Make remote call on another EFI over the serial port.
Usage
RemoteCall EletName [-in parameter-list] [-out parameter-list]
Description
This routines allow TCL script to make procedure call on other EFI across the 
serial. First, the script call this routine to send command out through the 
serial port. Upon receipt of the command, the dispatch routine in EFI perform 
the requested operation, and then send back a reply. The reply is received 
through another routine, RemoteRecv.

EletName: specifies which operation will be called in the EFI Side.
-in parameter-list: specifies input parameter list for the Elet
    Fortmat of input parameter:
        The format is Name=Value. Different parameter is seperated with space.
        The value is represented with character string. The value begin with 
        Oridinary Character (not @) can be directly accessed from the message; 
        And other value begining with Convension Character (@) will result in 
        fetching relative value in the varialist in the EFI-Side.
-out parameter-list: specifies output parameter list for the Elet. 
    Format of output parameter:
        The format is Name=VarName. Different parameter is seperated with space.
        'NAME' is the input parameter name of Elet. VarName is an variable name 
        defined in script. The Value for parameter whose VarName beginning with 
        Oridinary Character(not @) is returned in the response message, can be 
        accessed directly, the value for parameter whose VarName beginning with 
        Conversion Character (@) isn't returned in the response message. If the 
        VarName isn't specified, which means that variable name in both the 
        script and Elet is the same.
Notes
Elet: a kind of EFI Application.
Example
RemoteCall UdpWrite -in 0 172.16.220.28 66 NULL NULL NULL NULL NULL 128
"Udp_Write" -out Status
See also
RemoteRecv
