# namespace `HyperHug.Games.BR24.Features.UiSystem.Screens.Missions.Scripts.Views`  (4 types)

### public class `MissionPanelView` : MonoBehaviour  
`TypeDefIndex 3738`

| offset | field |
|---|---|
| 0x28 | `private SmallRewardView _rewardViewPrefab;` |
| 0x30 | `private RectTransform _rewardsContent;` |
| 0x38 | `private TextMeshProUGUI _descriptionText;` |
| 0x40 | `private TextMeshProUGUI _progressText;` |
| 0x48 | `private TextMeshProUGUI _progressTextBig;` |
| 0x50 | `private TextMeshProUGUI _claimedText;` |
| 0x58 | `private RectTransform _claimedPanel;` |
| 0x60 | `private RectTransform _claimedPanelBg;` |
| 0x68 | `private GameObject background;` |
| 0x70 | `private GameObject premiumLockPanel;` |
| 0x78 | `private Button buyPremiumButton;` |
| 0x80 | `private CanvasGroup _animationRoot;` |
| 0x88 | `private RectTransform _animationRootRectTransform;` |
| 0x90 | `private Sprite _activeClaimSprite;` |
| 0x98 | `private Sprite _inactiveClaimSprite;` |
| 0xA0 | `private rA _claimButton;` |
| 0xA8 | `private ConfigMission kxL;` |
| 0xB0 | `private Mission kxo;` |
| 0xB8 | `private qU kxy;` |
| 0xC0 | `private fEd kxz;` |
| 0xC8 | `private Hn kxh;` |
| 0xD0 | `private rU kxB;` |
| - | `private const float kxm = 0.2;` |

<details><summary>methods (21)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A1D30 | 0x2F6F390 |  | `public void add_kxT(Action value)` |
| 0x37A1DCC | 0x2F6F394 |  | `public void remove_kxT(Action value)` |
| 0x37A1ECC | 0x2F6F398 |  | `public void add_kxR(Action value)` |
| 0x37A1F68 | 0x2F6F39C |  | `public void remove_kxR(Action value)` |
| 0x37A1E68 | 0x2F6F3A0 |  | `public void dWm(qU e, fEd f, Hn F, rU d)` |
| 0x37A2004 | 0x2F6F400 |  | `public void dWl(ConfigMission e, Mission f)` |
| 0x37A25B4 | 0x2F6FFD4 |  | `public void Show(float animationDelay = 0)` |
| 0x37A266C | 0x2F7009C |  | `public void Hide(float animationDelay = 0)` |
| 0x37A2040 | 0x2F6F438 |  | `private void dWx()` |
| 0x37A27EC | 0x2F700C0 |  | `private void dWK(string e)` |
| 0x37A2904 | 0x2F700C4 |  | `private void dWG(string e)` |
| 0x37A2B0C | 0x2F700C8 |  | `private void dWP()` |
| 0x37A2A1C | 0x2F700CC |  | `private void dWD()` |
| 0x37A2CA0 | 0x2F700D0 |  | `private void OnEnable()` |
| 0x37A2D94 | 0x2F700D4 |  | `private void dWn()` |
| 0x37A2DB0 | 0x2F700D8 |  | `private void dWV()` |
| 0x37A2DCC | 0x2F700DC |  | `private void OnDisable()` |
| 0x37A2DE8 | 0x2F700E0 |  | `private void dWg()` |
| 0x37A308C | 0x2F700E4 |  | `public void .ctor()` |
| 0x37A3094 | 0x2F700EC |  | `private void dWp()` |
| - | 0x2F700F0 |  | `private void <dWx>b__33_0()` |

</details>

### public class `MissionsScreenButton` : rA  
`TypeDefIndex 3739`

| offset | field |
|---|---|
| 0x28 | `private bool _isRevertedColors;` |
| 0x30 | `private Image _lockImage;` |
| 0x38 | `private Image _leftImagePanel;` |
| 0x40 | `private TextMeshProUGUI _buttonText;` |
| 0x48 | `private Image _bgImage;` |
| 0x50 | `private Color _inactiveColor;` |
| 0x60 | `private Color _activeColor;` |
| 0x70 | `private Sprite _leftActivePanelSprite;` |
| 0x78 | `private Sprite _leftDeactivePanelSprite;` |
| 0x80 | `private GameObject notifycation;` |
| 0x88 | `private readonly Color kxb;` |
| 0x98 | `private readonly Color kxl;` |
| 0xA8 | `private readonly Color kxx;` |
| 0xB8 | `private readonly Color kxK;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379D7BC | 0x2F701E4 |  | `public void dWv(string e, bool f, bool F = false)` |
| 0x379F75C | 0x2F6E964 |  | `public void SetActive(bool isActive)` |
| 0x379D964 | 0x2F70364 |  | `public void dWS(bool e)` |
| 0x37A3178 | 0x2F703F8 |  | `public void .ctor()` |

</details>

### public class `MissionsView` : MonoBehaviour  
`TypeDefIndex 3742`

| offset | field |
|---|---|
| 0x30 | `private MissionPanelView _missionViewPrefab;` |
| 0x38 | `private RectTransform _missionsContent;` |
| - | `private const float kxv = 0.01;` |
| - | `private const float kxS = 0.075;` |
| 0x40 | `private readonly List<MissionPanelView> kxI;` |
| - | `private readonly List<string> kxIds;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379D684 | 0x2F70400 |  | `public void add_kxg(Action value)` |
| 0x37A319C | 0x2F70404 |  | `public void remove_kxg(Action value)` |
| 0x379D720 | 0x2F70408 |  | `public void add_kxp(Action value)` |
| 0x37A3238 | 0x2F7040C |  | `public void remove_kxp(Action value)` |
| 0x37A32D4 | 0x2F70410 |  | `private void Awake()` |
| 0x379EC68 | 0x2F6DCC8 |  | `public void dEu(List<ConfigMission> e, List<Mission> f, fEd F, TextMeshProUGUI d)` |
| 0x37A3360 | 0x2F70414 |  | `private void OnDisable()` |
| 0x37A32D8 | 0x2F70418 |  | `private void dEk()` |
| 0x37A3364 | 0x2F7041C |  | `public void .ctor()` |

</details>

### public class `MissionsWeekButtonsView` : MonoBehaviour  
`TypeDefIndex 3748`

| offset | field |
|---|---|
| 0x20 | `private MissionsScreenButton _weeklyButton;` |
| 0x28 | `private Image _arrowImage;` |
| 0x30 | `private MissionsScreenButton _weekButtonPrefab;` |
| 0x38 | `private RectTransform _weekButtonsContent;` |
| 0x40 | `private CanvasGroup _weekButtonsCanvasGroup;` |
| - | `private const float kKU = 0.33;` |
| 0x5C | `private readonly Color kKY;` |
| 0x6C | `private readonly Color kKW;` |
| 0x7C | `private int kKE;` |
| 0x80 | `private readonly List<MissionsScreenButton> kKA;` |
| 0x88 | `private tJ kKu;` |
| - | `private bool <kKc>k__BackingField;` |
| - | `private Action<int> kKd;` |
| - | `private readonly List<int> weekIds;` |

Properties: `public bool kKc { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F70538 |  | `public bool get_kKc()` |
| - | 0x2F70540 |  | `private void set_kKc(bool value)` |
| 0x379E7B8 | 0x2F7054C |  | `public void add_kKF(Action value)` |
| 0x379EB78 | 0x2F70550 |  | `public void remove_kKF(Action value)` |
| - | 0x2F6B460 |  | `public void add_kKd(Action<int> value)` |
| - | 0x2F6B3B0 |  | `public void remove_kKd(Action<int> value)` |
| 0x379D9F8 | 0x2F6B510 |  | `public void dEZ(tJ e, bool f)` |
| 0x37A3A7C | 0x2F7066C |  | `private void dEj(int e, MissionsScreenButton f)` |
| 0x379FB68 | 0x2F6EA7C |  | `public void dEa(int e)` |
| 0x379E728 | 0x2F70670 |  | `public void dEQ()` |
| 0x379EB5C | 0x2F70674 |  | `public void dEH()` |
| 0x379F870 | 0x2F70678 |  | `public void SetActive(bool isActive)` |
| 0x37A0074 | 0x2F70554 |  | `public void dEi(bool e)` |
| 0x379DDE8 | 0x2F706A0 |  | `public void dEw(bool e)` |
| 0x37A3A98 | 0x2F706A4 |  | `public void .ctor()` |
| 0x37A3B34 | 0x2F70780 |  | `private void dEJ()` |
| - | 0x2F70784 |  | `private void <dEZ>b__22_0()` |

</details>
