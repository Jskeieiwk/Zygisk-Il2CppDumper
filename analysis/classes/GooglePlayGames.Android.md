# namespace `GooglePlayGames.Android`  (10 types)

### public class `AndroidClient` : IPlayGamesClient  
`TypeDefIndex 3861`

| offset | field |
|---|---|
| 0x10 | `private readonly object GameServicesLock;` |
| 0x18 | `private readonly object AuthStateLock;` |
| 0x20 | `private readonly PlayGamesClientConfiguration mConfiguration;` |
| 0x40 | `private ISavedGameClient mSavedGameClient;` |
| 0x48 | `private IEventsClient mEventsClient;` |
| 0x50 | `private IVideoClient mVideoClient;` |
| 0x58 | `private AndroidTokenClient mTokenClient;` |
| 0x60 | `private Player mUser;` |
| 0x68 | `private AndroidClient.AuthState mAuthState;` |
| 0x70 | `private IUserProfile[] mFriends;` |
| 0x78 | `private LoadFriendsStatus mLastLoadFriendsStatus;` |
| 0x80 | `private AndroidJavaClass mGamesClass;` |
| 0x0 | `private static string TasksClassName;` |
| 0x88 | `private AndroidJavaObject mFriendsResolutionException;` |
| 0x90 | `private readonly int mLeaderboardMaxResults;` |
| 0x94 | `private readonly int mFriendsMaxResults;` |

<details><summary>methods (79)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376DC70 | 0x2F7DB88 |  | `internal void .ctor(PlayGamesClientConfiguration configuration)` |
| 0x376E054 | 0x2F7DB90 | 4 | `public void Authenticate(bool silent, Action<SignInStatus> callback)` |
| - | - |  | `private static Action<T> AsOnGameThreadCallback<T>(Action<T> callback)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x35FE85C Offset: 0x35FA85C VA: 0x35FE85C` |
| - | - |  | `\|-AndroidClient.AsOnGameThreadCallback<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x376E774 | 0x2F7DB94 |  | `private static void InvokeCallbackOnGameThread(Action callback)` |
| - | - |  | `private static void InvokeCallbackOnGameThread<T>(Action<T> callback, T data)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x35FE86C Offset: 0x35FA86C VA: 0x35FE86C` |
| - | - |  | `\|-AndroidClient.InvokeCallbackOnGameThread<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `private static Action<T1, T2> AsOnGameThreadCallback<T1, T2>(Action<T1, T2> toInvokeOnGameThread)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x35FE864 Offset: 0x35FA864 VA: 0x35FE864` |
| - | - |  | `\|-AndroidClient.AsOnGameThreadCallback<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `private static void InvokeCallbackOnGameThread<T1, T2>(Action<T1, T2> callback, T1 t1, T2 t2)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x35FE870 Offset: 0x35FA870 VA: 0x35FE870` |
| - | - |  | `\|-AndroidClient.InvokeCallbackOnGameThread<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x376EA80 | 0x2F7DB98 |  | `private void InitializeGameServices()` |
| 0x376E320 | 0x2F7DB9C |  | `private void InitializeTokenClient()` |
| 0x376EB8C | 0x2F7DBA0 | 13 | `public string GetUserEmail()` |
| 0x376ED14 | 0x2F7DBA8 | 10 | `public string GetIdToken()` |
| 0x376EDCC | 0x2F7DBB0 | 11 | `public string GetServerAuthCode()` |
| 0x376EE84 | 0x2F7DBB8 | 12 | `public void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback)` |
| 0x376EC44 | 0x2F7DBBC | 5 | `public bool IsAuthenticated()` |
| 0x376F028 | 0x2F7DBC4 | 8 | `public void LoadFriends(Action<bool> callback)` |
| 0x376F040 | 0x2F7DBC8 |  | `private void LoadAllFriends(int pageSize, bool forceReload, bool loadMore, Action<bool> callback)` |
| 0x376F740 | 0x2F7DBCC | 27 | `public void LoadFriends(int pageSize, bool forceReload, Action<LoadFriendsStatus> callback)` |
| 0x376F750 | 0x2F7DBD0 | 28 | `public void LoadMoreFriends(int pageSize, Action<LoadFriendsStatus> callback)` |
| 0x376F148 | 0x2F7DBD4 |  | `private void LoadFriendsPaginated(int pageSize, bool isLoadMore, bool forceReload, Action<LoadFriendsStatus> callback)` |
| 0x376FA64 | 0x2F7DBD8 | 24 | `public LoadFriendsStatus GetLastLoadFriendsStatus()` |
| 0x376FA6C | 0x2F7DBE0 | 23 | `public void AskForLoadFriendsResolution(Action<UIStatus> callback)` |
| 0x3770578 | 0x2F7DBE4 | 25 | `public void ShowCompareProfileWithAlternativeNameHintsUI(string playerId, string otherPlayerInGameName, string currentPlayerInGameName, Action<UIStatus> callback)` |
| 0x3770C50 | 0x2F7DBE8 | 26 | `public void GetFriendsListVisibility(bool forceReload, Action<FriendsListVisibilityStatus> callback)` |
| 0x37710EC | 0x2F7DBEC | 40 | `public IUserProfile[] GetFriends()` |
| 0x37710F4 | 0x2F7DBF4 | 6 | `public void SignOut()` |
| 0x37710FC | 0x2F7DBF8 |  | `public void SignOut(Action uiCallback)` |
| 0x37713C8 | 0x2F7DBFC | 7 | `public string GetUserId()` |
| 0x3771408 | 0x2F7DC04 | 9 | `public string GetUserDisplayName()` |
| 0x3771448 | 0x2F7DC0C | 14 | `public string GetUserImageUrl()` |
| 0x3771488 | 0x2F7DC14 | 41 | `public void SetGravityForPopups(Gravity gravity)` |
| 0x3771908 | 0x2F7DC18 | 15 | `public void GetPlayerStats(Action<CommonStatusCodes, PlayerStats> callback)` |
| 0x3771FCC | 0x2F7DC1C | 16 | `public void LoadUsers(string[] userIds, Action<IUserProfile[]> callback)` |
| 0x37726A4 | 0x2F7DC20 | 17 | `public void LoadAchievements(Action<Achievement[]> callback)` |
| 0x3772C78 | 0x2F7DC24 | 18 | `public void UnlockAchievement(string achId, Action<bool> callback)` |
| 0x3772F40 | 0x2F7DC28 | 19 | `public void RevealAchievement(string achId, Action<bool> callback)` |
| 0x3773208 | 0x2F7DC2C | 20 | `public void IncrementAchievement(string achId, int steps, Action<bool> callback)` |
| 0x3773550 | 0x2F7DC30 | 21 | `public void SetStepsAtLeast(string achId, int steps, Action<bool> callback)` |
| 0x3773898 | 0x2F7DC34 | 22 | `public void ShowAchievementsUI(Action<UIStatus> callback)` |
| 0x3773DE0 | 0x2F7DC38 | 32 | `public int LeaderboardMaxResults()` |
| 0x3773DE8 | 0x2F7DC40 | 29 | `public void ShowLeaderboardUI(string leaderboardId, LeaderboardTimeSpan span, Action<UIStatus> callback)` |
| 0x3771EEC | 0x2F7DC44 |  | `private void AddOnFailureListenerWithSignOut(AndroidJavaObject task, Action<AndroidJavaObject> callback)` |
| 0x37705B0 | 0x2F7DC48 |  | `private Action<UIStatus> GetUiSignOutCallbackOnGameThread(Action<UIStatus> callback)` |
| 0x37748F0 | 0x2F7DC50 | 30 | `public void LoadScores(string leaderboardId, LeaderboardStart start, int rowCount, LeaderboardCollection collection, LeaderboardTimeSpan timeSpan, Action<LeaderboardScoreData> callback)` |
| 0x3775080 | 0x2F7DC54 | 31 | `public void LoadMoreScores(ScorePageToken token, int rowCount, Action<LeaderboardScoreData> callback)` |
| 0x3775634 | 0x2F7DC58 |  | `private LeaderboardScoreData CreateLeaderboardScoreData(string leaderboardId, LeaderboardCollection collection, LeaderboardTimeSpan timespan, ResponseStatus status, AndroidJavaObject leaderboardScoresJava)` |
| 0x3776B48 | 0x2F7DC60 | 33 | `public void SubmitScore(string leaderboardId, long score, Action<bool> callback)` |
| 0x3776E7C | 0x2F7DC64 | 34 | `public void SubmitScore(string leaderboardId, long score, string metadata, Action<bool> callback)` |
| 0x37771FC | 0x2F7DC68 | 35 | `public void RequestPermissions(string[] scopes, Action<SignInStatus> callback)` |
| 0x37779C0 | 0x2F7DC6C |  | `private void UpdateClients()` |
| 0x3778510 | 0x2F7DC70 | 36 | `public bool HasPermissions(string[] scopes)` |
| 0x3778958 | 0x2F7DC78 | 37 | `public ISavedGameClient GetSavedGameClient()` |
| 0x3778A20 | 0x2F7DC80 | 38 | `public IEventsClient GetEventsClient()` |
| 0x3778AE8 | 0x2F7DC88 | 39 | `public IVideoClient GetVideoClient()` |
| 0x3772B2C | 0x2F7DC90 |  | `private AndroidJavaObject getAchievementsClient()` |
| 0x37717BC | 0x2F7DC98 |  | `private AndroidJavaObject getGamesClient()` |
| 0x376F768 | 0x2F7DCA0 |  | `private AndroidJavaObject getPlayersClient()` |
| 0x3774F10 | 0x2F7DCA8 |  | `private AndroidJavaObject getLeaderboardsClient()` |
| 0x3771DA0 | 0x2F7DCB0 |  | `private AndroidJavaObject getPlayerStatsClient()` |
| 0x3778DB8 | 0x2F7DCB8 |  | `private AndroidJavaObject getVideosClient()` |

</details>

### internal class `AndroidEventsClient` : IEventsClient  
`TypeDefIndex 3862`

| offset | field |
|---|---|
| 0x10 | `private AndroidJavaObject mEventsClient;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3777F10 | 0x2F7DCC0 |  | `public void .ctor(AndroidJavaObject account)` |
| 0x37802CC | 0x2F7DCC8 | 4 | `public void FetchAllEvents(DataSource source, Action<ResponseStatus, List<IEvent>> callback)` |
| 0x378066C | 0x2F7DCCC | 5 | `public void FetchEvent(DataSource source, string eventId, Action<ResponseStatus, IEvent> callback)` |
| 0x3780A78 | 0x2F7DCD0 | 6 | `public void IncrementEvent(string eventId, uint stepsToIncrement)` |
| - | - |  | `private static Action<T1, T2> ToOnGameThread<T1, T2>(Action<T1, T2> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x35FE874 Offset: 0x35FA874 VA: 0x35FE874` |
| - | - |  | `\|-AndroidEventsClient.ToOnGameThread<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x3780BD8 | 0x2F7DCD4 |  | `private static Event CreateEvent(AndroidJavaObject eventJava)` |

</details>

### internal class `AndroidHelperFragment`  
`TypeDefIndex 3863`

| offset | field |
|---|---|
| - | `private const string HelperFragmentClass = "com.google.games.bridge.HelperFragment";` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3778BB0 | 0x2F7DCDC |  | `public static AndroidJavaObject GetActivity()` |
| 0x3779FC4 | 0x2F7DCE4 |  | `public static AndroidJavaObject GetDefaultPopupView()` |
| 0x3773930 | 0x2F7DCEC |  | `public static void ShowAchievementsUI(Action<UIStatus> cb)` |
| 0x3781F6C | 0x2F7DCF0 |  | `public static void ShowCaptureOverlayUI()` |
| 0x3773EB8 | 0x2F7DCF4 |  | `public static void ShowAllLeaderboardsUI(Action<UIStatus> cb)` |
| 0x3774368 | 0x2F7DCF8 |  | `public static void ShowLeaderboardUI(string leaderboardId, LeaderboardTimeSpan timeSpan, Action<UIStatus> cb)` |
| 0x37706C4 | 0x2F7DCFC |  | `public static void ShowCompareProfileWithAlternativeNameHintsUI(string playerId, string otherPlayerInGameName, string currentPlayerInGameName, Action<UIStatus> cb)` |
| 0x377BD80 | 0x2F7DD00 |  | `public static void IsResolutionRequired(AndroidJavaObject friendsSharingConsentException, Action<bool> cb)` |
| 0x3770074 | 0x2F7DD04 |  | `public static void AskForLoadFriendsResolution(AndroidJavaObject friendsSharingConsentException, Action<UIStatus> cb)` |
| 0x37821F4 | 0x2F7DD08 |  | `public static void ShowSelectSnapshotUI(bool showCreateSaveUI, bool showDeleteSaveUI, int maxDisplayedSavedGames, string uiTitle, Action<SelectUIStatus, ISavedGameMetadata> cb)` |
| 0x378283C | 0x2F7DD0C |  | `public void .ctor()` |

</details>

### internal class `AndroidJavaConverter`  
`TypeDefIndex 3864`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37769F0 | 0x2F7DD14 |  | `internal static DateTime ToDateTime(long milliseconds)` |
| 0x377505C | 0x2F7DD1C |  | `internal static int ToLeaderboardVariantTimeSpan(LeaderboardTimeSpan span)` |
| 0x3775070 | 0x2F7DD24 |  | `internal static int ToLeaderboardVariantCollection(LeaderboardCollection collection)` |
| 0x377561C | 0x2F7DD2C |  | `internal static int ToPageDirection(ScorePageDirection direction)` |
| 0x377B02C | 0x2F7DD34 |  | `internal static Player ToPlayer(AndroidJavaObject player)` |
| 0x3783274 | 0x2F7DD3C |  | `internal static PlayerProfile ToPlayerProfile(AndroidJavaObject player)` |
| 0x37835A8 | 0x2F7DD44 |  | `internal static List<string> ToStringList(AndroidJavaObject stringList)` |
| 0x378389C | 0x2F7DD4C |  | `internal static AndroidJavaObject ToJavaStringList(List<string> list)` |
| 0x377CCA8 | 0x2F7DD54 |  | `internal static FriendsListVisibilityStatus ToFriendsListVisibilityStatus(int playerListVisibility)` |
| 0x377B86C | 0x2F7DD5C |  | `internal static IUserProfile[] playersBufferToArray(AndroidJavaObject playersBuffer)` |
| 0x3783AC0 | 0x2F7DD64 |  | `public void .ctor()` |

</details>

### public class `AndroidNearbyConnectionClient` : INearbyConnectionClient  
`TypeDefIndex 3871`

| offset | field |
|---|---|
| 0x10 | `private AndroidJavaObject mClient;` |
| 0x0 | `private static readonly long NearbyClientId;` |
| 0x8 | `private static readonly int ApplicationInfoFlags;` |
| 0x10 | `private static readonly string ServiceId;` |
| 0x18 | `protected IMessageListener mAdvertisingMessageListener;` |

<details><summary>methods (32)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376D82C | 0x2F7DD6C |  | `public void .ctor()` |
| 0x3783C80 | 0x2F7DD74 | 4 | `public int MaxUnreliableMessagePayloadLength()` |
| 0x3783C88 | 0x2F7DD7C | 5 | `public int MaxReliableMessagePayloadLength()` |
| 0x3783C90 | 0x2F7DD84 | 6 | `public void SendReliable(List<string> recipientEndpointIds, byte[] payload)` |
| 0x37841F4 | 0x2F7DD88 | 7 | `public void SendUnreliable(List<string> recipientEndpointIds, byte[] payload)` |
| 0x3783C94 | 0x2F7DD8C |  | `private void InternalSend(List<string> recipientEndpointIds, byte[] payload)` |
| 0x37841F8 | 0x2F7DD90 | 8 | `public void StartAdvertising(string name, List<string> appIdentifiers, Nullable<TimeSpan> advertisingDuration, Action<AdvertisingResult> resultCallback, Action<ConnectionRequest> connectionRequestCallback)` |
| 0x3784B90 | 0x2F7DD94 |  | `private AndroidJavaObject CreateAdvertisingOptions()` |
| 0x3785200 | 0x2F7DD9C | 9 | `public void StopAdvertising()` |
| 0x37852F4 | 0x2F7DDA0 | 10 | `public void SendConnectionRequest(string name, string remoteEndpointId, byte[] payload, Action<ConnectionResponse> responseCallback, IMessageListener listener)` |
| 0x37858C8 | 0x2F7DDA4 | 11 | `public void AcceptConnectionRequest(string remoteEndpointId, byte[] payload, IMessageListener listener)` |
| 0x3785DA8 | 0x2F7DDA8 | 12 | `public void StartDiscovery(string serviceId, Nullable<TimeSpan> advertisingDuration, IDiscoveryListener listener)` |
| 0x378667C | 0x2F7DDAC |  | `private AndroidJavaObject CreateDiscoveryOptions()` |
| 0x3786CEC | 0x2F7DDB4 | 13 | `public void StopDiscovery(string serviceId)` |
| 0x3786DC8 | 0x2F7DDB8 | 14 | `public void RejectConnectionRequest(string requestingEndpointId)` |
| 0x3786F80 | 0x2F7DDBC | 15 | `public void DisconnectFromEndpoint(string remoteEndpointId)` |
| 0x3787074 | 0x2F7DDC0 | 16 | `public void StopAllConnections()` |
| 0x3787168 | 0x2F7DDC4 | 17 | `public string GetAppBundleId()` |
| 0x378739C | 0x2F7DDCC | 18 | `public string GetServiceId()` |
| 0x37873F4 | 0x2F7DDD4 |  | `private static string ReadServiceId()` |
| - | - |  | `private static Action<T> ToOnGameThread<T>(Action<T> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3748444 Offset: 0x3744444 VA: 0x3748444` |
| - | - |  | `\|-AndroidNearbyConnectionClient.ToOnGameThread<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `private static Action<T1, T2> ToOnGameThread<T1, T2>(Action<T1, T2> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x374844C Offset: 0x374444C VA: 0x374844C` |
| - | - |  | `\|-AndroidNearbyConnectionClient.ToOnGameThread<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |

</details>

### internal class `AndroidSavedGameClient` : ISavedGameClient  
`TypeDefIndex 3873`

| offset | field |
|---|---|
| 0x0 | `private static readonly Regex ValidFilenameRegex;` |
| 0x10 | `private AndroidJavaObject mSnapshotsClient;` |
| 0x18 | `private AndroidClient mAndroidClient;` |

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3777BFC | 0x2F7DFEC |  | `public void .ctor(AndroidClient androidClient, AndroidJavaObject account)` |
| 0x3789988 | 0x2F7DFF4 | 4 | `public void OpenWithAutomaticConflictResolution(string filename, DataSource source, ConflictResolutionStrategy resolutionStrategy, Action<SavedGameRequestStatus, ISavedGameMetadata> completedCallback)` |
| 0x378A1B0 | 0x2F7DFF8 | 5 | `public void OpenWithManualConflictResolution(string filename, DataSource source, bool prefetchDataOnConflict, ConflictCallback conflictCallback, Action<SavedGameRequestStatus, ISavedGameMetadata> completedCallback)` |
| 0x3789D44 | 0x2F7DFFC |  | `private void InternalOpen(string filename, DataSource source, ConflictResolutionStrategy resolutionStrategy, bool prefetchDataOnConflict, ConflictCallback conflictCallback, Action<SavedGameRequestStatus, ISavedGameMetadata> completedCallback)` |
| 0x378A47C | 0x2F7E000 | 6 | `public void ReadBinaryData(ISavedGameMetadata metadata, Action<SavedGameRequestStatus, byte[]> completedCallback)` |
| 0x378A7FC | 0x2F7E004 | 7 | `public void ShowSelectSavedGameUI(string uiTitle, uint maxDisplayedSavedGames, bool showCreateSaveUI, bool showDeleteSaveUI, Action<SelectUIStatus, ISavedGameMetadata> callback)` |
| 0x378A984 | 0x2F7E008 | 8 | `public void CommitUpdate(ISavedGameMetadata metadata, SavedGameMetadataUpdate updateForMetadata, byte[] updatedBinaryData, Action<SavedGameRequestStatus, ISavedGameMetadata> callback)` |
| 0x378BD78 | 0x2F7E00C | 9 | `public void FetchAllSavedGames(DataSource source, Action<SavedGameRequestStatus, List<ISavedGameMetadata>> callback)` |
| 0x378C174 | 0x2F7E010 | 10 | `public void Delete(ISavedGameMetadata metadata)` |
| 0x378A39C | 0x2F7E014 |  | `private void AddOnFailureListenerWithSignOut(AndroidJavaObject task, Action<AndroidJavaObject> callback)` |
| 0x3789C08 | 0x2F7E018 |  | `private ConflictCallback ToOnGameThread(ConflictCallback conflictCallback)` |
| 0x3789CC4 | 0x2F7E020 |  | `internal static bool IsValidFilename(string filename)` |
| 0x378B160 | 0x2F7E028 |  | `private static AndroidJavaObject AsMetadataChange(SavedGameMetadataUpdate update)` |
| - | - |  | `private static Action<T1, T2> ToOnGameThread<T1, T2>(Action<T1, T2> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3748454 Offset: 0x3744454 VA: 0x3748454` |
| - | - |  | `\|-AndroidSavedGameClient.ToOnGameThread<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |

</details>

### internal class `AndroidSnapshotMetadata` : ISavedGameMetadata  
`TypeDefIndex 3874`

| offset | field |
|---|---|
| 0x10 | `private AndroidJavaObject mJavaSnapshot;` |
| 0x18 | `private AndroidJavaObject mJavaMetadata;` |
| 0x20 | `private AndroidJavaObject mJavaContents;` |

Properties: `public AndroidJavaObject JavaSnapshot { get; }`; `public AndroidJavaObject JavaMetadata { get; }`; `public AndroidJavaObject JavaContents { get; }`; `public bool IsOpen { get; }`; `public string Filename { get; }`; `public string Description { get; }`; `public string CoverImageURL { get; }`; `public TimeSpan TotalTimePlayed { get; }`; `public DateTime LastModifiedTimestamp { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x378F5D4 | 0x2F7E040 |  | `public AndroidJavaObject get_JavaSnapshot()` |
| 0x378F5DC | 0x2F7E048 |  | `public AndroidJavaObject get_JavaMetadata()` |
| 0x378F5E4 | 0x2F7E050 |  | `public AndroidJavaObject get_JavaContents()` |
| 0x378A700 | 0x2F7E058 | 4 | `public bool get_IsOpen()` |
| 0x378F5EC | 0x2F7E060 | 5 | `public string get_Filename()` |
| 0x378F6D8 | 0x2F7E068 | 6 | `public string get_Description()` |
| 0x378F7C4 | 0x2F7E070 | 7 | `public string get_CoverImageURL()` |
| 0x378F8B0 | 0x2F7E078 | 8 | `public TimeSpan get_TotalTimePlayed()` |
| 0x378F9D4 | 0x2F7E080 | 9 | `public DateTime get_LastModifiedTimestamp()` |
| 0x378F000 | 0x2F7E088 |  | `public void .ctor(AndroidJavaObject javaSnapshot)` |
| 0x37829F0 | 0x2F7E090 |  | `public void .ctor(AndroidJavaObject javaMetadata, AndroidJavaObject javaContents)` |

</details>

### internal class `AndroidTaskUtils`  
`TypeDefIndex 3878`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x378FAC4 | 0x2F7E098 |  | `private void .ctor()` |
| - | - |  | `public static void AddOnSuccessListener<T>(AndroidJavaObject task, Action<T> callback)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3748460 Offset: 0x3744460 VA: 0x3748460` |
| - | - |  | `\|-AndroidTaskUtils.AddOnSuccessListener<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `public static void AddOnSuccessListener<T>(AndroidJavaObject task, bool disposeResult, Action<T> callback)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3748464 Offset: 0x3744464 VA: 0x3748464` |
| - | - |  | `\|-AndroidTaskUtils.AddOnSuccessListener<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x376F8B4 | 0x2F7E0A0 |  | `public static void AddOnFailureListener(AndroidJavaObject task, Action<AndroidJavaObject> callback)` |
| - | - |  | `public static void AddOnCompleteListener<T>(AndroidJavaObject task, Action<T> callback)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x374845C Offset: 0x374445C VA: 0x374845C` |
| - | - |  | `\|-AndroidTaskUtils.AddOnCompleteListener<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |

</details>

### internal class `AndroidTokenClient` : TokenClient  
`TypeDefIndex 3880`

| offset | field |
|---|---|
| - | `private const string HelperFragmentClass = "com.google.games.bridge.HelperFragment";` |
| 0x10 | `private bool requestEmail;` |
| 0x11 | `private bool requestAuthCode;` |
| 0x12 | `private bool requestIdToken;` |
| 0x18 | `private List<string> oauthScopes;` |
| 0x20 | `private string webClientId;` |
| 0x28 | `private bool forceRefresh;` |
| 0x29 | `private bool hidePopups;` |
| 0x30 | `private string accountName;` |
| 0x38 | `private AndroidJavaObject account;` |
| 0x40 | `private string email;` |
| 0x48 | `private string authCode;` |
| 0x50 | `private string idToken;` |

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376EABC | 0x2F7E118 | 9 | `public void SetRequestAuthCode(bool flag, bool forceRefresh)` |
| 0x378FCF0 | 0x2F7E11C | 10 | `public void SetRequestEmail(bool flag)` |
| 0x378FCFC | 0x2F7E120 | 11 | `public void SetRequestIdToken(bool flag)` |
| 0x378FD08 | 0x2F7E124 | 12 | `public void SetWebClientId(string webClientId)` |
| 0x378FD10 | 0x2F7E128 | 15 | `public void SetHidePopups(bool flag)` |
| 0x378FD1C | 0x2F7E12C | 13 | `public void SetAccountName(string accountName)` |
| 0x376EAD0 | 0x2F7E130 | 14 | `public void AddOauthScopes(string[] scopes)` |
| 0x3771288 | 0x2F7E134 | 8 | `public void Signout()` |
| 0x378FD24 | 0x2F7E138 | 4 | `public string GetEmail()` |
| 0x378FD2C | 0x2F7E140 | 5 | `public string GetAuthCode()` |
| 0x378FD34 | 0x2F7E148 | 6 | `public string GetIdToken()` |
| 0x376E66C | 0x2F7E150 | 16 | `public void FetchTokens(bool silent, Action<int> callback)` |
| 0x3777358 | 0x2F7E154 | 17 | `public void RequestPermissions(string[] scopes, Action<SignInStatus> callback)` |
| 0x377853C | 0x2F7E158 | 18 | `public bool HasPermissions(string[] scopes)` |
| 0x378FD4C | 0x2F7E160 |  | `private void DoFetchToken(bool silent, Action<int> callback)` |
| 0x3790898 | 0x2F7E164 |  | `public AndroidJavaObject GetAccount()` |
| 0x376EF20 | 0x2F7E16C | 7 | `public void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback)` |
| 0x37908A8 | 0x2F7E170 |  | `private void DoGetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback)` |
| 0x376EAB4 | 0x2F7E174 |  | `public void .ctor()` |

</details>

### internal class `AndroidVideoClient` : IVideoClient  
`TypeDefIndex 3882`

| offset | field |
|---|---|
| 0x10 | `private AndroidJavaObject mVideosClient;` |
| 0x18 | `private bool mIsCaptureSupported;` |
| 0x20 | `private AndroidVideoClient.OnCaptureOverlayStateListenerProxy mOnCaptureOverlayStateListenerProxy;` |

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x377820C | 0x2F7E1F0 |  | `public void .ctor(bool isCaptureSupported, AndroidJavaObject account)` |
| 0x3791F70 | 0x2F7E1F8 | 4 | `public void GetCaptureCapabilities(Action<ResponseStatus, VideoCapabilities> callback)` |
| 0x37922C0 | 0x2F7E1FC | 5 | `public void ShowCaptureOverlay()` |
| 0x37922C4 | 0x2F7E200 | 6 | `public void GetCaptureState(Action<ResponseStatus, VideoCaptureState> callback)` |
| 0x3792614 | 0x2F7E204 | 7 | `public void IsCaptureAvailable(VideoCaptureMode captureMode, Action<ResponseStatus, bool> callback)` |
| 0x37929E4 | 0x2F7E208 | 8 | `public bool IsCaptureSupported()` |
| 0x37929EC | 0x2F7E210 | 9 | `public void RegisterCaptureOverlayStateChangedListener(CaptureOverlayStateListener listener)` |
| 0x3792BD4 | 0x2F7E214 | 10 | `public void UnregisterCaptureOverlayStateChangedListener()` |
| - | - |  | `private static Action<T1, T2> ToOnGameThread<T1, T2>(Action<T1, T2> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3748468 Offset: 0x3744468 VA: 0x3748468` |
| - | - |  | `\|-AndroidVideoClient.ToOnGameThread<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| 0x3792E28 | 0x2F7E218 |  | `private static VideoQualityLevel FromVideoQualityLevel(int captureQualityJava)` |
| 0x3792E34 | 0x2F7E220 |  | `private static VideoCaptureMode FromVideoCaptureMode(int captureMode)` |
| 0x37929D0 | 0x2F7E228 |  | `private static int ToVideoCaptureMode(VideoCaptureMode captureMode)` |
| 0x3792E48 | 0x2F7E230 |  | `private static VideoCaptureState CreateVideoCaptureState(AndroidJavaObject videoCaptureState)` |
| 0x3793180 | 0x2F7E238 |  | `private static VideoCapabilities CreateVideoCapabilities(AndroidJavaObject videoCapabilities)` |

</details>
