#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace runtime_scene {
// Exact Unity build d0a398d6e8c5d505. All operations are remote reads.
constexpr uintptr_t kObjectRegistry=0x17fed20;
constexpr std::array<uintptr_t,8> kColliderVtables={0x178e130,0x178e288,0x178e4e0,0x178e638,0x178eaa8,0x178edf8,0x17aa500,0x17ac478};
constexpr uintptr_t kBoxVtable=0x178e638;
struct Object {uintptr_t address;int32_t instance;uintptr_t vtable;bool box,enabled,trigger;};
struct Snapshot {bool readable=false;uint32_t slots=0,objects=0;uintptr_t registry=0,storage=0;std::vector<Object> colliders;};
template<class Reader> Snapshot capture(const Reader& reader,uintptr_t unityBase){
 Snapshot result;uintptr_t registry=0,storage=0;uint32_t mask=0;
 if(!reader.get(unityBase+kObjectRegistry,registry)||!registry||!reader.get(registry,storage)||!storage||!reader.get(registry+8,mask))return result;
 // Hash-map mask encodes byte offsets in units of eight; slot stride is24.
 if((mask&7)!=0||mask>0x1ffff8)return result;
 uint32_t capacity=mask/8+1;if(capacity<8||(capacity&(capacity-1)))return result;
 struct Entry {uint32_t hash,pad;int32_t key;uint32_t pad2;uintptr_t object;};
 static_assert(sizeof(Entry)==24);
 std::vector<Entry> entries(capacity);
 if(!reader.read(storage,entries.data(),entries.size()*sizeof(Entry)))return result;
 result.slots=capacity;result.registry=registry;result.storage=storage;
 for(const auto& entry:entries){
  if(entry.hash>=0xfffffffeu||!entry.object)continue;
  struct Header {uintptr_t vtable;int32_t instance;uint32_t rest;} header{};
  if(!reader.get(entry.object,header)||header.instance!=entry.key)continue;
  ++result.objects;if(header.vtable<unityBase)continue;
  uintptr_t relative=header.vtable-unityBase;bool collider=false;for(uintptr_t value:kColliderVtables)if(value==relative){collider=true;break;}
  if(!collider)continue;
  uint8_t flags[2]{};if(!reader.read(entry.object+0x4c,flags,2)||flags[0]>1||flags[1]>1)continue;
  result.colliders.push_back({entry.object,entry.key,relative,relative==kBoxVtable,flags[1]!=0,flags[0]!=0});
 }
 // Reject a snapshot if registry/storage changed while scanning (scene load/rehash).
 uintptr_t registryAfter=0,storageAfter=0;uint32_t maskAfter=0;
 if(!reader.get(unityBase+kObjectRegistry,registryAfter)||registryAfter!=registry||!reader.get(registry,storageAfter)||storageAfter!=storage||!reader.get(registry+8,maskAfter)||maskAfter!=mask){result.colliders.clear();return result;}
 result.readable=true;return result;
}
}
