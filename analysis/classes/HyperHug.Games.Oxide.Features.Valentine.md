# namespace `HyperHug.Games.Oxide.Features.Valentine`  (4 types)

### public class `EventShopPurchaseList` : MonoBehaviour  
`TypeDefIndex 3395`

| offset | field |
|---|---|
| 0x20 | `private EventShopUI m_PurchasesManager;` |
| 0x28 | `private RectTransform m_ListTransform;` |
| 0x30 | `private PurchaseSlot m_PurchaseTemplate;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3807CB4 | 0x2F0D384 |  | `private void Start()` |
| 0x3807CEC | 0x2F0D388 |  | `private void dwb()` |
| 0x3808014 | 0x2F0D38C |  | `public void .ctor()` |

</details>

### public class `EventShopUI` : yD, NY  
`TypeDefIndex 3396`

| offset | field |
|---|---|
| 0x28 | `private Window window;` |
| 0x30 | `private BuyWindow m_BuyWindow;` |
| 0x38 | `public Text balance;` |
| 0x40 | `private ScreenControlsManager screenControlsManager;` |
| 0x48 | `public MouseLook mouseLook;` |
| 0x50 | `private Button closeButton;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x380801C | 0x2F0D394 | 4 | `public void SelectItem(PurchaseSlot slot)` |
| 0x38080C0 | 0x2F0D398 | 5 | `public void BuyItem(PurchaseSlot slot, int times)` |
| 0x38081F4 | 0x2F0D39C |  | `public void Open()` |
| 0x38084EC | 0x2F0D3A0 |  | `public void Close()` |
| 0x3808574 | 0x2F0D3A4 |  | `public void .ctor()` |
| 0x380857C | 0x2F0D3AC |  | `private void dwl()` |

</details>

### public class `GrenadeSmoke` : vd  
`TypeDefIndex 3399`

| offset | field |
|---|---|
| - | `private bool smokeStarted;` |
| 0x68 | `private ShaftedProjectile shaftedProjectile;` |
| 0x70 | `private ParticleSystem smokeParticles;` |
| 0x78 | `private ParticleSystem destroyParticles;` |
| 0x80 | `private float destroyTime;` |
| 0x88 | `private CancellationTokenSource kMk;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0D3B0 |  | `private IEnumerator RecoveredDestroyTimer(CancellationToken token)` |
| 0x3808580 | 0x2F0D460 |  | `private void Awake()` |
| 0x38085E0 | 0x2F0D4C0 |  | `private void OnDestroy()` |
| 0x3808640 | 0x2F0D5D4 |  | `private void dwx()` |
| 0x3808758 | 0x2F0D5D8 |  | `private UniTaskVoid dwK(CancellationToken e)` |
| 0x3808814 | 0x2F0D600 |  | `public void .ctor()` |
| 0x3808824 | 0x2F0D608 | 12 | `public override bool Fuk()` |
| 0x380882C | 0x2F0D610 |  | `protected void dwG()` |
| 0x3808884 | 0x2F0D734 |  | `protected static void dwP(vd e, vo f, vt F)` |
| 0x38089A0 | 0x2F0D7B4 |  | `private static void .cctor()` |

</details>

### public class `LootBoxBalloon` : vd  
`TypeDefIndex 3400`

| offset | field |
|---|---|
| 0x68 | `private GameObject lootBoxPrefab;` |
| 0x70 | `private Transform[] lootBoxSpawnPoint;` |
| 0x78 | `private EntityDeathHandler entityDeathHandler;` |
| 0x80 | `private ParticleSystem deathParticles;` |
| 0x88 | `private Vector2 speed;` |
| 0x90 | `private Vector2 distance;` |
| 0x98 | `private PieceVitals pieceVitals;` |
| 0xA0 | `private Vector3 kMO;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3808E90 | 0x2F0DA28 |  | `private void Awake()` |
| 0x3808E94 | 0x2F0DA2C |  | `private void dwD(Xf e, PieceVitals f)` |
| 0x3808F6C | 0x2F0DA30 |  | `private void OnDestroy()` |
| 0x3808F70 | 0x2F0DA34 |  | `private float dwn()` |
| 0x3808FC8 | 0x2F0DA3C |  | `private void dwV()` |
| 0x380914C | 0x2F0DA40 |  | `private void dwg()` |
| 0x3809264 | 0x2F0DA44 |  | `public void .ctor()` |
| 0x380926C | 0x2F0DA4C | 12 | `public override bool Fuk()` |
| 0x3809274 | 0x2F0DA54 |  | `protected void dwp()` |
| 0x38092B4 | 0x2F0DA58 |  | `protected static void dwv(vd e, vo f, vt F)` |
| 0x38093D0 | 0x2F0DA5C |  | `private static void .cctor()` |

</details>
