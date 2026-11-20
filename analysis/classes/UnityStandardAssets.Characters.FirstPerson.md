# namespace `UnityStandardAssets.Characters.FirstPerson`  (2 types)

### public class `FirstPersonController` : MonoBehaviour  
`TypeDefIndex 2710`

| offset | field |
|---|---|
| 0x20 | `private bool m_IsWalking;` |
| 0x24 | `private float m_WalkSpeed;` |
| 0x28 | `private float m_RunSpeed;` |
| 0x2C | `private float m_RunstepLenghten;` |
| 0x30 | `private float m_JumpSpeed;` |
| 0x34 | `private float m_StickToGroundForce;` |
| 0x38 | `private float m_GravityMultiplier;` |
| 0x40 | `private MouseLook m_MouseLook;` |
| 0x48 | `private bool m_UseFovKick;` |
| 0x50 | `private FOVKick m_FovKick;` |
| 0x58 | `private bool m_UseHeadBob;` |
| 0x60 | `private CurveControlledBob m_HeadBob;` |
| 0x68 | `private LerpControlledBob m_JumpBob;` |
| 0x70 | `private float m_StepInterval;` |
| 0x78 | `private AudioClip[] m_FootstepSounds;` |
| 0x80 | `private AudioClip m_JumpSound;` |
| 0x88 | `private AudioClip m_LandSound;` |
| 0x90 | `private Camera tux;` |
| 0x98 | `private bool tuK;` |
| 0x9C | `private float tuG;` |
| 0xA0 | `private Vector2 tuP;` |
| 0xA8 | `private Vector3 tuD;` |
| 0xB8 | `private CharacterController tun;` |
| 0xC0 | `private CollisionFlags tuV;` |
| 0xC4 | `private bool tug;` |
| 0xC8 | `private Vector3 tup;` |
| 0xD4 | `private float tuv;` |
| 0xD8 | `private float tuS;` |
| 0xDC | `private bool tuI;` |
| 0xE0 | `private AudioSource tuM;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B2D588 | 0x2DEDBF0 |  | `private void Start()` |
| 0x3B2D714 | 0x2DEDBF4 |  | `private void RecoveredNoopUpdate()` |
| 0x3B2D898 | 0x2DEDBF8 |  | `private void UHv()` |
| 0x3B2D8E0 | 0x2DEDBFC |  | `private void RecoveredNoopFixedUpdate()` |
| 0x3B2DF54 | 0x2DEDC00 |  | `private void UHS()` |
| 0x3B2DF88 | 0x2DEDC04 |  | `private void UHI(float e)` |
| 0x3B2E320 | 0x2DEDC08 |  | `private void UHM()` |
| 0x3B2E0D4 | 0x2DEDC0C |  | `private void Uie(float e)` |
| 0x3B2DD18 | 0x2DEDC10 |  | `private void Uif(out float e)` |
| 0x3B2D848 | 0x2DEDC18 |  | `private void UiF()` |
| 0x3B2E7AC | 0x2DEDC1C |  | `private void OnControllerColliderHit(ControllerColliderHit hit)` |
| 0x3B2E8D0 | 0x2DEDC20 |  | `public void .ctor()` |

</details>

### public class `MouseLook`  
`TypeDefIndex 2711`

| offset | field |
|---|---|
| 0x10 | `public float XSensitivity;` |
| 0x14 | `public float YSensitivity;` |
| 0x18 | `public bool clampVerticalRotation;` |
| 0x1C | `public float MinimumX;` |
| 0x20 | `public float MaximumX;` |
| 0x24 | `public bool smooth;` |
| 0x28 | `public float smoothTime;` |
| 0x2C | `public bool lockCursor;` |
| 0x30 | `private Quaternion tkF;` |
| 0x40 | `private Quaternion tkd;` |
| 0x50 | `private bool tkc;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B2D6C4 | 0x2DEDC28 |  | `public void Uid(Transform e, Transform f)` |
| 0x3B2E430 | 0x2DEDC2C |  | `public void Uic(Transform e, Transform f)` |
| 0x3B2F524 | 0x2DEDC30 |  | `public void UiU(bool e)` |
| 0x3B2E310 | 0x2DEDC34 |  | `public void UiY()` |
| 0x3B2F558 | 0x2DEDC38 |  | `private void UiW()` |
| 0x3B2F4C0 | 0x2DEDC3C |  | `private Quaternion UiE(Quaternion e)` |
| 0x3B2F5D0 | 0x2DEDC50 |  | `public void .ctor()` |

</details>
