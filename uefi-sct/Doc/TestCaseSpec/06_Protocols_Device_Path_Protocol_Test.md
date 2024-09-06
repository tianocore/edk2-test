# Protocols Device Path Protocol Test

## Device Path Node Conformance Test

**Reference Document:**

*UEFI Specification*, Device Path Nodes Section.

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 17%" />
<col style="width: 32%" />
<col style="width: 34%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.1.1.1</td>
<td>0x91064ab1, 0x5408, 0x48c1, 0xbb, 0xd9, 0x2a, 0x49, 0xee, 0xe2,
0x1d, 0xc9</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check End of Hardware
Device Path - End This Device Path.</td>
<td>Verify the device path nodes. Type: 0x7F or 0xFF. Sub-Type: 0xFF.
Length: 4 bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.2</td>
<td>0xb5a0ee55, 0x0070, 0x472d, 0x84, 0xcd, 0xbc, 0xb1, 0xe2, 0xbc,
0x25, 0xc0</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Hardware Device
Path - PCI Device Path.</td>
<td>Verify the device path nodes. Type: 1.Sub-Type: 1.Length: 6
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.3</td>
<td>0x2902b389, 0xe4e7, 0x43cd, 0x9e, 0xff, 0xdc, 0x3f, 0xaa, 0xff,
0x12, 0xfa</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Hardware Device
Path - PCCARD Device Path.</td>
<td>Verify the device path nodes. Type: 1.Sub-Type: 2.Length: 5
bytes</td>
</tr>
<tr class="odd">
<td>5.4.1.1.4</td>
<td>0x745df5f1, 0x7d97, 0x4297, 0xaf, 0x5a, 0xc5, 0xca, 0x67, 0x28,
0x39, 0x18</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Hardware Device
Path - Memory Mapped Device Path.</td>
<td>Verify the device path nodes. Type: 1.Sub-Type: 3.Length: 24 bytes.
Memory Type &lt; <strong>EfiMaxMemoryType</strong>, or Memory Type &gt;
0x7FFFFFFF.End Address &gt;= Start Address.</td>
</tr>
<tr class="even">
<td>5.4.1.1.5</td>
<td>0xc8f02111, 0x1de9, 0x4df2, 0x8f, 0x17, 0xbb, 0x12, 0x9b, 0xa6,
0x4d, 0xfe</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Hardware Device
Path - Vendor Device Path.</td>
<td>Verify the device path nodes. Type: 1.Sub-Type: 4.Length&gt;=20
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.6</td>
<td>0x1c206e49, 0x6638, 0x469d, 0x8c, 0x9c, 0x26, 0x13, 0x85, 0x8e,
0x4d, 0x77</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Hardware Device
Path - Controller Device Path.</td>
<td>Verify the device path nodes. Type: 1.Sub-Type: 5.Length: 8
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.7</td>
<td>0xcedef0c0, 0x24cc, 0x4d36, 0x9d, 0x31, 0x9b, 0x9a, 0xf4, 0x63,
0xe6, 0x95</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check ACPI Device Path -
ACPI Device Path.</td>
<td>Verify the device path nodes. Type: 2.Sub-Type: 1.Length: 12
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.8</td>
<td>0xf497a21b, 0x8bb4, 0x4310, 0xba, 0xcf, 0xf6, 0xfc, 0x18, 0xda,
0x46, 0x9e</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check ACPI Device Path -
Expanded ACPI Device Path.</td>
<td>Verify the device path nodes. Type: 2.Sub-Type: 2.Length&gt;=19
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.9</td>
<td>0xc3b2ba41, 0x7126, 0x4b7a, 0xab, 0xdc, 0x7d, 0x1b, 0x46, 0x3d,
0x9b, 0xd7</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check ACPI _ADR Device
Path - ACPI _ADR Device Path.</td>
<td>Verify the device path nodes. Type<em>:</em> 2.Sub-Type<em>:</em> 3.
Length&gt;=8 bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.10</td>
<td>0xf52ef05c, 0x4a10, 0x4857, 0xb9, 0x8c, 0x01, 0xd8, 0x15, 0x6e,
0xf8, 0x3f</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - ATAPI Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 1.Length: 8 bytes.
PrimarySecondary: 0 or 1.SlaveMaster: 0 or 1.</td>
</tr>
<tr class="even">
<td>5.4.1.1.11</td>
<td>0x3e3eaf27, 0xf811, 0x4060, 0x97, 0xe1, 0x13, 0xfc, 0x5a, 0x51,
0x6c, 0x0c</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - SCSI Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 2.Length: 8
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.12</td>
<td>0x8f24a32d, 0xb167, 0x42df, 0x85, 0xc3, 0xa3, 0xec, 0x68, 0x4a,
0x79, 0x80</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - Fibre Channel Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 3.Length: 24
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.13</td>
<td>0xfd1e18a9, 0x0fd6, 0x4ea4, 0xac, 0xea, 0xe6, 0xc4, 0xd1, 0x73,
0x97, 0x52</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - 1394 Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 4.Length: 16
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.14</td>
<td>0x758cfe7a, 0x1463, 0x4f29, 0x8c, 0x5b, 0x0e, 0x3a, 0x04, 0x17,
0x5d, 0xf8</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - USB Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 5.Length: 6
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.15</td>
<td>0xd1527a5c, 0xc1bd, 0x4585, 0x93, 0x23, 0xa5, 0xea, 0xc7, 0xd5,
0x12, 0x7b</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - USB Device Path (WWID).</td>
<td>Verify the device path nodes. Type<em>:</em> 3.Sub-Type<em>:</em>
16. Length <em>&gt;=</em>10bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.16</td>
<td>0x50e59956, 0x46fd, 0x4b21, 0xb5, 0x57, 0x9a, 0x33, 0xb2, 0x08,
0xd3, 0x41</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - Device Logical Unit.</td>
<td>Verify the device path nodes. Type<em>:</em> 3.Sub-Type<em>:</em>
17. Length: 5 bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.17</td>
<td>0x2eb2da32, 0x351d, 0x4743, 0x80, 0x55, 0xea, 0x23, 0x75, 0x69,
0x61, 0xc2</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path – USB Device Path (Class).</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 15.Length: 11
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.18</td>
<td>0xba91dcd7, 0x719d, 0x4803, 0xaf, 0xe2, 0x61, 0x02, 0x1b, 0x31,
0x9b, 0x1f</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - I2O Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 6.Length: 8
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.19</td>
<td>0xb10c12a3, 0x8faa, 0x408a, 0x83, 0x63, 0x35, 0x6c, 0x74, 0x95,
0xe6, 0x80</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - MAC Address Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 11.Length: 37
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.20</td>
<td>0xdd68e9c3, 0x28e1, 0x44c7, 0x9c, 0x31, 0xba, 0xcc, 0x80, 0x4e,
0xe4, 0xb3</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - IPv4 Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 12.Length: 19 bytes.
StaticIPAddress: 0x00 or 0x01.</td>
</tr>
<tr class="even">
<td>5.4.1.1.21</td>
<td>0x2da145c3, 0x7d26, 0x4715, 0x8e, 0xfb, 0xf2, 0x35, 0xd5, 0x51,
0xe0, 0x77</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - IPv6 Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 13.Length: 43 bytes.
StaticIPAddress: 0x00 or 0x01.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.22</td>
<td>0xfcac17d1, 0xc792, 0x417a, 0x86, 0x99, 0x26, 0x11, 0xd0, 0xae,
0xc5, 0xba</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - InfiniBand Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 9.Length: 48
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.23</td>
<td>0x5f832ee4, 0x1d93, 0x42bf, 0x94, 0xea, 0xf8, 0x1b, 0x30, 0x1a,
0x9e, 0xf7</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - UART Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 14.Length: 19 bytes.
Parity: 0x00~0x05.Stop Bits: 0x00~0x03.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.24</td>
<td>0x86499222, 0x650a, 0x4492, 0x92, 0x2d, 0x46, 0x84, 0x4b, 0x1e,
0xb2, 0x0f</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - Vendor-Defined Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 10.Length&gt;=20
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.25</td>
<td>0x4c19f495, 0x7214, 0x48da, 0xb4, 0xc5, 0x2e, 0x6c, 0xae, 0xd2,
0x8f, 0xc9</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - UART Flow Control Messaging Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type: 10.Length: 24 bytes.
Vendor_GUID: DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL. Flow_Control_Map:
0 or 1.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.26</td>
<td>0x8e637c03, 0xa1df, 0x4ab6, 0xae, 0x29, 0x5b, 0x9c, 0xd8, 0x6c,
0x6d, 0x1e</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - Serial Attached SCSI (SAS) Device Path.</td>
<td>Verify the device path nodes. Type<em>:</em> 3.Sub-Type<em>:</em>
10.<em>Length</em>: 44 bytes. Vendor_GUID<em>:</em>
DEVICE_PATH_MESSAGING_SAS</td>
</tr>
<tr class="even">
<td>5.4.1.1.27</td>
<td>0x885db334, 0x940b, 0x4ec3, 0x82, 0xe5, 0xc5, 0xf1, 0x1d, 0xdb,
0x2a, 0x42</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Messaging Device
Path - iSCSI Device Path.</td>
<td>Verify the device path nodes. Type: 3.Sub-Type<em>:</em>
19.<em>Length&gt;=18</em> bytes. Options<em>:</em> Bit0=0x0, Bit2=0x0,
Bit10=0x0</td>
</tr>
<tr class="odd">
<td>5.4.1.1.28</td>
<td>0x1856d9b9, 0x57db, 0x49eb, 0x97, 0x35, 0x68, 0x8a, 0xee, 0x43,
0x76, 0xf6</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Media Device Path
- Hard Drive Media Device Path.</td>
<td>Verify the device path nodes. Type: 4.Sub-Type: 1.Length: 42 bytes.
MBR Type: 0x01 or 0x02.Signature Type: 0x00, 0x01 or 0x02.</td>
</tr>
<tr class="even">
<td>5.4.1.1.29</td>
<td>0x8b53dc1e, 0xb9be, 0x49d7, 0x86, 0xad, 0xd5, 0x12, 0x8e, 0x1f,
0x08, 0x34</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Media Device Path
- CD-ROM Media Device Path.</td>
<td>Verify the device path nodes. Type: 4.Sub-Type: 2.Length: 24
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.30</td>
<td>0x4c60bb0c, 0x8c00, 0x40f8, 0xa7, 0x35, 0x13, 0x4a, 0x56, 0x28,
0xe5, 0x21</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Media Device Path
- Vendor-Defined Media Device Path.</td>
<td>Verify the device path nodes. Type: 4.Sub-Type: 3.Length&gt;=20
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.31</td>
<td>0xde41b8cb, 0x401f, 0x4b7f, 0xb2, 0x34, 0xf8, 0xfb, 0x29, 0x3f,
0xc5, 0x23</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Media Device Path
- File Path Media Device Path.</td>
<td>Verify the device path nodes. Type: 4.Sub-Type: 4.Length&gt;=4
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.32</td>
<td>0xc9969745, 0x6507, 0x4695, 0xb1, 0x26, 0xc3, 0xf8, 0xe6, 0xd2,
0x86, 0xec</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check Media Device Path
- Media Protocol Device Path.</td>
<td>Verify the device path nodes. Type: 4.Sub-Type: 5.Length: 20
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.33</td>
<td>0x014988e5, 0xc211, 0x478d, 0x90, 0x6d, 0xf1, 0x6a, 0xb0, 0x73,
0x85, 0x0c</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check BIOS Boot
Specification Device Path.</td>
<td>Verify the device path nodes. Type: 5.Sub-Type: 1.Length&gt;=8
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.34</td>
<td>0x3152ee5d, 0xd161, 0x4916, 0xa4, 0x13, 0x44, 0xa7, 0x79, 0x39,
0x16, 0x7f</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Check End of Hardware
Device Path - End Entire Device Path.</td>
<td>Verify the device path nodes. Type: 0x7F or 0xFF.Sub-Type:
0xFF.Length: 4 bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.35</td>
<td>0xab5c791b, 0x015c, 0x41b2, 0x93, 0xdf, 0x70, 0xf5, 0xc8, 0xaf,
0x3a, 0xec</td>
<td>EFI_DEVICE_PATH_PROTOCOL – Check SATA Device Path.</td>
<td>Verify the device path nodes. Type: 3. SubType: 18. Length: 10
bytes</td>
</tr>
<tr class="odd">
<td>5.4.1.1.36</td>
<td>0x2bbca783, 0x4c23, 0x477d, 0xa7, 0x50, 0xf3, 0xda, 0xfa, 0xbc,
0x38, 0xf6</td>
<td>EFI_DEVICE_PATH_PROTOCOL – Check PIWG Fireware Volume</td>
<td>Verify the device path nodes. Type: 4. SubType: 6. Length &gt;= 4
bytes.</td>
</tr>
<tr class="even">
<td>5.4.1.1.37</td>
<td>0xbaaf24e1, 0x0c59, 0x4494, 0xaf, 0xef, 0x53, 0x02, 0xc1, 0x90,
0x57, 0x29</td>
<td>EFI_DEVICE_PATH_PROTOCOL – Check PIWG Fireware File</td>
<td>Verify the device path nodes. Type: 4. SubType: 7. Length &gt;= 4
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.38</td>
<td>0xbe55aaa6, 0x7510, 0x4904, 0x98, 0x65, 0x8c, 0xa7, 0x16, 0x34,
0xd2, 0x03</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL</strong> - Controller Device Path
Node.</td>
<td>Verify the device path nodes. Type: 3. SubType: 20. 0 &lt; VlanId
&lt; 4095</td>
</tr>
<tr class="even">
<td>5.4.1.1.39</td>
<td>0x5658c849, 0xd7ed, 0x4780, 0x8e, 0xe7, 0x6d, 0xf2, 0x62, 0x48,
0x1d, 0xdb</td>
<td><p><strong>EFI_DEVICE_PATH_PROTOCOL</strong> – Check Fibre Channel Ex</p></td>
<td>Verify the device path nodes. Type: 3. SubType: 21.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.40</td>
<td>0x3f412961, 0x4872, 0x4aa9, 0xbe, 0xd2, 0x2b, 0x03, 0x5f, 0xbc,
0xcc, 0xb6</td>
<td><p><strong>EFI_DEVICE_PATH_PROTOCOL</strong> – Check Serial Attached SCSI(SAS)
Ex.</p></td>
<td>Verify the device path nodes. Type: 3. SubType: 22.</td>
</tr>
<tr class="even">
<td>5.4.1.1.41</td>
<td>0x2ed116cb, 0x1ec7, 0x468a, 0x9c, 0xf8, 0x0f, 0xf4, 0x41, 0x2a,
0x4b, 0xb1</td>
<td><p><strong>EFI_DEVICE_PATH_PROTOCOL</strong> – Check NVMExpress.</p></td>
<td><p>Verify the device path nodes.</p>
<p>Type: 3. SubType: 23, Length = 16 bytes.</p></td>
</tr>
<tr class="odd">
<td>5.4.1.1.42</td>
<td>0x64770fbb, 0x280f, 0x40d5, 0x80, 0x33, 0x7, 0x82, 0x44, 0x7b, 0x3a,
0x2b</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Hardware Device Path - BMC Device Path.</p></td>
<td>Verify the device path nodes.
Type: 1. Sub-Type: 6. Length: 13
bytes. InterfaceType &gt;= 0 and InterfaceType &lt;= 3</td>
</tr>
<tr class="even">
<td>5.4.1.1.43</td>
<td>0x88882137, 0x4e4d, 0x445a, 0xa1, 0xae, 0x11, 0xd8, 0xc2, 0xe1,
0xcf, 0xac</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Messaging Device Path - Uniform Resource Identifiers (URI)
Device Path</p></td>
<td>Verify the device path nodes.
Type: 3. Sub-Type: 24. Length: &gt;= 4
bytes.</td>
</tr>
<tr class="odd">
<td>5.4.1.1.44</td>
<td>0xda928c4a, 0x6d22, 0x4091, 0x95, 0x8c, 0xe, 0xde, 0xa5, 0x3b, 0xc8,
0x2e</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Messaging Device Path - Universal Flash Storage (UFS) Device
Path</p></td>
<td>Verify the device path nodes.
Type: 3. Sub-Type: 25. Length: 6
bytes</td>
</tr>
<tr class="even">
<td>5.4.1.1.45</td>
<td>0x71e0582d, 0x983, 0x468e, 0x9a, 0x5d, 0xd2, 0xe5, 0xbb, 0x8c, 0x52,
0x6c</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Messaging Device Path - Secure Digital (SD) Device
Path</p></td>
<td>Verify the device path nodes.
Type: 3. Sub-Type: 26. Length: 5
bytes</td>
</tr>
<tr class="odd">
<td>5.4.1.1.46</td>
<td>0x3d20f5d0, 0x670a, 0x4923, 0x91, 0x78, 0xb0, 0x1e, 0x6d, 0xe8,
0xee, 0x13</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Messaging Device Path - Bluetooth Device Path</p></td>
<td>Verify the device path nodes.
Type: 3. Sub-Type: 27. Length: 10
bytes</td>
</tr>
<tr class="even">
<td>5.4.1.1.47</td>
<td>0x136c50de, 0xb2d4, 0x4416, 0xb4, 0x90, 0xe, 0x32, 0x85, 0xf1, 0x6a,
0x7</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Messaging Device Path - WIFI Device Path</p></td>
<td>Verify the device path nodes.
Type: 3. Sub-Type: 28. Length: 36
bytes</td>
</tr>
<tr class="odd">
<td>5.4.1.1.48</td>
<td>0x973269de, 0xdca6, 0x4ad9, 0x9b, 0x9b, 0x6, 0x40, 0xfa, 0x4d, 0xbd,
0xf5</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check Relative Offset Range Device Path</p></td>
<td>Verify the device path nodes.
Type: 4. Sub-Type: 8. Length: 24
bytes</td>
</tr>
<tr class="even">
<td>5.4.1.1.49</td>
<td>0x6e817459, 0x21fd, 0x4923, 0x89, 0xe7, 0xca, 0xf9, 0x7d, 0x9d,
0xc2, 0x27</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL -</p>
<p>Check RAM Disk Device Path</p></td>
<td>Verify the device path nodes.
Type: 4. Sub-Type: 9. Length: 38
bytes</td>
</tr>
<tr class="odd">
<td>5.4.1.1.50</td>
<td>0xdf69547d, 0xd032, 0x44bd, 0xb0, 0x54, 0x7f, 0x34, 0x3c, 0x2c,
0x7d, 0x95</td>
<td><p>EFI_DEVICE_PATH_PROTOCOL –</p>
<p>Check eMMC Device Path.</p></td>
<td>Verify the device path node. Type: 3. Sub-Type: 29. Length: 5
bytes</td>
</tr>
</tbody>
</table>

## Whole Device Path Conformance Test

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 20%" />
<col style="width: 32%" />
<col style="width: 34%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.2.1.1</td>
<td>0x4d36889a, 0x938a, 0x45ae, 0xaa, 0x79, 0x89, 0x7f, 0xa3, 0x7e,
0x15, 0x99</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> BIOS Root Specification
Device Path.</td>
<td>A Device Path containing the BIOS Boot Specification Device Path
should contain only the required End Device Path structure and no other
Device Path structures.</td>
</tr>
<tr class="odd">
<td>5.4.2.1.2</td>
<td>0xf141747c, 0xf5f8, 0x43b9, 0x99, 0x9e, 0x45, 0xad, 0x37, 0xe1,
0x2a, 0x49</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> PCI Root Bus Device Path
Node.</td>
<td>The device path node for PCI root bus is: ACPI Device Path: _HID
PNP0A03. It must be the first device path node.</td>
</tr>
<tr class="even">
<td>5.4.2.1.3</td>
<td>0xc44987b4, 0x9a29, 0x4b10, 0x82, 0xd3, 0xe9, 0x46, 0x81, 0x7e,
0x3c, 0x02</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> ACPI Device Path
Node.</td>
<td><p>ACPI _CRS Device Path Node must include</p>
<p>Floppy – ACPI Device Path: _HID PNP0604</p>
<p>Keyboard – ACPI Device Path: _HID PNP0301</p>
<p>Serial Port – ACPI Device Path: _HID PNP0501</p>
<p>Parallel Port – ACPI Device Path: _HID PNP0401.</p>
<p>EISA Device Path Nodes other than PCI Root Bus must be preceded by an
ACPI Device Path Node.</p></td>
</tr>
<tr class="odd">
<td>5.4.2.1.4</td>
<td>0xb28b09c6, 0x3b60, 0x48ce, 0xbf, 0x66, 0xac, 0xa1, 0xf6, 0x20,
0x6b, 0x01</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> PCI Device Path
Node.</td>
<td>The PCI Device Path Node must be preceded by an ACPI Device Path
Node that uniquely identifies the PCI root bus (Acpi(PNP0A03,0)) or
another PCI Device Path Node.</td>
</tr>
<tr class="even">
<td>5.4.2.1.5</td>
<td>0x47f98975, 0x2945, 0x4198, 0x99, 0xa0, 0x7b, 0x07, 0xfe, 0xe0,
0x9b, 0x85</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Memory Mapped Device
Path Node.</td>
<td>The Memory Mapped Device Path Node must be the first device path
node.</td>
</tr>
<tr class="odd">
<td>5.4.2.1.6</td>
<td>0xfc86d0ef, 0xb3da, 0x4377, 0x99, 0x36, 0x56, 0x85, 0xb4, 0x59,
0x9e, 0x24</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> ATAPI Device Path
Node.</td>
<td>The ATAPI Device Path Node must be preceded by a PCI Device Path
Node.</td>
</tr>
<tr class="even">
<td>5.4.2.1.7</td>
<td>0x390d6af3, 0x78a8, 0x41ed, 0x99, 0x78, 0x16, 0x4d, 0xfe, 0x2b,
0x30, 0xc8</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> SCSI Device Path
Node.</td>
<td>The SCSI Device Path Node must be preceded by a PCI Device Path
Node.</td>
</tr>
<tr class="odd">
<td>5.4.2.1.8</td>
<td>0xd456e708, 0x5b3c, 0x4f72, 0xae, 0xbb,0x7f, 0x94, 0x92, 0x76, 0x7b,
0xe1</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> USB Device Path
Node.</td>
<td>The USB Device Path Node must be preceded by a PCI Device Path
Node.</td>
</tr>
<tr class="even">
<td>5.4.2.1.9</td>
<td>0x436486e1, 0x4426, 0x427f, 0xa5, 0xc5, 0x45, 0xf2, 0x13, 0xef,
0x15, 0x88</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> PCI Option ROM Device
Path Node.</td>
<td>The PCI Option ROM Device Path Node must be preceded by a PCI Device
Path Node</td>
</tr>
<tr class="odd">
<td>5.4.2.1.10</td>
<td>0x9619e2ad, 0x0358, 0x4aef, 0x98, 0x60, 0xb9, 0x08, 0xa3, 0xcc,
0x08, 0x7e</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Device Path must be
terminated.</td>
<td>The Device Path must be terminated by an End of Device Path node
with a sub-type of End the Entire Device Path. A <strong>NULL</strong>
Device Path consists of a single End Device Path Node. A Device Path
that contains a <strong>NULL</strong> pointer and no Device Path
structures is illegal.</td>
</tr>
<tr class="even">
<td>5.4.2.1.11</td>
<td>0x59116d82, 0xaf34, 0x48a2, 0xaa, 0x22, 0xe4, 0x83, 0x7a, 0xd8,
0xe5, 0x8d</td>
<td><strong>EFI_DEVICE_PATH_PROTOCOL -</strong> Controller Device Path
Node.</td>
<td>The Controller Device Path Node must be preceded by a PCI Device
Path Node.</td>
</tr>
</tbody>
</table>

## Device Path Utilities Protocol Interface Function Test

### CreatDeviceNode Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.3.1.1</td>
<td>0x9831dfbb, 0x008e, 0x4b37, 0xb2, 0x3c, 0x76, 0x43, 0x7c, 0xa4,
0xee, 0x91</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.</strong> CreatDeviceNode
- CreatDeviceNode<strong>()</strong>must set <em>Type</em>,
<em>SubType</em> and <em>Length</em> correctly, return
EFI_DEVICE_PATH.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> with a
<em>NodeType</em> value of 1, a <em>NodeSubType</em> value of 1, and a
<em>NodeLength</em> value of 6.</p>
<p>2. The return <strong>EFI_DEVICE_PATH</strong> structure should have
<em>Type</em>, <em>SubType</em> and <em>Length</em> values that are the
same as the ones set in <strong>CreatDeviceNode()</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.4.3.1.2</td>
<td>0xf7c1a5dd, 0x3683, 0x43a6, 0x8d, 0x90, 0x6b, 0x79, 0x12, 0xbd,
0x32, 0x1d</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.</strong> CreatDeviceNode
- CreatDeviceNode<strong>()</strong>must set <em>Type</em>,
<em>SubType</em> and <em>Length</em> correctly, return
<strong>EFI_DEVICE_PATH</strong> (another case).</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> with a
<em>NodeType</em> value of 2, a <em>NodeSubType</em> value of 1 and a
<em>NodeLength</em> value of 12.</p>
<p>2. The return <strong>EFI_DEVICE_PATH</strong> structure should have
<em>Type</em>, <em>SubType</em> and <em>Length</em> values the same as
the ones set in <strong>CreatDeviceNode()</strong>.</p></td>
</tr>
</tbody>
</table>

### AppendDeviceNode Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.3.2.1</td>
<td>0x0deb01c9, 0x16db, 0x42ac, 0x99, 0x99, 0x27, 0x7b, 0x61, 0x96,
0xf4, 0xb8</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDeviceNode -AppendDeviceNode()</strong> called by the End
of Device Path node must set <em>Type</em>, <em>SubType</em> and
<em>Length</em> correctly in the first device path node, return
<strong>EFI_DEVICE_PATH</strong> structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> to create an End of
Device Path node.</p>
<p>2. Call <strong>CreatDeviceNode()</strong> with a <em>NodeType</em>
value of 2,a <em>NodeSubType</em> value of 1 and a
<strong>NodeLength</strong> value of 12.</p>
<p>3. Call <em>AppendDeviceNode()</em> with a <em>DeviceNode</em> value
of the return pointer of <strong>CreatDeviceNode()</strong>.</p>
<p>4. The first device path node in the return
<strong>EFI_DEVICE_PATH</strong> structure should have <em>Type</em>,
<em>SubType</em> and <em>Length</em> values the same as the ones set in
CreatDeviceNode().</p></td>
</tr>
<tr class="odd">
<td>5.4.3.2.2</td>
<td>0xc2fa4f0f, 0xd2f0, 0x44b1, 0xa8, 0x69, 0x04, 0xeb, 0xc8, 0x88,
0xa6, 0xb6</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL. AppendDeviceNode
-AppendDeviceNode()</strong> must set <em>Type</em>, <em>SubType</em>
and <em>Length</em> correctly in the last but the End of Device Path
node in the return <strong>EFI_DEVICE_PATH</strong> structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. The last but the end-of-device-path node in the return
<strong>EFI_DEVICE_PATH</strong> structure should have <em>Type</em>,
<em>SubType</em> and <em>Length</em> values the same as set in the last
<strong>CreatDeviceNode()</strong>.</p></td>
</tr>
</tbody>
</table>

### GetDevicePathSize Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.3.3.1</td>
<td>0x4257efa5, 0xd844, 0x4361, 0x98, 0xb9, 0x0d, 0x0e, 0x09, 0xf6,
0x8f, 0x78</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.</strong>
GetDevicePathSize - GetDevicePathSize<strong>()</strong> should return
the correct value and the return status should increase after
AppendDeviceNode() is called.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> to create an End of
Device Path node.</p>
<p>2. Call GetDevicePathSize().</p>
<p>3. Call <strong>AppendDeviceNode()</strong> with a
<em>DeviceNode</em> value of a return pointer of
<strong>CreatDeviceNode()</strong>.</p>
<p>4. Call GetDevicePathSize() again.</p>
<p>5. The return status should be 4 after
<strong>GetDevicePathSize()</strong> was called the first time.</p>
<p>6. The return status should show an increase of the new device path
node’s length after <strong>GetDevicePathSize()</strong> was called the
second time.</p></td>
</tr>
</tbody>
</table>

### DuplicateDevicePath Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.3.4.1</td>
<td>0x065a0a89, 0x3594, 0x440e, 0x82, 0xe6, 0x9e, 0xaf, 0x74, 0xc7,
0xb7, 0x2f</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.DuplicateDevicePath - DuplicateDevicePath()</strong> must
correctly set the return <strong>EFI_DEVICE_PATH</strong> structure the
same as the original one.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>GetDevicePathSize()</strong> first.</p>
<p>3. Call <strong>DupilicateDevicePath()</strong>.</p>
<p>4. Call <strong>GetDevicePathSize()</strong> with a
<em>DevicePath</em> value of the return value of
<strong>DupilicateDevicePath()</strong>.</p>
<p>5. The return value of <strong>GetDevicePathSize()</strong> should
keep the same as the first return value, and the two device paths should
be identical.</p></td>
</tr>
</tbody>
</table>

### DuplicateDevicePath Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.3.2.6</td>
<td>0x97363972, 0x64cd, 0x4af8, 0xa7, 0x07, 0x41, 0x49, 0x81, 0xad,
0x4a, 0xb2</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.DuplicateDevicePath -DuplicateDevicePath()</strong> should return
<strong>NULL</strong> if <em>DevicePath</em> is
<strong>NULL</strong></td>
<td><p>1. Call <strong>DupilicateDevicePath()</strong>with a
<em>DevicePath</em> value of <strong>NULL.</strong></p>
<p>2. The return value should be <strong>NULL.</strong></p></td>
</tr>
</tbody>
</table>

### AppendDevicePath Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.3.5.1</td>
<td>0x7da4d0e1, 0x2d1b, 0x4b60, 0xaa, 0xb2, 0xf3, 0xc1, 0x35, 0xf1,
0xf3, 0x21</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.AppendDevicePath - AppendDevicePath()</strong> must correctly
set the return <strong>EFI_DEVICE_PATH</strong> structure as the new
device path that appends the second device path to the first.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create another device
path.</p>
<p>3. Call <strong>AppendDevicePath()</strong> with <em>Src1</em> and
<em>Src2</em> set respectively.</p>
<p>4. Call <strong>GetDevicePathSize()</strong> with a
<em>DevicePath</em> value of the return value of
<strong>AppendDevicePath ()</strong>.</p>
<p>5. The return value of <strong>GetDevicePathSize()</strong> should
show an increase of the new device path’s length with the size of
<em>Src1</em>’s End of Device Path device node subtracted after
<strong>GetDevicePathSize()</strong> is called the second time.</p></td>
</tr>
</tbody>
</table>

### AppendDevicePathInstance Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.3.6.1</td>
<td>0x8d72d028, 0x1e92, 0x4a79, 0x8d, 0xbe, 0xab, 0xc9, 0x3a, 0x47,
0xed, 0xee</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.AppendDevicePathInstance - AppendDevicePathInstance()</strong>
must correctly set the return <strong>EFI_DEVICE_PATH</strong> structure
as the new device path that appends the specific device path instance to
the specific device path.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create another device
path as a new device path instance.</p>
<p>3. Call <strong>AppendDevicePathInstance()</strong> with a
<em>DevicePathInstance</em> value of the new device path instance.</p>
<p>4. The last device path instance of the returned
<strong>EFI_DEVICE_PATH</strong> structure should be the same as the
newly created one.</p></td>
</tr>
</tbody>
</table>

### GetNextDevicePathInstance Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.3.7.1</td>
<td>0x4c914601, 0x681c, 0x48e5, 0xbe, 0xbd, 0x72, 0xdf, 0xfb, 0x1b,
0x42, 0x63</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.GetNextDevicePathInstance - GetNextDevicePathInstance()</strong>
must get the next device path instance and return a pointer to the copy
of the current device path instance.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create another device
path as a new device path instance.</p>
<p>3. Call <strong>AppendDevicePathInstance()</strong> with a
<em>DevicePathInstance</em> value of the new device path instance.</p>
<p>4. Call <strong>GetNextDevicePathInstance()</strong>.</p>
<p>5. The return <strong>EFI_DEVICE_PATH</strong> structure should
include a device path instance the same as the first instance of the new
device path and <em>DevicePathInstanceSize</em> should become the size
of the first instance, and at the same time, the
<em>DevicePathInstance</em> should point to the second
instance.</p></td>
</tr>
</tbody>
</table>

### IsDevicePathMultiInstance Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.3.8.1</td>
<td>0x2e9e1bb4, 0x5e2f, 0x4a26, 0xbb, 0x16, 0xf8, 0x0f, 0xf8, 0xdf,
0x6c, 0xdd</td>
<td><p><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.IsDevicePathMultiInstance - IsDevicePathMultiInstance()</strong>
must judge whether a device path is a</p>
<p>multi-instance.</p></td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> to create an End of
Device Path node.</p>
<p>2. Call <strong>IsDevicePathMultiInstance()</strong>.</p>
<p>3. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> repeatedly to create a new device
path that includes only one device path instance.</p>
<p>4. Call <strong>IsDevicePathMultiInstance()</strong>.</p>
<p>5. Call <strong>AppendDevicePathInstance()</strong> with a
<em>DevicePathInstance</em> value of a new device path instance.</p>
<p>6. Call IsDevicePathMultiInstance().</p>
<p>7. The return values of <em>IsDevicePathMultiInstance</em> should be
<strong>FALSE</strong>, <strong>FALSE</strong> and <strong>TRUE</strong>
respectively.</p></td>
</tr>
</tbody>
</table>

## Device Path Utilities Protocol Interface Conformance Test

### CreatDeviceNode Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.4.1.1</td>
<td><p>0x44a2c284, 0xb019, 0x441b, 0x9e, 0xe0, 0x15,</p>
<p>0x14, 0x96, 0x51, 0xc8, 0x1f</p></td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL. CreatDeviceNode</strong>
- <strong>CreatDeviceNode()</strong> should fail with an invalid
<em>NodeLength</em> value</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> with a
<em>NodeLength</em> value of 3.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

### AppendDeviceNode Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.4.2.1</td>
<td>0x795510e5, 0xdd0e, 0x403e, 0xa3, 0x4c, 0x67, 0x64, 0x2f, 0xe6,
0x2b, 0x46</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDeviceNode -AppendDeviceNode()</strong> should return the
copy of <em>DeviceNode</em> with a <em>DevicePath</em> value of
<strong>NULL</strong></td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> with a
<em>NodeType</em> value of 1, a <em>NodeSubType</em> value of 1 and a
<em>NodeLength</em> value of 6.</p>
<p>2. Call <strong>AppendDeviceNode()</strong> with DevicePath value of
<strong>NULL</strong> and a DeviceNode value of the return pointer of
<strong>CreatDeviceNode()</strong>.</p>
<p>3. The return pointer should return the copy of the
<em>DeviceNode</em> parameter .</p></td>
</tr>
<tr class="odd">
<td>5.4.4.2.2</td>
<td>0x54f1f4cc, 0xa193, 0x4023, 0xa1, 0x68, 0x96, 0x9a, 0xa8, 0x2d,
0xdd, 0x13</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDeviceNode -AppendDeviceNode()</strong> should return the
copy of <em>DevicePath</em> with <em>DeviceNode</em> set to
<strong>NULL</strong></td>
<td><p>4. Call <strong>CreatDeviceNode()</strong> to create an End of
Device Path node.</p>
<p>5. Call <strong>AppendDeviceNode()</strong> with a
<em>DeviceNode</em> value of <strong>NULL</strong>.</p>
<p>6. The return should be the copy of <em>DevicePath</em>.</p></td>
</tr>
<tr class="even">
<td>5.4.4.2.3</td>
<td>0xbb6ae1b8, 0xb420, 0x4f94, 0xb7, 0x88, 0xc4, 0xcc, 0x3a, 0xda,
0x53, 0x05</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDeviceNode</strong> - <strong>AppendDeviceNode()</strong>
should return end-of-device-path device node if both <em>DevicePath</em>
and <em>DeviceNode</em> are <strong>NULL</strong></td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<em>AppendDeviceNode</em> with both <em>DevicePath</em> and
<em>DeviceNode</em> are <strong>NULL</strong></p>
<p>2. The return <strong>EFI_DEVICE_PATH_PROTOCOL</strong> structure
should be end-of-device-path device node.</p></td>
</tr>
</tbody>
</table>

### AppendDevicePath Conformance

<table>
<colgroup>
<col style="width: 11%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 45%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.4.3.1</td>
<td>0xba53eab4, 0xa3b2, 0x4ed3, 0xae, 0x7e, 0x77, 0xa3, 0x6a, 0x86,
0x1d, 0xb0</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDevicePath</strong> - <strong>AppendDevicePath()</strong>
should ignore <em>Src1</em> when it is set to
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>CreatDeviceNode()AppendDeviceNod()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>GetDevicePathSize()</strong>.</p>
<p>3. Call <strong>AppendDeviceNode()</strong> with a <em>Src1</em>
value of <strong>NULL</strong> and a valid <em>Src2</em> value.</p>
<p>4. Call <strong>GetDevicePathSize()</strong> with a
<em>DevicePath</em> value of the return value of
<strong>AppendDeviceNode()</strong>.</p>
<p>5. The return value of <strong>GetDevicePathSize()</strong> should be
the same as the first return value.</p></td>
</tr>
<tr class="odd">
<td>5.4.4.3.2</td>
<td>0x49fbe4f2, 0xb963, 0x4a01, 0xbb, 0xd0, 0xc2, 0x9d, 0x11, 0x17,
0x4f, 0x6d</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDevicePath</strong> - <strong>AppendDevicePath()</strong>
should ignore <em>Src2</em> when it is set to
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>CreatDeviceNode()AppendDeviceNode()</strong> repeatedly to create a new device
path.</p>
<p>2. Call <strong>GetDevicePathSize()</strong>.</p>
<p>3. Call <strong>AppendDeviceNode()</strong> with a valid
<em>Src1</em> value and a <em>Src2</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>GetDevicePathSize()</strong> with a
<em>DevicePath</em> value of the return value of
<strong>AppendDeviceNode()</strong>.</p>
<p>5. The return value of <strong>GetDevicePathSize()</strong> should be
the same as the first return value.</p></td>
</tr>
<tr class="even">
<td>5.4.4.3.3</td>
<td>0x546bd0e4, 0xd288, 0x461f, 0x8a, 0xac, 0x67, 0x75, 0xc6, 0x96,
0x83, 0xe4</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL</strong>.
<strong>AppendDeviceNode</strong> - <strong>AppendDeviceNode()</strong>
should return end-of-device-path if both <em>Src1</em> and <em>Src2</em>
are <strong>NULL</strong></td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode</strong> with both <em>Src1</em> and
<em>Src2</em> are <strong>NULL</strong></p>
<p>2. The return <strong>EFI_DEVICE_PATH</strong> structure should be
end-of-device-path.</p></td>
</tr>
</tbody>
</table>

### AppendDevicePathInstance Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.4.4.1</td>
<td>0xfe34dfb2, 0x7b8d, 0x42c7, 0x8a, 0x8a, 0x00, 0xea, 0x1b, 0xe6,
0xe5, 0x44</td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.AppendDevicePathInstance</strong> -
<strong>AppendDevicePathInstance()</strong> should fail with a
<em>DevicePathInstance</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> with a
<em>DevicePathInstance</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

### GetNextDevicePathInstance Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.4.5.1</td>
<td><p>0x25acf6b7, 0xd5c8,</p>
<p>0x4fb0, 0xa6, 0x89, 0xaf, 0x8c, 0x03, 0x4e, 0x5e, 0xdc</p></td>
<td><strong>EFI_DEVICE_PATH_UTILITIES_PROTOCOL.</strong>
GetNextDevicePathInstance -
GetNextDevicePathInstance<strong>()</strong>should fail with
<em>DevicePathInstance</em> set to <strong>NULL</strong>.</td>
<td><p>1. Call <strong>GetNextDevicePathInstance()</strong> with a
<em>DevicePathInstance</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

## Device Path To Text Protocol Interface Function Test

### ConvertDeviceNodeToText Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.5.1.1</td>
<td>0x68d2e9f6, 0xb5f0, 0x4660, 0xbd, 0xf7, 0x74, 0x97, 0x43, 0xce,
0xb1, 0xb4</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL</strong>.
<strong>ConvertDeviceNodeToTexT</strong>
-<strong>ConvertDeviceNodeToText()</strong> must set a string to
describe the device node structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong> and set the values of
this device path node’s specific device path data to create a device
path node of PCI Root Device Path.</p>
<p>2. Call <strong>ConvertDeviceNodeToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>3. The return string should be the same as the expected one.</p></td>
</tr>
<tr class="odd">
<td>5.4.5.1.2</td>
<td>0x09a4021d, 0x2804, 0x49fa, 0x82, 0x95, 0x30, 0xb1, 0xcf, 0x27,
0xf7, 0x88</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL</strong>.
<strong>ConvertDeviceNodeToTexT -ConvertDeviceNodeToText()</strong> must
set a string to describe the device node structure.</td>
<td><p>4. Call <strong>CreatDeviceNode()</strong> and set the values of
this device path node’s specific device path data to create a device
path node of PCI Device Path.</p>
<p>5. Call <strong>ConvertDeviceNodeToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>6. The return string should be the same as the expected one.</p></td>
</tr>
<tr class="even">
<td>5.4.5.1.3</td>
<td>0x97deff32, 0xa4d0, 0x4909, 0xa7, 0xfa, 0x98, 0xcf, 0x3e, 0xcf,
0xf5, 0xf0</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDeviceNodeToTexT</strong>
-<strong>ConvertDeviceNodeToText()</strong> must set a string to
describe the device node structure.</td>
<td><p>7. Call <strong>CreatDeviceNode()</strong> and set the values of
this device path node’s specific device path data to create a device
path node of ATAPI Device Path.</p>
<p>8. Call <strong>ConvertDeviceNodeToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>9. The return string should be the same as the expected one.</p></td>
</tr>
</tbody>
</table>

### ConvertDevicePathToText Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
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
<td>5.4.5.2.1</td>
<td><p>0x11993701, 0x534b,</p>
<p>0x4804, 0xb9, 0x17, 0x72, 0x6b, 0xc9, 0x57, 0x43, 0x13</p></td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDevicePathToText -ConvertDevicePathToText()</strong> must set a string to describe
the device path structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> and
<strong>AppendDevicePathInstance()</strong> repeatedly to create a
legacy floppy device path.</p>
<p>2. Call <strong>ConvertDevicePathToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>3. The return string should be the same as the expected one.</p></td>
</tr>
<tr class="odd">
<td>5.4.5.2.2</td>
<td>0xdb90a554, 0xc75f, 0x409e, 0x9d, 0x40, 0xcc, 0xcd, 0x6a, 0xc6,
0xd0, 0x57</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDevicePathToText -ConvertDevicePathToText()</strong> must set a string to describe
the device path structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> and
<strong>AppendDevicePathInstance()</strong> repeatedly to create an IDE
disk device path.</p>
<p>2. Call <strong>ConvertDevicePathToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>3. The return string should be the same as the expected one.</p></td>
</tr>
<tr class="even">
<td>5.4.5.2.3</td>
<td>0x532045b2, 0x8cb7, 0x4c27, 0x83, 0x72, 0xc2, 0x80, 0xe4, 0xe1,
0xf9, 0x29</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDevicePathToText -ConvertDevicePathToText()</strong> must set a string to describe
the device path structure.</td>
<td><p>1. Call <strong>CreatDeviceNode()</strong>,
<strong>AppendDeviceNode()</strong> and
<strong>AppendDevicePathInstance()</strong> repeatedly to create a
secondary root PCI bus with a PCI to PCI bridge device path.</p>
<p>2. Call <strong>ConvertDevicePathToText()</strong> with a
<em>DisplayOnly</em> value of <strong>FALSE</strong> and a
<em>AllowShortcuts</em> value of <strong>TRUE</strong> and
<strong>FALSE</strong> respectively.</p>
<p>3. The return string should be the same as the expected one.</p></td>
</tr>
</tbody>
</table>

## Device Path To Text Protocol Interface Conformance Test

### ConvertDeviceNodeToText Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
<col style="width: 44%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.6.1.1</td>
<td>0x945a93f7, 0xedac, 0x4893, 0xb2, 0xd2, 0x84, 0x0c, 0x39, 0xbb,
0x78, 0x24</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
should return <strong>NULL</strong> with <em>DeviceNode</em> set to
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>ConvertDeviceNodeToText ()</strong> with a
<em>DeviceNode</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

### ConvertDevicePathToText Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.6.2.1</td>
<td>0x2570911f, 0x1a08, 0x4f96, 0x92, 0xf5, 0x26, 0x7e, 0xc0, 0x8d,
0x75, 0xb0</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertDevicePathToText -ConvertDevicePathToText()</strong> should return
<strong>NULL</strong> with <em>DevicePath</em> set to
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>ConvertDevicePathToText ()</strong> with a
<em>DevicePath</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

## Device Path To Text Protocol Interface Coverage Test

### ConvertDeviceNodeToText Coverage

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 14%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.7.1.1</td>
<td>0xca28d9a9, 0x6159, 0x4b70, 0xb5, 0xa0, 0x6f, 0xb3, 0x68, 0x63,
0x02, 0xd2</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe PcCard device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.2</td>
<td>0x203b6963, 0x5013, 0x4683, 0x95, 0x8b, 0xd4, 0xa2, 0x1c, 0xcc,
0xbb, 0x8d</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Memory Mapped device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.3</td>
<td>0xc05c7ebe, 0x69a4, 0x4fcc, 0xb8, 0x29, 0x25, 0x77, 0x54, 0xf3,
0xb4, 0x3e</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Vendor defined device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.4</td>
<td>0x36de850b, 0xb28d, 0x4bfd, 0x9e, 0xff, 0xbc, 0xd8, 0x05, 0xa4,
0xa2, 0xf3</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Controller device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.5</td>
<td>0xa20c1075, 0x9bde, 0x42db, 0x83, 0x28, 0x62, 0x6a, 0x18, 0xe6,
0x07, 0x9e</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the ACPI Expended device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.6</td>
<td>0xd448b8f6, 0x2d7e, 0x473d, 0xae, 0x66, 0x9e, 0xc7, 0xba, 0xa7,
0xf9, 0x9c</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a shortcut form of text string to describe the ACPI
Expended device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.7</td>
<td>0xc4ef8ea1, 0x6fa7, 0x4e49, 0xa1, 0x7a, 0x30, 0xa0, 0xed, 0xd2,
0x3c, 0x6b</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion <strong>ConvertTextToDeviceNode()</strong>
has performed on the device node string.</td>
<td><p>1. Set a text string to describe the SCSI device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.8</td>
<td>0xac5859c4, 0x99a9, 0x43bc, 0xbd, 0x20, 0x76, 0xd4, 0x36, 0xa8,
0xf9, 0x71</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Fibre Channel device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.9</td>
<td>0xd00934b4, 0x846e, 0x4f8b, 0xa6, 0xc9, 0x13, 0xb, 0x19, 0x13, 0x49,
0x3c</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the AcpiAdr device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.10</td>
<td>0xe49fdcdb, 0xbadb, 0x48c7, 0xbe, 0x8b, 0xbc, 0xce, 0x19, 0x0f,
0x2b, 0x79</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the USB device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.11</td>
<td>0xb21543cc, 0x4090, 0x4e28, 0x88, 0xc5, 0x5b, 0xd6, 0x29, 0x17,
0x7b, 0xd9</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the I2O device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.12</td>
<td>0x4bf7bbff, 0x783f, 0x4ab0, 0xb5, 0x2a, 0x3e, 0xab, 0x1d, 0x6e,
0xdd, 0x02</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Infiniband device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.13</td>
<td>0xd7a537b7, 0x96a2, 0x478d, 0xa2, 0xd3, 0x67, 0xca, 0x68, 0x93,
0x8e, 0xe2</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the PC-ANSI device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.14</td>
<td>0xeaba3b8d, 0x0aad, 0x4729, 0xb0, 0x2e, 0xb6, 0xa4, 0x89, 0xdc,
0x17, 0x4d</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the <em>UartFlowCtrl</em> device
path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.15</td>
<td>0xd751aa0e, 0xb0ea, 0x43ee, 0x89, 0x65, 0x5, 0x4c, 0x97, 0x1, 0xa,
0x32</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the AcpiExp device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.16</td>
<td>0x51a639b6, 0x878d, 0x4118, 0x88, 0x6b, 0x15, 0x4f, 0x84, 0x5e,
0xfd, 0xfd</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the PciRoot device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.17</td>
<td>0xe23c5141, 0xac77, 0x42f4, 0xb4, 0x18, 0x9e, 0xd3, 0x76, 0xbc,
0xcf, 0xd7</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the MAC device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.18</td>
<td><p>0x77ebce11, 0x3621,</p>
<p>0x4900, 0xbd, 0xb2, 0x95, 0x01, 0x2a, 0xcd, 0xca, 0x46</p></td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the IPv4 device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.19</td>
<td>0xef32be73, 0xf5b7, 0x4545, 0xaf, 0xd7, 0x5e, 0xfb, 0xdc, 0x01,
0x8f, 0x16</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the IPv6 device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.20</td>
<td>0xbdf0860e, 0x12b6, 0x4c2a, 0xa2, 0x6c, 0x8e, 0x25, 0x87, 0x99,
0xa8, 0xd6</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the UART device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.21</td>
<td><p>0x340f6746, 0x662f,</p>
<p>0x4613, 0x89, 0x5a, 0x16, 0x57, 0x7d, 0xe0, 0x76, 0x99</p></td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the USB Class device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.22</td>
<td>0x16001709, 0x687d, 0x4880, 0x89, 0xc4, 0x1c, 0x63, 0x1e, 0xb5,
0x2e, 0x2d</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the PcieRoot device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.23</td>
<td>0xf375ad05, 0xd5ae, 0x408f, 0x8a, 0xa5, 0x21, 0xb8, 0xd1, 0xe9,
0xfd, 0x75</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Floppy device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.24</td>
<td>0xa4c0ed2e, 0x1438, 0x44cc, 0x97, 0x10, 0x1e, 0x2e, 0x29, 0xe3,
0xbd, 0xe6</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Keyboard device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.25</td>
<td><p>0x2ccd0cbb, 0x395f,</p>
<p>0x4b76, 0x8a, 0xe8, 0x3f, 0x4a, 0x07, 0x98, 0x4f, 0x3a</p></td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Logical Unit device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.26</td>
<td>0x13625cd7, 0x79d1, 0x4f0b, 0x80, 0xe0, 0xb5, 0x54, 0x94, 0xae,
0xc6, 0xb6</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Serial device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.27</td>
<td>0x2001ae80, 0x7309, 0x4b70, 0x9f, 0x4e, 0x7b, 0xad, 0x66, 0x9d,
0xc0, 0x43</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Hard Drive with GUID device
path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.28</td>
<td>0xf37b8ee5, 0xfb01, 0x41e3, 0xa2, 0x6a, 0xa1, 0x99, 0xd9, 0x59,
0x24, 0x74</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Parallel Port device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.29</td>
<td>0xe171c43f, 0x9aaf, 0x4133, 0x95, 0x80, 0xfb, 0xb5, 0xa7, 0x0b,
0x88, 0x72</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the CD-ROM device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as theoriginal one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.30</td>
<td>0x596665ca, 0x74e6, 0x4f6e, 0x88, 0xd8, 0x6e, 0x26, 0xe5, 0x3a,
0x42, 0xab</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the FibreEx device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.31</td>
<td>0x5b136106, 0xcee0, 0x46d9, 0x87, 0xa9, 0x68, 0x1d, 0x70, 0xf7,
0x1f, 0x17</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Media device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.32</td>
<td>0xdb0e6e8b, 0x1d57, 0x41e5, 0xb8, 0x74, 0x4c, 0xe8, 0x5a, 0xd5,
0x76, 0x4c</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText - ConvertDeviceNodeToText()</strong>
must recover the conversion <strong>ConvertTextToDeviceNode()</strong>
has performed on the device node string.</td>
<td><p>1. Set a text string to describe the SAS device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.33</td>
<td>0x44f98053, 0xbbf7, 0x4002, 0x9a, 0x7e, 0x6b, 0x4d, 0x37, 0x3e,
0x18, 0xff</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Media Relative Offset Range
device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.34</td>
<td>0x44ed02e4, 0x48c7, 0x42df, 0xbe, 0x12, 0x60, 0xc1, 0xb2, 0x7f,
0xe8, 0xab</td>
<td><strong>EFI_DEVICE_PATH_TO_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Vlan device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.35</td>
<td>0x4e3dfefc, 0xeebb, 0x46d0, 0xa1, 0xc3, 0x83, 0xaa, 0x2, 0x6d, 0xf1,
0x1b</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
SASEx device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.36</td>
<td>0x21e74335, 0x50c9, 0x4deb, 0x8a, 0x9d, 0xf4, 0x2, 0x97, 0xfc, 0xa2,
0x26</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
NVMe device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.37</td>
<td>0x252df981, 0x416a, 0x486d, 0x8c, 0x78, 0xde, 0xae, 0x72, 0x4a,
0x68, 0xeb</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
BMC device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.38</td>
<td>0x77cdae2c, 0x642c, 0x4113, 0xb6, 0x59, 0x25, 0x23, 0x42, 0xb1,
0x16, 0xb6</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
RamDisk device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.39</td>
<td>0xd823b4b, 0x58b4, 0x4882, 0x9f, 0x38, 0xb, 0xfb, 0x3, 0xa0, 0x29,
0xa3</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
Uri device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.40</td>
<td>0x4136553e, 0x8284, 0x409c, 0x90, 0x56, 0xcb, 0xbc, 0x91, 0xc5,
0xea, 0xa1</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
SD device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.41</td>
<td>0x23bcd190, 0x10b4, 0x4063, 0x95, 0x2, 0xea, 0x5c, 0x14, 0xfc, 0x72,
0x1e</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
BlueTooth device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.7.1.42</td>
<td>0x6faccc19, 0x7785, 0x49e6, 0xaf, 0x86, 0x9b, 0x5f, 0x69, 0x53,
0x60, 0x7d</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
Wi-Fi device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.7.1.43</td>
<td>0x60e2e2ac, 0xf5f9, 0x4ecf, 0xac, 0xb1, 0x79, 0xa1, 0xe5, 0xcc,
0xbc, 0xf6</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDeviceNodeToText -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string</td>
<td><p>1. Set a text string to describe the
eMMC device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
</tbody>
</table>

### ConvertDevicePathToText Coverage

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.7.2.1</td>
<td>0x4af4f3cb, 0x4afa, 0x43b5, 0xb3, 0x83, 0x2e, 0x08, 0x57, 0x15,
0xf7, 0xa6</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertDevicePathToText -ConvertDevicePathToText()</strong> must recover the conversion
that <strong>ConvertTextToDevicePath()</strong> has performed on the
device node string.</td>
<td><p>1. Set a text string to describe a device path with multiple
device path instances.</p>
<p>2. Call <strong>ConvertTextToDevicePath()</strong>.</p>
<p>3. Call <strong>ConvertDevicePathToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
</tbody>
</table>

## Device Path From Text Protocol Interface Function Test

### ConvertTextToDeviceNode Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.8.1.1</td>
<td>0x6ea38cc6, 0x6b02, 0x4ee7, 0x84, 0xcc, 0x37, 0xc0, 0x07, 0x55,
0xef, 0xa3</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode -ConvertTextToDeviceNode()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the PCI Root device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
<tr class="odd">
<td>5.4.8.1.2</td>
<td>0xe025cd1b, 0xda51, 0x4496, 0xac, 0xa0, 0xf6, 0x18, 0x3e, 0x67,
0xb6, 0x78</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode -ConvertTextToDeviceNode()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the PCI device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
<tr class="even">
<td>5.4.8.1.3</td>
<td>0xe924b842, 0x2e27, 0x4d39, 0x98, 0x7d, 0x3a, 0x64, 0xd7, 0x45,
0x0e, 0xda</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode -ConvertTextToDeviceNode()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the ATAPI device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
</tbody>
</table>

### ConvertTextToDevicePath Functionality

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.8.2.1</td>
<td>0xa2215ca2, 0x965a, 0x4ae3, 0xae, 0x58, 0xca, 0xd1, 0x20, 0xb3,
0xf5, 0x87</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevicePath -ConvertTextToDevicePath()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the legacy floppy device
path.</p>
<p>2. Call <strong>ConvertTextToDevicePath()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
<tr class="odd">
<td>5.4.8.2.2</td>
<td>0x34dcb77c, 0x782f, 0x429a, 0x92, 0xfc, 0xa0, 0x02, 0xae, 0xfb,
0xcb, 0xd7</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevicePath -ConvertTextToDevicePath()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the IDE disk device path.</p>
<p>2. Call <strong>ConvertTextToDevicePath()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
<tr class="even">
<td>5.4.8.2.3</td>
<td>0xbf4b5c33, 0x7cc4, 0x412b, 0xb6, 0x88, 0x14, 0x0a, 0x17, 0x3f,
0x4f, 0x5a</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevicePath -ConvertTextToDevicePath()</strong> must set a device node
structure.</td>
<td><p>1. Set a text string to describe the secondary root PCI bus with
a PCI to PCI bridge device path.</p>
<p>2. Call <strong>ConvertTextToDevicePath()</strong>.</p>
<p>3. The return structure should be the same as the expected
one.</p></td>
</tr>
</tbody>
</table>

## Device Path From Text Protocol Interface Conformance Test

### ConvertTextToDeviceNode Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 27%" />
<col style="width: 42%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.9.1.1</td>
<td>0x112d380b, 0x1f72, 0x41d4, 0xa3, 0x5a, 0xd3, 0x61, 0x72, 0xce,
0x42, 0x60</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode -ConvertTextToDeviceNode()</strong> should return
<strong>NULL</strong> with <em>TextDeviceNode</em> set to
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>ConvertTextToDeviceNode()</strong> with a
<em>TextDeviceNode</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

### ConvertTextToDevicePath Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 27%" />
<col style="width: 42%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.9.2.1</td>
<td>0x6de40774, 0x269d, 0x4c52, 0x9e, 0xce, 0xe4, 0x01, 0x95, 0xc4,
0x09, 0xed</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL</strong>.
<strong>ConvertTextToDevicePath - ConvertTextToDevicePath()</strong>
should return <strong>NULL</strong> with <em>TextDevicePath</em> set to
be <strong>NULL</strong>.</td>
<td><p>1. Call <strong>ConvertTextToDevicePath()</strong> with a
<em>TextDevicePath</em> value of <strong>NULL</strong>.</p>
<p>2. The return pointer should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>

## Device Path From Text Protocol Interface Coverage Test

### ConvertTextToDeviceNode Coverage

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 14%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.10.1.1</td>
<td>0xabd4778e, 0xc1c5, 0x4dcb, 0xa5, 0x75, 0x4a, 0x2e, 0x83, 0x68,
0x01, 0x82</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe PcCard device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the one originally
set.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.2</td>
<td>0x384a0f7f, 0x3aed, 0x4942, 0xbf, 0x29, 0xed, 0x70, 0x7c, 0xb8,
0x96, 0xc3</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Memory Mapped device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.3</td>
<td>0x5ea2ddfd, 0xd264, 0x46d5, 0x99, 0x97, 0x17, 0xb2, 0x36, 0xe4,
0x46, 0xee</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Vendor defined device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original
onet.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.4</td>
<td>0xeeaad308, 0x9461, 0x42dc, 0x95, 0x2a, 0x25, 0xe3, 0xfb, 0x34,
0xc6, 0x4d</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Controller device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.5</td>
<td>0x5adc74cf, 0x0a05, 0x4689, 0xa0, 0xd0, 0xf3, 0x71, 0x10, 0x05,
0x24, 0xf4</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the ACPI Expended device path
node.</p>
<p>1. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.6</td>
<td>0xac15c6df, 0x10f5, 0x40f1, 0x9e, 0xdc, 0x16, 0xa4, 0x22, 0x86,
0xe2, 0xae</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a shortcut form of text string to describe the ACPI
Expended device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.7</td>
<td>0xd6769fb3, 0x6f40, 0x441e, 0xbc, 0x16, 0xdb, 0xab, 0xc5, 0x1f,
0xbc, 0x8e</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the SCSI device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.8</td>
<td>0x5a6105d4, 0x6c72, 0x4842, 0xbb, 0xf9, 0x16, 0xb4, 0x63, 0xc5,
0x65, 0x21</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Fibre Channel device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.9</td>
<td>0x370abd68, 0xd84c, 0x4247, 0xbd, 0xbd, 0xb4, 0xbc, 0x2a, 0x1f,
0x74, 0x9d</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the 1394 device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.10</td>
<td>0x4b30ff6b, 0x0495, 0x4a88, 0x89, 0x24, 0xed, 0x47, 0xb4, 0x70,
0x3a, 0xea</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the USB device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.11</td>
<td>0x7c010d41, 0x940f, 0x4ab7, 0x99, 0xb3, 0x56, 0x29, 0xfe, 0xe2,
0xb3, 0xe8</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the I2O device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.12</td>
<td>0x3aff77da, 0x5f86, 0x4145, 0x84, 0xfa, 0x7e, 0x24, 0x64, 0x1a,
0xef, 0x67</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Infiniband device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.13</td>
<td>0x57945d65, 0x2cd1, 0x44cb, 0x95, 0xa2, 0x85, 0x3d, 0x6b, 0x45,
0xc2, 0x10</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has peformed on the device
node string.</td>
<td><p>1. Set a text string to describe the PC-ANSI device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.14</td>
<td>0x99fe3cd1, 0x9015, 0x4995, 0xb9, 0x6c, 0x03, 0x37, 0x1c, 0xc0,
0x26, 0xc5</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the UartFlowCtrl device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.15</td>
<td>0xbe92f84c, 0x3922, 0x426b, 0xa0, 0x2a, 0x1b, 0x1b, 0xeb, 0xf9,
0x9d, 0x7c</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the SAS device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.16</td>
<td>0x453b6f77, 0xd3bf, 0x4f23, 0x80, 0x35, 0x0f, 0x61, 0xdf, 0xe0,
0x16, 0xe1</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the DebugPort device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.17</td>
<td>0xdc026cfc, 0xc681, 0x43af, 0xb3, 0x73, 0xed, 0x8c, 0x1f, 0x7e,
0xaa, 0x6d</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the MAC device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original
onet.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.18</td>
<td>0x94dca74e, 0xacdd, 0x4fc2, 0xab, 0xb8, 0x48, 0xb1, 0x1b, 0xe0,
0x77, 0x57</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the IPv4 device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.19</td>
<td>0x447fabae, 0x7a70, 0x43df, 0x9f, 0x07, 0xc3, 0x07, 0x85, 0x24,
0x87, 0xd5</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the IPv6 device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.20</td>
<td>0xba0fc861, 0xd2ce, 0x4c70, 0x8b, 0xec, 0xaa, 0x89, 0xbc, 0x7d,
0x11, 0x0f</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe UART device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.21</td>
<td>0x2eba02bb, 0xa904, 0x4949, 0xa4, 0x6a, 0x41, 0x1f, 0xd8, 0xa8,
0xdd, 0xaf</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe USB Class device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as theoriginal one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.22</td>
<td>0x50cf1d50, 0xb560, 0x4a1a, 0x96, 0xc2, 0x01, 0x10, 0xf1, 0x25,
0xe3, 0x53</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the USB Video device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original
onet.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.23</td>
<td>0xd77e99e4, 0xe619, 0x4773, 0xa4, 0xa0, 0xbe, 0x55, 0x21, 0x4b,
0x01, 0xf0</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the UsbTest And Measurement
device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original
onet.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.24</td>
<td>0xe5490e03, 0x83be, 0x4642, 0x98, 0xc5, 0x26, 0xae, 0x4f, 0xa4,
0x5d, 0xe4</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the AcpiAdr device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.25</td>
<td>0xe1042ce4, 0x760e, 0x433d, 0xb1, 0x7b, 0x9d, 0x02, 0x14, 0xf3,
0x2a, 0x12</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Logical Unit device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.26</td>
<td>0x1e3c0327, 0x7081, 0x4b7f, 0xab, 0xfa, 0xff, 0x01, 0xc2, 0x8c,
0xbe, 0x3f</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the iSCSI device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.27</td>
<td>0x37beed32, 0x165b, 0x480a, 0x91, 0x9b, 0xf5, 0xf2, 0x46, 0x07,
0xc7, 0x11</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Hard Drive with GUID device
path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.28</td>
<td>0x20884e00, 0x4471, 0x4e65, 0x84, 0xae, 0x51, 0x5d, 0x92, 0xc1,
0xe4, 0xf6</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Hard Drive with MBR device
path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.29</td>
<td>0xfdca47e4, 0x9965, 0x41dc, 0xbb, 0x01, 0x19, 0x10, 0x54, 0x41,
0x69, 0x60</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the covnersion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the CD-ROM device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.30</td>
<td>0xa0fc2a05, 0x01e1, 0x4a96, 0xb8, 0x8d, 0xa7, 0x73, 0x33, 0x25,
0xaf, 0x6e</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the File Path device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.31</td>
<td>0x0a0fc261, 0x193b, 0x4136, 0x82, 0xe3, 0x41, 0x32, 0x62, 0x36,
0xc6, 0x10</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Media device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.32</td>
<td>0xb59ff699, 0x4dc5, 0x45b8, 0x8b, 0xe6, 0x25, 0x36, 0x2e, 0xda,
0x59, 0xf3</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the BBS path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.33</td>
<td>0x2379a6e4, 0x3b61, 0x471c, 0x87, 0xb9, 0xff, 0xe6, 0x6a, 0x98,
0x79, 0x13</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Media Relative Offset Range
device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.34</td>
<td>0x74f16d4f, 0xcbc4, 0x42f0, 0x99, 0x16, 0xae, 0x35, 0xa6, 0xd7,
0x5e, 0xb7</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Vlan device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.35</td>
<td>0xa6a5af57, 0xca9b, 0x42c1, 0x9b, 0xcd, 0xe3, 0xdb, 0xdf, 0x2, 0xf3,
0x8b</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the PciRoot device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.36</td>
<td>0x850d81ee, 0xe3d5, 0x468f, 0x83, 0x80, 0x25, 0x3e, 0xcb, 0xeb,
0xf2, 0x07</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the PcieRoot device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.37</td>
<td>0x1f72c17d, 0x9f1a, 0x4f57, 0xac, 0xb5, 0x2b, 0xfb, 0x3d, 0xe, 0x5b,
0x67</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Floppy device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.38</td>
<td>0x64dbbe77, 0x819e, 0x4cd9, 0x90, 0x88, 0xd9, 0x3d, 0x8f, 0x99, 0x9,
0x33</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Keyboard device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.39</td>
<td>0x62970cad, 0xb9ae, 0x459e, 0x94, 0xc7, 0x97, 0x37, 0x3, 0xc5, 0xda,
0x43</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Serial device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.40</td>
<td>0x2c0e3e0c, 0x28f4, 0x4284, 0xbb, 0x54, 0x4, 0x2b, 0x6b, 0x26, 0xd3,
0x4e</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the Parallel Port device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.41</td>
<td>0x826c2efe, 0xc377, 0x4594, 0x99, 0x42, 0xe1, 0xef, 0x07, 0x5d,
0xd1, 0x2f</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the FIbreEx device path
node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.42</td>
<td>0xad957706, 0xb29a, 0x4184, 0xb8, 0x42, 0xf6, 0xf1, 0xa4, 0xe0,
0x57, 0x9b</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDeviceNode - ConvertDeviceNodeToText()</strong>
must recover the conversion that
<strong>ConvertTextToDeviceNode()</strong> has performed on the device
node string.</td>
<td><p>1. Set a text string to describe the SasEx device path node.</p>
<p>2. Call <strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call <strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.43</td>
<td>0x5fda2be2, 0x242a, 0x4c81, 0xa9, 0x7c, 0xfb, 0x2e, 0xe9, 0x94,
0x14, 0xf6</td>
<td><p>EFI_DEVICE_PATH_FR</p>
<p>OM_TEXT_PROTOCOL.</p>
<p>ConvertTextToDevic</p>
<p>eNode -</p>
<p>ConvertDeviceNodeT</p>
<p><strong>oText()</strong> must recover</p>
<p>the conversion that</p>
<p>ConvertTextToDevic</p>
<p><strong>eNode()</strong> has performed</p>
<p>on the device node</p>
<p>string.</p></td>
<td><p>1. Set a text string to describe the NVM express device path
node.</p>
<p>2. Call</p>
<p><strong>ConvertTextToDeviceNode()</strong>.</p>
<p>3. Call</p>
<p><strong>ConvertDeviceNodeToText()</strong>.</p>
<p>4. The return string should be the</p>
<p>same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.44</td>
<td>0x6bc6e55b, 0xaa2c, 0x4853, 0x88, 0xbd, 0x7e, 0x79, 0xc8, 0xd3,
0xae, 0x58</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
BMC device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.45</td>
<td>0x177fd920, 0xb733, 0x4841, 0x9a, 0x10, 0xdb, 0x7b, 0x37, 0x4b,
0x47, 0x7c</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
UFS device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.46</td>
<td>0x84e9f8, 0x6b65, 0x48e1, 0x92, 0x32, 0x4, 0x6e, 0xb4, 0x56, 0xd1,
0xe3</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
SD device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.47</td>
<td>0x25c2071e, 0xedc, 0x403f, 0x89, 0x4a, 0xa4, 0x84, 0x25, 0xcc, 0xca,
0x80</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
Bluetooth device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.48</td>
<td>0x84a73ccc, 0x2468, 0x440a, 0x93, 0xa1, 0xe2, 0x37, 0x35, 0xe5,
0x9f, 0x66</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
Wi-Fi device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.49</td>
<td>0x671ecea, 0x309c, 0x4398, 0x8c, 0x1, 0xed, 0x15, 0x37, 0xed, 0xaa,
0x40</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
RamDisk device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="odd">
<td>5.4.10.1.50</td>
<td>0x7e00edfb, 0x4ef8, 0x45da, 0x9e, 0x54, 0x8e, 0xf, 0x1b, 0xa5, 0xc3,
0xde</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
Uri device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
<tr class="even">
<td>5.4.10.1.51</td>
<td>0x882a6001, 0xae82, 0x4bb5, 0x83, 0xd, 0x6c, 0x2a, 0xd7, 0x68, 0x44,
0xec</td>
<td>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevic
eNode -
ConvertDeviceNodeToText() must recover
the conversion that
ConvertTextToDevic
eNode() has performed
on the device node
string.</td>
<td><p>1. Set a text string to describe the
eMMC device path node.</p><p>
2. Call
ConvertTextToDeviceNode().</p><p>
3. Call
ConvertDeviceNodeToText().</p><p>
4. The return string should be the
same as the original one.</p></td>
</tr>
</tbody>
</table>

### ConvertTextToDevicePath Coverage

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 14%" />
<col style="width: 28%" />
<col style="width: 41%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.4.10.2.1</td>
<td>0x1759828d, 0x3377, 0x4473, 0x84, 0x8a, 0x1a, 0x92, 0x6f, 0x2e,
0x5b, 0xc5</td>
<td><strong>EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL.ConvertTextToDevicePath -ConvertDevicePathToText()</strong> must recover the conversion
that <strong>ConvertTextToDevicePath()</strong> has performed on the
device node string.</td>
<td><p>1. Set a text string to describe a device path with multiple
device path instances.</p>
<p>2. Call <strong>ConvertTextToDevicePath()</strong>.</p>
<p>3. Call <strong>ConvertDevicePathToText()</strong>.</p>
<p>4. The return string should be the same as the original one.</p></td>
</tr>
</tbody>
</table>