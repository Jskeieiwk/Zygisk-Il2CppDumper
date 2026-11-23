# r15-undetect — что изменилось и что осталось

## Цель
Убрать литералы и файловые отпечатки, по которым автоматические сканеры (игровой
аналитик, пассивный logcat-наблюдатель, обход /proc/<pid>/maps и /data/.../code_cache/)
опознают сборку как чит. Все идентификаторы перегенерируются на каждой сборке.

## Что переименовано на уровне сборки
`pack.sh` при каждом запуске генерирует и подставляет:

| Что                                   | Было                                       | Стало                                   |
|---------------------------------------|--------------------------------------------|-----------------------------------------|
| logcat tag                            | `Oxide_Internal`                           | `BRAND_TAG` (3 случайные буквы)         |
| Java package                          | `com.cloudcrack.oxide`                     | `com.android.oemsupport.a<rand6>`       |
| InternalBridge / InternalEntry        | фиксированные имена классов                | случайные 5-символьные классы в staging |
| SharedPreferences key                 | `oxide_internal_12034`                     | `cfg_<rand6>`                           |
| JSON конфиг на SD                     | `Oxide_Internal_12034.json`                | `cfg_<rand6>.json`                      |
| .so / .dex / .ogg staging prefix      | `oxide_<pid>.so`                           | `libart<rand3>_<pid>.so`                |
| имя лоадера на диске (внутри tar)     | `oxide-loader`                             | `.ld<rand4>`                            |
| имена артефактов в tar                | `oxide12034.so/.dex`, `rust_headshot.ogg`  | `lib<rand6>.{so,dex,ogg}`               |
| workdir в /data/local/tmp             | `oxide12034.$$`                            | `.cache_<rand8>.$$`                     |
| имя .sh                               | `Oxide_12034_r15.sh`                       | `update_<rand5>.sh`                     |
| маркеры инъектор↔.so                  | `.ready`, `.stage`                         | `.r`, `.p`                              |

## Поверхностные правки кода

### `native/brand.h` (новый)
Все макросы для имён. По умолчанию — нейтральные плейсхолдеры (`aud`, `art_`,
`com.android.oemsupport`, …). `pack.sh` перезаписывает файл на каждой сборке.

### `native/injector.cpp`
- Все `std::printf`/`std::puts` трассы удалены (`Target PID`, `Remote call: …`,
  `Internal startup: …`, `Library loaded, handle=…`). Лоадер молчит при успехе,
  пишет только короткие коды в stderr при ошибках.
- Пути стэйджинга используют `BRAND_LIB_PREFIX` вместо хардкоженного `oxide_`.
- После успешного `dlopen` файл `.so` немедленно `unlink()` снимается с диска;
  в `/proc/<pid>/maps` он останется как `… (deleted)`, зато файл-сканер его уже
  не прочтёт. Имя всё равно рандомизировано, если скрипт удастся прочитать.
- Маркерные файлы `.stage`→`.p`, `.ready`→`.r`.
- Строка ошибки «A Oxide_Internal payload is already loaded» заменена на `already loaded; restart` + случайный префикс.

### `native/oxide_features.cpp`
- Все `__android_log_print(…,"Oxide_Internal",…)` → `BRAND_TAG` + короткие коды
  (`sig`, `h`, `ui`, `fr`, `w0`, `b:…`, `ri:…`, `rdy=…`, `th=…`, `bm`).
- `stage()` пишет `.p` вместо `.stage` и использует `BRAND_TAG`.
- Длинные английские/русские сообщения свёрнуты в двух-трёх-буквенные коды.

### `native/internal_ui.cpp`
- Все `"Oxide_Internal"` → `BRAND_TAG`.
- Полные имена Java классов заменены на `BRAND_CLASS_BRIDGE` / `BRAND_CLASS_ENTRY`
  из `brand.h`.
- Длинные неоднозначные ошибки заменены на опаковые метки (`b`, `e`, `att`, `vm`, `dex`, `ui`).

### `launcher.sh.in`
- Все пользовательские строки (`Oxide 12034 r15 TEST`, «Перезапускаю Oxide…»,
  «Запрашиваю root-доступ…», «Oxide is not installed», «Oxide Internal failed»)
  сведены к коротким опаковым (`stop`, `mk`, `nostart`, `nopkg`, `inj`, `abi`,
  `root required`).
- Logcat-дамп на отказ отключён (прежняя версия писала `Oxide_r15_startup.txt` в
  `/sdcard/Download` — артефакт на диске). Теперь только нулевой exit-код.
- Токены `@PKG@`, `@SLUG@`, `@LOADER@`, `@LIBNAME@` подставляются `pack.sh`.

### `build.sh`
Флаги закалки для обоих бинарей:
- `-fvisibility=hidden -fvisibility-inlines-hidden` — внутренние символы не экспортируются.
- `-ffunction-sections -fdata-sections` + `-Wl,--gc-sections` — мёртвые секции выбрасываются.
- `-fno-ident` + линковка с `-Wl,--build-id=none,-s` — компиляторная подпись стирается.
- `-fomit-frame-pointer -DNDEBUG` — вырезает отладочные строки `assert`.
- `-z,noexecstack,-z,relro,-z,now` — стандартная ELF-защита.
- `--exclude-libs,ALL` — ни один статический символ не экспортируется из `.so`.
- Финальный `llvm-strip --strip-all --remove-section=.comment --remove-section=.note`.

### `pack.sh`
Полностью переписан. На каждом прогоне:
1. Генерирует токены (`BUILD_TAG`, `BUILD_PKG`, `BUILD_LIBNAME`, `BUILD_LOADER`, …).
2. Пишет `native/brand.h`.
3. Копирует Java в `build/java-staging/<pkg>/`, переименовывает классы
   `InternalBridge`/`InternalEntry` на 5-символьные, подставляет новые
   `BRAND_PREFS`, `BRAND_TAG` в литералы Java.
4. Запускает `build.sh` с `JAVA_SOURCE_DIR=build/java-staging`.
5. Переименовывает выходы под рандомные имена, стрипает, пакует в tar.
6. Подставляет токены в `launcher.sh.in` и base64-прикладывает payload.
7. Прогоняет `--verify`.

## Что НЕ изменилось (и что это значит)

### Managed IL2CPP class names
`api.class_from_name(game, "Oxide", "FPHitscan")` и подобные остаются в `.so`.
Их нельзя убрать без рантайм-декодирования, потому что они — буквальные имена
классов внутри игры. Эти строки встречаются и в самой `libil2cpp.so` игры, так
что они не отличают наш модуль от содержимого игрового процесса. **Но** `strings
lib<rand6>.so | grep Oxide` всё равно даст совпадения. Если это критично —
добавим XOR-инициализацию строк в отдельной итерации; скажи.

### `com.catsbit.oxidesurvivalisland`
Имя пакета игры остаётся в `launcher.sh` (передаётся лоадеру аргументом) и в
tar’овой записи `.sh` после base64. Это неизбежно — лоадеру надо знать, какой
процесс искать. Передавать через переменную окружения ничего не даст —
статически строка всё равно нужна.

### Dobby inline hooks
`DobbyHook` остаётся. Инлайн-хук переписывает первые 4–16 байт целевой функции
в `libil2cpp.so` и спавнит trampoline-страницу RW+RX вне игрового PT_LOAD. Если
античит начнёт CRC-считать свой `.text` или сканировать неузнаваемые
исполняемые страницы — поймает. Для текущего Catsbit Oxide этого поведения
пока не было. Обходной путь — миграция на патч `MethodInfo.methodPointer` (чисто
данные, без модификации `.text`); отдельная задача.

### ptrace-атач
Пока лоадер прикреплён к процессу, `/proc/<pid>/status` показывает `TracerPid`
≠ 0. Атач длится ~1–2 секунды. Если игра читает `TracerPid` в цикле сразу после
рестарта — поймает. Смягчение: вручную занулять `task_struct::ptracer` через
`/proc/<pid>/attr/current` требует seLinux-режима; не делаем.

### restorecon
Внешний `fork+exec` на `/system/bin/restorecon` остаётся — без него SO не
примет текущая SELinux-политика. Виден в `/proc` только в момент запуска
лоадера, вне контекста игры.

## Остаточные риски и следующие шаги
1. **IL2CPP class name strings** — обфусцировать XOR-at-init для всех
   `class_from_name`/`namespace` литералов (получится чище под `strings -a`).
2. **Dobby → MethodInfo pointer swap** для `PlayerManager.LateUpdate`,
   `AudioSource.PlayOneShot`, `CrosshairManager.Update`. Убирает модификацию
   `.text`. Нужны точные оффсеты MethodInfo в текущем Build ID.
3. **Memfd dlopen** вместо файлового стэйджинга. Android 11+ (API30+) поддерживает
   `dlopen("/proc/self/fd/N", …)`. Полный отказ от `/code_cache/`.
4. **Logcat-тэги-двойники** — `audioserver`, `zygote` и т.п. Делает поток
   логов нечитаемым для grep’а по нашим тэгам, но может сломать штатные
   фильтры. Рискованно.
5. **Java UI strings** — пользовательские заголовки меню (`Oxide 12034`,
   «Модули Oxide») по-прежнему в DEX. Для DEX, лежащего в `code_cache/`,
   это видно сканнеру файловой системы. Переименовать на нейтральные
   (`Overlay`, `Modules`) по вкусу.

## Сборка

```
cd project
bash pack.sh
```

На выходе: `dist/update_<rand5>.sh`. При каждом вызове `pack.sh` имена
меняются; никакой шаг не захардкожен.

Проверка контента: `sh dist/update_<rand5>.sh --verify` распакует tar в
`$TMPDIR` без запуска injectора.

Если нужно зафиксировать имена между сборками для скрипта раздачи —
переменные окружения:

```
BUILD_TAG=bgs BUILD_SLUG=1a2b3c4d BUILD_PKG=com.android.oemsupport.a000001 \
BUILD_LIB_PREFIX=libart123_ BUILD_PREFS=cfg_abcdef BUILD_LIBNAME=libmyname \
BUILD_LOADER=.ld0001 BUILD_SCRIPT=u.sh bash pack.sh
```
