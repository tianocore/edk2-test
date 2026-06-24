# REST EX Protocol Test

## EFI_REST_EX_PROTOCOL Test

**Reference Document:**

*UEFI Specification 2.8*, EFI_REST_EX_PROTOCOL Section.

*Mantis 1834* (protocol definition), *Mantis 1879* (EFI_NOT_READY clarification), *Mantis 1924* (async cancel/timeout semantics).

### GetService() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.1.1 | 0xb293a4c5, 0xd6e7, 0x40f3, 0x04, 0x15, 0x86, 0x97, 0xa2, 0xb3, 0xc4, 0xd5 | **EFI_REST_EX_PROTOCOL.GetService – GetService()** returns **EFI_SUCCESS** with valid *RestExServiceInfo* pointer. | 1. Call **GetService()** with a valid *RestExServiceInfo* pointer. The return status should be **EFI_SUCCESS**. |
| 5.33.1.1.2 | 0xc3a4b5d6, 0xe7f8, 0x4104, 0x15, 0x26, 0x97, 0xa8, 0xb3, 0xc4, 0xd5, 0xe6 | **EFI_REST_EX_PROTOCOL.GetService – GetService()** returns valid service type. | 1. Call **GetService()**. 2. Verify the returned *RestExServiceInfo* contains a valid service type (HTTP or non-HTTP REST). |

### Configure() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.2.1 | 0xd4b5c6e7, 0xf809, 0x4215, 0x26, 0x37, 0xa8, 0xb9, 0xc4, 0xd5, 0xe6, 0xf7 | **EFI_REST_EX_PROTOCOL.Configure – Configure()** with valid *RestExConfigData* returns **EFI_SUCCESS**. | 1. Call **Configure()** with valid *RestExConfigData*. The return status should be **EFI_SUCCESS**. |
| 5.33.1.2.2 | 0xe5c6d7f8, 0x091a, 0x4326, 0x37, 0x48, 0xb9, 0xca, 0xd5, 0xe6, 0xf7, 0x08 | **EFI_REST_EX_PROTOCOL.Configure – Configure()** with NULL resets to unconfigured state. | 1. Call **Configure()** with valid config. 2. Call **Configure()** with NULL. The return status should be **EFI_SUCCESS** and the protocol should reset to unconfigured state. |

### GetModeData() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.3.1 | 0xf6d7e809, 0x1a2b, 0x4437, 0x48, 0x59, 0xca, 0xdb, 0xe6, 0xf7, 0x08, 0x19 | **EFI_REST_EX_PROTOCOL.GetModeData – GetModeData()** returns valid data after **Configure()**. | 1. Call **Configure()** with valid config data. 2. Call **GetModeData()**. The return status should be **EFI_SUCCESS** and the returned data should be valid. |

### SendReceive() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.4.1 | 0x07e8f91a, 0x2b3c, 0x4548, 0x59, 0x6a, 0xdb, 0xec, 0xf7, 0x08, 0x19, 0x2a | **EFI_REST_EX_PROTOCOL.SendReceive – SendReceive()** processes a basic GET request. | 1. Call **Configure()** with valid config. 2. Call **SendReceive()** with a valid HTTP GET *RequestMessage*. The return status should be **EFI_SUCCESS** or a valid HTTP error status. |

### GetServiceTime() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.5.1 | 0x18f90a2b, 0x3c4d, 0x4659, 0x6a, 0x7b, 0xec, 0xfd, 0x08, 0x19, 0x2a, 0x3b | **EFI_REST_EX_PROTOCOL.GetServiceTime – GetServiceTime()** returns valid time or **EFI_UNSUPPORTED**. | 1. Call **Configure()** with valid config. 2. Call **GetServiceTime()**. The return status should be **EFI_SUCCESS** with valid time data, or **EFI_UNSUPPORTED** if the service does not support time retrieval. |

### AyncSendReceive() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.6.1 | 0x290a1b3c, 0x4d5e, 0x476a, 0x7b, 0x8c, 0xfd, 0x0e, 0x19, 0x2a, 0x3b, 0x4c | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** establishes an async request. | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with a valid *RestExToken*. The return status should be **EFI_SUCCESS**. |
| 5.33.1.6.2 | 0x4b2c3d5e, 0x6f70, 0x498c, 0x9d, 0xae, 0x1f, 0x20, 0x3b, 0x4c, 0x5d, 0x6f | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** with non-NULL *TimeOutInMilliSeconds* exercises timeout path (Mantis 1924). | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with a non-zero *TimeOutInMilliSeconds* value in the token. The return status should indicate timeout handling is active. |
| 5.33.1.6.3 | 0x5c3d4e6f, 0x7081, 0x4a9d, 0xae, 0xbf, 0x20, 0x31, 0x4c, 0x5d, 0x6e, 0x80 | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** with NULL *RequestMessage* cancellation returns **EFI_ABORTED** (Mantis 1924). | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with NULL *RequestMessage* in the token. The return status should be **EFI_ABORTED** per the revised cancellation semantics. |

### EventService() Function

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.1.7.1 | 0x3a1b2c4d, 0x5e6f, 0x487b, 0x8c, 0x9d, 0x0e, 0x1f, 0x2a, 0x3b, 0x4c, 0x5e | **EFI_REST_EX_PROTOCOL.EventService – EventService()** establishes event subscription. | 1. Call **Configure()** with valid config. 2. Call **EventService()** with a valid *RestExToken*. The return status should be **EFI_SUCCESS**. |


## EFI_REST_EX_PROTOCOL Conformance Test

**Reference Document:**

*UEFI Specification 2.8*, EFI_REST_EX_PROTOCOL Section.

*Mantis 1879* (EFI_NOT_READY when unconfigured), *Mantis 1924* (async cancel/timeout).

### GetService() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.1.1 | 0x3a1b2c4d, 0x5e6f, 0x4a7b, 0x8c, 0x9d, 0x0e, 0x1f, 0x2a, 0x3b, 0x4c, 0x5d | **EFI_REST_EX_PROTOCOL.GetService – GetService()** returns **EFI_INVALID_PARAMETER** with NULL *RestExServiceInfo*. | 1. Call **GetService()** with NULL *RestExServiceInfo*. The return status should be **EFI_INVALID_PARAMETER**. |

### GetModeData() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.2.1 | 0x4b2c3d5e, 0x6f70, 0x4b8c, 0x9d, 0xae, 0x1f, 0x20, 0x3b, 0x4c, 0x5d, 0x6e | **EFI_REST_EX_PROTOCOL.GetModeData – GetModeData()** returns **EFI_INVALID_PARAMETER** with NULL *RestExConfigData*. | 1. Call **GetModeData()** with NULL *RestExConfigData*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.2.2 | 0x5c3d4e6f, 0x7081, 0x4c9d, 0xae, 0xbf, 0x20, 0x31, 0x4c, 0x5d, 0x6e, 0x7f | **EFI_REST_EX_PROTOCOL.GetModeData – GetModeData()** returns **EFI_NOT_READY** when unconfigured (Mantis 1879). | 1. Without calling **Configure()**, call **GetModeData()**. The return status should be **EFI_NOT_READY**. |

### Configure() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.3.1 | 0x6d4e5f70, 0x8192, 0x4dae, 0xbf, 0xc0, 0x31, 0x42, 0x5d, 0x6e, 0x7f, 0x80 | **EFI_REST_EX_PROTOCOL.Configure – Configure()** with NULL *RestExConfigData* resets to unconfigured state. | 1. Call **Configure()** with NULL. The protocol should reset to unconfigured state and subsequent calls to **GetModeData()** should return **EFI_NOT_READY**. |

### SendReceive() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.4.1 | 0x7e5f6081, 0x92a3, 0x4ebf, 0xc0, 0xd1, 0x42, 0x53, 0x6e, 0x7f, 0x80, 0x91 | **EFI_REST_EX_PROTOCOL.SendReceive – SendReceive()** returns **EFI_INVALID_PARAMETER** with NULL *RequestMessage*. | 1. Call **Configure()** with valid config. 2. Call **SendReceive()** with NULL *RequestMessage*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.4.2 | 0x8f607192, 0xa3b4, 0x4fc0, 0xd1, 0xe2, 0x53, 0x64, 0x7f, 0x80, 0x91, 0xa2 | **EFI_REST_EX_PROTOCOL.SendReceive – SendReceive()** returns **EFI_INVALID_PARAMETER** with NULL *ResponseMessage*. | 1. Call **Configure()** with valid config. 2. Call **SendReceive()** with NULL *ResponseMessage*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.4.3 | 0xf6d7e809, 0x1a2b, 0x4537, 0x48, 0x59, 0xca, 0xdb, 0xe6, 0xf7, 0x08, 0x1a | **EFI_REST_EX_PROTOCOL.SendReceive – SendReceive()** returns **EFI_NOT_READY** when unconfigured (Mantis 1879). | 1. Without calling **Configure()**, call **SendReceive()** with valid parameters. The return status should be **EFI_NOT_READY**. |

### GetServiceTime() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.5.1 | 0xb293a4c5, 0xd6e7, 0x41f3, 0x04, 0x15, 0x86, 0x97, 0xa2, 0xb3, 0xc4, 0xd5 | **EFI_REST_EX_PROTOCOL.GetServiceTime – GetServiceTime()** returns **EFI_INVALID_PARAMETER** with NULL *Time*. | 1. Call **Configure()** with valid config. 2. Call **GetServiceTime()** with NULL *Time*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.5.2 | 0xc3a4b5d6, 0xe7f8, 0x4204, 0x15, 0x26, 0x97, 0xa8, 0xb3, 0xc4, 0xd5, 0xe7 | **EFI_REST_EX_PROTOCOL.GetServiceTime – GetServiceTime()** returns **EFI_NOT_READY** when unconfigured (Mantis 1879). | 1. Without calling **Configure()**, call **GetServiceTime()**. The return status should be **EFI_NOT_READY**. |

### AyncSendReceive() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.6.1 | 0x907182a3, 0xb4c5, 0x40d1, 0xe2, 0xf3, 0x64, 0x75, 0x80, 0x91, 0xa2, 0xb3 | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** returns **EFI_INVALID_PARAMETER** with NULL *RestExToken*. | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with NULL *RestExToken*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.6.2 | 0xa18293b4, 0xc5d6, 0x40e2, 0xf3, 0x04, 0x75, 0x86, 0x91, 0xa2, 0xb3, 0xc4 | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** returns **EFI_NOT_READY** when unconfigured (Mantis 1879). | 1. Without calling **Configure()**, call **AyncSendReceive()** with a valid token. The return status should be **EFI_NOT_READY**. |
| 5.33.2.6.3 | 0x07e8f91a, 0x2b3c, 0x4648, 0x59, 0x6a, 0xdb, 0xec, 0xf7, 0x08, 0x19, 0x2b | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** with NULL *RequestMessage* returns **EFI_ABORTED** (Mantis 1924). | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with NULL *RequestMessage* in the token. The return status should be **EFI_ABORTED** per revised cancellation semantics. |
| 5.33.2.6.4 | 0x18f90a2b, 0x3c4d, 0x4759, 0x6a, 0x7b, 0xec, 0xfd, 0x08, 0x19, 0x2a, 0x3c | **EFI_REST_EX_PROTOCOL.AyncSendReceive – AyncSendReceive()** with zero *TimeOutInMilliSeconds* returns **EFI_TIMEOUT** (Mantis 1924). | 1. Call **Configure()** with valid config. 2. Call **AyncSendReceive()** with *TimeOutInMilliSeconds* set to zero. The return status should be **EFI_TIMEOUT**. |

### EventService() Conformance

| Number | GUID | Assertion | Test Description |
|----|----|----|----|
| 5.33.2.7.1 | 0xd4b5c6e7, 0xf809, 0x4315, 0x26, 0x37, 0xa8, 0xb9, 0xc4, 0xd5, 0xe6, 0xf8 | **EFI_REST_EX_PROTOCOL.EventService – EventService()** returns **EFI_INVALID_PARAMETER** with NULL *RestExToken*. | 1. Call **Configure()** with valid config. 2. Call **EventService()** with NULL *RestExToken*. The return status should be **EFI_INVALID_PARAMETER**. |
| 5.33.2.7.2 | 0xe5c6d7f8, 0x091a, 0x4426, 0x37, 0x48, 0xb9, 0xca, 0xd5, 0xe6, 0xf7, 0x09 | **EFI_REST_EX_PROTOCOL.EventService – EventService()** returns **EFI_NOT_READY** when unconfigured (Mantis 1879). | 1. Without calling **Configure()**, call **EventService()** with a valid token. The return status should be **EFI_NOT_READY**. |
