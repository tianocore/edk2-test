# Protocols Security Test

## HASH Protocol Test

**Reference Document:**

*UEFI Specification*, EFI_HASH_PROTOCOL Section.

Configuration

- Call “**EFI_HASH_SERVICE_BINDING_PROTOCOL.CreateChild()**” before
  testing.

- Call “**EFI_HASH_SERVICE_BINDING_PROTOCOL.DestoryChild**” after
  testing.

- Execute testing of 25.4.1.1~25.4.1.3 and 25.4.2.1.1~25.4.2.5.2 for
  every hash protocol(SHA-x/MD5).

Required Elements

### GetHashSize()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 15%" />
<col style="width: 22%" />
<col style="width: 49%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>25.4.1.0.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xae</td>
<td>check input parameters of testing
<strong>EFI_HASH_PROTOCOL.GetHashSize()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>25.4.1.1.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa2</td>
<td><strong>EFI_HASH_PROTOCOL.GetHashSize()</strong> <em>HashSize</em>
invalid checking test.</td>
<td>Call <strong>GetHashSize()</strong> with
<strong>(Hashsize=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.4.1.2.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa3</td>
<td><strong>EFI_HASH_PROTOCOL.GetHashSize()</strong> HashAlgorithm
invalid checking test A.</td>
<td>Call <strong>GetHashSize()</strong> with
<strong>(HashAlgorithm=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>25.4.1.2.2</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa4</td>
<td><strong>EFI_HASH_PROTOCOL.GetHashSize()</strong> HashAlg invalid
checking test B.</td>
<td>Call <strong>GetHashSize()</strong> with <strong>(HashAlgorithm
invalid)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.4.1.3.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa5</td>
<td><strong>EFI_HASH_PROTOCOL.GetHashSize()</strong> get
<em>HashSize</em> of the special HashAlgorithm.</td>
<td><p>Call <strong>GetHashSize()</strong> with <strong>(HashAlgorithm
=SHA-x/MD5)</strong> should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
</tbody>
</table>


### Hash()

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
<td>25.4.2.0.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xae</td>
<td>check input parameters of testing <strong>EFI_HASH_PROTOCOL.
Hash()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>25.4.2.1.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa6</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> Message invalid checking
test.</td>
<td>Call <strong>Hash()</strong> with <strong>(Message=NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.4.2.1.2</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa7</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> Hash invalid checking
test.</td>
<td>Call <strong>Hash()</strong> with <strong>(Hash=NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>25.4.2.2.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa8</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> HashAlgorithm invalid
checking test.</td>
<td>Call <strong>Hash()</strong> with
<strong>(HashAlgorithm=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.4.2.2.2</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa9</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong>HashAlgorithm invalid
checking test.</td>
<td>Call <strong>Hash()</strong> with <strong>invalid
HashAlgorithm</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>25.4.2.3.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xaa</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> Extend invalid checking
test.</td>
<td>Call <strong>Hash()</strong> with <strong>(HashAlgorithm=NULL and
Extend=TRUE)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.4.2.4.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xab</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> hash some testing
data.</td>
<td><p>Call <strong>Hash()</strong> with <strong>(Extend=FALSE)</strong>
should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>25.4.2.4.2</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xac</td>
<td>Verify hash result getting from <strong>EFI_HASH_PROTOCOL.
Hash()</strong> (25.4.2.4.1)</td>
<td>check hash result getting from <strong>(25.4.2.4.1)</strong> correct
or not.</td>
</tr>
<tr class="even">
<td>25.4.2.5.1</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xad</td>
<td><strong>EFI_HASH_PROTOCOL. Hash()</strong> hash some extend testing
data.</td>
<td><p>Call <strong>Hash()</strong> with <strong>(Extend=TRUE)</strong>
should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>25.4.2.5.2</td>
<td>0xf2db2578, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xae</td>
<td>Verify hash result getting from <strong>EFI_HASH_PROTOCOL.
Hash()</strong> (25.4.2.5.1)</td>
<td>check extend hash result getting from <strong>(25.4.2.5.1)</strong>
correct or not.</td>
</tr>
</tbody>
</table>



## AUTHENTICATION_INFO Protocol Test

**Reference Document:**

*UEFI* *Specification*, EFI_AUTHENTICATION_INFO_PROTOCOL Section.

Configuration

Required: prepare testing data by calling
**EFI_AUTHENTICATION_INFO_PROTOCOL.Set()** before testing of **Get()**.

Required Elements

### Get()

<table>
<colgroup>
<col style="width: 13%" />
<col style="width: 15%" />
<col style="width: 31%" />
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
<td>25.1.1.1.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa3</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Get()</strong> get
authentication_info of the special <em>ControllerHandle</em>.</td>
<td><p>Call <strong>Get()</strong> with <strong>(valid</strong>
<em>ControllerHandle</em><strong>)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>25.1.1.2.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa4</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Get()</strong>
<em>ControllerHandle</em> invalid checking test.</td>
<td>Call <strong>Get()</strong> with
<strong>(</strong><em>ControllerHandle</em><strong>=NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.1.1.3.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa5</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Get()</strong>parameter
<em>Buffer</em> invalid checking test.</td>
<td>Call <strong>Get()</strong> with
<strong>(</strong><em>Buffer</em><strong>=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>




### Set()

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
<td>25.1.2.1.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa6</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Set()</strong> set
authentication_info of the special <em>ControllerHandle</em>.</td>
<td><p>Call <strong>Set()</strong> with <strong>(valid</strong>
<em>ControllerHandle</em> <strong>and</strong>
<em>Buffer</em><strong>)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>25.1.2.2.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa7</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Set()</strong>
<em>ControllerHandle</em> invalid checking test.</td>
<td>Call <strong>Set()</strong> with
<strong>(</strong><em>ControllerHandle</em><strong>=NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>25.1.2.3.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa8</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Set()</strong>parameter
<em>Buffer</em> invalid checking test.</td>
<td>Call <strong>Set()</strong> with <strong>(Buffer=NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>25.1.2.4.1</td>
<td>0xf2db2579, 0xdc54, 0x4896, 0x83, 0x7f, 0x8d, 0xab, 0x41, 0xfb,
0xde, 0xa9</td>
<td><strong>EFI_AUTHENTICATION_INFO_PROTOCOL.Set()</strong>parameter
<em>length</em> invalid checking test.</td>
<td>Call <strong>Set()</strong> with
<strong>(GenericAuthenticationNodeStruct.length&lt;18)</strong> should
return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>


## EFI_HASH2_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_HASH2_PROTOCOL Section.

### GetHashSize ()

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
<td id="section-7" class="unnumbered">25.2.1.1.1</td>
<td
id="xf70cb8e0-0x2c12-0x4976-0xaf-0xc9-0xac-0x90-0xda-0xae-0x6e-0x20"
class="unnumbered">0xf70cb8e0, 0x2c12, 0x4976, 0xaf, 0xc9, 0xac, 0x90,
0xda, 0xae, 0x6e, 0x20</td>
<td
id="efi_hash2_protocol.-gethashsize---gethashsize-returns-efi_success-with-valid-parameters-and-hashsize-match-the-hashalgorithm."
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. GetHashSize() -
GetHashSize() returns EFI_SUCCESS with valid parameters and HashSize
match the HashAlgorithm.</strong></td>
<td
id="call-gethashsize-with-the-valid-parameters-the-return-status-should-be-efi_success-and-returned-hashsize-should-match-the-hashalgorithm."
class="unnumbered">1. Call <strong>GetHashSize() with the valid
parameters, the return status should be EFI_SUCCESS and returned
HashSize should match the HashAlgorithm.</strong></td>
</tr>
<tr class="odd">
<td id="section-8" class="unnumbered">25.2.1.1.2</td>
<td
id="xb86858d8-0xcb57-0x4978-0x9d-0xed-0xe7-0xc7-0xb1-0x6-0x75-0xd7"
class="unnumbered">0xb86858d8, 0xcb57, 0x4978, 0x9d, 0xed, 0xe7, 0xc7,
0xb1, 0x6, 0x75, 0xd7</td>
<td id="efi_hash2_protocol.-gethashsize---gethashsize"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. GetHashSize() -
GetHashSize()</strong>
<strong>returns EFI_UNSUPPORTED with
unsupported</strong> <span id="hashalgorithm-or-hashalgorithm-being-null."
class="unnumbered"><strong>HashAlgorithm or HashAlgorithm being
NULL.</strong></td>
<td
id="call-gethashsize-with-unsupported-hashalgorithm-or-hashalgorithm-being-null-the-return-status-should-be-efi_unsupported."
class="unnumbered">1. Call <strong>GetHashSize() with unsupported
HashAlgorithm or HashAlgorithm being NULL, the return status should be
EFI_UNSUPPORTED.</strong></td>
</tr>
<tr class="even">
<td id="section-9" class="unnumbered">25.2.1.1.3</td>
<td
id="x9a001932-0x3abd-0x4cca-0x88-0xb5-0xdb-0xa1-0x58-0xc5-0xdb-0xef"
class="unnumbered">0x9a001932, 0x3abd, 0x4cca, 0x88, 0xb5, 0xdb, 0xa1,
0x58, 0xc5, 0xdb, 0xef</td>
<td id="efi_hash2_protocol.-gethashsize---gethashsize-1"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. GetHashSize() -
GetHashSize()</strong>
<strong>returns EFI_INVALID_PARAMETER when HashSize
is NULL.</strong></td>
<td
id="call-gethashsize-when-hashsize-is-null-the-return-status-should-be-efi_invalid_parameter."
class="unnumbered">1. Call <strong>GetHashSize() when HashSize is NULL,
the return status should be EFI_INVALID_PARAMETER.</strong></td>
</tr>

</tbody>
</table>


### Hash()

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
<td>25.2.1.2.1</td>
<td>0xf6905190, 0x3664, 0x4ff9, 0xac, 0x68, 0xce, 0x78, 0x24, 0x6b,
0x2a, 0x51</td>
<td><p>EFI_HASH2_PROTOCOL. Hash() - </p>
<p>Hash() returns EFI_SUCCESS with valid parameters and Hash2Out should
be correct.</p></td>
<td><p>1. Call GetHashSize() to get the</p>
<p>supported HashAlgorithm.</p>
<p>2. Call Hash() with the supported</p>
<p>HashAlgorithm. The return status should be EFI_SUCCESS. Hash ourput
should be correct.</p></td>
</tr>
<tr class="odd">
<td>25.2.1.2.2</td>
<td>0x89690c0c, 0x63c1, 0x40ab, 0x9b, 0x91, 0xfe, 0xd2, 0x32, 0x1a,
0x3e, 0x99</td>
<td><p>EFI_HASH2_PROTOCOL. Hash() - Hash() </p>
<p>returns EFI_UNSUPPORTED with unsupported HashAlgorithm or
HashAlgorithm being NULL.</p></td>
<td>1. Call Hash() with unsupported HashAlgorithm or HashAlgorithm being
NULL, the return status should be EFI_UNSUPPORTED.</td>
</tr>
<tr class="even">
<td>25.2.1.2.3</td>
<td>0xb9cceaa1, 0x3b8f, 0x45e3, 0x8a, 0x27, 0x99, 0x45, 0x3e, 0xb4,
0xd1, 0xbb</td>
<td><p>EFI_HASH2_PROTOCOL. Hash() - Hash() </p>
<p>returns EFI_INVALID_PARAMETER when Hash is NULL.</p></td>
<td>1. Call Hash() when Hash is NULL, the return status should be
EFI_INVALID_PARAMETER.</td>
</tr>

</tbody>
</table>


### HashInit()

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
<td id="section-12" class="unnumbered">25.2.1.3.1</td>
<td
id="x644e5fa7-0x3d9b-0x4a7b-0xb1-0x4e-0x43-0x34-0x28-0xf1-0x60-0xdb"
class="unnumbered">0x644e5fa7, 0x3d9b, 0x4a7b, 0xb1, 0x4e, 0x43, 0x34,
0x28, 0xf1, 0x60, 0xdb</td>
<td id="efi_hash2_protocol.-hashinit--"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashInit() -</strong>
<strong>HashInit() returns EFI_UNSUPPORTED with
unsupported HashAlgorithm or HashAlgorithm being
NULL.</strong></td>
<td
id="call-hashinit-with-unsupported-hashalgorithm-or-hashalgorithm-being-null-the-return-status-should-be-efi_unsupported."
class="unnumbered">1. Call <strong>HashInit() with unsupported
HashAlgorithm or HashAlgorithm being NULL, the return status should be
EFI_UNSUPPORTED.</strong></td>
</tr>
<tr class="odd">
<td id="section-13" class="unnumbered">25.2.1.3.2</td>
<td
id="x622e2357-0xc5ff-0x46b7-0xab-0xe7-0xdb-0x5e-0x76-0xbd-0xca-0xa9"
class="unnumbered">0x622e2357, 0xc5ff, 0x46b7, 0xab, 0xe7, 0xdb, 0x5e,
0x76, 0xbd, 0xca, 0xa9</td>
<td id="efi_hash2_protocol.-hashinit---1"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashInit() -</strong>
<strong>HashInit() returns
EFI_ALREADY_STARTED</strong> <strong>when it follows the call to
HashInit().</strong></td>
<td
id="call-hashinit-when-it-follows-the-call-to-hashinit-the-return-status-should-be-efi_already_started."
class="unnumbered">1. Call <strong>HashInit() when it follows the call
to HashInit(), the return status should be
EFI_ALREADY_STARTED.</strong></td>
</tr>
<tr class="even">
<td id="section-14" class="unnumbered">25.2.1.3.3</td>
<td
id="x69c8ed23-0xf7fd-0x4122-0xb3-0x1a-0x46-0xf8-0x48-0x11-0xa5-0x77"
class="unnumbered">0x69c8ed23, 0xf7fd, 0x4122, 0xb3, 0x1a, 0x46, 0xf8,
0x48, 0x11, 0xa5, 0x77</td>
<td id="efi_hash2_protocol.-hashinit---hashinit"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashInit() -
HashInit()</strong><strong>returns EFI_ALREADY_STARTED</strong>
<strong>when it follows the call to HashUpdate().</strong></td>
<td
id="call-hashinit-when-it-follows-the-call-to-hashupdate-the-return-status-should-be-efi_already_started."
class="unnumbered">1. Call <strong>HashInit() when it follows the call
to HashUpdate(), the return status should be
EFI_ALREADY_STARTED.</strong></td>
</tr>

</tbody>
</table>



### HashUpdate()

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
<td id="section-17" class="unnumbered">25.2.1.4.1</td>
<td
id="xa6a79ffd-0x7e93-0x4302-0xb5-0xaf-0xe5-0x43-0xc5-0x16-0x35-0x95"
class="unnumbered">0xa6a79ffd, 0x7e93, 0x4302, 0xb5, 0xaf, 0xe5, 0x43,
0xc5, 0x16, 0x35, 0x95</td>
<td id="efi_hash2_protocol.-hashupdate--"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashUpdate() -</strong>
<strong>HashUpdate() returns EFI_NOT_READY when it is
not preceded by a call to HashInit().</strong></td>
<td
id="call-hashupdate-when-it-is-not-preceded-by-the-call-to-hashinit"
class="unnumbered"><strong>1. Call HashUpdate() when it is not preceded
by the call to HashInit(),</strong><span id="the-return-status-should-be-efi_not_ready."
class="unnumbered"><strong>the return status should be
EFI_NOT_READY.</strong></td>
</tr>
<tr class="odd">
<td id="section-18" class="unnumbered">25.2.1.4.2</td>
<td
id="x4021bf59-0x8fab-0x4a5e-0xa8-0x6b-0x3e-0xad-0xa2-0x78-0xb3-0x72"
class="unnumbered">0x4021bf59, 0x8fab, 0x4a5e, 0xa8, 0x6b, 0x3e, 0xad,
0xa2, 0x78, 0xb3, 0x72</td>
<td id="efi_hash2_protocol.-hashupdate---hashupdate"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashUpdate() -
HashUpdate()</strong> <span id="returns-efi_not_ready-when-it-follows-the-call-to-hash."
class="unnumbered"><strong>returns EFI_NOT_READY when it follows the
call to Hash().</strong></td>
<td
id="call-hashupdate-when-it-follows-the-call-to-hash-the-return-status-should-be-efi_not_ready."
class="unnumbered"><strong>1. Call HashUpdate() when it follows the call
to Hash(), the return status should be EFI_NOT_READY.</strong></td>
</tr>
<tr class="even">
<td id="section-19" class="unnumbered">25.2.1.4.3</td>
<td
id="xf7cd2a58-0x18f9-0x4285-0xb9-0x2b-0x22-0x76-0x7e-0xff-0xc8-0xf5"
class="unnumbered">0xf7cd2a58, 0x18f9, 0x4285, 0xb9, 0x2b, 0x22, 0x76,
0x7e, 0xff, 0xc8, 0xf5</td>
<td id="efi_hash2_protocol.-hashupdate---hashupdate-1"
class="unnumbered"><strong>EFI_HASH2_PROTOCOL. HashUpdate() -
HashUpdate()</strong> <span id="returns-efi_not_ready-when-it-follows-the-call-to-hashfinal."
class="unnumbered"><strong>returns EFI_NOT_READY when it follows the
call to HashFinal().</strong></td>
<td
id="call-hashupdate-when-it-follows-the-call-to-hashfinal-the-return-status-should-be-efi_not_ready."
class="unnumbered"><strong>1. Call HashUpdate() when it follows the call
to HashFinal(), the return status should be
EFI_NOT_READY.</strong></td>
</tr>

</tbody>
</table>


### HashFinal()

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
<td id="section-21" class="unnumbered">25.2.1.5.1</td>
<td
id="xd66d9eb8-0x52a9-0x415d-0xa9-0x15-0x7b-0x50-0xb8-0x53-0x34-0x5a"
class="unnumbered">0xd66d9eb8, 0x52a9, 0x415d, 0xa9, 0x15, 0x7b, 0x50,
0xb8, 0x53, 0x34, 0x5a</td>
<td id="efi_hash2_protocol.hashfinal--"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
<span id="hashfinal-returns-efi_success-with-valid-parameters."
class="unnumbered"><strong>HashFinal() returns EFI_SUCCESS with valid
parameters.</strong></td>
<td id="call-gethashsize-to-get-the" class="unnumbered"><p>1. Call
<strong>GetHashSize() to get the</strong> <span id="supported-hashalgorithm." class="unnumbered"><strong>supported
HashAlgorithm.</strong></p><p>2. Call <strong>HashInit()</strong> with the
<strong>supported HashAlgorithm</strong>, the return status should be
<strong>EFI_SUCCESS</strong>.</p><p>3. Call <strong>HashInit()</strong> with the
<strong>supported HashAlgorithm</strong>, the return status should be
<strong>EFI_ALREADY_STARTED</strong>.</p><p
id="call-hashupdate-with-the-updated-message-the-return-status-should-be-efi_success."
class="unnumbered">4. Call <strong>HashUpdate()</strong> with the
<strong>updated message</strong>, the return status should be
<strong>EFI_SUCCESS</strong>.</p><p
id="call-hashupdate-with-the-updated-message-the-return-status-should-be-efi_success.-1"
class="unnumbered">5. Call <strong>HashUpdate()</strong> with the
<strong>updated message</strong>, the return status should be
<strong>EFI_SUCCESS</strong>.</p><p
id="call-hashfinal-to-get-the-hash-output.-the-return-status-should-be-efi_success.-hash-output-should-be-correct."
class="unnumbered">6. Call <strong>HashFinal() to get the Hash output.
The return status should be EFI_SUCCESS. Hash output should be
correct.</strong></td>
</tr>
<tr class="odd">
<td id="section-22" class="unnumbered">25.2.1.5.2</td>
<td
id="x459f2e7e-0x1a98-0x44c6-0x97-0xe-0x38-0x92-0x67-0xdb-0xe1-0x57"
class="unnumbered">0x459f2e7e, 0x1a98, 0x44c6, 0x97, 0xe, 0x38, 0x92,
0x67, 0xdb, 0xe1, 0x57</td>
<td id="efi_hash2_protocol.hashfinal---1"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
</p>
<p
id="hashfinal-returns-efi_not_ready-when-it-is-not-preceded-by-the-call-to-hashinithashupdate."
class="unnumbered"><strong>HashFinal() returns EFI_NOT_READY when it is
not preceded by the call to HashInit()/HashUpdate().</strong></td>
<td
id="call-hashfinal-when-it-is-not-preceded-by-the-call-to-hashinithashupdate"
class="unnumbered"><strong>1. Call HashFinal() when it is not preceded
by the call to HashInit()/HashUpdate(),</strong><span id="the-return-status-should-be-efi_not_ready.-1"
class="unnumbered"><strong>the return status should be
EFI_NOT_READY.</strong></td>
</tr>
<tr class="even">
<td id="section-23" class="unnumbered">25.2.1.5.3</td>
<td
id="x57baa339-0xab9b-0x4cb7-0x8e-0xed-0xeb-0x97-0x68-0x82-0xaf-0x6b"
class="unnumbered">0x57baa339, 0xab9b, 0x4cb7, 0x8e, 0xed, 0xeb, 0x97,
0x68, 0x82, 0xaf, 0x6b</td>
<td id="efi_hash2_protocol.hashfinal---2"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
<strong>HashFinal() returns EFI_NOT_READY when it is
not preceded by the call to HashUpdate().</strong></td>
<td
id="call-hashfinal-when-it-is-not-preceded-by-the-call-to-hashupdate"
class="unnumbered"><strong>1. Call HashFinal() when it is not preceded
by the call to HashUpdate(),</strong><span id="the-return-status-should-be-efi_not_ready.-2"
class="unnumbered"><strong>the return status should be
EFI_NOT_READY.</strong></td>
</tr>
<tr class="odd">
<td id="section-24" class="unnumbered">25.2.1.5.4</td>
<td
id="x69af3be6-0x3ac2-0x467c-0x8c-0x41-0x74-0xd4-0x53-0x2f-0x66-0xa6"
class="unnumbered">0x69af3be6, 0x3ac2, 0x467c, 0x8c, 0x41, 0x74, 0xd4,
0x53, 0x2f, 0x66, 0xa6</td>
<td id="efi_hash2_protocol.hashfinal---3"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
<strong>HashFinal() returns EFI_NOT_READY when it
follows the call to Hash().</strong></td>
<td
id="call-hashfinal-when-it-follows-the-call-to-hash-the-return-status-should-be-efi_not_ready."
class="unnumbered"><strong>1. Call HashFinal() when it follows the call
to Hash(), the return status should be EFI_NOT_READY.</strong></td>
</tr>
<tr class="even">
<td id="section-25" class="unnumbered">25.2.1.5.5</td>
<td
id="x6022b449-0x9fe1-0x4bd9-0x84-0x9c-0x67-0x9e-0x7f-0x7-0xa5-0xfe"
class="unnumbered">0x6022b449, 0x9fe1, 0x4bd9, 0x84, 0x9c, 0x67, 0x9e,
0x7f, 0x7, 0xa5, 0xfe</td>
<td id="efi_hash2_protocol.hashfinal---4"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
<span id="hashfinal-returns-efi_invalid_parameter-when-hash-is-null."
class="unnumbered"><strong>HashFinal() returns EFI_INVALID_PARAMETER
when Hash is NULL.</strong></td>
<td
id="call-hashfinal-when-hash-is-null-the-return-status-should-be-efi_invalid_parameter."
class="unnumbered"><strong>1. Call HashFinal() when Hash is NULL, the
return status should be EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td id="section-26" class="unnumbered">25.2.1.5.6</td>
<td
id="x2a6201e8-0xe536-0x4e92-0xb6-0x4e-0x8e-0xbd-0xc6-0xfe-0xe0-0x25"
class="unnumbered">0x2a6201e8, 0xe536, 0x4e92, 0xb6, 0x4e, 0x8e, 0xbd,
0xc6, 0xfe, 0xe0, 0x25</td>
<td id="efi_hash2_protocol.hashfinal---5"
class="unnumbered"><strong>EFI_Hash2_PROTOCOL.HashFinal() -</strong>
<strong>HashFinal() returns EFI_NOT_READY when it
follows the call to HashFinal().</strong></td>
<td
id="call-hashfinal-when-it-follows-the-call-to-hashfinal-the-return-status-should-be-efi_not_ready."
class="unnumbered"><strong>1. Call HashFinal() when it follows the call
to HashFinal(), the return status should be
EFI_NOT_READY.</strong></td>
</tr>
</tbody>
</table>


## EFI_PKCS7_VERIFY_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_PKCS7_VERIFY_PROTOCOL Section.

### VerifyBuffer()

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
<td id="section-28" class="unnumbered">25.3.1.1.1</td>
<td
id="x5c0eec50-0xa6ea-0x413c-0x8a-0x46-0x4a-0xd1-0x4a-0x77-0x76-0xf1"
class="unnumbered">0x5c0eec50, 0xa6ea, 0x413c, 0x8a, 0x46, 0x4a, 0xd1,
0x4a, 0x77, 0x76, 0xf1</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_SUCCESS when content signature
was verified against hash of content, the signer's certificate was not
found in RevokedDb, and was found in AllowedDb.</strong></td>
<td
id="call-verifybuffer-when-content-signature-was-verified-against-hash-of-content-the-signers-certificate-was-not-found-in-revokeddb-and-was-found-in-alloweddb-the-return-status-should-be-efi_success."
class="unnumbered">1. Call <strong>VerifyBuffer() when content signature
was verified against hash of content, the signer's certificate was not
found in RevokedDb, and was found in AllowedDb, the return status should
be EFI_SUCCESS.</strong></td>
</tr>
<tr class="odd">
<td id="section-29" class="unnumbered">25.3.1.1.2</td>
<td
id="x6ea61fbd-0x1e46-0x4854-0x83-0xf8-0x22-0x93-0x24-0x1a-0x38-0x67"
class="unnumbered">0x6ea61fbd, 0x1e46, 0x4854, 0x83, 0xf8, 0x22, 0x93,
0x24, 0x1a, 0x38, 0x67</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-1"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong><strong>returns EFI_BUFFER_TOO_SMALL when the size of
buffer indicated by ContentSize is too small to hold the content.
ContentSize should be updated to required size.</strong></td>
<td
id="call-verifybuffer-when-the-size-of-buffer-indicated-by-contentsize-is-too-small-to-hold-the-content-the-return-status-should-be-efi_buffer_too_small.-contentsize-should-be-updated-to-required-size."
class="unnumbered">1. Call <strong>VerifyBuffer() when the size of
buffer indicated by ContentSize is too small to hold the content, the
return status should be EFI_BUFFER_TOO_SMALL. ContentSize should be
updated to required size.</strong></td>
</tr>
<tr class="even">
<td id="section-30" class="unnumbered">25.3.1.1.3</td>
<td
id="x51af2845-0x1bfe-0x4bc3-0x90-0x69-0x7b-0x29-0xbc-0x7c-0xc3-0xc6"
class="unnumbered">0x51af2845, 0x1bfe, 0x4bc3, 0x90, 0x69, 0x7b, 0x29,
0xbc, 0x7c, 0xc3, 0xc6</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-2"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_SUCCESS when the size of buffer
indicated by ContentSize is big enough to hold the content, and retrive
the correct content.</strong></td>
<td
id="call-verifybuffer-when-the-size-of-buffer-indicated-by-contentsize-is-big-enough-to-hold-the-content-and-retrive-the-correct-content-the-return-status-should-be-efi_success."
class="unnumbered">1. Call <strong>VerifyBuffer() when the size of
buffer indicated by ContentSize is big enough to hold the content, and
retrive the correct content, the return status should be
EFI_SUCCESS.</strong></td>
</tr>
<tr class="odd">
<td id="section-31" class="unnumbered">25.3.1.1.4</td>
<td
id="x912e23ef-0x299c-0x41ab-0xa0-0xf5-0xfc-0xbc-0xf6-0xfd-0xd3-0x32"
class="unnumbered">0x912e23ef, 0x299c, 0x41ab, 0xa0, 0xf5, 0xfc, 0xbc,
0xf6, 0xfd, 0xd3, 0x32</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-3"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong><strong>returns EFI_SUCCESS when the content
signature was verified against hash of content, signer is found in both
AllowedDb and RevokedDb, the signing was allowed by reference to
TimeStampDb.</strong></td>
<td
id="call-verifybuffer-when-the-content-signature-was-verified-against-hash-of-content-signer-is-found-in-both-alloweddb-and-revokeddb-the-signing-was-allowed-by-reference-to-timestampdb-the-return-status-should-be-efi_success."
class="unnumbered">1. Call <strong>VerifyBuffer() when the content
signature was verified against hash of content, signer is found in both
AllowedDb and RevokedDb, the signing was allowed by reference to
TimeStampDb, the return status should be EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td id="section-32" class="unnumbered">25.3.1.1.5</td>
<td
id="x5ccc7dff-0xc397-0x4733-0xb6-0xc7-0x88-0xc4-0x3e-0x80-0x6a-0x67"
class="unnumbered">0x5ccc7dff, 0xc397, 0x4733, 0xb6, 0xc7, 0x88, 0xc4,
0x3e, 0x80, 0x6a, 0x67</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-4"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_UNSUPPORTED when SignedData is
NULL or SignedDataSize is 0 or AllowedDb is NULL or Content is not NULL
and ContentSize is NULL.</strong></td>
<td
id="call-verifybuffer-when-signeddata-is-null-or-signeddatasize-is-0-or-alloweddb-is-null-or-content-is-not-null-and-contentsize-is-null-the-return-status-should-be-efi_invalid_parameter."
class="unnumbered">1. Call <strong>VerifyBuffer() when SignedData is
NULL or SignedDataSize is 0 or AllowedDb is NULL or Content is not NULL
and ContentSize is NULL, the return status should be
EFI_INVALID_PARAMETER.</strong></td>
</tr>
<tr class="odd">
<td id="section-33" class="unnumbered">25.3.1.1.6</td>
<td
id="xb1f546c3-0x4e-0x4e33-0xb1-0x81-0x76-0xf3-0xf8-0xb1-0xd6-0x5b"
class="unnumbered">0xb1f546c3, 0x4e, 0x4e33, 0xb1, 0x81, 0x76, 0xf3,
0xf8, 0xb1, 0xd6, 0x5b</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-5"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_UNSUPPORTED when
SignedData</strong> buffer is not correctly formatted for
processing<strong>.</strong></td>
<td
id="call-verifybuffer-when-signeddata-buffer-is-not-correctly-formatted-for-processing-the-return-status-should-be-efi_unsupported."
class="unnumbered">1. Call <strong>VerifyBuffer() when
SignedData</strong> buffer is not correctly formatted for
processing<strong>, the return status should be
EFI_UNSUPPORTED.</strong></td>
</tr>
<tr class="even">
<td id="section-34" class="unnumbered">25.3.1.1.7</td>
<td
id="xf9382c57-0xd51d-0x4ba9-0x91-0x41-0x30-0xc6-0x28-0x8b-0xd3-0x64"
class="unnumbered">0xf9382c57, 0xd51d, 0x4ba9, 0x91, 0x41, 0x30, 0xc6,
0x28, 0x8b, 0xd3, 0x64</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-6"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <span id="returns-efi_" class="unnumbered"><strong>returns
EFI_</strong><span id="aborted-when-alloweddb-is-invalid-format."
class="unnumbered"><strong>ABORTED when AllowedDb</strong> is invalid
format<strong>.</strong></td>
<td
id="call-verifybuffer-when-alloweddb-is-invalid-format-the-return-status-should-be-efi_-aborted."
class="unnumbered">1. Call <strong>VerifyBuffer() when
AllowedDb</strong> is invalid format<strong>, the return status should
be EFI_ ABORTED.</strong></td>
</tr>
<tr class="odd">
<td id="section-35" class="unnumbered">25.3.1.1.8</td>
<td
id="x3b322e30-0x8378-0x441a-0xba-0x1d-0xee-0xe5-0x53-0xda-0x21-0x49"
class="unnumbered">0x3b322e30, 0x8378, 0x441a, 0xba, 0x1d, 0xee, 0xe5,
0x53, 0xda, 0x21, 0x49</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-7"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <span id="returns-efi_aborted-when-revokeddb-is-invalid-format."
class="unnumbered"><strong>returns EFI_ABORTED when RevokedDb</strong>
is invalid format<strong>.</strong></td>
<td
id="call-verifybuffer-when-revokeddb-is-invalid-format-the-return-status-should-be-efi_-aborted."
class="unnumbered">1. Call <strong>VerifyBuffer() when
RevokedDb</strong> is invalid format<strong>, the return status should
be EFI_ ABORTED.</strong></td>
</tr>
<tr class="even">
<td id="section-36" class="unnumbered">25.3.1.1.9</td>
<td
id="xdfe02003-0xb2ad-0x46bc-0xae-0xe0-0xf9-0xb8-0xd0-0xec-0xd3-0x4a"
class="unnumbered">0xdfe02003, 0xb2ad, 0x46bc, 0xae, 0xe0, 0xf9, 0xb8,
0xd0, 0xec, 0xd3, 0x4a</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-8"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <span id="returns-efi_aborted-when-timestampdb-is-invalid-format."
class="unnumbered"><strong>returns EFI_ABORTED when TimeStampDb</strong>
is invalid format<strong>.</strong></td>
<td
id="call-verifybuffer-when-timestampdb-is-invalid-format-the-return-status-should-be-efi_-aborted."
class="unnumbered">1. Call <strong>VerifyBuffer() when
TimeStampDb</strong> is invalid format<strong>, the return status should
be EFI_ ABORTED.</strong></td>
</tr>
<tr class="odd">
<td id="section-37" class="unnumbered">25.3.1.1.10</td>
<td
id="x8de626c4-0x7112-0x4a57-0xb2-0xbb-0x30-0xc-0x5f-0x2a-0xc1-0x8e"
class="unnumbered">0x8de626c4, 0x7112, 0x4a57, 0xb2, 0xbb, 0x30, 0xc,
0x5f, 0x2a, 0xc1, 0x8e</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-9"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong><strong>returns EFI_SECURITY_VIOLATION when Buffer is
correctly formatted but signer is not in AllowedDb.</strong></td>
<td
id="call-verifybuffer-when-buffer-is-correctly-formatted-but-signer-is-not-in-alloweddb-the-return-status-should-be-efi_security_violation."
class="unnumbered">1. Call <strong>VerifyBuffer() when Buffer is
correctly formatted but signer is not in AllowedDb, the return status
should be EFI_SECURITY_VIOLATION.</strong></td>
</tr>
<tr class="even">
<td id="section-38" class="unnumbered">25.3.1.1.11</td>
<td
id="x399e1246-0xd15a-0x491a-0xbb-0x82-0x99-0xa4-0xda-0xb3-0xac-0x28"
class="unnumbered">0x399e1246, 0xd15a, 0x491a, 0xbb, 0x82, 0x99, 0xa4,
0xda, 0xb3, 0xac, 0x28</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-10"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong><strong>returns EFI_SECURITY_VIOLATION when Buffer is
correctly formatted but signer is in RevokedDb.</strong></td>
<td
id="call-verifybuffer-when-buffer-is-correctly-formatted-but-signer-is-in-revokeddb-the-return-status-should-be-efi_security_violation."
class="unnumbered">1. Call <strong>VerifyBuffer() when Buffer is
correctly formatted but signer is in RevokedDb, the return status should
be EFI_SECURITY_VIOLATION.</strong></td>
</tr>
<tr class="odd">
<td id="section-39" class="unnumbered">25.3.1.1.12</td>
<td
id="x670b4eab-0xf28d-0x42db-0xa7-0xbc-0xad-0xd-0x59-0x80-0x49-0xaf"
class="unnumbered">0x670b4eab, 0xf28d, 0x42db, 0xa7, 0xbc, 0xad, 0xd,
0x59, 0x80, 0x49, 0xaf</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-11"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_SECURITY_VIOLATION when Buffer is
correctly formatted but the content hash is in
RevokedDb.</strong></td>
<td
id="call-verifybuffer-when-buffer-is-correctly-formatted-but-the-content-hash-is-in-revokeddb-the-return-status-should-be-efi_security_violation."
class="unnumbered">1. Call <strong>VerifyBuffer() when Buffer is
correctly formatted but the content hash is in RevokedDb, the return
status should be EFI_SECURITY_VIOLATION.</strong></td>
</tr>
<tr class="even">
<td id="section-40" class="unnumbered">25.3.1.1.13</td>
<td
id="xfd98e4e5-0xf8af-0x4dcf-0x81-0x1a-0x6c-0xf4-0x99-0x8a-0x3-0x9d"
class="unnumbered">0xfd98e4e5, 0xf8af, 0x4dcf, 0x81, 0x1a, 0x6c, 0xf4,
0x99, 0x8a, 0x3, 0x9d</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-12"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong><strong>returns EFI_UNSUPPORTED when Signed data
embedded in SignedData but InData is not NULL.</strong></td>
<td
id="call-verifybuffer-when-signed-data-embedded-in-signeddata-but-indata-is-not-null-the-return-status-should-be-efi_unsupported."
class="unnumbered">1. Call <strong>VerifyBuffer() when Signed data
embedded in SignedData but InData is not NULL, the return status should
be EFI_UNSUPPORTED.</strong></td>
</tr>
<tr class="odd">
<td id="section-41" class="unnumbered">25.3.1.1.14</td>
<td
id="xb136e016-0x4f80-0x44bd-0xba-0xb0-0x1c-0x34-0x8a-0x2d-0xa1-0x8a"
class="unnumbered">0xb136e016, 0x4f80, 0x44bd, 0xba, 0xb0, 0x1c, 0x34,
0x8a, 0x2d, 0xa1, 0x8a</td>
<td id="efi_pkcs7_verify_protocol.verifybuffer---verifybuffer-13"
class="unnumbered"><strong>EFI_PKCS7_VERIFY_PROTOCOL.VerifyBuffer() -
VerifyBuffer()</strong> <strong>returns EFI_ NOT_FOUND when InData is NULL
and no content embedded in SignedData.</strong></td>
<td
id="call-verifybuffer-when-indata-is-null-and-no-content-embedded-in-signeddata-the-return-status-should-be-efi_not_found."
class="unnumbered">1. Call <strong>VerifyBuffer() when InData is NULL
and no content embedded in SignedData, the return status should be
EFI_NOT_FOUND.</strong></td>
</tr>
</tbody>
</table>


