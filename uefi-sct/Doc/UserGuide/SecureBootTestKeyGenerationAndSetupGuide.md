# Secure Boot Test Key Generation Guide - AARCH64 (Linux)

Secure Boot is a key security mechanism that ensures a system boots only with firmware, operating systems, and drivers that are verified and trusted by the Original Equipment Manufacturer (OEM). It is designed to prevent the execution of unauthorized or malicious code during the boot process.

- `Note:`
  - This project is currently in its initial development phase, with a focus exclusively on scenarios where Secure Boot is enabled. The existing test cases are intended to fail if Secure Boot is not active.
    - Example: SecureBoot - VariableAttributesBBTest: SecureBoot not enabled  
  - In the upcoming phase, we plan to introduce additional test cases that will evaluate UEFI Secure Boot behavior when the system is not in Secure Boot mode.

## Core Features of Secure Boot

- **Code Signing:** Uses public/private key cryptography.
- **Certificate Validation:** Verifies firmware and software components using certificates.
- **Policy Enforcement:** Prevents execution of unsigned or tampered code.
- **Key Hierarchy:**
  - **PK (Platform Key):** Top-level trust anchor; authorizes changes to KEK.
  - **KEK (Key Exchange Key):** Manages updates to DB and DBX.
  - **DB (Database of Allowed Signatures):** Stores trusted certificates and hashes.
  - **DBX (Forbidden Signature Database):** Stores blacklisted certificates and hashes.

## Supported Secure Boot Test Case

### 1. `ImageLoadingTest`
- Validates image authentication and signature mechanisms during UEFI boot.
- Ensures that only images signed per platform policy are allowed to load.

### 2. `VariableAttributes`
- Validates the attributes (e.g., non-volatile, authenticated write access) of critical Secure Boot variables: PK, KEK, db, dbx.

### 3. `VariableUpdates`
- Tests runtime update paths for Secure Boot variables to ensure UEFI-enforced access control policies are in place.

---

## Pre-requisites

### 1. Required Tools
The following tools are required to generate and manage Secure Boot keys and certificates:
- openssl: For key and certificate generation.
- sbsigntool: For signing EFI binaries.
- efitools: For managing EFI signatures and keys.

- Note: These instructions are specific to Debian-based distributions (e.g., Ubuntu). They may not work as-is on OpenBSD, SUSE, or other non-Debian systems.

### 2. Install Required Tools (Ubuntu/Debian)

Before installing packages, make sure your package list is up to date:

```bash
sudo apt-get update
sudo apt-get install openssl sbsigntool efitools
```

---

### 4. Generate or Provide Secure Boot Keys

You can either use existing Secure Boot keys or generate new ones using `openssl`. The following keys and certificates are required:

- `TestPK1.key`, `TestPK1.crt`
- `TestKEK1.key`, `TestKEK1.crt`
- `TestDB1.key`, `TestDB1.crt`
- `TestDBX1.key`, `TestDBX1.crt`

#### Key Pair Creation

```bash
openssl req -new -x509 -newkey rsa:2048 -subj "/CN=PK1/" -keyout TestPK1.key -out TestPK1.crt -days 3650 -nodes -sha256
openssl req -new -x509 -newkey rsa:2048 -subj "/CN=KEK1/" -keyout TestKEK1.key -out TestKEK1.crt -days 3650 -nodes -sha256
openssl req -new -x509 -newkey rsa:2048 -subj "/CN=DB_Key1/" -keyout TestDB1.key -out TestDB1.crt -days 3650 -nodes -sha256
openssl req -new -x509 -newkey rsa:2048 -subj "/CN=DBX_Key1/" -keyout TestDBX1.key -out TestDBX1.crt -days 3650 -nodes -sha256
```

#### Convert crt certificate to der format

```bash
openssl x509 -in TestPK1.crt -outform der -out TestPK1.der
openssl x509 -in TestKEK1.crt -outform der -out TestKEK1.der
openssl x509 -in TestDB1.crt -outform der -out TestDB1.der
openssl x509 -in TestDBX1.crt -outform der -out TestDBX1.der
```
---

---

### 5. Set the Secure Boot Keys Directory

Set the environment variable `KEYS_DIR` to the path where your keys are stored:

```bash
export KEYS_DIR=~/secureboot-keys
```

Ensure that the `secureboot-keys` directory contains the following files:

- `TestPK1.key`, `TestPK1.crt`, `TestPk1.der`
- `TestKEK1.key`, `TestKEK1.crt`, `TestKEK1.der`
- `TestDB1.key`, `TestDB1.crt`, `TestDB1.der`
- `TestDBX1.key`, `TestDBX1.crt`, `TestDBX1.der`
