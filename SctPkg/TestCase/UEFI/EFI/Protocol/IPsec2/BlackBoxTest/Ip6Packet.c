/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  Ip6packet.c

Abstract:

--*/
//
// This is a IP4 Packet for TCP 
// 

#include "Efi.h"

UINT8 Ip6PacketTcp[] = 
{                   
                                                                                    0x60, 0x00,  
0x00, 0x00, 0x00, 0x28, 0x06, 0xff, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x43, 0x21, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0xee, 0x22, 0xb8, 0x19, 0xc5, 0x6d, 0xfd, 0x00, 0x00,  
0x00, 0x01, 0x50, 0x10, 0x80, 0x00, 0xfd, 0x2f, 0x00, 0x00, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x57,  
0x6f, 0x72, 0x6c, 0x64, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x57, 0x6f, 0x72, 0x6c, 0x64 
};

UINT32 Ip6PacketTcpSize = sizeof(Ip6PacketTcp);

UINT8 Ip6PacketUdp[] = 
{
                                                                                    0x60, 0x00,   
0x00, 0x00, 0x00, 0x26, 0x11, 0x40, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   
0x00, 0x00, 0x00, 0x00, 0x43, 0x21, 0x20, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0xf4, 0x06, 0xf5, 0x00, 0x26, 0xd2, 0xcf, 0x55, 0x64,   
0x70, 0x36, 0x54, 0x65, 0x73, 0x74, 0x42, 0x75, 0x66, 0x66, 0x65, 0x72, 0x00, 0x00, 0x00, 0x00,   
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

UINT32 Ip6PacketUdpSize = sizeof(Ip6PacketUdp);

