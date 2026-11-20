# namespace `HyperHug.Games.BR24.Features.UiSystem.Screens.BattlePass.Scripts.Views`  (7 types)

### public class `BattlePassBaseRewardView` : MonoBehaviour  
`TypeDefIndex 3750`

| offset | field |
|---|---|
| 0x20 | `private Image _rewardFrameBackground;` |
| 0x28 | `private List<Image> _rareFrameBackgrounds;` |
| 0x30 | `private Image _rewardImage;` |
| 0x38 | `private Sprite _rewardDefaultSprite;` |
| 0x40 | `private Sprite _rewardRaritySprite;` |
| 0x48 | `private Sprite _selectedSprite;` |
| 0x50 | `private List<Behaviour> onSelectEnable;` |
| 0x58 | `private List<GameObject> onSelectSetActive;` |
| 0x60 | `private RectTransform _receivedTextPanel;` |
| 0x68 | `private TextMeshProUGUI _receivedText;` |
| 0x70 | `private TextMeshProUGUI _countText;` |
| 0x78 | `private Image _lockedImage;` |
| 0x80 | `private RectTransform _timerPanel;` |
| 0x88 | `private TextMeshProUGUI _timeLeftText;` |
| 0x90 | `private Button _mainButton;` |
| 0x98 | `private GameObject canClaimOutline;` |
| 0xA0 | `private GameObject rareParentObject;` |
| 0xA8 | `private ParticleSystem _uncommonParticleSystem;` |
| 0xB0 | `private ParticleSystem _rareParticleSystem;` |
| 0xB8 | `private ParticleSystem _epicParticleSystem;` |
| 0xC0 | `private ParticleSystem _legendaryParticleSystem;` |
| 0xC8 | `private bool kKO;` |
| 0xC9 | `private bool kKt;` |
| 0xCA | `private bool kKr;` |
| 0xD0 | `private AssetReference kKN;` |
| 0xE0 | `public Action<BattlePassBaseRewardView> RewardClaimedPressed;` |
| 0xE8 | `public Action<tg, BattlePassBaseRewardView> PreviewRequested;` |
| 0xF0 | `private qU kKs;` |
| - | `private bool <kKq>k__BackingField;` |
| - | `private tg <kKC>k__BackingField;` |

Properties: `public bool kKq { get; set; }`; `public bool smD { get; }`; `public tg kKC { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F709D4 |  | `public bool get_kKq()` |
| - | 0x2F709DC |  | `private void set_kKq(bool value)` |
| 0x37A3C0C | 0x2F709E8 |  | `public bool get_smD()` |
| - | 0x2F709F0 |  | `public tg get_kKC()` |
| - | 0x2F709F8 |  | `private void set_kKC(tg value)` |
| 0x37A3C3C | 0x2F70A00 |  | `public void dEz(qU e)` |
| 0x37A3EC4 | 0x2F70A08 |  | `public void dEh(tg e, bool f)` |
| 0x37A45B0 | 0x2F70FC4 |  | `private void dEB(bool e)` |
| 0x37A4824 | 0x2F71178 |  | `private void dEm(Color e)` |
| 0x37A470C | 0x2F7160C |  | `private void dER(AssetReference e)` |
| 0x37A44D8 | 0x2F71610 |  | `private UniTask<bool> dEb()` |
| 0x37A49A8 | 0x2F7161C |  | `private void OnDestroy()` |
| 0x37A4A30 | 0x2F71620 |  | `public void dEl(bool e, bool f, bool F = true)` |
| 0x37A4ACC | 0x2F71778 |  | `public void Select()` |
| 0x37A3C58 | 0x2F71340 |  | `public void dEx()` |
| 0x37A4D38 | 0x2F71A44 |  | `public void dEK()` |
| 0x37A4D98 | 0x2F71AA4 |  | `public void .ctor()` |

</details>

### public class `BattlePassLevelView` : MonoBehaviour  
`TypeDefIndex 3755`

| offset | field |
|---|---|
| 0x20 | `public Canvas canvas;` |
| 0x28 | `public RectTransform _mainRectTransform;` |
| 0x30 | `public RectTransform RectTransform;` |
| 0x38 | `protected TextMeshProUGUI _levelText;` |
| 0x40 | `protected BattlePassBaseRewardView _battlePassBaseRewardPrefab;` |
| 0x48 | `protected RectTransform _freeRewardsContentPanel;` |
| 0x50 | `protected RectTransform _paidRewardsContentPanel;` |
| 0x58 | `protected Image _levelBackground;` |
| 0x60 | `protected GameObject _levelPanelBackground;` |
| 0x68 | `protected Color _notCurrentLevelBackgroundColor;` |
| 0x78 | `protected Color _currentLevelBackgroundColor;` |
| 0x88 | `protected Color _currentLevelTextColor;` |
| 0x98 | `protected Color _notCurrentLevelTextColor;` |
| 0xA8 | `protected GameObject currentBackground;` |
| 0xB0 | `protected List<BattlePassBaseRewardView> kKw;` |
| 0xB8 | `protected int kKJ;` |
| 0xC0 | `protected Hn kKX;` |
| 0xC8 | `private HP kKT;` |
| 0xD0 | `protected tS kKL;` |
| 0xD8 | `protected ir kKo;` |
| 0xE0 | `protected fEd kKy;` |
| 0xF8 | `private RectTransform kKB;` |
| 0x100 | `private RectTransform kKm;` |
| 0x108 | `private bool kKR;` |
| 0x110 | `private readonly Vector3[] kKb;` |
| 0x118 | `private readonly Vector3[] kKl;` |
| - | `private static readonly Vector3[] cullCorners;` |

<details><summary>methods (27)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A52EC | 0x2F71AB4 |  | `public void add_kKz(Action<BattlePassBaseRewardView> value)` |
| 0x37A539C | 0x2F71AB8 |  | `public void remove_kKz(Action<BattlePassBaseRewardView> value)` |
| 0x37A544C | 0x2F71ABC |  | `public void add_kKh(Action<BattlePassBaseRewardView> value)` |
| 0x37A54FC | 0x2F71AC0 |  | `public void remove_kKh(Action<BattlePassBaseRewardView> value)` |
| 0x37A55AC | 0x2F71AC4 |  | `public void dAf(tS e, fEd f)` |
| 0x37A5678 | 0x2F71AC8 | 4 | `public virtual void dAF(tK e, int f, Hn F, ir d)` |
| 0x37A5BD4 | 0x2F7278C |  | `public void dAd()` |
| 0x37A5AEC | 0x2F72790 |  | `private UniTaskVoid dAc(RewardEntry e, RectTransform f, bool F)` |
| - | 0x2F72798 |  | `private IEnumerator dAU()` |
| 0x37A60D4 | 0x2F727A0 |  | `private IEnumerator dAY()` |
| 0x37A6168 | 0x2F727A8 |  | `private bool dAW()` |
| 0x37A61A8 | 0x2F727B0 |  | `private void OnDestroy()` |
| 0x37A64FC | 0x2F727B4 |  | `public void dAE()` |
| 0x37A6764 | 0x2F727B8 |  | `public List<BattlePassBaseRewardView> dAA()` |
| 0x37A6808 | 0x2F727C0 |  | `protected void dAu(BattlePassBaseRewardView e)` |
| 0x37A6924 | 0x2F727C4 |  | `private void dAk(tg e, BattlePassBaseRewardView f)` |
| 0x37A601C | 0x2F727C8 |  | `protected void dAO()` |
| 0x37A61AC | 0x2F727CC |  | `private void dAt()` |
| 0x37A6974 | 0x2F727D0 |  | `private void dAr(int e)` |
| 0x37A5E1C | 0x2F727D4 |  | `protected void dAN()` |
| 0x37A6978 | 0x2F727D8 |  | `public bool dAq()` |
| 0x37A6C08 | 0x2F727E0 |  | `public void .ctor()` |
| 0x37A6CE4 | 0x2F727E8 |  | `private bool dAs(BattlePassBaseRewardView e)` |
| - | 0x2F727F0 |  | `public void SetCulled(float minWorldX, float maxWorldX)` |
| - | 0x2F72160 |  | `private void CreateTrack(Dictionary<int, List<RewardEntry>> rewards, RectTransform parent, bool paid, qU service)` |
| - | 0x2F729DC |  | `public void RefreshProgress(Hn progress)` |
| - | 0x2F72D3C |  | `private static void .cctor()` |

</details>

### public class `BattlePassMediumRewardView` : MonoBehaviour  
`TypeDefIndex 3756`

| offset | field |
|---|---|
| 0x20 | `private BattlePassBaseRewardView _battlePassBaseRewardView;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A730C | 0x2F72E80 |  | `public void dAC(tg e, bool f, fEd F)` |
| 0x37A736C | 0x2F72E84 |  | `public void .ctor()` |

</details>

### public class `BattlePassPromoRewardView` : MonoBehaviour  
`TypeDefIndex 3757`

| offset | field |
|---|---|
| 0x20 | `private BattlePassBaseRewardView _battlePassBasePromoRewardView;` |
| 0x28 | `private TextMeshProUGUI _levelText;` |
| 0x30 | `private Sprite _paidRewardBackground;` |
| 0x38 | `public Action<tg, BattlePassBaseRewardView> PreviewRequested;` |

Properties: `public BattlePassBaseRewardView smv { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F72E8C |  | `public BattlePassBaseRewardView get_smv()` |
| 0x37A737C | 0x2F72E94 |  | `public void dAj(tg e, int f, bool F, fEd d)` |
| 0x37A75E0 | 0x2F73148 |  | `private void dAa(tg e, BattlePassBaseRewardView f)` |
| 0x37A75FC | 0x2F73164 |  | `public void .ctor()` |

</details>

### public class `BattlePassRepeatableRewardView` : BattlePassLevelView  
`TypeDefIndex 3758`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A7604 | 0x2F7316C | 4 | `public override void dAF(tK e, int f, Hn F, ir d)` |
| 0x37A7AF4 | 0x2F73170 |  | `public void .ctor()` |

</details>

### public class `BattlePassUserProgressView` : MonoBehaviour  
`TypeDefIndex 3759`

| offset | field |
|---|---|
| 0x20 | `private TextMeshProUGUI _levelText;` |
| 0x28 | `private Image _experienceProgressSlider;` |
| 0x30 | `private TextMeshProUGUI _experienceText;` |
| 0x38 | `private Hn kKx;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379D55C | 0x2F731C8 |  | `public void dAQ(Hn e)` |
| 0x37A7CA0 | 0x2F73584 |  | `private void OnDisable()` |
| 0x37A7B40 | 0x2F7340C |  | `private void dAH(int e)` |
| 0x37A7AF8 | 0x2F7336C |  | `private void dAi(int e)` |
| 0x37A7D78 | 0x2F7366C |  | `public void .ctor()` |

</details>

### public class `SmallRewardView` : MonoBehaviour  
`TypeDefIndex 3760`

| offset | field |
|---|---|
| 0x20 | `private BattlePassBaseRewardView _battlePassBaseRewardView;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A278C | 0x2F73674 |  | `public void dAw(tg e, bool f, fEd F)` |
| 0x37A7D80 | 0x2F73724 |  | `public void .ctor()` |

</details>
