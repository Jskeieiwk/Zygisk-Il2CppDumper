# namespace `DigitalRubyShared`  (9 types)

### public class `FakeTouch`  
`TypeDefIndex 3981`

| offset | field |
|---|---|
| 0x10 | `public int Id;` |
| 0x14 | `public Vector2 ScreenPosition;` |
| 0x1C | `public bool ScreenPositionIsPercentage;` |
| 0x20 | `public float Time;` |
| 0x24 | `public Ja Phase;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39BA210 | 0x2F89780 |  | `public void .ctor()` |

</details>

### public class `GestureRecognizerComponentEvent` : UnityEvent  
`TypeDefIndex 3982`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x399A9D0 | 0x2F89788 |  | `public void .ctor()` |

</details>

### public class `GestureRecognizerComponentEventVector2` : UnityEvent<Vector2>  
`TypeDefIndex 3983`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x399A9D8 | 0x2F89790 |  | `public void .ctor()` |

</details>

### public class `GestureRecognizerComponentStateUpdatedEvent` : UnityEvent<JH>  
`TypeDefIndex 3984`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x399A988 | 0x2F897D8 |  | `public void .ctor()` |

</details>

### public sealed class `GestureRecognizerStateUpdatedDelegate` : MulticastDelegate  
`TypeDefIndex 3985`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F89820 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F89928 |  | `public virtual void Invoke(JH gesture)` |
| - | 0x2F8993C |  | `public virtual IAsyncResult BeginInvoke(JH gesture, AsyncCallback callback, object object)` |
| - | 0x2F8995C |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public sealed class `GestureRecognizerUpdated` : MulticastDelegate  
`TypeDefIndex 3986`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F89968 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F89A74 |  | `public virtual void Invoke(JH gesture, ICollection<GestureTouch> touches)` |
| - | 0x2F89A88 |  | `public virtual IAsyncResult BeginInvoke(JH gesture, ICollection<GestureTouch> touches, AsyncCallback callback, object object)` |
| - | 0x2F89AB0 |  | `public virtual void EndInvoke(IAsyncResult result)` |

</details>

### public struct `GestureTouch` : IComparable<GestureTouch>  
`TypeDefIndex 3987`

| offset | field |
|---|---|
| 0x0 | `private readonly int OoK;` |
| 0x4 | `private readonly float OoG;` |
| 0x8 | `private readonly float OoP;` |
| 0xC | `private readonly float OoD;` |
| 0x10 | `private readonly float Oon;` |
| 0x14 | `private readonly float OoV;` |
| 0x18 | `private readonly object Oog;` |
| 0x20 | `private readonly Ja Oop;` |

Properties: `public int snh { get; }`; `public float snB { get; }`; `public float snm { get; }`; `public float snR { get; }`; `public float snb { get; }`; `public float snl { get; }`; `public float snx { get; }`; `public float snK { get; }`; `public float snG { get; }`; `public float snP { get; }`; `public object snD { get; }`; `public Ja snn { get; }`

<details><summary>methods (16)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39BA710 | 0x2F89ABC |  | `public int get_snh()` |
| 0x39BA718 | 0x2F89AC4 |  | `public float get_snB()` |
| 0x39BA720 | 0x2F89ACC |  | `public float get_snm()` |
| 0x39BA728 | 0x2F89AD4 |  | `public float get_snR()` |
| 0x39BA730 | 0x2F89ADC |  | `public float get_snb()` |
| 0x39BA738 | 0x2F89AE4 |  | `public float get_snl()` |
| 0x39BA740 | 0x2F89AEC |  | `public float get_snx()` |
| 0x39BA748 | 0x2F89AF4 |  | `public float get_snK()` |
| 0x39BA750 | 0x2F89AFC |  | `public float get_snG()` |
| 0x39BA760 | 0x2F89B04 |  | `public float get_snP()` |
| 0x39BA770 | 0x2F89B0C |  | `public object get_snD()` |
| 0x39BA778 | 0x2F89B14 |  | `public Ja get_snn()` |
| 0x39BA648 | 0x2F89B1C |  | `public void .ctor(int platformSpecificId, float screenX, float screenY, float previousX, float previousY, float pressure = 1, object platformSpecificTouch, Ja touchPhase)` |
| 0x39BA684 | 0x2F89B2C | 4 | `public int CompareTo(GestureTouch other)` |
| 0x39BA690 | 0x2F89B34 | 2 | `public override int GetHashCode()` |
| 0x39BA698 | 0x2F89B3C | 0 | `public override bool Equals(object obj)` |

</details>

### public struct `ImageGestureRecognizerComponentScriptImageEntry`  
`TypeDefIndex 3988`

| offset | field |
|---|---|
| 0x0 | `public string Key;` |
| 0x8 | `public float ScorePadding;` |
| 0x10 | `public string Images;` |
| 0x18 | `public string Description;` |

### public class `MinMaxSliderAttribute` : PropertyAttribute  
`TypeDefIndex 3989`

Properties: `public float OhG { get; set; }`; `public float OhP { get; set; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x39D21D0 | 0x2F89B44 |  | `public float get_OhG()` |
| 0x39D21D8 | 0x2F89B4C |  | `private void set_OhG(float value)` |
| 0x39D21E0 | 0x2F89B50 |  | `public float get_OhP()` |
| 0x39D21E8 | 0x2F89B58 |  | `private void set_OhP(float value)` |
| 0x39D21F0 | 0x2F89B5C |  | `public void .ctor()` |
| 0x39D2214 | 0x2F89B64 |  | `public void .ctor(float min, float max)` |

</details>
