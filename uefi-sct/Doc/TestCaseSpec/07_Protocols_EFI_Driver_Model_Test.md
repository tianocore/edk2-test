# Protocols EFI Driver Model Test

## EFI_DRIVER_BINDING_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DRIVER_BINDING_PROTOCOL Section.

This test will change the system data during testing. It is not included
in the EFI SCT.

## EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL Section.

### GetDriver()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.2.1.1 | 0x013a1d94, 0x42ec, 0x429c, 0xb4, 0x99, 0x9d, 0x67, 0x5c, 0xea, 0x32, 0xe2 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver** - Invokes **GetDriver()** with invalid *ControllerHandle.* | Call **GetDriver()** with invalid *ControllerHandle*. It should return **EFI_INVALID_PARAMETER**. |
| 5.5.2.1.2 | 0xec346531, 0x5125, 0x4e5f, 0x93, 0xa9, 0x7a, 0x7a, 0xed, 0xc0, 0xe3, 0xb9 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver** - Invokes **GetDriver()** with invalid *DriverImageHandle* | Call **GetDriver()** with invalid *DriverImagePath*. It should return **EFI_INVALID_PARAMETER**. |
| 5.5.2.1.3 | 0xb6ce6934, 0xae1d, 0x41be, 0xba, 0x01, 0xac, 0x73, 0x49, 0x70, 0xe0, 0xb5 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver** - Invokes **GetDriver()** and verify interface correctness within test case | Call **GetDriver()** with *DriverImageHandle* is **NULL**. If the return status is **EFI_SUCCESS**, get the next image handle till the end. The return status should be **EFI_SUCCESS**, except the last one. The last one should be **EFI_NOT_FOUND**. |
| 5.5.2.1.4 | 0xf8e30f06, 0x98b8, 0x4aba, 0xa0, 0x73, 0x67, 0x69, 0x33, 0xc0, 0xf8, 0x81 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriver** - Invokes **GetDriver()** and verify whether the image handle is installed. | Call **GetDriverPath()** to get the valid *DevicePath*.Call **LoadImage()** to get the *DriverImageHandle*. Use this *DevicePath* and *DriverImageHandle* to call **DriverLoaded()**.Call **GetDriver()**.The Image Handle got by the **GetDriver()** should be same as the former handle which is got by **LoadImage()**.The new *DriverImageHandle* should be same as the before one. |

### GetDriverPath()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.2.2.1 | 0x47008c31, 0xe877, 0x4acf, 0x88, 0x7a, 0xd5, 0x56, 0xd4, 0xb1, 0xd5, 0xe3 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath** - Invokes **GetDriverPath()** with invalid *ControllerHandle.* | Call **GetDriverPath()** with invalid *ControllerHandle*. Return status should be **EFI_INVALID_PARAMETER**. |
| 5.5.2.2.2 | 0xbb8d1b45, 0xe187, 0x4195, 0xa9, 0xdc, 0xdb, 0xc7, 0x5e, 0xef, 0x99, 0x92 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath** - Invokes **GetDriverPath()** with invalid *DriverImageHandle* | Call **GetDriverPath()** with invalid *DriverImagePath*. Return status should be **EFI_INVALID_PARAMETER**. |
| 5.5.2.2.3 | 0xe0434e5d, 0xa452, 0x4ef6, 0xb3, 0x90, 0xba, 0x12, 0x2a, 0xbb, 0xa8, 0xa8 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.GetDriverPath** - Invokes **GetDriverPath()** and verify interface correctness within test case | Call **GetDriverPath()** with *DriverImagePath* is **NULL**.If the return status is **EFI_SUCCESS**, get the next image handle till the end. The return status should be **EFI_SUCCESS**, except the last one. The last one should be **EFI_NOT_FOUND**. |



### DriverLoaded()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.2.3.1 | 0x7bad1b57, 0xc99c, 0x48c0, 0xb5, 0x28, 0x0b, 0x86, 0x0e, 0xfc, 0x27, 0xc3 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded** - Invokes **DriverLoaded()** and verify interface correctness within test case | Call **GetDriverPath()** to get the valid *DevicePath*.Call **LoadImage()** to get the Driver Image Handle.Use this *DevicePath* and Driver Image Handle to call **DriverLoaded()**.The return status should be **EFI_SUCCESS**. |
| 5.5.2.3.2 | 0x4d764ca3, 0x4d43, 0x4a89, 0x93, 0x4b, 0x8f, 0x60, 0x9e, 0xca, 0x82, 0x4d | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded** - Invokes **DriverLoaded()** with *DriverImagePath* not gotten from the prior call to **GetDriverPath()**. | Call **DriverLoaded()** with *DriverImagePath* is not a device path that was returned on a prior call to **GetDriverPath()** for the controller specified by *ControllerHandle*. Return status should be **EFI_NOT_FOUND**. |
| 5.5.2.3.3 | 0x745042f7, 0xa9e8, 0x436b, 0x8c, 0x44, 0x42, 0x49, 0x07, 0x90, 0x68, 0x50 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded** - Invokes **DriverLoaded()** with invalid *ControllerHandle* | Call **DriverLoaded()** with invalid *ControllerHandle* .The return status should be **EFI_INVALID_PARAMETER**. |
| 5.5.2.3.4 | 0xecc09588, 0xb786, 0x49b1, 0x93, 0x7f, 0x8e, 0xed, 0x89, 0xa7, 0x52, 0xd6 | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded** - Invokes **DriverLoaded()** with invalid *DriverImagePath*. | Call **DriverLoaded()** with invalid *DriverImagePath* .The return status should be **EFI_INVALID_PARAMETER**. |
| 5.5.2.3.5 | 0xf5d05588, 0x0d6a, 0x40fa, 0xa9, 0x54, 0x4b, 0x40, 0xd7, 0x9b, 0x4e, 0x5b | **EFI_PLATFORM_DRIVER_OVERRIDE_PROTOCOL.DriverLoaded** - Invokes **DriverLoaded()** with invalid *DriverImageHandle* | Call **DriverLoaded()** with invalid *DriverImageHandle*. The return status should be **EFI_INVALID_PARAMETER**. |

## EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL Section.

### GetDriver()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 17%" />
<col style="width: 28%" />
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
<td>5.5.3.1.1</td>
<td>0x18a52d36, 0xd149, 0x414c, 0xa8, 0xc9, 0x43, 0xc8, 0x55, 0x71,
0xc6, 0x5f</td>
<td><strong>EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL.GetDriver –
GetDriver</strong> returns <strong>EFI_SUCCESS</strong> with valid
<em>DriverImageHandle</em></td>
<td><p>1. Circularly call <strong>GetDriver()</strong> with
<em>DriverImageHandle</em> retrieved by the last call of
<strong>GetDriver()</strong>, until the end of the list of override
drivers is reached.</p>
<p>Expected Behavior:</p>
<p>The return status of each valid <em>DriverImageHandle</em> must be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.3.1.2</td>
<td>0x841a7b86, 0xabf0, 0x40af, 0x92, 0x67, 0x3f, 0xb3, 0x69, 0x2f,
0xc0, 0x37</td>
<td><strong>EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL.GetDriver –
GetDriver</strong> returns <strong>EFI_NOT_FOUND</strong> with
unsupported Parameters</td>
<td><p>1. Circularly call <strong>GetDriver()</strong> with
<em>DriverImageHandle</em> retrieved by the last call of
<strong>GetDriver()</strong>, until the end of the list of override
drivers is reached.</p>
<p>Expected Behavior:</p>
<p>The last return status must be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.3.1.3</td>
<td>0x2f0b7eb4, 0xb6b4, 0x4a58, 0x87, 0x55, 0x93, 0x52, 0xd4, 0x7e,
0x27, 0xef</td>
<td><strong>EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL.GetDriver –
GetDriver ()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>DriverImageHandle</em></td>
<td><p>1. Pass the invalid <em>DriverImageHandle</em> to the
function</p>
<p>Expected Behavior:</p>
<p>The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>



## EFI_DRIVER_CONFIGURATION_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_BUS_SPECIFIC_DRIVER_OVERRIDE_PROTOCOL Section.

### SetOptions()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 20%" />
<col style="width: 33%" />
<col style="width: 30%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.4.1.1</td>
<td>0x82d78ef0, 0x0e7c, 0x4338, 0xb0, 0xe6, 0xef, 0x07, 0x01, 0x35,
0x18, 0xc7</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SetOptions –
SetOptions()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ControllerHandle</em></td>
<td>1. Call <strong>SetOptions()</strong> with invalid
<em>ControllerHandle</em>. Return status of
<strong>SetOptions()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.4.1.2</td>
<td>0x159d6867, 0x6e6f, 0x4cb0, 0x99, 0xc1, 0xdf, 0x57, 0x86, 0xc0,
0x61, 0x3f</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SetOptions –
SetOptions()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ActionRequired</em></td>
<td>1. Call <strong>SetOptions()</strong> with an
<em>ActionRequired</em> value of <strong>NULL</strong>. Return status
must be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.5.4.1.3</td>
<td>0x97465a70, 0x7746, 0x4116, 0x93, 0xbc, 0x22, 0xb1, 0xaa, 0x9e,
0x14, 0xa2</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SetOptions –
SetOptions()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ControllerHandle</em> &amp; <em>ChildHandle.</em></td>
<td>1. Call <strong>SetOptions()</strong> with: (
<em>ControllerHandle</em> == <strong>NULL</strong> &amp;&amp;
<em>ChildHandle</em> != <strong>NULL</strong> ). Return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.4.1.4</td>
<td>0x976f0e0a, 0xa696, 0x4922, 0x8a, 0x44, 0xf3, 0x50, 0xf5, 0x0b,
0xd5, 0xe8</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SetOptions –
SetOptions()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>Language</em>.</td>
<td><p>1. Parse the
<strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SupportedLanguage</strong>,
compare with the language code repository. If could not find out an
unsupported language, then skip this checkpoint.</p>
<p>2. Call <strong>SetOptions()</strong> with all unsupported
<em>Language</em> codes. Each return status must be
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.4.1.5</td>
<td>0x12b263e5, 0xcb83, 0x4855, 0x94, 0x35, 0x6e, 0xfb, 0x53, 0x9d,
0x22, 0x51</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.SetOptions –
SetOptions()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>ControllerHandle</em>.</td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>SetOptions()</strong>. The return code must be
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### OptionsValid()

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
<td>5.5.4.2.1</td>
<td>0x9a4ba394, 0xbf63, 0x4dba, 0xaf, 0x83, 0xc7, 0x50, 0xc9, 0xff,
0xaa, 0xf4</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.OptionsValid –
OptionsValid()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ControllerHandle</em>.</td>
<td>1. Call <strong>OptionsValid()</strong> with invalid
<em>ControllerHandle</em>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.4.2.2</td>
<td>0x10a4cd4b, 0x0e42, 0x4bed, 0x9b, 0x3e, 0x53, 0x21, 0x50, 0x9c,
0xd0, 0xf6</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.OptionsValid –
OptionsValid()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>ControllerHandle</em>.</td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>OptionsValid()</strong>. It should return
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>


### ForceDefaults()

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
<td>5.5.4.3.1</td>
<td>0x45b89573, 0xff7d, 0x4549, 0xbc, 0x5f, 0x7f, 0x23, 0x04, 0xa1,
0x1c, 0x43</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.ForceDefaults –
ForceDefaults()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ControllerHandle</em>.</td>
<td>1. Call <strong>ForceDefaults()</strong> with invalid
<em>ControllerHandle</em>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.4.3.2</td>
<td>0x0ede4bce, 0x0456, 0x45e5, 0x86, 0x04, 0x88, 0xc4, 0xa2, 0xbb,
0x7c, 0xa1</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.ForceDefaults –
ForceDefaults()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>.
with an <em>ActionRequired</em> value of <strong>NULL</strong></td>
<td>1. Call <strong>ForceDefaults()</strong> with an
<em>ActionRequired</em> value of <strong>NULL</strong>. Return status
must be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.5.4.3.3</td>
<td>0x0e7dd3db, 0x072b, 0x45b6, 0xaa, 0xdf, 0xf3, 0xed, 0xed, 0x37,
0xe6, 0xae</td>
<td><strong>EFI_DRIVER_CONFIGURATION_PROTOCOL.ForceDefaults –
ForceDefaults()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>ControllerHandle</em>.</td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>ForceDefaults()</strong>. It should return
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>


## EFI_DRIVER_DIAGNOSTICS_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DRIVER_DIAGNOSTICS_PROTOCOL Section.

### RunDiagnostic()

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
<td>5.5.5.1.1</td>
<td>0xe6351da7, 0x8e29, 0x451b, 0xb1, 0x16, 0xda, 0x93, 0x29, 0x97,
0x0f, 0x17</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ControllerHandle</em>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with invalid
<em>ControllerHandle</em>. Return Status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.5.1.2</td>
<td>0xf98940fb, 0x1ae6, 0x42a8, 0x95, 0xb3, 0xd3, 0x90, 0x84, 0x17,
0x2e, 0xb7</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>Language</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with a <em>Language</em>
value of <strong>NULL</strong>. Return Status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.5.1.3</td>
<td>0xe348a9ee, 0x10fc, 0x4487, 0x8c, 0x1a, 0xfc, 0xa8, 0x11, 0xd7,
0xbb, 0x24</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with an <em>ErrorType</em> value of <strong>NULL.</strong></td>
<td>1. Call <strong>RunDiagnostics()</strong> with an <em>ErrorType</em>
value of <strong>NULL</strong>. Return Status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.5.1.4</td>
<td>0x1f03e17d, 0x3f3c, 0x45ab, 0x93, 0xf5, 0xd3, 0xde, 0x3e, 0xc3,
0xe3, 0xcc</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>BufferSize</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with a <em>BufferSize</em>
value of <strong>NULL</strong>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.5.1.5</td>
<td>0x7a73befe, 0xb271, 0x486f, 0x9b, 0x0e, 0x97, 0x3c, 0x5e, 0x80,
0x64, 0xd9</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>Buffer</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with a <em>Buffer</em>
value of <strong>NULL</strong>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.5.1.6</td>
<td>0xaeab03a7, 0xfa56, 0x4e97, 0x8e, 0x1c, 0xc3, 0x35, 0xb4, 0xa4,
0xb4, 0x1c</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>Language</em>.</td>
<td><p>1. Parse the
<strong>EFI_DRIVER_DIAGNOSTICS_PROTOCOL.SupportedLanguage</strong>,
compare with the language code repository. If could not find out an
unsupported language, then skip this checkpoint.</p>
<p>2. Call <strong>RunDiagnostics()</strong> with all unsupported
Language codes.</p>
<p>Each return status of <strong>RunDiagnostics()</strong> is
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.5.1.7</td>
<td>0xf8d9425c, 0x4bc8, 0x44a9, 0xa4, 0x33, 0x9a, 0x2c, 0x01, 0xec,
0x58, 0x27</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>ControllerHandle</em>.</td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>RunDiagnostics()</strong>.</p>
<p>It should return <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



## EFI_DRIVER_DIAGNOSTICS2_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DRIVER_DIAGNOSTICS2_PROTOCOL Section.

### RunDiagnostic()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
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
<td>5.5.6.1.1</td>
<td>0x6c872dce, 0x787e, 0x44dc, 0xa8, 0x87, 0xea, 0x1b, 0x8d, 0x55,
0xfd, 0x59</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <strong>NULL</strong> <em>ControllerHandle</em>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with <strong>NULL</strong>
<em>ControllerHandle</em>. Return Status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.6.1.2</td>
<td>0xf3263eb0, 0x1630, 0x4749, 0x98, 0xe6, 0xc9, 0x50, 0x23, 0x15,
0xd3, 0xa2</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with invalid <em>ChildHandle</em>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with invalid
<em>ChildHandle</em>. Return Status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.6.1.3</td>
<td>0xc5b8e4ef, 0x2fa4, 0x4ae9, 0xa6, 0x5e, 0xdd, 0x47, 0x2d, 0xfd,
0x81, 0xe5</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <strong>Language</strong> value of <strong>NULL.</strong></td>
<td>1. Call <strong>RunDiagnostics()</strong> with
<strong>Language</strong> value of <strong>NULL</strong>. Return Status
must be <strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.6.1.4</td>
<td>0xe23426c8, 0x5fe2, 0x4e80, 0xa9, 0x40, 0xab, 0x66, 0x10, 0x63,
0x28, 0xf6</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <em>ErrorType</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with <em>ErrorType</em>
value of <strong>NULL</strong>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.6.1.5</td>
<td>0x6e86ac1a, 0x0ce8, 0x4f83, 0x9d, 0xa2, 0x38, 0x79, 0x1e, 0xff,
0x0f, 0x8c</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>BufferSize</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with a <em>BufferSize</em>
value of <strong>NULL</strong>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="odd">
<td>5.5.6.1.6</td>
<td>0x4c955e4c, 0x86b9, 0x4c6d, 0x83, 0xa0, 0x4e, 0xa3, 0x34, 0x67,
0xd0, 0x38</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>Buffer</em> value of <strong>NULL</strong>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with a <em>Buffer</em>
value of <strong>NULL</strong>. Return status must be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.6.1.7</td>
<td>0x8b218e7b, 0x24a0, 0x400c, 0xa8, 0x69, 0x1a, 0xd1, 0x14, 0x8e,
0x7a, 0x07</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>Language</em>.</td>
<td><p>1. Parse the
<strong>EFI_DRIVER_DIAGNOSTICS_PROTOCOL.SupportedLanguage</strong>,
compare with the language code repository. If could not find out an
unsupported language, then skip this checkpoint.</p>
<p>2. Call <strong>RunDiagnostics()</strong> with all unsupported
Language codes.</p>
<p>Each return status of <strong>RunDiagnostics()</strong> is
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.6.1.8</td>
<td>0xef071998, 0xeb8d, 0x488f, 0xa5, 0xd5, 0x9e, 0x44, 0x7a, 0x54,
0x20, 0x8b</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_UNSUPPORTED with virtual
device handle</strong></td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>RunDiagnostics()</strong>.</p>
<p>It should return <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.6.1.9</td>
<td>0xc9da5237, 0x6ad0, 0x4c74, 0x88, 0xd0, 0x6e, 0x51, 0x7f, 0x6c,
0x4f, 0x63</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> return <strong>EFI_UNSUPPORTED</strong> with
virtual child handle</td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ChildHandle</em> input for the
<strong>RunDiagnostics()</strong>.</p>
<p>It should return <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.6.1.10</td>
<td>0x2e31c21e, 0x1999, 0x42b7, 0x96, 0xe6, 0xda, 0x8e, 0xfc, 0xc1,
0xf1, 0x51</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_SUCCESS</strong> with
supported <em>Language</em>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with supported
<em>Language</em>. Return status must be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.5.6.1.11</td>
<td>0x04405fac, 0x1688, 0x4213, 0xa1, 0x1d, 0x4b, 0x64, 0x58, 0xff,
0xe7, 0x2c</td>
<td><strong>EFI_DRIVER_DIAGNOSTIC2_PROTOCOL.RunDiagnostics –
RunDiagnostics()</strong> returns <strong>EFI_SUCCESS</strong> with
supported <em><strong>Language</strong></em>.</td>
<td>1. Call <strong>RunDiagnostics()</strong> with supported
<em><strong>Language</strong></em>.. Return status must be
<strong>EFI_SUCCESS.</strong></td>
</tr>
</tbody>
</table>



## EFI_COMPONENT_NAME_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_COMPONENT_NAME_PROTOCOL Section.

### GetDriverName()

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
<td>5.5.7.1.1</td>
<td>0x628fcfba, 0xc74b, 0x4038, 0x91, 0x5a, 0x01, 0x1a, 0xb9, 0x0f,
0x67, 0x35</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetDriverName –
GetDriverName()</strong> returns its driver name in every supported
language.</td>
<td><p>For each supported language:</p>
<p>1. Call <strong>GetDriverName()</strong> to retrieve current driver’s
name.</p>
<p>2. Dump the returned driver name.</p>
<p>Each return code of <strong>GetDriverName()</strong> should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.1.2</td>
<td>0x59ed70e0, 0x9cc8, 0x48d5, 0x86, 0x75, 0xed, 0xcb, 0xb0, 0x88,
0xeb, 0xd9</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetDriverName –
GetDriverName()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>Language</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>GetDriverName()</strong> with a <em>Language</em>
value of <strong>NULL</strong>.</p>
<p>THe return status of <strong>GetDriverName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.1.3</td>
<td>0x9cffff0f, 0x65a7, 0x43a5, 0x9e, 0xf1, 0x74, 0x02, 0x27, 0x82,
0x3d, 0xfc</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetDriverName –
GetDriverName()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <em>DriverName</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>GetDriverName()</strong> with a
<em>DriverName</em> value of <strong>NULL</strong>.</p>
<p>The return status of <strong>GetDriverName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.1.4</td>
<td>0xcb089876, 0xe819, 0x4fd8, 0xac, 0xbe, 0x47, 0x56, 0x8c, 0x10,
0x93, 0xcc</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetDriverName –
GetDriverName()</strong> returns <strong>EFI_UNSUPPORTED</strong> with
unsupported <em>Language</em>.</td>
<td><p>1. Parse the
<strong>EFI_COMPONENT_NAME_PROTOCOL.SupportedLanguage</strong>, compare
with the language code repository. If could not find out an unsupported
language, then skip this checkpoint.</p>
<p>2. Call <strong>GetDriverName()</strong> with all unsupported
<em>Language</em> codes.</p>
<p>Each return status of <strong>GetDriverName()</strong> is
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### GetControllerName()

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
<td>5.5.7.2.1</td>
<td>0x961fabd3, 0x97ec, 0x4c97, 0xa0, 0x5a, 0xc2, 0xfd, 0xa6, 0x32,
0xf1, 0x3d</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> must successfully retrieve
<em>ControllerName</em> for all manageable
<em>ControllerHandle</em>.</td>
<td><p>1. Retrieve all controller handles that are managed by the driver
specified by the component protocol instance.</p>
<p>2. For each <em>ControllerHandle</em></p>
<p>Call <strong>GetControllerName()</strong> with the
<em>ControllerHandle</em> and at the same time, with a
<em>ChildHandle</em> value of <strong>NULL</strong> in every supported
language.</p>
<p>The <strong>GetControllerName()</strong> should return
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.2.2</td>
<td>0xa83cfe57, 0x8391, 0x472b, 0xbc, 0x0e, 0x12, 0x18, 0x95, 0x06,
0x86, 0x70</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> must successfully retrieve
<em>ControllerName</em> for <em>ChildHandle</em> of manageable
<em>ControllerHandle</em>.</td>
<td><p>1. Retrieve all controllers that are managed by the driver
specified by the component instance.</p>
<p>2. Retrieve all child controllers. (If the controller has no child
controller, then skip this checkpoint).</p>
<p>3. For each controller and its child controller:</p>
<p>Call <strong>GetControllerName()</strong> with every child controller
of the bus controller.</p>
<p>The <strong>GetControllerName()</strong> should return
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.2.3</td>
<td>0x735f5c9b, 0x95c9, 0x4949, 0xa8, 0xf7, 0x0a, 0x61, 0x06, 0x2e,
0x28, 0x67</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid
<em>ControllerHandle</em>.</td>
<td><p>1. Call <strong>GetControllerName()</strong> with invalid
<em>ControllerHandle</em>.</p>
<p>The return status of <strong>GetControllerName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.2.4</td>
<td>0x6f51eca4, 0x1808, 0x4b5b, 0x96, 0x9b, 0x88, 0xd8, 0xc8, 0xa5,
0x00, 0x3e</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid <em>ChildHandle</em>
when the driver is not a device driver.</td>
<td><p>Call <strong>GetControllerName()</strong> with invalid
<em>ChildHandle</em> when the driver is not a device driver.</p>
<p>The return status of <strong>GetControllerName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.2.5</td>
<td>0x9d3dedbf, 0xa123, 0x475b, 0xb6, 0x3e, 0x15, 0x01, 0xbc, 0x99,
0x81, 0x83</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>ControllerName</em>
value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>GetControllerName()</strong> with a
<em>ControllerName</em> value of <strong>NULL</strong>.</p>
<p>The return status of <strong>GetControllerName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.2.6</td>
<td>0xb436d551, 0xf2f4, 0x4fdc, 0xb0, 0x31, 0x07, 0x3d, 0xad, 0xec,
0xd7, 0x16</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>Language</em> value of
<strong>NULL</strong></td>
<td><p>1. Call <strong>GetControllerName()</strong> with a
<em>Language</em> value of <strong>NULL</strong></p>
<p>The return status of <strong>GetControllerName()</strong> is
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.2.7</td>
<td>0x27a4781a, 0xe85a, 0x4714, 0xab, 0x9a, 0x67, 0xc1, 0x01, 0x38,
0x5e, 0x83</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns <strong>EFI_UNSUPPORTED</strong>
with unsupported <em>Language</em>.</td>
<td><p>1. Parse the
<strong>EFI_COMPONENT_NAME_PROTOCOL.SupportedLanguage</strong>, compare
with the language code repository. If could not find out an unsupported
language, then skip this checkpoint.</p>
<p>2. Find out all controller handles that will cause
<strong>GetControllerHandle()</strong> return
<strong>EFI_SUCCESS</strong> when with supported Language.</p>
<p>3. Call <strong>GetDriverName()</strong> with each
<em>ControllerHandle</em> and at the same time with those unsupported
<em>Language</em> codes.</p>
<p>When input with unsupported <em>Language</em>, the return status of
<strong>GetControllerName()</strong> should be
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.2.8</td>
<td>0xa1a56539, 0x8150, 0x483f, 0xa1, 0xb7, 0x23, 0xaf, 0x4f, 0x84,
0x64, 0xc7</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns <strong>EFI_UNSUPPORTED</strong>
with irrelevant <em>ControllerHandle</em></td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ControllerHandle</em> input for the
<strong>GetControllerName()</strong>. It should return
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.2.9</td>
<td>0x8a5321c3, 0x3e88, 0x4c62, 0xbf, 0xdd, 0xc7, 0xe4, 0xec, 0xf5,
0x1f, 0x9f</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns <strong>EFI_UNSUPPORTED</strong>
with irrelevant <em>ChildHandle</em></td>
<td><p>1. Test case creates a virtual device handle that does not stand
for any device controller.</p>
<p>2. Input this handle as the <em>ChildHandle</em> input for the
<strong>GetControllerName()</strong> (at the same time, the
<em>ControllerHandle</em> should be valid). It should also return
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.7.2.10</td>
<td>0xa5ecbbe1, 0x1795, 0x4798, 0xa8, 0x26, 0x20, 0x9c, 0x57, 0x8e,
0x1d, 0xe9</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> returns <strong>EFI_UNSUPPORTED</strong>
with device handle and not-<strong>NULL</strong>
<em>ChildHandle</em></td>
<td><p>1. Test case gets a valid device handle, and an invalid
<em>ChildHandle</em>.</p>
<p>2. Input this device handle as <em>ControllerHandle</em> and the
<em>ChildHandle</em>. It should return
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.5.7.2.11</td>
<td>0xdb9e40a7, 0x8638, 0x4c0f, 0xb2, 0x94, 0xfe, 0x05, 0x23, 0xfa,
0x1e, 0x2f</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> go through each of the handles</td>
<td>Call <strong>GetGontrollerName()</strong>with all of the handles.
The return status should not be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.5.7.2.12</td>
<td>0x79ab9a12, 0xe535, 0x4727, 0xa0, 0x4d, 0x20, 0xb7, 0x8f, 0x91,
0x8f, 0x85</td>
<td><strong>EFI_COMPONENT_NAME_PROTOCOL.GetControllerName –
GetGontrollerName()</strong> go through each of the handles and child
handles</td>
<td>Call <strong>GetGontrollerName()</strong>with all of the handles and
child handles. The return status should not be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
</tbody>
</table>



## EFI_COMPONENT_NAME2_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_COMPONENT_NAME2_PROTOCOL Section.

### GetDriverName()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.8.1.1 | 0x31518904, 0x1307, 0x4bef, 0x84, 0xe6, 0x66, 0xff, 0x76, 0xa7, 0x8f, 0xf4 | **COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName()** returns **EFI_INVALID_PARAMETER** with **NULL** *Language* | Call **GetDriverName()** with *Language* being **NULL**. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.1.2 | 0x7b478492, 0x53c0, 0x4748, 0xa2, 0x44, 0x60, 0xf3, 0xf2, 0xd0, 0xee, 0x5a | **COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName()** returns **EFI_INVALID_PARAMETER** with **NULL** DriverName | Call **GetDriverName()** with **DriverName** being **NULL**. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.1.3 | 0x36e0a7e5, 0xbfc8, 0x4ab9, 0xb4, 0x1a, 0x9d, 0x69, 0x25, 0x43, 0x6a, 0xd2 | **COMPONENT_NAME_PROTOCOL.GetDriverName - GetDriverName()** returns **EFI_UNSUPPORTED** with unsupported language | Call **GetDriverName()** with unsupported *Language*. The returned status should be **EFI_UNSUPPORTED** |
| 5.5.8.1.4 | 0x327aa49d, 0x4a8b, 0x4101, 0x8b, 0x0d, 0x92, 0x32, 0x33, 0xfc, 0x09, 0xe5 | **COMPONENT_NAME2_PROTOCOL.GetDriverName - GetDriverName()** returns **EFI_SUCCESS** with supported languange | Call **GetDriverName()** with supported *Language*. The returned status should be **EFI_SUCCESS** |



### GetControllerName()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.8.2.1 | 0xc38a85af, 0x2d0a, 0x4bfa, 0x8f, 0x44, 0xa2, 0x47, 0xf1, 0xfd, 0x7b, 0x94 | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_INVALID_PARAMETER** with invalid ControllerHandle | Call **GetControllerName()** with invalid ControllerHandle. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.2.2 | 0xde8c8d23, 0x4aa6, 0x4dd7, 0x93, 0xbd, 0x35, 0x78, 0x40, 0x67, 0x6b, 0xff | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_INVALID_PARAMETER** with invalid *ChildHandle* and non-device ControllerHandle | Call **GetControllerName()** with valid Bus Handle(non-device ControllerHandle) and invalid *ChildHandle*. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.2.3 | 0x8398d1d9, 0xdfb7, 0x47f1, 0xad, 0x65, 0x36, 0xf1, 0x2a, 0x6a, 0x47, 0xea | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_INVALID_PARAMETER** with **NULL** ControllerName | Call **GetControllerName()** with valid device ControllerHandle and **NULL** ControllerName. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.2.4 | 0x8cf65e39, 0x125b, 0x4206, 0x99, 0x85, 0xca, 0xa5, 0x15, 0x68, 0x7b, 0x0a | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_INVALID_PARAMETER** with **NULL** *Language* | Call **GetControllerName()** with valid device ControllerHandle and **NULL** *Language*. The returned status should be **EFI_INVALID_PARAMETER** |
| 5.5.8.2.5 | 0x064d252b, 0xbc7f, 0x4859, 0x86, 0x02, 0xaf, 0xa9, 0x7f, 0x8e, 0xa2, 0xbd | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_UNSUPPORTED** with unsupported language | Call **GetControllerName()** with unsupported *Language*. The returned status should be **EFI_UNSUPPORTED** |
| 5.5.8.2.6 | 0x95c8bfd8, 0xc67c, 0x411e, 0x93, 0x95, 0x43, 0x28, 0x01, 0x2c, 0x07, 0x66 | **COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_UNSUPPORTED** with irrelevant ControllerHandle | Call **GetControllerName()** with irrelevant *ControllerHandle*. The returned status should be **EFI_UNSUPPORTED** |
| 5.5.8.2.7 | 0x155c06f0, 0xe315, 0x4175, 0xa0, 0xe9, 0x4d, 0xe3, 0xc5, 0x16, 0x3c, 0xb2 | **COMPONENT_NAME_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_UNSUPPORTED** with irrelevant *ChildHandle* | Call **GetControllerName()** with irrelevant *ChildHandle*. The returned status should be **EFI_UNSUPPORTED** |
| 5.5.8.2.8 | 0xabf5cd96, 0xfb74, 0x489c, 0xae, 0x70, 0xeb, 0x31, 0xa0, 0xfd, 0xef, 0x25 | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_SUCCESS** with supported language | Call **GetControllerName()** with Supported *Language* and valid *ControllerHandle*. The returned status should be **EFI_SUCCESS** |
| 5.5.8.2.9 | 0x38bd708a, 0xf1d7, 0x4b3b, 0xb2, 0x39, 0x06, 0xf6, 0xfd, 0xa2, 0x1c, 0xb8 | **COMPONENT_NAME2_PROTOCOL.GetControllerName - GetControllerName()** returns **EFI_SUCCESS** support language | Call **GetControllerName()** with Supported *Language*, valid *ControllerHandle* and valid *ChildHandle*. The returned status should be **EFI_SUCCESS** |



## EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL

**Reference Document:**

*UEFI Specification*, EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL
Section.

### Query()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 33%" />
<col style="width: 35%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.9.1.1</td>
<td>0x6acc3f19, 0xe9b, 0x4ff7, 0xbd,0xd0, 0x7e,0x49, 0x19,0x6, 0xa8,
0xdd</td>
<td><strong>EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query
-</strong> Invoke <strong>Query()</strong> and verify interface
correctness</td>
<td><p>1. Call <strong>Query()</strong> with valid
<em>ControllerHandle</em> and Instance</p>
<p>2. if <strong>EFI_SUCCESS</strong>, get the next
<em>ControllerHandle</em> till the end</p>
<p>3. The return status should be <strong>EFI_SUCCESS</strong> except
the last one. The last one should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.9.1.2</td>
<td>0x4cfb435, 0x4569, 0x48bb, 0x8c,0x8a, 0xba,0x2a, 0xa7,0x5f,
0x16,0xe2</td>
<td><strong>EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query
-</strong> Invoke <strong>Query()</strong> with invalid
<em>ControllerHandle</em></td>
<td>Call <strong>Query()</strong> with invalid
<em>ControllerHandle</em>, it should return
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
<tr class="even">
<td>5.5.9.1.3</td>
<td>0x28730223, 0x508, 0x46c9, 0x83, 0xf7, 0x94, 0xec, 0x52, 0x4, 0x65,
0x2a</td>
<td><strong>EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Query
-</strong> Invoke <strong>Query()</strong> with invalid Instance</td>
<td>Call <strong>Query()</strong> with Instance is
<strong>NULL</strong>, it should return
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
</tbody>
</table>



### Response()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 33%" />
<col style="width: 35%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.9.2.1</td>
<td>0x15cd60c3, 0xb30, 0x44df, 0xbe,0x9, 0x0,0xfa, 0x9f,0xe6,
0xf8,0xc5</td>
<td><strong>EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response
-</strong> Invoke <strong>Response()</strong> and verify interface
correctness</td>
<td><p>1. Call <strong>Query()</strong> with valid
<em>ControllerHandle</em> and Instance, call <strong>Response()</strong>
with the same <em>ControllerHandle</em> and the arguments returned from
<strong>Query()</strong></p>
<p>2. if <strong>EFI_SUCCESS</strong>, get the next
<em>ControllerHandle</em> till the end</p>
<p>3. The return status should be <strong>EFI_SUCCESS</strong> except
the last one. The last one should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.9.2.2</td>
<td>0x88e2dc36, 0x4d7b, 0x467a, 0xbb,0x60, 0xc9,0x97, 0xb7,0x22,
0xb7,0x12</td>
<td><strong>EFI_PLATFORM_TO_DRIVER_CONFIGURATION_PROTOCOL.Response
-</strong> Invoke <strong>Response()</strong> with invalid
<em>ControllerHandle</em></td>
<td>Call <strong>Query()</strong> and <strong>Response(</strong>) with
invalid <em>ControllerHandle</em>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong></td>
</tr>
</tbody>
</table>



### DMTF SM CLP ParameterTypeGuid

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 33%" />
<col style="width: 35%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.9.3.1</td>
<td>0x35a69b6e, 0x1755, 0x41ca, 0x97,0xd7, 0xab,0xc3, 0xb7,0xb7,
0x7c,0xd3</td>
<td><strong>EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPCommand</strong> - verify
the DMTF CLP command line <strong>NULL</strong>-terminated string and
return <strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Invoke <strong>Query()</strong>, produce
<strong>EFI_CONFIGURE_CLP_PARAMETER_BLK</strong>.</p>
<p>2. Verify ParameterTypeGuid.</p>
<p>3. Compare the CLPCommand string with Standard command verbs and
options. The return code should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.5.9.3.2</td>
<td>0x77b6a0b3, 0x7efe, 0x42f8, 0x98,0xcf, 0xf5,0x49, 0x51,0xe7,
0x1c,0x2c</td>
<td><strong>EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPReturnString</strong> –
verify the CLP return string is “format=keyword” format</td>
<td><p>1. Invoke <strong>Query()</strong> and
<strong>Response()</strong>, produce
<strong>EFI_CONFIGURE_CLP_PARAMETER_BLK</strong></p>
<p>2. Verify the CLPReturnString format is “format=keyword” format. The
return code should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.5.9.3.3</td>
<td>0xd7cacc21, 0x4e96, 0x444c, 0x91,0xcb, 0x70,0x4e, 0x3f,0xa8,
0x31,0x33</td>
<td><strong>EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPCmdStatus</strong> - with
valid command and return the command status of CLP with
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Invoke <strong>Query()</strong> and
<strong>Response()</strong>, produce
<strong>EFI_CONFIGURE_CLP_PARAMETER_BLK</strong></p>
<p>2. Compare the CLPCmdStatus string with Standard command return
status table. The return code should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.5.9.3.4</td>
<td>0x69e16544, 0x23bd, 0x4b46, 0x9d,0xe5, 0xe0,0x6a, 0xb4,0x3d,
0x8b,0x12</td>
<td><strong>EFI_CONFIGURE_CLP_PARAMETER_BLK.CLPErrorValue</strong> -
compare this parameter with CLP Error Value and return code
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Invoke <strong>Query()</strong> and
<strong>Response()</strong>, produce
<strong>EFI_CONFIGURE_CLP_PARAMETER_BLK</strong></p>
<p>2. Compare the CLPErrorValue with Error Values. The return code
should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.5.9.3.5</td>
<td>0x78e97814, 0x4c3d, 0x42b3, 0xae,0x7c, 0x7b,0x16, 0x61,0x69,
0x32,0x4a</td>
<td><strong>EFI_CONFIGURE_CLP_PARAMETER_BLK. CLPMsgCode</strong> -
compare with CLP Message Code, return code
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Invoke <strong>Query()</strong> and
<strong>Response()</strong>, produce
<strong>EFI_CONFIGURE_CLP_PARAMETER_BLK</strong></p>
<p>2. verify the CLPMsgCode is equal to the CLP Probable Cause Value,
the return code should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
</tbody>
</table>



## EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL Section.

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.5.10.1.1 | 0x9b72180d, 0x155c, 0x4b7a, 0xbb, 0xa8, 0x99, 0x83, 0x7b, 0x2f, 0x9d, 0xf8 | **EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.Length** - verify this value is the structure length, and return **EFI_SUCCESS**. | Verify the entire structure length is correct and return **EFI_SUCCESS** value. |
| 5.5.10.1.2 | 0xac1951b1, 0x7243, 0x40a9, 0xa0, 0x1, 0x9d, 0x9d, 0x6e, 0x44, 0x8f, 0x5a | **EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL.FirmwareVersion** - verify the parameter with **EFI_2_10_SYSTEM_REVISION**. Return **EFI_SUCCESS** or **EFI_INCOMPATIBLE_VERSION**.. | Initialize the **EFI_VERSION_PTOTOCOL** and compare the version of the EFI Specification that driver conforms to with **EFI_2_10_SYSTEM_REVISION**. If equal, return **EFI_SUCCESS;** if not, return value should be **EFI_INCOMPATIBLE_VERSION.** . |



## EFI_ADAPTER_INFORMATION_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_ADAPTER_INFORMATION_PROTOCOL Section.

### GetInformation()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 28%" />
<col style="width: 40%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.11.1.1</td>
<td><p>0x0d68257b,</p>
<p>0xf647,</p>
<p>0x452a,0x97,</p>
<p>0x44,0xa2,</p>
<p>0x23,0xe6,</p>
<p>0xee,0x3d,</p>
<p>0xf2</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation -
GetInformation()</strong> returns <strong>EFI_SUCCESS</strong></p>
<p>with valid information type.</p></td>
<td><p>Call <strong>GetSupportedTypes()</strong> to</p>
<p>get the valid Information type.</p>
<p>Call <strong>GetInformation ()</strong>, the</p>
<p>return status should be <strong>EFI_SUCCESS</strong> and the
InformationBlock != NULL.</p></td>
</tr>
<tr class="odd">
<td>5.5.11.1.2</td>
<td><p>0x15a3a10d,</p>
<p>0xca48,</p>
<p>0x4d52,0x99,</p>
<p>0x89,0x51,</p>
<p>0x71,0xfc,</p>
<p>0x90,0x90,</p>
<p>0x54</p></td>
<td><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation -
GetInformation()</strong>returns correct InformationBlockSize.</td>
<td><p>Call <strong>GetSupportedTypes()</strong> to</p>
<p>get the valid Information type.</p>
<p>Call <strong>GetInformation ()</strong> the return</p>
<p>status should be <strong>EFI_SUCCESS</strong> and the
InformationBlock != NULL.</p>
<p>Compare the InformationBlockSize</p>
<p>Received from step2 with the expected size. Their size should be
equal.</p></td>
</tr>
<tr class="even">
<td>5.5.11.1.3</td>
<td><p>0xeb7c1cc7,</p>
<p>0x5c94,</p>
<p>0x40c6,0xbe,</p>
<p>0xaf,0x53,</p>
<p>0x08,0xd7,</p>
<p>0xf6,0x35,</p>
<p>0x01</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation
-</strong></p>
<p><strong>GetInformation()</strong> returns
<strong>EFI_UNSUPPORTED</strong>with unknown InformationType.</p></td>
<td>Call <strong>GetInformation ()</strong> with unknown
InformationType, the return status should be
<strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.11.1.4</td>
<td><p>0xab0d01e7,</p>
<p>0x8f70,</p>
<p>0x4a76,0x87,</p>
<p>0x7e,0xa7,</p>
<p>0x13,0xce,</p>
<p>0x00,0x1b,</p>
<p>0x72</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation -
GetInformation()</strong> returns
<strong>EFI_INVALID_PARAMETERS</strong></p>
<p>with NULL InformationBlock.</p></td>
<td>Call <strong>GetInformation ()</strong>with NULL InformationBlock,
the return status should be
<strong>EFI_INVALID_PARAMETERS</strong>.</td>
</tr>
<tr class="even">
<td>5.5.11.1.5</td>
<td><p>0x5a831392,</p>
<p>0x7ee7,</p>
<p>0x4f3e,0xbc,</p>
<p>0xd6,0x32,</p>
<p>0x6d,0x64,</p>
<p>0xf9,0xc2,</p>
<p>0x1c</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation -
GetInformation()</strong> returns
<strong>EFI_INVALID_PARAMETERS</strong></p>
<p>with NULL InformationBlockSize.</p></td>
<td>Call <strong>GetInformation ()</strong>with NULL
InformationBlockSize, the return status should be
<strong>EFI_INVALID_PARAMETERS</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.11.1.6</td>
<td><p>0x2b35c5e2,</p>
<p>0xa25b,</p>
<p>0x48f3,0xab,</p>
<p>0xf7,0xbf,</p>
<p>0x32,0xd2,</p>
<p>0x17,0x1b,</p>
<p>0x93</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.GetInformation -
GetInformation()</strong> returns
<strong>EFI_NOT_FOUND</strong></p>
<p>for an InformationType that is supported but information is unavailable </p> and returns
<strong>EFI_SUCCESS</strong> for an InformationType that is supported and information is available</td>
<td>Call <strong>GetInformation ()</strong> with all known InformationTypes in a loop,
the return status should be either
<strong>EFI_NOT_FOUND</strong> or <strong>EFI_SUCCESS</strong>.
In case of EFI_NOT_FOUND is returned, check for InformationBlockSize to be set to 0</td>
</tr>
</tbody>
</table>

### SetInformation()

<table>
<colgroup>
<col style="width: 13%" />
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
<td>5.5.11.2.1</td>
<td><p>0xeed7dbd9,</p>
<p>0x834c,</p>
<p>0x4dbf,0xa1,</p>
<p>0x8d,0x39,</p>
<p>0x9f,0xdf,</p>
<p>0x19,0xd3,</p>
<p>0xf0</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation -
SetInformation()</strong> returns <strong>EFI_SUCCESS</strong></p>
<p>with valid information type.</p></td>
<td><p>Call <strong>GetSupportedTypes()</strong> to</p>
<p>get the valid Information type.</p>
<p>Call <strong>GetInformation ()</strong> the return</p>
<p>status should be <strong>EFI_SUCCESS</strong> and the
InformationBlock != NULL.</p>
<p>Call SetInformation()the</p>
<p>return status should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_WRITE_PROTECTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.11.2.2</td>
<td><p>0x2e1eae6b,</p>
<p>0x95f1,</p>
<p>0x4189,0xac,</p>
<p>0x02,0xc8,</p>
<p>0x50,0x41,</p>
<p>0x02,0x3c,</p>
<p>0xca</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation -
SetInformation()</strong> returns <strong>EFI_SUCCESS</strong></p>
<p>with valid information type.</p></td>
<td><p>Call <strong>GetSupportedTypes()</strong> to</p>
<p>get the valid Information type.</p>
<p>Call <strong>GetInformation ()</strong> the return</p>
<p>status should be <strong>EFI_SUCCESS</strong> and the
InformationBlock != NULL.</p>
<p>Call <strong>SetInformation()</strong>the</p>
<p>return status should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_WRITE_PROTECTED</strong>.</p>
<p>Call <strong>GetInformation ()</strong>and check</p>
<p>the received information with the Information set by step3. They
should be equal.</p></td>
</tr>
<tr class="even">
<td>5.5.11.2.3</td>
<td><p>0xdb4d7a52,</p>
<p>0x608c,</p>
<p>0x46f7,0xaf,</p>
<p>0x23,0x0b,</p>
<p>0x10,0x1e,</p>
<p>0xc8,0xb8,</p>
<p>0xec</p></td>
<td><p><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation -
SetInformation()</strong> returns <strong>EFI_UNSUPPORTED</strong></p>
<p>with unknown InformationType.</p></td>
<td><p>Call <strong>SetInformation()</strong> with unknown
InformationType, the return</p>
<p>status should be <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.5.11.2.4</td>
<td><p>0xd15882e0,</p>
<p>0xcb55,</p>
<p>0x42f4,0xbb,</p>
<p>0x30,0xcb,</p>
<p>0xa0,0x50,</p>
<p>0x3a,0xad,</p>
<p>0xc9</p></td>
<td><strong>EFI_ADAPTER_INFORMATION_PROTOCOL.SetInformation -
SetInformation()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
or <em>EFI_WRITE_PROTECTED</em> with NULL InformationBlock.</td>
<td><p>Call <strong>SetInformation()</strong>with NULL InformationBlock,
the return</p>
<p>status should be <strong>EFI_INVALID_PARAMETER</strong> </p>
<p>or <strong>EFI_WRITE_PROTECTED.</strong></p></td>
</tr>
</tbody>
</table>


### GetSupportedTypes()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 28%" />
<col style="width: 40%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.5.11.3.1</td>
<td><p>0x59a9f08d,</p>
<p>0xad58,</p>
<p>0x49e0,0x92,</p>
<p>0x7f,0x9b,</p>
<p>0x46,0xbb,</p>
<p>0x62,0x3b,</p>
<p>0x41</p></td>
<td><strong>EFI_ADAPTER_INFORMATION_PROTOCOL. GetSupportedTypes -
GetSupportedTypes()</strong> returns <strong>EFI_SUCCESS.</strong></td>
<td>Call <strong>GetSupportedTypes()</strong> , the return status should
be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.5.11.3.2</td>
<td><p>0xac9f6a14,</p>
<p>0xff26,</p>
<p>0x43d1,0x8c,</p>
<p>0x47,0x61,</p>
<p>0x56,0x00,</p>
<p>0xc4,0x12,</p>
<p>0xf4</p></td>
<td>EFI_ADAPTER_INFORMATION_PROTOCOL. GetSupportedTypes -
GetSupportedTypes() returns EFI_SUCCESS.</td>
<td><p>Call <strong>GetSupportedTypes()</strong> to get the valid
Information type.</p>
<p>The Information type received from step1 should be one of the
probable types.</p></td>
</tr>
<tr class="even">
<td>5.5.11.3.3</td>
<td><p>0xd55b2936,</p>
<p>0x5f3f,</p>
<p>0x40a8,0xb8,</p>
<p>0xa1,0x40,</p>
<p>0x9f,0x59,</p>
<p>0x50,0xda,</p>
<p>0x61</p></td>
<td><strong>EFI_ADAPTER_INFORMATION_PROTOCOL. GetSupportedTypes -
GetSupportedTypes()</strong>returns
<strong>EFI_INVALID_PARAMETER</strong> with NULL InfoTypesBuffer.</td>
<td><p>Call <strong>GetSupportedTypes()</strong>with</p>
<p>NULL InfoTypesBuffer, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="odd">
<td>5.5.11.3.4</td>
<td><p>0x890c711f,</p>
<p>0xce91,</p>
<p>0x4426,0xa5,</p>
<p>0xfd,0x01,</p>
<p>0x0a,0x1c,</p>
<p>0xa5,0x33,</p>
<p>0x5b</p></td>
<td><strong>EFI_ADAPTER_INFORMATION_PROTOCOL. GetSupportedTypes() -
GetSupportedTypes()</strong>returns
<strong>EFI_INVALID_PARAMETER</strong> with NULL
InfoTypesBufferCount.</td>
<td><p>Call <strong>GetSupportedTypes()</strong>with</p>
<p>NULL InfoTypesBufferCount, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>

