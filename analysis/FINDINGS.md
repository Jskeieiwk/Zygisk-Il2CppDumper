# Oxide Revolution — выводы по dump.cs

Статус: всё ниже **извлечено из твоего dump.cs**; в игре и против libil2cpp.so не проверялось. Предположения помечены как «предположение».

## 1. Две проблемы дампа, которые надо знать до любого кода
1. **Два конфликтующих набора RVA.** У каждого из 34 275 методов с `[Address(RVA=…)]` значение в атрибуте отличается от `// RVA:` в комментарии (пример `GenericVitals.Awake`: атрибут `0x39DD988`, комментарий `0x2E1FE1C`). Какой набор настоящий, по дампу определить нельзя. Проверка: открыть `libil2cpp.so` из APK и посмотреть, лежит ли в обоих адресах начало функции (пролог `stp`/`sub sp`) и совпадает ли с `Awake`. Пока не проверено — **ни один RVA из этого дампа использовать нельзя**.
2. **Поля в комментариях `// 0x7FFFFFFF` — заглушка.** Реальные смещения только в `[FieldOffset(Offset="0x..")]` (в отчёте это колонка offset). У статических полей `0x0/0x8` — это смещение внутри static-блока класса, а не в экземпляре; у полей без атрибута смещение неизвестно (`-`).

## 2. Обфускация
Из ~3600 типов в глобальном неймспейсе 1872 имеют имя из 1–3 символов (`Xb`, `vd`, `XU`, `Lc<T>`), у многих полей и методов имена вида `OmR`, `cik`, `Fuk`. Читаемы типы в `Oxide.*` и `HyperHug.*`, а также поля, помеченные `[SerializeField]` (их имена хранит сериализация Unity). Следствие: **поиск по имени через il2cpp_* для обфусцированных членов не переживёт обновление** (имена, скорее всего, меняются каждый билд — предположение, проверить по второй версии APK). Опираться надо на читаемые имена и на структуру (смещения, цепочки ссылок), с валидацией при старте.

## 3. Сеть
В `PlayerManager` есть `_Mirror_SyncVarHookDelegate_userID/teamName/vehicleID/seatID`, в образах есть Mirror, kcp2k, SimpleWebTransport, PlayFab. Это сетевая игра на Mirror; сервер авторитетен для здоровья, предметов и урона, скорее всего (предположение). Что реально работает на клиенте, определяется только тестом на твоём билде. Это влияет на выбор функций.

## 4. Карта геймплейных классов (смещения из `[FieldOffset]`)
Базовый класс игрока/компонентов `vd` — обфусцирован, его поля в этой карте не показаны (смещения ниже 0x68 принадлежат ему).

**`Oxide.PlayerManager : vd`** (TypeDefIndex 2879) — корневой объект локального/удалённых игроков.
`kcc` 0x68 · `mouseLook` 0x78 · `playerDeathHandler` 0x88 · `raycastManager` 0x90 · `fpManager` 0x98 · `inventory` 0xA0 · `vitals` 0xB8 · `equipment` 0xD8 · `weapon` 0xE0 (PlayerWeapon) · `team` 0x110 · `cameraManager` 0x118 · `characterModel` 0x140 · `animator` 0x168 · `weapons` 0x170 (FPWeaponBase[]) · `lookAngle` 0x184 · `vehicleID` 0x1C8 · `seatID` 0x1CC.
Статические: `EnabledInstances` (internal static HashSet<PlayerManager>), `activePlayerList`, `sleepingPlayerList` (UT<PlayerManager>) — кандидаты на список игроков (предположение, тип `UT<>` обфусцирован, надо смотреть его структуру).

**Здоровье:** `GenericVitals : XU` (idx 2817) `m_MaxHealth` 0x88, `m_Hitboxes` 0x98, `m_DamageMultipliers` 0xA0 → `EntityVitals` (idx 2765) `m_MinFallSpeed` 0xB0, `m_MaxFallSpeed` 0xB4 → `PlayerVitals` (idx 2885): `Player` 0xE0, `m_HealthRegeneration` 0xF0, `m_ThirstDepletion` 0xF8, `m_HungerDepletion` 0x100, `m_Temperature` 0x108, `m_RadiationLevel` 0x10C, `m_RadiationPoison` 0x110. **Текущее здоровье среди читаемых полей не найдено** — оно лежит в обфусцированном поле (`OmQ` 0xA8 / `OmH` 0xAC в GenericVitals — предположение, только по соседству с `m_MaxHealth`) либо в базе `XU`. Нужен эксперимент (ReClass / изменение HP в игре).

**Оружие:** `FPWeaponBase : FPObject` (idx 2809) → `FPHitscan` (idx 2782: `config` 0xC8 HitscanWeaponConfig, `m_FireMode` 0xD0, `m_Mask` 0xD4, `m_FireDuration` 0xD8, `m_BurstLength` 0xDC, `m_BurstDuration` 0xE0, `m_BurstPause` 0xE4), также `FPBow`, `FPMelee`, `FPRocketLauncher`, `FPSpear`, `FPExplosiveCharge`, `FPTool`, `FPTorch`, `FPBuildingHammer`. Патроны/магазин в читаемых полях не видны — искать в `HitscanWeaponConfig` и в обфусцированных полях `Item`/`PlayerWeapon`.

**Инвентарь:** `PlayerInventory` (idx 2873) `player` 0x68, `hotbarIndex` 0x98, `m_InventorySize` 0x9C, `m_HotbarSize` 0xA0, `hotbar` 0xC8. `Item` (idx 2825) `m_Amount` 0x34, `m_CurrentPropertyValues` 0x38. Данные предмета — `ItemData : ScriptableObject`, база — `ItemDatabase`.

**Движение:** `CustomCharacterController : BaseFirstPersonController` (idx 2760) `_walkSpeed` 0x14C, `_runSpeed` 0x150, `_collider` 0x158, `state` 0x160. Смерть: `PlayerDeathHandler` `death` (bool) 0xD8.

**Добыча/мир:** `MineableObject/Tree/Stone/Animal`, `LootObject`, `LootDestroyable`, `ItemPickup`, `Cupboard`, `Recycler`, `SmeltingStation`, `GunTrap`, `AnimalVitals`, `CannibalSpawner`; сборка — `Oxide.Building*`; карта — `HyperHug.Games.Oxide.Features.Map.*`; транспорт — `HyperHug.Games.Oxide.Features.Transport` (33 типа), `VehicleManager`, `Seat`.

## 5. Чего в дампе нет (unknown)
Базовые классы `vd`, `XU`, `Xb`, `XY`; текущее здоровье; патроны; камера/матрица для ESP (`FPCameraController : Lc<…>`, `cameraManager` — надо смотреть структуру); Unity-версия; версия билда; какой RVA-набор настоящий.

## 6. Следующий шаг
Скачать из APK (release dump3, `@OxideRevolution.apk`, 1.2 ГБ) `libil2cpp.so` и `global-metadata.dat`, проверить пролог функций по обоим RVA-наборам и версию метаданных. Это даст рабочие адреса и ответ по обфускации. После этого и после выбора функций (God mode / патроны / скорость / ESP …) можно писать модуль.
