# namespace `Revolution.Shared`  (7 types)

### public sealed class `DoorMotionGeometry`  
`TypeDefIndex 3971`

| offset | field |
|---|---|
| - | `private readonly Dictionary<uint, DoorMotionGeometry.Motion> motions;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F816AC |  | `public float Duration(uint prefab)` |
| - | 0x2F8172C |  | `public float Threshold(uint prefab)` |
| - | 0x2F817AC |  | `public bool ShapeMoves(uint prefab, int shape)` |
| - | 0x2F81868 |  | `public bool ShapeTransform(uint prefab, int shape, bool opening, float progress, out V3 offset, out V3 rotation, out float w)` |
| - | 0x2F81EE4 |  | `public float CastExtra(uint prefab, int leaf, InteractionShape shape, bool opening, float progress, V3 origin, V3 end)` |
| - | 0x2F82960 |  | `public static DoorMotionGeometry Read(Stream stream)` |
| - | 0x2F81B3C |  | `private static float Curve(float[] keys, float t)` |
| - | 0x2F832BC |  | `public float Cast(InteractionCatalog catalog, uint prefab, bool opening, float progress, V3 origin, V3 end, int mask, out int shape)` |
| - | 0x2F83194 |  | `public void .ctor()` |

</details>

### public sealed class `FoundationCollisionGeometry`  
`TypeDefIndex 3972`

| offset | field |
|---|---|
| - | `private readonly Dictionary<ulong, InteractionShape[]> profiles;` |

Properties: `public int Count { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F83724 |  | `public int get_Count()` |
| - | 0x2F83774 |  | `public static bool Supports(uint prefab)` |
| - | 0x2F8379C |  | `public InteractionShape[] Get(uint prefab, int grade)` |
| - | 0x2F8388C |  | `public static FoundationCollisionGeometry Read(Stream stream)` |
| - | 0x2F84098 |  | `public float Cast(uint prefab, int grade, V3 a, V3 b, int mask, out int shape)` |
| - | 0x2F84000 |  | `public void .ctor()` |

</details>

### public struct `V3`  
`TypeDefIndex 3973`

| offset | field |
|---|---|
| - | `public float X;` |
| - | `public float Y;` |
| - | `public float Z;` |

Properties: `public float Length2 { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F81ED8 |  | `public void .ctor(float x, float y, float z)` |
| - | 0x2F821A8 |  | `public static V3 op_Addition(V3 a, V3 b)` |
| - | 0x2F81EC8 |  | `public static V3 op_Subtraction(V3 a, V3 b)` |
| - | 0x2F83714 |  | `public static V3 op_Multiply(V3 a, float b)` |
| - | 0x2F84198 |  | `public static float Dot(V3 a, V3 b)` |
| - | 0x2F836EC |  | `public static V3 Cross(V3 a, V3 b)` |
| - | 0x2F841B0 |  | `public float get_Length2()` |

</details>

### public static class `InteractionContract`  
`TypeDefIndex 3974`

| offset | field |
|---|---|
| - | `public const float Range = 2;` |
| - | `public const float StandingEye = 1.6;` |
| - | `public const float CrouchingEye = 1.1;` |
| - | `public const float OriginalMeleeRayStart = 0.15;` |
| - | `public const int LayerMask = 579081;` |
| - | `public const uint PoseCommandHash = 284053833;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F841D0 |  | `public static void Ray(V3 feet, float yaw, float pitch, bool crouch, out V3 origin, out V3 end)` |

</details>

### public sealed class `InteractionShape`  
`TypeDefIndex 3975`

| offset | field |
|---|---|
| - | `public byte Kind;` |
| - | `public int Layer;` |
| - | `public int Part;` |
| - | `public float[] Data;` |
| - | `public const int RayOnlyPart = -2;` |
| - | `public const int MovementOnlyPart = -3;` |
| - | `private bool boundsReady;` |
| - | `private V3 boundsMin;` |
| - | `private V3 boundsMax;` |

Properties: `public bool AffectsMovement { get; }`; `public bool AffectsRaycasts { get; }`

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F8435C |  | `public bool get_AffectsMovement()` |
| - | 0x2F836D0 |  | `public bool get_AffectsRaycasts()` |
| - | 0x2F8436C |  | `private static V3 V(float[] d, int i)` |
| - | 0x2F843BC |  | `private void Bounds()` |
| - | 0x2F84874 |  | `private bool Near(V3 a, V3 b, float radius)` |
| - | 0x2F84A20 |  | `private static float Clamp(float a)` |
| - | 0x2F84A94 |  | `private static V3 ClosestSegment(V3 p, V3 a, V3 b)` |
| - | 0x2F84B9C |  | `private static V3 ClosestTriangle(V3 p, V3 a, V3 b, V3 c)` |
| - | 0x2F84FC0 |  | `public V3 ClosestPoint(V3 p)` |
| - | 0x2F858A8 |  | `private static float PointSegment(V3 p, V3 a, V3 b)` |
| - | 0x2F859BC |  | `private static float Segments(V3 p, V3 q, V3 a, V3 b)` |
| - | 0x2F85BD8 |  | `private static float PointTriangle(V3 p, V3 a, V3 b, V3 c)` |
| - | 0x2F8602C |  | `public static bool CapsuleTriangle(V3 a, V3 b, float radius, V3 x, V3 y, V3 z)` |
| - | 0x2F864DC |  | `private static float Triangle(V3 o, V3 d, V3 a, V3 b, V3 c, bool twoSided = false)` |
| - | 0x2F866F0 |  | `private bool ConvexContains(V3 p)` |
| - | 0x2F854C4 |  | `private bool MeshContains(V3 p)` |
| - | 0x2F86808 |  | `private static float Sphere(V3 o, V3 d, V3 c, float r)` |
| - | 0x2F85410 |  | `private V3 BoxLocal(V3 p)` |
| - | 0x2F86934 |  | `private float BoxDistance(V3 p)` |
| - | 0x2F821B8 |  | `public float Cast(V3 origin, V3 end, bool twoSided = false)` |
| - | 0x2F86A70 |  | `public bool OverlapsCapsule(V3 a, V3 b, float radius)` |
| - | 0x2F86E04 |  | `private static float SegmentTriangle(V3 a, V3 b, V3 x, V3 y, V3 z)` |
| - | 0x2F870E8 |  | `private static bool TrianglesNear(V3 a, V3 b, V3 c, V3 x, V3 y, V3 z, float radius)` |
| - | 0x2F87360 |  | `public static bool SweptCapsuleTriangle(V3 a, V3 b, V3 delta, float radius, V3 x, V3 y, V3 z)` |
| - | 0x2F87800 |  | `public bool SweepsCapsule(V3 a, V3 b, V3 delta, float radius)` |
| - | 0x2F84088 |  | `public void .ctor()` |

</details>

### public sealed class `InteractionCatalog`  
`TypeDefIndex 3976`

| offset | field |
|---|---|
| - | `private readonly Dictionary<ulong, InteractionShape[]> profiles;` |

Properties: `public int Count { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F88064 |  | `public int get_Count()` |
| - | 0x2F880B4 |  | `public InteractionShape[] Get(uint prefab, bool open = false)` |
| - | 0x2F88154 |  | `public static InteractionCatalog Read(Stream stream)` |
| - | 0x2F8885C |  | `public float Cast(uint prefab, bool open, V3 origin, V3 end, int mask, out int shape)` |
| - | 0x2F88978 |  | `public float CastParts(uint prefab, uint opened, V3 origin, V3 end, int mask, out int shape)` |
| - | 0x2F88AF8 |  | `public float CastStages(uint prefab, byte health, V3 origin, V3 end, int mask, out int shape)` |
| - | 0x2F887D4 |  | `public void .ctor()` |

</details>

### public sealed class `LockRayGeometry`  
`TypeDefIndex 3978`

| offset | field |
|---|---|
| - | `private readonly Dictionary<ulong, LockRayGeometry.Attachment[]> profiles;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F88D34 |  | `public static LockRayGeometry Read(Stream stream)` |
| - | 0x2F89420 |  | `public float Cast(uint prefab, int type, DoorMotionGeometry motion, bool opening, float progress, V3 origin, V3 end, int mask)` |
| - | 0x2F89390 |  | `public void .ctor()` |

</details>
