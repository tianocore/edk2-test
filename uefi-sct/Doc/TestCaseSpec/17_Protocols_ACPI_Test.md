# Protocols ACPI Test

## EFI_ACPI_TABLE_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_ACPI_TABLE_PROTOCOL Section.

### InstallAcpiTable ()

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
<td>5.16.1.1.1</td>
<td>0x278963cf, 0x0c77, 0x47b5, 0xa9, 0x1f, 0x2b, 0xa7, 0xde, 0x9d,
0xa3, 0x75</td>
<td><strong>ACPI_TABLE_PROTOCOL.InstallAcpiTable -
InstallAcpiTable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>NULL</strong>
AcpiTableBuffer.</td>
<td>Call <strong>InstallAcpiTable()</strong> with <strong>NULL
AcpiTableBuffer</strong>. The return status should be
<strong>EFi_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.16.1.1.2</td>
<td>0xa3f1e4b1, 0xe8d9, 0x4516, 0xa2, 0xbc, 0x3d, 0xef, 0x20, 0x15,
0xec, 0x7d</td>
<td><strong>ACPI_TABLE_PROTOCOL.InstallAcpiTable -
InstallAcpiTable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>NULL</strong>
TableKey.</td>
<td>Call <strong>InstallAcpiTable()</strong> with <strong>NULL
TableKey</strong>. The return status should be
<strong>EFi_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.16.1.1.3</td>
<td>0xb03fa7b4, 0xeb94, 0x4f56, 0x8a, 0x69, 0x5a, 0x13, 0x59, 0xcf,
0x57, 0x3f</td>
<td><strong>ACPI_TABLE_PROTOCOL.InstallAcpiTable -
InstallAcpiTable()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with AcpiTableBufferSize is
different with the size field in AcpiTableBuffer.</td>
<td>Call <strong>InstallAcpiTable()</strong> with the size of
<strong>AcpiTableBuffer</strong> not the same as the
<strong>AcpiTableBufferSize</strong>. The return status should be
<strong>EFi_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.16.1.1.4</td>
<td>0x40949ceb, 0x734b, 0x468d, 0x88, 0xca, 0xfe, 0xc2, 0x7e, 0x4c,
0x19, 0xd2</td>
<td><strong>ACPI_TABLE_PROTOCOL.InstallAcpiTable -
InstallAcpiTable()</strong> returns <strong>EFI_SUCCESS</strong> with
valid parameters</td>
<td><p>Call <strong>InstallAcpiTable()</strong> with valid parameter.
The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UninstallAcpiTable()</strong> to restore the
environment.</p></td>
</tr>
<tr class="even">
<td>5.16.1.1.5</td>
<td>0xfd58070a, 0xcefe, 0x4aea, 0x90, 0x3b, 0xa7, 0xa9, 0xbe, 0x53,
0x9c, 0xaf</td>
<td><p><strong>ACPI_TABLE_PROTO COL.InstallAcpiTable-</strong></p>
<p><strong>InstallAcpiTable()</strong>returns
<strong>EFI_SUCCESS</strong> and automatically correct
<strong>AcpiTable</strong> checksum</p></td>
<td><p>1. Call <strong>InstallAcpiTable()</strong> with
<strong>AcpiTable</strong> with wrong checksum.</p>
<p>2. The return status should be</p>
<p><strong>EFI_SUCCESS</strong> &amp; <strong>AcpiTable</strong>
checksum corrected.</p>
<p>3. Call <strong>UninstallAcpiTable()</strong> to restore the
environment.</p></td>
</tr>
</tbody>
</table>


### UninstallAcpiTable ()

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
<td>5.16.1.2.1</td>
<td>0x5c72198c, 0x74d2, 0x4c55, 0xb9, 0xcf, 0x17, 0xdc, 0x02, 0x30,
0xac, 0x71</td>
<td><strong>ACPI_TABLE_PROTOCOL.UninstallAcpiTable -
UninstallAcpiTable()</strong> returns <strong>EFI_NOT_FOUND</strong>
with <strong>TableKey</strong> not refer to a table entry.</td>
<td><p>Call <strong>InstallAcpiTable()</strong> with valid parameter.
The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UninstallAcpiTable()</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UninstallAcpiTable()</strong> again. The return status
should <strong>EFI_NOT_FOUND</strong>..</p></td>
</tr>
<tr class="odd">
<td>5.16.1.2.2</td>
<td>0xf1c7de32, 0xd0fe, 0x4d67, 0xb0, 0x28, 0x06, 0xb4, 0xa0, 0x84,
0x06, 0xc4</td>
<td><strong>ACPI_TABLE_PROTOCOL.UninstallAcpiTable -
UninstallAcpiTable()</strong> returns <strong>EFI_SUCCESS</strong> with
<strong>TableKey</strong> refer to a table entry.</td>
<td><p>Call <strong>InstallAcpiTable()</strong> with valid parameter.
The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Call <strong>UninstallAcpiTable()</strong>. The return status should
be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>

