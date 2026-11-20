# namespace `FIMSpace.FTools`  (12 types)

### public class `FAnimationClipsPack` : FContainerBase  
`TypeDefIndex 3893`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C479B4 | 0x2F7E798 | 9 | `public override void UPz(Object e)` |
| 0x3C47BFC | 0x2F7E79C |  | `public void .ctor()` |

</details>

### public abstract class `FContainerBase` : ScriptableObject  
`TypeDefIndex 3895`

| offset | field |
|---|---|
| 0x18 | `public List<FContainerBase.AssetReference> ContainedAssets;` |

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C47C88 | 0x2F7E7AC | 4 | `public virtual bool UPh(Object e)` |
| 0x3C47DDC | 0x2F7E7B4 | 5 | `public virtual void UPB(Object e)` |
| 0x3C47F4C | 0x2F7E7B8 | 6 | `public virtual void UPm(Object e)` |
| 0x3C47FDC | 0x2F7E7BC | 7 | `public virtual void UPR(Object e, string f = ".asset")` |
| 0x3C48038 | 0x2F7E7C0 | 8 | `public virtual void UPb(Object e)` |
| 0x3C481E0 | 0x2F7E7C4 |  | `public FContainerBase.AssetReference UPl(Object e)` |
| 0x3C47B34 | 0x2F7E7CC | 9 | `public virtual void UPz(Object e)` |
| 0x3C4837C | 0x2F7E7D0 | 10 | `public virtual void UPx(Object e)` |
| 0x3C483DC | 0x2F7E7D4 | 11 | `public virtual void UPK()` |
| 0x3C483E4 | 0x2F7E7D8 |  | `public void UPG()` |
| 0x3C48378 | 0x2F7E7DC |  | `public static void UPP(ScriptableObject e, Object f)` |
| 0x3C483E0 | 0x2F7E7E0 |  | `public static void UPD(FContainerBase e)` |
| 0x3C483D8 | 0x2F7E7E4 |  | `public static void UPn(FContainerBase e, Object f)` |
| 0x3C47C00 | 0x2F7E7A4 |  | `protected void .ctor()` |

</details>

### public class `FIK_CCDProcessor` : FIK_ProcessorBase  
`TypeDefIndex 3897`

| offset | field |
|---|---|
| 0x70 | `public FIK_CCDProcessor.CCDIKBone[] IKBones;` |
| 0x78 | `public bool ContinousSolving;` |
| 0x7C | `public float SyncWithAnimator;` |
| 0x80 | `public int ReactionQuality;` |
| 0x84 | `public float Smoothing;` |
| 0x88 | `public float StretchToTarget;` |
| 0x90 | `public AnimationCurve StretchCurve;` |
| 0x98 | `public bool Use2D;` |
| 0x99 | `public bool Invert;` |

Properties: `public FIK_CCDProcessor.CCDIKBone CcG { get; }`; `public FIK_CCDProcessor.CCDIKBone CcP { get; }`; `public float toi { get; set; }`

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C5201C | 0x2F7E7F0 |  | `public FIK_CCDProcessor.CCDIKBone get_CcG()` |
| 0x3C52044 | 0x2F7E7F8 |  | `public FIK_CCDProcessor.CCDIKBone get_CcP()` |
| 0x3C52078 | 0x2F7E800 |  | `public float get_toi()` |
| 0x3C52080 | 0x2F7E808 |  | `private void set_toi(float value)` |
| 0x3C52088 | 0x2F7E80C |  | `public void .ctor(Transform[] bonesChain)` |
| 0x3C52338 | 0x2F7E81C | 4 | `public override void Unh(Transform e)` |
| 0x3C52608 | 0x2F7E820 | 6 | `public override void Update()` |
| 0x3C536F0 | 0x2F7E824 |  | `protected Vector3 Ugc()` |
| 0x3C53CB8 | 0x2F7E834 |  | `private bool UgU()` |
| 0x3C5399C | 0x2F7E83C |  | `private Vector3 UgY()` |
| 0x3C5396C | 0x2F7E84C |  | `private float UgW()` |
| 0x3C53F34 | 0x2F7E854 |  | `public void UgE(float e = 60, float f = 50)` |
| 0x3C54010 | 0x2F7E858 |  | `public void UgA(float e = 1)` |
| 0x3C540B8 | 0x2F7E85C |  | `public void Ugu(AnimationCurve e)` |

</details>

### public abstract class `FIK_IKBoneBase`  
`TypeDefIndex 3898`

| offset | field |
|---|---|
| 0x20 | `public float sqrMagn;` |
| 0x24 | `public float BoneLength;` |
| 0x28 | `public float MotionWeight;` |
| 0x2C | `public Vector3 InitialLocalPosition;` |
| 0x38 | `public Quaternion InitialLocalRotation;` |
| 0x48 | `public Quaternion LastKeyLocalRotation;` |

Properties: `public FIK_IKBoneBase tof { get; set; }`; `public Transform toF { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C4C754 | 0x2F7E8D0 |  | `public FIK_IKBoneBase get_tof()` |
| 0x3C4C75C | 0x2F7E8D8 |  | `private void set_tof(FIK_IKBoneBase value)` |
| 0x3C4C764 | 0x2F7E8DC |  | `public Transform get_toF()` |
| 0x3C4C76C | 0x2F7E8E4 |  | `protected void set_toF(Transform value)` |
| 0x3C4C774 | 0x2F7E880 |  | `public void .ctor(Transform t)` |
| 0x3C4C868 | 0x2F7E8E8 | 4 | `public virtual void Unx(FIK_IKBoneBase e)` |

</details>

### public class `FIK_IKProcessor` : FIK_ProcessorBase  
`TypeDefIndex 3901`

| offset | field |
|---|---|
| 0x70 | `private FIK_IKProcessor.IKBone[] IKBones;` |
| 0x78 | `public float PositionWeight;` |
| 0x7C | `public float RotationWeight;` |
| 0x80 | `public bool UseEnsuredRotation;` |
| 0x84 | `public FIK_IKProcessor.xO AutoHintMode;` |
| 0x88 | `public float ManualHintPositionWeight;` |
| 0x8C | `public Vector3 IKManualHintPosition;` |
| 0xA0 | `private Transform toY;` |
| 0xA8 | `private bool toW;` |
| 0xAC | `private Vector3 toE;` |
| 0xB8 | `private Quaternion toA;` |
| 0xC8 | `private Quaternion tou;` |
| 0xD8 | `private Quaternion tok;` |
| 0xE8 | `private Quaternion toO;` |
| 0xF8 | `private Quaternion tot;` |
| 0x108 | `private float tor;` |
| 0x10C | `private float toN;` |
| 0x110 | `private float toq;` |
| 0x114 | `public bool AllowEditModeInit;` |

Properties: `public FIK_IKProcessor.IKBone CcB { get; }`; `public FIK_IKProcessor.IKBone Ccm { get; }`; `public FIK_IKProcessor.IKBone CcR { get; }`; `public int Ccb { get; }`; `public float toU { get; set; }`

<details><summary>methods (25)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C4C944 | 0x2F7E8EC |  | `public FIK_IKProcessor.IKBone get_CcB()` |
| 0x3C4C96C | 0x2F7E8F4 |  | `public FIK_IKProcessor.IKBone get_Ccm()` |
| 0x3C4C998 | 0x2F7E8FC |  | `public FIK_IKProcessor.IKBone get_CcR()` |
| 0x3C4C9F4 | 0x2F7E904 |  | `public int get_Ccb()` |
| 0x3C4CA10 | 0x2F7E90C |  | `public float get_toU()` |
| 0x3C4CA18 | 0x2F7E914 |  | `protected void set_toU(float value)` |
| 0x3C4C9C4 | 0x2F7E918 |  | `public FIK_IKProcessor.IKBone UnS(int e)` |
| 0x3C4CA20 | 0x2F7E920 |  | `public void .ctor(Transform startBone, Transform midBone, Transform endBone)` |
| 0x3C4CB70 | 0x2F7E928 |  | `public void UVf(Transform e, Transform f, Transform F)` |
| 0x3C4CED8 | 0x2F7E92C |  | `public void UVF(Transform e, Transform f)` |
| 0x3C4CF1C | 0x2F7E930 | 5 | `public override void UnB()` |
| 0x3C4CF34 | 0x2F7E934 |  | `public void UVd()` |
| 0x3C4D014 | 0x2F7E938 | 4 | `public override void Unh(Transform e)` |
| 0x3C4D914 | 0x2F7E93C |  | `public void UVc()` |
| 0x3C4D994 | 0x2F7E940 | 6 | `public override void Update()` |
| 0x3C4E5A4 | 0x2F7E944 |  | `public float UVU()` |
| 0x3C4E6BC | 0x2F7E94C |  | `public Vector3 UVY()` |
| 0x3C4E754 | 0x2F7E95C |  | `public float UVW(Vector3 e)` |
| 0x3C4E80C | 0x2F7E964 |  | `public float UVE(float e)` |
| 0x3C4E1E8 | 0x2F7E96C |  | `private Vector3 UVA()` |
| 0x3C4E82C | 0x2F7E97C |  | `public Vector3 UVu(Vector3 e)` |
| 0x3C4D790 | 0x2F7E98C |  | `public void UVk()` |
| 0x3C4E33C | 0x2F7E990 |  | `private Vector3 UVO(Vector3 e, Vector3 f)` |
| 0x3C4E924 | 0x2F7E9A0 |  | `private Vector3 UVt()` |
| 0x3C4ED50 | 0x2F7E9B0 |  | `public void UVr()` |

</details>

### public abstract class `FIK_ProcessorBase`  
`TypeDefIndex 3902`

| offset | field |
|---|---|
| 0x10 | `public float IKWeight;` |
| 0x14 | `public Vector3 IKTargetPosition;` |
| 0x20 | `public Quaternion IKTargetRotation;` |
| 0x30 | `public Vector3 LastLocalDirection;` |
| 0x3C | `public Vector3 LocalDirection;` |
| 0x68 | `public bool CallPreCalibrate;` |

Properties: `public float tLS { get; set; }`; `public bool tLI { get; set; }`; `public FIK_IKBoneBase[] tLM { get; set; }`; `public FIK_IKBoneBase Ccz { get; }`; `public FIK_IKBoneBase Cch { get; }`; `public Quaternion toe { get; set; }`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C4C534 | 0x2F7EA00 |  | `public float get_tLS()` |
| 0x3C4C53C | 0x2F7EA08 |  | `protected void set_tLS(float value)` |
| 0x3C4C544 | 0x2F7EA0C |  | `public bool get_tLI()` |
| 0x3C4C54C | 0x2F7EA14 |  | `protected void set_tLI(bool value)` |
| 0x3C4C558 | 0x2F7EA18 |  | `public FIK_IKBoneBase[] get_tLM()` |
| 0x3C4C560 | 0x2F7EA20 |  | `protected void set_tLM(FIK_IKBoneBase[] value)` |
| 0x3C4C568 | 0x2F7EA24 |  | `public FIK_IKBoneBase get_Ccz()` |
| 0x3C4C590 | 0x2F7EA2C |  | `public FIK_IKBoneBase get_Cch()` |
| 0x3C4C5C4 | 0x2F7EA34 |  | `public Quaternion get_toe()` |
| 0x3C4C5D0 | 0x2F7EA48 |  | `public void set_toe(Quaternion value)` |
| 0x3C4C5DC | 0x2F7EA4C | 4 | `public virtual void Unh(Transform e)` |
| 0x3C4C62C | 0x2F7EA50 | 5 | `public virtual void UnB()` |
| 0x3C4C680 | 0x2F7EA54 | 6 | `public virtual void Update()` |
| 0x3C4C684 | 0x2F7EA58 |  | `public static float EaseInOutQuint(float start, float end, float value)` |
| 0x3C4C6EC | 0x2F7E814 |  | `protected void .ctor()` |

</details>

### public class `FimpIK_Arm`  
`TypeDefIndex 3905`

| offset | field |
|---|---|
| 0x10 | `private Vector3 tLX;` |
| 0x1C | `private Quaternion tLT;` |
| 0x2C | `public Vector3 IKTargetPosition;` |
| 0x38 | `public Quaternion IKTargetRotation;` |
| 0x50 | `private float tLy;` |
| 0x54 | `private Vector3 tLz;` |
| 0x70 | `public Vector3 HandMiddleOffset;` |
| 0x7C | `private Vector3 tLB;` |
| 0x88 | `private xQ tLm;` |
| 0x90 | `private Vector3 tLR;` |
| 0x9C | `internal bool tLb;` |
| 0xA0 | `public float MaxStretching;` |
| 0xC0 | `public FimpIK_Arm.IKBone ChestIKBone;` |
| 0xC8 | `private bool tLn;` |
| 0xCC | `public float ManualHintPositionWeight;` |
| 0xD0 | `public Vector3 IKManualHintPosition;` |
| 0xDC | `private float tLV;` |
| 0xE0 | `private float tLg;` |
| 0xE4 | `public float _internalIKWeight;` |
| 0xE8 | `public float IKWeight;` |
| 0xEC | `public float IKPositionWeight;` |
| 0xF0 | `public float HandRotationWeight;` |
| 0xF4 | `public float ShoulderBlend;` |
| 0xF8 | `public FimpIK_Arm.xk AutoHintMode;` |
| 0xFC | `public bool MirrorMaths;` |
| 0x100 | `public Transform ShoulderTransform;` |
| 0x108 | `public Transform UpperarmTransform;` |
| 0x110 | `public Transform LowerarmTransform;` |
| 0x118 | `public Transform HandTransform;` |
| 0x120 | `private FimpIK_Arm.IKBone[] IKBones;` |
| 0x144 | `public Vector3 ikCustomHintOffset;` |

Properties: `public float tLL { get; set; }`; `public bool tLo { get; set; }`; `public Quaternion tLh { get; set; }`; `public float tLl { get; set; }`; `public bool tLx { get; set; }`; `public float tLK { get; set; }`; `public float tLG { get; set; }`; `public float tLP { get; set; }`; `public Transform tLD { get; set; }`; `public FimpIK_Arm.IKBone CcJ { get; }`; `public FimpIK_Arm.IKBone CcX { get; }`; `public FimpIK_Arm.IKBone CcT { get; }`; `public FimpIK_Arm.IKBone CcL { get; }`; `public int Cco { get; }`; `public bool Ccy { get; }`; `public Vector3 tLp { get; set; }`; `public Quaternion tLv { get; set; }`

<details><summary>methods (61)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C483E8 | 0x2F7EA60 |  | `public float get_tLL()` |
| 0x3C483F0 | 0x2F7EA68 |  | `protected void set_tLL(float value)` |
| 0x3C483F8 | 0x2F7EA6C |  | `public bool get_tLo()` |
| 0x3C48400 | 0x2F7EA74 |  | `public void set_tLo(bool value)` |
| 0x3C4873C | 0x2F7EA78 |  | `public Quaternion get_tLh()` |
| 0x3C48748 | 0x2F7EA8C |  | `protected void set_tLh(Quaternion value)` |
| 0x3C49098 | 0x2F7EA90 |  | `public float get_tLl()` |
| 0x3C490A0 | 0x2F7EA98 |  | `protected void set_tLl(float value)` |
| 0x3C494D4 | 0x2F7EA9C |  | `public bool get_tLx()` |
| 0x3C494DC | 0x2F7EAA4 |  | `public void set_tLx(bool value)` |
| 0x3C494E8 | 0x2F7EAA8 |  | `public float get_tLK()` |
| 0x3C494F0 | 0x2F7EAB0 |  | `public void set_tLK(float value)` |
| 0x3C494F8 | 0x2F7EAB4 |  | `public float get_tLG()` |
| 0x3C49500 | 0x2F7EABC |  | `public void set_tLG(float value)` |
| 0x3C49508 | 0x2F7EAC0 |  | `public float get_tLP()` |
| 0x3C49510 | 0x2F7EAC8 |  | `private void set_tLP(float value)` |
| 0x3C499CC | 0x2F7EACC |  | `public Transform get_tLD()` |
| 0x3C499D4 | 0x2F7EAD4 |  | `protected void set_tLD(Transform value)` |
| 0x3C48DE4 | 0x2F7EAD8 |  | `public FimpIK_Arm.IKBone get_CcJ()` |
| 0x3C48710 | 0x2F7EAE0 |  | `public FimpIK_Arm.IKBone get_CcX()` |
| 0x3C486E4 | 0x2F7EAE8 |  | `public FimpIK_Arm.IKBone get_CcT()` |
| 0x3C48DB8 | 0x2F7EAF0 |  | `public FimpIK_Arm.IKBone get_CcL()` |
| 0x3C49A0C | 0x2F7EAF8 |  | `public int get_Cco()` |
| 0x3C4B244 | 0x2F7EB00 |  | `public bool get_Ccy()` |
| 0x3C4B5D4 | 0x2F7EB08 |  | `public Vector3 get_tLp()` |
| 0x3C4B5E4 | 0x2F7EB18 |  | `private void set_tLp(Vector3 value)` |
| 0x3C4B5F4 | 0x2F7EB1C |  | `public Quaternion get_tLv()` |
| 0x3C4B608 | 0x2F7EB30 |  | `public void set_tLv(Quaternion value)` |
| 0x3C4840C | 0x2F7EB34 |  | `public void UDj(float e = 1)` |
| 0x3C485A8 | 0x2F7EB38 |  | `public void UDa(float e, float f, float F, float d = 1000)` |
| 0x3C485D8 | 0x2F7EB3C |  | `public void UDQ(Vector3 e, float f, float F, float d = 1000)` |
| 0x3C48628 | 0x2F7EB40 |  | `public Vector3 UDH()` |
| 0x3C48754 | 0x2F7EB50 |  | `public void UDJ(Quaternion e)` |
| 0x3C48760 | 0x2F7EB54 | 4 | `public virtual void UDX(Transform e)` |
| 0x3C48E0C | 0x2F7EB58 |  | `public void UDT(Quaternion e, float f = 1, bool F = false)` |
| 0x3C49044 | 0x2F7EB5C |  | `public void UDL()` |
| 0x3C490A8 | 0x2F7EB60 |  | `public void UDz()` |
| 0x3C484C8 | 0x2F7EB64 |  | `public void UDh()` |
| 0x3C49188 | 0x2F7EB68 |  | `public float UDB(Vector3 e)` |
| 0x3C49250 | 0x2F7EB70 |  | `public float UDm(Vector3 e)` |
| 0x3C49304 | 0x2F7EB78 | 5 | `protected virtual void UDR()` |
| 0x3C49518 | 0x2F7EB7C |  | `private void UDg(Vector3 e)` |
| 0x3C499DC | 0x2F7EB80 |  | `public FimpIK_Arm.IKBone Unf(int e)` |
| 0x3C49A28 | 0x2F7EB88 |  | `public void Und(Transform e)` |
| 0x3C4A17C | 0x2F7EB8C |  | `public void Unc(Transform e, Transform f, Transform F, Transform d)` |
| 0x3C4A70C | 0x2F7EB90 |  | `public void UnU()` |
| 0x3C4A718 | 0x2F7EB94 | 6 | `protected virtual void Refresh()` |
| 0x3C4A838 | 0x2F7EB98 | 7 | `protected virtual void UnY()` |
| 0x3C4A7D0 | 0x2F7EB9C |  | `public void UnW()` |
| 0x3C4A8F4 | 0x2F7EBA0 |  | `private Vector3 UnE()` |
| 0x3C4AA48 | 0x2F7EBB0 |  | `public Vector3 UnA(Vector3 e)` |
| 0x3C4A584 | 0x2F7EBC0 |  | `public void Unu()` |
| 0x3C4B064 | 0x2F7EBC4 |  | `private Vector3 Unk(Vector3 e, Vector3 f)` |
| 0x3C4B20C | 0x2F7EBD4 |  | `public void UnO(float e, float f, float F)` |
| 0x3C4B318 | 0x2F7EBD8 |  | `public void Unr(float e, float f, float F)` |
| 0x3C4B350 | 0x2F7EBDC |  | `public Vector3 UnN(Vector3 e)` |
| 0x3C4B430 | 0x2F7EBEC |  | `public Vector3 Unq(Vector3 e, float f = 1)` |
| 0x3C4B61C | 0x2F7EBFC |  | `public void Update()` |
| 0x3C4AB40 | 0x2F7EC00 |  | `private Vector3 Una()` |
| 0x3C4BC7C | 0x2F7EC10 |  | `public void UnQ()` |
| 0x3C4BC80 | 0x2F7EC14 |  | `public void .ctor()` |

</details>

### public class `FimpIK_Limb` : FIK_ProcessorBase  
`TypeDefIndex 3908`

| offset | field |
|---|---|
| 0x80 | `public float FeetStretchWeight;` |
| 0x84 | `public float FeetStretchSensitivity;` |
| 0x88 | `public float FeetStretchLimit;` |
| 0x8C | `public float FeetFadeQuicker;` |
| 0x90 | `public bool disableFeet;` |
| 0x94 | `private float toz;` |
| 0x98 | `private float toh;` |
| 0x9C | `private Vector3 toB;` |
| 0xB8 | `public Animator HumanoidAnimator;` |
| 0xC0 | `public bool IsRight;` |
| 0xC1 | `private bool tob;` |
| 0xC2 | `private bool tol;` |
| 0xC3 | `private bool tox;` |
| 0xC4 | `public float ManualHintPositionWeight;` |
| 0xC8 | `public Vector3 IKManualHintPosition;` |
| 0xD4 | `public bool UseEndBoneMapping;` |
| 0xD8 | `private float toK;` |
| 0xE0 | `private FimpIK_Limb.IKBone[] toG;` |
| 0xE8 | `public float IKPositionWeight;` |
| 0xEC | `public float FootRotationWeight;` |
| 0xF0 | `public FimpIK_Limb.xr AutoHintMode;` |
| 0xF4 | `protected Vector3 toP;` |
| 0x100 | `protected Quaternion toD;` |
| 0x110 | `protected Quaternion ton;` |
| 0x120 | `public Vector3 ExtraHintAdjustementOffset;` |
| 0x12C | `public bool InverseHint;` |

Properties: `public Quaternion too { get; set; }`; `public FimpIK_Limb.IKBone CcD { get; }`; `public float toy { get; set; }`; `public Transform tom { get; set; }`; `public FimpIK_Limb.IKBone Ccn { get; }`; `public FimpIK_Limb.IKBone CcV { get; }`; `public FimpIK_Limb.IKBone Ccg { get; }`; `public FimpIK_Limb.IKBone toR { get; set; }`; `public int Ccp { get; }`

<details><summary>methods (39)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C54908 | 0x2F7ED0C |  | `public Quaternion get_too()` |
| 0x3C54914 | 0x2F7ED20 |  | `protected void set_too(Quaternion value)` |
| 0x3C54920 | 0x2F7ED24 |  | `public FimpIK_Limb.IKBone get_CcD()` |
| 0x3C54B68 | 0x2F7ED2C |  | `public float get_toy()` |
| 0x3C54B70 | 0x2F7ED34 |  | `protected void set_toy(float value)` |
| 0x3C560D0 | 0x2F7ED38 |  | `public Transform get_tom()` |
| 0x3C560D8 | 0x2F7ED40 |  | `protected void set_tom(Transform value)` |
| 0x3C54C58 | 0x2F7ED44 |  | `public FimpIK_Limb.IKBone get_Ccn()` |
| 0x3C54C80 | 0x2F7ED4C |  | `public FimpIK_Limb.IKBone get_CcV()` |
| 0x3C54B3C | 0x2F7ED54 |  | `public FimpIK_Limb.IKBone get_Ccg()` |
| 0x3C560E0 | 0x2F7ED5C |  | `public FimpIK_Limb.IKBone get_toR()` |
| 0x3C560E8 | 0x2F7ED64 |  | `private void set_toR(FimpIK_Limb.IKBone value)` |
| 0x3C56120 | 0x2F7ED68 |  | `public int get_Ccp()` |
| 0x3C5494C | 0x2F7ED70 | 7 | `public virtual void Ugo(Transform e)` |
| 0x3C54B78 | 0x2F7ED74 |  | `public void Ugh()` |
| 0x3C54CAC | 0x2F7ED78 |  | `public void UgB()` |
| 0x3C54D8C | 0x2F7ED7C |  | `private float Ugm()` |
| 0x3C54F80 | 0x2F7ED84 |  | `public float UgR(Vector3 e)` |
| 0x3C5504C | 0x2F7ED8C |  | `public Vector3 Ugb(Vector3 e, float f)` |
| 0x3C551C8 | 0x2F7ED9C |  | `public void Ugl(float e, float f = 2)` |
| 0x3C55D9C | 0x2F7EDA0 |  | `private void Ugx()` |
| 0x3C55994 | 0x2F7EDA4 |  | `internal void UgK(float e, float f = 1)` |
| 0x3C560F0 | 0x2F7EDA8 |  | `public FimpIK_Limb.IKBone Ugv(int e)` |
| 0x3C5613C | 0x2F7EDB0 | 4 | `public override void Unh(Transform e)` |
| 0x3C568C4 | 0x2F7EDB4 |  | `public void UgI(Transform e, Transform f, Transform F)` |
| 0x3C56C04 | 0x2F7EDB8 |  | `public void UgM(Transform e, Transform f, Transform F, Transform d)` |
| 0x3C57020 | 0x2F7EDBC |  | `public void Upe(Transform e, Transform f)` |
| 0x3C57064 | 0x2F7EDC0 | 8 | `protected virtual void Refresh()` |
| 0x3C573C0 | 0x2F7EDC4 | 9 | `protected virtual void Upf()` |
| 0x3C575BC | 0x2F7EDC8 | 5 | `public override void UnB()` |
| 0x3C570D0 | 0x2F7EDCC |  | `public void UpF()` |
| 0x3C57618 | 0x2F7EDD0 |  | `protected Vector3 Upd()` |
| 0x3C5776C | 0x2F7EDE0 |  | `public Vector3 Upc(Vector3 e)` |
| 0x3C5673C | 0x2F7EDF0 |  | `public void UpU()` |
| 0x3C57FBC | 0x2F7EDF4 |  | `protected Vector3 UpY(Vector3 e, Vector3 f)` |
| 0x3C58164 | 0x2F7EE04 | 6 | `public override void Update()` |
| 0x3C57864 | 0x2F7EE08 |  | `private Vector3 UpW()` |
| 0x3C58914 | 0x2F7EE18 |  | `public void UpE()` |
| 0x3C58918 | 0x2F7EE1C |  | `public void .ctor()` |

</details>

### public class `FMuscle_Eulers`  
`TypeDefIndex 3910`

| offset | field |
|---|---|
| 0x10 | `public Vector3 DesiredEulerAngles;` |
| 0x28 | `private xC tyP;` |
| 0x30 | `private xC tyD;` |
| 0x38 | `private xC tyn;` |
| 0x40 | `public float Acceleration;` |
| - | `public float AccelerationLimit;` |
| 0x48 | `public float Damping;` |
| 0x4C | `public float BrakePower;` |

Properties: `public Vector3 tyG { get; set; }`; `public Quaternion CUd { get; }`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C5C190 | 0x2F7EED8 |  | `public Vector3 get_tyG()` |
| 0x3C5C19C | 0x2F7EEE8 |  | `private void set_tyG(Vector3 value)` |
| 0x3C5C1A8 | 0x2F7EEEC |  | `public Quaternion get_CUd()` |
| 0x3C5C1CC | 0x2F7EF00 |  | `public void Uvw(Vector3 e)` |
| 0x3C5C2F0 | 0x2F7EF04 |  | `public void UvJ(Quaternion e)` |
| 0x3C5C328 | 0x2F7EF08 |  | `public bool UvX()` |
| 0x3C5C37C | 0x2F7EF10 |  | `public void UvT(Vector3 e)` |
| 0x3C5C3C8 | 0x2F7EF14 |  | `public void UvL(float e)` |
| 0x3C5C414 | 0x2F7EF18 |  | `public void Uvo(Vector3 e, float f)` |
| 0x3C5C46C | 0x2F7EF1C |  | `public void Update(float delta, Vector3 desired, float acceleration, float accelerationLimit, float damping, float brakePower)` |
| 0x3C5C55C | 0x2F7EF20 |  | `public Vector3 Update(float delta, Vector3 desired)` |
| 0x3C5C614 | 0x2F7EF30 |  | `public void Update(float delta, Quaternion desired)` |
| - | 0x2F7EF34 |  | `public IEnumerator Uvy(Vector3 e, float f, bool F = false, float d = 0)` |
| 0x3C5C764 | 0x2F7EF3C |  | `public static void Uvz(ref FMuscle_Eulers e, FMuscle_Eulers f, FMuscle_Eulers F, float d)` |
| 0x3C5C790 | 0x2F7EF40 |  | `public void .ctor()` |

</details>

### public class `FMuscle_Quaternion`  
`TypeDefIndex 3912`

| offset | field |
|---|---|
| 0x10 | `public Quaternion DesiredRotation;` |
| 0x30 | `private xs tyL;` |
| 0x38 | `private xs tyo;` |
| 0x40 | `private xs tyy;` |
| 0x48 | `private xs tyz;` |
| 0x50 | `public float Acceleration;` |
| 0x54 | `public float AccelerationLimit;` |
| 0x58 | `public float Damping;` |
| 0x5C | `public float BrakePower;` |

Properties: `public Quaternion tyT { get; set; }`; `public bool CUe { get; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C5B70C | 0x2F7EF70 |  | `public Quaternion get_tyT()` |
| 0x3C5B718 | 0x2F7EF84 |  | `private void set_tyT(Quaternion value)` |
| 0x3C5B724 | 0x2F7EF88 |  | `public bool get_CUe()` |
| 0x3C5B734 | 0x2F7EF90 |  | `public void UvE(Quaternion e)` |
| 0x3C5B8A0 | 0x2F7EF94 |  | `public bool UvA()` |
| 0x3C5B908 | 0x2F7EF9C |  | `public void Uvu(Quaternion e)` |
| 0x3C5B968 | 0x2F7EFA0 |  | `public void Uvk(float e)` |
| 0x3C5B9C8 | 0x2F7EFA4 |  | `public void UvO(Quaternion e, float f)` |
| 0x3C5BA38 | 0x2F7EFA8 |  | `public void Update(float delta, Quaternion desired, float acceleration, float accelerationLimit, float damping, float brakePower)` |
| 0x3C5BB60 | 0x2F7EFAC |  | `public void Update(float delta, Quaternion desired)` |
| 0x3C5BC48 | 0x2F7EFB0 |  | `public void Uvt(float e, Quaternion f)` |
| 0x3C5BCAC | 0x2F7EFB4 |  | `public static Quaternion Uvr(Quaternion e, Quaternion f)` |
| 0x3C5BE40 | 0x2F7EFC8 |  | `public IEnumerator UvN(Quaternion e, float f, bool F = false, float d = 0)` |
| 0x3C5BF28 | 0x2F7EFD0 |  | `public static void Uvq(ref FMuscle_Quaternion e, FMuscle_Quaternion f, FMuscle_Quaternion F, float d)` |
| 0x3C5BF54 | 0x2F7EFD4 |  | `public void Uvs(Quaternion e)` |
| 0x3C5BFA4 | 0x2F7EFD8 |  | `public void .ctor()` |

</details>

### public class `FMuscle_Vector3`  
`TypeDefIndex 3914`

| offset | field |
|---|---|
| 0x10 | `public Vector3 DesiredPosition;` |
| 0x30 | `private xs tys;` |
| 0x38 | `private xs tyC;` |
| 0x40 | `private xs tyZ;` |
| 0x48 | `public float Acceleration;` |
| 0x4C | `public float AccelerationLimit;` |
| 0x50 | `public float Damping;` |
| 0x54 | `public float BrakePower;` |

Properties: `public Vector3 tyN { get; set; }`; `public bool tyq { get; set; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C5B1C8 | 0x2F7F008 |  | `public Vector3 get_tyN()` |
| 0x3C5B1D4 | 0x2F7F018 |  | `private void set_tyN(Vector3 value)` |
| 0x3C5B1E0 | 0x2F7F01C |  | `public bool get_tyq()` |
| 0x3C5B1E8 | 0x2F7F024 |  | `private void set_tyq(bool value)` |
| 0x3C5A594 | 0x2F7F028 |  | `public void UpV(Vector3 e)` |
| 0x3C5B1F4 | 0x2F7F02C |  | `public bool Upg()` |
| 0x3C5B248 | 0x2F7F034 |  | `public void Upp(Vector3 e)` |
| 0x3C5B294 | 0x2F7F038 |  | `public void Reset(Vector3 value)` |
| 0x3C5B2E0 | 0x2F7F03C |  | `public void Upv(float e)` |
| 0x3C58C40 | 0x2F7F040 |  | `public void UpS(Vector3 e)` |
| 0x3C5B32C | 0x2F7F044 |  | `public void Update(float delta, Vector3 desired, float acceleration, float accelerationLimit, float damping, float brakePower)` |
| 0x3C59B14 | 0x2F7F048 |  | `public Vector3 Update(float delta, Vector3 desired)` |
| 0x3C5B41C | 0x2F7F058 |  | `public IEnumerator UpI(Vector3 e, float f, bool F = false, float d = 0)` |
| 0x3C5B4FC | 0x2F7F060 |  | `public static void UpM(ref FMuscle_Vector3 e, FMuscle_Vector3 f, FMuscle_Vector3 F, float d)` |
| 0x3C58B80 | 0x2F7F064 |  | `public void Uve(Vector3 e)` |
| 0x3C5A580 | 0x2F7F068 |  | `public void .ctor()` |

</details>

### public class `FTools_IKProcessorek`  
`TypeDefIndex 3917`

| offset | field |
|---|---|
| 0x10 | `public Vector3 IKTargetPosition;` |
| 0x1C | `public Quaternion IKTargetRotation;` |
| 0x2C | `public Vector3 IKElbowTargetPosition;` |
| 0x38 | `public FTools_IKProcessorek.FTools_IKProcessorBone[] IKBones;` |
| 0x40 | `public bool Initialized;` |
| 0x44 | `public float IKWeight;` |
| 0x48 | `public Vector3 targetElbowNormal;` |
| 0x54 | `public bool LHand;` |
| 0x58 | `public FTools_IKProcessorek.xt ElbowMode;` |
| 0x5C | `public Quaternion frameEndBoneRotation;` |
| 0x6C | `private float toC;` |
| 0x70 | `public int CCD_ReactionQuality;` |
| 0x74 | `public float CCD_Smoothing;` |
| 0x78 | `public float CCD_LimitAngle;` |
| 0x7C | `public bool AutoWeight;` |
| 0x80 | `public Vector3 LastLocalDirection;` |
| 0x8C | `public Vector3 LocalDirection;` |
| 0x98 | `private Quaternion toZ;` |
| 0xA8 | `private bool toj;` |
| 0xAC | `public float weight;` |
| 0xB0 | `private Quaternion toa;` |

Properties: `public bool tos { get; set; }`; `public FTools_IKProcessorek.FTools_IKProcessorBone Ccl { get; }`; `public FTools_IKProcessorek.FTools_IKProcessorBone Ccx { get; }`; `public FTools_IKProcessorek.FTools_IKProcessorBone CcK { get; }`

<details><summary>methods (22)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C4EDFC | 0x2F7F098 |  | `public bool get_tos()` |
| 0x3C4EE04 | 0x2F7F0A0 |  | `private void set_tos(bool value)` |
| 0x3C4EE10 | 0x2F7F0A4 |  | `public FTools_IKProcessorek.FTools_IKProcessorBone get_Ccl()` |
| 0x3C4EE38 | 0x2F7F0AC |  | `public FTools_IKProcessorek.FTools_IKProcessorBone get_Ccx()` |
| 0x3C4EE64 | 0x2F7F0B4 |  | `public FTools_IKProcessorek.FTools_IKProcessorBone get_CcK()` |
| 0x3C4EEB0 | 0x2F7F0BC |  | `public void UVT(Transform e, Transform f, Transform F)` |
| 0x3C4F108 | 0x2F7F0C0 |  | `public void UVL(Transform[] e)` |
| 0x3C4F290 | 0x2F7F0C4 |  | `public void UVo(Transform e)` |
| 0x3C4FC2C | 0x2F7F0C8 |  | `public void Update()` |
| 0x3C50058 | 0x2F7F0CC |  | `public void UVy()` |
| 0x3C50614 | 0x2F7F0D0 |  | `public float UVz(Vector3 e)` |
| 0x3C5037C | 0x2F7F0D8 |  | `private Vector3 UVh()` |
| 0x3C50A08 | 0x2F7F0E8 |  | `public Vector3 UVB(Vector3 e)` |
| 0x3C4FAA8 | 0x2F7F0F8 |  | `public void UVm()` |
| 0x3C503A8 | 0x2F7F0FC |  | `private Vector3 UVR(Vector3 e, Vector3 f)` |
| 0x3C50B00 | 0x2F7F10C |  | `private Vector3 UVb()` |
| 0x3C4FC3C | 0x2F7F11C |  | `public void UVl()` |
| 0x3C50E98 | 0x2F7F120 |  | `protected Vector3 UVx()` |
| 0x3C514B4 | 0x2F7F130 |  | `private bool UVK()` |
| 0x3C5115C | 0x2F7F138 |  | `private Vector3 UVG()` |
| 0x3C5112C | 0x2F7F148 |  | `private float UVP()` |
| 0x3C51730 | 0x2F7F150 |  | `public void .ctor()` |

</details>
