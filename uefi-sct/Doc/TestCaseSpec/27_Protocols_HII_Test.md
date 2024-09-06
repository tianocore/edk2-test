# Protocols HII Test

## EFI_HII_FONT_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_FONT_PROTOCOL Section.

### StringToImage()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 17%" />
<col style="width: 27%" />
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
<td>5.18.1.1.1</td>
<td><p>0x6fca8706, 0x7d83, 0x4914,</p>
<p>0x8a, 0x16, 0x92, 0x0b, 0x07, 0xb1, 0x68, 0xb9</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>String</strong> been <strong>NULL</strong>.</td>
<td>Call <strong>StringToImage()</strong> with valid parameters except
<strong>String</strong> being <strong>NULL</strong>, The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.1.1.2</td>
<td><p>0x80ee2790, 0x9ff7, 0x4abe,</p>
<p>0x90, 0xaf, 0x05, 0x4a, 0x86, 0x69, 0xba, 0x51</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with <strong>Blt</strong>
been <strong>NULL.</strong></td>
<td>Call <strong>StringToImage()</strong> with valid parameters except
<strong>Blt</strong> being <strong>NULL</strong>, The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.1.1.3</td>
<td><p>0xe2f66ec3, 0x585a, 0x45ba,</p>
<p>0x8f, 0x7a, 0xd5, 0x18, 0x5f, 0xeb, 0x4e, 0x9a</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with wrong flag
combination<strong>.</strong></td>
<td>Call <strong>StringToImage()</strong> with <strong>Flag</strong>
being <strong>EFI_HII_OUT_FLAG_CLEAN_X</strong> with
<strong>EFI_HII_OUT_FLAG_WRAP</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.1.1.4</td>
<td><p>0xabf68512, 0x0bb8, 0x4ef8,</p>
<p>0x97, 0xc1, 0xda, 0x93, 0x55,0xda, 0x1b, 0x07</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with wrong flag
combination<strong>.</strong></td>
<td>Call <strong>StringToImage()</strong> with <strong>Flag</strong>
being <strong>EFI_HII_OUT_FLAG_CLEAN_X</strong> without
<strong>EFI_HII_OUT_FLAG_CLIP</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.1.1.5</td>
<td>0x6ff9c8b4, 0xeb8f, 0x4e0b, 0x9a, 0x97, 0x82, 0x94, 0x37, 0x0c,
0xdd, 0x3c</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td>Call <strong>StringToImage()</strong> with valid paramenters and use
<strong>EFI_GRAPHICS_OUTPUT_BLT_PIXEL</strong> structure in
<strong>EFI_IMAGE_OUTPUT</strong> structure.</td>
</tr>
<tr class="odd">
<td>5.18.1.1.6</td>
<td>0x182cc281, 0xb462, 0x458f, 0xaa, 0xb6, 0xca, 0x98, 0xb5, 0x27,
0x37, 0x31</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td>Call <strong>StringToImage()</strong> with valid paramenters and use
<strong>EFI_GRAPHICS_OUTPUT_PROTOCOL</strong> in
<strong>EFI_IMAGE_OUTPUT</strong> structure.</td>
</tr>
<tr class="even">
<td>5.18.1.1.7</td>
<td>0xcdf439d0, 0xe471, 0x4fe7, 0x86, 0x98, 0xf5, 0xb0, 0x5c, 0xcd,
0xa6, 0xae</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters for all ASCII
visible characters. Each images must equal to sys default glyph.</td>
<td><p>Call <strong>StringToImage()</strong> with valid paramenters and
<strong>StringInfo</strong> = NULL..</p>
<p>Compare image output with system default font glyph image</p></td>
</tr>
<tr class="odd">
<td>5.18.1.1.8</td>
<td>0xa8f40eac, 0x8633, 0x40ca, 0x95, 0x6d, 0x75, 0xb2, 0x81, 0x50,
0x75, 0x39</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters for all ASCII
visible characters. Each image must equal to the specific font
glyph.</td>
<td><p>Register a specific font package</p>
<p>Call <strong>StringToImage()</strong> with valid paramenters and
<strong>StringInfo</strong> = specific font. Compare image output with
specific font glyph image registered</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.9</td>
<td>0x42dc1626, 0x36ce, 0x421b, 0x8d, 0x66, 0x21, 0xb8, 0xaa, 0x43,
0x6c, 0x7b</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameters
<strong>EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td>1.Call <strong>StringToImage</strong>() with
<strong>EFI_HII_DIRECT_TO_SCREEN</strong>. For the final row, the
<strong>RowInfoArray.LineHeight</strong> and
<strong>RowInfoArray.BaseLine</strong> may describe pixels which are
outside the limit specified by Blt. Height (unless
<strong>EFI_HII_OUT_FLAG_CLIP_CLEAN_Y</strong> is specified) even though
those pixels were not drawn. 2.The return code should be
<strong>EFI_SUCCESS</strong> .</td>
</tr>
<tr class="odd">
<td>5.18.1.1.10</td>
<td>0xf8b5b9b6, 0xc3c6, 0x4993, 0x9b, 0x3c, 0xbc, 0x8d, 0x91, 0xee,
0x8c, 0x20</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td>1.Call StringToImage with <strong>EFI_HII_OUT_FLAG_CLIP |
EFI_HII_DIRECT_TO_SCREEN</strong>. For the final row, the
<strong>RowInfoArray.LineHeight</strong> and RowInfoArray.BaseLine 'May'
describe pixels which are outside the limit specified by Blt. Height
(unless <strong>EFI_HII_OUT_FLAG_CLIP_CLEAN_Y</strong> is specified)
even though those pixels were not drawn. 2.The return code should be
<strong>EFI_SUCCESS</strong> .</td>
</tr>
<tr class="even">
<td>5.18.1.1.11</td>
<td><p>0x4c70adb5, 0xcc05, 0x435a,</p>
<p>0x8c, 0xc4, 0xce, 0xd1, 0x54, 0x6e, 0xd7, 0xf6</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td>1.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X |
EFI_HII_DIRECT_TO_SCREEN</strong>. If a character's right-most on pixel
cannot fit, then it will not be drawn at all. 2.The return code should
be <strong>EFI_SUCCESS</strong> .</td>
</tr>
<tr class="odd">
<td>5.18.1.1.12</td>
<td><p>0xa000d36f, 0x2918, 0x448c,</p>
<p>0xad, 0x6d, 0x15, 0x77, 0xb5, 0x2f, 0xdc, 0x66</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td><p>1.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y |
EFI_HII_DIRECT_TO_SCREEN</strong>. If a row's bottom-most pixel exceed
screen <em>Height</em>, then it will not be drawn at all.</p>
<p>2.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.13</td>
<td><p>0x266f881, 0x409b, 0x47e5,</p>
<p>0x8f, 0x22, 0x21, 0x7d, 0x14, 0xa4, 0x8a, 0xab</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN</strong> and <em>String</em> with line break
opportunity</td>
<td><p>1.Call StringToImage() with <strong>EFI_HII_IGNORE_IF_NO_GLYPH |
EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN</strong> and
<em>String</em> with line break opportunity (SPACE is a line break
opportunity). Check display will wrapper at right place.</p>
<p>2.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="odd">
<td>5.18.1.1.14</td>
<td><p>0x2fa4edd2, 0xa193, 0x4882,</p>
<p>0xae, 0x1e, 0xeb, 0xfe, 0xf5, 0x57, 0x42, 0xcc</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN</strong> and
<em>String</em> without line break opportunity</td>
<td><p>1.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN</strong> and
<em>String</em> without line break opportunity. <em>String</em> is
designed to display as if <strong>EFI_HII_OUT_FLAG_CLIP_CLEAN_X</strong>
is set.</p>
<p>2.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.15</td>
<td>0x57300788, 0xba79, 0x4727, 0xb5, 0xe6, 0xe9, 0x20, 0xcd, 0x7e,
0xd6, 0x93</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage -StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td>1.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN.</strong>
If a row's bottom-most pixel cannot fit, then it will not be drawn at
all. This flag requires that <strong>EFI_HII_OUT_FLAG_CLIP</strong> be
set. 2.The return code should be <strong>EFI_SUCCESS</strong> .</td>
</tr>
<tr class="odd">
<td>5.18.1.1.16</td>
<td>0xf3b0daef, 0xab51, 0x4ebc, 0x93, 0x51, 0x74, 0xf6, 0x18, 0xaa,
0x9f, 0x9f</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_DIRECT_TO_SCREEN</strong>. 3.Check
<strong>EFI_HII_DIRECT_TO_SCREEN</strong> only case If
<strong>Blt</strong> is not NULL, then
<strong>EFI_HII_OUT_FLAG_CLIP</strong> is implied <em>String</em> is
designed to displayed with one full line 4.The return code should be
<strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.17</td>
<td><p>0x23ab3935, 0x483c, 0x4d75,</p>
<p>0xab, 0x3, 0xef, 0x50, 0x32, 0xea, 0x30, 0xbf</p></td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_CLIP</strong>.</p>
<p>3. For the final row, the <strong>RowInfoArray.LineHeight</strong>
and <strong>RowInfoArray.BaseLine</strong> may describe pixels which are
outside the limit specified by <strong>Blt</strong>.
<strong>Height</strong> (unless
<strong>EFI_HII_OUT_FLAG_CLIP_CLEAN_Y</strong> is specified) even though
those pixels were not drawn. 4.The return code should be
<strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="odd">
<td>5.18.1.1.18</td>
<td>0x9e992f5a, 0x4a3b, 0x44d8, 0x89, 0x47, 0xca, 0x30, 0x92, 0x2b,
0x69, 0xa5</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X |
EFI_HII_DIRECT_TO_SCREEN</strong>. 3. If a character's right-most on
pixel cannot fit, then it will not be drawn at all.</p>
<p>4.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.19</td>
<td>0xc8999c53, 0xd56, 0x4545, 0xbc, 0x55, 0x91, 0xf0, 0xd1, 0x1, 0x60,
0x4a</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y |
EFI_HII_DIRECT_TO_SCREEN</strong>. 3.If a row's bottom-most pixel exceed
screen <strong>Height</strong>, then it will not be drawn at all.</p>
<p>4.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="odd">
<td>5.18.1.1.20</td>
<td>0x9b71db4d, 0x5a06, 0x4246, 0x83, 0xd2, 0x9d, 0x31, 0x70, 0x73,
0x63, 0xd0</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN</strong> and <em>String</em> with line break
opportunity</td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN</strong> and <em>String</em> with line break
opportunity (SPACE is a line-break). 3.Check if the display is right.
4.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.21</td>
<td>0xb0e526b1, 0xc399, 0x4e31, 0xb2, 0x97, 0xc1, 0x29, 0x18, 0x37,
0x95, 0x79</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN</strong> and
<em>String</em> without line break opportunity</td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN</strong> and
<em>String</em> without line break opportunity.</p>
<p>3. <em>String</em> is designed to display as if
<strong>EFI_HII_OUT_FLAG_CLIP_CLEAN_X</strong> is set.</p>
<p>4.The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
<tr class="odd">
<td>5.18.1.1.22</td>
<td>0xcbdae1b4, 0xc99b, 0x4a08, 0x9b, 0xf9, 0x76, 0x69, 0x77, 0x71,
0x66, 0x30</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_IGNORE_LINE_BREAK | EFI_HII_DIRECT_TO_SCREEN</strong>.
3. If a row's bottom-most pixel cannot fit, then it will not be drawn at
all. This flag requires that <strong>EFI_HII_OUT_FLAG_CLIP</strong> is
set. 4. The return code should be <strong>EFI_SUCCESS</strong>
.</p></td>
</tr>
<tr class="even">
<td>5.18.1.1.23</td>
<td>0x36a9a186, 0x363f, 0x4b4b, 0xa3, 0xaf, 0xa9, 0x9b, 0x29, 0x7a,
0x6d, 0x41</td>
<td><strong>HII_FONT_PROTOCOL.StringToImage - StringToImage()</strong>
returns <strong>EFI_SUCCESS</strong> with parameter
<strong>EFI_HII_OUT_FLAG_TRANSPARENT</strong></td>
<td><p>1.Register a new font package</p>
<p>2.Call <strong>StringToImage()</strong> with
<strong>EFI_HII_OUT_FLAG_TRANSPARENT</strong>.</p>
<p>3. Check output buffer StringInfo background should be ignored
according to EFI spec.</p>
<p>4. The return code should be <strong>EFI_SUCCESS</strong> .</p></td>
</tr>
</tbody>
</table>


### StringIdToImage()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.1.2.1 | 0xf4e2c51e, 0x92a3, 0x4752, 0x92, 0x64, 0x27, 0xb1, 0x54, 0x21, 0x70, 0x3a | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_INVALID_PARAMETER** with **Blt** been **NULL**. | Call **StringIdToImage()** with valid parameters except **Blt** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.2.2 | 0x9aecc9b3, 0x3bff, 0x4c7c, 0x96, 0x6b, 0xa9, 0x64, 0x84, 0xfe, 0xd9, 0x89 | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_INVALID_PARAMETER** with **PackageList** been **NULL**. | Call **StringIdToImage()** with valid parameters except **PackageList** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.2.3 | 0x479e2e87, 0xf833, 0x4d2b, 0xbb, 0x47, 0x16, 0x77, 0x7b, 0x52, 0xb6, 0x6a | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_NOT_FOUND** with an invalid **PackageList**. | Call **StringIdToImage()** with valid parameters except an invalid **PackageList**, The return status should be **EFI_NOT_FOUND**. |
| 5.18.1.2.4 | 0xe1d5168a, 0x26da, 0x4000, 0xa9, 0xc8, 0x15, 0x85, 0xee, 0xea, 0x38, 0x33 | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_NOT_FOUND** with **StringId** not in PackageList. | Call **StringIdToIamge()** with a **StringId** which isn’t in **PackageList**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.1.2.5 | 0xfba0a646, 0x9942, 0x4790, 0x86, 0xef, 0xe8, 0x52, 0x32, 0xf1, 0xb5, 0xeb | **HII_FONT_PROTOCOL.StringIdToImage - StringToImage()** returns **EFI_INVALID_PARAMETER** with **invalid Flags combination.** | Call **StringIdToImage()** with **Flag** being **EFI_HII_OUT_FLAG_CLEAN_X** with **EFI_HII_OUT_FLAG_WRAP**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.2.6 | 0xd9b59551, 0xa799, 0x4c87, 0x89, 0xb3, 0x89, 0xc5, 0x6a, 0xb8, 0x43, 0x9f | **HII_FONT_PROTOCOL.StringIdToImage - StringToImage()** returns **EFI_INVALID_PARAMETER** with **invalid Flags combination.** | Call **StringIdToImage()** with **Flag** being **EFI_HII_OUT_FLAG_CLEAN_X** without **EFI_HII_OUT_FLAG_CLIP**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.2.7 | 0x3df4b27f, 0x7b07, 0x4a3d, 0xaa, 0x09, 0x60, 0xfa, 0xbe, 0x82, 0x99, 0x9f | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_SUCCESS** with valid parameters. | Call **StringIdToImage()** with valid paramenters and use **EFI_GRAPHICS_OUTPUT_BLT_PIXEL** structure in **EFI_IMAGE_OUTPUT** structure. The return status should **EFI_SUCCESS**. |
| 5.18.1.2.8 | 0xedcca70f, 0xcb25, 0x4d22, 0x98, 0x5e, 0x18, 0x86, 0x66, 0x8c, 0xc1, 0x9c | **HII_FONT_PROTOCOL.StringIdToImage - StringIdToImage()** returns **EFI_SUCCESS** with valid parameters. | Call **StringIdToImage()** with valid paramenters and use **EFI_GRAPHICS_OUTPUT_PROTOCOL** in **EFI_IMAGE_OUTPUT** structure. The return status should **EFI_SUCCESS**. |


### GetGlyph()

|  |  |  |  |
|----|----|----|----|
|  |  |  |  |
| 5.18.1.3.1 | 0xb94b394f, 0x8e3e, 0x4adc, 0x8f, 0x5c, 0x64, 0x12, 0x69, 0xa2, 0xed, 0xfe | **HII_FONT_PROTOCOL.GetGlyph - GetGlyph()** returns **EFI_INVALID_PARAMETER** with **Blt** being **NULL**. | Call **GetGlyph()** with **Blt** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.3.2 | 0xee445b90, 0xf370, 0x43fd, 0x83, 0xff, 0x00, 0x2d, 0x29, 0x1e, 0xcd, 0x42 | **HII_FONT_PROTOCOL.GetGlyph - GetGlyph()** returns **EFI_INVALID_PARAMETER** with non **NULL** **\*Blt**. | Call **GetGlyph()** with non **NULL** **Blt**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.3.3 | 0x0687a598, 0xa2a6, 0x4073, 0xa7, 0x4f, 0x05, 0xae, 0x9c, 0xe2, 0x1e, 0x33 | **HII_FONT_PROTOCOL.GetGlyph - GetGlyph()** returns **EFI_SUCCESS** with valid parameters. | Call **GetGlyph()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### GetFontInfo()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.1.4.1 | 0xf43589d3, 0xfccd, 0x413f, 0xb7, 0x50, 0xf8, 0xb4, 0x00, 0xd2, 0x92, 0x7b | **HII_FONT_PROTOCOL.GetFontInfo - GetFontInfo()** returns **EFI_INVALID_PARAMETER** with invalid **EFI_FONT_INFO_MASK** Combination. | Call **GetFontInfo()** with **StringInfoIn**-\>**FontInfoMask** being invalid combination. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.1.4.2 | 0x6e5210d4, 0xead5, 0x4042, 0xac, 0x30, 0xa4, 0xfb, 0x8f, 0x9f, 0xf1, 0x9a | **HII_FONT_PROTOCOL.GetFont - GetFont()** returns **EFI_SUCCESS** with valid parameters | Call **GetFontInfo()** with valid parameters. The return status should be **EFI_SUCCESS**. |
| 5.18.1.4.3 | 0x88294411, 0x3dd7, 0x4030, 0xb6, 0x40, 0x65, 0xa3, 0x85, 0x7b, 0x2f, 0x46 | **HII_FONT_PROTOCOL.GetFont - GetFont()** returns **EFI_SUCCESS** with valid parameters(StringInfoIn is **NULL**) | Call **GetFontInfo()** with valid parameters(StringInfoIn is **NULL**). The return status should be **EFI_SUCCESS**. |



## EFI_HII_STRING_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_STRING_PROTOCOL Section.

### NewString()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.2.1.1 | 0xb0eb04d6, 0x3328, 0x4157, 0xa8, 0x8e, 0xe9, 0x9a, 0x15, 0x62, 0x6b, 0x88 | **HII_STRING_PROTOCOL.NewString - NewString()** returns **EFI_INVALID_PARAMETER** with **StringId** being **NULL**. | Call **NewString()** with **StringId** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.1.2 | 0x9223196c, 0xadf1, 0x4181, 0xbc, 0xc3, 0x1d, 0x9e, 0xa4, 0xcf, 0x7a, 0x8e | **HII_STRING_PROTOCOL.NewString - NewString()** returns **EFI_INVALID_PARAMETER** with **Language** being **NULL**. | Call **NewString()** with **Language** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.1.3 | 0x8d9e83aa, 0x9bf1, 0x4466, 0xba, 0xba, 0xec, 0x14, 0xfd, 0xb3, 0x82, 0x14 | **HII_STRING_PROTOCOL.NewString - NewString()** returns **EFI_INVALID_PARAMETER** with **String** being **NULL**. | Call **NewString()** with **String** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.1.4 | 0x23b3df9d, 0x2330, 0x4db7, 0xa1, 0x71, 0x0c, 0x2a, 0x61, 0xb7, 0xd2, 0x24 | **HII_STRING_PROTOCOL.NewString - NewString()** returns **EFI_INVALID_PARAMETER** with **PackageLis**t beinf **NULL**. | Call **NewString()** with **PackageList** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.1.5 | 0x2077cb3b, 0xb8b4, 0x4ba9, 0xab, 0x49, 0x36, 0xc4, 0xe3, 0xb7, 0x1e, 0xb5 | **HII_STRING_PROTOCOL.NewString - NewString()** returns **EFI_SUCCESS** with valid parameters and result checked. | Part 1: Call **NewString()** with valid parameters. The return Status should be **EFI_SUCCESS**. |
| 5.18.2.1.6 | 0x8cd4cc42, 0xe5f0, 0x4f6f, 0x9f, 0x7d, 0x60, 0x47, 0x95, 0xd5, 0x05, 0x36 | **HII_STRING_PROTOCOL.NewString** - output the string and compare with the original string. | Part2: Call **GetString()** to check the output string with the original string. They should be same. |


### GetString()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
<col style="width: 31%" />
<col style="width: 38%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.2.2.1</td>
<td><p>0x640acc2d, 0x1174, 0x4735,</p>
<p>0x94, 0xb3, 0xbc, 0xe2, 0xca, 0xbb, 0x92, 0xc1</p></td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_NOT_FOUND</strong> with <strong>StringId</strong> being
invalid.</td>
<td>Call <strong>GetString()</strong> with an invalid
<strong>StringId</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.2.2</td>
<td>0x3c0c9dfe, 0xe56e, 0x43ee, 0x80, 0x26, 0x55, 0xb1, 0x14, 0x29,
0x2c, 0x38</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_NOT_FOUND</strong> with an invalid
<strong>PackageList</strong>.</td>
<td>Call <strong>GetString()</strong> with an invalid
<strong>PackageList</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.2.3</td>
<td>0x0460a672, 0xcba9, 0x4ee8, 0x9e, 0x43, 0x9d, 0xba, 0x85, 0x52,
0x3f, 0xab</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with <strong>StringSize</strong>
indicates the <strong>String</strong> is too small.</td>
<td>Call <strong>GetString()</strong> with <strong>StringSize</strong>
which indicates the <strong>String</strong> buffer is small. The return
status should <strong>EFI_BUFFER_TOO_SMALL</strong>. The
<strong>StringSize</strong> is updated with the required size.</td>
</tr>
<tr class="odd">
<td>5.18.2.2.4</td>
<td>0xeed5460f, 0x826e, 0x4e1b, 0xad, 0x79, 0xb7, 0x3b, 0x58, 0xc9,
0x57, 0x01</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_INVALID_LANGUAGE</strong> with <strong>string</strong> is
not in the specified Language.</td>
<td>Call <strong>GetString()</strong> with string specified by
<strong>StringId</strong> is available but not in the specified
<strong>Language</strong>. The return status should be
<strong>EFI_INVALID_LANGUAGE</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.2.5</td>
<td>0xafd0b70c, 0xe1b4, 0x43c1, 0x94, 0x60, 0x96, 0xf5, 0x3e, 0xe9,
0xaa, 0xe9</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Language</strong>
being <strong>NULL</strong>.</td>
<td>Call <strong>GetString()</strong> with <strong>Language</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.2.6</td>
<td>0xcf15f5f5, 0x7eaf, 0x4e63, 0x80, 0xd2, 0x5c, 0x9b, 0x89, 0x02,
0x1b, 0xf8</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>String</strong>
being <strong>NULL</strong>.</td>
<td>Call <strong>GetString()</strong> with <strong>String</strong> being
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.2.7</td>
<td>0xc37a209f, 0xaeab, 0x4152, 0xbf, 0x74, 0x27, 0x27, 0xea, 0x48,
0x4f, 0x38</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>StringSize</strong>
being <strong>NULL</strong>.</td>
<td>Call <strong>GetString()</strong> with <strong>StringSize</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.2.8</td>
<td>0x62a545c3, 0x3da2, 0x4f46, 0xb9, 0x07, 0xd4, 0xfe, 0x3e, 0xdf,
0x59, 0xc0</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>PackageList</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>GetString()</strong> with <strong>PackageList</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.2.9</td>
<td>0x276f380d, 0x96d6, 0x46d5, 0x8a, 0xbb, 0x2a, 0xf3, 0xb7, 0x3c,
0x2d, 0x43</td>
<td><strong>HII_STRING_PROTOCOL.GetString - GetString()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters and the result
checked.</td>
<td><p>Step1: Call <strong>NewString()</strong> with valid
parameters.</p>
<p>Step2: Call <strong>GetString()</strong> with valid parameters. The
return status should be <strong>EFI_SUCCESS</strong>. The output string
should be same with the original one.</p></td>
</tr>
</tbody>
</table>


### SetString()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 29%" />
<col style="width: 39%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.2.3.1</td>
<td><p>0xb7d699ce, 0xb3e9, 0x4327,</p>
<p>0x8b, 0x52, 0xdd, 0xd5, 0xa2, 0xff, 0xb9, 0x0c</p></td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_NOT_FOUND</strong> with <strong>StringId</strong> been
invalid.</td>
<td>Call <strong>SetString()</strong> with an invalid
<strong>StringId</strong> which is not in the database. The return
status should be <strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.3.2</td>
<td>0xfda7ec68, 0xbf34, 0x4086, 0xad, 0x72, 0x26, 0xe1, 0xd6, 0xdd,
0x45, 0x48</td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Languag</strong>e
been <strong>NULL</strong>.</td>
<td>Call <strong>SetString()</strong> with <strong>Language</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.3.3</td>
<td>0xb66221c2, 0xc6e7, 0x4129, 0xb3, 0x83, 0xa6, 0x51, 0x26, 0x2b,
0xcf, 0x57</td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>String</strong> been
<strong>NULL</strong>.</td>
<td>Call <strong>SetString()</strong> with <strong>String</strong> being
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.3.4</td>
<td>0x7439d8aa, 0xe2f6, 0x4c3b, 0x98, 0x0c, 0x13, 0xbd, 0xab, 0x97,
0xff, 0x95</td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_NOT_FOUND</strong> with an invalid
<strong>PackageList</strong>.</td>
<td>Call <strong>SetString()</strong> with an invalid
<strong>PackageList</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.3.5</td>
<td>0x66495376, 0x042b, 0x460a, 0xbb, 0x45, 0x19, 0xfd, 0x13, 0xf2,
0xe0, 0x2c</td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>PackageList</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>SetString()</strong> with <strong>PackageList</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.2.3.6</td>
<td>0xf346d13b, 0xcbd0, 0x451f, 0xa6, 0x93, 0x75, 0xf1, 0xe9, 0xdd,
0x1f, 0x74</td>
<td><strong>HII_STRING_PROTOCOL.SetString - SetString()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters and result
checked</td>
<td>Part 1: Call <strong>SetString()</strong> with valid parameters. The
return status should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.18.2.3.7</td>
<td>0xbf8f4ae6, 0xf506, 0x43d2, 0xa6, 0x43, 0xa7, 0xb4, 0xb2, 0x33,
0xe8, 0xe0</td>
<td><strong>HII_STRING_PROTOCOL.SetString</strong> - output the string
and compare with the reset string.</td>
<td>Part2: Call <strong>GetString()</strong> to check the output string
with the original string. They should be same.</td>
</tr>
</tbody>
</table>


### GetLanguages()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.2.4.1 | 0x7a983202, 0x322e, 0x4d12, 0x90, 0xb3, 0xcf, 0x8b, 0x6e, 0xc4, 0x97, 0x5b | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_INVALID_PARAMETER** with **Language**s been **NULL**. | Call **GetLanguages()** with **Languages** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.4.2 | 0xa9299182, 0xcd9a, 0x4014, 0xb4, 0x03, 0xe2, 0x67, 0xc7, 0xf4, 0x80, 0x7f | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_INVALID_PARAMETER** with **LanguagesSize** been **NULL**. | Call **GetLanguages()** with **LanguagesSize** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.4.3 | 0x83a0f73c, 0xdd2c, 0x4652, 0x8e, 0xbe, 0x32, 0xd5, 0xf9, 0x8e, 0x24, 0xef | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_NOT_FOUND** with an invalid **PackageList**. | Call **GetLanguages()** with an invalid **PackageList**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.4.4 | 0x696870ed, 0xfff5, 0x4b76, 0x9f, 0x82, 0xbe, 0x78, 0xf6, 0x58, 0x9b, 0x8b | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_INVALID_PARAMETER** with **PackageList** been **NULL**. | Call **GetLanguages()** with **PackageList** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.2.4.5 | 0x65dca7c5, 0x85a0, 0x48a0, 0x9a, 0x49, 0xa9, 0xbb, 0xae, 0xa2, 0x55, 0xf3 | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_BUFFER_TOO_SMALL** with **LanguagesSize** indicates the **Languages** is too small. | Call **GetLanguages()** with **LanguagesSize** which indicates the **Languages** buffer is small. The return status should **EFI_BUFFER_TOO_SMALL**. The **LanguagesSize** is updated with the required size. |
| 5.18.2.4.6 | 0xba61367b, 0x33b6, 0x41cc, 0x94, 0x60, 0x54, 0x75, 0xf1, 0xe5, 0x81, 0x89 | **HII_STRING_PROTOCOL.GetLanguages - GetLanguages()** returns **EFI_SUCCESS** with valid parameters. | Call **GetLanguages()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### GetSecondaryLanguages()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.2.5.1 | 0xff558856, 0xcf19, 0x47b2, 0x89, 0xc0, 0xdb, 0xdf, 0x0e, 0xf5, 0x31, 0xe2 | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_INVALID_PARAMETER** with **FirstLanguage** been **NULL**. | Call **GetSecondaryLanguages()** with **FirstLanguage** being **NULL**. The return status should **EFI_INVALID_PARAMETER**. |
| 5.18.2.5.2 | 0x05c043da, 0xd0dd, 0x4833, 0xa1, 0x27, 0x92, 0x3b, 0x6a, 0x58, 0x05, 0xdc | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_INVALID_PARAMETER** with **SecondLanguages** been **NULL**. | Call **GetSecondaryLanguages()** with **SecondLanguages** being **NULL**. The return status should **EFI_INVALID_PARAMETER**. |
| 5.18.2.5.3 | 0xa891d992, 0x6296, 0x4670, 0xa5, 0xbe, 0x5c, 0x53, 0xaa, 0xc0, 0x34, 0x48 | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_INVALID_PARAMETER** with **SecondLanguagesSize** been **NULL**. | Call **GetSecondaryLanguages()** with **SecondLanguagesSize** being **NULL**. The return status should **EFI_INVALID_PARAMETER**. |
| 5.18.2.5.4 | 0x050d991f, 0xd6f0, 0x4a07, 0x91, 0x6d, 0x58, 0xde, 0xc2, 0xec, 0xf3, 0x2f | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_NOT_FOUND** with an invalid **PackageList**. | Call **GetSecondaryLanguages()** with an invalid **PackageList**. The return status should **EFI_NOT_FOUND**. |
| 5.18.2.5.5 | 0x68d1489e, 0x587b, 0x44e5, 0xb8, 0x72, 0x17, 0xc1, 0x1e, 0xc9, 0xd3, 0xf7 | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_INVALID_PARAMETER** with **PackageList** been **NULL**. | Call **GetSecondaryLanguages()** with **PackageList** being **NULL**. The return status should **EFI_INVALID_PARAMETER**. |
| 5.18.2.5.6 | 0xa25ea8dd, 0x5681, 0x4912, 0xb5, 0xda, 0xe3, 0x04, 0x36, 0x7c, 0x23, 0x89 | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_NOT_FOUND** with **FirstLanguage** is not present in the PackageList. | Call **GetSecondaryLanguages()** with **FirstLanguage** which is not in the specified **PackageList**. The return status should **EFI_NOT_FOUND**. |
| 5.18.2.5.7 | 0x6750c8c6, 0x54b5, 0x4a95, 0xa4, 0x15, 0x44, 0xbc, 0x64, 0xb1, 0x9f, 0x81 | **HII_STRING_PROTOCOL.GetLanguages - GetSecondaryLanguages()** returns **EFI_BUFFER_TOO_SMALL** with **SecondLanguagesSize** indicates the **SecondLanguages** is too small. | Call **GetSecondaryLanguages()** with **SecondLanguagesSize** which indicates the **SecondLanguages** buffer is small. The return status should **EFI_BUFFER_TOO_SMALL**. The **SecondLanguagesSize** is updated with the required size. |
| 5.18.2.5.8 | 0x302b21ca, 0xbc47, 0x4c26, 0xa0, 0x21, 0x24, 0x2d, 0xba, 0x57, 0x42, 0x65 | **HII_STRING_PROTOCOL.GetSecondaryLanguages - GetSecondaryLanguages()** returns **EFI_SUCCESS** with **SecondLanguagesSize** is large enough. | Call **GetSecondaryLanguages()** with valid parameters. The return status should be **EFI_SUCCESS**. |



## EFI_HII_IMAGE_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_IMAGE_PROTOCOL Section.

### NewImage()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.3.1.1 | 0x20eafa16, 0xc9cd, 0x41b3, 0x96, 0x81, 0x46, 0x7b, 0x7f, 0x17, 0x3d, 0x71 | **HII_IMAGE_PROTOCOL.NewImage - NewImage()** returns **EFI_INVALID_PARAMETER** with **ImageId** been **NULL**. | Call **NewImage()** with **ImageId** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.3.1.2 | 0x0227338d, 0xb459, 0x4209, 0xb1, 0xa0, 0x10, 0x3c, 0xe8, 0x3e, 0x71, 0xf5 | **HII_IMAGE_PROTOCOL.NewImage - NewImage()** returns **EFI_INVALID_PARAMETER** with **Image** been **NULL.** | Call **NewImage()** with **Image** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.3.1.3 | 0x4930f94e, 0x6bdb, 0x42aa, 0xaf, 0xde, 0x87, 0x55, 0x55, 0x2c, 0x77, 0x1d | **HII_IMAGE_PROTOCOL.NewImage - NewImage()** returns **EFI_NOT_FOUND** with **PackageList** been **NULL**. | Call **NewImage()** with **PackageList** being **NULL**, The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.1.4 | 0x170bc177, 0xa2f7, 0x46ba, 0xa8, 0xd6, 0x09, 0xe5, 0xa4, 0xb1, 0x81, 0x8f | **HII_IMAGE_PROTOCOL.NewImage - NewImage()** returns **EFI_SUCCESS** with valid parameters and result checked. | Call **NewImage()** with valid parameters, The return status should be **EFI_SUCCESS**. |


### GetImage()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.3.2.1 | 0x55488ca5, 0x2a0c, 0x4dcb, 0xbc, 0x7d, 0xca, 0xaf, 0x05, 0x2f, 0xac, 0x13 | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_NOT_FOUND** with **ImageId** been invalid. | Call **GetImage()** with an invalid **ImageId** which is not in the database. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.2.2 | 0xdde7e63e, 0xa889, 0x47ce, 0xad, 0xe1, 0x15, 0x0b, 0xb8, 0xa3, 0x8e, 0x10 | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_BUFFER_TOO_SMALL** with **ImageSize** is small. | Call **GetImage()** with **ImageSize** which indicates the **Image** buffer is small. The return status should **EFI_BUFFER_TOO_SMALL**. The **ImageSize** is updated with the required size. |
| 5.18.3.2.3 | 0xa1f286a0, 0x26da, 0x4919, 0xa3, 0xc4, 0x90, 0x5b, 0x18, 0x03, 0x6c, 0x36 | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_INVALID_PARAMETER** with **Image** been **NULL.** | Call **GetImage()** with **Image** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.3.2.4 | 0x17a11dcc, 0x8d3d, 0x40dc, 0xb0, 0x9c, 0x37, 0xfc, 0x8e, 0x72, 0x46, 0xab | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_INVALID_PARAMETER** with **ImageSize** been **NULL**. | Call **GetImage()** with **ImageSize** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.3.2.5 | 0x51363bef, 0x2eb6, 0x4eef, 0x86, 0xdf, 0x48, 0xf1, 0x87, 0x75, 0x6f, 0x9e | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_NOT_FOUND** with an invalid **PackageLis**t**.** | Call **GetImage()** with an invalid **PackageList**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.2.6 | 0x05fc7f10, 0xe1ef, 0x4fd0, 0x91, 0x3d, 0x86, 0x46, 0x53, 0x7e, 0x4c, 0xbd | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_NOT_FOUND** with **PackageLis**t been **NULL.** | Call **GetImage()** with **PackageList** being **NULL**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.2.7 | 0x14cd0647, 0x3fd7, 0x4831, 0x9e, 0xa5, 0x9b, 0x3d, 0xd7, 0xc8, 0xeb, 0xb7 | **HII_IMAGE_PROTOCOL.GetImage - GetImage()** returns **EFI_SUCCESS** with valid parameters and the result checked. | Call **GetImage()** with valid parameters, The return status should be **EFI_SUCCESS**. |


### SetImage()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.3.3.1 | 0x9af36ab7, 0x8bd2, 0x417b, 0xa5, 0x10, 0x1f, 0x22, 0x99, 0x13, 0x72, 0x64 | **HII_IMAGE_PROTOCOL.SetImage - SetImage()** returns **EFI_NOT_FOUND** with **ImageId** been invalid | Call **SetImage()** with an invalid **ImageId** which is not in the database. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.3.2 | 0x5d9b72d9, 0x01f4, 0x47cd, 0x96, 0xbb, 0xb1, 0xf2, 0xf2, 0x1f, 0xf7, 0x2a | **HII_IMAGE_PROTOCOL.SetImage - SetImage()** returns **EFI_INVALID_PARAMETER** with **Image** been **NULL**. | Call **SetImage()** with **Image** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.3.3.3 | 0xa411c5ef, 0x0eeb, 0x4a9a, 0x85, 0x9a, 0x4a, 0x64, 0x0d, 0xa6, 0x16, 0xf7 | **HII_IMAGE_PROTOCOL.SetImage - SetImage()** returns **EFI_NOT_FOUND** with an invalid **PackageList.** | Call **SetImage()** with an invalid **PackageList**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.3.4 | 0x870c9c4c, 0xe099, 0x4024, 0xac, 0x3a, 0x7b, 0x8c, 0x30, 0x98, 0x8c, 0x2e | **HII_IMAGE_PROTOCOL.SetImage - SetImage()** returns **EFI_NOT_FOUND** with **PackageList** been **NULL.** | Call **SetImage()** with **PackageList** being **NULL**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.3.3.5 | 0xc99ad1a4, 0x3f5b, 0x46dc, 0xb4, 0x85, 0xb2, 0x23, 0x9d, 0xef, 0xbc, 0x2c | **HII_IMAGE_PROTOCOL.SetImage - SetImage()** returns **EFI_SUCCESS** with valid parameters and result checked. | Call **SetImage()** with valid parameters, The return status should be **EFI_SUCCESS**. |


### DrawImage()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 27%" />
<col style="width: 39%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.3.4.1</td>
<td>0x4bb8ee94, 0x8a57, 0x470f, 0x9d, 0xd5, 0xef, 0x81, 0xea, 0xd9,
0xd6, 0xad</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Image</strong> been
<strong>NULL</strong>.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Image</strong> being
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.4.2</td>
<td><p>0xd9034d5d, 0xde07, 0x4458,</p>
<p>0x92, 0xb7, 0x4c, 0xd1, 0x50, 0x1c, 0xe8, 0x90</p></td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_FORCE_TRANS</strong> and <strong>Blt</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Flags</strong> being
<strong>EFI_HII_DRAW_FLAG_FORCE_TRANS and Blt being NULL</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.4.3</td>
<td>0x5c232904, 0x23f8, 0x4b0f, 0x9c, 0x85, 0xb7, 0xe8, 0xa5, 0xc9,
0x80, 0x05</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DIRECT_TO_SCREEN</strong> and no screen.</td>
<td>Call <strong>DrawIamge()</strong> with <strong>Flags</strong> being
<strong>EFI_HII_DIRECT_TO_SCREEN</strong> and use
<strong>EFI_GRAPHICS_OUTPUT_BLT_PIXEL</strong> structure in
<strong>EFI_IMAGE_OUTPUT</strong> structure. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.4.4</td>
<td><p>0xf9e86ff1, 0x611c, 0x41b8,</p>
<p>0xb0, 0x8d, 0x2a, 0xe2, 0x5e, 0x34, 0x2a, 0x1d</p></td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_CLIP</strong> and <strong>Blt</strong> points
to <strong>NULL</strong>.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Flags</strong> being
<strong>EFI_HII_DRAW_FLAG_CLIP</strong> and <strong>Blt</strong> being
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.4.5</td>
<td>0x11ae81e8, 0xfe20, 0x472d, 0x8c, 0xdb, 0x40, 0xb7, 0x56, 0x09,
0xd9, 0xdc</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_DEFAULT</strong>, <strong>Blt</strong> points
to <strong>NULL and Image-&gt;Flags is
EFI_IMAGE_TRANSPARENT.</strong></td>
<td>Call <strong>DrawImage()</strong> with <strong>Blt</strong> being
<strong>NULL</strong>, <strong>Flags</strong> being
<strong>EFI_HII_DRAW_FLAG_DEFAULT</strong> and
<strong>Image</strong>-&gt;<strong>Flags</strong> being
<strong>EFI_IMAGE_TRANSPARENT</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.4.6</td>
<td>0x6e409e86, 0x16d3, 0x4b31, 0x96, 0x71, 0xf9, 0x2c, 0xe6, 0x26,
0x1b, 0xcf</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameter.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Flags</strong> being
<strong>EFI_HII_DRAW_FLAG_FORCE_OPAQUE</strong>, <strong>Blt</strong>
being <strong>NULL</strong> and other valid parameters. The return
status should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.4.7</td>
<td>0xedbef6eb, 0xf68f, 0x4154, 0xb0, 0x12, 0xb9, 0xd7, 0x55, 0x3b,
0xa6, 0x0a</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameter.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Flags</strong> being
valid combination, <strong>Blt</strong> being not <strong>NULL</strong>
and other valid parameters. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


### DrawImageId()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 27%" />
<col style="width: 38%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.3.5.1</td>
<td>0xcb1936c7, 0x53c7, 0x4a65, 0xa5, 0x3d, 0x85, 0xc2, 0x35, 0x72,
0xff, 0x29</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_NOT_FOUND</strong> with an invalid
<strong>PackageList</strong>.</td>
<td>Call <strong>DrawImageId()</strong> with an invalid
<strong>PackageList</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.5.2</td>
<td>0xb1372c26, 0x3de4, 0x4a5c, 0x8a, 0x1f, 0x71, 0x4a, 0x7b, 0x07,
0x0e, 0x67</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_NOT_FOUND</strong> with <strong>PackageList</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>DrawImageId()</strong> with
<strong>PackageList</strong> being <strong>NULL</strong>. The return
status should be <strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.5.3</td>
<td>0x23a7fcfd, 0x4d0f, 0x4460, 0xb8, 0xcc, 0x7a, 0xfa, 0xf7, 0x4d,
0xe5, 0xaa</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_NOT_FOUND</strong> with invalid ImageId.</td>
<td>Call <strong>DrawImageId()</strong> with an invalid
<strong>ImageId</strong> which is not in the specified
<strong>PackageList</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.5.4</td>
<td><p>0x5433fcf6, 0x06f4, 0x45f3,</p>
<p>0x91, 0x23, 0x79, 0x5f, 0x49, 0x69, 0x77, 0x4d</p></td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_NOT_FOUND</strong> with invalid
<strong>PackageList.</strong></td>
<td>Call <strong>DrawImageId()</strong> with an invalid
<strong>PackageList</strong> which is not in the database. The return
status should be <strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.5.5</td>
<td><p>0x2df19349, 0xec8c, 0x42f7,</p>
<p>0x9f, 0x8e, 0x1d, 0x56, 0x13, 0x6c, 0x95, 0xbc</p></td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImage()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_FORCE_TRANS</strong> and <strong>Blt</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>DrawImageId()</strong> with Flags being
<strong>EFI_HII_DRAW_FLAG_FORCE_TRANS</strong> and <strong>Blt</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.5.6</td>
<td>0x059732f0, 0x431e, 0x4ad3, 0x92, 0xa0, 0x4b, 0xda, 0xaa, 0x8d,
0x98, 0x92</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImage - DrawImage()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DIRECT_TO_SCREEN</strong> and no screen.</td>
<td>Call <strong>DrawIamgeId()</strong> with <strong>Flags</strong>
being <strong>EFI_HII_DIRECT_TO_SCREEN</strong> and use
<strong>EFI_GRAPHICS_OUTPUT_BLT_PIXEL</strong> structure in
<strong>EFI_IMAGE_OUTPUT</strong> structure. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.5.7</td>
<td>0xd12320fa, 0x063e, 0x48e3, 0x85, 0xd5, 0x1c, 0x9b, 0x7c, 0x48,
0x71, 0x13</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_CLIP</strong> and <strong>Blt</strong> points
to <strong>NULL.</strong></td>
<td>Call <strong>DrawImageId()</strong> with <strong>Flags</strong>
being <strong>EFI_HII_DRAW_FLAG_CLIP</strong> and <strong>Blt</strong>
being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.5.8</td>
<td>0xb3e326cb, 0x67bc, 0x49a7, 0x8c, 0xb6, 0xc3, 0xec, 0x3b, 0x83,
0x20, 0x1e</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>EFI_HII_DRAW_FLAG_DEFAULT</strong>, <strong>Blt</strong> points
to <strong>NULL and Image-&gt;Flags is
EFI_IMAGE_TRANSPARENT.</strong></td>
<td>Call <strong>DrawImageId()</strong> with <strong>Blt</strong> being
<strong>NULL</strong>, <strong>Flags</strong> being
<strong>EFI_HII_DRAW_FLAG_DEFAULT</strong> and
<strong>Image</strong>-&gt;<strong>Flags</strong> being
<strong>EFI_IMAGE_TRANSPARENT</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.3.5.9</td>
<td>0xaeeb761e, 0x1b38, 0x4b06, 0x8d, 0x26, 0xf3, 0x6f, 0xde, 0xa4,
0x3d, 0x88</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameter.</td>
<td>Call <strong>DrawImageId()</strong> with <strong>Flags</strong>
being <strong>EFI_HII_DRAW_FLAG_FORCE_OPAQUE</strong>,
<strong>Blt</strong> being <strong>NULL</strong> and other valid
parameters. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.3.5.10</td>
<td>0x2b844dec, 0xc8cf, 0x442c, 0x89, 0xc0, 0x9f, 0x44, 0xe0, 0x96,
0x4b, 0xcb</td>
<td><strong>HII_IMAGE_PROTOCOL.DrawImageId - DrawImageId()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameter.</td>
<td>Call <strong>DrawImage()</strong> with <strong>Flags</strong> being
valid combination, <strong>Blt</strong> being not <strong>NULL</strong>
and other valid parameters. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


## EFI_HII_DATABASE_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_DATABASE_PROTOCOL Section.

### NewPackageList ()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.1.1 | 0x17364518, 0x35c4, 0x481a, 0x82, 0x45, 0xdd, 0x8b, 0x85, 0xbf, 0x01, 0x7c | **HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList()** returns **EFI_INVALID_PARAMETER** with **PackageList** being **NULL.** | Call **NewPackageList()** with **PackageList** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.1.2 | 0xd12127b3, 0x3a61, 0x498d, 0xbb, 0x8f, 0x9f, 0x9e, 0xb3, 0x9a, 0xfd, 0x95 | **HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList()** returns **EFI_INVALID_PARAMETER** with **Handle** being **NULL**. | Call **NewPackageList()** with **Handle** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.1.3 | 0x3ee6503d, 0x5fab, 0x4f51, 0x9a, 0xee, 0xc9, 0x0f, 0x9d, 0x73, 0xe5, 0xd7 | **HII_DATABASE_PROTOCOL.NewPackageList - NewPackageList()** returns **EFI_SUCCESS** with valid inputs | Call **NewPackageList()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### RemovePackageList ()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.2.1 | 0x244e5792, 0x471b, 0x456b, 0x8b, 0xfe, 0x1f, 0x68, 0xeb, 0x8f, 0xcd, 0xd0 | **HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList()** returns **EFI_NOT_FOUND** with **Handle** being **NULL**. | Call **RemovePackageList()** with **Handle** being **NULL**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.2.2 | 0x4f2588b4, 0xadb6, 0x48ba, 0xac, 0x53, 0x97, 0x3e, 0x05, 0x64, 0x5d, 0x4f | **HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList()** returns **EFI_NOT_FOUND** with **Handle** has already been removed once. | Call **RemovePackageList()** with **Handle** which has been removed. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.2.3 | 0x28c05503, 0x33ce, 0x41ae, 0x90, 0x2e, 0xbc, 0x34, 0xe0, 0xb8, 0x0e, 0x9d | **HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList()** returns **EFI_NOT_FOUND** with an invalid **Handle**. | Call **RemovePackageList()** with an invalid **Handle**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.2.4 | 0xb4a3a9ac, 0x0dfa, 0x4025, 0xa6, 0x36, 0xac, 0x53, 0x19, 0x7a, 0x5e, 0xd2 | **HII_DATABASE_PROTOCOL.RemovePackageList - RemovePackageList()** returns **EFI_SUCCESS** with valid inputs. | Part1: Call **RemovePackageList()** with valid parameters. The return status should be **EFI_SUCCESS**. |
| 5.18.4.2.5 | 0xad310e29, 0x2112, 0x485b, 0xa4, 0xdc, 0xc8, 0xec, 0xf8, 0x49, 0x7b, 0xc9 | **HII_DATABASE_PROTOCOL.RemovePackageList - ExportPackageLists()** returns **EFI_NOT_FOUND** when **RemovePackageList** work. | Part2: Call **ExportPackageList()** with **Handle** which has been removed. The return status should be **EFI_NOT_FOUND**. |


### UpdatePackageList ()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.3.1 | 0xb4bf4c19, 0x64cc, 0x4efe, 0xa7, 0x21, 0x3f, 0xc2, 0x07, 0x88, 0x51, 0xb4 | **HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList()** returns **EFI_NOT_FOUND** with **Handle** being **NULL.** | Call **UpdatePackageList()** with **Handle** being **NULL**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.3.2 | 0xcd591535, 0x7df7, 0x4f99, 0x9d, 0x13, 0x3b, 0x8e, 0x39, 0x85, 0x39, 0x6f | **HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList()** returns **EFI_NOT_FOUND** with **Handle** has already been removed before. | Call **UpdatePackageList()** with **Handle** which has been removed. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.3.3 | 0x2a2f8bf0, 0x0c27, 0x41f3, 0xae, 0x19, 0xb0, 0x66, 0x16, 0x92, 0x5c, 0x0b | **HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList()** returns **EFI_NOT_FOUND** with an invalid **handle**. | Call **UpdatePackageList()** with an invalid **Handle**. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.3.4 | 0xfcb45969, 0x37f8, 0x430e, 0x86, 0x99, 0x7f, 0x89, 0xde, 0x52, 0x6f, 0x94 | **HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList()** returns **EFI_INVALID_PARAMETER** with **PackageLis**t been **NULL**. | Call **UpdatePackageList()** with **PackageList** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.3.5 | 0xe1f18c0b, 0xfa2f, 0x488a, 0x80, 0x25, 0x77, 0x35, 0x49, 0x55, 0x36, 0xe0 | **HII_DATABASE_PROTOCOL.UpdatePackageList - UpdatePackageList()** returns **EFI_SUCCESS** with valid inputs | Call **UpdatePackageList()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### ListPackageLists()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.4.1 | 0x7b5c4246, 0xe6b3, 0x4eb0, 0xaf, 0xc4, 0x23, 0xb1, 0xbf, 0xfd, 0x46, 0x39 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_INVALID_PARAMETER** with **Handle** being **NULL**. | Call **ListPackageList()** with **Handle** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.4.2 | 0x9268a2d0, 0xc922, 0x42bc, 0xb0, 0x5d, 0x3d, 0x18, 0xab, 0xf2, 0xe9, 0x37 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_INVALID_PARAMETER** with **HandleBufferLength** being **NULL**. | Call **ListPackageList()** with **HandleBufferLength** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.4.3 | 0x7c577327, 0x562c, 0x4333, 0x9b, 0x81, 0x9b, 0xf6, 0xf2, 0x80, 0x83, 0xec | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_NOT_FOUND** when no matching **handles** were found. | Call **ListPackageList()** with no match **Handle** being found. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.4.4 | 0xf5771b8e, 0x6db5, 0x473d, 0xba, 0x32, 0x21, 0xfe, 0xf2, 0x7f, 0x05, 0xf2 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_BUFFER_TOO_SMALL** when the **HandleBufferLength** indicates the buffer is too small. | Part1: Call **ListPackageList()** with **HandleBufferLength** which indicates the **Handle** buffer is small. The return status should **EFI_BUFFER_TOO_SMALL**. |
| 5.18.4.4.5 | 0x08c276ef, 0x185c, 0x4eac, 0xbe, 0x84, 0x7d, 0xb0, 0x8c, 0x38, 0x5f, 0xe7 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_BUFFER_TOO_SMALL** when the **HandleBufferLength** indicates the buffer is too small and return the needed buffer length. | Part 2: The **HandleBufferLength** is updated with the required size. |
| 5.18.4.4.6 | 0x212bb7e2, 0xa998, 0x4ede, 0xba, 0x08, 0x8d, 0x8c, 0xda, 0x9d, 0xb7, 0xd4 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_INVALID_PARAMETER** with **PackageType** is not **Guid** and **PackageGui**d is not **NULL**. | Call **ListPackageList()** with no Guid **PackageType** and no **NULL** **PackageGuid**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.4.7 | 0x9b711922, 0x06d3, 0x4ba4, 0x98, 0x5b, 0x50, 0x72, 0x46, 0x94, 0x8b, 0xb2 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_INVALID_PARAMETER** with **PackageType** is **EFI_HII_DATABASE_TYPE_GUID** and **PackageGuid** is **NULL.** | Call **ListPackageList()** with Guid **PackageType** and **PackageGuid** being **NULL**. The return status should **EFI_INVALID_PARAMETER**. |
| 5.18.4.4.8 | 0x1dd024a0, 0xc53b, 0x439e, 0x86, 0x43, 0xc3, 0xe2, 0x82, 0x1f, 0x34, 0x75 | **HII_DATABASE_PROTOCOL.ListPackageLists - ListPackageLists()** returns **EFI_SUCCESS** with valid inputs and return length checked. | Call **ListPackageList()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### ExportPackageLists ()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 20%" />
<col style="width: 27%" />
<col style="width: 38%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.4.5.1</td>
<td>0xdc1afed1, 0x5be4, 0x4488, 0xaf, 0xeb, 0x75, 0x70, 0xb6, 0x3d,
0xea, 0xc4</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>BufferSize</strong>
being <strong>NULL</strong>.</td>
<td>Call <strong>ExportPackageList()</strong> with
<strong>BufferSize</strong> being <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.4.5.2</td>
<td>0xd25ed0fa, 0xe829, 0x4e68, 0xbb, 0xa3, 0xef, 0x82, 0x5a, 0xa0,
0xba, 0x85</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Buffer</strong>
being <strong>NULL</strong></td>
<td>Call <strong>ExportPackageList()</strong> with
<strong>Buffer</strong> being <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.4.5.3</td>
<td>0x0462bf1f, 0xce31, 0x4314, 0xbd, 0x34, 0x40, 0x4a, 0x05, 0x04,
0xd3, 0x0c</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with <strong>BufferSize</strong>
indicates the buffer is too small.</td>
<td>Part1: Call <strong>ExportPackageList()</strong> with
<strong>BufferSize</strong> which indicates the <strong>Buffer</strong>
is small. The return status should
<strong>EFI_BUFFER_TOO_SMALL</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.4.5.4</td>
<td>0xf03af69e, 0x3bba, 0x4092, 0xb0, 0x40, 0x75, 0x4b, 0x42, 0x6b,
0x2f, 0xd0</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with <strong>BufferSize</strong>
indicates the buffer is too small and return the needed
<strong>BufferSize</strong>.</td>
<td>Part2: The <strong>BufferSize</strong> is updated with the required
size.</td>
</tr>
<tr class="even">
<td>5.18.4.5.5</td>
<td>0x55ce12c1, 0x35eb, 0x4d8c, 0xbf, 0xd9, 0x9b, 0x0c, 0x52, 0x4d,
0xc0, 0x76</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns <strong>EFI_NOT_FOUND</strong>
with handle has been already removed once.</td>
<td>Call <strong>ExportPackageList()</strong> with
<strong>Handle</strong> which has been removed once. The return status
should be <strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.4.5.6</td>
<td>0x22a02d74, 0xc2a8, 0x439f, 0xbd, 0x4c, 0xf6, 0xb0, 0x1a, 0xbe,
0x03, 0xe4</td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns <strong>EFI_NOT_FOUND</strong>
with the invalid handle.</td>
<td>Call <strong>ExportPackageList()</strong> with an invalid
<strong>Handle</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.4.5.7</td>
<td><p>0xc9741024, 0x3073, 0x4827,</p>
<p>0x92, 0x23, 0x06, 0x33, 0x96, 0x0b, 0x8d, 0x6d</p></td>
<td><strong>HII_DATABASE_PROTOCOL.ExportPackageLists -
ExportPackageLists()</strong> returns <strong>EFI_SUCCESS</strong> with
valid inputs and result checked.</td>
<td>Call <strong>ExportPackageList()</strong> with valid parameters. The
return status should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


### RegisterPackageNotify()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.6.1 | 0x1665f366, 0x70af, 0x4348, 0xbb, 0xc8, 0xb1, 0xaf, 0x38, 0xe1, 0x2d, 0xfd | **HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify()** returns **EFI_INVALID_PARAMETER** with **NotifyHandle** been **NULL**. | Call **RegisterPackageNotify()** with **NotifyHandle** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.6.2 | 0x7541d67b, 0xe837, 0x46bf, 0x85, 0x7e, 0xbc, 0x22, 0xf2, 0xe1, 0x0d, 0x60 | **HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify()** returns **EFI_INVALID_PARAMETER** with **PackageType** is not **Guid** and **PackageGuid** not been **NULL**. | Call **RegisterPackageNotify()** with no Guid **PackageType** and no **NULL** **PackageGuid**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.6.3 | 0x625abf38, 0x2d02, 0x46b2, 0xae, 0xa9, 0xcc, 0x5b, 0x0c, 0x83, 0xf1, 0x69 | **HII_DATABASE_PROTOCOL.RegisterPackageNotify - RegisterPackageNotify()** returns **EFI_INVALID_PARAMETER** with **PackageType** is **EFI_HII_PACKAGE_TYPE_GUID** and **PackageGuid** been **NULL.** | Call **RegisterPackageNotify()** with Guid **PackageType** and **NULL** **PackageGuid**. The return status should be **EFI_INVALID_PARAMETER**. |


### UnregisterPackageNotify()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.7.1 | 0xef67f1ff, 0x9b53, 0x40ac, 0x8e, 0xec, 0xca, 0x5c, 0x59, 0xfd, 0xbd, 0x0d | **HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify()** returns **EFI_NOT_FOUND** with the **NotifyHandle** has been removed already. | Call **UnRegisterPackageNotify()** with **NotifyHandle** which has been removed once. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.7.2 | 0xc5266e09, 0xe5e8, 0x4c85, 0xb3, 0x0a, 0xc9, 0x83, 0x04, 0x4f, 0x23, 0xfc | **HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify()** returns **EFI_NOT_FOUND** with an invalid **NotifyHandle**. | Call **UnRegisterPackageNotify()** with **NotifyHandle** which can’t be found in the database. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.7.3 | 0x51c64bb1, 0x3266, 0x4ccd, 0x82, 0xde, 0xed, 0x6b, 0xa7, 0x68, 0x35, 0xe5 | **HII_DATABASE_PROTOCOL.UnregisterPackageNotify - UnregisterPackageNotify()** returns **EFI_NOT_FOUND** with **NotifyHandle** been **NULL**. | Call **UnRegisterPackageNotify()** with **NotifyHandle** being **NULL**. The return status should be **EFI_NOT_FOUND**. |


### FindKeyboardLayouts()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.8.1 | 0xa61bf4b2, 0xb1e0, 0x4e62, 0x95, 0x2d, 0xa0, 0x68, 0x98, 0x48, 0x06, 0xb2 | **HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts()** returns **EFI_INVALID_PARAMETER** with **KeyGuidBufferLengt**h been **NULL**. | Call **FindKeyboardLayouts()** with **KeyGuidBufferLength** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.8.2 | 0x1ea6e881, 0x6f47, 0x4fdc, 0x8b, 0x8c, 0xba, 0x33, 0x9a, 0x13, 0xbe, 0xc0 | **HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts()** returns **EFI_INVALID_PARAMETER** with **KeyGuidBuffer** been **NULL.** | Call **FindKeyboardLayouts()** with **KeyGuidBuffer** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.8.3 | 0xc3bacca3, 0x901a, 0x49ad, 0xa9, 0x86, 0x41, 0x62, 0xff, 0xb3, 0xa1, 0x8f | **HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts()** returns **EFI_BUFFER_TOO_SMALL** with **KeyGuidBufferLength** indicates the buffer is too small. | Call **FindKeyboardLayouts()** with **KeyGuidBufferLength** which indicates **KeyGuidBuffer** is small. The return status should be **EFI_BUFFER_TOO_SMALL**. The **KeyGuidBufferLength** should be updated with required length. |
| 5.18.4.8.4 | 0x1dc41f45, 0x9e3a, 0x41e2, 0x8f, 0x99, 0x8d, 0x4d, 0x39, 0x32, 0x12, 0x85 | **HII_DATABASE_PROTOCOL.FindKeyboardLayouts - FindKeyboardLayouts()** returns **EFI_SUCCESS** with valid inputs. | Call **FindKeyboardLayouts()** with valid parameters. The return status should be **EFI_SUCCESS**. The **KeyGuidBufferLength** should be updated with actual length. |


### GetKeyboardLayout()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.9.1 | 0xbc4b4ea1, 0x069c, 0x459c, 0x8c, 0x22, 0x68, 0x19, 0x01, 0x71, 0x78, 0x48 | **HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout()** returns **EFI_INVALID_PARAMETER** with **KeyboardLayoutLength** been **NULL.** | Call **GetKeyboardLayout()** with **KeyboardLayoutLength** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.9.2 | 0xe2aeca1e, 0x5c50, 0x4ee7, 0x8f, 0x69, 0x46, 0xa7, 0xb9, 0x01, 0x3e, 0x0d | **HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout()** returns **EFI_INVALID_PARAMETER** with **KeyboardLayout** bee**n** **NULL.** | Call **GetKeyboardLayout()** with **KeyboardLayout** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.9.3 | 0x0d41d349, 0xe5f4, 0x43d5, 0x85, 0x0e, 0xfe, 0x4f, 0x08, 0x5a, 0xbf, 0xb2 | **HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout()** returns **EFI_BUFFER_TOO_SMALL** with **KeyboardLayoutLength** not enough. | Call **GetKeyboardLayout()** with **KeyboardLayoutLength** which indicates **KeyboardLayout** is small. The return status should be **EFI_BUFFER_TOO_SMALL**. The **KeyboardLayoutLength** should be updated with required length. |
| 5.18.4.9.4 | 0xc2732202, 0x48ca, 0x49f8, 0xbb, 0x18, 0xd3, 0x6c, 0xe1, 0xb4, 0x83, 0xfa | **HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout()** returns **EFI_NOT_FOUND** with the requested keyboard layout not found. | Call **GetKeyboardLayout()** with a Guid which can’t be found in the database. The return status should be **EFI_NOT_FOUND**. |
| 5.18.4.9.5 | 0x4ffc59ee, 0xefb8, 0x4533, 0x81, 0x4f, 0x85, 0xed, 0x90, 0x93, 0x44, 0xc7 | **HII_DATABASE_PROTOCOL.GetKeyboardLayout - GetKeyboardLayout()** returns **EFI_SUCCESS** with valid inputs. | Call **GetKeyboardLayout()** with valid parameters. The return status should be **EFI_SUCCESS**. |


### SetKeyboardLayout()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 27%" />
<col style="width: 39%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.4.10.1</td>
<td>0xad8c6cdc, 0xc749, 0x42e6, 0x88, 0xf7, 0x73, 0x44, 0x7c, 0x38,
0x9e, 0x4d</td>
<td><strong>HII_DATABASE_PROTOCOL.SetKeyboardLayout -
SetKeyboardLayout()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>KeyGuid</strong> set
to be <strong>NULL</strong>.</td>
<td>Call <strong>SetKeyboardLayout()</strong> with
<strong>KeyGuid</strong> being <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.4.10.2</td>
<td>0x07018fe1, 0xdde0, 0x449b, 0xa5, 0xe2, 0xb1, 0x7a, 0xb5, 0x68,
0x7c, 0x97</td>
<td><strong>HII_DATABASE_PROTOCOL.SetKeyboardLayout -
SetKeyboardLayout()</strong> returns <strong>EFI_NOT_FOUND</strong> with
the referenced keyboard layout not found.</td>
<td>Call <strong>SetKeyboardLayout()</strong> with
<strong>KeyGuid</strong> which can’t be found in database. The return
status should be <strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.4.10.3</td>
<td><p>0xe7a3dffa, 0x4cca, 0x4402,</p>
<p>0x8f, 0xf1, 0xe3, 0xf3, 0x16, 0xf5, 0x45, 0x1f</p></td>
<td><strong>HII_DATABASE_PROTOCOL.SetKeyboardLayout -
SetKeyboardLayout()</strong> returns <strong>EFI_SUCCESS</strong> with
valid inputs.</td>
<td>Call <strong>SetKeyboardLayout()</strong> with valid parameters. The
return status should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


### GetPackageListHandle()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.4.11.1 | 0x373b128d, 0x2216, 0x415b, 0xbb, 0xb1, 0x99, 0x0e, 0xe3, 0x79, 0xf2, 0x85 | **HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle()** returns **EFI_INVALID_PARAMETER** with **DriverHandle** been **NULL.** | Call **GetPackageListHandle ()** with **DriverHandle** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.11.2 | 0xb50cffb8, 0x7b74, 0x4b93, 0xb4, 0x87, 0xb3, 0x39, 0xf4, 0x7e, 0xa6, 0x25 | **HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle ()** returns **EFI_INVALID_PARAMETER** with a **PackageListHandle** which has been removed. | Call **GetPackageListHandle ()** with a **PackageListHandle** which has been removed. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.11.3 | 0x27a38687, 0x398a, 0x4d65, 0xab, 0x7b, 0x4d, 0xf2, 0xd1, 0x1f, 0x21, 0xa0 | **HII_DATABASE_PROTOCOL.GetPackageListHandle - GetPackageListHandle()** returns **EFI_INVALID_PARAMETER** with an invalid **PackageListHandle**. | Call **GetPackageListHandle ()**with an invalid **PackageListHandle**. The return status should be **EFI_INVALID_PARAMETER** . |
| 5.18.4.11.4 | 0x2bc2dae8, 0x2692, 0x487a, 0x94, 0x9d, 0xa7, 0x45, 0x08, 0x82, 0x65, 0x11 | **HII_DATABASE_PROTOCOL. GetPackageListHandle - GetPackageListHandle()** returns **EFI_INVALID_PARAMETER** with **PackageListHandle** being **NULL** . | Call **GetPackageListHandle ()**with **PackageListHandle** being **NULL**. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.4.11.5 | 0xa81329db, 0xcc91, 0x491c, 0xb1, 0x2a, 0x44, 0x0d, 0xf7, 0xed, 0x77, 0xc6 | **HII_DATABASE_PROTOCOL. GetPackageListHandle - GetPackageListHandle()** returns **EFI_SUCCESS** with valid inputs. | Call **GetPackageListHandle ()** with valid parameters. The return status should be **EFI_SUCCESS**. |


## EFI_HII_CONFIG_ROUTING_PROTOCOL Test

**Reference Document:**

*UEFI Specification,* EFI_HII_CONFIG_ROUTING_PROTOCOL Section.

### ExtractConfig()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 18%" />
<col style="width: 26%" />
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
<td>5.18.5.1.1</td>
<td>0x04697ed6, 0xcb4e, 0x4e02, 0xbb, 0x8e, 0x9b, 0x76, 0x0b, 0x90,
0xe2, 0xcd</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <strong>Request</strong> been <strong>NULL</strong>.</td>
<td>Call <strong>ExtractConfig()</strong> with valid parameters except
<strong>Request</strong> being <strong>NULL</strong>, The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.5.1.2</td>
<td>0x4a1e3525, 0x5247, 0x40dc, 0x93, 0xf7, 0x81, 0x30, 0x6a, 0xce,
0x20, 0xb5</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <strong>Progress</strong> been <strong>NULL.</strong></td>
<td>Call <strong>ExtractConfig()</strong> with valid parameters except
<strong>Progress</strong> being <strong>NULL</strong>, The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.5.1.3</td>
<td>0x05b967d0, 0xe19d, 0x46d8, 0x87, 0xd8, 0x7d, 0x29, 0x65, 0x53,
0x61, 0xc7</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with <strong>Results</strong> been <strong>NULL.</strong></td>
<td>Call <strong>ExtractConfig()</strong> with valid parameters except
<strong>Results</strong> being <strong>NULL</strong>, The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.5.1.4</td>
<td>0xee200b58, 0x3714, 0x4cb6, 0x91, 0xc6, 0x31, 0xbe, 0xbd, 0xf4,
0x64, 0x96</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_NOT_FOUND</strong> if
Routing data doesn’t match any known driver<strong>.</strong></td>
<td>Call <strong>ExtractConfig()</strong> with an invalid
<strong>Request</strong>. The ConfigHdr of <strong>Request</strong>
can’t be found in current system. The return status should be
<strong>EFI_NOT_FOUND</strong>. <strong>Progress</strong> should be set
to the “G” in the “GUID” of the routing header that doesn’t match.</td>
</tr>
<tr class="even">
<td>5.18.5.1.5</td>
<td>0xa18aebb6, 0x140f, 0x454f, 0x8f, 0xe5, 0x34, 0xdd, 0x38, 0xd8,
0xb0, 0xf0</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
if name in <strong>Request</strong> can’t match any known driver.</td>
<td>Call <strong>ExtractConfig()</strong> with an invalid
<strong>Request</strong>. The name in <strong>Request</strong> can’t be
found in current system. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.5.1.6</td>
<td>0x67adfcdd, 0xda46, 0x4eb8, 0x82, 0x9d, 0xa4, 0x92, 0x8c, 0x10,
0xba, 0x68</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameter and <strong>Progress</strong> points to the
<strong>Request</strong>’s <strong>NULL</strong> terminator.</td>
<td>Call <strong>ExtractConfig()</strong> with valid parameters. The
return status should be <strong>EFI_SUCCESS</strong> and
<strong>Progress</strong> points to the <strong>Request</strong>’s
<strong>NULL</strong> terminator.</td>
</tr>
<tr class="even">
<td>5.18.5.1.7</td>
<td>0xf91ef5f3, 0xe0c6, 0x4aca, 0xa0, 0xd0, 0x5, 0xf9, 0xb1, 0x6a, 0x13,
0xbd</td>
<td><strong>HII_CONFIG_ROUTING_PROT OCOL.ExtractConfig -
ExtractConfig()</strong> returns <strong>EFI_SUCCESS</strong> &amp;
Check if Results is in <strong>&lt;MultiConfigAltResp&gt;</strong>
format</td>
<td><p>1.Call <strong>ExtractConfig()</strong> with valid
parameters.</p>
<p>2.Check if Results is in <strong>&lt;MultiConfigAltResp&gt;</strong>
format. The return status should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
</tbody>
</table>


### ExportConfig()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.5.2.1 | 0x81f9658b, 0xbae2, 0x4e08, 0x87, 0xe3, 0x75, 0xe4, 0xe1, 0x47, 0x13, 0xba | **HII_CONFIG_ROUTING_PROTOCOL.ExportConfig - ExportConfig()** returns **EFI_INVALID_PARAMETER** with **Request** been **NULL**. | Call **ExportConfig()** with **Request** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.5.2.2 | 0xe23425ee, 0xaa38, 0x4074, 0xa1, 0xaa, 0xad, 0x5d, 0x98, 0x5a, 0x34, 0xe4 | **HII_CONFIG_ROUTING_PROTOCOL.ExportConfig - ExportConfig ()** returns **EFI_SUCCESS** with valid parameter. | Call **ExportConfig()** with valid parameter, The return status should be **EFI_SUCCESS**. |


### RouteConfig()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.5.3.1 | 0x3a5c09d6, 0x0532, 0x4b4d, 0x87, 0xc8, 0x5e, 0x20, 0x33, 0x78, 0xbc, 0x3f | **HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig()** returns **EFI_INVALID_PARAMETER** with **Configuration** been **NULL**. | Call **RouteConfig()** with **Configuration** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.5.3.2 | 0x18cdf3f8, 0xf9e6, 0x4128, 0xa4, 0xa6, 0x88, 0xea, 0x88, 0x5d, 0x59, 0x7c | **HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig()** returns **EFI_NOT_FOUND** if Routing data was not found. | Call **RouteConfig()** with an invalid **Configuration**. The ConfigHdr of **Configuration** can’t be found in current system. The return status should be **EFI_NOT_FOUND**. |
| 5.18.5.3.3 | 0x20833aeb, 0x9ff1, 0x4315, 0xb1, 0x0f, 0x31, 0x7c, 0x7b, 0x92, 0x45, 0x21 | **HII_CONFIG_ROUTING_PROTOCOL.RouteConfig - RouteConfig ()** returns **EFI_SUCCESS** with valid parameter and **Progress** points to the **Configuration**’s **NULL** terminator. | Call **RouteConfig()** with valid parameters. The return status should be **EFI_SUCCESS** and **Progress** points to the **Configuration**’s **NULL** terminator. |


### BlockToConfig()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.5.4.1 | 0xb1dfee09, 0x73e5, 0x4659, 0x9a, 0xc6, 0x59, 0x46, 0xc1, 0xa1, 0x53, 0xcb | **HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig()** returns **EFI_INVALID_PARAMETER** with **ConfigRequest** been **NULL**. | Call **BlockToConfig()** with valid parameters except **ConfigRequest** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.5.4.2 | 0x544bf56b, 0x3bdc, 0x46d5, 0x88, 0x4f, 0x19, 0xde, 0x76, 0x19, 0xef, 0xd3 | **HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig()** returns **EFI_INVALID_PARAMETER** with **Block** been **NULL.** | Call **BlockToConfig()** with valid parameters except **Block** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.5.4.3 | 0xee6f8fd8, 0x951d, 0x4976, 0x86, 0xf0, 0xae, 0x7f, 0x5c, 0x69, 0x5b, 0x40 | **HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig()** returns **EFI_INVALID_PARAMETER** with \<ConfigElement\> in **ConfigRequest** being a \<NvConfig\>. | Call **BlockToConfig()** with valid parameters except \<ConfigElement\> in **ConfigRequest** being a \<NvConfig\>, The return status should be **EFI_INVALID_PARAMETER** and **Progress** points to ‘&’ of the first non-\<BlockName\>. |
| 5.18.5.4.4 | 0xd38890ec, 0xd43e, 0x4e28, 0xab, 0x47, 0xef, 0x67, 0xeb, 0x2d, 0x3d, 0x92 | **HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig()** returns **EFI_DEVICE_ERROR** if **Block** is not large enough**.** | Call **BlockToConfig()** with with valid parameters except **Block** is not large enough. The return status should be **EFI_DEVICE_ERROR**. |
| 5.18.5.4.5 | 0x8b1b960c, 0xda67, 0x423c, 0x85, 0x31, 0x76, 0x28, 0x0d, 0xb8, 0x2a, 0xc1 | **HII_CONFIG_ROUTING_PROTOCOL.BlockToConfig - BlockToConfig()** returns **EFI_SUCCESS** with valid parameter and **Progress** points to the **ConfigRequest**’s **NULL** terminator**.** | Call **BlockToConfig()** with valid parameters. The return status should be **EFI_SUCCESS** and **Progress** points to the **ConfigRequest**’s **NULL** terminator. |


### ConfigToBlock ()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.5.5.1 | 0x76ab8420, 0x7c61, 0x4ebc, 0x8b, 0x5b, 0x62, 0xa3, 0x35, 0x64, 0x6f, 0x8f | **HII_CONFIG_ROUTING_PROTOCOL. ConfigToBlock - ConfigToBlock()** returns **EFI_INVALID_PARAMETER** with **ConfigResp** been **NULL**. | Call **ConfigToBlock()** with valid parameters except **ConfigResp** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.5.5.2 | 0xcc284047, 0x45d6, 0x4fec, 0x88, 0x50, 0x70, 0x3f, 0x45, 0x22, 0x01, 0xdc | **HII_CONFIG_ROUTING_PROTOCOL. ConfigToBlock - ConfigToBlock()** returns **EFI_INVALID_PARAMETER** with **Block** been **NULL. Progress** should point to the first character of **ConfigResp**. | Call **ConfigToBlock()** with valid parameters except **Block** being **NULL**, The return status should be **EFI_INVALID_PARAMETER** and **Progress** should point to the first character of **ConfigResp**. |
| 5.18.5.5.3 | 0x2d30da76, 0x9ec7, 0x480e, 0xb9, 0xe9, 0x6d, 0x50, 0x0d, 0x89, 0x21, 0xad | **HII_CONFIG_ROUTING_PROTOCOL. ConfigToBlock - ConfigToBlock()** returns **EFI_INVALID_PARAMETER** with \<RequestElement\> in **ConfigResp** being a \<Lable\>. | Call **ConfigToBlock()** with valid parameters except \< RequestElement \> in **ConfigResp** being a \<Lable\>. The return status should be **EFI_INVALID_PARAMETER** and **Progress** points to ‘&’ of the first non-\<BlockName\>. |
| 5.18.5.5.4 | 0xa5b33ea4, 0x767b, 0x489a, 0xb3, 0x7b, 0xf9, 0xef, 0xfd, 0x62, 0xbc, 0x7b | **HII_CONFIG_ROUTING_PROTOCOL. ConfigToBlock - ConfigToBlock()** returns **EFI_DEVICE_ERROR** if **Block** is not large enough**.** | Call **ConfigToBlock()** with valid parameters except **Block** is not large enough. The return status should be **EFI_DEVICE_ERROR**. |
| 5.18.5.5.5 | 0x59b759ff, 0x6c84, 0x407a, 0x9e, 0x24, 0x71, 0xe0, 0x65, 0x2d, 0xe3, 0x30 | **HII_CONFIG_ROUTING_PROTOCOL. ConfigToBlock - ConfigToBlock()** returns **EFI_SUCCESS** with valid parameter and **Progress** points to the **ConfigResp**’s **NULL** terminator**.** | Call **ConfigToBlock()** with valid parameters. The return status should be **EFI_SUCCESS** and **Progress** points to the **ConfigResp**’s **NULL** terminator. |


### GetAltCfg ()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 18%" />
<col style="width: 26%" />
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
<td>5.18.5.6.1</td>
<td>0x1ff2326a, 0x8e88, 0x45db, 0x94, 0x81, 0x02, 0x83, 0x80, 0x20,
0xad, 0x02</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>ConfigResp</strong> been <strong>NULL</strong>.</td>
<td>Call <strong>GetAltCfg()</strong> with valid parameters except
<strong>ConfigResp</strong> being <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.5.6.2</td>
<td>0xb9b88d34, 0x7479, 0x4807, 0xa4, 0xbf, 0x90, 0x35, 0x87, 0x0a,
0x3c, 0x1a</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>AltCfgResp</strong> been <strong>NULL</strong>.</td>
<td>Call <strong>GetAltCfg()</strong> with valid parameters except
<strong>AltCfgResp</strong> being <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.18.5.6.3</td>
<td><p>0xfe1e4232, 0x8819,</p>
<p>0x4f52, 0xac, 0xaa, 0xb2, 0x02, 0x72, 0x86, 0xc8, 0xe4</p></td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_SUCCESS</strong> with
<strong>NULL Guid</strong>, <strong>Name</strong>,
<strong>DevicePath</strong>, except a valid
<strong>AltCfgId</strong>.</td>
<td>Call <strong>GetAltCfg()</strong> with <strong>NULL Guid</strong>,
<strong>Name</strong>, <strong>DevicePath</strong>, except a valid
<strong>AltCfgId</strong>. The return status should be
<strong>EFI_SUCCESS</strong> and <strong>AltCfgResp</strong> should
points to retrieved data.</td>
</tr>
<tr class="odd">
<td>5.18.5.6.4</td>
<td>0xdf88e78e, 0x8f4d, 0x4027, 0xbb, 0xcd, 0xae, 0x10, 0x68, 0x58,
0xb6, 0x03</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong>returns <strong>EFI_SUCCESS</strong> with
<strong>NULL Name</strong>, <strong>DevicePath</strong>, except a valid
<strong>Guid</strong>, <strong>AltCfgId</strong>.</td>
<td>Call <strong>GetAltCfg()</strong>with <strong>NULL Name</strong>,
<strong>DevicePath</strong>, except a valid <strong>Guid</strong>,
<strong>AltCfgId</strong>. The return status should be
<strong>EFI_SUCCESS</strong> and <strong>AltCfgResp</strong> should
points to retrieved data.</td>
</tr>
<tr class="even">
<td>5.18.5.6.5</td>
<td>0x2b56a57a, 0xd906, 0x416c, 0x89, 0x76, 0x43, 0x5f, 0xc7, 0x1c,
0xb7, 0x73</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_SUCCESS</strong> with
<strong>NULL Guid</strong>, <strong>DevicePath</strong>, except a valid
<strong>Name</strong>, <strong>AltCfgId</strong>.</td>
<td>Call <strong>GetAltCfg()</strong> with <strong>NULL Guid</strong>,
<strong>DevicePath</strong>, except a valid <strong>Name</strong>,
<strong>AltCfgId</strong>. The return status should be
<strong>EFI_SUCCESS</strong> and <strong>AltCfgResp</strong> should
points to retrieved data.</td>
</tr>
<tr class="odd">
<td>5.18.5.6.6</td>
<td>0x17c575b3, 0x051f, 0x41eb, 0x89, 0xd1, 0x79, 0xb5, 0x8b, 0x0c,
0x92, 0x3c</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_SUCCESS</strong> with
<strong>NULL DevicePath</strong>, except a valid <strong>Guid</strong>,
<strong>Name</strong>, <strong>AltCfgId</strong>.</td>
<td>Call <strong>GetAltCfg()</strong> with <strong>NULL
DevicePath</strong>, except a valid
<strong>Guid</strong>,<strong>Name</strong>, <strong>AltCfgId</strong>.
The return status should be <strong>EFI_SUCCESS</strong> and
<strong>AltCfgResp</strong> should points to retrieved data.</td>
</tr>
<tr class="even">
<td>5.18.5.6.7</td>
<td>0xb948d2f8, 0x5c45, 0x4b10, 0x97, 0xb4, 0x95, 0x96, 0x97, 0x98,
0xe5, 0x8b</td>
<td><strong>HII_CONFIG_ROUTING_PROTOCOL. GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_SUCCESS</strong> returns
<strong>EFI_SUCCESS</strong> with <strong>NULL DevicePath</strong>,
<strong>AltCfgId</strong>, except a valid <strong>Guid</strong>,
<strong>Name</strong>.</td>
<td>Call <strong>GetAltCfg()</strong>with <strong>NULL
DevicePath</strong>, <strong>AltCfgId</strong>, except a valid
<strong>Guid</strong>, <strong>Name</strong>. The return status should
be <strong>EFI_SUCCESS</strong> and <strong>AltCfgResp</strong> should
points to retrieved data.</td>
</tr>
<tr class="odd">
<td>5.18.5.6.8</td>
<td>0xf732d246, 0x9fa5, 0x4ed3, 0x88, 0x95, 0x28, 0x63, 0xba, 0xf4,
0x68, 0x5d</td>
<td><strong>HII_CONFIG_ROUTING_PROT OCOL.GetAltCfg -
GetAltCfg()</strong> returns <strong>EFI_SUCCESS</strong> with valid
Name</td>
<td><p>1.Call <strong>GetAltCfg()</strong> with NULL GUID
<strong>DevicePath</strong>, <strong>AltCfgId</strong>, except a valid
Name.</p>
<p>2. The return status should be <strong>EFI_SUCCESS</strong> and
<strong>AltCfgResp</strong> should points to right data.</p></td>
</tr>
</tbody>
</table>


## EFI_HII_CONFIG_ACCESS_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_CONFIG_ACCESS_PROTOCOL Section.

### ExtractConfig()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.6.1.1 | 0xa7173eb5, 0xf76a, 0x4ea1, 0x95, 0x0d, 0x14, 0x91, 0x1e, 0x49, 0x86, 0xc1 | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_INVALID_PARAMETER** with **Request** been \<MultiConfigRequest\> format. | Call **ExtractConfig()** with valid parameters except with **Request** being \<MultiConfigRequest\> format., The return status should be **EFI_INVALID_PARAMETER**. And Progress should point to the most recent ‘&’ before the error or beginning of the string. |
| 5.18.6.1.2 | 0xfa5973e2, 0x0d05, 0x44c2, 0xaf, 0x2d, 0x1b, 0x68, 0x33, 0x42, 0x6d, 0x76 | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_INVALID_PARAMETER** with **Progress** been **NULL.** | Call **ExtractConfig()** with valid parameters except **Progress** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.6.1.3 | 0x6f6d1dd, 0x49b8, 0x488a, 0xa7, 0x75, 0xde, 0xbc, 0xc7, 0x60, 0xfd, 0x28 | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_INVALID_PARAMETER** with **Results** been **NULL.** | Call **ExtractConfig()** with valid parameters except **Results** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.6.1.4 | 0x28652613, 0x6bf4, 0x4f42, 0xab, 0xe2, 0x84, 0x4f, 0x2f, 0x77, 0xec, 0x2f | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_NOT_FOUND** if Routing data doesn’t match any known driver or **EFI_INVALID_PARAMETER** if there is an unknown name in **Request.** | Call **ExtractConfig()** with an invalid **Request**. The ConfigHdr of **Request** can’t be found in current system. The return status should be **EFI_NOT_FOUND**. **Progress** should point to the error reason. If an unknown name in the **Request**, the return status should be **EFI_INVALID_PARAMETER** and **Progress** should point to the ‘&’ before the name in question. |
| 5.18.6.1.5 | 0x24dcf8bf, 0xbfbf, 0x4588, 0xba, 0x0f, 0x77, 0x1e, 0x24, 0x4e, 0x3e, 0x08 | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_SUCCESS** with valid parameters and and **Progress** points to the **Request**’s **NULL** terminator. | Call **ExtractConfig()** with valid parameters. The return status should be **EFI_SUCCESS** and the **Progress** should point to **Request**’s **NULL** terminator. |
| 5.18.6.1.6 | 0x961a5268, 0x1998, 0x4a7e, 0x9d, 0x9d, 0xce, 0xdc, 0x67, 0xfb, 0xcc, 0x77 | **HII_CONFIG_ACCESS_PROTOCOL.ExtractConfig - ExtractConfig()** returns **EFI_SUCCESS** with valid parameter except **Request** been **NULL.** | Call **ExtractConfig()** with valid parameters except **Request** been **NULL**. The return status should be **EFI_SUCCESS**. |
| 5.18.6.1.7 | 0xab163674, 0x6c27, 0x4169, 0xa6, 0xa9, 0xe1, 0x9c, 0x88, 0x14, 0x94, 0x96 | **HII_CONFIG_ACCESS_PROT OCOL.ExtractConfig - ExtractConfig()** returns **EFI_SUCCESS**. Check if Results is in **\<MultiConfigAltResp\>** format | Call **ExtractConfig()** with valid parameters. The return status should be **EFI_SUCCESS** and Check if Results is in **\<MultiConfigAltResp\>** format. |



### RouteConfig()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.6.2.1 | 0xebba197a, 0x467f, 0x4736, 0x92, 0xf2, 0x11, 0xb1, 0x91, 0x2e, 0xe9, 0x90 | **HII_CONFIG_ACCESS_PROTOCOL.RouteConfig - RouteConfig()** returns **EFI_INVALID_PARAMETER** with **Configuration** been **NULL**. | Call **RouteConfig()** with valid parameters except with **Configuration** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.6.2.2 | 0x341fe3e0, 0xf688, 0x45f2, 0x91, 0x56, 0xc7, 0xae, 0x9f, 0x2c, 0xcb, 0xb0 | **HII_CONFIG_ACCESS_PROTOCOL. RouteConfig - RouteConfig()** returns **EFI_INVALID_PARAMETER** with **Progress** been **NULL.** | Call **RouteConfig()** with valid parameters except **Progress** being **NULL**, The return status should be **EFI_INVALID_PARAMETER**. |
| 5.18.6.2.3 | 0x1f99ebc8, 0x0253, 0x455f, 0x88, 0xac, 0x9e, 0x2b, 0xa6, 0xdc, 0xd7, 0x29 | **HII_CONFIG_ACCESS_PROTOCOL. RouteConfig - RouteConfig()** returns **EFI_NOT_FOUND** if no target was found with the routing data**.** | Call **RouteConfig()** with no found target for the routing data. The return status should be **EFI_NOT_FOUND**. |
| 5.18.6.2.4 | 0x603e52f0, 0x2ce3, 0x4e7a, 0xa7, 0x2e, 0xdf, 0x8c, 0xa3, 0xfd, 0xb2, 0x0d | **HII_CONFIG_ACCESS_PROTOCOL. RouteConfig - RouteConfig()**returns **EFI_SUCCESS** with valid parameters and and **Progress** points to the **Configuration**’s **NULL** terminator**.** | Call **RouteConfig()**with valid parameters. The return status should be **EFI_SUCCESS** and the **Progress** should point to **Configuration**’s **NULL** terminator. |


## EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL Section.

### SetData()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 24%" />
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
<td>5.18.7.1.1</td>
<td>0xf046a19c, 0xffc1, 0x4fd9, 0x9d, 0x73, 0x92, 0x4f, 0x8c, 0x43,
0xcf, 0xfb</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData() -
SetData()</strong></p>
<p><strong>returns EFI_NOT_FOUND when an element of the KeywordString
was not found. Progress points to the most recent '&amp;' before the
first failing string element and ProgressErr should be
KEYWORD_HANDLER_KEYWORD_NOT_FOUND.</strong></p></td>
<td><p>1. Call <strong>SetData() when an element of the KeywordString
was not found, the return status should be EFI_NOT_FOUND. Progress
points to the most recent '&amp;' before the first failing string
element and</strong></p>
<p><strong>ProgressErr should be
KEYWORD_HANDLER_KEYWORD_NOT_FOUND.</strong></p></td>
</tr>
<tr class="odd">
<td>5.18.7.1.2</td>
<td>0x553c956c, 0x78c1, 0x44d4, 0x81, 0x8e, 0x98, 0xdf, 0xd2, 0x25, 0x8,
0xe5</td>
<td><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData() - GetData()
returns EFI_SUCCESS, ProgressErr should be KEYWORD_HANDLER_ NO_ERROR.
Progress points to the string’s NULL terminator.</strong></td>
<td><p>2.</p>
<p>Check the system with <strong>GetData()</strong>, the storage
associated with the earlier keywords is not modified <strong>when an
EFI_NOT_FOUND error is generated during processing the second or later
keyword element.</strong></p></td>
</tr>
<tr class="even">
<td>5.18.7.1.3</td>
<td>0xe334ff21, 0x4005, 0x449a, 0x83, 0x1, 0x97, 0x44, 0xc1, 0xb0, 0xaf,
0xd5</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData()
-</strong></p>
<p><strong>SetData() returns EFI_SUCCESS when an element of the
KeywordString was found. Progress points to the string’s NULL terminator
and ProgressErr should be KEYWORD_HANDLER_ NO_ERROR.</strong></p></td>
<td>1. Call <strong>SetData() when an element of the KeywordString was
found, the return status should be EFI_SUCCESS. Progress points to the
string’s NULL terminator and ProgressErr should be KEYWORD_HANDLER_
NO_ERROR.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.1.4</td>
<td>0x8a4618b3, 0xa012, 0x40c4, 0xba, 0x6, 0xa, 0x93, 0x79, 0xb4, 0x64,
0x58</td>
<td><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData() - GetData()
returns EFI_SUCCESS, ProgressErr should be KEYWORD_HANDLER_ NO_ERROR.
Progress points to the string’s NULL terminator.</strong></td>
<td><p>2.</p>
<p>Check the system with <strong>GetData()</strong>, the storage
associated with the earlier keywords should be saved
correctly<strong>.</strong></p></td>
</tr>
<tr class="even">
<td>5.18.7.1.5</td>
<td>0xfe4f680c, 0xcbe, 0x4f85, 0xb3, 0x20, 0x5e, 0xcc, 0x9d, 0xce, 0xc5,
0x88</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData()
-</strong></p>
<p><strong>SetData() returns EFI_INVALID_PARAMETER when KeywordString
was NULL.</strong></p></td>
<td>1. Call <strong>SetData() when KeywordString was found, the return
status should be EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.1.6</td>
<td>0xe7966ef2, 0x941e, 0x4a59, 0x8e, 0x15, 0x2f, 0xde, 0x41, 0x9d,
0xfc, 0x91</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData()
-</strong></p>
<p><strong>SetData() returns EFI_INVALID_PARAMETER when parsing of the
KeywordString resulted in an error and Progress points to the most
recent '&amp;' before the first failing string
element.</strong></p></td>
<td>1. Call <strong>SetData() when parsing of the KeywordString resulted
in an error, the return status should be EFI_INVALID_PARAMETER. Progress
should point to the most recent '&amp;' before the first failing string
element.</strong></td>
</tr>
<tr class="even">
<td>5.18.7.1.7</td>
<td>0x1eff122d, 0xa263, 0x43bd, 0x94, 0xfc, 0x82, 0xb, 0x8b, 0xc9, 0xfa,
0x7c</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData()
-</strong></p>
<p><strong>SetData() returns EFI_NOT_FOUND when an element of the
KeywordString was not found and Progress points to the most recent
'&amp;' before the first failing string element.</strong></p></td>
<td>1. Call <strong>SetData() when an element of the KeywordString was
not found, the return status should be EFI_NOT_FOUND. Progress should
point to the most recent '&amp;' before the first failing string
element.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.1.8</td>
<td>0x4bd58084, 0xb158, 0x43fe, 0xbb, 0x87, 0x31, 0x8f, 0xb2, 0x3f,
0x7a, 0xe9</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. SetData()
-</strong></p>
<p><strong>SetData() returns EFI_ACCESS_DENIED when the ReadOnly element
is written and Progress points to the most recent '&amp;' before the
first failing string element.</strong></p></td>
<td>1. Call <strong>SetData() when the ReadOnly element is written, the
return status should be EFI_ACCESS_DENIED. Progress should point to the
most recent '&amp;' before the first failing string
element.</strong></td>
</tr>
</tbody>
</table>


### GetData()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 24%" />
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
<td>5.18.7.2.1</td>
<td>0x852b267e, 0xcbe, 0x4bd6, 0x85, 0x4d, 0x3b, 0xbd, 0xf0, 0xa0, 0xc,
0x49</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_SUCCESS when KeywordString and
NameSpaceId are NULL.</strong></p></td>
<td>1. Call <strong>GetData()when KeywordString and NameSpaceId are
NULL,</strong> the <strong>return status should be EFI_SUCCESS.
ProgressErr should be KEYWORD_HANDLER_NO_ERROR.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.2.2</td>
<td>0x247b91db, 0xf60b, 0x457f, 0xb9, 0x10, 0xb3, 0xc3, 0x30, 0xa8,
0xaf, 0x88</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() should output the correct result as expected
format.</strong></p></td>
<td>2. The preinstalled Str should be included in the
<strong>Results</strong> outputted from the
<strong>GetData()</strong>.</td>
</tr>
<tr class="even">
<td>5.18.7.2.3</td>
<td>0xf57e9ce0, 0x827a, 0x4d35, 0x89, 0xb8, 0xde, 0x24, 0x57, 0xe7,
0x94, 0xfb</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_SUCCESS when KeywordString is NULL and
NameSpaceId is one valid expression.</strong></p></td>
<td>1. Call <strong>GetData()when KeywordString is NULL and NameSpaceId
is one valid expression,</strong> the <strong>return status should be
EFI_SUCCESS. ProgressErr should be
KEYWORD_HANDLER_NO_ERROR.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.2.4</td>
<td>0x170ab626, 0x648c, 0x4088, 0x8b, 0x5d, 0xf8, 0xf2, 0x9d, 0x65,
0xaf, 0xba</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() should output the correct result as expected
format.</strong></p></td>
<td>2. The preinstalled Str should be included in the
<strong>Results</strong> outputted from the
<strong>GetData()</strong>.</td>
</tr>
<tr class="even">
<td>5.18.7.2.5</td>
<td>0x60bcfe65, 0xe73a, 0x46dd, 0xa9, 0x42, 0x22, 0xb4, 0xeb, 0x30,
0xb8, 0x7c</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_SUCCESS when KeywordString is the valid
expression (with PathHdr) and NameSpaceId is one valid
expression.</strong></p></td>
<td>1. Call <strong>GetData() when KeywordString is the valid expression
(with PathHdr) and NameSpaceId is one valid expression,</strong> the
<strong>return status should be EFI_SUCCESS. ProgressErr should be
KEYWORD_HANDLER_NO_ERROR and Progress points to the string’s NULL
terminator.</strong></td>
</tr>
<tr class="odd">
<td>5.18.7.2.6</td>
<td>0x7cc0b84, 0x4128, 0x4c66, 0x91, 0x90, 0x76, 0x15, 0x81, 0xb, 0x95,
0x9d</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_SUCCESS when KeywordString is the valid
expression (without PathHdr) and NameSpaceId is one valid
expression.</strong></p></td>
<td>2. Call <strong>GetData() when KeywordString is the valid expression
(without PathHdr) and NameSpaceId is one valid expression,</strong> the
<strong>return status should be EFI_SUCCESS. ProgressErr should be
KEYWORD_HANDLER_NO_ERROR and Progress points to the string’s NULL
terminator.</strong></td>
</tr>
<tr class="even">
<td>5.18.7.2.7</td>
<td>0x6114b15, 0xab62, 0x40f5, 0x86, 0xf6, 0x21, 0xd1, 0x81, 0x2b, 0x7f,
0x6c</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() should output the correct result as expected
format.</strong></p></td>
<td>3. The <strong>Results</strong> outputted with PathHdr should be
included in the <strong>Results</strong> outputted without PathHdr</td>
</tr>
<tr class="odd">
<td>5.18.7.2.8</td>
<td>0x378ef819, 0x29ee, 0x4875, 0x8c, 0xb2, 0x94, 0x6a, 0x77, 0xb1,
0x48, 0x73</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_INVALID_PARAMETER when Progress,
ProgressErr, or Resuts is NULL.</strong></p></td>
<td>1. Call <strong>GetData() when Progress, ProgressErr, or Resuts is
NULL,</strong> the <strong>return status should be
EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.18.7.2.9</td>
<td>0xb90fe257, 0xf693, 0x4c3e, 0x89, 0x59, 0x14, 0xb, 0xcf, 0x44, 0x7b,
0x5d</td>
<td><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData() - GetData()
returns EFI_INVALID_PARAMETER when</strong> Parsing of the
<strong>KeywordString</strong> resulted in an
error<strong>.</strong></td>
<td>1. Call <strong>GetData()</strong> when Parsing of the
<strong>KeywordString</strong> resulted in an error, the <strong>return
status should be EFI_INVALID_PARAMETER</strong>.
<strong>Progress</strong> should point to the most recent '&amp;' before
the first failing string element and <strong>ProgressErr</strong> should
be <strong>KEYWORD_HANDLER_MALFORMED_STRING</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.7.2.10</td>
<td>0x138298f2, 0x7b86, 0x49b7, 0x9c, 0xa7, 0x6d, 0x69, 0xbe, 0x8b,
0x52, 0xfd</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_NOT_FOUND when an element of the
KeywordString was not found.</strong></p></td>
<td>1. Call <strong>GetData()</strong> when <strong>an element of the
KeywordString was not found</strong>, the <strong>return status should
be EFI_NOT_FOUND</strong>. <strong>Progress</strong> should point to the
most recent '&amp;' before the first failing string element and
<strong>ProgressErr</strong> should be
<strong>KEYWORD_HANDLER_KEYWORD_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.7.2.11</td>
<td>0x48dab3bf, 0xb3dc, 0x4960, 0xa6, 0xf8, 0xb5, 0x1c, 0xd3, 0xfa,
0xfa, 0xe0</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_NOT_FOUND when the NamespaceId
specified was not found.</strong></p></td>
<td>1. Call <strong>GetData()</strong> when <strong>the NamespaceId
specified was not found</strong>, the <strong>return status should be
EFI_NOT_FOUND</strong>. <strong>ProgressErr</strong> should be
<strong>KEYWORD_HANDLER_KEYWORD_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.18.7.2.12</td>
<td>0xab69961e, 0xd77d, 0x4781, 0x8e, 0xe5, 0xf9, 0x13, 0x55, 0xc7,
0xce, 0x91</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() returns EFI_NOT_FOUND when an element of the
KeywordString was not found.</strong></p></td>
<td>1. Call <strong>GetData()</strong> when <strong>an element of the
KeywordString was not found</strong>, the <strong>return status should
be EFI_NOT_FOUND</strong>. <strong>Progress</strong> should point to the
most recent '&amp;' before the first failing string element and
<strong>ProgressErr</strong> should be
<strong>KEYWORD_HANDLER_KEYWORD_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.18.7.2.13</td>
<td>0xc6b310c5, 0xdddf, 0x4e1d, 0x9d, 0x8c, 0x20, 0x16, 0xe7, 0x66,
0xa6, 0xae</td>
<td><p><strong>EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL. GetData()
-</strong></p>
<p><strong>GetData() should output Results string contains values
returned for all keywords processed prior to the keyword generating the
error.</strong></p></td>
<td>2. The <strong>returned Results string should contain values for all
keywords processed prior to the keyword generating the
error.</strong></td>
</tr>
</tbody>
</table>


## EFI_HII_FONT_EX_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_FONT_EX_PROTOCOL Section.

### StringToImageEx()

<table>
<colgroup>
<col style="width: 11%" />
<col style="width: 29%" />
<col style="width: 29%" />
<col style="width: 29%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.18.8.1.1</td>
<td>0x81b18c28, 0x7d09, 0x4794, 0xab, 0x4e, 0x92, 0x9b, 0xb7, 0x2f,
0x19, 0x67</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_INVALID_PARAMETER when String is NULL.</td>
<td>1. Call StringToImageEx() when String is NULL, the return status
should be EFI_INVALID_PARAMETER.</td>
</tr>
<tr class="odd">
<td>5.18.8.1.2</td>
<td>0xeba34749, 0x9763, 0x4203, 0x9f, 0xd, 0x26, 0x3a, 0xa4, 0xe9, 0xd6,
0x9a</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_INVALID_PARAMETER when Blt is NULL.</td>
<td>1. Call StringToImageEx() when Blt is NULL, the return status should
be EFI_INVALID_PARAMETER.</td>
</tr>
<tr class="even">
<td>5.18.8.1.3</td>
<td>0xd6514302, 0x4b34, 0x4bae, 0xa0, 0xcd, 0x37, 0x77, 0xb8, 0x43, 0xc,
0x26</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_INVALID_PARAMETER with invalid Flags combination.</td>
<td>1. Call StringToImageEx() when Flags is the combination of
EFI_HII_OUT_FLAG_CLIP_CLEAN_X and EFI_HII_OUT_FLAG_WRAP, the return
status should be EFI_INVALID_PARAMETER.</td>
</tr>
<tr class="odd">
<td>5.18.8.1.4</td>
<td>0xf711f218, 0x8987, 0x4fa9, 0xb4, 0xb6, 0x64, 0x1e, 0xc1, 0x76,
0xe1, 0xc8</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_INVALID_PARAMETER with invalid Flags combination.</td>
<td>1. Call StringToImageEx() when Flags is
EFI_HII_OUT_FLAG_CLIP_CLEAN_X without EFI_HII_OUT_FLAG_CLIP, the return
status should be EFI_INVALID_PARAMETER.</td>
</tr>
<tr class="even">
<td>5.18.8.1.5</td>
<td>0x4dd0210d, 0x87b1, 0x4352, 0xa6, 0x16, 0x57, 0x91, 0x78, 0x73,
0xe0, 0xa0</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with valid Flags combination.</td>
<td>1. Call StringToImageEx() with the valid Flags combination and use
EFI_GRAPUICS_OUTPUT_BLT_PIXEL structure in EFI_IMAGE_OUTPUT structure,
the return status should be EFI_SUCCESS.</td>
</tr>
<tr class="odd">
<td>5.18.8.1.6</td>
<td>0x2af74a94, 0xed7, 0x4b68, 0x9c, 0xdd, 0xfa, 0xdf, 0xfe, 0x6, 0x68,
0x1f</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with valid Flags combination.</td>
<td>1. Call StringToImageEx() with the valid Flags combination and use
EFI_GRAPUICS_OUTPUT_PROTOCOL in EFI_IMAGE_OUTPUT structure, the return
status should be EFI_SUCCESS.</td>
</tr>
<tr class="even">
<td>5.18.8.1.7</td>
<td>0x7047fe55, 0x6c8c, 0x4062, 0x8a, 0x24, 0x26, 0xb5, 0x33, 0x88,
0x62, 0x81</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with valid parameters for all ASCII visible
characters. Each image must equal to sys default glyph.</td>
<td>1. Call StringToImageEx() with the valid parameters and StringInfo
is NULL. Compare image output with system default font glyph image.</td>
</tr>
<tr class="odd">
<td>5.18.8.1.8</td>
<td>0xf09da704, 0x352, 0x4afa, 0x90, 0x8f, 0x83, 0x73, 0xf2, 0xe9, 0xe6,
0x2c</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with valid parameters for all ASCII visible
characters. Each image must equal to the specific font glyph.</td>
<td>1. Register a specific font package. Call StringToImageEx() with the
valid parameters and StringInfo is the specific font. Compare image
output with specific font glyph image registered.</td>
</tr>
<tr class="even">
<td>5.18.8.1.9</td>
<td>0xbee39111, 0x1e5b, 0x4574, 0xae, 0xeb, 0x2, 0xdd, 0xaa, 0x17, 0x42,
0xbf</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Call StringToImageEx() with</p>
<p>EFI_HII_DIRECT_TO_SCREEN. For the final row, the
RowInfoArray.LineHeight and RowInfoArray.BaseLine may describe pixels
which are outside the limit specified by Blt.Height (unless
EFI_HII_OUT_FLAG_CLIP_CLEAN_Y is specified) even though those pixels
were not drawn.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.10</td>
<td>0x2c36e6b5, 0x983f, 0x4e05, 0x90, 0xdd, 0xfa, 0x79, 0xfd, 0xdb,
0x15, 0xcd</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP |
EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP |
EFI_HII_DIRECT_TO_SCREEN. For the final row, the RowInfoArray.LineHeight
and RowInfoArray.BaseLine may describe pixels which are outside the
limit specified by Blt.Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y is
specified) even though those pixels were not drawn.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.11</td>
<td>0x7dd51e66, 0xf38f, 0x4412, 0xa6, 0xd8, 0x32, 0x37, 0x85, 0xb9, 0x8,
0x31</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN. If a
character’s right-most pixel can’t fit, then it will not be drawn at
all.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.12</td>
<td>0x76805500, 0x3e74, 0x44cb, 0x95, 0x9b, 0x63, 0xf7, 0xb7, 0x78,
0x92, 0x17</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN. If a row’s
bottom-most pixel exceeds screen Height, then it will not be drawn at
all.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.13</td>
<td>0xe18566cf, 0x619d, 0x454c, 0x85, 0x6b, 0xe, 0x4e, 0xd3, 0x1c, 0x4a,
0xf1</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_IGNORE_IF_NO_GLYPH |
EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String with line
break opportunity.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_IGNORE_IF_NO_GLYPH |
EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String with line
break opportunity (SPACE is a line break opportunity). Check display
with wrapper at right place.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.14</td>
<td>0xacba2f9a, 0x1052, 0x478d, 0x96, 0x99, 0x78, 0xa1, 0x1e, 0x65, 0x5,
0x5d</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity.
String is designed to display as if EFI_HII_OUT_FLAG_CLIP_CLEAN_X is
set.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.15</td>
<td>0x82482a71, 0x2a32, 0x4104, 0xb7, 0x32, 0x91, 0xa0, 0x95, 0x81,
0x50, 0x49</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Call StringToImageEx() with EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN. If a row’s bottom-most pixel can’t fit, then
it will not be drawn at all. This flag requires that
EFI_HII_OUT_FLAG_CLIP be set.</p>
<p>2. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.16</td>
<td>0xf1c89a03, 0x5b7a, 0x4d1d, 0xbe, 0x9, 0x5c, 0xf7, 0xe5, 0x67, 0xe,
0x77</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_DIRECT_TO_SCREEN.</p>
<p>3. Check EFI_HII_DIRECT_TO_SCREEN only case if Blt is not NULL, then
EFI_HII_OUT_FLAG_CLIP is implied. String is designed to display with
full line.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.17</td>
<td>0x2154d7a2, 0x37e2, 0x43a3, 0xb4, 0xaf, 0xb3, 0x74, 0x8a, 0x6c,
0x54, 0xf0</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP.</p>
<p>3. For the final row, the RowInfoArray.LineHeight
andRowInfoArray.BaseLine may describe pixels which are outside the limit
specified by Blt.Height (unless EFI_HII_OUT_FLAG_CLIP_CLEAN_Y is
specified) even though those pixels were not drawn.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.18</td>
<td>0x6206dfcf, 0x6fb3, 0x4020, 0xba, 0xf3, 0x74, 0xe, 0xed, 0xac, 0x9c,
0xb2</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_DIRECT_TO_SCREEN.</p>
<p>3. If a character’s right-most pixel can’t fit, then it will not be
drawn at all.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.19</td>
<td>0x76bd46eb, 0x56a1, 0x4b66, 0xab, 0x63, 0x2e, 0xf1, 0x69, 0x1a,
0xfd, 0x80</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_OUT_FLAG_CLIP |
EFI_HII_OUT_FLAG_CLIP_CLEAN_Y | EFI_HII_DIRECT_TO_SCREEN.</p>
<p>3. If a row’s bottom-most pixel exceeds screen Height, then it will
not be drawn at all.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.20</td>
<td>0x9782016a, 0xcd4c, 0x4d39, 0x91, 0xc3, 0x7e, 0xe3, 0xce, 0xfd,
0xcc, 0x2d</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_IGNORE_IF_NO_GLYPH |
EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String with line
break opportunity.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_IGNORE_IF_NO_GLYPH |
EFI_HII_OUT_FLAG_WRAP | EFI_HII_DIRECT_TO_SCREEN and String with line
break opportunity (Space is a line-break).</p>
<p>3. Check if the display is right.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.21</td>
<td>0x2833962d, 0x3800, 0x45b3, 0x90, 0xf8, 0xfb, 0xe2, 0xee, 0xc6,
0x6e, 0xd9</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_OUT_FLAG_WRAP |
EFI_HII_DIRECT_TO_SCREEN and String without line break opportunity.</p>
<p>3. String is designed to display as if EFI_HII_OUT_FLAG_CLIP_CLEAN_X
is set.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="odd">
<td>5.18.8.1.22</td>
<td>0x12eb38a6, 0xfc, 0x4568, 0xa3, 0x44, 0x75, 0x40, 0xd3, 0x89, 0x88,
0xbe</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_IGNORE_LINE_BREAK |
EFI_HII_DIRECT_TO_SCREEN.</p>
<p>3. If a row’s bottom-most pixel can’t fit, then it will not be drawn
at all. This flag requires that EFI_HII_OUT_FLAG_CLIP be set.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
<tr class="even">
<td>5.18.8.1.23</td>
<td>0x9c9802d4, 0x98e5, 0x46b9, 0xab, 0xc7, 0x66, 0x17, 0xb7, 0x80,
0x40, 0x29</td>
<td>EFI_HII_FONT_EX_PROTOCOL. StringToImageEx() - StringToImageEx()
returns EFI_SUCCESS with parameters EFI_HII_OUT_FLAG_TRANSPARENT.</td>
<td><p>1. Register a specific font package.</p>
<p>2. Call StringToImageEx() with EFI_HII_OUT_FLAG_TRANSPARENT.</p>
<p>3. Check the output buffer StringInfo background should be ignored
according to UEFI Spec.</p>
<p>4. The return status should be EFI_SUCCESS.</p></td>
</tr>
</tbody>
</table>


### StringIdToImageEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.8.2.1 | 0x7baa464a, 0x572c, 0x4fa9, 0x80, 0xa3, 0x99, 0xa0, 0x61, 0xc0, 0x46, 0x4f | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when Blt is NULL. | 1\. Call StringIdToImageEx() when Blt is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.2 | 0xa086a16b, 0x6e61, 0x4f06, 0xb5, 0xd, 0xac, 0x6e, 0x80, 0x71, 0x11, 0xe4 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when PackageList is NULL. | 1\. Call StringIdToImageEx() when PackageList is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.3 | 0x10931cc4, 0xfa08, 0x4df8, 0xab, 0x6a, 0xb3, 0x8f, 0xa5, 0xc6, 0x84, 0x24 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when PackageList is not in Database. | 1\. Call StringIdToImageEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. |
| 5.18.8.2.4 | 0x7623d5de, 0x71e9, 0x49f6, 0xb7, 0x9f, 0xd2, 0x6f, 0x38, 0x69, 0xae, 0xe9 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when StringId is not in PackageList. | 1\. Call StringIdToImageEx() when StringId is not in PackageList, the return status should be EFI_NOT_FOUND. |
| 5.18.8.2.5 | 0x36cd9086, 0x8e5e, 0x4a95, 0xb4, 0xdd, 0x56, 0x94, 0x74, 0x5c, 0x21, 0x37 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when Flags is the invalid combination. | 1\. Call StringIdToImageEx() when Flags are EFI_HII_OUT_FLAG_CLIP_CLEAN_X with EFI_HII_OUT_FLAG_WRAP, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.6 | 0x16b7317e, 0x1196, 0x4323, 0x9d, 0xeb, 0xe8, 0xc7, 0x44, 0x32, 0x7e, 0x20 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when Flags is the invalid combination. | 1\. Call StringIdToImageEx() when Flags is EFI_HII_OUT_FLAG_CLIP_CLEAN_X without EFI_HII_OUT_FLAG_CLIP, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.7 | 0xc3a512bc, 0x6464, 0x4e74, 0xab, 0x8d, 0x41, 0xd5, 0x42, 0xd6, 0xad, 0x66 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_SUCCESS with valid parameters. | 1\. Call StringIdToImageEx() with valid parameters and use EFI_GRAPUICS_OUTPUT_BLT_PIXEL structure in EFI_IMAGE_OUTPUT structure, the return status should be EFI_SUCCESS. |
| 5.18.8.2.8 | 0x9c84a237, 0x9ba5, 0x417a, 0x94, 0xcd, 0xf5, 0xed, 0x37, 0xf7, 0xbb, 0x9e | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_SUCCESS with valid parameters. | 1\. Call StringIdToImageEx() with valid parameters and use EFI_GRAPUICS_OUTPUT_PROTOCOL structure in EFI_IMAGE_OUTPUT structure, the return status should be EFI_SUCCESS. |


### GetGlyphEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.8.3.1 | 0x4e1b65f1, 0xa0c1, 0x4f13, 0xb6, 0xfb, 0x2a, 0xdc, 0xaa, 0x21, 0x8d, 0x89 | **EFI_HII_FONT_EX_PROTOCOL. GetGlyphEx() - GetGlyphEx () returns EFI_INVALID_PARAMETER when Blt is NULL.** | 1\. Call **GetGlyphEx() when Blt is NULL,** the **return status should be EFI_INVALID_PARAMETER.** |
| 5.18.8.3.2 | 0x139af9e5, 0x5d3e, 0x46b2, 0x83, 0x9c, 0x52, 0x54, 0x66, 0xf1, 0xe0, 0xe | **EFI_HII_FONT_EX_PROTOCOL. GetGlyphEx() - GetGlyphEx () returns EFI_INVALID_PARAMETER when \*Blt is not NULL.** | 1\. Call **GetGlyphEx() when \*Blt is not NULL,** the **return status should be EFI_INVALID_PARAMETER.** |
| 5.18.8.3.3 | 0xf3fc9dce, 0x7f2c, 0x45d7, 0x87, 0xcf, 0x55, 0x17, 0xea, 0xcf, 0x9d, 0x4d | **EFI_HII_FONT_EX_PROTOCOL. GetGlyphEx() - GetGlyphEx () returns EFI_SUCCESS with valid parameters.** | 1\. Call **GetGlyphEx() with valid parameters,** the **return status should be EFI_SUCCESS.** |


### GetFontInfoEx()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 16%" />
<col style="width: 27%" />
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
<td>5.18.8.4.1</td>
<td>0x9511abcb, 0x462e, 0x4b96, 0xb3, 0xf, 0xbf, 0x9b, 0xf5, 0x68, 0x73,
0xeb</td>
<td><p><strong>EFI_HII_FONT_EX_PROTOCOL.</strong> </p>
<p><strong>GetFontInfoEx() - GetFontInfoEx() returns
EFI_INVALID_PARAMETER with invalid EFI_FONT_INFO_MASK
combination.</strong></p></td>
<td>1. Call <strong>GetFontInfoEx() when StringInfoIn-&gt;FontInfoMask
is the invalid combination,</strong> the <strong>return status should be
EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.18.8.4.2</td>
<td>0x167059e1, 0x4bf6, 0x4d8c, 0xb0, 0x96, 0x7b, 0xf4, 0x61, 0x7b,
0x75, 0x4b</td>
<td><strong>EFI_HII_FONT_EX_PROTOCOL. GetFontInfoEx() - GetFontInfoEx()
returns EFI_SUCCESS with valid parameters.</strong></td>
<td>1. Call <strong>GetFontInfoEx() with valid parameters,</strong> the
<strong>return status should be EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.18.8.4.3</td>
<td>0x29a5204a, 0x507e, 0x4dc0, 0xa1, 0xb1, 0x90, 0x53, 0xf7, 0x2e,
0xd7, 0x77</td>
<td><strong>EFI_HII_FONT_EX_PROTOCOL. GetFontInfoEx() - GetFontInfoEx()
returns EFI_SUCCESS with valid parameters(StringInfoIn is
NULL).</strong></td>
<td>1. Call <strong>GetFontInfoEx() with valid parameters(StringInfoIn
is NULL),</strong> the <strong>return status should be
EFI_SUCCESS.</strong></td>
</tr>
</tbody>
</table>


### GetGlyphInfo()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.8.5.1 | 0x298cb0c7, 0x7e78, 0x4e3e, 0x8d, 0x42, 0xc2, 0x2c, 0x16, 0xa0, 0x83, 0x31 | **EFI_HII_FONT_EX_PROTOCOL. GetGlyphInfo() - GetGlyphInfo() returns EFI_INVALID_PARAMETER when GlyphInfo is NULL.** | 1\. Call **GetGlyphInfo() when GlyphInfo is NULL,** the **return status should be EFI_INVALID_PARAMETER.** |
| 5.18.8.5.2 | 0xb20f87ce, 0xbc6b, 0x4e27, 0xb8, 0x2a, 0x61, 0x53, 0x59, 0xab, 0x92, 0xa7 | **EFI_HII_FONT_EX_PROTOCOL. GetFontInfoEx() - GetFontInfoEx() returns EFI_INVALID_PARAMETER when FontDisplayInfo is NULL.** | 1\. Call **GetGlyphInfo() when FontDisplayInfo is NULL,** the **return status should be EFI_INVALID_PARAMETER.** |
| 5.18.8.5.3 | 0x347f2e9e, 0x70c4, 0x4e89, 0xb9, 0x4, 0x7e, 0x5f, 0xbd, 0x78, 0x4d, 0xb3 | **EFI_HII_FONT_EX_PROTOCOL. GetFontInfoEx() - GetFontInfoEx() returns EFI_SUCCESS with valid parameters.** | 1\. Call **GetGlyphInfo() with valid parameters,** the **return status should be EFI_SUCCESS.** |


## EFI_HII_IMAGE_EX_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HII_IMAGE_EX_PROTOCOL Section.

### NewImageEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.3.1 | 0xe88ca946, 0xed6d, 0x415d, 0x85, 0x55, 0x0, 0x27, 0x9f, 0x14, 0xc3, 0xf9 | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_NOT_FOUND when ImageId is invalid. | 0x7baa464a, 0x572c, 0x4fa9, 0x80, 0xa3, 0x99, 0xa0, 0x61, 0xc0, 0x46, 0x4f |
| 5.18.9.3.2 | 5.18.9.6.2 | 0xf61dfb48, 0x1c77, 0x4907, 0x9f, 0xab, 0x43, 0x93, 0x17, 0x8c, 0x99, 0xee | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_INVALID_PARAMETER when Image is NULL. |
| 5.18.8.2.2 | 0xa086a16b, 0x6e61, 0x4f06, 0xb5, 0xd, 0xac, 0x6e, 0x80, 0x71, 0x11, 0xe4 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when PackageList is NULL. | 1\. Call StringIdToImageEx() when PackageList is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.3 | 0x10931cc4, 0xfa08, 0x4df8, 0xab, 0x6a, 0xb3, 0x8f, 0xa5, 0xc6, 0x84, 0x24 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when PackageList is not in Database. | 1\. Call StringIdToImageEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. |


### GetImageEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.3.1 | 0xe88ca946, 0xed6d, 0x415d, 0x85, 0x55, 0x0, 0x27, 0x9f, 0x14, 0xc3, 0xf9 | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_NOT_FOUND when ImageId is invalid. | 0x7baa464a, 0x572c, 0x4fa9, 0x80, 0xa3, 0x99, 0xa0, 0x61, 0xc0, 0x46, 0x4f |
| 5.18.9.3.2 | 5.18.9.6.2 | 0xf61dfb48, 0x1c77, 0x4907, 0x9f, 0xab, 0x43, 0x93, 0x17, 0x8c, 0x99, 0xee | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_INVALID_PARAMETER when Image is NULL. |
| 5.18.8.2.2 | 0xa086a16b, 0x6e61, 0x4f06, 0xb5, 0xd, 0xac, 0x6e, 0x80, 0x71, 0x11, 0xe4 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when PackageList is NULL. | 1\. Call StringIdToImageEx() when PackageList is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.3 | 0x10931cc4, 0xfa08, 0x4df8, 0xab, 0x6a, 0xb3, 0x8f, 0xa5, 0xc6, 0x84, 0x24 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when PackageList is not in Database. | 1\. Call StringIdToImageEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. |
| 5.18.8.2.4 | 0x7623d5de, 0x71e9, 0x49f6, 0xb7, 0x9f, 0xd2, 0x6f, 0x38, 0x69, 0xae, 0xe9 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when StringId is not in PackageList. | 1\. Call StringIdToImageEx() when StringId is not in PackageList, the return status should be EFI_NOT_FOUND. |


### SetImageEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.3.1 | 0xe88ca946, 0xed6d, 0x415d, 0x85, 0x55, 0x0, 0x27, 0x9f, 0x14, 0xc3, 0xf9 | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_NOT_FOUND when ImageId is invalid. | 0x7baa464a, 0x572c, 0x4fa9, 0x80, 0xa3, 0x99, 0xa0, 0x61, 0xc0, 0x46, 0x4f |
| 5.18.9.3.2 | 5.18.9.6.2 | 0xf61dfb48, 0x1c77, 0x4907, 0x9f, 0xab, 0x43, 0x93, 0x17, 0x8c, 0x99, 0xee | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_INVALID_PARAMETER when Image is NULL. |
| 5.18.8.2.2 | 0xa086a16b, 0x6e61, 0x4f06, 0xb5, 0xd, 0xac, 0x6e, 0x80, 0x71, 0x11, 0xe4 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when PackageList is NULL. | 1\. Call StringIdToImageEx() when PackageList is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.8.2.3 | 0x10931cc4, 0xfa08, 0x4df8, 0xab, 0x6a, 0xb3, 0x8f, 0xa5, 0xc6, 0x84, 0x24 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when PackageList is not in Database. | 1\. Call StringIdToImageEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. |
| 5.18.8.2.4 | 0x7623d5de, 0x71e9, 0x49f6, 0xb7, 0x9f, 0xd2, 0x6f, 0x38, 0x69, 0xae, 0xe9 | EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_NOT_FOUND when StringId is not in PackageList. | 1\. Call StringIdToImageEx() when StringId is not in PackageList, the return status should be EFI_NOT_FOUND. |


### DrawImageEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.4.1 | 0x42dd08a5, 0xbd85, 0x4eab, 0xb4, 0x74, 0x9f, 0xe2, 0x55, 0x71, 0x56, 0x8f | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() returns EFI_INVALID_PARAMETER when Image is NULL. | 1\. Call DrawImageEx() when Image is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.4.2 | 0xcf06b84d, 0x8d1f, 0x43c1, 0xb5, 0xb2, 0xa3, 0x3a, 0x2, 0xc2, 0xd, 0x50 | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() returns EFI_INVALID_PARAMETER when Flag is EFI_HII_DRAW_FLAG_TRANSPARENT and Blt is NULL. | 1\. Call DrawImageEx() when Flag is EFI_HII_DRAW_FLAG_TRANSPARENT and Blt is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.4.3 | 0xa20a8ee4, 0x9bed, 0x4538, 0x94, 0x7a, 0xbf, 0xb7, 0x42, 0xa6, 0xaf, 0xd9 | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() returns EFI_INVALID_PARAMETER when Flag is EFI_HII_DIRECT_TO_SCREEN and no screen. | 1\. Call DrawImageEx() when Flag is EFI_HII_DIRECT_TO_SCREEN and no screen, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.4.4 | 0x8a4f106c, 0xdb5d, 0x4491, 0x96, 0xbd, 0x62, 0x9a, 0xa8, 0xa2, 0xc4, 0x25 | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() returns EFI_INVALID_PARAMETER when Flag is EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL. | 1\. Call DrawImageEx() when Flag is EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.4.5 | 0x4ed61351, 0xc6de, 0x4910, 0x97, 0x15, 0xcf, 0xc5, 0x5e, 0xe, 0x75, 0x9b | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() returns EFI_INVALID_PARAMETER when Flag is EFI_HII_DRAW_FLAG_DEFAULT and Blt points to NULL, but Image-\>Flag is EFI_IMAGE_TRANSPARENT. | 1\. Call DrawImageEx() when Flag is EFI_HII_DRAW_FLAG_DEFAULT and Blt points to NULL, but Image-\>Flag is EFI_IMAGE_TRANSPARENT, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.4.6 | 0x3ac875ed, 0x46d4, 0x4d1d, 0xac, 0xfe, 0xdb, 0x37, 0xe5, 0xf1, 0xb7, 0xd0 | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() return EFI_SUCCESS with valid parameters. | 1\. Call DrawImageEx() when Flag is EFI_HII_DRAW_FLAG_FORCE_OPAQUE, Blt is NULL and other valid parameters, the return status should be EFI_SUCCESS. |
| 5.18.9.4.7 | 0x16a8be, 0x4466, 0x4777, 0xa0, 0xbd, 0xa9, 0x10, 0x1c, 0x54, 0x19, 0xa0 | EFI_HII_FONT_EX_PROTOCOL. DrawImageEx() - DrawImageEx() return EFI_SUCCESS with valid parameters. | 1\. Call DrawImageEx() when Flag is the valid combination, Blt is NULL and other valid parameters, the return status should be EFI_SUCCESS. |


### DrawImageIdEx()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.5.1 | 0x24ddcd2b, 0xa9d8, 0x4ec5, 0xaf, 0xf6, 0x77, 0xf3, 0x69, 0x8c, 0xe, 0x19 | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_NOT_FOUND when PackageList is not in Database. | 1\. Call DrawImageIdEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. |
| 5.18.9.5.2 | 0x8f114d30, 0x684d, 0x402e, 0xb5, 0x35, 0x74, 0x34, 0x1e, 0xbb, 0x88, 0x5f | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_NOT_FOUND when PackageList is NULL. | 1\. Call DrawImageIdEx() when PackageList is NULL, the return status should be EFI_NOT_FOUND. |
| 5.18.9.5.3 | 0x446d5d03, 0xf2b6, 0x4627, 0xad, 0xd1, 0x75, 0x6d, 0xfe, 0xe9, 0x18, 0x3f | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_NOT_FOUND when ImageId is invalid. | 1\. Call DrawImageIdEx() when ImageId is invalid, the return status should be EFI_NOT_FOUND. |
| 5.18.9.5.4 | 0x6dbc9f6e, 0x2694, 0x44ec, 0x99, 0xe9, 0x2d, 0x67, 0x6a, 0xfe, 0x9f, 0x37 | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_NOT_FOUND when PackageList is NULL. | 1\. Call DrawImageIdEx() when PackageList is invalid, the return status should be EFI_NOT_FOUND. |
| 5.18.9.5.5 | 0x8c43a76, 0x7f57, 0x41dd, 0x87, 0x99, 0x13, 0xcf, 0xf2, 0x5, 0x9b, 0x6 | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_INVALID_PARAMETER when Flags is EFI_HII_DRAW_FLAG_FORCE_TRANS and Blt is NULL. | 1\. Call DrawImageIdEx() when Flags is EFI_HII_DRAW_FLAG_FORCE_TRANS and Blt is NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.5.6 | 0x39787a10, 0x1204, 0x41a5, 0xa8, 0xdb, 0xd3, 0xe9, 0x83, 0xc4, 0x47, 0x44 | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_INVALID_PARAMETER when Flags is EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL. | 1\. Call DrawImageIdEx() when Flags is EFI_HII_DRAW_FLAG_CLIP and Blt points to NULL, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.5.7 | 0x82c37f35, 0xbca3, 0x494e, 0x8a, 0xdb, 0xf6, 0xd8, 0xf0, 0x7a, 0xf6, 0xe3 | EFI_HII_IMAGE_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() returns EFI_INVALID_PARAMETER when Flags is EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL and Image-\>Flags is EFI_IMAGE_TRANSPARENT. | 1\. Call DrawImageIdEx() when Flags is EFI_HII_DRAW_FLAG_DEFAULT, Blt points to NULL and Image-\>Flags is EFI_IMAGE_TRANSPARENT, the return status should be EFI_INVALID_PARAMETER. |
| 5.18.9.5.8 | 0x1c03d9b0, 0x8d9c, 0x40bf, 0x94, 0xa7, 0xa7, 0x85, 0xa3, 0x52, 0xa2, 0x68 | EFI_HII_FONT_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() return EFI_SUCCESS with valid parameters. | 1\. Call DrawImageIdEx() when Flag is EFI_HII_DRAW_FLAG_FORCE_OPAQUE, Blt is NULL and other valid parameters, the return status should be EFI_SUCCESS. |
| 5.18.9.5.9 | 0x5ee23086, 0xe0ee, 0x4cc8, 0x85, 0xf2, 0x5a, 0xd3, 0x52, 0xd7, 0x4d, 0xb7 | EFI_HII_FONT_EX_PROTOCOL. DrawImageIdEx() - DrawImageIdEx() return EFI_SUCCESS with valid parameters. | 1\. Call DrawImageIdEx() when Flag is the valid combination, Blt is NULL and other valid parameters, the return status should be EFI_SUCCESS. |


### GetImageInfo()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.18.9.3.1 | 0xe88ca946, 0xed6d, 0x415d, 0x85, 0x55, 0x0, 0x27, 0x9f, 0x14, 0xc3, 0xf9 | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_NOT_FOUND when ImageId is invalid. | 0x7baa464a, 0x572c, 0x4fa9, 0x80, 0xa3, 0x99, 0xa0, 0x61, 0xc0, 0x46, 0x4f |
| 5.18.9.6.2 | 0xf61dfb48, 0x1c77, 0x4907, 0x9f, 0xab, 0x43, 0x93, 0x17, 0x8c, 0x99, 0xee | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_INVALID_PARAMETER when Image is NULL. | 1\. Call GetImageInfo() when Image is NULL, the return status should be EFI_INVALID_PARAMETER. |
| EFI_HII_FONT_EX_PROTOCOL. StringIdToImageEx() - StringIdToImageEx() returns EFI_INVALID_PARAMETER when PackageList is NULL. | 1\. Call StringIdToImageEx() when PackageList is NULL, the return status should be EFI_INVALID_PARAMETER. | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_INVALID_PARAMETER when ImageId is 0. | 1\. Call GetImageInfo() when ImageId is 0, the return status should be EFI_INVALID_PARAMETER. |
| 1\. Call StringIdToImageEx() when PackageList is not in Database, the return status should be EFI_NOT_FOUND. | 0x9cf6b34c, 0x4d53, 0x464e, 0x99, 0x4e, 0xd0, 0x3, 0xb5, 0x7b, 0x8b, 0x67 | EFI_HII_IMAGE_EX_PROTOCOL. GetImageInfo() - GetImageInfo() returns EFI_SUCCESS with valid parameters. | 1\. Call GetImageInfo() with valid parameters, the return status should be EFI_SUCCESS. |

