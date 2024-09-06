# Protocols USB Support Test

## EFI_USB2_HC_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_USB2_HC_PROTOCOL Section.

Most of functionalities rely on the real USB devices. They are not
covered in below checkpoints.

### GetCapability()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.1.1.1 | 0xbe0fffbd, 0xc5cb, 0x4ab7, 0xa0, 0x8a, 0x79, 0xd1, 0x02, 0xb3, 0x5f, 0xf8 | **EFI_USB2_HC_PROTOCOL.** **GetCapability** - **GetCapability()** returns **EFI_INVALID_PARAMETER** with a *MaxSpeed* value of **NULL**. | 1\. Call **GetCapability()** with a *MaxSpeed* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.1.1.2 | 0x6dd53bd5, 0x463b, 0x46a7, 0xb0, 0x98, 0x06, 0xa6, 0xf6, 0xa5, 0x62, 0xdd | **EFI_USB2_HC_PROTOCOL.** **GetCapability** - **GetCapability ()** returns **EFI_INVALID_PARAMETER** with a *PortNumber* value of **NULL**. | 1\. Call **GetCapability ()** with a *PortNumber* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.1.1.3 | 0x0ffa5751, 0x96dd, 0x4a70, 0xa1, 0x01, 0x63, 0x66, 0x7b, 0x15, 0xcc, 0xf5 | **EFI_USB2_HC_PROTOCOL.** **GetCapability** - **GetCapability ()** returns **EFI_INVALID_PARAMETER** with an *Is64BitCapable* value of **NULL**. | 1\. Call **GetCapability ()** with an *Is64BitCapable* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |



### Reset()

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
<td>5.21.1.2.1</td>
<td>0xf8dd84cb, 0x72a2, 0x4cab, 0xac, 0x2e, 0x11, 0x6f, 0x3c, 0x0d,
0x5d, 0xb5</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with
<em>Attributes</em> values of
<strong>EFI_USB_HC_RESET_GLOBAL</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with <em>Attributes</em> values
of <strong>EFI_USB_HC_RESET_GLOBAL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of the USB host
controller. The controller should be in halt state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.2.2</td>
<td>0x3bdb0674, 0x621b, 0x4319, 0xb2, 0x4f, 0xc6, 0x1a, 0xd4, 0x09,
0x73, 0xd0</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with
<em>Attributes</em> values of
<strong>EFI_USB_HC_RESET_HOST_CONTROLLER</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with <em>Attributes</em> values
of <strong>EFI_USB_HC_RESET_HOST_CONTROLLER</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of the USB host
controller. The controller should be in halt state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.2.3</td>
<td>0xd243c0fd, 0x7654, 0x4400, 0xb3, 0x4a, 0xe3, 0x09, 0x8f, 0x9e,
0x5e, 0xd4</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with
<em>Attributes</em> values of <strong>EFI_USB_HC_RESET_GLOBAL |
EFI_USB_HC_RESET_HOST_CONTROLLER</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with <em>Attributes</em> values
of <strong>EFI_USB_HC_RESET_GLOBAL |
EFI_USB_HC_RESET_HOST_CONTROLLER</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of the USB host
controller. The controller should be in halt state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.2.4</td>
<td>0xa4f18be1, 0x15f2, 0x424f, 0xa6, 0xdb, 0x58, 0x6e, 0x0d, 0x54,
0x80, 0x25</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with
<em>Attributes</em> values of
<strong>EFI_USB_HC_RESET_GLOBAL_DEBUG</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with <em>Attributes</em> values
of <strong>EFI_USB_HC_RESET_GLOBAL_DEBUG</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of the USB host
controller. The controller should be in halt state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.2.5</td>
<td>0xe2df74c7, 0x7aea, 0x488c, 0xb9, 0xa2, 0x71, 0x94, 0xb2, 0x5f,
0xf3, 0x8b</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with
<em>Attributes</em> values of
<strong>EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an <em>Attributes</em>
value of <strong>EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG</strong>. The
return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of the USB host
controller. The controller should be in halt state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.2.6</td>
<td>0xda7ef15c, 0x01a4, 0x4004, 0x8c, 0x7a, 0x33, 0xc7, 0x89, 0x47,
0xd9, 0xfc</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_SUCCESS</strong> with an
<em>Attributes</em> value of <strong>EFI_USB_HC_RESET_GLOBAL_DEBUG |
EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an <em>Attributes</em>
value of <strong>EFI_USB_HC_RESET_GLOBAL_DEBUG |
EFI_USB_HC_RESET_HOST_CONTROLLER_DEBUG</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in halt state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.2.7</td>
<td>0xd2e6a8f0, 0x6c97, 0x4134, 0x81, 0x2e, 0x25, 0xf1, 0x75, 0x18,
0x6a, 0xe4</td>
<td><strong>EFI_USB2_HC_PROTOCOL.Reset</strong> -
<strong>Reset()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with an invalid <em>Attributes</em>.</td>
<td>1. Call <strong>Reset()</strong> with an invalid <em>Attributes</em>
value of 0. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>



### GetState()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 27%" />
<col style="width: 42%" />
</colgroup>
<tbody>
<tr class="odd">
<td>5.21.1.3.1</td>
<td>0x19be62be, 0xf20c, 0x4fa2, 0x89, 0xcc, 0x3a, 0x89, 0x39, 0x48,
0x4d, 0x86</td>
<td><strong>EFI_USB2_HC_PROTOCOL.GetState</strong> -
<strong>GetState()</strong> returns <strong>EFI_SUCCESS</strong> while
the host controller is in halt state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateHalt</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in halt state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.3.2</td>
<td>0xc2b1cb6a, 0x66b4, 0x4c6d, 0xb9, 0x0a, 0xc9, 0x5d, 0x27, 0xd6,
0xa5, 0xd1</td>
<td><strong>EFI_USB2_HC_PROTOCOL.GetState</strong> -
<strong>GetState()</strong> returns <strong>EFI_SUCCESS</strong> while
the host controller is in an operational state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateOperational</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in an Operational state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.3.3</td>
<td>0x95e913a0, 0x5ca9, 0x4edb, 0x92, 0x4f, 0xaa, 0x2f, 0x18, 0x9b,
0x57, 0x6a</td>
<td><strong>EFI_USB2_HC_PROTOCOL.GetState</strong> -
<strong>GetState()</strong> returns <strong>EFI_SUCCESS</strong> while
the host controller is in suspend state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateSuspend</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in Suspend state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.3.4</td>
<td>0xbc1b8f2e, 0xf1aa, 0x446f, 0x81, 0x78, 0x6e, 0x4e, 0xd5, 0x53,
0x02, 0x08</td>
<td><strong>EFI_USB2_HC_PROTOCOL.GetState</strong> -
<strong>GetState()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>State</strong>
value of <strong>NULL</strong>.</td>
<td>1. Call <strong>GetState()</strong> with a <em>State</em> value of
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>



### SetState()

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
<td>5.21.1.4.1</td>
<td>0x5d2282fe, 0xc37c, 0x4901, 0xbb, 0xf7, 0xf1, 0xb6, 0xf0, 0xae,
0x82, 0x91</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from halt to halt.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateHalt</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateHalt</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in halt state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.4.2</td>
<td>0x6f6e6713, 0x07dc, 0x4413, 0x85, 0x05, 0xee, 0x69, 0x9e, 0x32,
0x69, 0x27</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from halt state to operational state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateHalt</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateOperational</strong> again. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in an Operational state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.4.3</td>
<td>0x49ca37bc, 0x208d, 0x4feb, 0xa6, 0xd9, 0x68, 0xa3, 0x69, 0xca,
0xb3, 0xf1</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from halt state to suspend state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateHalt</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateSuspend</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in Suspend state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.4.4</td>
<td>0xa4663706, 0xd0c0, 0x45d7, 0x9a, 0x9d, 0x5e, 0x0e, 0xf8, 0xba,
0x2c, 0x26</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from operational state to operational state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateOperational</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateOperational</strong> again. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in an Operational state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.4.5</td>
<td>0xa9b73b45, 0xb3ca, 0x4579, 0x87, 0x38, 0xb3, 0xcc, 0xc4, 0x50,
0x09, 0x97</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from operational state to halt state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateOperational</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateHalt</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in halt state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.4.6</td>
<td>0x54936ebc, 0x9732, 0x4d9f, 0x83, 0x5c, 0x95, 0x77, 0xf5, 0xdb,
0x0e, 0xb1</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from operational state to suspend state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateOperational</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateSuspend</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in Suspend state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.4.7</td>
<td>0x9da57b17, 0x7841, 0x423a, 0xb1, 0xf8, 0x6d, 0x61, 0xf0, 0xd3,
0x17, 0xf0</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from suspend state to suspend state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateSuspend</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateSuspend</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in Suspend state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.4.8</td>
<td>0x5b4bf27e, 0xad64, 0x41a4, 0xa9, 0x8b, 0xd2, 0xb0, 0x7d, 0x32,
0xbb, 0xa3</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from suspend state to halt state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateSuspend</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateHalt</strong> again. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in halt state.</p></td>
</tr>
<tr class="even">
<td>5.21.1.4.9</td>
<td>0xc12e9ca0, 0x0e9c, 0x4204, 0xaa, 0xc3, 0x6d, 0x12, 0x33, 0x1b,
0x28, 0x9b</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns <strong>EFI_SUCCESS</strong> when
changing the state from suspend state to operational state.</td>
<td><p>1. Call <strong>SetState()</strong> with a <em>State</em> value
of <strong>EfiUsbHcStateSuspend</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetState()</strong> with a <em>State</em> value of
<strong>EfiUsbHcStateOperational</strong> again. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetState()</strong> to get the state of this USB host
controller. This controller should be in an Operational state.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.4.10</td>
<td>0x5168c4ef, 0x91f4, 0x48c5, 0x88, 0x1f, 0xf8, 0x01, 0x80, 0xd2,
0x98, 0x07</td>
<td><strong>EFI_USB2_HC_PROTOCOL.SetState</strong> -
<strong>SetState()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>State</strong>.</td>
<td><p>1. Call <strong>SetState()</strong> with an invalid
<em>State</em> value of <strong>-1</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>SetState()</strong> with an invalid <em>State</em>
value of <strong>EfiUsbHcStateMaximum</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>

### ControlTransfer()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>5.21.1.5.1</td>
<td>0x36308487, 0x3a2c, 0x48fa, 0x91, 0xed, 0xec, 0xc3, 0x59, 0xd0,
0x78, 0x46</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>TransferDirection</em>.</td>
<td><p>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>TransferDirection</em> value</p>
<p>(<strong>-1</strong>). The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>ControlTransfer()</strong> with an invalid
<em>TransferDirection</em> value (<strong>0x7FFFFFFF</strong><em>)</em>.
The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.5.2</td>
<td>0x26532efd, 0x62ab, 0x4d60, 0x9c, 0xd8, 0x14, 0xb7, 0x9d, 0x48,
0x8e, 0xa1</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a invalid
<em>Data</em> and <em>DataLength</em> values.</td>
<td><p>1. Call <strong>ControlTransfer()</strong> with an invalid
<strong>Data</strong> (value of<em>)</em> and <em>TransferDirection</em>
is either Efi<strong>UsbDataIn</strong> or
Efi<strong>UsbDataOut</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>ControlTransfer()</strong> with an invalid
<em>DataLength</em> (value of <strong>0</strong><em>)</em> and
<em>TransferDirection</em> is either Efi<strong>UsbDataIn</strong> or
Efi<strong>UsbDataOut</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>ControlTransfer()</strong> with an invalid
<em>Data</em> <strong>(</strong>not value of
<strong>NULL</strong><em>)</em> and <em>TransferDirection</em> value of
Efi<strong>UsbNoData</strong>.The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call <strong>ControlTransfer()</strong> with an invalid
<em>DataLength</em><strong>(</strong> value of
<strong>1</strong><em>)</em>and <em>TransferDirection</em> value of
Efi<strong>UsbNoData</strong>.The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.21.1.5.3</td>
<td>0x28f002fd, 0x3797, 0x46cb, 0xaf, 0x66, 0xd5, 0xb4, 0x27, 0x23,
0x1b, 0x7a</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an <em>Request</em>
value of <strong>NULL</strong>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>Request</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.5.4</td>
<td>0xddf99154, 0x12ea, 0x4c99, 0x9a, 0x49, 0x6a, 0x1c, 0x51, 0xc2,
0x7a, 0x77</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>MaximumPacketLength</em>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> ( value is not 8) when <em>DeviceSpeed</em>
is <strong>EFI_USB_SPEED_LOW</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.5.5</td>
<td>0xc258056b, 0x13ae, 0x4839, 0xbb, 0xda, 0xa0, 0x1f, 0x5c, 0x14,
0x0a, 0x51</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>MaximumPacketLength</em>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> (value of <strong>128</strong> not
<strong>8/16/32/64</strong>) when <em>DeviceSpeed</em> is
<strong>EFI_USB_SPEED_FULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.5.6</td>
<td>0x5f6973f9, 0x9d75, 0x4e26, 0x8a, 0x30, 0xb5, 0xc2, 0x0e, 0x47,
0xf0, 0xb3</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>MaximumPacketLength</em>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> (value of <strong>128</strong> not
<strong>8/16/32/64</strong>) when <em>DeviceSpeed</em> is
<strong>EFI_USB_SPEED_HIGH</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.5.7</td>
<td>0x66a39c82, 0xfb44, 0x4057, 0xbb, 0xd7, 0x4b, 0x24, 0x30, 0xff,
0x19, 0xa9</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>MaximumPacketLength</em>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> <em>(</em>value of <strong>256</strong> not
<strong>512</strong><em>)</em> when <em>DeviceSpeed</em> is
<strong>EFI_USB_SPEED_SUPER</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.5.8</td>
<td>0xf63896ea, 0x5143, 0x4b7a, 0x93, 0x51, 0x63, 0xb5, 0xb5, 0x95,
0x81, 0x5c</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ControlTransfer</strong> - <strong>ControlTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>TransferResult</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>ControlTransfer()</strong> with an invalid
<em>TransferResult</em> (value of <strong>NULL</strong>). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>


### BulkTransfer()

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
<td>5.21.1.6.1</td>
<td>0x0498c13e, 0xc21b, 0x4c4e, 0x95, 0xd2, 0x11, 0x9a, 0x10, 0x07,
0x51, 0x02</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>Data</em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>Data</em> value of <strong>NULL</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.6.2</td>
<td>0x2a1df585, 0xf82a, 0x42ab, 0x97, 0x4f, 0xfe, 0xfb, 0xf7, 0x89,
0xe6, 0xf5</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DataLength</em> value
of <strong>0</strong>.</td>
<td>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>DataLength</em> value of <strong>0</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.6.3</td>
<td>0x26ad2292, 0x449b, 0x4545, 0x80, 0xaa, 0x13, 0x39, 0x13, 0x15,
0x04, 0xf6</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DeviceSpeed</em> value
of <strong>EFI_USB_SPEED_LOW</strong>.</td>
<td>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>DeviceSpeed</em> value of <strong>EFI_USB_SPEED_LOW</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.6.4</td>
<td>0x1d89742e, 0xd026, 0x47d7, 0xa4, 0xcb, 0xe0, 0xb6, 0xd9, 0xc3,
0xd9, 0x54</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>MaximumPacketLength</em>.</td>
<td><p>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> (value of <strong>65</strong>) when
<em>DeviceSpeed</em> is <strong>EFI_USB_SPEED_FULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>BulkTransfer()</strong> with an invalid
<em>MaximumPacketLength</em> (value of <strong>513</strong>) when
<em>DeviceSpeed</em> is <strong>EFI_USB_SPEED_HIGH</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>BulkTransfer()</strong> with an</p>
<p>invalid <em>MaximumPacketLength</em> (value of <strong>1025</strong>)
when DeviceSpeed is <strong>EFI_USB_SPEED_SUPER</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.21.1.6.5</td>
<td>0xbc90875e, 0x0a8b, 0x4e3c, 0xbb, 0xf2, 0x5a, 0x43, 0x40, 0x3a,
0x6b, 0x05</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DataToggle</em> value
other than 0 and 1.</td>
<td>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>DataToggle</em> (value of <strong>2</strong><em>)</em>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.6.6</td>
<td>0x0dfea5a1, 0xf82a, 0x41a5, 0xbf, 0x67, 0xea, 0x89, 0xed, 0x74,
0x61, 0x21</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong> <strong>BulkTransfer</strong>
- <strong>BulkTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>TransferResult</em>
value of <strong>NULL</strong>.</td>
<td>1. Call <strong>BulkTransfer()</strong> with an invalid
<em>TransferResult</em> ( value of <strong>NULL</strong>). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>



### AsyncInterruptTransfer()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>5.21.1.7.1</td>
<td>0xec3427c4, 0xe4df, 0x4646, 0x8b, 0x63, 0xdc, 0x0b, 0x7d, 0xc0,
0x0d, 0xdd</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncInterruptTransfer</strong> - <strong>AsyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>EndPointAddress</em> value other than
<strong>EfiUsbDataIn</strong>.</td>
<td>1. Call <strong>AsyncInterruptTransfer</strong> <strong>()</strong>
with an <em>EndPointAddress</em> value other than
<strong>EfiUsbDataIn</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.7.2</td>
<td>0xc0cddbce, 0x4853, 0x4d71, 0xad, 0xe1, 0x59, 0x94, 0x90, 0x7c,
0x31, 0xcc</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncInterruptTransfer</strong> - <strong>AsyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a new,
invalid transfer.</td>
<td>1. Call <strong>AsyncInterruptTransfer</strong> <strong>()</strong>
with the <em>IsNewTransfer</em> value of <strong>TRUE</strong> and
<em>DataLength</em> value of <strong>0</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.7.3</td>
<td>0xaf26077c, 0x75e5, 0x4fbc, 0xad, 0x5e, 0x99, 0x3b, 0xce, 0x66,
0xb5, 0xc5</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncInterruptTransfer</strong> - <strong>AsyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a new,
invalid transfer.</td>
<td>1. Call <strong>AsyncInterruptTransfer</strong> <strong>()</strong>
with the <em>IsNewTransfer</em> value of <strong>TRUE</strong> and a
<em>DataToggle</em> value other than <strong>0</strong> and
<strong>1</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.7.4</td>
<td>0xccd35e94, 0x51db, 0x4118, 0xa8, 0xd4, 0x40, 0xbd, 0x2e, 0xee,
0x77, 0xd9</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncInterruptTransfer</strong> - <strong>AsyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with new,
invalid transfer.</td>
<td><p>1. Call <strong>AsyncInterruptTransfer</strong>
<strong>()</strong> with the <em>IsNewTransfer</em> value of
<strong>TRUE</strong> and <em>PollingInterval</em> value of
<strong>0</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>AsyncInterruptTransfer</strong> <strong>()</strong>
with the <em>IsNewTransfer</em> value of <strong>TRUE</strong> and
<em>PollingInterval</em> value of <strong>256</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



### SyncInterruptTransfer()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 14%" />
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
<td>5.21.1.8.1</td>
<td>0x509cb496, 0x1d63, 0x4faf, 0x8d, 0xdf, 0x00, 0xbc, 0x58, 0x05,
0x0d, 0xe6</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with the
<em>EndPointAddress</em> set other than
<strong>EfiUsbDataIn</strong>.</td>
<td>1. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with the <em>EndPointAddress</em> set other than
<strong>EfiUsbDataIn</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.8.2</td>
<td>0x3a0ad565, 0xb82c, 0x450f, 0xbc, 0xe6, 0x88, 0xb3, 0xd1, 0x6a,
0xde, 0x35</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>Data</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with a <em>Data</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.8.3</td>
<td>0xc139127a, 0x3797, 0x482f, 0xb3, 0x5c, 0xaa, 0xf7, 0x99, 0xbd,
0xf6, 0xc6</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>DataLength</em> value of <strong>0</strong>.</td>
<td>1. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with a <em>DataLength</em> value of 0. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.8.4</td>
<td>0x14cb206c, 0x422b, 0x47ee, 0x8c, 0x4b, 0xf3, 0x16, 0xfe, 0x33,
0xda, 0xfb</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with an
invalid <em>MaximumPacketLength</em>.</td>
<td><p>1. Call <strong>SyncInterruptTransfer</strong>
<strong>()</strong> with a <em>MaximumPacketLength</em> value of
<strong>9</strong> and <em>DeviceSpeed</em> value of
<strong>EFI_USB_SPEED_LOW</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with a <em>MaximumPacketLength</em> value of <strong>65</strong> and
<em>DeviceSpeed</em> value of <strong>EFI_USB_SPEED_FULL</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with a <em>MaximumPacketLength</em> value of <strong>3073</strong> and
<em>DeviceSpeed</em> value of <strong>EFI_USB_SPEED_HIGH</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.21.1.8.5</td>
<td>0xf4353439, 0x47e4, 0x4df3, 0x85, 0xe9, 0x9e, 0xfe, 0x72, 0x3a,
0x1e, 0x4b</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with
<em>DataToggle</em> pointing to a value other than <strong>0</strong>
and <strong>1</strong>.</td>
<td>1. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with <em>DataToggle</em> points to a value other than <strong>0</strong>
and <strong>1</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.8.6</td>
<td>0x81dfdb23, 0x681e, 0x4df7, 0xa7, 0x73, 0x6d, 0x41, 0x58, 0xdb,
0x88, 0x3e</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SyncInterruptTransfer</strong> - <strong>SyncInterruptTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>TransferResult</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>SyncInterruptTransfer</strong> <strong>()</strong>
with a <em>TransferResult</em> value of <strong>NULL</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>


### IsochronousTransfer()

<table>
<colgroup>
<col style="width: 13%" />
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
<td>5.21.1.9.1</td>
<td>0x74e2dcbf, 0xae9f, 0x4499, 0x82, 0x74, 0xcb, 0xbe, 0x86, 0x59,
0x5d, 0xb7</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>IsochronousTransfer</strong> - <strong>IsochronousTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>Data</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>IsochronousTransfer</strong> <strong>()</strong>
with a <em>Data</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.9.2</td>
<td>0xd93babd4, 0xd7de, 0x4e87, 0x9b, 0x5c, 0x68, 0xd2, 0xa6, 0x77,
0x33, 0xc4</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>IsochronousTransfer</strong> - <strong>IsochronousTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>DataLength</em> value of <strong>0</strong>.</td>
<td>1. Call <strong>IsochronousTransfer</strong> <strong>()</strong>
with a <em>DataLength</em> value of <strong>0</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.9.3</td>
<td>0x9b220909, 0x662c, 0x4b5e, 0x9e, 0x42, 0xdc, 0x66, 0x4c, 0xdb,
0xb1, 0x5f</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>IsochronousTransfer</strong> - <strong>IsochronousTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>MaxiumPacketLenth</em> set larger than <strong>1023</strong>.</td>
<td>1. Call <strong>IsochronousTransfer</strong> <strong>()</strong>
with a <em>MaxiumPacketLenth</em> value of <strong>1024</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.9.4</td>
<td>0x68898a17, 0x5ae9, 0x456a, 0xb1, 0xe0, 0xa3, 0xc0, 0x42, 0xeb,
0x50, 0x8d</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>IsochronousTransfer</strong> - <strong>IsochronousTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>TransferResult</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>IsochronousTransfer</strong> <strong>()</strong>
with a <em>TransferResult</em> value of <strong>NULL</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.9.5</td>
<td>0xfa4f5868, 0xf004, 0x4cbe, 0x88, 0x97, 0xfd, 0x6, 0xb2, 0x72, 0x76,
0x71</td>
<td id="efi_usb2_hc_procotol.isochronoustransfer"
class="unnumbered">EFI_USB2_HC_PROCOTOL.IsochronousTransfer IsochronousTransfer () returns
EFI_INVALID_PARAMETER
<p>when <em>DeviceSpeed</em> is not one of the supported
values.</p></td>
<td><strong>IsochronousTransfer()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>DeviceSpeed</em> is not
one of the supported values.</td>
</tr>
</tbody>
</table>



### AsyncIsochronousTransfer()

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
<td>5.21.1.10.1</td>
<td>0x55a7ea0c, 0x9ffc, 0x47dc, 0xb7, 0x5e, 0x5c, 0xfa, 0x8c, 0xed,
0xe1, 0x53</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncIsochronousTransfer</strong> -
<strong>AsyncIsochronousTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>Data</em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>AsyncIsochronousTransfer</strong>
<strong>()</strong> with a <em>Data</em> value of <strong>NULL</strong>.
The return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.10.2</td>
<td>0xfa310dd6, 0x4b8a, 0x4799, 0xa5, 0xdc, 0x80, 0xe7, 0xbb, 0xe0,
0x4e, 0xac</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncIsochronousTransfer</strong> -
<strong>AsyncIsochronousTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DataLength</em> value
of <strong>0</strong>.</td>
<td>1. Call <strong>AsyncIsochronousTransfer</strong>
<strong>()</strong> with a <em>DataLength</em> value of
<strong>0</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.1.10.3</td>
<td>0x4083742a, 0x6c43, 0x49b4, 0x8d, 0xe1, 0x7a, 0xf8, 0x0c, 0x8b,
0x02, 0x33</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>AsyncIsochronousTransfer</strong> -
<strong>AsyncIsochronousTransfer ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>MaxiumPacketLenth</em>
value of larger than <strong>1023</strong>.</td>
<td>1. Call <strong>AsyncIsochronousTransfer</strong>
<strong>()</strong> with a <em>MaxiumPacketLenth</em> value of 1024. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.1.10.4</td>
<td>0x474590c4, 0x8410, 0x4871, 0x93, 0xb4, 0x2b, 0xe, 0x9f, 0xb5, 0xe8,
0x30</td>
<td
id="usb2_hc_procotol.asyncisochronoustransfer-asyncisochronoustransfer-returns-efi_invalid_parameterwhen-devicespeed-is-not-one-of-the-supported-values."
class="unnumbered">USB2_HC_PROCOTOL.AsyncIsochronousTransfer
–AsyncIsochronousTransfer () returns EFI_INVALID_PARAMETERwhen
<em>DeviceSpeed</em> is not one of the supported values.</td>
<td><strong>AsyncIsochronousTransfer()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>DeviceSpeed</em> is not
one of the supported values.</td>
</tr>
</tbody>
</table>



### GetRootHubPortStatus()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>5.21.1.11.1</td>
<td>0x089705c5, 0xf134, 0x42b4, 0xbd, 0xeb, 0x7a, 0x74, 0xc7, 0x93,
0xa0, 0xf5</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>GetRootHubPortStatus</strong> - <strong>GetRootHubPortStatus
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with an
invalid <em>PortNumber</em>.</td>
<td><p>1. Call <strong>GetCapability()</strong> to get the number of
ports. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetRootHubPortStatus()</strong> with
<em>PortNumber</em> greater than the number of ports. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



### SetRootHubPortFeature()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 26%" />
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
<td>5.21.1.12.1</td>
<td>0xf74da277, 0x4ac2, 0x422c, 0x90, 0xda, 0xb4, 0x9f, 0xc7, 0x4f,
0x2a, 0x65</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SetRootHubPortFeature</strong> - <strong>SetRootHubPortFeature
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with an
invalid <em>PortNumber</em>.</td>
<td><p>1. Call <strong>GetRootHubPortNumber ()</strong> to get the
number of ports. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetRootHubPortFeature()</strong> with a
<em>PortNumber</em> greater than the number of ports. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.12.2</td>
<td>0xd7071255, 0x61db, 0x446a, 0xad, 0x65, 0x01, 0xb4, 0x54, 0x72,
0x1f, 0x80</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>SetRootHubPortFeature</strong> - <strong>SetRootHubPortFeature
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with an
invalid <em>PortFeature</em>.</td>
<td><p>1. Call <strong>GetRootHubPortNumber ()</strong> to get the
number of ports. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetRootHubPortFeature()</strong> with a
<em>PortFeature</em> not value of <strong>EfiUsbPortEnable</strong>,
<strong>EfiUsbPortSuspend</strong>, <strong>EfiUsbPortReset</strong> nor
<strong>EfiUsbPortPower</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



### ClearRootHubPortFeature()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 26%" />
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
<td>5.21.1.13.1</td>
<td>0x88cda060, 0xbe70, 0x4c49, 0x95, 0xac, 0xae, 0xa0, 0x37, 0xfa,
0x7f, 0x51</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ClearRootHubPortFeature</strong> -
<strong>ClearRootHubPortFeature ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>PortNumber</em>.</td>
<td><p>1. Call <strong>GetRootHubPortNumber ()</strong> to get the
number of ports. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>ClearRootHubPortFeature()</strong> with a
<em>PortNumber</em> greater than the number of ports. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.21.1.13.2</td>
<td>0x59de7e7c, 0x078d, 0x4217, 0xa5, 0xfd, 0xf0, 0x1e, 0x15, 0xeb,
0xa3, 0x67</td>
<td><strong>EFI_USB2_HC_PROTOCOL.</strong>
<strong>ClearRootHubPortFeature</strong> -
<strong>ClearRootHubPortFeature ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>PortFeature</em>.</td>
<td><p>1. Call <strong>GetRootHubPortNumber ()</strong> to get the
number of ports. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>ClearRootHubPortFeature()</strong> with a
<em>PortFeature</em> not value of <strong>EfiUsbPortEnable</strong>,
<strong>EfiUsbPortSuspend</strong>, <strong>EfiUsbPortPower</strong>,
<strong>EfiUsbPortConnectChange</strong>,
<strong>EfiUsbPortResetChange</strong>,
<strong>EfiUsbPortEnableChange</strong>,
<strong>EfiUsbPortSuspendChange</strong>, nor
<strong>EfiUsbPortOverCurrentChange</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



## EFI_USB_IO_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_USB_IO_PROTOCOL Section.

Most of functionalities rely on real USB devices. They are not covered
in below checkpoints.

### UsbControlTransfer()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 15%" />
<col style="width: 26%" />
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
<td>5.21.2.1.1</td>
<td>0xe687694c, 0xc7ec, 0x444b, 0xac, 0xc5, 0xa3, 0x56, 0xf2, 0xb6,
0x3f, 0x15</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbControlTransfer</strong> - <strong>UsbControlTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with an
invalid <em>TransferDirection</em>.</td>
<td><p>1. Call <strong>UsbControlTransfer()</strong> with an invalid
<em>TransferDirection</em> ( value of <strong>-1</strong>). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>UsbControlTransfer()</strong> with an invalid
<em>TransferDirection</em> ( value of <strong>0x7FFFFFFF</strong>). The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.21.2.1.2</td>
<td>0x4aa535ad, 0x7985, 0x49f3, 0x81, 0x53, 0xa3, 0xd7, 0x04, 0x1e,
0x3f, 0xd0</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbControlTransfer</strong> - <strong>UsbControlTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>Request</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbControlTransfer()</strong> with a
<em>Request</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.2.1.3</td>
<td>0xc6bfebde, 0xd2d6, 0x44fa, 0xa6, 0xd9, 0x9b, 0x3c, 0x88, 0x9a,
0x52, 0x81</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbControlTransfer</strong> - <strong>UsbControlTransfer
()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>Status</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbControlTransfer()</strong> with a <em>Status</em>
value of <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.1.4</td>
<td><p>0x937f99d5, 0x18ef, 0x424c, 0xb4, 0x4c, 0x54, 0xaf, 0xf6, 0x20,
0xe0, 0xdc</p></td>
<td><p><strong>EFI_USB_IO_PROTOCOL.</strong></p>
<p><strong>UsbControlTransfer -</strong></p>
<p><strong>UsbControlTransfer () returns</strong></p>
<p><strong>EFI_SUCCESS</strong> or <strong>EFI_DEVICE_ERROR</strong>
when the parameter <em>Timeout</em> is 0.</p></td>
<td><p>1. Call <strong>UsbControlTransfer ()</strong> when the
parameter <em>Timeout</em> is 0. The return code must be</p>
<p><strong>EFI_SUCCESS</strong> or
<strong>EFI_DEVICE_ERROR</strong>.</p>
<p>.</p></td>
</tr>
</tbody>
</table>


### UsbBulkTransfer()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>5.21.2.2.1</td>
<td>0xf7c2276a, 0xfcd0, 0x4aeb, 0x99, 0x79, 0xf8, 0x79, 0x24, 0xd4,
0xc4, 0x83</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>DeviceEndpoint</em>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with an invalid
<em>DeviceEndpoint</em> value of <strong>0</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.2.2</td>
<td>0xa0365348, 0xba4c, 0x43fe, 0xba, 0xde, 0x8e, 0x35, 0x26, 0x39,
0x7e, 0xbd</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>DeviceEndpoint</em>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with an invalid
<em>DeviceEndpoint</em> ( value of <strong>0x10</strong>). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.2.2.3</td>
<td>0xafcf7b82, 0x16ad, 0x4721, 0x92, 0x46, 0x0d, 0x7b, 0xbb, 0xbd,
0xc9, 0x3a</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>DeviceEndpoint</em>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with an invalid
<em>DeviceEndpoint</em> ( value of <strong>0x80</strong> ). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.2.4</td>
<td>0x88c28425, 0xfbc6, 0x4441, 0x91, 0x23, 0x88, 0x83, 0x76, 0x9c,
0xed, 0x1e</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>DeviceEndpoint</em>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with an invalid
<em>DeviceEndpoint</em> ( value of <strong>0x90</strong>). The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.2.2.5</td>
<td>0x383c6bd1, 0xb1f3, 0x4987, 0x8c, 0x6f, 0xb5, 0xd5, 0x23, 0xb4,
0x93, 0xc1</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>DeviceEndpoint</em> value of not a BULK endpoint.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with an invalid
<em>DeviceEndpoint</em> which is <strong>not a BULK endpoint.</strong>
The return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.2.6</td>
<td>0x141aa66b, 0x7628, 0x4275, 0xae, 0xe3, 0x8c, 0xe1, 0x17, 0x65,
0x0d, 0xcc</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a <em>Data</em>
value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with a <em>Data</em>
value of <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.2.2.7</td>
<td>0x486552a5, 0x9863, 0x4eed, 0x8b, 0x37, 0x92, 0xb3, 0x8b, 0xc3,
0xe3, 0xeb</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em>DataLength</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with a
<em>DataLength</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.2.8</td>
<td>0x582d809f, 0x88ce, 0x4a35, 0x89, 0xc6, 0xb5, 0x79, 0xf3, 0x70,
0x54, 0x66</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbBulkTransfer</strong> - <strong>UsbBulkTransfer ()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a <em>Status</em>
value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbBulkTransfer()</strong> with a <em>Status</em>
value of <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td id="section-23" class="unnumbered">5.21.2.2.9</td>
<td>0x3d1b8608, 0x8c1e, 0x4b09, 0x81, 0x0f, 0xd9, 0x5c, 0x2a, 0xd7,
0x66, 0xae</td>
<td><p><strong>EFI_USB_IO_PROTOCOL.</strong></p>
<p><strong>UsbBulkTransfer -</strong></p>
<p><strong>UsbBulkTransfer ()</strong> returns</p>
<p><strong>EFI_SUCCESS</strong> or <strong>EFI_DEVICE_ERROR</strong>
when</p>
<p>the parameter <em>Timeout</em> is 0.</p></td>
<td><p>1. Call <strong>UsbBulkTransfer ()</strong> when the parameter
<em>Timeout</em> is 0. The return code must be</p>
<p><strong>EFI_SUCCESS</strong> or</p>
<p><strong>EFI_DEVICE_ERROR</strong>.</p></td>
</tr>
</tbody>
</table>


### UsbAsyncInterruptTransfer()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.3.1 | 0x551fbef7, 0xd9e9, 0x4302, 0xa4, 0xcd, 0x2d, 0xb6, 0x83, 0x47, 0xc9, 0x4a | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *DeviceEndpoint* value of **0**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.2 | 0xbb293ec7, 0x3a01, 0x493d, 0xa2, 0x2b, 0x71, 0x97, 0x48, 0x0b, 0x4f, 0x64 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *DeviceEndpoint* value of **0x10**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.3 | 0xf2436425, 0xee55, 0x41ee, 0x81, 0x3d, 0xa4, 0x64, 0x47, 0x17, 0x18, 0xfa | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *DeviceEndpoint***(** value of **0x80)**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.4 | 0x7ab9696d, 0x6687, 0x4f7f, 0xac, 0x16, 0x6a, 0x60, 0x23, 0x57, 0x41, 0xa7 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *DeviceEndpoint* ( value of **0x90**). The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.5 | 0x17646b64, 0x413f, 0x41cc, 0xbd, 0x8c, 0x91, 0x66, 0xe4, 0xef, 0x3e, 0x4c | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with a *DeviceEndpoint* value of not an Interrupt endpoint. | 1\. Call **UsbAsyncInterruptTransfer ()** with a *DeviceEndpoint* value of not an Interrupt endpoint. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.6 | 0x4d89db86, 0x4acc, 0x4ed8, 0xb8, 0xd1, 0xc3, 0xaa, 0x75, 0x08, 0xb3, 0xee | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *PollingInterval*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *PollingInterval* value of **0**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.3.7 | 0x808d9c7c, 0x2397, 0x406d, 0x97, 0x69, 0xcd, 0xeb, 0x4f, 0xde, 0x11, 0x16 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncInterruptTransfer** - **UsbAsyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *PollingInterval*. | 1\. Call **UsbAsyncInterruptTransfer ()** with an invalid *PollingInterval* (value of **256**. The return status should be **EFI_INVALID_PARAMETER**. |

### UsbSyncInterruptTransfer()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.4.1 | 0x59735398, 0x5d31, 0x42e2, 0x8e, 0x65, 0x68, 0xbd, 0x6c, 0x1e, 0xbb, 0xb6 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbSyncInterruptTransfer ()** with an invalid *DeviceEndpoint* (value of **0**). The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.2 | 0xdd2221a8, 0x7dc1, 0x4d2a, 0x85, 0x99, 0x6b, 0x86, 0x9d, 0x74, 0xf0, 0xa7 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbSyncInterruptTransfer ()** with an invalid *DeviceEndpoint* value of **0x10**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.3 | 0x15c6a9c5, 0x9912, 0x4474, 0xac, 0xe5, 0xa3, 0x1d, 0x49, 0xde, 0x63, 0x28 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbSyncInterruptTransfer ()** with an invalid *DeviceEndpoint* value of **0x80**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.4 | 0x833ca596, 0xf83d, 0x455f, 0x95, 0x95, 0xe5, 0x77, 0xa6, 0xaf, 0x62, 0xdc | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbSyncInterruptTransfer ()** with an invalid *DeviceEndpoint* value of **0x90**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.5 | 0x60a2a3d0, 0xb657, 0x413d, 0x9b, 0x1c, 0xa7, 0x2b, 0x46, 0xaa, 0xa6, 0x77 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with a *DeviceEndpoint* value of not an Interrupt endpoint. | 1\. Call **UsbSyncInterruptTransfer ()** with a *DeviceEndpoint* value of not an Interrupt endpoint. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.6 | 0xd4730bf3, 0x8b92, 0x4bcf, 0x99, 0xef, 0xe1, 0xdb, 0x65, 0xe9, 0x86, 0xec | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with a *Data* value of **NULL**. | 1\. Call **UsbSyncInterruptTransfer ()** with a *Data* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.7 | 0x0dbc8bd6, 0x4405, 0x49c0, 0xa5, 0xd1, 0xbc, 0x01, 0xca, 0x61, 0x67, 0xb2 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with a *DataLength* value of **NULL**. | 1\. Call **UsbSyncInterruptTransfer ()** with a *DataLength* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.4.8 | 0xa5e94a41, 0xc3ef, 0x4172, 0x94, 0xc2, 0xc7, 0xba, 0xa8, 0x72, 0xc3, 0x74 | **EFI_USB_IO_PROTOCOL.** **UsbSyncInterruptTransfer** - **UsbSyncInterruptTransfer ()** returns **EFI_INVALID_PARAMETER** with a *Status* value of **NULL**. | 1\. Call **UsbSyncInterruptTransfer ()** with a *Status* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |



### UsbIsochronousTransfer()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.5.1 | 0x006bb343, 0x842a, 0x417a, 0xa8, 0x23, 0x29, 0x75, 0x68, 0x9b, 0x9e, 0x2a | **EFI_USB_IO_PROTOCOL.** **UsbIsochronousTransfer** - **UsbIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.5.2 | 0xd4f5400e, 0x3ed0, 0x4659, 0xa4, 0x80, 0xff, 0xf5, 0xeb, 0x8b, 0xae, 0x9b | **EFI_USB_IO_PROTOCOL.** **UsbIsochronousTransfer** - **UsbIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x10**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.5.3 | 0xcfbc4d53, 0x07b7, 0x4366, 0x85, 0x98, 0x85, 0xf1, 0x6a, 0x15, 0x82, 0xb3 | **EFI_USB_IO_PROTOCOL.** **UsbIsochronousTransfer** - **UsbIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x80**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.5.4 | 0xc9cc277e, 0x02a3, 0x4392, 0x82, 0x24, 0x87, 0xe5, 0x26, 0x21, 0xfd, 0xd6 | **EFI_USB_IO_PROTOCOL.** **UsbIsochronousTransfer** - **UsbIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x90**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.5.5 | 0x686e7854, 0xe518, 0x41c1, 0xb1, 0x71, 0x60, 0x4e, 0x6f, 0x7e, 0xe2, 0x91 | **EFI_USB_IO_PROTOCOL.** **UsbIsochronousTransfer** - **UsbIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with a *DeviceEndpoint* which is not an Isochronous endpoint. | 1\. Call **UsbIsochronousTransfer ()** with a *DeviceEndpoint* value of not an Isochronous endpoint. The return status should be **EFI_INVALID_PARAMETER**. |

### UsbAsyncIsochronousTransfer()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.6.1 | 0x5a8a2a48, 0xd6cc, 0x4993, 0x82, 0x1e, 0xf7, 0x2f, 0x48, 0x40, 0xa7, 0x26 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncIsochronousTransfer** - **UsbAsyncIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.6.2 | 0x7df33f6b, 0x7525, 0x4999, 0x83, 0x9c, 0xb2, 0xc7, 0x73, 0xd1, 0xa2, 0xa5 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncIsochronousTransfer** - **UsbAsyncIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x10**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.6.3 | 0x586d899f, 0x34f8, 0x474d, 0x99, 0x5e, 0x9e, 0x3e, 0x98, 0x9f, 0xf0, 0xee | **EFI_USB_IO_PROTOCOL.** **UsbAsyncIsochronousTransfer** - **UsbAsyncIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x80**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.6.4 | 0xfbe98aec, 0xeab8, 0x45a3, 0x85, 0xd3, 0x00, 0x32, 0x0d, 0x1c, 0xaa, 0xe3 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncIsochronousTransfer** - **UsbAsyncIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with an invalid *DeviceEndpoint*. | 1\. Call **UsbAsyncIsochronousTransfer ()** with an invalid *DeviceEndpoint* value of **0x90**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.21.2.6.5 | 0x7588b124, 0xdaa7, 0x4715, 0xa1, 0x99, 0xa4, 0xdc, 0x32, 0x19, 0x1c, 0xc9 | **EFI_USB_IO_PROTOCOL.** **UsbAsyncIsochronousTransfer** - **UsbAsyncIsochronousTransfer ()** returns **EFI_INVALID_PARAMETER** with a *DeviceEndpoint* value of not an Isochronous endpoint. | 1\. Call **UsbAsyncIsochronousTransfer ()** with a *DeviceEndpoint* value of not an Isochronous endpoint. The return status should be **EFI_INVALID_PARAMETER**. |



### UsbGetDeviceDescriptor()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.7.1 | 0xe789ba3f, 0x2405, 0x4d45, 0xbf, 0xdb, 0x7e, 0xa7, 0xe8, 0x33, 0xc6, 0x8b | **EFI_USB_IO_PROTOCOL.** **UsbGetDeviceDescriptor** - **UsbGetDeviceDescriptor ()** returns **EFI_INVALID_PARAMETER** with a *DeviceDescriptor* value of **NULL**. | 1\. Call **UsbGetDeviceDescriptor ()** with a *DeviceDescriptor* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |



### UsbGetConfigDescriptor()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.8.1 | 0x387570c3, 0x6923, 0x4cbb, 0x82, 0xb2, 0x59, 0xc7, 0x41, 0xab, 0x92, 0x4b | **EFI_USB_IO_PROTOCOL.** **UsbGetConfigDescriptor** - **UsbGetConfigDescriptor ()** returns **EFI_INVALID_PARAMETER** with a *ConfigurationDescriptor* value of **NULL**. | 1\. Call **UsbGetConfigDescriptor ()** with a *ConfigurationDescriptor* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |



### UsbGetInterfaceDescriptor()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.9.1 | 0x47c33713, 0x8fbc, 0x43a4, 0xa2, 0xcd, 0xc1, 0x6b, 0xc7, 0xa5, 0xd4, 0x37 | **EFI_USB_IO_PROTOCOL.** **UsbGetInterfaceDescriptor** - **UsbGetInterfaceDescriptor ()** returns **EFI_INVALID_PARAMETER** with a *InterfaceDescriptor* value of **NULL**. | 1\. Call **UsbGetInterfaceDescriptor ()** with a *InterfaceDescriptor* value of **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |


### UsbGetEndpointDescriptor()

<table>
<colgroup>
<col style="width: 13%" />
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
<td>5.21.2.10.1</td>
<td>0x8167f778, 0xa58c, 0x4837, 0xaf, 0xfb, 0x5e, 0x10, 0x69, 0x66,
0xa8, 0x74</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbGetEndpointDescriptor</strong> -
<strong>UsbGetEndpointDescriptor ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<em>EndpointDescriptor</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>UsbGetEndpointDescriptor ()</strong> with an
<em>EndpointDescriptor</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.21.2.10.2</td>
<td>0xb0da5669, 0x163d, 0x4d93, 0xae, 0xf0, 0x7b, 0x28, 0x53, 0x5f,
0x47, 0x3e</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbGetEndpointDescriptor</strong> -
<strong>UsbGetEndpointDescriptor ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an <em>EndpointIndex</em>
value of larger than <strong>15</strong>.</td>
<td>1. Call <strong>UsbGetEndpointDescriptor ()</strong> with an
<em>EndpointIndex</em> value of larger than <strong>15</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.21.2.10.3</td>
<td>0x692ec6a6, 0x057d, 0x43c3, 0x94, 0x74, 0x5c, 0x29, 0xb2, 0x5e,
0x5c, 0xe5</td>
<td><strong>EFI_USB_IO_PROTOCOL.</strong>
<strong>UsbGetEndpointDescriptor</strong> -
<strong>UsbGetEndpointDescriptor ()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an <em>EndpointIndex</em>
value of equal to the number of endpoints.</td>
<td><p>1. Call <strong>UsbGetInterfaceDescriptor ()</strong> to get the
number of endpoints. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>UsbGetEndpointDescriptor ()</strong> with an
<em>EndpointIndex</em> value of equal to the number of endpoints. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



### UsbPortReset()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.21.2.11.1 | 0x27431330, 0x54c8, 0x40fe, 0x93, 0x74, 0x9d, 0x39, 0x4d, 0x10, 0x75, 0x3b | **EFI_USB_IO_PROTOCOL.** **UsbPortReset** - **UsbPortReset ()** returns **EFI_INVALID_PARAMETER** with a USB hub. | 1\. Call **UsbPortReset** **()** with a USB hub. The return status should be **EFI_INVALID_PARAMETER**. |

