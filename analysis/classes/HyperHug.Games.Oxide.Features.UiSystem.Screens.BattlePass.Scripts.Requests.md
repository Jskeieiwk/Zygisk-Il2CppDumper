# namespace `HyperHug.Games.Oxide.Features.UiSystem.Screens.BattlePass.Scripts.Requests`  (6 types)

### public class `BattlePassConfig`  
`TypeDefIndex 3408`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public string battlePassId;` |
| 0x20 | `public DateTime start;` |
| 0x28 | `public DateTime end;` |
| 0x30 | `public int price;` |
| 0x34 | `public int plusPrice;` |
| 0x38 | `public int levelPrice;` |
| 0x3C | `public int levelPackPrice;` |
| 0x40 | `public int levelsInPack;` |
| 0x44 | `public int boughtLevelLimit;` |
| 0x48 | `public int experienceIncrement;` |
| 0x4C | `public int levelCount;` |
| 0x50 | `public int discountPlusPrice;` |
| 0x54 | `public int discountLevelPackPrice;` |
| 0x58 | `public List<ConfigMission> missions;` |
| 0x60 | `public Dictionary<int, List<RewardEntry>> freeRewards;` |
| 0x68 | `public Dictionary<int, List<RewardEntry>> paidRewards;` |
| 0x70 | `public List<RewardEntry> RepeatableRewards;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38F9460 | 0x2F0EB34 |  | `public void .ctor()` |

</details>

### public enum `BattlePassType`  
`TypeDefIndex 3409`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const BattlePassType Free = 0;` |
| - | `public const BattlePassType Paid = 1;` |
| - | `public const BattlePassType PaidPlus = 2;` |

### public class `ClientBattlePassProgress`  
`TypeDefIndex 3410`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public int level;` |
| 0x1C | `public int experience;` |
| 0x20 | `public int levelPacksBought;` |
| 0x24 | `public BattlePassType type;` |
| 0x28 | `public int paidRewardLevel;` |
| 0x2C | `public int freeRewardLevel;` |
| 0x30 | `public List<Mission> dailyMissions;` |
| 0x38 | `public List<Mission> weeklyMissions;` |
| 0x40 | `public Dictionary<int, List<Mission>> weeklyMissionByWeek;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38F9468 | 0x2F0EB3C |  | `public void .ctor()` |

</details>

### public class `ConfigMission`  
`TypeDefIndex 3411`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public int experience;` |
| 0x1C | `public Hl duration;` |
| 0x20 | `public DateTime start;` |
| 0x28 | `public DateTime end;` |
| 0x30 | `public double target;` |
| 0x38 | `public int week;` |
| 0x3C | `public bool isPremium;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38F9478 | 0x2F0EB44 |  | `public void .ctor()` |

</details>

### public class `Mission`  
`TypeDefIndex 3412`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public double progress;` |
| 0x20 | `public bool isClaimed;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38F9470 | 0x2F0EB4C |  | `public void .ctor()` |

</details>

### public class `RewardEntry`  
`TypeDefIndex 3413`

| offset | field |
|---|---|
| 0x10 | `public string id;` |
| 0x18 | `public int count;` |
| 0x1C | `public HG type;` |
| 0x20 | `public bool isHighlighted;` |
| 0x24 | `public iQ rarity;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38F9480 | 0x2F0EB54 |  | `public void .ctor()` |

</details>
