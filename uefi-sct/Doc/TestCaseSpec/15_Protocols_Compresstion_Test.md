# Protocols Compression Test

## EFI_DECOMPRESS_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_DECOMPRESS_PROTOCOL Section.

### GetInfo()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 15%" />
<col style="width: 26%" />
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
<td>5.13.1.1.1</td>
<td>0xb4929cbe, 0x0d83, 0x481f, 0x89, 0xc7, 0xb8, 0xbd, 0x49, 0x05,
0x7c, 0xae</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> returns <strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Get the Compressed file name and uncompressed file size from
the profile.</p>
<p>2. Read the Compressed file into memory</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.1.2</td>
<td>0x1c5d4afb, 0x66b2, 0x4ff3, 0xb9, 0x20, 0x6a, 0x21, 0x32, 0x62,
0x9f, 0xae</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> returns a <em>DestinationSize</em> that is
equal to the Uncompressed File Size.</td>
<td><p>1. Get the Compressed file name and uncompressed file size from
the profile.</p>
<p>2. Read the Compressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>The returned <em>DestinationSize</em> should equal the Uncompressed
File Size gotten from the profile.</p></td>
</tr>
<tr class="even">
<td>5.13.1.1.3</td>
<td>0x01a92787, 0x0d15, 0x4213, 0x92, 0x06, 0x8a, 0x3a, 0xb4, 0xa3,
0xba, 0x54</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> the second time returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Get the Compressed file name and uncompressed file size from
the profile.</p>
<p>2. Read the Compressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>GetInfo()</strong> again.</p>
<p>The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.1.4</td>
<td>0xb80b38e3, 0x3f4c, 0x43e0, 0xb8, 0x6d, 0x5b, 0x01, 0x38, 0xbd,
0x0f, 0x3e</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> the second time returns a
<em>DestinationSize</em> that is equal to the <em>DestinationSize</em>
returned after the first call.</td>
<td><p>1. Get the Compressed file name and uncompressed file size from
the profile.</p>
<p>2. Read the Compressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>GetInfo()</strong> again.</p>
<p>The returned <em>DestinationSize</em> should be the same value as the
first time.</p></td>
</tr>
<tr class="even">
<td>5.13.1.1.5</td>
<td>0x43ee9ff0, 0x4867, 0x4fe6, 0xac, 0x09, 0x72, 0x0a, 0x33, 0x8b,
0x80, 0xd8</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> the second time returns a
<em>ScratchSize</em> that is equal to the <em>ScratchSize</em> returned
after the first call.</td>
<td><p>1. Get the Compressed file name and uncompressed file size from
the profile.</p>
<p>2. Read the Compressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>GetInfo()</strong> again.</p>
<p>The returned <em>ScratchSize</em> should be the same value as the
first time.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.1.6</td>
<td>0x66c06d59, 0x77ab, 0x4bc6, 0x98, 0x20, 0xbf, 0x01, 0x60, 0xd6,
0x1e, 0x6a</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.GetInfo</strong> - Calling
<strong>GetInfo()</strong> with <em>SourceSize</em> &lt; 8 returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>Call <strong>GetInfo()</strong> with <em>SourceSize</em> &lt;
8.</p>
<p>The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>


### Decompress()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 15%" />
<col style="width: 26%" />
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
<td>5.13.1.2.1</td>
<td>0x37d2514e, 0x27f0, 0x4182, 0xb7, 0x13, 0x14, 0xf4, 0xbf, 0x53,
0xbb, 0xae</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> – Calling
<strong>Decompress()</strong> on a 0 length file returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Get the Compressed file name and uncompressed file name from
the profile.</p>
<p>2. Read the Compressed file and uncompressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>Decompress()</strong> with the compressed file
buffer.</p>
<p>The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.2.2</td>
<td>0xf2665735, 0x8992, 0x47bc, 0xb2, 0x99, 0x8a, 0x00, 0x32, 0xab,
0x59, 0x93</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> - Calling
<strong>Decompress()</strong> on a 0 length file does not modify the
buffer.</td>
<td><p>1. Get the Compressed file name and uncompressed file name from
the profile.</p>
<p>2. Read the Compressed file and uncompressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>Decompress()</strong> with the compressed file
buffer.</p>
<p>If the uncompressed file size is 0, the destination buffer should not
be modified.</p></td>
</tr>
<tr class="even">
<td>5.13.1.2.3</td>
<td>0x8eceea13, 0x34ce, 0x43af, 0xbf, 0x9c, 0xb8, 0x3d, 0xe6, 0x32,
0x29, 0x69</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> - Calling
<strong>Decompress()</strong> on a non‑0 file returns
<strong>EFI_SUCCESS</strong>.</td>
<td><p>1. Get the Compressed file name and uncompressed file name from
the profile.</p>
<p>2. Read the Compressed file and uncompressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>Decompress()</strong> with the compressed file
buffer.</p>
<p>The returned status should be <strong>EFI_SUCCESS</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.2.4</td>
<td>0xd8aa9038, 0xc3d1, 0x4f9c, 0x9d, 0xbb, 0x3c, 0xc8, 0x6d, 0xee,
0xd1, 0xe6</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> – After calling
<strong>Decompress()</strong> on a non‑0 file, the Decompressed data is
equal to the Uncompressed data.</td>
<td><p>1. Get the Compressed file name and uncompressed file name from
the profile.</p>
<p>2. Read the Compressed file and uncompressed file into memory.</p>
<p>3. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>4. Call <strong>Decompress()</strong> with the compressed file
buffer.</p>
<p>If the uncompressed file size is non-0, the Decompressed data should
be equal to the Uncompressed file data.</p></td>
</tr>
<tr class="even">
<td>5.13.1.2.5</td>
<td>0x9e6e6f21, 0x15f3, 0x4b0c, 0x9a, 0x9a, 0x17, 0xfc, 0xab, 0x5c,
0x54, 0x23</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> - After calling
<strong>Decompress()</strong> with an invalid compressed file, the
returned status is <strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>1. Get the invalid compressed format file name from the
profile.</p>
<p>2. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>3. Call <strong>Decompress()</strong> with an invalid compress format
buffer.</p>
<p>The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="odd">
<td>5.13.1.2.6</td>
<td>0xe145f85e, 0xcc48, 0x42d4, 0xab, 0x48, 0xb5, 0x16, 0x2f, 0xc3,
0xef, 0xae</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> - Calling
<strong>Decompress()</strong> with an incorrect <em>SourceSize</em> (
<em>SourceSize</em> - 1 ) returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>1. Read the Compressed file into memory and save the buffer
pointer.</p>
<p>2. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>3. Call <strong>Decompress()</strong> with incorrect
<em>SourceSize</em> ( <em>SourceSize</em> - 1 )</p>
<p>The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
<tr class="even">
<td>5.13.1.2.7</td>
<td>0xfdc75fd3, 0x3a02, 0x48e5, 0x8d, 0x7f, 0x0b, 0x14, 0x75, 0xb5,
0xcf, 0x1c</td>
<td><strong>EFI_DECOMPRESS_PROTOCOL.Decompress</strong> - Calling
<strong>Decompress()</strong> with <em>SourceSize</em> &lt; 8 returns
<strong>EFI_INVALID_PARAMETER</strong>.</td>
<td><p>1. Read the Compressed file into memory and save the buffer
pointer.</p>
<p>2. Call <strong>GetInfo()</strong> to retrieve the decompression
info.</p>
<p>3. Call <strong>Decompress()</strong> with <em>SourceSize</em> &lt;
8.</p>
<p>The returned status should be
<strong>EFI_INVALID_PARAMETER</strong>.</p></td>
</tr>
</tbody>
</table>

