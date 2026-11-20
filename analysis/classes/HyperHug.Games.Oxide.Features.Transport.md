# namespace `HyperHug.Games.Oxide.Features.Transport`  (33 types)

### public enum `AirKind`  
`TypeDefIndex 3483`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const AirKind Helicopter = 0;` |
| - | `public const AirKind Fighter = 1;` |

### public static class `AirBodies`  
`TypeDefIndex 3484`

| offset | field |
|---|---|
| - | `private static readonly List<Collider[]> bodies;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F18C90 |  | `public static void Add(Collider[] colliders)` |
| - | 0x2F18D64 |  | `public static void Remove(Collider[] colliders)` |
| - | 0x2F18DE4 |  | `public static void IgnoreProjectile(GameObject projectile)` |
| - | 0x2F190F4 |  | `private static void .cctor()` |

</details>

### public sealed class `AircraftController` : MonoBehaviour  
`TypeDefIndex 3485`

| offset | field |
|---|---|
| - | `public const int NetValues = 6;` |
| - | `public const float GunRate = 7;` |
| - | `public const float GunReload = 5;` |
| - | `public const int GunRounds = 1000;` |
| - | `private const float Gravity = 9.81;` |
| - | `private const float DryThrust = 6.5;` |
| - | `private const float BurnerThrust = 7;` |
| - | `private const float ParasiticDrag = 0.0004;` |
| - | `private const float LiftSlope = 0.0005;` |
| - | `private const float StallAngle = 18;` |
| - | `private const float FighterPitchRate = 72;` |
| - | `private const float FighterRollRate = 280;` |
| - | `private const float FighterYawRate = 16;` |
| - | `private const float CyclicPitch = 30;` |
| - | `private const float CyclicRoll = 38;` |
| - | `private const float PedalRate = 70;` |
| - | `private const float GunYawLimit = 125;` |
| - | `private const float GunUpLimit = 38;` |
| - | `private const float GunDownLimit = 62;` |
| - | `public AirKind kind;` |
| - | `public VehicleManager vehicle;` |
| - | `public Rigidbody body;` |
| - | `public Transform cameraPivot;` |
| - | `public Transform mainRotor;` |
| - | `public Transform tailRotor;` |
| - | `public Renderer rotorDisc;` |
| - | `public Transform gunYaw;` |
| - | `public Transform gunPitch;` |
| - | `public Transform gunBarrels;` |
| - | `public Transform elevonLeft;` |
| - | `public Transform elevonRight;` |
| - | `public Transform turbineLeft;` |
| - | `public Transform turbineRight;` |
| - | `public Transform gear;` |
| - | `public Transform[] muzzles;` |
| - | `public Transform[] rocketPoints;` |
| - | `public Vector3[] gearRays;` |
| - | `public ParticleSystem[] muzzleFlashes;` |
| - | `public ParticleSystem[] rocketSmoke;` |
| - | `public Renderer[] burnerFlames;` |
| - | `public Light burnerLight;` |
| - | `public Light muzzleLight;` |
| - | `public TrailRenderer[] wingTrails;` |
| - | `public ParticleSystem vaporCone;` |
| - | `public ParticleSystem rotorWash;` |
| - | `public ParticleSystem exhaust;` |
| - | `public Renderer vaporBell;` |
| - | `public AudioSource engineAudio;` |
| - | `public AudioSource burnerAudio;` |
| - | `public AudioSource gunAudio;` |
| - | `public AudioSource shotAudio;` |
| - | `public AudioSource whineAudio;` |
| - | `public AudioSource cabinAudio;` |
| - | `public AudioSource gunFarAudio;` |
| - | `public AudioClip gunLoop;` |
| - | `public AudioClip gunTail;` |
| - | `public AudioClip rocketClip;` |
| - | `public Material tracerMaterial;` |
| - | `public Material sparkMaterial;` |
| - | `public Material dustMaterial;` |
| - | `private float stickPitch;` |
| - | `private float stickRoll;` |
| - | `private float stickYaw;` |
| - | `private float stickLift;` |
| - | `private float flyYaw;` |
| - | `private float flyPitch;` |
| - | `private float aimSteer;` |
| - | `private float ctrlPitch;` |
| - | `private float ctrlRoll;` |
| - | `private bool mouseAim;` |
| - | `private bool gunHeld;` |
| - | `private bool rocketHeld;` |
| - | `private bool wasGun;` |
| - | `private float throttle;` |
| - | `private float engine;` |
| - | `private float burner;` |
| - | `private float rotor;` |
| - | `private float gear01;` |
| - | `private float gearTarget;` |
| - | `private float aimYaw;` |
| - | `private float aimPitch;` |
| - | `private bool engineOn;` |
| - | `private bool wasOwner;` |
| - | `private bool crashed;` |
| - | `private float <Speed>k__BackingField;` |
| - | `private float <VerticalSpeed>k__BackingField;` |
| - | `private float <Altitude>k__BackingField;` |
| - | `private float <Height>k__BackingField;` |
| - | `private float <AngleOfAttack>k__BackingField;` |
| - | `private float <GForce>k__BackingField;` |
| - | `private bool <Stalling>k__BackingField;` |
| - | `private bool <PullUp>k__BackingField;` |
| - | `private bool <OutOfArea>k__BackingField;` |
| - | `private bool <Grounded>k__BackingField;` |
| - | `private Vector3 <AimPoint>k__BackingField;` |
| - | `private Vector3 <GunPoint>k__BackingField;` |
| - | `private int ammo;` |
| - | `private int rockets;` |
| - | `private int rocketIndex;` |
| - | `private int muzzleIndex;` |
| - | `private float gunReadyAt;` |
| - | `private float rocketReadyAt;` |
| - | `private float nextRound;` |
| - | `private float nextRocket;` |
| - | `private float flash;` |
| - | `private int view;` |
| - | `private float lookYaw;` |
| - | `private float lookPitch;` |
| - | `private float lastLook;` |
| - | `private float fovBase;` |
| - | `private float cameraDistance;` |
| - | `private float shake;` |
| - | `private Quaternion chase;` |
| - | `private Vector3 lastVelocity;` |
| - | `private Vector3 gearRest;` |
| - | `private float areaTurn;` |
| - | `private BuildingPiece piece;` |
| - | `private int groundMask;` |
| - | `private int aimMask;` |
| - | `private Collider[] ownColliders;` |
| - | `private readonly RaycastHit[] hits;` |
| - | `private float engineSoundTarget;` |
| - | `private float remoteGunUntil;` |
| - | `private bool gunSounding;` |
| - | `private AudioLowPassFilter engineAir;` |
| - | `private AudioLowPassFilter whineAir;` |
| - | `private AudioLowPassFilter burnerAir;` |
| - | `private AudioLowPassFilter gunAir;` |
| - | `private Material discMaterial;` |
| - | `private MaterialPropertyBlock vaporBlock;` |
| - | `private static readonly int BaseColorId;` |
| - | `private float remoteEngine;` |
| - | `private float remoteBurner;` |
| - | `private float remoteYaw;` |
| - | `private float remotePitch;` |
| - | `private float remoteGear;` |
| - | `private float remoteRoll;` |
| - | `private float rotorAngle;` |
| - | `private float tailAngle;` |
| - | `private float turbineAngle;` |
| - | `private float barrelAngle;` |
| - | `private float spin;` |

Properties: `public float Speed { get; set; }`; `public float VerticalSpeed { get; set; }`; `public float Altitude { get; set; }`; `public float Height { get; set; }`; `public float AngleOfAttack { get; set; }`; `public float GForce { get; set; }`; `public bool Stalling { get; set; }`; `public bool PullUp { get; set; }`; `public bool OutOfArea { get; set; }`; `public bool Grounded { get; set; }`; `public float Throttle { get; }`; `public float Rotor { get; }`; `public float Burner { get; }`; `public float GearDown { get; }`; `public int Ammo { get; }`; `public int Rockets { get; }`; `public int RocketCapacity { get; }`; `public float GunReloadLeft { get; }`; `public float RocketReloadLeft { get; }`; `public float RocketReloadTime { get; }`; `public bool IsDriver { get; }`; `public Vector3 AimPoint { get; set; }`; `public Vector3 GunPoint { get; set; }`; `public Vector3 FlightPathPoint { get; }`; `public bool Cockpit { get; }`; `public bool MouseAim { get; }`; `public Vector3 AimDirection { get; }`; `public Vector3 MouseAimPoint { get; }`; `public Vector3 NosePoint { get; }`; `public float HealthFraction { get; }`; `public float SteerForNet { get; }`

<details><summary>methods (83)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F1918C |  | `public float get_Speed()` |
| - | 0x2F19194 |  | `private void set_Speed(float value)` |
| - | 0x2F1919C |  | `public float get_VerticalSpeed()` |
| - | 0x2F191A4 |  | `private void set_VerticalSpeed(float value)` |
| - | 0x2F191AC |  | `public float get_Altitude()` |
| - | 0x2F191B4 |  | `private void set_Altitude(float value)` |
| - | 0x2F191BC |  | `public float get_Height()` |
| - | 0x2F191C4 |  | `private void set_Height(float value)` |
| - | 0x2F191CC |  | `public float get_AngleOfAttack()` |
| - | 0x2F191D4 |  | `private void set_AngleOfAttack(float value)` |
| - | 0x2F191DC |  | `public float get_GForce()` |
| - | 0x2F191E4 |  | `private void set_GForce(float value)` |
| - | 0x2F191EC |  | `public bool get_Stalling()` |
| - | 0x2F191F4 |  | `private void set_Stalling(bool value)` |
| - | 0x2F19200 |  | `public bool get_PullUp()` |
| - | 0x2F19208 |  | `private void set_PullUp(bool value)` |
| - | 0x2F19214 |  | `public bool get_OutOfArea()` |
| - | 0x2F1921C |  | `private void set_OutOfArea(bool value)` |
| - | 0x2F19228 |  | `public bool get_Grounded()` |
| - | 0x2F19230 |  | `private void set_Grounded(bool value)` |
| - | 0x2F1923C |  | `public float get_Throttle()` |
| - | 0x2F19264 |  | `public float get_Rotor()` |
| - | 0x2F1926C |  | `public float get_Burner()` |
| - | 0x2F19274 |  | `public float get_GearDown()` |
| - | 0x2F1927C |  | `public int get_Ammo()` |
| - | 0x2F19284 |  | `public int get_Rockets()` |
| - | 0x2F1928C |  | `public int get_RocketCapacity()` |
| - | 0x2F192A4 |  | `public float get_GunReloadLeft()` |
| - | 0x2F192D0 |  | `public float get_RocketReloadLeft()` |
| - | 0x2F192FC |  | `public float get_RocketReloadTime()` |
| - | 0x2F19314 |  | `public bool get_IsDriver()` |
| - | 0x2F19398 |  | `public Vector3 get_AimPoint()` |
| - | 0x2F193A8 |  | `private void set_AimPoint(Vector3 value)` |
| - | 0x2F193B8 |  | `public Vector3 get_GunPoint()` |
| - | 0x2F193C8 |  | `private void set_GunPoint(Vector3 value)` |
| - | 0x2F193D8 |  | `public Vector3 get_FlightPathPoint()` |
| - | 0x2F195DC |  | `public bool get_Cockpit()` |
| - | 0x2F195EC |  | `public bool get_MouseAim()` |
| - | 0x2F195F4 |  | `public Vector3 get_AimDirection()` |
| - | 0x2F19690 |  | `public Vector3 get_MouseAimPoint()` |
| - | 0x2F1975C |  | `public Vector3 get_NosePoint()` |
| - | 0x2F197D8 |  | `public float get_HealthFraction()` |
| - | 0x2F198D4 |  | `private void Awake()` |
| - | 0x2F1A00C |  | `private void OnDestroy()` |
| - | 0x2F1A168 |  | `public void SetEngine(bool on)` |
| - | 0x2F1A21C |  | `public void FillNet(float[] v)` |
| - | 0x2F1A280 |  | `public void SetRemote(float[] v)` |
| - | 0x2F1A2C4 |  | `public float get_SteerForNet()` |
| - | 0x2F1A2CC |  | `public void SetSticks(float pitch, float roll, float yaw, float lift)` |
| - | 0x2F1A318 |  | `public void SetGunHeld(bool held)` |
| - | 0x2F1A324 |  | `public void SetRocketHeld(bool held)` |
| - | 0x2F1A330 |  | `public void ToggleView()` |
| - | 0x2F1A354 |  | `public void ToggleGear()` |
| - | 0x2F1A3A0 |  | `public void RequestReload()` |
| - | 0x2F1A458 |  | `public void AddLook(Vector2 degrees)` |
| - | 0x2F1A598 |  | `public void OnAirState(float rounds, float gunLeft, float rocketCount, float rocketLeft)` |
| - | 0x2F1A76C |  | `public void OnRemoteTracer(Vector3 from, Vector3 to, float kindOfHit)` |
| - | 0x2F1A894 |  | `public void OnRemoteRocket(Vector3 at)` |
| - | 0x2F1AA74 |  | `private void FixedUpdate()` |
| - | 0x2F1BE9C |  | `private void FlyHelicopter(float pitch, float roll, float dt)` |
| - | 0x2F1AC74 |  | `private void FlyFighter(float pitch, float roll, float dt)` |
| - | 0x2F1CF90 |  | `private int GearOnGround(float dt, Vector3 local)` |
| - | 0x2F1C8EC |  | `private void KeepInArea()` |
| - | 0x2F1D4D8 |  | `private void OnCollisionEnter(Collision collision)` |
| - | 0x2F1D6B4 |  | `private void Update()` |
| - | 0x2F20030 |  | `private void LateUpdate()` |
| - | 0x2F1D998 |  | `private void OwnerChanged(bool owner)` |
| - | 0x2F1DD84 |  | `private void SyncAim()` |
| - | 0x2F1A0CC |  | `private void RestoreFov()` |
| - | 0x2F1DE14 |  | `private void AimGuns(float dt)` |
| - | 0x2F20F44 |  | `private bool FirstHit(Vector3 origin, Vector3 direction, float distance, out RaycastHit best)` |
| - | 0x2F1E3CC |  | `private void FireWeapons()` |
| - | 0x2F211B8 |  | `private Vector3 ShotDirection(Vector3 origin, Vector3 barrel)` |
| - | 0x2F213BC |  | `private void FireRound()` |
| - | 0x2F1E528 |  | `private void GunSound(bool firing)` |
| - | 0x2F1A7C0 |  | `private void PlayMuzzle(bool local)` |
| - | 0x2F21748 |  | `private void FireRocket(float now)` |
| - | 0x2F1E6A4 |  | `private void Animate(float dt)` |
| - | 0x2F1F674 |  | `private void Sound(float dt)` |
| - | 0x2F21AA4 |  | `private static void Loop(AudioSource source, bool wanted)` |
| - | 0x2F20148 |  | `private void UpdateCamera(float dt)` |
| - | 0x2F21BE4 |  | `public void .ctor()` |
| - | 0x2F21CBC |  | `private static void .cctor()` |

</details>

### public sealed class `AirHudLines` : MaskableGraphic  
`TypeDefIndex 3487`

| offset | field |
|---|---|
| - | `private readonly List<AirHudLines.Segment> segments;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F21D24 |  | `public void Clear()` |
| - | 0x2F21D74 |  | `public void Line(Vector2 a, Vector2 b, float width, Color c)` |
| - | 0x2F21E98 |  | `public void Box(Vector2 centre, Vector2 size, float width, Color c)` |
| - | 0x2F21F8C |  | `public void Fill(Vector2 centre, Vector2 size, Color c)` |
| - | 0x2F21FD0 |  | `public void Circle(Vector2 centre, float radius, float width, Color c, int steps = 24, float from = 0, float to = 360)` |
| - | 0x2F22114 |  | `private static Vector2 Polar(float degrees)` |
| - | 0x2F2213C |  | `public void Apply()` |
| - | 0x2F2214C |  | `protected override void OnPopulateMesh(VertexHelper vh)` |
| - | 0x2F224EC |  | `public void .ctor()` |

</details>

### public sealed class `AirStick` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IDragHandler, IPointerUpHandler  
`TypeDefIndex 3488`

| offset | field |
|---|---|
| - | `public RectTransform Base;` |
| - | `public RectTransform Knob;` |
| - | `private Vector2 <Value>k__BackingField;` |
| - | `public float Range;` |
| - | `private Vector2 home;` |
| - | `private int pointer;` |
| - | `public bool HoldY;` |

Properties: `public Vector2 Value { get; set; }`

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F22578 |  | `public Vector2 get_Value()` |
| - | 0x2F22580 |  | `private void set_Value(Vector2 value)` |
| - | 0x2F22588 |  | `private void Start()` |
| - | 0x2F22604 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2F227CC |  | `public void OnDrag(PointerEventData e)` |
| - | 0x2F22928 |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2F22954 |  | `public void Release()` |
| - | 0x2F22AD8 |  | `private void OnDisable()` |
| - | 0x2F22ADC |  | `public void .ctor()` |

</details>

### public sealed class `AirButton` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IDragHandler  
`TypeDefIndex 3489`

| offset | field |
|---|---|
| - | `public Action<bool> Held;` |
| - | `public Action Click;` |
| - | `private int pointer;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F22AF4 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2F22BD4 |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2F22C88 |  | `public void OnDrag(PointerEventData e)` |
| - | 0x2F22D08 |  | `private void OnDisable()` |
| - | 0x2F22DB4 |  | `public void .ctor()` |

</details>

### internal static class `AirUi`  
`TypeDefIndex 3490`

| offset | field |
|---|---|
| - | `private static PauseManager pause;` |
| - | `private static float nextPauseLookup;` |
| - | `private static AudioClip beep;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F22DC4 |  | `internal static Transform Find(Transform root, string name, string parent)` |
| - | 0x2F22F30 |  | `internal static void NoClipping(Transform root)` |
| - | 0x2F22FE8 |  | `internal static bool GameUiOver()` |
| - | 0x2F23368 |  | `internal static string Health(float fraction)` |
| - | 0x2F234BC |  | `internal static Sprite SpriteOf(Transform t)` |
| - | 0x2F2357C |  | `internal static RectTransform Stretch(string name, Transform parent)` |
| - | 0x2F237B8 |  | `internal static AirStick Stick(string name, Transform parent, bool left, Sprite baseSprite, Sprite knobSprite)` |
| - | 0x2F23CBC |  | `internal static AirButton Button(string name, Transform parent, Sprite sprite, Vector2 anchor, Vector2 pivot, Vector2 position, float size, Color tint, string label, TMP_FontAsset font)` |
| - | 0x2F24084 |  | `internal static AudioClip Beep()` |

</details>

### public sealed class `AircraftHud` : MonoBehaviour  
`TypeDefIndex 3492`

| offset | field |
|---|---|
| - | `private static AircraftHud active;` |
| - | `public static bool ForceTouch;` |
| - | `private Canvas canvas;` |
| - | `private RectTransform rect;` |
| - | `private AirHudLines lines;` |
| - | `private GameObject touch;` |
| - | `private AirStick leftStick;` |
| - | `private AirStick rightStick;` |
| - | `private TextMeshProUGUI speedText;` |
| - | `private TextMeshProUGUI altText;` |
| - | `private TextMeshProUGUI headingText;` |
| - | `private TextMeshProUGUI leftInfo;` |
| - | `private TextMeshProUGUI weaponText;` |
| - | `private TextMeshProUGUI warning;` |
| - | `private TextMeshProUGUI title;` |
| - | `private TextMeshProUGUI hint;` |
| - | `private AudioSource warnAudio;` |
| - | `private float nextText;` |
| - | `private float nextBeep;` |
| - | `private AircraftController cached;` |
| - | `private GameObject gearObject;` |
| - | `private static readonly Color Green;` |
| - | `private static readonly Color Amber;` |
| - | `private static readonly Color Red;` |
| - | `private Color ink;` |

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F242C4 |  | `public static void Sync(ScreenControlsManager manager, sH state)` |
| - | 0x2F24420 |  | `private static AircraftHud Build(ScreenControlsManager manager)` |
| - | 0x2F245A4 |  | `private void Assemble(Transform root)` |
| - | 0x2F2566C |  | `private static AircraftController Current()` |
| - | 0x2F2573C |  | `private void OnDisable()` |
| - | 0x2F257B8 |  | `private void RestoreFromHud()` |
| - | 0x2F25864 |  | `private void Update()` |
| - | 0x2F25CB4 |  | `private static Vector2 Curve(Vector2 v)` |
| - | 0x2F28154 |  | `private static string WarningOf(AircraftController air)` |
| - | 0x2F2710C |  | `private void WriteTexts(AircraftController air, bool phone)` |
| - | 0x2F25DA0 |  | `private void DrawInstruments(AircraftController air)` |
| - | 0x2F283C4 |  | `private void Tape(float x, float value, float step, float pxPerUnit, bool left, Color dim, Color main)` |
| - | 0x2F28644 |  | `private Vector2 ToCanvas(Camera view, Vector3 world)` |
| - | 0x2F2872C |  | `public void .ctor()` |
| - | 0x2F28794 |  | `private static void .cctor()` |
| - | 0x2F28804 |  | `private void <Assemble>b__27_0(bool held)` |
| - | 0x2F28888 |  | `private void <Assemble>b__27_1(bool held)` |
| - | 0x2F2890C |  | `private void <Assemble>b__27_3()` |
| - | 0x2F2898C |  | `private void <Assemble>b__27_4()` |
| - | 0x2F28A0C |  | `private void <Assemble>b__27_5()` |

</details>

### public sealed class `DroneHud` : MonoBehaviour  
`TypeDefIndex 3494`

| offset | field |
|---|---|
| - | `public static bool ForceTouch;` |
| - | `private FpvDroneController drone;` |
| - | `private Canvas canvas;` |
| - | `private RectTransform rect;` |
| - | `private AirHudLines lines;` |
| - | `private GameObject touch;` |
| - | `private AirStick leftStick;` |
| - | `private AirStick rightStick;` |
| - | `private TextMeshProUGUI rec;` |
| - | `private TextMeshProUGUI recTime;` |
| - | `private TextMeshProUGUI name_;` |
| - | `private TextMeshProUGUI battery;` |
| - | `private TextMeshProUGUI flight;` |
| - | `private TextMeshProUGUI home;` |
| - | `private TextMeshProUGUI warn;` |
| - | `private TextMeshProUGUI hint;` |
| - | `private float keyPitch;` |
| - | `private float keyRoll;` |
| - | `private float keyYaw;` |
| - | `private float nextText;` |
| - | `private Canvas chatCanvas;` |
| - | `private bool chatOverride;` |
| - | `private int chatOrder;` |

<details><summary>methods (13)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F28C9C |  | `internal static DroneHud Show(FpvDroneController drone)` |
| - | 0x2F29B74 |  | `private void OnDestroy()` |
| - | 0x2F29A00 |  | `private void RaiseChat()` |
| - | 0x2F29C60 |  | `private void RestoreChat()` |
| - | 0x2F29D2C |  | `private static TextMeshProUGUI Osd(string name, Transform parent, float size, TMP_FontAsset font, TextAlignmentOptions align, Vector2 anchor, Vector2 pivot, Vector2 position, Vector2 box)` |
| - | 0x2F28ED0 |  | `private void Assemble(Transform root)` |
| - | 0x2F29EF0 |  | `private void Update()` |
| - | 0x2F2A854 |  | `private void WriteTexts(bool phone)` |
| - | 0x2F2B568 |  | `private void Draw()` |
| - | 0x2F2BFF8 |  | `public void .ctor()` |
| - | 0x2F2C000 |  | `private void <Assemble>b__28_0()` |
| - | 0x2F2C07C |  | `private void <Assemble>b__28_1()` |
| - | 0x2F2C0F8 |  | `private void <Assemble>b__28_2()` |

</details>

### public sealed class `AirTracers` : MonoBehaviour  
`TypeDefIndex 3496`

| offset | field |
|---|---|
| - | `private const int Count = 28;` |
| - | `private const float Velocity = 1100;` |
| - | `private const float Length = 170;` |
| - | `private static AirTracers instance;` |
| - | `private LineRenderer[] lines;` |
| - | `private float[] born;` |
| - | `private float[] life;` |
| - | `private Vector3[] from;` |
| - | `private Vector3[] direction;` |
| - | `private Vector3[] carried;` |
| - | `private float[] length;` |
| - | `private int next;` |
| - | `private ParticleSystem sparks;` |
| - | `private ParticleSystem dust;` |
| - | `private ParticleSystem blood;` |
| - | `private readonly AirTracers.Impact[] impacts;` |
| - | `private int impactNext;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F2C2D4 |  | `public static void Show(Material line, Material spark, Material puff, Vector3 a, Vector3 b, float kindOfHit, Vector3 carrier)` |
| - | 0x2F2C4C4 |  | `private void Build(Material line, Material spark, Material puff)` |
| - | 0x2F2CF0C |  | `private ParticleSystem Burst(string name, Material material, Color color, float life0, float life1, float speed0, float speed1, float size0, float size1, bool stretch)` |
| - | 0x2F2CBE8 |  | `private void Fire(Vector3 a, Vector3 b, float kindOfHit, Vector3 carrier)` |
| - | 0x2F2D4D0 |  | `private void LateUpdate()` |
| - | 0x2F2DA78 |  | `private static void Emit(ParticleSystem ps, AirTracers.Impact hit, int count)` |
| - | 0x2F2DBB0 |  | `public void .ctor()` |

</details>

### public struct `CarInput`  
`TypeDefIndex 3497`

| offset | field |
|---|---|
| 0x0 | `public Vector3 position;` |
| 0xC | `public Quaternion rotation;` |
| 0x1C | `public float accel;` |
| 0x20 | `public float brake;` |
| 0x24 | `public float steer;` |

### public struct `CarMove`  
`TypeDefIndex 3498`

| offset | field |
|---|---|
| 0x0 | `public Vector3 position;` |
| 0xC | `public Quaternion rotation;` |
| 0x1C | `public float steer;` |
| 0x20 | `public float[] wheelsSpeeds;` |

### public struct `CheckDirectionData`  
`TypeDefIndex 3499`

| offset | field |
|---|---|
| 0x0 | `public KCC sourceKcc;` |
| 0x8 | `public Transform exitPoint;` |
| 0x10 | `public float exitDistance;` |
| 0x14 | `public int mask;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x38247E8 | 0x2F2DC14 |  | `public CheckDirectionData dzl(Transform e)` |

</details>

### public struct `CheckDirectionResult`  
`TypeDefIndex 3500`

| offset | field |
|---|---|
| 0x0 | `public bool ObstacleFound;` |
| 0x1 | `public bool AvailableToSpawn;` |
| 0x4 | `public Vector3 Point;` |

### public sealed class `CheckDistanceDelegate` : MulticastDelegate  
`TypeDefIndex 3501`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F2DC20 |  | `public void .ctor(object object, IntPtr method)` |
| - | 0x2F2DCC0 |  | `public virtual CheckDirectionResult Invoke(CheckDirectionData data, ExitPoints exitPoints)` |
| - | 0x2F2DD10 |  | `public virtual IAsyncResult BeginInvoke(CheckDirectionData data, ExitPoints exitPoints, AsyncCallback callback, object object)` |
| - | 0x2F2DDD0 |  | `public virtual CheckDirectionResult EndInvoke(IAsyncResult result)` |

</details>

### public struct `ExitPoints`  
`TypeDefIndex 3502`

| offset | field |
|---|---|
| 0x0 | `public Transform defaultExitPoint;` |
| 0x8 | `public Transform frontExitPoint;` |
| 0x10 | `public Transform backExitPoint;` |

### public sealed class `FpvDroneController` : MonoBehaviour  
`TypeDefIndex 3503`

| offset | field |
|---|---|
| - | `public const int NetValues = 6;` |
| - | `private const float ThrustToWeight = 2.4;` |
| - | `private const float Gravity = 9.81;` |
| - | `private const float MotorLag = 0.09;` |
| - | `private const float ThrottleRate = 0.7;` |
| - | `private const float RateCentre = 70;` |
| - | `private const float RateMax = 320;` |
| - | `private const float YawCentre = 50;` |
| - | `private const float YawMax = 180;` |
| - | `private const float AngleLimit = 70;` |
| - | `private const float RateGain = 20;` |
| - | `private static readonly Vector3 AirDrag;` |
| - | `private const float CameraUp = 30;` |
| - | `private const float VerticalFov = 82;` |
| - | `private const float BatterySeconds = 300;` |
| - | `private const float SignalStart = 1000;` |
| - | `private const float SignalGone = 2000;` |
| - | `private const float LostAt = 2200;` |
| - | `private const float CrashSpeed = 5;` |
| - | `private const float ClearOfGround = 2.2;` |
| - | `private const float ArmedAtSpeed = 8;` |
| - | `private const float PadSeconds = 0.5;` |
| - | `public VehicleManager vehicle;` |
| - | `public Rigidbody body;` |
| - | `public Transform camTilt;` |
| - | `public Transform[] props;` |
| - | `public AudioSource buzz;` |
| - | `public AudioSource bootAudio;` |
| - | `public AudioClip bootClip;` |
| - | `public Material signalMaterial;` |
| - | `public Renderer[] hideInFpv;` |
| - | `public Light statusLed;` |
| - | `private float stickPitch;` |
| - | `private float stickRoll;` |
| - | `private float stickYaw;` |
| - | `private float stickThrottle;` |
| - | `private float mouseYaw;` |
| - | `private float mousePitch;` |
| - | `private float anglePitch;` |
| - | `private Vector2 mouseRate;` |
| - | `private bool engineOn;` |
| - | `private bool flying;` |
| - | `private bool ended;` |
| - | `private bool armedForCrash;` |
| - | `private bool acro;` |
| - | `private bool touching;` |
| - | `private BuildingPiece piece;` |
| - | `private float launchedAt;` |
| - | `private float spin;` |
| - | `private float throttle;` |
| - | `private float thrust;` |
| - | `private float nextSight;` |
| - | `private float blocked;` |
| - | `private Collider[] ownColliders;` |
| - | `private int groundMask;` |
| - | `private int lostCount;` |
| - | `private readonly bool[] propLost;` |
| - | `private Vector3 home;` |
| - | `private Vector3 lostTorque;` |
| - | `private float battery;` |
| - | `private float signal;` |
| - | `private RenderTexture picture;` |
| - | `private RawImage screen;` |
| - | `private Canvas screenCanvas;` |
| - | `private DroneHud hud;` |
| - | `private Material screenMaterial;` |
| - | `private static readonly int SignalId;` |
| - | `private static FpvDroneController <Active>k__BackingField;` |
| - | `private float remoteThrust;` |
| - | `private bool sightBlocked;` |
| - | `private bool crashSent;` |

Properties: `public float HealthFraction { get; }`; `public bool Flying { get; }`; `public float Battery { get; }`; `public float Signal { get; }`; `public float DistanceHome { get; }`; `public float FlightTime { get; }`; `public float Speed { get; }`; `public float VerticalSpeed { get; }`; `public float Altitude { get; }`; `public float ThrottleShown { get; }`; `public bool Armed { get; }`; `public bool Acro { get; }`; `public int PropsLost { get; }`; `public float CameraTilt { get; }`; `public float ViewFov { get; }`; `public bool BatteryEmpty { get; }`; `public static FpvDroneController Active { get; set; }`

<details><summary>methods (41)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F2BC9C |  | `public float get_HealthFraction()` |
| - | 0x2F2DDFC |  | `public bool get_Flying()` |
| - | 0x2F2DE04 |  | `public float get_Battery()` |
| - | 0x2F2DE0C |  | `public float get_Signal()` |
| - | 0x2F2BF2C |  | `public float get_DistanceHome()` |
| - | 0x2F2BC6C |  | `public float get_FlightTime()` |
| - | 0x2F2BE40 |  | `public float get_Speed()` |
| - | 0x2F2BDC0 |  | `public float get_VerticalSpeed()` |
| - | 0x2F2BD98 |  | `public float get_Altitude()` |
| - | 0x2F2DE14 |  | `public float get_ThrottleShown()` |
| - | 0x2F2DE1C |  | `public bool get_Armed()` |
| - | 0x2F2DE24 |  | `public bool get_Acro()` |
| - | 0x2F2DE2C |  | `public int get_PropsLost()` |
| - | 0x2F2BFE4 |  | `public float get_CameraTilt()` |
| - | 0x2F2BFEC |  | `public float get_ViewFov()` |
| - | 0x2F2DE34 |  | `public bool get_BatteryEmpty()` |
| - | 0x2F2DE44 |  | `public static FpvDroneController get_Active()` |
| - | 0x2F2DE9C |  | `private static void set_Active(FpvDroneController value)` |
| - | 0x2F2DEFC |  | `private void Awake()` |
| - | 0x2F2E300 |  | `private void OnDestroy()` |
| - | 0x2F2E8FC |  | `public void SetEngine(bool on)` |
| - | 0x2F2E9BC |  | `public void FillNet(float[] v)` |
| - | 0x2F2E9F0 |  | `public void SetRemote(float[] v)` |
| - | 0x2F2EA0C |  | `public void Begin()` |
| - | 0x2F2F668 |  | `public void End()` |
| - | 0x2F2E364 |  | `private void Teardown()` |
| - | 0x2F2EF84 |  | `private void BuildScreen()` |
| - | 0x2F2A6A8 |  | `public void SetSticks(float throttleStick, float yaw, float pitch, float roll)` |
| - | 0x2F2A6EC |  | `public void AddMouse(Vector2 degrees)` |
| - | 0x2F2A700 |  | `public void ToggleMode()` |
| - | 0x2F2A714 |  | `public void Leave()` |
| - | 0x2F2A79C |  | `public void Detonate()` |
| - | 0x2F2F704 |  | `private static float Rate(float stick, float centre, float max)` |
| - | 0x2F2F720 |  | `private void FixedUpdate()` |
| - | 0x2F30220 |  | `private void Update()` |
| - | 0x2F30A48 |  | `private void UpdateSignal(float dt)` |
| - | 0x2F30DE4 |  | `public void OnPropLost(int index)` |
| - | 0x2F313FC |  | `private void OnCollisionStay(Collision collision)` |
| - | 0x2F31408 |  | `private void OnCollisionEnter(Collision collision)` |
| - | 0x2F315A8 |  | `public void .ctor()` |
| - | 0x2F31614 |  | `private static void .cctor()` |

</details>

### public struct `HeliMove`  
`TypeDefIndex 3504`

| offset | field |
|---|---|
| 0x0 | `public Vector3 position;` |
| 0xC | `public Quaternion rotation;` |
| 0x1C | `public Vector3 velocity;` |
| 0x28 | `public float engineForce;` |

<details><summary>methods (1)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3822FAC | 0x2F3169C |  | `public void .ctor(Vector3 position, Quaternion rotation, Vector3 velocity, float engineForce)` |

</details>

### public sealed class `HitOverlay` : MonoBehaviour  
`TypeDefIndex 3505`

| offset | field |
|---|---|
| - | `public const int Body = 0;` |
| - | `public const int Vehicle = 1;` |
| - | `public const int Kill = 2;` |
| - | `public const int Structure = 3;` |
| - | `private const int Indicators = 4;` |
| - | `private static HitOverlay instance;` |
| - | `private Canvas canvas;` |
| - | `private RectTransform rect;` |
| - | `private AirHudLines lines;` |
| - | `private AudioSource voice;` |
| - | `private AudioClip body;` |
| - | `private AudioClip kill;` |
| - | `private AudioClip[] armour;` |
| - | `private AudioClip[] hurt;` |
| - | `private readonly Image[] indicator;` |
| - | `private readonly Vector3[] indicatorFrom;` |
| - | `private readonly float[] indicatorAt;` |
| - | `private int markKind;` |
| - | `private int nextIndicator;` |
| - | `private float markAt;` |
| - | `private float lastSound;` |

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F316C4 |  | `public static void Hit(int kind, float damage)` |
| - | 0x2F31A30 |  | `public static void Hurt(Vector3 from, float health)` |
| - | 0x2F31720 |  | `private static void Ensure()` |
| - | - |  | `private static T Built<T>(string key)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x382CA7C Offset: 0x3828A7C VA: 0x382CA7C` |
| - | - |  | `\|-HitOverlay.Built<object>` |
| - | - |  | `*/` |
| - | 0x2F31BDC |  | `private void Assemble(Canvas c)` |
| - | 0x2F3221C |  | `private static AudioClip Any(AudioClip[] clips)` |
| - | 0x2F31884 |  | `private void OnHit(int kind)` |
| - | 0x2F31AAC |  | `private void OnHurt(Vector3 from)` |
| - | 0x2F32264 |  | `private void LateUpdate()` |
| - | 0x2F32A64 |  | `public void .ctor()` |

</details>

### public sealed class `MilitaryBlast` : MonoBehaviour  
`TypeDefIndex 3506`

| offset | field |
|---|---|
| - | `public AudioSource close;` |
| - | `public AudioSource mid;` |
| - | `public AudioSource far;` |
| - | `public AudioSource debris;` |
| - | `public AudioClip[] closeClips;` |
| - | `public AudioClip[] midClips;` |
| - | `public AudioClip[] farClips;` |
| - | `public Light flash;` |
| - | `public GameObject groundBurst;` |
| - | `public GameObject airBurst;` |
| - | `public float flashIntensity;` |
| - | `public float flashTime;` |
| - | `public float shakeRadius;` |
| - | `public float shakeStrength;` |
| - | `private float born;` |
| - | `private static int groundMask;` |
| - | `private static Transform listener;` |

<details><summary>methods (7)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F32B6C |  | `private void Start()` |
| - | 0x2F3371C |  | `private static float Falloff(float d, float reference)` |
| - | 0x2F3372C |  | `private static void Play(AudioSource source, AudioClip[] clips, float volume, float delay, float blend, float spread, float cutoff, float d)` |
| - | 0x2F3394C |  | `private void Update()` |
| - | 0x2F33578 |  | `internal static Transform Listener()` |
| - | 0x2F33A7C |  | `public void .ctor()` |
| - | 0x2F33A90 |  | `private static void .cctor()` |

</details>

### public sealed class `HearingDuck` : MonoBehaviour  
`TypeDefIndex 3507`

| offset | field |
|---|---|
| - | `private static HearingDuck instance;` |
| - | `private float amount;` |
| - | `private float pending;` |
| - | `private float startAt;` |
| - | `private float master;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F33ADC |  | `public static void Kick(float strength, float delay)` |
| - | 0x2F33D14 |  | `private void Update()` |
| - | 0x2F33F34 |  | `public void .ctor()` |

</details>

### public static class `BlastShake`  
`TypeDefIndex 3508`

| offset | field |
|---|---|
| - | `private static float trauma;` |
| - | `private static float lastTime;` |
| - | `private static bool hooked;` |
| - | `private static bool applied;` |
| - | `private static Camera shaken;` |
| - | `private static Vector3 savedPosition;` |
| - | `private static Quaternion savedRotation;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F33F44 |  | `public static void Add(Vector3 at, float radius, float strength)` |
| - | 0x2F340AC |  | `public static void Kick(float amount)` |
| - | 0x2F341F8 |  | `private static void Begin(ScriptableRenderContext context, Camera cam)` |
| - | 0x2F34580 |  | `private static void End(ScriptableRenderContext context, Camera cam)` |

</details>

### public sealed class `TankController` : MonoBehaviour  
`TypeDefIndex 3509`

| offset | field |
|---|---|
| - | `public const int NetValues = 4;` |
| - | `public const float ReloadSeconds = 5;` |
| - | `public const float MinElevation = -7;` |
| - | `public const float MaxElevation = 22;` |
| - | `private const float MaxForward = 12.5;` |
| - | `private const float MaxReverse = 5.5;` |
| - | `private const float EngineAccel = 3.6;` |
| - | `private const float BrakeAccel = 7.5;` |
| - | `private const float CoastAccel = 3;` |
| - | `private const float MaxClimbAssist = 3.4;` |
| - | `private const float LateralGrip = 8.5;` |
| - | `private const float PivotRate = 44;` |
| - | `private const float CruiseRate = 20;` |
| - | `private const float YawAccel = 150;` |
| - | `private const float TurretRate = 38;` |
| - | `private const float GunRate = 22;` |
| - | `private const float TrackGauge = 2.96;` |
| - | `private const float TrackLoopMetres = 14.07;` |
| - | `private const float ClipSeconds = 8;` |
| - | `private const float RayStart = 1;` |
| - | `private const float RestCompression = 0.1;` |
| - | `private static readonly float[] StationZ;` |
| - | `private const float StationX = 1.48;` |
| - | `public VehicleManager vehicle;` |
| - | `public Rigidbody body;` |
| - | `public Transform turret;` |
| - | `public Transform gun;` |
| - | `public Transform muzzle;` |
| - | `public Transform cameraPivot;` |
| - | `public Animator tracksAnimator;` |
| - | `public AnimationClip tracksClip;` |
| - | `public Renderer visibilityRenderer;` |
| - | `public ParticleSystem fireEffect;` |
| - | `public ParticleSystem exhaust;` |
| - | `public ParticleSystem dustLeft;` |
| - | `public ParticleSystem dustRight;` |
| - | `public Light muzzleLight;` |
| - | `public Light[] headlights;` |
| - | `public Light[] rearLights;` |
| - | `public Renderer hullRenderer;` |
| - | `public int rearLampMaterial;` |
| - | `public AudioSource fireAudio;` |
| - | `public AudioSource engineAudio;` |
| - | `public AudioClip fireClip;` |
| - | `private float accelInput;` |
| - | `private float brakeInput;` |
| - | `private float steerInput;` |
| - | `private float throttle;` |
| - | `private float steer;` |
| - | `private bool fireHeld;` |
| - | `private float forwardSpeed;` |
| - | `private float yawRate;` |
| - | `private float leftTrack;` |
| - | `private float rightTrack;` |
| - | `private float turretYaw;` |
| - | `private float gunElevation;` |
| - | `private float targetYaw;` |
| - | `private float targetElevation;` |
| - | `private float remoteLeft;` |
| - | `private float remoteRight;` |
| - | `private float remoteYaw;` |
| - | `private float remoteElevation;` |
| - | `private bool hasRemote;` |
| - | `private bool engineOn;` |
| - | `private bool wasOwner;` |
| - | `private double nextShotAt;` |
| - | `private float cameraYaw;` |
| - | `private float cameraPitch;` |
| - | `private float cameraDistance;` |
| - | `private float shake;` |
| - | `private float lastLookAt;` |
| - | `private bool zoomed;` |
| - | `private float fovBase;` |
| - | `private float zoomBlend;` |
| - | `private float recoil;` |
| - | `private float flash;` |
| - | `private Vector3 gunRest;` |
| - | `private Quaternion turretRest;` |
| - | `private Quaternion gunRestRotation;` |
| - | `private readonly RaycastHit[] hits;` |
| - | `private int groundMask;` |
| - | `private int aimMask;` |
| - | `private PhysicMaterial slippery;` |
| - | `private PlayableGraph graph;` |
| - | `private AnimationClipPlayable leftClip;` |
| - | `private AnimationClipPlayable rightClip;` |
| - | `private double leftTime;` |
| - | `private double rightTime;` |
| - | `private bool graphReady;` |
| - | `private bool tracksDirty;` |
| - | `private MaterialPropertyBlock lampBlock;` |
| - | `private XE tankEntity;` |
| - | `private PieceVitals tankVitals;` |
| - | `private TankDistanceCulling distanceCulling;` |
| - | `private AvatarMask leftMask;` |
| - | `private AvatarMask rightMask;` |
| - | `private float nextTracksAt;` |
| - | `private float nextRamIntent;` |
| - | `private float brakeLight;` |
| - | `private static readonly int EmissionId;` |
| - | `private Color rearEmission;` |
| - | `private Vector3 <GunAimPoint>k__BackingField;` |
| - | `private BuildingPiece tankPiece;` |

Properties: `public bool IsDriver { get; }`; `public float ReloadProgress { get; }`; `public bool Zoomed { get; }`; `public Vector3 GunAimPoint { get; set; }`; `public float AimError { get; }`; `public float SpeedKph { get; }`; `public float HealthFraction { get; }`; `public float SteerInput { get; }`; `public static bool InputBlocked { get; }`

<details><summary>methods (47)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F346BC |  | `public bool get_IsDriver()` |
| - | 0x2F34740 |  | `public float get_ReloadProgress()` |
| - | 0x2F34784 |  | `public bool get_Zoomed()` |
| - | 0x2F3478C |  | `public Vector3 get_GunAimPoint()` |
| - | 0x2F3479C |  | `private void set_GunAimPoint(Vector3 value)` |
| - | 0x2F347AC |  | `public float get_AimError()` |
| - | 0x2F34814 |  | `public float get_SpeedKph()` |
| - | 0x2F34920 |  | `public float get_HealthFraction()` |
| - | 0x2F34ABC |  | `private void Awake()` |
| - | 0x2F351F4 |  | `private void Start()` |
| - | 0x2F355B8 |  | `private void OnDestroy()` |
| - | 0x2F357B0 |  | `public void SetAccel(float value)` |
| - | 0x2F357CC |  | `public void SetBrake(float value)` |
| - | 0x2F357E8 |  | `public void SetSteer(float value)` |
| - | 0x2F35804 |  | `public float get_SteerInput()` |
| - | 0x2F3580C |  | `public void SetEngine(bool on)` |
| - | 0x2F3590C |  | `public void FillNet(float[] values)` |
| - | 0x2F35940 |  | `public void SetRemote(float[] values)` |
| - | 0x2F35CD4 |  | `public void AddLook(Vector2 degrees)` |
| - | 0x2F35D98 |  | `public void SetFireHeld(bool held)` |
| - | 0x2F35E10 |  | `public static bool get_InputBlocked()` |
| - | 0x2F3606C |  | `public void ToggleZoom()` |
| - | 0x2F356F8 |  | `private void SetZoom(bool on)` |
| - | 0x2F3607C |  | `private void FixedUpdate()` |
| - | 0x2F367AC |  | `private void Drive(Vector3 normal, float contact, float dt)` |
| - | 0x2F36D7C |  | `private void Upright(int grounded)` |
| - | 0x2F370E8 |  | `private void Update()` |
| - | 0x2F384A4 |  | `private void LateUpdate()` |
| - | 0x2F3737C |  | `private void OwnerChanged(bool owner)` |
| - | 0x2F37500 |  | `private void AimTurret(float dt)` |
| - | 0x2F38DFC |  | `private bool FirstHit(Vector3 origin, Vector3 direction, float distance, out RaycastHit best)` |
| - | 0x2F359A0 |  | `private void ApplyTurret()` |
| - | 0x2F3793C |  | `private void Fire()` |
| - | 0x2F39224 |  | `public void OnNetworkFire()` |
| - | 0x2F390C4 |  | `private void PlayShot(bool local)` |
| - | 0x2F351F8 |  | `private void BuildTracks()` |
| - | 0x2F39798 |  | `private static AvatarMask Mask(List<string> paths)` |
| - | 0x2F39260 |  | `private static void CollectBones(Transform node, string path, List<string> vehicleLeft, List<string> vehicleRight)` |
| - | 0x2F37AD8 |  | `private void AdvanceTracks(float dt)` |
| - | 0x2F3988C |  | `private static double Repeat(double time)` |
| - | 0x2F37D58 |  | `private void UpdateEffects(float dt)` |
| - | 0x2F39B20 |  | `private void SetBrakeLamp(float strength)` |
| - | 0x2F398B8 |  | `private static void SetRate(ParticleSystem system, float rate)` |
| - | 0x2F39A74 |  | `private static bool IsDark()` |
| - | 0x2F38554 |  | `private void UpdateCamera(float dt)` |
| - | 0x2F39C54 |  | `public void .ctor()` |
| - | 0x2F39CF4 |  | `private static void .cctor()` |

</details>

### public sealed class `TankDamageEffects` : MonoBehaviour  
`TypeDefIndex 3510`

| offset | field |
|---|---|
| - | `public ParticleSystem smoke;` |
| - | `public ParticleSystem flames;` |
| - | `public ParticleSystem sparks;` |
| - | `public ParticleSystem blastDust;` |
| - | `public Light fireLight;` |
| - | `public bool wreck;` |
| - | `private TankController tank;` |
| - | `private TankDistanceCulling culling;` |
| - | `private float nextCheck;` |
| - | `private float born;` |
| - | `private float nextCookoff;` |
| - | `private int cookoffs;` |

<details><summary>methods (9)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F39DC4 |  | `public static int Severity(float health)` |
| - | 0x2F370A4 |  | `public static float DriveScale(float health)` |
| - | 0x2F39E2C |  | `private void Awake()` |
| - | 0x2F39ED8 |  | `private void OnEnable()` |
| - | 0x2F39F08 |  | `private void Update()` |
| - | 0x2F3A170 |  | `public void ApplyHealth(float health, bool visible)` |
| - | 0x2F3A47C |  | `private static void Rate(ParticleSystem system, float rate)` |
| - | 0x2F3A588 |  | `private void OnDisable()` |
| - | 0x2F3A738 |  | `public void .ctor()` |

</details>

### public sealed class `TankDistanceCulling` : MonoBehaviour  
`TypeDefIndex 3511`

| offset | field |
|---|---|
| - | `public const float MobileDistance = 4500;` |
| - | `public const float DesktopDistance = 4500;` |
| - | `private bool <IsCulled>k__BackingField;` |
| - | `private float <CameraDistance>k__BackingField;` |
| - | `private TankController tank;` |
| - | `private Renderer[] renderers;` |
| - | `private bool[] originalHidden;` |
| - | `private ParticleSystem[] particles;` |
| - | `private Camera view;` |
| - | `private float nextCheck;` |

Properties: `public bool IsCulled { get; set; }`; `public float CameraDistance { get; set; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F3A740 |  | `public bool get_IsCulled()` |
| - | 0x2F3A748 |  | `private void set_IsCulled(bool value)` |
| - | 0x2F3A754 |  | `public float get_CameraDistance()` |
| - | 0x2F3A75C |  | `private void set_CameraDistance(float value)` |
| - | 0x2F3A764 |  | `public static float Cutoff(bool mobile, float cameraFar)` |
| - | 0x2F3A780 |  | `private void Awake()` |
| - | 0x2F3A988 |  | `private void OnEnable()` |
| - | 0x2F3A990 |  | `private void OnDisable()` |
| - | 0x2F3AB34 |  | `private void Update()` |
| - | 0x2F3A998 |  | `private void SetCulled(bool value)` |
| - | 0x2F3ADBC |  | `public void .ctor()` |

</details>

### public sealed class `TankHud` : MonoBehaviour  
`TypeDefIndex 3512`

| offset | field |
|---|---|
| - | `private static TankHud active;` |
| - | `public static bool ForceTouch;` |
| - | `private static readonly Color Ink;` |
| - | `private static readonly Color Edge;` |
| - | `private static readonly Color White;` |
| - | `private static readonly Color Muted;` |
| - | `private static readonly Color Amber;` |
| - | `private RectTransform rect;` |
| - | `private RectTransform safeRoot;` |
| - | `private RectTransform touchRoot;` |
| - | `private RectTransform stickZone;` |
| - | `private RectTransform stickBase;` |
| - | `private RectTransform stickKnob;` |
| - | `private RectTransform gunMarker;` |
| - | `private Canvas canvas;` |
| - | `private Font font;` |
| - | `private Image fireShade;` |
| - | `private Image armorFill;` |
| - | `private Image reloadFill;` |
| - | `private AdminShape zoomBack;` |
| - | `private Text armorText;` |
| - | `private Text speedText;` |
| - | `private Text reloadText;` |
| - | `private Text zoomText;` |
| - | `private Text desktopHint;` |
| - | `private Text armorLabel;` |
| - | `private Text damageText;` |
| - | `private Vector2 stickHome;` |
| - | `private Vector2 stickValue;` |
| - | `private int stickPointer;` |
| - | `private const float StickRange = 48;` |
| - | `private float nextText;` |
| - | `private Rect lastSafeArea;` |
| - | `private Vector2 lastScreen;` |
| - | `private string lastLanguage;` |

<details><summary>methods (26)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F3ADC4 |  | `public static void Sync(ScreenControlsManager manager, sH state)` |
| - | 0x2F3B254 |  | `private static Transform Find(Transform root, string name, string parent)` |
| - | 0x2F3AF60 |  | `private static TankHud Build(ScreenControlsManager manager)` |
| - | 0x2F3D4E0 |  | `private static RectTransform Node(string name, Transform parent, Vector2 anchor, Vector2 pivot, Vector2 position, Vector2 size)` |
| - | 0x2F3D6F0 |  | `private static RectTransform Stretch(string name, Transform parent)` |
| - | 0x2F3D84C |  | `private static Sprite SpriteOf(Transform t)` |
| - | 0x2F3D90C |  | `private static Image Picture(RectTransform rt, Sprite sprite, Color color, bool raycast = false)` |
| - | 0x2F3DA00 |  | `private static AdminShape Shape(string name, Transform parent, Vector2 anchor, Vector2 position, Vector2 size, float radius, Color color, float border = 0)` |
| - | 0x2F3DBF0 |  | `private Text Label(string name, Transform parent, Vector2 anchor, Vector2 pos, Vector2 size, int pixels, Color color, TextAnchor align, string text)` |
| - | 0x2F3DE24 |  | `private static void ButtonLayout(Transform button, Transform parent, Vector2 anchor, Vector2 pos, float size)` |
| - | 0x2F3B39C |  | `private void Assemble(Transform root)` |
| - | 0x2F3E104 |  | `private static string L(string ru, string en)` |
| - | 0x2F3E354 |  | `private TankController CurrentTank()` |
| - | 0x2F3E16C |  | `private void RefreshSafeArea()` |
| - | 0x2F3E424 |  | `private void OnDisable()` |
| - | 0x2F3E7B8 |  | `private void OnApplicationFocus(bool focused)` |
| - | 0x2F3E850 |  | `private void Update()` |
| - | 0x2F3E630 |  | `private void PushDrive(TankController tank)` |
| - | 0x2F3FB94 |  | `internal void StickDown(PointerEventData e)` |
| - | 0x2F3FD0C |  | `internal void StickDrag(PointerEventData e)` |
| - | 0x2F3FE78 |  | `internal void StickUp(PointerEventData e)` |
| - | 0x2F3E500 |  | `private void ReleaseStick()` |
| - | 0x2F3FEA4 |  | `internal void FireHeld(bool held)` |
| - | 0x2F3FF2C |  | `public void .ctor()` |
| - | 0x2F3FF3C |  | `private static void .cctor()` |
| - | 0x2F3FFCC |  | `private void <Assemble>b__45_0()` |

</details>

### public sealed class `TankStickRelay` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IDragHandler, IPointerUpHandler  
`TypeDefIndex 3513`

| offset | field |
|---|---|
| - | `internal TankHud Owner;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F40058 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2F400E8 |  | `public void OnDrag(PointerEventData e)` |
| - | 0x2F40178 |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2F40208 |  | `public void .ctor()` |

</details>

### public sealed class `TankFireRelay` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IDragHandler  
`TypeDefIndex 3514`

| offset | field |
|---|---|
| - | `internal TankHud Owner;` |
| - | `private int pointer;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F40210 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2F402B8 |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2F40358 |  | `public void OnDrag(PointerEventData e)` |
| - | 0x2F40400 |  | `private void OnDisable()` |
| - | 0x2F40488 |  | `public void .ctor()` |

</details>

### public sealed class `TankLookRelay` : MonoBehaviour, IPointerDownHandler, IEventSystemHandler, IPointerUpHandler, IDragHandler  
`TypeDefIndex 3515`

| offset | field |
|---|---|
| - | `private int pointer;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F40498 |  | `public void OnPointerDown(PointerEventData e)` |
| - | 0x2F404CC |  | `public void OnPointerUp(PointerEventData e)` |
| - | 0x2F404F8 |  | `public void OnDrag(PointerEventData e)` |
| - | 0x2F405A0 |  | `private void OnDisable()` |
| - | 0x2F405AC |  | `public void .ctor()` |

</details>

### public sealed class `TankWreckPush` : MonoBehaviour  
`TypeDefIndex 3516`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F405BC |  | `private void Start()` |
| - | 0x2F407B4 |  | `public void .ctor()` |

</details>

### public class `VehicleManager` : Xb  
`TypeDefIndex 3518`

| offset | field |
|---|---|
| 0x80 | `public CarController carController;` |
| - | `public TankController tankController;` |
| - | `public AircraftController aircraftController;` |
| - | `public FpvDroneController droneController;` |
| 0x88 | `private CarMove OFw;` |
| 0xB0 | `private CarInput OFJ;` |
| 0xD8 | `public HelicopterController heliController;` |
| 0xE0 | `private HeliMove OFX;` |
| 0x110 | `public Transform cameraPivot;` |
| 0x118 | `public Transform mountPivot;` |
| 0x120 | `private Rigidbody m_Rigidbody;` |
| 0x128 | `private float airDrag;` |
| 0x12C | `private float airAngularDrag;` |
| 0x130 | `private PieceVitals m_PieceVitals;` |
| 0x138 | `private float exitDistance;` |
| 0x13C | `private LayerMask m_CheckMask;` |
| 0x140 | `private VehicleManager.sV m_VehType;` |
| 0x148 | `private Transform m_ExitPoint;` |
| 0x150 | `private Transform frontExitPoint;` |
| 0x158 | `private Transform backExitPoint;` |
| 0x160 | `private BuildingPiece m_Piece;` |
| 0x168 | `private int OFT;` |
| 0x16C | `private bool OFL;` |
| 0x170 | `public PlayerManager m_CurrentDriver;` |
| 0x0 | `public static UT<VehicleManager> activeVehiclesList;` |
| 0x178 | `private Terrain OFz;` |
| - | `private bool <OFo>k__BackingField;` |
| - | `private bool <OFy>k__BackingField;` |
| - | `private const string TankFireName = "System.Void HyperHug.Games.Oxide.Features.Transport.VehicleManager::TankFire(System.Single,System.Single)";` |
| - | `private const string TankFiredName = "System.Void HyperHug.Games.Oxide.Features.Transport.VehicleManager::TankFired()";` |
| - | `private static readonly uint TankFireHash;` |
| - | `private const string AirPrefix = "System.Void HyperHug.Games.Oxide.Features.Transport.VehicleManager::";` |
| - | `private static readonly uint AirGunHash;` |
| - | `private static readonly uint AirRocketHash;` |
| - | `private static readonly uint AirReloadHash;` |
| - | `private static readonly uint AirCrashHash;` |
| - | `private static readonly uint DroneExitHash;` |
| - | `private int dbgSent;` |
| - | `private float dbgNext;` |

Properties: `private bool HasOwnerAuthority { get; }`; `public VehicleManager.sV sxD { get; }`; `public bool OFo { get; set; }`; `public bool OFy { get; set; }`; `public bool sxn { get; }`; `public bool sxV { get; }`; `public Transform sxg { get; }`; `public bool sxp { get; }`

<details><summary>methods (74)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F407BC |  | `private bool get_HasOwnerAuthority()` |
| - | 0x2F40844 |  | `public VehicleManager.sV get_sxD()` |
| - | 0x2F4084C |  | `public bool get_OFo()` |
| - | 0x2F40854 |  | `private void set_OFo(bool value)` |
| - | 0x2F40860 |  | `public bool get_OFy()` |
| - | 0x2F40868 |  | `private void set_OFy(bool value)` |
| - | 0x2F3473C |  | `public bool get_sxn()` |
| - | 0x2F40874 |  | `public bool get_sxV()` |
| - | 0x2F408A0 |  | `public Transform get_sxg()` |
| - | 0x2F408A8 |  | `public bool get_sxp()` |
| 0x382201C | 0x2F408AC |  | `private void dyg()` |
| 0x3822704 | 0x2F41238 |  | `private void dyp()` |
| 0x3822774 | 0x2F41300 |  | `private void dyv()` |
| 0x38223BC | 0x2F40CF0 |  | `private void dyS()` |
| 0x382249C | 0x2F4100C |  | `private void dyI(CarMove e)` |
| 0x38228D4 | 0x2F41AC8 |  | `private void dyM(CarInput e)` |
| 0x3822A14 | 0x2F41BD0 |  | `private void dze(CarMove e)` |
| 0x38227D4 | 0x2F3F928 |  | `public void dzf(float e)` |
| 0x3822854 | 0x2F3F9EC |  | `public void dzF(float e)` |
| 0x38225DC | 0x2F3FAB0 |  | `public void dzd(float e)` |
| 0x3822670 | 0x2F41100 |  | `public void dzc(float[] e)` |
| 0x382233C | 0x2F40C70 |  | `public void dzU(float e)` |
| 0x3822B54 | 0x2F41BD4 |  | `public void dzY()` |
| 0x3822B64 | 0x2F41BE8 |  | `public void dzW()` |
| 0x3822C24 | 0x2F41D4C |  | `private void dzE()` |
| 0x3822FD4 | 0x2F420D8 |  | `private void dzA(HeliMove e)` |
| 0x3823114 | 0x2F421D4 |  | `private void dzu(HeliMove e)` |
| 0x3823254 | 0x2F421D8 |  | `public void SetHeliThrottle(float i)` |
| 0x38232E8 | 0x2F4226C |  | `public void SetHeliTurn(float i)` |
| 0x382337C | 0x2F42300 |  | `public void dzk(float e)` |
| 0x3823410 | 0x2F42394 |  | `public void dzO(float e)` |
| 0x382352C | 0x2F42428 |  | `private void ShowFar()` |
| - | 0x2F42588 |  | `private void Awake()` |
| 0x3823720 | 0x2F4282C |  | `private void Update()` |
| 0x3823758 | 0x2F42864 |  | `private void dzQ()` |
| 0x3823844 | 0x2F429F4 |  | `public void dzH(bool e)` |
| 0x3823894 | 0x2F42B88 |  | `private void dzi(bool e)` |
| 0x38239B8 | 0x2F42B8C |  | `private bool dzw()` |
| - | 0x2F42C24 |  | `private static uint StableHash(string value)` |
| - | 0x2F38FEC |  | `public void SendTankFire(float yaw, float elevation)` |
| - | 0x2F3668C |  | `public void SendTankRamInput(float input)` |
| - | 0x2F42C9C |  | `private void SendRay(uint hash, Vector3 origin, Vector3 direction)` |
| - | 0x2F42D84 |  | `public void SendAirGun(Vector3 origin, Vector3 direction)` |
| - | 0x2F42E2C |  | `public void SendAirRocket(Vector3 origin, Vector3 direction)` |
| - | 0x2F42ED4 |  | `public void SendAirReload()` |
| - | 0x2F42F7C |  | `public void SendDroneExit()` |
| - | 0x2F43024 |  | `public void SendAirCrash(float impact)` |
| - | 0x2F430E8 |  | `protected static void AirTracerRpc(vd e, vo f, vt F)` |
| - | 0x2F43244 |  | `protected static void AirRocketRpc(vd e, vo f, vt F)` |
| - | 0x2F43350 |  | `protected static void AirStateRpc(vd e, vo f, vt F)` |
| - | 0x2F43488 |  | `protected static void DroneBeginRpc(vd e, vo f, vt F)` |
| - | 0x2F43554 |  | `protected static void DroneEndRpc(vd e, vo f, vt F)` |
| - | 0x2F43620 |  | `protected static void DronePropRpc(vd e, vo f, vt F)` |
| - | 0x2F437D8 |  | `protected static void HitConfirmedRpc(vd e, vo f, vt F)` |
| - | 0x2F4396C |  | `protected static void VehicleHurtRpc(vd e, vo f, vt F)` |
| - | 0x2F43A58 |  | `protected static void TankFiredRpc(vd e, vo f, vt F)` |
| - | 0x2F413EC |  | `private static void WriteQuat(vx writer, Quaternion q)` |
| - | 0x2F4144C |  | `private static void WriteFloats(vx writer, float[] values)` |
| - | 0x2F414E4 |  | `private void SendCommand(uint hash, vx writer)` |
| 0x3823A50 | 0x2F43B20 |  | `public void .ctor()` |
| 0x3823A58 | 0x2F43B28 |  | `private static void .cctor()` |
| 0x3823E0C | 0x2F441D8 | 12 | `public override bool Fuk()` |
| 0x3823E14 | 0x2F441E0 |  | `protected void dzJ(CarMove e)` |
| 0x3823E7C | 0x2F441E4 |  | `protected static void dzX(vd e, vo f, vt F)` |
| 0x3824024 | 0x2F441E8 |  | `protected void dzT(CarInput e)` |
| 0x3824038 | 0x2F441EC |  | `protected static void dzL(vd e, vo f, vt F)` |
| 0x38241DC | 0x2F441F0 |  | `protected void dzo(CarMove e)` |
| 0x38241F4 | 0x2F44208 |  | `protected static void dzy(vd e, vo f, vt F)` |
| 0x3824368 | 0x2F44470 |  | `protected void dzz(HeliMove e)` |
| 0x3824388 | 0x2F44474 |  | `protected static void dzh(vd e, vo f, vt F)` |
| 0x3824520 | 0x2F44478 |  | `protected void dzB(HeliMove e)` |
| 0x3824540 | 0x2F44498 |  | `protected static void dzm(vd e, vo f, vt F)` |
| 0x38246A4 | 0x2F44624 |  | `protected void dzR(bool e)` |
| 0x38246AC | 0x2F4462C |  | `protected static void dzb(vd e, vo f, vt F)` |

</details>

### public sealed class `WreckFire` : MonoBehaviour  
`TypeDefIndex 3519`

| offset | field |
|---|---|
| - | `public ParticleSystem[] fires;` |
| - | `public Light glow;` |
| - | `public AudioSource crackle;` |
| - | `public float burnSeconds;` |
| - | `public float fadeSeconds;` |
| - | `public float glowIntensity;` |
| - | `private float[] rates;` |
| - | `private float born;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F446C0 |  | `private void Awake()` |
| - | 0x2F44814 |  | `private void OnEnable()` |
| - | 0x2F448B4 |  | `private void Update()` |
| - | 0x2F44B6C |  | `public void .ctor()` |

</details>

### public sealed class `WreckPiece` : MonoBehaviour  
`TypeDefIndex 3520`

| offset | field |
|---|---|
| - | `public Rigidbody hull;` |
| - | `public Vector3 centre;` |
| - | `public float push;` |
| - | `public float spin;` |
| - | `public float smokeSeconds;` |
| - | `public ParticleSystem smoke;` |
| - | `private float born;` |

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F44B88 |  | `private void OnEnable()` |
| - | 0x2F44BA4 |  | `private void Start()` |
| - | 0x2F44FEC |  | `private void Update()` |
| - | 0x2F450A8 |  | `public void .ctor()` |

</details>
