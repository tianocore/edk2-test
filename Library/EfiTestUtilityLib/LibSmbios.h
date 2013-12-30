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
                                                                
  Copyright 2006, 2007, 2008, 2009, 2010 Unified EFI, Inc. All  
  Rights Reserved, subject to all existing rights in all        
  matters included within this Test Suite, to which United      
  EFI, Inc. makes no claim of right.                            
                                                                
  Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>   
   
--*/
/*++

Module Name:

  LibSmbios.h

Abstract:

  Lib include  for SMBIOS services. Used to get system serial number and GUID

--*/

#ifndef _LIB_SMBIOS_H
#define _LIB_SMBIOS_H

//
// Define SMBIOS tables.
//

#pragma pack(1)

typedef UINT8   SMBIOS_STRING;

typedef struct {
  UINT8   AnchorString[4];
  UINT8   EntryPointStructureChecksum;
  UINT8   EntryPointLength;
  UINT8   MajorVersion;
  UINT8   MinorVersion;
  UINT16  MaxStructureSize;
  UINT8   EntryPointRevision;
  UINT8   FormattedArea[5];
  UINT8   IntermediateAnchorString[5];
  UINT8   IntermediateChecksum;
  UINT16  TableLength;
  UINT32  TableAddress;
  UINT16  NumberOfSmbiosStructures;
  UINT8   SmbiosBcdRevision;
} SMBIOS_STRUCTURE_TABLE;

//
// Please note that SMBIOS structures can be odd byte aligned since the
//  unformated section of each record is a set of arbitrary size strings.
//

typedef struct {
  UINT8   Type;
  UINT8   Length;
  UINT16  Handle;
} SMBIOS_HEADER;


typedef struct {
  SMBIOS_HEADER   Hdr;
  SMBIOS_STRING   Vendor;
  SMBIOS_STRING   BiosVersion;
  UINT16          BiosSegment;
  SMBIOS_STRING   BiosReleaseDate;
  UINT8           BiosSize;
  UINT64          BiosCharacteristics;
} SMBIOS_TYPE0;

typedef struct {
  SMBIOS_HEADER   Hdr;
  SMBIOS_STRING   Manufacturer;
  SMBIOS_STRING   ProductName;
  SMBIOS_STRING   Version;
  SMBIOS_STRING   SerialNumber;
  EFI_GUID        Uuid;
  UINT8           WakeUpType;
} SMBIOS_TYPE1;

typedef struct {
  SMBIOS_HEADER   Hdr;
  SMBIOS_STRING   Manufacturer;
  SMBIOS_STRING   ProductName;
  SMBIOS_STRING   Version;
  SMBIOS_STRING   SerialNumber;
} SMBIOS_TYPE2;

typedef struct {
  SMBIOS_HEADER   Hdr;
  SMBIOS_STRING   Manufacturer;
  UINT8           Type;
  SMBIOS_STRING   Version;
  SMBIOS_STRING   SerialNumber;
  SMBIOS_STRING   AssetTag;
  UINT8           BootupState;
  UINT8           PowerSupplyState;
  UINT8           ThermalState;
  UINT8           SecurityStatus;
  UINT8           OemDefined[4];
} SMBIOS_TYPE3;

typedef struct {
  SMBIOS_HEADER   Hdr;
  UINT8           Socket;
  UINT8           ProcessorType;
  UINT8           ProcessorFamily;
  SMBIOS_STRING   ProcessorManufacture;
  UINT8           ProcessorId[8];
  SMBIOS_STRING   ProcessorVersion;
  UINT8           Voltage;
  UINT16          ExternalClock;
  UINT16          MaxSpeed;
  UINT16          CurrentSpeed;
  UINT8           Status;
  UINT8           ProcessorUpgrade;
  UINT16          L1CacheHandle;
  UINT16          L2CacheHandle;
  UINT16          L3CacheHandle;
  SMBIOS_STRING   SerialNumber;
  SMBIOS_STRING   AssetTag;
  SMBIOS_STRING   PartNumber;
} SMBIOS_TYPE4;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8     ErrDetectMethod;
  UINT8     ErrCorrectCapability;
  UINT8     SupportInterleave;
  UINT8     CurrentInterleave;
  UINT8     MaxMemoryModuleSize;
  UINT16    SupportSpeed;
  UINT16    SupportMemoryType;
  UINT8     MemoryModuleVoltage;
  UINT8     AssociatedMemorySlotNum;
//  UINT16    MemoryModuleConfigHandles[Num]; //Num is AssociatedMemorySlotNum
//  UINT8     EnableErrCorrectCapabilities;
} SMBIOS_TYPE5;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING SocketDesignation;
  UINT8     BankConnections;
  UINT8     CurrentSpeed;
  UINT16    CurrentMemoryType;
  UINT8     InstalledSize;
  UINT8     EnabledSize;
  UINT8     ErrorStatus;
} SMBIOS_TYPE6;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING SocketDesignation;
  UINT16        CacheConfiguration;
  UINT16        MaximumCacheSize;
  UINT16        InstalledSize;
  UINT16        SupportedSRAMType;
  UINT16        CurrentSRAMType;
  UINT8         CacheSpeed;
  UINT8         ErrorCorrectionType;
  UINT8         SystemCacheType;
  UINT8         Associativity;
} SMBIOS_TYPE7;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING InternalReferenceDesignator;
  UINT8         InternalConnectorType;
  SMBIOS_STRING ExternalReferenceDesignator;
  UINT8         ExternalConnectorType;
  UINT8         PortType;
} SMBIOS_TYPE8;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING SlotDesignation;
  UINT8         SlotType;
  UINT8         SlotDataBusWidth;
  UINT8         CurrentUsage;
  UINT8         SlotLength;
  UINT16        SlotID;
  UINT8         SlotCharacteristics1;
  UINT8         SlotCharacteristics2;
} SMBIOS_TYPE9;


typedef struct DeviceStruct {
  UINT8         DeviceType;
  SMBIOS_STRING DescriptionString;
} DeviceStruct;

typedef struct {
  SMBIOS_HEADER Hdr;
  DeviceStruct  Device[1];
} SMBIOS_TYPE10;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         StringCount;
//  SMBIOS_STRING bufOEMString[1];
} SMBIOS_TYPE11;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         StringCount;
//  SMBIOS_STRING bufSysConfigurations[1];
} SMBIOS_TYPE12;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         InstallableLanguages;
  UINT8         Flags;
  UINT8         reserved[15];
//  SMBIOS_STRING IntalledLanguages;
  SMBIOS_STRING CurrentLanguages;
} SMBIOS_TYPE13;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING GroupName;
  UINT8         ItemType;
  UINT16        ItemHandle;
} SMBIOS_TYPE14;


typedef struct EVENTLOGTYPE {
  UINT8     LogType;
  UINT8     DataFormatType;
} EVENTLOGTYPE;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT16        LogAreaLength;
  UINT16        LogHeaderStartOffset;
  UINT16        LogDataStartOffset;
  UINT8         AccessMethod;
  UINT8         LogStatus;
  UINT32        LogChangeToken;
  UINT32        AccessMethodAddress;
  UINT8         LogHeaderFormat;
  UINT8         NumberOfSupportedLogTypeDescriptors;
  UINT8         LengthOfLogTypeDescriptor;
  EVENTLOGTYPE  EventLogTypeDescriptors[1];
} SMBIOS_TYPE15;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         Location;
  UINT8         Use;
  UINT8         MemoryErrorCorrection;
  UINT32        MaximumCapacity;
  UINT16        MemoryErrorInformationHandle;
  UINT16        NumberOfMemoryDevices;
} SMBIOS_TYPE16;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT16        MemoryArrayHandle;
  UINT16        MemoryErrorInformationHandle;
  UINT16        TotalWidth;
  UINT16        DataWidth;
  UINT16        Size;
  UINT8         FormFactor;
  UINT8         DeviceSet;
  SMBIOS_STRING DeviceLocator;
  SMBIOS_STRING BankLocator;
  UINT8         MemoryType;
  UINT16        TypeDetail;
  UINT16        Speed;
  SMBIOS_STRING Manufacturer;
  SMBIOS_STRING SerialNumber;
  SMBIOS_STRING AssetTag;
  SMBIOS_STRING PartNumber;
} SMBIOS_TYPE17;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         ErrorType;
  UINT8         ErrorGranularity;
  UINT8         ErrorOperation;
  UINT32        VendorSyndrome;
  UINT32        MemoryArrayErrorAddress;
  UINT32        DeviceErrorAddress;
  UINT32        ErrorResolution;
} SMBIOS_TYPE18;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT32        StartingAddress;
  UINT32        EndingAddress;
  UINT16        MemoryArrayHandle;
  UINT8         PartitionWidth;
} SMBIOS_TYPE19;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT32        StartingAddress;
  UINT32        EndingAddress;
  UINT16        MemoryDeviceHandle;
  UINT16        MemoryArrayMappedAddressHandle;
  UINT8         PartitionRowPosition;
  UINT8         InterleavePosition;
  UINT8         InterleavedDataDepth;
} SMBIOS_TYPE20;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         Type;
  UINT8         Interface;
  UINT8         NumberOfButtons;
} SMBIOS_TYPE21;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Location;
  SMBIOS_STRING Manufacturer;
  SMBIOS_STRING ManufactureDate;
  SMBIOS_STRING SerialNumber;
  SMBIOS_STRING DeviceName;
  SMBIOS_STRING BankLocator;
  UINT8         DeviceChemistry;
  UINT16        DeviceCapacity;
  UINT16        DesignVoltage;
  SMBIOS_STRING SBDSVersionNumber;
  UINT8         MaximumErrorInBatteryData;
  UINT16        SBDSSerialNumber;
  UINT16        SBDSManufactureDate;
  SMBIOS_STRING SBDSDeviceChemistry;
  UINT8         DesignCapacityMultiplier;
  UINT32        OEMSpecific;
} SMBIOS_TYPE22;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         Capabilities;
  UINT16        ResetCount;
  UINT16        ResetLimit;
  UINT16        TimerInterval;
  UINT16        Timeout;
} SMBIOS_TYPE23;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         HardwareSecuritySettings;
} SMBIOS_TYPE24;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         NextScheduledPowerOnMonth;
  UINT8         NextScheduledPowerOnDayOfMonth;
  UINT8         NextScheduledPowerOnHour;
  UINT8         NextScheduledPowerOnMinute;
  UINT8         NextScheduledPowerOnSecond;
} SMBIOS_TYPE25;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Description;
  UINT8         LocationAndStatus;
  UINT16        MaximumValue;
  UINT16        MinimumValue;
  UINT16        Resolution;
  UINT16        Tolerance;
  UINT16        Accuracy;
  UINT32        OEMDefined;
  UINT16        NominalValue;
} SMBIOS_TYPE26;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT16        TemperatureProbeHandle;
  UINT8         DeviceTypeAndStatus;
  UINT8         CoolingUnitGroup;
  UINT32        OEMDefined;
  UINT16        NominalSpeed;
} SMBIOS_TYPE27;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Description;
  UINT8         LocationAndStatus;
  UINT16        MaximumValue;
  UINT16        MinimumValue;
  UINT16        Resolution;
  UINT16        Tolerance;
  UINT16        Accuracy;
  UINT32        OEMDefined;
  UINT32        NominalValue;
} SMBIOS_TYPE28;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Description;
  UINT8         LocationAndStatus;
  UINT16        MaximumValue;
  UINT16        MinimumValue;
  UINT16        Resolution;
  UINT16        Tolerance;
  UINT16        Accuracy;
  UINT32        OEMDefined;
  UINT16        NominalValue;
} SMBIOS_TYPE29;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING ManufacturerName;
  UINT8         Connections;
} SMBIOS_TYPE30;

typedef struct {
  SMBIOS_HEADER Hdr;
} SMBIOS_TYPE31;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         Reserved[6];
  UINT8         BootStatus[1];
} SMBIOS_TYPE32;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         ErrorType;
  UINT8         ErrorGranularity;
  UINT8         ErrorOperation;
  UINT32        VendorSyndrome;
  UINT64        MemoryArrayErrorAddress;
  UINT64        DeviceErrorAddress;
  UINT32        ErrorResolution;
} SMBIOS_TYPE33;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Description;
  UINT8         Type;
  UINT32        Address;
  UINT8         AddressType;
} SMBIOS_TYPE34;

typedef struct {
  SMBIOS_HEADER Hdr;
  SMBIOS_STRING Description;
  UINT16        ManagementDeviceHandle;
  UINT16        ComponentHandle;
  UINT16        ThresholdHandle;
} SMBIOS_TYPE35;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT16        LowerThresholdNonCritical;
  UINT16        UpperThresholdNonCritical;
  UINT16        LowerThresholdCritical;
  UINT16        UpperThreaholdCritical;
  UINT16        LowerThresholdNonRecoverable;
  UINT16        UpperThresholdNonRecoverable;
} SMBIOS_TYPE36;


typedef struct MEMORYDEVICE {
  UINT8         DeviceLoad;
  UINT16          DeviceHandle;
} MEMORYDEVICE;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         ChannelType;
  UINT8         MaximumChannelLoad;
  UINT8         MemoryDeviceCount;
  MEMORYDEVICE  MemoryDevice[1];
} SMBIOS_TYPE37;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         InterfaceType;
  UINT8         IPMISpecificationRevision;
  UINT8         I2CSlaveAddress;
  UINT8         NVStorageDeviceAddress;
  UINT64        BaseAddress;
//  UINT8       BaseAddressModifier_InterruptInfo;
//  UINT8       InterruptNumber;
} SMBIOS_TYPE38;

typedef struct {
  SMBIOS_HEADER Hdr;
  UINT8         PowerUnitGroup;
  SMBIOS_STRING Location;
  SMBIOS_STRING DeviceName;
  SMBIOS_STRING Manufacturer;
  SMBIOS_STRING SerialNumber;
  SMBIOS_STRING AssetTagNumber;
  SMBIOS_STRING ModelPartNumber;
  SMBIOS_STRING RevisionLevel;
  SMBIOS_STRING Description;
  UINT16        MaxPowerCapacity;
  UINT16        PowerSupplyCharacteristics;
  UINT16        InputVoltageProbeHandle;
  UINT16        CoolingDeviceHandle;
  UINT16        InputCurrentProbeHandle;
} SMBIOS_TYPE39;

typedef struct {
  SMBIOS_HEADER Hdr;
} SMBIOS_TYPE126;

typedef struct {
  SMBIOS_HEADER Hdr;
} SMBIOS_TYPE127;


/*
  Notes:
    Among the following 42 type of structues for SMBIOS Stucture table,
    There are only 11 Types(0,1,3,4,7,9,16,17,19,20,32) are required,
    The other types is optional.
*/
typedef union {
  SMBIOS_HEADER   *Hdr;
  SMBIOS_TYPE0    *Type0;
  SMBIOS_TYPE1    *Type1;
  SMBIOS_TYPE2    *Type2;
  SMBIOS_TYPE3    *Type3;
  SMBIOS_TYPE4    *Type4;
  SMBIOS_TYPE5    *Type5;
  SMBIOS_TYPE6    *Type6;
  SMBIOS_TYPE7    *Type7;
  SMBIOS_TYPE8    *Type8;
  SMBIOS_TYPE9    *Type9;
  SMBIOS_TYPE10   *Type10;
  SMBIOS_TYPE11   *Type11;
  SMBIOS_TYPE12   *Type12;
  SMBIOS_TYPE13   *Type13;
  SMBIOS_TYPE14   *Type14;
  SMBIOS_TYPE15   *Type15;
  SMBIOS_TYPE16   *Type16;
  SMBIOS_TYPE17   *Type17;
  SMBIOS_TYPE18   *Type18;
  SMBIOS_TYPE19   *Type19;
  SMBIOS_TYPE20   *Type20;
  SMBIOS_TYPE21   *Type21;
  SMBIOS_TYPE22   *Type22;
  SMBIOS_TYPE23   *Type23;
  SMBIOS_TYPE24   *Type24;
  SMBIOS_TYPE25   *Type25;
  SMBIOS_TYPE26   *Type26;
  SMBIOS_TYPE27   *Type27;
  SMBIOS_TYPE28   *Type28;
  SMBIOS_TYPE29   *Type29;
  SMBIOS_TYPE30   *Type30;
  SMBIOS_TYPE31   *Type31;
  SMBIOS_TYPE32   *Type32;
  SMBIOS_TYPE33   *Type33;
  SMBIOS_TYPE34   *Type34;
  SMBIOS_TYPE35   *Type35;
  SMBIOS_TYPE36   *Type36;
  SMBIOS_TYPE37   *Type37;
  SMBIOS_TYPE38   *Type38;
  SMBIOS_TYPE39   *Type39;
  SMBIOS_TYPE126  *Type126;
  SMBIOS_TYPE127  *Type127;
  UINT8           *Raw;
} SMBIOS_STRUCTURE_POINTER;

#pragma pack()

#endif
