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
#     Protocols.tcl
#     
# Abstract:
# 
#     Implementation for EMS Remote Validation functions
#

if {[info exist PROTOCOL_TCL] == 1} {
  return
}
set PROTOCOL_TCL 1

set ProtocolTestCaseFullNameList {}
set ProtocolTestCasePathList     {}

# 
# Routine Description:
# 
#   Build RemoteValidation GUI frames
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsGuiFramesProtocolBuild {} {
  global GuiFrames GuiBoxs GuiCursors GuiColors
  set Name $GuiFrames(protocol)
  frame $Name -background $GuiColors(background) -borderwidth 0 -relief groove
  $GuiFrames(top) add $Name -minsize 2i -before $GuiFrames(testcase)
  set Name $GuiBoxs(protocol)
  canvas $Name -relief sunken \
        -borderwidth 1 -width 10 -height 20 \
		-xscrollcommand "$GuiBoxs(protocol).hs set" \
		-yscrollcommand "$GuiBoxs(protocol).vs set" \
		-background $GuiColors(protocol_box_background) \
		-cursor $GuiCursors(default)
  scrollbar  $GuiBoxs(protocol).vs -command "$Name yview" -orient vertical
  scrollbar  $GuiBoxs(protocol).hs -command "$Name xview" -orient horizontal
  pack $GuiBoxs(protocol).vs -side right  -fill y
  pack $GuiBoxs(protocol).hs -side bottom -fill x
  pack $GuiBoxs(protocol) -fill both -expand yes
}

# 
# Routine Description:
# 
#   Load test cases accroding to protocol
# 
# Arguments:
# 
#   protocol - protocol name
# 
# Returns:
# 
#   None.
# 
proc LoadTestCasesByProtocol {protocol} {
  global Tree_Node _ENTS
  global ProtocolTestCaseFullNameList ProtocolTestCasePathList
  set files [lsort -dictionary [glob -nocomplain [file join $_ENTS(case_root) $protocol *.tcl] ]]
  foreach file $files {
    set ff [file tail $file]
    if {$ff != "." && $ff != ".."} {
      if {[file isdirectory $file]} {
      } elseif {[string match -nocase *conf* $file ] || [string match -nocase *func* $file ]} {
        set Temp [file root $ff]
        regsub -all {\.} $Temp "_" Name
        TreeLeafInit "RemoteValidation:${protocol}:${Name}"
        lappend ProtocolTestCaseFullNameList                 RemoteValidation:${protocol}:${Name}
		lappend ProtocolTestCasePathList                     [file join $_ENTS(case_root) ${protocol} $ff]
		TreeNodeAdd "RemoteValidation:${protocol}" $Name
	  }
	}
  }
}

# 
# Routine Description:
# 
#   Build EMS RemoteValidation tree
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc EmsProtocolTreeBuild {} {
  global Tree_Node EmsProtocols ProtocolTestCaseFullNameList ProtocolTestCasePathList
  global _ENTS
  TreeRootInit "RemoteValidation"
  set ProtocolTestCaseFullNameList {}
  set ProtocolTestCasePathList {}
  set TestCaseDIRList [glob -directory $_ENTS(case_root) *]
  set EmsProtocols {}
  foreach TestCaseDIR $TestCaseDIRList {
	set TclFileList [glob -nocomplain [file join $TestCaseDIR *.tcl]]
	foreach TclFile $TclFileList {
	  set TclFileName [file tail $TclFile]
	  if {[string match -nocase *case* $TclFileName]} {
	    set TestCaseDIRName [file tail $TestCaseDIR]
		lappend EmsProtocols $TestCaseDIRName
		break
      }	
	}
  }
  foreach protocol $EmsProtocols {
	TreeNodeInit "RemoteValidation:${protocol}"
    TreeNodeAdd RemoteValidation ${protocol}
	LoadTestCasesByProtocol ${protocol}
  }
}

# 
# Routine Description:
# 
#   Load RemoteValidation Sequence file
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc LoadRemoteValidationSequence {} {
  global Tree_Node GuiBoxs
  global ProtocolTestCaseFullNameList ProtocolTestCasePathList

  set SEQ_DATA_MAGIC {[Test Case]}

  set types {
    {{ENTS sequence file} {.seq}}
    {{All file}           {*.*}}
  }

  set FileName [tk_getOpenFile -filetypes $types]
  if {$FileName == ""} {
    return
  }

  TreeNodeStateCleanup "RemoteValidation"

  if [catch {open $FileName r} ifile] {
    EmsGuiError "Can not open %s: $FileName"
    return
  }
  fconfigure $ifile -encoding unicode
  while {[gets $ifile magic] >= 0} {
    if {[string compare $magic $SEQ_DATA_MAGIC]} {
      continue
    }
    set Revision    [lindex [split [gets $ifile] "="] 1]
    set Guid        [lindex [split [gets $ifile] "="] 1]
    set FullName    [lindex [split [gets $ifile] "="] 1]
    set Order       [lindex [split [gets $ifile] "="] 1]
    set Iterations  [lindex [split [gets $ifile] "="] 1]

    set idx [lsearch -exact $ProtocolTestCaseFullNameList $FullName]
    if {$Order != 0xFFFFFFFF} {
      set Tree_Node(${FullName}:ChosenState)  1
      set Tree_Node(${FullName}:Count)        $Iterations
      TreeNodeChangeChosenState $GuiBoxs(protocol) "${FullName}" 1
    }
  }
  close $ifile

  TestCaseWindowFlush
  FlushWindow $GuiBoxs(protocol) "RemoteValidation"
}

# 
# Routine Description:
# 
#   Save the RemoteValidation Sequence file
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc SaveRemoteValidationSequence {} {
  global Tree_Node
  global ProtocolTestCaseFullNameList ProtocolTestCasePathList

  set SEQ_DATA_MAGIC {[Test Case]}

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

  set order 0
  if [catch {open $FileName w} ofile] {
    puts stderr "Can not open %s: $FileName"
    return
  }
  fconfigure $ofile -encoding unicode
  for {set i 0} {$i < [llength $ProtocolTestCaseFullNameList]} {incr i} {
    set FullName [lindex $ProtocolTestCaseFullNameList $i]
    puts $ofile $SEQ_DATA_MAGIC
    puts $ofile [format "Revision=%x" $Tree_Node(${FullName}:Revision)]
    puts $ofile [format "Guid=%s" $Tree_Node(${FullName}:Guid)]
    puts $ofile [format "Name=%s" ${FullName}]
    if {$Tree_Node(${FullName}:ChosenState)} {
      incr order
      puts $ofile [format "Order=%d" $order]
      puts $ofile [format "Iterations=%s" $Tree_Node(${FullName}:Count)]
    } else {
      puts $ofile [format "Order=%s" 0xFFFFFFFF]
      puts $ofile [format "Iterations=%s" 0xFFFFFFFF]
    }
  }
  close $ofile
}

# 
# Routine Description:
# 
#   Start the RemoteValidation test
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationTestStart {} {
  global _ENTS Tree_Node
  global ProtocolTestCaseFullNameList ProtocolTestCasePathList

  EmsOutputHighLight "Run test case on target [GetTargetMac]\n"

  EmsRemoteValidationTestStart
  for {set idx 0} {$idx < [llength $ProtocolTestCaseFullNameList]} {incr idx} {
    set FullName [lindex $ProtocolTestCaseFullNameList $idx]
    set Path     [lindex $ProtocolTestCasePathList $idx]
    if {$Tree_Node(${FullName}:ChosenState)} {
      set _ENTS(ExecuteFile) $Path
      set _ENTS(DefaultStatus) "Running $_ENTS(ExecuteFile)"
      EmsShowStatus $_ENTS(DefaultStatus)
      for {set c 1} {$c <= $Tree_Node(${FullName}:Count)} {incr c} {
        EmsTestCaseScriptEval $_ENTS(ExecuteFile) $FullName
      }
	}
  }
  RemoteValidationTestCaseAllPost

  set _ENTS(DefaultStatus) $_ENTS(init_status) 
  EmsShowStatus $_ENTS(DefaultStatus)
}

# 
# Routine Description:
# 
#   Continue the RemoteValidation test
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationTestContinue {} {
  EmsOutputHighLight "Continue run test case on target [GetTargetMac]\n"
  EmsRemoteValidationTestContinue
}

# 
# Routine Description:
# 
#   Set the RemoteValidation tree node result "Running" at 
#   the beginning of test
# 
# Arguments:
# 
#   FullName - The name of the case
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationSetResultBegin {FullName} {
  global Tree_Node GuiBoxs GuiColors

  set Tree_Node(${FullName}:Result)              "Running"
  set Tree_Node(${FullName}:ResultForeground)    $GuiColors(case_result_foreground_normal)
  $GuiBoxs(testcase).result$FullName configure -foreground $Tree_Node(${FullName}:ResultForeground)
}

# 
# Routine Description:
# 
#   Set the RemoteValidation tree node result at 
#   the end of test
# 
# Arguments:
# 
#   FullName - The name of the case
#   Result   - The result of the case 
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationSetResultEnd {FullName Result} {
  global Tree_Node GuiBoxs GuiColors

  set Tree_Node(${FullName}:Result)              $Result
  if {$Result == "Case Error"} {
    EmsRemoteValidationTestStop
    set Tree_Node(${FullName}:ResultForeground)  $GuiColors(case_result_foreground_error)
  } else {
    if {[ResultHasFail $Result]} {
      set Tree_Node(${FullName}:ResultForeground)  $GuiColors(case_result_foreground_fail)
	} elseif {[ResultHasWarn $Result]} {
      set Tree_Node(${FullName}:ResultForeground)  $GuiColors(case_result_foreground_warn)
	} else {
      set Tree_Node(${FullName}:ResultForeground)  $GuiColors(case_result_foreground_pass)
	}
  }
  $GuiBoxs(testcase).result$FullName configure -foreground $Tree_Node(${FullName}:ResultForeground)
}

# 
# Routine Description:
# 
#   Generate RemoteValidation test report
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationTestReport {} {
  set ReportFileName [clock format [clock seconds] -format %Y-%m-%d-%H-%M-%S -gmt false ]
  GenerateReport $ReportFileName
}

# 
# Routine Description:
# 
#   Edit RemoteValidation case
# 
# Arguments:
# 
#   String - The string of case
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationEditTestCase {String} {
  global _ENTS EmsFiles

  set Path [GetCaseRoot [GetCasePathName $String]]
  set Name [GetCaseName $String]
  regsub -all ":" $Path {/} CasePath
  regsub -all "_" $Name "." CaseName
  set EmsFiles(current) [file join $_ENTS(case_root) $CasePath $CaseName.tcl]
  EmsEditForm
}

# 
# Routine Description:
# 
#   Reload the RemoteValidation case window
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc RemoteValidationReload {} {
  global EmsGetRemoteValidationCaseTree EmsActiveLeftFrame

  set EmsGetRemoteValidationCaseTree   0
  set EmsActiveLeftFrame      ""
  CmdActiveRemoteValidationFrame
}

