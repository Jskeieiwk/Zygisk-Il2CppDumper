# namespace `ECM.Controllers`  (3 types)

### public class `BaseAgentController` : BaseCharacterController  
`TypeDefIndex 3949`

| offset | field |
|---|---|
| - | `If this property is set to true, the agent will brake automatically as it nears the destination.")]` |
| 0x11C | `private bool _autoBraking;` |
| 0x120 | `private float _brakingDistance;` |
| 0x124 | `private float _stoppingDistance;` |
| 0x128 | `public LayerMask groundMask;` |

Properties: `public NavMeshAgent koz { get; set; }`; `public bool syV { get; set; }`; `public float syg { get; set; }`; `public float syp { get; }`; `public float syv { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36FD410 | 0x2F7F854 |  | `public NavMeshAgent get_koz()` |
| 0x36FD418 | 0x2F7F85C |  | `private void set_koz(NavMeshAgent value)` |
| 0x36FD428 | 0x2F7F860 |  | `public bool get_syV()` |
| 0x36FD430 | 0x2F7F868 |  | `public void set_syV(bool value)` |
| 0x36FD4CC | 0x2F7F86C |  | `public float get_syg()` |
| 0x36FD4D4 | 0x2F7F874 |  | `public void set_syg(float value)` |
| 0x36FD4E8 | 0x2F7F878 |  | `public float get_syp()` |
| 0x36FD5B0 | 0x2F7F880 |  | `public float get_syv()` |
| 0x36FD5B8 | 0x2F7F888 |  | `public void set_syv(float value)` |
| 0x36FD65C | 0x2F7F88C |  | `protected void FKc()` |
| 0x36FD704 | 0x2F7F890 | 30 | `protected virtual void FKU()` |
| 0x36FD8B0 | 0x2F7F894 | 22 | `protected override Vector3 Fxw()` |
| 0x36FD91C | 0x2F7F8A4 | 26 | `protected override void FxQ()` |
| 0x36FDA88 | 0x2F7F8A8 | 27 | `public override void Awake()` |
| 0x36FDC28 | 0x2F7F8AC | 31 | `public virtual void LateUpdate()` |
| 0x36FDC2C | 0x2F7F674 |  | `public void .ctor()` |
| 0x36FDC64 | 0x2F7F8B0 | 12 | `public override bool Fuk()` |

</details>

### public class `BaseCharacterController` : XY  
`TypeDefIndex 3950`

| offset | field |
|---|---|
| 0x90 | `private float _speed;` |
| 0x94 | `private float _angularSpeed;` |
| 0x98 | `private float _acceleration;` |
| 0x9C | `private float _deceleration;` |
| 0xA0 | `If useBrakingFriction is false, this also affects the ability to stop more quickly when braking.")]` |
| - | `private float _groundFriction;` |
| 0xA4 | `private bool _useBrakingFriction;` |
| - | `Only used if useBrakingFriction is true, otherwise groundFriction is used.")]` |
| 0xA8 | `private float _brakingFriction;` |
| 0xAC | `private float _airFriction;` |
| - | `0 - no control, 1 - full control.")]` |
| 0xB0 | `private float _airControl;` |
| 0xB4 | `private bool _canCrouch;` |
| 0xB8 | `private float _standingHeight;` |
| 0xBC | `private float _crouchingHeight;` |
| 0xC0 | `private float _baseJumpHeight;` |
| 0xC4 | `private float _extraJumpTime;` |
| 0xC8 | `private float _extraJumpPower;` |
| 0xCC | `Typical values goes from 0.15f to 0.5f.")]` |
| - | `private float _jumpPreGroundedToleranceTime;` |
| 0xD0 | `private float _jumpPostGroundedToleranceTime;` |
| 0xD4 | `private float _maxMidAirJumps;` |
| - | `This requires a 'RootMotionController' attached to the 'Animator' game object.")]` |
| 0xD8 | `private bool _useRootMotion;` |
| 0xD9 | `This requires a 'RootMotionController' attached to the 'Animator' game object.")]` |
| - | `private bool _rootMotionRotation;` |
| 0xDC | `private Vector3 koh;` |
| 0xE8 | `protected bool koB;` |
| 0xE9 | `protected bool kom;` |
| 0xEA | `protected bool koR;` |
| 0xEB | `protected bool kob;` |
| 0xEC | `protected float kol;` |
| 0xF0 | `protected float kox;` |
| 0xF4 | `protected float koK;` |
| 0xF8 | `protected int koG;` |
| 0xFC | `private bool koP;` |
| 0xFD | `private bool koD;` |

Properties: `public CharacterMovement kon { get; set; }`; `public Animator koV { get; set; }`; `public uy kog { get; set; }`; `public bool syS { get; set; }`; `public float syI { get; set; }`; `public float syM { get; set; }`; `public float sze { get; set; }`; `public float szf { get; set; }`; `public float szF { get; set; }`; `public bool szd { get; set; }`; `public float szc { get; set; }`; `public float szU { get; set; }`; `public float szY { get; set; }`; `public bool szW { get; set; }`; `public float szE { get; set; }`; `public float szA { get; set; }`; `public float szu { get; set; }`; `public float szk { get; }`; `public float szO { get; set; }`; `public float szt { get; set; }`; `public float szr { get; set; }`; `public float szN { get; set; }`; `public float szq { get; set; }`; `public bool szs { get; set; }`; `public bool szC { get; set; }`; `public bool szZ { get; set; }`; `public bool szj { get; set; }`; `public bool sza { get; }`; `public bool szQ { get; }`; `public bool szH { get; }`; `public Vector3 szi { get; set; }`; `public bool kop { get; set; }`; `public bool kov { get; set; }`; `public bool szw { get; set; }`; `public bool koS { get; set; }`; `public bool koI { get; set; }`

<details><summary>methods (86)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36FDC6C | 0x2F7F8B8 |  | `public CharacterMovement get_kon()` |
| 0x36FDC74 | 0x2F7F8C0 |  | `private void set_kon(CharacterMovement value)` |
| 0x36FDC84 | 0x2F7F8C4 |  | `public Animator get_koV()` |
| 0x36FDC8C | 0x2F7F8CC |  | `public void set_koV(Animator value)` |
| 0x36FDC9C | 0x2F7F8D0 |  | `public uy get_kog()` |
| 0x36FDCA4 | 0x2F7F8D8 |  | `public void set_kog(uy value)` |
| 0x36FDCB4 | 0x2F7F8DC |  | `public bool get_syS()` |
| 0x36FB924 | 0x2F7F8E4 |  | `public void set_syS(bool value)` |
| 0x36FDCBC | 0x2F7F8E8 |  | `public float get_syI()` |
| 0x36FADA8 | 0x2F7F8F0 |  | `public void set_syI(float value)` |
| 0x36FDCC4 | 0x2F7F8F4 |  | `public float get_syM()` |
| 0x36FDCCC | 0x2F7F8FC |  | `public void set_syM(float value)` |
| 0x36FBFC8 | 0x2F7F900 |  | `public float get_sze()` |
| 0x36FDCDC | 0x2F7F908 |  | `public void set_sze(float value)` |
| 0x36FC00C | 0x2F7F90C |  | `public float get_szf()` |
| 0x36FDCEC | 0x2F7F914 |  | `public void set_szf(float value)` |
| 0x36FDCFC | 0x2F7F918 |  | `public float get_szF()` |
| 0x36FDD04 | 0x2F7F920 |  | `public void set_szF(float value)` |
| 0x36FDD14 | 0x2F7F924 |  | `public bool get_szd()` |
| 0x36FDD1C | 0x2F7F92C |  | `public void set_szd(bool value)` |
| 0x36FDD28 | 0x2F7F930 |  | `public float get_szc()` |
| 0x36FDD30 | 0x2F7F938 |  | `public void set_szc(float value)` |
| 0x36FDD40 | 0x2F7F93C |  | `public float get_szU()` |
| 0x36FDD48 | 0x2F7F944 |  | `public void set_szU(float value)` |
| 0x36FDD58 | 0x2F7F948 |  | `public float get_szY()` |
| 0x36FC35C | 0x2F7F950 |  | `public void set_szY(float value)` |
| 0x36FDD60 | 0x2F7F954 |  | `public bool get_szW()` |
| 0x36FDD68 | 0x2F7F95C |  | `public void set_szW(bool value)` |
| 0x36FDD74 | 0x2F7F960 |  | `public float get_szE()` |
| 0x36FDD7C | 0x2F7F968 |  | `public void set_szE(float value)` |
| 0x36FDD8C | 0x2F7F96C |  | `public float get_szA()` |
| 0x36FDD94 | 0x2F7F974 |  | `public void set_szA(float value)` |
| 0x36FDDA4 | 0x2F7F978 |  | `public float get_szu()` |
| 0x36FDDAC | 0x2F7F980 |  | `public void set_szu(float value)` |
| 0x36FB9C4 | 0x2F7F984 |  | `public float get_szk()` |
| 0x36FDDBC | 0x2F7F98C |  | `public float get_szO()` |
| 0x36FDDC4 | 0x2F7F994 |  | `public void set_szO(float value)` |
| 0x36FDDD4 | 0x2F7F998 |  | `public float get_szt()` |
| 0x36FDDDC | 0x2F7F9A0 |  | `public void set_szt(float value)` |
| 0x36FDDEC | 0x2F7F9A4 |  | `public float get_szr()` |
| 0x36FDDF4 | 0x2F7F9AC |  | `public void set_szr(float value)` |
| 0x36FDE04 | 0x2F7F9B0 |  | `public float get_szN()` |
| 0x36FDE0C | 0x2F7F9B8 |  | `public void set_szN(float value)` |
| 0x36FDE1C | 0x2F7F9BC |  | `public float get_szq()` |
| 0x36FDE24 | 0x2F7F9C4 |  | `public void set_szq(float value)` |
| 0x36FDE34 | 0x2F7F9C8 |  | `public bool get_szs()` |
| 0x36FDE3C | 0x2F7F9D0 |  | `public void set_szs(bool value)` |
| 0x36FDE48 | 0x2F7F9D4 |  | `public bool get_szC()` |
| 0x36FDE50 | 0x2F7F9DC |  | `public void set_szC(bool value)` |
| 0x36FCEE8 | 0x2F7F9E0 |  | `public bool get_szZ()` |
| 0x36FD004 | 0x2F7F9E8 |  | `public void set_szZ(bool value)` |
| 0x36FDE5C | 0x2F7F9EC |  | `public bool get_szj()` |
| 0x36F95EC | 0x2F7F9F4 |  | `public void set_szj(bool value)` |
| 0x36FDE64 | 0x2F7F9F8 |  | `public bool get_sza()` |
| 0x36FDE6C | 0x2F7FA00 |  | `public bool get_szQ()` |
| 0x36FBF8C | 0x2F7FA08 |  | `public bool get_szH()` |
| 0x36FDEB8 | 0x2F7FA10 |  | `public Vector3 get_szi()` |
| 0x36F963C | 0x2F7FA20 |  | `public void set_szi(Vector3 value)` |
| 0x36FDEC4 | 0x2F7FA24 |  | `public bool get_kop()` |
| 0x36FDECC | 0x2F7FA2C |  | `public void set_kop(bool value)` |
| 0x36FDED8 | 0x2F7FA30 |  | `public bool get_kov()` |
| 0x36FDEE0 | 0x2F7FA38 |  | `private void set_kov(bool value)` |
| 0x36FDEEC | 0x2F7FA3C |  | `public bool get_szw()` |
| 0x36FDEF4 | 0x2F7FA44 |  | `public void set_szw(bool value)` |
| 0x36FDF00 | 0x2F7FA48 |  | `public bool get_koS()` |
| 0x36FDF08 | 0x2F7FA50 |  | `public void set_koS(bool value)` |
| 0x36FDF14 | 0x2F7FA54 |  | `public bool get_koI()` |
| 0x36FDF1C | 0x2F7FA5C |  | `protected void set_koI(bool value)` |
| 0x36FDF28 | 0x2F7FA60 |  | `private void FGH()` |
| 0x36FE0E0 | 0x2F7FA64 |  | `public void FGi(Vector3 e, bool f = true)` |
| 0x36F99EC | 0x2F7FA68 |  | `public void FGw(bool e = true)` |
| 0x36FE104 | 0x2F7FA6C |  | `public void FGJ(bool e = true)` |
| 0x36FE138 | 0x2F7FA70 | 18 | `protected virtual void Jump()` |
| 0x36FE284 | 0x2F7FA74 | 19 | `protected virtual void FGX()` |
| 0x36FE368 | 0x2F7FA78 | 20 | `protected virtual void FGT()` |
| 0x36FE464 | 0x2F7FA7C | 21 | `protected virtual void Crouch()` |
| 0x36FADB8 | 0x2F7FA80 | 22 | `protected virtual Vector3 Fxw()` |
| 0x36FA438 | 0x2F7FA90 | 23 | `protected virtual void Move()` |
| 0x36FE788 | 0x2F7FA94 | 24 | `protected virtual void Fxa()` |
| 0x36FE78C | 0x2F7FA98 | 25 | `protected virtual void FxH()` |
| 0x36FE8AC | 0x2F7FA9C | 26 | `protected virtual void FxQ()` |
| 0x36F9EDC | 0x2F7FAA0 | 27 | `public virtual void Awake()` |
| 0x36FE988 | 0x2F7FAA4 | 28 | `public virtual void FixedUpdate()` |
| 0x36FE9D0 | 0x2F7FAA8 | 29 | `public virtual void Update()` |
| 0x36F9AC0 | 0x2F7F408 |  | `public void .ctor()` |
| 0x36FEA24 | 0x2F7FAAC | 12 | `public override bool Fuk()` |

</details>

### public class `BaseFirstPersonController` : BaseCharacterController  
`TypeDefIndex 3951`

| offset | field |
|---|---|
| 0x11C | `private float _forwardSpeed;` |
| 0x120 | `private float _backwardSpeed;` |
| 0x124 | `private float _strafeSpeed;` |
| 0x128 | `private float _runSpeedMultiplier;` |

Properties: `public Transform koM { get; set; }`; `public Transform kye { get; set; }`; `public MouseLook kyf { get; set; }`; `public float szJ { get; set; }`; `public float szX { get; set; }`; `public float szT { get; set; }`; `public float szL { get; set; }`; `public bool kyF { get; set; }`

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36FEA2C | 0x2F7FAB4 |  | `public Transform get_koM()` |
| 0x36FEA34 | 0x2F7FABC |  | `private void set_koM(Transform value)` |
| 0x36FEA44 | 0x2F7FAC0 |  | `public Transform get_kye()` |
| 0x36FEA4C | 0x2F7FAC8 |  | `private void set_kye(Transform value)` |
| 0x36FEA5C | 0x2F7FACC |  | `public MouseLook get_kyf()` |
| 0x36FEA64 | 0x2F7FAD4 |  | `private void set_kyf(MouseLook value)` |
| 0x36FEA74 | 0x2F7FAD8 |  | `public float get_szJ()` |
| 0x36FEA7C | 0x2F7FAE0 |  | `public void set_szJ(float value)` |
| 0x36FEA8C | 0x2F7FAE4 |  | `public float get_szX()` |
| 0x36FEA94 | 0x2F7FAEC |  | `public void set_szX(float value)` |
| 0x36FEAA4 | 0x2F7FAF0 |  | `public float get_szT()` |
| 0x36FEAAC | 0x2F7FAF8 |  | `public void set_szT(float value)` |
| 0x36FEABC | 0x2F7FAFC |  | `public float get_szL()` |
| 0x36FEAC4 | 0x2F7FB04 |  | `public void set_szL(float value)` |
| 0x36FEAD4 | 0x2F7FB08 |  | `public bool get_kyF()` |
| 0x36FEADC | 0x2F7FB10 |  | `public void set_kyF(bool value)` |
| 0x36FEAE8 | 0x2F7FB14 | 30 | `protected virtual void Fxi()` |
| 0x36FEC44 | 0x2F7FB18 | 31 | `protected virtual void FGV()` |
| 0x36FEC70 | 0x2F7FB1C | 25 | `protected override void FxH()` |
| 0x36FEC80 | 0x2F7FB20 | 32 | `protected virtual float FGg()` |
| 0x36FECC8 | 0x2F7FB28 | 22 | `protected override Vector3 Fxw()` |
| 0x36FED24 | 0x2F7FB38 | 26 | `protected override void FxQ()` |
| 0x36FEE18 | 0x2F7FB3C | 27 | `public override void Awake()` |
| 0x36FF128 | 0x2F7FB40 | 33 | `public virtual void LateUpdate()` |
| 0x36FA860 | 0x2F7F51C |  | `public void .ctor()` |
| 0x36FF138 | 0x2F7FB44 | 12 | `public override bool Fuk()` |

</details>
