# namespace `ECM.Examples`  (7 types)

### public class `CharacterController2D` : BaseCharacterController  
`TypeDefIndex 3937`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3709900 | 0x2F7F608 | 24 | `protected override void Fxa()` |
| 0x3709904 | 0x2F7F60C | 26 | `protected override void FxQ()` |
| 0x37099C0 | 0x2F7F610 | 25 | `protected override void FxH()` |
| 0x3709A20 | 0x2F7F614 | 27 | `public override void Awake()` |
| 0x3709ADC | 0x2F7F618 |  | `public void .ctor()` |
| 0x3709AE0 | 0x2F7F620 | 12 | `public override bool Fuk()` |

</details>

### public sealed class `CustomAgentController` : BaseAgentController  
`TypeDefIndex 3938`

| offset | field |
|---|---|
| 0x138 | `private float _walkSpeed;` |
| 0x13C | `private float _runSpeed;` |

Properties: `public float sBc { get; set; }`; `public float sBU { get; set; }`; `public bool kzU { get; set; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3709AE8 | 0x2F7F628 |  | `public float get_sBc()` |
| 0x3709AF0 | 0x2F7F630 |  | `public void set_sBc(float value)` |
| 0x3709AF8 | 0x2F7F634 |  | `public float get_sBU()` |
| 0x3709B00 | 0x2F7F63C |  | `public void set_sBU(float value)` |
| 0x3709B08 | 0x2F7F640 |  | `public bool get_kzU()` |
| 0x3709B10 | 0x2F7F648 |  | `public void set_kzU(bool value)` |
| 0x3709B1C | 0x2F7F64C |  | `private float FgZ()` |
| 0x3709B38 | 0x2F7F654 | 22 | `protected override Vector3 Fxw()` |
| 0x3709B60 | 0x2F7F664 | 24 | `protected override void Fxa()` |
| 0x3709E34 | 0x2F7F668 | 26 | `protected override void FxQ()` |
| 0x3709EA4 | 0x2F7F66C |  | `public void .ctor()` |
| 0x3709EE8 | 0x2F7F67C | 12 | `public override bool Fuk()` |

</details>

### public sealed class `EthanAgentController` : BaseAgentController  
`TypeDefIndex 3939`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370ACCC | 0x2F7F684 | 24 | `protected override void Fxa()` |
| 0x370AF30 | 0x2F7F688 |  | `public void .ctor()` |
| 0x370AF68 | 0x2F7F690 | 12 | `public override bool Fuk()` |

</details>

### public sealed class `EthanCharacterController` : BaseCharacterController  
`TypeDefIndex 3940`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370AF70 | 0x2F7F698 | 24 | `protected override void Fxa()` |
| 0x370B28C | 0x2F7F69C |  | `public void .ctor()` |
| 0x370B290 | 0x2F7F6A4 | 12 | `public override bool Fuk()` |

</details>

### public class `EthanPlatformerController` : BaseCharacterController  
`TypeDefIndex 3941`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370B298 | 0x2F7F6AC | 24 | `protected override void Fxa()` |
| 0x370B5B4 | 0x2F7F6B0 |  | `public void .ctor()` |
| 0x370B5B8 | 0x2F7F6B8 | 12 | `public override bool Fuk()` |

</details>

### public sealed class `FollowCameraController` : MonoBehaviour  
`TypeDefIndex 3942`

| offset | field |
|---|---|
| 0x20 | `private Transform _targetTransform;` |
| 0x28 | `private float _distanceToTarget;` |
| 0x2C | `private float _followSpeed;` |

Properties: `public Transform sBE { get; set; }`; `public float sBA { get; set; }`; `public float sBu { get; set; }`; `private Vector3 sBk { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370B920 | 0x2F7F6C0 |  | `public Transform get_sBE()` |
| 0x370B928 | 0x2F7F6C8 |  | `public void set_sBE(Transform value)` |
| 0x370B930 | 0x2F7F6CC |  | `public float get_sBA()` |
| 0x370B938 | 0x2F7F6D4 |  | `public void set_sBA(float value)` |
| 0x370B948 | 0x2F7F6D8 |  | `public float get_sBu()` |
| 0x370B950 | 0x2F7F6E0 |  | `public void set_sBu(float value)` |
| 0x370B960 | 0x2F7F6E4 |  | `private Vector3 get_sBk()` |
| 0x370B9D4 | 0x2F7F6F4 |  | `public void OnValidate()` |
| 0x370B9EC | 0x2F7F6F8 |  | `public void Awake()` |
| 0x370BA28 | 0x2F7F6FC |  | `public void LateUpdate()` |
| 0x370BAFC | 0x2F7F700 |  | `public void .ctor()` |

</details>

### public class `FPS_CustomController` : BaseFirstPersonController  
`TypeDefIndex 3943`

| offset | field |
|---|---|
| 0x150 | `public Animator cameraAnimator;` |
| 0x158 | `public float cameraAnimSpeed;` |
| 0x15C | `private int kzA;` |
| 0x160 | `private int kzu;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370B5C0 | 0x2F7F708 |  | `private void FgL()` |
| 0x370B7B8 | 0x2F7F70C | 24 | `protected override void Fxa()` |
| 0x370B7BC | 0x2F7F710 | 26 | `protected override void FxQ()` |
| 0x370B87C | 0x2F7F714 | 27 | `public override void Awake()` |
| 0x370B8FC | 0x2F7F718 |  | `public void .ctor()` |
| 0x370B918 | 0x2F7F720 | 12 | `public override bool Fuk()` |

</details>
