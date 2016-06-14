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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  UgaDrawBBTestMain.h

Abstract:

  BB test header file of UGA Draw Protocol

--*/


#ifndef _UGA_DRAW_BBTEST_H_
#define _UGA_DRAW_BBTEST_H_

#define TEST_CHIPSET_UGA_ONLY_NO
#define LOAD_INTEL_LOG

#include "Efi.h"
#include "Guid.h"
#include <Library/EfiTestLib.h>

#include EFI_PROTOCOL_DEFINITION (ConsoleControl)

#include EFI_GUID_DEFINITION (Bmp)

#define  UGA_DRAW_PROTOCOL_TEST_REVISION    0x00010000


#define  DEMO_WIDTH_HEIGHT_ENUM             2
#define  DEMO_SOURCE_POSITION_ENUM          3
#define  DEMO_DESTINATION_POSITION_ENUM     3
#define  DEMO_DELTA_ENUM                    4

#define  STEP_WIDTH                         50
#define  STEP_WIDTH_BUFFER                  100
#define  MAX_SCREEN_WIDTH                   800
#define  MAX_SCREEN_HEIGHT                  600

typedef
struct _DEMO_RESOLUTION_TYPE {
  UINT32 HorizontalResolution;
  UINT32 VerticalResolution;
} DEMO_RESOLUTION_TYPE;

typedef  UINT32 DEMO_REFRESH_RATE_TYPE;
typedef  UINT32 DEMO_COLOR_DEPTH_TYPE;


extern   EFI_EVENT                TimerEvent;
extern   DEMO_RESOLUTION_TYPE     DemoResolution[]  ;
extern   DEMO_REFRESH_RATE_TYPE   DemoRefreshRate[] ;
extern   DEMO_COLOR_DEPTH_TYPE    DemoColorDepth[]  ;

extern   UINTN                    DemoResolutionMax ;
extern   UINTN                    DemoRefreshRateMax;
extern   UINTN                    DemoColorDepthMax ;

#define  PIXEL(Buffer,Width,i,j)        ((Buffer)+((Width)*(i) + (j)))

EFI_STATUS
InitializeBBTestUgaDraw (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  );

EFI_STATUS
BBTestUgaDrawProtocolUnload (
  IN EFI_HANDLE           ImageHandle
  );


EFI_STATUS
BBTestGetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoFillFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoBltBufferFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoToVideoFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Conformance function
//
EFI_STATUS
BBTestGetModeConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestBltConformanceAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );


//
// Extensive function
//

EFI_STATUS
BBTestVideoFillBufferToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestVideoFillVideoToVideoManualTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestVideoToBltBufferAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoFillStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoBltBufferStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

EFI_STATUS
BBTestEfiUgaVideoToVideoStressAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  );

//
// Associatianal function
//

UINTN
UgaPrintXY (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *String
  );

UINTN
PrintXY (
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *ForeGround,  OPTIONAL
  IN EFI_UGA_PIXEL                    *BackGround,  OPTIONAL
  IN CHAR16                           *String
  );

UINTN
_IPrint (
  IN EFI_UGA_DRAW_PROTOCOL            *UgaDraw,
  IN EFI_SIMPLE_TEXT_OUT_PROTOCOL     *Sto,
  IN UINTN                            X,
  IN UINTN                            Y,
  IN EFI_UGA_PIXEL                    *Foreground,
  IN EFI_UGA_PIXEL                    *Background,
  IN CHAR16                           *String
  );

VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  ) ;

BOOLEAN
AutoJudge(
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

BOOLEAN
AutoJudgeUga(
  IN  UINTN         X,
  IN  UINTN         Y,
  IN  UINTN         Seconds,
  IN  BOOLEAN       Default,
  IN  CHAR16        *Message
  );

EFI_STATUS
UgaDrawClearScreen(
  IN  EFI_UGA_DRAW_PROTOCOL      *UgaDraw,
  IN  UINT32                     HorizontalResolution,
  IN  UINT32                     VerticalResolution
  );

EFI_STATUS
LoadBmp(
  IN EFI_UGA_PIXEL  **BltBuffer,
  IN UINTN         *Width,
  IN UINTN         *Height
  );

EFI_STATUS
ConvertBmpToUgaBlt (
  IN  VOID      *BmpImage,
  IN  UINTN     BmpImageSize,
  IN OUT VOID   **UgaBlt,
  IN OUT UINTN  *UgaBltSize,
  OUT UINTN     *PixelHeight,
  OUT UINTN     *PixelWidth
  );

EFI_STATUS
GetGraphicsBitMapFromFV (
  IN  EFI_GUID      *FileNameGuid,
  OUT VOID          **Image,
  OUT UINTN         *ImageSize
  );

VOID
GetTestData(
  IN  UINTN         Index,
  IN  UINTN        *Width,
  IN  UINTN        *Height,
  IN  UINTN        *SourceX,
  IN  UINTN        *SourceY,
  IN  UINTN        *DestinationX,
  IN  UINTN        *DestinationY,
  IN  UINTN        *Delta,
  IN  UINT32       HorizontalResolution,
  IN  UINT32       VerticalResolution
  );

EFI_STATUS
OutputScreen(
  IN EFI_UGA_DRAW_PROTOCOL   *UgaDraw,
  IN UINTN                   SourceX,
  IN UINTN                   SourceY,
  IN UINTN                   DestinationX,
  IN UINTN                   DestinationY
  );

EFI_STATUS
LocateDevicePathFromUgaDraw(
  IN EFI_UGA_DRAW_PROTOCOL                *UgaDraw,
  IN EFI_DEVICE_PATH_PROTOCOL             **DevicePath,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib
  );

//
// Entry GUIDs
//

#define UGA_DRAW_PROTOCOL_GETMODE_FUNCTION_AUTO_GUID \
  { 0xc4e5bb8, 0x2492, 0x457a, { 0x87, 0xb8, 0xb, 0xfb, 0xe2, 0x10, 0x80, 0x68 } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_FUNCTION_AUTO_GUID \
  { 0x3b6483c4, 0xb0b0, 0x4fa4, { 0xbb, 0x3c, 0x36, 0x88, 0xb, 0x1, 0x6b, 0x72 } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_FUNCTION_AUTO_GUID\
  { 0x5a0fdb31, 0x669f, 0x46a6, { 0x9f, 0x95, 0x10, 0x27, 0x60, 0xa6, 0x7d, 0xff } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_FUNCTION_AUTO_GUID\
  { 0xd91cb2c7, 0x4893, 0x4b19, { 0x84, 0xc8, 0x7f, 0xc0, 0xbd, 0x12, 0x77, 0x32 } }


//
// Conformance Test GUID
//

#define UGA_DRAW_PROTOCOL_GETMODE_CONFORMANCE_AUTO_GUID\
  { 0xacdfccef, 0xdd97, 0x4c0e, { 0x91, 0xdf, 0xdf, 0xed, 0x26, 0x2e, 0xcb, 0xfe } }

#define UGA_DRAW_PROTOCOL_BLT_CONFORMANCE_AUTO_GUID\
  { 0x79622ce0, 0xc4c3, 0x41ca, { 0xb3, 0xb7, 0x63, 0xac, 0x52, 0x37, 0x2, 0x0 } }

//
// Extensive Test Guid
//
#define UGA_DRAW_PROTOCOL_VIDEOFILL_BUFFERTOVIDEO_EXTENSIVE_MANUAL_GUID\
  { 0x6eee4cea, 0x1b93, 0x4eb6, { 0xa3, 0x84, 0xed, 0xad, 0xe6, 0xf8, 0xe4, 0x49 } }

#define UGA_DRAW_PROTOCOL_VIDEOFILL_VIDEOTOVIDEO_EXTENSIVE_MANUAL_GUID\
  { 0x7bb1e29d, 0x51b6, 0x4be9, { 0x90, 0x2e, 0x48, 0xad, 0xa5, 0xb8, 0xae, 0xf1 } }

#define UGA_DRAW_PROTOCOL_VIDEOTOBLTBUFFER_EXTENSIVE_AUTO_GUID\
  { 0x2457f1d5, 0xc764, 0x4ab1, { 0x8c, 0x38, 0x36, 0x17, 0xf9, 0x65, 0xf4, 0x76 } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOFILL_STRESS_AUTO_GUID \
  { 0xbb646a5f, 0x63da, 0x4517, { 0xae, 0x9e, 0x21, 0xb2, 0xfe, 0x82, 0xcc, 0x40 } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOBLTBUFFER_STRESS_AUTO_GUID\
  { 0xd00bccd6, 0x19d8, 0x4021, { 0xbb, 0x61, 0x2c, 0x62, 0x7c, 0xd0, 0x8f, 0x22 } }

#define UGA_DRAW_PROTOCOL_EFIUGAVIDEOTOVIDEO_STRESS_AUTO_GUID\
  { 0x3d595b26, 0x8306, 0x4034, { 0x86, 0xf8, 0xe6, 0x88, 0x7b, 0x2b, 0x6f, 0xd2 } }


#endif

