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

  IPsecConfigDataIp6Transport.h

Abstract:

  IPsec Config Data for Transport Mode from the UEFI 2.3 specification.

--*/

#ifndef _IPSEC_CONFIG_DATA_IP6_TRANSPORT_H_
#define _IPSEC_CONFIG_DATA_IP6_TRANSPORT_H_


extern EFI_IPSEC_PROCESS_POLICY InBoundProcessingPolicyIp6Transport;
extern EFI_IPSEC_PROCESS_POLICY OutBoundProcessingPolicyIp6Transport;


extern EFI_IP_ADDRESS_INFO LocalAddressIp6Transport;
extern EFI_IP_ADDRESS_INFO RemoteAddressIp6Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSpdSelectorIp6Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSpdSelectorIp6Transport;

extern EFI_IPSEC_CONFIG_SELECTOR InBoundSadSelectorIp6Transport;
extern EFI_IPSEC_CONFIG_SELECTOR OutBoundSadSelectorIp6Transport;


extern CHAR8  InBoundEncKeyIp6Transport[128]; 
extern CHAR8  InBoundAuthKeyIp6Transport[128];
extern CHAR8  OutBoundEncKeyIp6Transport[128]; 
extern CHAR8  OutBoundAuthKeyIp6Transport[128];

extern EFI_IPSEC_SA_DATA2 InBoundSadIp6Transport;
extern EFI_IPSEC_SA_DATA2 OutBoundSadIp6Transport;

extern EFI_IPSEC_SPD_DATA OutBoundSpdIp6Transport;
extern EFI_IPSEC_SPD_DATA InBoundSpdIp6Transport;

#endif

