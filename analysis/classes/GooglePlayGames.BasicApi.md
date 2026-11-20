# namespace `GooglePlayGames.BasicApi`  (27 types)

### public class `Achievement`  
`TypeDefIndex 3804`

| offset | field |
|---|---|
| 0x0 | `private static readonly DateTime UnixEpoch;` |
| 0x10 | `private string mId;` |
| 0x18 | `private bool mIsIncremental;` |
| 0x19 | `private bool mIsRevealed;` |
| 0x1A | `private bool mIsUnlocked;` |
| 0x1C | `private int mCurrentSteps;` |
| 0x20 | `private int mTotalSteps;` |
| 0x28 | `private string mDescription;` |
| 0x30 | `private string mName;` |
| 0x38 | `private long mLastModifiedTime;` |
| 0x40 | `private ulong mPoints;` |
| 0x48 | `private string mRevealedImageUrl;` |
| 0x50 | `private string mUnlockedImageUrl;` |

Properties: `public bool IsIncremental { get; set; }`; `public int CurrentSteps { get; set; }`; `public int TotalSteps { get; set; }`; `public bool IsUnlocked { get; set; }`; `public bool IsRevealed { get; set; }`; `public string Id { get; set; }`; `public string Description { get; set; }`; `public string Name { get; set; }`; `public DateTime LastModifiedTime { get; set; }`; `public ulong Points { get; set; }`; `public string RevealedImageUrl { get; set; }`; `public string UnlockedImageUrl { get; set; }`

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3795C08 | 0x2F7D398 |  | `public bool get_IsIncremental()` |
| 0x3795C10 | 0x2F7D3A0 |  | `public void set_IsIncremental(bool value)` |
| 0x3795C1C | 0x2F7D3A4 |  | `public int get_CurrentSteps()` |
| 0x3795C24 | 0x2F7D3AC |  | `public void set_CurrentSteps(int value)` |
| 0x3795C2C | 0x2F7D3B0 |  | `public int get_TotalSteps()` |
| 0x3795C34 | 0x2F7D3B8 |  | `public void set_TotalSteps(int value)` |
| 0x3795C3C | 0x2F7D3BC |  | `public bool get_IsUnlocked()` |
| 0x3795C44 | 0x2F7D3C4 |  | `public void set_IsUnlocked(bool value)` |
| 0x3795C50 | 0x2F7D3C8 |  | `public bool get_IsRevealed()` |
| 0x3795C58 | 0x2F7D3D0 |  | `public void set_IsRevealed(bool value)` |
| 0x3795C64 | 0x2F7D3D4 |  | `public string get_Id()` |
| 0x3795C6C | 0x2F7D3DC |  | `public void set_Id(string value)` |
| 0x3795C74 | 0x2F7D3E0 |  | `public string get_Description()` |
| 0x3795C7C | 0x2F7D3E8 |  | `public void set_Description(string value)` |
| 0x3795C84 | 0x2F7D3EC |  | `public string get_Name()` |
| 0x3795C8C | 0x2F7D3F4 |  | `public void set_Name(string value)` |
| 0x3795C94 | 0x2F7D3F8 |  | `public DateTime get_LastModifiedTime()` |
| 0x377ECB0 | 0x2F7D400 |  | `public void set_LastModifiedTime(DateTime value)` |
| 0x3795D1C | 0x2F7D404 |  | `public ulong get_Points()` |
| 0x3795D24 | 0x2F7D40C |  | `public void set_Points(ulong value)` |
| 0x3795D2C | 0x2F7D410 |  | `public string get_RevealedImageUrl()` |
| 0x3795D34 | 0x2F7D418 |  | `public void set_RevealedImageUrl(string value)` |
| 0x3795D3C | 0x2F7D41C |  | `public string get_UnlockedImageUrl()` |
| 0x3795D44 | 0x2F7D424 |  | `public void set_UnlockedImageUrl(string value)` |
| 0x37958F0 | 0x2F7D428 | 3 | `public override string ToString()` |
| 0x377EC20 | 0x2F7D430 |  | `public void .ctor()` |

</details>

### public enum `CommonStatusCodes`  
`TypeDefIndex 3805`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const CommonStatusCodes SuccessCached = 0;` |
| - | `public const CommonStatusCodes Success = 1;` |
| - | `public const CommonStatusCodes ServiceMissing = 2;` |
| - | `public const CommonStatusCodes ServiceVersionUpdateRequired = 3;` |
| - | `public const CommonStatusCodes ServiceDisabled = 4;` |
| - | `public const CommonStatusCodes SignInRequired = 5;` |
| - | `public const CommonStatusCodes InvalidAccount = 6;` |
| - | `public const CommonStatusCodes ResolutionRequired = 7;` |
| - | `public const CommonStatusCodes NetworkError = 8;` |
| - | `public const CommonStatusCodes InternalError = 9;` |
| - | `public const CommonStatusCodes ServiceInvalid = 10;` |
| - | `public const CommonStatusCodes DeveloperError = 11;` |
| - | `public const CommonStatusCodes LicenseCheckFailed = 12;` |
| - | `public const CommonStatusCodes Error = 13;` |
| - | `public const CommonStatusCodes Interrupted = 14;` |
| - | `public const CommonStatusCodes Timeout = 15;` |
| - | `public const CommonStatusCodes Canceled = 16;` |
| - | `public const CommonStatusCodes ApiNotConnected = 17;` |
| - | `public const CommonStatusCodes AuthApiInvalidCredentials = 18;` |
| - | `public const CommonStatusCodes AuthApiAccessForbidden = 19;` |
| - | `public const CommonStatusCodes AuthApiClientError = 20;` |
| - | `public const CommonStatusCodes AuthApiServerError = 21;` |
| - | `public const CommonStatusCodes AuthTokenError = 22;` |
| - | `public const CommonStatusCodes AuthUrlResolution = 23;` |

### public class `CommonTypesUtil`  
`TypeDefIndex 3806`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3795DD0 | 0x2F7D438 |  | `public static bool StatusIsSuccess(ResponseStatus status)` |
| 0x3795DDC | 0x2F7D440 |  | `public void .ctor()` |

</details>

### public enum `DataSource`  
`TypeDefIndex 3807`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const DataSource ReadCacheOrNetwork = 0;` |
| - | `public const DataSource ReadNetworkOnly = 1;` |

### public class `DummyClient` : IPlayGamesClient  
`TypeDefIndex 3808`

<details><summary>methods (40)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3795DE4 | 0x2F7D448 | 4 | `public void Authenticate(bool silent, Action<SignInStatus> callback)` |
| 0x3795E98 | 0x2F7D44C | 5 | `public bool IsAuthenticated()` |
| 0x3795EAC | 0x2F7D454 | 6 | `public void SignOut()` |
| 0x3795EB0 | 0x2F7D458 | 10 | `public string GetIdToken()` |
| 0x3795EC4 | 0x2F7D460 | 7 | `public string GetUserId()` |
| 0x3795F18 | 0x2F7D468 | 11 | `public string GetServerAuthCode()` |
| 0x3795F2C | 0x2F7D470 | 12 | `public void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback)` |
| 0x3795F58 | 0x2F7D474 | 13 | `public string GetUserEmail()` |
| 0x3795FA0 | 0x2F7D47C | 15 | `public void GetPlayerStats(Action<CommonStatusCodes, PlayerStats> callback)` |
| 0x3796018 | 0x2F7D480 | 9 | `public string GetUserDisplayName()` |
| 0x379606C | 0x2F7D488 | 14 | `public string GetUserImageUrl()` |
| 0x3796080 | 0x2F7D490 | 16 | `public void LoadUsers(string[] userIds, Action<IUserProfile[]> callback)` |
| 0x37960B0 | 0x2F7D494 | 17 | `public void LoadAchievements(Action<Achievement[]> callback)` |
| 0x37960E0 | 0x2F7D498 | 18 | `public void UnlockAchievement(string achId, Action<bool> callback)` |
| 0x3796110 | 0x2F7D49C | 19 | `public void RevealAchievement(string achId, Action<bool> callback)` |
| 0x3796140 | 0x2F7D4A0 | 20 | `public void IncrementAchievement(string achId, int steps, Action<bool> callback)` |
| 0x3796170 | 0x2F7D4A4 | 21 | `public void SetStepsAtLeast(string achId, int steps, Action<bool> callback)` |
| 0x37961A0 | 0x2F7D4A8 | 22 | `public void ShowAchievementsUI(Action<UIStatus> callback)` |
| 0x37961D0 | 0x2F7D4AC | 23 | `public void AskForLoadFriendsResolution(Action<UIStatus> callback)` |
| 0x3796200 | 0x2F7D4B0 | 24 | `public LoadFriendsStatus GetLastLoadFriendsStatus()` |
| 0x3796214 | 0x2F7D4B8 | 27 | `public void LoadFriends(int pageSize, bool forceReload, Action<LoadFriendsStatus> callback)` |
| 0x3796244 | 0x2F7D4BC | 28 | `public void LoadMoreFriends(int pageSize, Action<LoadFriendsStatus> callback)` |
| 0x3796274 | 0x2F7D4C0 | 25 | `public void ShowCompareProfileWithAlternativeNameHintsUI(string userId, string otherPlayerInGameName, string currentPlayerInGameName, Action<UIStatus> callback)` |
| 0x37962A4 | 0x2F7D4C4 | 26 | `public void GetFriendsListVisibility(bool forceReload, Action<FriendsListVisibilityStatus> callback)` |
| 0x37962D4 | 0x2F7D4C8 | 29 | `public void ShowLeaderboardUI(string leaderboardId, LeaderboardTimeSpan span, Action<UIStatus> callback)` |
| 0x3796304 | 0x2F7D4CC | 32 | `public int LeaderboardMaxResults()` |
| 0x379630C | 0x2F7D4D4 | 30 | `public void LoadScores(string leaderboardId, LeaderboardStart start, int rowCount, LeaderboardCollection collection, LeaderboardTimeSpan timeSpan, Action<LeaderboardScoreData> callback)` |
| 0x379638C | 0x2F7D4D8 | 31 | `public void LoadMoreScores(ScorePageToken token, int rowCount, Action<LeaderboardScoreData> callback)` |
| 0x3796418 | 0x2F7D4DC | 33 | `public void SubmitScore(string leaderboardId, long score, Action<bool> callback)` |
| 0x3796448 | 0x2F7D4E0 | 34 | `public void SubmitScore(string leaderboardId, long score, string metadata, Action<bool> callback)` |
| 0x3796478 | 0x2F7D4E4 | 35 | `public void RequestPermissions(string[] scopes, Action<SignInStatus> callback)` |
| 0x37964A8 | 0x2F7D4E8 | 36 | `public bool HasPermissions(string[] scopes)` |
| 0x37964BC | 0x2F7D4F0 | 37 | `public ISavedGameClient GetSavedGameClient()` |
| 0x37964D0 | 0x2F7D4F8 | 38 | `public IEventsClient GetEventsClient()` |
| 0x37964E4 | 0x2F7D500 | 39 | `public IVideoClient GetVideoClient()` |
| 0x37964F8 | 0x2F7D508 | 8 | `public void LoadFriends(Action<bool> callback)` |
| 0x3796524 | 0x2F7D50C | 40 | `public IUserProfile[] GetFriends()` |
| 0x379656C | 0x2F7D514 | 41 | `public void SetGravityForPopups(Gravity gravity)` |
| 0x3795E14 | 0x2F7D518 |  | `private static void LogUsage()` |
| 0x376DC68 | 0x2F7D51C |  | `public void .ctor()` |

</details>

### public enum `FriendsListVisibilityStatus`  
`TypeDefIndex 3809`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const FriendsListVisibilityStatus Unknown = 0;` |
| - | `public const FriendsListVisibilityStatus Visible = 1;` |
| - | `public const FriendsListVisibilityStatus ResolutionRequired = 2;` |
| - | `public const FriendsListVisibilityStatus Unavailable = 3;` |
| - | `public const FriendsListVisibilityStatus NetworkError = 4;` |
| - | `public const FriendsListVisibilityStatus NotAuthorized = 5;` |

### public enum `Gravity`  
`TypeDefIndex 3810`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const Gravity TOP = 0;` |
| - | `public const Gravity BOTTOM = 1;` |
| - | `public const Gravity LEFT = 2;` |
| - | `public const Gravity RIGHT = 3;` |
| - | `public const Gravity CENTER_HORIZONTAL = 4;` |

### public interface `IPlayGamesClient`  
`TypeDefIndex 3811`

<details><summary>methods (38)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void Authenticate(bool silent, Action<SignInStatus> callback);` |
| - | - |  | `public abstract bool IsAuthenticated();` |
| - | - |  | `public abstract void SignOut();` |
| - | - |  | `public abstract string GetUserId();` |
| - | - |  | `public abstract void LoadFriends(Action<bool> callback);` |
| - | - |  | `public abstract string GetUserDisplayName();` |
| - | - |  | `public abstract string GetIdToken();` |
| - | - |  | `public abstract string GetServerAuthCode();` |
| - | - |  | `public abstract void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback);` |
| - | - |  | `public abstract string GetUserEmail();` |
| - | - |  | `public abstract string GetUserImageUrl();` |
| - | - |  | `public abstract void GetPlayerStats(Action<CommonStatusCodes, PlayerStats> callback);` |
| - | - |  | `public abstract void LoadUsers(string[] userIds, Action<IUserProfile[]> callback);` |
| - | - |  | `public abstract void LoadAchievements(Action<Achievement[]> callback);` |
| - | - |  | `public abstract void UnlockAchievement(string achievementId, Action<bool> successOrFailureCalllback);` |
| - | - |  | `public abstract void RevealAchievement(string achievementId, Action<bool> successOrFailureCalllback);` |
| - | - |  | `public abstract void IncrementAchievement(string achievementId, int steps, Action<bool> successOrFailureCalllback);` |
| - | - |  | `public abstract void SetStepsAtLeast(string achId, int steps, Action<bool> callback);` |
| - | - |  | `public abstract void ShowAchievementsUI(Action<UIStatus> callback);` |
| - | - |  | `public abstract void AskForLoadFriendsResolution(Action<UIStatus> callback);` |
| - | - |  | `public abstract LoadFriendsStatus GetLastLoadFriendsStatus();` |
| - | - |  | `public abstract void ShowCompareProfileWithAlternativeNameHintsUI(string otherUserId, string otherPlayerInGameName, string currentPlayerInGameName, Action<UIStatus> callback);` |
| - | - |  | `public abstract void GetFriendsListVisibility(bool forceReload, Action<FriendsListVisibilityStatus> callback);` |
| - | - |  | `public abstract void LoadFriends(int pageSize, bool forceReload, Action<LoadFriendsStatus> callback);` |
| - | - |  | `public abstract void LoadMoreFriends(int pageSize, Action<LoadFriendsStatus> callback);` |
| - | - |  | `public abstract void ShowLeaderboardUI(string leaderboardId, LeaderboardTimeSpan span, Action<UIStatus> callback);` |
| - | - |  | `public abstract void LoadScores(string leaderboardId, LeaderboardStart start, int rowCount, LeaderboardCollection collection, LeaderboardTimeSpan timeSpan, Action<LeaderboardScoreData> callback);` |
| - | - |  | `public abstract void LoadMoreScores(ScorePageToken token, int rowCount, Action<LeaderboardScoreData> callback);` |
| - | - |  | `public abstract int LeaderboardMaxResults();` |
| - | - |  | `public abstract void SubmitScore(string leaderboardId, long score, Action<bool> successOrFailureCalllback);` |
| - | - |  | `public abstract void SubmitScore(string leaderboardId, long score, string metadata, Action<bool> successOrFailureCalllback);` |
| - | - |  | `public abstract void RequestPermissions(string[] scopes, Action<SignInStatus> callback);` |
| - | - |  | `public abstract bool HasPermissions(string[] scopes);` |
| - | - |  | `public abstract ISavedGameClient GetSavedGameClient();` |
| - | - |  | `public abstract IEventsClient GetEventsClient();` |
| - | - |  | `public abstract IVideoClient GetVideoClient();` |
| - | - |  | `public abstract IUserProfile[] GetFriends();` |
| - | - |  | `public abstract void SetGravityForPopups(Gravity gravity);` |

</details>

### public enum `LeaderboardCollection`  
`TypeDefIndex 3812`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LeaderboardCollection Public = 0;` |
| - | `public const LeaderboardCollection Social = 1;` |

### public class `LeaderboardScoreData`  
`TypeDefIndex 3813`

| offset | field |
|---|---|
| 0x10 | `private string mId;` |
| 0x18 | `private ResponseStatus mStatus;` |
| 0x20 | `private ulong mApproxCount;` |
| 0x28 | `private string mTitle;` |
| 0x30 | `private IScore mPlayerScore;` |
| 0x38 | `private ScorePageToken mPrevPage;` |
| 0x40 | `private ScorePageToken mNextPage;` |
| 0x48 | `private List<PlayGamesScore> mScores;` |

Properties: `public bool Valid { get; }`; `public ResponseStatus Status { get; set; }`; `public ulong ApproximateCount { get; set; }`; `public string Title { get; set; }`; `public string Id { get; set; }`; `public IScore PlayerScore { get; set; }`; `public IScore[] Scores { get; }`; `public ScorePageToken PrevPageToken { get; set; }`; `public ScorePageToken NextPageToken { get; set; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379660C | 0x2F7D524 |  | `public bool get_Valid()` |
| 0x3796620 | 0x2F7D52C |  | `public ResponseStatus get_Status()` |
| 0x3796628 | 0x2F7D534 |  | `internal void set_Status(ResponseStatus value)` |
| 0x3796630 | 0x2F7D538 |  | `public ulong get_ApproximateCount()` |
| 0x3796638 | 0x2F7D540 |  | `internal void set_ApproximateCount(ulong value)` |
| 0x3796640 | 0x2F7D544 |  | `public string get_Title()` |
| 0x3796648 | 0x2F7D54C |  | `internal void set_Title(string value)` |
| 0x3796650 | 0x2F7D550 |  | `public string get_Id()` |
| 0x3796658 | 0x2F7D558 |  | `internal void set_Id(string value)` |
| 0x3796660 | 0x2F7D55C |  | `public IScore get_PlayerScore()` |
| 0x3796668 | 0x2F7D564 |  | `internal void set_PlayerScore(IScore value)` |
| 0x376C9D8 | 0x2F7D568 |  | `public IScore[] get_Scores()` |
| 0x3796670 | 0x2F7D570 |  | `public ScorePageToken get_PrevPageToken()` |
| 0x3796678 | 0x2F7D578 |  | `internal void set_PrevPageToken(ScorePageToken value)` |
| 0x3796680 | 0x2F7D57C |  | `public ScorePageToken get_NextPageToken()` |
| 0x3796688 | 0x2F7D584 |  | `internal void set_NextPageToken(ScorePageToken value)` |
| 0x3796570 | 0x2F7D588 |  | `internal void .ctor(string leaderboardId)` |
| 0x3776940 | 0x2F7D590 |  | `internal void .ctor(string leaderboardId, ResponseStatus status)` |
| 0x3776A84 | 0x2F7D598 |  | `internal int AddScore(PlayGamesScore score)` |
| 0x3796690 | 0x2F7D5A0 | 3 | `public override string ToString()` |

</details>

### public enum `LeaderboardStart`  
`TypeDefIndex 3814`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LeaderboardStart TopScores = 0;` |
| - | `public const LeaderboardStart PlayerCentered = 1;` |

### public enum `LeaderboardTimeSpan`  
`TypeDefIndex 3815`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LeaderboardTimeSpan Daily = 0;` |
| - | `public const LeaderboardTimeSpan Weekly = 1;` |
| - | `public const LeaderboardTimeSpan AllTime = 2;` |

### public enum `LoadFriendsStatus`  
`TypeDefIndex 3816`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LoadFriendsStatus Unknown = 0;` |
| - | `public const LoadFriendsStatus Completed = 1;` |
| - | `public const LoadFriendsStatus LoadMore = 2;` |
| - | `public const LoadFriendsStatus ResolutionRequired = 3;` |
| - | `public const LoadFriendsStatus InternalError = 4;` |
| - | `public const LoadFriendsStatus NotAuthorized = 5;` |
| - | `public const LoadFriendsStatus NetworkError = 6;` |

### public class `Player` : PlayGamesUserProfile  
`TypeDefIndex 3817`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3783270 | 0x2F7D5A8 |  | `internal void .ctor(string displayName, string playerId, string avatarUrl)` |

</details>

### public class `PlayerProfile` : PlayGamesUserProfile  
`TypeDefIndex 3818`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37835A0 | 0x2F7D5B0 |  | `internal void .ctor(string displayName, string playerId, string avatarUrl, bool isFriend)` |

</details>

### public class `PlayerStats`  
`TypeDefIndex 3819`

| offset | field |
|---|---|
| 0x0 | `private static float UNSET_VALUE;` |
| 0x10 | `private bool mValid;` |
| 0x14 | `private int mNumberOfPurchases;` |
| 0x18 | `private float mAvgSessionLength;` |
| 0x1C | `private int mDaysSinceLastPlayed;` |
| 0x20 | `private int mNumberOfSessions;` |
| 0x24 | `private float mSessPercentile;` |
| 0x28 | `private float mSpendPercentile;` |
| 0x2C | `private float mSpendProbability;` |
| 0x30 | `private float mChurnProbability;` |
| 0x34 | `private float mHighSpenderProbability;` |
| 0x38 | `private float mTotalSpendNext28Days;` |

Properties: `public bool Valid { get; }`; `public int NumberOfPurchases { get; }`; `public float AvgSessionLength { get; }`; `public int DaysSinceLastPlayed { get; }`; `public int NumberOfSessions { get; }`; `public float SessPercentile { get; }`; `public float SpendPercentile { get; }`; `public float SpendProbability { get; }`; `public float ChurnProbability { get; }`; `public float HighSpenderProbability { get; }`; `public float TotalSpendNext28Days { get; }`

<details><summary>methods (22)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3797098 | 0x2F7D5B8 |  | `public bool get_Valid()` |
| 0x37970A0 | 0x2F7D5C0 |  | `public int get_NumberOfPurchases()` |
| 0x37970A8 | 0x2F7D5C8 |  | `public float get_AvgSessionLength()` |
| 0x37970B0 | 0x2F7D5D0 |  | `public int get_DaysSinceLastPlayed()` |
| 0x37970B8 | 0x2F7D5D8 |  | `public int get_NumberOfSessions()` |
| 0x37970C0 | 0x2F7D5E0 |  | `public float get_SessPercentile()` |
| 0x37970C8 | 0x2F7D5E8 |  | `public float get_SpendPercentile()` |
| 0x37970D0 | 0x2F7D5F0 |  | `public float get_SpendProbability()` |
| 0x37970D8 | 0x2F7D5F8 |  | `public float get_ChurnProbability()` |
| 0x37970E0 | 0x2F7D600 |  | `public float get_HighSpenderProbability()` |
| 0x37970E8 | 0x2F7D608 |  | `public float get_TotalSpendNext28Days()` |
| 0x377D53C | 0x2F7D610 |  | `public void .ctor(int numberOfPurchases, float avgSessionLength, int daysSinceLastPlayed, int numberOfSessions, float sessPercentile, float spendPercentile, float spendProbability, float churnProbability, float highSpenderProbability, float totalSpendNext28Days)` |
| 0x377D7B0 | 0x2F7D618 |  | `public void .ctor()` |
| 0x37970F0 | 0x2F7D620 |  | `public bool HasNumberOfPurchases()` |
| 0x3797170 | 0x2F7D628 |  | `public bool HasAvgSessionLength()` |
| 0x37971E0 | 0x2F7D630 |  | `public bool HasDaysSinceLastPlayed()` |
| 0x3797260 | 0x2F7D638 |  | `public bool HasNumberOfSessions()` |
| 0x37972E0 | 0x2F7D640 |  | `public bool HasSessPercentile()` |
| 0x3797350 | 0x2F7D648 |  | `public bool HasSpendPercentile()` |
| 0x37973C0 | 0x2F7D650 |  | `public bool HasChurnProbability()` |
| 0x3797430 | 0x2F7D658 |  | `public bool HasHighSpenderProbability()` |
| 0x37974A0 | 0x2F7D660 |  | `public bool HasTotalSpendNext28Days()` |

</details>

### public struct `PlayGamesClientConfiguration`  
`TypeDefIndex 3821`

| offset | field |
|---|---|
| 0x0 | `public static readonly PlayGamesClientConfiguration DefaultConfiguration;` |
| 0x0 | `private readonly bool mEnableSavedGames;` |
| 0x8 | `private readonly string[] mScopes;` |
| 0x10 | `private readonly bool mRequestAuthCode;` |
| 0x11 | `private readonly bool mForceRefresh;` |
| 0x12 | `private readonly bool mHidePopups;` |
| 0x13 | `private readonly bool mRequestEmail;` |
| 0x14 | `private readonly bool mRequestIdToken;` |
| 0x18 | `private readonly string mAccountName;` |

Properties: `public bool EnableSavedGames { get; }`; `public bool IsHidingPopups { get; }`; `public bool IsRequestingAuthCode { get; }`; `public bool IsForcingRefresh { get; }`; `public bool IsRequestingEmail { get; }`; `public bool IsRequestingIdToken { get; }`; `public string AccountName { get; }`; `public string[] Scopes { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3796964 | 0x2F7D668 |  | `public bool get_EnableSavedGames()` |
| 0x379696C | 0x2F7D670 |  | `public bool get_IsHidingPopups()` |
| 0x3796974 | 0x2F7D678 |  | `public bool get_IsRequestingAuthCode()` |
| 0x379697C | 0x2F7D680 |  | `public bool get_IsForcingRefresh()` |
| 0x3796984 | 0x2F7D688 |  | `public bool get_IsRequestingEmail()` |
| 0x379698C | 0x2F7D690 |  | `public bool get_IsRequestingIdToken()` |
| 0x3796994 | 0x2F7D698 |  | `public string get_AccountName()` |
| 0x379699C | 0x2F7D6A0 |  | `public string[] get_Scopes()` |
| 0x3796878 | 0x2F7D6A8 |  | `private void .ctor(PlayGamesClientConfiguration.Builder builder)` |
| 0x37969A4 | 0x2F7D6B4 |  | `public static bool op_Equality(PlayGamesClientConfiguration c1, PlayGamesClientConfiguration c2)` |
| 0x3796B48 | 0x2F7D6BC |  | `public static bool op_Inequality(PlayGamesClientConfiguration c1, PlayGamesClientConfiguration c2)` |
| 0x3796BE0 | 0x2F7D6C4 | 2 | `public override int GetHashCode()` |
| 0x3796D68 | 0x2F7D6CC | 0 | `public override bool Equals(object obj)` |

</details>

### public enum `ResponseStatus`  
`TypeDefIndex 3822`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ResponseStatus Success = 0;` |
| - | `public const ResponseStatus SuccessWithStale = 1;` |
| - | `public const ResponseStatus LicenseCheckFailed = 2;` |
| - | `public const ResponseStatus InternalError = 3;` |
| - | `public const ResponseStatus NotAuthorized = 4;` |
| - | `public const ResponseStatus VersionUpdateRequired = 5;` |
| - | `public const ResponseStatus Timeout = 6;` |
| - | `public const ResponseStatus ResolutionRequired = 7;` |

### public enum `ScorePageDirection`  
`TypeDefIndex 3823`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const ScorePageDirection Forward = 0;` |
| - | `public const ScorePageDirection Backward = 1;` |

### public class `ScorePageToken`  
`TypeDefIndex 3824`

| offset | field |
|---|---|
| 0x10 | `private string mId;` |
| 0x18 | `private object mInternalObject;` |
| 0x20 | `private LeaderboardCollection mCollection;` |
| 0x24 | `private LeaderboardTimeSpan mTimespan;` |
| 0x28 | `private ScorePageDirection mDirection;` |

Properties: `public LeaderboardCollection Collection { get; }`; `public LeaderboardTimeSpan TimeSpan { get; }`; `public ScorePageDirection Direction { get; }`; `public string LeaderboardId { get; }`; `internal object InternalObject { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37975C8 | 0x2F7D760 |  | `public LeaderboardCollection get_Collection()` |
| 0x37975D0 | 0x2F7D768 |  | `public LeaderboardTimeSpan get_TimeSpan()` |
| 0x37975D8 | 0x2F7D770 |  | `public ScorePageDirection get_Direction()` |
| 0x37975E0 | 0x2F7D778 |  | `public string get_LeaderboardId()` |
| 0x37975E8 | 0x2F7D780 |  | `internal object get_InternalObject()` |
| 0x379755C | 0x2F7D788 |  | `internal void .ctor(object internalObject, string id, LeaderboardCollection collection, LeaderboardTimeSpan timespan, ScorePageDirection direction)` |

</details>

### public class `SignInHelper`  
`TypeDefIndex 3825`

| offset | field |
|---|---|
| 0x0 | `private static int True;` |
| 0x4 | `private static int False;` |
| - | `private const string PromptSignInKey = "prompt_sign_in";` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37975F0 | 0x2F7D790 |  | `public static SignInStatus ToSignInStatus(int code)` |
| 0x37977B4 | 0x2F7D798 |  | `public static void SetPromptUiSignIn(bool value)` |
| 0x3797858 | 0x2F7D79C |  | `public static bool ShouldPromptUiSignIn()` |
| 0x3797904 | 0x2F7D7A4 |  | `public void .ctor()` |

</details>

### public enum `SignInInteractivity`  
`TypeDefIndex 3826`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const SignInInteractivity NoPrompt = 0;` |
| - | `public const SignInInteractivity CanPromptAlways = 1;` |
| - | `public const SignInInteractivity CanPromptOnce = 2;` |

### public enum `SignInStatus`  
`TypeDefIndex 3827`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const SignInStatus Success = 0;` |
| - | `public const SignInStatus UiSignInRequired = 1;` |
| - | `public const SignInStatus DeveloperError = 2;` |
| - | `public const SignInStatus NetworkError = 3;` |
| - | `public const SignInStatus InternalError = 4;` |
| - | `public const SignInStatus Canceled = 5;` |
| - | `public const SignInStatus AlreadyInProgress = 6;` |
| - | `public const SignInStatus Failed = 7;` |
| - | `public const SignInStatus NotAuthenticated = 8;` |

### public enum `UIStatus`  
`TypeDefIndex 3828`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const UIStatus Valid = 0;` |
| - | `public const UIStatus InternalError = 1;` |
| - | `public const UIStatus NotAuthorized = 2;` |
| - | `public const UIStatus VersionUpdateRequired = 3;` |
| - | `public const UIStatus Timeout = 4;` |
| - | `public const UIStatus UserClosedUI = 5;` |
| - | `public const UIStatus UiBusy = 6;` |
| - | `public const UIStatus NetworkError = 7;` |

### public enum `VideoCaptureMode`  
`TypeDefIndex 3829`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const VideoCaptureMode Unknown = 0;` |
| - | `public const VideoCaptureMode File = 1;` |
| - | `public const VideoCaptureMode Stream = 2;` |

### public enum `VideoCaptureOverlayState`  
`TypeDefIndex 3830`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const VideoCaptureOverlayState Unknown = 0;` |
| - | `public const VideoCaptureOverlayState Shown = 1;` |
| - | `public const VideoCaptureOverlayState Started = 2;` |
| - | `public const VideoCaptureOverlayState Stopped = 3;` |
| - | `public const VideoCaptureOverlayState Dismissed = 4;` |

### public enum `VideoQualityLevel`  
`TypeDefIndex 3831`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const VideoQualityLevel Unknown = 0;` |
| - | `public const VideoQualityLevel SD = 1;` |
| - | `public const VideoQualityLevel HD = 2;` |
| - | `public const VideoQualityLevel XHD = 3;` |
| - | `public const VideoQualityLevel FullHD = 4;` |
