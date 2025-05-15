# Protocols EFI Firmware Management Test Case

## EFI_FIRMWARE_MANAGEMENT_PROTOCOL

**Reference Document:**

*UEFI 2.3 Specification*, Chapter 32.

### GetImageInfo()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.1.1.1.1</td>
<td><p>0xd02b40ae, 0x62f, 0x4155,</p>
<p>0xbb, 0xdd, 0x4, 0x29, 0x18, 0x94, 0xea, 0x31</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImageInfo()</strong>returns</p>
<p>EFI_SUCCESS</p></td>
<td><p>Call function with all valid parameters. The function should
return <strong>EFI_SUCCESS</strong>.</p>
<p>Check for expected return code.</p>
<p>Check <em>*DescriptorVersion</em> is equal to 1.</p>
<p>Check <em>ImageIndex</em> is between 1 and
<em>*DescriptorCount</em>.</p>
<p>Check <em>AttributesSupported</em> has no bits set beyond bit 3.</p>
<p>Check <em>AttributesSetting</em> has no bits set beyond bit 3.</p>
<p>Check Compatibilities bits 1 thru 15 are 0s.</p></td>
</tr>
<tr class="odd">
<td>32.1.2.1.1</td>
<td>0x3789b80e, 0xab70, 0x4dc9, 0xbb, 0xbd, 0x70, 0x63, 0x76, 0x36,
0xab, 0x52</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImageInfo()</strong>returns</p>
<p>EFI_BUFFER_TOO_SMALL</p></td>
<td>Call function with valid parameters, except <em>*ImageInfoSize</em>
= 1. The function should return <strong>EFI_BUFFER_TOO_SMALL</strong>
and <em>*ImageInfoSize</em> > 1.</td>
</tr>
<tr class="even">
<td>32.1.2.1.2</td>
<td>0xca1d7706, 0x256b, 0x464e, 0xb6, 0xee, 0x50, 0x34, 0x1e, 0xec,
0x3c, 0x83</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImageInfo()</strong>returns</p>
<p>EFI_INVALID_PARAMETER</p></td>
<td>Call function with valid parameters, except <em>ImageInfoSize</em>
is NULL. The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>32.1.2.1.3</td>
<td>0x2c6aa8e6, 0x3356, 0x43f4, 0xbc, 0xca, 0xf7, 0xdc, 0x4d, 0x20, 0xbb, 0xf3</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImageInfo()</strong> returns</p>
<p>EFI_BUFFER_TOO_SMALL and ImageInfoSize > 1</p></td>
<td>Call function with valid parameters with <em>ImageInfo = NULL</em> and <em>ImageInfoSize = 0</em>. 
The function should return
<strong>EFI_BUFFER_TOO_SMALL</strong> with <strong>ImageInfoSize > 1</strong>.</td>
</tr>
<tr class="even">
<td>32.1.2.1.4</td>
<td>0x8ee98eb3, 0xee5d, 0x4182, 0xa2, 0x97, 0x2a, 0x00, 0x82, 0xc5, 0xe9, 0x52</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImageInfo()</strong> returns</p>
<p>EFI_INVALID_PARAMETER</p></td>
<td>Call function with with invalid parameters, <em>ImageInfo = NULL</em> and <em>ImageInfoSize = "Not too small"</em>. 
The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>

### GetImage()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.2.1.1.1</td>
<td>0xff704c46, 0x3999, 0x4a28, 0xa3, 0x6e, 0x76, 0x8a, 0xb6, 0xad,
0x89, 0xd8</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImage()</strong>returns</p>
<p><strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong></p></td>
<td><p>Authentication not required.</p>
<p>Call function with all valid parameters. The function should return
<strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.2.2.1.1</td>
<td><p>0x3c8d87b2, 0x6a89, 0x4a6c,</p>
<p>0xbc, 0x75, 0xe6, 0x86, 0xa1, 0x49, 0x13, 0xf0</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImage()</strong>returns</p>
<p><strong>EFI_BUFFER_TOO_SMALL</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>*ImageSize</em> = 1.
The function, if supported, should return
<strong>EFI_BUFFER_TOO_SMALL</strong> and <em>*ImageSize</em> >
1.</p></td>
</tr>
<tr class="even">
<td>32.2.2.1.2</td>
<td><p>0x88031c96, 0x99bf, 0x4d2c,</p>
<p>0x9f, 0x57, 0xa7, 0x2, 0x6a, 0xbc, 0xd3, 0x51</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImage()</strong>returns</p>
<p><strong>EFI_INVALID_PARAMETER</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>Image</em> is NULL.
The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.2.2.1.3</td>
<td>0x7a386361, 0x3a5d, 0x4e58, 0x8a, 0x51, 0x4d, 0x93, 0xb6, 0x55,
0x95, 0xf4</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImage()</strong>returns</p>
<p><strong>EFI_INVALID_PARAMETER</strong> or
<strong>EFI_NOT_FOUND</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>ImageIndex</em> = 0
or <em>ImageIndex</em> = <em>*DescriptorCount</em> + 1. The function
should return <strong>EFI_INVALID_PARAMETER</strong> or
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>32.2.2.1.4</td>
<td>0xd6a77629, 0x5afd, 0x4854, 0x87, 0xc8, 0xee, 0x9f, 0xc5, 0x3d,
0xbe, 0x3d</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetImage()</strong>returns</p>
<p><strong>EFI_SECURITY_VIOLATION</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication required.</p>
<p>Call function with valid parameters, except <em>Image</em> has a
dummy authentication data. The function should return
<strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
</tbody>
</table>

### SetImage()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.3.2.1.1</td>
<td>0x4ea24764, 0xa6b1, 0x43b5, 0xb8, 0xa0, 0xd3, 0x3f, 0xdc, 0x8b,
0xc6, 0xe4</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetImage()</strong>returns</p>
<p><strong>EFI_INVALID_PARAMETER</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>Image</em> is NULL.
The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.3.2.1.2</td>
<td><p>0xc82d1373,</p>
<p>0x1f87,</p>
<p>0x45f4,</p>
<p>0xaf, 0xfc,</p>
<p>0x10, 0xa7,</p>
<p>0xf7, 0xb0,</p>
<p>0x9c, 0xb0</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetImage()</strong>returns</p>
<p><strong>EFI_INVALID_PARAMETER</strong> or
<strong>EFI_ABORTED</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>ImageIndex</em> = 0
or <em>ImageIndex</em> = <em>*DescriptorCount</em> + 1. The function
should return <strong>EFI_INVALID_PARAMETER</strong> or
<strong>EFI_ABORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>32.3.2.1.3</td>
<td><p>0x2410a859,</p>
<p>0xdf6f,</p>
<p>0x4857, 0x92,</p>
<p>0x4a, 0x26,</p>
<p>0x37, 0x7,</p>
<p>0x11, 0xf,</p>
<p>0x1c</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetImage()</strong>returns</p>
<p><strong>EFI_SECURITY_VIOLATION</strong></p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>ImageIndex</em> = 0
or <em>ImageIndex</em> = <em>*DescriptorCount</em> + 1. The function
should return <strong>EFI_INVALID_PARAMETER</strong> or
<strong>EFI_ABORTED</strong>.</p>
<p><em>Image</em> has dummy authentication data.</p>
<p>The function should return</p>
<p><strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
</tbody>
</table>

### CheckImage()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.4.2.1.1</td>
<td>0x3987172c, 0xe6a0, 0x4099, 0xb1, 0x2b, 0xd8, 0xef, 0xf2, 0x62,
0x75, 0x93</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.CheckImage()</strong>returns</p>
<p>EFI_INVALID_PARAMETER</p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except <em>Image</em> is NULL.
The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.4.2.1.2</td>
<td><p>0xd6dad28e, 0x7f0f, 0x4f56,</p>
<p>0x9a, 0x93, 0x14, 0x7d, 0xb3, 0x74, 0x0, 0xc9</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.CheckImage()</strong>returns</p>
<p>EFI_SECURITY_VIOLATION</p></td>
<td><p>Function is supported.</p>
<p>Authentication required.</p>
<p>Call function with valid parameters, except <em>Image</em> has a
dummy authentication data. The function should return
<strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
</tbody>
</table>

### GetPackageInfo()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.5.1.1.1</td>
<td>0x70884539, 0x9a34, 0x4146, 0x83, 0x3a, 0x4d, 0x89, 0x8b, 0x9c,
0x7e, 0xa4</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.GetPackageInfo()</strong>returns</p>
<p><strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong></p></td>
<td><p>Call function with all valid parameters. The function should
return <strong>EFI_SUCCESS</strong> or
<strong>EFI_UNSUPPORTED</strong>.</p>
<p>Check <em>*AttributesSupported</em> has no bits set beyond bit 2.</p>
<p>Check <em>*AttributesSetting</em> has no bits set beyond bit
2.</p></td>
</tr>
</tbody>
</table>

### SetPackageInfo()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
<col style="width: 25%" />
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
<td>32.6.2.1.1</td>
<td>0xb5288fc3, 0xe906, 0x4468, 0x83, 0x3d, 0xd4, 0xa6, 0x58, 0xa5,
0x4f, 0xbd</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetPackageInfo()</strong>returns</p>
<p>EFI_INVALID_PARAMETER</p></td>
<td><p>Function is supported.</p>
<p>Authentication not required.</p>
<p>Call function with valid parameters, except
<em>**PackageVersionName</em> is longer than the value returned in
<em>*PackageVersionNameMaxLen</em>. The function should return
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.6.2.1.2</td>
<td><p>0x57355301, 0x1343, 0x497f,</p>
<p>0xbe, 0xe0, 0x8e, 0x5c, 0x27, 0xd2, 0x40, 0x2</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetPackageInfo()</strong>returns</p>
<p>EFI_SECURITY_VIOLATION</p></td>
<td><p>Function is supported.</p>
<p>Authentication is required.</p>
<p>Call function with valid parameters, except <em>Image</em> is NULL.
The function should return
<strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
<tr class="even">
<td>32.6.2.1.3</td>
<td><p>0xadeab82d, 0x7592, 0x40fe,</p>
<p>0x87, 0xa8, 0x93, 0x2b, 0xad, 0x97, 0xff, 0x5e</p></td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetPackageInfo()</strong>returns</p>
<p>EFI_SECURITY_VIOLATION</p></td>
<td><p>Function is supported.</p>
<p>Authentication is required.</p>
<p>Call function with valid parameters, except <em>ImageSize</em> is 0.
The function should return
<strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
<tr class="odd">
<td>32.6.2.1.4</td>
<td>0x9be658d2, 0x1312, 0x4254, 0x91, 0x10, 0x59, 0x0, 0xd5, 0xfd, 0x6c,
0x6c</td>
<td><p><strong>EFI_FIRMWARE_MANAGEMENT_PROTOCOL.SetPackageInfo()</strong>returns</p>
<p>EFI_SECURITY_VIOLATION</p></td>
<td><p>Function is supported.</p>
<p>Authentication is required.</p>
<p>Call function with valid parameters, except <em>Image</em> has a
dummy authentication data. The function should return
<strong>EFI_SECURITY_VIOLATION</strong>.</p></td>
</tr>
</tbody>
</table>
