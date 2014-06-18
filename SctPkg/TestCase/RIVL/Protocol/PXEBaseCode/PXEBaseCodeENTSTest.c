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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  PXEBaseCodeENTSTest.c

Abstract:

--*/

#include "PXEBaseCodeENTSTestCase.h"

static CHAR16     gPXEBaseCodeProtocolName[]      = L"PXEBaseCode";
CHAR16            *gPXEBaseCodeEntsRuntimeInfo    = NULL;
UINTN             gPXEBaseCodeEntsRuntimeInfoSize = 16;

ENTS_INTERFACE    gPXEBaseCodeEntsInterfaceList[] = {
  {
    L"Start",
    PXEBaseCodeStart_EntsTest,
    gPXEBaseCodeStartArgField
  },
  {
    L"Stop",
    PXEBaseCodeStop_EntsTest,
    gPXEBaseCodeStopArgField
  },
  {
    L"Dhcp",
    PXEBaseCodeDhcp_EntsTest,
    gPXEBaseCodeDhcpArgField
  },
  {
    L"Discover",
    PXEBaseCodeDiscover_EntsTest,
    gPXEBaseCodeDiscoverArgField
  },
  {
    L"Mtftp",
    PXEBaseCodeMtftp_EntsTest,
    gPXEBaseCodeMtftpArgField
  },
  {
    L"UdpWrite",
    PXEBaseCodeUdpWrite_EntsTest,
    gPXEBaseCodeUdpWriteArgField
  },
  {
    L"UdpRead",
    PXEBaseCodeUdpRead_EntsTest,
    gPXEBaseCodeUdpReadArgField
  },
  {
    L"SetIpFilter",
    PXEBaseCodeSetIpFilter_EntsTest,
    gPXEBaseCodeSetIpFilterArgField
  },
  {
    L"Arp",
    PXEBaseCodeArp_EntsTest,
    gPXEBaseCodeArpArgField
  },
  {
    L"SetParameters",
    PXEBaseCodeSetParameters_EntsTest,
    gPXEBaseCodeSetParametersArgField
  },
  {
    L"SetStationIp",
    PXEBaseCodeSetStationIp_EntsTest,
    gPXEBaseCodeSetStationIpArgField
  },
  {
    L"SetPackets",
    PXEBaseCodeSetPackets_EntsTest,
    gPXEBaseCodeSetPacketsArgField
  },
  {
    L"Mode",
    PXEBaseCodeMode_EntsTest,
    gPXEBaseCodeModeArgField
  },
  {
    L"UdpWritePattern1",
    PXEBaseCodeUdpWritePattern1_EntsTest,
    gPXEBaseCodeUdpWritePattern1ArgField
  },
  {
    L"UdpReadPattern1",
    PXEBaseCodeUdpReadPattern1_EntsTest,
    gPXEBaseCodeUdpReadPattern1ArgField
  },
  0
};

EFI_ENTS_PROTOCOL *gPXEBaseCodeEntsProtocolInterface = NULL;

EFI_STATUS
PXEBaseCodeENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  );


EFI_STATUS
PXEBaseCodeENTSTestMain (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
/*++

Routine Description:

  Entry point for PXEBaseCode protocol ENTS Test.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

  SctInitializeDriver (ImageHandle, SystemTable);
  EfiInitializeEntsLib (ImageHandle, SystemTable);

  tBS->HandleProtocol (
        ImageHandle,
        &gBlackBoxEfiLoadedImageProtocolGuid,
        (VOID *) &LoadedImage
        );

  LoadedImage->Unload = PXEBaseCodeENTSTestUnload;

  Status = tBS->AllocatePool (
                  EfiBootServicesData,
                  sizeof (EFI_ENTS_PROTOCOL),
                  (VOID **)&gPXEBaseCodeEntsProtocolInterface
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  gPXEBaseCodeEntsProtocolInterface->ClientName         = gPXEBaseCodeProtocolName;
  gPXEBaseCodeEntsProtocolInterface->ClientAttribute    = ENTS_PROTOCOL_ATTRIBUTE_PROTOCOL;
  gPXEBaseCodeEntsProtocolInterface->ClientGuid         = &gBlackBoxEfiPxeBaseCodeProtocolGuid;
  gPXEBaseCodeEntsProtocolInterface->ClientHandle       = NULL;
  gPXEBaseCodeEntsProtocolInterface->ClientInterface    = NULL;
  gPXEBaseCodeEntsProtocolInterface->EntsInterfaceList  = gPXEBaseCodeEntsInterfaceList;
  gPXEBaseCodeEntsProtocolInterface->RuntimeInfo        = gPXEBaseCodeEntsRuntimeInfo;
  gPXEBaseCodeEntsProtocolInterface->RuntimeInfoSize    = gPXEBaseCodeEntsRuntimeInfoSize;

  Status = tBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gPXEBaseCodeEntsProtocolInterface,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  return EFI_SUCCESS;

Error:
  if (gPXEBaseCodeEntsProtocolInterface != NULL) {
    tBS->FreePool (gPXEBaseCodeEntsProtocolInterface);
  }

  return Status;
}

EFI_STATUS
PXEBaseCodeENTSTestUnload (
  IN EFI_HANDLE                ImageHandle
  )
/*++

Routine Description:

  Unload routine.

Arguments:

  ImageHandle - The image handle.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
{
  EFI_STATUS  Status;

  Status = tBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiEntsProtocolGuid,
                  gPXEBaseCodeEntsProtocolInterface,
                  NULL
                  );

  if (gPXEBaseCodeEntsProtocolInterface != NULL) {
    tBS->FreePool (gPXEBaseCodeEntsProtocolInterface);
  }

  return Status;
}
