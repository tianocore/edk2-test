# Protocols EFI Loaded Image Test

## EFI_LOADED_IMAGE Protocol Test

**Reference Document:**

*UEFI Specification*, EFI_LOADED_IMAGE_PROTOCOL Section.

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 19%" />
<col style="width: 31%" />
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
<td>5.3.1.1.1</td>
<td>0xb324a56f, 0x5714, 0x44b4, 0xa2, 0x0f, 0x6e, 0x9b, 0x13, 0x7b,
0x8d, 0xf9</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL – BS.HandleProtocol()</strong> to
handle Loaded Image Protocol returns <strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle. The return code should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.2</td>
<td>0xbce0c845, 0x4ce1, 0x4c3b, 0x9f, 0x94, 0x84, 0x6c, 0x27, 0x9c,
0x93, 0xd0</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>Revision</em> is
equal to <strong>EFI_IMAGE_INFORMATION_REVISION</strong></td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <em>Revision</em> on each image handle should equal
<strong>EFI_IMAGE_INFORMATION_REVISION</strong>.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.3</td>
<td>0x12b28b7b, 0x8255, 0x4fad, 0xb3, 0x05, 0x81, 0x31, 0x16, 0x71,
0xb2, 0xe1</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>ParentHandle</em>
is equal to the test driver’s image handle</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <em>ParentHandle</em> should be equal to the test driver’s image
handle.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.4</td>
<td>0xb8e8ce9f, 0x3324, 0x4134, 0xab, 0x08, 0x3f, 0x3c, 0x9e, 0xe2,
0x5c, 0x27</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>SystemTable</em> is
not <strong>NULL</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <em>SystemTable</em> should not be <strong>NULL</strong>.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.5</td>
<td>0x3bf1e23d, 0x86e1, 0x4f8a, 0x8c, 0x1a, 0x7f, 0xdc, 0x5c, 0x49,
0x11, 0xb9</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL – DeviceHandle</strong> is not
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <strong>DeviceHandle</strong> should not be
<strong>NULL</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.6</td>
<td>0x7df05248, 0x72ff, 0x40a5, 0x94, 0x8c, 0xc6, 0x47, 0xd1, 0xfd,
0xc1, 0xae</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL -</strong> <em>ImageBase</em> is
not <strong>NULL</strong> and <em>ImageSize</em> is not 0.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <em>ImageBase</em> is not <strong>NULL</strong> and
<em>ImageSize</em> is not 0.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.7</td>
<td>0xfede5dd0, 0x92f6, 0x42de, 0x81, 0x4f, 0xf2, 0xe3, 0x33, 0x9b,
0x5d, 0xe1</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL -</strong> Application image’s
<em>ImageCodeType</em> equals <strong>EfiLoaderCode</strong> and
<em>ImageDataType</em> equals <strong>EfiLoaderData</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. Application image’s <em>ImageCodeType</em> should be
<strong>EfiLoaderCode</strong> and <em>ImageDataType</em> should be
<strong>EfiLoaderData</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.8</td>
<td>0x9ead501b, 0x4a09, 0x4c24, 0xba, 0x47, 0xcf, 0x27, 0xbf, 0xf0,
0x66, 0xdb</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL -</strong>
<strong>BootService</strong> image’s <em>ImageCodeType</em> equals
<strong>EfiBootServiceCode</strong> and <em>ImageDataType</em> equals
<strong>EfiBootServiceData</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <strong>BootService</strong> image’s <em>ImageCodeType</em> equals
<strong>EfiBootServiceCode</strong> and <em>ImageDataType</em> equals
<strong>EfiBootServiceData</strong>.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.9</td>
<td>0x064e5c37, 0xcfaf, 0x4b5a, 0xa2, 0xa0, 0xf6, 0x17, 0xdd, 0x41,
0xa4, 0x12</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL -</strong>
<strong>RuntimeService</strong> image’s <em>ImageCodeType</em> equals
<strong>EfiRuntimeServiceCode</strong> and <em>ImageDataType</em> equals
<strong>EfiRuntimeServiceData</strong>.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. <strong>RuntimeService</strong> image’s <em>ImageCodeType</em>
equals <strong>EfiRuntimeServiceCode</strong> and <em>ImageDataType</em>
equals <strong>EfiRuntimeServiceData</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.10</td>
<td>0xc7606256, 0x8a89, 0x48ce, 0xb5, 0x7b, 0xa1, 0xb0, 0x6b, 0x3c,
0x62, 0x3b</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL – Unload()</strong> is
<strong>NULL</strong> if the image has no Unload function.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. Check on Application Images which have no unload function. Unload
field should be <strong>NULL</strong>.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.11</td>
<td>0xfc2330ce, 0xaa7a, 0x4c64, 0xac, 0x5e, 0xfe, 0xb1, 0xf0, 0xf7,
0xda, 0xc7</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL – Unload()</strong> is not
<strong>NULL</strong> and its address is valid if the image has Unload
function.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. Check on Application Images which have Unload function. Unload
field should be valid and its entry address should be within the range
of [<em>ImageBase</em>, <em>ImageBase</em>+<em>ImageSize</em>]</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.12</td>
<td>0x69cb9798, 0x5b57, 0x4381, 0xb9, 0xb2, 0x54, 0xb9, 0xa2, 0x4b,
0x8d, 0x16</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>LoadOptions</em> is
used in notify function.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename with specified <em>LoadOptions</em>.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. Call <strong>BS.StartImage()</strong>. <em>LoadOptions</em> should
be used.</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.13</td>
<td>0x6da9aef4, 0xdadd, 0x4bda, 0xa7, 0x0d, 0x29, 0x47, 0x0e, 0x05,
0xf3, 0x17</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>LoadOptions</em> is
used in notify function.</td>
<td><p>1. Call <strong>BS.LoadImage()</strong> to get image handle by
filename with specified <em>LoadOptions</em>.</p>
<p>2. Call <strong>BS.HandleProtocol()</strong> to handle Loaded Image
Protocol on each image handle.</p>
<p>3. Call <strong>BS.StartImage()</strong>. <em>LoadOptions</em> should
be used.</p>
<p>4. Unload Image.</p>
<p>5. Change <em>LoadOptions</em> and call
<strong>BS.LoadImage()</strong> again.</p>
<p>6. Call <strong>BS.HandleProtocol()</strong> and
<strong>BS.StartImage()</strong>. Updated <em>LoadOptions</em> value
should be used.</p></td>
</tr>
<tr class="odd">
<td>5.3.1.1.14</td>
<td>0x0caae7f5, 0x0742, 0x458f, 0xbf, 0x02, 0x65, 0x2d, 0x33, 0xa4,
0xf1, 0xab</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>SystemTable</em> is
not <strong>NULL</strong></td>
<td>1. Check on all images in system. <em>SystemTable</em> should not be
<strong>NULL</strong>.</td>
</tr>
<tr class="even">
<td>5.3.1.1.15</td>
<td>0xa7bc2e01, 0x3162, 0x482c, 0xa6, 0x8b, 0x93, 0x9d, 0x0c, 0xf7,
0x9a, 0x45</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>ImageBase</em> is
not <strong>NULL</strong> and <em>ImageSize</em> is not 0</td>
<td>1. Check on all images in system. <em>ImageBase</em> is not
<strong>NULL</strong> and <em>ImageSize</em> is not 0.</td>
</tr>
<tr class="odd">
<td>5.3.1.1.16</td>
<td>0xa3ada89a, 0xef4e, 0x475b, 0xbc, 0x53, 0x00, 0x98, 0xd5, 0xc6,
0x5b, 0xee</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>ImageCodeType</em>
matches with the <em>ImageDataType</em>.</td>
<td><p>1. Check on all images in system.</p>
<p>If <em>ImageCodeType</em> is <strong>EfiLoaderCode</strong>,
<em>ImageDataType</em> should be <strong>EfiLoaderData</strong>;</p>
<p>If <em>ImageCodeType</em> is <strong>EfiBootServicesCode</strong>,
<em>ImageDataType</em> should be
<strong>EfiBootServicesData</strong>;</p>
<p>If <em>ImageCodeType</em> is <strong>EfiRuntimeServicesCode</strong>,
<em>ImageDataType</em> should be
<strong>EfiRuntimeServicesData</strong>;</p></td>
</tr>
<tr class="even">
<td>5.3.1.1.17</td>
<td>0xda215e1d, 0x5ac8, 0x480a, 0xa7, 0x9e, 0xa0, 0x66, 0xb9, 0x74,
0x58, 0x65</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> If
<strong>Unload()</strong> function is not <strong>NULL</strong>, its
address is valid.</td>
<td>1. Check on all images in system. If <strong>Unload()</strong>
function is not <strong>NULL</strong>, its address should be within the
range of [<em>ImageBase</em>,
<em>ImageBase</em>+<em>ImageSize</em>]</td>
</tr>
<tr class="odd">
<td>5.3.1.1.18</td>
<td>0xe2f6c4a6, 0xe2a8, 0x4bab, 0x94, 0xbb, 0x70, 0x44, 0x54, 0xd6,
0x2a, 0xea</td>
<td><strong>EFI_LOADED_IMAGE_PROTOCOL –</strong> <em>Revision</em>
equals <strong>EFI_IMAGE_INFORMATION_REVISION</strong>.</td>
<td>1. Check <em>Revision</em> on all file images. <em>Revision</em>
should be equal to <strong>EFI_IMAGE_INFORMATION_REVISION</strong></td>
</tr>
</tbody>
</table>
