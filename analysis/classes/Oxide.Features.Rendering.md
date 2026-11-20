# namespace `Oxide.Features.Rendering`  (13 types)

### public class `FrostRenderPass` : ScriptableRendererFeature  
`TypeDefIndex 3101`

| offset | field |
|---|---|
| 0x20 | `private FrostRenderPass.FrostSettings settings;` |
| 0x28 | `private FrostRenderPass.of frostPass;` |
| 0x0 | `private static bool isActive;` |
| 0x4 | `private static float intensity;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A571AC | 0x2E9A510 | 5 | `public override void Create()` |
| 0x3A57394 | 0x2E9A6E8 | 7 | `public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)` |
| 0x3A5750C | 0x2E9A84C | 11 | `protected override void Dispose(bool disposing)` |
| 0x3A57564 | 0x2E9A850 |  | `public static void cMF(float e)` |
| 0x3A575C4 | 0x2E9A8B0 |  | `public void .ctor()` |

</details>

### public static class `GrassShaderSwap`  
`TypeDefIndex 3104`

| offset | field |
|---|---|
| - | `private const string LitShader = "Universal Render Pipeline/Lit";` |
| - | `private static Shader fast;` |
| - | `private static GrassAmbientFeed feed;` |
| - | `private static GrassShaderSwap.Profile brightness;` |
| - | `private static readonly Dictionary<Tuple<Material, float>, Material> matched;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9ADF0 |  | `private static float Gain(string name)` |
| - | 0x2E9B050 |  | `public static void Apply()` |
| - | 0x2E9C038 |  | `private static void .cctor()` |

</details>

### public sealed class `GrassAmbientFeed` : MonoBehaviour  
`TypeDefIndex 3105`

| offset | field |
|---|---|
| - | `private static readonly int AmbientId;` |
| - | `private static readonly int CascadesId;` |
| - | `private int previousCascades;` |
| - | `private readonly Vector3[] up;` |
| - | `private readonly Color[] result;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9C0D0 |  | `private void LateUpdate()` |
| - | 0x2E9BE74 |  | `public void UpdateLighting()` |
| - | 0x2E9C0D4 |  | `public void .ctor()` |
| - | 0x2E9C1D0 |  | `private static void .cctor()` |

</details>

### public sealed class `GuiCameraSwitch` : MonoBehaviour  
`TypeDefIndex 3106`

| offset | field |
|---|---|
| - | `private const int OverlayOrder = -100;` |
| - | `private Camera guiCamera;` |
| - | `private Canvas canvas;` |
| - | `private UniversalAdditionalCameraData world;` |
| - | `private int cameraOrder;` |
| - | `private Nullable<bool> cameraMode;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9C26C |  | `public static void Attach(Camera guiCamera, UniversalAdditionalCameraData world)` |
| - | 0x2E9C4C4 |  | `private void LateUpdate()` |
| - | 0x2E9C84C |  | `public void .ctor()` |

</details>

### public sealed class `LocalPlayerShadow` : MonoBehaviour  
`TypeDefIndex 3107`

| offset | field |
|---|---|
| - | `private const float SettingInterval = 0.5;` |
| - | `private readonly List<Renderer> renderers;` |
| - | `private readonly List<Collider> colliders;` |
| - | `private readonly List<LODGroup> lodGroups;` |
| - | `private float nextSetting;` |
| - | `private int settingsRevision;` |
| - | `private bool shadows;` |
| - | `private GameObject body;` |
| - | `private static LocalPlayerShadow instance;` |
| - | `public static bool ShowBody;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9C854 |  | `private static void ResetInstance()` |
| - | 0x2E9C8B8 |  | `private static void Install()` |
| - | 0x2E9C8BC |  | `public static void EnsureInstalled()` |
| - | 0x2E9CAA4 |  | `private void OnEnable()` |
| - | 0x2E9CF28 |  | `private void OnDisable()` |
| - | 0x2E9CB70 |  | `private void LateUpdate()` |
| - | 0x2E9D620 |  | `private static void OwnBody(PlayerManager player, bool on)` |
| - | 0x2E9D784 |  | `private void BeforeRendering(ScriptableRenderContext context, List<Camera> cameras)` |
| - | 0x2E9CFCC |  | `private void Enforce()` |
| - | 0x2E9D810 |  | `public void .ctor()` |

</details>

### public static class `MonumentProxy`  
`TypeDefIndex 3108`

| offset | field |
|---|---|
| - | `private static readonly Dictionary<string, MonumentProxySet> sets;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9D948 |  | `private static Transform ByIndices(Transform t, string path)` |
| - | 0x2E9DA24 |  | `public static void Attach(GameObject monument, string prefabName)` |
| - | 0x2E9E1B0 |  | `private static void .cctor()` |

</details>

### public sealed class `MonumentProxySet` : ScriptableObject  
`TypeDefIndex 3109`

| offset | field |
|---|---|
| - | `public string monument;` |
| - | `public Mesh[] meshes;` |
| - | `public Material[] materials;` |
| - | `public float[] heights;` |
| - | `public string[] rendererPaths;` |
| - | `public Vector3 center;` |
| - | `public float size;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9E248 |  | `public void .ctor()` |

</details>

### public class `QualitySetupController` : MonoBehaviour  
`TypeDefIndex 3110`

| offset | field |
|---|---|
| 0x20 | `private List<Object> objectsByQuality;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A57CC8 | 0x2E9E250 |  | `private void Awake()` |
| 0x3A57DDC | 0x2E9E3A0 |  | `public void .ctor()` |

</details>

### public class `RadiationRenderPass` : ScriptableRendererFeature  
`TypeDefIndex 3113`

| offset | field |
|---|---|
| 0x20 | `private Shader shader;` |
| 0x28 | `private RadiationRenderPass.RadiationEffectSettings settings;` |
| 0x30 | `private RadiationRenderPass.oF pass;` |
| 0x38 | `private Material material;` |
| 0x0 | `private static float intensity;` |
| 0x4 | `private static bool isActive;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A57DE4 | 0x2E9E3A8 | 5 | `public override void Create()` |
| 0x3A58058 | 0x2E9E6B0 | 7 | `public override void AddRenderPasses(ScriptableRenderer renderer, ref RenderingData renderingData)` |
| 0x3A5822C | 0x2E9E864 | 11 | `protected override void Dispose(bool disposing)` |
| 0x3A58284 | 0x2E9E8D0 |  | `public static void cMc(float e)` |
| 0x3A582E4 | 0x2E9E930 |  | `public void .ctor()` |

</details>

### public static class `SettingsSliderStyle`  
`TypeDefIndex 3115`

| offset | field |
|---|---|
| - | `private static readonly Color Gold;` |
| - | `private static readonly Color Plate;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E9EF60 |  | `public static void Install(SettingsManager settings)` |
| - | 0x2E9FAA4 |  | `private static RectTransform Rect(string name, Transform parent, float left, float right, float height)` |
| - | 0x2E9FCA0 |  | `private static Image Image(RectTransform rect, Color color)` |
| - | 0x2E9F1BC |  | `private static void Apply(Yv view)` |
| - | 0x2E9FD4C |  | `private static void AddButton(RectTransform root, Yv view, bool plus)` |
| - | 0x2EA01F8 |  | `private static void .cctor()` |

</details>

### public static class `ShadowSettings`  
`TypeDefIndex 3117`

| offset | field |
|---|---|
| - | `public const string Prefix = "shadow_";` |
| - | `public static readonly int[] Resolutions;` |
| - | `private static readonly Dictionary<UniversalRenderPipelineAsset, UniversalRenderPipelineAsset> copies;` |
| - | `private static readonly Dictionary<int, RenderPipelineAsset> originals;` |
| - | `private static readonly Dictionary<string, FieldInfo> fields;` |
| - | `private static bool savePending;` |
| - | `private static float saveAt;` |
| - | `private static int filtering;` |
| - | `private static int <Revision>k__BackingField;` |
| - | `private static float <Strength>k__BackingField;` |
| - | `private static bool <LocalPlayerEnabled>k__BackingField;` |

Properties: `public static int Revision { get; set; }`; `public static float Strength { get; set; }`; `public static bool LocalPlayerEnabled { get; set; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EA0320 |  | `public static int get_Revision()` |
| - | 0x2EA0378 |  | `private static void set_Revision(int value)` |
| - | 0x2EA03D4 |  | `public static float get_Strength()` |
| - | 0x2EA042C |  | `private static void set_Strength(float value)` |
| - | 0x2EA0490 |  | `public static bool get_LocalPlayerEnabled()` |
| - | 0x2EA04E8 |  | `private static void set_LocalPlayerEnabled(bool value)` |
| - | 0x2EA0548 |  | `public static ShadowSettings.Values Preset(int index)` |
| - | 0x2EA0628 |  | `public static ShadowSettings.Values Read()` |
| - | 0x2EA09A4 |  | `public static void SetPreset(int index)` |
| - | 0x2EA0CE4 |  | `public static void Set(string key, int value)` |
| - | 0x2EA0BDC |  | `private static void Write(string key, int value)` |
| - | 0x2EA0C40 |  | `private static void Commit()` |
| - | 0x2EA0DB4 |  | `internal static void Save(bool force = false)` |
| - | 0x2EA0E74 |  | `private static void Field(UniversalRenderPipelineAsset asset, string name, object value)` |
| - | 0x2EA1100 |  | `public static UniversalRenderPipelineAsset Apply(UniversalRenderPipelineAsset pipeline, bool enabled)` |
| - | 0x2EA1B80 |  | `internal static void ApplyLight(Light light)` |
| - | 0x2EA1CF0 |  | `internal static void Restore()` |
| - | 0x2EA2104 |  | `private static void Reset()` |
| - | 0x2EA2230 |  | `private static void Install()` |
| - | 0x2EA22F4 |  | `private static void .cctor()` |

</details>

### public sealed class `ShadowSettingsRuntime` : MonoBehaviour  
`TypeDefIndex 3118`

| offset | field |
|---|---|
| - | `private Light sun;` |
| - | `private PlayerManager localPlayer;` |
| - | `private float nextLightUpdate;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EA24BC |  | `private void OnEnable()` |
| - | 0x2EA2560 |  | `private void Start()` |
| - | 0x2EA25B0 |  | `private void Loaded(Scene scene, LoadSceneMode mode)` |
| - | 0x2EA2608 |  | `private void LateUpdate()` |
| - | 0x2EA2908 |  | `private void OnApplicationPause(bool paused)` |
| - | 0x2EA2970 |  | `private void OnApplicationQuit()` |
| - | 0x2EA29BC |  | `private void OnDestroy()` |
| - | 0x2EA2A88 |  | `public void .ctor()` |

</details>

### public sealed class `ShadowSettingsPanel` : MonoBehaviour  
`TypeDefIndex 3127`

| offset | field |
|---|---|
| - | `private static readonly Color Gold;` |
| - | `private static readonly Color Ink;` |
| - | `private static readonly Color Plate;` |
| - | `private static readonly Color White;` |
| - | `private static readonly Color Muted;` |
| - | `private static readonly List<ShadowSettingsPanel> instances;` |
| - | `private readonly List<Action<ShadowSettings.Values>> bindings;` |
| - | `private readonly List<Action> captions;` |
| - | `private SettingsManager owner;` |
| - | `private Font font;` |
| - | `private GameObject details;` |
| - | `private CanvasGroup detailControls;` |
| - | `private ScrollRect scroll;` |
| - | `private string language;` |
| - | `private float nextLanguageCheck;` |

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EA2A90 |  | `private static string L(string ru, string en)` |
| - | 0x2EA2B1C |  | `public static void Ensure(SettingsManager settings)` |
| - | 0x2EA61B8 |  | `public static void RefreshExisting(SettingsManager settings)` |
| - | 0x2EA3BF4 |  | `private void Build()` |
| - | 0x2EA7D98 |  | `private string[] PresetNames()` |
| - | 0x2EA7F6C |  | `private void Set(string key, int value)` |
| - | 0x2EA7FDC |  | `private void Toggle(GameObject target)` |
| - | 0x2EA808C |  | `private void Layout()` |
| - | 0x2EA5D3C |  | `private void Refresh()` |
| - | 0x2EA827C |  | `private void OnEnable()` |
| - | 0x2EA8310 |  | `private void Update()` |
| - | 0x2EA83C0 |  | `private void OnDisable()` |
| - | 0x2EA8410 |  | `private void OnDestroy()` |
| - | 0x2EA8490 |  | `private static void ResetInstances()` |
| - | 0x2EA77F8 |  | `private GameObject Segments(Transform parent, Func<string> title, Func<string> hint, Func<string[]> names, Func<ShadowSettings.Values, int> get, Action<int> set)` |
| - | 0x2EA6CFC |  | `private void SliderRow(Transform parent, Func<string> title, Func<string> hint, string key, int min, int max, int step, Func<ShadowSettings.Values, int> get, Func<int, string> format)` |
| - | 0x2EA3978 |  | `private static RectTransform Rect(string name, Transform parent)` |
| - | 0x2EA3B00 |  | `private static void Stretch(RectTransform rect)` |
| - | 0x2EA6AE8 |  | `private static void Height(Transform target, float height)` |
| - | 0x2EA6BFC |  | `private static RectTransform Vertical(Transform parent, string name, float spacing)` |
| - | 0x2EA668C |  | `private static RectTransform FixedRow(Transform parent, string name, float height)` |
| - | 0x2EA63DC |  | `private Text Label(Transform parent, Func<string> caption, int size, Color color, float height)` |
| - | 0x2EA67A0 |  | `private Button Button(Transform parent, string name, Func<string> caption, Action click)` |
| - | 0x2EA8550 |  | `private static void Selected(Button button, Text text, bool on)` |
| - | 0x2EA86A8 |  | `public void .ctor()` |
| - | 0x2EA8784 |  | `private static void .cctor()` |

</details>
