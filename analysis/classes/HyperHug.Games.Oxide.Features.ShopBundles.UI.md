# namespace `HyperHug.Games.Oxide.Features.ShopBundles.UI`  (5 types)

### public class `BundleBuyPopup` : MonoBehaviour  
`TypeDefIndex 3547`

| offset | field |
|---|---|
| 0x38 | `private ItemDatabase itemDatabase;` |
| 0x40 | `private BundleItemView prefab;` |
| 0x48 | `private RectTransform ownedItemsContainer;` |
| 0x50 | `private RectTransform newItemsContainer;` |
| 0x58 | `private RectTransform buttonContainer;` |
| 0x60 | `private TextMeshProUGUI originalPrice;` |
| 0x68 | `private TextMeshProUGUI discountPrice;` |
| 0x70 | `private TextMeshProUGUI titleName;` |
| 0x78 | `private TextMeshProUGUI buttonText;` |
| 0x80 | `private Button buyButton;` |
| 0x88 | `private Button closeButton;` |

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3832C58 | 0x2F4C050 |  | `public void add_OcW(Action value)` |
| 0x3832CF4 | 0x2F4C054 |  | `public void remove_OcW(Action value)` |
| 0x3832D90 | 0x2F4C058 |  | `public void add_OcE(Action value)` |
| 0x3832E2C | 0x2F4C05C |  | `public void remove_OcE(Action value)` |
| 0x3832EC8 | 0x2F4C060 |  | `public void add_OcA(Action<ValueTuple<ItemData, SkinData>> value)` |
| 0x3832F78 | 0x2F4C064 |  | `public void remove_OcA(Action<ValueTuple<ItemData, SkinData>> value)` |
| 0x3833028 | 0x2F4C068 |  | `private void OnEnable()` |
| 0x3833110 | 0x2F4C06C |  | `private void OnDisable()` |
| 0x38331F8 | 0x2F4C070 |  | `public void dma(int e, int f, List<string> F, List<string> d, List<CatalogItem> c)` |
| 0x3833868 | 0x2F4C074 |  | `private void dmQ(Transform e)` |
| 0x3833E08 | 0x2F4C078 |  | `private void dmH(ValueTuple<ItemData, SkinData> item)` |
| 0x3833E2C | 0x2F4C07C |  | `private void dmi()` |
| 0x3833E50 | 0x2F4C080 |  | `private void dmw()` |
| 0x3833E74 | 0x2F4C084 |  | `public void .ctor()` |

</details>

### public class `BundleConfirmationPopup` : MonoBehaviour  
`TypeDefIndex 3548`

| offset | field |
|---|---|
| 0x28 | `private TextMeshProUGUI title;` |
| 0x30 | `private TextMeshProUGUI description;` |
| 0x38 | `private Button closeButton;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3834164 | 0x2F4C0A4 |  | `public void add_Ocu(Action value)` |
| 0x3834200 | 0x2F4C0A8 |  | `public void remove_Ocu(Action value)` |
| 0x383429C | 0x2F4C0AC |  | `private void Awake()` |
| 0x3834388 | 0x2F4C0B0 |  | `private void OnEnable()` |
| 0x3834418 | 0x2F4C0B4 |  | `private void OnDisable()` |
| 0x38342A0 | 0x2F4C0B8 |  | `private void dmL()` |
| 0x38344A8 | 0x2F4C0BC |  | `private void dmo()` |
| 0x38344CC | 0x2F4C0C0 |  | `public void .ctor()` |

</details>

### public class `BundleItemView` : MonoBehaviour  
`TypeDefIndex 3549`

| offset | field |
|---|---|
| 0x28 | `private Image icon;` |
| 0x30 | `private TextMeshProUGUI title;` |
| 0x38 | `private GameObject purchasedObject;` |
| 0x40 | `private Button previewButton;` |
| 0x48 | `private RarityBackgroundSwitcher rarityBackgroundSwitcher;` |
| 0x50 | `private ItemData OcO;` |
| 0x58 | `private SkinData Oct;` |
| 0x60 | `private bool Ocr;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3833D58 | 0x2F4C0C8 |  | `public void add_Ock(Action<ValueTuple<ItemData, SkinData>> value)` |
| 0x3834638 | 0x2F4C0CC |  | `public void remove_Ock(Action<ValueTuple<ItemData, SkinData>> value)` |
| 0x38346E8 | 0x2F4C0D0 |  | `private void OnEnable()` |
| 0x3834778 | 0x2F4C0D4 |  | `private void OnDisable()` |
| 0x3833B70 | 0x2F4C0D8 |  | `public void dmh(Sprite e, ItemData f, SkinData F, bool d)` |
| 0x3834808 | 0x2F4C0DC |  | `private void BuyItem()` |
| 0x3833CC8 | 0x2F4C0E0 |  | `public void dmB(CatalogItem e)` |
| 0x3834888 | 0x2F4C0E4 |  | `public void .ctor()` |

</details>

### public class `BundleShopBanner` : MonoBehaviour  
`TypeDefIndex 3550`

| offset | field |
|---|---|
| 0x28 | `private TextMeshProUGUI timerText;` |
| 0x30 | `private TextMeshProUGUI titleText;` |
| 0x38 | `private TextMeshProUGUI discountText;` |
| 0x40 | `private TextMeshProUGUI descriptionText;` |
| 0x48 | `private TextMeshProUGUI priceText;` |
| 0x50 | `private TextMeshProUGUI discountPriceText;` |
| 0x58 | `private GameObject priceContainer;` |
| 0x60 | `private GameObject obtainedTextContainer;` |
| 0x68 | `private Image image;` |
| 0x70 | `private Button openButton;` |
| 0x78 | `private TimeSpan Ocq;` |

Properties: `public Zj Ocs { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38349F0 | 0x2F4C0EC |  | `public Zj get_Ocs()` |
| 0x38349F8 | 0x2F4C0F4 |  | `private void set_Ocs(Zj value)` |
| 0x3834890 | 0x2F4C0F8 |  | `public void add_OcN(Action<Zj> value)` |
| 0x3834940 | 0x2F4C0FC |  | `public void remove_OcN(Action<Zj> value)` |
| 0x3834A00 | 0x2F4C100 |  | `private void OnEnable()` |
| 0x3834A90 | 0x2F4C104 |  | `private void OnDisable()` |
| 0x3834B20 | 0x2F4C108 |  | `public void dmK(Zj e, int f, int F, Za d)` |
| 0x3834D4C | 0x2F4C10C |  | `public void dmG(int e, int f)` |
| 0x3834E14 | 0x2F4C110 |  | `public void dmP(TimeSpan e)` |
| 0x383502C | 0x2F4C114 |  | `private void dmD()` |
| 0x3835054 | 0x2F4C118 |  | `public void .ctor()` |

</details>

### public class `BundlesUiReferencesHolder` : MonoBehaviour  
`TypeDefIndex 3551`

| offset | field |
|---|---|
| 0x20 | `private BundleBuyPopup popup;` |
| 0x28 | `private BundleConfirmationPopup confirmationPopup;` |

Properties: `public BundleBuyPopup sKZ { get; }`; `public BundleConfirmationPopup sKj { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38351F4 | 0x2F4C120 |  | `public BundleBuyPopup get_sKZ()` |
| 0x38351FC | 0x2F4C128 |  | `public BundleConfirmationPopup get_sKj()` |
| 0x3835204 | 0x2F4C130 |  | `public void .ctor()` |

</details>
