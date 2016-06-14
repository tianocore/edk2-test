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

  UgaDrawBBTestFunction.c

Abstract:

  Interface Function Test Cases of UGA Draw Protocol

--*/


#include "SctLib.h"
#include "UgaDrawBBTestMain.h"


UINTN                    DemoResolutionMax ;
UINTN                    DemoRefreshRateMax;
UINTN                    DemoColorDepthMax ;

/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.GetMode() Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.1
//
EFI_STATUS
BBTestGetModeFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType, SetModeAssertion;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg, HorizontalResolutionGet;
  UINT32                               VerticalResolution, VerticalResolutionOrg, VerticalResolutionGet;
  UINT32                               ColorDepth, ColorDepthOrg, ColorDepthGet;
  UINT32                               RefreshRate, RefreshRateOrg, RefreshRateGet;

  UINTN                                i, j, k, Index;
  EFI_UGA_PIXEL                        *BltBufferWhole;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;

  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2, *Blt;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }


  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawInterfaceTestAssertionGuid003,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Assertion Point 4.1.1.2.1
  // GetMode/SetMode should succeed to get or set the screen mode
  //

  //
  // For 800x600x32x60, it is the required mode!
  //

  //
  // Call SetMode to switch video device into 800x600x32x60 mode
  //
  HorizontalResolution = 800;
  VerticalResolution   = 600;
  ColorDepth           = 32;
  RefreshRate          = 60;
  Status1 = UgaDraw->SetMode (
                       UgaDraw,
                       HorizontalResolution,
                       VerticalResolution,
                       ColorDepth,
                       RefreshRate
                       );

  if (Status1 == EFI_SUCCESS) {
      BltBufferWhole = NULL;
      Status = gtBS->AllocatePool (
                       EfiBootServicesData,
                       HorizontalResolution * VerticalResolution * sizeof (EFI_UGA_PIXEL),
                       (VOID **)&BltBufferWhole
                       );
      if (EFI_ERROR (Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.AllocatePool - Allocate pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      SctZeroMem (BltBufferWhole, HorizontalResolution * VerticalResolution * sizeof (EFI_UGA_PIXEL));

      Status = UgaDraw->Blt (
                          UgaDraw,
                          BltBufferWhole,
                          EfiUgaVideoToBltBuffer,
                          0,
                          0,
                          0,
                          0,
                          HorizontalResolution,
                          VerticalResolution,
                          0
                          );
      if (EFI_ERROR(Status)) {
          StandardLib->RecordAssertion (
                         StandardLib,
                         EFI_TEST_ASSERTION_FAILED,
                         gTestGenericFailureGuid,
                         L"UgaDraw.Blt - EfiUgaVideoToBltBuffer",
                         L"%a:%d:Status - %r",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status
                         );
          if (BltBufferWhole != NULL) {
            Status = gtBS->FreePool (BltBufferWhole);
            BltBufferWhole = NULL;
          }
          return Status;
      }
      AssertionType = EFI_TEST_ASSERTION_PASSED;
      for (Index = 0; Index < HorizontalResolution * VerticalResolution; Index++) {
        if (((*((UINT32 * )BltBufferWhole + Index)) | 0xFF000000) != 0xFF000000){
          //
          // Assertion failed
          //
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          Index++;
          break;
        }
      }
      StandardLib->RecordAssertion (
                     StandardLib,
                     AssertionType,
                     gUgaDrawInterfaceTestAssertionGuid014,
                     L"EFI_UGA_DRAW_PROTOCOL.SetMode(), hardware frame buffer clean verification",
                     L"%a:%d: Status = %r,Index=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d,Pixel=0x%8x, Expected Pixel=0x%8x",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status,
                     Index,
                     HorizontalResolution,
                     VerticalResolution,
                     ColorDepth,
                     RefreshRate,
                      *((UINT32 * )BltBufferWhole + Index - 1) | 0xFF000000,
                     0xFF000000
                     );
      if (BltBufferWhole != NULL) {
        Status = gtBS->FreePool (BltBufferWhole);
        BltBufferWhole = NULL;
      }
  }
  if (EFI_ERROR(Status1)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawInterfaceTestAssertionGuid004,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to change video device's mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status1,
                 HorizontalResolution,
                 VerticalResolution,
                 ColorDepth,
                 RefreshRate
                 );
  //
  // Call GetMode() to retrieve information about current video device's mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionGet,
                      &VerticalResolutionGet,
                      &ColorDepthGet,
                      &RefreshRateGet
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawInterfaceTestAssertionGuid005,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve information about current video device'mode",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // Verify the retrieved mode with expected mode
  //
  if ((HorizontalResolution != HorizontalResolutionGet) ||
    (VerticalResolution != VerticalResolutionGet) ||
    (ColorDepth != ColorDepthGet)  ||  (RefreshRate != RefreshRateGet)) {

    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawInterfaceTestAssertionGuid006,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode/GetMode - GetMode after SetMode and compare",
                 L"%a:%d: Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d, ResolutionGet=(%dx%d), ColorDepthGet=%d, RefreshRateGet=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 HorizontalResolution,
                 VerticalResolution,
                 ColorDepth,
                 RefreshRate,
                 HorizontalResolutionGet,
                 VerticalResolutionGet,
                 ColorDepthGet,
                 RefreshRateGet
                 );



  //
  // Since the prepared demo mode is limited, and SetMode/GetMode will not elapse too long
  // So, for all demo mode, try it..
  //
  BltBuffer = NULL;
  BltBuffer2 = NULL;

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT * sizeof (EFI_UGA_PIXEL),
                   (VOID **)&BltBuffer
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  SctZeroMem (BltBuffer, MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT * sizeof (EFI_UGA_PIXEL));

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT * sizeof (EFI_UGA_PIXEL),
                   (VOID **)&BltBuffer2
                   );
  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (BltBuffer != NULL) {
      gtBS->FreePool (BltBuffer);
      BltBuffer = NULL;
    }
    return Status;
  }
  SctZeroMem (BltBuffer2, MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT * sizeof (EFI_UGA_PIXEL));

  Width                = 400;
  Height               = 300;
  Delta                = 0;
  Blt = BltBuffer;
  Blt->Blue  = 0xFF;
  Blt->Green = 0x00;
  Blt->Red   = 0x00;
  Blt->Reserved = 0;

  for (i = 0; i < DemoResolutionMax; i++) {
    HorizontalResolution = DemoResolution[i].HorizontalResolution;
    VerticalResolution = DemoResolution[i].VerticalResolution;
    for (j = 0; j < DemoRefreshRateMax; j++){
      RefreshRate = DemoRefreshRate[j];
      for (k = 0; k < DemoColorDepthMax; k++){
        ColorDepth = DemoColorDepth[k];
        //
        // switch screen into this demo mode
        //
           Status = UgaDraw->Blt (
                               UgaDraw,
                               BltBuffer,
                               EfiUgaVideoFill,
                               0,
                               0,
                               0,
                               0,
                               Width,
                               Height,
                               Delta
                               );
           if (EFI_ERROR(Status)) {
             AssertionType = EFI_TEST_ASSERTION_FAILED;
             StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"UgaDraw.Blt - EfiUgaVideoFill",
                   L"%a:%d: Status = %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
             if (BltBuffer != NULL) {
               Status = gtBS->FreePool (BltBuffer);
               BltBuffer = NULL;
             }
             if (BltBuffer2 != NULL) {
               Status = gtBS->FreePool (BltBuffer2);
               BltBuffer2 = NULL;
             }
             return Status;
           }
           gtBS->Stall (100000);
           Status = UgaDraw->SetMode (
                               UgaDraw,
                               HorizontalResolution,
                               VerticalResolution,
                               ColorDepth,
                               RefreshRate
                               );


           if (!EFI_ERROR(Status)) {
             //
             // Supported!
             //
             SetModeAssertion = EFI_TEST_ASSERTION_PASSED;
             BltBufferWhole = NULL;
             Status = gtBS->AllocatePool (
                              EfiBootServicesData,
                              HorizontalResolution * VerticalResolution * sizeof (EFI_UGA_PIXEL),
                              (VOID **)&BltBufferWhole
                              );
             if (EFI_ERROR (Status)) {
               StandardLib->RecordAssertion (
                              StandardLib,
                              EFI_TEST_ASSERTION_FAILED,
                              gTestGenericFailureGuid,
                              L"BS.AllocatePool - Allocate pool",
                              L"%a:%d:Status - %r",
                              __FILE__,
                              (UINTN)__LINE__,
                              Status
                              );
               if (BltBuffer != NULL) {
                 Status = gtBS->FreePool (BltBuffer);
                 BltBuffer = NULL;
               }
               if (BltBuffer2 != NULL) {
                 Status = gtBS->FreePool (BltBuffer2);
                 BltBuffer2 = NULL;
               }
               return Status;
             }
             SctZeroMem (BltBufferWhole, HorizontalResolution * VerticalResolution * sizeof (EFI_UGA_PIXEL));

             Status = UgaDraw->Blt (
                                 UgaDraw,
                                 BltBufferWhole,
                                 EfiUgaVideoToBltBuffer,
                                 0,
                                 0,
                                 0,
                                 0,
                                 HorizontalResolution,
                                 VerticalResolution,
                                 0
                                 );
             if (EFI_ERROR(Status)) {
               AssertionType = EFI_TEST_ASSERTION_FAILED;
               StandardLib->RecordAssertion (
                              StandardLib,
                              AssertionType,
                              gTestGenericFailureGuid,
                              L"UgaDraw.Blt - EfiUgaVideoFill",
                              L"%a:%d: Status = %r",
                              __FILE__,
                              (UINTN)__LINE__,
                              Status
                              );
               if (BltBufferWhole != NULL) {
                 Status = gtBS->FreePool (BltBufferWhole);
                 BltBufferWhole = NULL;
               }
               if (BltBuffer != NULL) {
                 Status = gtBS->FreePool (BltBuffer);
                 BltBuffer = NULL;
               }
               if (BltBuffer2 != NULL) {
                 Status = gtBS->FreePool (BltBuffer2);
                 BltBuffer2 = NULL;
               }
               return Status;
             }
             AssertionType = EFI_TEST_ASSERTION_PASSED;

             for (Index = 0; Index < HorizontalResolution * VerticalResolution; Index++) {

               if (((*((UINT32 * )BltBufferWhole + Index)) | 0xFF000000) != 0xFF000000){
                 //
                 // Assertion failed
                 //
                 Index++;
                 AssertionType = EFI_TEST_ASSERTION_FAILED;
                 break;
               }
             }

             StandardLib->RecordAssertion (
                            StandardLib,
                            AssertionType,
                            gUgaDrawInterfaceTestAssertionGuid014,
                            L"EFI_UGA_DRAW_PROTOCOL.SetMode(), hardware frame buffer clean verification",
                            L"%a:%d: Status = %r,Index=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d,Pixel=0x%8x, Expected Pixel=0x%8x",
                            __FILE__,
                            (UINTN)__LINE__,
                            Status,
                            Index,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate,
                             *((UINT32*)BltBufferWhole + Index - 1) | 0xFF000000,
                            0xFF000000
                            );

             if (BltBufferWhole != NULL) {
               Status = gtBS->FreePool (BltBufferWhole);
               BltBufferWhole = NULL;
             }
             //
             // Call GetMode() to retrieve information about current video device's mode
             //
             Status = UgaDraw->GetMode (
                                 UgaDraw,
                                 &HorizontalResolutionGet,
                                 &VerticalResolutionGet,
                                 &ColorDepthGet,
                                 &RefreshRateGet
                                 );

             if (EFI_ERROR(Status)) {
               AssertionType = EFI_TEST_ASSERTION_FAILED;
             } else {
               AssertionType = EFI_TEST_ASSERTION_PASSED;
             }
             StandardLib->RecordAssertion (
                            StandardLib,
                            AssertionType,
                            gUgaDrawInterfaceTestAssertionGuid008,
                            L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve information about current video device'mode",
                            L"%a:%d: Status = %r",
                            __FILE__,
                            (UINTN)__LINE__,
                            Status
                            );

             //
             // Verify the retrieved mode with expected mode
             //
             if (HorizontalResolution != HorizontalResolutionGet ||
               VerticalResolution != VerticalResolutionGet ||
               ColorDepth != ColorDepthGet  ||  RefreshRate != RefreshRateGet) {

               AssertionType = EFI_TEST_ASSERTION_FAILED;
             } else {
               AssertionType = EFI_TEST_ASSERTION_PASSED;
             }

             StandardLib->RecordAssertion (
                            StandardLib,
                            AssertionType,
                            gUgaDrawInterfaceTestAssertionGuid009,
                            L"EFI_UGA_DRAW_PROTOCOL.SetMode/GetMode - GetMode after SetMode and compare",
                            L"%a:%d: Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d, ResolutionGet=(%dx%d), ColorDepthGet=%d, RefreshRateGet=%d",
                            __FILE__,
                            (UINTN)__LINE__,
                            HorizontalResolution,
                            VerticalResolution,
                            ColorDepth,
                            RefreshRate,
                            HorizontalResolutionGet,
                            VerticalResolutionGet,
                            ColorDepthGet,
                            RefreshRateGet
                            );

          } else if (Status == EFI_UNSUPPORTED)  {
            SetModeAssertion = EFI_TEST_ASSERTION_PASSED;
          } else {
            //
            // Unexpected status
            //
            SetModeAssertion = EFI_TEST_ASSERTION_FAILED;
          }
          StandardLib->RecordAssertion (
                         StandardLib,
                         SetModeAssertion,
                         gUgaDrawInterfaceTestAssertionGuid011,
                         L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                         L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                         __FILE__,
                         (UINTN)__LINE__,
                         Status,
                         HorizontalResolution,
                         VerticalResolution,
                         ColorDepth,
                         RefreshRate
                         );

          //
          // Wait for 1 seconds
          //
          gtBS->Stall (100000);

      }
    }
  }
  if (BltBuffer != NULL) {
    Status = gtBS->FreePool (BltBuffer);
    BltBuffer = NULL;
  }
  if (BltBuffer2 != NULL) {
    Status = gtBS->FreePool (BltBuffer2);
    BltBuffer2 = NULL;
  }
  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gUgaDrawInterfaceTestAssertionGuid012,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoFill Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.2
//
EFI_STATUS
BBTestEfiUgaVideoFillFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1;
  EFI_STATUS                           Status2;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;

  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2, *Blt;

  UINTN                                m, Index;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;
  UINTN                                Size;

  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d:Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // Allocate Buffer for BltBuffer & BltBuffer2
  //
  BltBuffer = NULL;
  BltBuffer2 = NULL;

  Size = MAX_SCREEN_WIDTH * MAX_SCREEN_HEIGHT * sizeof (EFI_UGA_PIXEL);
  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Size,
                   (VOID **)&BltBuffer
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  SctZeroMem (BltBuffer, Size);

  Status = gtBS->AllocatePool (
                   EfiBootServicesData,
                   Size,
                   (VOID **)&BltBuffer2
                   );
  if (EFI_ERROR (Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    if (BltBuffer != NULL) {
      Status = gtBS->FreePool (BltBuffer);
    }
    return Status;
  }
  SctZeroMem (BltBuffer2, Size);
  //
  // for all demo mode, try it..
  //

  for (Index = 0; Index < 10; Index++) {
    //
    // prepare test data
    //
    switch (Index) {
      case 0:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 1:
        HorizontalResolution = 640;
        VerticalResolution   = 480;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 2:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 3:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 4:
        HorizontalResolution = 640;
        VerticalResolution   = 480;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 5:
        HorizontalResolution = 1024;
        VerticalResolution   = 768;
        RefreshRate          = 75;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 6:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 7:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 120;
        break;

      default:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = HorizontalResolution + 10;
        DestinationY         = 0;
        Delta                = 0;
        break;
    }



    //
    // Test data verification
    //
    if (DestinationX + Width > HorizontalResolution) {
      continue;
    }

    if (DestinationY + Height > VerticalResolution) {
      continue;
    }

    if (Width == 0 || Height == 0) {
      continue;
    }

    if (Delta == 0) {
      Delta = Width * sizeof (EFI_UGA_PIXEL);
    }

    //
    // switch screen into this demo mode
    //
    Status = UgaDraw->SetMode (
                        UgaDraw,
                        HorizontalResolution,
                        VerticalResolution,
                        ColorDepth,
                        RefreshRate
                        );
    if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                   L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Clear Screen
    //
    Status = UgaDrawClearScreen (
               UgaDraw,
               HorizontalResolution,
               VerticalResolution
               );
   if (EFI_ERROR(Status)) {
     AssertionType = EFI_TEST_ASSERTION_FAILED;
     StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gTestGenericFailureGuid,
                    L"EFI_UGA_DRAW_PROTOCOL.Blt - UgaDrawClearScreen",
                    L"%a:%d: Status = %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );
      return Status;
    }
    Blt = BltBuffer;
    Blt->Blue  = 0xFF;
    Blt->Green = 0x00;
    Blt->Red   = 0x00;
    Blt->Reserved = 0;

    //
    // Call Blt() with BltOperation being EfiUgaVideo Fill
    //
    Status1 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer,
                         EfiUgaVideoFill,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta
                         );

    //
    // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
    // to retrieve rectangles drawn by last EfiUgaVideoFill operation
    //
    Status2 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer2,
                         EfiUgaVideoToBltBuffer,
                         DestinationX,
                         DestinationY,
                         0,
                         0,
                         Width,
                         Height,
                         Delta
                         );

    //
    // All the retrieve rectangle should be with same pixel!
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (m = 0; m < Width * Height; m++) {

      if (((*((UINT32*)BltBuffer2 + m)) | 0xFF000000) != ((*((UINT32 * )Blt)) | 0xFF000000)){
        //
        // Assertion failed
        //
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        m++;
        break;
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid003,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill, pixel verification",
                   L"%a:%d: Status = %r, Intex = %d, Pixel Index = %d, Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Pixel Get = 0x%8x, Pixel expected = 0x%8x, Delta=%d, Blt=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   Index,
                   m,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   *((UINT32 * )BltBuffer2 + m - 1) | 0xFF000000,
                   *((UINT32 * )Blt) | 0xFF000000,
                   Delta,
                   *((UINT32 * )Blt),
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid001,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoFill - Blt/EfiUgaVideoFill",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );
    if (EFI_ERROR(Status2)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status2,
                   DestinationX,
                   DestinationY,
                   0, 0,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    //
    // Wait for some time
    //
    gtBS->Stall (100000);
  }

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );

  //
  // Free Buffer
  //
  if (BltBuffer != NULL) {
    Status = gtBS->FreePool (BltBuffer);
  }

  if (BltBuffer2 != NULL) {
    Status = gtBS->FreePool (BltBuffer2);
  }

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoToBltBuffer/EfiUgaBltBufferToVideo Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.3
//
EFI_STATUS
BBTestEfiUgaVideoBltBufferFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1;
  EFI_STATUS                           Status2;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;
  UINTN                                Size;
  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2;

  UINTN                                m, Index;
  UINTN                                IndexWidth, IndexHeight, IndexPos;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Assert pointer 4.1.3.2.1
  // Blt-EfiUgaBltBufferToVideo operation should succeed to write data to video screen
  // and EfiUgaVideoToBltBuffer operation should succeed to Read data from the video display rectangle
  //


  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );


  //
  // for all demo mode, try it..
  //
  for (Index = 0; Index < 10; Index++) {
    //
    // prepare test data
    //
    switch (Index) {
      case 0:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 1:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 2:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 3:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 4:
        HorizontalResolution = 640;
        VerticalResolution   = 480;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 5:
        HorizontalResolution = 1024;
        VerticalResolution   = 768;
        RefreshRate          = 75;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 6:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 7:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      default:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = HorizontalResolution + 10;
        DestinationY         = 0;
        Delta                = 0;
        break;
    }

    //
    // Test data verification
    // Here SourceXY is the Upper left hand of Video
    // DestinationXY is the Upper left hand fo BltBuffer
    //
    if (SourceX + Width > HorizontalResolution) {
      continue;
    }

    if (SourceY + Height > VerticalResolution) {
      continue;
    }

    if (Width == 0 || Height == 0) {
      continue;
    }

    if (Delta == 0) {
      Delta = Width * sizeof (EFI_UGA_PIXEL);
    }
    //
    // switch screen into this demo mode
    //

    Status = UgaDraw->SetMode (
                        UgaDraw,
                        HorizontalResolution,
                        VerticalResolution,
                        ColorDepth,
                        RefreshRate
                        );

    if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                   L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status)) {
      continue;
    }

    //
    // Clear Screen
    //
    Status = UgaDrawClearScreen (
               UgaDraw,
               HorizontalResolution,
               VerticalResolution
               );
   if (EFI_ERROR(Status)) {
     AssertionType = EFI_TEST_ASSERTION_FAILED;
     StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gTestGenericFailureGuid,
                    L"EFI_UGA_DRAW_PROTOCOL.Blt - UgaDrawClearScreen",
                    L"%a:%d: Status = %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );
      return Status;
    }
    //
    // Allocate Buffer for BltBuffer & BltBuffer2
    // BltBuffer should be large than (Width+DestinationX)*(Height+DestinationY)
    //
    BltBuffer = NULL;
    BltBuffer2 = NULL;
    Size = (Width + DestinationX) * (Height + DestinationY) * sizeof (EFI_UGA_PIXEL);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     Size,
                     (VOID **)&BltBuffer
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePool - Allocate pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
    SctZeroMem (BltBuffer, Size);

    Size = Width * Height * sizeof (EFI_UGA_PIXEL);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     Size,
                     (VOID **)&BltBuffer2
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePool - Allocate pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (BltBuffer !=NULL) {
        gtBS->FreePool (BltBuffer);
      }
      return Status;
    }
    SctZeroMem (BltBuffer2, Size);

    //
    // Delta should reflect the length of a row correctly
    //
    Delta = (Width + DestinationX) * sizeof (EFI_UGA_PIXEL);


    //
    // Actually, should output screen with some picture.
    //
    Status = OutputScreen (UgaDraw, SourceX, SourceY, DestinationX, DestinationY);
    if EFI_ERROR (Status) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"UgaDraw.Blt() - OutputScreen",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
        BltBuffer = NULL;
      }
      if (BltBuffer2 != NULL) {
        Status = gtBS->FreePool (BltBuffer2);
        BltBuffer2 = NULL;
      }
      return Status;
    }
    gtBS->Stall (50000);
    //
    // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
    // Operation to be tested! (1)
    //
    Status = UgaDraw->Blt (
                        UgaDraw,
                        BltBuffer,
                        EfiUgaVideoToBltBuffer,
                        SourceX,
                        SourceY,
                        DestinationX,
                        DestinationY,
                        Width,
                        Height,
                        Delta
                        );

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid004,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    //
    // Clear screen
    //
    Status = UgaDrawClearScreen (
               UgaDraw,
               HorizontalResolution,
               VerticalResolution
               );
   if (EFI_ERROR(Status)) {
     AssertionType = EFI_TEST_ASSERTION_FAILED;
     StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gTestGenericFailureGuid,
                    L"EFI_UGA_DRAW_PROTOCOL.Blt - UgaDrawClearScreen",
                    L"%a:%d: Status = %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
        BltBuffer = NULL;
      }
      if (BltBuffer2 != NULL) {
        Status = gtBS->FreePool (BltBuffer2);
        BltBuffer2 = NULL;
      }
      return Status;
    }
    //
    // Call Blt() with BltOperation being EfiUgaBltBufferToVideo to
    // re-draw Buffer into display
    // Note: Source and Destination should reverse with that of VideoToBltBuffer operation
    //

    //
    // Operation to be tested! (2)
    //

    Status1 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer,
                         EfiUgaBltBufferToVideo,
                         DestinationX,
                         DestinationY,
                         SourceX,
                         SourceY,
                         Width,
                         Height,
                         Delta
                         );

    gtBS->Stall (50000);
    //
    // Call Blt() with BltOperatoin being EfiUgaVideoToBltBuffer again
    // This time, use BltBuffer2 and save it
    //

    Status2 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer2,
                         EfiUgaVideoToBltBuffer,
                         SourceX,
                         SourceY,
                         0,
                         0,
                         Width,
                         Height,
                         0
                         );

    if (EFI_ERROR(Status2)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid006,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status2,
                   SourceX,
                   SourceY,
                   0,
                   0,
                   Width,
                   Height,
                   0,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid005,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   DestinationX,
                   DestinationY,
                   SourceX,
                   SourceY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );
    //
    // Compare BltBuffer with BltBuffer2 the two should be same
    // Operation to be tested! (3)
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (m = 0; m < Width * Height; m++) {
      IndexWidth  = m % Width;
      IndexHeight = m / Width + DestinationY;
      IndexPos = IndexWidth + DestinationX + IndexHeight * (Delta / sizeof (EFI_UGA_PIXEL));

      if (((*((UINT32 * )BltBuffer + IndexPos)) | 0xFF000000) != ((*((UINT32 * )BltBuffer2 + m)) | 0xFF000000)){
        //
        // Assertion failed
        //
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid008,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer, Pixel verification",
                   L"%a:%d: Status = %r,Video Source=(%dx%d),Buffer Destination=(%dx%d), Width=%d, Height=%d, Delta=%d Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    //
    // Free Buffer for next test data
    //
    if (BltBuffer != NULL) {
      Status = gtBS->FreePool (BltBuffer);
    }

    if (BltBuffer2 != NULL) {
      Status = gtBS->FreePool (BltBuffer2);
    }
  }

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );

  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_UGA_DRAW_PROTOCOL.Blt()  - EfiUgaVideoToVideo Function Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 4.1.4
//
EFI_STATUS
BBTestEfiUgaVideoToVideoFunctionAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_STATUS                           Status1;
  EFI_STATUS                           Status2;
  EFI_UGA_DRAW_PROTOCOL                *UgaDraw;

  EFI_TEST_ASSERTION                   AssertionType;

  UINT32                               HorizontalResolution, HorizontalResolutionOrg;
  UINT32                               VerticalResolution, VerticalResolutionOrg;
  UINT32                               ColorDepth, ColorDepthOrg;
  UINT32                               RefreshRate, RefreshRateOrg;

  UINTN                                Size;
  UINTN                                SourceX;
  UINTN                                SourceY;
  UINTN                                DestinationX;
  UINTN                                DestinationY;
  UINTN                                Width;
  UINTN                                Height;
  UINTN                                Delta;
  EFI_UGA_PIXEL                        *BltBuffer, *BltBuffer2;

  UINTN                                m, Index;

  EFI_DEVICE_PATH_PROTOCOL             *DevicePath;
  CHAR16                               *DevicePathStr;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   &StandardLib
                   );

  if (EFI_ERROR(Status)) {
    StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.HandleProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  UgaDraw = (EFI_UGA_DRAW_PROTOCOL *)ClientInterface;

  //
  // Get Device Path of current Uga_Draw_Protocol
  // And out put device path or device name
  //
  Status = LocateDevicePathFromUgaDraw (UgaDraw, &DevicePath, StandardLib);
  if (Status == EFI_SUCCESS) {
    DevicePathStr = SctDevicePathToStr (DevicePath);
    if (DevicePathStr != NULL) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"\r\nCurrent Device: %s",
                     DevicePathStr
                     );
      Status = gtBS->FreePool (DevicePathStr);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d:Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
        return Status;
      }
      DevicePathStr = NULL;
    }
  } else {
    //
    // Console Splitter/UgaDraw
    //
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"\r\nCurrent Device: ConsoleSplitter/UgaDraw"
                   );
#ifdef TEST_CHIPSET_UGA_ONLY
    return EFI_SUCCESS;
#endif
  }

  //
  // Backup video mode
  //
  Status = UgaDraw->GetMode (
                      UgaDraw,
                      &HorizontalResolutionOrg,
                      &VerticalResolutionOrg,
                      &ColorDepthOrg,
                      &RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }

  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.GetMode - GetMode to retrieve video device information",
                 L"%a:%d: Status = %r",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status
                 );

  //
  // for all demo mode, try it..
  //
  for (Index = 0; Index < 10; Index++) {
    //
    // prepare test data
    //
    switch (Index) {
      case 0:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 1:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 0;
        break;

      case 2:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 3:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 4:
        HorizontalResolution = 640;
        VerticalResolution   = 480;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = Width * sizeof (EFI_UGA_PIXEL);
        break;

      case 5:
        HorizontalResolution = 1024;
        VerticalResolution   = 768;
        RefreshRate          = 75;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 100;
        SourceY              = 100;
        DestinationX         = 0;
        DestinationY         = 0;
        Delta                = 120;
        break;

      case 6:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 400;
        Height               = 300;
        SourceX              = 800;
        SourceY              = 600;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      case 7:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = 400;
        DestinationY         = 300;
        Delta                = 0;
        break;

      default:
        HorizontalResolution = 800;
        VerticalResolution   = 600;
        RefreshRate          = 60;
        ColorDepth           = 32;
        Width                = 100;
        Height               = 100;
        SourceX              = 0;
        SourceY              = 0;
        DestinationX         = HorizontalResolution + 10;
        DestinationY         = 0;
        Delta                = 0;
        break;
    }

    //
    // Test data verification
    //
    if (DestinationX + Width > HorizontalResolution) {
      continue;
    }

    if (DestinationY + Height > VerticalResolution) {
      continue;
    }

    if (SourceX + Width > HorizontalResolution) {
      continue;
    }

    if (SourceY + Height > VerticalResolution) {
      continue;
    }

    if (SourceX == DestinationX && SourceY == DestinationY) {
      continue;
    }

    if (Width == 0 || Height == 0) {
      continue;
    }

    if (Delta == 0) {
      Delta = Width * sizeof (EFI_UGA_PIXEL);
    }

    //
    // switch screen into this demo mode
    //
    Status = UgaDraw->SetMode (
                        UgaDraw,
                        HorizontalResolution,
                        VerticalResolution,
                        ColorDepth,
                        RefreshRate
                        );
    if (Status == EFI_UNSUPPORTED || Status == EFI_SUCCESS)  {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to switch video device's mode",
                   L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status)) {
      continue;
    }


    //
    // Clear Screen
    //
    Status = UgaDrawClearScreen (
               UgaDraw,
               HorizontalResolution,
               VerticalResolution
               );
   if (EFI_ERROR(Status)) {
     AssertionType = EFI_TEST_ASSERTION_FAILED;
     StandardLib->RecordAssertion (
                    StandardLib,
                    AssertionType,
                    gTestGenericFailureGuid,
                    L"EFI_UGA_DRAW_PROTOCOL.Blt - UgaDrawClearScreen",
                    L"%a:%d: Status = %r",
                    __FILE__,
                    (UINTN)__LINE__,
                    Status
                    );
      return Status;
    }
    //
    // Allocate Buffer for BltBuffer & BltBuffer2
    //
    BltBuffer = NULL;
    BltBuffer2 = NULL;
    Size = Width * Height * sizeof (EFI_UGA_PIXEL);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     Size,
                     (VOID **)&BltBuffer
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePool - Allocate pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      return Status;
    }
    SctZeroMem (BltBuffer, Size);

    Size = Width * Height * sizeof (EFI_UGA_PIXEL);
    Status = gtBS->AllocatePool (
                     EfiBootServicesData,
                     Size,
                     (VOID **)&BltBuffer2
                     );
    if (EFI_ERROR (Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"BS.AllocatePool - Allocate pool",
                     L"%a:%d:Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                     );
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
      }
      return Status;
    }
    SctZeroMem (BltBuffer2, Size);
    //
    // Actually, should output screen with some picture.
    //

    Status = OutputScreen (UgaDraw, SourceX, SourceY, DestinationX, DestinationY);
    if (EFI_ERROR(Status)) {
      StandardLib->RecordAssertion (
                     StandardLib,
                     EFI_TEST_ASSERTION_FAILED,
                     gTestGenericFailureGuid,
                     L"UgaDraw.Blt() - OutputScreen",
                     L"%a:%d: Status - %r",
                     __FILE__,
                     (UINTN)__LINE__,
                     Status
                    );
      if (BltBuffer != NULL) {
        Status = gtBS->FreePool (BltBuffer);
        BltBuffer = NULL;
      }
      if (BltBuffer2 != NULL) {
        Status = gtBS->FreePool (BltBuffer2);
        BltBuffer2 = NULL;
      }
      return Status;
    }
    gtBS->Stall (50000);
    //
    // Call Blt() with BltOperation being EfiUgaVideoToBltBuffer
    // to save original screen
    //
    Status1 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer,
                         EfiUgaVideoToBltBuffer,
                         SourceX,
                         SourceY,
                         0,
                         0,
                         Width,
                         Height,
                         0
                         );

    //
    // Call Blt() with BltOperation being EfiUgaVideoToVideo to copy screen
    //

    Status2 = UgaDraw->Blt (
                         UgaDraw,
                         BltBuffer2,
                         EfiUgaVideoToVideo,
                         SourceX,
                         SourceY,
                         DestinationX,
                         DestinationY,
                         Width,
                         Height,
                         Delta
                         );

    gtBS->Stall (50000);
    //
    // Call Blt() with BltOperatoin being EfiUgaVideoToBltBuffer again
    // This time, use BltBuffer2, and the retrieved area should be destination rectangle
    //

    Status = UgaDraw->Blt (
                        UgaDraw,
                        BltBuffer2,
                        EfiUgaVideoToBltBuffer,
                        DestinationX,
                        DestinationY,
                        0, 0,
                        Width,
                        Height,
                        0
                        );

    if (EFI_ERROR(Status)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   DestinationX,
                   DestinationY,
                   0, 0,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status1)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gTestGenericFailureGuid,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToBltBuffer - Blt/EfiUgaVideoToBltBuffer",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status1,
                   SourceX,
                   SourceY,
                   0,
                   0,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    if (EFI_ERROR(Status2)) {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    }
    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid009,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status2,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    //
    // Compare BltBuffer with BltBuffer2
    // the two should be same
    //
    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for (m = 0; m < Width * Height; m++) {
      if ((0xFF000000 | (*((UINT32 * )BltBuffer + m))) != (0xFF000000 | (*((UINT32 * )BltBuffer2 + m)))){
        //
        // Assertion failed
        //
        AssertionType = EFI_TEST_ASSERTION_FAILED;
        break;
      }
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gUgaDrawBBTestFunctionAssertionGuid011,
                   L"EFI_UGA_DRAW_PROTOCOL.Blt/EfiUgaVideoToVideo - Blt/EfiUgaVideoToVideo, Pixel verification",
                   L"%a:%d: Status = %r,Source=(%dx%d), Destination=(%dx%d), Width=%d, Height=%d, Delta=%d, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status,
                   SourceX,
                   SourceY,
                   DestinationX,
                   DestinationY,
                   Width,
                   Height,
                   Delta,
                   HorizontalResolution,
                   VerticalResolution,
                   ColorDepth,
                   RefreshRate
                   );

    //
    // Free Buffer for next test data
    //
    if (BltBuffer != NULL) {
      Status = gtBS->FreePool (BltBuffer);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
      }
    }

    if (BltBuffer2 != NULL) {
      Status = gtBS->FreePool (BltBuffer2);
      if (EFI_ERROR(Status)) {
        StandardLib->RecordAssertion (
                       StandardLib,
                       EFI_TEST_ASSERTION_FAILED,
                       gTestGenericFailureGuid,
                       L"BS.FreePool - Free pool",
                       L"%a:%d: Status - %r",
                       __FILE__,
                       (UINTN)__LINE__,
                       Status
                       );
      }
    }
  }

  //
  // Restore video mode
  //
  Status = UgaDraw->SetMode (
                      UgaDraw,
                      HorizontalResolutionOrg,
                      VerticalResolutionOrg,
                      ColorDepthOrg,
                      RefreshRateOrg
                      );

  if (EFI_ERROR(Status)) {
    AssertionType = EFI_TEST_ASSERTION_FAILED;
  } else {
    AssertionType = EFI_TEST_ASSERTION_PASSED;
  }
  StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gTestGenericFailureGuid,
                 L"EFI_UGA_DRAW_PROTOCOL.SetMode - SetMode to restore original video mode",
                 L"%a:%d: Status = %r, Resolution=(%dx%d), ColorDepth=%d, RefreshRate=%d",
                 __FILE__,
                 (UINTN)__LINE__,
                 Status,
                 HorizontalResolutionOrg,
                 VerticalResolutionOrg,
                 ColorDepthOrg,
                 RefreshRateOrg
                 );

  return EFI_SUCCESS;
}
