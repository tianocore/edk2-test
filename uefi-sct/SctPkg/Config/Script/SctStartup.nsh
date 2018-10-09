## @file
#
#  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
#  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
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
#   SctStartup.nsh
#
# Abstract:
#
#   Startup script for EFI SCT automatic running
#
#--*/

#
# NOTE: The file system name is hard coded since I don't know how to get the
# file system name in the script.
#

echo -off

for %i in 0 1 2 3 4 5 6 7 8 9 A B C D E F
  if exist FS%i:\Sct then
    #
    # Found EFI SCT harness
    #
    FS%i:
    cd Sct

    echo Press any key to stop the EFI SCT running

    stallforkey.efi 5
    if %lasterror% == 0 then
      goto Done
    endif

    if exist FS%i:\Sct\.passive.mode then
      if exist FS%i:\Sct\.verbose.mode then
        Sct -c -p mnp -v
      else
        Sct -c -p mnp
      endif
    else
      if exist FS%i:\Sct\.verbose.mode then
        Sct -c -v
      else
        Sct -c
      endif
    endif
    
#    load SCRT\SCRTDriver.efi
#    SCRT\SCRTApp.efi

    goto Done
  endif
endfor

:Done
