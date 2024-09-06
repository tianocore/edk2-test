# Random Number Generator Protocols

## EFI_RNG_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_RNG_PROTOCOL Section.

### GetInfo ()

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
<td>5.33.4.1.1</td>
<td>0xb0aeea8a, 0xcd05, 0x4254, 0xb2, 0xcb, 0x30, 0xbb, 0x90, 0x87,
0x73, 0xc6</td>
<td><strong>EFI_RNG_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>Call <strong>GetInfo() t</strong>o get the</p>
<p>RNGAlgorithmListSize.</p>
<p>Allocate a list buffer with the</p>
<p>RNGAlgorithmListSize gotten from step1.</p>
<p>3. Call <strong>GetInfo()</strong> with the new allocated buffer, the
return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.33.4.1.2</td>
<td>0x50df54e5, 0x1449, 0x4a34, 0x95, 0x6a, 0xb6, 0x61, 0x66, 0xc2,
0xd5, 0x8a</td>
<td><strong>EFI_RNG_PROTOCOL.GetInfo() - GetInfo()</strong> returns
valid algorithm with valid parameters.</td>
<td><p>Call <strong>GetInfo()</strong> to get the</p>
<p>RNGAlgorithmListSize.</p>
<p>Allocate a list buffer with the</p>
<p>RNGAlgorithmListSize gotten from step1.</p>
<p>Call <strong>GetInfo()</strong> with the new allocated</p>
<p>buffer, the return status should be <strong>EFI_SUCCESS</strong>.</p>
<p>Compare the Algorithm gotten from</p>
<p>Step3 with the given algorithms, the result should be
success.</p></td>
</tr>
<tr class="even">
<td>5.33.4.1.3</td>
<td>0x0db3b0d2, 0x859f, 0x4682, 0x87, 0x67, 0x62, 0x35, 0x67, 0x91,
0xb7, 0x9d</td>
<td><strong>EFI_RNG_PROTOCOL.GetInfo() - GetInfo()</strong> returns
<strong>EFI_BUFFER_TOO_SMALL</strong> with small RNGAlgorithmListSize
and returns valid size</td>
<td><p>Call <strong>GetInfo()</strong> with small RNGAlgorithmListSize,
the return</p>
<p>status should be <strong>EFI_BUFFER_TOO_SMALL</strong> and returns
valid size</p></td>
</tr>
</tbody>
</table>


### GetRNG()

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
<td>5.33.4.2.1</td>
<td>0x4a54a35e, 0x66ac, 0x4c2e, 0x92, 0xd8, 0x7b, 0x26, 0x3d, 0x8a,
0x77, 0xa8</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_SUCCESS</strong> with valid parameters.</td>
<td><p>Call <strong>GetInfo()</strong> to get the</p>
<p>RNGAlgorithmListSize.</p>
<p>Allocate a list buffer with the</p>
<p>RNGAlgorithmListSize gotten from step1.</p>
<p>Call <strong>GetInfo()</strong> with the new allocated</p>
<p>Buffer.</p>
<p>Call <strong>GetRNG()</strong> with valid parameters,</p>
<p>the return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.33.4.2.2</td>
<td>0xe3d11e22, 0xeddb, 0x40c4, 0x8f, 0x6d, 0x25, 0x79, 0x33, 0xea,
0x62, 0xf8</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_SUCCESS</strong> with default algorithm.</td>
<td><p>Call <strong>GetRNG()</strong> with default algorithm,</p>
<p>the return status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="even">
<td>5.33.4.2.3</td>
<td>0xe79e5379, 0xd4dc, 0x4624, 0x88, 0x05, 0x09, 0x46, 0x1c, 0x09,
0x78, 0x28</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when RNGValueLength is 0.</td>
<td>Call <strong>GetRNG()</strong>when RNGValueLength is 0, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.33.4.2.4</td>
<td>0x76ac3e4c, 0x5f59, 0x4c21, 0x82, 0x0a, 0xe4, 0x24, 0xc2, 0xef,
0x36, 0x14</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when RNGValue is NULL.</td>
<td>Call <strong>GetRNG()</strong>when RNGValue is NULL, the return
status should be <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.33.4.2.5</td>
<td>0x27451869, 0x357d, 0x4e92, 0xb8, 0xb0, 0xb8, 0xc5, 0xba, 0xb9,
0xa4, 0xe9</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when RNGAlgorithm is NULL and
RNGValueLength is 0.</td>
<td>Call <strong>GetRNG()</strong>when RNGAlgorithm is NULL and
RNGValueLength is 0, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>5.33.4.2.6</td>
<td>0x31ce0e8, 0x3604, 0x4489, 0x93, 0x6c, 0x60, 0x8c, 0x9b, 0x2c, 0xf8,
0xf4</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_INVALID_PARAMETER</strong> when RNGValueLength is 0 after
the RNGAlgorithm is freed.</td>
<td>Call <strong>GetRNG()</strong>when RNGValue is NULL after the
RNGAlgorithm is freed, the return status should be
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>5.33.4.2.7</td>
<td>0x7a4ea182, 0xa4cd, 0x441d, 0x98, 0xd7, 0x73, 0x65, 0x87, 0x6f,
0xfa, 0x77</td>
<td><strong>EFI_RNG_PROTOCOL.GetRNG() - GetRNG()</strong> returns
<strong>EFI_UNSUPPORTED</strong> when RNGAlgorithm is unsupported.</td>
<td>Call <strong>GetRNG()</strong>when RNGAlgorithm is unsupported, the
return status should be <strong>EFI_UNSUPPORTED</strong>.</td>
</tr>
</tbody>
</table>

