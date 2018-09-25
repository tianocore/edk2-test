/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  common.h

Abstract:

  Common header file of Pci Rom Test.

--*/

#ifndef _COMMON_H_
#define _COMMON_H_

#include "SctLib.h"
#include <IndustryStandard/Pci22.h>

#include <UEFI/Protocol/PciRootBridgeIo.h>

//
//Test card types
//

#define NC_NEW_CARD               2
#define MAX_STRING_LENGTH         256
//
// Definitions required for new test card
//

#define NC_ROM_TOP_ADDRESS          0x38000
#define NC_BYTES_PER_FUNCTION       0x100
#define NC_MAX_FUNCTION             0x8
#define NC_MODE3_BIT                0x00000080
#define NC_MODE3_INT_BIT            0x00000400
#define NC_ROM_64K_BIT              0x00040000
#define NC_ROM_128K_BIT             0x00080000
#define NC_ROM_224K_BIT             0x000c0000
#define NC_MASTER_CTRL_REG          0x40
#define NC_MEMORY_ADDRESS_REG       0x44
#define NC_MEMORY_DATA_REG          0x48
#define NC_EXPROM_REG               0x54
#define NC_OFF_SP_CTRL              0x0B9
#define NC_OFF_MASK                 0x100
#define NC_FUNC0_ENABLE             0x01000000
#define NC_MEM_BA_BIT               0x0
#define NC_IO_BA_BIT                0x1
#define NC_RESET_BIT                0x00000001
#define NC_REVISION_ID              0x05
#define NC_INTA_MASK                0x00000100
#define NC_INTB_MASK                0x00000200
#define NC_INTC_MASK                0x00000400
#define NC_INTD_MASK                0x00000800

//
// Configuration Space Header Offsets
//
#define OFF_VENDOR_ID             0x00
#define OFF_DEVICE_ID             0x02
#define OFF_COMMAND               0x04
#define OFF_STATUS                0x06
#define OFF_REVISION_ID           0x08
#define OFF_PROG_IN               0x09
#define OFF_SUB_CLASS             0x0a
#define OFF_BASE_CLASS            0x0b
#define OFF_CACHELS               0x0c
#define OFF_LATTIMER              0x0d
#define OFF_HEADERTYPE            0x0e
#define OFF_BIST                  0x0f
#define OFF_INTLINE               0x3c

//
// Offsets Specific To Header Type 0
//
#define OFF_BASE0                 0x10
#define OFF_BASE1                 0x14
#define OFF_BASE2                 0x18
#define OFF_BASE3                 0x1c
#define OFF_BASE4                 0x20
#define OFF_BASE5                 0x24
#define OFF_EXP_ROM               0x30


//
// Offsets Specific To Special Add-In Card
//
#define OFF_SP_STATE              0x0b4
#define OFF_SP_EXPECTED           0x0b6
#define OFF_SP_EX_DONT_CARE       0x0b8
#define OFF_SP_RUNTIME            0x0b5
#define OFF_SP_IMGADDR            0x0b6
#define OFF_SP_EXP_ROM            0x0b0
#define OFF_SP_DEV_ID             0x002
#define OFF_SP_BA                 0x090

//
// Device basic Info
//

typedef struct {
  UINT16              DevId;
  UINT16              VenId;
  UINT16              Command;
  UINT16              Status;
  UINT8               RevId;
  UINT32              ClassCode;
  UINT8               CacheLS;
  UINT8               HeaderType;
  UINT8               LatencyTimer;
  UINT8               Bist;
  UINT8               SegNum;
  UINT8               BusNum;
  UINT8               DevNum;
  UINT8               FuncNum;
  UINT8               CardId;
  UINT8               CardType;
  UINT32              ROMMask;
  UINT32              Scratch;
} DevInfo;

//
// PCI Device
//
typedef struct _PCIDev{
  EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL   *RootBridgeIo;
  DevInfo                           BaseInfo;
} PCIDev;

#endif
