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
                                                                
  Copyright 2006 - 2012 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2012, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  ParseResult.c

--*/

#include "SCRTApp.h"
#include "ParseConf.h"

#pragma pack(1)

typedef union _VAR_INFO
{
  struct {
    UINT16 SetVariable        : 1;
    UINT16 GetVariable        : 1;
    UINT16 GetNextVariable    : 1;
    UINT16 QueryVariable      : 1;
    UINT16 GetTime            : 1;
    UINT16 SetTime            : 1;
    UINT16 SetWakeupTime      : 1;
    UINT16 GetWakeupTime      : 1;
    UINT16 QueryCapsule       : 1;
    UINT16 UpdateCapsule      : 1;
    UINT16 GetNextCount       : 1;
    UINT16 ColdReset          : 1;
    UINT16 WarmReset          : 1;
    UINT16 ShutDown           : 1;
    UINT16 Reserved           : 2;
  } BitMap;
  UINT16   TestData;
} VAR_INFO;

typedef struct _TEST_RECORD
{
  VAR_INFO Request;
  VAR_INFO  Result;
} TEST_RECORD;

#pragma pack()

CHAR16  *gTestRecordName      = L"TestRecord";
#define  TEST_RECORD_GUID    \
{ 0x6205d3e7, 0x9bde, 0x4e81, {0x8a, 0xb8, 0xf4, 0x5f, 0xa7, 0xed, 0x46, 0x6}}


EFI_STATUS
GetVariableRecord (
  TEST_RECORD      *TestRecord
  )
{
  UINTN         DataSize;
  EFI_STATUS    Status;
  EFI_GUID      VariableTestGuid = TEST_RECORD_GUID;

  DataSize     = sizeof(TEST_RECORD);
  //
  // get the record variable.
  //
  Status = tRT->GetVariable (
                  gTestRecordName,     
                  &VariableTestGuid,   
                  NULL,                
                  &DataSize,           
                  TestRecord           
                  );
  return Status;
}

EFI_STATUS
SCRTLogProcess(
  CHAR16  *InfFileName
  
)
{

  TEST_RECORD             TestRecord;
  VAR_INFO                Request;
  VAR_INFO                Result;
  BOOLEAN                 FirstFail;
  EFI_FILE_INFO           *FileInfo;
  EFI_FILE_HANDLE         FileHandle;  
  EFI_STATUS              Status;
  UINTN                   BufferSize;
  CHAR8                   Buffer[100];
  EFI_GUID                VariableTestGuid = TEST_RECORD_GUID;
  

  FirstFail   = FALSE;
  Status = GetVariableRecord(&TestRecord);
  if (EFI_ERROR (Status)) {
    SctPrint(L"Cannot find test record variable\n");
    return Status;
  }
  
  //
  // Create the Log file
  //  
  Status = SctOpenFileByName (
             InfFileName,
             &FileHandle,
             EFI_FILE_MODE_CREATE | EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE,
             0
             );
  if (EFI_ERROR (Status)) {
    SctPrint(L"Fail to create the Log file\n");     
    return Status;
  }

  //
  // If the file is directory, abort
  //
  Status = SctGetFileInfo (FileHandle, &FileInfo);
  if (EFI_ERROR (Status)) {
    SctPrint(L"Fail to open the Log file: %r\n", Status);
    return EFI_ABORTED;
  } else if (FileInfo->Attribute & EFI_FILE_DIRECTORY) {
    SctPrint(L"%s is a directory.\n", InfFileName);
    return EFI_ABORTED;
  }

  SctPrint (L"Success to get test record variable\n");
  SctPrint (L"Begin to parse the record...\n");
  Request.TestData   = TestRecord.Request.TestData;
  Result.TestData    = TestRecord.Result.TestData;

  SctPrint (L"\n********************Variable Test Group*******************\n\n");
  SctZeroMem (Buffer, 100);
  BufferSize  = 100;
  SctASPrint(Buffer, BufferSize, "\n********************Variable Test Group*******************\n\n");
  BufferSize = SctAsciiStrSize (Buffer);  
  SctWriteFile (FileHandle, &BufferSize, Buffer);

  if (Request.BitMap.SetVariable){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"SetVariable");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"SetVariable");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);
    if (Result.BitMap.SetVariable) {
      SctPrint (L"%5s %-20s Pass\n", L" ", L"SetVariable");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"SetVariable");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    } else {
      FirstFail = TRUE;
      SctPrint (L"%5s %-20s Fail\n", L" ", L"SetVariable");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"SetVariable");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    } 
  }

  if (Request.BitMap.GetVariable){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"GetVariable");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"GetVariable");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.GetVariable) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"GetVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"GetVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"GetVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"GetVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"GetVariable");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"GetVariable");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }


  if (Request.BitMap.GetNextVariable){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"GetNextVariable");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"GetNextVariable");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);		
    if (!FirstFail) {
      if (Result.BitMap.GetNextVariable) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"GetNextVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"GetNextVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"GetNextVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"GetNextVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"GetNextVariable");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"GetNextVariable");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    } 
  }

  if (Request.BitMap.QueryVariable){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"QueryVariable");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"QueryVariable");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);		
    if (!FirstFail) {
      if (Result.BitMap.QueryVariable) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"QueryVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"QueryVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"QueryVariable");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"QueryVariable");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      }
    } else{
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"QueryVariable");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"QueryVariable");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  SctPrint (L"\n*********************Time Test Group**********************\n\n");
  SctZeroMem (Buffer, 100);
  BufferSize  = 100;
  SctASPrint(Buffer, BufferSize, "\n*********************Time Test Group**********************\n\n");
  BufferSize = SctAsciiStrSize (Buffer);  
  SctWriteFile (FileHandle, &BufferSize, Buffer);
  
  if (Request.BitMap.GetTime){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"GetTime");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"GetTime");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {    
      if (Result.BitMap.GetTime) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"GetTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"GetTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"GetTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"GetTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"GetTime");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"GetTime");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.SetTime){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"SetTime");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"SetTime");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {     
      if (Result.BitMap.SetTime) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"SetTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"SetTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"SetTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"SetTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"SetTime");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"SetTime");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.SetWakeupTime){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"SetWakeupTime");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"SetWakeupTime");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {    
      if (Result.BitMap.SetWakeupTime) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"SetWakeupTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"SetWakeupTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"SetWakeupTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"SetWakeupTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"SetWakeupTime");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"SetWakeupTime");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.GetWakeupTime){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"GetWakeupTime");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"GetWakeupTime");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.GetWakeupTime) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"GetWakeupTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"GetWakeupTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"GetWakeupTime");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"GetWakeupTime");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"GetWakeupTime");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"GetWakeupTime");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }


  SctPrint (L"\n********************Capsule Test Group********************\n\n");
  SctZeroMem (Buffer, 100);
  BufferSize  = 100;
  SctASPrint(Buffer, BufferSize, "\n********************Capsule Test Group********************\n\n");
  BufferSize = SctAsciiStrSize (Buffer);  
  SctWriteFile (FileHandle, &BufferSize, Buffer);

  if (Request.BitMap.QueryCapsule){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"QueryCapsule");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"QueryCapsule");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.QueryCapsule) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"QueryCapsule");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"QueryCapsule");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail   =TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"QueryCapsule");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"QueryCapsule");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"QueryCapsule");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"QueryCapsule");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.UpdateCapsule){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"UpdateCapsule");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"UpdateCapsule");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.UpdateCapsule) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"UpdateCapsule");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"UpdateCapsule");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"UpdateCapsule");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"UpdateCapsule");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"UpdateCapsule");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"UpdateCapsule");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }


  SctPrint (L"\n*********************Misc Test Group**********************\n\n");
  SctZeroMem (Buffer, 100);
  BufferSize  = 100;
  SctASPrint(Buffer, BufferSize, "\n*********************Misc Test Group**********************\n\n");
  BufferSize = SctAsciiStrSize (Buffer);  
  SctWriteFile (FileHandle, &BufferSize, Buffer);

  if (Request.BitMap.GetNextCount){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"GetNextCount");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"GetNextCount");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.GetNextCount) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"GetNextCount");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"GetNextCount");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"GetNextCount");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"GetNextCount");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"GetNextCount");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"GetNextCount");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  SctPrint (L"\n*********************Reset Test Group*********************\n\n");
  SctZeroMem (Buffer, 100);
  BufferSize  = 100;
  SctASPrint(Buffer, BufferSize, "\n*********************Reset Test Group*********************\n\n");
  BufferSize = SctAsciiStrSize (Buffer);  
  SctWriteFile (FileHandle, &BufferSize, Buffer);

  if (Request.BitMap.ColdReset){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"ColdReset");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"ColdReset");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.ColdReset) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"ColdReset");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"ColdReset");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"ColdReset");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"ColdReset");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"ColdReset");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"ColdReset");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.WarmReset){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"WarmReset");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"WarmReset");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.WarmReset) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"WarmReset");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"WarmReset");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;
        SctPrint (L"%5s %-20s Fail\n", L" ", L"WarmReset");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"WarmReset");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"WarmReset"); 
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"WarmReset");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  }

  if (Request.BitMap.ShutDown){
    SctPrint (L"%5s %-20s Requested\n", L" ", L"ShutDown");
    SctZeroMem (Buffer, 100);
    BufferSize = 100;
    SctASPrint(Buffer, BufferSize, "%5s %-20s Requested\n", L" ", L"ShutDown");
    BufferSize = SctAsciiStrSize (Buffer);
    SctWriteFile (FileHandle, &BufferSize, Buffer);	
    if (!FirstFail) {
      if (Result.BitMap.ShutDown) {
        SctPrint (L"%5s %-20s Pass\n", L" ", L"ShutDown");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Pass\n", L" ", L"ShutDown");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } else {
        FirstFail  = TRUE;      
        SctPrint (L"%5s %-20s Fail\n", L" ", L"ShutDown");
        SctZeroMem (Buffer, 100);
        BufferSize = 100;
        SctASPrint(Buffer, BufferSize, "%5s %-20s Fail\n", L" ", L"ShutDown");
        BufferSize = SctAsciiStrSize (Buffer);
        SctWriteFile (FileHandle, &BufferSize, Buffer);
      } 
    } else {
      SctPrint (L"%5s %-20s Not Test\n", L" ", L"ShutDown");
      SctZeroMem (Buffer, 100);
      BufferSize = 100;
      SctASPrint(Buffer, BufferSize, "%5s %-20s Not Test\n", L" ", L"ShutDown");
      BufferSize = SctAsciiStrSize (Buffer);
      SctWriteFile (FileHandle, &BufferSize, Buffer);
    }
  } 

  Status = SctFlushFile (FileHandle);
  Status = SctCloseFile (FileHandle);

  Status = tRT->SetVariable (
                 gTestRecordName,             // VariableName
                 &VariableTestGuid,           // VendorGuid
                 EFI_VARIABLE_RUNTIME_ACCESS|EFI_VARIABLE_NON_VOLATILE|EFI_VARIABLE_BOOTSERVICE_ACCESS,                        // Attributes
                 0,                           // DataSize
                 &TestRecord                  // Data
                 );

  return EFI_SUCCESS;
}

