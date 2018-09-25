/** @file

  Copyright 2006 - 2016 Unified EFI, Inc.<BR>
  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>   

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at 
  http://opensource.org/licenses/bsd-license.php
 
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 
**/
/*++

Module Name:

  Tape.h

Abstract:

  define for TapeIo Protocol

--*/

#ifndef _TAPE_H_
#define _TAPE_H_


#define Hex2Ascii(_x)  ( ( ((_x)&0x0f)<10) ? ('0'+((_x)&0x0f)) : ('a'-10+((_x)&0x0f)) )
#define HEX2ASCII(_x)  ( ( ((_x)&0x0f)<10) ? ('0'+((_x)&0x0f)) : ('A'-10+((_x)&0x0f)) )

#define ASCII2HEX(_x)   ( ((_x)<='9') ? ((_x)-'0') : (((_x)<='F') ? ((_x)-'A') : ((_x)-'a')) )
#define Ascii2Hex ASCII2HEX


#define EFI_TAPE_IO_PROTOCOL_GUID { 0X1E93E633, 0XD65A, 0X459E, { 0XAB, 0X84, 0X93, 0XD9, 0XEC, 0X26, 0X6D, 0X18 }}

typedef struct _EFI_TAPE_IO_PROTOCOL EFI_TAPE_IO_PROTOCOL;;


#define TAPE_READ_TIMEOUT 	60 //	seconds
#define TAPE_WRITE_TIMEOUT 	60 //	seconds
#define TAPE_REWIND_TIMEOUT 60 //	seconds
#define TAPE_SPACE_TIMEOUT 	60 //	seconds
#define TAPE_WRITEFM_TIMEOUT 	60 //	seconds
#define TAPE_RESET_TIMEOUT 	60 //	seconds

#ifndef  EFI_END_OF_FILE
#define EFI_END_OF_FILE		0x10001001
#endif
#ifndef  EFI_END_OF_MEDIA
#define EFI_END_OF_MEDIA	0x10001002
#endif

//#define TAPE_BLOCK_SIZE 32768/16384/8192/4096/2048/1024/512/80
#define TAPE_BLOCK_SIZE 16384
//	0)return: EFI_SUCCESS when data was successfully transferred 
//	1)return: EFI_END_OF_FILE, when meeting file end
//	2)do read current file status by Buffer==NULL and BufferSize==0
//	3)return: EFI_NO_MEDIA when no media is loaded in the device
//	4)return: EFI_MEDIA_CHANGES when media changed since the last access, abort transfer
//	5)return: EFI_DEVICE_ERROR when a device error occurred while attrmpting to transfer data
//	6)return: EFI_INVALID_PATAMETER when Buffer==NULL but BufferSize!=0, or BufferSize is not multiple of device's fixed block size
//	7)return: EFI_NOT_READY	when device not ready, the transfer may be retried at a later time
//	8)return: EFI_TIMEOUT when transfer failed to complete whithin the timeout specified
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_READ)(
	IN EFI_TAPE_IO_PROTOCOL *_this,	//	a pointer to the EFI_TAPE_IO_PROCOTOL
	IN OUT UINTN *BufferSize,		//	size of the buffer in bytes pointed to by Buffer
	OUT void *Buffer				//	pointer to the buffer for data to be read into
);	

//	0)return: EFI_SUCCESS when data was successfully transferred 
//	1)return: EFI_END_OF_MEDIA, when reached the logical end of media, data may have transfer successfully
//	2)do read current operate status by Buffer==NULL and BufferSize==0
//	3)return: EFI_NO_MEDIA when no media is loaded in the device
//	4)return: EFI_MEDIA_CHANGES when media changed since the last access, abort transfer
//	5)return: EFI_DEVICE_ERROR when a device error occurred while attrmpting to transfer data
//	6)return: EFI_INVALID_PATAMETER when Buffer==NULL but BufferSize!=0, or BufferSize is not multiple of device's fixed block size
//	7)return: EFI_NOT_READY	when device not ready, the transfer may be retried at a later time
//	8)return: EFI_TIMEOUT when transfer failed to complete whithin the timeout specified
//	9)return: EFI_WRITE_PROTECTED when the media is write-protected
//	a)return: EFI_UNSUPPORTED when the device does not support this type transfer
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_WRITE)(
	IN EFI_TAPE_IO_PROTOCOL *_this,	//	a pointer to the EFI_TAPE_IO_PROCOTOL
	IN UINTN *BufferSize,			//	size of the buffer in bytes pointed to by Buffer
	OUT void *Buffer				//	pointer to the buffer for data to be written from
);	


//	0)return: EFI_SUCCESS when the media was successfully repositioned
//	1)return: EFI_NO_MEDIA when no media is loaded in the device
//	2)return: EFI_DEVICE_ERROR when a device error occurred while attrmpting to reposition the media
//	3)return: EFI_NOT_READY	when device not ready, the transfer may be retried at a later time
//	4)return: EFI_TIMEOUT when reposition failed to complete whithin the timeout specified
//	5)return: EFI_UNSUPPORTED when the device does not support this type transfer
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_REWIND)(
	IN EFI_TAPE_IO_PROTOCOL *_this	//	a pointer to the EFI_TAPE_IO_PROCOTOL
);	

//	0)return: EFI_SUCCESS when the media was successfully repositioned
//	1)return: EFI_END_OF_MEDIA when beginning or end of media was reached before the indicated number of data block or filemarks were found
//	2)return: EFI_NO_MEDIA when no media is loaded in the device
//	3)return: EFI_MEDIA_CHANGED when media changed since the last access in the device
//	4)return: EFI_DEVICE_ERROR when a device error occurred while attrmpting to reposition the media
//	5)return: EFI_NOT_READY	when device not ready, the transfer may be retried at a later time
//	6)return: EFI_TIMEOUT when reposition failed to complete whithin the timeout specified
//	7)return: EFI_UNSUPPORTED when the device does not support this type transfer
//	Type=0 for BLOCK, =1 for FILEMARK
#define TAPE_SPACE_TYPE_BLOCK 		0x00
#define TAPE_SPACE_TYPE_FILEMARK 	0x01
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_SPACE)(
	IN EFI_TAPE_IO_PROTOCOL *_this,	//	a pointer to the EFI_TAPE_IO_PROCOTOL
	IN INTN Direction,				//	direction and number of data block or filemarks to space over on media
	IN UINTN Type					//	type of mark to space over on media
);	

//	0)return: EFI_SUCCESS when data was successfully transferred
//	1)return: EFI_END_OF_MEDIA when beginning or end of media was reached before completed
//	2)return: EFI_NO_MEDIA when no media is loaded in the device
//	3)return: EFI_MEDIA_CHANGED when media changed since the last access in the device
//	4)return: EFI_DEVICE_ERROR when a device error occurred while transfer data
//	5)return: EFI_NOT_READY	when device not ready, the transfer may be retried at a later time
//	6)return: EFI_TIMEOUT when reposition failed to complete whithin the timeout specified
//	7)return: EFI_UNSUPPORTED when the device does not support this type transfer
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_WRITEFM)(
	IN EFI_TAPE_IO_PROTOCOL *_this,	//	a pointer to the EFI_TAPE_IO_PROCOTOL
	IN UINTN Count					//	number of filemarks to write to the media
);	


//	0)return: EFI_SUCCESS when bus and/or bus was successfully reset
//	1)return: EFI_NO_MEDIA when no media is loaded in the device
//	4)return: EFI_DEVICE_ERROR when a device error occurred while resetting
//	5)return: EFI_NOT_READY	when device not ready, the reset may be retried at a later time
//	6)return: EFI_TIMEOUT when reset failed to complete whithin the timeout specified
//	7)return: EFI_UNSUPPORTED when the device does not support this type reset
typedef EFI_STATUS
(EFIAPI *EFI_TAPE_RESET)(
	IN EFI_TAPE_IO_PROTOCOL *_this,	//	a pointer to the EFI_TAPE_IO_PROCOTOL
	IN BOOLEAN ExtendVerification	//	indicates whether the parent bus should alse be reset
);	


struct _EFI_TAPE_IO_PROTOCOL {
	EFI_TAPE_READ	TapeRead;		//	read a block of data from tape
	EFI_TAPE_WRITE 	TapeWrite;		//	write a block of data to the tape
	EFI_TAPE_REWIND	TapeRewind;		//	rewind the tape
	EFI_TAPE_SPACE	TapeSpace;		//	position the tape
	EFI_TAPE_WRITEFM	TapeWriteFM;//	write filemarks to the tape
	EFI_TAPE_RESET	TapeReset;		//	reset the tape device or its parent bus
};


typedef struct _TAPE_HEADER_FORMAT{
	UINT64 Signature;		//  should be equal to "EFI BOOT"
	UINT32 Revision;		//  = 1
	UINT32 BootDescSize;	//  = 1024
	UINT32 BootDescCRC;		//
	EFI_GUID TapeGuid;		//	EFI BOOT Tape GUID
	EFI_GUID TapeType;		//	EFI BOOT Tape Type GUID, for Bootloader and OS
	EFI_GUID TapeUnique;
	UINT32 BLLocation;		//	File number of EFI bootloader relative to the boot tape header
	UINT32 BLBlocksize;		//	EFI Bootloader Block Size in bytes
	UINT32 BLFilesize;		//	EFI Bootloader Total Size in bytes
	char OSVersion[40];		//	OS version(ASCII)
	char AppVersion[40];	//	Application Version(ASCII)
	char CreationDate[10];	//	EFI boot tape creation data(UTC) (yyyy-mm-dd ASCII)
	char CreationTime[10];	//	EFI boot tape creation time(UTC) (hh:mm:ss in ASCII)
	char SystemName[256];	//	Computer System Name(UTF-8, ref:2044)
	char TapeTitle[120];	//	Boot Tape Tile/Comment(UTF-8, ref:2044)
	char pad[468];			//	Reserved
}tape_header;	

#endif
