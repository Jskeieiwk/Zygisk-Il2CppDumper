# namespace `GooglePlayGames`  (12 types)

### public static class `GameInfo`  
`TypeDefIndex 3786`

| offset | field |
|---|---|
| - | `private const string UnescapedApplicationId = "APP_ID";` |
| - | `private const string UnescapedIosClientId = "IOS_CLIENTID";` |
| - | `private const string UnescapedWebClientId = "WEB_CLIENTID";` |
| - | `private const string UnescapedNearbyServiceId = "NEARBY_SERVICE_ID";` |
| - | `public const string ApplicationId = "506813099327";` |
| - | `public const string IosClientId = "__IOS_CLIENTID__";` |
| - | `public const string WebClientId = "506813099327-otok7cdk4bp57bnc8f6fqq26nifi1vri.apps.googleusercontent.com";` |
| - | `public const string NearbyConnectionServiceId = "";` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3764750 | 0x2F7CCE8 |  | `public static bool ApplicationIdInitialized()` |
| 0x3764860 | 0x2F7CCF0 |  | `public static bool IosClientIdInitialized()` |
| 0x3764910 | 0x2F7CCF8 |  | `public static bool WebClientIdInitialized()` |
| 0x37649C0 | 0x2F7CD00 |  | `public static bool NearbyConnectionsInitialized()` |
| 0x3764800 | 0x2F7CD08 |  | `private static string ToEscapedToken(string token)` |

</details>

### public static class `NearbyConnectionClientFactory`  
`TypeDefIndex 3787`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376D6F4 | 0x2F7CD10 |  | `public static void Create(Action<INearbyConnectionClient> callback)` |

</details>

### internal class `PlayGamesAchievement` : IAchievement, IAchievementDescription  
`TypeDefIndex 3788`

| offset | field |
|---|---|
| 0x10 | `private readonly ReportProgress mProgressCallback;` |
| 0x18 | `private string mId;` |
| 0x20 | `private bool mIsIncremental;` |
| 0x24 | `private int mCurrentSteps;` |
| 0x28 | `private int mTotalSteps;` |
| 0x30 | `private double mPercentComplete;` |
| 0x38 | `private bool mCompleted;` |
| 0x39 | `private bool mHidden;` |
| 0x40 | `private DateTime mLastModifiedTime;` |
| 0x48 | `private string mTitle;` |
| 0x50 | `private string mRevealedImageUrl;` |
| 0x58 | `private string mUnlockedImageUrl;` |
| 0x60 | `private UnityWebRequest mImageFetcher;` |
| 0x68 | `private Texture2D mImage;` |
| 0x70 | `private string mDescription;` |
| 0x78 | `private ulong mPoints;` |

Properties: `public string id { get; set; }`; `public bool isIncremental { get; }`; `public int currentSteps { get; }`; `public int totalSteps { get; }`; `public double percentCompleted { get; set; }`; `public bool completed { get; }`; `public bool hidden { get; }`; `public DateTime lastReportedDate { get; }`; `public string title { get; }`; `public Texture2D image { get; }`; `public string achievedDescription { get; }`; `public string unachievedDescription { get; }`; `public int points { get; }`

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37650EC | 0x2F7CD14 | 5 | `public string get_id()` |
| 0x37650F4 | 0x2F7CD1C | 6 | `public void set_id(string value)` |
| 0x37650FC | 0x2F7CD20 |  | `public bool get_isIncremental()` |
| 0x3765104 | 0x2F7CD28 |  | `public int get_currentSteps()` |
| 0x376510C | 0x2F7CD30 |  | `public int get_totalSteps()` |
| 0x3765114 | 0x2F7CD38 | 7 | `public double get_percentCompleted()` |
| 0x376511C | 0x2F7CD40 | 8 | `public void set_percentCompleted(double value)` |
| 0x3765124 | 0x2F7CD44 | 9 | `public bool get_completed()` |
| 0x376512C | 0x2F7CD4C | 10 | `public bool get_hidden()` |
| 0x3765134 | 0x2F7CD54 | 11 | `public DateTime get_lastReportedDate()` |
| 0x376513C | 0x2F7CD5C | 12 | `public string get_title()` |
| 0x3765144 | 0x2F7CD64 | 13 | `public Texture2D get_image()` |
| 0x3765148 | 0x2F7CD6C | 14 | `public string get_achievedDescription()` |
| 0x3765150 | 0x2F7CD74 | 15 | `public string get_unachievedDescription()` |
| 0x3765158 | 0x2F7CD7C | 16 | `public int get_points()` |
| 0x3764BDC | 0x2F7CD84 |  | `internal void .ctor()` |
| 0x3764D60 | 0x2F7CD8C |  | `internal void .ctor(ReportProgress progressCallback)` |
| 0x3764E7C | 0x2F7CD94 |  | `internal void .ctor(Achievement ach)` |
| 0x3764F84 | 0x2F7CD9C | 4 | `public void ReportProgress(Action<bool> callback)` |
| 0x3764FB4 | 0x2F7CDA0 |  | `private Texture2D LoadImage()` |

</details>

### internal class `PlayGamesClientFactory`  
`TypeDefIndex 3789`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376DB0C | 0x2F7CDA8 |  | `internal static IPlayGamesClient GetPlatformPlayGamesClient(PlayGamesClientConfiguration config)` |
| 0x376DE48 | 0x2F7CDB0 |  | `public void .ctor()` |

</details>

### public class `PlayGamesLeaderboard` : ILeaderboard  
`TypeDefIndex 3790`

| offset | field |
|---|---|
| 0x10 | `private string mId;` |
| 0x18 | `private UserScope mUserScope;` |
| 0x1C | `private Range mRange;` |
| 0x24 | `private TimeScope mTimeScope;` |
| 0x28 | `private string[] mFilteredUserIds;` |
| 0x30 | `private bool mLoading;` |
| 0x38 | `private IScore mLocalUserScore;` |
| 0x40 | `private uint mMaxRange;` |
| 0x48 | `private List<PlayGamesScore> mScoreList;` |
| 0x50 | `private string mTitle;` |

Properties: `public bool loading { get; set; }`; `public string id { get; set; }`; `public UserScope userScope { get; set; }`; `public Range range { get; set; }`; `public TimeScope timeScope { get; set; }`; `public IScore localUserScore { get; }`; `public uint maxRange { get; }`; `public IScore[] scores { get; }`; `public string title { get; }`; `public int ScoreCount { get; }`

<details><summary>methods (24)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3765880 | 0x2F7CDB8 | 4 | `public bool get_loading()` |
| 0x3765888 | 0x2F7CDC0 |  | `internal void set_loading(bool value)` |
| 0x3765894 | 0x2F7CDC4 | 5 | `public string get_id()` |
| 0x376589C | 0x2F7CDCC | 11 | `public void set_id(string value)` |
| 0x37658A4 | 0x2F7CDD0 | 6 | `public UserScope get_userScope()` |
| 0x37658AC | 0x2F7CDD8 | 12 | `public void set_userScope(UserScope value)` |
| 0x37658B4 | 0x2F7CDDC | 7 | `public Range get_range()` |
| 0x37658BC | 0x2F7CDE4 | 13 | `public void set_range(Range value)` |
| 0x37658C4 | 0x2F7CDE8 | 8 | `public TimeScope get_timeScope()` |
| 0x37658CC | 0x2F7CDF0 | 14 | `public void set_timeScope(TimeScope value)` |
| 0x37658D4 | 0x2F7CDF4 | 15 | `public IScore get_localUserScore()` |
| 0x37658DC | 0x2F7CDFC | 16 | `public uint get_maxRange()` |
| 0x37658E4 | 0x2F7CE04 | 17 | `public IScore[] get_scores()` |
| 0x376597C | 0x2F7CE0C | 18 | `public string get_title()` |
| 0x3765D4C | 0x2F7CE14 |  | `public int get_ScoreCount()` |
| 0x3765160 | 0x2F7CE1C |  | `public void .ctor(string id)` |
| 0x37651FC | 0x2F7CE24 | 9 | `public void SetUserFilter(string[] userIDs)` |
| 0x3765204 | 0x2F7CE28 | 10 | `public void LoadScores(Action<bool> callback)` |
| 0x3765984 | 0x2F7CE2C |  | `internal bool SetFromData(LeaderboardScoreData data)` |
| 0x3765B9C | 0x2F7CE34 |  | `internal void SetMaxRange(ulong val)` |
| 0x3765D3C | 0x2F7CE38 |  | `internal void SetTitle(string value)` |
| 0x3765D44 | 0x2F7CE3C |  | `internal void SetLocalUserScore(PlayGamesScore score)` |
| 0x3765BA4 | 0x2F7CE40 |  | `internal int AddScore(PlayGamesScore score)` |
| 0x3765CD4 | 0x2F7CE48 |  | `internal bool HasAllScores()` |

</details>

### public class `PlayGamesLocalUser` : PlayGamesUserProfile, ILocalUser, IUserProfile  
`TypeDefIndex 3791`

| offset | field |
|---|---|
| 0x38 | `internal PlayGamesPlatform mPlatform;` |
| 0x40 | `private string emailAddress;` |
| 0x48 | `private PlayerStats mStats;` |

Properties: `public IUserProfile[] friends { get; }`; `public bool authenticated { get; }`; `public bool underage { get; }`; `public string userName { get; }`; `public string id { get; }`; `public bool isFriend { get; }`; `public UserState state { get; }`; `public string AvatarURL { get; }`; `public string Email { get; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37661EC | 0x2F7CE50 | 13 | `public IUserProfile[] get_friends()` |
| 0x376646C | 0x2F7CE58 | 10 | `public bool get_authenticated()` |
| 0x3766534 | 0x2F7CE60 | 14 | `public bool get_underage()` |
| 0x376653C | 0x2F7CE68 | 15 | `public string get_userName()` |
| 0x376698C | 0x2F7CE70 | 16 | `public string get_id()` |
| 0x3766A54 | 0x2F7CE78 | 17 | `public bool get_isFriend()` |
| 0x3766A5C | 0x2F7CE80 | 18 | `public UserState get_state()` |
| 0x3766A64 | 0x2F7CE88 |  | `public string get_AvatarURL()` |
| 0x3766B2C | 0x2F7CE90 |  | `public string get_Email()` |
| 0x3765D94 | 0x2F7CE98 |  | `internal void .ctor(PlayGamesPlatform plaf)` |
| 0x3765E58 | 0x2F7CEE0 | 11 | `public void Authenticate(Action<bool> callback)` |
| 0x3765E7C | 0x2F7CEE4 | 9 | `public void Authenticate(Action<bool, string> callback)` |
| 0x3765EA0 | 0x2F7CEE8 |  | `public void Authenticate(Action<bool> callback, bool silent)` |
| 0x3765F90 | 0x2F7CEEC |  | `public void Authenticate(Action<bool, string> callback, bool silent)` |
| 0x3766088 | 0x2F7CEF0 | 12 | `public void LoadFriends(Action<bool> callback)` |
| 0x3766340 | 0x2F7CEF4 |  | `public string GetIdToken()` |
| 0x3766CA0 | 0x2F7CEFC |  | `public void GetStats(Action<CommonStatusCodes, PlayerStats> callback)` |

</details>

### public class `PlayGamesPlatform` : ISocialPlatform  
`TypeDefIndex 3792`

| offset | field |
|---|---|
| 0x0 | `private static PlayGamesPlatform sInstance;` |
| 0x8 | `private static bool sNearbyInitializePending;` |
| 0x10 | `private static INearbyConnectionClient sNearbyConnectionClient;` |
| 0x10 | `private readonly PlayGamesClientConfiguration mConfiguration;` |
| 0x30 | `private PlayGamesLocalUser mLocalUser;` |
| 0x38 | `private IPlayGamesClient mClient;` |
| 0x40 | `private string mDefaultLbUi;` |
| 0x48 | `private Dictionary<string, string> mIdMap;` |

Properties: `public static bool DebugLogEnabled { get; set; }`; `public static PlayGamesPlatform Instance { get; }`; `public static INearbyConnectionClient Nearby { get; }`; `public ISavedGameClient SavedGame { get; }`; `public IEventsClient Events { get; }`; `public IVideoClient Video { get; }`; `public ILocalUser localUser { get; }`

<details><summary>methods (83)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376726C | 0x2F7CF00 |  | `public static bool get_DebugLogEnabled()` |
| 0x37672F4 | 0x2F7CF08 |  | `public static void set_DebugLogEnabled(bool value)` |
| 0x3764C54 | 0x2F7CF0C |  | `public static PlayGamesPlatform get_Instance()` |
| 0x37674F4 | 0x2F7CF14 |  | `public static INearbyConnectionClient get_Nearby()` |
| 0x3767798 | 0x2F7CF1C |  | `public ISavedGameClient get_SavedGame()` |
| 0x376783C | 0x2F7CF24 |  | `public IEventsClient get_Events()` |
| 0x37678E0 | 0x2F7CF2C |  | `public IVideoClient get_Video()` |
| 0x3767984 | 0x2F7CF34 | 4 | `public ILocalUser get_localUser()` |
| 0x3766FE4 | 0x2F7CF3C |  | `internal void .ctor(IPlayGamesClient client)` |
| 0x3767128 | 0x2F7CF44 |  | `private void .ctor(PlayGamesClientConfiguration configuration)` |
| 0x3767384 | 0x2F7CF4C |  | `public static void InitializeInstance(PlayGamesClientConfiguration configuration)` |
| 0x3767588 | 0x2F7CF50 |  | `public static void InitializeNearby(Action<INearbyConnectionClient> callback)` |
| 0x376798C | 0x2F7CF54 |  | `public static PlayGamesPlatform Activate()` |
| 0x3767A84 | 0x2F7CF5C |  | `public void SetGravityForPopups(Gravity gravity)` |
| 0x3767B30 | 0x2F7CF60 |  | `public void AddIdMapping(string fromId, string toId)` |
| 0x3765E74 | 0x2F7CF64 |  | `public void Authenticate(Action<bool> callback)` |
| 0x3765E98 | 0x2F7CF68 |  | `public void Authenticate(Action<bool, string> callback)` |
| 0x3765EBC | 0x2F7CF6C |  | `public void Authenticate(Action<bool> callback, bool silent)` |
| 0x3765FAC | 0x2F7CF70 |  | `public void Authenticate(Action<bool, string> callback, bool silent)` |
| 0x3767B98 | 0x2F7CF74 |  | `public void Authenticate(SignInInteractivity signInInteractivity, Action<SignInStatus> callback)` |
| 0x3767FE8 | 0x2F7CF78 | 5 | `public void Authenticate(ILocalUser unused, Action<bool> callback)` |
| 0x3767FF4 | 0x2F7CF7C | 6 | `public void Authenticate(ILocalUser unused, Action<bool, string> callback)` |
| 0x3766484 | 0x2F7CF80 |  | `public bool IsAuthenticated()` |
| 0x3768000 | 0x2F7CF88 |  | `public void SignOut()` |
| 0x37680D8 | 0x2F7CF8C | 8 | `public void LoadUsers(string[] userIds, Action<IUserProfile[]> callback)` |
| 0x3766744 | 0x2F7CF90 |  | `public string GetUserId()` |
| 0x3766358 | 0x2F7CF98 |  | `public string GetIdToken()` |
| 0x3768248 | 0x2F7CFA0 |  | `public string GetServerAuthCode()` |
| 0x3768364 | 0x2F7CFA8 |  | `public void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback)` |
| 0x3766BFC | 0x2F7CFAC |  | `public string GetUserEmail()` |
| 0x3766DC0 | 0x2F7CFB4 |  | `public void GetPlayerStats(Action<CommonStatusCodes, PlayerStats> callback)` |
| 0x3766604 | 0x2F7CFB8 |  | `public string GetUserDisplayName()` |
| 0x3766868 | 0x2F7CFC0 |  | `public string GetUserImageUrl()` |
| 0x3768620 | 0x2F7CFC8 | 9 | `public void ReportProgress(string achievementID, double progress, Action<bool> callback)` |
| 0x3768B0C | 0x2F7CFCC |  | `internal static int progressToSteps(double progress, int totalSteps)` |
| 0x3768B4C | 0x2F7CFD4 |  | `public void RevealAchievement(string achievementID, Action<bool> callback)` |
| 0x3768D00 | 0x2F7CFD8 |  | `public void UnlockAchievement(string achievementID, Action<bool> callback)` |
| 0x3768EB4 | 0x2F7CFDC |  | `public void IncrementAchievement(string achievementID, int steps, Action<bool> callback)` |
| 0x376909C | 0x2F7CFE0 |  | `public void SetStepsAtLeast(string achievementID, int steps, Action<bool> callback)` |
| 0x3769284 | 0x2F7CFE4 | 10 | `public void LoadAchievementDescriptions(Action<IAchievementDescription[]> callback)` |
| 0x3769458 | 0x2F7CFE8 | 11 | `public void LoadAchievements(Action<IAchievement[]> callback)` |
| 0x376961C | 0x2F7CFEC | 12 | `public IAchievement CreateAchievement()` |
| 0x376966C | 0x2F7CFF4 | 13 | `public void ReportScore(long score, string board, Action<bool> callback)` |
| 0x3769854 | 0x2F7CFF8 |  | `public void ReportScore(long score, string board, string metadata, Action<bool> callback)` |
| 0x3769B30 | 0x2F7CFFC | 14 | `public void LoadScores(string leaderboardId, Action<IScore[]> callback)` |
| 0x3769C94 | 0x2F7D000 |  | `public void LoadScores(string leaderboardId, LeaderboardStart start, int rowCount, LeaderboardCollection collection, LeaderboardTimeSpan timeSpan, Action<LeaderboardScoreData> callback)` |
| 0x3769E4C | 0x2F7D004 |  | `public void LoadMoreScores(ScorePageToken token, int rowCount, Action<LeaderboardScoreData> callback)` |
| 0x3769FDC | 0x2F7D008 | 15 | `public ILeaderboard CreateLeaderboard()` |
| 0x376A038 | 0x2F7D010 | 16 | `public void ShowAchievementsUI()` |
| 0x376A040 | 0x2F7D014 |  | `public void ShowAchievementsUI(Action<UIStatus> callback)` |
| 0x376A1D8 | 0x2F7D018 | 17 | `public void ShowLeaderboardUI()` |
| 0x376A290 | 0x2F7D01C |  | `public void ShowLeaderboardUI(string leaderboardId)` |
| 0x376A284 | 0x2F7D020 |  | `public void ShowLeaderboardUI(string leaderboardId, Action<UIStatus> callback)` |
| 0x376A2BC | 0x2F7D024 |  | `public void ShowLeaderboardUI(string leaderboardId, LeaderboardTimeSpan span, Action<UIStatus> callback)` |
| 0x376A4B0 | 0x2F7D028 |  | `public void SetDefaultLeaderboardForUI(string lbid)` |
| 0x37660A4 | 0x2F7D02C | 18 | `public void LoadFriends(ILocalUser user, Action<bool> callback)` |
| 0x3765234 | 0x2F7D030 | 19 | `public void LoadScores(ILeaderboard board, Action<bool> callback)` |
| 0x376A57C | 0x2F7D034 |  | `public void RequestPermission(string scope, Action<SignInStatus> callback)` |
| 0x376A60C | 0x2F7D038 |  | `public void RequestPermissions(string[] scopes, Action<SignInStatus> callback)` |
| 0x376A75C | 0x2F7D03C |  | `public bool HasPermission(string scope)` |
| 0x376A7E4 | 0x2F7D044 |  | `public bool HasPermissions(string[] scopes)` |
| 0x376A910 | 0x2F7D04C | 7 | `public bool GetLoading(ILeaderboard board)` |
| 0x376A9B8 | 0x2F7D054 |  | `public void ShowCompareProfileWithAlternativeNameHintsUI(string userId, string otherPlayerInGameName, string currentPlayerInGameName, Action<UIStatus> callback)` |
| 0x376ABAC | 0x2F7D058 |  | `public void GetFriendsListVisibility(bool forceReload, Action<FriendsListVisibilityStatus> callback)` |
| 0x376AD70 | 0x2F7D05C |  | `public void AskForLoadFriendsResolution(Action<UIStatus> callback)` |
| 0x376AF2C | 0x2F7D060 |  | `public LoadFriendsStatus GetLastLoadFriendsStatus()` |
| 0x376B050 | 0x2F7D068 |  | `public void LoadFriends(int pageSize, bool forceReload, Action<LoadFriendsStatus> callback)` |
| 0x376B1B4 | 0x2F7D06C |  | `public void LoadMoreFriends(int pageSize, Action<LoadFriendsStatus> callback)` |
| 0x376B310 | 0x2F7D070 |  | `internal void HandleLoadingScores(PlayGamesLeaderboard board, LeaderboardScoreData scoreData, Action<bool> callback)` |
| 0x3766204 | 0x2F7D074 |  | `internal IUserProfile[] GetFriends()` |
| 0x37689E8 | 0x2F7D07C |  | `private string MapId(string id)` |
| - | - |  | `private static void InvokeCallbackOnGameThread<T>(Action<T> callback, T data)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38802E4 Offset: 0x387C2E4 VA: 0x38802E4` |
| - | - |  | `\|-PlayGamesPlatform.InvokeCallbackOnGameThread<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |
| - | - |  | `private static Action<T> ToOnGameThread<T>(Action<T> toConvert)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38802E8 Offset: 0x387C2E8 VA: 0x38802E8` |
| - | - |  | `\|-PlayGamesPlatform.ToOnGameThread<__Il2CppFullySharedGenericType>` |
| - | - |  | `*/` |

</details>

### public class `PlayGamesScore` : IScore  
`TypeDefIndex 3793`

| offset | field |
|---|---|
| 0x10 | `private string mLbId;` |
| 0x18 | `private long mValue;` |
| 0x20 | `private ulong mRank;` |
| 0x28 | `private string mPlayerId;` |
| 0x30 | `private string mMetadata;` |
| 0x38 | `private DateTime mDate;` |

Properties: `public string leaderboardID { get; set; }`; `public long value { get; set; }`; `public DateTime date { get; }`; `public string formattedValue { get; }`; `public string userID { get; }`; `public int rank { get; }`; `public string metaData { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376CC4C | 0x2F7D084 | 5 | `public string get_leaderboardID()` |
| 0x376CC54 | 0x2F7D08C | 6 | `public void set_leaderboardID(string value)` |
| 0x376CC5C | 0x2F7D090 | 7 | `public long get_value()` |
| 0x376CC64 | 0x2F7D098 | 8 | `public void set_value(long value)` |
| 0x376CC6C | 0x2F7D09C | 9 | `public DateTime get_date()` |
| 0x376CC74 | 0x2F7D0A4 | 10 | `public string get_formattedValue()` |
| 0x376CC80 | 0x2F7D0AC | 11 | `public string get_userID()` |
| 0x376CC88 | 0x2F7D0B4 | 12 | `public int get_rank()` |
| 0x376CC90 | 0x2F7D0BC |  | `public string get_metaData()` |
| 0x376CAF8 | 0x2F7D0C4 |  | `internal void .ctor(DateTime date, string leaderboardId, ulong rank, string playerId, ulong value, string metadata)` |
| 0x376CC10 | 0x2F7D0CC | 4 | `public void ReportScore(Action<bool> callback)` |

</details>

### public class `PlayGamesUserProfile` : IUserProfile  
`TypeDefIndex 3795`

| offset | field |
|---|---|
| 0x10 | `private string mDisplayName;` |
| 0x18 | `private string mPlayerId;` |
| 0x20 | `private string mAvatarUrl;` |
| 0x28 | `private bool mIsFriend;` |
| 0x29 | `private bool mImageLoading;` |
| 0x30 | `private Texture2D mImage;` |

Properties: `public string userName { get; }`; `public string id { get; }`; `public string gameId { get; }`; `public bool isFriend { get; }`; `public UserState state { get; }`; `public Texture2D image { get; }`; `public string AvatarURL { get; }`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376CEF8 | 0x2F7D0D0 | 4 | `public string get_userName()` |
| 0x376CF00 | 0x2F7D0D8 | 5 | `public string get_id()` |
| 0x376CF08 | 0x2F7D0E0 |  | `public string get_gameId()` |
| 0x376CF10 | 0x2F7D0E8 | 6 | `public bool get_isFriend()` |
| 0x376CF18 | 0x2F7D0F0 | 7 | `public UserState get_state()` |
| 0x376CF20 | 0x2F7D0F8 | 8 | `public Texture2D get_image()` |
| 0x376D210 | 0x2F7D100 |  | `public string get_AvatarURL()` |
| 0x376CC98 | 0x2F7CED8 |  | `internal void .ctor(string displayName, string playerId, string avatarUrl)` |
| 0x376CE04 | 0x2F7D108 |  | `internal void .ctor(string displayName, string playerId, string avatarUrl, bool isFriend)` |
| 0x376CE78 | 0x2F7D110 |  | `protected void ResetIdentity(string displayName, string playerId, string avatarUrl)` |
| - | 0x2F7D114 |  | `internal IEnumerator LoadImage()` |
| 0x376D240 | 0x2F7D11C | 0 | `public override bool Equals(object obj)` |
| 0x376D360 | 0x2F7D124 | 2 | `public override int GetHashCode()` |
| 0x376D410 | 0x2F7D12C | 3 | `public override string ToString()` |
| 0x376CD00 | 0x2F7D134 |  | `private void setAvatarUrl(string avatarUrl)` |

</details>

### public class `PluginVersion`  
`TypeDefIndex 3796`

| offset | field |
|---|---|
| - | `public const int VersionInt = 4116;` |
| - | `public const string VersionString = "0.10.14";` |
| - | `public const string VersionKey = "01014";` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x376DE50 | 0x2F7D160 |  | `public void .ctor()` |

</details>

### internal sealed class `ReportProgress` : MulticastDelegate  
`TypeDefIndex 3797`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F7D168 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F7D21C |  | `public virtual void Invoke(string id, double progress, Action<bool> callback)` |
| - | 0x2F7D230 |  | `public virtual IAsyncResult BeginInvoke(string id, double progress, Action<bool> callback, AsyncCallback __callback, object object)` |
| - | 0x2F7D2C8 |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### internal interface `TokenClient`  
`TypeDefIndex 3798`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract string GetEmail();` |
| - | - |  | `public abstract string GetAuthCode();` |
| - | - |  | `public abstract string GetIdToken();` |
| - | - |  | `public abstract void GetAnotherServerAuthCode(bool reAuthenticateIfNeeded, Action<string> callback);` |
| - | - |  | `public abstract void Signout();` |
| - | - |  | `public abstract void SetRequestAuthCode(bool flag, bool forceRefresh);` |
| - | - |  | `public abstract void SetRequestEmail(bool flag);` |
| - | - |  | `public abstract void SetRequestIdToken(bool flag);` |
| - | - |  | `public abstract void SetWebClientId(string webClientId);` |
| - | - |  | `public abstract void SetAccountName(string accountName);` |
| - | - |  | `public abstract void AddOauthScopes(string[] scopes);` |
| - | - |  | `public abstract void SetHidePopups(bool flag);` |
| - | - |  | `public abstract void FetchTokens(bool silent, Action<int> callback);` |
| - | - |  | `public abstract void RequestPermissions(string[] scopes, Action<SignInStatus> callback);` |
| - | - |  | `public abstract bool HasPermissions(string[] scopes);` |

</details>
