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
#     Implementation for EMS misc utility function
#

if {[info exist UTILITY_TCL] == 1} {
  return
}
set UTILITY_TCL 1

# 
# Routine Description:
# 
#   Wait for the lock.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsWaitForMutex {} {
  global _ENTS GuiBoxs GuiCursors GuiFrames

  if { $_ENTS(blockflag) != 0 } {
    return -1
  }
  
  set _ENTS(blockflag) 1

  $GuiFrames(button) configure -cursor $GuiCursors(busy)
  $GuiBoxs(output)   configure -cursor $GuiCursors(busy)
  $GuiBoxs(testcase) configure -cursor $GuiCursors(busy)
  update 
  return 0
}

# 
# Routine Description:
# 
#   Release the lock.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsReleaseMutex {} {
  global _ENTS GuiBoxs GuiCursors GuiFrames

  $GuiFrames(button) configure -cursor $GuiCursors(default)
  $GuiBoxs(output)   configure -cursor $GuiCursors(default)
  $GuiBoxs(testcase) configure -cursor $GuiCursors(default)
  set _ENTS(blockflag) 0
}

# 
# Routine Description:
# 
#   Generate report.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc CmdTestReport { } {
  global _ENTS EmsActiveLeftFrame

  if {[EmsTestIsRunning] == 1} {
    tk_messageBox -message "can not generate report when test is running" -type ok 
    return
  }

  if {[EmsWaitForMutex] == -1} {
    return
  }

  if {[file exists "Report"]} {
    if {[file type "Report"] != "directory"} {
      file delete "Report" -force
      file mkdir "Report"
	}
  } else {
    file mkdir "Report"
  }

  switch $EmsActiveLeftFrame {
    "RemoteExecution"   {RemoteExecutionTestReport}
    "RemoteValidation"  {RemoteValidationTestReport}
  }
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   Show the message in the status bar.
# 
# Arguments:
# 
#   status  : The string to show
# 
# Returns:
# 
#   None.
#
proc EmsShowStatus { Status } {
  global _ENTS
  set _ENTS(status) $Status
}

# 
# Routine Description:
# 
#   The callback function of reload a case tree
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
#
proc CmdCaseTreeReload {} {
  global EmsActiveLeftFrame

  if {[EmsTestIsRunning] == 1} {
    tk_messageBox -message "can not rebuild case tree when test is running" -type ok 
    return
  }

  if {[EmsWaitForMutex] == -1} {
    return
  }

  switch $EmsActiveLeftFrame {
    "RemoteExecution"   {RemoteExecutionReload}
    "RemoteValidation"  {RemoteValidationReload}
  }
  EmsReleaseMutex
}
