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
#     Sequence.tcl
#     
# Abstract:
# 
#     Implementation for EMS test case sequence functions
#

if {[info exist SEQUENCE_TCL] == 1} {
  return
}
set SEQUENCE_TCL 1

# 
# Routine Description:
# 
#   The callback funnction of loading a sequence file
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc CmdLoadSequence {} {
  global EmsActiveLeftFrame

  if {[EmsWaitForMutex] == -1} {
    return
  }
  switch $EmsActiveLeftFrame {
    "RemoteExecution"    {LoadRemoteExecutionSequence}
    "RemoteValidation"   {LoadRemoteValidationSequence}
  }
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   The callback function of Saving a sequence file
# 
# Arguments:
# 
#   Root - The root of test case
# 
# Returns:
# 
#   None.
# 
proc CmdSaveSequence {{Root "RemoteExecution"}} {
  global EmsActiveLeftFrame
  if {[EmsWaitForMutex] == -1} {
    return
  }
  switch $EmsActiveLeftFrame {
    "RemoteExecution"    {SaveRemoteExecutionSequence}
    "RemoteValidation"   {SaveRemoteValidationSequence}
  }
  EmsReleaseMutex
}

