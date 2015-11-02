/*++
  The material contained herein is not a license, either        
  expressly or impliedly, to any intellectual property owned    
  or controlled by any of the authors or developers of this     
  material or to any contribution thereto. The material         
  contained herein is provided on an "AS IS" basis and, to the  
  maximum extent permitted by applicable law, this information  
  is provided AS IS AND WITH ALL FAULTS, and the authors and    
  developers of this material hereby disclaim all other         
  warranties and conditions, either express, implied or         
  statutory, including, but not limited to, any (if any)        
  implied warranties, duties or conditions of merchantability,  
  of fitness for a particular purpose, of accuracy or           
  completeness of responses, of results, of workmanlike         
  effort, of lack of viruses and of lack of negligence, all     
  with regard to this material and any contribution thereto.    
  Designers must not rely on the absence or characteristics of  
  any features or instructions marked "reserved" or             
  "undefined." The Unified EFI Forum, Inc. reserves any         
  features or instructions so marked for future definition and  
  shall have no responsibility whatsoever for conflicts or      
  incompatibilities arising from future changes to them. ALSO,  
  THERE IS NO WARRANTY OR CONDITION OF TITLE, QUIET ENJOYMENT,  
  QUIET POSSESSION, CORRESPONDENCE TO DESCRIPTION OR            
  NON-INFRINGEMENT WITH REGARD TO THE TEST SUITE AND ANY        
  CONTRIBUTION THERETO.                                         
                                                                
  IN NO EVENT WILL ANY AUTHOR OR DEVELOPER OF THIS MATERIAL OR  
  ANY CONTRIBUTION THERETO BE LIABLE TO ANY OTHER PARTY FOR     
  THE COST OF PROCURING SUBSTITUTE GOODS OR SERVICES, LOST      
  PROFITS, LOSS OF USE, LOSS OF DATA, OR ANY INCIDENTAL,        
  CONSEQUENTIAL, DIRECT, INDIRECT, OR SPECIAL DAMAGES WHETHER   
  UNDER CONTRACT, TORT, WARRANTY, OR OTHERWISE, ARISING IN ANY  
  WAY OUT OF THIS OR ANY OTHER AGREEMENT RELATING TO THIS       
  DOCUMENT, WHETHER OR NOT SUCH PARTY HAD ADVANCE NOTICE OF     
  THE POSSIBILITY OF SUCH DAMAGES.                              
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++         

Module Name:

  SimpleTextInputEx.h

Abstract:

  Simple Text Input Ex Protocol from the UEFI 2.1 specification.

--*/

#ifndef _SIMPLE_TEXT_INPUT_EX_PROTOCOL_H_
#define _SIMPLE_TEXT_INPUT_EX_PROTOCOL_H_


//
// Global ID for the Simple Text Input Ex Protocol
//
#define EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL_GUID \
  {0xdd9e7534, 0x7762, 0x4698, 0x8c, 0x14, 0xf5, 0x85, 0x17, 0xa6, 0x25, 0xaa}

typedef struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;;


#define EFI_SHIFT_STATE_VALID       0x80000000
#define EFI_RIGHT_SHIFT_PRESSED     0x00000001
#define EFI_LEFT_SHIFT_PRESSED      0x00000002
#define EFI_RIGHT_CONTROL_PRESSED   0x00000004
#define EFI_LEFT_CONTROL_PRESSED    0x00000008
#define EFI_RIGHT_ALT_PRESSED       0x00000010
#define EFI_LEFT_ALT_PRESSED        0x00000020
#define EFI_RIGHT_LOGO_PRESSED      0x00000040
#define EFI_LEFT_LOGO_PRESSED       0x00000080
#define EFI_MENU_KEY_PRESSED        0x00000100
#define EFI_SYS_REQ_PRESSED         0x00000200


typedef UINT8  EFI_KEY_TOGGLE_STATE;

#define EFI_TOGGLE_STATE_VALID      0x80
#define EFI_KEY_STATE_EXPOSED       0x40
#define EFI_SCROLL_LOCK_ACTIVE      0x01
#define EFI_NUM_LOCK_ACTIVE         0x02
#define EFI_CAPS_LOCK_ACTIVE        0x04

#define EFI_TOGGLE_UNSUPPORTED1     0x08
#define EFI_TOGGLE_UNSUPPORTED2     0x10
#define EFI_TOGGLE_UNSUPPORTED3     0x20
#define EFI_TOGGLE_UNSUPPORTED4     0x40

#define TEST_SCAN_UP        0x01
#define TEST_SCAN_DOWN      0x02
#define TEST_SCAN_RIGHT     0x03
#define TEST_SCAN_LEFT      0x04
#define TEST_SCAN_HOME      0x05
#define TEST_SCAN_END       0x06
#define TEST_SCAN_INSERT    0x07
#define TEST_SCAN_DELETE    0x08
#define TEST_SCAN_PAGE_UP   0x09
#define TEST_SCAN_PAGE_DOWN 0x0a
#define TEST_SCAN_F1        0x0b
#define TEST_SCAN_F2        0x0c
#define TEST_SCAN_F3        0x0d
#define TEST_SCAN_F4        0x0e
#define TEST_SCAN_F5        0x0f
#define TEST_SCAN_F6        0x10
#define TEST_SCAN_F7        0x11
#define TEST_SCAN_F8        0x12
#define TEST_SCAN_F9        0x13
#define TEST_SCAN_F10       0x14
#define TEST_SCAN_F11       0x15
#define TEST_SCAN_F12       0x16
#define TEST_SCAN_ESC       0x17
#define TEST_SCAN_F13       0x68
#define TEST_SCAN_F14       0x69
#define TEST_SCAN_F15       0x6A
#define TEST_SCAN_F16       0x6B
#define TEST_SCAN_F17       0X6C
#define TEST_SCAN_F18       0X6D
#define TEST_SCAN_F19       0X6E
#define TEST_SCAN_F20       0X6F
#define TEST_SCAN_F21       0X70
#define TEST_SCAN_F22       0X71
#define TEST_SCAN_F23       0X72
#define TEST_SCAN_F24       0X73
#define TEST_SCAN_MUTE      0X7F
#define TEST_SCAN_VOLUME_UP 0X80
#define TEST_SCAN_VOLUME_DOWN      0X81
#define TEST_SCAN_BRIGHTNESS_UP    0X100
#define TEST_SCAN_BRIGHTNESS_DOWN  0X101
#define TEST_SCAN_SUSPEND          0X102
#define TEST_SCAN_HIBERNATE        0X103
#define TEST_SCAN_TOGGLE_DISPLAY   0X104
#define TEST_SCAN_RECOVERY         0X105
#define TEST_SCAN_EJECT            0X106




typedef struct EFI_KEY_STATE {
UINT32                                  KeyShiftState;
EFI_KEY_TOGGLE_STATE                    KeyToggleState;
} EFI_KEY_STATE;


typedef struct {
EFI_INPUT_KEY                           Key;
EFI_KEY_STATE                           KeyState;
} EFI_KEY_DATA;


typedef
EFI_STATUS
(EFIAPI *EFI_KEY_NOTIFY_FUNCTION) (
IN EFI_KEY_DATA                         *KeyData
);


typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_RESET_EX) (
IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
IN BOOLEAN                              ExtendedVerification
);


typedef
EFI_STATUS
(EFIAPI *EFI_INPUT_READ_KEY_EX) (
IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
OUT EFI_KEY_DATA                        *KeyData
);


typedef
EFI_STATUS
(EFIAPI *EFI_SET_STATE) (
IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
IN EFI_KEY_TOGGLE_STATE                 *KeyToggleState
);


typedef
EFI_STATUS
(EFIAPI *EFI_REGISTER_KEYSTROKE_NOTIFY) (
IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
IN EFI_KEY_DATA                         *KeyData,
IN EFI_KEY_NOTIFY_FUNCTION              KeyNotificationFunction,
OUT VOID                                **NotifyHandle
);


typedef
EFI_STATUS
(EFIAPI *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
IN VOID                                 *NotificationHandle
);

//
// Interface structure for the Simple Text Input Ex Protocol
//
struct _EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
EFI_INPUT_RESET_EX                      Reset;
EFI_INPUT_READ_KEY_EX                   ReadKeyStrokeEx;
EFI_EVENT                               WaitForKeyEx;
EFI_SET_STATE                           SetState;
EFI_REGISTER_KEYSTROKE_NOTIFY           RegisterKeyNotify;
EFI_UNREGISTER_KEYSTROKE_NOTIFY         UnregisterKeyNotify;
};

extern EFI_GUID gBlackBoxEfiSimpleTextInputExProtocolGuid;

#endif
