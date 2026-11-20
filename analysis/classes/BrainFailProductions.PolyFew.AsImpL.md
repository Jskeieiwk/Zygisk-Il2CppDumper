# namespace `BrainFailProductions.PolyFew.AsImpL`  (3 types)

### public class `ImportOptions`  
`TypeDefIndex 4000`

| offset | field |
|---|---|
| 0x10 | `public bool zUp;` |
| 0x11 | `public bool litDiffuse;` |
| 0x12 | `public bool convertToDoubleSided;` |
| 0x14 | `public float modelScaling;` |
| 0x18 | `public bool reuseLoaded;` |
| 0x19 | `public bool inheritLayer;` |
| 0x1A | `public bool buildColliders;` |
| - | `Note: it could not work for meshes with too many smooth surface regions.")]` |
| 0x1B | `public bool colliderConvex;` |
| 0x1C | `public bool colliderTrigger;` |
| 0x1D | `public bool use32bitIndices;` |
| 0x1E | `public bool hideWhileLoading;` |
| 0x20 | `public Vector3 localPosition;` |
| - | `(Euler angles)")]` |
| 0x2C | `public Vector3 localEulerAngles;` |
| 0x38 | `([1,1,1] = no rescaling)")]` |
| - | `public Vector3 localScale;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BBE8DC | 0x2F89C98 |  | `public void .ctor()` |

</details>

### public class `ModelImportInfo`  
`TypeDefIndex 4001`

| offset | field |
|---|---|
| - | `(leave it blank to use its file name)")]` |
| 0x10 | `public string name;` |
| 0x18 | `public string path;` |
| 0x20 | `public bool skip;` |
| 0x28 | `public ImportOptions loaderOptions;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BD46D0 | 0x2F89CA0 |  | `public void .ctor()` |

</details>

### public class `MultiObjectImporter` : bi  
`TypeDefIndex 4002`

| offset | field |
|---|---|
| 0x68 | `public bool autoLoadOnStart;` |
| 0x70 | `public List<ModelImportInfo> objectsList;` |
| 0x78 | `public ImportOptions defaultImportOptions;` |
| 0x80 | `private bX pathSettings;` |

Properties: `public string Cdb { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3BD46D8 | 0x2F89CA8 |  | `public string get_Cdb()` |
| 0x3BD48CC | 0x2F89CB0 |  | `public void Uze(ModelImportInfo[] e)` |
| 0x3BD4CA4 | 0x2F89CB4 | 10 | `protected virtual void Start()` |
| 0x3BD4D14 | 0x2F89CB8 |  | `public void .ctor()` |

</details>
