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

  NetDebug.c

Abstract:
  Implementation file of Network Debugging

--*/

#include <Library/NetLib.h>

#ifdef EFI_SYS_LOG

#include EFI_PROTOCOL_CONSUMER (NetDebugConfig)

EFI_NET_DEBUG_CONFIG_PROTOCOL *NetDebugConfigProtocol = NULL;

EFI_NET_DEBUG_CONFIG          *NetDbgCfg              = NULL;

EFI_NET_DEBUG_CONFIG *
NetDbgGetCfg (
  VOID
  )
{
  EFI_STATUS  Status;

  if (NULL == NetDebugConfigProtocol) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );
    if (EFI_ERROR (Status)) {
      return NULL;
    }

  }

  if (NULL == NetDbgCfg) {
    NetDbgCfg = NetDebugConfigProtocol->GetCfgDataPtr ();

  }

  ASSERT (NetDbgCfg);

  return NetDbgCfg;
}

VOID
NetDbgDump (
  VOID
  )
{
  if (NULL == NetDbgCfg) {
    return ;
  }

  if (NULL != NetDbgCfg->Mnp_Dbg) {
    NetDbgCfg->Mnp_Dbg ();
  }

  if (NULL != NetDbgCfg->Ip_Dbg) {
    NetDbgCfg->Ip_Dbg ();
  }

  if (NULL != NetDbgCfg->Udp_Dbg) {
    NetDbgCfg->Udp_Dbg ();
  }

  if (NULL != NetDbgCfg->Mtftp_Dbg) {
    NetDbgCfg->Mtftp_Dbg ();
  }

}

BOOLEAN
NetDbgCheck (
  IN UINT8  Level,
  IN UINT16 Source,
  IN UINT32 SubModule
  )
{
  EFI_STATUS  Status;
  if (NULL == NetDebugConfigProtocol) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );
    if (EFI_ERROR (Status)) {
      return FALSE;
    }
  }

  return NetDebugConfigProtocol->NetCheckLevel (Level, Source, SubModule);
}

INTN
NetDbgAssert (
  IN CHAR16 *FileName,
  IN UINT32 LineNumber,
  IN CHAR16 *Description
  )
{
  EFI_STATUS  Status;

  CHAR16      *Header;

  if (NULL == NetDebugConfigProtocol) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );
    if (EFI_ERROR (Status)) {
      return -1;
    }
  }

  Header = NetDbgSPrint (L"[ASSERT]:%s:%d\n", FileName, LineNumber);
  if (Header == NULL) {
    return -1;

  }

  NetDebugConfigProtocol->NetPrint (EFI_NETWORK_DEBUGLEVEL_ERROR, Header, Description);

  tBS->FreePool (Header);

  EFI_BREAKPOINT ();

  return 0;
}

INTN
NetDbgOutput (
  IN UINT8  Level,
  IN UINT16 Source,
  IN UINT32 SubModule,
  IN CHAR8  *FileName,
  IN UINT32 LineNumber,
  IN CHAR16 *Description
  )
{
  EFI_STATUS  Status;
  CHAR16      *MsgHeader;

  if (Description == NULL) {
    return -1;
  }

  if (NULL == NetDebugConfigProtocol) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );
    if (EFI_ERROR (Status)) {
      tBS->FreePool (Description);
      return -1;
    }
  }

  MsgHeader = NetDebugConfigProtocol->NetPrintHeader (
                                        Level,
                                        Source,
                                        SubModule,
                                        FileName,
                                        LineNumber
                                        );

  if (MsgHeader == NULL) {
    tBS->FreePool (Description);
    return -1;
  }

  NetDebugConfigProtocol->NetPrint (Level, MsgHeader, Description);

  tBS->FreePool (MsgHeader);
  tBS->FreePool (Description);

  return 0;
}

CHAR16 *
NetDbgSPrint (
  CHAR16 *Format,
  ...
  )
{
  EFI_STATUS  Status;
  VA_LIST     Marker;
  CHAR16      *Buffer;

  Buffer = NULL;
  if (NULL == NetDebugConfigProtocol) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );
    if (EFI_ERROR (Status)) {
      return NULL;
    }
  }

  VA_START (Marker, Format);
  Buffer = NetDebugConfigProtocol->NetVSPrint (Format, Marker);
  VA_END (Marker);

  return Buffer;
}
#endif

#ifdef EFI_DEBUG_MEMORY_LEAK

VOID *
EFIAPI
AllocatePoolDbg (
  IN UINTN            Size,
  IN CHAR16           *FileName,
  IN UINTN            Line
  )
{
  EFI_STATUS      Status;
  UINT8           *Buffer;
  CHAR16          *FileNamePtr;
  UINTN           Index;
  DBG_POOL_INFO   *Info;
  NET_LIST_ENTRY  *MemoryListHead;

  //
  //  Locate the EFI_NET_DEBUG_CONFIG_PROTOCOL interface
  //
  if (NetDebugConfigProtocol == NULL) {
    Status = tBS->LocateProtocol (
                    &gEfiNetDebugConfigProtocolGuid,
                    NULL,
                    &NetDebugConfigProtocol
                    );

    if (EFI_ERROR (Status)) {
      return NULL;
    }
  }

  MemoryListHead = (NET_LIST_ENTRY *) NetDebugConfigProtocol->GetMemLinkHeader ();
  if (MemoryListHead == NULL) {
    return NULL;
  }

  if (MemoryListHead->ForwardLink == NULL || MemoryListHead->BackLink == NULL) {
    //
    //  Not initialized yet
    //
    LIST_INIT (MemoryListHead);

  }

  Size += sizeof (DBG_POOL_INFO);

  Buffer = (UINT8 *) SctAllocatePool (Size);
  if (Buffer != NULL) {
    Index             = 0;
    Info              = (DBG_POOL_INFO *) Buffer;
    Info->FileName[0] = '\0';
    FileNamePtr       = (CHAR16 *) (Info->FileName);

    while (*FileName && Index < NET_DEBUG_MAX_FILE_NAME - 1) {
      *FileNamePtr++ = *FileName++;
      Index++;
    }

    Info->Signature = DBG_POOL_INFO_SIGNATURE;

    if (Index < NET_DEBUG_MAX_FILE_NAME) {
      Info->FileName[Index] = '\0';
    }

    Info->Line  = Line;
    Info->Size  = Size - sizeof (DBG_POOL_INFO);

    LIST_INSERT_TAIL (MemoryListHead, &Info->Entry);

    Buffer = Buffer + sizeof (DBG_POOL_INFO);
  } else {
    Buffer = NULL;
  }

  return (VOID *) Buffer;

}

VOID *
EFIAPI
AllocateZeroPoolDbg (
  IN UINTN            Size,
  IN CHAR16           *FileName,
  IN UINTN            Line
  )
{
  VOID  *Memory;

  Memory = AllocatePoolDbg (Size, FileName, Line);
  if (Memory != NULL) {
    NetZeroMem (Memory, Size);
  }

  return Memory;

}

VOID
EFIAPI
FreePoolDbg (
  IN VOID            *Buffer
  )
{
  DBG_POOL_INFO *Info;

  if (NULL == Buffer) {
    return ;
  }

  Info = (DBG_POOL_INFO *) ((CHAR8 *) Buffer - sizeof (DBG_POOL_INFO));

  if (Info->Signature == DBG_POOL_INFO_SIGNATURE) {
    ASSERT (Info->Size != 0);
    LIST_REMOVE_ENTRY (&Info->Entry);

    tBS->FreePool (Info);
  } else {
    //
    //  Should not go here
    //
    ASSERT (FALSE);
    tBS->FreePool (Buffer);
  }

  return ;
}

#endif
