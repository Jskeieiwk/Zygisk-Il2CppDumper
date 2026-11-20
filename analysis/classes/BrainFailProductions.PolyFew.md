# namespace `BrainFailProductions.PolyFew`  (4 types)

### public class `ObjectMaterialLinks` : MonoBehaviour  
`TypeDefIndex 3994`

| offset | field |
|---|---|
| 0x20 | `private List<RX.MaterialEntity> linkedEntities;` |
| 0x28 | `public List<Rt.MaterialProperties> materialsProperties;` |
| 0x30 | `public Texture2D linkedAttrImg;` |

Properties: `public List<RX.MaterialEntity> CdF { get; set; }`

<details><summary>methods (4)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B9D570 | 0x2F89C54 |  | `public List<RX.MaterialEntity> get_CdF()` |
| 0x3B9D578 | 0x2F89C5C |  | `public void set_CdF(List<RX.MaterialEntity> value)` |
| 0x3B9D8B4 | 0x2F89C60 |  | `private void Start()` |
| 0x3B9DBDC | 0x2F89C64 |  | `public void .ctor()` |

</details>

### public class `SerializableDictionary<TKey, TValue>` : IDictionary<TKey, TValue>, ICollection<KeyValuePair<TKey, TValue>>, IEnumerable<KeyValuePair<TKey, TValue>>, IEnumerable  
`TypeDefIndex 3997`

| offset | field |
|---|---|
| 0x0 | `private int[] _Buckets;` |
| 0x0 | `private int[] _HashCodes;` |
| 0x0 | `private int[] _Next;` |
| 0x0 | `private int _Count;` |
| 0x0 | `private int _Version;` |
| 0x0 | `private int _FreeList;` |
| 0x0 | `private int _FreeCount;` |
| 0x0 | `private TKey[] _Keys;` |
| 0x0 | `private TValue[] _Values;` |
| 0x0 | `private IEqualityComparer<TKey> trz;` |

Properties: `public Dictionary<TKey, TValue> Cdc { get; }`; `public int Count { get; }`; `public TValue Item { get; }`; `public TValue Item { get; set; }`; `public ICollection<TKey> Keys { get; }`; `public ICollection<TValue> Values { get; }`; `public bool IsReadOnly { get; }`

<details><summary>methods (204)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `private IEnumerator<KeyValuePair<TKey, TValue>> System.Collections.Generic.IEnumerable<System.Collections.Generic.KeyValuePair<TKey,TValue>>.GetEnumerator()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4A88 Offset: 0x3EC0A88 VA: 0x3EC4A88` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.System.Collections.Generic.IEnumerable<System.Collections.Generic.KeyValuePair<TKey,TValue>>.GetEnumerator` |
| - | - |  | `*/` |
| - | - |  | `private IEnumerator System.Collections.IEnumerable.GetEnumerator()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4A90 Offset: 0x3EC0A90 VA: 0x3EC4A90` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.System.Collections.IEnumerable.GetEnumerator` |
| - | - |  | `*/` |
| - | - |  | `public Dictionary<TKey, TValue> get_Cdc()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4A98 Offset: 0x3EC0A98 VA: 0x3EC4A98` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Cdc` |
| - | - |  | `*/` |
| - | - |  | `public int get_Count()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4AA0 Offset: 0x3EC0AA0 VA: 0x3EC4AA0` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Count` |
| - | - |  | `*/` |
| - | - |  | `public TValue get_Item(TKey key, TValue defaultValue)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4AA8 Offset: 0x3EC0AA8 VA: 0x3EC4AA8` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Item` |
| - | - |  | `*/` |
| - | - |  | `public TValue get_Item(TKey key)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4B6C Offset: 0x3EC0B6C VA: 0x3EC4B6C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Item` |
| - | - |  | `*/` |
| - | - |  | `public void set_Item(TKey key, TValue value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C30 Offset: 0x3EC0C30 VA: 0x3EC4C30` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.set_Item` |
| - | - |  | `*/` |
| - | - |  | `public ICollection<TKey> get_Keys()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C34 Offset: 0x3EC0C34 VA: 0x3EC4C34` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Keys` |
| - | - |  | `*/` |
| - | - |  | `public ICollection<TValue> get_Values()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C3C Offset: 0x3EC0C3C VA: 0x3EC4C3C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_Values` |
| - | - |  | `*/` |
| - | - |  | `public bool get_IsReadOnly()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C44 Offset: 0x3EC0C44 VA: 0x3EC4C44` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.get_IsReadOnly` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C4C Offset: 0x3EC0C4C VA: 0x3EC4C4C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor(int capacity)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C54 Offset: 0x3EC0C54 VA: 0x3EC4C54` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor(IEqualityComparer<TKey> comparer)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C5C Offset: 0x3EC0C5C VA: 0x3EC4C5C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor(int capacity, IEqualityComparer<TKey> comparer)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C64 Offset: 0x3EC0C64 VA: 0x3EC4C64` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor(IDictionary<TKey, TValue> dictionary)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C6C Offset: 0x3EC0C6C VA: 0x3EC4C6C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public void .ctor(IDictionary<TKey, TValue> dictionary, IEqualityComparer<TKey> comparer)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C74 Offset: 0x3EC0C74 VA: 0x3EC4C74` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>..ctor` |
| - | - |  | `*/` |
| - | - |  | `public bool UTj(TValue e)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C7C Offset: 0x3EC0C7C VA: 0x3EC4C7C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTj` |
| - | - |  | `*/` |
| - | - |  | `public bool ContainsKey(TKey key)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C84 Offset: 0x3EC0C84 VA: 0x3EC4C84` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.ContainsKey` |
| - | - |  | `*/` |
| - | - |  | `public void Clear()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C8C Offset: 0x3EC0C8C VA: 0x3EC4C8C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Clear` |
| - | - |  | `*/` |
| - | - |  | `public void Add(TKey key, TValue value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C90 Offset: 0x3EC0C90 VA: 0x3EC4C90` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Add` |
| - | - |  | `*/` |
| - | - |  | `private void UTa(int e, bool f)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C94 Offset: 0x3EC0C94 VA: 0x3EC4C94` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTa` |
| - | - |  | `*/` |
| - | - |  | `private void UTQ()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C98 Offset: 0x3EC0C98 VA: 0x3EC4C98` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTQ` |
| - | - |  | `*/` |
| - | - |  | `public bool Remove(TKey key)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4C9C Offset: 0x3EC0C9C VA: 0x3EC4C9C` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Remove` |
| - | - |  | `*/` |
| - | - |  | `private void UTH(TKey e, TValue f, bool F)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CA4 Offset: 0x3EC0CA4 VA: 0x3EC4CA4` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTH` |
| - | - |  | `*/` |
| - | - |  | `private void UTi(int e)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CA8 Offset: 0x3EC0CA8 VA: 0x3EC4CA8` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTi` |
| - | - |  | `*/` |
| - | - |  | `private int UTw(TKey e)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CAC Offset: 0x3EC0CAC VA: 0x3EC4CAC` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTw` |
| - | - |  | `*/` |
| - | - |  | `public bool TryGetValue(TKey key, out TValue value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CB4 Offset: 0x3EC0CB4 VA: 0x3EC4CB4` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.TryGetValue` |
| - | - |  | `*/` |
| - | - |  | `public void Add(KeyValuePair<TKey, TValue> item)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CE4 Offset: 0x3EC0CE4 VA: 0x3EC4CE4` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Add` |
| - | - |  | `*/` |
| - | - |  | `public bool Contains(KeyValuePair<TKey, TValue> item)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CE8 Offset: 0x3EC0CE8 VA: 0x3EC4CE8` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Contains` |
| - | - |  | `*/` |
| - | - |  | `public void CopyTo(KeyValuePair<TKey, TValue>[] array, int index)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CF0 Offset: 0x3EC0CF0 VA: 0x3EC4CF0` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.CopyTo` |
| - | - |  | `*/` |
| - | - |  | `public bool Remove(KeyValuePair<TKey, TValue> item)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CF4 Offset: 0x3EC0CF4 VA: 0x3EC4CF4` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.Remove` |
| - | - |  | `*/` |
| - | - |  | `public SerializableDictionary.Enumerator<TKey, TValue> GetEnumerator()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4CFC Offset: 0x3EC0CFC VA: 0x3EC4CFC` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.GetEnumerator` |
| - | - |  | `*/` |
| - | - |  | `private IEnumerator UTJ()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4DC0 Offset: 0x3EC0DC0 VA: 0x3EC4DC0` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTJ` |
| - | - |  | `*/` |
| - | - |  | `private IEnumerator<KeyValuePair<TKey, TValue>> UTX()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x3EC4DC8 Offset: 0x3EC0DC8 VA: 0x3EC4DC8` |
| - | - |  | `\|-SerializableDictionary<__Il2CppFullySharedGenericType, __Il2CppFullySharedGenericType>.UTX` |
| - | - |  | `*/` |

</details>

### public class `ToleranceSphere` : ScriptableObject  
`TypeDefIndex 3998`

| offset | field |
|---|---|
| 0x18 | `public Vector3 worldPosition;` |
| 0x24 | `public float diameter;` |
| 0x28 | `public Color color;` |
| 0x38 | `public float preservationStrength;` |
| 0x3C | `public bool isHidden;` |

<details><summary>methods (3)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B9DCB8 | 0x2F89C6C |  | `public void .ctor(Vector3 worldPosition, float diameter, Color color, float preservationStrength, bool isHidden = false)` |
| 0x3B9DD3C | 0x2F89C74 |  | `public void UTT(ToleranceSphereJson e)` |
| 0x3B9DD80 | 0x2F89C78 |  | `public void UTL(Vector3 e, float f, Color F, float d, bool c = false)` |

</details>

### public class `ToleranceSphereJson`  
`TypeDefIndex 3999`

| offset | field |
|---|---|
| 0x10 | `public Vector3 worldPosition;` |
| 0x1C | `public float diameter;` |
| 0x20 | `public Color color;` |
| 0x30 | `public float preservationStrength;` |
| 0x34 | `public bool isHidden;` |

<details><summary>methods (5)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| 0x3B9DDA4 | 0x2F89C7C |  | `public void .ctor(Vector3 worldPosition, float diameter, Color color, float preservationStrength, bool isHidden = false)` |
| 0x3B9DE28 | 0x2F89C84 |  | `public void .ctor(ToleranceSphere toleranceSphere)` |
| 0x3B9DF64 | 0x2F89C8C |  | `public void UTo(Vector3 e, float f, Color F, float d, bool c = false)` |
| 0x3B9DEBC | 0x2F89C90 |  | `public void UTy(ToleranceSphere e)` |
| 0x3B9DF88 | 0x2F89C94 |  | `public void UTz(ref ToleranceSphere e)` |

</details>
