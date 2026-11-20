# namespace `Oxide.AI.Actions`  (8 types)

### public class `Action` : ScriptableObject  
`TypeDefIndex 3210`

| offset | field |
|---|---|
| 0x18 | `protected int m_Priority;` |
| 0x1C | `protected bool m_IsInterruptable;` |
| 0x20 | `protected Lf.Ty m_RepeatType;` |
| 0x24 | `public bool m_IsActive;` |
| 0x28 | `private yH m_Preconditions;` |
| 0x30 | `private yH m_Effects;` |

Properties: `public bool CeH { get; set; }`; `public int Cei { get; }`; `public bool Cew { get; }`; `public Lf.Ty CeJ { get; }`; `public yH CeX { get; }`; `public yH CeT { get; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA6508 | 0x2ED0940 |  | `public bool get_CeH()` |
| 0x3AA6510 | 0x2ED0948 |  | `public void set_CeH(bool value)` |
| 0x3AA651C | 0x2ED094C |  | `public int get_Cei()` |
| 0x3AA6524 | 0x2ED0954 |  | `public bool get_Cew()` |
| 0x3AA652C | 0x2ED095C |  | `public Lf.Ty get_CeJ()` |
| 0x3AA6534 | 0x2ED0964 |  | `public yH get_CeX()` |
| 0x3AA653C | 0x2ED096C |  | `public yH get_CeT()` |
| 0x3AA6544 | 0x2ED0974 | 4 | `public virtual void UEZ(AIBrain e)` |
| 0x3AA6548 | 0x2ED0978 | 5 | `public virtual void UEj(AIBrain e)` |
| 0x3AA654C | 0x2ED097C | 6 | `public virtual void UEa(AIBrain e)` |
| 0x3AA657C | 0x2ED0980 | 7 | `public virtual bool UEQ(AIBrain e)` |
| 0x3AA6584 | 0x2ED0988 | 8 | `public virtual bool UEH(AIBrain e)` |
| 0x3AA658C | 0x2ED0990 | 9 | `public virtual void UEi(AIBrain e)` |
| 0x3AA6590 | 0x2ED0994 | 10 | `public virtual void UEw(AIBrain e)` |
| 0x3AA6594 | 0x2ED0998 | 11 | `public virtual bool UEJ(AIBrain e)` |
| 0x3AA659C | 0x2ED09A0 | 12 | `public virtual void UEX()` |
| 0x3AA65A0 | 0x2ED09A4 |  | `public void .ctor()` |

</details>

### public class `Attack` : Action  
`TypeDefIndex 3211`

| offset | field |
|---|---|
| 0x38 | `private float m_MinAttackDistance;` |
| 0x3C | `private float m_AttackIntervalMin;` |
| 0x40 | `private float m_AttackIntervalMax;` |
| 0x44 | `private bool m_HasKilledPlayer;` |
| 0x48 | `private GameObject m_Target;` |
| 0x50 | `private float m_NextTimeCanAttack;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA6628 | 0x2ED09AC | 4 | `public override void UEZ(AIBrain e)` |
| 0x3AA671C | 0x2ED09B0 | 7 | `public override bool UEQ(AIBrain e)` |
| 0x3AA6740 | 0x2ED09B8 | 9 | `public override void UEi(AIBrain e)` |
| 0x3AA6744 | 0x2ED09BC | 5 | `public override void UEj(AIBrain e)` |
| 0x3AA69C4 | 0x2ED09C0 | 8 | `public override bool UEH(AIBrain e)` |
| 0x3AA6B4C | 0x2ED09C8 | 11 | `public override bool UEJ(AIBrain e)` |
| 0x3AA6810 | 0x2ED09D0 |  | `private void UET(AIBrain e, Transform f, float F)` |
| 0x3AA6B80 | 0x2ED09D4 |  | `public void .ctor()` |

</details>

### public class `Chase` : Action  
`TypeDefIndex 3212`

| offset | field |
|---|---|
| 0x38 | `private SoundPlayer m_InitialScreamAudio;` |
| 0x40 | `private SoundPlayer m_ScreamingAudio;` |
| 0x48 | `private Vector2 m_ScreamInterval;` |
| 0x50 | `private Transform m_Target;` |
| 0x58 | `private float m_NextScreamTime;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA6B98 | 0x2ED09DC | 4 | `public override void UEZ(AIBrain e)` |
| 0x3AA6C9C | 0x2ED09E0 | 7 | `public override bool UEQ(AIBrain e)` |
| 0x3AA6D34 | 0x2ED09E8 | 9 | `public override void UEi(AIBrain e)` |
| 0x3AA6D38 | 0x2ECFFE8 |  | `public void UEL(AIBrain e, bool f)` |
| 0x3AA6D88 | 0x2ED09EC |  | `private void UEo(AIBrain e, Transform f, float F)` |
| 0x3AA6F3C | 0x2ED09F0 |  | `public void .ctor()` |

</details>

### public class `Eat` : Action  
`TypeDefIndex 3213`

| offset | field |
|---|---|
| 0x38 | `private float m_EatTime;` |
| 0x3C | `private bool m_IsDoneEating;` |
| 0x40 | `private float m_EatStartTime;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA6F4C | 0x2ED09F8 | 4 | `public override void UEZ(AIBrain e)` |
| 0x3AA7040 | 0x2ED09FC | 9 | `public override void UEi(AIBrain e)` |
| 0x3AA7044 | 0x2ED0A00 | 5 | `public override void UEj(AIBrain e)` |
| 0x3AA7118 | 0x2ED0A04 | 10 | `public override void UEw(AIBrain e)` |
| 0x3AA7188 | 0x2ED0A08 | 11 | `public override bool UEJ(AIBrain e)` |
| 0x3AA7190 | 0x2ED0A10 | 12 | `public override void UEX()` |
| 0x3AA719C | 0x2ED0A14 |  | `public void .ctor()` |

</details>

### public class `FindFood` : PointBased  
`TypeDefIndex 3214`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA71A0 | 0x2ED0A1C | 4 | `public override void UEZ(AIBrain e)` |
| 0x3AA735C | 0x2ED0A20 | 7 | `public override bool UEQ(AIBrain e)` |
| 0x3AA73F0 | 0x2ED0A28 |  | `public void .ctor()` |

</details>

### public class `Flee` : Action  
`TypeDefIndex 3215`

| offset | field |
|---|---|
| 0x38 | `private float m_MinFleeDistance;` |
| 0x40 | `private SoundPlayer m_ScreamAudio;` |
| 0x48 | `private float m_ScreamInterval;` |
| 0x4C | `private bool m_UpdatePosition;` |
| 0x50 | `private Vector3 m_FleePosition;` |
| 0x5C | `private float m_LastTimeScreamed;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA73F8 | 0x2ED0164 |  | `public void UEy(AIBrain e)` |
| 0x3AA7434 | 0x2ED0A38 |  | `public void .ctor()` |

</details>

### public class `Patrol` : PointBased  
`TypeDefIndex 3216`

| offset | field |
|---|---|
| 0x68 | `private Vector2 m_WaitTime;` |
| 0x70 | `private SoundPlayer m_Audio;` |
| 0x78 | `private float m_AudioPlayInterval;` |
| 0x7C | `private float m_NextMoveTime;` |
| 0x80 | `private bool m_Waiting;` |
| 0x84 | `private Nullable<Vector3> m_SuspectedTarget;` |
| 0x98 | `private AIBrain m_Brain;` |
| 0xA0 | `private float m_LastAudioPlayTime;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA7444 | 0x2ED0A40 |  | `private void UEz(Xf e)` |
| 0x3AA7508 | 0x2ED0A44 |  | `private void UEh()` |
| 0x3AA76B0 | 0x2ED0A48 |  | `public void .ctor()` |

</details>

### public class `PointBased` : Action  
`TypeDefIndex 3217`

| offset | field |
|---|---|
| 0x38 | `protected bool m_IsUrgent;` |
| 0x3C | `private Lf.Tz m_PointSequence;` |
| 0x40 | `private bool m_UsePredefinedPoints;` |
| 0x48 | `private string m_PointTag;` |
| 0x50 | `private int m_PointAmount;` |
| 0x54 | `private int m_PointMaxRadius;` |
| 0x58 | `protected int m_CurrentIndex;` |
| 0x60 | `protected List<Vector3> m_PointPositions;` |

Properties: `public List<Vector3> CeL { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AA7764 | 0x2ED0A50 |  | `public List<Vector3> get_CeL()` |
| 0x3AA72B0 | 0x2ED0A58 | 4 | `public override void UEZ(AIBrain e)` |
| 0x3AA776C | 0x2ECF5D0 |  | `public void UEm(AIBrain e)` |
| 0x3AA73A0 | 0x2ED0A5C | 7 | `public override bool UEQ(AIBrain e)` |
| 0x3AA72B4 | 0x2ED0A64 |  | `public void UER()` |
| 0x3AA73F4 | 0x2ED0A30 |  | `public void .ctor()` |

</details>
