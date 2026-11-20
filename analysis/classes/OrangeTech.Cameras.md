# namespace `OrangeTech.Cameras`  (2 types)

### public sealed class `OverShoulderCameraController` : MonoBehaviour  
`TypeDefIndex 3218`

| offset | field |
|---|---|
| 0x20 | `private Transform _target;` |
| 0x28 | `private float _minPitch;` |
| 0x2C | `private float _maxPitch;` |
| 0x30 | `private float _pitchDampTime;` |
| 0x34 | `private float koO;` |
| 0x38 | `private float kot;` |
| 0x3C | `private float kor;` |

Properties: `public Transform syy { get; set; }`; `public float syz { get; set; }`; `public float syh { get; set; }`; `public float syB { get; set; }`; `public Transform koN { get; set; }`; `public Transform koq { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F8CC0 | 0x2ED0A68 |  | `public Transform get_syy()` |
| 0x36F8CC8 | 0x2ED0A70 |  | `public void set_syy(Transform value)` |
| 0x36F8CD0 | 0x2ED0A74 |  | `public float get_syz()` |
| 0x36F8CD8 | 0x2ED0A7C |  | `public void set_syz(float value)` |
| 0x36F8CE0 | 0x2ED0A80 |  | `public float get_syh()` |
| 0x36F8CE8 | 0x2ED0A88 |  | `public void set_syh(float value)` |
| 0x36F8CF0 | 0x2ED0A8C |  | `public float get_syB()` |
| 0x36F8CF8 | 0x2ED0A94 |  | `public void set_syB(float value)` |
| 0x36F8D08 | 0x2ED0A98 |  | `public Transform get_koN()` |
| 0x36F8D10 | 0x2ED0AA0 |  | `private void set_koN(Transform value)` |
| 0x36F8D18 | 0x2ED0AA4 |  | `public Transform get_koq()` |
| 0x36F8D20 | 0x2ED0AAC |  | `private void set_koq(Transform value)` |
| 0x36F8D28 | 0x2ED0AB0 |  | `private static float FxY(float e, float f, float F)` |
| 0x36F8D64 | 0x2ED0AB8 |  | `public void OnValidate()` |
| 0x36F8D78 | 0x2ED0ABC |  | `public void Awake()` |
| 0x36F8E20 | 0x2ED0AC0 |  | `public void LateUpdate()` |
| 0x36F90D0 | 0x2ED0AC4 |  | `public void .ctor()` |

</details>

### public class `PreventCameraWallClip` : MonoBehaviour  
`TypeDefIndex 3219`

| offset | field |
|---|---|
| 0x20 | `private float _clipMoveTime;` |
| 0x24 | `private float _returnTime;` |
| 0x28 | `private float _sphereCastRadius;` |
| 0x2C | `private float _minDistance;` |
| 0x30 | `private LayerMask _collisionMask;` |
| 0x34 | `private float kos;` |
| 0x38 | `private float koC;` |
| 0x3C | `private float koZ;` |

Properties: `public float sym { get; set; }`; `public float syR { get; set; }`; `public float syb { get; set; }`; `public float syl { get; set; }`; `public LayerMask syx { get; set; }`; `public Transform koj { get; set; }`; `public Transform koa { get; set; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F90F0 | 0x2ED0ACC |  | `public float get_sym()` |
| 0x36F90F8 | 0x2ED0AD4 |  | `public void set_sym(float value)` |
| 0x36F9108 | 0x2ED0AD8 |  | `public float get_syR()` |
| 0x36F9110 | 0x2ED0AE0 |  | `public void set_syR(float value)` |
| 0x36F9120 | 0x2ED0AE4 |  | `public float get_syb()` |
| 0x36F9128 | 0x2ED0AEC |  | `public void set_syb(float value)` |
| 0x36F9138 | 0x2ED0AF0 |  | `public float get_syl()` |
| 0x36F9140 | 0x2ED0AF8 |  | `public void set_syl(float value)` |
| 0x36F9148 | 0x2ED0AFC |  | `public LayerMask get_syx()` |
| 0x36F9150 | 0x2ED0B04 |  | `public void set_syx(LayerMask value)` |
| 0x36F9158 | 0x2ED0B08 |  | `public Transform get_koj()` |
| 0x36F9160 | 0x2ED0B10 |  | `private void set_koj(Transform value)` |
| 0x36F9168 | 0x2ED0B14 |  | `public Transform get_koa()` |
| 0x36F9170 | 0x2ED0B1C |  | `private void set_koa(Transform value)` |
| 0x36F9178 | 0x2ED0B20 |  | `public void OnValidate()` |
| 0x36F919C | 0x2ED0B24 |  | `public void Awake()` |
| 0x36F92B0 | 0x2ED0B28 |  | `public void LateUpdate()` |
| 0x36F94DC | 0x2ED0B2C |  | `public void .ctor()` |

</details>
