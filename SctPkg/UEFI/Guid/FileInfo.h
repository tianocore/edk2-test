/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#ifndef __FILE_INFO_H__
#define __FILE_INFO_H__

#define EFI_FILE_INFO_ID   \
  { 0x9576e92, 0x6d3f, 0x11d2, {0x8e, 0x39, 0x0, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

typedef struct {
  UINT64                  Size;
  UINT64                  FileSize;
  UINT64                  PhysicalSize;
  EFI_TIME                CreateTime;
  EFI_TIME                LastAccessTime;
  EFI_TIME                ModificationTime;
  UINT64                  Attribute;
  CHAR16                  FileName[1];
} EFI_FILE_INFO;

//
// The FileName field of the EFI_FILE_INFO data structure is variable length.
// Whenever code needs to know the size of the EFI_FILE_INFO data structure, it needs to
// be the size of the data structure without the FileName field.  The following macro
// computes this size correctly no matter how big the FileName array is declared.
// This is required to make the EFI_FILE_INFO data structure ANSI compilant.
//
#define SIZE_OF_EFI_FILE_INFO OFFSET_OF(EFI_FILE_INFO,FileName)

extern EFI_GUID gBlackBoxEfiFileInfoGuid;

#endif
