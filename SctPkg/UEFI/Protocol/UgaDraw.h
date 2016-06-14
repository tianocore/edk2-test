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

  Copyright 2006, 2007, 2008, 2009, 2010, 2011 Unified EFI, Inc. All
  Rights Reserved, subject to all existing rights in all
  matters included within this Test Suite, to which United
  EFI, Inc. makes no claim of right.

  Copyright (c) 2014, ARM Ltd. All rights reserved.<BR>

--*/
/*++

Module Name:

  UgaDraw.h

Abstract:

--*/

#ifndef __EFI_UGA_PROTOCOL_FOR_TEST_H__
#define __EFI_UGA_PROTOCOL_FOR_TEST_H__

typedef struct _EFI_UGA_DRAW_PROTOCOL EFI_UGA_DRAW_PROTOCOL;

typedef struct {
  UINT8 Blue;
  UINT8 Green;
  UINT8 Red;
  UINT8 Reserved;
} EFI_UGA_PIXEL;

/**
  Return the current video mode information.

  @param  This                  The EFI_UGA_DRAW_PROTOCOL instance.
  @param  HorizontalResolution  The size of video screen in pixels in the X dimension.
  @param  VerticalResolution    The size of video screen in pixels in the Y dimension.
  @param  ColorDepth            Number of bits per pixel, currently defined to be 32.
  @param  RefreshRate           The refresh rate of the monitor in Hertz.

  @retval EFI_SUCCESS           Mode information returned.
  @retval EFI_NOT_STARTED       Video display is not initialized. Call SetMode ()
  @retval EFI_INVALID_PARAMETER One of the input args was NULL.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_GET_MODE)(
  IN  EFI_UGA_DRAW_PROTOCOL *This,
  OUT UINT32                *HorizontalResolution,
  OUT UINT32                *VerticalResolution,
  OUT UINT32                *ColorDepth,
  OUT UINT32                *RefreshRate
  );

/**
  Set the current video mode information.

  @param  This                 The EFI_UGA_DRAW_PROTOCOL instance.
  @param  HorizontalResolution The size of video screen in pixels in the X dimension.
  @param  VerticalResolution   The size of video screen in pixels in the Y dimension.
  @param  ColorDepth           Number of bits per pixel, currently defined to be 32.
  @param  RefreshRate          The refresh rate of the monitor in Hertz.

  @retval EFI_SUCCESS          Mode information returned.
  @retval EFI_NOT_STARTED      Video display is not initialized. Call SetMode ()

**/
typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_SET_MODE)(
  IN  EFI_UGA_DRAW_PROTOCOL *This,
  IN  UINT32                HorizontalResolution,
  IN  UINT32                VerticalResolution,
  IN  UINT32                ColorDepth,
  IN  UINT32                RefreshRate
  );

///
/// Enumration value for actions of Blt operations.
///
typedef enum {
  EfiUgaVideoFill,          ///< Write data from the  BltBuffer pixel (SourceX, SourceY)
                            ///< directly to every pixel of the video display rectangle
                            ///< (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
                            ///< Only one pixel will be used from the BltBuffer. Delta is NOT used.

  EfiUgaVideoToBltBuffer,   ///< Read data from the video display rectangle
                            ///< (SourceX, SourceY) (SourceX + Width, SourceY + Height) and place it in
                            ///< the BltBuffer rectangle (DestinationX, DestinationY )
                            ///< (DestinationX + Width, DestinationY + Height). If DestinationX or
                            ///< DestinationY is not zero then Delta must be set to the length in bytes
                            ///< of a row in the BltBuffer.

  EfiUgaBltBufferToVideo,   ///< Write data from the  BltBuffer rectangle
                            ///< (SourceX, SourceY) (SourceX + Width, SourceY + Height) directly to the
                            ///< video display rectangle (DestinationX, DestinationY)
                            ///< (DestinationX + Width, DestinationY + Height). If SourceX or SourceY is
                            ///< not zero then Delta must be set to the length in bytes of a row in the
                            ///< BltBuffer.

  EfiUgaVideoToVideo,       ///< Copy from the video display rectangle (SourceX, SourceY)
                            ///< (SourceX + Width, SourceY + Height) .to the video display rectangle
                            ///< (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
                            ///< The BltBuffer and Delta  are not used in this mode.

  EfiUgaBltMax              ///< Maxmimum value for enumration value of Blt operation. If a Blt operation
                            ///< larger or equal to this enumration value, it is invalid.
} EFI_UGA_BLT_OPERATION;

/**
    Blt a rectangle of pixels on the graphics screen.

    @param[in] This          - Protocol instance pointer.
    @param[in] BltBuffer     - Buffer containing data to blit into video buffer. This
                               buffer has a size of Width*Height*sizeof(EFI_UGA_PIXEL)
    @param[in] BltOperation  - Operation to perform on BlitBuffer and video memory
    @param[in] SourceX       - X coordinate of source for the BltBuffer.
    @param[in] SourceY       - Y coordinate of source for the BltBuffer.
    @param[in] DestinationX  - X coordinate of destination for the BltBuffer.
    @param[in] DestinationY  - Y coordinate of destination for the BltBuffer.
    @param[in] Width         - Width of rectangle in BltBuffer in pixels.
    @param[in] Height        - Hight of rectangle in BltBuffer in pixels.
    @param[in] Delta         - OPTIONAL

    @retval EFI_SUCCESS           - The Blt operation completed.
    @retval EFI_INVALID_PARAMETER - BltOperation is not valid.
    @retval EFI_DEVICE_ERROR      - A hardware error occured writting to the video buffer.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_UGA_DRAW_PROTOCOL_BLT)(
  IN  EFI_UGA_DRAW_PROTOCOL                   * This,
  IN  EFI_UGA_PIXEL                           * BltBuffer, OPTIONAL
  IN  EFI_UGA_BLT_OPERATION                   BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta         OPTIONAL
  );

///
/// This protocol provides a basic abstraction to set video modes and
/// copy pixels to and from the graphics controller's frame buffer.
///
struct _EFI_UGA_DRAW_PROTOCOL {
  EFI_UGA_DRAW_PROTOCOL_GET_MODE  GetMode;
  EFI_UGA_DRAW_PROTOCOL_SET_MODE  SetMode;
  EFI_UGA_DRAW_PROTOCOL_BLT       Blt;
};

extern EFI_GUID gBlackBoxEfiUgaDrawProtocolGuid;

#endif
