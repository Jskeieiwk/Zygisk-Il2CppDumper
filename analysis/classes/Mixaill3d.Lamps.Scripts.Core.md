# namespace `Mixaill3d.Lamps.Scripts.Core`  (3 types)

### public class `LampBasicBehaviour` : ScriptableObject  
`TypeDefIndex 3221`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F72CC | 0x2ED0B44 | 4 | `public virtual void Fly(GameObject[] e, float f, float F)` |
| 0x36F738C | 0x2ED0B48 |  | `protected void Flz(Renderer e, Color f)` |
| 0x36F7440 | 0x2ED0B4C | 5 | `protected virtual void Flh(Renderer e, float f, float F)` |
| 0x36F749C | 0x2ED0B50 |  | `protected float FlB(float e, float f)` |
| 0x36F74E4 | 0x2ED0B58 |  | `public void .ctor()` |

</details>

### public class `LampsController` : uw<LampsController>  
`TypeDefIndex 3222`

| offset | field |
|---|---|
| 0x20 | `private List<LampsGroup> kod;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F74EC | 0x2ED0B60 |  | `public void Flm(LampsGroup e)` |
| 0x36F7598 | 0x2ED0B64 |  | `public void FlR(LampsGroup e)` |
| 0x36F75F0 | 0x2ED0B68 |  | `public void Update()` |
| 0x36F7764 | 0x2ED0B6C |  | `public void .ctor()` |

</details>

### public class `LampsGroup` : MonoBehaviour  
`TypeDefIndex 3223`

| offset | field |
|---|---|
| 0x20 | `private LampBasicBehaviour _behaviour;` |
| 0x28 | `private float _timeOffset;` |
| 0x2C | `private float _speed;` |
| 0x30 | `private GameObject[] _lamps;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F7800 | 0x2ED0BB4 |  | `public List<GameObject> Flb(Transform e)` |
| 0x36F7888 | 0x2ED0BBC |  | `private void Fll(Transform e, List<GameObject> f)` |
| 0x36F7C78 | 0x2ED0BC0 |  | `public void Awake()` |
| 0x36F7D68 | 0x2ED0BC4 |  | `public void OnDestroy()` |
| 0x36F7CD4 | 0x2ED0BC8 |  | `private void Flx()` |
| 0x36F7738 | 0x2ED0BCC |  | `public void FlK()` |
| 0x36F7DBC | 0x2ED0BD0 |  | `public void .ctor()` |

</details>
