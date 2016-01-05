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
                                                                
  Copyright 2016 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>   
   
--*/


#ifndef _NVDATASTRUC_H_
#define _NVDATASTRUC_H_

#include <Guid/HiiPlatformSetupFormset.h>
#include <Guid/HiiFormMapMethodGuid.h>
#include <Guid/DriverSampleHii.h>
#include <Guid/ZeroGuid.h>

#define CONFIGURATION_VARSTORE_ID    0x1234

#pragma pack(1)
typedef struct {
  UINT16  WhatIsThePassword[20];
  UINT16  WhatIsThePassword2[20];
  UINT16  MyStringData[40];
  UINT16  PasswordClearText[20];
  UINT16  SomethingHiddenForHtml;
  UINT8   HowOldAreYouInYearsManual;
  UINT16  HowTallAreYouManual;
  UINT8   HowOldAreYouInYears;
  UINT16  HowTallAreYou;
  UINT8   MyFavoriteNumber;
  UINT8   TestLateCheck;
  UINT8   TestLateCheck2;
  UINT8   QuestionAboutTreeHugging;
  UINT8   QuestionAboutTreeHugging1;
  UINT8   QuestionAboutTreeHugging2;
  UINT8   ChooseToActivateNuclearWeaponry;
  UINT8   SuppressGrayOutSomething;
  UINT8   OrderedList[8];
  UINT16  BootOrder[8];
  UINT8   BootOrderLarge;
  UINT8   DynamicRefresh;
  UINT8   DynamicOneof;
  UINT8   DynamicOrderedList[5];
  UINT8   Reserved;
  EFI_HII_REF RefData;
  UINT8   NameValueVar0;
  UINT16  NameValueVar1;
  UINT16  NameValueVar2[20];
  UINT8   SerialPortNo;
  UINT8   SerialPortStatus;
  UINT16  SerialPortIo;
  UINT8   SerialPortIrq;
  UINT8   GetDefaultValueFromCallBack;
  UINT8   GetDefaultValueFromAccess;
  EFI_HII_TIME  Time;
  UINT8   RefreshGuidCount;
  UINT8   Match2;
} DRIVER_SAMPLE_CONFIGURATION;

//
// 2nd NV data structure definition
//
typedef struct {
  UINT8         Field8;
  UINT16        Field16;
  UINT8         OrderedList[3];
} MY_EFI_VARSTORE_DATA;

//
// Labels definition
//
#define LABEL_UPDATE1               0x1234
#define LABEL_UPDATE2               0x2234
#define LABEL_UPDATE3               0x3234
#define LABEL_END                   0x2223

#pragma pack()

#endif
