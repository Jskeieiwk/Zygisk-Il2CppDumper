# namespace `HyperHug.Games.Oxide`  (29 types)

### public struct `AppleSignInConnectOptions`  
`TypeDefIndex 3291`

| offset | field |
|---|---|
| 0x0 | `public bool ShowLoading;` |
| 0x1 | `public bool ForceLink;` |
| 0x8 | `public Action OnAppleResponseGot;` |
| 0x10 | `public Action OnSuccess;` |
| 0x18 | `public Action<string, string, PlayFabError> OnFail;` |

### public class `AutoSnowballTurret` : AutoTurretBase  
`TypeDefIndex 3292`

| offset | field |
|---|---|
| - | `private const float kDV = 0.1;` |
| - | `private const float kDg = 1;` |
| 0x160 | `public ShaftedProjectile snowballPrefab;` |
| 0x168 | `public Transform shootPoint;` |
| 0x170 | `private Vector3 kDp;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37BA864 | 0x2EDAE04 |  | `private void Start()` |
| 0x37BA868 | 0x2EDAE08 | 34 | `protected override void drU()` |
| 0x37BAC60 | 0x2EDB2A0 |  | `public void .ctor()` |
| 0x37BADBC | 0x2EDB42C | 12 | `public override bool Fuk()` |

</details>

### public class `AutoTurret` : AutoTurretBase  
`TypeDefIndex 3293`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37BADC4 | 0x2EDB434 |  | `public void .ctor()` |
| 0x37BAE18 | 0x2EDB488 | 12 | `public override bool Fuk()` |

</details>

### public class `AutoTurretBase` : Xb, Xa  
`TypeDefIndex 3295`

| offset | field |
|---|---|
| 0x0 | `private static readonly float[] kDv;` |
| 0x80 | `public Ws targetTrigger;` |
| 0x88 | `public XE entityHandler;` |
| 0x90 | `public PlayerManager target;` |
| 0x98 | `public Transform eyePos;` |
| 0xA0 | `public Vector3 aimDir;` |
| 0xB0 | `public Transform gunYaw;` |
| 0xB8 | `public Transform gunPitch;` |
| 0xC0 | `public Transform centerMuzzle;` |
| 0xC8 | `public float sightRange;` |
| 0xCC | `public float aimCone;` |
| 0xD0 | `public AutoTurretBase.rj flags;` |
| 0xD8 | `public BuildingPiece piece;` |
| 0xE0 | `public LayerMask visibilityMask;` |
| 0xE8 | `public string ammoId;` |
| 0xF0 | `public float fireRate;` |
| 0xF4 | `protected int m_Capacity;` |
| 0xF8 | `private string panelName;` |
| 0x100 | `private SoundPlayer m_FireAudio;` |
| 0x108 | `private ParticleSystem m_MuzzleFlash;` |
| 0x110 | `private AudioSource m_AudioSource;` |
| 0x118 | `private yU kDS;` |
| 0x120 | `private Vector3 kDI;` |
| 0x12C | `private Vector3 kDM;` |
| 0x138 | `protected bool kne;` |
| 0x13C | `private int knf;` |
| 0x140 | `private float knF;` |
| 0x144 | `private float knd;` |
| 0x148 | `private float knc;` |
| 0x14C | `private float knU;` |
| 0x150 | `private float knY;` |
| 0x154 | `private float knW;` |
| - | `private ItemHolder[] <knE>k__BackingField;` |

Properties: `public ItemHolder[] knE { get; set; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EDB490 |  | `public ItemHolder[] get_knE()` |
| - | 0x2EDB498 |  | `private void set_knE(ItemHolder[] value)` |
| 0x37BAE38 | 0x2EDB4A8 | 33 | `public override bool drE(out string e)` |
| 0x37BAE58 | 0x2EDB4C8 |  | `public void Update()` |
| 0x37BAE68 | 0x2EDB4D8 | 34 | `protected virtual void drU()` |
| 0x37BB1C8 | 0x2EDB744 |  | `protected Quaternion drA(Quaternion e, Quaternion f, float F)` |
| 0x37BB254 | 0x2EDB7D0 |  | `private void dru(Vector3 e)` |
| 0x37BB398 | 0x2EDB818 |  | `protected void drk()` |
| 0x37BB4B0 | 0x2EDB8B8 |  | `protected void drO(Vector3 e, Quaternion f, int F)` |
| 0x37BACB4 | 0x2EDB2F4 |  | `public void .ctor()` |
| 0x37BB644 | 0x2EDBAB0 |  | `private static void .cctor()` |
| 0x37BB8D0 | 0x2EDBD08 | 12 | `public override bool Fuk()` |
| 0x37BB8D8 | 0x2EDB7F4 |  | `protected void drt(Vector3 e)` |
| 0x37BB8E4 | 0x2EDBD10 |  | `protected static void drr(vd e, vo f, vt F)` |
| 0x37BBA20 | 0x2EDB81C |  | `protected void drN()` |
| 0x37BBA60 | 0x2EDBDBC |  | `protected static void drq(vd e, vo f, vt F)` |
| 0x37BBB7C | 0x2EDB8BC |  | `protected void drs(Vector3 e, Quaternion f, int F)` |
| 0x37BBCDC | 0x2EDBE3C |  | `protected static void drC(vd e, vo f, vt F)` |

</details>

### public class `BattlePassCongratulationPopupReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3296`

| offset | field |
|---|---|
| 0x20 | `public BattlePassBaseRewardView battlePassBaseRewardView;` |
| 0x28 | `public ScrollRect scrollRect;` |
| 0x30 | `public Transform RewardParent;` |
| 0x38 | `public Button ClaimButton;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37BA85C | 0x2EDBF3C |  | `public void .ctor()` |

</details>

### public class `Bootstrap` : MonoBehaviour, IDisposable  
`TypeDefIndex 3332`

| offset | field |
|---|---|
| 0x20 | `private bool kng;` |
| 0x28 | `private string knp;` |
| 0x30 | `private string knv;` |
| 0x38 | `private Bootstrap.ra knS;` |
| 0x3C | `public bool isRegistered;` |
| 0x48 | `private dQ appleAuthManagerProxy;` |
| 0x50 | `private AppleSignInLinkWindow appleSignInLinkWindow;` |
| 0x58 | `private LoginMethodButtonHandler loginMethodButtonHandler;` |
| 0x60 | `private ServicesManager servicesManager;` |
| 0x68 | `public Image agreementLine;` |
| 0x70 | `public ClickableErrorWindow clickableErrorWindow;` |
| 0x78 | `public GameObject guestNoticePanel;` |
| 0x80 | `public GameObject loginPanel;` |
| 0x88 | `public Toggle agreementToggle;` |
| 0x90 | `private Color knM;` |
| 0xA0 | `private Hr kVe;` |
| 0xA8 | `private bool kVf;` |
| 0xA9 | `private bool kVF;` |
| 0xAC | `private cd kVd;` |
| 0xB0 | `public GameObject voiceNoticePanel;` |
| 0xB8 | `public int version;` |
| 0xC0 | `private DeleteAccountConfirmationPopup deleteAccountConfirmationPopup;` |
| 0xC8 | `private LootboxShopsMenuManager _lootboxShopsMenuManager;` |
| 0xD0 | `public GameObject canvas;` |
| 0xD8 | `public GameObject errorPanel;` |
| 0xE0 | `public Text errorText;` |
| 0xE8 | `public GameObject menuUI;` |
| 0xF0 | `public GameObject loadingUI;` |
| 0xF8 | `public GameObject labelPrime;` |
| 0x100 | `public LoadingPanel loadingPanel;` |
| 0x108 | `public sR battlePassButton;` |
| 0x110 | `public sR missoinsButton;` |
| 0x118 | `public GameObject loadingMainUi;` |
| 0x120 | `public LanguagePanelReferenceHolder languagePanelReferenceHolder;` |
| 0x128 | `private cM kVc;` |
| 0x130 | `private qW kVU;` |
| 0x138 | `private bool kVY;` |
| 0x140 | `private rv kVW;` |
| 0x148 | `private Hu kVE;` |
| 0x150 | `private Ce kVA;` |
| 0x158 | `private Coroutine kVu;` |
| 0x160 | `private CancellationTokenSource kVk;` |
| 0x168 | `private sy kVO;` |
| 0x170 | `private sr kVt;` |
| 0x178 | `private qx kVr;` |
| 0x180 | `private fEd kVN;` |
| - | `public const bool GuestLoginEnabled = false;` |
| - | `private const string PlayFabTitleId = "53333";` |
| - | `private bool savedLoginRetryPending;` |
| - | `private bool menuTransitionInProgress;` |

Properties: `public Bootstrap.rQ knI { get; set; }`; `public ClickableErrorWindow sRy { get; }`

<details><summary>methods (67)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37BC380 | 0x2EDBF44 |  | `public Bootstrap.rQ get_knI()` |
| 0x37BC388 | 0x2EDBF4C |  | `private void set_knI(Bootstrap.rQ value)` |
| 0x37BD6BC | 0x2EDBF50 |  | `public ClickableErrorWindow get_sRy()` |
| 0x37BBE94 | 0x2EDBF58 |  | `private void dNc(Action<string> e)` |
| 0x37BBF10 | 0x2EDBFD4 |  | `private void dNU(bool e)` |
| 0x37BC138 | 0x2EDC078 |  | `public void LoginPlayGames()` |
| 0x37BC140 | 0x2EDC09C |  | `private void dNY()` |
| 0x37BC390 | 0x2EDC2D4 |  | `public void SetConfigReady()` |
| 0x37BC39C | 0x2EDC2E0 |  | `private IEnumerator dNA()` |
| 0x37BC430 | 0x2EDC374 |  | `private string dNu()` |
| 0x37BC378 | 0x2EDC37C |  | `private static string dNk()` |
| 0x37BC438 | 0x2EDC384 |  | `private void dNO()` |
| 0x37BC5C4 | 0x2EDC4F8 |  | `private void dNt(cd e)` |
| 0x37BC67C | 0x2EDC584 |  | `private IEnumerator dNr(string e, Bootstrap.rQ f)` |
| - | 0x2EDC634 |  | `public void TryLoginGuest()` |
| 0x37BC0CC | 0x2EDC69C |  | `private IEnumerator dNN()` |
| 0x37BC7AC | 0x2EDC730 |  | `public void LoginGuest()` |
| 0x37BC7CC | 0x2EDC798 |  | `public IEnumerator dNq()` |
| 0x37BC860 | 0x2EDC82C |  | `private IEnumerator dNs(LoginResult e)` |
| 0x37BC910 | 0x2EDC8DC |  | `private void dNC(PlayFabError e)` |
| 0x37BCFB4 | 0x2EDCACC |  | `public void RequestMicroPermission()` |
| 0x37BD08C | 0x2EDCB74 |  | `private bool dNZ()` |
| 0x37BD1B8 | 0x2EDCC44 |  | `public void MicroRequestPressedOk()` |
| 0x37BD21C | 0x2EDCC94 |  | `public void MicroRequestPressedLater()` |
| 0x37BD280 | 0x2EDCCE4 |  | `private UniTask dNj()` |
| 0x37BD32C | 0x2EDCE60 |  | `private void dNa()` |
| 0x37BD6C4 | 0x2EDD1F0 |  | `private void dNH(cM e, Hr f, fEd F, rv d, qW c, Hu U, Ce Y, sy W, sr E, qx A)` |
| 0x37BD814 | 0x2EDD340 | 4 | `public void Dispose()` |
| - | 0x2EDD378 |  | `private static bool IsValidNickname(string nickname)` |
| - | - |  | `private static T FindSceneObject<T>()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x37DCA84 Offset: 0x37D8A84 VA: 0x37DCA84` |
| - | - |  | `\|-Bootstrap.FindSceneObject<object>` |
| - | - |  | `*/` |
| - | 0x2EDD3D0 |  | `private IEnumerator ChooseNickname()` |
| - | 0x2EDD464 |  | `private void RefreshProfileUi()` |
| - | 0x2EDD5C0 |  | `private void ShowMainMenu()` |
| 0x37BD848 | 0x2EDD750 |  | `private void Start()` |
| 0x37BD964 | 0x2EDD7DC |  | `public void dNi()` |
| - | 0x2EDD770 |  | `private IEnumerator dNw()` |
| 0x37BD9AC | 0x2EDD824 |  | `public static void HideErrorPanels()` |
| - | 0x2EDD910 |  | `public void Error(string error)` |
| 0x37BD03C | 0x2EDCB2C |  | `public void dNJ()` |
| 0x37BDA84 | 0x2EDD9D4 |  | `private IEnumerator dNX()` |
| 0x37BDB18 | 0x2EDDA68 |  | `public void Exit()` |
| 0x37BDB68 | 0x2EDDAB8 |  | `public void DeleteAccountButtonClicked()` |
| 0x37BDDF8 | 0x2EDDE28 |  | `private static string GoogleText(string ru, string en)` |
| - | 0x2EDDEB4 |  | `private IEnumerator RetrySavedGoogleLogin()` |
| - | 0x2EDBFF8 |  | `private IEnumerator GoogleSiteLogin(bool interactive)` |
| - | 0x2EDDF70 |  | `private void ShowLoginBan(AccountBanNotice notice)` |
| - | 0x2EDDFBC |  | `private static bool SessionRejected(PlayFabError error)` |
| - | 0x2EDE068 |  | `private IEnumerator CompleteSiteLogin(SiteGoogleLogin.Session session, Action<LoginResult> ok, Action<PlayFabError> failed)` |
| - | 0x2EDE12C |  | `public void .ctor()` |
| 0x37BDE80 | 0x2EDE1B0 |  | `private void dNT(bool e, string f)` |
| 0x37BE030 | 0x2EDE34C |  | `private void dNL(string e)` |
| 0x37BE154 | 0x2EDE460 |  | `private void dNo(LoginResult e)` |
| 0x37BDFEC | 0x2EDE308 |  | `private void dNy(string e)` |
| 0x37BE208 | 0x2EDE514 |  | `private void dNz(PlayFabError e)` |
| 0x37BE2C0 | 0x2EDE5CC |  | `private void dNh(RegisterPlayFabUserResult e)` |
| 0x37BE3EC | 0x2EDE6E8 |  | `private void dNB()` |
| 0x37BE4CC | 0x2EDE7C8 |  | `private void dNm(PlayFabError e)` |
| 0x37BE698 | 0x2EDE96C |  | `private void dNR(ExecuteCloudScriptResult e)` |
| 0x37BE80C | 0x2EDEBAC |  | `private void dNb(PlayFabError e)` |
| 0x37BE900 | 0x2EDEE30 |  | `private bool dNl()` |
| - | 0x2EDEE4C |  | `private static bool HasAuthenticatedSession()` |
| - | 0x2EDEC88 |  | `private void ShowLoginPanel()` |

</details>

### public class `ChangeRegionButton` : MonoBehaviour  
`TypeDefIndex 3334`

| offset | field |
|---|---|
| 0x20 | `private Button _button;` |
| 0x28 | `private rD kVz;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37C6F54 | 0x2EE3434 |  | `private void dqz(rD e)` |
| 0x37C6F5C | 0x2EE3438 |  | `private void OnEnable()` |
| 0x37C700C | 0x2EE343C |  | `private void Start()` |
| 0x37C70FC | 0x2EE3440 |  | `private void OnDestroy()` |
| 0x37C71F0 | 0x2EE3444 |  | `private void dqh()` |
| 0x37C72BC | 0x2EE3448 |  | `public void .ctor()` |
| 0x37C72C4 | 0x2EE3450 |  | `private bool dqB()` |

</details>

### public class `ChangeRegionPopup` : MonoBehaviour  
`TypeDefIndex 3335`

| offset | field |
|---|---|
| - | `private const string kVh = "ui.screen.change_region_popup.description";` |
| 0x20 | `private Text _description;` |
| 0x28 | `private Button _okButton;` |
| 0x30 | `private rD kVB;` |
| 0x38 | `private string kVm;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37C78AC | 0x2EE3460 |  | `private void dqm(rD e)` |
| 0x37C78B4 | 0x2EE3464 |  | `private void Start()` |
| 0x37C7944 | 0x2EE3468 |  | `private void OnDestroy()` |
| 0x37C79D4 | 0x2EE346C |  | `public void Show(string regionId, string regionKey)` |
| 0x37C7B4C | 0x2EE3470 |  | `private void dqR()` |
| 0x37C7C14 | 0x2EE3474 |  | `public void .ctor()` |

</details>

### public class `DeleteAccountConfirmationPopup` : MonoBehaviour  
`TypeDefIndex 3339`

| offset | field |
|---|---|
| - | `private Action pendingDelete;` |
| - | `private Coroutine countdown;` |
| - | `private const int kVi = 10;` |
| 0x20 | `private Canvas canvas;` |
| 0x28 | `private Button deleteButton;` |
| 0x30 | `private Button cancelButton;` |
| 0x38 | `private Button closeButton;` |
| 0x40 | `private GameObject deleteButtonText;` |
| 0x48 | `private GameObject loaderGameObject;` |
| 0x50 | `private Text loaderTextGameObject;` |
| 0x58 | `private CancellationTokenSource kVw;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EE347C |  | `private IEnumerator RecoveredCountdown()` |
| - | 0x2EE3510 |  | `private void ConfirmDelete()` |
| - | 0x2EE367C |  | `public void EnsureRecoveredBindings()` |
| 0x37BDBF4 | 0x2EDDC7C |  | `public void Show(Action deleteAction)` |
| 0x37C38F4 | 0x2EE3BD0 |  | `private void OnDestroy()` |
| 0x37C3828 | 0x2EE3C28 |  | `private UniTask dqe(CancellationToken e)` |
| 0x37C3928 | 0x2EE35B0 |  | `private void Hide()` |
| 0x37C3A54 | 0x2EE3C34 |  | `public void .ctor()` |

</details>

### public class `EncryptedFingerprintProvider` : MonoBehaviour  
`TypeDefIndex 3340`

| offset | field |
|---|---|
| 0x20 | `private fLV transport;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37C69C4 | 0x2EE3E88 |  | `private void Awake()` |
| 0x37C6A54 | 0x2EE3E8C |  | `private bool dqi(PubKeyInfo e)` |
| 0x37C6ABC | 0x2EE3E94 |  | `public void .ctor()` |

</details>

### public class `FreeGiftPopupReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3341`

| offset | field |
|---|---|
| 0x20 | `private GameObject popup;` |
| 0x28 | `private Button freeGiftButton;` |

Properties: `public GameObject sRp { get; }`; `public Button sRv { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37CEFC0 | 0x2EE3E9C |  | `public GameObject get_sRp()` |
| 0x37CEFC8 | 0x2EE3EA4 |  | `public Button get_sRv()` |
| 0x37CEFD0 | 0x2EE3EAC |  | `public void .ctor()` |

</details>

### public class `HyperHugIdPanel` : MonoBehaviour  
`TypeDefIndex 3342`

| offset | field |
|---|---|
| 0x20 | `private Text hyperHugIdText;` |
| 0x28 | `private GameObject hyperHugHideIdImage;` |
| 0x30 | `private Button showIdButton;` |
| 0x38 | `private GameObject hideIcon;` |
| 0x40 | `private bool kgB;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D1B0C | 0x2EE3EB4 |  | `private void Awake()` |
| 0x37D1B9C | 0x2EE3EB8 |  | `private void OnDestroy()` |
| 0x37D1C2C | 0x2EE3EBC |  | `private void dsB()` |
| 0x37D1CA8 | 0x2EE3EC0 |  | `private void dsm()` |
| 0x37D1CF4 | 0x2EE3EC4 |  | `private void dsR()` |
| 0x37D1E64 | 0x2EE3EC8 |  | `public void .ctor()` |
| 0x37D1E6C | 0x2EE3ED0 |  | `private void dsb(bool e, string f)` |

</details>

### public class `MissionDataDialogue` : ScriptableObject  
`TypeDefIndex 3343`

| offset | field |
|---|---|
| 0x18 | `public Wp.Phrase task;` |
| 0x20 | `public Wp.Phrase taskDialogue;` |
| 0x28 | `public Wp.Phrase inProgressDialogue;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D1EF8 | 0x2EE3ED4 |  | `public void .ctor()` |

</details>

### public class `NpcDataDialogue` : ScriptableObject  
`TypeDefIndex 3344`

| offset | field |
|---|---|
| 0x18 | `public Wp.Phrase rewardDialogue;` |
| 0x20 | `public Wp.Phrase busyDialogue;` |
| 0x28 | `public Wp.Phrase laterDialogue;` |
| 0x30 | `public Wp.Phrase agreePhrase;` |
| 0x38 | `public Wp.Phrase takePhrase;` |
| 0x40 | `public Wp.Phrase byePhrase;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D2A08 | 0x2EE3EDC |  | `public void .ctor()` |

</details>

### public class `OutlineAnimatedImage` : Image  
`TypeDefIndex 3345`

| offset | field |
|---|---|
| - | `private RectTransform kgf;` |
| - | `private Material kgc;` |
| - | `private static readonly int Width;` |
| - | `private static readonly int Height;` |
| - | `private static readonly int AnimationTime;` |

Properties: `public override Material material { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EE3EE4 |  | `public override Material get_material()` |
| - | 0x2EE3F60 |  | `public override void set_material(Material value)` |
| - | 0x2EE41D8 |  | `protected override void Awake()` |
| - | 0x2EE4208 |  | `protected override void OnEnable()` |
| - | 0x2EE407C |  | `private void CreateMaterial()` |
| - | 0x2EE45A4 |  | `protected override void OnDisable()` |
| - | 0x2EE4690 |  | `private void Update()` |
| - | 0x2EE4248 |  | `private void dsU()` |
| - | 0x2EE4694 |  | `public void .ctor()` |
| - | 0x2EE46EC |  | `private static void .cctor()` |

</details>

### public class `QueueWindowController` : MonoBehaviour, IDisposable  
`TypeDefIndex 3348`

| offset | field |
|---|---|
| 0x20 | `private Text serverName;` |
| 0x28 | `private Text playersCount;` |
| 0x30 | `private ServerBrowserTags serverTags;` |
| 0x38 | `private Text mapName;` |
| 0x40 | `private Button cancelButton;` |
| 0x48 | `private Button skipQueueButton;` |
| 0x50 | `private Text connectionStateTextAhead;` |
| 0x58 | `private Text connectionStateTextBehind;` |
| 0x60 | `private Text coinsCount;` |
| 0x68 | `private Text passText;` |
| 0x70 | `private bool kgA;` |
| - | `private UnityAction cancelAction;` |
| - | `private UnityAction skipAction;` |

Properties: `public bool sRg { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37CC0D4 | 0x2EE47B4 |  | `public bool get_sRg()` |
| 0x37CC0DC | 0x2EE47BC |  | `public void dsk(YV e, Action f, Action F)` |
| 0x37CCA94 | 0x2EE4AEC | 4 | `public void Dispose()` |
| 0x37CCA9C | 0x2EE5684 |  | `public void dsO(int e, int f, int F, int d, int c, bool U)` |
| - | 0x2EE59B8 |  | `public void SetQueuePending(bool pending, string message)` |
| 0x37CCD18 | 0x2EE5ACC |  | `public void .ctor()` |

</details>

### public class `RateUsInstaller` : fWl  
`TypeDefIndex 3349`

| offset | field |
|---|---|
| 0x28 | `private FreeGiftPopupReferenceHolder freeGiftPopupReferenceHolder;` |
| 0x30 | `private RateUsPopupReferenceHolder rateUsPopupReferenceHolder;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37CF9AC | 0x2EE5B70 | 8 | `public override void FSz()` |
| 0x37CFB08 | 0x2EE5B74 |  | `public void .ctor()` |

</details>

### public class `RateUsPopupReferenceHolder` : MonoBehaviour  
`TypeDefIndex 3350`

| offset | field |
|---|---|
| 0x20 | `private GameObject popup;` |
| 0x28 | `private Button rateUsButton;` |
| 0x30 | `private Button cancelButton;` |

Properties: `public GameObject sRS { get; }`; `public Button sRI { get; }`; `public Button sRM { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D0464 | 0x2EE5B7C |  | `public GameObject get_sRS()` |
| 0x37D046C | 0x2EE5B84 |  | `public Button get_sRI()` |
| 0x37D0474 | 0x2EE5B8C |  | `public Button get_sRM()` |
| 0x37D047C | 0x2EE5B94 |  | `public void .ctor()` |

</details>

### public class `ScrollableLootOpener` : MonoBehaviour  
`TypeDefIndex 3351`

| offset | field |
|---|---|
| 0x20 | `private InfinityItemContainer m_ItemContainer;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D3628 | 0x2EE5B9C |  | `private void Start()` |
| 0x37D36DC | 0x2EE5BA0 |  | `private bool dsS(ItemHolder[] e)` |
| 0x37D37A0 | 0x2EE5BA8 |  | `public void .ctor()` |

</details>

### public class `SelectRegionPopup` : MonoBehaviour  
`TypeDefIndex 3352`

| offset | field |
|---|---|
| 0x20 | `private Button _confirm;` |
| 0x28 | `private Transform _regionItemsParent;` |
| 0x30 | `private RegionItem _regionItemPrefab;` |
| 0x38 | `private ChangeRegionPopup _changeRegionPopup;` |
| 0x40 | `private readonly List<RegionItem> kVI;` |
| 0x48 | `private rD kVM;` |
| 0x50 | `private string kge;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37CAC64 | 0x2EE5BB0 |  | `private void dse(rD e)` |
| 0x37CAC6C | 0x2EE5BB4 |  | `private void Start()` |
| 0x37CACFC | 0x2EE5BB8 |  | `private void OnDestroy()` |
| 0x37CAD8C | 0x2EE5BBC |  | `private void OnEnable()` |
| 0x37CB6D8 | 0x2EE5BC0 |  | `private void dsf(string e)` |
| 0x37CB848 | 0x2EE5BC4 |  | `private void dsF()` |
| 0x37CBA30 | 0x2EE5BC8 |  | `public void .ctor()` |
| 0x37CBABC | 0x2EE5BD0 |  | `private int dsd(Region e)` |
| 0x37CBBE8 | 0x2EE5BD8 |  | `private bool dsc(Region e)` |

</details>

### public class `ServerBrowserTags` : MonoBehaviour  
`TypeDefIndex 3354`

| offset | field |
|---|---|
| - | `private bool useWinterPalette;` |
| - | `private const string kgn = "PVP";` |
| - | `private const string kgV = "PVE";` |
| - | `private const string kgg = "sub.premium.lable";` |
| 0x20 | `private Image pvpTagImage;` |
| 0x28 | `private Text pvpTagText;` |
| 0x30 | `private Color pvpColor;` |
| 0x40 | `private Color pveColor;` |
| 0x50 | `private Image wipeTagImage;` |
| 0x58 | `private Text wipeTagText;` |
| 0x60 | `private Text multiplierTagText;` |
| 0x68 | `private Image multiplierTagImage;` |
| 0x70 | `private Image premiumTagImage;` |
| 0x78 | `private Text premiumTagText;` |
| 0x80 | `private Text platformTagText;` |
| 0x88 | `private Image platformTagImage;` |
| 0x90 | `private ServerBrowserItem.WipeTypeConfig[] wypeTypeConfigs;` |
| 0x98 | `private GameObject[] tags;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EE5BE0 |  | `public static Color MultiplierColor(int multiplier)` |
| - | 0x2EE5C94 |  | `private static void SetWidth(Graphic graphic, float width)` |
| 0x37CC3A8 | 0x2EE4BFC |  | `public void dsM(YV e)` |
| 0x37D37B0 | 0x2EE5CD8 |  | `public void .ctor()` |

</details>

### public class `ServerPlayersCount` : MonoBehaviour  
`TypeDefIndex 3355`

| offset | field |
|---|---|
| 0x20 | `private Color originalColor;` |
| 0x30 | `private Color overheadColor;` |
| 0x40 | `private GameObject overheadFirsIndicator;` |
| 0x48 | `private GameObject overheadSecondIndicator;` |
| 0x50 | `private Text playerCount;` |
| 0x58 | `private int firstOverheadLimit;` |
| 0x5C | `private int secondOverheadLimit;` |
| 0x60 | `private GameObject queueContent;` |
| 0x68 | `private Text queueSize;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D570C | 0x2EE5D10 |  | `public void dCZ(YV e)` |
| 0x37D58F4 | 0x2EE5FBC |  | `public void .ctor()` |

</details>

### public class `ServicesManager` : MonoBehaviour  
`TypeDefIndex 3357`

| offset | field |
|---|---|
| 0x20 | `private dQ appleAuthManagerProxy;` |
| 0x28 | `public Nq buttonGooglePlay;` |
| 0x30 | `public Nq buttonGameCenter;` |
| 0x38 | `public Nq buttonAppleSignIn;` |
| 0x40 | `public GameObject loadingUI;` |
| 0x48 | `private cd kgI;` |
| 0x4C | `private bool kgM;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D5A2C | 0x2EE5FC4 |  | `private void Awake()` |
| 0x37D5A58 | 0x2EE5FC8 |  | `public void ConnectPlayServices(bool forceLink)` |
| 0x37D5C78 | 0x2EE5FCC |  | `private void dCa(LinkGoogleAccountResult e)` |
| 0x37D5D84 | 0x2EE5FD0 |  | `public void ConnectGameCenter()` |
| 0x37D5D88 | 0x2EE5FD4 |  | `public void ConnectAppleSignIn(AppleSignInConnectOptions appleSignInConnectOptions)` |
| 0x37D5E30 | 0x2EE5FD8 |  | `public void ConnectAppleSignIn(bool forceLink)` |
| 0x37D5EF4 | 0x2EE5FDC |  | `private void dCQ(EmptyResult e)` |
| 0x37D5F34 | 0x2EE5FE0 |  | `private void dCH(LinkGameCenterAccountResult e)` |
| 0x37D5F74 | 0x2EE5FE4 |  | `private void dCi(PlayFabError e)` |
| 0x37D5CB8 | 0x2EE5FE8 |  | `private void dCw(cd e)` |
| 0x37D66C0 | 0x2EE5FEC |  | `public void Error(string error)` |
| 0x37D67B8 | 0x2EE5FF0 |  | `public void .ctor()` |
| 0x37D67C0 | 0x2EE5FF8 |  | `private void dCJ(string e, string f, PlayFabError F)` |
| 0x37D680C | 0x2EE5FFC |  | `private void dCX(PlayFabError e)` |
| 0x37D6810 | 0x2EE6000 |  | `private void dCT()` |

</details>

### public class `SettingsManager` : MonoBehaviour  
`TypeDefIndex 3366`

| offset | field |
|---|---|
| - | `private const string kpY = "OutlineFeature";` |
| 0x20 | `private UniversalRendererData[] rendererDatas;` |
| 0x28 | `private GameObject loading;` |
| 0x30 | `private Canvas graphicsNotSupportedPopupCanvas;` |
| 0x38 | `private GameObject readjustButtonRoot;` |
| 0x40 | `public Toggle compassToggle;` |
| 0x48 | `public Toggle fpsCounterToggle;` |
| 0x50 | `public Toggle playersIdToggle;` |
| 0x58 | `public Yv sensitivitySlider;` |
| 0x60 | `public Yv accelerationSlider;` |
| 0x68 | `public Yv aimSensitivitySlider;` |
| 0x70 | `public Yv graphicsQualitySlider;` |
| 0x78 | `public Toggle shadowsToggle;` |
| 0x80 | `public Toggle[] postProcessingToggles;` |
| 0x88 | `public Yv screenResolutionSlider;` |
| 0x90 | `public Toggle antiAliasingToggle;` |
| 0x98 | `public Yv drawDistanceSlider;` |
| 0xA0 | `public Toggle grassToggle;` |
| 0xA8 | `public Toggle outlineToggle;` |
| 0xB0 | `public Toggle floatingJoystickToggle;` |
| 0xB8 | `public Toggle aimCameraRotationToggle;` |
| 0xC0 | `public Toggle attackCameraRotationToggle;` |
| 0xC8 | `public Toggle smoothCameraToggle;` |
| - | `public Toggle motionBlurToggle;` |
| - | `public Toggle gyroscopeToggle;` |
| - | `public GyroscopeUnsupportedPopup gyroscopeUnsupportedPopup;` |
| - | `public Yv gyroscopeSensitivitySlider;` |
| 0xD0 | `public Yv masterVolumeSlider;` |
| 0xD8 | `public Yv ambienceSoundsSlider;` |
| 0xE0 | `public GameObject microPermission;` |
| 0xE8 | `public GameObject microAllowed;` |
| 0xF0 | `public Button changeNicknameButton;` |
| 0xF8 | `public Text nicknameLabel;` |
| 0x100 | `public AboutYou aboutYou;` |
| 0x108 | `private bool kpA;` |
| 0x110 | `private Hu kpu;` |
| 0x118 | `private jI kpk;` |
| 0x120 | `private sy kpO;` |
| - | `private static float recoveredMasterVolume;` |
| - | `private sB nicknameController;` |
| - | `private static Camera currentDeathCamera;` |
| - | `private static readonly int[] FrameSteps;` |
| - | `private Toggle unlockFpsToggle;` |
| - | `private Yv targetFrameRateSlider;` |
| - | `private UiSettingsSlider targetFrameRateMarks;` |
| - | `private GameObject targetFrameRateRow;` |

Properties: `public static float kpW { get; set; }`; `public static bool kpE { get; set; }`; `public static int sbU { get; }`; `public static bool SupportsGyroscope { get; }`

<details><summary>methods (85)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D7268 | 0x2EE6020 |  | `public static float get_kpW()` |
| 0x37D72C0 | 0x2EE6078 |  | `private static void set_kpW(float value)` |
| - | 0x2EE60DC |  | `public static bool get_kpE()` |
| - | 0x2EE6130 |  | `private static void set_kpE(bool value)` |
| - | 0x2EE617C |  | `public static int get_sbU()` |
| 0x37D73E4 | 0x2EE61C4 |  | `private void Start()` |
| 0x37D785C | 0x2EE7A68 |  | `private void OnDestroy()` |
| - | 0x2EE7B50 |  | `private IEnumerator dCP()` |
| 0x37D78A8 | 0x2EE7BE4 |  | `private void dCD()` |
| 0x37D83D4 | 0x2EE7BFC |  | `public void ForceReAdjustGraphics()` |
| 0x37D7BD4 | 0x2EE7268 |  | `public void dCn()` |
| 0x37D8780 | 0x2EE9280 |  | `public void ToggleCompass(bool toggle)` |
| 0x37D87F4 | 0x2EE9310 |  | `public void ToggleFpsCounter(bool toggle)` |
| 0x37D8868 | 0x2EE9370 |  | `public void ToggleFloatingJoystick(bool toggle)` |
| 0x37D88DC | 0x2EE93D0 |  | `public void ToggleAimCameraRotation(bool toggle)` |
| 0x37D8950 | 0x2EE9430 |  | `public void ToggleAttackCameraRotation(bool toggle)` |
| 0x37D89C4 | 0x2EE9490 |  | `public void ToggleSmoothCamera(bool toggle)` |
| 0x37D8A38 | 0x2EE94F0 |  | `public void TogglePlayersID(bool toggle)` |
| 0x37D8B10 | 0x2EE9550 |  | `public void SetSensitivityValue()` |
| 0x37D8BC8 | 0x2EE9640 |  | `public void SetAimSensitivityValue()` |
| 0x37D8C80 | 0x2EE9730 |  | `public void SetAccelerationValue()` |
| 0x37D8D38 | 0x2EE9820 |  | `public void SetDrawDistanceValue()` |
| 0x37D8E24 | 0x2EE9934 |  | `public void SetGraphicsQualityValue()` |
| 0x37D91A0 | 0x2EE9A84 |  | `public void SetScreenResolutionValue()` |
| 0x37D8460 | 0x2EE9BEC |  | `private void dCV(int e)` |
| 0x37D9294 | 0x2EE9CF8 |  | `public void ToggleAntiAliasing(bool toggle)` |
| 0x37D9308 | 0x2EE9D58 |  | `public void ToggleGrass(bool toggle)` |
| 0x37D937C | 0x2EE9DB8 |  | `public void ToggleShadows(bool toggle)` |
| 0x37D93F0 | 0x2EE9E18 |  | `public void SetPostProcessingValue(int value)` |
| 0x37D948C | 0x2EE9F14 |  | `public void ToggleOutline(bool toggle)` |
| 0x37D9510 | 0x2EE9F74 |  | `public void SetMasterVolumeValue()` |
| 0x37D9610 | 0x2EEA09C |  | `public void SetAmbienceSoundsValue()` |
| 0x37D96F4 | 0x2EEA1C4 |  | `public void RequestMicroPermission()` |
| 0x37D8570 | 0x2EEA2BC |  | `private void dCg(bool e)` |
| 0x37D77E4 | 0x2EE7964 |  | `private void CheckMicroAccess()` |
| 0x37D97A0 | 0x2EE7B28 |  | `public void dCp()` |
| 0x37D97C8 | 0x2EEA4FC |  | `public void .ctor()` |
| 0x37D981C | 0x2EEA504 |  | `private void dCv()` |
| 0x37D9914 | 0x2EEA658 |  | `private void dCS(string e)` |
| 0x37D9930 | 0x2EEA6EC |  | `private bool dCI()` |
| 0x37D83F4 | 0x2EEA6F4 |  | `private IEnumerator dCM()` |
| 0x37D9974 | 0x2EEA788 |  | `private bool dZe()` |
| - | 0x2EE92E0 |  | `private void Changed()` |
| - | 0x2EEA790 |  | `private void OnApplicationPause(bool paused)` |
| - | 0x2EEA7BC |  | `private void OnDisable()` |
| - | 0x2EEA7E4 |  | `private void OnApplicationQuit()` |
| - | 0x2EEA80C |  | `private void OnEnable()` |
| - | 0x2EEA93C |  | `private void OnSettingsSceneLoaded(Scene scene, LoadSceneMode mode)` |
| - | 0x2EEA95C |  | `private IEnumerator ApplyAfterSceneLoad()` |
| - | 0x2EEA250 |  | `private IEnumerator CheckPermissionNextFrame()` |
| - | 0x2EE7F3C |  | `private static void SetToggle(Toggle toggle, string key, int fallback)` |
| - | 0x2EE7FE4 |  | `private static void SetSlider(Yv view, float value, string format)` |
| - | 0x2EE62C0 |  | `private void InitializeDefaults()` |
| - | 0x2EEAA18 |  | `private void Wire(Toggle t, UnityAction<bool> action)` |
| - | 0x2EEAB84 |  | `private void Wire(Yv t, UnityAction action)` |
| - | 0x2EE696C |  | `private void WireControls()` |
| - | 0x2EE8924 |  | `public void ApplySettings()` |
| - | 0x2EEB9A0 |  | `public void ToggleMotionBlur(bool value)` |
| - | 0x2EEBA00 |  | `public static bool get_SupportsGyroscope()` |
| - | 0x2EEBA50 |  | `public void ToggleGyroscope(bool value)` |
| - | 0x2EEBB50 |  | `public void SetGyroscopeSensitivity()` |
| - | 0x2EE7C14 |  | `public void RefreshMotionControls()` |
| - | 0x2EEADCC |  | `private void UpdateGraphicsVisibility()` |
| - | 0x2EEB3D0 |  | `public static void RefreshCameraPostProcessing(Camera deathCamera)` |
| - | 0x2EE9BCC |  | `public static float ResolutionScale(int setting)` |
| - | 0x2EEB08C |  | `public static void ApplyRenderingPreferences()` |
| - | 0x2EEB8CC |  | `public static void ApplyFrameRate()` |
| - | 0x2EEBC10 |  | `public void ToggleUnlockFps(bool toggle)` |
| - | 0x2EEBC78 |  | `public void SetTargetFrameRateValue()` |
| - | 0x2EE82B8 |  | `private void BindFrameRate()` |
| - | 0x2EE87B8 |  | `private void RefreshFrameRateRow()` |
| - | 0x2EE8710 |  | `private static string FrameLabel(int rate)` |
| - | - |  | `private static void DisablePersistent<T>(UnityEvent<T> evt, string method)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38CB054 Offset: 0x38C7054 VA: 0x38CB054` |
| - | - |  | `\|-SettingsManager.DisablePersistent<float>` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38CB0D4 Offset: 0x38C70D4 VA: 0x38CB0D4` |
| - | - |  | `\|-SettingsManager.DisablePersistent<__Il2CppFullySharedGenericType>` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x38CAFD4 Offset: 0x38C6FD4 VA: 0x38CAFD4` |
| - | - |  | `\|-SettingsManager.DisablePersistent<bool>` |
| - | - |  | `*/` |
| - | 0x2EEC1B4 |  | `private static void .cctor()` |

</details>

### public class `SkinInfo` : MonoBehaviour  
`TypeDefIndex 3367`

| offset | field |
|---|---|
| 0x20 | `private Renderer[] renderers;` |

Properties: `public Renderer[] sbY { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D9D8C | 0x2EEC73C |  | `public Renderer[] get_sbY()` |
| 0x37D9D94 | 0x2EEC744 |  | `public void .ctor()` |

</details>

### public class `SnowballVfx` : MonoBehaviour  
`TypeDefIndex 3368`

| offset | field |
|---|---|
| 0x20 | `private ParticleSystem particleSystem;` |
| 0x28 | `private GameObject visual;` |

Properties: `public float sbW { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37D9D9C | 0x2EEC74C |  | `public float get_sbW()` |
| 0x37D9DCC | 0x2EEC754 |  | `public void dZd()` |
| 0x37D9E00 | 0x2EEC758 |  | `public void dZc()` |
| 0x37D9E34 | 0x2EEC75C |  | `public void .ctor()` |

</details>

### public class `UiSettingsSlider` : MonoBehaviour  
`TypeDefIndex 3372`

| offset | field |
|---|---|
| 0x20 | `private Color unselectColor;` |
| 0x30 | `private Color selectColor;` |
| 0x40 | `private Image imageToChange;` |
| 0x48 | `private int middlePoint;` |
| - | `private bool compactMenuStyle;` |
| - | `private Slider slider;` |
| - | `private float shown;` |
| - | `private List<Image> ticks;` |
| - | `private static readonly Color32 SegmentTrack;` |
| - | `private static readonly Color32 SegmentOn;` |
| - | `private static readonly Color32 SegmentOnText;` |
| - | `private static readonly Color32 SegmentOffText;` |
| - | `private List<Text> optionLabels;` |
| - | `private List<Image> segments;` |
| - | `private List<Text> captions;` |
| - | `private List<Image> borderMarks;` |

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2EEC764 |  | `private void OnEnable()` |
| - | 0x2EEC904 |  | `private void LateUpdate()` |
| - | 0x2EEC7C4 |  | `private void Refresh()` |
| 0x37D0484 | 0x2EECF8C |  | `public void OnChangeSlider(float value)` |
| - | 0x2EEDB84 |  | `private bool EnsureSegments()` |
| - | 0x2EEC908 |  | `private void RefreshSegments()` |
| - | 0x2EEBF48 |  | `public int RateAt(float value)` |
| - | 0x2EE8618 |  | `public int IndexOfRate(int rate)` |
| - | 0x2EED3E4 |  | `private void EnsureTicks()` |
| - | 0x2EED3C8 |  | `private void AlignOtherMarks()` |
| - | 0x2EEEC94 |  | `private void AlignOtherMarksList()` |
| - | 0x2EEDB7C |  | `private void AlignRateMarks()` |
| - | 0x2EEF320 |  | `private void AlignMarkList(List<Image> marks)` |
| - | 0x2EEF2A0 |  | `private static bool IsRateMark(string name)` |
| - | 0x2EEF218 |  | `private static int RateOf(string name)` |
| - | 0x2EEFA0C |  | `private static float MarkX(RectTransform mark, float width)` |
| - | 0x2EEFA50 |  | `private static void Paint(Graphic mark, Color color)` |
| - | 0x2EECD38 |  | `private void LocalizeMax()` |
| 0x37D04D8 | 0x2EEFB90 |  | `public void .ctor()` |
| - | 0x2EEFBA0 |  | `private static void .cctor()` |

</details>

### public class `UserMessageWindow` : MonoBehaviour  
`TypeDefIndex 3375`

| offset | field |
|---|---|
| 0x20 | `private GameObject messageWindow;` |
| 0x28 | `private Text messageText;` |
| 0x30 | `private CanvasGroup canvasGroup;` |
| 0x38 | `private readonly Queue<string> kpH;` |
| - | `private CancellationTokenSource kpr;` |
| 0x40 | `private bool kpi;` |
| 0x48 | `private CancellationTokenSource kpw;` |
| - | `private static UserMessageWindow <kpQ>k__BackingField;` |

Properties: `public static UserMessageWindow kpQ { get; set; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F06C7C |  | `public static UserMessageWindow get_kpQ()` |
| - | 0x2F06CC4 |  | `private static void set_kpQ(UserMessageWindow value)` |
| 0x37DBBBC | 0x2F06D1C |  | `private void Awake()` |
| 0x37DBC60 | 0x2F06DC0 |  | `private void OnDestroy()` |
| 0x37C9CB4 | 0x2F06DF8 |  | `public void Show(string message)` |
| 0x37DBC94 | 0x2F06ED8 |  | `private void Update()` |
| 0x37DBD38 | 0x2F06F94 |  | `private IEnumerator dZN(string e, CancellationToken f)` |
| 0x37DBE18 | 0x2F07058 |  | `public void .ctor()` |

</details>

### public class `WeaponBowArrow` : WeaponBase  
`TypeDefIndex 3376`

| offset | field |
|---|---|
| 0x40 | `public GameObject arrow;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37DC8D4 | 0x2F073D8 | 4 | `public override void Reload(bool loaded)` |
| 0x37DC968 | 0x2F073DC | 5 | `public override void FJp()` |
| 0x37DC9EC | 0x2F073E0 | 6 | `public override void FJv(jj e)` |
| 0x37DC9F4 | 0x2F073E4 |  | `private void OnDisable()` |
| 0x37DCA78 | 0x2F073E8 |  | `public void .ctor()` |

</details>
