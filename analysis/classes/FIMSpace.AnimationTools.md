# namespace `FIMSpace.AnimationTools`  (1 types)

### public class `LegAnimationClipMotion`  
`TypeDefIndex 3922`

| offset | field |
|---|---|
| 0x10 | `public bool analyzed;` |
| 0x18 | `public AnimationClip targetClip;` |
| 0x20 | `public List<LegAnimationClipMotion.MotionSample> sampledData;` |
| 0x28 | `public Vector3 LowestFootCoords;` |
| 0x34 | `public Vector3 HighestFootCoords;` |
| 0x40 | `public Vector3 FootCoordsDiffs;` |
| 0x4C | `public Vector3 startStepFootLocal;` |
| 0x58 | `public int startStepFootLocalIndex;` |
| 0x5C | `public float startStepFootProgress;` |
| 0x60 | `public Vector3 endStepFootLocal;` |
| 0x6C | `public int endStepFootLocalIndex;` |
| 0x70 | `public float endStepFootProgress;` |
| 0x74 | `public Vector3 approximateFootPushDirection;` |
| 0x80 | `public Vector3 approximateFootPushDirectionDominant;` |
| 0x8C | `public float approximateFootLocalXPosDuringPush;` |
| 0x90 | `public float approximateFootLocalZPosDuringPush;` |
| 0x94 | `public Vector3 _footForward;` |
| 0xA0 | `public Vector3 _footToToes;` |
| 0xAC | `public Vector3 _footToToesForw;` |
| 0xB8 | `public Vector3 _footLocalToGround;` |
| 0xC4 | `public float _latestToesTesh;` |
| 0xC8 | `public float _latestHeelTesh;` |
| 0xCC | `public float _latestHoldOnGround;` |
| 0xD0 | `public float _latestFloorOffset;` |
| 0xD4 | `public LegAnimationClipMotion.xW _latestAnalyzeMode;` |
| 0xD8 | `public float _groundToFootHeight;` |
| 0xDC | `public Quaternion _initFootRot;` |
| 0xEC | `public Quaternion _initFootLocRot;` |
| 0xFC | `public Quaternion _footRotMapping;` |
| 0x110 | `public AnimationCurve GroundingCurve;` |
| 0x118 | `private int tTy;` |
| 0x11C | `public int i_lowerIndex;` |
| 0x120 | `public int i_higherIndex;` |
| 0x124 | `public float i_progress;` |
| 0x128 | `public float i_forProgress;` |
| 0x0 | `public static List<LegAnimationClipMotion.TransformsBackup> poseBackup;` |

<details><summary>methods (28)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3C36B94 | 0x2F7F264 |  | `public void .ctor(AnimationClip clip)` |
| 0x3C36C80 | 0x2F7F26C |  | `public List<LegAnimationClipMotion.MotionSample> UGT(Transform e, Transform f, Transform F, Transform d, Transform c, Transform U, Transform Y, int W = 20, float E = 1, float A = 1, float u = 0, bool k = false, bool O = false, float t = 0, LegAnimationClipMotion.xW r, int N = 0, int q = 0)` |
| 0x3C393E0 | 0x2F7F274 |  | `public float UGL(Transform e, Transform f)` |
| 0x3C39740 | 0x2F7F27C |  | `public float UGo(Transform e, Transform f, float F, float d = 1)` |
| 0x3C394AC | 0x2F7F284 |  | `public float UGy(Transform e, Transform f, Nullable<float> F)` |
| 0x3C397AC | 0x2F7F28C |  | `public Vector3 UGz(float e, float f = 0.5)` |
| 0x3C3981C | 0x2F7F29C |  | `public Vector3 UGh(float e)` |
| 0x3C39AEC | 0x2F7F2AC |  | `public Vector3 UGB(float e)` |
| 0x3C39BAC | 0x2F7F2BC |  | `public LegAnimationClipMotion.MotionSample UGm(float e, bool f = true)` |
| 0x3C39C30 | 0x2F7F2C4 |  | `public Vector3 UGR(float e)` |
| 0x3C39D24 | 0x2F7F2D4 |  | `public Vector3 UGb(float e)` |
| 0x3C39544 | 0x2F7F2E4 |  | `public Vector3 UGl(float e)` |
| 0x3C39E0C | 0x2F7F2F4 |  | `public Vector3 UGx(float e)` |
| 0x3C39ECC | 0x2F7F304 |  | `public Vector3 UGK(float e)` |
| 0x3C39F8C | 0x2F7F314 |  | `public Vector3 UGG(float e)` |
| 0x3C3A04C | 0x2F7F324 |  | `public Vector3 UGP(float e)` |
| 0x3C3A10C | 0x2F7F334 |  | `public bool UGD(float e)` |
| 0x3C3A190 | 0x2F7F33C |  | `public bool UGn(float e)` |
| 0x3C3A224 | 0x2F7F344 |  | `public bool UGV(float e)` |
| 0x3C39790 | 0x2F7F34C |  | `public float UGg(float e, float f = 5)` |
| 0x3C398DC | 0x2F7F354 |  | `public void UGp(float e)` |
| 0x3C390C0 | 0x2F7F358 |  | `private void UGv(string e, float f)` |
| 0x3C39D18 | 0x2F7F35C |  | `public static float UGS(float e)` |
| 0x3C3A2B8 | 0x2F7F364 |  | `public LegAnimationClipMotion UGI()` |
| 0x3C38E68 | 0x2F7F36C |  | `private static void UGM(Transform e)` |
| 0x3C3962C | 0x2F7F370 |  | `private static void UPe()` |
| 0x3C390CC | 0x2F7F374 |  | `public Vector3 UPf(Transform e, float f)` |
| 0x3C3924C | 0x2F7F384 |  | `public Vector3 UPF(Transform e, float f)` |

</details>
