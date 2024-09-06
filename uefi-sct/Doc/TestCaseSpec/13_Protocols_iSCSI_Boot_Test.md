# Protocols iSCSI Boot Test

EFI_ISCSI_INITIATOR_NAME_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_ISCSI_INITIATOR_NAME_PROTOCOL Section.

## EFI_ISCSI_INITIATOR_NAME_PROTOCOL Function Test

### Get() Function

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 13%" />
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
<td>5.17.1.1.1</td>
<td>0xed92f3eb, 0xdda4, 0x4c65, 0xb3, 0x9f, 0x6c, 0x90, 0xfb, 0x2e,
0x77, 0xf9</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get</strong> – Calling
<strong>Get()</strong>returns <strong>EFI_SUCCESS.</strong></td>
<td><p>Call <strong>Get()</strong> with a valid <em>BufferSize</em>
value.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



### Set() Function

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 13%" />
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
<td>5.17.1.2.1</td>
<td>0x56cd69be, 0xcfea, 0x4a43, 0xae, 0x1a, 0x41, 0xe4, 0xde, 0x78,
0x83, 0xc8</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set</strong> – Calling
<strong>Set()</strong>returns <strong>EFI_SUCCESS.</strong></td>
<td><p>Call <strong>Set()</strong> with valid <em>BufferSize</em> and
<em>Buffer</em> values.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



## EFI_ISCSI_INITIATOR_NAME_PROTOCOL Conformance Test

### Get() Conformance

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
<td>5.17.2.1.1</td>
<td>0x4c893a1c, 0x9c28, 0x4038, 0x9a, 0x34, 0xce, 0xe3, 0x15, 0x70,
0xc4, 0xa6</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get</strong> – Calling
<strong>Get()</strong> should return <strong>EFI_SUCCESS</strong> with
valid parameters.</td>
<td><p>Call <strong>Get()</strong> with valid parameters.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.17.2.1.2</td>
<td>0x5f4d6864, 0xe8ed, 0x452e, 0xb2, 0xbc, 0x9a, 0x0e, 0x06, 0x61,
0x7e, 0x3a</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get</strong> – Calling
<strong>Get()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with a <em>BufferSize</em> or
<em>Buffer</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>Get()</strong>with a <em>BufferSize</em> value of
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>2. Call <strong>Get()</strong> with a <em>Buffer</em> value of
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="even">
<td>5.17.2.1.3</td>
<td>0x2502087d, 0xd853, 0x494e, 0xbd, 0xc5, 0x8b, 0x1a, 0xc1, 0x26,
0xd4, 0x61</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get</strong> – Calling
<strong>Get()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with a <em>BufferSize</em> value
that is too small.</td>
<td><p>Call <strong>Get()</strong>with a <em>BufferSize</em> that is too
small.</p>
<p>The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
</tbody>
</table>


### Set() Conformance

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
<td>5.17.2.2.1</td>
<td>0x5bd1c13e, 0x1b9c, 0x432f, 0xb9, 0x33, 0xd9, 0xcf, 0x6f, 0xac,
0xd4, 0x2d</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set</strong> – Calling
<strong>Set()</strong> should return <strong>EFI_SUCCESS</strong> with
valid parameters.</td>
<td><p>Call <strong>Set()</strong> with valid parameters.</p>
<p>The return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.17.2.2.2</td>
<td>0xacb61cfd, 0xe82b, 0x4250, 0xb0, 0x60, 0xdb, 0x18, 0x55, 0x9e,
0x58, 0xb1</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Set</strong> – Calling
<strong>Set()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with a <em>BufferSize</em> or
<em>Buffer</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call <strong>Set()</strong>with a <em>BufferSize</em> value of
<strong>NULL</strong>. The return should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>2. Call <strong>Set()</strong> with a <em>Buffer</em> value of
<strong>NULL</strong>. The return should be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="even">
<td>5.17.2.2.3</td>
<td>0xdc419b8e, 0xb074, 0x4388, 0xbb, 0x85, 0xc8, 0xed, 0xa0, 0x19,
0x95, 0xd3</td>
<td><strong>EFI_ISCSI_INITIATOR_NAME_PROTOCOL.Get</strong> – Calling
<strong>Get()</strong> should return
<strong>EFI_INVALID_PARAMETER</strong> with a <em>BufferSize</em> value
that exceeds the maximum.</td>
<td><p>Call <strong>Get()</strong>with a <em>BufferSize</em> value that
exceeds the maximum.</p>
<p>The return should be <strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
</tbody>
</table>

