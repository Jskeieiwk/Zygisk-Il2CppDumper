# namespace `HyperHug.Games.BR24.Features.UiSystem.Screens.BattlePass.Scripts.Screens`  (5 types)

### public class `BattlePassInAppScreen` : BaseScreen<tm>  
`TypeDefIndex 3764`

| offset | field |
|---|---|
| 0x40 | `private Image _backgroundImage;` |
| 0x48 | `private RectTransform _rewardsContent;` |
| 0x50 | `private SmallRewardView _battlePassMediumRewardViewPrefab;` |
| 0x58 | `private Image _premiumBackgroundRight;` |
| 0x60 | `private Image _premiumBackgroundLeft;` |
| 0x68 | `private Image _premiumIconRight;` |
| 0x70 | `private Image _premiumIconLeft;` |
| 0x78 | `private TextMeshProUGUI _premiumHeaderText;` |
| 0x80 | `private TextMeshProUGUI _premiumBodyText;` |
| 0x88 | `private TextMeshProUGUI _premiumPlusHeaderText;` |
| 0x90 | `private TextMeshProUGUI _premiumPlusBodyText;` |
| 0x98 | `private rA _regularBuyButton;` |
| 0xA0 | `private rA _premiumBuyButton;` |
| 0xA8 | `private TextMeshProUGUI _regularPriceText;` |
| 0xB0 | `private TextMeshProUGUI _premiumPriceText;` |
| 0xB8 | `private TextMeshProUGUI _discountedPriceText;` |
| 0xC0 | `private TextMeshProUGUI _premiumDiscountText;` |
| 0xC8 | `private TextMeshProUGUI _exclusiveRewardText;` |
| 0xE0 | `private tS kKP;` |
| 0xE8 | `private tm kKD;` |
| 0xF0 | `private fEd kKn;` |
| - | `private readonly List<SmallRewardView> previewRewards;` |

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A7D88 | 0x2F7372C |  | `public void add_kKK(Action value)` |
| 0x37A7E24 | 0x2F73730 |  | `public void remove_kKK(Action value)` |
| 0x37A7EC0 | 0x2F73734 |  | `public void add_kKG(Action value)` |
| 0x37A7F5C | 0x2F73738 |  | `public void remove_kKG(Action value)` |
| 0x37A7FF8 | 0x2F7373C |  | `public void dAy(tS e, fEd f)` |
| 0x37A802C | 0x2F73740 | 15 | `protected override void dYV(tm e)` |
| 0x37A8550 | 0x2F75554 |  | `private void dAz()` |
| 0x37A8944 | 0x2F75558 |  | `private UniTask dAh(RewardEntry e, Transform f)` |
| 0x37A8A10 | 0x2F75564 | 20 | `protected override void dYI()` |
| 0x37A8AE8 | 0x2F75568 | 21 | `protected override void dWe()` |
| 0x37A8B18 | 0x2F7556C |  | `public void .ctor()` |
| 0x37A8B60 | 0x2F7562C |  | `private void dAB()` |
| 0x37A8B7C | 0x2F75630 |  | `private void dAm()` |
| - | 0x2F74120 |  | `public static int EffectivePlusPrice(int normal, int sale)` |
| - | 0x2F73F80 |  | `private static void SetLocalized(TextMeshProUGUI text, string token, string fallback)` |
| - | 0x2F74130 |  | `private static void ArrangePrice(rA button, TextMeshProUGUI price, TextMeshProUGUI oldPrice, bool discount)` |
| - | 0x2F75634 |  | `private static void SetPriceSize(TextMeshProUGUI text, float fontSize)` |
| - | 0x2F749B8 |  | `private void BuildRewardPreview(BattlePassConfig config, int startLevel)` |
| - | 0x2F7589C |  | `public static List<RewardEntry> PreviewLevelRewards(BattlePassConfig config, int startLevel)` |

</details>

### public class `BattlePassLevelsScreen` : BaseScreen<tR>  
`TypeDefIndex 3766`

| offset | field |
|---|---|
| 0x40 | `private Image _backgroundImage;` |
| 0x48 | `private TextMeshProUGUI _screenNameText;` |
| 0x50 | `private TextMeshProUGUI _headerText;` |
| 0x58 | `private SmallRewardView _smallRewardViewPrefab;` |
| 0x60 | `private rA _buyCustomLevelsCountButton;` |
| 0x68 | `private TextMeshProUGUI _leftHeaderText;` |
| 0x70 | `private TextMeshProUGUI _leftSubHeaderText;` |
| 0x78 | `private TextMeshProUGUI _leftLevelsText;` |
| 0x80 | `private RectTransform _leftRewardsContent;` |
| 0x88 | `private rA _minusButton;` |
| 0x90 | `private rA _plusButton;` |
| 0x98 | `private rA _plus10Button;` |
| 0xA0 | `private TextMeshProUGUI _leftPriceText;` |
| 0xA8 | `private rA _buyLevelsPackButton;` |
| 0xB0 | `private TextMeshProUGUI _rightHeaderText;` |
| 0xB8 | `private TextMeshProUGUI _rightSubHeaderText;` |
| 0xC0 | `private RectTransform _rightRewardsContent;` |
| 0xC8 | `private TextMeshProUGUI _rightPriceText;` |
| 0xD0 | `private TextMeshProUGUI _rightDiscountedPriceText;` |
| 0xD8 | `private TextMeshProUGUI _rightDiscountText;` |
| 0xE0 | `private TextMeshProUGUI _rightBottomText;` |
| 0xE8 | `private tS kKv;` |
| 0xF0 | `private fEd kKS;` |
| 0xF8 | `private HP kKI;` |
| - | `private int selectedCount;` |

<details><summary>methods (32)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37A8ED4 | 0x2F75E40 |  | `public void add_kKM(Action value)` |
| 0x37A8F74 | 0x2F75E44 |  | `public void remove_kKM(Action value)` |
| 0x37A9014 | 0x2F75E48 |  | `public void add_kGe(Action value)` |
| 0x37A90B4 | 0x2F75E4C |  | `public void remove_kGe(Action value)` |
| 0x37A9154 | 0x2F75E50 |  | `public void add_kGf(Action value)` |
| 0x37A91F4 | 0x2F75E54 |  | `public void remove_kGf(Action value)` |
| 0x37A9294 | 0x2F75E58 |  | `public void add_kGF(Action value)` |
| 0x37A9334 | 0x2F75E5C |  | `public void remove_kGF(Action value)` |
| 0x37A93D4 | 0x2F75E60 |  | `public void add_kGd(Action value)` |
| 0x37A9474 | 0x2F75E64 |  | `public void remove_kGd(Action value)` |
| 0x37A9514 | 0x2F75E68 |  | `public void dAv(tS e, fEd f)` |
| 0x37A9548 | 0x2F75E6C | 15 | `protected override void dYV(tR e)` |
| 0x37A9C2C | 0x2F767E4 | 20 | `protected override void dYI()` |
| 0x37A9DDC | 0x2F767E8 | 21 | `protected override void dWe()` |
| 0x37A9E3C | 0x2F76184 |  | `public void dAS(HP e, int f)` |
| 0x37AA434 | 0x2F77218 |  | `private UniTask dAI(RewardEntry e, Transform f)` |
| 0x37A96E4 | 0x2F77224 |  | `private void dAM(HP e)` |
| 0x37AA514 | 0x2F77228 |  | `private void due()` |
| 0x37AA294 | 0x2F769A8 |  | `private List<RewardEntry> duf(HP e, int f)` |
| 0x37AA5A8 | 0x2F7722C |  | `public void .ctor()` |
| 0x37AA5F0 | 0x2F772A0 |  | `private void duF()` |
| 0x37AA60C | 0x2F772A4 |  | `private void dud()` |
| 0x37AA628 | 0x2F772A8 |  | `private void duc()` |
| 0x37AA644 | 0x2F772AC |  | `private void duU()` |
| 0x37AA660 | 0x2F772B0 |  | `private void duY()` |
| - | 0x2F767EC |  | `private static string PackDiscountLabel(int regularPrice, int price)` |
| - | 0x2F76B60 |  | `private void RenderRewards(RectTransform parent, List<RewardEntry> rewards, TextMeshProUGUI label)` |
| - | 0x2F772B4 |  | `private void <dYV>b__41_0()` |
| - | 0x2F772C4 |  | `private void <dYV>b__41_1()` |
| - | 0x2F772D4 |  | `private void <dYV>b__41_2()` |
| - | 0x2F772E4 |  | `private void <dYV>b__41_3()` |
| - | 0x2F772F4 |  | `private void <dYV>b__41_4()` |

</details>

### public class `BattlePassPromoScreen` : BaseScreen<tb>  
`TypeDefIndex 3769`

| offset | field |
|---|---|
| 0x40 | `private rA _upgradeButton;` |
| 0x48 | `private TextMeshProUGUI _discountText;` |
| 0x50 | `private Image _backgroundImage;` |
| 0x58 | `private TextMeshProUGUI _screenNameText;` |
| 0x60 | `private Image _freeBpImage;` |
| 0x68 | `private Image _premiumBpImage;` |
| 0x70 | `private BattlePassUiSkinPreviewReferenceHolder battlePassUiSkinPreviewReferenceHolder;` |
| 0x78 | `private BattlePassPromoRewardView _promoRewardViewPrefab;` |
| 0x80 | `private RectTransform _freeContentLayout;` |
| 0x88 | `private RectTransform _paidContentLayout;` |
| 0x98 | `private List<BattlePassPromoRewardView> kGW;` |
| 0xA0 | `private tb kGE;` |
| 0xA8 | `private tS kGA;` |
| 0xB0 | `private ir kGu;` |
| 0xB8 | `private iC kGk;` |
| 0xC0 | `private fEd kGO;` |
| - | `private string renderedId;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37AAA2C | 0x2F77328 |  | `public void add_kGY(Action value)` |
| 0x37AAAC8 | 0x2F7732C |  | `public void remove_kGY(Action value)` |
| 0x37AAB64 | 0x2F77330 |  | `public void duO(tS e, ir f, iC.is F, fEd d)` |
| 0x37AABE4 | 0x2F77334 | 15 | `protected override void dYV(tb e)` |
| 0x37AB310 | 0x2F77E78 | 18 | `protected override void dYp()` |
| 0x37AB5B0 | 0x2F77E7C | 19 | `protected override void dYv()` |
| 0x37AB5CC | 0x2F77E80 | 20 | `protected override void dYI()` |
| 0x37AB848 | 0x2F77E84 | 21 | `protected override void dWe()` |
| 0x37ABA78 | 0x2F77E88 |  | `private void dut(tg e, BattlePassBaseRewardView f)` |
| 0x37AAE38 | 0x2F77E8C |  | `private void dur()` |
| - | 0x2F77E90 |  | `private UniTask duN(RewardEntry e, Transform f, int F, bool d)` |
| 0x37AB314 | 0x2F77E9C |  | `private void duq()` |
| 0x37ABD24 | 0x2F77EA0 |  | `public void .ctor()` |
| 0x37ABDC0 | 0x2F77F0C |  | `private void dus()` |
| - | 0x2F777CC |  | `private void Populate(Dictionary<int, List<RewardEntry>> rewards, RectTransform parent, bool paid)` |

</details>

### public class `BattlePassScreen` : BaseScreen<tK>  
`TypeDefIndex 3775`

| offset | field |
|---|---|
| 0x40 | `private TextMeshProUGUI _seasonNameText;` |
| 0x48 | `private TextMeshProUGUI _seasonSpecialText;` |
| 0x50 | `private TextMeshProUGUI _lvlText;` |
| 0x58 | `private Image _specialBackground;` |
| 0x60 | `private UiTimer _seasonTimer;` |
| 0x68 | `private BattlePassUserProgressView _battlePassUserProgressView;` |
| 0x70 | `private rA _buyLevelsButton;` |
| 0x78 | `private rA _scrollToUnclaimedButton;` |
| 0x80 | `private rA _vaultButton;` |
| 0x88 | `private BattlePassUiSkinPreviewReferenceHolder battlePassUiSkinPreviewReferenceHolder;` |
| 0x90 | `private rA _howToEarnExpButton;` |
| 0x98 | `private UiTipView _howToEarnExpTipView;` |
| 0xA0 | `private rA _battlePassInfoButton;` |
| 0xA8 | `private UiTipView _battlePassInfoTipView;` |
| 0xB0 | `private RectTransform _battlePassLevelsContent;` |
| 0xB8 | `private HorizontalLayoutGroup _battlePassLevelsHorizontalLayout;` |
| 0xC0 | `private ScrollRect _battlePassLevelsScroll;` |
| 0xC8 | `private RectTransform _battlePassLevelsScrollRect;` |
| 0xD0 | `private BattlePassLevelView _battlePassLevelViewPrefab;` |
| 0xD8 | `private BattlePassRepeatableRewardView _battlePassRepeatableRewardView;` |
| 0xE0 | `private BattlePassRepeatableHighlightedRewardView _battlePassRepeatableHighlightedRewardView;` |
| 0xE8 | `private BattlePassHighlightedRewardView _highlightView;` |
| 0xF0 | `private Image _highlightBackground;` |
| 0xF8 | `private Image _highlightImage;` |
| 0x100 | `private rA _upgradeButton;` |
| 0x108 | `private rA _getItAllButton;` |
| 0x110 | `private TextMeshProUGUI _discountText;` |
| 0x118 | `private rA _giftButton;` |
| 0x120 | `private rA _missionsButton;` |
| 0x128 | `private GameObject missionsNotification;` |
| 0x130 | `private Image _defaultBackgroundImage;` |
| 0x138 | `private Image _previewBackgroundImage;` |
| 0x140 | `private Image _paidRewardMainBackgroundImage;` |
| 0x148 | `private rA _debug100gemsButton;` |
| 0x150 | `private rA _debugResetButton;` |
| 0x158 | `private List<BattlePassScreen.PreviewFx> _previewFx;` |
| 0x160 | `private BattlePassCongratulationPopupReferenceHolder battlePassCongratulationPopupReferenceHolder;` |
| - | `private const float kGa = 0.75;` |
| 0x1B8 | `private List<BattlePassLevelView> kGz;` |
| 0x1C0 | `private BattlePassLevelView kGh;` |
| 0x1C8 | `private float kGB;` |
| 0x1CC | `private float kGm;` |
| 0x1D0 | `private BattlePassBaseRewardView kGR;` |
| 0x1D8 | `private ir kGb;` |
| 0x1E0 | `private iC kGl;` |
| 0x1E8 | `private fEd kGx;` |
| 0x1F0 | `private tK kGK;` |
| 0x1F8 | `private rU kGG;` |
| 0x200 | `private Hz.Ho kGP;` |
| 0x208 | `private HL kGD;` |
| - | `private string renderedConfigId;` |
| - | `private bool staticsCached;` |
| - | `private GameObject[] fxUpgradeNodes;` |
| - | `private Coroutine buildRoutine;` |
| - | `private float cullX;` |
| - | `private float cullW;` |
| - | `private float cullV;` |
| - | `private int cullCount;` |
| - | `private int cullFrames;` |
| - | `private static readonly Vector3[] cullViewport;` |

Properties: `private HL sRf { get; }`; `protected override bool DeactivateOnHide { get; }`; `public bool IsBuilding { get; }`

<details><summary>methods (76)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37AD020 | 0x2F77FB8 |  | `private HL get_sRf()` |
| 0x37AC2CC | 0x2F77FC0 |  | `public void add_kGQ(Action<int> value)` |
| 0x37AC380 | 0x2F77FC4 |  | `public void remove_kGQ(Action<int> value)` |
| 0x37AC434 | 0x2F77FC8 |  | `public void add_kGH(Action value)` |
| 0x37AC4D4 | 0x2F77FCC |  | `public void remove_kGH(Action value)` |
| 0x37AC574 | 0x2F77FD0 |  | `public void add_kGi(Action value)` |
| 0x37AC614 | 0x2F77FD4 |  | `public void remove_kGi(Action value)` |
| 0x37AC6B4 | 0x2F77FD8 |  | `public void add_kGw(Action value)` |
| 0x37AC754 | 0x2F77FDC |  | `public void remove_kGw(Action value)` |
| 0x37AC7F4 | 0x2F77FE0 |  | `public void add_kGJ(Action value)` |
| 0x37AC894 | 0x2F77FE4 |  | `public void remove_kGJ(Action value)` |
| 0x37AC934 | 0x2F77FE8 |  | `public void add_kGX(Action value)` |
| 0x37AC9D4 | 0x2F77FEC |  | `public void remove_kGX(Action value)` |
| 0x37ACA74 | 0x2F77FF0 |  | `public void add_kGT(Action value)` |
| 0x37ACB14 | 0x2F77FF4 |  | `public void remove_kGT(Action value)` |
| 0x37ACBB4 | 0x2F77FF8 |  | `public void add_kGL(Action value)` |
| 0x37ACC54 | 0x2F77FFC |  | `public void remove_kGL(Action value)` |
| 0x37ACCF4 | 0x2F78000 |  | `public void add_kGo(Action value)` |
| 0x37ACD94 | 0x2F78004 |  | `public void remove_kGo(Action value)` |
| 0x37ACE34 | 0x2F78008 |  | `public void add_kGy(Action value)` |
| 0x37ACED4 | 0x2F7800C |  | `public void remove_kGy(Action value)` |
| 0x37ACF74 | 0x2F78010 |  | `public void duS(ir e, iC.is f, fEd F, rU d, Hz.Ho c)` |
| 0x37AD094 | 0x2F78014 | 20 | `protected override void dYI()` |
| 0x37AD5BC | 0x2F78018 |  | `private void duM()` |
| 0x37AD7F0 | 0x2F7801C | 21 | `protected override void dWe()` |
| 0x37ADA50 | 0x2F78020 | 16 | `protected override void dke()` |
| 0x37ADBC8 | 0x2F78024 |  | `private void dkf()` |
| 0x37ADBE4 | 0x2F78028 | 15 | `protected override void dYV(tK e)` |
| 0x37AE344 | 0x2F798AC |  | `public static bool HasClaimableRewards(BattlePassConfig config, Hn progress)` |
| - | 0x2F797CC |  | `public void RefreshClaimButton()` |
| - | 0x2F79BC8 |  | `private void dkF(tK e, int f)` |
| 0x37AE5A0 | 0x2F79BCC |  | `private void dkd(BattlePassBaseRewardView e)` |
| 0x37AE784 | 0x2F79BD0 |  | `private void dkc(int e)` |
| 0x37AE280 | 0x2F79BD4 |  | `private UniTaskVoid dkU(tK e, int f)` |
| 0x37AE93C | 0x2F79BDC |  | `private void dkY()` |
| - | 0x2F79BE0 |  | `private IEnumerator dkW()` |
| 0x37AECD0 | 0x2F79BE8 | 19 | `protected override void dYv()` |
| 0x37AED04 | 0x2F79BEC |  | `private void dkE(BattlePassBaseRewardView e)` |
| 0x37AF038 | 0x2F79BF0 |  | `private void dkA()` |
| 0x37AF088 | 0x2F79BF4 |  | `private IEnumerator Start()` |
| 0x37AF0FC | 0x2F79BFC |  | `public void dku(bool e = false)` |
| 0x37ADB20 | 0x2F79D1C |  | `private bool dkk()` |
| 0x37AF2F4 | 0x2F79D24 |  | `private void dkO(BattlePassLevelView e, bool f = false)` |
| 0x37AF4C4 | 0x2F79D28 | 17 | `protected override void dkt()` |
| 0x37ADA9C | 0x2F79D2C |  | `private void dkr()` |
| 0x37AEE4C | 0x2F79D30 |  | `private void dkN()` |
| 0x37AF4E0 | 0x2F79D34 |  | `private void dkq(Vector2 e)` |
| 0x37AF6D0 | 0x2F79D38 |  | `private bool dks(BattlePassLevelView e)` |
| 0x37AD770 | 0x2F79D40 |  | `private void dkC(bool e)` |
| 0x37AEE54 | 0x2F79D44 |  | `private void dkZ(iQ e)` |
| 0x37AD610 | 0x2F79D48 |  | `private void dkj()` |
| 0x37AF73C | 0x2F79D4C |  | `public void .ctor()` |
| 0x37AF82C | 0x2F79DC8 |  | `private void dka()` |
| 0x37AF84C | 0x2F79DCC |  | `private void dkQ()` |
| 0x37AF868 | 0x2F79DD0 |  | `private void dkH()` |
| 0x37AF884 | 0x2F79DD4 |  | `private void dki()` |
| 0x37AF8A0 | 0x2F79DD8 |  | `private void dkw()` |
| 0x37AF8BC | 0x2F79DDC |  | `private void dkJ()` |
| 0x37AF8D8 | 0x2F79DE0 |  | `private void dkX()` |
| 0x37AF8F4 | 0x2F79DE4 |  | `private void dkT()` |
| 0x37AF910 | 0x2F79DE8 |  | `private void dkL()` |
| 0x37AF92C | 0x2F79DEC |  | `private void dko()` |
| - | 0x2F7938C |  | `private static void Wire(rA button, Action action)` |
| - | 0x2F79428 |  | `private void PreparePreview()` |
| - | 0x2F79DF0 |  | `public void ShowRewardPreview(tg reward, BattlePassBaseRewardView selected)` |
| - | 0x2F7AD10 |  | `protected override bool get_DeactivateOnHide()` |
| - | 0x2F7AD18 |  | `public bool get_IsBuilding()` |
| - | 0x2F7971C |  | `private void StopBuild()` |
| - | 0x2F7AD28 |  | `private void OnDisable()` |
| - | 0x2F79760 |  | `private IEnumerator BuildLevels()` |
| - | 0x2F7AD64 |  | `private void LateUpdate()` |
| - | 0x2F7B0F8 |  | `private void UpdateHighlightedReward(Vector2 value)` |
| - | 0x2F7B18C |  | `private static void .cctor()` |
| - | 0x2F7B200 |  | `private void <dYV>b__92_0()` |
| - | 0x2F7B3A0 |  | `private void <dYV>b__92_1()` |
| - | 0x2F7B41C |  | `private void <dYV>b__92_2()` |

</details>

### public class `VaultScreen` : BaseScreen<tG>  
`TypeDefIndex 3777`

| offset | field |
|---|---|
| 0x40 | `private BattlePassBaseRewardView baseRewardView;` |
| 0x48 | `private rA vaultTipButton;` |
| 0x50 | `private UiTipView uiTipView;` |
| 0x58 | `private Transform rewardContainer;` |
| 0x60 | `private List<BattlePassBaseRewardView> kGv;` |
| 0x68 | `private ItemDatabase kGS;` |
| 0x70 | `private ZJ kGI;` |
| 0x78 | `private fEd kGM;` |

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37B05E0 | 0x2F7B894 |  | `public void dky(ZJ e, ItemDatabase f, fEd F)` |
| 0x37B0628 | 0x2F7B898 | 15 | `protected override void dYV(tG e)` |
| - | 0x2F7BC20 |  | `public static List<RewardEntry> GroupSafeRewards(JArray rows)` |
| 0x37B0704 | 0x2F7C2A0 | 16 | `protected override void dke()` |
| 0x37B0AF8 | 0x2F7C2A4 | 17 | `protected override void dkt()` |
| 0x37B0B40 | 0x2F7C2A8 | 20 | `protected override void dYI()` |
| 0x37B0CA8 | 0x2F7C2AC | 21 | `protected override void dWe()` |
| 0x37B0708 | 0x2F7C2B0 |  | `private void dkz()` |
| 0x37B0D38 | 0x2F7C2B4 |  | `private void dkh()` |
| 0x37B0E50 | 0x2F7C2B8 |  | `public void .ctor()` |
| - | 0x2F7C324 |  | `private void <dYV>b__9_0(JObject data)` |

</details>
