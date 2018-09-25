## @file
#
#  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2010 - 2012, Byosoft Corporation. All rights reserved.<BR>
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
#   This is the makefile for creating an valid Hii image file for testing.
#
#--*/


BASE_NAME=ImageServices_ValidHiiImage1
SOURCE_DIR=$(WORKSPACE)\SctPkg\TestCase\UEFI\EFI\BootServices\ImageServices\BlackBoxTest\Dependency\ValidHiiImage1
TARGET_EFI=$(SOURCE_DIR)\$(ARCH)\$(BASE_NAME).efi

#
# Define some useful macros, then include the master Efi toolchain setup
# file.
#
#BIN_DIR     = $(BUILD_DIR)\$(PROCESSOR)
#TOOLCHAIN   = TOOLCHAIN_$(PROCESSOR)

#!INCLUDE $(BUILD_DIR)\PlatformTools.env

#
# We generate the invalid image file from a profile
#



all : 
    $(CP) $(TARGET_EFI) $(DEBUG_DIR)
    $(CP) $(TARGET_EFI) $(BIN_DIR)
    -(CP) $(DEBUG_DIR)\*.map $(OUTPUT_DIR)
  