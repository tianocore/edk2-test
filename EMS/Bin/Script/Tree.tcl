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
#     Implementation for EMS test case tree functions
#

if {[info exist TREE_TCL] == 1} {
  return
}
set TREE_TCL 1

proc DEBUG {str} { tk_messageBox -message $str -type ok }
#################################################################
set maskdata "#define solid_width 9\n#define solid_height 9"
append maskdata {
  static unsigned char solid_bits[] = {
   0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01, 0xff, 0x01,
   0xff, 0x01, 0xff, 0x01, 0xff, 0x01
  };
}
set data "#define open_width 9\n#define open_height 9"
append data {
  static unsigned char open_bits[] = {
   0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x7d, 0x01, 0x01, 0x01,
   0x01, 0x01, 0x01, 0x01, 0xff, 0x01
  };
}
image create bitmap Tree_Unwrap_Image -data $data -maskdata $maskdata \
  -foreground black -background white
set data "#define closed_width 9\n#define closed_height 9"
append data {
  static unsigned char closed_bits[] = {
   0xff, 0x01, 0x01, 0x01, 0x11, 0x01, 0x11, 0x01, 0x7d, 0x01, 0x11, 0x01,
   0x11, 0x01, 0x01, 0x01, 0xff, 0x01
  };
}
image create bitmap Tree_Wrap_Image -data $data -maskdata $maskdata \
  -foreground black -background white

set icminidir "./Script/Image/MiniDir.bmp"
set ChosenN "./Script/Image/ChosenN.bmp"
set ChosenY "./Script/Image/ChosenY.bmp"

set TreeNodeSelected ""

# 
# Routine Description:
# 
#   Get the test case's name
# 
# Arguments:
# 
#   string - The input string
# 
# Returns:
# 
#   case's name
# 
proc GetCaseName {String} {
  set mid [string last ":" $String]
  if {$mid == -1} { return ""}
  set name [string range $String [expr $mid + 1] end]
  return $name
}

# 
# Routine Description:
# 
#   Get the test case's path
# 
# Arguments:
# 
#   string - The input string
# 
# Returns:
# 
#   case's path
# 
proc GetCasePath {String} {
  set mid [string last ":" $String]
  if {$mid == -1} {return $String}
  set path [string range $String 0 [expr $mid - 1]]
  return $path
}

# 
# Routine Description:
# 
#   Get the test case's root
# 
# Arguments:
# 
#   String - The input string
# 
# Returns:
# 
#   The root of the case
# 
proc GetCaseRoot {String} {
  set mid [string first ":" $String]
  if {$mid == -1} {return $String}
  set path [string range $String 0 [expr $mid - 1]]
  return $path
}

# 
# Routine Description:
# 
#   Get the test case's path name
# 
# Arguments:
# 
#   string - The input string
# 
# Returns:
# 
#   The path name of the case
# 
proc GetCasePathName {String} {
  set mid [string first ":" $String]
  if {$mid == -1} {return ""}
  set name [string range $String [expr $mid + 1] end]
  return $name
}

# 
# Routine Description:
# 
#   Initialize the root of case tree
# 
# Arguments:
# 
#   Root - The root of tree
# 
# Returns:
# 
#   None.
# 
proc TreeRootInit {Root} {
  global Tree_Node

  set Tree_Node(${Root}:Revision)    0
  set Tree_Node(${Root}:Guid)        0
  set Tree_Node(${Root}:Description) ""
  set Tree_Node(${Root}:Type)        0x01
  set Tree_Node(${Root}:ChosenState) 0
  set Tree_Node(${Root}:Children)    {}
  set Tree_Node(${Root}:Unwrap)      0
  set Tree_Node(${Root}:Font)        EmsTreeNodeSelectNFont
}

# 
# Routine Description:
# 
#   Initialize the Node of case tree
# 
# Arguments:
# 
#   Node - The node of tree
# 
# Returns:
# 
#   None.
# 
proc TreeNodeInit {node} {
  global Tree_Node

  set Tree_Node(${node}:Type)                 0x01
  set Tree_Node(${node}:Revision)             0
  set Tree_Node(${node}:Guid)                 0
  set Tree_Node(${node}:Description)          ""
  set Tree_Node(${node}:ChosenState)          0
  set Tree_Node(${node}:Font)                 EmsTreeNodeSelectNFont
  set Tree_Node(${node}:Unwrap)               0
  set Tree_Node(${node}:Children)             {}
}

# 
# Routine Description:
# 
#   Initialize the leaf of case tree
# 
# Arguments:
# 
#   leaf - The leaf of tree
# 
# Returns:
# 
#   None.
# 
proc TreeLeafInit {leaf} {
  global Tree_Node GuiColors

  set Tree_Node(${leaf}:Type)                 0x02
  set Tree_Node(${leaf}:Revision)             0
  set Tree_Node(${leaf}:Guid)                 0
  set Tree_Node(${leaf}:Description)          ""
  set Tree_Node(${leaf}:ChosenState)          0
  set Tree_Node(${leaf}:Count)                1
  set Tree_Node(${leaf}:Font)                 EmsTreeNodeSelectNFont
  set Tree_Node(${leaf}:Result)               "Not started"
  set Tree_Node(${leaf}:ResultForeground)     $GuiColors(case_result_foreground_normal)
}

# 
# Routine Description:
# 
#   Add the tree node to its parent's child list
# 
# Arguments:
# 
#   Parent   - The Parent of the tree node
#   NodeName - The name of the tree node
# 
# Returns:
# 
#   None.
# 
proc TreeNodeAdd {Parent NodeName} {
  global Tree_Node
  lappend Tree_Node(${Parent}:Children) ${NodeName}
}

# 
# Routine Description:
# 
#   Cleanup the window of case tree
# 
# Arguments:
# 
#   win - The case tree window
# 
# Returns:
# 
#   None.
# 
proc WindowCleanup {win} {
  global GuiBoxs
  $win delete all
}

# 
# Routine Description:
# 
#   Initialize the coordinates of the case tree window
# 
# Arguments:
# 
#   win - The case tree window
# 
# Returns:
# 
#   None.
# 
proc InitCoordinates {win} {
  global GuiBoxs
  set GuiBoxs($win:X) 10
  set GuiBoxs($win:Y) 10
}

# 
# Routine Description:
# 
#   refresh the case tree window
# 
# Arguments:
# 
#   win  - The case tree window
#   Root - The root of the case tree
# 
# Returns:
# 
#   None.
# 
proc FlushWindow {win Root} {
  global GuiBoxs Tree_Node
  WindowCleanup $win
  InitCoordinates $win
  TreeShow $win $Root
}

# 
# Routine Description:
# 
#   The callback function of the command of refreshing case tree window
# 
# Arguments:
# 
#   win  - The case tree window
#   path - the path of the input case
# 
# Returns:
# 
#   None.
# 
proc CmdFlushWindow {win path} {
  if {[EmsWaitForMutex] == -1} {
    return
  }
  FlushWindow $win [GetCaseRoot ${path}]
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   The callback function of the command of selecting a test case
# 
# Arguments:
# 
#   win  - The case tree window
#   path - the path of the case selected
# 
# Returns:
# 
#   None.
# 
proc CmdTreeNodeSelection {win path} {
  global Tree_Node
  global TreeNodeSelected

  if {[EmsWaitForMutex] == -1} {
    return
  }

  set Tree_Node(${TreeNodeSelected}:Font) EmsTreeNodeSelectNFont
  if {[llength $Tree_Node(${path}:Children)] != 0} {
    set child [lindex $Tree_Node(${path}:Children) 0]
    if {$Tree_Node(${path}:${child}:Type) == 0x02} {
      set Tree_Node(${path}:Font) EmsTreeNodeSelectYFont
      if {${path} != $TreeNodeSelected} {
        set TreeNodeSelected ${path}
        EmsTestCaseWindowShow ${path}
	  }
      FlushWindow $win [GetCaseRoot ${path}]
      EmsReleaseMutex
	  return
    }
  }
  set TreeNodeSelected ""
  TestCaseWindowCleanup
  FlushWindow $win [GetCaseRoot ${path}]
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   Change the chosen state of all the case's child node 
# 
# Arguments:
# 
#   path - The path of the input case
#   val  - The new chosen state
# 
# Returns:
# 
#   None.
# 
proc TreeNodeChangeChosenStateDown {path val} {
	global Tree_Node
	set Tree_Node(${path}:ChosenState) $val
	if {$Tree_Node(${path}:Type) == 0x01} {
		foreach n $Tree_Node(${path}:Children) {
			TreeNodeChangeChosenStateDown "${path}:${n}" $val
		}
	}
}

# 
# Routine Description:
# 
#   Change the chosen state of all the case's parent node
# 
# Arguments:
# 
#   path - The path of the input case
#   val  - The new chosen state
# 
# Returns:
# 
#   None.
# 
proc TreeNodeChangeChosenStateUp {path val} {
  global Tree_Node

  set parent [GetCasePath "${path}"]
  if {${parent} == ""} {
    return
  }
  if {$Tree_Node(${parent}:ChosenState) == 0 && $val == 1} {
    set Tree_Node(${parent}:ChosenState) $val
    TreeNodeChangeChosenStateUp "${parent}" $val
  }
  if {$Tree_Node(${parent}:ChosenState) == 1 && $val == 0} {
    foreach child $Tree_Node(${parent}:Children) {
      if {$Tree_Node(${parent}:${child}:ChosenState) == 1} {
        return
      }
	}
    set Tree_Node(${parent}:ChosenState) $val
    TreeNodeChangeChosenStateUp "${parent}" $val
  }
}

# 
# Routine Description:
# 
#   Change the chosen state of the case include its parent nodes and child
#   nodes
# 
# Arguments:
# 
#   win  - The window of the case tree
#   path - The path of the input case
#   val  - The new chosen state
# 
# Returns:
# 
#   None.
# 
proc TreeNodeChangeChosenState {win path val} {
  global Tree_Node

  TreeNodeChangeChosenStateDown "${path}" $val
  TreeNodeChangeChosenStateUp "${path}" $val
}

# 
# Routine Description:
# 
#   The callback function of changing case's chosen state
# 
# Arguments:
# 
#   win  - The window fo the case tree
#   path - The path of the case
# 
# Returns:
# 
#   None.
# 
proc CmdTreeNodeChangeChosenState {win path} {
  global Tree_Node

  if {[EmsWaitForMutex] == -1} {
    return
  }
  TreeNodeChangeChosenState $win "${path}" $Tree_Node(${path}:ChosenState)
  EmsReleaseMutex
}

# 
# Routine Description:
# 
#   cleanup the tree node state
# 
# Arguments:
# 
#   Node - The tree node
# 
# Returns:
# 
#   None.
# 
proc TreeNodeStateCleanup {Node} {
  global Tree_Node

  set Tree_Node(${Node}:ChosenState) 0
  if {$Tree_Node(${Node}:Type) == 0x02} {
    set $Tree_Node(${Node}:Count)   1
    set $Tree_Node(${Node}:Result)  "Not started"
  } else {
    foreach n $Tree_Node(${Node}:Children) {
      TreeNodeStateCleanup "${Node}:$n"
    }
  }
}

# 
# Routine Description:
# 
#   Show the case tree
# 
# Arguments:
# 
#   win  - The case tree window
#   path - The path of the case
#   x    - x axis
# 
# Returns:
# 
#   None.
# 
proc __TreeShow {win path x} {
  global Tree_Node GuiBoxs
  global icminidir ChosenY ChosenN

  if {$Tree_Node(${path}:Type) == 0x02} {
    return
  }

  if {[llength $Tree_Node(${path}:Children)] != 0} {
    set child [lindex $Tree_Node(${path}:Children) 0]
    if {$Tree_Node(${path}:${child}:Type) != 0x02} {
      if {$Tree_Node(${path}:Unwrap)} {
        set f [$win create image $x $GuiBoxs($win:Y) -image Tree_Unwrap_Image]
        $win bind $f <1> "set {Tree_Node(${path}:Unwrap)} 0; CmdFlushWindow $win {${path}}"
      } else {
        set f [$win create image $x $GuiBoxs($win:Y) -image Tree_Wrap_Image]
        $win bind $f <1> "set {Tree_Node(${path}:Unwrap)} 1; CmdFlushWindow $win {${path}}"
      }
    }
  }

  incr x 20
  if {$Tree_Node(${path}:ChosenState)} {
    set f [$win create bitmap $x $GuiBoxs($win:Y) -bitmap @[file join $icminidir] -foreground #333333]
    $win bind $f <1> "CmdTreeNodeSelection $win {${path}}"
    $win bind $f <3> "set {Tree_Node(${path}:ChosenState)} 0; CmdTreeNodeChangeChosenState $win {${path}}; TestCaseWindowFlush; FlushWindow $win [GetCaseRoot ${path}]"
    $win bind $f <Double-1> "set {Tree_Node(${path}:Unwrap)} [expr $Tree_Node(${path}:Unwrap) ^ 1]; CmdFlushWindow $win {${path}}"
    incr x 20
    set f [$win create bitmap $x $GuiBoxs($win:Y) -bitmap @[file join $ChosenY]]
    $win bind $f <1> "set {Tree_Node(${path}:ChosenState)} 0; CmdTreeNodeChangeChosenState $win {${path}}; TestCaseWindowFlush; FlushWindow $win [GetCaseRoot ${path}]"
  } else {
    set f [$win create bitmap $x $GuiBoxs($win:Y) -bitmap @[file join $icminidir] -foreground #339999]
    $win bind $f <1> "CmdTreeNodeSelection $win {${path}}"
    $win bind $f <3> "set {Tree_Node(${path}:ChosenState)} 1; CmdTreeNodeChangeChosenState $win {${path}}; TestCaseWindowFlush; FlushWindow $win [GetCaseRoot ${path}]"
    $win bind $f <Double-1> "set {Tree_Node(${path}:Unwrap)} [expr $Tree_Node(${path}:Unwrap) ^ 1]; CmdFlushWindow $win {${path}}"
    incr x 20
    set f [$win create bitmap $x $GuiBoxs($win:Y) -bitmap @[file join $ChosenN]]
    $win bind $f <1> "set {Tree_Node(${path}:ChosenState)} 1; CmdTreeNodeChangeChosenState $win {${path}}; TestCaseWindowFlush; FlushWindow $win [GetCaseRoot ${path}]"
  }

  incr x 10
  set Name [GetCaseName "${path}"]
  if {$Name != ""} {
    $win create text $x $GuiBoxs($win:Y) -text $Name -anchor w -font $Tree_Node(${path}:Font)
  } else {
    $win create text $x $GuiBoxs($win:Y) -text [GetCasePath "${path}"] -anchor w -font $Tree_Node(${path}:Font)
  }

  incr GuiBoxs($win:Y) 22
  if {$Tree_Node(${path}:Unwrap)} {
    foreach node $Tree_Node(${path}:Children) {
      __TreeShow $win ${path}:${node} [expr $x - 20]
    }
  }
}

# 
# Routine Description:
# 
#   The hook function for tree window cleanup
# 
# Arguments:
# 
#   Node
# 
# Returns:
# 
#   None.
# 
proc TreeWindowCleanupHook {} {
  global Tree_Node TreeNodeSelected
  set Tree_Node(${TreeNodeSelected}:Font) EmsTreeNodeSelectNFont
  set TreeNodeSelected                    ""
}

# 
# Routine Description:
# 
#   Reset the attribution of the tree window
# 
# Arguments:
# 
#   win - The case tree window
# 
# Returns:
# 
#   None.
# 
proc TreeWindowReset {win} {
  global GuiBoxs
  InitCoordinates $win
  $win delete all
}

# 
# Routine Description:
# 
#   Show the case tree window
# 
# Arguments:
# 
#   win  - The case tree window
#   Root - The root of the case tree
# 
# Returns:
# 
#   None.
# 
proc TreeShow {win Root} {
  global GuiBoxs
  TreeWindowReset $win
  __TreeShow $win ${Root} $GuiBoxs($win:X)
  $win config -scrollregion [$win bbox all]
}

