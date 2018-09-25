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
#   This is the makefile for creating an invalid compressed file for testing.
#
#--*/
BASE_NAME=Decompress_InvalidCompressedFile1
SOURCE_DIR=$(WORKSPACE)/SctPkg/TestCase/UEFI/EFI/Protocol/Decompress/BlackBoxTest/Dependency/InvalidCompressedFile1
GENBIN=GenBin
DEPENDECY=$(SOURCE_DIR)/InvalidCompressedFile1.ini
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
# We generate the compressed file from a profile
#
$(BIN_DIR)/$(BASE_NAME).cmp : $(DEPENDECY)
	$(GENBIN)  $(GEN_BIN_PROFILE) $(TARGET).cmp

all : $(BIN_DIR)/$(BASE_NAME).cmp

clean:
	$(RM) $(BIN_DIR)/$(BASE_NAME).cmp