/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Byosoft Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  ConfigureClpParameterBlkBBTestFunction.c

Abstract:

  Interface Function Test Cases of Efi Configure CLP Parameter Block

--*/


#include "SctLib.h"
#include "PlatformToDriverConfigurationBBTestMain.h"


//EFI_GUID  gBlackBoxEfiPlatformToDriverConfigurationClpGuid = EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_GUID;

CHAR16 *StandardClpCmdVerb[] = {\
    L"cd",\
    L"creat",\
    L"delete",\
    L"dump",\
    L"exit",\
    L"help",\
    L"load",\
    L"reset",\
    L"set",\
    L"show",\
    L"start",\
    L"stop",\
    L"version"\
   };

 CHAR16 *StandardClpCmdOption[] = {\
    L"-all",L"-a",\
    L"-destination",\
    L"-display",L"-d",\
    L"-examine",L"-x",\
    L"-force",L"-f",\
    L"-help",L"-h",\
    L"-keep",L"-k",\
    L"-level",L"-l",\
    L"-output",L"-o",\
    L"-source",\
    L"-version",L"-v",\
    L"-wait",L"-w"\
    };

EFI_STATUS
ParseCLPCommandLine(
   IN     EFI_CONFIGURE_CLP_PARAMETER_BLK   *EfiClpParameterBlock,
   OUT  CLP_CMD                                                *CLPCmd
  )
{
  //EFI_STATUS                                 Status;
  CHAR8                                         *CLPCmdStr;
  UINT8                                          CommandVerbLength,CommandLength;
  UINT8                                          CommandOptionLength;
  UINT8                                          CommandTargetLength;
  
    CLPCmdStr = EfiClpParameterBlock->CLPCommand;
    CommandLength =  sizeof(CLPCmdStr);
    CommandVerbLength = 0;
    for(;;){
       if(*CLPCmdStr==L' '||*CLPCmdStr==L'\0'){
           break;
	}
	CLPCmdStr++;
	CommandVerbLength++;
    }

    gtBS->CopyMem(
	              (VOID*)CLPCmd->CLPCmdVerb,
                     (VOID*)(EfiClpParameterBlock->CLPCommand),
                     sizeof(UINT8) * CommandVerbLength
                     );
    CLPCmd->CLPCmdVerb[CommandVerbLength] = L'\0';

   if(CommandVerbLength==CommandLength){
   	CLPCmd->CLPCmdOption[0] = L'\0';
	CLPCmd->CLPCmdTarget[0] = L'\0';
	CLPCmd->CLPCmdTargetLength = 0;
   	return EFI_SUCCESS;
   }

    CommandOptionLength = 0;
    CLPCmdStr++;
    CommandVerbLength++;
    for(;;){
       if(*CLPCmdStr==L' '||*CLPCmdStr==L'\0'){
           break;
	}
	CLPCmdStr++;
	CommandOptionLength++;
    }

    gtBS->CopyMem(
	              (VOID*)CLPCmd->CLPCmdOption,
                     (VOID*)(EfiClpParameterBlock->CLPCommand+CommandVerbLength),
                     sizeof(UINT8) * CommandOptionLength
                     );
    CLPCmd->CLPCmdOption[CommandOptionLength] = L'\0';

   if((CommandVerbLength+CommandOptionLength+sizeof(CHAR8))==CommandLength){
   	
        CLPCmd->CLPCmdTarget[0] = L'\0';
	 CLPCmd->CLPCmdTargetLength = 0;
        return EFI_SUCCESS;
   }

   CommandTargetLength = 0;
   CLPCmdStr++;
   CommandOptionLength++;
   for(;;){
       if(*CLPCmdStr==L'\0'){
           break;
	}
	CLPCmdStr++;
	CommandTargetLength++;
    }
   gtBS->CopyMem(
	              (VOID*)CLPCmd->CLPCmdTarget,
                     (VOID*)(EfiClpParameterBlock->CLPCommand+CommandVerbLength+CommandOptionLength),
                     sizeof(UINT8) * CommandTargetLength
                     );
   CLPCmd->CLPCmdTarget[CommandTargetLength] = L'\0';
   CLPCmd->CLPCmdTargetLength = CommandTargetLength + 1;
   return EFI_SUCCESS;

}

/**
 *  Entrypoint for EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPCommand Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */

EFI_STATUS
EFIAPI
BBTestCLPCommandAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL                                   *StandardLib;
  EFI_STATUS                                                                                 Status;
  EFI_CONFIGURE_CLP_PARAMETER_BLK                                          *EfiClpParameterBlock;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL               *PlatformToDriverConfiguation;
  EFI_TEST_ASSERTION                                                                   AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  CLP_CMD                                      *CLPCmd;
  UINTN                                          Index,Index1;


  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  PlatformToDriverConfiguation = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

 //
 // Assertion Point
 //
 
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  //
  //  get protocol Instance
  //
  
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

  //*ParameterTypeGuid =EFI_NULL_GUID;
  *ParameterBlockSize = sizeof(EFI_CONFIGURE_CLP_PARAMETER_BLK);
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&EfiClpParameterBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for EfiClpParameterBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //
  // Invoke Query(), produce EFI_CONFIGURE_CLP_PARAMETER_BLK
  //
  Status=EFI_SUCCESS;
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguation->Query (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &EfiClpParameterBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid006,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() and verify the EfiClpParameterBlock is produced",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Verify the ParameterTypeGuid is the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_BLOCK
  //

  if(ParameterTypeGuid->Data1==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data1
  	&&ParameterTypeGuid->Data2==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data2
  	&&ParameterTypeGuid->Data3==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data3
  	&&ParameterTypeGuid->Data4[0]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[0]
  	&&ParameterTypeGuid->Data4[1]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[1]
  	&&ParameterTypeGuid->Data4[2]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[2]
  	&&ParameterTypeGuid->Data4[3]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[3]
  	&&ParameterTypeGuid->Data4[4]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[4]
  	&&ParameterTypeGuid->Data4[5]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[5]
  	&&ParameterTypeGuid->Data4[6]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[6]
  	&&ParameterTypeGuid->Data4[7]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[7]
  	) 
  {
    //
    // Suppose the EfiClpParameterBlock had been produced,verify the CLPCommand is correct.
    //

   Status = gtBS->AllocatePool (EfiBootServicesData,sizeof(CLP_CMD),(VOID **)&CLPCmd);
   if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for CLPCmd",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }

   Status = ParseCLPCommandLine( EfiClpParameterBlock, CLPCmd);

    AssertionType = EFI_TEST_ASSERTION_PASSED;
    for(Index=0;Index<Num_CLPCmdVerb;Index++){
       if(SctStrCmp ((CHAR16*)CLPCmd->CLPCmdVerb,StandardClpCmdVerb[Index])==0){
          //Index = Num_CLPCmdVerb;
          for(Index1=0;Index1<Num_CLPCmdOption;Index1++){
             if(SctStrCmp ((CHAR16*)CLPCmd->CLPCmdOption,StandardClpCmdOption[Index1])==0){
                 if((Index !=4) && (Index1 ==5||Index1==6||(Index1 >=9&&Index1<=12)||Index1==15||Index1==16||(Index1 >=18&&Index1<=21))){
                       AssertionType = EFI_TEST_ASSERTION_PASSED;
			  Index = Num_CLPCmdVerb;
			  Index1=Num_CLPCmdOption;
                       break;
		   }else if(Index==4&&(Index1 ==5||Index1==6||(Index1 >=9&&Index1<=12)||Index1==15||Index1==16||(Index1 >=18&&Index1<=20))){
		         AssertionType = EFI_TEST_ASSERTION_PASSED;
			  Index = Num_CLPCmdVerb;
			  Index1=Num_CLPCmdOption;
			  break;
		   }else if ((Index == 2 || (Index >= 6 && Index <= 11)) && (Index1 == 7 || Index1 == 8)){
                       AssertionType = EFI_TEST_ASSERTION_PASSED;
                       Index = Num_CLPCmdVerb;
			  Index1=Num_CLPCmdOption;
			  break;
		   }else if((Index==3&&Index1==2)||(Index==6&&Index1==17)||(Index==9&&(Index1>=0&&Index1<=4&&Index1!=2))){
                       AssertionType = EFI_TEST_ASSERTION_PASSED;
                       Index = Num_CLPCmdVerb;
			  Index1=Num_CLPCmdOption;
			  break;
		   }else{
		         AssertionType = EFI_TEST_ASSERTION_FAILED;
			  Index = Num_CLPCmdVerb;
			  Index1=Num_CLPCmdOption;
                       break;
		   }
             }else{
               AssertionType = EFI_TEST_ASSERTION_FAILED;
              }
          }
       }else{
          AssertionType = EFI_TEST_ASSERTION_FAILED;
          }
     }
  
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigureClpParameterTestAssertionGuid001,
                 L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPCommand,compare with Verb and Option Support Requirements Table",
                 L"%a:%d:  CLPCommandVerb = %d, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 (CHAR16*)CLPCmd->CLPCmdVerb,
                 EFI_SUCCESS
                 );
  } else{
        gtBS->FreePool (EfiClpParameterBlock);
	 return EFI_UNSUPPORTED;
  }

  gtBS->FreePool (CLPCmd);
  gtBS->FreePool (EfiClpParameterBlock);
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPReturnString Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
//
EFI_STATUS
EFIAPI
BBTestCLPReturnStringAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_CONFIGURE_CLP_PARAMETER_BLK       *EfiClpParameterBlock;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL               *PlatformToDriverConfiguation;
  EFI_TEST_ASSERTION                                                                   AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  CLP_CMD                                    *CLPCmd;
  UINTN                                           Index;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  PlatformToDriverConfiguation = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

 //
 // Assertion Point
 //
 
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  //
  //  get protocol Instance
  //
  
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //*ParameterTypeGuid =EFI_NULL_GUID;
  *ParameterBlockSize = sizeof(EFI_CONFIGURE_CLP_PARAMETER_BLK);
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&EfiClpParameterBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for EfiClpParameterBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }



  //
  // Invoke Query() and Response(), produce EFI_CONFIGURE_CLP_PARAMETER_BLK
  //
  Status=EFI_SUCCESS;
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguation->Query (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &EfiClpParameterBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid007,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query()/Response() and verify the EfiClpParameterBlock protocol is produced",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  /* if(Status==EFI_SUCCESS){
    Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );
    if(Status == EFI_SUCCESS) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid008,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response - Invoke Response() and verify the CLPReturnString of CLP protocol is allocated",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
   }*/
  }

  //
  // Verify the ParameterTypeGuid is the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_BLOCK
  //

  if(ParameterTypeGuid->Data1==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data1
  	&&ParameterTypeGuid->Data2==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data2
  	&&ParameterTypeGuid->Data3==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data3
  	&&ParameterTypeGuid->Data4[0]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[0]
  	&&ParameterTypeGuid->Data4[1]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[1]
  	&&ParameterTypeGuid->Data4[2]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[2]
  	&&ParameterTypeGuid->Data4[3]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[3]
  	&&ParameterTypeGuid->Data4[4]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[4]
  	&&ParameterTypeGuid->Data4[5]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[5]
  	&&ParameterTypeGuid->Data4[6]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[6]
  	&&ParameterTypeGuid->Data4[7]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[7]
  	) 
  {
    //
    // Suppose the EfiClpParameterBlock had been produced,verify the CLPReturnString is correct.
    //

   Status = gtBS->AllocatePool (EfiBootServicesData,sizeof(CLP_CMD),(VOID **)&CLPCmd);
   if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for CLPCmd",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
        //
       //if support "keyword=value" format,verify the return string
       //
       Status = ParseCLPCommandLine( EfiClpParameterBlock, CLPCmd);
	
       if(SctStrCmp ((CHAR16*)CLPCmd->CLPCmdOption, StandardClpCmdOption[15])==0||
	 	SctStrCmp ((CHAR16*)CLPCmd->CLPCmdOption ,StandardClpCmdOption[16])==0){
	 	for(Index=0;Index<CLPCmd->CLPCmdTargetLength;Index++){
                     if(SctStrnCmp ((CHAR16*)(CLPCmd->CLPCmdTarget + Index),L"format=keyword" ,sizeof(L"format=keyword"))==0){
                           AssertionType = EFI_TEST_ASSERTION_PASSED;
			      StandardLib->RecordAssertion (
                                                            StandardLib,
                                                            AssertionType,
                                                            gConfigureClpParameterTestAssertionGuid002,
                                                            L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPReturnString,verify the output string is format=keyword format",
                                                            L"%a:%d:  Expected=%r",
                                                            __FILE__,
                                                            (UINTN)__LINE__,
                                                            EFI_SUCCESS
                                                            );
				  break;
			}
		  }
        }
	 	
	//
	//if return  status is EFI_UNSUPPORTED
	//
       if(*(EfiClpParameterBlock->CLPReturnString)==EFI_UNSUPPORTED){
          AssertionType = EFI_TEST_ASSERTION_PASSED;

          StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigureClpParameterTestAssertionGuid002,
                 L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPReturnString,the UEFI Driver not support the SM CLP -output option requested by the caller",
                 L"%a:%d:  CLPReturnString = %d, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 *(EfiClpParameterBlock->CLPReturnString),
                 EFI_SUCCESS
                 );
       }
  
  } else{
     gtBS->FreePool (EfiClpParameterBlock);
     return EFI_UNSUPPORTED;
  }
  
  gtBS->FreePool (EfiClpParameterBlock);
  return EFI_SUCCESS;
}


/**
 *  Entrypoint for EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPReturnStatus Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS
//
EFI_STATUS
EFIAPI
BBTestCLPCmdStatusAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_CONFIGURE_CLP_PARAMETER_BLK       *EfiClpParameterBlock;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL               *PlatformToDriverConfiguation;
  EFI_TEST_ASSERTION                                                                   AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  CHAR16                                        Status_Tag;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  PlatformToDriverConfiguation = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

 //
 // Assertion Point
 //
 
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  //
  //  get protocol Instance
  //
  
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //*ParameterTypeGuid =EFI_NULL_GUID;
  *ParameterBlockSize = sizeof(EFI_CONFIGURE_CLP_PARAMETER_BLK);
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&EfiClpParameterBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for EfiClpParameterBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }



  //
  // Invoke Query(), produce EFI_CONFIGURE_CLP_PARAMETER_BLK
  //
  Status=EFI_SUCCESS;
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguation->Query (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &EfiClpParameterBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid009,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query()/Response() and verify the EfiClpParameterBlock protocol is produced",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Verify the ParameterTypeGuid is the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_BLOCK
  //

  if(ParameterTypeGuid->Data1==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data1
  	&&ParameterTypeGuid->Data2==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data2
  	&&ParameterTypeGuid->Data3==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data3
  	&&ParameterTypeGuid->Data4[0]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[0]
  	&&ParameterTypeGuid->Data4[1]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[1]
  	&&ParameterTypeGuid->Data4[2]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[2]
  	&&ParameterTypeGuid->Data4[3]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[3]
  	&&ParameterTypeGuid->Data4[4]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[4]
  	&&ParameterTypeGuid->Data4[5]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[5]
  	&&ParameterTypeGuid->Data4[6]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[6]
  	&&ParameterTypeGuid->Data4[7]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[7]
  	) 
  {
    //
    // Suppose the EfiClpParameterBlock had been produced,verify the CLPCmdStatus is correct.
    //
  
    switch(EfiClpParameterBlock->CLPCmdStatus){
     case  0:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Status_Tag     = COMMAND_COMPLETED;
		break;
     case  1:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Status_Tag     = COMMAND_SPAWNED;
		break;
     case  2:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Status_Tag     = COMMAND_PROCESSING_FAILED;
		break;
     case  3:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Status_Tag     = COMMAND_EXECUTION_FAILED;
		break;
     default:
	 	AssertionType = EFI_TEST_ASSERTION_FAILED;
		Status_Tag     = COMMAND_STATUS_ERROR;
		break;
    }
  
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigureClpParameterTestAssertionGuid003,
                 L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPCmdStatus,compare with Status Table return after Response",
                 L"%a:%d:  CLPCmdStatus = %d, Status_Tag = %s,Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiClpParameterBlock->CLPCmdStatus,
                 Status_Tag,
                 EFI_SUCCESS
                 );
  } else{
     return EFI_UNSUPPORTED;
  }
  
  return EFI_SUCCESS;
}

/**
 *  Entrypoint for EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPErrorValue Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
//
EFI_STATUS
EFIAPI
BBTestCLPErrorValueAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_CONFIGURE_CLP_PARAMETER_BLK       *EfiClpParameterBlock;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL               *PlatformToDriverConfiguation;
  EFI_TEST_ASSERTION                                                                   AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
//  UINT8                                          Index;
  UINT16                                        Error_Tag;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  PlatformToDriverConfiguation = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

 //
 // Assertion Point
 //
 
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  //
  //  get protocol Instance
  //
  
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //*ParameterTypeGuid =EFI_NULL_GUID;
  *ParameterBlockSize = sizeof(EFI_CONFIGURE_CLP_PARAMETER_BLK);
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&EfiClpParameterBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for EfiClpParameterBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }



  //
  // Invoke Query(), produce EFI_CONFIGURE_CLP_PARAMETER_BLK
  //
  Status=EFI_SUCCESS;
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguation->Query (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &EfiClpParameterBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid011,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query()/Response() and verify the EfiClpParameterBlock protocol is produced",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Verify the ParameterTypeGuid is the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_BLOCK
  //

  if(ParameterTypeGuid->Data1==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data1
  	&&ParameterTypeGuid->Data2==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data2
  	&&ParameterTypeGuid->Data3==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data3
  	&&ParameterTypeGuid->Data4[0]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[0]
  	&&ParameterTypeGuid->Data4[1]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[1]
  	&&ParameterTypeGuid->Data4[2]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[2]
  	&&ParameterTypeGuid->Data4[3]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[3]
  	&&ParameterTypeGuid->Data4[4]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[4]
  	&&ParameterTypeGuid->Data4[5]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[5]
  	&&ParameterTypeGuid->Data4[6]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[6]
  	&&ParameterTypeGuid->Data4[7]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[7]
  	) 
  {
    //
    // Suppose the EfiClpParameterBlock had been produced,verify the CLPErrorValue is correct.
    //
    switch(EfiClpParameterBlock->CLPErrorValue){
     case  255:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = COMMAND_ERROR_UNSPECIFIED;
		break;
     case  254:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = COMMAND_NOT_SUPPORTED;
		break;
     case  253:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = COMMAND_NOT_RECOGNIZED;
		break;
     case  252:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = COMMAND_SYNTAX_ERROR;
		break;
     case  251:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = INVALID_OPTION;
		break;
     case  250:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = INVALID_ARGUMENT;
		break;
     case  249:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = OUTPUT_FORMAT_NOT_SUPPORTED;
		break;
     case  248:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = MISSING_ARGUMENT;
		break;
     case  247:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = OPTION_NOT_SUPPORTED;
		break;
     case  246:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = INVALID_TARGET;
		break;
     case  245:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = REQUIRED_OPTION_MISSING;
		break;
     case  244:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = QUEUE_FULL;
		break;
     case  243:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = UNRECOGNIZED_OEM_EXTENSION;
		break;
     case  242:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = MISSING_REQUIRED_TARGET;
		break;
     case  241:
	 	AssertionType = EFI_TEST_ASSERTION_PASSED;
		Error_Tag     = FUNCTION_NOT_SUPPORTED;
		break;
     default:
	 	AssertionType = EFI_TEST_ASSERTION_FAILED;
		Error_Tag     = ERROR_VALUE_NOT_FOUND;
		break;
    }
  
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigureClpParameterTestAssertionGuid004,
                 L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPErrorValue,compare with ErrorValue  Table",
                 L"%a:%d:  CLPErrorValue = %d, Error_Tag = %s, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiClpParameterBlock->CLPErrorValue,
                 Error_Tag,
                 EFI_SUCCESS
                 );
	
    return EFI_SUCCESS;
  }
  return EFI_UNSUPPORTED;
  
}
/**
 *  Entrypoint for EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPMessageCode Parameter Test.
 *  @param This a pointer of EFI_BB_TEST_PROTOCOL.
 *  @param ClientInterface a pointer to the interface to be tested.
 *  @param TestLevel test "thoroughness" control.
 *  @param SupportHandle a handle containing protocols required.
 *  @return EFI_SUCCESS Finish the test successfully.
 */
//
// TDS 
//
EFI_STATUS
EFIAPI
BBTestCLPMessageCodeAutoTest (
  IN EFI_BB_TEST_PROTOCOL       *This,
  IN VOID                       *ClientInterface,
  IN EFI_TEST_LEVEL             TestLevel,
  IN EFI_HANDLE                 SupportHandle
  )
{
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL   *StandardLib;
  EFI_STATUS                           Status;
  EFI_CONFIGURE_CLP_PARAMETER_BLK       *EfiClpParameterBlock;
  EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL               *PlatformToDriverConfiguation;
  EFI_TEST_ASSERTION                                                                   AssertionType;
  EFI_HANDLE                                         *CtrlerHandles;
  UINTN                                                  CtrlerHandleNo;
  UINTN                                                  CtrlerHandleIndex;
  EFI_HANDLE                                         ChildHandle;
  UINTN                                          *Instance;
  EFI_GUID                                     *ParameterTypeGuid=NULL;
  UINTN                                          *ParameterBlockSize=0;
  UINT16                                         MsgCodeValue;
  //
  // Get the Standard Library Interface
  //
  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiStandardTestLibraryGuid,
                   (VOID **) &StandardLib
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

  PlatformToDriverConfiguation = (EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL *)ClientInterface;

 //
 // Assertion Point
 //
 
  // Get all the handles in the system.
  SctLocateHandle (AllHandles, NULL, NULL, &CtrlerHandleNo, &CtrlerHandles);

  //
  //  get protocol Instance
  //
  
  Status = gtBS->LocateProtocol (
                         &gBlackBoxEfiPlatformToDriverConfigurationProtocolGuid,
                         NULL,
                         (VOID **) &Instance
                         );
  if( EFI_ERROR(Status) ){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.LocateProtocol - Handle standard test library",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }
  
  //*ParameterTypeGuid =EFI_NULL_GUID;
  *ParameterBlockSize = sizeof(EFI_CONFIGURE_CLP_PARAMETER_BLK);
  ChildHandle =NULL;
  
  Status = gtBS->AllocatePool (EfiBootServicesData,*ParameterBlockSize,(VOID **)&EfiClpParameterBlock);
  if(EFI_ERROR(Status)){
     StandardLib->RecordAssertion (
                   StandardLib,
                   EFI_TEST_ASSERTION_FAILED,
                   gTestGenericFailureGuid,
                   L"BS.AllocatePool - Allocate pool memory for EfiClpParameterBlock",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
    return Status;
  }



  //
  // Invoke Query(), produce EFI_CONFIGURE_CLP_PARAMETER_BLK
  //
  Status=EFI_SUCCESS;
  for (CtrlerHandleIndex = 0; CtrlerHandleIndex < CtrlerHandleNo; CtrlerHandleIndex++) {
    while(!EFI_ERROR(Status)) {
      Status = PlatformToDriverConfiguation->Query (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         &ParameterTypeGuid,
                                         (VOID **) &EfiClpParameterBlock,
                                         ParameterBlockSize
                                         );
      if(Status == EFI_SUCCESS){
        Status = PlatformToDriverConfiguation->Response (
                                         PlatformToDriverConfiguation,
                                         CtrlerHandles[CtrlerHandleIndex],
                                         ChildHandle,
                                         Instance,
                                         ParameterTypeGuid,
                                         &EfiClpParameterBlock,
                                         *ParameterBlockSize,
                                         EfiPlatformConfigurationActionNone
                                         );			
        Instance++;
      }
    }

    if(Status == EFI_NOT_FOUND) {
      AssertionType = EFI_TEST_ASSERTION_PASSED;
    } else {
      AssertionType = EFI_TEST_ASSERTION_FAILED;
    }

    StandardLib->RecordAssertion (
                   StandardLib,
                   AssertionType,
                   gConfigureClpParameterTestAssertionGuid013,
                   L"EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query - Invoke Query() and verify the EfiClpParameterBlock protoco is producedl",
                   L"%a:%d:Status - %r",
                   __FILE__,
                   (UINTN)__LINE__,
                   Status
                   );
  }

  //
  // Verify the ParameterTypeGuid is the EFI_PLATFORM_TO_DRIVER_CONFIGURATION_CLP_BLOCK
  //

  if(ParameterTypeGuid->Data1==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data1
  	&&ParameterTypeGuid->Data2==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data2
  	&&ParameterTypeGuid->Data3==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data3
  	&&ParameterTypeGuid->Data4[0]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[0]
  	&&ParameterTypeGuid->Data4[1]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[1]
  	&&ParameterTypeGuid->Data4[2]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[2]
  	&&ParameterTypeGuid->Data4[3]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[3]
  	&&ParameterTypeGuid->Data4[4]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[4]
  	&&ParameterTypeGuid->Data4[5]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[5]
  	&&ParameterTypeGuid->Data4[6]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[6]
  	&&ParameterTypeGuid->Data4[7]==gBlackBoxEfiPlatformToDriverConfigurationClpGuid.Data4[7]
  	) 
  {
    //
    // Suppose the EfiClpParameterBlock had been produced,verify the CLPMsgCode is in the scope of the Probable Cause Value.
    //
  
    MsgCodeValue = EfiClpParameterBlock->CLPMsgCode;
    if(MsgCodeValue & 0x8000){
       // Bit15=1, Message Code is OEM Specific,ignore it
       return EFI_UNSUPPORTED;
    }
    else{
        if(EfiClpParameterBlock->CLPMsgCode<=130 && EfiClpParameterBlock->CLPMsgCode>=0) {
          AssertionType = EFI_TEST_ASSERTION_PASSED;
        }else{
          AssertionType = EFI_TEST_ASSERTION_FAILED;
        }
    }
  
    StandardLib->RecordAssertion (
                 StandardLib,
                 AssertionType,
                 gConfigureClpParameterTestAssertionGuid005,
                 L"EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPMsgCode,compare with Message Code Probable Cause Value",
                 L"%a:%d:  CLPMsgCode = %d, Expected=%r",
                 __FILE__,
                 (UINTN)__LINE__,
                 EfiClpParameterBlock->CLPMsgCode,
                 EFI_SUCCESS
                 );
  } else{
     return EFI_UNSUPPORTED;
  }
  
  return EFI_SUCCESS;
}

