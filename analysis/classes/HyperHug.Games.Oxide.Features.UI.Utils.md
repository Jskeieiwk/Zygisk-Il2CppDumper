# namespace `HyperHug.Games.Oxide.Features.UI.Utils`  (1 types)

### public class `BlobButton` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IPointerClickHandler, IPointerExitHandler  
`TypeDefIndex 3426`

| offset | field |
|---|---|
| 0x20 | `private UnityEvent OnClick;` |
| 0x28 | `private UnityEvent OnLongPress;` |
| 0x30 | `private bool _enableInput;` |
| 0x31 | `private bool _unscaledTime;` |
| 0x32 | `private bool _jumpOnEnable;` |
| 0x33 | `private bool _alwaysPulse;` |
| 0x34 | `private bool _uniformScale;` |
| 0x38 | `private float _longPressTime;` |
| 0x3C | `private float _rigidity;` |
| 0x40 | `private float _damping;` |
| 0x44 | `private float _startScale;` |
| 0x48 | `private float _minScale;` |
| 0x4C | `private float _maxScale;` |
| 0x50 | `private float _pressedScale;` |
| 0x54 | `private float _startJumpSpeed;` |
| 0x58 | `private float _pulseAmplitude;` |
| 0x5C | `private float _pulseFrequency;` |
| 0x60 | `private RectTransform kMC;` |
| 0x68 | `private Vector3 kMZ;` |
| 0x74 | `private float kMj;` |
| 0x78 | `private float kMa;` |
| 0x7C | `private float kMQ;` |
| 0x80 | `private float kMH;` |
| - | `private double blobFrames;` |
| - | `private bool blobHeld;` |
| - | `private const float kMi = 0.01;` |
| 0x84 | `private bool kMw;` |

Properties: `public Vector3 slo { get; }`; `public bool kMJ { get; set; }`

<details><summary>methods (25)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0EFAC |  | `public void AdvanceBlob(float elapsed)` |
| - | 0x2F0F31C |  | `public Vector3 get_slo()` |
| 0x380A6B4 | 0x2F0F328 |  | `public bool get_kMJ()` |
| 0x380A6BC | 0x2F0F330 |  | `private void set_kMJ(bool value)` |
| 0x380A6C8 | 0x2F0F334 |  | `public void add_kMX(Action value)` |
| 0x380A764 | 0x2F0F338 |  | `public void remove_kMX(Action value)` |
| 0x380A800 | 0x2F0F33C |  | `public void add_kMT(Action value)` |
| 0x380A89C | 0x2F0F340 |  | `public void remove_kMT(Action value)` |
| 0x380A938 | 0x2F0F344 |  | `public void add_kML(Action value)` |
| 0x380A9D4 | 0x2F0F348 |  | `public void remove_kML(Action value)` |
| 0x380AA70 | 0x2F0F34C |  | `private void Awake()` |
| 0x380AAC8 | 0x2F0F45C |  | `private void OnEnable()` |
| 0x380AACC | 0x2F0F3AC |  | `public void dJW()` |
| 0x380AB98 | 0x2F0F0D0 |  | `private void dJE()` |
| 0x380AC20 | 0x2F0F46C | 4 | `public void OnPointerDown(PointerEventData eventData)` |
| 0x380ACCC | 0x2F0F470 |  | `private void OnLongPressEvent()` |
| 0x380ACE0 | 0x2F0F474 | 6 | `public void OnPointerClick(PointerEventData eventData)` |
| 0x380AD24 | 0x2F0F478 | 5 | `public void OnPointerUp(PointerEventData eventData)` |
| 0x380ADC0 | 0x2F0F47C | 7 | `public void OnPointerExit(PointerEventData eventData)` |
| 0x380AE5C | 0x2F0F480 |  | `private void Update()` |
| 0x380AFB4 | 0x2F0F298 |  | `private bool dJA(float e)` |
| 0x380AEC0 | 0x2F0F1AC |  | `private void dJu()` |
| 0x380AB8C | 0x2F0F460 |  | `public void Jump()` |
| 0x380B038 | 0x2F0F4B0 |  | `public void dJk(bool e)` |
| 0x380B044 | 0x2F0F4B4 |  | `public void .ctor()` |

</details>
