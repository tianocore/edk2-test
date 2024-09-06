# EFI Compliance Test

## EFI Requirements Test

**Reference Document:**

*UEFI Specification,* Requirements Section.

Configuration

Configuration is a checkpoint in the EFI Requirements Test. If the you
need to check the platform-specific protocols, the related profile needs
to be updated.

For the correct formatting of profiles, refer to Appendix section A.1,
EFI Requirements Test Profile.

### Required Elements

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
<col style="width: 27%" />
<col style="width: 43%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.22.1.1.1</td>
<td>0xf6a871e3, 0xef8a, 0x420f, 0x82, 0x01, 0x35, 0xb6, 0x1c, 0xe2,
0xe8, 0xdb</td>
<td>EFI-Compliant - EFI System Table must be implemented.</td>
<td><p>1. The <em>Signature</em> of EFI System Table should be
0x5453595320494249.</p>
<p>2. The <em>Revision</em> of EFI System Table should be equal to or
larger than 0x00020000.</p>
<p>3. The <em>Reserved</em> field in EFI System Table should be 0.</p>
<p>4. The <em>RuntimeServices</em> and <em>BootServices</em> pointers of
EFI System Table should not be <strong>NULL</strong>.</p>
<p>5. The <em>CRC32</em> of EFI System Table must be correct.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.1.2</td>
<td>0xaddab6ed, 0x5a17, 0x4327, 0x8f, 0xb1, 0x72, 0x93, 0x3d, 0x1a,
0x7b, 0xba</td>
<td>EFI-Compliant - EFI Boot Services Table must be implemented.</td>
<td><p>1. The <em>Signature</em> of EFI Boot Services Table should be
0x56524553544f4f42.</p>
<p>2. The <em>Revision</em> of EFI Boot Services Table should be equal
to or larger than 0x00020000.</p>
<p>3. The <em>Reserved</em> field in EFI Boot Services Table should be
0.</p>
<p>4. No function pointers in EFI Boot Services Table should be
<strong>NULL</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.1.3</td>
<td>0x13a20958, 0xc860, 0x452f, 0xb9, 0xa2, 0xe6, 0xd9, 0x96, 0x41,
0x92, 0x24</td>
<td>EFI-Compliant - EFI Runtime Services Table must be implemented.</td>
<td><p>1. The <em>Signature</em> of EFI Runtime Services Table should be
0x56524553544e5552.</p>
<p>2. The <em>Revision</em> of EFI Runtime Services Table should be
equal to or larger than 0x00020000.</p>
<p>3. The <em>Reserved</em> field in EFI Runtime Services Table should
be 0.</p>
<p>4. No function pointers in EFI Runtime Services Table should be
<strong>NULL</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.1.4</td>
<td>0xa82f8d56, 0x1476, 0x41f1, 0xba, 0xc4, 0x97, 0x59, 0x79, 0x9f,
0x97, 0xf3</td>
<td>EFI-Compliant –<strong>EFI_LOADED_IMAGE_PROTOCOL</strong> must
exist.</td>
<td>1. Call <strong>LocateProtocol()</strong> to find the
<strong>LOADED_IMAGE_PROTOCOL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.22.1.1.5</td>
<td>0xf61f0f0a, 0x64fe, 0x40a6, 0x9d, 0x7c, 0x07, 0x46, 0xa2, 0x30,
0x24, 0x5f</td>
<td>EFI-Compliant –<strong>EFI_DEVICE_PATH_PROTOCOL</strong> must
exist.</td>
<td>1. Call <strong>LocateProtocol()</strong> to find the
<strong>DEVICE_PATH_PROTOCOL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.22.1.1.6</td>
<td>0x02c017d7, 0x1557, 0x47d9, 0xbc, 0xe9, 0x87, 0x18, 0x2d, 0x07,
0x91, 0x0c</td>
<td>EFI-Compliant –<strong>EFI_DECOMPRESS_PROTOCOL</strong> must
exist.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>DECOMPRESS_PROTOCOL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. No function pointers in <strong>DECOMPRESS_PROTOCOL</strong>
should be <strong>NULL</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.1.7</td>
<td>0x3a07dc1b, 0x53d1, 0x4fac, 0x88, 0xaf, 0xc7, 0x25, 0x79, 0xeb,
0x07, 0xf2</td>
<td>UEFI-Compliant<strong>-EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>
must exist</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>, the return status
should be <strong>EFI_SUCCESS</strong></p>
<p>2. No function pointer in <strong>Device</strong>
<strong>Path</strong> <strong>Utility</strong> protocol should be
<strong>NULL</strong></p></td>
</tr>
<tr class="odd">
<td>5.22.1.1.8</td>
<td>0xf6334f9b, 0xb930, 0x4adb, 0xa5, 0x3b, 0x76, 0xfa, 0x7b, 0x4c,
0x27, 0x62</td>
<td><p>UEFI-Compliant</p>
<p>The <strong>EFI_GLOBAL_VARIABLE</strong> guid should be used by the
globally defined variables only, and the attributes of the variables
should be same with the definition in the Specification.</p></td>
<td><p>1. Locate all variables with <strong>EFI_GLOBAL_VARIABLE</strong>
guid, check the variable name is in the pre-defined globally variable
list.</p>
<p>2. Check the variable attribute.</p></td>
</tr>
</tbody>
</table>


### Platform-Specific Elements

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 13%" />
<col style="width: 27%" />
<col style="width: 43%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.22.1.2.1</td>
<td>0x8f7556c2, 0x4665, 0x4353, 0xa3, 0xaf, 0x9c, 0x00, 0x5a, 0x1e,
0x63, 0xe1</td>
<td>EFI-Compliant - <strong>EFI_SIMPLE_ TEXT_INPUT_PROTOCOL,</strong>
<strong>EFI_SIMPLE_ TEXT_INPUT_EX_PROTOCOL</strong> and
<strong>EFI_SIMPLE_TEXT_OUT_PROTOCOL</strong> must be implemented if a
platform includes console devices.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SIMPLE_ TEXT_INPUT_PROTOCOL</strong>.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL</strong>.</p>
<p>3. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SIMPLE_TEXT_OUT_PROTOCOL</strong>.</p>
<p>4. If the INI file indicates that the platform includes console
devices, the return status in steps 1, 2 and 3 should be
<strong>EFI_SUCCESS</strong>. If not, the return status in steps 1, 2
and 3 should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.2</td>
<td>0x72ba0e86, 0x58e5, 0x48dd, 0x85, 0x29, 0x88, 0xc6, 0x83, 0x83,
0x11, 0x8d</td>
<td>UEFI-Compliant - <strong>EFI_GRAPHICS_OUTPUT_PROTOCOL</strong>,
<strong>EFI_EDID_ACTIVE_PROTOCOL, EFI_EDID_DISCOVERED_PROTOCOL</strong>
must be implemented if a platform includes graphical console
devices.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_GRAPHICS_OUTPUT_PROTOCOL</strong></p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_EDID_ACTIVE_PROTOCOL</strong>. <strong>,</strong></p>
<p>3. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_EDID_DISCOVERED_PROTOCOL.</strong></p>
<p>4. If the INI file indicates that the platform includes graphical
console devices, the return status in all steps 1, 2 and 3 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. If the INI file doesn’t indicate that the platform includes
graphical console devices, the return status in all steps 1, 2 and 3
could be either <strong>EFI_SUCCESS</strong> or
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.3</td>
<td>0x18670db1, 0x89fb, 0x4de4, 0xb1, 0x0f, 0x89, 0x8e, 0x04, 0x7d,
0x95, 0x2a</td>
<td>UEFI-Compliant –<strong>EFI_SIMPLE_POINTER_PROTOCOL</strong> must be
implemented if a platform includes a pointer device as part of its
console support.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SIMPLE_POINTER_PROTOCOL</strong>.</p>
<p>2. If the INI file indicates that the platform includes a pointer
device, the return status in step 1 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If the INI file doesn’t indicate that the platform includes a
pointer device, the return status in step 1 could be either
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.4</td>
<td>0xbf38a3fd, 0x58ac, 0x419a, 0xab, 0xc2, 0xc6, 0x0b, 0xae, 0x9c,
0xfe, 0x67</td>
<td>UEFI-Compliant –<strong>EFI_BLOCK_IO_PROTOCOL</strong>,
<strong>EFI_DISK_IO_PROTOCOL</strong>,
<strong>EFI_SIMPLE_FILE_SYSTEM</strong>;
<strong>EFI_UNICODE_COLLATION_PROTOCOL</strong> must be implemented if a
platform supports booting from a disk.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_BLOCK_IO_PROTOCOL</strong> protocol.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_DISK_IO_PROTOCOL</strong>.</p>
<p>3. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SIMPLE_FILE_SYSTEM_PROTOCOL</strong>.</p>
<p>4. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_UNICODE_COLLATION_PROTOCOL</strong>.</p>
<p>5. If the INI file indicates that the platform supports booting from
a disk, the return status in steps 1, 2, 3, and 4 all should be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. If the INI file doesn’t indicate that the platform supports
booting from a disk, the return status in steps 1, 2, 3, and 4 all
should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.5</td>
<td>0x98551ae7, 0x5020, 0x4ddd, 0x86, 0x1a, 0xcf, 0xff, 0xb4, 0xd6,
0x03, 0x82</td>
<td><p>UEFI-Compliant –
EFI_PXE_BASE_CODE_PROTOCOL must be implemented if a platform supports
TFTP-based booting from a network device. And platform must be prepared
to produce this protocol on any of
EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL (UNDI),</p>
<p><strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong>, or the
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong>. If platform supports
validating the image received from network device,
<strong>SetupMode</strong> equal zero.</p></td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_PXE_BASE_CODE_PROTOCOL</strong></p><p>
2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_NETWORK_INTERFACE_IDENTIFIER_PROTOCOL</strong>,
<strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong>,
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong></p><p>
3. If the INI file indicates that the platform
supports TFTP-based booting from a network device, the return status in
step 1 should be <strong>EFI_SUCCESS</strong>. And one of the step 2
should be <strong>EFI_SUCCESS</strong> at least</p><p>
4. If the INI file doesn’t indicate that the
platform supports TFTP-based booting from a network device, the return
status in both step 1
and step 2 step should be <strong>EFI_SUCCESS
</strong>or <strong>EFI_ERROR</strong></p><p>
5. If the INI file indicates that the platform
supports validating the image received
from a network device, <strong>SetupMode</strong> equal zero.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.6</td>
<td>0x517bcbeb, 0x4982, 0x4a7e, 0x85, 0x51, 0xca, 0x84, 0x7d, 0xdc,
0x21, 0xc2</td>
<td>UEFI-Compliant –<strong>EFI_SERIAL_IO_PROTOCOL</strong> must be
implemented if a platform includes a byte stream device.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SERIAL_IO_PROTOCOL</strong>.</p>
<p>2. If the INI file indicates that the platform includes a byte-stream
device, the return status in step 1 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If the INI file doesn’t indicate that the platform includes a
byte-stream device, the return status in step 1 step could be either
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.7</td>
<td>0x213a75c9, 0x7f3d, 0x42db, 0xb3, 0x2a, 0x02, 0xdb, 0xd6, 0x98,
0x31, 0x9d</td>
<td>UEFI-Compliant –<strong>EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL</strong> and
<strong>EFI_PCI_IO_PROTOCOL</strong> must be implemented if a platform
includes PCI bus support.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_PCI_ROOT_BRIDGE_IO</strong> <strong>_PROTOCOL</strong>.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_PCI_IO_PROTOCOL</strong>.</p>
<p>3. If the INI file indicates that the platform includes PCI bus
support, the return status in both steps 1 and 2 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. If the INI file doesn’t indicate that the platform includes PCI
bus support, the return status in both steps 1 and 2 steps could be
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.8</td>
<td>0x0ccd5843, 0x5bb5, 0x4fc2, 0xa7, 0x32, 0xdb, 0x17, 0xc4, 0x14,
0xa4, 0x3d</td>
<td>UEFI-Compliant –<strong>EFI_USB_HC2_PROTOCOL</strong> and
<strong>EFI_USB_IO_PROTOCOL</strong> must be implemented if a platform
includes USB bus support.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_USB_HC2_PROTOCOL</strong>.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_USB_IO_PROTOCOL</strong>.</p>
<p>3. If INI file indicates the platform includes USB bus support, the
return status in 1 and 2 steps should be both
<strong>EFI_SUCCESS</strong>.</p>
<p>4. If INI file doesn’t indicate the platform includes USB bus
support, the return status in 1 and 2 steps should be both
<strong>EFI_SUCCESS</strong> or both
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.9</td>
<td>0x2b83418f, 0xe7fb, 0x4528, 0xb6, 0xff, 0xc9, 0xd4, 0x87, 0xae,
0x2e, 0xff</td>
<td>UEFI-Compliant –<strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL</strong>
must be implemented if a platform includes an I/O system that uses SCSI
command packets.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL</strong>.</p>
<p>2. If INI file indicates the platform includes an I/O system that
uses SCSI command packets, the return status in 1 step should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If INI file doesn’t indicate the platform includes an I/O system
that uses SCSI command packets, the return status in 1 step could be
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.10</td>
<td>0x3ee22696, 0x0875, 0x46f4, 0x88, 0x84, 0xba, 0x12, 0x4c, 0x7e,
0xaf, 0xf0</td>
<td>UEFI-Compliant –<strong>EFI_DEBUG_SUPPORT_PROTOCOL</strong> and
<strong>EFI_DEBUG_PORT_PROTOCOL</strong> must be implemented if a
platform supports debugging capabilities.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_DEBUG_SUPPORT_PROTOCOL</strong>.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_DEBUG_PORT_PROTOCOL</strong>.</p>
<p>3. If INI file indicates the platform supports debugging
capabilities, the return status in 1 and 2 steps should be both
<strong>EFI_SUCCESS</strong>.</p>
<p>4. If INI file doesn’t indicate the platform supports debugging
capabilities, the return status in 1 and 2 steps should be both
<strong>EFI_SUCCESS</strong> or both
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.11</td>
<td>0x329027ce, 0x406e, 0x48c8, 0x8a, 0xc1, 0xa0, 0x2c, 0x1a, 0x6e,
0x39, 0x83</td>
<td>UEFI-Compliant
–<strong>EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL</strong> must be
implemented if a platform includes the ability to override the default
driver.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL</strong>.</p>
<p>2. If INI file indicates the platform includes the ability to
override the default driver, the return status in 1 step should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If INI file doesn’t indicate the platform includes the ability to
override the default driver, the return status in 1 step could be
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.12</td>
<td>0x76a6a1b0, 0x8c53, 0x407d, 0x84, 0x86, 0x9a, 0x6e, 0x63, 0x32,
0xd3, 0xce</td>
<td>UEFI-Compliant –
<strong>EFI_MANAGED_NETWOR
K_PROTOCOL</strong>,
<strong>EFI_MANAGED_NETWOR
K_SERVICE_BINDING_
PROTOCOL,
EFI_ARP_PROTOCOL,
EFI_ARP_SERVICE_BI
NDING_PROTOCOL,
EFI_DHCP4_PROTOCOL,<br/>
EFI_DHCP4_SERVICE_
BINDING_PROTOCOL,
EFI_TCP4_PROTOCOL,
EFI_TCP4_SERVICE_B
INDING_PROTOCOL,
EFI_IP4_PROTOCOL,<br/>
EFI_IP4_SERVICE_BINDING_PROTOCOL,
EFI_IP4_CONFIG2_PROTOCOL,
EFI_UDP4_PROTOCOL,
EFI_UDP4_SERVICE_B
INDING_PROTOCOL,
EFI_MTFTP4_PROTOCO
L,</strong> and
<strong>EFI_MTFTP4_SERVICE
_BINIING_PROTOCOL
</strong>are required for general
network application</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong>,
<strong>EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL,</strong>
<strong>EFI_ARP_PROTOCOL,
EFI_ARP_SERVICE_BINDING_PROTOCOL, EFI_DHCP4_PROTOCOL,<br/>
EFI_DHCP4_SERVICE_BINDING_PROT
OCOL, EFI_TCP4_PROTOCOL,
EFI_TCP4_SERVICE_BINDING_PROTO
COL, EFI_IP4_PROTOCOL,<br/>
EFI_IP4_SERVICE_BINDING_PROTOC
OL, EFI_IP4_CONFIG2_PROTOCOL,
EFI_UDP4_PROTOCOL,
EFI_UDP4_SERVICE_BINDING_PROTO
COL, EFI_MTFTP4_PROTOCOL,</strong> and
<strong>EFI_MTFTP4_SERVICE_BINIING_PRO
TOCOL
</strong></p><p>2. If INI file indicates the platform includes
the ability to general network application,
the return status for locating all protocols
described in step 1 should be <strong>EFI_SUCCESS
</strong><p>3. If INI file doesn’t indicate the platform
includes the ability for general network
application, the return status for locating
all protocols described in step 1 could</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.13</td>
<td>0x28c068f2, 0xf398, 0x488a, 0xb0, 0x59, 0x53, 0x4e, 0x98, 0x2d,
0x9c, 0x85</td>
<td>UEFI-Compliant –<strong>EFI_SCSI IO_PROTOCOL,</strong>
<strong>EFI_Block</strong> <strong>IO_PROTOCOL</strong> and
<strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL</strong> must be implemented if
a platform supports booting from a SCSI peripheral device.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_SCSI IO_PROTOCOL</strong>.</p>
<p>2. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_Block</strong> <strong>IO_PROTOCOL</strong> protocol.</p>
<p>3. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL</strong>.</p>
<p>4. If the INI file indicates that the platform supports booting from
a network device, the return status in all steps 1, 2 and 3 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. If the INI file doesn’t indicate that the platform supports
booting from a network device, the return status in all steps 1, 2 and 3
should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.14</td>
<td>0x6b7077a6, 0x4b13, 0x4e13, 0x9b, 0x1f, 0x0c, 0x4b, 0x3a, 0x86,
0x69, 0xe2</td>
<td>UEFI-Compliant –
<strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL</strong> and
<strong>EFI_AUTHENTICATION_INFO_PROTOCOL
</strong>must be implemented if a platform supports booting from a
ISCSI
peripheral device.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_ISCSI_INITIATOR_NAME_PROTO
COL</strong> and
<strong>EFI_AUTHENTICATION_INFO_PROTOCOL</strong></p><p>
2. If the INI file indicates that the platform
supports booting from a iSCSI peripheral,
the return status in both steps 1 should be
<strong>EFI_SUCCESS</strong></p><p>
3. If the INI file doesn’t indicate that the
platform supports booting from iSCSI peripheral, the return status in
steps 1 should
be <strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.15</td>
<td>0x4c82eb2d, 0xc785, 0x410c, 0x95, 0xd1, 0xae, 0x27, 0x12, 0x21,
0x44, 0xc8</td>
<td>UEFI Compliant –UEFI V6 General Network Driver <strong>Dhcp6SB,
Tcp6SB, Ip6SB, Udp6SB, Ip6Config, Vlan</strong> must exist if a platform
supports V6 network stack</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the V6 network
stack.</p>
<p>2. If the INI file indicates that the platform supports v6 stack</p>
<p>, the return status in step 1 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If the INI file doesn’t indicate that the platform supports v6
network stack, the return status in steps1 should be
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.16</td>
<td>0x1d0a2f2a, 0x924, 0x4b8c, 0x9f, 0xc7, 0xb1, 0x85, 0xcc, 0x22, 0xe1,
0x18</td>
<td>UEFI Compliant –UEFI EBC interpreter must exist if a platform
supports EBC image</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find the
<strong>EFI_EBC_PROTOCOL</strong>.</p>
<p>2. If the INI file indicates that the platform supports EBC image</p>
<p>, the return status in step 1 should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. If the INI file doesn’t indicate that the platform supports EBC
image, the return status in step 1 should be
<strong>EFI_SUCCESS</strong> or <strong>EFI_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.17</td>
<td><p>0xb7cd2d76, 0xea43, 0x4013, 0xb7, 0xd1, 0x59, 0xeb, 0x2e,
0xc9,</p>
<p>0xbf, 0x1b</p></td>
<td>UEFI Compliant –UEFI <strong>HiiDatabase, HiiString,
HiiConfigRouting, HiiConfigAccess</strong> must be existed if the
platform supports HII. If it supports bitmapped fonts, then
<strong>HiiFont</strong> must exist also.</td>
<td><p>1. Call <strong>LocateProtocol()</strong> to find
<strong>HiiDatabase, HiiString, HiiConfigRouting,
HiiConfigAccess</strong>.</p>
<p>2. If the INI file indicates that the platform supports HII all
return statuses in step 1 should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. If the INI file doesn’t indicate that the platform supports HII,
the return status in step1 should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_ERROR</strong>.</p>
<p>4. If step 2 is true, and the INI file indicates the platform support
bitmapped font, call <strong>LocateProtocol()</strong> to find
<strong>HiiFont,</strong> and the return status should
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.18</td>
<td><p>0x5aea7246, 0xbcf9,</p>
<p>0x4ba4, 0x81, 0xd2, 0x83, 0x2c, 0x98, 0x41, 0x46, 0xf3</p></td>
<td><p>UEFI-Compliant –
</p>
<p>EFI_NVM_EXPRESS
_PASS_THRU_PROTOCOL
must be implemented if a platform includes an NVM Express
controller</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL</p><p>
2. If the INI file indicates that the platform </p>
<p>includes an NVM Express controller, the return status in steps 1
should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate that the platform includes an NVM
Express controller, the return status in steps 1 should be EFI_SUCCESS
or EFI_ERROR.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.19</td>
<td>0x5cb0cdb5, 0xac80, 0x4983, 0xb7, 0x10, 0x4b, 0xb, 0xf0, 0x19, 0x15,
0x63</td>
<td><p>UEFI Compliant –
</p>
<p>EFI_BLOCK_IO_PROTOCOL must be existed if the platform supports
booting from a block-oriented NVM Express controller.
EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL may be required.</p></td>
<td><p>1. Call LocateProtocol() to find EFI_BLOCK_IO_PROTOCOL</p><p>
2. If the INI file indicates that the platform supports </p>
<p>booting from a block-oriented NVM Express controller, all return
statuses in step 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate that the platform supports booting
from a block-oriented NVM Express controller, the return status in step1
should be EFI_SUCCESS or EFI_ERROR</p><p>
4. If step 2 is true, and the INI file indicates the platform support
EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL, call LocateProtocol() to find it,
and the return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.20</td>
<td>0x563f654f, 0xaba8, 0x4539, 0x80, 0x4b, 0x50, 0x63, 0x5, 0x7, 0x26,
0x23</td>
<td><p>UEFI-Compliant –
</p>
<p>EFI_ATA_PASS_THRU_PROTOCOL must be implemented if a platform</p>
<p>includes an I/O subsystem that utilizes ATA command packets.</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_ATA_PASS_THRU_PROTOCOL</p><p>
2. If the INI file indicates that the platform includes an I/O subsystem
that utilizes ATA command packets, the return status in steps 1 should
be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate that the platform includes an I/O
subsystem that utilizes ATA command packets, the return status in steps
1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.21</td>
<td>0x2e6d1733, 0x6d39, 0x49ab, 0xa8, 0x86, 0x1b, 0x6d, 0xe4, 0x45,
0x66, 0xa8</td>
<td><p>UEFI Compliant –
</p>
<p>EFI_DNS4_PROTOCOL, EFI_DNS4_SERVICE_BINDING_PROTOCOL must be existed
if the platform supports DNS for IPv4 stack.</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_DNS4_PROTOCOL and EFI_DNS4_SERVICE_BINDING_PROTOCOL</p><p>
2. If the INI file indicates that the platform supports DNS for IPv4
stack, the return status in steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.22</td>
<td>0xe02a6ef3, 0x4b70, 0x40ec, 0xaa, 0x23, 0x50, 0xb7, 0xb9, 0x72,
0xb0, 0x65</td>
<td><p>UEFI Compliant –
</p>
<p>EFI_DNS6_PROTOCOL, EFI_DNS6_SERVICE_BINDING_PROTOCOL must be existed
if the platform supports DNS for IPv6 stack.</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_DNS6_PROTOCOL and EFI_DNS6_SERVICE_BINDING_PROTOCOL</p><p>
2. If the INI file indicates that the platform supports DNS for IPv6
stack, the return status in steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.23</td>
<td>0xcb6f7b77, 0xb15, 0x43f7, 0xa9, 0x5b, 0x8c, 0x7f, 0x9f, 0xd7, 0xb,
0x21</td>
<td>UEFI Compliant –
EFI_TLS_PROTOCOL, EFI_TLS_SERVICE_BINDING_PROTOCOL,
EFI_TLS_CONFIGURATION_PROTOCOL must be existed if the platform supports
TLS feature.</td>
<td><p>1. Call LocateProtocol() to find the
EFI_TLS_PROTOCOL, EFI_TLS_SERVICE_BINDING_PROTOCOL and
EFI_TLS_CONFIGURATION_PROTOCOL</p><p>
2. If the INI file indicates that the platform supports TLS feature, the
return status in steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.24</td>
<td>0x77fddb95, 0x5969, 0x4fb4, 0xa2, 0x18, 0x5c, 0xc, 0x76, 0xb, 0x5,
0x64</td>
<td><p>UEFI Compliant –
</p>
<p>EFI_HTTP_PROTOCOL, EFI_HTTP_SERVICE_BINDING_PROTOCOL,
EFI_HTTP_UTILITIES_PROTOCOL must be existed if the platform includes the
ability to perform a HTTP-based boot from a network device.</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_HTTP_PROTOCOL, EFI_HTTP_SERVICE_BINDING_PROTOCOL and EFI_HTTP_
UTILITIES_PROTOCOL</p><p>
2. If the INI file indicates that the platform includes the ability to
perform a HTTP-based boot from a network device, the return status in
steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="even">
<td>5.22.1.2.25</td>
<td><p>0xf0dc12</p>
<p>fa, 0x3c4b, 0x43f7, 0xa6, 0x9e, 0xa5, 0xbe, 0x6f, 0xcc, 0x90,
0xa1</p></td>
<td><p>UEFI Compliant –
</p>
<p>EFI_EAP_PROTOCOL, EFI_EAP_CONFIGURATION_PROTOCOL,
EFI_EAP_MANAGEMENT2_PROTOCOL must be existed if the platform includes
the ability to perform a wireless boot from a network device with EAP
feature, and if this platform provides a standalone wireless EAP
driver.</p></td>
<td><p>1. Call LocateProtocol() to find the
EFI_EAP_PROTOCOL, EFI_EAP_CONFIGURATION_PROTOCOL and
EFI_EAP_MANAGEMENT2_PROTOCOL</p><p>
2. If the INI file indicates that the platform includes the ability to
perform a wireless boot from a network device with EAP feature, and if
this platform provides a standalone wireless EAP driver, the return
status in steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
<tr class="odd">
<td>5.22.1.2.26</td>
<td>0x87e50392, 0xf5a2, 0x42b8, 0x81, 0x12, 0x68, 0xbe, 0xc9, 0x2, 0xb9,
0xbc</td>
<td><p>UEFI Compliant –
</p>
<p>EFI_BLUETOOTH_HC_PROTOCOL, EFI_</p>
<p>BLUETOOTH_IO_PROTOCOL, EFI_BLUETOOTH_CONFIG_PROTOCOL must be existed
if the platform supports classic Bluetooth.</p></td>
<td><p>1. Call LocateProtocol() to find the
UEFI Compliant –UEFI
EFI_BLUETOOTH_HC_PROTOCOL, EFI_BLUETOOTH_IO_PROTOCOL and
EFI_BLUETOOTH_CONFIG_PROTOCOL</p><p>
2. If the INI file indicates that the platform supports classic
Bluetooth, the return status in steps 1 should be EFI_SUCCESS</p><p>
3. If the INI file doesn’t indicate this capability, the return status
in steps 1 should be EFI_SUCCESS or EFI_ERROR.</p></td>
</tr>
</tbody>
</table>
