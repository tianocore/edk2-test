/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  SCRTDriver.h

--*/

#ifndef _SCRT_DRIVER_H_
#define _SCRT_DRIVER_H_

#include "SctLib.h"
#include "Guid.h"
#include EFI_GUID_DEFINITION(GlobalVariable)

#include <PiPei.h>
#include <Ppi/CpuIo.h>

#include <Library/BaseLib.h>

extern EFI_RUNTIME_SERVICES            *VRT;

//
// Define for SetVariable/GetVariable Function Test
//
#define MAX_BUFFER_SIZE    256
#define SCRTFuncName       L"Runtime Test Function"

#define RUNTIME_FUNC_ADDRESS_GUID \
  { \
    0x8BA20E61, 0x92AA, 0x11d2, {0x07, 0x0E, 0x02, 0xE0, 0x98, 0x03, 0x2B, 0x8C } \
  }

#define VARIABLE_TEST_GUID \
{ 0x686adbc6, 0xf83c, 0x414a, {0x98, 0x79, 0x2c, 0x48, 0x8e, 0x8d, 0x39, 0x3c }}

#define  TEST_RECORD_GUID    \
{ 0x6205d3e7, 0x9bde, 0x4e81, {0x8a, 0xb8, 0xf4, 0x5f, 0xa7, 0xed, 0x46, 0x6 }}

//
// Define for UpdateCapsule/QueryCapsuleCapabilities Function Test
//
#define TEST_CAPSULE_GUID \
  {0x3B6686BD, 0x0D76, 0x4030, {0xB7, 0x0E, 0xB5, 0x51, 0x9E, 0x2F, 0xC5, 0xA0 }}

typedef struct {
  EFI_CAPSULE_HEADER  CapsuleHeader;
  UINT32              CapsuleBody[256];
}CAPSULE_IMAGE;


typedef struct {
  UINT64                 Signature;
  EFI_PHYSICAL_ADDRESS   FuncAddr; 
} SCRT_STUB_TABLE;

#define SCRT_STUB_TABLE_SIGNATURE          0x5AA55AA5
#define CONFIGURE_INFO_SIGNATURE          0x5AA5

//
// EFI Test Assertion Types
//
typedef enum {
  EFI_TEST_ASSERTION_PASSED,
  EFI_TEST_ASSERTION_WARNING,
  EFI_TEST_ASSERTION_FAILED
} EFI_TEST_ASSERTION;

//
// Configuration File Info
//
typedef union _CONF_INFO
{
  struct {
  UINT32 SetVariable        : 1;
  UINT32 GetVariable        : 1;
  UINT32 GetNextVariable    : 1;
  UINT32 QueryVariable      : 1;
  UINT32 GetTime            : 1;
  UINT32 SetTime            : 1;
  UINT32 SetWakeupTime      : 1;
  UINT32 GetWakeupTime      : 1;
  UINT32 QueryCapsule       : 1;
  UINT32 UpdateCapsule      : 1;
  UINT32 GetNextCount       : 1;
  UINT32 ColdReset          : 1;
  UINT32 WarmReset          : 1;
  UINT32 ShutDown           : 1;
  UINT32 Reserved           : 2;
  UINT32 Signature          : 16;
  } BitMap;
  UINT32  InfoData;
} CONF_INFO;


typedef struct _DEBUGGER_INFO
{
  BOOLEAN               MmioFlag;
  UINTN                 IoPort;
  UINTN                 IoBase;
  UINTN                 MmioBase;
} DEBUGGER_INFO;


typedef struct  _RUNTIME_HANDOFF{
  CONF_INFO         ConfigureInfo;
  DEBUGGER_INFO     DebuggerInfo;
}RUNTIME_HANDOFF; 


#pragma pack(1)

typedef union _VAR_INFO
{
  struct {
    UINT16 SetVariable        : 1;
    UINT16 GetVariable        : 1;
    UINT16 GetNextVariable    : 1;
    UINT16 QueryVariable      : 1;
    UINT16 GetTime            : 1;
    UINT16 SetTime            : 1;
    UINT16 SetWakeupTime      : 1;
    UINT16 GetWakeupTime      : 1;
    UINT16 QueryCapsule       : 1;
    UINT16 UpdateCapsule      : 1;
    UINT16 GetNextCount       : 1;
    UINT16 ColdReset          : 1;
    UINT16 WarmReset          : 1;
    UINT16 ShutDown           : 1;
    UINT16 Reserved           : 2;
  } BitMap;
  UINT16   TestData;
} VAR_INFO;

typedef struct _TEST_RECORD
{
  VAR_INFO Request;
  VAR_INFO  Result;
} TEST_RECORD;

#pragma pack()

//
// Define for debug function
//
VOID 
Port80 ( 
  UINT8 num
  )
/*++

Routine Description:

  Print a Hex number to I/O 80h

Arguments:

  num  - a Hex number

Returns:

  NONE
  
--*/  
;


VOID 
Printf (
  IN   CHAR8  *Format,
  ...
  )
/*++

Routine Description:

  Print a formatted string to COM1 and COM2 synchronously.

Arguments:

  Format  - Format string.
  ...     - Vararg list consumed by processing Format.
 
Returns:

  NONE

--*/  
;

VOID 
RecordAssertion (
  IN   EFI_TEST_ASSERTION    Status,
  IN   EFI_GUID              EventId,
  IN   CHAR8                *Description,
  IN   CHAR8                *Format,
  ...
  )
/*++

Routine Description:

  Print a formatted string specially for checkpoint to COM1 and COM2 synchronously.

Arguments:

  Status           - Checkpoint Status.
  EventId          - Checkpoint related unique GUID
  Description      - Checkpoint concise description
  Format           - Format string
  ...              - Vararg list consumed by processing Format.
  
Returns:

  NONE

--*/ 
;


EFI_STATUS
EFIAPI
InitializeSCRTDriver (
  IN EFI_HANDLE              ImageHandle,
  IN EFI_SYSTEM_TABLE        *SystemTable
  )
/*++

Routine Description:

  This function does initialization for SCRTDriver

Arguments:

  ImageHandle   - The firmware allocated handle for the EFI image.
  SystemTable   - A pointer to the EFI System Table.

Returns:
  
  Status code
  
--*/ 
;

EFI_STATUS
EFIAPI
RuntimeTestFunc (
  UINTN   ConfigInfo
  )
/*++

Routine Description:

  Perform runtime service test in a virtual addressing mode.
  
Arguments:

  NONE

Returns:

  NONE
  
--*/ 
;


//
// Define for test case
//
VOID
EfiVariableTestVirtual (
  CONF_INFO  *ConfigData
  )
/*++

Routine Description:

  Test Variable related Runtime Service in runtime phase.

Arguments:
   
   NONE
   
Returns:

   NONE
--*/
;

VOID
EfiTimeTestVirtual (
  CONF_INFO  *ConfigData
  )
/*++

Routine Description:

  Test Time related Runtime Service in runtime phase.

Arguments:
   
   NONE
   
Returns:

   NONE
--*/  
;

VOID
EfiCapsuleTestVirtual (
  CONF_INFO  *ConfigData
  )
/*++

Routine Description:

  Test capsule related Runtime Service in runtime phase.

Arguments:
   
   NONE
   
Returns:

   NONE
--*/
;

VOID
EfiMiscTestVirtual (
  CONF_INFO  *ConfigData
  )
/*++

Routine Description:

  Test GetNextHighMonotonicCount Runtime Service in runtime phase.

Arguments:
   
   NONE
   
Returns:

   NONE
--*/   
;

VOID
EfiResetTestVirtual (
  CONF_INFO  *ConfigData
  )
/*++

Routine Description:

  Test Reset related Runtime Service in runtime phase.

Arguments:
   
   NONE
   
Returns:

   NONE
--*/ 
;


EFI_STATUS
DebugWorker (
  IN CHAR8    *String 
  )
;

EFI_STATUS
ConsumeHandOff (
  IN  UINTN         HandOffAddr,
  OUT CONF_INFO     *ConfigData
  );


VOID
FixAddress (
  IN UINTN     *PhyAddress
  );

VOID
InitVariableRecord (
  CONF_INFO    *ConfigData
  );

VOID
DumpRuntimeTable(VOID);

EFI_STATUS
EfiIoRead (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  );

EFI_STATUS
EfiIoWrite (
  IN     EFI_PEI_CPU_IO_PPI_WIDTH  Width,
  IN     UINT64                     Address,
  IN     UINTN                      Count,
  IN OUT VOID                       *Buffer
  );

#endif
