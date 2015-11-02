@REM
@REM The material contained herein is not a license, either      
@REM expressly or impliedly, to any intellectual property owned  
@REM or controlled by any of the authors or developers of this   
@REM material or to any contribution thereto. The material       
@REM contained herein is provided on an "AS IS" basis and, to the
@REM maximum extent permitted by applicable law, this information
@REM is provided AS IS AND WITH ALL FAULTS, and the authors and  
@REM developers of this material hereby disclaim all other       
@REM warranties and conditions, either express, implied or       
@REM statutory, including, but not limited to, any (if any)      
@REM implied warranties, duties or conditions of merchantability,
@REM of fitness for a particular purpose, of accuracy or         
@REM completeness of responses, of results, of workmanlike       
@REM effort, of lack of viruses and of lack of negligence, all   
@REM with regard to this material and any contribution thereto.  
@REM Designers must not rely on the absence or characteristics of
@REM any features or instructions marked "reserved" or           
@REM "undefined." The Unified EFI Forum, Inc. reserves any       
@REM features or instructions so marked for future definition and
@REM shall have no responsibility whatsoever for conflicts or    
@REM incompatibilities arising from future changes to them. ALSO,
@REM THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,
@REM QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR          
@REM NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY      
@REM CONTRIBUTION THERETO.                                       
@REM                                                             
@REM IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR
@REM ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR   
@REM THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST    
@REM PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,      
@REM CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER 
@REM UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY
@REM WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS     
@REM DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF   
@REM THE POSSIBILITY OF SUCH DAMAGES.                            
@REM                                                             
@REM Copyright 2006 - 2013 Unified EFI, Inc. All
@REM Rights Reserved, subject to all existing rights in all      
@REM matters included within this Test Suite, to which United    
@REM EFI, Inc. makes no claim of right.                          
@REM                                                             
@REM Copyright (c) 2010 - 2014, Intel Corporation. All rights reserved.<BR> 
@REM
@REM
@echo %DEBUG% OFF

@echo %DEBUG% OFF

rem /*++
rem 
rem Module Name:
rem
rem   CommonGenFramework.bat
rem
rem Abstract:
rem
rem   Common part for generating the test package
rem
rem --*/

set ProcessorType=%2
set Installer=%3

set Framework=SctPackage%ProcessorType%\%ProcessorType%

rem *********************************************
rem Create target directory
rem *********************************************

if exist %Framework% (
  rmdir /s /q %Framework%
)

mkdir %Framework%
mkdir %Framework%\Data
mkdir %Framework%\Dependency
mkdir %Framework%\Support
mkdir %Framework%\Test
mkdir %Framework%\Sequence
mkdir %Framework%\Report
mkdir %Framework%\Application
mkdir %Framework%\Proxy
mkdir %Framework%\Ents\Support
mkdir %Framework%\Ents\Test


rem *********************************************
rem Copy the SCT framework and the related application
rem *********************************************

copy %ProcessorType%\SCT.efi              %Framework%\            > NUL

copy %ProcessorType%\StandardTest.efi     %Framework%\Support\    > NUL
copy %ProcessorType%\TestProfile.efi      %Framework%\Support\    > NUL
copy %ProcessorType%\TestRecovery.efi     %Framework%\Support\    > NUL
copy %ProcessorType%\TestLogging.efi      %Framework%\Support\    > NUL

copy ..\..\..\SctPkg\Config\Script\SctStartup.nsh   SctPackage%ProcessorType%\             > NUL
copy %ProcessorType%\InstallSct.efi       SctPackage%ProcessorType%\%Installer%  > NUL
copy %ProcessorType%\StallForKey.efi      %Framework%\            > NUL

rem *********************************************
rem Copy the SCT configuration data
rem *********************************************

copy ..\..\..\SctPkg\Config\Data\Category.ini       %Framework%\Data\       > NUL
copy ..\..\..\SctPkg\Config\Data\GuidFile.txt       %Framework%\Data\       > NUL

rem *********************************************
rem For UEFI SCT
rem *********************************************

if %1. EQU uefi_sct. (
rem *********************************************
rem Copy the UEFI 2.1 Test Cases
rem *********************************************

mkdir %Framework%\SCRT
copy %ProcessorType%\SCRTDriver.efi           %Framework%\SCRT            > NUL
copy %ProcessorType%\SCRTApp.efi              %Framework%\SCRT            > NUL
copy ..\..\..\SctPkg\Config\Data\SCRT.conf    %Framework%\SCRT            > NUL

copy %ProcessorType%\EfiCompliantBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\ExeModeBBTest.efi                        %Framework%\Test\ > NUL

copy %ProcessorType%\EventTimerTaskPriorityServicesBbTest.efi %Framework%\Test\ > NUL
copy %ProcessorType%\MemoryAllocationServicesBbTest.efi       %Framework%\Test\ > NUL
copy %ProcessorType%\ProtocolHandlerServicesBbTest.efi        %Framework%\Test\ > NUL
copy %ProcessorType%\ImageServicesBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\MiscBootServicesBbTest.efi               %Framework%\Test\ > NUL

copy %ProcessorType%\VariableServicesBbTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\TimeServicesBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\MiscRuntimeServicesBbTest.efi            %Framework%\Test\ > NUL

copy %ProcessorType%\BisBbTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\BlockIoBbTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\BlockIo2BbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\BusSpecificDriverOverrideBbTest.efi      %Framework%\Test\ > NUL
rem copy %ProcessorType%\ComponentNameBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\DebugPortBbTest.efi                      %Framework%\Test\ > NUL
copy %ProcessorType%\DebugSupportBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\DecompressBbTest.efi                     %Framework%\Test\ > NUL
rem copy %ProcessorType%\DeviceIoBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathBBTest.efi                     %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathUtilitiesBBTest.efi            %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathToTextBBTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathFromTextBBTest.efi             %Framework%\Test\ > NUL
copy %ProcessorType%\DiskIoBbTest.efi                         %Framework%\Test\ > NUL
rem copy %ProcessorType%\DriverDiagnosticsBbTest.efi              %Framework%\Test\ > NUL
rem copy %ProcessorType%\DriverConfigurationBbTest.efi            %Framework%\Test\ > NUL
copy %ProcessorType%\EbcBbTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\LoadedImageBbTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\LoadFileBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\PciIoBbTest.efi                          %Framework%\Test\ > NUL
copy %ProcessorType%\PciRootBridgeIoBbTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\PlatformDriverOverrideBbTest.efi         %Framework%\Test\ > NUL
copy %ProcessorType%\PxeBaseCodeBbTest.efi                    %Framework%\Test\ > NUL
rem copy %ProcessorType%\ScsiPassThruBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\ScsiIoBbTest.efi                         %Framework%\Test\ > NUL
copy %ProcessorType%\ExtScsiPassThruBbTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\AtaPassThruBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\iScsiInitiatorNameBBTest.efi             %Framework%\Test\ > NUL
copy %ProcessorType%\SerialIoBbTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleFileSystemBbTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleNetworkBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimplePointerBbTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextInBbTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextOutBbTest.efi                  %Framework%\Test\ > NUL
rem copy %ProcessorType%\UgaDrawBbTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\GraphicsOutputBBTest.efi                 %Framework%\Test\ > NUL
copy %ProcessorType%\UnicodeCollation2BbTest.efi              %Framework%\Test\ > NUL
rem copy %ProcessorType%\UsbHcTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\UsbIoTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\Usb2HcTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\AuthenticationBBTest.efi                 %Framework%\Test\ > NUL
rem copy %ProcessorType%\HashBBTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\TapeBBTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\AcpiTableProtocolBBTest.efi              %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextInputExBBTest.efi              %Framework%\Test\ > NUL
copy %ProcessorType%\ComponentName2BbTest.efi                 %Framework%\Test\ > NUL
copy %ProcessorType%\DriverDiagnostics2BbTest.efi             %Framework%\Test\ > NUL

copy %ProcessorType%\HIIDatabaseBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\HIIStringBBTest.efi                      %Framework%\Test\ > NUL
copy %ProcessorType%\HIIFontBBTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\HIIImageBBTest.efi                       %Framework%\Test\ > NUL

copy %ProcessorType%\AbsolutePointerBBTest.efi                %Framework%\Test\ > NUL
rem copy %ProcessorType%\DriverSupportedEfiVersionBBTest.efi      %Framework%\Test\ > NUL
copy %ProcessorType%\PlatformToDriverConfigurationBBTest.efi  %Framework%\Test\ > NUL

copy %ProcessorType%\HIIConfigAccessBBTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\HIIConfigRoutingBBTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\VlanConfigBBTest.efi                     %Framework%\Test\ > NUL
copy %ProcessorType%\IPsecConfigBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\IPsec2BBTest.efi                         %Framework%\Test\ > NUL
copy %ProcessorType%\StorageSecurityCommandBBTest.efi         %Framework%\Test\ > NUL

copy %ProcessorType%\FirmwareManagementBBTest.efi             %Framework%\Test\ > NUL

copy %ProcessorType%\AdapterInfoBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\DiskIo2BBTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\TimeStampBBTest.efi                      %Framework%\Test\ > NUL
copy %ProcessorType%\RandomNumberBbTest.efi                   %Framework%\Test\ > NUL


rem *********************************************
rem Copy ENTS binary
rem *********************************************

copy %ProcessorType%\SerialMonitor.efi                %Framework%\Ents\Support\ > NUL
copy %ProcessorType%\ManagedNetworkMonitor.efi        %Framework%\Ents\Support\ > NUL
copy %ProcessorType%\IP4NetworkMonitor.efi            %Framework%\Ents\Support\ > NUL
copy %ProcessorType%\Eftp.efi                         %Framework%\Ents\Support\ > NUL

copy %ProcessorType%\BootService_ENTSTest.efi         %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\RuntimeService_ENTSTest.efi      %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\GenericService_ENTSTest.efi      %Framework%\Ents\Test\    > NUL

copy %ProcessorType%\SimpleNetwork_ENTSTest.efi       %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\PXEBaseCode_ENTSTest.efi         %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Mnp*_ENTSTest.efi                %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Arp*_ENTSTest.efi                %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Ip4*_ENTSTest.efi                %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Ip6*_ENTSTest.efi                %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Udp4*_ENTSTest.efi               %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Udp6*_ENTSTest.efi               %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Dhcp4*_ENTSTest.efi              %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Dhcp6*_ENTSTest.efi              %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Mtftp4*_ENTSTest.efi             %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Mtftp6*_ENTSTest.efi             %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Tcp4*_ENTSTest.efi               %Framework%\Ents\Test\    > NUL
copy %ProcessorType%\Tcp6*_ENTSTest.efi               %Framework%\Ents\Test\    > NUL

rem *********************************************
rem Copy the test dependency files
rem *********************************************

call :CopyDependency EfiCompliant
call :CopyDependency ProtocolHandlerServices
call :CopyDependency ImageServices
call :CopyDependency Decompress
call :CopyDependency DeviceIo
call :CopyDependency Ebc
call :CopyDependency LoadedImage
call :CopyDependency PciIo
call :CopyDependency PciRootBridgeIo
call :CopyDependency PxeBaseCode
)

rem *********************************************
rem For IHV SCT
rem *********************************************

if %1. EQU ihv_sct. (
  rem *********************************************
  rem Copy the EFI 1.10 Test Cases for IHV
  rem *********************************************

  copy %ProcessorType%\IhvBlockIoBbTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvBlockIo2BbTest.efi                    %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvComponentNameBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvComponentName2BbTest.efi              %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvBusSpecificDriverOverrideBbTest.efi   %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDeviceIoBbTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDevicePathBbTest.efi                  %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDiskIoBbTest.efi                      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverBindingBbTest.efi               %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDriverConfigurationBbTest.efi         %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDriverDiagnosticsBbTest.efi           %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverDiagnostics2BbTest.efi          %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvEbcBbTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPlatformDriverOverrideBbTest.efi      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPxeBaseCodeBbTest.efi                 %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvScsiPassThruBbTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSerialIoBbTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleFileSystemBbTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleNetworkBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimplePointerBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextInBbTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextInputExBBTest.efi           %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextOutBbTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvGraphicsOutputBBTest.efi              %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvExtScsiPassThruBbTest.efi             %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvScsiIoBBTest.efi                      %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvUgaDrawBbTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUnicodeCollationBbTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUnicodeCollation2BbTest.efi           %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvUsbHcTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUsbIoTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUsb2HcTest.efi                        %Framework%\Test\ > NUL
  copy %ProcessorType%\IhviScsiInitiatorNameBBTest.efi          %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvStorageSecurityCommandBBTest.efi      %Framework%\Test\ > NUL
  
  rem *********************************************
  rem Copy the UEFI 2.1 Test Cases for IHV
  rem *********************************************

  copy %ProcessorType%\IhvAbsolutePointerBBTest.efi             %Framework%\Test\ > NUL
rem copy %ProcessorType%\IhvDriverSupportedEfiVersionBBTest.efi   %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPlatformToDriverConfigurationBBTest.efi  %Framework%\Test\ > NUL
  
  rem *********************************************
  rem Copy the test dependency files
  rem *********************************************

  copy %ProcessorType%\IhvAdapterInfoBBTest.efi                 %Framework%\Test\ > NUL  
  copy %ProcessorType%\IhvDiskIo2BBTest.efi                     %Framework%\Test\ > NUL  

  call :CopyDependency DeviceIo
  call :CopyDependency Ebc
  call :CopyDependency PxeBaseCode
)

echo DONE!
goto :EOF


rem *********************************************
rem Copy the test dependency files for each test
rem *********************************************

:CopyDependency

mkdir %Framework%\Dependency\%1BbTest

dir /b %ProcessorType%\%1_*.       > temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.efi   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.ini   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.cmp   >> temp.txt 2>NUL
dir /b %ProcessorType%\%1_*.ucmp  >> temp.txt 2>NUL

for /F "tokens=*" %%i in (temp.txt) do (
  call :CopyDependencyFile %1 %%i
)

del /f temp.txt >NUL

goto :EOF


rem *********************************************
rem Copy each test dependency file
rem *********************************************

:CopyDependencyFile

setlocal

set Source=%2
set Target=%Source:*_=%

copy %ProcessorType%\%Source%     %Framework%\Dependency\%1BbTest\%Target%  > NUL

endlocal

goto :EOF
