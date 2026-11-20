# namespace `HyperHug.Games.Oxide.Features.ResourceBundles.UI`  (5 types)

### public class `BundleCell` : MonoBehaviour  
`TypeDefIndex 3575`

| offset | field |
|---|---|
| 0x20 | `private BundleSlot bundleSlotPrefab;` |
| 0x28 | `private Transform slotsContainer;` |
| 0x30 | `private readonly List<BundleSlot> OUg;` |

Properties: `public IReadOnlyList<BundleSlot> sGe { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4CC64 |  | `public IReadOnlyList<BundleSlot> get_sGe()` |
| 0x384096C | 0x2F4CC6C |  | `public void dbV(ZG e)` |
| 0x3841020 | 0x2F4D0A8 |  | `public void dbg()` |
| 0x38411DC | 0x2F4D6F8 |  | `public void .ctor()` |

</details>

### public class `BundleSlot` : MonoBehaviour  
`TypeDefIndex 3576`

| offset | field |
|---|---|
| - | `private const int OUp = 3;` |
| - | `private const int OUv = 4;` |
| 0x28 | `private GameObject rowPrefab;` |
| 0x30 | `private BundleSlotItem itemSlotPrefab;` |
| 0x38 | `private BundleSlotItem smallItemPrefab;` |
| 0x40 | `private Transform imageContainer;` |
| 0x48 | `private Transform multiRowGroup;` |
| 0x50 | `private Transform singleRowGroup;` |
| 0x58 | `private Transform discountContainer;` |
| 0x60 | `private TextMeshProUGUI priceText;` |
| 0x68 | `private TextMeshProUGUI discountedPriceText;` |
| 0x70 | `private TextMeshProUGUI titleText;` |
| 0x78 | `private TextMeshProUGUI discountText;` |
| 0x80 | `private RarityBackgroundSwitcher rarityBackgroundSwitcher;` |
| 0x88 | `private ItemDatabase itemDatabase;` |
| 0x90 | `private Image packImage;` |
| 0x98 | `private Button buyButton;` |
| - | `private ResourceBundleConfig <OUI>k__BackingField;` |
| - | `private Action<BundleSlot> OUS;` |

Properties: `public ResourceBundleConfig OUI { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4D780 |  | `public ResourceBundleConfig get_OUI()` |
| - | 0x2F4D788 |  | `private void set_OUI(ResourceBundleConfig value)` |
| - | 0x2F4D790 |  | `public void add_OUS(Action<BundleSlot> value)` |
| - | 0x2F4D840 |  | `public void remove_OUS(Action<BundleSlot> value)` |
| 0x38413D4 | 0x2F4D8F0 |  | `private void OnEnable()` |
| 0x3841464 | 0x2F4D9C4 |  | `private void OnDisable()` |
| 0x3840D50 | 0x2F4D29C |  | `public void dbM(ResourceBundleConfig e)` |
| 0x38416E4 | 0x2F4DC84 |  | `private void dle(ResourceBundleConfig e)` |
| 0x38417B0 | 0x2F4DE2C |  | `private void dlf(List<ItemEntry> e)` |
| 0x3841910 | 0x2F4DFD4 |  | `private void dlF(List<ItemEntry> e)` |
| 0x3841974 | 0x2F4E680 |  | `private void dld(List<ItemEntry> e, Transform f, int F, int d)` |
| 0x3841D34 | 0x2F4E46C |  | `private void dlc(ItemEntry e, Transform f)` |
| 0x3841E4C | 0x2F4E788 |  | `private BundleSlotItem dlU()` |
| 0x3841A34 | 0x2F4E790 |  | `private void dlY(Transform e)` |
| 0x3841F0C | 0x2F4E794 |  | `private void dlW()` |
| 0x3841F2C | 0x2F4E7B4 |  | `public void .ctor()` |
| - | 0x2F4E16C |  | `private static void ClearRows(Transform t)` |

</details>

### public class `BundleSlotItem` : MonoBehaviour  
`TypeDefIndex 3577`

| offset | field |
|---|---|
| 0x20 | `private Image icon;` |
| 0x28 | `private TextMeshProUGUI countText;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3841EB0 | 0x2F4E684 |  | `public void dlE(Sprite e, int f)` |
| 0x3841F34 | 0x2F4E7BC |  | `public void .ctor()` |

</details>

### public class `PurchaseConfirmationPopup` : MonoBehaviour  
`TypeDefIndex 3578`

| offset | field |
|---|---|
| - | `private const string OUM = "resource.bundle.confirmation.title";` |
| - | `private const string OYe = "resource.bundle.confirmation.description";` |
| 0x30 | `private GameObject windowRoot;` |
| 0x38 | `private TextMeshProUGUI priceText;` |
| 0x40 | `private TextMeshProUGUI titleText;` |
| 0x48 | `private TextMeshProUGUI descriptionText;` |
| 0x50 | `private Button confirmButton;` |
| 0x58 | `private Button cancelButton;` |
| 0x60 | `private BundleSlot OYd;` |
| - | `private Action<BundleSlot> OYf;` |
| - | `private Action OYF;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4E7C4 |  | `public void add_OYf(Action<BundleSlot> value)` |
| - | 0x2F4E874 |  | `public void remove_OYf(Action<BundleSlot> value)` |
| - | 0x2F4E924 |  | `public void add_OYF(Action value)` |
| - | 0x2F4E9C0 |  | `public void remove_OYF(Action value)` |
| 0x38421D4 | 0x2F4EA5C |  | `private void Awake()` |
| 0x38421F4 | 0x2F4EB58 |  | `private void OnEnable()` |
| 0x38422DC | 0x2F4ECB4 |  | `private void OnDisable()` |
| 0x38423C4 | 0x2F4EE10 |  | `public void Show(BundleSlot slot)` |
| 0x3842594 | 0x2F4EAD4 |  | `public void Hide()` |
| 0x38425B4 | 0x2F4F09C |  | `private void dlt()` |
| 0x38425E4 | 0x2F4F0E0 |  | `private void dlr()` |
| 0x3842610 | 0x2F4F110 |  | `public void .ctor()` |

</details>

### public class `RarityBackgroundSwitcher` : MonoBehaviour  
`TypeDefIndex 3579`

| offset | field |
|---|---|
| 0x20 | `private Image backgroundImage;` |
| 0x28 | `private Image secondLayerImage;` |
| 0x30 | `private Color commonSprite;` |
| 0x40 | `private Color uncommonSprite;` |
| 0x50 | `private Color rareSprite;` |
| 0x60 | `private Color epicSprite;` |
| 0x70 | `private Color legendarySprite;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x384153C | 0x2F4DADC |  | `public void dlN(iQ e)` |
| 0x3842618 | 0x2F4F118 |  | `public void .ctor()` |

</details>
