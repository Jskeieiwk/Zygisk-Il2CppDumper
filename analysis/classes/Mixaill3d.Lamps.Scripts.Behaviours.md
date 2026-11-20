# namespace `Mixaill3d.Lamps.Scripts.Behaviours`  (4 types)

### public class `ColorChangeOverTime` : LampBasicBehaviour  
`TypeDefIndex 3224`

| offset | field |
|---|---|
| 0x18 | `protected Gradient _gradient;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F7DCC | 0x2ED0BD8 | 5 | `protected override void Flh(Renderer e, float f, float F)` |
| 0x36F7E3C | 0x2ED0BDC |  | `public void .ctor()` |

</details>

### public class `EveryColorChangeOverTime` : LampBasicBehaviour  
`TypeDefIndex 3225`

| offset | field |
|---|---|
| 0x18 | `protected Gradient[] _gradients;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F7E44 | 0x2ED0BE4 | 5 | `protected override void Flh(Renderer e, float f, float F)` |
| 0x36F7EF8 | 0x2ED0BE8 |  | `public void .ctor()` |

</details>

### public class `FromTextureColorChanging` : LampBasicBehaviour  
`TypeDefIndex 3226`

| offset | field |
|---|---|
| 0x18 | `private int _frameWidth;` |
| 0x1C | `private int _frameHeight;` |
| 0x20 | `private Texture2D texture;` |

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F7F00 | 0x2ED0BF0 | 5 | `protected override void Flh(Renderer e, float f, float F)` |
| 0x36F8020 | 0x2ED0BF4 |  | `public void .ctor()` |

</details>

### public class `SmoothFromTextureColorChanging` : LampBasicBehaviour  
`TypeDefIndex 3227`

| offset | field |
|---|---|
| 0x18 | `private int _frameWidth;` |
| 0x1C | `private int _frameHeight;` |
| 0x20 | `private Texture2D texture;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x36F8028 | 0x2ED0BFC | 5 | `protected override void Flh(Renderer e, float f, float F)` |
| 0x36F8188 | 0x2ED0C00 |  | `private Color FlD(Renderer e, int f, int F)` |
| 0x36F8200 | 0x2ED0C14 |  | `public void .ctor()` |

</details>
