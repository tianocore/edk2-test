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
#     Implementation for EMS output form function
#

if {[info exist OUTPUT_TCL] == 1} {
  return
}
set OUTPUT_TCL 1

# 
# Routine Description:
# 
#   Output a message in output window.
# 
# Arguments:
# 
#   string     :   The message to show
# 
# Returns:
# 
#   None.
# 
proc EmsOutput { string } {
  global GuiBoxs
  EmsShowStatus "output start"
  $GuiBoxs(output) insert end $string
  $GuiBoxs(output) see end
  EmsShowStatus "output end"
  return 
}

# 
# Routine Description:
# 
#   Output an error message in output window.
# 
# Arguments:
# 
#   string     :   The message to show.
# 
# Returns:
# 
#   None.
# 
proc EmsOutputError { string } {
  global GuiBoxs
  $GuiBoxs(output) insert end $string gui_output_tags(error)
  $GuiBoxs(output) see end 
  update
  return 
}

# 
# Routine Description:
# 
#   Output an highlight message in output window.
# 
# Arguments:
# 
#   string     :   The message to show.
# 
# Returns:
# 
#   None.
# 
proc EmsOutputHighLight { string } {
  global GuiBoxs
  $GuiBoxs(output) insert end $string gui_output_tags(highlight)
  $GuiBoxs(output) see end 
  update
  return 
}

# 
# Routine Description:
# 
#   Clean up output window.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsClearOutput { } {
  global GuiBoxs
  $GuiBoxs(output) delete 1.0 end 
}
