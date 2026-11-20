# namespace `ManeFunction.DOTweenExtensions`  (1 types)

### public class `DOTweenUIController` : UIBehaviour  
`TypeDefIndex 3967`

| offset | field |
|---|---|
| - | `private bool _autoplay;` |
| - | `private bool _createOnStart;` |
| - | `private bool _restartOnEnable;` |
| - | `private bool _pauseOnDisable;` |
| - | `private bool _finishOnStop;` |
| - | `private bool _unscaledTime;` |
| - | `private DOTweenUIController.FloatData _moveX;` |
| - | `private DOTweenUIController.FloatData _moveY;` |
| - | `private DOTweenUIController.FloatData _scaleX;` |
| - | `private DOTweenUIController.FloatData _scaleY;` |
| - | `private DOTweenUIController.FloatData _rotate;` |
| - | `private DOTweenUIController.FloatData _fade;` |
| - | `private DOTweenUIController.ColorData _color;` |
| - | `private readonly List<Tween> active;` |
| - | `private bool started;` |

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F80200 |  | `protected override void Start()` |
| - | 0x2F806DC |  | `protected override void OnEnable()` |
| - | 0x2F80880 |  | `protected override void OnDisable()` |
| - | 0x2F809FC |  | `protected override void OnDestroy()` |
| - | 0x2F80B84 |  | `private void Add(DOTweenUIController.FloatData data, Func<float, float, Tweener> factory, float delay)` |
| - | 0x2F80CF4 |  | `private void AddLoop(Tween t, float delay, int loops, float interval, LoopType loopType)` |
| - | 0x2F80238 |  | `private void CreateTweeners(float delay = 0)` |
| - | 0x2F81048 |  | `public void Play(float delay = 0)` |
| - | 0x2F808A8 |  | `public void Pause()` |
| - | 0x2F811D0 |  | `public void Stop()` |
| - | 0x2F80710 |  | `public void Restart()` |
| - | 0x2F81338 |  | `public void SetTweenEnabled(DOTweenUIController.TweenType type, bool enabled)` |
| - | 0x2F813C0 |  | `public void .ctor()` |

</details>
