# namespace `HyperHug.Games.Oxide.Features.Network`  (5 types)

### public struct `Capture3DRotated` : jT  
`TypeDefIndex 3616`

| offset | field |
|---|---|
| 0x0 | `public Vector3 Position;` |
| 0xC | `public Vector3 Size;` |
| 0x18 | `public Quaternion Rotation;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387F5BC | 0x2F5B490 |  | `public void .ctor(Vector3 position, Vector3 size, Quaternion rotation)` |
| 0x3880CD0 | 0x2F5B4A0 | 4 | `public void dDZ()` |
| 0x387FEB0 | 0x2F5B4A4 |  | `public static Capture3DRotated dDj(Capture3DRotated e, Capture3DRotated f, double F)` |
| 0x3880DBC | 0x2F5B4B4 | 3 | `public override string ToString()` |

</details>

### public struct `CaptureTransform` : jT  
`TypeDefIndex 3617`

| offset | field |
|---|---|
| 0x8 | `public Vector3 Position;` |
| 0x14 | `public Quaternion Rotation;` |

Properties: `public double OEp { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3882970 | 0x2F5B4BC |  | `public double get_OEp()` |
| 0x3882978 | 0x2F5B4C4 |  | `public void set_OEp(double value)` |
| 0x3882030 | 0x2F5B4C8 |  | `public void .ctor(double timestamp, Vector3 position, Quaternion rotation)` |
| 0x3882980 | 0x2F5B4D8 | 4 | `public void dDZ()` |
| 0x3881DA0 | 0x2F5B4DC |  | `public static CaptureTransform dDn(CaptureTransform e, CaptureTransform f, double F)` |

</details>

### public abstract class `DistributedInterestManagement` : pD  
`TypeDefIndex 3621`

| offset | field |
|---|---|
| - | `private const int OEz = 64;` |
| 0x28 | `private int OEh;` |
| 0x2C | `private int visibleRange;` |
| 0x30 | `private float rebuildInterval;` |
| 0x38 | `private List<uint> OEB;` |
| 0x40 | `private Dictionary<uint, List<DistributedInterestManagement.jJ>> OEm;` |
| 0x48 | `private double OER;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x387E1E0 | 0x2F5B4EC |  | `private int dDY(NetworkIdentity e)` |
| 0x387E29C | 0x2F5B4F4 | 6 | `public override void dDW()` |
| 0x387E330 | 0x2F5B4F8 | 4 | `public override bool dDE(NetworkIdentity e, vt f)` |
| 0x387E990 | 0x2F5B500 | 12 | `public override void dDA(NetworkIdentity e, HashSet<vt> f)` |
| 0x387E454 | 0x2F5B504 |  | `internal void dDu(NetworkIdentity e)` |
| 0x387E7F8 | 0x2F5B508 |  | `internal void dDk(NetworkIdentity e, bool f)` |
| 0x387F0FC | 0x2F5B50C |  | `internal void Update()` |
| 0x387F1BC | 0x2F5B510 |  | `private void dDO()` |
| 0x387F3F4 | 0x2F5B514 |  | `public void .ctor()` |
| 0x387ECC0 | 0x2F5B51C |  | `internal static void dDt(Component e, ref DistributedInterestManagement._003C_003Ec__DisplayClass12_0 f)` |
| 0x387EE64 | 0x2F5B520 |  | `private void dDr(ref DistributedInterestManagement._003C_003Ec__DisplayClass13_0 e)` |

</details>

### public class `HitBoxRecorderRoot` : vd  
`TypeDefIndex 3622`

| offset | field |
|---|---|
| 0x68 | `private HitBox[] hitBoxes;` |
| 0x70 | `private bool useTickProvider;` |
| 0x74 | `private int historyLimit;` |
| 0x78 | `private jX[] OEK;` |
| 0x80 | `public Color historyColor;` |
| 0x90 | `private jL OEG;` |
| 0x98 | `private uint OEP;` |

Properties: `public uint sPf { get; }`; `public float sPF { get; }`; `public bool sPd { get; }`; `public HitBox[] sPc { get; set; }`; `public uint sPU { get; set; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3880E8C | 0x2F5B52C |  | `public uint get_sPf()` |
| 0x3880F44 | 0x2F5B534 |  | `public float get_sPF()` |
| 0x3881000 | 0x2F5B53C |  | `public bool get_sPd()` |
| 0x3881008 | 0x2F5B544 |  | `public HitBox[] get_sPc()` |
| 0x3881010 | 0x2F5B54C |  | `private void set_sPc(HitBox[] value)` |
| 0x3881670 | 0x2F5B550 |  | `public uint get_sPU()` |
| 0x3881180 | 0x2F5B558 |  | `public void set_sPU([In] uint value)` |
| 0x3881018 | 0x2F5B55C |  | `private void Awake()` |
| 0x3881078 | 0x2F5B560 |  | `private void Update()` |
| 0x3881238 | 0x2F5B564 |  | `public void dDJ(uint e)` |
| 0x388129C | 0x2F5B568 |  | `public bool dDX(int e, Vector3 f, float F, uint d, float c)` |
| 0x38812D4 | 0x2F5B570 |  | `public void dDT(PlayerManager e)` |
| 0x38813E4 | 0x2F5B680 |  | `private void dDL()` |
| 0x388151C | 0x2F5B684 |  | `private void dDo()` |
| 0x3881650 | 0x2F5B688 |  | `public void .ctor()` |
| 0x3881668 | 0x2F5B690 | 12 | `public override bool Fuk()` |
| 0x3881678 | 0x2F5B698 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x38816D8 | 0x2F5B69C | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public struct `PlayerConnectedMessage` : vw  
`TypeDefIndex 3623`
