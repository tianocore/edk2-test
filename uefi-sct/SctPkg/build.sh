#!/bin/bash
#
#  Copyright 2006 - 2015 Unified EFI, Inc.<BR>
#  Copyright (c) 2011 - 2020, ARM Ltd. All rights reserved.<BR>
#  (C) Copyright 2021 Hewlett Packard Enterprise Development LP<BR>
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

SctpackageDependencyList=(SctPkg BaseTools)

function get_build_arch
{
	case `uname -m` in
	    arm*)
	        BUILD_ARCH=ARM;;
	    aarch64*)
	        BUILD_ARCH=AARCH64;;
	    riscv64*)
	        BUILD_ARCH=RISCV64;;
	    loongarch64*)
	        BUILD_ARCH=LOONGARCH64;;
	    x86_64*)
	        BUILD_ARCH=X64;;
	    *)
	        BUILD_ARCH=other;;
	esac
}

function set_cross_compile
{
	get_build_arch

	echo "Target: $SCT_TARGET_ARCH"
	echo "Build: $BUILD_ARCH"
	if [ "$SCT_TARGET_ARCH" = "$BUILD_ARCH" ]; then
	    TEMP_CROSS_COMPILE=
	elif [ "$SCT_TARGET_ARCH" == "X64" ]; then
	    if [ X"$CROSS_COMPILE_64" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_64"
	    else
	        TEMP_CROSS_COMPILE=x86_64-linux-gnu-
	    fi
	elif [ "$SCT_TARGET_ARCH" == "AARCH64" ]; then
	    if [ X"$CROSS_COMPILE_64" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_64"
	    else
	        TEMP_CROSS_COMPILE=aarch64-linux-gnu-
	    fi
	elif [ "$SCT_TARGET_ARCH" == "ARM" ]; then
	    if [ X"$CROSS_COMPILE_32" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_32"
	    else
	        TEMP_CROSS_COMPILE=arm-linux-gnueabihf-
	    fi
	elif [ "$SCT_TARGET_ARCH" == "RISCV64" ]; then
	    if [ X"$CROSS_COMPILE_64" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_64"
	    else
	        TEMP_CROSS_COMPILE=riscv64-unknown-elf-
	    fi
	elif [ "$SCT_TARGET_ARCH" == "LOONGARCH64" ]; then
	    if [ X"$CROSS_COMPILE_64" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_64"
	    else
	        TEMP_CROSS_COMPILE=loongarch64-unknown-linux-gnu-
	    fi
	else
	    echo "Unsupported target architecture '$SCT_TARGET_ARCH'!" >&2
	fi
}

function get_gcc_version
{
	gcc_version=$($1 -dumpversion)

	if [ ${gcc_version%%.*} -ge 5 ]; then
		gcc_version=5
	fi

	case $gcc_version in
		4.6*|4.7*|4.8*|4.9*|5*)
			echo GCC$(echo ${gcc_version} | awk -F. '{print $1$2}')
			;;
		*)
			echo "Unknown toolchain version '$gcc_version'" >&2
			echo "Attempting to build using GCC49 profile." >&2
			echo GCC49
			;;
	esac
}

function get_clang_version
{
	clang_version=`$1 --version | head -1 | sed 's/^.*version\s*\([0-9]*\).\([0-9]*\).*/\1\2/g'`
	echo "CLANG$clang_version"
}


GetBaseToolsBinSubDir() {
	#
	# Figure out a uniq directory name from the uname command
	#
	UNAME_DIRNAME=`uname -sm`
	UNAME_DIRNAME=${UNAME_DIRNAME// /-}
	UNAME_DIRNAME=${UNAME_DIRNAME//\//-}
	echo $UNAME_DIRNAME
}

GetEdkToolsPathBinDirectory() {
	#
	# Figure out a uniq directory name from the uname
	# command
	#
	BIN_SUB_DIR=`GetBaseToolsBinSubDir`

	if [ -e	$EDK_TOOLS_PATH/BinWrappers/$BIN_SUB_DIR ]
	then
		EDK_TOOLS_PATH_BIN=$EDK_TOOLS_PATH/BinWrappers/$BIN_SUB_DIR
	else
		EDK_TOOLS_PATH_BIN=$EDK_TOOLS_PATH/BinWrappers/PosixLike
	fi
        echo $EDK_TOOLS_PATH_BIN
}

PrintUsage() {
	#
	#Print Help
	#
	echo "Usage:"
	echo "    $0 <architecture (ARM, AARCH64, X64, RISCV64, LOONGARCH64, etc)> \
<toolchain name (RVCT or ARMGCC or GCC*)> \
[build type (RELEASE OR DEBUG, DEFAULT: DEBUG)]"
}

#Iterate through the SCT package dependency list and check if they exist in the current directory
for pkg in ${names[@]}
do
    if [ ! -d `pwd`/$name]
    then
    echo "Couldn't build SCT:"
    echo The directory `pwd`/$name does not exist.
    exit -1
    fi
done

export EFI_SOURCE=`pwd`

# check if the last command was successful
status=$?
if test $status -ne 0; then
	echo Could not Run the edksetup.sh script
	exit -1
fi

SCT_TARGET_ARCH=${1}

#
# Pick a default tool type for a given OS
#
case `uname` in
   Linux*)
	case ${2} in
		RVCT | rvct)
			TARGET_TOOLS=RVCTLINUX
		;;

		ARMGCC | armgcc)
			TARGET_TOOLS=ARMGCC
		;;
		
		GCC* | gcc*)
			set_cross_compile
			CROSS_COMPILE="$TEMP_CROSS_COMPILE"
			export TARGET_TOOLS=`get_gcc_version "$CROSS_COMPILE"gcc`
		;;

		*)
			echo "Couldn't build SCT:"
			PrintUsage
			exit -1
		;;
	esac
   ;;
   CYGWIN*)
	case ${2} in
		RVCT | rvct)
			TARGET_TOOLS=RVCT31CYGWIN
		;;

		ARMGCC | armgcc)
			TARGET_TOOLS=ARMGCCCYGWIN
		;;

		*)
			echo "Couldn't build SCT:"
			PrintUsage
			exit -1
		;;
	esac
   ;;
   *)
     echo "Couldn't build SCT:"
     echo "Unknown OS, Use this script either in Unix or Cygwin environment".
     PrintUsage
     exit -1
   ;;
esac

# Drop parsed command line arguments
shift 2

echo "TOOLCHAIN is ${TARGET_TOOLS}"
export ${TARGET_TOOLS}_${SCT_TARGET_ARCH}_PREFIX=$CROSS_COMPILE
echo "Toolchain prefix: ${TARGET_TOOLS}_${SCT_TARGET_ARCH}_PREFIX=$CROSS_COMPILE"

SCT_BUILD=DEBUG
if [ "$1" = "RELEASE" -o "$1" = "DEBUG" ]; then
  SCT_BUILD=$1
  shift
fi

#
# Setup workspace if it is not set
#
if [ -z "${WORKSPACE:-}" ]; then
	echo Initializing workspace
	export WORKSPACE=$PWD
	export PACKAGES_PATH=$WORKSPACE/edk2:$WORKSPACE/SctPkg
	# We do not pass BuildArmSct.sh arguments to edksetup.sh
	while (( "$#" )); do
		shift
	done
	. edk2/edksetup.sh
else
	echo Building from: $WORKSPACE
fi

if  [[ ! -e $EDK_TOOLS_PATH/Source/C/bin ]]
then
  # build the tools if they don't yet exist
  echo Building tools: $EDK_TOOLS_PATH
  make -C $EDK_TOOLS_PATH
  status=$?
  if test $status -ne 0
  then
    echo Error while building EDK tools
    exit -1
  fi
else
  echo using prebuilt tools
fi

rm -f $EDK_TOOLS_PATH/Source/C/bin/GenBin

# build the GenBin if it doesn't yet exist
echo Building GenBin
make -C SctPkg/Tools/Source/GenBin
status=$?
if test $status -ne 0
then
  echo Error while building GenBin
  exit -1
fi

# Copy GenBin file to Base tools bin directory
DEST_DIR=`GetEdkToolsPathBinDirectory`
# Ensure the directory exist
mkdir -p $DEST_DIR
cp $EDK_TOOLS_PATH/Source/C/bin/GenBin $DEST_DIR/GenBin

#
# Build the packages needed for the SCT
# Set $DSC_EXTRA to any extra packages needed for the build
#
#for DSC in SctPkg/UEFI/UEFI_SCT.dsc SctPkg/UEFI/IHV_SCT.dsc $DSC_EXTRA
for DSC in SctPkg/UEFI/UEFI_SCT.dsc $DSC_EXTRA
do
	build -p $DSC -a $SCT_TARGET_ARCH -t $TARGET_TOOLS -b $SCT_BUILD $@
	# Check if there is any error
	status=$?
	if test $status -ne 0
	then
		echo Could not build package $DSC
		exit -1
	fi
done

#
# If the argument is clean, then don't have to generate Sct binary.
#
for arg in "$@"
do
  if [ $arg == clean ] || [ $arg == cleanall ]
  then
      # no need to post process if we are doing a clean
      exit 1
  fi
done

#
# Change directory to Build directory
#
cd Build/UefiSct/${SCT_BUILD}_${TARGET_TOOLS}
pwd

#
# Run a script to generate Sct binary for the target architecture
#
../../../SctPkg/CommonGenFramework.sh uefi_sct $SCT_TARGET_ARCH Install$SCT_TARGET_ARCH.efi

status=$?
if test $status -ne 0
then
  echo Could not generate UEFI SCT binary
  exit -1
else
echo The SCT binary "SctPackage${SCT_TARGET_ARCH}" is located at "$EFI_SOURCE/Build/UefiSct/${SCT_BUILD}_${TARGET_TOOLS}"
fi

cd ../../../
pwd

#cd Build/IhvSct/${SCT_BUILD}_${TARGET_TOOLS}
#pwd
#../../../SctPkg/CommonGenFramework.sh ihv_sct $SCT_TARGET_ARCH Install$SCT_TARGET_ARCH.efi

#status=$?
#if test $status -ne 0
#then
#  echo Could not generate IHV SCT binary
#  exit -1
#else
#echo The IHV binary "SctPackage${SCT_TARGET_ARCH}" is located at "$EFI_SOURCE/Build/IhvSct/${SCT_BUILD}_${TARGET_TOOLS}"
#fi
