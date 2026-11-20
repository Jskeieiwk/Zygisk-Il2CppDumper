# namespace `Oxide`  (142 types)

### public sealed class `AddressableSurfaceDatabase` : BaseSurfaceDatabase  
`TypeDefIndex 2741`

| offset | field |
|---|---|
| 0x18 | `private SurfaceDatabase surfaceDatabase;` |
| 0x20 | `private SurfaceMap _surfaceMap;` |
| 0x0 | `private static readonly Dictionary<Wm.WB, string> _splatToSurfaceMap;` |
| 0x28 | `private readonly Dictionary<string, int> _surfaceNameToIdMap;` |

Properties: `public override SurfaceData sSO { get; }`; `public override SurfaceData[] sSt { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A0F3E4 | 0x2DF138C | 4 | `public override SurfaceData get_sSO()` |
| 0x3A0F404 | 0x2DF1418 | 5 | `public override SurfaceData[] get_sSt()` |
| 0x3A0F424 | 0x2DF14A4 |  | `public void clx(SurfaceMap e, SurfaceDatabase f)` |
| 0x3A0F51C | 0x2DF14D4 |  | `public Texture clK()` |
| 0x3A0F624 | 0x2DF14DC | 6 | `protected override Texture clG(Collider e, Vector3 f)` |
| 0x3A0F9E4 | 0x2DF1A34 |  | `public void .ctor()` |
| 0x3A0F8B8 | 0x2DF1A44 |  | `private int clP(float[] e)` |

</details>

### public class `AmbienceController` : MonoBehaviour  
`TypeDefIndex 2742`

| offset | field |
|---|---|
| 0x20 | `private AudioSource m_DayAudioSrc;` |
| 0x28 | `private AudioSource m_NightAudioSrc;` |
| 0x30 | `private AnimationCurve m_DayVolCurve;` |
| 0x38 | `private float m_DayVolFactor;` |
| 0x40 | `private AnimationCurve m_NightVolCurve;` |
| 0x48 | `private float m_NightVolFactor;` |
| 0x50 | `private At TODSky;` |
| 0x58 | `private float Oml;` |
| - | `public const string VolumeKey = "ambience_sounds";` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E0284 | 0x2DF1A4C |  | `private void Start()` |
| - | 0x2DF1C90 |  | `public void ApplyVolume(float volume)` |
| 0x39E03A8 | 0x2DF1DD8 |  | `private void Update()` |
| 0x39E0478 | 0x2DF1F60 |  | `public void .ctor()` |

</details>

### public class `AnimalVitals` : EntityVitals  
`TypeDefIndex 2743`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DCCDC | 0x2DF1F68 |  | `public void cHI(float e)` |
| 0x39DCE08 | 0x2DF1F6C |  | `public void cHM(float e)` |
| 0x39DCF34 | 0x2DF1F70 |  | `public void .ctor()` |
| 0x39DCF8C | 0x2DF1FE8 | 12 | `public override bool Fuk()` |
| 0x39DCF94 | 0x2DF1FF0 |  | `protected void cie(float e)` |
| 0x39DD144 | 0x2DF20C4 |  | `protected static void cif(vd e, vo f, vt F)` |
| 0x39DD27C | 0x2DF2154 |  | `protected void ciF(float e)` |
| 0x39DD2E4 | 0x2DF21BC |  | `protected static void cid(vd e, vo f, vt F)` |
| 0x39DD41C | 0x2DF224C |  | `private static void .cctor()` |

</details>

### public class `Anvil` : Xb, Xa  
`TypeDefIndex 2745`

| offset | field |
|---|---|
| - | `private const float Ola = 0.1;` |
| 0x98 | `public RequiredRepairItem[] RequiredItems;` |
| - | `0 - the requirements will be very low.")]` |
| - | `private const float Olw = 0.7;` |
| 0xA0 | `private AudioSource m_AudioSource;` |
| 0xA8 | `private SoundPlayer m_RepairAudio;` |
| 0xB0 | `private WaitForSeconds OlJ;` |
| 0xB8 | `private ItemContainer OlX;` |
| 0xC0 | `public float progress;` |
| 0xC4 | `public bool hasItem;` |
| 0xC5 | `public bool readyForRepair;` |

Properties: `public ItemHolder OlQ { get; set; }`; `public ItemHolder OlH { get; set; }`; `public Anvil.XB Oli { get; set; }`; `public float svi { get; set; }`

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FAF64 | 0x2DF23A8 |  | `public ItemHolder get_OlQ()` |
| 0x39FAF6C | 0x2DF23B0 |  | `private void set_OlQ(ItemHolder value)` |
| 0x39FAF74 | 0x2DF23B4 |  | `public ItemHolder get_OlH()` |
| 0x39FAF7C | 0x2DF23BC |  | `private void set_OlH(ItemHolder value)` |
| 0x39FAF84 | 0x2DF23C0 |  | `public Anvil.XB get_Oli()` |
| 0x39FAF8C | 0x2DF23C8 |  | `private void set_Oli(Anvil.XB value)` |
| 0x39FB17C | 0x2DF23CC |  | `public float get_svi()` |
| 0x39FB184 | 0x2DF23D4 |  | `public void set_svi([In] float value)` |
| 0x39FAF94 | 0x2DF23D8 |  | `private void Awake()` |
| 0x39FB0C8 | 0x2DF23DC | 33 | `public override bool drE(out string e)` |
| 0x39FB0E8 | 0x2DF23FC |  | `public void .ctor()` |
| 0x39FB174 | 0x2DF2404 | 12 | `public override bool Fuk()` |
| 0x39FB23C | 0x2DF240C | 5 | `protected override void FCk(vx e, bool f)` |
| 0x39FB29C | 0x2DF2410 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `AudioUtils` : MonoBehaviour  
`TypeDefIndex 2748`

| offset | field |
|---|---|
| 0x20 | `public Xq<TE> LastGunshot;` |
| 0x28 | `private Dictionary<AudioSource, Coroutine> OKM;` |
| 0x30 | `private AudioSource m_2DAudioSource;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FDED0 | 0x2DF2480 |  | `public void cxN(AudioClip e, float f)` |
| 0x3A1107C | 0x2DF2548 |  | `public AudioSource cxq(string e, Transform f, Vector3 F, bool d, float c, float U)` |
| 0x3A112D0 | 0x2DF2550 |  | `public AudioSource cxs(string e, Transform f, Vector3 F, bool d, float c, float U, float Y)` |
| 0x3A09978 | 0x2DF2558 |  | `public AudioSource cxC(string e, Transform f, Vector3 F, bool d, float c, float U, float Y, AnimationCurve W)` |
| 0x3A05C20 | 0x2DF27A8 |  | `public void cxZ(AudioSource e, float f, float F)` |
| 0x3A11548 | 0x2DF291C |  | `private IEnumerator cxj(AudioSource e, float f, float F)` |
| 0x3A115EC | 0x2DF29E0 |  | `public void .ctor()` |

</details>

### public sealed class `BarrelBreakEffect` : MonoBehaviour  
`TypeDefIndex 2749`

| offset | field |
|---|---|
| - | `private Rigidbody[] fragments;` |
| - | `private Vector3[] scales;` |
| - | `private float started;` |
| - | `private bool settling;` |
| - | `private const float Hold = 1.1;` |
| - | `private const float Fade = 0.3;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF2C8C |  | `public void Begin()` |
| - | 0x2DF3140 |  | `private void Update()` |
| - | 0x2DF33DC |  | `public void .ctor()` |

</details>

### public abstract class `BaseSurfaceDatabase` : ScriptableObject  
`TypeDefIndex 2750`

Properties: `public abstract SurfaceData sSO { get; }`; `public abstract SurfaceData[] sSt { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract SurfaceData get_sSO();` |
| - | - |  | `public abstract SurfaceData[] get_sSt();` |
| - | - |  | `protected abstract Texture clG(Collider e, Vector3 f);` |
| 0x3A10668 | 0x2DF33E4 |  | `public int cxf(RaycastHit e)` |
| 0x3A0A3D0 | 0x2DF3A14 |  | `public SurfaceData cxF(Ray e, float f, LayerMask F)` |
| 0x3A108A0 | 0x2DF3B48 |  | `public SurfaceData cxd(Collider e, Vector3 f, int F)` |
| 0x3A106E0 | 0x2DF3D48 |  | `private int cxc(Collider e, Vector3 f, int F)` |
| 0x3A0F72C | 0x2DF3D50 |  | `protected float[] cxU(Vector3 e, TerrainData f, Vector3 F)` |
| 0x3A10AA0 | 0x2DF3664 |  | `private Texture cxY(Collider e, int f)` |
| 0x3A0FA6C | 0x2DF1A3C |  | `protected void .ctor()` |

</details>

### public class `CameraAnimator` : XY  
`TypeDefIndex 2751`

| offset | field |
|---|---|
| 0x90 | `private Animator m_Animator;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D8D04 | 0x2DF3D58 |  | `private void Awake()` |
| 0x39D8EA0 | 0x2DF3D5C |  | `private void cHe()` |
| 0x39D8F14 | 0x2DF3D60 |  | `private void cHf()` |
| 0x39D8F88 | 0x2DF3D64 |  | `public void .ctor()` |
| 0x39D8F98 | 0x2DF3D6C | 12 | `public override bool Fuk()` |

</details>

### public class `CannibalSpawner` : MonoBehaviour  
`TypeDefIndex 2754`

| offset | field |
|---|---|
| 0x20 | `private bool m_ShowGUI;` |
| 0x21 | `private bool m_EnableSpawning;` |
| 0x24 | `private int m_MaxCount;` |
| 0x28 | `private CannibalSpawner.Tw m_SpawnMode;` |
| 0x2C | `private float m_SpawnInterval;` |
| 0x30 | `private GameObject[] m_Prefabs;` |
| 0x38 | `private float OGH;` |
| 0x40 | `private GameObject[] OGi;` |
| 0x48 | `private List<XE> OGw;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A189F0 | 0x2DF3D74 |  | `private void Start()` |
| 0x3A18A5C | 0x2DF3D78 |  | `private void OnGUI()` |
| 0x3A18DEC | 0x2DF3D7C |  | `private void RecoveredNoopUpdate()` |
| 0x3A18F28 | 0x2DF3D80 |  | `private void Spawn()` |
| 0x3A19278 | 0x2DF3D84 |  | `private void cKX(XE e)` |
| 0x3A192D0 | 0x2DF3D88 |  | `public void .ctor()` |

</details>

### public class `ClampAttribute` : PropertyAttribute  
`TypeDefIndex 2755`

| offset | field |
|---|---|
| 0x10 | `public readonly Vector2 ClampLimits;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D88C4 | 0x2DF3DA4 |  | `public void .ctor(float min, float max)` |

</details>

### public class `CostItem`  
`TypeDefIndex 2756`

| offset | field |
|---|---|
| 0x10 | `private string m_Name;` |
| 0x18 | `private float m_Amount;` |

Properties: `public string spH { get; set; }`; `public float spi { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E8580 | 0x2DF3DAC |  | `public string get_spH()` |
| 0x39E8588 | 0x2DF3DB4 |  | `public void set_spH(string value)` |
| 0x39E8590 | 0x2DF3DB8 |  | `public float get_spi()` |
| 0x39E8598 | 0x2DF3DC0 |  | `public void set_spi(float value)` |
| 0x39E853C | 0x2DF3DC4 |  | `public void .ctor(string nm, float amt)` |

</details>

### public class `Cupboard` : Xb, Xa  
`TypeDefIndex 2757`

| offset | field |
|---|---|
| 0x80 | `public ItemContainer inventory;` |
| 0x88 | `public bool isLootable;` |
| 0x98 | `protected int m_Capacity;` |
| 0xA0 | `private string panelName;` |
| 0xA8 | `private BuildingPiece m_Piece;` |
| 0xB0 | `private GameObject m_LootBag;` |
| 0xB8 | `private List<CostItem> OlP;` |
| 0x0 | `public static UT<Cupboard> cupboards;` |
| 0xC0 | `public float protectedTime;` |
| 0xC4 | `public int costItemLogs;` |
| 0xC8 | `public int costItemStones;` |
| 0xCC | `public int costItemMetal;` |
| 0xD0 | `public int costItemHQM;` |
| 0xD4 | `public bool isSubscribed;` |

Properties: `public BuildingPiece svw { get; }`; `public ItemHolder[] OlG { get; set; }`; `public float svJ { get; }`; `public int svX { get; }`; `public int svT { get; }`; `public int svL { get; }`; `public int svo { get; }`; `public bool svy { get; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FC7F4 | 0x2DF3DCC |  | `public BuildingPiece get_svw()` |
| 0x39FC7FC | 0x2DF3DD4 |  | `public ItemHolder[] get_OlG()` |
| 0x39FC804 | 0x2DF3DDC |  | `private void set_OlG(ItemHolder[] value)` |
| - | 0x2DF3DE0 |  | `public float get_svJ()` |
| - | 0x2DF3DE8 |  | `public int get_svX()` |
| - | 0x2DF3DF0 |  | `public int get_svT()` |
| - | 0x2DF3DF8 |  | `public int get_svL()` |
| - | 0x2DF3E00 |  | `public int get_svo()` |
| - | 0x2DF3E08 |  | `public bool get_svy()` |
| 0x39FC80C | 0x2DF3E10 |  | `private void Awake()` |
| 0x39FC93C | 0x2DF3E14 | 33 | `public override bool drE(out string e)` |
| 0x39FC95C | 0x2DF3E34 |  | `private List<Xj.Value> cBG(List<Xj.Value> e, string f, float F)` |
| 0x39FCCA4 | 0x2DF3E3C |  | `private Xj.Value cBP(List<Xj.Value> e, string f)` |
| 0x39FCD6C | 0x2DF3E44 |  | `public void .ctor()` |
| 0x39FCED0 | 0x2DF3E4C | 12 | `public override bool Fuk()` |
| 0x39FD35C | 0x2DF3E54 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x39FD49C | 0x2DF3E58 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public sealed class `CustomCharacterController` : BaseFirstPersonController  
`TypeDefIndex 2760`

| offset | field |
|---|---|
| 0x14C | `private float _walkSpeed;` |
| 0x150 | `private float _runSpeed;` |
| 0x158 | `private CapsuleCollider _collider;` |
| 0x160 | `public jc state;` |
| 0x164 | `private CollisionFlags OKf;` |
| 0x168 | `private float OKF;` |
| 0x16C | `private bool OKd;` |
| 0x170 | `private float OKc;` |
| 0x174 | `private CustomCharacterController.Xp OKU;` |
| 0x178 | `private CustomCharacterController.MoveData OKY;` |
| 0x1A4 | `private float OKW;` |

Properties: `public float sSf { get; set; }`; `public float sSF { get; set; }`; `public bool OKE { get; set; }`

<details><summary>methods (28)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A074D4 | 0x2DF3F34 |  | `public float get_sSf()` |
| 0x3A074DC | 0x2DF3F3C |  | `public void set_sSf(float value)` |
| 0x3A074EC | 0x2DF3F40 |  | `public float get_sSF()` |
| 0x3A074F4 | 0x2DF3F48 |  | `public void set_sSF(float value)` |
| 0x3A07504 | 0x2DF3F4C |  | `public bool get_OKE()` |
| 0x3A0750C | 0x2DF3F54 |  | `private void set_OKE(bool value)` |
| 0x3A073C0 | 0x2DF3F58 | 27 | `public override void Awake()` |
| 0x3A07518 | 0x2DF3F5C | 29 | `public override void Update()` |
| 0x3A07DEC | 0x2DF3F60 |  | `private float cbs()` |
| 0x3A07E08 | 0x2DF3F68 | 22 | `protected override Vector3 Fxw()` |
| 0x3A07E40 | 0x2DF3F78 | 24 | `protected override void Fxa()` |
| 0x3A07C60 | 0x2DF3F7C |  | `private void cbC(CustomCharacterController.MoveData e)` |
| 0x3A080DC | 0x2DF3F80 | 26 | `protected override void FxQ()` |
| 0x3A07B20 | 0x2DF3F84 |  | `private void cbZ(CustomCharacterController.MoveData e)` |
| 0x3A081BC | 0x2DF3F88 |  | `private void cbj(CustomCharacterController.MoveData e)` |
| 0x3A082FC | 0x2DF3F8C |  | `public float cba()` |
| 0x3A08314 | 0x2DF3F94 |  | `public bool cbQ()` |
| 0x3A0831C | 0x2DF3F9C |  | `public bool cbH()` |
| 0x3A08324 | 0x2DF3FA4 |  | `public float cbi()` |
| 0x3A08340 | 0x2DF3FAC |  | `public float cbw()` |
| 0x3A0835C | 0x2DF3FB4 |  | `public float cbJ()` |
| 0x3A08364 | 0x2DF3FBC |  | `public void .ctor()` |
| 0x3A08384 | 0x2DF3FC4 | 12 | `public override bool Fuk()` |
| 0x3A0838C | 0x2DF3FCC |  | `protected void cbX(CustomCharacterController.MoveData e)` |
| 0x3A083D4 | 0x2DF3FD0 |  | `protected static void cbT(vd e, vo f, vt F)` |
| 0x3A08584 | 0x2DF3FD4 |  | `protected void cbL(CustomCharacterController.MoveData e)` |
| 0x3A085A4 | 0x2DF3FD8 |  | `protected static void cbo(vd e, vo f, vt F)` |
| 0x3A086FC | 0x2DF3FDC |  | `private static void .cctor()` |

</details>

### public class `DamageArea` : MonoBehaviour  
`TypeDefIndex 2761`

| offset | field |
|---|---|
| 0x20 | `private float m_DamagePerSecond;` |
| 0x24 | `private Lf.Le m_DamageType;` |
| 0x28 | `private List<XE> OmZ;` |
| 0x30 | `private Coroutine Omj;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DD5B4 | 0x2DF3FF0 |  | `public void .ctor()` |

</details>

### public sealed class `DragAction` : MulticastDelegate  
`TypeDefIndex 2762`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF3FF8 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2DF4104 |  | `public virtual void Invoke(PointerEventData data, Slot slot, ItemContainer collection)` |
| - | 0x2DF4118 |  | `public virtual IAsyncResult BeginInvoke(PointerEventData data, Slot slot, ItemContainer collection, AsyncCallback callback, object object)` |
| - | 0x2DF4144 |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public sealed class `DropAction` : MulticastDelegate  
`TypeDefIndex 2763`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF4150 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2DF425C |  | `public virtual void Invoke(ItemContainer initialCollection, Slot initialSlot, Item item)` |
| - | 0x2DF4270 |  | `public virtual IAsyncResult BeginInvoke(ItemContainer initialCollection, Slot initialSlot, Item item, AsyncCallback callback, object object)` |
| - | 0x2DF429C |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public class `EntityDeathHandler` : XU  
`TypeDefIndex 2764`

| offset | field |
|---|---|
| 0x88 | `private AudioSource m_AudioSource;` |
| 0x90 | `private SoundPlayer m_DeathAudio;` |
| 0x98 | `private SoundPlayer m_HitAudio;` |
| 0xA0 | `private SoundPlayer m_CriticalHitAudio;` |
| 0xA8 | `private Collider[] m_CollidersToEnable;` |
| 0xB0 | `private GameObject[] m_ObjectsToDisable;` |
| 0xB8 | `private Behaviour[] m_BehavioursToDisable;` |
| 0xC0 | `private Collider[] m_CollidersToDisable;` |
| 0xC8 | `private bool m_EnableRagdoll;` |
| 0xD0 | `private Ragdoll m_Ragdoll;` |
| 0xD8 | `private bool m_EnableDeathAnim;` |
| 0xE0 | `private Animator m_Animator;` |
| 0xE8 | `private GameObject m_DestroyedObject;` |
| 0xF0 | `private bool m_DestroyOnDeath;` |
| 0xF4 | `private float m_DestroyTimer;` |
| 0xF8 | `public bool notifyHit;` |
| 0x100 | `public BuildingPiece piece;` |
| 0x108 | `public bool death;` |
| 0x10C | `private Vector3 OKA;` |
| 0x118 | `private Quaternion OKu;` |
| - | `private bool deathEffectPlayed;` |
| - | `private readonly Dictionary<Renderer, bool> lootRenderers;` |
| - | `private readonly Dictionary<Collider, bool> lootColliders;` |
| - | `private readonly Dictionary<Renderer, bool> constructionRenderers;` |
| - | `private readonly Dictionary<Collider, bool> constructionColliders;` |
| - | `private Action OKk_;` |

Properties: `public bool sSd { get; set; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF42A8 |  | `private void HideConstructionVisual(GameObject visual)` |
| - | 0x2DF456C |  | `private void RestoreConstructionVisual()` |
| - | 0x2DF48DC |  | `private void HideDeadConstructionIfPresent()` |
| - | 0x2DF4A00 |  | `private void ApplyLootDeathState()` |
| 0x3A08E94 | 0x2DF5064 |  | `public bool get_sSd()` |
| 0x3A08E9C | 0x2DF506C |  | `public void set_sSd([In] bool value)` |
| 0x3A08898 | 0x2DF5070 |  | `public void add_OKk(Action value)` |
| 0x3A08938 | 0x2DF5104 |  | `public void remove_OKk(Action value)` |
| 0x3A089D8 | 0x2DF5198 |  | `private void Awake()` |
| 0x3A08AB4 | 0x2DF5258 |  | `public void cbh()` |
| 0x3A08BCC | 0x2DF525C |  | `private void OnEnable()` |
| 0x3A08DFC | 0x2DF55C0 |  | `public void cbB(bool e)` |
| 0x3A08E60 | 0x2DF5620 |  | `private bool cbm(Lf.Le e)` |
| 0x3A08E84 | 0x2DF563C |  | `public void .ctor()` |
| 0x3A08E8C | 0x2DF5760 | 12 | `public override bool Fuk()` |
| 0x3A08F58 | 0x2DF5768 |  | `protected void cbl()` |
| 0x3A092F4 | 0x2DF5F1C |  | `protected static void cbx(vd e, vo f, vt F)` |
| 0x3A09410 | 0x2DF5F9C |  | `private static void .cctor()` |
| 0x3A0953C | 0x2DF6084 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A0959C | 0x2DF60E4 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `EntityVitals` : GenericVitals  
`TypeDefIndex 2765`

| offset | field |
|---|---|
| 0xB0 | `protected float m_MinFallSpeed;` |
| 0xB4 | `protected float m_MaxFallSpeed;` |
| 0xB8 | `public SoundPlayer m_HurtAudio;` |
| 0xC0 | `public float m_TimeBetweenScreams;` |
| 0xC8 | `public SoundPlayer m_FallDamageAudio;` |
| 0xD0 | `public Animator m_Animator;` |
| 0xD8 | `public float m_GetHitMax;` |
| 0xDC | `public float m_NextTimeCanScream;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DD5C4 | 0x2DF6290 |  | `private void Awake()` |
| 0x39DD700 | 0x2DF63CC | 19 | `protected virtual void cic()` |
| 0x39DD7AC | 0x2DF6478 |  | `private void ciU(float e)` |
| 0x39DCF60 | 0x2DF1FAC |  | `public void .ctor()` |
| 0x39DD8D8 | 0x2DF6598 | 12 | `public override bool Fuk()` |

</details>

### public class `EquipmentPiece`  
`TypeDefIndex 2766`

| offset | field |
|---|---|
| 0x18 | `private string m_ItemName;` |
| 0x20 | `private GameObject m_Object;` |
| 0x28 | `private GameObject m_ObjectThirdPerson;` |
| 0x30 | `private Dictionary<GameObject, HashSet<GameObject>> OPF;` |
| 0x38 | `private Renderer[] m_Renderers;` |

Properties: `public ItemHolder OPf { get; set; }`; `public string sSL { get; }`; `public GameObject sSo { get; }`; `public Renderer[] sSy { get; }`; `public Dictionary<GameObject, HashSet<GameObject>> sSz { get; }`; `public GameObject sSh { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1EE4C | 0x2DF65A0 |  | `public ItemHolder get_OPf()` |
| 0x3A1EE54 | 0x2DF65A8 |  | `public void set_OPf(ItemHolder value)` |
| 0x3A1EE5C | 0x2DF65AC |  | `public string get_sSL()` |
| 0x3A1EE64 | 0x2DF65B4 |  | `public GameObject get_sSo()` |
| 0x3A1EE6C | 0x2DF65BC |  | `public Renderer[] get_sSy()` |
| 0x3A1EE74 | 0x2DF65C4 |  | `public Dictionary<GameObject, HashSet<GameObject>> get_sSz()` |
| 0x3A1EE7C | 0x2DF65CC |  | `public GameObject get_sSh()` |
| 0x3A1EE84 | 0x2DF65D4 |  | `public void .ctor()` |

</details>

### public struct `EquipPiece`  
`TypeDefIndex 2767`

| offset | field |
|---|---|
| 0x0 | `public bool Enabled;` |
| 0x4 | `public int Skin;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A25560 | 0x2DF65DC |  | `public void .ctor(bool e, int s)` |

</details>

### public class `Firelight` : MonoBehaviour  
`TypeDefIndex 2768`

| offset | field |
|---|---|
| 0x20 | `private float m_ToggleDuration;` |
| 0x24 | `private float m_LightIntensity;` |
| 0x28 | `private float m_LightRange;` |
| 0x2C | `private float m_IntensityNoise;` |
| 0x30 | `private Light m_Light;` |
| 0x38 | `private bool OlD;` |
| 0x39 | `private bool Oln;` |
| 0x3C | `private float OlV;` |
| 0x40 | `private float Olg;` |
| 0x44 | `private float Olp;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FD734 | 0x2DF65EC |  | `private void Update()` |
| 0x39FD860 | 0x2DF67EC |  | `public void cmc(bool e)` |
| 0x39FD8B8 | 0x2DF68FC |  | `public void .ctor()` |

</details>

### public class `FootstepPlayer` : vd  
`TypeDefIndex 2769`

| offset | field |
|---|---|
| 0x68 | `public PlayerManager player;` |
| 0x70 | `private Tc m_FootstepSelectionMethod;` |
| 0x74 | `private float m_LandSpeedThreeshold;` |
| 0x78 | `private LayerMask m_Mask;` |
| 0x80 | `private AudioSource m_AudioSource;` |
| 0x88 | `private float m_SoundRange;` |
| 0x8C | `private float m_WalkStepLength;` |
| 0x90 | `private float m_RunStepLength;` |
| 0x94 | `private float m_WalkVolumeFactor;` |
| 0x98 | `private float m_RunVolumeFactor;` |
| 0x9C | `private float m_CrouchVolumeFactor;` |
| 0xA0 | `private AnimationCurve m_SoundCurve;` |
| 0xA8 | `private AudioSource OKO;` |
| 0xB0 | `private AudioSource OKt;` |
| 0xB8 | `private Xv OKr;` |
| 0xBC | `private float OKN;` |
| - | `private Vector3 stepOrigin;` |
| - | `private bool stepOriginSet;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A09648 | 0x2DF6920 |  | `private void Start()` |
| 0x3A09C08 | 0x2DF6C04 |  | `private void FixedUpdate()` |
| 0x3A09EB4 | 0x2DF7048 |  | `private void cbK()` |
| 0x3A09E7C | 0x2DF7720 |  | `private void EnsureSources()` |
| - | 0x2DF6F68 |  | `private float cbG()` |
| 0x3A0A25C | 0x2DF7A64 |  | `private float cbP()` |
| 0x3A0A340 | 0x2DF7B3C |  | `private void cbD()` |
| 0x3A0A37C | 0x2DF7B74 |  | `private void cbn(float e)` |
| 0x3A09F24 | 0x2DF7270 |  | `private SurfaceData cbV()` |
| 0x3A0A504 | 0x2DF7BC4 |  | `public void .ctor()` |
| 0x3A0A660 | 0x2DF7BCC | 12 | `public override bool Fuk()` |

</details>

### public class `FPAnimator` : MonoBehaviour  
`TypeDefIndex 2771`

| offset | field |
|---|---|
| 0x20 | `private Animator m_Animator;` |
| 0x28 | `protected float drawClipLength;` |
| 0x2C | `protected float holsterClipLength;` |
| 0x30 | `protected FPObject ORI;` |
| 0x38 | `protected bool ORM;` |
| 0x40 | `public XA Player;` |

Properties: `public Animator spb { get; }`; `public FPObject spl { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF7BD4 |  | `public Animator get_spb()` |
| - | 0x2DF7BDC |  | `public FPObject get_spl()` |
| 0x39EE248 | 0x2DF7BE4 | 4 | `public virtual void dQU()` |
| 0x39EE4C8 | 0x2DF7E54 | 5 | `public virtual void cyc()` |
| 0x39EE4D4 | 0x2DF7E60 | 6 | `protected virtual void OnDestroy()` |
| 0x39EE63C | 0x2DF803C | 7 | `protected virtual void OnValidate()` |
| 0x39EE768 | 0x2DF8040 | 8 | `protected virtual void On_Draw()` |
| 0x39EE830 | 0x2DF80EC | 9 | `protected virtual void cyU()` |
| 0x39EE8F8 | 0x2DF8198 |  | `private void cyY()` |
| 0x39EE928 | 0x2DF81C8 |  | `private void cyW()` |
| 0x39EE958 | 0x2DF81F8 |  | `public void .ctor()` |

</details>

### public class `FPBow` : FPWeaponBase  
`TypeDefIndex 2772`

| offset | field |
|---|---|
| 0xC4 | `private LayerMask m_Mask;` |
| 0xC8 | `private float m_MaxDistance;` |
| 0xD0 | `private FPBowAnimator fpBowAnimator;` |
| 0xD8 | `private float m_MinTimeBetweenShots;` |
| 0xE0 | `public ShaftedProjectile m_ArrowPrefab;` |
| 0xE8 | `private Vector3 m_SpawnOffset;` |
| 0xF8 | `private AudioSource m_AudioSource;` |
| 0x100 | `private SoundPlayer m_ReleaseAudio;` |
| 0x108 | `private SoundPlayer m_StretchAudio;` |
| 0x110 | `private float Obe;` |
| 0x114 | `private float Obf;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39EE968 | 0x2DF8218 | 5 | `public override void Initialize()` |
| 0x39EEA78 | 0x2DF836C |  | `private void FixedUpdate()` |
| 0x39EEC18 | 0x2DF8544 | 17 | `public override bool daS(Camera e)` |
| 0x39EF0B4 | 0x2DF87B0 | 7 | `protected override void OnDestroy()` |
| 0x39EF1A8 | 0x2DF88F8 | 14 | `public override bool daM(bool e)` |
| 0x39EF278 | 0x2DF8A64 |  | `private bool cyE()` |
| 0x39EF2CC | 0x2DF8AB4 |  | `private void cyA()` |
| 0x39EEE48 | 0x2DF86E0 |  | `private void cyu(Camera e)` |
| 0x39EF2F0 | 0x2DF8AD0 |  | `private void AnimateThrow()` |
| 0x39EF344 | 0x2DF8B10 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x39EF3A8 | 0x2DF8C3C |  | `public bool cyk()` |
| 0x39EF3C8 | 0x2DF8C5C |  | `public void .ctor()` |

</details>

### public class `FPBowAnimator` : FPAnimator  
`TypeDefIndex 2773`

| offset | field |
|---|---|
| 0x48 | `private float m_ReleaseSpeed;` |
| 0x50 | `private WeaponShake m_ReleaseShake;` |
| 0x58 | `private Vector3 m_NoAmmoPosition;` |
| 0x64 | `private Vector3 m_NoAmmoRotation;` |
| 0x70 | `public GameObject arrowPrefab;` |
| 0x78 | `private FPBow ObF;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39EF3E0 | 0x2DF8C64 | 4 | `public override void dQU()` |
| 0x39EF204 | 0x2DF89A8 |  | `public void Reload()` |
| 0x39EF670 | 0x2DF8FA8 |  | `private void On_Reload()` |
| 0x39EF6D0 | 0x2DF9084 | 6 | `protected override void OnDestroy()` |
| 0x39EF850 | 0x2DF9238 | 7 | `protected override void OnValidate()` |
| 0x39EF944 | 0x2DF923C |  | `private void cyO()` |
| 0x39EF9D4 | 0x2DF930C |  | `private void cyt()` |
| 0x39EFA64 | 0x2DF93DC |  | `private void cyr()` |
| 0x39EFB18 | 0x2DF94E8 |  | `public void .ctor()` |

</details>

### public class `FPBuildingHammer` : FPMelee  
`TypeDefIndex 2774`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39EFB30 | 0x2DF9508 | 20 | `protected override void On_Hit(XR raycastData)` |
| 0x39EFCA0 | 0x2DF9510 |  | `private void cyN(XR e)` |
| 0x39F0B74 | 0x2DF9514 |  | `public void .ctor()` |

</details>

### public class `FPCameraController` : Lc<FPCameraController>  
`TypeDefIndex 2775`

| offset | field |
|---|---|
| 0x20 | `private Vector3 m_DefaultPosInfluence;` |
| 0x2C | `private Vector3 m_DefaultRotInfluence;` |
| 0x38 | `private XA m_Player;` |
| 0x40 | `private TrigonometricBob m_WalkHeadbob;` |
| 0x48 | `private TrigonometricBob m_RunHeadbob;` |
| 0x50 | `private GenericShake m_DamageShake;` |
| 0x58 | `private WeaponShake m_LandShake;` |
| 0x60 | `private float m_LandThreeshold;` |
| 0x64 | `private Vector3 OBy;` |
| 0x70 | `private Vector3 OBz;` |
| 0x7C | `private Vector3 OBh;` |
| 0x88 | `private Vector3 OBm;` |
| 0x98 | `private List<Jv> OBR;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D9538 | 0x2DF951C |  | `public Jv cHA(Jv e)` |
| 0x39D95E8 | 0x2DF95CC |  | `public Jv cHu(float e, float f, float F, float d)` |
| 0x39D9724 | 0x2DF95D4 |  | `public Jv cHk(float e, float f, float F, float d, Vector3 c, Vector3 U)` |
| 0x39D9858 | 0x2DF95DC |  | `public Jv cHO(float e, float f, float F)` |
| 0x39D9A2C | 0x2DF95E4 |  | `public Jv cHt(float e, float f, float F, Vector3 d, Vector3 c)` |
| 0x39D9B6C | 0x2DF95EC |  | `private void Awake()` |
| 0x39D9C10 | 0x2DF9690 |  | `private void cHr(Xf e)` |
| 0x39D9CD0 | 0x2DF9694 |  | `private void cHN(float e)` |
| 0x39D9D60 | 0x2DF9698 |  | `private void LateUpdate()` |
| 0x39DA26C | 0x2DF99FC |  | `public void .ctor()` |

</details>

### public class `FPChargeAnimator` : FPAnimator  
`TypeDefIndex 2777`

| offset | field |
|---|---|
| 0x48 | `private float m_ThrowSpeed;` |
| 0x50 | `private WeaponShake m_ThrowShake;` |
| 0x58 | `private FPExplosiveCharge Obd;` |
| - | `private bool throwPose;` |
| - | `private Coroutine pose;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F0C4C | 0x2DF9B10 | 4 | `public override void dQU()` |
| 0x39F0E38 | 0x2DF9C2C | 8 | `protected override void On_Draw()` |
| 0x39F0F08 | 0x2DF9DBC | 9 | `protected override void cyU()` |
| - | 0x2DF9E78 |  | `private void OnDisable()` |
| - | 0x2DF9E9C |  | `protected override void OnDestroy()` |
| - | 0x2DF9D08 |  | `private void PoseTo(Vector3 from, Vector3 to, float duration, bool snapFrom)` |
| - | 0x2DF9F6C |  | `private IEnumerator PoseRoutine(Vector3 from, Vector3 to, float duration, bool snapFrom)` |
| 0x39F0FB4 | 0x2DFA060 |  | `private void cyq()` |
| 0x39F1054 | 0x2DFA130 |  | `public void .ctor()` |

</details>

### public class `FPExplosiveCharge` : FPWeaponBase  
`TypeDefIndex 2779`

| offset | field |
|---|---|
| 0xC4 | `private LayerMask m_Mask;` |
| 0xC8 | `private float m_MaxDistance;` |
| 0xCC | `private float m_MinTimeBetweenThrows;` |
| 0xD0 | `public ShaftedProjectile m_ChargePrefab;` |
| 0xD8 | `private Vector3 m_SpawnOffset;` |
| 0xE4 | `private float m_SpawnDelay;` |
| 0xE8 | `private AudioSource m_AudioSource;` |
| 0xF0 | `private SoundPlayer m_ThrowAudio;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F106C | 0x2DFA458 | 5 | `public override void Initialize()` |
| 0x39F1080 | 0x2DFA478 |  | `private void FixedUpdate()` |
| 0x39F10D0 | 0x2DFA480 | 17 | `public override bool daS(Camera e)` |
| 0x39F1304 | 0x2DFA5F8 |  | `private IEnumerator cya(Camera e, float f)` |
| 0x39F13C4 | 0x2DFA61C |  | `private void AnimateThrow()` |
| 0x39F1400 | 0x2DFA664 | 10 | `public override void dQd()` |
| - | 0x2DFA6BC |  | `public override void On_Draw(Item correspondingItem)` |
| 0x39F1430 | 0x2DFA764 |  | `public void .ctor()` |

</details>

### public class `FPHitscan` : FPWeaponBase  
`TypeDefIndex 2782`

| offset | field |
|---|---|
| 0xC8 | `private HitscanWeaponConfig config;` |
| 0xD0 | `private Lf.Tp m_FireMode;` |
| 0xD4 | `private LayerMask m_Mask;` |
| 0xD8 | `private float m_FireDuration;` |
| 0xDC | `private int m_BurstLength;` |
| 0xE0 | `private float m_BurstDuration;` |
| 0xE4 | `private float m_BurstPause;` |
| 0xE8 | `private AudioSource m_AudioSource;` |
| 0xF0 | `private SoundPlayer m_FireAudio;` |
| 0xF8 | `private SoundPlayer triggerAudio;` |
| 0x100 | `private SoundPlayer m_ReloadAudio;` |
| 0x108 | `private ParticleSystem m_MuzzleFlash;` |
| 0x110 | `private GameObject m_Tracer;` |
| 0x118 | `private Vector3 m_TracerOffset;` |
| 0x128 | `private Rigidbody m_ShellPrefab;` |
| 0x130 | `private FPHitscan.XJ m_ShellSpawnMethod;` |
| 0x138 | `private FPHitscanEventHandler m_AnimEventHandler;` |
| 0x140 | `private Transform m_WeaponRoot;` |
| 0x148 | `private Vector3 m_ShellSpawnOffset;` |
| 0x154 | `private Vector3 m_ShellSpawnVelocity;` |
| 0x160 | `private float m_ShellSpin;` |
| 0x168 | `private FPHitscanAnimator hitscanAnimator;` |
| 0x170 | `private WaitForSeconds Obq;` |
| 0x178 | `private qg Obs;` |
| 0x180 | `private qV ObC;` |
| 0x188 | `private bool ObZ;` |
| 0x18C | `private float Obj;` |

Properties: `public LayerMask spD { get; }`; `public float spn { get; }`; `public int spV { get; }`; `public qV spg { get; }`; `public int ReloadLoops { get; }`; `public float ReloadDuration { get; }`

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F17B8 | 0x2DFA794 |  | `public LayerMask get_spD()` |
| 0x39F17C0 | 0x2DFA79C |  | `public float get_spn()` |
| 0x39F1868 | 0x2DFA7A4 |  | `public int get_spV()` |
| 0x39F17DC | 0x2DFA7AC |  | `public qV get_spg()` |
| 0x39F1884 | 0x2DFA7B4 | 5 | `public override void Initialize()` |
| 0x39F1A70 | 0x2DFA8C8 |  | `private void FixedUpdate()` |
| 0x39F1CA8 | 0x2DFAC10 | 17 | `public override bool daS(Camera e)` |
| 0x39F1FC8 | 0x2DFADFC | 18 | `public override bool cyo(Camera e)` |
| - | 0x2DFAE6C |  | `public int get_ReloadLoops()` |
| - | 0x2DFAF04 |  | `public float get_ReloadDuration()` |
| - | 0x2DFAF0C |  | `protected IEnumerator cyy(Camera e)` |
| 0x39F1DF8 | 0x2DFACD0 |  | `protected void cyz(Camera e)` |
| - | 0x2DFBBF4 |  | `public void SpectatorFire()` |
| - | 0x2DFBCC0 |  | `public void SpectatorReload()` |
| 0x39F204C | 0x2DFAF14 |  | `protected void cyh(Camera e)` |
| - | 0x2DFAAE0 |  | `private void DecaySpread()` |
| - | 0x2DFBE78 |  | `private void Bloom()` |
| - | 0x2DFBD54 |  | `private static Vector3 Deflect(Vector3 forward, float degrees)` |
| 0x39F3134 | 0x2DFBF14 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x39F3174 | 0x2DFBF1C | 11 | `public override void dQd()` |
| 0x39F31D8 | 0x2DFBF24 | 14 | `public override bool daM(bool e)` |
| 0x39F1C40 | 0x2DFAB84 |  | `private float cyB()` |
| 0x39F330C | 0x2DFC198 | 7 | `protected override void OnDestroy()` |
| 0x39F3404 | 0x2DFC19C |  | `private void cym(string e)` |
| 0x39F3490 | 0x2DFC1A0 |  | `private void cyR()` |
| 0x39F364C | 0x2DFC1A4 |  | `public void .ctor()` |

</details>

### public class `FPHitscanAnimator` : FPAnimator  
`TypeDefIndex 2783`

| offset | field |
|---|---|
| 0x48 | `private float m_FireSpeed;` |
| 0x4C | `private int m_FireTypesCount;` |
| 0x50 | `private WeaponShake m_FireShake;` |
| 0x58 | `private FPHitscan Oba;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F375C | 0x2DFC1D4 | 4 | `public override void dQU()` |
| 0x39F3268 | 0x2DFC044 |  | `public void Reload()` |
| 0x39F39B0 | 0x2DFC4D0 |  | `private void OnDestroy()` |
| 0x39F3B30 | 0x2DFC67C | 7 | `protected override void OnValidate()` |
| 0x39F3C24 | 0x2DFC680 |  | `private void cyb()` |
| 0x39F3CB8 | 0x2DFC758 |  | `private void cyl()` |
| 0x39F3D4C | 0x2DFC878 |  | `public void PlayFire()` |
| - | 0x2DFC87C |  | `private void cyx()` |
| 0x39F3E08 | 0x2DFC964 |  | `public void .ctor()` |

</details>

### public class `FPHitscanEventHandler` : MonoBehaviour  
`TypeDefIndex 2784`

| offset | field |
|---|---|
| 0x20 | `public XN<string> AnimEvent_SpawnObject;` |
| 0x28 | `private AudioSource m_AudioSource;` |
| 0x30 | `private float m_Volume;` |
| 0x38 | `private AudioClip[] m_Sounds;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F3E24 | 0x2DFC984 |  | `public void PlaySound(int index)` |
| 0x39F3EF0 | 0x2DFC988 |  | `public void SpawnObject(string name)` |
| 0x39F3F48 | 0x2DFC98C |  | `public void .ctor()` |

</details>

### public class `FPManager` : MonoBehaviour  
`TypeDefIndex 2792`

| offset | field |
|---|---|
| 0x20 | `public Camera m_WorldCamera;` |
| - | `private PlayerEquipmentResources equipmentResources;` |
| 0x28 | `private Camera m_FPCamera;` |
| 0x30 | `private float m_NormalFOV;` |
| 0x34 | `private float m_AimFOV;` |
| 0x38 | `private float m_FOVSetSpeed;` |
| 0x3C | `private float m_AimSpeedMultiplier;` |
| 0x40 | `private PlayerWeapon m_WeaponManager;` |
| 0x48 | `private XA m_EventHandler;` |
| 0x50 | `private RaycastManager m_RaycastManager;` |
| 0x58 | `public FPObject _currentWeapon;` |
| 0x60 | `private FPWeaponBase ObL;` |
| 0x68 | `private jk playerFPWeaponView;` |
| 0x70 | `private Coroutine Obo;` |
| 0x78 | `private WeaponPiece Oby;` |
| 0x84 | `private int Obz;` |
| 0x88 | `private CancellationTokenSource Obh;` |
| 0x90 | `private CancellationTokenSource ObB;` |
| 0x98 | `private TaskCompletionSource<bool> Obm;` |
| 0xA0 | `private bool ObR;` |
| - | `private float <Obb>k__BackingField;` |
| - | `private bool mountedWeaponHidden;` |

Properties: `public FPWeaponBase spS { get; }`; `public float spI { get; }`; `public bool spM { get; }`; `public bool sve { get; }`; `public float Obb { get; set; }`; `public bool HasCurrentOrPending { get; }`; `private bool MountedWeaponHidden { get; }`

<details><summary>methods (35)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DFC994 |  | `public FPWeaponBase get_spS()` |
| - | 0x2DFC99C |  | `public float get_spI()` |
| - | 0x2DFCA14 |  | `public bool get_spM()` |
| - | 0x2DFCA9C |  | `public bool get_sve()` |
| - | 0x2DFCB74 |  | `public float get_Obb()` |
| - | 0x2DFCB7C |  | `private void set_Obb(float value)` |
| 0x39F417C | 0x2DFCB84 |  | `private void Awake()` |
| 0x39F44F4 | 0x2DFCFA4 |  | `private void OnDestroy()` |
| 0x39F45DC | 0x2DFD16C |  | `private void cyI()` |
| - | 0x2DFD1AC |  | `private void cyM()` |
| - | 0x2DFD25C |  | `public void cze(WeaponPiece e, int f)` |
| 0x39F47C4 | 0x2DFD0D4 |  | `private void czf()` |
| 0x39F4830 | 0x2DFD32C |  | `private Task czF(WeaponPiece e, int f, CancellationToken F, TaskCompletionSource<bool> d)` |
| 0x39F4938 | 0x2DFD460 |  | `private void czd(FPObject e, int f)` |
| - | 0x2DFD78C |  | `public bool get_HasCurrentOrPending()` |
| - | 0x2DFD828 |  | `public bool TryGetDrawnWeapon(out WeaponPiece piece, out int animationId)` |
| - | 0x2DFD9B8 |  | `public void RecoveredRedraw()` |
| 0x39F4B0C | 0x2DFDAA8 |  | `private void czc()` |
| 0x39F4BB0 | 0x2DFDB4C |  | `private void czU()` |
| 0x39F4C6C | 0x2DFDC08 |  | `private bool czY()` |
| 0x39F4EA4 | 0x2DFDE88 |  | `private void czW()` |
| - | 0x2DFDE04 |  | `private IEnumerator czE(float e)` |
| 0x39F4F24 | 0x2DFDEE0 |  | `private bool czA()` |
| 0x39F4FB4 | 0x2DFDF7C |  | `private bool czu(bool e)` |
| 0x39F5114 | 0x2DFE144 |  | `public string czk()` |
| 0x39F51BC | 0x2DFE1DC |  | `public bool cyp()` |
| - | 0x2DFE268 |  | `public bool czO()` |
| - | 0x2DFD900 |  | `private bool get_MountedWeaponHidden()` |
| - | 0x2DFE26C |  | `public void SyncMountedWeaponVisibility()` |
| 0x39F5248 | 0x2DFE3A8 |  | `public void czt(bool e)` |
| 0x39F5278 | 0x2DFE5EC |  | `public void czr(bool e)` |
| 0x39F1CA0 | 0x2DFAC08 |  | `public void czN(float e)` |
| 0x39F53C0 | 0x2DFE7E0 |  | `public void .ctor()` |
| 0x39F53D4 | 0x2DFE7E8 |  | `private bool czq()` |
| 0x39F53DC | 0x2DFE7F0 |  | `private bool czs()` |

</details>

### public class `FPMelee` : FPWeaponBase  
`TypeDefIndex 2794`

| offset | field |
|---|---|
| 0xC8 | `private Xo m_EventHandler;` |
| 0xD0 | `private float m_MaxReach;` |
| 0xD4 | `private float hitRadius;` |
| 0xD8 | `private float m_TimeBetweenAttacks;` |
| 0xDC | `private float pauseAfterAttack;` |
| 0xE0 | `private float m_DamagePerHit;` |
| 0xE4 | `private float m_ImpactForce;` |
| 0xE8 | `protected AudioSource m_AudioSource;` |
| 0xF0 | `private SoundPlayer m_AttackAudio;` |
| 0xF8 | `protected TU m_SoundType;` |
| 0x100 | `private Xr Obl;` |
| 0x108 | `private Xr Obx;` |
| 0x110 | `private Xr ObK;` |

Properties: `public Xr svf { get; }`; `public Xr svF { get; }`; `public Xr svd { get; }`; `public float svc { get; }`; `public float svU { get; }`; `public float svY { get; }`; `public float svW { get; }`; `public float svE { get; }`

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F6918 | 0x2E14BC8 |  | `public Xr get_svf()` |
| 0x39F6920 | 0x2E14BD0 |  | `public Xr get_svF()` |
| 0x39F6928 | 0x2E14BD8 |  | `public Xr get_svd()` |
| 0x39F6930 | 0x2E14BE0 |  | `public float get_svc()` |
| 0x39F6938 | 0x2E14BE8 |  | `public float get_svU()` |
| 0x39F6940 | 0x2E14BF0 |  | `public float get_svY()` |
| 0x39F6948 | 0x2E14BF8 |  | `public float get_svW()` |
| 0x39F6950 | 0x2E14C00 |  | `public float get_svE()` |
| 0x39F6958 | 0x2E14C08 | 5 | `public override void Initialize()` |
| 0x39F696C | 0x2E14C1C |  | `private void FixedUpdate()` |
| 0x39F69BC | 0x2E14CC4 | 17 | `public override bool daS(Camera e)` |
| 0x39F6A50 | 0x2E14D58 | 18 | `public override bool cyo(Camera e)` |
| 0x39F6A60 | 0x2E14D68 | 19 | `protected virtual void Start()` |
| 0x39F6AF0 | 0x2E14DF8 | 7 | `protected override void OnDestroy()` |
| 0x39F6B80 | 0x2E14E88 |  | `private void czJ()` |
| 0x39EFEC4 | 0x2E15008 | 20 | `protected virtual void On_Hit(XR raycastData)` |
| 0x39F6CA8 | 0x2E15708 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x39F6C6C | 0x2E14FC8 |  | `private void On_Woosh()` |
| 0x39F0B78 | 0x2E157B4 |  | `public void .ctor()` |

</details>

### public class `FPMeleeAnimator` : FPAnimator  
`TypeDefIndex 2795`

| offset | field |
|---|---|
| 0x48 | `private float m_MissSpeed;` |
| 0x4C | `private float m_HitSpeed;` |
| 0x50 | `private WeaponShake m_MeleeWooshShake;` |
| 0x58 | `private WeaponShake m_MeleeHitShake;` |
| 0x60 | `private FPMelee ObG;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F6CD4 | 0x2E158F4 | 4 | `public override void dQU()` |
| 0x39F6F98 | 0x2E15BD0 | 7 | `protected override void OnValidate()` |
| 0x39F70AC | 0x2E15BD4 |  | `private void czX()` |
| 0x39F713C | 0x2E15C54 |  | `private void czT()` |
| 0x39F71C0 | 0x2E15CBC |  | `private void czL()` |
| 0x39F71DC | 0x2E15CD8 |  | `public void .ctor()` |

</details>

### public class `FPMotion` : MonoBehaviour  
`TypeDefIndex 2796`

| offset | field |
|---|---|
| 0x20 | `private Transform m_Model;` |
| 0x28 | `private Transform m_Pivot;` |
| 0x30 | `private Sway m_MovementSway;` |
| 0x38 | `private Sway m_RotationSway;` |
| 0x40 | `private TrigonometricBob m_WalkBob;` |
| 0x48 | `private TrigonometricBob m_AimBob;` |
| 0x50 | `private TrigonometricBob m_RunBob;` |
| 0x58 | `private LerpControlledBob m_LandBob;` |
| 0x60 | `private float m_MaxLandSpeed;` |
| 0x68 | `private TransformOffset m_IdleOffset;` |
| 0x70 | `private TransformOffset m_RunOffset;` |
| 0x78 | `private TransformOffset m_AttackOffset;` |
| 0x80 | `private TransformOffset m_AimOffset;` |
| 0x88 | `private TransformOffset m_OnLadderOffset;` |
| 0x90 | `private TransformOffset m_JumpOffset;` |
| 0x98 | `private TransformOffset m_LookOffset;` |
| 0xA0 | `private TransformOffset m_TooCloseOffset;` |
| 0xA8 | `private Transform Obn;` |
| 0xB0 | `private FPObject ObV;` |
| 0xB8 | `private FPWeaponBase Obg;` |
| 0xC0 | `private TransformOffset Obp;` |
| 0xC8 | `private bool Obv;` |
| 0xD0 | `public XA Player;` |
| - | `private FPAnimator weaponAnimator;` |
| - | `private bool reloadRunBlend;` |
| - | `private static readonly int HolsterState;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F7594 | 0x2E15D04 |  | `private void Start()` |
| 0x39F7910 | 0x2E160B0 |  | `private void On_Draw()` |
| 0x39F7944 | 0x2E160EC |  | `private void czb()` |
| 0x39F7950 | 0x2E160F8 |  | `private void czl(float e)` |
| 0x39F77D8 | 0x2E15F7C |  | `private void czx()` |
| 0x39F79C8 | 0x2E16170 |  | `private void Update()` |
| 0x39F81DC | 0x2E16E84 |  | `private void czK(TransformOffset e, bool f)` |
| 0x39F824C | 0x2E16EF8 |  | `public void .ctor()` |
| - | 0x2E16F00 |  | `private static void .cctor()` |

</details>

### public class `FPObject` : MonoBehaviour, IInitializable  
`TypeDefIndex 2797`

| offset | field |
|---|---|
| 0x20 | `public Xr Draw;` |
| 0x28 | `public Xr Holster;` |
| 0x48 | `public int m_ObjectID;` |
| 0x50 | `public string m_ObjectName;` |
| 0x58 | `private int m_TargetFOV;` |
| 0x60 | `protected RaycastManager m_RaycastManager;` |
| 0x68 | `protected PlayerWeapon m_WeaponManager;` |
| 0x70 | `protected float drawPeriod;` |
| 0x74 | `protected float holsterPeriod;` |
| 0x78 | `protected Xj.Value Olf;` |
| 0x80 | `public PlayerManager Player;` |
| 0x88 | `public XA PlayerEventHandler;` |
| 0x90 | `protected FixedTimer OlF;` |
| - | `private bool <ObS>k__BackingField;` |
| - | `private Item <ObI>k__BackingField;` |
| - | `private float <ObM>k__BackingField;` |
| - | `private float <Ole>k__BackingField;` |
| - | `private bool <Old>k__BackingField;` |

Properties: `public bool ObS { get; set; }`; `public int svt { get; }`; `public string svr { get; }`; `public Item ObI { get; set; }`; `public int svN { get; }`; `public float ObM { get; set; }`; `public float Ole { get; set; }`; `public RaycastManager svq { get; set; }`; `public PlayerWeapon svs { get; set; }`; `public bool Old { get; set; }`

<details><summary>methods (27)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E16F68 |  | `public bool get_ObS()` |
| - | 0x2E16F70 |  | `private void set_ObS(bool value)` |
| - | 0x2E16F7C |  | `public int get_svt()` |
| - | 0x2E16F84 |  | `public string get_svr()` |
| - | 0x2E16F8C |  | `public Item get_ObI()` |
| - | 0x2E16F94 |  | `private void set_ObI(Item value)` |
| - | 0x2E16F9C |  | `public int get_svN()` |
| - | 0x2E16FA4 |  | `public float get_ObM()` |
| - | 0x2E16FAC |  | `protected void set_ObM(float value)` |
| - | 0x2E16FB4 |  | `public float get_Ole()` |
| - | 0x2E16FBC |  | `protected void set_Ole(float value)` |
| - | 0x2E16FC4 |  | `public RaycastManager get_svq()` |
| - | 0x2E16FCC |  | `public void set_svq(RaycastManager value)` |
| - | 0x2E16FD4 |  | `public PlayerWeapon get_svs()` |
| - | 0x2E16FDC |  | `public void set_svs(PlayerWeapon value)` |
| - | 0x2E16FE4 |  | `public bool get_Old()` |
| - | 0x2E16FEC |  | `protected void set_Old(bool value)` |
| 0x39EEA6C | 0x2E16FF8 | 5 | `public virtual void Initialize()` |
| 0x39F82EC | 0x2E17004 | 6 | `public virtual void chY()` |
| 0x39F82F8 | 0x2E17010 | 7 | `protected virtual void OnDestroy()` |
| 0x39F82FC | 0x2E17014 |  | `private void FixedUpdate()` |
| 0x39F8340 | 0x2E170A4 | 8 | `public virtual bool chW()` |
| 0x39F8360 | 0x2E170C4 | 9 | `public virtual bool chE()` |
| - | 0x2E170CC |  | `public virtual void RefreshItem(Item item)` |
| 0x39F8368 | 0x2E17228 | 10 | `public virtual void On_Draw(Item correspondingItem)` |
| 0x39F319C | 0x2E17334 | 11 | `public virtual void dQd()` |
| 0x39F844C | 0x2E17370 |  | `public void .ctor()` |

</details>

### public class `FPRocketAnimator` : FPAnimator  
`TypeDefIndex 2800`

| offset | field |
|---|---|
| 0x48 | `private WeaponShake m_ReleaseShake;` |
| 0x50 | `public GameObject m_RocketPrefab;` |
| 0x58 | `private GameObject m_Smoke;` |
| 0x60 | `private bool m_UseSmoke;` |
| 0x68 | `private FPRocketLauncher m_RocketLauncher;` |
| - | `private Coroutine pose;` |

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F853C | 0x2E17400 | 4 | `public override void dQU()` |
| 0x39F8610 | 0x2E174B8 | 6 | `protected override void OnDestroy()` |
| 0x39F86A8 | 0x2E17504 | 8 | `protected override void On_Draw()` |
| 0x39F8778 | 0x2E176AC | 9 | `protected override void cyU()` |
| - | 0x2E17770 |  | `private IEnumerator ReloadDraw()` |
| - | 0x2E17804 |  | `public void SetRocketVisible(bool visible)` |
| - | 0x2E174D4 |  | `private void CancelPresentation()` |
| - | 0x2E17988 |  | `private void OnDisable()` |
| - | 0x2E175E8 |  | `private void PoseTo(Vector3 from, Vector3 to, float duration, bool snapFrom, bool easeOut)` |
| - | 0x2E1798C |  | `private IEnumerator PoseRoutine(Vector3 from, Vector3 to, float duration, bool snapFrom, bool easeOut)` |
| - | 0x2E17A8C |  | `private static float EaseOutBack(float u)` |
| - | 0x2E17AC0 |  | `private static float EaseInBack(float u)` |
| 0x39F8824 | 0x2E17AE4 |  | `public void Release()` |
| - | 0x2E17AE8 |  | `private void chA()` |
| 0x39F8998 | 0x2E17C70 |  | `public void Reload()` |
| 0x39F8AAC | 0x2E17D3C |  | `private void chu()` |
| 0x39F8B98 | 0x2E17DE0 |  | `public void .ctor()` |

</details>

### public class `FPRocketLauncher` : FPWeaponBase  
`TypeDefIndex 2801`

| offset | field |
|---|---|
| 0xC4 | `private LayerMask m_Mask;` |
| 0xC8 | `private float m_MaxDistance;` |
| 0xD0 | `private FPRocketAnimator m_FPRocketAnimator;` |
| 0xD8 | `private float reloadPeriod;` |
| 0xDC | `private float m_MinTimeBetweenShots;` |
| 0xE0 | `public ShaftedProjectile m_RocketPrefab;` |
| 0xE8 | `private Vector3 m_SpawnOffset;` |
| 0xF8 | `private AudioSource m_AudioSource;` |
| 0x100 | `private SoundPlayer m_ReleaseAudio;` |
| 0x108 | `private SoundPlayer m_ReloadAudio;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F8BA8 | 0x2E181E4 | 5 | `public override void Initialize()` |
| 0x39F8C4C | 0x2E182D0 |  | `private void FixedUpdate()` |
| 0x39F8D78 | 0x2E18524 | 17 | `public override bool daS(Camera e)` |
| 0x39F91FC | 0x2E18A80 | 7 | `protected override void OnDestroy()` |
| 0x39F928C | 0x2E18B58 | 14 | `public override bool daM(bool e)` |
| 0x39F931C | 0x2E18DB4 |  | `private bool chk()` |
| 0x39F8F90 | 0x2E18678 |  | `private void chO(Camera e)` |
| 0x39F9344 | 0x2E18F30 |  | `private void AnimateThrow()` |
| 0x39F9380 | 0x2E18F34 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x39F9404 | 0x2E18F38 | 11 | `public override void dQd()` |
| 0x39F93E4 | 0x2E18F3C |  | `public bool cht()` |
| 0x39F942C | 0x2E18F44 |  | `public void .ctor()` |

</details>

### public class `FPSpear` : FPWeaponBase  
`TypeDefIndex 2803`

| offset | field |
|---|---|
| 0xC4 | `private LayerMask m_Mask;` |
| 0xC8 | `private float m_MaxDistance;` |
| 0xCC | `private float m_MinTimeBetweenThrows;` |
| 0xD0 | `public ShaftedProjectile m_SpearPrefab;` |
| 0xD8 | `private Vector3 m_SpawnOffset;` |
| 0xE4 | `private float m_SpawnDelay;` |
| 0xE8 | `private AudioSource m_AudioSource;` |
| 0xF0 | `private SoundPlayer m_ThrowAudio;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F954C | 0x2E18F48 | 5 | `public override void Initialize()` |
| 0x39F95F0 | 0x2E19030 |  | `private void FixedUpdate()` |
| 0x39F9640 | 0x2E19034 | 17 | `public override bool daS(Camera e)` |
| 0x39F9924 | 0x2E1920C | 7 | `protected override void OnDestroy()` |
| 0x39F99B4 | 0x2E192F0 |  | `private bool chC()` |
| - | 0x2E191EC |  | `private IEnumerator chZ(Camera e, float f)` |
| 0x39F9A04 | 0x2E1940C |  | `private void AnimateThrow()` |
| 0x39F9A58 | 0x2E1944C | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x39F9B24 | 0x2E194F0 |  | `public void .ctor()` |

</details>

### public class `FPSpearAnimator` : FPAnimator  
`TypeDefIndex 2804`

| offset | field |
|---|---|
| 0x48 | `private float m_ThrowSpeed;` |
| 0x50 | `private WeaponShake m_ThrowShake;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39F9F1C | 0x2E1951C | 4 | `public override void dQU()` |
| 0x39FA270 | 0x2E19770 | 5 | `public override void cyc()` |
| 0x39FA27C | 0x2E1977C | 6 | `protected override void OnDestroy()` |
| 0x39FA520 | 0x2E19970 | 7 | `protected override void OnValidate()` |
| 0x39FA618 | 0x2E19974 |  | `private void chj()` |
| 0x39FA6E0 | 0x2E19A44 |  | `private void chQ()` |
| 0x39FA800 | 0x2E19B54 |  | `private void chH()` |
| 0x39FA8A0 | 0x2E19C28 |  | `public void .ctor()` |

</details>

### public class `FPTool` : FPMelee  
`TypeDefIndex 2806`

| offset | field |
|---|---|
| 0x118 | `public FPTool.Xh m_ToolPurposes;` |
| 0x11C | `public float m_Efficiency;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FA8B0 | 0x2E19C30 | 20 | `protected override void On_Hit(XR raycastData)` |
| 0x39FA99C | 0x2E19C34 |  | `public void .ctor()` |

</details>

### public class `FPTorch` : FPMelee  
`TypeDefIndex 2807`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FA9AC | 0x2E19C50 |  | `public void .ctor()` |

</details>

### public abstract class `FPWeaponBase` : FPObject  
`TypeDefIndex 2809`

| offset | field |
|---|---|
| 0x95 | `private bool m_UseWhileNearObjects;` |
| 0x98 | `private Lf.Le m_DamageType;` |
| 0x9C | `private bool canAim;` |
| 0xA0 | `protected Xj.Value Olk;` |
| 0xA8 | `protected bool OlO;` |
| 0xA9 | `protected bool Olt;` |
| 0xB0 | `private Xr Olr;` |
| - | `private bool <OlN>k__BackingField;` |
| - | `private bool <Olq>k__BackingField;` |
| - | `private float <Ols>k__BackingField;` |
| - | `private float <OlC>k__BackingField;` |

Properties: `public Xr svj { get; }`; `public bool sva { get; }`; `public bool svQ { get; }`; `public Lf.Le svH { get; }`; `public bool OlN { get; set; }`; `public bool Olq { get; set; }`; `public float Ols { get; set; }`; `public float OlC { get; set; }`; `public bool BlocksSprint { get; }`; `public bool IsFiringMotion { get; }`

<details><summary>methods (31)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E19C54 |  | `public Xr get_svj()` |
| - | 0x2E19C5C |  | `public bool get_sva()` |
| - | 0x2E19C64 |  | `public bool get_svQ()` |
| - | 0x2E19C6C |  | `public Lf.Le get_svH()` |
| - | 0x2E19C74 |  | `public bool get_OlN()` |
| - | 0x2E19C7C |  | `protected void set_OlN(bool value)` |
| - | 0x2E19C88 |  | `public bool get_Olq()` |
| - | 0x2E19C90 |  | `protected void set_Olq(bool value)` |
| - | 0x2E19C9C |  | `public float get_Ols()` |
| - | 0x2E19CA4 |  | `protected void set_Ols(float value)` |
| - | 0x2E19CAC |  | `public float get_OlC()` |
| - | 0x2E19CB4 |  | `protected void set_OlC(float value)` |
| 0x39FAC34 | 0x2E19CBC | 9 | `public override bool chE()` |
| 0x39FAC5C | 0x2E19CE4 | 8 | `public override bool chW()` |
| 0x39FAC84 | 0x2E19D0C | 12 | `public virtual bool chK()` |
| 0x39FACD4 | 0x2E19D5C | 13 | `public virtual bool chG()` |
| 0x39FACF4 | 0x2E18C70 | 14 | `public virtual bool daM(bool e)` |
| 0x39FAD60 | 0x2E19D7C | 15 | `public virtual bool chP()` |
| 0x39FAD90 | 0x2E19E2C | 16 | `public virtual bool chD()` |
| - | 0x2E19EDC |  | `public override void RefreshItem(Item item)` |
| 0x39F9A84 | 0x2E1573C | 10 | `public override void On_Draw(Item correspondingItem)` |
| - | 0x2E18E44 |  | `protected void FireProjectile(ShaftedProjectile projectile, Vector3 origin, Vector3 angles, float strength)` |
| - | 0x2E16BE8 |  | `public bool get_BlocksSprint()` |
| - | 0x2E16D84 |  | `public bool get_IsFiringMotion()` |
| - | 0x2E19F58 |  | `protected void ProjectilePose(Camera camera, LayerMask mask, float distance, Vector3 offset, out Vector3 origin, out Vector3 angles)` |
| - | 0x2E19320 |  | `protected IEnumerator SendProjectile(Camera camera, LayerMask mask, float distance, Vector3 offset, float delay, float strength = 1, ShaftedProjectile projectile)` |
| - | 0x2E189CC |  | `protected void SpendRound()` |
| - | 0x2E18484 |  | `protected void ReleaseDrawLock()` |
| 0x39FADC0 | 0x2E1A1FC | 17 | `public virtual bool daS(Camera e)` |
| 0x39FADC8 | 0x2E1A204 | 18 | `public virtual bool cyo(Camera e)` |
| 0x39F9B40 | 0x2E15884 |  | `protected void .ctor()` |

</details>

### public class `GameController` : vd  
`TypeDefIndex 2815`

| offset | field |
|---|---|
| 0x50 | `public static bool isPlaying;` |
| 0x68 | `private ItemDatabase m_ItemDatabase;` |
| 0x70 | `private GameObject m_PlayerPrefab;` |
| 0x78 | `private Lu mainCamera;` |
| 0x80 | `private AudioUtils audioUtils;` |
| 0x88 | `private DissonanceComms m_VoiceManager;` |
| 0x90 | `private InputManager m_InputManager;` |
| 0x98 | `private Volume volume;` |
| 0xA0 | `private VolumeProfile[] volumeProfiles;` |
| 0xA8 | `public Hotbar hotbar;` |
| 0xB0 | `public zF teamUI;` |
| 0xB8 | `public DamageGUI damageGUI;` |
| 0xC0 | `public ze deathScreen;` |
| 0xC8 | `public yI craftingGUI;` |
| 0xD0 | `public yS characterGUI;` |
| 0xD8 | `public PurchasesUI purchasesUI;` |
| 0xE0 | `public EventShopUI eventShopUI;` |
| 0xE8 | `public BuildingWheel buildingMenu;` |
| 0xF0 | `public PlayerStatsGUI playerStatsGUI;` |
| 0xF8 | `public PlayerVitalsGUI playerVitalsGUI;` |
| 0x100 | `public zf questUI;` |
| 0x108 | `public CrosshairManager crosshairManager;` |
| 0x110 | `public PlayerInputHandler playerInputHandler;` |
| 0x118 | `public ScreenControlsManager screenControlsManager;` |
| 0x120 | `public cA compass;` |
| 0x128 | `public MapManager mapManager;` |
| 0x130 | `public At TODSky;` |
| 0x138 | `public LifeInfo lifeInfo;` |
| 0x140 | `public RespawnMenu respawnMenu;` |
| 0x148 | `public PauseManager pauseManager;` |
| 0x150 | `public Lm playersListManager;` |
| 0x158 | `public Wj teamManager;` |
| 0x160 | `public GameObject voiceIndicator;` |
| 0x168 | `public GameObject voiceButton;` |
| 0x170 | `private jK context;` |
| 0x60 | `private static readonly TrY<GameObject> zGz;` |
| 0x178 | `private js.jq OGG;` |
| - | `private bool inventoryPreviewBound;` |
| 0x180 | `private HF OGP;` |
| - | `private static readonly TrY<NetworkIdentity> XYa;` |
| - | `private static readonly TrY<PlayerManager> iKR;` |
| - | `private static readonly TrY<XA> btD;` |
| - | `private static PlayerInputHandler <OGz>k__BackingField;` |
| - | `private static InputManager <OGh>k__BackingField;` |
| - | `private static AudioUtils <OGB>k__BackingField;` |
| - | `private static Lu <OGm>k__BackingField;` |
| - | `private static BaseSurfaceDatabase <OGR>k__BackingField;` |
| - | `private static ItemDatabase <OGb>k__BackingField;` |
| - | `private static ScreenControlsManager <OGl>k__BackingField;` |
| - | `private static DissonanceComms <OGx>k__BackingField;` |
| - | `private static CrosshairManager lookAtHealthOwner;` |

Properties: `private static GameObject OGK { get; set; }`; `public static NetworkIdentity OGL { get; set; }`; `public static PlayerManager OGo { get; set; }`; `public static XA OGy { get; set; }`; `public static PlayerInputHandler OGz { get; set; }`; `public static InputManager OGh { get; set; }`; `public static AudioUtils OGB { get; set; }`; `public static Lu OGm { get; set; }`; `public static BaseSurfaceDatabase OGR { get; set; }`; `public static ItemDatabase OGb { get; set; }`; `public static ScreenControlsManager OGl { get; set; }`; `public static DissonanceComms OGx { get; set; }`; `public jK sSi { get; }`; `private bool sSw { get; }`

<details><summary>methods (67)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E1A344 |  | `private static GameObject get_OGK()` |
| - | 0x2E1A3BC |  | `private static void set_OGK(GameObject value)` |
| - | 0x2E1A43C |  | `public static NetworkIdentity get_OGL()` |
| - | 0x2E1A4B4 |  | `private static void set_OGL(NetworkIdentity value)` |
| - | 0x2E1A534 |  | `public static PlayerManager get_OGo()` |
| - | 0x2E1A5AC |  | `private static void set_OGo(PlayerManager value)` |
| - | 0x2E1A62C |  | `public static XA get_OGy()` |
| - | 0x2E1A6A4 |  | `private static void set_OGy(XA value)` |
| - | 0x2E1A724 |  | `public static PlayerInputHandler get_OGz()` |
| - | 0x2E1A77C |  | `private static void set_OGz(PlayerInputHandler value)` |
| - | 0x2E1A7DC |  | `public static InputManager get_OGh()` |
| - | 0x2E1A834 |  | `private static void set_OGh(InputManager value)` |
| - | 0x2E1A894 |  | `public static AudioUtils get_OGB()` |
| - | 0x2E1A8EC |  | `private static void set_OGB(AudioUtils value)` |
| - | 0x2E1A94C |  | `public static Lu get_OGm()` |
| - | 0x2E1A9A4 |  | `private static void set_OGm(Lu value)` |
| - | 0x2E1AA04 |  | `public static BaseSurfaceDatabase get_OGR()` |
| - | 0x2E1AA5C |  | `private static void set_OGR(BaseSurfaceDatabase value)` |
| - | 0x2E1AABC |  | `public static ItemDatabase get_OGb()` |
| - | 0x2E1AB14 |  | `private static void set_OGb(ItemDatabase value)` |
| - | 0x2E1AB74 |  | `public static ScreenControlsManager get_OGl()` |
| - | 0x2E1ABCC |  | `private static void set_OGl(ScreenControlsManager value)` |
| - | 0x2E1AC2C |  | `public static DissonanceComms get_OGx()` |
| - | 0x2E1AC84 |  | `private static void set_OGx(DissonanceComms value)` |
| 0x3A19BC8 | 0x2E1ACE4 |  | `public jK get_sSi()` |
| 0x3A19BD0 | 0x2E1ACEC |  | `private bool get_sSw()` |
| 0x3A19CA8 | 0x2E1ACF4 |  | `public void cGc(js.jq e, HF f)` |
| 0x3A19CDC | 0x2E1AD28 |  | `public void cGU(vt e, float f, float F)` |
| 0x3A19E20 | 0x2E1AD2C |  | `private void Awake()` |
| 0x3A1A754 | 0x2E1B044 |  | `private void Start()` |
| - | 0x2E1B128 |  | `private void BindInventoryPreview()` |
| 0x3A1AA24 | 0x2E1C69C |  | `private void Update()` |
| - | 0x2E1C90C |  | `internal static void MyW(PlayerManager expected)` |
| - | 0x2E1CA4C |  | `private static void app()` |
| - | 0x2E1CA9C |  | `private void OnDestroy()` |
| 0x3A1AA4C | 0x2E1CB20 |  | `public void cGY(GameObject e)` |
| 0x3A1B424 | 0x2E1D3D0 |  | `private void ConfigureRecoveredCameraStack()` |
| - | 0x2E1DB94 |  | `public void Respawn()` |
| 0x3A1B52C | 0x2E1DCC4 |  | `public void cGW(uint e)` |
| 0x3A1B644 | 0x2E1DE08 |  | `public void Suicide()` |
| 0x3A1B7C8 | 0x2E1DEC0 |  | `public void Respawn(vt conn)` |
| 0x3A1B7CC | 0x2E1DEC4 |  | `public void cGE(Transform e)` |
| 0x3A1B24C | 0x2E1D318 |  | `public void cGA(Transform e, Transform f, bool F = false)` |
| 0x3A1BB04 | 0x2E1E228 |  | `public void cGu(string e)` |
| 0x3A1A35C | 0x2E1E22C |  | `private void cGk()` |
| - | 0x2E1E920 |  | `private Task cGO(Action<bool> e, Action<bool> f)` |
| 0x3A1BC28 | 0x2E1E928 |  | `public void cGt(string e, string f, bool F)` |
| 0x3A1BD7C | 0x2E1E92C |  | `private void cGr(int e, int f, int F, float d, int c)` |
| 0x3A1BF08 | 0x2E1E930 |  | `public void cGN(bool[] e, Vector3[] f)` |
| 0x3A1C048 | 0x2E1E934 |  | `public static GameObject cGq(GameObject e, Vector3 f, Quaternion F)` |
| 0x3A1C10C | 0x2E1E93C |  | `public void .ctor()` |
| 0x3A1C114 | 0x2E1E944 |  | `private void cGs(bool e)` |
| 0x3A1C1D4 | 0x2E1E948 |  | `private void cGC()` |
| 0x3A1C3CC | 0x2E1E94C | 12 | `public override bool Fuk()` |
| 0x3A1C3D4 | 0x2E1E954 |  | `protected void cGZ(vt e, float f, float F)` |
| 0x3A1C3F0 | 0x2E1EAD0 |  | `protected static void cGj(vd e, vo f, vt F)` |
| 0x3A1C554 | 0x2E1EAD4 |  | `protected void cGa(string e)` |
| 0x3A1C560 | 0x2E1ECF8 |  | `protected static void cGQ(vd e, vo f, vt F)` |
| 0x3A1C698 | 0x2E1ED88 |  | `protected void cGH(string e, string f, bool F)` |
| 0x3A1C7EC | 0x2E1EEF4 |  | `protected static void cGi(vd e, vo f, vt F)` |
| 0x3A1C950 | 0x2E1EFB8 |  | `protected void cGw(int e, int f, int F, float d, int c)` |
| 0x3A1CAA0 | 0x2E1EFBC |  | `protected static void cGJ(vd e, vo f, vt F)` |
| 0x3A1CC38 | 0x2E1EFC0 |  | `protected void cGX(bool[] e, Vector3[] f)` |
| 0x3A1CC54 | 0x2E1F05C |  | `protected static void cGT(vd e, vo f, vt F)` |
| 0x3A1CDAC | 0x2E1F060 |  | `private static void .cctor()` |
| - | 0x2E1B544 |  | `public void ApplyVisualSettings()` |
| - | 0x2E1F434 |  | `public bool RefreshCameraStack()` |

</details>

### public class `GenericShake`  
`TypeDefIndex 2816`

| offset | field |
|---|---|
| 0x10 | `private float m_Magnitude;` |
| 0x14 | `private float m_MinMagnitudeScale;` |
| 0x18 | `private float m_Roughness;` |
| 0x1C | `private Vector3 m_PositionInfluence;` |
| 0x28 | `private Vector3 m_RotationInfluence;` |
| 0x34 | `private float m_FadeInTime;` |
| 0x38 | `private float m_FadeOutTime;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D9C5C | 0x2E1FC60 |  | `public void cHC(float e)` |
| 0x39DA410 | 0x2E1FD2C |  | `private Jv cHZ(float e)` |
| 0x39DA4F4 | 0x2E1FE14 |  | `public void .ctor()` |

</details>

### public class `GenericVitals` : XU  
`TypeDefIndex 2817`

| offset | field |
|---|---|
| 0x88 | `public float m_MaxHealth;` |
| 0x90 | `protected AudioSource m_AudioSource;` |
| 0x98 | `private HitBox[] m_Hitboxes;` |
| 0xA0 | `private float[] m_DamageMultipliers;` |
| 0xA8 | `protected float OmQ;` |
| 0xAC | `private float OmH;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DD988 | 0x2E1FE1C |  | `private void Awake()` |
| 0x39DD9E4 | 0x2E1FE78 | 18 | `public virtual void cik(float e, Lf.Le f, PlayerManager F)` |
| 0x39DDB48 | 0x2E1FFD4 |  | `public HitBox ciO(int e)` |
| 0x39DDB8C | 0x2E20010 |  | `public void cit(HitBox[] e)` |
| 0x39DD8C8 | 0x2E20018 |  | `public void .ctor()` |
| 0x39DDB9C | 0x2E20038 | 12 | `public override bool Fuk()` |

</details>

### public class `GunTrap` : Xb, Xa  
`TypeDefIndex 2818`

| offset | field |
|---|---|
| 0x80 | `public Ws trigger;` |
| 0x88 | `public Transform muzzlePos;` |
| 0x90 | `public Transform eyeTransform;` |
| 0x98 | `public int numPellets;` |
| 0x9C | `public int aimCone;` |
| 0xA0 | `public float sensorRadius;` |
| 0xA4 | `public LayerMask visibilityMask;` |
| 0xA8 | `public XE entityHandler;` |
| 0xB0 | `public BuildingPiece piece;` |
| 0xB8 | `protected int m_Capacity;` |
| 0xC0 | `private string panelName;` |
| 0xC8 | `public ItemContainer inventory;` |
| 0xD8 | `private AudioSource m_AudioSource;` |
| 0xE0 | `private SoundPlayer m_FireAudio;` |
| 0xE8 | `private ParticleSystem m_MuzzleFlash;` |

Properties: `public ItemHolder[] OPU { get; set; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1F5D4 | 0x2E20040 |  | `public ItemHolder[] get_OPU()` |
| 0x3A1F5DC | 0x2E20048 |  | `private void set_OPU(ItemHolder[] value)` |
| 0x3A1F5E4 | 0x2E2004C | 33 | `public override bool drE(out string e)` |
| 0x3A1F604 | 0x2E2006C |  | `public void cGv()` |
| 0x3A1F71C | 0x2E20284 |  | `public void cGS(Vector3 e, Quaternion f, int F)` |
| 0x3A1F8B0 | 0x2E2047C |  | `public void .ctor()` |
| 0x3A1F93C | 0x2E20484 | 12 | `public override bool Fuk()` |
| 0x3A1F944 | 0x2E20070 |  | `protected void cGI()` |
| 0x3A1F980 | 0x2E2048C |  | `protected static void cGM(vd e, vo f, vt F)` |
| 0x3A1FA9C | 0x2E20288 |  | `protected void cPe(Vector3 e, Quaternion f, int F)` |
| 0x3A1FBFC | 0x2E2050C |  | `protected static void cPf(vd e, vo f, vt F)` |
| 0x3A1FDB4 | 0x2E2060C |  | `private static void InitializeShotRpc()` |
| - | 0x2E20610 |  | `private static void .cctor()` |

</details>

### public class `HelpboxAttribute` : PropertyAttribute  
`TypeDefIndex 2819`

| offset | field |
|---|---|
| 0x10 | `public readonly string Message;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D88F0 | 0x2E2076C |  | `public void .ctor(string message)` |

</details>

### public class `HideSwitchAttribute` : PropertyAttribute  
`TypeDefIndex 2820`

| offset | field |
|---|---|
| 0x10 | `public readonly string m_BasedOnValue;` |
| 0x18 | `public readonly float m_IndentAmount;` |
| 0x1C | `public readonly bool m_ShowOnBool;` |
| 0x20 | `public readonly string m_ShowOnString;` |
| 0x28 | `public readonly int m_ShowOnInt;` |
| 0x2C | `public readonly float m_ShowOnFloat;` |
| 0x30 | `public readonly Vector3 m_ShowOnVector3;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D8920 | 0x2E20774 |  | `public void .ctor(string basedOn, bool showOnValue, float indentAmount = 20)` |
| 0x39D89E0 | 0x2E2077C |  | `public void .ctor(string basedOn, string showOnValue, float indentAmount = 20)` |
| 0x39D8AAC | 0x2E20784 |  | `public void .ctor(string basedOn, int showOnValue, float indentAmount = 20)` |
| 0x39D8B6C | 0x2E2078C |  | `public void .ctor(string basedOn, float showOnValue, float indentAmount = 20)` |
| 0x39D8C2C | 0x2E20794 |  | `public void .ctor(string basedOn, Vector3 showOnValue, float indentAmount = 20)` |

</details>

### public class `HitBox` : MonoBehaviour, XF  
`TypeDefIndex 2821`

| offset | field |
|---|---|
| 0x20 | `private float m_DamageMultiplier;` |
| 0x24 | `private Vector3 size;` |
| 0x30 | `private Vector3 center;` |
| 0x40 | `public HitBoxRecorderRoot HitBoxRoot;` |
| 0x48 | `public XE m_ParentEntity;` |
| 0x50 | `public Collider m_Collider;` |
| 0x58 | `public Rigidbody m_Rigidbody;` |
| 0x60 | `public MineableObject m_MineableObject;` |
| 0x68 | `public Ut m_HitArea;` |
| 0x6C | `public int id;` |

Properties: `public Vector3 sVR { get; }`; `public Vector3 sVb { get; }`; `public float sVl { get; }`; `public uint sVx { get; }`; `public float sVK { get; }`; `public bool sVG { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DDC58 | 0x2E2079C |  | `public Vector3 get_sVR()` |
| 0x39DDC64 | 0x2E207AC |  | `public Vector3 get_sVb()` |
| 0x39DDC90 | 0x2E207BC |  | `public float get_sVl()` |
| 0x39DDC98 | 0x2E207C4 |  | `public uint get_sVx()` |
| 0x39DDD2C | 0x2E207CC |  | `public float get_sVK()` |
| 0x39DDCCC | 0x2E207D4 |  | `public bool get_sVG()` |
| 0x39DDD60 | 0x2E207DC | 4 | `public void ciB(PlayerManager e, Xf f)` |
| 0x39DDD64 | 0x2E207E0 |  | `public bool ciG()` |
| 0x39DDD78 | 0x2E207E8 |  | `public bool ciP(Vector3 e, float f)` |
| 0x39DDE6C | 0x2E207F0 |  | `public bool ciD(Vector3 e, LayerMask f)` |
| 0x39DE02C | 0x2E207F8 |  | `public Vector3 cin(Vector3 e)` |
| 0x39DE0A4 | 0x2E20808 |  | `private void OnValidate()` |
| 0x39DE27C | 0x2E2080C |  | `public void .ctor()` |

</details>

### public class `InventoryController` : Lc<InventoryController>  
`TypeDefIndex 2822`

| offset | field |
|---|---|
| 0x20 | `public Xq<Lf.TI> State;` |
| 0x28 | `public XO<Lf.TI> SetState;` |
| 0x30 | `public XO<ItemHolder[]> OpenFurnace;` |
| 0x38 | `public XO<ItemHolder[]> OpenBigFurnace;` |
| 0x40 | `public XO<ItemHolder[]> OpenCampfire;` |
| 0x48 | `public XO<ItemHolder[]> OpenCupboard;` |
| 0x50 | `public XO<ItemHolder[]> OpenTurret;` |
| 0x58 | `public XO<ItemHolder[]> OpenTerminal;` |
| 0x60 | `public XO<ItemHolder[]> OpenRecycler;` |
| 0x68 | `public XO<ItemHolder[]> OpenShop;` |
| 0x70 | `public XO<ItemHolder[]> OpenGuntrap;` |
| 0x78 | `public XO<ItemHolder[]> OpenFueltank;` |
| 0x80 | `public XO<ItemHolder[]> OpenPlayerLoot;` |
| 0x88 | `public XO<ItemHolder[]> OpenLootContainer;` |
| 0x90 | `public XO<ItemHolder[]> OpenBigLoot;` |
| 0x98 | `public XO<ItemHolder[]> OpenInfinityLoot;` |
| 0xA0 | `public XO<ItemHolder[]> OpenAnvil;` |
| 0xA8 | `public XO<yT> CraftItem;` |
| 0xB0 | `public XN<ItemHolder> EquipmentChanged;` |
| 0xB8 | `public Xq<SF<EquipPiece>> EquipmentListChanged;` |
| 0xC0 | `public Xq<SF<EquipPiece>> WeaponListChanged;` |
| 0xE0 | `private ItemDatabase m_ItemDatabase;` |
| 0xE8 | `private int m_InventorySize;` |
| 0xEC | `private int m_HotbarSize;` |
| 0xF0 | `private Vector3 m_DropOffset;` |
| 0xFC | `private float m_DropAngularFactor;` |
| 0x100 | `private float m_DropSpeed;` |
| 0x108 | `private XA ORh;` |
| 0x110 | `private ItemHolder[] ORB;` |
| 0x118 | `private ItemHolder[] ORm;` |
| 0x120 | `private ItemHolder[] ORR;` |
| 0x128 | `public XM playerStats;` |
| 0x130 | `public Button closeButton;` |
| 0x138 | `public GameObject craftButton;` |
| - | `private ItemContainer <ORo>k__BackingField;` |
| - | `private ItemContainer <ORy>k__BackingField;` |
| - | `private ItemContainer[] <ORz>k__BackingField;` |
| - | `private bool refreshingEquipment;` |

Properties: `public bool spT { get; }`; `public ItemDatabase spL { get; }`; `public ItemContainer ORo { get; set; }`; `public ItemContainer ORy { get; set; }`; `public ItemContainer[] ORz { get; set; }`

<details><summary>methods (40)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E16B98 |  | `public bool get_spT()` |
| - | 0x2E20814 |  | `public ItemDatabase get_spL()` |
| - | 0x2E208DC |  | `public ItemContainer get_ORo()` |
| - | 0x2E208E4 |  | `private void set_ORo(ItemContainer value)` |
| - | 0x2E208F4 |  | `public ItemContainer get_ORy()` |
| - | 0x2E208FC |  | `private void set_ORy(ItemContainer value)` |
| - | 0x2E2090C |  | `public ItemContainer[] get_ORz()` |
| - | 0x2E20914 |  | `private void set_ORz(ItemContainer[] value)` |
| 0x39E8660 | 0x2E20924 |  | `public bool cLS(Item e, out int f)` |
| 0x39E86D8 | 0x2E20930 |  | `public bool cLI(int e, int f, ItemContainer F, out int d)` |
| 0x39E8770 | 0x2E2093C |  | `public bool cLM(int e, int f, int F, ItemContainer d, out int c)` |
| 0x39E8810 | 0x2E20948 |  | `public bool coe(string e, int f, ItemContainer F, out int d)` |
| 0x39E88A8 | 0x2E20954 |  | `public int cof(string e)` |
| 0x39E88C4 | 0x2E2095C |  | `public bool coF(Item e, Slot f)` |
| 0x39E8E2C | 0x2E20964 |  | `public ItemHolder[] cod()` |
| 0x39E8E34 | 0x2E2096C |  | `private void Awake()` |
| 0x39E9368 | 0x2E20F54 |  | `public void coc()` |
| 0x39E9464 | 0x2E2142C |  | `private void coU(Xf e)` |
| 0x39E96E0 | 0x2E21430 |  | `public void ClearSlotsOnDeath()` |
| - | 0x2E21434 |  | `private void coY()` |
| 0x39E97F0 | 0x2E21940 |  | `private void coW(ItemContainer e)` |
| 0x39E9968 | 0x2E21B18 |  | `private void coE(ItemContainer e)` |
| 0x39E9B48 | 0x2E21B1C |  | `private bool coA(Lf.TI e)` |
| 0x39E9DA4 | 0x2E2217C |  | `private Jp cou(Lf.TI e)` |
| 0x39E9DBC | 0x2E22184 |  | `public void cok(string e, ItemHolder[] f)` |
| 0x39E926C | 0x2E20E58 |  | `private ItemHolder[] coO(int e)` |
| 0x39EA1A8 | 0x2E2288C |  | `public string cot()` |
| 0x39EA50C | 0x2E22894 |  | `public string cor()` |
| 0x39EA870 | 0x2E2289C |  | `public string coN()` |
| 0x39EABD4 | 0x2E228A4 |  | `public void coq(string e, ItemContainer f)` |
| 0x39EB0B0 | 0x2E228A8 |  | `public void cos(string e)` |
| 0x39EB534 | 0x2E228AC |  | `public void InventoryAction()` |
| 0x39EB594 | 0x2E22924 |  | `public void ApplyRecoveredSlot(string name, int count, float condition, int ammo, int skin, int index)` |
| - | 0x2E23180 |  | `public void ApplyItemProps(int hotbarIndex, float condition, int ammo)` |
| - | 0x2E1B6DC |  | `public void EnsureRecoveredState()` |
| - | 0x2E1BDC0 |  | `public void RefreshEquipmentPresentation()` |
| - | 0x2E234DC |  | `private static float Channel(ProtectionValues values, Lf.Le channel)` |
| - | 0x2E23320 |  | `private static float ArmorTotal(string[] names, ProtectionValues[] values, int count, Lf.Le channel, bool environmental)` |
| - | 0x2E23584 |  | `public void .ctor()` |
| 0x39EBA5C | 0x2E23620 |  | `private void coC()` |

</details>

### public class `Item`  
`TypeDefIndex 2825`

| offset | field |
|---|---|
| 0x10 | `public XN<Xj.Value> PropertyChanged;` |
| 0x18 | `public Xr StackChanged;` |
| 0x34 | `private int m_Amount;` |
| 0x38 | `private List<Xj.Value> m_CurrentPropertyValues;` |
| - | `private bool <ORC>k__BackingField;` |
| - | `private ItemData <ORZ>k__BackingField;` |
| - | `private int <ORj>k__BackingField;` |

Properties: `public bool ORC { get; set; }`; `public ItemData ORZ { get; set; }`; `public int sgF { get; }`; `public string sgd { get; }`; `public int sgc { get; set; }`; `public Sprite Icon { get; }`; `public int ORj { get; set; }`; `public List<Xj.Value> sgU { get; }`

<details><summary>methods (22)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E2367C |  | `public bool get_ORC()` |
| - | 0x2E23684 |  | `private void set_ORC(bool value)` |
| - | 0x2E23690 |  | `public ItemData get_ORZ()` |
| - | 0x2E23698 |  | `private void set_ORZ(ItemData value)` |
| 0x39E444C | 0x2E236A0 |  | `public int get_sgF()` |
| - | 0x2E236A8 |  | `public string get_sgd()` |
| - | 0x2E23740 |  | `public int get_sgc()` |
| - | 0x2E23748 |  | `public void set_sgc(int value)` |
| - | 0x2E2376C |  | `public Sprite get_Icon()` |
| - | 0x2E23964 |  | `public int get_ORj()` |
| - | 0x2E2396C |  | `public void set_ORj(int value)` |
| - | 0x2E23974 |  | `public List<Xj.Value> get_sgU()` |
| 0x39E44E8 | 0x2E2397C |  | `public static bool cJx(Item e)` |
| 0x39E44F4 | 0x2E22E98 |  | `public void .ctor(ItemData data, int currentInStack = 1, List<Xj.Value> customPropertyValues, int skin = -1)` |
| 0x39E4864 | 0x2E23B98 |  | `public void cJK(ItemDatabase e)` |
| 0x39E4B08 | 0x2E23B9C |  | `public bool cJG(string e)` |
| 0x39E4C24 | 0x2E17144 |  | `public Xj.Value cJP(string e)` |
| 0x39E4D5C | 0x2E23C90 |  | `public bool cJD(string e, out Xj.Value f)` |
| 0x39E471C | 0x2E23988 |  | `private List<Xj.Value> cJn(List<Xj.Value> e)` |
| 0x39E4EB4 | 0x2E23CC0 |  | `private void cJV(Xj.Value e)` |
| 0x39E4F0C | 0x2E23D18 |  | `public void cJg()` |
| 0x39E5018 | 0x2E23D1C |  | `public bool cJp(Item e)` |

</details>

### public class `ItemCategory`  
`TypeDefIndex 2826`

| offset | field |
|---|---|
| 0x10 | `private string m_Name;` |
| 0x18 | `private ItemData[] m_Items;` |

Properties: `public string sge { get; }`; `public ItemData[] sgf { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E4410 | 0x2E23DC8 |  | `public string get_sge()` |
| - | 0x2E23DD0 |  | `public ItemData[] get_sgf()` |
| 0x39E4420 | 0x2E23DD8 |  | `public void .ctor()` |

</details>

### public class `ItemData` : ScriptableObject  
`TypeDefIndex 2830`

| offset | field |
|---|---|
| - | `public Sprite recoveredIcon;` |
| 0x18 | `private string m_ItemName;` |
| 0x20 | `private string m_ShortName;` |
| 0x28 | `private int m_levelToOpen;` |
| 0x30 | `private Wp.Phrase m_DisplayName;` |
| 0x38 | `private Wp.Phrase m_Description;` |
| 0x40 | `private int m_Id;` |
| 0x48 | `private string m_Category;` |
| 0x50 | `private AssetReference m_IconRef;` |
| 0x58 | `private AssetReference m_WorldObjectRef;` |
| 0x60 | `private int m_StackSize;` |
| 0x68 | `private List<Xj.Value> m_PropertyValues;` |
| 0x70 | `private bool m_IsBuildable;` |
| 0x71 | `private bool m_IsCraftable;` |
| 0x72 | `private bool m_IsVehicle;` |
| 0x73 | `private bool m_HasBlueprint;` |
| 0x74 | `private bool m_StoreItem;` |
| 0x78 | `private RecipeConfig recipeConfig;` |
| 0x80 | `private LootSpawn burnResult;` |
| 0x88 | `private ProtectionValues protection;` |
| 0x90 | `private Purchase m_Purchase;` |
| 0x98 | `private SkinData[] skinData;` |
| 0xA0 | `private ItemPreviewPositionConfig itemPreviewPositionConfig;` |

Properties: `public string RecoveredShortName { get; }`; `public string sgt { get; set; }`; `public int sgr { get; set; }`; `public Wp.Phrase sgN { get; set; }`; `public Wp.Phrase sgq { get; set; }`; `public int sgs { get; set; }`; `public string sgC { get; set; }`; `public Sprite sgZ { get; }`; `public GameObject sgj { get; }`; `public int sga { get; }`; `public List<Xj.Value> sgQ { get; }`; `public bool sgH { get; }`; `public bool sgi { get; }`; `public bool sgw { get; }`; `public bool sgJ { get; }`; `public LootSpawn sgX { get; }`; `public bool sgT { get; }`; `public bool sgL { get; set; }`; `public bool sgo { get; }`; `public RecipeConfig sgy { get; }`; `public ProtectionValues sgz { get; }`; `public Purchase sgh { get; }`; `public SkinData[] sgB { get; set; }`; `public string sgm { get; }`; `public ItemPreviewPositionConfig sgR { get; }`; `public AssetReference sgb { get; }`

<details><summary>methods (40)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E23DE0 |  | `public string get_RecoveredShortName()` |
| - | 0x2E23DE8 |  | `public string get_sgt()` |
| - | 0x2E23DF0 |  | `public void set_sgt(string value)` |
| - | 0x2E23DF8 |  | `public int get_sgr()` |
| - | 0x2E23E00 |  | `public void set_sgr(int value)` |
| - | 0x2E23E08 |  | `public Wp.Phrase get_sgN()` |
| - | 0x2E23E10 |  | `public void set_sgN(Wp.Phrase value)` |
| - | 0x2E23E18 |  | `public Wp.Phrase get_sgq()` |
| - | 0x2E23E20 |  | `public void set_sgq(Wp.Phrase value)` |
| - | 0x2E23E28 |  | `public int get_sgs()` |
| - | 0x2E23E30 |  | `public void set_sgs(int value)` |
| - | 0x2E23E38 |  | `public string get_sgC()` |
| - | 0x2E23E40 |  | `public void set_sgC(string value)` |
| - | 0x2E238A0 |  | `public Sprite get_sgZ()` |
| - | 0x2E23E48 |  | `public GameObject get_sgj()` |
| - | 0x2E23ECC |  | `public int get_sga()` |
| - | 0x2E23ED4 |  | `public List<Xj.Value> get_sgQ()` |
| 0x39E55EC | 0x2E23EDC |  | `public bool get_sgH()` |
| 0x39E55F4 | 0x2E23EE4 |  | `public bool get_sgi()` |
| 0x39E55FC | 0x2E23EEC |  | `public bool get_sgw()` |
| 0x39E5644 | 0x2E23F7C |  | `public bool get_sgJ()` |
| 0x39E56A0 | 0x2E23FDC |  | `public LootSpawn get_sgX()` |
| 0x39E56A8 | 0x2E23FE4 |  | `public bool get_sgT()` |
| - | 0x2E23FEC |  | `public bool get_sgL()` |
| - | 0x2E23FF4 |  | `public void set_sgL(bool value)` |
| 0x39E56C4 | 0x2E24000 |  | `public bool get_sgo()` |
| 0x39E56CC | 0x2E24008 |  | `public RecipeConfig get_sgy()` |
| - | 0x2E24010 |  | `public ProtectionValues get_sgz()` |
| 0x39E56DC | 0x2E24018 |  | `public Purchase get_sgh()` |
| 0x39E56E4 | 0x2E24020 |  | `public SkinData[] get_sgB()` |
| 0x39E56EC | 0x2E24028 |  | `public void set_sgB(SkinData[] value)` |
| 0x39E56F4 | 0x2E2402C |  | `public string get_sgm()` |
| 0x39E56FC | 0x2E24034 |  | `public ItemPreviewPositionConfig get_sgR()` |
| 0x39E5704 | 0x2E2403C |  | `public AssetReference get_sgb()` |
| 0x39E570C | 0x2E24044 |  | `public void cXI(RecipeConfig e)` |
| 0x39E5714 | 0x2E24048 |  | `public void cXM(ProtectionValues e)` |
| 0x39E571C | 0x2E2404C |  | `public bool cTe(string e)` |
| 0x39E57C8 | 0x2E2414C |  | `public Xj.Value cTf(string e)` |
| 0x39E5894 | 0x2E2424C |  | `public bool cTF(string e, out SkinData f)` |
| 0x39E5954 | 0x2E24390 |  | `public void .ctor()` |

</details>

### public class `ItemDatabase` : ScriptableObject  
`TypeDefIndex 2833`

| offset | field |
|---|---|
| 0x18 | `private ItemCategory[] m_Categories;` |
| 0x20 | `public Xj.Definition[] m_ItemProperties;` |
| 0x28 | `private AssetReference bagPickupRef;` |
| 0x30 | `public TechTreeData techTreeData;` |

Properties: `public ItemCategory[] sgl { get; }`; `public GameObject sgx { get; }`

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E24404 |  | `public ItemCategory[] get_sgl()` |
| 0x39E596C | 0x2E2440C |  | `public GameObject get_sgx()` |
| 0x39E59DC | 0x2E24414 |  | `public bool cTY(int e, out ItemData f)` |
| 0x39E5A9C | 0x2E22CE0 |  | `public bool cTW(string e, out ItemData f)` |
| 0x39E5BA8 | 0x2E245B0 |  | `public bool cTE(string e, out ItemData f)` |
| 0x39E5CB4 | 0x2E245D0 |  | `public bool cTA(string e, out List<ItemData> f, int F = 0)` |
| 0x39E5F58 | 0x2E248A4 |  | `public ItemData cTu(string e)` |
| 0x39E603C | 0x2E24974 |  | `public bool cTk(string e, out SkinData f, out ItemData F)` |
| 0x39E641C | 0x2E24D2C |  | `public ItemData cTO(string e)` |
| 0x39E6310 | 0x2E24C34 |  | `public bool cTt(string e, out ItemData f)` |
| 0x39E60C0 | 0x2E249F8 |  | `public bool cTr(string e, out SkinData f, out ItemData F)` |
| 0x39E6544 | 0x2E24E3C |  | `public string cTN(SkinData e, ItemData f)` |
| 0x39E6684 | 0x2E24F58 |  | `public int cTq(string e, string f)` |
| 0x39E67D0 | 0x2E250A4 |  | `public bool cTs(int e, out RecipeConfig f)` |
| 0x39E6890 | 0x2E250C4 |  | `public bool cTC(string e, out RecipeConfig f)` |
| 0x39E69A8 | 0x2E250E4 |  | `public List<string> cTZ()` |
| 0x39E6B08 | 0x2E250EC |  | `public List<ItemData> cTj()` |
| 0x39E6C64 | 0x2E25224 |  | `public int cTa()` |
| 0x39E6CCC | 0x2E2522C |  | `public void .ctor()` |

</details>

### public class `ItemDragHandler` : Lc<ItemDragHandler>  
`TypeDefIndex 2834`

| offset | field |
|---|---|
| 0x20 | `private float m_DraggedItemScale;` |
| 0x24 | `private float m_DraggedItemAlpha;` |
| 0x28 | `private KeyCode m_SplitKey;` |
| 0x30 | `private ItemContainer[] ORb;` |
| 0x38 | `private bool ORl;` |
| 0x40 | `private Item ORx;` |
| 0x48 | `private RectTransform ORK;` |
| 0x50 | `private Canvas ORG;` |
| 0x58 | `private RectTransform ORP;` |
| 0x60 | `private Vector2 ORD;` |
| 0x68 | `private Slot ORn;` |
| - | `private bool moveSent;` |

Properties: `public bool spo { get; }`

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E25268 |  | `public bool get_spo()` |
| 0x39EBD68 | 0x2E25270 |  | `private void Start()` |
| 0x39EBFD0 | 0x2E2552C | 5 | `protected override void OnDestroy()` |
| 0x39EC0E4 | 0x2E258D8 |  | `private void coj()` |
| 0x39EC298 | 0x2E25798 |  | `private void coa()` |
| 0x39EC344 | 0x2E259CC |  | `private void coQ(PointerEventData e, Slot f, ItemContainer F)` |
| 0x39EC614 | 0x2E25BB4 |  | `private void coH(PointerEventData e, Slot f, ItemContainer F)` |
| 0x39EC708 | 0x2E25CB8 |  | `private void coi(PointerEventData e, Slot f, ItemContainer F)` |
| - | 0x2E25F4C |  | `internal static bool CanDropInto(Slot source, Slot target, Item item)` |
| 0x39ECA64 | 0x2E26154 |  | `private bool cow(Slot e)` |
| 0x39ECAFC | 0x2E26244 |  | `private void coJ(Slot e, Slot f)` |
| 0x39ECC28 | 0x2E2634C |  | `private void coX(Slot e, Slot f)` |
| 0x39EC158 | 0x2E25950 |  | `private void coT(Slot e)` |
| 0x39ECD30 | 0x2E263B0 |  | `public void .ctor()` |

</details>

### public class `ItemHolder`  
`TypeDefIndex 2835`

| offset | field |
|---|---|
| 0x10 | `public XN<ItemHolder> Updated;` |
| 0x20 | `public string container;` |
| 0x28 | `public string category;` |
| 0x30 | `public string requiredItem;` |
| 0x38 | `public string specialItem;` |
| 0x40 | `public bool onlyGive;` |
| 0x44 | `private int ORT;` |
| 0x48 | `private Slot ORL;` |
| 0x50 | `public bool isNew;` |
| - | `private Item <ORX>k__BackingField;` |

Properties: `public bool sgK { get; }`; `public Item ORX { get; set; }`; `public int sgG { get; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E26410 |  | `public bool get_sgK()` |
| - | 0x2E26430 |  | `public Item get_ORX()` |
| - | 0x2E26438 |  | `private void set_ORX(Item value)` |
| - | 0x2E26440 |  | `public int get_sgG()` |
| 0x39E6D24 | 0x2E26448 |  | `public static bool cTJ(ItemHolder e)` |
| 0x39E6D30 | 0x2E22804 |  | `public void .ctor()` |
| 0x39E6DC0 | 0x2E26454 |  | `public void .ctor(string _container)` |
| 0x39E6E64 | 0x2E264F0 |  | `public bool cTX(ItemData e, int f, out int F, List<Xj.Value> d, int c = -1)` |
| 0x39E7168 | 0x2E26320 |  | `public bool cTT(Item e, out int f)` |
| 0x39E73E8 | 0x2E2166C |  | `public void cTL(Item e, bool f = true)` |
| 0x39E7638 | 0x2E26868 |  | `public void cTo(Item e)` |
| 0x39E7884 | 0x2E2686C |  | `public void cTy(int e, out int f, bool F = true)` |
| 0x39E7960 | 0x2E26874 |  | `public void cTz(int e, bool f = true)` |
| 0x39E7A1C | 0x2E26878 |  | `private void cTh(Xj.Value e)` |
| 0x39E7A70 | 0x2E26920 |  | `private void cTB()` |
| 0x39E7AC4 | 0x2E269C8 |  | `public void cTm(int e)` |
| 0x39E7ACC | 0x2E269D0 |  | `public void cTR(Slot e)` |
| 0x39E7354 | 0x2E26748 |  | `public bool cTb(Item e)` |
| 0x39E7088 | 0x2E2666C |  | `public bool cTl(ItemData e)` |
| 0x39E7AD4 | 0x2E269D8 |  | `private bool cTx(string e)` |

</details>

### public class `ItemPickup` : Xb  
`TypeDefIndex 2837`

| offset | field |
|---|---|
| - | `private bool hasServerPose;` |
| - | `private Vector3 serverPosition;` |
| - | `private Quaternion serverRotation;` |
| 0x88 | `private ItemPickup.Xl m_PickupMethod;` |
| 0x90 | `private AudioClip m_OnDestroySound;` |
| 0x98 | `private float m_OnDestroyVolume;` |
| 0x9C | `private bool randomSkin;` |
| 0x9D | `public bool isNew;` |
| 0x9E | `private bool OlS;` |
| 0xA0 | `public string item;` |
| 0xA8 | `public int amount;` |
| 0xAC | `public int skin;` |
| - | `private readonly Dictionary<Renderer, Material[]> pickupBaseMaterials;` |
| - | `private QT pickupVisual;` |
| - | `private string visualItem;` |
| - | `private int visualSkin;` |
| - | `private int visualAmount;` |
| - | `private Item <Olv>k__BackingField;` |

Properties: `public Item Olv { get; set; }`; `public string svz { get; set; }`; `public int svh { get; set; }`; `public int svB { get; set; }`

<details><summary>methods (25)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E269E0 |  | `private static void .cctor()` |
| - | 0x2E26AC8 |  | `private static void ReadServerPose(vd component, vo reader, vt connection)` |
| - | 0x2E26BC0 |  | `private void LateUpdate()` |
| - | 0x2E26E0C |  | `private void Awake()` |
| - | 0x2E26E10 |  | `private void ConfigureNetworkBody()` |
| - | 0x2E27050 |  | `private void RefreshPickupVisual()` |
| - | 0x2E275E0 |  | `private void ReleasePickupVisual()` |
| - | 0x2E277A8 |  | `private void PlayPickupSound()` |
| - | 0x2E278C4 |  | `public Item get_Olv()` |
| - | 0x2E278CC |  | `private void set_Olv(Item value)` |
| 0x39FE000 | 0x2E278D4 |  | `public string get_svz()` |
| 0x39FE008 | 0x2E278DC |  | `public void set_svz([In] string value)` |
| 0x39FE0C0 | 0x2E278E0 |  | `public int get_svh()` |
| 0x39FDAA4 | 0x2E278E8 |  | `public void set_svh([In] int value)` |
| 0x39FE0C8 | 0x2E278EC |  | `public int get_svB()` |
| 0x39FDB5C | 0x2E278F4 |  | `public void set_svB([In] int value)` |
| 0x39FD8DC | 0x2E278F8 | 13 | `public override void dHP()` |
| 0x39FDC14 | 0x2E278FC | 11 | `public override void Fsv()` |
| 0x39FDD78 | 0x2E27900 | 26 | `public override void FqM(PlayerManager e)` |
| 0x39FDDE8 | 0x2E27A20 | 10 | `public override void diJ()` |
| - | 0x2E27A6C |  | `public override void cgh()` |
| 0x39FDF78 | 0x2E27A90 |  | `public void .ctor()` |
| 0x39FDFF8 | 0x2E27B20 | 12 | `public override bool Fuk()` |
| 0x39FE0D0 | 0x2E27B28 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x39FE18C | 0x2E27B2C | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `Lamp` : Xb, UC  
`TypeDefIndex 2839`

| offset | field |
|---|---|
| 0x80 | `private Lamp.Xx m_Mode;` |
| 0x88 | `private GameObject m_LightOn;` |
| 0x90 | `private GameObject m_LightOff;` |
| 0x98 | `private AudioSource m_AudioSource;` |
| 0xA0 | `private SoundPlayer m_ToggleAudio;` |
| 0xA8 | `public bool lighting;` |

Properties: `public bool svm { get; set; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FE488 | 0x2E27BE8 |  | `public bool get_svm()` |
| 0x39FE490 | 0x2E27BF0 |  | `public void set_svm([In] bool value)` |
| 0x39FE310 | 0x2E27BFC | 11 | `public override void Fsv()` |
| 0x39FE350 | 0x2E27CC8 |  | `private void cmt(bool e)` |
| 0x39FE474 | 0x2E27DBC | 34 | `public bool FOL()` |
| 0x39FE47C | 0x2E27DC4 |  | `public void .ctor()` |
| 0x39FE480 | 0x2E27DCC | 12 | `public override bool Fuk()` |
| 0x39FE54C | 0x2E27CD0 |  | `protected void cmq(bool e)` |
| 0x39FE5B0 | 0x2E27DD4 |  | `protected static void cms(vd e, vo f, vt F)` |
| 0x39FE6EC | 0x2E27E68 |  | `private static void .cctor()` |
| 0x39FE818 | 0x2E27F50 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x39FE878 | 0x2E27FB0 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `LerpControlledBob`  
`TypeDefIndex 2842`

| offset | field |
|---|---|
| 0x14 | `private float m_MaxBobDuration;` |
| 0x18 | `private float m_MaxBobAmount;` |
| 0x20 | `private AnimationCurve m_DurationCurve;` |
| 0x28 | `private AnimationCurve m_DisplacementCurve;` |
| - | `private float <OGr>k__BackingField;` |

Properties: `public float OGr { get; set; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E28004 |  | `public float get_OGr()` |
| - | 0x2E2800C |  | `private void set_OGr(float value)` |
| 0x3A1473C | 0x2E28014 |  | `public IEnumerator cKY(float e)` |
| 0x3A147E0 | 0x2E280B8 |  | `public void .ctor()` |

</details>

### public class `LevelData`  
`TypeDefIndex 2843`

| offset | field |
|---|---|
| 0x10 | `public int lvl;` |
| 0x14 | `public int exp;` |
| 0x18 | `public int ratio;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A42110 | 0x2E2832C |  | `public void .ctor()` |

</details>

### public class `LifeInfo` : MonoBehaviour  
`TypeDefIndex 2844`

| offset | field |
|---|---|
| 0x20 | `public Text aliveTime;` |
| 0x28 | `public Text killerName;` |
| 0x30 | `public Text killerWeapon;` |
| 0x38 | `public Text killerDistance;` |
| 0x40 | `public GameObject weaponRoot;` |
| 0x48 | `public GameObject distanceRoot;` |
| 0x50 | `public Image weaponIcon;` |
| 0x58 | `public ItemDatabase itemDatabase;` |
| 0x60 | `private Button reportButton;` |
| 0x68 | `private Action OPq;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A223A8 | 0x2E28334 |  | `private void OnEnable()` |
| 0x3A22438 | 0x2E28450 |  | `private void OnDisable()` |
| 0x3A224C8 | 0x2E28524 |  | `public void cPC(float e, string f, string F, float d, Action c)` |
| 0x3A22768 | 0x2E28A64 |  | `private void cPZ()` |
| 0x3A22784 | 0x2E28A80 |  | `public void .ctor()` |

</details>

### public struct `LootDescription`  
`TypeDefIndex 2845`

| offset | field |
|---|---|
| 0x0 | `public LootItem Loot;` |
| 0x8 | `public int ReceivedAmount;` |

### public class `LootDestroyable` : vd  
`TypeDefIndex 2846`

| offset | field |
|---|---|
| 0x68 | `protected int m_Capacity;` |
| 0x78 | `public PieceVitals m_PieceVitals;` |
| 0x80 | `public XE m_EntityHandler;` |
| 0x88 | `public float health;` |
| 0x8C | `public float maxHealth;` |

Properties: `public ItemHolder[] OPs { get; set; }`; `public float sSl { get; set; }`; `public float sSx { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A2278C | 0x2E28A88 |  | `public ItemHolder[] get_OPs()` |
| 0x3A22794 | 0x2E28A90 |  | `private void set_OPs(ItemHolder[] value)` |
| 0x3A227B4 | 0x2E28A94 |  | `public float get_sSl()` |
| 0x3A227BC | 0x2E28A9C |  | `public void set_sSl([In] float value)` |
| 0x3A22874 | 0x2E28AA0 |  | `public float get_sSx()` |
| 0x3A2287C | 0x2E28AA8 |  | `public void set_sSx([In] float value)` |
| 0x3A2279C | 0x2E28AAC |  | `public void .ctor()` |
| 0x3A227AC | 0x2E28AB4 | 12 | `public override bool Fuk()` |
| 0x3A22934 | 0x2E28ABC | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A229C0 | 0x2E28B48 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `LootItem` : ISerializationCallbackReceiver  
`TypeDefIndex 2847`

| offset | field |
|---|---|
| 0x10 | `public string ItemName;` |
| 0x18 | `public float Amount;` |
| 0x1C | `public float StartAmount;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FF538 | 0x2E28BBC |  | `public void .ctor(string item = "null", int amt = 0)` |
| 0x39FF578 | 0x2E28BC4 |  | `public void cmh(PlayerManager e, out int f, float F)` |
| 0x39FF650 | 0x2E28BCC | 5 | `public void OnAfterDeserialize()` |
| 0x39FF65C | 0x2E28BD0 | 4 | `public void OnBeforeSerialize()` |

</details>

### public class `LootObject` : Xb, Xa  
`TypeDefIndex 2850`

| offset | field |
|---|---|
| 0x80 | `public ItemContainer inventory;` |
| 0x88 | `public bool isLootable;` |
| 0x89 | `public bool destroyOnEmpty;` |
| 0x8A | `public bool isNew;` |
| 0x98 | `protected int m_Capacity;` |
| 0xA0 | `private Transform m_Cover;` |
| 0xA8 | `private float m_OpenSpeed;` |
| 0xAC | `private float m_ClosedRotation;` |
| 0xB0 | `private float m_OpenRotation;` |
| 0xB8 | `protected string panelName;` |
| 0xC0 | `private BuildingPiece m_Piece;` |
| 0xC8 | `private bool m_DropOnDestroy;` |
| 0xD0 | `private GameObject m_LootBag;` |
| 0xD8 | `private float Oxc;` |
| 0xDC | `private int OxU;` |
| 0xE0 | `private bool m_SaveItems;` |
| - | `private ItemHolder[] <Oxd>k__BackingField;` |

Properties: `public ItemHolder[] Oxd { get; set; }`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E28BD4 |  | `public ItemHolder[] get_Oxd()` |
| - | 0x2E28BDC |  | `private void set_Oxd(ItemHolder[] value)` |
| 0x39FE934 | 0x2E28BE4 | 27 | `public override void Fae(PlayerManager e)` |
| 0x39FE94C | 0x2E28BE8 |  | `private void Awake()` |
| - | 0x2E28D48 |  | `private void ConfigureBalloonCrateBody()` |
| 0x39FEA7C | 0x2E28EE4 | 34 | `public virtual bool cmi(PlayerManager e, string f = "", bool F = true)` |
| 0x39FEA84 | 0x2E28EEC | 31 | `public override void dbx(PlayerManager e)` |
| - | 0x2E28EF0 |  | `private IEnumerator cmw(bool e)` |
| 0x39FEB30 | 0x2E28F98 |  | `private void cmJ(bool e)` |
| 0x39FEC54 | 0x2E29044 | 33 | `public override bool drE(out string e)` |
| 0x39FEC74 | 0x2E29064 |  | `public void .ctor()` |
| 0x39FED08 | 0x2E2906C | 12 | `public override bool Fuk()` |
| 0x39FED10 | 0x2E28FA0 |  | `protected void cmX(bool e)` |
| 0x39FEDB8 | 0x2E29074 |  | `protected static void cmT(vd e, vo f, vt F)` |
| 0x39FEEF4 | 0x2E29108 |  | `private static void .cctor()` |

</details>

### public class `LootOnDeath` : XU  
`TypeDefIndex 2851`

| offset | field |
|---|---|
| 0x88 | `private LootObject m_LootContainer;` |

Properties: `public LootObject sSc { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A0A668 | 0x2E294C4 |  | `public LootObject get_sSc()` |
| 0x3A0A670 | 0x2E294CC |  | `public void set_sSc(LootObject value)` |
| 0x3A0A678 | 0x2E294D0 |  | `private void Start()` |
| 0x3A0A71C | 0x2E294D4 |  | `private void cbv()` |
| 0x3A0A73C | 0x2E294D8 |  | `public void .ctor()` |
| 0x3A0A744 | 0x2E294E0 | 12 | `public override bool Fuk()` |

</details>

### public class `MineableAnimal` : MineableObject  
`TypeDefIndex 2852`

| offset | field |
|---|---|
| 0xD0 | `public XE m_EventHandler;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A22ABC | 0x2E294E8 |  | `public void .ctor()` |
| 0x3A22B14 | 0x2E29548 | 12 | `public override bool Fuk()` |

</details>

### public class `MineableColliderBridge` : MonoBehaviour  
`TypeDefIndex 2853`

Properties: `public MineableStone MineableStone { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FF190 | 0x2E29550 |  | `public MineableStone get_MineableStone()` |
| 0x39FF198 | 0x2E29558 |  | `private void set_MineableStone(MineableStone value)` |
| 0x39FF1A0 | 0x2E2955C |  | `public void .ctor()` |

</details>

### public class `MineableCompositeStone` : MineableStone  
`TypeDefIndex 2854`

| offset | field |
|---|---|
| 0xE0 | `private List<GameObject> pieces;` |
| 0xE8 | `private byte OxY;` |
| 0xF0 | `public Action<byte, byte> _Mirror_SyncVarHookDelegate_hpRelative;` |

Properties: `public byte svl { get; set; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FF3BC | 0x2E29564 |  | `public byte get_svl()` |
| 0x39FF3C4 | 0x2E2956C |  | `public void set_svl([In] byte value)` |
| 0x39FF1A8 | 0x2E29584 |  | `private void cmL(byte e, byte f)` |
| 0x39FF1B0 | 0x2E2958C |  | `private void cmo(byte e)` |
| 0x39FF2D4 | 0x2E2970C |  | `public void .ctor()` |
| 0x39FF3B4 | 0x2E297F0 | 12 | `public override bool Fuk()` |
| 0x39FF428 | 0x2E297F8 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x39FF488 | 0x2E29858 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `MineableObject` : vd  
`TypeDefIndex 2855`

| offset | field |
|---|---|
| 0x68 | `public Xr Destroyed;` |
| 0x70 | `private FPTool.Xh m_RequiredToolPurpose;` |
| 0x74 | `private float m_Resistance;` |
| 0x78 | `private float m_CurrentHealth;` |
| 0x80 | `protected GameObject m_DestroyedObject;` |
| 0x88 | `protected GameObject m_DestroyedNetworkObject;` |
| 0x90 | `protected Vector3 m_DestroyedObjectOffset;` |
| 0xA0 | `protected List<LootItem> m_Loot;` |
| 0xA8 | `protected List<LootItem> m_FinishBonus;` |
| 0xB0 | `protected float OxW;` |
| 0xB8 | `protected Transform OxE;` |
| 0xC0 | `public float fractionRemaining;` |
| 0x0 | `public static Dictionary<uint, MineableObject> objectsList;` |
| 0xC4 | `public int m_Experience;` |
| 0xC8 | `private XG OxA;` |

Properties: `public float svx { get; }`; `public GameObject svK { get; }`; `public Vector3 svG { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FF660 | 0x2E298D8 |  | `public float get_svx()` |
| 0x39FF668 | 0x2E298E0 |  | `public GameObject get_svK()` |
| 0x39FF670 | 0x2E298E8 |  | `public Vector3 get_svG()` |
| 0x39FF67C | 0x2E298F4 |  | `public void cmb()` |
| 0x39FF794 | 0x2E29A6C |  | `protected void DestroyNow()` |
| 0x39FF960 | 0x2E29540 |  | `public void .ctor()` |
| 0x39FF9EC | 0x2E29A70 |  | `private static void .cctor()` |
| 0x39FFB8C | 0x2E29BCC | 12 | `public override bool Fuk()` |
| 0x39FFB94 | 0x2E298F8 |  | `protected void cml()` |
| 0x39FFD08 | 0x2E29BD4 |  | `protected static void cmx(vd e, vo f, vt F)` |

</details>

### public class `MineableStone` : MineableObject  
`TypeDefIndex 2856`

| offset | field |
|---|---|
| 0xD0 | `private int Oxt;` |
| 0xD8 | `private Lb Oxr;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A027C0 | 0x2E29C54 |  | `public void cRe(int e, Lb f)` |
| 0x39FF360 | 0x2E29798 |  | `public void .ctor()` |
| 0x3A027D0 | 0x2E29C64 | 12 | `public override bool Fuk()` |

</details>

### public class `MineableTree` : MineableObject  
`TypeDefIndex 2857`

| offset | field |
|---|---|
| 0xD0 | `private List<Collider> colliders;` |
| 0xD8 | `private List<Renderer> renderers;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A027D8 | 0x2E29C6C |  | `public void cRf(Vector3 e)` |
| 0x3A0291C | 0x2E29FD8 | 11 | `public override void Fsv()` |
| 0x3A02948 | 0x2E2A004 |  | `private void cRF(bool e)` |
| 0x3A02AA0 | 0x2E2A190 |  | `private void cRd(bool e)` |
| 0x3A02BF8 | 0x2E2A31C |  | `public void .ctor()` |
| 0x3A02C4C | 0x2E2A414 | 12 | `public override bool Fuk()` |
| 0x3A02C54 | 0x2E29C70 |  | `protected void cRc(Vector3 e)` |
| 0x3A02F80 | 0x2E2A41C |  | `protected static void cRU(vd e, vo f, vt F)` |
| 0x3A030B8 | 0x2E2A4AC |  | `private static void .cctor()` |

</details>

### public class `MouseLook` : MonoBehaviour  
`TypeDefIndex 2858`

| offset | field |
|---|---|
| - | `private const float OBb = 0.1;` |
| 0x20 | `private XA m_EventHandler;` |
| 0x28 | `private Transform m_LookRoot;` |
| 0x30 | `private bool m_Invert;` |
| 0x31 | `private bool m_CanUnlock;` |
| 0x34 | `public float m_Sensitivity;` |
| 0x38 | `private Vector2 m_DefaultLookLimits;` |
| 0x40 | `private Vector2 m_CrouchLookLimits;` |
| 0x48 | `public Vector2 m_CurrentMouseLook;` |
| 0x50 | `private float OBl;` |
| 0x54 | `private float OBx;` |
| 0x58 | `private float OBK;` |
| 0x5C | `private Vector2 OBG;` |
| 0x64 | `private Vector2 OBP;` |
| 0x6C | `private bool OBD;` |
| 0x70 | `private float OBn;` |
| 0x74 | `private Vector2 OBV;` |
| - | `private bool OBg_;` |
| - | `private Jp OBp_;` |

Properties: `public float sVH { get; }`; `public Vector2 sVi { get; }`; `public bool OBg { get; set; }`; `public Jp OBp { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DA528 | 0x2E2A594 |  | `public float get_sVH()` |
| 0x39DA530 | 0x2E2A59C |  | `public Vector2 get_sVi()` |
| 0x39DA538 | 0x2E2A5A8 |  | `public bool get_OBg()` |
| 0x39DA540 | 0x2E2A5B0 |  | `private void set_OBg(bool value)` |
| 0x39DA54C | 0x2E2A5BC |  | `public Jp get_OBp()` |
| 0x39DA554 | 0x2E2A5C4 |  | `private void set_OBp(Jp value)` |
| 0x39DA55C | 0x2E2A5CC |  | `private void OnEnable()` |
| 0x39DA8C8 | 0x2E2A5D0 |  | `private void OnDisable()` |
| 0x39DA84C | 0x2E2A5D4 |  | `public void cHJ(bool e, Jp f)` |
| 0x39DAA38 | 0x2E2A69C |  | `private void cHX()` |
| 0x39DAA44 | 0x2E2A6A0 |  | `private void cHT()` |
| 0x39DAA50 | 0x2E2A6A4 |  | `private void RecoveredNoopUpdate()` |
| 0x39DAB0C | 0x2E2A6A8 |  | `private void cHL(float e)` |
| 0x39DAF7C | 0x2E2A6AC |  | `private float cHo(float e, float f, float F)` |
| 0x39DAD94 | 0x2E2A6B4 |  | `private void cHy(bool e, float f)` |
| 0x39DAFBC | 0x2E2A6B8 |  | `public void cHz(Vector2 e)` |
| 0x39DAFC8 | 0x2E2A6BC |  | `public void .ctor()` |

</details>

### public class `ParticleDestroyer` : MonoBehaviour  
`TypeDefIndex 2860`

| offset | field |
|---|---|
| 0x20 | `private float m_MinDuration;` |
| 0x24 | `private float m_MaxDuration;` |
| 0x28 | `private float OBT;` |
| 0x2C | `private bool OBL;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E2A6C4 |  | `private IEnumerator Start()` |
| 0x39D85E0 | 0x2E2A6CC |  | `public void cQM()` |
| 0x39D85EC | 0x2E2A6D0 |  | `public void .ctor()` |

</details>

### public class `PauseManager` : vd  
`TypeDefIndex 2863`

| offset | field |
|---|---|
| 0x68 | `private MapManager mapManager;` |
| 0x70 | `public Lm playersList;` |
| 0x78 | `public GameObject mainCanvas;` |
| 0x80 | `public GameObject pauseCanvas;` |
| 0x88 | `public GameObject mapCanvas;` |
| 0x90 | `public MouseLook mouseLook;` |
| 0x98 | `private HF OPC;` |
| 0xA1 | `private bool OPj;` |
| - | `private int <LastTransitionFrame>k__BackingField;` |
| - | `private const float LeaveDelay = 3;` |
| - | `private bool pauseWasOpen;` |
| - | `private float leaveCooldownEnd;` |
| - | `private PauseManager.LeaveButtonCooldown disconnectCooldown;` |
| - | `private PauseManager.LeaveButtonCooldown exitCooldown;` |

Properties: `public int LastTransitionFrame { get; set; }`; `public bool IsMapOpen { get; }`

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A22B1C | 0x2E2A700 |  | `private void Update()` |
| 0x3A1C27C | 0x2E2A948 |  | `public void SetPause(bool status)` |
| 0x3A22B20 | 0x2E2B13C |  | `public void ShowMap(bool isOpenedFromPause)` |
| - | 0x2E2B1E8 |  | `public int get_LastTransitionFrame()` |
| - | 0x2E2B1F0 |  | `private void set_LastTransitionFrame(int value)` |
| - | 0x2E2B1F8 |  | `public bool get_IsMapOpen()` |
| - | 0x2E2B030 |  | `private MapManager ResolveMap()` |
| - | 0x2E2B27C |  | `public void CloseMap()` |
| 0x3A22B58 | 0x2E2B310 |  | `private void Start()` |
| - | 0x2E2B334 |  | `private static void FixCanvas(GameObject target)` |
| - | 0x2E2B68C |  | `public void ChatUpdateStatus()` |
| 0x3A22C6C | 0x2E2B7C8 |  | `public void LeaveRoom()` |
| 0x3A22E50 | 0x2E2BA38 |  | `public void Exit()` |
| 0x3A23034 | 0x2E2BC70 |  | `public void .ctor()` |
| - | 0x2E2A704 |  | `private void UpdateLeaveCooldown()` |
| - | 0x2E2BA00 |  | `private bool CanLeave()` |
| - | 0x2E2C0EC |  | `private void OnDisable()` |
| - | 0x2E2BE8C |  | `private void ResetLeaveCooldown()` |
| 0x3A2303C | 0x2E2C0F0 | 12 | `public override bool Fuk()` |

</details>

### public class `PauseOptionsMenu` : MonoBehaviour  
`TypeDefIndex 2864`

| offset | field |
|---|---|
| - | `private PauseManager pauseManager;` |
| - | `private GameObject optionsPrefab;` |
| - | `private GameObject customizationPrefab;` |
| - | `private GameObject languagePanelPrefab;` |
| - | `private Sprite background;` |
| - | `private UniversalRendererData[] rendererDatas;` |
| - | `private int sortingOrder;` |
| - | `private GameObject root;` |
| - | `private GameObject customization;` |
| - | `private GameObject language;` |
| - | `private SettingsManager settings;` |
| - | `private GyroscopeUnsupportedPopup gyroscopePopup;` |

Properties: `public bool IsOpen { get; }`

<details><summary>methods (24)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E2C24C |  | `public bool get_IsOpen()` |
| - | 0x2E2C2D0 |  | `private void Start()` |
| - | 0x2E2C764 |  | `private void LateUpdate()` |
| - | 0x2E2C830 |  | `public void Open()` |
| - | 0x2E2AEE0 |  | `public void Close()` |
| - | 0x2E2CEEC |  | `public void OpenLanguage()` |
| - | 0x2E2D070 |  | `public void OpenControls()` |
| - | 0x2E2C374 |  | `private void AddPauseButton()` |
| - | 0x2E2C8C4 |  | `private void Build()` |
| - | 0x2E2D83C |  | `private void AddBackButton(Transform options)` |
| - | 0x2E2DFAC |  | `private void PrepareOptions(Transform options)` |
| - | 0x2E2E39C |  | `private void BindSettings(Transform body)` |
| - | 0x2E2EC6C |  | `private void SetPrivate(string field, object value)` |
| - | - |  | `private static T Find<T>(Transform parent, string path)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x387BA78 Offset: 0x3877A78 VA: 0x387BA78` |
| - | - |  | `\|-PauseOptionsMenu.Find<object>` |
| - | - |  | `*/` |
| - | 0x2E2D24C |  | `private static void SetLabel(GameObject target, string token, string english)` |
| - | 0x2E2D39C |  | `private static RectTransform NewChild(string name, Transform parent)` |
| - | 0x2E2D734 |  | `private static void Stretch(RectTransform rect)` |
| - | 0x2E2D52C |  | `private static void Cover(Image image, Sprite sprite)` |
| - | 0x2E2ED54 |  | `public void .ctor()` |

</details>

### public class `PieceVitals` : GenericVitals  
`TypeDefIndex 2865`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DE294 | 0x2E2ED64 |  | `public void .ctor()` |
| 0x39DE2A4 | 0x2E2ED6C | 12 | `public override bool Fuk()` |

</details>

### public class `PivotDisplayer` : MonoBehaviour  
`TypeDefIndex 2866`

| offset | field |
|---|---|
| 0x20 | `private Color m_Color;` |
| 0x30 | `private float m_Radius;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A14A20 | 0x2E2ED74 |  | `private void OnDrawGizmosSelected()` |
| 0x3A14A64 | 0x2E2ED78 |  | `public void .ctor()` |

</details>

### public class `PlayerDeathHandler` : vd  
`TypeDefIndex 2870`

| offset | field |
|---|---|
| 0x68 | `private PlayerManager player;` |
| 0x70 | `private GameObject m_Camera;` |
| 0x78 | `private GameObject m_Backpack;` |
| 0x80 | `private AudioSource m_AudioSource;` |
| 0x88 | `private SoundPlayer m_DeathAudio;` |
| 0x90 | `private SoundPlayer m_HitAudio;` |
| 0x98 | `private SoundPlayer m_CriticalHitAudio;` |
| 0xA0 | `public GameObject[] m_ObjectsToDisable;` |
| 0xA8 | `public Behaviour[] m_BehavioursToDisable;` |
| 0xB0 | `public Collider[] m_CollidersToDisable;` |
| 0xB8 | `public GameObject m_CharacterModel;` |
| 0xC0 | `public bool m_EnableRagdoll;` |
| 0xC8 | `public Ragdoll m_Ragdoll;` |
| 0xD0 | `private bool m_DestroyOnDeath;` |
| 0xD4 | `private float m_DestroyTimer;` |
| 0xD8 | `public bool death;` |
| - | `private bool localDeathPresented;` |
| - | `private static AudioListener deathEar;` |
| - | `private static List<AudioListener> suspendedEars;` |
| - | `private static float earVolume;` |
| - | `private static int hearingGeneration;` |
| - | `private bool earFaded;` |

Properties: `public bool sSU { get; set; }`

<details><summary>methods (28)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E2ED80 |  | `public bool get_sSU()` |
| - | 0x2E2ED88 |  | `public void set_sSU(bool value)` |
| 0x3A0A74C | 0x2E2ED94 |  | `private void Awake()` |
| 0x3A0A750 | 0x2E2ED98 | 11 | `public override void Fsv()` |
| 0x3A0A908 | 0x2E2FEE8 |  | `public void cbI(float e, string f, string F, string d, float c, int U, Vector3 Y, Vector3 W)` |
| 0x3A0AB08 | 0x2E2FEEC |  | `public void cbM(SleepingBagData[] e)` |
| 0x3A0AC2C | 0x2E3004C |  | `public void cle(bool e)` |
| 0x3A0AC90 | 0x2E300AC |  | `private bool clf(Lf.Le e)` |
| 0x3A0ACB4 | 0x2E300B4 |  | `public void .ctor()` |
| - | 0x2E300BC |  | `private static void DeathStep(Action action)` |
| 0x3A0ACBC | 0x2E3017C | 12 | `public override bool Fuk()` |
| 0x3A0AD88 | 0x2E2EF68 |  | `protected void clc(float e, string f, string F, string d, float c, int U, Vector3 Y, Vector3 W)` |
| - | 0x2E303D4 |  | `private static void DisableList(GameObject[] objects, Behaviour[] behaviours, Collider[] colliders)` |
| - | 0x2E30720 |  | `private static void Show(GameObject go)` |
| 0x3A0B500 | 0x2E3080C |  | `protected static void clU(vd e, vo f, vt F)` |
| 0x3A0B710 | 0x2E2FEF0 |  | `protected void clY(SleepingBagData[] e)` |
| 0x3A0B73C | 0x2E30810 |  | `protected static void clW(vd e, vo f, vt F)` |
| - | 0x2E30814 |  | `public static void RestoreHearing()` |
| - | 0x2E30C2C |  | `private void LateUpdate()` |
| - | 0x2E305B8 |  | `private void BeginEarFade()` |
| - | 0x2E30E78 |  | `private IEnumerator FadeEar()` |
| - | 0x2E30F0C |  | `private static void .cctor()` |
| 0x3A0BA14 | 0x2E310D0 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A0BA74 | 0x2E310D4 | 15 | `protected override void FCO(vo e, bool f)` |
| - | 0x2E31128 |  | `private void <clc>b__30_0()` |
| - | 0x2E31688 |  | `private void <clc>b__30_1()` |
| - | 0x2E3171C |  | `private void <clc>b__30_2()` |
| - | 0x2E31810 |  | `private void <clc>b__30_3()` |

</details>

### public class `PlayerInputHandler` : MonoBehaviour  
`TypeDefIndex 2871`

| offset | field |
|---|---|
| 0x20 | `public GameController controller;` |
| 0x28 | `private ScreenControlsReferenceHolder screenControlsReferenceHolder;` |
| 0x40 | `private PlayerInput OBf;` |
| 0x60 | `private bool OBF;` |
| 0x64 | `private float OBd;` |
| 0x68 | `private float OBc;` |
| 0x6C | `private float OBU;` |
| 0x70 | `private ds OBY;` |
| 0x78 | `private int OBW;` |
| 0x7C | `private bool OBE;` |
| - | `private PlayerManager <OhM>k__BackingField;` |
| - | `private XA <OBe>k__BackingField;` |
| - | `private bool aimBlockedUntilRelease;` |
| - | `private bool attackBlockedUntilRelease;` |
| - | `private bool <IsAimHeld>k__BackingField;` |

Properties: `private PlayerManager OhM { get; set; }`; `private XA OBe { get; set; }`; `public PlayerInput sVO { get; }`; `public Vector2 sVt { get; }`; `public bool IsJumpHeld { get; }`; `public bool IsCrouchHeld { get; }`; `public bool IsSprintHeld { get; }`; `public bool IsAimHeld { get; set; }`; `public bool IsAttackHeld { get; }`

<details><summary>methods (60)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E32448 |  | `private PlayerManager get_OhM()` |
| - | 0x2E32450 |  | `private void set_OhM(PlayerManager value)` |
| - | 0x2E32458 |  | `private XA get_OBe()` |
| - | 0x2E32460 |  | `private void set_OBe(XA value)` |
| 0x39D45E4 | 0x2E32468 |  | `public PlayerInput get_sVO()` |
| 0x39D45F0 | 0x2E32474 |  | `public Vector2 get_sVt()` |
| 0x39D4630 | 0x2E32480 |  | `private void Awake()` |
| 0x39D4728 | 0x2E32484 |  | `private void Start()` |
| 0x39D48D8 | 0x2E3263C |  | `public void cQJ()` |
| - | 0x2E311B8 |  | `public static PlayerInputHandler ForPlayer(PlayerManager player)` |
| - | 0x2E32648 |  | `private bool Held(string name)` |
| - | 0x2E3267C |  | `public bool get_IsJumpHeld()` |
| - | 0x2E326C4 |  | `public bool get_IsCrouchHeld()` |
| - | 0x2E3270C |  | `public bool get_IsSprintHeld()` |
| - | 0x2E32754 |  | `public void CancelSprint()` |
| - | 0x2E3280C |  | `public void CancelCrouch()` |
| - | 0x2E31320 |  | `public void CancelAttackUntilRelease()` |
| - | 0x2E31548 |  | `public void CancelAimUntilRelease()` |
| - | 0x2E32904 |  | `public bool get_IsAimHeld()` |
| - | 0x2E3290C |  | `private void set_IsAimHeld(bool value)` |
| - | 0x2E32918 |  | `public void AimAction(bool held)` |
| - | 0x2E32A2C |  | `private void OnDisable()` |
| - | 0x2E32ABC |  | `public bool get_IsAttackHeld()` |
| 0x39D48E4 | 0x2E32AC4 |  | `private void cQX()` |
| 0x39D48F0 | 0x2E32AD0 |  | `private void Update()` |
| 0x39D4968 | 0x2E32DEC |  | `private void cQT()` |
| 0x39D4F54 | 0x2E32DF0 |  | `private void cQL(InputDevice e, InputDeviceChange f)` |
| 0x39D4F28 | 0x2E32DF4 |  | `private bool cQo()` |
| 0x39D4E48 | 0x2E32DFC |  | `private bool cQy(Vector2 e)` |
| 0x39D4F60 | 0x2E32E04 |  | `private void cQz()` |
| 0x39D4FBC | 0x2E32E08 |  | `public void InventoryAction()` |
| 0x39D5048 | 0x2E32EA4 |  | `public void ViewWeaponAction()` |
| 0x39D5124 | 0x2E32F44 |  | `public void InteractAction(bool hold)` |
| 0x39D4DD4 | 0x2E33038 |  | `public void cQh(bool e)` |
| 0x39D4EB0 | 0x2E33060 |  | `public void cQB(bool e)` |
| 0x39D51F0 | 0x2E33088 |  | `public void cQm(bool e)` |
| 0x39D5244 | 0x2E330DC |  | `public void AttackAction(bool hold)` |
| 0x39D5458 | 0x2E33518 |  | `public void ReloadAction()` |
| 0x39D5478 | 0x2E335D0 |  | `public void PlaceObject()` |
| 0x39D551C | 0x2E33658 |  | `public void RotateObject()` |
| 0x39D553C | 0x2E336E0 |  | `public void ExitBuildMode()` |
| 0x39D55E0 | 0x2E338B0 |  | `public void UpgradeObject()` |
| 0x39D5600 | 0x2E33938 |  | `public void PickupObject()` |
| 0x39D5620 | 0x2E339C0 |  | `public void DemolishObject()` |
| 0x39D5640 | 0x2E33A48 |  | `public void KeyAction()` |
| 0x39D5660 | 0x2E33AD0 |  | `public void SetCarAccel(float i)` |
| 0x39D567C | 0x2E33BF8 |  | `public void SetCarBrake(float i)` |
| 0x39D5698 | 0x2E33D20 |  | `public void SetCarSteer(float i)` |
| 0x39D56B4 | 0x2E33E48 |  | `public void SetHeliThrottle(float i)` |
| 0x39D56D0 | 0x2E33F70 |  | `public void SetHeliTurn(float i)` |
| 0x39D56EC | 0x2E34098 |  | `public void ExitVehicle()` |
| 0x39D5708 | 0x2E3418C |  | `public void cQR(PlayerManager e)` |
| 0x39D5A10 | 0x2E34230 |  | `private void cQb()` |
| 0x39D5A18 | 0x2E34238 |  | `private void cQl()` |
| 0x39D4DFC | 0x2E3423C |  | `private Vector2 cQx()` |
| 0x39D5D18 | 0x2E34248 |  | `private Vector2 cQK()` |
| 0x39D5D60 | 0x2E34254 |  | `private void OnDestroy()` |
| 0x39D5E18 | 0x2E3429C |  | `public void .ctor()` |
| - | 0x2E342A4 |  | `private void <Start>b__23_0(InputAction.CallbackContext context)` |
| - | 0x2E34500 |  | `private void <Start>b__23_1(InputAction.CallbackContext context)` |

</details>

### public class `PlayerInventory` : vd  
`TypeDefIndex 2873`

| offset | field |
|---|---|
| 0x68 | `public PlayerManager player;` |
| 0x98 | `private int hotbarIndex;` |
| 0x9C | `private int m_InventorySize;` |
| 0xA0 | `private int m_HotbarSize;` |
| 0xA8 | `public PlayerModelInfo playerModelInfo;` |
| 0xB0 | `private Vector3 m_DropOffset;` |
| 0xBC | `private float m_DropAngularFactor;` |
| 0xC0 | `private float m_DropSpeed;` |
| 0xC8 | `public Hotbar hotbar;` |

Properties: `public ItemContainer OPw { get; set; }`; `public ItemContainer OPJ { get; set; }`; `public EventShopUI OPX { get; set; }`; `public ItemContainer[] OPT { get; set; }`; `public List<ItemHolder> OPL { get; set; }`; `public int OPo { get; set; }`

<details><summary>methods (71)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A2E514 | 0x2E34508 |  | `public ItemContainer get_OPw()` |
| 0x3A2E51C | 0x2E34510 |  | `private void set_OPw(ItemContainer value)` |
| 0x3A2E524 | 0x2E34514 |  | `public ItemContainer get_OPJ()` |
| 0x3A2E52C | 0x2E3451C |  | `private void set_OPJ(ItemContainer value)` |
| 0x3A2E534 | 0x2E34520 |  | `public EventShopUI get_OPX()` |
| 0x3A2E53C | 0x2E34528 |  | `private void set_OPX(EventShopUI value)` |
| 0x3A2E544 | 0x2E3452C |  | `public ItemContainer[] get_OPT()` |
| 0x3A2E54C | 0x2E34534 |  | `private void set_OPT(ItemContainer[] value)` |
| 0x3A2E554 | 0x2E34538 |  | `public List<ItemHolder> get_OPL()` |
| 0x3A2E55C | 0x2E34540 |  | `private void set_OPL(List<ItemHolder> value)` |
| 0x3A2E564 | 0x2E34544 |  | `public int get_OPo()` |
| 0x3A2E56C | 0x2E3454C |  | `private void set_OPo(int value)` |
| 0x3A2E574 | 0x2E34550 |  | `private void Awake()` |
| 0x3A2E998 | 0x2E34554 |  | `private void cnZ()` |
| 0x3A2EA80 | 0x2E34558 |  | `public int cnj(Item e, ItemContainer f, bool F = false, bool d = false)` |
| 0x3A2EA88 | 0x2E34560 |  | `public void cna(int e, int f)` |
| 0x3A2EBC8 | 0x2E34564 |  | `public void cnQ()` |
| 0x3A2ECD8 | 0x2E34568 |  | `public void cnH(int e, int f)` |
| 0x3A2EE18 | 0x2E3456C |  | `public int cni(string e)` |
| 0x3A2EF24 | 0x2E34790 |  | `public bool cnw(string e, int f, bool F = false)` |
| 0x3A2EF2C | 0x2E34798 |  | `public int cnJ(string e, int f, bool F = false)` |
| 0x3A2EF34 | 0x2E347A0 |  | `public void cnX(string e, int f, string F, int d)` |
| 0x3A2F0A4 | 0x2E34954 |  | `public int cnT(int e)` |
| 0x3A2F0D0 | 0x2E34964 |  | `public void cnL(string e, int f)` |
| 0x3A2F210 | 0x2E34AE8 |  | `public void cno(string e, int f, float F, int d, int c, int U)` |
| 0x3A2F3B0 | 0x2E34AEC |  | `public void cny(int e, float f, int F)` |
| 0x3A2F50C | 0x2E34AF0 |  | `public void cnz(int e, float f, int F)` |
| 0x3A2F668 | 0x2E34AF4 |  | `public void cnh(int e)` |
| 0x3A2F78C | 0x2E34C54 |  | `public void cnB(int e)` |
| 0x3A2F8B0 | 0x2E34C58 |  | `public bool cnm(out Item e)` |
| 0x3A2F978 | 0x2E34C78 |  | `public bool cnR(string e, out Item f)` |
| 0x3A2F9F4 | 0x2E34C98 |  | `public bool cnb(bool e)` |
| 0x3A2F9FC | 0x2E34CA0 |  | `public void cnl(bool e)` |
| 0x3A2FB20 | 0x2E34CA4 |  | `public void cnx(string e, int f)` |
| 0x3A2FC60 | 0x2E34E28 |  | `public void cnK(string e)` |
| 0x3A2FD84 | 0x2E34E2C |  | `public void cnG(string e, int f, int F)` |
| 0x3A2FED8 | 0x2E34FC4 |  | `public void cnP(Item e)` |
| 0x3A2FEDC | 0x2E34FC8 |  | `private bool cnD(bool e = true)` |
| 0x3A30000 | 0x2E34FD0 |  | `private bool cnn(string e)` |
| 0x3A30114 | 0x2E34FD8 | 10 | `public override void diJ()` |
| 0x3A301CC | 0x2E34FDC |  | `public void .ctor()` |
| 0x3A301F4 | 0x2E34FE4 | 12 | `public override bool Fuk()` |
| 0x3A301FC | 0x2E34FEC |  | `protected void cnV(int e, int f)` |
| 0x3A30234 | 0x2E3513C |  | `protected static void cng(vd e, vo f, vt F)` |
| 0x3A30380 | 0x2E351E0 |  | `protected void cnp()` |
| 0x3A3039C | 0x2E351E4 |  | `protected static void cnv(vd e, vo f, vt F)` |
| 0x3A304C0 | 0x2E351E8 |  | `protected void cnS(int e, int f)` |
| 0x3A304F8 | 0x2E35338 |  | `protected static void cnI(vd e, vo f, vt F)` |
| 0x3A30644 | 0x2E353DC |  | `protected void cnM(string e, int f, string F, int d)` |
| 0x3A30648 | 0x2E353E0 |  | `protected static void cVe(vd e, vo f, vt F)` |
| 0x3A307D4 | 0x2E353E4 |  | `protected void cVf(string e, int f)` |
| 0x3A307D8 | 0x2E353E8 |  | `protected static void cVF(vd e, vo f, vt F)` |
| 0x3A3094C | 0x2E353EC |  | `protected void cVd(string e, int f, float F, int d, int c, int U)` |
| 0x3A30B34 | 0x2E353F0 |  | `protected static void cVc(vd e, vo f, vt F)` |
| 0x3A30CEC | 0x2E353F4 |  | `protected void cVU(int e, float f, int F)` |
| 0x3A30E60 | 0x2E353F8 |  | `protected static void cVY(vd e, vo f, vt F)` |
| 0x3A30FD0 | 0x2E353FC |  | `protected void cVW(int e, float f, int F)` |
| 0x3A31130 | 0x2E35400 |  | `protected static void cVE(vd e, vo f, vt F)` |
| 0x3A312A0 | 0x2E35404 |  | `protected void cVA(int e)` |
| 0x3A312A4 | 0x2E35408 |  | `protected static void cVu(vd e, vo f, vt F)` |
| 0x3A3140C | 0x2E3540C |  | `protected void cVk(int e)` |
| 0x3A314A8 | 0x2E354A8 |  | `protected static void cVO(vd e, vo f, vt F)` |
| 0x3A315E8 | 0x2E35540 |  | `protected void cVt(bool e)` |
| 0x3A3164C | 0x2E35544 |  | `protected static void cVr(vd e, vo f, vt F)` |
| 0x3A31788 | 0x2E35548 |  | `protected void cVN(string e, int f)` |
| 0x3A3178C | 0x2E3554C |  | `protected static void cVq(vd e, vo f, vt F)` |
| 0x3A31900 | 0x2E35550 |  | `protected void cVs(string e)` |
| 0x3A319CC | 0x2E35644 |  | `protected static void cVC(vd e, vo f, vt F)` |
| 0x3A31B0C | 0x2E356DC |  | `protected void cVZ(string e, int f, int F)` |
| 0x3A31B10 | 0x2E356E0 |  | `protected static void cVj(vd e, vo f, vt F)` |
| 0x3A31C90 | 0x2E356E4 |  | `private static void .cctor()` |

</details>

### public class `PlayerManager` : vd  
`TypeDefIndex 2879`

| offset | field |
|---|---|
| - | `internal static readonly HashSet<PlayerManager> EnabledInstances;` |
| 0x68 | `public KCC kcc;` |
| 0x70 | `public Transform worldCameraRoot;` |
| 0x78 | `public MouseLook mouseLook;` |
| 0x80 | `public XA playerEventHandler;` |
| 0x88 | `public PlayerDeathHandler playerDeathHandler;` |
| 0x90 | `public RaycastManager raycastManager;` |
| 0x98 | `public FPManager fpManager;` |
| 0xA0 | `public PlayerInventory inventory;` |
| 0xA8 | `public LQ interaction;` |
| 0xB0 | `public Ls crafter;` |
| 0xB8 | `public PlayerVitals vitals;` |
| 0xC0 | `public XM stats;` |
| 0xC8 | `public Lw loot;` |
| 0xD0 | `public LH lifeStory;` |
| 0xD8 | `public Lj equipment;` |
| 0xE0 | `public PlayerWeapon weapon;` |
| 0xE8 | `public Yr blueprints;` |
| 0xF0 | `public La compass;` |
| 0xF8 | `public Yj statistics;` |
| 0x100 | `public Ly purchases;` |
| 0x108 | `public YC missions;` |
| 0x110 | `public Lh team;` |
| 0x118 | `public Lu cameraManager;` |
| 0x120 | `public Yd nicklabel;` |
| 0x128 | `public VoiceBroadcastTrigger broadcastTrigger;` |
| 0x130 | `public xK voicePlayer;` |
| 0x138 | `public Wd simulation;` |
| 0x140 | `public GameObject characterModel;` |
| 0x148 | `public Cd playerNetworkSubscriptionController;` |
| 0x150 | `private Collider voiceCollider;` |
| 0x158 | `private Td verificationController;` |
| 0x160 | `private PlayerLevelsConfig levelsConfig;` |
| 0x0 | `public static UT<PlayerManager> sleepingPlayerList;` |
| 0x8 | `public static UT<PlayerManager> activePlayerList;` |
| 0x168 | `public Animator animator;` |
| 0x170 | `private FPWeaponBase[] weapons;` |
| 0x178 | `public GameController m_GameController;` |
| 0x180 | `public float NextChatTime;` |
| 0x184 | `public float lookAngle;` |
| 0x188 | `public List<Wv> triggers;` |
| 0x190 | `private float OPV;` |
| 0x198 | `protected string OPg;` |
| 0x1A0 | `private float OPp;` |
| 0x1A4 | `private float OPv;` |
| 0x1A8 | `private bool OPS;` |
| 0x1B0 | `private js OPM;` |
| - | `private jLo ytK;` |
| - | `private jLo xWB;` |
| - | `private jLo DvU;` |
| 0x1C8 | `public uint vehicleID;` |
| 0x1CC | `public uint seatID;` |
| 0x1D0 | `private bool ODe;` |
| 0x1D1 | `private bool ODf;` |
| 0x1D4 | `private float ODF;` |
| 0x1D8 | `private bool ODd;` |
| 0x1D9 | `private bool ODc;` |
| 0x1DA | `private bool ODU;` |
| 0x1DB | `private bool ODY;` |
| 0x1DC | `private bool ODW;` |
| 0x1E0 | `private VehicleManager ODE;` |
| 0x1E8 | `private Seat ODA;` |
| 0x1F0 | `private Vector3 ODu;` |
| 0x200 | `private VoicePlayerState ODk;` |
| 0x208 | `private bool[] ODO;` |
| 0x210 | `private int ODt;` |
| 0x214 | `private float ODr;` |
| 0x218 | `public Action<string, string> _Mirror_SyncVarHookDelegate_userID;` |
| 0x220 | `public Action<string, string> _Mirror_SyncVarHookDelegate_teamName;` |
| 0x228 | `public Action<uint, uint> _Mirror_SyncVarHookDelegate_vehicleID;` |
| 0x230 | `public Action<uint, uint> _Mirror_SyncVarHookDelegate_seatID;` |
| - | `private static js.jq viewFactory;` |
| - | `private bool remoteStarted;` |
| - | `private float dbgVehNext;` |

Properties: `internal object CXp { get; }`; `public string userID { get; set; }`; `public string teamName { get; set; }`; `public string Nick { get; set; }`; `public Td sSV { get; }`; `public bool OPI { get; set; }`; `public Cd sSg { get; }`; `public bool sSp { get; }`; `public bool sSv { get; }`; `public bool sSS { get; }`; `public Seat sSI { get; }`; `public VehicleManager sSM { get; }`; `public bool sIe { get; }`; `public string sIf { get; set; }`; `public string sIF { get; }`; `public bool sId { get; }`; `public float sIc { get; }`; `public float sIU { get; }`; `public float sIY { get; }`; `public static IEnumerable<PlayerManager> sIW { get; }`; `public string sIE { get; set; }`; `public string sIA { get; set; }`; `public uint sIu { get; set; }`; `public uint sIk { get; set; }`; `public bool sIO { get; set; }`; `public bool sIt { get; set; }`; `public float sIr { get; set; }`; `public bool sIN { get; set; }`; `public bool sIq { get; set; }`; `public bool sIs { get; set; }`; `public bool SuppressMountedWeapons { get; }`

<details><summary>methods (190)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E35CE4 |  | `internal object get_CXp()` |
| - | 0x2E35CF0 |  | `public string get_userID()` |
| - | 0x2E35CFC |  | `public void set_userID(string value)` |
| - | 0x2E35D08 |  | `public string get_teamName()` |
| - | 0x2E35D14 |  | `public void set_teamName(string value)` |
| - | 0x2E35D20 |  | `public string get_Nick()` |
| - | 0x2E35D2C |  | `private void set_Nick(string value)` |
| 0x3A389DC | 0x2E35D38 |  | `public Td get_sSV()` |
| 0x3A389E4 | 0x2E35D40 |  | `public bool get_OPI()` |
| 0x3A389EC | 0x2E35D48 |  | `private void set_OPI(bool value)` |
| 0x3A389F8 | 0x2E35D4C |  | `public Cd get_sSg()` |
| 0x3A38C58 | 0x2E35D54 |  | `public bool get_sSp()` |
| 0x3A38CA0 | 0x2E35D5C |  | `public bool get_sSv()` |
| 0x3A38CE8 | 0x2E35D64 |  | `public bool get_sSS()` |
| 0x3A38D80 | 0x2E35D6C |  | `public Seat get_sSI()` |
| 0x3A38D88 | 0x2E35D74 |  | `public VehicleManager get_sSM()` |
| 0x3A38D90 | 0x2E35D7C |  | `public bool get_sIe()` |
| 0x3A38DF0 | 0x2E35D84 |  | `public string get_sIf()` |
| 0x3A38DF8 | 0x2E35D8C |  | `public void set_sIf(string value)` |
| 0x3A38F20 | 0x2E35D90 |  | `public string get_sIF()` |
| 0x3A323F4 | 0x2E35D98 |  | `public bool get_sId()` |
| 0x3A38FD0 | 0x2E35DF0 |  | `public float get_sIc()` |
| 0x3A39020 | 0x2E35DF8 |  | `public float get_sIU()` |
| 0x3A39070 | 0x2E35E00 |  | `public float get_sIY()` |
| 0x3A3B4A0 | 0x2E35E08 |  | `public static IEnumerable<PlayerManager> get_sIW()` |
| 0x3A3E158 | 0x2E35E10 |  | `public string get_sIE()` |
| 0x3A3922C | 0x2E35E18 |  | `public void set_sIE([In] string value)` |
| 0x3A3E160 | 0x2E35E1C |  | `public string get_sIA()` |
| 0x3A392D4 | 0x2E35E24 |  | `public void set_sIA([In] string value)` |
| 0x3A3E168 | 0x2E35E28 |  | `public uint get_sIu()` |
| 0x3A39340 | 0x2E35E30 |  | `public void set_sIu([In] uint value)` |
| 0x3A3E170 | 0x2E35E34 |  | `public uint get_sIk()` |
| 0x3A393AC | 0x2E35E3C |  | `public void set_sIk([In] uint value)` |
| - | 0x2E35E40 |  | `public bool get_sIO()` |
| - | 0x2E35E48 |  | `public void set_sIO(bool value)` |
| - | 0x2E35E54 |  | `public bool get_sIt()` |
| - | 0x2E35E5C |  | `public void set_sIt(bool value)` |
| - | 0x2E35E68 |  | `public float get_sIr()` |
| - | 0x2E35E70 |  | `public void set_sIr(float value)` |
| 0x3A3E3C0 | 0x2E35E78 |  | `public bool get_sIN()` |
| 0x3A3E3C8 | 0x2E35E80 |  | `public void set_sIN([In] bool value)` |
| 0x3A3E484 | 0x2E35E84 |  | `public bool get_sIq()` |
| 0x3A3E48C | 0x2E35E8C |  | `public void set_sIq([In] bool value)` |
| - | 0x2E35E90 |  | `public bool get_sIs()` |
| - | 0x2E35E98 |  | `public void set_sIs(bool value)` |
| 0x3A38A00 | 0x2E35EA4 |  | `public void cgA(js.jq e)` |
| 0x3A38A04 | 0x2E35EA8 |  | `public void cgH(js.jq e)` |
| - | 0x2E36330 |  | `private void FollowMount(Transform pivot)` |
| - | 0x2E36504 |  | `private void SyncMountedPresentation()` |
| - | 0x2E36670 |  | `private void ResolveLocalMount()` |
| - | 0x2E36C1C |  | `private void LateUpdate()` |
| - | 0x2E36CD4 |  | `private void UpdateRemoteVehicle()` |
| - | 0x2E36FE4 |  | `private void UpdateRemoteSeat()` |
| - | 0x2E37294 |  | `private void BuildView()` |
| 0x3A390C0 | 0x2E373C4 |  | `private void Awake()` |
| 0x3A3916C | 0x2E37474 |  | `public void cgi(string e, string f)` |
| 0x3A39290 | 0x2E37478 |  | `public void cgw(string e, string f)` |
| 0x3A39338 | 0x2E3747C |  | `public void cgJ(uint e, uint f)` |
| 0x3A393A4 | 0x2E37480 |  | `public void cgX(uint e, uint f)` |
| 0x3A39410 | 0x2E37484 |  | `private void cgT()` |
| 0x3A39520 | 0x2E37488 |  | `public void OnEnable()` |
| 0x3A395AC | 0x2E37508 | 11 | `public override void Fsv()` |
| 0x3A395C8 | 0x2E3750C |  | `private void OnDisable()` |
| - | 0x2E376F0 |  | `private IEnumerator cgL()` |
| 0x3A395F8 | 0x2E376F8 |  | `private void Update()` |
| 0x3A3A384 | 0x2E38090 |  | `public void Respawn()` |
| 0x3A3A4A0 | 0x2E38364 |  | `public void Respawn(uint sleepingbag)` |
| 0x3A3A5C8 | 0x2E3867C |  | `public void Suicide()` |
| 0x3A3A388 | 0x2E38844 |  | `public void cgo()` |
| - | 0x2E38848 |  | `public bool get_SuppressMountedWeapons()` |
| - | 0x2E37F60 |  | `public bool cgN()` |
| - | 0x2E388FC |  | `public bool cgO()` |
| 0x3A3A5CC | 0x2E38994 |  | `public void cgy()` |
| 0x3A3A4A4 | 0x2E38CDC |  | `public void cgz(uint e)` |
| 0x3A3A6E4 | 0x2E38CE0 | 4 | `public override void cgh()` |
| - | 0x2E38CE4 |  | `public void InitializeLocalPlayer()` |
| 0x3A3A900 | 0x2E3918C |  | `public void cgB()` |
| 0x3A3AA18 | 0x2E392C4 |  | `public float cgm()` |
| 0x3A3AA20 | 0x2E392CC |  | `public bool cgR()` |
| 0x3A3AA28 | 0x2E392D4 |  | `public bool cgb()` |
| 0x3A3AA30 | 0x2E392DC |  | `public bool cgl()` |
| 0x3A3AA38 | 0x2E392E4 |  | `public Cupboard cgx(OBB e)` |
| 0x3A3AA40 | 0x2E392EC |  | `private void cgK(int e, int f, int F, float d, int c)` |
| 0x3A3ABCC | 0x2E392F0 |  | `private void cgG(string e, int f, int F)` |
| 0x3A3AD20 | 0x2E392F4 |  | `public OBB cgP()` |
| 0x3A3A258 | 0x2E39308 |  | `private void cgD(float e)` |
| 0x3A3AE14 | 0x2E3930C |  | `private bool cgn()` |
| 0x3A3AE64 | 0x2E39314 |  | `private void cgV(float e)` |
| 0x3A3AF90 | 0x2E39318 |  | `public void cgg(string e)` |
| 0x3A3AF94 | 0x2E3931C |  | `public void cgp(string e, string[] f)` |
| 0x3A3AF98 | 0x2E39320 |  | `public void cgv(string e, string[] f)` |
| 0x3A3B0D8 | 0x2E39324 |  | `public void cgS(string e)` |
| 0x3A3B1FC | 0x2E39328 |  | `public void cgI(float e, Lf.Le f, PlayerManager F)` |
| 0x3A3B220 | 0x2E3932C |  | `public void Heal(float amount)` |
| 0x3A3B23C | 0x2E39330 |  | `public void cgM(float e, float f)` |
| 0x3A3B37C | 0x2E39334 |  | `public void cpe(bool e)` |
| 0x3A3B53C | 0x2E39338 |  | `public void cpF(string e)` |
| 0x3A3B660 | 0x2E394D0 |  | `public void cpd(string e)` |
| 0x3A3B784 | 0x2E394D4 |  | `public void cpc(string e)` |
| 0x3A3B8A8 | 0x2E394D8 |  | `public void cpU(string e, object[] args)` |
| 0x3A3B9E8 | 0x2E394DC | 8 | `public override void FZo(vo e, bool f)` |
| 0x3A3BA50 | 0x2E39648 |  | `public void cpY(PlayerManager e)` |
| 0x3A3BA54 | 0x2E368C4 |  | `public void cpW(VehicleManager e)` |
| 0x3A3BB00 | 0x2E36AB0 |  | `public void cpE(Seat e)` |
| 0x3A3A090 | 0x2E37FC0 |  | `private void cpA()` |
| 0x3A3BBD0 | 0x2E3964C |  | `private float cpu(float e, float f, float F)` |
| 0x3A3BC10 | 0x2E33B60 |  | `public void SetCarAccel(float i)` |
| 0x3A3BCA8 | 0x2E33C88 |  | `public void SetCarBrake(float i)` |
| 0x3A3BD40 | 0x2E33DB0 |  | `public void SetCarSteer(float i)` |
| 0x3A3BDD8 | 0x2E33ED8 |  | `public void SetHeliThrottle(float i)` |
| 0x3A3BE70 | 0x2E34000 |  | `public void SetHeliTurn(float i)` |
| 0x3A3BF08 | 0x2E34114 |  | `public void ExitVehicle()` |
| 0x3A3BF80 | 0x2E3968C |  | `public void cpk()` |
| 0x3A3C098 | 0x2E397E4 |  | `public void cpO(Vector3 e, Vector3 f)` |
| 0x3A3C208 | 0x2E397E8 |  | `public void cpt()` |
| 0x3A3C280 | 0x2E39860 |  | `public void cpr()` |
| 0x3A3C398 | 0x2E399A4 |  | `public void cpN(Vector3 e, Vector3 f)` |
| 0x3A3C508 | 0x2E399A8 |  | `private static PlayerManager cpq(string e, IEnumerable<PlayerManager> f)` |
| 0x3A3C710 | 0x2E399B0 |  | `public static PlayerManager cps(string e, IEnumerable<PlayerManager> f)` |
| 0x3A3C840 | 0x2E399B8 |  | `public static PlayerManager cpC(string e)` |
| 0x3A3C9D8 | 0x2E399C0 |  | `public static PlayerManager cpZ(string e)` |
| 0x3A3CB70 | 0x2E399C8 |  | `public static PlayerManager cpj(string e)` |
| 0x3A3CBD0 | 0x2E399D0 |  | `public static PlayerManager cpa(string e)` |
| 0x3A3CC2C | 0x2E399D8 |  | `public void cpQ(string e)` |
| 0x3A3CD50 | 0x2E399DC |  | `private void Disconnect()` |
| 0x3A3CDE0 | 0x2E399E4 |  | `public void cpH(string e)` |
| 0x3A3CF04 | 0x2E399E8 |  | `public bool cpi()` |
| 0x3A3A048 | 0x2E39A48 |  | `public void cpw(int e, string f)` |
| 0x3A3CF64 | 0x2E39A4C |  | `public void cpJ(int e, string f)` |
| 0x3A3D0A4 | 0x2E39A50 |  | `public void cpX(string e, string f, string F)` |
| 0x3A3D1F8 | 0x2E39BE8 |  | `public void cpT()` |
| 0x3A3D23C | 0x2E39BEC |  | `public Vector3 cpL(Vector3 e)` |
| 0x3A3D37C | 0x2E39BFC |  | `public Vector3 cpo()` |
| 0x3A3D398 | 0x2E39C0C |  | `public Vector3 cpy()` |
| 0x3A3D3EC | 0x2E39C1C |  | `public void cpz()` |
| 0x3A3D3FC | 0x2E39C20 |  | `public void .ctor()` |
| 0x3A3D5E0 | 0x2E39C28 |  | `private static void .cctor()` |
| 0x3A3E150 | 0x2E3A04C | 12 | `public override bool Fuk()` |
| 0x3A3E60C | 0x2E3A054 |  | `protected void cvf()` |
| 0x3A3E614 | 0x2E3A058 |  | `protected static void cvF(vd e, vo f, vt F)` |
| 0x3A3E768 | 0x2E3A05C |  | `protected void cvd()` |
| 0x3A3E76C | 0x2E3A060 |  | `protected static void cvc(vd e, vo f, vt F)` |
| 0x3A3E8B8 | 0x2E3A064 |  | `protected void cvU()` |
| 0x3A3E8BC | 0x2E3A068 |  | `protected static void cvY(vd e, vo f, vt F)` |
| 0x3A3EA08 | 0x2E3A06C |  | `protected void cvW(uint e)` |
| 0x3A3EA0C | 0x2E3A070 |  | `protected static void cvE(vd e, vo f, vt F)` |
| 0x3A3EB74 | 0x2E3A074 |  | `protected void cvA()` |
| 0x3A3EB78 | 0x2E3A078 |  | `protected static void cvu(vd e, vo f, vt F)` |
| 0x3A3ECC4 | 0x2E3A07C |  | `protected void cvk(int e, int f, int F, float d, int c)` |
| 0x3A3EE34 | 0x2E3A220 |  | `protected static void cvO(vd e, vo f, vt F)` |
| 0x3A3EFCC | 0x2E3A314 |  | `protected void cvt(string e, int f, int F)` |
| 0x3A3EFF0 | 0x2E3A468 |  | `protected static void cvr(vd e, vo f, vt F)` |
| 0x3A3F154 | 0x2E3A52C |  | `protected void cvN(float e)` |
| 0x3A3F27C | 0x2E3A530 |  | `protected static void cvq(vd e, vo f, vt F)` |
| 0x3A3F3E8 | 0x2E3A534 |  | `protected void cvs(float e)` |
| 0x3A3F424 | 0x2E3A560 |  | `protected static void cvC(vd e, vo f, vt F)` |
| 0x3A3F55C | 0x2E3A60C |  | `protected void cvZ(string e, string[] f)` |
| 0x3A3F6E0 | 0x2E3A610 |  | `protected static void cvj(vd e, vo f, vt F)` |
| 0x3A3F82C | 0x2E3A614 |  | `protected void cva(string e)` |
| 0x3A3F838 | 0x2E3A618 |  | `protected static void cvQ(vd e, vo f, vt F)` |
| 0x3A3F970 | 0x2E3A61C |  | `protected void cvH(float e, float f)` |
| 0x3A3F98C | 0x2E3A620 |  | `protected static void cvi(vd e, vo f, vt F)` |
| 0x3A3FAE8 | 0x2E3A624 |  | `protected void cvw(bool e)` |
| 0x3A3FB34 | 0x2E3A76C |  | `protected static void cvJ(vd e, vo f, vt F)` |
| 0x3A3FC70 | 0x2E3A800 |  | `protected void cvX(string e)` |
| 0x3A3FC74 | 0x2E3A804 |  | `protected static void cvT(vd e, vo f, vt F)` |
| 0x3A3FDDC | 0x2E3A808 |  | `protected void cvL(string e)` |
| 0x3A3FDE0 | 0x2E3A80C |  | `protected static void cvo(vd e, vo f, vt F)` |
| 0x3A3FF48 | 0x2E3A810 |  | `protected void cvy(string e)` |
| 0x3A3FFA0 | 0x2E3A814 |  | `protected static void cvz(vd e, vo f, vt F)` |
| 0x3A400D8 | 0x2E3A818 |  | `protected void cvh(string e, object[] f)` |
| 0x3A40108 | 0x2E3A81C |  | `protected static void cvB(vd e, vo f, vt F)` |
| 0x3A40264 | 0x2E3A820 |  | `protected void cvm()` |
| 0x3A40268 | 0x2E3A824 |  | `protected static void cvR(vd e, vo f, vt F)` |
| 0x3A403B4 | 0x2E3A828 |  | `protected void cvb(Vector3 e, Vector3 f)` |
| 0x3A404D8 | 0x2E3AA2C |  | `protected static void cvl(vd e, vo f, vt F)` |
| 0x3A40658 | 0x2E3AAFC |  | `protected void cvx()` |
| 0x3A4065C | 0x2E3AB00 |  | `protected static void cvK(vd e, vo f, vt F)` |
| 0x3A407A8 | 0x2E3AB04 |  | `protected void cvG(Vector3 e, Vector3 f)` |
| 0x3A40898 | 0x2E3AE40 |  | `protected static void cvP(vd e, vo f, vt F)` |
| 0x3A40A18 | 0x2E3AF10 |  | `protected void cvD(string e)` |
| 0x3A40A24 | 0x2E3AF14 |  | `protected static void cvn(vd e, vo f, vt F)` |
| 0x3A40B5C | 0x2E3AF18 |  | `protected void cvV(string e)` |
| 0x3A40BB4 | 0x2E3AF1C |  | `protected static void cvg(vd e, vo f, vt F)` |
| 0x3A40CEC | 0x2E3AF20 |  | `protected void cvp(int e, string f)` |
| 0x3A40CF0 | 0x2E3AF24 |  | `protected static void cvv(vd e, vo f, vt F)` |
| 0x3A40E64 | 0x2E3AF28 |  | `protected void cvS(string e, string f, string F)` |
| 0x3A40E68 | 0x2E3AF2C |  | `protected static void cvI(vd e, vo f, vt F)` |
| 0x3A40FE8 | 0x2E3AF30 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A411D8 | 0x2E3AF34 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `PlayerPauseHandler` : MonoBehaviour  
`TypeDefIndex 2880`

| offset | field |
|---|---|
| 0x20 | `private oP m_DOF;` |
| 0x28 | `private oR m_ColorCorrectionCurves;` |
| 0x30 | `private GameObject m_Background;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A0BC10 | 0x2E3B424 |  | `private void Start()` |
| 0x3A0BCCC | 0x2E3B428 |  | `private void clE()` |
| 0x3A0BE08 | 0x2E3B42C |  | `public void SetActive(bool active)` |
| 0x3A0BED4 | 0x2E3B430 |  | `public void .ctor()` |

</details>

### public struct `PlayerSaveData`  
`TypeDefIndex 2881`

| offset | field |
|---|---|
| 0x0 | `public string ItemData;` |
| 0x8 | `public string EquipData;` |
| 0x10 | `public string HotbarData;` |
| 0x18 | `public int FPSItemIndex;` |
| 0x20 | `public string Position;` |
| 0x28 | `public string Rotation;` |
| 0x30 | `public float Food;` |
| 0x34 | `public float Water;` |
| 0x38 | `public float Stamina;` |
| 0x3C | `public float Health;` |

### public class `PlayerSleepHandler` : XY  
`TypeDefIndex 2883`

| offset | field |
|---|---|
| 0x90 | `private float m_SleepSpeed;` |
| 0x94 | `private float m_SleepFinishPause;` |
| 0x98 | `private int m_GetUpHour;` |
| 0xA0 | `private Collider[] m_CollidersToDisable;` |
| 0xA8 | `private GameObject[] m_ObjectsToDisable;` |
| 0xB0 | `private Behaviour[] m_BehavioursToDisable;` |
| 0xB8 | `private Vector3 OKJ;` |
| 0xC4 | `private Quaternion OKX;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A0BEDC | 0x2E3B438 |  | `private void Awake()` |
| 0x3A0BF80 | 0x2E3B43C |  | `private bool clt(SleepingBag e)` |
| - | 0x2E3B444 |  | `private IEnumerator clr(SleepingBag e)` |
| 0x3A0C090 | 0x2E3B44C |  | `private void clN(bool e)` |
| 0x3A0C194 | 0x2E3B450 |  | `public void .ctor()` |
| 0x3A0C1B0 | 0x2E3B458 | 12 | `public override bool Fuk()` |

</details>

### public class `PlayerVitals` : EntityVitals  
`TypeDefIndex 2885`

| offset | field |
|---|---|
| 0xE0 | `public PlayerManager Player;` |
| 0xE8 | `public XA PlayerEvent;` |
| 0xF0 | `public StatRegenData m_HealthRegeneration;` |
| 0xF8 | `private StatDepleter m_ThirstDepletion;` |
| 0x100 | `private StatDepleter m_HungerDepletion;` |
| 0x108 | `private float m_Temperature;` |
| 0x10C | `private float m_RadiationLevel;` |
| 0x110 | `private float m_RadiationPoison;` |
| 0x114 | `private bool m_SleepRestoresHealth;` |
| 0x118 | `private float m_DamagePeriod;` |
| 0x11C | `private float m_LastDamageTime;` |
| 0x120 | `private float updatePeriod;` |
| 0x124 | `private float OmR;` |
| 0x128 | `private bool Omb;` |

Properties: `public float sVP { get; }`; `public float sVD { get; }`; `public float sVn { get; }`; `private XA Events { get; }`

<details><summary>methods (30)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3B488 |  | `public float get_sVP()` |
| - | 0x2E3B490 |  | `public float get_sVD()` |
| - | 0x2E3B498 |  | `public float get_sVn()` |
| 0x39DE514 | 0x2E3B4A0 |  | `public float ciS()` |
| 0x39DE538 | 0x2E3B4C4 |  | `public void ciI(float e)` |
| 0x39DE664 | 0x2E3B4C8 |  | `public void ciM(float e)` |
| 0x39DE790 | 0x2E3B4CC |  | `public void cwe(float e)` |
| 0x39DE8BC | 0x2E3B4D0 |  | `public void cwf(float e, float f, float F)` |
| 0x39DEA18 | 0x2E3B4D4 |  | `public void cwF(float e, float f, float F)` |
| 0x39DEB74 | 0x2E3B4D8 |  | `public void cwd(int e, float f, int F, int d)` |
| 0x39DECE4 | 0x2E3B4DC |  | `public void cwc(float e)` |
| 0x39DED4C | 0x2E3B658 | 18 | `public override void cik(float e, Lf.Le f, PlayerManager F)` |
| 0x39DEED8 | 0x2E3B65C |  | `public void Heal(float amount)` |
| 0x39DEFA8 | 0x2E3B660 |  | `public float cwU(float e, float f)` |
| 0x39DEFFC | 0x2E3B668 |  | `public void .ctor()` |
| 0x39DF03C | 0x2E3B670 | 12 | `public override bool Fuk()` |
| 0x39DF044 | 0x2E3B678 |  | `protected void cwY(float e)` |
| 0x39DF168 | 0x2E3B750 |  | `protected static void cwW(vd e, vo f, vt F)` |
| 0x39DF2A0 | 0x2E3B754 |  | `protected void cwE(float e)` |
| 0x39DF308 | 0x2E3B82C |  | `protected static void cwA(vd e, vo f, vt F)` |
| 0x39DF440 | 0x2E3B830 |  | `protected void cwu(float e)` |
| 0x39DF4A8 | 0x2E3B908 |  | `protected static void cwk(vd e, vo f, vt F)` |
| 0x39DF5E0 | 0x2E3B90C |  | `protected void cwO(float e, float f, float F)` |
| 0x39DF6A4 | 0x2E3BA38 |  | `protected static void cwt(vd e, vo f, vt F)` |
| 0x39DF814 | 0x2E3BA3C |  | `protected void cwr(float e, float f, float F)` |
| 0x39DF824 | 0x2E3BA4C |  | `protected static void cwN(vd e, vo f, vt F)` |
| 0x39DF990 | 0x2E3BA50 |  | `protected void cwq(int e, float f, int F, int d)` |
| 0x39DFAA4 | 0x2E3BB44 |  | `protected static void cws(vd e, vo f, vt F)` |
| - | 0x2E3B5A0 |  | `private XA get_Events()` |
| 0x39DFC28 | 0x2E3BB48 |  | `private static void .cctor()` |

</details>

### public class `Pool`  
`TypeDefIndex 2886`

| offset | field |
|---|---|
| 0x10 | `private string m_PoolName;` |
| 0x18 | `private GameObject m_Prefab;` |
| 0x20 | `private int m_Amount;` |
| 0x28 | `private List<GameObject> ORV;` |

Properties: `public string spy { get; }`; `public GameObject spz { get; }`; `public int sph { get; }`; `public List<GameObject> spB { get; }`

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39ECD8C | 0x2E3C3B8 |  | `public string get_spy()` |
| 0x39ECD94 | 0x2E3C3C0 |  | `public GameObject get_spz()` |
| 0x39ECD9C | 0x2E3C3C8 |  | `public int get_sph()` |
| 0x39ECDA4 | 0x2E3C3D0 |  | `public List<GameObject> get_spB()` |
| 0x39ECDAC | 0x2E3C3D8 |  | `private GameObject coh()` |
| 0x39ECF24 | 0x2E3C3E0 |  | `private GameObject coB()` |
| 0x39ED09C | 0x2E3C3E8 |  | `public void Spawn(Vector3 position, Quaternion rotation)` |
| 0x39ED194 | 0x2E3C3EC |  | `public void com(Vector3[] e, Quaternion[] f)` |
| 0x39ED258 | 0x2E3C3F0 |  | `public void coR(GameObject e)` |
| 0x39ED358 | 0x2E3C3F4 |  | `public void cob()` |
| 0x39ED3D0 | 0x2E3C3F8 |  | `public void cox(bool e)` |
| 0x39ED508 | 0x2E3C3FC |  | `public void coK()` |
| 0x39ED614 | 0x2E3C400 |  | `public void coG()` |
| 0x39ED6F0 | 0x2E3C404 |  | `public void .ctor()` |

</details>

### public class `PooledObject` : MonoBehaviour  
`TypeDefIndex 2888`

| offset | field |
|---|---|
| 0x20 | `public XN<PooledObject> Released;` |
| 0x28 | `private bool m_ReleaseOnTimer;` |
| 0x2C | `private float m_ReleaseTimer;` |
| 0x30 | `private ParticleSystem[] m_ToResetParticles;` |
| 0x38 | `private WaitForSeconds ORS;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39EDCCC | 0x2E3C40C | 4 | `public virtual void coM(Vector3 e, Quaternion f, Transform F)` |
| 0x39EDFC8 | 0x2E3C410 | 5 | `public virtual void cye()` |
| 0x39EE038 | 0x2E3C414 |  | `private void Awake()` |
| 0x39EDF5C | 0x2E3C418 |  | `private IEnumerator cyf()` |
| 0x39EE0E8 | 0x2E3C420 |  | `public void .ctor()` |

</details>

### public class `PoolManager` : MonoBehaviour  
`TypeDefIndex 2889`

| offset | field |
|---|---|
| 0x20 | `private List<Pool> _pools;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39ED778 | 0x2E3C450 |  | `private void Awake()` |
| 0x39ED77C | 0x2E3C454 |  | `private void coP()` |
| 0x39EDAF8 | 0x2E3C458 |  | `public Pool coD(string e)` |
| 0x39EDC30 | 0x2E3C460 |  | `public void .ctor()` |

</details>

### public class `Purchase`  
`TypeDefIndex 2890`

| offset | field |
|---|---|
| 0x10 | `private int m_Price;` |
| 0x14 | `private int m_Amount;` |

Properties: `public int sgA { get; }`; `public int sgu { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3C468 |  | `public int get_sgA()` |
| - | 0x2E3C470 |  | `public int get_sgu()` |
| 0x39E5340 | 0x2E3C4CC |  | `public static bool cXr(Purchase e)` |
| 0x39E534C | 0x2E3C4E0 |  | `public void .ctor()` |

</details>

### public struct `QueueItem`  
`TypeDefIndex 2891`

| offset | field |
|---|---|
| 0x0 | `public string m_Result;` |
| 0x8 | `public int m_Amount;` |
| 0xC | `public int m_Skin;` |
| 0x10 | `public int m_RemainedTime;` |
| 0x14 | `private int OPa;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A2436C | 0x2E3C4E8 |  | `public void .ctor(string item, int amount, int craftingTime, int skin)` |

</details>

### public class `Ragdoll` : MonoBehaviour  
`TypeDefIndex 2893`

| offset | field |
|---|---|
| 0x20 | `public Rigidbody m_Pelvis;` |
| 0x28 | `private bool setRagdollLayer;` |
| 0x30 | `private string m_NormalLayer;` |
| 0x38 | `private string m_RagdollLayer;` |
| 0x40 | `private Ragdoll.BoneToReparent[] m_BonesToReparent;` |
| 0x48 | `private Collider[] collidersToEnable;` |
| 0x50 | `public Texture m_SurfaceTexture;` |
| 0x58 | `private bool m_AutoAssignHitboxes;` |
| 0x60 | `private Rigidbody[] m_Bones;` |
| 0x68 | `private FloatingObject floatingObject;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DFF60 | 0x2E3C524 |  | `private void Awake()` |
| 0x39DFFE4 | 0x2E30184 |  | `public void cwZ(Vector3 e)` |
| 0x39E01EC | 0x2E3C630 |  | `public void .ctor()` |

</details>

### public class `RaycastManager` : MonoBehaviour  
`TypeDefIndex 2894`

| offset | field |
|---|---|
| 0x20 | `public PlayerManager player;` |
| 0x28 | `public Camera m_WorldCamera;` |
| 0x30 | `public float m_RayLength;` |
| 0x34 | `private float m_AimRayLength;` |
| 0x38 | `private float OlK;` |
| 0x3C | `private float m_TooCloseThreeshold;` |
| 0x40 | `public LayerMask m_LayerMask;` |
| 0x44 | `private LayerMask m_AimLayerMask;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FBADC | 0x2E3C640 |  | `private void Start()` |
| - | 0x2E3C920 |  | `private static bool Alive(UQ target)` |
| 0x39FBC98 | 0x2E3CA08 |  | `private void OnDisable()` |
| 0x39FBCA0 | 0x2E3CB68 |  | `private bool cBz()` |
| 0x39FBE48 | 0x2E3D46C |  | `private bool cBh()` |
| 0x39FBEF8 | 0x2E3CE74 |  | `private void Update()` |
| 0x39FC5CC | 0x2E3D52C |  | `public Vector3 cBB()` |
| 0x39F9B1C | 0x2E3D640 |  | `public void cBm(float e, float f = 0)` |
| 0x39FC714 | 0x2E3D648 |  | `public void .ctor()` |
| 0x39FC72C | 0x2E3D670 |  | `private void cBR()` |
| 0x39FC790 | 0x2E3D774 |  | `private void cBb()` |

</details>

### public class `RayImpact`  
`TypeDefIndex 2895`

| offset | field |
|---|---|
| 0x10 | `private float m_MaxDamage;` |
| 0x14 | `private float m_MaxImpulse;` |
| 0x18 | `private AnimationCurve m_DistanceCurve;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FA9B4 | 0x2E3D778 |  | `public float chi(float e, float f)` |
| 0x39FAA18 | 0x2E3D780 |  | `public float chw(float e, float f)` |
| 0x39FA9CC | 0x2E3D788 |  | `private float chJ(float e, float f, float F)` |
| 0x39FAA30 | 0x2E3D790 |  | `public void .ctor()` |

</details>

### public class `Recipe`  
`TypeDefIndex 2896`

| offset | field |
|---|---|
| 0x10 | `private int m_Duration;` |
| 0x14 | `private int m_Count;` |
| 0x18 | `private RequiredItem[] m_RequiredItems;` |

Properties: `public int spw { get; }`; `public int spJ { get; }`; `public RequiredItem[] spX { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E85A0 | 0x2E3D798 |  | `public int get_spw()` |
| 0x39E85A8 | 0x2E3D7A0 |  | `public int get_spJ()` |
| 0x39E85B0 | 0x2E3D7A8 |  | `public RequiredItem[] get_spX()` |
| 0x39E85B8 | 0x2E3D7B0 |  | `public static bool cLK(Recipe e)` |
| 0x39E85C4 | 0x2E3D7B8 |  | `public void .ctor()` |

</details>

### public class `Recycler` : Xb, Xa  
`TypeDefIndex 2897`

| offset | field |
|---|---|
| 0x80 | `private ParticleSystem m_Particles;` |
| 0x88 | `public string panelName;` |
| 0x90 | `public List<string> excludedCategories;` |
| 0x98 | `public List<string> excludedItems;` |
| 0xA0 | `public AudioSource audioSource;` |
| 0xA8 | `public bool recycling;` |
| 0xA9 | `private bool ODo;` |

Properties: `public bool sIZ { get; set; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3D7C0 |  | `public bool get_sIZ()` |
| - | 0x2E3D7C8 |  | `public void set_sIZ(bool value)` |
| 0x3A4D1B4 | 0x2E3D7D4 |  | `public void Update()` |
| 0x3A4D21C | 0x2E3D8C8 |  | `public void .ctor()` |
| 0x3A4D28C | 0x2E3D8D0 | 12 | `public override bool Fuk()` |
| 0x3A4D358 | 0x2E3D8D8 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A4D3B8 | 0x2E3D8DC | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `ReloadLoop` : StateMachineBehaviour  
`TypeDefIndex 2898`

| offset | field |
|---|---|
| 0x18 | `private float m_NextReloadTime;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39FADD0 | 0x2E3D930 | 4 | `public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)` |
| 0x39FAE38 | 0x2E3D934 | 5 | `public override void OnStateUpdate(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)` |
| 0x39FAF5C | 0x2E3D938 |  | `public void .ctor()` |

</details>

### public class `ReorderableAttribute` : PropertyAttribute  
`TypeDefIndex 2899`

| offset | field |
|---|---|
| 0x10 | `private RangeAttribute OBo;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D8CFC | 0x2E3D940 |  | `public void .ctor()` |

</details>

### public class `ReorderableBoolList` : ReorderableGenericList<bool>  
`TypeDefIndex 2900`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DB34 | 0x2E3D948 |  | `public void .ctor()` |

</details>

### public class `ReorderableFloatList` : ReorderableGenericList<float>  
`TypeDefIndex 2901`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DBC4 | 0x2E3D990 |  | `public void .ctor()` |

</details>

### public class `ReorderableGenericList<T>` : IEnumerable<T>, IEnumerable  
`TypeDefIndex 2902`

| offset | field |
|---|---|
| 0x0 | `private List<T> m_List;` |

Properties: `public T Item { get; set; }`; `public int sSX { get; }`; `public List<T> sST { get; }`

<details><summary>methods (216)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `private IEnumerator System.Collections.IEnumerable.GetEnumerator()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABB90 Offset: 0x3EA7B90 VA: 0x3EABB90` |
| - | - |  | `\|-ReorderableGenericList<object>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC208 Offset: 0x3EA8208 VA: 0x3EAC208` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB8EC Offset: 0x3EA78EC VA: 0x3EAB8EC` |
| - | - |  | `\|-ReorderableGenericList<bool>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABA40 Offset: 0x3EA7A40 VA: 0x3EABA40` |
| - | - |  | `\|-ReorderableGenericList<int>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABE24 Offset: 0x3EA7E24 VA: 0x3EABE24` |
| - | - |  | `\|-ReorderableGenericList<float>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABCE0 Offset: 0x3EA7CE0 VA: 0x3EABCE0` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABF74 Offset: 0x3EA7F74 VA: 0x3EABF74` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC0C4 Offset: 0x3EA80C4 VA: 0x3EAC0C4` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `*/` |
| - | - |  | `public T get_Item(int key)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABF84 Offset: 0x3EA7F84 VA: 0x3EABF84` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB8FC Offset: 0x3EA78FC VA: 0x3EAB8FC` |
| - | - |  | `\|-ReorderableGenericList<bool>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABBA0 Offset: 0x3EA7BA0 VA: 0x3EABBA0` |
| - | - |  | `\|-ReorderableGenericList<object>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC21C Offset: 0x3EA821C VA: 0x3EAC21C` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABA50 Offset: 0x3EA7A50 VA: 0x3EABA50` |
| - | - |  | `\|-ReorderableGenericList<int>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC0D4 Offset: 0x3EA80D4 VA: 0x3EAC0D4` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABCF0 Offset: 0x3EA7CF0 VA: 0x3EABCF0` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.get_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABE34 Offset: 0x3EA7E34 VA: 0x3EABE34` |
| - | - |  | `\|-ReorderableGenericList<float>.get_Item` |
| - | - |  | `*/` |
| - | - |  | `public void set_Item(int key, T value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABD14 Offset: 0x3EA7D14 VA: 0x3EABD14` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABE58 Offset: 0x3EA7E58 VA: 0x3EABE58` |
| - | - |  | `\|-ReorderableGenericList<float>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC2D0 Offset: 0x3EA82D0 VA: 0x3EAC2D0` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABBC4 Offset: 0x3EA7BC4 VA: 0x3EABBC4` |
| - | - |  | `\|-ReorderableGenericList<object>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABA74 Offset: 0x3EA7A74 VA: 0x3EABA74` |
| - | - |  | `\|-ReorderableGenericList<int>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC0F8 Offset: 0x3EA80F8 VA: 0x3EAC0F8` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB920 Offset: 0x3EA7920 VA: 0x3EAB920` |
| - | - |  | `\|-ReorderableGenericList<bool>.set_Item` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABFA8 Offset: 0x3EA7FA8 VA: 0x3EABFA8` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.set_Item` |
| - | - |  | `*/` |
| - | - |  | `public int get_sSX()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABA98 Offset: 0x3EA7A98 VA: 0x3EABA98` |
| - | - |  | `\|-ReorderableGenericList<int>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABBE8 Offset: 0x3EA7BE8 VA: 0x3EABBE8` |
| - | - |  | `\|-ReorderableGenericList<object>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC11C Offset: 0x3EA811C VA: 0x3EAC11C` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC3AC Offset: 0x3EA83AC VA: 0x3EAC3AC` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABFCC Offset: 0x3EA7FCC VA: 0x3EABFCC` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABD38 Offset: 0x3EA7D38 VA: 0x3EABD38` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABE7C Offset: 0x3EA7E7C VA: 0x3EABE7C` |
| - | - |  | `\|-ReorderableGenericList<float>.get_sSX` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB948 Offset: 0x3EA7948 VA: 0x3EAB948` |
| - | - |  | `\|-ReorderableGenericList<bool>.get_sSX` |
| - | - |  | `*/` |
| - | - |  | `public List<T> get_sST()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABD54 Offset: 0x3EA7D54 VA: 0x3EABD54` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABAB4 Offset: 0x3EA7AB4 VA: 0x3EABAB4` |
| - | - |  | `\|-ReorderableGenericList<int>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABE98 Offset: 0x3EA7E98 VA: 0x3EABE98` |
| - | - |  | `\|-ReorderableGenericList<float>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABC04 Offset: 0x3EA7C04 VA: 0x3EABC04` |
| - | - |  | `\|-ReorderableGenericList<object>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABFE8 Offset: 0x3EA7FE8 VA: 0x3EABFE8` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC3D4 Offset: 0x3EA83D4 VA: 0x3EAC3D4` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB964 Offset: 0x3EA7964 VA: 0x3EAB964` |
| - | - |  | `\|-ReorderableGenericList<bool>.get_sST` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC138 Offset: 0x3EA8138 VA: 0x3EAC138` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.get_sST` |
| - | - |  | `*/` |
| - | - |  | `public IEnumerator<T> GetEnumerator()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABEA0 Offset: 0x3EA7EA0 VA: 0x3EABEA0` |
| - | - |  | `\|-ReorderableGenericList<float>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABFF0 Offset: 0x3EA7FF0 VA: 0x3EABFF0` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABC0C Offset: 0x3EA7C0C VA: 0x3EABC0C` |
| - | - |  | `\|-ReorderableGenericList<object>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC140 Offset: 0x3EA8140 VA: 0x3EAC140` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC3DC Offset: 0x3EA83DC VA: 0x3EAC3DC` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABD5C Offset: 0x3EA7D5C VA: 0x3EABD5C` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABABC Offset: 0x3EA7ABC VA: 0x3EABABC` |
| - | - |  | `\|-ReorderableGenericList<int>.GetEnumerator` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB96C Offset: 0x3EA796C VA: 0x3EAB96C` |
| - | - |  | `\|-ReorderableGenericList<bool>.GetEnumerator` |
| - | - |  | `*/` |
| - | - |  | `private IEnumerator cGz()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABB20 Offset: 0x3EA7B20 VA: 0x3EABB20` |
| - | - |  | `\|-ReorderableGenericList<int>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABDB4 Offset: 0x3EA7DB4 VA: 0x3EABDB4` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC054 Offset: 0x3EA8054 VA: 0x3EAC054` |
| - | - |  | `\|-ReorderableGenericList<Vector2>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC198 Offset: 0x3EA8198 VA: 0x3EAC198` |
| - | - |  | `\|-ReorderableGenericList<Vector3>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC488 Offset: 0x3EA8488 VA: 0x3EAC488` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABC70 Offset: 0x3EA7C70 VA: 0x3EABC70` |
| - | - |  | `\|-ReorderableGenericList<object>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB9D0 Offset: 0x3EA79D0 VA: 0x3EAB9D0` |
| - | - |  | `\|-ReorderableGenericList<bool>.cGz` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABF04 Offset: 0x3EA7F04 VA: 0x3EABF04` |
| - | - |  | `\|-ReorderableGenericList<float>.cGz` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABDC4 Offset: 0x3EA7DC4 VA: 0x3EABDC4` |
| - | - |  | `\|-ReorderableGenericList<Quaternion>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABC80 Offset: 0x3EA7C80 VA: 0x3EABC80` |
| - | - |  | `\|-ReorderableGenericList<object>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAB9E0 Offset: 0x3EA79E0 VA: 0x3EAB9E0` |
| - | - |  | `\|-ReorderableGenericList<bool>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABB30 Offset: 0x3EA7B30 VA: 0x3EABB30` |
| - | - |  | `\|-ReorderableGenericList<int>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EABF14 Offset: 0x3EA7F14 VA: 0x3EABF14` |
| - | - |  | `\|-ReorderableGenericList<float>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC064 Offset: 0x3EA8064 VA: 0x3EAC064` |
| - | - |  | `\|-ReorderableGenericList<Vector2>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC49C Offset: 0x3EA849C VA: 0x3EAC49C` |
| - | - |  | `\|-ReorderableGenericList<__Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EAC1A8 Offset: 0x3EA81A8 VA: 0x3EAC1A8` |
| - | - |  | `\|-ReorderableGenericList<Vector3>..ctor` |
| - | - |  | `*/` |

</details>

### public class `ReorderableIntList` : ReorderableGenericList<int>  
`TypeDefIndex 2903`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DB7C | 0x2E3D9D8 |  | `public void .ctor()` |

</details>

### public class `ReorderableQuaternionList` : ReorderableGenericList<Quaternion>  
`TypeDefIndex 2904`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DCE4 | 0x2E3DA20 |  | `public void .ctor()` |

</details>

### public class `ReorderableRectTransformList` : ReorderableGenericList<RectTransform>  
`TypeDefIndex 2905`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DD74 | 0x2E3DA68 |  | `public void .ctor()` |

</details>

### public class `ReorderableStringList` : ReorderableGenericList<string>  
`TypeDefIndex 2906`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DC0C | 0x2E3DAB0 |  | `public void .ctor()` |

</details>

### public class `ReorderableTransformList` : ReorderableGenericList<Transform>  
`TypeDefIndex 2907`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DD2C | 0x2E3DAF8 |  | `public void .ctor()` |

</details>

### public class `ReorderableVector2List` : ReorderableGenericList<Vector2>  
`TypeDefIndex 2908`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DC54 | 0x2E3DB40 |  | `public void .ctor()` |

</details>

### public class `ReorderableVector3List` : ReorderableGenericList<Vector3>  
`TypeDefIndex 2909`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A1DC9C | 0x2E3DB88 |  | `public void .ctor()` |

</details>

### public class `RequiredItem`  
`TypeDefIndex 2910`

| offset | field |
|---|---|
| 0x10 | `private string m_Name;` |
| 0x18 | `private int m_Amount;` |

Properties: `public string spa { get; set; }`; `public int spQ { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3DBD0 |  | `public string get_spa()` |
| - | 0x2E3DBD8 |  | `public void set_spa(string value)` |
| - | 0x2E3DBE0 |  | `public int get_spQ()` |
| - | 0x2E3DBE8 |  | `public void set_spQ(int value)` |
| 0x39E84E0 | 0x2E3DBF0 |  | `public void .ctor(string nm, int amt)` |

</details>

### public struct `RequiredRepairItem`  
`TypeDefIndex 2911`

| offset | field |
|---|---|
| - | `private string <OlT>k__BackingField;` |
| - | `private int <OlL>k__BackingField;` |

Properties: `public string OlT { get; set; }`; `public int OlL { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3DC2C |  | `public string get_OlT()` |
| - | 0x2E3DC34 |  | `private void set_OlT(string value)` |
| - | 0x2E3DC3C |  | `public int get_OlL()` |
| - | 0x2E3DC44 |  | `private void set_OlL(int value)` |
| 0x39FB384 | 0x2E3DC4C |  | `public void .ctor(string name, int needs)` |

</details>

### public class `RootHeightHandler` : MonoBehaviour  
`TypeDefIndex 2912`

| offset | field |
|---|---|
| 0x20 | `private PlayerManager m_Player;` |
| 0x28 | `private XA m_EventHandler;` |
| 0x30 | `private float m_CrouchSpeed;` |
| 0x34 | `private float OBv;` |
| 0x38 | `private float OBS;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DAFE8 | 0x2E3DC74 |  | `private void Start()` |
| 0x39DB0E8 | 0x2E3DDE0 |  | `private void cHh()` |
| 0x39DB118 | 0x2E3DE10 |  | `private void cHB()` |
| 0x39DB148 | 0x2E3DE40 |  | `private void Update()` |
| 0x39DB260 | 0x2E3DF34 |  | `public void .ctor()` |

</details>

### public class `SceneReflection` : MonoBehaviour  
`TypeDefIndex 2914`

| offset | field |
|---|---|
| 0x20 | `private ReflectionProbe m_ReflectionProbe;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E0490 | 0x2E3DF54 |  | `private IEnumerator Start()` |
| 0x39E0524 | 0x2E3DF5C |  | `public void .ctor()` |

</details>

### public class `ShaftedProjectile` : vd  
`TypeDefIndex 2919`

| offset | field |
|---|---|
| - | `private bool clientPrediction;` |
| - | `private float flightAge;` |
| - | `private float travelled;` |
| - | `private Vector3 launchPosition;` |
| - | `private Quaternion attachedRotation;` |
| - | `private Collider[] ownerColliders;` |
| - | `private bool impactPlayed;` |
| - | `private static readonly List<ShaftedProjectile> predictions;` |
| 0x68 | `private string m_ObjectName;` |
| 0x70 | `private Transform m_Model;` |
| 0x78 | `private Transform m_Pivot;` |
| 0x80 | `private Transform m_ExplosionPos;` |
| 0x88 | `private TrailRenderer m_Trail;` |
| 0x90 | `public LayerMask m_Mask;` |
| 0x94 | `private float m_MaxDistance;` |
| 0x98 | `private FPWeaponBase m_WeaponLaunched;` |
| 0xA0 | `private Collider m_Collider;` |
| 0xA8 | `private Rigidbody m_Rigidbody;` |
| 0xB0 | `private float m_LaunchSpeed;` |
| 0xB4 | `private float gravity;` |
| 0xB8 | `private float m_MaxDamage;` |
| 0xBC | `private float m_MaxDamageRadius;` |
| 0xC0 | `private float m_MinDamageRadius;` |
| 0xC4 | `private Lf.Le m_DamageType;` |
| 0xC8 | `private float m_PenetrationThreeshold;` |
| 0xCC | `private float m_PenetrationOffset;` |
| 0xD0 | `private Vector2 m_RandomRotation;` |
| 0xD8 | `private bool isPenetration;` |
| 0xDC | `private float m_TwangDuration;` |
| 0xE0 | `private float m_TwangRange;` |
| 0xE8 | `private AudioSource m_AudioSource;` |
| 0xF0 | `private SoundPlayer m_HitAudio;` |
| 0xF8 | `private SoundPlayer m_TwangAudio;` |
| 0x100 | `private TU m_PenetrationType;` |
| 0x108 | `public GameObject explosion;` |
| 0x110 | `public GameObject prefab;` |
| 0x118 | `public Ed smokeEffect;` |
| 0x120 | `public float timerAmount;` |
| 0x128 | `private Behaviour[] m_BehavioursToEnable;` |
| 0x130 | `private Behaviour[] m_BehavioursToDisable;` |
| 0x138 | `private ShaftedProjectile.XP projectilleType;` |
| 0x13C | `private bool attachToTarget;` |
| 0x13D | `private bool deattachOnMove;` |
| 0x13E | `private bool colliderFit;` |
| 0x13F | `private bool finalMovePosition;` |
| 0x140 | `private float explosionScale;` |
| 0x144 | `private bool finalDestroy;` |
| 0x148 | `private Bounds m_Bounds;` |
| 0x160 | `private bool disableInteraction;` |
| 0x164 | `private float castRadius;` |
| 0x168 | `private XE OxQ;` |
| 0x170 | `private bool OxH;` |
| 0x171 | `private bool Oxi;` |
| 0x174 | `private Vector3 Oxw;` |
| 0x180 | `private Transform OxJ;` |
| 0x188 | `private Vector3 OxX;` |
| 0x198 | `private Xb OxT;` |
| 0x1A0 | `public bool done;` |

Properties: `public float svn { get; }`; `public float svV { get; }`; `public bool svg { get; set; }`

<details><summary>methods (39)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E3DF8C |  | `public static ShaftedProjectile Predict(ShaftedProjectile source, FPWeaponBase weapon, Vector3 position, Vector3 angles, float strength)` |
| - | 0x2E3E610 |  | `private void RemoveMatchingPrediction()` |
| - | 0x2E3EA8C |  | `private void SetSettledVisuals()` |
| - | 0x2E3EC88 |  | `private void SimulateFlight(float dt)` |
| - | 0x2E3F820 |  | `private void FinishImpact(bool explode)` |
| - | 0x2E3FC6C |  | `private void OnDestroy()` |
| - | 0x2E3FCEC |  | `public float get_svn()` |
| - | 0x2E3FCF4 |  | `public float get_svV()` |
| - | 0x2E3FCFC |  | `public bool get_svg()` |
| - | 0x2E3FD04 |  | `public void set_svg(bool value)` |
| 0x3A031E4 | 0x2E3FD10 |  | `public void add_OxL(Action<GameObject, GameObject> value)` |
| 0x3A03298 | 0x2E3FD14 |  | `public void remove_OxL(Action<GameObject, GameObject> value)` |
| 0x3A0334C | 0x2E3FD18 |  | `public void add_Oxo(Action<ShaftedProjectile> value)` |
| 0x3A03400 | 0x2E3FD1C |  | `public void remove_Oxo(Action<ShaftedProjectile> value)` |
| 0x3A034C4 | 0x2E3FD20 | 11 | `public override void Fsv()` |
| 0x3A03598 | 0x2E3FD54 |  | `public void Reset()` |
| 0x3A03684 | 0x2E3E45C |  | `public void cRq(XE e, FPWeaponBase f, float F = 1)` |
| 0x3A03870 | 0x2E3FE08 |  | `private void OnEnable()` |
| - | 0x2E3FE74 |  | `private void Awake()` |
| 0x3A03970 | 0x2E40054 |  | `private void FixedUpdate()` |
| 0x3A03974 | 0x2E3FA5C |  | `private bool cRs()` |
| 0x3A03A68 | 0x2E40070 |  | `private void cRC(Vector3 e)` |
| 0x3A03BAC | 0x2E40074 |  | `private void cRZ(Vector3 e, Vector3 f)` |
| 0x3A03D1C | 0x2E40078 |  | `private void cRj()` |
| 0x3A03E34 | 0x2E4007C |  | `private void cRa()` |
| 0x3A03F4C | 0x2E3FBF8 |  | `private IEnumerator cRQ()` |
| 0x3A03FE0 | 0x2E40080 |  | `public void .ctor()` |
| 0x3A0403C | 0x2E40088 | 12 | `public override bool Fuk()` |
| 0x3A0404C | 0x2E40090 |  | `protected void cRw(Vector3 e)` |
| 0x3A04094 | 0x2E400D8 |  | `protected static void cRJ(vd e, vo f, vt F)` |
| 0x3A041CC | 0x2E40168 |  | `protected void cRX(Vector3 e, Vector3 f)` |
| 0x3A04300 | 0x2E40224 |  | `protected static void cRT(vd e, vo f, vt F)` |
| 0x3A04480 | 0x2E3FB4C |  | `protected void cRL()` |
| 0x3A04540 | 0x2E402F4 |  | `protected static void cRo(vd e, vo f, vt F)` |
| 0x3A0465C | 0x2E40374 |  | `protected void cRy()` |
| 0x3A046DC | 0x2E403F4 |  | `protected static void cRz(vd e, vo f, vt F)` |
| 0x3A047F8 | 0x2E40474 |  | `private static void .cctor()` |
| 0x3A04A60 | 0x2E40724 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A04AC0 | 0x2E40770 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `ShopOrder`  
`TypeDefIndex 2920`

| offset | field |
|---|---|
| 0x10 | `public string item;` |
| 0x18 | `public int amount;` |
| 0x1C | `public int skin;` |
| 0x20 | `public int ammo;` |
| 0x24 | `public float durability;` |
| 0x28 | `public string cost;` |
| 0x30 | `public int costPerItem;` |
| 0x34 | `public int available;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A52BA0 | 0x2E40E28 |  | `public void .ctor()` |

</details>

### public class `ShopOrders`  
`TypeDefIndex 2921`

| offset | field |
|---|---|
| 0x10 | `public List<ShopOrder> orders;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A52B98 | 0x2E40E30 |  | `public void .ctor()` |

</details>

### public class `SkinObject`  
`TypeDefIndex 2922`

| offset | field |
|---|---|
| 0x10 | `private AssetReference m_PreviewObjectRef;` |
| 0x18 | `private AssetReference m_WorldObjectRef;` |

Properties: `public GameObject sgk { get; }`; `public GameObject sgO { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E5354 | 0x2E40E38 |  | `public GameObject get_sgk()` |
| 0x39E53F4 | 0x2E40E40 |  | `public GameObject get_sgO()` |
| 0x39E5494 | 0x2E40E48 |  | `public void .ctor()` |

</details>

### public class `SleepingBag` : vd  
`TypeDefIndex 2923`

| offset | field |
|---|---|
| 0x6C | `private Vector3 m_SpawnPosOffset;` |
| 0x78 | `private float usageDelay;` |
| 0x80 | `private BuildingPiece m_Piece;` |
| 0x0 | `private static readonly Dictionary<string, List<SleepingBag>> Oxy;` |
| 0x88 | `public float lastUseTime;` |
| - | `private Xn <ItemType>k__BackingField;` |

Properties: `public Vector3 svp { get; }`; `public Xn ItemType { get; set; }`; `public float svv { get; set; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E40E50 |  | `public Vector3 get_svp()` |
| - | 0x2E40E7C |  | `public Xn get_ItemType()` |
| - | 0x2E40E84 |  | `private void set_ItemType(Xn value)` |
| - | 0x2E40E8C |  | `public float get_svv()` |
| - | 0x2E40E94 |  | `public void set_svv(float value)` |
| 0x3A04E50 | 0x2E40E9C |  | `public void .ctor()` |
| 0x3A04F00 | 0x2E40EA4 | 12 | `public override bool Fuk()` |
| 0x3A04FC8 | 0x2E40EAC | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A05028 | 0x2E40EB0 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `SmeltingStation` : Xb, Xa  
`TypeDefIndex 2925`

| offset | field |
|---|---|
| - | `private const float Oxz = 0.1;` |
| 0x80 | `public Xq<bool> IsBurning;` |
| 0x88 | `public Xr BurnedItem;` |
| 0x90 | `public ItemContainer inventory;` |
| 0xB0 | `private XV m_Type;` |
| 0xB4 | `private int m_LootContainerSize;` |
| 0xB8 | `private ParticleSystem[] m_Fire;` |
| 0xC0 | `private AudioSource m_FireSource;` |
| 0xC8 | `private Firelight m_FireLight;` |
| 0xD0 | `private float m_FireVolume;` |
| 0xD8 | `private GameObject[] m_EnabledObject;` |
| 0xE0 | `private GameObject[] m_DisabledObject;` |
| 0xE8 | `private bool blockInput;` |
| 0xE9 | `private bool stopWithoutInput;` |
| 0xF0 | `private GameObject m_DamageArea;` |
| 0xF8 | `private GameObject m_TemperatureTrigger;` |
| 0x100 | `private WaitForSeconds OxR;` |
| 0x108 | `private Coroutine Oxb;` |
| 0x110 | `private float Oxl;` |
| 0x114 | `private float Oxx;` |
| 0x118 | `private float OxK;` |
| 0x11C | `private float OxG;` |
| 0x120 | `private LootSpawn OxP;` |
| 0x128 | `private LootSpawn OxD;` |
| 0x130 | `public bool burning;` |
| 0x131 | `public bool blocked;` |
| 0x134 | `public float progress;` |
| 0x138 | `private int Oxn;` |

Properties: `public ItemHolder Oxh { get; set; }`; `public ItemHolder OxB { get; set; }`; `public ItemHolder[] Oxm { get; set; }`; `public bool svS { get; set; }`; `public bool svI { get; set; }`; `public float svM { get; set; }`

<details><summary>methods (30)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A050D0 | 0x2E40F00 |  | `public ItemHolder get_Oxh()` |
| 0x3A050D8 | 0x2E40F08 |  | `private void set_Oxh(ItemHolder value)` |
| 0x3A050E0 | 0x2E40F0C |  | `public ItemHolder get_OxB()` |
| 0x3A050E8 | 0x2E40F14 |  | `private void set_OxB(ItemHolder value)` |
| 0x3A050F0 | 0x2E40F18 |  | `public ItemHolder[] get_Oxm()` |
| 0x3A050F8 | 0x2E40F20 |  | `private void set_Oxm(ItemHolder[] value)` |
| 0x3A05FB8 | 0x2E40F24 |  | `public bool get_svS()` |
| 0x3A05B64 | 0x2E40F2C |  | `public void set_svS([In] bool value)` |
| 0x3A05FC0 | 0x2E40F30 |  | `public bool get_svI()` |
| 0x3A05FC8 | 0x2E40F38 |  | `public void set_svI([In] bool value)` |
| 0x3A06084 | 0x2E40F3C |  | `public float get_svM()` |
| 0x3A0608C | 0x2E40F44 |  | `public void set_svM([In] float value)` |
| 0x3A05100 | 0x2E40F48 |  | `private void Awake()` |
| 0x3A0529C | 0x2E41090 |  | `private void OnEnable()` |
| 0x3A0534C | 0x2E411E0 | 13 | `public override void dHP()` |
| 0x3A05424 | 0x2E416A0 | 11 | `public override void Fsv()` |
| 0x3A055C0 | 0x2E41830 | 10 | `public override void diJ()` |
| 0x3A05678 | 0x2E41834 |  | `public void cRP(bool e)` |
| 0x3A0579C | 0x2E41838 | 33 | `public override bool drE(out string e)` |
| 0x3A057BC | 0x2E41370 |  | `private void cRD()` |
| 0x3A05560 | 0x2E41858 |  | `private void cRn()` |
| 0x3A05D9C | 0x2E4185C |  | `private void cRV()` |
| 0x3A05E7C | 0x2E41860 |  | `public void cRg(int e)` |
| 0x3A05E84 | 0x2E41864 |  | `public void .ctor()` |
| 0x3A05FB0 | 0x2E4186C | 12 | `public override bool Fuk()` |
| 0x3A06144 | 0x2E41874 |  | `protected void cbf(bool e)` |
| 0x3A061DC | 0x2E419B4 |  | `protected static void cbF(vd e, vo f, vt F)` |
| 0x3A06318 | 0x2E419B8 |  | `private static void .cctor()` |
| 0x3A06444 | 0x2E41AD0 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3A06500 | 0x2E41AD4 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `SoundPlayer`  
`TypeDefIndex 2926`

| offset | field |
|---|---|
| 0x10 | `private AudioClip[] m_Sounds;` |
| 0x18 | `private Vector2 m_VolumeRange;` |
| 0x20 | `private Vector2 m_PitchRange;` |
| 0x28 | `private int OGN;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A15DFC | 0x2E41D24 |  | `public void cKk(Tc e, AudioSource f, float F = 1)` |
| 0x3A1601C | 0x2E41F38 |  | `public void cKO(AudioSource e)` |
| 0x3A16034 | 0x2E41FB4 |  | `public void cKt(Tc e, Vector3 f, float F = 1)` |
| 0x3A160D4 | 0x2E420C4 |  | `public void cKr(Tc e)` |
| 0x3A15F00 | 0x2E41E68 |  | `private int cKN(Tc e)` |
| 0x3A161E0 | 0x2E42240 |  | `public void .ctor()` |

</details>

### public class `SpawnPoint`  
`TypeDefIndex 2927`

| offset | field |
|---|---|
| 0x10 | `public Vector3 ODN;` |
| 0x1C | `public Quaternion ODq;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A42108 | 0x2E42264 |  | `public void .ctor()` |

</details>

### public class `StatDepleter`  
`TypeDefIndex 2928`

| offset | field |
|---|---|
| 0x10 | `private float m_DepletionRate;` |
| 0x14 | `private float m_Damage;` |
| 0x18 | `private float m_DamagePeriod;` |
| 0x1C | `private Lf.Le m_DamageType;` |
| 0x20 | `private float OmB;` |
| 0x24 | `private int Omm;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DE2AC | 0x2E4226C |  | `public void Update(Xq<float> statValue, XO<Xf> healthChanger, float deltaTime)` |
| 0x39DE4D8 | 0x2E42270 |  | `public void .ctor()` |

</details>

### public class `StatRegenData`  
`TypeDefIndex 2929`

| offset | field |
|---|---|
| 0x10 | `private bool m_Enabled;` |
| 0x14 | `private float m_Pause;` |
| 0x18 | `private float m_Speed;` |
| 0x1C | `private float Oma;` |

Properties: `public bool sVz { get; }`; `public bool sVh { get; }`; `public bool sVB { get; }`; `public float sVm { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39DD8E0 | 0x2E42278 |  | `public bool get_sVz()` |
| 0x39DD938 | 0x2E42280 |  | `public bool get_sVh()` |
| 0x39DD914 | 0x2E42288 |  | `public bool get_sVB()` |
| 0x39DD940 | 0x2E42290 |  | `public float get_sVm()` |
| 0x39DD948 | 0x2E42298 |  | `public void ciu()` |
| 0x39DD96C | 0x2E4229C |  | `public void .ctor()` |

</details>

### public class `SurfaceData`  
`TypeDefIndex 2930`

| offset | field |
|---|---|
| - | `private const int OKK = 100;` |
| - | `private const int OKG = 100;` |
| - | `private const int OKP = 25;` |
| - | `private const int OKD = 25;` |
| 0x10 | `private string m_Name;` |
| 0x18 | `private Texture[] m_Textures;` |
| 0x20 | `private SoundPlayer m_FootstepSounds;` |
| 0x28 | `private SoundPlayer m_JumpSounds;` |
| 0x30 | `private SoundPlayer m_LandSounds;` |
| 0x38 | `private SoundPlayer m_BulletImpactSounds;` |
| 0x40 | `private GameObject[] m_BulletDecals;` |
| 0x48 | `private GameObject[] m_BulletImpactFX;` |
| 0x50 | `private SoundPlayer m_ChopSounds;` |
| 0x58 | `private SoundPlayer m_HitSounds;` |
| 0x60 | `private GameObject[] m_ChopFX;` |
| 0x68 | `private GameObject[] m_HitFX;` |
| 0x70 | `private bool m_IsPenetrable;` |
| 0x78 | `private SoundPlayer m_SpearPenetrationSounds;` |
| 0x80 | `private SoundPlayer m_ArrowPenetrationSounds;` |
| 0x88 | `private int OKn;` |

Properties: `public string sSr { get; }`; `public bool sSN { get; }`; `public Texture[] sSq { get; }`; `public SoundPlayer Footsteps { get; }`; `public SoundPlayer Jump { get; }`; `public SoundPlayer Land { get; }`; `public SoundPlayer BulletImpact { get; }`; `public SoundPlayer Chop { get; }`; `public SoundPlayer Hit { get; }`; `public SoundPlayer SpearPenetration { get; }`; `public SoundPlayer ArrowPenetration { get; }`

<details><summary>methods (21)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E422A4 |  | `public string get_sSr()` |
| - | 0x2E422AC |  | `public bool get_sSN()` |
| - | 0x2E422B4 |  | `public Texture[] get_sSq()` |
| - | 0x2E422BC |  | `public SoundPlayer get_Footsteps()` |
| - | 0x2E422C4 |  | `public SoundPlayer get_Jump()` |
| - | 0x2E422CC |  | `public SoundPlayer get_Land()` |
| - | 0x2E422D4 |  | `public SoundPlayer get_BulletImpact()` |
| - | 0x2E422DC |  | `public SoundPlayer get_Chop()` |
| - | 0x2E422E4 |  | `public SoundPlayer get_Hit()` |
| - | 0x2E422EC |  | `public SoundPlayer get_SpearPenetration()` |
| - | 0x2E422F4 |  | `public SoundPlayer get_ArrowPenetration()` |
| 0x3A0FC20 | 0x2E422FC |  | `public bool clV(Texture e)` |
| 0x3A0A2A4 | 0x2E424E8 |  | `public void clp(Tc e, TU f, float F = 1, AudioSource d)` |
| 0x3A0FCC4 | 0x2E4255C |  | `public void clv(Tc e, TU f, float F = 1, Vector3 d)` |
| 0x3A0FD70 | 0x2E4262C |  | `public void clS(Vector3 e, Quaternion f, Transform F)` |
| 0x3A0FFAC | 0x2E42754 |  | `public void clI(Vector3 e, Quaternion f, Transform F)` |
| 0x3A101E8 | 0x2E42760 |  | `public void clM(Vector3 e, Quaternion f, Transform F)` |
| 0x3A10424 | 0x2E4276C |  | `public void cxe(Vector3 e, Quaternion f, Transform F)` |
| - | 0x2E425BC |  | `private SoundPlayer SoundFor(TU kind)` |
| - | 0x2E42638 |  | `private static void Spawn(GameObject[] prefabs, Vector3 point, Quaternion rotation, Transform parent, float life)` |
| 0x3A10660 | 0x2E42940 |  | `public void .ctor()` |

</details>

### public sealed class `SurfaceDatabase` : BaseSurfaceDatabase  
`TypeDefIndex 2931`

| offset | field |
|---|---|
| 0x18 | `private SurfaceData m_DefaultSurface;` |
| 0x20 | `private SurfaceData[] m_Surfaces;` |

Properties: `public override SurfaceData sSO { get; }`; `public override SurfaceData[] sSt { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A10E60 | 0x2E42948 | 4 | `public override SurfaceData get_sSO()` |
| 0x3A10E68 | 0x2E42950 | 5 | `public override SurfaceData[] get_sSt()` |
| 0x3A10E70 | 0x2E42958 |  | `public SurfaceData cxW(Texture e)` |
| 0x3A10F04 | 0x2E429E0 | 6 | `protected override Texture clG(Collider e, Vector3 f)` |
| 0x3A10FF4 | 0x2E42D70 |  | `private int cxE(Vector3 e, float[] f)` |
| 0x3A1105C | 0x2E42D78 |  | `public void .ctor()` |

</details>

### public sealed class `SurfaceFxPool` : MonoBehaviour  
`TypeDefIndex 2932`

| offset | field |
|---|---|
| - | `private const int MaxIdlePerPrefab = 24;` |
| - | `private static SurfaceFxPool instance;` |
| - | `private readonly Dictionary<GameObject, Stack<SurfaceFxPooled>> idle;` |
| - | `private readonly List<SurfaceFxPooled> live;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E42778 |  | `public static void Spawn(GameObject prefab, Vector3 point, Quaternion rotation, Transform parent, float life)` |
| - | 0x2E42D80 |  | `private void Take(GameObject prefab, Vector3 point, Quaternion rotation, Transform parent, float life)` |
| - | 0x2E432F4 |  | `private void Update()` |
| - | 0x2E43438 |  | `private void Return(SurfaceFxPooled fx)` |
| - | 0x2E435FC |  | `public void .ctor()` |

</details>

### public sealed class `SurfaceFxPooled` : MonoBehaviour  
`TypeDefIndex 2933`

| offset | field |
|---|---|
| - | `public GameObject prefab;` |
| - | `public float expires;` |
| - | `private ParticleSystem[] particles;` |
| - | `private TrailRenderer[] trails;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E4325C |  | `public void Cache()` |
| - | 0x2E430F4 |  | `public void Restart()` |
| - | 0x2E436D8 |  | `public void .ctor()` |

</details>

### public class `SurfaceIdentity` : MonoBehaviour  
`TypeDefIndex 2934`

| offset | field |
|---|---|
| 0x20 | `private Texture m_Texture;` |

Properties: `public Texture sSs { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A11064 | 0x2E436E0 |  | `public Texture get_sSs()` |
| 0x3A1106C | 0x2E436E8 |  | `public void set_sSs(Texture value)` |
| 0x3A11074 | 0x2E436F0 |  | `public void .ctor()` |

</details>

### public class `Sway`  
`TypeDefIndex 2935`

| offset | field |
|---|---|
| 0x18 | `private bool Enabled;` |
| 0x1C | `private Vector2 Magnitude;` |
| 0x24 | `private Vector2 MaxValue;` |
| 0x2C | `private float LerpSpeed;` |
| - | `private Vector2 <OGF>k__BackingField;` |

Properties: `public Vector2 OGF { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E436F8 |  | `public Vector2 get_OGF()` |
| - | 0x2E43700 |  | `private void set_OGF(Vector2 value)` |
| 0x3A141E0 | 0x2E43708 |  | `public Sway cxV()` |
| 0x3A14260 | 0x2E43790 |  | `public void cxg(Vector2 e, float f)` |
| 0x3A142C0 | 0x2E43788 |  | `public void .ctor()` |

</details>

### public sealed class `TerrainSurfaceBinding` : MonoBehaviour  
`TypeDefIndex 2936`

| offset | field |
|---|---|
| - | `public string[] LayerTypes;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E437F0 |  | `public static void BindGenerated(Terrain terrain)` |
| - | 0x2E43AA0 |  | `internal static string Canonical(string name)` |
| - | 0x2E43C70 |  | `internal static SurfaceData Resolve(BaseSurfaceDatabase database, Collider collider, Vector3 point)` |
| - | 0x2E4423C |  | `public void .ctor()` |

</details>

### public class `TimeOfDay` : Lc<TimeOfDay>  
`TypeDefIndex 2937`

| offset | field |
|---|---|
| 0x20 | `public Xq<Lf.TS> State;` |
| 0x28 | `private Light m_Sun;` |
| 0x30 | `private Light m_Moon;` |
| 0x38 | `private bool m_StopTime;` |
| 0x39 | `private bool m_ShowGUI;` |
| 0x3C | `private int m_CurrentHour;` |
| 0x40 | `private int m_DefaultHour;` |
| 0x44 | `private int m_DayDuration;` |
| 0x48 | `private Vector3 m_RotationAxis;` |
| 0x54 | `private FogMode m_FogMode;` |
| 0x58 | `private AnimationCurve m_FogIntensity;` |
| 0x60 | `private Gradient m_FogColor;` |
| 0x68 | `private Gradient m_AmbientLightColor;` |
| 0x70 | `private AnimationCurve m_SunIntensity;` |
| 0x78 | `private Gradient m_SunColor;` |
| 0x80 | `private AnimationCurve m_MoonIntensity;` |
| 0x88 | `private Gradient m_MoonColor;` |
| 0x90 | `private Material m_Skybox;` |
| 0x98 | `private AnimationCurve m_SkyboxBlend;` |
| 0xA0 | `private Lf.TS OmD;` |
| 0xA8 | `private Transform Omn;` |
| 0xB0 | `private Transform OmV;` |
| 0xB8 | `private float Omg;` |
| 0xBC | `private float Omp;` |
| 0xC0 | `private int Omv;` |
| 0xC4 | `private float OmS;` |

Properties: `public float sVp { get; set; }`; `public int sVv { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39E0658 | 0x2E44244 |  | `public float get_sVp()` |
| 0x39E0660 | 0x2E4424C |  | `public void set_sVp(float value)` |
| 0x39E06C8 | 0x2E44250 |  | `public int get_sVv()` |
| 0x39E06D0 | 0x2E44258 |  | `private void Awake()` |
| 0x39E0930 | 0x2E4425C |  | `private void OnGUI()` |
| 0x39E0BF8 | 0x2E44260 |  | `private void Update()` |
| 0x39E1008 | 0x2E44264 |  | `private void OnValidate()` |
| 0x39E08FC | 0x2E44268 |  | `private void cwX()` |
| 0x39E109C | 0x2E4426C |  | `public string cwT()` |
| 0x39E115C | 0x2E44274 |  | `public void .ctor()` |

</details>

### public class `TransformOffset`  
`TypeDefIndex 2938`

| offset | field |
|---|---|
| 0x10 | `private float m_LerpSpeed;` |
| 0x14 | `private Vector3 m_Position;` |
| 0x20 | `private Vector3 m_Rotation;` |
| 0x2C | `private Vector3 ObP;` |
| 0x38 | `private Vector3 ObD;` |

Properties: `public Vector3 svA { get; }`; `public Vector3 svu { get; }`; `public Vector3 svk { get; }`; `public Vector3 svO { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E442BC |  | `public Vector3 get_svA()` |
| - | 0x2E442C8 |  | `public Vector3 get_svu()` |
| - | 0x2E442D4 |  | `public Vector3 get_svk()` |
| - | 0x2E442E0 |  | `public Vector3 get_svO()` |
| 0x39F7328 | 0x2E442EC |  | `public TransformOffset czB()` |
| 0x39F73A8 | 0x2E4437C |  | `public void Reset()` |
| 0x39F7404 | 0x2E443E8 |  | `public void czm(Vector3 e, Vector3 f)` |
| 0x39F7414 | 0x2E443F8 |  | `public void czR(TransformOffset e)` |
| 0x39F7448 | 0x2E4442C |  | `public void Update(float deltaTime, out Vector3 position, out Quaternion rotation)` |
| 0x39F7584 | 0x2E44374 |  | `public void .ctor()` |

</details>

### public class `TreeCreator`  
`TypeDefIndex 2940`

| offset | field |
|---|---|
| 0x10 | `private int m_PrototypeIndex;` |
| 0x18 | `private MineableObject m_Prefab;` |
| 0x20 | `private Vector3 m_PositionOffset;` |
| 0x2C | `private Vector3 m_RotationOffset;` |
| 0x38 | `private TreeManager OxS;` |

Properties: `public int sSe { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A06674 | 0x2E44568 |  | `public int get_sSe()` |
| 0x3A0667C | 0x2E44570 |  | `public MineableObject cbU(TreeManager e, Terrain f, TreeInstance F, int d)` |
| 0x3A06AD8 | 0x2E44578 |  | `private void cbY(Terrain e, TreeInstance f, int F)` |
| 0x3A06C80 | 0x2E4457C |  | `public void .ctor()` |

</details>

### public class `TreeManager` : vd  
`TypeDefIndex 2941`

| offset | field |
|---|---|
| 0x68 | `private TreeCreator[] m_TreeCreators;` |
| 0x70 | `private Terrain OxI;` |
| 0x78 | `private List<MineableObject> OxM;` |
| 0x80 | `private TreeInstance[] OKe;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A06D78 | 0x2E44598 |  | `private void Awake()` |
| 0x3A06F30 | 0x2E4459C |  | `private TreeCreator cbW(int e)` |
| 0x3A06B5C | 0x2E445A4 |  | `public void cbE(int e)` |
| 0x3A06F8C | 0x2E445A8 |  | `private void OnApplicationQuit()` |
| 0x3A06FBC | 0x2E445AC |  | `public void .ctor()` |
| 0x3A07044 | 0x2E445B4 | 12 | `public override bool Fuk()` |
| 0x3A0704C | 0x2E445BC |  | `protected void cbA(int e)` |
| 0x3A07154 | 0x2E445C0 |  | `protected static void cbu(vd e, vo f, vt F)` |
| 0x3A07294 | 0x2E445C4 |  | `private static void .cctor()` |

</details>

### public class `TrigonometricBob`  
`TypeDefIndex 2942`

| offset | field |
|---|---|
| - | `private const float OGd = 1;` |
| - | `private const float OGc = 2;` |
| 0x10 | `private bool m_Enabled;` |
| 0x14 | `private float m_Speed;` |
| 0x18 | `private float m_CooldownSpeed;` |
| 0x1C | `private float m_AmountX;` |
| 0x20 | `private float m_AmountY;` |
| 0x28 | `private AnimationCurve m_Curve;` |
| 0x30 | `private float OGU;` |
| 0x34 | `private Vector3 OGY;` |

Properties: `public float sSj { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E445C8 |  | `public float get_sSj()` |
| 0x3A142D0 | 0x2E445D0 |  | `public TrigonometricBob cxv()` |
| 0x3A14350 | 0x2E44650 |  | `public Vector3 cxS(float e, float f)` |
| 0x3A14468 | 0x2E44774 |  | `public Vector3 cxI(float e)` |
| 0x3A14584 | 0x2E44894 |  | `private float cxM(float e)` |
| 0x3A145D8 | 0x2E448E8 |  | `public void .ctor()` |

</details>

### public sealed class `TryerDelegate` : MulticastDelegate  
`TypeDefIndex 2943`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E44A3C |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2E44AD8 |  | `public virtual bool Invoke()` |
| - | 0x2E44AEC |  | `public virtual IAsyncResult BeginInvoke(AsyncCallback callback, object object)` |
| - | 0x2E44B0C |  | `public virtual bool EndInvoke(IAsyncResult result)` |

</details>

### public class `VirtualItem`  
`TypeDefIndex 2944`

| offset | field |
|---|---|
| 0x24 | `private int m_Amount;` |
| - | `private ItemData <ORa>k__BackingField;` |
| - | `private int <ORQ>k__BackingField;` |
| - | `private int <ORH>k__BackingField;` |
| - | `private float <ORi>k__BackingField;` |

Properties: `public ItemData ORa { get; set; }`; `public int sgY { get; }`; `public string sgW { get; }`; `public int sgE { get; set; }`; `public int ORQ { get; set; }`; `public int ORH { get; set; }`; `public float ORi { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E44B34 |  | `public ItemData get_ORa()` |
| - | 0x2E44B3C |  | `private void set_ORa(ItemData value)` |
| - | 0x2E44B44 |  | `public int get_sgY()` |
| - | 0x2E44BC0 |  | `public string get_sgW()` |
| - | 0x2E44C3C |  | `public int get_sgE()` |
| - | 0x2E44C44 |  | `public void set_sgE(int value)` |
| - | 0x2E44C4C |  | `public int get_ORQ()` |
| - | 0x2E44C54 |  | `private void set_ORQ(int value)` |
| - | 0x2E44C5C |  | `public int get_ORH()` |
| - | 0x2E44C64 |  | `private void set_ORH(int value)` |
| - | 0x2E44C6C |  | `public float get_ORi()` |
| - | 0x2E44C74 |  | `private void set_ORi(float value)` |
| 0x39E5108 | 0x2E44C7C |  | `public void .ctor(ItemData data, int currentInStack = 1, float durability = -1, int ammo = -1, int skin = -1)` |
| 0x39E5178 | 0x2E44CDC |  | `public bool cXE()` |
| 0x39E5188 | 0x2E44CE4 |  | `public bool cXA()` |
| 0x39E519C | 0x2E44CEC |  | `public Xj.Value cXu(string e)` |
| 0x39E5278 | 0x2E44CF4 |  | `public bool cXk(VirtualItem e)` |

</details>

### public class `WeaponChanging` : StateMachineBehaviour  
`TypeDefIndex 2945`

| offset | field |
|---|---|
| 0x18 | `private PlayerWeapon weaponManager;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A52BA8 | 0x2E44CFC | 4 | `public override void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)` |
| 0x3A52C64 | 0x2E44D00 |  | `public void .ctor()` |

</details>

### public struct `WeaponPiece`  
`TypeDefIndex 2946`

| offset | field |
|---|---|
| 0x0 | `public bool Enabled;` |
| 0x4 | `public int Number;` |
| 0x8 | `public int Skin;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A25570 | 0x2E44D08 |  | `public void .ctor(bool e, int s, int n)` |

</details>

### public class `WeaponShake`  
`TypeDefIndex 2947`

| offset | field |
|---|---|
| 0x10 | `private float m_Magnitude;` |
| 0x14 | `private float m_Roughness;` |
| 0x18 | `private Vector3 m_PositionInfluence;` |
| 0x24 | `private Vector3 m_RotationInfluence;` |
| 0x30 | `private float m_FadeInTime;` |
| 0x34 | `private float m_FadeOutTime;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D9CFC | 0x2E44D14 |  | `public void cHq()` |
| 0x39DA324 | 0x2E44DD0 |  | `private Jv cHs()` |
| 0x39DA3E8 | 0x2E44E98 |  | `public void .ctor()` |

</details>

### public class `Workbench` : Xb  
`TypeDefIndex 2948`

| offset | field |
|---|---|
| 0x80 | `private BuildingPiece m_Piece;` |

Properties: `public BuildingPiece sIQ { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E44EA0 |  | `public BuildingPiece get_sIQ()` |
| 0x3A52C74 | 0x2E44EA8 |  | `public void .ctor()` |
| 0x3A52C7C | 0x2E44EB0 | 12 | `public override bool Fuk()` |

</details>
