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
#     Main.tcl
#     
# Abstract:
# 
#     TK Gui for EMS2.0 
#

Include ./Script/About.tcl
Include ./Script/Configure.tcl
Include ./Script/Edit.tcl
Include ./Script/Help.tcl
Include ./Script/Image.tcl
Include ./Script/Init.tcl
Include ./Script/Menu.tcl
Include ./Script/Output.tcl
Include ./Script/Sequence.tcl
Include ./Script/Utility.tcl
Include ./Script/TestCaseWindow.tcl
Include ./Script/Tree.tcl
Include ./Script/Protocols.tcl
Include ./Script/Category.tcl
Include ./Script/TestCase.tcl

wm iconify .

# 
# Routine Description:
# 
#   Active the RemoteExecution frame
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc ActiveRemoteExecutionFrame {} {
  global GuiFrames GuiBoxs GuiCursors GuiColors EmsActiveLeftFrame EmsLeftWindow
  $GuiFrames(top) forget $GuiFrames(protocol)
  $GuiFrames(top) add $GuiFrames(category) -minsize 2i -before $GuiFrames(testcase)
  set EmsActiveLeftFrame "RemoteExecution"
  set EmsLeftWindow $GuiBoxs(category)

  TestCaseWindowCleanup
  TreeWindowCleanupHook
  TreeShow $GuiBoxs(category) RemoteExecution
}

# 
# Routine Description:
# 
#   Active the RemoteValidation frame
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc ActiveRemoteValidationFrame {} {
  global GuiFrames GuiBoxs GuiCursors GuiColors EmsActiveLeftFrame EmsLeftWindow
  $GuiFrames(top) forget $GuiFrames(category)
  $GuiFrames(top) add $GuiFrames(protocol) -minsize 2i -before $GuiFrames(testcase)
  set EmsActiveLeftFrame "RemoteValidation"
  set EmsLeftWindow $GuiBoxs(protocol)

  TestCaseWindowCleanup
  TreeWindowCleanupHook
  TreeShow $GuiBoxs(protocol) RemoteValidation
}

# 
# Routine Description:
# 
#   The callback funtin of activing the RemoteExecution frame
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc CmdActiveRemoteExecutionFrame {} {
  global GuiBoxs EmsActiveLeftFrame EmsGetRemoteCaseTree

  if {$EmsGetRemoteCaseTree == 0} {
    if {[EmsTestIsRunning] == 1} {
      tk_messageBox -type ok -message "The Test is Running!"
      EmsReleaseMutex
      return
    }

    EmsThreadCmd "Exec \"cp -q \\\\SCT\\\\Data\\\\CaseTree.ini \\\\ \";PutFile CaseTree.ini; Exec \"del -q \\\\CaseTree.ini\"" 20000
    set Time 0
     while {[EmsTestIsRunning] == 1 && $Time < 100} {
      after 200
      incr Time
    }
    if {$Time >= 100 || ![file exists "CaseTree.ini"]} {
      EmsGuiError "Get Remote Case Tree time out!"
      return
    }
	Stall 1
    EmsCategoryTreeBuild
    set EmsGetRemoteCaseTree 1
  }

  if {$EmsActiveLeftFrame != "RemoteExecution"} {
    ActiveRemoteExecutionFrame
  }
}

# 
# Routine Description:
# 
#   The callback funtin of activing the RemoteValidation frame
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc CmdActiveRemoteValidationFrame {} {
  global GuiBoxs EmsActiveLeftFrame EmsGetRemoteValidationCaseTree

  if {$EmsGetRemoteValidationCaseTree == 0} {
    EmsProtocolTreeBuild
	set EmsGetRemoteValidationCaseTree 1
  }

  if {$EmsActiveLeftFrame != "RemoteValidation"} {
    ActiveRemoteValidationFrame
  }
}

# 
# Routine Description:
# 
#   Initialize the EMS left frame
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsLeftFrameInit {} {
  global GuiBoxs EmsActiveLeftFrame EmsGetRemoteValidationCaseTree

  set EmsGetRemoteValidationCaseTree   0
  set EmsActiveLeftFrame      ""
  CmdActiveRemoteValidationFrame
}

# 
# Routine Description:
# 
#   Start the EMS GUI
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsStartGui {} {
  global TclPlatform
  global _ENTS
  global GuiColors GuiFrames GuiBoxs GuiCursors
  global Images 
  toplevel $GuiFrames(main) -background $GuiColors(background)
  wm withdraw $GuiFrames(main)
  wm title $GuiFrames(main) " UEFI SCT EMS"
  wm geometry $GuiFrames(main) +[winfo screenwidth .]+0

  #
  # Main menu
  #
  set Name $GuiFrames(mainmenu)
  frame $Name -background $GuiColors(background)  -relief raised -borderwidth 1 -cursor $GuiCursors(default)
  pack  $Name -anchor nw -expand 0 -fill x -ipadx 0 -ipady 0 -padx 0 -pady 0 -side top

  panedwindow $Name.p -orient horizontal  -showhandle 0  -background $GuiColors(background)
  pack $Name.p -expand 1 -fill both
  frame $Name.p.1 -background lightgray -relief flat -borderwidth 0
  $Name.p add $Name.p.1 -minsize 1i -padx 0 -pady 0

  set Menu $Name.p.1.file
  set Menu_string($Menu) {
    {{tearoff} {} {no}}
    {{command} {Load sequence file ...} {-command CmdLoadSequence -accelerator "F2"  -underline 0}}
    {{command} {Save sequence file as ...}   {-command CmdSaveSequence -accelerator "F3"  -underline 0}}
    {{separator} {} {}}
    {{command} {Preference ...} {-command EmsConfigForm -accelerator "F5"  -underline 0}}
    {{command} {Exit} {-command CmdStopGui -accelerator "Alt+F4"  -underline 1}}
    }
  BuildMenu $Menu File $Menu_string($Menu)

  set Menu $Name.p.1.run
  set Menu_string($Menu) {
    {{tearoff} {} {no}}
    {{command} {Start}  {-command CmdTestStart -accelerator "F9"  -underline 0}}
    {{command} {Stop}   {-command CmdTestStop -accelerator "F10"  -underline 3}}
    {{separator} {} {}}	
    {{command} {Continue}   {-command CmdTestContinue -accelerator "F11" -underline 0}}
    }
  BuildMenu $Menu Run $Menu_string($Menu)

  set Menu $Name.p.1.windows
  set Menu_string($Menu) {
	{{tearoff} {} {no}}
	{{command} {RemoteExecution}   {-command CmdActiveRemoteExecutionFrame -underline 6}}
	{{command} {RemoteValidation} {-command CmdActiveRemoteValidationFrame -underline 6}}
	{{separator} {} {}}
	{{command} {RefreshCaseTree} {-command CmdCaseTreeReload -underline 0}}
	{{separator} {} {}}
    }
  BuildMenu $Menu Windows $Menu_string($Menu)

  set Menu $Name.p.1.tools
  set Menu_string($Menu) {
    {{tearoff} {} {no}}
    {{command} {Edit}   {-command EmsEditForm -accelerator "Ctrl+E"  -underline 0}}
    {{command} {Clear Output}   {-command EmsClearOutput -accelerator "Ctrl+L"  -underline 0}}
	{{separator} {} {}}	
    {{command} {Target Exit}   {-command "EmsThreadCmd \"Exit\" -1" -accelerator "Ctrl+T"  -underline 0}}
    {{separator} {} {}}
    }
  BuildMenu $Menu Tools $Menu_string($Menu)

  set Menu $Name.p.1.help
  set Menu_string($Menu) {
    {{tearoff} {} {no}}
    {{command} {Index}   {-command EmsHelpForm -accelerator "F1"  -underline 0}}
    {{command} {About ENTS ...} {-command CmdHelpAbout -accelerator "F11"  -underline 0}}
    }
  BuildMenu $Menu Help $Menu_string($Menu)

  #
  # Button frame 
  #
  set Name $GuiFrames(button)
  frame $Name -background $GuiColors(background) -relief raised -borderwidth 1
  pack $Name -anchor nw -side top -expand 0 -fill x -ipadx 0 -ipady 0 -padx 0 -pady 0 

  panedwindow $Name.p -orient horizontal  -showhandle 0  -background $GuiColors(background)
  pack $Name.p -expand 1 -fill both
  frame $Name.p.1 -background lightgray -relief flat -borderwidth 0
  $Name.p add $Name.p.1 -minsize 1i -padx 0 -pady 0

  BuildButton $Name.p.1.load    $Images(load)   "CmdLoadSequence" "Load sequence file"  
  BuildButton $Name.p.1.save    $Images(save)   "CmdSaveSequence" "Save sequence file"  
  BuildButton $Name.p.1.config  $Images(config) "EmsConfigForm" "Configure the preference"  

  frame $Name.p.2 -background $GuiColors(background) -relief flat -borderwidth 0
  $Name.p add $Name.p.2 -minsize 1i -padx 0 -pady 0
  BuildButton $Name.p.2.start   $Images(start) "CmdTestStart" "start to run the testcases"  
  BuildButton $Name.p.2.stop    $Images(stop) "CmdTestStop" "stop"  
  BuildButton $Name.p.2.report  $Images(report) "CmdTestReport" "Report"  

  frame $Name.p.3 -background $GuiColors(background) -relief flat -borderwidth 0
  $Name.p add $Name.p.3 -minsize 1i -padx 0 -pady 0
  BuildButton $Name.p.3.index $Images(help) "EmsHelpForm" "Display help information"  
  BuildButton $Name.p.3.about $Images(about) "CmdHelpAbout" "Display copyright"  

  panedwindow $GuiFrames(panedwindow) -orient vertical -showhandle 0  -background $GuiColors(background)
  pack $GuiFrames(panedwindow) -expand 1 -fill both

  #----------------------------------------
  set Name $GuiFrames(top)
  panedwindow $Name -orient horizontal -showhandle 0 -background $GuiColors(background)

  $GuiFrames(panedwindow) add $Name -minsize 1i -padx 0 -pady 0

  set Name $GuiFrames(testcase)
  frame $Name -background $GuiColors(background) -borderwidth 0 -relief ridge
  $GuiFrames(top) add $Name -minsize 2i

  set Name $GuiBoxs(testcase)
  text $Name -wrap none -width 60 -height 20 -relief sunken \
       -borderwidth 1 -cursor $GuiCursors(default) \
       -background $GuiColors(testcase_box_background)  \
       -xscrollcommand "$GuiFrames(testcase).hs set" \
       -yscrollcommand "$GuiFrames(testcase).vs set" 
  scrollbar $GuiFrames(testcase).vs -command "$Name yview" -orient vertical
  scrollbar $GuiFrames(testcase).hs -command "$Name xview" -orient horizontal
  pack $GuiFrames(testcase).vs -side right -fill y
  pack $GuiFrames(testcase).hs -side bottom -fill x
  pack $GuiBoxs(testcase) -side left -fill both -expand 1

  EmsGuiFramesCategoryBuild
  EmsGuiFramesProtocolBuild
  EmsTestCaseWindowInit

  #
  # Bottom frame
  #
  set Name $GuiFrames(bottom)
  frame $Name -background $GuiColors(background) -borderwidth 1  -relief ridge 
  $GuiFrames(panedwindow) add $Name -minsize 1i -padx 0 -pady 0

  set Name $GuiFrames(bottom).text   ; # GuiBoxs(output)
  text $Name -wrap none -width 100 -height 1 -relief sunken -borderwidth 1 \
             -cursor arrow -font EmsBasicFont \
             -background $GuiColors(output_box_background)  \
             -foreground $GuiColors(output_box_foreground)  \
             -xscrollcommand "  $GuiFrames(bottom).scrollx set " \
             -yscrollcommand "  $GuiFrames(bottom).scrolly set " 
  scrollbar  $GuiFrames(bottom).scrolly -command "$Name yview" -orient vertical -borderwidth 0
  scrollbar  $GuiFrames(bottom).scrollx -command "$Name xview" -orient horizontal -borderwidth 0
  $Name tag configure gui_output_tags(error)  -foreground Red -background $GuiColors(output_box_background) -font {"Courier New" 10 bold}
  $Name tag configure gui_output_tags(highlight)  -foreground Black -background $GuiColors(output_box_background) -font {"Courier New" 12 bold}
 
  bind $Name <KeyPress-Return> {
        global GuiBoxs
        set TmpCmd [ $GuiBoxs(output) get "insert linestart"  "insert lineend"]
#        EmsThreadCmd "$TmpCmd" -1
#        eval $TmpCmd
  } 

  pack $GuiFrames(bottom).scrolly -side right  -fill y 
  pack $GuiFrames(bottom).scrollx -side bottom -fill x 
  pack $Name -anchor sw -side left -expand 1 -fill both

  #
  # Status frame
  #
  frame $GuiFrames(status) -background black -borderwidth 1 -relief flat 
  pack $GuiFrames(status) -anchor nw -side bottom -fill both -expand 0
  
  set Name $GuiFrames(status).currentstatus
  label $Name -background $GuiColors(background_status) \
              -foreground $GuiColors(foreground_status) \
              -textvariable _ENTS(status) -relief flat -anchor w 
  pack $Name -anchor w -expand 0
  

  #
  # Shortcut keys 
  #
  bind $GuiFrames(main) <F1>  { EmsEditHelp      }
  bind $GuiFrames(main) <F2>  { CmdLoadSequence  }
  bind $GuiFrames(main) <F3>  { CmdSaveSequence  }
  bind $GuiFrames(main) <F5>  { EmsConfigForm    }
  bind $GuiFrames(main) <F9>  { CmdTestStart     }
  bind $GuiFrames(main) <F10> { CmdTestStop      }
  bind $GuiFrames(main) <F11>  { CmdTestContinue  }

  wm geometry   $GuiFrames(main)  +0+0
  wm minsize    $GuiFrames(main)  320 240
  wm state      $GuiFrames(main)  zoomed
  wm resizable  $GuiFrames(main)  1 1
  update
}


# 
# Routine Description:
# 
#   Terminate the GUI
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc CmdStopGui {} {
  EmsTclResCleanup
  exit
}

# 
# Routine Description:
# 
#   PopUp a error dialog.
# 
# Arguments:
# 
#   The message in the dialog box.
# 
# Returns:
# 
#   None.
# 
proc EmsGuiError {Message} {
  catch "destroy .xxx"
  bell
  tk_dialog .xxx "Error" "$Message" warning 0 Close
}

proc EmsGuiDialog {Message} {
  catch "destroy .yyy"
  tk_dialog .yyy "Message" "$Message" warning 0 Close
}

#===============================================================================
# start here 
#===============================================================================
#
# Check the version of TCL/TK
#
if {[info exists tcl_version] == 0 || $tcl_version < 8.4} {
    error "Error :  This program requires Tcl 8.4 or higher"
}
if {[info exists tk_version] == 0 || $tk_version < 8.4} {
    error "Error :  This program requires Tk 4.1 or higher"
}
if {[info exists tcl_platform(threaded)] == 0} {
	error "Error :  This program requires Tcl Threads support"
}
#
# Clear previous global variables
#
foreach globalvar [info globals *ENTS*] {
    catch "unset $globalvar" dummy
}

# Initialize global variables
EmsInitGlobals
EmsHostInit
if {[TclTargetCleanup [GetTargetMac]] != "OK"} {
  puts "Can not cleanup Target"
}

#
# Initialize Images
#
EmsInitImages

#
# start GUI
#
EmsStartGui

#
# Use EmsOutput to output the log information
#
catch { SetOutput "EmsOutput" }

RecvAssertionThreadStart
EmsTestInit
EftpStart $_ENTS(hostmac)

if {[file exists CaseTree.ini]} {
  file delete CaseTree.ini -force
}

EmsLeftFrameInit

wm protocol $GuiFrames(main) WM_DELETE_WINDOW CmdStopGui
wm withdraw .
raise $GuiFrames(main)
update

GuiMainEventLoop
