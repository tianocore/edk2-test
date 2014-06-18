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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
 
  EftpOption.h
 
Abstract:
  Eftp Option process functions
--*/

#ifndef _EFI_EFTP_OPTION_H_
#define _EFI_EFTP_OPTION_H_

typedef enum {
  EFTP_UNICAST= 1,
} EFTP_TRANSFER_TYPE;

//
// Change the macros and the OptionObjs array at the same time
//
enum {
  EFTP_OPTION_TSIZE   = 0,
  EFTP_OPTION_TIMEOUT,
  EFTP_OPTION_BLKSIZE,
  EFTP_OPTION_MCAST,
  EFTP_OPTION_BIGBLKNO,
  EFTP_OPTION_STREAM,
  EFTP_OPTION_PKTDELAY,
  EFTP_OPTION_MAX,
};

typedef struct _EFTP_OPTION {
  UINT16              Timeout;
  UINT16              BlkSize;
  UINT16              BlknoLen;
  EFTP_TRANSFER_TYPE  TransferType;
  EFTP_PEER_ADDR      McastChannel;
  UINT64              Tsize;
  UINT16              Pktdelay;
  UINT16              NBlkInStream;
  UINT64              Exist;  // This is a flag marking whether an option exists in the packet
} EFTP_OPTION;

//
// ExtractOption is called to extract the options from the tftp packet,
// it will do some basic validation, such as whether the bigblk# is 8.
// VerifyOption is called after all the options have been extracted
// from the packet, it intends to validate the relationship between the options.
//
typedef
EFI_STATUS
(*ExtractOption) (
  OUT EFTP_OPTION * Opt,
  IN CHAR8        *Str
  );

typedef
EFI_STATUS
(*VerifyOption) (
  OUT EFTP_OPTION * Opt
  );

typedef struct _EFTP_OPTIONOBJ {
  UINTN         Index;
  CHAR8         *Name;
  ExtractOption Extract;
  VerifyOption  Verify;
} EFTP_OPTIONOBJ;

#define IS_DIGIT(Ch)  (((Ch) >= '0') && ((Ch) <= '9'))

VOID
EftpInitOption (
  IN EFTP_OPTION*Opt
  )
/*++

Routine Description:

  Initalize the EFTP_OPTION structure

Arguments:

  Opt - Option structure to initialize

Returns:

  NONE

--*/
;

EFI_STATUS
EftpGetOptions (
  IN EFI_EFTP_PROTOCOL     *This,
  IN UINT32                PacketLen,
  IN EFI_EFTP_PACKET       *Packet,
  IN OUT UINT32            *OptionCount,
  OUT EFI_EFTP_OPTION      **OptionList
  )
/*++

Routine Description:

  Parse the options in the packet(OACK/RRQ/WRQ) to name/value pairs.

Arguments:

  This         - The Eftp protocol
  PacketLen    - The length of the packet
  Packet       - The packet
  OptionCount  - The interger variable to store number of options.
  OptionList   - The memory buffer to store the name/value pairs. The caller should release it.

Returns:

  EFI_INVALID_PARAMETER  - Not correct parameters or packet head
  EFI_PROTOCOL_ERROR     - Mal-form packet provided
  EFI_SUCCESS            - Options are successfully parsed
  Others                 - Failed to allocate memory for the buffer.
  
--*/
;

EFI_STATUS
EftpExtractOptions (
  IN EFI_EFTP_PROTOCOL     *This,
  IN EFTP_OPTION           *Option,
  IN EFI_EFTP_PACKET       *Packet,
  IN UINT32                PacketLen
  )
/*++

Routine Description:

  Extract the options from the packet, and check whether they are OK

Arguments:

  This            - The eftp protocol
  Option          - Option structure to fill extracted options.
  Packet          - Packet to extract options from
  PacketLen       - Packet length

Returns:

  EFI_INVALID_PARAMETER - Packet is mal-formed
  EFI_SUCCESS           - Successfully extracted the option from packet

--*/
;

EFI_STATUS
EftpCheckOption (
  IN EFI_EFTP_OPTION             *OptionList,
  IN UINT32                      OptionCount,
  IN UINT16                      OpCode
  )
/*++

Routine Description:

  Check whether user provided options are well-formed

Arguments:

  OptionList   - The list of option to check
  OptionCount  - The number of options in the option list
  OpCode       - OpCode the options are to be used with

Returns:

  EFI_INVALID_PARAMETER - Invalid paramter, for example, null option point, 
                          multicast option in WRQ.
  EFI_UNSUPPORTED       - Unsupported options in the option list.
  EFI_SUCCESS           - Options are OK.

--*/
;

#endif
