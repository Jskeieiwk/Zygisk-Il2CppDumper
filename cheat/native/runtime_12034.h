#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
namespace oxide12034 {
// Only for Build ID 76e47a1addbd7aee36595c8dc2bb2f7eac1ffc5e.
// Recovered native IL2CPP API wrappers; names in dynsym are obfuscated.
// No guessed assembly layouts or synthetic method lookup are used.
struct RuntimeEntry { const char* name; uintptr_t rva; uint32_t words[4]; };
inline constexpr RuntimeEntry runtimeEntries[] = {
    {"domain_get",0x61f0324,{0x14011096,0xaa0103e0,0x1400c8af,0xa9bf4ffe}},
    {"thread_attach",0x61f0780,{0x140120d8,0x140120ff,0x1401244a,0x14015d7a}},
    {"thread_detach",0x61f0784,{0x140120ff,0x1401244a,0x14015d7a,0x14015dc8}},
    {"domain_get_assemblies",0x61f0330,{0xa9bf4ffe,0xaa0103f3,0x9400c84c,0xa9402000}},
    {"assembly_get_image",0x61efe28,{0x1400c9aa,0x140163cc,0x1401638d,0x9104d408}},
    {"image_get_name",0x61f0aec,{0x1400c679,0x14010ea3,0x14010ea2,0xd10083ff}},
    {"class_from_name",0x61efe60,{0x14016ca1,0x140163bc,0x140163c2,0x140163f5}},
    {"class_get_method_from_name",0x61efe88,{0x140164be,0x1400d38f,0x1400d38c,0x1401653f}},
    {"class_get_methods",0x61efe84,{0x1401648b,0x140164be,0x1400d38f,0x1400d38c}},
    {"method_get_name",0x61f0668,{0x1400d196,0x14011d99,0x14011d9b,0x14011dc1}},
    {"method_get_param_count",0x61f0678,{0x14011dc4,0x14011dc5,0x14011d44,0x14011de2}},
    {"method_get_param",0x61f067c,{0x14011dc5,0x14011d44,0x14011de2,0x14011d42}},
    {"type_get_type",0x61f07d8,{0x1401439a,0x14014714,0xd10103ff,0xf90013fe}},
    {"class_get_type",0x61eff08,{0x91008000,0xd65f03c0,0xb9411c00,0xd65f03c0}},
    {"type_get_object",0x61f07d4,{0x1400d0ab,0x1401439a,0x14014714,0xd10103ff}},
    {"runtime_invoke",0x61f0748,{0x140159a6,0x140152bf,0x14015b3d,0x14015b3e}},
    {"object_unbox",0x61f0720,{0x1400cb11,0x1400c9cc,0x14011eb9,0x14011eba}},
    {"string_chars",0x61f0760,{0x1400b04c,0x1400bf88,0x1400bf87,0x1400bfb2}},
    {"string_length",0x61f075c,{0x1400b04f,0x1400b04c,0x1400bf88,0x1400bf87}},
    {"string_new",0x61f0764,{0x1400bf88,0x1400bf87,0x1400bfb2,0x1400bf8c}},
    {"gchandle_new",0x61f059c,{0x17ffdd90,0xd10103ff,0xa9034ffe,0x910003e8}},
    {"gchandle_get_target",0x61f05d4,{0x17ffde7d,0xd10083ff,0xa900fbe1,0xf90003e0}},
    {"gchandle_free",0x61f061c,{0x17ffdeca,0x52800200,0xd65f03c0,0x52800400}},
    {"object_get_class",0x61f06f4,{0x1400c777,0x1400ca3a,0x1400ca54,0xf81f0ffe}},
    {"class_is_assignable_from",0x61efe4c,{0x1401662d,0x140166eb,0x14016601,0x52800021}},
};
// The caller must verify the complete Build ID before reading these RVAs.
inline void* runtimeEntry(uintptr_t base, const char* name) {
    if(!base || !name)return nullptr;
    for(const auto& entry:runtimeEntries){
        if(std::strcmp(name,entry.name)!=0)continue;
        for(size_t i=0;i<4;++i)
            if(*reinterpret_cast<const volatile uint32_t*>(base+entry.rva+i*4)!=entry.words[i])return nullptr;
        return reinterpret_cast<void*>(base+entry.rva);
    }
    return nullptr;
}
}
