# 
#  Copyright 2006 - 2011 Unified EFI, Inc.<BR> 
#  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>
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
#     Implementation for EMS About function
#

if {[info exist ABOUT_TCL] == 1} {
  return
}
set ABOUT_TCL 1

# 
# Routine Description:
# 
#   ENTS About form.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdHelpAbout {} {
  global  GuiColors GuiFrames

  catch "destroy .emsAbout"
  toplevel .emsAbout -background LightGray
  wm withdraw .emsAbout
  wm title .emsAbout {About ENTS}

  set Parent .emsAbout
  set Name $Parent.mainwin
  frame $Name -background  $GuiColors(background)  -height 20 -width 80
  pack $Name -anchor nw -side top -fill x -padx 0 -pady 5
  
  set Name $Parent.mainwin.info
  label $Name  -background LightGray -font EmsBasicFont \
               -justify left -text  \
  {  EMS(Efi Management Side for UEFI SCT)
  
  Copyright 2006 - 2017 Unified EFI, Inc.<BR> 
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
 
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
  
  pack $Name -side top -anchor nw

  set Name $Parent.mainwin1
  frame $Name -background lightgray  -height 20 -width 80
  pack $Name -anchor nw -side top -fill x -padx 0 -pady 5
     
  set Name $Parent.mainwin1.btn_close
  button $Name  -activebackground Lavender -background $GuiColors(background) \
        -command {destroy .emsAbout } -foreground $GuiColors(foreground) \
        -highlightbackground LightGray -text close \
        -height 1 -width 10
  pack $Name -anchor ne -side bottom -fill none

  set x [expr [winfo rootx $GuiFrames(main)] + 30]
  set y [expr [winfo rooty $GuiFrames(main)] + 30]
  wm geometry .emsAbout +$x+$y
  wm deiconify .emsAbout
  wm resizable .emsAbout 0 0 
  raise .emsAbout
  update
  wm minsize .emsAbout [winfo width .emsAbout] \
        [winfo height .emsAbout]
  wm maxsize .emsAbout [winfo width .emsAbout] \
        [winfo height .emsAbout]

  focus .emsAbout
  grab  .emsAbout
  tkwait window .emsAbout
}
