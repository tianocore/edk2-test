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
#     Implementation for EMS test case functions
#

if {[info exist TEST_CASE_TCL] == 1} {
  return
}
set TEST_CASE_TCL 1

# 
# Routine Description:
# 
#   Clean up the test environment.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsTestCleanup { } {
  CloseDev mnp
  return
}

# 
# Routine Description:
# 
#   Start the EMS test
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdTestStart {} {
  global _ENTS EmsActiveLeftFrame

  if {[EmsWaitForMutex] == -1} {
    return
  }

  if {[EmsTestIsRunning] == 1} {
    tk_messageBox -type ok -message "The Test is Running!"
    EmsReleaseMutex
	return
  }

  switch $EmsActiveLeftFrame {
    "RemoteExecution"   {RemoteExecutionTestStart}
    "RemoteValidation"  {RemoteValidationTestStart}
  }
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   Continue the EMS test
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdTestContinue {} {
  global _ENTS EmsActiveLeftFrame

  if {[EmsWaitForMutex] == -1} {
    return
  }

  if {[EmsTestIsRunning] == 1} {
    tk_messageBox -type ok -message "The Test is Running!"
    EmsReleaseMutex
	return
  }

  switch $EmsActiveLeftFrame {
    "RemoteExecution"   {RemoteExecutionTestContinue}
    "RemoteValidation"  {RemoteValidationTestContinue}
  }

  EmsReleaseMutex
}
 
# 
# Routine Description:
# 
#   Stop running test cases.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdTestStop { } {
  global _ENTS EmsActiveLeftFrame

  if {$EmsActiveLeftFrame == "RemoteExecution"} {
    tk_messageBox -type ok -message "Can not stop remote execution"
    return
  }

  if {[EmsTestIsRunning] == 0 } {
    return
  }

  set choice [tk_messageBox -type yesnocancel -default yes -message "Are you sure to stop running?" -icon question]
  if { [string compare $choice yes] == 0 } {
    tk_messageBox -type ok -message "The Test will stop after current test case fininsh"
	EmsRemoteValidationTestStop
  }
  return
}

# 
# Routine Description:
# 
#   Reload the test case tree
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdTestCaseReload {} {
  global _ENTS EmsActiveLeftFrame

  if {[EmsWaitForMutex] == -1} {
    return
  }

  switch $EmsActiveLeftFrame {
    "RemoteExecution"    {RemoteExecutionTestCaseReload}
    "RemoteValidation"   {RemoteValidationTestCaseReload}
  }
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   Check whether the case fail
# 
# Arguments:
# 
#   Result - The string of the case result
# 
# Returns:
# 
#   1 case fail
#   0 case no fail
# 
proc ResultHasFail {Result} {
  set FailPos [string last "(" $Result]
  if {$FailPos == -1} {return 1}
  if {[string range $Result [expr $FailPos + 1] [expr $FailPos + 1]] != "0"} {return 1}
  return 0
}

# 
# Routine Description:
# 
#   Check whether the result of case has warnning
# 
# Arguments:
# 
#   Result - The string of the case result
# 
# Returns:
# 
#   1 case result has warnning
#   0 case result has no warnning
# 
proc ResultHasWarn {Result} {
  set WarnRecord [string range $Result [expr [string first " " $Result] + 1] [expr [string last " " $Result] - 1]]
  set WarnPos [string first "(" $WarnRecord]
  if {$WarnPos == -1} {return 1}
  if {[string range $WarnRecord [expr $WarnPos + 1] [expr $WarnPos + 1]] != "0"} {return 1}
  return 0
}

