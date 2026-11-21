# VANTA — external чит для Oxide / HyperHug BR24

External Android-чит на базе дампа dump3. Два компонента:

- **overlay app** (`overlay/`) — обычное Android-приложение с двумя ролями:
  - Главный экран-инжектор: красивый дарк-UI, статус процесса, кнопка START/STOP, живая консоль.
  - Фоновый оверлей поверх игры: ESP (рамки/ники/HP/дистанция/snap-линии), aim-FOV, плавающее меню с чекбоксами и слайдерами.
- **helper .so** (`helper/`) — ptrace-инжектится в процесс игры **один раз** при старте. Внутри только читает структуры IL2CPP:
  `PlayerManager.clientPlayerList`, `Transform.get_position`, `PlayerVitals` → пишет позиции и HP в shared memory `/data/local/tmp/vanta_oxide_shm`.
  **Никаких записей в память игры, никаких хуков игровых функций** → серверные античит-детекторы (speedhack/flyhack violations, см. `PlayerManager.violationLevel`) слепы.

## Требования

- Root (Magisk ok), разрешён ptrace к соседним процессам (SELinux permissive или cheat-процесс с su).
- Android 7+ (minSdk 24), только arm64-v8a.

## Сборка

```
cd vanta-cheat/overlay
gradle wrapper --gradle-version 8.9
./gradlew :app:assembleRelease
```

Либо запустить workflow `Build VANTA overlay` в Actions — он собирает APK автоматически.

## Офсеты

Из `dump.cs` версии dump3 (HyperHug BR24, пакет `Oxide`):

| поле | смещение |
|---|---|
| `PlayerManager.worldCameraRoot` | `0xA8` |
| `PlayerManager.mouseLook` | `0xB0` (признак локалки) |
| `PlayerManager.vitals` | `0x108` |
| `PlayerManager.lastTickPosition` | `0x228` |
| `PlayerManager.clientPlayerList` (static) | field name |
| `GenericVitals.m_MaxHealth` | `0x88` |
| `aoN.Health` (Observable float) | `0x98` |
| `aoN.Velocity` | `0xB0` |
| `MouseLook.m_LookRoot` | `0x28` |

При обновлении игры сверять в `helper/src/main/cpp/offsets.h`.
