#include "internal_state.h"
#include "brand.h"
#include "dobby.h"
#include "runtime_12034.h"
#include "ballistics.h"
#include <unordered_map>
#include <android/log.h>
#include <dlfcn.h>
#include <elf.h>
#include <fcntl.h>
#include <link.h>
#include <pthread.h>
#include <unistd.h>
#include <algorithm>
#include <atomic>
#include <array>
#include <cmath>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {
constexpr uintptr_t kUpdate=0x7818ED8; // PlayerManager.LateUpdate, Oxide 12034 ARM64
constexpr uint32_t kUpdateWord=0xf81e0ffe;
constexpr uintptr_t kSecondCheck=0x78198A4; // PlayerManager.Update
constexpr uint32_t kSecondWord=0xd10203ff;
constexpr uintptr_t kOneShot=0xE2C5B88; // UnityEngine.AudioSource.PlayOneShot(AudioClip,float)
constexpr uint32_t kOneShotWord=0xfc1d0fe8;
struct Vec3 {float x,y,z;};
struct Vec2 {float x,y;};
struct Color {float r,g,b,a;};
struct Matrix {float v[16];};
struct Array {void* klass;void* monitor;void* bounds;uintptr_t length;void* items[1];};
using Object=void;using Method=void;using Class=void;using Image=void;using Type=void;using Domain=void;using Assembly=void;
struct Api {
    Domain*(*domain_get)();void*(*thread_attach)(Domain*);void(*thread_detach)(void*);
    const Assembly**(*domain_get_assemblies)(Domain*,size_t*);Image*(*assembly_get_image)(const Assembly*);
    const char*(*image_get_name)(Image*);Class*(*class_from_name)(Image*,const char*,const char*);
    Method*(*class_get_method_from_name)(Class*,const char*,int);Method*(*class_get_methods)(Class*,void**);
    const char*(*method_get_name)(Method*);uint32_t(*method_get_param_count)(Method*);
    const Type*(*method_get_param)(Method*,uint32_t);int(*type_get_type)(const Type*);
    const Type*(*class_get_type)(Class*);
    Object*(*type_get_object)(const Type*);Object*(*runtime_invoke)(Method*,void*,void**,Object**);
    void*(*object_unbox)(Object*);const uint16_t*(*string_chars)(Object*);int32_t(*string_length)(Object*);
    Object*(*string_new)(const char*);
    // This build uses pointer-sized GC handles (GetTarget masks a 64-bit address).
    uintptr_t(*gchandle_new)(Object*,bool);Object*(*gchandle_get_target)(uintptr_t);void(*gchandle_free)(uintptr_t);
    Class*(*object_get_class)(Object*);bool(*class_is_assignable_from)(Class*,Class*);
} api{};
struct Methods {
    Method *find=nullptr,*mainCamera=nullptr,*getWidth=nullptr,*getHeight=nullptr,*getTransform=nullptr,
      *getPosition=nullptr,*setPosition=nullptr,*getForward=nullptr,*getRight=nullptr,*getView=nullptr,*getProjection=nullptr,*lookAt=nullptr,*raycast=nullptr,
      *getLocal=nullptr,*getNickname=nullptr,*getBone=nullptr,*isHuman=nullptr,*getGameObject=nullptr,*getObjectName=nullptr,
      *getHotbar=nullptr,*getSlots=nullptr,*getSlotItem=nullptr,*selectSlot=nullptr,
      *getAmbient=nullptr,*setAmbient=nullptr,*getSkybox=nullptr,*getMaterialColor=nullptr,*setMaterialColor=nullptr,
      *hasProperty=nullptr,*getTint=nullptr,*setTint=nullptr,
      *getRenderers=nullptr,*getMaterials=nullptr,*getFloat=nullptr,*setFloat=nullptr,
      *getQueue=nullptr,*setQueue=nullptr,*enableKeyword=nullptr,*disableKeyword=nullptr,
      *attackTool=nullptr,
      *getCameraFov=nullptr,*setCameraFov=nullptr,*getWeaponFov=nullptr,*setWeaponFov=nullptr;
    Object *playerType=nullptr,*botType=nullptr,*resourceType=nullptr,*lootType=nullptr;
    Object *rendererType=nullptr,*hitMarkerType=nullptr;
    Class *toolClass=nullptr,*hitscanClass=nullptr;
    Method *getWeaponConfig=nullptr,*getBulletSpeed=nullptr,*getBallisticProfile=nullptr,
        *getProfileGravity=nullptr,*getProfileDrag=nullptr,
        *getActive=nullptr,*setActive=nullptr;
} m;
uintptr_t base=0;
std::string gameLibraryPath;
bool buildIdMatched=false;
void(*originalUpdate)(void*,void*)=nullptr;
void(*originalCrosshairUpdate)(void*,void*)=nullptr;
Vec2(*originalMove)(void*,void*)=nullptr;
void(*originalOneShot)(void*,void*,float,void*)=nullptr;
std::atomic<float> moveX{0},moveY{0};
std::atomic<float> farmX{0},farmY{0};
Vec3 freecamPosition{};bool freecamWasActive=false;uint64_t freecamLastFrame=0;
std::atomic<bool> ready{false};
void stage(const char* message) {
    // Progress file under dladdr() is unavailable when the payload is reflectively
    // mapped (no soinfo). Keep the logcat line so dj can tail progress.
    __android_log_print(ANDROID_LOG_INFO,BRAND_TAG,"%s",message);
}
uint64_t lastSample=0;
Object* fovCamera=nullptr;float originalFov=0.f;
Object* fovWeapon=nullptr;float originalWeaponFov=0.f;
struct WorldMarker {Vec3 position;float distance;unsigned kind;std::string name;};
std::vector<WorldMarker> worldMarkers;
uint64_t lastWorldSample=0;
uint64_t lastHeal=0;
Object* skyMaterial=nullptr;Color skyOriginal{},ambientOriginal{};bool skyCaptured=false,ambientCaptured=false;
Color tintOriginal{};bool tintCaptured=false;
struct ChamMaterial {uintptr_t handle=0;Color base{},legacy{};float surface=0,src=1,dst=0,zwrite=1;int queue=2000;bool weapon=false;};
std::vector<ChamMaterial> chamMaterials;
uint64_t lastChamSample=0,lastChamSweep=0;
Vec3 farmTarget{};bool haveFarmTarget=false;float farmBestDistance=INFINITY;
uint64_t farmLastProgress=0,farmLastAttack=0;bool farmDetourRight=true;
struct FarmIgnore {Vec3 position;uint64_t until;};std::vector<FarmIgnore> farmIgnore;

template<class T> T sym(void* handle,const char* name){return reinterpret_cast<T>(dlsym(handle,name));}
int locate(dl_phdr_info* info,size_t,void*) {
    if(info->dlpi_name&&strstr(info->dlpi_name,"/libil2cpp.so")){
        base=info->dlpi_addr;
        gameLibraryPath=info->dlpi_name;
        static const uint8_t expected[20]={0x76,0xe4,0x7a,0x1a,0xdd,0xbd,0x7a,0xee,0x36,0x59,
            0x5c,0x8d,0xc2,0xbb,0x2f,0x7e,0xac,0x1f,0xfc,0x5e};
        for(int i=0;i<info->dlpi_phnum;i++){
            const ElfW(Phdr)& ph=info->dlpi_phdr[i];if(ph.p_type!=PT_NOTE||ph.p_memsz>4096)continue;
            const uint8_t* data=reinterpret_cast<const uint8_t*>(base+ph.p_vaddr);
            size_t at=0;
            while(at+sizeof(ElfW(Nhdr))<=ph.p_memsz){
                const auto* note=reinterpret_cast<const ElfW(Nhdr)*>(data+at);
                size_t names=(note->n_namesz+3u)&~size_t(3),desc=(note->n_descsz+3u)&~size_t(3);
                size_t size=sizeof(ElfW(Nhdr))+names+desc;
                if(size==0||at+size>ph.p_memsz)break;
                const uint8_t* name=data+at+sizeof(ElfW(Nhdr));
                const uint8_t* id=name+names;
                if(note->n_type==NT_GNU_BUILD_ID&&note->n_namesz>=4&&memcmp(name,"GNU",4)==0&&
                    note->n_descsz==sizeof(expected)&&memcmp(id,expected,sizeof(expected))==0)buildIdMatched=true;
                at+=size;
            }
        }
        return 1;
    }
    return 0;
}
bool versionMatches() {
    if(!base||!buildIdMatched)return false;
    return *reinterpret_cast<volatile uint32_t*>(base+kUpdate)==kUpdateWord &&
           *reinterpret_cast<volatile uint32_t*>(base+kSecondCheck)==kSecondWord;
}
Object* call(Method* method,void* self,void** args=nullptr) {
    if(!method)return nullptr;
    Object* exception=nullptr;Object* value=api.runtime_invoke(method,self,args,&exception);
    return exception?nullptr:value;
}
template<class T> bool unbox(Object* object,T& out) {
    if(!object)return false;void* p=api.object_unbox(object);if(!p)return false;
    std::memcpy(&out,p,sizeof(T));return true;
}
std::string string(Object* object) {
    if(!object)return {};
    int n=api.string_length(object);const uint16_t* chars=api.string_chars(object);
    if(!chars||n<=0||n>48)return {};
    std::string result;result.reserve(n);
    for(int i=0;i<n;i++) {
        uint32_t cp=chars[i];
        if(cp>=0xd800&&cp<=0xdbff&&i+1<n&&chars[i+1]>=0xdc00&&chars[i+1]<=0xdfff)
            cp=0x10000+((cp-0xd800)<<10)+(chars[++i]-0xdc00);
        if(cp<0x80)result.push_back(char(cp));
        else if(cp<0x800){result.push_back(char(0xc0|(cp>>6)));result.push_back(char(0x80|(cp&63)));}
        else if(cp<0x10000){result.push_back(char(0xe0|(cp>>12)));result.push_back(char(0x80|((cp>>6)&63)));result.push_back(char(0x80|(cp&63)));}
        else {result.push_back(char(0xf0|(cp>>18)));result.push_back(char(0x80|((cp>>12)&63)));result.push_back(char(0x80|((cp>>6)&63)));result.push_back(char(0x80|(cp&63)));}
    }
    return result;
}
Image* image(const char* part) {
    size_t count=0;const Assembly** all=api.domain_get_assemblies(api.domain_get(),&count);
    if(!all||count>1000)return nullptr;
    for(size_t i=0;i<count;i++){Image* im=api.assembly_get_image(all[i]);const char* name=api.image_get_name(im);
        if(name&&strstr(name,part))return im;}
    return nullptr;
}
Method* method(Class* klass,const char* name,int params){return klass?api.class_get_method_from_name(klass,name,params):nullptr;}
std::string resolveFailure;
bool resolve() {
    resolveFailure.clear();
    m=Methods{};
    stage("resolving: opening IL2CPP handle");
    void* h=gameLibraryPath.empty()?nullptr:dlopen(gameLibraryPath.c_str(),RTLD_NOW|RTLD_NOLOAD);
    if(!h)h=dlopen("libil2cpp.so",RTLD_NOW|RTLD_NOLOAD);
    // Version-checked wrappers remain available when the linker namespace hides the handle.
#define BIND(n) stage("resolving export: " #n);api.n=h?sym<decltype(api.n)>(h,"il2cpp_" #n):nullptr;if(!api.n)api.n=reinterpret_cast<decltype(api.n)>(oxide12034::runtimeEntry(base,#n));if(!api.n){resolveFailure="runtime adapter missing: " #n;stage(resolveFailure.c_str());if(h)dlclose(h);return false;}
    BIND(domain_get);BIND(thread_attach);BIND(thread_detach);BIND(domain_get_assemblies);
    BIND(assembly_get_image);BIND(image_get_name);BIND(class_from_name);BIND(class_get_method_from_name);
    BIND(class_get_methods);BIND(method_get_name);BIND(method_get_param_count);BIND(method_get_param);BIND(type_get_type);
    BIND(class_get_type);BIND(type_get_object);BIND(runtime_invoke);BIND(object_unbox);
    BIND(string_chars);BIND(string_length);BIND(string_new);
    BIND(gchandle_new);BIND(gchandle_get_target);BIND(gchandle_free);
    BIND(object_get_class);BIND(class_is_assignable_from);
#undef BIND
    stage("calling il2cpp_domain_get");
    Domain* domain=api.domain_get();if(!domain){if(h)dlclose(h);return false;}
    // Called only from PlayerManager.LateUpdate on an existing managed thread.
    // Never attach/detach this engine-owned thread.
    stage("enumerating IL2CPP assemblies");
    Image* game=image("Assembly-CSharp");Image* core=image("UnityEngine.CoreModule");
    Image* physics=image("UnityEngine.PhysicsModule");Image* ui=image("UnityEngine.UI");
    Image* animation=image("UnityEngine.AnimationModule");
    stage("resolving game and Unity classes");
    m.hitscanClass=game?api.class_from_name(game,"Oxide","FPHitscan"):nullptr;
    Class* weaponConfig=game?api.class_from_name(game,"HyperHug.Games.Oxide.Features.Weapons","HitscanWeaponConfig"):nullptr;
    Class* profile=game?api.class_from_name(game,"HyperHug.Games.Oxide.Features.Weapons.Ballistics","BallisticProfile"):nullptr;
    Class* gameObject=core?api.class_from_name(core,"UnityEngine","GameObject"):nullptr;
    m.getWeaponConfig=method(m.hitscanClass,"rTl",0);
    m.getBulletSpeed=method(weaponConfig,"get_BulletSpeed",0);
    m.getBallisticProfile=method(m.hitscanClass,"rTy",0);
    m.getProfileGravity=method(profile,"zoT",0);m.getProfileDrag=method(profile,"zoJ",0);
    m.getActive=method(gameObject,"get_activeSelf",0);m.setActive=method(gameObject,"SetActive",1);
    Class* player=game?api.class_from_name(game,"Oxide","PlayerManager"):nullptr;
    Class* bot=game?api.class_from_name(game,"HyperHug.Games.Oxide.Features.NPC","NPCBrainHumanoid"):nullptr;
    Class* resource=game?api.class_from_name(game,"Oxide","MineableObject"):nullptr;
    Class* loot=game?api.class_from_name(game,"Oxide","LootObject"):nullptr;
    Class* weaponRender=game?api.class_from_name(game,"Oxide.Features.Rendering","FirstPersonRenderController"):nullptr;
    Class* controller=game?api.class_from_name(game,"Oxide","GameControllerBase"):nullptr;
    Class* inventory=game?api.class_from_name(game,"Oxide","PlayerInventory"):nullptr;
    Class* hotbar=game?api.class_from_name(game,"Oxide","Hotbar"):nullptr;
    Class* slot=game?api.class_from_name(game,"Oxide","Slot"):nullptr;
    Class* renderSettings=core?api.class_from_name(core,"UnityEngine","RenderSettings"):nullptr;
    Class* material=core?api.class_from_name(core,"UnityEngine","Material"):nullptr;
    Class* renderer=core?api.class_from_name(core,"UnityEngine","Renderer"):nullptr;
    Class* hitMarker=game?api.class_from_name(game,"HyperHug.Games.Oxide.Features.MineableExtensions","MineableObjectExtension_HitMarkerItem"):nullptr;
    Class* melee=game?api.class_from_name(game,"Oxide","FPMelee"):nullptr;
    m.toolClass=game?api.class_from_name(game,"Oxide","FPTool"):nullptr;
    Class* text=ui?api.class_from_name(ui,"UnityEngine.UI","Text"):nullptr;
    Class* animator=animation?api.class_from_name(animation,"UnityEngine","Animator"):nullptr;
    Class* camera=core?api.class_from_name(core,"UnityEngine","Camera"):nullptr;
    Class* screen=core?api.class_from_name(core,"UnityEngine","Screen"):nullptr;
    Class* component=core?api.class_from_name(core,"UnityEngine","Component"):nullptr;
    Class* transform=core?api.class_from_name(core,"UnityEngine","Transform"):nullptr;
    Class* object=core?api.class_from_name(core,"UnityEngine","Object"):nullptr;
    Class* physicsClass=physics?api.class_from_name(physics,"UnityEngine","Physics"):nullptr;
    if(player&&controller&&camera&&screen&&component&&transform&&object){
        stage("creating reflection type objects on managed callback");
        m.playerType=api.type_get_object(api.class_get_type(player));
        if(bot)m.botType=api.type_get_object(api.class_get_type(bot));
        if(resource)m.resourceType=api.type_get_object(api.class_get_type(resource));
        if(loot)m.lootType=api.type_get_object(api.class_get_type(loot));
        stage("resolving game and Unity methods");
        m.find=method(object,"FindObjectsOfType",1);m.getLocal=method(controller,"rxI",0);
        m.mainCamera=method(camera,"get_main",0);m.getWidth=method(screen,"get_width",0);
        m.getCameraFov=method(camera,"get_fieldOfView",0);
        m.setCameraFov=method(camera,"set_fieldOfView",1);
        m.getHeight=method(screen,"get_height",0);m.getTransform=method(component,"get_transform",0);
        m.getPosition=method(transform,"get_position",0);m.setPosition=method(transform,"set_position",1);
        m.getForward=method(transform,"get_forward",0);m.getRight=method(transform,"get_right",0);
        m.getView=method(camera,"get_worldToCameraMatrix",0);
        m.getProjection=method(camera,"get_projectionMatrix",0);
        // LookAt(Transform, Vector3) appears first in metadata. Both arguments
        // here are Vector3 values, so require the value-type overload explicitly.
        void* lookSearch=nullptr;Method* lookCandidate=nullptr;
        while(transform&&(lookCandidate=api.class_get_methods(transform,&lookSearch))){
            if(std::strcmp(api.method_get_name(lookCandidate),"LookAt")!=0||
               api.method_get_param_count(lookCandidate)!=2)continue;
            if(api.type_get_type(api.method_get_param(lookCandidate,0))==0x11&&
               api.type_get_type(api.method_get_param(lookCandidate,1))==0x11){m.lookAt=lookCandidate;break;}
        }
        m.getNickname=method(text,"get_text",0);
        m.getGameObject=method(component,"get_gameObject",0);
        m.getObjectName=method(object,"get_name",0);
        m.getHotbar=method(inventory,"rus",0);m.getSlots=method(hotbar,"Yim",0);
        m.getSlotItem=method(slot,"Yum",0);m.selectSlot=method(hotbar,"Yit",2);
        m.getAmbient=method(renderSettings,"get_ambientSkyColor",0);
        m.setAmbient=method(renderSettings,"set_ambientSkyColor",1);
        m.getSkybox=method(renderSettings,"get_skybox",0);
        m.rendererType=renderer?api.type_get_object(api.class_get_type(renderer)):nullptr;
        m.hitMarkerType=hitMarker?api.type_get_object(api.class_get_type(hitMarker)):nullptr;
        m.attackTool=method(melee,"rfW",0);
        m.getMaterials=method(renderer,"get_materials",0);
        m.getQueue=method(material,"get_renderQueue",0);m.setQueue=method(material,"set_renderQueue",1);
        m.enableKeyword=method(material,"EnableKeyword",1);m.disableKeyword=method(material,"DisableKeyword",1);
        void* childrenSearch=nullptr;Method* childCandidate=nullptr;
        while(component&&(childCandidate=api.class_get_methods(component,&childrenSearch))){
            if(strcmp(api.method_get_name(childCandidate),"GetComponentsInChildren")!=0||
                api.method_get_param_count(childCandidate)!=2)continue;
            if(api.type_get_type(api.method_get_param(childCandidate,0))==0x12&&
               api.type_get_type(api.method_get_param(childCandidate,1))==0x02){m.getRenderers=childCandidate;break;}
        }
        m.getMaterialColor=method(material,"get_color",0);
        m.setMaterialColor=method(material,"set_color",1);
        void* search=nullptr;Method* colorCandidate=nullptr;
        while(material&&(colorCandidate=api.class_get_methods(material,&search))){
            const char* name=api.method_get_name(colorCandidate);uint32_t count=api.method_get_param_count(colorCandidate);
            if(count<1||api.type_get_type(api.method_get_param(colorCandidate,0))!=0x0e)continue;
            if(strcmp(name,"HasProperty")==0&&count==1)m.hasProperty=colorCandidate;
            if(strcmp(name,"GetColor")==0&&count==1)m.getTint=colorCandidate;
            if(strcmp(name,"SetColor")==0&&count==2)m.setTint=colorCandidate;
            if(strcmp(name,"GetFloat")==0&&count==1)m.getFloat=colorCandidate;
            if(strcmp(name,"SetFloat")==0&&count==2)m.setFloat=colorCandidate;
        }
        m.getWeaponFov=method(weaponRender,"WKb",0);m.setWeaponFov=method(weaponRender,"WKI",1);
        m.getBone=method(animator,"GetBoneTransform",1);m.isHuman=method(animator,"get_isHuman",0);
        void* iterator=nullptr;Method* candidate=nullptr;
        while(physicsClass&&(candidate=api.class_get_methods(physicsClass,&iterator)))
            if(strcmp(api.method_get_name(candidate),"Raycast")==0&&api.method_get_param_count(candidate)==5&&
               api.type_get_type(api.method_get_param(candidate,2))==0x0c){m.raycast=candidate;break;}
    }
    if(h)dlclose(h);
    return m.playerType&&m.find&&m.getLocal&&m.mainCamera&&m.getWidth&&m.getHeight&&m.getTransform&&
           m.getPosition&&m.getView&&m.getProjection;
}
Vec2 replacementMove(void* self,void* info){
    Vec2 input=originalMove?originalMove(self,info):Vec2{};
    if(internal::state.isAutoFarm())return {farmX.load(std::memory_order_relaxed),farmY.load(std::memory_order_relaxed)};
    if(!internal::state.isFreecam())return input;
    moveX.store(input.x,std::memory_order_relaxed);moveY.store(input.y,std::memory_order_relaxed);
    return {};
}
void replacementOneShot(void* self,void* clip,float volume,void* info){
    if(ready.load(std::memory_order_acquire)&&clip&&m.getObjectName&&
       string(call(m.getObjectName,clip))=="Headshot"&&internal::state.onHeadshot())return;
    if(originalOneShot)originalOneShot(self,clip,volume,info);
}
void updateFreecam(){
    if(!m.setPosition||!m.getRight){internal::state.freecamAvailableSet(false);return;}
    bool active=internal::state.isFreecam();
    if(!active){freecamWasActive=false;freecamLastFrame=0;moveX=0;moveY=0;return;}
    Object* camera=call(m.mainCamera,nullptr);Object* transform=camera?call(m.getTransform,camera):nullptr;
    if(!transform)return;
    if(!freecamWasActive){if(!unbox(call(m.getPosition,transform),freecamPosition))return;freecamWasActive=true;}
    uint64_t now=internal::nowMs();float dt=freecamLastFrame?std::clamp((now-freecamLastFrame)/1000.f,0.f,.05f):0.f;
    freecamLastFrame=now;
    Vec3 forward{},right{};
    if(!unbox(call(m.getForward,transform),forward)||!unbox(call(m.getRight,transform),right))return;
    auto options=internal::state.freecamInput();
    float x=std::clamp(moveX.load(std::memory_order_relaxed),-1.f,1.f),
          y=std::clamp(moveY.load(std::memory_order_relaxed),-1.f,1.f);
    float speed=std::clamp(static_cast<float>(options.speed),2.f,50.f);
    freecamPosition.x+=(right.x*x+forward.x*y)*speed*dt;
    freecamPosition.y+=(right.y*x+forward.y*y)*speed*dt;
    freecamPosition.z+=(right.z*x+forward.z*y)*speed*dt;
    void* args[]={&freecamPosition};call(m.setPosition,transform,args);
}
Vec3 project(Vec3 world,const Matrix& view,const Matrix& projection,int w,int h) {
    const float in[4]={world.x,world.y,world.z,1.f};float eye[4]={},clip[4]={};
    for(int row=0;row<4;row++)for(int col=0;col<4;col++)eye[row]+=view.v[col*4+row]*in[col];
    for(int row=0;row<4;row++)for(int col=0;col<4;col++)clip[row]+=projection.v[col*4+row]*eye[col];
    if(!std::isfinite(clip[3])||std::abs(clip[3])<0.001f)return {0,0,-1};
    return {(clip[0]/std::abs(clip[3])+1.f)*w*.5f,(clip[1]/std::abs(clip[3])+1.f)*h*.5f,clip[3]};
}
void addWorldMarker(Object* object,Vec3 cameraPos,unsigned kind,const std::string& name,int range){
    Object* tr=call(m.getTransform,object);Vec3 pos{};
    if(!tr||!unbox(call(m.getPosition,tr),pos))return;
    float distance=std::sqrt((pos.x-cameraPos.x)*(pos.x-cameraPos.x)+
                             (pos.y-cameraPos.y)*(pos.y-cameraPos.y)+(pos.z-cameraPos.z)*(pos.z-cameraPos.z));
    if(!std::isfinite(distance)||distance<1.f||distance>range)return;
    WorldMarker marker{pos,distance,kind,name};
    if(worldMarkers.size()<384){worldMarkers.push_back(std::move(marker));return;}
    auto furthest=std::max_element(worldMarkers.begin(),worldMarkers.end(),
        [](const WorldMarker& a,const WorldMarker& b){return a.distance<b.distance;});
    if(distance<furthest->distance)*furthest=std::move(marker);
}
void sampleWorld(Vec3 cameraPos,const internal::Config& settings,uint64_t now){
    if(now-lastWorldSample<1200)return;lastWorldSample=now;worldMarkers.clear();
    if((settings.oreEsp||settings.animalEsp||settings.autoFarmFeature)&&m.resourceType){
        void* args[]={m.resourceType};Array* objects=reinterpret_cast<Array*>(call(m.find,nullptr,args));
        if(objects&&objects->length<=15000)for(uintptr_t i=0;i<objects->length;i++){
            Object* object=objects->items[i];if(!object)continue;
            int type=*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(object)+0xd8);
            unsigned kind=0;const char* label=nullptr;
            switch(type){
                case 1: label="Медведь";kind=5;break;case 2:label="Кабан";kind=5;break;
                case 3:label="Олень";kind=5;break;case 4:label="Кролик";kind=5;break;
                case 5:label="Курица";kind=5;break;case 6:label="Рыба";kind=5;break;
                case 8:label="Дерево";kind=4;break;case 9:label="Камень";kind=1;break;
                case 10:label="Железо";kind=3;break;case 11:label="Сера";kind=2;break;
                case 22:label="Заяц";kind=5;break;case 25:label="Крыса";kind=5;break;
                case 26:label="Волк";kind=5;break;case 27:label="Акула";kind=5;break;
                default:break;
            }
            if(!kind||(kind==5&&!settings.animalEsp)||(kind!=5&&!settings.oreEsp&&!settings.autoFarmFeature))continue;
            addWorldMarker(object,cameraPos,kind,label,settings.espDistance);
        }
    }
    if(settings.objectEsp&&m.lootType){
        void* args[]={m.lootType};Array* objects=reinterpret_cast<Array*>(call(m.find,nullptr,args));
        if(objects&&objects->length<=10000)for(uintptr_t i=0;i<objects->length;i++){
            Object* object=objects->items[i];if(!object)continue;
            std::string prefab;
            if(m.getGameObject&&m.getObjectName){Object* gameObject=call(m.getGameObject,object);
                if(gameObject)prefab=string(call(m.getObjectName,gameObject));}
            std::string panel=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(object)+0xe0));
            std::string test=prefab+" "+panel;
            std::transform(test.begin(),test.end(),test.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
            unsigned kind=6;int bit=1;const char* label="Ящик";
            if(test.find("elite")!=std::string::npos){kind=8;bit=4;label="Элитный ящик";}
            else if(test.find("military")!=std::string::npos||test.find("army")!=std::string::npos){kind=7;bit=2;label="Военный ящик";}
            else if(test.find("red")!=std::string::npos){kind=9;bit=8;label="Красный ящик";}
            if((settings.crateMask&bit)==0)continue;
            addWorldMarker(object,cameraPos,kind,label,settings.espDistance);
        }
    }
    std::sort(worldMarkers.begin(),worldMarkers.end(),
        [](const WorldMarker& a,const WorldMarker& b){return a.distance<b.distance;});
}
void applySky(const internal::Config& settings){
    if(!m.getAmbient||!m.setAmbient)return;
    if(!settings.customSky){
        if(ambientCaptured){void* args[]={&ambientOriginal};call(m.setAmbient,nullptr,args);ambientCaptured=false;}
        if(skyCaptured&&skyMaterial&&m.getSkybox&&call(m.getSkybox,nullptr)==skyMaterial){
            if(m.setMaterialColor){void* args[]={&skyOriginal};call(m.setMaterialColor,skyMaterial,args);}
            if(tintCaptured&&m.setTint){Object* prop=api.string_new("_Tint");void* args[]={prop,&tintOriginal};call(m.setTint,skyMaterial,args);}
        }
        skyCaptured=tintCaptured=false;skyMaterial=nullptr;return;
    }
    Color color{settings.skyR/255.f,settings.skyG/255.f,settings.skyB/255.f,1.f};
    if(!ambientCaptured){ambientCaptured=unbox(call(m.getAmbient,nullptr),ambientOriginal);}
    void* ambientArg[]={&color};call(m.setAmbient,nullptr,ambientArg);
    Object* material=m.getSkybox?call(m.getSkybox,nullptr):nullptr;
    if(!material)return;
    if(material!=skyMaterial){skyMaterial=material;skyCaptured=m.getMaterialColor&&unbox(call(m.getMaterialColor,material),skyOriginal);
        tintCaptured=false;
        if(m.hasProperty&&m.getTint&&m.setTint){Object* prop=api.string_new("_Tint");void* args[]={prop};bool has=false;
            if(unbox(call(m.hasProperty,material,args),has)&&has)tintCaptured=unbox(call(m.getTint,material,args),tintOriginal);}}
    if(skyCaptured&&m.setMaterialColor){void* args[]={&color};call(m.setMaterialColor,material,args);}
    if(tintCaptured&&m.setTint){Object* prop=api.string_new("_Tint");void* args[]={prop,&color};call(m.setTint,material,args);}
}
bool materialColor(Object* material,const char* key,Color& value){
    if(!m.getTint||!m.hasProperty)return false;
    Object* name=api.string_new(key);void* args[]={name};bool has=false;
    return unbox(call(m.hasProperty,material,args),has)&&has&&unbox(call(m.getTint,material,args),value);
}
void setMaterialColor(Object* material,const char* key,Color value){
    if(!m.setTint)return;Object* name=api.string_new(key);void* args[]={name,&value};call(m.setTint,material,args);
}
float materialFloat(Object* material,const char* key,float fallback){
    if(!m.getFloat)return fallback;Object* name=api.string_new(key);void* args[]={name};float value=fallback;
    unbox(call(m.getFloat,material,args),value);return value;
}
void setMaterialFloat(Object* material,const char* key,float value){
    if(!m.setFloat)return;Object* name=api.string_new(key);void* args[]={name,&value};call(m.setFloat,material,args);
}
void materialKeyword(Object* material,bool on){
    Method* selected=on?m.enableKeyword:m.disableKeyword;if(!selected)return;
    Object* key=api.string_new("_SURFACE_TYPE_TRANSPARENT");void* args[]={key};call(selected,material,args);
}
void restoreCham(ChamMaterial& entry){
    Object* material=api.gchandle_get_target(entry.handle);
    if(material){setMaterialColor(material,"_BaseColor",entry.base);
        setMaterialColor(material,"_Color",entry.legacy);
        if(entry.weapon){setMaterialFloat(material,"_Surface",entry.surface);
            setMaterialFloat(material,"_SrcBlend",entry.src);setMaterialFloat(material,"_DstBlend",entry.dst);
            setMaterialFloat(material,"_ZWrite",entry.zwrite);
            if(m.setQueue){void* args[]={&entry.queue};call(m.setQueue,material,args);}
            materialKeyword(material,entry.surface>0.5f);}}
    api.gchandle_free(entry.handle);
}
void clearChams(){for(auto& entry:chamMaterials)restoreCham(entry);chamMaterials.clear();}
void applyCham(Object* material,bool weapon,const internal::Config& settings){
    if(!material||!m.getTint||!m.setTint||!m.hasProperty)return;
    auto found=std::find_if(chamMaterials.begin(),chamMaterials.end(),[&](const ChamMaterial& e){
        return api.gchandle_get_target(e.handle)==material;});
    if(found==chamMaterials.end()){
        if(chamMaterials.size()>=192)return;
        ChamMaterial next;next.weapon=weapon;
        if(!materialColor(material,"_BaseColor",next.base))return;
        if(!materialColor(material,"_Color",next.legacy))next.legacy=next.base;
        if(weapon){next.surface=materialFloat(material,"_Surface",0.f);
            next.src=materialFloat(material,"_SrcBlend",1.f);next.dst=materialFloat(material,"_DstBlend",0.f);
            next.zwrite=materialFloat(material,"_ZWrite",1.f);
            if(m.getQueue)unbox(call(m.getQueue,material),next.queue);}
        next.handle=api.gchandle_new(material,false);if(!next.handle)return;
        chamMaterials.push_back(next);found=chamMaterials.end()-1;
    }
    Color color=weapon?Color{settings.weaponR/255.f,settings.weaponG/255.f,settings.weaponB/255.f,settings.weaponAlpha/100.f}:
        Color{settings.chamR/255.f,settings.chamG/255.f,settings.chamB/255.f,1.f};
    setMaterialColor(material,"_BaseColor",color);setMaterialColor(material,"_Color",color);
    if(weapon){setMaterialFloat(material,"_Surface",1.f);setMaterialFloat(material,"_SrcBlend",5.f);
        setMaterialFloat(material,"_DstBlend",10.f);setMaterialFloat(material,"_ZWrite",0.f);
        int queue=3000;if(m.setQueue){void* args[]={&queue};call(m.setQueue,material,args);}
        materialKeyword(material,true);}
}
void addChams(Object* component,bool weapon,const internal::Config& settings){
    if(!component||!m.getRenderers||!m.rendererType||!m.getMaterials)return;
    bool includeInactive=false;void* args[]={m.rendererType,&includeInactive};
    Array* renderers=reinterpret_cast<Array*>(call(m.getRenderers,component,args));
    if(!renderers||renderers->length>40)return;
    for(uintptr_t i=0;i<renderers->length;i++){
        Object* renderer=renderers->items[i];
        Array* materials=renderer?reinterpret_cast<Array*>(call(m.getMaterials,renderer)):nullptr;
        if(!materials||materials->length>12)continue;
        for(uintptr_t j=0;j<materials->length;j++)applyCham(materials->items[j],weapon,settings);
    }
}
void updateChams(const internal::Config& settings,uint64_t now){
    for(auto it=chamMaterials.begin();it!=chamMaterials.end();){
        if((it->weapon&&!settings.weaponChams)||(!it->weapon&&!settings.playerChams)){
            restoreCham(*it);it=chamMaterials.erase(it);
        }else ++it;
    }
    if(now-lastChamSweep>12000){clearChams();lastChamSweep=now;}
}
void autoHeal(Object* local,const internal::Config& settings,uint64_t now){
    if(!settings.autoHeal||now-lastHeal<2200||!m.getHotbar||!m.getSlots||!m.getSlotItem||!m.selectSlot)return;
    Object* vitals=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(local)+0x108);
    Object* entity=vitals?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(vitals)+0x68):nullptr;
    Object* health=entity?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(entity)+0x98):nullptr;
    if(!health)return;
    float max=*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(vitals)+0x88);
    float current=*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(health)+0x20);
    if(!std::isfinite(current)||!std::isfinite(max)||max<=0||current<=0||current>max||
       current*100.f/max>=settings.healThreshold)return;
    Object* inventory=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(local)+0xd8);
    Object* hotbar=inventory?call(m.getHotbar,inventory):nullptr;
    Object* list=hotbar?call(m.getSlots,hotbar):nullptr;
    if(!list)return;
    int count=*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(list)+0x18);
    Array* slots=*reinterpret_cast<Array**>(reinterpret_cast<uint8_t*>(list)+0x10);
    if(!slots||count<1||count>12||slots->length<static_cast<uintptr_t>(count))return;
    for(int i=0;i<count;i++){
        Object* slot=slots->items[i];Object* item=slot?call(m.getSlotItem,slot):nullptr;
        Object* data=item?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(item)+0x20):nullptr;
        if(!data)continue;
        std::string name=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(data)+0x20));
        if(name.empty())name=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(data)+0x18));
        std::transform(name.begin(),name.end(),name.begin(),[](unsigned char c){return static_cast<char>(std::tolower(c));});
        if(name.find("bandage")==std::string::npos&&name.find("medkit")==std::string::npos&&
           name.find("first aid")==std::string::npos&&name.find("medical") == std::string::npos)continue;
        bool force=false;void* args[]={&i,&force};call(m.selectSlot,hotbar,args);
        force=true;call(m.selectSlot,hotbar,args);lastHeal=now;break;
    }
}
float horizontalDistance(Vec3 a,Vec3 b){return std::hypot(a.x-b.x,a.z-b.z);}
void farmTick(Object* local,Object* cameraTransform,const internal::Config& settings,uint64_t now){
    if(!internal::state.isAutoFarm()){
        farmX.store(0,std::memory_order_relaxed);farmY.store(0,std::memory_order_relaxed);
        haveFarmTarget=false;return;
    }
    Object* playerTransform=call(m.getTransform,local);Vec3 playerPos{};
    if(!playerTransform||!unbox(call(m.getPosition,playerTransform),playerPos))return;
    farmIgnore.erase(std::remove_if(farmIgnore.begin(),farmIgnore.end(),[&](const FarmIgnore& x){return x.until<now;}),farmIgnore.end());
    auto present=[&](Vec3 point){return std::any_of(worldMarkers.begin(),worldMarkers.end(),[&](const WorldMarker& x){
        return x.kind==static_cast<unsigned>(settings.farmKind)&&horizontalDistance(x.position,point)<2.f;});};
    if(haveFarmTarget&&!present(farmTarget))haveFarmTarget=false;
    if(!haveFarmTarget){
        float best=INFINITY;
        for(const auto& marker:worldMarkers){
            if(marker.kind!=static_cast<unsigned>(settings.farmKind))continue;
            if(std::any_of(farmIgnore.begin(),farmIgnore.end(),[&](const FarmIgnore& x){
                return horizontalDistance(x.position,marker.position)<3.f;}))continue;
            float distance=horizontalDistance(playerPos,marker.position);
            if(distance<best){best=distance;farmTarget=marker.position;haveFarmTarget=true;}
        }
        farmBestDistance=best;farmLastProgress=now;
    }
    if(!haveFarmTarget){farmX=0;farmY=0;return;}
    float distance=horizontalDistance(playerPos,farmTarget);
    if(distance<farmBestDistance-.25f){farmBestDistance=distance;farmLastProgress=now;}
    if(distance>2.4f&&now-farmLastProgress>10000){
        farmIgnore.push_back({farmTarget,now+30000});haveFarmTarget=false;farmDetourRight=!farmDetourRight;
        farmX=0;farmY=0;return;
    }
    if(distance>2.4f){
        Vec3 direction{(farmTarget.x-playerPos.x)/distance,0,(farmTarget.z-playerPos.z)/distance};
        bool blocked=false;
        if(m.raycast&&distance>3.8f){Vec3 origin=playerPos;origin.y+=1.f;
            float range=std::min(distance-2.f,2.f);int mask=-1,triggers=1;
            void* args[]={&origin,&direction,&range,&mask,&triggers};unbox(call(m.raycast,nullptr,args),blocked);}
        if(blocked){float x=direction.x;direction.x=farmDetourRight?direction.z:-direction.z;
            direction.z=farmDetourRight?-x:x;}
        Vec3 forward{},right{};
        if(!unbox(call(m.getForward,cameraTransform),forward)||!unbox(call(m.getRight,cameraTransform),right))return;
        float fl=std::hypot(forward.x,forward.z),rl=std::hypot(right.x,right.z);
        if(fl<.1f||rl<.1f)return;
        farmX.store(std::clamp((direction.x*right.x+direction.z*right.z)/rl,-1.f,1.f),std::memory_order_relaxed);
        farmY.store(std::clamp((direction.x*forward.x+direction.z*forward.z)/fl,-1.f,1.f),std::memory_order_relaxed);
        return;
    }
    farmX=0;farmY=0;
    Vec3 point=farmTarget;point.y+=1.f;float best=3.f;
    if(m.hitMarkerType){void* search[]={m.hitMarkerType};Array* markers=reinterpret_cast<Array*>(call(m.find,nullptr,search));
        if(markers&&markers->length<=128)for(uintptr_t i=0;i<markers->length;i++){
            Object* marker=markers->items[i];if(!marker)continue;
            Object* tr=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(marker)+0x38);
            if(!tr)tr=call(m.getTransform,marker);Vec3 pos{};
            if(!tr||!unbox(call(m.getPosition,tr),pos))continue;
            float d=std::sqrt((pos.x-farmTarget.x)*(pos.x-farmTarget.x)+
                (pos.y-farmTarget.y)*(pos.y-farmTarget.y)+(pos.z-farmTarget.z)*(pos.z-farmTarget.z));
            if(d<best){best=d;point=pos;}
        }}
    Vec3 up{0,1,0};void* lookArgs[]={&point,&up};call(m.lookAt,cameraTransform,lookArgs);
    if(now-farmLastAttack<800||!m.attackTool||!m.toolClass)return;
    Object* fp=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(local)+0xd0);
    Object* held=fp?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(fp)+0x50):nullptr;
    if(!held||!api.class_is_assignable_from(m.toolClass,api.object_get_class(held)))return;
    call(m.attackTool,held);farmLastAttack=now;
}
struct MotionSample {Vec3 position{},velocity{};uint64_t at=0;bool valid=false;std::string id;};
std::unordered_map<void*,MotionSample> targetMotion;
Vec3 trackMotion(Object* target,Vec3 position,uint64_t now,bool& valid){
    std::string id=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(target)+0x2e8));
    auto& sample=targetMotion[target];valid=false;
    if(sample.at&&sample.id==id&&now>sample.at){
        float dt=(now-sample.at)/1000.f;
        Vec3 delta{position.x-sample.position.x,position.y-sample.position.y,position.z-sample.position.z};
        float displacement=std::sqrt(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z);
        if(dt>=.02f&&dt<=.5f&&std::isfinite(displacement)&&displacement<=std::max(3.f,dt*150.f)){
            sample.velocity={delta.x/dt,delta.y/dt,delta.z/dt};valid=true;
        }
    }
    sample.position=position;sample.at=now;sample.id=id;sample.valid=valid;
    return sample.velocity;
}
struct BulletModel {float speed=0,drag=0;Vec3 gravity{};bool valid=false;};
BulletModel weaponBallistics(Object* held){
    BulletModel model;
    if(!held||!m.hitscanClass||!m.getWeaponConfig||!m.getBulletSpeed||!m.getBallisticProfile||
        !m.getProfileGravity||!m.getProfileDrag||
        !api.class_is_assignable_from(m.hitscanClass,api.object_get_class(held)))return model;
    Object* config=call(m.getWeaponConfig,held);Object* profile=call(m.getBallisticProfile,held);
    float scale=0;
    if(!config||!profile||!unbox(call(m.getBulletSpeed,config),model.speed)||
       !unbox(call(m.getProfileGravity,profile),scale)||!unbox(call(m.getProfileDrag,profile),model.drag))return model;
    // Integrator multiplies Vector3.down by profile.Gravity; it is not a Physics.gravity scale.
    model.gravity={0,-scale,0};
    model.valid=std::isfinite(scale)&&ballistic::finite({model.gravity.x,model.gravity.y,model.gravity.z})&&
        model.speed>=1&&model.speed<=10000&&std::isfinite(model.drag)&&model.drag>=0&&model.drag<=100;
    return model;
}
struct HiddenCrosshair {uintptr_t handle;bool active;};
std::vector<HiddenCrosshair> hiddenCrosshairs;
void restoreCrosshairs(){
    for(auto& entry:hiddenCrosshairs){
        Object* object=api.gchandle_get_target(entry.handle);
        if(object){void* args[]={&entry.active};call(m.setActive,object,args);}
        api.gchandle_free(entry.handle);
    }
    hiddenCrosshairs.clear();
}
void hideCrosshairComponent(Object* component){
    if(!component)return;
    Object* object=call(m.getGameObject,component);if(!object)return;
    auto found=std::find_if(hiddenCrosshairs.begin(),hiddenCrosshairs.end(),[&](const HiddenCrosshair& e){return api.gchandle_get_target(e.handle)==object;});
    if(found==hiddenCrosshairs.end()){
        if(hiddenCrosshairs.size()>=64)return;
        bool active=false;if(!unbox(call(m.getActive,object),active))return;
        uintptr_t handle=api.gchandle_new(object,false);if(!handle)return;
        hiddenCrosshairs.push_back({handle,active});
    }
    bool off=false;void* args[]={&off};call(m.setActive,object,args);
}
void hideCrosshairData(Object* data){
    if(!data)return;
    hideCrosshairComponent(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(data)+0x40));
    hideCrosshairComponent(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(data)+0x58));
}
void crosshairUpdate(void* self,void* info){
    if(originalCrosshairUpdate)originalCrosshairUpdate(self,info);
    if(!ready.load(std::memory_order_acquire)||!self)return;
    if(!internal::state.read().customCrosshair){restoreCrosshairs();return;}
    hideCrosshairData(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(self)+0x48));
    hideCrosshairData(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(self)+0x80));
    Array* all=*reinterpret_cast<Array**>(reinterpret_cast<uint8_t*>(self)+0x50);
    if(all&&all->length<=64)for(uintptr_t i=0;i<all->length;i++)hideCrosshairData(all->items[i]);
}
void tick() {
    uint64_t now=internal::nowMs();auto settings=internal::state.read();
    uint64_t interval=settings.aim?50:settings.esp?180:500;
    if(now-lastSample<interval)return;lastSample=now;
    // Optional feature dependencies must not block the independent ESP pipeline.
    settings.aim=settings.aim&&m.getForward&&m.lookAt&&(!settings.visible||m.raycast);
    for(auto it=targetMotion.begin();it!=targetMotion.end();){if(now-it->second.at>2000)it=targetMotion.erase(it);else ++it;}
    auto visual=internal::state.readVisual();
    applySky(settings);
    bool scanChams=now-lastChamSample>=500;
    if(scanChams){lastChamSample=now;updateChams(settings,now);}
    Object* local=call(m.getLocal,nullptr);if(!local)return;
    autoHeal(local,settings,now);
    std::string localTeam=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(local)+0x2f0));
    Object* fpManager=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(local)+0xd0);
    Object* heldWeapon=fpManager?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(fpManager)+0x50):nullptr;
    BulletModel bullet=settings.aim?weaponBallistics(heldWeapon):BulletModel{};
    if(settings.aim&&!bullet.valid){
        static uint64_t lastModelWarning=0;
        if(now-lastModelWarning>5000){lastModelWarning=now;__android_log_print(ANDROID_LOG_WARN,BRAND_TAG,"bm");}
    }
    if(scanChams&&settings.weaponChams&&heldWeapon)addChams(heldWeapon,true,settings);
    Object* weaponRender=fpManager?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(fpManager)+0x28):nullptr;
    if(weaponRender&&m.getWeaponFov&&m.setWeaponFov){
        if(settings.weaponFov>0){
            if(weaponRender!=fovWeapon){fovWeapon=weaponRender;unbox(call(m.getWeaponFov,weaponRender),originalWeaponFov);}
            float value=static_cast<float>(settings.weaponFov);void* args[]={&value};call(m.setWeaponFov,weaponRender,args);
        }else if(weaponRender==fovWeapon&&originalWeaponFov>0.f){
            void* args[]={&originalWeaponFov};call(m.setWeaponFov,weaponRender,args);fovWeapon=nullptr;
        }
    }
    Object* camera=call(m.mainCamera,nullptr);if(!camera)return;
    if(settings.cameraFov>0&&m.getCameraFov&&m.setCameraFov){
        if(camera!=fovCamera){fovCamera=camera;unbox(call(m.getCameraFov,camera),originalFov);}
        float value=static_cast<float>(settings.cameraFov);void* args[]={&value};call(m.setCameraFov,camera,args);
    }else if(fovCamera==camera&&m.setCameraFov&&originalFov>0.f){
        void* args[]={&originalFov};call(m.setCameraFov,camera,args);fovCamera=nullptr;
    }
    Object* cameraTransform=call(m.getTransform,camera);if(!cameraTransform)return;
    Vec3 cameraPos{};if(!unbox(call(m.getPosition,cameraTransform),cameraPos))return;
    if(settings.autoFarmFeature)sampleWorld(cameraPos,settings,now);
    farmTick(local,cameraTransform,settings,now);
    int width=0,height=0;
    if(!unbox(call(m.getWidth,nullptr),width)||!unbox(call(m.getHeight,nullptr),height)||width<64||height<64)return;
    Matrix view{},projection{};
    if(!unbox(call(m.getView,camera),view)||!unbox(call(m.getProjection,camera),projection))return;
    void* search[]={m.playerType};Array* list=reinterpret_cast<Array*>(call(m.find,nullptr,search));
    if(!list||list->length>512)return;
    internal::Hud hud;hud.sampled=now;hud.players=0;hud.bots=m.botType?0:-1;
    internal::Frame frame;frame.width=width;frame.height=height;frame.sampled=now;
    float best=INFINITY;Vec3 bestPoint{};bool haveBest=false;
    for(uintptr_t i=0;i<list->length;i++) {
        Object* player=list->items[i];if(!player||player==local)continue;
        if(scanChams&&settings.playerChams)addChams(player,false,settings);
        int flags=*reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(player)+0x2c0);
        bool sleeping=(flags&1)!=0;
        if(!sleeping)++hud.players;
        if(sleeping&&!settings.espSleepers)continue;
        if(settings.ignoreTeams&&!localTeam.empty()){
            std::string team=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0x2f0));
            if(team==localTeam)continue;
        }
        if(!settings.playerEsp&&!settings.aim)continue;
        Object* tr=call(m.getTransform,player);if(!tr)continue;
        Vec3 feet{};if(!unbox(call(m.getPosition,tr),feet))continue;
        float dx=feet.x-cameraPos.x,dy=feet.y-cameraPos.y,dz=feet.z-cameraPos.z;
        float distance=std::sqrt(dx*dx+dy*dy+dz*dz);
        if(!std::isfinite(distance)||distance<1.f||distance>std::max(settings.espDistance,settings.maxDistance))continue;
        Vec3 head=feet;head.y+=1.65f;
        std::array<internal::Point,10> bones{};
        if(settings.playerEsp&&visual.skeleton&&distance<350.f&&m.getBone&&m.isHuman){
            Object* animator=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0x1f0);
            bool humanoid=false;
            if(animator&&unbox(call(m.isHuman,animator),humanoid)&&humanoid){
                const int ids[10]={10,8,0,13,15,17,14,16,18,5};
                for(int b=0;b<10;b++){
                    int id=ids[b];void* args[]={&id};Object* bone=call(m.getBone,animator,args);
                    Vec3 point{};if(!bone||!unbox(call(m.getPosition,bone),point))continue;
                    if(b==0)head=point;
                    Vec3 screen=project(point,view,projection,width,height);
                    bones[b]={screen.x,screen.y,screen.z};
                }
            }
        }
        Vec3 top=project(head,view,projection,width,height);
        Vec3 bottom=project(feet,view,projection,width,height);
        if(!std::isfinite(top.x)||!std::isfinite(bottom.x))continue;
        if(settings.playerEsp&&distance<=settings.espDistance){
            internal::Target target;target.headX=top.x;target.headY=top.y;target.feetX=bottom.x;
            target.feetY=bottom.y;target.depth=top.z;target.distance=distance;target.sleeping=sleeping;
            target.bones=bones;
            Object* vitals=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0x108);
            if(vitals){
                float maxHp=*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(vitals)+0x88);
                Object* entity=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(vitals)+0x68);
                Object* health=entity?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(entity)+0x98):nullptr;
                if(health){float current=*reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(health)+0x20);
                    if(std::isfinite(current)&&std::isfinite(maxHp)&&maxHp>0.f&&maxHp<10000.f&&current>=0.f&&current<=maxHp*1.1f)
                        target.hp=std::clamp(current/maxHp,0.f,1.f);}
            }
            Object* nick=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0x170);
            if(nick&&m.getNickname){Object* nameText=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(nick)+0x38);
                if(nameText)target.name=string(call(m.getNickname,nameText));}
            if(target.name.empty())target.name=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0x2e8));
            if(visual.weapon){Object* manager=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(player)+0xd0);
                Object* held=manager?*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(manager)+0x50):nullptr;
                if(held)target.item=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(held)+0x78));}
            frame.targets.push_back(std::move(target));
        }
        bool motionValid=false;Vec3 velocity{};
        if(settings.aim)velocity=trackMotion(player,head,now,motionValid);
        if(settings.aim&&bullet.valid&&motionValid&&cameraPos.y>=0&&head.y>=0&&!sleeping&&top.z>0&&distance<=settings.maxDistance){
            float sx=top.x-width*.5f,sy=top.y-height*.5f,score=std::hypot(sx,sy);
            if(score>=settings.fov||score>=best)continue;
            if(settings.visible&&m.raycast){
                Vec3 direction{head.x-cameraPos.x,head.y-cameraPos.y,head.z-cameraPos.z};
                float length=std::sqrt(direction.x*direction.x+direction.y*direction.y+direction.z*direction.z);
                if(length<=1.f)continue;direction={direction.x/length,direction.y/length,direction.z/length};
                float range=length-0.8f;int mask=-1,triggers=1;
                void* args[]={&cameraPos,&direction,&range,&mask,&triggers};bool blocked=true;
                if(!unbox(call(m.raycast,nullptr,args),blocked)||blocked)continue;
            }
            ballistic::V launch;float flight=0;
            if(!ballistic::intercept({head.x-cameraPos.x,head.y-cameraPos.y,head.z-cameraPos.z},
                {velocity.x,velocity.y,velocity.z},{bullet.gravity.x,bullet.gravity.y,bullet.gravity.z},bullet.drag,bullet.speed,launch,flight))continue;
            best=score;bestPoint={cameraPos.x+launch.x,cameraPos.y+launch.y,cameraPos.z+launch.z};haveBest=true;
        }
    }
    if(m.botType){
        void* botSearch[]={m.botType};Array* bots=reinterpret_cast<Array*>(call(m.find,nullptr,botSearch));
        if(bots&&bots->length<=512){hud.bots=static_cast<int>(bots->length);
            if(settings.esp)for(uintptr_t i=0;i<bots->length;i++){
                Object* bot=bots->items[i];if(!bot)continue;
                Object* tr=call(m.getTransform,bot);Vec3 feet{};
                if(!tr||!unbox(call(m.getPosition,tr),feet))continue;
                float dx=feet.x-cameraPos.x,dy=feet.y-cameraPos.y,dz=feet.z-cameraPos.z;
                float distance=std::sqrt(dx*dx+dy*dy+dz*dz);
                if(!std::isfinite(distance)||distance<1.f||distance>settings.espDistance)continue;
                Vec3 head=feet;head.y+=1.65f;Vec3 top=project(head,view,projection,width,height);
                Vec3 bottom=project(feet,view,projection,width,height);
                if(!std::isfinite(top.x)||!std::isfinite(bottom.x))continue;
                internal::Target t;t.headX=top.x;t.headY=top.y;t.feetX=bottom.x;t.feetY=bottom.y;
                t.depth=top.z;t.distance=distance;t.bot=true;
                Object* entity=*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(bot)+0x68);
                if(entity)t.name=string(*reinterpret_cast<Object**>(reinterpret_cast<uint8_t*>(entity)+0x88));
                frame.targets.push_back(std::move(t));
            }
        }
    }
    if(settings.esp){
        if(settings.oreEsp||settings.animalEsp||settings.objectEsp)sampleWorld(cameraPos,settings,now);
        else worldMarkers.clear();
        for(const auto& marker:worldMarkers){
            if(marker.kind>=1&&marker.kind<=4&&!settings.oreEsp)continue;
            Vec3 lower=marker.position,upper=marker.position;upper.y+=marker.kind==4?2.0f:1.0f;
            Vec3 bottom=project(lower,view,projection,width,height);
            Vec3 top=project(upper,view,projection,width,height);
            if(!std::isfinite(top.x)||!std::isfinite(bottom.x))continue;
            internal::Target t;t.headX=top.x;t.headY=top.y;t.feetX=bottom.x;t.feetY=bottom.y;
            t.depth=top.z;t.distance=marker.distance;t.kind=marker.kind;t.name=marker.name;
            frame.targets.push_back(std::move(t));
        }
    }
    internal::state.publishHud(hud);
    static bool firstWorldSample=false;
    if(!firstWorldSample){
        firstWorldSample=true;
        __android_log_print(ANDROID_LOG_INFO,BRAND_TAG,"w0:%d/%d/%d",gettid(),hud.players,hud.bots);
        stage("w0");
    }
    if(settings.esp||settings.aim)internal::state.publish(std::move(frame));
    if(settings.aim&&haveBest){
        Vec3 current{};if(!unbox(call(m.getPosition,cameraTransform),current))return;
        Vec3 delta{bestPoint.x-current.x,bestPoint.y-current.y,bestPoint.z-current.z};
        float distance=std::sqrt(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z);if(distance<0.1f)return;
        Vec3 forward{};if(!unbox(call(m.getForward,cameraTransform),forward))return;
        Vec3 desired{delta.x/distance,delta.y/distance,delta.z/distance};
        float fraction=1.f/std::max(1,settings.smooth);
        Vec3 blended{forward.x*(1.f-fraction)+desired.x*fraction,
                     forward.y*(1.f-fraction)+desired.y*fraction,
                     forward.z*(1.f-fraction)+desired.z*fraction};
        float magnitude=std::sqrt(blended.x*blended.x+blended.y*blended.y+blended.z*blended.z);
        if(magnitude<0.001f)return;
        Vec3 look{current.x+blended.x/magnitude*distance,current.y+blended.y/magnitude*distance,
                  current.z+blended.z/magnitude*distance};
        Vec3 up{0,1,0};void* args[]={&look,&up};call(m.lookAt,cameraTransform,args);
    }
}
void reportFeatureBindings(){
    std::string missing;
    auto report=[&](const char* name,bool bound){
        __android_log_print(ANDROID_LOG_INFO,BRAND_TAG,"b:%s=%d",name,bound?1:0);
        if(!bound){if(!missing.empty())missing+=", ";missing+=name;}
    };
    report("player ESP / counter",m.playerType&&m.find&&m.getPosition&&m.getView&&m.getProjection);
    report("bot ESP / counter",m.botType&&m.find);
    report("skeleton",m.getBone&&m.isHuman);
    report("aim",m.getForward&&m.lookAt);
    report("aim visibility",m.raycast);
    report("ballistic profile",m.getWeaponConfig&&m.getBulletSpeed&&m.getBallisticProfile&&m.getProfileGravity&&m.getProfileDrag);
    report("custom crosshair suppression",originalCrosshairUpdate!=nullptr);
    report("resources / animals ESP",m.resourceType&&m.find);
    report("crates ESP",m.lootType&&m.find&&m.getObjectName);
    report("camera FOV",m.getCameraFov&&m.setCameraFov);
    report("weapon FOV",m.getWeaponFov&&m.setWeaponFov);
    report("player / weapon chams",m.rendererType&&m.getRenderers&&m.getMaterials&&m.hasProperty&&m.getTint&&m.setTint);
    report("weapon transparency",m.getFloat&&m.setFloat&&m.getQueue&&m.setQueue&&m.enableKeyword&&m.disableKeyword);
    report("RGB sky",m.getAmbient&&m.setAmbient&&m.getSkybox&&m.getTint&&m.setTint);
    report("freecam",originalMove&&m.setPosition&&m.getRight&&m.getForward);
    report("auto farm",originalMove&&m.attackTool&&m.toolClass&&m.resourceType&&m.lookAt&&m.raycast&&m.getRight&&m.getForward);
    report("auto heal hotbar selection",m.getHotbar&&m.getSlots&&m.getSlotItem&&m.selectSlot);
    report("headshot sound hook",originalOneShot!=nullptr);
    internal::state.featureStatus(missing.empty()?"runtime bindings ready; device test pending":
        "missing bindings: "+missing);
}
// Entered only after an actual PlayerManager.LateUpdate returns. No runtime
// allocation, domain lookup, or GC registration is attempted by the boot pthread.
void initializeFromUpdate(){
    static std::atomic_flag resolving=ATOMIC_FLAG_INIT;
    static unsigned attempts=0;
    static uint64_t lastAttempt=0;
    if(ready.load(std::memory_order_acquire)||resolving.test_and_set(std::memory_order_acquire))return;
    const uint64_t now=internal::nowMs();
    if(attempts>=10||(lastAttempt&&now-lastAttempt<1000)){
        resolving.clear(std::memory_order_release);return;
    }
    lastAttempt=now;++attempts;
    __android_log_print(ANDROID_LOG_INFO,BRAND_TAG,"ri:%d/%u",gettid(),attempts);
    stage("resolving runtime from managed LateUpdate callback");
    if(!resolve()){
        std::string failure="Runtime resolve failed: "+(resolveFailure.empty()?
            std::string("required game methods unavailable"):resolveFailure);
        stage(failure.c_str());internal::state.rendererStatus(failure);
        resolving.clear(std::memory_order_release);return;
    }
    stage("IL2CPP methods resolved on managed callback");
    // This method reads the game's movement joystick. Returning zero keeps the player at rest.
    if(m.setPosition&&m.getRight&&m.getForward&&DobbyHook(reinterpret_cast<void*>(base+0x769A984),
            reinterpret_cast<dobby_dummy_func_t>(replacementMove),
            reinterpret_cast<dobby_dummy_func_t*>(&originalMove))==0){
        internal::state.freecamAvailableSet(true);
        internal::state.autoFarmAvailableSet(m.attackTool&&m.toolClass&&m.resourceType&&m.lookAt&&m.raycast&&m.getRight&&m.getForward);
    }
    if(*reinterpret_cast<volatile uint32_t*>(base+kOneShot)==kOneShotWord)
        DobbyHook(reinterpret_cast<void*>(base+kOneShot),
            reinterpret_cast<dobby_dummy_func_t>(replacementOneShot),
            reinterpret_cast<dobby_dummy_func_t*>(&originalOneShot));
    // CrosshairManager.Update, exact 12034 signature checked before installing.
    if(m.getActive&&m.setActive&&m.getGameObject&&
       *reinterpret_cast<const volatile uint32_t*>(base+0x7a71074)==0xf81d0ffe&&
       DobbyHook(reinterpret_cast<void*>(base+0x7a71074),reinterpret_cast<dobby_dummy_func_t>(crosshairUpdate),
           reinterpret_cast<dobby_dummy_func_t*>(&originalCrosshairUpdate))==0)internal::state.crosshairAvailableSet(true);
    reportFeatureBindings();
    ready.store(true,std::memory_order_release);
    stage("runtime ready: waiting for local player sample");
    resolving.clear(std::memory_order_release);
}
void replacement(void* self,void* info){
    if(!originalUpdate)return;
    originalUpdate(self,info);
    if(!ready.load(std::memory_order_acquire))initializeFromUpdate();
    if(ready.load(std::memory_order_acquire)&&call(m.getLocal,nullptr)==self){updateFreecam();tick();}
}
void* boot(void*){
    stage("thread started");
    for(int i=0;i<200&&!base;i++){dl_iterate_phdr(locate,nullptr);if(!base)usleep(100000);}
    if(!base){stage("FAILED: libil2cpp.so not found in game process");return nullptr;}
    stage("game library found");
    if(!versionMatches()){
        stage("FAILED:sig");
        internal::state.rendererStatus("sig");
        __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"sig");return nullptr;
    }
    stage("game signature verified");
    stage("attaching menu before runtime initialization");
    if(!internal::installUi()){stage("FAILED: Android UI did not attach");return nullptr;}
    if(DobbyHook(reinterpret_cast<void*>(base+kUpdate),reinterpret_cast<dobby_dummy_func_t>(replacement),
           reinterpret_cast<dobby_dummy_func_t*>(&originalUpdate))!=0){
        stage("FAILED:h");internal::state.rendererStatus("h");return nullptr;}
    stage("update hook installed; runtime deferred until PlayerManager.LateUpdate");
    stage("attaching Android UI");
    bool ui=internal::installUi();
    if(!ui){stage("FAILED:ui");__android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"ui-attach");return nullptr;}
    stage("Android UI attached; waiting for first frame");
    bool graphicsReady=false;
    for(int i=0;i<250;i++){
        if(internal::state.status().find("ready")!=std::string::npos){graphicsReady=true;break;}
        usleep(200000);
    }
    if(!graphicsReady){stage("FAILED:fr");__android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"fr");return nullptr;}
    // Marker file skipped under reflective loading; loader does not wait for it.
    stage(ready.load(std::memory_order_acquire)?"ready":"ready:defer");
    __android_log_print(ANDROID_LOG_INFO,BRAND_TAG,"rdy=%d",ready.load(std::memory_order_acquire)?1:0);
    return nullptr;
}
__attribute__((constructor)) void start(){
    pthread_t thread;
    int result=pthread_create(&thread,nullptr,boot,nullptr);
    if(result==0)pthread_detach(thread);
    else __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"th=%d",result);
}
}
