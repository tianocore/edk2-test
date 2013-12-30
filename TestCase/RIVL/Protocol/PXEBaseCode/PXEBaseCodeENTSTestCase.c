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

  PXEBaseCodeENTSTestCase.c

Abstract:

--*/

#include "PXEBaseCodeENTSTestCase.h"

//
// PXEBaseCode.Start
//
static BOOLEAN    StartUseIpv6;
static EFI_STATUS *StartStatus;

ENTS_ARG_FIELD    gPXEBaseCodeStartArgField[] = {
  {
    BOOL,
    &StartUseIpv6
  },
  {
    POINTER,
    &StartStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeStart_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStart Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *StartStatus = PXEBaseCode->Start (
                                PXEBaseCode,
                                StartUseIpv6
                                );
  RecordMessage (
    &gPXEBaseCodeEntsRuntimeInfo,
    &gPXEBaseCodeEntsRuntimeInfoSize,
    L"Status - %r",
    *StartStatus
    );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.Stop
//
static EFI_STATUS *StopStatus;

ENTS_ARG_FIELD    gPXEBaseCodeStopArgField[] = {
  {
    POINTER,
    &StopStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeStop_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeStop Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *StopStatus = PXEBaseCode->Stop (PXEBaseCode);
  RecordMessage (
    &gPXEBaseCodeEntsRuntimeInfo,
    &gPXEBaseCodeEntsRuntimeInfoSize,
    L"Status - %r",
    *StopStatus
    );

  return EFI_SUCCESS;
}

//
// PXEBaseCode.Dhcp
//
static BOOLEAN    DhcpSortOffers;
static EFI_STATUS *DhcpStatus;

ENTS_ARG_FIELD    gPXEBaseCodeDhcpArgField[] = {
  {
    BOOL,
    &DhcpSortOffers
  },
  {
    POINTER,
    &DhcpStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeDhcp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDhcp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *DhcpStatus = PXEBaseCode->Dhcp (
                              PXEBaseCode,
                              DhcpSortOffers
                              );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.Discover
//
static UINT16                           DiscoverType;
static UINT16                           *DiscoverLayer;
static BOOLEAN                          DiscoverUseBis;
static EFI_PXE_BASE_CODE_DISCOVER_INFO  *DiscoverInfo;
static EFI_STATUS                       *DiscoverStatus;

ENTS_ARG_FIELD                          gPXEBaseCodeDiscoverArgField[] = {
  {
    OCTET2,
    &DiscoverType
  },
  {
    POINTER,
    &DiscoverLayer
  },
  {
    BOOL,
    &DiscoverUseBis
  },
  {
    POINTER,
    &DiscoverInfo
  },
  {
    POINTER,
    &DiscoverStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeDiscover_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeDiscover Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *DiscoverStatus = PXEBaseCode->Discover (
                                  PXEBaseCode,
                                  DiscoverType,
                                  DiscoverLayer,
                                  DiscoverUseBis,
                                  DiscoverInfo
                                  );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.Mtftp
//
static EFI_PXE_BASE_CODE_TFTP_OPCODE  MtftpOperation;
static VOID                           *MtftpBufferPtr;
static BOOLEAN                        MtftpOverwrite;
static UINT64                         *MtftpBufferSize;
static UINTN                          *MtftpBlockSize;
static EFI_IP_ADDRESS                 *MtftpServerIp;
static CHAR8                          *MtftpFileName;
static EFI_PXE_BASE_CODE_MTFTP_INFO   *MtftpInfo;
static BOOLEAN                        MtftpDontUseBuffer;
static EFI_STATUS                     *MtftpStatus;

ENTS_ARG_FIELD                        gPXEBaseCodeMtftpArgField[] = {
  {
    OCTETN,
    &MtftpOperation
  },
  {
    POINTER,
    &MtftpBufferPtr
  },
  {
    BOOL,
    &MtftpOverwrite
  },
  {
    POINTER,
    &MtftpBufferSize
  },
  {
    POINTER,
    &MtftpBlockSize
  },
  {
    POINTER,
    &MtftpServerIp
  },
  {
    POINTER,
    &MtftpFileName
  },
  {
    POINTER,
    &MtftpInfo
  },
  {
    BOOL,
    &MtftpDontUseBuffer
  },
  {
    POINTER,
    &MtftpStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeMtftp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMtftp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *MtftpStatus = PXEBaseCode->Mtftp (
                                PXEBaseCode,
                                MtftpOperation,
                                MtftpBufferPtr,
                                MtftpOverwrite,
                                MtftpBufferSize,
                                MtftpBlockSize,
                                MtftpServerIp,
                                (UINT8 *) MtftpFileName,
                                MtftpInfo,
                                MtftpDontUseBuffer
                                );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.UdpWrite
//
static UINT16                     UdpWriteOpFlags;
static EFI_IP_ADDRESS             *UdpWriteDestIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpWriteDestPort;
static EFI_IP_ADDRESS             *UdpWriteGatewayIp;
static EFI_IP_ADDRESS             *UdpWriteSrcIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpWriteSrcPort;
static UINTN                      *UdpWriteHeaderSize;
static VOID                       *UdpWriteHeaderPtr;
static UINTN                      *UdpWriteBufferSize;
static VOID                       *UdpWriteBufferPtr;
static EFI_STATUS                 *UdpWriteStatus;

ENTS_ARG_FIELD                    gPXEBaseCodeUdpWriteArgField[] = {
  {
    OCTET2,
    &UdpWriteOpFlags
  },
  {
    POINTER,
    &UdpWriteDestIp
  },
  {
    POINTER,
    &UdpWriteDestPort
  },
  {
    POINTER,
    &UdpWriteGatewayIp
  },
  {
    POINTER,
    &UdpWriteSrcIp
  },
  {
    POINTER,
    &UdpWriteSrcPort
  },
  {
    POINTER,
    &UdpWriteHeaderSize
  },
  {
    POINTER,
    &UdpWriteHeaderPtr
  },
  {
    POINTER,
    &UdpWriteBufferSize
  },
  {
    POINTER,
    &UdpWriteBufferPtr
  },
  {
    POINTER,
    &UdpWriteStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeUdpWrite_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWrite Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *UdpWriteStatus = PXEBaseCode->UdpWrite (
                                  PXEBaseCode,
                                  UdpWriteOpFlags,
                                  UdpWriteDestIp,
                                  UdpWriteDestPort,
                                  UdpWriteGatewayIp,
                                  UdpWriteSrcIp,
                                  UdpWriteSrcPort,
                                  UdpWriteHeaderSize,
                                  UdpWriteHeaderPtr,
                                  UdpWriteBufferSize,
                                  UdpWriteBufferPtr
                                  );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.UdpRead
//
static UINT16                     UdpReadOpFlags;
static EFI_IP_ADDRESS             *UdpReadDestIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpReadDestPort;
static EFI_IP_ADDRESS             *UdpReadSrcIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpReadSrcPort;
static UINTN                      *UdpReadHeaderSize;
static VOID                       *UdpReadHeaderPtr;
static UINTN                      *UdpReadBufferSize;
static VOID                       *UdpReadBufferPtr;
static EFI_STATUS                 *UdpReadStatus;

ENTS_ARG_FIELD                    gPXEBaseCodeUdpReadArgField[] = {
  {
    OCTET2,
    &UdpReadOpFlags
  },
  {
    POINTER,
    &UdpReadDestIp
  },
  {
    POINTER,
    &UdpReadDestPort
  },
  {
    POINTER,
    &UdpReadSrcIp
  },
  {
    POINTER,
    &UdpReadSrcPort
  },
  {
    POINTER,
    &UdpReadHeaderSize
  },
  {
    POINTER,
    &UdpReadHeaderPtr
  },
  {
    POINTER,
    &UdpReadBufferSize
  },
  {
    POINTER,
    &UdpReadBufferPtr
  },
  {
    POINTER,
    &UdpReadStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeUdpRead_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpRead Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *UdpReadStatus = PXEBaseCode->UdpRead (
                                  PXEBaseCode,
                                  UdpReadOpFlags,
                                  UdpReadDestIp,
                                  UdpReadDestPort,
                                  UdpReadSrcIp,
                                  UdpReadSrcPort,
                                  UdpReadHeaderSize,
                                  UdpReadHeaderPtr,
                                  UdpReadBufferSize,
                                  UdpReadBufferPtr
                                  );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.SetIpFilter
//
static EFI_PXE_BASE_CODE_IP_FILTER  *SetIpFilterNewFilter;
static EFI_STATUS                   *SetIpFilterStatus;

ENTS_ARG_FIELD                      gPXEBaseCodeSetIpFilterArgField[] = {
  {
    POINTER,
    &SetIpFilterNewFilter
  },
  {
    POINTER,
    &SetIpFilterStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeSetIpFilter_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetIpFilter Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *SetIpFilterStatus = PXEBaseCode->SetIpFilter (
                                      PXEBaseCode,
                                      SetIpFilterNewFilter
                                      );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.Arp
//
static EFI_IP_ADDRESS   *ArpIpAddr;
static EFI_MAC_ADDRESS  *ArpMacAddr;
static EFI_STATUS       *ArpStatus;

ENTS_ARG_FIELD          gPXEBaseCodeArpArgField[] = {
  {
    POINTER,
    &ArpIpAddr
  },
  {
    POINTER,
    &ArpMacAddr
  },
  {
    POINTER,
    &ArpStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeArp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeArp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *ArpStatus = PXEBaseCode->Arp (
                              PXEBaseCode,
                              ArpIpAddr,
                              ArpMacAddr
                              );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.SetParameters
//
static BOOLEAN    *SetParametersNewAutoArp;
static BOOLEAN    *SetParametersNewSendGUID;
static UINT8      *SetParametersNewTTL;
static UINT8      *SetParametersNewToS;
static BOOLEAN    *SetParametersNewMakeCallback;
static EFI_STATUS *SetParametersStatus;

ENTS_ARG_FIELD    gPXEBaseCodeSetParametersArgField[] = {
  {
    POINTER,
    &SetParametersNewAutoArp
  },
  {
    POINTER,
    &SetParametersNewSendGUID
  },
  {
    POINTER,
    &SetParametersNewTTL
  },
  {
    POINTER,
    &SetParametersNewToS
  },
  {
    POINTER,
    &SetParametersNewMakeCallback
  },
  {
    POINTER,
    &SetParametersStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeSetParameters_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetParameters Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *SetParametersStatus = PXEBaseCode->SetParameters (
                                        PXEBaseCode,
                                        SetParametersNewAutoArp,
                                        SetParametersNewSendGUID,
                                        SetParametersNewTTL,
                                        SetParametersNewToS,
                                        SetParametersNewMakeCallback
                                        );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.SetStationIp
//
static EFI_IP_ADDRESS *SetStationIpNewStationIp;
static EFI_IP_ADDRESS *SetStationIpNewSubnetMask;
static EFI_STATUS     *SetStationIpStatus;

ENTS_ARG_FIELD        gPXEBaseCodeSetStationIpArgField[] = {
  {
    POINTER,
    &SetStationIpNewStationIp
  },
  {
    POINTER,
    &SetStationIpNewSubnetMask
  },
  {
    POINTER,
    &SetStationIpStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeSetStationIp_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetStationIp Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *SetStationIpStatus = PXEBaseCode->SetStationIp (
                                      PXEBaseCode,
                                      SetStationIpNewStationIp,
                                      SetStationIpNewSubnetMask
                                      );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.SetPackets
//
static BOOLEAN                  *SetPacketsNewDhcpDiscoverValid;
static BOOLEAN                  *SetPacketsNewDhcpAckReceived;
static BOOLEAN                  *SetPacketsNewProxyOfferReceived;
static BOOLEAN                  *SetPacketsNewPxeDiscoverValid;
static BOOLEAN                  *SetPacketsNewPxeReplyReceived;
static BOOLEAN                  *SetPacketsNewPxeBisReplyReceived;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewDhcpDiscover;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewDhcpAck;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewProxyOffer;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewPxeDiscover;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewPxeReply;
static EFI_PXE_BASE_CODE_PACKET *SetPacketsNewPxeBisReply;
static EFI_STATUS               *SetPacketsStatus;

ENTS_ARG_FIELD                  gPXEBaseCodeSetPacketsArgField[] = {
  {
    POINTER,
    &SetPacketsNewDhcpDiscoverValid
  },
  {
    POINTER,
    &SetPacketsNewDhcpAckReceived
  },
  {
    POINTER,
    &SetPacketsNewProxyOfferReceived
  },
  {
    POINTER,
    &SetPacketsNewPxeDiscoverValid
  },
  {
    POINTER,
    &SetPacketsNewPxeReplyReceived
  },
  {
    POINTER,
    &SetPacketsNewPxeBisReplyReceived
  },
  {
    POINTER,
    &SetPacketsNewDhcpDiscover
  },
  {
    POINTER,
    &SetPacketsNewDhcpAck
  },
  {
    POINTER,
    &SetPacketsNewProxyOffer
  },
  {
    POINTER,
    &SetPacketsNewPxeDiscover
  },
  {
    POINTER,
    &SetPacketsNewPxeReply
  },
  {
    POINTER,
    &SetPacketsNewPxeBisReply
  },
  {
    POINTER,
    &SetPacketsStatus
  },
  0
};

EFI_STATUS
PXEBaseCodeSetPackets_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeSetPackets Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  *SetPacketsStatus = PXEBaseCode->SetPackets (
                                    PXEBaseCode,
                                    SetPacketsNewDhcpDiscoverValid,
                                    SetPacketsNewDhcpAckReceived,
                                    SetPacketsNewProxyOfferReceived,
                                    SetPacketsNewPxeDiscoverValid,
                                    SetPacketsNewPxeReplyReceived,
                                    SetPacketsNewPxeBisReplyReceived,
                                    SetPacketsNewDhcpDiscover,
                                    SetPacketsNewDhcpAck,
                                    SetPacketsNewProxyOffer,
                                    SetPacketsNewPxeDiscover,
                                    SetPacketsNewPxeReply,
                                    SetPacketsNewPxeBisReply
                                    );
  return EFI_SUCCESS;
}

//
// PXEBaseCode.Mode
//
static EFI_PXE_BASE_CODE_MODE *Mode;

ENTS_ARG_FIELD                gPXEBaseCodeModeArgField[] = {
  {
    POINTER,
    &Mode
  },
  0
};

EFI_STATUS
PXEBaseCodeMode_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeMode Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  EntsCopyMem (Mode, PXEBaseCode->Mode, sizeof (EFI_PXE_BASE_CODE_MODE));

  return EFI_SUCCESS;
}

//
// PXEBaseCode.UdpWritePattern1
//
static UINTN                      UdpWritePattern1Number;
static UINT16                     UdpWritePattern1OpFlags;
static EFI_IP_ADDRESS             *UdpWritePattern1DestIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpWritePattern1DestPort;
static EFI_IP_ADDRESS             *UdpWritePattern1GatewayIp;
static EFI_IP_ADDRESS             *UdpWritePattern1SrcIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpWritePattern1SrcPort;
static UINTN                      *UdpWritePattern1HeaderSize;
static VOID                       *UdpWritePattern1HeaderPtr;
static UINTN                      *UdpWritePattern1BufferSize;
static VOID                       *UdpWritePattern1BufferPtr;
static EFI_STATUS                 *UdpWritePattern1Status;

ENTS_ARG_FIELD                    gPXEBaseCodeUdpWritePattern1ArgField[] = {
  {
    OCTETN,
    &UdpWritePattern1Number
  },
  {
    OCTET2,
    &UdpWritePattern1OpFlags
  },
  {
    POINTER,
    &UdpWritePattern1DestIp
  },
  {
    POINTER,
    &UdpWritePattern1DestPort
  },
  {
    POINTER,
    &UdpWritePattern1GatewayIp
  },
  {
    POINTER,
    &UdpWritePattern1SrcIp
  },
  {
    POINTER,
    &UdpWritePattern1SrcPort
  },
  {
    POINTER,
    &UdpWritePattern1HeaderSize
  },
  {
    POINTER,
    &UdpWritePattern1HeaderPtr
  },
  {
    POINTER,
    &UdpWritePattern1BufferSize
  },
  {
    POINTER,
    &UdpWritePattern1BufferPtr
  },
  {
    POINTER,
    &UdpWritePattern1Status
  },
  0
};

EFI_STATUS
PXEBaseCodeUdpWritePattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpWritePattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;
  UINTN                       Index;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  for (Index = 0; Index < UdpWritePattern1Number;) {
    *UdpWritePattern1Status = PXEBaseCode->UdpWrite (
                                            PXEBaseCode,
                                            UdpWritePattern1OpFlags,
                                            UdpWritePattern1DestIp,
                                            UdpWritePattern1DestPort,
                                            UdpWritePattern1GatewayIp,
                                            UdpWritePattern1SrcIp,
                                            UdpWritePattern1SrcPort,
                                            UdpWritePattern1HeaderSize,
                                            UdpWritePattern1HeaderPtr,
                                            UdpWritePattern1BufferSize,
                                            UdpWritePattern1BufferPtr
                                            );
    if (*UdpWritePattern1Status == EFI_SUCCESS) {
      ++Index;
    } else if (*UdpWritePattern1Status != EFI_TIMEOUT) {
      break;
    }
  }

  return EFI_SUCCESS;
}

//
// PXEBaseCode.UdpReadPattern1
//
static UINTN                      UdpReadPattern1Number;
static UINT16                     UdpReadPattern1OpFlags;
static EFI_IP_ADDRESS             *UdpReadPattern1DestIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpReadPattern1DestPort;
static EFI_IP_ADDRESS             *UdpReadPattern1SrcIp;
static EFI_PXE_BASE_CODE_UDP_PORT *UdpReadPattern1SrcPort;
static UINTN                      *UdpReadPattern1HeaderSize;
static VOID                       *UdpReadPattern1HeaderPtr;
static UINTN                      *UdpReadPattern1BufferSize;
static VOID                       *UdpReadPattern1BufferPtr;
static EFI_STATUS                 *UdpReadPattern1Status;

ENTS_ARG_FIELD                    gPXEBaseCodeUdpReadPattern1ArgField[] = {
  {
    OCTETN,
    &UdpReadPattern1Number
  },
  {
    OCTET2,
    &UdpReadPattern1OpFlags
  },
  {
    POINTER,
    &UdpReadPattern1DestIp
  },
  {
    POINTER,
    &UdpReadPattern1DestPort
  },
  {
    POINTER,
    &UdpReadPattern1SrcIp
  },
  {
    POINTER,
    &UdpReadPattern1SrcPort
  },
  {
    POINTER,
    &UdpReadPattern1HeaderSize
  },
  {
    POINTER,
    &UdpReadPattern1HeaderPtr
  },
  {
    POINTER,
    &UdpReadPattern1BufferSize
  },
  {
    POINTER,
    &UdpReadPattern1BufferPtr
  },
  {
    POINTER,
    &UdpReadPattern1Status
  },
  0
};

EFI_STATUS
PXEBaseCodeUdpReadPattern1_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  PXEBaseCodeUdpReadPattern1 Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_PXE_BASE_CODE_PROTOCOL  *PXEBaseCode;
  UINTN                       Index;
  EFI_IP_ADDRESS              UdpReadPattern1DestIpOrg;
  EFI_PXE_BASE_CODE_UDP_PORT  UdpReadPattern1DestPortOrg;
  EFI_IP_ADDRESS              UdpReadPattern1SrcIpOrg;
  EFI_PXE_BASE_CODE_UDP_PORT  UdpReadPattern1SrcPortOrg;
  UINTN                       UdpReadPattern1HeaderSizeOrg;
  UINTN                       UdpReadPattern1BufferSizeOrg;

  PXEBaseCode = (EFI_PXE_BASE_CODE_PROTOCOL *) ClientInterface;

  EntsCopyMem (&UdpReadPattern1DestIpOrg, UdpReadPattern1DestIp, sizeof (EFI_IP_ADDRESS));
  UdpReadPattern1DestPortOrg = *UdpReadPattern1DestPort;
  EntsCopyMem (&UdpReadPattern1SrcIpOrg, UdpReadPattern1SrcIp, sizeof (EFI_IP_ADDRESS));
  UdpReadPattern1SrcPortOrg     = *UdpReadPattern1SrcPort;
  UdpReadPattern1HeaderSizeOrg  = *UdpReadPattern1HeaderSize;
  UdpReadPattern1BufferSizeOrg  = *UdpReadPattern1BufferSize;

  for (Index = 0; Index < UdpReadPattern1Number;) {
    EntsCopyMem (UdpReadPattern1DestIp, &UdpReadPattern1DestIpOrg, sizeof (EFI_IP_ADDRESS));
    *UdpReadPattern1DestPort = UdpReadPattern1DestPortOrg;
    EntsCopyMem (UdpReadPattern1SrcIp, &UdpReadPattern1SrcIpOrg, sizeof (EFI_IP_ADDRESS));
    *UdpReadPattern1SrcPort     = UdpReadPattern1SrcPortOrg;
    *UdpReadPattern1HeaderSize  = UdpReadPattern1HeaderSizeOrg;
    *UdpReadPattern1BufferSize  = UdpReadPattern1BufferSizeOrg;

    *UdpReadPattern1Status = PXEBaseCode->UdpRead (
                                            PXEBaseCode,
                                            UdpReadPattern1OpFlags,
                                            UdpReadPattern1DestIp,
                                            UdpReadPattern1DestPort,
                                            UdpReadPattern1SrcIp,
                                            UdpReadPattern1SrcPort,
                                            UdpReadPattern1HeaderSize,
                                            UdpReadPattern1HeaderPtr,
                                            UdpReadPattern1BufferSize,
                                            UdpReadPattern1BufferPtr
                                            );
    if (*UdpReadPattern1Status == EFI_SUCCESS) {
      ++Index;
    } else if (*UdpReadPattern1Status != EFI_TIMEOUT) {
      break;
    }
  }

  return EFI_SUCCESS;
}
