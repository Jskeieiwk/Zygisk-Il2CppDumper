# Cloud StandKnife v0.38 — передача проекта

## Состав архива

Исходники `src/`, `assets/`, `menu.html`, манифест, `build.sh`, тесты,
отчёты `analysis/`, шрифты с лицензиями, `loader.p12`, Node-манифесты.
В корне также находятся `dump.cs`, `script.json`, `libil2cpp.so` для игры 3.3.
APK, временная папка build, Node-модули и SDK в архив не включены.
Исполняемые `assets/inject-arm*` включены как реальные файлы, а не ссылки
на прежнюю рабочую папку.

## Ключи

`loader.p12` — существующий ключ подписи APK; alias `loader`, пароль
`cloud-magic-dev` (также указан в build.sh). Хранить архив и пароль закрыто.
Ключей Cloudflare и исходников сервера лицензий в этом проекте нет.

## Среда сборки

Linux x86_64, Bash, Node.js, npm, Python 3 (команда `python`), Java.
`npm ci` устанавливает версии из `package-lock.json`.
Android-инструменты, на которые ссылается build.sh, нужно установить:

- `tools/ecj.jar` — компилятор Eclipse ECJ с поддержкой Java 8.
- `tools/android-35/android.jar` — Android SDK Platform 35.
- `tools/android-15/aapt`, `zipalign`, `apksigner` — Android SDK Build Tools 35.
- `tools/android-15/lib/d8.jar`, `lib/apksigner.jar`.
- `tools/android-15/lib64/libc++.so` — библиотека из тех же Build Tools.

Имена локальных каталогов исторические: android-15 здесь содержит Build
Tools для Android 15, а не API 15. aapt, zipalign, apksigner должны быть исполняемыми.

```bash
npm ci
for test_file in tests/*.cjs; do node "$test_file" || exit 1; done
bash build.sh
```

Выход: `Cloud-StandKnife-root-v38-test.apk`. Для следующей версии обновить
AndroidManifest.xml, строки версии в src/MainActivity.java и LoaderService.java,
menu.html, имя APK в build.sh и analysis/feature-audit.json.

## Текущий статус

**v0.38** (`analysis/V038_RU.md`): автовалл без толщин (переключатели; насквозь только игроки и объекты с `BreakableObjectBase`,
значения в `WALL_RULES` измерены по дампу 3.3), `Hitbox All`, приоритет частей тела, `Multipoint Scale` %, `Hitchance` %,
`Auto Scope` с обучением бита прицела. 28 локальных тестов проходят, APK собран и подписан тем же ключом, **на телефоне не запускалась**.
Рабочий дамп (dump.cs, script.json, libil2cpp.so) лежит в `Cloud-project-v23.tar.gz.enc` релиза dump3; релизный `zusa99.zip` повреждён.

Состояние v0.37 ниже сохранено для истории.

Устройство пользователя: Xiaomi 22111317PG, Android 14, arm64, Magisk root,
SELinux Enforcing. Игра com.neshurick.standknife версии 3.3, Frida 17.26.3.
В тренировке пользователь сообщил о стабильных 120 FPS после v0.21.
В матчах v0.21/v0.22 на видеозаписях около 25–49 FPS и задержка ESP.
В телеметрии v0.22 canvasMs местами 57–143 мс в среднем, до 278 мс в пике.

v0.37 построена и подписана, локальные тесты прошли. **Результата теста v0.37 на телефоне пока нет.**
Найден источник фризов v0.28–v0.30: сканирование сцены (`FindObjectsOfType`) каждые 1.5 с для кругов эффектов, 45–306 мс
(`CLOUD:capture-slow … worldScanMs`). В v0.32 заменено хуком `GrenadeEffectController.Play`; результата на телефоне нет
(`analysis/V031_RU.md`, `analysis/V032_RU.md`). v0.32: добавлен хук окклюзии («Reveal Occluded»), см. V032_RU.md.
Измерения на телефоне есть для v0.27 (`analysis/V028_RU.md`): общая память работает, `cameraMs` 1.5–3.8, `gameFps` 43–65 в матче.
Не заявлять, что фризы устранены. Измерения на телефоне есть для v0.22 (`analysis/V024_RU.md`) и v0.24
(`analysis/V025_RU.md`): в матче 4–5 игроков `gameFps` 26–40, `cameraMs` 12–16, `canvasMs` 9–12.

## Что менялось

- v0.20: удалён перехват Activity.dispatchTouchEvent; касания берутся через
  Unity Input; кэш текста и оптимизация аватарок.
- v0.21: матричная проекция всех костей вместо экранного растягивания;
  текущие позиции игроков читаются на каждом кадре камеры, предсказание
  из старой выборки больше не используется при показе ESP. Позы костей
  остаются на частоте выборки сведений. Матрица сверяется с WorldToScreenPoint.
- v0.22: CanvasBatch.java выполняет пачки линий и подписей в ART;
  исправлен отбор crash-лога по PID. Одной пакетной передачи оказалось недостаточно.
- v0.23: CanvasBatch также является Android View. JS записывает готовый
  Picture в обработчике игровой камеры. Java onDraw показывает последний
  Picture без входа в JS, старые кадры не ставятся в очередь. Кадр очищается
  при сбросе сессии и не рисуется, если устарел более чем на 350 мс.

- v0.28: масштаб и исчезновение кругов молотова/дыма (`ParticleSystem.isPlaying`), настраиваемая задержка ESP
  (история кадров в Java, слово `W_DELAY`). См. `analysis/V028_RU.md`.
- v0.27: кадр через общую память (прямой `ByteBuffer`), чтение в Java на каждом vsync, ноль вызовов Java на кадр;
  при отказе — путь v0.26. См. `analysis/V027_RU.md`.
- v0.26: один вызов Java на кадр (`CanvasBatch.frame`), круги/прямоугольники/аватарки в пакете, Java сам проверяет
  геометрию поверхности, автоогонь только по прямой видимости (`fireState.clear`). См. `analysis/V026_RU.md`.
- v0.25: упакованный целочисленный кадр (`assets/frame-codec.js`), математика без аллокаций, `Force Shot` проходит правило
  стены, строки `CLOUD:auto-shot`. См. `analysis/V025_RU.md`.
- v0.24: запись кадра в Java двумя вызовами (`CanvasBatch.beginFrame/endFrame/abortFrame`,
  `assets/overlay-frame.js`), фазовая телеметрия (`captureMs`, `reprojectMs`, `lagAvgMs/lagMaxMs`,
  `CLOUD:runtime=`), кнопка запуска с V8 (`--runtime=v8`, только если инжектор его принимает).
  Подробно и с честными границами: `analysis/V024_RU.md`.

## Куда смотреть следующему ИИ

Начать с `analysis/V046_RU.md` (автоскоп с измеренным байтом, антиаим удалён, третье лицо), затем `analysis/V045_RU.md` (автоскоп: ожидание подтверждения клика, журнал выборок), затем `analysis/V044_RU.md` (третье лицо без рук первого лица), затем `analysis/V043_RU.md` (цена шага прицела по журналу v0.42, зонд скрытых игроков, телеметрия aimCasts), затем `analysis/V042_RU.md` (стоимость прицела, `aimMs`, ошибка `bool` в третьем лице), затем `analysis/V041_RU.md` (третье лицо с телом, вывод зонда AA), затем `analysis/V040_RU.md` (антиаим: движок готов, `senderRva` не измерен, зонд AA Probe), затем `analysis/V039_RU.md` (хуки вместо скана сцены, не собрано и не запускалось), затем `analysis/V038_RU.md`, затем `analysis/V037_RU.md`, затем `analysis/V036_RU.md`, затем `analysis/V035_RU.md`, затем `analysis/V034_RU.md`, затем `analysis/V033_RU.md`, затем `analysis/V032_RU.md`, затем `analysis/V030_RU.md`, `analysis/V029_RU.md`, `analysis/V028_RU.md`, `analysis/V027_RU.md`, `analysis/V026_RU.md`, `analysis/V025_RU.md`, `analysis/V024_RU.md`, `analysis/V023_RU.md`, `assets/overlay-frame.js`, `src/CanvasBatch.java`, `assets/module.js`,
`tests/native-picture.cjs`, `tests/compiled-canvas.cjs`, `tests/esp-frame-sync.cjs`.
`analysis/feature-audit.json` хранит состояние доступности пунктов меню;
не считать наличие переключателя доказательством работающей функции.

Строка `CLOUD:esp-renderer=native-picture` подтверждает выбор нового пути.
`CLOUD:native-picture` содержит время показа Java View.
`CLOUD:picture-frame-error` означает ошибку записи кадра.
`javascript-fallback` означает возврат к старому View.
В native-picture режиме canvasMs измеряет подготовку Picture и уже входит
в cameraMs: **не складывать эти показатели**. Это время CPU, не замер GPU.

Остаются непроверенными загрузка dex на устройстве, производительность
Picture, синхронизация отдельного Android View с Unity SurfaceView и реальный
FPS в матче. Подготовка Picture всё ещё использует JS и Java bridge.
Не добавлять новые обещания FPS без замеров на телефоне.

## Правила продолжения

Не выдумывать RVA, результаты запуска и успешные исправления. Адреса новых
методов сверять с приложенными dump.cs/script.json. Сохранять подпись APK
существующим ключом. Сначала воспроизвести/локализовать проблему, затем
изменить код, прогнать соответствующие проверки и собрать APK. Прямо
отмечать разницу между локальными тестами и проверкой на устройстве.

SHA256SUMS.txt содержит контрольные суммы всех файлов архива, кроме себя.

## Примечание о сборке v0.24

APK v0.24–v0.37 собран не штатным `build.sh`, а его копией для окружения без Android Build Tools:
`ecj` 3.38.0 (Maven Central), framework-jar API 34 (`org.robolectric:android-all:14-robolectric-10818077`),
`aapt`, `zipalign`, `apksigner` из apt и `dx --min-sdk-version=24` вместо `d8 --min-api 24`.
Лямбды в LoaderService/MainActivity для такого APK заменены анонимными классами (в v0.24 `dx` с лямбдами падал на
устройстве: `NoSuchMethodError LambdaMetafactory.metafactory`); dex 037. Исходники проекта остаются с лямбдами. Для штатной сборки по-прежнему использовать `build.sh` с `tools/`.
Подпись тем же `loader.p12`, alias `loader`.
