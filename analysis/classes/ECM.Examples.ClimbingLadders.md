# namespace `ECM.Examples.ClimbingLadders`  (2 types)

### public sealed class `Ladder` : MonoBehaviour  
`TypeDefIndex 3947`

| offset | field |
|---|---|
| 0x20 | `public float PathLength;` |
| 0x24 | `public Vector3 PathOffset;` |
| 0x30 | `public Transform TopPoint;` |
| 0x38 | `public Transform BottomPoint;` |

Properties: `public Vector3 sBO { get; }`; `public Vector3 sBt { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370C380 | 0x2F7F7B8 |  | `public Vector3 get_sBO()` |
| 0x370C3F0 | 0x2F7F7C8 |  | `public Vector3 get_sBt()` |
| 0x370C458 | 0x2F7F7D8 |  | `public Vector3 Fgn(Vector3 e, out float f)` |
| 0x370C730 | 0x2F7F7EC |  | `private void OnDrawGizmos()` |
| 0x370C924 | 0x2F7F7F0 |  | `public void .ctor()` |

</details>

### public class `MyCharacterController` : BaseCharacterController  
`TypeDefIndex 3948`

| offset | field |
|---|---|
| 0x11C | `public float ClimbingSpeed;` |
| 0x120 | `public float GrabbingTime;` |
| 0x124 | `public LayerMask ladderMask;` |
| 0x128 | `private Ladder kzt;` |
| 0x130 | `private float kzr;` |
| 0x134 | `private Vector3 kzN;` |
| 0x140 | `private Vector3 kzq;` |
| 0x14C | `private Quaternion kzs;` |
| 0x15C | `private Quaternion kzC;` |
| 0x16C | `private float kzZ;` |

Properties: `public bool kzj { get; set; }`; `public bool kza { get; set; }`; `public bool kzQ { get; set; }`; `public bool kzH { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370C938 | 0x2F7F7F8 |  | `public bool get_kzj()` |
| 0x370C940 | 0x2F7F800 |  | `public void set_kzj(bool value)` |
| 0x370C94C | 0x2F7F804 |  | `public bool get_kza()` |
| 0x370C954 | 0x2F7F80C |  | `private void set_kza(bool value)` |
| 0x370C960 | 0x2F7F810 |  | `public bool get_kzQ()` |
| 0x370C968 | 0x2F7F818 |  | `private void set_kzQ(bool value)` |
| 0x370C974 | 0x2F7F81C |  | `public bool get_kzH()` |
| 0x370C97C | 0x2F7F824 |  | `private void set_kzH(bool value)` |
| 0x370C988 | 0x2F7F828 | 24 | `protected override void Fxa()` |
| 0x370C98C | 0x2F7F82C |  | `private void Fpf()` |
| 0x370CBB4 | 0x2F7F830 |  | `private void FpF()` |
| 0x370CC68 | 0x2F7F834 |  | `private void Fpd()` |
| 0x370CFB8 | 0x2F7F838 | 23 | `protected override void Move()` |
| 0x370D154 | 0x2F7F83C | 25 | `protected override void FxH()` |
| 0x370D1EC | 0x2F7F840 | 26 | `protected override void FxQ()` |
| 0x370D2E4 | 0x2F7F844 |  | `public void .ctor()` |
| 0x370D2FC | 0x2F7F84C | 12 | `public override bool Fuk()` |

</details>
