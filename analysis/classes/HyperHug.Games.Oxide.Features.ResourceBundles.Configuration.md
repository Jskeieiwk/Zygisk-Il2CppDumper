# namespace `HyperHug.Games.Oxide.Features.ResourceBundles.Configuration`  (4 types)

### public struct `ItemEntry`  
`TypeDefIndex 3581`

| offset | field |
|---|---|
| 0x0 | `private string item;` |
| 0x8 | `private int quantity;` |

Properties: `public string sGF { get; }`; `public int sGd { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4F174 |  | `public string get_sGF()` |
| - | 0x2F4F17C |  | `public int get_sGd()` |

</details>

### public class `ResourceBundleConfig` : ScriptableObject  
`TypeDefIndex 3582`

| offset | field |
|---|---|
| - | `private const int MaxBundleSize = 8;` |
| - | `private const int MinBundleSize = 4;` |
| 0x18 | `private ResourceBundleVisualSettings visualSettings;` |
| 0x20 | `private List<ItemEntry> items;` |
| 0x28 | `private string id;` |
| 0x30 | `private int price;` |
| 0x34 | `private int discountValue;` |
| 0x38 | `private int requiredPlayerLevel;` |

Properties: `public string sGu { get; }`; `public int sGk { get; }`; `public int sGO { get; }`; `public List<ItemEntry> sGt { get; }`; `public int sGr { get; }`; `public int sGN { get; }`; `public ResourceBundleVisualSettings sGq { get; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4F184 |  | `public string get_sGu()` |
| - | 0x2F4DA98 |  | `public int get_sGk()` |
| - | 0x2F4F18C |  | `public int get_sGO()` |
| - | 0x2F4F194 |  | `public List<ItemEntry> get_sGt()` |
| - | 0x2F4F19C |  | `public int get_sGr()` |
| - | 0x2F4F1A4 |  | `public int get_sGN()` |
| - | 0x2F4F1AC |  | `public ResourceBundleVisualSettings get_sGq()` |
| 0x3844A6C | 0x2F4F1B4 |  | `private void dlD()` |
| 0x3844B38 | 0x2F4F1B8 |  | `public void .ctor()` |

</details>

### public class `ResourceBundleVisualSettings` : ScriptableObject  
`TypeDefIndex 3583`

| offset | field |
|---|---|
| 0x18 | `private Sprite bundleSprite;` |
| 0x20 | `private string titleLocalizationKey;` |
| 0x28 | `private ZP bundleSize;` |
| 0x2C | `private int sortOrder;` |
| 0x30 | `private iQ rarity;` |
| 0x34 | `private bool skipRarity;` |

Properties: `public Sprite sGc { get; }`; `public string sGU { get; }`; `public ZP sGY { get; }`; `public int sGW { get; }`; `public iQ sGE { get; }`; `public bool sGA { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4F1C0 |  | `public Sprite get_sGc()` |
| - | 0x2F4F1C8 |  | `public string get_sGU()` |
| - | 0x2F4F1D0 |  | `public ZP get_sGY()` |
| - | 0x2F4F1D8 |  | `public int get_sGW()` |
| - | 0x2F4F1E0 |  | `public iQ get_sGE()` |
| - | 0x2F4F1E8 |  | `public bool get_sGA()` |
| 0x3844A34 | 0x2F4F1F0 |  | `public void .ctor()` |

</details>

### public class `ResourcesBundleCatalog` : ScriptableObject  
`TypeDefIndex 3586`

| offset | field |
|---|---|
| 0x18 | `private List<ResourceBundleConfig> bundles;` |
| 0x20 | `private AssetReference cellSlot;` |

Properties: `public AssetReference sGs { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4F1F8 |  | `public AssetReference get_sGs()` |
| 0x38446C8 | 0x2F4F200 |  | `public List<ResourceBundleConfig> dlp(int e)` |
| 0x3844BD0 | 0x2F4F550 |  | `public void .ctor()` |

</details>
