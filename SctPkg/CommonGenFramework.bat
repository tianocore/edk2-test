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
@REM Copyright 2006 - 2016 Unified EFI, Inc. All
@REM Rights Reserved, subject to all existing rights in all      
@REM matters included within this Test Suite, to which United    
@REM EFI, Inc. makes no claim of right.                          
@REM                                                             
@REM Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR> 
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

copy %ProcessorType%\EfiCompliantBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\ExeModeBBTest.efi                        %Framework%\Test\ > NUL

copy %ProcessorType%\EventTimerTaskPriorityServicesBBTest.efi %Framework%\Test\ > NUL
copy %ProcessorType%\MemoryAllocationServicesBBTest.efi       %Framework%\Test\ > NUL
copy %ProcessorType%\ProtocolHandlerServicesBBTest.efi        %Framework%\Test\ > NUL
copy %ProcessorType%\ImageServicesBBTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\MiscBootServicesBBTest.efi               %Framework%\Test\ > NUL

copy %ProcessorType%\VariableServicesBBTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\TimeServicesBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\MiscRuntimeServicesBBTest.efi            %Framework%\Test\ > NUL

copy %ProcessorType%\BisBBTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\BlockIoBBTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\BlockIo2BBTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\BusSpecificDriverOverrideBBTest.efi      %Framework%\Test\ > NUL
rem copy %ProcessorType%\ComponentNameBBTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\DebugPortBBTest.efi                      %Framework%\Test\ > NUL
copy %ProcessorType%\DebugSupportBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\DecompressBBTest.efi                     %Framework%\Test\ > NUL
rem copy %ProcessorType%\DeviceIoBBTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathBBTest.efi                     %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathUtilitiesBBTest.efi            %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathToTextBBTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\DevicePathFromTextBBTest.efi             %Framework%\Test\ > NUL
copy %ProcessorType%\DiskIoBBTest.efi                         %Framework%\Test\ > NUL
rem copy %ProcessorType%\DriverDiagnosticsBBTest.efi              %Framework%\Test\ > NUL
rem copy %ProcessorType%\DriverConfigurationBBTest.efi            %Framework%\Test\ > NUL
copy %ProcessorType%\EbcBBTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\LoadedImageBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\LoadFileBBTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\PciIoBBTest.efi                          %Framework%\Test\ > NUL
copy %ProcessorType%\PciRootBridgeIoBBTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\PlatformDriverOverrideBBTest.efi         %Framework%\Test\ > NUL
copy %ProcessorType%\PxeBaseCodeBBTest.efi                    %Framework%\Test\ > NUL
rem copy %ProcessorType%\ScsiPassThruBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\ScsiIoBBTest.efi                         %Framework%\Test\ > NUL
copy %ProcessorType%\ExtScsiPassThruBBTest.efi                %Framework%\Test\ > NUL
copy %ProcessorType%\AtaPassThruBBTest.efi                    %Framework%\Test\ > NUL
copy %ProcessorType%\iScsiInitiatorNameBBTest.efi             %Framework%\Test\ > NUL
copy %ProcessorType%\SerialIoBBTest.efi                       %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleFileSystemBBTest.efi               %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleNetworkBBTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimplePointerBBTest.efi                  %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextInBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextOutBBTest.efi                  %Framework%\Test\ > NUL
rem copy %ProcessorType%\UgaDrawBBTest.efi                        %Framework%\Test\ > NUL
copy %ProcessorType%\GraphicsOutputBBTest.efi                 %Framework%\Test\ > NUL
copy %ProcessorType%\UnicodeCollation2BBTest.efi              %Framework%\Test\ > NUL
rem copy %ProcessorType%\UsbHcTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\UsbIoTest.efi                            %Framework%\Test\ > NUL
copy %ProcessorType%\Usb2HcTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\AuthenticationBBTest.efi                 %Framework%\Test\ > NUL
rem copy %ProcessorType%\HashBBTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\TapeBBTest.efi                           %Framework%\Test\ > NUL
copy %ProcessorType%\AcpiTableProtocolBBTest.efi              %Framework%\Test\ > NUL
copy %ProcessorType%\SimpleTextInputExBBTest.efi              %Framework%\Test\ > NUL
copy %ProcessorType%\ComponentName2BBTest.efi                 %Framework%\Test\ > NUL
copy %ProcessorType%\DriverDiagnostics2BBTest.efi             %Framework%\Test\ > NUL

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
copy %ProcessorType%\RandomNumberBBTest.efi                   %Framework%\Test\ > NUL
copy %ProcessorType%\Hash2BBTest.efi                          %Framework%\Test\ > NUL
copy %ProcessorType%\Pkcs7BBTest.efi                          %Framework%\Test\ > NUL
copy %ProcessorType%\ConfigKeywordHandlerBBTest.efi           %Framework%\Test\ > NUL

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
call :CopyDependency ConfigKeywordHandler
)

rem *********************************************
rem For IHV SCT
rem *********************************************

if %1. EQU ihv_sct. (
  rem *********************************************
  rem Copy the EFI 1.10 Test Cases for IHV
  rem *********************************************

  copy %ProcessorType%\IhvBlockIoBBTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvBlockIo2BBTest.efi                    %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvComponentNameBBTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvComponentName2BBTest.efi              %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvBusSpecificDriverOverrideBBTest.efi   %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDeviceIoBBTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDevicePathBBTest.efi                  %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDiskIoBBTest.efi                      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverBindingBBTest.efi               %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDriverConfigurationBBTest.efi         %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvDriverDiagnosticsBBTest.efi           %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvDriverDiagnostics2BBTest.efi          %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvEbcBBTest.efi                         %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPlatformDriverOverrideBBTest.efi      %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvPxeBaseCodeBBTest.efi                 %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvScsiPassThruBBTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSerialIoBBTest.efi                    %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleFileSystemBBTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleNetworkBBTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimplePointerBBTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextInBBTest.efi                %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextInputExBBTest.efi           %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvSimpleTextOutBBTest.efi               %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvGraphicsOutputBBTest.efi              %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvExtScsiPassThruBBTest.efi             %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvScsiIoBBTest.efi                      %Framework%\Test\ > NUL
rem  copy %ProcessorType%\IhvUgaDrawBBTest.efi                     %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUnicodeCollationBBTest.efi            %Framework%\Test\ > NUL
  copy %ProcessorType%\IhvUnicodeCollation2BBTest.efi           %Framework%\Test\ > NUL
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

mkdir %Framework%\Dependency\%1BBTest

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

copy %ProcessorType%\%Source%     %Framework%\Dependency\%1BBTest\%Target%  > NUL

endlocal

goto :EOF
