# Network Protocols ARP and DHCP

## EFI_ARP_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_ARP_PROTOCOL Section.

### Add()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 16%" />
<col style="width: 24%" />
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
<td>5.24.1.1.1</td>
<td>0xf6fa3bd8, 0xd8d0, 0x4c54, 0x88, 0xc2, 0x1f, 0xcf, 0x27, 0x62,
0xc5, 0xd4</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with both the <em>DenyFlag</em>
and <em>TargetAddress</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with both the
<em>DenyFlag</em> and <em>TargetAddress</em> value of
<strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.2</td>
<td>0x6404caf6, 0x9020, 0x4272, 0xa2, 0x79, 0x6f, 0x53, 0x8d, 0x42,
0x5c, 0x35</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DenyFlag</em> value of
<strong>FALSE</strong> and the <em>TargetHwAddress /TargetSwAddress</em>
value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and the
<em>TargetHwAddress /TargetSwAddress</em> value of
<strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.3</td>
<td>0x138858cd, 0x40fe, 0x4b05, 0xb4, 0x8c, 0xb5, 0x9f, 0xf2, 0xfd,
0xee, 0x5e</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DenyFlag</em> value of
<strong>FALSE</strong> and a <em>TargetHwAddress</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<strong>DenyFlag</strong> value of <strong>FALSE</strong> and a
<em>TargetHwAddress</em> value of <strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.4</td>
<td>0x48a946f4, 0x8ff7, 0x4b50, 0xa1, 0xb2, 0xc6, 0x82, 0xcd, 0xa5,
0x78, 0x62</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DenyFlag</em> value of
<strong>FALSE</strong> and a <em>TargetSwAddress</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and a
<em>TargetSwAddress</em> value of <strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.5</td>
<td>0x32deb7c7, 0x9e67, 0x459f, 0xbf, 0x4c, 0xbc, 0x80, 0x33, 0x31,
0x36, 0x05</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>DenyFlag</em> value of
<strong>TRUE</strong> and both <em>TargetHwAddress</em> and
<em>TargetSwAddress</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> when
<em>DenyFlag</em> is <strong>TRUE</strong> and both
<em>TargetHwAddress</em> and <em>TargetSwAddress</em> are not
<strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.6</td>
<td>0x87d47f39, 0x8d82, 0x40c4, 0xb9, 0x36, 0x2c, 0xf5, 0x8b, 0xa2,
0xd9, 0x32</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when the ARP cache entry of the same
<em>TargetSwAddress</em> already exists and <em>Overwrite</em> is
<strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress</em> / <em>TargetHwAddress</em> values.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>TRUE</strong> and with the same
<em>TargetSwAddress</em> as the one used in the last call while
<em>Overwrite</em> is <strong>FALSE</strong>.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.7</td>
<td>0xecc2942f, 0xd23e, 0x421e, 0x8a, 0x31, 0x3c, 0xe2, 0xdf, 0xee,
0x82, 0xcb</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when the ARP cache entry of the same
<em>TargetHwAddress</em> already exists and Overwrite is
<strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress</em> / <em>TargetHwAddress</em> values.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>TRUE</strong> and with the same
<em>TargetHwAddress</em> as the one used in the last call while
Overwrite is <strong>FALSE</strong>.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.8</td>
<td>0x31b66402, 0x4c9a, 0x486f, 0x9e, 0x68, 0xf5, 0xb1, 0x8b, 0x7b,
0xb4, 0xbf</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when the ARP cache entry of the same
<em>TargetHwAddress</em> already exists and <em>Overwrite</em> is
<strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress</em><strong>/</strong><em>TargetHwAddress</em> .</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with the same
<em>TargetSwAddress</em>/<em>TargetHwAddress</em> as the ones used in
the last call while Overwrite is <strong>FALSE</strong>.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.9</td>
<td>0x14c76af4, 0x29ca, 0x4018, 0x85, 0x6d, 0xfb, 0xfa, 0xfb, 0xae,
0x02, 0xa6</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured and <em>TargetHwAddress</em> is valid, while
<em>DenyFlag</em> is <strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>TRUE</strong> and with valid
<em>TargetHwAddress</em> .</p>
<p>The return status must be <strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.10</td>
<td>0x8f07a21d, 0xfca8, 0x4d4a, 0xa7, 0x18, 0xaf, 0x80, 0x27, 0x46,
0x84, 0x40</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured and <em>TargetSwAddress</em> is valid, while
<em>DenyFlag</em> is <strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>TRUE</strong> and a valid
<em>TargetSwAddress</em> value.</p>
<p>The return status must be <strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.11</td>
<td>0xf7e1b57e, 0x8499, 0x49b7, 0xa1, 0x35, 0xe0, 0x25, 0x7a, 0x68,
0x7c, 0xca</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured and <em>TargetSwAddress</em>/<em>TargetHwAddress</em>
are valid, while <em>DenyFlag</em> is <strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress/TargetHwAddress</em> .</p>
<p>The return status must be <strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.12</td>
<td>0x203039cb, 0xbfce, 0x472f, 0x9d, 0x46, 0xfe, 0x53, 0xcd, 0x47,
0x42, 0xb6</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when Adding normal entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress/TargetHwAddress</em> .</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the same
<em>TargetSwAddress</em> as the one added.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the
<em>TargetHwAddress</em> added into the entry cache, and compare the
<em>TargetHwAddress</em> brought back by it, then verify if they are the
same.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.13</td>
<td>0x7e93dc4e, 0x2731, 0x41d4, 0x96, 0x89, 0x27, 0x3a, 0xfe, 0xdc,
0x26, 0x40</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> When overwrite is
<strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress/TargetHwAddress</em> .</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with the same
<em>TargetSwAddress</em> as the one used in the last call and another
different <em>TargetHwAddress</em> , while overwrite is
<strong>TRUE</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the same
<em>TargetSwAddress</em> as the one added.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the
<em>TargetHwAddress</em> added at the second time, and compare the
<em>TargetHwAddress</em> brought back by it, then verify if they are the
same.</p>
<p>7. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.14</td>
<td>0xa00cc3c8, 0x005c, 0x4aed, 0xa1, 0x5c, 0x3e, 0x91, 0xca, 0x56,
0x33, 0xe5</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding normal entry with Timeout
set.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> with a
<em>DenyFlag</em> value of <strong>FALSE</strong> and with valid
<em>TargetSwAddress/TargetHwAddress</em> .</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to overwrite the
exist entry with TimeoutValue set to be 50 seconds.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the same
<em>TargetSwAddress</em> as the same one added.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the
<em>TargetHwAddress</em> added at the second time, and compare the
<em>TargetHwAddress</em> brought back, then verify if they are the
same.</p>
<p>7. Stall 30 seconds and then call
<strong>EFI_ARP_PROTOCOL.Request()</strong> and verify if the Address is
correct again.</p>
<p>8. Stall 20 seconds to let entry timeout, then call
<strong>EFI_ARP_PROTOCOL.Request(),</strong> and now the return status
must be EFI_NOT_READY.</p>
<p>9. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.15</td>
<td>0x46eee5b0, 0x7a16, 0x4be3, 0x87, 0x9e, 0xb6, 0x4f, 0xaa, 0xd0,
0xc0, 0x65</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding normal entry after the request
call.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em>.</p>
<p>The return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with the same <em>TargetSwAddress</em> as the one used in
<strong>Request().</strong></p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the
<em>TargetHwAddress</em> added, and compare the <em>TargetHwAddress</em>
brought back by it, then verify if they are the same.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.16</td>
<td>0x01321dca, 0xe8d4, 0x4022, 0xb7, 0xa1, 0xd6, 0x69, 0xca, 0xcb,
0x52, 0x0b</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding denied entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
with the valid <em>TargetSwAddress</em>.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with the same
<em>TargetSwAddress</em> as the one used in the last call.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with a
<em>TargetHwAddress</em> value of “0.0.0.0.0.0”, and compare the
<em>TargetHwAddress</em> brought back by it, then verify if they are the
same.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.17</td>
<td>0x7856bfd5, 0x758a, 0x4bcf, 0x9d, 0xc9, 0x2e, 0x36, 0x9a, 0xea,
0xf7, 0xdf</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding denied entry with a overwrite
value of <strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
with the valid <em>TargetHwAddress</em> (0:2:3:4:5:6) and overwrite
value of <strong>TRUE</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161). The OS side should capture
the request packet sent from the EUT side.</p>
<p>5. If captured, the OS side configures the ARP reply packet with
source IP “172.16.210.161”, source Mac “0:2:3:4:5:6”. Then send the
packet back to EUT side.</p>
<p>6. Then the OS side configures another ARP reply packet with source
IP “172.16.210.161”, source Mac “0:2:3:4:5:7”. Then sends the second
packet back to EUT side.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with a
<em>TargetHwAddress</em> value of “0:2:3:4:5:7” and compare the
<em>TargetHwAddress</em> brought back by it, then verify if they are the
same.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.18</td>
<td>0xefcdb906, 0xa43a, 0x437f, 0x81, 0x35, 0xe0, 0xef, 0xea, 0xd3,
0xdc, 0x0a</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> – Add denied entry with overwrite is
<strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with the valid <em>TargetSwAddress</em>”172.16.210.161” and
<em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to overwrite the
existed entry with a deny entry and the <em>TargetHwAddress</em> is
still “0:2: 3:4:5:6”.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161). The OS side should capture
the request packet sent from the EUT side.</p>
<p>6. If having captured, the OS side configures the ARP reply packet
with sender IP “172.16.210.161”, sender Mac “0:2:3:4:5:6”. Then send the
packet back to EUT side.</p>
<p>7. Then the OS side configures another ARP reply packet with sender
IP “172.16.210.161”, sender Mac “0:2:3:4:5:7”. Then send the second
packet back to EUT side.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>8. Compare the <em>TargetHwAddress</em> brought back by
<strong>EFI_ARP_PROTOCOL.Request()</strong> with “0:2:3:4:5:7” and
verify if they are same.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.19</td>
<td>0xccf3f6de, 0x5d43, 0x4dfa, 0xbe, 0x65, 0xe8, 0xc5, 0x3d, 0xe0,
0xdf, 0x95</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> – returns
<strong>EFI_SUCCESS</strong> when adding denied entry with overwrite
value of <strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with the valid <em>TargetSwAddress</em>”172.16.210.161” and
<em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to overwrite the
existed entry with a deny entry and the <em>TargetHwAddress</em> is
still “0:2: 3:4:5:6”.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161). The OS side should capture
the request packet sent from the EUT side.</p>
<p>6. If having captured, the OS side configures the ARP reply packet
with sender IP “172.16.210.161”, sender Mac “0:2:3:4:5:6”. Then send the
packet back to EUT side.</p>
<p>7. Then the OS side configures another ARP reply packet with sender
IP “172.16.210.161”, sender Mac “0:2:3:4:5:7”. Then send the second
packet back to EUT side.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>8. Compare the <em>TargetHwAddress</em> brought back by
<strong>EFI_ARP_PROTOCOL.Request()</strong> with “0:2:3:4:5:7” and
verify if they are same.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p>
<p>9. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to overwrite the
exist entry with a deny entry whose <em>TargetSwAddress</em> is
“172.16.210.161”.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.19 (continued)</td>
<td></td>
<td></td>
<td><p>10. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED</strong>.</p></td>
</tr>
<tr class="even">
<td>5.24.1.1.20</td>
<td>0xb294d2a8, 0xb3f7, 0x4ec0, 0xa1, 0x4c, 0x74, 0xa9, 0x6d, 0xcc,
0x56, 0xb7</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding denied entry with Timeout
set.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
whose <em>TargetSwAddress</em> is ”172.16.210.161” and a Timeout value
of set to be 50.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED</strong> and the return
<em>TargetHwAddress</em> must be “0:0:0:0:0:0”.</p>
<p>5. Stall 30 seconds, call <strong>EFI_ARP_PROTOCOL.Request()</strong>
again with valid <em>TargetSwAddress</em>”172.16.210.161”.</p>
<p>The return status must be <strong>EFI_ACCESS_DENIED</strong> and the
return <em>TargetHwAddress</em> must be “0:0:0:0:0:0”.</p>
<p>6. Stall 20 seconds, call <strong>EFI_ARP_PROTOCOL.Request()</strong>
again with valid <em>TargetSwAddress</em>”172.16.210.161”.This time the
return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>7. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.1.21</td>
<td>0x48d3af46, 0x09db, 0x4c34, 0xb9, 0x1e, 0xb0, 0x48, 0xe0, 0x1a,
0x9d, 0x17</td>
<td><strong>EFI_ARP_PROTOCOL.Add()</strong> - returns
<strong>EFI_SUCCESS</strong> when adding denied entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
whose <em>TargetSwAddress</em> is ”172.16.210.161”.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Verify if the return <em>TargetHwAddress</em> is
“0:0:0:0:0:0”.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>


### Cancel()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
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
<td>5.24.1.2.1</td>
<td>0x56539533, 0xee7d, 0x4e57, 0xaf, 0x89, 0x2a, 0xa7, 0x3d, 0x82,
0x36, 0x61</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>TargetSwAddress</em>
value of invalid.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with a
<em>TargetSwAddress</em> value of <strong>NULL</strong> and a
<em>ResolvedEvent</em> value other than <strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.2.2</td>
<td>0xe9118c8c, 0x1e0e, 0x451b, 0x8f, 0x4f, 0xd6, 0x37, 0x8b, 0x82,
0xf3, 0x6a</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid <em>Event</em>
value.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY</strong>.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with an
<em>Event</em> value of <strong>NULL</strong> and a
<em>TargetSwAddress</em> value of not <strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.2.3</td>
<td>0x8b6cee26, 0x52c3, 0x45fe, 0xae, 0x7e, 0xfa, 0xa6, 0xd9, 0xc1,
0x80, 0xc7</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_NOT_FOUND</strong> with <em>Event</em> not found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with valid
<em>TargetSwAddress</em> while <em>Event</em> is not issued by the
<strong>EFI_ARP_PROTOCOL.Request().</strong></p>
<p>The return status must be <strong>EFI_NOT_FOUND.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.2.4</td>
<td>0x09e570d8, 0xdc54, 0x4458, 0xb9, 0xa3, 0x58, 0x4f, 0xeb, 0x64,
0xc0, 0xdb</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_NOT_FOUND</strong> with <em>TargetSwAddress</em> not
found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with a
<em>TargetSwAddress</em> value of “172.16.210.160” which is not issued
by the <strong>EFI_ARP_PROTOCOL.Request().</strong></p>
<p>The return status must be <strong>EFI_NOT_FOUND.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.2.5</td>
<td>0xbecb34c1, 0xbfed, 0x43c1, 0x81, 0xfe, 0xc5, 0x9f, 0x8d, 0xf4,
0xf2, 0x5a</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_NOT_FOUND</strong> with <em>TargetSwAddress</em> not
found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with a
<em>TargetSwAddress</em> value of “172.16.210.160” which is not issued
by the <strong>EFI_ARP_PROTOCOL.Request().</strong></p>
<p>The return status must be <strong>EFI_NOT_FOUND.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.2.6</td>
<td>0x9511bd75, 0x971b, 0x4e14, 0xb2, 0xd1, 0x44, 0x9b, 0x2e, 0x0a,
0x90, 0x78</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_NOT_FOUND</strong> with both the <em>TargetSwAddress</em>
and <em>Event</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong>with both the
<em>TargetSwAddress</em> and <em>Event</em> value of
<strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_NOT_FOUND.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.2.7</td>
<td>0xd45a3a11, 0xf14c, 0x4dc2, 0x8d, 0x91, 0xfe, 0x0b, 0xa7, 0x14,
0xac, 0x97</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>ConfigData</em> value of <strong>NULL</strong> to reset the ARP
driver instance.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with valid
parameters which Request () had issued.</p>
<p>The return status must be <strong>EFI_NOT_STARTED.</strong></p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.2.8</td>
<td>0x1b5f4fbb, 0x0d7d, 0x4b4c, 0xad, 0x29, 0x7b, 0x8b, 0xa5, 0x3e,
0xab, 0xc6</td>
<td><strong>EFI_ARP_PROTOCOL.Cancel()</strong> - returns
<strong>EFI_SUCCESS</strong> when canceling request.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> (172.16.210.161).</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Cancel()</strong> with parameters
issued by <strong>EFI_ARP_PROTOCOL.Request()</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>5. Then the OS side shouldn’t capture any packet sent from the EUT
side.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> again, the return
status should be <strong>EFI_NOT_READY</strong> and the return
<em>TargetHwAddress</em> should be “0:0:0:0:0:0”.</p>
<p>7. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>



### Configure()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 23%" />
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
<td>5.24.1.3.1</td>
<td>0xcdbd6b40, 0x3b1f, 0x4cd5, 0x8b, 0xd9, 0x33, 0x99, 0x63, 0x8e,
0x80, 0x35</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid
<em>SwAddressLength</em>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 0.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.2</td>
<td>0x072fb583, 0x5885, 0x4b2e, 0x99, 0x72, 0xe7, 0x2c, 0x5b, 0xd3,
0x34, 0xd5</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with invalid
<em>StationAddress</em>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>StationAddress</em> value of <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.3</td>
<td>0x3a8fde87, 0x1d5d, 0x462e, 0x8e, 0x3c, 0x01, 0xec, 0x3b, 0x9f,
0xf7, 0x5b</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong>when the <em>StationAddress</em> is
different from the one that has already registered.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with different
<em>StationAddress</em> with the one that has already registerd.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.4</td>
<td>0x2747e156, 0xee8d, 0x4533, 0xb4, 0x63, 0xa8, 0xb0, 0x5f, 0xe0,
0x6b, 0xc1</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the <em>SwAddressLength</em> is
different from the one that has already registered.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
different <em>SwAddressLength</em> from the one that has already
registered.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.5</td>
<td>0x790466e9, 0x0f6e, 0x4a3d, 0xa7, 0xdb, 0x5c, 0xb5, 0x6b, 0x59,
0x01, 0xef</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the <em>SwAddressLength</em> is
different from the one that has already registered.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with different
<em>SwAddressLength</em> from the one that has already registerd.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.6</td>
<td>0xab90d4d0, 0xa0ac, 0x44c3, 0xb7, 0x03, 0x12, 0xdd, 0x10, 0x37,
0x74, 0x1d</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the <em>SwAddressType</em> is
different from the one that has already registered.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with different
<em>SwAddressType</em> from the one that has already registered.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.7</td>
<td>0xf41970a5, 0x733f, 0x47d4, 0x8f, 0x52, 0xd5, 0x5c, 0x86, 0xd7,
0x96, 0x9f</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the <em>SwAddressType</em> is
different from the one that has already registered.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with different
<em>SwAddressType</em> from the one that has already registerd.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.8</td>
<td>0x8b9bcd53, 0x9a83, 0x45c0, 0x9b, 0x5f, 0xf2, 0x99, 0x2c, 0x78,
0xf8, 0x1b</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet, and send back the
ARP reply packet filled with source IP”172.16.210.161” and source MAC
“0:2:3:4:5:6”.</p>
<p>5. The return status must be <strong>EFI_NOT_READY</strong> and the
return <em>TargetHwAddress</em> should be“0:2:3:4:5:6”.</p>
<p>6. The OS side sends a request packet to resolve IP “172.16.210.102”
with the source IP”172.16.210.161” and source MAC”0:2:3:4:5:7”.</p>
<p>7. Then OS should capture the ARP reply packet sent from the EUT
side.</p>
<p>8. If having captured, call
<strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>9. The return <em>TargetHwAddress</em> must be “0:2:3:4:5:7”, and</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>10. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.9</td>
<td>0xeee99be3, 0xa701, 0x4612, 0x98, 0x1a, 0xad, 0x8c, 0x06, 0x4a,
0xd7, 0xa5</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>ConfigData</em> value of <strong>NULL</strong> to reset the ARP
driver instance.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong>, the return
status should be <strong>EFI_NOT_STARTED</strong>.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> again with
valid parameters.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>7. The OS side should capture the request packet, and send back the
ARP reply packet filled with source IP”172.16.210.161” and source MAC
“0:2:3:4:5:6”.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>8. Verify if the return <em>TargetHwAddress</em> is
“0:2:3:4:5:6”.</p>
<p>9 Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.10</td>
<td>0x4423e5b6, 0x6f3c, 0x41c3, 0x8c, 0x50, 0xea, 0x71, 0xd8, 0x52,
0x3b, 0x74</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> with parameter timeout
set<strong>.</strong></td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters with timeout set to be 50.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet, and send back the
ARP reply packet filled with source IP”172.16.210.161” and source MAC
“0:2:3:4:5:6”.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>5. Verify if the return <em>TargetHwAddress</em> is
“0:2:3:4:5:6”.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “172.16.210.161” again.</p>
<p>7. The return status should be <strong>EFI_SUCCESS</strong> and the
<em>TargetHwAddress</em> be “0:2:3:4:5:6”.</p>
<p>8. Stall 30 seconds, call <strong>EFI_ARP_PROTOCOL.Request()</strong>
like the step 6 again.</p>
<p>9. The return status should be <strong>EFI_SUCCESS</strong> and the
<em>TargetHwAddress</em> be “0:2:3:4:5:6”.</p>
<p>10. Stall 20 seconds, call
<strong>EFI_ARP_PROTOCOL.Request()</strong> like the step 6 again.</p>
<p>11. This time the return status should be
<strong>EFI_NOT_READY</strong> and the <em>TargetHwAddress</em> be
“0:0:0:0:0:0”.</p>
<p>12. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.11</td>
<td>0x79f9aacd, 0xfb79, 0x4746, 0x8f, 0x5c, 0x38, 0x4b, 0xf9, 0x2e,
0x0a, 0x53</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> and packet count is correct when
<em>ConfigData.RetryCount</em> is <strong>5</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet for 5 times.</p>
<p>The return status should be <strong>EFI_NOT_READY</strong> and the
<em>TargetHwAddress</em> should be “0:0:0:0:0:0”.</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.12</td>
<td>0x970634b0, 0x57a5, 0x40c5, 0x92, 0x01, 0xcb, 0xb2, 0x00, 0x8c,
0xbb, 0x43</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with
<em>EntryTimeOut</em>, <em>RetryCount</em>, <em>RetryTimeOut</em> value
of 0.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>EntryTimeOut</em> value of 5000000, a <em>RetryCount</em> value of
30, and a <em>RetryTimeOut</em> value of 5000000.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet.</p>
<p>5. If having captured, the OS side sends an ARP reply back with
source IP “172.16.210.161”, source MAC “0:2:3:4:5:6”.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.3.13</td>
<td>0xc6c2e0c3, 0x9715, 0x48a8, 0x86, 0xba, 0x36, 0xbd, 0xac, 0x70,
0x71, 0x6d</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> when <em>SwAddressLength</em> is 1.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 1.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “171.16.210.161”.</p>
<p>4. The OS side should capture the request packet.</p>
<p>5. If having captured, the OS side sends an ARP reply back with
source IP “171”, source MAC “0:2:3:4:5:6”, Target IP “172”.</p>
<p>The return status should be <strong>EFI_NOT_READY</strong> and the
<em>TargetHwAddress</em> should be “0:2:3:4:5:6”.</p>
<p>6. The OS sends an ARP request to the broadcast address with source
IP “171” and source MAC” 0:2:3:4:5:6” to resolve Target IP “172”.</p>
<p>7. The OS should capture the packet.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.3.14</td>
<td>0xf4972462, 0x1dc5, 0x484f, 0xb6, 0x55, 0x8b, 0x2e, 0x89, 0xec,
0x2c, 0x46</td>
<td><strong>EFI_ARP_PROTOCOL.Configure() -</strong> returns
<strong>EFI_SUCCESS</strong> when <em>SwAddressLength</em> is 16.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 16.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with valid
<em>TargetSwAddress</em> “171.16.210.161”.</p>
<p>4. The OS side should capture the request packet.</p>
<p>5. If having captured, the OS side sends an ARP reply back filled
with source IP “172.16.210.161.0.0.0.0.0.0.0.0.0.0.0.0”, source MAC
“0:2:3:4:5:6”, Target IP “172.16.210.102.0.0.0.0.0.0.0.0.0.0.0.0”.</p>
<p>The return status should be “EFI_NOT_READY” and the
<em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>6. The OS sends an ARP request to the broadcast address with source
IP “172.16.210.161.0.0.0.0.0.0.0.0.0.0.0.0” and source MAC” 0:2:3:4:5:6”
to resolve Target IP “172.16.210.102.0.0.0.0.0.0.0.0.0.0.0.0”.</p>
<p>7. The OS should capture the packet.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>



### Delete()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
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
<td>5.24.1.4.1</td>
<td>0x1ba44874, 0x8e16, 0x422e, 0x97, 0x73, 0x43, 0x6f, 0x06, 0x2f,
0x6f, 0x01</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when the specified deletion key of
MacAddress is not found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
added entry with key specified as IpAddress which is the same as the
<em>TargetSwAddress</em> of added entry.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> again with key
specified as MacAddress which is the same with the
<em>TargetHwAddress</em> of added entry.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.4.2</td>
<td>0xab90c68f, 0xa0af, 0x4188, 0x9a, 0x74, 0x66, 0x5a, 0x9c, 0x8a,
0x4b, 0x92</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when the specified deletion key of
IpAddress was not found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
added entry with key specified as MacAddress which is the same with the
<em>TargetHwAddress</em> of the added entry.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> again with key
specified as IpAddress which is the same as the <em>TargetSwAddress</em>
of the added entry.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.4.3</td>
<td>0xe03b088c, 0x8cf0, 0x4db9, 0xa0, 0xc1, 0x77, 0xa9, 0xf4, 0x1a,
0xce, 0x0a</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when ARP driver instance has not been
configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> with key specified
as IpAddress.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.4.4</td>
<td>0x4b8b9c7f, 0x96fc, 0x41fb, 0xbc, 0x58, 0x32, 0x1d, 0x13, 0x75,
0xed, 0x7b</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when ARP driver instance has not been
configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> with key specified
as MacAddress.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.4.5</td>
<td>0x494278d5, 0x4ff5, 0x4ac5, 0x9e, 0xd7, 0xfa, 0x53, 0xa1, 0x7e,
0x03, 0xed</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_SUCCESS</strong> when deleting the normal entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
added entry with key specified as IpAddress which is the same as the
<em>TargetSwAddress</em> of the added entry.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> which is the same as the
<em>TargetSwAddress</em> of the added entry.</p>
<p>The return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.4.6</td>
<td>0xd2477a4f, 0xef0d, 0x46a2, 0x9a, 0x86, 0x32, 0x82, 0x3f, 0x2c,
0x4b, 0xa3</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_SUCCESS</strong> when deleting the normal entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
added entry with key specified as MacAddress which is the same as the
<em>TargetHwAddress</em> of the added entry.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> which is the same as the
<em>TargetSwAddress</em> of the added entry.</p>
<p>The return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.4.7</td>
<td>0x1e618ee9, 0x40b9, 0x4f79, 0xb9, 0x26, 0xee, 0x2b, 0xa3, 0x73,
0x51, 0x4c</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_SUCCESS</strong> when deleting all entries.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong>with AddressBuffer
set to <strong>NULL</strong> and <em>BySwAddress</em> set to
<strong>TRUE</strong> to delete all entries.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> which is the same as the
<em>TargetSwAddress</em> of the added entry.</p>
<p>The return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.4.8</td>
<td>0x34a1c3fa, 0xf335, 0x471d, 0x83, 0x03, 0xef, 0x50, 0x98, 0xa3,
0x05, 0x30</td>
<td><strong>EFI_ARP_PROTOCOL.Delete() -</strong> returns
<strong>EFI_SUCCESS</strong> when deleting all entries.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong>with AddressBuffer
set to <strong>NULL</strong> and <em>BySwAddress</em> set to
<strong>FALSE</strong> to delete all entries.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> which is the same as the
<em>TargetSwAddress</em> of the added entry.</p>
<p>The return status must be <strong>EFI_NOT_READY</strong>.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>



### Find()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 15%" />
<col style="width: 24%" />
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
<td>5.24.1.5.1</td>
<td>0x16bcb5a1, 0xf2c1, 0x419a, 0x8a, 0xf1, 0xea, 0x4b, 0xd9, 0x89,
0x5f, 0xda</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when both <em>EntryLength</em>
and <em>EntryCount</em> are <strong>NULL</strong> and <em>Refresh</em>
is <strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with both
<em>EntryLength</em> and <em>EntryCount</em> are <strong>NULL</strong>,
<em>BySwAddress</em> is <strong>TRUE</strong>,and <em>Refresh</em> is
<strong>FALSE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.2</td>
<td>0x210ce61b, 0xa76d, 0x4c56, 0xbe, 0x24, 0xe7, 0xb8, 0x11, 0x50,
0xd7, 0x10</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when both <em>EntryLength</em>
and <em>EntryCount</em> are <strong>NULL</strong> and <em>Refresh</em>
is <strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with both the
<em>EntryLength</em> and <em>EntryCount</em> value of
<strong>NULL</strong> and a <em>BySwAddress</em> value of
<strong>FALSE</strong> while <em>Refresh</em> is
<strong>FALSE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.3</td>
<td>0xf6244c19, 0x6e26, 0x4b9e, 0x84, 0xd3, 0x43, 0x65, 0xb7, 0x6c,
0x17, 0x39</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when both <em>EntryLength</em>
and <em>EntryCount</em> are <strong>NULL</strong> and Entries are not
<strong>NULL</strong> while <em>Refresh</em> is
<strong>TRUE</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with both
<em>EntryLength</em> and <em>EntryCount</em> are <strong>NULL</strong>
and Entries are not <strong>NULL</strong> while <em>Refresh</em> is
<strong>TRUE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.4</td>
<td>0x5508b3bb, 0x7062, 0x46e7, 0xa4, 0x31, 0xf2, 0xed, 0x67, 0x0b,
0xee, 0x61</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with the specified
IpAddress.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.5</td>
<td>0x9d95d0d7, 0x8e23, 0x4db4, 0xb1, 0xb6, 0x76, 0xc2, 0xee, 0xdc,
0x0f, 0x4f</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with the specified
MacAddress.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.6</td>
<td>0x056e9bc8, 0xb221, 0x4063, 0xa2, 0x59, 0x19, 0xe0, 0x08, 0xff,
0x86, 0xda</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with the specified
IpAddress and a <em>Refresh</em> value of <strong>TRUE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.7</td>
<td>0xc8b3f76f, 0x5ec3, 0x40f6, 0x98, 0x72, 0x31, 0xea, 0x23, 0x6f,
0xc8, 0x08</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with the specified
MacAddress and a <em>Refresh</em> value of <strong>TRUE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.8</td>
<td>0xe0814da9, 0x47fb, 0x443d, 0x84, 0xce, 0xaf, 0x65, 0x01, 0x33,
0x3f, 0x69</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with AddressBuffer
set to <strong>NULL</strong> and <em>BySwAddress</em> set to
<strong>FALSE</strong> while <em>Refresh</em> is <strong>TRUE</strong>
so as to <em>refresh</em> all the entries.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.9</td>
<td>0xdb367aca, 0xbc94, 0x4c36, 0x92, 0xbd, 0x3b, 0xba, 0x16, 0x9e,
0xc0, 0x6e</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when no matching entries were found.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with AddressBuffer
set to <strong>NULL</strong> and <em>BySwAddress</em> set to
<strong>TRUE</strong> while <em>Refresh</em> is <strong>TRUE</strong> so
as to <em>refresh</em> all the entries.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.10</td>
<td>0x883abd28, 0xd498, 0x4868, 0xb1, 0xa7, 0xe3, 0x22, 0xd1, 0x22,
0x6a, 0x12</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress when <em>Refresh</em> is <strong>FALSE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.11</td>
<td>0x9301dc5d, 0xc1f2, 0x4858, 0x93, 0xcf, 0xda, 0x77, 0x96, 0xa6,
0x2a, 0x8f</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress and <em>Refresh</em> is <strong>TRUE</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.12</td>
<td>0x6350837b, 0x0e0e, 0x4241, 0xbd, 0x10, 0x87, 0x77, 0xb3, 0x35,
0xa7, 0xd3</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first call to <strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress that is the same as the <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.13</td>
<td>0x81716a64, 0x63db, 0x4625, 0xad, 0x87, 0xf1, 0x23, 0x46, 0x94,
0x9f, 0xa9</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the first
<strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress that is the same as the <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
entry added in the second time.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress that is the same as the <em>TargetSwAddress</em> in the
first <strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x1.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.14</td>
<td>0x34fd32ad, 0x8e3e, 0x4f49, 0xa0, 0xd7, 0xcc, 0xca, 0xac, 0xa3,
0xce, 0x1f</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first call to <strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with AddressBuffer
set to <strong>NULL</strong> to find all the entries.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.15</td>
<td>0x3b98d05b, 0x0cd1, 0x41a3, 0xa4, 0x8b, 0x2c, 0xe3, 0x37, 0x6e,
0x0f, 0x09</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the first
<strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress that is the same as the <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
entry added in the second time.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with AddressBuffer
set to <strong>NULL</strong> to find all the entries.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x1.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.16</td>
<td>0x0c8090e4, 0xa0c5, 0x427f, 0xa2, 0xf9, 0x34, 0xd8, 0x10, 0x91,
0x11, 0x2f</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry with
refreshing.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with timeout set to 50s.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first all to <strong>EFI_ARP_PROTOCOL.Add()</strong>,while the
<em>TargetSwAddress</em> is different. In addition, timeout is set to
50s.</p>
<p>5. Stall 20 s.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add( )</strong> call when
<strong>refresh</strong> is <strong>TRUE</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>7. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.17</td>
<td>0x89474dd0, 0x461b, 0x49c3, 0xa8, 0x5e, 0xaa, 0x16, 0x74, 0xad,
0x6f, 0x9d</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry without
refreshing.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with timeout set to 50s.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first all to <strong>EFI_ARP_PROTOCOL.Add()</strong>,while the
<em>TargetSwAddress</em> is different. In addition, timeout is set to
50s.</p>
<p>5. Stall 20 s.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add(</strong>) call when <em>refresh</em> is
<strong>TRUE</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>7. Stall 35 s.</p>
<p>8. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call and a <em>refresh</em>
value of <strong>FALSE</strong>.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x16 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>9. Stall 20 s.</p>
<p>10. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add( )</strong> call with a <em>refresh</em>
value of <strong>FALSE</strong>.</p>
<p>The return status must be <strong>EFI_NOT_FOUND</strong>.</p>
<p>11. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.18</td>
<td>0x97fbb88f, 0x0566, 0x4b4b, 0x93, 0xfe, 0x5e, 0xc9, 0xad, 0x60,
0x8d, 0x7e</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry with a
<em>SwAddressLength</em> value of 16.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 16.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first call to <strong>EFI_ARP_PROTOCOL.Add()</strong>, while
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x22 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.19</td>
<td>0xcbd6f47d, 0x2edc, 0x4235, 0x91, 0x50, 0x1f, 0xba, 0xe9, 0x07,
0xac, 0x26</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry with a
<em>SwAddressLength</em> value of 16.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 16.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the one used in the
first call to <strong>EFI_ARP_PROTOCOL.Add()</strong>, while
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <strong>EntryLength</strong> should be 0x22
and the return <strong>EntryCount</strong> should be 0x2.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
entry added in the second time.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress the same as <em>TargetSwAddress</em> in the first
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x22 and the
return <em>EntryCount</em> should be 0x1.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.5.20</td>
<td>0x630e139e, 0x287a, 0x456c, 0xa5, 0xf7, 0x58, 0x35, 0xaf, 0x42,
0xf7, 0x7d</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry with a
<em>SwAddressLength</em> value of 1.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 1.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the first
<strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as the <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x13 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.5.21</td>
<td>0xf7c0f95a, 0xfaa2, 0x4577, 0x8c, 0x66, 0xb4, 0x76, 0x82, 0x00,
0x85, 0x5d</td>
<td><strong>EFI_ARP_PROTOCOL.Find() -</strong> returns
<strong>EFI_SUCCESS</strong> when finding the entry with a
<em>SwAddressLength</em> value of 1.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with a
<em>SwAddressLength</em> value of 1.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add another normal
entry with the same <em>TargetHwAddress</em> as the first
<strong>EFI_ARP_PROTOCOL.Add()</strong>, while the
<em>TargetSwAddress</em> is different.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as the <em>TargetHwAddress</em> in the
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x13 and the
return <em>EntryCount</em> should be 0x2.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Delete()</strong> to delete the
entry added in the second time.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress the same as the <em>TargetSwAddress</em> in the first
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>In addition, the return <em>EntryLength</em> should be 0x13 and the
return <em>EntryCount</em> should be 0x1.</p>
<p>8. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>



### Flush()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 16%" />
<col style="width: 25%" />
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
<td>5.24.1.6.1</td>
<td>0x057bd5b9, 0xc869, 0x4446, 0xa9, 0xd1, 0x79, 0x07, 0xdc, 0xf8,
0x74, 0xf0</td>
<td><strong>EFI_ARP_PROTOCOL.Flush() -</strong> returns
<strong>EFI_NOT_FOUND</strong> when flushing the entry again after the
first flush.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
permanent entry 1.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
dynamic entry 2.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
permanent entry 3.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
dynamic entry 4.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Flush()</strong> to remove all
dynamic cache entries.</p>
<p>8. Call <strong>EFI_ARP_PROTOCOL.Flush()</strong> again.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_FOUND.</strong></p>
<p>9. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.6.2</td>
<td>0xe34bd9b5, 0x94b2, 0x422a, 0xb8, 0xd1, 0x6c, 0x18, 0x07, 0x6c,
0xef, 0xbb</td>
<td><strong>EFI_ARP_PROTOCOL.Flush() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when the arp driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Flush()</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.6.3</td>
<td>0xf2cc7ff1, 0x9049, 0x4daa, 0xa3, 0x4d, 0xca, 0x55, 0xf5, 0xe9,
0x67, 0x55</td>
<td><strong>EFI_ARP_PROTOCOL.Flush() -</strong> returns
<strong>EFI_SUCCESS</strong> when flushing the entry.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.e</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
permanent entry 1.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
dynamic entry 2 – timeout is 50s.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
permanent entry 3.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
dynamic entry 4 – timeout is 50s.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Flush()</strong> to remove all
dynamic cache entries.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>8. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress the same as the <em>TargetSwAddress</em> in the first
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>9. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress the same as the <em>TargetHwAddress</em> in the first
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>10. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of IpAddress the same as the <em>TargetSwAddress</em> in the second
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_NOT_FOUND</strong>.</p>
<p>11. Call <strong>EFI_ARP_PROTOCOL.Find()</strong> with specified key
of MacAddress as same as the <em>TargetHwAddress</em> in the second
<strong>EFI_ARP_PROTOCOL.Add()</strong> call.</p>
<p>The return status must be <strong>EFI_NOT_FOUND</strong>.</p>
<p>14. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>


### Request()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 15%" />
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
<td>5.24.1.7.1</td>
<td>0x464366ea, 0xf5a5, 0x47a0, 0x8b, 0x3b, 0x67, 0x09, 0x89, 0xcf,
0x43, 0xd2</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>TargetHwAddress</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with a
<em>TargetHwAddress</em> value of <strong>NULL</strong> ,and both the
<em>ResolvedEvent</em> and <em>TargetSwAdddress</em> value other than
<strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.2</td>
<td>0xb4df082c, 0xb895, 0x4ec8, 0xac, 0xc7, 0x26, 0x58, 0x87, 0xc7,
0xe3, 0xbb</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>TargetHwAddress</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with a
<em>TargetHwAddress</em> value of <strong>NULL</strong> ,a
<em>ResolvedEvent</em> value of <strong>NULL</strong>, and a
<em>TargetSwAdddress</em> value other than <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.3</td>
<td>0x58d0454a, 0xeed1, 0x4ccd, 0xa3, 0xd0, 0x10, 0xa5, 0xa8, 0x71,
0x46, 0x38</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>TargetHwAddress
TargetHwAddress</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with a
<em>TargetHwAddress</em> value of <strong>NULL</strong>, and both the
<em>ResolvedEvent</em> and <em>TargetSwAdddress</em> value of
<strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.4</td>
<td>0xe726cb6e, 0x3ee3, 0x474e, 0x9c, 0x1c, 0xa7, 0xc7, 0xa6, 0x93,
0x85, 0x1d</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the requested Address is present
in the deny address list.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal
entry.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
whose <em>TargetSwAddress</em> is the same as the one used in the first
Add() call to overwrite the entry first added.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> the same as the one used in the call to
<strong>EFI_ARP_PROTOCOL.Add()</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_ACCESS_DENIED.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
0:0:0:0:0:0.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.5</td>
<td>0xd774703f, 0x7ed8, 0x48da, 0x9f, 0x86, 0x5e, 0xf8, 0x19, 0x47,
0xb6, 0x47</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when both
<em>TargetSwAddress</em> and <em>ResolvedEvent</em> are not
<strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.6</td>
<td>0x122d41e6, 0x252a, 0x4afb, 0xa2, 0x47, 0x03, 0x56, 0xd5, 0x3c,
0x4a, 0x64</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_NOT_STARTED</strong> when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when
<em>TargetSwAddress</em> is not <strong>NULL</strong> and
<em>ResolvedEvent</em> is <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.7</td>
<td>0xca3946d0, 0x64ff, 0x4139, 0x97, 0x66, 0x82, 0x91, 0xcb, 0xc1,
0x12, 0x09</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_NOT_STARTED</strong> – when the ARP driver instance has not
been configured.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when both
<em>TargetSwAddress</em> and <em>ResolvedEvent</em> are
<strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.8</td>
<td>0xf4b08f82, 0xdafd, 0x4618, 0x94, 0xed, 0x15, 0xf8, 0x54, 0xce,
0xe3, 0x9f</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_NOT_READY</strong> – when the request has been started and
is not finished.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet and send back the
reply packet with SourceIp “172.16.210.161”, SourceMac
“0:2:3:4:5:6”.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>10. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.9</td>
<td>0x3d6668d9, 0x631c, 0x4cee, 0xae, 0xc9, 0xc1, 0x0f, 0x3f, 0xe6,
0xee, 0x27</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_NOT_READY</strong> – when the request has been started and
is not finished.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet and send back the
reply packet with SourceIp “172.16.210.161”, SourceMac
“0:2:3:4:5:6”.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>5. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and
<em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a deny entry
with the same <em>TargetHwAddress</em> as the one used in the first Add(
) to overwrite the entry first added.</p>
<p>7. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>8. The OS side should capture the request packet and send back the
first reply packet with SourceIp “172.16.210.161”, SourceMac
“0:2:3:4:5:6”.</p>
<p>9. Then OS sends back the second reply packet with SourceIp
“172.16.210.161”, SourceMac “0:2:3:4:5:7”.</p>
<p>The return status must be</p>
<p><strong>EFI_NOT_READY.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:7”.</p>
<p>10. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.10</td>
<td>0xe37f681b, 0xab41, 0x4370, 0xab, 0x02, 0xf6, 0xd5, 0xfb, 0x0a,
0xf2, 0xb7</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when the data was copied from the ARP cache
into the <em>TargetHwAddress</em> buffer.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet and validate whether
the packet is rightly sent from the EUT side.</p>
<p>5. The OS sends back the reply packet with SourceIp “172.16.210.161”,
SourceMac “0:2:3:4:5:6”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.11</td>
<td>0x93e9a6d8, 0xb732, 0x40d7, 0x8d, 0x1e, 0xe5, 0xdb, 0xa6, 0xf6,
0x02, 0x1e</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when the data was copied from the ARP cache
into the <em>TargetHwAddress</em> buffer.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>4. The OS side should capture the request packet and validate whether
the packet is rightly sent from the EUT side.</p>
<p>5. The OS sends back the reply packet with SourceIp “172.16.210.161”,
SourceMac “0:2:3:4:5:6”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> “0:2:3:4:5:6”.</p>
<p>6. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with broadcast
destination address to resolve <em>TargetSwAddress</em>
“172.16.210.161”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>7. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.12</td>
<td>0xa227797d, 0x00b5, 0x4ff0, 0xb4, 0x62, 0x46, 0x87, 0xa1, 0x31,
0xa0, 0x1c</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when the data was copied from the ARP cache
into the <em>TargetHwAddress</em> buffer.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and TargeHwAddress
“0:2:3:4:5:6”</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> with
<em>TargetSwAddress</em> “172.16.210.161”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.13</td>
<td>0xd958bbd5, 0x3429, 0x4b94, 0x9f, 0xe5, 0x8e, 0xe1, 0xf4, 0x8b,
0xfd, 0xd2</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when requesting the entry whose
<em>TargetSwAddress</em> is a multicast IP address.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and TargeHwAddress
“0:2:3:4:5:6”</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> to resolve
multicast IP address “224.0.1.2”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“1:0:5e:0:1:2”.</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.14</td>
<td>0x46146a28, 0x7af5, 0x43c5, 0xb7, 0xd1, 0x6f, 0xfb, 0xd6, 0xa4,
0x89, 0x97</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when requesting the entry whose
<em>TargetSwAddress</em> is a multicast IP address.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and
<em>TargetHwAddress</em> “0:2:3:4:5:6”</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> to resolve
multicast IP address “238.255.255.255”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> is “1:0:5e:7f: ff:
ff”.</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.15</td>
<td>0x50ecb99e, 0xfdab, 0x441c, 0x85, 0x08, 0x92, 0x5f, 0x1b, 0xdf,
0x42, 0x4b</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when requesting the entry whose
<em>TargetSwAddress</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and TargeHwAddress
“0:2:3:4:5:6”</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when
<em>TargetSwAddress</em> is <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be “ff: ff:
ff: ff: ff: ff”. (Network interface hardware broadcast address).</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="odd">
<td>5.24.1.7.16</td>
<td>0x50d9cb20, 0x1177, 0x4b13, 0xbc, 0x41, 0xf0, 0xf3, 0x2a, 0x3d,
0xf9, 0x02</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when requesting the entry whose
<em>TargetSwAddress</em> is “255.255.255.255”.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Add()</strong> to add a normal entry
with <em>TargetSwAddress</em> “172.16.210.161” and TargeHwAddress
“0:2:3:4:5:6”</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when
<em>TargetSwAddress</em> is “255.255.255.255”.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be “ff: ff:
ff: ff: ff: ff”. (Network interface hardware broadcast address).</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
<tr class="even">
<td>5.24.1.7.17</td>
<td>0xf7140dcf, 0x0d15, 0x438a, 0xa3, 0x4d, 0x47, 0x23, 0x97, 0x6f,
0x0b, 0xc8</td>
<td><strong>EFI_ARP_PROTOCOL.Request() -</strong> returns
<strong>EFI_SUCCESS</strong> when calling <strong>Request ()</strong>
twice with the same <em>TargetSwAddress</em>.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> when
<em>TargetSwAddress</em> is “172.16.210.161”.</p>
<p>The return status should be <strong>EFI_NOT_READY</strong>.</p>
<p>4. Call <strong>EFI_ARP_PROTOCOL.Request()</strong> again when
<em>TargetSwAddress</em> is “172.16.210.161”.</p>
<p>The return status should be <strong>EFI_NOT_READY</strong>.</p>
<p>5. The OS side should capture the request packet and send back the
reply packet with SouceIP “172.16.210.161” and SourceMac
”0:2:3:4:5:6”.</p>
<p>The return <em>EventContext</em> should be 2.</p>
<p>The return status must be</p>
<p><strong>EFI_SUCCESS.</strong></p>
<p>In addition, the return <em>TargetHwAddress</em> should be
“0:2:3:4:5:6”.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment</p></td>
</tr>
</tbody>
</table>


### CreateChild()

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
<td>5.24.1.8.1</td>
<td>0xd01e591b, 0x6b83, 0x417c, 0xbf, 0xe0, 0x1d, 0xb3, 0x78, 0xea,
0x2c, 0x78</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>NULL</strong> child handle.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> with the
parameter a <em>ChildHandle</em> value of <strong>NULL</strong>.</p>
<p>The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.1.8.2</td>
<td>0x51d66e16, 0x39f6, 0x4fff, 0x8a, 0x99, 0xf2, 0x95, 0x01, 0xe3,
0x4b, 0xe8</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_INVALID_PARAMETER</strong> with invalid child
handle.</td>
<td>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> with a
invalid <em>ChildHandle</em>. The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.1.8.3</td>
<td>0x460a6262, 0xaa4d, 0x4e25, 0x92, 0x6b, 0x55, 0x1e, 0xf0, 0xb5,
0x6d, 0x37</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> –
invokes <strong>CreateChild()</strong> to create different childs.</td>
<td>Call <strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild</strong>()
to create childs three times and then destroy them.</td>
</tr>
</tbody>
</table>



### DestroyChild()

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
<td>5.24.1.9.1</td>
<td>0xfaabc3ef, 0xc56f, 0x44d1, 0xbe, 0xb6, 0x53, 0x5b, 0x26, 0x4d,
0xba, 0x63</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> -
returns <strong>EFI_UNSUPPORTED</strong> with invalid child handle.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle</p>
<p>The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>3. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> again
with value of Handle set to be 8 and clean up the environment.</p>
<p>The return status must be <strong>EFI_UNSUPPORTED.</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.1.9.2</td>
<td>0x7b8de1fe, 0x93e1, 0x48a4, 0xa0, 0x5e, 0x38, 0xad, 0x8f, 0x26,
0xf0, 0x83</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> -
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>NULL</strong> child.</td>
<td>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the <strong>NULL</strong> child.</td>
</tr>
<tr class="even">
<td>5.24.1.9.3</td>
<td>0xf651081a, 0xb71f, 0x4617, 0x99, 0x7a, 0xd1, 0x87, 0x7a, 0x07,
0x03, 0x28</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> -
returns <strong>EFI_INVALID_PARAMETER</strong> and inexistent
child.</td>
<td>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the inexistent child.</td>
</tr>
<tr class="odd">
<td>5.24.1.9.4</td>
<td>0x5772a154, 0xb8f5, 0x4fec, 0xaa, 0x80, 0xae, 0xb9, 0x0c, 0x4c,
0xd2, 0x5d</td>
<td><strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> –
invokes <strong>DestroyChild()</strong> to destroy different childs</td>
<td>Call <strong>EFI_ARP_SERVICE_BINDING_PROTOCOL. DestroyChild</strong>
() to destroy the newly three created Arp childs.</td>
</tr>
</tbody>
</table>


### RFC Related

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 15%" />
<col style="width: 22%" />
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
<td>5.24.1.10.1</td>
<td>0x0f6557a8, 0xf383, 0x436e, 0x96, 0x2b, 0x88, 0x2a, 0x28, 0x3c,
0x4c, 0x64</td>
<td><strong>EFI_ARP_PROTOCOL.Rfc –</strong> Send an ARP request and
check the ARP reply .</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Send ARP request to the broadcast address with sender ip
“172.16.210.161” and sender Mac”0:2:3:4:5:7” to resolve the Target
ip”172.16.210.102”.</p>
<p>4. Then the OS side should capture the reply packet.</p>
<p>5. If having captured, dump the reply packet and validate whether the
sender Mac is the MacAddress of TargetMachine.</p>
<p>6. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.1.10.2</td>
<td>0x842c7377, 0x04b6, 0x459f, 0x92, 0x56, 0x39, 0xbf, 0x2e, 0x2f,
0xc5, 0x93</td>
<td><strong>EFI_ARP_PROTOCOL.Rfc –</strong> without reply when sending
an ARP request with opcode invalid.</td>
<td><p>1. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Arp child handle.</p>
<p>2. Call <strong>EFI_ARP_PROTOCOL.Configure()</strong> with valid
parameters.</p>
<p>3. Send ARP request to the broadcast address with sender ip
“172.16.210.161” and sender Mac”0:2:3:4:5:7” to resolve the Target
ip”172.16.210.102” – the opcode set to 255.</p>
<p>4. Then the OS side shouldn’t capture the reply packet.</p>
<p>5. Call
<strong>EFI_ARP_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created Arp child handle and clean up the
environment.</p></td>
</tr>
</tbody>
</table>



## EFI_DHCP4_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DHCP4_PROTOCOL Section.

### GetModeData()

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
<td>5.24.2.1.1</td>
<td>0x52159e94, 0x4a67, 0x44f6, 0x9b, 0x0b, 0x83, 0x21, 0x93, 0x41,
0xe1, 0xf3</td>
<td><strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> - invokes
<strong>GetModeData()</strong> to get all mode data when the Dhcp4 child
has not been configured.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get all
mode data when the Dhcp4 child has not been configured. The
ModeData.State should be Dhcp4Stopped.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to verify the
Dhcp4 child in the Dhcp4Stopped state.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.1.2</td>
<td>0x969e5dac, 0x2097, 0x4a3f, 0xaa, 0x15, 0xb0, 0x6d, 0xff, 0x26,
0x48, 0xec</td>
<td><strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> - invokes
<strong>GetModeData()</strong> to get DHCP4 mode data during the
configuration process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data when the Dhcp4 child has been configured. The
ModeData.State should be Dhcp4Init.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data during the configuration process. The ModeData.State
should be Dhcp4Selecting.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.1.3</td>
<td>0xca520116, 0x5097, 0x4cda, 0x80, 0x79, 0x4a, 0x9b, 0x8f, 0xdd,
0x88, 0x38</td>
<td><strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> - invokes
<strong>GetModeData()</strong> to get DHCP4 mode data during the
configuration process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.1.24".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data when the Dhcp4 child has been configured. The
ModeData.State should be Dhcp4InitReboot.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data during the configuration process. The ModeData.State
should be Dhcp4Rebooting.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>


### Configure()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
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
<td>5.24.2.2.1</td>
<td>0xbd919c90, 0x708b, 0x4502, 0xad, 0xd7, 0xd5, 0x85, 0x30, 0x4b,
0x84, 0x0e</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> when this driver instance was not in the
Dhcp4Stopped, Dhcp4Init, Dhcp4InitReboot, or Dhcp4Bound state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data during the configuration process. The ModeData.State
should be Dhcp4Selecting.The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
the child during the configuration process. The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>6. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.2.2</td>
<td>0x57b62321, 0x14a8, 0x4412, 0xb4, 0x20, 0xad, 0x49, 0x5d, 0x6a,
0xab, 0xbb</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> when Another instance is already in a valid
configured state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child1.</p>
<p>2. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child2.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child1.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child2. The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.2.3</td>
<td>0x5101b2b6, 0x8021, 0x4a04, 0x90, 0x83, 0xf6, 0x6b, 0x9f, 0x4d,
0x10, 0x1f</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> with invalid parameters, among which
<em>DiscoverTryCount</em> is positive and <em>DiscoverTimeout</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
the new instance with a <em>DiscoverTryCount</em> value of positive and
a <em>DiscoverTimeout</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PATAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.2.4</td>
<td>0x50f034a4, 0x2aa4, 0x4d1a, 0x8a, 0x8c, 0x9d, 0x7c, 0x06, 0x48,
0xc9, 0x35</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> with invalid parameters, among which
<em>RequestTryCount</em> is positive and <em>RequestTimeout</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
the new instance with a <em>RequestTryCount</em> value of positive and a
<em>RequestTimeout</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PATAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.2.5</td>
<td>0xc199419b, 0x62b1, 0x4cda, 0xb4, 0x38, 0x9d, 0xcd, 0xed, 0x4d,
0x83, 0x6d</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> with invalid parameters, among which
<em>OptionCount</em> is positive and <em>OptionList</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
the new instance with a <em>OptionCount</em> value of positive and a
<em>OptionList</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PATAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.2.6</td>
<td>0xada01077, 0x4869, 0x4c21, 0x8f, 0x6d, 0x6e, 0x65, 0x93, 0x41,
0xbc, 0xa6</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> with invalid parameters, except that
<em>ClientAddress</em> is an invalid unicast address.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
the new instance with a <em>ClientAddress</em> value of an invalid
unicast address. The return status should be
<strong>EFI_INVALID_PATAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.2.7</td>
<td>0xde6079f0, 0x4aa4, 0x4665, 0x80, 0x8b, 0xa0, 0x22, 0x3c, 0x8b,
0xf6, 0x40</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> to Validate the configuration data effect
before and after calling Dhcp.start() to start the Configuration.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to check
the configuration data effect.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>6. Call Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to
configure child with setting <em>ClientAddress</em> "192.168.2.3".</p>
<p>7. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to check
the configuration data effect.</p>
<p>8. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL.</strong></p>
<p>9. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>10. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.2.8</td>
<td>0x73401b2e, 0x30aa, 0x422d, 0xa3, 0xca, 0x9f, 0x36, 0x78, 0x1c,
0xfa, 0x94</td>
<td><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> to Validate the configuration data effect
before and after calling <strong>Dhcp-&gt;star</strong>t to start the
Configuration, Call <strong>Dhcp.stop()</strong> before calling
<strong>Dhcp.start()</strong> again.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to check
the configuration data effect.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration.</p>
<p>6. Call Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to
configure child with setting <strong>ClientAddress</strong>
"192.168.2.3".</p>
<p>7. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to check
the configuration data effect.</p>
<p>8. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> again to start
the configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>9. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>10. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.2.9</td>
<td>0x1a27208e, 0x08a8, 0x42a6, 0xb9, 0x3f, 0x8b, 0x95, 0x94, 0x24,
0x46, 0xb7</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.Configure()</strong> - invokes
<strong>Configure()</strong> with the following condition:</p>
<p>if one instance wants to make it possible for another instance to
configure successfully, it must call
<strong>EFI_DHCP4_PROTOCOL.Configure()</strong> with DhcpCfgData set to
<strong>NULL</strong>.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child1.</p>
<p>2. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child2.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child1.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child2. The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child1 with setting <em>ConfigData</em> to <strong>NULL</strong>. The
return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child2. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Start()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 15%" />
<col style="width: 24%" />
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
<td>5.24.2.3.1</td>
<td>0xbac2be63, 0xd705, 0x4667, 0x9d, 0x1b, 0x04, 0xe0, 0x5e, 0xeb,
0xcb, 0x3a</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> when the driver instance is in the Dhcp4Stopped
state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>. The return status should be
<strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.2</td>
<td>0xc67ae0d7, 0x3401, 0x4daf, 0xa6, 0x4c, 0xb9, 0xa6, 0x0e, 0xea,
0x17, 0x71</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> with no response during the specified timeout
value.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>. The return status should be
<strong>EFI_TIMEOUT</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.3</td>
<td>0xd7cd1980, 0x7509, 0x4612, 0x80, 0xc0, 0x5c, 0x21, 0x5b, 0x9e,
0x8e, 0x10</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> while the user aborts the DHCP process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0" and
Dhcp4Callback=1(Callbackfunctionlist[1]=Aborted)</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>. The return status should be
<strong>EFI_ABORTED</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.4</td>
<td>0x580e7e81, 0x506d, 0x4339, 0xb7, 0xc2, 0x9f, 0x05, 0x53, 0x8f,
0xf5, 0xde</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> to start configuration process while another
instance has already started the DHCP process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child1.</p>
<p>2. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child2.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child1.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process of child1 with a <em>CompletionEvent</em> value
other than <strong>NULL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process of child2 with a <em>CompletionEvent</em> value of
<strong>NULL</strong>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process of child1.</p>
<p>7. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process of child2.</p>
<p>8. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.5</td>
<td>0x8bd59e83, 0x3f3a, 0x4649, 0xb8, 0x61, 0x36, 0x56, 0x23, 0x5c,
0x8f, 0x7d</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and Asynchronous Mode.
(Calling functions in sequence A).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of not
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.6</td>
<td>0xaca2403d, 0x458b, 0x4c8e, 0x8f, 0x77, 0x1f, 0x87, 0x85, 0x31,
0x08, 0xed</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and Asynchronous Mode.
(Calling functions in sequence B).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.7</td>
<td>0x7344b984, 0x306d, 0x467b, 0xa4, 0x3d, 0x36, 0x77, 0xf8, 0xc9,
0x79, 0x78</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and Asynchronous Mode.
(Calling functions in sequence C).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPNAK packet. The
ModeData.State should be Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.8</td>
<td>0xf9a23299, 0xeb65, 0x472b, 0xbe, 0x96, 0xe5, 0xea, 0x77, 0x2e,
0x03, 0xc0</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and Asynchronous Mode.
(Calling functions in sequence A).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.9</td>
<td>0x723e3088, 0x5f48, 0x4b09, 0x9b, 0x17, 0x80, 0x45, 0x86, 0xf9,
0x9a, 0xad</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and Asynchronous Mode.
(Calling functions in sequence B).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver havng stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.10</td>
<td>0xa8fcde55, 0x522b, 0x49ea, 0xbc, 0xe8, 0x6b, 0xea, 0x80, 0x57,
0x91, 0x21</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and Asynchronous Mode.
(Calling functions in sequence C).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPNAK packet. The
ModeData.State should be Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.11</td>
<td>0x941de4e1, 0xc289, 0x417b, 0x87, 0xeb, 0xef, 0x3e, 0x1e, 0xc0,
0x12, 0x3d</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and synchronous Mode.
(Calling functions in sequence A).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.12</td>
<td>0xff3f4b6d, 0x2b40, 0x49b5, 0xb9, 0xe0, 0x7e, 0x11, 0x8a, 0x73,
0x70, 0x0a</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and synchronous Mode.
(Calling functions in sequence B).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.13</td>
<td>0x35972f03, 0x90dc, 0x41ae, 0x8e, 0x1e, 0x27, 0x72, 0x47, 0x3b,
0x06, 0xb6</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4Init State and synchronous Mode.
(Calling functions in sequence C).</td>
<td><p><strong>1. Call
EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to create a
new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPNAK packet. The
ModeData.State should be Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.14</td>
<td>0x90924db4, 0x1237, 0x4d59, 0x88, 0xf3, 0x11, 0x8b, 0xed, 0x01,
0x80, 0xae</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and synchronous Mode.
(Calling functions in sequence A).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.3.15</td>
<td>0x434f1845, 0xd940, 0x4129, 0xaa, 0xeb, 0x7a, 0x1b, 0xe7, 0xe1,
0x39, 0x48</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and synchronous Mode.
(Calling functions in sequence B).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.3.16</td>
<td>0x340ff4c6, 0x7412, 0x44d4, 0x8f, 0x33, 0xeb, 0xc2, 0x6f, 0x22,
0x1d, 0x0c</td>
<td><strong>EFI_DHCP4_PROTOCOL.Start()</strong> - invokes
<strong>Start()</strong> in Dhcp4InitReboot State and synchronous Mode.
(Calling functions in sequence C).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPNAK packet. The
ModeData.State should be Dhcp4Init.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>


### RenewRebind()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 14%" />
<col style="width: 24%" />
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
<td>5.24.2.4.1</td>
<td>0x15bdc212, 0xbad5, 0x4213, 0xb2, 0x38, 0x50, 0xac, 0x76, 0x18,
0xdc, 0x90</td>
<td><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> when the driver instance is in the
Dhcp4Stopped state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong>. The return status
should be <strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong>. The return
status should be <strong>EFI_NOT_STARTED</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.4.2</td>
<td>0x2949dc87, 0xdbcd, 0x4d64, 0x8f, 0x10, 0x68, 0x2f, 0xa2, 0x27,
0xe0, 0x88</td>
<td><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> while getting no response during the
specified time.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong> and a
<em>CompletionEvent</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_TIMEOUT</strong>.</p>
<p>6. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.4.3</td>
<td>0xd7f4cb11, 0xc3dc, 0x421f, 0x98, 0x80, 0x5c, 0x2a, 0x2d, 0x73,
0x06, 0x02</td>
<td><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> when the driver instance is not in the
Dhcp4Bound state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having sent the DHCPREQUEST packet. The
ModeData.State should be Dhcp4Rebooting.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong> and a
<em>CompletionEvent</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>6. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.4.4</td>
<td>0x38bb70ba, 0xb05c, 0x4431, 0xb4, 0xf9, 0x8f, 0x4e, 0x9b, 0x10,
0xc7, 0x54</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in Asynchronous Mode using unicast.</p>
<p>(Calling functions in sequence A).</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong> and a
<em>CompletionEvent</em> value of not <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.4.5</td>
<td>0x432ccefe, 0x8586, 0x4358, 0xb7, 0xee, 0xf1, 0x36, 0xe3, 0x8a,
0xd8, 0x30</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in Asynchronous Mode using unicast.</p>
<p>(Calling functions in sequence B).</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong> and a
<em>CompletionEvent</em> value of not <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.4.6</td>
<td>0xc0b17d39, 0x32bb, 0x41f8, 0xbd, 0x44, 0x6b, 0xb8, 0x53, 0x0f,
0xa4, 0xaf</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in Asynchronous Mode using broadcast.</p>
<p>(Calling functions in sequence A).</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong> and a
<em>CompletionEvent</em> value of not <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.4.7</td>
<td>0x819f530e, 0x0d51, 0x43ce, 0x83, 0x73, 0x0b, 0x27, 0xc6, 0x36,
0x3b, 0x63</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in Asynchronous Mode using broadcast.</p>
<p>Sequence B.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong> and a
<em>CompletionEvent</em> value of not <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.4.8</td>
<td>0x982b5d48, 0x2d87, 0x40ea, 0xbe, 0x60, 0x44, 0x60, 0x49, 0xfe,
0x08, 0x98</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in synchronous Mode using unicast.</p>
<p>Sequence A.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong> and a
<em>CompletionEvent</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.4.9</td>
<td>0x4cc9abee, 0xd9e8, 0x444b, 0xb8, 0x34, 0x3e, 0xd4, 0x57, 0x96,
0x25, 0xc9</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in synchronous Mode using unicast.</p>
<p>Sequence B.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of not
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong> and a
<em>CompletionEvent</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.4.10</td>
<td>0x061ca38f, 0x5092, 0x483b, 0xa4, 0xd2, 0xf3, 0x1f, 0x53, 0x3f,
0xe7, 0xac</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in synchronous Mode using broadcast.</p>
<p>Sequence A.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>FALSE</strong> and a
<em>CompletionEvent</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.4.11</td>
<td>0xf9fa2078, 0x6283, 0x4510, 0xad, 0x21, 0xba, 0xe1, 0x15, 0x21,
0x56, 0xf9</td>
<td><p><strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> - invokes
<strong>RenewRebind()</strong> with the driver instance extending lease
time in synchronous Mode using broadcast.</p>
<p>Sequence B.</p></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.RenewRebind()</strong> with a
<em>RebindRequest</em> value of <strong>TRUE</strong> and a
<em>CompletionEvent</em> value of not <strong>NULL</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Bound.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>


### Release()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.24.2.5.1</td>
<td>0xa80fa204, 0x87dd, 0x4e92, 0x8a, 0x5d, 0xee, 0x55, 0x6c, 0x83,
0xac, 0x7c</td>
<td><strong>EFI_DHCP4_PROTOCOL.Release()</strong> - invokes
<strong>Release()</strong> with the driver in the configuration process,
but not in the Dhcp4Bound or Dhcp4InitReboot state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of not
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Release()</strong> after Stop the
REQUEST packet from the driver. The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.5.2</td>
<td>0x70f9485c, 0x4fef, 0x4bf3, 0xac, 0xd5, 0x2e, 0xe0, 0xba, 0x30,
0x3d, 0xd9</td>
<td><strong>EFI_DHCP4_PROTOCOL.Release()</strong> - invokes
<strong>Release()</strong> with the driver in the Dhcp4Stopped state,
but not in the Dhcp4Bound or Dhcp4InitReboot state.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to verify the
driver in the Dhcp4Stopped state.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Release()</strong> when the driver
is in the Dhcp4Stopped state. The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.5.3</td>
<td>0x67c1be03, 0xf9c4, 0x4419, 0x88, 0xf0, 0xb9, 0xfc, 0x6c, 0x1a,
0xd2, 0x67</td>
<td><strong>EFI_DHCP4_PROTOCOL.Release()</strong> - invokes
<strong>Release()</strong> when the driver is in the DhcpBound
State<strong>.</strong></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "0.0.0.0".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value of
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after the driver having stopped the DHCPACK packet. The
ModeData.State should be Dhcp4Bound.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Release()</strong> and capture
ARPREQUEST packet from the driver, send ARPREPLY packet to the driver,
then capture DHCPRELEASE packet from the driver. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.5.4</td>
<td>0x555d101b, 0xf86a, 0x4e6f, 0x95, 0x70, 0x1c, 0xfa, 0xe7, 0xd2,
0xd6, 0x8a</td>
<td><strong>EFI_DHCP4_PROTOCOL.Release()</strong> - invokes
<strong>Release()</strong> when the driver is in the DhcpInitReboot
State<strong>.</strong></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data. The ModeData.State should be DhcpInitReboot.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Release()</strong> and capture
ARPREQUEST packet from the driver, send ARPREPLY packet to the driver,
then capture DHCPRELEASE packet from the driver. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after time out. The ModeData.State should be
Dhcp4Init.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Stop()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.24.2.6.1</td>
<td>0xda8661a5, 0x82d4, 0x4b1b, 0xa2, 0x68, 0xf3, 0x4f, 0xe5, 0xab,
0x03, 0x57</td>
<td><strong>EFI_DHCP4_PROTOCOL.Stop()</strong> - invokes
<strong>Stop()</strong> when the driver is in the DhcpInitReboot
State<strong>.</strong></td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after receiving REQUEST packet from the driver. The
ModeData.State should be DhcpInitReboot.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.6.2</td>
<td>0x0f6193fc, 0x21f7, 0x4831, 0xbf, 0x53, 0x39, 0x28, 0xc0, 0x49,
0x6b, 0x48</td>
<td><strong>EFI_DHCP4_PROTOCOL.Stop()</strong> - invokes
<strong>Stop()</strong> when the driver is in the configuration
process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Configure()</strong> to configure
child with setting <em>ClientAddress</em> "192.168.2.4".</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Start()</strong> to start the
configuration process with a <em>CompletionEvent</em> value other than
<strong>NULL</strong>.</p>
<p>4. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data after receiving REQUEST packet from the driver. The
ModeData.State should be Dhcp4Rebooting.</p>
<p>5. Call <strong>EFI_DHCP4_PROTOCOL.Stop()</strong> to stop the
configuration process. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call <strong>EFI_DHCP4_PROTOCOL.GetModeData()</strong> to get
Dhcp4 mode data. The ModeData.State should be Dhcp4Stopped.</p>
<p>7. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Build()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.24.2.7.1</td>
<td>0xc2aa2960, 0xdd52, 0x4e56, 0x87, 0x7e, 0x8c, 0x44, 0x6a, 0x5e,
0xea, 0x31</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>SeedPacket</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with a
<em>SeedPacket</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.7.2</td>
<td>0xf19cc8c3, 0x9a84, 0x4d62, 0x94, 0xae, 0xc3, 0x4b, 0x06, 0x3a,
0xea, 0x91</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>SeedPacket</em> is not a
well-formed DHCP packet (Magic Number Error).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with a
SeedPacket.<strong>EFI_DHCP4_PROTOCOL</strong>.Magik value of error
magic cookie. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.7.3</td>
<td>0xc650067b, 0x4ab0, 0x4170, 0x9b, 0x4b, 0x4f, 0x7a, 0xeb, 0x77,
0xc0, 0x5e</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>AppendCount</em> is not
0 and <em>AppendList</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with a
<em>AppendCount</em> value other than <strong>NULL</strong> and
<em>AppendList</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.7.4</td>
<td>0x1debfafe, 0xdfbe, 0x4ff5, 0x8a, 0xcd, 0x8f, 0xe1, 0x11, 0x82,
0x30, 0xe0</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>DeleteCount</em> is not
0 and <em>DeleteList</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with a
<em>DeleteCount</em> value of <strong>NULL</strong> and a
<em>DeleteList</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.7.5</td>
<td>0xd0beca24, 0xa8f3, 0x4753, 0x8c, 0xdb, 0x96, 0xe6, 0x00, 0x92,
0x78, 0x47</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>NewPacket</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with a
<em>NewPacket</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.7.6</td>
<td>0x7d05c782, 0xccf3, 0x42d0, 0x9a, 0x6e, 0x0d, 0x6b, 0x5c, 0x8d,
0x9c, 0x20</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter both <em>DeleteCount</em>
and <em>OptionCount</em> are 0 and <em>NewPacket</em> is not
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with both the
<em>DeleteCount</em> and <em>OptionCount</em> value of 0 and a
<em>NewPacket</em> value other than <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.7.7</td>
<td>0xf52d8032, 0xd5c6, 0x48e1, 0x86, 0xb0, 0xac, 0x47, 0xae, 0x82,
0x93, 0xed</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> when the parameter <em>AppendCount</em> and
<em>AppendList</em> are not <strong>NULL</strong>, and build a new
packet with DHCP options appended.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with both the
<em>AppendCount</em> and <em>AppendList</em> value other than
<strong>NULL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to parse the
packet returned by the parameter <em>NewPacket</em> of
<strong>EFI_DHCP4_PROTOCOL.Build()</strong>. The <em>NewPacket</em>
should include the DHCP options matching the parameter
<em>AppendList</em> of <strong>EFI_DHCP4_PROTOCOL.Build()</strong>.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.7.8</td>
<td>0x78dae7e2, 0x579a, 0x47a1, 0xb2, 0x45, 0x8c, 0xad, 0x39, 0xc8,
0x07, 0x27</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> to delete defined options.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with both the
<em>DeleteCount</em> and <em>DeleteList</em> value other than
<strong>NULL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to parse the
packet returned by the parameter <em>NewPacket</em> of
<strong>EFI_DHCP4_PROTOCOL.Build()</strong>. The <em>NewPacket</em>
should not include the DHCP options matching the parameter
<em>DeleteList</em> of <strong>EFI_DHCP4_PROTOCOL.Build()</strong>.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.7.9</td>
<td>0xfc1f9cb7, 0xed3d, 0x4e6d, 0x93, 0x2a, 0x63, 0xb5, 0xcf, 0xb4,
0xb3, 0x37</td>
<td><strong>EFI_DHCP4_PROTOCOL.Build()</strong> - invokes
<strong>Build()</strong> to delete an undefined option.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Build()</strong> with both the
<em>DeleteCount</em> and <em>DeleteList</em> value other than
<strong>NULL</strong>, and <em>DeleteList</em> include an undefined
option. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to parse the
packet returned by the parameter <em>NewPacket</em> of
<strong>EFI_DHCP4_PROTOCOL.Build()</strong>. The <em>NewPacket</em>
should not include the DHCP options matching the parameter
<em>DeleteList</em> of <strong>EFI_DHCP4_PROTOCOL.Build()</strong>.</p>
<p>4. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Transmit**Receive()**

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.24.2.8.1</td>
<td>0x6d1bb6a7, 0x5d67, 0x4982, 0x96, 0x35, 0x54, 0xeb, 0x4b, 0x0c,
0xfa, 0xd5</td>
<td><strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> - invokes
<strong>TransmitReceive()</strong> when the parameter
<em>RemoteAddress</em> is 0.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> with a
<em>RemoteAddress</em> value of 0. The return status should be
<strong>EFI_UNSUPPORTED</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.8.2</td>
<td>0xd2bec02f, 0x8304, 0x4713, 0x8a, 0x95, 0x4b, 0xd3, 0x4c, 0x69,
0x89, 0xc0</td>
<td><strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> - invokes
<strong>TransmitReceive()</strong> when the parameter <em>Packet</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> with a
<em>Packet</em> value of <strong>NULL</strong>. The return status should
be <strong>EFI_UNSUPPORTED</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.8.3</td>
<td>0x9dfd549b, 0x59eb, 0x4f5d, 0x99, 0x5f, 0xb8, 0x2d, 0xdd, 0x18,
0x02, 0xba</td>
<td><strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> - invokes
<strong>TransmitReceive()</strong> when the parameter <em>Packet</em> is
not a well-formed DHCP packet(Magic Number error).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> with a
<em>Packet</em> value of not a well-formed DHCP packet(Magic Number
error). The return status should be <strong>EFI_UNSUPPORTE</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.8.4</td>
<td>0xce99ae23, 0x910a, 0x4818, 0xa0, 0x89, 0xf3, 0xf4, 0x5b, 0xc5,
0xeb, 0xa8</td>
<td><strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> - invokes
<strong>TransmitReceive()</strong> when the transaction ID in
<em>Packet</em> is in used by another DHCP process.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> when
the transaction ID in <em>Packet</em> is in use by another DHCP process.
The return status should be <strong>EFI_UNSUPPORTED</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.8.5</td>
<td>0xbe6683bd, 0x807a, 0x4fb0, 0xbc, 0x7b, 0xf7, 0x51, 0x07, 0x0e,
0x0e, 0x66</td>
<td><strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> - invokes
<strong>TransmitReceive()</strong> when the previous call to this
function has not finished yet. Try to call this function after
collection process completed.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.TransmitReceive()</strong> with
the previous call to this function not finished yet. The return status
should be <strong>EFI_UNSUPPORTE</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Parse()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 16%" />
<col style="width: 24%" />
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
<td>5.24.2.9.1</td>
<td>0x7cca1a2c, 0x4136, 0x4ff0, 0xbc, 0x22, 0xca, 0x80, 0x56, 0x8d,
0xfd, 0xbf</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the parameter <em>Packet</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>Packet</em> value of <strong>NULL</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.9.2</td>
<td>0x225ddf1b, 0x9fb9, 0x4a9b, 0xb3, 0xb6, 0xca, 0x25, 0xeb, 0x31,
0x0d, 0xbb</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the parameter <em>OptionCount</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>OptionCount</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.9.3</td>
<td>0xea1a95dd, 0xdb6c, 0x4200, 0xb7, 0xc7, 0x19, 0xb0, 0xa3, 0x81,
0x06, 0x5d</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the <em>Packet</em> is not a well-formed
DHCP packet (Magic Number error).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>Packet</em> value other than a well-formed DHCP packet (Magic Number
error). The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.9.4</td>
<td>0x91e4d243, 0x4ed6, 0x451a, 0xb0, 0x9c, 0x0a, 0x35, 0x6a, 0x06,
0x1d, 0xda</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the <em>Packet</em> is not well-formed
DHCP packet (No End option).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>Packet</em> value other than a well-formed DHCP packet (No End
option). The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.9.5</td>
<td>0xd836cddd, 0x6bb4, 0x455e, 0x9e, 0xc4, 0x49, 0x9f, 0xc3, 0x27,
0xdd, 0x21</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the <em>Packet</em> is not a well-formed
DHCP packet (Length &lt; Header Size).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>Packet</em> value other than a well-formed DHCP packet (Length &lt;
Header Size). The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.9.6</td>
<td>0xed5c8f2b, 0x0043, 0x4f43, 0xae, 0x83, 0xa6, 0xbf, 0xab, 0x5b,
0xa2, 0xba</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the <em>Packet</em> is not a well-formed
DHCP packet (Size &lt; Length).</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>Packet</em> value other than a well-formed DHCP packet (Size &lt;
Length). The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.9.7</td>
<td>0x4bd82a66, 0xcede, 0x4132, 0xa8, 0xca, 0xd9, 0x95, 0xe8, 0xe7,
0x9a, 0xb2</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when the parameter <em>OptionCount</em> is
smaller than the number of options that were found in the
<em>Packet</em>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with the
parameter <strong>OptionCount</strong> smaller than the number of
options that were found in the <em>Packet</em>. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.9.8</td>
<td>0xa73ac67a, 0xe5c9, 0x41e7, 0xb6, 0xc0, 0x80, 0xa2, 0x6f, 0x27,
0x7e, 0xc0</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<em>Parse()</em> when the parameter <em>PacketOptionList</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> with a
<em>PacketOptionList</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.9.9</td>
<td>0xc84a412c, 0x702a, 0x40e1, 0xa3, 0x9c, 0x55, 0xa8, 0x8c, 0xbe,
0x60, 0x5a</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when options exist in packet.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to check the
<em>PacketOptionList</em> when options exist in packet. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.9.10</td>
<td>0x2ba25811, 0x4069, 0x45da, 0xb3, 0x9e, 0xfa, 0x05, 0x14, 0x42,
0x4a, 0x4c</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> when no options exist in packet</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to check the
<em>PacketOptionList</em> when no options exist in packet. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.24.2.9.11</td>
<td>0x6ce744e5, 0x9e5a, 0x4fb5, 0xa5, 0xf2, 0x3b, 0xe8, 0xf5, 0xb5,
0xad, 0x42</td>
<td><strong>EFI_DHCP4_PROTOCOL.Parse()</strong> - invokes
<strong>Parse()</strong> with Pad Option included in packet</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call <strong>EFI_DHCP4_PROTOCOL.Parse()</strong> to check the
<em>PacketOptionList</em> with Pad Option included in packet. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### CreateChild()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.24.2.10.1 | 0x4b66733f, 0xd324, 0x4af9, 0x9d, 0x92, 0x91, 0x4f, 0x5f, 0x77, 0x2e, 0xf0 | **EFI_DHCP4_PROTOCOL.CreateChild()** - invokes CreateChild() when Child Handle is **NULL**. | 1\. Call **EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()** to create a new Dhcp4 child with **NULL** Handle Pointer. The return status should be **EFI_INVALID_PATAMETER**. |
| 5.24.2.10.2 | 0x1e0f5047, 0x1be9, 0x4db0, 0xa5, 0x71, 0xfc, 0x82, 0xbc, 0x2d, 0x0a, 0x06 | **EFI_DHCP4_PROTOCOL.CreateChild()** - to test the function of **CreateChild()**. | Call **EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()** to create childs three times and then destroy them. |


### DestroyChild()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 16%" />
<col style="width: 25%" />
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
<td>5.24.2.11.1</td>
<td>0x1f92470a, 0x7aec, 0x4fb4, 0xa4, 0x0d, 0x5f, 0x0c, 0xd2, 0x40,
0x1f, 0x08</td>
<td><strong>EFI_DHCP4_PROTOCOL.DestroyChild()</strong> – invokes
<strong>DestroyChild()</strong> when Call this function twice.</td>
<td><p>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new Dhcp4 child.</p>
<p>2. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created Dhcp4 child again. The return status should be
<strong>EFI_UNSUPPORTED</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.24.2.11.2</td>
<td>0x06b43e55, 0xd8af, 0x494f, 0x8b, 0x93, 0x78, 0xf8, 0xd0, 0x7a,
0xa4, 0xc8</td>
<td><strong>EFI_DHCP4_PROTOCOL.DestroyChild()</strong> – invokes
<strong>DestroyChild()</strong> when Child Handle is
<strong>NULL</strong>.</td>
<td>1. Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
Destroy a Dhcp4 child with <strong>NULL</strong> Handle Pointer. The
return status should be <strong>EFI_INVALID_PATAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.24.2.11.3</td>
<td>0xc44a4b68, 0x1f16, 0x4098, 0xb2, 0x6d, 0x2c, 0x43, 0xcb, 0x27,
0x4d, 0xae</td>
<td><strong>EFI_DHCP4_PROTOCOL.DestroyChild()</strong> – to test the
function of <strong>DestroyChild()</strong>.</td>
<td>Call
<strong>EFI_DHCP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly three created Dhcp4 childs.</td>
</tr>
</tbody>
</table>


## EFI_DHCP6_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DHCP6_PROTOCOL Section.

### CreateChild()

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
<td>5.24.3.1.1</td>
<td>0xbd25610a, 0xa4b3, 0x412a, 0xbf, 0x03, 0xb0, 0xf7, 0xce, 0x80,
0x98, 0xbf</td>
<td><strong>EFI_DHCP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <strong>NULL</strong> <em>ChildHandle</em>.</td>
<td>Call <strong>CreateChild()</strong> with a <strong>NULL</strong>
<em>ChildHandle</em>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.1.2</td>
<td>0xcbf5cb1d, 0xd74d, 0x45bc, 0x94, 0xd2, 0x72, 0xda, 0x7f, 0xf7,
0xbe, 0xda</td>
<td><strong>EFI_DHCP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
1<sup>st</sup> valid <em>ChildHandle</em>.</td>
<td><p>5.24.3.1.2 to 5.24.3.1.5 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> with the 1<sup>st</sup> valid
<em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.24.3.1.3</td>
<td>0xb9cfe63d, 0x2cc2, 0x4940, 0xb3, 0x01, 0x39, 0x22, 0xf3, 0xff,
0xdd, 0x35</td>
<td><strong>EFI_DHCP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
2<sup>nd</sup> valid <em>ChildHandle</em>.</td>
<td>2. Call <strong>CreateChild()</strong> with the 2<sup>nd</sup> valid
<em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.1.4</td>
<td>0x2336ebe8, 0x4934, 0x4a6c, 0xae, 0x72, 0x06, 0x73, 0xb6, 0x7a,
0xa0, 0xa6</td>
<td><strong>EFI_DHCP6_SERVICE_BINDING_PROTOCOL.DestroyChild() -
DestroyChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
2<sup>nd</sup> valid <em>ChildHandle</em>.</td>
<td>3. Call <strong>DestroyChild()</strong> with the 2<sup>nd</sup>
valid <em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.24.3.1.5</td>
<td>0x0fe6555e, 0x3487, 0x4989, 0x89, 0x96, 0x18, 0xa7, 0x2a, 0x71,
0x52, 0xd5</td>
<td><strong>EFI_DHCP6_SERVICE_BINDING_PROTOCOL.DestroyChild() -
DestroyChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
1<sup>st</sup> valid <em>ChildHandle</em>.</td>
<td>4. Call <strong>DestroyChild()</strong> with the 1<sup>st</sup>
valid <em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


### DestroyChild ()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.24.3.2.1 | 0x6e2206aa, 0xbee7, 0x4f16, 0xa7, 0xaa, 0x71, 0x54, 0xa2, 0xe9, 0x63, 0x65 | **EFI_DHCP6_SERVICE_BINDING_PROTOCOL. DestroyChild() - DestroyChild()** returns **EFI_INVALID_PARAMETER** with a **NULL** *ChildHandle.* | Call **DestroyChild()** with a **NULL** *ChildHandle*, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.24.3.2.2 | 0x061893a7, 0x48de, 0x431a, 0xad, 0x5b, 0x56, 0x29, 0xb6, 0x9c, 0xe6, 0xce | **EFI_DHCP6_SERVICE_BINDING_PROTOCOL. DestroyChild() - DestroyChild()** returns **EFI_UNSUPPORTED** with a *ChildHandle* which has been destroyed. | Call **DestroyChild()** with a *ChildHandle* which has been destroyed, the return status should be **EFI_UNSUPPORTED**. |



### GetModeData()

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
<td>5.24.3.3.1</td>
<td>0x3678146a, 0x0596, 0x4661, 0x8e, 0x53, 0xf6, 0x61, 0xa6, 0xec,
0xe2, 0xf3</td>
<td><strong>EFI_DHCP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> with an instance which has
not been configured.</td>
<td>Call <strong>GetModeData()</strong>with an instance which has not
been configured, The return status should be
<strong>EFI_ACCESS_DENIED</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.3.2</td>
<td>0xf58195a9, 0x1924, 0x4490, 0x95, 0x4b, 0x17, 0x75, 0xfc, 0x1c,
0xbf, 0xb0</td>
<td><strong>EFI_ DHCP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>NULL</strong> <strong>Dhcp6ConfigData</strong> and
<strong>Dhcp6ModeData</strong></td>
<td>Call <strong>GetModeData()</strong>with <strong>NULL</strong>
<strong>Dhcp6ConfigData</strong> and <strong>Dhcp6ModeData,</strong> The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.24.3.3.3</td>
<td>0x99d01c9a, 0x2bd6, 0x442f, 0x8f, 0xe5, 0xda, 0x8a, 0xa6, 0x88,
0x27, 0x29</td>
<td><strong>Dhcp6CfgData.CallbackContext</strong> should be 5.</td>
<td><p>5.24.3.3.3 to 5.24.3.1.13 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create an event for the Dhcp6CfgData</p>
<p>3. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>4. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>5. The <strong>Dhcp6CfgData.CallbackContext</strong> should be 5. The
reason is Callback() is called by
SendSolict/RcvdAdvertise/SelectAdvertise/SendRequest/RcvdReply.
Callback() add <strong>Dhcp6CfgData.CallbackContext</strong> with 1 each
time.</p></td>
</tr>
<tr class="odd">
<td>5.24.3.3.4</td>
<td>0x46993cb1, 0xfb2c, 0x44b3, 0xad, 0xe1, 0x7e, 0xa1, 0xe8, 0x43,
0xbd, 0x2e</td>
<td><strong>Dhcp6CfgData.IaInfoEvent</strong> should be signaled.</td>
<td>6. When <strong>Start</strong>() return, the
<strong>Dhcp6CfgData.IaInfoEvent</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.24.3.3.5</td>
<td>0x6a6bd40b, 0xb963, 0x4313, 0x8b, 0x4f, 0x45, 0x0e, 0x11, 0x4b,
0x6e, 0xeb</td>
<td><strong>EFI_ DHCP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with
<strong>Dhcp6ConfigData</strong> and <strong>Dhcp6ModeData</strong></td>
<td>7. Call <strong>GetModeData()</strong>with
<strong>Dhcp6ConfigData</strong> and <strong>Dhcp6ModeData,</strong> The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.3.6</td>
<td>0x24694dfa, 0x5cc6, 0x4358, 0x9a, 0x14, 0x5c, 0xf2, 0x5e, 0x3a,
0x1a, 0xa4</td>
<td><strong>Dhcp6ModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></td>
<td>8. <strong>Dhcp6ModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></td>
</tr>
<tr class="even">
<td>5.24.3.3.7</td>
<td>0x6a19ff82, 0x9ea9, 0x44c1, 0xb8, 0x71, 0x69, 0x05, 0xfe, 0x18,
0x58, 0xbc</td>
<td><strong>Dhcp6ConfigData.OptionCount</strong> should be same with
configured the value.</td>
<td>9. <strong>Dhcp6ConfigData.OptionCount</strong> should be same with
the configured value.</td>
</tr>
<tr class="odd">
<td>5.24.3.3.8</td>
<td>0x9fa4ae6e, 0x82b3, 0x4ed7, 0xb9, 0xfc, 0x69, 0x0f, 0x0a, 0x98,
0xe5, 0xde</td>
<td><strong>Dhcp6ConfigData.OptionList</strong> should be same with
configured the value.</td>
<td>10. <strong>Dhcp6ConfigData.OptionList</strong> should be same with
the configured value.</td>
</tr>
<tr class="even">
<td>5.24.3.3.9</td>
<td>0xa803b115, 0x47b7, 0x496f, 0x95, 0xdb, 0x38, 0xf2, 0x3e, 0x27,
0x3c, 0x20</td>
<td><strong>Dhcp6ConfigData.IaDescriptor</strong> should be same with
configured the value.</td>
<td>11. <strong>Dhcp6ConfigData.IaDescriptor</strong> should be same
with the configured value.</td>
</tr>
<tr class="odd">
<td>5.24.3.3.10</td>
<td>0x2e4a61f7, 0x3a07, 0x4dd9, 0x8b, 0xf6, 0xc3, 0xef, 0xbb, 0x35,
0xb7, 0x90</td>
<td><strong>Dhcp6ConfigData.</strong> <strong>IaInfoEvent</strong>
should be same with configured the value.</td>
<td>12. <strong>Dhcp6ConfigData.</strong> <strong>IaInfoEvent</strong>
should be same with the configured value.</td>
</tr>
<tr class="even">
<td>5.24.3.3.11</td>
<td>0x32797b99, 0x3b8b, 0x4456, 0x9d, 0xca, 0x3f, 0x76, 0xc6, 0x3f,
0x1c, 0xbf</td>
<td><strong>Dhcp6ConfigData.</strong> <strong>ReconfigureAccept</strong>
should be same with configured the value.</td>
<td>13. <strong>Dhcp6ConfigData.</strong>
<strong>ReconfigureAccept</strong> should be same with the configured
value.</td>
</tr>
<tr class="odd">
<td>5.24.3.3.12</td>
<td>0xb2f4a83b, 0xe44d, 0x4770, 0x81, 0xef, 0xef, 0x06, 0x29, 0xbd,
0x7f, 0xd7</td>
<td><strong>Dhcp6ConfigData.</strong> <strong>RapidCommit</strong>
should be same with configured the value.</td>
<td>14. <strong>Dhcp6ConfigData.</strong> <strong>RapidCommit</strong>
should be same with the configured value.</td>
</tr>
<tr class="even">
<td>5.24.3.3.13</td>
<td>0x45ea153f, 0x2d5f, 0x40b4, 0xbd, 0x34, 0x04, 0x52, 0x27, 0xd9,
0xb5, 0xc3</td>
<td><strong>Dhcp6ConfigData.SolicitRetransmission</strong> should be
same with configured the value.</td>
<td>15. <strong>Dhcp6ConfigData.SolicitRetransmission</strong> should be
same with the configured value.</td>
</tr>
</tbody>
</table>



### Configure()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 17%" />
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
<td>5.24.3.4.1</td>
<td>0x8aa05b75, 0x4bdf, 0x45e6, 0x81, 0x74, 0x21, 0x85, 0x55, 0x88,
0x19, 0x74</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>Dhcp6ConfigData.OptionCount</strong> &gt; 0 and
<strong>Dhcp6ConfigData. OptionList</strong> is
<strong>NULL</strong></td>
<td>Call <strong>Configure()</strong> with
<strong>Dhcp6ConfigData.OptionCount</strong> &gt; 0 and
<strong>Dhcp6ConfigData. OptionList</strong> is <strong>NULL</strong>,
The return status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.2</td>
<td>0xee84c2d5, 0xda69, 0x45ca, 0x9b, 0x62, 0x6c, 0x5f, 0x9a, 0xd9,
0x0d, 0xe2</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>OptionList</strong> containing ClientId option.</td>
<td>Call <strong>Configure()</strong> with <strong>OptionList</strong>
containing ClientId option, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.4.3</td>
<td>0xd6cda19e, 0xcec6, 0x458a, 0xb9, 0xc7, 0x9d, 0x5e, 0xc8, 0x3d,
0xdd, 0x3f</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>OptionList</strong> containing ReconfigAccept option.</td>
<td>Call <strong>Configure()</strong> with <strong>OptionList</strong>
containing ReconfigAccept option, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.4</td>
<td>0x8a694b28, 0x7d56, 0x4171, 0xa9, 0x91, 0x07, 0x89, 0x56, 0x08,
0xf3, 0xb2</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>OptionList</strong> containing RapidCommit option.</td>
<td>Call <strong>Configure()</strong> with <strong>OptionList</strong>
containing RapidCommit option, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.4.5</td>
<td>0x671c33eb, 0x66ab, 0x46db, 0xac, 0x12, 0xb6, 0x41, 0xca, 0xf3,
0xc2, 0xad</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>OptionList</strong> containing IA for Non-temporary Addresses
Option.</td>
<td>Call <strong>Configure()</strong> with <strong>OptionList</strong>
containing IA for Non-temporary Addresses Option, The return status
should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.6</td>
<td>0x438764a3, 0x3419, 0x48c1, 0xbc, 0xb6, 0xa7, 0x82, 0x21, 0xaf,
0x4d, 0xb7</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>OptionList</strong> containing IA for temporary Addresses
Option.</td>
<td>Call <strong>Configure()</strong> with <strong>OptionList</strong>
containing IA for temporary Addresses Option, The return status should
be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.4.7</td>
<td>0x4ae68d37, 0x1f81, 0x41a9, 0xbf, 0x5a, 0xf7, 0x5f, 0xd6, 0xcf,
0x04, 0x11</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an invalid
<strong>IaDescriptor.Type</strong> (neither
<strong>EFI_DHCP6_IA_TYPE_NA</strong> nor
<strong>EFI_DHCP6_IA_TYPE_TA</strong>).</td>
<td>Call <strong>Configure()</strong> with an invalid
<strong>IaDescriptor.Type</strong> (neither
<strong>EFI_DHCP6_IA_TYPE_NA</strong> nor
<strong>EFI_DHCP6_IA_TYPE_TA</strong>), The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.8</td>
<td>0xffb74292, 0x6403, 0x4e09, 0xb3, 0x83, 0xe9, 0xa8, 0x14, 0x98,
0x54, 0xfa</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an
<strong>IaDescriptor</strong> is not unique.</td>
<td>Call <strong>Configure()</strong> with an
<strong>IaDescriptor</strong> is not unique, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.4.9</td>
<td>0x286b8508, 0x13bc, 0x44cc, 0xaa, 0x6a, 0xc2, 0xd9, 0xac, 0xc7,
0xeb, 0x49</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with both
<strong>IaInfoEvent</strong> and <strong>SolicitRetransmission</strong>
<strong>NULL</strong>.</td>
<td>Call <strong>Configure()</strong> with both
<strong>IaInfoEvent</strong> and <strong>SolicitRetransmission</strong>
<strong>NULL</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.10</td>
<td>0xc74fd682, 0x5e75, 0x455d, 0xbf, 0xc2, 0x28, 0xe0, 0xf3, 0x54,
0x34, 0xfa</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with a non <strong>NULL
SolicitRetransmission</strong> while <strong>Mrc</strong> and
<strong>Mrd</strong> are zero.</td>
<td>Call <strong>Configure()</strong>with a non <strong>NULL
Dhcp6ConfigData</strong> while <strong>Mrc</strong> and
<strong>Mrd</strong> are zero, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.4.11</td>
<td>0x49935e3b, 0xe516, 0x423f, 0xa9, 0xb1, 0x99, 0x97, 0xea, 0xd4,
0x1c, 0x96</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> with a non <strong>NULL
Dhcp6ConfigData</strong> while the instance has already been
configured.</td>
<td>Call <strong>Configure()</strong>with a non <strong>NULL
Dhcp6ConfigData</strong> while the instance has already been configured,
The return status should be <strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.12</td>
<td>0x59090898, 0x378c, 0x4555, 0xa6, 0xab, 0x14, 0x10, 0x96, 0xdc,
0x4f, 0xde</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_SUCCESS</strong> with a valid
<strong>Dhcp6ConfigData</strong></td>
<td><p>5.24.3.4.12 to 5.24.3.4.15 belong to one case.</p>
<p>1. Call <strong>Configure()</strong>with a valid
<strong>Dhcp6ConfigData</strong>, The return status should be
<strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.4.13</td>
<td>0x568406ba, 0xa297, 0x4917, 0x8e, 0x7f, 0x77, 0xbb, 0x73, 0x6b,
0x53, 0xae</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_SUCCESS</strong> with a <strong>NULL
Dhcp6ConfigData</strong></td>
<td>2. Call <strong>Configure()</strong>with a <strong>NULL
Dhcp6ConfigData</strong>, The return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.4.14</td>
<td>0x670d8a4d, 0x57e4, 0x424a, 0xbb, 0x72, 0x02, 0xb6, 0x72, 0xb0,
0x2d, 0x78</td>
<td><strong>Dhcp6ModeData.ClientId</strong> should not be 0.</td>
<td><p>3. Call <strong>GetModeData()</strong>to get
<strong>GetModeData.</strong></p>
<p>4. <strong>Dhcp6ModeData.ClientId</strong> should not be 0.</p></td>
</tr>
<tr class="even">
<td>5.24.3.4.15</td>
<td>0x93080b8e, 0x5908, 0x4c54, 0x8d, 0xa7, 0xf6, 0x73, 0x2c, 0x66,
0x68, 0x92</td>
<td><strong>Dhcp6ModeData.Ia</strong> should be 0.</td>
<td>5. <strong>Dhcp6ModeData.Ia</strong> should be 0.</td>
</tr>
</tbody>
</table>


### Start()

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
<td>5.24.3.5.1</td>
<td>0x2153bcbb, 0xd5d3, 0x487e, 0x80, 0x98, 0xea, 0x02, 0x22, 0x79,
0x60, 0x11</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start() - Start()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> with the non configured
instance.</td>
<td>Call <strong>Start()</strong> with the non configured instance, The
return status should be <strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.5.2</td>
<td>0x5b1e8f26, 0x72e7, 0x429a, 0xbc, 0xbd, 0xff, 0xd0, 0x27, 0x91,
0x8a, 0x35</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start() - Start()</strong> returns
<strong>EFI_ALREADY_STARTED</strong> with the configured instance which
has been started.</td>
<td>Call <strong>Start()</strong> with the configured instance which has
been started, The return status should be
<strong>EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.5.3</td>
<td>0xc5eca119, 0x7635, 0x4c13, 0x98, 0x5d, 0xde, 0xed, 0xf6, 0x94,
0x83, 0x37</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start() - Start()</strong> returns
<strong>EFI_NO_RESPONSE</strong> while DHCPv6 S.A.R.R process failed
because of no response.</td>
<td>Call <strong>Start()</strong> while DHCPv6 S.A.R.R process failed
because of no response, The return status should be
<strong>EFI_NO_RESPONSE.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.5.4</td>
<td>0x23731450, 0xf84f, 0x43cc, 0xa6, 0x2a, 0x87, 0x6c, 0x10, 0xb7,
0xb2, 0x08</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start() - Start()</strong> returns
<strong>EFI_ABORTED</strong> when the user returns error status from
callback function.</td>
<td>Call <strong>Configure()</strong>when the user returns error status
from callback function, The return status should be
<strong>EFI_ABORTED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.5.5</td>
<td>0xd5a092e9, 0xed43, 0x4e5e, 0x8d, 0x9f, 0xc9, 0xc4, 0x92, 0x65,
0x27, 0xce</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start()</strong> -
<strong>Start()</strong> returns <strong>EFI_SUCCESS</strong> when the
S.A.R.R process successfully.</td>
<td><p>5.24.3.5.5 to 5.24.3.5.7 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create an event for the Dhcp6CfgData</p>
<p>3. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>4. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>5. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.5.6</td>
<td>0xbb8655d9, 0x8d41, 0x452a, 0x92, 0x6e, 0xc8, 0xe7, 0x92, 0xf8,
0xc4, 0xcc</td>
<td><strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong>.</td>
<td><p>6. Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>7. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.5.7</td>
<td>0xb7d13d3b, 0x6492, 0x4955, 0x9d, 0x51, 0xe0, 0xba, 0x96, 0x69,
0xfd, 0x43</td>
<td><strong>Dhcp6ConfigData.IaInfoEvent</strong> should be
<strong>signaled</strong>.</td>
<td>8. <strong>Dhcp6ConfigData.IaInfoEvent</strong> should be
<strong>signaled</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.5.8</td>
<td>0x6e3cc768, 0x1a9c, 0x466f, 0xa6, 0x0f, 0xac, 0xd4, 0x58, 0x76,
0xdb, 0x7f</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Start()</strong> -
<strong>Start()</strong> returns <strong>EFI_SUCCESS</strong> when the
S.A.R.R process successfully.</td>
<td><p>5.24.3.5.8 to 5.24.3.5.9 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.5.9</td>
<td>0xf68a6461, 0x26cf, 0x4f37, 0xa5, 0xd2, 0x65, 0xb2, 0x65, 0xd1,
0x1a, 0x84</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with both
<strong>IaInfoEvent</strong> and <strong>SolicitRetransmission</strong>
<strong>NULL</strong>.</td>
<td><p>5. Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p></td>
</tr>
</tbody>
</table>


### InfoRequest()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 17%" />
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
<td>5.24.3.6.1</td>
<td>0x5bf750bc, 0x349f, 0x4aa2, 0xa5, 0x9f, 0xfd, 0x09, 0xba, 0xf0,
0xcf, 0xc1</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>NULL</strong> <strong>OptionRequest</strong>.</td>
<td>Call <strong>InfoRequest()</strong> with <strong>NULL</strong>
<strong>OptionRequest</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.6.2</td>
<td>0x3e90fc45, 0x7a27, 0x4c9b, 0x88, 0x8b, 0xfc, 0xa8, 0x56, 0x9f,
0x80, 0xef</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with non zero
<strong>OptionCount</strong> and an <strong>NULL
OptionList</strong>.</td>
<td>Call <strong>InfoRequest()</strong> with non zero
<strong>OptionCount</strong> and an <strong>NULL OptionList</strong>,
The return status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.6.3</td>
<td>0xa85f59d4, 0x3a09, 0x4a74, 0xa8, 0xd6, 0x71, 0xee, 0x08, 0x20,
0x2f, 0x7e</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when
<strong>OptionList</strong> contains client identity option.</td>
<td>Call <strong>InfoRequest()</strong> when <strong>OptionList</strong>
contains client identity option, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.6.4</td>
<td>0x8647418d, 0xb3f9, 0x4bf5, 0xb5, 0x24, 0xf4, 0xc1, 0x7d, 0x36,
0x00, 0x20</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with an <strong>NULL
Retransmission</strong>.</td>
<td>Call <strong>InfoRequest()</strong> with an <strong>NULL
Retransmission</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.6.5</td>
<td>0xf18e8693, 0xd00f, 0x497f, 0x86, 0xfe, 0xf9, 0x3a, 0x2f, 0x50,
0x38, 0x04</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when both
<strong>Retransmission.Mrd</strong> and
<strong>Retransmission.Mrt</strong> are zero.</td>
<td>Call <strong>InfoRequest()</strong> when both
<strong>Retransmission.Mrd</strong> and
<strong>Retransmission.Mrt</strong> are zero, The return status should
be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.6.6</td>
<td>0x1669a032, 0x433a, 0x4dbc, 0x8c, 0x00, 0x81, 0xc4, 0xb6, 0x59,
0x78, 0x1f</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when
<strong>ReplyCallback</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>InfoRequest()</strong> when
<strong>ReplyCallback</strong> is <strong>NULL</strong>, The return
status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.6.7</td>
<td>0xaa884b5b, 0xb369, 0x46cc, 0x85, 0xa9, 0xfe, 0xb0, 0x33, 0xd1,
0xaa, 0x48</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_NO_RESPONSE</strong> when Dhcp6 server doesn’t
response.</td>
<td>Call <strong>InfoRequest()</strong> when Dhcp6 server doesn’t
response, The return status should be
<strong>EFI_NO_RESPONSE.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.6.8</td>
<td>0x3ade8458, 0xd07a, 0x4f45, 0xbc, 0xc3, 0x49, 0x68, 0x20, 0xe9,
0x85, 0x0b</td>
<td><strong>EFI_ DHCP6 PROTOCOL.InfoRequest() - InfoRequest()</strong>
returns <strong>EFI_ABORTED</strong> when the user returns error status
from <strong>ReplyCallback</strong> function.</td>
<td>Call <strong>InfoRequest()</strong>when the user returns error
status from <strong>ReplyCallback</strong> function, The return status
should be <strong>EFI_ABORTED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.6.9</td>
<td>0xc7cb2c53, 0xd008, 0x40b5, 0xb0, 0x53, 0xb2, 0x68, 0x08, 0xb8,
0x81, 0x3a</td>
<td>InfoRequestPacket should be received.</td>
<td><p>5.24.3.6.9 to 5.24.3.6.12 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create a timeout event.</p>
<p>3. Call <strong>InfoRequest()</strong> to obtain configuration
information without ant IA address.</p>
<p>4. InfoRequestPacket should be received.</p></td>
</tr>
<tr class="odd">
<td>5.24.3.6.10</td>
<td>0x730310e5, 0x5df3, 0x41f9, 0xbf, 0x4a, 0x75, 0x1b, 0x01, 0xf9,
0x59, 0xef</td>
<td>The return status of <strong>InfoRequest()</strong> should be
<strong>EFI_SUCCESS</strong></td>
<td><p>5. Send the the Reply packet for the InfoRequest message.</p>
<p>6. The return status of <strong>InfoRequest()</strong> should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.6.11</td>
<td>0x1cb6efc5, 0x1d58, 0x4c8e, 0xb5, 0x7d, 0x83, 0x7d, 0xd2, 0x8c,
0xb0, 0xd3</td>
<td>The CallbackContext should be updated with
<strong>ReplyCallback()</strong></td>
<td>7. The CallbackContext should be updated with
<strong>ReplyCallback()</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.6.12</td>
<td>0x5738bba8, 0xf1ad, 0x4889, 0x87, 0xed, 0x29, 0x21, 0x59, 0x17,
0x61, 0x48</td>
<td>The Timeout event should not be signaled.</td>
<td>8. The Timeout event should not be signaled.</td>
</tr>
<tr class="even">
<td>5.24.3.6.13</td>
<td>0xa0995b80, 0x76ad, 0x4d99, 0xa5, 0xd3, 0x0d, 0x55, 0x1d, 0xb0,
0x94, 0x75</td>
<td>InfoRequestPacket should be received.</td>
<td><p>5.24.3.6.13 to 5.24.3.6.15 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>InfoRequest()</strong> to obtain configuration
information without ant IA address.</p>
<p>3. InfoRequestPacket should be received.</p></td>
</tr>
<tr class="odd">
<td>5.24.3.6.14</td>
<td>0x46a40db0, 0x5b97, 0x4272, 0x98, 0x98, 0x9c, 0xbb, 0xe7, 0xa2,
0x22, 0x5f</td>
<td>The return status of <strong>InfoRequest()</strong> should be
<strong>EFI_SUCCESS</strong></td>
<td><p>4. Send the the Reply packet for the InfoRequest message.</p>
<p>5. The return status of <strong>InfoRequest()</strong> should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.6.15</td>
<td>0x4b1612fa, 0x7561, 0x4b55, 0xb9, 0xa2, 0x76, 0x40, 0x02, 0xc6,
0x95, 0xe1</td>
<td>The CallbackContext should be updated with
<strong>ReplyCallback()</strong></td>
<td>6. The CallbackContext should be updated with
<strong>ReplyCallback()</strong></td>
</tr>
</tbody>
</table>


### RenewRebind()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 17%" />
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
<td>5.24.3.7.1</td>
<td>0x613614f9, 0x2c96, 0x45ee, 0xad, 0xb8, 0xf0, 0x88, 0x72, 0xfd,
0x86, 0xf9</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> when the instance has not
been configured.</td>
<td>Call <strong>RenewRebind()</strong> when the instance has not been
configured, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.7.2</td>
<td>0x28ce0a5d, 0x6f3d, 0x47ad, 0xb1, 0x95, 0xc2, 0x5f, 0xce, 0xd8,
0x98, 0xb5</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state.</td>
<td>Call <strong>RenewRebind()</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.7.3</td>
<td>0x5c85dc0c, 0x634a, 0x4db3, 0x95, 0x81, 0x72, 0x0d, 0x1b, 0xda,
0x6c, 0x84</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_ALREADY_STARTED</strong> with <strong>RebindRequest
TRUE</strong> when the instance in <strong>Dhcp6Rebinding</strong>
state.</td>
<td>Call <strong>RenewRebind()</strong> with <strong>RebindRequest
TRUE</strong> when the instance in <strong>Dhcp6Rebinding</strong>
state, The return status should be
<strong>EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.7.4</td>
<td>0x94bc77a0, 0xb016, 0x4d71, 0x8f, 0x5b, 0xd0, 0x49, 0x1a, 0x2c,
0x4f, 0x0c</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_ALREADY_STARTED</strong> with <strong>RebindRequest
FALSE</strong> when the instance in <strong>Dhcp6Rebinding</strong>
state.</td>
<td>Call <strong>RenewRebind()</strong> with <strong>RebindRequest
FALSE</strong> when the instance in <strong>Dhcp6Rebinding</strong>
state, The return status should be
<strong>EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.7.5</td>
<td>0xcc0b1c38, 0x2b99, 0x4ef4, 0xb9, 0x35, 0x63, 0x2e, 0x12, 0x46,
0x4f, 0xf7</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_ABORTED</strong> when the user returns error status
from callback function.</td>
<td>Call <strong>RenewRebind()</strong> when the user returns error
status from callback function, The return status should be
<strong>EFI_ABORTED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.7.6</td>
<td>0x2957725b, 0x7693, 0x40ac, 0xae, 0x81, 0x59, 0x54, 0x88, 0x25,
0xf7, 0x48</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_SUCCESS</strong> when the exchange process is
executed successfully.</td>
<td><p>5.24.3.7.6 to 5.24.3.7.8 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>RenewRebind()</strong> and execute exchange process,
including RENEW-REPLY, the return status should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.7.7</td>
<td>0xf495e992, 0xe807, 0x4a38, 0xbf, 0x42, 0x57, 0x1d, 0xd1, 0xfe,
0x8f, 0xc7</td>
<td>CallbackContext should updated.</td>
<td>8. CallbackContext should be updated.</td>
</tr>
<tr class="odd">
<td>5.24.3.7.8</td>
<td>0x23d22d31, 0x1852, 0x4527, 0x80, 0x73, 0xcf, 0x8a, 0x51, 0x16,
0xff, 0x92</td>
<td>The state is still <strong>Dhcp6Bound</strong>.</td>
<td>9. The state is still <strong>Dhcp6Bound</strong></td>
</tr>
<tr class="even">
<td>5.24.3.7.9</td>
<td>0x6ae394d7, 0xa5dc, 0x4147, 0x93, 0x5e, 0xf5, 0x07, 0xb2, 0xb8,
0xea, 0x35</td>
<td><strong>EFI_ DHCP6 PROTOCOL.RenewRebind() - RenewRebind()</strong>
returns <strong>EFI_SUCCESS</strong> when the exchange process is
executed successfully.</td>
<td><p>5.24.3.7.9 to 5.24.3.7.10 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>RenewRebind()</strong> and execute exchange process,
including RENEW-REBIND-REPLY, the return status should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.7.10</td>
<td>0x9f653dd2, 0x3edd, 0x47d6, 0xa6, 0x2e, 0x6c, 0x79, 0x99, 0x3d,
0xd9, 0x58</td>
<td>The state is still <strong>Dhcp6Bound</strong>.</td>
<td>8. The state is still <strong>Dhcp6Bound</strong>.</td>
</tr>
</tbody>
</table>


### Decline()

<table>
<colgroup>
<col style="width: 14%" />
<col style="width: 17%" />
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
<td>5.24.3.8.1</td>
<td>0x30c90eee, 0x69f1, 0x4a41, 0x88, 0x4d, 0x27, 0x6e, 0x9f, 0x6c,
0x0e, 0x33</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the instance has not been
configured.</td>
<td>Call <strong>Decline()</strong> when the instance has not been
configured, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.8.2</td>
<td>0x2f3cd8a1, 0x8987, 0x434d, 0xa1, 0xbb, 0xfc, 0xb6, 0x83, 0x04,
0xf6, 0x0d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state.</td>
<td>Call <strong>Decline()</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.8.3</td>
<td>0x6224a781, 0xfa3a, 0x4190, 0xa4, 0xfa, 0x5b, 0xec, 0x33, 0xbf,
0x3f, 0xfc</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when the
<strong>AddressCount</strong> is zero.</td>
<td>Call <strong>Decline()</strong> when the
<strong>AddressCount</strong> is zero, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.8.4</td>
<td>0x1c8166c0, 0xbc5e, 0x4d1f, 0xa3, 0x8b, 0x65, 0x34, 0x7e, 0x76,
0x10, 0x69</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when the
<strong>Addresses</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>Decline()</strong> when the <strong>Addresses</strong>
is <strong>NULL</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.8.5</td>
<td>0xc14f0d80, 0xe7e5, 0x4742, 0x9c, 0xc5, 0x27, 0xd0, 0x37, 0x79,
0x1b, 0x0d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_NOT_FOUND</strong> when any specified address in
<strong>Addresses</strong> is not correlated with the configured
IA.</td>
<td>Call <strong>Decline()</strong> when any specified address in
<strong>Addresses</strong> is not correlated with the configured IA, The
return status should be <strong>EFI_NOT_FOUND.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.8.6</td>
<td>0x44b4fcda, 0xf970, 0x4f3e, 0x88, 0xbb, 0x52, 0xf2, 0x52, 0xe9,
0x81, 0xdf</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_ABORTED</strong> when the user returns error status from
callback function.</td>
<td>Call <strong>Decline()</strong> when the user returns error status
from callback function, The return status should be
<strong>EFI_ABORTED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.8.7</td>
<td>0x86606604, 0x5e2b, 0x4268, 0x91, 0xcd, 0x99, 0xc6, 0xb5, 0x7a,
0x42, 0xd8</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_SUCCESS</strong> with execute exchange process, including
DECLINE- REPLY.</td>
<td><p>5.24.3.8.7 to 5.24.3.8.8 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Decline()</strong> and execute exchange process,
including DECLINE- REPLY, the return status should be
<strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.8.8</td>
<td>0x1119b246, 0x8627, 0x45a1, 0x87, 0x89, 0x5b, 0xba, 0x7b, 0x4c,
0x0b, 0x48</td>
<td>The state is still <strong>Dhcp6Bound</strong>.</td>
<td>8. The state is still <strong>Dhcp6Bound</strong></td>
</tr>
<tr class="even">
<td>5.24.3.8.9</td>
<td>0x554529cc, 0x30e2, 0x4269, 0x88, 0xb7, 0x72, 0x8e, 0x31, 0x1d,
0xbd, 0x1b</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_SUCCESS</strong> to decline all IP6 addresses of the
configured IA and execute exchange process, including DECLINE-
REPLY.</td>
<td><p>5.24.3.8.9 to 5.24.3.8.10 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Decline()</strong> to decline all IP6 addresses of
the configured IA and execute exchange process, including DECLINE-
REPLY, the return status should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.8.10</td>
<td>0xf7449f19, 0x53e0, 0x4130, 0xba, 0x62, 0xea, 0x2b, 0x1f, 0x74,
0x8c, 0xa0</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>8. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
<tr class="even">
<td>5.24.3.8.11</td>
<td>0xcdbd802e, 0x7647, 0x41bc, 0x9b, 0xe6, 0xe4, 0x11, 0x9f, 0x6c,
0x79, 0x2d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_SUCCESS</strong> to decline all IP6 addresses of the
configured IA and execute exchange process, including DECLINE-
REPLY.</td>
<td><p>5.24.3.8.11 to 5.24.3.8.13 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create <strong>IaInfoEvent</strong></p>
<p>3. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>4. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>5. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>6. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>7. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>8. Call <strong>Decline()</strong> to decline all IP6 addresses of
the configured IA and execute exchange process, including DECLINE-
REPLY, the return status should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.8.12</td>
<td>0xfce31eb4, 0xeb16, 0x4b22, 0xb3, 0x55, 0xa8, 0xb0, 0x82, 0x0f,
0x0d, 0x3d</td>
<td>After the Decline exchange process returns,the
<strong>IaInfoEvent</strong> will be signaled.</td>
<td>9. After the Decline exchange process returns,the
<strong>IaInfoEvent</strong> will be signaled.</td>
</tr>
<tr class="even">
<td>5.24.3.8.13</td>
<td>0x313da4fc, 0xf2ce, 0x4ecc, 0xa9, 0x97, 0x03, 0xea, 0x77, 0xfb,
0xdb, 0x59</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>10. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.8.14</td>
<td>0x60c90ab2, 0x4372, 0x4b75, 0x84, 0x56, 0xe6, 0xe1, 0xfa, 0x34,
0x71, 0xad</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_NO_RESPONSE</strong> to decline all IP6 addresses of the
configured IA without the response from server.</td>
<td><p>5.24.3.8.14 to 5.24.3.8.15 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Decline()</strong> to decline all IP6 addresses of
the configured IA without the response from server, the return status
should be <strong>EFI_NO_RESPONSE</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.8.15</td>
<td>0x6af27ff2, 0xecb2, 0x4e96, 0xaf, 0xf7, 0xa7, 0x6b, 0x18, 0xe6,
0x38, 0xfa</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>8. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
</tbody>
</table>


### Release()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 17%" />
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
<td>5.24.3.9.1</td>
<td>0xfd3f1c62, 0x37d9, 0x4f34, 0x85, 0xe5, 0x93, 0x85, 0x28, 0x2f,
0xd3, 0xc4</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the instance has not been
configured.</td>
<td>Call <strong>Release()</strong> when the instance has not been
configured, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.9.2</td>
<td>0x38bc0e62, 0x4d8f, 0x4706, 0xb1, 0x39, 0xe0, 0xa7, 0x1c, 0xbd,
0x6d, 0x56</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state.</td>
<td>Call <strong>Release()</strong> when the instance is not in
<strong>Dhcp6Bound</strong> state, The return status should be
<strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.9.3</td>
<td>0x8e214193, 0x3dfb, 0x48e3, 0xb6, 0xe3, 0xdb, 0x4b, 0xde, 0xa4,
0xbc, 0xef</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when the
<strong>AddressCount</strong> is not zero and <strong>Addresses</strong>
is <strong>NULL</strong>.</td>
<td>Call <strong>Release()</strong> when the
<strong>AddressCount</strong> is not zero and <strong>Addresses</strong>
is <strong>NULL</strong>, The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.9.4</td>
<td>0x4b411cb3, 0x2427, 0x4315, 0xa3, 0x74, 0xa9, 0xdd, 0x29, 0xf7,
0x9a, 0xed</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_NOT_FOUND</strong> when any specified address in
<strong>Addresses</strong> is not correlated with the configured
IA.</td>
<td>Call <strong>Release()</strong> when any specified address in
<strong>Addresses</strong> is not correlated with the configured IA, The
return status should be <strong>EFI_NOT_FOUND.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.9.5</td>
<td>0xa4b55b0e, 0x1037, 0x4717, 0x83, 0x53, 0x29, 0x24, 0xd3, 0x18,
0x23, 0x5d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_ABORTED</strong> when the user returns error status from
callback function.</td>
<td>Call <strong>Release()</strong> when the user returns error status
from callback function, The return status should be
<strong>EFI_ABORTED.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.9.6</td>
<td>0x1459bb4e, 0xa926, 0x42cc, 0x99, 0x7d, 0xf8, 0x87, 0xf7, 0xd0,
0xbb, 0x71</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_SUCCESS</strong> to release one of the IPv6 address that has
already been assigned to the configured IA.</td>
<td><p>5.24.3.9.6 to 5.24.3.9.7 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Release()</strong> to release one of the IPv6 address
that has already been assigned to the configured IA, the return status
should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.9.7</td>
<td>0x7251daef, 0x57ae, 0x4fc6, 0x81, 0xf4, 0x10, 0xe2, 0x34, 0xa5,
0x87, 0xa4</td>
<td>The state is still <strong>Dhcp6Bound</strong>.</td>
<td>8. The state is still <strong>Dhcp6Bound</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.9.8</td>
<td>0x692e0cfb, 0x587d, 0x4906, 0x91, 0xa1, 0xcb, 0x20, 0x3b, 0x1e,
0xba, 0x2d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Decline() - Decline()</strong> returns
<strong>EFI_SUCCESS</strong> to release all IP6 addresses of the
configured IA and execute exchange process, including RELEASE-
REPLY.</td>
<td><p>5.24.3.9.8 to 5.24.3.9.9 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Release()</strong> to release all IP6 addresses of
the configured IA and execute exchange process, including RELEASE-
REPLY, the return status should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.9.9</td>
<td>0x309de757, 0x2ab4, 0x4d5b, 0xb3, 0x7c, 0xb7, 0xdc, 0x46, 0x40,
0x4d, 0x1c</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>8. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
<tr class="odd">
<td>5.24.3.9.10</td>
<td>0x7b131129, 0x2fdb, 0x4a67, 0x8f, 0xaa, 0xe9, 0x0c, 0x1d, 0x08,
0xab, 0x94</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_SUCCESS</strong> to release all IP6 addresses of the
configured IA and execute exchange process, including RELEASE-
REPLY.</td>
<td><p>5.24.3.9.10 to 5.24.3.9.12 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create <strong>IaInfoEvent</strong></p>
<p>3. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>4. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>5. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>6. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>7. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>8. Call <strong>Release()</strong> to release all IP6 addresses of
the configured IA and execute exchange process, including RELEASE-
REPLY, the return status should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="even">
<td>5.24.3.9.11</td>
<td>0x47d072fd, 0x5782, 0x413b, 0xb4, 0x62, 0xb3, 0x18, 0x58, 0x04,
0xad, 0x4e</td>
<td>After the Release exchange process returns,the
<strong>IaInfoEvent</strong> will be signaled.</td>
<td>9. After the Release exchange process returns, the
<strong>IaInfoEvent</strong> will be signaled.</td>
</tr>
<tr class="odd">
<td>5.24.3.9.12</td>
<td>0x22dc90e4, 0xd93c, 0x465d, 0x90, 0x27, 0x35, 0xe9, 0xab, 0x3f,
0x3a, 0x3a</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>10. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
<tr class="even">
<td>5.24.3.9.13</td>
<td>0x52b03918, 0x1e8c, 0x4620, 0xa1, 0x44, 0x02, 0x09, 0xae, 0xf3,
0xc7, 0x9d</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_NO_RESPONSE</strong> to release all IP6 addresses of the
configured IA without the response from server.</td>
<td><p>5.24.3.9.14 to 5.24.3.9.15 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>3. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>4. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>5. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>6. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>7. Call <strong>Release()</strong> to release all IP6 addresses of
the configured IA without the response from server, the return status
should be <strong>EFI_NO_RESPONSE</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.9.14</td>
<td>0xc65a96c1, 0x448c, 0x4d75, 0x81, 0x90, 0x19, 0x13, 0x76, 0x1e,
0x79, 0x3d</td>
<td>The state is still <strong>Dhcp6Init</strong>.</td>
<td>8. The state is still <strong>Dhcp6Init</strong>.</td>
</tr>
</tbody>
</table>


### Stop()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 17%" />
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
<td>5.24.3.10.1</td>
<td>0x592d9e8d, 0x82cd, 0x44d8, 0xbf, 0x26, 0x0b, 0x40, 0x81, 0x25,
0x65, 0x17</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Stop() - Stop()</strong> returns
<strong>EFI_SUCCESS</strong> when the instance has not been
configured.</td>
<td>Call <strong>Stop()</strong> when the instance has not been
configured, The return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="odd">
<td>5.24.3.10.2</td>
<td>0x69ac94c1, 0xb57f, 0x4251, 0xb9, 0x56, 0x20, 0xaa, 0x9f, 0x30,
0x0d, 0xc1</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Stop() - Stop()</strong> returns
<strong>EFI_SUCCESS</strong> when the instance has been configured.</td>
<td>Call <strong>Stop()</strong> when the instance has been configured,
The return status should be <strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.24.3.10.3</td>
<td>0x51255767, 0x7218, 0x400d, 0xa2, 0xd7, 0x3f, 0x3e, 0x50, 0x8c,
0x90, 0x64</td>
<td><strong>EFI_ DHCP6 PROTOCOL.Release() - Release()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when the
<strong>AddressCount</strong> is not zero and <strong>Addresses</strong>
is <strong>NULL</strong>.</td>
<td><p>5.24.3.9.3 to 5.24.3.9.5 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an DHCP6
instance.</p>
<p>2. Create <strong>IaInfoEvent</strong></p>
<p>3. Call <strong>Configure()</strong> to initialize the DHCP6
instance.</p>
<p>4. Call <strong>Start()</strong> to start S.A.R.R process.</p>
<p>5. Get the return status of <strong>Start()</strong>, it should be
<strong>EFI_SUCCESS</strong></p>
<p>6. The CallbackContext is updated</p>
<p>Call <strong>GetModeData()</strong> to get the
<strong>GetModeData</strong></p>
<p>7. <strong>GetModeData.Ia.State</strong> should be
<strong>Dhcp6Bound</strong></p>
<p>8. <strong>IaInfoEvent</strong> should be signaled.</p>
<p>9. Call <strong>Stop()</strong> to stop all IP6 addresses of the
configured IA and execute exchange process, including RELEASE- REPLY,
the return status should be <strong>EFI_SUCCESS</strong></p></td>
</tr>
<tr class="odd">
<td>5.24.3.10.4</td>
<td>0xd00b1578, 0x5f23, 0x4ab7, 0x99, 0x40, 0x98, 0x51, 0x8a, 0x30,
0x8c, 0x08</td>
<td><strong>IaInfoEvent</strong> should be signaled.</td>
<td><strong>IaInfoEvent</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.24.3.10.5</td>
<td>0xcfa8dc36, 0xc246, 0x45d7, 0x94, 0xf1, 0xc9, 0x18, 0x54, 0xd6,
0x38, 0xad</td>
<td>The state of IA should be <strong>Dhcp6Init</strong>.</td>
<td>The state of IA should be <strong>Dhcp6Init</strong></td>
</tr>
</tbody>
</table>


### Parse()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.24.3.11.1 | 0x15a7d1de, 0x4bf6, 0x4507, 0xa3, 0xe2, 0xa1, 0xa4, 0x2e, 0xdd, 0x43, 0x23 | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_INVALID_PARAMETER** when the **Packet** is **NULL**. | Call **Parse()** when the **Packet** is **NULL**, The return status should be **EFI_INVALID_PARAMETER.** |
| 5.24.3.11.2 | 0x28a7d965, 0x82bf, 0x49c6, 0xb1, 0xd8, 0x56, 0x08, 0x37, 0x0b, 0xdd, 0x62 | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_INVALID_PARAMETER** when the **Packet** is not well-formed(length is too small). | Call **Parse()** when the **Packet** is not well-formed(length is too small), The return status should be **EFI_INVALID_PARAMETER.** |
| 5.24.3.11.3 | 0x2228cc36, 0xa56b, 0x4aa8, 0xa2, 0x15, 0x06, 0x01, 0xce, 0xfe, 0x00, 0x94 | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_INVALID_PARAMETER** when the **OptionCount** is not zero and **PacketOptionList** is **NULL**. | Call **Parse()** when the **OptionCount** is not zero and **PacketOptionList** is **NULL**, The return status should be **EFI_INVALID_PARAMETER.** |
| 5.24.3.11.4 | 0x444b0ef0, 0x0297, 0x4805, 0x8b, 0x2a, 0xc4, 0xa2, 0xf8, 0x82, 0xac, 0x2c | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_INVALID_PARAMETER** when the **OptionCount** is **NULL**. | Call **Parse()** when the **OptionCount** is **NULL**, The return status should be **EFI_INVALID_PARAMETER.** |
| 5.24.3.11.5 | 0x49182e78, 0x34dc, 0x4450, 0xb6, 0x2c, 0xfe, 0x28, 0x33, 0x51, 0xc1, 0x96 | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_BUFFER_TOO_SMALL** when the **OptionCount** is **NULL**. | Call **Parse()** when **OptionCount** is smaller than the number of **option** that were found in the **Packet**, The return status should be **EFI_BUFFER_TOO_SMALL.** |
| 5.24.3.11.6 | 0x43dcf866, 0x9f05, 0x47d5, 0x92, 0xa1, 0x1e, 0x6f, 0x26, 0xf4, 0x1f, 0x61 | **OptionCount** should be update to the right number of **option** that is found in the **packet.** | **OptionCount** should be update to the right number of **option** that is found in the **packet.** |
| 5.24.3.11.7 | 0xacfb1bb7, 0x7b28, 0x4c35, 0xbd, 0x9f, 0x7e, 0x89, 0xa1, 0x9e, 0x54, 0xe2 | **EFI\_ DHCP6 PROTOCOL.Parse() - Parse()** returns **EFI_SUCCESS** with the valid parameters. | Call **Parse()** with the valid parameters, The return status should be **EFI_SUCCESS.** |
| 5.24.3.11.8 | 0xbb477381, 0x7731, 0x4259, 0x87, 0x01, 0xca, 0x1f, 0x71, 0xd6, 0xf9, 0x7e | The **OpCode** should be retrieved correctly. | The **OpCode** should be retrieved correctly. |

