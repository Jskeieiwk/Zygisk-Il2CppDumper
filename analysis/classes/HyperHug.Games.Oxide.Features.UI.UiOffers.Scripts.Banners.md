# namespace `HyperHug.Games.Oxide.Features.UI.UiOffers.Scripts.Banners`  (3 types)

### public class `UiBannerView` : MonoBehaviour  
`TypeDefIndex 3439`

| offset | field |
|---|---|
| 0x20 | `private Image _background;` |
| 0x28 | `private Image _header;` |
| 0x30 | `private Image _ribbon;` |
| 0x38 | `private UiYellowOfferButton _button;` |
| 0x48 | `private SpecialOfferBanner Oev;` |
| 0x50 | `private Product OeS;` |

Properties: `public string sxN { get; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3815B14 | 0x2F0FCA4 |  | `public string get_sxN()` |
| 0x38159B4 | 0x2F0FCAC |  | `public void add_Oep(Action<SpecialOfferBanner> value)` |
| 0x3815A64 | 0x2F0FCB0 |  | `public void remove_Oep(Action<SpecialOfferBanner> value)` |
| 0x3815B30 | 0x2F0FCB4 |  | `public void dLi(SpecialOfferBanner e, Product f, bool F)` |
| 0x3815B60 | 0x2F0FCB8 |  | `public void dLw()` |
| 0x3815B64 | 0x2F0FCBC |  | `private void OnEnable()` |
| 0x3815BF0 | 0x2F0FCC0 |  | `private void OnDisable()` |
| 0x3815C7C | 0x2F0FCC4 |  | `private void dLJ()` |
| 0x3815C9C | 0x2F0FCC8 |  | `public void .ctor()` |

</details>

### public class `UiOfferRowView` : MonoBehaviour  
`TypeDefIndex 3440`

| offset | field |
|---|---|
| 0x20 | `private UiBannerView[] _bannerViews;` |

Properties: `public UiBannerView[] sxq { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3815CA4 | 0x2F0FCD0 |  | `public UiBannerView[] get_sxq()` |
| 0x3815CAC | 0x2F0FCD8 |  | `public void .ctor()` |

</details>

### public class `UiYellowOfferButton` : MonoBehaviour  
`TypeDefIndex 3441`

| offset | field |
|---|---|
| 0x20 | `private RectTransform _purchasedPanel;` |
| 0x28 | `private RectTransform _notPurchasedPanel;` |
| 0x30 | `private Text _originalPrice;` |
| 0x38 | `private Text _fakePrice;` |
| 0x40 | `private Text _boughtText;` |
| 0x48 | `private Button _button;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3814B50 | 0x2F0FCE0 |  | `public void add_OeI(Action value)` |
| 0x3814CDC | 0x2F0FCE4 |  | `public void remove_OeI(Action value)` |
| 0x3815304 | 0x2F0FCE8 |  | `public void dLo(string e, Product f, bool F)` |
| 0x3815CB4 | 0x2F0FCEC |  | `private void OnEnable()` |
| 0x3815D44 | 0x2F0FCF0 |  | `private void OnDisable()` |
| 0x3815D68 | 0x2F0FCF4 |  | `public void .ctor()` |
| 0x3815D70 | 0x2F0FCFC |  | `private void dLy()` |

</details>
