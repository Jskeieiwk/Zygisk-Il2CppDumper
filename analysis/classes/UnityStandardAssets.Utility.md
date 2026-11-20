# namespace `UnityStandardAssets.Utility`  (9 types)

### public class `AutoMobileShaderSwitch` : MonoBehaviour  
`TypeDefIndex 2688`

| offset | field |
|---|---|
| 0x20 | `private AutoMobileShaderSwitch.ReplacementList m_ReplacementList;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AD63F0 | 0x2DED78C |  | `private void OnEnable()` |
| 0x3AD6D60 | 0x2DED790 |  | `public void .ctor()` |

</details>

### public class `CurveControlledBob`  
`TypeDefIndex 2689`

| offset | field |
|---|---|
| 0x10 | `public float HorizontalBobRange;` |
| 0x14 | `public float VerticalBobRange;` |
| 0x18 | `public AnimationCurve Bobcurve;` |
| 0x20 | `public float VerticaltoHorizontalRatio;` |
| 0x24 | `private float tdm;` |
| 0x28 | `private float tdR;` |
| 0x2C | `private float tdb;` |
| 0x30 | `private Vector3 tdl;` |
| 0x3C | `private float tdx;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AD78B4 | 0x2DED7A8 |  | `public void Usl(Camera e, float f)` |
| 0x3AD7954 | 0x2DED7AC |  | `public Vector3 Usx(float e)` |
| 0x3AD7A58 | 0x2DED7BC |  | `public void .ctor()` |

</details>

### public class `FOVKick`  
`TypeDefIndex 2692`

| offset | field |
|---|---|
| 0x10 | `public Camera Camera;` |
| 0x18 | `public float originalFov;` |
| 0x1C | `public float FOVIncrease;` |
| 0x20 | `public float TimeToIncrease;` |
| 0x24 | `public float TimeToDecrease;` |
| 0x28 | `public AnimationCurve IncreaseCurve;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AD8878 | 0x2DED7C4 |  | `public void UCf(Camera e)` |
| 0x3AD88C0 | 0x2DED7C8 |  | `private void UCF(Camera e)` |
| 0x3AD89A8 | 0x2DED7CC |  | `public void UCd(Camera e)` |
| 0x3AD89B0 | 0x2DED7D0 |  | `public IEnumerator UCc()` |
| 0x3AD8A44 | 0x2DED7D8 |  | `public IEnumerator UCU()` |
| 0x3AD8AD8 | 0x2DED7E0 |  | `public void .ctor()` |

</details>

### public class `LerpControlledBob`  
`TypeDefIndex 2694`

| offset | field |
|---|---|
| 0x10 | `public float BobDuration;` |
| 0x14 | `public float BobAmount;` |
| 0x18 | `private float tcH;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3AD9640 | 0x2DED838 |  | `public float UCu()` |
| - | 0x2DED840 |  | `public IEnumerator UCk()` |
| 0x3AD96DC | 0x2DED848 |  | `public void .ctor()` |

</details>

### public class `PlatformSpecificContent` : MonoBehaviour  
`TypeDefIndex 2696`

| offset | field |
|---|---|
| 0x20 | `private PlatformSpecificContent.zx m_BuildTargetGroup;` |
| 0x28 | `private GameObject[] m_Content;` |
| 0x30 | `private MonoBehaviour[] m_MonoBehaviours;` |
| 0x38 | `private bool m_ChildrenOfThisObject;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ADA258 | 0x2DED878 |  | `private void OnEnable()` |
| 0x3ADA25C | 0x2DED87C |  | `private void UCH()` |
| 0x3ADA26C | 0x2DED880 |  | `private void UCi(bool e)` |
| 0x3ADA654 | 0x2DED884 |  | `public void .ctor()` |

</details>

### public class `SmoothFollow` : MonoBehaviour  
`TypeDefIndex 2697`

| offset | field |
|---|---|
| 0x20 | `private Transform target;` |
| 0x28 | `private float distance;` |
| 0x2C | `private float height;` |
| 0x30 | `private float rotationDamping;` |
| 0x34 | `private float heightDamping;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ADB788 | 0x2DED88C |  | `private void Start()` |
| 0x3ADB78C | 0x2DED890 |  | `private void RecoveredNoopLateUpdate()` |
| 0x3ADBAC0 | 0x2DED894 |  | `public void .ctor()` |

</details>

### public class `TimedObjectDestructor` : MonoBehaviour  
`TypeDefIndex 2698`

| offset | field |
|---|---|
| 0x20 | `private float m_TimeOut;` |
| 0x24 | `private bool m_DetachChildren;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ADC4E8 | 0x2DED89C |  | `private void Awake()` |
| 0x3ADC550 | 0x2DED8EC |  | `private void DestroyNow()` |
| 0x3ADC5E0 | 0x2DED97C |  | `public void .ctor()` |

</details>

### public class `WaypointCircuit` : MonoBehaviour  
`TypeDefIndex 2701`

| offset | field |
|---|---|
| 0x20 | `public WaypointCircuit.WaypointList waypointList;` |
| 0x28 | `private bool smoothRoute;` |
| 0x2C | `private int tUe;` |
| 0x30 | `private Vector3[] tUf;` |
| 0x38 | `private float[] tUF;` |
| 0x40 | `public float editorVisualisationSubsteps;` |
| 0x48 | `private int tUc;` |
| 0x4C | `private int tUU;` |
| 0x50 | `private int tUY;` |
| 0x54 | `private int tUW;` |
| 0x58 | `private float tUE;` |
| 0x5C | `private Vector3 tUA;` |
| 0x68 | `private Vector3 tUu;` |
| 0x74 | `private Vector3 tUk;` |
| 0x80 | `private Vector3 tUO;` |

Properties: `public float tUd { get; set; }`; `public Transform[] CFW { get; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ADC5F0 | 0x2DED99C |  | `public float get_tUd()` |
| 0x3ADC5F8 | 0x2DED9A4 |  | `private void set_tUd(float value)` |
| 0x3ADC600 | 0x2DED9A8 |  | `public Transform[] get_CFW()` |
| 0x3ADC61C | 0x2DED9B0 |  | `private void Awake()` |
| 0x3ADC94C | 0x2DED9B4 |  | `public WaypointCircuit.RoutePoint UCD(float e)` |
| 0x3ADCA7C | 0x2DED9C0 |  | `public Vector3 UCn(float e)` |
| 0x3ADCCE8 | 0x2DED9D0 |  | `private Vector3 UCV(Vector3 e, Vector3 f, Vector3 F, Vector3 d, float c)` |
| 0x3ADC66C | 0x2DED9E0 |  | `private void UCg()` |
| 0x3ADCDF4 | 0x2DED9E4 |  | `private void OnDrawGizmos()` |
| 0x3ADD074 | 0x2DED9E8 |  | `private void OnDrawGizmosSelected()` |
| 0x3ADCDFC | 0x2DED9EC |  | `private void UCp(bool e)` |
| 0x3ADD07C | 0x2DED9F0 |  | `public void .ctor()` |

</details>

### public class `WaypointProgressTracker` : MonoBehaviour  
`TypeDefIndex 2703`

| offset | field |
|---|---|
| 0x20 | `private WaypointCircuit circuit;` |
| 0x28 | `private float lookAheadForTargetOffset;` |
| 0x2C | `private float lookAheadForTargetFactor;` |
| 0x30 | `private float lookAheadForSpeedOffset;` |
| 0x34 | `private float lookAheadForSpeedFactor;` |
| 0x38 | `private WaypointProgressTracker.zg progressStyle;` |
| 0x3C | `private float pointToPointThreshold;` |
| 0x88 | `public Transform target;` |
| 0x90 | `private float tUq;` |
| 0x94 | `private int tUs;` |
| 0x98 | `private Vector3 tUC;` |
| 0xA4 | `private float tUZ;` |

Properties: `public WaypointCircuit.RoutePoint tUt { get; set; }`; `public WaypointCircuit.RoutePoint tUr { get; set; }`; `public WaypointCircuit.RoutePoint tUN { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3ADD158 | 0x2DEDA0C |  | `public WaypointCircuit.RoutePoint get_tUt()` |
| 0x3ADD16C | 0x2DEDA18 |  | `private void set_tUt(WaypointCircuit.RoutePoint value)` |
| 0x3ADD180 | 0x2DEDA1C |  | `public WaypointCircuit.RoutePoint get_tUr()` |
| 0x3ADD194 | 0x2DEDA28 |  | `private void set_tUr(WaypointCircuit.RoutePoint value)` |
| 0x3ADD1A8 | 0x2DEDA2C |  | `public WaypointCircuit.RoutePoint get_tUN()` |
| 0x3ADD1BC | 0x2DEDA38 |  | `private void set_tUN(WaypointCircuit.RoutePoint value)` |
| 0x3ADD1D0 | 0x2DEDA3C |  | `private void Start()` |
| 0x3ADD2F0 | 0x2DEDA40 |  | `public void Reset()` |
| 0x3ADD3BC | 0x2DEDA44 |  | `private void RecoveredNoopUpdate()` |
| 0x3ADD8AC | 0x2DEDA48 |  | `private void OnDrawGizmos()` |
| 0x3ADDA48 | 0x2DEDA4C |  | `public void .ctor()` |

</details>
