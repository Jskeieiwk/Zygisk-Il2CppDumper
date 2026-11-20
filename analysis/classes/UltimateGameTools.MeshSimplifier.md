# namespace `UltimateGameTools.MeshSimplifier`  (3 types)

### public class `MeshUniqueVertices`  
`TypeDefIndex 2725`

| offset | field |
|---|---|
| 0x10 | `private List<Vector3> m_listVertices;` |
| 0x18 | `private List<Vector3> m_listVerticesWorld;` |
| 0x20 | `private List<MeshUniqueVertices.SerializableBoneWeight> m_listBoneWeights;` |
| 0x28 | `private MeshUniqueVertices.ListIndices[] m_aFaceList;` |

Properties: `public MeshUniqueVertices.ListIndices[] syf { get; }`; `public List<Vector3> syF { get; }`; `public List<Vector3> syd { get; }`; `public List<MeshUniqueVertices.SerializableBoneWeight> syc { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36D9DB0 | 0x2DF0D24 |  | `public MeshUniqueVertices.ListIndices[] get_syf()` |
| 0x36D9DB8 | 0x2DF0D2C |  | `public List<Vector3> get_syF()` |
| 0x36D9DC0 | 0x2DF0D34 |  | `public List<Vector3> get_syd()` |
| 0x36D9DC8 | 0x2DF0D3C |  | `public List<MeshUniqueVertices.SerializableBoneWeight> get_syc()` |
| 0x36D9DD0 | 0x2DF0D44 |  | `public void FRX(Mesh e, Vector3[] f)` |
| 0x36DA964 | 0x2DF0D48 |  | `public void .ctor()` |

</details>

### public class `RelevanceSphere`  
`TypeDefIndex 2726`

| offset | field |
|---|---|
| 0x10 | `public bool m_bExpanded;` |
| 0x14 | `public Vector3 m_v3Position;` |
| 0x20 | `public Vector3 m_v3Rotation;` |
| 0x2C | `public Vector3 m_v3Scale;` |
| 0x38 | `public float m_fRelevance;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36DB1F4 | 0x2DF0E60 |  | `public void .ctor()` |
| 0x36DB254 | 0x2DF0E68 |  | `public void FRT(Transform e, float f)` |

</details>

### public class `Simplifier` : MonoBehaviour  
`TypeDefIndex 2737`

| offset | field |
|---|---|
| 0x4 | `private static int kLu;` |
| - | `private const float kLk = 10000000;` |
| 0x28 | `private List<Simplifier.uA> kLO;` |
| 0x30 | `private List<Simplifier.uA> kLt;` |
| 0x38 | `private Simplifier.uE[] kLr;` |
| 0x40 | `private int m_nOriginalMeshVertexCount;` |
| 0x44 | `private float m_fOriginalMeshSize;` |
| 0x48 | `private List<int> m_listVertexMap;` |
| 0x50 | `private List<int> m_listVertexPermutationBack;` |
| 0x58 | `private MeshUniqueVertices m_meshUniqueVertices;` |
| 0x60 | `private Mesh m_meshOriginal;` |
| 0x68 | `private bool m_bUseEdgeLength;` |
| 0x69 | `private bool m_bUseCurvature;` |
| 0x6A | `private bool m_bProtectTexture;` |
| 0x6B | `private bool m_bLockBorder;` |

Properties: `public static bool kLE { get; set; }`; `public static int syH { get; set; }`; `public bool kLA { get; set; }`; `public bool syi { get; set; }`; `public bool syw { get; set; }`; `public bool syJ { get; set; }`; `public bool syX { get; set; }`

<details><summary>methods (35)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36DB368 | 0x2DF0E6C |  | `public static bool get_kLE()` |
| 0x36DB3B0 | 0x2DF0E74 |  | `public static void set_kLE(bool value)` |
| 0x36DB400 | 0x2DF0E78 |  | `public static int get_syH()` |
| 0x36DB448 | 0x2DF0E80 |  | `public static void set_syH(int value)` |
| 0x36DB494 | 0x2DF0E84 |  | `public bool get_kLA()` |
| 0x36DB49C | 0x2DF0E8C |  | `public void set_kLA(bool value)` |
| 0x36DB4A8 | 0x2DF0E90 |  | `public bool get_syi()` |
| 0x36DB4B0 | 0x2DF0E98 |  | `public void set_syi(bool value)` |
| 0x36DB4BC | 0x2DF0E9C |  | `public bool get_syw()` |
| 0x36DB4C4 | 0x2DF0EA4 |  | `public void set_syw(bool value)` |
| 0x36DB4D0 | 0x2DF0EA8 |  | `public bool get_syJ()` |
| 0x36DB4D8 | 0x2DF0EB0 |  | `public void set_syJ(bool value)` |
| 0x36DB4E4 | 0x2DF0EB4 |  | `public bool get_syX()` |
| 0x36DB4EC | 0x2DF0EBC |  | `public void set_syX(bool value)` |
| 0x36D7F90 | 0x2DF0EC0 |  | `public IEnumerator Fbo(GameObject e, Mesh f, RelevanceSphere[] F, string d = "", Simplifier.ProgressDelegate c)` |
| 0x36D8684 | 0x2DF0EC8 |  | `public IEnumerator Fby(GameObject e, Mesh f, int F, string d = "", Simplifier.ProgressDelegate c)` |
| 0x36DB548 | 0x2DF0ED0 |  | `public int Fbz()` |
| 0x36DB550 | 0x2DF0ED8 |  | `public int Fbh()` |
| 0x36DB590 | 0x2DF0EE0 |  | `public static Vector3[] FbB(GameObject e)` |
| 0x36DBD40 | 0x2DF0EE8 |  | `private IEnumerator Fbm(GameObject e, Mesh f, Mesh F, Simplifier.uE[] d, Vector3[] c, string U = "", Simplifier.ProgressDelegate Y)` |
| 0x36DBE50 | 0x2DF0EF0 |  | `private int FbR(int e, int f)` |
| 0x36DBEE0 | 0x2DF0EF8 |  | `private float Fbb(Simplifier.uA e, Simplifier.uA f, float F)` |
| 0x36DC578 | 0x2DF0F00 |  | `private void Fbl(Simplifier.uA e, Transform f, RelevanceSphere[] F)` |
| - | 0x2DF0F04 |  | `private IEnumerator Fbx(string e, Transform f, RelevanceSphere[] F, Simplifier.ProgressDelegate d)` |
| 0x36DC97C | 0x2DF0F0C |  | `private void FbK(Simplifier.uA e, Simplifier.uA f, bool F, Transform d, RelevanceSphere[] c)` |
| 0x36DD820 | 0x2DF0F10 |  | `private void FbG(List<Vector3> e, List<Vector3> f, List<MeshUniqueVertices.SerializableBoneWeight> F)` |
| 0x36DDBC8 | 0x2DF0F14 |  | `private void FbP(int e, List<int> f, int[] F, Vector2[] d)` |
| 0x36DE2E4 | 0x2DF0F18 |  | `private void FbD(Vector2[] e, Simplifier.uW f)` |
| 0x36DE4A8 | 0x2DF0F1C |  | `private Simplifier.uA Fbn()` |
| 0x36DE550 | 0x2DF0F24 |  | `private float FbV(int e)` |
| 0x36DD508 | 0x2DF0F2C |  | `private void Fbg(int e)` |
| 0x36DD680 | 0x2DF0F30 |  | `private void Fbp(int e)` |
| 0x36DE5FC | 0x2DF0F34 |  | `private void Fbv(Simplifier.uA e)` |
| 0x36DE4AC | 0x2DF0F38 |  | `private Simplifier.uA FbS()` |
| 0x36DE6C0 | 0x2DF0F40 |  | `public void .ctor()` |

</details>
