Name
CreatePacket - Create a packet to send.
Usage
CreatePacket packetname -t [type] [option＃]
Description
Packetname
  The name of the packet to create.

Type
  Specify what type packet to create. Ents now supports the following packet
  type: eth, eap, eapol, arp, ip, ipv4, icmp, igmp, udp, tcp, tftp, mtftp. 

Optionlist
  Type	Option name	Description		Default Value
  Eth	Eth_dst         
  Eth	Eth_src         
  Eth	Eth_type        
  Eth	Eth_payload     
  Eap	Eap_Code        
  Eap	Eap_identifier      
  Eap	Eap_type        
  Eap	Eap_typedata      
  Eapol	Eapol_type      
  Eapol	Eapol_ver       
  Eapol	Eapol_Payload
  Arp	Arp_hrd		Hardware type		ETH (0x01)
  Arp	Arp_pro		Protocol type		IP (0x0800)
  Arp	Arp_hln		Hardware address length	6
  Arp	Arp_pln		Protocol address length	4
  Arp	Arp_op		ARP operation		Mandatory
  Arp	Arp_sha		Sender hardware address	Mandatory
  Arp	Arp_spa		Sender protocol address	Mandatory
  Arp	Arp_tha		Target hardware address	Mandatory
  Arp	Arp_tpa		Target protocol address	Mandatory
  Arp	Arp_Payload
  Ip	IP_ver		IP version      0x04
  Ipv4	Ipv4_ver	Version			0x04
  Ipv4	Ipvr_ihl	Internet header length	0x05
  Ipv4	Ipv4_len	Total Length  
  Ipv4	Ipv4_tos	Type of service		0x00
  Ipv4	Ipv4_id		Identification  
  Ipv4	Ipv4_frag	Fragment information	0x00
  Ipv4	Ipv4_ttl	Time to live		0x40
  Ipv4	Ipv4_prot	Next level protocol	Mandatory
  Ipv4	Ipv4_sum	Checksum on the header  
  Ipv4	Ipv4_src	Source IP address 
  Ipv4	Ipv4_dst	Destination IP address  
  Ipv4	Ipv4_opts       
  Ipv4	Ipv4_payload
  Icmp	Icmp_type	ICMP message type	Mandatory
  Icmp	Icmp_code	ICMP message code	Mandatory
  Icmp	Icmp_chksum	Checksum on the header
  Icmp	Icmp_id		Message identifier	0x00
  Icmp	Icmp_seq	Message sequence	0x00
  Icmp	Icmp_mask	ICMP mask
  Icmp	Icmp_otime	Original timestamp
  Icmp	Icmp_rtime	Receive timestamp
  Icmp	Icmp_ttime	Transmit timestamp
  Icmp	Icmp_gateway	ICMP gateway
  Icmp	Icmp_orig_len	Original IP length
  Icmp	Icmp_orig_tos	Original IP TOS
  Icmp	Icmp_orig_id	Original IP ID
  Icmp	Icmp_orig_frag	Original IP fragment
  Icmp	Icmp_orig_ttl	Original IP TTL
  Icmp	Icmp_orig_prot	Original IP protocol
  Icmp	Icmp_orig_check	Original IP checksum
  Icmp	Icmp_orig_src	Original IP source
  Icmp	Icmp_orig_dst   Original IP destination
  Icmp	Icmp_payload
  Igmp	Igmp_type	IGMP message type	Mandatory
  Igmp	Igmp_MaxResTime	Max response time	0x00
  Igmp	Igmp_sum	Checksum  
  Igmp	Igmp_ip		Group Address		Mandatory
  Igmp	Igmp_payload
  Igmp	Igmp_srcip	Source IP   
  Igmp	Igmp_destip	Destination IP		224.0.0.1
  Udp 	Udp_sp		UDP source port		0x00
  Udp 	Udp_dp		UDP destination port	Mandatory
  Udp 	Udp_len		Length of user datagram 
  Udp 	Udp_sum		Checksum  
  Udp 	Udp_payload   
  Dhcp  Dhcp_op   op code of Dhcp packet Manadatory
  Dhcp  Dhcp_htype hardware address type
  Dhcp  Dhcp_hlen  hardware address len
  Dhcp  Dhcp_hops  hops
  Dhcp  Dhcp_xid   transition Id   Manadatory
  Dhcp  Dhcp_secs  secs
  Dhcp  Dhcp_flags flag
  Dhcp  Dhcp_ciaddr client IP address
  Dhcp  Dhcp_yiaddr your IP address
  Dhcp  Dhcp_siaddr server IP address
  Dhcp  Dhcp_giaddr gateway IP address
  Dhcp  Dhcp_chaddr client hardware address
  Dhcp  Dhcp_sname  server name
  Dhcp  Dhcp_file   file name
  Dhcp  Dhcp_magic  magic number
  Dhcp  Dhcp_options option payload
  Dhcp  Dhcp_sport  source port used in UDP header
  Dhcp  Dhcp_dport  desination port used in UDP head

        Name          Description                         Mandatory   Default
                                                                           
  Tcp 	Tcp_sp        TCP source port                     FALSE       0x00   
  Tcp 	Tcp_dp        TCP destination port                TRUE               
  Tcp 	Tcp_seq       sequence number                     FALSE       0x00   
  Tcp 	Tcp_ack       acknowledgement number              FALSE       0x00   
  Tcp   Tcp_offset    Data offset                         FALSE       *      
  Tcp   Tcp_control   control flags                       FALSE       0x00   
  Tcp   Tcp_win       window size                         FALSE       0x400  
  Tcp   Tcp_sum       checksum (0 for libnet to autofill) FALSE       0x00   
  Tcp   Tcp_urg       urgent pointer                      FALSE       0x00   
  Tcp   Tcp_options   byte string of TCP options          FALSE       NULL   
  Tcp 	Tcp_payload   TCP payload                         FALSE       NULL   

  *Note: Tcp_offset item cann't be configured currently due to libnet doesn't 
         support.
  Tftp
  Mtftp

Notes:
Explicit option [-IP_ver 0x06] can be used to create packet over Ipv6. 
Example:
Create a TCP packet over Ipv6
  CreatePacket Packet 每t tcp 每IP_ver 0x06 每tcp_control 0x01 每tcp_payload Payload
Create a TCP packet over Ipv4
  CreatePacket Packet -t tcp -tcp_control 0x01 -tcp_payload Payload
See also
SendPacket DumpPacket
