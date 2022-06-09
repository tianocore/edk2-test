/** @file

  Copyright 2006 - 2013 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2019, ARM Ltd. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  EntsLib.h

Abstract:

  SCT extended data services declarations.

--*/

#ifndef _EFI_ENTS_LIB_H
#define _EFI_ENTS_LIB_H

//
// #include "StandardTestLibrary.h"
//
#include EFI_PROTOCOL_DEFINITION (SimpleFileSystem)
#include EDK_PROTOCOL_DEFINITION (FileInfo)
#include EDK_PROTOCOL_DEFINITION (FileSystemInfo)
#include EDK_PROTOCOL_DEFINITION (FileSystemVolumeLabelInfo)
#include EFI_PROTOCOL_DEFINITION (BlockIo)
#include EFI_PROTOCOL_DEFINITION (DeviceIo)
#if (EFI_SPECIFICATION_VERSION < 0x0002000A)
#include EFI_PROTOCOL_DEFINITION (Hii)
#elif (EFI_SPECIFICATION_VERSION < 0x00020028)
#include "TianoHii.h"
#endif
#include EFI_PROTOCOL_DEFINITION (UnicodeCollation)
#include EFI_PROTOCOL_DEFINITION (SimpleTextOut)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCode)
#include EFI_PROTOCOL_DEFINITION (PxeBaseCodeCallBack)
#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
  #include <Protocol/NetworkInterfaceIdentifier.h>
#else
  #include EFI_PROTOCOL_DEFINITION (EfiNetworkInterfaceIdentifier)
#endif
#include EFI_PROTOCOL_DEFINITION (DevicePath)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)
#include EFI_PROTOCOL_DEFINITION (DiskIo)
#include EFI_PROTOCOL_DEFINITION (LoadFile)
#include EFI_PROTOCOL_DEFINITION (SerialIo)
#include EFI_PROTOCOL_DEFINITION (SimpleNetwork)
#if (EFI_SPECIFICATION_VERSION < 0x00020028)
  #include EFI_PROTOCOL_DEFINITION (VariableStore)
  #include EFI_PROTOCOL_DEFINITION (DebugAssert)
#endif
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics)
#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_GUID_DEFINITION (GlobalVariable)
#include EFI_GUID_DEFINITION (Gpt)
#include EFI_GUID_DEFINITION (Mps)
#include EFI_GUID_DEFINITION (Acpi)
#include EFI_GUID_DEFINITION (SmBios)

extern EFI_GUID             gtEfiDevicePathProtocolGuid;
extern EFI_GUID             gtEfiLoadedImageProtocolGuid;
extern EFI_GUID             gtEfiSimpleTextInProtocolGuid;
extern EFI_GUID             gtEfiSimpleTextOutProtocolGuid;
extern EFI_GUID             gtEfiBlockIoProtocolGuid;
extern EFI_GUID             gtEfiDiskIoProtocolGuid;
extern EFI_GUID             gtEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID             gtEfiLoadFileProtocolGuid;
extern EFI_GUID             gtEfiDeviceIoProtocolGuid;
extern EFI_GUID             gtEfiVariableStoreProtocolGuid;
extern EFI_GUID             gtEfiLegacyBootProtocolGuid;
extern EFI_GUID             gtEfiUnicodeCollationProtocolGuid;
extern EFI_GUID             gtEfiSerialIoProtocolGuid;
extern EFI_GUID             gtEfiVgaClassProtocolGuid;
extern EFI_GUID             tTextOutSpliterProtocol;
extern EFI_GUID             tErrorOutSpliterProtocol;
extern EFI_GUID             tTextInSpliterProtocol;
extern EFI_GUID             gtEfiSimpleNetworkProtocolGuid;
extern EFI_GUID             gtEfiPxeBaseCodeProtocolGuid;
extern EFI_GUID             gtEfiPxeCallbackProtocolGuid;
extern EFI_GUID             gtEfiNetworkInterfaceIdentifierProtocolGuid;

extern EFI_GUID             tEfiGlobalVariable;
extern EFI_GUID             tGenericFileInfo;
extern EFI_GUID             gtEfiFileSystemInfoGuid;
extern EFI_GUID             gtEfiFileSystemVolumeLabelInfoGuid;
extern EFI_GUID             tPcAnsiProtocol;
extern EFI_GUID             tVt100Protocol;
extern EFI_GUID             tNullGuid;
extern EFI_GUID             gtEfiUnknownDeviceGuid;

extern EFI_GUID             gtEfiPartTypeSystemPartitionGuid;
extern EFI_GUID             gtEfiPartTypeLegacyMbrGuid;

extern EFI_GUID             gtEfiMpsTableGuid;
extern EFI_GUID             gtEfiAcpiTableGuid;
extern EFI_GUID             gtEfiAcpi20TableGuid;
extern EFI_GUID             gtEfiSMBIOSTableGuid;

//
// Public read-only data in the EFI library
//
extern EFI_SYSTEM_TABLE     *gntST;
extern EFI_BOOT_SERVICES    *gntBS;
extern EFI_RUNTIME_SERVICES *gntRT;

extern EFI_MEMORY_TYPE      EntsPoolAllocationType;

extern EFI_UNICODE_COLLATION_PROTOCOL *EntsUnicodeInterface;

extern EFI_DEVICE_PATH_PROTOCOL        *gntDevicePath;
extern CHAR16                          *gntFilePath;
extern EFI_HANDLE                      mImageHandle;

#define SCT_PASSIVE_MODE_RECORD_FILE        L"SCT\\.passive.mode"

//
// External functions declarations
//
EFI_STATUS
EFIAPI
EfiInitializeEntsLib (
  IN  EFI_HANDLE                  ImageHandle,
  IN  EFI_SYSTEM_TABLE            *SystemTable
  )
/*++

Routine Description:

  Initialize Ents library.

Arguments:

  ImageHandle           - The image handle.
  SystemTable           - The system table.

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
GetImageDevicePath (
  IN EFI_HANDLE                   ImageHandle,
  OUT EFI_DEVICE_PATH_PROTOCOL    **DevicePath,
  OUT CHAR16                      **FilePath
  )
/*++

Routine Description:

  Get device path and file path from the image handle.

Arguments:

  ImageHandle - The image handle.
  DevicePath  - The device path of the image handle.
  FilePath    - The file path of the image handle.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  EFI_NOT_FOUND        - File path not found.
  Others               - Some failure happened.

--*/
;

//
// EFI Test Assertion Types
//
typedef enum {
  NET_EFI_TEST_ASSERTION_PASSED,
  NET_EFI_TEST_ASSERTION_WARNING,
  NET_EFI_TEST_ASSERTION_FAILED,
  NET_EFI_TEST_ASSERTION_CASE_BEGIN,
  NET_EFI_TEST_ASSERTION_CASE_OVER
} NET_EFI_TEST_ASSERTION;

EFI_STATUS
RecordMessage (
  IN  OUT CHAR16**ResultBuffer,
  IN  OUT UINTN *ResultBufferSize,
  IN     CHAR16 *Format,
  ...
  )
/*++

Routine Description:

  Record runtime information to a buffer.

Arguments:

  ResultBuffer      - Buffer space.
  ResultBufferSize  - Result buffer size in octets.
  Format            - Format string.
  ...               - Variables.

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.

--*/
;

EFI_STATUS
NetRecordAssertion (
  IN NET_EFI_TEST_ASSERTION   Type,
  IN EFI_GUID                 EventId,
  IN CHAR16                   *Description
  )
/*++

Routine Description:

  Records the test result to network.

Arguments:

  Type          - Test result.
  EventId       - GUID for the checkpoint.
  Description   - Simple description for the checkpoint.

Returns:

  EFI_SUCCESS           - Record the assertion successfully.
  EFI_INVALID_PARAMETER - Invalid Type.
  Others                - Problems when sending assertion packets.

--*/
;

//
// External functions declarations
//
INTN
EntsStrCmp (
  IN CHAR16                         *s1,
  IN CHAR16                         *s2
  )
;

VOID
EntsStrCpy (
  IN CHAR16                         *Dest,
  IN CHAR16                         *Src
  )
;

VOID
EntsStrCat (
  IN CHAR16                         *Dest,
  IN CHAR16                         *Src
  )
;

UINTN
EntsStrLen (
  IN CHAR16                         *s1
  )
;

VOID
EntsStrTrim (
  IN OUT CHAR16   *str,
  IN     CHAR16   c
  );

CHAR16 *
EntsStrDuplicate (
  IN CHAR16                         *Src
  )
;

INTN
EFIAPI
EntsLibStubStriCmp (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *s1,
  IN CHAR16                           *s2
  )
;

VOID
EFIAPI
EntsLibStubStrLwrUpr (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *Str
  )
;

BOOLEAN
EFIAPI
EntsLibStubMetaiMatch (
  IN EFI_UNICODE_COLLATION_PROTOCOL   *This,
  IN CHAR16                           *String,
  IN CHAR16                           *Pattern
  )
;

EFI_STATUS
Char16ToChar8 (
  IN  CHAR16 *Src,
  OUT CHAR8  *Dest,
  OUT UINTN  Size
  )
/*++

Routine Description:

  Convert a NULL-ended string of CHAR16 to CHAR8.

Arguments:

  Src   - NULL ended string of CHAR16.
  Dest  - String of CHAR8.
  Size  - The length of CHAR8 string

Returns:

  EFI_SUCCESS - Operation succeeded.
  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES  - Memory allocation failed.
  Others      - Some failure happened.

--*/
;

EFI_STATUS
Char8ToChar16 (
  IN  CHAR8  *Src,
  IN  UINTN  Size,
  OUT CHAR16 *Dest
  )
/*++

Routine Description:

  Convert a NULL-ended string of CHAR8 to CHAR16.

Arguments:

  Src   - String of CHAR8 which is not necessarily null ended.
  Size  - The byte number of CHAR8 string.
  Dest  - String of coresponding CHAR16,

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  EFI_SUCCESS - Operation succeeded.

--*/
;

UINTN
strspn (
  const CHAR16 *s,
  const CHAR16 *accept
  )
/*++

Routine Description:

  Find the first substring.

--*/
;

CHAR16 *
strpbrk (
  const CHAR16 *cs,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Scan strings for characters in specified character sets.

--*/
;

CHAR16 *
strtok_line (
  CHAR16       *s,
  const CHAR16 *ct
  )
;

CHAR16 *
strtok_arg (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string
  Tokens are separated by separators defined in "ct"
  If enclosed in double quotations, other separators are invalid. Then token is 
  the content in the quotations.

--*/
;

CHAR16 *
strtok_field (
  CHAR16       *s,
  const CHAR16 *ct
  )
/*++

Routine Description:

  Find the next token in a string.

--*/
;

INTN
EntsStrToUINTN (
  IN CHAR16        *Str,
  IN OUT UINTN     *Value
  )
;

INTN
EntsHexStrToUINTN (
  IN CHAR16        *Str,
  IN OUT UINTN     *Value
  )
;

EFI_STATUS
EntsStrToValue (
  IN CHAR16             *Buffer,
  OUT UINTN             *Value
  )
/*++

Routine Description:

  Convert a string to a value.

Arguments:

  Buffer  - String buffer.
  Value   - Pointer to receive the converted value.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EntsValueToStr (
  IN UINTN              Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a value to a string.

Arguments:

  Value   - Value to be converted.
  Buffer  - Receive string buffer pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EntsHexValueToStr (
  IN UINTN              Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a hexadecimal value to a string.

Arguments:

  Value   - Value to be converted.
  Buffer  - Pointer to string receive buffer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EntsStrToHexValue (
  IN CHAR16             *Buffer,
  OUT UINTN             *Value
  )
/*++

Routine Description:

  Convert a string to a hexadecimal value.

Arguments:

  Buffer  - String buffer to be converted.
  Value   - Receive value pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EntsBooleanToStr (
  IN BOOLEAN            Value,
  OUT CHAR16            *Buffer
  )
/*++

Routine Description:

  Convert a boolean to a string.

Arguments:

  Value   - Boolean value.
  Buffer  - Receive string buffer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_SUCCESS - Operation succeeded.

--*/
;

EFI_STATUS
EntsStrToBoolean (
  IN CHAR16             *Buffer,
  OUT BOOLEAN           *Value
  )
/*++

Routine Description:

  Convert a string to a boolean.

Arguments:

  Buffer  - String buffer to be converted.
  Value   - Receive value pointer.

Returns:

  EFI_INVALID_PARAMETER - Parameter invalid.
  EFI_UNSUPPORTED - String not supported.
  EFI_SUCCESS - Operation succeeded.
  
--*/
;

BOOLEAN
EntsStrBeginWith (
  IN CHAR16             *Str,
  IN CHAR16             *SubStr
  )
;

BOOLEAN
EntsStrEndWith (
  IN CHAR16             *Str,
  IN CHAR16             *SubStr
  )
/*++

Routine Description:

  Test if the string is end with the sub string.

Arguments:

  Str     - NULL ended string.
  SubStr  - NULL ended string.

Returns:

  TRUE    - Str ends with SubStr.
  FALSE   - Str does not end with SubStr.

--*/
;

CHAR16 *
EntsStrChr (
  IN  CHAR16  *Str,
  IN  CHAR16  c
  );

UINTN
EntsStrStr (
  IN  CHAR16  *Str,
  IN  CHAR16  *Pat
  )
/*++

Routine Description:

  Search Pat in Str.

Arguments:

  Str - String to be searched.
  Pat - Search pattern.

Returns:
  
  0 : not found
  >= 1 : found position + 1

--*/
;

UINTN
HexStringToValue (
  IN CHAR16             *String,
  IN UINTN              Length
  )
/*++

Routine Description:

  Convert a hex string to a value.

Arguments:

  String  - Hex string buffer.
  Length  - Hex string length.

Returns:

  Converted value.

--*/
;

INTN
a2i (
  IN CHAR16       Ch
  )
;

CHAR16
i2A (
  UINTN    x
  )
;

CHAR16
i2a (
  UINTN    x
  )
;

EFI_STATUS
EntsIpToStr (
  IN EFI_IP_ADDRESS       *IpAddr,
  IN UINTN                StrSize,
  IN OUT CHAR16           *Str
  )
;

EFI_STATUS
EntsStrToMac (
  IN CHAR16              *Str,
  IN OUT EFI_MAC_ADDRESS *MacAddr
  )
;

EFI_STATUS
EntsMacToStr (
  IN EFI_MAC_ADDRESS     *MacAddr,
  IN UINTN               StrSize,
  IN OUT CHAR16          *Str
  )
;

EFI_STATUS
EntsTimeToStr (
  IN EFI_TIME            *Time,
  IN UINTN               StrSize,
  IN OUT CHAR16          *Str
  )
;

EFI_STATUS
EntsStatusToStr (
  IN EFI_STATUS          Status,
  IN UINTN               StrSize,
  IN OUT CHAR16          *Str
  )
;

CHAR8
M2S (
  IN CHAR8                     Ch
  )
;

EFI_STATUS
MemToString (
  IN VOID                      *Mem,
  IN OUT CHAR16                *String,
  IN UINT32                    MemSize
  )
/*++

Routine Description:

  Convert Memory to a Unicode string.

Arguments:

  Mem     - Memory buffer to be converted.
  String  - Receive string buffer pointer.
  MemSize - Memory buffer size.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

CHAR8
S2M (
  IN CHAR8                     Ch
  )
;

EFI_STATUS
StringToMem (
  IN CHAR16                    *String,
  IN OUT VOID                  *Mem,
  IN UINT32                    MemSize
  )
/*++

Routine Description:

  Convert a Unicode string to Memory.

Arguments:

  String  - Unicode string buffer.
  Mem     - Receive memory buffer pointer.
  MemSize - Receive memory buffer size.

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

//
// Debug Level
//
#define EFI_ENTS_D_ERROR    0x01
#define EFI_ENTS_D_WARNING  0x02
#define EFI_ENTS_D_TRACE    0x04
#define EFI_ENTS_D_LEVEL    (EFI_ENTS_D_ERROR)

#define ENTS_DEBUG

#ifdef ENTS_DEBUG
#define EFI_ENTS_DEBUG(a)   EfiEntsDebug a
#define EFI_ENTS_STATUS(a)  EfiEntsStatus a
#else
#define EFI_ENTS_DEBUG(a)
#define EFI_ENTS_STATUS(a)
#endif

#define ENTS_MAX_BUFFER_SIZE              512
#define EFI_ENTS_FILE_LOG                 L"Ents.log"
#define EFI_NET_ASSERTION_RESULT_PASS     "PASS"
#define EFI_NET_ASSERTION_RESULT_FAIL     "FAIL"
#define EFI_NET_ASSERTION_RESULT_WARN     "WARN"
#define EFI_NET_ASSERTION_TYPE_ASSERTION  "ASSERTION"
#define EFI_NET_ASSERTION_TYPE_CASE_BEGN  "CASE_BEGN"
#define EFI_NET_ASSERTION_TYPE_CASE_OVER  "CASE_OVER"
#define EFI_NET_ASSERTION_MAX_LEN         1400
#define NET_ASSERTION_MSG_LEN             1024
#define NET_ASSERTION_MSG_HEADER_LEN      128
#define GUID_STRING_LEN                   37
#define RESULT_STRING_LEN                 5
#define TYPE_STRING_LEN                   10

//
// EFI_ENTS_DEBUG worker function
//
EFI_STATUS
EntsInitializeDebugServices (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath,
  IN CHAR16                       *FilePath
  )
/*++

Routine Description:

  Initialize the debug services.

Arguments:

  DevicePath  - Pointer to EFI_DEVICE_PATH_PROTOCOL instance.
  FilePath    - FilePath string.

Returns:

  EFI_SUCCESS          - Operation succeeded.
  EFI_OUT_OF_RESOURCES - Memory allocation failed.
  Others               - Some failure happened.

--*/
;

EFI_STATUS
CloseDebugServices (
  VOID
  )
/*++

Routine Description:

  Free the debug services.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.
  Others      - Some failure happened.

--*/
;

VOID
EfiEntsDebug (
  IN UINTN              Level,
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Ents debugging services.

Arguments:

  Level   - Debug level like ERROR, WARNING, TRACE etc.
  Format  - String format.
  ...     - Variables.

Returns:

  None.

--*/
;

//
// EFI_ENTS_STATUS worker function
//
VOID
EfiEntsStatus (
  IN CHAR16             *Format,
  ...
  )
/*++

Routine Description:

  Worker function for EFI_ENTS_STATUS marco.

Arguments:

  Format  - Format string.
  ...     - Variables.

Returns:

  None.

--*/
;

#define MINS_PER_HOUR   60
#define HOURS_PER_DAY   24
#define SECS_PER_MIN    60
#define SECS_PER_HOUR   (SECS_PER_MIN * MINS_PER_HOUR)
#define SECS_PER_DAY    (SECS_PER_HOUR * HOURS_PER_DAY)
#define DAYS_PER_NYEAR  365
#define DAYS_PER_LYEAR  366

UINT32
EntsSecondsElapsedFromBaseYear (
  IN UINT16             BaseYear,
  IN UINT16             Year,
  IN UINT8              Month,
  IN UINT8              Day,
  IN UINT8              Hour,
  IN UINT8              Minute,
  IN UINT8              Second
  )
/*++

Routine Description:

  Calculate the elapsed seconds from the base year.
  
Arguments:

  BaseYear  - The base year.
  Year      - Current year.
  Month     - Current month.
  Day       - Current day.
  Hour      - Current hour.
  Minute    - Current minute.
  Second    - Current second.

Returns:

  The elapsed seconds.

--*/
;

#pragma pack(1)
typedef struct ether_packet_struc {
  UINT8   DstMac[6];
  UINT8   SrcMac[6];
  UINT16  EtherType;
  UINT8   data[1];
} ETHER_PACKET;
#pragma pack()

#define ETHER_HEAD_LEN          (sizeof (ETHER_PACKET) - 1)

#define IP_FLAG_DF              (unsigned short) 0x4000
#define IP_FLAG_MF              (unsigned short) 0x2000
#define IP_OFFSET               (unsigned short) 0x1FFF

#define IP_PROTOCOL_ICMP        0x01
#define IP_PROTOCOL_IGMP        0x02
#define IP_PROTOCOL_GGP         0x03
#define IP_PROTOCOL_IP          0x04
#define IP_PROTOCOL_ST          0x05
#define IP_PROTOCOL_TCP         0x06
#define IP_PROTOCOL_UCL         0x07
#define IP_PROTOCOL_EGP         0x08
#define IP_PROTOCOL_IGP         0x09
#define IP_PROTOCOL_BBN_RCC_MON 0x0a
#define IP_PROTOCOL_NVP_II      0x0b
#define IP_PROTOCOL_PUP         0x0c
#define IP_PROTOCOL_ARGUS       0x0d
#define IP_PROTOCOL_EMCON       0x0e
#define IP_PROTOCOL_XNET        0x0f
#define IP_PROTOCOL_CHAOS       0x10
#define IP_PROTOCOL_UDP         (unsigned char) 0x11

#define IP_DEFAULT_TTL          (UINT8) 64
#define IP_DEFAULT_ID           (UINT16) 0x1234
#define IP_DEFAULT_TOS          (UINT8) 0

//
// IP4
//
#pragma pack(1)
typedef struct ipv4_packet_struc {
  char            verhlen;
  char            tos;
  unsigned short  totallen;
  unsigned short  id;
  unsigned short  flagoff;
  unsigned char   ttl;
  char            protocol;
  unsigned short  cksum;
  long            srcadd;
  long            dstadd;
  char            data[1];
} IPV4_PACKET;
#pragma pack()

#define IPV4_HEAD_LEN (sizeof (IPV4_PACKET) - 1)

//
// UDP4
//
#pragma pack(1)
typedef struct udp_packet_struc {
  unsigned short  udp_src;    /* source UDP port number 	 */
  unsigned short  udp_dst;    /* destination UDP port number	 */
  unsigned short  udp_len;    /* length of UDP data		 */
  unsigned short  udp_cksum;  /* UDP checksum (0 => none)	*/
  char            data[1];
} UDP_PACKET;
#pragma pack()

#define UDP_HEAD_LEN  (sizeof (UDP_PACKET) - 1)

//
// List entry - doubly linked list
// Redefined due to conflicts between Shell and EDK.
//
typedef struct _NET_SCT_LIST_ENTRY {
  struct _NET_SCT_LIST_ENTRY  *ForwardLink;
  struct _NET_SCT_LIST_ENTRY  *Blink;
} NET_SCT_LIST_ENTRY;

#define NetInitializeListHead(ListHead) \
  (ListHead)->ForwardLink = ListHead; \
  (ListHead)->Blink = ListHead;

#define NetIsListEmpty(ListHead)  ((BOOLEAN) ((ListHead)->ForwardLink == (ListHead)))

#define _NetRemoveEntryList(Entry) { \
    NET_SCT_LIST_ENTRY  *_Blink, *_ForwardLink; \
    _ForwardLink        = (Entry)->ForwardLink; \
    _Blink        = (Entry)->Blink; \
    _Blink->ForwardLink = _ForwardLink; \
    _ForwardLink->Blink = _Blink; \
  }

#ifdef EFI_DEBUG
#define NetRemoveEntryList(Entry) \
  _NetRemoveEntryList (Entry); \
  (Entry)->ForwardLink  = (NET_SCT_LIST_ENTRY *) EFI_BAD_POINTER; \
  (Entry)->Blink  = (NET_SCT_LIST_ENTRY *) EFI_BAD_POINTER;
#else
#define NetRemoveEntryList(Entry) _NetRemoveEntryList (Entry);
#endif

#define NetInsertTailList(ListHead, Entry) { \
    NET_SCT_LIST_ENTRY  *_ListHead, *_Blink; \
    _ListHead         = (ListHead); \
    _Blink            = _ListHead->Blink; \
    (Entry)->ForwardLink    = _ListHead; \
    (Entry)->Blink    = _Blink; \
    _Blink->ForwardLink     = (Entry); \
    _ListHead->Blink  = (Entry); \
  }

#define NetInsertHeadList(ListHead, Entry) { \
    NET_SCT_LIST_ENTRY  *_ListHead, *_ForwardLink; \
    _ListHead         = (ListHead); \
    _ForwardLink            = _ListHead->ForwardLink; \
    (Entry)->ForwardLink    = _ForwardLink; \
    (Entry)->Blink    = _ListHead; \
    _ForwardLink->Blink     = (Entry); \
    _ListHead->ForwardLink  = (Entry); \
  }

#define NetSwapListEntries(Entry1, Entry2) { \
    NET_SCT_LIST_ENTRY  *Entry1ForwardLink, *Entry1Blink; \
    NET_SCT_LIST_ENTRY  *Entry2ForwardLink, *Entry2Blink; \
    Entry2ForwardLink         = (Entry2)->ForwardLink; \
    Entry2Blink         = (Entry2)->Blink; \
    Entry1ForwardLink         = (Entry1)->ForwardLink; \
    Entry1Blink         = (Entry1)->Blink; \
    Entry2Blink->ForwardLink  = Entry2ForwardLink; \
    Entry2ForwardLink->Blink  = Entry2Blink; \
    (Entry2)->ForwardLink     = Entry1; \
    (Entry2)->Blink     = Entry1Blink; \
    Entry1Blink->ForwardLink  = (Entry2); \
    (Entry1)->Blink     = (Entry2); \
  }

#define NetListEntry(Entry, Type, Field) _CR(Entry, Type, Field)
#define NetListHead(ListHead, Type, Field) \
        NetListEntry((ListHead)->ForwardLink, Type, Field)
//
// NET_DEBUG_CACHE_BUFFER
//
typedef struct _NET_DEBUG_CACHE_BUFFER {
  CHAR8 * Message;
  UINT16 MessageLen;
  NET_SCT_LIST_ENTRY Entry;
} NET_DEBUG_CACHE_BUFFER;

//
//  UINT32 NTOHL(UINT32 x);
//
#define NTOHL(x)               \
  (UINT32)((((UINT32)(x) & 0xff     )<<24) | \
          (((UINT32)(x) & 0xff00    )<<8 ) | \
          (((UINT32)(x) & 0xff0000  )>>8 ) | \
          (((UINT32)(x) & 0xff000000)>>24)   \
         )

//
//  UINT16 NTOHS(UINT16 x);
//
#define NTOHS(x)           \
  (UINT16) ((((UINT16)(x) & 0xff  )<<8) | (((UINT16)(x) & 0xff00)>>8) )

//
//  UINT32 HTONL(UINT32 x)
//
#define  HTONL(x)           NTOHL(x)

//
//  UINT16 HTONS(UINT16 x)
//
#define  HTONS(x)           NTOHS(x)

//
//  EFI_FIELD_OFFSET - returns the byte offset to a field within a structure
//
#define EFI_FIELD_OFFSET(TYPE, Field) ((UINTN)(&(((TYPE *) 0)->Field)))

CHAR8 *
Unicode2Ascii (
  OUT CHAR8          *AsciiStr,
  IN  CHAR16         *UnicodeStr
  );

EFI_STATUS
NetAssertionUtilityInstall (
  VOID
  )
/*++

Routine Description:

  Used to initialize NetAssertionConfigData.

Arguments:

  None

Returns:

  EFI_SUCCESS - Operation succeeded.

--*/
;

VOID
NetAssertionUtilityUninstall (
  VOID
  );

EFI_STATUS
EntsLibLocateProtocol (
  IN  EFI_GUID    *ProtocolGuid,
  OUT VOID        **Interface
  )
/*++

Routine Description:

  Find the first instance of this Protocol in the system and return it's interface

Arguments:

  ProtocolGuid    - Provides the protocol to search for
  Interface       - On return, a pointer to the first interface that matches ProtocolGuid

Returns:

  EFI_SUCCESS     - A protocol instance matching ProtocolGuid was found

  EFI_NOT_FOUND   - No protocol instances were found that match ProtocolGuid

--*/
;

EFI_STATUS
EntsLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE       SearchType,
  IN EFI_GUID                     * Protocol OPTIONAL,
  IN VOID                         *SearchKey OPTIONAL,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  )
/*++

Routine Description:

  Function returns an array of handles that support the requested protocol
  in a buffer allocated from pool.

Arguments:

  SearchType           - Specifies which handle(s) are to be returned.
  Protocol             - Provides the protocol to search by.
                         This parameter is only valid for SearchType ByProtocol.
  SearchKey            - Supplies the search key depending on the SearchType.
  NoHandles            - The number of handles returned in Buffer.
  Buffer               - A pointer to the buffer to return the requested array of
                         handles that support Protocol.

Returns:

  EFI_SUCCESS           - The result array of handles was returned.
  EFI_NOT_FOUND         - No handles match the search.
  EFI_OUT_OF_RESOURCES - There is not enough pool memory to store the matching results.

--*/
;

//
// External functions declarations
//
UINTN
EntsPrint (
  IN CHAR16                         *fmt,
  ...
  )
/*++

Routine Description:

    Prints a formatted unicode string to the default console

Arguments:

    fmt         - Format string
    ...         - Variables.

Returns:

    Length of string printed to the console

--*/
;


UINTN
EntsNoPrint (
  IN CHAR16                         *fmt,
  ...
  )
;

//#define ENTS_OUTPUT

#ifdef ENTS_OUTPUT
#define EntsOutput EntsPrint
#else
#define EntsOutput EntsNoPrint
#endif

UINTN
EntsSPrint (
  OUT CHAR16                        *Str,
  IN UINTN                          StrSize,
  IN CHAR16                         *fmt,
  ...
  )
/*++

Routine Description:

    Prints a formatted unicode string to a buffer

Arguments:

    Str         - Output buffer to print the formatted string into

    StrSize     - Size of Str.  String is truncated to this size.
                  A size of 0 means there is no limit

    fmt         - The format string
    ...         - Variables.

Returns:

    String length returned in buffer

--*/
;

UINTN
EntsVSPrint (
  OUT CHAR16                        *Str,
  IN UINTN                          StrSize,
  IN CHAR16                         *fmt,
  IN VA_LIST                        vargs
  )
/*++

Routine Description:

    Prints a formatted unicode string to a buffer

Arguments:

    Str         - Output buffer to print the formatted string into
    StrSize     - Size of Str.  String is truncated to this size.
      A size of 0 means there is no limit
    fmt         - The format string
    vargs       - Variable list.

Returns:

    String length returned in buffer

--*/
;

UINTN
EntsASPrint (
  OUT CHAR8         *Buffer,
  IN  UINTN         BufferSize,
  IN  CONST CHAR8   *Format,
  ...
  )
;

CHAR16                          *
EntsPoolPrint (
  IN CHAR16                         *fmt,
  ...
  );

typedef struct {
  CHAR16            *str;
  UINTN             len;
  UINTN             maxlen;
} ENTS_POOL_PRINT;

CHAR16 *
EntsCatPrint (
  IN OUT ENTS_POOL_PRINT     *Str,
  IN CHAR16             *fmt,
  ...
  );

BOOLEAN
EntsGrowBuffer (
  IN OUT EFI_STATUS   *Status,
  IN OUT VOID         **Buffer,
  IN UINTN            BufferSize
  )
/*++

Routine Description:

    Helper function called as part of the code needed
    to allocate the proper sized buffer for various
    EFI interfaces.

Arguments:

    Status      - Current status

    Buffer      - Current allocated buffer, or NULL

    BufferSize  - Current buffer size needed

Returns:

    TRUE - if the buffer was reallocated and the caller
    should try the API again.

--*/
;

VOID
EntsZeroMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size
  )
/*++

Routine Description:

  Fills a buffer with zeros.

Arguments:

  Buffer                - A pointer to the buffer to fill with zeros.
  Size                  - Number of bytes to zero in the buffer.

Returns:

  None

--*/
;

VOID
EntsSetMem (
  IN VOID                           *Buffer,
  IN UINTN                          Size,
  IN UINT8                          Value
  )
/*++

Routine Description:

  Fills a buffer with a value.

Arguments:

  Buffer                - A pointer to the buffer to free.
  Size                  - The number of bytes in the buffer to fill.
  Value                 - The value to fill Buffer with.

Returns:

  None

--*/
;

VOID
EntsCopyMem (
  IN VOID                           *Dest,
  IN VOID                           *Src,
  IN UINTN                          len
  )
/*++

Routine Description:

  Copies the contents of one buffer to another.

Arguments:

  Dest                - A pointer to the buffer to copy to
  Src                 - A pointer to the buffer to copy from.
  len                 - The number of bytes to copy.

Returns:

  None

--*/
;

INTN
EntsCompareMem (
  IN VOID                           *Dest,
  IN VOID                           *Src,
  IN UINTN                          len
  )
/*++

Routine Description:

  Compares the contents of one buffer to another.

Arguments:

  Dest                - A pointer to the buffer to compare
  Src                 - A pointer to the buffer to compare
  len                 - The number of bytes to compare

Returns:

  0                   - Dest is identical to Src for len bytes.
  !=0                 - Dest is not identical to Src for len bytes.

--*/
;

VOID                            *
EntsAllocatePool (
  IN UINTN                          Size
  )
/*++

Routine Description:

  Allocates pool memory.

Arguments:

  Size                 - Size in bytes of the pool being requested.

Returns:
  EFI_SUCEESS          - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
;

VOID                            *
EntsAllocateZeroPool (
  IN UINTN                          Size
  )
/*++

Routine Description:

  Allocates pool memory and initializes the memory to zeros.

Arguments:

  Size                 - Size in bytes of the pool being requested.

Returns:
  EFI_SUCEESS          - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES - The pool requested could not be allocated.

--*/
;

VOID                            *
EntsReallocatePool (
  IN VOID                           *OldPool,
  IN UINTN                          OldSize,
  IN UINTN                          NewSize
  )
/*++

Routine Description:

  Adjusts the size of a previously allocated buffer.

Arguments:
  OldPool               - A pointer to the buffer whose size is being adjusted.
  OldSize               - The size of the current buffer.
  NewSize               - The size of the new buffer.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.
  EFI_OUT_OF_RESOURCES  - The pool requested could not be allocated.
  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
;

VOID
EntsFreePool (
  IN VOID                           *p
  )
/*++

Routine Description:

  Releases a previously allocated buffer.

Arguments:

  P                     - A pointer to the buffer to free.

Returns:

  EFI_SUCEESS           - The requested number of bytes were allocated.
  EFI_INVALID_PARAMETER - The buffer was invalid.

--*/
;

VOID
EntsGuidToString (
  OUT CHAR16                        *Buffer,
  IN EFI_GUID                       *Guid
  )
/*++

Routine Description:

  Converts Guid to a string

Arguments:

  Buffer      - On return, a pointer to the buffer which contains the string.
  Guid        - guid to compare

Returns:
  none

--*/
;

INTN
EntsCompareGuid (
  IN EFI_GUID                       *Guid1,
  IN EFI_GUID                       *Guid2
  )
/*++

Routine Description:

  Compares to GUIDs

Arguments:

  Guid1       - guid to compare
  Guid2       - guid to compare

Returns:
  0           - if Guid1 == Guid2

--*/
;

UINT64
SctRShiftU64 (
  IN UINT64                         Operand,
  IN UINTN                          Count
  )
;

UINT64
SctDivU64x32 (
  IN UINT64                         Dividend,
  IN UINTN                          Divisor,
  OUT UINTN                         *Remainder OPTIONAL
  )
;

EFI_STATUS
EntsWaitForSingleEvent (
  IN EFI_EVENT                                                Event,
  IN UINT64                                                   Timeout OPTIONAL
  )
/*++

Routine Description:

  Function waits for a given event to fire, or for an optional timeout to expire.

Arguments:
  Event            - The event to wait for

  Timeout          - An optional timeout value in 100 ns units.

Returns:

  EFI_SUCCESS       - Event fired before Timeout expired.
  EFI_TIME_OUT     - Timout expired before Event fired..

--*/
;

EFI_DEVICE_PATH_PROTOCOL        *
EntsDuplicateDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:

  Function creates a duplicate copy of an existing device path.

Arguments:

  DevPath        - A pointer to a device path data structure

Returns:

  If the memory is successfully allocated, then the contents of DevPath are copied
  to the newly allocated buffer, and a pointer to that buffer is returned.
  Otherwise, NULL is returned.

--*/
;

EFI_DEVICE_PATH_PROTOCOL        *
EntsUnpackDevicePath (
  IN EFI_DEVICE_PATH_PROTOCOL  *DevPath
  )
/*++

Routine Description:

  Function unpacks a device path data structure so that all the nodes of a device path
  are naturally aligned.

Arguments:

  DevPath        - A pointer to a device path data structure

Returns:

  If the memory for the device path is successfully allocated, then a pointer to the
  new device path is returned.  Otherwise, NULL is returned.

--*/
;

CHAR16 *
EntsDevicePathToStr (
  EFI_DEVICE_PATH_PROTOCOL                     *DevPath
  );

EFI_STATUS
SetContextRecord (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName,
  IN CHAR16                                    *Key,
  IN UINTN                                     Size,
  IN VOID                                      *Value
  );

EFI_STATUS
GetContextRecord (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName,
  IN CHAR16                                    *Key,
  IN UINTN                                     *BufSize, 
  OUT VOID                                     *RecordBuf
  );

EFI_STATUS
PassiveTestContextCreate (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName
  );

EFI_STATUS
PassiveTestContextDelete (
  IN EFI_DEVICE_PATH_PROTOCOL                  *DevicePath,
  IN CHAR16                                    *FileName
  );

EFI_STATUS
EntsNetworkServiceBindingGetControllerHandle (
  IN  EFI_GUID                 *ProtocolGuid,
  OUT EFI_HANDLE               *ClientHandle
  );

VOID
EntsChooseNICAndSave (
  VOID
  );

EFI_STATUS
GetMacAddress (
  OUT UINT8                         *MacAddr
  );

EFI_STATUS
CreateFile (
  IN EFI_FILE_HANDLE              RootDir,
  IN CHAR16                       *FileName,
  OUT EFI_FILE_HANDLE             *Handle
  );

#endif
