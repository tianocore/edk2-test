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

  EntsTime.c

Abstract:

  ENTS time services implementations.

--*/
#include "Efi.h"
#include <Library/EntsLib.h>

//
// Global variables and definitions
//
#define IS_LEAP(y)  ((((y) % 4) == 0 && ((y) % 100) != 0) || ((y) % 400) == 0)

static const UINTN  MonthLengths[2][12] = {
  {
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
  },
  {
    31,
    29,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31
  }
};

UINT32
EntsSecondsElapsedFromBaseYear (
  IN UINT16             BaseYear,
  IN UINT16             Year,
  IN UINT8              Month,
  IN UINT8              Day,
  IN UINT8              Hour,
  IN UINT8              Minute,
  IN UINT8              Second
  )
/*++

Routine Description:

  Calculate the elapsed seconds from the base year.
  
Arguments:

  BaseYear  - The base year.
  Year      - Current year.
  Month     - Current month.
  Day       - Current day.
  Hour      - Current hour.
  Minute    - Current minute.
  Second    - Current second.

Returns:

  The elapsed seconds.

--*/
{
  UINTN   Seconds;
  UINT32  LeapYear;
  INTN    Index;

  Seconds = 0;
  for (Index = BaseYear; Index < Year; Index++) {
    if (IS_LEAP (Index)) {
      Seconds += DAYS_PER_LYEAR * SECS_PER_DAY;
    } else {
      Seconds += DAYS_PER_NYEAR * SECS_PER_DAY;
    }
  }

  LeapYear = IS_LEAP (Year);
  for (Index = 0; Index < Month - 1; Index++) {
    Seconds += MonthLengths[LeapYear][Index] * SECS_PER_DAY;
  }

  for (Index = 0; Index < Day - 1; Index++) {
    Seconds += SECS_PER_DAY;
  }

  for (Index = 0; Index < Hour; Index++) {
    Seconds += SECS_PER_HOUR;
  }

  for (Index = 0; Index < Minute; Index++) {
    Seconds += SECS_PER_MIN;
  }

  return (UINT32) (Seconds + Second);
}
