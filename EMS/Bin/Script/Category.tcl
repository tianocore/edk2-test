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
# Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
# Rights Reserved, subject to all existing rights in all      
# matters included within this Test Suite, to which United    
# EFI, Inc. makes no claim of right.                          
#                                                             
# Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR> 
#
#
# 
# Module Name:
#   
#     TestCase.tcl
#     
# Abstract:
# 
#     Implementation for EMS Remote Exection function
#

if {[info exist CATEGORYTREE_TCL] == 1} {
  return
}
set CATEGORYTREE_TCL 1

set CategoryTestCaseFullNameList {}
set CategoryTestCaseNameList     {}
set CategoryTestCaseGuidList     {}

# 
# Routine Description:
# 
#   Build a category tree
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsCategoryTreeBuild {} {
  global Tree_Node CategoryTestCaseFullNameList 
  global CategoryTestCaseNameList CategoryTestCaseGuidList

  set CASE_TREE_NODE_MAGIC "\[Test Node\]"

  if {[catch {open "CaseTree.ini" r} ifile]} {
    EmsGuiError "Can not open CaseTree.ini"
    return
  }

  TreeRootInit "RemoteExecution"
  set CategoryTestCaseFullNameList {}
  set CategoryTestCaseNameList {}
  set CategoryTestCaseGuidList {}

  fconfigure $ifile -encoding unicode

  # unicode file header is 0xFEFF 
  if { [string compare [read $ifile 1] "\ufeff"]!=0} {
    fconfigure $ifile -encoding ascii
  } 
  
  while {[gets $ifile magic] >= 0} {
    if {[string compare [GetValidString $magic] $CASE_TREE_NODE_MAGIC] != 0} {
      continue
	}
    set Revision    [lindex [split [gets $ifile] "="] 1]
    set Guid        [lindex [split [gets $ifile] "="] 1]
    set Name        [lindex [split [gets $ifile] "="] 1]
    set Type        [lindex [split [gets $ifile] "="] 1]
    set Description [lindex [split [gets $ifile] "="] 1]

    regsub -all {\\} $Name ":" TreeNode_Name
    if {$Type == 0x01} {
      TreeNodeInit RemoteExecution:${TreeNode_Name}
    } else {
      TreeLeafInit RemoteExecution:${TreeNode_Name}
      lappend CategoryTestCaseFullNameList			                RemoteExecution:${TreeNode_Name}
      lappend CategoryTestCaseNameList                              [GetCaseName ${TreeNode_Name}]
      lappend CategoryTestCaseGuidList                              $Guid
    }
    set Tree_Node(RemoteExecution:${TreeNode_Name}:Revision)      $Revision
    set Tree_Node(RemoteExecution:${TreeNode_Name}:Guid)          $Guid
    set Tree_Node(RemoteExecution:${TreeNode_Name}:Type)          $Type
    set Tree_Node(RemoteExecution:${TreeNode_Name}:Description)   $Description
    TreeNodeAdd [GetCasePath "RemoteExecution:${TreeNode_Name}"] [GetCaseName "RemoteExecution:${TreeNode_Name}"]
  }
  close $ifile
}

# 
# Routine Description:
# 
#   Build EMS GUI category frames
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsGuiFramesCategoryBuild {} {
  global GuiFrames GuiBoxs GuiCursors GuiColors
  set Name $GuiFrames(category)
  frame $Name -background $GuiColors(background) -borderwidth 0 -relief groove
  $GuiFrames(top) add $Name -minsize 2i -before $GuiFrames(testcase)
  set Name $GuiBoxs(category)
  canvas $Name -relief sunken  \
        -borderwidth 1 -width 10 -height 20 \
        -xscrollcommand "$GuiFrames(category).hs set" \
        -yscrollcommand "$GuiFrames(category).vs set" \
        -background $GuiColors(category_box_background) \
        -cursor $GuiCursors(default)
  scrollbar $GuiFrames(category).hs -orient horizontal -command "$Name xview"
  scrollbar $GuiFrames(category).vs -orient vertical -command "$Name yview"
  pack $GuiFrames(category).hs -side bottom -fill x
  pack $GuiFrames(category).vs -side right -fill y
  pack $GuiBoxs(category) -expand yes -fill both
}

# 
# Routine Description:
# 
#   Load RemoteExecution sequenece file
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc LoadRemoteExecutionSequence {} {
  global Tree_Node GuiBoxs
  global CategoryTestCaseFullNameList CategoryTestCaseGuidList

  set SEQ_DATA_MAGIC "\[Test Case\]"

  set types {
    {{ENTS sequence file} {.seq}}
    {{All file}           {*.*}}
  }

  set FileName [tk_getOpenFile -filetypes $types]
  if {$FileName == ""} {
    return
  }

  TreeNodeStateCleanup "RemoteExecution"

  if [catch {open $FileName r} ifile] {
    EmsGuiError "Can not open %s: $FileName"
    return
  }
  while {[gets $ifile magic] >= 0} {
    if {[string compare $magic $SEQ_DATA_MAGIC]} {
      continue
    }
    set Revision    [lindex [split [gets $ifile] "="] 1]
    set Guid        [lindex [split [gets $ifile] "="] 1]
    set Name        [lindex [split [gets $ifile] "="] 1]
    set Order       [lindex [split [gets $ifile] "="] 1]
    set Iterations  [lindex [split [gets $ifile] "="] 1]

    set idx [lsearch -exact $CategoryTestCaseGuidList $Guid]
    set FullName [lindex $CategoryTestCaseFullNameList $idx]
    if {$Order != 0xFFFFFFFF} {
      set Tree_Node(${FullName}:ChosenStatxe)  1
      set Tree_Node(${FullName}:Count)        $Iterations
      TreeNodeChangeChosenState $GuiBoxs(category) "${FullName}" 1
    }
  }
  close $ifile

  TestCaseWindowFlush
  FlushWindow $GuiBoxs(category) "RemoteExecution"
}

# 
# Routine Description:
# 
#   Generate RemoteExecution sequence file
# 
# Arguments:
# 
#   ofile - The output file
# 
# Returns:
# 
#   None.
# 
proc GenerateRemoteExecutionSequence {ofile} {
  global Tree_Node
  global CategoryTestCaseFullNameList CategoryTestCaseNameList

  set SEQ_DATA_MAGIC "\[Test Case\]"
  
  set order 0
  for {set i 0} {$i < [llength $CategoryTestCaseNameList]} {incr i} {
    puts $ofile $SEQ_DATA_MAGIC
    puts $ofile [format "Revision=0x%x" $Tree_Node([lindex $CategoryTestCaseFullNameList $i]:Revision)]
    puts $ofile [format "Guid=%s" $Tree_Node([lindex $CategoryTestCaseFullNameList $i]:Guid)]
    puts $ofile [format "Name=%s" [lindex $CategoryTestCaseNameList $i]]
    if {$Tree_Node([lindex $CategoryTestCaseFullNameList $i]:ChosenState)} {
      puts $ofile [format "Order=0x%d" $order]
      puts $ofile [format "Iterations=0x%s" $Tree_Node([lindex $CategoryTestCaseFullNameList $i]:Count)]
      incr order
    } else {
      puts $ofile [format "Order=%s" 0xFFFFFFFF]
      puts $ofile [format "Iterations=%s" 0xFFFFFFFF]
    }
  }
}

# 
# Routine Description:
# 
#   Save RemoteExecution Sequence file
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc SaveRemoteExecutionSequence {} {
  set types {
    {{ENTS sequence file} {.seq}}
    {{All file}           {*.*}}
  }
  set FileName [tk_getSaveFile -filetypes $types -defaultextension seq]
  if {$FileName == ""} {return}
  if {[file exists $FileName]} {
    if {![file writable $FileName]} {
      EmsGuiError "File \[$FileName\] is not writable."
      return
    }
  }
  if [catch {open $FileName w} ofile] {
    puts stderr "Can not open %s: $FileName"
    return
  }
  GenerateRemoteExecutionSequence $ofile
  close $ofile
}

# 
# Routine Description:
# 
#   Start the remoteExecution test
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionTestStart {} {
  global _ENTS

  if {[TclTargetCleanup [GetTargetMac]] != "OK"} {
    EmsGuiError "The target machine is not active!"
    return
  }

  if [catch {open "TempSeq.seq" w} ofile] {
    puts stderr "Can not open %s: TempSeq"
	return
  }
  GenerateRemoteExecutionSequence $ofile
  close $ofile
  set _ENTS(RunningFlag) 1

  EmsThreadCmd "GetFile \"TempSeq.seq\";Exec \"cp -q \\\\TempSeq.seq \\\\sct\\\\Sequence \";Exec \"Del -q \\\\TempSeq.seq\";Exec \"sct -s TempSeq.seq -p $_ENTS(communication_type) -f\"" -1

  set _ENTS(DefaultStatus) $_ENTS(init_status)
  EmsShowStatus $_ENTS(DefaultStatus)
}

# 
# Routine Description:
# 
#   Continue the RemoteExecution test
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionTestContinue {} {
  tk_messageBox -type ok -message "Remote execution test does not support continue run"
}

proc RemoteExecutionTestReport {} {
  global _ENTS

  if {[file exists RemoteExectionReport.csv]} {
    file delete RemoteExectionReport.csv
  }

  EmsThreadCmd "Exec \"sct -g RemoteExectionReport.csv -p $_ENTS(communication_type)\";Exec \"cp -q \\\\SCT\\\\Report\\\\RemoteExectionReport.csv \\\\ \";PutFile \"RemoteExectionReport.csv\"; Exec \"Del -q \\\\RemoteExectionReport.csv \"" -1

  set Timeout 0
  while {[EmsTestIsRunning] == 1 && $Timeout < 200} {
    after 2000
    incr Timeout
  }

  if {[EmsTestIsRunning] != 1} {
    catch {file copy -force RemoteExectionReport.csv Report}
	catch {file delete -force RemoteExectionReport.csv}
    tk_messageBox -type ok -message "The RemoteExectionReport.csv Download ready"
    return
  }
  EmsGuiError "Can not get report file from remote machine"
}

# 
# Routine Description:
# 
#   Reload the RemoteExecution case tree
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionReload {} {
  global EmsGetRemoteCaseTree EmsActiveLeftFrame

  set EmsGetRemoteCaseTree    0
  set EmsActiveLeftFrame      ""
  CmdActiveRemoteExecutionFrame
}

# 
# Routine Description:
# 
#   Get the RemoteExecution tree node accroding to GUID
# 
# Arguments:
# 
#   Guid - GUID string
# 
# Returns:
# 
#   Return the RemoteExecution tree node
# 
proc GuidToRemoteExecutionTreeNode {Guid} {
  global Tree_Node CategoryTestCaseFullNameList CategoryTestCaseGuidList

  set idx [lsearch -exact $CategoryTestCaseGuidList $Guid]
  return [lindex $CategoryTestCaseFullNameList $idx]
}

# 
# Routine Description:
# 
#   Set the RemoteExecution tree node result "Running"
# 
# Arguments:
# 
#   Guid - GUID string
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionSetResultBegin {Guid} {
  global Tree_Node GuiColors GuiBoxs

  set Path [GuidToRemoteExecutionTreeNode ${Guid}]
  set Tree_Node(${Path}:Result) "Running"
  set Tree_Node(${Path}:ResultForeground)    $GuiColors(case_result_foreground_normal)
  $GuiBoxs(testcase).result${Path} configure -foreground $Tree_Node(${Path}:ResultForeground)
}

# 
# Routine Description:
# 
#   Set the RemoteExecution tree node result value when case run finished
# 
# Arguments:
# 
#   Guid   - GUID string
#   Result - The result of the case
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionSetResultEnd {Guid Result} {
  global Tree_Node GuiBoxs GuiColors

  set Path [GuidToRemoteExecutionTreeNode ${Guid}]
  set Tree_Node(${Path}:Result) $Result
  if {[ResultHasFail $Result]} {
    set Tree_Node(${Path}:ResultForeground)  $GuiColors(case_result_foreground_fail)
  } elseif {[ResultHasWarn $Result]} {
    set Tree_Node(${Path}:ResultForeground)  $GuiColors(case_result_foreground_warn)
  } else {
    set Tree_Node(${Path}:ResultForeground)  $GuiColors(case_result_foreground_pass)
  }
  $GuiBoxs(testcase).result${Path} configure -foreground $Tree_Node(${Path}:ResultForeground)
}

# 
# Routine Description:
# 
#   Edit RemoteExecution case
# 
# Arguments:
# 
#   Path - The case path
# 
# Returns:
# 
#   None.
# 
proc RemoteExecutionEditTestCase {Path} {
  tk_messageBox -type ok -message "can not edit the Remote Execution test cases"
}
