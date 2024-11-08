## @file
#
#  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
#  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
#  Copyright (c) 2019,Microchip Technology Inc.<BR>
#  (C) Copyright 2021 Hewlett Packard Enterprise Development LP<BR>
#  Copyright (c) 2023, Loongson Technology Corporation Limited. All rights reserved.<BR>
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
##
#/*++
#
# Module Name:
#
#    IHV_SCT.dsc
#
# Abstract:
#
#   This is a build description file used to build the test modules for IHV SCT
#
# Notes:
#
#   The info in this file is broken down into sections. The start of a section
#   is designated by a "[" in the first column. So the [=====] separater ends
#   a section.
#
#--*/

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = IhvSct
  PLATFORM_GUID                  = 81ae3da4-3e91-4611-9015-eabc96b5e556
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/IhvSct
  SUPPORTED_ARCHITECTURES        = IA32|X64|ARM|AARCH64|RISCV64|LOONGARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

################################################################################
#
# SKU Identification section - list of all SKU IDs supported by this
#                              Platform.
#
################################################################################
[SkuIds]
  0|DEFAULT              # The entry: 0|DEFAULT is reserved and always required.

[BuildOptions]
  MSFT:*_*_IA32_CC_FLAGS    = /D EFI32 /wd4133 /Od
  MSFT:*_*_IA32_ASM_FLAGS   = /DEFI32
  MSFT:*_*_IA32_VFRPP_FLAGS = /D EFI32
  MSFT:*_*_IA32_APP_FLAGS   = /D EFI32
  MSFT:*_*_IA32_PP_FLAGS    = /D EFI32

  MSFT:*_*_X64_CC_FLAGS    = /D EFIX64 /wd4133 /Od
  MSFT:*_*_X64_ASM_FLAGS   = /DEFIX64
  MSFT:*_*_X64_VFRPP_FLAGS = /D EFIX64
  MSFT:*_*_X64_APP_FLAGS   = /D EFIX64
  MSFT:*_*_X64_PP_FLAGS    = /D EFIX64

#  GCC:*_*_IA32_CC_FLAGS     = -D EFI32 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error -mno-red-zone -Wno-address -mno-stack-arg-probe "-DEFIAPI=__attribute__((ms_abi))" -m32 -mabi=ms -D MDE_CPU_X32
   GCC:*_*_IA32_CC_FLAGS     = -D EFIX64 $(GCC_VER_MACRO) -Wno-error 
#  GCC:*_*_IA32_VFRPP_FLAGS  = -D EFI32 $(GCC_VER_MACRO)
#  GCC:*_*_IA32_APP_FLAGS    = -D EFI32 $(GCC_VER_MACRO)
#  GCC:*_*_IA32_PP_FLAGS     = -D EFI32 $(GCC_VER_MACRO)

#  GCC:*_*_X64_CC_FLAGS     = -D EFIX64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error -mno-red-zone -Wno-address -mno-stack-arg-probe "-DEFIAPI=__attribute__((ms_abi))" -m64 -mcmodel=large -mabi=ms -D MDE_CPU_X64

   GCC:*_*_X64_CC_FLAGS     = -D EFIX64 $(GCC_VER_MACRO) -Wno-error 
#  GCC:*_*_X64_VFRPP_FLAGS  = -D EFIX64 $(GCC_VER_MACRO)
#  GCC:*_*_X64_APP_FLAGS    = -D EFIX64 $(GCC_VER_MACRO)
#  GCC:*_*_X64_PP_FLAGS     = -D EFIX64 $(GCC_VER_MACRO)
#  GCC:*_*_X64_ASM_FLAGS    = -DEFIX64

  #TODO: OM - fixme RVCT:*_*_ARM_CC_FLAGS = -D EFIARM $(GCC_VER_MACRO)
  *_*_ARM_CC_FLAGS = -D EFIARM
  GCC:*_*_ARM_CC_FLAGS  = -D EFIARM $(GCC_VER_MACRO) -fno-stack-protector -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error=implicit-function-declaration -Wno-error
  *_*_ARM_VFRPP_FLAGS   = -D EFIARM $(GCC_VER_MACRO)
  *_*_ARM_APP_FLAGS     = -D EFIARM $(GCC_VER_MACRO)
  *_*_ARM_PP_FLAGS      = -D EFIARM $(GCC_VER_MACRO)

  RVCT:*_*_ARM_DLINK_FLAGS = --muldefweak
# 167:  "argument of type <type1> is incompatible with parameter of type # <type2>"
#       (caused here by passing typed pointers to functions that take "void *" or "void **")
# 1295: "provide arguments" (i.e. `UINTN Function ()` should be `UINTN Function (VOID)`)
# 188:  "enumerated type mixed with another type"
#       (i.e. passing an integer as an enum without a cast)
# 550:  "variable <var> was set but never used"
# 1:    "last line of file ends without a newline"
# 68:   "integer conversion resulted in a change of sign" ("if (Status == -1)")
# 111:  "statement is unreachable" (invariably "break;" after "return X;" in case statement)
# 177:  "function <static function> was declared but never referenced"
  RVCT:*_*_ARM_CC_FLAGS    = --diag_remark=167 --diag_suppress=167,1295,188,550,1,68,111,177

  *_*_AARCH64_CC_FLAGS         = -D EFIAARCH64 $(GCC_VER_MACRO)
  GCC:*_*_AARCH64_CC_FLAGS     = -D EFIAARCH64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error
  *_*_AARCH64_VFRPP_FLAGS      = -D EFIAARCH64 $(GCC_VER_MACRO)
  *_*_AARCH64_APP_FLAGS        = -D EFIAARCH64 $(GCC_VER_MACRO)
  *_*_AARCH64_PP_FLAGS         = -D EFIAARCH64 $(GCC_VER_MACRO)
  RVCT:*_*_AARCH64_DLINK_FLAGS = --muldefweak

  *_*_RISCV64_CC_FLAGS         = -D EFIRISCV64 $(GCC_VER_MACRO)
  GCC:*_*_RISCV64_CC_FLAGS  = -D EFIRISCV64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error
  *_*_RISCV64_VFRPP_FLAGS      = -D EFIRISCV64 $(GCC_VER_MACRO)
  *_*_RISCV64_APP_FLAGS        = -D EFIRISCV64 $(GCC_VER_MACRO)
  *_*_RISCV64_PP_FLAGS         = -D EFIRISCV64 $(GCC_VER_MACRO)

  *_*_LOONGARCH64_CC_FLAGS     = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  GCC:*_*_LOONGARCH64_CC_FLAGS = -D EFILOONGARCH64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error
  *_*_LOONGARCH64_VFRPP_FLAGS  = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  *_*_LOONGARCH64_APP_FLAGS    = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  *_*_LOONGARCH64_PP_FLAGS     = -D EFILOONGARCH64 $(GCC_VER_MACRO)

  DEBUG_*_*_CC_FLAGS  = -DEFI_DEBUG
  RELEASE_*_*_CC_FLAGS  = -DMDEPKG_NDEBUG

[Libraries]
  SctPkg/Library/SctLib/SctLib.inf
  SctPkg/Library/EfiTestLib/EfiTestLib.inf
  SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasLib/EntsLib.inf
  MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf

[Libraries.IA32,Libraries.X64]

!include MdePkg/MdeLibs.dsc.inc

[LibraryClasses.common]
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  SctLib|SctPkg/Library/SctLib/SctLib.inf
  NetLib|SctPkg/Library/NetLib/NetLib.inf
  EntsLib|SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasLib/EntsLib.inf
  EasLib|SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasDispatcher/Eas.inf
  EfiTestLib|SctPkg/Library/EfiTestLib/EfiTestLib.inf

[LibraryClasses.IA32]

###############################################################################
#
# These are the components that will be built by the master makefile
#
###############################################################################

[Components]

#
# The default package
#
DEFINE PACKAGE=Default

#
# Components
#

#
# Following are the SCT suite & related drivers
#

#SctPkg/TestInfrastructure/SCT/Framework/Sct.inf
SctPkg/TestInfrastructure/SCT/Drivers/StandardTest/StandardTest.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestProfile/TestProfile.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestRecovery/TestRecovery.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestLogging/TestLogging.inf

#
# Related SCT applications
#

SctPkg/Application/InstallSct/InstallSct.inf
SctPkg/Application/StallForKey/StallForKey.inf

#
# Test cases for UEFI/IHV SCT
#

SctPkg/TestCase/UEFI/IHV/Protocol/BlockIo/BlackBoxTest/IhvBlockIoBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/BlockIo2/BlackBoxTest/IhvBlockIo2BBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/BusSpecificDriverOverride/BlackBoxTest/IhvBusSpecificDriverOverrideBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/ComponentName2/BlackBoxTest/IhvComponentName2BBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/DevicePath/BlackBoxTest/IhvDevicePathBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/DiskIo/BlackBoxTest/IhvDiskIoBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/DiskIo2/BlackBoxTest/IhvDiskIo2BBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/DriverBinding/BlackBoxTest/IhvDriverBindingBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/DriverDiagnostics2/BlackBoxTest/IhvDriverDiagnostics2BBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/Ebc/BlackBoxTest/IhvEbcBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/PxeBaseCode/BlackBoxTest/IhvPxeBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/ScsiPassThru/BlackBoxTest/IhvScsiPassThruBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SerialIo/BlackBoxTest/IhvSerialIoBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimpleFileSystem/BlackBoxTest/IhvSimpleFileSystemBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimpleNetwork/BlackBoxTest/IhvSimpleNetworkBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimplePointer/BlackBoxTest/IhvSimplePointerBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimpleTextIn/BlackBoxTest/IhvSimpleTextInBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimpleTextInputEx/BlackBoxTest/IhvSimpleTextInputExBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/SimpleTextOut/BlackBoxTest/IhvSimpleTextOutBBTest_uefi.inf
SctPkg/TestCase/UEFI/IHV/Protocol/UnicodeCollation2/BlackBoxTest/IhvUnicodeCollation2BBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/Usb2Hc/BlackBoxTest/IhvUsb2HcTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/UsbIo/BlackBoxTest/IhvUsbIoTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/GraphicsOutput/BlackBoxTest/IhvGraphicsOutputBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/ExtScsiPassThru/BlackBoxTest/IhvExtScsiPassThruBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/ScsiIo/BlackBoxTest/IhvScsiIoBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/HIIConfigAccess/BlackBoxTest/IhvHIIConfigAccessBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/iScsiInitiatorName/BlackBoxTest/IhviScsiInitiatorNameBBTest.inf

SctPkg/TestCase/UEFI/IHV/Protocol/AbsolutePointer/BlackBoxTest/IhvAbsolutePointerBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/FirmwareManagement/BlackBoxTest/IhvFirmwareManagementBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/StorageSecurityCommand/BlackBoxTest/IhvStorageSecurityCommandBBTest.inf

SctPkg/TestCase/UEFI/IHV/Protocol/AdapterInfo/BlackBoxTest/IhvAdapterInfoBBTest.inf
#
# Dependency files for UEFI/IHV Test
#
SctPkg/TestCase/UEFI/IHV/Protocol/Ebc/BlackBoxTest/Dependency/EbcDriverBin/EbcDriverBin.inf

SctPkg/TestInfrastructure/SCT/Framework/Sct.inf

[Components.IA32, Components.X64]
SctPkg/TestCase/UEFI/IHV/Protocol/PlatformDriverOverride/BlackBoxTest/IhvPlatformDriverOverrideBBTest.inf
SctPkg/TestCase/UEFI/IHV/Protocol/PlatformToDriverConfiguration/BlackBoxTest/IhvPlatformToDriverConfigurationBBTest.inf
