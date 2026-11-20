# namespace `HyperHug.Games.Oxide.Features.Interactables`  (3 types)

### public class `Jukebox` : Xb  
`TypeDefIndex 3698`

| offset | field |
|---|---|
| 0x80 | `private AudioSource audioSource;` |
| 0x88 | `private AudioClip[] audioClips;` |
| 0x90 | `private BuildingPiece piece;` |
| 0x98 | `private JukeboxAudioVisual jukeboxAudioVisual;` |
| 0xA0 | `public byte state;` |
| 0xA4 | `public float seconds;` |
| 0xA8 | `private byte Oqs;` |
| 0xB0 | `private double OqC;` |
| 0xB8 | `private float OqZ;` |

Properties: `private int sDd { get; }`; `private QG sDc { get; }`; `public byte sDU { get; set; }`; `public float sDY { get; set; }`

<details><summary>methods (14)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F666E8 |  | `private int get_sDd()` |
| - | 0x2F66700 |  | `private QG get_sDc()` |
| - | 0x2F6670C |  | `public byte get_sDU()` |
| - | 0x2F66714 |  | `public void set_sDU(byte value)` |
| - | 0x2F6671C |  | `public float get_sDY()` |
| - | 0x2F66724 |  | `public void set_sDY(float value)` |
| 0x38DAA40 | 0x2F6672C | 27 | `public override void Fae(PlayerManager e)` |
| 0x38DAA44 | 0x2F66730 |  | `private void ceD()` |
| 0x38DAD78 | 0x2F66BB0 |  | `private void Update()` |
| 0x38DAEDC | 0x2F66BC8 | 11 | `public override void Fsv()` |
| 0x38DAEF8 | 0x2F66BE4 |  | `public void .ctor()` |
| 0x38DAF00 | 0x2F66BEC | 12 | `public override bool Fuk()` |
| 0x38DAFD0 | 0x2F66BF4 | 5 | `protected override void FCk(vx e, bool f)` |
| 0x38DB05C | 0x2F66C50 | 15 | `protected override void FCO(vo e, bool f)` |

</details>

### public class `JukeboxAudioVisual` : MonoBehaviour  
`TypeDefIndex 3701`

| offset | field |
|---|---|
| - | `private readonly float[] recoveredSamples;` |
| - | `private Coroutine recoveredLightFade;` |
| 0x20 | `private Renderer firstLodRenderer;` |
| 0x28 | `private GameObject lightEffects;` |
| 0x30 | `private AudioSource audioSource;` |
| 0x38 | `private float maxAmplitude;` |
| 0x40 | `private Renderer renderer;` |
| 0x48 | `private JukeboxFlare jukeboxFlare;` |
| 0x50 | `private float[] speed;` |
| 0x58 | `private LODGroup lodGroup;` |
| 0x60 | `private float multiplier;` |
| 0x64 | `private bool Oqa;` |
| 0x68 | `private Material OqQ;` |
| 0x0 | `private static readonly int OqH;` |
| 0x4 | `private static readonly int Oqi;` |
| 0x70 | `private CancellationTokenSource Oqw;` |
| 0x8 | `private static readonly int OqJ;` |
| 0x78 | `private Camera OqX;` |
| 0x80 | `public float maxDistance;` |

<details><summary>methods (12)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F66CC0 |  | `private static void .cctor()` |
| - | 0x2F66D88 |  | `private void BeginLightFade(float target)` |
| - | 0x2F66E58 |  | `private IEnumerator FadeLight(float target)` |
| - | 0x2F66EFC |  | `private void OnDestroy()` |
| 0x38DB174 | 0x2F66FC0 |  | `private void Awake()` |
| 0x38DABE0 | 0x2F669D0 |  | `public void cev()` |
| 0x38DAB14 | 0x2F6693C |  | `public void ceS()` |
| 0x38DACB0 | 0x2F66A68 |  | `public void ceI(int e)` |
| 0x38DB34C | 0x2F673E0 |  | `private UniTaskVoid ceM(bool e, CancellationToken f)` |
| 0x38DB480 | 0x2F67474 |  | `private void Update()` |
| 0x38DB654 | 0x2F677A8 |  | `private float cfe()` |
| 0x38DB738 | 0x2F678AC |  | `public void .ctor()` |

</details>

### public class `JukeboxFlare` : MonoBehaviour  
`TypeDefIndex 3702`

| offset | field |
|---|---|
| 0x20 | `private MeshRenderer[] flares;` |
| 0x28 | `private Transform flaresParent;` |
| 0x30 | `private Gradient gradientColor;` |
| 0x38 | `private Light lightColor;` |
| 0x40 | `public float speed;` |
| 0x44 | `public float brighness;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38DB320 | 0x2F67268 |  | `public void cff()` |
| 0x38DB41C | 0x2F672F8 |  | `public void cfF()` |
| 0x38DBB88 | 0x2F67B70 |  | `private void Update()` |
| 0x38DBDA4 | 0x2F67E20 |  | `public void .ctor()` |

</details>
