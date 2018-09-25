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
#     Implementation for EMS Configuration form function
#

if {[info exist CONFIGURE_TCL] == 1} {
  return
}
set CONFIGURE_TCL 1

set DefaultConfFile         "Init.conf"
set DefaultConfFileMagic    "\[Default Configuration\]"

# 
# Routine Description:
# 
#   Validate the root of the case
# 
# Arguments:
# 
#   CaseRoot - The case root
# 
# Returns:
# 
#   1 Valid
#   0 Not valid
# 
proc ValidateCaseRoot {CaseRoot} {
  if {[file exists $CaseRoot]} {
    return 1
  } else {
    EmsGuiError "Case Root dos not exist!"
    return 0
  }
}

# 
# Routine Description:
# 
#   Validate Communication type
# 
# Arguments:
# 
#   Type - The commnunication type
# 
# Returns:
# 
#   0 Not valid
#   1 Valid
# 
proc ValidateCommunicationType {Type} {
  global _ENTS

  if {[lsearch $_ENTS(communication_types) $Type] != -1} {
    return 1
  } else {
    EmsGuiError "Don't support communication type : $Type"
    return 0
  }
}

# 
# Routine Description:
# 
#   Validate the target is 32 bit or 64 bit
# 
# Arguments:
# 
#   Bits - 32 bit or 64 bit
# 
# Returns:
# 
#   1 Valid
#   0 Not valid
# 
proc ValidateTargetBits {Bits} {
  global _ENTS

  if {[lsearch $_ENTS(target_platform_bit_types) $Bits] != -1} {
    return 1
  } else {
    EmsGuiError "Don't support $Bits bit target"
    return 0
  }
}

# 
# Routine Description:
# 
#   Validate a MAC address.
# 
# Arguments:
# 
#   Mac : The input MAC address.
# 
# Returns:
# 
#   1, it is a valid MAC  
#   0, it is an invalid MAC
# 
proc ValidateMac  { Mac } {
  set TempList [split $Mac :]
  set TempNum [llength $TempList ]
  if { $TempNum != 6 } {
    return 0
  }
  foreach str $TempList {
    if [string is xdigit -strict $str] {
    } else {
      return 0
    }
    if {[subst 0x$str] <0 || [subst 0x$str]>255} {
      return 0
    }
  }
  return 1
}

# 
# Routine Description:
# 
#   ENTS Preference configure form.
#   A GUI for user to configure the followings:
#     ENTS testcase root directory
#     ENTS communication type (MNP/IP4/Serial)
#     Log verbose level
#     Target MAC address
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsConfigForm { } {

  global _ENTS GuiColors GuiBoxs GuiFrames 
  global TempCaseRoot TempCommunicationType TempTargetMac OldTargetMac TempVerboseLevel TempTargetBits
  global InterfaceIndexs EmsAdapterName Mac
  
  set TempCaseRoot            $_ENTS(case_root)
  set TempCommunicationType   $_ENTS(communication_type)
  set TempTargetBits          $_ENTS(target_platform_bit_type)
  set TempTargetMac           [GetTargetMac]
  
  if {[EmsTestIsRunning] == 1} {
    tk_messageBox -message "Can not configure EMS when test is running" -type ok 
    return
  }

  catch "destroy .emsConfig"

  toplevel .emsConfig  -background $GuiColors(background)
  wm withdraw .emsConfig
  wm title .emsConfig "EMS Preference"

  labelframe .emsConfig.lf_case_root -background $GuiColors(background) -text "ENTS Testcase Root Dir ..."  -padx 4 -pady 4
  pack .emsConfig.lf_case_root -side top -padx 4 -pady 4 -fill x
  
  entry .emsConfig.lf_case_root.e_case_root -width  40 \
        -background $GuiColors(background) -relief sunken \
        -textvariable TempCaseRoot 
  pack .emsConfig.lf_case_root.e_case_root -side left -fill x

  button .emsConfig.lf_case_root.b_case_root -text "... " \
         -background $GuiColors(background) -command \
     {
      set tt_case_root $TempCaseRoot
      set tt_case_root [tk_chooseDirectory -initialdir $tt_case_root) \
                                          -parent .emsConfig \
                                           -title "Set Root Directory" \
                                           -mustexist true ]; 
      if {$tt_case_root != ""} {
        set TempCaseRoot $tt_case_root
      } 
     }
  pack .emsConfig.lf_case_root.b_case_root -side left -fill x

  labelframe .emsConfig.lf_type -text "Communication Type" \
             -padx 4 -pady 4  -background $GuiColors(background)
  pack .emsConfig.lf_type -side top -padx 4 -pady 4 -expand yes -fill x -anchor w

  spinbox .emsConfig.lf_type.sb_type -values $_ENTS(communication_types) \
          -textvariable TempCommunicationType -state readonly -wrap 1 \
          -background $GuiColors(background)
  pack .emsConfig.lf_type.sb_type -side left -expand yes -fill x 
#  set TempCommunicationType $_ENTS(communication_type)

  set OldTargetMac [GetTargetMac]
  labelframe .emsConfig.lf_target_mac -text "New Target MAC" \
             -padx 4 -pady 4 -background $GuiColors(background) 
  pack .emsConfig.lf_target_mac -side top -padx 4 -pady 4 -expand yes -fill x -anchor w
  set Mac(0) [lindex [split $TempTargetMac :] 0]
  set Mac(1) [lindex [split $TempTargetMac :] 1]
  set Mac(2) [lindex [split $TempTargetMac :] 2]
  set Mac(3) [lindex [split $TempTargetMac :] 3]
  set Mac(4) [lindex [split $TempTargetMac :] 4]
  set Mac(5) [lindex [split $TempTargetMac :] 5]
  entry .emsConfig.lf_target_mac.e_target_mac_0 \
          -textvariable Mac(0) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_0 -side left -expand yes -fill x
  entry .emsConfig.lf_target_mac.e_target_mac_1 \
          -textvariable Mac(1) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_1 -side left -expand yes -fill x
  entry .emsConfig.lf_target_mac.e_target_mac_2 \
          -textvariable Mac(2) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_2 -side left -expand yes -fill x
  entry .emsConfig.lf_target_mac.e_target_mac_3 \
          -textvariable Mac(3) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_3 -side left -expand yes -fill x
  entry .emsConfig.lf_target_mac.e_target_mac_4 \
          -textvariable Mac(4) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_4 -side left -expand yes -fill x
  entry .emsConfig.lf_target_mac.e_target_mac_5 \
          -textvariable Mac(5) -background $GuiColors(background) -width 1 -justify right
  pack .emsConfig.lf_target_mac.e_target_mac_5 -side left -expand yes -fill x

  labelframe .emsConfig.lf_target_mac_old -text "Old Target MAC" \
             -padx 4 -pady 4 -background $GuiColors(background)
  pack .emsConfig.lf_target_mac_old -side top -padx 4 -pady 4 -expand yes -fill x -anchor w
  entry .emsConfig.lf_target_mac_old.e_target_mac_old \
          -textvariable OldTargetMac -relief flat -state disable
  pack .emsConfig.lf_target_mac_old.e_target_mac_old

	labelframe .emsConfig.lf_target_bits -text "Target Platform Bits" \
             -padx 4 -pady 4  -background $GuiColors(background)
  pack .emsConfig.lf_target_bits -side top -padx 4 -pady 4 -expand yes -fill x -anchor w

  spinbox .emsConfig.lf_target_bits.sb_type -values $_ENTS(target_platform_bit_types) \
          -textvariable TempTargetBits -state readonly -wrap 1 \
          -background $GuiColors(background)
  pack .emsConfig.lf_target_bits.sb_type -side left -expand yes -fill x 
  set TempTargetBits $_ENTS(target_platform_bit_type)

  set temp {
             set TempTargetMac "$Mac(0):$Mac(1):$Mac(2):$Mac(3):$Mac(4):$Mac(5)"

             if {![ValidateCaseRoot $TempCaseRoot]} {
               EmsGuiError "$TempCaseRoot is not exists!"
               EmsConfigForm
		     }
			 if {![ValidateCommunicationType $TempCommunicationType]} {
               EmsGuiError "$TempCommunicationType is not supported!"
               EmsConfigForm
			 }
			 if {![ValidateMac $TempTargetMac]} {
			   EmsGuiError "Target MAC error!"
               EmsConfigForm
		     }
             if {![ValidateTargetBits $TempTargetBits]} {
               EmsGuiError "$TempTargetBis is not supported!"
               EmsConfigForm
			 }

			 if {[string compare $_ENTS(communication_type) $TempCommunicationType] != 0} {
			   set _ENTS(communication_type) $TempCommunicationType
			 }
			 if {[string compare $_ENTS(case_root) $TempCaseRoot] != 0} {
               set _ENTS(case_root)          $TempCaseRoot
               SetCaseRoot $TempCaseRoot
               EmsLeftFrameInit
			 }
			 if {[string compare $_ENTS(target_platform_bit_type) $TempTargetBits] != 0} {
			   set _ENTS(target_platform_bit_type)      $TempTargetBits
			   SetTargetBits $TempTargetBits
			 }
			 if {$OldTargetMac != $TempTargetMac} {
               SetTargetMac $TempTargetMac
			   TclTargetCleanup [GetTargetMac]
			 }
			 EmsSaveDefaultConfigure
             destroy .emsConfig; 
           }
  button .emsConfig.b_ok -background $GuiColors(background) \
        -command  $temp \
        -text OK \
        -height 1 -width 10

  button .emsConfig.b_cancel -background $GuiColors(background) \
        -command {destroy .emsConfig} \
        -text Cancel \
        -height 1 -width 10
  pack .emsConfig.b_cancel .emsConfig.b_ok -side right -fill none -padx 4 -pady 4

  set x [expr [winfo rootx $GuiFrames(main)] + 30]
  set y [expr [winfo rooty $GuiFrames(main)] + 30]
  wm geometry .emsConfig +$x+$y
  wm deiconify .emsConfig
  wm resizable .emsConfig  0 0
  raise .emsConfig
  update
  wm minsize .emsConfig [winfo width .emsConfig] [winfo height .emsConfig]
  wm maxsize .emsConfig [winfo width .emsConfig] [winfo height .emsConfig]
  focus .emsConfig
  grab  .emsConfig
  tkwait window .emsConfig
}

# 
# Routine Description:
# 
#   Configurate the EMS with raw data
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsRawConfigure {} {
  global _ENTS

  SetCaseRoot      $_ENTS(case_root)
  CaseVerboseLevel $_ENTS(verbose_level)
  SetTargetMac     "00:00:00:00:00:00"
  SetTargetBits    32
}

# 
# Routine Description:
# 
#   Load EMS default configuration
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsLoadDefaultConfigure {} {
  global _ENTS DefaultConfFileMagic DefaultConfFile

  EmsRawConfigure

  if {[file exists $DefaultConfFile]} {
    if {[catch {open $DefaultConfFile r} ifile]} {
      EmsGuiError "Can not open default.conf"
      return
    }

    gets $ifile magic
    if {[string compare $magic $DefaultConfFileMagic] == 0} {
      set CaseRoot                  [lindex [split [gets $ifile] "="] 1]
      set CommunicationType         [lindex [split [gets $ifile] "="] 1]
      set DefaultTargetMac          [lindex [split [gets $ifile] "="] 1]
      set TargetBits                [lindex [split [gets $ifile] "="] 1]
						
	  if {[ValidateCaseRoot $CaseRoot] && \
		  [ValidateCommunicationType $CommunicationType] && \
		  [ValidateMac $DefaultTargetMac] && \
		  [ValidateTargetBits $TargetBits]} {
        set _ENTS(case_root)                $CaseRoot
        set _ENTS(communication_type)       $CommunicationType
        set _ENTS(target_platform_bit_type) $TargetBits

        SetCaseRoot      $CaseRoot
        SetTargetMac     $DefaultTargetMac
        SetTargetBits    $TargetBits
      } else {
        EmsGuiError "Init configure file format error!"
	  }
	}
    close $ifile
  }
}

# 
# Routine Description:
# 
#   Save current configuration as default configturation
# 
# Arguments:
# 
#   None.
# 
# Returns:
# 
#   None.
# 
proc EmsSaveDefaultConfigure {} {
  global _ENTS DefaultConfFileMagic DefaultConfFile

  if {[file exists $DefaultConfFile]} {
    if {![file writable $DefaultConfFile]} {
      file attributes $DefaultConfFile -readonly 0
    }
  }

  if [catch {open $DefaultConfFile w} ofile] {
    puts stderr "Can not open $DefaultConfFile"
    return
  }
  puts $ofile $DefaultConfFileMagic
  puts $ofile [format "CASE_ROOT_DIR      =%s" $_ENTS(case_root)]
  puts $ofile [format "COMMUNICATION_TYPE =%s" $_ENTS(communication_type)]
  puts $ofile [format "TARGET_MAC         =%s" [GetTargetMac]]
  puts $ofile [format "TARGET_BITS        =%s" $_ENTS(target_platform_bit_type)]

  close $ofile
}

