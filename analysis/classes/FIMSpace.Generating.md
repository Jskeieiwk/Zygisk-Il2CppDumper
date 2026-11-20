# namespace `FIMSpace.Generating`  (3 types)

### public struct `MinMax`  
`TypeDefIndex 3890`

| offset | field |
|---|---|
| 0x0 | `public int Min;` |
| 0x4 | `public int Max;` |

Properties: `public bool CUO { get; }`; `public static MinMax CUt { get; }`; `public Vector2 CUr { get; }`; `public Vector2Int CUN { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3E19308 | 0x2F7E700 |  | `public bool get_CUO()` |
| 0x3E19328 | 0x2F7E708 |  | `public static MinMax get_CUt()` |
| 0x3E19338 | 0x2F7E710 |  | `public Vector2 get_CUr()` |
| 0x3E19348 | 0x2F7E71C |  | `public Vector2Int get_CUN()` |
| 0x3E19330 | 0x2F7E724 |  | `public void .ctor(int min, int max)` |
| 0x3E19350 | 0x2F7E72C |  | `public int UMG()` |

</details>

### public struct `MinMaxF`  
`TypeDefIndex 3891`

| offset | field |
|---|---|
| 0x0 | `public float Min;` |
| 0x4 | `public float Max;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3E193DC | 0x2F7E734 |  | `public void .ctor(float min, float max)` |

</details>

### public class `PrefabReference`  
`TypeDefIndex 3892`

| offset | field |
|---|---|
| 0x10 | `private GameObject Prefab;` |
| 0x18 | `private GameObject tzQ;` |
| 0x20 | `private Collider MainCollider;` |
| 0x28 | `private Collider tzH;` |
| 0x30 | `private int tzi;` |
| 0x34 | `public int subID;` |
| 0x38 | `private Texture tzw;` |
| 0x0 | `public static GUILayoutOption[] opt;` |
| 0x8 | `public static GUILayoutOption[] opt2;` |
| 0x10 | `public static GUILayoutOption[] opt3;` |
| 0x18 | `public static bool StopReloadLayoutOptions;` |
| 0x40 | `protected Mesh _refMesh;` |
| 0x48 | `protected Collider _refCol;` |

Properties: `public GameObject CUW { get; }`; `public Collider CUE { get; }`; `public GameObject CUA { get; }`; `public Collider CUu { get; }`; `public Texture CUk { get; }`

<details><summary>methods (21)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3E174BC | 0x2F7E73C |  | `public GameObject get_CUW()` |
| 0x3E174C4 | 0x2F7E744 |  | `public Collider get_CUE()` |
| 0x3E174CC | 0x2F7E74C |  | `public GameObject get_CUA()` |
| 0x3E17544 | 0x2F7E754 |  | `public Collider get_CUu()` |
| 0x3E175BC | 0x2F7E75C |  | `public Texture get_CUk()` |
| 0x3E176A0 | 0x2F7E764 | 4 | `protected virtual void UMi(Color e, int f = 72, string F = "", Action d, Action c, bool U = true, bool Y = true)` |
| 0x3E176A4 | 0x2F7E768 | 5 | `protected virtual void UMw(int e = 72, string f = "", Action F, bool d = true)` |
| 0x3E176A8 | 0x2F7E76C | 6 | `public virtual void UMJ()` |
| 0x3E176AC | 0x2F7E770 |  | `public static void UMX(PrefabReference e, Color f, string F = "", int d = 72, Action c, Action U, bool Y = true, Object W, bool E = true, bool A = true)` |
| - | - |  | `public static void UMT<e>(List<e> e_p, ref bool f, ref int F, ref bool d, Color c, Color U, float Y = 500, int W = 72, bool E = false, Object A, bool u = true)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38A702C Offset: 0x38A302C VA: 0x38A702C` |
| - | - |  | `\|-PrefabReference.UMT<object>` |
| - | - |  | `*/` |
| 0x3E176B0 | 0x2F7E774 |  | `public Mesh UML(bool e = false)` |
| 0x3E17A54 | 0x2F7E77C |  | `public Collider UMo()` |
| 0x3E17C68 | 0x2F7E784 |  | `public void UMy(GameObject e)` |
| 0x3E17C70 | 0x2F7E788 |  | `public void UMz(Collider e)` |
| 0x3E17C78 | 0x2F7E78C |  | `public void UMh(GameObject e)` |
| 0x3E17D4C | 0x2F7E790 |  | `public void .ctor()` |

</details>
