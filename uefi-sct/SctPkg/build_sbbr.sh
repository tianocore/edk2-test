#!/bin/bash
# The material contained herein is not a license, either
# expressly or impliedly, to any intellectual property owned
# or controlled by any of the authors or developers of this
# material or to any contribution thereto. The material
# contained herein is provided on an "AS IS" basis and, to the
# maximum extent permitted by applicable law, this information
# is provided AS IS AND WITH ALL FAULTS, and the authors and
# developers of this material hereby disclaim all other
# warranties and conditions, either express, implied or
# statutory, including, but not limited to, any (if any)
# implied warranties, duties or conditions of merchantability,
# of fitness for a particular purpose, of accuracy or
# completeness of responses, of results, of workmanlike
# effort, of lack of viruses and of lack of negligence, all
# with regard to this material and any contribution thereto.
# Designers must not rely on the absence or characteristics of
# any features or instructions marked "reserved" or
# "undefined." The Unified EFI Forum, Inc. reserves any
# features or instructions so marked for future definition and
# shall have no responsibility whatsoever for conflicts or
# incompatibilities arising from future changes to them. ALSO,
# THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
# QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR
# NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY
# CONTRIBUTION THERETO.
#
# IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
# ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR
# THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST
# PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,
# CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER
# UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
# WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS
# DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF
# THE POSSIBILITY OF SUCH DAMAGES.
#
# Copyright 2006 - 2015 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all
# matters included within this Test Suite, to which United
# EFI, Inc. makes no claim of right.
#
# Copyright (c) 2011, 2015 ARM Ltd. All rights reserved.<BR>
#

SctpackageDependencyList=(EdkCompatibilityPkg SctPkg BaseTools)

function get_build_arch
{
	case `uname -m` in
	    aarch64*)
	        BUILD_ARCH=AARCH64;;
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
	elif [ "$SCT_TARGET_ARCH" == "AARCH64" ]; then
	    if [ X"$CROSS_COMPILE_64" != X"" ]; then
	        TEMP_CROSS_COMPILE="$CROSS_COMPILE_64"
	    else
	        TEMP_CROSS_COMPILE=aarch64-linux-gnu-
	    fi
	else
	    echo "Unsupported target architecture '$SCT_TARGET_ARCH'!" >&2
	fi
}

function get_gcc_version
{
	gcc_version=$($1 -dumpversion)
	case $gcc_version in
		4.6*|4.7*|4.8*|4.9*)
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
	echo "    $0 <architecture (ARM, AARCH64, X64, etc)> \
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
export EDK_SOURCE=`pwd`/EdkCompatibilityPkg

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

		GCC | gcc)
            set_cross_compile
	        CROSS_COMPILE="$TEMP_CROSS_COMPILE"
            export TARGET_TOOLS=`get_gcc_version "$CROSS_COMPILE"gcc`

		;;

		*)
			echo "Couldn't build SBBR SCT:"
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
			echo "Couldn't build SBBR SCT:"
			PrintUsage
			exit -1
		;;
	esac
   ;;
   *)
     echo "Couldn't build SBBR SCT:"
     echo "Unknown OS, Use this script either in Unix or Cygwin environment".
     PrintUsage
     exit -1
   ;;
esac

echo "TOOLCHAIN is ${TARGET_TOOLS}"
export ${TARGET_TOOLS}_${SCT_TARGET_ARCH}_PREFIX=$CROSS_COMPILE
echo "Toolchain prefix: ${TARGET_TOOLS}_${SCT_TARGET_ARCH}_PREFIX=$CROSS_COMPILE"

SCT_BUILD=DEBUG
if [ "$3" = "RELEASE" -o "$3" = "DEBUG" ]; then
  SCT_BUILD=$3
  shift
fi

#
# Setup workspace if it is not set
#
if [ -z "${WORKSPACE:-}" ]; then
	echo Initializing workspace
	# Uses an external BaseTools project
	# Uses the BaseTools in edk2
	export EDK_TOOLS_PATH=`pwd`/BaseTools
	# We do not pass BuildArmSct.sh arguments to edksetup.sh
	while (( "$#" )); do
		shift
	done
	source ./edksetup.sh
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

# Copy GenBin file to Base tools directory
DEST_DIR=`GetEdkToolsPathBinDirectory`
# Ensure the directory exist
mkdir -p $DEST_DIR
case `uname -m` in
	x86_64)
		cp SctPkg/Tools/Bin/GenBin_lin_64 $DEST_DIR/GenBin
		;;
	x86_32)
		cp SctPkg/Tools/Bin/GenBin_lin_32 $DEST_DIR/GenBin
		;;
	*)
		cp SctPkg/Tools/Bin/GenBin_lin_32 $DEST_DIR/GenBin
		;;
esac

#
# Build the SCT package
#
build -p SctPkg/UEFI/SBBR_SCT.dsc -a $SCT_TARGET_ARCH -t $TARGET_TOOLS -b $SCT_BUILD $3 $4 $5 $6 $7 $8 $9

# Check if there is any error
status=$?
if test $status -ne 0
then
echo Could not build the SBBR SCT package
        exit -1
fi

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
cd Build/SbbrSct/${SCT_BUILD}_${TARGET_TOOLS}
pwd

#
# Run a script to generate Sct binary for the target architecture
#
../../../SctPkg/CommonGenFramework.sh sbbr_sct $SCT_TARGET_ARCH Install$SCT_TARGET_ARCH.efi

status=$?
if test $status -ne 0
then
echo Could not generate SBBR SCT binary
     exit -1
else
echo The SBBR SCT binary "SctPackage${SCT_TARGET_ARCH}" is located at "$EFI_SOURCE/Build/SbbrSct/${SCT_BUILD}_${TARGET_TOOLS}"
fi
