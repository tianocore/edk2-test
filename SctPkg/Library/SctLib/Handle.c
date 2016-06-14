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

  Copyright (c) 2013-2014, ARM Ltd. All rights reserved.

--*/

#include "SctLibInternal.h"

#include EFI_PROTOCOL_DEFINITION (ComponentName)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
  #include <Guid/HobList.h>
#else
  #include EFI_GUID_DEFINITION (Hob)
#endif

/*++

Routine Description:

  Find the first instance of this Protocol in the system and return it's interface

Arguments:

  ProtocolGuid    - Provides the protocol to search for
  Interface       - On return, a pointer to the first interface that matches ProtocolGuid

Returns:

  EFI_SUCCESS     - A protocol instance matching ProtocolGuid was found

  EFI_NOT_FOUND   - No protocol instances were found that match ProtocolGuid

--*/
EFI_STATUS
SctLocateProtocol (
  IN  EFI_GUID    *ProtocolGuid,
  OUT VOID        **Interface
  )
{
  EFI_STATUS      Status;
  UINTN           NumberHandles, Index;
  EFI_HANDLE      *Handles;


  *Interface = NULL;
  Status = SctLocateHandle (ByProtocol, ProtocolGuid, NULL, &NumberHandles, &Handles);
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "SctLocateProtocol: Handle not found\n"));
    return Status;
  }

  for (Index=0; Index < NumberHandles; Index++) {
    Status = tBS->HandleProtocol(
                   Handles[Index],
                   ProtocolGuid,
                   Interface
                   );

    if (!EFI_ERROR(Status)) {
      break;
    }
  }

  if (Handles) {
    SctFreePool (Handles);
  }

  return Status;
}

/*++

Routine Description:

  Function returns an array of handles that support the requested protocol
  in a buffer allocated from pool.

Arguments:

  SearchType           - Specifies which handle(s) are to be returned.
  Protocol             - Provides the protocol to search by.
                         This parameter is only valid for SearchType ByProtocol.
  SearchKey            - Supplies the search key depending on the SearchType.
  NoHandles            - The number of handles returned in Buffer.
  Buffer               - A pointer to the buffer to return the requested array of
                         handles that support Protocol.

Returns:

  EFI_SUCCESS           - The result array of handles was returned.
  EFI_NOT_FOUND         - No handles match the search.
  EFI_OUT_OF_RESOURCES - There is not enough pool memory to store the matching results.

--*/
EFI_STATUS
SctLocateHandle (
  IN EFI_LOCATE_SEARCH_TYPE       SearchType,
  IN EFI_GUID                     *Protocol OPTIONAL,
  IN VOID                         *SearchKey OPTIONAL,
  IN OUT UINTN                    *NoHandles,
  OUT EFI_HANDLE                  **Buffer
  )
{
  EFI_STATUS          Status;
  UINTN               BufferSize;

  //
  // Initialize for SctGrowBuffer loop
  //

  Status = EFI_SUCCESS;
  *Buffer = NULL;
  BufferSize = 50 * sizeof(EFI_HANDLE);

  //
  // Call the real function
  //

  while (SctGrowBuffer (&Status, (VOID **) Buffer, BufferSize)) {
    Status = tBS->LocateHandle (
                   SearchType,
                   Protocol,
                   SearchKey,
                   &BufferSize,
                   *Buffer
                   );
  }

  *NoHandles = BufferSize / sizeof (EFI_HANDLE);
  if (EFI_ERROR(Status)) {
    *NoHandles = 0;
  }

  return Status;
}

/**
 *  Get the Pei Protocol Interface from the Hob list.
 *  @param ProtocolGuid Pei Protocol Guid.
 *  @param Interface Pei Protocol interface to be returned.
 *  @return EFI_SUCCESS the protocol interface is got successfully.
 *  @return EFI_NOT_FOUND the protocol Guid is not found
 */
EFI_STATUS
SctGetPeiProtocol (
  IN EFI_GUID      *ProtocolGuid,
  IN OUT VOID      **Interface
  )
{
  EFI_STATUS  Status;
  VOID        *HobList;
  VOID        *Buffer;

  Status = SctGetSystemConfigurationTable (&gEfiHobListGuid, &HobList);

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = SctGetNextGuidHob (&HobList, ProtocolGuid, &Buffer, NULL);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  *Interface = (VOID *)(*(UINTN *)(Buffer));

  return Status;
}

/*++

Routine Description:
  Function returns a system configuration table that is stored in the
  EFI System Table based on the provided GUID.

Arguments:
  TableGuid        - A pointer to the table's GUID type.

  Table            - On exit, a pointer to a system configuration table.

Returns:

  EFI_SUCCESS      - A configuration table matching TableGuid was found

  EFI_NOT_FOUND    - A configuration table matching TableGuid was not found

--*/
EFI_STATUS
SctGetSystemConfigurationTable(
  IN EFI_GUID *TableGuid,
  IN OUT VOID **Table
  )
{
  UINTN Index;

  for (Index=0;Index<tST->NumberOfTableEntries;Index++) {
    if (SctCompareGuid (TableGuid,&(tST->ConfigurationTable[Index].VendorGuid))==0) {
      *Table = tST->ConfigurationTable[Index].VendorTable;
      return EFI_SUCCESS;
    }
  }
  return EFI_NOT_FOUND;
}

EFI_STATUS
SctScanHandleDatabase (
  EFI_HANDLE  DriverBindingHandle,       OPTIONAL
  UINT32      *DriverBindingHandleIndex, OPTIONAL
  EFI_HANDLE  ControllerHandle,          OPTIONAL
  UINT32      *ControllerHandleIndex,    OPTIONAL
  UINTN       *HandleCount,
  EFI_HANDLE  **HandleBuffer,
  UINT32      **HandleType
  )
{
  EFI_STATUS                           Status;
  UINTN                                HandleIndex;
  EFI_GUID                             **ProtocolGuidArray;
  UINTN                                ArrayCount;
  UINTN                                ProtocolIndex;
  EFI_OPEN_PROTOCOL_INFORMATION_ENTRY  *OpenInfo;
  UINTN                                OpenInfoCount;
  UINTN                                OpenInfoIndex;
  UINTN                                ChildIndex;
  BOOLEAN                              DriverBindingHandleIndexValid;

  DriverBindingHandleIndexValid = FALSE;
  if (DriverBindingHandleIndex != NULL) {
    *DriverBindingHandleIndex = 0xffffffff;
  }
  if (ControllerHandleIndex != NULL) {
    *ControllerHandleIndex    = 0xffffffff;
  }
  *HandleCount              = 0;
  *HandleBuffer             = NULL;
  *HandleType               = NULL;

  //
  // Retrieve the list of all handles from the handle database
  //
  Status = tBS->LocateHandleBuffer (
                 AllHandles,
                 NULL,
                 NULL,
                 HandleCount,
                 HandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 *HandleCount * sizeof(UINT32),
                 (VOID **)HandleType
                 );
  if (EFI_ERROR (Status)) {
    goto Error;
  }

  for (HandleIndex = 0; HandleIndex < *HandleCount; HandleIndex++) {

    //
    // Assume that the handle type is unknown
    //
    (*HandleType)[HandleIndex] = SCT_HANDLE_TYPE_UNKNOWN;

    if (DriverBindingHandle != NULL && DriverBindingHandleIndex != NULL && (*HandleBuffer)[HandleIndex] == DriverBindingHandle) {
      *DriverBindingHandleIndex = (UINT32)HandleIndex;
      DriverBindingHandleIndexValid = TRUE;
    }

    if (ControllerHandle != NULL && ControllerHandleIndex != NULL && (*HandleBuffer)[HandleIndex] == ControllerHandle) {
      *ControllerHandleIndex = (UINT32)HandleIndex;
    }

  }

  for (HandleIndex = 0; HandleIndex < *HandleCount; HandleIndex++) {

    //
    // Retrieve the list of all the protocols on each handle
    //
    Status = tBS->ProtocolsPerHandle (
                   (*HandleBuffer)[HandleIndex],
                   &ProtocolGuidArray,
                   &ArrayCount
                   );
    if (!EFI_ERROR (Status)) {

      for (ProtocolIndex = 0; ProtocolIndex < ArrayCount; ProtocolIndex++) {

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiLoadedImageProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_IMAGE_HANDLE;
        }

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverBindingProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_DRIVER_BINDING_HANDLE;
        }

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverConfigurationProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_DRIVER_CONFIGURATION_HANDLE;
        }

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDriverDiagnosticsProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_DRIVER_DIAGNOSTICS_HANDLE;
        }

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiComponentNameProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_COMPONENT_NAME_HANDLE;
        }

        if (SctCompareGuid (ProtocolGuidArray[ProtocolIndex], &gEfiDevicePathProtocolGuid) == 0) {
          (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_DEVICE_HANDLE;
        }

        //
        // Retrieve the list of agents that have opened each protocol
        //
        Status = tBS->OpenProtocolInformation (
                       (*HandleBuffer)[HandleIndex],
                       ProtocolGuidArray[ProtocolIndex],
                       &OpenInfo,
                       &OpenInfoCount
                       );
        if (!EFI_ERROR (Status)) {

          for (OpenInfoIndex=0; OpenInfoIndex < OpenInfoCount; OpenInfoIndex++) {
            if (DriverBindingHandle != NULL && OpenInfo[OpenInfoIndex].AgentHandle == DriverBindingHandle) {
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                //
                // Mark the device handle as being managed by the driver specified by DriverBindingHandle
                //
                (*HandleType)[HandleIndex] |= (SCT_HANDLE_TYPE_DEVICE_HANDLE | SCT_HANDLE_TYPE_CONTROLLER_HANDLE);
                //
                // Mark the DriverBindingHandle as being a driver that is managing at least one controller
                //
                if (DriverBindingHandleIndexValid) {
                  (*HandleType)[*DriverBindingHandleIndex] |= SCT_HANDLE_TYPE_DEVICE_DRIVER;
                }
              }
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                //
                // Mark the DriverBindingHandle as being a driver that is managing at least one child controller
                //
                if (DriverBindingHandleIndexValid) {
                  (*HandleType)[*DriverBindingHandleIndex] |= SCT_HANDLE_TYPE_BUS_DRIVER;
                }
              }

              if (ControllerHandle != NULL && (*HandleBuffer)[HandleIndex] == ControllerHandle) {
                if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                  for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                    if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].ControllerHandle) {
                      (*HandleType)[ChildIndex] |= (SCT_HANDLE_TYPE_DEVICE_HANDLE | SCT_HANDLE_TYPE_CHILD_HANDLE);
                    }
                  }
                }
              }
            }

            if (DriverBindingHandle == NULL && OpenInfo[OpenInfoIndex].ControllerHandle == ControllerHandle) {
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_DRIVER) == EFI_OPEN_PROTOCOL_BY_DRIVER) {
                for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                  if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].AgentHandle) {
                    (*HandleType)[ChildIndex] |= SCT_HANDLE_TYPE_DEVICE_DRIVER;
                  }
                }
              }
              if ((OpenInfo[OpenInfoIndex].Attributes & EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) == EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER) {
                (*HandleType)[HandleIndex] |= SCT_HANDLE_TYPE_PARENT_HANDLE;
                for (ChildIndex = 0; ChildIndex < *HandleCount; ChildIndex++) {
                  if ((*HandleBuffer)[ChildIndex] == OpenInfo[OpenInfoIndex].AgentHandle) {
                    (*HandleType)[ChildIndex] |= SCT_HANDLE_TYPE_BUS_DRIVER;
                  }
                }
              }
            }
          }
          tBS->FreePool (OpenInfo);
        }
      }
      tBS->FreePool (ProtocolGuidArray);
    }
  }

  return EFI_SUCCESS;

Error:
  if (*HandleType != NULL) {
    tBS->FreePool (*HandleType);
  }
  if (*HandleBuffer != NULL) {
    tBS->FreePool (*HandleBuffer);
  }
  *HandleCount = 0;
  *HandleBuffer = NULL;
  *HandleType   = NULL;

  return Status;
}

STATIC
EFI_STATUS
LibGetHandleDatabaseSubset (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINT32      Mask,
  UINTN       *MatchingHandleCount,
  EFI_HANDLE  **MatchingHandleBuffer
  )

{
  EFI_STATUS  Status;
  UINTN       HandleCount;
  EFI_HANDLE  *HandleBuffer;
  UINT32      *HandleType;
  UINTN       HandleIndex;

  *MatchingHandleCount  = 0;
  if (MatchingHandleBuffer != NULL) {
    *MatchingHandleBuffer = NULL;
  }

  HandleBuffer = NULL;
  HandleType   = NULL;

  Status = SctScanHandleDatabase (
             DriverBindingHandle,
             NULL,
             ControllerHandle,
             NULL,
             &HandleCount,
             &HandleBuffer,
             &HandleType
             );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Count the number of handles that match the attributes in Mask
  //
  for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
    if ((HandleType[HandleIndex] & Mask) == Mask) {
      (*MatchingHandleCount)++;
    }
  }

  //
  // If no handles match the attributes in Mask then return EFI_NOT_FOUND
  //
  if (*MatchingHandleCount == 0) {
    Status = EFI_NOT_FOUND;
    goto Done;
  }

  if (MatchingHandleBuffer == NULL) {
    Status = EFI_SUCCESS;
    goto Done;
  }

  //
  // Allocate a handle buffer for the number of handles that matched the attributes in Mask
  //
  Status = tBS->AllocatePool (
                 EfiBootServicesData,
                 *MatchingHandleCount * sizeof (EFI_HANDLE),
                 (VOID **)MatchingHandleBuffer
                 );
  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Fill the allocated buffer with the handles that matched the attributes in Mask
  //
  *MatchingHandleCount = 0;
  for (HandleIndex = 0; HandleIndex < HandleCount; HandleIndex++) {
    if ((HandleType[HandleIndex] & Mask) == Mask) {
      (*MatchingHandleBuffer)[(*MatchingHandleCount)++] = HandleBuffer[HandleIndex];
    }
  }

  Status = EFI_SUCCESS;

Done:

  //
  // Free the buffers alocated by SctScanHandleDatabase()
  //
  if (HandleBuffer != NULL) {
    tBS->FreePool (HandleBuffer);
  }

  if (HandleType != NULL) {
    tBS->FreePool (HandleType);
  }

  return Status;
}

EFI_STATUS
SctGetManagedChildControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  EFI_HANDLE  ControllerHandle,
  UINTN       *ChildControllerHandleCount,
  EFI_HANDLE  **ChildControllerHandleBuffer
  )
{
  return LibGetHandleDatabaseSubset (
           DriverBindingHandle,
           ControllerHandle,
           SCT_HANDLE_TYPE_CHILD_HANDLE | SCT_HANDLE_TYPE_DEVICE_HANDLE,
           ChildControllerHandleCount,
           ChildControllerHandleBuffer
           );
}

EFI_STATUS
SctGetManagedControllerHandles (
  EFI_HANDLE  DriverBindingHandle,
  UINTN       *ControllerHandleCount,
  EFI_HANDLE  **ControllerHandleBuffer
  )
{
  return LibGetHandleDatabaseSubset (
           DriverBindingHandle,
           NULL,
           SCT_HANDLE_TYPE_CONTROLLER_HANDLE | SCT_HANDLE_TYPE_DEVICE_HANDLE,
           ControllerHandleCount,
           ControllerHandleBuffer
           );
}
