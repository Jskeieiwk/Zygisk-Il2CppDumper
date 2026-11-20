# namespace `Dissonance.Integrations.MirrorIgnorance`  (2 types)

### internal struct `DissonanceNetworkMessage` : vw, IDisposable  
`TypeDefIndex 3979`

| offset | field |
|---|---|
| 0x0 | `public ArraySegment<byte> Data;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3E1F920 | 0x2F89610 |  | `public void .ctor(ArraySegment<byte> packet)` |
| 0x3E203EC | 0x2F8973C | 4 | `public void Dispose()` |

</details>

### public struct `MirrorConn` : IEquatable<MirrorConn>  
`TypeDefIndex 3980`

| offset | field |
|---|---|
| 0x0 | `public readonly vO Connection;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3E206D0 | 0x2F89740 |  | `public void .ctor(vO connection)` |
| 0x3E21F24 | 0x2F89748 | 2 | `public override int GetHashCode()` |
| 0x3E21F44 | 0x2F89760 | 3 | `public override string ToString()` |
| 0x3E21F64 | 0x2F89768 | 0 | `public override bool Equals(object obj)` |
| 0x3E21FF8 | 0x2F89770 | 4 | `public bool Equals(MirrorConn other)` |

</details>
