# namespace `Oxide.InputSystem`  (5 types)

### public class `Axis`  
`TypeDefIndex 2980`

| offset | field |
|---|---|
| 0x10 | `private string m_AxisName;` |
| 0x18 | `private bool m_Normalize;` |
| 0x1C | `private Lf.Tx m_AxisType;` |
| 0x20 | `private string m_UnityAxisName;` |
| 0x28 | `private KeyCode m_PositiveKey;` |
| 0x2C | `private KeyCode m_NegativeKey;` |

Properties: `public string sIx { get; set; }`; `public Lf.Tx sIK { get; }`; `public string sIG { get; }`; `public KeyCode sIP { get; }`; `public KeyCode sID { get; }`; `public bool sIn { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A7CAB0 | 0x2E69414 |  | `public string get_sIx()` |
| 0x3A7CAB8 | 0x2E6941C |  | `public void set_sIx(string value)` |
| 0x3A7CAC0 | 0x2E69420 |  | `public Lf.Tx get_sIK()` |
| 0x3A7CAC8 | 0x2E69428 |  | `public string get_sIG()` |
| 0x3A7CAD0 | 0x2E69430 |  | `public KeyCode get_sIP()` |
| 0x3A7CAD8 | 0x2E69438 |  | `public KeyCode get_sID()` |
| 0x3A7CAE0 | 0x2E69440 |  | `public bool get_sIn()` |
| 0x3A7CAE8 | 0x2E69448 |  | `public void .ctor(string name, Lf.Tx axisType)` |
| 0x3A7CB24 | 0x2E69450 |  | `public void .ctor(string name, Lf.Tx axisType, Joystick joystick)` |
| 0x3A7CB60 | 0x2E69458 |  | `public void .ctor(string name, Lf.Tx axisType, string unityAxisName)` |
| 0x3A7CBB4 | 0x2E69460 |  | `public void .ctor(string name, Lf.Tx axisType, KeyCode positiveKey, KeyCode negativeKey, string unityAxisName)` |

</details>

### public class `Button`  
`TypeDefIndex 2981`

| offset | field |
|---|---|
| 0x10 | `private string m_ButtonName;` |
| 0x18 | `private KeyCode m_Key;` |

Properties: `public string sIV { get; set; }`; `public KeyCode sIg { get; }`

<details><summary>methods (6)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A7CC1C | 0x2E69468 |  | `public string get_sIV()` |
| 0x3A7CC24 | 0x2E69470 |  | `public void set_sIV(string value)` |
| 0x3A7CC2C | 0x2E69474 |  | `public KeyCode get_sIg()` |
| 0x3A7CC34 | 0x2E6947C |  | `public void .ctor(string name)` |
| 0x3A7CC64 | 0x2E69484 |  | `public void .ctor(string name, KeyCode key)` |
| 0x3A7CCA0 | 0x2E6948C |  | `public void .ctor(string name, yY handler)` |

</details>

### public class `InputData` : ScriptableObject  
`TypeDefIndex 2982`

| offset | field |
|---|---|
| 0x18 | `private Lf.Tb m_InputType;` |
| 0x20 | `private List<Button> m_Buttons;` |
| 0x28 | `private List<Axis> m_Axes;` |

Properties: `public Lf.Tb sIp { get; }`; `public List<Button> sIv { get; }`; `public List<Axis> sIS { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A7CEC0 | 0x2E69494 |  | `public Lf.Tb get_sIp()` |
| 0x3A7CEC8 | 0x2E6949C |  | `public List<Button> get_sIv()` |
| 0x3A7CED0 | 0x2E694A4 |  | `public List<Axis> get_sIS()` |
| 0x3A7CED8 | 0x2E694AC |  | `public void .ctor()` |

</details>

### public class `InputManager` : MonoBehaviour  
`TypeDefIndex 2983`

| offset | field |
|---|---|
| 0x20 | `private InputData m_InputData;` |

Properties: `public InputData sII { get; set; }`

<details><summary>methods (17)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A7CFB4 | 0x2E694B4 |  | `public InputData get_sII()` |
| 0x3A7CFBC | 0x2E694BC |  | `public void set_sII(InputData value)` |
| 0x3A7CFC4 | 0x2E694C0 |  | `public void UFy(Lf.Tb e, Lf.Tl f)` |
| 0x3A7D2CC | 0x2E694C4 |  | `private void UFz()` |
| 0x3A7D4D0 | 0x2E694C8 |  | `public void UFh(Lf.Tl e)` |
| 0x3A7D578 | 0x2E694CC |  | `public void UFB()` |
| 0x3A7D630 | 0x2E694D0 |  | `public float UFm(string e)` |
| 0x3A7D7E4 | 0x2E694D8 |  | `public float UFR(string e)` |
| 0x3A7D8A0 | 0x2E694E0 |  | `public bool UFb(string e)` |
| 0x3A7D9A0 | 0x2E694E8 |  | `public bool UFl(string e)` |
| 0x3A7D9C4 | 0x2E694F0 |  | `public bool UFx(string e)` |
| 0x3A7D41C | 0x2E694F8 |  | `private void UFK(Button e)` |
| 0x3A7D218 | 0x2E694FC |  | `private void UFG(Axis e)` |
| 0x3A7D8C4 | 0x2E69500 |  | `private Button UFP(string e)` |
| 0x3A7D6EC | 0x2E69508 |  | `private Axis UFD(string e)` |
| 0x3A7D7C8 | 0x2E69510 |  | `private int UFn(KeyCode e)` |
| 0x3A7D9E8 | 0x2E69518 |  | `public void .ctor()` |

</details>

### public class `Joystick` : MonoBehaviour, IPointerUpHandler, IEventSystemHandler, IPointerDownHandler, IDragHandler  
`TypeDefIndex 2984`

| offset | field |
|---|---|
| 0x20 | `private float m_MovementRange;` |
| 0x28 | `private Canvas Ovc;` |
| 0x30 | `private Vector3 OvU;` |
| 0x3C | `private Vector3 OvY;` |
| 0x48 | `private float OvW;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3A7D9F0 | 0x2E69520 |  | `private void Start()` |
| 0x3A7DA78 | 0x2E69524 | 6 | `public void OnDrag(PointerEventData data)` |
| 0x3A7DBCC | 0x2E69528 | 4 | `public void OnPointerUp(PointerEventData data)` |
| 0x3A7DC44 | 0x2E6952C | 5 | `public void OnPointerDown(PointerEventData data)` |
| 0x3A7DC48 | 0x2E69530 |  | `public float UFV()` |
| 0x3A7DC58 | 0x2E69538 |  | `public float UFg()` |
| 0x3A7DC68 | 0x2E69540 |  | `public float UFp()` |
| 0x3A7D40C | 0x2E69548 |  | `public void .ctor()` |

</details>
