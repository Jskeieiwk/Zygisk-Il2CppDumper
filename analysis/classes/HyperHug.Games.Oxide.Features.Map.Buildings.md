# namespace `HyperHug.Games.Oxide.Features.Map.Buildings`  (9 types)

### public sealed class `BasicBuildingNetworkObjectSpawner` : aV  
`TypeDefIndex 3647`

| offset | field |
|---|---|
| 0x20 | `private GameObject prefabToSpawn;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B6DA4 | 0x2F5D474 | 4 | `public override IDisposable Spawn(out List<Object> result)` |
| 0x38B6FE4 | 0x2F5D494 | 5 | `public override void dSk(List<Object> e)` |
| 0x38B6FE8 | 0x2F5D498 |  | `public void .ctor()` |

</details>

### public class `BuildingDescription` : MonoBehaviour  
`TypeDefIndex 3648`

| offset | field |
|---|---|
| 0x20 | `private Transform networkObjectsRoot;` |
| 0x28 | `private BuildingNetworkObjectsDescription buildingNetworkObjectsDescription;` |
| - | `private Transform <TeleportPoint>k__BackingField;` |
| - | `private jB <BuildingType>k__BackingField;` |
| - | `private WA[] <SpawnGroupObjects>k__BackingField;` |
| - | `private Transform <Casino>k__BackingField;` |
| - | `private GameObject <KickArea>k__BackingField;` |
| - | `private bool <FixAnchoredPosition>k__BackingField;` |
| - | `private float <FixAnchoredPositionShift>k__BackingField;` |

Properties: `public Transform TeleportPoint { get; set; }`; `public jB BuildingType { get; set; }`; `public WA[] SpawnGroupObjects { get; set; }`; `public Transform Casino { get; set; }`; `public GameObject KickArea { get; set; }`; `public bool FixAnchoredPosition { get; set; }`; `public float FixAnchoredPositionShift { get; set; }`; `public List<NPCBase> Oti { get; }`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5D4A0 |  | `public Transform get_TeleportPoint()` |
| - | 0x2F5D4A8 |  | `private void set_TeleportPoint(Transform value)` |
| - | 0x2F5D4B0 |  | `public jB get_BuildingType()` |
| - | 0x2F5D4B8 |  | `private void set_BuildingType(jB value)` |
| - | 0x2F5D4C0 |  | `public WA[] get_SpawnGroupObjects()` |
| - | 0x2F5D4C8 |  | `private void set_SpawnGroupObjects(WA[] value)` |
| - | 0x2F5D4D0 |  | `public Transform get_Casino()` |
| - | 0x2F5D4D8 |  | `private void set_Casino(Transform value)` |
| - | 0x2F5D4E0 |  | `public GameObject get_KickArea()` |
| - | 0x2F5D4E8 |  | `private void set_KickArea(GameObject value)` |
| - | 0x2F5D4F0 |  | `public bool get_FixAnchoredPosition()` |
| - | 0x2F5D4F8 |  | `private void set_FixAnchoredPosition(bool value)` |
| - | 0x2F5D504 |  | `public float get_FixAnchoredPositionShift()` |
| - | 0x2F5D50C |  | `private void set_FixAnchoredPositionShift(float value)` |
| 0x38B706C | 0x2F5D514 |  | `public List<NPCBase> get_Oti()` |
| 0x38B7074 | 0x2F5D51C |  | `public void dSt()` |
| 0x38B7078 | 0x2F5D520 |  | `private void dSr()` |
| 0x38B707C | 0x2F5D524 |  | `public void .ctor()` |

</details>

### public class `BuildingNetworkObjectsDescription` : MonoBehaviour  
`TypeDefIndex 3649`

Properties: `public List<NPCBase> Otw { get; set; }`; `public List<aV> Spawners { get; set; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B7174 | 0x2F5D52C |  | `public List<NPCBase> get_Otw()` |
| 0x38B717C | 0x2F5D534 |  | `protected void set_Otw(List<NPCBase> value)` |
| 0x38B7184 | 0x2F5D538 |  | `public List<aV> get_Spawners()` |
| 0x38B718C | 0x2F5D540 |  | `private void set_Spawners(List<aV> value)` |
| 0x38B7194 | 0x2F5D544 |  | `public void .ctor()` |

</details>

### public class `BuildingsCollectionDesigned` : ag  
`TypeDefIndex 3650`

Properties: `public override List<BuildingDescription> Buildings { get; set; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B7224 | 0x2F5D54C | 4 | `public override List<BuildingDescription> get_Buildings()` |
| 0x38B722C | 0x2F5D554 | 5 | `protected override void set_Buildings(List<BuildingDescription> value)` |
| 0x38B7234 | 0x2F5D558 |  | `public void .ctor()` |

</details>

### public sealed class `BuildingsCollectionProcedural` : ag  
`TypeDefIndex 3652`

| offset | field |
|---|---|
| 0x20 | `private List<BuildingDescription> buildingPrefabs;` |
| - | `private List<BuildingDescription> <Buildings>k__BackingField;` |

Properties: `public override List<BuildingDescription> Buildings { get; set; }`

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F5D560 |  | `public override List<BuildingDescription> get_Buildings()` |
| - | 0x2F5D568 |  | `protected override void set_Buildings(List<BuildingDescription> value)` |
| 0x38B724C | 0x2F5D570 |  | `public void dSs(GameObject e)` |
| 0x38B74A0 | 0x2F5DC14 |  | `private BuildingDescription dSC(string e)` |
| 0x38B75A4 | 0x2F5DD0C |  | `private Vector3 dSZ(Vector3 e, BuildingDescription f)` |
| 0x38B783C | 0x2F5DED8 |  | `private void dSj(string e)` |
| 0x38B7894 | 0x2F5DEDC |  | `public void .ctor()` |

</details>

### public sealed class `NpcBuildingNetworkObjectSpawner` : aV  
`TypeDefIndex 3653`

| offset | field |
|---|---|
| 0x20 | `private BuildingNetworkObjectsDescription buildingDescription;` |
| 0x28 | `private AssetReference npcPrefabReference;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B791C | 0x2F5E030 | 4 | `public override IDisposable Spawn(out List<Object> result)` |
| 0x38B7C4C | 0x2F5E050 | 5 | `public override void dSk(List<Object> e)` |
| 0x38B7C50 | 0x2F5E054 |  | `public void .ctor()` |

</details>

### public sealed class `SeatAndTerminalBuildingNetworkObjectSpawner` : aV  
`TypeDefIndex 3654`

| offset | field |
|---|---|
| 0x20 | `private Transform seatTransform;` |
| 0x28 | `private Transform terminalTransform;` |
| 0x30 | `public Seat seatPrefab;` |
| 0x38 | `public LuckyWheelTerminal terminalPrefab;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B7C58 | 0x2F5E05C | 4 | `public override IDisposable Spawn(out List<Object> result)` |
| 0x38B7FC0 | 0x2F5E07C | 5 | `public override void dSk(List<Object> e)` |
| 0x38B7FC4 | 0x2F5E080 |  | `public void .ctor()` |

</details>

### public class `SeatBuildingNetworkObjectSpawner` : aV  
`TypeDefIndex 3655`

| offset | field |
|---|---|
| 0x20 | `private Transform seatTransform;` |
| 0x28 | `public Seat seatPrefab;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B7FCC | 0x2F5E088 | 4 | `public override IDisposable Spawn(out List<Object> result)` |
| 0x38B8204 | 0x2F5E0A8 | 5 | `public override void dSk(List<Object> e)` |
| 0x38B8208 | 0x2F5E0AC |  | `public void .ctor()` |

</details>

### public sealed class `WheelBuildingNetworkObjectSpawner` : aV  
`TypeDefIndex 3656`

| offset | field |
|---|---|
| 0x20 | `private Um prefabToSpawn;` |
| 0x28 | `private Um OtJ;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38B8210 | 0x2F5E0B4 | 4 | `public override IDisposable Spawn(out List<Object> result)` |
| 0x38B8464 | 0x2F5E0D4 | 5 | `public override void dSk(List<Object> e)` |
| 0x38B8660 | 0x2F5E0D8 |  | `public void .ctor()` |

</details>
