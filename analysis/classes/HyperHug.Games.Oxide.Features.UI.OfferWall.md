# namespace `HyperHug.Games.Oxide.Features.UI.OfferWall`  (5 types)

### public class `OfferWallCoreInstaller` : ScriptableObjectInstaller  
`TypeDefIndex 3472`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x381A7B4 | 0x2F18AAC | 6 | `public override void FSz()` |
| 0x381A860 | 0x2F18AB0 |  | `private void doz()` |
| 0x381A8EC | 0x2F18AB4 |  | `public void .ctor()` |

</details>

### public class `OfferWallUiInstaller` : fWl  
`TypeDefIndex 3473`

| offset | field |
|---|---|
| 0x28 | `private UiOfferWallScreen offerWallScreen;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x381C118 | 0x2F18ABC | 8 | `public override void FSz()` |
| 0x381C184 | 0x2F18AC0 |  | `public void .ctor()` |

</details>

### public class `UiOfferWallButton` : MonoBehaviour  
`TypeDefIndex 3474`

| offset | field |
|---|---|
| 0x20 | `private Button button;` |
| 0x28 | `private UiOfferWallScreen OfD;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x381D7C0 | 0x2F18AC8 |  | `private void OnEnable()` |
| 0x381D868 | 0x2F18ACC |  | `private void dyc()` |
| 0x381E12C | 0x2F18AD0 |  | `public void .ctor()` |

</details>

### public class `UiOfferWallItem` : MonoBehaviour  
`TypeDefIndex 3476`

| offset | field |
|---|---|
| 0x20 | `private Button offerWallOpenButton;` |
| 0x28 | `private GameObject buttonTextObject;` |
| 0x30 | `private GameObject loadingIndicatorObject;` |
| 0x38 | `private GameObject saleIndicator;` |
| 0x40 | `private Text saleText;` |
| 0x48 | `private int Ofg;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x381E134 | 0x2F18AD8 |  | `public void dyY(int e, int f)` |
| 0x381E218 | 0x2F18ADC |  | `public void dyW(Action<int> e)` |
| 0x381E320 | 0x2F18AE0 |  | `public void dyE(bool e)` |
| 0x381E140 | 0x2F18AE4 |  | `private void dyA(int e)` |
| 0x381E368 | 0x2F18AE8 |  | `public void .ctor()` |

</details>

### public class `UiOfferWallScreen` : MonoBehaviour  
`TypeDefIndex 3478`

| offset | field |
|---|---|
| - | `private const string Ofv = "offerwall.notAvailable";` |
| - | `private const string OfS = "not.available.with.vpn";` |
| - | `private const string OfI = "not.available.on.guest";` |
| - | `private const string OfM = "offerwall.tip.title";` |
| - | `private const string OFe = "offerwall.tip.dscr";` |
| 0x20 | `private Canvas canvas;` |
| 0x28 | `private Text notAvailableOfferWallsText;` |
| 0x30 | `private Button infoButton;` |
| 0x38 | `private List<UiOfferWallItem> uiOfferWallItems;` |
| 0x40 | `private sX OFf;` |
| 0x48 | `private Bootstrap OFF;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x381E430 | 0x2F18B08 |  | `public void dyk(sX e, Bootstrap f)` |
| 0x381E464 | 0x2F18B0C |  | `private void Start()` |
| 0x381E4F4 | 0x2F18B10 |  | `private void OnDestroy()` |
| 0x381D880 | 0x2F18B14 |  | `public void Show()` |
| 0x381E520 | 0x2F18B18 |  | `public void Hide()` |
| 0x381E554 | 0x2F18B1C |  | `private void dyO()` |
| 0x381E640 | 0x2F18B20 |  | `private void dyt(int e)` |
| 0x381E674 | 0x2F18B24 |  | `private void Awake()` |
| 0x381E694 | 0x2F18B28 |  | `public void .ctor()` |

</details>
