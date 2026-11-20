# namespace `AmplifyImpostors`  (5 types)

### public class `AmplifyImpostor` : MonoBehaviour  
`TypeDefIndex 4042`

| offset | field |
|---|---|
| - | `private const string kzL = "e82933f4c0eb9ba42aab0739f48efe21";` |
| - | `private const string kzo = "57c23892d43bc9f458360024c5985405";` |
| - | `private const string kzy = "31bd3cd74692f384a916d9d7ea87710d";` |
| - | `private const string kzz = "572f9be5706148142b8da6e9de53acdb";` |
| - | `private const string kzh = "e4786beb7716da54dbb02a632681cc37";` |
| - | `private const string kzB = "089f3a2f6b5f48348a48c755f8d9a7a2";` |
| - | `private const string kzm = "94e2ddcdfb3257a43872042f97e2fb01";` |
| - | `private const string kzR = "990451a2073f6994ebf9fd6f90a842b3";` |
| - | `private const string kzb = "47b6b3dcefe0eaf4997acf89caf8c75e";` |
| - | `private const string kzl = "56236dc63ad9b7949b63a27f0ad180b3";` |
| - | `private const string kzx = "175c951fec709c44fa2f26b8ab78b8dd";` |
| - | `private const string kzK = "0403878495ffa3c4e9d4bcb3eac9b559";` |
| - | `private const string kzG = "83dd8de9a5c14874884f9012def4fdcc";` |
| - | `private const string kzP = "da79d698f4bf0164e910ad798d07efdf";` |
| 0x20 | `private AmplifyImpostorAsset m_data;` |
| 0x28 | `private Transform m_rootTransform;` |
| 0x30 | `private LODGroup m_lodGroup;` |
| 0x38 | `private Renderer[] m_renderers;` |
| 0x40 | `public ub m_lodReplacement;` |
| 0x44 | `public uK m_renderPipelineInUse;` |
| 0x48 | `public int m_insertIndex;` |
| 0x50 | `public GameObject m_lastImpostor;` |
| 0x58 | `public string m_folderPath;` |
| 0x60 | `public string m_impostorName;` |
| 0x68 | `public ul m_cutMode;` |
| - | `private const float kzD = -90;` |
| - | `private const float kzn = 90;` |
| - | `private const int kzV = 256;` |
| 0x70 | `private RenderTexture[] kzg;` |
| 0x78 | `private RenderTexture[] kzp;` |
| 0x80 | `private RenderTexture kzv;` |
| 0x88 | `public Texture2D m_alphaTex;` |
| 0x90 | `private float kzS;` |
| 0x94 | `private float kzI;` |
| 0x98 | `private Vector2 kzM;` |
| 0xA0 | `private Bounds khe;` |
| 0xB8 | `private Vector3 khf;` |
| 0xC4 | `private Quaternion khF;` |
| 0xD4 | `private Vector3 khd;` |
| - | `private const int khc = 65536;` |

Properties: `public AmplifyImpostorAsset sBC { get; set; }`; `public Transform sBZ { get; set; }`; `public LODGroup sBj { get; set; }`; `public Renderer[] sBa { get; set; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x370D860 | 0x2F89E34 |  | `public AmplifyImpostorAsset get_sBC()` |
| 0x370D868 | 0x2F89E3C |  | `public void set_sBC(AmplifyImpostorAsset value)` |
| 0x370D870 | 0x2F89E40 |  | `public Transform get_sBZ()` |
| 0x370D878 | 0x2F89E48 |  | `public void set_sBZ(Transform value)` |
| 0x370D880 | 0x2F89E4C |  | `public LODGroup get_sBj()` |
| 0x370D888 | 0x2F89E54 |  | `public void set_sBj(LODGroup value)` |
| 0x370D890 | 0x2F89E58 |  | `public Renderer[] get_sBa()` |
| 0x370D898 | 0x2F89E60 |  | `public void set_sBa(Renderer[] value)` |
| 0x370D8A0 | 0x2F89E64 |  | `private void FpH(List<TextureOutput> e, bool f)` |
| 0x370DE74 | 0x2F89E68 |  | `private void Fpi(List<TextureOutput> e)` |
| 0x370E048 | 0x2F89E6C |  | `private void Fpw()` |
| 0x370E0C4 | 0x2F89E70 |  | `private void FpJ()` |
| 0x370E140 | 0x2F89E74 |  | `public void FpX(uG e, int f, bool F = true, bool d = false, bool c = false, Shader U)` |
| 0x370FEC4 | 0x2F89E78 |  | `private Matrix4x4 FpT(uG e, int f, int F, int d, int c)` |
| 0x37104D4 | 0x2F89E88 |  | `private Vector3 FpL(Vector2 e)` |
| 0x37102D0 | 0x2F89E98 |  | `private Vector3 Fpo(float e, float f)` |
| 0x37103E8 | 0x2F89EA8 |  | `private Vector3 Fpy(float e, float f)` |
| 0x37105EC | 0x2F89EB8 |  | `public void Fpz(AmplifyImpostorAsset e)` |
| 0x37114FC | 0x2F89EBC |  | `public Mesh Fph(Vector2[] e, Vector3 f, float F = 1, float d = 1, bool c = true)` |
| 0x3711CB8 | 0x2F89EC4 |  | `public void .ctor()` |

</details>

### public class `AmplifyImpostorAsset` : ScriptableObject  
`TypeDefIndex 4043`

| offset | field |
|---|---|
| 0x18 | `public Material Material;` |
| 0x20 | `public Mesh Mesh;` |
| 0x28 | `public int Version;` |
| 0x2C | `public uG ImpostorType;` |
| 0x30 | `public bool LockedSizes;` |
| 0x34 | `public int SelectedSize;` |
| 0x38 | `public Vector2 TexSize;` |
| 0x40 | `public bool DecoupleAxisFrames;` |
| 0x44 | `public int HorizontalFrames;` |
| 0x48 | `public int VerticalFrames;` |
| 0x4C | `public int PixelPadding;` |
| 0x50 | `public int MaxVertices;` |
| 0x54 | `public float Tolerance;` |
| 0x58 | `public float NormalScale;` |
| 0x60 | `public Vector2[] ShapePoints;` |
| 0x68 | `public AmplifyImpostorBakePreset Preset;` |
| 0x70 | `public List<TextureOutput> OverrideOutput;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3711E0C | 0x2F89ECC |  | `public void .ctor()` |

</details>

### public class `AmplifyImpostorBakePreset` : ScriptableObject  
`TypeDefIndex 4044`

| offset | field |
|---|---|
| 0x18 | `public Shader BakeShader;` |
| 0x20 | `public Shader RuntimeShader;` |
| 0x28 | `public uI Pipeline;` |
| 0x2C | `public int AlphaIndex;` |
| 0x30 | `public List<TextureOutput> Output;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3712188 | 0x2F89ED4 |  | `public void .ctor()` |

</details>

### public class `TextureOutput`  
`TypeDefIndex 4045`

| offset | field |
|---|---|
| 0x10 | `public int Index;` |
| 0x14 | `public uS OverrideMask;` |
| 0x18 | `public bool Active;` |
| 0x20 | `public string Name;` |
| 0x28 | `public uv Scale;` |
| 0x2C | `public bool SRGB;` |
| 0x30 | `public uV Channels;` |
| 0x34 | `public ug Compression;` |
| 0x38 | `public un ImageFormat;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3711FA0 | 0x2F89EDC |  | `public void .ctor()` |
| 0x371201C | 0x2F89EE4 |  | `public void .ctor(bool a, string n, uv s, bool sr, uV c, ug nc, un i)` |
| 0x3712108 | 0x2F89EEC |  | `public TextureOutput FpB()` |

</details>

### public class `VersionInfo`  
`TypeDefIndex 4046`

| offset | field |
|---|---|
| - | `public const byte Major = 0;` |
| - | `public const byte Minor = 9;` |
| - | `public const byte Release = 7;` |
| 0x0 | `public static byte Revision;` |

Properties: `public static int sBi { get; }`; `public static string sBw { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3716A54 | 0x2F89EF4 |  | `public static int get_sBi()` |
| 0x3716AB4 | 0x2F89EFC |  | `public static string get_sBw()` |
| 0x37168D4 | 0x2F89F04 |  | `public static string Fvc()` |
| 0x3716B58 | 0x2F89F0C |  | `public void .ctor()` |

</details>
