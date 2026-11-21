# VANTA — чит для Oxide Survival Island (`com.catsbit.oxidesurvivalisland` 1.20.12034)

Один self-extracting `vanta.sh`:
- встроен standalone **ptrace-инжектор** и **libvanta.so**
- скрипт спрашивает `Overlay 0/1`, стартует игру, инжектит
- внутри игры — ImGui-меню (red-dark как на референс-видео), ESP, aim

## Использование

```sh
# положить vanta.sh в /data/local/tmp (или любое writable)
chmod 777 vanta.sh
su -c sh vanta.sh
# ↳ Overlay 0/1: 1
# ↳ скрипт сам запустит игру и инжектнет чит
```

Watermark `@Cloud_Crack` плавает сверху экрана — тап откроет меню. Закрыть — зонтик слева-сверху меню.

## Структура

- `mod/injector/inject.cpp` — standalone ptrace-инжектор (aarch64)
- `mod/libvanta/` — чит-либа, инжектимая в процесс игры:
  - `entry.cpp` — точка входа `vanta_start()`
  - `gl_hook.cpp` / `plt_hook.cpp` — хук `eglSwapBuffers` через GOT в `libil2cpp.so`/`libunity.so`
  - `renderer.cpp` — ImGui + GL ES3 backend, red-dark тема
  - `menu.cpp` — вкладки Combat/Visuals/Utility/Player/Skins/Misc, pill-тогглы, слайдеры
  - `esp.cpp` — ESP через ImGui background draw list
  - `input.cpp` — тач через `/dev/input/event*` → ImGui
  - `aim.cpp` — aim через `/dev/uinput`
  - `game.cpp` — il2cpp API ридер `PlayerManager.clientPlayerList`
  - `state.cpp` — конфиг меню
- `mod/vanta.sh.in` — шаблон launcher
- `mod/pack.py` — сборка `vanta.sh` с base64-блобами
- `helper/src/main/cpp/il2cpp_api.*`, `offsets.h` — общие с модом

## Сборка

Через CI (`.github/workflows/build-vanta.yml`): пуш в бранч → собирает `vanta.sh` артефактом.

Локально:
```
cmake -S mod -B mod/build \
    -DCMAKE_TOOLCHAIN_FILE=$NDK/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a -DANDROID_PLATFORM=android-24 \
    -DCMAKE_BUILD_TYPE=Release -DANDROID_STL=c++_static
cmake --build mod/build
python3 mod/pack.py --template mod/vanta.sh.in \
    --inj mod/build/inject-arm64 --so mod/build/libvanta.so \
    --out mod/build/vanta.sh
```

## Офсеты (dump.cs @ dump3 release)

| поле | смещение | заметка |
|---|---|---|
| `PlayerManager.worldCameraRoot` | `0xA8` | Transform головы |
| `PlayerManager.mouseLook` | `0xB0` | признак локалки |
| `PlayerManager.vitals` | `0x108` | → EntityVitals |
| `PlayerManager.lastTickPosition` | `0x228` | резервная позиция |
| `PlayerManager.clientPlayerList` (static) | field name | main source |
| `GenericVitals.m_MaxHealth` | `0x88` | |
| `aoN.Health` (Observable float) | `0x98` → `0x18` | значение внутри обёртки |
| `MouseLook.m_LookRoot` | `0x28` | камера первого лица |

## Что чит делает / не делает

- **НЕ пишет** в память игры, **НЕ хукает** игровые методы. Только: read через il2cpp API + hook EGL swap + уинпут для aim.
- Серверные детекторы speedhack/flyhack (`violationLevel`, `speedhackDistance`, `flyhackInAirSeconds`) ничего не считают — мы не меняем позицию.
- `util_no_recoil`/`fast_loot`/`god_mode` в меню — заглушки, для них нужен внутриигровой hook (пока отключены как write-пути).
