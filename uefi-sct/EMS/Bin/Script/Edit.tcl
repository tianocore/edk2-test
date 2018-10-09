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
#     Implementation for EMS Edit form function
#

if {[info exist EDIT_TCL] == 1} {
  return
}
set EDIT_TCL 1

# 
# Routine Description:
# 
#   Load a file into edit box.
# 
# Arguments:
# 
#   The file's name.
# 
# Returns:
# 
#   None.
# 
proc EmsLoadFile { FileName } {
  global EmsFiles GuiBoxs

  if {![file readable "$FileName"]} {
    return
  }
  if {[catch "open \"$FileName\" r" fd]} {
    return
  }
   
  set EmsFiles(package) "[read $fd]"
  close $fd

  set EmsFiles(temppackage) $EmsFiles(package)
  .emsEdit.text_frame.text delete 1.0 end
  .emsEdit.text_frame.text insert end $EmsFiles(temppackage)
  EmsEditHighlight 1.0 end ; # Highlight the keywords

  wm title .emsEdit "edit $EmsFiles(current)"
}

# 
# Routine Description:
# 
#   Popup a OpenFile dialog to open file.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsEditOpen { } {
  global EmsFiles GuiBoxs

  set types {
        {{ENTS test script} {.tcl}}
        {{All file}        {*.*}}
        }

  set EmsFiles(current) [tk_getOpenFile -filetypes $types]
  EmsLoadFile  "$EmsFiles(current)"

}

# 
# Routine Description:
# 
#   Popup a SaveFile dialog to Save file.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsEditSave { } {
  global EmsFiles

  set types {
        {{ENTS test script} {.tcl}}
        {{All file}         {*.*}}
        }
  set TempFile $EmsFiles(current)
  set TempPackage "[.emsEdit.text_frame.text get 1.0 end]"

  if {$TempFile == ""} {return}
  if {[file exists $TempFile]} {
    if {![file writable $TempFile]} {
      EmsGuiError "File \[$TempFile\] is not writable."
      return
    }
  }

  if {[catch "open $TempFile w" fd]} {
    EmsGuiError "Error opening $TempFile):  \[$fd\]"
    return
   }
  puts $fd "$TempPackage"
  close $fd

  wm title .emsEdit "edit $EmsFiles(current)"

  unset TempFile
  unset TempPackage
}

# 
# Routine Description:
# 
#   The main form of Edit.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsEditForm { } {
  global Images
  global GuiColors GuiBoxs GuiFrames
  global EmsFiles

  catch "destroy .emsEdit"

  toplevel .emsEdit  -background $GuiColors(background)
  wm withdraw .emsEdit
  if [info exist EmsFiles(current) ] {
    wm title .emsEdit "edit $EmsFiles(current)"
  } else {
    wm title .emsEdit {edit}
  }

  frame  .emsEdit.button_frame -background $GuiColors(background) -relief raised -border 1 
  pack   .emsEdit.button_frame -side top -fill x

  BuildButton .emsEdit.button_frame.open $Images(load)   "EmsEditOpen" "Load file"  
  BuildButton .emsEdit.button_frame.save $Images(save)   "EmsEditSave" "Save file"  
  BuildButton .emsEdit.button_frame.help $Images(help)   "EmsEditHelp" "Help"  

  bind .emsEdit <Control-s> {EmsEditSave}
  bind .emsEdit <Control-S> {EmsEditSave}

  frame .emsEdit.text_frame
  pack .emsEdit.text_frame -side top -fill x

  text .emsEdit.text_frame.text -wrap none -cursor arrow \
     -width 120 -height 40 -borderwidth 1 \
     -relief raised -setgrid true -font EmsEditFont \
     -xscrollcommand {.emsEdit.text_frame.scrollx set} \
     -yscrollcommand {.emsEdit.text_frame.scrolly set} \
     -background white -selectbackground black \
     -undo 1 
  
  bind .emsEdit.text_frame.text <F1> {
    EmsEditHelp 
  }
  
  bind .emsEdit.text_frame.text <Control-w> {
    if { [.emsEdit.text_frame.text cget -wrap] == "none" } {
      .emsEdit.text_frame.text configure -wrap word
    } else {
      .emsEdit.text_frame.text configure -wrap none
    }
  }
  
  bind .emsEdit.text_frame.text <<Modified>> {
    if [ .emsEdit.text_frame.text edit modified ] {
      .emsEdit.text_frame.text edit modified 0 ;
      set idx "insert"
      set Range [%W tag prevrange gui_edit_tags(rivl_key) $idx]
      set idx "insert lineend "
      if {[llength $Range] == 0} {
        EmsEditHighlight 1.0 $idx
      } else {
        set leftIdx  [lindex $Range 0]
        EmsEditHighlight "$leftIdx -1 line" $idx
      }
    }
  }
 
  scrollbar .emsEdit.text_frame.scrolly -command {.emsEdit.text_frame.text yview} -orient vertical
  scrollbar .emsEdit.text_frame.scrollx -command {.emsEdit.text_frame.text xview} -orient horizontal
  pack .emsEdit.text_frame.scrolly -side right  -fill y
  pack .emsEdit.text_frame.scrollx -side bottom -fill x
  pack .emsEdit.text_frame.text -side left -fill both -expand false
  pack .emsEdit.text_frame -side top -fill both -expand false

  set x [expr [winfo rootx $GuiFrames(main)] + 300]
  set y [expr [winfo rooty $GuiFrames(main)] + [winfo height $GuiFrames(main)] - 300]

  wm geometry .emsEdit +30+30
  wm deiconify .emsEdit
  wm resizable .emsEdit  0 0
  raise .emsEdit
  update

  .emsEdit.text_frame.text tag configure gui_edit_tags(tcl_key)  -foreground Blue       -background white
  .emsEdit.text_frame.text tag configure gui_edit_tags(rivl_key) -foreground red        -background white
  .emsEdit.text_frame.text tag configure gui_edit_tags(tcl_var)  -foreground brown      -background white
  .emsEdit.text_frame.text tag configure gui_edit_tags(rivl_var) -foreground purple     -background white
  .emsEdit.text_frame.text tag configure gui_edit_tags(xdigit)   -foreground red        -background white
  .emsEdit.text_frame.text tag configure gui_edit_tags(comment)  -foreground CadetBlue4 -background white
  .emsEdit.text_frame.text tag raise gui_edit_tags(comment)

  if [info exist EmsFiles(current) ] {
    EmsLoadFile  "$EmsFiles(current)"
  }
}

# 
# Routine Description:
# 
#   The callback funcition of openning a edit form
# 
# Arguments:
# 
#    Start    : The Start of the range
#    End      : The End of the range
# 
# Returns:
# 
#   None.
# 
proc CmdEmsEditForm {Path} {
  global EmsActiveLeftFrame

  switch $EmsActiveLeftFrame {
    "RemoteExecution"    { RemoteExecutionEditTestCase $Path }
    "RemoteValidation"   { RemoteValidationEditTestCase $Path }
  }
}

# 
# Routine Description:
# 
#   Highlight all the keywords in the specified range.
# 
# Arguments:
# 
#    Start    : The Start of the range
#    End      : The End of the range
# 
# Returns:
# 
#   None.
# 
proc EmsEditHighlight { Start End } {
  global RivlKeys TclKeys

  .emsEdit.text_frame.text tag remove gui_edit_tags(tcl_key)   $Start $End 
  .emsEdit.text_frame.text tag remove gui_edit_tags(rivl_key)  $Start $End 
  .emsEdit.text_frame.text tag remove gui_edit_tags(tcl_var)   $Start $End 
  .emsEdit.text_frame.text tag remove gui_edit_tags(rivl_var)  $Start $End 
  .emsEdit.text_frame.text tag remove gui_edit_tags(comment)   $Start $End 
  .emsEdit.text_frame.text tag remove gui_edit_tags(xdigit)    $Start $End 

  EmsEditHighlightKeys .emsEdit.text_frame.text $RivlKeys gui_edit_tags(rivl_key) $Start $End 
  EmsEditHighlightKeys .emsEdit.text_frame.text $TclKeys gui_edit_tags(tcl_key)  $Start $End 
  EmsEditHighlightComment .emsEdit.text_frame.text  "#" gui_edit_tags(comment) $Start $End 
  EmsEditHighlightVars .emsEdit.text_frame.text {$} gui_edit_tags(tcl_var) $Start $End 
  EmsEditHighlightVars .emsEdit.text_frame.text {@} gui_edit_tags(rivl_var) $Start $End 
  EmsEditHighlightXdigits .emsEdit.text_frame.text  gui_edit_tags(xdigit) $Start $End 
}

# 
# Routine Description:
# 
#   Highlight the keywords in TextWidget with Tag.
# 
# Arguments:
# 
#    TextWidget :   The text widget 
#    Keys       :   The keywords 
#    Tag        :   Highlight Tag
#    Start      :   The Start of the range
#    End        :   The End of the range
# 
# Returns:
# 
#   None.
# 
proc EmsEditHighlightKeys { TextWidget Keys Tag Start End } {

  foreach key $Keys {
    set cur $Start
    while 1 {
      set cur [$TextWidget search -exact -count length  -regexp  \\m$key\\M $cur $End]
      if {$cur == ""} {
        break
      }
      $TextWidget tag add $Tag $cur "$cur + $length char "
      set cur [$TextWidget index "$cur + $length char"]
    }
  }
}

# 
# Routine Description:
# 
#   Highlight the variables in TextWidget with Tag.
# 
# Arguments:
# 
#    TextWidget :   The text widget 
#    Keys       :   The keywords 
#    Tag        :   Highlight Tag
#    Start      :   The Start of the range
#    End        :   The End of the range
# 
# Returns:
# 
#   None.
# 
proc EmsEditHighlightVars { TextWidget char Tag Start End} {
  set cur $Start
  while 1 {
    set cur [$TextWidget search -exact -count length  -regexp  "\[$char\].*?\\M" $cur $End]
    if {$cur == ""} {
     break
    }
    $TextWidget tag add $Tag $cur "$cur + $length char"
    set cur [$TextWidget index "$cur + $length char"]
  }
}

# 
# Routine Description:
# 
#   Highlight the xdigits in TextWidget with Tag.
# 
# Arguments:
# 
#    TextWidget :   The text widget 
#    Keys       :   The keywords 
#    Tag        :   Highlight Tag
#    Start      :   The Start of the range
#    End        :   The End of the range
# 
# Returns:
# 
#   None.
# 
proc EmsEditHighlightXdigits { TextWidget Tag Start End } {

  set cur $Start
  while 1 {
    set cur [$TextWidget search -exact -count length  -regexp "\\m\[0-9\]\[0-9a-hA-H\]*" $cur $End]
    if {$cur == ""} {
      break
    }
    $TextWidget tag add $Tag $cur "$cur + $length char"
    set cur [$TextWidget index "$cur + $length char"]
  }
  set cur $Start
  while 1 {
    set cur [$TextWidget search -exact -count length  -regexp "\\m0\[xX\]\[0-9a-hA-H\]*" $cur $End]
    if {$cur == ""} {
      break
    }
    $TextWidget tag add $Tag $cur "$cur + $length char"
    set cur [$TextWidget index "$cur + $length char"]
  }
}

# 
# Routine Description:
# 
#   Highlight the xdigits in TextWidget with Tag.
# 
# Arguments:
# 
#    TextWidget :   The text widget 
#    Keys       :   The keywords 
#    Tag        :   Highlight Tag
#    Start      :   The Start of the range
#    End        :   The End of the range
# 
# Returns:
# 
#   None.
# 
proc EmsEditHighlightComment { TextWidget char Tag Start End } {
    set cur $Start
    while 1 {
      set cur [$TextWidget search -exact -count length  -regexp  "\[$char\].*" $cur $End]
      if {$cur == ""} {
              break
      }
      $TextWidget tag add $Tag $cur "$cur + $length char"
      set cur [$TextWidget index "$cur + $length char"]
    }
}
