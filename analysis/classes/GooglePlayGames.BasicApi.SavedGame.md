# namespace `GooglePlayGames.BasicApi.SavedGame`  (8 types)

### public sealed class `ConflictCallback` : MulticastDelegate  
`TypeDefIndex 3836`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F7D81C |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F7D928 |  | `public virtual void Invoke(IConflictResolver resolver, ISavedGameMetadata original, byte[] originalData, ISavedGameMetadata unmerged, byte[] unmergedData)` |
| - | 0x2F7D93C |  | `public virtual IAsyncResult BeginInvoke(IConflictResolver resolver, ISavedGameMetadata original, byte[] originalData, ISavedGameMetadata unmerged, byte[] unmergedData, AsyncCallback callback, object object)` |
| - | 0x2F7D96C |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public enum `ConflictResolutionStrategy`  
`TypeDefIndex 3837`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ConflictResolutionStrategy UseLongestPlaytime = 0;` |
| - | `public const ConflictResolutionStrategy UseOriginal = 1;` |
| - | `public const ConflictResolutionStrategy UseUnmerged = 2;` |
| - | `public const ConflictResolutionStrategy UseManual = 3;` |
| - | `public const ConflictResolutionStrategy UseLastKnownGood = 4;` |
| - | `public const ConflictResolutionStrategy UseMostRecentlySaved = 5;` |

### public interface `IConflictResolver`  
`TypeDefIndex 3838`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void ChooseMetadata(ISavedGameMetadata chosenMetadata);` |
| - | - |  | `public abstract void ResolveConflict(ISavedGameMetadata chosenMetadata, SavedGameMetadataUpdate metadataUpdate, byte[] updatedData);` |

</details>

### public interface `ISavedGameClient`  
`TypeDefIndex 3839`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void OpenWithAutomaticConflictResolution(string filename, DataSource source, ConflictResolutionStrategy resolutionStrategy, Action<SavedGameRequestStatus, ISavedGameMetadata> callback);` |
| - | - |  | `public abstract void OpenWithManualConflictResolution(string filename, DataSource source, bool prefetchDataOnConflict, ConflictCallback conflictCallback, Action<SavedGameRequestStatus, ISavedGameMetadata> completedCallback);` |
| - | - |  | `public abstract void ReadBinaryData(ISavedGameMetadata metadata, Action<SavedGameRequestStatus, byte[]> completedCallback);` |
| - | - |  | `public abstract void ShowSelectSavedGameUI(string uiTitle, uint maxDisplayedSavedGames, bool showCreateSaveUI, bool showDeleteSaveUI, Action<SelectUIStatus, ISavedGameMetadata> callback);` |
| - | - |  | `public abstract void CommitUpdate(ISavedGameMetadata metadata, SavedGameMetadataUpdate updateForMetadata, byte[] updatedBinaryData, Action<SavedGameRequestStatus, ISavedGameMetadata> callback);` |
| - | - |  | `public abstract void FetchAllSavedGames(DataSource source, Action<SavedGameRequestStatus, List<ISavedGameMetadata>> callback);` |
| - | - |  | `public abstract void Delete(ISavedGameMetadata metadata);` |

</details>

### public interface `ISavedGameMetadata`  
`TypeDefIndex 3840`

Properties: `public abstract bool IsOpen { get; }`; `public abstract string Filename { get; }`; `public abstract string Description { get; }`; `public abstract string CoverImageURL { get; }`; `public abstract TimeSpan TotalTimePlayed { get; }`; `public abstract DateTime LastModifiedTimestamp { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract bool get_IsOpen();` |
| - | - |  | `public abstract string get_Filename();` |
| - | - |  | `public abstract string get_Description();` |
| - | - |  | `public abstract string get_CoverImageURL();` |
| - | - |  | `public abstract TimeSpan get_TotalTimePlayed();` |
| - | - |  | `public abstract DateTime get_LastModifiedTimestamp();` |

</details>

### public struct `SavedGameMetadataUpdate`  
`TypeDefIndex 3842`

| offset | field |
|---|---|
| 0x0 | `private readonly bool mDescriptionUpdated;` |
| 0x8 | `private readonly string mNewDescription;` |
| 0x10 | `private readonly bool mCoverImageUpdated;` |
| 0x18 | `private readonly byte[] mNewPngCoverImage;` |
| 0x20 | `private readonly Nullable<TimeSpan> mNewPlayedTime;` |

Properties: `public bool IsDescriptionUpdated { get; }`; `public string UpdatedDescription { get; }`; `public bool IsCoverImageUpdated { get; }`; `public byte[] UpdatedPngCoverImage { get; }`; `public bool IsPlayedTimeUpdated { get; }`; `public Nullable<TimeSpan> UpdatedPlayedTime { get; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37985A0 | 0x2F7D978 |  | `public bool get_IsDescriptionUpdated()` |
| 0x37985A8 | 0x2F7D980 |  | `public string get_UpdatedDescription()` |
| 0x37985B0 | 0x2F7D988 |  | `public bool get_IsCoverImageUpdated()` |
| 0x37985B8 | 0x2F7D990 |  | `public byte[] get_UpdatedPngCoverImage()` |
| 0x37985C0 | 0x2F7D998 |  | `public bool get_IsPlayedTimeUpdated()` |
| 0x37985FC | 0x2F7D9A0 |  | `public Nullable<TimeSpan> get_UpdatedPlayedTime()` |
| 0x3798530 | 0x2F7D9AC |  | `private void .ctor(SavedGameMetadataUpdate.Builder builder)` |

</details>

### public enum `SavedGameRequestStatus`  
`TypeDefIndex 3843`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const SavedGameRequestStatus Success = 0;` |
| - | `public const SavedGameRequestStatus TimeoutError = 1;` |
| - | `public const SavedGameRequestStatus InternalError = 2;` |
| - | `public const SavedGameRequestStatus AuthenticationError = 3;` |
| - | `public const SavedGameRequestStatus BadInputError = 4;` |

### public enum `SelectUIStatus`  
`TypeDefIndex 3844`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const SelectUIStatus SavedGameSelected = 0;` |
| - | `public const SelectUIStatus UserClosedUI = 1;` |
| - | `public const SelectUIStatus InternalError = 2;` |
| - | `public const SelectUIStatus TimeoutError = 3;` |
| - | `public const SelectUIStatus AuthenticationError = 4;` |
| - | `public const SelectUIStatus BadInputError = 5;` |
| - | `public const SelectUIStatus UiBusy = 6;` |
