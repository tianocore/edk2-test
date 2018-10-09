/** @file

  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
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
