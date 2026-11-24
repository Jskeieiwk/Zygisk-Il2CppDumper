#include "../native/runtime_scene.h"
#include <cassert>
#include <cstring>
struct Memory {
 std::vector<uint8_t> bytes=std::vector<uint8_t>(0x1801000);
 bool read(uintptr_t address,void* out,size_t n)const{if(address>bytes.size()||n>bytes.size()-address)return false;std::memcpy(out,bytes.data()+address,n);return true;}
 template<class T>bool get(uintptr_t address,T& out)const{return read(address,&out,sizeof(out));}
 template<class T>void put(uintptr_t address,T value){std::memcpy(bytes.data()+address,&value,sizeof(value));}
};
int main(){Memory m;uintptr_t base=0,registry=0x1000,slots=0x2000;
 m.put(runtime_scene::kObjectRegistry,registry);m.put(registry,slots);m.put(registry+8,uint32_t(56));
 for(int i=0;i<8;i++)m.put(slots+i*24,uint32_t(0xffffffff));
 for(int i=0;i<3;i++){uintptr_t object=0x3000+i*0x100;m.put(slots+i*24,uint32_t(4+i*4));m.put(slots+i*24+8,int32_t(i+10));m.put(slots+i*24+16,object);m.put(object,i==2?runtime_scene::kColliderVtables[2]:runtime_scene::kBoxVtable);m.put(object+8,int32_t(i+10));m.put(object+0x4c,uint8_t(0));m.put(object+0x4d,uint8_t(i==1?0:1));}
 auto s=runtime_scene::capture(m,base);assert(s.readable&&s.slots==8&&s.objects==3&&s.colliders.size()==3);assert(s.colliders[0].box&&s.colliders[0].enabled&&!s.colliders[0].trigger);assert(!s.colliders[1].enabled);assert(!s.colliders[2].box);
 m.put(registry+8,uint32_t(57));assert(!runtime_scene::capture(m,base).readable);
 m.put(registry+8,uint32_t(56));m.put(uintptr_t(0x3008),int32_t(999));assert(runtime_scene::capture(m,base).colliders.size()==2);
}
