# namespace `HyperHug.Games.Oxide.Features.ServersManaging.ClientSide`  (7 types)

### public struct `ChangeRegionsResponse`  
`TypeDefIndex 3563`

| offset | field |
|---|---|
| 0x0 | `public bool isSuccess;` |
| 0x8 | `public string error;` |
| 0x10 | `public RegionListResponse result;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DF06C | 0x2F4C2CC |  | `public void .ctor(string error)` |

</details>

### public struct `GetRegionsListResponse`  
`TypeDefIndex 3564`

| offset | field |
|---|---|
| 0x0 | `public bool isSuccess;` |
| 0x8 | `public string error;` |
| 0x10 | `public RegionListResponse result;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38E01A0 | 0x2F4C2D8 |  | `public void .ctor(string error)` |

</details>

### public struct `GetServerListResponse`  
`TypeDefIndex 3565`

Properties: `public bool OZj { get; set; }`; `public string OZa { get; set; }`; `public Yb.ServerListResponse OZQ { get; set; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38E0D64 | 0x2F4C2E4 |  | `public bool get_OZj()` |
| 0x38E0D6C | 0x2F4C2EC |  | `private void set_OZj(bool value)` |
| 0x38E0D78 | 0x2F4C2F0 |  | `public string get_OZa()` |
| 0x38E0D80 | 0x2F4C2F8 |  | `private void set_OZa(string value)` |
| 0x38E0D88 | 0x2F4C2FC |  | `public Yb.ServerListResponse get_OZQ()` |
| 0x38E0D90 | 0x2F4C304 |  | `private void set_OZQ(Yb.ServerListResponse value)` |
| 0x38E0D98 | 0x2F4C308 |  | `public void .ctor(string error)` |
| 0x38E0DC0 | 0x2F4C310 |  | `public void .ctor(Yb.ServerListResponse serverListResponse)` |

</details>

### public class `PingColor`  
`TypeDefIndex 3566`

| offset | field |
|---|---|
| 0x10 | `public int Ping;` |
| 0x14 | `public Color Color;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DEE1C | 0x2F4C318 |  | `public void .ctor()` |

</details>

### public class `Region`  
`TypeDefIndex 3567`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public string key;` |
| 0x20 | `public string ip;` |
| 0x28 | `public bool isDefault;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DFFC4 | 0x2F4C320 |  | `public void .ctor()` |

</details>

### public class `RegionItem` : MonoBehaviour  
`TypeDefIndex 3568`

| offset | field |
|---|---|
| 0x28 | `private Button _button;` |
| 0x30 | `private Text _name;` |
| 0x38 | `private Text _ping;` |
| 0x40 | `private GameObject _frame;` |
| 0x48 | `private PingColor[] _colors;` |
| 0x50 | `private Color _badPingColor;` |
| 0x60 | `private Action<string> OZq;` |

Properties: `public string OZN { get; set; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DFC78 | 0x2F4C328 |  | `public string get_OZN()` |
| 0x38DFC80 | 0x2F4C330 |  | `private void set_OZN(string value)` |
| 0x38DFC88 | 0x2F4C334 |  | `public void cFu(string e, string f, int F, bool d, Action<string> c)` |
| 0x38DFEFC | 0x2F4C338 |  | `private void OnDestroy()` |
| 0x38DFE64 | 0x2F4C33C |  | `private void cFk(int e)` |
| 0x38DFF8C | 0x2F4C340 |  | `private void cFO()` |
| 0x38DFE44 | 0x2F4C344 |  | `public void cFt(bool e)` |
| 0x38DFFB4 | 0x2F4C348 |  | `public void .ctor()` |

</details>

### public class `RegionListResponse`  
`TypeDefIndex 3569`

| offset | field |
|---|---|
| 0x10 | `public string currentRegion;` |
| 0x18 | `public Region[] availableRegions;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DFFBC | 0x2F4C350 |  | `public void .ctor()` |

</details>
