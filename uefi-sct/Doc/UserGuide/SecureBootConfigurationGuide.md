
# Enrolling and Disabling Secure Boot Keys on EDK2-Based UEFI Firmware

This guide outlines the steps for enrolling and disabling Secure Boot keys using UEFI firmware based on EDK2.

## Requirements

- A UEFI firmware implementation based on EDK2
- Secure Boot keys including:
  - Platform Key (PK)
  - Key Exchange Key (KEK)
  - Signature Database (db)
  - Forbidden Signature Database (dbx)
- For instructions on generating and setting up these keys, refer to:
  - `uefi-sct/Doc/UserGuide/SecureBootTestKeyGenerationAndSetupGuide.md`

## Enrolling Secure Boot Keys

1. **Access the UEFI Setup Utility**
   - During system boot, press the designated key (e.g., `Esc`, `Del`, `F2`) to enter the firmware setup.

2. **Open the Security or Boot Configuration Menu**
   - Use arrow keys to navigate.
   - Look for sections such as `Boot Manager`, `Device Manager`, `Security`, or `Advanced`.

3. **Locate Secure Boot Settings**
   - Find the `Secure Boot Configuration` section.
   - This may be under `Device Manager` or a specific `Secure Boot` menu.

4. **Proceed with Key Enrollment**
   - Follow platform-specific procedures to load PK, KEK, db, and dbx.
   - Example: For Raspberry Pi, refer to the section “Enrolling Secure Boot Keys on Raspberry Pi Using UEFI Firmware.”

5. **Save and Exit**
   - Press `F10` or follow on-screen instructions to save changes.
   - Confirm if prompted.

6. **Reboot the System**

7. **Verify Secure Boot Status**
   - Boot into the UEFI shell and run:
     ```
     setvar SecureBoot
     ```
   - Output `1` confirms Secure Boot is active.

## Disabling Secure Boot

1. **Reboot the Machine**

2. **Enter UEFI Setup Utility**
   - Press the designated key (e.g., `Esc`, `Del`, `F2`) during startup.

3. **Open the Boot or Security Menu**
   - Navigate using arrow keys.
   - Look under `Boot Manager`, `Device Manager`, `Security`, or `Advanced`.

4. **Access Secure Boot Options**
   - Locate `Secure Boot Configuration`.

5. **Disable Secure Boot**
   - Change the `Secure Boot` setting to `Disabled`.

6. **Remove Secure Boot Keys**
   - Open the key management section.
   - Choose to delete PK, KEK, db, and dbx.
   - Example: See “Clearing Secure Boot Keys on Raspberry Pi Using UEFI Firmware.”

7. **Save and Exit**
   - Use `F10` or other instructions to save and reboot.

8. **Confirm Secure Boot is Disabled**
   - From the UEFI shell, run:
     ```
     setvar SecureBoot
     ```
   - Output `0` means Secure Boot is disabled.

## Managing Secure Boot Keys on Raspberry Pi (UEFI Firmware)

### Enrolling Secure Boot Keys

1. Go to `Device Manager → Secure Boot Configuration → Secure Boot Mode`
2. Select `Custom mode` and press `Enter`
3. Enter `Custom Secure Boot Options`
4. Enroll the `dbx` key:
   - Navigate: `DBX Options → Enroll Signature → Enroll Signature Using File`
   - Choose: `NO VOLUME LABEL → EFI → BOOT → DBX.der`
5. Select `Commit Changes and Exit`
6. Repeat similar steps for:
   - `db`: `DB Options → enroll DB.der`
   - `kek`: `KEK Options → enroll KEK.der`
   - `pk`: `PK Options → enroll PK.der`

### Clearing Secure Boot Keys

1. Go to `Device Manager → Secure Boot Configuration → Secure Boot Mode`
2. Set mode to `Custom`, press `Enter`
3. Enter `Custom Secure Boot Options`
4. For each key:
   - `dbx`: `DBX Options → Delete Signature`
   - `db`: `DB Options → delete DB.der`
   - `kek`: `KEK Options → delete KEK.der`
   - `pk`: `PK Options → delete PK.der`

