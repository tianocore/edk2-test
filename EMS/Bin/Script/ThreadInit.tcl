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
# 
# Module Name:
#   
#     TestCase.tcl
#     
# Abstract:
# 
#     script for EMS run test case thread initialization
#

Include ./Script/Init.tcl

# 
# Routine Description:
# 
#   Print the error message
# 
# Arguments:
# 
#   message - the message to print
# 
# Returns:
# 
#   None.
# 
proc EmsGuiError {Message} {
  catch "destroy .xxx"
  bell
  tk_dialog .xxx "Error" "$Message" warning 0 Close
}

