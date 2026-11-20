# namespace `HyperHug.Games.Oxide.Features.ServerAnalytics.ServerPlayersAnalytics`  (2 types)

### public class `PlayerAnalyticsModel`  
`TypeDefIndex 3570`

| offset | field |
|---|---|
| 0x10 | `public string playerId;` |
| 0x18 | `public float runDistance;` |

Properties: `public Nullable<int> playTime { get; set; }`; `public Nullable<int> lootBoxesOpened { get; set; }`; `public Nullable<int> casinoWins { get; set; }`; `public Nullable<int> headshots { get; set; }`; `public Dictionary<string, int> used { get; set; }`; `public Dictionary<string, int> quests { get; set; }`; `public Dictionary<string, int> crafted { get; set; }`; `public Dictionary<string, int> found { get; set; }`; `public Dictionary<string, int> breaked { get; set; }`; `public Dictionary<string, int> cooked { get; set; }`; `public Dictionary<string, int> killed { get; set; }`; `public Dictionary<string, int> killedPlayersWithWeapon { get; set; }`; `public Dictionary<string, int> built { get; set; }`; `public Dictionary<string, float> damagedPlayersWithWeapon { get; set; }`; `public Dictionary<string, int> bought { get; set; }`; `public Dictionary<string, int> sKx { get; }`; `public Dictionary<string, int> sKK { get; }`; `public Dictionary<string, int> sKG { get; }`; `public Dictionary<string, int> sKP { get; }`; `public Dictionary<string, int> sKD { get; }`; `public Dictionary<string, int> sKn { get; }`; `public Dictionary<string, int> sKV { get; }`; `public Dictionary<string, int> sKg { get; }`; `public Dictionary<string, float> sKp { get; }`; `public Dictionary<string, int> sKv { get; }`

<details><summary>methods (41)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x383EEE8 | 0x2F4C358 |  | `public Nullable<int> get_playTime()` |
| 0x383EEF0 | 0x2F4C360 |  | `public void set_playTime(Nullable<int> value)` |
| 0x383EEF8 | 0x2F4C364 |  | `public Nullable<int> get_lootBoxesOpened()` |
| 0x383EF00 | 0x2F4C36C |  | `public void set_lootBoxesOpened(Nullable<int> value)` |
| 0x383EF08 | 0x2F4C370 |  | `public Nullable<int> get_casinoWins()` |
| 0x383EF10 | 0x2F4C378 |  | `public void set_casinoWins(Nullable<int> value)` |
| 0x383EF18 | 0x2F4C37C |  | `public Nullable<int> get_headshots()` |
| 0x383EF20 | 0x2F4C384 |  | `public void set_headshots(Nullable<int> value)` |
| 0x383EF28 | 0x2F4C388 |  | `public Dictionary<string, int> get_used()` |
| 0x383EF30 | 0x2F4C390 |  | `public void set_used(Dictionary<string, int> value)` |
| 0x383EF38 | 0x2F4C394 |  | `public Dictionary<string, int> get_quests()` |
| 0x383EF40 | 0x2F4C39C |  | `public void set_quests(Dictionary<string, int> value)` |
| 0x383EF48 | 0x2F4C3A0 |  | `public Dictionary<string, int> get_crafted()` |
| 0x383EF50 | 0x2F4C3A8 |  | `public void set_crafted(Dictionary<string, int> value)` |
| 0x383EF58 | 0x2F4C3AC |  | `public Dictionary<string, int> get_found()` |
| 0x383EF60 | 0x2F4C3B4 |  | `public void set_found(Dictionary<string, int> value)` |
| 0x383EF68 | 0x2F4C3B8 |  | `public Dictionary<string, int> get_breaked()` |
| 0x383EF70 | 0x2F4C3C0 |  | `public void set_breaked(Dictionary<string, int> value)` |
| 0x383EF78 | 0x2F4C3C4 |  | `public Dictionary<string, int> get_cooked()` |
| 0x383EF80 | 0x2F4C3CC |  | `public void set_cooked(Dictionary<string, int> value)` |
| 0x383EF88 | 0x2F4C3D0 |  | `public Dictionary<string, int> get_killed()` |
| 0x383EF90 | 0x2F4C3D8 |  | `public void set_killed(Dictionary<string, int> value)` |
| 0x383EF98 | 0x2F4C3DC |  | `public Dictionary<string, int> get_killedPlayersWithWeapon()` |
| 0x383EFA0 | 0x2F4C3E4 |  | `public void set_killedPlayersWithWeapon(Dictionary<string, int> value)` |
| 0x383EFA8 | 0x2F4C3E8 |  | `public Dictionary<string, int> get_built()` |
| 0x383EFB0 | 0x2F4C3F0 |  | `public void set_built(Dictionary<string, int> value)` |
| 0x383EFB8 | 0x2F4C3F4 |  | `public Dictionary<string, float> get_damagedPlayersWithWeapon()` |
| 0x383EFC0 | 0x2F4C3FC |  | `public void set_damagedPlayersWithWeapon(Dictionary<string, float> value)` |
| 0x383EFC8 | 0x2F4C400 |  | `public Dictionary<string, int> get_bought()` |
| 0x383EFD0 | 0x2F4C408 |  | `public void set_bought(Dictionary<string, int> value)` |
| 0x383EA7C | 0x2F4C40C |  | `public Dictionary<string, int> get_sKx()` |
| 0x383E7E8 | 0x2F4C414 |  | `public Dictionary<string, int> get_sKK()` |
| 0x383E86C | 0x2F4C41C |  | `public Dictionary<string, int> get_sKG()` |
| 0x383E6E0 | 0x2F4C424 |  | `public Dictionary<string, int> get_sKP()` |
| 0x383E974 | 0x2F4C42C |  | `public Dictionary<string, int> get_sKD()` |
| 0x383E764 | 0x2F4C434 |  | `public Dictionary<string, int> get_sKn()` |
| 0x383EB00 | 0x2F4C43C |  | `public Dictionary<string, int> get_sKV()` |
| 0x383E9F8 | 0x2F4C444 |  | `public Dictionary<string, int> get_sKg()` |
| 0x383E8F0 | 0x2F4C44C |  | `public Dictionary<string, float> get_sKp()` |
| 0x383EB84 | 0x2F4C454 |  | `public Dictionary<string, int> get_sKv()` |
| 0x383E658 | 0x2F4C45C |  | `public void .ctor()` |

</details>

### public class `PlayersAnalyticsModelSend`  
`TypeDefIndex 3571`

| offset | field |
|---|---|
| 0x10 | `public string serverId;` |
| 0x18 | `public PlayerAnalyticsModel[] statistics;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x383EE58 | 0x2F4C464 |  | `public void .ctor()` |

</details>
