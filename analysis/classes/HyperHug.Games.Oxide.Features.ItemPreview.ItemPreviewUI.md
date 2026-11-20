# namespace `HyperHug.Games.Oxide.Features.ItemPreview.ItemPreviewUI`  (2 types)

### public class `ItemPreviewUIReferenceHolderMono` : MonoBehaviour, QL  
`TypeDefIndex 3694`

| offset | field |
|---|---|
| - | `private GameObject <Window>k__BackingField;` |
| - | `private RawImage <PreviewImage>k__BackingField;` |
| - | `private sF <UICallbacksMono>k__BackingField;` |
| - | `private Button <CloseButton>k__BackingField;` |
| - | `private Button <BuyButton>k__BackingField;` |
| - | `private Text <PriceText>k__BackingField;` |
| - | `private Text <TitleText>k__BackingField;` |
| - | `private Text <DescriptionText>k__BackingField;` |
| - | `private Image <BackgroundImage>k__BackingField;` |
| - | `private RarityTextColorSwitcher <RarityTextColorSwitcher>k__BackingField;` |

Properties: `public GameObject Window { get; set; }`; `public RawImage PreviewImage { get; set; }`; `public sF UICallbacksMono { get; set; }`; `public Button CloseButton { get; set; }`; `public Button BuyButton { get; set; }`; `public Text PriceText { get; set; }`; `public Text TitleText { get; set; }`; `public Text DescriptionText { get; set; }`; `public Image BackgroundImage { get; set; }`; `public RarityTextColorSwitcher RarityTextColorSwitcher { get; set; }`

<details><summary>methods (21)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F66474 |  | `public GameObject get_Window()` |
| - | 0x2F6647C |  | `private void set_Window(GameObject value)` |
| - | 0x2F66484 |  | `public RawImage get_PreviewImage()` |
| - | 0x2F6648C |  | `private void set_PreviewImage(RawImage value)` |
| - | 0x2F66494 |  | `public sF get_UICallbacksMono()` |
| - | 0x2F6649C |  | `private void set_UICallbacksMono(sF value)` |
| - | 0x2F664A4 |  | `public Button get_CloseButton()` |
| - | 0x2F664AC |  | `private void set_CloseButton(Button value)` |
| - | 0x2F664B4 |  | `public Button get_BuyButton()` |
| - | 0x2F664BC |  | `private void set_BuyButton(Button value)` |
| - | 0x2F664C4 |  | `public Text get_PriceText()` |
| - | 0x2F664CC |  | `private void set_PriceText(Text value)` |
| - | 0x2F664D4 |  | `public Text get_TitleText()` |
| - | 0x2F664DC |  | `private void set_TitleText(Text value)` |
| - | 0x2F664E4 |  | `public Text get_DescriptionText()` |
| - | 0x2F664EC |  | `private void set_DescriptionText(Text value)` |
| - | 0x2F664F4 |  | `public Image get_BackgroundImage()` |
| - | 0x2F664FC |  | `private void set_BackgroundImage(Image value)` |
| - | 0x2F66504 |  | `public RarityTextColorSwitcher get_RarityTextColorSwitcher()` |
| - | 0x2F6650C |  | `private void set_RarityTextColorSwitcher(RarityTextColorSwitcher value)` |
| - | 0x2F66514 |  | `public void .ctor()` |

</details>

### public class `RarityTextColorSwitcher` : MonoBehaviour  
`TypeDefIndex 3695`

| offset | field |
|---|---|
| 0x20 | `private Text text;` |
| 0x28 | `private Color commonSprite;` |
| 0x38 | `private Color uncommonSprite;` |
| 0x48 | `private Color rareSprite;` |
| 0x58 | `private Color epicSprite;` |
| 0x68 | `private Color legendarySprite;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38D36B8 | 0x2F6651C |  | `public void cet(iQ e)` |
| 0x38D4454 | 0x2F66644 |  | `public void .ctor()` |

</details>
