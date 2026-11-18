/** @file

  Copyright (c) 2026, Arm Ltd. All rights reserved.<BR>

  This program and the accompanying materials are licensed and made available
  under the terms and conditions of the BSD License which accompanies this
  distribution. The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include "SctLib.h"
#include <Guid/ImageAuthentication.h>
#include "SecureBootBBTestMain.h"
#include "SecureBootBBTestSupport.h"

#define KEK_ATTRIBUTES  (EFI_VARIABLE_NON_VOLATILE | \
                         EFI_VARIABLE_BOOTSERVICE_ACCESS | \
                         EFI_VARIABLE_RUNTIME_ACCESS | \
                         EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS)

#define PERSISTENCE_VERSION       2U
#define PERSISTENCE_STAGE_CLEANUP  1U
#define PERSISTENCE_STAGE_RESET    2U
#define RECOVERY_BUFFER_SIZE      1024U
#define PERSISTENCE_JOURNAL        L"AuthVariablePersistence.rec"

typedef enum {
  Kek4T1,
  Kek4T2,
  Kek1T3,
  PersistenceFileCount
} PERSISTENCE_FILE_INDEX;

typedef struct {
  VOID   *Data;
  UINTN  Size;
} PERSISTENCE_FILE;

typedef struct {
  PERSISTENCE_FILE  Requests[PersistenceFileCount];
  // Payload views borrow storage from the requests and must not be freed.
  PERSISTENCE_FILE  Kek4Payload;
  PERSISTENCE_FILE  Kek1Payload;
} PERSISTENCE_FIXTURES;

typedef struct {
  EFI_GUID  Signature;
  UINT32    Version;
  UINT32    Stage;
  // Identify the three authenticated requests across reset.
  UINT32    FixtureCrc[PersistenceFileCount];
} PERSISTENCE_RECORD;

STATIC EFI_GUID  mPersistenceSignature = SECURE_BOOT_AUTH_VARIABLE_PERSISTENCE_TEST_GUID;
STATIC EFI_GUID  mPkcs7Guid = EFI_CERT_TYPE_PKCS7_GUID;
STATIC EFI_GUID  mX509Guid = EFI_CERT_X509_GUID;
STATIC CHAR16    *mPersistenceFiles[PersistenceFileCount] = {
  L"TestKEK4T1.auth",
  L"TestKEK4T2.auth",
  L"TestKEK1T3.auth"
};

STATIC
EFI_STATUS
RecordPersistenceAssertion (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_GUID                            AssertionGuid,
  IN EFI_TEST_ASSERTION                  Result,
  IN CHAR16                              *Detail,
  IN UINTN                               LineNumber
  )
{
  CHAR16  *Description;

  Description = L"SecureBoot - authenticated KEK persistence";

  if (Result == EFI_TEST_ASSERTION_PASSED) {
    if (SctCompareMem (
          &AssertionGuid,
          &gSecureBootAuthVariablePersistenceBbTestAssertionGuid001,
          sizeof (EFI_GUID)
          ) == 0) {
      Description = L"SecureBoot - KEK persistence across cold reset";
    } else if (SctCompareMem (
                 &AssertionGuid,
                 &gSecureBootAuthVariablePersistenceBbTestAssertionGuid002,
                 sizeof (EFI_GUID)
                 ) == 0) {
      Description = L"SecureBoot - KEK replay protection";
    } else if (SctCompareMem (
                 &AssertionGuid,
                 &gSecureBootAuthVariablePersistenceBbTestAssertionGuid003,
                 sizeof (EFI_GUID)
                 ) == 0) {
      Description = L"SecureBoot - authenticated KEK update";
    } else if (SctCompareMem (
                 &AssertionGuid,
                 &gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
                 sizeof (EFI_GUID)
                 ) == 0) {
      Description = L"SecureBoot - KEK restoration and cleanup";
    }
  }

  return StandardLib->RecordAssertion (
                        StandardLib,
                        Result,
                        AssertionGuid,
                        Description,
                        L"%a:%d: %s",
                        __FILE__,
                        LineNumber,
                        Detail
                        );
}

STATIC
EFI_STATUS
LoadDependencyFile (
  IN CHAR16              *FileName,
  OUT PERSISTENCE_FILE   *File
  )
{
  EFI_STATUS       Status;
  EFI_FILE_HANDLE  FileHandle;
  UINT32           FileSize;
  UINTN            BufferSize;

  Status = OpenFileAndGetSize (FileName, &FileHandle, &FileSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (FileSize == 0) {
    FileHandle->Close (FileHandle);
    return EFI_LOAD_ERROR;
  }

  File->Data = SctAllocatePool (FileSize);
  if (File->Data == NULL) {
    FileHandle->Close (FileHandle);
    return EFI_OUT_OF_RESOURCES;
  }

  BufferSize = FileSize;
  Status = FileHandle->Read (FileHandle, &BufferSize, File->Data);
  FileHandle->Close (FileHandle);
  if (EFI_ERROR (Status) || (BufferSize != FileSize)) {
    return EFI_LOAD_ERROR;
  }

  File->Size = BufferSize;
  return EFI_SUCCESS;
}

STATIC
VOID
FreePersistenceFiles (
  IN PERSISTENCE_FIXTURES  *Fixtures
  )
{
  UINTN  Index;

  for (Index = 0; Index < PersistenceFileCount; Index++) {
    if (Fixtures->Requests[Index].Data != NULL) {
      gtBS->FreePool (Fixtures->Requests[Index].Data);
    }
  }
}

STATIC
BOOLEAN
ValidPayload (
  IN PERSISTENCE_FILE  *File
  )
{
  EFI_SIGNATURE_LIST  Header;

  if (File->Size <= sizeof (Header) + sizeof (EFI_GUID)) {
    return FALSE;
  }

  SctCopyMem (&Header, File->Data, sizeof (Header));
  return (SctCompareMem (&Header.SignatureType, &mX509Guid, sizeof (EFI_GUID)) == 0) &&
         (Header.SignatureListSize == File->Size) &&
         (Header.SignatureHeaderSize == 0) &&
         (Header.SignatureSize == File->Size - sizeof (Header));
}

STATIC
UINT64
TimeValue (
  IN EFI_TIME  *Time
  )
{
  return SctLShiftU64 ((UINT64)Time->Year, 40) |
         SctLShiftU64 ((UINT64)Time->Month, 32) |
         SctLShiftU64 ((UINT64)Time->Day, 24) |
         SctLShiftU64 ((UINT64)Time->Hour, 16) |
         SctLShiftU64 ((UINT64)Time->Minute, 8) |
         Time->Second;
}

STATIC
BOOLEAN
ExtractRequestPayload (
  IN PERSISTENCE_FILE   *Request,
  OUT PERSISTENCE_FILE  *Payload,
  OUT EFI_TIME          *Time
  )
{
  EFI_VARIABLE_AUTHENTICATION_2  Header;
  UINTN                          HeaderSize;
  UINTN                          PayloadOffset;

  HeaderSize = sizeof (EFI_TIME) + OFFSET_OF (WIN_CERTIFICATE_UEFI_GUID, CertData);
  if (Request->Size < HeaderSize) {
    return FALSE;
  }

  SctZeroMem (&Header, sizeof (Header));
  SctCopyMem (&Header, Request->Data, HeaderSize);
  if ((Header.AuthInfo.Hdr.dwLength <= OFFSET_OF (WIN_CERTIFICATE_UEFI_GUID, CertData)) ||
      (Header.AuthInfo.Hdr.dwLength > Request->Size - sizeof (EFI_TIME)) ||
      (Header.AuthInfo.Hdr.wRevision != 0x0200) ||
      (Header.AuthInfo.Hdr.wCertificateType != WIN_CERT_TYPE_EFI_GUID) ||
      (SctCompareMem (&Header.AuthInfo.CertType, &mPkcs7Guid, sizeof (EFI_GUID)) != 0)) {
    return FALSE;
  }

  PayloadOffset = sizeof (EFI_TIME) + Header.AuthInfo.Hdr.dwLength;
  Payload->Data = (UINT8 *)Request->Data + PayloadOffset;
  Payload->Size = Request->Size - PayloadOffset;
  if (!ValidPayload (Payload)) {
    return FALSE;
  }

  *Time = Header.TimeStamp;
  return (Time->Year >= 1900) && (Time->Year <= 9999) &&
         (Time->Month >= 1) && (Time->Month <= 12) &&
         (Time->Day >= 1) && (Time->Day <= 31) &&
         (Time->Hour <= 23) && (Time->Minute <= 59) && (Time->Second <= 59) &&
         (Time->Pad1 == 0) && (Time->Nanosecond == 0) &&
         (Time->TimeZone == 0) && (Time->Daylight == 0) && (Time->Pad2 == 0);
}

STATIC
EFI_STATUS
LoadPersistenceFiles (
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  OUT PERSISTENCE_FIXTURES               *Fixtures,
  OUT PERSISTENCE_RECORD                 *Identity
  )
{
  EFI_STATUS        Status;
  UINTN             Index;
  EFI_TIME          T1;
  EFI_TIME          T2;
  EFI_TIME          T3;
  PERSISTENCE_FILE  T2Payload;

  SctZeroMem (Fixtures, sizeof (*Fixtures));
  SctZeroMem (Identity, sizeof (*Identity));
  Identity->Signature = mPersistenceSignature;
  Identity->Version = PERSISTENCE_VERSION;
  for (Index = 0; Index < PersistenceFileCount; Index++) {
    Status = LoadDependencyFile (mPersistenceFiles[Index], &Fixtures->Requests[Index]);
    if (EFI_ERROR (Status)) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Could not load %s: %r",
                     mPersistenceFiles[Index],
                     Status
                     );
      return Status;
    }

    Status = gtBS->CalculateCrc32 (
                     Fixtures->Requests[Index].Data,
                     Fixtures->Requests[Index].Size,
                     &Identity->FixtureCrc[Index]
                     );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  // Extract and validate the embedded ESLs before the first KEK write.
  // T1 supplies the expected TestKEK4 payload; T3 supplies TestKEK1 for both
  // the unsigned-update attempt and restoration. T2 must carry T1's payload.
  if (!ExtractRequestPayload (&Fixtures->Requests[Kek4T1], &Fixtures->Kek4Payload, &T1) ||
      !ExtractRequestPayload (&Fixtures->Requests[Kek4T2], &T2Payload, &T2) ||
      !ExtractRequestPayload (&Fixtures->Requests[Kek1T3], &Fixtures->Kek1Payload, &T3) ||
      (Fixtures->Kek4Payload.Size != T2Payload.Size) ||
      (SctCompareMem (Fixtures->Kek4Payload.Data, T2Payload.Data, T2Payload.Size) != 0) ||
      (TimeValue (&T1) >= TimeValue (&T2)) || (TimeValue (&T2) >= TimeValue (&T3))) {
    return EFI_COMPROMISED_DATA;
  }

  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
ValidateKek (
  IN EFI_RUNTIME_SERVICES                *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN PERSISTENCE_FILE                    *Expected,
  IN CHAR16                              *Operation OPTIONAL,
  OUT BOOLEAN                            *Mismatch OPTIONAL
  )
{
  EFI_STATUS  Status;
  UINT32      Attributes;
  VOID        *Data;
  UINTN       Size;
  UINTN       AllocatedSize;
  BOOLEAN     DataRead;

  Size = 0;
  Attributes = 0;
  Data = NULL;
  DataRead = FALSE;
  if (Mismatch != NULL) {
    *Mismatch = FALSE;
  }

  Status = RT->GetVariable (L"KEK", &gEfiGlobalVariableGuid, &Attributes, &Size, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    Status = EFI_ERROR (Status) ? Status : EFI_COMPROMISED_DATA;
    goto Exit;
  }

  AllocatedSize = Size;
  Data = SctAllocatePool (Size);
  if (Data == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }

  Status = RT->GetVariable (L"KEK", &gEfiGlobalVariableGuid, &Attributes, &Size, Data);
  if (!EFI_ERROR (Status)) {
    DataRead = TRUE;
    if ((Attributes != KEK_ATTRIBUTES) || (Size != Expected->Size) ||
        (Size > AllocatedSize) || (SctCompareMem (Data, Expected->Data, Size) != 0)) {
      Status = EFI_COMPROMISED_DATA;
      if (Mismatch != NULL) {
        // Report a confirmed mismatch only when GetVariable() returned
        // data within the allocated buffer.
        *Mismatch = (Size <= AllocatedSize);
      }
    }
  }

Exit:
  // A NULL operation suppresses the expected mismatch while probing whether
  // cleanup has already restored TestKEK1. All test checks name their stage.
  if (Operation != NULL) {
    if (!EFI_ERROR (Status)) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"%s: PASS (%d bytes, attributes=0x%08x)",
                     Operation,
                     Size,
                     Attributes
                     );
    } else if (DataRead) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"%s: FAIL; expected size=%d, attributes=0x%08x; "
                     L"actual size=%d, attributes=0x%08x; validation: %r "
                     L"(EFI_COMPROMISED_DATA - KEK payload or attributes differ)",
                     Operation,
                     Expected->Size,
                     KEK_ATTRIBUTES,
                     Size,
                     Attributes,
                     Status
                     );
    } else {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"%s: FAIL; could not retrieve KEK for comparison: %r",
                     Operation,
                     Status
                     );
    }
  }

  if (Data != NULL) {
    gtBS->FreePool (Data);
  }

  return Status;
}

STATIC
EFI_STATUS
SetKek (
  IN EFI_RUNTIME_SERVICES  *RT,
  IN PERSISTENCE_FILE      *File
  )
{
  return RT->SetVariable (
               L"KEK",
               &gEfiGlobalVariableGuid,
               KEK_ATTRIBUTES,
               File->Size,
               File->Data
               );
}

STATIC
EFI_STATUS
OpenPersistenceJournal (
  IN UINT64            Mode,
  OUT EFI_FILE_HANDLE  *Handle
  )
{
  EFI_FILE_HANDLE  Root;
  EFI_STATUS       Status;
  CHAR16           *Path;

  Root = SctOpenRoot (gDeviceHandle);
  if (Root == NULL) {
    return EFI_DEVICE_ERROR;
  }

  Path = SctPoolPrint (L"%s\\%s", gFilePath, PERSISTENCE_JOURNAL);
  if (Path == NULL) {
    Root->Close (Root);
    return EFI_OUT_OF_RESOURCES;
  }

  Status = Root->Open (Root, Handle, Path, Mode, 0);
  gtBS->FreePool (Path);
  Root->Close (Root);
  return Status;
}

STATIC
EFI_STATUS
ReadPersistenceJournal (
  OUT PERSISTENCE_RECORD  *Record
  )
{
  EFI_STATUS       Status;
  EFI_FILE_HANDLE  Handle;
  UINTN            Size;
  // An extra byte detects records larger than this version of the structure.
  UINT8            Buffer[sizeof (PERSISTENCE_RECORD) + 1];

  Status = OpenPersistenceJournal (EFI_FILE_MODE_READ, &Handle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Size = sizeof (Buffer);
  Status = Handle->Read (Handle, &Size, Buffer);
  Handle->Close (Handle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Size != sizeof (*Record)) {
    return EFI_COMPROMISED_DATA;
  }

  SctCopyMem (Record, Buffer, sizeof (*Record));
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
SavePersistenceRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_RECORD                  *Record
  )
{
  EFI_STATUS          Status;
  EFI_FILE_HANDLE     Handle;
  PERSISTENCE_RECORD  Saved;
  UINTN               Size;

  // SCT removes its shared reset file when a test returns. Keep a test-owned
  // journal as well, so a failed restoration remains recoverable on a rerun.
  Status = OpenPersistenceJournal (
             EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE | EFI_FILE_MODE_CREATE,
             &Handle
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Size = sizeof (*Record);
  Status = Handle->Write (Handle, &Size, Record);
  if (!EFI_ERROR (Status) && (Size != sizeof (*Record))) {
    Status = EFI_DEVICE_ERROR;
  }

  if (!EFI_ERROR (Status)) {
    Status = Handle->Flush (Handle);
  }

  Handle->Close (Handle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = ReadPersistenceJournal (&Saved);
  if (EFI_ERROR (Status) || (SctCompareMem (&Saved, Record, sizeof (Saved)) != 0)) {
    return EFI_DEVICE_ERROR;
  }

  return RecoveryLib->WriteResetRecord (RecoveryLib, sizeof (*Record), Record);
}

STATIC
EFI_STATUS
ClearPersistenceRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib
  )
{
  EFI_STATUS       Status;
  EFI_FILE_HANDLE  Handle;
  UINT8            EmptyRecord;
  UINT8            Buffer[RECOVERY_BUFFER_SIZE];
  UINTN            Size;

  // TrlWriteResetRecord deletes and recreates the file before writing. A zero
  // length write therefore leaves an empty file, which SCT treats as no state.
  EmptyRecord = 0;
  Status = RecoveryLib->WriteResetRecord (RecoveryLib, 0, &EmptyRecord);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Size = sizeof (Buffer);
  Status = RecoveryLib->ReadResetRecord (RecoveryLib, &Size, Buffer);
  if ((Status != EFI_NOT_FOUND) && (EFI_ERROR (Status) || (Size != 0))) {
    return EFI_ERROR (Status) ? Status : EFI_DEVICE_ERROR;
  }

  // Remove the durable journal last, after restoration and shared-state clear.
  Status = OpenPersistenceJournal (EFI_FILE_MODE_READ | EFI_FILE_MODE_WRITE, &Handle);
  if (Status == EFI_NOT_FOUND) {
    return EFI_SUCCESS;
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Handle->Delete (Handle);
  // Delete closes the handle even when it returns EFI_WARN_DELETE_FAILURE.
  return (Status == EFI_SUCCESS) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

STATIC
BOOLEAN
ValidPersistenceRecord (
  IN PERSISTENCE_RECORD  *Record,
  IN PERSISTENCE_RECORD  *Identity
  )
{
  return (SctCompareMem (&Record->Signature, &Identity->Signature, sizeof (EFI_GUID)) == 0) &&
         (Record->Version == PERSISTENCE_VERSION) &&
         ((Record->Stage == PERSISTENCE_STAGE_RESET) || (Record->Stage == PERSISTENCE_STAGE_CLEANUP)) &&
         (SctCompareMem (Record->FixtureCrc, Identity->FixtureCrc, sizeof (Record->FixtureCrc)) == 0);
}

STATIC
EFI_STATUS
ReadPersistenceRecord (
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_RECORD                  *Identity,
  OUT PERSISTENCE_RECORD                 *Record,
  OUT BOOLEAN                            *Found
  )
{
  EFI_STATUS          Status;
  BOOLEAN             SharedFound;
  UINT8               Buffer[RECOVERY_BUFFER_SIZE];
  UINTN               Size;
  PERSISTENCE_RECORD  Journal;

  *Found = FALSE;
  Size = sizeof (Buffer);
  Status = RecoveryLib->ReadResetRecord (RecoveryLib, &Size, Buffer);
  SharedFound = (Status == EFI_SUCCESS) && (Size != 0);
  if ((Status != EFI_NOT_FOUND) && EFI_ERROR (Status)) {
    return Status;
  }

  if (SharedFound) {
    if (Size != sizeof (*Record)) {
      return EFI_COMPROMISED_DATA;
    }

    SctCopyMem (Record, Buffer, sizeof (*Record));
    if (!ValidPersistenceRecord (Record, Identity)) {
      return EFI_COMPROMISED_DATA;
    }
  }

  Status = ReadPersistenceJournal (&Journal);
  if ((Status == EFI_NOT_FOUND) && !SharedFound) {
    return EFI_SUCCESS;
  }

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (!ValidPersistenceRecord (&Journal, Identity)) {
    return EFI_COMPROMISED_DATA;
  }

  // Only SCT's reset record permits resuming checks after a cold reset.
  // Journal writes precede shared-record writes. A stage mismatch means an
  // interrupted save, so allow cleanup but never resume the test checks.
  if (!SharedFound || (Record->Stage != Journal.Stage)) {
    Journal.Stage = PERSISTENCE_STAGE_CLEANUP;
  }

  *Record = Journal;
  *Found = TRUE;
  return EFI_SUCCESS;
}

STATIC
EFI_STATUS
RestoreKekAndClearRecord (
  IN EFI_RUNTIME_SERVICES                *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_FIXTURES                *Fixtures
  )
{
  EFI_STATUS  Status;
  BOOLEAN     Mismatch;

  // A previous T3 write may have succeeded before reset or a clear failure.
  // In that case, verify the restored KEK instead of replaying T3.
  Status = ValidateKek (RT, StandardLib, &Fixtures->Kek1Payload, NULL, &Mismatch);
  if (EFI_ERROR (Status)) {
    // Restore a confirmed mismatch or missing KEK. A read/allocation failure
    // leaves the current state unknown, even if GetVariable returned
    // EFI_COMPROMISED_DATA, so retain recovery state without attempting T3.
    if (!Mismatch && (Status != EFI_NOT_FOUND)) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"Could not inspect KEK before restoration: %r; "
                     L"T3 not attempted; retaining cleanup journal.",
                     Status
                     );
      return Status;
    }

    Status = SetKek (RT, &Fixtures->Requests[Kek1T3]);
    if (Status != EFI_SUCCESS) {
      StandardLib->RecordMessage (
                     StandardLib,
                     EFI_VERBOSE_LEVEL_DEFAULT,
                     L"TestKEK1 restoration at T3 failed: %r; retaining cleanup journal.",
                     Status
                     );
      return EFI_ERROR (Status) ? Status : EFI_DEVICE_ERROR;
    }

    Status = ValidateKek (
               RT,
               StandardLib,
               &Fixtures->Kek1Payload,
               L"T3 KEK restoration (TestKEK1)",
               NULL
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"KEK restoration: PASS (TestKEK1 already present; T3 not replayed)"
                   );
  }

  Status = ClearPersistenceRecord (RecoveryLib);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Recovery state cleanup: %s (%r)",
                 EFI_ERROR (Status) ? L"FAIL" : L"PASS",
                 Status
                 );
  return Status;
}

STATIC
EFI_STATUS
CleanupAndRecordFailure (
  IN EFI_RUNTIME_SERVICES                *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_FIXTURES                *Fixtures,
  IN PERSISTENCE_RECORD                  *Record,
  IN EFI_GUID                            AssertionGuid,
  IN CHAR16                              *Detail,
  IN UINTN                               LineNumber
  )
{
  EFI_STATUS  Status;

  (VOID)RecordPersistenceAssertion (
          StandardLib,
          AssertionGuid,
          EFI_TEST_ASSERTION_FAILED,
          Detail,
          LineNumber
          );
  Record->Stage = PERSISTENCE_STAGE_CLEANUP;
  Status = SavePersistenceRecord (RecoveryLib, Record);
  if (EFI_ERROR (Status)) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"Could not save cleanup stage: %r; retaining existing journal.",
                   Status
                   );
  }

  Status = RestoreKekAndClearRecord (RT, StandardLib, RecoveryLib, Fixtures);
  if (EFI_ERROR (Status)) {
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
            EFI_TEST_ASSERTION_FAILED,
            L"KEK restoration or recovery-state cleanup failed; retry cleanup with the same fixtures.",
            (UINTN)__LINE__
            );
  }

  return EFI_DEVICE_ERROR;
}

STATIC
EFI_STATUS
SecureBootAuthVariablePersistenceStart (
  IN EFI_RUNTIME_SERVICES                *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_FIXTURES                *Fixtures,
  IN PERSISTENCE_RECORD                  *Record
  )
{
  EFI_STATUS  Status;
  EFI_STATUS  ReadStatus;
  CHAR16      *Failure;

  // This test restores the enrolled test KEK, so require that baseline first.
  Status = ValidateKek (
             RT,
             StandardLib,
             &Fixtures->Kek1Payload,
             L"Initial KEK (TestKEK1)",
             NULL
             );
  if (EFI_ERROR (Status)) {
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            gSecureBootAuthVariablePersistenceBbTestAssertionGuid001,
            EFI_TEST_ASSERTION_FAILED,
            L"Initial KEK must match the TestKEK1 payload embedded in T3 and the expected attributes.",
            (UINTN)__LINE__
            );
    return Status;
  }

  // Journal cleanup intent before any firmware mutation. The reset stage is
  // written only after T1 and the unsigned-update checks have all succeeded.
  Record->Stage = PERSISTENCE_STAGE_CLEANUP;
  Status = SavePersistenceRecord (RecoveryLib, Record);
  if (EFI_ERROR (Status)) {
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
            EFI_TEST_ASSERTION_FAILED,
            L"Could not save cleanup intent before modifying KEK.",
            (UINTN)__LINE__
            );
    return Status;
  }

  Failure = L"Could not install TestKEK4 with the PK-signed T1 request.";
  Status = SetKek (RT, &Fixtures->Requests[Kek4T1]);
  if (Status != EFI_SUCCESS) {
    StandardLib->RecordMessage (
                   StandardLib,
                   EFI_VERBOSE_LEVEL_DEFAULT,
                   L"T1 authenticated KEK update failed: %r",
                   Status
                   );
    goto Failed;
  }

  Failure = L"KEK payload or attributes differ after installing TestKEK4 at T1.";
  Status = ValidateKek (
             RT,
             StandardLib,
             &Fixtures->Kek4Payload,
             L"T1 authenticated KEK update (TestKEK4)",
             NULL
             );
  if (EFI_ERROR (Status)) {
    goto Failed;
  }

  // Submit a different, unsigned ESL with the authenticated KEK attributes.
  // Check both the rejection status and the unchanged KEK value/attributes.
  Status = SetKek (RT, &Fixtures->Kek1Payload);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"Unsigned KEK update: %r (%s)",
                 Status,
                 (Status == EFI_SECURITY_VIOLATION) ?
                   L"EFI_SECURITY_VIOLATION - Expected" : L"Unexpected status"
                 );
  ReadStatus = ValidateKek (
                 RT,
                 StandardLib,
                 &Fixtures->Kek4Payload,
                 L"KEK unchanged after unsigned-update attempt (TestKEK4)",
                 NULL
                 );
  Failure = L"Unsigned KEK update was not rejected with EFI_SECURITY_VIOLATION or changed KEK.";
  if ((Status != EFI_SECURITY_VIOLATION) || EFI_ERROR (ReadStatus)) {
    goto Failed;
  }

  Record->Stage = PERSISTENCE_STAGE_RESET;
  Status = SavePersistenceRecord (RecoveryLib, Record);
  Failure = L"Could not save persistence state before cold reset.";
  if (EFI_ERROR (Status)) {
    goto Failed;
  }

  SctPrint (L"System will cold reset to verify KEK persistence.\n");
  gtBS->Stall (1000000);
  RT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
  Failure = L"ResetSystem returned unexpectedly.";

Failed:
  return CleanupAndRecordFailure (
           RT,
           StandardLib,
           RecoveryLib,
           Fixtures,
           Record,
           gSecureBootAuthVariablePersistenceBbTestAssertionGuid001,
           Failure,
           (UINTN)__LINE__
           );
}

STATIC
EFI_STATUS
SecureBootAuthVariablePersistenceRecover (
  IN EFI_RUNTIME_SERVICES                *RT,
  IN EFI_STANDARD_TEST_LIBRARY_PROTOCOL  *StandardLib,
  IN EFI_TEST_RECOVERY_LIBRARY_PROTOCOL  *RecoveryLib,
  IN PERSISTENCE_FIXTURES                *Fixtures,
  IN PERSISTENCE_RECORD                  *Record
  )
{
  EFI_STATUS  Status;
  EFI_STATUS  ReadStatus;
  EFI_GUID    AssertionGuid;
  CHAR16      *Failure;

  if (Record->Stage == PERSISTENCE_STAGE_CLEANUP) {
    return CleanupAndRecordFailure (
             RT,
             StandardLib,
             RecoveryLib,
             Fixtures,
             Record,
             gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
             L"An interrupted or failed persistence run requires cleanup; this run cannot pass.",
             (UINTN)__LINE__
             );
  }

  // Consume the reset stage before further checks. An interruption from here
  // must retry cleanup, rather than replay an incomplete sequence as a PASS.
  Record->Stage = PERSISTENCE_STAGE_CLEANUP;
  Status = SavePersistenceRecord (RecoveryLib, Record);
  AssertionGuid = gSecureBootAuthVariablePersistenceBbTestAssertionGuid001;
  Failure = L"Could not save cleanup intent after reset.";
  if (EFI_ERROR (Status)) {
    goto Failed;
  }

  Failure = L"KEK persistence validation failed after cold reset; expected TestKEK4 payload and attributes.";
  Status = ValidateKek (
             RT,
             StandardLib,
             &Fixtures->Kek4Payload,
             L"KEK persistence across cold reset (TestKEK4)",
             NULL
             );
  if (EFI_ERROR (Status)) {
    goto Failed;
  }

  AssertionGuid = gSecureBootAuthVariablePersistenceBbTestAssertionGuid002;
  Status = SetKek (RT, &Fixtures->Requests[Kek4T1]);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"T1 replay: %r (%s)",
                 Status,
                 (Status == EFI_SECURITY_VIOLATION) ?
                   L"EFI_SECURITY_VIOLATION - Expected" : L"Unexpected status"
                 );
  ReadStatus = ValidateKek (
                 RT,
                 StandardLib,
                 &Fixtures->Kek4Payload,
                 L"KEK unchanged after T1 replay (TestKEK4)",
                 NULL
                 );
  Failure = L"T1 replay was not rejected with EFI_SECURITY_VIOLATION or changed KEK.";
  if ((Status != EFI_SECURITY_VIOLATION) || EFI_ERROR (ReadStatus)) {
    goto Failed;
  }

  AssertionGuid = gSecureBootAuthVariablePersistenceBbTestAssertionGuid003;
  Status = SetKek (RT, &Fixtures->Requests[Kek4T2]);
  StandardLib->RecordMessage (
                 StandardLib,
                 EFI_VERBOSE_LEVEL_DEFAULT,
                 L"T2 authenticated KEK update: %r (%s)",
                 Status,
                 (Status == EFI_SUCCESS) ? L"EFI_SUCCESS - Expected" : L"Unexpected status"
                 );
  ReadStatus = ValidateKek (
                 RT,
                 StandardLib,
                 &Fixtures->Kek4Payload,
                 L"KEK payload verification after T2 attempt (TestKEK4)",
                 NULL
                 );
  Failure = L"Newer T2 update was not accepted or left incorrect KEK payload/attributes.";
  if ((Status != EFI_SUCCESS) || EFI_ERROR (ReadStatus)) {
    goto Failed;
  }

  AssertionGuid = gSecureBootAuthVariablePersistenceBbTestAssertionGuid004;
  Failure = L"T3 restoration or recovery-state cleanup failed; retaining the cleanup journal.";
  Status = RestoreKekAndClearRecord (RT, StandardLib, RecoveryLib, Fixtures);
  if (EFI_ERROR (Status)) {
    // Leave cleanup state intact. A rerun can validate an already applied T3.
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            AssertionGuid,
            EFI_TEST_ASSERTION_FAILED,
            Failure,
            (UINTN)__LINE__
            );
    return Status;
  }

  // Defer every PASS until all checks, T3 restoration, and clearing succeed.
  (VOID)RecordPersistenceAssertion (
          StandardLib,
          gSecureBootAuthVariablePersistenceBbTestAssertionGuid001,
          EFI_TEST_ASSERTION_PASSED,
          L"KEK payload/attributes persisted across cold reset after unsigned-update rejection.",
          (UINTN)__LINE__
          );
  (VOID)RecordPersistenceAssertion (
          StandardLib,
          gSecureBootAuthVariablePersistenceBbTestAssertionGuid002,
          EFI_TEST_ASSERTION_PASSED,
          L"Authenticated T1 replay was rejected and KEK remained unchanged.",
          (UINTN)__LINE__
          );
  (VOID)RecordPersistenceAssertion (
          StandardLib,
          gSecureBootAuthVariablePersistenceBbTestAssertionGuid003,
          EFI_TEST_ASSERTION_PASSED,
          L"Newer authenticated T2 update succeeded with the expected KEK payload and attributes.",
          (UINTN)__LINE__
          );
  return RecordPersistenceAssertion (
           StandardLib,
           gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
           EFI_TEST_ASSERTION_PASSED,
           L"TestKEK1 restoration was verified and all recovery state cleared.",
           (UINTN)__LINE__
           );

Failed:
  return CleanupAndRecordFailure (
           RT,
           StandardLib,
           RecoveryLib,
           Fixtures,
           Record,
           AssertionGuid,
           Failure,
           (UINTN)__LINE__
           );
}

EFI_STATUS
SecureBootAuthVariablePersistenceTest (
  IN EFI_BB_TEST_PROTOCOL  *This,
  IN VOID                  *ClientInterface,
  IN EFI_TEST_LEVEL        TestLevel,
  IN EFI_HANDLE            SupportHandle
  )
{
  EFI_STATUS                            Status;
  EFI_RUNTIME_SERVICES                  *RT;
  EFI_STANDARD_TEST_LIBRARY_PROTOCOL     *StandardLib;
  EFI_TEST_RECOVERY_LIBRARY_PROTOCOL     *RecoveryLib;
  EFI_TEST_PROFILE_LIBRARY_PROTOCOL     *ProfileLib;
  EFI_TEST_LOGGING_LIBRARY_PROTOCOL      *LoggingLib;
  PERSISTENCE_FIXTURES                   Fixtures;
  PERSISTENCE_RECORD                     Identity;
  PERSISTENCE_RECORD                     Record;
  BOOLEAN                               Found;

  Status = GetTestSupportLibrary (SupportHandle, &StandardLib, &ProfileLib, &LoggingLib);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gtBS->HandleProtocol (
                   SupportHandle,
                   &gEfiTestRecoveryLibraryGuid,
                   (VOID **)&RecoveryLib
                   );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (FALSE == CheckBBTestCanRunAndRecordAssertion (
                  StandardLib,
                  L"Secure Boot authenticated KEK persistence test not supported in EFI",
                  __FILE__,
                  (UINTN)__LINE__
                  )) {
    return EFI_SUCCESS;
  }

  if (LoggingLib != NULL) {
    LoggingLib->EnterFunction (
                  LoggingLib,
                  L"SecureBootAuthVariablePersistenceTest",
                  L"PK-authenticated KEK updates, rejection, persistence, and restoration"
                  );
  }

  RT = (EFI_RUNTIME_SERVICES *)ClientInterface;
  SctZeroMem (&Fixtures, sizeof (Fixtures));
  Status = GetSystemData (ProfileLib);
  if (!EFI_ERROR (Status)) {
    Status = LoadPersistenceFiles (StandardLib, &Fixtures, &Identity);
  }

  if (EFI_ERROR (Status)) {
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            gSecureBootAuthVariablePersistenceBbTestAssertionGuid001,
            EFI_TEST_ASSERTION_FAILED,
            L"Could not load/validate all persistence dependencies; KEK and recovery state left untouched.",
            (UINTN)__LINE__
            );
    goto Exit;
  }

  Status = ReadPersistenceRecord (RecoveryLib, &Identity, &Record, &Found);
  if (EFI_ERROR (Status)) {
    // A shared, foreign, stale, or unreadable record is never proof that this
    // test modified KEK. Preserve it and do not attempt Secure Boot cleanup.
    (VOID)RecordPersistenceAssertion (
            StandardLib,
            gSecureBootAuthVariablePersistenceBbTestAssertionGuid004,
            EFI_TEST_ASSERTION_FAILED,
            L"Unrecognized/unreadable recovery state or changed fixtures; KEK and records left untouched.",
            (UINTN)__LINE__
            );
    goto Exit;
  }

  if (Found) {
    Status = SecureBootAuthVariablePersistenceRecover (RT, StandardLib, RecoveryLib, &Fixtures, &Record);
  } else {
    Record = Identity;
    Status = SecureBootAuthVariablePersistenceStart (RT, StandardLib, RecoveryLib, &Fixtures, &Record);
  }

Exit:
  FreePersistenceFiles (&Fixtures);
  if (LoggingLib != NULL) {
    LoggingLib->ExitFunction (
                  LoggingLib,
                  L"SecureBootAuthVariablePersistenceTest",
                  L"PK-authenticated KEK updates, rejection, persistence, and restoration"
                  );
  }

  return Status;
}
