# namespace `HyperHug.Games.Oxide.Features.Map.Procedural`  (12 types)

### internal struct `CatalogResult`  
`TypeDefIndex 3632`

| offset | field |
|---|---|
| 0x0 | `public bool Success;` |
| 0x8 | `public string Error;` |
| 0x10 | `public IResourceLocator Result;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3884610 | 0x2F5BC7C |  | `public static CatalogResult dna(IResourceLocator e)` |
| 0x38846B0 | 0x2F5BC88 |  | `public static CatalogResult dnQ(string e)` |

</details>

### public struct `CatalogSaveInfo`  
`TypeDefIndex 3633`

| offset | field |
|---|---|
| 0x0 | `public string mapKey;` |
| 0x8 | `public string server;` |

### internal struct `DownloadStatus`  
`TypeDefIndex 3635`

| offset | field |
|---|---|
| 0x0 | `public bool Success;` |
| 0x8 | `public string ErrorText;` |
| 0x10 | `public DownloadStatus.aE Error;` |
| 0x18 | `public long FreeSizeBytes;` |
| 0x20 | `public long BundleSizeBytes;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3895574 | 0x2F5BC94 |  | `public static DownloadStatus dgF()` |
| 0x3895600 | 0x2F5BCB8 |  | `public static DownloadStatus dgd(string e)` |
| 0x3895650 | 0x2F5BD08 |  | `public static DownloadStatus dgc(long e, long f)` |

</details>

### public struct `MapBundlesSAveInfo`  
`TypeDefIndex 3636`

| offset | field |
|---|---|
| 0x0 | `public string mapId;` |
| 0x8 | `public bool loaded;` |

### public sealed class `NoSpaceException` : Exception  
`TypeDefIndex 3637`

Properties: `public override string Message { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38A8A78 | 0x2F5BD20 | 5 | `public override string get_Message()` |
| 0x38A8A80 | 0x2F5BD28 |  | `public void .ctor(long free, long toDownload)` |

</details>

### public sealed class `NotEnoughSpaceWarningDelegate` : MulticastDelegate  
`TypeDefIndex 3638`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5BD80 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F5BE20 |  | `public virtual void Invoke(long freeSizeBytes, long bundleSizeBytes)` |
| - | 0x2F5BE34 |  | `public virtual IAsyncResult BeginInvoke(long freeSizeBytes, long bundleSizeBytes, AsyncCallback callback, object object)` |
| - | 0x2F5BED0 |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public struct `OutdatedMapBundlesSAveInfo`  
`TypeDefIndex 3639`

| offset | field |
|---|---|
| 0x0 | `public string catalogUrl;` |

### public struct `ServerBundleDescription`  
`TypeDefIndex 3640`

| offset | field |
|---|---|
| 0x0 | `public string Id;` |
| 0x8 | `public string ProceduralMapCatalogUrl;` |
| 0x10 | `public string ProceduralMapId;` |
| 0x18 | `public bool Maintenance;` |

### public struct `ServerBundleStateInfo`  
`TypeDefIndex 3641`

| offset | field |
|---|---|
| 0x0 | `public az State;` |
| 0x4 | `public float Progress;` |

### public class `UiDownloadMapErrorWindow` : MonoBehaviour  
`TypeDefIndex 3643`

| offset | field |
|---|---|
| - | `private bool requested;` |
| 0x20 | `private Canvas canvas;` |
| 0x28 | `private Button okButton;` |
| 0x30 | `private Button backgroundButton;` |
| 0x38 | `private Text bodyText;` |
| 0x40 | `private Text headerText;` |
| 0x48 | `private jI OOp;` |
| 0x50 | `private readonly Dictionary<string, string> OOv;` |
| - | `private const string OOS = "ui.message.error.queue_connection_fail.common.body";` |

Properties: `private string OOI { get; set; }`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B04E0 | 0x2F5BEDC |  | `private string get_OOI()` |
| 0x38B04E8 | 0x2F5BEE4 |  | `private void set_OOI(string value)` |
| 0x38B04F0 | 0x2F5BEE8 |  | `public void dvz(jI e)` |
| 0x38B04F8 | 0x2F5BEEC |  | `private void Awake()` |
| 0x38B0700 | 0x2F5C130 |  | `private void OnEnable()` |
| 0x38B088C | 0x2F5C134 |  | `private void OnDisable()` |
| 0x38B062C | 0x2F5C138 |  | `private void dvh()` |
| 0x38B0A94 | 0x2F5C13C |  | `private void Show(string error, string key)` |
| - | 0x2F5C30C |  | `public void ShowDownloadError(string error)` |
| 0x38B060C | 0x2F5C084 |  | `private void Hide()` |
| 0x38B0BF8 | 0x2F5C49C |  | `private void Close()` |
| 0x38B0C10 | 0x2F5C4A0 |  | `private void dvB()` |
| 0x38B0C14 | 0x2F5C4A4 |  | `private void dvm(QueueErrorModel e)` |
| 0x38B0E5C | 0x2F5C510 |  | `public void .ctor()` |
| 0x38B0D60 | 0x2F5C518 |  | `private void dvR(ref UiDownloadMapErrorWindow._003C_003Ec__DisplayClass21_0 e)` |

</details>

### public class `UiDownloadMapNoSpaceWindow` : MonoBehaviour  
`TypeDefIndex 3644`

| offset | field |
|---|---|
| - | `private bool requested;` |
| 0x20 | `private Text bodyText;` |
| 0x28 | `private Canvas canvas;` |
| 0x30 | `private Button okButton;` |
| 0x38 | `private Button backgroundButton;` |
| 0x40 | `private jI OOM;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B2C9C | 0x2F5C51C |  | `public void dvb(jI e)` |
| 0x38B2CA4 | 0x2F5C520 |  | `private void Awake()` |
| 0x38B2DD0 | 0x2F5C764 |  | `private void OnEnable()` |
| 0x38B2EC4 | 0x2F5C768 |  | `private void OnDisable()` |
| 0x38B2FB8 | 0x2F5C76C |  | `public void ShowNoSpace(long e, long f)` |
| - | 0x2F5CA3C |  | `private void dvl(long e, long f)` |
| 0x38B31F8 | 0x2F5C988 |  | `private void Show()` |
| 0x38B2DB0 | 0x2F5C6B8 |  | `private void Hide()` |
| 0x38B3218 | 0x2F5CA40 |  | `private void Close()` |
| 0x38B3020 | 0x2F5C7DC |  | `private string dvx(long e)` |
| 0x38B3140 | 0x2F5C8E8 |  | `private string dvK(string e, string f)` |
| 0x38B321C | 0x2F5CA44 |  | `public void .ctor()` |

</details>

### public class `UiMapsDeleteOption` : MonoBehaviour  
`TypeDefIndex 3646`

| offset | field |
|---|---|
| 0x20 | `private Button button;` |
| 0x28 | `private RectTransform loadingBar;` |
| 0x30 | `private GameObject activeRoot;` |
| 0x38 | `private GameObject inactiveRoot;` |
| 0x40 | `private ah Ote;` |
| 0x48 | `private bool Otf;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B3224 | 0x2F5CA4C |  | `private void OnEnable()` |
| 0x38B3520 | 0x2F5CE3C |  | `private void Update()` |
| 0x38B32D8 | 0x2F5CD38 |  | `private void dvG(bool e)` |
| 0x38B36FC | 0x2F5CF0C |  | `private void dvP()` |
| 0x38B36C4 | 0x2F5CFC8 |  | `private void dvD()` |
| 0x38B3734 | 0x2F5D084 |  | `private void dvn()` |
| 0x38B354C | 0x2F5CE4C |  | `private void dvV()` |
| 0x38B37D8 | 0x2F5D23C |  | `public void .ctor()` |
| - | 0x2F5CB6C |  | `private void ResolveService()` |
| - | 0x2F5D1B4 |  | `private IEnumerator DeleteMaps(am manager)` |

</details>
