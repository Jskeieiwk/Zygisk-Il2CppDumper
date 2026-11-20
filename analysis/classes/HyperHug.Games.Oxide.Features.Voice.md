# namespace `HyperHug.Games.Oxide.Features.Voice`  (2 types)

### public sealed class `PcmVoiceChat` : MonoBehaviour  
`TypeDefIndex 3393`

| offset | field |
|---|---|
| - | `public const string CommandName = "System.Void Oxide.PlayerManager::CmdVoicePcm16(System.Byte[])";` |
| - | `public const string RpcName = "System.Void Oxide.PlayerManager::RpcVoicePcm16(System.Byte[])";` |
| - | `public const byte PlayerManagerComponent = 4;` |
| - | `public const int SampleRate = 16000;` |
| - | `public const int ChunkSamples = 1600;` |
| - | `public const float Range = 14;` |
| - | `public const float TailSeconds = 0.22;` |
| - | `private const int MaxPcmBytes = 8192;` |
| - | `private static readonly uint CommandHash;` |
| - | `private static PcmVoiceChat instance;` |
| - | `private bool pttButtonHeld;` |
| - | `private bool open;` |
| - | `private float tailUntil;` |
| - | `private string device;` |
| - | `private AudioClip loop;` |
| - | `private int readPosition;` |
| - | `private GameController controller;` |
| - | `private float nextFind;` |
| - | `private GameObject boundButton;` |
| - | `private bool permissionAsked;` |

<details><summary>methods (20)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0B1DC |  | `private static uint StableHash(string value)` |
| - | 0x2F0B254 |  | `private static void Register()` |
| - | 0x2F0B33C |  | `private static void Boot()` |
| - | 0x2F0B484 |  | `private static void OnVoiceRpc(vd behaviour, vo reader, vt connection)` |
| - | 0x2F0B7E0 |  | `private GameController Controller()` |
| - | 0x2F0BB24 |  | `private void Update()` |
| - | 0x2F0C25C |  | `private static bool Typing()` |
| - | 0x2F0BDF4 |  | `private void BindButton(GameController gc)` |
| - | 0x2F0C758 |  | `private bool HasPermission()` |
| - | 0x2F0C3D0 |  | `private bool StartCapture()` |
| - | 0x2F0C6E4 |  | `private void StopCapture()` |
| - | 0x2F0C544 |  | `private void Poll(PlayerManager me)` |
| - | 0x2F0C79C |  | `private static byte[] ToPcm16(float[] samples)` |
| - | 0x2F0C8BC |  | `private static void Send(PlayerManager me, byte[] pcm)` |
| - | 0x2F0CC44 |  | `private void OnDestroy()` |
| - | 0x2F0CD20 |  | `public void .ctor()` |
| - | 0x2F0CD30 |  | `private static void .cctor()` |
| - | 0x2F0CD94 |  | `private void <BindButton>b__27_0(BaseEventData _)` |
| - | 0x2F0CDA0 |  | `private void <BindButton>b__27_1(BaseEventData _)` |
| - | 0x2F0CDA8 |  | `private void <BindButton>b__27_2(BaseEventData _)` |

</details>

### public sealed class `PcmVoiceSpeaker` : MonoBehaviour  
`TypeDefIndex 3394`

| offset | field |
|---|---|
| - | `private const int RingCapacity = 96000;` |
| - | `private const int StreamClipSamples = 4096;` |
| - | `private const int MaxBufferedSamples = 16000;` |
| - | `private const int TargetBufferedSamples = 8000;` |
| - | `private const float IndicatorSeconds = 0.4;` |
| - | `private AudioSource source;` |
| - | `private AudioClip clip;` |
| - | `private readonly object ringLock;` |
| - | `private float[] ring;` |
| - | `private int write;` |
| - | `private int read;` |
| - | `private int count;` |
| - | `private Image indicator;` |
| - | `private float lastReceived;` |
| - | `private bool indicatorOn;` |

<details><summary>methods (8)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | 0x2F0CDB0 |  | `public void BindIndicator(Image image)` |
| - | 0x2F0B8BC |  | `public void Enqueue(byte[] pcm)` |
| - | 0x2F0CDB8 |  | `private void Setup()` |
| - | 0x2F0CFAC |  | `private void OnRead(float[] data)` |
| - | 0x2F0D12C |  | `private void Update()` |
| - | 0x2F0D1F4 |  | `private void OnDisable()` |
| - | 0x2F0D280 |  | `private void OnDestroy()` |
| - | 0x2F0D310 |  | `public void .ctor()` |

</details>
