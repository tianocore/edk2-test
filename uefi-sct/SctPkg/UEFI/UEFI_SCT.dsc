## @file
#
#  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
#  Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
#  (C) Copyright 2017 - 2021 Hewlett Packard Enterprise Development LP<BR>
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
#    UEFI_SCT.dsc
#
# Abstract:
#
#   This is a build description file used to build the test modules of UEFI SCT.
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
  PLATFORM_NAME                  = UefiSct
  PLATFORM_GUID                  = 81ae3da4-3e91-4611-9015-eabc96b5e556
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/UefiSct
  SUPPORTED_ARCHITECTURES        = IA32|X64|ARM|AARCH64|RISCV64|LOONGARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  
  DEFINE GCC_VER_MACRO           =
  DEFINE MSFT_VER_MACRO          =


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
  MSFT:*_*_IA32_ASM_FLAGS   = /D EFI32
  MSFT:*_*_IA32_VFRPP_FLAGS = /D EFI32
  MSFT:*_*_IA32_APP_FLAGS   = /D EFI32
  MSFT:*_*_IA32_PP_FLAGS    = /D EFI32

  MSFT:*_*_X64_CC_FLAGS    = /D EFIX64 /wd4133 /Od
  MSFT:*_*_X64_ASM_FLAGS   = /D EFIX64
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
  GCC:*_*_RISCV64_CC_FLAGS     = -D EFIRISCV64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error
  *_*_RISCV64_VFRPP_FLAGS      = -D EFIRISCV64 $(GCC_VER_MACRO)
  *_*_RISCV64_APP_FLAGS        = -D EFIRISCV64 $(GCC_VER_MACRO)
  *_*_RISCV64_PP_FLAGS         = -D EFIRISCV64 $(GCC_VER_MACRO)

  *_*_LOONGARCH64_CC_FLAGS         = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  GCC:*_*_LOONGARCH64_CC_FLAGS     = -D EFILOONGARCH64 $(GCC_VER_MACRO) -ffreestanding -nostdinc -nostdlib -Wno-error=unused-function -Wno-error=unused-but-set-variable -Wno-error
  *_*_LOONGARCH64_VFRPP_FLAGS      = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  *_*_LOONGARCH64_APP_FLAGS        = -D EFILOONGARCH64 $(GCC_VER_MACRO)
  *_*_LOONGARCH64_PP_FLAGS         = -D EFILOONGARCH64 $(GCC_VER_MACRO)

  DEBUG_*_*_CC_FLAGS  = -DEFI_DEBUG
  RELEASE_*_*_CC_FLAGS  = -DMDEPKG_NDEBUG

[Libraries]
  SctPkg/Library/SctLib/SctLib.inf
  SctPkg/Library/EfiTestLib/EfiTestLib.inf

  SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasLib/EntsLib.inf

  MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf

!include MdePkg/MdeLibs.dsc.inc

[LibraryClasses.common]
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf

  SctLib|SctPkg/Library/SctLib/SctLib.inf
  NetLib|SctPkg/Library/NetLib/NetLib.inf
  EntsLib|SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasLib/EntsLib.inf
  EasLib|SctPkg/TestInfrastructure/SCT/Framework/ENTS/EasDispatcher/Eas.inf
  EfiTestLib|SctPkg/Library/EfiTestLib/EfiTestLib.inf

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

SctPkg/TestInfrastructure/SCT/Framework/Sct.inf
SctPkg/TestInfrastructure/SCT/Drivers/StandardTest/StandardTest.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestProfile/TestProfile.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestRecovery/TestRecovery.inf
SctPkg/TestInfrastructure/SCT/Drivers/TestLogging/TestLogging.inf

#
# Related SCT applications
#

SctPkg/Application/InstallSct/InstallSct.inf
SctPkg/Application/StallForKey/StallForKey.inf

SctPkg/SCRT/SCRTApp/SCRTApp.inf
SctPkg/SCRT/SCRTDriver/SCRTDriver.inf

#
# Test cases for UEFI SCT and UEFI/EFI SCT
#

SctPkg/TestCase/UEFI/EFI/Generic/EfiCompliant/BlackBoxTest/EfiCompliantBBTest_uefi.inf
SctPkg/TestCase/UEFI/EFI/BootServices/EventTimerTaskPriorityServices/BlackBoxTest/EventTimerTaskPriorityServicesBBTest_uefi.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/ImageBBTest.inf
SctPkg/TestCase/UEFI/EFI/BootServices/MemoryAllocationServices/BlackBoxTest/MemoryAllocationServicesBBTest.inf
SctPkg/TestCase/UEFI/EFI/BootServices/MiscBootServices/BlackBoxTest/MiscBootServicesBBTest.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/ProtocolHandlerBBTest.inf

SctPkg/TestCase/UEFI/EFI/RuntimeServices/MiscRuntimeServices/BlackBoxTest/MiscRuntimeServicesBBTest.inf
SctPkg/TestCase/UEFI/EFI/RuntimeServices/TimeServices/BlackBoxTest/TimeServicesBBTest.inf
SctPkg/TestCase/UEFI/EFI/RuntimeServices/VariableServices/BlackBoxTest/VariableServicesBBTest.inf
SctPkg/TestCase/UEFI/EFI/RuntimeServices/TCGMemoryOverwriteRequest/BlackBoxTest/TCGMemoryOverwriteRequestBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/GraphicsOutput/BlackBoxTest/GraphicsOutputBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Bis/BlackBoxTest/BisBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/BlockIo/BlackBoxTest/BlockIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/BlockIo2/BlackBoxTest/BlockIo2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/BusSpecificDriverOverride/BlackBoxTest/BusSpecificDriverOverrideBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DebugPort/BlackBoxTest/DebugPortBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DebugSupport/BlackBoxTest/DebugSupportBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/DecompressBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DevicePath/BlackBoxTest/DevicePathBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DevicePathUtilities/BlackBoxTest/DevicePathUtilitiesBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DevicePathToText/BlackBoxTest/DevicePathToTextBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DevicePathFromText/BlackBoxTest/DevicePathFromTextBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DiskIo/BlackBoxTest/DiskIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/DiskIo2/BlackBoxTest/DiskIo2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Ebc/BlackBoxTest/EbcBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/LoadedImageBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadFile/BlackBoxTest/LoadFileBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PciIo/BlackBoxTest/PciIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PciRootBridgeIo/BlackBoxTest/PciRootBridgeIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PlatformDriverOverride/BlackBoxTest/PlatformDriverOverrideBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PxeBaseCode/BlackBoxTest/PxeBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ScsiIo/BlackBoxTest/ScsiIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ExtScsiPassThru/BlackBoxTest/ExtScsiPassThruBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/iScsiInitiatorName/BlackBoxTest/iScsiInitiatorNameBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SerialIo/BlackBoxTest/SerialIoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimpleNetwork/BlackBoxTest/SimpleNetworkBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimpleFileSystem/BlackBoxTest/SimpleFileSystemBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimplePointer/BlackBoxTest/SimplePointerBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimpleTextIn/BlackBoxTest/SimpleTextInBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimpleTextOut/BlackBoxTest/SimpleTextOutBBTest_uefi.inf
SctPkg/TestCase/UEFI/EFI/Protocol/UnicodeCollation2/BlackBoxTest/UnicodeCollation2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/RegularExpression/BlackBoxTest/RegularExpressionBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Usb2Hc/BlackBoxTest/Usb2HcTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/UsbIo/BlackBoxTest/UsbIoTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Authentication/BlackBoxTest/AuthenticationBBTest.inf
#SctPkg/TestCase/UEFI/EFI/Protocol/Hash/BlackBoxTest/HashBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Tape/BlackBoxTest/TapeBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/DriverDiagnostics2/BlackBoxTest/DriverDiagnostics2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ACPITable/BlackBoxTest/AcpiTableProtocolBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SimpleTextInputEx/BlackBoxTest/SimpleTextInputExBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ComponentName2/BlackBoxTest/ComponentName2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIDatabase/BlackBoxTest/HIIDatabaseBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIString/BlackBoxTest/HIIStringBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIImage/BlackBoxTest/HIIImageBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIImageEx/BlackBoxTest/HIIImageExBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIFont/BlackBoxTest/HIIFontBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIFontEx/BlackBoxTest/HIIFontExBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIConfigAccess/BlackBoxTest/HIIConfigAccessBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/HIIConfigRouting/BlackBoxTest/HIIConfigRoutingBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/VlanConfig/BlackBoxTest/VlanConfigBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/IPsecConfig/BlackBoxTest/IPsecConfigBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/IPsec2/BlackBoxTest/IPsec2BBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/AbsolutePointer/BlackBoxTest/AbsolutePointerBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PlatformToDriverConfiguration/BlackBoxTest/PlatformToDriverConfigurationBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/FirmwareManagement/BlackBoxTest/FirmwareManagementBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/AtaPassThru/BlackBoxTest/AtaPassThruBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/StorageSecurityCommand/BlackBoxTest/StorageSecurityCommandBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/AdapterInfo/BlackBoxTest/AdapterInfoProtocolBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/TimeStamp/BlackBoxTest/TimeStampProtocolBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/RandomNumber/BlackBoxTest/RandomNumberBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/TCG2/BlackBoxTest/TCG2ProtocolBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/Hash2/BlackBoxTest/Hash2BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PKCS7Verify/BlackBoxTest/Pkcs7BBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ConfigKeywordHandler/BlackBoxTest/ConfigKeywordHandlerBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/RamDisk/BlackBoxTest/RamDiskProtocolBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/NVMEPassThru/BlackBoxTest/NVMEPassThruBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/EraseBlock/BlackBoxTest/EraseBlockBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/SDMMCPassThru/BlackBoxTest/SDMMCPassThruBBTest.inf

SctPkg/TestCase/UEFI/EFI/Protocol/PartitionInfo/BlackBoxTest/PartitionInfoBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/UFSDeviceConfig/BlackBoxTest/UFSDeviceConfigBBTest.inf
SctPkg/TestCase/UEFI/EFI/Protocol/ResetNotification/BlackBoxTest/ResetNotificationBBTest.inf
#
# Dependency files for UEFI/EFI Compliant Test
#

SctPkg/TestCase/UEFI/EFI/Generic/EfiCompliant/BlackBoxTest/Dependency/Config/Config.inf

#
# Dependency files for Image Services Test
#

SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/LoadFile/LoadFile.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/Application1/Application1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/Application2/Application2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/Application3/Application3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/Application4/Application4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver1/BootServicesDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver2/BootServicesDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver3/BootServicesDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver4/BootServicesDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver5/BootServicesDriver5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/BootServicesDriver6/BootServicesDriver6.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver1/RuntimeServicesDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver2/RuntimeServicesDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver3/RuntimeServicesDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver4/RuntimeServicesDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver5/RuntimeServicesDriver5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/RuntimeServicesDriver6/RuntimeServicesDriver6.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage1/CombinationImage1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage2/CombinationImage2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage3/CombinationImage3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage4/CombinationImage4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage5/CombinationImage5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage6/CombinationImage6.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage7/CombinationImage7.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage8/CombinationImage8.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage9/CombinationImage9.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/CombinationImage10/CombinationImage10.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage1/InvalidImage1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage2/InvalidImage2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage3/InvalidImage3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage4/InvalidImage4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage5/InvalidImage5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage6/InvalidImage6.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/InvalidImage7/InvalidImage7.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/ValidHiiImage1/ValidHiiImage1.inf
#SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/VeryLargeImage1/VeryLargeImage1.inf


#
# Dependency files for Protocol Handler Services Test
#

SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/BusDriver1/BusDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/BusDriver2/BusDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/BusDriver3/BusDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/BusDriver4/BusDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DBindingDriver1/DBindingDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DBindingDriver2/DBindingDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DBindingDriver3/DBindingDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DBindingDriver4/DBindingDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DBindingDriver5/DBindingDriver5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver1/DeviceDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver2/DeviceDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver3/DeviceDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver4/DeviceDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver5/DeviceDriver5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver6/DeviceDriver6.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver7/DeviceDriver7.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver11/DeviceDriver11.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver12/DeviceDriver12.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver13/DeviceDriver13.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver14/DeviceDriver14.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver15/DeviceDriver15.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver18/DeviceDriver18.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver19/DeviceDriver19.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver110/DeviceDriver110.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/DeviceDriver111/DeviceDriver111.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/TestDriver1/TestDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/TestDriver2/TestDriver2.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/TestDriver3/TestDriver3.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/TestDriver4/TestDriver4.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/TestDriver5/TestDriver5.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/PlatformOverrideDriver1/PlatformOverrideDriver1.inf
SctPkg/TestCase/UEFI/EFI/BootServices/ProtocolHandlerServices/BlackBoxTest/Dependency/BusOverrideDriver1/BusOverrideDriver1.inf

#
# Dependency files for Decompress Protocol Test
#

SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/Config/Config.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/CompressedFile1/CompressedFile1.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/CompressedFile2/CompressedFile2.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/UncompressedFile1/UncompressedFile1.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/UncompressedFile2/UncompressedFile2.inf
SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/InvalidCompressedFile1/InvalidCompressedFile1.inf

#
# Dependency files for EBC Protocol Test
#
SctPkg/TestCase/UEFI/EFI/Protocol/Ebc/BlackBoxTest/Dependency/EbcDriverBin/EbcDriverBin.inf

#
# Dependency files for Loaded Image Protocol Test
#

SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/Application1/Application1.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/Application2/Application2.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/BootServicesDriver1/BootServicesDriver1.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/BootServicesDriver2/BootServicesDriver2.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/RuntimeServicesDriver1/RuntimeServicesDriver1.inf
SctPkg/TestCase/UEFI/EFI/Protocol/LoadedImage/BlackBoxTest/Dependency/RuntimeServicesDriver2/RuntimeServicesDriver2.inf

#
# Dependency files for PCI IO Protocol Test
#

SctPkg/TestCase/UEFI/EFI/Protocol/PciIo/BlackBoxTest/Dependency/Config/Config.inf
SctPkg/TestCase/UEFI/EFI/Protocol/PciIo/BlackBoxTest/Dependency/MakeConfigWritable/MakeConfigWritable.inf

#
# Dependency files for PCI Root Bridge IO Protocol Test
#

SctPkg/TestCase/UEFI/EFI/Protocol/PciRootBridgeIo/BlackBoxTest/Dependency/Config/Config.inf

#
# Dependency files for PXE Base Code Protocol Test
#
SctPkg/TestCase/UEFI/EFI/Protocol/PxeBaseCode/BlackBoxTest/Dependency/Config/Config.inf

#
# Dependency files for Config Keyword Handler Protocol Test
#
SctPkg/TestCase/UEFI/EFI/Protocol/ConfigKeywordHandler/BlackBoxTest/Dependency/SampleDriver/DriverSampleDxe.inf

#
# Support Files
#
SctPkg/TestInfrastructure/SCT/Framework/ENTS/Eftp/Eftp.inf
SctPkg/TestInfrastructure/SCT/Framework/ENTS/MonitorServices/SerialMonitor/SerialMonitor.inf
SctPkg/TestInfrastructure/SCT/Framework/ENTS/MonitorServices/ManagedNetworkMonitor/ManagedNetworkMonitor.inf
SctPkg/TestInfrastructure/SCT/Framework/ENTS/MonitorServices/IP4NetworkMonitor/IP4NetworkMonitor.inf


#
# Test Cases for RIVL (Only for UEFI SCT)
#

SctPkg/TestCase/RIVL/BootService/BootServiceENTSTest.inf
SctPkg/TestCase/RIVL/RuntimeService/RuntimeServiceENTSTest.inf
SctPkg/TestCase/RIVL/GenericService/GenericServiceENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/SimpleNetwork/SimpleNetworkENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/PXEBaseCode/PXEBaseCodeENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/AddressResolutionProtocol/Arp/ArpENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/AddressResolutionProtocol/ArpServiceBinding/ArpServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/InternetProtocol4/Ip4/Ip4ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/InternetProtocol4/Ip4Config/Ip4ConfigENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/InternetProtocol4/Ip4Config2/Ip4Config2ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/InternetProtocol4/Ip4ServiceBinding/Ip4ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/InternetProtocol6/Ip6/Ip6ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/InternetProtocol6/Ip6Config/Ip6ConfigENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/InternetProtocol6/Ip6ServiceBinding/Ip6ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/ManagedNetwork/MNP/MnpENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/ManagedNetwork/MNPSB/MnpSBENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Dhcp4/Dhcp4/Dhcp4ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Dhcp4/Dhcp4SB/Dhcp4SBENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Dhcp6/Dhcp6/Dhcp6ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Dhcp6/Dhcp6SB/Dhcp6SBENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Udp4/Udp4/Udp4ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Udp4/Udp4ServiceBinding/Udp4ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Udp6/Udp6/Udp6ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Udp6/Udp6ServiceBinding/Udp6ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Mtftp4/Mtftp4/Mtftp4ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Mtftp4/Mtftp4ServiceBinding/Mtftp4ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Mtftp6/Mtftp6/Mtftp6ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Mtftp6/Mtftp6ServiceBinding/Mtftp6ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Tcp4/Tcp4/Tcp4ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Tcp4/Tcp4ServiceBinding/Tcp4ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Tcp6/Tcp6/Tcp6ENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Tcp6/Tcp6ServiceBinding/Tcp6ServiceBindingENTSTest.inf

SctPkg/TestCase/RIVL/Protocol/Http/Http/HttpENTSTest.inf
SctPkg/TestCase/RIVL/Protocol/Http/HttpServiceBinding/HttpServiceBindingENTSTest.inf

[Components.IA32, Components.X64]
SctPkg/TestCase/UEFI/EFI/Generic/ExeMode/BlackBoxTest/ExeModeBBTest.inf

[Components.RISCV64]
SctPkg/TestCase/UEFI/EFI/Protocol/RiscV/BlackBoxTest/RiscVBootProtocolBBTest.inf
