Name
StartCapture - Start to capture packet
Usage
StartCapture  Name  Filter
Description
Name 
  The name for capture control block to be create
Filter
  The syntax of the filter is identical that the WinPcap use. For detail syntax, please refer to 
	http://winpcap.mirror.ethereal.com/301a/docs/group__language.html
Example 
set L_Filter "ip6 host ac:10:d2:a3::"
StartCapture CCB $L_Filter
