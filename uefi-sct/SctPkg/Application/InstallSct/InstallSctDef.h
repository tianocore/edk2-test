/** @file

  Copyright 2006 - 2017 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
  Portions copyright (c) 2014, ARM Ltd. All rights reserved.<BR>
  (C) Copyright 2021 Hewlett Packard Enterprise Development LP<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/

#ifndef _EFI_INSTALL_SCT_DEF_H_
#define _EFI_INSTALL_SCT_DEF_H_

#if defined(EFI32)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"32"
  #define INSTALL_SCT_PLATFORM_NAME         L"IA32"
#elif defined(EFIX64)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"x64"
  #define INSTALL_SCT_PLATFORM_NAME         L"X64"
#elif defined(EFI64)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"64"
  #define INSTALL_SCT_PLATFORM_NAME         L"IPF"
#elif defined(EFIARM)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"arm"
  #define INSTALL_SCT_PLATFORM_NAME         L"ARM"
#elif defined(EFIAARCH64)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"aarch64"
  #define INSTALL_SCT_PLATFORM_NAME         L"AARCH64"
#elif defined(EFIRISCV64)
  #define INSTALL_SCT_PLATFORM_SHORT_NAME   L"riscv64"
  #define INSTALL_SCT_PLATFORM_NAME         L"RISCV64"
#else
  #error "Architecture not supported"
#endif

#endif
