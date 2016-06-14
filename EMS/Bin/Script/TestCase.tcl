#
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
# Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010, Intel Corporation. All rights reserved.<BR> 
#
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

