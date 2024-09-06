# Protocols String Services Test

## EFI_REGULAR_EXPRESSION_PROTOCOL Test

**Reference Document:**

*UEFI Specification*, EFI_REGULAR_EXPRESSION_PROTOCOL Section.

### MatchString()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.35.1.1.1 | 0x9cec70a0, 0xfb56, 0x4b7f, 0x95, 0x31, 0xeb, 0xd0, 0x61, 0xa2, 0xcf, 0x8f | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns **EFI_INVALID_PARAMETER** when String is NULL. | 1\. Call **MatchString()** when String is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.35.1.1.2 | 0xfdceb7d8, 0x5fb7, 0x43c8, 0x8f, 0xa8, 0xec, 0xf, 0x7f, 0x14, 0x34, 0x29 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns **EFI_INVALID_PARAMETER** when Pattern is NULL. | 1\. Call **MatchString()** when Pattern is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.35.1.1.3 | 0x76813d40, 0xd2a7, 0x4912, 0x9e, 0xc4, 0x96, 0x6b, 0x14, 0x15, 0x4b, 0x51 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns **EFI_INVALID_PARAMETER** when Result is NULL. | 1\. Call **MatchString()** when Result is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.35.1.1.4 | 0xea3de64c, 0xe402, 0x43a7, 0xb4, 0x77, 0x66, 0xcd, 0xf5, 0x13, 0x1e, 0x85 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns EFI_INVALID_PARAMETER when CapturesCount is NULL. | 1\. Call **MatchString()** when CapturesCount is **NULL**, the return status should be **EFI_INVALID_PARAMETER**. |
| 5.35.1.1.5 | 0x98dee30e, 0xdc2b, 0x4dc6, {0x83, 0x10, 0xf8, 0x85, 0x17, 0x2f, 0x4c, 0xc8 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns EFI_UNSUPPORTED with unsupported SyntaxType. | 1\. Call MatchString() with unsupported SyntaxType, the return status should be EFI_UNSUPPORTED. |
| 5.35.1.1.6 | 0x94407424, 0xc17e, 0x4a28, 0xb7, 0x84, 0x3f, 0x84, 0x39, 0xcf, 0x30, 0x96 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns EFI_SUCCESS with all supported SyntaxType. | 1\. Call **MatchString()** with all supported **SyntaxType**, the return status should be **EFI_SUCCESS**. |
| 5.35.1.1.7 | 0x3d3be925, 0xfbf3, 0x425c, 0xbd, 0xd, 0x2b, 0x95, 0x2f, 0xf3, 0xbf, 0xe8 | **EFI_REGULAR_EXPRESSION_PROTOCOL.MatchString()** - MatchString() returns EFI_SUCCESS with default SyntaxType. | 1\. Call **MatchString()** with default **SyntaxType**, the return status should be **EFI_SUCCESS**. |


### GetInfo()

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.35.1.2.1 | 0x3219e1b1, 0xac3a, 0x4f53, 0x99, 0x11, 0xf3, 0x25, 0x44, 0x5b, 0xa8, 0x26 | **EFI_REGULAR_EXPRESSION_PROTOCOL.GetInfo()** - GetInfo() returns **EFI_BUFFER_TOO_SMALL** when **SyntaxTypeListSize** is too small to hold the result. | 1\. Call **GetInfo()** when **SyntaxTypeListSize** is too small to hold the result, the return status should be **EFI_BUFFER_TOO_SMALL**. The outputted **SyntaxTypeListSize** should be the multiple of size of **EFI_REGEX_SYNTAX_TYPE.** |
| 5.35.1.2.2 | 0x5a216f4d, 0xb4fe, 0x486d, 0x8e, 0x2e, 0x7b, 0xf9, 0x98, 0x47, 0x62, 0xbd | **EFI_REGULAR_EXPRESSION_PROTOCOL.GetInfo()** - GetInfo() returns **EFI_INVALID_PARAMETER** when **SyntaxTypeListSize is NULL.** | 1\. Call **GetInfo()** when **SyntaxTypeListSize is NULL**, the return status should be **EFI_INVALID_PARAMETER.** |
| 5.35.1.2.3 | 0x5365a661, 0xdb02, 0x46ed, 0xb8, 0x3e, 0xbc, 0x71, 0x6d, 0x6a, 0x8b, 0xb4 | **EFI_CONFIG_KEYWORD_HANDLER_PROTOCOL.GetData()** - GetData() returns **EFI_SUCCESS** with valid parameters. | 1\. Call **GetInfo()** with valid parameters, the return status should be **EFI_SUCCESS**. The outputted **SyntaxTypeListSize** should be same as the input size. |

