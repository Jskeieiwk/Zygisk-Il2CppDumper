# namespace `HyperHug.Games.BR24.Features.UiSystem.Screens.Missions.Scripts`  (1 types)

### public class `MissionsScreen` : BaseScreen<tJ>  
`TypeDefIndex 3737`

| offset | field |
|---|---|
| 0x40 | `private Image _backgroundImage;` |
| 0x48 | `private TextMeshProUGUI _screenNameText;` |
| 0x50 | `private UiTimer _seasonTimer;` |
| 0x58 | `private Image _bpLogoImage;` |
| 0x60 | `private BattlePassUiSkinPreviewReferenceHolder battlePassUiSkinPreviewReferenceHolder;` |
| 0x68 | `private BattlePassUserProgressView _battlePassUserProgressView;` |
| 0x70 | `private TextMeshProUGUI _selectedViewText;` |
| 0x78 | `private RectTransform _selectedViewPanel;` |
| 0x80 | `private MissionsWeekButtonsView _missionsWeekButtonsView;` |
| 0x88 | `private MissionsView _missionsView;` |
| 0x90 | `private MissionsScreenButton _dailyButton;` |
| 0x98 | `private rA _battlePassButton;` |
| 0xA0 | `private rA _battlePassSecondButton;` |
| 0xA8 | `private rA _infoButton;` |
| 0xB0 | `private UiTipView _uiTipView;` |
| 0xB8 | `private ScrollRect scrollRect;` |
| 0xC0 | `private GameObject topFade;` |
| 0xC8 | `private GameObject bottomFade;` |
| 0xD0 | `private TextMeshProUGUI missionsProgressText;` |
| 0xD8 | `private TextMeshProUGUI _nextLevelRewardText;` |
| 0x120 | `private tJ kxN;` |
| 0x128 | `private tS kxq;` |
| 0x130 | `private int kxs;` |
| 0x138 | `private ir kxC;` |
| 0x140 | `private iC kxZ;` |
| 0x148 | `private fEd kxj;` |
| 0x150 | `private rU kxa;` |
| - | `private int <kxr>k__BackingField;` |
| - | `private bool selectedWeekly;` |
| - | `private TMP_Text goLabel;` |
| - | `private TMP_FontAsset boldFont;` |
| - | `private bool boldFontLoaded;` |

Properties: `public bool smG { get; }`; `public int kxr { get; set; }`; `protected override bool DeactivateOnHide { get; }`

<details><summary>methods (50)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x379D180 | 0x2F6AC30 |  | `public bool get_smG()` |
| - | 0x2F6AC38 |  | `public int get_kxr()` |
| - | 0x2F6AC40 |  | `private void set_kxr(int value)` |
| 0x379C8B8 | 0x2F6AC48 |  | `public void add_kxW(Action value)` |
| 0x379C954 | 0x2F6AC4C |  | `public void remove_kxW(Action value)` |
| 0x379C9F0 | 0x2F6AC50 |  | `public void add_kxE(Action value)` |
| 0x379CA8C | 0x2F6AC54 |  | `public void remove_kxE(Action value)` |
| 0x379CB28 | 0x2F6AC58 |  | `public void add_kxA(Action value)` |
| 0x379CBC4 | 0x2F6AC5C |  | `public void remove_kxA(Action value)` |
| 0x379CC60 | 0x2F6AC60 |  | `public void add_kxu(Action value)` |
| 0x379CCFC | 0x2F6AC64 |  | `public void remove_kxu(Action value)` |
| 0x379CD98 | 0x2F6AC68 |  | `public void add_kxk(Action value)` |
| 0x379CE38 | 0x2F6AC6C |  | `public void remove_kxk(Action value)` |
| 0x379CED8 | 0x2F6AC70 |  | `public void add_kxO(Action<int> value)` |
| 0x379CF8C | 0x2F6AC74 |  | `public void remove_kxO(Action<int> value)` |
| 0x379D040 | 0x2F6AC78 |  | `public void add_kxt(Action value)` |
| 0x379D0E0 | 0x2F6AC7C |  | `public void remove_kxt(Action value)` |
| 0x379D1AC | 0x2F6AC80 |  | `public void dYn(tS e, ir f, iC.is F, fEd d, rU c)` |
| 0x379D244 | 0x2F6AC84 | 15 | `protected override void dYV(tJ e)` |
| 0x379E000 | 0x2F6CAC4 |  | `private void dYg(bool e)` |
| 0x379E070 | 0x2F6CAC8 | 18 | `protected override void dYp()` |
| 0x379E3D8 | 0x2F6DCB0 | 19 | `protected override void dYv()` |
| 0x379E1C4 | 0x2F6D1FC |  | `private tg dYS(tJ e)` |
| 0x379E3F4 | 0x2F6DCB4 |  | `private void Start()` |
| 0x379E450 | 0x2F6DCB8 | 20 | `protected override void dYI()` |
| 0x379E904 | 0x2F6DCBC |  | `private void dYM(Vector2 e)` |
| 0x379E9B8 | 0x2F6DCC0 | 21 | `protected override void dWe()` |
| 0x379EC14 | 0x2F6DCC4 |  | `private void dWf(List<ConfigMission> e, List<Mission> f)` |
| 0x379F51C | 0x2F6C7F4 |  | `public void dWF()` |
| 0x379F8F4 | 0x2F6C510 |  | `public void dWd(int e)` |
| 0x379FBF8 | 0x2F6EB5C |  | `public static bool dWc(HP e)` |
| 0x379FC20 | 0x2F6ECF0 |  | `public static bool dWU(HP e)` |
| 0x379FD98 | 0x2F6ECFC |  | `public static bool dWY(HP e, int f)` |
| 0x379D874 | 0x2F6ED08 |  | `private static bool dWW(HP e)` |
| 0x37A0058 | 0x2F6ED10 |  | `public void dWE(bool e)` |
| 0x37A011C | 0x2F6ED14 |  | `public void dWA(bool e)` |
| 0x37A01F0 | 0x2F6ED18 |  | `private void dWu(int e)` |
| 0x37A020C | 0x2F6ED1C |  | `private void dWk()` |
| 0x37A0228 | 0x2F6ED20 |  | `private void dWO()` |
| 0x37A0244 | 0x2F6ED24 |  | `private void dWt()` |
| 0x37A0260 | 0x2F6ED28 |  | `public void .ctor()` |
| 0x37A02A8 | 0x2F6ED94 |  | `private void dWr()` |
| 0x37A02C4 | 0x2F6ED98 |  | `private void dWN()` |
| 0x37A02E0 | 0x2F6ED9C |  | `private void dWq()` |
| 0x37A02FC | 0x2F6EDA0 |  | `private void dWs()` |
| 0x37A0318 | 0x2F6EDA4 |  | `private void dWC()` |
| - | 0x2F6EB94 |  | `private static bool ReadyMissions(HP data, int duration, int week = 0)` |
| - | 0x2F6EDB0 |  | `protected override bool get_DeactivateOnHide()` |
| - | 0x2F6EDB8 |  | `public void PrewarmPreview()` |
| - | 0x2F6D650 |  | `private void RestoreForwardButton()` |

</details>
