# namespace `HyperHug.Games.Oxide.Features.Player`  (18 types)

### public class `CharacterAnimation` : MonoBehaviour  
`TypeDefIndex 3589`

| offset | field |
|---|---|
| 0x20 | `private Animator animator;` |
| 0x28 | `private CharacterSpeedConfig animationSpeedConfig;` |
| 0x30 | `private PlayerModelInfo playerModelInfo;` |
| 0x38 | `private Transform bodyTarget;` |
| 0x40 | `private Transform bodyTargetRoot;` |
| 0x48 | `private Transform headTarget;` |
| 0x50 | `private Transform headTargetRoot;` |
| 0x58 | `private Ragdoll ragdoll;` |
| 0x60 | `private CharacterAnimation.HumanBone[] bones;` |
| 0x68 | `private Transform[] OYH;` |
| 0x70 | `private bool OYi;` |
| 0x78 | `private Quaternion[] OYw;` |
| 0x80 | `private XA OYJ;` |
| 0x88 | `private ZS OYX;` |
| 0x90 | `private PlayerManager OYT;` |
| 0x98 | `private bool OYL;` |
| 0x9C | `private Vector3 OYo;` |
| 0xA8 | `private float OYy;` |

Properties: `public Animator sGC { get; }`; `public Ragdoll sGZ { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3848E48 | 0x2F4F748 |  | `public Animator get_sGC()` |
| 0x3848E50 | 0x2F4F7EC |  | `public Ragdoll get_sGZ()` |
| 0x3848E58 | 0x2F4F7F4 |  | `public void dxU(PlayerManager e, ZS f)` |
| 0x3849068 | 0x2F4FA88 |  | `private void dxY()` |
| 0x3849170 | 0x2F4FC14 |  | `public void dxW(Vector2 e)` |
| 0x384927C | 0x2F4FDDC |  | `public void dxE(Vector2 e)` |
| 0x3849388 | 0x2F4FFA4 |  | `public void dxA(Move e)` |
| 0x38496A8 | 0x2F5038C |  | `public float dxu(jc e)` |
| 0x384983C | 0x2F505D0 |  | `private void OnAnimatorIK(int layerIndex)` |
| 0x3849854 | 0x2F505E8 |  | `private void dxk()` |
| 0x3849688 | 0x2F50360 |  | `public static float dxO(jc e)` |
| 0x3849CC8 | 0x2F50B60 |  | `private Vector3 dxt(HumanBodyBones e)` |
| 0x3849D48 | 0x2F50CE0 |  | `public void .ctor()` |

</details>

### public class `CharacterSpeedConfig` : ScriptableObject  
`TypeDefIndex 3590`

| offset | field |
|---|---|
| - | `private float <StandSprintSpeed>k__BackingField;` |
| - | `private float <StandJogSpeed>k__BackingField;` |
| - | `private float <StandWalkSpeed>k__BackingField;` |
| - | `private float <CrouchJogSpeed>k__BackingField;` |
| - | `private float <CrouchWalkSpeed>k__BackingField;` |
| - | `private float <BackSpeedFactor>k__BackingField;` |
| - | `private float <JumpHeight>k__BackingField;` |
| - | `private float <Gravity>k__BackingField;` |
| - | `private float <JumpSpeedFromLadder>k__BackingField;` |
| - | `private float <SpeedOnLadder>k__BackingField;` |
| - | `private float <SlidingSpeed>k__BackingField;` |
| - | `private float <SwimSpeed>k__BackingField;` |
| - | `private float <SwimBackSpeedFactor>k__BackingField;` |

Properties: `public float StandSprintSpeed { get; set; }`; `public float StandJogSpeed { get; set; }`; `public float StandWalkSpeed { get; set; }`; `public float CrouchJogSpeed { get; set; }`; `public float CrouchWalkSpeed { get; set; }`; `public float BackSpeedFactor { get; set; }`; `public float JumpHeight { get; set; }`; `public float Gravity { get; set; }`; `public float JumpSpeedFromLadder { get; set; }`; `public float SpeedOnLadder { get; set; }`; `public float SlidingSpeed { get; set; }`; `public float SwimSpeed { get; set; }`; `public float SwimBackSpeedFactor { get; set; }`; `public float sGQ { get; }`

<details><summary>methods (29)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F50CF0 |  | `public float get_StandSprintSpeed()` |
| - | 0x2F50CF8 |  | `private void set_StandSprintSpeed(float value)` |
| - | 0x2F50D00 |  | `public float get_StandJogSpeed()` |
| - | 0x2F50D08 |  | `private void set_StandJogSpeed(float value)` |
| - | 0x2F50D10 |  | `public float get_StandWalkSpeed()` |
| - | 0x2F50D18 |  | `private void set_StandWalkSpeed(float value)` |
| - | 0x2F50D20 |  | `public float get_CrouchJogSpeed()` |
| - | 0x2F50D28 |  | `private void set_CrouchJogSpeed(float value)` |
| - | 0x2F50D30 |  | `public float get_CrouchWalkSpeed()` |
| - | 0x2F50D38 |  | `private void set_CrouchWalkSpeed(float value)` |
| - | 0x2F50D40 |  | `public float get_BackSpeedFactor()` |
| - | 0x2F50D48 |  | `private void set_BackSpeedFactor(float value)` |
| - | 0x2F50D50 |  | `public float get_JumpHeight()` |
| - | 0x2F50D58 |  | `private void set_JumpHeight(float value)` |
| - | 0x2F50D60 |  | `public float get_Gravity()` |
| - | 0x2F50D68 |  | `private void set_Gravity(float value)` |
| - | 0x2F50D70 |  | `public float get_JumpSpeedFromLadder()` |
| - | 0x2F50D78 |  | `private void set_JumpSpeedFromLadder(float value)` |
| - | 0x2F50D80 |  | `public float get_SpeedOnLadder()` |
| - | 0x2F50D88 |  | `private void set_SpeedOnLadder(float value)` |
| - | 0x2F50D90 |  | `public float get_SlidingSpeed()` |
| - | 0x2F50D98 |  | `private void set_SlidingSpeed(float value)` |
| - | 0x2F50DA0 |  | `public float get_SwimSpeed()` |
| - | 0x2F50DA8 |  | `private void set_SwimSpeed(float value)` |
| - | 0x2F50DB0 |  | `public float get_SwimBackSpeedFactor()` |
| - | 0x2F50DB8 |  | `private void set_SwimBackSpeedFactor(float value)` |
| 0x384A4F4 | 0x2F50DC0 |  | `public float get_sGQ()` |
| 0x384A508 | 0x2F50DC8 |  | `private float dxZ()` |
| 0x384A51C | 0x2F50DD0 |  | `public void .ctor()` |

</details>

### public class `EquipmentObjectSkinData` : EquipmentPieceSkinData  
`TypeDefIndex 3591`

| offset | field |
|---|---|
| 0x0 | `private static readonly int Cull;` |
| 0x30 | `public AssetReference gameObjectRef;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x384B540 | 0x2F50DD8 | 6 | `public override QT dxi(GameObject e, QT f, jt F)` |
| 0x384B998 | 0x2F51234 | 5 | `public override QT dxw(GameObject e, QT f, jt F)` |
| 0x384BC84 | 0x2F51520 | 4 | `public override QT dxJ(QT e, int f = 0)` |
| 0x384BCBC | 0x2F51558 |  | `public void .ctor()` |
| - | 0x2F51568 |  | `private static void .cctor()` |

</details>

### public abstract class `EquipmentPieceSkinData` : SkinData  
`TypeDefIndex 3592`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x384BA60 | 0x2F512FC | 5 | `public virtual QT dxw(GameObject e, QT f, jt F)` |
| - | - |  | `public abstract QT dxi(GameObject e, QT f, jt F);` |
| 0x384BD48 | 0x2F515D0 |  | `private void dxX(GameObject e, jt f, QT F)` |
| 0x384BE54 | 0x2F516DC | 7 | `protected virtual void dxT(SkinnedMeshRenderer[] e, SkinnedMeshRenderer f, Transform F, QT d)` |
| 0x384BCC4 | 0x2F51560 |  | `protected void .ctor()` |

</details>

### public class `EquipmentRecolorSkinData` : EquipmentPieceSkinData  
`TypeDefIndex 3593`

| offset | field |
|---|---|
| 0x0 | `private static readonly int Cull;` |
| 0x30 | `public AssetReference materialRef;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x384BF70 | 0x2F51824 | 7 | `protected override void dxT(SkinnedMeshRenderer[] e, SkinnedMeshRenderer f, Transform F, QT d)` |
| 0x384C0F0 | 0x2F519B0 | 6 | `public override QT dxi(GameObject e, QT f, jt F)` |
| 0x384C548 | 0x2F51E0C | 4 | `public override QT dxJ(QT e, int f = 0)` |
| 0x384C658 | 0x2F51F1C |  | `public void .ctor()` |
| - | 0x2F51F24 |  | `private static void .cctor()` |

</details>

### public class `KCC` : vd, bz, jL  
`TypeDefIndex 3596`

| offset | field |
|---|---|
| - | `private const float OWF = 0.3;` |
| - | `private const int OWd = 256;` |
| - | `private const int OWc = 8;` |
| - | `private const float OWU = 32;` |
| - | `private const float OWY = 0.03125;` |
| 0x70 | `public HitBoxRecorderRoot hitBoxRecorderRoot;` |
| 0x78 | `public PlayerManager player;` |
| 0x80 | `private CharacterSpeedConfig characterSpeedConfig;` |
| 0x88 | `public Transform head;` |
| 0x90 | `private float lookHeightOffset;` |
| 0x94 | `private float m_AirControl;` |
| 0x98 | `private float stableMovementSharpness;` |
| 0x9C | `private bool m_EnableRunning;` |
| 0x9D | `private bool m_EnableJumping;` |
| 0x9E | `private bool m_EnableCrouching;` |
| 0xA0 | `private float normalHeight;` |
| 0xA4 | `private float m_CrouchHeight;` |
| 0xA8 | `private float crouchSpeed;` |
| 0xAC | `private bool interpolate;` |
| 0xB0 | `public Animator m_Animator;` |
| 0xB8 | `private CharacterAnimation OWW;` |
| 0xC0 | `private ZS OWE;` |
| 0xC8 | `private float OWA;` |
| 0xCC | `private Vector3 OWu;` |
| 0xD8 | `private Vector3 OWk;` |
| 0xE4 | `private KCC.jd OWO;` |
| 0xE8 | `private bool OWt;` |
| 0xEC | `private PlayerInput OWr;` |
| 0x10C | `private Move OWN;` |
| 0x148 | `private Terrain OWq;` |
| 0x150 | `private float OWs;` |
| 0x154 | `private Vector3 OWC;` |
| 0x160 | `private float OWZ;` |
| 0x168 | `private Collider[] OWj;` |
| 0x170 | `private bool OWa;` |
| 0x174 | `private float OWQ;` |
| 0x178 | `private float OWH;` |
| 0x17C | `private float OWi;` |
| 0x180 | `private uint OWw;` |
| 0x184 | `private uint OWJ;` |
| 0x188 | `private double OWX;` |
| 0x190 | `private jF<PlayerInput> OWT;` |
| 0x198 | `private jF<Move> OWL;` |
| 0x1A0 | `private jF<Move> OWo;` |
| 0x1C4 | `public float speedModifier;` |
| 0x1C8 | `public vN visibility;` |
| 0x1CC | `private bool OWR;` |
| 0x1D0 | `private double OWb;` |
| 0x1D8 | `public Action<vN, vN> _Mirror_SyncVarHookDelegate_visibility;` |
| 0x68 | `private KinematicCharacterMotor _0x68;` |
| 0x1B4 | `private int _0x1B4;` |
| 0x1A8 | `private Vector3 _0x1A8;` |
| 0x1BC | `private float _0x1BC;` |
| 0x1C0 | `private int _0x1C0;` |
| 0x1B8 | `private byte _0x1B8;` |
| - | `private bool bodyAnimation;` |
| - | `private bool <LocalFlight>k__BackingField;` |
| - | `private Vector3 bodyLastPosition;` |
| - | `private float bodyLastAt;` |
| - | `private uint remoteSeen;` |
| - | `private readonly Collider[] ladderOverlaps;` |
| - | `private bool hadLadderContact;` |

Properties: `public KinematicCharacterMotor Motor { get; set; }`; `private float sGw { get; }`; `private XA sGJ { get; }`; `private bool sGX { get; }`; `public float sGT { get; }`; `public Vector3 InteractionFeet { get; }`; `public bool PhysicalCrouch { get; }`; `public float sGL { get; }`; `public float sGo { get; }`; `public float sGy { get; }`; `public Vector3 sGz { get; }`; `public Vector3 OWy { get; set; }`; `public jU OWz { get; set; }`; `public jc OWh { get; set; }`; `public float OWB { get; set; }`; `public float sGh { get; }`; `public uint OWm { get; set; }`; `public float sGB { get; set; }`; `public vN sGm { get; set; }`; `public bool LocalFlight { get; set; }`; `public bool BodyAnimation { get; set; }`

<details><summary>methods (120)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x384C6DC | 0x2F51F8C |  | `public KinematicCharacterMotor get_Motor()` |
| 0x384C6E4 | 0x2F51F94 |  | `private void set_Motor(KinematicCharacterMotor value)` |
| - | 0x2F51F98 |  | `private float get_sGw()` |
| - | 0x2F51FB4 |  | `private XA get_sGJ()` |
| 0x384C724 | 0x2F51FD0 |  | `private bool get_sGX()` |
| 0x384C784 | 0x2F520D0 |  | `public float get_sGT()` |
| - | 0x2F520F4 |  | `public Vector3 get_InteractionFeet()` |
| - | 0x2F52194 |  | `public bool get_PhysicalCrouch()` |
| - | 0x2F521A4 |  | `public PlayerInput PhysicalInput(PlayerInput value)` |
| - | 0x2F521C0 |  | `public void ApplyServerPosture(bool crouch)` |
| - | 0x2F522B0 |  | `public float get_sGL()` |
| - | 0x2F522CC |  | `public float get_sGo()` |
| - | 0x2F522E8 |  | `public float get_sGy()` |
| - | 0x2F5230C |  | `public Vector3 get_sGz()` |
| - | 0x2F52318 |  | `public Vector3 get_OWy()` |
| - | 0x2F52328 |  | `private void set_OWy(Vector3 value)` |
| - | 0x2F52338 |  | `public jU get_OWz()` |
| - | 0x2F52340 |  | `private void set_OWz(jU value)` |
| - | 0x2F52348 |  | `public jc get_OWh()` |
| - | 0x2F52350 |  | `private void set_OWh(jc value)` |
| - | 0x2F52358 |  | `public float get_OWB()` |
| - | 0x2F52360 |  | `private void set_OWB(float value)` |
| 0x384C88C | 0x2F52368 |  | `public float get_sGh()` |
| - | 0x2F52370 |  | `public uint get_OWm()` |
| - | 0x2F52378 |  | `private void set_OWm(uint value)` |
| - | 0x2F52380 |  | `public float get_sGB()` |
| - | 0x2F52388 |  | `public void set_sGB(float value)` |
| 0x385151C | 0x2F52390 |  | `public vN get_sGm()` |
| 0x3851524 | 0x2F52398 |  | `public void set_sGm([In] vN value)` |
| 0x384C8B8 | 0x2F5239C | 13 | `public override void dHP()` |
| 0x384D024 | 0x2F52AF8 | 11 | `public override void Fsv()` |
| 0x384C8D4 | 0x2F523B8 |  | `private void dKA()` |
| 0x384D040 | 0x2F52B14 |  | `private void dKu()` |
| 0x384D174 | 0x2F52BF8 |  | `public void dKk(bool e)` |
| 0x384D2B0 | 0x2F52D58 |  | `public Vector3 dKO()` |
| 0x384D354 | 0x2F52E0C |  | `private void Update()` |
| - | 0x2F54550 |  | `public bool get_LocalFlight()` |
| - | 0x2F54558 |  | `public void set_LocalFlight(bool value)` |
| - | 0x2F53E0C |  | `private Move MountedAnimationMove()` |
| - | 0x2F54564 |  | `public void ApplyMountPose(Vector3 position, Quaternion rotation)` |
| - | 0x2F54688 |  | `public void ApplyServerPosition(Vector3 position, float yaw)` |
| - | 0x2F5474C |  | `public bool get_BodyAnimation()` |
| - | 0x2F54754 |  | `public void set_BodyAnimation(bool value)` |
| - | 0x2F5362C |  | `private void SmoothRemote(Move e)` |
| - | 0x2F53CC4 |  | `private void EnsureAnimation()` |
| 0x384D530 | 0x2F53F30 |  | `private void dKt(out int e)` |
| 0x384D608 | 0x2F54028 |  | `private void dKr()` |
| 0x384DC68 | 0x2F55640 |  | `private void dKN()` |
| 0x384E2E4 | 0x2F55D24 |  | `private void tGjVbFUyriGKNKgJ(Move e)` |
| 0x384E42C | 0x2F55F44 |  | `private void dKs(Move e)` |
| 0x384DE80 | 0x2F549F8 |  | `private void dKC(Move e)` |
| 0x384E560 | 0x2F560A4 |  | `private void dKZ(vN e, vN f)` |
| 0x384E174 | 0x2F55AE4 |  | `private void dKj()` |
| 0x384E27C | 0x2F55BEC |  | `private void dKa(float e)` |
| 0x384D998 | 0x2F53A98 |  | `private void dKQ()` |
| 0x384E638 | 0x2F560A8 | 31 | `public float dKH()` |
| 0x384E03C | 0x2F548DC |  | `private void dKi()` |
| 0x384C7C8 | 0x2F56108 |  | `private float dKw(jU e)` |
| 0x384E1E0 | 0x2F55B50 |  | `private void dKJ(float e, int f = 1)` |
| 0x384E694 | 0x2F56120 |  | `private void dKX(PlayerInput e)` |
| 0x384E8EC | 0x2F562FC |  | `private void dKT(float e)` |
| 0x384DD6C | 0x2F55818 |  | `private void dKL()` |
| 0x384F9F0 | 0x2F573D0 |  | `private void dKo()` |
| 0x384EDC4 | 0x2F567BC |  | `private void dKy(float e)` |
| 0x384F6D0 | 0x2F56DEC |  | `private void dKz(float e)` |
| 0x384FF0C | 0x2F57688 |  | `private bool dKh(int e)` |
| 0x384FD58 | 0x2F574D4 |  | `private float dKB(Vector3 e)` |
| 0x384FFC0 | 0x2F57738 |  | `private float dKm()` |
| 0x3850078 | 0x2F577F0 |  | `private void dKR(PlayerInput e)` |
| 0x384EB94 | 0x2F565DC |  | `private void dKb(float e)` |
| 0x384F3A8 | 0x2F570A4 |  | `private void dKl(float e)` |
| 0x384FC4C | 0x2F573D4 |  | `private void dKx()` |
| 0x384E8C4 | 0x2F577F4 |  | `public bool dKK()` |
| 0x38502D4 | 0x2F57818 |  | `private bool dKG()` |
| 0x38503A8 | 0x2F578E8 |  | `private bool dKP()` |
| 0x38503B0 | 0x2F578F0 |  | `private bool dKD()` |
| 0x385063C | 0x2F57C70 |  | `private bool dKn()` |
| 0x384D12C | 0x2F52268 |  | `private void dKV(float e)` |
| 0x3850644 | 0x2F57C78 |  | `private bool dKg()` |
| 0x38505BC | 0x2F57BF0 |  | `private bool dKp()` |
| 0x385068C | 0x2F57CC0 |  | `private void dKv()` |
| 0x3850738 | 0x2F57D68 |  | `private void dKS(Rigidbody e)` |
| 0x385073C | 0x2F57D6C |  | `private void OnTriggerEnter(Collider other)` |
| 0x3850850 | 0x2F57FEC |  | `private void OnTriggerExit(Collider other)` |
| - | 0x2F57EB0 |  | `private static bool IsLadder(Collider c)` |
| - | 0x2F552BC |  | `private void RefreshLadders()` |
| 0x384D218 | 0x2F52C9C |  | `private void dKI()` |
| 0x384DB30 | 0x2F54CAC |  | `private void CrXsusEdUXhgJNUk(PlayerInput e)` |
| 0x3850930 | 0x2F58168 |  | `private void dGe(uint e)` |
| 0x384E4F8 | 0x2F54760 |  | `private void dGf(bool e)` |
| 0x38505AC | 0x2F5816C |  | `public bool dGF()` |
| 0x384EAC8 | 0x2F564A4 |  | `private bool dGd(float e)` |
| 0x3850D4C | 0x2F5817C | 18 | `public void dGc(ref Quaternion e, float f)` |
| 0x3850DA8 | 0x2F581D8 | 19 | `public void dGU(ref Vector3 e, float f)` |
| 0x3850E18 | 0x2F5824C | 20 | `public void dGY(float e)` |
| 0x3850E1C | 0x2F58250 | 21 | `public void dGW(float e)` |
| 0x3850E4C | 0x2F58280 |  | `private void dGE()` |
| 0x3850E88 | 0x2F582BC |  | `private void dGA()` |
| 0x384DE30 | 0x2F582C0 |  | `private void dGu(float e)` |
| 0x3850E8C | 0x2F559B8 |  | `private float dGk()` |
| 0x3850F1C | 0x2F58310 | 22 | `public void dGO(float e)` |
| 0x3850F2C | 0x2F58320 | 23 | `public bool dGt(Collider e)` |
| 0x3850F34 | 0x2F58328 | 24 | `public void dGr(Collider e, Vector3 f, Vector3 F, ref HitStabilityReport d)` |
| 0x3850F38 | 0x2F5832C | 25 | `public void dGN(Collider e, Vector3 f, Vector3 F, ref HitStabilityReport d)` |
| 0x3850F3C | 0x2F58330 | 26 | `public void dGq(Collider e, Vector3 f, Vector3 F, Vector3 d, Quaternion c, ref HitStabilityReport U)` |
| 0x3850F40 | 0x2F58334 | 27 | `public void dGs(Collider e)` |
| 0x3851008 | 0x2F58338 | 28 | `public void dGC(List<Rigidbody> e)` |
| 0x385100C | 0x2F5833C | 29 | `public void dGZ(Collider[] e, int f)` |
| 0x3851010 | 0x2F58340 |  | `public static Vector3 dGj(Vector3 e, Vector3 f)` |
| 0x3851170 | 0x2F58350 |  | `private void OnDrawGizmosSelected()` |
| 0x38512E8 | 0x2F58354 |  | `public void .ctor()` |
| 0x38513FC | 0x2F58484 |  | `private void dGa()` |
| 0x3851454 | 0x2F584DC | 12 | `public override bool Fuk()` |
| 0x3851588 | 0x2F584E4 |  | `protected void dGJ(Move e)` |
| 0x3851794 | 0x2F584E8 |  | `protected static void dGX(vd e, vo f, vt F)` |
| 0x3851918 | 0x2F584EC |  | `protected void dGT(PlayerInput e)` |
| 0x385191C | 0x2F584F0 |  | `protected static void dGL(vd e, vo f, vt F)` |
| 0x3851A94 | 0x2F584F4 |  | `private static void .cctor()` |
| 0x3851C30 | 0x2F5860C | 5 | `protected override void FCk(vx e, bool f)` |
| 0x3851CBC | 0x2F58610 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public struct `Move`  
`TypeDefIndex 3597`

| offset | field |
|---|---|
| 0x0 | `public jc State;` |
| 0x4 | `public jU Pose;` |
| 0x8 | `public bool Aim;` |
| 0xC | `public Vector3 Position;` |
| 0x18 | `public Vector3 RealVelocity;` |
| 0x24 | `public Vector2 MoveDirection;` |
| 0x2C | `public float YRotation;` |
| 0x30 | `public float DeltaTime;` |
| 0x34 | `public uint Tick;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3870E84 | 0x2F5451C |  | `public void .ctor(jc state, jU pose, bool aim, Vector3 position, Vector3 realVelocity, Vector2 moveDirection, float yRotation, float deltaTime, uint tick)` |
| 0x3870EB8 | 0x2F52BD8 |  | `public void .ctor(Vector3 position, float yRotation, float deltaTime, uint tick)` |

</details>

### public class `PlayerEquipmentPiece` : ScriptableObject  
`TypeDefIndex 3598`

| offset | field |
|---|---|
| 0x18 | `public string id;` |
| 0x20 | `public AssetReference prefabRef;` |
| 0x28 | `public AssetReference defaultMaterialRef;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3873268 | 0x2F588C0 |  | `public void .ctor()` |

</details>

### public class `PlayerEquipmentResources` : ScriptableObject  
`TypeDefIndex 3599`

| offset | field |
|---|---|
| 0x18 | `public PlayerEquipmentPiece[] equipments;` |
| 0x20 | `public PlayerWeaponPiece[] weapons;` |
| 0x28 | `private AssetReference[] baseWeaponRefs;` |

Properties: `public AssetReference[] sGb { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F588C8 |  | `public AssetReference[] get_sGb()` |
| 0x3873278 | 0x2F588D0 |  | `public void .ctor()` |

</details>

### public class `PlayerLevelsConfig` : ScriptableObject  
`TypeDefIndex 3601`

| offset | field |
|---|---|
| - | `private const float ExpX = 0.075;` |
| - | `private const float ExpY = 1.75;` |
| 0x18 | `private bool overrideLevelExp;` |
| 0x20 | `private LevelData[] overrideLevels;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387622C | 0x2F588D8 |  | `public int dPd(int e)` |
| 0x3876378 | 0x2F588E0 |  | `private int dPc(int e)` |
| 0x387647C | 0x2F588E8 |  | `public void .ctor()` |

</details>

### public class `PlayerModelInfo` : MonoBehaviour, jj, jt  
`TypeDefIndex 3602`

| offset | field |
|---|---|
| 0x20 | `private Transform head;` |
| 0x28 | `private Transform rightWeaponHolder;` |
| 0x30 | `private Transform leftWeaponHolder;` |
| 0x38 | `private Transform equipmentHolder;` |
| 0x40 | `private Transform body;` |
| 0x48 | `private Transform headModel;` |
| 0x50 | `private SkinnedMeshRenderer skinnedMeshRenderer;` |
| 0x58 | `private CharacterAnimation characterAnimation;` |
| 0x60 | `private LODGroup[] lodGroups;` |

Properties: `public Transform sRU { get; }`; `public Transform sRY { get; }`; `public Transform sRW { get; }`; `public SkinnedMeshRenderer sGx { get; }`; `public Transform sGK { get; }`; `public Transform sGG { get; }`; `public Transform sGP { get; }`; `public Transform sGD { get; }`; `public CharacterAnimation sGn { get; }`; `public LODGroup[] sGV { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38764A8 | 0x2F58900 | 4 | `public Transform get_sRU()` |
| 0x38764B0 | 0x2F58908 | 5 | `public Transform get_sRY()` |
| 0x38764B8 | 0x2F58910 | 6 | `public Transform get_sRW()` |
| 0x38764C0 | 0x2F58918 | 8 | `public SkinnedMeshRenderer get_sGx()` |
| 0x38764C8 | 0x2F58920 |  | `public Transform get_sGK()` |
| 0x38764D0 | 0x2F58928 | 7 | `public Transform get_sGG()` |
| 0x38764D8 | 0x2F58930 |  | `public Transform get_sGP()` |
| 0x38764E0 | 0x2F58938 |  | `public Transform get_sGD()` |
| 0x38764E8 | 0x2F58940 |  | `public CharacterAnimation get_sGn()` |
| 0x38764F0 | 0x2F58948 |  | `public LODGroup[] get_sGV()` |
| 0x38764F8 | 0x2F58950 |  | `public void .ctor()` |

</details>

### public class `PlayerViewInstaller` : ScriptableObjectInstaller<PlayerViewInstaller>  
`TypeDefIndex 3603`

| offset | field |
|---|---|
| 0x20 | `private PlayerViewReferenceHolder playerViewReferenceHolder;` |

Properties: `public PlayerViewReferenceHolder Holder { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F58958 |  | `public PlayerViewReferenceHolder get_Holder()` |
| 0x3876C04 | 0x2F58960 | 6 | `public override void FSz()` |
| 0x3876D00 | 0x2F58964 |  | `public void .ctor()` |

</details>

### public class `PlayerViewReferenceHolder`  
`TypeDefIndex 3604`

| offset | field |
|---|---|
| 0x10 | `private PlayerModelInfo playerModelInfo;` |

Properties: `public PlayerModelInfo sGS { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3876D48 | 0x2F589AC |  | `public PlayerModelInfo get_sGS()` |
| 0x3876D50 | 0x2F589B4 |  | `public void .ctor()` |
| - | 0x2F589BC |  | `public void .ctor(PlayerModelInfo model)` |

</details>

### public class `PlayerWeaponPiece` : ScriptableObject  
`TypeDefIndex 3605`

| offset | field |
|---|---|
| 0x18 | `public string id;` |
| 0x20 | `public AssetReference rightHandPrefabRef;` |
| 0x28 | `public AssetReference leftHandPrefabRef;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3878678 | 0x2F589EC |  | `public void .ctor()` |

</details>

### public abstract class `SkinData` : ScriptableObject  
`TypeDefIndex 3606`

| offset | field |
|---|---|
| 0x18 | `public string Id;` |
| 0x20 | `public string baseId;` |
| - | `public Sprite directIcon;` |
| 0x28 | `public AssetReference iconRef;` |

Properties: `public Sprite sPe { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387A350 | 0x2F48588 |  | `public Sprite get_sPe()` |
| - | - |  | `public abstract QT dxJ(QT e, int f = 0);` |
| 0x387A3C0 | 0x2F5181C |  | `protected void .ctor()` |

</details>

### public class `WeaponObjectSkinData` : WeaponSkinData  
`TypeDefIndex 3608`

| offset | field |
|---|---|
| 0x30 | `public AssetReference rightHandPrefabRef;` |
| 0x38 | `public AssetReference leftHandPrefabRef;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387A3C8 | 0x2F589F4 | 5 | `public override QT dPK(PlayerWeaponPiece e, jj f)` |
| 0x387A8AC | 0x2F58EE8 | 4 | `public override QT dxJ(QT e, int f = 0)` |
| 0x387AC58 | 0x2F59294 | 6 | `public override QT dPG(PlayerWeaponPiece e)` |
| 0x387B018 | 0x2F59668 |  | `public void .ctor()` |

</details>

### public class `WeaponRecolorSkinData` : WeaponSkinData  
`TypeDefIndex 3610`

| offset | field |
|---|---|
| 0x30 | `public AssetReference materialRef;` |
| - | `public CosmicPropVariant propVariant;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387B0F4 | 0x2F597A0 | 5 | `public override QT dPK(PlayerWeaponPiece e, jj f)` |
| 0x387BB3C | 0x2F5A248 | 4 | `public override QT dxJ(QT e, int f = 0)` |
| 0x387C018 | 0x2F5A76C | 6 | `public override QT dPG(PlayerWeaponPiece e)` |
| 0x387C838 | 0x2F5B010 |  | `public void .ctor()` |

</details>

### public abstract class `WeaponSkinData` : SkinData  
`TypeDefIndex 3612`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387B654 | 0x2F59D50 | 5 | `public virtual QT dPK(PlayerWeaponPiece e, jj f)` |
| 0x387C4A8 | 0x2F5AC48 | 6 | `public virtual QT dPG(PlayerWeaponPiece e)` |
| 0x387B020 | 0x2F59670 |  | `protected void .ctor()` |

</details>
