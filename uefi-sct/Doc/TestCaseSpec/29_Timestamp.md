# Timestamp Protocols

## EFI_TIMESTAMP_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_TIMESTAMP_PROTOCOL Section.

### GetTimestamp()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.34.1.1.1 | 0xa971e7ad, 0x5889, 0x4af0, 0x8c, 0x7e, 0x05, 0xa6, 0x88, 0xca, 0xf6, 0xd8 | **EFI_TIMESTAMP_PROTOCOL.GetTimestamp - GetTimestamp()** returns reasonable value. | Call **GetTimestamp ()** should return a reasonable value. |



### GetProperties()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.34.1.2.1 | 0x7530e468, 0xc9d0, 0x4881, 0xa2, 0xe7, 0xb5, 0x9f, 0x80, 0x38, 0x70, 0x26 | **EFI_TIMESTAMP_PROTOCOL.GetProperties- GetProperties()** returns **EFI_SUCCESS** with properties being not **NULL**. | Call **GetProperties ()**with properties being not NULL, the return status should be **EFI_SUCCESS**. |
| 5.34.1.2.2 | 0x2e9847b0, 0x8d24, 0x4c8d, 0xbd, 0xbc, 0x57, 0xc5, 0xdb, 0x10, 0x10, 0x95 | **EFI_TIMESTAMP_PROTOCOL.GetProperties- GetProperties()** Properties.EndValue returned from **GetProperties()** should be in 0xFFFF format. | Call **GetProperties ()**with properties being not **NULL**, Properties.EndValue returned from **GetProperties()** should be in 0xFFFF format. |
| 5.34.1.2.3 | 0x3b1d442f, 0xcc6d, 0x4e89, 0xa3, 0x91, 0x00, 0x40, 0xb2, 0x39, 0xd7, 0xb6 | **EFI_TIMESTAMP_PROTOCOL.GetProperties- GetProperties()** returns **EFI_INVALID_PARAMETER** with properties being **NULL**. | Call **GetProperties ()**with properties being **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |

