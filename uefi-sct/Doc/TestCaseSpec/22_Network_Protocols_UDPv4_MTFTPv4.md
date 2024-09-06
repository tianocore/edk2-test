# Network Protocols UDP and MTFTP

## EFI_UDP4_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_UDP4_PROTOCOL Section.

### GetModeData()

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
<td>5.26.1.1.1</td>
<td>0xfc4d1b7b, 0x4abd, 0x47d3, 0xbd, 0x64, 0xe0, 0x98, 0x86, 0x29,
0x73, 0xec</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData() –</strong> invokes
<strong>GetModeData()</strong> to get all mode data before
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> to get all
mode data. The return status should be
<strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.1.2</td>
<td><p>0x15c32ffb, 0x2cdf, 0x4b5b,</p>
<p>0xab, 0x3e, 0x5a, 0xed, 0x7f, 0xc5, 0x25, 0xe7</p></td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get <strong>EFI_UDP4_PROTOCOL</strong>
mode data before configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_UDP4_PROTOCOL</strong> mode data. The return status should
be <strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.1.3</td>
<td>0xcdcd0bb9, 0x455a, 0x4525, 0xb8, 0xf2, 0x0e, 0xe0, 0x4b, 0xaa,
0x80, 0x14</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get <strong>EFI_IP4_PROTOCOL</strong>
mode data before configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_IP4_PROTOCOL</strong> mode data. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.1.4</td>
<td>0xcc19f3f7, 0x80b9, 0x46e8, 0xb2, 0xaa, 0xb6, 0xdd, 0x81, 0x66,
0xd8, 0x93</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong> mode data before
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong> mode data. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.1.5</td>
<td>0xd291d441, 0x2d3b, 0x4575, 0xa3, 0xf3, 0x05, 0xe1, 0x5a, 0x34,
0x62, 0xc0</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get
<strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong> mode data before
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong> mode data. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.1.6</td>
<td>0xf28448b0, 0xd525, 0x40f7, 0x92, 0xf1, 0xed, 0x6d, 0xaa, 0x59,
0xe4, 0xb4</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData() –</strong> invokes
<strong>GetModeData()</strong> to get all mode data after
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new instance.</p>
<p>3 Call <strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> to get all
mode data. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.1.7</td>
<td>0x182f712c, 0x1b2a, 0x4850, 0xbd, 0x78, 0xa6, 0xe6, 0xb6, 0xf6,
0x73, 0x54</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get <strong>EFI_UDP4_PROTOCOL</strong>
mode data after configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new instance.</p>
<p>3 Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_UDP4_PROTOCOL</strong> mode data. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.1.8</td>
<td>0x8aa1ebeb, 0xb735, 0x421e, 0x92, 0x1d, 0xf8, 0x76, 0xd2, 0xae,
0xdf, 0x1c</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get <strong>EFI_IP4_PROTOCOL</strong>
mode data after configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new instance.</p>
<p>3 Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_IP4_PROTOCOL</strong> mode data. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.1.9</td>
<td>0xba1c7d49, 0x4490, 0x42e1, 0xa8, 0x92, 0xc3, 0x61, 0xef, 0x5d,
0x94, 0x79</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong> mode data after
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new instance.</p>
<p>3 Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_MANAGED_NETWORK_PROTOCOL</strong> mode data. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.1.10</td>
<td>0x5df96df3, 0x6404, 0x4486, 0xb6, 0xb7, 0x00, 0xb9, 0x2d, 0x81,
0x21, 0x26</td>
<td><strong>EFI_UDP4_PROTOCOL.GetModeData()</strong> – invokes
<strong>GetModeData()</strong> to get
<strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong> mode data after
configuration.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new instance.</p>
<p>3 Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>GetModeData()</strong> to get
<strong>EFI_SIMPLE_NETWORK_PROTOCOL</strong> mode data. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Configure()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.26.1.2.1</td>
<td>0x13a8fd73, 0x6b66, 0x4418, 0x85, 0x4c, 0xda, 0x63, 0xff, 0x42,
0x75, 0x4f</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with a <em>StationAddress</em>
value of a multicast address.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with a
<em>StationAddress</em> value of a multicast address. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.2</td>
<td>0xd8b6f8bd, 0x1ba8, 0x48c1, 0x90, 0x30, 0x5a, 0x37, 0x18, 0x0c,
0x06, 0x01</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with an invalid <em>SubnetMask</em>
value.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with an invalid
<em>SubnetMask</em> value. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.3</td>
<td>0xb4a98a30, 0x35e9, 0x4460, 0x81, 0x5d, 0x42, 0x33, 0x7c, 0x17,
0x6c, 0x44</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>AcceptPromiscuous</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>AcceptPromiscuous</em>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.23</td>
<td>0x349fc21a, 0x37db, 0x406e, 0xbd, 0xc8, 0xf6, 0x12, 0x2c, 0xa9,
0xe9, 0xfc</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>RemoteAddress</em> being a multicast address.The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL</strong>.<strong>CreateChild</strong>()
to create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong>with the
parameter <em>RemoteAddress</em> being a multicast address.The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.4</td>
<td>0xa36f507b, 0x7526, 0x441e, 0xaf, 0x48, 0x4a, 0xc4, 0xf4, 0x31,
0xe6, 0xbd</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>AcceptBroadcast</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>AcceptBroadcast</em>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.5</td>
<td>0xac4cf23e, 0x0c5e, 0x4299, 0xb4, 0x29, 0xc8, 0x83, 0xe7, 0xe6,
0x73, 0xb8</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>AcceptAnyPort</em> before the instance has been stopped or
reset.</td>
<td><p><strong>1. Call
EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to create a new
<strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>AcceptAnyPort</em>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.6</td>
<td>0xc08bfbab, 0x0cde, 0x4332, 0x86, 0x86, 0x42, 0x52, 0xdc, 0x50,
0x48, 0xcc</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>AllowDuplicatePort</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>AllowDuplicatePort</em>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.7</td>
<td>0x66544950, 0x16ff, 0x4854, 0x9c, 0x09, 0x45, 0x84, 0x29, 0x2d,
0x7c, 0x51</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>UseDefaultAddress</em> before the instance has been stopped or
reset.</td>
<td><p><strong>1. Call
EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to create a new
<strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>UseDefaultAddress</em>. The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.24</td>
<td>0xee87c393, 0xf728, 0x46b9, 0xb1, 0x31, 0x58, 0xc3, 0xdd, 0x5e,
0x18, 0x34</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> when
<em>UdpConfigData.AllowDuplicatePort is</em> <strong>FALSE</strong> and
<em>UdpConfigData.StationPort</em> is already used by other
instance.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong>when
<em>UdpConfigData.AllowDuplicatePort</em> is <strong>FALSE</strong> and
<strong>UdpConfigData.StationPort</strong> is already used by other
instance. The return status should be
<strong>EFI_ACCESS_DENIED.</strong></p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.8</td>
<td>0xbe8ab604, 0x1c84, 0x4a80, 0xb6, 0x9a, 0x43, 0xfd, 0xf8, 0x94,
0x5e, 0xf2</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to test the function of
transmitting a packet.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> to transmit a
packet and verify if it is successful.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.9</td>
<td>0xddbba5ba, 0x678b, 0x426e, 0x87, 0xa8, 0x8c, 0x1b, 0xde, 0x5b,
0x36, 0x96</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to test that function of receiving
a packet.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to receive a
packet and verify if it is successful.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.10</td>
<td>0xefe91110, 0x4e6e, 0x4e07, 0xa7, 0xec, 0x09, 0x74, 0xb7, 0xe3,
0x03, 0x87</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>TypeOfService</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>TypeOfService</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.11</td>
<td>0xc6f4f65f, 0x9a98, 0x4d6e, 0xaf, 0xae, 0xe9, 0x87, 0xf9, 0xb4,
0xb4, 0x9c</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>TimeToLive</em> before the instance has been stopped or reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>TimeToLive</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.12</td>
<td>0xe6313038, 0x43f2, 0x4cbe, 0xb8, 0x61, 0xa4, 0x1b, 0x6e, 0x3d,
0x58, 0x91</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>DoNotFragment</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>DoNotFragment</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.13</td>
<td>0x2c81abe0, 0xcf2a, 0x42d0, 0xb4, 0xe3, 0x59, 0x9e, 0x9e, 0x2f,
0x60, 0x6a</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>ReceiveTimeout</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>ReceiveTimeout</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.14</td>
<td>0x798d02e5, 0x0810, 0x462c, 0x8f, 0xba, 0xe9, 0x32, 0xfb, 0x9d,
0x84, 0x85</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to reconfigure the
<em>TransmitTimeout</em> before the instance has been stopped or
reset.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to reconfigure
the <em>TransmitTimeout</em>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.15</td>
<td>0xbe426d4c, 0x8242, 0x4a4e, 0x8d, 0x7d, 0x58, 0xe0, 0x93, 0x92,
0x77, 0x7c</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptBroadcast</em> set to <strong>FALSE</strong>. Check that it
can not receive broadcast packet.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptBroadcast</em> set to <strong>FALSE</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check it can
not receive broadcast packet.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.16</td>
<td>0xb50d8d35, 0xc0c9, 0x4955, 0x94, 0x13, 0xf7, 0x0a, 0x39, 0x2d,
0xa3, 0x0f</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptBroadcast</em> set to <strong>TRUE</strong>. Check that it can
receive broadcast packet successfully.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptBroadcast</em> set to <strong>TRUE</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check that
it can receive broadcast packet successfully.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.17</td>
<td>0x4881a297, 0x3afc, 0x4324, 0xa5, 0x8f, 0xcb, 0x02, 0x64, 0xe5,
0xbd, 0x5e</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptPromiscuous</em> set to <strong>FALSE</strong>. Check that it
can not receive packet to other unicast MACs than its own.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptPromiscuous</em> set to <strong>FALSE</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check that
it can not receive packet to other unicast MACs than its own.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.18</td>
<td>0x066131ca, 0xa6e4, 0x478b, 0x9a, 0xca, 0x05, 0x93, 0xfc, 0xc7,
0xfd, 0x4b</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptPromiscuous</em> set to <strong>TRUE</strong>. Check that it
can receive packet to other unicast MACs than its own.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptPromiscuous</em> set to <strong>TRUE</strong>. The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check that
it can receive packet to other unicast MACs than its own.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.19</td>
<td>0x2867badf, 0x1696, 0x40a1, 0xb8, 0x40, 0x00, 0x4c, 0x79, 0xed,
0xc7, 0xf3</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptAnyPort</em> set to <strong>FALSE</strong>. Check that it can
not receive packet to other port.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptAnyPort</em> set to <strong>TRUE</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check that
it can not receive packet to other port.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.20</td>
<td>0x17d43b3d, 0x9187, 0x4515, 0x83, 0x94, 0x13, 0xdf, 0xf9, 0x35,
0xf4, 0x9e</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> with the parameter
<em>AcceptAnyPort</em> set to <strong>TRUE</strong>. Check that it can
receive packet to other port.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>AcceptAnyPort</em> set to <strong>TRUE</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> and check that
it can receive packet to other port.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.2.21</td>
<td>0x08c86675, 0x7018, 0x418d, 0xb4, 0x3d, 0x36, 0xdc, 0xc5, 0x8b,
0xdc, 0x88</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to check if the parameter
<em>TypeOfService</em> can effect the sending out of the packet.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>TypeOfService</em> set to <strong>1</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> and check that
it can transmit the packet successfully.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.2.22</td>
<td>0x4fb07a34, 0xc2ab, 0x40c1, 0x8a, 0x26, 0x42, 0x6d, 0x54, 0x32,
0x3a, 0xa4</td>
<td><strong>EFI_UDP4_PROTOCOL.</strong> <strong>Configure() –</strong>
invokes <strong>Configure()</strong> to check if the parameter
<em>TimeToLive</em> can effect the sending out of the packet .</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Configure()</strong> to configure
the new <strong>EFI_UDP4_PROTOCOL</strong> instance with the parameter
<em>TimeToLive</em> set to <strong>111</strong>. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> and check that
it can transmit the packet successfully.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Groups()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.1.3.1</td>
<td>0x90ff05c9, 0xea78, 0x4359, 0x95, 0xc0, 0x4d, 0x09, 0x7b, 0xa2,
0xcf, 0x14</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> with a <em>JoinFlag</em> value of
<strong>TRUE</strong> and a <em>MulticastAddress</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> with a
<em>JoinFlag</em> value of <strong>TRUE</strong> and a
<em>MulticastAddress</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.3.2</td>
<td>0x4e1cabfe, 0x2dda, 0x4e0c, 0xbd, 0xbc, 0x5f, 0xfc, 0x77, 0x42,
0xf8, 0x0f</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> with a <em>JoinFlag</em> value of
<strong>TRUE</strong> and a <em>*MulticastAddress</em> value of an
invalid multicast address.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> with a
<em>JoinFlag</em> value of <strong>TRUE</strong> and a
<em>*MulticastAddress</em> value of an invalid multicast address. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.3.3</td>
<td>0xf1018cf8, 0xd8ba, 0x4fa1, 0x82, 0xec, 0x64, 0x52, 0x06, 0x9a,
0x4a, 0xa7</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> when the group address is not in the group
table ,while <em>JoinFlag</em> is <strong>FALSE</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join a group
address into the group table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to leave an group
address which is not in the group table The return status should be
<strong>EFI_NOT_FOUND</strong>.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.3.8</td>
<td>0x86b5bd38, 0x04ae, 0x4a44, 0xbe, 0x0d, 0x1d, 0x7f, 0x32, 0x0f,
0x46, 0xf8</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> when the EFI UDPv4 protocol instance has not
been started.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong>when the EFI UDPv4
protocol instance has not been started.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.3.9</td>
<td>0xde218295, 0x6dec, 0x4c7f, 0x8c, 0x02, 0xc9, 0x46, 0xea, 0x64,
0x59, 0xd6</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> when the group address is already in the group
table when <em>JoinFlag</em> is <strong>FALSE.</strong></td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join a group
address into the group table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> when the group
address is already in the group table when <em>JoinFlag</em> is
<strong>FALSE.</strong>The return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.3.4</td>
<td>0x101a001f, 0x547e, 0x4e1b, 0xae, 0xf6, 0x7d, 0x35, 0x27, 0xb1,
0x23, 0x6f</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> to join a group address and call
<strong>Receive()</strong> to check that it can receive UDP packets to
the group IP.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join a group
address into the group table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to receive the
packets and check that it is successful.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.3.5</td>
<td>0x22561bd0, 0x47ba, 0x4240, 0x96, 0x3a, 0x2a, 0xaf, 0x83, 0x5b,
0xda, 0x72</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> to join two multicast group address and call
<strong>Receive()</strong> to check if it can receive UDP packets to
either of the groups.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join two group
address into the group table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to check it can
receive UDP packets to either of the groups.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.3.6</td>
<td>0x7fcefed3, 0x6e40, 0x4ed8, 0xa4, 0x41, 0x83, 0x7f, 0x5e, 0x13,
0x06, 0x62</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups()</strong> – invokes
<strong>Groups()</strong> to leave a specified group.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join a
specified group address into the group table. The return status should
be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to leave the
group joined in step 3. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.3.7</td>
<td>0x06e97222, 0x1858, 0x469a, 0xa8, 0x19, 0x25, 0xd7, 0x1a, 0x15,
0xc3, 0x68</td>
<td><strong>EFI_UDP4_PROTOCOL.Groups() –</strong> invokes
<strong>Groups()</strong> to leave all multicast groups with a
<em>MulticastAddress</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to join two group
address into the group table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Groups()</strong> to leave all
multicast groups with a <em>MulticastAddress</em> value of
<strong>NULL</strong>. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Routes()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.26.1.4.1</td>
<td>0xedcd02f7, 0x3b78, 0x4186, 0x9d, 0x14, 0x52, 0x92, 0x6b, 0x85,
0x73, 0x08</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> with a <em>SubnetAddress</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> with a
<em>SubnetAddress</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.4.2</td>
<td>0xf0bedea5, 0x05bf, 0x4ab9, 0x89, 0xb3, 0xdf, 0xd9, 0x8e, 0x08,
0xe4, 0xdd</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes()</strong> – invokes
<strong>Routes()</strong> with a <em>SubnetMask</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> with a
<em>SubnetMask</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.4.3</td>
<td>0x377694cc, 0x9254, 0x4197, 0x92, 0x6c, 0x26, 0x58, 0x5c, 0xde,
0xc9, 0x4c</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> with a <em>GatewayAddress</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> with a
<em>GatewayAddress</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.4.4</td>
<td>0xc694ffe9, 0xef16, 0x47f4, 0x86, 0x89, 0x34, 0x6c, 0x80, 0xb1,
0x59, 0x54</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> with a <em>*SubnetMask</em> value of an
invalid subnet mask.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> with a
<em>*SubnetMask</em> value of an invalid subnet mask. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.4.5</td>
<td>0x601c9a17, 0x1da6, 0x45bc, 0xbb, 0xdc, 0xf8, 0x92, 0xdc, 0xe3,
0x43, 0x04</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> with a <em>*GatewayAddress</em> value of an
invalid unicast IP address.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> with a
<em>*GatewayAddress</em> value of an invalid unicast IP address. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.4.6</td>
<td>0xab7d87d5, 0x9761, 0x4877, 0x9f, 0x96, 0x42, 0xab, 0x99, 0x66,
0xd5, 0x3f</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> to delete a route which is not in the routing
table.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to delete a route
which is not in the routing table. The return status should be
<strong>EFI_NOT_FOUND</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.4.7</td>
<td>0x72569926, 0x4edb, 0x4d5b, 0xa2, 0xe5, 0x76, 0x31, 0x2f, 0xd2,
0x76, 0x74</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> to add a route that has already defined in the
routing table.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to add a route
into the routing table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to add the route
into the routing table which has already defined in step 3. The return
status should be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.4.10</td>
<td>0xe9ff9948, 0x9168, 0x4698, 0xa1, 0x49, 0x44, 0xef, 0x57, 0x33,
0x77, 0x20</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> when the EFI UDPv4 Protocol instance has not
been started.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> when the EFI
UDPv4 Protocol instance has not been started. The return status should
be <strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.4.8</td>
<td>0xae5c33be, 0x930e, 0x401b, 0x8f, 0x4d, 0x32, 0xc8, 0x95, 0xc4,
0x55, 0x48</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> to add a route to destination IP and send a
packet to it.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to add a route
into the routing table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> to send a
packet to the destination IP and check that it is successful.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.4.9</td>
<td>0xd39800b9, 0xe6e6, 0x4e29, 0xab, 0xd6, 0x17, 0x7a, 0x46, 0x10,
0x51, 0x3d</td>
<td><strong>EFI_UDP4_PROTOCOL.Routes() –</strong> invokes
<strong>Routes()</strong> to delete a route to destination IP and check
that packet can not been sent to it.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to add a route
into the routing table. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Routes()</strong> to delete the
route added in the step 3. The return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> to send a
packet to the destination IP and check that it will be failed.</p>
<p>6. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Transmit()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.1.5.1</td>
<td>0xd793cd46, 0x574d, 0x4f5d, 0x92, 0x8a, 0x2b, 0x84, 0x7a, 0xc0,
0x77, 0xd9</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit()</strong> – invokes
<strong>Transmit()</strong> with a <em>Token</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> with a
<em>Token</em> value of <strong>NULL</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.2</td>
<td>0xf8ffef65, 0x20fe, 0x4381, 0xa5, 0x46, 0x07, 0x7c, 0x5a, 0x89,
0x7b, 0x6d</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit()</strong> – invokes
<strong>Transmit()</strong> with a <em>Token.Event</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Transmit()</strong> with a
<em>Token.Event</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.3</td>
<td>0x157caa4e, 0xa260, 0x47a2, 0x97, 0x04, 0xd6, 0x62, 0x6c, 0xd9,
0x62, 0xf9</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit()</strong> – invokes
<strong>Transmit()</strong> with a <em>Token</em>.Packet.FragmentCount
value of 0.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Transmit()</strong> with a
<em>Token</em>.Packet.FragmentCount value of 0. The return status should
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.4</td>
<td>0xceebb331, 0x26c1, 0x4c6b, 0x91, 0x74, 0xb2, 0xdd, 0xda, 0xb7,
0x3a, 0x7a</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit()</strong> – invokes
<strong>Transmit()</strong> with a <em>Token.Packet.TxData</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Transmit()</strong> with a
<em>Token.Packet.TxData</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.5</td>
<td>0xd381956d, 0x6b86, 0x48a4, 0x82, 0x56, 0x37, 0x5e, 0xa2, 0x46,
0xf6, 0xfa</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> with a
<em>Token</em><strong>.Packet.DataLength</strong> value other than equal
to the sum of fragment lengths.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> with a
<em>Token</em><strong>.Packet.DataLength</strong> value other than equal
to the sum of fragment lengths. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.7</td>
<td>0x7f9fc4ec, 0x756c, 0x4399, 0xa2, 0x7e, 0x2e, 0x38, 0x3a, 0xff,
0x4e, 0x7b</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong>with the parameter
<em>Token.Packet.TxData.FragmentTable[].FragmentLenth/FragmetBuffer</em>
fields being invalid.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
parameter <em>Token.Packet.TxData.FragmentTable[].FragmentLenth</em>
fields being zero. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
parameter <em>Token.Packet.TxData.FragmentTable[].FragmentBuffer</em>
fields being <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.8</td>
<td>0x5d755449, 0x3840, 0x4cc8, 0x9c, 0x7f, 0x3a, 0x1a, 0xf3, 0x42,
0xd2, 0x89</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong>with the parameter
<em>Token.Packet.TxData.GatewayAddress</em> being not a valid unicast
IPv4 address if it is not <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
parameter <em>Token.Packet.TxData.GatewayAddress</em> being
255.255.255.255. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.9</td>
<td>0x411080da, 0x2db4, 0x415e, 0xa0, 0xf5, 0x72, 0xf4, 0x1e, 0x55,
0x38, 0xdb</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong>with the parameter
<em>Token.Packet.TxData.GatewayAddress</em> being not a valid unicast
IPv4 address if it is not <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
parameter <em>Token.Packet.TxData.GatewayAddress</em> being
172.16.220.255. The return status should be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.10</td>
<td>0x154ee561, 0x041a, 0x4e4b, 0x96, 0x3a, 0xfd, 0xc6, 0x4c, 0x4e,
0x3f, 0x29</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong>with the parameter
<em>Token.Packet.TxData.GatewayAddress</em> being not a valid unicast
IPv4 address if it is not <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
parameter <em>Token.Packet.TxData.GatewayAddress</em> being 224.0.0.2.
The return status should be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.11</td>
<td>0x0161be6a, 0x75d4, 0x444b, 0xaf, 0x31, 0x78, 0xa4, 0xf0, 0x65,
0xed, 0x43</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> with
<em>Token.Packet.TxData.UdpSessionData</em> being not valid unicast IPv4
addresses if it is not <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
<em>Token.Packet.TxData.UdpSessionData</em> being 224.0.0.1. The return
status should be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.12</td>
<td>0x3315e964, 0xc1bb, 0x4984, 0xb7, 0xc3, 0xff, 0x1a, 0x94, 0xb0,
0xe9, 0xd3</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> with
<em>Token.Packet.TxData.UdpSessionData</em> being not valid unicast IPv4
addresses if it is not <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>with the
<em>Token.Packet.TxData.UdpSessionData</em> being 172.16.220.0. The
return status should be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.13</td>
<td>0x4206d340, 0xe096, 0x4369, 0x96, 0x32, 0x9a, 0x35, 0x27, 0xcf,
0x64, 0xce</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> when the EFI UDPv4 Protocol instance has not
been started.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> when the EFI
UDPv4 Protocol instance has not been started. The return status should
be <strong>EFI_NOT_STARTED.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.14</td>
<td>0xbd543b46, 0xcb6a, 0x4cfb, 0x80, 0x68, 0xe1, 0xaa, 0x28, 0x32,
0x43, 0x75</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> when there is no route to the destination
network or address.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> when there is
no route to the destination network or address. The return status should
be <strong>EFI_NOT_FOUND.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.15</td>
<td>0x0b3c198b, 0xfffd, 0x4dde, 0x9b, 0x1e, 0xbd, 0x5f, 0x8e, 0x70,
0xa0, 0xc2</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> when the data length is greater than the
maximum UDP packet size.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong>when the data
length is greater than the maximum UDP packet size. The return status
should be <strong>EFI_BAD_BUFFER_SIZE.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.16</td>
<td>0xae0d4495, 0xbcda, 0x4de3, 0xa4, 0xbc, 0xab, 0xed, 0xd4, 0x82,
0xdc, 0x92</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> when the length of the IP header+UDP
header+data length is greater than MTU if <em>DoNotFragment</em> is
<strong>TRUE</strong></td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> when the length
of the IP header+UDP header+data length is greater than MTU if
<em>DoNotFragment</em> is <strong>TRUE.</strong> The return status
should be <strong>EFI_BAD_BUFFER_SIZE.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.17</td>
<td>0xd983be7a, 0x33fd, 0x4308, 0x80, 0x6c, 0x00, 0x58, 0xef, 0xff,
0xe8, 0x17</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit()</strong> – to add a route to
destination IP and send a packet to it.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Routes()</strong>to add a
route.</p>
<p>4. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Transmit()</strong>to
transmit packet.</p>
<p>5. Captured packet and verify.</p>
<p>6. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.5.18</td>
<td>0x71158c72, 0xa476, 0x42a8, 0x94, 0x81, 0x6d, 0xa0, 0xb8, 0xb4,
0x2c, 0xef</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> when the <em>TxData.GatewayAddress</em> has
been set</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Transmit()</strong>to
transmit packet.</p>
<p>4. Captured packet and verify.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.5.6</td>
<td>0xc0c68374, 0x0d85, 0x4bbb, 0x8b, 0x20, 0xbd, 0x88, 0xb1, 0xb0,
0x7b, 0xd7</td>
<td><strong>EFI_UDP4_PROTOCOL.Transmit() –</strong> invokes
<strong>Transmit()</strong> with the transmit completion token whose
<em>Token.Event</em> was already in the transmit queue.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> to transmit a
packet. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Transmit()</strong> with the same
<em>Token.Event</em> in step 3. The return status should be
<strong>EFI_ACCESS_DENIED.</strong></p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Receive()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 20%" />
<col style="width: 24%" />
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
<td>5.26.1.6.1</td>
<td>0x95bf8134, 0x5277, 0x413c, 0xbe, 0x1f, 0xf5, 0x03, 0x2b, 0x08,
0x78, 0x92</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive()</strong> – invokes
<strong>Receive()</strong> with a <em>Token</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> with a
<em>Token</em> value of <strong>NULL</strong>. The return status should
be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.6.2</td>
<td>0xa158c0cd, 0x496b, 0x4dfe, 0x9c, 0xe9, 0x93, 0xea, 0x76, 0x40,
0x77, 0x7a</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive()</strong> – invokes
<strong>Receive()</strong> with a <em>Token.Event</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL</strong>.<strong>Receive()</strong>
with a <em>Token.Event</em> value of <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.6.3</td>
<td>0xdd8e13d5, 0x7a76, 0x4237, 0x82, 0x14, 0x79, 0x03, 0xda, 0x61,
0x92, 0x4d</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> invokes
<strong>Receive()</strong> when the EFI UDPv4 Protocol instance has not
been started.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>when the EFI
UDPv4 Protocol instance has not been started. The return status should
be <strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.6.4</td>
<td>0xe2a9f6b9, 0x7827, 0x474f, 0x97, 0x12, 0xc6, 0x9c, 0xad, 0xb0,
0x1c, 0x49</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> invokes
<strong>Receive()</strong>when a receive completion token with the same
<em>Token.Event</em> was already in the receive queue.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> at the first
time the return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL</strong>.<strong>Receive()</strong>
again the return status should be EFI_ACCESS_DENIED.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.6.5</td>
<td>0xa96aa0f5, 0x1c6b, 0x41cf, 0x98, 0x2f, 0xf8, 0x4f, 0x90, 0x43,
0x34, 0xb3</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> the receiving fails
because an ICMP error packet is received.</td>
<td><p>1. Create a NETWORK unreachable packet.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>to receive the
packet. The return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Verify the R_<em>Token</em>.Status it should be
EFI_NETWORK_UNREACHABLE.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.6.6</td>
<td>0x3db8e8ee, 0x6c0b, 0x43d2, 0xa5, 0xfe, 0xb2, 0x34, 0x30, 0x5c,
0x12, 0xf8</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> the receiving fails
because an ICMP error packet is received.</td>
<td><p>1. Create a HOST unreachable packet.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>to receive the
packet. The return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Verify the R_<em>Token</em>.Status it should be
<strong>EFI_HOST_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.1.6.7</td>
<td>0x26f533d1, 0xb63e, 0x4997, 0xbd, 0x2d, 0x68, 0x52, 0xc8, 0x0c,
0xe3, 0x71</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> the receiving fails
because an ICMP error packet is received.</td>
<td><p>1. Create a PROTOCOL error packet.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>to receive the
packet. The return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Verify the R_<em>Token</em>.Status it should be
<strong>EFI_PROTOCOL_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.6.8</td>
<td>0xc982e2f7, 0xdf6f, 0x4a7b, 0x9d, 0x4a, 0x25, 0x87, 0x0c, 0x80,
0xb7, 0x9b</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> the receiving fails
because an ICMP error packet is received.</td>
<td><p>1. Create a PORT unreachable packet.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>to receive the
packet. The return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Verify the R_<em>Token</em>.Status it should be
<strong>EFI_PORT_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.1.6.9</td>
<td>0x0685647b, 0xeee8, 0x4756, 0xbf, 0xea, 0x72, 0xc6, 0xb5, 0xff,
0x98, 0xb6</td>
<td><strong>EFI_UDP4_PROTOCOL.Receive() –</strong> the receiving fails
because an ICMP error packet is received.</td>
<td><p>1. Create a TCMP error packet.</p>
<p>2. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong>to receive the
packet. The return status should be <strong>EFI_SUCCESS.</strong></p>
<p>3. Verify the R_<em>Token</em>.Status it should be
<strong>EFI_ICMP_ERROR</strong>.</p></td>
</tr>
</tbody>
</table>



### Cancel()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 20%" />
<col style="width: 24%" />
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
<td>5.26.1.7.1</td>
<td>0xb4ca8ee0, 0x2b8b, 0x41b3, 0x97, 0x3c, 0x2f, 0x2b, 0x05, 0x07,
0x48, 0x17</td>
<td><strong>EFI_UDP4_PROTOCOL.Cancel() –</strong> invokes
<strong>Cancel()</strong> to cancel a receive request while it has been
completed.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to receive a
packet and check that it is successful.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Cancel()</strong> to cancel the
receive request while the token has been completed. The return status
should be <strong>EFI_NOT_FOUND</strong>.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.1.7.2</td>
<td>0x46a1ec38, 0x0183, 0x485a, 0xa2, 0xa5, 0x50, 0x4e, 0x3b, 0xdb,
0x1b, 0x53</td>
<td><strong>EFI_UDP4_PROTOCOL.Cancel() –</strong> invokes
<strong>Cancel()</strong> to cancel a receive request.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to receive a
packet.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Cancel()</strong> to cancel the
receive request in step 3. Then check the packet sent to EUT will not be
captured.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.1.7.3</td>
<td>0x6fff20b8, 0x55cd, 0x4610, 0xb3, 0xbe, 0xaa, 0x19, 0x5f, 0x29,
0x10, 0x66</td>
<td><strong>EFI_UDP4_PROTOCOL.Cancel() –</strong> invokes
<strong>Cancel()</strong> to cancel all pending tokens with the
parameter <em>Token</em> set to <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance.</p>
<p>3. Call <strong>EFI_UDP4_PROTOCOL.Receive()</strong> to set two
requests in the receive queue.</p>
<p>4. Call <strong>EFI_UDP4_PROTOCOL.Cancel()</strong> with the
parameter <em>Token</em> set to <strong>NULL</strong>. Then check that
no packet sent to EUT will be captured.</p>
<p>5. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>


### Poll()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 20%" />
<col style="width: 25%" />
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
<td>5.26.1.8.1</td>
<td>0x18e54eae, 0x4d67, 0x468c, 0xb6, 0x0d, 0x81, 0x83, 0xd4, 0x07,
0xfe, 0xe8</td>
<td><strong>EFI_UDP4_PROTOCOL.Poll() –</strong> invokes
<strong>Poll()</strong> when the instance has not been started.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_PROTOCOL</strong>.<strong>Configure()</strong> to
configure the new <strong>EFI_UDP4_PROTOCOL</strong> instance. Then call
<strong>EFI_IP4_PROTOCOL.Configure()</strong> again with an
<em>IpConfigData</em> value of <strong>NULL</strong>.</p>
<p>3. Call <strong>EFI_IP4_PROTOCOL.Poll()</strong> for incoming data
packets and processing outgoing data packets. The return status should
be <strong>EFI_NOT_STARTED</strong>.</p>
<p>4. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>




### CreateChild()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.1.9.1</td>
<td>0xf88eaa0c, 0x764e, 0x45e0, 0x95, 0x86, 0xa6, 0x7f, 0x7d, 0x6f,
0xb2, 0x82</td>
<td><strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> –
invokes CreateChild() with a <em>ChildHandle</em> value of
<strong>NULL</strong>.</td>
<td>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child with a
<em>ChildHandle</em> value of <strong>NULL</strong>. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.1.9.2</td>
<td>0x4dedef14, 0xbcba, 0x4b26, 0xbc, 0xc8, 0xb4, 0x7f, 0x8c, 0x08,
0xc9, 0x9d</td>
<td><strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> –
invokes CreateChild() to create three instances.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create three <strong>EFI_UDP4_PROTOCOL</strong> instances and configure
them. The return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment.</p></td>
</tr>
</tbody>
</table>



### DestroyChild()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.1.10.1</td>
<td>0x0ff5f5a1, 0x4d29, 0x40ae, 0xa4, 0xef, 0x02, 0x3b, 0xd3, 0xb8,
0x2e, 0x8c</td>
<td><strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> –
invokes <strong>DestroyChild()</strong> with an invalid
<em>ChildHandle</em> value.</td>
<td>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>with an
invalid <em>ChildHandle</em> value. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.1.10.3</td>
<td>0x9d888685, 0xfde7, 0x4832, 0xbc, 0x95, 0x03, 0xd6, 0x44, 0xc6,
0x29, 0xc5</td>
<td><strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> –
invokes <strong>DestroyChild()</strong> to destroy an existed child
twice.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_UDP4_PROTOCOL</strong> child.</p>
<p>2. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL.</strong> The return
status should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> again.
The return status should be EFI_UNSUPPORTED.</p></td>
</tr>
<tr class="even">
<td>5.26.1.10.2</td>
<td>0x1ff85dcf, 0x885e, 0x42bf, 0x80, 0xd8, 0xf8, 0x4a, 0xaf, 0x11,
0xeb, 0x77</td>
<td><strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> –
invokes <strong>DestroyChild()</strong> to destroy a child.</td>
<td><p>1. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a <strong>EFI_UDP4_PROTOCOL</strong> child. The return status
should be <strong>EFI_SUCCESS</strong>.</p>
<p>2. Call
<strong>EFI_UDP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created <strong>EFI_UDP4_PROTOCOL</strong> child and clean
up the environment. The return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
</tbody>
</table>



## EFI_MTFTP4_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_MTFTP4_PROTOCOL Section.

### CreateChild()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.1.1</td>
<td>0xf44c5295, 0x599e, 0x48bc, 0xbb, 0x67, 0xed, 0x9a, 0x21, 0x5b,
0xa9, 0xb1</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_INVALID_PARAMETER</strong> when creating Child 1
again.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create the same child again.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.1.5</td>
<td><p>0x5e30aa7c,0xd5f6,</p>
<p>0x4cac,</p>
<p>0xb2,0x54,</p>
<p>0xbf,0xdf,</p>
<p>0x16,0x3b,</p>
<p>0x34,0xfc</p></td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> –
invokes <strong>CreateChild()</strong> with <em>ChildHandle</em> being
<strong>NULL</strong>.</td>
<td>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong>with
<em>ChildHandle</em> being <strong>NULL.</strong> The return status must
be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.2.1.2</td>
<td>0xca3fb64a, 0xd149, 0x4f76, 0x91, 0x45, 0xe4, 0xf6, 0xcc, 0xe6,
0x5b, 0x27</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_SUCCESS</strong> when creating child1.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle1.</p>
<p>The return status must be <strong>FI_SUCCESS.</strong></p></td>
</tr>
<tr class="odd">
<td>5.26.2.1.3</td>
<td>0xb07ae013, 0x0d83, 0x49c3, 0x99, 0x23, 0xef, 0x27, 0x67, 0xd5,
0x48, 0xfe</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_SUCCESS</strong> when creating child2.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle1.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle: Handle2.
The return status must be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.2.1.4</td>
<td>0xd4d966c4, 0xc05a, 0x4995, 0xbf, 0xfb, 0x2c, 0x86, 0x8b, 0x3c,
0x2c, 0x0b</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> -
returns <strong>EFI_SUCCESS</strong> when creating child3.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle1.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle2.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle: Handle3.
The return status must be <strong>EFI_SUCCESS.</strong></p>
<p>6. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
three times to destroy the three newly created
<strong>EFI_MTFTP4_PROTOCOL</strong> child handles and clean up the
environment.</p></td>
</tr>
</tbody>
</table>


### DestroyChild()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.2.1</td>
<td>0x3c312328, 0x313d, 0x47f6, 0x80, 0x7c, 0x5b, 0x1e, 0x10, 0xc2,
0xc0, 0x4d</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
- returns <strong>EFI_INVALID_PARAMETER</strong> when destroying a
<strong>NULL</strong> child.</td>
<td><p>Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy a <strong>NULL</strong> child.</p>
<p>The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="odd">
<td>5.26.2.2.2</td>
<td>0xe1c0ee52, 0xd5af, 0x4ec0, 0xa3, 0xf6, 0x31, 0xfb, 0xe0, 0xd4,
0xb7, 0x04</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
- returns <strong>EFI_INVALID_PARAMETER</strong> when destroying an
un-existed child.</td>
<td><p>Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy an un-existed child.</p>
<p>The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.2.2.3</td>
<td>0x28f8e30c, 0xa5d9, 0x4327, 0x99, 0xfa, 0xac, 0xda, 0xc9, 0x5f,
0xa4, 0xff</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
- returns <strong>EFI_UNSUPPORTED</strong> when destroying the same
child twice.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:</p>
<p>2. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the new created child.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created child again. The return status must be
<strong>EFI_UNSUPPORTED.</strong></p></td>
</tr>
<tr class="odd">
<td>5.26.2.2.4</td>
<td>0xcb939b7a, 0x266a, 0x44f5, 0xa2, 0xe3, 0x57, 0xea, 0xde, 0x7f,
0x44, 0x08</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
- returns <strong>EFI_SUCCESS</strong> with all valid invocations.</td>
<td><p>1 .Add an entry in ARP cache.</p>
<p>2. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle1.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>5. If having not captured the packet, OS side set assert fail and
call <strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
to destroy the created child and clean up the environment. The return
status must be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.2.2.5</td>
<td>0xc9d38d67, 0xadc1, 0x425d, 0xa4, 0xa1, 0x04, 0x18, 0xc6, 0x4b,
0x63, 0x0c</td>
<td><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
- returns <strong>EFI_SUCCESS</strong> with all valid invocations.</td>
<td><p>1 .Add an entry in ARP cache.</p>
<p>2. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle:
Handle1.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>5. If having captured the packet, configured OS side will send back a
normal OACK packet with active flag set. 6. OS side captures ack packet
sent from EUT side and call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the created child and clean up the environment. The return
status must be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
</tbody>
</table>


### GetModeData()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.3.1</td>
<td>0xdc9ac841, 0x8a0f, 0x4214, 0x91, 0x73, 0x60, 0x65, 0xee, 0x51,
0x8c, 0x52</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetModeData()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>ModeData</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.GetModeData()</strong> with a
<em>ModeData</em> value of <strong>NULL</strong>. The return status must
be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.3.2</td>
<td>0x40eccfcd, 0xee1c, 0x405f, 0xb0, 0x64, 0x2d, 0xe5, 0x66, 0x7b,
0xfb, 0xee</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetModeData()</strong> - returns
<strong>EFI_SUCCESS</strong> with all valid invocations.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetModeData()</strong> with all
valid parameters. The return status must be
<strong>EFI_SUCCESS.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment..</p></td>
</tr>
</tbody>
</table>

### Configure()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.4.1</td>
<td>0x2c5b72d9, 0x2c30, 0x4249, 0xa2, 0x3a, 0x92, 0x14, 0xfd, 0xea,
0x73, 0x12</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when</p>
<p><em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> is
<strong>FALSE</strong> and <em>MtftpConfigData</em>-&gt;
<em>StationIp</em> is an invalid IPv4 unicast address.</p></td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2.Call
<strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
with</p>
<p>a <em>MtftpConfigData-&gt; UseDefaultSetting</em> value of
<strong>FALSE</strong> and a <em>MtftpConfigData-&gt; StationIp</em>
value of unicast address. The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.4.2</td>
<td>0x01ef2cac, 0x1259, 0x41c9, 0xbd, 0x91, 0x49, 0x68, 0xa9, 0xfd,
0xd6, 0x42</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when</p>
<p><em>MtftpConfigData</em>-<em>&gt; UseDefaultSetting</em> is
<strong>FALSE</strong> and <em>MtftpConfigData-&gt; SubnetMask</em> is
invalid.</p></td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2.Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> when
<em>MtftpConfigData</em>-&gt;<em>UseDefaultSetting</em> is
<strong>FALSE</strong> and
<em>MtftpConfigData</em>-&gt;<em>SubnetMask</em> is invalid. The return
status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.4.3</td>
<td>0xbe92bd2e, 0xd085, 0x4da2, 0xaf, 0xbf, 0xec, 0x7b, 0x0d, 0xc7,
0xec, 0xca</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
- returns <strong>EFI_INVALID_PARAMETER</strong> when</p>
<p><em>MtftpConfigData-&gt; UseDefaultSetting</em> is
<strong>FALSE</strong> and <em>MtftpConfigData-&gt; ServerIp</em> is an
invalid IPv4 unicast address.</p></td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call
<strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong> with
a</p>
<p><em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> value of
<strong>FALSE</strong> and a <em>MtftpConfigData</em>-&gt;
<em>ServerIp</em> value of an invalid IPv4 unicast address. The return
status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.4.4</td>
<td>0x5891d15c, 0x7f5d, 0x4c0d, 0xb0, 0x90, 0x88, 0xcd, 0x44, 0xe1,
0xea, 0x68</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
- returns <strong>EFI_INVALID_PARAMETER</strong> when</p>
<p><em>MtftpConfigData-&gt; UseDefaultSetting</em> is
<strong>FALSE</strong> and <strong>MtftpConfigData-&gt;
GatewayIp</strong> is an invalid IPv4 unicast address.</p></td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <em>EFI_MTFTP4_PROTOCOL</em>.<strong>Configure()</strong>
with a</p>
<p><em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> value of
<strong>FALSE</strong> and a <em>MtftpConfigData</em>-&gt;
<em>GatewayIp</em> value of an invalid IPv4 unicast address. The return
status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.4.5</td>
<td>0xd01d26be, 0x35fb, 0x4a08, 0xb0, 0x22, 0x7b, 0xe2, 0x53, 0xcf,
0x99, 0x02</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
- returns <strong>EFI_INVALID_PARAMETER</strong> when</p>
<p><em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> is
<strong>FALSE</strong> and <em>MtftpConfigData</em>-&gt;
<em>GatewayIp</em> is not in the same subnet with station
address.</p></td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2.Call
<strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
when</p>
<p><em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> is
<strong>FALSE</strong> and <em>MtftpConfigData</em>-&gt;
<em>GatewayIp</em> is not in the same subnet with station address. The
return status must be <strong>EFI_INVALID_PARAMETER.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.4.6</td>
<td>0x37ccae28, 0x4b81, 0x4ba5, 0x8d, 0xe6, 0x79, 0xe7, 0xda, 0xb9,
0x03, 0x04</td>
<td><strong>EFI_MTFTP4_PROTOCOL.Configure ()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when some operation of this EFI
MTFTPv4 Protocol driver instance has not finished yet and the
configuration data cannot be changed at this time.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2.Call
<strong>EFI_MTFTP4_PROTOCOL</strong>.<strong>Configure()</strong>
when</p>
<p>some operation of this EFI MTFTPv4 Protocol driver instance has not
finished yet and the configuration data cannot be changed at this time.
The return status must be <strong>EFI_ACCESS_DENIED.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.4.7</td>
<td>0xd31e47ea, 0x5a76, 0x49aa, 0xbd, 0x40, 0x6f, 0xd9, 0x49, 0x88,
0x5f, 0x84</td>
<td><strong>EFI_MTFTP4_PROTOCOL.Configure ()</strong> - returns
<strong>EFI_SUCCESS</strong> when it is reset by calling Configure ()
with a <em>MtftpConfigData</em> value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with
<em>MtftpConfigData</em> set to <strong>NULL</strong>. The return status
must be <strong>EFI_SUCCESS.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>

### GetInfo()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.26.2.5.1</td>
<td>0x794b1aae, 0x92b4, 0x40de, 0xad, 0xed, 0x43, 0xb3, 0x55, 0x37,
0xd8, 0xa3</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>FileName</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData-&gt; UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with a
<em>FileName</em> value of <strong>NULL</strong>. The return stats must
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.2</td>
<td>0x0733cdb5, 0x4072, 0x4129, 0xa2, 0x06, 0xce, 0x56, 0x6e, 0xf6,
0xd8, 0x61</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<em>OverrideData</em>.GatewayIp value of invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData-&gt; UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with an
<em>OverrideData</em>.GatewayIp value of invalid. The return status must
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.3</td>
<td>0xa04d3e7c, 0x5e50, 0x4472, 0xa7, 0x70, 0xc1, 0xa9, 0x48, 0xcb,
0xd9, 0x1e</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>OverrideData</em>.ServerIp value.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData-&gt; UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with an
<em>OverrideData</em>.ServerIp value of invalid. The return status must
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.4</td>
<td>0x10d2101c, 0x0aa3, 0x4713, 0xb8, 0x2b, 0xe1, 0x43, 0xed, 0xf4,
0x11, 0x26</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>OverrideData</em>.GatewayIp and <em>OverrideData</em>.ServerIp are
not in the same subnet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with
<em>OverrideData</em>.GatewayIp and <em>OverrideData</em>.ServerIp are
not in the same subnet. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.5</td>
<td>0xf85b07f6, 0x9f89, 0x41ad, 0x8d, 0x53, 0x47, 0x53, 0x97, 0xac,
0x98, 0x1a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>OptionCount</em> is not
0 and <em>OptionList</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> when
<em>OptionCount</em> is not 0 and <em>OptionList</em> is
<strong>NULL</strong>. The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.6</td>
<td>0xb9caedcf, 0xf071, 0x421a, 0x9f, 0xb9, 0x7e, 0x24, 0x9d, 0xf4,
0xe3, 0xb2</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>PacketLength</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with a
<em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> value of
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with a
<em>PacketLength</em> value of <strong>NULL</strong>. The return status
must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.7</td>
<td>0x5cb9e305, 0xb4e2, 0x4416, 0xa7, 0x35, 0xe2, 0x72, 0xb6, 0x98,
0xf8, 0x23</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> with a MTFTPv4 ERROR packet having
received in the Buffer.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with
<em>MtftpConfigData</em>-&gt; <em>UseDefaultSetting</em> is
<strong>FALSE</strong>.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> when
<em>OverrideData</em> is <strong>NULL</strong> and <em>ModeStr</em> is
<strong>NULL</strong>. OS side must capture the packet sent from EUT
side.</p>
<p>4. If have captured the packet, configured OS side to send back a
MTFTPv4 ERROR packet and OS side should capture another packet sent from
EUT side. The return status must be <strong>EFI_TFTP_ERROR</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.8</td>
<td>0x30e6a222, 0x2bbc, 0x4ff6, 0xa8, 0xf2, 0xd6, 0x8a, 0xc2, 0x91,
0x98, 0x29</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_TIMEOUT</strong> when no packets were received from the
MTFTPv4 server.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> when
<em>OverrideData</em> is <strong>NULL</strong> and ModeStr is
<strong>NULL</strong>. In addition, the OS side doesn’t send any packets
back. The return status must be <strong>EFI_TIMEOUT.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.9</td>
<td>0xc4c5ced1, 0x30a5, 0x4c54, 0xa3, 0xc0, 0x80, 0x2b, 0x35, 0x83,
0xbf, 0x70</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_NOT_STARTED</strong> with the EFI MTFTPv4 Protocol driver
having not been started.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> when both
<em>OverrideData</em> and <em>ModeStr</em> are <strong>NULL</strong>.
The return status must be <strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.10</td>
<td>0x32db978c, 0x9d9b, 0x4144, 0x97, 0x9c, 0x27, 0x14, 0x42, 0x9f,
0xe3, 0x47</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when invoking
<strong>GetInfo()</strong> interface while the previous operation has
not been completed yet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> to change the
<strong>EFI_MTFTP4_PROTOCOL</strong> State.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> when the
previous operation has not been completed yet. The return status must be
<strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.11</td>
<td>0xbf72714a, 0x113f, 0x487e, 0xab, 0x10, 0x08, 0xa7, 0x98, 0xf3,
0x4f, 0xc4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server responding a normal OACK
packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side should capture the packet sent from EUT side.</p>
<p>4. Configure OS side to send back a normal OACK packet and OS side
should capture another packet sent from EUT side.</p>
<p>5. The return status of the
<strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.12</td>
<td>0x77dbe1e4, 0x6219, 0x4531, 0xae, 0xbe, 0x58, 0x26, 0x4b, 0x53,
0x7e, 0xd1</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - test the
<strong>EFI_ICMP_ERROR</strong> conformance of
<strong>GetInfo()</strong> when an ICMP ERROR packet was received and in
the buffer.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side should capture the packet sent from EUT side.</p>
<p>4. Configure OS side to send back a ICMP error packet. The return
status must be <strong>EFI_ICMP_ERROR.</strong></p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.13</td>
<td>0x70e8d3e9, 0x75a9, 0x4652, 0x82, 0x68, 0xa4, 0x0d, 0xdd, 0x1a,
0x81, 0x5f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - test the
<strong>EFI_UNSUPPORTED</strong> conformance of
<strong>GetInfo()</strong> when one or more options in the optionlist
are in the unsupported list of structure
<strong>EFI_MTFTP4_MODE_DATA</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with one or
more options in the optionlist are in the unsupported list of structure
<strong>EFI_MTFTP4_MODE_DATA</strong>. The return status should be
<strong>EFI_UNSUPPORTED.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.14</td>
<td>0xfaa23d30, 0x1d66, 0x4d8e, 0xbe, 0x21, 0x2d, 0xa7, 0xbc, 0x1c,
0x9d, 0xfd</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> - test the
<strong>EFI_PROTOCOL_ERROR</strong> conformance of
<strong>GetInfo()</strong>. The client received an unexpected MTFTPv4
packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side should capture the packet sent from EUT side.</p>
<p>4. Configure OS side to send back an unexpected packet and the return
status should be <strong>EFI_PROTOCOL_ERROR</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.15</td>
<td>0xd2c1e819, 0x610b, 0x4cfc, 0x94, 0xf1, 0x33, 0xcd, 0x13, 0xaf,
0x4b, 0xc9</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo – GetInfo()</strong> must return
<strong>EFI_NETWORK_UNREACHABLE</strong> when receive an ICMP net
unreachable packet.</td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROT OCOL.CreateChild()</strong>
to create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP net unreachable packet and the return status should be
<strong>EFI_NETWORK_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_P ROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.16</td>
<td>0x290076e3, 0xdaf2, 0x453d, 0xb2,0x21,0xcd,0x27,
0xce,,0xe7,0x3d,0xbe</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo – GetInfo()</strong> must return
<strong>EFI_HOST_UNREACHABLE</strong> when receiving an ICMP host
unreachable packet.</td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROT OCOL.CreateChild()</strong>
to create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configur</strong></p>
<p><strong>e()</strong> with all valid parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP host unreachable packet and the return status should be
<strong>EFI_HOST_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_P ROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created <strong>EFI_MTFTP4_PROTOCO</strong>L child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.5.17</td>
<td>0x706bc816, 0x6353, 0x40ae, 0xa9,0x47,0x9a,0xf0,
0x01,0xa9,0x82,0x8c</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo – GetInfo()</strong> must return
<strong>EFI_PROTOCOL_UNREACHABLE</strong> when receive an ICMP protocol
unreachable packet.</td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROT OCOL.CreateChild()</strong>
to create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configur</strong></p>
<p><strong>e()</strong> with all valid parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP protocol unreachable packet and the return status should be
<strong>EFI_PROTOCOL_UNREACHABLE</strong>.</p>
<p>5. Call <strong>EFI_MTFTP4_SERVICE_BINDING_P
ROTOCOL.DestroyChild()</strong> to</p>
<p>destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.5.18</td>
<td>0xa165bd19, 0x951a, 0x4486,
0x88,0x4d,0x1d,0x94,0x30,0xa7,0xbe,0x3c</td>
<td><strong>EFI_MTFTP4_PROTOCOL.GetInfo – GetInfo()</strong> must return
<strong>EFI_PORT_UNREACHABLE</strong> when receive an ICMP port
unreachable packet.</td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROT OCOL.CreateChild()</strong>
to create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configur</strong></p>
<p><strong>e()</strong> with all valid parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.GetInfo()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP port unreachable packet and the return status should be
<strong>EFI_PORT_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_P ROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
</tbody>
</table>



### ParseOptions()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.26.2.6.1</td>
<td>0x9bea2f3f, 0x9f02, 0x4eb2, 0x8b, 0x1f, 0x99, 0xd5, 0xcf, 0xc3,
0x57, 0x29</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with a <em>PacketLength</em>
value of 0.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with a
<strong>PacketLength</strong> value of 0. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.6.2</td>
<td>0x0bc09196, 0xb38a, 0x4fa8, 0xb0, 0x38, 0x4c, 0x4c, 0x8b, 0x3c,
0x69, 0xfa</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with a <em>Packet</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with a
<em>Packet</em> value of <strong>NULL</strong>. The return status must
be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.6.3</td>
<td>0x72723929, 0x60bd, 0x49c1, 0x99, 0xbd, 0xd1, 0x48, 0x60, 0x33,
0x7a, 0xdc</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with a <em>Packet</em> value of
an invalid MTFTPv4 Packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with a
<em>Packet</em> value of an invalid MTFTPv4 Packet <strong>-</strong>
<strong>Packet.OpCode</strong> is 0x11. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.6.4</td>
<td>0xb7ed01b9, 0x7e1b, 0x40ba, 0x8b, 0x6a, 0x52, 0x34, 0xdf, 0x13,
0x53, 0xf0</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with a <em>Packet</em> value of
an invalid MTFTPv4 Packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with a
<em>Packet</em> value of an invalid MTFTPv4 Packet -
<strong>Packet.OpCode</strong> is 0x01.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.6.5</td>
<td>0x350c473e, 0x9901, 0x4125, 0xbc, 0xc9, 0x65, 0xbf, 0xa9, 0xf3,
0x16, 0x30</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with a <em>Packet</em> value of
an invalid MTFTPv4 Packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with a
<em>Packet</em> value of an invalid MTFTPv4 Packet -
<strong>Packet.OpCode</strong> is 0x06 and <em>PacketLength</em> is 1.
The return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.6.6</td>
<td>0xcf909489, 0xace2, 0x4fec, 0x8d, 0xc9, 0x66, 0xa0, 0xd9, 0x33,
0xa6, 0x4a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_parameter</strong> with an <em>OptionCount</em>
value of <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with an
<em>OptionCount</em> value of <strong>NULL</strong>.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.6.7</td>
<td>0x0131da11, 0x62a1, 0x494f, 0xb1, 0x0a, 0xaf, 0x5d, 0xe2, 0x12,
0xe9, 0x88</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when parsing a non-OACK
packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>BS-&gt; CopyMem()</strong> to fill the packet needed
to be parsed. Set <strong>Packet.OpCode</strong> to be 0x100.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with the
configured non-OACK packet.</p>
<p>The return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.6.9</td>
<td>0x5b7bbe95, 0xdba3, 0x4e9c, 0x89, 0xde, 0x37, 0xf1, 0xf6, 0x42,
0x04, 0x24</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - test the
<strong>EFI_NOT_FOUND</strong> conformance of
<strong>ParseOptions()</strong> with no options were found in the OACK
packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with no
options were found in the OACK packet..The return status must be
<strong>EFI_NOT_FOUND</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.6.8</td>
<td>0x973e370a, 0x5936, 0x4377, 0xb0, 0x6c, 0x82, 0xe6, 0x11, 0x4d,
0xda, 0x6f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> - returns
<strong>EFI_SUCCESS</strong> when parsing a OACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>BS-&gt; CopyMem()</strong> to fill the packet needed
to be parsed. Set <strong>Packet.OpCode</strong> to be 0x600.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ParseOptions()</strong> with the
configured OACK packet. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### ReadFile()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.7.1</td>
<td>0x38728e11, 0x6f6f, 0x409a, 0x84, 0x31, 0xf5, 0x1e, 0x60, 0x0f,
0x7d, 0x6f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TIMEOUT</strong> with no packets sent back from the MTFTPv4
server.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters.</p>
<p>4. If OS side has captured the packet, don’t send back any packets,
stall and wait until client timeout.</p>
<p>The return status must be <strong>EFI_TIMEOUT</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.2</td>
<td>0xcb0105ab, 0x7f16, 0x46a1, 0x87, 0xf2, 0x18, 0x6b, 0x86, 0x74,
0x6a, 0xba</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TIMEOUT</strong> when the passive Client having not received
any data packets from the server.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. Configure OS side to send back a normal OACK packet with flag set
to be passive.</p>
<p>5. Then OS side doesn’t send any data packets back, then stall and
wait until client timeout.</p>
<p>The return status must be <strong>EFI_TIMEOUT</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.3</td>
<td>0x95384167, 0xa706, 0x4f2c, 0x82, 0x8c, 0x8e, 0x3f, 0x15, 0xee,
0x82, 0x0a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when TFTPv4 ERROR packet was
received.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If having captured the packet, configure OS side to send back a
<strong>EFI_MTFTP4_PROTOCOL</strong> Error packet.</p>
<p>5. OS side should capture another packet sent from EUT side. The
return status must be <strong>EFI_TFTP_ERROR.</strong></p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.4</td>
<td>0xf5ac75d7, 0xa32e, 0x4b1f, 0xa8, 0x19, 0x2e, 0xfc, 0x73, 0x24,
0xcc, 0xba</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the active client receives an
MTFTPv4 ERROR packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If having captured the packet, Configure OS side to respond a
normal OACK with flag set to be active.</p>
<p>5. If having captured ack, OS side sends back a
<strong>EFI_MTFTP4_PROTOCOL</strong> Error packet. The return status
must be <strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.5</td>
<td>0x49f424ed, 0xfdbc, 0x4c82, 0x8d, 0xb8, 0xd5, 0xa2, 0xa4, 0x9b,
0x7e, 0xff</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the passive client has received a
MTFTPv4 ERROR packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If having captured the packet, configure OS side to respond a
normal OACK packet with flag set to be passive, and then send back a
<strong>EFI_MTFTP4_PROTOCOL</strong> Error packet. The return status
must be <strong>EFI_TFTP_ERROR</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.6</td>
<td>0x1392cef9, 0x74e0, 0x4f89, 0xa5, 0x26, 0xa7, 0xa7, 0x77, 0x56,
0x33, 0xd4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the server responds with an error
OACK packet – active/passive flag error.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – active/ passive flag error.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.7</td>
<td>0x1f4fd053, 0x9e4b, 0x49c4, 0x9a, 0xea, 0x58, 0x75, 0x60, 0xf1,
0xec, 0x7d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when timeout value in OACK packet is
invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – timeout value is invalid.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.8</td>
<td>0x9bbcc0bb, 0x5386, 0x4e5c, 0xa3, 0xac, 0x65, 0xc7, 0x62, 0xf6,
0x93, 0xaa</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when blocksize option value in OACK
packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – blocksize option value is invalid.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.9</td>
<td>0x329ae187, 0x6758, 0x42b9, 0x84, 0xae, 0x92, 0x32, 0x42, 0x15,
0xa5, 0xef</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when multicast IP address in OACK packet
is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – multicast IP address is invalid.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.10</td>
<td>0xe491fc10, 0x0c0f, 0x4d45, 0xb5, 0xc3, 0x3c, 0x29, 0x10, 0xdb,
0xe4, 0x70</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when client's listening port in OACK
packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – client's listening port is 65536.</p>
<p>5. If having captured an ack, OS check whether it is a packet with an
error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.11</td>
<td>0xcff83e43, 0x5d33, 0x4cc0, 0x80, 0xc4, 0x55, 0x96, 0x0e, 0x5f,
0x58, 0xae</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the format of multicast IP address
in OACK packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – the format of multicast IP address is
invalid.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.12</td>
<td>0x28754983, 0xac7d, 0x4e7f, 0x9f, 0xad, 0xbf, 0x55, 0x59, 0xff,
0xa7, 0x62</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the format of multicast option in
OACK packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – the format of multicast option is
invalid.</p>
<p>5. If having captured the ack, OS check whether it is a packet with
an error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.13</td>
<td>0x64fd965d, 0x2acc, 0x4540, 0xbc, 0x57, 0x50, 0xe8, 0xab, 0x02,
0xe8, 0x8a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the format of multicast option in
OACK packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with error OACK packet – the format of multicast option is invalid.</p>
<p>5. If having captured ack, OS check whether it is a packet with error
code. The return status must be <strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.14</td>
<td>0xd09c7076, 0x316f, 0x4245, 0xac, 0x31, 0x95, 0x82, 0x22, 0xa4,
0x67, 0xd7</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the format of multicast option in
OACK packet is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
with an error OACK packet – the format of multicast option is
invalid.</p>
<p>5. If having captured an ack, OS check whether it is a packet with an
error code. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.15</td>
<td>0x1322cb38, 0x8f90, 0x4fa8, 0xbe, 0xa9, 0x5b, 0x31, 0x8e, 0xb8,
0x24, 0xad</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the passive client tries to change
to be active, but the server responds with an error OACK packet -
active/passive flag is error.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to respond
OACK with flag set to be passive and then send the file missing several
packets.</p>
<p>5. The OS side should capture the ack sent from the passive client to
ask for the missing packets.</p>
<p>7. If having captured it, OS sends back OACK with error active/
passive flag. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.16</td>
<td>0xff2d0e80, 0xdecd, 0x4a1c, 0xb6, 0x7c, 0xe4, 0xcd, 0x99, 0x9d,
0x69, 0x09</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the server adds more other options
in the OACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active while adding more other options in the
OACK packet; then OS should capture the ack packet.</p>
<p>5. If having captured ack, OS sends back the only data packet and
then receives another ack. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.17</td>
<td>0xa7fcbfff, 0x8367, 0x466e, 0x9d, 0x25, 0x5b, 0x80, 0xb8, 0x4f,
0xb5, 0x8f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when active client receives OACK, while
<em>Token-&gt; OptionCount</em> is 0.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> without any
option requested. OS side must capture the packet</p>
<p>sent from EUT side</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with some options and flag set to be active.</p>
<p>5. Then OS should capture ack and sends back the only one data
packet. The return status must be <strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.18</td>
<td>0x00450815, 0x41f5, 0x4da8, 0x90, 0x66, 0x78, 0x80, 0x94, 0x07,
0x34, 0xea</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> –When the passive client downloads, it
misses the first and the last data packet. Then server set the client to
be active while changing the transfer channel.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the second and the third data packet to the
multicast IP address while missing the first and the last data
packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 to ask for the
missing packets and the server should capture it.</p>
<p>7. If having captured the request, the server sends back OACK with
flag set to be active and the client’s listening port also changed. Then
the server should capture an error packet. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.19</td>
<td>0x9017244c, 0x127a, 0x486e, 0x81, 0x5b, 0x20, 0xe8, 0xa6, 0x55,
0xd4, 0x6f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_NOT_STARTED</strong> with the EFI MTFTPv4 Protocol driver
having not been started.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. The return status must be
<strong>EFI_NOT_STARTED.</strong></p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.20</td>
<td>0x84b13fab, 0x04f5, 0x474b, 0x89, 0x4c, 0x63, 0xef, 0x9d, 0xcf,
0x78, 0x58</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>Token</em> is
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>Token</em> is <strong>NULL</strong>. The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.21</td>
<td>0xd25ff5a4, 0x71e7, 0x4e38, 0xb4, 0x3e, 0x4a, 0xcc, 0xe7, 0x83,
0xfa, 0x77</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>Token</em>-&gt;<em>Filename</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>Token</em>-&gt;<em>Filename</em> is <strong>NULL</strong>. The
return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.22</td>
<td>0xf370c329, 0xe20b, 0x45a0, 0x9a, 0xb3, 0xd4, 0x13, 0x70, 0x98,
0x00, 0x03</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>Token</em>-&gt;
<em>OptionCount</em> is not 0 and <em>Token</em>-&gt;
<em>OptionList</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>Token</em>-&gt;<em>OptionCount</em> is not 0 and
<em>Token</em>-&gt;<em>OptionList</em> is <strong>NULL</strong>. The
return status must be <strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.23</td>
<td>0x2357c86f, 0xf9ba, 0x4f25, 0x9c, 0x77, 0x75, 0x10, 0xab, 0xb5,
0x10, 0x7e</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>Token</em>-&gt;<em>Buffer</em> and
<em>Token</em>-&gt;<em>CheckPacket</em> are both
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>Token</em>-&gt;<em>Buffer</em> and
<em>Token</em>-&gt;<em>CheckPacket</em> are both <strong>NULL</strong>.
The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.24</td>
<td>0x66019567, 0x321d, 0x41a8, 0xaa, 0xff, 0x60, 0x7f, 0x75, 0xa4,
0x08, 0x42</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>OverrideData</em>.GatewayIp is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>OverrideData</em>.GatewayIp is invalid.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.25</td>
<td>0x5f64495c, 0xad06, 0x4185, 0x87, 0x55, 0x86, 0xd9, 0x44, 0xf6,
0x39, 0x81</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>OverrideData</em>.ServerIp is invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>OverrideData</em>.ServerIp is invalid. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.26</td>
<td>0x17fa0734, 0x38f6, 0x4fe5, 0x9f, 0x6a, 0x5d, 0xae, 0x9e, 0xf2,
0xf3, 0xac</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>OverrideData</em>.GatewayIp is not in the same subnet with
<em>StationIp</em>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when
<em>OverrideData</em><strong>.</strong><em>GatewayIp</em> is not in the
same subnet with <em>StationIp</em>. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.27</td>
<td>0xa5d93fc4, 0x9b20, 0x45cc, 0xbe, 0x45, 0xcc, 0x60, 0x5e, 0x51,
0xae, 0xf4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_UNSUPPORTED</strong> when options of “restart” and “session”
in the <em>Token</em>-&gt;<em>OptionList</em> are in the unsupported
list of this implementation.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when options
of “restart” and “session” in the <em>Token</em>-&gt;<em>OptionList</em>
are in the unsupported list of this implementation. The return status
must be</p>
<p><strong>EFI_UNSUPPORTED</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.28</td>
<td>0x40f05e07, 0x3a7b, 0x4244, 0x97, 0x4f, 0x96, 0x9a, 0x89, 0x5c,
0xa4, 0x83</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_UNSUPPORTED</strong> when option of “pktdelay” in the
<em>Token</em>-&gt;<em>OptionList</em> are in the unsupported list of
this implementation.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> when option
of “pktdelay” in the <em>Token</em>-&gt;<em>OptionList</em> are in the
unsupported list of this implementation.The return status must be
<strong>EFI_UNSUPPORTED</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.29</td>
<td>0xa8d5abdf, 0x3e19, 0x462e, 0x9f, 0x6d, 0x9f, 0xa6, 0x13, 0xd2,
0x96, 0xd3</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> for calling
<strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> again before the first
call ends.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> for the first
time with all valid parameters.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> for the
second time with the same <em>Token</em> before the first call ends. The
return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.30</td>
<td>0xab02a8d2, 0x2086, 0x4372, 0xb5, 0xc7, 0x06, 0x0e, 0x28, 0x65,
0x1e, 0x8f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_BUFFER_TOO_SMALL</strong> when client is active and the
<em>BufferSize</em> is not larger enough to hold the downloaded data in
downloading process.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. Configure OS side to send back a normal OACK packet with multicast
option and flag set to be active. In addition, OS side should capture
Ack packet sent from EUT side and then responds with data packet whose
size is larger than the set <em>BufferSize</em>.</p>
<p>5. Then OS side should capture another packet.</p>
<p>The return status must be</p>
<p><strong>EFI_BUFFER_TOO_SMALL</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.31</td>
<td>0xf135f02b, 0x51ca, 0x47b9, 0xab, 0xf4, 0x4b, 0xd9, 0x78, 0x86,
0x68, 0xf8</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_BUFFER_TOO_SMALL</strong> when client is passive.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. Configure OS side to send back a normal OACK packet with
multicasts option and flag set to be passive and wait for the client's
processing.</p>
<p>5. OS side sends a data packet whose size is larger than the set
<em>BufferSize</em>. The return status must be
<strong>EFI_BUFFER_TOO_SMALL</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.32</td>
<td>0xb8363dd2, 0xedca, 0x49a6, 0xbe, 0x32, 0x90, 0x87, 0xb9, 0x57,
0x6a, 0x1f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_BUFFER_TOO_SMALL</strong> when calling <em>ReadFile</em>
asynchronously and Client is passive.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong>
asynchronously with all valid parameters. OS side must capture the
packet sent from EUT side.</p>
<p>4. Configure OS side to send back a normal OACK packet with option of
multicast and flag set to be passive and wait for the client's
processing.</p>
<p>5. OS side sends a data packet whose size is larger than the set
<em>BufferSize</em>. The return status must be
<strong>EFI_BUFFER_TOO_SMALL</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.33</td>
<td>0x5ae24123, 0xbb88, 0x42a5, 0xa1, 0xd0, 0xb3, 0x49, 0xfa, 0x20,
0x04, 0x6f</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_BUFFER_TOO_SMALL</strong> when the client is an active
client and the <em>BufferSize</em> is not larger enough to hold the
downloaded data in downloading process - return this status until having
received the last data block.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. Configure OS side to send back a normal OACK packet with multicast
option and flag set to be active. In addition, OS side should capture
Ack packet sent from EUT side and then responds with serious data
packets whose size are larger than the set <em>BufferSize</em>.</p>
<p>5. Then OS side should capture the ack for the data blocks except the
last block.</p>
<p>6. Then OS side should capture the error packet.</p>
<p>The return status must be</p>
<p><strong>EFI_BUFFER_TOO_SMALL</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.34</td>
<td>0xcfdaf47b, 0x8a46, 0x498c, 0x92, 0x0e, 0x96, 0x15, 0xc1, 0x23,
0xbe, 0x57</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the active download
process in <em>CheckPacket</em> callback routine in the case of
receiving data packets.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with
<em>CheckPacket</em> callback set. OS side must capture the packet sent
from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture an ack packet
sent from client.</p>
<p>5. If having captured it, server sends the only data packet back to
the client.</p>
<p>6. Then server should capture another packet and check that if it is
an error packet. The return status must be
<strong>EFI_ABORTED</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.35</td>
<td>0x731fb0ec, 0xb6b1, 0x4424, 0xb0, 0x61, 0x1b, 0xaa, 0xb3, 0x3f,
0xc0, 0x88</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the active download
process in <em>CheckPacket</em> callback routine in the case of
receiving OACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with
<em>CheckPacket</em> callback set. OS side must capture the packet sent
from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture another
packet and check whether it is an error packet. The return status must
be <strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.36</td>
<td>0xbd75e9f5, 0x76b3, 0x4e67, 0xb9, 0xbf, 0xcd, 0xfb, 0xed, 0x5c,
0x34, 0xa6</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the passive download
process in <em>CheckPacket</em> callback routine in the case of
receiving data packets.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with
<em>CheckPacket</em> callback set. OS side must capture the packet sent
from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive.</p>
<p>5. If having captured it, server sends the only data packet back to
the client.</p>
<p>6. Then server should capture another packet and check that if it is
an error packet. The return status must be
<strong>EFI_ABORTED</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.37</td>
<td>0xc9f2cdc8, 0x38eb, 0x4446, 0x9d, 0xc4, 0x5c, 0x78, 0x4a, 0x69,
0x0b, 0xd1</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the passive download
process in <em>CheckPacket</em> callback routine in the case of
receiving OACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with
<em>CheckPacket</em> callback set. OS side must capture the packet sent
from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive and then OS should capture another
packet and check that if it is an error packet.</p>
<p>The return status must be <strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.38</td>
<td>0xc911f1f0, 0x385b, 0x4de3, 0xb3, 0x86, 0xe3, 0x20, 0xec, 0x3c,
0xa8, 0xc2</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the active download
process in <em>TimeoutCallback</em> routine in the case of receiving
Ack.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with Timeout
callback set. OS side must capture the packet sent from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack. The
return status must be <strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.39</td>
<td>0xfd55be46, 0xb941, 0x4708, 0xbe, 0x69, 0x24, 0x82, 0xca, 0x2c,
0x29, 0x34</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the passive download
process in Timeout Callback routine in the case of receiving Ack.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with Timeout
callback set. OS side must capture the packet sent from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive and then OS should capture ack. The
return status must be <strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.40</td>
<td>0x8ad083d8, 0x9757, 0x40ef, 0x99, 0x86, 0x21, 0xee, 0x90, 0x4a,
0xa0, 0x2d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server sends back with normal OACK
packet whose active flag is set.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back the only data packet and
then receives another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.41</td>
<td>0xc3640c29, 0xbfcd, 0x4f0c, 0xae, 0x7e, 0xcc, 0x44, 0x8a, 0xc1,
0x8e, 0x16</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when server send backs with normal OACK
packet whose passive flag is set.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive and stall to wait for the client to
join in the multicast group.</p>
<p>5. OS sends back the only data packet. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.42</td>
<td>0x5e294d5a, 0xf09e, 0x4fdc, 0xa2, 0x2e, 0x9d, 0xcb, 0xfa, 0x44,
0x3d, 0x2b</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server sends back normal OACK
packet after the client resends RRQ several times.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters, client should retry 5 times to send RRQ then OS side
should capture the packet sent from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back the only data packet and
then receives another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.43</td>
<td>0x162e4457, 0x63d9, 0x4402, 0xad, 0xac, 0xaa, 0xdf, 0x3a, 0x61,
0xaf, 0xdc</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server doesn’t copy the client’s
option strings verbatim from the RRQ packet to the OACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active while not coping the client’s option
strings verbatim from the RRQ packet to the OACK packet; then OS should
capture ack packet.</p>
<p>5. If having captured ack, OS sends back the only data packet and
then receives another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.44</td>
<td>0xe0d3922c, 0x017d, 0x44a2, 0x90, 0x88, 0xad, 0xb6, 0xeb, 0x9f,
0x4c, 0xed</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when client receives an error server source
port data packet, it just ignores the packet and continues the data
processing.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active; then OS should capture ack packet.</p>
<p>5. If having captured ack, OS sends back an error server source data
packet. In addition, client just ignores it.</p>
<p>6. The server sends back another correct source data packet then. The
return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.45</td>
<td>0xcc4f141c, 0x9df1, 0x404e, 0x90, 0x27, 0x60, 0xea, 0xbd, 0xa8,
0x08, 0xd8</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> After passive client having received some
packets, the server sets it to be active and sends out remaining
packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK to set the client passive.</p>
<p>5. If having captured ack0, OS sends back the first and the last data
packet.</p>
<p>6. Server resends an empty multicast OACK to set the client
active.</p>
<p>7. If having captured ack, OS sends out remain packet. The return
status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.46</td>
<td>0x2d4d9962, 0x24ac, 0x4f62, 0x9b, 0x66, 0x3c, 0xa5, 0xf3, 0x67,
0xb3, 0xa0</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when server doesn’t support option
extension and just sends back the data packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If having captured the packet, OS side sends back the only one
data packet then receives another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.47</td>
<td>0x9e9e85f5, 0x669d, 0x4de3, 0x82, 0xa4, 0xff, 0x96, 0xb9, 0x69,
0x79, 0x05</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server doesn’t support multicast
option and just doesn’t support multicast.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
an OACK without multicast option only and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back the only one data packet
then receives another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.48</td>
<td>0x0bdc47fc, 0x659e, 0x497f, 0x8d, 0x10, 0x10, 0x52, 0xd3, 0x95,
0x7d, 0x19</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client continuously joins the
group to download file, while the Active flag is set.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Do the step of 4,5,6 for 5 times:</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>5. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>6. If having captured ack, OS sends back the only data packet and
then receives another ack.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.49</td>
<td>0xc965cbdf, 0x1539, 0x4507, 0xb0, 0xd1, 0x4f, 0xcd, 0x17, 0xc4,
0xbb, 0x54</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server sends back the Data with
incorrect sequence of the block numbers.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back data packets with incorrect
sequence of block numbers and then receives another ack. The return
status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.50</td>
<td>0xcf00a8ae, 0x8676, 0x4ee3, 0xb5, 0xcc, 0x82, 0x22, 0xf9, 0x46,
0x94, 0x03</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server sends back the Data after
some packets' retransmission.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, server send backs the Number1 data packet
and then receive another ack.</p>
<p>6. Then server doesn’t do anything until having received the fourth
ack. Then it sends the rest data packets back. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.51</td>
<td>0x21a80b34, 0x73b3, 0x47ba, 0x82, 0x0c, 0x37, 0x34, 0x43, 0x7e,
0xd5, 0xd4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when client downloads a file with length
equal to 1 byte.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back the only data packet with
length equal to 1 byte and then receives another ack. The return status
must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.52</td>
<td>0x9e8004a9, 0xc28c, 0x461b, 0x84, 0xa1, 0x31, 0xca, 0xc6, 0x48,
0x31, 0x28</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when using <em>OverrideData</em> to replace
the configuration data and retry counter is set to 0 in override
data.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with
<em>OverrideData</em> replacing the configuration data and retry counter
set to 0 in override data. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active and then OS should capture ack
packet.</p>
<p>5. If having captured ack, OS sends back the only data packet with
length equal to 1 byte and then receives another ack. The return status
must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.53</td>
<td>0x9bd82567, 0x6249, 0x4635, 0xb0, 0x2d, 0xf8, 0x06, 0x0d, 0x26,
0x68, 0xa6</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when active client receives data packets
after server sends back OACK packet twice.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active; then OS should capture ack packet.</p>
<p>5. If having captured ack, OS send backs another OACK with the same
option. Then sends back the only data packet and then receives another
ack.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.54</td>
<td>0xcf35445d, 0x0aa1, 0x4485, 0x8e, 0xb6, 0x5f, 0xd8, 0xb4, 0x65,
0x55, 0x84</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client is passive and it receives
unexpected packets (BlockNo is a former number).</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive.</p>
<p>5. Then OS doesn’t sends back all the data packets in sequence. The
return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.55</td>
<td>0x62908d19, 0xc308, 0x4f16, 0xa1, 0x70, 0xb6, 0x9a, 0xdf, 0x47,
0xb4, 0x72</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client is passive and it receives
unexpected packets (BlockNo is a further number).</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be passive.</p>
<p>5. Then OS doesn’t sends back all the data packets in sequence. The
return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.56</td>
<td>0x58c614fb, 0x51d9, 0x4043, 0xb1, 0x24, 0x95, 0xa3, 0x7c, 0xcd,
0x3d, 0x70</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server responds data packet with
data length larger than blocksize.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
OACK with flag set to be active. In addition, OS should capture an
ack.</p>
<p>5. If having captured it, OS sends back the first data packet with
length larger than blocksize, then the rest data packet.</p>
<p>6. OS should capture ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.57</td>
<td>0x23a7aebe, 0x0117, 0x44fc, 0x9d, 0xcc, 0x68, 0x4c, 0xa6, 0x31,
0x2a, 0x20</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client receives an unexpected ACK
packet in the case of downloading file.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
an unexpected ACK and a normal OACK with flag set to be active.</p>
<p>5. Then if OS side has captured the ack, OS side sends back the only
data packet.</p>
<p>6. OS should capture another ack. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.58</td>
<td>0x9df88b27, 0x0a20, 0x4d91, 0x98, 0x2b, 0x32, 0x26, 0x41, 0x62,
0x39, 0x44</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the active client receives an
unexpected OACK packet in the case of downloading file.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be active.</p>
<p>5. If OS side has captured the ack, OS side send backs OACK
again.</p>
<p>6. The server should capture another ack. Then the server sends the
only data packet back to the client. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.59</td>
<td>0xad60cb28, 0x6451, 0x400a, 0xa5, 0x74, 0xf6, 0x35, 0x9f, 0x01,
0x92, 0xd3</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client receives an
unexpected OACK packet in the case of downloading file.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the first data packet to the multicast IP
address and another OACK to the client again.</p>
<p>6. Then the server sends the last data packet back to the multicast
IP address. The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.60</td>
<td>0x2309b8ea, 0x5593, 0x4835, 0xb6, 0x24, 0x65, 0xda, 0xc5, 0x51,
0x04, 0x5d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the last data packet. After client is timeout, server sets client
to be passive again and sends out the lost packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the first three data packets to the
multicast IP address while missing the last data packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 to ask for
missing packets and the server should capture it.</p>
<p>7. If having captured the request, the server sends OACK back again
and then the last data packet.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.61</td>
<td>0xf6c81b41, 0x8edd, 0x46df, 0x8a, 0x82, 0x46, 0x40, 0xd9, 0x8b,
0xda, 0xa5</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the last data packet. After client is timeout, server sets client
to be passive again and sends out all the data packets.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the first three data packets to the
multicast IP address while missing the last data packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 and the server
should capture it.</p>
<p>7. If having captured the request, the server sends OACK back again
and then all the data packets.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.62</td>
<td>0x7156d37f, 0xd7ef, 0x47ea, 0xa2, 0xf3, 0x64, 0x3e, 0x7c, 0x44,
0x9f, 0x65</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the first and the last packet. After client is timeout, server
sets client to be passive again and sends out the lost packet</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the second and the third data packet to the
multicast IP address while missing the first and the last data
packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 and the server
should capture it.</p>
<p>7. If having captured the request, the server sends OACK back again
and then all the lost packets.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.63</td>
<td>0x34753378, 0xb423, 0x40b1, 0x93, 0x7c, 0x4d, 0xaa, 0x5c, 0xa6,
0x63, 0x43</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the first and the last packet. After client is timeout, server
sets client to be passive again and sends out all the data packets.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the second and the third data packet to the
multicast IP address while missing the first and the last data
packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 and the server
should capture it.</p>
<p>7. If having captured the request, the server sends OACK back again
and then all the packets.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>8. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.64</td>
<td>0xd756be67, 0xd667, 0x432f, 0xbb, 0xd6, 0x3a, 0xe1, 0xf5, 0xe6,
0x61, 0xd1</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the first and the last packet. After client is timeout, server
sets client to be active again and sends out the missing packets.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the second and the third data packet to the
multicast IP address while missing the first and the last data
packet.</p>
<p>6. After passive client is timeout, it’ll send ack0 to ask for the
missing packets.</p>
<p>7. If having captured the request, the server sends back OACK with
flag set to be active and then the first data packet.</p>
<p>8. The server expects the ack packet to request the last packet. If
having captured it, server will send the last data packet. The return
status must be <strong>EFI_SUCCESS</strong>.</p>
<p>9. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.65</td>
<td>0xc0fc889f, 0xc91f, 0x4a41, 0x80, 0x59, 0x0e, 0x22, 0x56, 0x79,
0x0b, 0x53</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses two blocks of packets. After client is timeout, server sets
client to be passive again and sends out the lost packets randomly.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the first and the seventh data packet to
the multicast IP address while missing the Number2, 3, 4, 5, 6, 8 data
packets.</p>
<p>6. After passive client is timeout, it’ll send ack0 and the server
should capture it.</p>
<p>7. If having captured the ack0 packet, the server sends back OACK
with flag set to be passive. Then it sends out the data packets randomly
in the order Number4, 2, 6, 3, 5, 8.</p>
<p>8. The server expects the ack packet. If having captured, server will
send the second data packet.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>9. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.66</td>
<td>0x5a4ed7d1, 0x0e36, 0x4f9c, 0xa7, 0x9c, 0xf2, 0x35, 0x2e, 0xf7,
0x3b, 0x2d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the passive client downloads, it
misses the first and the last packets. Then server changes the client to
be active and retrieves its unicast transfer model.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all
valid parameters. OS side must capture the packet sent from EUT
side.</p>
<p>4. If OS side has captured the packet, configure server to send back
a normal OACK with flag set to be passive.</p>
<p>5. Then server sends back the second and the third data packets to
the multicast IP address while missing the first and the last data
packets.</p>
<p>6. After passive client is timeout, it’ll send ack0 and the server
should capture it.</p>
<p>7. If having captured the request, the server sends back OACK with
transfer mode changed to be unicast and flag set to be active. Then it
expects the ack sent from the client and sends out the first data
packet.</p>
<p>8. The server should capture the ack and then sends back the second
packet.</p>
<p>9. As above, server sends the third and the last data packets. The
return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>10. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.67</td>
<td>0xb441ee5b, 0xbf7f, 0x446f, 0xa2, 0x5c, 0x77, 0x7a, 0x0b, 0xdd,
0xde, 0x78</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - to test the
<strong>EFI_ICMP_ERROR</strong> conformance of
<strong>ReadFile()</strong> with an ICMP ERROR packet being
received.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> and OS side
capture the packet sent from EUT side.</p>
<p>4. If OS side has captured the packet, configure server to send back
an ICMP error packet. The return status must be
<strong>EFI_ICMP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.68</td>
<td>0x6eaabf78, 0x3914, 0x4d08, 0x85, 0x0c, 0xbf, 0x63, 0x6d, 0xe9,
0xf3, 0x55</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> - to test the
<strong>EFI_INVALID_PARAMETER</strong> conformance of
<strong>ReadFile()</strong> when one or more options in
<em>Token.OptionList</em> have wrong format.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with invalid
muticast option value. The return status must be
<strong>EFI_INVALID_PARAMETER.</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.69</td>
<td>0xd5e062fc, 0x5c0f, 0x470c, 0x8b,0x7a,0x44,0xf7, 0xbc,0xad,
0xc6,0x9c</td>
<td><p><strong>EFI_MTFTP4_PROT</strong></p>
<p><strong>OCOL.ReadFile()</strong>- <strong>ReadFile()</strong> must
return <strong>EFI_NETWORK_UNREACHABLE</strong> when receive an ICMP
network unreachable packet.</p></td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create</p>
<p>a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.Configur</strong></p>
<p><strong>e()</strong> with all valid parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP network unreachable packet and the return status should be
<strong>EFI_NETWORK_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created</p>
<p><strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.70</td>
<td>0x6d8a5555, 0xe632, 0x470e, 0x98,0xe5,0x61,0xd2,0x2e,0xc9,
0x0d,0x0d</td>
<td><p><strong>EFI_MTFTP4_PROT</strong></p>
<p><strong>OCOL.ReadFile()</strong></p>
<p>- <strong>ReadFile()</strong> must return</p>
<p><strong>EFI_HOST_UNREACHABLE</strong> when receive an ICMP host
unreachable packet.</p></td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create</p>
<p>a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.ReadFile</strong></p>
<p><strong>()</strong> with all valid parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP host unreachable packet and the return status should be
<strong>EFI_HOST_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong>
child</p>
<p>handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.71</td>
<td>0x732738e8, 0x1ff1, 0x4f3a, 0xa0,0xc8,
0x38,0x81,0x1d,0x15,0x92,0x83</td>
<td><p><strong>EFI_MTFTP4_PROT</strong></p>
<p><strong>OCOL.ReadFile()</strong></p>
<p>- <strong>ReadFile()</strong> must return
<strong>EFI_PROTOCOL_UNREACHABLE</strong> when receive an ICMP protocol
unreachable packet.</p></td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create</p>
<p>a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an ICMP protocol unreachable
packet and the return status should be
<strong>EFI_PROTOCOL_UNREACHABLE</strong>.</p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
to</p>
<p>destroy the newly created</p>
<p><strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.7.72</td>
<td>0xd1c4e1e8, 0x1099, 0x4646, 0xb7,0xc9, 0x64,0x7e, 0x65,0xc3,
0x82,0x30</td>
<td><p><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong>-
<strong>ReadFile()</strong> must return</p>
<p><strong>EFI_PORT_UNREACHABLE</strong> when receive an ICMP port
unreachable packet.</p></td>
<td><p>1. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all valid
parameters.</p>
<p>3. Call</p>
<p><strong>EFI_MTFTP4_PROTOCOL.ReadFile()</strong> with all valid
parameters. OS side</p>
<p>should capture the packet sent from</p>
<p>EUT side.</p>
<p>4. Configure Host side to send back an</p>
<p>ICMP port unreachable packet and the return status should be
<strong>EFI_PORT_UNREACHABLE.</strong></p>
<p>5. Call</p>
<p><strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong>
to destroy the newly created</p>
<p><strong>EFI_MTFTP4_PROTOCOL</strong> child</p>
<p>handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### WriteFile()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.8.1</td>
<td>0x4b00df17, 0xc244, 0x413d, 0x8e, 0xbf, 0xe8, 0x7e, 0x10, 0x9a,
0xa8, 0xd4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>Token</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with a
<em>Token</em> value of <strong>NULL</strong>. The return status must be
<strong>EFI_NVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.2</td>
<td>0xddc80d3b, 0x448d, 0x4ef9, 0xab, 0x74, 0x88, 0x47, 0xa7, 0xc9,
0x7c, 0xa8</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em>Token</em>-&gt;<em>Filename</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
<em>Token</em>-&gt;<em>Filename</em> value of <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.3</td>
<td>0x97304d43, 0x1101, 0x4b76, 0x90, 0x70, 0x66, 0x85, 0x62, 0x9e,
0xb3, 0xa3</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>Token</em>-&gt;
<em>OptionCount</em> is not 0 and <em>Token</em>-&gt;<em>OptionList</em>
is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> when
<em>Token</em>-&gt; <em>OptionCount</em> is not 0 and
<em>Token</em>-&gt;<em>OptionList</em> is <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.4</td>
<td>0xf061683f, 0xb39e, 0x42af, 0x92, 0x86, 0x9f, 0x18, 0xcc, 0xc7,
0xc0, 0x8d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when both
<em>Token</em>-&gt;<em>Buffer</em> and <em>Token</em>-&gt;
<em>PacketNeeded</em> are <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> when both
<em>Token</em>-&gt;<em>Buffer</em> and <em>Token</em>-&gt;
<em>PacketNeeded</em> are <strong>NULL</strong>. The return status must
be <strong>EFI_NVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.5</td>
<td>0xa2d02347, 0x9410, 0x49b3, 0xa9, 0xd2, 0xd7, 0x1a, 0xf4, 0xc5,
0xa7, 0x34</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<strong>OverrideData.GatewayIp</strong> value of invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with an
<strong>OverrideData.GatewayIp</strong> value of invalid. The return
status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment..</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.6</td>
<td>0xe8f09c7b, 0x2cf3, 0x482e, 0x93, 0xc6, 0x4f, 0x45, 0x85, 0x3a,
0x43, 0x0c</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<strong>OverrideData.ServerIp</strong> value of invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with an
<em>OverrideData</em><strong>.</strong><em>ServerIp</em> value of
invalid. The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.7</td>
<td>0x069921c9, 0x8f37, 0x45b6, 0xa4, 0x98, 0xa3, 0x2f, 0xc9, 0xb5,
0x8d, 0x50</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<strong>OverrideData.GatewayIp</strong> is not in the same subnet with
<em>StationIp</em>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> when
<strong>OverrideData.GatewayIp</strong> is not in the same subnet with
<em>StationIp</em>. The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.8</td>
<td>0xb95d36a6, 0x091e, 0x444b, 0x9d, 0xd7, 0x30, 0x4c, 0x9e, 0x59,
0xab, 0x81</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the EFI MTFTPv4 Protocol driver
having not been started.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters. The return status must be
<strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.9</td>
<td>0x67021dd5, 0xf97d, 0x4783, 0x8d, 0xe2, 0x93, 0x6e, 0x6c, 0x5a,
0xe5, 0xeb</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_ACCESS_DENIED</strong> when calling
<strong>EFI_MTFTP4_PROTOCOL.WriteFile</strong> again before the first
call ends.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> for the
first time with all valid parameters.</p>
<p>4. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> for the
second time with the same <em>Token</em> before the first call ends. The
return status must be <strong>EFI_ACCESS_DENIED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.10</td>
<td>0x4a445105, 0xf332, 0x4251, 0xb1, 0x5c, 0x10, 0x5c, 0x27, 0xeb,
0x67, 0x09</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_UNSUPPORTED</strong> when one or more options in the
<em>Token</em>-&gt;<em>OptionList</em> are in the unsupported list for
this implementation.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> when one or
more options in the <em>Token</em>-&gt;<em>OptionList</em> are in the
unsupported list for this implementation. The return status must be
<strong>EFI_UNSUPPORTED</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.11</td>
<td>0x00ee8108, 0xb8ce, 0x4428, 0x9a, 0x58, 0x3c, 0xf3, 0x33, 0x3e,
0xf4, 0x9a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_TFTP_ERROR</strong> when the client receives an MTFTPv4
ERROR packet during uploading.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, send a normal OACK to the client.</p>
<p>5. Then OS side should capture the data packets. If having captured,
OS side sends an error packet back. The return status must be
<strong>EFI_TFTP_ERROR</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.12</td>
<td>0x0b05148f, 0x4f07, 0x413d, 0x8e, 0x47, 0x99, 0xbe, 0xac, 0x25,
0xc3, 0x4d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_ICMP_ERROR,</strong> when server sends back an ICMP error
packet, client should terminate the session.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds an ICMP error packet. The return status must
be <strong>EFI_ICMP_ERROR</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.13</td>
<td>0x26ac0f66, 0x2fa1, 0x4e91, 0x93, 0x14, 0xfe, 0x0f, 0x86, 0x93,
0x47, 0x4d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the upload process in
<em>CheckPacket</em> callback routine</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
<em>CheckPacket</em> callback set.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK. The return status must be
<strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.14</td>
<td>0x105a5b0c, 0x72cb, 0x4854, 0x95, 0xdd, 0x86, 0xd7, 0x28, 0x0d,
0xa6, 0x12</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the upload process in
TimeoutCallback callback routine</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
TimeoutCallback callback set.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK. The return status must be
<strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.15</td>
<td>0xcaeef509, 0x3240, 0x4675, 0xa2, 0x50, 0x0b, 0xaf, 0xb5, 0x5a,
0xcb, 0x16</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_ABORTED</strong> when the user aborts the upload process in
PacketNeeded callback routine</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
PacketNeeded callback set.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK. The return status must be
<strong>EFI_ABORTED</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.25</td>
<td>0xb76d5034, 0xbee6, 0x468a, 0xa1, 0xf2, 0xc6, 0x9f, 0x20, 0x0d,
0xa6, 0xae</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - to test the
<strong>EFI_INVALID_PARAMETER</strong> conformance of
<strong>WriteFile</strong> when one or more options in
<em>Token.OptionList</em> have wrong format.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with invalid
timeout option value. The return status must be
<strong>EFI_INVALID_PARAMETER</strong></p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.16</td>
<td>0xcc7a5aad, 0xe6ec, 0x4fa7, 0x97, 0x0a, 0xac, 0x30, 0xd6, 0x39,
0x20, 0x16</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the user uploads a packet with data
less than one block.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
<em>BufferSize</em> set to 100.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and respond ACK.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.17</td>
<td>0x2649936f, 0x161c, 0x40c2, 0xa8, 0x53, 0xc0, 0xa4, 0xa3, 0x2e,
0xf2, 0x62</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the user uploads a packet with data
length equal to 1 byte.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
<em>BufferSize</em> set to 1.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and respond with an ACK packet. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.18</td>
<td>0xbcbec9fd, 0x00d8, 0x494d, 0xa4, 0xff, 0x86, 0x98, 0xc4, 0xb0,
0x6a, 0x5a</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the user uploads a packet with
override configuration data.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with
override configuration data.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds a normal OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and respond with an ACK packet. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.19</td>
<td>0x741101e7, 0x7888, 0x4bd8, 0xa2, 0xcb, 0x1d, 0xec, 0xb1, 0x34,
0x66, 0x31</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server responds with an incorrect
ack packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds an OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and responds with an incorrent ACK to the incorrect packet number
followed by a correct ACK. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.20</td>
<td>0xa3c22b82, 0x5f14, 0x4419, 0x8f, 0xc6, 0xd7, 0x89, 0x88, 0xa9,
0x88, 0xe9</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server responds WRQ with an ACK
instead of OACK, so client sends data packet to server.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds with an ACK instead of an OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and respond with an ACK to this packet. The return status must be
<strong>EFI_SUCCESS.</strong></p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.21</td>
<td>0x20787b06, 0x8766, 0x4ced, 0xb0, 0x25, 0x65, 0xfa, 0xf1, 0xd3,
0x6c, 0x7c</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server replies WRQ with an invalid
BlockNo ACK instead of OACK, client should ignore this packet and
continue the normal process.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds with an invalid BlockNo ACK instead of an
OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and responds with an ACK to this packet. The return status must
be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.22</td>
<td>0xf549a91c, 0x9d15, 0x45c7, 0xb2, 0xed, 0xa6, 0x7e, 0xff, 0x08,
0xc0, 0xf4</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the server replies DATA packet with an
error ACK ( <em>BufferLen &lt; sizeof(UINT16))</em> instead of OACK,
client should ignore this packet and continue the normal process.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds with a normal OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and replies with an error ACK ( <em>BufferLen &lt;
sizeof(UINT16))</em> and a correct ACK , client should ignore this error
ACK and continue the normal process.</p>
<p>The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.8.23</td>
<td>0x9ee2172f, 0xb96e, 0x4d13, 0x9e, 0x6c, 0xbd, 0x27, 0x44, 0x95,
0xee, 0xc6</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client receives an unexpected OACK
when waiting for ACK packet during uploading file.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds with ACK.</p>
<p>5. The server should capture the only data packet sent from the
client and respond with an unexpected OACK and an ACK to this packet.
The return status must be <strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.8.24</td>
<td>0x434974c8, 0x5f8c, 0x46d8, 0x89, 0x57, 0x4e, 0x03, 0xff, 0xfa,
0xa3, 0xc5</td>
<td><strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> - returns
<strong>EFI_SUCCESS</strong> when the client receives an error server
source port ACK in the case of waiting for ACK packet.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.WriteFile()</strong> with all
valid parameters.</p>
<p>4. The server should capture the write request. If having captured
the packet, server responds with a normal OACK.</p>
<p>5. The server should capture the only data packet sent from the
client and replies with an error server source port ACK and a correct
ACK for the packet; client should ignore this error ACK and continue the
normal process. The return status must be
<strong>EFI_SUCCESS</strong>.</p>
<p>6. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### ReadDirectory()

<table>
<colgroup>
<col style="width: 16%" />
<col style="width: 18%" />
<col style="width: 24%" />
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
<td>5.26.2.9.1</td>
<td>0xc9e02ded, 0x0e98, 0x4162, 0x8d, 0x4c, 0x14, 0x58, 0xd0, 0x6a,
0xc7, 0xab</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a <em>Token</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with a
<em>Token</em> value of <strong>NULL</strong>. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p><strong>4.</strong> Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.2</td>
<td>0x120fa0f3, 0xad22, 0x4d39, 0xb9, 0x00, 0xe5, 0x60, 0xdd, 0x8f,
0xe3, 0xb2</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em>Token</em>-&gt;<em>Filename</em> value of
<strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with a
<em>Token</em>-&gt;<em>Filename</em> value of <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.9.3</td>
<td>0xe6339187, 0x07d0, 0x467f, 0x9b, 0x89, 0x5b, 0xf5, 0x6c, 0x2d,
0xf8, 0xe0</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when <em>Token</em>- &gt;
<em>OptionCount</em> is not 0 and <em>Token</em>-&gt;
<em>OptionList</em> is <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> when
<em>Token</em>- &gt;<em>OptionCount</em> is not 0 and
<em>Token</em>-&gt; <em>OptionList</em> is <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.4</td>
<td>0xc39cb583, 0x3fa4, 0x4c7f,0x9a, 0x93, 0xa5, 0xf9, 0x30, 0xf0, 0x42,
0x6c</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when both
<em>Token</em>-&gt;<em>Buffer</em> and
<em>Token</em>-&gt;<em>CheckPacket</em> are <strong>NULL</strong>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> when
both <em>Token</em>-&gt;<em>Buffer</em> and
<em>Token</em>-&gt;<em>CheckPacket</em> are <strong>NULL</strong>.</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.9.5</td>
<td>0xaf58aaf5, 0x3cd0, 0x47aa, 0x8b, 0x93, 0x4f, 0x7b, 0x8b, 0xe8,
0x4d, 0xf1</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<em>OverrideData</em>.GatewayIp value of invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with an
<em>OverrideData</em><strong>.GatewayIp</strong> value of invalid. The
return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.6</td>
<td>0x7044e68a, 0x6ca9, 0x4b23, 0x9a, 0x50, 0x91, 0x85, 0x34, 0xa3,
0xca, 0xfb</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> with an
<em>OverrideData</em>.ServerIp value of invalid.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with an
<em>OverrideData</em><strong>.ServerIp</strong> value of invalid. The
return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.9.7</td>
<td>0x8bd21805, 0xec3c, 0x4041, 0xa4, 0xe4, 0x75, 0xf1, 0xa4, 0xec,
0xae, 0x4d</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_INVALID_PARAMETER</strong> when
<em>OverrideData</em>.GatewayIp is not in the same subnet with
<em>StationIp</em>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> for
<em>OverrideData</em>.GatewayIp is not in the same subnet
with<em>StationIp</em> .</p>
<p>The return status must be</p>
<p><strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.8</td>
<td>0x7ecf38c4, 0x4fc5, 0x4663, 0xa4, 0xc4, 0xc0, 0x48, 0x45, 0xfe,
0x59, 0x6b</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_NOT_STARTED</strong> while the EFI MTFTPv4 Protocol driver
having not been started.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with all
valid parameters.</p>
<p>The return status must be <strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.9.9</td>
<td>0x31599521, 0xb38b, 0x47c8, 0xa6, 0x39, 0xaf, 0x50, 0xe3, 0x30,
0xbe, 0x87</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_UNSUPPORTED</strong> when one or more options in the a
<em>Token</em>-&gt;<em>OptionList</em> value of in the unsupported list
of this implementation.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with one
or more options in the a <em>Token</em>-&gt;<em>OptionList</em> value of
in the unsupported list of this implementation.</p>
<p>The return status must be <strong>EFI_UNSUPPORTED</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.10</td>
<td>0xefc6d249, 0x179f, 0x49a2, 0x96, 0x1c, 0x0d, 0x90, 0xe7, 0x79,
0x4c, 0xcb</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_ICMP_ERROR</strong> when the server responds with an ICMP
error packet, client should terminate the session.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with all
valid parameters.</p>
<p>4. If OS side has captured the request, it sends out an ICMP error
packet.</p>
<p>The return status must be <strong>EFI_ICMP_ERROR</strong>.</p>
<p>5. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.9.12</td>
<td>0xab9bacfb, 0x79ee, 0x41e5, 0xb9, 0xe9, 0x40, 0x31, 0x7a, 0xf1,
0xcc, 0x64</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - test the
<strong>EFI_INVALID_PARAMETER</strong> conformance of
<strong>ReadDirectory()</strong> when one or more options in
<em>Token.OptionList</em> have wrong format.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with
invalid timeout option value. The return status must be
<strong>EFI_INVALID_PARAMETER</strong>.</p>
<p>4. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
<tr class="odd">
<td>5.26.2.9.11</td>
<td>0x968731a3, 0x01e8, 0x44d7, 0xad, 0xba, 0x70, 0x88, 0x80, 0x8c,
0x99, 0xe1</td>
<td><strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> - returns
<strong>EFI_SUCCESS</strong> - read a list of files on the MTFTPv4
server that are logically (or operationally) related to
<em>Token</em>-&gt;<em>FileName</em>.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Configure()</strong> with all
valid parameters.</p>
<p>3. Call <strong>EFI_MTFTP4_PROTOCOL.ReadDirectory()</strong> with all
valid parameters.</p>
<p>4. If OS side has captured the request, it sends out a normal
OACK.</p>
<p>5. Then OS side should capture the ack from the client and send back
the only data packet.</p>
<p>6. Then OS side expects another ack.</p>
<p>The return status must be <strong>EFI_ICMP_ERROR</strong>.</p>
<p>7. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>



### Poll()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>5.26.2.10.1</td>
<td>0x57e97972, 0xa7a3, 0x4647, 0x95, 0x9a, 0x23, 0x29, 0x5b, 0x81,
0x2c, 0xfe</td>
<td><strong>EFI_MTFTP4_PROTOCOL.Poll()</strong> - returns
<strong>EFI_NOT_STARTED</strong> when the EFI MTFTPv4 Protocol driver
having not been started.</td>
<td><p>1. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild()</strong> to
create a new <strong>EFI_MTFTP4_PROTOCOL</strong> child handle.</p>
<p>2. Call <strong>EFI_MTFTP4_PROTOCOL.Poll()</strong> with all valid
parameters. The return status must be
<strong>EFI_NOT_STARTED</strong>.</p>
<p>3. Call
<strong>EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild()</strong> to
destroy the newly created <strong>EFI_MTFTP4_PROTOCOL</strong> child
handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>


## EFI_UDP6_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_UDP6_PROTOCOL Section.

### CreateChild()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.26.3.1.1 | 0x1d3e7323, 0x5a46, 0x4fe3, 0xbf, 0x9d, 0x0a, 0xb8, 0xb1, 0xfd, 0xe7, 0x92 | **EFI_UDP6_SERVICE_BINDING_PROTOCOL.CreateChild() - CreateChild()** returns **EFI_INVALID_PARAMETER** with a **NULL** *ChildHandle*. | Call **CreateChild()** with a **NULL** *ChildHandle*, the return status should be **EFI_INVALID_PARAMETER.** |
| 5.26.3.1.2 | 0x8872614e, 0x51d5, 0x434d, 0xb8, 0x71, 0x20, 0x30, 0x4f, 0xbe, 0x04, 0x92 | **EFI_UDP6_SERVICE_BINDING_PROTOCOL.CreateChild() - CreateChild()** returns **EFI_SUCCESS** with a valid *ChildHandle*. | Call **CreateChild()** with a valid *ChildHandle*, the return status should be **EFI_SUCCESS.** |


### DestoryChild()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.26.3.2.1 | 0x25c39b09, 0xba61, 0x49f3, 0xa3, 0x58, 0x98, 0x11, 0x17, 0xd8, 0x14, 0x0e | **EFI_UDP6_SERVICE_BINDING_PROTOCOL.DestoryChild() - DestoryChild()** returns **EFI_INVALID_PARAMETER** with a **NULL** *ChildHandle*. | Call **DestoryChild()** with a **NULL** *ChildHandle*, the return status should be **EFI_INVALID_PARAMETER.** |
| 5.26.3.2.2 | 0x1e938ebd, 0x425a, 0x4eb6, 0xbd, 0x12, 0x9c, 0xa2, 0xdc, 0xc4, 0x0b, 0x4c | **EFI_UDP6_SERVICE_BINDING_PROTOCOL.DestoryChild() - DestoryChild()** returns **EFI_SUCCESS** with a valid *ChildHandle*. | Call **DestoryChild()** with a valid *ChildHandle*, the return status should be **EFI_SUCCESS.** |


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
<td>5.26.3.3.1</td>
<td>0x920b75d9, 0xba94, 0x4e72, 0xb0, 0x4d, 0x77, 0xe5, 0x81, 0xe7,
0xcf, 0x91</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_NOT_STARTED</strong> with a not configured
<em>ChildHandle</em></td>
<td>Call <strong>GetModeData()</strong> with a not configured
<em>ChildHandle</em>, the return status should be
<strong>EFI_NOT_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.3.2</td>
<td>0x1a823790, 0xcaec, 0x413d, 0xbc, 0xf3, 0xe7, 0xfa, 0x70, 0xdf,
0x87, 0x6d</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters</td>
<td><p>5.26.3.3.2 to 5.26.3.3.4 belong to one case</p>
<p>1. Call <strong>GetModeData()</strong> with valid parameters, the
return status should be <strong>EFI_ SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.3.3.3</td>
<td>0xdb72ffca, 0xd3d9, 0x4837, 0x8f, 0x39, 0xf9, 0x67, 0x2e, 0x9d,
0x93, 0xab</td>
<td>Validate the <em>IP6ModeData.IsConfigured</em></td>
<td>2. The value of <em>IP6ModeData.IsConfigured</em> should be
<strong>TRUE</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.3.3.4</td>
<td>0x923aecf2, 0xcfc6, 0x4497, 0x8c, 0x49, 0xe6, 0x74, 0x1c, 0x60,
0xc7, 0x66</td>
<td>Validate the <em>Udp6ConfigData</em></td>
<td>3. The value of <em>Udp6ConfigData</em> should be same with the
assigned configure data.</td>
</tr>
</tbody>
</table>


### Configure()

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
<td>5.26.3.4.1</td>
<td>0x1c36e6e8, 0xf453, 0x41bb, 0x84, 0x6f, 0x0a, 0x67, 0x91, 0xa6,
0xe5, 0xe7</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em>UdpConfigData.StationAddress</em> being neither zero nor one of the
configured IP addresses in the underlying IPv6 driver</td>
<td>Call <strong>Configure()</strong> with a
<em>UdpConfigData.StationAddress</em> being neither zero nor one of the
configured IP addresses in the underlying IPv6 driver, the return status
should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.4.2</td>
<td>0xef302465, 0x7ec6, 0x4652, 0xbb, 0xf0, 0x62, 0x73, 0xa5, 0x5a,
0xd5, 0x52</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a
<em>UdpConfigData.RemoteAddress</em> being an invalid unicast IPv6
address if it is not zero.</td>
<td>Call <strong>Configure()</strong> with a <em>UdpConfigData
RemoteAddress</em> being an invalid unicast IPv6 address if it is not
zero, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.4.3</td>
<td>0xe146a746, 0x2985, 0x4a7b, 0x92, 0xa5, 0x08, 0x44, 0x8d, 0x41,
0x69, 0x03</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_ALREADY_STARTED</strong> with a <em>ChildHandle</em>
instance has already been started/configured.</td>
<td>Call <strong>Configure()</strong> with a <em>ChildHandle</em>
instance has already been started/configured, the return status should
be <strong>EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.4.4</td>
<td>0x3522ad76, 0xe7aa, 0x4477, 0x9a, 0x41, 0xb7, 0xdc, 0xd6, 0xff,
0x7f, 0xf2</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> with <em>UdpConfigData.
AllowDuplicatePort</em> is <strong>FALSE</strong> and
<em>UdpConfigData.StationPort</em> is already used by other
instance.</td>
<td>Call <strong>Configure()</strong> with <em>UdpConfigData.
AllowDuplicatePort</em> is <strong>FALSE</strong> and
<em>UdpConfigData.StationPort</em> is already used by other instance,
the return status should be <strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.4.5</td>
<td>0x370fcb11, 0x68de, 0x4c01, 0xb0, 0xce, 0x64, 0x53, 0xb0, 0x94,
0x8f, 0xb5</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters</td>
<td><p>5.26.3.4.5 to 5.26.3.4.9 belong to one case.</p>
<p>1. Call <strong>Configure()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="odd">
<td>5.26.3.4.6</td>
<td>0xd6c84689, 0x0df8, 0x4f69, 0xa6, 0xd0, 0x76, 0x92, 0x89, 0xd0,
0x7d, 0x20</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters</td>
<td>2. Call <strong>GetModeData()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.4.7</td>
<td>0x7c2f3112, 0x80e9, 0x4b59, 0x98, 0xd5, 0x06, 0x25, 0x8e, 0x3e,
0x5f, 0x9f</td>
<td>Validate the <em>IP6ModeData.IsConfigured</em> and
<em>Udp6ConfigData</em></td>
<td>3. The value of <em>IP6ModeData.IsConfigured</em> should be
<strong>TRUE</strong>. The value of <em>Udp6ConfigData</em> should be
same with the assigned configure data.</td>
</tr>
<tr class="odd">
<td>5.26.3.4.8</td>
<td>0xc3fbe729, 0x3f1d, 0x41df, 0x83, 0x66, 0x6f, 0x50, 0x45, 0xf7,
0xce, 0x74</td>
<td><strong>EFI_UDP6 PROTOCOL.Configure() - Configure()</strong> returns
<strong>EFI_SUCCESS</strong> with a <strong>NULL</strong>
<em>Udp6ConfigData</em></td>
<td>4. Call <strong>Configure()</strong> with a <strong>NULL</strong>
<em>Udp6ConfigData</em>, the return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.4.9</td>
<td>0xd5a2273d, 0x33f4, 0x4f98, 0xb0, 0x8e, 0x9a, 0xd4, 0xec, 0x49,
0x9c, 0x76</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_NOT_STARTED</strong> with valid parameters</td>
<td>5. Call <strong>GetModeData()</strong> with valid parameters, the
return status should be <strong>EFI_NOT_STARTED.</strong></td>
</tr>
</tbody>
</table>


### Groups()

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
<td>5.26.3.5.1</td>
<td>0x1f290403, 0xaa9e, 0x4e3b, 0x94, 0xfb, 0x2d, 0x2b, 0xa0, 0x56,
0x6b, 0x22</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_NOT_STARTED</strong> with a not configured
<em>ChildHandle</em></td>
<td>Call <strong>Groups()</strong> with a not configured
<em>ChildHandle</em>, the return status should be
<strong>EFI_NOT_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.5.2</td>
<td>0xb1fd2421, 0x6e59, 0x4987, 0xb8, 0x28, 0x1c, 0x13, 0xb1, 0xe3,
0x60, 0x37</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an invalid <em>MulticaseAddress</em></td>
<td>Call <strong>Groups()</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an invalid <em>MulticaseAddress</em>, the return
status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.5.3</td>
<td>0xd2d32833, 0x51b6, 0x4c1b, 0x9a, 0x1c, 0x08, 0x11, 0xe6, 0xc1,
0xef, 0x4a</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_ALREADY_STARTED</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has already
been in the group table.</td>
<td>Call <strong>Groups()</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has already
been in the group table, the return status should be
<strong>EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.5.4</td>
<td>0x68c084c2, 0x55ef, 0x488a, 0x93, 0x24, 0xf9, 0x7b, 0x64, 0xbc,
0xbf, 0x03</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_NOT_FOUND</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table.</td>
<td><p>5.26.3.5.4 to 5.26.3.5.7 belong to one case.</p>
<p>1. Call <strong>Groups()</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table, the return status should be
<strong>EFI_NOT_FOUND.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.3.5.5</td>
<td>0xf16ff0fc, 0x074a, 0x460e, 0xa1, 0x11, 0x5f, 0x9e, 0xd3, 0x35,
0x9c, 0xac</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_SUCCESS</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table.</td>
<td>2. Call <strong>Groups()</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table, the return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.5.6</td>
<td>0x60253644, 0x6c0e, 0x4662, 0xbd, 0x4c, 0x63, 0xc8, 0xde, 0xb1,
0x0c, 0x21</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_SUCCESS</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
inserted in the group table.</td>
<td>3. Call <strong>Groups()</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
inserted in the group table, the return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.5.7</td>
<td>0x5200ac0c, 0x0adb, 0x4a14, 0xa8, 0xbf, 0xbd, 0x42, 0xeb, 0x68,
0x2d, 0x8e</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_NOT_FOUND</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
removed from the group table.</td>
<td>4. Call <strong>Groups()</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
removed from the group table, the return status should be
<strong>EFI_NOT_FOUND.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.5.8</td>
<td>0x05df343c, 0xaff4, 0x4dc5, 0x8b, 0xa5, 0xd7, 0x76, 0x63, 0x12,
0x89, 0x25</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_SUCCESS</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table.</td>
<td><p>5.26.3.5.8 to 5.26.3.5.11 belong to one case.</p>
<p>1. Call <strong>Groups()</strong> with <strong>TRUE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which is not in the
group table, the return status should be
<strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.3.5.9</td>
<td>0x24602ea3, 0x6bb2, 0x49cf, 0xac, 0x38, 0xb0, 0x13, 0x85, 0x5c,
0xc8, 0xb9</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters. Check the
<em>Ip6ModeData.GroupCount</em> and <em>Ip6ModeData.GroupTable</em></td>
<td>2. Call <strong>GetModeData()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS.</strong>
<em>Ip6ModeData.GroupCount</em> and <em>Ip6ModeData.GroupTable</em>
should be reasonable.</td>
</tr>
<tr class="odd">
<td>5.26.3.5.10</td>
<td>0x6aabe731, 0x0de1, 0x4643, 0x82, 0x4e, 0x18, 0x0c, 0x65, 0x4a,
0xac, 0x0c</td>
<td><strong>EFI_UDP6 PROTOCOL.Groups() - Groups()</strong> returns
<strong>EFI_SUCCESS</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
inserted in the group table.</td>
<td>3. Call <strong>Groups()</strong> with <strong>FALSE</strong>
<em>JoinFlag</em> and an <em>MulticaseAddress</em> which has been
inserted in the group table, the return status should be
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.5.11</td>
<td>0xe9d7c7e6, 0xfc75, 0x48ef, 0xb9, 0x46, 0x00, 0xda, 0x5d, 0xe4,
0xcd, 0xea</td>
<td><strong>EFI_UDP6 PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters. Check the
<em>Ip6ModeData.GroupCount</em></td>
<td>4. Call <strong>GetModeData()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS.</strong>
<em>Ip6ModeData.GroupCount</em> should be reasonable.</td>
</tr>
</tbody>
</table>


### Transmit()

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
<td>5.26.3.6.1</td>
<td>0x845b6a05, 0x23f3, 0x4c4f, 0x8d, 0xbc, 0xc0, 0xd3, 0x69, 0x9b,
0x76, 0x46</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_NOT_STARTED</strong> with a not configured
<em>ChildHandle</em></td>
<td>Call <strong>Transmit()</strong> with a not configured
<em>ChildHandle</em>, the return status should be
<strong>EFI_NOT_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.2</td>
<td>0x71c15402, 0x7d5c, 0x4b8c, 0xb9, 0xa5, 0xfd, 0xe5, 0x3e, 0x68,
0xed, 0x22</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token</em></td>
<td>Call <strong>Transmit()</strong> with a <strong>NULL</strong>
<em>Token</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.3</td>
<td>0x12795cad, 0xdbbe, 0x41cd, 0x84, 0x57, 0x5f, 0xae, 0x7d, 0x72,
0x07, 0x2a</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token-&gt;Event</em></td>
<td>Call <strong>Transmit()</strong> with a <strong>NULL</strong>
<em>Token-&gt;Event</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.4</td>
<td>0xbfcd7c31, 0xcb6f, 0x4cfd, 0xb9, 0xe2, 0x01, 0xd7, 0x5c, 0x6b,
0x44, 0xfa</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData</em></td>
<td>Call <strong>Transmit()</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.5</td>
<td>0x4c71fbec, 0x6cc6, 0x4cac, 0x89, 0x74, 0x67, 0xb5, 0x27, 0xbe,
0xef, 0xa3</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em>Token-&gt;Packet.TxData</em>-&gt;FragmentCount is Zero</td>
<td>Call <strong>Transmit()</strong> with
<em>Token-&gt;Packet.TxData</em>-&gt;FragmentCount is Zero, the return
status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.6</td>
<td>0xe0e3d058, 0xbdc3, 0x4ed2, 0x9c, 0x39, 0xea, 0x10, 0x6b, 0xe5,
0xea, 0x7a</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with
<em>Token-&gt;Packet.TxData-&gt;FragmentTable[0].FragmentLength</em> is
Zero</td>
<td>Call <strong>Transmit()</strong> with
<em>Token-&gt;Packet.TxData-&gt;FragmentTable[0].FragmentLength</em> is
Zero, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.7</td>
<td>0xbacc7fd3, 0x9a5c, 0x4ae6, 0xb6, 0xb3, 0x7f, 0x95, 0xc7, 0xda,
0xc4, 0xa2</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData-&gt;FragmentTable[0].FragmentBuffer</em></td>
<td>Call <strong>Transmit()</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData-&gt;FragmentTable[0].FragmentBuffer</em>,
the return status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.8</td>
<td>0xf062269b, 0x66bb, 0x426a, 0x8e, 0xeb, 0x06, 0xd3, 0x0c, 0xd3,
0x30, 0x16</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with an invalid
<em>Token-&gt;Packet.TxData-&gt;DataLength</em></td>
<td>Call <strong>Transmit()</strong> with an invalid
<em>Token-&gt;Packet.TxData-&gt;DataLength</em> which is not equal to
the sum of the fragments length, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.9</td>
<td>0x5a3af347, 0xdf8a, 0x4a67, 0x80, 0x32, 0xa7, 0xd0, 0xa8, 0xcc,
0x2f, 0x97</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a non-zero
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData-&gt;DestinationAddress</em>
which is not specified in Configure process</td>
<td>Call <strong>Transmit()</strong> with a non-zero
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData-&gt;DestinationAddress</em>
which is not specified in Configure process, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.10</td>
<td>0x52218200, 0xfffd, 0x4b78, 0x8b, 0x2b, 0xec, 0x17, 0x56, 0x2c,
0x3f, 0xd7</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a zero
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData-&gt;DestinationAddress</em>
when DestinationAddress is unspecified when doing Configure process</td>
<td>Call <strong>Transmit()</strong> with a zero
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData-&gt;DestinationAddress</em>
when DestinationAddress is unspecified when doing Configure process, the
return status should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.11</td>
<td>0x97434d51, 0x8e06, 0x49e9, 0x95, 0xd0, 0xfc, 0x3a, 0x03, 0xf9,
0x9c, 0xee</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData</em> and the instance’s
<em>UdpConfigData.RemoteAddress</em> is unspecified.</td>
<td>Call <strong>Transmit()</strong> with a <strong>NULL</strong>
<em>Token-&gt;Packet.TxData-&gt;Udp6sessionData</em> and the instance’s
<em>UdpConfigData.RemoteAddress</em> is unspecified, the return status
should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.12</td>
<td>0x31b5da9f, 0xd866, 0x43c7, 0x8c, 0x2b, 0xf8, 0xd9, 0x7c, 0x5b,
0xdb, 0x12</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> with a <em>Token-&gt;Event</em> which
has already been in the transmit queue.</td>
<td>Call <strong>Transmit()</strong> with a <em>Token-&gt;Event</em>
which has already been in the transmit queue, the return status should
be <strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.6.13</td>
<td>0x99e6bfb0, 0x903b, 0x4c6c, 0xa4, 0x6c, 0x9e, 0x51, 0x23, 0xdb,
0xdd, 0x4b</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_BAD_BUFFER_SIZE</strong> with a
<em>Token-&gt;Packet.TxData-&gt;DataLength</em> which beyond the maximum
udp6 packet size.</td>
<td>Call <strong>Transmit()</strong> with a
<em>Token-&gt;Packet.TxData-&gt;DataLength</em> which beyond the maximum
udp6 packet size, the return status should be
<strong>EFI_BAD_BUFFER_SIZE.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.6.14</td>
<td>0xaf040d05, 0xf0e3, 0x4348, 0x8f, 0x1d, 0xd9, 0x99, 0x90, 0xc7,
0x3d, 0x06</td>
<td><strong>EFI_UDP6 PROTOCOL.Transmit() - Transmit()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.3.6.14 to 5.26.3.6.17 belong to one case.</p>
<p>1. Call <strong>Transmit()</strong> with valid parameters, the return
status should be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.3.6.15</td>
<td>0x930f3d18, 0x3261, 0x4d17, 0xa3, 0xc0, 0x0d, 0xd1, 0xa6, 0x5d,
0x10, 0xe1</td>
<td><em>Token-&gt;Event</em> should be signnaled</td>
<td><em>Token-&gt;Event</em> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.3.6.16</td>
<td>0x93873bee, 0x2136, 0x432e, 0xb0, 0x8f, 0xd7, 0x9d, 0xd9, 0xf9,
0xcf, 0x04</td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong></td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.3.6.17</td>
<td>0x30ca402a, 0xed8a, 0x4c69, 0x94, 0x7f, 0xa0, 0x4c, 0xd1, 0xbb,
0xaa, 0x58</td>
<td>The received packet content should be reasonable.</td>
<td>The received packet content should be reasonable.</td>
</tr>
</tbody>
</table>


### Receive()

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
<td>5.26.3.7.1</td>
<td>0xb5c83b2c, 0x66c1, 0x4ea5, 0xba, 0x41, 0x6c, 0xc4, 0x85, 0xb2,
0x58, 0xaf</td>
<td><strong>EFI_UDP6 PROTOCOL.Receive() - Receive()</strong> returns
<strong>EFI_NOT_STARTED</strong> with a not configured
<em>ChildHandle</em></td>
<td>Call <strong>Receive()</strong> with a not configured
<em>ChildHandle</em>, the return status should be
<strong>EFI_NOT_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.7.2</td>
<td>0xc5c9fd31, 0xf095, 0x473f, 0xaf, 0x53, 0x87, 0x16, 0xc8, 0x51,
0x58, 0x9d</td>
<td><strong>EFI_UDP6 PROTOCOL.Receive() - Receive()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token</em></td>
<td>Call <strong>Receive()</strong> with a <strong>NULL</strong>
<em>Token</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.7.3</td>
<td>0xa8916a19, 0xecf7, 0x4392, 0xa1, 0x65, 0xc0, 0x6e, 0x1b, 0xff,
0xc1, 0xe6</td>
<td><strong>EFI_UDP6 PROTOCOL.Receive() - Receive()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> with a <strong>NULL</strong>
<em>Token-&gt;Event</em></td>
<td>Call <strong>Receive()</strong> with a <strong>NULL</strong>
<em>Token-&gt;Event</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.7.14</td>
<td>0x17a43441, 0x0701, 0x446b, 0xab, 0x37, 0x4c, 0xd9, 0x23, 0xcf,
0xc1, 0x43</td>
<td><strong>EFI_UDP6 PROTOCOL.Receive() – Receive()</strong> returns
<strong>EFI_ACCESS_DENIED</strong> with a <em>Token-&gt;Event</em> which
has already been in the transmit queue.</td>
<td>Call <strong>Receive()</strong> with a <em>Token-&gt;Event</em>
which has already been in the transmit queue, the return status should
be <strong>EFI_ACCESS_DENIED.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.7.5</td>
<td>0x3166ca55, 0x6f3f, 0x4748, 0xbc, 0x48, 0xf7, 0xb6, 0x86, 0x35,
0x9d, 0xcc</td>
<td><strong>EFI_UDP6 PROTOCOL.Receive() – Receive()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.3.7.5 to 5.26.3.7.8 belong to one case.</p>
<p>1. Call <strong>Receive()</strong>with valid parameters, the return
status should be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="odd">
<td>5.26.3.7.6</td>
<td>0xb5e37f49, 0xc13a, 0x4c80, 0x9d, 0x37, 0x9b, 0xb6, 0x96, 0xb8,
0x14, 0xe7</td>
<td><em>Token-&gt;Event</em> should be signaled</td>
<td><em>Token-&gt;Event</em> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.3.7.7</td>
<td>0x96a78bb2, 0x8d5d, 0x4ed1, 0x9e, 0xc5, 0xc7, 0x34, 0x28, 0x61,
0x1e, 0x7d</td>
<td>The received packet content should be reasonable.</td>
<td>The received packet content should be reasonable.</td>
</tr>
<tr class="odd">
<td>5.26.3.7.8</td>
<td>0x90b87634, 0x1da5, 0x4f26, 0x8c, 0x78, 0x82, 0xba, 0xd5, 0x4a,
0xc8, 0xfe</td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong></td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


### Cancel()

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
<td>5.26.3.8.1</td>
<td>0xd0aafd24, 0xa340, 0x40f4, 0xba, 0x48, 0xe1, 0x59, 0x86, 0xc7,
0x78, 0x79</td>
<td><strong>EFI_UDP6 PROTOCOL.Cancel() – Cancel()</strong> returns
<strong>EFI_NOT_STARTED</strong> with a not configured
<em>ChildHandle</em></td>
<td>Call <strong>Cancel()</strong> with a not configured
<em>ChildHandle</em>, the return status should be
<strong>EFI_NOT_STARTED.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.8.2</td>
<td>0x063478c3, 0x207d, 0x4b82, 0x96, 0xf5, 0x0f, 0xbf, 0xee, 0x2f,
0xac, 0x5f</td>
<td><strong>EFI_UDP6 PROTOCOL.Cancel() – Cancel()</strong> returns
<strong>EFI_NOT_FOUND</strong> with a <em>Token</em> which hasn’t been
inserted into both transmit and receive queue.</td>
<td>Call <strong>Cancel()</strong>with a <em>Token</em> which hasn’t
been inserted into both transmit and receive queue, the return status
should be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="even">
<td>5.26.3.8.3</td>
<td>0xed1466df, 0xccc6, 0x412e, 0xbe, 0xda, 0xb9, 0x87, 0xc8, 0x37,
0x2b, 0x6f</td>
<td><strong>EFI_UDP6 PROTOCOL.Cancel() – Cancel()</strong> returns
<strong>EFI_NOT_FOUND</strong> with a <em>Token</em> which has been
removed into both transmit and receive queue.</td>
<td>Call <strong>Cancel()</strong>with a <em>Token</em> which has been
removed into both transmit and receive queue, the return status should
be <strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.3.8.4</td>
<td>0xebe8e81e, 0x632c, 0x4aa9, 0xa8, 0x50, 0x27, 0xb7, 0x32, 0x63,
0xd0, 0x62</td>
<td><strong>EFI_UDP6 PROTOCOL.Cancel() – Cancel()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.3.8.4 to 5.26.3.8.6 belong to one case.</p>
<p>1. Call <strong>Cancel()</strong> with valid parameters, the return
status should be <strong>EFI_SUCCESS.</strong></p></td>
</tr>
<tr class="even">
<td>5.26.3.8.5</td>
<td>0x616b87c1, 0xa5f9, 0x4195, 0x81, 0x38, 0x9c, 0xb8, 0xcd, 0x3c,
0x64, 0x50</td>
<td><em>Token-&gt;Event</em> should be signaled</td>
<td><em>Token-&gt;Event</em> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.3.8.6</td>
<td>0x1280bba6, 0x5d60, 0x43ae, 0xba, 0x36, 0x2d, 0xce, 0x08, 0x79,
0x5e, 0x57</td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong></td>
<td><em>Token-&gt;Status</em> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>


## EFI_MTFTP6_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_MTFTP6_PROTOCOL Section.

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
<td>5.26.4.1.1</td>
<td>0xed279b2f, 0x0fb1, 0x4f84, 0x8c, 0x11, 0x69, 0x36, 0x88, 0x0f,
0x94, 0x48</td>
<td><strong>EFI_MTFTP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
with a <strong>NULL</strong> <em>ChildHandle</em>.</td>
<td>Call <strong>CreateChild()</strong> with a <strong>NULL</strong>
<em>ChildHandle</em>, the return status should be
<strong>EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td>5.26.4.1.2</td>
<td>0x758b358d, 0x4bf0, 0x4bcc, 0x82, 0x6c, 0xe4, 0xad, 0x40, 0xe8,
0x29, 0x6e</td>
<td><strong>EFI_MTFTP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
1<sup>st</sup> valid <em>ChildHandle</em>.</td>
<td><p>5.26.4.1.2 to 5.26.4.1.5 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> with the 1<sup>st</sup> valid
<em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.1.3</td>
<td>0x5446dbb2, 0xbf0b, 0x4685, 0x88, 0xf4, 0x3b, 0x14, 0x3e, 0x2b,
0xdd, 0x1b</td>
<td><strong>EFI_MTFTP6_SERVICE_BINDING_PROTOCOL.CreateChild() -
CreateChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
2<sup>nd</sup> valid <em>ChildHandle</em>.</td>
<td>2. Call <strong>CreateChild()</strong> with the 2<sup>nd</sup> valid
<em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.1.4</td>
<td>0x6a61e0bd, 0xd760, 0x4788, 0x85, 0xc9, 0x4b, 0x45, 0xe2, 0x9e,
0x7e, 0x02</td>
<td><strong>EFI_MTFTP6_SERVICE_BINDING_PROTOCOL.DestroyChild() -
DestroyChild()</strong> returns <strong>EFI_SUCCESS</strong> with the
2<sup>nd</sup> valid <em>ChildHandle</em>.</td>
<td>3. Call <strong>DestroyChild()</strong> with the 2<sup>nd</sup>
valid <em>ChildHandle</em>, the return status should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.1.5</td>
<td>0x0403eeee, 0x34d6, 0x47f4, 0x80, 0xcf, 0x28, 0x44, 0xa1, 0x7e,
0xfb, 0x7a</td>
<td><strong>EFI_MTFTP6_SERVICE_BINDING_PROTOCOL.DestroyChild() -
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
| 5.26.4.2.1 | 0xc4bdecde, 0xc89f, 0x4402, 0x9e, 0x9b, 0x2e, 0xac, 0xdd, 0xd6, 0xf7, 0xa6 | **EFI_MTFTP6_SERVICE_BINDING_PROTOCOL. DestroyChild() - DestroyChild()** returns **EFI_INVALID_PARAMETER** with a **NULL** *ChildHandle.* | Call **DestroyChild()** with a **NULL** *ChildHandle*, the return status should be **EFI_INVALID_PARAMETER**. |



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
<td>5.26.4.3.1</td>
<td>0x2d5eae25, 0x9fda, 0x47c9, 0x80, 0x14, 0xf3, 0x34, 0xf0, 0x1e,
0x67, 0x12</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> with
<strong>NULL</strong> <strong>ModeData</strong></td>
<td>Call <strong>GetModeData()</strong>with <strong>NULL</strong>
<strong>ModeData,</strong> the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.3.2</td>
<td>0x2a17e0f5, 0x6eab, 0x4528, 0xb1, 0xef, 0x4e, 0x99, 0x77, 0xd0,
0xc4, 0xa7</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetModeData() - GetModeData()</strong>
returns <strong>EFI_SUCCESS</strong> with the valid parameters.</td>
<td><p>5.26.4.3.2 to 5.26.4.3.3 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an MTFTP6
instance.</p>
<p>2. Call <strong>Configure()</strong> to initialize the MTFTP6
instance.</p>
<p>3. Call <strong>GetModeData()</strong> with the valid parameters, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.3.3</td>
<td>0x51c6056a, 0x9582, 0x444a, 0xba, 0x84, 0x0d, 0xd5, 0xe4, 0x93,
0xb3, 0xa0</td>
<td><strong>Mtftp6ModeData.ConfigData</strong> should be the same as
previous set <strong>ConfigData</strong>.</td>
<td><p>4. <strong>Mtftp6ModeData.ConfigData</strong> should be the same
as previous set <strong>ConfigData</strong>.</p>
<p>5. Call <strong>DestroyChild()</strong> to destroy the MTFTP6
instance.</p></td>
</tr>
</tbody>
</table>


### Configure()

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
<td>5.26.4.4.1</td>
<td>0x2a946231, 0xa817, 0x45ed, 0x88, 0x59, 0x44, 0x42, 0xd5, 0x6d,
0x53, 0x45</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when StationIP is neither
zero nor a configured IP address.</td>
<td>Call <strong>Configure()</strong> when StationIP is neither zero nor
a configured IP address, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.4.2</td>
<td>0x02caf586, 0xff1c, 0x41e6, 0xb6, 0x5b, 0x6f, 0xd0, 0x22, 0xa4,
0x60, 0x14</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when ServerIp is an
invalid unicast IPv6 address.</td>
<td>Call <strong>Configure()</strong> when ServerIp is an invalid
unicast IPv6 address, such as ff02::1, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.4.3</td>
<td>0x9e06f1d5, 0xb888, 0x4976, 0x9c, 0x39, 0x6a, 0xcf, 0x26, 0x94,
0x2d, 0x76</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when ServerIp is an
invalid unicast IPv6 address.</td>
<td>Call <strong>Configure()</strong> when ServerIp is an invalid
unicast IPv6 address, such as ::, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.4.4</td>
<td>0xe5efe42a, 0x6539, 0x487d, 0x89, 0xe3, 0xb2, 0x88, 0x2a, 0xb1,
0xd7, 0xd4</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> when StationIp and LocalPort
have already been used.</td>
<td>Call <strong>Configure()</strong> when StationIp and LocalPort have
already been used, the return status should be
<strong>EFI_ACCESS_DENIED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.4.5</td>
<td>0xcde4ae63, 0x74f6, 0x46fc, 0xa2, 0xae, 0x23, 0x2b, 0x39, 0x3a,
0x02, 0xd3</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_ACCESS_DENIED</strong> when call
<strong>Configure()</strong> again to update the Configure Data without
call <strong>Configure()</strong> with <strong>NULL</strong>.</td>
<td>Call <strong>Configure()</strong> again to update the Configure Data
without call <strong>Configure()</strong> with <strong>NULL</strong>,
the return status should be <strong>EFI_ACCESS_DENIED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.4.6</td>
<td>0x90337601, 0x85ca, 0x4152, 0x9f, 0x54, 0xdc, 0xac, 0x13, 0x87,
0x28, 0xdb</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_SUCCESS</strong> with valid
<strong>Mtftp6ConfigData</strong>.</td>
<td><p>5.26.4.4.6 to 5.26.4.4.9 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an MTFTP6
instance.</p>
<p>2. Call <strong>Configure()</strong> with valid
<strong>Mtftp6ConfigData</strong>, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.4.7</td>
<td>0x85bceaa3, 0x377a, 0x4847, 0x93, 0x4c, 0xa7, 0xea, 0x95, 0x1a,
0x4e, 0x57</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_SUCCESS</strong> when
<strong>Mtftp6ConfigData</strong> is <strong>NULL</strong>.</td>
<td>3. Call <strong>Configure()</strong> when
<strong>Mtftp6ConfigData</strong> is <strong>NULL</strong>, the return
status should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.4.8</td>
<td>0x62c85a93, 0x029d, 0x4bb2, 0xb5, 0x82, 0x25, 0x63, 0xae, 0x63,
0xba, 0xd7</td>
<td><strong>EFI_MTFTP6_PROTOCOL.Configure() - Configure()</strong>
returns <strong>EFI_SUCCESS</strong> with valid
<strong>Mtftp6ConfigData</strong> in the second time.</td>
<td>4. Call <strong>Configure()</strong> with the valid
<strong>Mtftp6ConfigData</strong> in the second time, the return status
should be <strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.4.9</td>
<td>0xef42aa6a, 0x1c66, 0x4768, 0x8c, 0x4f, 0xc1, 0x18, 0x8a, 0xdc,
0x69, 0xfb</td>
<td>Call <strong>GetModeData()</strong> with the valid parameters, the
<strong>Mtftp6ModeData.ConfigData</strong> should be the same as
previous set <strong>ConfigData</strong>.</td>
<td><p>5. Call <strong>GetModeData()</strong> with the valid parameters,
the <strong>Mtftp6ModeData.ConfigData</strong> should be the same as
previous set <strong>ConfigData</strong>.</p>
<p>6. Call <strong>DestroyChild()</strong> to destroy the MTFTP6
instance.</p></td>
</tr>
</tbody>
</table>


### GetInfo()

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
<td>5.26.4.5.1</td>
<td>0xed2fb03d, 0x8422, 0x46dc, 0xa4, 0xda, 0x31, 0xbe, 0x84, 0xa2,
0xf5, 0x0d</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_NOT_STARTED</strong> when the instance hasn't been
configured.</td>
<td>Call <strong>GetInfo()</strong> when the instance hasn't been
configured, the return status should be
<strong>EFI_NOT_STARTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.5.2</td>
<td>0xae921a1d, 0x1d87, 0x40a0, 0x90, 0x09, 0xe1, 0xc3, 0x30, 0x45,
0xd7, 0x7d</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when filename is
<strong>NULL</strong>.</td>
<td>Call <strong>GetInfo()</strong> when filename is
<strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.5.3</td>
<td>0x99321cf6, 0x6591, 0x4b71, 0xbd, 0xbe, 0x5a, 0xcb, 0xbe, 0x97,
0x32, 0x51</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <strong>OptionCount</strong>
isn't zero and <strong>OptionList</strong> is
<strong>NULL</strong>.</td>
<td>Call <strong>GetInfo()</strong> when <strong>OptionCount</strong>
isn't zero and <strong>OptionList</strong> is <strong>NULL</strong>, the
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.5.4</td>
<td>0x807e6ac5, 0x5ff8, 0x4e9c, 0x9f, 0xb0, 0x21, 0x9d, 0x3c, 0xf6,
0xae, 0x1c</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>OptionList</strong> is wrong format.</td>
<td>Call <strong>GetInfo()</strong> when one or more options in
<strong>OptionList</strong> is wrong format, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.5.5</td>
<td>0xdddb451a, 0x2d08, 0x45f2, 0xb4, 0x3c, 0x63, 0xde, 0xfc, 0xcc,
0x29, 0x42</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when
<strong>PacketLength</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>GetInfo()</strong> when <strong>PacketLength</strong>
is <strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.5.6</td>
<td>0x1b915cd6, 0x34eb, 0x4a87, 0x8f, 0x18, 0x63, 0x25, 0x91, 0x1b,
0x80, 0x85</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when
<strong>OverrideData.ServerIp</strong> is invalid unicast address.</td>
<td>Call <strong>GetInfo()</strong> when
<strong>OverrideData.ServerIp</strong> is invalid unicast address, the
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.5.7</td>
<td>0x890ecac1, 0xd029, 0x4a8f, 0x99, 0x10, 0x57, 0x73, 0xa0, 0x70,
0xba, 0xff</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>OptionList</strong> is unsupported.</td>
<td>Call <strong>GetInfo()</strong> when one or more options in
<strong>OptionList</strong> is unsupported, the return status should be
<strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.5.8</td>
<td>0xa807dd98, 0x8d94, 0x42cd, 0x9b, 0x38, 0x2c, 0x4d, 0xa1, 0x43,
0xc1, 0xbc</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_TFTP_ERROR</strong> when a mtftp6 error packet received from
the other side.</td>
<td>Call <strong>GetInfo()</strong> when a mtftp6 error packet received
from the other side, the return status should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.5.9</td>
<td>0x8ea63309, 0x2824, 0x4186, 0x93, 0x39, 0xd4, 0x10, 0x44, 0xef,
0xf2, 0x36</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_TIMEOUT</strong> when there is no response from the other
side.</td>
<td>Call <strong>GetInfo()</strong> when no response is sent from the
other side, the return status should be
<strong>EFI_TIMEOUT</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.5.10</td>
<td>0x29b90725, 0x6662, 0x43f5, 0xa4, 0xe5, 0xb0, 0xb5, 0xfa, 0x26,
0x55, 0x38</td>
<td><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_PORT_UNREACHABLE</strong> when an ICMP port unreachable
error packet was received.</td>
<td>Call <strong>GetInfo()</strong>when an ICMP port unreachable error
packet was received, the return status should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.5.11</td>
<td>0x01b2ee0f, 0xb879, 0x4475, 0x9e, 0x58, 0x7d, 0xff, 0x51, 0x13,
0x88, 0x87</td>
<td><strong>EFI_MTFTP6_PROTOCOL. GetInfo () - GetInfo ()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.4.5.11 to 5.26.4.5.12 belong to one case.</p>
<p>1. Call <strong>CreateChild()</strong> to create an MTFTP6
instance.</p>
<p>2. Call <strong>Configure()</strong> with valid
<strong>Mtftp6ConfigData</strong>, the return status should be
<strong>EFI_SUCCESS</strong>.</p>
<p>3. Call <strong>GetInfo()</strong> with valid parameters.</p>
<p>4. Host send MTFTP6 OACK packet.</p>
<p>5. Host receive the Ack for OACK</p>
<p>6. The return status of <strong>GetInfo()</strong> should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.5.12</td>
<td>0x9ddd227a, 0x0734, 0x4d6b, 0xaf, 0xa9, 0xdb, 0xc1, 0xad, 0x10,
0xb7, 0xd3</td>
<td>Call <strong>ParseOptions()</strong> to parse the
<strong>Packet</strong>, the content of
<strong>EFI_MTFTP6_OPTION</strong> should be right.</td>
<td>7. Call <strong>ParseOptions()</strong> to parse the
<strong>Packet</strong>, the content of
<strong>EFI_MTFTP6_OPTION</strong> should be right.</td>
</tr>
<tr class="even">
<td>5.26.4.5.13</td>
<td><p>0x1257a949,</p>
<p>0xb84d, 0x43f6, 0x89,0x2b, 0x48,0x5f, 0x33,0x65, 0x82,0x12</p></td>
<td><p><strong>EFI_MTFTP6_PROTOCOL.GetInfo(</strong>) -
<strong>GetInfo()</strong> returns</p>
<p><strong>EFI_PORT_UNREACHABlE</strong> when an ICMP port</p>
<p>unreachable error packet</p>
<p>was received.</p></td>
<td><p>Call <strong>GetInfo()</strong> when an ICMP port</p>
<p>unreachable error packet was received,</p>
<p>the return status should be</p>
<p><strong>EFI_PORT_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.5.14</td>
<td>0xd3688340, 0x7b29, 0x46cb, 0x98,0x05, 0x76,0xf0, 0xab,0xef,
0x78,0xc0</td>
<td><p><strong>EFI_MTFTP6_PROTOCOL</strong></p>
<p>.<strong>GetInfo()</strong> - <strong>GetInfo()</strong> returns</p>
<p><strong>EFI_NETWORK_UNREACHABLE</strong> when an ICMP net</p>
<p>unreachable error packet</p>
<p>was received.</p></td>
<td><p>Call <strong>GetInfo()</strong> when an ICMP net</p>
<p>unreachable error packet was received,</p>
<p>the return status should be</p>
<p><strong>EFI_NETWORK_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.5.15</td>
<td>0x8cffd8f0,0xf8e7, 0x4e6c, 0x8e,0x2f, 0xbe,0xf5, 0xff,0xd8,
0xd4,0x8c</td>
<td><p><strong>EFI_MTFTP6_PROTOCOL.GetInfo()</strong> -
<strong>GetInfo()</strong> returns</p>
<p><strong>EFI_HOST_UNREACHABLE</strong> when an ICMP host</p>
<p>unreachable error packet</p>
<p>was received.</p></td>
<td><p>Call <strong>GetInfo()</strong> when an ICMP host</p>
<p>unreachable error packet was received,</p>
<p>the return status should be</p>
<p><strong>EFI_HOST_UNREACHABLE</strong>.</p></td>
</tr>
</tbody>
</table>



### ParseOptions()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.26.4.6.1 | 0x165bba38, 0x2cc8, 0x4c86, 0xb5, 0x9a, 0x82, 0xd5, 0x33, 0xe0, 0x3d, 0x12 | **EFI_MTFTP6_PROTOCOL.ParseOptions() - ParseOptions()** returns **EFI_INVALID_PARAMETER** when **PacketLen** is zero. | Call **ParseOptions()** when **PacketLen** is zero, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.26.4.6.2 | 0x46feb505, 0x82fd, 0x4d84, 0x98, 0x9f, 0x2a, 0x24, 0x70, 0xff, 0xf9, 0x1f | **EFI_MTFTP6_PROTOCOL. ParseOptions() - ParseOptions()** returns **EFI_INVALID_PARAMETER** when **Packet** is **NULL**. | Call **ParseOptions()** when **Packet** is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.26.4.6.3 | 0x2c5276ba, 0x0fed, 0x474f, 0x91, 0x79, 0x9d, 0xa1, 0xdb, 0x8e, 0x32, 0x19 | **EFI_MTFTP6_PROTOCOL. ParseOptions() - ParseOptions()** returns **EFI_INVALID_PARAMETER** when **Packet** isn't a valid Mtftp6 packet. | Call **ParseOptions()** when **Packet** isn't a valid Mtftp6 packet, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.26.4.6.4 | 0x3bd37c27, 0xeaea, 0x474c, 0x92, 0xf7, 0xd4, 0x90, 0x68, 0x50, 0xb5, 0x54 | **EFI_MTFTP6_PROTOCOL. ParseOptions() - ParseOptions()** returns **EFI_INVALID_PARAMETER** when when **OptionCount** is **NULL**. | Call **ParseOptions()** when **OptionCount** is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.26.4.6.5 | 0xd5918b06, 0x88cd, 0x4321, 0x90, 0x18, 0x3e, 0x3e, 0x1a, 0xd2, 0xcd, 0xa1 | **EFI_MTFTP6_PROTOCOL. ParseOptions() - ParseOptions()** returns **EFI_NOT_FOUND** when no **Options** is found. | Call **ParseOptions()** when no **Options** is found, the return status should be **EFI_NOT_FOUND**. |
| 5.26.4.6.6 | 0xad87d495, 0x9738, 0x4c86, 0x97, 0x2c, 0x63, 0xdb, 0xcd, 0x2b, 0xda, 0x84 | **EFI_MTFTP6_PROTOCOL. ParseOptions() - ParseOptions()** returns **EFI_PROTOCOL_ERROR** when one or more of the option fields are not valid. | Call **ParseOptions()** when one or more of the option fields are not valid, the return status should be **EFI_PROTOCOL_ERROR**. |


### ReadFile()

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
<td>5.26.4.7.1</td>
<td>0x33346d27, 0x213b, 0x4137, 0xa0, 0x4e, 0xff, 0x79, 0xc3, 0x40,
0x82, 0x2a</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_NOT_STARTED</strong> when the instance hasn’t been
configured.</td>
<td>Call <strong>ReadFile()</strong>when the instance hasn’t been
configured. The return status should be
<strong>EFI_NOT_STARTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.2</td>
<td>0xfa4a5e44, 0x3823, 0x4273, 0xa8, 0x86, 0x7d, 0x95, 0xb4, 0xd9,
0x0d, 0xa1</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <strong>Token</strong> is
<strong>NULL</strong>.</td>
<td>Call <strong>ReadFile()</strong> when <strong>Token</strong> is
<strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.3</td>
<td>0x2e09fd86, 0xfe91, 0x4490, 0x9f, 0x33, 0xa9, 0xdf, 0x38, 0x65,
0xf0, 0xdf</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when
<strong>Token.Filename</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>ReadFile()</strong> when
<strong>Token.Filename</strong> is <strong>NULL</strong>. The return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.4</td>
<td>0x197e3225, 0xc6ba, 0x43ee, 0x8d, 0xf7, 0x31, 0x31, 0xbd, 0x71,
0x5e, 0x2e</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when <strong>OptionCount</strong>
isn't zero and <strong>OptionList</strong> is
<strong>NULL</strong>.</td>
<td>Call <strong>ReadFile()</strong> when <strong>OptionCount</strong>
isn't zero and <strong>OptionList</strong> is <strong>NULL</strong>. The
return status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.5</td>
<td>0x983411c5, 0x040b, 0x4995, 0xbb, 0x0e, 0x80, 0xb8, 0x69, 0x3b,
0x6b, 0x9e</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>Token.OptionList</strong> is wrong format.</td>
<td>Call <strong>ReadFile()</strong> when one or more options in
<strong>Token.OptionList</strong> is wrong format. The return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.6</td>
<td>0x7fff6983, 0x39e5, 0x421f, 0x93, 0xb8, 0x3a, 0x16, 0x4d, 0x3a,
0x95, 0x34</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>Token.Buffer</strong> and <strong>Token.CheckPacket</strong> are
both <strong>NULL</strong>.</td>
<td>Call <strong>ReadFile()</strong> when one or more options in
<strong>Token.Buffer</strong> and <strong>Token.CheckPacket</strong> are
both <strong>NULL</strong>. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.7</td>
<td>0xbdb9aaa3, 0x4efa, 0x41dc, 0x91, 0x22, 0xf9, 0x15, 0x04, 0x4f,
0x34, 0xac</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>Token.OverrideData.ServerIp</strong> is not valid unicast IPv6
address.</td>
<td>Call <strong>ReadFile()</strong> when one or more options in
<strong>Token.OverrideData.ServerIp</strong> is not valid unicast IPv6
address. The return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.8</td>
<td>0xf410b1c3, 0x5e50, 0x4389, 0x99, 0xac, 0x5f, 0x9f, 0xe7, 0xed,
0x47, 0x9d</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when one or more options in
<strong>Token.OptionList</strong> is not supported.</td>
<td>Call <strong>ReadFile()</strong> when one or more options in
<strong>Token.OptionList</strong> is not supported. The return status
should be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.9</td>
<td>0xb5b845cf, 0x1ac2, 0x4ba6, 0x88, 0x13, 0x35, 0xdc, 0xe6, 0x07,
0xec, 0x82</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> when
<strong>Token.BufferSize</strong> isn't large enough to hold the
download data in download process.</td>
<td>Call <strong>ReadFile()</strong> when
<strong>Token.BufferSize</strong> isn't large enough to hold the
download data in download process. The return status should be
<strong>EFI_BUFFER_TOO_SMALL</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.10</td>
<td>0x79f11d98, 0x4a0c, 0x4c2a, 0x8f, 0x48, 0x58, 0xa6, 0x04, 0x6c,
0x11, 0x94</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_ABORTED</strong> when current operation is aborted by
user.</td>
<td>Call <strong>ReadFile()</strong> when current operation is aborted
by user. The return status should be <strong>EFI_ABORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.11</td>
<td>0x99d1d01e, 0x23f4, 0x4877, 0x98, 0xe9, 0x6e, 0xa3, 0xb9, 0x98,
0x8e, 0x9d</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_TFTP_ERROR</strong> when a mtftp6 error packet
received.</td>
<td>Call <strong>ReadFile()</strong> when a mtftp6 error packet was
received. The return status should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.12</td>
<td>0x2e222488, 0xcab8, 0x40d5, 0xa6, 0x71, 0xac, 0xa6, 0x6c, 0x76,
0x58, 0x59</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_PORT_UNREACHABLE</strong> when a icmp6 port unreachable
error packet was received.</td>
<td>Call <strong>ReadFile()</strong> when a icmp6 port unreachable error
packet was received. The return status should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.13</td>
<td>0x36a6ebe2,0xdb79, 0x423f, 0xad,0x53, 0x9b,0xf1, 0x7d,0x1b,
0x4c,0x20</td>
<td><p><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong>
returns</p>
<p><strong>EFI_NETWORK_UNREACHABLE</strong> when an ICMP net unreachable
error packet was received.</p></td>
<td><p>Call <strong>GetInfo()</strong> when an ICMP net</p>
<p>unreachable error packet was received. The return status should
be</p>
<p><strong>EFI_NETWORK_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.7.14</td>
<td>0x3215f20a, 0xec4f, 0x4666, 0x8d,0x6b, 0x e7,0x09, 0x21,0x65,
0x7a,0xa2</td>
<td><p><strong>EFI_MTFTP6_PROTOCOL.GetInfo() - GetInfo()</strong>
returns</p>
<p><strong>EFI_HOST_UNREACHABLE</strong> when an ICMP host</p>
<p>unreachable error packet was received.</p></td>
<td><p>Call <strong>GetInfo()</strong> when an ICMP host unreachable
error packet was received. The return status should be</p>
<p><strong>EFI_HOST_UNREACHABLE</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.7.15</td>
<td>0x0d5a4c2a, 0xc87e, 0x41e4, 0xa8, 0x6b, 0xce, 0x62, 0x30, 0x7c,
0x84, 0x06</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_TIMEOUT</strong> when no response was received.</td>
<td>Call <strong>ReadFile()</strong> when no response was received. The
return status should be <strong>EFI_TIMEOUT</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.16</td>
<td>0xa29fb61f, 0x4f6c, 0x4e15, 0xaf, 0x96, 0xb7, 0x0c, 0xf2, 0x1c,
0xd7, 0x71</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.4.7.16 to 5.26.4.7.17 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters. The return
status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.7.17</td>
<td>0xea84cd69, 0x5550, 0x44a0, 0xbb, 0xe7, 0x0f, 0xc1, 0x5d, 0x08,
0xb8, 0x35</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>2. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.18</td>
<td>0x789c0d97, 0x68d8, 0x4a72, 0xa8, 0x7f, 0x66, 0x37, 0xcb, 0x6b,
0xb8, 0xe0</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.4.7.18 to 5.26.4.7.20 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters, the return
status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.7.19</td>
<td>0x9a991ff0, 0x84af, 0x4290, 0x85, 0x3b, 0x02, 0xe0, 0xb7, 0xe4,
0xe0, 0x28</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.20</td>
<td>0xd90350a1, 0x7e65, 0x435f, 0xa3, 0x8f, 0x24, 0x27, 0xf1, 0x08,
0x8f, 0x5f</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.21</td>
<td>0xdf7f3d8e, 0x492e, 0x46ef, 0xb9, 0x8e, 0x26, 0x06, 0x9e, 0x85,
0x7a, 0x73</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and
<strong>Token.BufferSize</strong> is not large enough.</td>
<td><p>5.26.4.7.21 to 5.26.4.7.23 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and
<strong>Token.BufferSize</strong> is not large enough, the return status
should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.7.22</td>
<td>0x5ff92824, 0x75a9, 0x4e39, 0xa3, 0xa0, 0xc6, 0x2d, 0x42, 0x09,
0x48, 0x78</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.7.23</td>
<td>0x5bd23489, 0xc9df, 0x4ce5, 0x84, 0xe9, 0x51, 0xa1, 0x88, 0xe2,
0x96, 0x3f</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_BUFFER_TOO_SMALL</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_BUFFER_TOO_SMALL</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.24</td>
<td>0x4f23a070, 0xd01c, 0x441c, 0x88, 0x36, 0x26, 0xc4, 0x00, 0x05,
0xda, 0x0b</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and current
operation is aborted by user.</td>
<td><p>5.26.4.7.24 to 5.26.4.7.26 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and current
operation is aborted by user, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.7.25</td>
<td>0xb22cb194, 0xd7db, 0x4141, 0x87, 0x8d, 0xab, 0xb7, 0x76, 0x9a,
0x12, 0xf6</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.26</td>
<td>0x8a946d5c, 0xa820, 0x47c1, 0x83, 0xdf, 0x4b, 0x73, 0x9f, 0x52,
0x89, 0x53</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.27</td>
<td>0x11b9ec6c, 0xff52, 0x4279, 0x9a, 0x07, 0x64, 0x1b, 0xcb, 0xe5,
0x37, 0x73</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a mtftp6
error packet was received.</td>
<td><p>5.26.4.7.27 to 5.26.4.7.29 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a mtftp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.7.28</td>
<td>0x70e67e7f, 0x0a67, 0x4402, 0xa2, 0x63, 0x9a, 0xe9, 0x75, 0xcb,
0x7c, 0x71</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.7.29</td>
<td>0x35b45761, 0x9657, 0x4211, 0xb4, 0xfb, 0xed, 0x68, 0xe1, 0x98,
0xf4, 0x02</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.30</td>
<td>0x6aa2ecf0, 0xb01e, 0x4a8e, 0xb3, 0xdc, 0xd0, 0x54, 0xce, 0xb6,
0xa0, 0x83</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received.</td>
<td><p>5.26.4.7.30 to 5.26.4.7.32 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.7.31</td>
<td>0x6794533c, 0xf4f6, 0x4972, 0x8c, 0xf4, 0x3a, 0xc6, 0x20, 0x20,
0x19, 0x4e</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.7.32</td>
<td>0xda706911, 0x98fd, 0x49a3, 0xa6, 0x55, 0x74, 0x75, 0xb5, 0x5a,
0x0d, 0x4f</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.7.33</td>
<td>0xc80090b9, 0x0876, 0x4959, 0xbd, 0x80, 0x6c, 0x41, 0x40, 0x92,
0xac, 0x48</td>
<td><strong>EFI_MTFTP6_PROTOCOL.ReadFile() - ReadFile()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received.</td>
<td><p>5.26.4.7.33 to 5.26.4.7.35 belong to one case.</p>
<p>1. Call <strong>ReadFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and no
response was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.7.34</td>
<td>0xa8ce4013, 0x648f, 0x46d5, 0xa4, 0x89, 0xd3, 0x33, 0x1a, 0xee,
0x1d, 0x57</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.7.35</td>
<td>0xbb028e8c, 0xf45a, 0x4052, 0x83, 0x3b, 0x45, 0x81, 0xec, 0x1b,
0x62, 0x0f</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
</tr>
</tbody>
</table>


### WriteFile()

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
<td>5.26.4.8.1</td>
<td>0x3123cc65, 0x7cea, 0x4b5e, 0x92, 0xd9, 0x7d, 0x8c, 0xe4, 0x95,
0x3f, 0x4f</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_NOT_STARTED</strong> when the instance hasn’t been
configured.</td>
<td>Call <strong>WriteFile()</strong>when the instance hasn’t been
configured, the return status should be
<strong>EFI_NOT_STARTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.2</td>
<td>0x6738f74e, 0x3f6f, 0x48db, 0xaa, 0x1b, 0x8d, 0x38, 0xf8, 0x19,
0x4a, 0x61</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - Writeile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when
<strong>Token</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>WriteFile()</strong> when <strong>Token</strong> is
<strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.3</td>
<td>0x637d7d38, 0x102d, 0x4382, 0x9f, 0x95, 0x0f, 0xc3, 0x97, 0x84,
0x29, 0xcf</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when
<strong>Token.Filename</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>WriteFile()</strong> when
<strong>Token.Filename</strong> is <strong>NULL</strong>, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.4</td>
<td>0xf39cdb05, 0xd139, 0x4dd7, 0x8c, 0x15, 0x41, 0x2f, 0x8b, 0xde,
0x04, 0xb3</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when
<strong>Token.OptionCount</strong> isn't zero and
<strong>Token.OptionList</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>WriteFile()</strong> when
<strong>Token.OptionCount</strong> isn't zero and
<strong>Token.OptionList</strong> is <strong>NULL</strong>, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.5</td>
<td>0x9d3fcbac, 0xbc54, 0x46d9, 0x85, 0x41, 0x64, 0xe3, 0xaa, 0x41,
0x25, 0x58</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when one or more options
in <strong>Token.OptionList</strong> is wrong format.</td>
<td>Call <strong>WriteFile()</strong> when one or more options in
<strong>Token.OptionList</strong> is wrong format, the return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.6</td>
<td>0x181a05aa, 0xcd53, 0x4ba1, 0xb8, 0xf3, 0x98, 0x09, 0x9b, 0xd4,
0xa7, 0xe1</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when one or more options
in <strong>Token.Buffer</strong> and <strong>Token.PacketNeeded</strong>
are both <strong>NULL</strong>.</td>
<td>Call <strong>WriteFile()</strong> when one or more options in
<strong>Token.Buffer</strong> and <strong>Token.PacketNeeded</strong>
are both <strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.7</td>
<td>0xb820e6cb, 0x5290, 0x4748, 0x94, 0x66, 0x8d, 0xc1, 0x99, 0x2e,
0x12, 0xc1</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when one or more options
in <strong>Token.OverrideData.ServerIp</strong> is not valid unicast
IPv6 address.</td>
<td>Call <strong>WriteFile()</strong> when one or more options in
<strong>Token.OverrideData.ServerIp</strong> is not valid unicast IPv6
address, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.8</td>
<td>0x3854186d, 0x550e, 0x4006, 0xbe, 0xff, 0x1c, 0x52, 0x5b, 0xa4,
0x3e, 0xcf</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_INVALID_PARAMETER</strong> when one or more options
in <strong>Token.OptionList</strong> is not supported.</td>
<td>Call <strong>WriteFile()</strong> when one or more options in
<strong>Token.OptionList</strong> is not supported, the return status
should be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.9</td>
<td>0x54ae8e18, 0xd428, 0x48c1, 0xad, 0x32, 0xb5, 0x51, 0xda, 0x1e,
0x90, 0x7f</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.4.8.9 to 5.26.4.8.10 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.8.10</td>
<td>0xc2e70601, 0xb8d5, 0x4aa6, 0xbb, 0x5c, 0x6e, 0xda, 0x2a, 0xd0,
0xa6, 0x6a</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>2. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.11</td>
<td>0x9e572894, 0x38da, 0x4039, 0x96, 0xc9, 0xaa, 0xfe, 0xa6, 0x48,
0x60, 0x74</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>5.26.4.8.11 to 5.26.4.8.13 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.8.12</td>
<td>0xeba41d25, 0x03d7, 0x41d7, 0xa0, 0x58, 0xa8, 0x90, 0xad, 0x68,
0xa7, 0x0b</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.8.13</td>
<td>0x39afac2f, 0xb620, 0x45e9, 0x8d, 0x82, 0x7a, 0xec, 0x36, 0x9d,
0x19, 0xfb</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.14</td>
<td>0x98410f1a, 0x6f26, 0x45f4, 0x8c, 0x5d, 0x9e, 0x11, 0x19, 0x53,
0xd3, 0xf8</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and current
operation is aborted by user.</td>
<td><p>5.26.4.8.14 to 5.26.4.8.16 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and current
operation is aborted by user, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.8.15</td>
<td>0xbb6d10b9, 0x4466, 0x4f97, 0x9a, 0x3f, 0xa9, 0xa0, 0x7a, 0x49,
0x88, 0x5d</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.16</td>
<td>0x87eff284, 0x80a4, 0x48ae, 0xa1, 0x87, 0x54, 0xa5, 0xf6, 0xd8,
0xcc, 0xcf</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.17</td>
<td>0x84cf72a7, 0x0d57, 0x4519, 0x8d, 0x94, 0x5a, 0x63, 0xeb, 0xff,
0x8c, 0x73</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a mtftp6
error packet was received.</td>
<td><p>5.26.4.8.17 to 5.26.4.8.19 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a mtftp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.8.18</td>
<td>0x35003a00, 0x715d, 0x4f05, 0x80, 0x0d, 0xec, 0xcc, 0x92, 0xed,
0x19, 0x51</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.8.19</td>
<td>0x11ce4fd8, 0x7d75, 0x49ec, 0x8a, 0x2b, 0x98, 0x57, 0xd9, 0xce,
0x5d, 0x66</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.20</td>
<td>0xb1d3d500, 0x4afa, 0x465f, 0x8e, 0xac, 0x79, 0x0d, 0xf9, 0xef,
0x3f, 0xea</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received.</td>
<td><p>5.26.4.8.20 to 5.26.4.8.22 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.8.21</td>
<td>0x42093ba6, 0x54ce, 0x408c, 0x82, 0x0f, 0xce, 0xba, 0xf4, 0x56,
0x58, 0xe9</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.8.22</td>
<td>0xc7ba7541, 0x6d62, 0x4143, 0x8e, 0x18, 0x6e, 0xbb, 0xfe, 0x2c,
0x42, 0xd8</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.8.23</td>
<td>0x08fffd13, 0x7cfb, 0x49ec, 0x8b, 0x02, 0x2a, 0x45, 0xb9, 0x78,
0x1d, 0xcd</td>
<td><strong>EFI_MTFTP6_PROTOCOL.WriteFile() - WriteFile()</strong>
returns <strong>EFI_SUCCESS</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received.</td>
<td><p>5.26.4.8.23 to 5.26.4.8.25 belong to one case.</p>
<p>1. Call <strong>WriteFile()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and no
response was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.8.24</td>
<td>0xeb45268b, 0xa856, 0x4ab8, 0xb4, 0xba, 0x38, 0xf9, 0x35, 0xd7,
0x99, 0x2c</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.8.25</td>
<td>0xa93f3a80, 0xeb22, 0x4ad8, 0xb5, 0x7c, 0xf5, 0x39, 0x7d, 0xe5,
0x39, 0x33</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
</tr>
</tbody>
</table>


### ReadDirectory()

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
<td>5.26.4.9.1</td>
<td>0x1947060b, 0x44a2, 0x4e22, 0x9b, 0xe9, 0x20, 0xf4, 0xa2, 0x9e,
0xb4, 0x2e</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_NOT_STARTED</strong> when
the instance hasn’t been configured.</td>
<td>Call <strong>ReadDirectory()</strong>when the instance hasn’t been
configured, the return status should be
<strong>EFI_NOT_STARTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.2</td>
<td>0x9d2a2470, 0x98de, 0x425a, 0xbb, 0x3f, 0xab, 0x01, 0x84, 0x13,
0xe6, 0x9c</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when <strong>Token</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>ReadDirectory()</strong> when <strong>Token</strong> is
<strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.3</td>
<td>0x6288a172, 0xbc68, 0x49c1, 0xa8, 0x85, 0x56, 0x5a, 0x9e, 0xf9,
0x5c, 0x46</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when <strong>Token.Filename</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>ReadDirectory()</strong> when
<strong>Token.Filename</strong> is <strong>NULL</strong>, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.4</td>
<td>0xe95a938b, 0x7d16, 0x4b40, 0xbd, 0x23, 0x81, 0x7b, 0xf6, 0xf1,
0xff, 0xb4</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when <strong>Token.OptionCount</strong> isn't zero and
<strong>Token.OptionList</strong> is <strong>NULL</strong>.</td>
<td>Call <strong>ReadDirectory()</strong> when
<strong>Token.OptionCount</strong> isn't zero and
<strong>Token.OptionList</strong> is <strong>NULL</strong>, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.5</td>
<td>0x4ec4e899, 0x9f53, 0x461a, 0xb3, 0xe4, 0x21, 0xe4, 0x1e, 0x66,
0x56, 0x21</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when one or more options in <strong>Token.OptionList</strong> is wrong
format.</td>
<td>Call <strong>ReadDirectory()</strong> when one or more options in
<strong>Token.OptionList</strong> is wrong format, the return status
should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.6</td>
<td>0xbb6ac976, 0xbe0b, 0x4329, 0x98, 0xe3, 0x1f, 0x2d, 0xc8, 0x63,
0x8f, 0x9a</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when one or more options in <strong>Token.Buffer</strong> and
<strong>Token.CheckPacket</strong> are both <strong>NULL</strong>.</td>
<td>Call <strong>ReadDirectory()</strong> when one or more options in
<strong>Token.Buffer</strong> and <strong>Token.CheckPacket</strong> are
both <strong>NULL</strong>, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.7</td>
<td>0xa41fa6b3, 0xc128, 0x451f, 0x82, 0xf4, 0xf8, 0x92, 0x8e, 0xa8,
0x61, 0xfd</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when one or more options in <strong>Token.OverrideData.ServerIp</strong>
is not valid unicast IPv6 address.</td>
<td>Call <strong>ReadDirectory()</strong> when one or more options in
<strong>Token.OverrideData.ServerIp</strong> is not valid unicast IPv6
address, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.8</td>
<td>0xed4d5f77, 0x7856, 0x4c4a, 0x9a, 0x6b, 0x19, 0x66, 0xc7, 0xf6,
0x80, 0xfb</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_INVALID_PARAMETER</strong>
when one or more options in <strong>Token.OptionList</strong> is not
supported.</td>
<td>Call <strong>ReadDirectory()</strong> when one or more options in
<strong>Token.OptionList</strong> is not supported, the return status
should be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.9</td>
<td>0xf6439066, 0xb46e, 0x484e, 0x9a, 0x99, 0xfe, 0xa9, 0xaf, 0x72,
0xf9, 0xce</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_ABORTED</strong> when
current operation is aborted by user.</td>
<td>Call <strong>ReadDirectory()</strong> when current operation is
aborted by user, the return status should be
<strong>EFI_ABORTED</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.10</td>
<td>0xd8f2b214, 0xbfc2, 0x4344, 0x85, 0x13, 0xfc, 0x07, 0x04, 0x3f,
0x63, 0x6f</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_TFTP_ERROR</strong> when a
mtftp6 error packet was received.</td>
<td>Call <strong>ReadDirectory()</strong> when a mtftp6 error packet was
received, the return status should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.11</td>
<td>0x74cbaed3, 0x1521, 0x4677, 0x83, 0xb0, 0xca, 0xac, 0x84, 0x92,
0x27, 0x68</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_PORT_UNREACHABLE</strong>
when a icmp6 port unreachable error packet was received.</td>
<td>Call <strong>ReadDirectory()</strong> when a icmp6 port unreachable
error packet was received, the return status should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.12</td>
<td>0x71038101, 0x41ba, 0x416e, 0xa7, 0xb3, 0xd6, 0x12, 0x27, 0x8f,
0xb9, 0xe5</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_TIMEOUT</strong> when no
response was received.</td>
<td>Call <strong>ReadDirectory()</strong> when no response was received,
the return status should be <strong>EFI_TIMEOUT</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.13</td>
<td>0x177b35e7, 0x8e93, 0x48c4, 0x8f, 0x19, 0x7e, 0xe7, 0xf9, 0x9d,
0x65, 0x60</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters.</td>
<td><p>5.26.4.9.13 to 5.26.4.9.14 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.9.14</td>
<td>0x63dd12dd, 0x62e4, 0x40d3, 0x88, 0x30, 0xac, 0x2e, 0x61, 0xd2,
0x08, 0xb8</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>2. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.15</td>
<td>0xbc2d0220, 0xa92b, 0x4281, 0x82, 0xf1, 0x45, 0xf1, 0x98, 0x10,
0x33, 0x05</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters.</td>
<td><p>5.26.4.9.15 to 5.26.4.9.17 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.9.16</td>
<td>0xc495566f, 0x31a5, 0x47d3, 0x97, 0x50, 0xdf, 0xe9, 0xed, 0xfd,
0xe7, 0xfc</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.9.17</td>
<td>0xb734f8cc, 0x91c2, 0x4ce8, 0xa3, 0x11, 0x70, 0x70, 0xb8, 0x27,
0x6b, 0x03</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.18</td>
<td>0xce7b5436, 0x3e80, 0x46d1, 0xbc, 0x6a, 0x04, 0x05, 0x91, 0xd8,
0xf2, 0x00</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters, <strong>Token.Event</strong> is not <strong>NULL</strong>
and current operation is aborted by user.</td>
<td><p>5.26.4.9.18 to 5.26.4.9.20 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and current
operation is aborted by user, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.9.19</td>
<td>0x06cc2106, 0x12e0, 0x4b26, 0x82, 0x84, 0xb6, 0x45, 0x26, 0x56,
0xb7, 0x67</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.20</td>
<td>0x2f8d4207, 0xcaa0, 0x4fe8, 0xae, 0x18, 0x09, 0xfc, 0xd8, 0x1f,
0x60, 0xb1</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_ABORTED</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.21</td>
<td>0xf19e2441, 0x2e9d, 0x4754, 0xaa, 0x1c, 0x9d, 0xff, 0x5d, 0xac,
0x7b, 0xfb</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters, <strong>Token.Event</strong> is not <strong>NULL</strong>
and a mtftp6 error packet was received.</td>
<td><p>5.26.4.9.21 to 5.26.4.9.23 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a mtftp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.9.22</td>
<td>0x6d29ada4, 0xb541, 0x4ed1, 0x9c, 0x54, 0x42, 0x97, 0xc6, 0x99,
0xa9, 0x2f</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.9.23</td>
<td>0x7ee4d2f0, 0x43a5, 0x4730, 0x88, 0x00, 0x7f, 0x72, 0xcd, 0x76,
0x6e, 0xb5</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TFTP_ERROR</strong>.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.24</td>
<td>0x24b159a5, 0x0d03, 0x408d, 0x84, 0x3d, 0x5b, 0xfd, 0xb8, 0xf7,
0x10, 0xc4</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters, <strong>Token.Event</strong> is not <strong>NULL</strong>
and a icmp6 error packet was received.</td>
<td><p>5.26.4.9.24 to 5.26.4.9.26 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and a icmp6
error packet was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.26.4.9.25</td>
<td>0x450a81e4, 0xf424, 0x4399, 0x9a, 0xb9, 0xef, 0x2e, 0xa9, 0x4a,
0x7e, 0x46</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="odd">
<td>5.26.4.9.26</td>
<td>0xc2b9002f, 0x9183, 0x4a4b, 0xba, 0x26, 0x3f, 0x72, 0x93, 0xed,
0xf0, 0xa4</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_PORT_UNREACHABLE</strong>.</td>
</tr>
<tr class="even">
<td>5.26.4.9.27</td>
<td>0x1aef9df8, 0xcf77, 0x449a, 0xa1, 0x6b, 0x0b, 0x8d, 0x8e, 0x4a,
0xf9, 0x06</td>
<td><strong>EFI_MTFTP6_PROTOCOL. ReadDirectory() -
ReadDirectory()</strong> returns <strong>EFI_SUCCESS</strong> with valid
parameters, <strong>Token.Event</strong> is not <strong>NULL</strong>
and a icmp6 error packet was received.</td>
<td><p>5.26.4.9.27 to 5.26.4.9.29 belong to one case.</p>
<p>1. Call <strong>ReadDirectory()</strong> with valid parameters,
<strong>Token.Event</strong> is not <strong>NULL</strong> and no
response was received, the return status should be
<strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.26.4.9.28</td>
<td>0xb5398e7d, 0x02cb, 0x4fd2, 0xa9, 0xdd, 0xd9, 0x75, 0x8f, 0x32,
0xd9, 0x26</td>
<td>The <strong>Token.Event</strong> should be signaled.</td>
<td>2. The <strong>Token.Event</strong> should be signaled.</td>
</tr>
<tr class="even">
<td>5.26.4.9.29</td>
<td>0x279e1bfa, 0x5db9, 0x44ba, 0xbb, 0x3c, 0xe4, 0x3b, 0xf1, 0xeb,
0xa8, 0x70</td>
<td>The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
<td>3. The <strong>Token.Status</strong> should be
<strong>EFI_TIMEOUT</strong>.</td>
</tr>
</tbody>
</table>



### Poll()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.26.4.10.1 | 0xdfb24a28, 0xc61c, 0x4ec0, 0x9e, 0x78, 0x3a, 0xcf, 0x85, 0x9f, 0xa8, 0x0e | **EFI_MTFTP6_PROTOCOL. Poll() – Poll()** returns **EFI_NOT_STARTED** when the instance hasn’t been configured. | Call **Poll()**when the instance hasn’t been configured, the return status should be **EFI_NOT_STARTED**. |

