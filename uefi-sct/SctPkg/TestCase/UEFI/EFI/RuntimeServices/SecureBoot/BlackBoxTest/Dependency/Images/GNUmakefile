## @file
#
#  Copyright 2006 - 2012 Unified EFI, Inc.<BR>
#  Copyright (c) 2025, Arm Ltd. All rights reserved.<BR>
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at 
#  http://opensource.org/licenses/bsd-license.php
# 
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
# 
##
#/*++
#
# Module Name:
#
#   makefile
#
# Abstract:
#
#   This is the makefile for creating a private/public keypair for Secure Boot testing.
#
#--*/

BASE_NAME=SecureBoot
TARGET=$(BIN_DIR)/$(BASE_NAME)
# Date string 5 years in the future (used for long-term key validity)
FUTURE_DATE=$(shell date --rfc-3339=date -d "+5 year")
# Date string 1 day in the future
FUTURE_DATE2=$(shell date --rfc-3339=date -d "+1 day")
# Date string 2 days in the future
FUTURE_DATE3=$(shell date --rfc-3339=date -d "+2 day")
# Date string 3 days in the future
FUTURE_DATE4=$(shell date --rfc-3339=date -d "+3 day")
# Date string 1 year in the past (used to simulate expired keys or legacy signatures)
PAST_DATE=$(shell date --rfc-3339=date -d "-1 year")

ifdef KEYS_DIR
$(info Using KEYS_DIR: $(KEYS_DIR))
TEST_PK1_CRT=$(KEYS_DIR)/TestPK1.crt
TEST_PK1_KEY=$(KEYS_DIR)/TestPK1.key
TEST_KEK1_CRT=$(KEYS_DIR)/TestKEK1.crt
TEST_KEK1_KEY=$(KEYS_DIR)/TestKEK1.key
TEST_DB1_CRT=$(KEYS_DIR)/TestDB1.crt
TEST_DB1_KEY=$(KEYS_DIR)/TestDB1.key
TEST_DBX1_CRT=$(KEYS_DIR)/TestDBX1.crt
TEST_DBX1_KEY=$(KEYS_DIR)/TestDBX1.key
else
$(warning [WARN] KEYS_DIR is not set. Please provide KEYS_DIR=<path> when invoking make.)
exit 0;
endif

# Build all required certificates, signature lists, images, and .auth files for Secureboot test scenarios
all: TestKEK2 TestKEK3 KEKSigList1.auth KEKSigList3.auth TestImage1.bin TestImage2.bin TestImage3.bin TestImage4.bin TestImage5.bin TestImage6.bin TestImage7.bin TestImage8.bin TestImage9.bin TestImage10.bin NullKEK.auth NullDB.auth NullDBX.auth TestKEK1.auth TestDB1.auth TestDBX1.auth SignCert1 dbSigList1.auth SignCert2 SignCert3 SignCert4 SignCert5 RevokedCert1 RevokedCert2 RevokedCert3 RevokedCert4 dbSigList2.auth dbSigList3.auth dbSigList4.auth dbxRevokedList1.auth dbSigList5.auth unsignedKeyUpdate Image19ACert Image19BCert TestImage19.bin Image20ACert Image20BCert TestImage20.bin Image19BCert.auth

#Image that is not signed
TestImage1.bin:
	cp $(BIN_DIR)/SampleAppForSecureBootTest1.efi $(TARGET)_$(@)

#Image that is signed with SignCert1, but certificate is not in the db variable
TestImage2.bin: SignCert1
	cp $(BIN_DIR)/SampleAppForSecureBootTest1.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_SignCert1.key --cert $(TARGET)_SignCert1.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with SignCert2 in the first signature list
TestImage3.bin: SignCert2
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_SignCert2.key --cert $(TARGET)_SignCert2.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with SignCert3 in the second signature list
TestImage4.bin: SignCert3
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_SignCert3.key --cert $(TARGET)_SignCert3.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is not signed but hash in list
TestImage5.bin:
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)

#Image that is signed with RevokedCert1 with signature in db but revoked in dbx with SHA256 of cert
TestImage6.bin: RevokedCert1
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_RevokedCert1.key --cert $(TARGET)_RevokedCert1.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with RevokedCert2 with signature in db but revoked in dbx with SHA384 of cert
TestImage7.bin: RevokedCert2
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_RevokedCert2.key --cert $(TARGET)_RevokedCert2.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with RevokedCert3 with signature in db but revoked in dbx with SHA512 of cert
TestImage8.bin: RevokedCert3
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_RevokedCert3.key --cert $(TARGET)_RevokedCert3.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with RevokedCert4 with signature in db but revoked in dbx with cert
TestImage9.bin: RevokedCert4
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_RevokedCert4.key --cert $(TARGET)_RevokedCert4.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with SignCert3 with signature in db but revoked with SHA256 hash of image in DBXRevokedList1
TestImage10.bin: SignCert3
	cp $(BIN_DIR)/SampleAppForSecureBootTest3.efi $(TARGET)_Unsigned_$(@).tmp
	cp $(BIN_DIR)/SampleAppForSecureBootTest3.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_SignCert3.key --cert $(TARGET)_SignCert3.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with Image19ACert and Image19BCert, test with each certificate in db
TestImage19.bin: Image19ACert Image19BCert
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_Image19ACert.key --cert $(TARGET)_Image19ACert.crt $(TARGET)_$(@) --output $(TARGET)_$(@)
	sbsign --key $(TARGET)_Image19BCert.key --cert $(TARGET)_Image19BCert.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

#Image that is signed with Image20ACert and Image20BCert, with Image20ACert in db and revoked in dbx with SHA256 of Image20BCert
TestImage20.bin: Image20ACert Image20BCert
	cp $(BIN_DIR)/SampleAppForSecureBootTest2.efi $(TARGET)_$(@)
	sbsign --key $(TARGET)_Image20ACert.key --cert $(TARGET)_Image20ACert.crt $(TARGET)_$(@) --output $(TARGET)_$(@)
	sbsign --key $(TARGET)_Image20BCert.key --cert $(TARGET)_Image20BCert.crt $(TARGET)_$(@) --output $(TARGET)_$(@)

# Generate a new RSA KEK certificate (KEK2) with a long validity
TestKEK2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_KEK2/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate a new RSA KEK certificate (KEK3) with a long validity
TestKEK3:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_TEST_KEK3/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 1 for TestImage2
SignCert1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert1/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 2 for TestImage3
SignCert2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert2/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 3 for TestImage4
SignCert3:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert3/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 4 for dbSigList4.auth
SignCert4:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert4/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 5 for dbSigList5.auth
SignCert5:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_SignCert5/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate Revoked certificate 1 for TestImage6
RevokedCert1:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert1/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate Revoked certificate 2 for TestImage7
RevokedCert2:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert2/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate Revoked certificate 3 for TestImage8
RevokedCert3:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert3/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate Revoked certificate 4 for TestImage9
RevokedCert4:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_RevokedCert4/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 19A for TestImage19
Image19ACert:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_Image19ACert/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 19B for TestImage19
Image19BCert:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_Image19BCert/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 20A for TestImage20
Image20ACert:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_Image20ACert/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Generate certificate 20B for TestImage20
Image20BCert:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_Image20BCert/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000

# Create a KEK signature list containing KEK1 and KEK2 certificates and sign it
KEKSigList1.auth: TestKEK2
	cert-to-efi-sig-list $(TEST_KEK1_CRT) $(BIN_DIR)/SecureBoot_TestKEK1.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestKEK2.crt $(BIN_DIR)/SecureBoot_TestKEK2.esl
	cat $(BIN_DIR)/SecureBoot_TestKEK1.esl $(BIN_DIR)/SecureBoot_TestKEK2.esl > $(BIN_DIR)/SecureBoot_KEKSigList1.esl
	sign-efi-sig-list -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_KEKSigList1.esl $(BIN_DIR)/SecureBoot_KEKSigList1.auth

# Create an empty KEK list (used to clear KEK variable)
NullKEK.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullKEK.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_NullKEK.esl $(BIN_DIR)/SecureBoot_NullKEK.auth

# Used to delete the test keys in db by setting an empty signature list
NullDB.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullDB.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_NullDB.esl $(BIN_DIR)/SecureBoot_NullDB.auth

# Create an empty dbx list (used to clear revoked keys list)
NullDBX.auth:
	cat /dev/null > $(BIN_DIR)/SecureBoot_NullDBX.esl
	sign-efi-sig-list -t $(FUTURE_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) dbx $(BIN_DIR)/SecureBoot_NullDBX.esl $(BIN_DIR)/SecureBoot_NullDBX.auth

# Create KEK1 authenticated update from certificate
# Timestamp is in the past so KEK1 can be deleted
TestKEK1.auth:
	cert-to-efi-sig-list $(TEST_KEK1_CRT) $(BIN_DIR)/SecureBoot_TestKEK1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_TestKEK1.esl $(BIN_DIR)/SecureBoot_TestKEK1.auth

# Create db1 authenticated update certificate
TestDB1.auth:
	cert-to-efi-sig-list $(TEST_DB1_CRT) $(BIN_DIR)/SecureBoot_TestDB1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_TestDB1.esl $(BIN_DIR)/SecureBoot_TestDB1.auth

# Create dbx authenticated update from certificate
TestDBX1.auth:
	cert-to-efi-sig-list $(TEST_DBX1_CRT) $(BIN_DIR)/SecureBoot_TestDBX1.esl
	sign-efi-sig-list -t $(PAST_DATE) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) dbx $(BIN_DIR)/SecureBoot_TestDBX1.esl $(BIN_DIR)/SecureBoot_TestDBX1.auth

# Generate a signed KEK list (KEKSigList3.auth) using PK1 credentials and KEK3 certificate
KEKSigList3.auth: TestKEK3
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestKEK3.crt $(BIN_DIR)/SecureBoot_KEKSigList3.esl
	sign-efi-sig-list -a -t $(FUTURE_DATE2) -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) KEK $(BIN_DIR)/SecureBoot_KEKSigList3.esl $(BIN_DIR)/SecureBoot_KEKSigList3.auth

# Generate a signed db signature list using PK1 credentials and SignCert1
dbSigList1.auth: SignCert1
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert1.crt $(BIN_DIR)/SecureBoot_TestDB1.esl
	sign-efi-sig-list -c $(TEST_PK1_CRT) -k $(TEST_PK1_KEY) db $(BIN_DIR)/SecureBoot_TestDB1.esl $(BIN_DIR)/SecureBoot_DBSigList1.auth

# Generate a combined db signature list from multiple certs and one hash
dbSigListLong: SignCert2 SignCert3 RevokedCert1 RevokedCert2 RevokedCert3 RevokedCert4 TestImage5.bin Image19ACert Image20ACert
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-000000000002 $(BIN_DIR)/SecureBoot_SignCert2.crt $(BIN_DIR)/SecureBoot_TestDB2.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-000000000003 $(BIN_DIR)/SecureBoot_SignCert3.crt $(BIN_DIR)/SecureBoot_TestDB3.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C1 $(BIN_DIR)/SecureBoot_RevokedCert1.crt $(BIN_DIR)/SecureBoot_TestDB4.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C2 $(BIN_DIR)/SecureBoot_RevokedCert2.crt $(BIN_DIR)/SecureBoot_TestDB5.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C3 $(BIN_DIR)/SecureBoot_RevokedCert3.crt $(BIN_DIR)/SecureBoot_TestDB6.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C4 $(BIN_DIR)/SecureBoot_RevokedCert4.crt $(BIN_DIR)/SecureBoot_TestDB7.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C4 $(BIN_DIR)/SecureBoot_Image19ACert.crt $(BIN_DIR)/SecureBoot_Image19ACert.esl
	cert-to-efi-sig-list -g 11111111-2222-3333-4444-0000000000C4 $(BIN_DIR)/SecureBoot_Image20ACert.crt $(BIN_DIR)/SecureBoot_Image20ACert.esl
	hash-to-efi-sig-list $(BIN_DIR)/SecureBoot_TestImage5.bin $(BIN_DIR)/SecureBoot_Hash1.esl
	cat $(BIN_DIR)/SecureBoot_TestDB2.esl $(BIN_DIR)/SecureBoot_TestDB3.esl $(BIN_DIR)/SecureBoot_TestDB4.esl $(BIN_DIR)/SecureBoot_TestDB5.esl $(BIN_DIR)/SecureBoot_TestDB6.esl  $(BIN_DIR)/SecureBoot_TestDB7.esl $(BIN_DIR)/SecureBoot_Image19ACert.esl $(BIN_DIR)/SecureBoot_Image20ACert.esl $(BIN_DIR)/SecureBoot_Hash1.esl  > $(BIN_DIR)/SecureBoot_DBSigListLong.esl

# Sign the long db signature list to create db authenticated update
dbSigList2.auth: dbSigListLong
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE2)" db $(BIN_DIR)/SecureBoot_DBSigListLong.esl $(BIN_DIR)/SecureBoot_DBSigList2.auth

# Sign a long db signature list to create dbx authenticated update
dbSigList3.auth: dbSigListLong
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE2)" dbx $(BIN_DIR)/SecureBoot_DBSigListLong.esl $(BIN_DIR)/SecureBoot_DBSigList3.auth

# Convert SignCert4 to ESL and sign it using KEK2 to generate a db4 long list
dbSigList4.auth: SignCert4
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert4.crt $(BIN_DIR)/SecureBoot_TestDB9.esl
	sign-efi-sig-list -c $(BIN_DIR)/SecureBoot_TestKEK2.crt -k $(BIN_DIR)/SecureBoot_TestKEK2.key -t "$(FUTURE_DATE3)" db $(BIN_DIR)/SecureBoot_TestDB9.esl $(BIN_DIR)/SecureBoot_DBSigList4.auth

# Create dbx revoked list from cert hashes and one binary hash
dbxRevokedList1.auth: RevokedCert1 RevokedCert2 RevokedCert3 RevokedCert4 TestImage10.bin Image20BCert
	cert-to-efi-hash-list -s 256 $(BIN_DIR)/SecureBoot_RevokedCert1.crt $(BIN_DIR)/SecureBoot_RevokedCert1.esl
	cert-to-efi-hash-list -s 384 $(BIN_DIR)/SecureBoot_RevokedCert2.crt $(BIN_DIR)/SecureBoot_RevokedCert2.esl
	cert-to-efi-hash-list -s 512 $(BIN_DIR)/SecureBoot_RevokedCert3.crt $(BIN_DIR)/SecureBoot_RevokedCert3.esl
	cert-to-efi-hash-list -s 256 $(BIN_DIR)/SecureBoot_Image20BCert.crt $(BIN_DIR)/SecureBoot_Image20BCert.esl
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_RevokedCert4.crt $(BIN_DIR)/SecureBoot_RevokedCert4.esl
	hash-to-efi-sig-list $(BIN_DIR)/SecureBoot_Unsigned_TestImage10.bin.tmp $(BIN_DIR)/SecureBoot_RevokedHash1.esl
	cat $(BIN_DIR)/SecureBoot_RevokedCert1.esl $(BIN_DIR)/SecureBoot_RevokedCert2.esl $(BIN_DIR)/SecureBoot_RevokedCert3.esl  $(BIN_DIR)/SecureBoot_RevokedCert4.esl $(BIN_DIR)/SecureBoot_RevokedHash1.esl $(BIN_DIR)/SecureBoot_Image20BCert.esl > $(BIN_DIR)/SecureBoot_dbxRevokedList1.esl
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE2)" dbx $(BIN_DIR)/SecureBoot_dbxRevokedList1.esl $(BIN_DIR)/SecureBoot_dbxRevokedList1.auth

# Convert SignCert5 to ESL and sign it using KEK3 (with append flag) to generate a db5 long lis
dbSigList5.auth: SignCert5
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_SignCert5.crt $(BIN_DIR)/SecureBoot_TestDB10.esl
	sign-efi-sig-list -a -c $(BIN_DIR)/SecureBoot_TestKEK3.crt -k $(BIN_DIR)/SecureBoot_TestKEK3.key -t "$(FUTURE_DATE4)" db $(BIN_DIR)/SecureBoot_TestDB10.esl $(BIN_DIR)/SecureBoot_DBSigList5.auth

# Generate and sign Image19B certificate for db entry
Image19BCert.auth: Image19BCert
	cert-to-efi-sig-list $(BIN_DIR)/SecureBoot_Image19BCert.crt $(BIN_DIR)/SecureBoot_Image19BCert.esl
	sign-efi-sig-list -c $(TEST_KEK1_CRT) -k $(TEST_KEK1_KEY) -t "$(FUTURE_DATE3)" db $(BIN_DIR)/SecureBoot_Image19BCert.esl $(BIN_DIR)/SecureBoot_Image19BCert.auth

# Generate an unsigned certificate and export it as .auth without signing (for negative test case)
unsignedKeyUpdate:
	openssl req -x509 -sha256 -newkey rsa:2048 -subj /CN=ACS_UNSIGNED_KEY/ -keyout $(TARGET)_$(@).key -out $(TARGET)_$(@).crt -nodes -days 4000
	cert-to-efi-sig-list $(TARGET)_$(@).crt $(TARGET)_$(@).esl
	# exporting a .auth file without signing it with PK or KEK for testing purposes
	mv $(TARGET)_$(@).esl $(TARGET)_$(@).auth

clean:
	$(RM) $(BIN_DIR)/$(TARGET)_*.key
	$(RM) $(BIN_DIR)/$(TARGET)_*.crt
	$(RM) $(BIN_DIR)/$(TARGET)_*.der
