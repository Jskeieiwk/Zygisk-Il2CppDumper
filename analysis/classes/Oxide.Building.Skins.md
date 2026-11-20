# namespace `Oxide.Building.Skins`  (18 types)

### public sealed class `ConstructionBlastMarker` : MonoBehaviour  
`TypeDefIndex 3165`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EB7DE4 |  | `private void Start()` |
| - | 0x2EB8230 |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionBundleShop` : MonoBehaviour  
`TypeDefIndex 3168`

| offset | field |
|---|---|
| - | `private static ConstructionBundleShop current;` |
| - | `private Button action;` |
| - | `private Button closeButton;` |
| - | `private Button showSet;` |
| - | `private CollectionPrice price;` |
| - | `private RectTransform panel;` |
| - | `private Canvas canvas;` |
| - | `private Text previewName;` |
| - | `private Text status;` |
| - | `private CollectionPreviewStudio studio;` |
| - | `private bool buying;` |
| - | `private bool confirm;` |
| - | `private readonly Dictionary<ConstructionSkin, Image> cards;` |

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EB8238 |  | `public static void AddBanner(RectTransform parent)` |
| - | 0x2EB8244 |  | `public static void Show(Transform source)` |
| - | 0x2EB96AC |  | `private static string ShortName(ConstructionPieceType piece)` |
| - | 0x2EB86D0 |  | `private void Build()` |
| - | 0x2EB9AA8 |  | `public void SetPreview(ConstructionSkin skin)` |
| - | 0x2EBA80C |  | `private void OnEnable()` |
| - | 0x2EBA9DC |  | `private void OnDisable()` |
| - | 0x2EBABAC |  | `private void OnDestroy()` |
| - | 0x2EBAC60 |  | `private void Update()` |
| - | 0x2EBAD74 |  | `private bool CompleteSet()` |
| - | 0x2EBAF74 |  | `private bool SetEquipped()` |
| - | 0x2EBA2E4 |  | `private void Refresh()` |
| - | 0x2EBB1A0 |  | `private void Act()` |
| - | 0x2EBACF4 |  | `private void Close()` |
| - | 0x2EBBC14 |  | `public void .ctor()` |
| - | 0x2EBBC9C |  | `private void <Build>b__16_0()` |
| - | 0x2EBBCA4 |  | `private void <Build>b__16_1()` |
| - | 0x2EBBCC0 |  | `private void <Act>b__25_0(VirtualPurchaseItemResultDto result)` |
| - | 0x2EBC120 |  | `private void <Act>b__25_1(PlayFabError error)` |

</details>

### public static class `ConstructionCraftSkins`  
`TypeDefIndex 3169`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBC6E8 |  | `public static bool PieceOf(ItemData item, out ConstructionPieceType piece)` |
| - | 0x2EBC7F0 |  | `public static bool Owned(SkinData skin)` |
| - | 0x2EB4D98 |  | `public static int PreviewSkin(Item item)` |

</details>

### public sealed class `ConstructionDestructionData` : ScriptableObject  
`TypeDefIndex 3172`

| offset | field |
|---|---|
| - | `public const string ResourcePath = "ConstructionSkins/Destruction/Database";` |
| - | `public ConstructionDestructionData.Entry[] entries;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBC9AC |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionDestructionEffect` : MonoBehaviour  
`TypeDefIndex 3173`

| offset | field |
|---|---|
| - | `private static ConstructionDestructionData database;` |
| - | `private static readonly Dictionary<Mesh, ConstructionDestructionData.Entry> entries;` |
| - | `private static readonly HashSet<ConstructionDestructionEffect> active;` |
| - | `private readonly List<Rigidbody> bodies;` |

Properties: `public static int ActiveBodyCount { get; }`; `public static int ActiveChunkCount { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBCAE0 |  | `public static int get_ActiveBodyCount()` |
| - | 0x2EBCDE4 |  | `public static int get_ActiveChunkCount()` |
| - | 0x2EBCE30 |  | `private static void ResetState()` |
| - | 0x2EBD118 |  | `private static void Load()` |
| - | 0x2EBD374 |  | `private static ConstructionDestructionData.Entry Entry(Mesh mesh)` |
| - | 0x2EBD688 |  | `public static bool TryPlay(Component piece, GameObject visualRoot, int grade)` |
| - | 0x2EBE464 |  | `private static BoxCollider AddBox(GameObject chunk, Bounds bounds)` |
| - | 0x2EB7E9C |  | `public static void NotifyBlast(Vector3 position, Scene scene)` |
| - | 0x2EBCEC8 |  | `public static void Clear()` |
| - | 0x2EBE50C |  | `private void OnDestroy()` |
| - | 0x2EBE3C8 |  | `private static void DestroyObject(Object value)` |
| - | 0x2EBE58C |  | `public void .ctor()` |
| - | 0x2EBE614 |  | `private static void .cctor()` |

</details>

### public enum `ConstructionPieceType`  
`TypeDefIndex 3174`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ConstructionPieceType Wall = 0;` |
| - | `public const ConstructionPieceType Doorway = 1;` |
| - | `public const ConstructionPieceType Window = 2;` |
| - | `public const ConstructionPieceType Foundation = 3;` |
| - | `public const ConstructionPieceType FoundationTriangle = 4;` |
| - | `public const ConstructionPieceType Floor = 5;` |
| - | `public const ConstructionPieceType FloorTriangle = 6;` |
| - | `public const ConstructionPieceType FoundationStairs = 7;` |
| - | `public const ConstructionPieceType LShapedStairs = 8;` |
| - | `public const ConstructionPieceType UShapedStairs = 9;` |
| - | `public const ConstructionPieceType HighStoneWall = 10;` |
| - | `public const ConstructionPieceType HighStoneGates = 11;` |

### public enum `ConstructionGrade`  
`TypeDefIndex 3175`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ConstructionGrade Wood = 0;` |
| - | `public const ConstructionGrade Stone = 1;` |
| - | `public const ConstructionGrade Metal = 2;` |
| - | `public const ConstructionGrade HighQualityMetal = 3;` |

### public enum `ConstructionSkinRarity`  
`TypeDefIndex 3176`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ConstructionSkinRarity Common = 0;` |
| - | `public const ConstructionSkinRarity Uncommon = 1;` |
| - | `public const ConstructionSkinRarity Rare = 2;` |
| - | `public const ConstructionSkinRarity Epic = 3;` |
| - | `public const ConstructionSkinRarity Legendary = 4;` |

### public sealed class `ConstructionSkin` : ScriptableObject  
`TypeDefIndex 3179`

| offset | field |
|---|---|
| - | `public string id;` |
| - | `public int networkId;` |
| - | `public string bundleId;` |
| - | `public ConstructionPieceType piece;` |
| - | `public string nameKey;` |
| - | `public string englishName;` |
| - | `public string descriptionKey;` |
| - | `public string englishDescription;` |
| - | `public Sprite icon;` |
| - | `public Color tint;` |
| - | `public ConstructionSkinRarity rarity;` |
| - | `public ConstructionSkin.GradeLook[] grades;` |
| - | `public bool placeholder;` |
| - | `public int price;` |

Properties: `public string DisplayName { get; }`; `public string Description { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBE6FC |  | `public string get_DisplayName()` |
| - | 0x2EBE77C |  | `public string get_Description()` |
| - | 0x2EBE7FC |  | `public ConstructionSkin.GradeLook For(ConstructionGrade grade)` |
| - | 0x2EBE91C |  | `public static Color RarityColor(ConstructionSkinRarity rarity)` |
| - | 0x2EBE9C4 |  | `private static ConstructionSkin.GradeLook[] NewGrades()` |
| - | 0x2EBEC48 |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionSkinApplication` : MonoBehaviour  
`TypeDefIndex 3181`

| offset | field |
|---|---|
| - | `private readonly Dictionary<Renderer, Material[]> materials;` |
| - | `private readonly Dictionary<MeshFilter, ConstructionSkinApplication.OriginalMesh> meshes;` |
| - | `private MeshFilter filter;` |
| - | `private Mesh mesh;` |
| - | `private Vector3 position;` |
| - | `private Vector3 scale;` |
| - | `private Quaternion rotation;` |
| - | `private bool captured;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBECE8 |  | `private void Capture()` |
| - | 0x2EBF0BC |  | `public void Apply(ConstructionSkin.GradeLook look)` |
| - | 0x2EBF8AC |  | `public void Restore()` |
| - | 0x2EBFCBC |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionSkinDatabase` : ScriptableObject  
`TypeDefIndex 3184`

| offset | field |
|---|---|
| - | `public const string ResourcePath = "ConstructionSkins/ConstructionSkinDatabase";` |
| - | `public List<ConstructionSkin> skins;` |
| - | `public Sprite bundleIcon;` |
| - | `public Sprite bundleBanner;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBFD98 |  | `public IEnumerable<ConstructionSkin> For(ConstructionPieceType piece)` |
| - | 0x2EBFE74 |  | `public ConstructionSkin Find(string id)` |
| - | 0x2EBFF84 |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionSkinPointer` : MonoBehaviour, IPointerEnterHandler, IEventSystemHandler, IPointerExitHandler, IPointerDownHandler, IPointerUpHandler, IPointerClickHandler  
`TypeDefIndex 3185`

| offset | field |
|---|---|
| - | `public bool hovered;` |
| - | `public bool pressed;` |
| - | `public Action entered;` |
| - | `public Action clicked;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EC0134 |  | `public void OnPointerEnter(PointerEventData e)` |
| - | 0x2EC0158 |  | `public void OnPointerExit(PointerEventData e)` |
| - | 0x2EC0160 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2EC016C |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2EC0174 |  | `public void OnPointerClick(PointerEventData e)` |
| - | 0x2EC0190 |  | `private void OnDisable()` |
| - | 0x2EC0198 |  | `public void .ctor()` |

</details>

### public sealed class `ConstructionSkinPop` : MonoBehaviour  
`TypeDefIndex 3186`

| offset | field |
|---|---|
| - | `private float time;` |
| - | `private float shake;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EC01A0 |  | `public void Pop()` |
| - | 0x2EC01A8 |  | `public void Shake()` |
| - | 0x2EC01B0 |  | `private void Update()` |
| - | 0x2EC0388 |  | `private void OnDisable()` |
| - | 0x2EC0454 |  | `public void .ctor()` |

</details>

### public static class `ConstructionSkins`  
`TypeDefIndex 3191`

| offset | field |
|---|---|
| - | `public const string BrickBundleId = "bundle.construction.heritage.brick";` |
| - | `public const int BrickNetworkId = 1001;` |
| - | `private static ConstructionSkinDatabase database;` |
| - | `private static bool loaded;` |
| - | `private static Action Changed;` |

Properties: `public static ConstructionSkinDatabase Database { get; }`

<details><summary>methods (24)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EBA900 |  | `public static void add_Changed(Action value)` |
| - | 0x2EBAAD0 |  | `public static void remove_Changed(Action value)` |
| - | 0x2EC0464 |  | `private static void .cctor()` |
| - | 0x2EB99BC |  | `public static ConstructionSkinDatabase get_Database()` |
| - | 0x2EC0504 |  | `public static void ReloadDatabase()` |
| - | 0x2EC056C |  | `public static List<ConstructionSkin> For(ConstructionPieceType piece)` |
| - | 0x2EBC4B8 |  | `public static bool CraftedItem(ConstructionPieceType piece)` |
| - | 0x2EC0684 |  | `private static string Key(ConstructionPieceType piece)` |
| - | 0x2EC0718 |  | `public static bool OwnsId(string id)` |
| - | 0x2EBC8BC |  | `public static bool Owned(ConstructionSkin skin)` |
| - | 0x2EBC564 |  | `public static ConstructionSkin Selected(ConstructionPieceType piece)` |
| - | 0x2EC0848 |  | `public static void Select(ConstructionPieceType piece, ConstructionSkin skin)` |
| - | 0x2EBB8D8 |  | `public static bool SelectSet(string bundleId)` |
| - | 0x2EBB3E4 |  | `public static void ClearSet(string bundleId)` |
| - | 0x2EC0A40 |  | `public static string SkinId(ConstructionPieceType piece)` |
| - | 0x2EC0B40 |  | `public static ConstructionSkin ForNetwork(ConstructionPieceType piece, int networkId)` |
| - | 0x2EB5AA0 |  | `public static int SelectedNetworkId(BuildingPiece target)` |
| - | 0x2EC0D60 |  | `public static bool PieceOf(BuildingCategory category, out ConstructionPieceType piece)` |
| - | 0x2EC0CB8 |  | `public static bool PieceOf(BuildingPiece target, out ConstructionPieceType piece)` |
| - | 0x2EC0E14 |  | `public static bool PieceOf(string name, out ConstructionPieceType piece)` |
| - | 0x2EB0930 |  | `public static bool ApplyNetwork(GameObject target, BuildingPiece piece, int networkId, int grade)` |
| - | 0x2EC13F4 |  | `public static bool Apply(GameObject target, ConstructionSkin skin, ConstructionGrade grade)` |
| - | 0x2EB086C |  | `public static void Restore(GameObject target)` |
| - | 0x2EC09AC |  | `private static void Notify()` |

</details>

### public sealed class `ConstructionSkinStrip` : MonoBehaviour  
`TypeDefIndex 3195`

| offset | field |
|---|---|
| - | `private const float Width = 236;` |
| - | `private const float Pad = 14;` |
| - | `private const float Inner = 208;` |
| - | `private const float Gap = 10;` |
| - | `private const float TileHeight = 112;` |
| - | `private static readonly Color Card;` |
| - | `private static readonly Color TileColor;` |
| - | `private RectTransform window;` |
| - | `private RectTransform wheelRing;` |
| - | `private RectTransform card;` |
| - | `private RectTransform info;` |
| - | `private RectTransform unlockButton;` |
| - | `private CanvasGroup windowGroup;` |
| - | `private CanvasGroup group;` |
| - | `private CanvasGroup infoGroup;` |
| - | `private Text nameLabel;` |
| - | `private Text rarityLabel;` |
| - | `private Text descriptionLabel;` |
| - | `private Text unlockLabel;` |
| - | `private Font bold;` |
| - | `private Font regular;` |
| - | `private ConstructionPieceType piece;` |
| - | `private Sprite pieceIcon;` |
| - | `private ConstructionSkin focused;` |
| - | `private readonly List<ConstructionSkinStrip.Tile> tiles;` |
| - | `private bool available;` |
| - | `private bool wasVisible;` |
| - | `private float shown;` |
| - | `private float infoFade;` |
| - | `private float height;` |

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EC1788 |  | `private void OnEnable()` |
| - | 0x2EC1888 |  | `private void OnDisable()` |
| - | 0x2EC1980 |  | `private void Changed()` |
| - | 0x2EC2238 |  | `public static void Show(BuildingWheel wheel, BuildingCategory category)` |
| - | 0x2EC2584 |  | `private static List<ConstructionSkin> Ready(ConstructionPieceType type)` |
| - | 0x2EC2340 |  | `private void Refresh(BuildingCategory category)` |
| - | 0x2EC2744 |  | `private bool Build()` |
| - | 0x2EC35A4 |  | `private void BuildTiles()` |
| - | 0x2EC4AE8 |  | `private static string ShortName(ConstructionSkin skin)` |
| - | 0x2EC4EE4 |  | `private void Choose(ConstructionSkinStrip.Tile tile)` |
| - | 0x2EC19FC |  | `private void UpdateState()` |
| - | 0x2EC5570 |  | `private void Update()` |
| - | 0x2EC5FD0 |  | `private void Place(float slide)` |
| - | 0x2EC63A0 |  | `public RectTransform Settle()` |
| - | 0x2EC4288 |  | `private static void Remove(GameObject go)` |
| - | 0x2EC6600 |  | `public void .ctor()` |
| - | 0x2EC6690 |  | `private static void .cctor()` |
| - | 0x2EC66F4 |  | `private void <Build>b__37_0()` |

</details>

### public static class `ConstructionSkinUi`  
`TypeDefIndex 3196`

| offset | field |
|---|---|
| - | `public static readonly Color Yellow;` |
| - | `public static readonly Color Button;` |
| - | `private static readonly Dictionary<string, Sprite> sprites;` |
| - | `private static readonly Dictionary<string, AudioClip> sounds;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EC688C |  | `public static Sprite Sprite(string name)` |
| - | 0x2EC5128 |  | `public static void Play(string name, float volume = 0.7)` |
| - | 0x2EC5320 |  | `public static void PlayEquip(bool skin)` |
| - | 0x2EC53D4 |  | `public static int Price(ConstructionSkin skin)` |
| - | 0x2EC548C |  | `public static string Rarity(ConstructionSkinRarity rarity)` |
| - | 0x2EC4450 |  | `public static RectTransform Rect(string name, Transform parent, float x, float y, float width, float height)` |
| - | 0x2EC48B8 |  | `public static RectTransform Stretch(string name, Transform parent, float inset = 0)` |
| - | 0x2EC433C |  | `public static Image Image(RectTransform rt, string sprite, Color color)` |
| - | 0x2EC4BB0 |  | `public static Image[] Frame(Transform parent, float thickness, Color color)` |
| - | 0x2EC4658 |  | `public static Text Text(RectTransform rt, Font font, int size, Color color, TextAnchor anchor, bool wrap = false)` |
| - | 0x2EC47A4 |  | `public static void Fit(Text text, int min)` |
| - | 0x2EC481C |  | `public static void Shadow(Text text, float alpha = 0.5)` |
| - | 0x2EC6354 |  | `public static float Damp(float current, float target, float speed, float dt)` |
| - | 0x2EC5FAC |  | `public static float OutCubic(float t)` |
| - | 0x2EC69B4 |  | `private static void .cctor()` |

</details>

### public sealed class `ConstructionUpgradeEffect` : MonoBehaviour  
`TypeDefIndex 3198`

| offset | field |
|---|---|
| - | `private const string Resource = "ConstructionSkins/FX/";` |
| - | `private const string Sounds = "ConstructionSkins/Sounds/";` |
| - | `private const float MaxDistance = 70;` |
| - | `private const float SettleTime = 0.3;` |
| - | `private static readonly ConstructionUpgradeEffect.Profile Stone;` |
| - | `private static readonly ConstructionUpgradeEffect.Profile Metal;` |
| - | `private static readonly ConstructionUpgradeEffect.Profile Armour;` |
| - | `private static Shader masonry;` |
| - | `private static Material dustMaterial;` |
| - | `private static Material sparkMaterial;` |
| - | `private static bool loaded;` |
| - | `private static bool ownsSparkMaterial;` |
| - | `private static bool warnedMissing;` |
| - | `private static readonly Dictionary<string, AudioClip> clips;` |
| - | `private static readonly Dictionary<Material, Material> growing;` |
| - | `private static readonly Dictionary<Material, Material> fading;` |
| - | `private static readonly int RevealY;` |
| - | `private static readonly int RevealAxis;` |
| - | `private static readonly int RevealLag;` |
| - | `private static readonly int RevealFresh;` |
| - | `private static readonly int RevealParts;` |
| - | `private static readonly int RevealSlide;` |
| - | `private static readonly int RevealDelay;` |
| - | `private static readonly int RevealCourse;` |
| - | `private static readonly int RevealJitter;` |
| - | `private static readonly int RevealPress;` |
| - | `private static readonly int RevealHeat;` |
| - | `private static readonly int RevealHeatWidth;` |
| - | `private static readonly int RevealSheen;` |
| - | `private ConstructionUpgradeEffect.Profile profile;` |
| - | `private GameObject ghost;` |
| - | `private GameObject ghostPivot;` |
| - | `private GameObject ground;` |
| - | `private readonly List<Renderer> grown;` |
| - | `private readonly List<Material[]> originals;` |
| - | `private readonly List<Material[]> variants;` |
| - | `private readonly List<MaterialPropertyBlock> originalBlocks;` |
| - | `private readonly List<MaterialPropertyBlock> activeBlocks;` |
| - | `private Renderer[] ghostRenderers;` |
| - | `private MaterialPropertyBlock newBlock;` |
| - | `private MaterialPropertyBlock oldBlock;` |
| - | `private ParticleSystem smoke;` |
| - | `private ParticleSystem wisps;` |
| - | `private ParticleSystem debris;` |
| - | `private ParticleSystem sparks;` |
| - | `private Transform settling;` |
| - | `private Vector3 settlingFrom;` |
| - | `private Bounds bounds;` |
| - | `private Bounds emitterBounds;` |
| - | `private int emitterFace;` |
| - | `private int visualLayer;` |
| - | `private float surfaceFrom;` |
| - | `private float surfaceTo;` |
| - | `private Vector3 axis;` |
| - | `private float from;` |
| - | `private float to;` |
| - | `private float spread;` |
| - | `private float duration;` |
| - | `private float time;` |
| - | `private float nextTap;` |
| - | `private float settle;` |
| - | `private float groundY;` |
| - | `private float emissionRemainder;` |
| - | `private float previousLine;` |
| - | `private int emittedSamples;` |
| - | `private bool running;` |

<details><summary>methods (30)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EC6AC4 |  | `private static void ResetResources()` |
| - | 0x2EC6FB4 |  | `private static bool Load()` |
| - | 0x2EC7540 |  | `private static AudioClip Clip(string name)` |
| - | 0x2EC7668 |  | `public static GameObject Snapshot(GameObject oldRoot)` |
| - | 0x2EC7B34 |  | `private static GameObject CopyRenderHierarchy(Transform source, Transform parent)` |
| - | 0x2EC8C4C |  | `public static void Play(Component piece, GameObject before, GameObject newRoot, int grade)` |
| - | 0x2ECA5DC |  | `public static void Cancel(Component piece)` |
| - | 0x2EC81C0 |  | `private static Material Variant(Material source, bool grow)` |
| - | 0x2ECA6A0 |  | `private float Spread(Material material)` |
| - | 0x2EC9134 |  | `private bool Begin(GameObject before, GameObject newRoot)` |
| - | 0x2ECAAD8 |  | `private void IncludeBounds(Renderer renderer, ref bool found, ref bool emitterFound)` |
| - | 0x2ECAE5C |  | `private void Recess(GameObject copy)` |
| - | 0x2ECBEAC |  | `private void Update()` |
| - | 0x2ECBEC8 |  | `private void Step(float deltaTime)` |
| - | 0x2ECB8E4 |  | `private void Apply(float line)` |
| - | 0x2ECCC1C |  | `private void Impact()` |
| - | 0x2ECC9B4 |  | `private void Sound(string name, float pitch, float volume)` |
| - | 0x2EC8E3C |  | `public void Finish()` |
| - | 0x2ECA7B0 |  | `private void Restore()` |
| - | 0x2ECE56C |  | `private void OnDisable()` |
| - | 0x2ECE588 |  | `private void OnDestroy()` |
| - | 0x2EC6ED0 |  | `private static void Dispose(Object value, float after = 0)` |
| - | 0x2ECB510 |  | `private void StartParticles()` |
| - | 0x2ECD394 |  | `private ParticleSystem Particles(string name, Material material, int max, Color start, Color end, float minSize, float maxSize, float gravity, float minLife, float maxLife, bool bounce)` |
| - | 0x2ECDEFC |  | `private static void Release(ParticleSystem system, float after)` |
| - | 0x2ECBB88 |  | `private void BurstAtLine(float line, int smokeCount, int sparkCount)` |
| - | 0x2ECC240 |  | `private void EmitAlong(float line, float deltaTime)` |
| - | 0x2ECDFD4 |  | `private bool SurfacePoint(float line, out Vector3 point, out Vector3 outward)` |
| - | 0x2ECE630 |  | `public void .ctor()` |
| - | 0x2ECE7E0 |  | `private static void .cctor()` |

</details>

### public sealed class `CraftedConstructionSkinData` : SkinData  
`TypeDefIndex 3199`

| offset | field |
|---|---|
| - | `public ConstructionSkin constructionSkin;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2ECF274 |  | `public override QT dxJ(QT target, int variant = 0)` |
| - | 0x2ECF468 |  | `public void .ctor()` |

</details>
