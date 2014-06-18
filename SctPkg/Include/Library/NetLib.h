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

  NetLib.h

Abstract:

  Header file of Network drivers.

--*/

#ifndef _EFI_NET_LIB_H
#define _EFI_NET_LIB_H

//
// Included files
//
#include "SctLib.h"

#include EFI_PROTOCOL_DEFINITION (ComponentName2)
#include EFI_PROTOCOL_DEFINITION (DriverBinding)
#include EFI_PROTOCOL_DEFINITION (DriverConfiguration2)
#include EFI_PROTOCOL_DEFINITION (DriverDiagnostics2)
#include EFI_PROTOCOL_DEFINITION (LoadedImage)

//
// For christea debug
//
//#define EFI_NETWORK_STACK_DEBUG 1

#ifdef EFI_NETWORK_STACK_DEBUG
#define EFI_SYS_LOG
#endif

#include <Library/NetDebug.h>

#define  __W(x)  L##x
#define  __W2(x) __W(x)
#define  __WFILE__  __W2(__FILE__)

//
// Debug Print
//
#ifdef EFI_SYS_LOG

extern EFI_NET_DEBUG_CONFIG_PROTOCOL  *NetDebugConfigProtocol;

#define NET_DEBUG( Level, Source, SubModule, PrintString )   if (NetDbgCheck(Level, Source, SubModule)) NetDbgOutput(Level, Source, SubModule, NULL, 0, NetDbgSPrint PrintString )

#define NET_DEBUG_FL( Level, Source, SubModule, PrintString ) if(NetDbgCheck(Level, Source, SubModule)) NetDbgOutput(Level, Source, SubModule, __FILE__, __LINE__, NetDbgSPrint PrintString )

#ifdef ASSERT
#undef ASSERT
#endif
#define ASSERT(assertion) {\
  if (!(assertion)){\
    NetDbgAssert(__WFILE__, __LINE__, L"ASSERT:"__W2(#assertion));\
  }\
}


#else
#define NET_DEBUG( Level, Source, SubModule, PrintString )
#define NET_DEBUG_FL( Level, Source, SubModule, PrintString )
#endif

//
// Redefined function/constant names
//
#ifdef EFI_DEBUG_MEMORY_LEAK
#define NetAllocateZeroPool(Size)   AllocateZeroPoolDbg( Size, __WFILE__, __LINE__ )
#define NetAllocatePool(Size)       AllocatePoolDbg( Size, __WFILE__, __LINE__ )
#define NetFreePool                 FreePoolDbg
#else
#define NetAllocateZeroPool   SctAllocateZeroPool
#define NetAllocatePool       SctAllocatePool
#define NetFreePool           tBS->FreePool
#endif

#ifdef NET_SSE2_SPEEDUP
VOID
NetCommonLibCopyMem (
  IN VOID   *Destination,
  IN VOID   *Source,
  IN UINTN  Length
  );

VOID
NetCommonLibSetMem (
  IN VOID   *Buffer,
  IN UINTN  Size,
  IN UINT8  Value
  );

#define NetCopyMem            NetCommonLibCopyMem
#define NetZeroMem(_Destination,_Length)\
                              NetCommonLibSetMem  ((_Destination), (_Length), 0)
#else
#define NetCopyMem            SctCopyMem
#define NetZeroMem(_Destination,_Length)\
                              SctZeroMem ((_Destination), (_Length))
#endif

#define NetCompareMem         SctCompareMem



#define NetAsciiStrLen        SctAsciiStrLen
#define NetAsciiStrCpy        SctAsciiStrCpy

#define NetMultU64x32         SctMultU64x32

#if (EFI_SPECIFICATION_VERSION < 0x00020028)
#define EVT_TIMER             EFI_EVENT_TIMER
#define EVT_NOTIFY_WAIT       EFI_EVENT_NOTIFY_WAIT
#define EVT_NOTIFY_SIGNAL     EFI_EVENT_NOTIFY_SIGNAL

#define NET_TPL_SYSTEM_POLL       EFI_TPL_NOTIFY
#define NET_TPL_GLOBAL_LOCK       NET_TPL_SYSTEM_POLL
#define NET_TPL_LOCK              (EFI_TPL_CALLBACK+1)
#define NET_TPL_EVENT             EFI_TPL_CALLBACK
#define NET_TPL_RECYCLE           EFI_TPL_CALLBACK
#define NET_TPL_FAST_RECYCLE      NET_TPL_SYSTEM_POLL
#define NET_TPL_SLOW_TIMER        (EFI_TPL_CALLBACK-1)
#define NET_TPL_FAST_TIMER        (EFI_TPL_CALLBACK+1)
#define NET_TPL_TIMER             EFI_TPL_CALLBACK
#else
#define NET_TPL_SYSTEM_POLL       TPL_NOTIFY
#define NET_TPL_GLOBAL_LOCK       NET_TPL_SYSTEM_POLL
#define NET_TPL_LOCK              (TPL_CALLBACK+1)
#define NET_TPL_EVENT             TPL_CALLBACK
#define NET_TPL_RECYCLE           TPL_CALLBACK
#define NET_TPL_FAST_RECYCLE      NET_TPL_SYSTEM_POLL
#define NET_TPL_SLOW_TIMER        (TPL_CALLBACK-1)
#define NET_TPL_FAST_TIMER        (TPL_CALLBACK+1)
#define NET_TPL_TIMER             TPL_CALLBACK
#endif
//
//sychronization primitives
//
#define NET_ATOMIC_INC(x)  __asm{ lock;inc x; }
#define NET_ATOMIC_DEC(x)  __asm{ lock;dec x; }

#define NET_LOCK         SCT_LOCK

//VOID  NET_LOCK_INIT(NET_LOCK *x)
//Default TPL is EFI_TPL_CALLBACK+1. Because the input processing runs at EFI_TPL_CALLBACK,
//So we can just raise current TPL to EFI_TPL_CALLBACK
#define NET_LOCK_INIT(x)             SctInitializeLock(x, NET_TPL_LOCK)


//VOID  NET_LOCK_INIT_GLOBAL_LOCK(NET_LOCK *x)
//Global lock will block any driver or application to access critical data.
//In single processor environment, the extreme case is to disable any interrupt.
//In multiple processor environment, the extreme case is to disable all interrupts on every processor.
//In EFI/Tiano environment, it only need to raise current TPL to EFI_TPL_NOTIFY or more higher.
#define NET_LOCK_INIT_GLOBAL_LOCK(x) SctInitializeLock(x,NET_TPL_GLOBAL_LOCK)

//
//EFI_STATUS NET_TRYLOCK (IN NET_LOCK  *x)
//
//Description:
//
//If locked, NET_TRYLOCK will return EFI_ACCESS_DENIED immediately. Otherwise lock is acquired.
//NET_TRYLOCK is typically called by application or event handlers to access shared data.
//When lock is acquired, event handler that access the same shared data 
//will not run. This is guaranteed by firmware. Be caution that when the lock flag is being set, 
//interrupt can occur and preempt the current runing function. Thus the lock flag may be set without 
//being able to RaiseTPL. In this case, since another NET_TRYLOCK() will first check this flag and if flag
//is set, it will return immediately. So it's still safe.
//
//NOTE:After calling NET_TRYLOCK and the lock is obtained, additional NET_TRYLOCK 
//MAY be called WITHOUT self-deadlock, and the lock remains until unlocked.
//
#define NET_TRYLOCK(x)   SctAcquireLockOrFail(x)

//
//VOID  NET_SPINLOCK (IN NET_LOCK  *x)
//
//Description:
//
//NET_SPINLOCK will loop (do nothing) to wait for the lock. Exit loop if lock is acquired, 
//otherwise, the processor calling NET_SPINLOCK will continue to run in the empty loop.
//
//This function is used to synchronize different processors and it only takes effect where multiple processors 
//are available(SMP architecture). 
//In single processor system, this NET_SPINLOCK will prevent from re-entering the same input procedure,
//so shared data will not be accessed twice at same time by input procedure.
//If applications acquire this lock, then input procedure in interrupt mode will be blocked, so needn't worry about it.
//In current implementation on EFI/Tiano, the network software interrupt handler can't be re-entered, so in
//single processor environment, NET_SPINLOCK is defined to be empty.

#define NET_SPIN_LOCK(x)  
#define NET_SPIN_UNLOCK(x)
//
//NOTE: In current network stack implementation, the receiving callback functions are running in interrupt time.
//Moreover, all interfaces exposed by network stack driver can be called in receiving callback functions, so all
//these interfaces may run in interrupt time.
//

//VOID  NET_UNLOCK (IN NET_LOCK  *x)
#define NET_UNLOCK(x)    SctReleaseLock(x)

//flag : UINTN
#define NET_DISABLE_INTERRUPT(flag) (flag = tBS->RaiseTPL(EFI_TPL_HIGH_LEVEL))
#define NET_ENABLE_INTERRUPT(flag)  tBS->RestoreTPL(flag)


//
// Redefined structures
//

//
//double linked list operations
//

#define IS_LIST_EMPTY(ListHead)             SctIsListEmpty (ListHead)

#define NET_LIST_ENTRY                      SCT_LIST_ENTRY
#define LIST_INIT                           SctInitializeListHead
#if (EFI_SPECIFICATION_VERSION < 0x00020028)
#define LIST_ENTRY(Entry,Type,Field)        _CR(Entry,Type,Field)
#else
#define LIST_ENTRY(Entry,Type,Field)        BASE_CR(Entry,Type,Field)
#endif
#define LIST_ENTRY_S(Entry,Type,Field,Sig)  CR(Entry,Type,Field,Sig)
#define LIST_INSERT_HEAD                    SctInsertHeadList
#define LIST_INSERT_TAIL                    SctInsertTailList
#define LIST_IS_EMPTY                       IS_LIST_EMPTY    
#define LIST_FOR_EACH(Entry, ListHead)      for(Entry = (ListHead)->ForwardLink; Entry != (ListHead); Entry = Entry->ForwardLink)

//
//before using following LIST_ macro, make sure the list is not empty
//
#define LIST_REMOVE_ENTRY(Entry)            SctRemoveEntryList (Entry);

#define LIST_REMOVE_HEAD(ListHead){     \
  SCT_LIST_ENTRY *_Net_Entry;           \
  _Net_Entry = (ListHead)->ForwardLink; \
  LIST_REMOVE_ENTRY(_Net_Entry);        \
}

#define LIST_REMOVE_TAIL(ListHead){     \
  SCT_LIST_ENTRY *_Net_Entry;           \
  _Net_Entry = (ListHead)->BackLink;    \
  LIST_REMOVE_ENTRY(_Net_Entry);        \
}

#define LIST_HEAD(ListHead, Type, Field)    LIST_ENTRY((ListHead)->ForwardLink, Type, Field)
#define LIST_TAIL(ListHead, Type, Field)    LIST_ENTRY((ListHead)->BackLink, Type, Field)


#define LIST_INSERT_AFTER_ENTRY(PrevEntry,NewEntry){\
  (NewEntry)->BackLink               = (PrevEntry);\
  (NewEntry)->ForwardLink            = (PrevEntry)->ForwardLink;\
  (PrevEntry)->ForwardLink->BackLink = (NewEntry);\
  (PrevEntry)->ForwardLink           = (NewEntry);\
  }

#define LIST_INSERT_BEFORE_ENTRY(PostEntry,NewEntry){\
  (NewEntry)->ForwardLink            = (PostEntry);\
  (NewEntry)->BackLink               = (PostEntry)->BackLink;\
  (PostEntry)->BackLink->ForwardLink = (NewEntry);\
  (PostEntry)->BackLink              = (NewEntry);\
  }

typedef struct _OBJECT_LIST_CLASS OBJECT_LIST_CLASS;

//
//  Object list structure and operations
//
typedef struct _OBJECT_LIST_ENTRY
{
  NET_LIST_ENTRY        Entry;      // list entry to link with other other entries
  VOID                  *Object;    // Pointer to the object. Maintain by user
} OBJECT_LIST_ENTRY;
/*
#define OBJECT_LIST_INIT_HEAD(x)                  LIST_INIT(&((x)->Entry)); \
                                                  (x)->Object = NULL
#define OBJECT_LIST_INSERT_HEAD(_ListHead, _Entry)  \
          LIST_INSERT_HEAD( &((_ListHead)->Entry), &((_Entry)->Entry) )
#define OBJECT_LIST_INSERT_TAIL(_ListHead, _Entry)  \
          LIST_INSERT_TAIL( &((_ListHead)->Entry), &((_Entry)->Entry) )

#define OBJECT_LIST_IS_EMPTY(_Entry)              LIST_IS_EMPTY( &((_Entry)->Entry) )
#define OBJECT_LIST_REMOVE_ENTRY(_Entry)          LIST_REMOVE_ENTRY( &((_Entry)->Entry) )
#define OBJECT_LIST_GET_NEXT(_Entry)              LIST_ENTRY( (_Entry)->Entry.ForwardLink, OBJECT_LIST_ENTRY, Entry)
#define FREE_OBJECT_LIST(_ListHead)  {\
          OBJECT_LIST_ENTRY   *_ObjListEntry;                       \
          while( !OBJECT_LIST_IS_EMPTY(_ListHead) ){                \
            _ObjListEntry = OBJECT_LIST_GET_NEXT(_ListHead);        \
            OBJECT_LIST_REMOVE_ENTRY(_ObjListEntry);                \
            NetFreePool(_ObjListEntry);                             \
          }                                                         \
        }
*/

typedef
OBJECT_LIST_ENTRY*
(EFIAPI *OBJECT_LIST_GET_FIRST_ENTRY) (
  IN  OBJECT_LIST_CLASS   *This
  );


typedef
EFI_STATUS
(EFIAPI *OBJECT_LIST_INSERT_HEAD) (
  IN  OBJECT_LIST_CLASS   *This,
  IN  VOID                *Object
  );

typedef
EFI_STATUS
(EFIAPI *OBJECT_LIST_INSERT_TAIL) (
  IN  OBJECT_LIST_CLASS   *This,
  IN  VOID                *Object
  );

typedef
BOOLEAN 
(EFIAPI *OBJECT_LIST_IS_EMPTY) (
  IN  OBJECT_LIST_CLASS   *This
  );

typedef
VOID
(EFIAPI *OBJECT_LIST_REMOVE_ENTRY) (
  IN  OBJECT_LIST_CLASS   *This,
  IN  OBJECT_LIST_ENTRY   *Entry
  );

typedef
VOID* 
(EFIAPI *OBJECT_LIST_GET_NEXT) (
  IN      OBJECT_LIST_CLASS     *This,
  IN OUT  OBJECT_LIST_ENTRY     **Entry
  );

typedef
VOID* 
(EFIAPI *OBJECT_LIST_REMOVE_HEAD) (
  IN      OBJECT_LIST_CLASS     *This
  );

typedef
UINTN 
(EFIAPI *OBJECT_LIST_GET_COUNT) (
  IN      OBJECT_LIST_CLASS     *This
  );


typedef
EFI_STATUS
(EFIAPI *OBJECT_LIST_PRE_ALLOCATE_FREE_ENTRY) (
  IN  OBJECT_LIST_CLASS     *This,
  IN  UINTN                 NewEntryCount
  );

typedef
EFI_STATUS
(EFIAPI *OBJECT_LIST_RELEASE_FREE_ENTRY_POOL) (
  IN  OBJECT_LIST_CLASS     *This
  );

typedef
OBJECT_LIST_ENTRY*
(EFIAPI *OBJECT_LIST_GET_ONE_ENTRY_FROM_FREE_ENTRY_POOL) (
  IN  OBJECT_LIST_CLASS     *This
  );

typedef
VOID
(EFIAPI *OBJECT_LIST_RECYCLE_ENTRY)(
  IN  OBJECT_LIST_CLASS     *This,
  IN  OBJECT_LIST_ENTRY     *ObjListEntry
  );

#define DEFAULT_OBJECT_LIST_ALLOCATE_NUMBER   64
struct _OBJECT_LIST_CLASS
{
  // Private member
  NET_LIST_ENTRY            Head;
  NET_LIST_ENTRY            ObjListPool;
  UINTN                     PoolIncrementCount;
  BOOLEAN                   UserAllocated;
  // Public method
  OBJECT_LIST_GET_FIRST_ENTRY   GetFirstEntry;
  OBJECT_LIST_INSERT_HEAD       InsertHead;
  OBJECT_LIST_INSERT_TAIL       InsertTail;
  OBJECT_LIST_IS_EMPTY          IsEmpty;
  OBJECT_LIST_REMOVE_ENTRY      RemoveEntry;
  OBJECT_LIST_GET_NEXT          GetNext;
  OBJECT_LIST_REMOVE_HEAD       RemoveHead;
  OBJECT_LIST_GET_COUNT         GetCount;
  // Private method
  OBJECT_LIST_PRE_ALLOCATE_FREE_ENTRY             PreAllocateFreeEntry;
  OBJECT_LIST_RELEASE_FREE_ENTRY_POOL             ReleaseFreeEntryPool;
  OBJECT_LIST_GET_ONE_ENTRY_FROM_FREE_ENTRY_POOL  GetOneEntryFromFreeEntryPool;
  OBJECT_LIST_RECYCLE_ENTRY                       RecycleEntry;
};

OBJECT_LIST_CLASS*
EFIAPI
NewObjectList (
  IN      UINTN             IncrementCount    OPTIONAL,
  IN OUT  OBJECT_LIST_CLASS *ObjList          OPTIONAL
  );

//EFI_STATUS
VOID
EFIAPI
DeleteObjectList (
  IN OBJECT_LIST_CLASS  *ObjList
  );


//
// Network helper functions. Implemented in Lib\NetLib.c
//

//
//  UINT32 NTOHL(UINT32 x);
//
#define NTOHL(x)               \
  (UINT32)((((UINT32)(x) & 0xff     )<<24) | \
          (((UINT32)(x) & 0xff00    )<<8 ) | \
          (((UINT32)(x) & 0xff0000  )>>8 ) | \
          (((UINT32)(x) & 0xff000000)>>24)   \
         )

//
//  UINT16 NTOHS(UINT16 x);
//
#define NTOHS(x)           \
  (UINT16) ((((UINT16)(x) & 0xff  )<<8) | (((UINT16)(x) & 0xff00)>>8) )

//
//  UINT32 HTONL(UINT32 x)
//
#define  HTONL(x)           NTOHL(x)

//
//  UINT16 HTONS(UINT16 x)
//
#define  HTONS(x)           NTOHS(x)

//
//  UINT32 NTOH64(UINT64 x)
//
#define  NTOH64(x)          NetSwap64(x)

//
//  UINT32 HTON64(UINT64 x)
//
#define  HTON64(x)          NetSwap64(x)

EFI_STATUS
EfiLibInstallAllDriverProtocolsWithUnload (
  IN EFI_HANDLE                         ImageHandle,
  IN EFI_SYSTEM_TABLE                   *SystemTable,
  IN EFI_DRIVER_BINDING_PROTOCOL        *DriverBinding,
  IN EFI_HANDLE                         DriverBindingHandle,
#if (EFI_SPECIFICATION_VERSION >= 0x00020000)
  IN EFI_COMPONENT_NAME2_PROTOCOL       *ComponentName2, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION2_PROTOCOL *DriverConfiguration2,  OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS2_PROTOCOL   *DriverDiagnostics2     OPTIONAL
#else
  IN EFI_COMPONENT_NAME_PROTOCOL        *ComponentName, OPTIONAL
  IN EFI_DRIVER_CONFIGURATION_PROTOCOL  *DriverConfiguration,  OPTIONAL
  IN EFI_DRIVER_DIAGNOSTICS_PROTOCOL    *DriverDiagnostics     OPTIONAL
#endif
  );

typedef
EFI_STATUS 
(EFIAPI *EFI_LIB_DRIVER_UNLOAD) (
  IN EFI_HANDLE  ImageHandle
  );

EFI_STATUS 
EFIAPI
EfiLibDefaultUnload (
  IN EFI_HANDLE  ImageHandle
  );


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
  );


typedef struct _NET_FRAGMENT_DATA
{
 UINT32       FragmentLength;
 VOID         *FragmentBuffer;
} NET_FRAGMENT_DATA;

// calculate the internet checksum (RFC 1071)
// return 16 bit ones complement of ones complement sum of 16 bit words
UINT16
NetFragmentChecksum(
  IN UINTN FragmentCount, 
  IN NET_FRAGMENT_DATA *FragmentTable);

UINT16
NetChecksum(
  IN UINT8  *Buffer, 
  IN UINTN  Length);

INTN
NetAsciiStrCaseCmp(
  IN  CHAR8   *Left,
  IN  CHAR8   *Right);

UINT64
NetAsciiStrToU64(
  IN  CHAR8   *Str);

UINT64
NetSwap64(
  IN  UINT64    Num);

UINT64
NetTimeToSeconds(
  EFI_TIME   Time);

//
//  Public used data structures
//

#define US_TO_100_NS                          10
#define MS_TO_100_NS                          (1000*US_TO_100_NS)
#define S_TO_100NS                            (1000*MS_TO_100_NS)

#define NET_IFTYPE_ETHERNET             0x01
#define NET_IFTYPE_TOKENRING            0x04
#define NET_IFTYPE_FIBRE_CHANNEL        0x12


//
// The following stucture/macro are designed for ethernet only.
// If we want to extend it to other physical network we need to make 
// modifications to them
//

#define NET_ETHER_ADDR_LEN    6
#define NET_ETHER_MTU         1514

#define NET_IPV4_PROTOCOL_ADDRESS_LEN       4         // 32bits, 4 bytes

#define NET_MEDIA_HEADER_PROTOCOL_IPV4      0x0800    // Host byte order
#define NET_MEDIA_HEADER_PROTOCOL_ARP       0x0806    // Host byte order
#define NET_MEDIA_HEADER_PROTOCOL_IPV6      0x86DD    // Host byte order

#pragma pack(1)
typedef struct _NET_ETHER_HEADER
{
  UINT8   DstMac[ NET_ETHER_ADDR_LEN ];
  UINT8   SrcMac[ NET_ETHER_ADDR_LEN ];
  UINT16  ProtocolType;
} NET_ETHER_HEADER;
#pragma pack()

#define NET_MAX_PROTOCOL_ADDRESS_LENGTH sizeof(EFI_IP_ADDRESS)
#define NET_MAX_HARDWARE_ADDRESS_LENGTH sizeof(EFI_MAC_ADDRESS)

typedef struct _NET_PROTOCOL_ADDRESS
{
  UINT16        ProtocolAddressType;
  UINT8         ProtocolAddressLen;
  UINT8         ProtocolAddress[ NET_MAX_PROTOCOL_ADDRESS_LENGTH ];
} NET_PROTOCOL_ADDRESS;

typedef struct _NET_HARDWARE_ADDRESS
{
  UINT16        HardwareAddressType;
  UINT8         HardwareAddressLen;
  UINT8         HardwareAddress[ NET_MAX_HARDWARE_ADDRESS_LENGTH ];
} NET_HARDWARE_ADDRESS;

#define IS_EQUAL_NET_HARDWARE_ADDRESS( Addr1, Addr2 ) \
  ( ( (Addr1)->HardwareAddressType == (Addr2)->HardwareAddressType ) &&     \
    ( (Addr1)->HardwareAddressLen == (Addr2)->HardwareAddressLen ) &&       \
    ( NetCompareMem ( (Addr1)->HardwareAddress, (Addr2)->HardwareAddress, (Addr1)->HardwareAddressLen ) == 0 )  \
  )

#define NET_ETHER_HEADER_SIZE   sizeof(NET_ETHER_HEADER)
#define NET_ETHER_FCS_SIZE      4

extern EFI_MAC_ADDRESS  BroadcastMacAddr;

#define IS_BROADCAST_EFI_MAC_ADDR( Mac )  \
  ( NetCompareMem ( BroadcastMacAddr.Addr, (Mac)->Addr, NET_ETHER_ADDR_LEN ) == 0 )

#define IS_MULTICAST_EFI_MAC_ADDR( Mac )  \
  (((*((UINT32*)Mac) & 0x00000001) == 0x00000001) && !IS_BROADCAST_EFI_MAC_ADDR(Mac))



#define IS_EQUAL_EFI_MAC_ADDR( Mac1, Mac2 ) \
  ( NetCompareMem ( (Mac1)->Addr, (Mac2)->Addr, NET_ETHER_ADDR_LEN ) == 0 )
/*
#define IS_EQUAL_EFI_MAC_ADDR( Mac1, Mac2 ) \
  ( (Mac1)->Addr[0] == (Mac2)->Addr[0] &&   \
    (Mac1)->Addr[1] == (Mac2)->Addr[1] &&   \
    (Mac1)->Addr[2] == (Mac2)->Addr[2] &&   \
    (Mac1)->Addr[3] == (Mac2)->Addr[3] &&   \
    (Mac1)->Addr[4] == (Mac2)->Addr[4] &&   \
    (Mac1)->Addr[5] == (Mac2)->Addr[5]      \
  )

#define MAC_COPY_ADDR(DstMac, SrcMac) \
  {                                   \
      UINTN Index;                    \
      for(Index=0;Index<sizeof(EFI_MAC_ADDRESS);Index++){  \
        ((EFI_MAC_ADDRESS*)(DstMac))->Addr[Index] = ((EFI_MAC_ADDRESS*)(SrcMac))->Addr[Index];\
      }\
  }
*/
#define MAC_COPY_ADDR(DstMac, SrcMac) ((*(DstMac)) = (*(SrcMac)))


#define IS_BROADCAST_MAC_ADDR( Mac )  \
          ( *((UINT32*)(Mac)) == 0xffffffff && ((UINT16*)(Mac))[2] == 0xffff )

//
//  See http://www.cisco.com/univercd/cc/td/doc/cisintwk/ito_doc/ipmulti.htm#xtocid11
//  for multicase MAC address define
//  (This macro is for network byte order MAC address)
//
#define IS_MULTICAST_MAC_ADDR( Mac )  \
  (((*((UINT32*)Mac) & 0x00000001) == 0x00000001) && !IS_BROADCAST_MAC_ADDR(Mac))

#define IS_EQUAL_MAC_ADDR( Mac1, Mac2 ) \
  ( NetCompareMem ( (Mac1), (Mac2), NET_ETHER_ADDR_LEN ) == 0 )
#endif /* _EFI_NET_LIB_H */
