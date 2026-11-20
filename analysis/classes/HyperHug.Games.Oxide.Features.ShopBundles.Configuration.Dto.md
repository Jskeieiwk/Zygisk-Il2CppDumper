# namespace `HyperHug.Games.Oxide.Features.ShopBundles.Configuration.Dto`  (3 types)

### public class `BundleData` : ScriptableObject  
`TypeDefIndex 3559`

| offset | field |
|---|---|
| 0x18 | `private string bundleID;` |
| 0x20 | `private BundleVisualItem bundleVisual;` |

Properties: `public BundleVisualItem sKz { get; }`; `public string sKh { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x383D96C | 0x2F4C25C |  | `public BundleVisualItem get_sKz()` |
| 0x383D974 | 0x2F4C264 |  | `public string get_sKh()` |
| 0x383D97C | 0x2F4C26C |  | `public void .ctor()` |

</details>

### public class `BundleItemsCatalog` : ScriptableObject  
`TypeDefIndex 3560`

| offset | field |
|---|---|
| 0x18 | `private List<BundleData> bundleItems;` |
| 0x20 | `private AssetReference fullSizeBundlePrefab;` |
| 0x28 | `private AssetReference halfSizeBundlePrefab;` |
| 0x30 | `private AssetReference bundlesContainerPrefab;` |
| 0x38 | `private Dictionary<string, BundleData> _cache;` |

Properties: `public AssetReference sKB { get; }`; `public AssetReference sKm { get; }`; `public AssetReference sKR { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x383D984 | 0x2F4C274 |  | `public AssetReference get_sKB()` |
| 0x383D98C | 0x2F4C27C |  | `public AssetReference get_sKm()` |
| 0x383D994 | 0x2F4C284 |  | `public AssetReference get_sKR()` |
| 0x383D99C | 0x2F4C28C |  | `public BundleData dbU(string e)` |
| 0x383DA20 | 0x2F4C294 |  | `private void dbY()` |
| 0x383DBE8 | 0x2F4C298 |  | `public void .ctor()` |

</details>

### public class `BundleVisualItem` : ScriptableObject  
`TypeDefIndex 3561`

| offset | field |
|---|---|
| 0x18 | `private Sprite fullBannerIcon;` |
| 0x20 | `private Sprite halfBannerIcon;` |
| 0x28 | `private string localizationTitleKey;` |
| 0x30 | `private string localizationDescriptionKey;` |

Properties: `public string sKb { get; }`; `public string sKl { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x383DBF0 | 0x2F4C2A0 |  | `public string get_sKb()` |
| 0x383DBF8 | 0x2F4C2A8 |  | `public string get_sKl()` |
| 0x383DC00 | 0x2F4C2B0 |  | `public Sprite dbA(Za e)` |
| 0x383DC18 | 0x2F4C2B8 |  | `public void .ctor()` |

</details>
