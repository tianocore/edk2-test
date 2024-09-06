# EFI Tape IO to Test

## EFI_TAPE_IO_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_TAPE_IO_PROTOCOL Section.

Configuration

Before testing of **TapeRead()** and **TapeSapce()**, we must make tape
ready by calling **TapeWrite()** and **TapeWriteFM()** to write some
blocks and some FileMarks.

Required Elements

### TapeRead()

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
<td>12.5.1.0.1</td>
<td>0xc42dcb51, 0x5101, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>check input parameters of testing
<strong>EFI_TAPE_IO_PROTOCOL.TapeRead().</strong></td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>12.5.1.1.1</td>
<td>0xc42dcb51, 0x5102, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRead()</strong> read some data from
the tape.</td>
<td><p>Call <strong>TapeRead()</strong> with
<strong>(bufferSize=16384)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p>
<p>Please note the configuration.</p></td>
</tr>
<tr class="even">
<td>12.5.1.1.2</td>
<td>0xc42dcb51, 0x512f, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>Verify the data getting from step
<strong>(12.5.1.1.1)</strong>.</td>
<td>After success of step <strong>(12.5.1.1.1)</strong> check reading
data is all correctly or not.</td>
</tr>
<tr class="odd">
<td>12.5.1.2.1</td>
<td>0xc42dcb51, 0x5103, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRead()</strong> Buffer invalid
checking test.</td>
<td>Call <strong>TapeRead()</strong> with
<strong>(bufferSize!=0,Buffer=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>12.5.1.2.2</td>
<td>0xc42dcb51, 0x5104, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRead() This=NULL</strong> checking
test.</td>
<td>Call <strong>TapeRead()</strong>with <strong>(This =NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>12.5.1.3.1</td>
<td>0xc42dcb51, 0x5105, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRead()</strong>parameters valid
checking test.</td>
<td>Call <strong>TapeRead()</strong> with
<strong>(bufferSize=0,buffer=NULL)</strong> should return
<strong>EFI_SUCCESS.</strong></td>
</tr>
<tr class="even">
<td>12.5.1.3.2</td>
<td>0xc42dcb51, 0x5107, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRead()</strong>parameters valid
checking test.</td>
<td>Call <strong>TapeRead()</strong> with
<strong>(bufferSize=0,buffer!=NULL)</strong> should return
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>

### TapeWrite()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>12.5.2.0.1</td>
<td>0xc42dcb51, 0x5108, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>check input parameters of testing
<strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>12.5.2.1.1</td>
<td>0xc42dcb51, 0x5109, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()</strong> write some data to
the tape.</td>
<td><p>Call <strong>TapeWrite()</strong> with
<strong>(bufferSize=16384)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="even">
<td>12.5.2.2.1</td>
<td>0xc42dcb51, 0x510a, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()</strong> Buffer invalid
checking test.</td>
<td>Call <strong>TapeWrite()</strong> with
<strong>(bufferSize!=0,Buffer=NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="odd">
<td>12.5.2.2.2</td>
<td>0xc42dcb51, 0x510b, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()This</strong> invalid
checking test.</td>
<td>Call <strong>TapeWrite()</strong> with <strong>(This =NULL)</strong>
should return <strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
<tr class="even">
<td>12.5.2.3.1</td>
<td>0xc42dcb51, 0x510c, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()</strong> parameters valid
checking test A.</td>
<td>Call <strong>TapeWrite()</strong> with
<strong>(bufferSize=0,buffer=NULL)</strong> should return
<strong>EFI_SUCCESS</strong>.</td>
</tr>
<tr class="odd">
<td>12.5.2.3.2</td>
<td>0xc42dcb51, 0x510e, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWrite()</strong>parameters valid
checking test B.</td>
<td>Call <strong>TapeWrite()</strong> with
<strong>(bufferSize=0,buffer!=NULL)</strong> should return
<strong>EFI_SUCCESS</strong>.</td>
</tr>
</tbody>
</table>



### TapeRewind()

<table>
<colgroup>
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 25%" />
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
<td>12.5.3.0.1</td>
<td>0xc42dcb51, 0x5110, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>check input parameters of testing
<strong>EFI_TAPE_IO_PROTOCOL.TapeRewind()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>12.5.3.1.1</td>
<td>0xc42dcb51, 0x5111, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRewind()</strong> rewind the
tape.</td>
<td><p>Call <strong>TapeRewind()</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="even">
<td>12.5.3.2.1</td>
<td>0xc42dcb51, 0x5112, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeRewind()</strong>parameters
<strong>This</strong> invalid checking test.</td>
<td>Call <strong>TapeRewind(NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>




### TapeSpace()

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
<td>12.5.4.0.1</td>
<td>0xc42dcb51, 0x5118, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>check input parameters of testing
<strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>12.5.4.1.0</td>
<td>0xc42dcb51, 0x511f, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> make the tape
testing ready.</td>
<td><p>Call <strong>TapeRewind()</strong> for tape ready.</p>
<p>Exit testing when error occurred.</p>
<p>Please note the configuration.</p></td>
</tr>
<tr class="even">
<td>12.5.4.1.1</td>
<td>0xc42dcb51, 0x5119, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> space some
BLOCKs</td>
<td><p>Call <strong>TapeSpace()</strong> with <strong>(spaceType =
TAPE_SPACE_TYPE_BLOCK)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>12.5.4.1.2</td>
<td>0xc42dcb51, 0x511e, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> space some
FILEMARKs</td>
<td><p>Call <strong>TapeSpace()</strong> with <strong>(spaceType =
TAPE_SPACE_TYPE_FILEMARK)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="even">
<td>12.5.4.2.1</td>
<td>0xc42dcb51, 0x511a, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> spaceDir &lt; 0
testing</td>
<td><p>Call <strong>TapeSpace()</strong> with <strong>(spaceDir &lt;
0)</strong> should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>12.5.4.3.1</td>
<td>0xc42dcb51, 0x511b, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> spaceDir = 0
testing</td>
<td><p>Call <strong>TapeSpace()</strong> with <strong>(spaceDir =
0)</strong> should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="even">
<td>12.5.4.4.1</td>
<td>0xc42dcb51, 0x511c, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong> spaceDir &gt; 0
testing</td>
<td><p>Call <strong>TapeSpace()</strong> with <strong>(spaceDir &gt;
0)</strong> should return <strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="odd">
<td>12.5.4.5.1</td>
<td>0xc42dcb51, 0x511d, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeSpace()</strong>parameter spaceType
invalid checking test.</td>
<td>Call <strong>TapeSpace()</strong> with <strong>invalid
spaceType</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>




### TapeWriteFM()

<table>
<colgroup>
<col style="width: 12%" />
<col style="width: 15%" />
<col style="width: 18%" />
<col style="width: 52%" />
</colgroup>
<tbody>
<tr class="odd">
<td>Number</td>
<td>GUID</td>
<td>Assertion</td>
<td>Test Description</td>
</tr>
<tr class="even">
<td>12.5.5.0.1</td>
<td>0xc42dcb51, 0x5120, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td>check input parameters of testing
<strong>EFI_TAPE_IO_PROTOCOL.TapeWriteFM()</strong>.</td>
<td>Check interface/environment valid.</td>
</tr>
<tr class="odd">
<td>12.5.5.1.1</td>
<td>0xc42dcb51, 0x5121, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWriteFM()</strong> write some
FileMarks to the tape.</td>
<td><p>Call <strong>TapeWriteFM()</strong> with
<strong>(Count=1)</strong> should return
<strong>EFI_SUCCESS</strong>.</p>
<p>Exit testing when error occurred.</p></td>
</tr>
<tr class="even">
<td>12.5.5.2.1</td>
<td>0xc42dcb51, 0x5122, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1,
0x00, 0xde</td>
<td><strong>EFI_TAPE_IO_PROTOCOL.TapeWriteFM()</strong> parameter
<strong>This</strong> invalid checking test.</td>
<td>Call <strong>TapeWriteFM(NULL)</strong> should return
<strong>EFI_INVALID_PARAMETER</strong>.</td>
</tr>
</tbody>
</table>



### TapeReset()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 12.5.6.0.1 | 0xc42dcb51, 0x5128, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1, 0x00, 0xde | check input parameters of testing **EFI_TAPE_IO_PROTOCOL.TapeReset()**. | Check interface/environment valid. |
| 12.5.6.1.1 | 0xc42dcb51, 0x5129, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1, 0x00, 0xde | **EFI_TAPE_IO_PROTOCOL.TapeReset()** reset the tape. | Call **TapeReset()** with **(extendReset=TRUE)** should return **EFI_SUCCESS**. |
| 12.5.6.1.2 | 0xc42dcb51, 0x512a, 0x4d36, 0xba,0x07, 0x9e,0xfc, 0x66,0xd1, 0x00,0xde | **EFI_TAPE_IO_PROTOCOL.TapeReset()** reset the tape. | Call **TapeReset()** with **(extendReset=FALSE)** should return **EFI_SUCCESS**. |
| 12.5.6.2.1 | 0xc42dcb51, 0x5122, 0x4d36, 0xba, 0x07, 0x9e, 0xfc, 0x66, 0xd1, 0x00, 0xde | **EFI_TAPE_IO_PROTOCOL.TapeReset()**parameter **This** invalid checking test. | Call **TapeReset()** with invalid parameters **(This=NULL)** should return **EFI_INVALID_PARAMETER**. |

