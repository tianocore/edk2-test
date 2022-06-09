/** @file

  Copyright 2006 - 2011 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  UnicodeCollationBBTestMain.c

Abstract:

  Test Driver of Unicode Collation Protocol

--*/


#include "SctLib.h"
#include "UnicodeCollationBBTestMain.h"

CHAR8                                                EngUpperMap[0x100];
CHAR8                                                EngLowerMap[0x100];
CHAR8                                                EngInfoMap[0x100];

CHAR8                                                OtherChars[] = {'0','1','2','3','4','5','6','7',
                                                                     '8','9','\\','.','_','^','$','~',
                                                                     '!','#','%','&','-','{','}','(',
                                                                     ')','@','`','\'', '\0'};


//
// Build Data structure here
//

EFI_BB_TEST_PROTOCOL_FIELD gBBTestProtocolField = {
  UNICODE_COLLATION_PROTOCOL_TEST_REVISION,
  EFI_UNICODE_COLLATION_PROTOCOL_GUID,
  L"Unicode Collation Protocol Test",
  L"UEFI Unicode Collation Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    UNICODE_COLLATION_PROTOCOL_STRICOLL_FUNCTION_AUTO_GUID,
    L"StriColl_Func",
    L"Perform auto function checkes on the StriColl interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStriCollFunctionAutoTest
  },
  {
    UNICODE_COLLATION_PROTOCOL_METAIMATCH_FUNCTION_AUTO_GUID,
    L"MetaiMatch_Func",
    L"Perform auto function checkes on the MetaiMatch interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMetaiMatchFunctionAutoTest
  },
  {
    UNICODE_COLLATION_PROTOCOL_STRLWR_FUNCTION_AUTO_GUID,
    L"StrLwr_Func",
    L"Perform auto function checkes on the StrLwr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStrLwrFunctionAutoTest
  },
  {
    UNICODE_COLLATION_PROTOCOL_STRUPR_FUNCTION_AUTO_GUID,
    L"StrUpr_Func",
    L"Perform auto function checkes on the StrUpr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStrUprFunctionAutoTest
  },
  {
    UNICODE_COLLATION_PROTOCOL_FATTOSTR_FUNCTION_AUTO_GUID,
    L"FatToStr_Func",
    L"Perform auto function checkes on the FatToStr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFatToStrFunctionAutoTest
  },
  {
    UNICODE_COLLATION_PROTOCOL_STRTOFAT_FUNCTION_AUTO_GUID,
    L"StrToFat_Func",
    L"Perform auto function checkes on the StrToFat interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStrToFatFunctionAutoTest
  },

#ifdef EFI_TEST_EXHAUSTIVE
  {
    UNICODE_COLLATION_PROTOCOL_STRESS_AUTO_GUID,
    L"Unicode Collation Stress Test",
    L"Test the functionality of the interface on large-length strings",
    EFI_TEST_LEVEL_EXHAUSTIVE,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStressAutoTest
  },
#endif

  0
};


EFI_BB_TEST_PROTOCOL *gBBTestProtocolInterface;

EFI_STATUS
EFIAPI
BBTestUnicodeCollationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Unicode Collation Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestUnicodeCollation (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EfiInitializeTestLib (ImageHandle, SystemTable);

  InitCharMapping();

  return EfiInitAndInstallBBTestInterface (
           &ImageHandle,
           &gBBTestProtocolField,
           gBBTestEntryField,
           BBTestUnicodeCollationProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
EFIAPI
BBTestUnicodeCollationProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  )
{
  EFI_STATUS Status;

  Status = EfiUninstallAndFreeBBTestInterface (
             ImageHandle,
             gBBTestProtocolInterface
             );

  return Status;
}

/**
 *  Assistant function to copy a Unicode string to destination
 *  @param  Destination buffer of destine Unicode string
 *  @param  Source buffer of original Unicode string
 */
VOID
CopyUnicodeString (
  IN CHAR16                     *Destination,
  IN CHAR16                     *Source
  )
{
  UINTN                Index = 0;
  while (Source != NULL && (*Source) != 0 && Index < MAX_SIZE_OF_STRING) {
    *Destination = *Source;
    Destination++;
    Source++;
  }
  *Destination = 0;
}

/**
 *  Assistant function to check the correctness of StrLwr functionality
 *  @param  Original buffer of source Unicode string
 *  @param  Result buffer of Unicode string after StrLwr call
 *  @return TRUE/FALSE whether Result reflect the functionality of StrLwr on Original string
 */
BOOLEAN
CheckStrLwr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  )
{

  if (Original == NULL && Result == NULL) {
    return TRUE;
  }

  if (!(Original != NULL && Result != NULL)) {
    return FALSE;
  }

  //
  // Original and Result should have same length
  //
  if (GetStrLen16(Original) != GetStrLen16(Result)) {
    return FALSE;
  }

  //
  // All character in Result should be in lower case
  //
  while (*Original) {
    if (*Result != ToLower (*Original)) {
      return FALSE;
    }
    Original++;
    Result++;
  }

  return TRUE;
}

/**
 *  Assistant function to get length of a Unicode string
 *  @param  s Unicode string
 *  @return length of the string
 */
UINTN
GetStrLen16(
  IN CHAR16                    *s
  )
{
  UINTN           len=0;

  if (s == NULL) {
    return len;
  }

  while (*s != 0) {
    len++;
    s++;
  }
  return len;
}

/**
 *  Assistant function to get length of an OEM string
 *  @param  s OEM string
 *  @return length of the string
 */
UINTN
GetStrLen8(
  IN CHAR8                     *s
  )
{
  UINTN           len = 0;

  if (s == NULL) {
    return len;
  }

  while (*s != 0) {
    len++;
    s++;
  }
  return len;
}

/**
 *  Assistant function to check the correctness of StrUpr functionality
 *  @param  Original buffer of source Unicode string
 *  @param  Result buffer of Unicode string after StrUpr call
 *  @return TRUE/FALSE whether Result reflect the functionality of StrUpr on Original string
 */
BOOLEAN
CheckStrUpr (
  IN CHAR16                     *Original,
  IN CHAR16                     *Result
  )
{
  if (Original == NULL && Result == NULL) {
    return TRUE;
  }

  if (!(Original != NULL && Result != NULL)) {
    return FALSE;
  }

  //
  // Original and Result should have same length
  //
  if (GetStrLen16 (Original) != GetStrLen16 (Result)) {
    return FALSE;
  }

  //
  // All character in Result should be in Upper case
  //
  while (*Original) {
    if (*Result != ToUpper (*Original)) {
      return FALSE;
    }
    Original++;
    Result++;
  }

  return TRUE;
}

/**
 *  Assistant function to check whether two Unicode string are equal
 *  @param  S1/S2 two Unicode strings
 *  @return TRUE/FALSE whether the two Unicode string are equal
 */
BOOLEAN
CheckStrEql (
  IN CHAR16                     *S1,
  IN CHAR16                     *S2
  )
{
  if (S1 == NULL && S2 == NULL) {
    return TRUE;
  }

  if (!(S1 != NULL && S2 != NULL)) {
    return FALSE;
  }

  while (*S1 && *S2) {
    if (*S1 != *S2) {
      return FALSE;
    }
    S1++;
    S2++;
  }

  return TRUE;
}

/**
 *  Assistant function to check the correctness of FatToStr functionality
 *  @param  Fat buffer of source string
 *  @parma  FatSize length of Fat
 *  @param  Result buffer of Unicode string after FatToStr call
 *  @return TRUE/FALSE whether Result reflect the functionality of FatToStr on Original Fat string and FatSize
 */
BOOLEAN
CheckFatToStr (
  IN CHAR8                      *Fat,
  IN UINTN                      FatSize,
  IN CHAR16                     *Result
  )
{
  //
  // The length of Result should be less than FatSize and the length of Fat
  //
  if (GetStrLen16 (Result) > FatSize || GetStrLen16 (Result) > GetStrLen8 (Fat)) {
    return FALSE;
  }

  //
  // Result reflect Fat correctly
  //
  while (*Fat && FatSize) {
    if (*Result != *Fat) {
      return FALSE;
    }
    Result++;;
    Fat++;
    FatSize--;
  }
  return TRUE;
}

/**
 *  Assistant function to check the correctness of StrToFat functionality
 *  @param  Source buffer of source Unicode string
 *  @parma  FatSize length of Source
 *  @param  Fat buffer of Fat string after StrToFat call
 *  @param  IsLongFileName whether Fat is a 8.3 file name
 *  @return TRUE/FALSE whether Result reflect the functionality of FatToStr on Original Fat string and FatSize
 */
BOOLEAN
CheckStrToFat (
  IN CHAR16                     *Source,
  IN UINTN                      FatSize,
  IN CHAR8                      *Fat,
  IN BOOLEAN                    IsLongFileName
  )
{
  //
  // The length of Fat should be less than FatSize and the length of Source
  //

  //
  // Comment out following check according to spec changed.
  //

  //if (GetStrLen8(Fat)>FatSize || GetStrLen8(Fat)>GetStrLen16(Source)) {
  //  return FALSE;
  //}

  //
  // Fat reflect Source correctly
  //
  while (*Source && FatSize) {
    if (*Source == '.' || *Source == ' ') {
      Source ++;
      continue;
    }

    if ((*Source < 0x100 && (EngInfoMap[*Source] & CHAR_FAT_VALID)) &&
         !(*Fat == EngUpperMap[*Source] || *Fat == EngLowerMap[*Source] )) {
      return FALSE;
    }

    if (!(*Source < 0x100 && (EngInfoMap[*Source] & CHAR_FAT_VALID)) && *Fat != '_') {
      return FALSE;
    }

    Source++;
    Fat++;
    FatSize--;
  }

  //
  // Comment out following check according to spec changed.
  //


  return TRUE;
}


/**
 *  Assistant function to check whether a string is in 8.3 filename
 *  @param  Fat file name
 *  @return TRUE/FALSE whether a string is a long file name, or not
 */
BOOLEAN
CheckLongFileName(
  IN CHAR16                     *Source,
  IN UINTN                      FatSize
  )
{
  //
  // Note 8.3 format means that files can have between 1 and 8 characters
  // in the file name. The name must start with a letter or a number and
  // can contain any characters except the following:
  //
  //                     . " / \ [ ] : ; | = , * ? (space)
  //
  // An 8.3 file name typically has a file name extension
  // between one and three characters long with the same character restrictions.
  // A period separates the file name from the file name extension.
  //

  while (*Source && FatSize) {
    if (*Source == '.' || *Source == ' ') {
      Source ++;
      continue;
    }

    if (!(*Source < 0x100 && (EngInfoMap[*Source] & CHAR_FAT_VALID))) {
      return TRUE;
    }

    Source++;
    FatSize--;
  }

  //
  // new spec doesn't check string length
  //
    return FALSE;
}

/**
 *  Assistant function to initialize the character mapping varible
 */
VOID
InitCharMapping()
{
  UINTN               Index;
  UINTN               Index2;


  for (Index = 0; Index < 0x100; Index++) {
    EngUpperMap[Index] = (CHAR8) Index;
    EngLowerMap[Index] = (CHAR8) Index;
    EngInfoMap[Index] = 0;

    if ((Index >= 'a'   &&  Index <= 'z')  ||
        (Index >= 0xe0  &&  Index <= 0xf6) ||
        (Index >= 0xf8  &&  Index <= 0xfe)) {

      Index2 = Index - 0x20;
      EngUpperMap[Index] = (CHAR8) Index2;
      EngLowerMap[Index2] = (CHAR8) Index;

      EngInfoMap[Index] |= CHAR_FAT_VALID;
      EngInfoMap[Index2] |= CHAR_FAT_VALID;
    }
  }

  for (Index = 0; OtherChars[Index]; Index++) {
    Index2 = OtherChars[Index];
    EngInfoMap[Index2] |= CHAR_FAT_VALID;
  }
}
