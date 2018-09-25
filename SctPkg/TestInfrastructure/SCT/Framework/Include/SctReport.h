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
/*++

Module Name:

  SctReport.h

Abstract:

  This file provides the test report generation services.

--*/

#ifndef _EFI_SCT_REPORT_H_
#define _EFI_SCT_REPORT_H_

//
// External functions declarations
//

EFI_STATUS
GetInstanceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL                         *DevicePath,
  IN CHAR16                                           *FilePath,
  IN CHAR16                                           *MetaName,
  OUT EFI_SCT_LOG_STATE                               *FileState,
  OUT UINT32                                          *Index,
  OUT UINT32                                          *Iteration,
  OUT UINT32                                          *PassNumber,
  OUT UINT32                                          *WarnNumber,
  OUT UINT32                                          *FailNumber
  );

EFI_STATUS
GetInterfaceAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL                         *DevicePath,
  IN CHAR16                                           *FilePath,
  IN CHAR16                                           *MetaName,
  OUT UINT32                                          *PassNumber,
  OUT UINT32                                          *WarnNumber,
  OUT UINT32                                          *FailNumber
  );

EFI_STATUS
GetProtocolAssertion (
  IN EFI_DEVICE_PATH_PROTOCOL                         *DevicePath,
  IN CHAR16                                           *FileName,
  OUT UINT32                                          *PassNumber,
  OUT UINT32                                          *WarnNumber,
  OUT UINT32                                          *FailNumber
  );

EFI_STATUS
GenerateReport (
  IN EFI_DEVICE_PATH_PROTOCOL                         *DevicePath,
  IN CHAR16                                           *LogFilePath,
  IN CHAR16                                           *ReportFileName
  );

#endif
