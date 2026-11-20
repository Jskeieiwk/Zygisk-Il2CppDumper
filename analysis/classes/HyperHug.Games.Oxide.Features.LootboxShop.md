# namespace `HyperHug.Games.Oxide.Features.LootboxShop`  (21 types)

### public struct `EventDateTime`  
`TypeDefIndex 3657`

| offset | field |
|---|---|
| 0x0 | `public int Year;` |
| 0x4 | `public int Month;` |
| 0x8 | `public int Day;` |
| 0xC | `public int Hour;` |

### public class `ItemModel`  
`TypeDefIndex 3658`

| offset | field |
|---|---|
| - | `private string <Key>k__BackingField;` |
| - | `private bool <isSkin>k__BackingField;` |
| - | `private string <SkinKey>k__BackingField;` |
| - | `private AssetReference <PreviewImage>k__BackingField;` |
| - | `private AssetReference <GrantedPreviewImage>k__BackingField;` |
| - | `private Color <RarityColor>k__BackingField;` |
| - | `private Color <DescriptionColor>k__BackingField;` |
| - | `public Sprite iconSprite;` |
| - | `public Sprite previewSprite;` |
| - | `public Sprite grantedSprite;` |

Properties: `public string Key { get; set; }`; `public bool isSkin { get; set; }`; `public string SkinKey { get; set; }`; `public AssetReference PreviewImage { get; set; }`; `public AssetReference GrantedPreviewImage { get; set; }`; `public Color RarityColor { get; set; }`; `public Color DescriptionColor { get; set; }`; `public string ServerKey { get; }`; `private string Readable { get; }`; `public string DisplayName { get; }`; `public string WeaponName { get; }`

<details><summary>methods (19)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5E0E0 |  | `public string get_Key()` |
| - | 0x2F5E0E8 |  | `private void set_Key(string value)` |
| - | 0x2F5E0F0 |  | `public bool get_isSkin()` |
| - | 0x2F5E0F8 |  | `private void set_isSkin(bool value)` |
| - | 0x2F5E104 |  | `public string get_SkinKey()` |
| - | 0x2F5E10C |  | `private void set_SkinKey(string value)` |
| - | 0x2F5E114 |  | `public AssetReference get_PreviewImage()` |
| - | 0x2F5E11C |  | `private void set_PreviewImage(AssetReference value)` |
| - | 0x2F5E124 |  | `public AssetReference get_GrantedPreviewImage()` |
| - | 0x2F5E12C |  | `private void set_GrantedPreviewImage(AssetReference value)` |
| - | 0x2F5E134 |  | `public Color get_RarityColor()` |
| - | 0x2F5E140 |  | `private void set_RarityColor(Color value)` |
| - | 0x2F5E14C |  | `public Color get_DescriptionColor()` |
| - | 0x2F5E158 |  | `private void set_DescriptionColor(Color value)` |
| - | 0x2F5E164 |  | `public string get_ServerKey()` |
| - | 0x2F5E1A0 |  | `private string get_Readable()` |
| - | 0x2F5E334 |  | `public string get_DisplayName()` |
| - | 0x2F5E3C4 |  | `public string get_WeaponName()` |
| - | 0x2F5E434 |  | `public void .ctor()` |

</details>

### public class `LootboxShopAvailableResponse`  
`TypeDefIndex 3659`

| offset | field |
|---|---|
| 0x10 | `public bool isSuccess;` |
| 0x18 | `public LootboxShopErrorData error;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B92FC | 0x2F5E43C |  | `public void .ctor()` |

</details>

### public class `LootboxShopBanner` : MonoBehaviour  
`TypeDefIndex 3660`

| offset | field |
|---|---|
| - | `private Text _timerText;` |
| - | `private Button _openButton;` |
| - | `private LootboxShopsMenuManager Oth;` |
| - | `private LootboxShopModel OtB;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5E444 |  | `public void dSl(LootboxShopModel e, LootboxShopsMenuManager f)` |
| - | 0x2F5EB14 |  | `private void OnEnable()` |
| - | 0x2F5EBE8 |  | `private void OnDisable()` |
| - | 0x2F5E9D0 |  | `private void RefreshTimer()` |
| - | 0x2F5EE30 |  | `private void dSx()` |
| - | 0x2F5F064 |  | `public void .ctor()` |

</details>

### public class `LootboxShopBannerModel`  
`TypeDefIndex 3661`

| offset | field |
|---|---|
| - | `private AssetReference <Prefab>k__BackingField;` |
| - | `public GameObject prefabObject;` |

Properties: `public AssetReference Prefab { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5F06C |  | `public AssetReference get_Prefab()` |
| - | 0x2F5F074 |  | `private void set_Prefab(AssetReference value)` |
| - | 0x2F5F07C |  | `public void .ctor()` |

</details>

### public static class `LootboxShopClient`  
`TypeDefIndex 3665`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5F084 |  | `private static void Send(string path, bool post, Action<string> ok, Action<string> failed)` |
| - | 0x2F5F190 |  | `public static void State(string shopId, Action<bool, int, string[], LootboxShopErrorData> done)` |
| - | 0x2F5F2C8 |  | `public static void Purchase(string shopId, Action<bool, string, int, LootboxShopErrorData> done)` |

</details>

### public class `LootboxShopErrorData`  
`TypeDefIndex 3666`

| offset | field |
|---|---|
| - | `public const string LootBoxNotFound = "LB-001";` |
| - | `public const string AllItemsWon = "LB-002";` |
| - | `public const string InsufficientFunds = "LB-003";` |
| - | `public const string NotAvailableInCountry = "AU-002";` |
| - | `private string <Error>k__BackingField;` |

Properties: `public string Error { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5F838 |  | `public string get_Error()` |
| - | 0x2F5F840 |  | `private void set_Error(string value)` |
| - | 0x2F5F848 |  | `public void .ctor(string error)` |

</details>

### public static class `LootboxShopFx`  
`TypeDefIndex 3668`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5E730 |  | `public static void ApplyHeaders(GameObject root, LootboxShopModel model)` |
| - | 0x2F5E914 |  | `public static void ApplyHeadersLater(MonoBehaviour host, LootboxShopModel model)` |
| - | 0x2F5F954 |  | `private static IEnumerator Later(GameObject root, LootboxShopModel model)` |
| - | 0x2F5E4B0 |  | `public static void Apply(GameObject root)` |

</details>

### public class `LootboxShopItemView` : MonoBehaviour  
`TypeDefIndex 3669`

| offset | field |
|---|---|
| - | `private Button _itemButton;` |
| - | `private Image _rarityImage;` |
| - | `private GameObject[] _selectedFrames;` |
| - | `private GameObject _claimedFrame;` |
| - | `private Image _itemImage;` |
| - | `private bool isUsingExternalIcon;` |
| - | `private ItemModel <OtR>k__BackingField;` |
| - | `private Action<LootboxShopItemView> Otm;` |

Properties: `public ItemModel OtR { get; set; }`

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5FB1C |  | `public ItemModel get_OtR()` |
| - | 0x2F5FB24 |  | `private void set_OtR(ItemModel value)` |
| - | 0x2F5FB2C |  | `public void add_Otm(Action<LootboxShopItemView> value)` |
| - | 0x2F5FBDC |  | `public void remove_Otm(Action<LootboxShopItemView> value)` |
| - | 0x2F5FC8C |  | `public void dSn(ItemModel e, Sprite f, bool F)` |
| - | 0x2F5FF68 |  | `private void OnEnable()` |
| - | 0x2F60040 |  | `private void OnDisable()` |
| - | 0x2F5FDFC |  | `public void dSV(bool e)` |
| - | 0x2F5FED0 |  | `public void dSg(bool e)` |
| - | 0x2F60118 |  | `public void Subscribe(Action<LootboxShopItemView> handler)` |
| - | 0x2F6011C |  | `private void dSp()` |
| - | 0x2F6013C |  | `public void .ctor()` |

</details>

### public class `LootboxShopModel`  
`TypeDefIndex 3670`

| offset | field |
|---|---|
| - | `private string <Name>k__BackingField;` |
| - | `private string <Id>k__BackingField;` |
| - | `private EventDateTime <StartDate>k__BackingField;` |
| - | `private EventDateTime <EndDate>k__BackingField;` |
| - | `private int <DisplayPeriodInHours>k__BackingField;` |
| - | `private int <OpenPreviewItemNumber>k__BackingField;` |
| - | `private LootboxShopScreenModel <MainScreen>k__BackingField;` |
| - | `private LootboxShopPopUpModel <PopUp>k__BackingField;` |
| - | `private LootboxShopBannerModel <Banner>k__BackingField;` |
| - | `private string <Prices>k__BackingField;` |
| - | `public Sprite headerEn;` |
| - | `public Sprite headerRu;` |
| - | `public Sprite headerZh;` |

Properties: `public string Name { get; set; }`; `public string Id { get; set; }`; `public EventDateTime StartDate { get; set; }`; `public EventDateTime EndDate { get; set; }`; `public int DisplayPeriodInHours { get; set; }`; `public int OpenPreviewItemNumber { get; set; }`; `public LootboxShopScreenModel MainScreen { get; set; }`; `public LootboxShopPopUpModel PopUp { get; set; }`; `public LootboxShopBannerModel Banner { get; set; }`; `public string Prices { get; set; }`; `private string PopupKey { get; }`; `public int[] PriceList { get; }`; `public TimeSpan TimeLeft { get; }`

<details><summary>methods (30)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F60144 |  | `public string get_Name()` |
| - | 0x2F6014C |  | `private void set_Name(string value)` |
| - | 0x2F60154 |  | `public string get_Id()` |
| - | 0x2F6015C |  | `private void set_Id(string value)` |
| - | 0x2F60164 |  | `public EventDateTime get_StartDate()` |
| - | 0x2F60170 |  | `private void set_StartDate(EventDateTime value)` |
| - | 0x2F60178 |  | `public EventDateTime get_EndDate()` |
| - | 0x2F60184 |  | `private void set_EndDate(EventDateTime value)` |
| - | 0x2F6018C |  | `public int get_DisplayPeriodInHours()` |
| - | 0x2F60194 |  | `private void set_DisplayPeriodInHours(int value)` |
| - | 0x2F6019C |  | `public int get_OpenPreviewItemNumber()` |
| - | 0x2F601A4 |  | `private void set_OpenPreviewItemNumber(int value)` |
| - | 0x2F601AC |  | `public LootboxShopScreenModel get_MainScreen()` |
| - | 0x2F601B4 |  | `private void set_MainScreen(LootboxShopScreenModel value)` |
| - | 0x2F601BC |  | `public LootboxShopPopUpModel get_PopUp()` |
| - | 0x2F601C4 |  | `private void set_PopUp(LootboxShopPopUpModel value)` |
| - | 0x2F601CC |  | `public LootboxShopBannerModel get_Banner()` |
| - | 0x2F601D4 |  | `private void set_Banner(LootboxShopBannerModel value)` |
| - | 0x2F601DC |  | `public string get_Prices()` |
| - | 0x2F601E4 |  | `private void set_Prices(string value)` |
| - | 0x2F601EC |  | `private static DateTime Convert(EventDateTime value)` |
| - | 0x2F602CC |  | `public bool dSm()` |
| - | 0x2F5ECC0 |  | `public int dSR()` |
| - | 0x2F60384 |  | `public bool dSb()` |
| - | 0x2F604E4 |  | `public void MarkPopupShown()` |
| - | 0x2F60498 |  | `private string get_PopupKey()` |
| - | 0x2F60588 |  | `public int[] get_PriceList()` |
| - | 0x2F5F878 |  | `public Sprite HeaderFor(string language)` |
| - | 0x2F60728 |  | `public TimeSpan get_TimeLeft()` |
| - | 0x2F60808 |  | `public void .ctor()` |

</details>

### public class `LootboxShopPopup` : MonoBehaviour  
`TypeDefIndex 3671`

| offset | field |
|---|---|
| - | `private Text _timerText;` |
| - | `private Button _closeButton;` |
| - | `private Button _openButton;` |
| - | `private LootboxShopsMenuManager Otb;` |
| - | `private LootboxShopModel Otl;` |

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F60810 |  | `public void dSv(LootboxShopModel e, LootboxShopsMenuManager f)` |
| - | 0x2F609A8 |  | `private void OnEnable()` |
| - | 0x2F60B0C |  | `private void OnDisable()` |
| - | 0x2F60C70 |  | `private void dSS()` |
| - | 0x2F60CDC |  | `private void dSI()` |
| - | 0x2F60D90 |  | `public void .ctor()` |

</details>

### public class `LootboxShopPopUpModel`  
`TypeDefIndex 3672`

| offset | field |
|---|---|
| - | `private AssetReference <Prefab>k__BackingField;` |
| - | `public GameObject prefabObject;` |

Properties: `public AssetReference Prefab { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F60D98 |  | `public AssetReference get_Prefab()` |
| - | 0x2F60DA0 |  | `private void set_Prefab(AssetReference value)` |
| - | 0x2F60DA8 |  | `public void .ctor()` |

</details>

### public class `LootboxShopPriceData`  
`TypeDefIndex 3673`

| offset | field |
|---|---|
| 0x10 | `public int price;` |
| 0x18 | `public string[] itemsWon;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B92EC | 0x2F60DB0 |  | `public void .ctor()` |

</details>

### public class `LootboxShopPurchaseData`  
`TypeDefIndex 3674`

| offset | field |
|---|---|
| 0x10 | `public string itemWon;` |
| 0x18 | `public int balance;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B92DC | 0x2F60DB8 |  | `public void .ctor()` |

</details>

### public class `LootboxShopPurchaseResponse`  
`TypeDefIndex 3675`

| offset | field |
|---|---|
| 0x10 | `public LootboxShopPurchaseData result;` |
| 0x18 | `public bool isSuccess;` |
| 0x20 | `public LootboxShopErrorData error;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B92E4 | 0x2F60DC0 |  | `public void .ctor()` |

</details>

### public class `LootboxShopResponse`  
`TypeDefIndex 3676`

| offset | field |
|---|---|
| 0x10 | `public LootboxShopPriceData result;` |
| 0x18 | `public bool isSuccess;` |
| 0x20 | `public LootboxShopErrorData error;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B92F4 | 0x2F60DC8 |  | `public void .ctor()` |

</details>

### public class `LootboxShopsConfig` : ScriptableObject  
`TypeDefIndex 3677`

| offset | field |
|---|---|
| - | `private const string ConfigPath = "Configs/LootboxShopsConfig";` |
| - | `private static string _remoteConfig;` |
| - | `private static bool _isEnabled;` |
| - | `private static LootboxShopsConfig _instance;` |
| - | `private LootboxShopModel[] <LootboxShops>k__BackingField;` |

Properties: `public LootboxShopModel[] LootboxShops { get; set; }`; `public static bool IsEnabled { get; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F60DD0 |  | `public LootboxShopModel[] get_LootboxShops()` |
| - | 0x2F60DD8 |  | `private void set_LootboxShops(LootboxShopModel[] value)` |
| - | 0x2F60DE0 |  | `public void dSH(string e)` |
| - | 0x2F60EB4 |  | `public static void dSi(string e)` |
| - | 0x2F60F30 |  | `public static void dSw(bool e)` |
| - | 0x2F60F90 |  | `public static bool get_IsEnabled()` |
| - | 0x2F60FE8 |  | `public static LootboxShopsConfig dSJ()` |
| - | 0x2F611A0 |  | `public static LootboxShopModel ActiveShop()` |
| - | 0x2F6129C |  | `public void .ctor()` |
| - | 0x2F612A4 |  | `private static void .cctor()` |

</details>

### public class `LootboxShopsConfigLoader` : qu  
`TypeDefIndex 3679`

| offset | field |
|---|---|
| 0x10 | `private float _003COtT_003Ek__BackingField;` |

Properties: `public string soQ { get; }`; `public float kaz { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B8974 | 0x2F612F0 | 4 | `public string get_soQ()` |
| 0x38B89C4 | 0x2F612F8 | 5 | `public float get_kaz()` |
| 0x38B89CC | 0x2F61300 |  | `private void set_kaz(float value)` |
| 0x38B89D4 | 0x2F61304 | 6 | `public UniTask<bool> FJC(CancellationToken e)` |
| 0x38B8AAC | 0x2F61310 |  | `public void .ctor()` |

</details>

### public class `LootboxShopScreen` : MonoBehaviour  
`TypeDefIndex 3683`

| offset | field |
|---|---|
| - | `private const int Oru = 20;` |
| - | `private ItemDatabase _itemDatabase;` |
| - | `private RectTransform _coinsPanel;` |
| - | `private Text _coinsCountText;` |
| - | `private Text _spinPriceText;` |
| - | `private RectTransform _spinPricePanel;` |
| - | `private RectTransform _loadingPanel;` |
| - | `private Image _previewItemImage;` |
| - | `private Text _timerText;` |
| - | `private Button _closeButton;` |
| - | `private Button _spinButton;` |
| - | `private LootboxShopItemView[] _lootboxShopItemViews;` |
| - | `private RectTransform _tipPanel;` |
| - | `private Button _tipButton;` |
| - | `private Text _rules;` |
| - | `private Text _descriptionHeaderText;` |
| - | `private Text _descriptionBodyText;` |
| - | `private Image _descriptionMainImage;` |
| - | `private Image _descriptionHeaderImage;` |
| - | `private RectTransform _confirmPanel;` |
| - | `private Button _confirmSpinCloseButton;` |
| - | `private Button _confirmSpinButton;` |
| - | `private RectTransform _againPanel;` |
| - | `private Image _againSpinImage;` |
| - | `private Text _againSpinPriceText;` |
| - | `private Button _againSpinCloseButton;` |
| - | `private Button _againSpinButton;` |
| - | `private GameObject _againPricePanel;` |
| - | `private Text _againButtonText;` |
| - | `private LootboxShopItemView Ork;` |
| - | `private LootboxShopModel Orq;` |
| - | `private aS Ors;` |
| - | `private int OrC;` |
| - | `private bool _busy;` |
| - | `private Tween _spinTween;` |
| - | `private float[] _baseScale;` |
| - | `private RectTransform _previewGroup;` |
| - | `private float _previewScale;` |
| - | `private bool _bound;` |
| - | `private float _timerAt;` |
| - | `private readonly HashSet<string> _won;` |

Properties: `private ItemModel[] Items { get; }`; `private static cM Store { get; }`

<details><summary>methods (41)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F61320 |  | `private void dIu(cM e, Uf f)` |
| - | 0x2F61324 |  | `public void dIk(LootboxShopModel e, aS f)` |
| - | 0x2F61C68 |  | `private ItemModel[] get_Items()` |
| - | 0x2F62400 |  | `private static cM get_Store()` |
| - | 0x2F61CD4 |  | `private bool Owned(ItemModel item)` |
| - | 0x2F62464 |  | `private void OnEnable()` |
| - | 0x2F626C8 |  | `private void OnDisable()` |
| - | 0x2F6246C |  | `private void Bind(bool on)` |
| - | 0x2F626D0 |  | `private static void Hook(Button button, UnityAction action, bool on)` |
| - | 0x2F62780 |  | `private void Update()` |
| - | 0x2F627C4 |  | `private void OnDestroy()` |
| - | 0x2F62800 |  | `private void dIO()` |
| - | 0x2F62310 |  | `private void dIt(Action<bool, int, string[], LootboxShopErrorData> done)` |
| - | 0x2F62874 |  | `private void dIz(bool ok, int price, string[] won, LootboxShopErrorData error)` |
| - | 0x2F62984 |  | `private void dIr(int price, LootboxShopErrorData error)` |
| - | 0x2F633AC |  | `private void dIq(string message)` |
| - | 0x2F62AEC |  | `private void ApplyClaimed()` |
| - | 0x2F62C70 |  | `private void RefreshPrice()` |
| - | 0x2F61E5C |  | `private void dIH()` |
| - | 0x2F61EE4 |  | `private void dIi()` |
| - | 0x2F61EE8 |  | `private void RefreshCoins()` |
| - | 0x2F61FE4 |  | `private void RefreshTimer()` |
| - | 0x2F61DB0 |  | `private void SetLoading(bool on)` |
| - | 0x2F62270 |  | `private static void SetPanel(RectTransform panel, bool on)` |
| - | 0x2F6352C |  | `private void dIC(LootboxShopItemView e)` |
| - | 0x2F62178 |  | `private void dIa(LootboxShopItemView e)` |
| - | 0x2F61954 |  | `private void FitPreview()` |
| - | 0x2F637B4 |  | `private void ShowPreview(Sprite sprite)` |
| - | 0x2F63918 |  | `private void ShowDescription(ItemModel item)` |
| - | 0x2F63B80 |  | `private void OpenConfirm()` |
| - | 0x2F63B98 |  | `private void CloseConfirm()` |
| - | 0x2F63BA4 |  | `private void CloseAgain()` |
| - | 0x2F63BB0 |  | `private void ToggleTip()` |
| - | 0x2F63C70 |  | `private void Spin()` |
| - | 0x2F63D38 |  | `private void dIT(string itemWon, int balance)` |
| - | 0x2F64338 |  | `private void SetLoadingFlag(bool on)` |
| - | 0x2F6164C |  | `private void FitGroups()` |
| - | 0x2F63530 |  | `private void ShowGroup(int index)` |
| - | 0x2F64044 |  | `private void dIN(string itemWon, int balance)` |
| - | 0x2F64344 |  | `public void .ctor()` |
| - | 0x2F643D8 |  | `private void <Spin>b__76_0(bool ok, string itemWon, int balance, LootboxShopErrorData error)` |

</details>

### public class `LootboxShopScreenModel`  
`TypeDefIndex 3684`

| offset | field |
|---|---|
| - | `private AssetReference <Prefab>k__BackingField;` |
| - | `private ItemModel[] <Items>k__BackingField;` |
| - | `public GameObject prefabObject;` |

Properties: `public AssetReference Prefab { get; set; }`; `public ItemModel[] Items { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F64650 |  | `public AssetReference get_Prefab()` |
| - | 0x2F64658 |  | `private void set_Prefab(AssetReference value)` |
| - | 0x2F64660 |  | `public ItemModel[] get_Items()` |
| - | 0x2F64668 |  | `private void set_Items(ItemModel[] value)` |
| - | 0x2F64670 |  | `public void .ctor()` |

</details>

### public class `LootboxShopsMenuManager` : MonoBehaviour, st  
`TypeDefIndex 3685`

| offset | field |
|---|---|
| - | `private RectTransform screensContent;` |
| - | `private aS Otz;` |
| - | `private LootboxShopScreen _screen;` |
| - | `private GameObject _popup;` |

Properties: `public int sxs { get; }`; `private Transform Parent { get; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F64678 |  | `public int get_sxs()` |
| - | 0x2F64680 |  | `private void dSy(aS.av e)` |
| - | 0x2F64684 |  | `private Transform get_Parent()` |
| - | 0x2F64834 |  | `public void Show()` |
| - | 0x2F5EEB8 |  | `public void dSz(LootboxShopModel e)` |
| - | 0x2F64BD8 |  | `public bool dLz()` |
| - | 0x2F64C8C |  | `public void AddBanner(RectTransform parent)` |
| - | 0x2F649D8 |  | `private static void Stretch(GameObject target)` |
| - | 0x2F64ECC |  | `public void .ctor()` |

</details>
