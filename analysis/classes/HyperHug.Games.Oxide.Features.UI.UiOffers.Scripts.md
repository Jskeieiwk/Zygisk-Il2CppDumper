# namespace `HyperHug.Games.Oxide.Features.UI.UiOffers.Scripts`  (4 types)

### public class `SpecialOffersManager` : MonoBehaviour  
`TypeDefIndex 3435`

| offset | field |
|---|---|
| 0x20 | `private RectTransform _offersContent;` |
| 0x28 | `private RectTransform _bannersContent;` |
| 0x30 | `private UiSpecialOfferScreen _uiSpecialOfferScreenPrefab;` |
| 0x38 | `private UiSpecialOfferBanner _uiSpecialOfferBannerPrefab;` |
| 0x40 | `private cM Oex;` |
| 0x48 | `private readonly List<UiSpecialOfferScreen> OeK;` |
| 0x50 | `private readonly List<UiSpecialOfferBanner> OeG;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3813B20 | 0x2F0FBF4 |  | `private void dTv(cM e)` |
| 0x3813B28 | 0x2F0FBF8 |  | `private void Start()` |
| 0x3813B2C | 0x2F0FBFC |  | `private void dTS()` |
| 0x3813B30 | 0x2F0FC00 |  | `private void OnEnable()` |
| 0x3813C1C | 0x2F0FC04 |  | `private void OnDisable()` |
| 0x3813D08 | 0x2F0FC08 |  | `private void dTI(string e)` |
| 0x3813FD4 | 0x2F0FC0C |  | `private void dTM(List<ItemIsHighlighted> e)` |
| 0x38141A4 | 0x2F0FC10 |  | `private void dLe()` |
| 0x3814214 | 0x2F0FC14 |  | `private void dLf(string e)` |
| 0x3814234 | 0x2F0FC18 |  | `private void dLF(string e)` |
| 0x3814424 | 0x2F0FC1C |  | `public void .ctor()` |

</details>

### public class `UiOfferItemView` : MonoBehaviour  
`TypeDefIndex 3436`

| offset | field |
|---|---|
| 0x20 | `private Sprite _defaultSprite;` |
| 0x28 | `private Sprite _highlightedSprite;` |
| 0x30 | `private Image _mainImage;` |
| 0x38 | `private Text _nameText;` |
| 0x40 | `private ItemDatabase _itemDatabase;` |
| 0x48 | `private Image _itemImage;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3814500 | 0x2F0FC24 |  | `public void dLd(ItemIsHighlighted e)` |
| 0x3814718 | 0x2F0FC28 |  | `public void .ctor()` |

</details>

### public class `UiSpecialOfferBanner` : MonoBehaviour  
`TypeDefIndex 3437`

| offset | field |
|---|---|
| 0x20 | `private Image _background;` |
| 0x28 | `private Image _headerImage;` |
| 0x30 | `private UiYellowOfferButton _button;` |
| 0x38 | `private Button _offerButton;` |
| 0x50 | `private SpecialOfferBanner Oen;` |

Properties: `public string sxO { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38149E0 | 0x2F0FC30 |  | `public string get_sxO()` |
| 0x3814720 | 0x2F0FC38 |  | `public void add_OeP(Action<string> value)` |
| 0x38147D0 | 0x2F0FC3C |  | `public void remove_OeP(Action<string> value)` |
| 0x3814880 | 0x2F0FC40 |  | `public void add_OeD(Action<string> value)` |
| 0x3814930 | 0x2F0FC44 |  | `public void remove_OeD(Action<string> value)` |
| 0x38149FC | 0x2F0FC48 |  | `public void dLA(SpecialOfferBanner e, Product f)` |
| 0x3814A60 | 0x2F0FC4C |  | `private void OnEnable()` |
| 0x3814BEC | 0x2F0FC50 |  | `private void OnDisable()` |
| 0x3814D78 | 0x2F0FC54 |  | `private void dLu()` |
| 0x3814DB0 | 0x2F0FC58 |  | `private void dLk()` |
| 0x3814DE8 | 0x2F0FC5C |  | `public void .ctor()` |

</details>

### public class `UiSpecialOfferScreen` : MonoBehaviour  
`TypeDefIndex 3438`

| offset | field |
|---|---|
| 0x20 | `private Button _closeButton;` |
| 0x28 | `private RectTransform _backgroundRect;` |
| 0x30 | `private Image _backgroundImage;` |
| 0x38 | `private Image _headerImage;` |
| 0x40 | `private Image _discountImage;` |
| 0x48 | `private Image _ribbonImage;` |
| 0x50 | `private Text _ribbonText;` |
| 0x58 | `private Text _timerText;` |
| 0x60 | `private Image _timerImage;` |
| 0x68 | `private RectTransform _offerItemsContent;` |
| 0x70 | `private UiOfferItemView[] _offerItemViews;` |
| 0x78 | `private UiYellowOfferButton _button;` |
| 0x80 | `private RectTransform[] _vfxPanels;` |
| 0x88 | `private RectTransform _itemsInfoPanel;` |
| 0x90 | `private Text _itemsInfoText;` |
| 0x98 | `private Button _itemsPopUpButton;` |
| 0xA0 | `private RectTransform _itemsPopUp;` |
| 0xA8 | `private Image _itemsPopUpBackground;` |
| 0xB0 | `private Button _itemsCloseButton;` |
| 0xB8 | `private Text _itemsHeaderText;` |
| 0xC0 | `private Text _itemsBottomText;` |
| 0xC8 | `private UiOfferItemView _itemOfferViewPrefab;` |
| 0xD0 | `private UiYellowOfferButton _itemOfferButton;` |
| 0xD8 | `private RectTransform _itemsContent;` |
| 0xE8 | `private SpecialOfferScreen Oeg;` |

Properties: `public string sxt { get; }`; `public SpecialOfferScreen sxr { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38143A0 | 0x2F0FC64 |  | `public string get_sxt()` |
| 0x3814F50 | 0x2F0FC6C |  | `public SpecialOfferScreen get_sxr()` |
| 0x3814DF0 | 0x2F0FC74 |  | `public void add_OeV(Action<string> value)` |
| 0x3814EA0 | 0x2F0FC78 |  | `public void remove_OeV(Action<string> value)` |
| 0x3814F58 | 0x2F0FC7C |  | `public void dLq(SpecialOfferScreen e, string f, Product F)` |
| 0x3815524 | 0x2F0FC80 |  | `private void OnEnable()` |
| 0x38156E4 | 0x2F0FC84 |  | `private void OnDisable()` |
| 0x38158A4 | 0x2F0FC88 |  | `private void dLs()` |
| 0x38158DC | 0x2F0FC8C |  | `private void Close()` |
| 0x38143BC | 0x2F0FC90 |  | `public void dLC()` |
| 0x3815900 | 0x2F0FC94 |  | `private void dLZ()` |
| 0x381592C | 0x2F0FC98 |  | `private void dLj()` |
| 0x38159AC | 0x2F0FC9C |  | `public void .ctor()` |

</details>
