# namespace `Oxide.Dialogs`  (1 types)

### public class `ConfirmDialogUI` : MonoBehaviour  
`TypeDefIndex 3146`

| offset | field |
|---|---|
| 0x20 | `private GameObject uiCanvas;` |
| 0x28 | `private Text uiTitleText;` |
| 0x30 | `private Text uiMessageText;` |
| 0x38 | `private GameObject uiButtonsParent;` |
| 0x40 | `private Button uiNegativeButton;` |
| 0x48 | `private Button uiPositiveButton;` |
| 0x50 | `private Text tFT;` |
| 0x58 | `private Text tFL;` |
| 0x60 | `private Image tFo;` |
| 0x68 | `private Image tFy;` |
| 0x70 | `private CanvasGroup tFz;` |
| 0x78 | `private int maxMessageLetters;` |
| 0x7C | `private bool _defaultHasButtons;` |
| 0x80 | `private string _defaultNegativeButtonText;` |
| 0x88 | `private string _defaultPositiveButtonText;` |
| 0x90 | `private zA _defaultButtonsColor;` |
| 0x94 | `private float _defaultFadeDuration;` |
| 0x98 | `private Queue<zE> tFh;` |
| 0xA0 | `private zE tFB;` |
| 0xA8 | `private zE tFm;` |
| 0xB0 | `private Color[] dialogButtonColors;` |
| 0xB8 | `public bool IsActive;` |
| 0x0 | `public static ConfirmDialogUI Instance;` |

<details><summary>methods (22)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ACDED4 | 0x2EAB3D0 |  | `private void Awake()` |
| 0x3ACE14C | 0x2EAB8D8 |  | `public ConfirmDialogUI Uqi(string e)` |
| 0x3ACE1B4 | 0x2EAB920 |  | `public ConfirmDialogUI Uqw(string e)` |
| 0x3ACE21C | 0x2EAB968 |  | `public ConfirmDialogUI UqJ(bool e = true)` |
| 0x3ACE280 | 0x2EAB9AC |  | `public ConfirmDialogUI UqX(zA e)` |
| 0x3ACE2E0 | 0x2EAB9B4 |  | `public ConfirmDialogUI UqT(string e = "no")` |
| 0x3ACE348 | 0x2EAB9FC |  | `public ConfirmDialogUI UqL(string e = "yes")` |
| 0x3ACE3B0 | 0x2EABA44 |  | `public ConfirmDialogUI Uqo(float e = 0.15)` |
| 0x3ACE418 | 0x2EABA84 |  | `public ConfirmDialogUI Uqy(UnityAction e)` |
| 0x3ACE480 | 0x2EABACC |  | `public ConfirmDialogUI Uqz(UnityAction e)` |
| 0x3ACE4E8 | 0x2EABB14 |  | `public ConfirmDialogUI Uqh(UnityAction e)` |
| 0x3ACE550 | 0x2EABB5C |  | `public void Show()` |
| 0x3ACE5C8 | 0x2EABC3C |  | `private void UqB()` |
| 0x3ACE8F0 | 0x2EABFAC |  | `public void Hide()` |
| 0x3ACE0A4 | 0x2EAB7F4 |  | `private void Uqm()` |
| 0x3ACE9E8 | 0x2EAC0BC |  | `private void UqR(UnityAction e)` |
| 0x3ACEA10 | 0x2EAC0C0 |  | `private IEnumerator Uqb(CanvasGroup e, float f, float F, float d)` |
| 0x3ACE874 | 0x2EAC0C8 |  | `private IEnumerator Uql(float e)` |
| 0x3ACE964 | 0x2EAC0D0 |  | `private IEnumerator Uqx(float e)` |
| 0x3ACEB18 | 0x2EAC0D8 |  | `public void .ctor()` |
| 0x3ACEC08 | 0x2EAC0E0 |  | `private void UqK()` |
| 0x3ACEC40 | 0x2EAC11C |  | `private void UqG()` |

</details>
