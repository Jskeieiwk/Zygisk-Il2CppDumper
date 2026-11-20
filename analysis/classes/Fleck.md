# namespace `Fleck`  (4 types)

### public class `ConnectionNotAvailableException` : Exception  
`TypeDefIndex 3883`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x374323C | 0x2F7E2BC |  | `public void .ctor()` |
| 0x3743294 | 0x2F7E314 |  | `public void .ctor(string message)` |
| 0x37432FC | 0x2F7E36C |  | `public void .ctor(string message, Exception innerException)` |

</details>

### public class `QueuedStream` : Stream  
`TypeDefIndex 3887`

| offset | field |
|---|---|
| 0x28 | `private readonly Stream kBK;` |
| 0x30 | `private readonly Queue<QueuedStream.kl> kBG;` |
| 0x38 | `private int kBP;` |
| 0x3C | `private bool kBD;` |

Properties: `public override bool CanRead { get; }`; `public override bool CanSeek { get; }`; `public override bool CanWrite { get; }`; `public override long Length { get; }`; `public override long Position { get; set; }`

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3744A2C | 0x2F7E3C4 | 8 | `public override bool get_CanRead()` |
| 0x3744A4C | 0x2F7E3CC | 9 | `public override bool get_CanSeek()` |
| 0x3744A6C | 0x2F7E3D4 | 11 | `public override bool get_CanWrite()` |
| 0x3744A8C | 0x2F7E3DC | 12 | `public override long get_Length()` |
| 0x3744AAC | 0x2F7E3E4 | 13 | `public override long get_Position()` |
| 0x3744AD0 | 0x2F7E3EC | 14 | `public override void set_Position(long value)` |
| 0x3744964 | 0x2F7E3F0 |  | `public void .ctor(Stream stream)` |
| 0x3744AF4 | 0x2F7E448 | 35 | `public override int Read(byte[] buffer, int offset, int count)` |
| 0x3744B18 | 0x2F7E450 | 33 | `public override long Seek(long offset, SeekOrigin origin)` |
| 0x3744B3C | 0x2F7E458 | 34 | `public override void SetLength(long value)` |
| 0x3744B60 | 0x2F7E45C | 38 | `public override void Write(byte[] buffer, int offset, int count)` |
| 0x3744BBC | 0x2F7E460 | 25 | `public override IAsyncResult BeginRead(byte[] buffer, int offset, int count, AsyncCallback callback, object state)` |
| 0x3744BE0 | 0x2F7E468 | 29 | `public override IAsyncResult BeginWrite(byte[] buffer, int offset, int count, AsyncCallback callback, object state)` |
| 0x3744FD4 | 0x2F7E470 | 26 | `public override int EndRead(IAsyncResult asyncResult)` |
| 0x3744FF8 | 0x2F7E478 | 30 | `public override void EndWrite(IAsyncResult asyncResult)` |
| 0x3745110 | 0x2F7E47C | 23 | `public override void Flush()` |
| 0x3745134 | 0x2F7E480 | 21 | `public override void Close()` |
| 0x3745158 | 0x2F7E484 | 22 | `protected override void Dispose(bool disposing)` |
| 0x3744E64 | 0x2F7E488 |  | `private IAsyncResult FMe(byte[] e, int f, int F, AsyncCallback d, object c, QueuedStream.kl U)` |

</details>

### public class `SubProtocolNegotiationFailureException` : Exception  
`TypeDefIndex 3888`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3748A78 | 0x2F7E4E4 |  | `public void .ctor()` |
| 0x3748AD0 | 0x2F7E53C |  | `public void .ctor(string message)` |
| 0x3748B38 | 0x2F7E594 |  | `public void .ctor(string message, Exception innerException)` |

</details>

### public class `WebSocketException` : Exception  
`TypeDefIndex 3889`

Properties: `public ushort kRc { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x374D2A8 | 0x2F7E5EC |  | `public ushort get_kRc()` |
| 0x374D2B0 | 0x2F7E5F4 |  | `private void set_kRc(ushort value)` |
| 0x3744600 | 0x2F7E5F8 |  | `public void .ctor(ushort statusCode)` |
| 0x374D1B0 | 0x2F7E650 |  | `public void .ctor(ushort statusCode, string message)` |
| 0x374D224 | 0x2F7E6A8 |  | `public void .ctor(ushort statusCode, string message, Exception innerException)` |

</details>
