# namespace `GooglePlayGames.BasicApi.Nearby`  (10 types)

### public struct `AdvertisingResult`  
`TypeDefIndex 3845`

| offset | field |
|---|---|
| 0x0 | `private readonly ResponseStatus mStatus;` |
| 0x8 | `private readonly string mLocalEndpointName;` |

Properties: `public bool Succeeded { get; }`; `public ResponseStatus Status { get; }`; `public string LocalEndpointName { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3798884 | 0x2F7D9FC |  | `public bool get_Succeeded()` |
| 0x3798894 | 0x2F7DA04 |  | `public ResponseStatus get_Status()` |
| 0x379889C | 0x2F7DA0C |  | `public string get_LocalEndpointName()` |
| 0x3798818 | 0x2F7DA14 |  | `public void .ctor(ResponseStatus status, string localEndpointName)` |

</details>

### public struct `ConnectionRequest`  
`TypeDefIndex 3846`

| offset | field |
|---|---|
| 0x0 | `private readonly EndpointDetails mRemoteEndpoint;` |
| 0x18 | `private readonly byte[] mPayload;` |

Properties: `public EndpointDetails RemoteEndpoint { get; }`; `public byte[] Payload { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3798A70 | 0x2F7DA1C |  | `public EndpointDetails get_RemoteEndpoint()` |
| 0x3798A84 | 0x2F7DA28 |  | `public byte[] get_Payload()` |
| 0x37988A4 | 0x2F7DA30 |  | `public void .ctor(string remoteEndpointId, string remoteEndpointName, string serviceId, byte[] payload)` |

</details>

### public struct `ConnectionResponse`  
`TypeDefIndex 3848`

| offset | field |
|---|---|
| 0x0 | `private static readonly byte[] EmptyPayload;` |
| 0x0 | `private readonly long mLocalClientId;` |
| 0x8 | `private readonly string mRemoteEndpointId;` |
| 0x10 | `private readonly ConnectionResponse.Status mResponseStatus;` |
| 0x18 | `private readonly byte[] mPayload;` |

Properties: `public long LocalClientId { get; }`; `public string RemoteEndpointId { get; }`; `public ConnectionResponse.Status ResponseStatus { get; }`; `public byte[] Payload { get; }`

<details><summary>methods (11)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3798B44 | 0x2F7DA3C |  | `public long get_LocalClientId()` |
| 0x3798B4C | 0x2F7DA44 |  | `public string get_RemoteEndpointId()` |
| 0x3798B54 | 0x2F7DA4C |  | `public ConnectionResponse.Status get_ResponseStatus()` |
| 0x3798B5C | 0x2F7DA54 |  | `public byte[] get_Payload()` |
| 0x3798A8C | 0x2F7DA5C |  | `private void .ctor(long localClientId, string remoteEndpointId, ConnectionResponse.Status code, byte[] payload)` |
| 0x3798B64 | 0x2F7DA68 |  | `public static ConnectionResponse Rejected(long localClientId, string remoteEndpointId)` |
| 0x3798BE8 | 0x2F7DA74 |  | `public static ConnectionResponse NetworkNotConnected(long localClientId, string remoteEndpointId)` |
| 0x3798C6C | 0x2F7DA80 |  | `public static ConnectionResponse InternalError(long localClientId, string remoteEndpointId)` |
| 0x3798CF0 | 0x2F7DA8C |  | `public static ConnectionResponse EndpointNotConnected(long localClientId, string remoteEndpointId)` |
| 0x3798D74 | 0x2F7DA98 |  | `public static ConnectionResponse Accepted(long localClientId, string remoteEndpointId, byte[] payload)` |
| 0x3798D94 | 0x2F7DAA4 |  | `public static ConnectionResponse AlreadyConnected(long localClientId, string remoteEndpointId)` |

</details>

### public class `DummyNearbyConnectionClient` : INearbyConnectionClient  
`TypeDefIndex 3849`

<details><summary>methods (18)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3798E8C | 0x2F7DAB0 | 4 | `public int MaxUnreliableMessagePayloadLength()` |
| 0x3798E94 | 0x2F7DAB8 | 5 | `public int MaxReliableMessagePayloadLength()` |
| 0x3798E9C | 0x2F7DAC0 | 6 | `public void SendReliable(List<string> recipientEndpointIds, byte[] payload)` |
| 0x3798F24 | 0x2F7DAC4 | 7 | `public void SendUnreliable(List<string> recipientEndpointIds, byte[] payload)` |
| 0x3798FAC | 0x2F7DAC8 | 8 | `public void StartAdvertising(string name, List<string> appIdentifiers, Nullable<TimeSpan> advertisingDuration, Action<AdvertisingResult> resultCallback, Action<ConnectionRequest> connectionRequestCallback)` |
| 0x379902C | 0x2F7DACC | 9 | `public void StopAdvertising()` |
| 0x37990B4 | 0x2F7DAD0 | 10 | `public void SendConnectionRequest(string name, string remoteEndpointId, byte[] payload, Action<ConnectionResponse> responseCallback, IMessageListener listener)` |
| 0x37991C4 | 0x2F7DAD4 | 11 | `public void AcceptConnectionRequest(string remoteEndpointId, byte[] payload, IMessageListener listener)` |
| 0x379924C | 0x2F7DAD8 | 12 | `public void StartDiscovery(string serviceId, Nullable<TimeSpan> advertisingTimeout, IDiscoveryListener listener)` |
| 0x37992D4 | 0x2F7DADC | 13 | `public void StopDiscovery(string serviceId)` |
| 0x379935C | 0x2F7DAE0 | 14 | `public void RejectConnectionRequest(string requestingEndpointId)` |
| 0x37993E4 | 0x2F7DAE4 | 15 | `public void DisconnectFromEndpoint(string remoteEndpointId)` |
| 0x379946C | 0x2F7DAE8 | 16 | `public void StopAllConnections()` |
| 0x37994F4 | 0x2F7DAEC |  | `public string LocalEndpointId()` |
| 0x379953C | 0x2F7DAF4 |  | `public string LocalDeviceId()` |
| 0x379958C | 0x2F7DAFC | 17 | `public string GetAppBundleId()` |
| 0x37995DC | 0x2F7DB04 | 18 | `public string GetServiceId()` |
| 0x379962C | 0x2F7DB0C |  | `public void .ctor()` |

</details>

### public struct `EndpointDetails`  
`TypeDefIndex 3850`

| offset | field |
|---|---|
| 0x0 | `private readonly string mEndpointId;` |
| 0x8 | `private readonly string mName;` |
| 0x10 | `private readonly string mServiceId;` |

Properties: `public string EndpointId { get; }`; `public string Name { get; }`; `public string ServiceId { get; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3799634 | 0x2F7DB14 |  | `public string get_EndpointId()` |
| 0x379963C | 0x2F7DB1C |  | `public string get_Name()` |
| 0x3799644 | 0x2F7DB24 |  | `public string get_ServiceId()` |
| 0x37989C4 | 0x2F7DB2C |  | `public void .ctor(string endpointId, string name, string serviceId)` |

</details>

### public interface `IDiscoveryListener`  
`TypeDefIndex 3851`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void OnEndpointFound(EndpointDetails discoveredEndpoint);` |
| - | - |  | `public abstract void OnEndpointLost(string lostEndpointId);` |

</details>

### public interface `IMessageListener`  
`TypeDefIndex 3852`

<details><summary>methods (2)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract void OnMessageReceived(string remoteEndpointId, byte[] data, bool isReliableMessage);` |
| - | - |  | `public abstract void OnRemoteEndpointDisconnected(string remoteEndpointId);` |

</details>

### public interface `INearbyConnectionClient`  
`TypeDefIndex 3853`

<details><summary>methods (15)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `public abstract int MaxUnreliableMessagePayloadLength();` |
| - | - |  | `public abstract int MaxReliableMessagePayloadLength();` |
| - | - |  | `public abstract void SendReliable(List<string> recipientEndpointIds, byte[] payload);` |
| - | - |  | `public abstract void SendUnreliable(List<string> recipientEndpointIds, byte[] payload);` |
| - | - |  | `public abstract void StartAdvertising(string name, List<string> appIdentifiers, Nullable<TimeSpan> advertisingDuration, Action<AdvertisingResult> resultCallback, Action<ConnectionRequest> connectionRequestCallback);` |
| - | - |  | `public abstract void StopAdvertising();` |
| - | - |  | `public abstract void SendConnectionRequest(string name, string remoteEndpointId, byte[] payload, Action<ConnectionResponse> responseCallback, IMessageListener listener);` |
| - | - |  | `public abstract void AcceptConnectionRequest(string remoteEndpointId, byte[] payload, IMessageListener listener);` |
| - | - |  | `public abstract void StartDiscovery(string serviceId, Nullable<TimeSpan> advertisingTimeout, IDiscoveryListener listener);` |
| - | - |  | `public abstract void StopDiscovery(string serviceId);` |
| - | - |  | `public abstract void RejectConnectionRequest(string requestingEndpointId);` |
| - | - |  | `public abstract void DisconnectFromEndpoint(string remoteEndpointId);` |
| - | - |  | `public abstract void StopAllConnections();` |
| - | - |  | `public abstract string GetAppBundleId();` |
| - | - |  | `public abstract string GetServiceId();` |

</details>

### public enum `InitializationStatus`  
`TypeDefIndex 3854`

| offset | field |
|---|---|
| - | `public int value__;` |
| - | `public const InitializationStatus Success = 0;` |
| - | `public const InitializationStatus VersionUpdateRequired = 1;` |
| - | `public const InitializationStatus InternalError = 2;` |

### public struct `NearbyConnectionConfiguration`  
`TypeDefIndex 3855`

| offset | field |
|---|---|
| - | `public const int MaxUnreliableMessagePayloadLength = 1168;` |
| - | `public const int MaxReliableMessagePayloadLength = 4096;` |
| 0x0 | `private readonly Action<InitializationStatus> mInitializationCallback;` |
| 0x8 | `private readonly long mLocalClientId;` |

Properties: `public long LocalClientId { get; }`; `public Action<InitializationStatus> InitializationCallback { get; }`

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x37996BC | 0x2F7DB38 |  | `public long get_LocalClientId()` |
| 0x37996C4 | 0x2F7DB40 |  | `public Action<InitializationStatus> get_InitializationCallback()` |
| 0x379964C | 0x2F7DB48 |  | `public void .ctor(Action<InitializationStatus> callback, long localClientId)` |

</details>
