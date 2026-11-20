# namespace `HyperHug.Games.Oxide.Features.Loot`  (2 types)

### public class `CarDoor` : Ua  
`TypeDefIndex 3686`

| offset | field |
|---|---|
| 0x40 | `private LootBoxCar lootBoxCar;` |
| 0x48 | `private Vector3 openRotation;` |
| 0x54 | `private Vector3 closedRotation;` |
| 0x60 | `private Collider doorCollider;` |
| 0x68 | `private float openSpeed;` |
| 0x70 | `private Transform[] doorTransforms;` |
| 0x78 | `private Vector3 Orj;` |
| 0x84 | `private Vector3 Ora;` |
| 0x90 | `private int OrQ;` |
| 0x94 | `private bool OrH;` |
| - | `private bool started;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38C2160 | 0x2F64ED4 |  | `private void Awake()` |
| - | 0x2F64F94 |  | `private void Start()` |
| - | 0x2F64FAC |  | `private bool Opened()` |
| - | 0x2F6508C |  | `private static bool Near(Vector3 a, Vector3 b)` |
| - | 0x2F650E8 |  | `private void Pose(Vector3 euler)` |
| 0x38C2194 | 0x2F65208 |  | `private void Update()` |
| 0x38C2500 | 0x2F65460 |  | `private void dIR(bool e)` |
| 0x38C25E4 | 0x2F655B4 | 13 | `public override void Fsd()` |
| 0x38C2720 | 0x2F65698 |  | `public void .ctor()` |

</details>

### public class `LootBoxCar` : Xb  
`TypeDefIndex 3687`

| offset | field |
|---|---|
| 0x80 | `private bool designedOnMap;` |
| 0x88 | `private WA[] spawnGroups;` |
| 0x90 | `private Transform[] groundPoints;` |
| 0x98 | `private Material defaultMaterial;` |
| 0xA0 | `private Renderer[] randomRenderers;` |
| 0xA8 | `private Material[] randomMaterials;` |
| 0xB0 | `private RaycastHit[] Ori;` |
| 0xB8 | `public SF<bool> Opened;` |
| 0xC0 | `public int Color;` |
| - | `private bool painted;` |

Properties: `public int sPP { get; set; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38C3168 | 0x2F656A0 |  | `public int get_sPP()` |
| 0x38C3170 | 0x2F656A8 |  | `public void set_sPP([In] int value)` |
| 0x38C2730 | 0x2F656B0 |  | `private void Awake()` |
| 0x38C27AC | 0x2F657DC |  | `private void dIb()` |
| 0x38C2944 | 0x2F65A30 | 11 | `public override void Fsv()` |
| - | 0x2F65A4C |  | `private void Start()` |
| 0x38C2960 | 0x2F65A64 |  | `private void dIl()` |
| 0x38C2A80 | 0x2F65B70 | 29 | `public override void dIx(PlayerManager e, int f)` |
| 0x38C2B08 | 0x2F65C00 |  | `private void dIK()` |
| 0x38C3094 | 0x2F65C04 |  | `public void .ctor()` |
| 0x38C3160 | 0x2F65DDC | 12 | `public override bool Fuk()` |
| 0x38C3228 | 0x2F65DE4 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x38C3288 | 0x2F65E44 | 15 | `protected override void FCO(vo e, bool f)` |

</details>
