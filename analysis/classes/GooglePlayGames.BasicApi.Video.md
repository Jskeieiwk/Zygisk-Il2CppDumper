# namespace `GooglePlayGames.BasicApi.Video`  (4 types)

### public interface `CaptureOverlayStateListener`  
`TypeDefIndex 3832`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void OnCaptureOverlayStateChanged(VideoCaptureOverlayState overlayState);` |

</details>

### public interface `IVideoClient`  
`TypeDefIndex 3833`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void GetCaptureCapabilities(Action<ResponseStatus, VideoCapabilities> callback);` |
| - | - |  | `public abstract void ShowCaptureOverlay();` |
| - | - |  | `public abstract void GetCaptureState(Action<ResponseStatus, VideoCaptureState> callback);` |
| - | - |  | `public abstract void IsCaptureAvailable(VideoCaptureMode captureMode, Action<ResponseStatus, bool> callback);` |
| - | - |  | `public abstract bool IsCaptureSupported();` |
| - | - |  | `public abstract void RegisterCaptureOverlayStateChangedListener(CaptureOverlayStateListener listener);` |
| - | - |  | `public abstract void UnregisterCaptureOverlayStateChangedListener();` |

</details>

### public class `VideoCapabilities`  
`TypeDefIndex 3834`

| offset | field |
|---|---|
| 0x10 | `private bool mIsCameraSupported;` |
| 0x11 | `private bool mIsMicSupported;` |
| 0x12 | `private bool mIsWriteStorageSupported;` |
| 0x18 | `private bool[] mCaptureModesSupported;` |
| 0x20 | `private bool[] mQualityLevelsSupported;` |

Properties: `public bool IsCameraSupported { get; }`; `public bool IsMicSupported { get; }`; `public bool IsWriteStorageSupported { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37979C8 | 0x2F7D7AC |  | `public bool get_IsCameraSupported()` |
| 0x37979D0 | 0x2F7D7B4 |  | `public bool get_IsMicSupported()` |
| 0x37979D8 | 0x2F7D7BC |  | `public bool get_IsWriteStorageSupported()` |
| 0x379795C | 0x2F7D7C4 |  | `internal void .ctor(bool isCameraSupported, bool isMicSupported, bool isWriteStorageSupported, bool[] captureModesSupported, bool[] qualityLevelsSupported)` |
| 0x37979E0 | 0x2F7D7CC |  | `public bool SupportsCaptureMode(VideoCaptureMode captureMode)` |
| 0x3797AB0 | 0x2F7D7D4 |  | `public bool SupportsQualityLevel(VideoQualityLevel qualityLevel)` |
| 0x3797B80 | 0x2F7D7DC | 3 | `public override string ToString()` |

</details>

### public class `VideoCaptureState`  
`TypeDefIndex 3835`

| offset | field |
|---|---|
| 0x10 | `private bool mIsCapturing;` |
| 0x14 | `private VideoCaptureMode mCaptureMode;` |
| 0x18 | `private VideoQualityLevel mQualityLevel;` |
| 0x1C | `private bool mIsOverlayVisible;` |
| 0x1D | `private bool mIsPaused;` |

Properties: `public bool IsCapturing { get; }`; `public VideoCaptureMode CaptureMode { get; }`; `public VideoQualityLevel QualityLevel { get; }`; `public bool IsOverlayVisible { get; }`; `public bool IsPaused { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379811C | 0x2F7D7E4 |  | `public bool get_IsCapturing()` |
| 0x3798124 | 0x2F7D7EC |  | `public VideoCaptureMode get_CaptureMode()` |
| 0x379812C | 0x2F7D7F4 |  | `public VideoQualityLevel get_QualityLevel()` |
| 0x3798134 | 0x2F7D7FC |  | `public bool get_IsOverlayVisible()` |
| 0x379813C | 0x2F7D804 |  | `public bool get_IsPaused()` |
| 0x37980C8 | 0x2F7D80C |  | `internal void .ctor(bool isCapturing, VideoCaptureMode captureMode, VideoQualityLevel qualityLevel, bool isOverlayVisible, bool isPaused)` |
| 0x3798144 | 0x2F7D814 | 3 | `public override string ToString()` |

</details>
