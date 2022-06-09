/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Mtftp4ENTSTestCase.c

Abstract:

--*/

#include "Mtftp4ENTSTestCase.h"

//
// Mtftp4.GetModeData
//
static EFI_MTFTP4_MODE_DATA *GetModeData_ModeData;
static EFI_STATUS           *GetModeData_Status;

ENTS_ARG_FIELD  gMtftp4GetModeDataArgField[] = {
  {
    POINTER,
    &GetModeData_ModeData
  },
  {
    POINTER,
    &GetModeData_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4GetModeData_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 GetModeData Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  *GetModeData_Status = Mtftp4->GetModeData (
                                  Mtftp4,
                                  GetModeData_ModeData
                                  );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *GetModeData_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.Configure
//
static EFI_MTFTP4_CONFIG_DATA *Configure_Mtftp4ConfigData;
static EFI_STATUS             *Configure_Status;

ENTS_ARG_FIELD                gMtftp4ConfigureArgField[] = {
  {
    POINTER,
    &Configure_Mtftp4ConfigData
  },
  {
    POINTER,
    &Configure_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4Configure_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 Configure Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  *Configure_Status = Mtftp4->Configure (
                                Mtftp4,
                                Configure_Mtftp4ConfigData
                                );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *Configure_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.GetInfo
//
static EFI_MTFTP4_OVERRIDE_DATA *GetInfo_OverrideData;
static UINT8                    *GetInfo_Filename;
static UINT8                    *GetInfoModeStr;
static UINT8                    GetInfo_OptionCount;
static EFI_MTFTP4_OPTION        *GetInfo_OptionList;
static UINT32                   *GetInfo_PacketLength;
static EFI_MTFTP4_PACKET        **GetInfo_Packet;
static EFI_STATUS               *GetInfo_Status;

ENTS_ARG_FIELD                  gMtftp4GetInfoArgField[] = {
  {
    POINTER,
    &GetInfo_OverrideData
  },
  {
    POINTER,
    &GetInfo_Filename
  },
  {
    POINTER,
    &GetInfoModeStr
  },
  {
    OCTET8,
    &GetInfo_OptionCount
  },
  {
    POINTER,
    &GetInfo_OptionList
  },
  {
    POINTER,
    &GetInfo_PacketLength
  },
  {
    POINTER,
    &GetInfo_Packet
  },
  {
    POINTER,
    &GetInfo_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4GetInfo_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 GetInfo Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  *GetInfo_Status = Mtftp4->GetInfo (
                              Mtftp4,
                              GetInfo_OverrideData,
                              GetInfo_Filename,
                              GetInfoModeStr,
                              GetInfo_OptionCount,
                              GetInfo_OptionList,
                              GetInfo_PacketLength,
                              GetInfo_Packet
                              );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *GetInfo_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.ParseOptions
//
static UINT32             ParseOptions_PacketLen;
static EFI_MTFTP4_PACKET  *ParseOptions_Packet;
static UINT32             *ParseOptions_OptionCount;
static EFI_MTFTP4_OPTION  **ParseOptions_OptionList;
static EFI_STATUS         *ParseOptions_Status;

ENTS_ARG_FIELD            gMtftp4ParseOptionsArgField[] = {
  {
    OCTETN,
    &ParseOptions_PacketLen
  },
  {
    POINTER,
    &ParseOptions_Packet
  },
  {
    POINTER,
    &ParseOptions_OptionCount
  },
  {
    POINTER,
    &ParseOptions_OptionList
  },
  {
    POINTER,
    &ParseOptions_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4ParseOptions_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ParseOptions Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  *ParseOptions_Status = Mtftp4->ParseOptions (
                                  Mtftp4,
                                  ParseOptions_PacketLen,
                                  ParseOptions_Packet,
                                  ParseOptions_OptionCount,
                                  ParseOptions_OptionList
                                  );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *ParseOptions_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.ReadFile
//
EFI_STATUS
EFIAPI
ReadFileCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadFileCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadFileCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadFileCheckPacket3 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

static EFI_MTFTP4_CHECK_PACKET      ReadFileCheckPacketList[] = {
  ReadFileCheckPacket0,
  ReadFileCheckPacket1,
  ReadFileCheckPacket2,
  ReadFileCheckPacket3
};

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

static EFI_MTFTP4_TIMEOUT_CALLBACK  ReadFileTimeoutCallbackList[] = {
  ReadFileTimeoutCallback0,
  ReadFileTimeoutCallback1,
  ReadFileTimeoutCallback2
};

EFI_STATUS
EFIAPI
ReadFilePacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
ReadFilePacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
ReadFilePacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

static EFI_MTFTP4_PACKET_NEEDED     ReadFilePacketNeededList[] = {
  ReadFilePacketNeeded0,
  ReadFilePacketNeeded1,
  ReadFilePacketNeeded2
};

static EFI_MTFTP4_TOKEN             *ReadFile_Token;
static UINTN                        ReadFileCheckPacket;
static UINTN                        ReadFileTimeoutCallback;
static UINTN                        ReadFilePacketNeeded;
static EFI_STATUS                   *ReadFile_Status;

ENTS_ARG_FIELD                      gMtftp4ReadFileArgField[] = {
  {
    POINTER,
    &ReadFile_Token
  },
  {
    OCTETN,
    &ReadFileCheckPacket
  },
  {
    OCTETN,
    &ReadFileTimeoutCallback
  },
  {
    OCTETN,
    &ReadFilePacketNeeded
  },
  {
    POINTER,
    &ReadFile_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4ReadFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ReadFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  if (ReadFile_Token != NULL) {
    if (ReadFileCheckPacket < 4) {
      ReadFile_Token->CheckPacket = ReadFileCheckPacketList[ReadFileCheckPacket];
    } else {
      EntsPrint (L"ReadFile_Token->CheckPacket     = NULL\n");
      ReadFile_Token->CheckPacket = NULL;
    }

    if (ReadFileTimeoutCallback < 3) {
      ReadFile_Token->TimeoutCallback = ReadFileTimeoutCallbackList[ReadFileTimeoutCallback];
    } else {
      ReadFile_Token->TimeoutCallback = NULL;
    }

    if (ReadFilePacketNeeded < 3) {
      ReadFile_Token->PacketNeeded = ReadFilePacketNeededList[ReadFilePacketNeeded];
    } else {
      ReadFile_Token->PacketNeeded = NULL;
    }
  }

  *ReadFile_Status = Mtftp4->ReadFile (
                              Mtftp4,
                              ReadFile_Token
                              );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *ReadFile_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.WriteFile
//
EFI_STATUS
EFIAPI
WriteFileCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
WriteFileCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
WriteFileCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

static EFI_MTFTP4_CHECK_PACKET      WriteFileCheckPacketList[] = {
  WriteFileCheckPacket0,
  WriteFileCheckPacket1,
  WriteFileCheckPacket2
};

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

static EFI_MTFTP4_TIMEOUT_CALLBACK  WriteFileTimeoutCallbackList[] = {
  WriteFileTimeoutCallback0,
  WriteFileTimeoutCallback1,
  WriteFileTimeoutCallback2
};

EFI_STATUS
EFIAPI
WriteFilePacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
WriteFilePacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
WriteFilePacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

static EFI_MTFTP4_PACKET_NEEDED     WriteFilePacketNeededList[] = {
  WriteFilePacketNeeded0,
  WriteFilePacketNeeded1,
  WriteFilePacketNeeded2
};

static EFI_MTFTP4_TOKEN             *WriteFile_Token;
static UINTN                        WriteFileCheckPacket;
static UINTN                        WriteFileTimeoutCallback;
static UINTN                        WriteFilePacketNeeded;
static EFI_STATUS                   *WriteFile_Status;

ENTS_ARG_FIELD                      gMtftp4WriteFileArgField[] = {
  {
    POINTER,
    &WriteFile_Token
  },
  {
    OCTETN,
    &WriteFileCheckPacket
  },
  {
    OCTETN,
    &WriteFileTimeoutCallback
  },
  {
    OCTETN,
    &WriteFilePacketNeeded
  },
  {
    POINTER,
    &WriteFile_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4WriteFile_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 WriteFile Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  if (WriteFile_Token != NULL) {
    if (WriteFileCheckPacket < 3) {
      WriteFile_Token->CheckPacket = WriteFileCheckPacketList[WriteFileCheckPacket];
    } else {
      WriteFile_Token->CheckPacket = NULL;
    }

    if (WriteFileTimeoutCallback < 3) {
      WriteFile_Token->TimeoutCallback = WriteFileTimeoutCallbackList[WriteFileTimeoutCallback];
    } else {
      WriteFile_Token->TimeoutCallback = NULL;
    }

    if (WriteFilePacketNeeded < 3) {
      WriteFile_Token->PacketNeeded = WriteFilePacketNeededList[WriteFilePacketNeeded];
    } else {
      WriteFile_Token->PacketNeeded = NULL;
    }
  }

  *WriteFile_Status = Mtftp4->WriteFile (
                                Mtftp4,
                                WriteFile_Token
                                );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *WriteFile_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.ReadDirectory
//
EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket3 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  );

static EFI_MTFTP4_CHECK_PACKET      ReadDirectoryCheckPacketList[] = {
  ReadDirectoryCheckPacket0,
  ReadDirectoryCheckPacket1,
  ReadDirectoryCheckPacket2,
  ReadDirectoryCheckPacket3
};

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  );

static EFI_MTFTP4_TIMEOUT_CALLBACK  ReadDirectoryTimeoutCallbackList[] = {
  ReadDirectoryTimeoutCallback0,
  ReadDirectoryTimeoutCallback1,
  ReadDirectoryTimeoutCallback2
};

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  );

static EFI_MTFTP4_PACKET_NEEDED     ReadDirectoryPacketNeededList[] = {
  ReadDirectoryPacketNeeded0,
  ReadDirectoryPacketNeeded1,
  ReadDirectoryPacketNeeded2
};

static EFI_MTFTP4_TOKEN             *ReadDirectory_Token;
static UINTN                        ReadDirectoryCheckPacket;
static UINTN                        ReadDirectoryTimeoutCallback;
static UINTN                        ReadDirectoryPacketNeeded;
static EFI_STATUS                   *ReadDirectory_Status;

ENTS_ARG_FIELD                      gMtftp4ReadDirectoryArgField[] = {
  {
    POINTER,
    &ReadDirectory_Token
  },
  {
    OCTETN,
    &ReadDirectoryCheckPacket
  },
  {
    OCTETN,
    &ReadDirectoryTimeoutCallback
  },
  {
    OCTETN,
    &ReadDirectoryPacketNeeded
  },
  {
    POINTER,
    &ReadDirectory_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4ReadDirectory_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 ReadDirectory Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4 = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  if (ReadDirectory_Token != NULL) {
    if (ReadDirectoryCheckPacket < 4) {
      ReadDirectory_Token->CheckPacket = ReadDirectoryCheckPacketList[ReadDirectoryCheckPacket];
    } else {
      ReadDirectory_Token->CheckPacket = NULL;
    }

    if (ReadDirectoryTimeoutCallback < 3) {
      ReadDirectory_Token->TimeoutCallback = ReadDirectoryTimeoutCallbackList[ReadDirectoryTimeoutCallback];
    } else {
      ReadDirectory_Token->TimeoutCallback = NULL;
    }

    if (ReadDirectoryPacketNeeded < 3) {
      ReadDirectory_Token->PacketNeeded = ReadDirectoryPacketNeededList[ReadDirectoryPacketNeeded];
    } else {
      ReadDirectory_Token->PacketNeeded = NULL;
    }
  }

  *ReadDirectory_Status = Mtftp4->ReadDirectory (
                                    Mtftp4,
                                    ReadDirectory_Token
                                    );
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *ReadDirectory_Status
    );
  return EFI_SUCCESS;
}

//
// Mtftp4.Poll
//
static EFI_STATUS *Poll_Status;

ENTS_ARG_FIELD    gMtftp4PollArgField[] = {
  {
    POINTER,
    &Poll_Status
  },
  0
};

EFI_STATUS
EFIAPI
Mtftp4Poll_EntsTest (
  VOID *ClientInterface
  )
/*++

Routine Description:

  Mtftp4 Poll Ents test entry point.

Arguments:

  ClientInterface - RPC calling interface.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EFI_MTFTP4_PROTOCOL *Mtftp4;

  Mtftp4        = (EFI_MTFTP4_PROTOCOL *) ClientInterface;

  *Poll_Status  = Mtftp4->Poll (Mtftp4);
  RecordMessage (
    &gMtftp4EntsRuntimeInfo,
    &gMtftp4EntsRuntimeInfoSize,
    L"Status - %r",
    *Poll_Status
    );
  return EFI_SUCCESS;
}

//
// ReadFile Callback Routines.
//
EFI_STATUS
EFIAPI
ReadFileCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readfile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFileCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readfile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 CheckTimes = 0;

  CheckTimes++;
  EntsPrint (L"Callback ReadFileCheckPacket1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFileCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readfile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Something failed.

--*/
{
  switch (NTOHS (Packet->OpCode)) {
  // Data8 field should be ignored and treated as reserved
  case EFI_MTFTP4_OPCODE_DATA8:    
    EntsPrint (L"Callback ReadFileCheckPacket2() Data8 field should be ignored.\n");
    break;

  case EFI_MTFTP4_OPCODE_DATA:
    EntsPrint (L"Callback ReadFileCheckPacket2() abort the process.\n");
    break;

  case EFI_MTFTP4_OPCODE_OACK:
  case EFI_MTFTP4_OPCODE_ERROR:
  default:
    return EFI_SUCCESS;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadFileCheckPacket3 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readfile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Something failed.

--*/
{
  switch (NTOHS (Packet->OpCode)) {
  case EFI_MTFTP4_OPCODE_DATA:
    return EFI_SUCCESS;

  // Data8 field should be ignored and treated as reserved
  case EFI_MTFTP4_OPCODE_DATA8:
    EntsPrint (L"Callback ReadFileCheckPacket3() Data8 field should be ignored.\n");
    break;
    
  case EFI_MTFTP4_OPCODE_OACK:
  case EFI_MTFTP4_OPCODE_ERROR:
  default:
    EntsPrint (L"Callback ReadFileCheckPacket3() abort the process.\n");
    break;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readfile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readfile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 TimeoutTimes = 0;

  TimeoutTimes++;
  EntsPrint (L"Callback ReadFileTimeoutCallback1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFileTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readfile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback ReadFileTimeoutCallback2() abort the process.\n");

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadFilePacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readfile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFilePacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readfile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 PacketNeededTimes = 0;

  PacketNeededTimes++;
  EntsPrint (L"Callback ReadFilePacketNeeded1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadFilePacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readfile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback ReadFilePacketNeeded2() abort the process.\n");

  return EFI_ABORTED;
}

//
// WriteFile Callback Routines.
//
EFI_STATUS
EFIAPI
WriteFileCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 writefile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback WriteFileCheckPacket0() is called.\n");
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFileCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 writefile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 CheckTimes = 0;

  CheckTimes++;
  EntsPrint (L"Callback WriteFileCheckPacket1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFileCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 writefile check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback WriteFileCheckPacket2() abort the process.\n");

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 writefile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 writefile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 TimeoutTimes = 0;

  TimeoutTimes++;
  EntsPrint (L"Callback WriteFileTimeoutCallback1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFileTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 writefile timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback WriteFileTimeoutCallback2() abort the process.\n");

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
WriteFilePacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 writefile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFilePacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 writefile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 PacketNeededTimes = 0;

  PacketNeededTimes++;
  EntsPrint (L"Callback WriteFilePacketNeeded1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
WriteFilePacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 writefile packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback WriteFilePacketNeeded2() abort the process.\n");

  return EFI_ABORTED;
}

//
// ReadDirectory Callback Routines.
//
EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readDirectory check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readDirectory check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 CheckTimes = 0;

  CheckTimes++;
  EntsPrint (L"Callback ReadDirectoryCheckPacket1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readDirectory check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  switch (NTOHS (Packet->OpCode)) {  
  // Data8 field should be ignored and treated as reserved
  case EFI_MTFTP4_OPCODE_DATA8:
    EntsPrint (L"Callback ReadDirectoryCheckPacket2() Data8 field should be ignored.\n");
    break;
    
  case EFI_MTFTP4_OPCODE_DATA:
    EntsPrint (L"Callback ReadDirectoryCheckPacket2() abort the process.\n");
    break;

  case EFI_MTFTP4_OPCODE_OACK:
  case EFI_MTFTP4_OPCODE_ERROR:
  default:
    return EFI_SUCCESS;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadDirectoryCheckPacket3 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN UINT16              PacketLen,
  IN EFI_MTFTP4_PACKET   *Packet
  )
/*++

Routine Description:

  Mtftp4 readDirectory check packet callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  PacketLen - Packet length.
  Packet    - Pointer to a Mtftpv4 packet.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  switch (NTOHS (Packet->OpCode)) {
  case EFI_MTFTP4_OPCODE_DATA:
    return EFI_SUCCESS;

  // Data8 field should be ignored and treated as reserved
  case EFI_MTFTP4_OPCODE_DATA8:
    EntsPrint (L"Callback ReadDirectoryCheckPacket3() Data8 field should be ignored.\n");
    break;
    
  case EFI_MTFTP4_OPCODE_OACK:
  case EFI_MTFTP4_OPCODE_ERROR:
  default:
    EntsPrint (L"Callback ReadDirectoryCheckPacket3() abort the process.\n");
    break;
  }

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readDirectory timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readDirectory timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 TimeoutTimes = 0;

  TimeoutTimes++;
  EntsPrint (L"Callback ReadDirectoryTimeoutCallback1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryTimeoutCallback2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token
  )
/*++

Routine Description:

  Mtftp4 readDirectory timeout callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback ReadDirectoryTimeoutCallback2() abort the process.\n");

  return EFI_ABORTED;
}

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded0 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readDirectory packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded1 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readDirectory packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  static UINT16 PacketNeededTimes = 0;

  PacketNeededTimes++;
  EntsPrint (L"Callback ReadDirectoryPacketNeeded1() is called.\n");

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ReadDirectoryPacketNeeded2 (
  IN EFI_MTFTP4_PROTOCOL *This,
  IN EFI_MTFTP4_TOKEN    *Token,
  IN OUT UINT16          *Length,
  OUT void               **Buffer
  )
/*++

Routine Description:

  Mtftp4 readDirectory packet needed callback routine.

Arguments:

  This      - Pointer to EFI_MTFTP4_PROTOCOL instance.
  Token     - Token that caller provided.
  Length    - Length of raw data wanted on input. 
  Buffer    - Pointer to buffer where the data is stored.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
{
  EntsPrint (L"Callback ReadDirectoryPacketNeeded2() abort the process.\n");

  return EFI_ABORTED;
}
