# namespace `HyperHug.Games.Oxide.Features.UiSystem.Core.Scripts.PreviewSystem`  (2 types)

### public class `BattlePassPreviewSettings`  
`TypeDefIndex 3420`

| offset | field |
|---|---|
| 0x10 | `public ItemPreviewUIReferenceHolderMono itemPreviewUIReferenceHolderMono;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3900C5C | 0x2F0EE28 |  | `public void .ctor()` |

</details>

### public class `BattlePassUiSkinPreviewReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3421`

| offset | field |
|---|---|
| - | `private RectTransform <NotExistsPanel>k__BackingField;` |
| - | `private TextMeshProUGUI <NotExistsIdText>k__BackingField;` |
| - | `private RectTransform <DownloadPanel>k__BackingField;` |
| - | `private RectTransform <ActiveDownloadPanel>k__BackingField;` |
| - | `private rA <DownloadButton>k__BackingField;` |
| - | `private Image <ActiveDownloadProgressImage>k__BackingField;` |
| - | `private TextMeshProUGUI <ActiveDownloadProgressText>k__BackingField;` |
| - | `private RectTransform <InQueuePanel>k__BackingField;` |
| - | `private RectTransform <SkinNamePanel>k__BackingField;` |
| - | `private TextMeshProUGUI <SkinNameText>k__BackingField;` |
| - | `private RectTransform <SkinDescriptionPanel>k__BackingField;` |
| - | `private TextMeshProUGUI <SkinDescriptionText>k__BackingField;` |
| - | `private RectTransform <ButtonsPanel>k__BackingField;` |
| - | `private rA <ZoomPlusButton>k__BackingField;` |
| - | `private rA <ZoomMinusButton>k__BackingField;` |
| - | `private sF <UICallbacksMono>k__BackingField;` |
| - | `private RawImage <RawImage>k__BackingField;` |
| - | `private Image <ImageIcon>k__BackingField;` |
| - | `private TextMeshProUGUI <CategoryName>k__BackingField;` |
| - | `private GameObject <ImageIconPanel>k__BackingField;` |
| - | `private Qm <OQv>k__BackingField;` |

Properties: `public RectTransform NotExistsPanel { get; set; }`; `public TextMeshProUGUI NotExistsIdText { get; set; }`; `public RectTransform DownloadPanel { get; set; }`; `public RectTransform ActiveDownloadPanel { get; set; }`; `public rA DownloadButton { get; set; }`; `public Image ActiveDownloadProgressImage { get; set; }`; `public TextMeshProUGUI ActiveDownloadProgressText { get; set; }`; `public RectTransform InQueuePanel { get; set; }`; `public RectTransform SkinNamePanel { get; set; }`; `public TextMeshProUGUI SkinNameText { get; set; }`; `public RectTransform SkinDescriptionPanel { get; set; }`; `public TextMeshProUGUI SkinDescriptionText { get; set; }`; `public RectTransform ButtonsPanel { get; set; }`; `public rA ZoomPlusButton { get; set; }`; `public rA ZoomMinusButton { get; set; }`; `public sF UICallbacksMono { get; set; }`; `public RawImage RawImage { get; set; }`; `public Image ImageIcon { get; set; }`; `public TextMeshProUGUI CategoryName { get; set; }`; `public GameObject ImageIconPanel { get; set; }`; `public Qm OQv { get; set; }`

<details><summary>methods (43)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0EE30 |  | `public RectTransform get_NotExistsPanel()` |
| - | 0x2F0EE38 |  | `private void set_NotExistsPanel(RectTransform value)` |
| - | 0x2F0EE40 |  | `public TextMeshProUGUI get_NotExistsIdText()` |
| - | 0x2F0EE48 |  | `private void set_NotExistsIdText(TextMeshProUGUI value)` |
| - | 0x2F0EE50 |  | `public RectTransform get_DownloadPanel()` |
| - | 0x2F0EE58 |  | `private void set_DownloadPanel(RectTransform value)` |
| - | 0x2F0EE60 |  | `public RectTransform get_ActiveDownloadPanel()` |
| - | 0x2F0EE68 |  | `private void set_ActiveDownloadPanel(RectTransform value)` |
| - | 0x2F0EE70 |  | `public rA get_DownloadButton()` |
| - | 0x2F0EE78 |  | `private void set_DownloadButton(rA value)` |
| - | 0x2F0EE80 |  | `public Image get_ActiveDownloadProgressImage()` |
| - | 0x2F0EE88 |  | `private void set_ActiveDownloadProgressImage(Image value)` |
| - | 0x2F0EE90 |  | `public TextMeshProUGUI get_ActiveDownloadProgressText()` |
| - | 0x2F0EE98 |  | `private void set_ActiveDownloadProgressText(TextMeshProUGUI value)` |
| - | 0x2F0EEA0 |  | `public RectTransform get_InQueuePanel()` |
| - | 0x2F0EEA8 |  | `private void set_InQueuePanel(RectTransform value)` |
| - | 0x2F0EEB0 |  | `public RectTransform get_SkinNamePanel()` |
| - | 0x2F0EEB8 |  | `private void set_SkinNamePanel(RectTransform value)` |
| - | 0x2F0EEC0 |  | `public TextMeshProUGUI get_SkinNameText()` |
| - | 0x2F0EEC8 |  | `private void set_SkinNameText(TextMeshProUGUI value)` |
| - | 0x2F0EED0 |  | `public RectTransform get_SkinDescriptionPanel()` |
| - | 0x2F0EED8 |  | `private void set_SkinDescriptionPanel(RectTransform value)` |
| - | 0x2F0EEE0 |  | `public TextMeshProUGUI get_SkinDescriptionText()` |
| - | 0x2F0EEE8 |  | `private void set_SkinDescriptionText(TextMeshProUGUI value)` |
| - | 0x2F0EEF0 |  | `public RectTransform get_ButtonsPanel()` |
| - | 0x2F0EEF8 |  | `private void set_ButtonsPanel(RectTransform value)` |
| - | 0x2F0EF00 |  | `public rA get_ZoomPlusButton()` |
| - | 0x2F0EF08 |  | `private void set_ZoomPlusButton(rA value)` |
| - | 0x2F0EF10 |  | `public rA get_ZoomMinusButton()` |
| - | 0x2F0EF18 |  | `private void set_ZoomMinusButton(rA value)` |
| - | 0x2F0EF20 |  | `public sF get_UICallbacksMono()` |
| - | 0x2F0EF28 |  | `private void set_UICallbacksMono(sF value)` |
| - | 0x2F0EF30 |  | `public RawImage get_RawImage()` |
| - | 0x2F0EF38 |  | `private void set_RawImage(RawImage value)` |
| - | 0x2F0EF40 |  | `public Image get_ImageIcon()` |
| - | 0x2F0EF48 |  | `private void set_ImageIcon(Image value)` |
| - | 0x2F0EF50 |  | `public TextMeshProUGUI get_CategoryName()` |
| - | 0x2F0EF58 |  | `private void set_CategoryName(TextMeshProUGUI value)` |
| - | 0x2F0EF60 |  | `public GameObject get_ImageIconPanel()` |
| - | 0x2F0EF68 |  | `private void set_ImageIconPanel(GameObject value)` |
| - | 0x2F0EF70 |  | `public Qm get_OQv()` |
| - | 0x2F0EF78 |  | `private void set_OQv(Qm value)` |
| 0x3908EAC | 0x2F0EF80 |  | `public void .ctor()` |

</details>
