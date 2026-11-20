# namespace `HyperHug.Games.Oxide.Features.Store`  (9 types)

### public abstract class `BasicPurchasableUi` : MonoBehaviour  
`TypeDefIndex 3521`

| offset | field |
|---|---|
| 0x28 | `private GameObject[] loadings;` |
| 0x30 | `protected UiPurchaseButton[] uiPurchaseButtons;` |
| 0x38 | `private GameObject root;` |
| 0x40 | `private GameObject offerwallButton;` |
| - | `private Action<string> OFh;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F450C4 |  | `public void add_OFh(Action<string> value)` |
| - | 0x2F45174 |  | `public void remove_OFh(Action<string> value)` |
| 0x3824B98 | 0x2F45224 | 4 | `public virtual void dzG()` |
| 0x3824DB8 | 0x2F452E8 |  | `public void dzP()` |
| 0x3824F28 | 0x2F453A0 | 5 | `protected virtual void dzD(string e)` |
| 0x3824F44 | 0x2F453BC |  | `public void dzn(bool e)` |
| - | - |  | `public abstract bool dzV(CatalogItem e, Product[] f, List<CatalogItem> F, out bool d);` |
| 0x3824FAC | 0x2F45424 |  | `public void Show(bool inGame)` |
| 0x3825048 | 0x2F454C0 |  | `public void Hide()` |
| 0x3825068 | 0x2F454E0 |  | `protected void .ctor()` |

</details>

### public sealed class `CoinsPurchasableUi` : BasicPurchasableUi  
`TypeDefIndex 3524`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3825070 | 0x2F454E8 | 6 | `public override bool dzV(CatalogItem e, Product[] f, List<CatalogItem> F, out bool d)` |
| - | 0x2F45714 |  | `protected override void dzD(string e)` |
| 0x38252D0 | 0x2F4577C |  | `public void .ctor()` |

</details>

### public sealed class `InGameItemStoreMainUiMono` : Uf  
`TypeDefIndex 3526`

| offset | field |
|---|---|
| 0x28 | `private readonly Dictionary<Type, BasicPurchasableUi> OFm;` |
| 0x30 | `private BasicPurchasableUi[] basicPurchasableUis;` |
| 0x38 | `private cM OFR;` |
| 0x40 | `private ItemDatabase OFb;` |
| 0x48 | `private Qw OFl;` |
| 0x50 | `private Action<bool> OFx;` |

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3825438 | 0x2F4581C |  | `private void dhe(cM e, ItemDatabase f, QX.QJ F)` |
| 0x38254B0 | 0x2F4588C | 6 | `public override void FrK(bool e)` |
| 0x3825514 | 0x2F45980 |  | `private bool dhf(CatalogItem e, Product[] f, List<CatalogItem> F)` |
| - | - |  | `private e dhF<e>()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x382F464 Offset: 0x382B464 VA: 0x382F464` |
| - | - |  | `\|-InGameItemStoreMainUiMono.dhF<object>` |
| - | - |  | `*/` |
| 0x38255BC | 0x2F45ADC | 7 | `public override void FrG(Product[] e, List<CatalogItem> f, List<string> F)` |
| 0x3825BAC | 0x2F45C90 | 8 | `public override void FrP(List<string> e)` |
| 0x3825BB0 | 0x2F45C94 | 9 | `public override void FrD(List<string> e)` |
| 0x3825BB4 | 0x2F45C98 | 10 | `public override void Frn(string e)` |
| 0x3825BB8 | 0x2F45C9C | 11 | `public override void FrV(int e)` |
| 0x3825BBC | 0x2F45CA0 | 12 | `public override void Frg()` |
| 0x3825BC0 | 0x2F45CA4 | 13 | `public override void Frp(string e, StoreItemEntry f, int F)` |
| 0x3825BC4 | 0x2F45CA8 | 14 | `public override void Frv(string e, string f, string F, int d, bool c, Action<bool> U)` |
| 0x3825CB8 | 0x2F46034 | 15 | `public override void FrS(bool e, string f, int F)` |
| 0x3825CD0 | 0x2F4622C | 16 | `public override void ShowCoinsPopup()` |
| 0x3825D5C | 0x2F462F0 | 18 | `protected override void FNe()` |
| 0x3825F4C | 0x2F4603C |  | `private void dhd(bool e, string f, int F)` |
| 0x3826074 | 0x2F46560 | 17 | `protected override void FrM()` |
| 0x38261F8 | 0x2F467E8 |  | `private void dhc(string e)` |
| 0x3826228 | 0x2F46800 |  | `public void .ctor()` |
| 0x38262B0 | 0x2F46888 |  | `private void dhU(VirtualPurchaseItemResultDto e)` |
| 0x3826344 | 0x2F468E4 |  | `private void dhY(PlayFabError e)` |

</details>

### public sealed class `ItemStoreBannersUiMono` : sv  
`TypeDefIndex 3527`

| offset | field |
|---|---|
| 0x28 | `private UiOfferRowView[] offerRows;` |
| 0x30 | `private RectTransform listParent;` |
| 0x38 | `private LootboxShopsMenuManager lootboxShopsMenuManager;` |
| 0x40 | `private cM OFG;` |
| 0x48 | `private Zr OFP;` |
| 0x50 | `private readonly List<UiBannerView> OFD;` |
| - | `private float _nextBannerCheck;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3826680 | 0x2F469D4 |  | `private void dhu(cM e, Zr f)` |
| 0x38266B0 | 0x2F46A04 | 6 | `public override void dzv()` |
| - | 0x2F46B20 |  | `private void OnEnable()` |
| - | 0x2F46B28 |  | `private void Update()` |
| 0x38266B4 | 0x2F46A08 |  | `private void dhk()` |
| 0x38268FC | 0x2F46BF0 |  | `private void dhO(SpecialOfferBanner e)` |
| 0x3826924 | 0x2F46C18 | 7 | `public override void dzS()` |
| 0x3826AD0 | 0x2F46C1C | 9 | `protected override void dhA()` |
| 0x3826D34 | 0x2F46C20 |  | `public void .ctor()` |

</details>

### public class `ItemStoreInstaller` : ScriptableObjectInstaller  
`TypeDefIndex 3528`

| offset | field |
|---|---|
| 0x20 | `private ItemDatabase itemDatabase;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3826DBC | 0x2F46C28 | 6 | `public override void FSz()` |
| 0x3826EE8 | 0x2F46C2C |  | `public void .ctor()` |

</details>

### public sealed class `ItemStoreMainUiMono` : Uf  
`TypeDefIndex 3537`

| offset | field |
|---|---|
| - | `private const int OFv = 5;` |
| 0x28 | `private AboutYou aboutPlayer;` |
| 0x30 | `private GameObject[] loadings;` |
| 0x38 | `private RectTransform listParent;` |
| 0x40 | `private ItemDatabase itemDatabase;` |
| 0x48 | `private Text coinsBalance;` |
| 0x50 | `private GameObject newItemsTag;` |
| 0x58 | `private rm confirmPurchaseForCoins;` |
| 0x60 | `private GameObject discountTag;` |
| 0x68 | `private GameObject restoreButton;` |
| 0x70 | `private Button premiumButton;` |
| 0x78 | `private StoreItemEntry itemEntry;` |
| 0x80 | `private SubscriptionStoreItem subscriptionStoreItemPrefab;` |
| 0x88 | `private RectTransform rowEntry;` |
| 0x90 | `private BasicPurchasableUi[] basicPurchasableUis;` |
| 0x98 | `private cM OFS;` |
| 0xA0 | `private readonly List<StoreItemEntry> OFI;` |
| 0xA8 | `private RectTransform OFM;` |
| 0xB0 | `private int Ode;` |
| 0xB8 | `private readonly Dictionary<Type, BasicPurchasableUi> Odf;` |
| 0xC0 | `private Cw OdF;` |
| 0xC8 | `private Cw.Ci Odd;` |
| 0xD0 | `private Cs Odc;` |
| 0xD8 | `private QX.QJ OdU;` |
| 0xE0 | `private Qw OdY;` |
| 0xE8 | `private Action<bool> OdW;` |

<details><summary>methods (27)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3826EF0 | 0x2F46C34 |  | `private void dhZ(cM e, Ce f, Cw.Ci F, Cs d, QX.QJ c)` |
| 0x3827040 | 0x2F46D98 |  | `public void dhj()` |
| 0x3827098 | 0x2F46DDC | 6 | `public override void FrK(bool e)` |
| 0x3827150 | 0x2F46E8C |  | `private bool dha(CatalogItem e, Product[] f, List<CatalogItem> F, out bool d)` |
| 0x38271FC | 0x2F46F30 | 7 | `public override void FrG(Product[] e, List<CatalogItem> f, List<string> F)` |
| - | 0x2F48640 |  | `private void PrioritizeNewItems(List<CatalogItem> catalog)` |
| 0x38287D4 | 0x2F48414 |  | `private void dhQ(Transform e)` |
| 0x38288E4 | 0x2F48F18 | 8 | `public override void FrP(List<string> e)` |
| 0x38289C0 | 0x2F48FF4 | 9 | `public override void FrD(List<string> e)` |
| 0x3828D70 | 0x2F4939C | 10 | `public override void Frn(string e)` |
| 0x3828E78 | 0x2F494E8 | 11 | `public override void FrV(int e)` |
| 0x3828EC0 | 0x2F49530 | 12 | `public override void Frg()` |
| 0x3828ED0 | 0x2F49540 | 13 | `public override void Frp(string e, StoreItemEntry f, int F)` |
| 0x382907C | 0x2F496C8 | 14 | `public override void Frv(string e, string f, string F, int d, bool c, Action<bool> U)` |
| 0x3829170 | 0x2F498FC |  | `private void dhH(bool e, string f, int F)` |
| 0x38291D4 | 0x2F49960 | 15 | `public override void FrS(bool e, string f, int F)` |
| 0x382924C | 0x2F499D8 | 16 | `public override void ShowCoinsPopup()` |
| 0x38292D8 | 0x2F49AB0 | 17 | `protected override void FrM()` |
| - | - |  | `public e dhi<e>()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3845A18 Offset: 0x3841A18 VA: 0x3845A18` |
| - | - |  | `\|-ItemStoreMainUiMono.dhi<object>` |
| - | - |  | `*/` |
| 0x38295EC | 0x2F49C74 | 18 | `protected override void FNe()` |
| 0x38297CC | 0x2F49E70 |  | `private void dhw(string e)` |
| 0x38297FC | 0x2F49EA0 |  | `public void .ctor()` |

</details>

### public class `ItemStoreUiInstaller` : kX  
`TypeDefIndex 3538`

| offset | field |
|---|---|
| 0x30 | `private sv _bannersUiMono;` |
| 0x38 | `private Uf _itemStoreMainUiMono;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3829C88 | 0x2F4A82C | 8 | `public override void FSz()` |
| 0x3829D44 | 0x2F4A830 |  | `public void .ctor()` |

</details>

### public sealed class `StoreRowsFit` : MonoBehaviour  
`TypeDefIndex 3539`

| offset | field |
|---|---|
| - | `private float width;` |
| - | `private int count;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F4A838 |  | `private void LateUpdate()` |
| - | 0x2F4A970 |  | `private static void Fit(RectTransform list)` |
| - | 0x2F4AE50 |  | `public void .ctor()` |

</details>

### public class `UiPurchaseButton` : MonoBehaviour  
`TypeDefIndex 3540`

| offset | field |
|---|---|
| 0x28 | `private string id;` |
| 0x30 | `private Button button;` |
| 0x38 | `private Text price;` |
| - | `private Action<string> OdE;` |

Properties: `public string sxv { get; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3829D4C | 0x2F4AE64 |  | `public string get_sxv()` |
| - | 0x2F4AE6C |  | `public void add_OdE(Action<string> value)` |
| - | 0x2F4AF1C |  | `public void remove_OdE(Action<string> value)` |
| - | 0x2F4AFCC |  | `private void Awake()` |
| 0x3824C60 | 0x2F4B07C |  | `public void dhL()` |
| 0x38252AC | 0x2F4B124 |  | `public void dho(string e)` |
| - | 0x2F4B1E8 |  | `public void SetPriceAvailable(bool available)` |
| 0x3829D54 | 0x2F4B27C |  | `private void dhy()` |
| 0x3829D74 | 0x2F4B29C |  | `public void .ctor()` |

</details>
