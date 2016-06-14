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
