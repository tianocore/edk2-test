Name
CreateTcb - Create a TCP Control Block
Usage
CreateTcb <name> <LocalIp> <LocalPort> <RemoteIp> <RemotePort>
Description
Notes
  Once a TCB is created, the following TCL variables are available:
  
  <TcbName>.l_state         /* local connection state , not used yet*/
  <TcbName>.r_state         /* expected remote connection state , not used yet */
  <TcbName>.l_mss;          /* local mss */
  <TcbName>.r_mss           /* remote advertised msss*/
  <TcbName>.l_ip
  <TcbName>.l_port
  <TcbName>.r_ip
  <TcbName>.r_port
  <TcbName>.l_sa_p          /* Local SACK permitted ?*/
  <TcbName>.r_sa_p          /* Remote SACK permitted ?*/
  <TcbName>.l_isn           /* Local ISN */
  <TcbName>.r_isn           /* Remote ISN */
  <TcbName>.r_f_cwr         /* The flags in the last received packet 1 or 0*/
  <TcbName>.r_f_ece
  <TcbName>.r_f_urg
  <TcbName>.r_f_ack
  <TcbName>.r_f_psh
  <TcbName>.r_f_rst
  <TcbName>.r_f_syn
  <TcbName>.r_f_fin
  <TcbName>.r_seq           /* The information in the last received packet */
  <TcbName>.r_ack
  <TcbName>.r_win
  <TcbName>.r_urg
  <TcbName>.r_len
  <TcbName>.l_win
  <TcbName>.r_error         /* Some thing wrong in the received packet */
  <TcbName>.l_next_seq      /* The sequence number, calculated by the last out packet */
  <TcbName>.l_max_seq       /* The max sequence number, has been sent out*/
  <TcbName>.l_acked_seq     /* The ACK sequence number, calculated by the last out packet */
  <TcbName>.l_max_acked_seq /* The MAX ACK sequence number, has been sent out */
  <TcbName>.r_next_seq      /* The sequence number received in the last packet */
  <TcbName>.r_max_seq       /* The MAX sequence number received*/
  <TcbName>.r_acked_seq     /* The ACK number in the last packet from peer */
  <TcbName>.r_max_acked_seq /* The MAX ACK number received */
  
Example
CreateTcb Tcb1 172.16.220.188 1398 172.16.220.94 9999 
See also
DestroyTcb SendTcpPacket UpdateTcpSendBuffer ReceiveTcpPacket

