#!/bin/sh
#
#  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
#  Copyright (c) 2011 - 2019, ARM Ltd. All rights reserved.<BR>
#  Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<CR>
#  (C) Copyright 2017 Hewlett Packard Enterprise Development LP<BR>
#  Copyright (c) 2019,Microchip Technology Inc.<BR>
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
# 
# Module Name
#
#   CommonGenFramework.sh
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
    cp $Source     $Framework/Dependency/$1BBTest/$Target > NUL
}

# *********************************************
# Copy the test dependency files for each test
# *********************************************

CopyDependency()
{
    mkdir -p $Framework/Dependency/$1BBTest	
    ls -h $ProcessorType/$1_Invalid*       > temp.txt 2>NUL
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
    echo "Generating UEFI SCT binary"
    # *********************************************
    # Copy the UEFI 2.1 Test Cases
    # *********************************************

    mkdir -p $Framework/SCRT
    cp $ProcessorType/SCRTDRIVER.efi                           $Framework/SCRT  > NUL
    cp $ProcessorType/SCRTAPP.efi                              $Framework/SCRT  > NUL
    cp ../../../SctPkg/Config/Data/SCRT.conf                   $Framework/SCRT  > NUL

    cp $ProcessorType/EfiCompliantBBTest.efi                   $Framework/Test/ > NUL

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
    cp $ProcessorType/BlockIo2BBTest.efi                       $Framework/Test/ > NUL
    cp $ProcessorType/BusSpecificDriverOverrideBBTest.efi      $Framework/Test/ > NUL
#   cp $ProcessorType/ComponentNameBBTest.efi                  $Framework/Test/ > NUL
    cp $ProcessorType/DebugPortBBTest.efi                      $Framework/Test/ > NUL
    cp $ProcessorType/DebugSupportBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/DecompressBBTest.efi                     $Framework/Test/ > NUL
#Note: Device IO BB is deprecated in SCT 2.3
#   cp $ProcessorType/DeviceIoBBTest.efi                       $Framework/Test/ > NUL
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
#   cp $ProcessorType/ScsiPassThruBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/ScsiIoBBTest.efi                         $Framework/Test/ > NUL
    cp $ProcessorType/ExtScsiPassThruBBTest.efi                $Framework/Test/ > NUL
    cp $ProcessorType/AtaPassThruBBTest.efi                    $Framework/Test/ > NUL
    cp $ProcessorType/iScsiInitiatorNameBBTest.efi             $Framework/Test/ > NUL
    cp $ProcessorType/SerialIoBBTest.efi                       $Framework/Test/ > NUL
    cp $ProcessorType/SimpleFileSystemBBTest.efi               $Framework/Test/ > NUL
    cp $ProcessorType/SimpleNetworkBBTest.efi                  $Framework/Test/ > NUL
    cp $ProcessorType/SimplePointerBBTest.efi                  $Framework/Test/ > NUL
    cp $ProcessorType/SimpleTextInBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/SimpleTextOutBBTest.efi                  $Framework/Test/ > NUL
#Note: UGA I/O + UGA Draw Protocol BB is deprecated in SCT 2.3
#   cp $ProcessorType/UgaDrawBbTest.efi                        $Framework/Test/ > NUL
    cp $ProcessorType/GraphicsOutputBBTest.efi                 $Framework/Test/ > NUL
    cp $ProcessorType/UnicodeCollation2BBTest.efi              $Framework/Test/ > NUL
#Note: USB Host Controller Protocol BB is deprecated in SCT 2.3	
#   cp $ProcessorType/UsbHcTest.efi                            $Framework/Test/ > NUL
    cp $ProcessorType/UsbIoTest.efi                            $Framework/Test/ > NUL
    cp $ProcessorType/Usb2HcTest.efi                           $Framework/Test/ > NUL
#    cp $ProcessorType/AuthenticationBBTest.efi                 $Framework/Test/ > NUL
#   cp $ProcessorType/HashBBTest.efi                           $Framework/Test/ > NUL
    cp $ProcessorType/TapeBBTest.efi                           $Framework/Test/ > NUL
    cp $ProcessorType/AcpiTableProtocolBBTest.efi              $Framework/Test/ > NUL
    cp $ProcessorType/SimpleTextInputExBBTest.efi              $Framework/Test/ > NUL
    cp $ProcessorType/ComponentName2BBTest.efi                 $Framework/Test/ > NUL
    cp $ProcessorType/DriverDiagnostics2BBTest.efi             $Framework/Test/ > NUL
    
    cp $ProcessorType/HIIDatabaseBBTest.efi                    $Framework/Test/ > NUL
    cp $ProcessorType/HIIStringBBTest.efi                      $Framework/Test/ > NUL
    cp $ProcessorType/HIIFontBBTest.efi                        $Framework/Test/ > NUL
    cp $ProcessorType/HIIFontExBBTest.efi                      $Framework/Test/ > NUL
    cp $ProcessorType/HIIImageBBTest.efi                       $Framework/Test/ > NUL
    cp $ProcessorType/HIIImageExBBTest.efi                     $Framework/Test/ > NUL

    cp $ProcessorType/AbsolutePointerBBTest.efi                $Framework/Test/ > NUL
#   cp $ProcessorType/DriverSupportedEfiVersionBBTest.efi      $Framework/Test/ > NUL
    cp $ProcessorType/PlatformToDriverConfigurationBBTest.efi  $Framework/Test/ > NUL
    cp $ProcessorType/HIIConfigAccessBBTest.efi                $Framework/Test/ > NUL
    cp $ProcessorType/HIIConfigRoutingBBTest.efi               $Framework/Test/ > NUL
    cp $ProcessorType/VlanConfigBBTest.efi                     $Framework/Test/ > NUL
    cp $ProcessorType/IPsecConfigBBTest.efi                    $Framework/Test/ > NUL
    cp $ProcessorType/IPsec2BBTest.efi                         $Framework/Test/ > NUL
    cp $ProcessorType/StorageSecurityCommandBBTest.efi         $Framework/Test/ > NUL

    cp $ProcessorType/FirmwareManagementBBTest.efi             $Framework/Test/ > NUL

    cp $ProcessorType/AdapterInfoBBTest.efi                    $Framework/Test/ > NUL
    cp $ProcessorType/DiskIo2BBTest.efi                        $Framework/Test/ > NUL
    cp $ProcessorType/TimeStampBBTest.efi                      $Framework/Test/ > NUL
    cp $ProcessorType/RandomNumberBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/TCG2ProtocolBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/Hash2BBTest.efi                          $Framework/Test/ > NUL
    cp $ProcessorType/Pkcs7BBTest.efi                          $Framework/Test/ > NUL
    cp $ProcessorType/ConfigKeywordHandlerBBTest.efi           $Framework/Test/ > NUL
    cp $ProcessorType/RegularExpressionBBTest.efi              $Framework/Test/ > NUL

    cp $ProcessorType/RamDiskProtocolBBTest.efi                $Framework/Test/ > NUL
    cp $ProcessorType/NVMEPassThruBBTest.efi                   $Framework/Test/ > NUL
    cp $ProcessorType/EraseBlockBBTest.efi                     $Framework/Test/ > NUL
    cp $ProcessorType/SDMMCPassThruBBTest.efi                  $Framework/Test/ > NUL
    cp $ProcessorType/PartitionInfoBBTest.efi                  $Framework/Test/ > NUL
    cp $ProcessorType/UFSDeviceConfigBBTest.efi                $Framework/Test/ > NUL
    cp $ProcessorType/ResetNotificationBBTest.efi              $Framework/Test/ > NUL
    # Only include RiscVBootProtocolBBTest.efi if the file exists (true on RISCV64)
    if [ -e $ProcessorType/RiscVBootProtocolBBTest.efi ]; then
      cp $ProcessorType/RiscVBootProtocolBBTest.efi              $Framework/Test/ > NUL
    fi

    # *********************************************
    # Copy ENTS binary
    # *********************************************

    cp $ProcessorType/SerialMonitor.efi                $Framework/Ents/Support/ > NUL
    cp $ProcessorType/ManagedNetworkMonitor.efi        $Framework/Ents/Support/ > NUL
    cp $ProcessorType/IP4NetworkMonitor.efi            $Framework/Ents/Support/ > NUL
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
    cp $ProcessorType/Http*_ENTSTest.efi               $Framework/Ents/Test/    > NUL
	
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
    CopyDependency ConfigKeywordHandler
fi

# *********************************************
# For IHV SCT
# *********************************************

if [ $1 = "ihv_sct" ]
then
  echo "Generating IHV SCT binary"
  # *********************************************
  # Copy the EFI 1.10 Test Cases for IHV
  # *********************************************

  cp $ProcessorType/IhvBlockIoBBTest.efi                     $Framework/Test/ > NUL
  cp $ProcessorType/IhvBlockIo2BBTest.efi                    $Framework/Test/ > NUL
#  cp $ProcessorType/IhvComponentNameBBTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvComponentName2BBTest.efi              $Framework/Test/ > NUL
  cp $ProcessorType/IhvBusSpecificDriverOverrideBBTest.efi   $Framework/Test/ > NUL
#  cp $ProcessorType/IhvDeviceIoBBTest.efi                    $Framework/Test/ > NUL
  cp $ProcessorType/IhvDevicePathBBTest.efi                  $Framework/Test/ > NUL
  cp $ProcessorType/IhvDiskIoBBTest.efi                      $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverBindingBBTest.efi               $Framework/Test/ > NUL
#  cp $ProcessorType/IhvDriverConfigurationBBTest.efi         $Framework/Test/ > NUL
#  cp $ProcessorType/IhvDriverDiagnosticsBBTest.efi           $Framework/Test/ > NUL
  cp $ProcessorType/IhvDriverDiagnostics2BBTest.efi          $Framework/Test/ > NUL
  cp $ProcessorType/IhvEbcBBTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvPxeBaseCodeBBTest.efi                 $Framework/Test/ > NUL
#  cp $ProcessorType/IhvScsiPassThruBBTest.efi                $Framework/Test/ > NUL
  cp $ProcessorType/IhvSerialIoBBTest.efi                    $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleFileSystemBBTest.efi            $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleNetworkBBTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimplePointerBBTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextInBBTest.efi                $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextInputExBBTest.efi           $Framework/Test/ > NUL
  cp $ProcessorType/IhvSimpleTextOutBBTest.efi               $Framework/Test/ > NUL
  cp $ProcessorType/IhvGraphicsOutputBBTest.efi              $Framework/Test/ > NUL
  cp $ProcessorType/IhvExtScsiPassThruBBTest.efi             $Framework/Test/ > NUL
  cp $ProcessorType/IhvScsiIoBBTest.efi                      $Framework/Test/ > NUL
#  cp $ProcessorType/IhvUgaDrawBBTest.efi                     $Framework/Test/ > NUL
#  cp $ProcessorType/IhvUnicodeCollationBBTest.efi            $Framework/Test/ > NUL
  cp $ProcessorType/IhvUnicodeCollation2BBTest.efi           $Framework/Test/ > NUL
#  cp $ProcessorType/IhvUsbHcTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvUsbIoTest.efi                         $Framework/Test/ > NUL
  cp $ProcessorType/IhvUsb2HcTest.efi                        $Framework/Test/ > NUL
  cp $ProcessorType/IhviScsiInitiatorNameBBTest.efi          $Framework/Test/ > NUL
  cp $ProcessorType/IhvStorageSecurityCommandBBTest.efi      $Framework/Test/ > NUL
  cp $ProcessorType/IhvFirmwareManagementBBTest.efi          $Framework/Test/ > NUL
  cp $ProcessorType/IhvHIIConfigAccessBBTest.efi             $Framework/Test/ > NUL

  # *********************************************
  # Copy the UEFI 2.1 Test Cases for IHV
  # *********************************************

  cp $ProcessorType/IhvAbsolutePointerBBTest.efi             $Framework/Test/ > NUL
#  cp $ProcessorType/IhvDriverSupportedEfiVersionBBTest.efi   $Framework/Test/ > NUL
  if [ $ProcessorType = "IA32" ] || [ $ProcessorType = "X64" ]
  then
     cp $ProcessorType/IhvPlatformDriverOverrideBBTest.efi      $Framework/Test/ > NUL
     cp $ProcessorType/IhvPlatformToDriverConfigurationBBTest.efi  $Framework/Test/ > NUL
  fi
  # *********************************************
  # Copy the test dependency files
  # *********************************************

  cp $ProcessorType/IhvAdapterInfoBBTest.efi                 $Framework/Test/ > NUL
  cp $ProcessorType/IhvDiskIo2BBTest.efi                     $Framework/Test/ > NUL

  CopyDependency DeviceIo
  CopyDependency Ebc
  CopyDependency PxeBaseCode
fi

