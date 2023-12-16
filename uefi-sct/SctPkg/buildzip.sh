#!/bin/bash
#
#  EDK2 SCT build script for SCT+Shell in a zip file
#
#  Copyright (c) 2021, ARM Ltd. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

set -e

TARGET_ARCH=$1

if [ X"${TARGET_ARCH}" == X"" ]
then
	echo  "Usage: $0 <ARM|AARCH64>"
	exit
fi

case $TARGET_ARCH in
	AARCH64)
		BOOT_IMAGE_NAME=BOOTAA64.efi;;
	*)
		BOOT_IMAGE_NAME=BOOT${TARGET_ARCH}.efi;;
esac

# clear all positional parameters
set --

NUM_CPUS=$((`getconf _NPROCESSORS_ONLN` + 2))

make -j"$NUM_CPUS" -C edk2/BaseTools/

# Build the SCT, CapsuleApp.efi, and the shell
DSC_EXTRA="ShellPkg/ShellPkg.dsc MdeModulePkg/MdeModulePkg.dsc" ./SctPkg/build.sh ${TARGET_ARCH} GCC RELEASE -j"$NUM_CPUS"

# Assemble all the files that need to be in the zip file
mkdir -p ${TARGET_ARCH}_SCT/EFI/BOOT
cp Build/Shell/RELEASE_GCC5/${TARGET_ARCH}/Shell_EA4BB293-2D7F-4456-A681-1F22F42CD0BC.efi ${TARGET_ARCH}_SCT/EFI/BOOT/${BOOT_IMAGE_NAME}

mkdir -p ${TARGET_ARCH}_SCT/SCT
cp -r Build/UefiSct/RELEASE_GCC5/SctPackage${TARGET_ARCH}/${TARGET_ARCH}/* ${TARGET_ARCH}_SCT/SCT/
cp Build/UefiSct/RELEASE_GCC5/SctPackage${TARGET_ARCH}/SctStartup.nsh ${TARGET_ARCH}_SCT/Startup.nsh

mkdir -p ${TARGET_ARCH}_SCT/Mde
cp Build/MdeModule/RELEASE_GCC5/${TARGET_ARCH}/CapsuleApp.efi ${TARGET_ARCH}_SCT/Mde

# Check if user has cloned edk-test-parser and buildzip.sh can access
if [ ! -d "${pwd}edk2-test-parser" ]
then
        echo "edk2-test-parser repo is missing from current directory, please clone and try again"
        exit
fi

# Copy edk2-test-parser tool into the repo
cp -r edk2-test-parser/* ${TARGET_ARCH}_SCT/SCT/Sequence/

# Put some version information into the ESP directory
cat > ./${TARGET_ARCH}_SCT/versions.txt << EOF
EDK2_VER=`git -C ./edk2 describe`
EDK2_TEST_VER=`git -C ./edk2-test describe`
BUILD_DATE="`date`"
EOF

# Zip up the test folder
cd ${TARGET_ARCH}_SCT
zip -r ../edk2-test-${TARGET_ARCH,,}.zip *
cd ..

