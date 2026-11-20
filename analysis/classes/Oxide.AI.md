# namespace `Oxide.AI`  (6 types)

### public class `AIBrain` : Xc  
`TypeDefIndex 3200`

| offset | field |
|---|---|
| 0x90 | `private List<Action> m_AvailableActions;` |
| 0x98 | `private List<Goal> m_AvailableGoals;` |
| 0xA0 | `private Action m_Fallback;` |
| 0xA8 | `private float m_MinPlanInterval;` |
| 0xAC | `private float m_MinGoalPriorityCheckInterval;` |
| 0xB0 | `private Queue<Action> OSi;` |
| 0xB8 | `private yQ OSw;` |
| 0xC0 | `private Goal OSJ;` |
| 0xC8 | `private yH OSX;` |
| 0xD0 | `private AISettings m_Settings;` |
| 0xD8 | `private Animator m_Animator;` |
| 0xE0 | `private NavMeshAgent m_NavMeshAgent;` |
| 0xE8 | `private Chase m_ChaseAction;` |
| 0xF0 | `private bool m_FitGround;` |
| 0xF1 | `private bool OST;` |
| 0xF4 | `private float OSL;` |
| 0xF8 | `private float OSo;` |

Properties: `public List<Action> sMS { get; }`; `public Action sMI { get; }`; `public Queue<Action> sMM { get; }`; `public Goal Cee { get; }`; `public yH Cef { get; }`; `public Animator CeF { get; }`; `public AISettings Ced { get; }`; `public bool Cec { get; }`; `public bool CeU { get; }`

<details><summary>methods (33)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A8DA20 | 0x2ECF470 |  | `public List<Action> get_sMS()` |
| 0x3A8DA28 | 0x2ECF478 |  | `public Action get_sMI()` |
| 0x3A8DA30 | 0x2ECF480 |  | `public Queue<Action> get_sMM()` |
| 0x3A8DA38 | 0x2ECF488 |  | `public Goal get_Cee()` |
| 0x3A8DA40 | 0x2ECF490 |  | `public yH get_Cef()` |
| 0x3A8DA48 | 0x2ECF498 |  | `public Animator get_CeF()` |
| 0x3A8DA50 | 0x2ECF4A0 |  | `public AISettings get_Ced()` |
| 0x3A8DA58 | 0x2ECF4A8 |  | `public bool get_Cec()` |
| 0x3A8DA60 | 0x2ECF4B0 |  | `public bool get_CeU()` |
| 0x3A8DA68 | 0x2ECF4B8 |  | `public void UYD()` |
| 0x3A8DB40 | 0x2ECF5D4 |  | `private void Start()` |
| 0x3A8E1DC | 0x2ECFC6C |  | `public void UYn(string e, bool f)` |
| 0x3A8E368 | 0x2ECFC70 |  | `public void UYV(string e)` |
| 0x3A8E228 | 0x2ECFC74 |  | `public void UYg(string e, bool f)` |
| 0x3A8E3A8 | 0x2ECFC78 |  | `public void UYp(string e)` |
| 0x3A8E4CC | 0x2ECFC7C |  | `public void UYv(bool e)` |
| 0x3A8E5F0 | 0x2ECFC80 |  | `private bool UYS()` |
| 0x3A8E884 | 0x2ECFC88 |  | `private void UYI()` |
| 0x3A8E97C | 0x2ECFC8C |  | `private void UYM()` |
| 0x3A8DDE4 | 0x2ECF878 |  | `private void UWe()` |
| 0x3A8DFAC | 0x2ECFA44 |  | `private void UWf()` |
| 0x3A8EABC | 0x2ECFC90 |  | `private void UWF(int e)` |
| 0x3A8EBE0 | 0x2ECFC94 |  | `public void .ctor()` |
| 0x3A8EBF0 | 0x2ECFCB4 | 12 | `public override bool Fuk()` |
| 0x3A8EBF8 | 0x2ECFCBC |  | `protected void UWd(string e, bool f)` |
| 0x3A8EC28 | 0x2ECFDC8 |  | `protected static void UWc(vd e, vo f, vt F)` |
| 0x3A8ED78 | 0x2ECFE70 |  | `protected void UWU(string e)` |
| 0x3A8EDA4 | 0x2ECFEDC |  | `protected static void UWY(vd e, vo f, vt F)` |
| 0x3A8EEE4 | 0x2ECFF74 |  | `protected void UWW(bool e)` |
| 0x3A8EF80 | 0x2ECFFEC |  | `protected static void UWE(vd e, vo f, vt F)` |
| 0x3A8F0BC | 0x2ED0080 |  | `protected void UWA(int e)` |
| 0x3A8F178 | 0x2ED0168 |  | `protected static void UWu(vd e, vo f, vt F)` |
| 0x3A8F2B8 | 0x2ED0200 |  | `private static void .cctor()` |

</details>

### public class `AISettings` : Xc  
`TypeDefIndex 3201`

| offset | field |
|---|---|
| 0x90 | `private EntityMovement m_Movement;` |
| 0x98 | `private EntityDetection m_Detection;` |
| 0xA0 | `private EntityVitals m_Vitals;` |
| 0xA8 | `private EntityDeathHandler m_DeathHandler;` |
| 0xB0 | `private float m_HitDamage;` |
| 0xB4 | `private float m_MaxAttackDistance;` |
| 0xB8 | `private AudioSource m_AudioSource;` |
| 0xC0 | `private SoundPlayer m_AttackSounds;` |
| 0xC8 | `private SoundPlayer m_HitSounds;` |
| 0xD0 | `private AIBrain m_Brain;` |
| 0xD8 | `private EntityAnimation OSy;` |

Properties: `public EntityMovement CeY { get; }`; `public EntityDetection CeW { get; }`; `public EntityVitals CeE { get; }`; `public EntityAnimation CeA { get; }`; `public AudioSource Ceu { get; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA0EF4 | 0x2ED0444 |  | `public EntityMovement get_CeY()` |
| 0x3AA0EFC | 0x2ED044C |  | `public EntityDetection get_CeW()` |
| 0x3AA0F04 | 0x2ED0454 |  | `public EntityVitals get_CeE()` |
| 0x3AA0F0C | 0x2ECFCF4 |  | `public EntityAnimation get_CeA()` |
| 0x3AA0F14 | 0x2ED05A8 |  | `public AudioSource get_Ceu()` |
| 0x3AA0F1C | 0x2ED05B0 |  | `public void OnAnimationDamage()` |
| 0x3AA0F20 | 0x2ED05B4 |  | `public void PlayAttackSounds()` |
| 0x3AA0F4C | 0x2ED05E0 |  | `public void UWq()` |
| 0x3AA0F78 | 0x2ED060C |  | `private void Start()` |
| 0x3AA105C | 0x2ED062C |  | `public void UWs(ya e)` |
| 0x3AA1060 | 0x2ED0630 |  | `public void .ctor()` |
| 0x3AA1074 | 0x2ED0654 | 12 | `public override bool Fuk()` |

</details>

### public class `EntityAnimation`  
`TypeDefIndex 3202`

| offset | field |
|---|---|
| 0x10 | `private AIBrain OSz;` |
| 0x18 | `private Animator OSh;` |
| 0x20 | `private AnimatorControllerParameter[] OSB;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA0FF8 | 0x2ED0464 |  | `public void UWC(AIBrain e)` |
| 0x3AA107C | 0x2ED065C |  | `public bool UWZ(string e)` |
| 0x3AA1114 | 0x2ECFE98 |  | `public void UWj(string e)` |
| 0x3AA1158 | 0x2ECFD7C |  | `public void UWa(string e, bool f)` |
| 0x3AA11A4 | 0x2ED0730 |  | `public bool UWQ(string e)` |
| 0x3AA0FF0 | 0x2ED045C |  | `public void .ctor()` |

</details>

### public class `EntityDetection`  
`TypeDefIndex 3203`

| offset | field |
|---|---|
| 0x18 | `private float m_TargetSearchDelay;` |
| 0x20 | `private Transform m_Eyes;` |
| 0x28 | `private int m_ViewAngle;` |
| 0x2C | `private int m_ViewRadius;` |
| 0x30 | `private int m_HearRange;` |
| 0x34 | `private LayerMask m_SpotMask;` |
| 0x38 | `private LayerMask m_ObstacleMask;` |
| 0x40 | `private List<GameObject> OSR;` |
| 0x48 | `private List<GameObject> OSb;` |
| 0x50 | `private Transform OSl;` |
| 0x58 | `private float OSx;` |
| 0x5C | `private float OSK;` |
| 0x60 | `private Collider[] OSG;` |
| 0x68 | `private int OSP;` |

Properties: `public int Cek { get; }`; `public int CeO { get; }`; `public int Cet { get; }`; `public GameObject OSm { get; set; }`; `public List<GameObject> Cer { get; }`; `public List<GameObject> CeN { get; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA128C | 0x2ED0808 |  | `public int get_Cek()` |
| 0x3AA1294 | 0x2ED0810 |  | `public int get_CeO()` |
| 0x3AA129C | 0x2ED0818 |  | `public int get_Cet()` |
| 0x3AA12A4 | 0x2ED0820 |  | `public GameObject get_OSm()` |
| 0x3AA12AC | 0x2ED0828 |  | `public void set_OSm(GameObject value)` |
| 0x3AA12B4 | 0x2ED082C |  | `public List<GameObject> get_Cer()` |
| 0x3AA12BC | 0x2ED0834 |  | `public List<GameObject> get_CeN()` |
| 0x3AA12C4 | 0x2ED083C |  | `public void UWo(Transform e)` |
| 0x3AA12F4 | 0x2ED0840 |  | `public void Update(AIBrain brain)` |
| 0x3AA1D9C | 0x2ED0844 |  | `public bool UWy()` |
| 0x3AA1F38 | 0x2ED084C |  | `public bool UWz()` |
| 0x3AA1F88 | 0x2ED0854 |  | `public Transform UWh()` |
| 0x3AA1A58 | 0x2ED085C |  | `private void UWB()` |
| 0x3AA14D8 | 0x2ED0860 |  | `private List<GameObject> UWm()` |
| 0x3AA1410 | 0x2ED0868 |  | `private void UWR()` |
| 0x3AA20CC | 0x2ED086C |  | `public void .ctor()` |

</details>

### public class `EntityMovement`  
`TypeDefIndex 3204`

| offset | field |
|---|---|
| 0x10 | `private float m_WalkSpeed;` |
| 0x14 | `private float m_RunSpeed;` |
| 0x18 | `private LayerMask m_TerrainLayer;` |
| 0x1C | `private Vector3 OSD;` |
| 0x28 | `private Lf.Th OSn;` |
| 0x30 | `private AIBrain OSV;` |
| 0x38 | `private NavMeshAgent OSg;` |
| 0x40 | `private Quaternion OSp;` |
| 0x50 | `private Quaternion OSv;` |
| 0x60 | `private Quaternion OSS;` |
| 0x70 | `private Quaternion OSI;` |
| 0x80 | `private Vector3 OSM;` |
| 0x8C | `private RaycastHit OIe;` |
| 0xB8 | `private Vector3 OIf;` |
| 0xC4 | `private int OIF;` |

Properties: `public Vector3 Ceq { get; }`; `public Lf.Th Ces { get; }`; `public NavMeshAgent CeC { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA21BC | 0x2ED0874 |  | `public Vector3 get_Ceq()` |
| 0x3AA21C8 | 0x2ED0884 |  | `public Lf.Th get_Ces()` |
| 0x3AA21D0 | 0x2ED088C |  | `public NavMeshAgent get_CeC()` |
| 0x3AA21D8 | 0x2ED0894 |  | `public void UWK(AIBrain e)` |
| 0x3AA22F8 | 0x2ED0898 |  | `public void Update(Transform transform)` |
| 0x3AA27DC | 0x2ED089C |  | `public void UWG(Transform e)` |
| 0x3AA2B48 | 0x2ED08A0 |  | `private void UWP(float e, string f, bool F, Lf.Th d)` |
| 0x3AA2BA4 | 0x2ED08A4 |  | `public bool UWD(bool e = true)` |
| 0x3AA2698 | 0x2ED08AC |  | `private bool UWn(Vector3 e, out RaycastHit f)` |
| 0x3AA2C78 | 0x2ED08C0 |  | `public void UWV(Quaternion e)` |
| 0x3AA2C84 | 0x2ED08C4 |  | `public void .ctor()` |

</details>

### public class `EntityVitals`  
`TypeDefIndex 3205`

| offset | field |
|---|---|
| 0x10 | `private float m_HungerRegenerationTime;` |
| 0x14 | `private float OId;` |
| 0x18 | `private bool OIc;` |

Properties: `public bool CeZ { get; set; }`; `public float Cej { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA2C8C | 0x2ED08CC |  | `public bool get_CeZ()` |
| 0x3AA2C94 | 0x2ED08D4 |  | `public void set_CeZ(bool value)` |
| 0x3AA2CA0 | 0x2ED08D8 |  | `public float get_Cej()` |
| 0x3AA2CA8 | 0x2ED08E0 |  | `public void set_Cej(float value)` |
| 0x3AA2CB0 | 0x2ED08E4 |  | `public void Update(AIBrain brain)` |
| 0x3AA2D80 | 0x2ED08E8 |  | `public void .ctor()` |

</details>
