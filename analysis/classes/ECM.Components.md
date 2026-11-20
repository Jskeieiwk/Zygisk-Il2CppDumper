# namespace `ECM.Components`  (8 types)

### public abstract class `BaseGroundDetection` : MonoBehaviour  
`TypeDefIndex 3952`

| offset | field |
|---|---|
| 0x20 | `private LayerMask _groundMask;` |
| 0x24 | `private float _groundLimit;` |
| 0x28 | `The character will step up a stair only if it is closer to the ground than the indicated value.` |
| - | `As rule of thumb, configure it to your character's collider radius.")]` |
| - | `private float _stepOffset;` |
| 0x2C | `private float _ledgeOffset;` |
| 0x30 | `As rule of thumb, configure it to your character's collider radius.")]` |
| - | `private float _castDistance;` |
| 0x34 | `private QueryTriggerInteraction _triggerInteraction;` |
| 0x0 | `private static readonly Collider[] kyL;` |
| - | `protected const float kyo = 0.05;` |
| - | `protected const float kyy = 0.01;` |
| - | `protected const float kyz = 0.05;` |
| - | `protected const float kyh = 0.1;` |
| - | `protected const float kyB = 0.001;` |
| 0x38 | `private CapsuleCollider kym;` |
| 0x40 | `protected GroundHit kyR;` |
| 0x90 | `private LayerMask kyb;` |
| 0x94 | `private int kyl;` |
| 0x98 | `private int kyx;` |

Properties: `public LayerMask sha { get; set; }`; `public float shQ { get; set; }`; `public float shH { get; set; }`; `public float shi { get; set; }`; `public float shw { get; set; }`; `public QueryTriggerInteraction shJ { get; set; }`; `public CapsuleCollider shX { get; }`; `public bool shT { get; }`; `public bool shL { get; }`; `public bool sho { get; }`; `public bool shy { get; }`; `public float shz { get; }`; `public bool shh { get; }`; `public float shB { get; }`; `public bool shm { get; }`; `public Vector3 shR { get; }`; `public Vector3 shb { get; }`; `public float shl { get; }`; `public Collider shx { get; }`; `public Rigidbody shK { get; }`; `public float shG { get; }`; `public Vector3 shP { get; }`; `public GroundHit shD { get; }`; `public GroundHit kyK { get; set; }`; `public LayerMask shn { get; set; }`

<details><summary>methods (50)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3705F58 | 0x2F7FB4C |  | `public LayerMask get_sha()` |
| 0x3705F60 | 0x2F7FB54 |  | `public void set_sha(LayerMask value)` |
| 0x3705F68 | 0x2F7FB58 |  | `public float get_shQ()` |
| 0x3705F70 | 0x2F7FB60 |  | `public void set_shQ(float value)` |
| 0x3705F90 | 0x2F7FB64 |  | `public float get_shH()` |
| 0x3705F98 | 0x2F7FB6C |  | `public void set_shH(float value)` |
| 0x3705FE4 | 0x2F7FB70 |  | `public float get_shi()` |
| 0x3705FEC | 0x2F7FB78 |  | `public void set_shi(float value)` |
| 0x3706034 | 0x2F7FB7C |  | `public float get_shw()` |
| 0x37028A0 | 0x2F7FB84 |  | `public void set_shw(float value)` |
| 0x370603C | 0x2F7FB88 |  | `public QueryTriggerInteraction get_shJ()` |
| 0x3706044 | 0x2F7FB90 |  | `public void set_shJ(QueryTriggerInteraction value)` |
| 0x3701524 | 0x2F7FB94 |  | `public CapsuleCollider get_shX()` |
| 0x37016AC | 0x2F7FB9C |  | `public bool get_shT()` |
| 0x37016B4 | 0x2F7FBA4 |  | `public bool get_shL()` |
| 0x3701748 | 0x2F7FBAC |  | `public bool get_sho()` |
| 0x370176C | 0x2F7FBB4 |  | `public bool get_shy()` |
| 0x3701790 | 0x2F7FBBC |  | `public float get_shz()` |
| 0x37017B4 | 0x2F7FBC4 |  | `public bool get_shh()` |
| 0x37017D8 | 0x2F7FBCC |  | `public float get_shB()` |
| 0x37017F8 | 0x2F7FBD4 |  | `public bool get_shm()` |
| 0x37015FC | 0x2F7FBDC |  | `public Vector3 get_shR()` |
| 0x3701628 | 0x2F7FBEC |  | `public Vector3 get_shb()` |
| 0x370165C | 0x2F7FBFC |  | `public float get_shl()` |
| 0x3701680 | 0x2F7FC04 |  | `public Collider get_shx()` |
| 0x37016A4 | 0x2F7FC0C |  | `public Rigidbody get_shK()` |
| 0x370187C | 0x2F7FC14 |  | `public float get_shG()` |
| 0x3701634 | 0x2F7FC1C |  | `public Vector3 get_shP()` |
| 0x370604C | 0x2F7FC2C |  | `public GroundHit get_shD()` |
| 0x370605C | 0x2F7FC38 |  | `public GroundHit get_kyK()` |
| 0x370606C | 0x2F7FC44 |  | `private void set_kyK(GroundHit value)` |
| 0x3706090 | 0x2F7FC48 |  | `public LayerMask get_shn()` |
| 0x3706098 | 0x2F7FC50 |  | `public void set_shn(LayerMask value)` |
| 0x37060A0 | 0x2F7FC54 | 4 | `protected virtual void FnI()` |
| 0x37020E0 | 0x2F7FC58 |  | `public Collider[] FnM(Vector3 e, Quaternion f, out int F)` |
| 0x3706170 | 0x2F7FC64 |  | `protected bool FVe(Vector3 e, Vector3 f, out RaycastHit F, float d, float c = 0.05)` |
| 0x3706294 | 0x2F7FC78 |  | `protected bool FVf(Vector3 e, float f, Vector3 F, out RaycastHit d, float c, float U = 0.05)` |
| 0x37063C0 | 0x2F7FC8C |  | `protected bool FVF(Vector3 e, Vector3 f, float F, Vector3 d, out RaycastHit c, float U, float Y = 0.05)` |
| 0x3706538 | 0x2F7FCA0 | 5 | `public virtual bool FVd(Vector3 e, Quaternion f, Vector3 F, out RaycastHit d, float c = inf, float U = 0.05)` |
| 0x3706784 | 0x2F7FCB4 | 6 | `protected virtual void FVc()` |
| 0x37067C8 | 0x2F7FCB8 | 7 | `protected virtual void FVU()` |
| 0x37067F0 | 0x2F7FCBC | 8 | `public virtual void FVY()` |
| - | - |  | `public abstract bool FPj(Vector3 e, Quaternion f, ref GroundHit F, float d = inf);` |
| 0x3702D08 | 0x2F7FCC0 |  | `public void FVW()` |
| - | - |  | `public abstract bool FPa(Vector3 e, out RaycastHit f, float F = inf, float d = 0.05);` |
| 0x37069C0 | 0x2F7FCC4 | 11 | `protected virtual void FVE()` |
| 0x37069C4 | 0x2F7FCC8 | 12 | `protected virtual void OnValidate()` |
| 0x3706A18 | 0x2F7FCCC | 13 | `protected virtual void Awake()` |
| 0x3706A8C | 0x2F7FCD0 |  | `public void OnDrawGizmosSelected()` |
| 0x3701258 | 0x2F7FCD4 |  | `protected void .ctor()` |

</details>

### public sealed class `BoxGroundDetection` : BaseGroundDetection  
`TypeDefIndex 3953`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3701194 | 0x2F7FCDC | 9 | `public override bool FPj(Vector3 e, Quaternion f, ref GroundHit F, float d = inf)` |
| 0x37011CC | 0x2F7FCE4 | 10 | `public override bool FPa(Vector3 e, out RaycastHit f, float F = inf, float d = 0.05)` |
| 0x3701204 | 0x2F7FCF8 |  | `public void .ctor()` |

</details>

### public sealed class `CharacterMovement` : MonoBehaviour  
`TypeDefIndex 3955`

| offset | field |
|---|---|
| 0x20 | `private float _maxLateralSpeed;` |
| 0x24 | `private float _maxRiseSpeed;` |
| 0x28 | `private float _maxFallSpeed;` |
| 0x2C | `private bool _useGravity;` |
| 0x30 | `private Vector3 _gravity;` |
| 0x3C | `private bool _slideOnSteepSlope;` |
| 0x40 | `private float _slopeLimit;` |
| 0x44 | `private float _slideGravityMultiplier;` |
| 0x48 | `private bool _snapToGround;` |
| 0x4C | `0 == no snap at all, 1 == 100% stick to ground.")]` |
| - | `private float _snapStrength;` |
| 0x0 | `private static readonly Collider[] kyt;` |
| 0x50 | `private Coroutine kyr;` |
| 0x58 | `private Vector3 kyN;` |
| 0x64 | `private float kyq;` |
| 0x68 | `private bool kys;` |
| 0x6C | `private float kyC;` |
| 0x70 | `private bool kyZ;` |
| 0x74 | `private Vector3 kyj;` |
| 0x80 | `private Vector3 kya;` |

Properties: `public float szm { get; set; }`; `public float szR { get; set; }`; `public float szb { get; set; }`; `public bool szl { get; set; }`; `public Vector3 szx { get; set; }`; `public bool szK { get; set; }`; `public float szG { get; set; }`; `public float szP { get; set; }`; `public bool szD { get; set; }`; `public float szn { get; set; }`; `public CapsuleCollider szV { get; }`; `private BaseGroundDetection kyQ { get; set; }`; `public Vector3 szg { get; }`; `public Vector3 szp { get; }`; `public Vector3 szv { get; }`; `public float szS { get; }`; `public Collider szI { get; }`; `public Rigidbody szM { get; }`; `public bool she { get; }`; `public bool shf { get; }`; `public bool shF { get; }`; `public bool shd { get; }`; `public bool shc { get; }`; `public bool kyH { get; set; }`; `public bool shU { get; }`; `public bool shY { get; }`; `public float shW { get; }`; `public bool shE { get; }`; `public float shA { get; }`; `public bool shu { get; }`; `public float shk { get; }`; `public bool shO { get; }`; `public bool kyi { get; set; }`; `public Vector3 kyw { get; set; }`; `public Vector3 kyJ { get; set; }`; `public bool kyX { get; set; }`; `public Vector3 sht { get; set; }`; `public float shr { get; }`; `public Quaternion shN { get; set; }`; `public GroundHit shq { get; }`; `public GroundHit shs { get; }`; `public LayerMask shC { get; }`; `public LayerMask shZ { get; }`; `public QueryTriggerInteraction shj { get; }`; `public Rigidbody kyT { get; set; }`

<details><summary>methods (102)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3701434 | 0x2F7FD00 |  | `public float get_szm()` |
| 0x370143C | 0x2F7FD08 |  | `public void set_szm(float value)` |
| 0x370144C | 0x2F7FD0C |  | `public float get_szR()` |
| 0x3701454 | 0x2F7FD14 |  | `public void set_szR(float value)` |
| 0x3701464 | 0x2F7FD18 |  | `public float get_szb()` |
| 0x36FCA4C | 0x2F7FD20 |  | `public void set_szb(float value)` |
| 0x370146C | 0x2F7FD24 |  | `public bool get_szl()` |
| 0x3701474 | 0x2F7FD2C |  | `public void set_szl(bool value)` |
| 0x3701480 | 0x2F7FD30 |  | `public Vector3 get_szx()` |
| 0x370148C | 0x2F7FD40 |  | `public void set_szx(Vector3 value)` |
| 0x3701498 | 0x2F7FD44 |  | `public bool get_szK()` |
| 0x37014A0 | 0x2F7FD4C |  | `public void set_szK(bool value)` |
| 0x37014AC | 0x2F7FD50 |  | `public float get_szG()` |
| 0x37014B4 | 0x2F7FD58 |  | `public void set_szG(float value)` |
| 0x37014D4 | 0x2F7FD5C |  | `public float get_szP()` |
| 0x37014DC | 0x2F7FD64 |  | `public void set_szP(float value)` |
| 0x37014EC | 0x2F7FD68 |  | `public bool get_szD()` |
| 0x37014F4 | 0x2F7FD70 |  | `public void set_szD(bool value)` |
| 0x3701500 | 0x2F7FD74 |  | `public float get_szn()` |
| 0x3701508 | 0x2F7FD7C |  | `public void set_szn(float value)` |
| 0x36F9A30 | 0x2F7FD80 |  | `public CapsuleCollider get_szV()` |
| 0x37015CC | 0x2F7FD88 |  | `private BaseGroundDetection get_kyQ()` |
| 0x37015D4 | 0x2F7FD90 |  | `private void set_kyQ(BaseGroundDetection value)` |
| 0x37015DC | 0x2F7FD94 |  | `public Vector3 get_szg()` |
| 0x3701608 | 0x2F7FDA4 |  | `public Vector3 get_szp()` |
| 0x36F9A64 | 0x2F7FDB4 |  | `public Vector3 get_szv()` |
| 0x3701640 | 0x2F7FDC4 |  | `public float get_szS()` |
| 0x3701664 | 0x2F7FDCC |  | `public Collider get_szI()` |
| 0x3701688 | 0x2F7FDD4 |  | `public Rigidbody get_szM()` |
| 0x36F99FC | 0x2F7FDDC |  | `public bool get_she()` |
| 0x36FA5C4 | 0x2F7FDE4 |  | `public bool get_shf()` |
| 0x37016BC | 0x2F7FDEC |  | `public bool get_shF()` |
| 0x37016D8 | 0x2F7FDF4 |  | `public bool get_shd()` |
| 0x37016FC | 0x2F7FDFC |  | `public bool get_shc()` |
| 0x3701718 | 0x2F7FE04 |  | `public bool get_kyH()` |
| 0x3701720 | 0x2F7FE0C |  | `private void set_kyH(bool value)` |
| 0x370172C | 0x2F7FE10 |  | `public bool get_shU()` |
| 0x3701750 | 0x2F7FE18 |  | `public bool get_shY()` |
| 0x3701774 | 0x2F7FE20 |  | `public float get_shW()` |
| 0x3701798 | 0x2F7FE28 |  | `public bool get_shE()` |
| 0x37017BC | 0x2F7FE30 |  | `public float get_shA()` |
| 0x37017E0 | 0x2F7FE38 |  | `public bool get_shu()` |
| 0x3700774 | 0x2F7FE40 |  | `public float get_shk()` |
| 0x37019C4 | 0x2F7FE48 |  | `public bool get_shO()` |
| 0x3701A00 | 0x2F7FE50 |  | `public bool get_kyi()` |
| 0x3701A08 | 0x2F7FE58 |  | `private void set_kyi(bool value)` |
| 0x3701A14 | 0x2F7FE5C |  | `public Vector3 get_kyw()` |
| 0x3701A20 | 0x2F7FE6C |  | `private void set_kyw(Vector3 value)` |
| 0x3701A2C | 0x2F7FE70 |  | `public Vector3 get_kyJ()` |
| 0x3701A38 | 0x2F7FE80 |  | `private void set_kyJ(Vector3 value)` |
| 0x3701A44 | 0x2F7FE84 |  | `public bool get_kyX()` |
| 0x3701A4C | 0x2F7FE8C |  | `public void set_kyX(bool value)` |
| 0x36FB05C | 0x2F7FE90 |  | `public Vector3 get_sht()` |
| 0x36FCA5C | 0x2F7FEA0 |  | `public void set_sht(Vector3 value)` |
| 0x36FAFFC | 0x2F7FEA4 |  | `public float get_shr()` |
| 0x36F9A84 | 0x2F7FEAC |  | `public Quaternion get_shN()` |
| 0x36F9AA0 | 0x2F7FEC0 |  | `public void set_shN(Quaternion value)` |
| 0x3701A58 | 0x2F7FEC4 |  | `public GroundHit get_shq()` |
| 0x3701A80 | 0x2F7FED0 |  | `public GroundHit get_shs()` |
| 0x36F9A48 | 0x2F7FEDC |  | `public LayerMask get_shC()` |
| 0x3701AA8 | 0x2F7FEE4 |  | `public LayerMask get_shZ()` |
| 0x3701AC4 | 0x2F7FEEC |  | `public QueryTriggerInteraction get_shj()` |
| 0x3701AE0 | 0x2F7FEF4 |  | `public Rigidbody get_kyT()` |
| 0x3701AE8 | 0x2F7FEFC |  | `private void set_kyT(Rigidbody value)` |
| 0x36FDF90 | 0x2F7FF00 |  | `public void FDx(bool e, bool f = true)` |
| 0x3701AF0 | 0x2F7FF04 |  | `public void FDK(Vector3 e, float f, float F)` |
| 0x3701B94 | 0x2F7FF08 |  | `public void FDG(float e, float f)` |
| 0x36FE4D8 | 0x2F7FF0C |  | `public void FDP(float e)` |
| 0x3701C20 | 0x2F7FF10 |  | `private void FDD(Vector3 e, Vector3 f, float F, out int d, LayerMask c, QueryTriggerInteraction U)` |
| 0x36FB544 | 0x2F7FF18 |  | `public Collider[] FDn(Vector3 e, Quaternion f, out int F, LayerMask d, QueryTriggerInteraction c)` |
| 0x36FE55C | 0x2F7FF24 |  | `public bool FDV(float e)` |
| 0x3701EA8 | 0x2F7FF2C |  | `private void FDg(ref Vector3 e, Quaternion f)` |
| 0x37024AC | 0x2F7FF30 |  | `public bool FDp(Vector3 e, Quaternion f, out GroundHit F, float d = inf)` |
| 0x37024DC | 0x2F7FF3C |  | `public bool FDv(out GroundHit e, float f = inf)` |
| 0x36FC090 | 0x2F7FF48 |  | `public void Rotate(Vector3 direction, float angularSpeed, bool onlyLateral = true)` |
| 0x370259C | 0x2F7FF4C |  | `public void FDS(float e, bool f = true)` |
| 0x36FE448 | 0x2F7FF50 |  | `public void FDI(Vector3 e, ForceMode f)` |
| 0x36FBA54 | 0x2F7FF54 |  | `public void FDM(float e)` |
| 0x3702714 | 0x2F7FF58 |  | `public void Fne(Vector3 e)` |
| 0x36F9C60 | 0x2F7FF5C |  | `public void Fnf(float e = 0.1)` |
| 0x36FB9B0 | 0x2F7FF60 |  | `public void FnF()` |
| 0x36FB9B8 | 0x2F7FF64 |  | `public void Fnd()` |
| 0x37028B4 | 0x2F7FF68 |  | `private void Fnc()` |
| 0x370295C | 0x2F7FF6C |  | `private void FnU()` |
| 0x3702DC4 | 0x2F7FF70 |  | `private void FnY()` |
| 0x37030F8 | 0x2F7FF74 |  | `private void FnW(Vector3 e, float f, bool F)` |
| 0x3703944 | 0x2F7FF78 |  | `private void FnE(Vector3 e, float f, float F, float d, float c, float U)` |
| 0x3703F9C | 0x2F7FF7C |  | `private void FnA(Vector3 e, float f, float F, float d, float c, float U, bool Y = true)` |
| 0x37048E0 | 0x2F7FF80 |  | `private void Fnu(Vector3 e, float f, float F, float d, float c, float U, bool Y)` |
| 0x3704B54 | 0x2F7FF84 |  | `private void Fnk()` |
| 0x3704D70 | 0x2F7FF88 |  | `private void FnO()` |
| 0x36FCF70 | 0x2F7FF8C |  | `public void Move(Vector3 desiredVelocity, float maxDesiredSpeed, bool onlyLateral = true)` |
| 0x36FBEC0 | 0x2F7FF90 |  | `public void Move(Vector3 desiredVelocity, float maxDesiredSpeed, float acceleration, float deceleration, float friction, float brakingFriction, bool onlyLateral = true)` |
| 0x3704EA4 | 0x2F7FF94 |  | `private void Fnt()` |
| 0x3705190 | 0x2F7FF98 |  | `private void Fnr(ref Vector3 e, ref Quaternion f)` |
| 0x3705668 | 0x2F7FF9C |  | `private void FnN(ref Vector3 e, ref Quaternion f)` |
| 0x37057F4 | 0x2F7FFA0 |  | `private IEnumerator Fnq()` |
| 0x3705888 | 0x2F7FFA8 |  | `public void OnValidate()` |
| 0x37058E4 | 0x2F7FFAC |  | `public void Awake()` |
| 0x3705C80 | 0x2F7FFB0 |  | `public void OnEnable()` |
| 0x3705CD4 | 0x2F7FFB4 |  | `public void OnDisable()` |
| 0x3705CE8 | 0x2F7FFB8 |  | `public void .ctor()` |

</details>

### public sealed class `GroundDetection` : BaseGroundDetection  
`TypeDefIndex 3956`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3706B0C | 0x2F7FFE8 |  | `private bool FVA(Vector3 e, Quaternion f, out RaycastHit F, float d, float c = 0.05)` |
| 0x3706CE8 | 0x2F7FFFC |  | `private bool FVu(Vector3 e, Quaternion f, out RaycastHit F, float d, float c = 0.05)` |
| 0x3706E5C | 0x2F80010 |  | `private bool FVk(Vector3 e, Quaternion f, Vector3 F, out RaycastHit d, float c = inf, float U = 0.05)` |
| 0x3707250 | 0x2F80024 |  | `private void FVO(Vector3 e, Quaternion f, ref GroundHit F, float d, Vector3 c, Vector3 U)` |
| 0x3707D0C | 0x2F80028 | 9 | `public override bool FPj(Vector3 e, Quaternion f, ref GroundHit F, float d = inf)` |
| 0x37081C8 | 0x2F80030 | 10 | `public override bool FPa(Vector3 e, out RaycastHit f, float F = inf, float d = 0.05)` |
| 0x3708704 | 0x2F80044 | 11 | `protected override void FVE()` |
| 0x3708708 | 0x2F80048 |  | `public void .ctor()` |

</details>

### public struct `GroundHit`  
`TypeDefIndex 3957`

| offset | field |
|---|---|
| 0x0 | `private float kyG;` |
| 0x4 | `private float kyP;` |

Properties: `public bool kyD { get; set; }`; `public bool kyn { get; set; }`; `public bool kyV { get; set; }`; `public bool kyg { get; set; }`; `public float shV { get; set; }`; `public bool kyp { get; set; }`; `public float shg { get; set; }`; `public Vector3 kyv { get; set; }`; `public Vector3 kyS { get; set; }`; `public float kyI { get; set; }`; `public Collider kyM { get; set; }`; `public Rigidbody kze { get; set; }`; `public Vector3 kzf { get; set; }`

<details><summary>methods (29)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370875C | 0x2F80050 |  | `public bool get_kyD()` |
| 0x3708764 | 0x2F80058 |  | `public void set_kyD(bool value)` |
| 0x3708770 | 0x2F8005C |  | `public bool get_kyn()` |
| 0x3708778 | 0x2F80064 |  | `public void set_kyn(bool value)` |
| 0x3708784 | 0x2F80068 |  | `public bool get_kyV()` |
| 0x370878C | 0x2F80070 |  | `public void set_kyV(bool value)` |
| 0x3708798 | 0x2F80074 |  | `public bool get_kyg()` |
| 0x37087A0 | 0x2F8007C |  | `public void set_kyg(bool value)` |
| 0x37087AC | 0x2F80080 |  | `public float get_shV()` |
| 0x3707CFC | 0x2F80088 |  | `public void set_shV(float value)` |
| 0x37087B4 | 0x2F8008C |  | `public bool get_kyp()` |
| 0x37087BC | 0x2F80094 |  | `public void set_kyp(bool value)` |
| 0x37087C8 | 0x2F80098 |  | `public float get_shg()` |
| 0x3707CEC | 0x2F800A0 |  | `public void set_shg(float value)` |
| 0x37087D0 | 0x2F800A4 |  | `public Vector3 get_kyv()` |
| 0x37087DC | 0x2F800B4 |  | `public void set_kyv(Vector3 value)` |
| 0x37087E8 | 0x2F800B8 |  | `public Vector3 get_kyS()` |
| 0x37087F4 | 0x2F800C8 |  | `public void set_kyS(Vector3 value)` |
| 0x3708800 | 0x2F800CC |  | `public float get_kyI()` |
| 0x3708808 | 0x2F800D4 |  | `private void set_kyI(float value)` |
| 0x3708810 | 0x2F800D8 |  | `public Collider get_kyM()` |
| 0x3708818 | 0x2F800E0 |  | `private void set_kyM(Collider value)` |
| 0x3708820 | 0x2F800E4 |  | `public Rigidbody get_kze()` |
| 0x3708828 | 0x2F800EC |  | `private void set_kze(Rigidbody value)` |
| 0x3708830 | 0x2F800F0 |  | `public Vector3 get_kzf()` |
| 0x370883C | 0x2F80100 |  | `public void set_kzf(Vector3 value)` |
| 0x37068F0 | 0x2F80104 |  | `public void .ctor(GroundHit other)` |
| 0x37086C8 | 0x2F8010C |  | `public void .ctor(RaycastHit hitInfo)` |
| 0x3707C5C | 0x2F80114 |  | `public void FVx(RaycastHit e)` |

</details>

### public class `MouseLook` : MonoBehaviour  
`TypeDefIndex 3958`

| offset | field |
|---|---|
| 0x20 | `private bool _lockCursor;` |
| 0x24 | `private KeyCode _unlockCursorKey;` |
| 0x28 | `private float _lateralSensitivity;` |
| 0x2C | `private float _verticalSensitivity;` |
| 0x30 | `private bool _smooth;` |
| 0x34 | `A smaller value will reach the target faster.")]` |
| - | `public float _smoothTime;` |
| 0x38 | `private bool _clampPitch;` |
| 0x3C | `private float _minPitchAngle;` |
| 0x40 | `private float _maxPitchAngle;` |
| 0x44 | `protected bool kzF;` |
| 0x48 | `protected Quaternion kzd;` |
| 0x58 | `protected Quaternion kzc;` |

Properties: `public bool shp { get; set; }`; `public KeyCode shv { get; set; }`; `public float shS { get; set; }`; `public float shI { get; set; }`; `public bool shM { get; set; }`; `public float sBe { get; set; }`; `public bool sBf { get; set; }`; `public float sBF { get; set; }`; `public float sBd { get; set; }`

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3708848 | 0x2F80118 |  | `public bool get_shp()` |
| 0x3708850 | 0x2F80120 |  | `public void set_shp(bool value)` |
| 0x370885C | 0x2F80124 |  | `public KeyCode get_shv()` |
| 0x3708864 | 0x2F8012C |  | `public void set_shv(KeyCode value)` |
| 0x370886C | 0x2F80130 |  | `public float get_shS()` |
| 0x3708874 | 0x2F80138 |  | `public void set_shS(float value)` |
| 0x3708884 | 0x2F8013C |  | `public float get_shI()` |
| 0x370888C | 0x2F80144 |  | `public void set_shI(float value)` |
| 0x370889C | 0x2F80148 |  | `public bool get_shM()` |
| 0x37088A4 | 0x2F80150 |  | `public void set_shM(bool value)` |
| 0x37088B0 | 0x2F80154 |  | `public float get_sBe()` |
| 0x37088B8 | 0x2F8015C |  | `public void set_sBe(float value)` |
| 0x37088C8 | 0x2F80160 |  | `public bool get_sBf()` |
| 0x37088D0 | 0x2F80168 |  | `public void set_sBf(bool value)` |
| 0x37088DC | 0x2F8016C |  | `public float get_sBF()` |
| 0x37088E4 | 0x2F80174 |  | `public void set_sBF(float value)` |
| 0x3708908 | 0x2F80178 |  | `public float get_sBd()` |
| 0x3708910 | 0x2F80180 |  | `public void set_sBd(float value)` |
| 0x3708934 | 0x2F80184 | 4 | `public virtual void FgY(Transform e, Transform f)` |
| 0x3708984 | 0x2F80188 | 5 | `public virtual void FgW(CharacterMovement e, Transform f)` |
| 0x3708FB0 | 0x2F8018C | 6 | `public virtual void FgE(bool e)` |
| 0x3708FE4 | 0x2F80190 | 7 | `public virtual void FgA()` |
| 0x3708FFC | 0x2F80194 | 8 | `protected virtual void Fgu()` |
| 0x3708F4C | 0x2F80198 |  | `protected Quaternion Fgk(Quaternion e)` |
| 0x3709074 | 0x2F801AC | 9 | `public virtual void OnValidate()` |
| 0x37090C8 | 0x2F801B0 |  | `public void .ctor()` |

</details>

### public sealed class `RaycastGroundDetection` : BaseGroundDetection  
`TypeDefIndex 3959`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37012AC | 0x2F801B8 | 9 | `public override bool FPj(Vector3 e, Quaternion f, ref GroundHit F, float d = inf)` |
| 0x37012E4 | 0x2F801C0 | 10 | `public override bool FPa(Vector3 e, out RaycastHit f, float F = inf, float d = 0.05)` |
| 0x370131C | 0x2F801D4 |  | `public void .ctor()` |

</details>

### public sealed class `SphereGroundDetection` : BaseGroundDetection  
`TypeDefIndex 3960`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3701370 | 0x2F801DC | 9 | `public override bool FPj(Vector3 e, Quaternion f, ref GroundHit F, float d = inf)` |
| 0x37013A8 | 0x2F801E4 | 10 | `public override bool FPa(Vector3 e, out RaycastHit f, float F = inf, float d = 0.05)` |
| 0x37013E0 | 0x2F801F8 |  | `public void .ctor()` |

</details>
