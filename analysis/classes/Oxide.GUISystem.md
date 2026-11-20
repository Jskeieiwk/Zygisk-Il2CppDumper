# namespace `Oxide.GUISystem`  (64 types)

### public class `AnvilGUI` : yD  
`TypeDefIndex 2985`

| offset | field |
|---|---|
| 0x28 | `private Text m_RequiredItemsText;` |
| 0x30 | `private Color m_HasEnoughColor;` |
| 0x40 | `private Color m_NotEnoughColor;` |
| 0x50 | `private Image m_ProgressBar;` |
| 0x58 | `private Button m_RepairButton;` |
| 0x60 | `public ItemContainer m_InputContainer;` |
| 0x68 | `public ItemContainer m_ResultContainer;` |
| 0x70 | `private ItemContainer OMX;` |
| 0x78 | `private string OMT;` |
| 0x80 | `private string OML;` |
| 0x88 | `private Anvil OMo;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB2368 | 0x2E69550 |  | `private void Awake()` |
| 0x3AB2504 | 0x2E6966C |  | `private void Start()` |
| 0x3AB2634 | 0x2E69778 |  | `public void Update()` |
| 0x3AB26C0 | 0x2E6983C |  | `private void UuT()` |
| 0x3AB2708 | 0x2E6991C |  | `private void UuL()` |
| 0x3AB28B8 | 0x2E69920 |  | `private bool Uuo(ItemHolder[] e)` |
| 0x3AB2F64 | 0x2E6A028 |  | `private void Uuy(Slot e)` |
| 0x3AB2B28 | 0x2E69BA4 |  | `public void Uuz()` |
| 0x3AB2F68 | 0x2E6A02C |  | `public void .ctor()` |

</details>

### public class `AutoTurretGUI` : yD  
`TypeDefIndex 2986`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |
| 0x30 | `private AutoTurretBase OIN;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA7888 | 0x2E6A034 |  | `private void Start()` |
| 0x3AA79C0 | 0x2E6A20C |  | `private bool UEb(ItemHolder[] e)` |
| 0x3AA7B60 | 0x2E6A6D8 |  | `private void UEl()` |
| 0x3AA7BD4 | 0x2E6A798 |  | `private void OnDestroy()` |
| 0x3AA7CF0 | 0x2E6A8A8 |  | `public void .ctor()` |

</details>

### public class `BigLootOpener` : MonoBehaviour  
`TypeDefIndex 2987`

| offset | field |
|---|---|
| 0x20 | `private ItemContainer m_ItemContainer;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA7CF8 | 0x2E6A8B0 |  | `private void Start()` |
| 0x3AA7DAC | 0x2E6A9C4 |  | `private bool UEx(ItemHolder[] e)` |
| 0x3AA7E70 | 0x2E6AACC |  | `public void .ctor()` |

</details>

### public class `BuildingCategory` : Selectable  
`TypeDefIndex 2988`

| offset | field |
|---|---|
| 0x100 | `public BuildingWheel BuildingMenu;` |
| 0x108 | `public Vector2 DesiredOffset;` |
| 0x110 | `public float Distance;` |
| 0x114 | `public float Offset;` |
| 0x118 | `public float Spacing;` |
| 0x120 | `public Wp.Phrase CategoryName;` |
| 0x128 | `public Wp.Phrase CategoryDescription;` |
| 0x130 | `public int CategoryIndex;` |
| 0x138 | `public AssetReference BuildableObjectRef;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA8440 | 0x2E6AAD4 |  | `public void UED(bool e)` |
| 0x3AA8444 | 0x2E6AAD8 | 32 | `public override void OnPointerDown(PointerEventData eventData)` |
| 0x3AA87E0 | 0x2E6AF04 |  | `public void .ctor()` |

</details>

### public class `BuildingPiece` : MonoBehaviour  
`TypeDefIndex 2989`

| offset | field |
|---|---|
| 0x20 | `private string m_PieceName;` |
| 0x28 | `private Vector2 m_DesiredOffset;` |
| 0x30 | `private BuildingPiece m_BuildableObject;` |
| 0x38 | `private Image OIj;` |
| 0x40 | `private Color OIa;` |

Properties: `public string Ceo { get; }`; `public Sprite Cey { get; }`; `public Vector2 Cez { get; }`; `public BuildingPiece Ceh { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA8838 | 0x2E6AF5C |  | `public string get_Ceo()` |
| 0x3AA8840 | 0x2E6AF64 |  | `public Sprite get_Cey()` |
| 0x3AA885C | 0x2E6AF80 |  | `public Vector2 get_Cez()` |
| 0x3AA8864 | 0x2E6AF88 |  | `public BuildingPiece get_Ceh()` |
| 0x3AA886C | 0x2E6AF90 |  | `public void UEv(Color e)` |
| 0x3AA8890 | 0x2E6AFB4 |  | `public void UES()` |
| 0x3AA88C0 | 0x2E6AFE4 |  | `private void Awake()` |
| 0x3AA8944 | 0x2E6B068 |  | `public void .ctor()` |

</details>

### public class `BuildingWheel` : yD  
`TypeDefIndex 2990`

| offset | field |
|---|---|
| - | `private BuildingCategory[] desktopCategories;` |
| 0x28 | `public BuildingCategory SelectedCategory;` |
| 0x30 | `private Window m_Window;` |
| 0x38 | `private Camera m_GUICamera;` |
| 0x40 | `private RectTransform m_SelectionHighlight;` |
| 0x48 | `private Text m_CategoryName;` |
| 0x50 | `private Text m_CategoryDescription;` |
| 0x58 | `private Button m_BuildButton;` |
| 0x60 | `private SoundPlayer m_RefreshAudio;` |
| 0x68 | `private SoundPlayer m_SelectPieceAudio;` |
| 0x70 | `private float m_Distance;` |
| 0x74 | `private float m_Offset;` |
| 0x78 | `private float m_Spacing;` |
| 0x80 | `private BuildingCategory OIQ;` |
| 0x88 | `private int OIH;` |
| 0x90 | `private Button CloseButton;` |

Properties: `public bool DesktopIsOpen { get; }`; `public RectTransform CeB { get; }`; `public float Cem { get; }`; `public float CeR { get; }`; `public float Ceb { get; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E6B070 |  | `public bool get_DesktopIsOpen()` |
| - | 0x2E6B0F4 |  | `public void DesktopHover(Vector2 screenPosition)` |
| - | 0x2E6B1D4 |  | `public BuildingCategory DesktopCategoryAt(Vector2 screenPosition)` |
| - | 0x2E6B650 |  | `public void DesktopFinish(bool confirm)` |
| - | 0x2E6BA4C |  | `public RectTransform get_CeB()` |
| - | 0x2E6BAB0 |  | `public float get_Cem()` |
| - | 0x2E6BAB8 |  | `public float get_CeR()` |
| - | 0x2E6BAC0 |  | `public float get_Ceb()` |
| 0x3AA896C | 0x2E6BAC8 |  | `public void UAF()` |
| 0x3AA8BC8 | 0x2E6BD24 |  | `private void UAd()` |
| 0x3AA8C68 | 0x2E6BDC4 |  | `private void UAc()` |
| 0x3AA8D04 | 0x2E6BF84 |  | `private bool UAU()` |
| 0x3AA8CDC | 0x2E6BE38 |  | `private void UAY()` |
| 0x3AA8F24 | 0x2E6C2E4 |  | `private bool UAW()` |
| 0x3AA846C | 0x2E6AB78 |  | `public void UAE(BuildingCategory e)` |
| 0x3AA91A0 | 0x2E6B7A8 |  | `public void SelectPiece()` |
| 0x3AA9318 | 0x2E6C610 |  | `private void UAA()` |
| 0x3AA93DC | 0x2E6C6D4 |  | `public void .ctor()` |

</details>

### public class `BuyWindow` : MonoBehaviour  
`TypeDefIndex 2991`

| offset | field |
|---|---|
| 0x20 | `private Image icon;` |
| 0x28 | `private Text title;` |
| 0x30 | `private Text description;` |
| 0x38 | `private Text price;` |
| 0x40 | `private Text stack;` |
| 0x48 | `private GameObject message;` |
| 0x50 | `private Button button;` |
| 0x58 | `private PurchaseAmountView purchaseAmountView;` |
| 0x60 | `private PurchaseSlot OIq;` |
| 0x68 | `private NY OIs;` |
| 0x70 | `private int OIC;` |
| 0x74 | `private int OIZ;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA7E78 | 0x2E6C6F8 |  | `public void UEK(PurchaseSlot e, int f = -1)` |
| 0x3AA8138 | 0x2E6CB58 |  | `private void Awake()` |
| 0x3AA8190 | 0x2E6CBB4 |  | `public void Buy()` |
| 0x3AA8274 | 0x2E6CCBC |  | `public void Hide()` |
| 0x3AA7EF8 | 0x2E6C7E8 |  | `private void UEG()` |
| 0x3AA8310 | 0x2E6CDB0 |  | `private void OnEnable()` |
| 0x3AA83A0 | 0x2E6CEBC |  | `private void OnDisable()` |
| 0x3AA8430 | 0x2E6CF88 |  | `private void UEP(int e)` |
| 0x3AA8438 | 0x2E6CFA4 |  | `public void .ctor()` |

</details>

### public class `CharacterEquipmentHandler` : MonoBehaviour  
`TypeDefIndex 2993`

| offset | field |
|---|---|
| 0x20 | `private AudioSource m_AudioSource;` |
| 0x28 | `private SoundPlayer m_EquipAudio;` |
| 0x30 | `private Slot[] slots;` |
| - | `private bool bound;` |
| - | `private readonly Dictionary<ItemHolder, string> wornKeys;` |
| - | `private int lastEquipSoundFrame;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E6CFAC |  | `private string EquipmentKey(ItemHolder holder)` |
| - | 0x2E6D060 |  | `private void OnDestroy()` |
| - | 0x2E6D1C0 |  | `private void Start()` |
| - | 0x2E6D540 |  | `private void Update()` |
| - | 0x2E6D1F4 |  | `private bool TryBind()` |
| - | 0x2E6D4D4 |  | `private IEnumerator BindWhenReady()` |
| - | 0x2E6D578 |  | `private void PlayEquip()` |
| 0x3AA94F0 | 0x2E6D78C |  | `private void UAu(ItemHolder e)` |
| 0x3AA95B0 | 0x2E6D934 |  | `public void .ctor()` |

</details>

### public class `CraftingCategory` : Selectable  
`TypeDefIndex 2994`

| offset | field |
|---|---|
| 0x100 | `public XN<CraftingCategory> Selected;` |
| 0x108 | `private string m_DisplayName;` |
| 0x110 | `private string shortName;` |
| 0x118 | `private ReorderableStringList m_CorrespondingCategories;` |
| 0x120 | `private ReorderableStringList m_SpecialItems;` |

Properties: `public string Cel { get; }`; `public string Cex { get; }`; `public ReorderableStringList CeK { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA95B8 | 0x2E6DA90 |  | `public string get_Cel()` |
| 0x3AA95C0 | 0x2E6DA98 |  | `public string get_Cex()` |
| 0x3AA95C8 | 0x2E6DAA0 |  | `public ReorderableStringList get_CeK()` |
| 0x3AA95D0 | 0x2E6DAA8 |  | `public bool UAr(string e)` |
| 0x3AA9694 | 0x2E6DB6C |  | `public bool UAN(string e)` |
| 0x3AA9758 | 0x2E6DC30 | 32 | `public override void OnPointerDown(PointerEventData eventData)` |
| 0x3AA97C0 | 0x2E6DC98 |  | `public void .ctor()` |

</details>

### public class `CraftingList` : yD  
`TypeDefIndex 2997`

| offset | field |
|---|---|
| 0x28 | `public Xr RecipesGenerated;` |
| 0x30 | `private CraftingMenu m_CraftingMenu;` |
| 0x38 | `private RectTransform m_ListTransform;` |
| 0x40 | `private RecipeSlot m_RecipeTemplate;` |
| 0x48 | `private zd m_TechTreeGUI;` |
| 0x50 | `private List<yJ> OIX;` |
| 0x58 | `private List<RecipeSlot> OIT;` |
| 0x60 | `private List<RecipeSlot> OIL;` |

Properties: `public List<yJ> CeD { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA9A28 | 0x2E6DD68 |  | `public List<yJ> get_CeD()` |
| 0x3AA9A30 | 0x2E6DD70 |  | `private void Awake()` |
| 0x3AA9B2C | 0x2E6DE6C |  | `private void Start()` |
| 0x3AAA138 | 0x2E6E46C |  | `private void UAQ()` |
| 0x3AAA168 | 0x2E6E4A0 |  | `private void UAi()` |
| 0x3AAA5E0 | 0x2E6E91C |  | `private RecipeSlot UAw(string e)` |
| 0x3AA9B64 | 0x2E6DEA4 |  | `private void UAJ()` |
| 0x3AAA984 | 0x2E6EBF8 |  | `public void UAX()` |
| 0x3AAAB60 | 0x2E6EDA0 |  | `public void UAT()` |
| 0x3AAAD0C | 0x2E6EF48 |  | `public void .ctor()` |

</details>

### public class `CraftingMenu` : MonoBehaviour  
`TypeDefIndex 2998`

| offset | field |
|---|---|
| 0x20 | `public Xq<CraftingCategory> SelectedCategory;` |
| 0x28 | `private CraftingCategory m_FirstSelected;` |
| 0x30 | `private Text m_CategoryName;` |
| 0x38 | `private CraftingCategory[] OIo;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AAAEBC | 0x2E6F0C8 |  | `private void Awake()` |
| 0x3AAB068 | 0x2E6F258 |  | `private void Start()` |
| 0x3AAB0E0 | 0x2E6F2D0 |  | `private void UAL(CraftingCategory e)` |
| 0x3AAB204 | 0x2E6F3F4 |  | `public void .ctor()` |

</details>

### public class `CraftingQueue` : yD  
`TypeDefIndex 2999`

| offset | field |
|---|---|
| 0x28 | `private QueueElement m_QueueElementTemplate;` |
| 0x30 | `private Transform m_QueueParent;` |
| 0x38 | `private int m_MaxElements;` |
| 0x40 | `private List<QueueElement> OIy;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AAB290 | 0x2E6F480 |  | `private void Awake()` |
| 0x3AAB364 | 0x2E6F554 |  | `private void Update()` |
| 0x3AABB48 | 0x2E6FC0C |  | `private bool UAo(yT e)` |
| 0x3AAB778 | 0x2E6F95C |  | `private void UAy(QueueItem e)` |
| 0x3AABF1C | 0x2E6FCCC |  | `public void CancelCrafting(QueueElement element)` |
| 0x3AABFA0 | 0x2E6FD50 |  | `public void .ctor()` |

</details>

### public sealed class `CraftWeaponInfo` : MonoBehaviour  
`TypeDefIndex 3006`

| offset | field |
|---|---|
| - | `public const string Prefix = "@wi:";` |
| - | `private const float PageWidth = 323;` |
| - | `private const float PageHeight = 111;` |
| - | `private const float TileHeight = 25;` |
| - | `private const float RowHeight = 24;` |
| - | `private const float Gap = 3;` |
| - | `private const float RepairShare = 0.1;` |
| - | `private static readonly Dictionary<string, CraftWeaponInfo.Stat> stats;` |
| - | `private static Object askedBy;` |
| - | `private RecipeInspector inspector;` |
| - | `private ItemData item;` |
| - | `private bool open;` |
| - | `private RectTransform content;` |
| - | `private RectTransform required;` |
| - | `private RectTransform panel;` |
| - | `private Button button;` |
| - | `private Text buttonText;` |
| - | `private Font bold;` |
| - | `private Font regular;` |
| - | `private Color gold;` |
| - | `private readonly List<CraftWeaponInfo.Cell> tiles;` |
| - | `private CraftWeaponInfo.Cell bottomRow;` |
| - | `private CraftWeaponInfo.Cell wallsRow;` |
| - | `private readonly List<Image> wallIcons;` |
| - | `private readonly List<Text> wallCounts;` |

<details><summary>methods (29)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E6FDE0 |  | `private static void .cctor()` |
| - | 0x2E70674 |  | `private static void Add(string s, string k, float d, float r, int m, float rl, int p, float rt, string a)` |
| - | 0x2E707A4 |  | `private static void Blast(string s, float centre, float edge, float radius, float timer, float speed)` |
| - | 0x2E70A20 |  | `public static bool Receive(string text)` |
| - | 0x2E73B04 |  | `public static void Select(RecipeInspector inspector, ItemData item)` |
| - | 0x2E73E48 |  | `private static string T(string key, string english)` |
| - | 0x2E73EB0 |  | `private static string N(float v)` |
| - | 0x2E7404C |  | `private static CraftWeaponInfo.Stat StatOf(ItemData data)` |
| - | 0x2E74168 |  | `private static bool IsAmmo(ItemData data)` |
| - | 0x2E73C44 |  | `private void Show(ItemData data)` |
| - | 0x2E750C0 |  | `private void SetOpen(bool value)` |
| - | 0x2E742F4 |  | `private bool Build()` |
| - | 0x2E75858 |  | `private CraftWeaponInfo.Cell MakeCell(float width, float height, float valueWidth)` |
| - | 0x2E75D9C |  | `private static void Fit(CraftWeaponInfo.Cell cell, bool icon, float valueWidth)` |
| - | 0x2E75294 |  | `private static RectTransform Rect(string name, Transform parent, Vector2 anchorMin, Vector2 anchorMax, Vector2 pivot, Vector2 position, Vector2 size)` |
| - | 0x2E757B0 |  | `private static void Place(RectTransform rt, Vector2 anchorMin, Vector2 anchorMax, Vector2 pivot, Vector2 position, Vector2 size)` |
| - | 0x2E754B4 |  | `private static Text Label(Transform parent, string text, Font font, int size, Color color, TextAnchor anchor)` |
| - | 0x2E75EAC |  | `private ItemData Find(string shortName)` |
| - | 0x2E70DD4 |  | `private void Render()` |
| - | 0x2E75FB8 |  | `private static string Damage(CraftWeaponInfo.Stat stat)` |
| - | 0x2E76378 |  | `public static List<KeyValuePair<string, string>> Lines(ItemData data, out bool unloadable)` |
| - | 0x2E77948 |  | `private static ItemData ItemOf(string shortName)` |
| - | 0x2E77A54 |  | `public static float DurabilityOf(ItemData data)` |
| - | 0x2E77AA8 |  | `public static string Kind(ItemData data)` |
| - | 0x2E76078 |  | `private void SetRow(CraftWeaponInfo.Cell cell, string label, string value, Sprite icon)` |
| - | 0x2E76200 |  | `private static float Durability(ItemData data)` |
| - | 0x2E77BB0 |  | `public void .ctor()` |
| - | 0x2E77CEC |  | `private void <Build>b__39_1()` |
| - | 0x2E77CFC |  | `private bool <Render>b__46_0(CraftWeaponInfo.Stat x)` |

</details>

### public class `CrosshairData`  
`TypeDefIndex 3007`

| offset | field |
|---|---|
| 0x10 | `private string m_ItemName;` |
| 0x18 | `private bool m_HideWhenAiming;` |
| 0x1C | `private Color m_NormalColor;` |
| 0x2C | `private Color m_OnEntityColor;` |
| 0x3C | `private yR m_Type;` |
| 0x40 | `private Image m_Image;` |
| 0x48 | `private Sprite m_Sprite;` |
| 0x50 | `private Vector2 m_Size;` |
| 0x58 | `private DynamicCrosshair m_Crosshair;` |

Properties: `public string Ceg { get; }`; `public bool Cep { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E77F80 |  | `public string get_Ceg()` |
| - | 0x2E77F88 |  | `public bool get_Cep()` |
| 0x3AB2F94 | 0x2E77F90 |  | `public static bool Uum(CrosshairData e)` |
| 0x3AB2FA0 | 0x2E77F9C |  | `public void Update(XA player)` |
| 0x3AB30E0 | 0x2E78184 |  | `public void UuR(bool e)` |
| 0x3AB3264 | 0x2E78364 |  | `public void .ctor()` |

</details>

### public class `CrosshairManager` : yD  
`TypeDefIndex 3015`

| offset | field |
|---|---|
| - | `private readonly CrosshairManager.HammerPieceHighlight hammerHighlight;` |
| - | `private const float OMh = 40;` |
| 0x28 | `private GameObject m_OpenMessage;` |
| 0x30 | `private MessageForPlayer m_GrabMessage;` |
| 0x38 | `private GameObject m_InviteMessage;` |
| 0x40 | `private GameObject[] m_KeyButtons;` |
| 0x48 | `private CrosshairData m_DefaultCrosshair;` |
| 0x50 | `private CrosshairData[] m_CustomCrosshairs;` |
| 0x58 | `private GameObject m_CriticalCrosshair;` |
| 0x60 | `private CrosshairManager.HitSet[] hitSets;` |
| 0x68 | `private RectTransform hitsRect;` |
| 0x70 | `private BlobButton hitBlobButton;` |
| 0x78 | `private CrosshairData OMB;` |
| 0x80 | `private float OMm;` |
| 0x88 | `public Uz lookAtHealth;` |
| 0x90 | `private float OMb;` |
| 0x94 | `private bool OMl;` |
| 0x98 | `private float OMx;` |
| 0x9C | `private int OMK;` |
| 0xA0 | `private Vector2 OMG;` |
| 0xA8 | `private float OMP;` |
| 0xB0 | `private CrosshairManager.HitSet OMD;` |
| 0xB8 | `private bool OMn;` |
| 0xB9 | `private bool OMV;` |
| 0xBA | `private HitData OMg;` |
| 0xBB | `private bool OMp;` |
| 0xC0 | `private CancellationTokenSource OMv;` |

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7836C |  | `private void UpdateHammerHighlight()` |
| - | 0x2E79200 |  | `private void OnDisable()` |
| 0x3AB32E0 | 0x2E79218 |  | `public void UuD()` |
| 0x3AB36CC | 0x2E7987C |  | `public void Uun(float e, float f)` |
| 0x3AB37B4 | 0x2E79988 |  | `private UniTaskVoid UuV(CancellationToken e)` |
| 0x3AB3870 | 0x2E79AB4 |  | `private void Update()` |
| 0x3AB3A20 | 0x2E79CA4 |  | `private void Uug(CrosshairManager.HitSet e)` |
| 0x3AB3A18 | 0x2E79EB4 |  | `private CrosshairManager.yb Uup(HitData e)` |
| 0x3AB3B18 | 0x2E7965C |  | `private void Uuv()` |
| 0x3AB35B8 | 0x2E796DC |  | `private void UuS()` |
| 0x3AB3C10 | 0x2E7ABFC |  | `private void UuI()` |
| 0x3AB3C14 | 0x2E7AC00 |  | `private void UuM()` |
| 0x3AB3B9C | 0x2E79EBC |  | `private void Uke()` |
| 0x3AB3C18 | 0x2E79FB8 |  | `private void Ukf()` |
| 0x3AB4720 | 0x2E7AC04 |  | `public void UkF(bool e)` |
| 0x3AB473C | 0x2E7AC20 |  | `private void OnDestroy()` |
| 0x3AB4858 | 0x2E7AEF8 |  | `public void .ctor()` |
| - | 0x2E7B03C |  | `private bool <Update>b__37_0(CrosshairManager.HitSet set)` |

</details>

### public class `CupboardGUI` : yD  
`TypeDefIndex 3016`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |
| 0x30 | `public CostItemUI[] costItems;` |
| 0x38 | `public Text baseProtected;` |
| 0x40 | `public Wp.Phrase protectedText;` |
| 0x48 | `public GameObject baseNotProtected;` |
| 0x50 | `public GameObject noOwnerTitle;` |
| 0x58 | `public GameObject controlPanel;` |
| 0x60 | `public GameObject subscriptionText;` |
| 0x68 | `public GameObject subscriptionIcon;` |
| 0x70 | `public Text authPlayersText;` |
| 0x78 | `private Cupboard tfw;` |
| 0x80 | `private float tfJ;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC3540 | 0x2E7B218 |  | `private void Start()` |
| 0x3AC3678 | 0x2E7B3F0 |  | `private void Update()` |
| 0x3AC3B9C | 0x2E7B7F0 |  | `private bool UrV(ItemHolder[] e)` |
| 0x3AC3D88 | 0x2E7BAA4 |  | `public void Urg(int e)` |
| 0x3AC36C0 | 0x2E7B48C |  | `private void Urp()` |
| 0x3AC3E70 | 0x2E7BBF4 |  | `public void ClearList()` |
| 0x3AC3F1C | 0x2E7BD08 |  | `private void Urv()` |
| 0x3AC3F90 | 0x2E7BDD8 |  | `private void OnDestroy()` |
| 0x3AC40AC | 0x2E7BEE8 |  | `public void .ctor()` |

</details>

### public class `DamageGUI` : yD  
`TypeDefIndex 3017`

| offset | field |
|---|---|
| 0x28 | `private ImageFader m_BloodScreenFader;` |
| 0x30 | `private RectTransform m_IndicatorRT;` |
| 0x38 | `private ImageFader m_IndicatorFader;` |
| 0x40 | `private int m_IndicatorDistance;` |
| 0x44 | `private Vector3 tec;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB5408 | 0x2E7BEF0 |  | `public void Ukk()` |
| 0x3AB54C0 | 0x2E7C064 |  | `private void Update()` |
| 0x3AB5A7C | 0x2E7C570 |  | `private void UkO()` |
| - | 0x2E7C688 |  | `public void ShowFatalDamage()` |
| 0x3AB5B48 | 0x2E7C6CC |  | `private void OnEnable()` |
| 0x3AB5B60 | 0x2E7C6E0 |  | `public void .ctor()` |

</details>

### public class `DurabilityBar`  
`TypeDefIndex 3018`

| offset | field |
|---|---|
| 0x18 | `private GameObject m_Background;` |
| 0x20 | `private Image m_Bar;` |
| 0x28 | `private Gradient m_ColorGradient;` |
| 0x30 | `private float m_Durability;` |
| - | `private bool <teV>k__BackingField;` |

Properties: `public bool teV { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7C6E8 |  | `public bool get_teV()` |
| - | 0x2E7C6F0 |  | `private void set_teV(bool value)` |
| 0x3ABFD3C | 0x2E7C6FC |  | `public void UtX(bool e)` |
| 0x3ABFDE0 | 0x2E7C810 |  | `public void UtT(float e)` |
| 0x3ABFE44 | 0x2E7C904 |  | `public void .ctor()` |

</details>

### public class `DynamicCrosshair` : MonoBehaviour  
`TypeDefIndex 3019`

| offset | field |
|---|---|
| 0x20 | `private float m_Distance;` |
| 0x28 | `private RectTransform crosshairRect;` |
| 0x30 | `private Image[] crosshairImages;` |

Properties: `public float CeI { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7C90C |  | `public float get_CeI()` |
| 0x3AB31FC | 0x2E78294 |  | `public void SetActive(bool active)` |
| 0x3AB30A4 | 0x2E780E8 |  | `public void Ukr(float e)` |
| 0x3AB5B78 | 0x2E7C914 |  | `public void .ctor()` |

</details>

### public class `FlamesIcon` : MonoBehaviour  
`TypeDefIndex 3020`

| offset | field |
|---|---|
| 0x20 | `private SmeltingStationGUI m_SmeltingStationGUI;` |
| 0x28 | `private Animator m_Animator;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ABB25C | 0x2E7C91C |  | `public void UOZ(bool e)` |
| 0x3ABB2DC | 0x2E7CA64 |  | `public void .ctor()` |

</details>

### public class `FuelTankGUI` : yD  
`TypeDefIndex 3021`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC581C | 0x2E7CA6C |  | `private void Start()` |
| 0x3AC58D0 | 0x2E7CB80 |  | `private bool UNr(ItemHolder[] e)` |
| 0x3AC5994 | 0x2E7CC88 |  | `public void .ctor()` |

</details>

### public class `GUIController` : Lc<GUIController>  
`TypeDefIndex 3022`

| offset | field |
|---|---|
| 0x20 | `public ItemContainer InventoryContainer;` |
| 0x28 | `public ItemContainer HotbarContainer;` |
| 0x30 | `public ItemContainer[] EquipmentContainers;` |
| 0x38 | `public Transform previewParent;` |
| 0x40 | `public RuntimeAnimatorController previewAnimator;` |
| 0x48 | `public ItemContainer LootContainer;` |
| 0x50 | `public AnvilGUI AnvilGUI;` |
| 0x58 | `public KeypadUI KeypadUI;` |
| 0x60 | `public PurchasesUI PurchasesUI;` |
| 0x68 | `public zd TechTreeUI;` |
| 0x70 | `public zf QuestUI;` |
| 0x78 | `public zF TeamUI;` |
| 0x80 | `public CupboardGUI CupboardUI;` |
| 0x88 | `public yS CharacterUI;` |
| 0x90 | `public RecyclerGUI RecyclerUI;` |
| 0x98 | `public We ShopUI;` |
| 0xA0 | `public EventShopUI EventShopUI;` |
| 0xA8 | `public ItemContainer[] Containers;` |
| 0xC0 | `private Canvas m_Canvas;` |
| 0xC8 | `private Camera m_GUICamera;` |
| 0xD0 | `private Font m_Font;` |
| 0xD8 | `private ReorderableRectTransformList m_SelectionBlockers;` |
| 0xE0 | `private AudioClip m_InventoryOpenClip;` |
| 0xE8 | `private AudioClip m_InventoryCloseClip;` |
| - | `private PlayerManager <tfC>k__BackingField;` |
| - | `private XA <tfZ>k__BackingField;` |

Properties: `public PlayerManager tfC { get; set; }`; `public XA tfZ { get; set; }`; `public Canvas Cfj { get; }`; `public Font Cfa { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7CC90 |  | `public PlayerManager get_tfC()` |
| - | 0x2E7CC98 |  | `private void set_tfC(PlayerManager value)` |
| - | 0x2E7CCA0 |  | `public XA get_tfZ()` |
| - | 0x2E7CCA8 |  | `private void set_tfZ(XA value)` |
| - | 0x2E7CCB0 |  | `public Canvas get_Cfj()` |
| 0x3AC14FC | 0x2E7CCB8 |  | `public Font get_Cfa()` |
| 0x3AC0AD0 | 0x2E7CCC0 |  | `public bool UrJ()` |
| 0x3AC1504 | 0x2E7CCC8 |  | `public void UrX()` |
| 0x3AC159C | 0x2E7CCCC |  | `public void UrT()` |
| 0x3AC15F8 | 0x2E7CCD0 |  | `private void Start()` |
| 0x3AC16B4 | 0x2E7CCD4 |  | `public void UrL(PlayerManager e, XA f)` |
| 0x3AC16E4 | 0x2E7D800 |  | `public void Uro()` |
| 0x3AC17D4 | 0x2E7D984 |  | `public void .ctor()` |

</details>

### public class `GunTrapGUI` : yD  
`TypeDefIndex 3023`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |
| 0x30 | `private GunTrap tfh;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC599C | 0x2E7D9CC |  | `private void Start()` |
| 0x3AC5AD4 | 0x2E7DAE0 |  | `private bool UNN(ItemHolder[] e)` |
| 0x3AC5C90 | 0x2E7DBE8 |  | `private void UNq()` |
| 0x3AC5D04 | 0x2E7DBEC |  | `private void OnDestroy()` |
| 0x3AC5E20 | 0x2E7DBF0 |  | `public void .ctor()` |

</details>

### public struct `HitData`  
`TypeDefIndex 3024`

| offset | field |
|---|---|
| 0x0 | `public bool IsCritical;` |

### public class `HoldableButton` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IDragHandler  
`TypeDefIndex 3025`

| offset | field |
|---|---|
| 0x28 | `private AnimationCurve delayCurve;` |
| 0x30 | `private bool tfm;` |
| 0x34 | `private int tfR;` |
| 0x38 | `private HoldTimer tfb;` |
| 0x40 | `private int tfl;` |
| - | `private Action tfB;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7DBF8 |  | `public void add_tfB(Action value)` |
| - | 0x2E7DC94 |  | `public void remove_tfB(Action value)` |
| 0x3AC5F60 | 0x2E7DD30 | 4 | `public void OnPointerDown(PointerEventData eventData)` |
| 0x3AC5FF4 | 0x2E7DDD0 | 5 | `public void OnPointerUp(PointerEventData eventData)` |
| 0x3AC602C | 0x2E7DE08 |  | `private void Update()` |
| 0x3AC5FD8 | 0x2E7DDB4 |  | `private void UNZ()` |
| 0x3AC60DC | 0x2E7DEBC | 6 | `public void OnDrag(PointerEventData eventData)` |
| 0x3AC60E0 | 0x2E7DEC0 |  | `public void UNj()` |
| 0x3AC60F8 | 0x2E7DED8 |  | `public void .ctor()` |

</details>

### internal struct `HoldTimer`  
`TypeDefIndex 3026`

| offset | field |
|---|---|
| 0x0 | `private float tfx;` |
| 0x4 | `private float tfK;` |

Properties: `public bool CfJ { get; }`; `public float CfX { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7E058 |  | `public bool get_CfJ()` |
| - | 0x2E7E068 |  | `public float get_CfX()` |
| 0x3AC5FD0 | 0x2E7E074 |  | `public void UNH(float e, float f = 0)` |
| 0x3AC60B0 | 0x2E7E07C |  | `public void Update(float deltaTime)` |

</details>

### public class `Hotbar` : yD  
`TypeDefIndex 3027`

| offset | field |
|---|---|
| 0x28 | `private bool m_EnableScrolling;` |
| 0x2C | `private float m_ScrollThreeshold;` |
| 0x30 | `private float m_SelectedSlotScale;` |
| 0x34 | `private Color m_FrameColor;` |
| 0x48 | `private OnScreenCustomButton[] m_AimButtons;` |
| 0x50 | `private GameObject m_ReloadButton;` |
| 0x58 | `private GameObject m_ViewButton;` |
| 0x60 | `private GameObject m_UpgradeButton;` |
| 0x68 | `private GameObject m_PickupButton;` |
| 0x70 | `private GameObject m_DemolishButton;` |
| 0x78 | `private ItemContainer m_HotbarContainer;` |
| 0x80 | `private List<Slot> teU;` |
| 0x88 | `private Slot teY;` |
| 0x90 | `private int teW;` |
| 0x94 | `private float teE;` |
| 0x98 | `private Image teA;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7E08C |  | `private void AlignSelectionFrame()` |
| - | 0x2E7E3C0 |  | `private void LateUpdate()` |
| 0x3AB5B88 | 0x2E7E3C4 |  | `private void Awake()` |
| 0x3AB5C90 | 0x2E7E578 |  | `public void ResetVisualSelection()` |
| - | 0x2E7E698 |  | `public void UkN()` |
| 0x3AB5F90 | 0x2E7F118 |  | `private bool Ukq()` |
| 0x3AB605C | 0x2E7F2C8 |  | `private void Uks(PointerEventData e, Slot f)` |
| 0x3AB66B8 | 0x2E7F770 |  | `private void UkC(Slot e)` |
| 0x3AB6774 | 0x2E7F92C |  | `private void Update()` |
| 0x3AB6160 | 0x2E7F458 |  | `public void UkZ(int e, bool f = false)` |
| 0x3AB67E4 | 0x2E7FA14 |  | `public bool Ukj()` |
| 0x3AB6958 | 0x2E7ED14 |  | `public void Uka()` |
| 0x3AB6CFC | 0x2E7FB0C |  | `public int UkQ()` |
| 0x3AB6D50 | 0x2E7FB60 |  | `public void .ctor()` |
| 0x3AB6D74 | 0x2E7FB68 |  | `private void UkH()` |

</details>

### public class `ImageFader`  
`TypeDefIndex 3030`

| offset | field |
|---|---|
| 0x18 | `private Image m_Image;` |
| 0x20 | `private float m_MinAlpha;` |
| 0x24 | `private float m_FadeInSpeed;` |
| 0x28 | `private float m_FadeOutSpeed;` |
| 0x2C | `private float m_FadeOutPause;` |
| 0x30 | `private Coroutine teF;` |
| 0x38 | `private MonoBehaviour ted;` |
| - | `private bool <tef>k__BackingField;` |

Properties: `public bool tef { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E7FB74 |  | `public bool get_tef()` |
| - | 0x2E7FB7C |  | `private void set_tef(bool value)` |
| 0x3AB4C5C | 0x2E7FB88 |  | `public void UkA(MonoBehaviour e, float f)` |
| 0x3AB4DE0 | 0x2E7FCBC |  | `private IEnumerator Uku(float e)` |
| 0x3AB4E84 | 0x2E7FD60 |  | `public void Reset()` |
| 0x3AB4F88 | 0x2E7FE58 |  | `public void .ctor()` |

</details>

### public class `InfinityItemContainer` : ItemContainer  
`TypeDefIndex 3031`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ABBBBC | 0x2E80220 | 5 | `public override bool UOJ(Item e)` |
| 0x3ABBC18 | 0x2E80230 | 4 | `public override void UOX(ItemHolder[] e)` |
| 0x3ABC238 | 0x2E80E44 |  | `public void .ctor()` |

</details>

### public class `ItemContainer` : yD  
`TypeDefIndex 3035`

| offset | field |
|---|---|
| - | `private bool recoveredSlotsDiscovered;` |
| - | `private readonly List<Slot> recoveredSpareSlots;` |
| 0x28 | `public XN<Slot> Slot_Refreshed;` |
| 0x60 | `public bool isLocked;` |
| 0x68 | `public List<Slot> Slots;` |
| 0x78 | `private string _Name;` |
| 0x80 | `private Window m_Window;` |
| 0x88 | `protected Slot m_SlotTemplate;` |
| 0x90 | `protected Transform m_SlotsParent;` |
| 0x98 | `private int m_PreviewSize;` |
| 0xA0 | `private ReorderableStringList m_RequiredCategories;` |
| 0xA8 | `private ReorderableStringList m_RequiredProperties;` |
| 0xB0 | `private ReorderableStringList m_RequiredItems;` |
| 0xB8 | `private ReorderableStringList m_SpecialItems;` |
| 0xC0 | `private List<Slot> teD;` |
| 0xC8 | `private bool ten;` |
| - | `private ItemHolder[] <teP>k__BackingField;` |
| - | `private Action<PointerEventData, Slot> tem;` |
| - | `private Action<PointerEventData, Slot> teR;` |
| - | `private Action<BaseEventData, Slot> teb;` |
| - | `private DragAction tel;` |
| - | `private DragAction teK;` |
| - | `private DragAction teG;` |

Properties: `public bool CfE { get; }`; `public string CfA { get; }`; `public ItemHolder[] teP { get; set; }`

<details><summary>methods (53)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E80F24 |  | `public bool get_CfE()` |
| - | 0x2E80FA8 |  | `public string get_CfA()` |
| - | 0x2E80FB0 |  | `public ItemHolder[] get_teP()` |
| - | 0x2E80FB8 |  | `private void set_teP(ItemHolder[] value)` |
| - | 0x2E80FC0 |  | `public void add_tem(Action<PointerEventData, Slot> value)` |
| - | 0x2E81070 |  | `public void remove_tem(Action<PointerEventData, Slot> value)` |
| - | 0x2E7E4C8 |  | `public void add_teR(Action<PointerEventData, Slot> value)` |
| - | 0x2E81120 |  | `public void remove_teR(Action<PointerEventData, Slot> value)` |
| - | 0x2E811D0 |  | `public void add_teb(Action<BaseEventData, Slot> value)` |
| - | 0x2E81280 |  | `public void remove_teb(Action<BaseEventData, Slot> value)` |
| - | 0x2E81330 |  | `public void add_tel(DragAction value)` |
| - | 0x2E813CC |  | `public void remove_tel(DragAction value)` |
| - | 0x2E81468 |  | `public void add_teK(DragAction value)` |
| - | 0x2E81504 |  | `public void remove_teK(DragAction value)` |
| - | 0x2E815A0 |  | `public void add_teG(DragAction value)` |
| - | 0x2E8163C |  | `public void remove_teG(DragAction value)` |
| 0x3ABB904 | 0x2E816D8 |  | `public void UOV(ItemHolder e)` |
| 0x3ABBFA4 | 0x2E80234 | 4 | `public virtual void UOX(ItemHolder[] e)` |
| 0x3ABCE08 | 0x2E7F1DC |  | `public bool UOg(Item e)` |
| 0x3ABCEA4 | 0x2E81798 |  | `public void UOp(Item e, int f)` |
| 0x3ABCEE0 | 0x2E8179C |  | `public bool UOv(ItemData e, int f, out int F)` |
| 0x3ABCF1C | 0x2E817A8 |  | `public bool UOS(ItemData e, int f)` |
| 0x3ABCF58 | 0x2E817B0 |  | `public bool UOI(string e, int f, out int F)` |
| 0x3ABD010 | 0x2E817BC |  | `public bool UOM(string e, int f)` |
| 0x3ABBBCC | 0x2E80228 | 5 | `public virtual bool UOJ(Item e)` |
| 0x3ABD0CC | 0x2E817C4 |  | `public bool Ute(ItemData e, int f, int F, out int d)` |
| 0x3ABD170 | 0x2E7F2C0 |  | `public bool Utf(Item e)` |
| 0x3ABD2C0 | 0x2E817D0 |  | `public bool UtF(string e, int f, bool F = false)` |
| 0x3ABD2C8 | 0x2E817D8 |  | `public void Utd(string e, int f, out int F)` |
| 0x3ABD2E0 | 0x2E817E0 |  | `public void Utc(string e, int f)` |
| 0x3ABD30C | 0x2E817E4 |  | `public void UtU(ItemContainer e)` |
| 0x3ABD444 | 0x2E817E8 |  | `public int UtY(int e)` |
| 0x3ABD53C | 0x2E817F0 |  | `public int UtW(string e)` |
| 0x3ABD640 | 0x2E818A0 |  | `public void UtE()` |
| 0x3ABD8FC | 0x2E818A4 |  | `public void UtA()` |
| 0x3ABD6B4 | 0x2E818A8 |  | `public void Utu()` |
| 0x3ABD7F4 | 0x2E818AC |  | `public void Utk()` |
| 0x3ABE4CC | 0x2E818B0 |  | `private void Awake()` |
| 0x3ABE598 | 0x2E818B4 |  | `private void UtO(PointerEventData e, Slot f)` |
| 0x3ABE6F4 | 0x2E818D0 |  | `private void Utt(PointerEventData e, Slot f)` |
| 0x3ABE710 | 0x2E818EC |  | `private void Utr(BaseEventData e, Slot f)` |
| 0x3ABE72C | 0x2E81908 |  | `private void UtN(PointerEventData e, Slot f)` |
| 0x3ABE74C | 0x2E81928 |  | `private void Utq(PointerEventData e, Slot f)` |
| 0x3ABE76C | 0x2E81948 |  | `private void Uts(PointerEventData e, Slot f)` |
| 0x3ABE78C | 0x2E81968 |  | `private void UtC(Slot e)` |
| 0x3ABE7E4 | 0x2E819C0 |  | `private void UtZ(Transform e, Slot f, int F, bool d)` |
| 0x3ABCB74 | 0x2E819C4 |  | `private void Utj(Transform e, Slot f)` |
| 0x3ABE900 | 0x2E819C8 |  | `private void Uta()` |
| 0x3ABEF54 | 0x2E819CC |  | `private void UtQ()` |
| 0x3ABE22C | 0x2E819D0 |  | `private void UtH(Transform e, Slot f)` |
| 0x3ABE350 | 0x2E819D4 |  | `private void Uti(Transform e, Slot f)` |
| 0x3ABFC68 | 0x2E819D8 |  | `private void OnDestroy()` |
| 0x3ABC23C | 0x2E80E48 |  | `public void .ctor()` |

</details>

### public static class `ItemInfoPanel`  
`TypeDefIndex 3045`

| offset | field |
|---|---|
| - | `public const string Prefix = "@ii:";` |
| - | `private static ItemInfoPanel.Packet packet;` |
| - | `private static Object askedBy;` |
| - | `private static Action Updated;` |

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E81AF8 |  | `public static void add_Updated(Action value)` |
| - | 0x2E81BB4 |  | `public static void remove_Updated(Action value)` |
| - | 0x2E81C70 |  | `public static bool Receive(string text)` |
| - | 0x2E81E40 |  | `public static void Request()` |
| - | 0x2E81F60 |  | `private static string T(string key, string english)` |
| - | 0x2E81FC8 |  | `private static string N(float v)` |
| - | 0x2E82168 |  | `private static string Signed(float v)` |
| - | 0x2E821E4 |  | `private static string Amount(float a, float b)` |
| - | 0x2E82264 |  | `private static string Sec(float v)` |
| - | 0x2E82308 |  | `private static ItemData Find(string shortName)` |
| - | 0x2E82414 |  | `private static string NameOf(string shortName)` |
| - | 0x2E824BC |  | `public static bool Unloadable(Item item)` |
| - | 0x2E82570 |  | `public static List<ItemInfoPanel.Row> Rows(Item item)` |
| - | 0x2E8421C |  | `private static void Farm(Action<string, string> add, string label, int perHit, int hits, int total)` |
| - | 0x2E844EC |  | `private static void Food(ItemInfoPanel.Consumable food, Action<string> header, Action<string, string> add)` |
| - | 0x2E84E0C |  | `private static void Station(string shortName, Action<string> header, Action<string, string> add)` |

</details>

### public class `ItemInspector` : yD  
`TypeDefIndex 3048`

| offset | field |
|---|---|
| 0x30 | `private Camera m_GUICamera;` |
| 0x38 | `private Window m_Window;` |
| 0x40 | `private Text m_ItemName;` |
| 0x48 | `private Text m_MainDescription;` |
| 0x50 | `private Image m_Icon;` |
| 0x58 | `private DurabilityBar m_DurabilityBar;` |
| 0x60 | `private Button m_DropButton;` |
| 0x68 | `private Button m_ConsumeButton;` |
| 0x70 | `private Button m_SplitButton;` |
| 0x78 | `private GameObject m_SplitPanel;` |
| 0x80 | `private Slider m_SplitSlider;` |
| 0x88 | `private Text m_SplitValue;` |
| 0x90 | `private YX projectileProtectionText;` |
| 0x98 | `private YX meleeProtectionText;` |
| 0xA0 | `private YX coldProtectionText;` |
| 0xA8 | `private YX radiationProtectionText;` |
| 0xB0 | `private SoundPlayer m_ItemDropAudio;` |
| 0xB8 | `private SoundPlayer m_DismantleAudio;` |
| 0xC0 | `private ItemContainer[] ter;` |
| 0xC8 | `private ItemContainer teN;` |
| 0xD0 | `private float teq;` |
| 0xD4 | `private int tes;` |
| - | `private Slot <tet>k__BackingField;` |

Properties: `public Slot tet { get; set; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E85A14 |  | `public Slot get_tet()` |
| - | 0x2E85A1C |  | `private void set_tet(Slot value)` |
| 0x3AB6D90 | 0x2E85A24 |  | `private void Awake()` |
| 0x3AB6EC8 | 0x2E8619C |  | `private void Start()` |
| 0x3AB6FCC | 0x2E862E4 |  | `private void Uko(BaseEventData e, Slot f)` |
| 0x3AB7290 | 0x2E86708 |  | `private void Uky(Item e)` |
| 0x3AB7AE4 | 0x2E870C4 |  | `private void Ukz(ItemHolder e)` |
| 0x3AB7C80 | 0x2E87258 |  | `private void Ukh()` |
| 0x3AB7E0C | 0x2E874DC |  | `private void UkB()` |
| 0x3AB7F00 | 0x2E875F8 |  | `private void Ukm()` |
| 0x3AB79CC | 0x2E86DEC |  | `private void UkR()` |
| 0x3AB7F7C | 0x2E876E0 |  | `public void RefreshSplitValue()` |
| 0x3AB7958 | 0x2E8669C |  | `private IEnumerator Ukb()` |
| 0x3AB80F4 | 0x2E87830 |  | `public void .ctor()` |
| 0x3AB80FC | 0x2E87838 |  | `private void Ukl(BaseEventData e, Slot f)` |
| - | 0x2E87858 |  | `private void <Awake>b__27_0(float value)` |

</details>

### public sealed class `ItemInspectorActions` : MonoBehaviour  
`TypeDefIndex 3050`

| offset | field |
|---|---|
| - | `private const float ButtonWidth = 100;` |
| - | `private const float ButtonHeight = 35;` |
| - | `private const float ButtonGap = 10;` |
| - | `private const float ConsumeLeft = 310;` |
| - | `private const float ConsumeBottom = 55;` |
| - | `private const float CardWidth = 270;` |
| - | `private const float CardGap = 6;` |
| - | `private const float Pad = 10;` |
| - | `private const float TitleHeight = 30;` |
| - | `private const float LineHeight = 20;` |
| - | `private const float HeaderHeight = 20;` |
| - | `private const float LineGap = 2;` |
| - | `private const float CardMaxHeight = 380;` |
| - | `private static readonly Color Gold;` |
| - | `private static readonly Color Label;` |
| - | `private static readonly Color Light;` |
| - | `private Button info;` |
| - | `private Button unload;` |
| - | `private GameObject consume;` |
| - | `private GameObject splitPanel;` |
| - | `private int layoutKey;` |
| - | `private Text infoLabel;` |
| - | `private Text unloadLabel;` |
| - | `private Text title;` |
| - | `private RectTransform window;` |
| - | `private RectTransform card;` |
| - | `private RectTransform list;` |
| - | `private Transform content;` |
| - | `private ScrollRect scroll;` |
| - | `private Font bold;` |
| - | `private Font regular;` |
| - | `private bool open;` |
| - | `private Color labelColor;` |
| - | `private Item item;` |
| - | `private Slot slot;` |
| - | `private float unloadedAt;` |
| - | `private readonly List<ItemInspectorActions.Line> lines;` |

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E85C40 |  | `public static ItemInspectorActions Attach(ItemInspector inspector, Transform window, Button template, Button style, GameObject splitting, Text description)` |
| - | 0x2E87C0C |  | `private Button Clone(Button template, Button style, Transform parent, string name, float left, float bottom, float width, ref Text label)` |
| - | 0x2E880A0 |  | `private void BuildCard()` |
| - | 0x2E889F8 |  | `private static RectTransform Rect(string name, Transform parent)` |
| - | 0x2E88B64 |  | `private static Text Text(Transform parent, Font font, int size, Color color, TextAnchor anchor)` |
| - | 0x2E88E74 |  | `private ItemInspectorActions.Line MakeLine()` |
| - | 0x2E89260 |  | `private void Fill(List<ItemInfoPanel.Row> rows)` |
| - | 0x2E89770 |  | `private void Place()` |
| - | 0x2E8999C |  | `private void LateUpdate()` |
| - | 0x2E899A0 |  | `private void Layout()` |
| - | 0x2E89C1C |  | `private void OnDestroy()` |
| - | 0x2E88804 |  | `private void Labels()` |
| - | 0x2E86F88 |  | `public static void Refresh(ItemInspector inspector, Item item, Slot slot)` |
| - | 0x2E89C98 |  | `private void Redraw()` |
| - | 0x2E89E28 |  | `private void ToggleInfo()` |
| - | 0x2E89ED0 |  | `private void Unload()` |
| - | 0x2E8A03C |  | `public void .ctor()` |
| - | 0x2E8A0D4 |  | `private static void .cctor()` |

</details>

### public class `KeypadUI` : yD  
`TypeDefIndex 3051`

| offset | field |
|---|---|
| 0x28 | `private Text codeText;` |
| 0x30 | `private GameObject keys;` |
| 0x38 | `private GameObject loading;` |
| 0x40 | `private Window window;` |
| 0x48 | `private string tfG;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC6100 | 0x2E8A148 |  | `public void EnterNumber(int i)` |
| 0x3AC6214 | 0x2E8A264 |  | `public void UNi()` |
| 0x3AC626C | 0x2E8A39C |  | `public void ClearCode()` |
| 0x3AC62FC | 0x2E8A46C |  | `public void Show()` |
| 0x3AC6328 | 0x2E8A568 |  | `public void Hide()` |
| 0x3AC6378 | 0x2E8A65C |  | `public void .ctor()` |

</details>

### public class `LogTemplate` : MessageDisplayer  
`TypeDefIndex 3052`

| offset | field |
|---|---|
| 0x40 | `private CanvasGroup tfP;` |
| 0x48 | `private float tfD;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC1974 | 0x2E8A664 |  | `internal void UNw(string e, Color f, int F = 16)` |
| 0x3AC63E8 | 0x2E8A668 |  | `private void Update()` |
| 0x3AC6430 | 0x2E8A66C |  | `private void UNJ()` |
| 0x3AC6578 | 0x2E8A670 |  | `public void .ctor()` |

</details>

### public class `LootContainerOpener` : MonoBehaviour  
`TypeDefIndex 3053`

| offset | field |
|---|---|
| 0x20 | `private ItemContainer m_ItemContainer;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB87CC | 0x2E8A6BC |  | `private void Start()` |
| 0x3AB8880 | 0x2E8A7D0 |  | `private bool Ukx(ItemHolder[] e)` |
| 0x3AB8944 | 0x2E8A8D8 |  | `public void .ctor()` |

</details>

### public class `LuckyWheelGUI` : yD  
`TypeDefIndex 3054`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |
| 0x30 | `private ItemContainer m_Winning;` |
| 0x38 | `private Text m_RemainingTime;` |
| 0x40 | `private Image[] m_SlotsBackground;` |
| 0x48 | `private Color[] m_SlotColors;` |
| 0x50 | `private LuckyWheelTerminal tfn;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC657C | 0x2E8A8E0 |  | `private void Start()` |
| 0x3AC66B4 | 0x2E8AA64 |  | `public void Update()` |
| 0x3AC696C | 0x2E8AD0C |  | `private bool UNX(ItemHolder[] e)` |
| 0x3AC6804 | 0x2E8AB9C |  | `public void UNT(bool e, int f = -1)` |
| 0x3AC6B7C | 0x2E8B084 |  | `private void UNL()` |
| 0x3AC6BF0 | 0x2E8B0F8 |  | `private void OnDestroy()` |
| 0x3AC6D0C | 0x2E8B214 |  | `public void .ctor()` |

</details>

### public class `MapManager` : yD  
`TypeDefIndex 3055`

| offset | field |
|---|---|
| 0x28 | `private MapView mapView;` |
| 0x30 | `private GameObject mapCanvasObject;` |
| 0x38 | `private Button closeButton;` |
| 0x40 | `private StaticInterestMarkers staticInterestMarkers;` |
| 0x48 | `private PauseManager pauseManager;` |
| 0x50 | `private bool tfo;` |
| - | `private bool <tfy>k__BackingField;` |

Properties: `public bool tfy { get; set; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E8B21C |  | `public bool get_tfy()` |
| - | 0x2E8B224 |  | `private void set_tfy(bool value)` |
| 0x3AC4CB4 | 0x2E8B230 |  | `private void Awake()` |
| 0x3AC4CD0 | 0x2E8B34C |  | `private void OnEnable()` |
| 0x3AC4DC4 | 0x2E8B4E4 |  | `private void OnDisable()` |
| 0x3AC4DE8 | 0x2E8B5BC |  | `public void UNE(bool[] e, Vector3[] f)` |
| 0x3AC4E04 | 0x2E8B658 |  | `public void ShowMap(bool isOpenedFromPause)` |
| 0x3AC54C4 | 0x2E8B750 |  | `public void UNA()` |
| 0x3AC54F0 | 0x2E8B7D8 |  | `private void UNu()` |
| - | 0x2E8B870 |  | `internal void BindPause(PauseManager owner)` |
| - | 0x2E8B7DC |  | `public void CloseMap()` |
| 0x3AC5524 | 0x2E8B878 |  | `public void .ctor()` |

</details>

### public class `MessageDisplayer` : Lc<MessageDisplayer>  
`TypeDefIndex 3056`

| offset | field |
|---|---|
| 0x20 | `private GameObject m_LogTemplate;` |
| 0x28 | `private Color m_BaseMessageColor;` |
| 0x38 | `protected float m_FadeDelay;` |
| 0x3C | `protected float m_FadeSpeed;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC181C | 0x2E8B880 |  | `public void Ury(string e, Color f, int F = 16)` |
| 0x3AC1B1C | 0x2E8A674 |  | `public void .ctor()` |

</details>

### public class `MessageForPlayer`  
`TypeDefIndex 3057`

| offset | field |
|---|---|
| 0x10 | `private GameObject m_Root;` |
| 0x18 | `private Text m_Text;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB3294 | 0x2E8B884 |  | `public void Uub(bool e)` |
| 0x3AB32B4 | 0x2E8B918 |  | `public void Uul(string e)` |
| 0x3AB32D8 | 0x2E8B9B4 |  | `public void .ctor()` |

</details>

### public class `OrderedSkin`  
`TypeDefIndex 3058`

| offset | field |
|---|---|
| 0x10 | `public int skinId;` |
| 0x14 | `public bool selected;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB0230 | 0x2E8B9BC |  | `public void .ctor()` |

</details>

### public class `PlayerLootGUI` : yD  
`TypeDefIndex 3059`

| offset | field |
|---|---|
| 0x28 | `private ItemContainer m_LootContainer;` |
| 0x30 | `public Text backpackOwner;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC6D14 | 0x2E8B9C4 |  | `private void Start()` |
| 0x3AC6DC8 | 0x2E8BAD8 |  | `private bool UNo(ItemHolder[] e)` |
| 0x3AC6F88 | 0x2E8BD54 |  | `public void .ctor()` |

</details>

### public class `PlayerStatsGUI` : yD  
`TypeDefIndex 3060`

| offset | field |
|---|---|
| 0x28 | `private YX projectileProtectionText;` |
| 0x30 | `private YX meleeProtectionText;` |
| 0x38 | `private YX radiationProtectionText;` |
| 0x40 | `private YX coldProtectionText;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB894C | 0x2E8BD5C |  | `public void UkK()` |
| 0x3AB89FC | 0x2E8BEEC |  | `public void UkG()` |
| 0x3AB8DCC | 0x2E8C3CC |  | `public void .ctor()` |

</details>

### public class `PlayerVitalsGUI` : yD  
`TypeDefIndex 3061`

| offset | field |
|---|---|
| 0x28 | `private Image m_ExpBar;` |
| 0x30 | `private Text m_LevelText;` |
| 0x38 | `private Image m_HealthBar;` |
| 0x40 | `private Image healthRegenBar;` |
| 0x48 | `private Text[] m_HealthText;` |
| 0x50 | `private Image m_ThirstBar;` |
| 0x58 | `private Text[] m_ThirstText;` |
| 0x60 | `private Image m_HungerBar;` |
| 0x68 | `private Text[] m_HungerText;` |
| 0x70 | `private int teC;` |
| 0x74 | `private int teZ;` |
| 0x78 | `private int tej;` |
| - | `private bool bound;` |
| - | `private bool regenShown;` |
| - | `private XA events;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E8C3D4 |  | `private void Update()` |
| 0x3AB8DDC | 0x2E8C480 |  | `public void UkP()` |
| 0x3AB9094 | 0x2E8CAF0 |  | `private void UkD()` |
| 0x3AB9148 | 0x2E8CBDC |  | `private void Ukn()` |
| 0x3AB91A8 | 0x2E8C9A8 |  | `private void UkV()` |
| 0x3AB96F8 | 0x2E8CD60 |  | `private void Ukg()` |
| 0x3AB95D4 | 0x2E8CCBC |  | `private void Ukp()` |
| - | 0x2E8CE04 |  | `private static void WriteStat(Text[] labels, Image bar, float value)` |
| 0x3AB981C | 0x2E8D028 |  | `public void .ctor()` |

</details>

### public class `PurchaseAmountView` : MonoBehaviour  
`TypeDefIndex 3062`

| offset | field |
|---|---|
| - | `private const int tfV = 1000;` |
| 0x28 | `private HoldableButton decrementButton;` |
| 0x30 | `private HoldableButton incrementButton;` |
| 0x38 | `private InputField amountText;` |
| 0x40 | `private int tfp;` |
| 0x44 | `private int tfv;` |
| - | `private Action<int> tfg;` |

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E8D030 |  | `public void add_tfg(Action<int> value)` |
| - | 0x2E8D0E0 |  | `public void remove_tfg(Action<int> value)` |
| 0x3AC70F0 | 0x2E8D190 |  | `private void OnEnable()` |
| 0x3AC72C4 | 0x2E8D36C |  | `private void OnDisable()` |
| 0x3AC7290 | 0x2E8D338 |  | `public void UNh()` |
| 0x3AC73C4 | 0x2E8D474 |  | `private void UNB()` |
| 0x3AC7454 | 0x2E8D504 |  | `private void UNm()` |
| 0x3AC73C8 | 0x2E8D478 |  | `private void UNR()` |
| 0x3AC7458 | 0x2E8D508 |  | `private void UNb()` |
| 0x3AC7510 | 0x2E8D5C8 |  | `private void UNl(string e)` |
| 0x3AC75E8 | 0x2E8D690 |  | `private void UNx(string e)` |
| 0x3AC7514 | 0x2E8D5CC |  | `private void UNK(string e)` |
| 0x3AC74E4 | 0x2E8D59C |  | `private void UNG()` |
| 0x3AC7628 | 0x2E8D6D0 |  | `public void .ctor()` |

</details>

### public class `PurchasesList` : MonoBehaviour  
`TypeDefIndex 3063`

| offset | field |
|---|---|
| 0x20 | `public Xr RecipesGenerated;` |
| 0x28 | `private PurchasesUI m_PurchasesManager;` |
| 0x30 | `private PurchasesMenu m_PurchasesMenu;` |
| 0x38 | `private RectTransform m_ListTransform;` |
| 0x40 | `private RectTransform m_BundleTransform;` |
| 0x48 | `private RectTransform m_scrollViewRect;` |
| 0x50 | `private PurchaseSlot m_PurchaseTemplate;` |
| 0x58 | `private List<yP> teL;` |
| 0x60 | `private bool teo;` |
| 0x68 | `private Zx tey;` |

Properties: `public List<yP> CfU { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E8D6D8 |  | `public List<yP> get_CfU()` |
| 0x3ABA3E8 | 0x2E8D6E0 |  | `private void UOr(Zx e)` |
| 0x3ABA3F0 | 0x2E8D6E4 |  | `private void Awake()` |
| 0x3ABA4EC | 0x2E8D874 |  | `private void Start()` |
| 0x3ABA51C | 0x2E8E1E4 |  | `private void OnDestroy()` |
| 0x3ABA5C0 | 0x2E8E2CC |  | `private void UON()` |
| 0x3ABA5F0 | 0x2E8E2D0 |  | `private void UOq()` |
| 0x3ABA7AC | 0x2E8DA14 |  | `public void UOs()` |
| 0x3ABAD58 | 0x2E8F258 |  | `public void .ctor()` |
| - | 0x2E8E958 |  | `private void CreateBundleRows()` |

</details>

### public class `PurchaseSlot` : MonoBehaviour  
`TypeDefIndex 3064`

| offset | field |
|---|---|
| 0x28 | `private Text m_PurchaseName;` |
| 0x30 | `private Text m_PurchaseStack;` |
| 0x38 | `private Image m_IconHolder;` |
| 0x40 | `private Text m_PriceHolder;` |
| 0x48 | `public string m_ItemName;` |
| 0x50 | `public int m_ItemPrice;` |
| 0x54 | `public int m_ItemAmount;` |
| 0x58 | `private NY teJ;` |
| - | `private ItemData <tew>k__BackingField;` |

Properties: `public ItemData tew { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E8F260 |  | `public ItemData get_tew()` |
| - | 0x2E8F268 |  | `private void set_tew(ItemData value)` |
| 0x3AB9CC8 | 0x2E8E6BC |  | `public void UOW(NY e, ItemData f)` |
| 0x3AB9ED4 | 0x2E8F270 |  | `public void UOE(NY e, ItemData f, string F)` |
| 0x3ABA194 | 0x2E8F344 |  | `public void Select()` |
| 0x3ABA238 | 0x2E8F3F0 |  | `public void .ctor()` |

</details>

### public class `PurchasesMenu` : MonoBehaviour  
`TypeDefIndex 3065`

| offset | field |
|---|---|
| 0x20 | `public Xq<CraftingCategory> SelectedCategory;` |
| 0x28 | `private CraftingCategory m_FirstSelected;` |
| 0x30 | `private Text m_CategoryName;` |
| 0x38 | `private CraftingCategory[] tez;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ABAE18 | 0x2E8F3F8 |  | `private void Awake()` |
| 0x3ABAFC4 | 0x2E8F584 |  | `private void Start()` |
| 0x3ABB068 | 0x2E8F5FC |  | `private void UOC(CraftingCategory e)` |
| 0x3ABB1D0 | 0x2E8F7D8 |  | `public void .ctor()` |

</details>

### public class `PurchasesUI` : yD, qD, NY  
`TypeDefIndex 3066`

| offset | field |
|---|---|
| 0x28 | `private float tfS;` |
| 0x30 | `private Canvas purchaseLoader;` |
| 0x38 | `private Window window;` |
| 0x40 | `private PurchasesList m_PurchasesList;` |
| 0x48 | `private PurchasesMenu m_PurchasesMenu;` |
| 0x50 | `private BuyWindow m_BuyWindow;` |
| 0x58 | `private PurchaseConfirmationPopup confirmationPopup;` |
| 0x60 | `private Lz playerSave;` |
| 0x68 | `public Text balance;` |
| 0x70 | `private GameObject craftingButton;` |
| 0x78 | `private GameObject inventoryButton;` |
| 0x80 | `public MouseLook mouseLook;` |
| 0x88 | `private Button closeButton;` |
| 0x90 | `private Button buyMoreCoinsButton;` |
| 0x98 | `private Button subscribeButton;` |
| 0xA0 | `private Uf tfI;` |
| 0xA8 | `private sG tfM;` |
| 0xB0 | `private Cs tFe;` |
| 0xB8 | `private Zl tFf;` |
| - | `private bool primeWired;` |
| - | `private bool confirmationWired;` |

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC7630 | 0x2E8F864 |  | `private void UNP(Uf e, sG f, Cs F, Zl d)` |
| 0x3AC7744 | 0x2E8F8C4 | 5 | `public void SelectItem(PurchaseSlot slot)` |
| 0x3AC7764 | 0x2E8F9F8 | 6 | `public void BuyItem(PurchaseSlot slot, int times)` |
| 0x3AC7864 | 0x2E8FC98 | 4 | `public void dHp(BundleSlot e)` |
| 0x3AC791C | 0x2E8FD4C |  | `public void Open()` |
| 0x3AC7C14 | 0x2E905A4 |  | `public void Close()` |
| 0x3AC7DD8 | 0x2E90948 |  | `public void HideCounter()` |
| 0x3AC7E7C | 0x2E909CC |  | `private void Update()` |
| 0x3AC7F60 | 0x2E90B50 |  | `private void OnEnable()` |
| 0x3AC8078 | 0x2E90D54 |  | `private void OnDisable()` |
| 0x3AC7840 | 0x2E8FC08 |  | `private void ShowCoinsPopup()` |
| 0x3AC814C | 0x2E90F58 |  | `private void UND(int e)` |
| 0x3AC8194 | 0x2E90FF8 |  | `public void .ctor()` |
| 0x3AC819C | 0x2E91000 |  | `private void UNn()` |
| - | 0x2E9025C |  | `private void EnsureStore()` |
| - | 0x2E91004 |  | `private void BuyBundle(BundleSlot slot)` |

</details>

### public class `QueueElement` : MonoBehaviour  
`TypeDefIndex 3067`

| offset | field |
|---|---|
| 0x20 | `public XN<QueueElement> Cancel;` |
| 0x28 | `public Xr Complete;` |
| 0x30 | `private Image m_Icon;` |
| 0x38 | `private Text m_RemainedTime;` |
| 0x40 | `private GameObject m_AmountLabel;` |
| 0x48 | `private Text m_Amount;` |
| 0x50 | `private yT OIm;` |
| 0x58 | `private ItemData OIR;` |
| 0x60 | `private bool OIb;` |
| 0x68 | `private CraftingQueue OIl;` |

Properties: `public ItemData Cen { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AAC030 | 0x2E911E8 |  | `public ItemData get_Cen()` |
| 0x3AABC10 | 0x2E911F0 |  | `public void UAh(yT e, CraftingQueue f)` |
| 0x3AAC038 | 0x2E91478 |  | `public void CancelCrafting()` |
| 0x3AABA20 | 0x2E91500 |  | `public void UAB(int e, int f)` |
| 0x3AAC0BC | 0x2E91600 |  | `public void .ctor()` |

</details>

### public class `RecipeInspector` : yD  
`TypeDefIndex 3074`

| offset | field |
|---|---|
| - | `private const string OIp = "removed";` |
| - | `private const string OIv = "skin";` |
| 0x30 | `private CraftingList m_CraftingList;` |
| 0x38 | `private int m_MaxCraftAmount;` |
| 0x40 | `private Text m_ItemName;` |
| 0x48 | `private Text m_Description;` |
| 0x50 | `private Image m_Icon;` |
| 0x58 | `private RequiredItemRow[] m_RequiredItemsTable;` |
| 0x60 | `private Text m_TotalTime;` |
| 0x68 | `private Image m_TotalTimeImage;` |
| 0x70 | `private GameObject subscriptionIcon;` |
| 0x78 | `private InputField m_DesiredAmount;` |
| 0x80 | `private Animator m_Animator;` |
| 0x88 | `private Button m_CraftButton;` |
| 0x90 | `private Transform skinsParent;` |
| 0x98 | `private SkinItem skinEntry;` |
| 0xA0 | `private string vehicleLimitWarning;` |
| 0xA8 | `private PurchaseAmountView purchaseAmountView;` |
| 0xB0 | `private ItemData OII;` |
| 0xB8 | `private bool OIM;` |
| 0xBC | `private int OMe;` |
| 0xC0 | `private int OMf;` |
| 0xC8 | `private List<SkinItem> OMF;` |
| 0xD0 | `private sq OMd;` |
| 0xD8 | `private cM OMc;` |
| 0xE0 | `private Uf OMU;` |
| 0xE8 | `private ItemDatabase OMY;` |
| - | `private RecipeSlot <OIS>k__BackingField;` |
| - | `private RecipeSlot <OMW>k__BackingField;` |

Properties: `public RecipeSlot OIS { get; set; }`; `internal RequiredItemRow[] InfoRows { get; }`; `internal Text InfoName { get; }`; `internal Text InfoDescription { get; }`; `public RecipeSlot OMW { get; set; }`

<details><summary>methods (29)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E916C0 |  | `public RecipeSlot get_OIS()` |
| - | 0x2E916C8 |  | `private void set_OIS(RecipeSlot value)` |
| - | 0x2E916D0 |  | `internal RequiredItemRow[] get_InfoRows()` |
| - | 0x2E916D8 |  | `internal Text get_InfoName()` |
| - | 0x2E916E0 |  | `internal Text get_InfoDescription()` |
| - | 0x2E916E8 |  | `public RecipeSlot get_OMW()` |
| - | 0x2E916F0 |  | `private void set_OMW(RecipeSlot value)` |
| 0x3AAC19C | 0x2E916F8 |  | `public void UAg(sq e, cM f, Uf F, ItemDatabase d)` |
| 0x3AAC200 | 0x2E91758 |  | `private void OnEnable()` |
| 0x3AAC290 | 0x2E917E4 |  | `private void OnDisable()` |
| 0x3AAC320 | 0x2E91870 |  | `public void Try_StartCrafting()` |
| 0x3AACF88 | 0x2E91F58 |  | `public void SetDesiredAmount(string s)` |
| 0x3AAD010 | 0x2E91FC0 |  | `public void TryIncreaseAmount()` |
| 0x3AAD098 | 0x2E92028 |  | `public void TryDecreaseAmount()` |
| 0x3AAD120 | 0x2E92090 |  | `private void Awake()` |
| 0x3AAD290 | 0x2E921D0 |  | `private void UAp(ItemHolder e)` |
| 0x3AAD310 | 0x2E92250 |  | `private void UAv()` |
| 0x3AAD78C | 0x2E926B8 |  | `public void UAS(ItemData e)` |
| 0x3AADEDC | 0x2E92D80 |  | `private void UAI()` |
| 0x3AAEA24 | 0x2E93554 |  | `public void UAM(int e)` |
| 0x3AAEC10 | 0x2E9372C |  | `public void Uue(RecipeSlot e, bool f)` |
| 0x3AAC9FC | 0x2E91A24 |  | `private void Uuf(ItemData e, bool f = true)` |
| 0x3AAF07C | 0x2E938D4 |  | `public void UuF()` |
| 0x3AAF0F4 | 0x2E93998 |  | `private void Uud(int e)` |
| 0x3AAF120 | 0x2E939C4 |  | `public void Uuc(ItemData e, int f, SkinItem F)` |
| 0x3AAF4B4 | 0x2E93CE0 |  | `private void UuU(bool e, int f, SkinItem F)` |
| 0x3AAFB74 | 0x2E93EA0 |  | `public void .ctor()` |
| 0x3AAFC04 | 0x2E93F30 |  | `private bool UuY(SelectedSkin e)` |
| - | 0x2E93F58 |  | `private bool <UAI>b__55_0(SelectedSkin s)` |

</details>

### public class `RecipeSlot` : MonoBehaviour  
`TypeDefIndex 3075`

| offset | field |
|---|---|
| 0x30 | `private Text m_RecipeName;` |
| 0x38 | `private Image m_Icon;` |
| 0x40 | `private GameObject m_Locked;` |
| 0x48 | `private bool OMu;` |
| 0x50 | `private RecipeInspector OMk;` |
| - | `private ItemData <OME>k__BackingField;` |
| - | `private bool <OMA>k__BackingField;` |

Properties: `public ItemData OME { get; set; }`; `public bool OMA { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E94130 |  | `public ItemData get_OME()` |
| - | 0x2E94138 |  | `private void set_OME(ItemData value)` |
| - | 0x2E94140 |  | `public bool get_OMA()` |
| - | 0x2E94148 |  | `private void set_OMA(bool value)` |
| 0x3AAA8BC | 0x2E94154 |  | `public void Uuk(ItemData e)` |
| 0x3AAAB28 | 0x2E941DC |  | `public void UuO(bool e)` |
| 0x3AAAD00 | 0x2E94214 |  | `public void Uut()` |
| 0x3AB009C | 0x2E94220 |  | `public void Select()` |
| 0x3AB00BC | 0x2E94244 |  | `public void Uur(RecipeInspector e)` |
| 0x3AB00C4 | 0x2E9424C |  | `public void .ctor()` |

</details>

### public class `RequiredItemRow` : MonoBehaviour  
`TypeDefIndex 3076`

| offset | field |
|---|---|
| 0x20 | `private Color m_HaveEnoughColor;` |
| 0x30 | `private Color m_DontHaveEnoughColor;` |
| 0x40 | `private Text m_Amount;` |
| 0x48 | `private Text m_Type;` |
| 0x50 | `private Text m_Total;` |
| 0x58 | `private Text m_Have;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AAED84 | 0x2E94254 |  | `public void UuN(int e, string f, int F, int d)` |
| 0x3AB00CC | 0x2E94484 |  | `public void .ctor()` |

</details>

### public class `ScreenFader` : yD  
`TypeDefIndex 3078`

| offset | field |
|---|---|
| 0x28 | `private Image m_Image;` |
| 0x30 | `private float m_FadeSpeed;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB9824 | 0x2E944AC |  | `public void UOe()` |
| 0x3AB9914 | 0x2E944B0 |  | `private void UOf()` |
| 0x3AB99C0 | 0x2E944B4 |  | `private void UOF()` |
| 0x3AB9944 | 0x2E944B8 |  | `private IEnumerator UOd(float e)` |
| 0x3AB9A18 | 0x2E944C0 |  | `private Color UOc(Color e, float f, float F)` |
| 0x3AB9A3C | 0x2E944D4 |  | `public void .ctor()` |

</details>

### public class `SelectedSkin`  
`TypeDefIndex 3079`

| offset | field |
|---|---|
| 0x10 | `public string itemShortName;` |
| 0x18 | `public List<OrderedSkin> orderedSkin;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB0238 | 0x2E94504 |  | `public void .ctor()` |

</details>

### public class `SelectedSkins`  
`TypeDefIndex 3080`

| offset | field |
|---|---|
| 0x10 | `public List<SelectedSkin> selectedSkins;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AB01A0 | 0x2E9450C |  | `public void .ctor()` |

</details>

### public class `Slot` : Selectable, IBeginDragHandler, IEventSystemHandler, IDragHandler, IEndDragHandler  
`TypeDefIndex 3086`

| offset | field |
|---|---|
| - | `private bool <WasDragged>k__BackingField;` |
| 0x100 | `public XN<Slot> Refreshed;` |
| 0x148 | `public ItemContainer Parent;` |
| 0x150 | `private Image m_ItemIcon;` |
| 0x158 | `private Image m_BackgroundIcon;` |
| 0x160 | `private Text m_StackDisplayer;` |
| 0x168 | `private Text delayDisplayer;` |
| 0x170 | `private Image delayFillImage;` |
| 0x178 | `private DurabilityBar m_DurabilityBar;` |
| 0x180 | `private ReorderableStringList m_RequiredCategories;` |
| 0x188 | `private ReorderableStringList m_RequiredProperties;` |
| 0x190 | `private ReorderableStringList m_RequiredItems;` |
| 0x198 | `private ReorderableStringList m_SpecialItems;` |
| 0x1A0 | `private GameObject m_Locked;` |
| 0x1A8 | `private bool tfr;` |
| 0x1B0 | `private Coroutine tfN;` |
| 0x1B8 | `private QC tfq;` |
| 0x1C0 | `private bool tfs;` |
| - | `private ItemHolder <tft>k__BackingField;` |
| - | `private Slot.BaseAction tfY;` |
| - | `private Slot.BaseAction tfW;` |
| - | `private Slot.PointerAction tfE;` |
| - | `private Slot.PointerAction tfA;` |
| - | `private Slot.PointerAction tfu;` |
| - | `private Slot.PointerAction tfk;` |
| - | `private Slot.PointerAction tfO;` |
| - | `private bool dragHidden;` |
| - | `private Item dragHiddenItem;` |
| - | `private float dragHiddenUntil;` |

Properties: `public bool WasDragged { get; set; }`; `public ItemHolder tft { get; set; }`; `public bool Cfr { get; }`; `public Item CfN { get; }`; `public ReorderableStringList Cfq { get; set; }`; `public ReorderableStringList Cfs { get; set; }`; `public ReorderableStringList CfC { get; set; }`; `public ReorderableStringList CfZ { get; set; }`

<details><summary>methods (50)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E94514 |  | `public bool get_WasDragged()` |
| - | 0x2E9451C |  | `private void set_WasDragged(bool value)` |
| - | 0x2E94528 |  | `public void SetRecoveredAmmoBackground(string shortName)` |
| - | 0x2E947EC |  | `public ItemHolder get_tft()` |
| - | 0x2E947F4 |  | `private void set_tft(ItemHolder value)` |
| - | 0x2E94804 |  | `public bool get_Cfr()` |
| - | 0x2E947D4 |  | `public Item get_CfN()` |
| - | 0x2E9482C |  | `public ReorderableStringList get_Cfq()` |
| - | 0x2E94834 |  | `public void set_Cfq(ReorderableStringList value)` |
| - | 0x2E94844 |  | `public ReorderableStringList get_Cfs()` |
| - | 0x2E9484C |  | `public void set_Cfs(ReorderableStringList value)` |
| - | 0x2E9485C |  | `public ReorderableStringList get_CfC()` |
| - | 0x2E94864 |  | `public void set_CfC(ReorderableStringList value)` |
| - | 0x2E94874 |  | `public ReorderableStringList get_CfZ()` |
| - | 0x2E9487C |  | `public void set_CfZ(ReorderableStringList value)` |
| - | 0x2E9488C |  | `public void add_tfY(Slot.BaseAction value)` |
| - | 0x2E9492C |  | `public void remove_tfY(Slot.BaseAction value)` |
| - | 0x2E949CC |  | `public void add_tfW(Slot.BaseAction value)` |
| - | 0x2E94A6C |  | `public void remove_tfW(Slot.BaseAction value)` |
| - | 0x2E94B0C |  | `public void add_tfE(Slot.PointerAction value)` |
| - | 0x2E94BAC |  | `public void remove_tfE(Slot.PointerAction value)` |
| - | 0x2E94C4C |  | `public void add_tfA(Slot.PointerAction value)` |
| - | 0x2E94CEC |  | `public void remove_tfA(Slot.PointerAction value)` |
| - | 0x2E94D8C |  | `public void add_tfu(Slot.PointerAction value)` |
| - | 0x2E94E2C |  | `public void remove_tfu(Slot.PointerAction value)` |
| - | 0x2E94ECC |  | `public void add_tfk(Slot.PointerAction value)` |
| - | 0x2E94F6C |  | `public void remove_tfk(Slot.PointerAction value)` |
| - | 0x2E9500C |  | `public void add_tfO(Slot.PointerAction value)` |
| - | 0x2E950AC |  | `public void remove_tfO(Slot.PointerAction value)` |
| 0x3AC000C | 0x2E9514C |  | `public bool Urk(Item e)` |
| - | 0x2E956D4 |  | `public void SetDragHidden(bool hidden, float seconds = 30)` |
| - | 0x2E95BB0 |  | `public void UrO(ItemHolder e)` |
| 0x3ABD9D4 | 0x2E95798 |  | `public void Refresh()` |
| 0x3AC0270 | 0x2E95C14 |  | `private bool Urt()` |
| 0x3AC054C | 0x2E95C1C |  | `private void Update()` |
| 0x3AC057C | 0x2E95C20 |  | `public RectTransform Urr(Item e, float f)` |
| 0x3AC0868 | 0x2E95F44 |  | `public void UrN(Vector3 e, float f)` |
| 0x3AC09A0 | 0x2E96118 | 36 | `public override void OnSelect(BaseEventData data)` |
| 0x3AC09EC | 0x2E96164 | 37 | `public override void OnDeselect(BaseEventData data)` |
| 0x3AC0C94 | 0x2E961B0 | 32 | `public override void OnPointerDown(PointerEventData data)` |
| 0x3AC0CE0 | 0x2E96200 | 33 | `public override void OnPointerUp(PointerEventData data)` |
| 0x3AC0D2C | 0x2E9624C | 39 | `public void OnBeginDrag(PointerEventData data)` |
| 0x3AC0D4C | 0x2E96274 | 40 | `public void OnDrag(PointerEventData data)` |
| 0x3AC0D6C | 0x2E96294 | 41 | `public void OnEndDrag(PointerEventData data)` |
| 0x3AC0E84 | 0x2E963FC | 4 | `protected override void Awake()` |
| 0x3AC0FA0 | 0x2E964A4 |  | `private void Urq(ItemHolder e)` |
| 0x3AC090C | 0x2E96084 |  | `private IEnumerator Urs(Vector3 e, float f)` |
| 0x3AC0C18 | 0x2E964D0 |  | `private IEnumerator UrC(int e)` |
| 0x3AC0514 | 0x2E964D8 |  | `public void UrZ(bool e)` |
| 0x3AC0FF4 | 0x2E96510 |  | `public void .ctor()` |

</details>

### public class `SlotSplitter` : Selectable, IBeginDragHandler, IEventSystemHandler, IDragHandler, IEndDragHandler  
`TypeDefIndex 3089`

| offset | field |
|---|---|
| 0x118 | `public Item CurrentItem;` |
| 0x120 | `public int SplitAmount;` |
| 0x128 | `private Image m_ItemIcon;` |
| 0x130 | `private Text m_StackDisplayer;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC9F88 | 0x2E96A3C |  | `public void add_tFc(SlotSplitter.PointerAction value)` |
| 0x3ACA028 | 0x2E96A40 |  | `public void remove_tFc(SlotSplitter.PointerAction value)` |
| 0x3ACA0C8 | 0x2E96A44 |  | `public void add_tFU(SlotSplitter.PointerAction value)` |
| 0x3ACA168 | 0x2E96A48 |  | `public void remove_tFU(SlotSplitter.PointerAction value)` |
| 0x3ACA208 | 0x2E96A4C |  | `public void add_tFY(SlotSplitter.PointerAction value)` |
| 0x3ACA2A8 | 0x2E96A50 |  | `public void remove_tFY(SlotSplitter.PointerAction value)` |
| 0x3ACA348 | 0x2E96A54 |  | `public void Refresh(int amount)` |
| 0x3ACA4B0 | 0x2E96A58 |  | `public RectTransform Uqf(float e)` |
| 0x3ACA700 | 0x2E96A60 | 39 | `public void OnBeginDrag(PointerEventData data)` |
| 0x3ACA720 | 0x2E96A64 | 40 | `public void OnDrag(PointerEventData data)` |
| 0x3ACA740 | 0x2E96A68 | 41 | `public void OnEndDrag(PointerEventData data)` |
| 0x3ACA848 | 0x2E96A6C |  | `public void .ctor()` |

</details>

### public class `SmeltingStationGUI` : yD  
`TypeDefIndex 3090`

| offset | field |
|---|---|
| 0x28 | `private XV m_Type;` |
| 0x30 | `private ItemContainer m_LootContainer;` |
| 0x38 | `private Image m_ProgressBar;` |
| 0x40 | `private FlamesIcon m_FlamesIcon;` |
| 0x48 | `private GameObject m_TurnOn;` |
| 0x50 | `private GameObject m_TurnOff;` |
| 0x58 | `private ItemContainer m_Input;` |
| 0x60 | `private ItemContainer m_Fuel;` |
| 0x68 | `private bool offable;` |
| 0x70 | `private SmeltingStation teh;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ABB2E4 | 0x2E96D6C |  | `private void Start()` |
| 0x3ABB45C | 0x2E97108 |  | `public void Update()` |
| 0x3ABB4F8 | 0x2E97368 |  | `private bool UOj(ItemHolder[] e)` |
| 0x3ABB9B8 | 0x2E97734 |  | `public void SwitchFire(bool enable)` |
| 0x3ABB8AC | 0x2E97220 |  | `private void UOa(bool e)` |
| 0x3ABBA0C | 0x2E96EC0 |  | `private void BindFireButton(GameObject target, bool on)` |
| - | 0x2E97824 |  | `private void TurnOnRecovered()` |
| - | 0x2E9782C |  | `private void TurnOffRecovered()` |
| - | 0x2E97834 |  | `private void UOQ()` |
| 0x3ABBB40 | 0x2E97840 |  | `private void UOH()` |
| 0x3ABBBB4 | 0x2E9784C |  | `public void .ctor()` |

</details>

### public class `StaticInterestMarkers` : MonoBehaviour  
`TypeDefIndex 3091`

| offset | field |
|---|---|
| 0x20 | `private jK worldSetUpContext;` |
| 0x28 | `private List<UiInterestAreaPin> markers;` |
| 0x30 | `private RectTransform rect;` |
| 0x38 | `private RectTransform convertPoint;` |
| 0x40 | `private bool tfz;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AC4E4C | 0x2E97854 |  | `public void UNO()` |
| 0x3AC552C | 0x2E9889C |  | `private void UNt()` |
| 0x3AC5704 | 0x2E988A0 |  | `public void .ctor()` |

</details>

### public class `TechTreeEntry` : MonoBehaviour  
`TypeDefIndex 3092`

| offset | field |
|---|---|
| 0x20 | `public Image icon;` |
| 0x28 | `public Image background;` |
| 0x30 | `public Color researchedColor;` |
| 0x40 | `public Color selectedColor;` |
| 0x50 | `public Color defaultColor;` |
| 0x60 | `public GameObject locked;` |
| 0x68 | `public string item;` |
| 0x70 | `public int cost;` |
| 0x74 | `public int level;` |
| 0x78 | `public List<TechTreeEntry> nextItems;` |
| 0x80 | `public bool unlocked;` |
| 0x81 | `public bool researched;` |
| 0x88 | `public List<RecoveredTechTreeLine> techTreeLines;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ACB884 | 0x2E988A8 |  | `public void UqF()` |
| 0x3ACB9EC | 0x2E98AD0 |  | `public void Research()` |
| 0x3ACBB70 | 0x2E98CDC |  | `public void Select()` |
| 0x3ACBBA0 | 0x2E98D6C |  | `public void Uqd()` |
| 0x3ACBC04 | 0x2E98E84 |  | `public void .ctor()` |

</details>

### public class `UiInterestAreaPin` : MonoBehaviour  
`TypeDefIndex 3093`

| offset | field |
|---|---|
| - | `private RectTransform recoveredRect;` |
| - | `private Image recoveredImage;` |
| - | `private jB <Type>k__BackingField;` |

Properties: `public jB Type { get; set; }`; `public RectTransform RectTransform { get; set; }`; `public Image Image { get; set; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E98E8C |  | `public jB get_Type()` |
| - | 0x2E98E94 |  | `private void set_Type(jB value)` |
| - | 0x2E987EC |  | `public RectTransform get_RectTransform()` |
| - | 0x2E98E9C |  | `private void set_RectTransform(RectTransform value)` |
| - | 0x2E9873C |  | `public Image get_Image()` |
| - | 0x2E98EA4 |  | `private void set_Image(Image value)` |
| 0x3AC5814 | 0x2E98EAC |  | `public void .ctor()` |

</details>

### public class `VirtualSlot` : MonoBehaviour  
`TypeDefIndex 3094`

| offset | field |
|---|---|
| 0x20 | `public ItemData itemData;` |
| 0x28 | `public int itemAmount;` |
| 0x30 | `private Image m_ItemIcon;` |
| 0x38 | `private Text m_StackDisplayer;` |
| 0x40 | `private DurabilityBar m_DurabilityBar;` |
| 0x48 | `private GameObject m_Locked;` |
| 0x50 | `private bool tFu;` |
| 0x58 | `private VirtualItem tFk;` |

Properties: `public bool CfT { get; }`; `public VirtualItem CfL { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E98EB4 |  | `public bool get_CfT()` |
| - | 0x2E98EBC |  | `public VirtualItem get_CfL()` |
| 0x3ACD704 | 0x2E98EC4 |  | `public void UqE(VirtualItem e, int f)` |
| 0x3ACDB70 | 0x2E990FC |  | `public void UqA(ItemData e, int f)` |
| 0x3ACDD2C | 0x2E991C0 |  | `public void Uqu(int e)` |
| 0x3ACDE2C | 0x2E992B4 |  | `protected void Awake()` |
| 0x3ACDB38 | 0x2E992B8 |  | `public void Uqk(bool e)` |
| 0x3ACDECC | 0x2E99354 |  | `public void .ctor()` |

</details>

### public class `Window` : MonoBehaviour  
`TypeDefIndex 3098`

| offset | field |
|---|---|
| - | `private bool <IgnoreInventoryState>k__BackingField;` |
| 0x0 | `public static Xq<int> Opened;` |
| 0x24 | `private float m_HideSpeed;` |
| 0x28 | `private float m_ShowSpeed;` |
| 0x2C | `private float m_RefreshSpeed;` |
| - | `Specific State - will open when the inventory opens in a specific state (e.g. Furnace-mode, Campfire-mode).` |
| - | `Manual - will have to be manually opened from another script.")]` |
| 0x30 | `private Window.yp m_OpenTrigger;` |
| 0x34 | `private Lf.TI m_StateTrigger;` |
| 0x38 | `private Animator m_Animator;` |
| 0x40 | `private CanvasGroup canvasGroup;` |
| 0x48 | `private GameObject content;` |
| - | `private bool <tfH>k__BackingField;` |

Properties: `public bool IgnoreInventoryState { get; set; }`; `public bool tfH { get; set; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9935C |  | `public bool get_IgnoreInventoryState()` |
| - | 0x2E99364 |  | `public void set_IgnoreInventoryState(bool value)` |
| - | 0x2E99370 |  | `public bool get_tfH()` |
| - | 0x2E99378 |  | `private void set_tfH(bool value)` |
| 0x3AC1B90 | 0x2E99384 | 4 | `public virtual void Open()` |
| 0x3AC1E00 | 0x2E99904 | 5 | `public virtual void Close(bool instant = false)` |
| 0x3AC2018 | 0x2E99C44 |  | `public void Refresh()` |
| 0x3AC2088 | 0x2E99CA0 | 6 | `protected virtual void Start()` |
| 0x3AC2168 | 0x2E99E00 |  | `private void Urx()` |
| - | 0x2E99BD8 |  | `private IEnumerator UrK()` |
| 0x3AC1FF8 | 0x2E99AE4 |  | `private void UrG()` |
| 0x3AC1D2C | 0x2E995F8 |  | `private void UrP()` |
| 0x3AC225C | 0x2E99F50 |  | `private void OnEnable()` |
| - | 0x2E9A0EC |  | `private void OnDisable()` |
| - | 0x2E9A254 |  | `private void OnDestroy()` |
| - | 0x2E9A3C4 |  | `public void .ctor()` |

</details>
