# Introduction

## Overview

This document provides detailed information for each assertion in the
UEFI SCT fundamental service and protocol tests. This document can be
used as a reference on case assertion for UEFI SCT users.

**Reference Documents**

- *UEFI Specification*
*--* indicates current and past UEFI specifications, unless specific
  versions are noted
- *UEFI SCT Getting Started*
- *UEFI SCT User Guide*

<table>
<colgroup>
<col style="width: 11%" />
<col style="width: 16%" />
<col style="width: 32%" />
<col style="width: 40%" />
</colgroup>
<tbody>
<tr class="odd">
<td>5.26.2.7.71</td>
<td>0x732738e8, 0x1ff1, 0x4f3a, 0xa0,0xc8,
0x38,0x81,0x1d,0x15,0x92,0x83</td>
<td><p>EFI_MTFTP4_PROTOCOL.ReadFile()</p>
<p>- ReadFile() must return</p>
<p>EFI_PROTOCOL_UNREACHABLE when receive an ICMP protocol unreachable
packet.</p></td>
<td><p>1. Call EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild() to create a new EFI_MTFTP4_PROTOCOL child handle.</p>
<p>2. Call EFI_MTFTP4_PROTOCOL.Configure() with all valid parameters.</p>
<p>3. Call EFI_MTFTP4_PROTOCOL.ReadFile() with all valid parameters. OS side should capture the packet sent from EUT side.</p>
<p>4. Configure Host side to send back an ICMP protocol unreachable packet and the return status should be
EFI_PROTOCOL_UNREACHABLE.</p>
<p>5. Call EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild() to destroy the newly created EFI_MTFTP4_PROTOCOL child handle and clean up the environment.</p></td>
</tr>
<tr class="even">
<td>5.26.2.7.72</td>
<td>0xd1c4e1e8, 0x1099, 0x4646, 0xb7,0xc9, 0x64,0x7e, 0x65,0xc3,
0x82,0x30</td>
<td><p>EFI_MTFTP4_PROTOCOL.ReadFile()</p>
<p>- ReadFile() must return</p>
<p>EFI_PORT_UNREACHABLE when receive an ICMP port unreachable
packet.</p></td>
<td><p>1. Call EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.CreateChild() to create a new EFI_MTFTP4_PROTOCOL child handle.</p>
<p>2. Call EFI_MTFTP4_PROTOCOL.Configure() with all valid parameters.</p>
<p>3. Call EFI_MTFTP4_PROTOCOL.ReadFile() with all valid parameters. OS side should capture the packet sent from EUT side.</p>
<p>4. Configure Host side to send back an ICMP port unreachable packet and the return status should be
EFI_PORT_UNREACHABLE.</p>
<p>5. Call EFI_MTFTP4_SERVICE_BINDING_PROTOCOL.DestroyChild() to destroy the newly created EFI_MTFTP4_PROTOCOL child handle and clean up the environment.</p></td>
</tr>
</tbody>
</table>


## System Hang

If the system hangs in any of tests, the UEFI SCT framework records a
failure assertion in the test report and skips this test after a system
restart.

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.20.1.1.1 | 0xde687a18, 0x0bbd, 0x4396, 0x85, 0x09, 0x49, 0x8f, 0xf2, 0x32, 0x34, 0xf1 | System hangs or stops.. | The name of the test which causes the system hang can be found in the test report. |
