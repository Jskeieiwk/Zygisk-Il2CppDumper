# namespace `UnityStandardAssets.Cameras`  (3 types)

### public abstract class `AbstractTargetFollower` : MonoBehaviour  
`TypeDefIndex 2713`

| offset | field |
|---|---|
| 0x20 | `protected Transform m_Target;` |
| 0x28 | `private bool m_AutoTargetPlayer;` |
| 0x2C | `private AbstractTargetFollower.mx m_UpdateType;` |
| 0x30 | `protected Rigidbody tkr;` |

Properties: `public Transform CFb { get; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B3244C | 0x2DEDC58 |  | `public Transform get_CFb()` |
| 0x3B3206C | 0x2DEDC60 | 4 | `protected virtual void Start()` |
| 0x3B321F0 | 0x2DEDC64 |  | `private void RecoveredNoopFixedUpdate()` |
| 0x3B322B4 | 0x2DEDC68 |  | `private void RecoveredNoopLateUpdate()` |
| 0x3B3237C | 0x2DEDC6C |  | `public void UiZ()` |
| - | - |  | `protected abstract void Uij(float e);` |
| 0x3B32124 | 0x2DEDC70 |  | `public void Uia()` |
| 0x3B32444 | 0x2DEDC74 | 6 | `public virtual void UiQ(Transform e)` |
| 0x3B32454 | 0x2DEDC78 |  | `protected void .ctor()` |

</details>

### public class `AutoCam` : PivotBasedCameraRig  
`TypeDefIndex 2714`

| offset | field |
|---|---|
| 0x54 | `private float m_MoveSpeed;` |
| 0x58 | `private float m_TurnSpeed;` |
| 0x5C | `private float m_RollSpeed;` |
| 0x60 | `private bool m_FollowVelocity;` |
| 0x61 | `private bool m_FollowTilt;` |
| 0x64 | `private float m_SpinTurnLimit;` |
| 0x68 | `private float m_TargetVelocityLowerLimit;` |
| 0x6C | `private float m_SmoothTurnTime;` |
| 0x70 | `private float tkN;` |
| 0x74 | `private float tkq;` |
| 0x78 | `private float tks;` |
| 0x7C | `private Vector3 tkC;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B32464 | 0x2DEDC80 | 5 | `protected override void Uij(float e)` |
| 0x3B32A68 | 0x2DEDC84 |  | `public void .ctor()` |

</details>

### public abstract class `PivotBasedCameraRig` : AbstractTargetFollower  
`TypeDefIndex 2715`

| offset | field |
|---|---|
| 0x38 | `protected Transform tkZ;` |
| 0x40 | `protected Transform tkj;` |
| 0x48 | `protected Vector3 tka;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B32B08 | 0x2DEDC94 | 7 | `protected virtual void Awake()` |
| 0x3B32AF8 | 0x2DEDC8C |  | `protected void .ctor()` |

</details>
