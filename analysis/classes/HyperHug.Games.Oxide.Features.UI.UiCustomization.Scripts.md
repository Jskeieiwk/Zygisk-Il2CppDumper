# namespace `HyperHug.Games.Oxide.Features.UI.UiCustomization.Scripts`  (5 types)

### public class `UiButtonsSettingsView` : MonoBehaviour  
`TypeDefIndex 3442`

| offset | field |
|---|---|
| 0x20 | `private Slider _opacitySlider;` |
| 0x28 | `private Text _opacityValue;` |
| 0x30 | `private Slider _scaleSlider;` |
| 0x38 | `private Text _scaleValue;` |
| 0x40 | `private UiCustomizationScreen kMP;` |
| 0x48 | `private UiCustomizationButton kMD;` |

Properties: `private float slz { get; }`; `private float slh { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0FD00 |  | `private float get_slz()` |
| - | 0x2F0FE94 |  | `private float get_slh()` |
| 0x380CAD4 | 0x2F0FF58 |  | `public void Open(UiCustomizationScreen uiCustomizationScreen, UiCustomizationButton button)` |
| 0x380CCD0 | 0x2F101F0 |  | `private void dJm(float e)` |
| 0x380CEC8 | 0x2F103B8 |  | `private void dJR(float e)` |
| 0x380D044 | 0x2F10520 |  | `private void OnEnable()` |
| 0x380D140 | 0x2F10698 |  | `private void OnDisable()` |
| 0x380D23C | 0x2F10810 |  | `public void Close()` |
| 0x380D260 | 0x2F10834 |  | `public void .ctor()` |
| - | 0x2F0FFB0 |  | `private void RefreshValues()` |

</details>

### public class `UiCustomizationButton` : MonoBehaviour  
`TypeDefIndex 3445`

| offset | field |
|---|---|
| - | `private static uint <DesktopLayoutRevision>k__BackingField;` |
| 0x20 | `private sk _buttonType;` |
| 0x24 | `private float _radius;` |
| 0x28 | `private GameObject selectedFrame;` |
| 0x30 | `private List<Image> mainImages;` |
| 0x38 | `private readonly Color kMn;` |
| 0x48 | `private readonly Color kMV;` |
| 0x58 | `private readonly Color kMg;` |
| - | `private const float kMp = 25;` |
| - | `private const float kMv = 0.45;` |
| 0x90 | `private Vector3 Oed;` |
| 0x9C | `private Vector3 Oec;` |
| 0xA8 | `private Vector3 OeU;` |
| 0xB8 | `private sA OeY;` |
| 0xC0 | `private bool OeW;` |
| 0xC8 | `private sF OeE;` |
| 0xD0 | `private float OeA;` |
| - | `private bool kReady;` |
| - | `private bool applied;` |
| - | `private Vector3 authoredLocalPosition;` |
| - | `private bool hasAuthoredPosition;` |
| - | `private Vector2 authoredAnchoredPosition;` |
| - | `private float removingScale;` |
| - | `private Action<UiCustomizationButton, PointerEventData> kMM_;` |
| - | `private Action<UiCustomizationButton, PointerEventData> Oee_;` |
| - | `private Action<UiCustomizationButton, PointerEventData> Oef_;` |
| - | `private Action<UiCustomizationButton, PointerEventData> OeF_;` |
| - | `public static bool UseAuthoredLayout;` |
| - | `private bool layoutApplied;` |
| - | `private Rect appliedParentRect;` |
| - | `private sA appliedSettings;` |
| - | `private bool appliedAuthored;` |
| - | `private CanvasGroup removedGroup;` |
| - | `private bool hiddenByLayout;` |
| - | `private float shownAlpha;` |
| - | `private bool shownRaycasts;` |
| - | `private bool shownInteractable;` |

Properties: `public static uint DesktopLayoutRevision { get; set; }`; `public float slB { get; }`; `public sk slm { get; }`; `public bool slR { get; set; }`; `public float slb { get; set; }`; `public float sll { get; set; }`; `private Vector3 slx { get; set; }`; `private float slK { get; set; }`; `private float slG { get; set; }`; `public bool slP { get; set; }`; `public bool kMS { get; set; }`; `public bool kMI { get; set; }`; `public Vector3 LastValidPosition { get; set; }`

<details><summary>methods (61)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F1083C |  | `public static uint get_DesktopLayoutRevision()` |
| - | 0x2F10884 |  | `private static void set_DesktopLayoutRevision(uint value)` |
| - | 0x2F108D0 |  | `private void OnTransformParentChanged()` |
| - | 0x2F10944 |  | `private void OnDestroy()` |
| - | 0x2F109B8 |  | `public float get_slB()` |
| - | 0x2F109D4 |  | `public sk get_slm()` |
| - | 0x2F109DC |  | `public bool get_slR()` |
| - | 0x2F10AAC |  | `public void set_slR(bool value)` |
| - | 0x2F0FF38 |  | `public float get_slb()` |
| - | 0x2F10AC0 |  | `public void set_slb(float value)` |
| - | 0x2F0FDAC |  | `public float get_sll()` |
| - | 0x2F10B54 |  | `public void set_sll(float value)` |
| - | 0x2F10D24 |  | `private Vector3 get_slx()` |
| - | 0x2F10ED0 |  | `private void set_slx(Vector3 value)` |
| - | 0x2F110A4 |  | `private float get_slK()` |
| - | 0x2F110BC |  | `private void set_slK(float value)` |
| - | 0x2F110CC |  | `private float get_slG()` |
| - | 0x2F110E4 |  | `private void set_slG(float value)` |
| 0x380D530 | 0x2F110F4 |  | `public bool get_slP()` |
| 0x380D558 | 0x2F1117C |  | `public void set_slP(bool value)` |
| - | 0x2F11214 |  | `public bool get_kMS()` |
| - | 0x2F1121C |  | `private void set_kMS(bool value)` |
| - | 0x2F11228 |  | `public bool get_kMI()` |
| - | 0x2F11230 |  | `private void set_kMI(bool value)` |
| 0x380D5B0 | 0x2F1123C |  | `public void add_kMM(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D660 | 0x2F112E4 |  | `public void remove_kMM(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D710 | 0x2F1138C |  | `public void add_Oee(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D7C0 | 0x2F11434 |  | `public void remove_Oee(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D870 | 0x2F114DC |  | `public void add_Oef(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D920 | 0x2F11584 |  | `public void remove_Oef(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380D9D0 | 0x2F1162C |  | `public void add_OeF(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380DA80 | 0x2F116D4 |  | `public void remove_OeF(Action<UiCustomizationButton, PointerEventData> value)` |
| 0x380DB30 | 0x2F1177C |  | `private void Awake()` |
| 0x380DC40 | 0x2F1197C |  | `private void OnEnable()` |
| 0x380DC84 | 0x2F11E88 |  | `public void dXt()` |
| 0x380E258 | 0x2F11B30 |  | `public void dXr()` |
| 0x380E54C | 0x2F124C0 |  | `public void dXN()` |
| 0x380E63C | 0x2F12794 |  | `public void dXq()` |
| 0x380E708 | 0x2F12948 |  | `public void dXs(Vector2 e, Vector2 f)` |
| 0x380E870 | 0x2F12BF4 |  | `public void dXC()` |
| 0x380E874 | 0x2F12BF8 |  | `private void Update()` |
| 0x380E624 | 0x2F12D5C |  | `public void dXZ(Vector3 e, bool f = false)` |
| 0x380E7EC | 0x2F12A78 |  | `public void dXj()` |
| 0x380E960 | 0x2F12DC0 |  | `public void dXa()` |
| 0x380E974 | 0x2F12DDC |  | `public void dXQ(bool e)` |
| 0x380E9C0 | 0x2F12E28 |  | `public void dXH(bool e)` |
| 0x380EA0C | 0x2F12E74 |  | `public void dXi()` |
| 0x380E3C0 | 0x2F125C4 |  | `private void dXw(Color e)` |
| 0x380EB3C | 0x2F12F10 |  | `private void dXJ(PointerEventData e)` |
| 0x380EB6C | 0x2F12F40 |  | `private void dXX(PointerEventData e)` |
| 0x380EBD0 | 0x2F12FF4 |  | `private void dXT(PointerEventData e)` |
| 0x380EC00 | 0x2F13024 |  | `private void OnClick(PointerEventData eventData)` |
| 0x380EC30 | 0x2F13054 |  | `public void .ctor()` |
| 0x380EC60 | 0x2F130A8 |  | `private void dXL()` |
| - | 0x2F12EA4 |  | `private IEnumerator RemoveAnimated()` |
| - | 0x2F130F4 |  | `private void OnDisable()` |
| - | 0x2F1317C |  | `private void ApplyRenderedLayout()` |
| - | 0x2F122D4 |  | `private void HideRemoved(bool removed)` |
| - | 0x2F11E1C |  | `private IEnumerator ApplyAfterCanvasLayout()` |
| - | 0x2F13548 |  | `public Vector3 get_LastValidPosition()` |
| - | 0x2F13554 |  | `public void set_LastValidPosition(Vector3 value)` |

</details>

### public class `UiCustomizationForbiddenArea` : MonoBehaviour  
`TypeDefIndex 3446`

| offset | field |
|---|---|
| 0x20 | `private float _width;` |
| 0x24 | `private float _height;` |
| 0x28 | `private float Oeu;` |

Properties: `private float slD { get; }`; `private float sln { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x380EC84 | 0x2F138A4 |  | `private float get_slD()` |
| 0x380EC94 | 0x2F138AC |  | `private float get_sln()` |
| 0x380ECA0 | 0x2F138B4 |  | `private void Awake()` |
| 0x380ED0C | 0x2F138E0 |  | `public sU.RectCorners dXz()` |
| 0x380EDCC | 0x2F139B4 |  | `public void .ctor()` |

</details>

### public class `UiCustomizationRemoveArea` : MonoBehaviour  
`TypeDefIndex 3447`

| offset | field |
|---|---|
| 0x20 | `private float _width;` |
| 0x24 | `private float _height;` |
| 0x28 | `private float Oek;` |

Properties: `private float slV { get; }`; `private float slg { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x380EDE0 | 0x2F139BC |  | `private float get_slV()` |
| 0x380EDF0 | 0x2F139C4 |  | `private float get_slg()` |
| 0x380EDFC | 0x2F139CC |  | `private void Awake()` |
| 0x380EE68 | 0x2F139F8 |  | `public sU.RectCorners dXm()` |
| 0x380EEE8 | 0x2F13ACC |  | `public void .ctor()` |

</details>

### public class `UiCustomizationScreen` : MonoBehaviour  
`TypeDefIndex 3450`

| offset | field |
|---|---|
| 0x20 | `private UiButtonsSettingsView _uiButtonsSettingsView;` |
| 0x28 | `private RectTransform _content;` |
| 0x30 | `private Button _cancelButton;` |
| 0x38 | `private Button _saveButton;` |
| 0x40 | `private Button _defaultButton;` |
| 0x48 | `private List<UiCustomizationButton> OeN;` |
| 0x50 | `private List<UiCustomizationForbiddenArea> Oeq;` |
| 0x58 | `private UiCustomizationRemoveArea Oes;` |
| 0x60 | `private UiCustomizationButton OeC;` |
| 0x68 | `private UiSettingsDatabase OeZ;` |
| - | `public const float MaxButtonScale = 2;` |
| - | `public const float MinButtonScale = 0.5;` |
| - | `public const float MaxButtonOpacity = 1;` |
| - | `public const float MinButtonOpacity = 0.1;` |
| - | `private const float Oej = 40;` |
| - | `private bool wired;` |

<details><summary>methods (23)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x380EEFC | 0x2F13AD4 |  | `private void Awake()` |
| 0x380F004 | 0x2F13FF0 |  | `private void dXK(UiSettingsDatabase e)` |
| 0x380F00C | 0x2F13FF8 |  | `private void Start()` |
| 0x380F160 | 0x2F140D4 |  | `private void OnEnable()` |
| 0x380F194 | 0x2F14168 |  | `private IEnumerator dXG()` |
| 0x380F228 | 0x2F141FC |  | `private void OnDisable()` |
| 0x380F5A0 | 0x2F1457C |  | `private void dXP()` |
| 0x380F5C4 | 0x2F14728 |  | `private void dXD()` |
| 0x380F80C | 0x2F14C2C |  | `private void dXn()` |
| 0x380CE0C | 0x2F102A0 |  | `public void dXV(UiCustomizationButton e, float f)` |
| 0x380D004 | 0x2F10468 |  | `public void dXg(UiCustomizationButton e, float f)` |
| 0x380FDE0 | 0x2F15528 |  | `private void dXp(UiCustomizationButton e, PointerEventData f)` |
| 0x380FEE8 | 0x2F156BC |  | `private void dXv(UiCustomizationButton e, PointerEventData f)` |
| 0x380FE1C | 0x2F155BC |  | `private void dXS(UiCustomizationButton e)` |
| 0x380FF2C | 0x2F15774 |  | `private void dXI(UiCustomizationButton e, PointerEventData f)` |
| 0x3810024 | 0x2F158B0 |  | `private void dXM(UiCustomizationButton e, PointerEventData f)` |
| 0x380F960 | 0x2F14FA0 |  | `private bool dTe(Vector3 e, float f = 1)` |
| 0x380F9CC | 0x2F15070 |  | `private bool dTf(UiCustomizationButton e, Vector3 f, float F)` |
| 0x38103B0 | 0x2F15A4C |  | `private bool dTF()` |
| 0x3810408 | 0x2F15A5C |  | `private List<Vector2> dTd()` |
| 0x38106B4 | 0x2F15D08 |  | `public void .ctor()` |
| - | 0x2F13C90 |  | `private void PrepareJoystickEditing()` |
| - | 0x2F14DF4 |  | `private void SelectJoystick()` |

</details>
