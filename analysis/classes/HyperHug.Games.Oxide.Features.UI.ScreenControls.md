# namespace `HyperHug.Games.Oxide.Features.UI.ScreenControls`  (7 types)

### public class `OnScreenColorSwitchButton` : OnScreenCustomButton  
`TypeDefIndex 3464`

| offset | field |
|---|---|
| 0x60 | `protected Image[] images;` |
| 0x68 | `protected Color colorUp;` |
| 0x78 | `protected Color colorDown;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3819334 | 0x2F17378 | 14 | `public override void doW(bool e)` |
| 0x3819418 | 0x2F17438 |  | `public void .ctor()` |

</details>

### public class `OnScreenCustomButton` : OnScreenControl, IPointerDownHandler, IEventSystemHandler, IDragHandler, IPointerUpHandler  
`TypeDefIndex 3465`

| offset | field |
|---|---|
| 0x38 | `private sQ buttonType;` |
| 0x3C | `private bool setStateOnPressed;` |
| 0x3D | `private bool longPress;` |
| 0x40 | `private float longPressTime;` |
| 0x48 | `private OnScreenCustomButton mirrorButton;` |
| 0x50 | `private bool cancelledPointerRelease;` |
| - | `private bool Ofa;` |
| 0x51 | `private bool OfQ;` |
| 0x52 | `private bool OfH;` |
| 0x53 | `private bool Ofi;` |
| 0x58 | `private string m_ControlPath;` |

Properties: `protected override string controlPathInternal { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F17448 |  | `public void ResetPressedState()` |
| - | 0x2F174F0 |  | `protected override string get_controlPathInternal()` |
| - | 0x2F174F8 |  | `protected override void set_controlPathInternal(string value)` |
| 0x3819428 | 0x2F17500 | 6 | `protected override void OnEnable()` |
| 0x3819448 | 0x2F17520 | 7 | `protected override void OnDisable()` |
| 0x38194D0 | 0x2F17590 | 10 | `public virtual void SetActive(bool active)` |
| 0x38194DC | 0x2F1759C | 11 | `public virtual void OnPointerUp(PointerEventData eventData)` |
| 0x3819560 | 0x2F17620 |  | `private void doE()` |
| 0x3819764 | 0x2F17804 | 12 | `public virtual void OnPointerDown(PointerEventData eventData)` |
| 0x38197E8 | 0x2F17890 |  | `private void doA()` |
| 0x38198B8 | 0x2F1794C |  | `private void OnLongPress()` |
| 0x38198C8 | 0x2F1795C | 13 | `public virtual void dou(bool e)` |
| 0x381992C | 0x2F179C0 | 14 | `public virtual void doW(bool e)` |
| 0x3819684 | 0x2F1773C |  | `public void dok(bool e)` |
| 0x3819930 | 0x2F179C4 |  | `private void Update()` |
| 0x3819420 | 0x2F17440 |  | `public void .ctor()` |
| - | 0x2F17A40 |  | `public void OnDrag(PointerEventData eventData)` |

</details>

### public class `OnScreenMouse` : OnScreenControl, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IDragHandler  
`TypeDefIndex 3466`

| offset | field |
|---|---|
| 0x0 | `public static Vector2 Delta;` |
| - | `public static float DeltaSeconds;` |
| - | `private int activePointer;` |
| 0x38 | `private string controlPath;` |
| 0x40 | `private bool Ofw;` |
| 0x41 | `private bool OfJ;` |

Properties: `protected override string controlPathInternal { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3819AE4 | 0x2F17A44 | 4 | `protected override string get_controlPathInternal()` |
| 0x3819AEC | 0x2F17A4C | 5 | `protected override void set_controlPathInternal(string value)` |
| 0x38199BC | 0x2F17A54 | 8 | `public void OnPointerDown(PointerEventData eventData)` |
| 0x3819A44 | 0x2F17B94 | 9 | `public void OnPointerUp(PointerEventData eventData)` |
| 0x3819A48 | 0x2F17C08 | 10 | `public void OnDrag(PointerEventData eventData)` |
| 0x3819AB0 | 0x2F17D34 |  | `private void Update()` |
| 0x38199C0 | 0x2F17B04 |  | `private void doO()` |
| 0x3819AF4 | 0x2F17D68 |  | `public void .ctor()` |
| - | 0x2F17D78 |  | `protected override void OnDisable()` |
| - | 0x2F17D9C |  | `private void OnApplicationFocus(bool focused)` |

</details>

### public class `OnScreenSpriteSwitchButton` : OnScreenCustomButton  
`TypeDefIndex 3467`

| offset | field |
|---|---|
| 0x60 | `protected Image[] images;` |
| 0x68 | `protected Sprite[] spritesUp;` |
| 0x70 | `protected Sprite[] spritesDown;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3819AFC | 0x2F17DC8 | 14 | `public override void doW(bool e)` |
| 0x3819B84 | 0x2F17E50 | 10 | `public override void SetActive(bool isActive)` |
| 0x3819BF0 | 0x2F17EC0 |  | `public void .ctor()` |

</details>

### public class `ScreenControlsManager` : MonoBehaviour  
`TypeDefIndex 3469`

| offset | field |
|---|---|
| 0x20 | `private ScreenControlsSet[] screenControlsSets;` |
| 0x28 | `private Dictionary<sH, ScreenControlsSet> OfX;` |
| - | `private sH <OfT>k__BackingField;` |
| - | `private sH <OfL>k__BackingField;` |

Properties: `public sH OfT { get; set; }`; `public sH OfL { get; set; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F17EC8 |  | `public sH get_OfT()` |
| - | 0x2F17ED0 |  | `private void set_OfT(sH value)` |
| - | 0x2F17ED8 |  | `public sH get_OfL()` |
| - | 0x2F17EE0 |  | `private void set_OfL(sH value)` |
| 0x3819C18 | 0x2F17EE8 |  | `private void Awake()` |
| - | 0x2F17EEC |  | `private IEnumerator Start()` |
| 0x38083BC | 0x2F17F80 |  | `public void dos(sH e)` |
| 0x3819D10 | 0x2F186AC |  | `public void doC()` |
| 0x3819D18 | 0x2F186B4 |  | `public void .ctor()` |

</details>

### public class `ScreenControlsReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3470`

| offset | field |
|---|---|
| - | `private OnScreenCustomButton <AimLeftButton>k__BackingField;` |
| - | `private OnScreenCustomButton <AimRightButton>k__BackingField;` |
| - | `private OnScreenCustomButton <CrouchButton>k__BackingField;` |
| - | `private OnScreenCustomButton <SprintButton>k__BackingField;` |
| - | `private GameObject <FixedJoystick>k__BackingField;` |
| - | `private GameObject <FloatingJoystick>k__BackingField;` |
| - | `private GameObject <AttackLeftButton>k__BackingField;` |
| - | `private GameObject <AttackRightButton>k__BackingField;` |

Properties: `public OnScreenCustomButton AimLeftButton { get; set; }`; `public OnScreenCustomButton AimRightButton { get; set; }`; `public OnScreenCustomButton CrouchButton { get; set; }`; `public OnScreenCustomButton SprintButton { get; set; }`; `public GameObject FixedJoystick { get; set; }`; `public GameObject FloatingJoystick { get; set; }`; `public GameObject AttackLeftButton { get; set; }`; `public GameObject AttackRightButton { get; set; }`

<details><summary>methods (21)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F18810 |  | `public OnScreenCustomButton get_AimLeftButton()` |
| - | 0x2F18818 |  | `private void set_AimLeftButton(OnScreenCustomButton value)` |
| - | 0x2F18820 |  | `public OnScreenCustomButton get_AimRightButton()` |
| - | 0x2F18828 |  | `private void set_AimRightButton(OnScreenCustomButton value)` |
| - | 0x2F18830 |  | `public OnScreenCustomButton get_CrouchButton()` |
| - | 0x2F18838 |  | `private void set_CrouchButton(OnScreenCustomButton value)` |
| - | 0x2F18840 |  | `public OnScreenCustomButton get_SprintButton()` |
| - | 0x2F18848 |  | `private void set_SprintButton(OnScreenCustomButton value)` |
| - | 0x2F18850 |  | `public GameObject get_FixedJoystick()` |
| - | 0x2F18858 |  | `private void set_FixedJoystick(GameObject value)` |
| - | 0x2F18860 |  | `public GameObject get_FloatingJoystick()` |
| - | 0x2F18868 |  | `private void set_FloatingJoystick(GameObject value)` |
| - | 0x2F18870 |  | `public GameObject get_AttackLeftButton()` |
| - | 0x2F18878 |  | `private void set_AttackLeftButton(GameObject value)` |
| - | 0x2F18880 |  | `public GameObject get_AttackRightButton()` |
| - | 0x2F18888 |  | `private void set_AttackRightButton(GameObject value)` |
| 0x3819DA8 | 0x2F18890 |  | `public void .ctor()` |
| - | 0x2F1850C |  | `public void ApplyJoystickPreference()` |
| - | 0x2F189C4 |  | `private static void SetMouse(GameObject target, bool enabled)` |
| - | 0x2F18AA0 |  | `private void OnEnable()` |
| - | 0x2F18898 |  | `private static void ApplyJoystick(GameObject target, bool selected)` |

</details>

### public class `ScreenControlsSet`  
`TypeDefIndex 3471`

| offset | field |
|---|---|
| 0x10 | `public sH screenControlsType;` |
| 0x18 | `public GameObject[] screenControls;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3819D20 | 0x2F18AA4 |  | `public void .ctor()` |

</details>
