# namespace `UnityStandardAssets.Vehicles.Aeroplane`  (5 types)

### public class `AeroplaneAiControl` : MonoBehaviour  
`TypeDefIndex 2678`

| offset | field |
|---|---|
| 0x20 | `private float m_RollSensitivity;` |
| 0x24 | `private float m_PitchSensitivity;` |
| 0x28 | `private float m_LateralWanderDistance;` |
| 0x2C | `private float m_LateralWanderSpeed;` |
| 0x30 | `private float m_MaxClimbAngle;` |
| 0x34 | `private float m_MaxRollAngle;` |
| 0x38 | `private float m_SpeedEffect;` |
| 0x3C | `private float m_TakeoffHeight;` |
| 0x40 | `private Transform m_Target;` |
| 0x48 | `private AeroplaneController tAj;` |
| 0x50 | `private float tAa;` |
| 0x54 | `private bool tAQ;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B27C08 | 0x2DED664 |  | `private void Awake()` |
| 0x3B27C7C | 0x2DED668 |  | `public void Reset()` |
| 0x3B27C84 | 0x2DED66C |  | `private void RecoveredNoopFixedUpdate()` |
| 0x3B27F2C | 0x2DED670 |  | `public void UQI(Transform e)` |
| 0x3B27F34 | 0x2DED674 |  | `public void .ctor()` |

</details>

### public class `AeroplaneAudio` : MonoBehaviour  
`TypeDefIndex 2680`

| offset | field |
|---|---|
| 0x20 | `private AudioClip m_EngineSound;` |
| 0x28 | `private float m_EngineMinThrottlePitch;` |
| 0x2C | `private float m_EngineMaxThrottlePitch;` |
| 0x30 | `private float m_EngineFwdSpeedMultiplier;` |
| 0x38 | `private AudioClip m_WindSound;` |
| 0x40 | `private float m_WindBasePitch;` |
| 0x44 | `private float m_WindSpeedPitchFactor;` |
| 0x48 | `private float m_WindMaxSpeedVolume;` |
| 0x50 | `private AeroplaneAudio.AdvancedSetttings m_AdvancedSetttings;` |
| 0x58 | `private AudioSource tAH;` |
| 0x60 | `private AudioSource tAi;` |
| 0x68 | `private AeroplaneController tAw;` |
| 0x70 | `private Rigidbody tAJ;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B27F50 | 0x2DED67C |  | `private void Awake()` |
| 0x3B28198 | 0x2DED680 |  | `private void RecoveredNoopUpdate()` |
| 0x3B2836C | 0x2DED684 |  | `public void .ctor()` |

</details>

### public class `AeroplaneController` : MonoBehaviour  
`TypeDefIndex 2681`

| offset | field |
|---|---|
| 0x20 | `private float m_MaxEnginePower;` |
| 0x24 | `private float m_Lift;` |
| 0x28 | `private float m_ZeroLiftSpeed;` |
| 0x2C | `private float m_RollEffect;` |
| 0x30 | `private float m_PitchEffect;` |
| 0x34 | `private float m_YawEffect;` |
| 0x38 | `private float m_BankedTurnEffect;` |
| 0x3C | `private float m_AerodynamicEffect;` |
| 0x40 | `private float m_AutoTurnPitch;` |
| 0x44 | `private float m_AutoRollLevel;` |
| 0x48 | `private float m_AutoPitchLevel;` |
| 0x4C | `private float m_AirBrakesEffect;` |
| 0x50 | `private float m_ThrottleChangeSpeed;` |
| 0x54 | `private float m_DragIncreaseFactor;` |
| 0x84 | `private float tAx;` |
| 0x88 | `private float tAK;` |
| 0x8C | `private float tAG;` |
| 0x90 | `private bool tAP;` |
| 0x94 | `private float tAD;` |
| 0x98 | `private Rigidbody tAn;` |
| 0xA0 | `private WheelCollider[] tAV;` |

Properties: `public float tAT { get; set; }`; `public float tAL { get; set; }`; `public bool tAo { get; set; }`; `public float tAy { get; set; }`; `public float tAz { get; set; }`; `public float CFy { get; }`; `public float tAh { get; set; }`; `public float tAB { get; set; }`; `public float tAm { get; set; }`; `public float tAR { get; set; }`; `public float tAb { get; set; }`; `public float tAl { get; set; }`

<details><summary>methods (38)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B28788 | 0x2DED694 |  | `public float get_tAT()` |
| 0x3B28790 | 0x2DED69C |  | `private void set_tAT(float value)` |
| 0x3B28798 | 0x2DED6A0 |  | `public float get_tAL()` |
| 0x3B287A0 | 0x2DED6A8 |  | `private void set_tAL(float value)` |
| 0x3B287A8 | 0x2DED6AC |  | `public bool get_tAo()` |
| 0x3B287B0 | 0x2DED6B4 |  | `private void set_tAo(bool value)` |
| 0x3B287BC | 0x2DED6B8 |  | `public float get_tAy()` |
| 0x3B287C4 | 0x2DED6C0 |  | `private void set_tAy(float value)` |
| 0x3B287CC | 0x2DED6C4 |  | `public float get_tAz()` |
| 0x3B287D4 | 0x2DED6CC |  | `private void set_tAz(float value)` |
| 0x3B287DC | 0x2DED6D0 |  | `public float get_CFy()` |
| 0x3B287E4 | 0x2DED6D8 |  | `public float get_tAh()` |
| 0x3B287EC | 0x2DED6E0 |  | `private void set_tAh(float value)` |
| 0x3B287F4 | 0x2DED6E4 |  | `public float get_tAB()` |
| 0x3B287FC | 0x2DED6EC |  | `private void set_tAB(float value)` |
| 0x3B28804 | 0x2DED6F0 |  | `public float get_tAm()` |
| 0x3B2880C | 0x2DED6F8 |  | `private void set_tAm(float value)` |
| 0x3B28814 | 0x2DED6FC |  | `public float get_tAR()` |
| 0x3B2881C | 0x2DED704 |  | `private void set_tAR(float value)` |
| 0x3B28824 | 0x2DED708 |  | `public float get_tAb()` |
| 0x3B2882C | 0x2DED710 |  | `private void set_tAb(float value)` |
| 0x3B28834 | 0x2DED714 |  | `public float get_tAl()` |
| 0x3B2883C | 0x2DED71C |  | `private void set_tAl(float value)` |
| 0x3B28844 | 0x2DED720 |  | `private void Start()` |
| 0x3B27EC4 | 0x2DED724 |  | `public void Move(float rollInput, float pitchInput, float yawInput, float throttleInput, bool airBrakes)` |
| 0x3B289A8 | 0x2DED728 |  | `private void UHH()` |
| 0x3B289F4 | 0x2DED72C |  | `private void UHi()` |
| 0x3B28BAC | 0x2DED730 |  | `private void UHw()` |
| 0x3B28C24 | 0x2DED734 |  | `private void UHJ()` |
| 0x3B28C7C | 0x2DED738 |  | `private void UHX()` |
| 0x3B28CF0 | 0x2DED73C |  | `private void UHT()` |
| 0x3B28DDC | 0x2DED740 |  | `private void UHL()` |
| 0x3B29134 | 0x2DED744 |  | `private void UHo()` |
| 0x3B2937C | 0x2DED748 |  | `private void UHy()` |
| 0x3B2956C | 0x2DED74C |  | `private void UHz()` |
| 0x3B29784 | 0x2DED750 |  | `public void Immobilize()` |
| 0x3B29790 | 0x2DED754 |  | `public void Reset()` |
| 0x3B29798 | 0x2DED758 |  | `public void .ctor()` |

</details>

### public class `AeroplaneControlSurfaceAnimator` : MonoBehaviour  
`TypeDefIndex 2684`

| offset | field |
|---|---|
| 0x20 | `private float m_Smoothing;` |
| 0x28 | `private AeroplaneControlSurfaceAnimator.ControlSurface[] m_ControlSurfaces;` |
| 0x30 | `private AeroplaneController tAX;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B28434 | 0x2DED760 |  | `private void Start()` |
| 0x3B284EC | 0x2DED764 |  | `private void RecoveredNoopUpdate()` |
| 0x3B28644 | 0x2DED768 |  | `private void UQM(AeroplaneControlSurfaceAnimator.ControlSurface e, Quaternion f)` |
| 0x3B28770 | 0x2DED76C |  | `public void .ctor()` |

</details>

### public class `AeroplanePropellerAnimator` : MonoBehaviour  
`TypeDefIndex 2685`

| offset | field |
|---|---|
| 0x20 | `private Transform m_PropellorModel;` |
| 0x28 | `private Transform m_PropellorBlur;` |
| 0x30 | `private Texture2D[] m_PropellorBlurTextures;` |
| 0x38 | `private float m_ThrottleBlurStart;` |
| 0x3C | `private float m_ThrottleBlurEnd;` |
| 0x40 | `private float m_MaxRpm;` |
| 0x48 | `private AeroplaneController tAg;` |
| 0x50 | `private int tAp;` |
| - | `private const float tAv = 60;` |
| 0x58 | `private Renderer tAS;` |
| 0x60 | `private Renderer tAI;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B297CC | 0x2DED77C |  | `private void Awake()` |
| 0x3B2989C | 0x2DED780 |  | `private void RecoveredNoopUpdate()` |
| 0x3B29A74 | 0x2DED784 |  | `public void .ctor()` |

</details>
