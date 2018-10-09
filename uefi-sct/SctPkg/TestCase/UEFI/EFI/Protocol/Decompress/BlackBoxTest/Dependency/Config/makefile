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
#   This is the makefile for creating an INI file.
#
#--*/

BASE_NAME=Decompress_DecompressBbTest
SOURCE_DIR=$(WORKSPACE)\SctPkg\TestCase\UEFI\EFI\Protocol\Decompress\BlackBoxTest\Dependency\Config

#
# Define some useful macros, then include the master Efi toolchain setup
# file.
#
#BIN_DIR     = $(BUILD_DIR)\$(PROCESSOR)
#TOOLCHAIN   = TOOLCHAIN_$(PROCESSOR)

#!INCLUDE $(BUILD_DIR)\PlatformTools.env

#
# We simply copy the INI file from the source directory to the build directory
#
$(BIN_DIR)\$(BASE_NAME).ini : $(SOURCE_DIR)\DecompressBbTest.ini
  copy $(SOURCE_DIR)\DecompressBbTest.ini $(BIN_DIR)\$(BASE_NAME).ini /y
!MESSAGE BIN_DIR:$(BIN_DIR)
!MESSAGE BUILD_DIR:$(BUILD_DIR)
!MESSAGE PROCESSOR:$(PROCESSOR)
!MESSAGE TOOLCHAIN:$(TOOLCHAIN)
all : $(BIN_DIR)\$(BASE_NAME).ini

clean:
	$(BIN_DIR)\$(BASE_NAME).ini
