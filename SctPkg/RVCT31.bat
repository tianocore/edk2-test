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
@REM Copyright 2006 - 2012 Unified EFI, Inc. All
@REM Rights Reserved, subject to all existing rights in all      
@REM matters included within this Test Suite, to which United    
@REM EFI, Inc. makes no claim of right.                          
@REM                                                             
@REM Copyright (c) 2011, 2012 ARM Ltd. All rights reserved.<BR>

CALL ../edksetup.bat
SET efi_source=%WORKSPACE%
SET edk_source=%WORKSPACE%\EdkCompatibilityPkg
build -p %WORKSPACE%\SctPkg\UEFI\UEFI_SCT.dsc -t RVCT31 -a ARM %1 %2 %3 %4