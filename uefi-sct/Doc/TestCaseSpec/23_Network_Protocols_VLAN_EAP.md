# Network Protocols VLAN and EAP

## EFI_VLAN_CONFIG_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_VLAN_CONFIG_PROTOCOL Section.

### Set()

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
<td>5.27.1.1.1</td>
<td>0xedbb5f4f, 0x4de7, 0x43ff, 0x82, 0x1c, 0x13, 0x80, 0x98, 0x95,
0xd1, 0x76</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.SET - SET()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>VlanId</strong>.</td>
<td>Call <strong>Set()</strong> with valid parameters except an invalid
<strong>VlanId</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.1.2</td>
<td>0x9c1292c2, 0xe03a, 0x438d, 0x9d, 0xab, 0x4e, 0xd0, 0xa9, 0xa8,
0xb6, 0x83</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.SET - SET()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>Priority</strong>.</td>
<td>Call <strong>Set()</strong> with valid parameters except an invalid
<strong>Priority</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.27.1.1.3</td>
<td>0xe3584990, 0x0b04, 0x48ea, 0x96, 0x3d, 0x36, 0xf7, 0x62, 0x29,
0x9f, 0x42</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.SET - SET()</strong> returns
<strong>EFI_SUCCESS</strong> with a valid <strong>VlanId</strong> and a
valid <strong>Priority</strong>.</td>
<td><p>5.27.1.1.3 – 5.27.1.1.6 belong to one case</p>
<p>1. Call <strong>Set()</strong>with a valid <strong>VlanId</strong>
and a valid <strong>Priority</strong>, The return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.27.1.1.4</td>
<td>0xc14eb533, 0xc076, 0x4a9e, 0xb5, 0x6d, 0xea, 0x00, 0xce, 0xac,
0x7b, 0x2d</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_SUCCESS</strong> with the same <strong>VlanId</strong>, a
valid <strong>NumberOfVlan</strong> and a valid
<strong>Priority</strong>.</td>
<td>2. Call <strong>Find()</strong>with the same
<strong>VlanId</strong>, a valid <strong>NumberOfVlan</strong> and a
valid <strong>Priority</strong>. The return status should be
<strong>EFI_SUCCESS</strong>. The <strong>NumberOfVlan</strong> should
be 1. The output <strong>VlanId</strong> and <strong>Priority</strong>
in the <strong>Entries</strong> should be the same value of
<strong>VlanId</strong>/<strong>Priority</strong> which are set in
step1.</td>
</tr>
<tr class="even">
<td>5.27.1.1.5</td>
<td>0x48deb1ad, 0xd59b, 0x404e, 0x88, 0xe7, 0x42, 0x53, 0xac, 0x0e,
0xce, 0x22</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.SET - SET()</strong> returns
<strong>EFI_SUCCESS</strong> with the same <strong>VlanId</strong> and a
different <strong>Priority</strong>.</td>
<td>3. Call <strong>Set()</strong>with the same <strong>VlanId</strong>
and a different <strong>Priority</strong>, The return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.1.6</td>
<td>0x98f1580a, 0xa2b6, 0x4e61, 0x8b, 0xc9, 0x31, 0xb1, 0xac, 0xb0,
0x20, 0xb5</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_SUCCESS</strong> with the same <strong>VlanId</strong>, a
valid <strong>NumberOfVlan</strong> and a valid
<strong>Priority</strong>.</td>
<td>4. Call <strong>Find()</strong>with the same
<strong>VlanId</strong>, a valid <strong>NumberOfVlan</strong> and a
valid <strong>Priority</strong>. The return status should be
<strong>EFI_SUCCESS</strong>. The <strong>NumberOfVlan</strong> should
be 1. The output <strong>VlanId</strong> and <strong>Priority</strong>
in the <strong>Entries</strong> should be the same value of
<strong>VlanId</strong>/<strong>Priority</strong> which are set in
step2.</td>
</tr>
</tbody>
</table>



### Find()

<table style="width:100%;">
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 27%" />
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
<td>5.27.1.2.1</td>
<td>0x07f07b52, 0x93e8, 0x43fe, 0xa7, 0x84, 0x01, 0x71, 0x02, 0x37,
0x66, 0x82</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>VlanId</strong>.</td>
<td>Call <strong>Find()</strong> with valid parameters except an invalid
<strong>VlanId</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.2.2</td>
<td>0xedb0b22d, 0xa6b5, 0x497d, 0xbb, 0x9b, 0x75, 0x85, 0x47, 0x11,
0x35, 0xc5</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<strong>NumberOfVlan</strong> been <strong>NULL</strong>.</td>
<td>Call <strong>Find()</strong> with valid parameters except
<strong>NumberOfVlan</strong> being <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.27.1.2.3</td>
<td>0x57d7d76b, 0x6b88, 0x44c9, 0x85, 0x0c, 0x0f, 0xb6, 0xcb, 0xe1,
0x9c, 0xd9</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Entries</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>Find()</strong> with valid parameters(a valid
<strong>NumberOfVlan</strong> and an NULL <strong>VlanId</strong>)
except <strong>Entries</strong> being <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.2.4</td>
<td>0x1de50bab, 0x1f3a, 0x4c62, 0x82, 0x93, 0x6e, 0x9a, 0x11, 0x03,
0xce, 0x6f</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>Entries</strong>
been <strong>NULL</strong>.</td>
<td>Call <strong>Find()</strong> with valid parameters(a valid
<strong>NumberOfVlan</strong> and a valid <strong>VlanId</strong>)
except <strong>Entries</strong> being <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.27.1.2.5</td>
<td>0x49d1f535, 0x3b53, 0x4892, 0x98, 0x02, 0x5c, 0x19, 0xa3, 0x6d,
0xd1, 0x53</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_SUCCESS</strong> or <strong>EFI_NOT_FOUND</strong> with
valid parameters.</td>
<td>Call <strong>Find()</strong> with valid parameters(a valid
<strong>NumberOfVlan</strong>, a valid Entries and NULL
<strong>VlanId</strong>), The return status should be
<strong>EFI_SUCCESS</strong> or <strong>EFI_NOT_FOUND</strong>. If
<strong>EFI_SUCCESS</strong>. <strong>NumberOfVlan</strong> should be
greater than 0 and <strong>Entries</strong> should not be
<strong>NULL</strong>. If <strong>EFI_NOT_FOUND</strong>,
<strong>NumberOfVlan</strong> should be 0 and <strong>Entries</strong>
should be <strong>NULL</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.2.6</td>
<td>0x2f95fed6, 0xed1b, 0x4ac0, 0x9a, 0xa8, 0x97, 0x81, 0x76, 0xac,
0xcf, 0x8d</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.27.1.2.6 – 5.27.1.2.7 belong to one case</p>
<p>1. Call <strong>Set()</strong> to config a Vlan</p>
<p>2. Call <strong>Find()</strong> with the same <strong>VlanId</strong>
The return status should be <strong>EFI_SUCCESS</strong>. The
<strong>NumberOfVlan</strong> should be 1. The output
<strong>VlanId</strong> and <strong>Priority</strong> in the
<strong>Entries</strong> should be the same value of
<strong>VlanId</strong>/<strong>Priority</strong> which are set in step
1.</p></td>
</tr>
<tr class="even">
<td>5.27.1.2.7</td>
<td>0xf4d6c7d9, 0x21bf, 0x48b5, 0xb0, 0x1d, 0x10, 0xf4, 0xfa, 0x11,
0xf7, 0x8d</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Find - Find()</strong> returns
<strong>EFI_NOT_FOUND</strong> with valid parameters.</td>
<td><p>3. Call <strong>Remove()</strong> to delete the same VlanId</p>
<p>4. Call <strong>Find()</strong> with the same <strong>VlanId</strong>
The return status should be <strong>EFI_NOT_FOUND</strong>. The
<strong>NumberOfVlan</strong> should be 0. The <strong>Entries</strong>
should be <strong>NULL</strong>.</p></td>
</tr>
</tbody>
</table>



### Remove()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 27%" />
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
<td>5.27.1.3.1</td>
<td>0x1adaa7a4, 0xd1d3, 0x49d5, 0x97, 0xb4, 0xe4, 0x0f, 0x63, 0x1b,
0x68, 0xd0</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>VlanId</strong>.</td>
<td>Call <strong>Remove()</strong>with valid parameters except an
invalid <strong>VlanId</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.27.1.3.2</td>
<td>0xaa94b834, 0xf247, 0x4530, 0xb0, 0x6a, 0x49, 0x4e, 0x10, 0x37,
0xb5, 0xe5</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove()</strong> returns
<strong>EFI_NOT_FOUND</strong> with an not set
<strong>VlanId</strong>.</td>
<td>Call <strong>Remove()</strong>with valid parameters except an not
set <strong>VlanId</strong>, The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
<tr class="even">
<td>5.27.1.3.3</td>
<td>0x30991f39, 0x7410, 0x46ed, 0xa5, 0xe6, 0xdb, 0xc9, 0xf7, 0x86,
0x4f, 0xd3</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.27.1.3.3 – 5.27.1.3.4 belong to one case</p>
<p>1. Call <strong>Set()</strong> to configure a
<strong>VlanId</strong></p>
<p>2. Call <strong>Remove()</strong> with the same
<strong>VlanId</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.27.1.3.4</td>
<td>0x28b96fd8, 0xc729, 0x4906, 0xa6, 0xbd, 0xda, 0xe4, 0xd0, 0x2a,
0x82, 0x1e</td>
<td><strong>EFI_VLAN_CONFIG_PROTOCOL.Remove - Remove()</strong> returns
<strong>EFI_NOT_FOUND</strong> with valid parameters.</td>
<td>3. Call <strong>Remove()</strong> with the same
<strong>VlanId</strong>. The return status should be
<strong>EFI_NOT_FOUND</strong>.</td>
</tr>
</tbody>
</table>

