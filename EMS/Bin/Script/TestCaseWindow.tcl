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
#     TestCaseWindow.tcl
#     
# Abstract:
# 
#     Implementation for EMS test case window functions
#

if {[info exist TESTCASEWINDOW_TCL] == 1} {
  return
}
set TESTCASEWINDOW_TCL 1

# 
# Routine Description:
# 
#   Initialize the test case window
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsTestCaseWindowInit {} {
  global Tree_Node GuiBoxs GuiColors

  $GuiBoxs(testcase) configure -state normal
  $GuiBoxs(testcase) delete 1.0 end

  checkbutton $GuiBoxs(testcase).cb \
      -relief flat -background $GuiColors(testcase_box_background) \
      -font EmsTestCaseTitleFont \
      -borderwidth 0 -padx 0 -pady 0 -state disabled
  $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).cb

  label $GuiBoxs(testcase).name  \
      -background $GuiColors(testcase_box_background) \
      -anchor w -text "Case Name" -relief flat  \
      -width 40 -font EmsTestCaseTitleFont
  $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).name

  label $GuiBoxs(testcase).count  \
      -background $GuiColors(testcase_box_background) \
      -width 5 -relief flat -font EmsTestCaseTitleFont \
      -text "Count"
  $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).count

  label $GuiBoxs(testcase).result  \
      -background $GuiColors(testcase_box_background) \
      -anchor e -text Result  \
      -relief flat  \
      -width 32 -font EmsTestCaseTitleFont
  $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).result

  $GuiBoxs(testcase) insert end \n
  $GuiBoxs(testcase) configure -state disabled
}

# 
# Routine Description:
# 
#   Show the test cases in window
# 
# Arguments:
# 
#   path - The path of the case
# 
# Returns:
# 
#   None.
# 
proc EmsTestCaseWindowShow {path} {
  global _ENTS Tree_Node GuiBoxs GuiColors EmsLeftWindow

  TestCaseWindowCleanup

  $GuiBoxs(testcase) insert end \n
  foreach c $Tree_Node(${path}:Children) {
    regsub -all {\.} ${c} "_" temp_testcase

    checkbutton $GuiBoxs(testcase).cb$temp_testcase \
        -variable Tree_Node(${path}:${c}:ChosenState) \
        -command "CmdTreeNodeChangeChosenState $EmsLeftWindow {${path}:${c}}; FlushWindow $EmsLeftWindow [GetCaseRoot ${path}:${c}]" \
        -relief flat -background $GuiColors(testcase_box_background) \
        -font EmsTestCaseFont -indicatoron 1 \
        -borderwidth 0 -padx 0 -pady 0
    $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).cb$temp_testcase

    label $GuiBoxs(testcase).name$temp_testcase  \
        -background $GuiColors(testcase_box_background) \
        -anchor w -text $c -relief flat  \
        -width 40 -font EmsTestCaseFont
    $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).name$temp_testcase
	bind $GuiBoxs(testcase).name$temp_testcase <Double-Button-1> "CmdEmsEditForm {${path}:${c}}"

    spinbox $GuiBoxs(testcase).count$temp_testcase       \
        -from 1 -to 1000 -increment 1  -justify right \
        -background $GuiColors(testcase_box_background) \
        -width 5 -relief groove -font Ems_basic_font  \
        -state readonly \
        -textvariable Tree_Node(${path}:${c}:Count)
    $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).count$temp_testcase

    label $GuiBoxs(testcase).result${path}:${c}  \
        -background $GuiColors(testcase_box_background) \
        -anchor e -textvariable Tree_Node(${path}:${c}:Result) \
        -relief flat  \
        -width 32 -font EmsTestCaseFont \
		-foreground $Tree_Node(${path}:${c}:ResultForeground)
    $GuiBoxs(testcase) window create end -window $GuiBoxs(testcase).result${path}:${c}

    $GuiBoxs(testcase) insert end \n
  }
  $GuiBoxs(testcase) configure -state disabled
}

# 
# Routine Description:
# 
#   Cleanup the EMS test case window
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc TestCaseWindowCleanup {} {
  global GuiBoxs
  $GuiBoxs(testcase) configure -state normal
  $GuiBoxs(testcase) delete 2.0 end
}

# 
# Routine Description:
# 
#   refresh the EMS test case window
# 
# Arguments:
# 
#   None
# 
# Returns:
# 
#   None.
# 
proc TestCaseWindowFlush {} {
  global TreeNodeSelected
  if {$TreeNodeSelected != ""} {
    EmsTestCaseWindowShow $TreeNodeSelected
  }
}
