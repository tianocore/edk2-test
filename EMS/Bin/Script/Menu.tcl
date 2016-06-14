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
