# namespace `HyperHug.Games.Oxide.Features.SleepingBags`  (3 types)

### public class `RespawnMenu` : MonoBehaviour  
`TypeDefIndex 3543`

| offset | field |
|---|---|
| 0x20 | `private RectTransform sleepingBagsParent;` |
| 0x28 | `private GameObject sleepingBagMarkerPrefab;` |
| 0x30 | `private GameObject randomPointPrefab;` |
| 0x38 | `private GameController controller;` |
| 0x40 | `private MapView mapView;` |
| 0x48 | `private RespawnPointView OdM;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3832068 | 0x2F4B2FC |  | `public void dmF(SleepingBagData[] e)` |
| 0x38325B8 | 0x2F4B858 |  | `private void dmd(SleepingBagData e)` |
| 0x3832880 | 0x2F4B85C |  | `public void Respawn()` |
| 0x38324DC | 0x2F4BA48 |  | `public void dmc(RespawnPointView e)` |
| 0x3832938 | 0x2F4BC28 |  | `public void .ctor()` |

</details>

### public class `RespawnPointView` : MonoBehaviour  
`TypeDefIndex 3544`

| offset | field |
|---|---|
| - | `private const string Oce = "ui.sleeping.bag.num";` |
| 0x20 | `private Text idText;` |
| 0x28 | `private Text cooldownText;` |
| 0x30 | `private GameObject cooldownIndicator;` |
| 0x38 | `private Image cooldownImage;` |
| 0x40 | `private Image backgroundImage;` |
| 0x48 | `private Color normalColor;` |
| 0x58 | `private Color cooldownColor;` |
| 0x68 | `private Outline outline;` |
| 0x70 | `private uint Ocf;` |
| 0x74 | `private uint OcF;` |
| 0x78 | `private GameController Ocd;` |
| 0x80 | `private bool Occ;` |
| 0x84 | `private SleepingBagData OcU;` |

Properties: `public bool sKs { get; }`; `public uint sKC { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3832940 | 0x2F4BC30 |  | `public bool get_sKs()` |
| 0x3832950 | 0x2F4BC10 |  | `public uint get_sKC()` |
| 0x38328FC | 0x2F4B960 |  | `public void Respawn()` |
| 0x3832958 | 0x2F4BCF8 |  | `public void OnClick()` |
| 0x3832598 | 0x2F4BB78 |  | `public void dmW(bool e)` |
| 0x38326E8 | 0x2F4B6E0 |  | `public void dmE(GameController e, SleepingBagData f)` |
| 0x38324BC | 0x2F4B734 |  | `public void dmA(GameController e)` |
| 0x38329A4 | 0x2F4BC48 |  | `private bool dmu()` |
| 0x3832A18 | 0x2F4BDB4 |  | `private void Update()` |
| 0x3832C50 | 0x2F4C048 |  | `public void .ctor()` |

</details>

### public struct `SleepingBagData`  
`TypeDefIndex 3545`

| offset | field |
|---|---|
| 0x0 | `public Xn ItemType;` |
| 0x4 | `public uint NetId;` |
| 0x8 | `public uint DisplayId;` |
| 0xC | `public float LastUseTime;` |
| 0x10 | `public float UsageDelay;` |
| 0x14 | `public Vector3 Position;` |
