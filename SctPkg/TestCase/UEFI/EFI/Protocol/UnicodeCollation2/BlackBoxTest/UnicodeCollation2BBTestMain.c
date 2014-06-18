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
                                                                
  Copyright (c) 2010 - 2011, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  UnicodeCollation2BBTestMain.c

Abstract:

  Test Driver of Unicode Collation2 Protocol

--*/


#include "SctLib.h"
#include "UnicodeCollation2BBTestMain.h"

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
  UNICODE_COLLATION2_PROTOCOL_TEST_REVISION,
  EFI_UNICODE_COLLATION2_PROTOCOL_GUID,
  L"Unicode Collation2 Protocol Test",
  L"UEFI Unicode Collation2 Protocol Test"
};


EFI_GUID gSupportProtocolGuid1[2] = {
  EFI_STANDARD_TEST_LIBRARY_GUID,
  EFI_NULL_GUID
};

EFI_BB_TEST_ENTRY_FIELD gBBTestEntryField[] = {
  {
    UNICODE_COLLATION2_PROTOCOL_STRICOLL_FUNCTION_AUTO_GUID,
    L"StriColl_Func",
    L"Perform auto function checkes on the StriColl interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStriCollFunctionAutoTest
  },
  {
    UNICODE_COLLATION2_PROTOCOL_METAIMATCH_FUNCTION_AUTO_GUID,
    L"MetaiMatch_Func",
    L"Perform auto function checkes on the MetaiMatch interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestMetaiMatchFunctionAutoTest
  },
  {
    UNICODE_COLLATION2_PROTOCOL_STRLWR_FUNCTION_AUTO_GUID,
    L"StrLwr_Func",
    L"Perform auto function checkes on the StrLwr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStrLwrFunctionAutoTest
  },
  {
    UNICODE_COLLATION2_PROTOCOL_STRUPR_FUNCTION_AUTO_GUID,
    L"StrUpr_Func",
    L"Perform auto function checkes on the StrUpr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestStrUprFunctionAutoTest
  },
  {
    UNICODE_COLLATION2_PROTOCOL_FATTOSTR_FUNCTION_AUTO_GUID,
    L"FatToStr_Func",
    L"Perform auto function checkes on the FatToStr interface",
    EFI_TEST_LEVEL_DEFAULT,
    gSupportProtocolGuid1,
    EFI_TEST_CASE_AUTO,
    BBTestFatToStrFunctionAutoTest
  },
  {
    UNICODE_COLLATION2_PROTOCOL_STRTOFAT_FUNCTION_AUTO_GUID,
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
BBTestUnicodeCollation2ProtocolUnload (
  IN EFI_HANDLE       ImageHandle
  );


/**
 *  Unicode Collation2 Protocol Test Driver Entry point.
 *  @param ImageHandle the driver image handle.
 *  @param SystemTable the system table.
 *  @return EFI_SUCCESS the driver is loaded successfully.
 */
EFI_STATUS
InitializeBBTestUnicodeCollation2 (
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
           BBTestUnicodeCollation2ProtocolUnload,
           &gBBTestProtocolInterface
           );
}

/**
 *  The driver's Unload function.
 *  @param ImageHandle the test driver image handle.
 *  @return EFI_SUCCESS unload successfully.
 */
EFI_STATUS
BBTestUnicodeCollation2ProtocolUnload (
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
