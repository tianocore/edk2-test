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
#     Implementation for EMS Menu form function
#

if {[info exist MENU_TCL] == 1} {
  return
}
set MENU_TCL 1

# 
# Routine Description:
# 
#   Add a set of menu selections to a menu from a command list.
# 
# Arguments:
# 
#    newmenu          - Name of the window to create a menu in
#    Cmdlist          - A list of commands defining menu items
#      {menuID MenuName ExtraCmds}
#      menuID: Defines the type of menu to create.  Options are:
#         separator - Makes a separator line
#         command   - Creates a command menu
#         cascade   - Creates a cascading menu
#      MenuName: The name to put in this menu
#      ExtraCmds:  Extra args to define this menubutton
#        If menuID is cascade, then ExtraCmds is a list of ID, Name, Cmd lists
# 
# Returns:
# 
#   None.
# 
proc AddItemsToMenu {menubutton cmdList} {
  global GuiMenus GuiColors

  foreach cmd $cmdList {
    switch [lindex $cmd 0] {
      "separator" {
         eval "$menubutton add separator [lindex $cmd 2]"
         }
      "tearoff"  {
         if {[string match [lindex $cmd 2] "no"]} {
           $menubutton configure -tearoff no
        } else {
           $menubutton configure -tearoff yes
                }
         }
      "command"  {
         eval "$menubutton add [lindex $cmd 0] -label {[lindex $cmd 1]} [lindex $cmd 2]"
         }
      "cascade"  {
         incr GuiMenus(menuCount);
         set newmenu $menubutton.m$GuiMenus(menuCount)
         eval "$menubutton add cascade -label {[lindex $cmd 1]} -menu $newmenu"
         menu $newmenu -activebackground $GuiColors(activebackground) \
              -activeforeground $GuiColors(activeforeground) \
              -background $GuiColors(menuforeground) \
              -foreground $GuiColors(menubackground) 
         AddItemsToMenu $newmenu [lindex $cmd 2]
         }
      }
    }
  }

# 
# Routine Description:
# 
#   Constuct menu
# 
# Arguments:
# 
#    Name             - Menu pathname
#    Lable            - Specifies a string to be displayed inside the menu button.
#    Cmdlist
#      {menuID MenuName ExtraCmds}
#      menuID: Defines the type of menu to create.  Options are:
#         separator - Makes a separator line
#         command   - Creates a command menu
#         cascade   - Creates a cascading menu
#      MenuName: The name to put in this menu
#      ExtraCmds:  Extra args to define this menubutton
#        If menuID is cascade, then ExtraCmds is a list of ID, Name, Cmd lists
# 
# Returns:
# 
#   None.
# 
proc BuildMenu {Name Label cmd_list} {
  global GuiMenus
  global GuiColors
  
  menubutton $Name  -activebackground $GuiColors(activebackground) \
      -activeforeground $GuiColors(activeforeground) \
      -background $GuiColors(background) \
      -foreground $GuiColors(foreground) \
      -relief flat -text $Label  -underline 0
  
  incr GuiMenus(menuCount);
  set newmenu $Name.m$GuiMenus(menuCount)

  $Name configure -menu $newmenu

  catch "destroy $newmenu"
 
  eval "menu $newmenu"

  eval [list AddItemsToMenu $newmenu $cmd_list]

  $newmenu configure -activebackground $GuiColors(activebackground)\
     -activeforeground $GuiColors(activeforeground)\
     -background $GuiColors(menuforeground) \
     -foreground $GuiColors(foreground)

  pack $Name -anchor nw -expand 0 -ipadx 4 -ipady 0 -padx 0 -pady 0 -side left
}

# 
# Routine Description:
# 
#    Build a button and pack it.
# 
# Arguments:
# 
#    Name             - Name of the buttone to build
#    data             - The base64 encoded data of the button image
#    cmd              - The command to execute when this is selected
#    prompt           - Prompt information
# 
# Returns:
# 
#   None.
# 
proc BuildButton {Name data cmd prompt} {

  global _ENTS GuiColors
  set im [image create photo -data $data -gamma 1 -height 32 -width 32 -palette 5/5/5]

  button $Name -background $GuiColors(background) -foreground black -activebackground white -image $im \
         -relief groove -command "$cmd" -border 1
  pack $Name -anchor nw -side left -expand 0  -fill x 
  bind $Name <Enter> "EmsShowStatus \"$prompt\"; $Name configure -relief raised"
  bind $Name <Leave> "EmsShowStatus \"$_ENTS(DefaultStatus)\";  $Name configure -relief groove"
}
