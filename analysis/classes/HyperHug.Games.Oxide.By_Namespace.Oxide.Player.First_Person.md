# namespace `HyperHug.Games.Oxide.By_Namespace.Oxide.Player.First_Person`  (6 types)

### public class `FPCrossbow` : FPWeaponBase  
`TypeDefIndex 3714`

| offset | field |
|---|---|
| 0xC4 | `private LayerMask m_Mask;` |
| 0xC8 | `private float m_MaxDistance;` |
| 0xD0 | `private FPCrossbowAnimator fpCrossbowAnimator;` |
| 0xD8 | `private HitscanWeaponConfig config;` |
| 0xE0 | `private float m_MinTimeBetweenShots;` |
| 0xE4 | `private float reloadPeriod;` |
| 0xE8 | `public ShaftedProjectile m_ArrowPrefab;` |
| 0xF0 | `private Vector3 m_SpawnOffset;` |
| 0xFC | `private Vector3 aimSpawnOffset;` |
| 0x108 | `private AudioSource m_AudioSource;` |
| 0x110 | `private SoundPlayer m_ReleaseAudio;` |
| 0x118 | `private SoundPlayer m_StretchAudio;` |
| 0x120 | `private float kSX;` |
| 0x128 | `private qg kST;` |

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37F60B4 | 0x2F68880 | 5 | `public override void Initialize()` |
| 0x37F61F4 | 0x2F689DC |  | `private void FixedUpdate()` |
| 0x37F64DC | 0x2F68D30 | 17 | `public override bool daS(Camera e)` |
| 0x37F6480 | 0x2F68C38 |  | `private float daI()` |
| 0x37F6A90 | 0x2F68FA8 | 7 | `protected override void OnDestroy()` |
| 0x37F6B20 | 0x2F6908C | 14 | `public override bool daM(bool e)` |
| 0x37F6C54 | 0x2F6928C |  | `private bool dQe()` |
| 0x37F6C7C | 0x2F692BC |  | `private void dQf()` |
| 0x37F66F4 | 0x2F68E94 |  | `private void dQF(Camera e)` |
| 0x37F6E40 | 0x2F692C0 |  | `private void AnimateThrow()` |
| 0x37F6E7C | 0x2F69300 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x37F6F94 | 0x2F6944C | 11 | `public override void dQd()` |
| 0x37F6F74 | 0x2F6942C |  | `public bool dQc()` |
| 0x37F6FC0 | 0x2F69454 |  | `public void .ctor()` |

</details>

### public class `FPCrossbowAnimator` : FPAnimator  
`TypeDefIndex 3715`

| offset | field |
|---|---|
| 0x48 | `private float m_ReleaseSpeed;` |
| 0x50 | `private WeaponShake m_ReleaseShake;` |
| 0x58 | `private Vector3 m_NoAmmoPosition;` |
| 0x64 | `private Vector3 m_NoAmmoRotation;` |
| 0x70 | `public GameObject arrowPrefab;` |
| 0x78 | `private FPCrossbow kSL;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37F6FD8 | 0x2F6945C | 4 | `public override void dQU()` |
| 0x37F6BB0 | 0x2F691AC |  | `public void Reload()` |
| 0x37F726C | 0x2F69770 |  | `private void On_Reload()` |
| 0x37F7334 | 0x2F69888 | 6 | `protected override void OnDestroy()` |
| 0x37F74B8 | 0x2F69A40 | 7 | `protected override void OnValidate()` |
| 0x37F75B0 | 0x2F69A44 |  | `private void dQY()` |
| 0x37F7644 | 0x2F69B18 |  | `private void dQW()` |
| 0x37F76D4 | 0x2F69C04 |  | `private void dQE()` |
| 0x37F7788 | 0x2F69D10 |  | `public void .ctor()` |

</details>

### public class `FpSkinBowChanger` : FPSkinChanger  
`TypeDefIndex 3716`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37F808C | 0x2F69D18 | 7 | `public override void dQk(GameObject e, GameObject f)` |
| 0x37F8090 | 0x2F69D1C |  | `public void .ctor()` |

</details>

### public class `FPSkinChanger` : MonoBehaviour, jj  
`TypeDefIndex 3717`

| offset | field |
|---|---|
| 0x20 | `private Transform weaponParent;` |
| 0x28 | `private Transform leftWeaponParent;` |
| 0x30 | `private SkinnedMeshRenderer defaultSkinMeshRenderer;` |

Properties: `public Transform sbT { get; }`; `public Transform sRU { get; }`; `public Transform sRY { get; }`; `public Transform sRW { get; }`; `public SkinnedMeshRenderer sbL { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37F7798 | 0x2F69D2C |  | `public Transform get_sbT()` |
| 0x37F77A0 | 0x2F69D34 | 4 | `public Transform get_sRU()` |
| 0x37F77A8 | 0x2F69D3C | 5 | `public Transform get_sRY()` |
| 0x37F77B0 | 0x2F69D44 | 6 | `public Transform get_sRW()` |
| 0x37F77B8 | 0x2F69D4C |  | `public SkinnedMeshRenderer get_sbL()` |
| 0x37F77C0 | 0x2F69D54 | 7 | `public virtual void dQk(GameObject e, GameObject f)` |
| 0x37F77C4 | 0x2F69D24 |  | `public void .ctor()` |

</details>

### public class `FPSnowball` : FPWeaponBase  
`TypeDefIndex 3719`

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
| 0x37F77CC | 0x2F69D58 | 5 | `public override void Initialize()` |
| 0x37F7870 | 0x2F69E44 |  | `private void FixedUpdate()` |
| 0x37F78C0 | 0x2F69E4C | 17 | `public override bool daS(Camera e)` |
| 0x37F7BA4 | 0x2F6A030 | 7 | `protected override void OnDestroy()` |
| 0x37F7C34 | 0x2F6A114 |  | `private bool dQq()` |
| - | 0x2F6A00C |  | `private IEnumerator dQs(Camera e, float f)` |
| 0x37F7C84 | 0x2F6A144 |  | `private void AnimateThrow()` |
| 0x37F7CD8 | 0x2F6A184 | 10 | `public override void On_Draw(Item correspondingItem)` |
| 0x37F7D08 | 0x2F6A22C |  | `public void .ctor()` |

</details>

### public class `TorchView` : MonoBehaviour, qC  
`TypeDefIndex 3722`

| offset | field |
|---|---|
| 0x20 | `private Light light;` |
| 0x28 | `private ParticleSystem particleSystem;` |
| 0x30 | `private float lightIntensity;` |
| 0x34 | `private float lightRange;` |
| 0x38 | `private float lightDrawDuration;` |
| 0x3C | `private float intensityNoise;` |
| 0x40 | `private float volume;` |
| 0x48 | `private AudioSource fireAudioSource;` |
| 0x50 | `private bool kSP;` |
| 0x51 | `private bool _003CkSD_003Ek__BackingField;` |

Properties: `public bool sbz { get; set; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F6A25C |  | `public bool get_sbz()` |
| - | 0x2F6A264 |  | `private void set_sbz(bool value)` |
| 0x37F80AC | 0x2F6A270 | 5 | `public void dQZ(bool e)` |
| 0x37F8100 | 0x2F6A354 |  | `public void OnEnable()` |
| 0x37F81B0 | 0x2F6A404 |  | `private void Update()` |
| 0x37F8130 | 0x2F6A384 |  | `private IEnumerator dQw(bool e)` |
| 0x37F8264 | 0x2F6A504 |  | `public void .ctor()` |

</details>
