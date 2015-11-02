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
#     Implementation for EMS TCL Init function
#

if {[info exist INIT_TCL] == 1} {
  return
}
set INIT_TCL 1

# 
# Routine Description:
# 
#   Initialize The EMS GUI configuration
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsInitGuiConfigure {} {
  global GuiColors GuiFrames GuiBoxs GuiMenus GuiCursors
  global EmsActiveLeftFrame EmsLeftWindow EmsGetRemoteCaseTree EmsGetRemoteValidationCaseTree

  #
  # Init Fonts
  #
  font create EmsBasicReadonlyFont         -family Times  -size 10 -weight bold
  font create EmsBasicFont                 -family Times  -size 10 
  font create EmsProtocolFont              -family Times  -size 10 -weight bold
  font create EmsTestCaseFont              -family Times  -size 10 -weight bold
  font create EmsTestCaseTitleFont         -family Times  -size 10 -weight bold
  font create EmsEditFont                  -family Times  -size 10

  font create EmsTreeNodeSelectYFont       -family Times  -size 12 -weight bold
  font create EmsTreeNodeSelectNFont       -family Times  -size 10

  #
  # Init Colors 
  # 
  set GuiColors(background)                lightgray    ;
  set GuiColors(foreground)                black        ;
  
  set GuiColors(menuforeground)            white         ; #for menu
  set GuiColors(menubackground)            black         ; #for menu
  set GuiColors(activeforeground)          white         ; #for menu
  set GuiColors(activebackground)          "DodgerBlue3" ; #for menu
  set GuiColors(background_status)         black         ; #for status bar
  set GuiColors(foreground_status)         green         ; #for status bar
  
  set GuiColors(protocol_box_background)   #EFEFEF ; #for protocol window
  set GuiColors(protocol_box_foreground)   black   ; #for protocol window
  set GuiColors(testcase_box_background)   #EFEFEF ; #for testcase window
  set GuiColors(testcase_box_foreground)   black   ; #for testcase window
  set GuiColors(category_box_background)   #EFEFEF ; #for protocol window
  set GuiColors(category_box_foreground)   black   ; #for protocol window

  set GuiColors(output_box_background)     #EFEFEF ; #for output window
  set GuiColors(output_box_foreground)     black   ; #for output window

  set GuiColors(case_result_foreground_normal)    Black
  set GuiColors(case_result_foreground_error)     Red
  set GuiColors(case_result_foreground_fail)      Brown
  set GuiColors(case_result_foreground_pass)      Green
  set GuiColors(case_result_foreground_warn)      Yellow

  #
  # Init Frames' names
  #
  set GuiFrames(main)                      .mainframe
  set GuiFrames(edit)                      .EmsEdit
  set GuiFrames(config)                    .emsConfig

  set GuiFrames(mainmenu)                  $GuiFrames(main).menuframe
  set GuiFrames(button)                    $GuiFrames(main).buttons
  set GuiFrames(status)                    $GuiFrames(main).statusframe
  set GuiFrames(panedwindow)               $GuiFrames(main).p
  set GuiFrames(top)                       $GuiFrames(main).p.top

  set EmsGetRemoteCaseTree                 0
  set EmsGetRemoteValidationCaseTree                0
  set EmsActiveLeftFrame                   ""
  set EmsLeftWindow                        ""

  set GuiFrames(protocol)                  $GuiFrames(top).left1
  set GuiFrames(category)                  $GuiFrames(top).left2
  set GuiFrames(testcase)                  $GuiFrames(top).right
  set GuiBoxs(category)                    $GuiFrames(category).window
  set GuiBoxs(testcase)                    $GuiFrames(testcase).window
  set GuiBoxs(protocol)                    $GuiFrames(protocol).window     ;#Protocol window

  set GuiFrames(bottom)                    $GuiFrames(main).p.bottom
  set GuiFrames(output)                    $GuiFrames(bottom)

  set GuiBoxs(output)                      $GuiFrames(bottom).text  ;#Output window

  set GuiCursors(busy)                     circle
  set GuiCursors(default)                  arrow

  set GuiMenus(menuCount)                  0;
}

# 
# Routine Description:
# 
#   Initialize the EMS keywords
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsInitKeywords {} {
  global RivlKeys TclKeys

  set RivlKeys {
    BeginLog        BeginScope CaptureMultiPacket CapturePacket   CaseAttribute    CaseCategory
    CaseDescription CaseGuid   CaseLevel          CaseName        CaseVerboseLevel CreatePacket
	CreatePayload   DelVar     DelType            DestroyPacket   DumpPacket       EndLog
    EndScope        GetAck     GetMac             GetVar          Include          LocalEther
    LocalIp         OpenDev    ParsePacket        RecordAssertion RecordMessage    RemoteEther
    RemoteIp        SendPacket SetFilter          SetVar          ValidatePacket   VifDown
    VifUp           BOOLEAN    INTN               UINTN           INT8             UINT8
    INT16           UINT16     INT32              UINT32          INT64            UINT64
    CHAR8           CHAR16     POINTER            Sizeof          Typeof           ViewType
    Pack            Exit       Func               Struct          Union            NULL 
    TRUE            FALSE
  }

  #
  # Init TCL keywords 
  #
  #     after append array auto_execok auto_load auto_mkindex auto_reset
  #     bgerror
  #     catch cd clock close concat
  #     eof error eval exec exit expr
  #     fblocked fconfigure file fileevent flush format
  #     gets glob global
  #     history
  #     incr info interpEmsProtocols
  #     join
  #     lappend lindex linsert list llength load lrange lreplace lsearch lsort
  #     message
  #     open
  #     package parray pid proc puts pwd
  #     read regexp regsub rename return
  #     scan seek set socket source split string subst
  #     tell time trace tcl_endOfWord tcl_startOfNextWord tcl_startOfPreviousWord tcl_wordBreakAfter tcl_wordBreakBefore
  #     unknown unset update uplevel upvar
  #     vwait
  set TclKeys {
     gets      puts    incr   exec    source  proc    global  set    unset  break  case 
     continue  default else   elseif  for     foreach if      switch then   while
  }
}

# 
# Routine Description:
# 
#   Initialize some configuation of RemoteExecution
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsInitRemoteValidationConfigure {} {
  global _ENTS EmsAdapterDesc InterfaceIndexs EmsAdapterName
  #
  # Initialize network adapters in system
  #
  ShowIf
  set _ENTS(InterfaceNumber)  [array size EmsAdapterDesc]
  set TempList                [array get EmsAdapterDesc ]
  set i                       0
  set TempCount               0
  
  set temp                    [lindex  $TempList $i ]
  while { $temp != "" } {
    set InterfaceIndexs($TempCount) $temp
    incr i
    lappend _ENTS(interfaces) [lindex $TempList $i]
    incr i
    incr TempCount
    set temp [lindex  $TempList $i ]
  }
  set _ENTS(interface) [expr $TempCount-1]
}

# 
# Routine Description:
# 
#   Initialize all the global setting, including fonts, colors, frames.
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsInitGlobals {} {
  global _ENTS
  global RivlKeys TclKeys
  global EmsProtocols

  #
  # Init Configurations
  #
  set _ENTS(pwd)                 [pwd]
  set _ENTS(case_root)           [file join $_ENTS(pwd) TestCase]
  set _ENTS(verbose_levels)      [ list QUIET MINIMAL DEFAULT NOISY EXHAUSTIVE ]
  set _ENTS(verbose_level)       DEFAULT

  set _ENTS(communication_types) [list MNP]
  set _ENTS(communication_type)  MNP
  set _ENTS(target_platform_bit_types) [list 32 64 ]
  set _ENTS(target_platform_bit_type)  32

  set _ENTS(init_status)         "Intel UEFI SCT EMS 0.90"
  set _ENTS(DefaultStatus)       $_ENTS(init_status)
  set _ENTS(status)              $_ENTS(DefaultStatus)
  set _ENTS(blockflag)           0
  
  set EmsProtocols  { MNP  ARP  IP4  IP4Config  TCP4  UDP4  DHCP4  MTFTP4  IP6  IP6Config  TCP6  UDP6  DHCP6  MTFTP6 }

  EmsLoadDefaultConfigure
  EmsInitGuiConfigure
  EmsInitKeywords
  EmsInitRemoteValidationConfigure 
}

# 
# Routine Description:
# 
#   Initialize the interface configuration
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
#
proc EmsInterfaceConfigForm {} {
  global _ENTS InterfaceIndexs EmsAdapterName GuiColors TempInterface ReadMe

  catch "destroy .emsInterfaceConfig"
  toplevel .emsInterfaceConfig -background $GuiColors(background)
  wm withdraw .emsInterfaceConfig
  wm title .emsInterfaceConfig "EMS Interface Configure"

  labelframe .emsInterfaceConfig.interface -text "Interface" -padx 4 -pady 4 -background $GuiColors(background)
  pack .emsInterfaceConfig.interface -side top -padx 4 -pady 4 -expand yes -fill x -anchor w
  spinbox .emsInterfaceConfig.interface.sb_interface \
          -values $_ENTS(interfaces) \
          -textvariable TempInterface -state readonly -wrap 1 \
          -background $GuiColors(background) \
          -width 40 
  pack .emsInterfaceConfig.interface.sb_interface -side left -expand yes -fill x

  set ReadMe "Please choose the host interface. Once the interface be chosen it can not be changed"
  labelframe .emsInterfaceConfig.readMe -text "" -padx 4 -pady 4 -background $GuiColors(background)
  pack .emsInterfaceConfig.readMe -side top -padx 4 -pady 4 -expand yes -fill x -anchor w
  text .emsInterfaceConfig.readMe.l_readMe \
        -width 40 -height 2 -background $GuiColors(background) \
		-relief sunken -font EmsBasicReadonlyFont -state normal 
  pack .emsInterfaceConfig.readMe.l_readMe -side left -fill x
  .emsInterfaceConfig.readMe.l_readMe insert end $ReadMe
  .emsInterfaceConfig.readMe.l_readMe see end
  .emsInterfaceConfig.readMe.l_readMe configure -state disabled

  set Cmd {
	        global _ENTS EmsAdapterName InterfaceIndexs
            set _ENTS(interface) [lsearch $_ENTS(interfaces) "$TempInterface"]
            set TempName \\Device\\NPF_$EmsAdapterName($InterfaceIndexs($_ENTS(interface)))
            Interface  $InterfaceIndexs($_ENTS(interface)) $TempName
            destroy .emsInterfaceConfig
          }

  button .emsInterfaceConfig.b_ok -background $GuiColors(background) -command $Cmd -text OK -height 1 -width 10
  pack .emsInterfaceConfig.b_ok -side right -fill none -padx 4 -pady 4
  button .emsInterfaceConfig.b_cancel -background $GuiColors(background) -command "exit" -text Cancel -height -1 -width 10
  pack .emsInterfaceConfig.b_cancel -side right -fill none -padx 4 -pady 4

  wm deiconify .emsInterfaceConfig
  wm resizable .emsInterfaceConfig 0 0
  raise .emsInterfaceConfig
  update
  wm minsize .emsInterfaceConfig [winfo width .emsInterfaceConfig] [winfo height .emsInterfaceConfig]
  wm maxsize .emsInterfaceConfig [winfo width .emsInterfaceConfig] [winfo height .emsInterfaceConfig]
  focus .emsInterfaceConfig
  grab .emsInterfaceConfig
  tkwait window .emsInterfaceConfig
}

proc EmsHostInit {} {
  global _ENTS InterfaceIndexs EmsAdapterName

  EmsInterfaceConfigForm

  set _ENTS(hostmac)   [GetHostMac]
  catch { OpenDev mnp }
}

