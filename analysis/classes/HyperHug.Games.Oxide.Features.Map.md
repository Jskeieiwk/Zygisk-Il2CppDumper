# namespace `HyperHug.Games.Oxide.Features.Map`  (7 types)

### public abstract class `MapDetailsConfigBase` : ScriptableObject, jm, IDisposable  
`TypeDefIndex 3624`

Properties: `public abstract string sPW { get; }`; `public abstract Sprite MapSprite { get; set; }`; `public abstract Vector2 CorrectionOffset { get; set; }`; `public abstract float CorrectionScale { get; set; }`; `public bool sPE { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract string get_sPW();` |
| - | - |  | `public abstract Sprite get_MapSprite();` |
| - | - |  | `protected abstract void set_MapSprite(Sprite value);` |
| - | - |  | `public abstract Vector2 get_CorrectionOffset();` |
| - | - |  | `protected abstract void set_CorrectionOffset(Vector2 value);` |
| - | - |  | `public abstract float get_CorrectionScale();` |
| - | - |  | `protected abstract void set_CorrectionScale(float value);` |
| 0x38830C0 | 0x2F5B6A0 | 8 | `public bool get_sPE()` |
| 0x38830C8 | 0x2F5B6A8 | 9 | `public void Dispose()` |
| 0x38830CC | 0x2F5B6AC |  | `protected void .ctor()` |

</details>

### public class `MapDetailsConfigDesigned` : MapDetailsConfigBase  
`TypeDefIndex 3625`

| offset | field |
|---|---|
| 0x18 | `private jb mapType;` |
| 0x20 | `private MapNamesInfo mapNamesInfo;` |
| - | `private Sprite <MapSprite>k__BackingField;` |
| - | `private Vector2 <CorrectionOffset>k__BackingField;` |
| - | `private float <CorrectionScale>k__BackingField;` |

Properties: `public override string sPW { get; }`; `public override Sprite MapSprite { get; set; }`; `public override Vector2 CorrectionOffset { get; set; }`; `public override float CorrectionScale { get; set; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38831DC | 0x2F5B6B4 | 10 | `public override string get_sPW()` |
| - | 0x2F5B6BC |  | `public override Sprite get_MapSprite()` |
| - | 0x2F5B6C4 |  | `protected override void set_MapSprite(Sprite value)` |
| - | 0x2F5B6CC |  | `public override Vector2 get_CorrectionOffset()` |
| - | 0x2F5B6D4 |  | `protected override void set_CorrectionOffset(Vector2 value)` |
| - | 0x2F5B6DC |  | `public override float get_CorrectionScale()` |
| - | 0x2F5B6E4 |  | `protected override void set_CorrectionScale(float value)` |
| 0x38832B8 | 0x2F5B6EC |  | `public void .ctor()` |

</details>

### public class `MapInstaller` : ScriptableObjectInstaller  
`TypeDefIndex 3626`

| offset | field |
|---|---|
| 0x20 | `private MapNamesInfo mapNamesInfo;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38832C0 | 0x2F5B6F4 | 6 | `public override void FSz()` |
| 0x38833A0 | 0x2F5B6F8 |  | `private void dDv()` |
| 0x38834BC | 0x2F5B6FC |  | `private void dDS()` |
| 0x3883578 | 0x2F5B700 |  | `public void .ctor()` |

</details>

### public class `MapNamesInfo` : ScriptableObject  
`TypeDefIndex 3628`

Properties: `public MapNamesInfo.MapNamesInfoItem[] MapNamesInfoItems { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3883580 | 0x2F5B708 |  | `public MapNamesInfo.MapNamesInfoItem[] get_MapNamesInfoItems()` |
| 0x3883588 | 0x2F5B710 |  | `private void set_MapNamesInfoItems(MapNamesInfo.MapNamesInfoItem[] value)` |
| 0x3883590 | 0x2F5B714 |  | `public string dDI(string e)` |
| 0x3883648 | 0x2F5B71C |  | `public string dDM(string e)` |
| 0x3883784 | 0x2F5B724 |  | `public static bool dne(string e)` |
| 0x38837E8 | 0x2F5B72C |  | `public void .ctor()` |

</details>

### public sealed class `SceneReferencesDesigned` : jx  
`TypeDefIndex 3629`

| offset | field |
|---|---|
| 0x20 | `private MapDetailsConfigBase mapDetailsConfig;` |
| - | `private ag <BuildingsCollection>k__BackingField;` |
| - | `private BaseSurfaceDatabase <SurfaceDatabase>k__BackingField;` |

Properties: `public override Terrain Terrain { get; set; }`; `public override jm sPA { get; set; }`; `public override ag BuildingsCollection { get; set; }`; `public override BaseSurfaceDatabase SurfaceDatabase { get; set; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5B73C |  | `public override Terrain get_Terrain()` |
| - | 0x2F5B744 |  | `protected override void set_Terrain(Terrain value)` |
| - | 0x2F5B748 |  | `public override jm get_sPA()` |
| - | 0x2F5B750 |  | `protected override void set_sPA(jm value)` |
| - | 0x2F5B80C |  | `public override ag get_BuildingsCollection()` |
| - | 0x2F5B814 |  | `protected override void set_BuildingsCollection(ag value)` |
| - | 0x2F5B81C |  | `public override BaseSurfaceDatabase get_SurfaceDatabase()` |
| - | 0x2F5B824 |  | `protected override void set_SurfaceDatabase(BaseSurfaceDatabase value)` |
| 0x3884208 | 0x2F5B82C |  | `public void .ctor()` |

</details>

### public sealed class `SceneReferencesProcedural` : jx  
`TypeDefIndex 3630`

| offset | field |
|---|---|
| 0x28 | `private jm _003COAf_003Ek__BackingField;` |
| - | `private jm <sPA>k__BackingField;` |
| - | `private ag <BuildingsCollection>k__BackingField;` |
| - | `private BaseSurfaceDatabase <SurfaceDatabase>k__BackingField;` |

Properties: `public override Terrain Terrain { get; set; }`; `public override jm sPA { get; set; }`; `public override ag BuildingsCollection { get; set; }`; `public override BaseSurfaceDatabase SurfaceDatabase { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5B834 |  | `public override Terrain get_Terrain()` |
| - | 0x2F5B83C |  | `protected override void set_Terrain(Terrain value)` |
| - | 0x2F5B840 |  | `public override jm get_sPA()` |
| - | 0x2F5B848 |  | `protected override void set_sPA(jm value)` |
| - | 0x2F5B850 |  | `public override ag get_BuildingsCollection()` |
| - | 0x2F5B858 |  | `protected override void set_BuildingsCollection(ag value)` |
| - | 0x2F5B860 |  | `public override BaseSurfaceDatabase get_SurfaceDatabase()` |
| - | 0x2F5B868 |  | `protected override void set_SurfaceDatabase(BaseSurfaceDatabase value)` |
| 0x3884250 | 0x2F5B870 |  | `public void dnY(Terrain e, jm f, ag F, BaseSurfaceDatabase d)` |
| 0x38842C0 | 0x2F5B8C8 |  | `public void .ctor()` |

</details>

### public sealed class `WorldSetUpContextHybrid` : jK  
`TypeDefIndex 3631`

| offset | field |
|---|---|
| 0x20 | `private jx links;` |

Properties: `private jx sPr { get; }`; `public override ag sPu { get; set; }`; `public override Terrain sPk { get; set; }`; `public override jm sPO { get; set; }`; `public override BaseSurfaceDatabase sPt { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5B8D0 |  | `private jx get_sPr()` |
| - | 0x2F5B9FC |  | `public override ag get_sPu()` |
| - | 0x2F5BA94 |  | `protected override void set_sPu(ag value)` |
| - | 0x2F5BA98 |  | `public override Terrain get_sPk()` |
| - | 0x2F5BB30 |  | `protected override void set_sPk(Terrain value)` |
| - | 0x2F5BB34 |  | `public override jm get_sPO()` |
| - | 0x2F5BBCC |  | `protected override void set_sPO(jm value)` |
| - | 0x2F5BBD0 |  | `public override BaseSurfaceDatabase get_sPt()` |
| - | 0x2F5BC68 |  | `protected override void set_sPt(BaseSurfaceDatabase value)` |
| 0x388440C | 0x2F5BC6C |  | `public void dnq(jx e)` |
| 0x3884414 | 0x2F5BC74 |  | `public void .ctor()` |

</details>
