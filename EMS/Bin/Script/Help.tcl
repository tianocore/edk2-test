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
#     Implementation for EMS Help form function
#

if {[info exist HELP_TCL] == 1} {
  return
}
set HELP_TCL 1

# 
# Routine Description:
# 
#   Start the the main form of Help.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsEditHelp { } {
  EmsHelpForm 
}

# 
# Routine Description:
# 
#   Show help information of specified command.
# 
# Arguments:
# 
#   Widget    :    The text Widget
#   Command   :    The command's name
# 
# Returns:
# 
#   None.
# 
proc EmsHelpShow { Widget command } {
  global _ENTS ENTSTags

  $Widget configure -state normal
  
  set _ENTS(helpfile) [file join . doc commands $command.em]
  if {![file readable $_ENTS(helpfile)]} {
    EmsHelpShowHome $Widget
    return
  }
  if {[catch "open $_ENTS(helpfile) r" fd]} {
    return
   }
  set _ENTS(help_package) "[read $fd]"
  close $fd
  $Widget delete 1.0 end

  set _ENTS(packagekeyname) [file tail $_ENTS(helpfile)]

  EmsHelpHighLight $Widget $_ENTS(help_package)
  
  $Widget  configure -state disabled
} 


# 
# Routine Description:
# 
#   Search related topics using key.
# 
# Arguments:
# 
#   The search key.
# 
# Returns:
# 
#   None.
# 
proc EmsHelpSearchTopic { key } {
  global _ENTS

  if {[string length $key] == 0} {
    set _ENTS(current_commands) $_ENTS(commands)
    return
  }

  set _ENTS(current_commands) ""

  foreach command $_ENTS(commands) {
    if { [string first [string tolower $key] [string tolower $command]] != 0 } {
      continue
    }
    lappend _ENTS(current_commands) $command
  }
  update
}


# 
# Routine Description:
# 
#   Show the home page of writes' guide
# 
# Arguments:
# 
#   The text Widget
# 
# Returns:
# 
#   None.
# 
proc EmsHelpShowHome { Widget } {
  global _ENTS 

  $Widget configure -state normal
  $Widget delete 1.0 end
  $Widget insert end "\n\n\tENTS Case Writers Guide" Help_tag(title) 
  $Widget  configure -state disabled
}

# 
# Routine Description:
# 
#   Initialize _ENTS(commands)
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsHelpInitCommands { } {
  global _ENTS 
  
  set files [lsort -dictionary [glob -nocomplain [file join . doc commands *.em] ]]
  set _ENTS(commands) ""
  foreach file $files {
    set ff [file tail $file]
    if {$ff != "." && $ff != ".."} {
      if {[file isdirectory $file]} {
      } else {
        set temp [split $ff .]
        lappend _ENTS(commands) [lindex $temp 0]
      }
    }
  }
}

# 
# Routine Description:
# 
#   Initialize the tags for help.
# 
# Arguments:
# 
#   The text Widget.
# 
# Returns:
# 
#   None.
# 
proc EmsHelpInitTags { Widget } {
  global _ENTS

  set _ENTS(help_keys) { Name Usage Description "Return value" Notes Example "See also"}
  
  $Widget tag configure Help_tag(key)     -font {"Courier New" 11 bold} -foreground black
  $Widget tag configure Help_tag(normal)  -font {"Courier New" 10 }     -foreground black
  $Widget tag configure Help_tag(command) -font {"Courier New" 10 bold} -foreground black
  $Widget tag configure Help_tag(help)    -font {"Courier New" 10 bold} -foreground red 
  $Widget tag configure Help_tag(title)   -font {"Times" 30 bold} -foreground black

  foreach command $_ENTS(commands) {
    $Widget tag configure Help_tag($command) -font {"Courier New" 10 bold } -foreground black
    set temp "EmsHelpShow $Widget $command"
    $Widget tag bind Help_tag($command) <1> $temp
    $Widget tag bind Help_tag($command) <Any-Enter> \
    "$Widget tag configure Help_tag($command) -font {{Courier New} 10 bold underline}; $Widget configure -cursor hand2"
    $Widget tag bind Help_tag($command) <Any-Leave> \
    "$Widget tag configure Help_tag($command) -font {{Courier New} 10 bold }; $Widget configure -cursor arrow"
  }
}

# 
# Routine Description:
# 
#   Display the package and highlight all the keys.
# 
# Arguments:
# 
#   Widget      :  The text Widget
#   package     :  The package to display
# 
# Returns:
# 
#   None.
# 
proc EmsHelpHighLight { Widget package } {
  global _ENTS    
  set LineCount 0
  
  # Split it into lines 
  set list_temp [split $package \n]

  foreach line_x $list_temp {
    set inserted 0
    #skip Null string
    if {[string equal $line_x ""] == 1} {
      $Widget insert end \n
      incr LineCount 
      continue
    }
    foreach key $_ENTS(help_keys) {
      if {[string first $key $line_x] == 0} {
         $Widget insert end " \n" Help_tag(key) $line_x Help_tag(key) "\n"
         set inserted 1
         incr LineCount 2
         break
      }
    }
    if {$inserted == 1} continue
    $Widget  insert end "\t"
    $Widget  insert end $line_x
    $Widget  insert end "\n"
    incr LineCount 

    foreach command $_ENTS(commands) {
      set index 0
      while {1} {
        set index [string first $command $line_x $index]
        if {$index == -1 } {
          break ;#
        }
        incr index 
        $Widget  tag add Help_tag($command) $LineCount.$index $LineCount.[expr $index + [string length $command]]
      }
    }
  }
}

# 
# Routine Description:
# 
#   The main form of Help.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsHelpForm { } {
  global _ENTS Images
  global GuiColors GuiBoxs GuiFrames
  global EmsFiles

  EmsHelpInitCommands  
  
  catch "destroy .ems_help"

  toplevel .ems_help  -background $GuiColors(background)
  wm withdraw .ems_help
  wm title .ems_help "ENTS Case Writer's Guide"
  
  frame  .ems_help.button_frame -background $GuiColors(background) -relief raised -border 1
  pack   .ems_help.button_frame -side top -fill x

  BuildButton .ems_help.button_frame.home $Images(home) "EmsHelpShowHome .ems_help.panedwindow.right.text" ""  
  BuildButton .ems_help.button_frame.exit $Images(stop) "destroy .ems_help" ""  

  set Name .ems_help.panedwindow
  panedwindow $Name -orient horizontal -showhandle 0 -background $GuiColors(background)
  pack $Name -expand 1 -fill both
  
  set Name .ems_help.panedwindow.left
  frame $Name -background $GuiColors(background) -borderwidth 0 -relief ridge 
  .ems_help.panedwindow add $Name -minsize 2i 

  label $Name.l -background $GuiColors(background) -font EmsBasicFont \
               -justify left -text "Search for:"
  pack $Name.l -side top -anchor nw

  entry $Name.e -width 30 -relief sunken -textvariable _ENTS(HelpWord)
  pack  $Name.e -side top -anchor ne -fill x
  bind $Name.e <Return> {EmsHelpSearchTopic $_ENTS(HelpWord)}

  button $Name.b -text "List Topics" -background $GuiColors(background) -command {EmsHelpSearchTopic $_ENTS(HelpWord)}

  pack $Name.b -side top  -fill x -anchor ne

  set _ENTS(current_commands) $_ENTS(commands)

  frame $Name.f -background $GuiColors(background) -borderwidth 0 -relief ridge 
  pack $Name.f -side top -expand yes -fill both
    
  listbox $Name.f.lb -listvariable _ENTS(current_commands) -width 20 \
             -xscrollcommand "  $Name.f.scrollx set " \
             -yscrollcommand "  $Name.f.scrolly set " 
  scrollbar $Name.f.scrolly -command "$Name.f.lb yview" -orient vertical -borderwidth 0
  scrollbar $Name.f.scrollx -command "$Name.f.lb xview" -orient horizontal -borderwidth 0

  pack $Name.f.scrolly -side right  -fill y
  pack $Name.f.scrollx -side bottom -fill x
  pack $Name.f.lb -anchor sw -side top -expand yes -fill both       

  bind $Name.f.lb <Double-Button-1> {
         set i [%W curselection]
         EmsHelpShow .ems_help.panedwindow.right.text [%W get $i]
         }
    
  set Name .ems_help.panedwindow.right
  frame $Name -background $GuiColors(background) -borderwidth 0 -relief ridge 
  .ems_help.panedwindow add $Name -minsize 2i 

  text $Name.text -wrap none -width 80 -height 20 -relief sunken -borderwidth 1 \
             -cursor arrow -font {"Courier New" 10 } -foreground black \
             -background white  \
             -foreground black  \
             -xscrollcommand "  $Name.scrollx set " \
             -yscrollcommand "  $Name.scrolly set " \
             -wrap word
  scrollbar  $Name.scrolly -command "$Name.text yview" -orient vertical -borderwidth 0
  scrollbar  $Name.scrollx -command "$Name.text xview" -orient horizontal -borderwidth 0

  pack $Name.scrolly -side right  -fill y                                 
  pack $Name.scrollx -side bottom -fill x                                 
  pack $Name.text -anchor sw -side left -expand 1 -fill both              

  EmsHelpInitTags $Name.text 
  EmsHelpShowHome $Name.text 
  
  set x [expr [winfo rootx $GuiFrames(main)] + 300]
  set y [expr [winfo rooty $GuiFrames(main)] + [winfo height $GuiFrames(main)] - 300]

  wm geometry .ems_help +30+30
  wm deiconify .ems_help
  wm resizable .ems_help  1 1
  raise .ems_help
  update
}
