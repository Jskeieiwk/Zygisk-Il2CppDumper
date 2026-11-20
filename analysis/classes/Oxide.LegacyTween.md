# namespace `Oxide.LegacyTween`  (19 types)

### public class `LeanAudioStream`  
`TypeDefIndex 2949`

| offset | field |
|---|---|
| - | `public int position;` |
| - | `public AudioClip audioClip;` |
| - | `public float[] audioArr;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E44EB8 |  | `public void .ctor(float[] audioArr)` |
| - | 0x2E44EE8 |  | `public void OnAudioRead(float[] data)` |
| - | 0x2E44F54 |  | `public void OnAudioSetPosition(int newPosition)` |

</details>

### public class `LeanAudio`  
`TypeDefIndex 2950`

| offset | field |
|---|---|
| - | `public static float MIN_FREQEUNCY_PERIOD;` |
| - | `public static int PROCESSING_ITERATIONS_MAX;` |
| - | `public static float[] generatedWaveDistances;` |
| - | `public static int generatedWaveDistancesCount;` |
| - | `private static float[] longList;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E44F5C |  | `public static LeanAudioOptions options()` |
| - | 0x2E4509C |  | `public static LeanAudioStream createAudioStream(AnimationCurve volume, AnimationCurve frequency, LeanAudioOptions options)` |
| - | 0x2E4595C |  | `public static AudioClip createAudio(AnimationCurve volume, AnimationCurve frequency, LeanAudioOptions options)` |
| - | 0x2E45164 |  | `private static int createAudioWave(AnimationCurve volume, AnimationCurve frequency, LeanAudioOptions options)` |
| - | 0x2E4545C |  | `private static AudioClip createAudioFromWave(int waveLength, LeanAudioOptions options)` |
| - | 0x2E45A18 |  | `private static void OnAudioSetPosition(int newPosition)` |
| - | 0x2E45A1C |  | `public static AudioClip generateAudioFromCurve(AnimationCurve curve, int frequencyRate = 44100)` |
| - | 0x2E45B88 |  | `public static AudioSource play(AudioClip audio, float volume)` |
| - | 0x2E45D84 |  | `public static AudioSource play(AudioClip audio)` |
| - | 0x2E45E2C |  | `public static AudioSource play(AudioClip audio, Vector3 pos)` |
| - | 0x2E45EA8 |  | `public static AudioSource play(AudioClip audio, Vector3 pos, float volume)` |
| - | 0x2E45C54 |  | `public static AudioSource playClipAt(AudioClip clip, Vector3 pos)` |
| - | 0x2E45F58 |  | `public static void printOutAudioClip(AudioClip audioClip, ref AnimationCurve curve, float scaleX = 1)` |
| - | 0x2E460FC |  | `public void .ctor()` |
| - | 0x2E46104 |  | `private static void .cctor()` |

</details>

### public class `LeanAudioOptions`  
`TypeDefIndex 2952`

| offset | field |
|---|---|
| - | `public LeanAudioOptions.LeanAudioWaveStyle waveStyle;` |
| - | `public Vector3[] vibrato;` |
| - | `public Vector3[] modulation;` |
| - | `public int frequencyRate;` |
| - | `public float waveNoiseScale;` |
| - | `public float waveNoiseInfluence;` |
| - | `public bool useSetData;` |
| - | `public LeanAudioStream stream;` |

<details><summary>methods (10)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E45078 |  | `public void .ctor()` |
| - | 0x2E4615C |  | `public LeanAudioOptions setFrequency(int frequencyRate)` |
| - | 0x2E46164 |  | `public LeanAudioOptions setVibrato(Vector3[] vibrato)` |
| - | 0x2E46180 |  | `public LeanAudioOptions setWaveSine()` |
| - | 0x2E46188 |  | `public LeanAudioOptions setWaveSquare()` |
| - | 0x2E46194 |  | `public LeanAudioOptions setWaveSawtooth()` |
| - | 0x2E461A0 |  | `public LeanAudioOptions setWaveNoise()` |
| - | 0x2E461AC |  | `public LeanAudioOptions setWaveStyle(LeanAudioOptions.LeanAudioWaveStyle style)` |
| - | 0x2E461B4 |  | `public LeanAudioOptions setWaveNoiseScale(float waveScale)` |
| - | 0x2E461BC |  | `public LeanAudioOptions setWaveNoiseInfluence(float influence)` |

</details>

### public class `LeanSmooth`  
`TypeDefIndex 2953`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E461C4 |  | `public static float damp(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1)` |
| - | 0x2E462E0 |  | `public static Vector3 damp(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1)` |
| - | 0x2E4638C |  | `public static Color damp(Color current, Color target, ref Color currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1)` |
| - | 0x2E46464 |  | `public static float spring(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5)` |
| - | 0x2E46508 |  | `public static Vector3 spring(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5)` |
| - | 0x2E465D4 |  | `public static Color spring(Color current, Color target, ref Color currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5)` |
| - | 0x2E466D4 |  | `public static float linear(float current, float target, float moveSpeed, float deltaTime = -1)` |
| - | 0x2E46748 |  | `public static Vector3 linear(Vector3 current, Vector3 target, float moveSpeed, float deltaTime = -1)` |
| - | 0x2E46878 |  | `public static Color linear(Color current, Color target, float moveSpeed)` |
| - | 0x2E469CC |  | `public static float bounceOut(float current, float target, ref float currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5, float hitDamping = 0.9)` |
| - | 0x2E46AB0 |  | `public static Vector3 bounceOut(Vector3 current, Vector3 target, ref Vector3 currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5, float hitDamping = 0.9)` |
| - | 0x2E46B8C |  | `public static Color bounceOut(Color current, Color target, ref Color currentVelocity, float smoothTime, float maxSpeed = -1, float deltaTime = -1, float friction = 2, float accelRate = 0.5, float hitDamping = 0.9)` |
| - | 0x2E46CA0 |  | `public void .ctor()` |

</details>

### public enum `TweenAction`  
`TypeDefIndex 2954`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const TweenAction MOVE_X = 0;` |
| - | `public const TweenAction MOVE_Y = 1;` |
| - | `public const TweenAction MOVE_Z = 2;` |
| - | `public const TweenAction MOVE_LOCAL_X = 3;` |
| - | `public const TweenAction MOVE_LOCAL_Y = 4;` |
| - | `public const TweenAction MOVE_LOCAL_Z = 5;` |
| - | `public const TweenAction MOVE_CURVED = 6;` |
| - | `public const TweenAction MOVE_CURVED_LOCAL = 7;` |
| - | `public const TweenAction MOVE_SPLINE = 8;` |
| - | `public const TweenAction MOVE_SPLINE_LOCAL = 9;` |
| - | `public const TweenAction SCALE_X = 10;` |
| - | `public const TweenAction SCALE_Y = 11;` |
| - | `public const TweenAction SCALE_Z = 12;` |
| - | `public const TweenAction ROTATE_X = 13;` |
| - | `public const TweenAction ROTATE_Y = 14;` |
| - | `public const TweenAction ROTATE_Z = 15;` |
| - | `public const TweenAction ROTATE_AROUND = 16;` |
| - | `public const TweenAction ROTATE_AROUND_LOCAL = 17;` |
| - | `public const TweenAction CANVAS_ROTATEAROUND = 18;` |
| - | `public const TweenAction CANVAS_ROTATEAROUND_LOCAL = 19;` |
| - | `public const TweenAction CANVAS_PLAYSPRITE = 20;` |
| - | `public const TweenAction ALPHA = 21;` |
| - | `public const TweenAction TEXT_ALPHA = 22;` |
| - | `public const TweenAction CANVAS_ALPHA = 23;` |
| - | `public const TweenAction CANVASGROUP_ALPHA = 24;` |
| - | `public const TweenAction ALPHA_VERTEX = 25;` |
| - | `public const TweenAction COLOR = 26;` |
| - | `public const TweenAction CALLBACK_COLOR = 27;` |
| - | `public const TweenAction TEXT_COLOR = 28;` |
| - | `public const TweenAction CANVAS_COLOR = 29;` |
| - | `public const TweenAction CANVAS_MOVE_X = 30;` |
| - | `public const TweenAction CANVAS_MOVE_Y = 31;` |
| - | `public const TweenAction CANVAS_MOVE_Z = 32;` |
| - | `public const TweenAction CALLBACK = 33;` |
| - | `public const TweenAction MOVE = 34;` |
| - | `public const TweenAction MOVE_LOCAL = 35;` |
| - | `public const TweenAction MOVE_TO_TRANSFORM = 36;` |
| - | `public const TweenAction ROTATE = 37;` |
| - | `public const TweenAction ROTATE_LOCAL = 38;` |
| - | `public const TweenAction SCALE = 39;` |
| - | `public const TweenAction VALUE3 = 40;` |
| - | `public const TweenAction GUI_MOVE = 41;` |
| - | `public const TweenAction GUI_MOVE_MARGIN = 42;` |
| - | `public const TweenAction GUI_SCALE = 43;` |
| - | `public const TweenAction GUI_ALPHA = 44;` |
| - | `public const TweenAction GUI_ROTATE = 45;` |
| - | `public const TweenAction DELAYED_SOUND = 46;` |
| - | `public const TweenAction CANVAS_MOVE = 47;` |
| - | `public const TweenAction CANVAS_SCALE = 48;` |
| - | `public const TweenAction CANVAS_SIZEDELTA = 49;` |
| - | `public const TweenAction FOLLOW = 50;` |
| - | `public const TweenAction NONE = 51;` |

### public enum `LeanTweenType`  
`TypeDefIndex 2955`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LeanTweenType notUsed = 0;` |
| - | `public const LeanTweenType linear = 1;` |
| - | `public const LeanTweenType easeOutQuad = 2;` |
| - | `public const LeanTweenType easeInQuad = 3;` |
| - | `public const LeanTweenType easeInOutQuad = 4;` |
| - | `public const LeanTweenType easeInCubic = 5;` |
| - | `public const LeanTweenType easeOutCubic = 6;` |
| - | `public const LeanTweenType easeInOutCubic = 7;` |
| - | `public const LeanTweenType easeInQuart = 8;` |
| - | `public const LeanTweenType easeOutQuart = 9;` |
| - | `public const LeanTweenType easeInOutQuart = 10;` |
| - | `public const LeanTweenType easeInQuint = 11;` |
| - | `public const LeanTweenType easeOutQuint = 12;` |
| - | `public const LeanTweenType easeInOutQuint = 13;` |
| - | `public const LeanTweenType easeInSine = 14;` |
| - | `public const LeanTweenType easeOutSine = 15;` |
| - | `public const LeanTweenType easeInOutSine = 16;` |
| - | `public const LeanTweenType easeInExpo = 17;` |
| - | `public const LeanTweenType easeOutExpo = 18;` |
| - | `public const LeanTweenType easeInOutExpo = 19;` |
| - | `public const LeanTweenType easeInCirc = 20;` |
| - | `public const LeanTweenType easeOutCirc = 21;` |
| - | `public const LeanTweenType easeInOutCirc = 22;` |
| - | `public const LeanTweenType easeInBounce = 23;` |
| - | `public const LeanTweenType easeOutBounce = 24;` |
| - | `public const LeanTweenType easeInOutBounce = 25;` |
| - | `public const LeanTweenType easeInBack = 26;` |
| - | `public const LeanTweenType easeOutBack = 27;` |
| - | `public const LeanTweenType easeInOutBack = 28;` |
| - | `public const LeanTweenType easeInElastic = 29;` |
| - | `public const LeanTweenType easeOutElastic = 30;` |
| - | `public const LeanTweenType easeInOutElastic = 31;` |
| - | `public const LeanTweenType easeSpring = 32;` |
| - | `public const LeanTweenType easeShake = 33;` |
| - | `public const LeanTweenType punch = 34;` |
| - | `public const LeanTweenType once = 35;` |
| - | `public const LeanTweenType clamp = 36;` |
| - | `public const LeanTweenType pingPong = 37;` |
| - | `public const LeanTweenType animationCurve = 38;` |

### public enum `LeanProp`  
`TypeDefIndex 2956`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const LeanProp position = 0;` |
| - | `public const LeanProp localPosition = 1;` |
| - | `public const LeanProp x = 2;` |
| - | `public const LeanProp y = 3;` |
| - | `public const LeanProp z = 4;` |
| - | `public const LeanProp localX = 5;` |
| - | `public const LeanProp localY = 6;` |
| - | `public const LeanProp localZ = 7;` |
| - | `public const LeanProp scale = 8;` |
| - | `public const LeanProp color = 9;` |

### public class `LeanTween` : MonoBehaviour  
`TypeDefIndex 2961`

| offset | field |
|---|---|
| - | `public static bool throwErrors;` |
| - | `public static float tau;` |
| - | `public static float PI_DIV2;` |
| - | `private static LTSeq[] sequences;` |
| - | `private static LTDescr[] tweens;` |
| - | `private static int[] tweensFinished;` |
| - | `private static int[] tweensFinishedIds;` |
| - | `private static LTDescr tween;` |
| - | `private static int tweenMaxSearch;` |
| - | `private static int maxTweens;` |
| - | `private static int maxSequences;` |
| - | `private static int frameRendered;` |
| - | `private static GameObject _tweenEmpty;` |
| - | `public static float dtEstimated;` |
| - | `public static float dtManual;` |
| - | `public static float dtActual;` |
| - | `private static uint global_counter;` |
| - | `private static int i;` |
| - | `private static int j;` |
| - | `private static int finishedCnt;` |
| - | `public static AnimationCurve punch;` |
| - | `public static AnimationCurve shake;` |
| - | `private static int maxTweenReached;` |
| - | `public static int startSearch;` |
| - | `public static LTDescr d;` |
| - | `private static Action<LTEvent>[] eventListeners;` |
| - | `private static GameObject[] goListeners;` |
| - | `private static int eventsMaxSearch;` |
| - | `public static int EVENTS_MAX;` |
| - | `public static int LISTENERS_MAX;` |
| - | `private static int INIT_LISTENERS_MAX;` |

Properties: `public static int maxSearch { get; }`; `public static int maxSimulataneousTweens { get; }`; `public static int tweensRunning { get; }`; `public static GameObject tweenEmpty { get; }`

<details><summary>methods (177)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E46CA8 |  | `public static void init()` |
| - | 0x2E46D60 |  | `public static int get_maxSearch()` |
| - | 0x2E46DB8 |  | `public static int get_maxSimulataneousTweens()` |
| - | 0x2E46E10 |  | `public static int get_tweensRunning()` |
| - | 0x2E46D00 |  | `public static void init(int maxSimultaneousTweens)` |
| - | 0x2E46EC8 |  | `public static void init(int maxSimultaneousTweens, int maxSimultaneousSequences)` |
| - | 0x2E47390 |  | `public static void reset()` |
| - | 0x2E474F0 |  | `public void Update()` |
| - | 0x2E47B40 |  | `private static void onLevelWasLoaded54(Scene scene, LoadSceneMode mode)` |
| - | 0x2E47BA0 |  | `private static void internalOnLevelWasLoaded(int lvl)` |
| - | 0x2E4753C |  | `public static void update()` |
| - | 0x2E47EF4 |  | `public static void removeTween(int i, int uniqueId)` |
| - | 0x2E47BF0 |  | `public static void removeTween(int i, bool shouldReset = true)` |
| - | 0x2E47FB8 |  | `public static Vector3[] add(Vector3[] a, Vector3 b)` |
| - | 0x2E48124 |  | `public static float closestRot(float from, float to)` |
| - | 0x2E48174 |  | `public static void cancelAll()` |
| - | 0x2E481C4 |  | `public static void cancelAll(bool callComplete)` |
| - | 0x2E48390 |  | `public static void cancel(GameObject gameObject)` |
| - | 0x2E483EC |  | `public static void cancel(GameObject gameObject, bool callOnComplete, TweenAction matchType = 51)` |
| - | 0x2E48580 |  | `public static void cancel(RectTransform rect)` |
| - | 0x2E485F8 |  | `public static void cancel(GameObject gameObject, int uniqueId, bool callOnComplete = false)` |
| - | 0x2E48870 |  | `public static void cancel(LTRect ltRect, int uniqueId)` |
| - | 0x2E48988 |  | `public static void cancel(int uniqueId)` |
| - | 0x2E489E0 |  | `public static void cancel(int uniqueId, bool callOnComplete)` |
| - | 0x2E48C30 |  | `public static LTDescr descr(int uniqueId)` |
| - | 0x2E48E78 |  | `public static LTDescr description(int uniqueId)` |
| - | 0x2E48ECC |  | `public static LTDescr[] descriptions(GameObject gameObject)` |
| - | 0x2E4915C |  | `public static void pause(GameObject gameObject, int uniqueId)` |
| - | 0x2E491B0 |  | `public static void pause(int uniqueId)` |
| - | 0x2E49298 |  | `public static void pause(GameObject gameObject)` |
| - | 0x2E493E8 |  | `public static void pauseAll()` |
| - | 0x2E494AC |  | `public static void resumeAll()` |
| - | 0x2E49570 |  | `public static void resume(GameObject gameObject, int uniqueId)` |
| - | 0x2E495C4 |  | `public static void resume(int uniqueId)` |
| - | 0x2E496AC |  | `public static void resume(GameObject gameObject)` |
| - | 0x2E497FC |  | `public static bool isPaused(GameObject gameObject)` |
| - | 0x2E49A78 |  | `public static bool isPaused(RectTransform rect)` |
| - | 0x2E49CD4 |  | `public static bool isPaused(int uniqueId)` |
| - | 0x2E49AE8 |  | `public static bool isTweening(GameObject gameObject)` |
| - | 0x2E49E24 |  | `public static bool isTweening(RectTransform rect)` |
| - | 0x2E49E94 |  | `public static bool isTweening(int uniqueId)` |
| - | 0x2E49F9C |  | `public static bool isTweening(LTRect ltRect)` |
| - | 0x2E4A0AC |  | `public static void drawBezierPath(Vector3 a, Vector3 b, Vector3 c, Vector3 d, float arrowSize = 0, Transform arrowTransform)` |
| - | 0x2E4A674 |  | `public static object logError(string error)` |
| - | 0x2E4A714 |  | `public static LTDescr options(LTDescr seed)` |
| - | 0x2E4A784 |  | `public static LTDescr options()` |
| - | 0x2E4AAB0 |  | `public static GameObject get_tweenEmpty()` |
| - | 0x2E4AB18 |  | `private static LTDescr pushNewTween(GameObject gameObject, Vector3 to, float time, LTDescr tween)` |
| - | 0x2E4AC3C |  | `public static LTDescr play(RectTransform rectTransform, Sprite[] sprites)` |
| - | 0x2E4AD28 |  | `public static LTSeq sequence(bool initSequence = true)` |
| - | 0x2E4AF50 |  | `public static LTDescr alpha(GameObject gameObject, float to, float time)` |
| - | 0x2E4B020 |  | `public static LTDescr alpha(LTRect ltRect, float to, float time)` |
| - | 0x2E4B0D0 |  | `public static LTDescr textAlpha(RectTransform rectTransform, float to, float time)` |
| - | 0x2E4B174 |  | `public static LTDescr alphaText(RectTransform rectTransform, float to, float time)` |
| - | 0x2E4B218 |  | `public static LTDescr alphaCanvas(CanvasGroup canvasGroup, float to, float time)` |
| - | 0x2E4B2BC |  | `public static LTDescr alphaVertex(GameObject gameObject, float to, float time)` |
| - | 0x2E4B348 |  | `public static LTDescr color(GameObject gameObject, Color to, float time)` |
| - | 0x2E4B44C |  | `public static LTDescr textColor(RectTransform rectTransform, Color to, float time)` |
| - | 0x2E4B524 |  | `public static LTDescr colorText(RectTransform rectTransform, Color to, float time)` |
| - | 0x2E4B5FC |  | `public static LTDescr delayedCall(float delayTime, Action callback)` |
| - | 0x2E4B6DC |  | `public static LTDescr delayedCall(float delayTime, Action<object> callback)` |
| - | 0x2E4B7BC |  | `public static LTDescr delayedCall(GameObject gameObject, float delayTime, Action callback)` |
| - | 0x2E4B890 |  | `public static LTDescr delayedCall(GameObject gameObject, float delayTime, Action<object> callback)` |
| - | 0x2E4B974 |  | `public static LTDescr destroyAfter(LTRect rect, float delayTime)` |
| - | 0x2E4BA64 |  | `public static LTDescr move(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E4BB00 |  | `public static LTDescr move(GameObject gameObject, Vector2 to, float time)` |
| - | 0x2E4BBB8 |  | `public static LTDescr move(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E4BD18 |  | `public static LTDescr move(GameObject gameObject, LTBezierPath to, float time)` |
| - | 0x2E4BDF0 |  | `public static LTDescr move(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E4BEC8 |  | `public static LTDescr moveSpline(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E4BFD0 |  | `public static LTDescr moveSpline(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E4C0A8 |  | `public static LTDescr moveSplineLocal(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E4C1B0 |  | `public static LTDescr move(LTRect ltRect, Vector2 to, float time)` |
| - | 0x2E4C260 |  | `public static LTDescr moveMargin(LTRect ltRect, Vector2 to, float time)` |
| - | 0x2E4C310 |  | `public static LTDescr moveX(GameObject gameObject, float to, float time)` |
| - | 0x2E4C39C |  | `public static LTDescr moveY(GameObject gameObject, float to, float time)` |
| - | 0x2E4C428 |  | `public static LTDescr moveZ(GameObject gameObject, float to, float time)` |
| - | 0x2E4C4B4 |  | `public static LTDescr moveLocal(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E4C550 |  | `public static LTDescr moveLocal(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E4C6B0 |  | `public static LTDescr moveLocalX(GameObject gameObject, float to, float time)` |
| - | 0x2E4C73C |  | `public static LTDescr moveLocalY(GameObject gameObject, float to, float time)` |
| - | 0x2E4C7C8 |  | `public static LTDescr moveLocalZ(GameObject gameObject, float to, float time)` |
| - | 0x2E4C854 |  | `public static LTDescr moveLocal(GameObject gameObject, LTBezierPath to, float time)` |
| - | 0x2E4C92C |  | `public static LTDescr moveLocal(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E4CA04 |  | `public static LTDescr move(GameObject gameObject, Transform to, float time)` |
| - | 0x2E4CAE8 |  | `public static LTDescr rotate(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E4CB84 |  | `public static LTDescr rotate(LTRect ltRect, float to, float time)` |
| - | 0x2E4CC28 |  | `public static LTDescr rotateLocal(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E4CCC4 |  | `public static LTDescr rotateX(GameObject gameObject, float to, float time)` |
| - | 0x2E4CD50 |  | `public static LTDescr rotateY(GameObject gameObject, float to, float time)` |
| - | 0x2E4CDDC |  | `public static LTDescr rotateZ(GameObject gameObject, float to, float time)` |
| - | 0x2E4CE68 |  | `public static LTDescr rotateAround(GameObject gameObject, Vector3 axis, float add, float time)` |
| - | 0x2E4CF28 |  | `public static LTDescr rotateAroundLocal(GameObject gameObject, Vector3 axis, float add, float time)` |
| - | 0x2E4CFE8 |  | `public static LTDescr scale(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E4D084 |  | `public static LTDescr scale(LTRect ltRect, Vector2 to, float time)` |
| - | 0x2E4D134 |  | `public static LTDescr scaleX(GameObject gameObject, float to, float time)` |
| - | 0x2E4D1C0 |  | `public static LTDescr scaleY(GameObject gameObject, float to, float time)` |
| - | 0x2E4D24C |  | `public static LTDescr scaleZ(GameObject gameObject, float to, float time)` |
| - | 0x2E4D2D8 |  | `public static LTDescr value(GameObject gameObject, float from, float to, float time)` |
| - | 0x2E4D388 |  | `public static LTDescr value(float from, float to, float time)` |
| - | 0x2E4D43C |  | `public static LTDescr value(GameObject gameObject, Vector2 from, Vector2 to, float time)` |
| - | 0x2E4D514 |  | `public static LTDescr value(GameObject gameObject, Vector3 from, Vector3 to, float time)` |
| - | 0x2E4D5E4 |  | `public static LTDescr value(GameObject gameObject, Color from, Color to, float time)` |
| - | 0x2E4D72C |  | `public static LTDescr value(GameObject gameObject, Action<float> callOnUpdate, float from, float to, float time)` |
| - | 0x2E4D810 |  | `public static LTDescr value(GameObject gameObject, Action<float, float> callOnUpdateRatio, float from, float to, float time)` |
| - | 0x2E4D8F4 |  | `public static LTDescr value(GameObject gameObject, Action<Color> callOnUpdate, Color from, Color to, float time)` |
| - | 0x2E4DA28 |  | `public static LTDescr value(GameObject gameObject, Action<Color, object> callOnUpdate, Color from, Color to, float time)` |
| - | 0x2E4DB5C |  | `public static LTDescr value(GameObject gameObject, Action<Vector2> callOnUpdate, Vector2 from, Vector2 to, float time)` |
| - | 0x2E4DC50 |  | `public static LTDescr value(GameObject gameObject, Action<Vector3> callOnUpdate, Vector3 from, Vector3 to, float time)` |
| - | 0x2E4DD54 |  | `public static LTDescr value(GameObject gameObject, Action<float, object> callOnUpdate, float from, float to, float time)` |
| - | 0x2E4DE3C |  | `public static LTDescr delayedSound(AudioClip audio, Vector3 pos, float volume)` |
| - | 0x2E4DF20 |  | `public static LTDescr delayedSound(GameObject gameObject, AudioClip audio, Vector3 pos, float volume)` |
| - | 0x2E4E008 |  | `public static LTDescr move(RectTransform rectTrans, Vector3 to, float time)` |
| - | 0x2E4E0CC |  | `public static LTDescr moveX(RectTransform rectTrans, float to, float time)` |
| - | 0x2E4E180 |  | `public static LTDescr moveY(RectTransform rectTrans, float to, float time)` |
| - | 0x2E4E234 |  | `public static LTDescr moveZ(RectTransform rectTrans, float to, float time)` |
| - | 0x2E4E2E8 |  | `public static LTDescr rotate(RectTransform rectTrans, float to, float time)` |
| - | 0x2E4E3E8 |  | `public static LTDescr rotate(RectTransform rectTrans, Vector3 to, float time)` |
| - | 0x2E4E4F8 |  | `public static LTDescr rotateAround(RectTransform rectTrans, Vector3 axis, float to, float time)` |
| - | 0x2E4E5E0 |  | `public static LTDescr rotateAroundLocal(RectTransform rectTrans, Vector3 axis, float to, float time)` |
| - | 0x2E4E6C8 |  | `public static LTDescr scale(RectTransform rectTrans, Vector3 to, float time)` |
| - | 0x2E4E78C |  | `public static LTDescr size(RectTransform rectTrans, Vector2 to, float time)` |
| - | 0x2E4E84C |  | `public static LTDescr alpha(RectTransform rectTrans, float to, float time)` |
| - | 0x2E4E900 |  | `public static LTDescr color(RectTransform rectTrans, Color to, float time)` |
| - | 0x2E4E9E8 |  | `public static float tweenOnCurve(LTDescr tweenDescr, float ratioPassed)` |
| - | 0x2E4EA30 |  | `public static Vector3 tweenOnCurveVector(LTDescr tweenDescr, float ratioPassed)` |
| - | 0x2E4EB08 |  | `public static float easeOutQuadOpt(float start, float diff, float ratioPassed)` |
| - | 0x2E4EB20 |  | `public static float easeInQuadOpt(float start, float diff, float ratioPassed)` |
| - | 0x2E4EB30 |  | `public static float easeInOutQuadOpt(float start, float diff, float ratioPassed)` |
| - | 0x2E4EB80 |  | `public static Vector3 easeInOutQuadOpt(Vector3 start, Vector3 diff, float ratioPassed)` |
| - | 0x2E4EC0C |  | `public static float linear(float start, float end, float val)` |
| - | 0x2E4EC30 |  | `public static float clerp(float start, float end, float val)` |
| - | 0x2E4EC94 |  | `public static float spring(float start, float end, float val)` |
| - | 0x2E4ED44 |  | `public static float easeInQuad(float start, float end, float val)` |
| - | 0x2E4ED58 |  | `public static float easeOutQuad(float start, float end, float val)` |
| - | 0x2E4ED74 |  | `public static float easeInOutQuad(float start, float end, float val)` |
| - | 0x2E4EDC8 |  | `public static float easeInOutQuadOpt2(float start, float diffBy2, float val, float val2)` |
| - | 0x2E4EE00 |  | `public static float easeInCubic(float start, float end, float val)` |
| - | 0x2E4EE18 |  | `public static float easeOutCubic(float start, float end, float val)` |
| - | 0x2E4EE40 |  | `public static float easeInOutCubic(float start, float end, float val)` |
| - | 0x2E4EE98 |  | `public static float easeInQuart(float start, float end, float val)` |
| - | 0x2E4EEB4 |  | `public static float easeOutQuart(float start, float end, float val)` |
| - | 0x2E4EEDC |  | `public static float easeInOutQuart(float start, float end, float val)` |
| - | 0x2E4EF38 |  | `public static float easeInQuint(float start, float end, float val)` |
| - | 0x2E4EF58 |  | `public static float easeOutQuint(float start, float end, float val)` |
| - | 0x2E4EF88 |  | `public static float easeInOutQuint(float start, float end, float val)` |
| - | 0x2E4EFF0 |  | `public static float easeInSine(float start, float end, float val)` |
| - | 0x2E4F028 |  | `public static float easeOutSine(float start, float end, float val)` |
| - | 0x2E4F05C |  | `public static float easeInOutSine(float start, float end, float val)` |
| - | 0x2E4F0A0 |  | `public static float easeInExpo(float start, float end, float val)` |
| - | 0x2E4F0D8 |  | `public static float easeOutExpo(float start, float end, float val)` |
| - | 0x2E4F110 |  | `public static float easeInOutExpo(float start, float end, float val)` |
| - | 0x2E4F180 |  | `public static float easeInCirc(float start, float end, float val)` |
| - | 0x2E4F1A8 |  | `public static float easeOutCirc(float start, float end, float val)` |
| - | 0x2E4F1D0 |  | `public static float easeInOutCirc(float start, float end, float val)` |
| - | 0x2E4F224 |  | `public static float easeInBounce(float start, float end, float val)` |
| - | 0x2E4F2AC |  | `public static float easeOutBounce(float start, float end, float val)` |
| - | 0x2E4F374 |  | `public static float easeInOutBounce(float start, float end, float val)` |
| - | 0x2E4F428 |  | `public static float easeInBack(float start, float end, float val, float overshoot = 1)` |
| - | 0x2E4F45C |  | `public static float easeOutBack(float start, float end, float val, float overshoot = 1)` |
| - | 0x2E4F49C |  | `public static float easeInOutBack(float start, float end, float val, float overshoot = 1)` |
| - | 0x2E4F534 |  | `public static float easeInElastic(float start, float end, float val, float overshoot = 1, float period = 0.3)` |
| - | 0x2E4F614 |  | `public static float easeOutElastic(float start, float end, float val, float overshoot = 1, float period = 0.3)` |
| - | 0x2E4F6E8 |  | `public static float easeInOutElastic(float start, float end, float val, float overshoot = 1, float period = 0.3)` |
| - | 0x2E4F848 |  | `public static LTDescr followDamp(Transform trans, Transform target, LeanProp prop, float smoothTime, float maxSpeed = -1)` |
| - | 0x2E4FBFC |  | `public static LTDescr followSpring(Transform trans, Transform target, LeanProp prop, float smoothTime, float maxSpeed = -1, float friction = 2, float accelRate = 0.5)` |
| - | 0x2E4FFBC |  | `public static LTDescr followBounceOut(Transform trans, Transform target, LeanProp prop, float smoothTime, float maxSpeed = -1, float friction = 2, float accelRate = 0.5, float hitDamping = 0.9)` |
| - | 0x2E5036C |  | `public static LTDescr followLinear(Transform trans, Transform target, LeanProp prop, float moveSpeed)` |
| - | 0x2E506FC |  | `public static void addListener(int eventId, Action<LTEvent> callback)` |
| - | 0x2E50764 |  | `public static void addListener(GameObject caller, int eventId, Action<LTEvent> callback)` |
| - | 0x2E50ADC |  | `public static bool removeListener(int eventId, Action<LTEvent> callback)` |
| - | 0x2E50D50 |  | `public static bool removeListener(int eventId)` |
| - | 0x2E50B44 |  | `public static bool removeListener(GameObject caller, int eventId, Action<LTEvent> callback)` |
| - | 0x2E50E14 |  | `public static void dispatchEvent(int eventId)` |
| - | 0x2E50E6C |  | `public static void dispatchEvent(int eventId, object data)` |
| - | 0x2E51040 |  | `public void .ctor()` |
| - | 0x2E51048 |  | `private static void .cctor()` |

</details>

### public class `LTUtility`  
`TypeDefIndex 2962`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E53624 |  | `public static Vector3[] reverse(Vector3[] arr)` |
| - | 0x2E536C0 |  | `public void .ctor()` |

</details>

### public class `LTBezier`  
`TypeDefIndex 2963`

| offset | field |
|---|---|
| - | `public float length;` |
| - | `private Vector3 a;` |
| - | `private Vector3 aa;` |
| - | `private Vector3 bb;` |
| - | `private Vector3 cc;` |
| - | `private float len;` |
| - | `private float[] arcLengths;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E536C8 |  | `public void .ctor(Vector3 a, Vector3 b, Vector3 c, Vector3 d, float precision)` |
| - | 0x2E539B0 |  | `private float map(float u)` |
| - | 0x2E53958 |  | `private Vector3 bezierPoint(float t)` |
| - | 0x2E53AD0 |  | `public Vector3 point(float t)` |

</details>

### public class `LTBezierPath`  
`TypeDefIndex 2964`

| offset | field |
|---|---|
| - | `public Vector3[] pts;` |
| - | `public float length;` |
| - | `public bool orientToPath;` |
| - | `public bool orientToPath2d;` |
| - | `private LTBezier[] beziers;` |
| - | `private float[] lengthRatio;` |
| - | `private int currentBezier;` |
| - | `private int previousBezier;` |

Properties: `public float distance { get; }`

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E53AE8 |  | `public void .ctor()` |
| - | 0x2E53AF0 |  | `public void .ctor(Vector3[] pts_)` |
| - | 0x2E53B1C |  | `public void setPoints(Vector3[] pts_)` |
| - | 0x2E53EA0 |  | `public float get_distance()` |
| - | 0x2E53EA8 |  | `public Vector3 point(float ratio)` |
| - | 0x2E53F6C |  | `public void place2d(Transform transform, float ratio)` |
| - | 0x2E54020 |  | `public void placeLocal2d(Transform transform, float ratio)` |
| - | 0x2E540D4 |  | `public void place(Transform transform, float ratio)` |
| - | 0x2E54140 |  | `public void place(Transform transform, float ratio, Vector3 worldUp)` |
| - | 0x2E541DC |  | `public void placeLocal(Transform transform, float ratio)` |
| - | 0x2E54248 |  | `public void placeLocal(Transform transform, float ratio, Vector3 worldUp)` |
| - | 0x2E54340 |  | `public void gizmoDraw(float t = -1)` |
| - | 0x2E54420 |  | `public float ratioAtPoint(Vector3 pt, float precision = 0.01)` |

</details>

### public class `LTSpline`  
`TypeDefIndex 2965`

| offset | field |
|---|---|
| - | `public static int DISTANCE_COUNT;` |
| - | `public static int SUBLINE_COUNT;` |
| - | `public float distance;` |
| - | `public bool constantSpeed;` |
| - | `public Vector3[] pts;` |
| - | `public Vector3[] ptsAdj;` |
| - | `public int ptsAdjLength;` |
| - | `public bool orientToPath;` |
| - | `public bool orientToPath2d;` |
| - | `private int numSections;` |
| - | `private int currPt;` |

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E545F4 |  | `public void .ctor(Vector3[] pts)` |
| - | 0x2E54A20 |  | `public void .ctor(Vector3[] pts, bool constantSpeed)` |
| - | 0x2E5462C |  | `private void init(Vector3[] pts, bool constantSpeed)` |
| - | 0x2E54C64 |  | `public Vector3 map(float u)` |
| - | 0x2E54A60 |  | `public Vector3 interp(float t)` |
| - | 0x2E54D5C |  | `public float ratioAtPoint(Vector3 pt)` |
| - | 0x2E54E88 |  | `public Vector3 point(float ratio)` |
| - | 0x2E54EA0 |  | `public void place2d(Transform transform, float ratio)` |
| - | 0x2E54F54 |  | `public void placeLocal2d(Transform transform, float ratio)` |
| - | 0x2E5508C |  | `public void place(Transform transform, float ratio)` |
| - | 0x2E550F8 |  | `public void place(Transform transform, float ratio, Vector3 worldUp)` |
| - | 0x2E55194 |  | `public void placeLocal(Transform transform, float ratio)` |
| - | 0x2E55200 |  | `public void placeLocal(Transform transform, float ratio, Vector3 worldUp)` |
| - | 0x2E552C0 |  | `public void gizmoDraw(float t = -1)` |
| - | 0x2E55374 |  | `public void drawGizmo(Color color)` |
| - | 0x2E554C0 |  | `public static void drawGizmo(Transform[] arr, Color color)` |
| - | 0x2E556EC |  | `public static void drawLine(Transform[] arr, float width, Color color)` |
| - | 0x2E556FC |  | `public void drawLinesGLLines(Material outlineMaterial, Color color, float width)` |
| - | 0x2E558C4 |  | `public Vector3[] generateVectors()` |
| - | 0x2E55AA0 |  | `private static void .cctor()` |

</details>

### public class `LTRect`  
`TypeDefIndex 2966`

| offset | field |
|---|---|
| - | `public Rect _rect;` |
| - | `public float alpha;` |
| - | `public float rotation;` |
| - | `public Vector2 pivot;` |
| - | `public Vector2 margin;` |
| - | `public Rect relativeRect;` |
| - | `public bool rotateEnabled;` |
| - | `public bool rotateFinished;` |
| - | `public bool alphaEnabled;` |
| - | `public string labelStr;` |
| - | `public LTGUI.Element_Type type;` |
| - | `public GUIStyle style;` |
| - | `public bool useColor;` |
| - | `public Color color;` |
| - | `public bool fontScaleToFit;` |
| - | `public bool useSimpleScale;` |
| - | `public bool sizeByHeight;` |
| - | `public Texture texture;` |
| - | `private int _id;` |
| - | `public int counter;` |
| - | `public static bool colorTouched;` |

Properties: `public bool hasInitiliazed { get; }`; `public int id { get; }`; `public float x { get; set; }`; `public float y { get; set; }`; `public float width { get; set; }`; `public float height { get; set; }`; `public Rect rect { get; set; }`

<details><summary>methods (29)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E55AF0 |  | `public void .ctor()` |
| - | 0x2E55BB8 |  | `public void .ctor(Rect rect)` |
| - | 0x2E55C20 |  | `public void .ctor(float x, float y, float width, float height)` |
| - | 0x2E55C98 |  | `public void .ctor(float x, float y, float width, float height, float alpha)` |
| - | 0x2E55D18 |  | `public void .ctor(float x, float y, float width, float height, float alpha, float rotation)` |
| - | 0x2E55FC8 |  | `public bool get_hasInitiliazed()` |
| - | 0x2E55FD8 |  | `public int get_id()` |
| - | 0x2E55FE4 |  | `public void setId(int id, int counter)` |
| - | 0x2E55B4C |  | `public void reset()` |
| - | 0x2E55DC0 |  | `public void resetForRotation()` |
| - | 0x2E55FEC |  | `public float get_x()` |
| - | 0x2E55FF4 |  | `public void set_x(float value)` |
| - | 0x2E55FFC |  | `public float get_y()` |
| - | 0x2E56004 |  | `public void set_y(float value)` |
| - | 0x2E5600C |  | `public float get_width()` |
| - | 0x2E56014 |  | `public void set_width(float value)` |
| - | 0x2E5601C |  | `public float get_height()` |
| - | 0x2E56024 |  | `public void set_height(float value)` |
| - | 0x2E5602C |  | `public Rect get_rect()` |
| - | 0x2E56234 |  | `public void set_rect(Rect value)` |
| - | 0x2E56240 |  | `public LTRect setStyle(GUIStyle style)` |
| - | 0x2E5625C |  | `public LTRect setFontScaleToFit(bool fontScaleToFit)` |
| - | 0x2E56268 |  | `public LTRect setColor(Color color)` |
| - | 0x2E5627C |  | `public LTRect setAlpha(float alpha)` |
| - | 0x2E56284 |  | `public LTRect setLabel(string str)` |
| - | 0x2E562A0 |  | `public LTRect setUseSimpleScale(bool useSimpleScale, Rect relativeRect)` |
| - | 0x2E562B4 |  | `public LTRect setUseSimpleScale(bool useSimpleScale)` |
| - | 0x2E562FC |  | `public LTRect setSizeByHeight(bool sizeByHeight)` |
| - | 0x2E56308 |  | `public override string ToString()` |

</details>

### public class `LTEvent`  
`TypeDefIndex 2967`

| offset | field |
|---|---|
| - | `public int id;` |
| - | `public object data;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E56510 |  | `public void .ctor(int id, object data)` |

</details>

### public class `LTGUI`  
`TypeDefIndex 2969`

| offset | field |
|---|---|
| - | `public static int RECT_LEVELS;` |
| - | `public static int RECTS_PER_LEVEL;` |
| - | `public static int BUTTONS_MAX;` |
| - | `private static LTRect[] levels;` |
| - | `private static int[] levelDepths;` |
| - | `private static Rect[] buttons;` |
| - | `private static int[] buttonLevels;` |
| - | `private static int[] buttonLastFrame;` |
| - | `private static LTRect r;` |
| - | `private static Color color;` |
| - | `private static bool isGUIEnabled;` |
| - | `private static int global_counter;` |

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E56548 |  | `public static void init()` |
| - | 0x2E5663C |  | `public static void initRectCheck()` |
| - | 0x2E567C4 |  | `public static void reset()` |
| - | 0x2E5691C |  | `public static void update(int updateLevel)` |
| - | 0x2E5707C |  | `public static bool checkOnScreen(Rect rect)` |
| - | 0x2E570F4 |  | `public static void destroy(int id)` |
| - | 0x2E57250 |  | `public static void destroyAll(int depth)` |
| - | 0x2E57338 |  | `public static LTRect label(Rect rect, string label, int depth)` |
| - | 0x2E573F4 |  | `public static LTRect label(LTRect rect, string label, int depth)` |
| - | 0x2E5776C |  | `public static LTRect texture(Rect rect, Texture texture, int depth)` |
| - | 0x2E57828 |  | `public static LTRect texture(LTRect rect, Texture texture, int depth)` |
| - | 0x2E5747C |  | `public static LTRect element(LTRect rect, int depth)` |
| - | 0x2E578AC |  | `public static bool hasNoOverlap(Rect rect, int depth)` |
| - | 0x2E57B68 |  | `public static bool pressedWithinRect(Rect rect)` |
| - | 0x2E57CA8 |  | `public static bool checkWithinRect(Vector2 vec2, Rect rect)` |
| - | 0x2E57C38 |  | `public static Vector2 firstTouch()` |
| - | 0x2E57D24 |  | `public void .ctor()` |
| - | 0x2E57D2C |  | `private static void .cctor()` |

</details>

### public static class `LeanTweenExt`  
`TypeDefIndex 2970`

<details><summary>methods (99)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E57D98 |  | `public static LTDescr LeanAlpha(GameObject gameObject, float to, float time)` |
| - | 0x2E57E08 |  | `public static LTDescr LeanAlphaVertex(GameObject gameObject, float to, float time)` |
| - | 0x2E57E78 |  | `public static LTDescr LeanAlpha(RectTransform rectTransform, float to, float time)` |
| - | 0x2E57EE8 |  | `public static LTDescr LeanAlpha(CanvasGroup canvas, float to, float time)` |
| - | 0x2E57F58 |  | `public static LTDescr LeanAlphaText(RectTransform rectTransform, float to, float time)` |
| - | 0x2E57FC8 |  | `public static void LeanCancel(GameObject gameObject)` |
| - | 0x2E58020 |  | `public static void LeanCancel(GameObject gameObject, bool callOnComplete)` |
| - | 0x2E5808C |  | `public static void LeanCancel(GameObject gameObject, int uniqueId, bool callOnComplete = false)` |
| - | 0x2E580FC |  | `public static void LeanCancel(RectTransform rectTransform)` |
| - | 0x2E58154 |  | `public static LTDescr LeanColor(GameObject gameObject, Color to, float time)` |
| - | 0x2E581EC |  | `public static LTDescr LeanColorText(RectTransform rectTransform, Color to, float time)` |
| - | 0x2E58284 |  | `public static LTDescr LeanDelayedCall(GameObject gameObject, float delayTime, Action callback)` |
| - | 0x2E582FC |  | `public static LTDescr LeanDelayedCall(GameObject gameObject, float delayTime, Action<object> callback)` |
| - | 0x2E58374 |  | `public static bool LeanIsPaused(GameObject gameObject)` |
| - | 0x2E583CC |  | `public static bool LeanIsPaused(RectTransform rectTransform)` |
| - | 0x2E58424 |  | `public static bool LeanIsTweening(GameObject gameObject)` |
| - | 0x2E5847C |  | `public static LTDescr LeanMove(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E58504 |  | `public static LTDescr LeanMove(Transform transform, Vector3 to, float time)` |
| - | 0x2E585A8 |  | `public static LTDescr LeanMove(RectTransform rectTransform, Vector3 to, float time)` |
| - | 0x2E58630 |  | `public static LTDescr LeanMove(GameObject gameObject, Vector2 to, float time)` |
| - | 0x2E586B0 |  | `public static LTDescr LeanMove(Transform transform, Vector2 to, float time)` |
| - | 0x2E5874C |  | `public static LTDescr LeanMove(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E587C4 |  | `public static LTDescr LeanMove(GameObject gameObject, LTBezierPath to, float time)` |
| - | 0x2E5883C |  | `public static LTDescr LeanMove(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E588B4 |  | `public static LTDescr LeanMove(Transform transform, Vector3[] to, float time)` |
| - | 0x2E58940 |  | `public static LTDescr LeanMove(Transform transform, LTBezierPath to, float time)` |
| - | 0x2E589CC |  | `public static LTDescr LeanMove(Transform transform, LTSpline to, float time)` |
| - | 0x2E58A58 |  | `public static LTDescr LeanMoveLocal(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E58AE0 |  | `public static LTDescr LeanMoveLocal(GameObject gameObject, LTBezierPath to, float time)` |
| - | 0x2E58B58 |  | `public static LTDescr LeanMoveLocal(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E58BD0 |  | `public static LTDescr LeanMoveLocal(Transform transform, Vector3 to, float time)` |
| - | 0x2E58C74 |  | `public static LTDescr LeanMoveLocal(Transform transform, LTBezierPath to, float time)` |
| - | 0x2E58D00 |  | `public static LTDescr LeanMoveLocal(Transform transform, LTSpline to, float time)` |
| - | 0x2E58D8C |  | `public static LTDescr LeanMoveLocalX(GameObject gameObject, float to, float time)` |
| - | 0x2E58DFC |  | `public static LTDescr LeanMoveLocalY(GameObject gameObject, float to, float time)` |
| - | 0x2E58E6C |  | `public static LTDescr LeanMoveLocalZ(GameObject gameObject, float to, float time)` |
| - | 0x2E58EDC |  | `public static LTDescr LeanMoveLocalX(Transform transform, float to, float time)` |
| - | 0x2E58F68 |  | `public static LTDescr LeanMoveLocalY(Transform transform, float to, float time)` |
| - | 0x2E58FF4 |  | `public static LTDescr LeanMoveLocalZ(Transform transform, float to, float time)` |
| - | 0x2E59080 |  | `public static LTDescr LeanMoveSpline(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E590F8 |  | `public static LTDescr LeanMoveSpline(GameObject gameObject, LTSpline to, float time)` |
| - | 0x2E59170 |  | `public static LTDescr LeanMoveSpline(Transform transform, Vector3[] to, float time)` |
| - | 0x2E591FC |  | `public static LTDescr LeanMoveSpline(Transform transform, LTSpline to, float time)` |
| - | 0x2E59288 |  | `public static LTDescr LeanMoveSplineLocal(GameObject gameObject, Vector3[] to, float time)` |
| - | 0x2E59300 |  | `public static LTDescr LeanMoveSplineLocal(Transform transform, Vector3[] to, float time)` |
| - | 0x2E5938C |  | `public static LTDescr LeanMoveX(GameObject gameObject, float to, float time)` |
| - | 0x2E593FC |  | `public static LTDescr LeanMoveX(Transform transform, float to, float time)` |
| - | 0x2E59488 |  | `public static LTDescr LeanMoveX(RectTransform rectTransform, float to, float time)` |
| - | 0x2E594F8 |  | `public static LTDescr LeanMoveY(GameObject gameObject, float to, float time)` |
| - | 0x2E59568 |  | `public static LTDescr LeanMoveY(Transform transform, float to, float time)` |
| - | 0x2E595F4 |  | `public static LTDescr LeanMoveY(RectTransform rectTransform, float to, float time)` |
| - | 0x2E59664 |  | `public static LTDescr LeanMoveZ(GameObject gameObject, float to, float time)` |
| - | 0x2E596D4 |  | `public static LTDescr LeanMoveZ(Transform transform, float to, float time)` |
| - | 0x2E59760 |  | `public static LTDescr LeanMoveZ(RectTransform rectTransform, float to, float time)` |
| - | 0x2E597D0 |  | `public static void LeanPause(GameObject gameObject)` |
| - | 0x2E59828 |  | `public static LTDescr LeanPlay(RectTransform rectTransform, Sprite[] sprites)` |
| - | 0x2E59890 |  | `public static void LeanResume(GameObject gameObject)` |
| - | 0x2E598E8 |  | `public static LTDescr LeanRotate(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E59970 |  | `public static LTDescr LeanRotate(Transform transform, Vector3 to, float time)` |
| - | 0x2E59A14 |  | `public static LTDescr LeanRotate(RectTransform rectTransform, Vector3 to, float time)` |
| - | 0x2E59A9C |  | `public static LTDescr LeanRotateAround(GameObject gameObject, Vector3 axis, float add, float time)` |
| - | 0x2E59B34 |  | `public static LTDescr LeanRotateAround(Transform transform, Vector3 axis, float add, float time)` |
| - | 0x2E59BE8 |  | `public static LTDescr LeanRotateAround(RectTransform rectTransform, Vector3 axis, float add, float time)` |
| - | 0x2E59C80 |  | `public static LTDescr LeanRotateAroundLocal(GameObject gameObject, Vector3 axis, float add, float time)` |
| - | 0x2E59D18 |  | `public static LTDescr LeanRotateAroundLocal(Transform transform, Vector3 axis, float add, float time)` |
| - | 0x2E59DCC |  | `public static LTDescr LeanRotateAroundLocal(RectTransform rectTransform, Vector3 axis, float add, float time)` |
| - | 0x2E59E64 |  | `public static LTDescr LeanRotateX(GameObject gameObject, float to, float time)` |
| - | 0x2E59ED4 |  | `public static LTDescr LeanRotateX(Transform transform, float to, float time)` |
| - | 0x2E59F60 |  | `public static LTDescr LeanRotateY(GameObject gameObject, float to, float time)` |
| - | 0x2E59FD0 |  | `public static LTDescr LeanRotateY(Transform transform, float to, float time)` |
| - | 0x2E5A05C |  | `public static LTDescr LeanRotateZ(GameObject gameObject, float to, float time)` |
| - | 0x2E5A0CC |  | `public static LTDescr LeanRotateZ(Transform transform, float to, float time)` |
| - | 0x2E5A158 |  | `public static LTDescr LeanScale(GameObject gameObject, Vector3 to, float time)` |
| - | 0x2E5A1E0 |  | `public static LTDescr LeanScale(Transform transform, Vector3 to, float time)` |
| - | 0x2E5A284 |  | `public static LTDescr LeanScale(RectTransform rectTransform, Vector3 to, float time)` |
| - | 0x2E5A30C |  | `public static LTDescr LeanScaleX(GameObject gameObject, float to, float time)` |
| - | 0x2E5A37C |  | `public static LTDescr LeanScaleX(Transform transform, float to, float time)` |
| - | 0x2E5A408 |  | `public static LTDescr LeanScaleY(GameObject gameObject, float to, float time)` |
| - | 0x2E5A478 |  | `public static LTDescr LeanScaleY(Transform transform, float to, float time)` |
| - | 0x2E5A504 |  | `public static LTDescr LeanScaleZ(GameObject gameObject, float to, float time)` |
| - | 0x2E5A574 |  | `public static LTDescr LeanScaleZ(Transform transform, float to, float time)` |
| - | 0x2E5A600 |  | `public static LTDescr LeanSize(RectTransform rectTransform, Vector2 to, float time)` |
| - | 0x2E5A680 |  | `public static LTDescr LeanValue(GameObject gameObject, Color from, Color to, float time)` |
| - | 0x2E5A798 |  | `public static LTDescr LeanValue(GameObject gameObject, float from, float to, float time)` |
| - | 0x2E5A818 |  | `public static LTDescr LeanValue(GameObject gameObject, Vector2 from, Vector2 to, float time)` |
| - | 0x2E5A8B0 |  | `public static LTDescr LeanValue(GameObject gameObject, Vector3 from, Vector3 to, float time)` |
| - | 0x2E5A960 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<float> callOnUpdate, float from, float to, float time)` |
| - | 0x2E5A9F0 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<float, float> callOnUpdate, float from, float to, float time)` |
| - | 0x2E5AA80 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<float, object> callOnUpdate, float from, float to, float time)` |
| - | 0x2E5AB10 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<Color> callOnUpdate, Color from, Color to, float time)` |
| - | 0x2E5AC30 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<Vector2> callOnUpdate, Vector2 from, Vector2 to, float time)` |
| - | 0x2E5ACD8 |  | `public static LTDescr LeanValue(GameObject gameObject, Action<Vector3> callOnUpdate, Vector3 from, Vector3 to, float time)` |
| - | 0x2E5AD98 |  | `public static void LeanSetPosX(Transform transform, float val)` |
| - | 0x2E5ADE4 |  | `public static void LeanSetPosY(Transform transform, float val)` |
| - | 0x2E5AE30 |  | `public static void LeanSetPosZ(Transform transform, float val)` |
| - | 0x2E5AE7C |  | `public static void LeanSetLocalPosX(Transform transform, float val)` |
| - | 0x2E5AEC8 |  | `public static void LeanSetLocalPosY(Transform transform, float val)` |
| - | 0x2E5AF14 |  | `public static void LeanSetLocalPosZ(Transform transform, float val)` |
| - | 0x2E5AF60 |  | `public static Color LeanColor(Transform transform)` |

</details>

### public class `LTDescr`  
`TypeDefIndex 2974`

| offset | field |
|---|---|
| - | `public bool toggle;` |
| - | `public bool useEstimatedTime;` |
| - | `public bool useFrames;` |
| - | `public bool useManualTime;` |
| - | `public bool usesNormalDt;` |
| - | `public bool hasInitiliazed;` |
| - | `public bool hasExtraOnCompletes;` |
| - | `public bool hasPhysics;` |
| - | `public bool onCompleteOnRepeat;` |
| - | `public bool onCompleteOnStart;` |
| - | `public bool useRecursion;` |
| - | `public float ratioPassed;` |
| - | `public float passed;` |
| - | `public float delay;` |
| - | `public float time;` |
| - | `public float speed;` |
| - | `public float lastVal;` |
| - | `private uint _id;` |
| - | `public int loopCount;` |
| - | `public uint counter;` |
| - | `public float direction;` |
| - | `public float directionLast;` |
| - | `public float overshoot;` |
| - | `public float period;` |
| - | `public float scale;` |
| - | `public bool destroyOnComplete;` |
| - | `public Transform trans;` |
| - | `internal Vector3 fromInternal;` |
| - | `internal Vector3 toInternal;` |
| - | `internal Vector3 diff;` |
| - | `internal Vector3 diffDiv2;` |
| - | `public TweenAction type;` |
| - | `private LeanTweenType easeType;` |
| - | `public LeanTweenType loopType;` |
| - | `public bool hasUpdateCallback;` |
| - | `public LTDescr.EaseTypeDelegate easeMethod;` |
| - | `private LTDescr.ActionMethodDelegate <easeInternal>k__BackingField;` |
| - | `private LTDescr.ActionMethodDelegate <initInternal>k__BackingField;` |
| - | `public SpriteRenderer spriteRen;` |
| - | `public RectTransform rectTransform;` |
| - | `public Text uiText;` |
| - | `public Image uiImage;` |
| - | `public RawImage rawImage;` |
| - | `public Sprite[] sprites;` |
| - | `public LTDescrOptional _optional;` |
| - | `public static float val;` |
| - | `public static float dt;` |
| - | `public static Vector3 newVect;` |

Properties: `public Vector3 from { get; set; }`; `public Vector3 to { get; set; }`; `public LTDescr.ActionMethodDelegate easeInternal { get; set; }`; `public LTDescr.ActionMethodDelegate initInternal { get; set; }`; `public Transform toTrans { get; }`; `public int uniqueId { get; }`; `public int id { get; }`; `public LTDescrOptional optional { get; set; }`

<details><summary>methods (311)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E5AFC8 |  | `public Vector3 get_from()` |
| - | 0x2E5AFD4 |  | `public void set_from(Vector3 value)` |
| - | 0x2E5AFE0 |  | `public Vector3 get_to()` |
| - | 0x2E5AFEC |  | `public void set_to(Vector3 value)` |
| - | 0x2E5AFF8 |  | `public LTDescr.ActionMethodDelegate get_easeInternal()` |
| - | 0x2E5B000 |  | `public void set_easeInternal(LTDescr.ActionMethodDelegate value)` |
| - | 0x2E5B008 |  | `public LTDescr.ActionMethodDelegate get_initInternal()` |
| - | 0x2E5B010 |  | `public void set_initInternal(LTDescr.ActionMethodDelegate value)` |
| - | 0x2E5B018 |  | `public Transform get_toTrans()` |
| - | 0x2E5B034 |  | `public override string ToString()` |
| - | 0x2E5B72C |  | `public void .ctor()` |
| - | 0x2E5B7A0 |  | `public LTDescr cancel(GameObject gameObject)` |
| - | 0x2E5B868 |  | `public int get_uniqueId()` |
| - | 0x2E5B71C |  | `public int get_id()` |
| - | 0x2E5B878 |  | `public LTDescrOptional get_optional()` |
| - | 0x2E5B880 |  | `public void set_optional(LTDescrOptional value)` |
| - | 0x2E5B888 |  | `public void reset()` |
| - | 0x2E5B9D8 |  | `public LTDescr setFollow()` |
| - | 0x2E5B9E4 |  | `public LTDescr setMoveX()` |
| - | 0x2E5BAB4 |  | `public LTDescr setMoveY()` |
| - | 0x2E5BB88 |  | `public LTDescr setMoveZ()` |
| - | 0x2E5BC5C |  | `public LTDescr setMoveLocalX()` |
| - | 0x2E5BD30 |  | `public LTDescr setMoveLocalY()` |
| - | 0x2E5BE04 |  | `public LTDescr setMoveLocalZ()` |
| - | 0x2E5BED8 |  | `private void initFromInternal()` |
| - | 0x2E5BEE0 |  | `public LTDescr setOffset(Vector3 offset)` |
| - | 0x2E5BEEC |  | `public LTDescr setMoveCurved()` |
| - | 0x2E5BFC0 |  | `public LTDescr setMoveCurvedLocal()` |
| - | 0x2E5C094 |  | `public LTDescr setMoveSpline()` |
| - | 0x2E5C168 |  | `public LTDescr setMoveSplineLocal()` |
| - | 0x2E5C23C |  | `public LTDescr setScaleX()` |
| - | 0x2E5C310 |  | `public LTDescr setScaleY()` |
| - | 0x2E5C3E4 |  | `public LTDescr setScaleZ()` |
| - | 0x2E5C4B8 |  | `public LTDescr setRotateX()` |
| - | 0x2E5C58C |  | `public LTDescr setRotateY()` |
| - | 0x2E5C660 |  | `public LTDescr setRotateZ()` |
| - | 0x2E5C734 |  | `public LTDescr setRotateAround()` |
| - | 0x2E5C808 |  | `public LTDescr setRotateAroundLocal()` |
| - | 0x2E5C8DC |  | `public LTDescr setAlpha()` |
| - | 0x2E5C9B0 |  | `public LTDescr setTextAlpha()` |
| - | 0x2E5CA84 |  | `public LTDescr setAlphaVertex()` |
| - | 0x2E5CB58 |  | `public LTDescr setColor()` |
| - | 0x2E5CC2C |  | `public LTDescr setCallbackColor()` |
| - | 0x2E5CD00 |  | `public LTDescr setTextColor()` |
| - | 0x2E5CDD4 |  | `public LTDescr setCanvasAlpha()` |
| - | 0x2E5CEA8 |  | `public LTDescr setCanvasGroupAlpha()` |
| - | 0x2E5CF7C |  | `public LTDescr setCanvasColor()` |
| - | 0x2E5D050 |  | `public LTDescr setCanvasMoveX()` |
| - | 0x2E5D124 |  | `public LTDescr setCanvasMoveY()` |
| - | 0x2E5D1F8 |  | `public LTDescr setCanvasMoveZ()` |
| - | 0x2E5D2CC |  | `private void initCanvasRotateAround()` |
| - | 0x2E5D308 |  | `public LTDescr setCanvasRotateAround()` |
| - | 0x2E5D3DC |  | `public LTDescr setCanvasRotateAroundLocal()` |
| - | 0x2E5D4B0 |  | `public LTDescr setCanvasPlaySprite()` |
| - | 0x2E5D584 |  | `public LTDescr setCanvasMove()` |
| - | 0x2E5D658 |  | `public LTDescr setCanvasScale()` |
| - | 0x2E5D72C |  | `public LTDescr setCanvasSizeDelta()` |
| - | 0x2E5D800 |  | `private void callback()` |
| - | 0x2E5D878 |  | `public LTDescr setCallback()` |
| - | 0x2E5D9B4 |  | `public LTDescr setValue3()` |
| - | 0x2E5DAF0 |  | `public LTDescr setMove()` |
| - | 0x2E5DBC4 |  | `public LTDescr setMoveLocal()` |
| - | 0x2E5DC98 |  | `public LTDescr setMoveToTransform()` |
| - | 0x2E5DD6C |  | `public LTDescr setRotate()` |
| - | 0x2E5DE40 |  | `public LTDescr setRotateLocal()` |
| - | 0x2E5DF14 |  | `public LTDescr setScale()` |
| - | 0x2E5DFE8 |  | `public LTDescr setGUIMove()` |
| - | 0x2E5E0BC |  | `public LTDescr setGUIMoveMargin()` |
| - | 0x2E5E190 |  | `public LTDescr setGUIScale()` |
| - | 0x2E5E264 |  | `public LTDescr setGUIAlpha()` |
| - | 0x2E5E338 |  | `public LTDescr setGUIRotate()` |
| - | 0x2E5E40C |  | `public LTDescr setDelayedSound()` |
| - | 0x2E5E4E0 |  | `public LTDescr setTarget(Transform trans)` |
| - | 0x2E5E508 |  | `private void init()` |
| - | 0x2E5E744 |  | `private void initSpeed()` |
| - | 0x2E5E830 |  | `public LTDescr updateNow()` |
| - | 0x2E5E848 |  | `public bool updateInternal()` |
| - | 0x2E5E64C |  | `public void callOnCompletes()` |
| - | 0x2E5EB14 |  | `public LTDescr setFromColor(Color col)` |
| - | 0x2E5EB50 |  | `private static void alphaRecursive(Transform transform, float val, bool useRecursion = true)` |
| - | 0x2E5EFD0 |  | `private static void colorRecursive(Transform transform, Color toColor, bool useRecursion = true)` |
| - | 0x2E5F3BC |  | `private static void alphaRecursive(RectTransform rectTransform, float val, int recursiveLevel = 0)` |
| - | 0x2E5F7FC |  | `private static void alphaRecursiveSprite(Transform transform, float val)` |
| - | 0x2E5FBD4 |  | `private static void colorRecursiveSprite(Transform transform, Color toColor)` |
| - | 0x2E5FFD4 |  | `private static void colorRecursive(RectTransform rectTransform, Color toColor)` |
| - | 0x2E6040C |  | `private static void textAlphaChildrenRecursive(Transform trans, float val, bool useRecursion = true)` |
| - | 0x2E607C4 |  | `private static void textAlphaRecursive(Transform trans, float val, bool useRecursion = true)` |
| - | 0x2E60B4C |  | `private static void textColorRecursive(Transform trans, Color toColor)` |
| - | 0x2E60F08 |  | `private static Color tweenColor(LTDescr tween, float val)` |
| - | 0x2E60F64 |  | `public LTDescr pause()` |
| - | 0x2E60F80 |  | `public LTDescr resume()` |
| - | 0x2E60F8C |  | `public LTDescr setAxis(Vector3 axis)` |
| - | 0x2E60FAC |  | `public LTDescr setDelay(float delay)` |
| - | 0x2E60FB4 |  | `public LTDescr setEase(LeanTweenType easeType)` |
| - | 0x2E610F0 |  | `public LTDescr setEaseLinear()` |
| - | 0x2E624A4 |  | `public LTDescr setEaseSpring()` |
| - | 0x2E61218 |  | `public LTDescr setEaseInQuad()` |
| - | 0x2E61184 |  | `public LTDescr setEaseOutQuad()` |
| - | 0x2E612AC |  | `public LTDescr setEaseInOutQuad()` |
| - | 0x2E61340 |  | `public LTDescr setEaseInCubic()` |
| - | 0x2E613D4 |  | `public LTDescr setEaseOutCubic()` |
| - | 0x2E61468 |  | `public LTDescr setEaseInOutCubic()` |
| - | 0x2E614FC |  | `public LTDescr setEaseInQuart()` |
| - | 0x2E61590 |  | `public LTDescr setEaseOutQuart()` |
| - | 0x2E61624 |  | `public LTDescr setEaseInOutQuart()` |
| - | 0x2E616B8 |  | `public LTDescr setEaseInQuint()` |
| - | 0x2E6174C |  | `public LTDescr setEaseOutQuint()` |
| - | 0x2E617E0 |  | `public LTDescr setEaseInOutQuint()` |
| - | 0x2E61874 |  | `public LTDescr setEaseInSine()` |
| - | 0x2E61908 |  | `public LTDescr setEaseOutSine()` |
| - | 0x2E6199C |  | `public LTDescr setEaseInOutSine()` |
| - | 0x2E61A30 |  | `public LTDescr setEaseInExpo()` |
| - | 0x2E61AC4 |  | `public LTDescr setEaseOutExpo()` |
| - | 0x2E61B58 |  | `public LTDescr setEaseInOutExpo()` |
| - | 0x2E61BEC |  | `public LTDescr setEaseInCirc()` |
| - | 0x2E61C80 |  | `public LTDescr setEaseOutCirc()` |
| - | 0x2E61D14 |  | `public LTDescr setEaseInOutCirc()` |
| - | 0x2E61DA8 |  | `public LTDescr setEaseInBounce()` |
| - | 0x2E61E3C |  | `public LTDescr setEaseOutBounce()` |
| - | 0x2E61ED0 |  | `public LTDescr setEaseInOutBounce()` |
| - | 0x2E61F64 |  | `public LTDescr setEaseInBack()` |
| - | 0x2E61FF8 |  | `public LTDescr setEaseOutBack()` |
| - | 0x2E6208C |  | `public LTDescr setEaseInOutBack()` |
| - | 0x2E62120 |  | `public LTDescr setEaseInElastic()` |
| - | 0x2E621B4 |  | `public LTDescr setEaseOutElastic()` |
| - | 0x2E62248 |  | `public LTDescr setEaseInOutElastic()` |
| - | 0x2E622DC |  | `public LTDescr setEasePunch()` |
| - | 0x2E623C0 |  | `public LTDescr setEaseShake()` |
| - | 0x2E62538 |  | `private Vector3 tweenOnCurve()` |
| - | 0x2E625F8 |  | `private Vector3 easeInOutQuad()` |
| - | 0x2E6269C |  | `private Vector3 easeInQuad()` |
| - | 0x2E62714 |  | `private Vector3 easeOutQuad()` |
| - | 0x2E62798 |  | `private Vector3 easeLinear()` |
| - | 0x2E6280C |  | `private Vector3 easeSpring()` |
| - | 0x2E62908 |  | `private Vector3 easeInCubic()` |
| - | 0x2E62984 |  | `private Vector3 easeOutCubic()` |
| - | 0x2E62A10 |  | `private Vector3 easeInOutCubic()` |
| - | 0x2E62ABC |  | `private Vector3 easeInQuart()` |
| - | 0x2E62B3C |  | `private Vector3 easeOutQuart()` |
| - | 0x2E62BCC |  | `private Vector3 easeInOutQuart()` |
| - | 0x2E62CA0 |  | `private Vector3 easeInQuint()` |
| - | 0x2E62D24 |  | `private Vector3 easeOutQuint()` |
| - | 0x2E62DB8 |  | `private Vector3 easeInOutQuint()` |
| - | 0x2E62E74 |  | `private Vector3 easeInSine()` |
| - | 0x2E62F34 |  | `private Vector3 easeOutSine()` |
| - | 0x2E62FE8 |  | `private Vector3 easeInOutSine()` |
| - | 0x2E63078 |  | `private Vector3 easeInExpo()` |
| - | 0x2E63100 |  | `private Vector3 easeOutExpo()` |
| - | 0x2E63188 |  | `private Vector3 easeInOutExpo()` |
| - | 0x2E63254 |  | `private Vector3 easeInCirc()` |
| - | 0x2E632E4 |  | `private Vector3 easeOutCirc()` |
| - | 0x2E63370 |  | `private Vector3 easeInOutCirc()` |
| - | 0x2E63450 |  | `private Vector3 easeInBounce()` |
| - | 0x2E6357C |  | `private Vector3 easeOutBounce()` |
| - | 0x2E636E4 |  | `private Vector3 easeInOutBounce()` |
| - | 0x2E638C0 |  | `private Vector3 easeInBack()` |
| - | 0x2E63964 |  | `private Vector3 easeOutBack()` |
| - | 0x2E63A0C |  | `private Vector3 easeInOutBack()` |
| - | 0x2E63B10 |  | `private Vector3 easeInElastic()` |
| - | 0x2E63BF0 |  | `private Vector3 easeOutElastic()` |
| - | 0x2E63CD0 |  | `private Vector3 easeInOutElastic()` |
| - | 0x2E63DB0 |  | `public LTDescr setOvershoot(float overshoot)` |
| - | 0x2E63DB8 |  | `public LTDescr setPeriod(float period)` |
| - | 0x2E63DC0 |  | `public LTDescr setScale(float scale)` |
| - | 0x2E63DC8 |  | `public LTDescr setEase(AnimationCurve easeCurve)` |
| - | 0x2E63E78 |  | `public LTDescr setTo(Vector3 to)` |
| - | 0x2E63EA8 |  | `public LTDescr setTo(Transform to)` |
| - | 0x2E63ED0 |  | `public LTDescr setFrom(Vector3 from)` |
| - | 0x2E63F94 |  | `public LTDescr setFrom(float from)` |
| - | 0x2E63FA0 |  | `public LTDescr setDiff(Vector3 diff)` |
| - | 0x2E63FAC |  | `public LTDescr setHasInitialized(bool has)` |
| - | 0x2E63FB8 |  | `public LTDescr setId(uint id, uint global_counter)` |
| - | 0x2E63FC4 |  | `public LTDescr setPassed(float passed)` |
| - | 0x2E63FCC |  | `public LTDescr setTime(float time)` |
| - | 0x2E63FE8 |  | `public LTDescr setSpeed(float speed)` |
| - | 0x2E64010 |  | `public LTDescr setRepeat(int repeat)` |
| - | 0x2E64060 |  | `public LTDescr setLoopType(LeanTweenType loopType)` |
| - | 0x2E64068 |  | `public LTDescr setUseEstimatedTime(bool useEstimatedTime)` |
| - | 0x2E64078 |  | `public LTDescr setIgnoreTimeScale(bool useUnScaledTime)` |
| - | 0x2E64088 |  | `public LTDescr setUseFrames(bool useFrames)` |
| - | 0x2E64098 |  | `public LTDescr setUseManualTime(bool useManualTime)` |
| - | 0x2E640A8 |  | `public LTDescr setLoopCount(int loopCount)` |
| - | 0x2E640B8 |  | `public LTDescr setLoopOnce()` |
| - | 0x2E640C4 |  | `public LTDescr setLoopClamp()` |
| - | 0x2E640E4 |  | `public LTDescr setLoopClamp(int loops)` |
| - | 0x2E640EC |  | `public LTDescr setLoopPingPong()` |
| - | 0x2E6410C |  | `public LTDescr setLoopPingPong(int loops)` |
| - | 0x2E64128 |  | `public LTDescr setOnComplete(Action onComplete)` |
| - | 0x2E64158 |  | `public LTDescr setOnComplete(Action<object> onComplete)` |
| - | 0x2E64188 |  | `public LTDescr setOnComplete(Action<object> onComplete, object onCompleteParam)` |
| - | 0x2E641DC |  | `public LTDescr setOnCompleteParam(object onCompleteParam)` |
| - | 0x2E6420C |  | `public LTDescr setOnUpdate(Action<float> onUpdate)` |
| - | 0x2E6423C |  | `public LTDescr setOnUpdateRatio(Action<float, float> onUpdate)` |
| - | 0x2E6426C |  | `public LTDescr setOnUpdateObject(Action<float, object> onUpdate)` |
| - | 0x2E6429C |  | `public LTDescr setOnUpdateVector2(Action<Vector2> onUpdate)` |
| - | 0x2E642CC |  | `public LTDescr setOnUpdateVector3(Action<Vector3> onUpdate)` |
| - | 0x2E642FC |  | `public LTDescr setOnUpdateColor(Action<Color> onUpdate)` |
| - | 0x2E6432C |  | `public LTDescr setOnUpdateColor(Action<Color, object> onUpdate)` |
| - | 0x2E6435C |  | `public LTDescr setOnUpdate(Action<Color> onUpdate)` |
| - | 0x2E6438C |  | `public LTDescr setOnUpdate(Action<Color, object> onUpdate)` |
| - | 0x2E643BC |  | `public LTDescr setOnUpdate(Action<float, object> onUpdate, object onUpdateParam)` |
| - | 0x2E64410 |  | `public LTDescr setOnUpdate(Action<Vector3, object> onUpdate, object onUpdateParam)` |
| - | 0x2E64464 |  | `public LTDescr setOnUpdate(Action<Vector2> onUpdate, object onUpdateParam)` |
| - | 0x2E644B8 |  | `public LTDescr setOnUpdate(Action<Vector3> onUpdate, object onUpdateParam)` |
| - | 0x2E6450C |  | `public LTDescr setOnUpdateParam(object onUpdateParam)` |
| - | 0x2E64534 |  | `public LTDescr setOrientToPath(bool doesOrient)` |
| - | 0x2E64600 |  | `public LTDescr setOrientToPath2d(bool doesOrient2d)` |
| - | 0x2E6465C |  | `public LTDescr setRect(LTRect rect)` |
| - | 0x2E64684 |  | `public LTDescr setRect(Rect rect)` |
| - | 0x2E64724 |  | `public LTDescr setPath(LTBezierPath path)` |
| - | 0x2E6474C |  | `public LTDescr setPoint(Vector3 point)` |
| - | 0x2E6476C |  | `public LTDescr setDestroyOnComplete(bool doesDestroy)` |
| - | 0x2E64778 |  | `public LTDescr setAudio(object audio)` |
| - | 0x2E64054 |  | `public LTDescr setOnCompleteOnRepeat(bool isOn)` |
| - | 0x2E647A0 |  | `public LTDescr setOnCompleteOnStart(bool isOn)` |
| - | 0x2E647AC |  | `public LTDescr setRect(RectTransform rect)` |
| - | 0x2E647C8 |  | `public LTDescr setSprites(Sprite[] sprites)` |
| - | 0x2E647E4 |  | `public LTDescr setFrameRate(float frameRate)` |
| - | 0x2E6480C |  | `public LTDescr setOnStart(Action onStart)` |
| - | 0x2E64834 |  | `public LTDescr setDirection(float direction)` |
| - | 0x2E6497C |  | `public LTDescr setRecursive(bool useRecursion)` |
| - | 0x2E64988 |  | `private void <setMoveX>b__73_0()` |
| - | 0x2E649B0 |  | `private void <setMoveX>b__73_1()` |
| - | 0x2E64A2C |  | `private void <setMoveY>b__74_0()` |
| - | 0x2E64A54 |  | `private void <setMoveY>b__74_1()` |
| - | 0x2E64ACC |  | `private void <setMoveZ>b__75_0()` |
| - | 0x2E64AF4 |  | `private void <setMoveZ>b__75_1()` |
| - | 0x2E64B70 |  | `private void <setMoveLocalX>b__76_0()` |
| - | 0x2E64B98 |  | `private void <setMoveLocalX>b__76_1()` |
| - | 0x2E64C14 |  | `private void <setMoveLocalY>b__77_0()` |
| - | 0x2E64C3C |  | `private void <setMoveLocalY>b__77_1()` |
| - | 0x2E64CB4 |  | `private void <setMoveLocalZ>b__78_0()` |
| - | 0x2E64CDC |  | `private void <setMoveLocalZ>b__78_1()` |
| - | 0x2E64D58 |  | `private void <setMoveCurved>b__81_0()` |
| - | 0x2E64E20 |  | `private void <setMoveCurvedLocal>b__82_0()` |
| - | 0x2E64EE8 |  | `private void <setMoveSpline>b__83_0()` |
| - | 0x2E64FB0 |  | `private void <setMoveSplineLocal>b__84_0()` |
| - | 0x2E65078 |  | `private void <setScaleX>b__85_0()` |
| - | 0x2E650A0 |  | `private void <setScaleX>b__85_1()` |
| - | 0x2E6511C |  | `private void <setScaleY>b__86_0()` |
| - | 0x2E65144 |  | `private void <setScaleY>b__86_1()` |
| - | 0x2E651BC |  | `private void <setScaleZ>b__87_0()` |
| - | 0x2E651E4 |  | `private void <setScaleZ>b__87_1()` |
| - | 0x2E65260 |  | `private void <setRotateX>b__88_0()` |
| - | 0x2E652EC |  | `private void <setRotateX>b__88_1()` |
| - | 0x2E65368 |  | `private void <setRotateY>b__89_0()` |
| - | 0x2E653F4 |  | `private void <setRotateY>b__89_1()` |
| - | 0x2E6546C |  | `private void <setRotateZ>b__90_0()` |
| - | 0x2E654F8 |  | `private void <setRotateZ>b__90_1()` |
| - | 0x2E65574 |  | `private void <setRotateAround>b__91_0()` |
| - | 0x2E655AC |  | `private void <setRotateAround>b__91_1()` |
| - | 0x2E65750 |  | `private void <setRotateAroundLocal>b__92_0()` |
| - | 0x2E65788 |  | `private void <setRotateAroundLocal>b__92_1()` |
| - | 0x2E659A8 |  | `private void <setAlpha>b__93_0()` |
| - | 0x2E65FC0 |  | `private void <setAlpha>b__93_2()` |
| - | 0x2E660FC |  | `private void <setAlpha>b__93_1()` |
| - | 0x2E66248 |  | `private void <setTextAlpha>b__94_0()` |
| - | 0x2E6630C |  | `private void <setTextAlpha>b__94_1()` |
| - | 0x2E6634C |  | `private void <setAlphaVertex>b__95_0()` |
| - | 0x2E663D4 |  | `private void <setAlphaVertex>b__95_1()` |
| - | 0x2E665C8 |  | `private void <setColor>b__96_0()` |
| - | 0x2E66B7C |  | `private void <setColor>b__96_1()` |
| - | 0x2E66D4C |  | `private void <setCallbackColor>b__97_0()` |
| - | 0x2E66D60 |  | `private void <setCallbackColor>b__97_1()` |
| - | 0x2E66F30 |  | `private void <setTextColor>b__98_0()` |
| - | 0x2E67004 |  | `private void <setTextColor>b__98_1()` |
| - | 0x2E67148 |  | `private void <setCanvasAlpha>b__99_0()` |
| - | 0x2E67274 |  | `private void <setCanvasAlpha>b__99_1()` |
| - | 0x2E673FC |  | `private void <setCanvasGroupAlpha>b__100_0()` |
| - | 0x2E67460 |  | `private void <setCanvasGroupAlpha>b__100_1()` |
| - | 0x2E674DC |  | `private void <setCanvasColor>b__101_0()` |
| - | 0x2E67618 |  | `private void <setCanvasColor>b__101_1()` |
| - | 0x2E677D0 |  | `private void <setCanvasMoveX>b__102_0()` |
| - | 0x2E677F8 |  | `private void <setCanvasMoveX>b__102_1()` |
| - | 0x2E6785C |  | `private void <setCanvasMoveY>b__103_0()` |
| - | 0x2E67884 |  | `private void <setCanvasMoveY>b__103_1()` |
| - | 0x2E678EC |  | `private void <setCanvasMoveZ>b__104_0()` |
| - | 0x2E67914 |  | `private void <setCanvasMoveZ>b__104_1()` |
| - | 0x2E6797C |  | `private void <setCanvasRotateAround>b__106_0()` |
| - | 0x2E67AF8 |  | `private void <setCanvasRotateAroundLocal>b__107_0()` |
| - | 0x2E67CDC |  | `private void <setCanvasPlaySprite>b__108_0()` |
| - | 0x2E67D44 |  | `private void <setCanvasPlaySprite>b__108_1()` |
| - | 0x2E67E84 |  | `private void <setCanvasMove>b__109_0()` |
| - | 0x2E67EB0 |  | `private void <setCanvasMove>b__109_1()` |
| - | 0x2E67EE8 |  | `private void <setCanvasScale>b__110_0()` |
| - | 0x2E67F14 |  | `private void <setCanvasScale>b__110_1()` |
| - | 0x2E67F4C |  | `private void <setCanvasSizeDelta>b__111_0()` |
| - | 0x2E67F78 |  | `private void <setCanvasSizeDelta>b__111_1()` |
| - | 0x2E67FB0 |  | `private void <setMove>b__115_0()` |
| - | 0x2E67FDC |  | `private void <setMove>b__115_1()` |
| - | 0x2E68060 |  | `private void <setMoveLocal>b__116_0()` |
| - | 0x2E6808C |  | `private void <setMoveLocal>b__116_1()` |
| - | 0x2E68110 |  | `private void <setMoveToTransform>b__117_0()` |
| - | 0x2E6813C |  | `private void <setMoveToTransform>b__117_1()` |
| - | 0x2E68210 |  | `private void <setRotate>b__118_0()` |
| - | 0x2E682D4 |  | `private void <setRotate>b__118_1()` |
| - | 0x2E68358 |  | `private void <setRotateLocal>b__119_0()` |
| - | 0x2E6841C |  | `private void <setRotateLocal>b__119_1()` |
| - | 0x2E684A0 |  | `private void <setScale>b__120_0()` |
| - | 0x2E684CC |  | `private void <setScale>b__120_1()` |
| - | 0x2E68550 |  | `private void <setGUIMove>b__121_0()` |
| - | 0x2E685A0 |  | `private void <setGUIMove>b__121_1()` |
| - | 0x2E68624 |  | `private void <setGUIMoveMargin>b__122_0()` |
| - | 0x2E68650 |  | `private void <setGUIMoveMargin>b__122_1()` |
| - | 0x2E68690 |  | `private void <setGUIScale>b__123_0()` |
| - | 0x2E686E0 |  | `private void <setGUIScale>b__123_1()` |
| - | 0x2E68764 |  | `private void <setGUIAlpha>b__124_0()` |
| - | 0x2E6878C |  | `private void <setGUIAlpha>b__124_1()` |
| - | 0x2E687C8 |  | `private void <setGUIRotate>b__125_0()` |
| - | 0x2E68818 |  | `private void <setGUIRotate>b__125_1()` |
| - | 0x2E68854 |  | `private void <setDelayedSound>b__126_0()` |

</details>

### public class `LTDescrOptional`  
`TypeDefIndex 2975`

| offset | field |
|---|---|
| - | `private Transform <toTrans>k__BackingField;` |
| - | `private Vector3 <point>k__BackingField;` |
| - | `private Vector3 <axis>k__BackingField;` |
| - | `private float <lastVal>k__BackingField;` |
| - | `private Quaternion <origRotation>k__BackingField;` |
| - | `private LTBezierPath <path>k__BackingField;` |
| - | `private LTSpline <spline>k__BackingField;` |
| - | `public AnimationCurve animationCurve;` |
| - | `public int initFrameCount;` |
| - | `public Color color;` |
| - | `private LTRect <ltRect>k__BackingField;` |
| - | `private Action<float> <onUpdateFloat>k__BackingField;` |
| - | `private Action<float, float> <onUpdateFloatRatio>k__BackingField;` |
| - | `private Action<float, object> <onUpdateFloatObject>k__BackingField;` |
| - | `private Action<Vector2> <onUpdateVector2>k__BackingField;` |
| - | `private Action<Vector3> <onUpdateVector3>k__BackingField;` |
| - | `private Action<Vector3, object> <onUpdateVector3Object>k__BackingField;` |
| - | `private Action<Color> <onUpdateColor>k__BackingField;` |
| - | `private Action<Color, object> <onUpdateColorObject>k__BackingField;` |
| - | `private Action <onComplete>k__BackingField;` |
| - | `private Action<object> <onCompleteObject>k__BackingField;` |
| - | `private object <onCompleteParam>k__BackingField;` |
| - | `private object <onUpdateParam>k__BackingField;` |
| - | `private Action <onStart>k__BackingField;` |

Properties: `public Transform toTrans { get; set; }`; `public Vector3 point { get; set; }`; `public Vector3 axis { get; set; }`; `public float lastVal { get; set; }`; `public Quaternion origRotation { get; set; }`; `public LTBezierPath path { get; set; }`; `public LTSpline spline { get; set; }`; `public LTRect ltRect { get; set; }`; `public Action<float> onUpdateFloat { get; set; }`; `public Action<float, float> onUpdateFloatRatio { get; set; }`; `public Action<float, object> onUpdateFloatObject { get; set; }`; `public Action<Vector2> onUpdateVector2 { get; set; }`; `public Action<Vector3> onUpdateVector3 { get; set; }`; `public Action<Vector3, object> onUpdateVector3Object { get; set; }`; `public Action<Color> onUpdateColor { get; set; }`; `public Action<Color, object> onUpdateColorObject { get; set; }`; `public Action onComplete { get; set; }`; `public Action<object> onCompleteObject { get; set; }`; `public object onCompleteParam { get; set; }`; `public object onUpdateParam { get; set; }`; `public Action onStart { get; set; }`

<details><summary>methods (45)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E68AB0 |  | `public Transform get_toTrans()` |
| - | 0x2E68AB8 |  | `public void set_toTrans(Transform value)` |
| - | 0x2E68AC0 |  | `public Vector3 get_point()` |
| - | 0x2E68ACC |  | `public void set_point(Vector3 value)` |
| - | 0x2E68AD8 |  | `public Vector3 get_axis()` |
| - | 0x2E68AE4 |  | `public void set_axis(Vector3 value)` |
| - | 0x2E68AF0 |  | `public float get_lastVal()` |
| - | 0x2E68AF8 |  | `public void set_lastVal(float value)` |
| - | 0x2E68B00 |  | `public Quaternion get_origRotation()` |
| - | 0x2E68B0C |  | `public void set_origRotation(Quaternion value)` |
| - | 0x2E68B18 |  | `public LTBezierPath get_path()` |
| - | 0x2E68B20 |  | `public void set_path(LTBezierPath value)` |
| - | 0x2E68B28 |  | `public LTSpline get_spline()` |
| - | 0x2E68B30 |  | `public void set_spline(LTSpline value)` |
| - | 0x2E68B38 |  | `public LTRect get_ltRect()` |
| - | 0x2E68B40 |  | `public void set_ltRect(LTRect value)` |
| - | 0x2E68B48 |  | `public Action<float> get_onUpdateFloat()` |
| - | 0x2E68B50 |  | `public void set_onUpdateFloat(Action<float> value)` |
| - | 0x2E68B58 |  | `public Action<float, float> get_onUpdateFloatRatio()` |
| - | 0x2E68B60 |  | `public void set_onUpdateFloatRatio(Action<float, float> value)` |
| - | 0x2E68B68 |  | `public Action<float, object> get_onUpdateFloatObject()` |
| - | 0x2E68B70 |  | `public void set_onUpdateFloatObject(Action<float, object> value)` |
| - | 0x2E68B78 |  | `public Action<Vector2> get_onUpdateVector2()` |
| - | 0x2E68B80 |  | `public void set_onUpdateVector2(Action<Vector2> value)` |
| - | 0x2E68B88 |  | `public Action<Vector3> get_onUpdateVector3()` |
| - | 0x2E68B90 |  | `public void set_onUpdateVector3(Action<Vector3> value)` |
| - | 0x2E68B98 |  | `public Action<Vector3, object> get_onUpdateVector3Object()` |
| - | 0x2E68BA0 |  | `public void set_onUpdateVector3Object(Action<Vector3, object> value)` |
| - | 0x2E68BA8 |  | `public Action<Color> get_onUpdateColor()` |
| - | 0x2E68BB0 |  | `public void set_onUpdateColor(Action<Color> value)` |
| - | 0x2E68BB8 |  | `public Action<Color, object> get_onUpdateColorObject()` |
| - | 0x2E68BC0 |  | `public void set_onUpdateColorObject(Action<Color, object> value)` |
| - | 0x2E68BC8 |  | `public Action get_onComplete()` |
| - | 0x2E68BD0 |  | `public void set_onComplete(Action value)` |
| - | 0x2E68BD8 |  | `public Action<object> get_onCompleteObject()` |
| - | 0x2E68BE0 |  | `public void set_onCompleteObject(Action<object> value)` |
| - | 0x2E68BE8 |  | `public object get_onCompleteParam()` |
| - | 0x2E68BF0 |  | `public void set_onCompleteParam(object value)` |
| - | 0x2E68BF8 |  | `public object get_onUpdateParam()` |
| - | 0x2E68C00 |  | `public void set_onUpdateParam(object value)` |
| - | 0x2E68C08 |  | `public Action get_onStart()` |
| - | 0x2E68C10 |  | `public void set_onStart(Action value)` |
| - | 0x2E68C18 |  | `public void reset()` |
| - | 0x2E68D30 |  | `public void callOnUpdate(float val, float ratioPassed)` |
| - | 0x2E68E94 |  | `public void .ctor()` |

</details>

### public class `LTSeq`  
`TypeDefIndex 2976`

| offset | field |
|---|---|
| - | `public LTSeq previous;` |
| - | `public LTSeq current;` |
| - | `public LTDescr tween;` |
| - | `public float totalDelay;` |
| - | `public float timeScale;` |
| - | `private int debugIter;` |
| - | `public uint counter;` |
| - | `public bool toggle;` |
| - | `private uint _id;` |

Properties: `public int id { get; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2E68E9C |  | `public int get_id()` |
| - | 0x2E68EAC |  | `public void reset()` |
| - | 0x2E68EDC |  | `public void init(uint id, uint global_counter)` |
| - | 0x2E68F30 |  | `private LTSeq addOn()` |
| - | 0x2E68FE4 |  | `private float addPreviousDelays()` |
| - | 0x2E69020 |  | `public LTSeq append(float delay)` |
| - | 0x2E69044 |  | `public LTSeq append(Action callback)` |
| - | 0x2E6911C |  | `public LTSeq append(Action<object> callback, object obj)` |
| - | 0x2E691B0 |  | `public LTSeq append(GameObject gameObject, Action callback)` |
| - | 0x2E69234 |  | `public LTSeq append(GameObject gameObject, Action<object> callback, object obj)` |
| - | 0x2E690B8 |  | `public LTSeq append(LTDescr tween)` |
| - | 0x2E692D8 |  | `public LTSeq insert(LTDescr tween)` |
| - | 0x2E69324 |  | `public LTSeq setScale(float timeScale)` |
| - | 0x2E69344 |  | `private void setScaleRecursive(LTSeq seq, float timeScale, int count)` |
| - | 0x2E693D8 |  | `public LTSeq reverse()` |
| - | 0x2E693DC |  | `public void .ctor()` |

</details>
