#!/bin/sh
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
# Copyright 2006 - 2012 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2011, 2012 ARM Ltd All rights reserved. 
#
#
#
# 
# Module Name
#
#   CommonGenFramework.bat
#
# Abstract
#
#   Common part for generating the test package
#
#
export ProcessorType=$2
export Installer=$3
export Framework=SctPackage$ProcessorType/$ProcessorType
# *********************************************
# Create target directory
# *********************************************
if [ -e $Framework ]
then
  rm -rf $Framework
fi

echo "Generating SCT binary"

mkdir -p $Framework
mkdir -p $Framework/Data
mkdir -p $Framework/Dependency
mkdir -p $Framework/Support
mkdir -p $Framework/Test
mkdir -p $Framework/Sequence
mkdir -p $Framework/Report
mkdir -p $Framework/Application
mkdir -p $Framework/Proxy
mkdir -p $Framework/Ents/Support
mkdir -p $Framework/Ents/Test


# *********************************************
# Copy the SCT framework and the related application
# *********************************************

cp $ProcessorType/SCT.efi              $Framework/            > NUL

cp $ProcessorType/StandardTest.efi     $Framework/Support/    > NUL
cp $ProcessorType/TestProfile.efi      $Framework/Support/    > NUL
cp $ProcessorType/TestRecovery.efi     $Framework/Support/    > NUL
cp $ProcessorType/TestLogging.efi      $Framework/Support/    > NUL

cp ../../../SctPkg/Config/Script/SctStartup.nsh   SctPackage$ProcessorType/             > NUL
cp $ProcessorType/InstallSct.efi       SctPackage$ProcessorType/$Installer  > NUL
cp $ProcessorType/StallForKey.efi      $Framework/            > NUL

# *********************************************
# Copy the SCT configuration data
# *********************************************

cp ../../../SctPkg/Config/Data/Category.ini       $Framework/Data/       > NUL
cp ../../../SctPkg/Config/Data/GuidFile.txt       $Framework/Data/       > NUL

# *********************************************
# Copy each test dependency file
# *********************************************

CopyDependencyFile()
{
	export Source=$2
	export Target=$(echo $2 | cut -d'/' -f2 | sed 's/\w*_//g')
	cp $Source     $Framework/Dependency/$1BbTest/$Target > NUL
}

# *********************************************
# Copy the test dependency files for each test
# *********************************************

CopyDependency()
{
	mkdir -p $Framework/Dependency/$1BbTest	
	ls -h $ProcessorType/$1_*.       > temp.txt 2>NUL
	ls -h $ProcessorType/$1_*.efi   >> temp.txt 2>NUL
	ls -h $ProcessorType/$1_*.ini   >> temp.txt 2>NUL
	ls -h $ProcessorType/$1_*.cmp   >> temp.txt 2>NUL
	ls -h $ProcessorType/$1_*.ucmp  >> temp.txt 2>NUL

	while read line 																																													 
	 do 
	  	CopyDependencyFile $1 $line
	 done < temp.txt
    rm -f temp.txt >NUL
}

# *********************************************
# For UEFI SCT
# *********************************************

if [ $1 = "uefi_sct" ] 
then 
	# *********************************************
	# Copy the UEFI 2.1 Test Cases
	# *********************************************
	
	mkdir -p $Framework/SCRT
	cp $ProcessorType/SCRTDRIVER.efi                           $Framework/SCRT  > NUL
	cp $ProcessorType/SCRTAPP.efi                              $Framework/SCRT  > NUL
	cp ../../../SctPkg/Config/Data/SCRT.conf                   $Framework/SCRT  > NUL
	
	cp $ProcessorType/EfiCompliantBbTest.efi                   $Framework/Test/ > NUL

  # Only include ExeModeBBTest.efi if the file exists
  if [ -e $ProcessorType/ExeModeBBTest.efi ]; then
	  cp $ProcessorType/ExeModeBBTest.efi                      $Framework/Test/ > NUL
  fi
	
	cp $ProcessorType/EventTimerTaskPriorityServicesBBTest.efi $Framework/Test/ > NUL
	cp $ProcessorType/MemoryAllocationServicesBBTest.efi       $Framework/Test/ > NUL
	cp $ProcessorType/ProtocolHandlerServicesBBTest.efi        $Framework/Test/ > NUL
	cp $ProcessorType/ImageServicesBBTest.efi                  $Framework/Test/ > NUL
	cp $ProcessorType/MiscBootServicesBBTest.efi               $Framework/Test/ > NUL
	
	cp $ProcessorType/VariableServicesBBTest.efi               $Framework/Test/ > NUL
	cp $ProcessorType/TimeServicesBBTest.efi                   $Framework/Test/ > NUL
	cp $ProcessorType/MiscRuntimeServicesBBTest.efi            $Framework/Test/ > NUL
	
	cp $ProcessorType/BisBBTest.efi                            $Framework/Test/ > NUL
	cp $ProcessorType/BlockIoBBTest.efi                        $Framework/Test/ > NUL
	cp $ProcessorType/BusSpecificDriverOverrideBBTest.efi      $Framework/Test/ > NUL
#   cp $ProcessorType/ComponentNameBbTest.efi                  $Framework/Test/ > NUL
	cp $ProcessorType/DebugPortBBTest.efi                      $Framework/Test/ > NUL
	cp $ProcessorType/DebugSupportBBTest.efi                   $Framework/Test/ > NUL
	cp $ProcessorType/DecompressBBTest.efi                     $Framework/Test/ > NUL
#Note: Device IO BB is deprecated in SCT 2.3
#	cp $ProcessorType/DeviceIoBbTest.efi                       $Framework/Test/ > NUL
	cp $ProcessorType/DevicePathBBTest.efi                     $Framework/Test/ > NUL
	cp $ProcessorType/DevicePathUtilitiesBBTest.efi            $Framework/Test/ > NUL
	cp $ProcessorType/DevicePathToTextBBTest.efi               $Framework/Test/ > NUL
	cp $ProcessorType/DevicePathFromTextBBTest.efi             $Framework/Test/ > NUL
	cp $ProcessorType/DiskIoBBTest.efi                         $Framework/Test/ > NUL
#   cp $ProcessorType/DriverDiagnosticsBBTest.efi              $Framework/Test/ > NUL
#   cp $ProcessorType/DriverConfigurationBBTest.efi            $Framework/Test/ > NUL
	cp $ProcessorType/EbcBBTest.efi                            $Framework/Test/ > NUL
	cp $ProcessorType/LoadedImageBBTest.efi                    $Framework/Test/ > NUL
	cp $ProcessorType/LoadFileBBTest.efi                       $Framework/Test/ > NUL
	cp $ProcessorType/PciIoBBTest.efi                          $Framework/Test/ > NUL
	cp $ProcessorType/PciRootBridgeIoBBTest.efi                $Framework/Test/ > NUL
	cp $ProcessorType/PlatformDriverOverrideBBTest.efi         $Framework/Test/ > NUL
	cp $ProcessorType/PxeBaseCodeBBTest.efi                    $Framework/Test/ > NUL
#Note: SCSI Passthru Protocol BB is deprecated in SCT 2.3
#	cp $ProcessorType/ScsiPassThruBbTest.efi                   $Framework/Test/ > NUL
	cp $ProcessorType/ScsiIoBBTest.efi                         $Framework/Test/ > NUL
	cp $ProcessorType/ExtScsiPassThruBBTest.efi                $Framework/Test/ > NUL
	cp $ProcessorType/iScsiInitiatorNameBBTest.efi             $Framework/Test/ > NUL
	cp $ProcessorType/SerialIoBbTest.efi                       $Framework/Test/ > NUL
	cp $ProcessorType/SimpleFileSystemBBTest.efi               $Framework/Test/ > NUL
	cp $ProcessorType/SimpleNetworkBBTest.efi                  $Framework/Test/ > NUL
	cp $ProcessorType/SimplePointerBBTest.efi                  $Framework/Test/ > NUL
	cp $ProcessorType/SimpleTextInBBTest.efi                   $Framework/Test/ > NUL
	cp $ProcessorType/SimpleTextOutBBTest.efi                  $Framework/Test/ > NUL
#Note: UGA I/O + UGA Draw Protocol BB is deprecated in SCT 2.3
#	cp $ProcessorType/UgaDrawBbTest.efi                        $Framework/Test/ > NUL
	cp $ProcessorType/GraphicsOutputBBTest.efi                 $Framework/Test/ > NUL
	cp $ProcessorType/UnicodeCollation2BBTest.efi              $Framework/Test/ > NUL
#Note: USB Host Controller Protocol BB is deprecated in SCT 2.3	
#	cp $ProcessorType/UsbHcTest.efi                            $Framework/Test/ > NUL
	cp $ProcessorType/UsbIoTest.efi                            $Framework/Test/ > NUL
	cp $ProcessorType/Usb2HcTest.efi                           $Framework/Test/ > NUL
	cp $ProcessorType/AuthenticationBBTest.efi                 $Framework/Test/ > NUL
	cp $ProcessorType/HashBBTest.efi                           $Framework/Test/ > NUL
	cp $ProcessorType/TapeBBTest.efi                           $Framework/Test/ > NUL
	cp $ProcessorType/AcpiTableProtocolBBTest.efi              $Framework/Test/ > NUL
	cp $ProcessorType/SimpleTextInputExBBTest.efi              $Framework/Test/ > NUL
	cp $ProcessorType/ComponentName2BBTest.efi                 $Framework/Test/ > NUL
	cp $ProcessorType/DriverDiagnostics2BBTest.efi             $Framework/Test/ > NUL
	
	cp $ProcessorType/HIIDatabaseBBTest.efi                    $Framework/Test/ > NUL
	cp $ProcessorType/HIIStringBBTest.efi                      $Framework/Test/ > NUL
	cp $ProcessorType/HIIFontBBTest.efi                        $Framework/Test/ > NUL
	cp $ProcessorType/HIIImageBBTest.efi                       $Framework/Test/ > NUL
	
	cp $ProcessorType/AbsolutePointerBBTest.efi                $Framework/Test/ > NUL
#	cp $ProcessorType/DriverSupportedEfiVersionBBTest.efi      $Framework/Test/ > NUL
	cp $ProcessorType/PlatformToDriverConfigurationBBTest.efi  $Framework/Test/ > NUL
	
	cp $ProcessorType/HIIConfigAccessBBTest.efi                $Framework/Test/ > NUL
	cp $ProcessorType/HIIConfigRoutingBBTest.efi               $Framework/Test/ > NUL
	cp $ProcessorType/VlanConfigBBTest.efi                     $Framework/Test/ > NUL
	cp $ProcessorType/IPsecConfigBBTest.efi                    $Framework/Test/ > NUL
    cp $ProcessorType/IPsec2BBTest.efi                         $Framework/Test/ > NUL
	cp $ProcessorType/StorageSecurityCommandBBTest.efi  	   $Framework/Test/ > NUL
	# *********************************************
	# Copy ENTS binary
	# *********************************************
	
	cp $ProcessorType/SerialMonitor.efi                $Framework/Ents/Support/ > NUL
	cp $ProcessorType/MNPMonitor.efi                   $Framework/Ents/Support/ > NUL
	cp $ProcessorType/IP4Monitor.efi                   $Framework/Ents/Support/ > NUL
	cp $ProcessorType/Eftp.efi                         $Framework/Ents/Support/ > NUL
	
	cp $ProcessorType/BootService_ENTSTest.efi         $Framework/Ents/Test/    > NUL
	cp $ProcessorType/RuntimeService_ENTSTest.efi      $Framework/Ents/Test/    > NUL
	cp $ProcessorType/GenericService_ENTSTest.efi      $Framework/Ents/Test/    > NUL
	
	cp $ProcessorType/SimpleNetwork_ENTSTest.efi       $Framework/Ents/Test/    > NUL
	cp $ProcessorType/PXEBaseCode_ENTSTest.efi         $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Mnp*_ENTSTest.efi                $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Arp*_ENTSTest.efi                $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Ip4*_ENTSTest.efi                $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Ip6*_ENTSTest.efi                $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Udp4*_ENTSTest.efi               $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Udp6*_ENTSTest.efi               $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Dhcp4*_ENTSTest.efi              $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Dhcp6*_ENTSTest.efi              $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Mtftp4*_ENTSTest.efi             $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Mtftp6*_ENTSTest.efi             $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Tcp4*_ENTSTest.efi               $Framework/Ents/Test/    > NUL
	cp $ProcessorType/Tcp6*_ENTSTest.efi               $Framework/Ents/Test/    > NUL
	
	# *********************************************
	# Copy the test dependency files
	# *********************************************
	
	CopyDependency EfiCompliant
	CopyDependency ProtocolHandlerServices
	CopyDependency ImageServices
	CopyDependency Decompress
	CopyDependency DeviceIo
	CopyDependency Ebc
	CopyDependency LoadedImage
	CopyDependency PciIo
	CopyDependency PciRootBridgeIo
	CopyDependency PxeBaseCode
fi

# *********************************************
# For IHV SCT
# *********************************************

if [ $1 = "hv_sct" ]
then
  # *********************************************
  # Copy the EFI 1.10 Test Cases for IHV
  # *********************************************

  cp $ProcessorType/IhvBlockIoBbTest.efi                     $Framework/Test/ > NUL
  cp $ProcessorType/IhvComponentNameBbTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvComponentName2BbTest.efi              $Framework/Test/ > NUL
  cp $ProcessorType/IhvBusSpecificDriverOverrideBbTest.efi   $Framework/Test/ > NUL
  cp $ProcessorType/IhvDeviceIoBbTest.efi                    $Framework/Test/ > NUL
  cp $ProcessorType/IhvDevicePathBbTest.efi                  $Framework/Test/ > NUL
  cp $ProcessorType/IhvDiskIoBbTest.efi                      $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverBindingBbTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverConfigurationBbTest.efi         $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverDiagnosticsBBTest.efi           $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverDiagnostics2BbTest.efi          $Framework/Test/ > NUL
  cp $ProcessorType/IhvEbcBbTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvPlatformDriverOverrideBbTest.efi      $Framework/Test/ > NUL
  cp $ProcessorType/IhvPxeBaseCodeBbTest.efi                 $Framework/Test/ > NUL
  cp $ProcessorType/IhvScsiPassThruBbTest.efi                $Framework/Test/ > NUL
  cp $ProcessorType/IhvSerialIoBbTest.efi                    $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleFileSystemBbTest.efi            $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleNetworkBbTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimplePointerBbTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextInBbTest.efi                $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextInputExBBTest.efi           $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextOutBbTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvGraphicsOutputBBTest.efi              $Framework/Test/ > NUL
  cp $ProcessorType/IhvExtScsiPassThruBbTest.efi             $Framework/Test/ > NUL
  cp $ProcessorType/IhvScsiIoBBTest.efi                      $Framework/Test/ > NUL
  cp $ProcessorType/IhvUgaDrawBbTest.efi                     $Framework/Test/ > NUL
  cp $ProcessorType/IhvUnicodeCollationBbTest.efi            $Framework/Test/ > NUL
  cp $ProcessorType/IhvUnicodeCollation2BbTest.efi           $Framework/Test/ > NUL
  cp $ProcessorType/IhvUsbHcTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvUsbIoTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvUsb2HcTest.efi                        $Framework/Test/ > NUL
  cp $ProcessorType/IhviScsiInitiatorNameBBTest.efi          $Framework/Test/ > NUL
  cp $ProcessorType/IhvStorageSecurityCommandBBTest.efi      $Framework/Test/ > NUL

  # *********************************************
  # Copy the UEFI 2.1 Test Cases for IHV
  # *********************************************

  cp $ProcessorType/IhvAbsolutePointerBBTest.efi             $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverSupportedEfiVersionBBTest.efi   $Framework/Test/ > NUL
  cp $ProcessorType/IhvPlatformToDriverConfigurationBBTest.efi  $Framework/Test/ > NUL
  
  # *********************************************
  # Copy the test dependency files
  # *********************************************

  CopyDependency DeviceIo
  CopyDependency Ebc
  CopyDependency PxeBaseCode
fi

