# namespace `HyperHug.Games.BR24.Features.UiSystem.Core.Scripts.Base`  (1 types)

### public abstract class `BaseScreen<T>` : MonoBehaviour, rC  
`TypeDefIndex 3783`

| offset | field |
|---|---|
| 0x0 | `protected rA _closeButton;` |
| 0x0 | `private CanvasGroup kDm;` |
| - | `private bool <kDh>k__BackingField;` |
| - | `private bool <kDB>k__BackingField;` |
| - | `private Action kDz;` |
| - | `private bool raycastGated;` |
| - | `private static readonly List<GraphicRaycaster> gateBuffer;` |

Properties: `private GameObject rC.sRN { get; }`; `private Transform rC.sRq { get; }`; `public bool kDh { get; set; }`; `public bool kDB { get; set; }`; `protected virtual bool DeactivateOnHide { get; }`; `protected bool RaycastGated { get; }`

<details><summary>methods (198)</summary>

| RVA (Address attr) | RVA (comment) | slot | method |
|---|---|---|---|
| - | - |  | `private GameObject rC.get_sRN()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FA0 Offset: 0x43E4FA0 VA: 0x43E8FA0` |
| - | - |  | `\|-BaseScreen<object>.rC.get_sRN` |
| - | - |  | `*/` |
| - | - |  | `private Transform rC.get_sRq()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FB4 Offset: 0x43E4FB4 VA: 0x43E8FB4` |
| - | - |  | `\|-BaseScreen<object>.rC.get_sRq` |
| - | - |  | `*/` |
| - | - |  | `public bool get_kDh()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FC8 Offset: 0x43E4FC8 VA: 0x43E8FC8` |
| - | - |  | `\|-BaseScreen<object>.get_kDh` |
| - | - |  | `*/` |
| - | - |  | `protected void set_kDh(bool value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FD0 Offset: 0x43E4FD0 VA: 0x43E8FD0` |
| - | - |  | `\|-BaseScreen<object>.set_kDh` |
| - | - |  | `*/` |
| - | - |  | `public bool get_kDB()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FDC Offset: 0x43E4FDC VA: 0x43E8FDC` |
| - | - |  | `\|-BaseScreen<object>.get_kDB` |
| - | - |  | `*/` |
| - | - |  | `protected void set_kDB(bool value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FE4 Offset: 0x43E4FE4 VA: 0x43E8FE4` |
| - | - |  | `\|-BaseScreen<object>.set_kDB` |
| - | - |  | `*/` |
| - | - |  | `public void add_kDz(Action value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E8FF0 Offset: 0x43E4FF0 VA: 0x43E8FF0` |
| - | - |  | `\|-BaseScreen<object>.add_kDz` |
| - | - |  | `*/` |
| - | - |  | `public void remove_kDz(Action value)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E908C Offset: 0x43E508C VA: 0x43E908C` |
| - | - |  | `\|-BaseScreen<object>.remove_kDz` |
| - | - |  | `*/` |
| - | - |  | `private void Awake()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9128 Offset: 0x43E5128 VA: 0x43E9128` |
| - | - |  | `\|-BaseScreen<object>.Awake` |
| - | - |  | `*/` |
| - | - |  | `protected abstract void dYV(T e);` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x0 Offset: 0x0` |
| - | - |  | `\|-BaseScreen<object>.dYV` |
| - | - |  | `*/` |
| - | - |  | `public void dtw(rq e)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9234 Offset: 0x43E5234 VA: 0x43E9234` |
| - | - |  | `\|-BaseScreen<object>.dtw` |
| - | - |  | `*/` |
| - | - |  | `protected virtual void dke()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E92A8 Offset: 0x43E52A8 VA: 0x43E92A8` |
| - | - |  | `\|-BaseScreen<object>.dke` |
| - | - |  | `*/` |
| - | - |  | `public void Open()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E92AC Offset: 0x43E52AC VA: 0x43E92AC` |
| - | - |  | `\|-BaseScreen<object>.Open` |
| - | - |  | `*/` |
| - | - |  | `protected virtual void dkt()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9314 Offset: 0x43E5314 VA: 0x43E9314` |
| - | - |  | `\|-BaseScreen<object>.dkt` |
| - | - |  | `*/` |
| - | - |  | `public void Close()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9318 Offset: 0x43E5318 VA: 0x43E9318` |
| - | - |  | `\|-BaseScreen<object>.Close` |
| - | - |  | `*/` |
| - | - |  | `protected virtual void dYp()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E935C Offset: 0x43E535C VA: 0x43E935C` |
| - | - |  | `\|-BaseScreen<object>.dYp` |
| - | - |  | `*/` |
| - | - |  | `public void Show()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9360 Offset: 0x43E5360 VA: 0x43E9360` |
| - | - |  | `\|-BaseScreen<object>.Show` |
| - | - |  | `*/` |
| - | - |  | `protected virtual void dYv()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E949C Offset: 0x43E549C VA: 0x43E949C` |
| - | - |  | `\|-BaseScreen<object>.dYv` |
| - | - |  | `*/` |
| - | - |  | `protected virtual bool get_DeactivateOnHide()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E94A0 Offset: 0x43E54A0 VA: 0x43E94A0` |
| - | - |  | `\|-BaseScreen<object>.get_DeactivateOnHide` |
| - | - |  | `*/` |
| - | - |  | `public void Park()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E94A8 Offset: 0x43E54A8 VA: 0x43E94A8` |
| - | - |  | `\|-BaseScreen<object>.Park` |
| - | - |  | `*/` |
| - | - |  | `protected bool get_RaycastGated()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E95A4 Offset: 0x43E55A4 VA: 0x43E95A4` |
| - | - |  | `\|-BaseScreen<object>.get_RaycastGated` |
| - | - |  | `*/` |
| - | - |  | `private void SetRaycastGate(bool blocked)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E95AC Offset: 0x43E55AC VA: 0x43E95AC` |
| - | - |  | `\|-BaseScreen<object>.SetRaycastGate` |
| - | - |  | `*/` |
| - | - |  | `public void GateNew(Transform root)` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9820 Offset: 0x43E5820 VA: 0x43E9820` |
| - | - |  | `\|-BaseScreen<object>.GateNew` |
| - | - |  | `*/` |
| - | - |  | `public void Hide()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9AA4 Offset: 0x43E5AA4 VA: 0x43E9AA4` |
| - | - |  | `\|-BaseScreen<object>.Hide` |
| - | - |  | `*/` |
| - | - |  | `protected abstract void dYI();` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x0 Offset: 0x0` |
| - | - |  | `\|-BaseScreen<object>.dYI` |
| - | - |  | `*/` |
| - | - |  | `private void dtJ()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9BF4 Offset: 0x43E5BF4 VA: 0x43E9BF4` |
| - | - |  | `\|-BaseScreen<object>.dtJ` |
| - | - |  | `*/` |
| - | - |  | `protected abstract void dWe();` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x0 Offset: 0x0` |
| - | - |  | `\|-BaseScreen<object>.dWe` |
| - | - |  | `*/` |
| - | - |  | `private void dtX()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9BF8 Offset: 0x43E5BF8 VA: 0x43E9BF8` |
| - | - |  | `\|-BaseScreen<object>.dtX` |
| - | - |  | `*/` |
| - | - |  | `protected void .ctor()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9BFC Offset: 0x43E5BFC VA: 0x43E9BFC` |
| - | - |  | `\|-BaseScreen<object>..ctor` |
| - | - |  | `*/` |
| - | - |  | `private GameObject dtT()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9C04 Offset: 0x43E5C04 VA: 0x43E9C04` |
| - | - |  | `\|-BaseScreen<object>.dtT` |
| - | - |  | `*/` |
| - | - |  | `private Transform dtL()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9C18 Offset: 0x43E5C18 VA: 0x43E9C18` |
| - | - |  | `\|-BaseScreen<object>.dtL` |
| - | - |  | `*/` |
| - | - |  | `private void dto()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9C2C Offset: 0x43E5C2C VA: 0x43E9C2C` |
| - | - |  | `\|-BaseScreen<object>.dto` |
| - | - |  | `*/` |
| - | - |  | `private static void .cctor()` |
| - | - |  | `/* GenericInstMethod :` |
| - | - |  | `\|` |
| - | - |  | `\|-RVA: 0x43E9C98 Offset: 0x43E5C98 VA: 0x43E9C98` |
| - | - |  | `\|-BaseScreen<object>..cctor` |
| - | - |  | `*/` |

</details>
