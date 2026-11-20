# namespace `Lean.Localization`  (19 types)

### public class `LeanLanguage`  
`TypeDefIndex 3230`

| offset | field |
|---|---|
| 0x10 | `private string name;` |
| 0x18 | `private List<string> cultures;` |

Properties: `public string sDv { get; set; }`; `public List<string> sDS { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39211F4 | 0x2ED1508 |  | `public string get_sDv()` |
| 0x39211EC | 0x2ED1510 |  | `public void set_sDv(string value)` |
| 0x39211FC | 0x2ED1514 |  | `public List<string> get_sDS()` |
| 0x3921280 | 0x2ED151C |  | `public void .ctor()` |

</details>

### public class `LeanLanguageCSV` : ib  
`TypeDefIndex 3233`

| offset | field |
|---|---|
| 0x28 | `public TextAsset Source;` |
| 0x30 | `public string Language;` |
| 0x38 | `public string Separator;` |
| 0x40 | `public string NewLine;` |
| 0x48 | `public string Comment;` |
| 0x50 | `public LeanLanguageCSV.iB Cache;` |
| 0x58 | `private List<LeanLanguageCSV.Entry> entries;` |
| 0x0 | `private static readonly char[] OiR;` |
| 0x8 | `private static Stack<LeanLanguageCSV.Entry> Oib;` |

Properties: `public List<LeanLanguageCSV.Entry> sDI { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3921288 | 0x2ED1524 |  | `public List<LeanLanguageCSV.Entry> get_sDI()` |
| 0x392130C | 0x2ED152C | 4 | `public override void cWP(string e, string f)` |
| 0x3921534 | 0x2ED1530 |  | `public void cWD()` |
| 0x3921628 | 0x2ED1534 |  | `public void cWn()` |
| 0x3922140 | 0x2ED1538 |  | `public void .ctor()` |

</details>

### public class `LeanLanguageNameAttribute` : PropertyAttribute  
`TypeDefIndex 3234`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39222FC | 0x2ED1548 |  | `public void .ctor()` |

</details>

### public class `LeanLocalization` : MonoBehaviour  
`TypeDefIndex 3236`

| offset | field |
|---|---|
| - | `public const string HelpUrlPrefix = "http://carloswilkes.github.io/Documentation/LeanLocalization#";` |
| - | `public const string ComponentPathPrefix = "Lean/Localization/Lean ";` |
| 0x0 | `public static List<LeanLocalization> Instances;` |
| 0x8 | `public static Dictionary<string, LeanToken> CurrentTokens;` |
| 0x10 | `public static Dictionary<string, LeanLanguage> CurrentLanguages;` |
| 0x18 | `public static Dictionary<string, LeanTranslation> CurrentTranslations;` |
| 0x20 | `public string DefaultLanguage;` |
| 0x28 | `public LeanLocalization.im DetectLanguage;` |
| 0x2C | `public bool SaveLanguage;` |
| 0x30 | `private List<LeanLanguage> languages;` |
| 0x38 | `private List<LeanPrefab> prefabs;` |
| 0x28 | `private static string Oix;` |
| 0x30 | `private static bool OiK;` |
| 0x38 | `private static Dictionary<string, LeanTranslation> OiG;` |

Properties: `public List<LeanLanguage> sDM { get; }`; `public List<LeanPrefab> sne { get; }`; `public static bool snf { get; }`; `public static string snF { get; set; }`

<details><summary>methods (41)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3922304 | 0x2ED1550 |  | `public List<LeanLanguage> get_sDM()` |
| 0x3922388 | 0x2ED1558 |  | `public List<LeanPrefab> get_sne()` |
| 0x392240C | 0x2ED1560 |  | `public static bool get_snf()` |
| 0x392267C | 0x2ED1568 |  | `public static string get_snF()` |
| 0x39224EC | 0x2ED1570 |  | `public static void set_snF(string value)` |
| 0x3920418 | 0x2ED1574 |  | `public static void add_Oil(Action value)` |
| 0x392058C | 0x2ED1578 |  | `public static void remove_Oil(Action value)` |
| 0x39226D4 | 0x2ED157C |  | `public static void cEe(string e, LeanToken f)` |
| 0x3921B18 | 0x2ED1580 |  | `public static LeanTranslation cEf(string e)` |
| 0x3922890 | 0x2ED1588 |  | `public void cEF()` |
| 0x39225E8 | 0x2ED158C |  | `private static void cEd()` |
| 0x39228E8 | 0x2ED1590 |  | `private static void cEc()` |
| 0x3922980 | 0x2ED1594 |  | `public void cEU(string e)` |
| 0x39229D4 | 0x2ED1598 |  | `public void cEY(int e)` |
| 0x3922AB0 | 0x2ED159C |  | `public bool cEW(string e)` |
| 0x3922ACC | 0x2ED15A4 |  | `public bool cEE(string e, ref LeanLanguage f)` |
| 0x3922BA0 | 0x2ED15AC |  | `public void cEA(Object e)` |
| 0x3922D60 | 0x2ED15B0 |  | `public LeanLanguage cEu(string e, string[] f)` |
| 0x3922F34 | 0x2ED15B8 |  | `public static LeanToken cEk(string e)` |
| 0x3923080 | 0x2ED15C0 |  | `public LeanToken cEO(string e)` |
| 0x392315C | 0x2ED15C8 |  | `public static void cEt(string e, string f, bool F = true)` |
| 0x39234B0 | 0x2ED15CC |  | `public static string cEr(string e, string f)` |
| 0x392356C | 0x2ED15D4 |  | `public static LeanPhrase cEN(string e)` |
| 0x39236B8 | 0x2ED15DC |  | `public LeanPhrase cEq(string e)` |
| 0x391FC74 | 0x2ED15E4 |  | `public static LeanTranslation cEs(string e)` |
| 0x3923794 | 0x2ED15EC |  | `public static string cEC(string e, string f, bool F = true)` |
| - | - |  | `public static e cEZ<e>(string e_p, e f)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x384D440 Offset: 0x3849440 VA: 0x384D440` |
| - | - |  | `\|-LeanLocalization.cEZ<object>` |
| - | - |  | `*/` |
| 0x3921DA0 | 0x2ED15F4 |  | `public static void cEj(bool e = true)` |
| 0x3923C4C | 0x2ED15F8 |  | `public static void cEa()` |
| 0x3923CA8 | 0x2ED15FC | 4 | `protected virtual void OnEnable()` |
| 0x3923FC0 | 0x2ED1600 | 5 | `protected virtual void OnDisable()` |
| 0x3924048 | 0x2ED1604 | 6 | `protected virtual void Update()` |
| 0x392393C | 0x2ED1608 |  | `private void cEQ()` |
| 0x3923D88 | 0x2ED160C |  | `private void cEH()` |
| 0x392411C | 0x2ED1610 |  | `private string cEi(string e)` |
| 0x3924254 | 0x2ED1618 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedAudioSource` : LeanLocalizedBehaviour  
`TypeDefIndex 3237`

| offset | field |
|---|---|
| 0x30 | `public AudioClip FallbackAudioClip;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x391F3EC | 0x2ED1620 | 8 | `public override void cWz(LeanTranslation e)` |
| 0x391F488 | 0x2ED1624 | 11 | `protected virtual void Awake()` |
| 0x391F548 | 0x2ED1628 |  | `public void .ctor()` |

</details>

### public abstract class `LeanLocalizedBehaviour` : MonoBehaviour, ih  
`TypeDefIndex 3238`

| offset | field |
|---|---|
| 0x20 | `private string translationName;` |
| 0x28 | `private HashSet<LeanToken> OiP;` |

Properties: `public string snd { get; set; }`

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39244EC | 0x2ED1638 |  | `public string get_snd()` |
| 0x3924430 | 0x2ED1640 |  | `public void set_snd(string value)` |
| 0x39244F4 | 0x2ED1644 | 5 | `public void cWB(LeanToken e)` |
| 0x39245F0 | 0x2ED1648 | 6 | `public void cWm(LeanToken e)` |
| 0x3924650 | 0x2ED164C | 7 | `public void cWR()` |
| - | - |  | `public abstract void cWz(LeanTranslation e);` |
| 0x3924480 | 0x2ED1650 | 4 | `public void cWb()` |
| 0x39247C8 | 0x2ED1654 | 9 | `protected virtual void OnEnable()` |
| 0x3924860 | 0x2ED1658 | 10 | `protected virtual void OnDisable()` |
| 0x391F550 | 0x2ED1630 |  | `protected void .ctor()` |

</details>

### public class `LeanLocalizedDropdown` : MonoBehaviour, ih  
`TypeDefIndex 3240`

| offset | field |
|---|---|
| 0x20 | `private List<LeanLocalizedDropdown.Option> options;` |
| 0x28 | `private HashSet<LeanToken> Oim;` |

Properties: `public List<LeanLocalizedDropdown.Option> sDp { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x391F558 | 0x2ED165C |  | `public List<LeanLocalizedDropdown.Option> get_sDp()` |
| 0x391F5DC | 0x2ED1664 | 5 | `public void cWB(LeanToken e)` |
| 0x391F6D8 | 0x2ED1668 | 6 | `public void cWm(LeanToken e)` |
| 0x391F738 | 0x2ED166C | 7 | `public void cWR()` |
| 0x391F910 | 0x2ED1670 | 4 | `public void cWb()` |
| 0x3920380 | 0x2ED1674 | 8 | `protected virtual void OnEnable()` |
| 0x39204F4 | 0x2ED1678 | 9 | `protected virtual void OnDisable()` |
| 0x3920668 | 0x2ED167C |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedImage` : LeanLocalizedBehaviour  
`TypeDefIndex 3241`

| offset | field |
|---|---|
| 0x30 | `public Sprite FallbackSprite;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3920678 | 0x2ED168C | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3920714 | 0x2ED1690 | 11 | `protected virtual void Awake()` |
| 0x39207CC | 0x2ED1694 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedRenderer` : LeanLocalizedBehaviour  
`TypeDefIndex 3242`

| offset | field |
|---|---|
| 0x30 | `public Material FallbackMaterial;` |
| 0x38 | `public int Index;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39207D4 | 0x2ED169C | 8 | `public override void cWz(LeanTranslation e)` |
| 0x392093C | 0x2ED16A0 | 11 | `protected virtual void Awake()` |
| 0x3920A18 | 0x2ED16A4 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedSpriteRenderer` : LeanLocalizedBehaviour  
`TypeDefIndex 3243`

| offset | field |
|---|---|
| 0x30 | `public Sprite FallbackSprite;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3920A20 | 0x2ED16AC | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3920ABC | 0x2ED16B0 | 11 | `protected virtual void Awake()` |
| 0x3920B7C | 0x2ED16B4 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedText` : LeanLocalizedBehaviour  
`TypeDefIndex 3244`

| offset | field |
|---|---|
| 0x30 | `public string FallbackText;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3920B84 | 0x2ED16BC | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3920CCC | 0x2ED16C0 | 11 | `protected virtual void Awake()` |
| 0x3920D5C | 0x2ED16C4 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedTextFont` : LeanLocalizedBehaviour  
`TypeDefIndex 3245`

| offset | field |
|---|---|
| 0x30 | `public Font FallbackFont;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3920D64 | 0x2ED16CC | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3920E00 | 0x2ED16D0 | 11 | `protected virtual void Awake()` |
| 0x3920EC0 | 0x2ED16D4 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedTextMesh` : LeanLocalizedBehaviour  
`TypeDefIndex 3246`

| offset | field |
|---|---|
| 0x30 | `public string FallbackText;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3920EC8 | 0x2ED16DC | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3920FF8 | 0x2ED16E0 | 11 | `protected virtual void Awake()` |
| 0x3921080 | 0x2ED16E4 |  | `public void .ctor()` |

</details>

### public class `LeanLocalizedTextMeshFont` : LeanLocalizedBehaviour  
`TypeDefIndex 3247`

| offset | field |
|---|---|
| 0x30 | `public Font FallbackFont;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3921088 | 0x2ED16EC | 8 | `public override void cWz(LeanTranslation e)` |
| 0x3921124 | 0x2ED16F0 | 11 | `protected virtual void Awake()` |
| 0x39211E4 | 0x2ED16F4 |  | `public void .ctor()` |

</details>

### public class `LeanPhrase` : ib  
`TypeDefIndex 3250`

| offset | field |
|---|---|
| 0x28 | `private LeanPhrase.iR data;` |
| 0x30 | `private List<LeanPhrase.Entry> entries;` |

Properties: `public LeanPhrase.iR snc { get; set; }`; `public List<LeanPhrase.Entry> snU { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3924900 | 0x2ED16FC |  | `public LeanPhrase.iR get_snc()` |
| 0x39248F8 | 0x2ED1704 |  | `public void set_snc(LeanPhrase.iR value)` |
| 0x3924908 | 0x2ED1708 |  | `public List<LeanPhrase.Entry> get_snU()` |
| 0x392498C | 0x2ED1710 |  | `public void cEo()` |
| 0x39249F8 | 0x2ED1714 | 4 | `public override void cWP(string e, string f)` |
| 0x3924B54 | 0x2ED1718 |  | `private void cEy(LeanTranslation e, LeanPhrase.Entry f, bool F)` |
| 0x3924BBC | 0x2ED171C |  | `private void cEz(LeanTranslation e, object f, bool F)` |
| 0x3924BFC | 0x2ED1720 |  | `public bool cEh(string e, ref LeanPhrase.Entry f)` |
| 0x3924CD0 | 0x2ED1728 |  | `public void cEB(string e)` |
| 0x3924DA0 | 0x2ED172C |  | `public LeanPhrase.Entry cEm(string e, string f, Object F)` |
| 0x3924F40 | 0x2ED1734 |  | `public void .ctor()` |

</details>

### public class `LeanPrefab`  
`TypeDefIndex 3251`

| offset | field |
|---|---|
| 0x10 | `public Object Root;` |
| 0x18 | `private List<ib> sources;` |
| 0x20 | `private int OiD;` |
| 0x24 | `private bool Oin;` |
| 0x0 | `private static List<ib> OiV;` |

Properties: `public List<ib> snY { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3924098 | 0x2ED1744 |  | `public List<ib> get_snY()` |
| 0x3924F98 | 0x2ED174C |  | `public bool cEb()` |
| 0x39252B8 | 0x2ED1754 |  | `private bool cEl()` |
| 0x3925154 | 0x2ED175C |  | `private void cEx(ib e)` |
| 0x392535C | 0x2ED1760 |  | `private void cEK(Transform e)` |
| 0x3922D58 | 0x2ED1764 |  | `public void .ctor()` |

</details>

### public class `LeanToken` : ib  
`TypeDefIndex 3252`

| offset | field |
|---|---|
| 0x28 | `private string value;` |
| 0x30 | `private HashSet<ih> Oip;` |
| 0x0 | `private static HashSet<ih> Oiv;` |

Properties: `public string snW { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39257B8 | 0x2ED176C |  | `public string get_snW()` |
| 0x3923244 | 0x2ED1774 |  | `public void set_snW(string value)` |
| 0x39257C0 | 0x2ED1778 |  | `public void cEV(float e)` |
| 0x39257F4 | 0x2ED177C |  | `public void cEg(string e)` |
| 0x39257F8 | 0x2ED1780 |  | `public void cEp(int e)` |
| 0x392582C | 0x2ED1784 |  | `public void cEv(ih e)` |
| 0x391F8B0 | 0x2ED1788 |  | `public void cES(ih e)` |
| 0x39258E8 | 0x2ED178C |  | `public void cEI()` |
| 0x3925AD4 | 0x2ED1790 | 4 | `public override void cWP(string e, string f)` |
| 0x3925B40 | 0x2ED1794 | 6 | `protected override void OnDisable()` |
| 0x3925B58 | 0x2ED1798 |  | `public void .ctor()` |

</details>

### public class `LeanTranslation`  
`TypeDefIndex 3254`

| offset | field |
|---|---|
| 0x10 | `private string name;` |
| 0x18 | `public object OiS;` |
| 0x20 | `public bool OiI;` |
| 0x28 | `private List<LeanTranslation.Entry> OiM;` |
| 0x0 | `private static bool Owe;` |
| 0x8 | `private static StringBuilder current;` |
| 0x10 | `private static StringBuilder Owf;` |
| 0x18 | `private static List<LeanToken> OwF;` |

Properties: `public string snE { get; }`; `public List<LeanTranslation.Entry> snA { get; }`

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3925C48 | 0x2ED17A0 |  | `public string get_snE()` |
| 0x3925C50 | 0x2ED17A8 |  | `public List<LeanTranslation.Entry> get_snA()` |
| 0x39227F4 | 0x2ED17B0 |  | `public void .ctor(string newName)` |
| 0x3921CB4 | 0x2ED17B8 |  | `public void cAf(string e, Object f)` |
| 0x39238B8 | 0x2ED17BC |  | `public void cAF()` |
| 0x3925C58 | 0x2ED17C0 |  | `public int cAd(string e)` |
| 0x391FD1C | 0x2ED17C8 |  | `public static string cAc(string e, string f, ih F)` |
| 0x3925D00 | 0x2ED17D0 |  | `private static bool cAU(string e, StringBuilder f)` |

</details>

### public class `LeanTranslationNameAttribute` : PropertyAttribute  
`TypeDefIndex 3255`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3925EB4 | 0x2ED17D8 |  | `public void .ctor()` |

</details>
