# namespace `Oxide.Building`  (11 types)

### public class `BuildingHelpers`  
`TypeDefIndex 3148`

| offset | field |
|---|---|
| 0x10 | `public LayerMask m_BuildingPieceMask;` |
| 0x14 | `public LayerMask m_OccupyPlacementMask;` |
| 0x18 | `public LayerMask m_FreePlacementMask;` |
| 0x1C | `public LayerMask m_NoPlacementMask;` |
| 0x20 | `public LayerMask m_TerrainMask;` |
| 0x24 | `private int m_BuildRange;` |
| 0x28 | `private bool m_UsePulseEffect;` |
| 0x29 | `private bool m_PulseWhenSnapped;` |
| 0x2C | `private float m_PulseEffectDuration;` |
| 0x30 | `private float m_PulseMin;` |
| 0x34 | `private float m_PulseMax;` |
| 0x38 | `private PlayerManager m_PlayerManager;` |
| 0x40 | `private BuildingPiece[] m_Pieces;` |
| 0x48 | `private BuildingPiece Ovu;` |
| 0x50 | `public GameObject m_CurrentPreview;` |
| 0x58 | `private Socket Ovk;` |
| 0x60 | `private bool OvO;` |
| 0x61 | `private bool Ovt;` |
| 0x64 | `private Color Ovr;` |
| 0x74 | `private Vector3 OvN;` |
| 0x80 | `private Transform Ovq;` |
| 0x88 | `private dI Ovs;` |
| 0x90 | `private BuildingPiece OvC;` |
| 0x98 | `private Camera OvZ;` |
| 0xA0 | `private SleepingBagData[] Ovj;` |
| 0xA8 | `private float Ova;` |

Properties: `public BuildingPiece sIM { get; }`; `public bool sMe { get; set; }`; `public bool sMf { get; }`; `public Color sMF { get; set; }`; `public Vector3 sMd { get; set; }`; `public Socket sMc { get; }`; `public int sMU { get; }`; `public BuildingPiece[] sMY { get; }`

<details><summary>methods (33)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EAC1E4 |  | `public BuildingPiece get_sIM()` |
| - | 0x2EAC1EC |  | `public bool get_sMe()` |
| - | 0x2EAC1F4 |  | `public void set_sMe(bool value)` |
| - | 0x2EAC200 |  | `public bool get_sMf()` |
| - | 0x2EAC208 |  | `public Color get_sMF()` |
| - | 0x2EAC214 |  | `public void set_sMF(Color value)` |
| - | 0x2EAC220 |  | `public Vector3 get_sMd()` |
| - | 0x2EAC22C |  | `public void set_sMd(Vector3 value)` |
| - | 0x2EAC238 |  | `public Socket get_sMc()` |
| - | 0x2EAC240 |  | `public int get_sMU()` |
| - | 0x2EAC248 |  | `public BuildingPiece[] get_sMY()` |
| 0x3A7F844 | 0x2EAC250 |  | `public void UdA(Transform e, XA f, AudioSource F)` |
| 0x3A7F914 | 0x2EAC320 |  | `public void Udu()` |
| 0x3A7FA48 | 0x2EAC454 |  | `private void Udk()` |
| 0x3A80A8C | 0x2EAD7E0 |  | `private void UdO()` |
| 0x3A7FE70 | 0x2EAC7D4 |  | `private void Udt()` |
| 0x3A80BA8 | 0x2EAD900 |  | `public void Udr()` |
| 0x3A81B40 | 0x2EAE800 |  | `private void UdN()` |
| 0x3A80D60 | 0x2EADA60 |  | `private void Udq(Collider[] e)` |
| 0x3A81598 | 0x2EAE25C |  | `private bool Uds()` |
| 0x3A8269C | 0x2EAF330 |  | `public void UdC(GameObject e, int itemSkin = -1)` |
| 0x3A82B64 | 0x2EAF9C8 |  | `public void UdZ(SleepingBagData[] e, float f = 0)` |
| 0x3A80B0C | 0x2EAD868 |  | `private bool Udj(Vector3 e)` |
| 0x3A807FC | 0x2EAD54C |  | `public bool Uda()` |
| 0x3A80278 | 0x2EACFC8 |  | `public bool UdQ()` |
| 0x3A803CC | 0x2EAD114 |  | `public bool UdH()` |
| 0x3A80960 | 0x2EAD6A8 |  | `public bool Udi()` |
| 0x3A8055C | 0x2EAD2BC |  | `public bool Udw()` |
| 0x3A806D0 | 0x2EAD430 |  | `public bool UdJ()` |
| 0x3A82B90 | 0x2EAF9F4 |  | `public void UdX()` |
| 0x3A82C24 | 0x2EAFA88 |  | `public void UdT()` |
| 0x3A82D30 | 0x2EAFB94 |  | `public bool UdL()` |
| 0x3A82D8C | 0x2EAFBF0 |  | `public void .ctor()` |

</details>

### public class `BuildingPiece` : vd  
`TypeDefIndex 3150`

| offset | field |
|---|---|
| 0x78 | `private string m_PieceName;` |
| 0x80 | `private int m_PieceIndex;` |
| 0x84 | `private Vector3 m_CorrectPosition;` |
| 0x90 | `private Vector3 m_CorrectRotation;` |
| 0xA0 | `private RequiredItem[] m_RequiredItems;` |
| 0xA8 | `private Vector3 m_RotationAmount;` |
| 0xB4 | `private bool m_ShowBounds;` |
| 0xB8 | `private Bounds m_Bounds;` |
| 0xD0 | `private YU[] m_ObstacleChecks;` |
| 0xD8 | `private SurfaceIdentity m_SurfaceIdentity;` |
| 0xE0 | `private MeshCollider m_MeshCollider;` |
| 0xE8 | `private MeshFilter m_MainMesh;` |
| 0xF0 | `private List<Renderer> m_Renderers;` |
| 0xF8 | `private List<Renderer> m_IgnoredRenderers;` |
| 0x100 | `private List<Collider> m_Colliders;` |
| 0x108 | `private List<Collider> m_IgnoredColliders;` |
| 0x110 | `public cs[] m_Grades;` |
| 0x118 | `public BuildingGrade.dR m_Grade;` |
| 0x120 | `public Transform skinHolder;` |
| 0x128 | `private bool m_Deployable;` |
| 0x129 | `private bool m_CheckObstacle;` |
| 0x130 | `private string m_PickupItem;` |
| 0x138 | `private float m_HealthMultiplier;` |
| 0x140 | `private Xb m_Inventory;` |
| 0x148 | `private yA m_NeededSpace;` |
| 0x150 | `private yA[] m_SpacesToOccupy;` |
| 0x158 | `private List<string> m_IgnoredOverlaps;` |
| 0x160 | `private bool m_RequiresSockets;` |
| 0x164 | `private float m_OutOfGroundHeight;` |
| 0x168 | `private bool m_AllowUnderTerrainMovement;` |
| 0x170 | `private Behaviour[] m_BehavioursToDisable;` |
| 0x178 | `private bool m_CheckStability;` |
| 0x17C | `private LayerMask m_StabilityCheckMask;` |
| 0x180 | `private bool m_ShowStabilityBox;` |
| 0x188 | `private Bounds[] m_StabilityBoxes;` |
| 0x190 | `private bool grounded;` |
| 0x191 | `public bool m_EnableTP;` |
| 0x192 | `public bool m_ShowTP;` |
| 0x194 | `public Bounds m_TPBox;` |
| 0x1B0 | `private SoundPlayer m_BuildAudio;` |
| 0x1B8 | `private GameObject m_PlacementFX;` |
| 0x1C0 | `private Material m_PreviewMat;` |
| 0x1C8 | `public Transform[] terrainTests;` |
| 0x1D0 | `public di[] areaCheckTests;` |
| 0x1D8 | `public float withinDegrees;` |
| 0x1DC | `public bool m_TerrainFit;` |
| 0x1E0 | `public float stability;` |
| 0x1E4 | `public int grade;` |
| 0x1E8 | `public int skin;` |
| 0x1F0 | `public Socket[] Sockets;` |
| 0x1F8 | `private Lock m_Lock;` |
| 0x200 | `private cQ m_Decay;` |
| 0x208 | `private PieceVitals m_PieceVitals;` |
| 0x210 | `private XE m_EntityHandler;` |
| 0x218 | `private float OvX;` |
| 0x21C | `private float OvT;` |
| 0x220 | `private Dictionary<Renderer, Material[]> OvL;` |
| 0x228 | `private yu Ovo;` |
| 0x230 | `private List<BuildingPiece.yk> Ovy;` |
| 0x238 | `private int Ovz;` |
| 0x23C | `private bool Ovh;` |
| 0x240 | `private List<yq> OvB;` |
| 0x248 | `private bool Ovm;` |
| 0x249 | `private bool OvR;` |
| 0x24A | `private bool Ovb;` |
| 0x24C | `public float health;` |
| 0x250 | `public float maxHealth;` |
| 0x0 | `public static HashSet<BuildingPiece> saveList;` |
| 0x8 | `private static Queue<BuildingPiece> Ovx;` |
| 0x10 | `private static uint OvK;` |
| 0x254 | `private uint OvG;` |
| 0x258 | `private float OvP;` |
| 0x260 | `private Vector3[] OvD;` |
| 0x268 | `private Material Ovn;` |
| 0x270 | `private QT OvV;` |
| - | `private yE <Ovw>k__BackingField;` |
| - | `private BuildingPiece <OvJ>k__BackingField;` |
| - | `private bool <Ovl>k__BackingField;` |
| - | `private int visualGrade;` |
| - | `private int visualSkin;` |

Properties: `public yu sMW { get; }`; `public yE Ovw { get; set; }`; `public BuildingPiece OvJ { get; set; }`; `public string sME { get; }`; `public Vector3 sMA { get; }`; `public Vector3 sMu { get; }`; `public RequiredItem[] sMk { get; }`; `public Vector3 sMO { get; }`; `public yA sMt { get; }`; `public yA[] sMr { get; }`; `public List<string> sMN { get; }`; `public float sMq { get; }`; `public bool sMs { get; }`; `public bool sMC { get; }`; `public SoundPlayer sMZ { get; }`; `public GameObject sMj { get; }`; `public Bounds sMa { get; }`; `public YU[] sMQ { get; }`; `public List<Renderer> sMH { get; }`; `public MeshFilter sMi { get; }`; `public bool sMw { get; }`; `public bool sMJ { get; }`; `public string sMX { get; }`; `public int sMT { get; }`; `public float sML { get; }`; `public LayerMask sMo { get; }`; `public Lock sMy { get; }`; `public float sMz { get; }`; `public bool Ovl { get; set; }`; `public float sMh { get; }`; `public int sMB { get; }`; `public int sMm { get; }`; `public float sMR { get; }`; `public float sMb { get; }`

<details><summary>methods (69)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EAFC30 |  | `public yu get_sMW()` |
| - | 0x2EAFC38 |  | `public yE get_Ovw()` |
| - | 0x2EAFC40 |  | `public void set_Ovw(yE value)` |
| - | 0x2EAFC50 |  | `public BuildingPiece get_OvJ()` |
| - | 0x2EAFC58 |  | `public void set_OvJ(BuildingPiece value)` |
| - | 0x2EAFC68 |  | `public string get_sME()` |
| - | 0x2EAFC70 |  | `public Vector3 get_sMA()` |
| - | 0x2EAFC7C |  | `public Vector3 get_sMu()` |
| - | 0x2EAFC88 |  | `public RequiredItem[] get_sMk()` |
| - | 0x2EAFC90 |  | `public Vector3 get_sMO()` |
| - | 0x2EAFC9C |  | `public yA get_sMt()` |
| - | 0x2EAFCA4 |  | `public yA[] get_sMr()` |
| - | 0x2EAFCAC |  | `public List<string> get_sMN()` |
| - | 0x2EAFCB4 |  | `public float get_sMq()` |
| - | 0x2EAFCBC |  | `public bool get_sMs()` |
| - | 0x2EAFCC4 |  | `public bool get_sMC()` |
| - | 0x2EAFCCC |  | `public SoundPlayer get_sMZ()` |
| - | 0x2EAFCD4 |  | `public GameObject get_sMj()` |
| - | 0x2EACA54 |  | `public Bounds get_sMa()` |
| - | 0x2EAFCDC |  | `public YU[] get_sMQ()` |
| - | 0x2EAFCE4 |  | `public List<Renderer> get_sMH()` |
| - | 0x2EAFCEC |  | `public MeshFilter get_sMi()` |
| - | 0x2EAFCF4 |  | `public bool get_sMw()` |
| - | 0x2EAFCFC |  | `public bool get_sMJ()` |
| - | 0x2EAFD1C |  | `public string get_sMX()` |
| - | 0x2EAFD24 |  | `public int get_sMT()` |
| - | 0x2EAFD2C |  | `public float get_sML()` |
| - | 0x2EAFD34 |  | `public LayerMask get_sMo()` |
| - | 0x2EAFD3C |  | `public Lock get_sMy()` |
| 0x3A82ED4 | 0x2EAFD44 |  | `public float get_sMz()` |
| - | 0x2EAFD4C |  | `public bool get_Ovl()` |
| - | 0x2EAFD54 |  | `private void set_Ovl(bool value)` |
| - | 0x2EAFD60 |  | `public float get_sMh()` |
| - | 0x2EAFD68 |  | `public int get_sMB()` |
| - | 0x2EAFD70 |  | `public int get_sMm()` |
| - | 0x2EAFD78 |  | `public float get_sMR()` |
| - | 0x2EAFD80 |  | `public float get_sMb()` |
| - | 0x2EAFD88 |  | `private void RefreshNetworkAppearance()` |
| 0x3A82F04 | 0x2EB0A28 |  | `private void Awake()` |
| 0x3A83728 | 0x2EB1248 | 11 | `public override void Fsv()` |
| 0x3A83BA8 | 0x2EB127C | 10 | `public override void diJ()` |
| 0x3A82864 | 0x2EAF620 |  | `public void Uck(yu e)` |
| 0x3A83A60 | 0x2EB15C0 |  | `private void UcO(Material e)` |
| 0x3A83EEC | 0x2EB1708 |  | `private void Uct(Dictionary<Renderer, Material[]> e)` |
| 0x3A7FEC4 | 0x2EAC828 |  | `public bool Ucr()` |
| 0x3A8019C | 0x2EACB00 |  | `public bool UcN(Collider e)` |
| 0x3A8407C | 0x2EB1898 |  | `public bool Ucq()` |
| 0x3A82814 | 0x2EAF4D0 |  | `public void Ucs(int e)` |
| 0x3A8428C | 0x2EB1AAC |  | `public void UcC(int e)` |
| 0x3A843B0 | 0x2EB1AB0 |  | `public void UcZ(int e)` |
| 0x3A844D4 | 0x2EB1AB4 |  | `public void Ucj(PlayerManager e)` |
| 0x3A844D8 | 0x2EB1AB8 |  | `public void Uca(PlayerManager e)` |
| 0x3A844DC | 0x2EB1ABC |  | `public void UcQ()` |
| 0x3A84550 | 0x2EB1B18 |  | `public void StopDemolishTimer()` |
| 0x3A84558 | 0x2EB1B20 |  | `private bool UcH()` |
| 0x3A845CC | 0x2EB1B84 |  | `public GameObject Uci()` |
| 0x3A84620 | 0x2EB1BD4 |  | `public void Ucw()` |
| 0x3A84628 | 0x2EB1BDC |  | `public void UcJ()` |
| 0x3A84740 | 0x2EB1BE0 |  | `public void .ctor()` |
| 0x3A84B10 | 0x2EB1EBC |  | `private static void .cctor()` |
| 0x3A84DD0 | 0x2EB2150 | 12 | `public override bool Fuk()` |
| 0x3A85198 | 0x2EB2158 |  | `protected void Ucb(int e)` |
| 0x3A856A4 | 0x2EB2160 |  | `protected static void Ucl(vd e, vo f, vt F)` |
| 0x3A857E4 | 0x2EB21F4 |  | `protected void Ucx(int e)` |
| 0x3A85970 | 0x2EB21FC |  | `protected static void UcK(vd e, vo f, vt F)` |
| 0x3A85AB0 | 0x2EB2290 |  | `protected void UcG()` |
| 0x3A85AEC | 0x2EB22CC |  | `protected static void UcP(vd e, vo f, vt F)` |
| 0x3A85C08 | 0x2EB234C | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A85D1C | 0x2EB2460 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `BuildingSocket` : Socket  
`TypeDefIndex 3151`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A86730 | 0x2EB2D2C |  | `private void OnDrawGizmos()` |
| 0x3A869EC | 0x2EB2D30 |  | `private void OnDrawGizmosSelected()` |
| 0x3A86A58 | 0x2EB2D34 |  | `public void .ctor()` |

</details>

### public struct `CompatibilityRuleApplyResult`  
`TypeDefIndex 3152`

| offset | field |
|---|---|
| 0x0 | `public bool Success;` |
| 0x1 | `public bool UseDistanceLimitOverride;` |
| 0x4 | `public float DistanceLimitOverride;` |

### public class `Door` : Xb  
`TypeDefIndex 3155`

| offset | field |
|---|---|
| - | `private GameObject[] rayColliders;` |
| - | `private float rayMotionStarted;` |
| - | `private bool rayOpening;` |
| 0x80 | `private Transform[] m_Models;` |
| 0x88 | `private Collider[] m_Colliders;` |
| 0x90 | `private Vector3[] m_ClosedRotations;` |
| 0x98 | `private Vector3[] m_OpenRotations;` |
| 0xA0 | `private AnimationCurve m_AnimationCurve;` |
| 0xA8 | `private float m_AnimationTime;` |
| 0xAC | `private float m_InteractionThreeshold;` |
| 0xB0 | `private SoundPlayer m_DoorOpen;` |
| 0xB8 | `private SoundPlayer m_DoorClose;` |
| 0xC0 | `private BuildingPiece m_Piece;` |
| 0xC8 | `private bool m_AutoClose;` |
| 0xCC | `private float m_AutoCloseTime;` |
| 0xD0 | `private bool OSf;` |
| 0xD4 | `private float OSF;` |
| 0xD8 | `private Quaternion[] OSd;` |
| 0xE0 | `private int OSc;` |
| 0xE4 | `public bool opened;` |

Properties: `public bool RayOpening { get; }`; `public float RayProgress { get; }`; `public bool sMK { get; }`; `public bool sMG { get; set; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EB2E9C |  | `public bool get_RayOpening()` |
| - | 0x2EB2ED4 |  | `public float get_RayProgress()` |
| 0x3A86EA4 | 0x2EB2F1C |  | `public bool get_sMK()` |
| 0x3A87628 | 0x2EB2F24 |  | `public bool get_sMG()` |
| 0x3A873E8 | 0x2EB2F2C |  | `public void set_sMG([In] bool value)` |
| 0x3A86EAC | 0x2EB2F38 |  | `private void Awake()` |
| 0x3A86FC8 | 0x2EB3100 | 11 | `public override void Fsv()` |
| 0x3A87254 | 0x2EB3270 | 26 | `public override void FqM(PlayerManager e)` |
| 0x3A87284 | 0x2EB329C |  | `private IEnumerator UcI(bool e)` |
| 0x3A8732C | 0x2EB3344 |  | `private void Interact()` |
| 0x3A874A4 | 0x2EB33EC |  | `public void UcM(bool e)` |
| 0x3A875C8 | 0x2EB33F0 |  | `public void .ctor()` |
| 0x3A87620 | 0x2EB3454 | 12 | `public override bool Fuk()` |
| 0x3A87630 | 0x2EB345C |  | `protected void UUF(bool e)` |
| 0x3A876B8 | 0x2EB34E0 |  | `protected static void UUd(vd e, vo f, vt F)` |
| 0x3A877F4 | 0x2EB3574 |  | `private static void .cctor()` |
| 0x3A87920 | 0x2EB365C | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A87980 | 0x2EB36BC | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `InteractableColorSkin` : SkinData  
`TypeDefIndex 3156`

| offset | field |
|---|---|
| 0x30 | `public AssetReference materialRef;` |
| - | `public CosmicPropVariant propVariant;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A8809C | 0x2EB3DD0 | 4 | `public override QT dxJ(QT e, int f = 0)` |
| 0x3A8835C | 0x2EB4114 |  | `public void .ctor()` |

</details>

### public class `PlayerBuilder` : vd  
`TypeDefIndex 3157`

| offset | field |
|---|---|
| - | `private const float OSA = 5;` |
| 0x68 | `public PlayerManager player;` |
| - | `private BuildingPiece constructionUpgradeTarget;` |
| 0x70 | `private BuildingHelpers m_BuildingHelpers;` |
| 0x78 | `private AudioSource m_AudioSource;` |
| 0x80 | `private GenericShake m_PlaceShake;` |
| 0x88 | `private GameObject[] m_FoundationColliders;` |
| 0x90 | `private float OSu;` |
| 0x98 | `private ItemContainer OSk;` |
| 0xA0 | `private ItemContainer OSO;` |
| 0xA8 | `private BuildingPiece OSt;` |
| 0xB0 | `private bool OSr;` |
| 0xB8 | `private string OSN;` |
| 0xC0 | `private Lock OSq;` |

<details><summary>methods (45)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A88F00 | 0x2EB411C |  | `private void Start()` |
| 0x3A89320 | 0x2EB4584 |  | `private void UUN()` |
| 0x3A89A34 | 0x2EB4C9C |  | `private void UUq()` |
| 0x3A897E8 | 0x2EB4A70 |  | `private void UUs()` |
| 0x3A89B18 | 0x2EB4E48 |  | `private void UUC()` |
| 0x3A89C30 | 0x2EB4F8C |  | `private void UUZ(SleepingBagData[] e, float f)` |
| 0x3A895E4 | 0x2EB4870 |  | `private void UUj()` |
| 0x3A89D70 | 0x2EB4F90 |  | `private bool UUa()` |
| 0x3A89DB0 | 0x2EB4FD0 |  | `private bool UUQ()` |
| 0x3A8A5FC | 0x2EB583C |  | `public void UUH(bool e, int f, Vector3 F, Quaternion d, uint c, int U)` |
| 0x3A8A7DC | 0x2EB5B80 |  | `private void UUi(int e, int f)` |
| 0x3A8A91C | 0x2EB5B84 |  | `private void UUw(int e)` |
| 0x3A8A418 | 0x2EB55E0 |  | `public void UUJ(uint e)` |
| 0x3A8AA40 | 0x2EB5B88 |  | `private bool UUX(int e)` |
| 0x3A8AB04 | 0x2EB5C48 |  | `private bool UUT(int e)` |
| 0x3A8A53C | 0x2EB5740 |  | `private bool UUL()` |
| 0x3A8ABCC | 0x2EB5D20 |  | `private bool UUo()` |
| 0x3A8AD98 | 0x2EB5ED8 |  | `public void UUy(uint e)` |
| 0x3A8AEBC | 0x2EB61B0 |  | `private bool UUz()` |
| 0x3A8B0B0 | 0x2EB6380 |  | `public void UUh(uint e)` |
| 0x3A8B1D4 | 0x2EB64E0 |  | `private bool UUB()` |
| 0x3A8B3CC | 0x2EB66B4 |  | `public void UUm(uint e)` |
| 0x3A8B4F0 | 0x2EB6814 |  | `private bool UUR(BuildingPiece e)` |
| 0x3A8B604 | 0x2EB690C |  | `private void LateUpdate()` |
| 0x3A8B654 | 0x2EB695C |  | `public void .ctor()` |
| 0x3A8B65C | 0x2EB6964 | 12 | `public override bool Fuk()` |
| 0x3A8B664 | 0x2EB696C |  | `protected void UUb()` |
| 0x3A8B668 | 0x2EB6970 |  | `protected static void UUl(vd e, vo f, vt F)` |
| 0x3A8B7B4 | 0x2EB6974 |  | `protected void UUx(SleepingBagData[] e, float f)` |
| 0x3A8B7E8 | 0x2EB6AB0 |  | `protected static void UUK(vd e, vo f, vt F)` |
| 0x3A8B958 | 0x2EB6B54 |  | `protected void UUG(bool e, int f, Vector3 F, Quaternion d, uint c, int U)` |
| 0x3A8B95C | 0x2EB6B58 |  | `protected static void UUP(vd e, vo f, vt F)` |
| 0x3A8BB00 | 0x2EB6BAC |  | `protected void UUD(int e, int f)` |
| 0x3A8BB10 | 0x2EB6BBC |  | `protected static void UUn(vd e, vo f, vt F)` |
| 0x3A8BC64 | 0x2EB6BFC |  | `protected void UUV(int e)` |
| 0x3A8BC94 | 0x2EB6C2C |  | `protected static void UUg(vd e, vo f, vt F)` |
| 0x3A8BDCC | 0x2EB6CBC |  | `protected void UUp(uint e)` |
| 0x3A8BDD0 | 0x2EB6CC0 |  | `protected static void UUv(vd e, vo f, vt F)` |
| 0x3A8BF38 | 0x2EB6CC4 |  | `protected void UUS(uint e)` |
| 0x3A8BF3C | 0x2EB6CC8 |  | `protected static void UUI(vd e, vo f, vt F)` |
| 0x3A8C0A4 | 0x2EB6CCC |  | `protected void UUM(uint e)` |
| 0x3A8C0A8 | 0x2EB6CD0 |  | `protected static void UYe(vd e, vo f, vt F)` |
| 0x3A8C210 | 0x2EB6CD4 |  | `protected void UYf(uint e)` |
| 0x3A8C214 | 0x2EB6CD8 |  | `protected static void UYF(vd e, vo f, vt F)` |
| 0x3A8C37C | 0x2EB6CDC |  | `private static void .cctor()` |

</details>

### public class `Socket` : MonoBehaviour  
`TypeDefIndex 3161`

| offset | field |
|---|---|
| 0x20 | `public BuildingPiece Piece;` |
| 0x28 | `private List<Socket.PieceOffset> m_PieceOffsets;` |
| 0x30 | `private float m_Radius;` |
| 0x38 | `private List<yA> OSZ;` |
| 0x40 | `private List<Socket.ys> OSj;` |
| 0x48 | `public bool male;` |
| 0x49 | `public bool maleDummy;` |
| 0x4A | `public bool female;` |
| 0x4B | `public bool femaleDummy;` |
| 0x4C | `public bool monogamous;` |
| 0x50 | `public Vector3 position;` |
| 0x5C | `public Quaternion rotation;` |
| 0x6C | `public Vector3 selectSize;` |
| 0x78 | `public Vector3 selectCenter;` |
| 0x84 | `public Socket.yC socketType;` |
| 0x88 | `public float support;` |
| 0x8C | `public int index;` |
| 0x0 | `private static readonly List<yO> OSa;` |

Properties: `public List<yA> sMg { get; }`; `public List<Socket.PieceOffset> sMp { get; }`; `public float sMv { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EB6EAC |  | `public List<yA> get_sMg()` |
| - | 0x2EB6EB4 |  | `public List<Socket.PieceOffset> get_sMp()` |
| - | 0x2EB6EBC |  | `public float get_sMv()` |
| 0x3A8C820 | 0x2EB6EC4 |  | `private void Awake()` |
| 0x3A8C89C | 0x2EB6F40 |  | `public void UYa(BuildingPiece e)` |
| 0x3A824FC | 0x2EAF1B4 |  | `public bool UYQ(string e, out Socket.PieceOffset f)` |
| 0x3A8CA2C | 0x2EB70D0 |  | `public void UYH(yA[] e, BuildingPiece f)` |
| 0x3A82398 | 0x2EAF050 |  | `public bool UYi(BuildingPiece e)` |
| 0x3A8CC5C | 0x2EB7300 |  | `private bool UYw(Socket e, out CompatibilityRuleApplyResult f)` |
| 0x3A888A0 | 0x2EB74F8 |  | `public bool UYJ(Vector3 e, Quaternion f, Socket F, Vector3 d, Quaternion c)` |
| 0x3A8CE54 | 0x2EB75CC |  | `private void OnDrawGizmosSelected()` |
| 0x3A86AAC | 0x2EB2D88 |  | `public void .ctor()` |
| - | 0x2EB761C |  | `private static void .cctor()` |

</details>

### public class `StabilityPoint`  
`TypeDefIndex 3162`

| offset | field |
|---|---|
| 0x10 | `private string m_Name;` |
| 0x18 | `private Vector3 m_Position;` |
| 0x24 | `private Vector3 m_Direction;` |
| 0x30 | `private float m_Distance;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A8D140 | 0x2EB7844 |  | `public StabilityPoint UYX()` |
| 0x3A8D1C0 | 0x2EB78C4 |  | `public bool UYT(BuildingPiece e, LayerMask f)` |
| 0x3A8D380 | 0x2EB7A84 |  | `public void UYL(BuildingPiece e)` |
| 0x3A8D530 | 0x2EB7C34 |  | `public void .ctor()` |

</details>

### public class `StabilitySocket` : Socket  
`TypeDefIndex 3163`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A8D59C | 0x2EB7CA0 |  | `public void .ctor()` |

</details>

### public static class `WallPlacementJoint`  
`TypeDefIndex 3164`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EB7CF4 |  | `private static bool Wall(BuildingPiece piece)` |
| - | 0x2EACBDC |  | `public static bool IsCorner(BuildingPiece preview, Collider obstacle)` |

</details>
