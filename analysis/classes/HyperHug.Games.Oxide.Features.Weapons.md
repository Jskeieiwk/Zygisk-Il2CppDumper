# namespace `HyperHug.Games.Oxide.Features.Weapons`  (4 types)

### public class `DispersionConfig` : ScriptableObject  
`TypeDefIndex 3387`

| offset | field |
|---|---|
| 0x18 | `private float minFireDispersion;` |
| 0x1C | `private float maxFireDispersion;` |
| 0x20 | `private float minDispersion;` |
| 0x24 | `private float maxDispersion;` |
| 0x28 | `private float dispersionIncreasePerShot;` |
| 0x2C | `private float dispersionDecreaseRate;` |

Properties: `public float MinFireDispersion { get; }`; `public float MaxFireDispersion { get; }`; `public float MinDispersion { get; }`; `public float MaxDispersion { get; }`; `public float IncreasePerShot { get; }`; `public float DecreaseRate { get; }`; `public float sbp { get; }`; `public float sbv { get; }`; `public float sbS { get; }`; `public float sbI { get; }`; `public float sbM { get; }`; `public float sle { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F075CC |  | `public float get_MinFireDispersion()` |
| - | 0x2F075D4 |  | `public float get_MaxFireDispersion()` |
| - | 0x2F075DC |  | `public float get_MinDispersion()` |
| - | 0x2F075E4 |  | `public float get_MaxDispersion()` |
| - | 0x2F075EC |  | `public float get_IncreasePerShot()` |
| - | 0x2F075F4 |  | `public float get_DecreaseRate()` |
| - | 0x2F075FC |  | `public float get_sbp()` |
| - | 0x2F07604 |  | `public float get_sbv()` |
| - | 0x2F0760C |  | `public float get_sbS()` |
| - | 0x2F07614 |  | `public float get_sbI()` |
| - | 0x2F0761C |  | `public float get_sbM()` |
| - | 0x2F07624 |  | `public float get_sle()` |
| 0x380273C | 0x2F0762C |  | `public void .ctor()` |

</details>

### public struct `HitCheckData`  
`TypeDefIndex 3388`

| offset | field |
|---|---|
| 0x0 | `public int weaponId;` |
| 0x4 | `public bool hit;` |
| 0x8 | `public uint targetId;` |

### public class `HitscanWeaponConfig` : ScriptableObject  
`TypeDefIndex 3389`

| offset | field |
|---|---|
| 0x18 | `private float damage;` |
| 0x1C | `private float fireRate;` |
| 0x20 | `private float range;` |
| 0x24 | `private float accuracy;` |
| 0x28 | `private float mobility;` |
| 0x2C | `private int maxMagazineAmmo;` |
| 0x30 | `private float reloadTime;` |
| 0x34 | `private float prepareTime;` |
| 0x38 | `private int projectilesPerShot;` |
| 0x3C | `private bool needPrepareEveryShot;` |
| 0x3D | `private bool suppressReloadWhileAimed;` |
| 0x3E | `private bool suppressed;` |
| 0x40 | `private DispersionConfig dispersionConfig;` |

Properties: `public DispersionConfig slf { get; }`; `public float slF { get; }`; `public float sld { get; }`; `public int slc { get; }`; `public float slU { get; }`; `public float slY { get; }`; `public float slW { get; }`; `public float slE { get; }`; `public float slA { get; }`; `public float slu { get; }`; `public float slk { get; }`; `public float slO { get; }`; `public float slt { get; }`; `public int slr { get; }`; `public bool slN { get; }`; `public bool slq { get; }`; `public bool sls { get; }`; `public float FireRateValue { get; }`; `public float ReloadTimeValue { get; }`; `public float RangeValue { get; }`; `public float AccuracyValue { get; }`; `public int PelletsValue { get; }`; `public DispersionConfig DispersionValue { get; }`

<details><summary>methods (24)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x380275C | 0x2F07634 |  | `public DispersionConfig get_slf()` |
| 0x3802764 | 0x2F0763C |  | `public float get_slF()` |
| 0x380276C | 0x2F07644 |  | `public float get_sld()` |
| 0x3802774 | 0x2F0764C |  | `public int get_slc()` |
| 0x380277C | 0x2F07654 |  | `public float get_slU()` |
| 0x3802784 | 0x2F0765C |  | `public float get_slY()` |
| - | 0x2F07664 |  | `public float get_slW()` |
| 0x3802794 | 0x2F0766C |  | `public float get_slE()` |
| 0x38027A8 | 0x2F07674 |  | `public float get_slA()` |
| 0x38027B0 | 0x2F0767C |  | `public float get_slu()` |
| 0x38027C4 | 0x2F07684 |  | `public float get_slk()` |
| 0x38027CC | 0x2F0768C |  | `public float get_slO()` |
| 0x38027E0 | 0x2F07694 |  | `public float get_slt()` |
| 0x38027FC | 0x2F0769C |  | `public int get_slr()` |
| 0x3802804 | 0x2F076A4 |  | `public bool get_slN()` |
| 0x380280C | 0x2F076AC |  | `public bool get_slq()` |
| 0x3802814 | 0x2F076B4 |  | `public bool get_sls()` |
| - | 0x2F076BC |  | `public float get_FireRateValue()` |
| - | 0x2F076C4 |  | `public float get_ReloadTimeValue()` |
| - | 0x2F076CC |  | `public float get_RangeValue()` |
| - | 0x2F076D4 |  | `public float get_AccuracyValue()` |
| - | 0x2F076DC |  | `public int get_PelletsValue()` |
| - | 0x2F076EC |  | `public DispersionConfig get_DispersionValue()` |
| - | 0x2F076F4 |  | `public void .ctor()` |

</details>

### public class `PlayerWeapon` : vd  
`TypeDefIndex 3391`

| offset | field |
|---|---|
| - | `private const float kIn = 0.2;` |
| - | `private const float kIV = 0.1;` |
| 0x0 | `public static string[] obfuscatedKeys;` |
| 0x68 | `public PlayerManager player;` |
| 0x70 | `public Animator animator;` |
| 0x78 | `public jQ playerWeaponView;` |
| 0x80 | `private jk playerFPWeaponView;` |
| 0x88 | `private LayerMask shotMask;` |
| 0x90 | `private FPManager fPManager;` |
| 0x98 | `private jiL kIg;` |
| 0x9C | `private bool kIp;` |
| 0xA0 | `private WeaponPiece kIv;` |
| 0xAC | `private int kIS;` |
| 0xB0 | `private int kII;` |
| 0xB4 | `private jiL kIM;` |
| - | `private int damagePoseFrame;` |
| - | `private jQ ownBodyView;` |
| - | `private WeaponPiece ownBodyPiece;` |
| - | `private int ownBodyAnimationId;` |
| - | `private bool bodyReloadReset;` |
| - | `private float bodyReloadResetUntil;` |
| - | `private int reloadSequence;` |
| - | `private int pendingReloadSequence;` |
| - | `private int bodyReloadSequence;` |
| - | `private float reloadRequestAt;` |

Properties: `public float slC { get; }`; `public int slZ { get; set; }`; `public bool slj { get; set; }`; `public WeaponPiece sla { get; set; }`; `public int slQ { get; set; }`; `public uint OwnerNetId { get; }`; `public bool ReloadPending { get; }`

<details><summary>methods (70)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F076FC |  | `public float get_slC()` |
| 0x38047FC | 0x2F077AC |  | `public int get_slZ()` |
| 0x3804804 | 0x2F077B4 |  | `public void set_slZ([In] int value)` |
| 0x38048BC | 0x2F077B8 |  | `public bool get_slj()` |
| 0x38048C4 | 0x2F077C0 |  | `public void set_slj([In] bool value)` |
| 0x3804980 | 0x2F077C4 |  | `public WeaponPiece get_sla()` |
| 0x3804990 | 0x2F077D0 |  | `public void set_sla([In] WeaponPiece value)` |
| 0x3804A58 | 0x2F077D4 |  | `public int get_slQ()` |
| 0x3804A60 | 0x2F077DC |  | `public void set_slQ([In] int value)` |
| - | 0x2F077E0 |  | `private void PrepareDamagePose()` |
| - | 0x2F07830 |  | `public bool CanDamageTarget(uint target, Vector3 point)` |
| - | 0x2F07C6C |  | `public uint get_OwnerNetId()` |
| 0x380282C | 0x2F07CEC |  | `public void dia(int e, bool f, uint F, int d, Vector3 c, uint U, float Y)` |
| 0x38029F8 | 0x2F07FB8 |  | `public void diQ(int e, bool f, uint F, int d, Vector3 c, uint U, float Y)` |
| 0x37F6CA0 | 0x2F08224 |  | `public void diH(int e, Vector3 f, Vector3 F, float d)` |
| 0x3802C68 | 0x2F0859C |  | `private void diw(WeaponPiece e, int f)` |
| 0x3802DB0 | 0x2F085A0 | 11 | `public void RecoverLocalFP()` |
| - | 0x2F08778 |  | `public override void Fsv()` |
| 0x3802F54 | 0x2F08A94 | 10 | `public override void diJ()` |
| 0x380301C | 0x2F08B58 |  | `private void Update()` |
| 0x3803250 | 0x2F09264 |  | `public void diX(bool e)` |
| 0x3803358 | 0x2F09268 |  | `public void diT()` |
| 0x3803404 | 0x2F0926C |  | `public void diL()` |
| - | 0x2F08F50 |  | `public void SyncOwnBody()` |
| - | 0x2F08444 |  | `public void AnimateOwnBodyAttack()` |
| - | 0x2F09270 |  | `private int BodyWeaponId()` |
| - | 0x2F093BC |  | `private void AnimateBodyReload()` |
| - | 0x2F094E4 |  | `private void LateUpdate()` |
| 0x3803514 | 0x2F095C8 |  | `public void dio()` |
| 0x380362C | 0x2F09714 |  | `public void diy()` |
| 0x380373C | 0x2F09718 |  | `public void diz()` |
| 0x380384C | 0x2F0971C |  | `public void dih(Vector3 e, Quaternion f, TU F, int d)` |
| 0x3803A70 | 0x2F09AA4 |  | `public void diB(int e, Vector3 f, Quaternion F, int d)` |
| 0x3803C20 | 0x2F09CE8 |  | `public void dim(int e, Vector3 f, Quaternion F, int d)` |
| 0x3803DD0 | 0x2F09CEC |  | `public void diR(int e, Vector3 f, Quaternion F, int d)` |
| 0x3803F80 | 0x2F097A4 |  | `private void dib(int e, Vector3 f, Quaternion F, int d)` |
| - | 0x2F09CF0 |  | `public bool get_ReloadPending()` |
| - | 0x2F09D44 |  | `public bool BeginReloadV1(int objectId)` |
| - | 0x2F09F60 |  | `private void ApplyReloadState(int sequence, int state)` |
| 0x37F6340 | 0x2F09FA4 |  | `public void dil(int e, bool f)` |
| 0x3804174 | 0x2F0A154 |  | `public FPObject dix(string e)` |
| 0x3804190 | 0x2F0A15C |  | `public void .ctor()` |
| 0x38041A4 | 0x2F0A170 |  | `private static void .cctor()` |
| 0x38047F4 | 0x2F0A4C8 | 12 | `public override bool Fuk()` |
| 0x3804B18 | 0x2F0A4D0 |  | `protected void div(int e, bool f, uint F, int d, Vector3 c, uint U, float Y)` |
| 0x3804B1C | 0x2F0A4D4 |  | `protected static void diS(vd e, vo f, vt F)` |
| 0x3804CCC | 0x2F0A4D8 |  | `protected void diI(int e, bool f, uint F, int d, Vector3 c, uint U, float Y)` |
| 0x3804CD0 | 0x2F0A4DC |  | `protected static void diM(vd e, vo f, vt F)` |
| 0x3804E80 | 0x2F0A4E0 |  | `protected void dwe(int e, Vector3 f, Vector3 F, float d)` |
| 0x3804E84 | 0x2F0A4E4 |  | `protected static void dwf(vd e, vo f, vt F)` |
| 0x3805010 | 0x2F0A4E8 |  | `protected void dwF(WeaponPiece e, int f)` |
| 0x380510C | 0x2F0A83C |  | `protected static void dwd(vd e, vo f, vt F)` |
| 0x3805264 | 0x2F0A840 |  | `protected void dwc()` |
| 0x38052D4 | 0x2F0A844 |  | `protected static void dwU(vd e, vo f, vt F)` |
| 0x38053F0 | 0x2F0A8C4 |  | `protected void dwY()` |
| 0x38053F4 | 0x2F0A8C8 |  | `protected static void dwW(vd e, vo f, vt F)` |
| 0x3805540 | 0x2F0A8CC |  | `protected void dwE()` |
| 0x380563C | 0x2F0AA08 |  | `protected static void dwA(vd e, vo f, vt F)` |
| 0x3805758 | 0x2F0AA88 |  | `protected void dwu()` |
| 0x3805804 | 0x2F0AB48 |  | `protected static void dwk(vd e, vo f, vt F)` |
| 0x3805920 | 0x2F0ABC8 |  | `protected void dwO(int e, Vector3 f, Quaternion F, int d)` |
| 0x3805924 | 0x2F0ABCC |  | `protected static void dwt(vd e, vo f, vt F)` |
| 0x3805AB0 | 0x2F0ABD0 |  | `protected void dwr(int e, Vector3 f, Quaternion F, int d)` |
| 0x3805AB4 | 0x2F0ABD4 |  | `protected static void dwN(vd e, vo f, vt F)` |
| 0x3805C80 | 0x2F0ABD8 |  | `protected void dwq(int e, Vector3 f, Quaternion F, int d)` |
| 0x3805C84 | 0x2F0ABDC |  | `protected static void dws(vd e, vo f, vt F)` |
| 0x3805E50 | 0x2F0ADF0 |  | `protected void dwC(int e, bool f)` |
| 0x3805E54 | 0x2F0ADF4 |  | `protected static void dwZ(vd e, vo f, vt F)` |
| 0x3805FC8 | 0x2F0ADF8 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x38060B8 | 0x2F0AED4 | 15 | `protected override void FCO(vo e, bool f)` |

</details>
