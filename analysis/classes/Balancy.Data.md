# namespace `Balancy.Data`  (8 types)

### public class `BattlePassData`  
`TypeDefIndex 4034`

| offset | field |
|---|---|
| 0x10 | `public List<ClientBattlePassProgress> BattlePassProgress;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3909524 | 0x2F89DE0 |  | `public void .ctor()` |

</details>

### public class `DailyMissionsProgressData`  
`TypeDefIndex 4035`

| offset | field |
|---|---|
| 0x10 | `public List<string> ActiveMissions;` |
| 0x18 | `public int Day;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39095AC | 0x2F89DE8 |  | `public void .ctor()` |

</details>

### public class `EquippedItem`  
`TypeDefIndex 4036`

| offset | field |
|---|---|
| 0x10 | `public int Id;` |
| 0x14 | `public int Category;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3909634 | 0x2F89DF0 |  | `public void .ctor()` |

</details>

### public class `Inventory`  
`TypeDefIndex 4037`

| offset | field |
|---|---|
| 0x10 | `public List<EquippedItem> EquippedItems;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x390963C | 0x2F89DF8 |  | `public void .ctor()` |

</details>

### public class `OffersData`  
`TypeDefIndex 4038`

| offset | field |
|---|---|
| 0x10 | `private int offerIndex;` |

Properties: `public int OfferIndex { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39094FC | 0x2F89E00 |  | `public int get_OfferIndex()` |
| 0x3909504 | 0x2F89E08 |  | `public void set_OfferIndex(int value)` |
| 0x390950C | 0x2F89E0C |  | `public void .ctor()` |

</details>

### public class `PlayerData`  
`TypeDefIndex 4039`

| offset | field |
|---|---|
| 0x10 | `private OffersData offersData;` |

Properties: `public OffersData OffersData { get; }`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3909514 | 0x2F89E14 |  | `public OffersData get_OffersData()` |
| 0x390951C | 0x2F89E1C |  | `public void .ctor()` |

</details>

### public class `ProfileData`  
`TypeDefIndex 4040`

| offset | field |
|---|---|
| 0x10 | `public Inventory InventoryData;` |
| 0x18 | `public BattlePassData BattlePassData;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3909644 | 0x2F89E24 |  | `public void .ctor()` |

</details>

### public class `UserProgressData`  
`TypeDefIndex 4041`

| offset | field |
|---|---|
| 0x10 | `public int Experience;` |
| 0x14 | `public int Level;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39096EC | 0x2F89E2C |  | `public void .ctor()` |

</details>
