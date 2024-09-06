# Protocols SCSI Bus Support Test

## EFI_SCSI_IO_PROTOCOL Function Test

**Reference Document:**

*UEFI Specification*, EFI_SCSI_IO_PROTOCOL Section..

### GetDeviceType() Function

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
<td>5.9.2.1.1</td>
<td>0xa9b53582, 0xcbd5, 0x4934, 0x85, 0x95, 0x2e, 0x4d, 0xc6, 0x8a,
0xb1, 0x34</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.GetDeviceType</strong> –
<strong>GetDeviceType()</strong> should return
<strong>EFI_SUCCESS</strong> with SCSI device correctly installed</td>
<td><p>Call <strong>GetDeviceType()</strong>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



### GetDeviceLocation() Function

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
<td>5.9.2.2.1</td>
<td>0x2d1db8e2, 0xb4d3, 0x4bbf, 0x80, 0xa6, 0x4c, 0x15, 0xef, 0x54,
0x87, 0x31</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.GetDeviceLocation</strong> –
<strong>GetDeviceLocation()</strong> should return
<strong>EFI_SUCCESS</strong> after setting <em>Target</em> and
<em>Lun</em>.</td>
<td><p>Call <strong>GetDeviceLocation()</strong> with valid
<em>Target</em> and <em>Lun</em>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>


### ResetBus() Function

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
<td>5.9.2.3.1</td>
<td>0xb11aec12, 0x0ffb, 0x46da, 0x82, 0x37, 0xaa, 0xa0, 0xed, 0x46,
0x29, 0x05</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.ResetBus - ResetBus()</strong> should
return <strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong>
with SCSI device correctly installed.</td>
<td><p>Call <strong>ResetBus()</strong> after SCSI device correctly
installed.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>


### ResetDevice() Function

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
<td>5.9.2.4.1</td>
<td>0x05720e96, 0xf8ab, 0x46f5, 0xbc, 0xf9, 0xc9, 0x24, 0x51, 0x1c,
0xd5, 0x44</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.ResetDevice</strong> -
<strong>ResetDevice()</strong> should return
<strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong> with
SCSI device correctly installed.</td>
<td><p>Call <strong>ResetDevice()</strong> after SCSI device correctly
installed.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### ExecuteScsiCommand () Function

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
<td>5.9.2.5.1</td>
<td>0xaf88a458, 0xdeab, 0x4744, 0xae, 0xf5, 0xe4, 0x1c, 0xb1, 0x0e,
0xbb, 0xb3</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand</strong> - Invokes
<strong>ExecuteScsiCommand()</strong> with <strong>NULL</strong>
<em>Event</em> will verify interface correctness by returning
<strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>ExecuteScsiCommand ()</strong> with
<strong>NULL</strong> <em>Event</em>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.2.5.2</td>
<td>0x96789d65, 0x11e6, 0x4a2d, 0xbb, 0x5b, 0xe3, 0x3d, 0x22, 0x6b,
0x28, 0xf1</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.ExecuteScsiCommand</strong> - Invokes
<strong>ExecuteScsiCommand</strong> <strong>()</strong> with
<em>Event</em> verifies interface correctness.</td>
<td><p>Call <strong>ExecuteScsiCommand</strong> <strong>()</strong> with
<em>Event</em>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong> and the
event should be invoked.</p></td>
</tr>
</tbody>
</table>



## EFI_SCSI_IO_PROTOCOL Conformance Test

**Reference Document:**

*UEFI Specification*, EFI_SCSI_IO_PROTOCOL Section.

### GetDeviceType() Conformance

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
<td>5.9.3.1.1</td>
<td>0x37a8da14, 0x170a, 0x4620, 0xaa, 0xea, 0x26, 0x6f, 0x35, 0x8f,
0x0c, 0x75</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.GetDeviceType</strong> –
<strong>GetDeviceType()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with <em>DeviceType</em> set
<strong>NULL</strong>.</td>
<td><p>Call <strong>GetDeviceType()</strong> with a <em>DeviceType</em>
value of <strong>NULL</strong>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### GetDeviceLocation() Conformance

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
<td>5.9.3.2.1</td>
<td>0x6937c784, 0xb044, 0x4828, 0xb8, 0x77, 0xff, 0xc7, 0x35, 0x8f,
0xf2, 0xaa</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.GetDeviceLocation</strong> –
<strong>GetDeviceLocation()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with <em>Target</em> set
<strong>NULL</strong>.</td>
<td><p>Call <strong>GetDeviceLocation ()</strong> with a <em>Target</em>
value of <strong>NULL</strong>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.3.2.2</td>
<td>0x6a48edf9, 0x8a3b, 0x4e9c, 0xb7, 0x6f, 0x37, 0x45, 0x83, 0xc7,
0xdc, 0x2b</td>
<td><strong>EFI_SCSI_IO_PROTOCOL.GetDeviceLocation</strong> –
<strong>GetDeviceLocation()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with <em>Lun</em> set
<strong>NULL</strong>.</td>
<td><p>Call <strong>GetDeviceLocation ()</strong> with a <em>Lun</em>
value of <strong>NULL</strong>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### ExecuteScsiCommand () Conformance

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
<td>5.9.3.3.1</td>
<td>0x17503bd1, 0x4d36, 0x4183, 0x9f, 0xf1, 0x9d, 0x0f, 0xc2, 0x21,
0x33, 0x26</td>
<td><strong>EFI_SCSI_IO_PROTOCOL. ExecuteScsiCommand</strong>
<strong>-</strong> Calling <strong>ExecuteScsiCommand</strong>
<strong>()</strong> with an too long <em>InTransferLength</em> value and
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_BAD_BUFFER_SIZE</strong>.</td>
<td><p>Call <strong>ExecuteScsiCommand</strong> <strong>()</strong> with
an <em>InTransferLength</em> value larger than the length which SCSI
controller can handle.</p>
<p>The return status should be <strong>EFI_BAD_BUFFER_SIZE</strong> and
<em>InTransferLength</em> will be updated to the length that SCSI
controller be able to handle.</p></td>
</tr>
<tr class="odd">
<td>5.9.3.3.2</td>
<td>0x8c27b8c2, 0x2c40, 0x4f6a, 0xbb, 0x54, 0x26, 0x5d, 0x12, 0x9a,
0x97, 0xce</td>
<td><strong>EFI_SCSI_IO_PROTOCOL. ExecuteScsiCommand</strong>
<strong>-</strong> Calling <strong>ExecuteScsiCommand</strong>
<strong>()</strong> with invalid <em>Packet</em> and
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>ExecuteScsiCommand</strong> <strong>()</strong> with
invalid <em>Packet</em> .</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.3.3.3</td>
<td>0xbeb81209, 0x808d, 0x46d1, 0xa2, 0x36, 0x23, 0x7f, 0x17, 0x22,
0x30, 0x37</td>
<td><strong>EFI_SCSI_IO_PROTOCOL. ExecuteScsiCommand</strong>
<strong>-</strong> Calling <strong>ExecuteScsiCommand</strong>
<strong>()</strong> with an too long <em>InTransferLength</em> value and
no <strong>NULL</strong> <em>Event</em> returns
<strong>EFI_BAD_BUFFER_SIZE</strong>.</td>
<td><p>Call <strong>ExecuteScsiCommand</strong> <strong>()</strong> with
an <em>InTransferLength</em> value larger than the length which SCSI
controller can handle.</p>
<p>The return status should be <strong>EFI_BAD_BUFFER_SIZE</strong> and
<em>InTransferLength</em> will be updated to the length that SCSI
controller be able to handle.</p></td>
</tr>
<tr class="odd">
<td>5.9.3.3.4</td>
<td>0x994fd5e2, 0x2d39, 0x4fa9, 0xa7, 0x4f, 0x8d, 0x09, 0xe0, 0xb6,
0x84, 0x1c</td>
<td><strong>EFI_SCSI_IO_PROTOCOL. ExecuteScsiCommand</strong>
<strong>-</strong> Calling <strong>ExecuteScsiCommand</strong>
<strong>()</strong> with invalid <em>Packet</em> and no
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>ExecuteScsiCommand</strong> <strong>()</strong> with
invalid <em>Packet</em> .</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


## EFI_EXT_SCSI_PASS_PROTOCOL Function Test 

**Reference Document:**

*UEFI Specification*, EFI_EXT_SCSI_PASS_THRU_PROTOCOL Section.

### GetNextTargetLun() Function

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
<td>5.9.4.1.1</td>
<td>0x4f658292, 0xa409, 0x4d67, 0xba, 0x13, 0x04, 0xc2, 0x51, 0x85,
0xf2, 0x80</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun</strong> –
<strong>GetNextTargetLun()</strong> retrieves the list of legal Target
IDs and LUNs for SCSI devices on a SCSI channel.</td>
<td><p>Call <strong>GetNextTargetLun ()</strong> with a <em>Target</em>
value of 0xFF’s to get the first SCSI device present on a SCSI
channel.</p>
<p>Use the values of <em>Target</em> and <em>Lun</em> values that are
returned to get the next SCSI device until the end.</p>
<p>Every call of <strong>GetNextTargetLun()</strong> should return
<strong>EFI_SUCCESS</strong> except the last one.</p>
<p>The last call should return <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
</tbody>
</table>



### BuildDevicePath() Function

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
<td>5.9.4.2.1</td>
<td>0x130d44b6, 0xce53, 0x42b6, 0x9b, 0xa6, 0x3d, 0x11, 0x5d, 0x49,
0x2b, 0x33</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath</strong> -
Invoking <strong>BuildDevicePath()</strong> will verify interface
correctness by returning <strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>GetNextTargetLun()</strong> to get the first
device’s <em>Target</em> and <em>Lun</em>.</p>
<p>Call <strong>BuildDevicePath()</strong> with a valid parameter. Free
the <em>DevicePath</em>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



### GetTargetLun() Function

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
<td>5.9.4.3.1</td>
<td>0x6ea827e4, 0x522c, 0x44b6, 0x99, 0xe4, 0x25, 0x93, 0x19, 0xba,
0xcc, 0x57</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun -</strong>
Invoking <strong>GetTargetLun()</strong> will verify interface
correctness by returning <strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>GetNextTargetLun()</strong> and
<strong>BuildDevicePath()</strong> to get the valid
<em>DevicePath</em>.</p>
<p>Use this <em>DevicePath</em> to call
<strong>GetTargetLun()</strong>.</p>
<p>The return value should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>


### ResetChannel() Function

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
<td>5.9.4.4.1</td>
<td>0x4e0080d2, 0x4065, 0x4b92, 0xa4, 0x61, 0x52, 0x49, 0xf3, 0x8f,
0xaf, 0x55</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetChannel</strong> -
Invoking <strong>ResetChannel()</strong> will verify interface
correctness via return code of <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</td>
<td><p>Call <strong>ResetChannel()</strong>.</p>
<p>The return value should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### ResetTargetLun() Function

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
<td>5.9.4.5.1</td>
<td>0x9400bc81, 0x9e48, 0x469b, 0xa0, 0x97, 0xd0, 0x08, 0x45, 0xb6,
0x69, 0xe8</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun</strong> -
Invoking <strong>ResetTargetLun()</strong> will verify interface
correctness via return code of <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</td>
<td><p>Call <strong>GetNextTargetLun()</strong> to get valid
<em>Target</em> and <em>Lun</em>.</p>
<p>Use the <em>Target</em> and <em>Lun</em> values that are returned to
call <strong>ResetTargetLun()</strong>.</p>
<p>The return value should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### GetNextTarget () Function

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
<td>5.9.4.6.1</td>
<td>0xc89631f3, 0xbd59, 0x4959, 0xba, 0x10, 0x3f, 0xa9, 0x94, 0x62,
0x02, 0xdf</td>
<td><p><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.</strong></p>
<p><strong>GetNextTarget</strong> – <strong>GetNextTarget()</strong>
retrieves the list of legal Target IDs for SCSI devices on a SCSI
channel.</p></td>
<td><p>Call <strong>GetNextTarget ()</strong> with a <em>Target</em>
value of 0xFF’s to get the first SCSI device present on a SCSI
channel.</p>
<p>Use the <em>Target</em> value that is returned to get the next SCSI
device until the end.</p>
<p>Every call of <strong>GetNextTarget ()</strong> should return
<strong>EFI_SUCCESS</strong> except the last one.</p>
<p>The last call should return <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
</tbody>
</table>


### PassThru () Function

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
<td>5.9.4.7.1</td>
<td>0xdb7841b9, 0x2a4a, 0x45b1, 0xa9, 0x9f, 0x67, 0x7a, 0xb4, 0xcd,
0x79, 0xa2</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru</strong> - Invoking
<strong>PassThru()</strong> with <strong>NULL</strong> <em>Event</em>
will verify interface correctness by returning
<strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>GetNextDevice()</strong> to get valid
<em>Target</em> and <em>Lun</em> values.</p>
<p>Call <strong>PassThru()</strong>with the returned values of
<em>Target</em>, <em>Lun</em> , and a <strong>NULL</strong>
<em>Event</em>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.4.7.2</td>
<td>0x4787ed6f, 0xa984, 0x4b15, 0xb2, 0xf3, 0xa0, 0xd1, 0xb8, 0xce,
0x61, 0x89</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru</strong> - Invoking
<strong>PassThru()</strong> with <em>Event</em> will verify interface
correctness by returning <strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>GetNextDevice()</strong> to get valid
<em>Target</em> and <em>Lun</em> values.</p>
<p>Call <strong>PassThru()</strong>with the returned value of
<em>Target</em>, <em>Lun</em> and a <strong>Event</strong>.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong> and the
event should be invoked.</p></td>
</tr>
</tbody>
</table>



## EFI_EXT_SCSI_PASS_PROTOCOL Conformance Test 

**Reference Document:**

*UEFI Specification*, EFI_EXT_SCSI_PASS_THRU_PROTOCOL Section.

### GetNextTargetLun() Conformance

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
<td>5.9.5.1.1</td>
<td>0xaad50e59, 0x9423, 0x427d, 0xa7, 0x5d, 0x69, 0x1c, 0x90, 0xb7,
0xf9, 0x75</td>
<td><strong>EFI_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun</strong> - Call
<strong>GetNextTargetLun()</strong> with an invalid
<em>Target</em>.</td>
<td><p>Call <strong>GetNextTargetLun()</strong> with <em>Target</em>’s
all bits are 1 to get the first device.</p>
<p>Call <strong>GetNextTargetLun()</strong> with an invalid
<em>Target</em>.</p>
<p>It should return <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.1.2</td>
<td>0xb3e87aa1, 0x6e9c, 0x478f, 0x9b, 0xd5, 0x39, 0x50, 0x08, 0x01,
0x28, 0x96</td>
<td><strong>EFI_SCSI_PASS_THRU_PROTOCOL.GetNextTargetLun</strong> - Call
<strong>GetNextTargetLun()</strong> with an invalid <em>Lun</em>.</td>
<td><p>Call <strong>GetNextTargetLun()</strong> with <em>Target</em>‘s
all bits are 1 to get the first device.</p>
<p>Call <strong>GetNextTargetLun()</strong> with an invalid
<em>Lun</em>.</p>
<p>It should return <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### BuildDevicePath() Conformance

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
<td>5.9.5.2.1</td>
<td>0x942a0e01, 0x7b80, 0x46e4, 0xa7, 0x57, 0x86, 0xc4, 0xec, 0x53,
0xf4, 0xe4</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath</strong> -
Calling <strong>BuildDevicePath()</strong> with an invalid
<em>Target</em> returns <strong>EFI_NOT_FOUND</strong>.</td>
<td><p>Call <strong>BuildDevicePath()</strong> with an invalid
<em>Target</em>.</p>
<p>The return status should be <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.2.2</td>
<td>0x222f00c1, 0xf6bf, 0x41ed, 0xae, 0xfd, 0xaa, 0xc4, 0x8f, 0x3f,
0xa9, 0xdb</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath</strong> -
Calling <strong>BuildDevicePath()</strong> with invalid <em>Lun</em>
returns <strong>EFI_NOT_FOUND</strong>.</td>
<td><p>Call <strong>BuildDevicePath()</strong> with invalid
<em>Lun</em>.</p>
<p>The return status should be <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.5.2.3</td>
<td>0xc72e6a78, 0x5292, 0x4493, 0x90, 0x40, 0xb0, 0x44, 0x5a, 0x9c,
0x17, 0x14</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.BuildDevicePath</strong> -
Calling <strong>BuildDevicePath()</strong> with <strong>NULL</strong>
<em>DevicePath</em> returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>BuildDevicePath()</strong> with
<strong>NULL</strong> <em>DevicePath</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### GetTargetLun() Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
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
<td>5.9.5.3.1</td>
<td>0xff2f0849, 0x690b, 0x48ea, 0x8e, 0x35, 0x64, 0x36, 0x3f, 0xaa,
0x8c, 0x5c</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun -</strong>
Invoking <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>DevicePath</em> returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>DevicePath</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.3.2</td>
<td>0x6602bd0a, 0x1c05, 0x49e5, 0xa8, 0xd4, 0xc6, 0x03, 0x8c, 0x43,
0x9a, 0xf9</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun -</strong>
Invoking <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>Target</em> returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>Target</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.5.3.3</td>
<td>0x1b64d49a, 0x1f1b, 0x4610, 0xa2, 0x66, 0xde, 0x32, 0xa1, 0x07,
0x2b, 0x32</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun -</strong>
Invoking <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>Lun</em> returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetTargetLun()</strong> with <strong>NULL</strong>
<em>Lun</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.3.4</td>
<td>0xf7830eaf, 0xba30, 0x4224, 0xab, 0xc4, 0x42, 0x42, 0x8b, 0x7a,
0x04, 0x5d</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.GetTargetLun</strong> -
Calling <strong>GetTargetLun()</strong> with unsupported
<em>DevicePath</em> returns <strong>EFI_UNSUPPORTED</strong>.</td>
<td><p>Call <strong>GetTargetLun()</strong> with unsupported
<em>DevicePath</em>.</p>
<p>The return status should be
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>


### ResetTargetLun() Conformance

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 16%" />
<col style="width: 26%" />
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
<td>5.9.5.4.1</td>
<td>0x106ae2fc, 0x3f34, 0x4afe, 0x82, 0x44, 0x40, 0x27, 0x57, 0x60,
0x98, 0x31</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun</strong> -
Calling <strong>ResetTargetLun()</strong> with an invalid
<em>Target</em> returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetResetTargetLun()</strong> with an invalid
<em>Target</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.4.2</td>
<td>0xc9378047, 0x9b4b, 0x4abf, 0xaa, 0x6b, 0xe3, 0xcd, 0xb6, 0xc4,
0x19, 0x39</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.ResetTargetLun</strong> -
Calling <strong>ResetTargetLun()</strong> with an invalid <em>Lun</em>
returns <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetResetTargetLun()</strong> with an invalid
<em>Lun</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### GetNextTarget () Conformance

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
<td>5.9.5.5.1</td>
<td>0xb564ad60, 0x32ce, 0x4f5f, 0x86, 0x7a, 0xef, 0x9f, 0xef, 0x5e,
0x94, 0xa2</td>
<td><strong>EFI_SCSI_PASS_THRU_PROTOCOL.GetNextTarget</strong> - Call
<strong>GetNextTarget()</strong> with an invalid <em>Target</em></td>
<td><p>Call <strong>GetNextTarget()</strong> with an invalid
<em>Target</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### PassThru() Conformance

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
<td>5.9.5.6.1</td>
<td>0x6d6fcacd, 0x3463, 0x41c8, 0xa5, 0x01, 0xa2, 0x99, 0x40, 0x44,
0x59, 0xb8</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with an too long <em>InTransferLength</em>
and <strong>NULL</strong> <em>Event</em> returns
<strong>EFI_BAD_BUFFER_SIZE</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with an
<em>InTransferLength</em> larger than the SCSI controller can
handle.</p>
<p>The return status should be <strong>EFI_BAD_BUFFER_SIZE</strong> and
the <em>InTransferLength</em> will be updated to the length that SCSI
controller can handle.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.6.2</td>
<td>0x645295b5, 0xc36b, 0x4b23, 0xaf, 0xc7, 0xd4, 0xcc, 0xc0, 0x1d,
0xb6, 0x4f</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with an invalid <em>Target</em> and
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with an invalid
<em>Target</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.5.6.3</td>
<td>0x9f9489a2, 0x23f3, 0x4962, 0x9d, 0x8f, 0xd2, 0xc0, 0xa7, 0xcb,
0x2f, 0xb1</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Calling
PassThru()</strong> with an invalid <em>Lun</em> and
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with an invalid
<em>Lun</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.6.4</td>
<td>0xc584b074, 0xa8cd, 0x438c, 0xb5, 0x18, 0xb1, 0xec, 0x59, 0xfa,
0xc8, 0xee</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with invalid <em>Packet</em> content and
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with invalid <em>Packet</em>
content.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.5.6.5</td>
<td>0x3cd806fd, 0x3742, 0x44e9, 0xa6, 0x19, 0xdf, 0x2d, 0x37, 0x47,
0xe7, 0x8f</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with an too long <em>InTransferLength</em>
and no <strong>NULL</strong> <em>Event</em> returns
<strong>EFI_BAD_BUFFER_SIZE</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with an
<em>InTransferLength</em> larger than the SCSI controller can
handle.</p>
<p>The return status should be <strong>EFI_BAD_BUFFER_SIZE</strong> and
the <em>InTransferLength</em> will be updated to the length that SCSI
controller can handle.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.6.6</td>
<td>0x9648ab45, 0x898b, 0x4b44, 0xab, 0x9e, 0x24, 0x6b, 0xc6, 0x49,
0xc9, 0xfd</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with an invalid <em>Target</em> and no
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong></td>
<td><p>Call <strong>PassThru()</strong> with an invalid
<em>Target</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.9.5.6.7</td>
<td>0x8662da7d, 0x6f98, 0x4051, 0xb1, 0x87, 0x85, 0xb0, 0xf4, 0xb5,
0x3a, 0xf1</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru - Calling
PassThru()</strong> with an invalid <em>Lun</em> and no
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with an invalid
<em>Lun</em>.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.9.5.6.8</td>
<td>0xf9ec9bf2, 0x743f, 0x4eed, 0x82, 0xbc, 0x35, 0xf2, 0xcc, 0x56,
0x45, 0xda</td>
<td><strong>EFI_EXT_SCSI_PASS_THRU_PROTOCOL.PassThru -</strong> Calling
<strong>PassThru()</strong> with invalid <em>Packet</em> content and no
<strong>NULL</strong> <em>Event</em> returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>PassThru()</strong> with invalid <em>Packet</em>
content.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>

