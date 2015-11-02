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

  SimpleTextIn.h

Abstract:

  Simple Text Out protocol from the EFI 1.0 specification.

--*/

#ifndef _SIMPLE_TEXT_OUT_PROTOCOL_FOR_TEST_H_
#define _SIMPLE_TEXT_OUT_PROTOCOL_FOR_TEST_H_

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID \
  { \
    0x387477c2, 0x69c7, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b } \
  }

typedef struct _EFI_SIMPLE_TEXT_OUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

#define EFI_TEXT_ATTR(f, b)       ((f) | ((b) << 4))

/**
  Reset the text output device hardware and optionaly run diagnostics

  @param  This                 The protocol instance pointer.
  @param  ExtendedVerification Driver may perform more exhaustive verfication
                               operation of the device during reset.

  @retval EFI_SUCCESS          The text output device was reset.
  @retval EFI_DEVICE_ERROR     The text output device is not functioning correctly and
                               could not be reset.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_RESET)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN BOOLEAN                                ExtendedVerification
  );

/**
  Write a string to the output device.

  @param  This   The protocol instance pointer.
  @param  String The NULL-terminated string to be displayed on the output
                 device(s). All output devices must also support the Unicode
                 drawing character codes defined in this file.

  @retval EFI_SUCCESS             The string was output to the device.
  @retval EFI_DEVICE_ERROR        The device reported an error while attempting to output
                                  the text.
  @retval EFI_UNSUPPORTED         The output device's mode is not currently in a
                                  defined text mode.
  @retval EFI_WARN_UNKNOWN_GLYPH  This warning code indicates that some of the
                                  characters in the string could not be
                                  rendered and were skipped.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_STRING)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN CHAR16                                 *String
  );

/**
  Verifies that all characters in a string can be output to the
  target device.

  @param  This   The protocol instance pointer.
  @param  String The NULL-terminated string to be examined for the output
                 device(s).

  @retval EFI_SUCCESS      The device(s) are capable of rendering the output string.
  @retval EFI_UNSUPPORTED  Some of the characters in the string cannot be
                           rendered by one or more of the output devices mapped
                           by the EFI handle.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_TEST_STRING)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN CHAR16                                 *String
  );

/**
  Returns information for an available text mode that the output device(s)
  supports.

  @param  This       The protocol instance pointer.
  @param  ModeNumber The mode number to return information on.
  @param  Columns    Returns the geometry of the text output device for the
                     requested ModeNumber.
  @param  Rows       Returns the geometry of the text output device for the
                     requested ModeNumber.

  @retval EFI_SUCCESS      The requested mode information was returned.
  @retval EFI_DEVICE_ERROR The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED  The mode number was not valid.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_QUERY_MODE)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN UINTN                                  ModeNumber,
  OUT UINTN                                 *Columns,
  OUT UINTN                                 *Rows
  );

/**
  Sets the output device(s) to a specified mode.

  @param  This       The protocol instance pointer.
  @param  ModeNumber The mode number to set.

  @retval EFI_SUCCESS      The requested text mode was set.
  @retval EFI_DEVICE_ERROR The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED  The mode number was not valid.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_MODE)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN UINTN                                  ModeNumber
  );

/**
  Sets the background and foreground colors for the OutputString () and
  ClearScreen () functions.

  @param  This      The protocol instance pointer.
  @param  Attribute The attribute to set. Bits 0..3 are the foreground color, and
                    bits 4..6 are the background color. All other bits are undefined
                    and must be zero. The valid Attributes are defined in this file.

  @retval EFI_SUCCESS       The attribute was set.
  @retval EFI_DEVICE_ERROR  The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED   The attribute requested is not defined.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN UINTN                                  Attribute
  );

/**
  Clears the output device(s) display to the currently selected background
  color.

  @param  This              The protocol instance pointer.

  @retval  EFI_SUCCESS      The operation completed successfully.
  @retval  EFI_DEVICE_ERROR The device had an error and could not complete the request.
  @retval  EFI_UNSUPPORTED  The output device is not in a valid text mode.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_CLEAR_SCREEN)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *This
  );

/**
  Sets the current coordinates of the cursor position

  @param  This        The protocol instance pointer.
  @param  Column      The position to set the cursor to. Must be greater than or
                      equal to zero and less than the number of columns and rows
                      by QueryMode ().
  @param  Row         The position to set the cursor to. Must be greater than or
                      equal to zero and less than the number of columns and rows
                      by QueryMode ().

  @retval EFI_SUCCESS      The operation completed successfully.
  @retval EFI_DEVICE_ERROR The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED  The output device is not in a valid text mode, or the
                           cursor position is invalid for the current mode.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN UINTN                                  Column,
  IN UINTN                                  Row
  );

/**
  Makes the cursor visible or invisible

  @param  This    The protocol instance pointer.
  @param  Visible If TRUE, the cursor is set to be visible. If FALSE, the cursor is
                  set to be invisible.

  @retval EFI_SUCCESS      The operation completed successfully.
  @retval EFI_DEVICE_ERROR The device had an error and could not complete the
                           request, or the device does not support changing
                           the cursor mode.
  @retval EFI_UNSUPPORTED  The output device is not in a valid text mode.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_TEXT_ENABLE_CURSOR)(
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN BOOLEAN                                Visible
  );

/**
  @par Data Structure Description:
  Mode Structure pointed to by Simple Text Out protocol.
**/
typedef struct {
  ///
  /// The number of modes supported by QueryMode () and SetMode ().
  ///
  INT32   MaxMode;

  //
  // current settings
  //

  ///
  /// The text mode of the output device(s).
  ///
  INT32   Mode;
  ///
  /// The current character output attribute.
  ///
  INT32   Attribute;
  ///
  /// The cursor's column.
  ///
  INT32   CursorColumn;
  ///
  /// The cursor's row.
  ///
  INT32   CursorRow;
  ///
  /// The cursor is currently visbile or not.
  ///
  BOOLEAN CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;

///
/// The SIMPLE_TEXT_OUTPUT protocol is used to control text-based output devices.
/// It is the minimum required protocol for any handle supplied as the ConsoleOut
/// or StandardError device. In addition, the minimum supported text mode of such
/// devices is at least 80 x 25 characters.
///
struct _EFI_SIMPLE_TEXT_OUT_PROTOCOL {
  EFI_TEXT_RESET                Reset;

  EFI_TEXT_STRING               OutputString;
  EFI_TEXT_TEST_STRING          TestString;

  EFI_TEXT_QUERY_MODE           QueryMode;
  EFI_TEXT_SET_MODE             SetMode;
  EFI_TEXT_SET_ATTRIBUTE        SetAttribute;

  EFI_TEXT_CLEAR_SCREEN         ClearScreen;
  EFI_TEXT_SET_CURSOR_POSITION  SetCursorPosition;
  EFI_TEXT_ENABLE_CURSOR        EnableCursor;

  ///
  /// Pointer to SIMPLE_TEXT_OUTPUT_MODE data.
  ///
  EFI_SIMPLE_TEXT_OUTPUT_MODE   *Mode;
};

extern EFI_GUID gBlackBoxEfiSimpleTextOutProtocolGuid;

#endif
