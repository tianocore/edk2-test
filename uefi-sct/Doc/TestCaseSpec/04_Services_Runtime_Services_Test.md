# Services Runtime Services Test

## Variable Services Test

**Reference Document:**

*UEFI Specification*, Variable Services Section.

- Variable Services Functions

| Name                  | Type    | Description                                  |
|-----------------------|---------|----------------------------------------------|
| GetVariable()         | Runtime | Returns the value of a variable.             |
| GetNextVariableName() | Runtime | Enumerates the current variable names.       |
| SetVariable()         | Runtime | Sets the value of a variable.                |
| QueryVariableInfo()   | Runtime | Queries the information about the variables. |

### GetVariable()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 20%" />
<col style="width: 32%" />
<col style="width: 32%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.2.1.1.1</td>
<td>0xb0d54fee, 0x2787, 0x4d2d, 0xbf, 0x98, 0x73, 0xa0, 0xcd, 0x7f,
0xe9, 0x5d</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>VariableName</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>GetVariable()</strong> service with a
<em><strong>VariableName</strong></em> value of <strong>NULL</strong>.
The return code must be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.1.2</td>
<td>0x390c5e26, 0x9b46, 0x4974, 0xb3, 0x2d, 0x2b, 0xb1, 0xd4, 0x05,
0xb0, 0xd7</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>VendorGuid</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>GetVariable()</strong> service with a
<em><strong>VendorGuid</strong></em> value of <strong>NULL</strong>. The
return code must be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.1.3</td>
<td>0x176354a6, 0x1088, 0x474f, 0xbf, 0x6f, 0x95, 0x8c, 0x1c, 0xc3,
0x40, 0x8f</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>DataSize</strong></em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetVariable()</strong> service to get the test
variable while the <em><strong>DataSize</strong></em> is
<strong>NULL</strong>. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.1.4</td>
<td>0x400ab801, 0xf6c6, 0x4d04, 0xa0, 0x42, 0xa2, 0x15, 0x0b, 0xd5,
0xb6, 0x2a</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>Data</strong></em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetVariable()</strong> service to get the test
variable while the <em><strong>Data</strong></em> is
<strong>NULL</strong>. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.1.5</td>
<td>0x9b704b3d, 0x05a4, 0x4147, 0xb2, 0x55, 0x35, 0xbc, 0x3d, 0xd6,
0xcc, 0x24</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_NOT_FOUND</strong> with a nonexistent variable.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to delete the test
variable.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The return code must be <strong>EFI_NOT_FOUND</strong>.</p>
<p>4. Call <strong>SetVariable()</strong> services to insert two
variables that are similar to the test variable.</p>
<p>5. Call <strong>GetVariable()</strong> service to get the test
variable. The return code must be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.1.6</td>
<td>0xd3d915a5, 0xe7b0, 0x4417, 0x9c, 0x2e, 0x1a, 0xa8, 0x42, 0x4d,
0x22, 0x2c</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_NOT_FOUND</strong> with a nonexistent
<em><strong>VendorGuid</strong></em>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable with <strong>GUID2</strong>.</p>
<p>2. Call <strong>GetVariable()</strong> service to get the variable
with <strong>GUID1</strong>. The return code must be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.1.7</td>
<td>0x1562ce35, 0x83e7, 0x48a7, 0xad, 0x71, 0xfa, 0xa4, 0xbe, 0x17,
0x88, 0x46</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with a
<em><strong>DataSize</strong></em> value of 0.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetVariable()</strong> service to get the test
variable with a <em><strong>DataSize</strong></em> value of 0. The
return code must be <strong>EFI_BUFFER_TOO_SMALL</strong>, and the
returned <em><strong>DataSize</strong></em> should be the inserted value
in step 1.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.1.8</td>
<td>0x121c17d1, 0xbb0e, 0x4e2e, 0xb2, 0xa5, 0x03, 0x86, 0x2f, 0x46,
0xc0, 0x39</td>
<td><strong>RT.GetVariable – GetVariable()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with a
<em><strong>DataSize</strong></em> value of -1.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetVariable()</strong> service to get the test
variable with the inserted <em><strong>DataSize</strong></em> value of
–1. The return code must be <strong>EFI_BUFFER_TOO_SMALL</strong>, and
the returned <em><strong>DataSize</strong></em> should be the inserted
value in step 1.</p></td>
</tr>
<tr class="even">
<td id="section" class="unnumbered">5.2.1.1.9</td>
<td
id="xe542e81c-0x2020-0x4f3e-0xa9-0xb-0x67-0xd4-0xa8-0xd1-0x70-0xb4"
class="unnumbered">0xe542e81c, 0x2020, 0x4f3e, 0xa9, 0xb, 0x67, 0xd4,
0xa8, 0xd1, 0x70, 0xb4</td>
<td
id="rt.getvariable-getvariable-returns-efi_buffer_too_small-with-a-datasize-value-of-0."
class="unnumbered"><strong>RT.GetVariable –
GetVariable()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong>
with a <em><strong>DataSize</strong></em> value of 0.</td>
<td
id="call-setvariable-service-to-insert-a-test-variable.-2.-call-getvariable-service-to-get-the-test-variable-with-a-datasize-value-of-0-and-null-data.-the-return-code-must-be-efi_buffer_too_small-and-the-returned-datasize-should-be-the-inserted-value-in-step-1."
class="unnumbered">1. Call <strong>SetVariable()</strong>
service to insert a test
variable.
2. Call <strong>GetVariable()</strong>
service to get the test variable
with a <em>DataSize</em> value of 0 and NULL <em>Data</em>.
The return code must be
<strong>EFI_BUFFER_TOO_SMALL</strong>,
and the returned <em>DataSize
</em>should be the inserted value
in step 1.</td>
</tr>
<tr class="odd">
<td id="section-1" class="unnumbered">5.2.1.1.10</td>
<td
id="xaa35cc00-0xc55c-0x42d8-0xa6-0xd4-0x1e-0xb4-0x9d-0xe3-0xd7-0x54"
class="unnumbered">0xaa35cc00,
0xc55c, 0x42d8,
0xa6, 0xd4,
0x1e, 0xb4,
0x9d, 0xe3,
0xd7, 0x54</td>
<td
id="rt.getvariable-getvariable-gets-the-existing-variable-without-attributes-at-efi_tpl_application."
class="unnumbered"><strong>RT.GetVariable –
GetVariable()</strong> gets the
existing variable without
attributes at
EFI_TPL_APPLICATION.</td>
<td
id="call-setvariable-service-to-insert-a-test-variable.-2.-call-getvariable-service-to-get-the-test-variable-without-attributes.-the-returned-status-must-be-efi_success-and-the-returned-data-and-datasize-must-be-the-same-as-the-data-written-before."
class="unnumbered">1. Call SetVariable()
service to insert a test
variable.
2. Call GetVariable()
service to get the test variable
without <em>Attributes</em>. The
returned status must be
EFI_SUCCESS, and the
returned <em>Data</em> and
<em>DataSize</em> must be the same
as the data written before.</td>
</tr>
<tr class="even">
<td id="section-2" class="unnumbered">5.2.1.1.11</td>
<td
id="x742a9651-0x9783-0x43b8-0x8c-0x18-0x47-0x04-0xae-0x41-0xc3-0x34"
class="unnumbered">0x742a9651,
0x9783, 0x43b8,
0x8c, 0x18,
0x47, 0x04,
0xae, 0x41,
0xc3, 0x34</td>
<td
id="rt.getvariable-getvariable-gets-the-existing-variable-without-attributes-at-efi_tpl_callback."
class="unnumbered">RT.GetVariable –
GetVariable() gets the
existing variable without
attributes at
EFI_TPL_CALLBACK.</td>
<td
id="call-setvariable-service-to-insert-a-test-variable.-2.-call-getvariable-service-to-get-the-test-variable-without-attributes.-the-returned-status-must-be-efi_success-and-the-returned-data-and-datasize-must-be-the-same-as-the-data-written-before.-1"
class="unnumbered">1. Call SetVariable()
service to insert a test
variable.
2. Call GetVariable()
service to get the test variable
without <em>Attributes</em>. The
returned status must be
EFI_SUCCESS, and the
returned <em>Data</em> and
<em>DataSize</em> must be the same
as the data written before.</td>
</tr>
<tr class="odd">
<td id="section-3" class="unnumbered">5.2.1.1.12</td>
<td
id="x90e959d0-0xbe2c-0x45fd-0x85-0x32-0x85-0x21-0xe4-0xe0-0xfb-0x72"
class="unnumbered">0x90e959d0,
0xbe2c, 0x45fd,
0x85, 0x32,
0x85, 0x21,
0xe4, 0xe0, 0xfb, 0x72</td>
<td
id="rt.getvariable-getvariable-gets-the-existing-variable-with-attributes-at-efi_tpl_application"
class="unnumbered">RT.GetVariable –
GetVariable() gets the
existing variable with
attributes at
EFI_TPL_APPLICATION</td>
<td
id="call-setvariable-service-to-insert-a-test-variable.-2.-call-getvariable-service-to-get-the-test-variable-with-attributes.-the-returned-status-must-be-efi_success-and-the-returned-attributes-data-and-datasize-must-be-the-same-as-the-data-written-before."
class="unnumbered">1. Call SetVariable()
service to insert a test
variable.
2. Call GetVariable()
service to get the test variable
with <em>Attributes</em>. The
returned status must be
EFI_SUCCESS, and the
returned <em>Attributes</em>, <em>Data
</em>and <em>DataSize</em> must be the
same as the data written
before.</td>
</tr>
<tr class="even">
<td id="section-4" class="unnumbered">5.2.1.1.13</td>
<td
id="x5c8b43b7-0xec6f-0x4621-0xb8-0x48-0x6a-0x40-0x0f-0xd8-0xb3-0x43"
class="unnumbered">0x5c8b43b7,
0xec6f, 0x4621,
0xb8, 0x48,
0x6a, 0x40, 0x0f, 0xd8, 0xb3, 0x43</td>
<td
id="rt.getvariable-getvariable-gets-the-existing-variable-with-attributes-at-efi_tpl_callback."
class="unnumbered">RT.GetVariable –
GetVariable() gets the
existing variable with
attributes at
EFI_TPL_CALLBACK.</td>
<td
id="call-setvariable-service-to-insert-a-test-variable.-2.-call-getvariable-service-to-get-the-test-variable-with-attributes.-the-returned-status-must-be-efi_success-and-the-returned-attributes-data-and-datasize-must-be-the-same-as-the-data-written-before.-1"
class="unnumbered">1. Call SetVariable()
service to insert a test
variable.
2. Call GetVariable()
service to get the test variable
with <em>Attributes</em>. The
returned status must be
EFI_SUCCESS, and the
returned <em>Attributes</em>, <em>Data
</em>and <em>DataSize</em> must be the
same as the data written
before.</td>
</tr>
</tbody>
</table>

### GetNextVariableName()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
<col style="width: 32%" />
<col style="width: 33%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.2.1.2.1</td>
<td>0x5826847a, 0x9067, 0x4f9f, 0x88, 0x38, 0x0b, 0xf8, 0xec, 0x20,
0x17, 0x1c</td>
<td><strong>RT.GetNextVariableName – GetNextVariableName()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>VariableNameSize</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>GetNextVariableName()</strong> service with a
<em><strong>VariableNameSize</strong></em> value of
<strong>NULL</strong>. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.2.2</td>
<td>0x8e8258dc, 0x6634, 0x4de1, 0x85, 0x7a, 0x60, 0x45, 0x7e, 0xfa,
0x7c, 0x21</td>
<td>RT.GetNextVariableName - <strong>GetNextVariableName()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>VariableName</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>GetNextVariableName()</strong> service with a
<em><strong>VariableName</strong></em> value of <strong>NULL</strong>.
The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.2.3</td>
<td>0x99a357f0, 0xb6c5, 0x4aec, 0x96, 0x48, 0x34, 0x73, 0x2d, 0x2a,
0x49, 0x50</td>
<td>RT.GetNextVariableName - <strong>GetNextVariableName()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a
<em><strong>VendorGuid</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>GetNextVariableName()</strong> service with a
<em><strong>VendorGuid</strong></em> value of <strong>NULL</strong>. The
returned status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.2.4</td>
<td>0x51c19dba, 0xbaf6, 0x4854, 0xac, 0x09, 0x60, 0x45, 0x47, 0x88,
0x67, 0x98</td>
<td><strong>RT.GetNextVariableName – GetNextVariableName()</strong>
returns <strong>EFI_BUFFER_TOO_SMALL</strong> with a
<em><strong>VariableNameSize</strong></em> value of 2.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetNextVariableName()</strong> service with a
<em><strong>VariableNameSize</strong></em> value of 2. The returned
status should be <strong>EFI_BUFFER_TOO_SMALL</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.2.5</td>
<td>0xfe09ff82, 0xb289, 0x449f, 0xb0, 0x83, 0x98, 0x1d, 0x68, 0xd9,
0x17, 0xb1</td>
<td><strong>RT.GetNextVariableName – GetNextVariableName()</strong>
returns <strong>EFI_NOT_FOUND</strong> after the entire variable list
returned.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to delete the test
variable.</p>
<p>3. Call <strong>GetNextVariableName()</strong> service to traverseall
variables. The deleted test variable should not be returned.</p>
<p>4. The last returned status of <strong>GetNextVariableName()</strong>
service should be <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.2.6</td>
<td>0x12071508, 0x16c7, 0x4e5e, 0xa4, 0x22, 0x59, 0xe0, 0x24, 0x1c,
0xc6, 0x28</td>
<td><strong>RT.GetNextVariableName – GetNextVariableName()</strong> gets
the existing variable at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetNextVariableName()</strong> service to traverseall
variables. The test variable should be returned in this loop.</p></td>
</tr>
<tr class="even">
<td>5.2.1.2.7</td>
<td>0xa85043bc, 0x4f0d, 0x47b3, 0x8e, 0x9d, 0x2d, 0xb6, 0xc8, 0xf8,
0xfa, 0xef</td>
<td><strong>RT.GetNextVariableName – GetNextVariableName()</strong> gets
the exist variable at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>GetNextVariableName()</strong> service to traverseall
variables. The test variable should be returned in this loop.</p></td>
</tr>
</tbody>
</table>


### SetVariable()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
<col style="width: 32%" />
<col style="width: 32%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.2.1.3.1</td>
<td>0x73af529b, 0x3ebe, 0x464a, 0xba, 0x6a, 0xfb, 0x04, 0x7b, 0x56,
0x4f, 0x74</td>
<td><strong>RT.SetVariable – SetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when the
<em><strong>VariableName</strong></em> value is an empty string.</td>
<td>1. Call <strong>SetVariable()</strong> service when the
<em><strong>VariableName</strong></em> value is an empty string. The
returned status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.2</td>
<td>0x39e95cbb, 0x6b89, 0x473e, 0x91, 0xba, 0x92, 0x08, 0x2d, 0x1b,
0x94, 0xad</td>
<td><strong>RT.SetVariable – SetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>RA</strong> only
<em><strong>Attributes</strong></em>.</td>
<td>1. Call <strong>SetVariable()</strong> service with
<strong>EFI_VARIABLE_RUNTIME_ACCESS</strong> attributes. The returned
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.3.3</td>
<td>0xf6ef5087, 0x4962, 0x4d71, 0x80, 0x09, 0xdb, 0xe2, 0x78, 0x94,
0x53, 0xe6</td>
<td><strong>RT.SetVariable – SetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>NV|RA</strong>
<em><strong>Attributes</strong></em>.</td>
<td>1. Call <strong>SetVariable()</strong> service with
<strong>EFI_VARIABLE_NON_VOLATILE</strong> |
<strong>EFI_VARIABLE_RUNTIME_ACCESS</strong> attributes. The returned
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.4</td>
<td>0x65973462, 0x6877, 0x408f, 0x9b, 0xe1, 0x46, 0x69, 0x3e, 0xab,
0x03, 0x84</td>
<td><strong>RT.SetVariable – SetVariable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a variable that exceeds the
maximum size.</td>
<td>1. Call <strong>SetVariable()</strong> service to set a test
variable with the size of (UINTN)-1. The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.3.5</td>
<td>0x6c9cf2ea, 0xcabd, 0x4312, 0xb9, 0xcf, 0x0a, 0x96, 0xc4, 0xf1,
0xea, 0x8b</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets a nonexistent
variable at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable with <strong>GUID2</strong>.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable with <strong>GUID1</strong>. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable with <strong>GUID1</strong> and <strong>GUID2</strong>. The
data of both variables should be the same as the values written
before.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.6</td>
<td>0x3ae09eaf, 0x07cd, 0x4320, 0x92, 0xfd, 0xe9, 0xe6, 0x4b, 0x31,
0x6f, 0xe1</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets a nonexistent
variable at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable with <strong>GUID2</strong>.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable with <strong>GUID1</strong>. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable with <strong>GUID1</strong> and <strong>GUID2</strong>. The
data of both variables should be the same as the values written
before.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.7</td>
<td>0x7ccde75b, 0x4ef2, 0x40ec, 0x9a, 0xcb, 0x84, 0x7b, 0xb5, 0x29,
0x73, 0xbe</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable with the data from <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the same data. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.8</td>
<td>0x5b720ad1, 0xd0cc, 0x4be0, 0x93, 0x18, 0x20, 0x1b, 0xac, 0x32,
0x8d, 0x4f</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable with the data from <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the same data. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be unchanged.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.9</td>
<td>0x2dee62d3, 0xbab7, 0x4d91, 0x8b, 0x47, 0x3e, 0x38, 0x35, 0xd3,
0x88, 0xae</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable value which is different from the one at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the different data in which the left part of new
data is the same as old data. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be changed to the new
one.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.10</td>
<td>0x861a0691, 0x6590, 0x4a28, 0xae, 0x56, 0xaa, 0xcb, 0xf3, 0xf2,
0xbe, 0x99</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable value which is different from the one at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the different data in which the left part of new
data is the same as the old data The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be changed to the new
one.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.11</td>
<td>0x76198a1a, 0xc63a, 0x4a3b, 0x88, 0xb0, 0xc4, 0x45, 0x39, 0xdd,
0xff, 0x5d</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable with different data at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the different data in which the left part of old
data is the same as the new data The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be changed to the new
one.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.12</td>
<td>0xcefbdb2c, 0x0c7d, 0x4dcf, 0xae, 0x16, 0x32, 0xa8, 0x78, 0xca,
0x2d, 0x3e</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets the existing
variable with different data at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert the test
variable again with the different data in which the left part of old
data is the same as the new data. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The data of the test variable should be changed to the new
one.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.13</td>
<td>0xc457149c, 0x75d0, 0x48b5, 0xa1, 0x6c, 0x7e, 0x9f, 0x14, 0x4a,
0xab, 0x15</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert two
similar variables.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned data should be those written before.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.14</td>
<td>0x89f533da, 0x20ee, 0x41f8, 0x8c, 0x60, 0xc3, 0xc4, 0x14, 0x19,
0x05, 0x15</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert two
similar variables.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned data should be those written before.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.15</td>
<td>0xfc5f89d1, 0x4fce, 0x4fe9, 0xa2, 0xfd, 0xa2, 0xfe, 0x69, 0x5b,
0xaa, 0x35</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
similar variable, whose name is the test variable’s name plus character
‘A’.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the similar
variable. The returned data should be unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.16</td>
<td>0xfa5f4961, 0xdfaf, 0x425f, 0x95, 0x14, 0x14, 0x52, 0x5c, 0x69,
0xc7, 0x83</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
similar variable, whose name is the test variable’s name + ‘A’.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the similar
variable. The returned data should be unchanged.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.17</td>
<td>0x3cf290ca, 0x49e9, 0x43c0, 0x8a, 0x0c, 0x46, 0xea, 0x17, 0x53,
0x41, 0x08</td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
similar variable, whose name is the test variable’s name minus character
‘A’.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get a similar
variable. The returned data should be unchanged.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.18</td>
<td><p>0xc1f69f8f, 0xa6ed, 0x4823, 0x88, 0xd9, 0x9a, 0x23, 0x8e, 0x6a, 0x11, 0x00</p></td>
<td><strong>RT.SetVariable – SetVariable()</strong> sets similar
existing variables at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
similar variable, whose name is the test variable’s name minus character
‘A’.</p>
<p>2. Call <strong>SetVariable()</strong> service to insert a test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the similar
variable. The returned data should be unchanged.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.19</td>
<td>0x7b893a77, 0x70ca, 0x48e4, 0xad, 0x1d, 0xe4, 0x31, 0x15, 0xb1,
0xce, 0x5e</td>
<td><strong>RT.SetVariable – SetVariable()</strong> removes all
variables with a <em><strong>DataSize</strong></em> value of 0 at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service with a
<em><strong>DataSize</strong></em> value of 0 to delete the test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.20</td>
<td>0x8fcc7182, 0x4f77, 0x4841, 0xbb, 0x81, 0x20, 0xe5, 0x30, 0x5e,
0xa9, 0xda</td>
<td><strong>RT.SetVariable – SetVariable()</strong> removes all
variables with a <em><strong>DataSize</strong></em> value of 0 at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service with a
<em><strong>DataSize</strong></em> value of 0 to delete the test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.21</td>
<td>0x931b363e, 0x8ab4, 0x49db, 0x82, 0x21, 0x2f, 0xdd, 0x9d, 0xa4,
0x36, 0x6c</td>
<td><strong>RT.SetVariable – SetVariable()</strong> removes all
variables with <em><strong>Attributes</strong></em> values of 0 at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service with
<em><strong>Attributes</strong></em> values of 0 to delete the test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.22</td>
<td>0x7eac83e5, 0x0e54, 0x4812, 0x9b, 0xb0, 0x6f, 0xf6, 0xdc, 0x7d,
0xeb, 0x8f</td>
<td><strong>RT.SetVariable – SetVariable()</strong> removes all
variables with <em><strong>Attributes</strong></em> values of 0 at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a test
variable.</p>
<p>2. Call <strong>SetVariable()</strong> service with
<em><strong>Attributes</strong></em> values of 0 to delete the test
variable. The returned status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.23</td>
<td>0x6afdea5e, 0x1030, 0x48ab, 0x91, 0xdd, 0x7c, 0xd3, 0x53, 0x7c,
0xad, 0x3b</td>
<td><strong>RT.SetVariable –</strong> checks Non-volatile variable
exists after system reset at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
non-volatile test variable. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Reset the system.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be <strong>EFI_SUCCESS</strong>,
and the returned data should be the same as the original data
set.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.24</td>
<td>0x653f14cc, 0x8ecd, 0x4aaf, 0xad, 0xd6, 0x96, 0xc5, 0x07, 0x11,
0x2d, 0x67</td>
<td><strong>RT.SetVariable –</strong> checks Non-volatile variable
exists after system reset at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
non-volatile test variable. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Reset the system.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be <strong>EFI_SUCCESS</strong>,
and the returned data should be the same as the orginal data
set.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.25</td>
<td>0xb93d2b03, 0x5943, 0x4c7d, 0x98, 0xec, 0xc5, 0xfe, 0x4c, 0x6e,
0x10, 0xc9</td>
<td><strong>RT.SetVariable –</strong> checks Volatile variable does not
exist after system reset at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
volatile test variable. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Reset the system.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.26</td>
<td>0x9ec88dbe, 0xa0e4, 0x43a2, 0xaa, 0x2b, 0x60, 0xbd, 0xe6, 0xb0,
0x14, 0x1a</td>
<td><strong>RT.SetVariable –</strong> Volatile variable does not exist
after system reset at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
volatile test variable. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Reset the system.</p>
<p>3. Call <strong>GetVariable()</strong> service to get the test
variable. The returned status should be
<strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.3.27</td>
<td>0x98ca8089, 0x7f55, 0x4427, 0x8c, 0x15, 0xaf, 0xa6, 0x3d, 0x78,
0x48, 0xb0</td>
<td><strong>RT.SetVariable -</strong> With <strong>DataSize</strong> is
0</td>
<td><p>1. Call <strong>SetVariable()</strong> service to insert a
volatile test variable. The returned status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>2. Call <strong>SetVariable()</strong> service to remove this
variable with <strong>DataSize</strong> being 0. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>SetVariable()</strong> service to remove this
variable with <strong>DataSize</strong> being 0. The returned status
should be <strong>EFI_NOT_FOUND</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.28</td>
<td><p>0x008e18a5, 0xc345, 0x48ae, 0x91, 0x34, 0x61, 0xa6,</p>
<p>0x92, 0xe3, 0xb, 0x87</p></td>
<td><strong>RT.SetVariable -</strong> Must return
<strong>EFI_SUCCESS</strong> when creating one time-based Auth
Variable.</td>
<td>Call <strong>SetVariable</strong> to create a time-based
authenticated variable. The expected return status is
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.3.29</td>
<td>0x20678b3e, 0xbcca, 0x4186, 0x84, 0xaf, 0x47, 0x16, 0xe7, 0xaf,
0xde, 0x85</td>
<td><strong>RT.SetVariable -</strong> The created time-based Auth
Variable should pass the data validation.</td>
<td>Call <strong>GetVariable</strong> to retrieve the Auth Variable, and
validate the Auth Variable data.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.30</td>
<td>0xaa6bf36f, 0xdae5, 0x43ed, 0x95, 0x4d, 0xc1, 0xc7, 0x97, 0x9d,
0x32, 0xa0</td>
<td><strong>RT.SetVariable -</strong> The second Call
<strong>SetVariable()</strong> with the same <strong>Data</strong>. The
return status is <strong>EFI_SECURITY_VIOLATION</strong>.</td>
<td>The second Call <strong>SetVariable()</strong> with the same
<strong>Data</strong>. The return status is
<strong>EFI_SECURITY_VIOLATION</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.3.31</td>
<td>0x2bc131ec, 0x0530, 0x4994, 0xbb, 0x81, 0x15, 0x35, 0x5c, 0xef,
0xe5, 0x88</td>
<td><strong>RT.SetVariable -</strong> Call
<strong>SetVariable()</strong>with modified/invalid
<strong>Data</strong>. The expected status is
<strong>EFI_SECURITY_VIOLATION</strong></td>
<td><p>Call <strong>SetVariable()</strong> with modified/invalid
<strong>Data.</strong> The expected status is
<strong>EFI_SECURITY_VIOLATION</strong></p>
<p>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.3.32</td>
<td>0x0e49b21e, 0x409c, 0x4502, 0x9e, 0xc6, 0x55, 0xfe, 0x85, 0xf8,
0x54, 0x95</td>
<td><strong>RT.SetVariable</strong> - Call
<strong>SetVariable()</strong> with new/valid <strong>Data</strong>. The
expected status is <strong>EFI_SUCCESS.</strong></td>
<td>Call <strong>SetVariable()</strong> with new/valid
<strong>Data</strong>. The expected status is
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.2.1.3.33</td>
<td>0xadabac45, 0x1e0d, 0x40b0, 0x9b, 0xd1, 0x8c, 0x3a, 0xd7, 0xfb,
0x69, 0xd6</td>
<td><strong>RT.SetVariable -</strong> The renewed time-based Auth
Variable should pass the data validation.</td>
<td>Call <strong>GetVariable</strong> to retrieve the renewed Auth
Variable, and validate the Auth Variable data.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.34</td>
<td>0x6339807b, 0x0741, 0x45c4, 0x81, 0xa8, 0xe2, 0xde, 0x5a, 0x0b,
0xfb, 0x55</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> with the old
<strong>Data</strong>/timestamp. The expected status is
<strong>EFI_SECURITY_VIOLATION.</strong></td>
<td>Call <strong>SetVariable()</strong> with the old
<strong>Data</strong>/timestamp. The expected status is
<strong>EFI_SECURITY_VIOLATION</strong></td>
</tr>
<tr class="even">
<td>5.2.1.3.35</td>
<td>0xa2d53dea, 0x8275, 0x4b9a, 0xbd, 0xa0, 0xac, 0x86, 0xfb, 0x4e,
0x0f, 0x30</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> with the <strong>Data</strong> signed by
another key, the expect status should be
<strong>EFI_SECURITY_VIOLATION</strong></td>
<td>Call <strong>SetVariable()</strong> with the <strong>Data</strong>
signed by another key, the expect status should be
<strong>EFI_SECURITY_VIOLATION</strong></td>
</tr>
<tr class="odd">
<td>5.2.1.3.36</td>
<td>0x28c7f0db, 0x2546, 0x4374, 0x8f, 0xf9, 0x75, 0x80, 0xc4, 0x68,
0x9b, 0x93</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> to do the append operation, the expect
status should be <strong>EFI_SUCCESS</strong></td>
<td>Call <strong>SetVariable()</strong> to do the append operation, the
expect status should be <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.2.1.3.37</td>
<td>0x1e87dbe9, 0x234b, 0x4c82, 0x8c, 0x86, 0x2f, 0x26, 0xfa, 0xc6,
0x60, 0x2e</td>
<td><strong>RT.SetVariable –</strong>The appended time base Auth
Variable should pass the data validation</td>
<td>Call <strong>GetVariable()</strong> to retrieve the appended Auth
Variable, and validate the Auth Variable data.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.38</td>
<td>0x3cc4add2, 0x0ed7, 0x4837, 0xb4, 0x63, 0xbc, 0x46, 0xd1, 0x3b,
0x2f, 0x65</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> to do the delete operation. The expected
status is <strong>EFI_SUCCESS</strong></td>
<td>Call <strong>SetVariable()</strong> to do the delete operation. The
expected status is <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="even">
<td>5.2.1.3.39</td>
<td>0xfa50a705, 0x5d95, 0x4cad, 0xb4, 0x6c, 0xa0, 0x12, 0x9b, 0x68,
0x22, 0x8e</td>
<td><strong>RT.SetVariable –</strong>The deleted time-based Auth
Variable should not be found.</td>
<td>Call <strong>GetVariable()</strong> to retrieve the deleted Auth
Variable. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.40</td>
<td>0x27e8e4de, 0x56ed, 0x4710, 0xa6, 0x3a, 0xc6, 0x35, 0xe3, 0x9d,
0x33, 0x64</td>
<td><p><strong>RT.SetVariable -</strong> must</p>
<p>return <strong>EFI_SUCCESS</strong> when creating a time-based Auth
Variable with one different key.</p></td>
<td>Call <strong>SetVariable()</strong>to create a time-based Auth
Variable with one different key. The expected return status is
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.3.41</td>
<td>0xba99e7f8, 0x8018, 0x46a2, 0xb2, 0xe5, 0x8b, 0xde, 0x42, 0xc1,
0xe6, 0xd5</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> to do the append operation with the new
data. The expected status is <strong>EFI_SUCCESS</strong></td>
<td>Call <strong>SetVariable()</strong> to do the append operation with
the new data. The expected status is <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="odd">
<td>5.2.1.3.42</td>
<td>0xc764906d, 0x73bb, 0x44b7, 0xae, 0x40, 0x0c, 0x51, 0xde, 0xc3,
0xc7, 0x51</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> to set the <strong>Data</strong> with one
old timestamp. The return status should be
<strong>EFI_SECURITY_VIOLATION</strong></td>
<td>Call <strong>SetVariable()</strong> to set the <strong>Data</strong>
with one old timestamp. The return status should be
<strong>EFI_SECURITY_VIOLATION</strong></td>
</tr>
<tr class="even">
<td>5.2.1.3.43</td>
<td>0x1a28fa01, 0x135c, 0x4aeb, 0xa1, 0xb4, 0x68, 0x6a, 0x0b, 0x53,
0xb2, 0x9</td>
<td><strong>RT.SetVariable –</strong> call
<strong>SetVariable()</strong> to do the delete operation. The expected
status is <strong>EFI_SUCCESS</strong></td>
<td>Call <strong>SetVariable()</strong> to do the delete operation. The
expected status is <strong>EFI_SUCCESS</strong></td>
</tr>
<tr class="odd">
<td>5.2.1.3.44</td>
<td><p>0xe9893bcb,</p>
<p>0xef2b, 0x495c,</p>
<p>0x82, 0xf0,</p>
<p>0xd0, 0x63, 0x0d, 0xa7, 0x94, 0x76</p></td>
<td><p><strong>RT.SetVariable –</strong> must return</p>
<p><strong>EFI_SECURITY_VIOLATION</strong></p></td>
<td>Call <strong>SetVariable()</strong>to enroll an invalid time-based
authenticated variable but several bits changed.</td>
</tr>
<tr class="even">
<td>5.2.1.3.45</td>
<td><p>0x2534abc0,</p>
<p>0x1f01, 0x48a0,</p>
<p>0x96, 0xde,</p>
<p>0xf8, 0xbb,</p>
<p>0xa7, 0x45,</p>
<p>0xc3, 0x64</p></td>
<td><p><strong>RT.SetVariable –</strong> must return</p>
<p><strong>EFI_SECURITY_VIOLATION</strong></p></td>
<td>Call <strong>SetVariable()</strong> to enroll a time-based
authenticated variable with an invalid attribute.</td>
</tr>
<tr class="odd">
<td>5.2.1.3.46</td>
<td>0x896f8325, 0xed28, 0x4af5, 0x96, 0xba, 0x3b, 0xe3, 0xf2, 0x97,
0x74, 0x8b</td>
<td><p>RT.SetVariable –</p>
<p><strong>SetVariable()</strong> returns</p>
<p>EFI_INVALID_PARAMETER</p>
<p>When it wants to change the attribute of one existed variable</p>
<p>.</p></td>
<td><p>1. Call <strong>SetVariable()</strong></p>
<p>service to modify the attribute of one existed variable.</p>
<p>The returned status should be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>

### QueryVariableInfo()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
<col style="width: 32%" />
<col style="width: 33%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.2.1.4.1</td>
<td>0xad9578bf, 0x7a02, 0x4ef0, 0x8f, 0xe8, 0xd9, 0x45, 0x91, 0xa1,
0xe9, 0x31</td>
<td><strong>RT.QueryVariableInfo –</strong>Query variable info with a
<em><strong>MaximumVariableStorageSize</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>QueryVariableInfo</strong> service with a
<em><strong>MaximumVariableStorageSize</strong></em> value of
<strong>NULL</strong>. The returned code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.4.2</td>
<td>0x5d13a732, 0x60ea, 0x42d5, 0xa0, 0x01, 0x43, 0x63, 0xd9, 0xb1,
0x8b, 0xf4</td>
<td><strong>RT.QueryVariableInfo –</strong>Query variable info with a
<em><strong>RemainingVariableStorageSize</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>QueryVariableInfo</strong> service with a
<em><strong>RemainingVariableStorageSize</strong></em> value of
<strong>NULL</strong>. The returned code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.4.3</td>
<td>0xd3247b73, 0x5eb9, 0x4594, 0x8a, 0xb3, 0x27, 0xd9, 0x38, 0x4f,
0x3f, 0x13</td>
<td><strong>RT.QueryVariableInfo –</strong>Query variable info with
<em><strong>MaximumVariableSize</strong></em> value of
<strong>NULL</strong>.</td>
<td>1. Call <strong>QueryVariableInfo</strong> service with a
<em><strong>MaximumVariableSize</strong></em> value of
<strong>NULL</strong>. The returned code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.1.4.4</td>
<td>0xe7f2eb9f, 0x1624, 0x45a9, 0xa2, 0x87, 0x3e, 0xa6, 0xf2, 0xf7,
0x4c, 0x5f</td>
<td><p><strong>RT.QueryVariableInfo –</strong>Query variable info when
<em><strong>Attributes</strong></em> is not a combination of
<strong>EFI_VARIABLE_RUNTIME_ACCESS</strong></p>
<p>, <strong>EFI_VARIABLE_BOOTSERVICE_ACCESS</strong></p>
<p>and <strong>EFI_VARIABLE_NON_VOLATILE.</strong></p></td>
<td>1. Call <strong>QueryVariableInfo</strong> service with
<em><strong>Attributes</strong></em> values of 0. The returned code must
be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.2.1.4.5</td>
<td>0x2f9966ba, 0x0091, 0x4085, 0xbf, 0x9d, 0x09, 0xaa, 0x80, 0x9f,
0x94, 0x2e</td>
<td><strong>RT.QueryVariableInfo –</strong>Query variable info with an
invalid combination of <em><strong>Attributes</strong></em>.</td>
<td><p>1. Call <strong>QueryVariableInfo</strong> service with the
<em><strong>Attributes</strong></em>:</p>
<p><strong>EFI_VARIABLE_NON_VOLATILE</strong></p>
<p><strong>EFI_VARIABLE_RUNTIME_ACCESS</strong></p>
<p><strong>EFI_VARIABLE_NON_VOLATILE|EFI_VARIABLE_RUNTIME_ACCESS</strong></p>
<p>The returned code must be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="odd">
<td>5.2.1.4.8</td>
<td>0xad6e6a8f, 0x3a05, 0x4183,0xb6, 0x90, 0x40, 0xa8, 0x91, 0xd8, 0x62,
0xae</td>
<td><strong>RT.QueryVariableInfo –</strong> Query variable info with a
valid <em><strong>Attributes</strong></em> in Run time.</td>
<td><p>For each TPL less than or equal to <strong>TPL_CALLBACK</strong>
and each <em><strong>Attributes</strong></em> of <strong>BA, NV|BA,
BA|RA</strong> and <strong>NV|BA|RA</strong> do:</p>
<p>1. Call <strong>QueryVariableInfo</strong> with the
<em><strong>Attributes</strong></em> selected. Check.(Number1)</p>
<p>2. Call <strong>SetVariable</strong> service to insert a variable.
Check.</p>
<p>3. Call <strong>QueryVariableInfo</strong> with the
<em><strong>Attributes</strong></em> selected. Check. (Number2)</p>
<p>4. Call <strong>SetVariable</strong> service to delete the variable
inserted. Check.</p>
<p>5. Call <strong>QueryVariableInfo</strong> service with the
<em><strong>Attributes</strong></em> selected. Check.(Number3)</p>
<p>For Number1, Number2, Number3, the following items need to be
checked:</p>
<p>1. returned codes must be <strong>EFI_SUCCESS</strong>.</p>
<p>2. returned <strong>*MaximumVariableStorageSize</strong> must be the
same.</p>
<p>3. returned <strong>*MaximumVariableSize</strong> must be the same,
and they all are equal to <strong>MAX_VARIABLE_SIZE</strong>.</p>
<p>4. Number2 returned <strong>*RemainingVariableStorageSize</strong>
must be the value of Number1 minus the size of the variable inserted in
step 2.</p>
<p>5. Number3 returned <strong>*RemainingVariableStorageSize</strong>
must be the value of Number1</p></td>
</tr>
</tbody>
</table>


### HardwareErrorRecord

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
<col style="width: 32%" />
<col style="width: 32%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>5.2.1.5.1</td>
<td>0xc8126edc, 0x7197, 0x4113, 0xb7, 0xb6, 0xd5, 0x3d, 0x53, 0xe6,
0x72, 0xea</td>
<td><strong>HWErrRecTest – Func Test</strong></td>
<td><p>1. Call <strong>GetVariable()</strong> to check the
<strong>HardwareErrorRecord</strong> support of platform.</p>
<p>2. Call <strong>QueryVariableInfo()</strong> to detect the storage
size.</p>
<p>3. Get a useable <strong>HWErrRec</strong> variable name and call
<strong>SetVariable()</strong> to set it with data.</p>
<p>4. Reset system, call <strong>GetVariable()</strong> to get the
data.</p>
<p>5. Compare the data, they should be same.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.5.2</td>
<td>0xd8bd5c0a, 0x192f, 0x4501, 0xbc, 0x58, 0x89, 0xd3, 0x18, 0x60,
0x24, 0x5e</td>
<td><strong>HWErrRecTest – Conf Test</strong> HardwareErrorRecord with
invalid attributes.</td>
<td><p>1. Call <strong>GetVariable()</strong> to check the
<strong>HardwareErrorRecord</strong> support of platform.</p>
<p>2. Call <strong>QueryVariableInfo()</strong> to detect the storage
size.</p>
<p>3. Get a useable <strong>HWErrRec</strong> variable name and call
<strong>SetVariable()</strong> to set it with invalid attributes. The
returned code must be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.1.5.3</td>
<td>0xe1259932, 0xf39c, 0x465b, 0xb4, 0xe3, 0xa1, 0xb2, 0x77, 0x8b,
0xa1, 0x04</td>
<td><strong>HWErrRecTest – Conf Test</strong> HardwareErrorRecord with
twice deletion.</td>
<td><p>1. Call <strong>GetVariable()</strong> to check the
<strong>HardwareErrorRecord</strong> support of platform.</p>
<p>2. Call <strong>QueryVariableInfo()</strong> to detect the storage
size.</p>
<p>3. Get a useable <strong>HWErrRec</strong> variable name and call
<strong>SetVariable()</strong> to set it.</p>
<p>4. Delete the variable twice. The first time, the returned code must
be <strong>EFI_SUCCESS;</strong> the second time, the returned code must
be <strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.1.5.4</td>
<td>0xf5b942c9, 0x1f0c, 0x4c45, 0x85, 0x72, 0xc4, 0x53,
0x79, 0x51, 0x50, 0xdf</td>
<td><strong>HWErrRecTest – ConfTest </strong>
Retrive the Hardware Error Record variables, check
the name of them.</td>
<td><p>1. Call <strong>GetVariable()</strong> to check the HardwareErrorRecord support of platform.</p>
<p>2. Call <strong>QueryVariableInfo()</strong> to detect the storage size.</p>
<p>3. Retrive the Hardware Error Record variables, check
the name of them</p></td>
</tr>
</tbody>
</table>


## Time Services Test

**Reference Document:**

*UEFI Specification,* Time Services Section

- Time Services Functions

| Name | Type | Description |
|----|----|----|
| GetTime | Runtime | Returns the current time and date, and the time-keeping capabilities of the platform. |
| SetTime | Runtime | Sets the current local time and date information. |
| GetWakeupTime | Runtime | Returns the current wakeup alarm clock setting. |
| SetWakeupTime | Runtime | Sets the system wakeup alarm clock time. |

### GetTime()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.2.2.1.1 | 0x105de1dc, 0x32b2, 0x4d85, 0x9b, 0x30, 0xd4, 0x41, 0x80, 0x0f, 0xdc, 0x4c | **RT.GetTime – GetTime()** returns **EFI_INVALID_PARAMETER** with ***Time*** is **NULL**. | 1\. Call **GetTime()** with ***Time*** is **NULL**. The return code must be **EFI_INVALID_PARAMETER**. |
| 5.2.2.1.2 | 0x51437f55, 0x25e1, 0x43eb, 0xae, 0x76, 0x0d, 0x32, 0x1c, 0x12, 0xf6, 0x38 | **RT.GetTime – GetTime()** gets the system time at **EFI_TPL_APPLICATION**. | 1\. Call **GetTime()** with valid parameters. The return code must be **EFI_SUCCESS**. |
| 5.2.2.1.3 | 0x1a6e41f0, 0x361e, 0x4c46, 0xa2, 0xc4, 0x35, 0x42, 0xb3, 0x6f, 0xa5, 0xb6 | **RT.GetTime – GetTime()** gets the system time at **EFI_TPL_CALLBACK**. | 1\. Call **GetTime()** with valid parameters. The return code must be **EFI_SUCCESS**. |
| 5.2.2.1.4 | 0x3568b497, 0x6524, 0x4415, 0xac, 0xaa, 0xa8, 0xee, 0x24, 0x83, 0x9b, 0xdd | **RT.GetTime – GetTime()** gets the system time at **EFI_TPL_APPLICATION**. | 1\. Call **GetTime()** with valid parameters. The return time should be valid. |
| 5.2.2.1.5 | 0xa2c13016, 0x01d4, 0x4ea7, 0xb0, 0x8e, 0xb7, 0x74, 0x22, 0x4d, 0x7e, 0xa5 | **RT.GetTime – GetTime()** gets the system time at **EFI_TPL_CALLBACK**. | 1\. Call **GetTime()** with valid parameters. The return time should be valid. |
| 5.2.2.1.6 | 0x2cd14974, 0x4937, 0x4817, 0x91, 0xb0, 0x82, 0x2f, 0x40, 0xca, 0x22, 0xbc | **RT.GetTime – GetTime()** gets the system time with ***Capabilities*** is **NULL** at **EFI_TPL_APPLICATION**. | 1\. Call **GetTime()** with a ***Capabilities*** value of **NULL**. The return code should be **EFI_SUCCESS**. |
| 5.2.2.1.7 | 0x9bbabc14, 0xced2, 0x48fc, 0xbb, 0x9e, 0x79, 0x37, 0x49, 0xe8, 0x1f, 0xe2 | **RT.GetTime – GetTime()** gets the system time with ***Capabilities*** is **NULL** at **EFI_TPL_CALLBACK**. | 1\. Call **GetTime()** with a ***Capabilities*** value of **NULL**. The return code should be **EFI_SUCCESS**. |
| 5.2.2.1.8 | 0x938366e9, 0x3311, 0x4007, 0x87, 0xc3, 0xa2, 0x18, 0x7f, 0x05, 0x14, 0xe3 | **RT.GetTime – GetTime()** gets the system time with ***Capabilities*** is **NULL** at **EFI_TPL_APPLICATION**. | 1\. Call **GetTime()** with a ***Capabilities*** value of **NULL**. The return time should be valid. |
| 5.2.2.1.9 | 0x565f4b15, 0xb132, 0x4c74, 0x97, 0xc2, 0xf3, 0xa6, 0xf5, 0xbf, 0xd2, 0x21 | **RT.GetTime – GetTime()** gets the system time with ***Capabilities*** is **NULL** at **EFI_TPL_CALLBACK**. | 1\. Call **GetTime()** with a ***Capabilities*** value of **NULL**. The return time should be valid. |


### SetTime()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
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
<td>5.2.2.2.1</td>
<td>0x6f96cde3, 0x6067, 0x4213, 0x81, 0xf8, 0x45, 0x90, 0x1d, 0x92,
0x1a, 0x12</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Year</strong></em> is 1899. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.2</td>
<td>0x8ce9f594, 0x2d49, 0x4436, 0xb1, 0xd1, 0xe4, 0xd4, 0xbf, 0x55,
0x41, 0xdc</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Year</strong></em> is 10000. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.3</td>
<td>0x972fadc8, 0x5cc4, 0x4cbe, 0xbe, 0xd6, 0x76, 0xca, 0xef, 0x2d,
0x1b, 0x1a</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Year</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.4</td>
<td>0xcaac8a85, 0x26c2, 0x43e7, 0x83, 0x40, 0x5a, 0x78, 0x85, 0x43,
0xef, 0x81</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Month</strong></em> is 0. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.5</td>
<td>0x12470ee0, 0x19e1, 0x49ff, 0xbc, 0x1e, 0x8e, 0xb3, 0x6f, 0xab,
0xf0, 0xfc</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Month</strong></em> is 13. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.6</td>
<td>0xae7293c9, 0x0cbd, 0x4317, 0xb6, 0xeb, 0x33, 0xe1, 0x83, 0x46,
0x8d, 0x9e</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Month</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.7</td>
<td>0xb8048c3c, 0xbf1f, 0x477d, 0xb7, 0x17, 0x55, 0x41, 0xfc, 0xa7,
0xb5, 0x61</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Day</strong></em> is 0. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.8</td>
<td>0x0d2c6265, 0xad3a, 0x4554, 0xb0, 0x16, 0x6c, 0xb7, 0xff, 0x59,
0x1f, 0x78</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Day</strong></em> is 32. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.9</td>
<td>0x0467b0c4, 0xdf8c, 0x4bfc, 0xa8, 0x4b, 0xef, 0xa6, 0x90, 0x5b,
0xde, 0xd9</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Day</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.10</td>
<td>0x1e433b44, 0xa599, 0x4dcd, 0x9c, 0x38, 0xe7, 0xc0, 0x97, 0xf2,
0x56, 0x4b</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Month</strong></em> is 4 and
<em><strong>Time.Day</strong></em> is 31. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.11</td>
<td>0xc9bfb088, 0x07ba, 0x413c, 0xa4, 0x72, 0xbd, 0x17, 0x92, 0xdd,
0xc6, 0xec</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Hour</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Hour</strong></em> is 24. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.12</td>
<td>0xd7b3ca07, 0xa484, 0x4604, 0x83, 0x37, 0x6f, 0x13, 0x4f, 0x88,
0xb3, 0x5a</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Hour</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Hour</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.13</td>
<td>0xc645baaa, 0x3eb6, 0x4577, 0x97, 0x5d, 0x21, 0x05, 0x04, 0x83,
0x64, 0x2b</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Minute</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Minute</strong></em> is 60. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.14</td>
<td>0xa42f7c8e, 0xfa7a, 0x4026, 0xb9, 0x6b, 0x66, 0xe3, 0xf2, 0xe9,
0x93, 0x55</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Minute</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Minute</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.15</td>
<td>0xd37d5f03, 0x6dbb, 0x4724, 0x9e, 0xc1, 0xed, 0x13, 0x6b, 0x17,
0x22, 0xe9</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Second</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Second</strong></em> is 60. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.16</td>
<td>0xcd47c7aa, 0x6522, 0x45ed, 0xa7, 0xb4, 0x29, 0x6d, 0x57, 0x43,
0xc7, 0x78</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Second</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Second</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.17</td>
<td>0x14bccf9f, 0xda75, 0x46db, 0xb1, 0xfc, 0x7e, 0x67, 0x3b, 0x37,
0x25, 0x6e</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Nanosecond</strong></em> is greater than the upper
range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Nanosecond</strong></em> is 1000000000. The return code
must be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.18</td>
<td>0x966cf8d6, 0xf952, 0x4770, 0xa1, 0x9e, 0xf8, 0x78, 0xbc, 0x60,
0xbc, 0xeb</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Nanosecond</strong></em> is invalid.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.Nanosecond</strong></em> is -1. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.19</td>
<td>0x59a9febb, 0xf6d1, 0x4b13, 0xae, 0xcd, 0xf3, 0x65, 0xc2, 0x11,
0xa4, 0xed</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>TimeZone</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.TimeZone</strong></em> is -1441. The return code must
be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.20</td>
<td>0x5786f2c1, 0x48a7, 0x4856, 0x89, 0xe7, 0xba, 0xce, 0xc0, 0x85,
0xf3, 0xf9</td>
<td><strong>RT.SetTime - SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>TimeZone</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time.TimeZone</strong></em> is 1441. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.21</td>
<td>0xd3a1cbdd, 0x1df5, 0x4d24, 0x97, 0x53, 0xc3, 0xae, 0xa2, 0x7a,
0xab, 0x46</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid leap day.</td>
<td>1. Call <strong>SetTime()</strong> with
<em><strong>Time</strong></em> is 2001/2/29. The return code must be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.22</td>
<td>0x29151ae4, 0x7a5e, 0x42d9, 0x84, 0xf8, 0xe9, 0xc5, 0x67, 0x87,
0xb7, 0xe8</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Year</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Year</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.23</td>
<td>0x75e988ee, 0xec78, 0x4190, 0x9a, 0x09, 0xb1, 0x31, 0x5c, 0x20,
0x25, 0xa5</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Year</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Year</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.24</td>
<td>0x3b96a20c, 0x2b1f, 0x44ea, 0xba, 0xa9, 0xf9, 0x6f, 0xee, 0x13,
0x1d, 0x05</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Year</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Year</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>Year</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="even">
<td>5.2.2.2.25</td>
<td>0xe664e1d7, 0xb733, 0x410d, 0xbc, 0x53, 0xd4, 0xcf, 0xf2, 0x46,
0x43, 0x55</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Year</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Year</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>Year</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.2.26</td>
<td>0x4e123824, 0x8636, 0x4426, 0x81, 0xe6, 0x16, 0x75, 0x62, 0x8c,
0xde, 0x69</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Month</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Month</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.27</td>
<td>0x8f0bfe23, 0xb6ec, 0x4ea2, 0x8e, 0x03, 0x0a, 0x7a, 0x5e, 0x36,
0x45, 0xb3</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Month</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Month</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.28</td>
<td>0x2d5cdbe5, 0x1055, 0x4ef6, 0x8e, 0x90, 0x0c, 0x99, 0x3f, 0x93,
0xf6, 0x98</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Month</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Month</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>Month</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="even">
<td>5.2.2.2.29</td>
<td>0xda4b19e7, 0xf605, 0x4fb9, 0xa1, 0x81, 0xcc, 0xd3, 0x35, 0x29,
0x0b, 0xfe</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>Month</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Month</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<strong>Month</strong>. The return <strong>Time</strong> should be set
before.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.2.30</td>
<td>0x7af90ce7, 0x1fed, 0x4101, 0x82, 0xdc, 0xcc, 0x63, 0x4c, 0xdf,
0x20, 0x4e</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the daylight at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Daylight</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.31</td>
<td>0xfa81d174, 0x5743, 0x485f, 0xb2, 0x48, 0xaa, 0xea, 0xdd, 0x7c,
0x1e, 0x51</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the daylight at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Daylight</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.32</td>
<td>0xb39bc904, 0x55e7, 0x4b9b, 0xb4, 0xd8, 0x27, 0x4a, 0xdd, 0x71,
0xd6, 0x25</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the daylight at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Daylight</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>Daylight</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="even">
<td>5.2.2.2.33</td>
<td>0x54daf29b, 0x48e6, 0x4fa4, 0xad, 0x00, 0xb8, 0xd6, 0x48, 0xaf,
0x7d, 0x88</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the daylight at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.Daylight</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>Daylight</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.2.34</td>
<td>0xcdbbda04, 0x4f7c, 0x4ba5, 0x8b, 0xcf, 0xc0, 0x50, 0xe5, 0xa9,
0x76, 0xc7</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>TimeZone</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.TimeZone</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.2.35</td>
<td>0xf749b4f1, 0x537d, 0x4ddf, 0x85, 0x45, 0xc0, 0xa4, 0x19, 0x93,
0xce, 0xe4</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>TimeZone</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.TimeZone</strong></em>. The return code should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.2.36</td>
<td>0xea99dec5, 0xb879, 0x4c8d, 0xbf, 0xd1, 0xf6, 0x3f, 0xe7, 0x58,
0x99, 0xbf</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>TimeZone</strong></em> at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.TimeZone</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>TimeZone</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="even">
<td>5.2.2.2.37</td>
<td>0xd9c645b9, 0x52de, 0x415c, 0xab, 0xdc, 0x72, 0x26, 0xce, 0x6a,
0x30, 0xb1</td>
<td><strong>RT.SetTime – SetTime()</strong> returns
<strong>EFI_SUCCESS</strong> to update the
<em><strong>TimeZone</strong></em> at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetTime()</strong> to update the
<em><strong>Time.TimeZone</strong></em>.</p>
<p>2. Call <strong>GetTime()</strong> to verify the updated
<em><strong>TimeZone</strong></em>. The return
<em><strong>Time</strong></em> should be set before.</p></td>
</tr>
</tbody>
</table>



### GetWakeupTime()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.2.2.3.1 | 0xbb9fd931, 0xd3c0, 0x43cd, 0xb0, 0xa7, 0xfe, 0x17, 0xdc, 0xd7, 0x4d, 0x53 | **RT.GetWakeupTime – GetWakeupTime()** returns **EFI_INVALID_PARAMETER** with ***Enabled*** is **NULL**. | 1\. Call **GetWakeupTime()** with ***Enabled*** is **NULL**. The return code must be **EFI_UNSUPPORTED** or **EFI_INVALID_PARAMETER**. |
| 5.2.2.3.2 | 0x200b6e00, 0x9e1b, 0x4891, 0x83, 0x01, 0xef, 0x46, 0x9f, 0x31, 0x17, 0x08 | **RT.GetWakeupTime – GetWakeupTime()** returns **EFI_INVALID_PARAMETER** with ***Pending*** is **NULL**. | 1\. Call **GetWakeupTime()** with ***Pending*** is **NULL**. The return code must be **EFI_UNSUPPORTED** or **EFI_INVALID_PARAMETER**. |
| 5.2.2.3.3 | 0x209435c5, 0xfa4f, 0x405d, 0x80, 0xa6, 0x9e, 0xdc, 0x9d, 0x38, 0x8c, 0xc6 | **RT.GetWakeupTime – GetWakeupTime()** returns **EFI_INVALID_PARAMETER** with ***Time*** is **NULL**. | 1\. Call **GetWakeupTime()** with ***Time*** is **NULL**. The return code must be **EFI_UNSUPPORTED** or **EFI_INVALID_PARAMETER**. |
| 5.2.2.3.4 | 0xe553c375, 0xd529, 0x4610, 0xad, 0xb5, 0x3a, 0x56, 0xc3, 0xec, 0xcb, 0xe9 | **RT.GetWakeupTime – GetWakeupTime()** returns **EFI_SUCCESS** at **EFI_TPL_APPLICATION**. | 1\. Call **GetWakeupTime()** with valid parameters. The return code must be **EFI_UNSUPPORTED** or **EFI_SUCCESS**. |
| 5.2.2.3.5 | 0x36414d2a, 0xf932, 0x43ca, 0xab, 0x08, 0x41, 0x8e, 0x59, 0xd9, 0xa4, 0xa2 | **RT.GetWakeupTime – GetWakeupTime()** returns **EFI_SUCCESS** at **EFI_TPL_CALLBACK**. | 1\. Call **GetWakeupTime()** with valid parameters. The return code must be **EFI_UNSUPPORTED** or **EFI_SUCCESS**. |
| 5.2.2.3.6 | 0x6092de6c, 0x062f, 0x4adb, 0xab, 0x4b, 0xb4, 0xda, 0x69, 0xd2, 0x8e, 0xd8 | **RT.GetWakeupTime – GetWakeupTime()** gets the wakeup status at **EFI_TPL_APPLICATION**. | 1\. Call **GetWakeupTime()** with valid parameters. If the ***Enabled*** is **TRUE**, the return time should be valid. |
| 5.2.2.3.7 | 0x8061bae9, 0x341c, 0x48ab, 0xad, 0x37, 0x15, 0x5c, 0x6b, 0x0f, 0x13, 0x34 | **RT.GetWakeupTime – GetWakeupTime()** gets the wakeup status at **EFI_TPL_CALLBACK**. | 1\. Call **GetWakeupTime()** with valid parameters. If the ***Enabled*** is **TRUE**, the return time should be valid. |



### SetWakeupTime()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 19%" />
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
<td>5.2.2.4.1</td>
<td>0x41d27daf, 0xe088, 0x441c, 0xb2, 0x05, 0x6d, 0xd7, 0xa4, 0xac,
0x08, 0xb1</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Year</strong></em> is 1997. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.2</td>
<td>0xe2dbc697, 0xc56a, 0x4c58, 0xa2, 0x74, 0x58, 0x99, 0x94, 0x1c,
0x7e, 0x02</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Year</strong></em> is 2100. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.3</td>
<td>0x2ef795b9, 0xdfac, 0x4334, 0xa2, 0x43, 0x55, 0xbe, 0x0d, 0x0c,
0x3b, 0x44</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Year</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Year</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.4</td>
<td>0x8f7fe2f6, 0xd96d, 0x4765, 0x96, 0x42, 0x05, 0xae, 0x30, 0x66,
0xd8, 0xb9</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Month</strong></em> is 0. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.5</td>
<td>0xc398668f, 0x03c2, 0x4cac, 0x81, 0x18, 0x7c, 0xbe, 0xab, 0xd1,
0xb9, 0x67</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Month</strong></em> is 13. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.6</td>
<td>0x57a4eedd, 0xafa6, 0x4233, 0xb2, 0xeb, 0x79, 0xe4, 0x5e, 0x3d,
0xc0, 0x2d</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Month</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Month</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.7</td>
<td>0x61dd2e73, 0x0c29, 0x436a, 0x80, 0x73, 0x3c, 0xe4, 0xde, 0xc7,
0x0d, 0xf2</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Day</strong></em> is 0. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.8</td>
<td>0x7c532de7, 0x3d59, 0x4a43, 0x9c, 0xf1, 0x8c, 0x35, 0x51, 0x70,
0xbc, 0x86</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Day</strong></em> is 32. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.9</td>
<td>0xb07ea402, 0x8403, 0x4c42, 0xa4, 0x11, 0x23, 0x2c, 0x37, 0xf9,
0xc5, 0x27</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Day</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.10</td>
<td>0xc86e5f11, 0x2e97, 0x4cee, 0x9c, 0xc8, 0xd3, 0xf5, 0x7f, 0xa6,
0x46, 0x75</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Day</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<strong>Time.Month</strong> is 4 and <strong>Time.Day</strong> is 31.
The return code must be <strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.11</td>
<td>0x0ef3f79c, 0x9399, 0x47f8, 0xab, 0x3b, 0xa6, 0x6c, 0x2f, 0x78,
0x1f, 0x9e</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Hour</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Hour</strong></em> is 24. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.12</td>
<td>0x9f61f3ac, 0x059b, 0x4658, 0x98, 0x2d, 0x61, 0x6e, 0xab, 0x25,
0xcb, 0x6d</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Hour</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Hour</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.13</td>
<td>0xa05b10e8, 0x098e, 0x4c02, 0xad, 0x30, 0xef, 0xac, 0x58, 0xf4,
0x07, 0x56</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Minute</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Minute</strong></em> is 60. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.14</td>
<td>0xbca1c0cf, 0xe121, 0x42fc, 0xba, 0x49, 0x2b, 0xd0, 0xad, 0x74,
0x3d, 0x60</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Minute</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Minute</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.15</td>
<td>0x89c7e1f1, 0x98cb, 0x4f3c, 0x96, 0xc7, 0x03, 0x59, 0x22, 0xd0,
0xce, 0x34</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Second</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Second</strong></em> is 60. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.16</td>
<td>0x59b0d53d, 0xffac, 0x4c1a, 0xb9, 0xb0, 0x2c, 0xe6, 0xfc, 0x93,
0x8f, 0x0e</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Second</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Second</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.17</td>
<td>0x98737393, 0x45af, 0x4945, 0xa7, 0xd2, 0xe2, 0x92, 0xfd, 0x4e,
0x8d, 0x20</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Nanosecond</strong></em> is greater than the upper
range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Nanosecond</strong></em> is 1000000000. The return code
must be <strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.18</td>
<td>0xc9eff904, 0x5d44, 0x451c, 0x94, 0xd2, 0x66, 0x73, 0xe1, 0x8e,
0x65, 0x05</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>Nanosecond</strong></em> is invalid.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.Nanosecond</strong></em> is -1. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.19</td>
<td>0x4cf4b039, 0xf2aa, 0x4f8a, 0x9c, 0xec, 0x0a, 0x80, 0x2c, 0xea,
0xd7, 0x5f</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>TimeZone</strong></em> is less than the low range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.TimeZone</strong></em> is -1441. The return code must
be <strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.20</td>
<td>0xabd093eb, 0x7d84, 0x4ebc, 0xb3, 0x24, 0xc2, 0x85, 0x79, 0x5b,
0xde, 0x34</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em><strong>TimeZone</strong></em> is greater than the upper range.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time.TimeZone</strong></em> is 1441. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.21</td>
<td>0x0fce1f4c, 0x41f6, 0x4de4, 0x80, 0xa7, 0x77, 0x14, 0xa0, 0x35,
0x6d, 0x9b</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid leap day.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Time</strong></em> is 2001/2/29. The return code must be
<strong>EFI_UNSUPPORTED</strong> or
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.22</td>
<td>0x4b660fec, 0xc2d0, 0x423f, 0xa3, 0x87, 0x07, 0x80, 0x41, 0xa1,
0x83, 0xb7</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters at
<strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with valid parameters. The
return code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.23</td>
<td>0x218d16a6, 0xf52a, 0x4e42, 0x80, 0x52, 0x1a, 0x4d, 0x5d, 0x4a,
0x19, 0x60</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters at
<strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with valid parameters. The
return code should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.24</td>
<td>0x0da0ec8a, 0xb748, 0x4c42, 0xa8, 0xc6, 0x71, 0x03, 0x75, 0x32,
0x90, 0x71</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Enabled</strong></em> should be
<strong>TRUE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.2.4.25</td>
<td>0x34aaf995, 0xd29b, 0x4892, 0xa4, 0x18, 0x99, 0x2c, 0xb0, 0xee,
0x29, 0xea</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Enabled</strong></em> should be
<strong>TRUE</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.4.26</td>
<td>0x49f3c56e, 0x013b, 0x4fa8, 0x8a, 0xb2, 0x17, 0x70, 0xd5, 0x37,
0x3d, 0x74</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Pending</strong></em> should be
<strong>FALSE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.2.4.27</td>
<td><p>0xb39225e6,</p>
<p>0x3d06, 0x401c, 0xad, 0x26, 0x3e, 0xa9, 0x23, 0x71, 0xf3,
0xdc</p></td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Pending</strong></em> should be
<strong>FALSE</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.4.28</td>
<td>0x6fd3d6d4, 0x2694, 0x4677, 0x87, 0x76, 0x3d, 0xd6, 0x2e, 0x3a,
0x8c, 0xa0</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="even">
<td>5.2.2.4.29</td>
<td>0xdf714d88, 0x9ee9, 0x4027, 0xa3, 0x70, 0xe5, 0xa2, 0x83, 0x56,
0x5c, 0xed</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> enables the
wakeup time at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with valid
parameters.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Time</strong></em> should be set before.</p></td>
</tr>
<tr class="odd">
<td>5.2.2.4.30</td>
<td>0xd3835a5c, 0xb4be, 0x4f6c, 0xab, 0xf0, 0x29, 0x52, 0x52, 0x37,
0x14, 0x06</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> disables the
wakeup time with <em><strong>Enable</strong></em> is
<strong>FALSE</strong> at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Enable</strong></em> is <strong>FALSE</strong>. The return
code must be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.2.2.4.31</td>
<td>0xeb8730ec, 0x578d, 0x41b1, 0xa2, 0xbe, 0x4a, 0x9f, 0xf6, 0x03,
0xdb, 0x22</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> disables the
wakeup time with <em><strong>Enable</strong></em> is
<strong>FALSE</strong> at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Enable</strong></em> is <strong>FALSE</strong>. The return
code must be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.2.2.4.32</td>
<td>0xffaa1029, 0x16ae, 0x4d5c, 0xba, 0x74, 0x86, 0x80, 0xf4, 0xba,
0x9c, 0xd0</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> disables the
wakeup time with <em><strong>Enable</strong></em> is
<strong>FALSE</strong> at <strong>EFI_TPL_APPLICATION</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Enable</strong></em> is <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Enabled</strong></em> must be
<strong>FALSE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.2.2.4.33</td>
<td>0x8a70609a, 0xab54, 0x475e, 0x8d, 0xf2, 0xc3, 0xf9, 0x11, 0x58,
0xc4, 0xa8</td>
<td><strong>RT.SetWakeupTime – SetWakeupTime()</strong> disables the
wakeup time with <em><strong>Enable</strong></em> is
<strong>FALSE</strong> at <strong>EFI_TPL_CALLBACK</strong>.</td>
<td><p>1. Call <strong>SetWakeupTime()</strong> with
<em><strong>Enable</strong></em> is <strong>FALSE</strong>.</p>
<p>2. Call <strong>GetWakeupTime()</strong> to get the wakeup time. The
return <em><strong>Enable</strong></em> must be
<strong>FALSE</strong>.</p></td>
</tr>
</tbody>
</table>


## Virtual Memory Services Test

**Reference Document:**

*UEFI Specification*, Virtual Memory Services Section.

- Virtual Memory Functions

| Name | Type | Description |
|----|----|----|
| SetVirtualAddressMap | Runtime | Used by an OS loader to convert from physical addressing to virtual addressing. |
| ConvertPointer | Runtime | Used by EFI components to convert internal pointers when switching to virtual addressing. |


No test case is designed to verify these functions in the EFI SCT.

## Misc Runtime Services Test

**Reference Document:**

*UEFI Specification*, Miscellaneous Runtime Services Section.

- Miscellaneous Runtime Services Functions

| Name | Type | Description |
|----|----|----|
| ResetSystem | Runtime | Reset the entire platform. |
| UpdateCapsule | Runtime | Passes capsules to the firmware with both virtual and physical mapping. |
| QueryCapsuleCapabilities | Runtime | Estimate if a capsule or capsules can be updated via UpdateCapsule() |
| GetNextHighMonotonicCount | Runtime | Returns the next high 32 bits of the platform’s monotonic counter. |

### ResetSystem()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.2.4.1.1 | 0x26feed7e, 0x1501, 0x4c0a, 0xae, 0xf3, 0x86, 0xd6, 0x6b, 0xe2, 0xfc, 0xd0 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetCold** at **EFI_TPL_APPLICATION**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetCold**. The system should be reset. |
| 5.2.4.1.2 | 0x567f8ee9, 0x4e5e, 0x4278, 0x86, 0x3d, 0xdb, 0xc4, 0xd7, 0x4f, 0x0f, 0xba | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetCold** at **EFI_TPL_CALLBACK**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetCold**. The system should be reset. |
| 5.2.4.1.3 | 0xb7a21919, 0xf358, 0x4a1d, 0x85, 0x26, 0xcc, 0x52, 0x4c, 0x52, 0x94, 0xb2 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetCold** at **EFI_TPL_NOTIFY**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetCold**. The system should be reset. |
| 5.2.4.1.4 | 0x7bbad1aa, 0x88b4, 0x4d66, 0x95, 0x94, 0xdb, 0x7e, 0x65, 0xe1, 0xd3, 0xa4 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetWarm** at **EFI_TPL_APPLICATION**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetWarm**. The system should be reset. |
| 5.2.4.1.5 | 0xdbe1128b, 0x5155, 0x4241, 0x84, 0x1e, 0x54, 0xea, 0x76, 0x3a, 0x85, 0xc9 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetWarm** at **EFI_TPL_CALLBACK**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetWarm**. The system should be reset. |
| 5.2.4.1.6 | 0x8128b536, 0x0b56, 0x480b, 0xa2, 0xd4, 0xcd, 0x79, 0xf8, 0xfa, 0xcb, 0x3b | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetWarm** at **EFI_TPL_NOTIFY**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetWarm**. The system should be reset. |
| 5.2.4.1.7 | 0x1189a0df, 0xe9cc, 0x45e6, 0xbb, 0x94, 0x21, 0xa7, 0xb3, 0x42, 0x70, 0x96 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetShutdown** at **EFI_TPL_APPLICATION**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetShutdown**. The system should be reset or shut down. |
| 5.2.4.1.8 | 0x22b8b295, 0x62a2, 0x4e14, 0xb8, 0x5b, 0xd2, 0xde, 0x36, 0x37, 0x15, 0xb5 | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetShutdown** at **EFI_TPL_CALLBACK**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetShutdown**. The system should be reset or shut down. |
| 5.2.4.1.9 | 0x1ed1babb, 0x6521, 0x4515, 0x93, 0x9a, 0x39, 0x26, 0xc8, 0xe3, 0x12, 0xff | **RT.ResetSystem – ResetSystem()** resets the platform with ***ResetType*** is **EfiResetShutdown** at **EFI_TPL_NOTIFY**. | 1\. Call **ResetSystem()** with a ***ResetType*** value of **EfiResetShutdown**. The system should be reset or shut down. |

### UpdateCapsule()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.2.4.2.1 | 0xf48a2ac4, 0xbce7, 0x4fa7, 0x9e, 0x1b, 0xb9, 0x6f, 0xf8, 0x60, 0xe3, 0x0a | **RT.UpdateCapsule –UpdateCapsule()** returns **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED** with ***CapsuleCount*** is **NULL**. | 1\. Call **UpdateCapsule()** with a ***CapsuleCount*** value of **NULL**. The return value should be **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED**. |
| 5.2.4.2.2 | 0x304f6960, 0x79d0, 0x4f17, 0x88, 0x11, 0x62, 0x0f, 0xc6, 0xbd, 0xb0, 0xd4 | **RT. UpdateCapsule–UpdateCapsule()** returns **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED** when a capsule has the **CAPSULE_FLAGS_PERSIST_ACROSS_RESET** in its header, but the ***ScatterGatherList*** is **NULL**. | 1\. Call **UpdateCapsule()** with ***ScatterGatherList*** is **NULL** and a capsule has the flag of **CAPSULE_FLAGS_PERSIST_ACROSS_RESET** in its header.The return value should be **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED**. |
| 5.2.4.2.3 | 0x18f86bf8, 0x76cf, 0x4225, 0x8e, 0x3e, 0x1b, 0x1f, 0x63, 0x43, 0x26, 0x00 | **RT.UpdateCapsule– UpdateCapsule()**returns **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED** when a capsule has the flag of **CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE** in its header only. | 1\. Call **UpdateCapsule()**when a capsule has the flag of **CAPSULE_FLAGS_POPULATE_SYSTEM_TABLE** in its header only. The return value should be **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED** |

### QueryCapsuleCapabilities()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.2.4.3.1 | 0x5b5f42d4, 0x8985, 0x45a0, 0x9d, 0xf2, 0x21, 0xaf, 0x74, 0xb1, 0xf5, 0xf6 | **RT.QueryCapsuleCapabilities– QueryCapsuleCapabilities()** query for generic capsule capability with a fake **EFI_CAPSULE_HEADER**. **CAPSULE_FLAGS_PERSIST_ACROSS_RESET** is set in the flags in the header. | 1\. Call **QueryCapsuleCapabilities()** with a fake **EFI_CAPSULE_HEADER.** The return value should be **EFI_SUCCESS** or **EFI_UNSUPPORTED**. |
| 5.2.4.3.2 | 0x13826168, 0xfef6, 0x407e, 0x93, 0x7c, 0x6d, 0x5e, 0x32, 0x34, 0x9d, 0x5c | **RT.QueryCapsuleCapabilities–QueryCapsuleCapabilities()** query for generic capsule capability with a fake **EFI_CAPSULE_HEADER**. **0** is set in the flags in the header. | 1\. Call **QueryCapsuleCapabilities()** with a fake **EFI_CAPSULE_HEADER.** The return value should be **EFI_SUCCESS** or **EFI_UNSUPPORTED**. |
| 5.2.4.3.3 | 0x67c3c36d, 0x4cf8, 0x41fb, 0xa7, 0x8a, 0x86, 0x36, 0x84, 0xe9, 0xe6, 0xe4 | **RT.QueryCapsuleCapabilities– QueryCapsuleCapabilities()**query for generic capsule capability with ***MaximumCapsuleSize*** is **NULL**. | 1\. Call **QueryCapsuleCapabilities()** with ***MaximumCapsuleSize*** is **NULL**. The return value should be **EFI_INVALID_PARAMETER** or **EFI_UNSUPPORTED** |

### GetNextHighMonotonicCount()

This function may only be available in Runtime. No test case is designed
to verify it.