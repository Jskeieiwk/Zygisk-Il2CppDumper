# namespace `UnityEngine.UI`  (1 types)

### public class `ScrollRectEx` : UIBehaviour, IInitializePotentialDragHandler, IEventSystemHandler, IBeginDragHandler, IEndDragHandler, IDragHandler, IScrollHandler, ICanvasElement, ILayoutGroup, ILayoutController  
`TypeDefIndex 2719`

| offset | field |
|---|---|
| 0x20 | `public PointerEventData.InputButton scrollButton;` |
| 0x24 | `public PointerEventData.InputButton altScrollButton;` |
| 0x28 | `private RectTransform m_Content;` |
| 0x30 | `private bool m_Horizontal;` |
| 0x31 | `private bool m_Vertical;` |
| 0x34 | `private ScrollRectEx.Om m_MovementType;` |
| 0x38 | `private float m_Elasticity;` |
| 0x3C | `private bool m_Inertia;` |
| 0x40 | `private float m_DecelerationRate;` |
| 0x44 | `private float m_ScrollSensitivity;` |
| 0x48 | `private RectTransform m_Viewport;` |
| 0x50 | `private Scrollbar m_HorizontalScrollbar;` |
| 0x58 | `private Scrollbar m_VerticalScrollbar;` |
| 0x60 | `private ScrollRectEx.OR m_HorizontalScrollbarVisibility;` |
| 0x64 | `private ScrollRectEx.OR m_VerticalScrollbarVisibility;` |
| 0x68 | `private float m_HorizontalScrollbarSpacing;` |
| 0x6C | `private float m_VerticalScrollbarSpacing;` |
| 0x70 | `private ScrollRectEx.ScrollRectEvent m_OnValueChanged;` |
| 0x78 | `private Vector2 kbI;` |
| 0x80 | `private Vector2 kbM;` |
| 0x88 | `private RectTransform kle;` |
| 0x90 | `private Bounds klf;` |
| 0xA8 | `private Bounds klF;` |
| 0xC0 | `private Vector2 kld;` |
| 0xC8 | `private bool klc;` |
| 0xCC | `private Vector2 klU;` |
| 0xD4 | `private Bounds klY;` |
| 0xEC | `private Bounds klW;` |
| 0x104 | `private bool klE;` |
| 0x105 | `private bool klA;` |
| 0x106 | `private bool klu;` |
| 0x108 | `private float klk;` |
| 0x10C | `private float klO;` |
| 0x110 | `private RectTransform klt;` |
| 0x118 | `private RectTransform klr;` |
| 0x120 | `private RectTransform klN;` |
| 0x128 | `private DrivenRectTransformTracker klq;` |
| 0x130 | `private readonly Vector3[] kls;` |

Properties: `public RectTransform smN { get; set; }`; `public bool smq { get; set; }`; `public bool sms { get; set; }`; `public ScrollRectEx.Om smC { get; set; }`; `public float smZ { get; set; }`; `public bool smj { get; set; }`; `public float sma { get; set; }`; `public float smQ { get; set; }`; `public RectTransform smH { get; set; }`; `public Scrollbar smi { get; set; }`; `public Scrollbar smw { get; set; }`; `public ScrollRectEx.OR smJ { get; set; }`; `public ScrollRectEx.OR smX { get; set; }`; `public float smT { get; set; }`; `public float smL { get; set; }`; `public ScrollRectEx.ScrollRectEvent smo { get; set; }`; `protected RectTransform smy { get; }`; `public Vector2 smz { get; set; }`; `private RectTransform smh { get; }`; `public Vector2 smB { get; set; }`; `public float smm { get; set; }`; `public float smR { get; set; }`; `private bool smb { get; }`; `private bool sml { get; }`

<details><summary>methods (80)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DEDC98 |  | `public RectTransform get_smN()` |
| - | 0x2DEDCA0 |  | `public void set_smN(RectTransform value)` |
| - | 0x2DEDD84 |  | `public bool get_smq()` |
| - | 0x2DEDD8C |  | `public void set_smq(bool value)` |
| - | 0x2DEDD98 |  | `public bool get_sms()` |
| - | 0x2DEDDA0 |  | `public void set_sms(bool value)` |
| - | 0x2DEDDAC |  | `public ScrollRectEx.Om get_smC()` |
| - | 0x2DEDDB4 |  | `public void set_smC(ScrollRectEx.Om value)` |
| - | 0x2DEDDBC |  | `public float get_smZ()` |
| - | 0x2DEDDC4 |  | `public void set_smZ(float value)` |
| - | 0x2DEDDCC |  | `public bool get_smj()` |
| - | 0x2DEDDD4 |  | `public void set_smj(bool value)` |
| - | 0x2DEDDE0 |  | `public float get_sma()` |
| - | 0x2DEDDE8 |  | `public void set_sma(float value)` |
| - | 0x2DEDDF0 |  | `public float get_smQ()` |
| - | 0x2DEDDF8 |  | `public void set_smQ(float value)` |
| - | 0x2DEDE00 |  | `public RectTransform get_smH()` |
| - | 0x2DEDE08 |  | `public void set_smH(RectTransform value)` |
| - | 0x2DEDE24 |  | `public Scrollbar get_smi()` |
| - | 0x2DEDE2C |  | `public void set_smi(Scrollbar value)` |
| - | 0x2DEDE48 |  | `public Scrollbar get_smw()` |
| - | 0x2DEDE50 |  | `public void set_smw(Scrollbar value)` |
| - | 0x2DEDE6C |  | `public ScrollRectEx.OR get_smJ()` |
| - | 0x2DEDE74 |  | `public void set_smJ(ScrollRectEx.OR value)` |
| - | 0x2DEDE7C |  | `public ScrollRectEx.OR get_smX()` |
| - | 0x2DEDE84 |  | `public void set_smX(ScrollRectEx.OR value)` |
| - | 0x2DEDE8C |  | `public float get_smT()` |
| - | 0x2DEDE94 |  | `public void set_smT(float value)` |
| - | 0x2DEDE9C |  | `public float get_smL()` |
| - | 0x2DEDEA4 |  | `public void set_smL(float value)` |
| - | 0x2DEDEAC |  | `public ScrollRectEx.ScrollRectEvent get_smo()` |
| - | 0x2DEDEB4 |  | `public void set_smo(ScrollRectEx.ScrollRectEvent value)` |
| - | 0x2DEDED0 |  | `protected RectTransform get_smy()` |
| - | 0x2DEE024 |  | `public Vector2 get_smz()` |
| - | 0x2DEE02C |  | `public void set_smz(Vector2 value)` |
| - | 0x2DEDF88 |  | `private RectTransform get_smh()` |
| - | 0x2DEE034 |  | `public Vector2 get_smB()` |
| - | 0x2DEE124 |  | `public void set_smB(Vector2 value)` |
| - | 0x2DEE064 |  | `public float get_smm()` |
| - | 0x2DEE5A4 |  | `public void set_smm(float value)` |
| - | 0x2DEE0C4 |  | `public float get_smR()` |
| - | 0x2DEE5AC |  | `public void set_smR(float value)` |
| - | 0x2DEE5B4 |  | `private bool get_smb()` |
| - | 0x2DEE63C |  | `private bool get_sml()` |
| 0x375F0C8 | 0x2DEE6C4 |  | `protected void .ctor()` |
| 0x375F228 | 0x2DEE7D8 | 29 | `public virtual void Rebuild(CanvasUpdate executing)` |
| 0x375F2B0 | 0x2DEE860 |  | `private void dUr()` |
| 0x375F888 | 0x2DEEE38 | 5 | `protected override void OnEnable()` |
| 0x375FA2C | 0x2DEF07C | 7 | `protected override void OnDisable()` |
| 0x375FC54 | 0x2DEF2AC | 9 | `public override bool IsActive()` |
| 0x375FCD4 | 0x2DEF32C |  | `private void dUN()` |
| 0x375FD48 | 0x2DEF3A0 | 30 | `public virtual void dUq()` |
| 0x375FD98 | 0x2DEF3F0 | 31 | `public virtual void OnScroll(PointerEventData data)` |
| 0x375FFD0 | 0x2DEF660 | 32 | `public virtual void OnInitializePotentialDrag(PointerEventData eventData)` |
| 0x3760044 | 0x2DEF6D4 | 33 | `public virtual void OnBeginDrag(PointerEventData eventData)` |
| 0x3760184 | 0x2DEF814 | 34 | `public virtual void OnEndDrag(PointerEventData eventData)` |
| 0x37601B8 | 0x2DEF848 | 35 | `public virtual void OnDrag(PointerEventData eventData)` |
| 0x37603DC | 0x2DEFA74 | 36 | `protected virtual void dUs(Vector2 e)` |
| 0x3760490 | 0x2DEFB28 | 37 | `protected virtual void LateUpdate()` |
| 0x375F7B0 | 0x2DEED60 |  | `private void dUC()` |
| 0x375F628 | 0x2DEEBD8 |  | `private void dUZ(Vector2 e)` |
| 0x3760B7C | 0x2DF0188 |  | `private void dUj(float e)` |
| 0x3760B84 | 0x2DF0190 |  | `private void dUa(float e)` |
| 0x375EB68 | 0x2DEE154 |  | `private void dUQ(float e, int f)` |
| 0x37603A4 | 0x2DEFA3C |  | `private static float dUH(float e, float f)` |
| 0x3760B8C | 0x2DF0198 | 10 | `protected override void OnRectTransformDimensionsChange()` |
| 0x3760B90 | 0x2DF019C | 38 | `public virtual void SetLayoutHorizontal()` |
| 0x37612BC | 0x2DF08C0 | 39 | `public virtual void SetLayoutVertical()` |
| 0x3760A10 | 0x2DF0084 |  | `private void dUi()` |
| 0x3761374 | 0x2DF0978 |  | `private void dUw()` |
| 0x375EDEC | 0x2DEE3EC |  | `private void dUJ()` |
| 0x3761078 | 0x2DF0680 |  | `private Bounds dUX()` |
| 0x375FED4 | 0x2DEF52C |  | `private Vector2 dUT(Vector2 e)` |
| 0x375E7E0 | 0x2DEEFF4 |  | `protected void dUL()` |
| 0x375E3C8 | 0x2DEDCBC |  | `protected void dUo()` |
| 0x37615D0 | 0x2DF0BCC |  | `public void dUy(Vector2 e)` |
| 0x376176C | 0x2DF0D0C | 24 | `public void LayoutComplete()` |
| 0x3761770 | 0x2DF0D10 | 25 | `public void GraphicUpdateComplete()` |
| 0x3761774 | 0x2DF0D14 | 23 | `private Transform dUz()` |
| - | 0x2DF0D1C |  | `private Transform UnityEngine.UI.ICanvasElement.get_transform()` |

</details>
