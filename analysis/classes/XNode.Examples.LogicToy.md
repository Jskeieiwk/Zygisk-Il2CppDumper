# namespace `XNode.Examples.LogicToy`  (6 types)

### public class `AndNode` : LogicNode  
`TypeDefIndex 2666`

| offset | field |
|---|---|
| - | `public bool input;` |
| 0x39 | `public bool output;` |

Properties: `public override bool sBJ { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x373A298 | 0x2DED510 | 9 | `public override bool get_sBJ()` |
| 0x373A2A0 | 0x2DED518 | 10 | `protected override void FvP()` |
| 0x373A5B4 | 0x2DED51C | 6 | `public override object Fwo(NodePort e)` |
| 0x373A610 | 0x2DED524 |  | `public void .ctor()` |

</details>

### public class `LogicGraph` : NodeGraph  
`TypeDefIndex 2667`

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x373A290 | 0x2DED534 |  | `public void .ctor()` |

</details>

### public abstract class `LogicNode` : Node  
`TypeDefIndex 2668`

| offset | field |
|---|---|
| 0x30 | `public Action onStateChange;` |

Properties: `public abstract bool sBJ { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract bool get_sBJ();` |
| 0x373A46C | 0x2DED53C |  | `public void FvD(NodePort e)` |
| - | - |  | `protected abstract void FvP();` |
| 0x373A698 | 0x2DED540 | 7 | `public override void Fvn(NodePort e, NodePort f)` |
| 0x373A618 | 0x2DED52C |  | `protected void .ctor()` |

</details>

### public class `NotNode` : LogicNode  
`TypeDefIndex 2669`

| offset | field |
|---|---|
| 0x38 | `public bool input;` |
| 0x39 | `public bool output;` |

Properties: `public override bool sBJ { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x373A6A4 | 0x2DED544 | 9 | `public override bool get_sBJ()` |
| 0x373A6AC | 0x2DED54C | 10 | `protected override void FvP()` |
| 0x373A87C | 0x2DED550 | 6 | `public override object Fwo(NodePort e)` |
| 0x373A8D8 | 0x2DED558 |  | `public void .ctor()` |

</details>

### public class `PulseNode` : LogicNode, kQ  
`TypeDefIndex 2670`

| offset | field |
|---|---|
| 0x38 | `public float interval;` |
| 0x3C | `public bool output;` |
| 0x40 | `private float timer;` |

Properties: `public override bool sBJ { get; }`

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x373A960 | 0x2DED560 | 9 | `public override bool get_sBJ()` |
| 0x373A968 | 0x2DED568 | 11 | `public void Fvx(float e)` |
| 0x373AA2C | 0x2DED56C | 10 | `protected override void FvP()` |
| 0x373AA30 | 0x2DED570 | 6 | `public override object Fwo(NodePort e)` |
| 0x373AA8C | 0x2DED578 |  | `public void .ctor()` |

</details>

### public class `ToggleNode` : LogicNode  
`TypeDefIndex 2671`

| offset | field |
|---|---|
| 0x38 | `public bool input;` |
| 0x39 | `public bool output;` |

Properties: `public override bool sBJ { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x373AA9C | 0x2DED580 | 9 | `public override bool get_sBJ()` |
| 0x373AAA4 | 0x2DED588 | 10 | `protected override void FvP()` |
| 0x373AC84 | 0x2DED58C | 6 | `public override object Fwo(NodePort e)` |
| 0x373ACE0 | 0x2DED594 |  | `public void .ctor()` |

</details>
