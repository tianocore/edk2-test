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
                                                                
  Copyright 2006 - 2013 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:
  
  NetLib.c

Abstract:

--*/

#include <Library/NetLib.h>

#if (EFI_SPECIFICATION_VERSION >= 0x00020028)
#include <Protocol/DriverConfiguration.h>
#endif

EFI_MAC_ADDRESS BroadcastMacAddr = {
  {
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0xff,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
  }
};

EFI_STATUS
EFIAPI
EfiLibDefaultUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS                        Status;
  EFI_HANDLE                        *DeviceHandleBuffer;
  UINTN                             DeviceHandleCount;
  UINTN                             Index;
  EFI_DRIVER_BINDING_PROTOCOL       *DriverBinding;
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  IN EFI_COMPONENT_NAME2_PROTOCOL       *ComponentName2; OPTIONAL
  EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfiguration2;
  EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics2;
#else
  IN EFI_COMPONENT_NAME_PROTOCOL        *ComponentName; OPTIONAL
  EFI_DRIVER_CONFIGURATION_PROTOCOL     *DriverConfiguration;
  EFI_DRIVER_DIAGNOSTICS_PROTOCOL       *DriverDiagnostics;
#endif


  //
  // Get the list of all the handles in the handle database.
  // If there is an error getting the list, then the unload operation fails.
  //
  Status = tBS->LocateHandleBuffer (AllHandles, NULL, NULL, &DeviceHandleCount, &DeviceHandleBuffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Disconnect the driver specified by ImageHandle from all the devices in the
  // handle database.
  //
  for (Index = 0; Index < DeviceHandleCount; Index++) {
    Status = tBS->DisconnectController (DeviceHandleBuffer[Index], ImageHandle, NULL);
  }
  //
  // Uninstall all the protocols that were installed in the driver entry point
  //
  for (Index = 0; Index < DeviceHandleCount; Index++) {
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiDriverBindingProtocolGuid, (VOID **) &DriverBinding);
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (DriverBinding->ImageHandle != ImageHandle) {
      continue;
    }
    tBS->UninstallProtocolInterface (ImageHandle, &gEfiDriverBindingProtocolGuid, DriverBinding);

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiComponentName2ProtocolGuid, (VOID **) &ComponentName2);
#else
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiComponentNameProtocolGuid, &ComponentName);
#endif
    if (!EFI_ERROR (Status)) {
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiComponentName2ProtocolGuid, ComponentName2);
#else
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiComponentNameProtocolGuid, ComponentName);
#endif
    }
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiDriverConfiguration2ProtocolGuid, (VOID **) &DriverConfiguration2);
#else                                                           
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiDriverConfigurationProtocolGuid, &DriverConfiguration);
#endif	
    if (!EFI_ERROR (Status)) {
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiDriverConfiguration2ProtocolGuid, DriverConfiguration2);
#else
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiDriverConfigurationProtocolGuid, DriverConfiguration);
#endif
    }
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiDriverDiagnostics2ProtocolGuid, (VOID **) &DriverDiagnostics2);
#else                                                         
    Status = tBS->HandleProtocol (DeviceHandleBuffer[Index], &gEfiDriverDiagnosticsProtocolGuid, &DriverDiagnostics);
#endif
    if (!EFI_ERROR (Status)) {
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiDriverDiagnostics2ProtocolGuid, DriverDiagnostics2);
#else
      tBS->UninstallProtocolInterface (ImageHandle, &gEfiDriverDiagnosticsProtocolGuid, DriverDiagnostics);
#endif
    }
  }
  //
  // Free the buffer containing the list of handles from the handle database
  //
  if (DeviceHandleBuffer != NULL) {
    tBS->FreePool (DeviceHandleBuffer);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EfiLibInstallAllDriverProtocolsWithUnload (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   * SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL        * DriverBinding,
  IN EFI_HANDLE                         DriverBindingHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  IN EFI_COMPONENT_NAME2_PROTOCOL       * ComponentName2, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION2_PROTOCOL * DriverConfiguration2, OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL   * DriverDiagnostics2 OPTIONAL
#else
  IN EFI_COMPONENT_NAME_PROTOCOL        * ComponentName, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL  * DriverConfiguration, OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL    * DriverDiagnostics OPTIONAL
#endif
  )
/*++

Routine Description:

  Intialize a driver by installing the Driver Binding Protocol onto the 
  driver's DriverBindingHandle.  This is typically the same as the driver's
  ImageHandle, but it can be different if the driver produces multiple
  DriverBinding Protocols.  This function also initializes the EFI Driver
  Library that initializes the global variables gST, tBS, gRT.

Arguments:

  ImageHandle         - The image handle of the driver

  SystemTable         - The EFI System Table that was passed to the driver's entry point

  DriverBinding       - A Driver Binding Protocol instance that this driver is producing

  DriverBindingHandle - The handle that DriverBinding is to be installe onto.  If this
                        parameter is NULL, then a new handle is created.

  ComponentName       - A Component Name Protocol instance that this driver is producing

  DriverConfiguration - A Driver Configuration Protocol instance that this driver is producing
  
  DriverDiagnostics   - A Driver Diagnostics Protocol instance that this driver is producing

Returns: 

  EFI_SUCCESS if all the protocols were installed onto DriverBindingHandle

  Otherwise, then return status from tBS->InstallProtocolInterface()

--*/
{
  return EfiLibInstallAllDriverProtocolsWithCustomizedUnload (
          ImageHandle,
          SystemTable,
          DriverBinding,
          DriverBindingHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
          ComponentName2,
          DriverConfiguration2,
          DriverDiagnostics2,
#else
          ComponentName,
          DriverConfiguration,
          DriverDiagnostics,
#endif         
          EfiLibDefaultUnload
          );
}

EFI_STATUS
EfiLibInstallAllDriverProtocolsWithCustomizedUnload (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL        *DriverBinding,
  IN EFI_HANDLE                         DriverBindingHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  IN EFI_COMPONENT_NAME2_PROTOCOL       *ComponentName2, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION2_PROTOCOL *DriverConfiguration2,  OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL   *DriverDiagnostics2,    OPTIONAL
#else
  IN EFI_COMPONENT_NAME_PROTOCOL        *ComponentName, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL  *DriverConfiguration,  OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL    *DriverDiagnostics,    OPTIONAL
#endif
  IN EFI_LIB_DRIVER_UNLOAD              CustomizedUnload
  )
{
  EFI_STATUS                Status;
  EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;

#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  Status = SctInstallAllDriverProtocols2 (
#else
  Status = SctInstallAllDriverProtocols (
#endif
            ImageHandle,
            SystemTable,
            DriverBinding,
            DriverBindingHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
            ComponentName2,
            DriverConfiguration2,
            DriverDiagnostics2	
#else
            ComponentName,
            DriverConfiguration,
            DriverDiagnostics	
#endif	   

			);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Retrieve the Loaded Image Protocol from Image Handle
  //
  Status = tBS->OpenProtocol (
                  ImageHandle,
                  &gEfiLoadedImageProtocolGuid,
                  (VOID **) &LoadedImage,
                  ImageHandle,
                  ImageHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Fill in the Unload() service of the Loaded Image Protocol
  //
  LoadedImage->Unload = (CustomizedUnload == NULL) ? EfiLibDefaultUnload : CustomizedUnload;

  return EFI_SUCCESS;

}

UINT16
NetChecksum (
  IN UINT8  *Buffer,
  IN UINTN  Length
  )
/*++

  Routine Description:
    Calculate the internet checksum (see RFC 1071)

  Arguments:
    Packet             - Buffer which contains the data to be checksummed
    Length             - Length to be checksummed

  Returns:
    Checksum           - Returns the 16 bit ones complement of 
                         ones complement sum of 16 bit words

--*/
{
  UINT32  Sum;
  UINT8   Odd;
  UINT16  *Packet;

  Packet  = (UINT16 *) Buffer;

  Sum     = 0;
  Odd     = (UINT8) (Length & 1);
  Length >>= 1;
  while (Length--) {
    Sum += *Packet++;
  }

  if (Odd) {
    Sum += *(UINT8 *) Packet;
  }

  Sum = (Sum & 0xffff) + (Sum >> 16);
  //
  // in case above carried
  //
  Sum += Sum >> 16;

  return (UINT16) (~ (UINT16) Sum);
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
INTN
NetAsciiStrCaseCmp (
  IN  CHAR8   *Left,
  IN  CHAR8   *Right
  )
/*++

  Routine Description:
    Compare two ascii strings. Case is ignored.
    
  Arguments:
    Left    - The first ascii string.
    Right   - The second ascii string.
    
  Returns:
    0       - The two ascii strings are equal.
    -1      - Left is less than Right (Left < Right).
    1       - Left is greater than Right (Left > Right).
--*/
{
  INTN  Cmp;

  if (Left == NULL) {
    return (INTN) ((NULL == Right) ? 0 : -1);
  }

  if (Right == NULL) {
    return 1;
  }
  //
  //  Now both Left and Right are not NULL
  //
  do {
    if (*Left >= 'A' && *Left <= 'Z') {
      Cmp = 'a' +*Left - 'A';
    } else {
      Cmp = *Left;
    }

    if (*Right >= 'A' && *Right <= 'Z') {
      Cmp -= 'a' +*Right - 'A';
    } else {
      Cmp -= *Right;
    }

    Left++;
    Right++;
  } while ((Cmp == 0) && (*Left != '\0') && (*Right != '\0'));

  if ((Cmp == 0) && (*Left != *Right)) {
    //
    //  The length of strings are not equal.
    //  But only the length of the short one is compared.
    //  At this point either *Left is '\0' or *Right is '\0'.
    //
    if (*Left != '\0') {
      return 1;
    } else {
      return -1;
    }
  }

  return Cmp;
}

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

//
//
//
UINT64
NetAsciiStrToU64 (
  IN  CHAR8   *Str
  )
{
  UINT64  Num;

  Num = 0;

  if (Str != NULL) {
    for (; *Str >= '0' && *Str <= '9'; ++Str) {
      Num = SctMultU64x32 (Num, 10) +*Str - '0';
    }
  }

  return Num;
}

UINT64
NetSwap64 (
  IN  UINT64    Num
  )
{
  union {
    UINT64  Num;
    UINT8   Raw[8];
  } u;

  UINT8 Tmp;

  u.Num     = Num;

  Tmp       = u.Raw[0];
  u.Raw[0]  = u.Raw[7];
  u.Raw[7]  = Tmp;

  Tmp       = u.Raw[1];
  u.Raw[1]  = u.Raw[6];
  u.Raw[6]  = Tmp;

  Tmp       = u.Raw[2];
  u.Raw[2]  = u.Raw[5];
  u.Raw[5]  = Tmp;

  Tmp       = u.Raw[3];
  u.Raw[3]  = u.Raw[4];
  u.Raw[4]  = Tmp;

  return u.Num;
}

UINT64
NetTimeToSeconds (
  IN  EFI_TIME Time
  )
{
  UINT32  Years;
  UINT32  Days;
  UINT32  Index;
  UINT32  LeapYearCnt;
  UINT64  Seconds;

  //
  // gRT->GetTime(&Time,NULL);
  //
  Years       = Time.Year - 1900;
  LeapYearCnt = Years >> 2;
  if (LeapYearCnt > 0) {
    LeapYearCnt -= Years / 100;
    if (Years >= 100) {
      LeapYearCnt += (Years + 300) / 400;
    }
  }

  Days = 0;
  for (Index = 1; Index < Time.Month; Index++) {
    switch (Index) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
      Days += 31;
      break;

    case 4:
    case 6:
    case 9:
    case 11:
      Days += 30;
      break;

    case 2:
      if ((Time.Year % 400 == 0) || (Time.Year % 4 == 0 && Time.Year % 100 != 0)) {
        Days += 28;
      } else {
        Days += 29;
      }
      break;

    default:
      ASSERT (0);
      break;
    }
  }

  Days += (Time.Day - 1);

  Seconds = Years * 365 * 24 * 3600 + LeapYearCnt * 24 * 3600;
  Seconds += Days * 24 * 3600;
  Seconds += Time.Hour * 3600;
  Seconds += Time.Minute * 60;
  Seconds += Time.Second;

  return Seconds;
}

UINT16
NetFragmentChecksum (
  IN UINTN             FragmentCount,
  IN NET_FRAGMENT_DATA *FragmentTable
  )
/*++

  Routine Description:
    Calculate the internet checksum (see RFC 1071)

  Arguments:
    FragmentCount   - The counts of fragment which contains the data to be checksummed
    FragmentTable    - The fragment descriptor table which describe the data to be checksummed
    

  Returns:
    Checksum           - Returns the 16 bit ones complement of 
                         ones complement sum of 16 bit words

--*/
{
  UINT32  Sum;
  UINT8   Odd;
  UINT16  *Packet;
  UINT8   *TempPacket;
  UINTN   Index;
  UINT8   LastData;
  UINT16  TempData;
  UINTN   Length;

  Packet = NULL;
  ASSERT (FragmentCount != 0);

  Sum       = 0;
  Odd       = 0;
  LastData  = 0;

  for (Index = 0; Index < FragmentCount; Index++) {
    Length = FragmentTable[Index].FragmentLength;
    if (Odd) {
      TempPacket  = (UINT8 *) FragmentTable[Index].FragmentBuffer;
      TempData    = (UINT16) (*TempPacket++);
      TempData <<= 8;
      TempData = TempData + (UINT16) LastData;

      Sum += TempData;
      Packet = (UINT16 *) TempPacket;
      Length -= 1;
    } else {
      Packet = (UINT16 *) FragmentTable[Index].FragmentBuffer;
    }

    Odd = (UINT8) (Length & 1);
    if (Length) {
      Length >>= 1;
      while (Length--) {
        Sum += *Packet++;
      }
    }

    if (Odd) {
      LastData = *(UINT8 *) Packet;
    }
  }

  if (Odd) {
    Sum += *(UINT8 *) Packet;
  }

  Sum = (Sum & 0xffff) + (Sum >> 16);
  //
  // in case above carried
  //
  Sum += Sum >> 16;

  return (UINT16) (~ (UINT16) Sum);
}

OBJECT_LIST_ENTRY *
EFIAPI
ObjectListGetFirstEntry (
  IN  OBJECT_LIST_CLASS   *This
  )
{
  ASSERT (This != NULL);

  if (LIST_IS_EMPTY (&This->Head)) {
    return NULL;
  } else {
    return LIST_ENTRY (This->Head.ForwardLink, OBJECT_LIST_ENTRY, Entry);
  }
}

EFI_STATUS
EFIAPI
ObjectListInsertHead (
  IN  OBJECT_LIST_CLASS   *This,
  IN  VOID                *Object
  )
{
  OBJECT_LIST_ENTRY *ObjListEntry;

  ObjListEntry = NULL;

  ASSERT (This != NULL);

  if (Object == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ObjListEntry = This->GetOneEntryFromFreeEntryPool (This);

  if (ObjListEntry == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else {
    ObjListEntry->Object = Object;

    LIST_INSERT_HEAD (&This->Head, &ObjListEntry->Entry);

    return EFI_SUCCESS;
  }
}

EFI_STATUS
EFIAPI
ObjectListInsertTail (
  IN  OBJECT_LIST_CLASS   *This,
  IN  VOID                *Object
  )
{
  OBJECT_LIST_ENTRY *ObjListEntry;

  ObjListEntry = NULL;

  ASSERT (This != NULL);

  if (Object == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ObjListEntry = This->GetOneEntryFromFreeEntryPool (This);

  if (ObjListEntry == NULL) {
    return EFI_OUT_OF_RESOURCES;
  } else {
    ObjListEntry->Object = Object;

    LIST_INSERT_TAIL (&This->Head, &ObjListEntry->Entry);

    return EFI_SUCCESS;
  }

}

BOOLEAN
EFIAPI
ObjectListIsEmpty (
  IN  OBJECT_LIST_CLASS   *This
  )
{
  ASSERT (This != NULL);

  return LIST_IS_EMPTY (&This->Head);
}

VOID
EFIAPI
ObjectListRemoveEntry (
  IN  OBJECT_LIST_CLASS   *This,
  IN  OBJECT_LIST_ENTRY   *ObjListEntry
  )
{
  ASSERT (This != NULL);
  ASSERT (ObjListEntry != NULL);

  LIST_REMOVE_ENTRY (&ObjListEntry->Entry);

  ObjListEntry->Object = NULL;

  This->RecycleEntry (This, ObjListEntry);

  return ;

}

VOID *
EFIAPI
ObjectListGetNext (
  IN      OBJECT_LIST_CLASS     *This,
  IN OUT  OBJECT_LIST_ENTRY     **Entry
  )
/*++

  Routine Description:
    Get the next entry in the object list.

  Arguments:
    This                - Object list pointer.
    Entry               - Current entry

  Returns:
    When the *Entry == NULL, return NULL
    and store the first entry in *Entry
    When the *Entry != NULL, return the object in current entry
    and store the next entry in *Entry
    When reaching the end of this list, the returned *Entry is NULL

--*/
{
  OBJECT_LIST_ENTRY *CurrentEntry;

  CurrentEntry = *Entry;

  ASSERT (This != NULL);
  ASSERT (Entry != NULL);

  if (*Entry == NULL) {
    *Entry = This->GetFirstEntry (This);

    return NULL;
  }

  if (CurrentEntry->Entry.ForwardLink == &This->Head) {
    //
    //  Reach list end
    //
    *Entry = NULL;
  } else {
    *Entry = LIST_ENTRY (CurrentEntry->Entry.ForwardLink, OBJECT_LIST_ENTRY, Entry);
  }

  return CurrentEntry->Object;
}

UINTN
EFIAPI
ObjectListGetCount (
  IN      OBJECT_LIST_CLASS     *This
  )
{
  UINTN             Count;
  OBJECT_LIST_ENTRY *CurrentEntry;

  Count         = 0;
  CurrentEntry  = NULL;

  ASSERT (This != NULL);

  CurrentEntry = This->GetFirstEntry (This);

  while (CurrentEntry != NULL) {
    This->GetNext (This, &CurrentEntry);
    Count++;
  }

  return Count;
}

VOID *
EFIAPI
ObjectListRemoveHead (
  IN      OBJECT_LIST_CLASS     *This
  )
{
  OBJECT_LIST_ENTRY *ObjListEntry;
  VOID              *Object;

  ObjListEntry  = NULL;
  Object        = NULL;

  ASSERT (This != NULL);

  if (LIST_IS_EMPTY (&This->Head)) {
    return NULL;
  }

  ObjListEntry  = LIST_ENTRY (This->Head.ForwardLink, OBJECT_LIST_ENTRY, Entry);

  Object        = ObjListEntry->Object;
  ASSERT (Object != NULL);

  This->RemoveEntry (This, ObjListEntry);

  return Object;

}

EFI_STATUS
EFIAPI
ObjectListPreAllocateFreeEntry (
  IN OBJECT_LIST_CLASS    *This,
  IN UINTN                NewEntryCount
  )
{
  UINTN             i;
  OBJECT_LIST_ENTRY *ObjListEntry;

  ObjListEntry = NULL;

  ASSERT (This != NULL);
  ASSERT (LIST_IS_EMPTY (&This->ObjListPool));

  for (i = 0; i < NewEntryCount; i++) {
    ObjListEntry = NetAllocatePool (sizeof (OBJECT_LIST_ENTRY));
    if (ObjListEntry == NULL) {
      This->ReleaseFreeEntryPool (This);
      return EFI_OUT_OF_RESOURCES;
    }
    //
    //  Initialize the allocated entry
    //
    ObjListEntry->Object = NULL;

    LIST_INSERT_TAIL (&This->ObjListPool, &ObjListEntry->Entry);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
ObjectListReleaseFreeEntryPool (
  IN OBJECT_LIST_CLASS    *This
  )
{
  OBJECT_LIST_ENTRY *ObjListEntry;
  NET_LIST_ENTRY    *Link;

  ObjListEntry  = NULL;
  Link          = NULL;

  ASSERT (This != NULL);

  while (!LIST_IS_EMPTY (&This->ObjListPool)) {
    Link = This->ObjListPool.ForwardLink;
    ASSERT (Link != NULL);

    ObjListEntry = LIST_ENTRY (Link, OBJECT_LIST_ENTRY, Entry);

    LIST_REMOVE_ENTRY (Link);

    NetFreePool (ObjListEntry);
  }

  return EFI_SUCCESS;

}

OBJECT_LIST_ENTRY *
EFIAPI
ObjectListGetOneEntryFromFreeEntryPool (
  IN  OBJECT_LIST_CLASS     *This
  )
{
  EFI_STATUS        Status;
  NET_LIST_ENTRY    *Link;
  OBJECT_LIST_ENTRY *ObjListEntry;

  Link          = NULL;
  ObjListEntry  = NULL;

  ASSERT (This != NULL);

  //
  //  Check if the pool is empty
  //
  if (LIST_IS_EMPTY (&This->ObjListPool)) {
    //
    //  No free entry available in the pool
    //  We need to get some
    //
    Status = This->PreAllocateFreeEntry (This, This->PoolIncrementCount);

    if (EFI_ERROR (Status)) {
      return NULL;
    }
  }
  //
  //  Get a OBJECT_LIST_ENTRY from the free buffe pool
  //
  Link          = This->ObjListPool.ForwardLink;
  ObjListEntry  = LIST_ENTRY (Link, OBJECT_LIST_ENTRY, Entry);

  LIST_REMOVE_ENTRY (&ObjListEntry->Entry);

  return ObjListEntry;
}

VOID
EFIAPI
ObjectListRecycleEntry (
  IN  OBJECT_LIST_CLASS     *This,
  IN  OBJECT_LIST_ENTRY     *ObjListEntry
  )
{
  ASSERT (This != NULL);
  ASSERT (ObjListEntry != NULL);

  LIST_INSERT_TAIL (&This->ObjListPool, &ObjListEntry->Entry);
}

OBJECT_LIST_CLASS *
EFIAPI
NewObjectList (
  IN      UINTN             IncrementCount,
  IN OUT  OBJECT_LIST_CLASS *ObjList
  )
{
  if (ObjList == NULL) {
    //
    //  Allocate the object for user
    //
    if ((ObjList = NetAllocatePool (sizeof (OBJECT_LIST_CLASS))) == NULL) {
      return NULL;
    }

    ObjList->UserAllocated = FALSE;
  } else {
    //
    //  User supplied the object space
    //
    ObjList->UserAllocated = TRUE;
  }
  //
  //  Initialize the object list
  //
  if (IncrementCount == 0) {
    ObjList->PoolIncrementCount = DEFAULT_OBJECT_LIST_ALLOCATE_NUMBER;
  } else {
    ObjList->PoolIncrementCount = IncrementCount;
  }

  ObjList->GetFirstEntry                = ObjectListGetFirstEntry;
  ObjList->InsertHead                   = ObjectListInsertHead;
  ObjList->InsertTail                   = ObjectListInsertTail;
  ObjList->IsEmpty                      = ObjectListIsEmpty;
  ObjList->RemoveEntry                  = ObjectListRemoveEntry;
  ObjList->GetNext                      = ObjectListGetNext;
  ObjList->RemoveHead                   = ObjectListRemoveHead;
  ObjList->GetCount                     = ObjectListGetCount;
  ObjList->PreAllocateFreeEntry         = ObjectListPreAllocateFreeEntry;
  ObjList->ReleaseFreeEntryPool         = ObjectListReleaseFreeEntryPool;
  ObjList->GetOneEntryFromFreeEntryPool = ObjectListGetOneEntryFromFreeEntryPool;
  ObjList->RecycleEntry                 = ObjectListRecycleEntry;

  LIST_INIT (&ObjList->Head);
  LIST_INIT (&ObjList->ObjListPool);

  return ObjList;
}
//
// EFI_STATUS
//
VOID
EFIAPI
DeleteObjectList (
  IN OBJECT_LIST_CLASS  *ObjList
  )
{
  OBJECT_LIST_ENTRY *ObjListEntry;

  ObjListEntry = NULL;

  ASSERT (ObjList != NULL);

  //
  //  Remove all the entries in this list
  //
  while (!LIST_IS_EMPTY (&ObjList->Head)) {
    ObjListEntry = LIST_ENTRY (ObjList->Head.ForwardLink, OBJECT_LIST_ENTRY, Entry);

    LIST_REMOVE_ENTRY (&ObjListEntry->Entry);

    ObjList->RecycleEntry (ObjList, ObjListEntry);
  }
  //
  //  Free the ObjListPool
  //
  ObjList->ReleaseFreeEntryPool (ObjList);

  if (!ObjList->UserAllocated) {
    NetFreePool (ObjList);
  }

  return ;
}
