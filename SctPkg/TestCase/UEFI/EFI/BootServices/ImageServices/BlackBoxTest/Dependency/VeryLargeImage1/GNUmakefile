## @file
#
#  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2011 - 2012, ARM Ltd. All rights reserved.<BR>
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
#   This is the makefile for creating a very large image for testing. This image
#   cannot be used to verify on IPF or x64 platforms.
#
#--*/

BASE_NAME=ImageServices_VeryLargeImage1
SOURCE_DIR=$(WORKSPACE)/SctPkg/TestCase/UEFI/EFI/BootServices/ImageServices/BlackBoxTest/Dependency/VeryLargeImage1
GENBIN=GenBin
DEPENDECY=$(SOURCE_DIR)/VeryLargeImage1.ini
UNAME = $(shell uname)

#Check if it is cygwin environment
ifeq ($(findstring CYGWIN,$(UNAME)),CYGWIN)
	GEN_BIN_PROFILE=`cygpath -m $(DEPENDECY)`
	TARGET=`cygpath -m $(BIN_DIR)/$(BASE_NAME)`
else
	GEN_BIN_PROFILE=$(DEPENDECY)
	TARGET=$(BIN_DIR)/$(BASE_NAME)
endif
#
# Define some useful macros, then include the master Efi toolchain setup
# file.
#
#BIN_DIR     = $(BUILD_DIR)/$(PROCESSOR)
#TOOLCHAIN   = TOOLCHAIN_$(PROCESSOR)

#!INCLUDE $(BUILD_DIR)/PlatformTools.env

#
# We generate the invalid image file from a profile
#
$(BIN_DIR)/$(BASE_NAME) : $(DEPENDECY)
	$(GENBIN)  $(GEN_BIN_PROFILE) $(TARGET)

all : $(BIN_DIR)/$(BASE_NAME)

clean:
	$(RM) $(BIN_DIR)/$(BASE_NAME)
