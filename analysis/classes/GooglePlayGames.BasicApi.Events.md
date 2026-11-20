# namespace `GooglePlayGames.BasicApi.Events`  (4 types)

### internal class `Event` : IEvent  
`TypeDefIndex 3856`

| offset | field |
|---|---|
| 0x10 | `private string mId;` |
| 0x18 | `private string mName;` |
| 0x20 | `private string mDescription;` |
| 0x28 | `private string mImageUrl;` |
| 0x30 | `private ulong mCurrentCount;` |
| 0x38 | `private EventVisibility mVisibility;` |

Properties: `public string Id { get; }`; `public string Name { get; }`; `public string Description { get; }`; `public string ImageUrl { get; }`; `public ulong CurrentCount { get; }`; `public EventVisibility Visibility { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379975C | 0x2F7DB50 | 4 | `public string get_Id()` |
| 0x3799764 | 0x2F7DB58 | 5 | `public string get_Name()` |
| 0x379976C | 0x2F7DB60 | 6 | `public string get_Description()` |
| 0x3799774 | 0x2F7DB68 | 7 | `public string get_ImageUrl()` |
| 0x379977C | 0x2F7DB70 | 8 | `public ulong get_CurrentCount()` |
| 0x3799784 | 0x2F7DB78 | 9 | `public EventVisibility get_Visibility()` |
| 0x37996CC | 0x2F7DB80 |  | `internal void .ctor(string id, string name, string description, string imageUrl, ulong currentCount, EventVisibility visibility)` |

</details>

### public enum `EventVisibility`  
`TypeDefIndex 3857`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const EventVisibility Hidden = 0;` |
| - | `public const EventVisibility Revealed = 1;` |

### public interface `IEvent`  
`TypeDefIndex 3858`

Properties: `public abstract string Id { get; }`; `public abstract string Name { get; }`; `public abstract string Description { get; }`; `public abstract string ImageUrl { get; }`; `public abstract ulong CurrentCount { get; }`; `public abstract EventVisibility Visibility { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract string get_Id();` |
| - | - |  | `public abstract string get_Name();` |
| - | - |  | `public abstract string get_Description();` |
| - | - |  | `public abstract string get_ImageUrl();` |
| - | - |  | `public abstract ulong get_CurrentCount();` |
| - | - |  | `public abstract EventVisibility get_Visibility();` |

</details>

### public interface `IEventsClient`  
`TypeDefIndex 3859`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void FetchAllEvents(DataSource source, Action<ResponseStatus, List<IEvent>> callback);` |
| - | - |  | `public abstract void FetchEvent(DataSource source, string eventId, Action<ResponseStatus, IEvent> callback);` |
| - | - |  | `public abstract void IncrementEvent(string eventId, uint stepsToIncrement);` |

</details>
