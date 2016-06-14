Name
BuildTcpOption - Build a TCP option 
Usage
BuildTcpOption: BuildTcpOption <name> [options]
Description
    BuildTcpOption: BuildTcpOption <name> [options]
      Options: 
        -l/L  Options length 
        -m/M  MSS 
Notes
Example
BuildTcpOptions Option_MSS1460 -m 1460 -l 8
UpdateTcpSendBuffer Tcb1 -c 0x02 -o Option_MSS1460 ; #SYN
See also
UpdateTcpSendBuffer
