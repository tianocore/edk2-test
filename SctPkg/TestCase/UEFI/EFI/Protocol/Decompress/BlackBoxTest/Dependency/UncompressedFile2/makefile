## @file
#
#  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>
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
#   makefile
#
# Abstract:
#
#   This is the makefile for creating an empty uncompressed file for testing.
#
#--*/

BASE_NAME=Decompress_UncompressedFile2
SOURCE_DIR=$(WORKSPACE)\SctPkg\TestCase\UEFI\EFI\Protocol\Decompress\BlackBoxTest\Dependency\UncompressedFile2
GENBIN=$(EDK_TOOLS_PATH)\Bin\Win32\GenBin.exe
#
# Define some useful macros, then include the master Efi toolchain setup
# file.
#
#BIN_DIR     = $(BUILD_DIR)\$(PROCESSOR)
#TOOLCHAIN   = TOOLCHAIN_$(PROCESSOR)

#!INCLUDE $(BUILD_DIR)\PlatformTools.env

#
# We generate the uncompressed file from a profile
#
$(BIN_DIR)\$(BASE_NAME).ucmp : $(SOURCE_DIR)\UncompressedFile2.ini
	$(GENBIN) $(SOURCE_DIR)\UncompressedFile2.ini $(BIN_DIR)\$(BASE_NAME).ucmp

all : $(BIN_DIR)\$(BASE_NAME).ucmp

clean:
	$(BIN_DIR)\$(BASE_NAME).ucmp
