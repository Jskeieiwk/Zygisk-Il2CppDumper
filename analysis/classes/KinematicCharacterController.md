# namespace `KinematicCharacterController`  (11 types)

### public struct `CharacterGroundingReport`  
`TypeDefIndex 3259`

| offset | field |
|---|---|
| 0x0 | `public bool FoundAnyGround;` |
| 0x1 | `public bool IsStableOnGround;` |
| 0x2 | `public bool SnappingPrevented;` |
| 0x4 | `public Vector3 GroundNormal;` |
| 0x10 | `public Vector3 InnerGroundNormal;` |
| 0x1C | `public Vector3 OuterGroundNormal;` |
| 0x28 | `public Collider GroundCollider;` |
| 0x30 | `public Vector3 GroundPoint;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BDF560 | 0x2ED1820 |  | `public void UzI(CharacterTransientGroundingReport e)` |

</details>

### public struct `CharacterTransientGroundingReport`  
`TypeDefIndex 3260`

| offset | field |
|---|---|
| 0x0 | `public bool FoundAnyGround;` |
| 0x1 | `public bool IsStableOnGround;` |
| 0x2 | `public bool SnappingPrevented;` |
| 0x4 | `public Vector3 GroundNormal;` |
| 0x10 | `public Vector3 InnerGroundNormal;` |
| 0x1C | `public Vector3 OuterGroundNormal;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BDF650 | 0x2ED1910 |  | `public void UzM(CharacterGroundingReport e)` |

</details>

### public struct `HitStabilityReport`  
`TypeDefIndex 3261`

| offset | field |
|---|---|
| 0x0 | `public bool IsStable;` |
| 0x1 | `public bool FoundInnerNormal;` |
| 0x4 | `public Vector3 InnerNormal;` |
| 0x10 | `public bool FoundOuterNormal;` |
| 0x14 | `public Vector3 OuterNormal;` |
| 0x20 | `public bool ValidStepDetected;` |
| 0x28 | `public Collider SteppedCollider;` |
| 0x30 | `public bool LedgeDetected;` |
| 0x31 | `public bool IsOnEmptySideOfLedge;` |
| 0x34 | `public float DistanceFromLedge;` |
| 0x38 | `public bool IsMovingTowardsEmptySideOfLedge;` |
| 0x3C | `public Vector3 LedgeGroundNormal;` |
| 0x48 | `public Vector3 LedgeRightDirection;` |
| 0x54 | `public Vector3 LedgeFacingDirection;` |

### public class `KCCSettings` : ScriptableObject  
`TypeDefIndex 3262`

| offset | field |
|---|---|
| 0x18 | `public bool AutoSimulation;` |
| 0x19 | `public bool Interpolate;` |
| 0x1C | `public int MotorsListInitialCapacity;` |
| 0x20 | `public int MoversListInitialCapacity;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BDF538 | 0x2ED19A8 |  | `public void .ctor()` |

</details>

### public class `KinematicCharacterMotor` : MonoBehaviour  
`TypeDefIndex 3263`

| offset | field |
|---|---|
| 0x20 | `private bool autoSimulation;` |
| 0x28 | `public CapsuleCollider Capsule;` |
| 0x30 | `private float CapsuleRadius;` |
| 0x34 | `private float CapsuleHeight;` |
| 0x38 | `private float CapsuleYOffset;` |
| 0x40 | `private PhysicMaterial CapsulePhysicsMaterial;` |
| 0x48 | `public float GroundDetectionExtraDistance;` |
| 0x4C | `public float MaxStableSlopeAngle;` |
| 0x50 | `public LayerMask StableGroundLayers;` |
| 0x54 | `public bool DiscreteCollisionEvents;` |
| 0x58 | `public bm StepHandling;` |
| 0x5C | `public float MaxStepHeight;` |
| 0x60 | `public bool AllowSteppingWithoutStableGrounding;` |
| 0x64 | `public float MinRequiredStepDepth;` |
| 0x68 | `public bool LedgeAndDenivelationHandling;` |
| 0x6C | `public float MaxStableDistanceFromLedge;` |
| 0x70 | `public float MaxVelocityForLedgeSnap;` |
| 0x74 | `public float MaxStableDenivelationAngle;` |
| 0x78 | `public bool InteractiveRigidbodyHandling;` |
| 0x7C | `public bB RigidbodyInteractionType;` |
| 0x80 | `public float SimulatedCharacterMass;` |
| 0x84 | `public bool PreserveAttachedRigidbodyMomentum;` |
| 0x85 | `public bool HasPlanarConstraint;` |
| 0x88 | `public Vector3 PlanarConstraintAxis;` |
| 0x94 | `public int MaxMovementIterations;` |
| 0x98 | `public int SimulationSubsteps;` |
| 0x9C | `public int MaxDecollisionIterations;` |
| 0xA0 | `public float MaxDecollisionStep;` |
| 0xA4 | `public bool CheckMovementInitialOverlaps;` |
| 0xA5 | `public bool KillVelocityWhenExceedMaxMovementIterations;` |
| 0xA6 | `public bool KillRemainingMovementWhenExceedMaxMovementIterations;` |
| 0xA8 | `public CharacterGroundingReport GroundingStatus;` |
| 0xE8 | `public CharacterTransientGroundingReport LastGroundingStatus;` |
| 0x110 | `public LayerMask CollidableLayers;` |
| 0x118 | `private Transform tji;` |
| 0x120 | `private Vector3 tjw;` |
| 0x12C | `private Vector3 tjJ;` |
| 0x138 | `private Vector3 tjX;` |
| 0x144 | `private Vector3 tjT;` |
| 0x150 | `private Vector3 tjL;` |
| 0x15C | `private Quaternion tjo;` |
| 0x170 | `private Rigidbody tjy;` |
| 0x178 | `private Vector3 tjz;` |
| 0x184 | `private Vector3 tjh;` |
| 0x190 | `private Vector3 tjB;` |
| 0x19C | `private Vector3 tjm;` |
| 0x1A8 | `private Vector3 tjR;` |
| 0x1B4 | `private Vector3 tjb;` |
| 0x1C0 | `private int tjl;` |
| 0x1C8 | `private OverlapResult[] tjx;` |
| 0x1D0 | `public bz CharacterController;` |
| 0x1D8 | `public bool LastMovementIterationFoundAnyGround;` |
| 0x1DC | `public int IndexInCharacterSystem;` |
| 0x1E0 | `public Vector3 InitialTickPosition;` |
| 0x1EC | `public Vector3 LastInterpolatedPosition;` |
| 0x1F8 | `public Quaternion InitialTickRotation;` |
| 0x208 | `public Rigidbody AttachedRigidbodyOverride;` |
| 0x210 | `public Vector3 BaseVelocity;` |
| 0x220 | `private RaycastHit[] tjK;` |
| 0x228 | `private Collider[] tjG;` |
| 0x230 | `private List<Rigidbody> tjP;` |
| 0x238 | `private RigidbodyProjectionHit[] tjD;` |
| 0x240 | `private Rigidbody tjn;` |
| 0x248 | `private bool tjV;` |
| 0x249 | `private bool tjg;` |
| 0x24A | `private bool tjp;` |
| 0x24C | `private Vector3 tjv;` |
| 0x258 | `private bool tjS;` |
| 0x25C | `private Quaternion tjI;` |
| 0x26C | `private bool tjM;` |
| 0x270 | `private Vector3 tae;` |
| 0x27C | `private int taf;` |
| 0x280 | `private bool taF;` |
| 0x281 | `private bool tad;` |
| 0x284 | `private float tac;` |
| 0x288 | `private Vector3 taU;` |
| 0x294 | `private Vector3 taY;` |
| 0x2A0 | `private Vector3 taW;` |
| 0x2AC | `private Vector3 taE;` |
| 0x2B8 | `private Quaternion taA;` |
| - | `public const int MaxHitsBudget = 16;` |
| - | `public const int MaxCollisionBudget = 16;` |
| - | `public const int MaxGroundingSweepIterations = 2;` |
| - | `public const int MaxSteppingSweepIterations = 3;` |
| - | `public const int MaxRigidbodyOverlapsCount = 16;` |
| - | `public const float CollisionOffset = 0.01;` |
| - | `public const float GroundProbeReboundDistance = 0.02;` |
| - | `public const float MinimumGroundProbingDistance = 0.005;` |
| - | `public const float GroundProbingBackstepDistance = 0.1;` |
| - | `public const float SweepProbingBackstepDistance = 0.002;` |
| - | `public const float SecondaryProbesVertical = 0.02;` |
| - | `public const float SecondaryProbesHorizontal = 0.001;` |
| - | `public const float MinVelocityMagnitude = 0.01;` |
| - | `public const float SteppingForwardDistance = 0.03;` |
| - | `public const float MinDistanceForLedge = 0.05;` |
| - | `public const float CorrelationForVerticalObstruction = 0.01;` |
| - | `public const float ExtraSteppingForwardDistance = 0.01;` |
| - | `public const float ExtraStepHeightPadding = 0.01;` |

Properties: `public Transform CdD { get; }`; `public Vector3 CdV { get; }`; `public Vector3 Cdg { get; }`; `public Vector3 Cdp { get; }`; `public Vector3 Cdv { get; }`; `public Vector3 CdS { get; }`; `public Quaternion CdI { get; }`; `public Rigidbody CdM { get; }`; `public Vector3 Cce { get; }`; `public Vector3 Ccf { get; }`; `public Vector3 CcF { get; }`; `public Vector3 Ccd { get; }`; `public Vector3 Ccc { get; }`; `public Vector3 CcU { get; }`; `public int CcY { get; }`; `public OverlapResult[] CcW { get; }`; `public Quaternion CcE { get; set; }`; `public Vector3 CcA { get; }`

<details><summary>methods (73)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BDF6E8 | 0x2ED19B0 |  | `public Transform get_CdD()` |
| 0x3BDF6F0 | 0x2ED19B8 |  | `public Vector3 get_CdV()` |
| 0x3BDF700 | 0x2ED19C8 |  | `public Vector3 get_Cdg()` |
| 0x3BDF710 | 0x2ED19D8 |  | `public Vector3 get_Cdp()` |
| 0x3BDF720 | 0x2ED19E8 |  | `public Vector3 get_Cdv()` |
| 0x3BDF730 | 0x2ED19F8 |  | `public Vector3 get_CdS()` |
| 0x3BDF740 | 0x2ED1A08 |  | `public Quaternion get_CdI()` |
| 0x3BDF754 | 0x2ED1A1C |  | `public Rigidbody get_CdM()` |
| 0x3BDF75C | 0x2ED1A24 |  | `public Vector3 get_Cce()` |
| 0x3BDF76C | 0x2ED1A34 |  | `public Vector3 get_Ccf()` |
| 0x3BDF77C | 0x2ED1A44 |  | `public Vector3 get_CcF()` |
| 0x3BDF78C | 0x2ED1A54 |  | `public Vector3 get_Ccd()` |
| 0x3BDF79C | 0x2ED1A64 |  | `public Vector3 get_Ccc()` |
| 0x3BDF7AC | 0x2ED1A74 |  | `public Vector3 get_CcU()` |
| 0x3BDF7BC | 0x2ED1A84 |  | `public int get_CcY()` |
| 0x3BDF7C4 | 0x2ED1A8C |  | `public OverlapResult[] get_CcW()` |
| - | 0x2ED1A94 |  | `public Quaternion get_CcE()` |
| - | 0x2ED1AA8 |  | `private void set_CcE(Quaternion value)` |
| 0x3BDF898 | 0x2ED1B68 |  | `public Vector3 get_CcA()` |
| 0x3BDF8BC | 0x2ED1B8C |  | `private void OnEnable()` |
| 0x3BDF930 | 0x2ED1B90 |  | `private void OnDisable()` |
| 0x3BDF99C | 0x2ED1B94 |  | `private void Reset()` |
| 0x3BDFAF8 | 0x2ED1B98 |  | `private void OnValidate()` |
| 0x3BDFAFC | 0x2ED1B9C |  | `private void UhZ()` |
| 0x3BDF9A0 | 0x2ED1BA0 |  | `public void Uhj()` |
| 0x3BDFE20 | 0x2ED1EB4 |  | `public void Uha(bool e)` |
| 0x3BDFE44 | 0x2ED1ED8 |  | `public void UhQ(bool e)` |
| 0x3BDFE50 | 0x2ED1EE4 |  | `public void UhH(bool e)` |
| 0x3BDFE5C | 0x2ED1EF0 |  | `public void Uhi(Vector3 e, bool f = true)` |
| 0x3BDFEDC | 0x2ED1F70 |  | `public void Uhw(Quaternion e, bool f = true)` |
| 0x3BDFF68 | 0x2ED1FFC |  | `public void UhJ(Vector3 e, Quaternion f, bool F = true)` |
| 0x3BE0040 | 0x2ED20D4 |  | `public void UhX(Vector3 e)` |
| 0x3BE0058 | 0x2ED20EC |  | `public void UhT(Quaternion e)` |
| 0x3BE0074 | 0x2ED2108 |  | `public KinematicCharacterMotorState UhL()` |
| 0x3BE0210 | 0x2ED2304 |  | `public void Uho(KinematicCharacterMotorState e, bool f = true)` |
| 0x3BDFB98 | 0x2ED1CF8 |  | `public void Uhy(float e, float f, float F)` |
| 0x3BE02FC | 0x2ED23F0 |  | `private void Awake()` |
| 0x3BE0378 | 0x2ED246C |  | `public void Uhz()` |
| 0x3BE044C | 0x2ED2540 |  | `public void Uhh(float e)` |
| 0x3BE3D38 | 0x2ED5D1C |  | `public void UhB(float e)` |
| 0x3BE2F3C | 0x2ED4EF0 |  | `private bool Uhm(Vector3 e)` |
| 0x3BE4E8C | 0x2ED6E00 |  | `private bool UhR(ref HitStabilityReport e, Vector3 f)` |
| 0x3BE32D0 | 0x2ED5284 |  | `public void Uhb(ref Vector3 e, Quaternion f, float F, ref CharacterGroundingReport d)` |
| 0x3BE5C58 | 0x2ED7BEC |  | `public void Uhl(float e = 0.1)` |
| 0x3BE32B0 | 0x2ED5264 |  | `public bool Uhx()` |
| 0x3BE3954 | 0x2ED5914 |  | `public Vector3 UhK(Vector3 e, Vector3 f)` |
| 0x3BE1568 | 0x2ED3544 |  | `private bool UhG(ref Vector3 e, float f)` |
| 0x3BE3068 | 0x2ED501C |  | `private Vector3 UhP(Vector3 e, bool f)` |
| 0x3BE4CC8 | 0x2ED6C38 |  | `private void UhD(Rigidbody e, Vector3 f, Vector3 F, Vector3 d, HitStabilityReport c)` |
| 0x3BE663C | 0x2ED85A4 |  | `public void Uhn(Vector3 e)` |
| 0x3BE5C68 | 0x2ED7BFC |  | `private void UhV(bool e, Vector3 f, Vector3 F, Vector3 d, ref bR c, bool U, Vector3 Y, Vector3 W, ref Vector3 E, ref float A, ref Vector3 u)` |
| 0x3BE664C | 0x2ED85B4 |  | `private void Uhg(Vector3 e, Vector3 f, Vector3 F, Vector3 d, bool c, bool U, bool Y, out bool W, out Vector3 E)` |
| 0x3BE6C8C | 0x2ED8BE8 | 4 | `public virtual void Uhp(ref Vector3 e, Vector3 f, bool F)` |
| 0x3BE71CC | 0x2ED9128 | 5 | `public virtual void Uhv(ref Vector3 e, RigidbodyProjectionHit f, float F)` |
| 0x3BE2690 | 0x2ED4670 |  | `private void UhS(ref Vector3 e, float f)` |
| 0x3BE71D0 | 0x2ED912C |  | `public void UhI(Vector3 e, Vector3 f, Vector3 F, float d, out Vector3 c, out Vector3 U)` |
| 0x3BE72B8 | 0x2ED92A0 |  | `private bool UhM(Collider e)` |
| 0x3BE7348 | 0x2ED9330 |  | `private bool UBe(Collider e)` |
| 0x3BE5218 | 0x2ED7190 |  | `public void UBf(Collider e, Vector3 f, Vector3 F, Vector3 d, Quaternion c, Vector3 U, ref HitStabilityReport Y)` |
| 0x3BE7724 | 0x2ED96F0 |  | `private void UBF(Vector3 e, Quaternion f, Vector3 F, Vector3 d, ref HitStabilityReport c)` |
| 0x3BE7C58 | 0x2ED9C38 |  | `private bool UBd(int e, Vector3 f, Quaternion F, Vector3 d, Vector3 c, out Collider U)` |
| 0x3BE3A7C | 0x2ED5A3C |  | `public void UBc(Rigidbody e, Vector3 f, float F, out Vector3 d, out Vector3 c)` |
| 0x3BE2E50 | 0x2ED4DF8 |  | `private Rigidbody UBU(Collider e)` |
| 0x3BE81F0 | 0x2EDA1C8 |  | `public Vector3 UBY(Vector3 e, Vector3 f, float F)` |
| 0x3BE150C | 0x2ED34E8 |  | `public Vector3 UBW(Vector3 e, float f)` |
| 0x3BE8204 | 0x2EDA1DC |  | `private void UBE(ref Vector3 e, Vector3 f)` |
| 0x3BE2B10 | 0x2ED4AE8 |  | `public int UBA(Vector3 e, Quaternion f, Collider[] F, float d = 0, bool c = false)` |
| 0x3BE8268 | 0x2EDA2B0 |  | `public int UBu(Vector3 e, Quaternion f, Collider[] F, LayerMask d, QueryTriggerInteraction c, float U = 0)` |
| 0x3BE61CC | 0x2ED816C |  | `public int UBk(Vector3 e, Quaternion f, Vector3 F, float d, out RaycastHit c, RaycastHit[] U, float Y = 0, bool W = false)` |
| 0x3BE85BC | 0x2EDA5EC |  | `public int UBO(Vector3 e, Quaternion f, Vector3 F, float d, out RaycastHit c, RaycastHit[] U, LayerMask Y, QueryTriggerInteraction W, float E = 0)` |
| 0x3BE49F4 | 0x2ED691C |  | `private bool UBt(Vector3 e, Quaternion f, Vector3 F, float d, out RaycastHit c)` |
| 0x3BE7504 | 0x2ED94B8 |  | `public int UBr(Vector3 e, Vector3 f, float F, out RaycastHit d, RaycastHit[] c, bool U = false)` |
| 0x3BE899C | 0x2EDA9FC |  | `public void .ctor()` |

</details>

### public struct `KinematicCharacterMotorState`  
`TypeDefIndex 3264`

| offset | field |
|---|---|
| 0x0 | `public Vector3 Position;` |
| 0xC | `public Quaternion Rotation;` |
| 0x1C | `public Vector3 BaseVelocity;` |
| 0x28 | `public bool MustUnground;` |
| 0x2C | `public float MustUngroundTime;` |
| 0x30 | `public bool LastMovementIterationFoundAnyGround;` |
| 0x34 | `public CharacterTransientGroundingReport GroundingStatus;` |
| 0x60 | `public Rigidbody AttachedRigidbody;` |
| 0x68 | `public Vector3 AttachedRigidbodyVelocity;` |

### public class `KinematicCharacterSystem` : MonoBehaviour  
`TypeDefIndex 3265`

| offset | field |
|---|---|
| 0x0 | `private static KinematicCharacterSystem tak;` |
| 0x8 | `public static List<KinematicCharacterMotor> CharacterMotors;` |
| 0x10 | `public static List<bl> PhysicsMovers;` |
| 0x18 | `private static float taO;` |
| 0x1C | `private static float tat;` |
| 0x20 | `public static KCCSettings Settings;` |

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BE8D60 | 0x2EDAD90 |  | `public static void UBN()` |
| 0x3BE8F40 | 0x2EDAD94 |  | `public static KinematicCharacterSystem UBq()` |
| 0x3BE8F98 | 0x2EDAD9C |  | `public static void UBs(int e)` |
| 0x3BE906C | 0x2EDADA0 |  | `public static void UBC(KinematicCharacterMotor e)` |
| 0x3BE9140 | 0x2EDADA4 |  | `public static void UBZ(KinematicCharacterMotor e)` |
| 0x3BE91C0 | 0x2EDADA8 |  | `public static void UBj(int e)` |
| 0x3BE9294 | 0x2EDADAC |  | `public static void UBa(bl e)` |
| 0x3BE937C | 0x2EDADB0 |  | `public static void UBQ(bl e)` |
| 0x3BE93FC | 0x2EDADB4 |  | `private void OnDisable()` |
| 0x3BE9468 | 0x2EDADB8 |  | `private void Awake()` |
| 0x3BE94D0 | 0x2EDADBC |  | `private void RecoveredNoopFixedUpdate()` |
| 0x3BE9C3C | 0x2EDADC0 |  | `private void RecoveredNoopLateUpdate()` |
| 0x3BE95E0 | 0x2EDADC4 |  | `public static void UBH(float e)` |
| 0x3BE97E8 | 0x2EDADC8 |  | `public static void UBi(float e, List<KinematicCharacterMotor> f, List<bl> F)` |
| 0x3BE99E4 | 0x2EDADCC |  | `public static void UBw(float e)` |
| 0x3BE9CBC | 0x2EDADD0 |  | `private static void UBJ()` |
| 0x3BEA2C0 | 0x2EDADD4 |  | `public void .ctor()` |

</details>

### public struct `OverlapResult`  
`TypeDefIndex 3266`

| offset | field |
|---|---|
| 0x0 | `public Vector3 Normal;` |
| 0x10 | `public Collider Collider;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BDF550 | 0x2EDADDC |  | `public void .ctor(Vector3 normal, Collider collider)` |

</details>

### public struct `PhysicsMoverState`  
`TypeDefIndex 3267`

| offset | field |
|---|---|
| 0x0 | `public Vector3 Position;` |
| 0xC | `public Quaternion Rotation;` |
| 0x1C | `public Vector3 Velocity;` |
| 0x28 | `public Vector3 AngularVelocity;` |

### public class `ReadOnlyAttribute` : PropertyAttribute  
`TypeDefIndex 3268`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BEBED8 | 0x2EDADEC |  | `public void .ctor()` |

</details>

### public struct `RigidbodyProjectionHit`  
`TypeDefIndex 3269`

| offset | field |
|---|---|
| 0x0 | `public Rigidbody Rigidbody;` |
| 0x8 | `public Vector3 HitPoint;` |
| 0x14 | `public Vector3 EffectiveHitNormal;` |
| 0x20 | `public Vector3 HitVelocity;` |
| 0x2C | `public bool StableOnHit;` |
