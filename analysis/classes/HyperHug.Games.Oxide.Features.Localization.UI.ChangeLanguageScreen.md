# namespace `HyperHug.Games.Oxide.Features.Localization.UI.ChangeLanguageScreen`  (2 types)

### public class `LanguageButtonReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3691`

| offset | field |
|---|---|
| 0x20 | `private Button button;` |
| 0x28 | `private Image icon;` |
| 0x30 | `private GameObject selectImage;` |
| 0x38 | `private GameObject downloadImage;` |

Properties: `public Button sPD { get; }`; `public Image sPn { get; }`; `public GameObject sPV { get; }`; `public GameObject sPg { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F65EAC |  | `public Button get_sPD()` |
| - | 0x2F65EB4 |  | `public Image get_sPn()` |
| - | 0x2F65EBC |  | `public GameObject get_sPV()` |
| - | 0x2F65EC4 |  | `public GameObject get_sPg()` |
| 0x38C564C | 0x2F65ECC |  | `public void .ctor()` |

</details>

### public class `LanguagePanelReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3693`

| offset | field |
|---|---|
| 0x20 | `private Color disabledColor;` |
| 0x30 | `private Color activeColor;` |
| 0x40 | `private LanguageButtonReferenceHolder[] buttons;` |
| 0x48 | `public Action OnEnabled;` |
| 0x50 | `public Action OnDisabled;` |
| - | `private bool wired;` |

Properties: `public Color sPp { get; }`; `public Color sPv { get; }`; `public LanguageButtonReferenceHolder[] sPS { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F65ED4 |  | `public Color get_sPp()` |
| - | 0x2F65EE0 |  | `public Color get_sPv()` |
| - | 0x2F65EEC |  | `public LanguageButtonReferenceHolder[] get_sPS()` |
| - | 0x2F65EF4 |  | `private void OnEnable()` |
| 0x38C7174 | 0x2F66384 |  | `private void OnDisable()` |
| 0x38C7190 | 0x2F663A0 |  | `public void .ctor()` |
| - | 0x2F663A8 |  | `private void SelectLanguage(LanguageButtonReferenceHolder button)` |
| - | 0x2F6610C |  | `private void RefreshLanguageStates()` |

</details>
