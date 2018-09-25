/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Sct.h

Abstract:

  SCT master include file.

--*/

#ifndef _EFI_SCT_H_
#define _EFI_SCT_H_

//
// Includes
//

#include "SctLib.h"
#include <Library/EfiTestLib.h>
#include "LibPrivate.h"

#include EFI_TEST_PROTOCOL_DEFINITION(TestProfileLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestRecoveryLibrary)
#include EFI_TEST_PROTOCOL_DEFINITION(TestLoggingLibrary)

#include "ApTest.h"

#include "SctTypes.h"
#include "SctCore.h"

#include "Execute/ExecuteSupport.h"

#include "SctData.h"
#include "SctDataEx.h"
#include "SctDebug.h"
#include "SctExecute.h"
#include "SctLoad.h"
#include "SctMisc.h"
#include "SctOperation.h"
#include "SctOutput.h"
#include "SctReport.h"
#include "SctDeviceConfig.h"
#include "SctUi.h"

#include "SctDef.h"


#include "Eas.h"

#endif
