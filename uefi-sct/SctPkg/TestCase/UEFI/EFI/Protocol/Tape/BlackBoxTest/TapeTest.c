/** @file

  Copyright 2006 - 2010 Unified EFI, Inc.<BR>
  Copyright (c) 2010, Phoenix Corporation. All rights reserved.<BR>

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  TapeTest.c

Abstract:
  
  This driver supports TapeIo protocol test

--*/

#include "SctLib.h"
#include "TapeBBTestMain.h"
#include "TapeTest.h"

#define TAPE_IO_TEST_FILEMARK_CNT 5
#define TAPE_IO_TEST_BLOCKMARK_CNT 7
//
// Worker functions
//

/***********************************************************

***********************************************************/


#define MAX_TAPE_BUFFER_SIZE TAPE_BLOCK_SIZE
/*********************************************************


*********************************************************/
EFI_STATUS prepareTapeTest(int initTestFileMarkCnt, int initTestBlockMarkCnt)
{
  EFI_STATUS status;
  char *buffer=NULL;
  UINTN bufferSize = MAX_TAPE_BUFFER_SIZE; 
  EFI_INPUT_KEY Key;
  int index, ii;
  	
  buffer = (char *)SctAllocatePool (bufferSize);
  
  //  1.0 check input parameters
  if((buffer==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;	
    
  if(status == EFI_SUCCESS)
  {
	SctPrint (L"\r\n  Tape IO protocol Test will lose all data on the Tape? (Y/N)");
	status = gtST->ConIn->ReadKeyStroke (gtST->ConIn, &Key); 
	while(status == EFI_NOT_READY){
        status = gtST->ConIn->ReadKeyStroke(gtST->ConIn, &Key);
        if((status == EFI_SUCCESS) &&
           (Key.UnicodeChar != 'Y') && 
           (Key.UnicodeChar != 'y') && 
           (Key.UnicodeChar != 'N') && 
           (Key.UnicodeChar != 'n'))
        {
          // check for a valid key
          SctPrint (L"\r\n      Invalid selection ......................... enter (Y/N)");
          status = EFI_NOT_READY;
        }
    }

	if((Key.UnicodeChar == 'Y') || (Key.UnicodeChar == 'y'))
	{
        SctPrint (L"\r\n  Preparing tape ... ");
			 	
	  	for(index=0; index<(int)bufferSize; index++)
	  		buffer[index] = (char)index;

	  	//  Note: the returned status has not check after calling TapeIoProtocol()
	  	//  reset tape	driver	  	
	  	status = gTapeIoProtocol->TapeReset(gTapeIoProtocol, 1);  
	  	SctPrint (L"\r\n  Reset tape ... %s", ((status == EFI_SUCCESS) ? L"O.K." : L"Fail!") );
		if(status != EFI_SUCCESS)
			goto prepareTapeTestEnd;
			
	  	//  goto tape begin
	  	status = gTapeIoProtocol->TapeRewind(gTapeIoProtocol);	
	  	SctPrint (L"\r\n  Rewind tape I ... %s", ((status == EFI_SUCCESS) ? L"O.K." : L"Fail!") );
		if(status != EFI_SUCCESS)
			goto prepareTapeTestEnd;
			
	  	//  write some data and FileMark
	  	initTestFileMarkCnt = (initTestFileMarkCnt<TAPE_IO_TEST_FILEMARK_CNT) ? TAPE_IO_TEST_FILEMARK_CNT : initTestFileMarkCnt;
	  	for(index=0; index<initTestFileMarkCnt; index++)
	  	{	  	
	  		SctPrint (L"\r\n  Write tape(%d, %d) ... ", index+1, initTestBlockMarkCnt);
	  		for(ii=0; ii<initTestBlockMarkCnt; ii++)
	  		{
			  	bufferSize = MAX_TAPE_BUFFER_SIZE;
			  	status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, buffer);
			  	SctPrint (L"%s", ((status == EFI_SUCCESS) ? L"." : L"Fail!") );
			  	if(status != EFI_SUCCESS)
					goto prepareTapeTestEnd;
		  	}
		  	
		  	status = gTapeIoProtocol->TapeWriteFM(gTapeIoProtocol, 1);
		  	SctPrint (L" %s", ((status == EFI_SUCCESS) ? L"O.K." : L"Fail!") );
		  	if(status != EFI_SUCCESS)
				goto prepareTapeTestEnd;
	  	}
		                            
		//  write some other FileMark
		status = gTapeIoProtocol->TapeWriteFM(gTapeIoProtocol, 10);
		SctPrint (L"\r\n  WriteFM II ... %s", ((status == EFI_SUCCESS) ? L"O.K." : L"Fail!") );

        //  goto tape begin
	  	status = gTapeIoProtocol->TapeRewind(gTapeIoProtocol);
	  	SctPrint (L"\r\n  Rewind tape II ... %s", ((status == EFI_SUCCESS) ? L"O.K." : L"Fail!") );
	  	
	  	if(status != EFI_SUCCESS)
			goto prepareTapeTestEnd;	
    }
    
  } 

prepareTapeTestEnd:     
  if(buffer!=NULL)
  	tBS->FreePool (buffer);	  

  logMsg(gTapeBBTestMainAssertionGuid02E,
  			"EFI_TAPE_IO_PROTOCOL Test", 
  			"prepare for tape testing", 
  			status, 
  			EFI_SUCCESS
  		);  
  		
  SctPrint (L"\r\n  prepareTapeTest Completed.\r\n");		
  return status;	  
}

/*********************************************************


*********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionRead(  
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  char *buffer=NULL;
  UINTN bufferSize = MAX_TAPE_BUFFER_SIZE; 
  UINTN index;
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionRead",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  							
  buffer = (char *)SctAllocatePool (bufferSize);
  
  //  1.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((buffer==NULL)||(_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid001,
  			"EFI_TAPE_IO_PROTOCOL read test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);
  		
  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionReadEnd;		

  //  1.0.1 prepare Reading data
  prepareTapeTest(TAPE_IO_TEST_FILEMARK_CNT, TAPE_IO_TEST_BLOCKMARK_CNT);
  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionReadEnd;	
  	  	      
  //  1.1 TapeRead with valid parameters
  status = gTapeIoProtocol->TapeRead(gTapeIoProtocol, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid002,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"with valid parameters", 
  			status, 
  			EFI_SUCCESS
  		);

  switch(status)
  {
  	case EFI_SUCCESS:  	
  	case EFI_END_OF_FILE:	
		  //  1.1.1 verify reading data ...
		  for(index=0; index<bufferSize; index++)
		  	if(buffer[index]!=(char)(index&0xff))
		  		break;
		  
		  logMsg(gTapeBBTestMainAssertionGuid02F,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"verify reading data", 
  			((index==bufferSize)?EFI_SUCCESS:EFI_LOAD_ERROR), 
  			EFI_SUCCESS
  			);				    			 
		   
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_MEDIA_CHANGED:
  	case EFI_DEVICE_ERROR:
  	case EFI_INVALID_PARAMETER:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	default:
  		 goto BBTestTapeFunctionReadEnd;
  		 break;
  }
  

  //  1.2.1 TapeRead with invalid parameters
  status = gTapeIoProtocol->TapeRead(gTapeIoProtocol, &bufferSize, NULL);
  logMsg(gTapeBBTestMainAssertionGuid003,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"with invalid parameters(Buffer=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);

  //  1.2.2 TapeRead with invalid parameters
  status = gTapeIoProtocol->TapeRead(NULL, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid004,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);
  		
  //  1.3.1 TapeRead with valid parameters
  bufferSize = 0;
  status = gTapeIoProtocol->TapeRead(gTapeIoProtocol, &bufferSize, NULL);
  logMsg(gTapeBBTestMainAssertionGuid005,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"with valid parameters(bufferSize=0,buffer=NULL)", 
  			status, 
  			EFI_SUCCESS
  		);

  //  1.3.2 TapeRead with valid parameters
  bufferSize = 0;
  status = gTapeIoProtocol->TapeRead(gTapeIoProtocol, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid007,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"with valid parameters(bufferSize=0,buffer!=NULL)", 
  			status, 
  			EFI_SUCCESS
  		);
  		  		
#if 0  		  		  		
  //  1.4 do TapeRead with valid parameters until not EFI_SUCCESS  
  while(status==EFI_SUCCESS)
  {  	
  	bufferSize = MAX_TAPE_BUFFER_SIZE;
  	status = gTapeIoProtocol->TapeRead(gTapeIoProtocol, &bufferSize, buffer);
  }
  logMsg(gTapeBBTestMainAssertionGuid006,
  			"EFI_TAPE_IO_PROTOCOL.TapeRead", 
  			"do with valid parameters until not EFI_SUCCESS", 
  			status, 
  			EFI_SUCCESS
  		);
#endif
  		  
BBTestTapeFunctionReadEnd:		
  if(buffer!=NULL)
  	tBS->FreePool (buffer);
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionRead",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
							

  return EFI_SUCCESS;
}

/***********************************************************

***********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionWrite (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  char *buffer=NULL;
  UINTN bufferSize = MAX_TAPE_BUFFER_SIZE; 
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionWrite",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  							
  buffer = (char *)SctAllocatePool (bufferSize);
  
  //  2.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((buffer==NULL)||(_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid008,
  			"EFI_TAPE_IO_PROTOCOL write test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);  

  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionWriteEnd;	
  	
  //  2.1 TapeWrite with valid parameters
  status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid009,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite", 
  			"with valid parameters", 
  			status, 
  			EFI_SUCCESS
  		);

  switch(status)
  {
  	case EFI_SUCCESS:
  	case EFI_END_OF_MEDIA:	 
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_MEDIA_CHANGED:
  	case EFI_DEVICE_ERROR:
  	case EFI_INVALID_PARAMETER:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	case EFI_WRITE_PROTECTED:
  	case EFI_UNSUPPORTED:
  	default:
  		 goto BBTestTapeFunctionWriteEnd;
  		 break;
  }

  //  2.2.1 TapeWrite with invalid parameters
  bufferSize = MAX_TAPE_BUFFER_SIZE;
  status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, NULL);
  logMsg(gTapeBBTestMainAssertionGuid00A,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite(Buffer=NULL)", 
  			"with invalid parameters", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);

  //  2.2.2 TapeWrite with invalid parameters
  bufferSize = MAX_TAPE_BUFFER_SIZE;
  status = gTapeIoProtocol->TapeWrite(NULL, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid00B,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);

  //  2.3.1 TapeWrite with invalid parameters
  bufferSize = 0;
  status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, NULL);
  logMsg(gTapeBBTestMainAssertionGuid00C,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite", 
  			"with invalid parameters(bufferSize=0,buffer=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);

  //  2.3.2 TapeWrite with valid parameters
  bufferSize = 0;
  status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, buffer);
  logMsg(gTapeBBTestMainAssertionGuid00E,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite", 
  			"with valid parameters(bufferSize=0,buffer!=NULL)", 
  			status, 
  			EFI_SUCCESS
  		);
  		
#if 0  		  		
  //  2.4 do TapeWrite with valid parameters until not EFI_SUCCESS
  while(status==EFI_SUCCESS)
  {
  	bufferSize = MAX_TAPE_BUFFER_SIZE;
  	status = gTapeIoProtocol->TapeWrite(gTapeIoProtocol, &bufferSize, buffer);
  }
  logMsg(gTapeBBTestMainAssertionGuid00D,
  			"EFI_TAPE_IO_PROTOCOL.TapeWrite", 
  			"do with valid parameters until not EFI_SUCCESS", 
  			status, 
  			EFI_SUCCESS
  		);
#endif
  		  
BBTestTapeFunctionWriteEnd:	
  if(buffer!=NULL)
  	tBS->FreePool (buffer);		
  	    							
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionWrite",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
  
						

  return EFI_SUCCESS;
}


/***********************************************************

***********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionRewind (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionRewind",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  							
  //  3.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid010,
  			"EFI_TAPE_IO_PROTOCOL Rewind test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);   

  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionRewindEnd;	
  	
  
  //  3.1 TapeRewind with valid parameter							
  status = gTapeIoProtocol->TapeRewind(gTapeIoProtocol);
  logMsg(gTapeBBTestMainAssertionGuid011,
  			"EFI_TAPE_IO_PROTOCOL.Rewind", 
  			"with valid parameters", 
  			status, 
  			EFI_SUCCESS
  		);

  switch(status)
  {
  	case EFI_SUCCESS:
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_DEVICE_ERROR:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	case EFI_UNSUPPORTED:
  	default:
  		 goto BBTestTapeFunctionRewindEnd;
  		 break;
  }

  //  3.2 TapeRewind with invalid parameters
  status = gTapeIoProtocol->TapeRewind(NULL);
  logMsg(gTapeBBTestMainAssertionGuid012,
  			"EFI_TAPE_IO_PROTOCOL.TapeRewind", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);

BBTestTapeFunctionRewindEnd:  							
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionRewind",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
  							

  return EFI_SUCCESS;
}


/***********************************************************

***********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionSpace (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  INTN spaceDir;
  UINTN spaceType;
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionSpace",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  
  //  4.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid018,
  			"EFI_TAPE_IO_PROTOCOL Space test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);    

  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionSpaceEnd;	  	

  //  4.0.1 prepare Reading data
  prepareTapeTest(TAPE_IO_TEST_FILEMARK_CNT, TAPE_IO_TEST_BLOCKMARK_CNT);
  if(status != EFI_SUCCESS)
    goto BBTestTapeFunctionSpaceEnd;	

  //  4.1.1.a.0 rewind tape
  status = gTapeIoProtocol->TapeRewind(gTapeIoProtocol);
  logMsg(gTapeBBTestMainAssertionGuid01F,
	  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
	  			"call TapeRewind for TapeSpace (spaceType=BLOCK) testing", 
	  			status, 
	  			EFI_SUCCESS
	  		);  
  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionSpaceEnd;
  	  							
  //  4.1.1.a.1 TapeSpace by BlockMark with valid parameter
  spaceDir  = TAPE_IO_TEST_BLOCKMARK_CNT;
  spaceType = TAPE_SPACE_TYPE_BLOCK;  
  status = gTapeIoProtocol->TapeSpace(gTapeIoProtocol, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid019,
  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
  			"with valid parameters(spaceDir>0,spaceType=BLOCK)", 
  			status, 
  			EFI_SUCCESS
  		);
  		
  if(status != EFI_SUCCESS)		
  	goto BBTestTapeFunctionSpaceEnd;

  //  4.1.1.b.0 rewind tape
  status = gTapeIoProtocol->TapeRewind(gTapeIoProtocol);
  logMsg(gTapeBBTestMainAssertionGuid01F,
                "EFI_TAPE_IO_PROTOCOL.TapeSpace", 
                "call TapeRewind for TapeSpace (spaceType=FILEMARK) testing", 
                status, 
                EFI_SUCCESS
            );  
  if(status != EFI_SUCCESS)
    goto BBTestTapeFunctionSpaceEnd;

  //  4.1.1.b.1 TapeSpace by FileMark with valid parameter
  spaceDir  = TAPE_IO_TEST_FILEMARK_CNT;
  spaceType = TAPE_SPACE_TYPE_FILEMARK;  
  status = gTapeIoProtocol->TapeSpace(gTapeIoProtocol, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid01E,
	  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
	  			"with valid parameters(spaceDir>0,spaceType=FILEMARK)", 
	  			status, 
	  			EFI_SUCCESS
	  		);	
  
  switch(status)
  {
  	case EFI_SUCCESS:
  	case EFI_END_OF_MEDIA:
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_MEDIA_CHANGED:
  	case EFI_DEVICE_ERROR:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	case EFI_UNSUPPORTED:
  	default:
  		 goto BBTestTapeFunctionSpaceEnd;
  		 break;
  } 	
  
  //  4.1.2 TapeSpace with valid parameter
  spaceDir  = -5;
  //spaceType = TAPE_SPACE_TYPE_BLOCK;  
  status = gTapeIoProtocol->TapeSpace(gTapeIoProtocol, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid01A,
  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
  			"with valid parameters(spaceDir<0)", 
  			status, 
  			EFI_SUCCESS
  		);

  //  4.1.3 TapeSpace with valid parameter
  spaceDir  = 0;
  //spaceType = TAPE_SPACE_TYPE_BLOCK;  
  status = gTapeIoProtocol->TapeSpace(gTapeIoProtocol, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid01B,
  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
  			"with valid parameters(spaceDir=0)", 
  			status, 
  			EFI_SUCCESS
  		);  		

  //  4.2.1 TapeSpace with invalid parameter
  spaceDir  = 5;
  //spaceType = TAPE_SPACE_TYPE_BLOCK;  
  status = gTapeIoProtocol->TapeSpace(NULL, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid01C,
  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);  

  //  4.2.2 TapeSpace with invalid parameter
  spaceDir  = 5;
  spaceType++;  
  status = gTapeIoProtocol->TapeSpace(gTapeIoProtocol, spaceDir, spaceType);							
  logMsg(gTapeBBTestMainAssertionGuid01D,
  			"EFI_TAPE_IO_PROTOCOL.TapeSpace", 
  			"with invalid parameters(spaceType invalid)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);  
  		
BBTestTapeFunctionSpaceEnd:  		  						
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionSpace",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
  							

  return EFI_SUCCESS;
}


/***********************************************************

***********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionWriteFM (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  INTN Count;
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionWriteFM",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  
  //  5.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid020,
  			"EFI_TAPE_IO_PROTOCOL WriteFM test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);     

  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionWriteFMEnd;	
  	
  //  5.1 TapeWriteFM with valid parameter
  Count = 1;
  status = gTapeIoProtocol->TapeWriteFM(gTapeIoProtocol, Count);					
  logMsg(gTapeBBTestMainAssertionGuid021,
  			"EFI_TAPE_IO_PROTOCOL.TapeWriteFM", 
  			"with valid parameters(Count=1)", 
  			status, 
  			EFI_SUCCESS
  		);

  switch(status)
  {
  	case EFI_SUCCESS:
  	case EFI_END_OF_MEDIA:
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_MEDIA_CHANGED:
  	case EFI_DEVICE_ERROR:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	case EFI_UNSUPPORTED:
  	default:
  		 goto BBTestTapeFunctionWriteFMEnd;
  		 break;
  } 		 

  //  5.2 TapeWriteFM with invalid parameter
  status = gTapeIoProtocol->TapeWriteFM(NULL, Count);							
  logMsg(gTapeBBTestMainAssertionGuid022,
  			"EFI_TAPE_IO_PROTOCOL.TapeWriteFM", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);  

BBTestTapeFunctionWriteFMEnd:    							
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionWriteFM",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
  							

  return EFI_SUCCESS;
}


/***********************************************************

***********************************************************/
EFI_STATUS
EFIAPI
BBTestTapeFunctionReset (
  IN EFI_BB_TEST_PROTOCOL             *_This,
  IN VOID                             *ClientInterface,
  IN EFI_TEST_LEVEL                   TestLevel,
  IN EFI_HANDLE                       SupportHandle
  )
{
  EFI_STATUS status;
  BOOLEAN extendReset;
  
  getStandardLibInterface(SupportHandle);
  //
  // Enter a function. It is put at the entry point of a function
  LogEnterFunction( LoggingLib, 
  							L"BBTestTapeFunctionReset",
  							L"%a:%d : EnterFunction",
  							__FILE__, (UINTN)__LINE__ );  
  
  //  6.0 check input parameters
  gTapeIoProtocol = (EFI_TAPE_IO_PROTOCOL *)ClientInterface;
  if((_This==NULL) || (LoggingLib==NULL) || (gTapeIoProtocol==NULL))
  	status = EFI_INVALID_PARAMETER;
  else
    status = EFI_SUCCESS;
  logMsg(gTapeBBTestMainAssertionGuid028,
  			"EFI_TAPE_IO_PROTOCOL Reset test", 
  			"check input parameters", 
  			status, 
  			EFI_SUCCESS
  		);      

  if(status != EFI_SUCCESS)
  	goto BBTestTapeFunctionResetEnd;	

  
  //  6.1.1 TapeReset with valid parameter
  extendReset = 1;
  status = gTapeIoProtocol->TapeReset(gTapeIoProtocol, extendReset);  					
  logMsg(gTapeBBTestMainAssertionGuid029,
  			"EFI_TAPE_IO_PROTOCOL.TapeReset", 
  			"with valid parameters(extendReset=TRUE)", 
  			status, 
  			EFI_SUCCESS
  		);

  switch(status)
  {
  	case EFI_SUCCESS:
  		 break;
  	  	
  	case EFI_NO_MEDIA:
  	case EFI_DEVICE_ERROR:
  	case EFI_NOT_READY:
  	case EFI_TIMEOUT:
  	case EFI_UNSUPPORTED:
  	default:
  		 goto BBTestTapeFunctionResetEnd;
  		 break;
  }

  //  6.1.2 TapeReset with valid parameter
  extendReset = 0;
  status = gTapeIoProtocol->TapeReset(gTapeIoProtocol, extendReset);  					
  logMsg(gTapeBBTestMainAssertionGuid02A,
  			"EFI_TAPE_IO_PROTOCOL.TapeReset", 
  			"with valid parameters(extendReset=FALSE)", 
  			status, 
  			EFI_SUCCESS
  		);

  //  6.2 TapeReset with invalid parameter
  status = gTapeIoProtocol->TapeReset(NULL, extendReset);							
  logMsg(gTapeBBTestMainAssertionGuid022,
  			"EFI_TAPE_IO_PROTOCOL.TapeReset", 
  			"with invalid parameters(EFI_TAPE_IO_PROTOCOL=NULL)", 
  			status, 
  			EFI_INVALID_PARAMETER
  		);  

BBTestTapeFunctionResetEnd:  		 		   						
  //
  // Exit a function. It is put at the exit point of a function
  LogExitFunction( LoggingLib, 
  							L"BBTestTapeFunctionReset",
  							L"%a:%d : ExitFunction",
  							__FILE__, (UINTN)__LINE__ );
  							

  return EFI_SUCCESS;
}


/***********************************************************

***********************************************************/
typedef struct{
	EFI_STATUS status;
	char *message;
}EfiMsgStrStruct;

EfiMsgStrStruct TapeStatusMsgArr[]=
{
	{EFI_SUCCESS, 		"EFI_SUCCESS"},
	{EFI_END_OF_FILE, 	"EFI_END_OF_FILE"},
	{EFI_NO_MEDIA, 		"EFI_NO_MEDIA"},
	{EFI_MEDIA_CHANGED, "EFI_MEDIA_CHANGED"},
	{EFI_DEVICE_ERROR, 	"EFI_DEVICE_ERROR"},
	{EFI_INVALID_PARAMETER, "EFI_INVALID_PARAMETER"},
	{EFI_NOT_READY, 	"EFI_NOT_READY"},
	{EFI_TIMEOUT, 		"EFI_TIMEOUT"},
	{EFI_END_OF_MEDIA, 	"EFI_END_OF_MEDIA"},
	{EFI_WRITE_PROTECTED, "EFI_WRITE_PROTECTED"},
	{EFI_UNSUPPORTED, 	"EFI_UNSUPPORTED"}
};
		
char *getErrorMsgStr( EFI_STATUS status )
{
	int index;
	
	for(index=0; index<sizeof(TapeStatusMsgArr)/sizeof(EfiMsgStrStruct); index++)
		if(TapeStatusMsgArr[index].status == status)
			return TapeStatusMsgArr[index].message;
			
	return (char *)"unknown status!";
}	


/***********************************************************

***********************************************************/
void dumpTapeHeaderInfo(tape_header *tapeHdr)
{
	char *ptr;
	
	if(tapeHdr == NULL)
		return;
		
	ptr = (char *)&tapeHdr->Signature;
	my_printf((L"\r\n  %16s: %c%c%c%c%c%c%c%c", 
				"Signature", 
				ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7]
				));
				
	my_printf((L"\r\n  %16s: %d", 
				"Revision", 
				tapeHdr->Revision
				));

	my_printf((L"\r\n  %16s: %d bytes/block", 
				"BootDescSize", 
				tapeHdr->BootDescSize
				));
				
	my_printf((L"\r\n  %16s: %08Xh", 
				"BootDescCRC", 
				tapeHdr->BootDescCRC
				));
				

	my_printf((L"\r\n  %16s: %g", 
				"TapeGuid", 
				&tapeHdr->TapeGuid
				));
				
	my_printf((L"\r\n  %16s: %g", 
				"TapeType", 
				&tapeHdr->TapeType
				));
				
	my_printf((L"\r\n  %16s: %g", 
				"TapeUnique", 
				&tapeHdr->TapeUnique
				));	
				
	my_printf((L"\r\n  %16s: %d", 
				"BLLocation", 
				tapeHdr->BLLocation
				));
				
	my_printf((L"\r\n  %16s: %d bytes", 
				"BLBlocksize", 
				tapeHdr->BLBlocksize
				));
				
	my_printf((L"\r\n  %16s: %d bytes", 
				"BLFilesize", 
				tapeHdr->BLFilesize
				));

	my_printf((L"\r\n  %16s: %s", 
				"OSVersion", 
				tapeHdr->OSVersion
				));	
	my_printf((L"\r\n  %16s: %s", 
				"AppVersion", 
				tapeHdr->AppVersion
				));	
	my_printf((L"\r\n  %16s: %s", 
				"CreationDate", 
				tapeHdr->CreationDate
				));	
	my_printf((L"\r\n  %16s: %s", 
				"CreationTime", 
				tapeHdr->CreationTime
				));	

	my_printf((L"\r\n  %16s: %s", 
				"SystemName", 
				tapeHdr->SystemName
				));	
	my_printf((L"\r\n  %16s: %s", 
				"TapeTitle", 
				tapeHdr->TapeTitle
				));	
}
