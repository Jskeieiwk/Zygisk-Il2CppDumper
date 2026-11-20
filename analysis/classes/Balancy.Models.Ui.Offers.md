# namespace `Balancy.Models.Ui.Offers`  (3 types)

### public abstract class `BaseOfferModel`  
`TypeDefIndex 4011`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3909784 | 0x2F89CD8 |  | `protected void .ctor()` |

</details>

### public class `SpecialOfferBanner`  
`TypeDefIndex 4012`

| offset | field |
|---|---|
| 0x10 | `private string unnyIdHeader;` |
| 0x18 | `private string unnyIdInfoOffer;` |
| 0x20 | `public readonly string StoreId;` |

Properties: `public SpecialOfferScreen InfoOffer { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x390978C | 0x2F89CE0 |  | `public SpecialOfferScreen get_InfoOffer()` |
| 0x39097E8 | 0x2F89CE8 |  | `public void .ctor()` |

</details>

### public class `SpecialOfferScreen` : BaseOfferModel  
`TypeDefIndex 4013`

| offset | field |
|---|---|
| 0x10 | `private string[] unnyIdItems;` |
| 0x18 | `private string unnyIdHeader;` |
| 0x20 | `private string unnyIdItemsPopUp;` |
| 0x28 | `public readonly string VfxId;` |
| 0x30 | `public readonly Color TimerTextColor;` |
| 0x40 | `public readonly string StoreId;` |

Properties: `public ItemIsHighlighted[] Items { get; }`; `public SpecialOfferItemsPopUp ItemsPopUp { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39097F0 | 0x2F89CF0 |  | `public ItemIsHighlighted[] get_Items()` |
| 0x390987C | 0x2F89CF8 |  | `public SpecialOfferItemsPopUp get_ItemsPopUp()` |
| 0x39097E0 | 0x2F89D00 |  | `public void .ctor()` |

</details>
