# TCG2 Protocol

## TCG2_PROTOCOL Test

Reference Document:

EFI Protocol Specification, Level 00 Revision 00.13, March 30, 2016. EFI_TCG2_PROTOCOL Chapter 6. The implementation of
the EFI_TCG2_BOOT_SERVICE_CAPABILITY struct is assumed to be version 1.1.

Tests in this chapter support TPMs based TCG PC Client Platform TPM Profile Specification for TPM 2.0.

### GetCapability()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.1.1</p>
            </td>
            <td>
                <p>0xca93b02a, 0xe897, 0x4400, 0x81, 0x38, 0xc8, 0xa8, 0xcb, 0x2f, 0xc1, 0xed</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.GetCapability() - GetCapabilty() returns EFI_INVALID_PARAMTERwith NULL pointer
                    Capability Struct Passed in.</p>
            </td>
            <td>
                <p>Call GetCapability()with NULL for capability struct pointer.</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.1.2</p>
            </td>
            <td>
                <p>0xfdee7001, 0x7e28, 0x4e35, 0x99, 0x66, 0x98, 0x0b, 0xeb, 0xba, 0xf1, 0x57</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.GetCapability() - GetCapability() shall populate all structure elements and return
                    with a Status of EFI_SUCCESS when the incoming Size field is greater than or equal to the size of
                    EFI_TCG2_BOOT_SERVICE_CAPABILITY supported by the firmware.</p>
            </td>
            <td>
                <p>Invoke GetCapabilty()with Protocol Capability. Size set to sizeof(EFI_TCG2_BOOT_SEVICE_CAPABILTY)</p>
                <ol>
                    <li>Verify that StructureVersion-&gt;Major == 1</li>
                    <li>Verify that StructureVersion-&gt;Minor == 1</li>
                    <li>Verify that ProtocolVersion-&gt;Major == 1</li>
                    <li>Verify that ProtocolVersion-&gt;Minor == 1</li>
                    <li>Verify that HashAlgorithmBitmapincludes SHA256</li>
                    <li>Verify that SupportedEventLogs is EFI_TCG2_EVENT_LOG_FORMAT_TCG_2</li>
                    <li>Verify that ~ActivePcrBanks &amp; HashAlgorithmBitMap == 0</li>
                    <li>Verify that NumberofPcrBanks is at least 1</li>
                    <li>Verify that ActivePcrBanks includes SHA256, SHA384, or SHA512</li>
                </ol>
                <p>Verify returned Status == EFI_SUCCESS.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.1.3</p>
            </td>
            <td>
                <p>0xda8821d9, 0x3d2c, 0x4698, 0x8c, 0xd5, 0x0f, 0x0c, 0x82, 0x94, 0x1d, 0x0c</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.GetCapability() – If the incoming Size parameter to GetCapability() is less than
                    the size of EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field then the
                    output Size field is populated with the full size of the capability struct supported by the firmware
                    and return code is BUFFER_TOO_SMALL. This allows a client to determine the size of
                    EFI_TCG2_BOOT_SERVICE_CAPABILITY supported by the firmware.</p>
            </td>
            <td>
                <p>Invoke GetCapability() with ProtocolCapability.Size set to a value less than the size of
                    EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field.</p>
                <ol>
                    <li>Verify Status returned == EFI_BUFFER_TOO_SMALL.</li>
                </ol>
                <p>Verify returned Size equal to sizeof(EFI_TCG2_BOOT_SERVICE_CAPABILITY).</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.1.4</p>
            </td>
            <td>
                <p>0x8ddb031b, 0x7448, 0x40ee, 0xb1, 0xa2, 0xe6, 0xf8, 0xe8, 0xc4, 0xe5, 0x5f</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.GetCapability() – If the incoming Size parameter to GetCapability() is greater than
                    or equal to the size of EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID
                    field and is less than sizeof(EFI_TCG2_BOOT_SEVICE_CAPABILTY) supported by the firmware, then the
                    fields up to and including the ManufacturerID are populated. This is a case of client that supports
                    version 1.0 of the EFI_TCG2_BOOT_SERVICE_CAPABILITY struct.</p>
            </td>
            <td>
                <p>Invoke GetCapability() with ProtocolCapability.Size set to a value equal to the size of
                    EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the ManufacturerID field.</p>
                <ol>
                    <li>Verify Status returned == EFI_SUCCESS.</li>
                </ol>
                <p>Verify returned Size equals the size of EFI_TCG2_BOOT_SERVICE_CAPABILITY up to and including the
                    ManufacturerID field.</p>
            </td>
        </tr>
    </tbody>
</table>

### GetActivePcrBanks()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.2.1</p>
            </td>
            <td>
                <p>0x7a1e79a3, 0x4064, 0x4372, 0xbb, 0x64,0x55, 0xb8, 0xf2, 0xa5, 0xa3, 0x26</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetActivePcrBanks() - GetActivePcrBanks() returns EFI_INVALID_PARAMETERwith NULL
                    pointer Passed in.</p>
            </td>
            <td>
                <p>Invoke GetActivePcrBanks()with ActivePcrBanks=NULL.</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.2.2</p>
            </td>
            <td>
                <p>0xb0e717c4, 0xb1e2, 0x49f7, 0xb2, 0xd7,0x60, 0x58,0x97, 0x7d, 0x09, 0x2c</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetActivePcrBanks() - GetActivePcrBanks()should return with EFI_SUCCESSand have
                    SHA256/384/512 Algorithms in its Bitmap.</p>
            </td>
            <td>
                <p>1. Invoke GetActivePcrBanks()with valid ActivePcrBanks buffer. Should return EFI_SUCCESS.</p>
                <ol>
                    <li>Verify Status returned == EFI_SUCCESS</li>
                </ol>
                <p>Verify that returned ActivePcrBanks bitmap includes SHA256, SHA384, or SHA512.c. Verify that returned
                    ActivePcrBanks bitmap matches one returned by GetCapabilty().</p>
            </td>
        </tr>
    </tbody>
</table>

### HashLogExtendEvent()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.3.1</p>
            </td>
            <td>
                <p>0xa8e1b5e6, 0xfc09, 0x461c, 0xb0, 0xe9, 0x2a, 0x49, 0xcd, 0x25, 0xc1, 0x24</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test with NULL DataToHash Pointer
                    should return EFI_INVALID_PARAMETER.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent()with DataToHash=NULL.</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.2</p>
            </td>
            <td>
                <p>0x26f04a9b, 0x7b7a, 0x4f47, 0xbe, 0xa8, 0xb1, 0xa6, 0x02, 0x65, 0x19, 0x8a</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test with NULL EfiTcgEvent Pointer
                    should return EFI_INVALID_PARAMETER.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent() with EfiTcgEvent=NULL</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.3</p>
            </td>
            <td>
                <p>0x4d1d9985, 0x91e2, 0x4948, 0x89, 0x16, 0xbb, 0x98, 0x13, 0x62, 0x39, 0x1d</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test with Event.Size &lt;
                    Event.Header.HeaderSize + sizeof(UINT32) should return EFI_INVALID_PARAMETER.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent() with EfiTcgEvent.Size is less than EfiTcgEvent.Header.HeaderSize +
                    sizeof(UINT32).</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.4</p>
            </td>
            <td>
                <p>0xfb59cab7, 0x4f8c, 0x4ded, 0xa4, 0x1c, 0xc8, 0x41, 0x20, 0x1c, 0x37, 0x22</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test with PCRIndex &gt; 23 should
                    return EFI_INVALID_PARAMETER.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent with EfiTcgEvent.Header.PCRIndex=24.</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.5</p>
            </td>
            <td>
                <p>0x0363d22f, 0xc66a, 0x4872, 0xa5, 0x46, 0x06, 0x7f, 0x6a, 0x0d, 0xdb, 0xcd</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent() Test with valid parameters should
                    return EFI_SUCCESS.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent() with:</p>
                <ul>
                    <li>DataToHash = "The quick brown fox jumps over the lazy dog"</li>
                    <li>PCRIndex = 16</li>
                    <li>EventType = EV_POST_CODE</li>
                    <li>Event data = "TCG2 Protocol Test"</li>
                </ul>
                <p>Verify Status returned == EFI_SUCCESS.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.6</p>
            </td>
            <td>
                <p>0x9cd6d636, 0x603a, 0x4b78, 0x80, 0xa3, 0xa3, 0xb9, 0xcc, 0x6a, 0x0b, 0x08</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test Handling of PE_COFF_IMAGE flag.
                </p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent() with:</p>
                <ul>
                    <li>DataToHash = "The quick brown fox jumps over the lazy dog"</li>
                    <li>PCRIndex = 16</li>
                    <li>EventType = EV_POST_CODE</li>
                    <li>Event data = "TCG2 Protocol Test"</li>
                    <li>Flags = PE_COFF_IMAGE</li>
                </ul>
                <p>Verify Status returned == EFI_UNSUPPORTED.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.3.7</p>
            </td>
            <td>
                <p>0xa8e1b5e6, 0xfc09, 0x461c, 0xb0, 0xe9, 0x2a, 0x49, 0xcd, 0x25, 0xc1, 0x24</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. HashLogExtendEvent() - HashLogExtendEvent()Test with NULL DataToHash Pointer
                    should return EFI_INVALID_PARAMETER.</p>
            </td>
            <td>
                <p>Invoke HashLogExtendEvent()with DataToHash=NULL.</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
    </tbody>
</table>

### GetEventLog()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.4.1</p>
            </td>
            <td>
                <p>0xfc80408e, 0x9a3c, 0x4054, 0x96, 0xf9, 0x31, 0x23, 0x35, 0xc2, 0x31, 0x35</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetEventLog() - GetEventLog() should return EFI_INVALID_PARAMTER when passed in
                    invalid EventLog Format.</p>
            </td>
            <td>
                <p>Invoke GetEventLog() with invalid EventLogFormat.</p>
                <p>Verify Status returned == EFI_SUCCESS.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.4.2</p>
            </td>
            <td>
                <p>0x45fa1a42, 0x912a, 0x5124, 0x84, 0xf4, 0x41, 0x67, 0xab, 0xb5, 0x89, 0x90</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetEventLog() - GetEventLog() shall return EFI_SUCCESS when a valid EventLogFormat
                    is passed in.</p>
            </td>
            <td>
                <p>Invoke GetEventLog() with EventLogFormat=EFI_TCG2_EVENT_LOG_FORMAT_TCG_2. Should return EFI_SUCCESS.
                </p>
                <p>Verify Status returned == EFI_SUCCESS.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.4.3</p>
            </td>
            <td>
                <p>0x1689bc3a, 0x2298, 0xa116, 0x28, 0x4c, 0xc1, 0xdd, 0xaa, 0xd8, 0xef, 0x51</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetEventLog() - GetEventLog() should return correct EventLogHeader</p>
            </td>
            <td>
                <p>Verify that the returned event log is present at EventLogLocation address by verifying event log
                    header.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.4.4</p>
            </td>
            <td>
                <p>0x126a789a, 0x1932, 0x3234, 0x21, 0xab, 0x42, 0x64, 0x8a, 0x7b, 0x63, 0x76</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL. GetEventLog() - GetEventLog() should record Event from Test 0x0363d22f as last
                    EventLogEntry.</p>
            </td>
            <td>
                <p>Verify that an event log entry is present at EventLogLastEntry by verifying the last entry. The last
                    entry should be the one added with the HashLogExtendEvent in test 0x0363d22f:</p>
                <ol>
                    <li>Verify TCG_PCR_EVENT2.PCRIndex = 16</li>
                    <li>Verify TCG_PCR_EVENT2.EventType = EV_POST_CODE</li>
                </ol>
                <p>Verify TCG_PCR_EVENT2.Digests.Count = [must equal number of active PCR banks]</p>
            </td>
        </tr>
    </tbody>
</table>

### SubmitCommmand()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.5.1</p>
            </td>
            <td>
                <p>0x3aac8b9a, 0x312a, 0x4dcf, 0x12, 0x76, 0x54, 0x55, 0x32, 0xcd, 0x3a, 0xea</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.SubmitComand() - SubmitCommand() shall populate the response buffer and return with
                    a status of EFI_SUCCESS when valid command parameters are passed in.</p>
            </td>
            <td>
                <p>Invoke SubmitCommand() with a command buffer containing Command TPM2_HASH Command, and Data to Hash
                    is "The quick brown fox jumps over the lazy dog".</p>
                <ol>
                    <li>Verify Status returned == EFI_SUCCESS.</li>
                </ol>
                <p>Verify returned outHash matches expected result</p>
            </td>
        </tr>
    </tbody>
</table>

### SetActivePcrBanks()

<table>
    <tbody>
        <tr>
            <th>
                <p>Number</p>
            </th>
            <th>
                <p>GUID</p>
            </th>
            <th>
                <p>Assertion</p>
            </th>
            <th>
                <p>Test Description</p>
            </th>
        </tr>
        <tr>
            <td>
                <p>31.1.6.1</p>
            </td>
            <td>
                <p>0x48586d48, 0xa8a4, 0x4129, 0x99, 0x8e, 0x78, 0x62, 0x3a, 0xac, 0x43, 0x6a</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.SetActivePcrBanks () - SetActivePcrBanks() should return EFI_INVALID_PARAMETER with
                    bitmap value of zero.</p>
            </td>
            <td>
                <p>Invoke SetActivePcrBanks() with ActivePcrBanks=0</p>
                <p>Verify Status returned == EFI_INVALID_PARAMETER.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.6.2</p>
            </td>
            <td>
                <p>0x1ed1b506, 0xc3c9, 0x45ea, 0xbf, 0x1e, 0x9b, 0xf2, 0x87, 0x08, 0x4e, 0x17</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.SetActivePcrBanks () - SetActivePcrBanks() should return EFI_INVALID_PARAMETER with
                    an ActivePcrBanks value with a bit set but not defined in HashAlgorithmBitMap.</p>
            </td>
            <td>
                <ol>
                    <li>Invoke GetCapabilty() to retrieve HashAlgorithmBitmap.</li>
                    <li>Invoke SetActivePcrBanks() with a bit set that is not in HashAlgorithmBitMap<ol>
                            <li>Verify Status returned == EFI_INVALID_PARAMETER</li>
                        </ol>
                    </li>
                </ol>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.6.3</p>
            </td>
            <td>
                <p>0x2923c2b2, 0x5a83, 0x4977, 0xbd, 0xed, 0x78, 0xb0, 0xd8, 0xbb, 0xcc, 0x77</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.SetActivePcrBanks () - SetActivePcrBanks() should return EFI_SUCESS for all bank
                    permutations defined in HashAlgorithmmBitmap.</p>
            </td>
            <td>
                <p>Using the HashAlgorithmBitMap from 30.1.6.2, invoke SetActivePcrBanks() with ActivePcrBanks from all
                    permutations of banks reported in HashAlgorithmBitMap retrieved via GetCapabilities(). For each
                    Permutation:</p>
                <p>Verify Status returned == EFI_SUCCESS.</p>
            </td>
        </tr>
        <tr>
            <td>
                <p>31.1.6.4</p>
            </td>
            <td>
                <p>0x181bc213, 0x4512, 0x47ea, 0x8a, 0xb6, 0x44, 0x76, 0xbf, 0x9a, 0x44, 0x6d</p>
            </td>
            <td>
                <p>EFI_TCG2_PROTOCOL.SetActivePcrBanks () - Verify that the ActivePcrBanks value set by
                    SetActivePcrBanks() is active following a reboot.</p>
            </td>
            <td>
                <ol>
                    <li>Identify the first algorithm in HashAlgorithmBitMap retrieved in test 30.1.6.3</li>
                    <li>Invoke ActivePcrBanks() to set the ActivePcrBanks to the first algorithm.</li>
                    <li>Reboot the system</li>
                </ol>
                <p>Invoke GetActivePcrBanks(). Should return EFI_SUCCESS, and ActivePcrBanks should be equal to the
                    value set in step #2</p>
            </td>
        </tr>
    </tbody>
</table>