/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
                    (VOID **) &NetDebugConfigProtocol
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
                    (VOID **) &NetDebugConfigProtocol
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
                    (VOID **) &NetDebugConfigProtocol
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
                    (VOID **) &NetDebugConfigProtocol
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
                    (VOID **) &NetDebugConfigProtocol
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
                    (VOID **) &NetDebugConfigProtocol
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
