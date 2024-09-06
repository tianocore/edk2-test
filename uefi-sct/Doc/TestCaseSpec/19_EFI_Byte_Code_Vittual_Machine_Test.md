# EFI Byte Code Virtual Machine Test

## EFI_EBC_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_EBC_PROTOCOL Section.

### CreateThunk()

<table>
<colgroup>
<col style="width: 12%" />
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
<td>5.15.1.1.1</td>
<td>0x5de39abd, 0xe9d4, 0x4fee, 0xb4, 0xdd, 0x31, 0x73, 0xb7, 0x35,
0xe3, 0x20</td>
<td><strong>EFI_EBC_PROTOCOL.CreateThunk</strong> - Calling
<strong>CreateThunk()</strong> with an invalid Parameters returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>CreateThunk()</strong> when the EBC image entry
point is not 2-byte aligned.</p>
<p>The return code should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.15.1.1.2</td>
<td>0x6f19a253, 0xc6ff, 0x41a3, 0xa5, 0x8b, 0xa4, 0x57, 0x16, 0xe1,
0x2f, 0x4c</td>
<td><strong>EFI_EBC_PROTOCOL.CreateThunk</strong> - Calling
<strong>CreateThunk()</strong> to create ebc thunk returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>CreateThunk()</strong> to create thunk for the EBC
image.</p>
<p>The return code should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.15.1.1.3</td>
<td>0xcabc5c1e, 0x75a0, 0x4349, 0xab, 0xd8, 0x41, 0x17, 0x7b, 0x25,
0x9e, 0x8a</td>
<td><strong>EFI_EBC_PROTOCOL.CreateThunk</strong> – Calling
<strong>CreateThunk()</strong> invokes the Ebc entry point.</td>
<td><p>Call <strong>CreateThunk()</strong> to create thunk for the EBC
image and invokes the thunk.</p>
<p>The entry point of EBC image must be invoked.</p></td>
</tr>
</tbody>
</table>


### UnloadIImage()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
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
<td>5.15.1.2.1</td>
<td>0x99c53b53, 0x0998, 0x4fda, 0xaa, 0x4e, 0x9c, 0xc4, 0x9a, 0x1c,
0x8a, 0x19</td>
<td><strong>EFI_EBC_PROTOCOL.UnloadImage</strong> - Calling
<strong>UnloadImage()</strong> with an invalid Parameters returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>UnloadImage()</strong> when the image handle is not
recognized as belonging to an EBC image that has been executed.</p>
<p>The return code should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.15.1.2.2</td>
<td>0xecea2853, 0xe14e, 0x493b, 0x9a, 0xb3, 0xcd, 0xa4, 0xc8, 0x32,
0x2c, 0x3e</td>
<td><strong>EFI_EBC_PROTOCOL.UnloadImage</strong> - Calling
<strong>UnloadImage()</strong> unloads ebc thunk.</td>
<td><p>Call <strong>UnloadImage()</strong> to unload the EBC image from
memory.</p>
<p>The return code should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



### RegisterICacheFlush()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
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
<td>5.15.1.3.1</td>
<td>0xf362b36f, 0x819d, 0x45a4, 0xa5, 0xc7, 0xa0, 0x0a, 0x81, 0x2b,
0xf3, 0x5f</td>
<td><strong>EFI_EBC_PROTOCOL.RegisterICacheFlush</strong> - Calling
<strong>RegisterICacheFlush()</strong> registers an ebc callback
function.</td>
<td><p>Call <strong>RegisterICacheFlush()</strong> to register a
callback function.</p>
<p>The return code should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.15.1.3.2</td>
<td>0x26480c1d, 0xac79, 0x46e5, 0xa4, 0xff, 0xec, 0x3e, 0xd5, 0x99,
0x87, 0xec</td>
<td><strong>EFI_EBC_PROTOCOL.RegisterICacheFlush</strong> - Callback
function is invoked after calling <strong>CreateThunk()</strong>.</td>
<td><p>1. Call <strong>RegisterICacheFlush()</strong> to register a
callback function.</p>
<p>2. Call <strong>CreateThunk()</strong> to create thunk for an EBC
image.</p>
<p>The callback function should be invoked.</p></td>
</tr>
</tbody>
</table>


### GetVersion()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
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
<td>5.15.1.4.1</td>
<td>0xce787a92, 0x1ee8, 0x4f65, 0xb7, 0x7c, 0xb4, 0xcd, 0xcf, 0xcd,
0xd3, 0xf2</td>
<td><strong>EFI_EBC_PROTOCOL.GetVersion</strong> - Calling
<strong>GetVersion()</strong> when version pointer is
<strong>NULL</strong> and returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetVersion()</strong> when version pointer is
<strong>NULL</strong>.</p>
<p>The return code should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.15.1.4.2</td>
<td>0x57100f81, 0xe05a, 0x4abf, 0x93, 0xc2, 0x49, 0x1c, 0xf8, 0xd4,
0xb6, 0x7c</td>
<td><strong>EFI_EBC_PROTOCOL.GetVersion</strong> - Calling
<strong>GetVersion()</strong> to get ebc interpreter version returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>Call <strong>GetVersion()</strong> to get the version of the EBC
interpreter.</p>
<p>The return code should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>

