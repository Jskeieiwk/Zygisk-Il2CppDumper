# namespace `Oxide.Features.Network`  (9 types)

### internal class `JoinRequestModel`  
`TypeDefIndex 3128`

Properties: `public string ServerId { get; set; }`; `public string MapId { get; set; }`; `public string Data { get; set; }`; `public string Data01 { get; set; }`; `public bool Data02 { get; set; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B75C | 0x2EAABA4 |  | `public string get_ServerId()` |
| 0x3A5B764 | 0x2EAABAC |  | `private void set_ServerId(string value)` |
| 0x3A5B76C | 0x2EAABB0 |  | `public string get_MapId()` |
| 0x3A5B774 | 0x2EAABB8 |  | `private void set_MapId(string value)` |
| 0x3A5B77C | 0x2EAABBC |  | `public string get_Data()` |
| 0x3A5B784 | 0x2EAABC4 |  | `private void set_Data(string value)` |
| 0x3A5B78C | 0x2EAABC8 |  | `public string get_Data01()` |
| 0x3A5B794 | 0x2EAABD0 |  | `private void set_Data01(string value)` |
| 0x3A5B79C | 0x2EAABD4 |  | `public bool get_Data02()` |
| 0x3A5B7A4 | 0x2EAABDC |  | `private void set_Data02(bool value)` |
| 0x3A5A5CC | 0x2EAABE0 |  | `public void .ctor(string serverId, string mapId, string data, string data01, bool data02)` |
| 0x3A5B7B0 | 0x2EAABE8 | 3 | `public override string ToString()` |

</details>

### internal class `JoinSkipResponse`  
`TypeDefIndex 3129`

Properties: `public bool IsSuccess { get; set; }`; `public QueueErrorModel Error { get; set; }`; `public QueueResponse Model { get; set; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B880 | 0x2EAABF0 |  | `public bool get_IsSuccess()` |
| 0x3A5B888 | 0x2EAABF8 |  | `private void set_IsSuccess(bool value)` |
| 0x3A5B894 | 0x2EAABFC |  | `public QueueErrorModel get_Error()` |
| 0x3A5B89C | 0x2EAAC04 |  | `private void set_Error(QueueErrorModel value)` |
| 0x3A5B8A4 | 0x2EAAC08 |  | `public QueueResponse get_Model()` |
| 0x3A5B8AC | 0x2EAAC10 |  | `private void set_Model(QueueResponse value)` |
| 0x3A5A658 | 0x2EAAC14 |  | `public static JoinSkipResponse cMz(string e)` |
| 0x3A5B990 | 0x2EAAC1C |  | `public void .ctor()` |
| 0x3A5B8B4 | 0x2EAAC24 |  | `internal static JoinSkipResponse cMh()` |

</details>

### public class `NetworkPrefabsConfig` : ScriptableObject  
`TypeDefIndex 3131`

| offset | field |
|---|---|
| 0x18 | `private List<NetworkPrefabsConfig.PrefabReference> prefabReferences;` |

Properties: `public List<NetworkPrefabsConfig.PrefabReference> sIL { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5E31C | 0x2EAAC2C |  | `public List<NetworkPrefabsConfig.PrefabReference> get_sIL()` |
| 0x3A5E324 | 0x2EAAC34 |  | `public NetworkPrefabsConfig.PrefabReference cMD(uint e)` |
| 0x3A5E4E8 | 0x2EAAE58 |  | `public void .ctor()` |

</details>

### public class `NetworkPrefabsSpawnManager` : MonoBehaviour  
`TypeDefIndex 3133`

| offset | field |
|---|---|
| 0x20 | `private NetworkPrefabsConfig prefabsConfig;` |
| 0x28 | `private bool isSmoothSpawn;` |
| 0x2C | `private int warmupBatchSize;` |
| 0x30 | `private ou OVJ;` |

Properties: `public NetworkPrefabsConfig sIo { get; }`; `private bool sIy { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5E570 | 0x2EAAE60 |  | `public NetworkPrefabsConfig get_sIo()` |
| 0x3A5E578 | 0x2EAAE68 |  | `private bool get_sIy()` |
| 0x3A5E594 | 0x2EAAE70 |  | `public UniTask cMg(CancellationToken e)` |
| - | 0x2EAAF10 |  | `public void RegisterRecoveredPrefabs()` |
| 0x3A5E664 | 0x2EAB2D8 |  | `public void cMp()` |
| 0x3A5E848 | 0x2EAB2DC |  | `private GameObject cMv(SpawnMessage e)` |
| 0x3A5E9E4 | 0x2EAB2E4 |  | `private void cMS(GameObject e)` |
| 0x3A5EB0C | 0x2EAB2E8 |  | `public void .ctor()` |

</details>

### public class `QueueErrorModel`  
`TypeDefIndex 3134`

| offset | field |
|---|---|
| - | `public const string DefaultEmpty = "00-000";` |
| - | `public const string InsufficientFunds = "JQ-001";` |
| - | `public const string SkipDisabled = "JQ-002";` |
| - | `public const string PrivateServer = "JQ-003";` |
| - | `public const string NoPremium = "JQ-004";` |
| - | `public const string BadSecret = "JQ-005";` |
| - | `public const string InvalidServer = "JQ-006";` |
| - | `public const string InvalidHash = "JQ-007";` |
| - | `public const string AlreadyOnServer = "JQ-008";` |
| - | `public const string InvalidMap = "JQ-009";` |
| - | `public const string Data01Data02Match = "JQ-010";` |

Properties: `public string Error { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B9C8 | 0x2EAB2F8 |  | `public string get_Error()` |
| 0x3A5B9D0 | 0x2EAB300 |  | `private void set_Error(string value)` |
| 0x3A5B998 | 0x2EAB304 |  | `public void .ctor(string error)` |

</details>

### internal class `QueueInfo`  
`TypeDefIndex 3135`

| offset | field |
|---|---|
| 0x10 | `public int position;` |
| 0x14 | `public int playersAfter;` |
| 0x18 | `public int skipPrice;` |
| 0x1C | `public bool skipAvailable;` |
| 0x20 | `public Yb.ServerListEntry serverInfo;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B9E0 | 0x2EAB30C |  | `public void .ctor()` |

</details>

### internal class `QueueResponse`  
`TypeDefIndex 3136`

| offset | field |
|---|---|
| 0x10 | `public bool allowedToJoin;` |
| 0x18 | `public ServerInfo serverInfo;` |
| 0x20 | `public QueueInfo queueInfo;` |
| 0x28 | `public string failReasonCode;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B9D8 | 0x2EAB314 |  | `public void .ctor()` |

</details>

### internal class `ServerInfo`  
`TypeDefIndex 3137`

| offset | field |
|---|---|
| 0x10 | `public string ip;` |
| 0x18 | `public int port;` |
| 0x20 | `public string secret;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B9E8 | 0x2EAB31C |  | `public void .ctor()` |

</details>

### internal class `SkipRequestModel`  
`TypeDefIndex 3138`

Properties: `public string ServerId { get; set; }`; `public string MapId { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A5B808 | 0x2EAB324 |  | `public string get_ServerId()` |
| 0x3A5B810 | 0x2EAB32C |  | `private void set_ServerId(string value)` |
| 0x3A5B818 | 0x2EAB330 |  | `public string get_MapId()` |
| 0x3A5B820 | 0x2EAB338 |  | `private void set_MapId(string value)` |
| 0x3A5B6D8 | 0x2EAB33C |  | `public void .ctor(string serverId, string mapId)` |
| 0x3A5B828 | 0x2EAB344 | 3 | `public override string ToString()` |

</details>
