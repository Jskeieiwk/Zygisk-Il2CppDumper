# namespace `GooglePlayGames.OurUtils`  (5 types)

### public class `Logger`  
`TypeDefIndex 3799`

| offset | field |
|---|---|
| 0x0 | `private static bool debugLogEnabled;` |
| 0x1 | `private static bool warningLogEnabled;` |

Properties: `public static bool DebugLogEnabled { get; set; }`; `public static bool WarningLogEnabled { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3793778 | 0x2F7D2D4 |  | `public static bool get_DebugLogEnabled()` |
| 0x37937D0 | 0x2F7D2DC |  | `public static void set_DebugLogEnabled(bool value)` |
| 0x3793830 | 0x2F7D2E0 |  | `public static bool get_WarningLogEnabled()` |
| 0x3793888 | 0x2F7D2E8 |  | `public static void set_WarningLogEnabled(bool value)` |
| 0x376B880 | 0x2F7D2EC |  | `public static void d(string msg)` |
| 0x376C5F4 | 0x2F7D2F0 |  | `public static void w(string msg)` |
| 0x376C078 | 0x2F7D2F4 |  | `public static void e(string msg)` |
| 0x3793900 | 0x2F7D2F8 |  | `public static string describe(byte[] b)` |
| 0x37939A4 | 0x2F7D300 |  | `private static string ToLogMessage(string prefix, string logType, string msg)` |
| 0x3793D10 | 0x2F7D308 |  | `public void .ctor()` |

</details>

### public static class `Misc`  
`TypeDefIndex 3800`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3794110 | 0x2F7D310 |  | `public static bool BuffersAreIdentical(byte[] a, byte[] b)` |
| 0x37941A4 | 0x2F7D318 |  | `public static byte[] GetSubsetBytes(byte[] array, int offset, int length)` |
| - | - |  | `public static T CheckNotNull<T>(T value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3861DE8 Offset: 0x385DDE8 VA: 0x3861DE8` |
| - | - |  | `\|-Misc.CheckNotNull<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `public static T CheckNotNull<T>(T value, string paramName)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3861EBC Offset: 0x385DEBC VA: 0x3861EBC` |
| - | - |  | `\|-Misc.CheckNotNull<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x377C440 | 0x2F7D320 |  | `public static bool IsApiException(AndroidJavaObject exception)` |

</details>

### public class `NearbyHelperObject` : MonoBehaviour  
`TypeDefIndex 3801`

| offset | field |
|---|---|
| 0x0 | `private static NearbyHelperObject instance;` |
| 0x8 | `private static double mAdvertisingRemaining;` |
| 0x10 | `private static double mDiscoveryRemaining;` |
| 0x18 | `private static INearbyConnectionClient mClient;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3783AC8 | 0x2F7D328 |  | `public static void CreateObject(INearbyConnectionClient client)` |
| 0x379430C | 0x2F7D32C |  | `private static double ToSeconds(Nullable<TimeSpan> span)` |
| 0x37898B4 | 0x2F7D334 |  | `public static void StartAdvertisingTimer(Nullable<TimeSpan> span)` |
| 0x3789924 | 0x2F7D338 |  | `public static void StartDiscoveryTimer(Nullable<TimeSpan> span)` |
| 0x3794400 | 0x2F7D33C |  | `public void Awake()` |
| 0x379446C | 0x2F7D340 |  | `public void OnDisable()` |
| 0x3794520 | 0x2F7D344 |  | `public void Update()` |
| 0x3794304 | 0x2F7D348 |  | `public void .ctor()` |

</details>

### public static class `PlatformUtils`  
`TypeDefIndex 3802`

Properties: `public static bool Supported { get; }`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379472C | 0x2F7D350 |  | `public static bool get_Supported()` |

</details>

### public class `PlayGamesHelperObject` : MonoBehaviour  
`TypeDefIndex 3803`

| offset | field |
|---|---|
| 0x0 | `private static PlayGamesHelperObject instance;` |
| 0x8 | `private static bool sIsDummy;` |
| 0x10 | `private static List<Action> sQueue;` |
| 0x20 | `private List<Action> localQueue;` |
| 0x18 | `private static bool sQueueEmpty;` |
| 0x20 | `private static List<Action<bool>> sPauseCallbackList;` |
| 0x28 | `private static List<Action<bool>> sFocusCallbackList;` |

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376DE58 | 0x2F7D358 |  | `public static void CreateObject()` |
| 0x3794A58 | 0x2F7D35C |  | `public void Awake()` |
| 0x3794AC4 | 0x2F7D360 |  | `public void OnDisable()` |
| 0x376D0C8 | 0x2F7D364 |  | `public static void RunCoroutine(IEnumerator action)` |
| 0x376E86C | 0x2F7D368 |  | `public static void RunOnGameThread(Action action)` |
| 0x3794B98 | 0x2F7D36C |  | `public void Update()` |
| 0x3794E10 | 0x2F7D370 |  | `public void OnApplicationFocus(bool focused)` |
| 0x3795100 | 0x2F7D374 |  | `public void OnApplicationPause(bool paused)` |
| 0x37953F0 | 0x2F7D378 |  | `public static void AddFocusCallback(Action<bool> callback)` |
| 0x3795514 | 0x2F7D37C |  | `public static bool RemoveFocusCallback(Action<bool> callback)` |
| 0x3795594 | 0x2F7D384 |  | `public static void AddPauseCallback(Action<bool> callback)` |
| 0x37956B8 | 0x2F7D388 |  | `public static bool RemovePauseCallback(Action<bool> callback)` |
| 0x37949D0 | 0x2F7D390 |  | `public void .ctor()` |

</details>
