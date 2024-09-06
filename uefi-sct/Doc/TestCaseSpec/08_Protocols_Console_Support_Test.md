# Protocols Console Support Test

## EFI_SIMPLE\_ TEXT_INPUT_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_SIMPLE_TEXT_INPUT_PROTOCOL Section.

### Reset()

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
<td>5.6.1.1.1</td>
<td>0x7cb5f8dd, 0x7346, 0x484b, 0xb1, 0xb3, 0xa6, 0x46, 0x69, 0x6d,
0xea, 0xe7</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_PROTOCOL.Reset – Reset()</strong>
returns <strong>EFI_SUCCESS</strong> with <em>ExtendedVerification</em>
as <strong>FALSE.</strong></td>
<td>1. Call <strong>Reset()</strong> with <em>ExtendedVerification</em>
as <strong>FALSE</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.1.1.2</td>
<td>0x6fc31add, 0xf34b, 0x4b56, 0x9b, 0xa6, 0x36, 0xb2, 0x7c, 0xbe,
0xf5, 0xa2</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_PROTOCOL.Reset –
ReadKeyStroke()</strong> returns <strong>EFI_NOT_READY</strong> when
there is no key has been stroked.</td>
<td><p>1. Call <strong>Reset()</strong> with
<em>ExtendedVerification</em> as <strong>FALSE</strong>.</p>
<p>2. After <strong>Reset()</strong>, do not stroke any key, and call
<strong>ReadKeyStroke()</strong>. The return code should be
<strong>EFI_NOT_READY</strong></p></td>
</tr>
<tr class="even">
<td>5.6.1.1.3</td>
<td>0x8da56db6, 0xd7df, 0x4029, 0xba, 0x98, 0x37, 0x46, 0x0b, 0x21,
0x0e, 0x3b</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_PROTOCOL.Reset – Reset()</strong>
returns <strong>EFI_SUCCESS</strong> with <em>ExtendedVerification</em>
as <strong>TRUE.</strong></td>
<td>1. Call <strong>Reset()</strong> with <em>ExtendedVerification</em>
as <strong>TRUE</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.1.1.4</td>
<td>0x3d51b174, 0x59f8, 0x44bc, 0xb7, 0xf7, 0x9a, 0x11, 0x2c, 0x51,
0x82, 0xa1</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_PROTOCOL.Reset –
ReadKeyStroke()</strong> returns <strong>EFI_NOT_READY</strong> when
there is no key that has been stroked.</td>
<td><p>1. Call <strong>Reset()</strong> with
<em>ExtendedVerification</em> as <strong>TRUE</strong>.</p>
<p>2. After <strong>Reset()</strong>, do not stroke any key, and call
<strong>ReadKeyStroke()</strong>. The return code should be
<strong>EFI_NOT_READY</strong></p></td>
</tr>
</tbody>
</table>


### ReadKeyStroke()

No automatic test case is designed to verify this function.

## EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL Section.

UEFI 2.1 Specification, Section 11.3.

### Reset()

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
<td>5.6.2.1.1</td>
<td>0xecaf43c6, 0x6b77, 0x413a, 0x89, 0x8f, 0x28, 0x0e, 0x92, 0x5f,
0xf9, 0x43</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Reset – Reset()</strong>
without Extended Verification Mode</td>
<td><p>1. Call <strong>Reset()</strong> with
<em>ExtendedVerification</em> as <strong>FALSE</strong>.</p>
<p>2. Check cursor position. It should be (0,0).</p></td>
</tr>
<tr class="odd">
<td>5.6.2.1.2</td>
<td>0xc40bba44, 0xcfa3, 0x4494, 0xaf, 0xa5, 0xfa, 0x2f, 0x78, 0xcb,
0x20, 0x20</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Reset – Reset()</strong>
without Extended Verification Mode returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>Reset()</strong> with <em>ExtendedVerification</em>
as <strong>FALSE</strong>. The return code should be
<strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.6.2.1.3</td>
<td>0x51267bf4, 0x7b3e, 0x46fd, 0xac, 0x6c, 0xff, 0x8e, 0x54, 0x61,
0xd1, 0x7f</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Reset – Reset()</strong>
with Extended Verification Mode</td>
<td><p>1. Call <strong>Reset()</strong> with
<em>ExtendedVerification</em> as <strong>TRUE</strong>.</p>
<p>2. Check cursor position. It should be (0,0).</p></td>
</tr>
<tr class="odd">
<td>5.6.2.1.4</td>
<td>0x1771a342, 0xbbc3, 0x43da, 0x91, 0x4d, 0x7d, 0x59, 0xb7, 0xd8,
0x86, 0x2e</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Reset – Reset()</strong>
with Extended Verification Mode returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>Reset()</strong> with <em>ExtendedVerification</em>
as <strong>TRUE</strong>. The return code should be
<strong>EFI_SUCCESS</strong></td>
</tr>
</tbody>
</table>



### OutputString()

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
<td>5.6.2.2.1</td>
<td>0x3e706c2f, 0xc7ee, 0x43de, 0x8f, 0xe7, 0x39, 0x81, 0x33, 0x11,
0x7d, 0x9b</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with normal Unicode String. Cursor value in Mode
should be assigned to the right position.</td>
<td><p>1. Call <strong>OutputString()</strong> with normal Unicode
String.</p>
<p>2. Check cursor position. It should be at the end of the string. In
addition, other attributes of output mode remain unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.2.2</td>
<td>0xb7c77060, 0xbd1e, 0x4607, 0x85, 0x41, 0xdc, 0xf5, 0x08, 0xe3,
0xff, 0xd4</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with normal Unicode string returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>OutputString()</strong> with normal Unicode String.
The return code should be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.6.2.2.3</td>
<td>0xf3f07bdb, 0x683d, 0x448f, 0xa5, 0x4a, 0xb5, 0x61, 0xf9, 0x86,
0x95, 0xb5</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with very long Unicode String. Cursor value in
Mode should be assigned to the right position.</td>
<td><p>1. Call <strong>OutputString()</strong> with very long Unicode
String.</p>
<p>2. Check cursor position. It should be at the end of the string. In
addition, other attributes of output mode remain unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.2.4</td>
<td>0xcefd060c, 0x9ed5, 0x4862, 0x96, 0x75, 0xda, 0x26, 0x3b, 0xdc,
0x35, 0x3a</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with very long Unicode String returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>OutputString()</strong> with very long Unicode
String. The return code should be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.6.2.2.5</td>
<td>0x722925c0, 0xf84a, 0x4aa0, 0x9d, 0xe8, 0x04, 0x03, 0x70, 0xe0,
0x69, 0x0f</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with cursor control Unicode String. Cursor value
in Mode should be assigned to the right position.</td>
<td><p>1. Call <strong>OutputString()</strong> with Drawing Unicode
String.</p>
<p>2. Check cursor position. It should be at the end of the string. In
addition, other attributes of output mode remain unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.2.6</td>
<td>0x6fce5c66, 0xd273, 0x446d, 0x88, 0x54, 0x94, 0x7b, 0x6c, 0xd4,
0xa3, 0x96</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with Drawing Unicode String returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>OutputString()</strong> with Drawing Unicode String.
The return code should be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.6.2.2.7</td>
<td>0xae266668, 0xa3ef, 0x4930, 0x85, 0x64, 0x55, 0x9f, 0x9e, 0x96,
0x14, 0x6b</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with cursor control Unicode String. Cursor value
in Mode should be assigned to the right position.</td>
<td><p>1. Call <strong>OutputString()</strong> with cursor control
Unicode String.</p>
<p>2. Check cursor position. It should be at the appointed postion. In
addition, other attributes of output mode remain unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.2.8</td>
<td>0x2e40bcfe, 0x7713, 0x4ab1, 0x99, 0x5c, 0xe0, 0x8b, 0x2d, 0xdc,
0x2b, 0x60</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.OutputString –
OutputString()</strong> with cursor control Unicode String returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>OutputString()</strong> with cursor control Unicode
String. The return code should be <strong>EFI_SUCCESS</strong></td>
</tr>
</tbody>
</table>


### TestString()

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
<td>5.6.2.3.1</td>
<td>0x0317202b, 0x4c09, 0x4f09, 0xa8, 0x9e, 0x17, 0x91, 0x7d, 0x0b,
0xb5, 0x6c</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.TestString –
TestString()</strong> with cursor control Unicode String. Cursor value
in Mode should be assigned to the right position.</td>
<td><p>1. Call <strong>TestString()</strong> with normal Unicode
String.</p>
<p>2. Check cursor position. It should be at the end of the string. In
addition, other attributes of output mode remain unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.3.2</td>
<td>0x92609750, 0x7965, 0x4e08, 0xae, 0xaf, 0xb1, 0xec, 0xa3, 0x61,
0x63, 0x66</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.TestString –
TestString()</strong> with normal Unicode string returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>TestString()</strong> with normal Unicode String
Mode value. The return code should be <strong>EFI_SUCCESS</strong></td>
</tr>
</tbody>
</table>


### QueryMode()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.2.4.1 | 0x26d95327, 0x008c, 0x4ca1, 0xb6, 0x75, 0x9d, 0x86, 0x20, 0xdf, 0x73, 0x19 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode – QueryMode()** with supported *ModeNumber* value remains other attributes unchanged | 1\. Call **QueryMode()** with supported *ModeNumber* value. Other attributes should remain unchanged. |
| 5.6.2.4.2 | 0xf2b8054e, 0xcfa7, 0x4fcd, 0x9e, 0x6c, 0xc6, 0x07, 0xbe, 0x62, 0xff, 0x27 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode – QueryMode()** with supported *ModeNumber* value returns **EFI_SUCCESS** | 1\. Call **QueryMode()** with supported *ModeNumber* value. The return code should be **EFI_SUCCESS** |
| 5.6.2.4.3 | 0x4b5c620e, 0x0e2f, 0x4c19, 0xa2, 0x41, 0x25, 0xbd, 0x47, 0x67, 0xbf, 0x3e | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode – QueryMode()** with unsupported *ModeNumber* value returns **EFI_UNSUPPORTED** | 1\. Call **QueryMode()** with each *ModeNumber* value less than **MaxMode**. If *ModeNumber* \#1 (80\*50) is unsupported, the return code should be **EFI_UNSUPPORTED** |
| 5.6.2.4.4 | 0x5c444cd8, 0x3dce, 0x4be7, 0xb5, 0xcd, 0x39, 0x38, 0xd5, 0x04, 0xac, 0x95 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode** – *ModeNumber* \#0 is supported and the dimension is 80 \* 25 | 1\. Call **QueryMode()** with each **Mode** value less than **MaxMode**. *ModeNumber* \#0 should be supported and the dimension is 80 \* 25 |
| 5.6.2.4.5 | 0x3b069c23, 0xde80, 0x4eb9, 0x86, 0x57, 0x48, 0x0f, 0x63, 0x81, 0x6c, 0x53 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode** – If *ModeNumber* \#1 is supported, the dimension is 80 \* 50 | 1\. Call **QueryMode()** with each *ModeNumber* value less than **MaxMode**. If *ModeNumber* \#1 is supported, the dimension should be 80 \* 50 |
| 5.6.2.4.6 | 0x891cb899, 0xc05e, 0x4160, 0xa9, 0x8c, 0x06, 0x04, 0xc4, 0x0a, 0x44, 0x48 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode – QueryMode()** with Invalid *ModeNumber* Fields, **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode** does not change before and after | 1\. Call **QueryMode()** with Invalid Mode Fields beyond **MaxMode**. **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode** should not change before and after |
| 5.6.2.4.7 | 0x8f0b6ebe, 0xaa65, 0x4aa4, 0x8c, 0xfc, 0x22, 0x08, 0x74, 0xe7, 0x95, 0x63 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.QueryMode – QueryMode()** with Invalid Mode Fields returns **EFI_UNSUPPORTED** | 1\. Call **QueryMode()** with Invalid Mode Fields beyond **MaxMode**. The return code should be **EFI_UNSUPPORTED** |



### SetMode()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.2.5.1 | 0x3680c8c3, 0x8fc6, 0x4fe2, 0xa2, 0xdb, 0x4f, 0xcb, 0xe1, 0x0a, 0x14, 0x87 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode – SetMode()** with supported *ModeNumber* value sets mode and cursor postion | 1\. Call **SetMode()** with supported *ModeNumber* value. Cursor position should be set to (0,0). Current mode should be the appointed mode. Other attributes should remain unchanged. |
| 5.6.2.5.2 | 0xcb1c6bc5, 0x6c12, 0x4d3a, 0x91, 0xc4, 0x2e, 0xdb, 0x09, 0xa3, 0x5d, 0x5f | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode – SetMode()** with supported *ModeNumber* value returns **EFI_SUCCESS** | 1\. Call **SetMode()** with supported *ModeNumber* value. The return code should be **EFI_SUCCESS** |
| 5.6.2.5.3 | 0xab044f50, 0xd0d3, 0x44f5, 0x92, 0x34, 0xe0, 0x52, 0xcc, 0x26, 0x47, 0x89 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode – SetMode()** with Invalid Mode Fields, **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode** does not change before and after | 1\. Call **SetMode()** with Invalid Mode Fields beyond **MaxMode**. **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode** should not change before and after |
| 5.6.2.5.4 | 0x6ce26a46, 0xab4a, 0x44df, 0x86, 0xc0, 0x3a, 0x97, 0xc3, 0xa3, 0x93, 0x0f | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetMode – SetMode()** with Invalid Mode Fields returns **EFI_UNSUPPORTED** | 1\. **SetMode()** with Invalid Mode Fields beyond **MaxMode**. The return code should be **EFI_UNSUPPORTED**. |



### SetAttribute()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.2.6.1 | 0xb401e101, 0x5386, 0x49fc, 0x89, 0x64, 0x54, 0x3b, 0xad, 0x90, 0x7b, 0x58 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** with supported attributes returns **EFI_SUCCESS** | 1\. Call **SetAttribute()** with supported attributes. The return code should be **EFI_SUCCESS**. |
| 5.6.2.6.2 | 0x49b1f9ea, 0x085c, 0x4b2b, 0xa8, 0x98, 0x75, 0x6a, 0xa7, 0x61, 0x2f, 0x4a | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** should return **EFI_SUCCESS** with valid attributes | 1\. Check return status of **SetAttribute()**with valid attribute to set foreground color |
| 5.6.2.6.3 | 0xefa8f25f, 0x60fe, 0x4707, 0x9f,0x2b, 0x66, 0x12, 0xf6, 0x4d, 0x3f, 0x6e | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** changes output color and remains other mode fields unchanged | 1\. Check all the fields of output mode. The background color and foreground color should be set as appointed value, and other fields should not be changed. |
| 5.6.2.6.4 | 0x3af1e31e, 0x1523, 0x4ad3, 0xa0, 0x77, 0x51, 0xd2, 0x32, 0x8e, 0xdf, 0x80 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** with supported attributes returns **EFI_SUCCESS** and output color is set as expected | 1\. After the multiple calls of **SetAttribute()**, check all the return codes and changes in output mode fields. |
| 5.6.2.6.5 | 0x42c6876b, 0x46e7, 0x47a5, 0xb4, 0x27, 0x25, 0x06, 0x1e, 0x25, 0xe8, 0xbf | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** with Invalid Attribute values, does not change **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode**. | 1\. Call **SetAttribute()** with Invalid Attribute values. **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.Mode** should not be changed |
| 5.6.2.6.6 | 0x300a1814, 0xd2c8, 0x4a51, 0xa9, 0x37, 0x0b, 0x8c, 0xe9, 0x3f, 0xb4, 0x45 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetAttribute – SetAttribute()** with Invalid Attribute values returns **EFI_UNSUPPORTED** | 1\. Call **SetAttribute()** with Invalid Attribute values. The return code should be **EFI_UNSUPPORTED**. |


### ClearScreen()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.2.7.1 | 0xa92ce5f8, 0x89a8, 0x4695, 0xbc, 0xb1, 0x59, 0x3e, 0x0e, 0x88, 0xe2, 0x41 | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.ClearScreen – ClearScreen()** sets cursor position to (0,0) and remain other attributes unchanged. | 1\. Call **ClearScreen()** in all supported modes. The cursor position should be set to (0,0), and other attributes of output should not be changed. |
| 5.6.2.7.2 | 0xb3a0092f, 0xe768, 0x4359, 0xa9, 0xeb, 0x3d, 0x85, 0x27, 0x78, 0xc4, 0xcb | **EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.ClearScreen – ClearScreen()** returns **EFI_SUCCESS**. | 1\. Call **ClearScreen()** in all supported modes. The return code should be **EFI_SUCCESS**. |



### SetCursorPosition()

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
<td>5.6.2.8.1</td>
<td>0xe4f9fd56, 0x1e72, 0x44ee, 0xb0, 0x31, 0xae, 0xc6, 0xb4, 0xda,
0xb2, 0x0d</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition –
SetCursorPosition()</strong> moves cursor to appointed position and
remain other attributes unchanged.</td>
<td>1. Call <strong>SetCursorPosition()</strong> in all supported modes
to move cursor to every valid position within dimension boundary. The
cursor position should be set to appointed value, and other attributes
of output should not be changed.</td>
</tr>
<tr class="odd">
<td>5.6.2.8.2</td>
<td>0xbe56dc0d, 0x8779, 0x4700, 0xb4, 0x4c, 0x6d, 0xf4, 0x39, 0xfb,
0xf6, 0xaa</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition –
SetCursorPosition()</strong> returns <strong>EFI_SUCCESS</strong>.</td>
<td>1. Call <strong>SetCursorPosition()</strong> in all supported modes
to move cursor to every valid position within dimension boundary. The
return code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.6.2.8.3</td>
<td>0xa125b94f, 0xcbc6, 0x4e25, 0x80, 0x33, 0xfb, 0xf0, 0xde, 0x73,
0x14, 0x65</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition –
SetCursorPosition()</strong> returns <strong>EFI_SUCCESS</strong> and
moves cursor to appointed position.</td>
<td><p>1. Call <strong>SetCursorPosition()</strong> in all supported
modes to move cursor to every valid position within dimension
boundary.</p>
<p>2. Check return code and behavior of each call.</p></td>
</tr>
<tr class="odd">
<td>5.6.2.8.4</td>
<td>0x85e9aabd, 0x1376, 0x4e67, 0xb6, 0x14, 0xce, 0xcf, 0x63, 0x36,
0x9b, 0x31</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition –
SetCursorPosition()</strong> with Invalid Row/Column Numbers does not
change cursor position.</td>
<td>1. Call <strong>SetCursorPosition()</strong> with Invalid Row/Column
Numbers. Mode-&gt;<strong>CursorColumn</strong> /
<strong>CursorRow</strong> should remain unchanged.</td>
</tr>
<tr class="even">
<td>5.6.2.8.5</td>
<td>0xbeff2f08, 0xbc3e, 0x4e4f, 0xb8, 0x6f, 0x05, 0xb0, 0xe9, 0xd1,
0x0b, 0xa3</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.SetCursorPosition –
SetCursorPosition()</strong> with Invalid Row/Column Numbers returns
<strong>EFI_UNSUPPORTED</strong>.</td>
<td>1. Call <strong>SetCursorPosition()</strong> with Invalid Row/Column
Numbers. The return code should be
<strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
</tbody>
</table>



### EnableCursor()

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
<td>5.6.2.9.1</td>
<td>0xdf85a087, 0xd1c9, 0x4739, 0x97, 0x2c, 0x4e, 0xd8, 0x61, 0x5f,
0x56, 0xd4</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>TRUE</strong> returns
<strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong></td>
<td>1. Call <strong>EnableCursor()</strong> with <strong>TRUE</strong>.
If <strong>EnableCursor()</strong> is unsupported, the return code
should be <strong>EFI_UNSUPPORTED</strong></td>
</tr>
<tr class="odd">
<td>5.6.2.9.2</td>
<td>0x318fe413, 0xd07d, 0x4aad, 0x9c, 0x62, 0xf8, 0xfe, 0x7f, 0x77,
0xbe, 0xb2</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>TRUE</strong> changes cursor status
to visible.</td>
<td><p>1. Call <strong>EnableCursor()</strong> with
<strong>TRUE</strong>.</p>
<p>2. If <strong>EnableCursor()</strong> success,
<strong>CursorVisible</strong> should be <strong>TRUE</strong></p></td>
</tr>
<tr class="even">
<td>5.6.2.9.3</td>
<td>0x07394e57, 0xf2f5, 0x4045, 0x8b, 0x2c, 0x91, 0xbb, 0x2b, 0xe4,
0x3c, 0x4e</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>TRUE</strong> returns
<strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong></td>
<td>1. Call <strong>EnableCursor()</strong> with <strong>TRUE</strong>.
If <strong>EnableCursor()</strong> is supported. The return code should
be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="odd">
<td>5.6.2.9.4</td>
<td>0xb3121d1b, 0xbd25, 0x477d, 0xad, 0xc3, 0x5d, 0xe3, 0x1b, 0x19,
0x43, 0x25</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>FALSE</strong> returns
<strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong></td>
<td>1. Call <strong>EnableCursor()</strong> with <strong>FALSE</strong>.
If <strong>EnableCursor()</strong> is unsupported, the return code
should be <strong>EFI_UNSUPPORTED</strong></td>
</tr>
<tr class="even">
<td>5.6.2.9.5</td>
<td>0xcfd7fe8d, 0x1674, 0x4205, 0xb6, 0x3a, 0xe6, 0x4e, 0x86, 0x15,
0x66, 0x0c</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>FALSE</strong> changes cursor
status to invisible.</td>
<td><p>1. Call <strong>EnableCursor()</strong> with
<strong>FALSE</strong>.</p>
<p>2. If <strong>EnableCursor()</strong> success, <em>CursorVisible</em>
should be <strong>FALSE</strong></p></td>
</tr>
<tr class="odd">
<td>5.6.2.9.6</td>
<td>0x3f2b2512, 0x91cf, 0x44d9, 0xae, 0xbd, 0x89, 0x76, 0x40, 0xf1,
0xb4, 0x1f</td>
<td><strong>EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL.EnableCursor –
EnableCursor()</strong> with <strong>FALSE</strong> returns
<strong>EFI_SUCCESS</strong> or <strong>EFI_UNSUPPORTED</strong></td>
<td>1. Call <strong>EnableCursor()</strong> with <strong>FALSE</strong>.
If <strong>EnableCursor()</strong> is supported. The return code should
be <strong>EFI_SUCCESS</strong></td>
</tr>
</tbody>
</table>


## EFI_SIMPLE_POINTER_PROTOCOL_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_SIMPLE_POINTER_PROTOCOL Section.

### Reset()

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
<td>5.6.4.1.1</td>
<td>0x3fcb89c6, 0xe504, 0x4669, 0xbf, 0x31, 0xba, 0x03, 0xb7, 0x66,
0xc8, 0xc2</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong> returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>. The
return code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.4.1.2</td>
<td>0xd752813f, 0x32dc, 0x4820, 0xb7, 0x59, 0xe8, 0x97, 0x0c, 0xf3,
0x33, 0x89</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset()</strong> returns 0 for all related movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. If success,
<em>RelativeMovementX, RelativeMovementY</em> and
<em>RelativeMovementZ</em> should be 0.</p></td>
</tr>
<tr class="even">
<td>5.6.4.1.3</td>
<td>0x716eefc7, 0x8c0a, 0x4636, 0xa0, 0xdb, 0x7e, 0x70, 0x20, 0xce,
0xe8, 0x5d</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset()</strong> returns
<strong>EFI_UNSUPPORTED</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. The return code maybe
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.6.4.1.4</td>
<td>0xce6806f5, 0xe186, 0x4c24, 0x83, 0xaa, 0x00, 0x4f, 0xac, 0xf0,
0x28, 0x65</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong> returns
<strong>EFI_SUCCESS</strong></td>
<td>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>. The return
code should be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.6.4.1.5</td>
<td>0xd3e54374, 0x17b6, 0x417b, 0xae, 0xc7, 0xcc, 0x55, 0xcc, 0x42,
0x35, 0xa2</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset()</strong> returns 0 for all related movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. If success,
<em>RelativeMovementX, RelativeMovementY</em> and
<em>RelativeMovementZ</em> should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.4.1.6</td>
<td>0xd8a03978, 0x7023, 0x4d61, 0x92, 0xbd, 0x15, 0xd3, 0x9b, 0x3f,
0x5d, 0x11</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset()</strong> returns
<strong>EFI_UNSUPPORTED</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. The return code maybe
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### GetState()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 15%" />
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
<td>5.6.4.2.1</td>
<td>0x5271062e, 0xdef9, 0x4d30, 0x84, 0x3b, 0x8d, 0x6e, 0x41, 0x33,
0x13, 0xf3</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.GetState - GetState()</strong>
after <strong>Reset()</strong> returns 0 for all related movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. If success,
<em>RelativeMovementX, RelativeMovementY</em> and
<em>RelativeMovementZ</em> should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.4.2.2</td>
<td>0x7614c447, 0x12a0, 0x403d, 0x8a, 0xde, 0x98, 0x97, 0x51, 0x7d,
0xd8, 0x49</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.GetState - GetState()</strong>
returns <strong>EFI_NOT_READY</strong> when there is no move since last
call of <strong>GetState()</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>.</p>
<p>3. Call <strong>GetState()</strong> again, the return code should be
<strong>EFI_NOT_READY</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.4.2.3</td>
<td>0x2f8f8710, 0x02dd, 0x411f, 0xaa, 0xb5, 0x27, 0xe1, 0x3a, 0x6a,
0xb2, 0x79</td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.GetState - GetState()</strong>
after <strong>Reset()</strong> returns 0 for all related movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. If success,
<em>RelativeMovementX, RelativeMovementY</em> and
<em>RelativeMovementZ</em> should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.4.2.4</td>
<td><p>0x3db7ea18,0xda9d,</p>
<p>0x4760,</p>
<p>0xa7,0x43,</p>
<p>0x04,0xb4,</p>
<p>0x8d,0x14,</p>
<p>0x4e,0x90</p></td>
<td><strong>EFI_SIMPLE_POINTER_PROTOCOL.GetState - GetState()</strong>
returns <strong>EFI_NOT_READY</strong> when there is no move since last
call of <strong>GetState()</strong>.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>.</p>
<p>3. Call <strong>GetState()</strong> again, the return code should be
<strong>EFI_NOT_READY</strong>.</p></td>
</tr>
</tbody>
</table>


## EFI_SERIAL_IO_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_SERIAL_IO_PROTOCOL Section.

### Reset()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.5.1.1 | 0x2e369256, 0x6c78, 0x49e9, 0x9e, 0xd5, 0xe3, 0xd2, 0x88, 0x34, 0x33, 0xa0 | EFI_SERIAL_IO_PROTOCOL .Reset - Reset() returns **EFI_SUCCESS**. | 1\. Call Reset(). The return code should be **EFI_SUCCESS**. |



### SetAttributes()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.5.2.1 | 0x34260cb2, 0x43ae, 0x4853, 0x87, 0x4b, 0x47, 0x7c, 0xeb, 0x14, 0x42, 0x02 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *BaudRate* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *BaudRate*. The return code should be **EFI_SUCCESS** and the *BaudRate* field of **Mode** should be equal to the set value. |
| 5.6.5.2.2 | 0x3fd35bee, 0x5013, 0x472f, 0xa0, 0x08, 0xbd, 0xdf, 0x31, 0x9c, 0xe6, 0x6b | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *ReceiveFifoDepth* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *ReceiveFifoDepth*. The return code should be **EFI_SUCCESS** and the *ReceiveFifoDepth* field of *Mode* should be equal to the set value. |
| 5.6.5.2.3 | 0x8cf74222, 0x7134, 0x47b6, 0xa5, 0x82, 0xf4, 0xd9, 0xad, 0xa7, 0xa3, 0xf4 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *Timeout* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *Timeout*. The return code should be **EFI_SUCCESS** and the *Timeout* field of *Mode* should be equal to the set value. |
| 5.6.5.2.4 | 0x68f91273, 0x0078, 0x4e6c, 0xb9, 0xdb, 0x62, 0x59, 0xb5, 0x39, 0xf7, 0x4a | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *Parity* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *Parity*. The return code should be **EFI_SUCCESS** and the *Parity* field of *Mode* should be equal to the set value. |
| 5.6.5.2.5 | 0xdf6038c2, 0x3752, 0x4e22, 0xab, 0x4c, 0xfe, 0x66, 0x67, 0x0c, 0xa3, 0xdf | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *DataBits* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *DataBits*. The return code should be **EFI_SUCCESS** and the *DataBits* field of *Mode* should be equal to the set value. |
| 5.6.5.2.6 | 0xdf6f2692, 0x9a0d, 0x4b0f, 0xbc, 0x8e, 0x36, 0x8b, 0x6a, 0x03, 0xe0, 0xb1 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with valid *StopBits* returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with various valid *StopBits*. The return code should be **EFI_SUCCESS** and the *StopBits* field of *Mode* should be equal to the set value. |
| 5.6.5.2.7 | 0xb199d5d2, 0x1143, 0x499e, 0xa5, 0xf8, 0xf0, 0xa7, 0x6f, 0x79, 0xfe, 0xe5 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with default attributes returns **EFI_SUCCESS**. | 1\. Call **SetAttributes()** with default attributes: *BaudRate*=115200; FifoDepth=1; *Timeout*=1000000; *Parity*=**NoParity**; *DataBits*=8; *StopBits*=**OneStopBit**; The return code should be **EFI_SUCCESS** |
| 5.6.5.2.8 | 0x3041ec45, 0x00af, 0x4787, 0xb1, 0xe9, 0x15, 0xb8, 0x7a, 0xc5, 0xdd, 0xc8 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with nonstandard *BaudRate* values returns **EFI_SUCCESS** and set *BaudRate* as the nearest standard baud rate value. | 1\. Call **SetAttributes()** with nonstandard *BaudRate* values. The return code should be **EFI_SUCCESS** and the *BaudRate* field of *Mode* should be equal to the nearest standard baud rate value. |
| 5.6.5.2.9 | 0x7a5cca70, 0x46c7, 0x4488, 0x87, 0x65, 0x84, 0x33, 0x66, 0x78, 0xa5, 0x01 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *BaudRate* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *BaudRate*. The return code should be **EFI_INVALID_PARAMETER**. |
| 5.6.5.2.10 | 0x190ca14d, 0xa6c2, 0x4a42, 0x86, 0x29, 0xa5, 0x14, 0x96, 0xc8, 0xe0, 0x52 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *ReceiveFifoDepth* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *ReceiveFifoDepth*. The return code should be **EFI_INVALID_PARAMETER**. |
| 5.6.5.2.11 | 0xd40c796b, 0xb654, 0x4fb5, 0x88, 0xb0, 0x1e, 0xc8, 0x2a, 0x27, 0x13, 0x50 | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *Timeout* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *Timeout*. The return code should be **EFI_INVALID_PARAMETER**. |
| 5.6.5.2.12 | 0x15dc5ee1, 0x9871, 0x4e25, 0xb2, 0x22, 0xc5, 0x38, 0x5c, 0x9b, 0xf3, 0x6b | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *Parity* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *Parity*. The return code should be **EFI_INVALID_PARAMETER**. |
| 5.6.5.2.13 | 0x0aa15e38, 0xb05c, 0x46cf, 0xb1, 0xf3, 0x1e, 0xb7, 0x41, 0x37, 0xb8, 0xbf | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *DataBits* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *DataBits*. The return code should be **EFI_INVALID_PARAMETER**. |
| 5.6.5.2.14 | 0x174a5c87, 0x74cf, 0x4e88, 0x84, 0x04, 0x68, 0x3e, 0xcb, 0x40, 0xf3, 0x2f | **EFI_SERIAL_IO_PROTOCOL .SetAttributes - SetAttributes()** with unsupported *StopBits* returns **EFI_INVALID_PARAMETER**. | 1\. Call **SetAttributes()** with unsupported *StopBits*. The return code should be **EFI_INVALID_PARAMETER**. |


### SetControl()

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
<td>5.6.5.3.1</td>
<td>0xac56dfb5, 0xce1c, 0x42a6, 0x98, 0xc9, 0xc6, 0xf5, 0xc8, 0xad,
0x83, 0xda</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .SetControl - SetControl()</strong>
with valid bits returns <strong>EFI_SUCCESS</strong> and
<strong>GetControl()</strong> returns the set bits.</td>
<td><p>1. Call <strong>SetControl()</strong> with valid control bits.
The return code should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>GetControl()</strong>. The valid control bits should
be set.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.3.2</td>
<td>0x00605cbc, 0x3965, 0x4b61, 0xa2, 0x54, 0x2b, 0x2b, 0x72, 0x31,
0x72, 0xea</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .SetControl - SetControl()</strong>
with unsupported control bits returns
<strong>EFI_UNSUPPORTED</strong>.</td>
<td>1. Call <strong>SetControl()</strong> with unsupported control bits.
The return code should be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
</tbody>
</table>



### GetControl()

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
<td>5.6.5.4.1</td>
<td>0x131f5894, 0x1613, 0x4f3e, 0xbd, 0x45, 0x2b, 0xdd, 0xb7, 0xed,
0x22, 0xb0</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .GetControl - GetControl()</strong>
returns <strong>EFI_SUCCESS</strong> and gets the bits set by
<strong>SetControl()</strong>.</td>
<td><p>1. Call <strong>SetControl()</strong> with valid control
bits.</p>
<p>2. Call <strong>GetControl()</strong>.The return code should be
<strong>EFI_SUCCESS</strong> and the valid control bits should be
returned.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.4.2</td>
<td>0xdd059dc5, 0x6558, 0x4d43, 0xac, 0x65, 0x58, 0xa6, 0x1d, 0x64,
0x8d, 0xb0</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .GetControl - GetControl()</strong>
returns <strong>EFI_SUCCESS</strong> and gets the bit of
<strong>EFI_SERIAL_INPUT_BUFFER_EMPTY</strong> after buffer contents are
read out.</td>
<td><p>1. Call <strong>Read()</strong> to read out buffer contents.</p>
<p>2. Call <strong>GetControl()</strong>.The return code should be
<strong>EFI_SUCCESS</strong> and
<strong>EFI_SERIAL_INPUT_BUFFER_EMPTY</strong> is set.</p></td>
</tr>
</tbody>
</table>


### Write()

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
<td>5.6.5.5.1</td>
<td>0x72c50358, 0xc760, 0x4200, 0x8d, 0xb2, 0x09, 0x4d, 0x96, 0x84,
0x6f, 0x1a</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Write - Write()</strong> in
software-loopback mode returns <strong>EFI_SUCCESS</strong> and
<strong>Read()</strong> gets the same contents.</td>
<td><p>1. Call <strong>Write()</strong> in software-loopback mode. The
return code should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>Read()</strong> to get buffer. It should return the
written contents.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.5.2</td>
<td>0x688bf990, 0xfd8f, 0x430e, 0x8e, 0x1c, 0x78, 0x07, 0x2d, 0x74,
0xbd, 0x08</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Write - Write()</strong> in
hardware-loopback mode returns <strong>EFI_SUCCESS</strong> and
<strong>Read()</strong> gets the same contents.</td>
<td><p>1. Call <strong>Write()</strong> in hardware-loopback mode. The
return code should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>Read()</strong> to get buffer. It should return the
written contents.</p></td>
</tr>
<tr class="even">
<td>5.6.5.5.3</td>
<td>0x198873b8, 0xe8f2, 0x4bfd, 0xa0, 0x20, 0x36, 0xff, 0xb4, 0x93,
0x72, 0x02</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Write - Write()</strong> in
non-loopback mode returns <strong>EFI_SUCCESS</strong>.</td>
<td>1. Call <strong>Write()</strong> in non-loopback mode. The return
code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>



### Read()

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
<td>5.6.5.6.1</td>
<td>0x8ad0312f, 0x4cfc, 0x4611, 0xb7, 0x62, 0x85, 0x3a, 0xa3, 0x9d,
0x2f, 0xd9</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
software-loopback mode returns <strong>EFI_SUCCESS</strong> and gets the
same contents written.</td>
<td><p>1. Call <strong>Write()</strong> in software-loopback mode.</p>
<p>2. Call <strong>Read()</strong> in software-loopback to get buffer.
It should return the written contents. The return code should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.6.2</td>
<td>0x76cb227f, 0x312d, 0x4476, 0x8c, 0x59, 0x6a, 0x98, 0x27, 0x5b,
0x62, 0x3d</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
hardware-loopback mode returns <strong>EFI_SUCCESS</strong> and gets the
same contents written.</td>
<td><p>1. Call <strong>Write()</strong> in hardware-loopback mode.</p>
<p>2. Call <strong>Read()</strong> in hardware-loopback to get buffer.
It should return the written contents. The return code should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.5.6.3</td>
<td>0x3faefba1, 0x4049, 0x4868, 0x8f, 0x34, 0x59, 0xaf, 0x3e, 0x62,
0xdf, 0xb0</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
hardware-loopback mode without any characters in buffer returns
<strong>EFI_TIME_OUT</strong> and set buffer size to 0.</td>
<td><p>1. Call <strong>Read()</strong> to read out all contents in
buffer.</p>
<p>2. Call <strong>Read()</strong> again, the return code should be
<strong>EFI_TIME_OUT</strong> and <em>BufferSize</em> should be
0.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.6.4</td>
<td>0xc96db50e, 0xd269, 0x4fb0, 0x88, 0xbd, 0x6a, 0x02, 0x06, 0x66,
0x53, 0xa7</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
hardware-loopback mode with <em>BufferSize</em>=2 returns
<strong>EFI_TIME_OUT</strong> when there is only 1 byte contents in
serial buffer.</td>
<td><p>1. Call <strong>Read()</strong> to read out all contents in
buffer.</p>
<p>2. Call <strong>Write()</strong> to write 1 byte into serial
buffer.</p>
<p>3. Call <strong>Read()</strong> again with <em>BufferSize</em> = 2.
The return code should be <strong>EFI_TIME_OUT</strong>,
<em>BufferSize</em> should be 1 and 1 byte should be read.</p></td>
</tr>
<tr class="even">
<td>5.6.5.6.5</td>
<td>0xb636572b, 0x7aaa, 0x4146, 0x8d, 0xd4, 0x18, 0xef, 0xac, 0xb4,
0x8a, 0x1a</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
software-loopback mode without any characters in buffer returns
<strong>EFI_TIME_OUT</strong> and set buffer size to 0.</td>
<td><p>1. Call <strong>Read()</strong> to read out all contents in
buffer.</p>
<p>2. Call <strong>Read()</strong> again, the return code should be
<strong>EFI_TIME_OUT</strong> and <em>BufferSize</em> should be
0.</p></td>
</tr>
<tr class="odd">
<td>5.6.5.6.6</td>
<td>0x48050436, 0xc835, 0x4a24, 0x87, 0x75, 0x4d, 0x2e, 0x47, 0x88,
0xb5, 0x97</td>
<td><strong>EFI_SERIAL_IO_PROTOCOL .Read - Read()</strong> in
software-loopback mode with <em>BufferSize</em>=2 returns
<strong>EFI_TIME_OUT</strong> when there is only 1 byte contents in
serial buffer.</td>
<td><p>1. Call <strong>Read()</strong> to read out all contents in
buffer.</p>
<p>2. Call <strong>Write()</strong> to write 1 byte into serial
buffer.</p>
<p>3. Call <strong>Read()</strong> again with <em>BufferSize</em> = 2.
The return code should be <strong>EFI_TIME_OUT</strong>,
<em>BufferSize</em> should be 1 and 1 byte should be read.</p></td>
</tr>
</tbody>
</table>


## EFI_GRAPHICS_OUTPUT_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_GRAPHICS_OUTPUT_PROTOCOL Section.

### QueryMode()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 20%" />
<col style="width: 23%" />
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
<td>5.6.6.1.1</td>
<td>0xd1824539, 0x92cd, 0x434c, 0x81, 0x65, 0x87, 0x2c, 0xc2, 0x1a,
0x5f, 0x9e</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameter.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>SetMode()</strong> to switch the video device to the
specified mode.</p>
<p>•Call <strong>QueryMode()</strong> with the current mode to get the
current info structure and check the content of Info.</p>
<p>The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>For <em>PixelBlueGreenRedReserved8BitPerColor</em> or
<em>PixelRedGreenBlueReserved8BitPerColor</em>, the
<em>FrameBufferSize</em> should be <em>PixelsPerScanLine</em> *
<em>VerticalResolution</em> * <em>PixelElementSize</em>.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.1.2</td>
<td>0x82dfd41e, 0x49db, 0x4c86, 0x99, 0xbb, 0xc5, 0x74, 0x33, 0x4b,
0xa0, 0xc3</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> Call
<strong>QueryMode()</strong> with <em>MaxMode</em>.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an Info value of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value except
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL.</strong></p></td>
</tr>
<tr class="even">
<td>5.6.6.1.3</td>
<td>0x8ebcd9ab, 0x69a9, 0x48a2, 0x9b, 0xbc, 0x8c, 0x47, 0x9e, 0x68,
0x91, 0x56</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> Call
<strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an Info <em>value</em> of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value except
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL</strong></p></td>
</tr>
<tr class="odd">
<td>5.6.6.1.4</td>
<td>0x394e306b, 0x652a, 0x403a, 0xbd, 0x15, 0xdb, 0x9b, 0x46, 0xc3,
0x44, 0x3b</td>
<td><strong>ConsoleContro. QueryMode –</strong> Call
<strong>QueryMode()</strong> with an <em>Info</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an <em>Info</em> value of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value but
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL</strong></p></td>
</tr>
<tr class="even">
<td>5.6.6.1.5</td>
<td>0xe7782dc5, 0x2b78, 0x460f, 0xb1, 0x02, 0x88, 0xd5, 0x12, 0x06,
0x45, 0x1f</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> Call
<strong>QueryMode()</strong> with a valid <em>ModeNumber</em>. The
returned status should be <strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an <em>Info</em> value of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value except
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL</strong></p></td>
</tr>
<tr class="odd">
<td>5.6.6.1.6</td>
<td>0x486360f1, 0x6b8e, 0x48b5, 0x8b, 0xa8, 0xae, 0x40, 0xeb, 0x3b,
0x07, 0xa2</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> Call
<strong>QueryMode()</strong> with with valid parameters.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an <em>Info</em> value of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value except
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL</strong></p></td>
</tr>
<tr class="even">
<td>5.6.6.1.7</td>
<td>0xdc19ab69, 0x764e, 0x429b, 0xa5, 0x3f, 0xb8, 0x1e, 0xd6, 0x3c,
0xd6, 0xc0</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. QueryMode –</strong> Call
<strong>QueryMode()</strong>to Check the mode structure and dump
it.</td>
<td><p>1. Call <strong>QueryMode()</strong> with <em>MaxMode</em>. The
returned status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>2. Call <strong>QueryMode()</strong> with a <em>SizeOfInfo</em> value
of <strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call <strong>QueryMode()</strong> with an <em>Info</em> value of
<strong>NULL</strong>. The returned status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>QueryMode()</strong> with the specified mode number.
The returned status should be any value except
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>•The called allocated buffer that the Info points to should not be
<strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>



### SetMode()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
<col style="width: 23%" />
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
<td>5.6.6.2.1</td>
<td>0xb3a4939b, 0xd00a, 0x4da7, 0xaf, 0x6d, 0xf3, 0xee, 0xcb, 0xf9,
0x99, 0x0c</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. SetMode –SetMode()</strong>
returns <strong>EFI_SUCCESS</strong> when setting the graphics device
and the set of active video output devices to the video mode specified
by <em>ModeNumber</em>.</td>
<td>Call <strong>SetMode()</strong> with valid mode numbers from 0 to
<em>MaxMode</em>-1.The returned status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.6.2.2</td>
<td>0x128e953b, 0xe6ec, 0x4f93, 0xa8, 0xec, 0x72, 0xc5, 0x9b, 0x8a,
0x40, 0x43</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. SetMode –</strong> Call
<strong>SetMode()</strong>with valid <em>ModeNumber</em>.</td>
<td><p>1. For valid graphics mode number from 0 to
<em>MaxMode</em>-1:</p>
<p>•Call <strong>SetMode()</strong> with valid mode, the returned status
should not be <strong>EFI_UNSUPPORTED</strong> and should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>QueryMode()</strong> with the same mode number as
<strong>SetMode()</strong>.</p>
<p>•The Info structure the <strong>QueryMode()</strong> returns and
current mode of graphic device should be the same.</p>
<p>4. Call <strong>SetMode()</strong> with <em>MaxMode</em>. The
returned status should be <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.6.2.3</td>
<td>0x4f13e7ba, 0xb35a, 0x4bf7, 0xb1, 0xc0, 0xfe, 0x39, 0x9c, 0x49,
0x97, 0xfe</td>
<td><p><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. SetMode –</strong>Call
<strong>QueryMode()</strong> with the <em>ModeNumber</em> the
<strong>SetMode()</strong> set , then</p>
<p>compare the Info structure <strong>QueryMode()</strong> returns with
current mode of graphic device in order to verify whether they are same,
and at last dump the Info structure.</p></td>
<td><p>1. For valid graphics mode number from 0 to
<em>MaxMode</em>-1:</p>
<p>•Call <strong>SetMode()</strong> with valid mode, the returned status
should not be <strong>EFI_UNSUPPORTED</strong> and should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>QueryMode()</strong> with the same mode number as
<strong>SetMode()</strong>.</p>
<p>•The Info structure the <strong>QueryMode()</strong> returns and
current mode of graphic device should be the same.</p>
<p>2. Call <strong>SetMode()</strong> with <em>MaxMode</em>. The
returned status should be <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.2.4</td>
<td>0x8776b9dc, 0x711e, 0x4e36, 0x99, 0x21, 0x7e, 0xa7, 0xc4, 0xc7,
0xee, 0x6d</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL. SetMode –</strong> Call
<strong>SetMode()</strong>with valid <em>MaxMode</em>.</td>
<td><p>1. For valid graphics mode number from 0 to
<em>MaxMode</em>-1:</p>
<p>•Call <strong>SetMode()</strong> with valid mode, the returned status
should not be <strong>EFI_UNSUPPORTED</strong> and should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>QueryMode()</strong> with the same mode number as
<strong>SetMode()</strong>.</p>
<p>•The Info structure the <strong>QueryMode()</strong> returns and
current mode of graphic device should be the same.</p>
<p>2. Call <strong>SetMode()</strong> with <em>MaxMode</em>. The
returned status should be <strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>



### Blt()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 16%" />
<col style="width: 22%" />
<col style="width: 46%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.6.6.3.1</td>
<td>0x95a44702, 0xcea0, 0x480f, 0x9f, 0x84, 0xe2, 0x4c, 0x17, 0xbf,
0x47, 0x79</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt – EfiBltVideoFill</strong>
operation should fill graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a BltOperation value of
<em>EfiBltVideoFill</em> to write data from the <em>BltBuffer</em> pixel
(0, 0) directly to every pixel of the video display rectangle
(<em>DestinationX</em>, <em>DestionationY</em>)
(<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to retrieve the rectangles drawn by the
last <em>EfiBltVideoFill</em> operation. All the retrieved rectangles
should be the same pixel used in the last <em>EfiBltVideoFill</em>
operation. If pixels verification passes, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.2</td>
<td>0x699c30b0, 0xab3f, 0x45d9, 0xbd, 0x69, 0x6b, 0x93, 0x96, 0xb7,
0x7e, 0x66</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt – EfiBltVideoFill</strong>
operation should fill graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoFill</em> to write data from the BltBuffer pixel (0, 0)
directly to every pixel of the video display rectangle
(<em>DestinationX</em>, <em>DestionationY</em>) (<em>DestinationX</em>
+<em>Width</em>, <em>DestionationY</em> +<em>Height</em>). The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to retrieve the rectangles drawn by the
last <em>EfiBltVideoFill</em> operation. All the retrieved rectangles
should be the same pixel used in the last <em>EfiBltVideoFill</em>
operation. If pixels verification passes, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.3</td>
<td>0xc34c3fa4, 0xa61e, 0x4598, 0x9f, 0x80, 0x2d, 0xee, 0x8e, 0x2c,
0x9b, 0x57</td>
<td><p><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –
EfiBltBufferToVideo</strong></p>
<p>operation should write data to video screen and
<strong>EfiBltVideoToBltBuffer</strong> operation should read data from
video display rectangle.</p></td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to read data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(SourceX+Width, SourceY+Height) and place it in the BltBuffer
rectangle (DestinationX, DestionationY) (DestionationX+Width,</p>
<p><em>DestionationY</em>+<em>Height</em>). The returned status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to the video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). – Source and Destination
should reverse with that of <strong>EfiBltVideoToBltBuffer</strong>
operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•The <em>BltBuffer</em> and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.4</td>
<td>0x33a341ea, 0xc6a2, 0x4037, 0x8a, 0x2d, 0x19, 0xea, 0x1f, 0xe2,
0xf2, 0xa6</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt – EfiBltBufferToVideo
o</strong>peration should write data to video screen and
<strong>EfiBltVideoToBltBuffer</strong> operation should read data from
video display rectangle.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(SourceX+Width, SourceY+Height) and place it in the BltBuffer
rectangle (DestinationX, DestionationY) (DestionationX+Width,</p>
<p><em>DestionationY</em>+<em>Height</em>). The returned status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to the video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). – Source and Destination
should reverse with that of <strong>EfiBltVideoToBltBuffer</strong>
operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•The <em>BltBuffer</em> and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.5</td>
<td>0x13f113dc, 0xafd0, 0x4658, 0xb7, 0xfb, 0x83, 0xd5, 0xae, 0x6f,
0x10, 0x58</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –
EfiBltBufferToVide</strong> operation should write data to video screen
and <strong>EfiBltVideoToBltBuffer</strong> operation should read data
from video display rectangle.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to read data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the <em>BltBuffer</em> rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). The returned status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). – Source and Destination
should reverse with that of <strong>EfiVideoToBltBuffer</strong>
operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•The <em>BltBuffer</em> and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.6</td>
<td>0x5ca291cc, 0x84a0, 0x489d, 0x9b, 0x2a, 0x0f, 0x2f, 0xcc, 0xc6,
0x0b, 0x29</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –
EfiBltBufferToVide</strong> operation should write data to video screen
and <strong>EfiBltVideoToBltBuffer</strong> operation should read data
from video display rectangle.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to read data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the BltBuffer rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). The returned status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,</p>
<p><em>DestionationY</em>+<em>Height</em>). – Source and Destination
should reverse with that of <strong>EfiBltVideoToBltBuffer</strong>
operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> to read data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)</p>
<p>(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
and place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.7</td>
<td>0x6c2632c0, 0xe3de, 0x4afc, 0xb3, 0xa1, 0xbe, 0x50, 0x75, 0xab,
0x2d, 0x7a</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value
of</p>
<p><em>EfiBltVideoToBltBuffer</em> to save original screen and read data
from the video display rectangle</p>
<p>(<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in <em>BltBuffer</em> rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) to
another display rectangle (<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> again to retrieve the area from the
video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the
BltBuffer2</p>
<p>rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value
of 0.</p>
<p>•The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.8</td>
<td>0x07d1d0c1, 0x3884, 0x4310, 0x97, 0xbc, 0x16, 0xd6, 0xaa, 0x1a,
0x21, 0x80</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value
of</p>
<p><em>EfiBltVideoToBltBuffer</em> to save original screen and read data
from the video display rectangle</p>
<p>(<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in <em>BltBuffer</em> rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) to
another display rectangle (<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoToBltBuffer</em> again to retrieve the area from the
video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the
BltBuffer2</p>
<p>rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value
of 0.</p>
<p>•The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.9</td>
<td>0x11af616a, 0xbef5, 0x4590, 0xbe, 0x85, 0x19, 0x52, 0xa0, 0x0d,
0xe1, 0xaf</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>Call
<strong>Blt()</strong>with invalid <em>BltOperation</em>.</td>
<td><p>Repeat the following step 6 times:</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value other
than</p>
<p>EfiBltVideoFill/<strong>EfiBltVideoToBltBuffer</strong>/<strong>EfiBltBufferToVideo</strong>/<strong>EfiBltVideoToVideo</strong>.The
returned status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Restore the screen mode.</p></td>
</tr>

<tr class="even">
<td>5.6.6.3.11</td>
<td>0xe967bdc7, 0xa0ea, 0x4fd7, 0xab, 0xba, 0x52, 0xf3, 0xef, 0x53,
0x22, 0x3e</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>Call
<strong>Blt()</strong> to verify that the pixels
<strong>EfiBltVideoToBltBuffer</strong> retrieves are the same as the
pixels <strong>EfiBltVideoFill</strong> fills.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to write data from the
<em>BltBuffer</em> pixel (0, 0) directly to every pixel of the video
display rectangle (<em>DestinationX</em>, <em>DestionationY</em>)
(<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the rectangles drawn
by the last <strong>EfiBltVideoFill</strong> operation. The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>All of the retrieved rectangles should be the same pixel used in the
last <strong>EfiBltVideoFill</strong> operation.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.12</td>
<td>0x1fc521b0, 0x63c1, 0x4f42, 0xb8, 0x14, 0x06, 0x8a, 0x6c, 0x9c,
0x3e, 0x29</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Call <strong>Blt()</strong>with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to write data from the
<em>BltBuffer</em> pixel (0, 0) directly to every pixel of the video
display rectangle (<em>DestinationX</em>, <em>DestionationY</em>)
(<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the rectangles drawn
by the last <strong>EfiBltVideoFill</strong> operation. The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>All of the retrieved rectangles should be the same pixel used in the
last <strong>EfiBltVideoFill</strong> operation.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.13</td>
<td>0x04fd0571, 0xf3eb, 0x4d69, 0xb2, 0xd2, 0x5c, 0x4f, 0xfb, 0x10,
0x5a, 0xc3</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video memory to buffer.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoFill</strong> to write data from the
<em>BltBuffer</em> pixel (0, 0) directly to every pixel of the video
display rectangle (<em>DestinationX</em>, <em>DestionationY</em>)
(<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the rectangles drawn
by the last <strong>EfiBltVideoFill</strong> operation. The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>All of the retrieved rectangles should be the same pixel used in the
last <strong>EfiBltVideoFill</strong> operation.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.14</td>
<td>0x5bee154c, 0xe519, 0x4be4, 0xaf, 0x8c, 0xb4, 0x18, 0x8e, 0x79,
0xb4, 0xbf</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>• To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the BltBuffer rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the BltBuffer
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). – Source and Destination should
reverse with that of <strong>EfiBltVideoToBltBuffer</strong> operation.
The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.15</td>
<td>0xf9e726c1, 0x1346, 0x419e, 0x90, 0x8a, 0x66, 0xc4, 0x49, 0x8c,
0xfd, 0x71</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video to the buffer <em>BltBuffer</em>.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the <em>BltBuffer</em> rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). – Source and Destination should
be the reverse of the <strong>EfiBltVideoToBltBuffer</strong> operation.
The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.16</td>
<td>0x00f74a1b, 0x4599, 0x45b7, 0xb6, 0xf7, 0x13, 0xf2, 0xcb, 0xd8,
0x6c, 0xe6</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should write data to the video
screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the <em>BltBuffer</em> rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the
<em>BltBuffer</em> rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to the video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). – Source and Destination should
be the reverse of the <strong>FeiBltVideoToBltBuffer</strong> operation.
The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a <em>Delta</em> value of 0.The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.17</td>
<td>0x26da6582, 0x8b82, 0x4bd2, 0xac, 0x3a, 0x6e, 0x37, 0x85, 0x4f,
0xd8, 0x21</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video to another buffer BltBuffer2.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the <em>BltBuffer</em> rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the BltBuffer
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to the video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). – Source and Destination should
be the reverse of the <strong>EfiBltVideoToBltBuffer</strong> operation.
The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a <em>Delta</em> value of 0.The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.18</td>
<td>0x0aaf7f4e, 0x1794, 0x403c, 0xb3, 0xb0, 0x18, 0xf5, 0xe4, 0xd3,
0xc4, 0xea</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>Verify if the
pixels retrieved from the first operation of
<strong>EfiBltVideoToBltBuffer</strong> are the same as the pixels
retrieved from the second operation.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the <em>BltBuffer</em> rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to write data from the BltBuffer
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>)
directly to the video display rectangle (<em>DestinationX</em>,
<em>DestionationY</em>) (<em>DestionationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). – Source and Destination should
be the reverse of the <strong>EfiBltVideoToBltBuffer</strong> operation.
The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to read data from the video
display rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) and
place it in the BltBuffer2 rectangle (0, 0) (<em>Width</em>,
<em>Height</em>) with a delta value of 0.The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.19</td>
<td>0x2a79335b, 0xafc3, 0x4ccf, 0x9b, 0xa4, 0x91, 0x9b, 0xe4, 0xb8,
0xbe, 0xfc</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to save the original screen and
read data from the video display rectangle (<em>SourceX</em>,
<em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) and place it in the <em>BltBuffer</em>
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0.The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
EfiBltVideoToVideo to copy data from the video display rectangle
(<em>SourceX</em>, <em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) to another display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> again to retrieve the area from
the video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in BltBuffer2
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0. The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.20</td>
<td>0x3f4c2c88, 0xa1f8, 0x46f5, 0x9e, 0x5e, 0x67, 0x50, 0xb4, 0xae,
0x2b, 0x6f</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video display rectangle to the buffer <em>BltBuffer</em>.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to save the original screen and
read data from the video display rectangle (<em>SourceX</em>,
<em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) and place it in the <em>BltBuffer</em>
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0.The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) to
another display rectangle (<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> again to retrieve the area from
the video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the BltBuffer2
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0. The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.21</td>
<td>0xa11dd47e, 0xf144, 0x460c, 0x9e, 0x18, 0x7e, 0xb7, 0xed, 0xda,
0xc0, 0x18</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to save the original screen and
read data from the video display rectangle (<em>SourceX</em>,
<em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) and place it in the <em>BltBuffer</em>
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0.The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
EfiBltVideoToVideo to copy data from the video display rectangle
(<em>SourceX</em>, <em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) to another display rectangle
(<em>DestinationX</em>, Dest<em>i</em>nationY)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> again to retrieve the area from
the video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the BltBuffer2
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0. The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.22</td>
<td>0xbe3e3046, 0x5aea, 0x48d0, 0x91, 0xc4, 0x62, 0xce, 0xff, 0x61,
0x3c, 0xec</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video display rectangle to another buffer BltBuffer2.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to save the original screen and
read data from the video display rectangle (<em>SourceX</em>,
<em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) and place it in the <em>BltBuffer</em>
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0.The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) to
another display rectangle (<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> again to retrieve the area from
the video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the BltBuffer2
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0. The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.23</td>
<td>0xed4e402a, 0x403c, 0x4071, 0x86, 0x93, 0x9d, 0x8d, 0x28, 0xf7,
0x83, 0xd9</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>Verify that the
pixels <strong>EfiBltVideoToBltBuffer</strong> retrieves are the same as
the ones the second operation retrieves.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•To select a different valid parameter (<em>SourceX</em>,
<em>SourceY</em>, <em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>, <em>Delta</em>):</p>
<p>Load a bitmap from the prepared buffer and call
<strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display it in the video. The
returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoToBltBuffer</strong> to save the original screen and
read data from the video display rectangle (<em>SourceX</em>,
<em>SourceY</em>) (<em>SourceX</em>+<em>Width</em>,
<em>SourceY</em>+<em>Height</em>) and place it in the <em>BltBuffer</em>
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0.The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy data from the video display
rectangle (<em>SourceX</em>, <em>SourceY</em>)
(<em>SourceX</em>+<em>Width</em>, <em>SourceY</em>+<em>Height</em>) to
another display rectangle (<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestionationY</em>+<em>Height</em>). The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> again to retrieve the area from
the video display and read data from the video display rectangle
(<em>DestinationX</em>, <em>DestinationY</em>)
(<em>DestinationX</em>+<em>Width</em>,
<em>DestinationY</em>+<em>Height</em>) and place it in the BltBuffer2
rectangle (0, 0) (<em>Width</em>, <em>Height</em>) with a delta value of
0. The returned status should be <strong>EFI_SUCCESS</strong>.</p>
<p>The BltBuffer and BltBuffer2 should be the same.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.24</td>
<td>0x3b54894e, 0x6383, 0x4dd5, 0x9e, 0x53, 0xbe, 0x6b, 0xc1, 0x1b,
0xd8, 0x94</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat the following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong>with a <em>BltOperation</em> value
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
EfiBltBufferToVideo operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between the two
coordinates. In addition, the (<em>DestinationX</em>,
<em>DestinationY</em>, <em>Width</em>, <em>Height</em>) should not
exceed the boundary of the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.25</td>
<td>0xd0869ac8, 0x1d16, 0x4657, 0xae, 0xf2, 0x06, 0xc3, 0x49, 0x82,
0x1d, 0x55</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.26</td>
<td>0x1f026b26, 0x36fd, 0x4f1c, 0x95, 0x4c, 0x16, 0x0f, 0x9f, 0x98,
0x49, 0xd1</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.27</td>
<td>0xd0bfb3c3, 0x54df, 0x4c07, 0x8e, 0x5c, 0x7a, 0x19, 0xa3, 0x5b,
0x5c, 0x0c</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong>with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP files rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.28</td>
<td>0xfde7edd9, 0x1486, 0x45e9, 0xae, 0x06, 0x31, 0xe8, 0xcb, 0x3f,
0xf3, 0x46</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> Value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.29</td>
<td>0x538471f3, 0x8828, 0x4d1b, 0x8c, 0x2b, 0x01, 0x37, 0xe9, 0x4f,
0xae, 0xc9</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare BltBuffer from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.30</td>
<td>0x30ef55c6, 0x62a2, 0x4f90, 0xb3, 0xf8, 0xf4, 0xf9, 0x1b, 0x94,
0xbf, 0x91</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare BltBuffer from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions with 2 times:</p>
<p>change the (<em>DestinationX</em>,<em>DestinationY</em>) from the
upper left-hand corner to the upper right-hand corner, then down to the
lower right-hand corner, then to the lower left-hand corner, then to the
upper left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise.</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.31</td>
<td>0x2bb7feeb, 0x9b15, 0x4b27, 0x92, 0x61, 0xff, 0xa6, 0x9e, 0xcf,
0x0a, 0x00</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions, change the
(<em>DestinationX</em>,<em>DestinationY</em>) from the upper left-hand
corner to the upper right-hand corner, then down to the lower right-hand
corner, then to the lower left-hand corner, then to the upper left-hand
corner, i.e., rotate the (<em>DestinationX</em>,<em>DestinationY</em>)
clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last call
of <strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.32</td>
<td>0x3bb9ebcc, 0x370a, 0x4c02, 0xb2, 0x0d, 0x1f, 0x86, 0x5a, 0x98,
0xaa, 0x15</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display.</p>
<p>•Repeat following actions, change the
(<em>DestinationX</em>,<em>DestinationY</em>) from the upper left-hand
corner to the upper right-hand corner, then down to the lower right-hand
corner, then to the lower left-hand corner, then to the upper left-hand
corner, i.e., rotate the (<em>DestinationX</em>,<em>DestinationY</em>)
clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file stored in
<em>BltBuffer</em>. The returned status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the rectangle in the last
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>,
<em>DestinationY</em>,<em>Width</em>, <em>Height</em>) should avoid
exceeding the boundary of the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.33</td>
<td>0xb904f2be, 0x720e, 0x4d9b, 0x86, 0x72, 0xd7, 0x84, 0x6b, 0xbc,
0x53, 0xea</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>fiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the EfiBltVideoToVideo
operation should not overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.34</td>
<td>0x53748ffc, 0xaff8, 0x4cc9, 0x83, 0xab, 0xc7, 0x09, 0xe1, 0x59,
0x1c, 0xed</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last call of EfiBltVideoToVideo operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.35</td>
<td>0x4acd2d08, 0x01dd, 0x411f, 0xa6, 0xe2, 0xf3, 0x6f, 0x9f, 0x4b,
0x03, 0xb0</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<em>EfiBltVideoFill</em> to clear the source rectangle in the last
EfiBltVideoToVideo operation. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.36</td>
<td>0xb11e8ade, 0x0c54, 0x4963, 0x89, 0x66, 0xa0, 0x4a, 0x50, 0x40,
0x1c, 0x7b</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to lower the left-hand corner, then to upper the
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP rotates correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.37</td>
<td>0xfa43d810, 0x7501, 0x481f, 0xbd, 0xcd, 0xc1, 0x06, 0x57, 0x94,
0x84, 0x9a</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> vlue of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to upper the
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.38</td>
<td>0x94989a37, 0x3941, 0x4cd8, 0x97, 0x0b, 0x14, 0xfa, 0x46, 0xb6,
0x07, 0x16</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last call of <strong>EfiBltVideoToVideo</strong> operation. The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.39</td>
<td>0x4dde309d, 0xaf32, 0x4a35, 0x91, 0x5a, 0x41, 0xcb, 0xb0, 0x18,
0x7c, 0x29</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display shoul be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.40</td>
<td>0xaa6b7386, 0x0537, 0x4762, 0xa1, 0x43, 0xca, 0xde, 0xb7, 0x55,
0x15, 0xc7</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToVideo</strong> operation should copy data from one video
display rectangle to another.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.41</td>
<td>0xb751208f, 0x10eb, 0x47eb, 0x9c, 0x73, 0x15, 0x08, 0xb8, 0xc9,
0xcd, 0xbe</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –EfiBltVideoFill</strong>
operation should fill the graphic screen with pixels.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from
<strong>theEfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last <strong>EfiBltVideoToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt the user to judge whether the BMP file rotates
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.42</td>
<td>0x57b7debf, 0xb831, 0x40d1, 0x8b, 0xa0, 0xa6, 0x57, 0x7b, 0x92,
0xe2, 0x53</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>check logo
rotatation correctly from user’s view.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the display. The returned
status should be <strong>EFI_SUCCESS</strong>, and the display should be
cleaned.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display the BMP file.</p>
<p>•Repeat following actions, change the</p>
<p>(<em>DestinationX</em>,<em>DestinationY</em>) from the upper
left-hand corner to the upper right-hand corner, then down to the lower
right-hand corner, then to the lower left-hand corner, then to the upper
left-hand corner, i.e., rotate the
(<em>DestinationX</em>,<em>DestinationY</em>) clockwise:</p>
<p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToVideo</strong> to copy the Video drawn by the last
<strong>EfiBltVideoToVideo</strong> or
<strong>EfiBltBufferToVideo</strong> operation. The returned status
should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> The two rectangles from the
<strong>EfiBltVideoToVideo</strong> operation should not
overlap.</p></td>
</tr>
<tr class="even">
<td></td>
<td></td>
<td></td>
<td><p>Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoFill</strong> to clear the source rectangle in the
last call of <strong>EfiBltVideoToVideo</strong> operation. The returned
status should be <strong>EFI_SUCCESS</strong>.</p>
<p><strong>Note:</strong> the rotation of (<em>DestinationX</em>,
<em>DestinationY</em>) may have some distance between two coordinate. In
addition, the (<em>DestinationX</em>, <em>DestinationY</em>,
<em>Width</em>, <em>Height</em>) should avoid exceeding the boundary of
the current screen mode.</p>
<p>•Prompt user to judge whether the rotation of the BMP file
correctly.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.43</td>
<td>0x8971c5fe, 0x02c6, 0x4ada, 0xab, 0x30, 0x36, 0xc5, 0xa7, 0xd9,
0xdc, 0x01</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltBufferToVideo</strong> operation should draw the bitmap from the
specified buffer to the video screen.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display BMP file to some
position of the screen.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the whole screen to
a large <em>BltBuffer</em>. The return status</p>
<p>should be <strong>EFI_SUCCESS</strong>.</p>
<p>•Change <em>SourceX</em> from 0 to HorizontalResolution step by step,
and change <em>SourceY</em> from 0 to VerticalResolution step by step,
carry out following action:</p>
<p>For small <em>Width</em>, <em>Height</em>, and <em>BltBuffer</em>,
call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong>. The returned status should be
<strong>EFI_SUCCESS</strong>. The small <em>BltBuffer</em> retrieved
should be the same as the corresponding segment in the large
<em>BltBuffer</em> standing for the whole screen buffer.</p></td>
</tr>
<tr class="even">
<td>5.6.6.3.44</td>
<td>0x03093b96, 0x2b15, 0x4008, 0xb7, 0xbf, 0x9f, 0x8c, 0x17, 0x41,
0x2d, 0xb3</td>
<td><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt
–EfiBltVideoToBltBuffer</strong> operation should retrieve the pixels
from the video display rectangle to the specified buffer.</td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display BMP file to some
position of the screen.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the whole screen to
a large <em>BltBuffer</em>. The return status</p>
<p>should be <strong>EFI_SUCCESS</strong></p>
<p>•Change <em>SourceX</em> from 0 to HorizontalResolution step by step,
and change <em>SourceY</em> from 0 to VerticalResolution step by step,
carry out following action:</p>
<p>For small <em>Width</em>, <em>Height</em>,and <em>BltBuffer</em>,
Call <strong>Blt()</strong>with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong>. The returned status should be
<strong>EFI_SUCCESS</strong>. The small <em>BltBuffer</em> retrieved
should be the same as the corresponding segment in the large
<em>BltBuffer</em> standing for the whole screen buffer.</p></td>
</tr>
<tr class="odd">
<td>5.6.6.3.45</td>
<td>0x1ef36d93, 0x8591, 0x4172, 0x94, 0xfd, 0x93, 0x08, 0x54, 0x6e,
0x73, 0x11</td>
<td><p><strong>EFI_GRAPHICS_OUTPUT_PROTOCOL.Blt –</strong>Blt/</p>
<p><strong>EfiBltVideoToBltBuffe</strong>, Pixel verification.</p></td>
<td><p>For valid graphics mode number from 0 to <em>MaxMode</em>-1:</p>
<p>•Prepare some <em>BltBuffer</em> from a small BMP file.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltBufferToVideo</strong> to display BMP file to some
position of the screen.</p>
<p>•Call <strong>Blt()</strong> with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong> to retrieve the whole screen to
a large <em>BltBuffer</em>. The return status</p>
<p>should be <strong>EFI_SUCCESS</strong></p>
<p>•Change <em>SourceX</em> from 0 to HorizontalResolution step by step,
and change <em>SourceY</em> from 0 to VerticalResolution step by step,
carry out following action:</p>
<p>For mall <em>Width</em>, <em>Height</em>, and <em>BltBuffer</em>,
call <strong>Blt()</strong>with a <em>BltOperation</em> value of
<strong>EfiBltVideoToBltBuffer</strong>. The returned status should be
<strong>EFI_SUCCESS</strong>. The small <em>BltBuffer</em> retrieved
should be the same as the corresponding segment in the large
<em>BltBuffer</em> standing for the whole screen buffer.</p></td>
</tr>
</tbody>
</table>


## EFI_SIMPLE\_ TEXT_INPUT_EX_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL Section.

### Reset()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.6.7.1.1 | 0xc969bba7, 0xed63, 0x4235, 0x80, 0x46, 0xa1, 0x8c, 0xa2, 0x8a, 0x3f, 0x6a | **SIMPLE_TEXT_INPUT_EX_PROTOCOL.Reset - Reset()** returns **EFI_SUCCESS** and **ReadKeyStrokeEx** return **EFI_NOT_READY** | It is a auto test. Call **Reset()**. **EFI_SUCCESS** should be returned. Call **ReadKeyStrokeEx()**. **EFI_NOT_READY** should be returned. |
| 5.6.7.1.2 | 0x35381b6c, 0x1035, 0x4241, 0x95, 0x80, 0x21, 0x25, 0x3b, 0x78, 0x60, 0x8d | **SIMPLE_TEXT_INPUT_EX_PROTOCOL.Reset - Reset()** returns **EFI_SUCCESS** and **ReadKeyStrokeEx** return **EFI_NOT_READY** | It is a manual test. Press a key. Call **Reset()**. **EFI_SUCCESS** should be returned. Call **ReadKeyStrokeEx()**. **EFI_NOT_READY** should be returned. |

### ReadKeyStrokeEx ()

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
<td>5.6.7.2.1</td>
<td>0x89854ccd, 0xa672, 0x4856, 0xb7, 0x6c, 0xb1, 0x66, 0xc5, 0x64,
0x2f, 0x9a</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStorkeEx -
ReadKeyStorkeEx()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with KeyData being
<strong>NULL</strong>.</td>
<td><p>Call <strong>Reset()</strong> first, and
<strong>EFI_SUCCESS</strong> should be returned.</p>
<p>Call <strong>ReadKeyStrokeEx()</strong> with <strong>KeyData</strong>
being <strong>NULL</strong>. <strong>EFI_INVALID_PARAMETER</strong>
should be returned.</p></td>
</tr>
<tr class="odd">
<td>5.6.7.2.2</td>
<td>0x5d141dc0, 0xded6, 0x4e01, 0xa9, 0x8b, 0x55, 0x1f, 0x3e, 0xe3,
0x59, 0x4d</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStorkeEx -
ReadKeyStorkeEx()</strong> returns <strong>EFI_NOT_READY</strong> with
console just been reseted.</td>
<td><p>Call <strong>Reset()</strong> first, and
<strong>EFI_SUCCESS</strong> should be returned.</p>
<p>Call <strong>ReadKeyStrokeEx()</strong> with valid parameter.
<strong>EFI_NOT_READY</strong> should be returned.</p></td>
</tr>
<tr class="even">
<td>5.6.7.2.3</td>
<td>0x5eed7df1, 0x4630, 0x44e1, 0x97, 0xaa, 0xd3, 0x26, 0x82, 0x24,
0xc4, 0x30</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStroke -
ReadKeyStrokeEx()</strong> return <strong>EFI_SUCCESS</strong> with key
input</td>
<td><p>It is a manual test. Part 1:</p>
<p>Call <strong>Reset()</strong>. <strong>EFI_SUCCESS</strong> should be
returned. Press a key. Call <strong>ReadKeyStrokeEx()</strong> with
valid parameter. <strong>EFI_SUCCESS</strong> should be
returned.</p></td>
</tr>
<tr class="odd">
<td>5.6.7.2.4</td>
<td>0x3032721e, 0x8089, 0x49d4, 0x94, 0x5a, 0x46, 0x07, 0xdc, 0x05,
0xcf, 0x8d</td>
<td><strong>EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL.ReadKeyStroke -
ReadKeyStroke()</strong> with key input, user's view</td>
<td>Part 2: Echo the key which is pressed. Tester decides the SUCCESS or
Failure.</td>
</tr>
</tbody>
</table>


### SetState ()

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
<td>5.6.7.3.1</td>
<td>0x6647a0e7, 0x483c, 0x4777, 0xa9, 0x4b, 0xc8, 0xbc, 0xa3, 0xdf,
0xc7, 0x9c</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with KeyToggleState being
<strong>NULL</strong>.</td>
<td>Call <strong>SetState()</strong> with <em>KeyToggleState</em> being
<strong>NULL</strong>. Return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.7.3.2</td>
<td>0x4c766c77, 0xdbf3, 0x4b3d, 0x82, 0x59, 0x81, 0xf8, 0xb8, 0xaa,
0x17, 0x75</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState()</strong>
returns <strong>EFI_UNSUPPORTED</strong> with KeyToggleState being a
unsupported bit set.</td>
<td>Call <strong>SetState()</strong> with unsupported
<em>KeyToggleState</em>. Return status should be
<strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.6.7.3.3</td>
<td>0x44bf142c, 0x72a9, 0x445e, 0xaf, 0x84, 0xaa, 0xc5, 0x96, 0xc6,
0x3f, 0xc8</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.SetState - SetState()</strong>
returns <strong>EFI_UNSUPPORTED</strong> or <strong>EFI_SUCCESS</strong>
with a valid bit set</td>
<td><p>Call <strong>SetState()</strong> with valid
<strong>KeyToogleState.</strong> The return status should be
<strong>EFI_UNSUPPORTED</strong> or <strong>EFI_SUCCESS</strong>.</p>
<p>Press a key and call <strong>ReadKeyStrokeEx()</strong>. The
<em>KeyToggleState</em> should be same as the State which be
set.</p></td>
</tr>
</tbody>
</table>



### RegisterKeyNotify ()

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
<td>5.6.7.4.1</td>
<td>0x27a40c7e, 0x119e, 0x451d, 0x84, 0x70, 0x1d, 0xc4, 0x52, 0x09,
0x2b, 0x0a</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify -
RegisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <em>KeyData</em> being
<strong>NULL</strong></td>
<td>Call <strong>RefisterKeyNotify()</strong> with <strong>NULL</strong>
<em>KeyData</em>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.7.4.2</td>
<td>0xb03a561d, 0x6339, 0x4035, 0xaf, 0xd5, 0xfa, 0x2e, 0xce, 0x16,
0x4b, 0xf9</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify -
RegisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em>KeyNotificationFunction</em> being <strong>NULL</strong></td>
<td>Call <strong>RefisterKeyNotify()</strong> with <strong>NULL</strong>
<em>KeyNotificationFunction</em>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.6.7.4.3</td>
<td>0x5b22932e, 0xc24d, 0x45fe, 0x8b, 0xbd, 0x2e, 0x0e, 0x56, 0xfa,
0xc3, 0x16</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify -
RegisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <em>NotifyHandle</em> being
<strong>NULL</strong>.</td>
<td>Call <strong>RefisterKeyNotify()</strong> with <strong>NULL</strong>
<em>NotifyHandle</em>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.7.4.4</td>
<td>0x69a1c06c, 0x516e, 0x4595, 0xbe, 0x4f, 0x6b, 0x18, 0x58, 0xcc,
0x82, 0x3d</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify -
RegisterKeyNotify()</strong> returns <strong>EFI_SUCCESS</strong>.</td>
<td><p>It is a manual test. Part 1:</p>
<p>Call <strong>Reset()</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Press a key, call <strong>ReadKeyStrokeEx()</strong> to get the key
value. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>RegisterKeyNotify()</strong> with the key. The return
status should <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.7.4.5</td>
<td>0x6f509a8c, 0x0df2, 0x499d, 0x97, 0x56, 0x35, 0xbe, 0x3c, 0xcb,
0x21, 0xc4</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.RegisterKeyNotify -
RegisterKeyNotify()</strong> returns <strong>EFI_SUCCESS</strong> and
notify function has been invoked.</td>
<td><p>Part 2:</p>
<p>Call <strong>Reset()</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Press the same key and check the the result of the notify
function..</p>
<p>Call <strong>UnregisterKeyNotify()</strong>.</p></td>
</tr>
</tbody>
</table>



### UnregisterKeyNotify ()

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
<td>5.6.7.5.1</td>
<td>0xa5244802, 0xf4bf, 0x4e8a, 0xaa, 0x76, 0xe4, 0x87, 0x37, 0x43,
0xd8, 0xd1</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify -
UnregisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <em>NotifyHandle</em> being
<strong>NULL</strong></td>
<td>Call <strong>UnrefisterKeyNotify</strong> with <strong>NULL</strong>
<em>NotifyHandle</em>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.7.5.2</td>
<td>0x5d1c8b11, 0x326f, 0x4cf5, 0xb0, 0x3d, 0x89, 0xaa, 0x2f, 0xaf,
0x66, 0x42</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify -
UnregisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <em>NotifyHandle</em> not
refer to a register notify function anymore.</td>
<td><p>Call <strong>RegisterKeyNotify()</strong> with valid parameter.
Return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UnregisterKeyNotify()</strong> twice. Return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.7.5.3</td>
<td>0x5fe62478, 0x4614, 0x4430, 0xb9, 0xe9, 0x30, 0xe2, 0x12, 0x19,
0xeb, 0x35</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify -
UnregisterKeyNotify()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with NotifyHandle being illegal
format.</td>
<td>Call <strong>UnrefisterKeyNotify()</strong> with invalid
<em>NotifyHandle</em>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.7.5.4</td>
<td>0xe305a4b5, 0x03c3, 0x43c4, 0x93, 0x16, 0x7d, 0x7a, 0xb3, 0x6a,
0x13, 0xa5</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify -
UnregisterKeyNotify()</strong> returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>It is a manual test. Part 1:</p>
<p>Call <strong>Reset()</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Press a key, call <strong>ReadKeyStrokeEx()</strong> to get the key
value. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>RegisterKeyNotify()</strong> with the key. The return
status should <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UnregisterKeyNotify()</strong> with the valid
<em>NotifyHandle</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.7.5.5</td>
<td>0x534369f7, 0x8399, 0x4353, 0x94, 0xad, 0xc4, 0x48, 0xfa, 0xda,
0xeb, 0x84</td>
<td><strong>SIMPLE_TEXT_INPUT_EX_PROTOCOL.UnregisterKeyNotify -
UnregisterKeyNotify()</strong> returns <strong>EFI_SUCCESS</strong> and
notify function has not been invoked.</td>
<td><p>Part 2:</p>
<p>Call <strong>Reset()</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>Press the same key and check the the result of the notify
function.</p></td>
</tr>
</tbody>
</table>


## EFI_ABSOLUTE_POINTER_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_ABSOLUTE_POINTER_PROTOCOL Section.

### Reset()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 18%" />
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
<td>5.6.8.1.1</td>
<td>0xa4e0b129, 0x4bd4, 0x4446, 0x8d, 0x32, 0xaa, 0x45, 0x64, 0xb2,
0x74, 0x6e</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - Reset()</strong> with
an ExtendedVerification value of <strong>FALSE</strong> returns
<strong>EFI_SUCCESS</strong>. If device error, should return
<strong>EFI_DEVICE_ERROR</strong></td>
<td>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>. The
return code should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_DEVICE_ERROR</strong>.</td>
</tr>
<tr class="odd">
<td>5.6.8.1.2</td>
<td>0xc246b3ff, 0xc1d5, 0x499b, 0x92, 0x87, 0x73, 0xf5, 0x88, 0xf6,
0xa9, 0x9f</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - Reset()</strong> with
an ExtendedVerification value of <strong>TRUE</strong> returns
<strong>EFI_SUCCESS</strong>. If device error, should return
<strong>EFI_DEVICE_ERROR</strong>.</td>
<td>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>. The return
code should be <strong>EFI_SUCCESS</strong> or
<strong>EFI_DEVICE_ERROR</strong>.</td>
</tr>
<tr class="even">
<td>5.6.8.1.3</td>
<td>0xab689092, 0xc9e2, 0x4618, 0x90, 0xa8, 0x4, 0x74, 0xde, 0x94, 0x7c,
0x4e</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset ()</strong> return
<strong>EFI_UNSUPPORTED</strong></td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>,the return code maybe
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.6.8.1.4</td>
<td>0x5c250202, 0xe791, 0x4cee, 0x86, 0x74, 0x4e, 0x3a, 0x43, 0xbc,
0x18, 0x15</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - Reset()</strong> with
an ExtendedVerification value of <strong>TRUE</strong> returns
<strong>EFI_SUCCESS</strong>.</td>
<td>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>. The return
code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.6.8.1.5</td>
<td>0x39c1417d, 0xf6a2, 0x4a77, 0xbb, 0xcd, 0xe, 0xb8, 0xeb, 0x41, 0xe7,
0x52</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset ()</strong> return 0 for all current movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. if success, Current movement in
X,Y and Z should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.8.1.6</td>
<td>0xd909148a, 0xd05a, 0x4694, 0xb4, 0xc4, 0xfc, 0x27, 0x87, 0x40,
0xce, 0x78</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.Reset - GetState()</strong>
after <strong>Reset ()</strong> return
<strong>EFI_UNSUPPORTED</strong></td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState(),</strong>the return code maybe
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
</tbody>
</table>


### GetState()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
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
<td>5.6.8.2.1</td>
<td>0x5271062f, 0xdef9, 0x4d30, 0x84,0x3b, 0x8d,0x6e, 0x41,0x33,
0x13,0xf3</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.GetState - GetState()</strong>
after <strong>Reset()</strong> returns 0 for all current movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. if success, Current movement in
X,Y and Z should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.8.2.2</td>
<td>0x7614c448, 0x12a0, 0x403d, 0x8a,0xde, 0x98,0x97, 0x51,0x7d,
0xd8,0x49</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.GetState - GetState()</strong>
returns <strong>EFI_NOT_READY</strong> when there is no move since last
call of <strong>GetState()</strong>or returns
<strong>EFI_DEVICE_ERROR</strong> while a device error occurred..</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of FALSE.</p>
<p>2. Call <strong>GetState()</strong> .</p>
<p>3. Call <strong>GetState()</strong> again, the return code should be
<strong>EFI_NOT_READY</strong> or
<strong>EFI_DEVICE_ERROR</strong>.</p></td>
</tr>
<tr class="even">
<td>5.6.8.2.3</td>
<td>0x2f8f8711, 0x02dd, 0x411f, 0xaa,0xb5, 0x27,0xe1, 0x3a,0x6a,
0xb2,0x79</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.GetState - GetState()</strong>
after Reset() returns 0 for all current movement.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong>. if success, Current movement in
X,Y and Z should be 0.</p></td>
</tr>
<tr class="odd">
<td>5.6.8.2.4</td>
<td>0x3db7ea19, 0xda9d, 0x4760, 0xa7,0x43, 0x04,0xb4, 0x8d,0x14,
0x4e,0x90</td>
<td><strong>EFI_ABSOLUTE_POINTER_PROTOCOL.GetState - GetState()</strong>
returns <strong>EFI_NOT_READY</strong> when there is no move since last
call of <strong>GetState()</strong>or returns
<strong>EFI_DEVICE_ERROR</strong> while a device error occurred.</td>
<td><p>1. Call <strong>Reset()</strong> with an
<em>ExtendedVerification</em> value of <strong>TRUE</strong>.</p>
<p>2. Call <strong>GetState()</strong> .</p>
<p>3. Call <strong>GetState()</strong> again, the return code should be
<strong>EFI_NOT_READY</strong> or
<strong>EFI_DEVICE_ERROR</strong>.</p></td>
</tr>
</tbody>
</table>

