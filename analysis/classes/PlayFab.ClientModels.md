# namespace `PlayFab.ClientModels`  (3 types)

### public class `ErrorItemDto`  
`TypeDefIndex 2738`

| offset | field |
|---|---|
| - | `private string <Code>k__BackingField;` |

Properties: `public string Code { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF12F0 |  | `public string get_Code()` |
| - | 0x2DF12F8 |  | `public void set_Code(string value)` |
| - | 0x2DF1300 |  | `public void .ctor()` |

</details>

### public class `ItemDto`  
`TypeDefIndex 2739`

| offset | field |
|---|---|
| - | `private string <Id>k__BackingField;` |
| - | `private int <Price>k__BackingField;` |

Properties: `public string Id { get; set; }`; `public int Price { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF1308 |  | `public string get_Id()` |
| - | 0x2DF1310 |  | `public void set_Id(string value)` |
| - | 0x2DF1318 |  | `public int get_Price()` |
| - | 0x2DF1320 |  | `public void set_Price(int value)` |
| - | 0x2DF1328 |  | `public void .ctor()` |

</details>

### public class `VirtualPurchaseItemResultDto`  
`TypeDefIndex 2740`

| offset | field |
|---|---|
| - | `private ErrorItemDto <Error>k__BackingField;` |
| - | `private bool <IsSuccess>k__BackingField;` |
| - | `private List<ItemDto> <Items>k__BackingField;` |
| - | `private int <Balance>k__BackingField;` |
| - | `private int <BalanceChange>k__BackingField;` |

Properties: `public ErrorItemDto Error { get; set; }`; `public bool IsSuccess { get; set; }`; `public List<ItemDto> Items { get; set; }`; `public int Balance { get; set; }`; `public int BalanceChange { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2DF1330 |  | `public ErrorItemDto get_Error()` |
| - | 0x2DF1338 |  | `public void set_Error(ErrorItemDto value)` |
| - | 0x2DF1340 |  | `public bool get_IsSuccess()` |
| - | 0x2DF1348 |  | `public void set_IsSuccess(bool value)` |
| - | 0x2DF1354 |  | `public List<ItemDto> get_Items()` |
| - | 0x2DF135C |  | `public void set_Items(List<ItemDto> value)` |
| - | 0x2DF1364 |  | `public int get_Balance()` |
| - | 0x2DF136C |  | `public void set_Balance(int value)` |
| - | 0x2DF1374 |  | `public int get_BalanceChange()` |
| - | 0x2DF137C |  | `public void set_BalanceChange(int value)` |
| - | 0x2DF1384 |  | `public void .ctor()` |

</details>
