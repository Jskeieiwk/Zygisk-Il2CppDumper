#include "internal_state.h"
#include "brand.h"
#include <android/log.h>
#include <jni.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>
#include <link.h>
#include <fstream>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

namespace internal {
namespace {
bool failed(JNIEnv* env,const char* step);
std::string stagedSoundPath;
std::string uiDexPath;
std::string stagedDexPath(JNIEnv* env, jobject app) {
    jclass context=env->FindClass("android/content/Context");
    if(!context||failed(env,"Context")) return {};
    jmethodID getCache=env->GetMethodID(context,"getCodeCacheDir","()Ljava/io/File;");
    if(!getCache||failed(env,"getCodeCacheDir lookup")) return {};
    jobject cache=env->CallObjectMethod(app,getCache);
    if(!cache||failed(env,"getCodeCacheDir")) return {};
    jclass fileClass=env->FindClass("java/io/File");
    if(!fileClass||failed(env,"File")) return {};
    jmethodID absolute=env->GetMethodID(fileClass,"getAbsolutePath","()Ljava/lang/String;");
    if(!absolute||failed(env,"getAbsolutePath lookup")) return {};
    jstring path=static_cast<jstring>(env->CallObjectMethod(cache,absolute));
    if(!path||failed(env,"getAbsolutePath")) return {};
    const char* chars=env->GetStringUTFChars(path,nullptr);
    if(!chars||failed(env,"cache path")) return {};
    std::string directory(chars);env->ReleaseStringUTFChars(path,chars);
    DIR* entries=opendir(directory.c_str());
    if(!entries) return {};
    std::string best;time_t newest=0;
    const std::string prefix=BRAND_LIB_PREFIX;
    while(dirent* entry=readdir(entries)) {
        std::string name(entry->d_name);
        if(name.compare(0,prefix.size(),prefix)!=0||name.size()<=prefix.size()+4||
           name.compare(name.size()-4,4,".dex")!=0) continue;
        std::string candidate=directory+"/"+name;
        struct stat info{};
        if(stat(candidate.c_str(),&info)!=0||!S_ISREG(info.st_mode)) continue;
        if(best.empty()||info.st_mtime>=newest){best=candidate;newest=info.st_mtime;}
    }
    closedir(entries);
    return best;
}
// Resolve an exported function from the exact loaded ART image.
void* artExport(const char* name) {
    struct Search {const char* name;void* result;}; Search search{name,nullptr};
    dl_iterate_phdr([](dl_phdr_info* info,size_t,void* opaque)->int {
        auto& q=*static_cast<Search*>(opaque);
        if(!info->dlpi_name||!strstr(info->dlpi_name,"/libart.so"))return 0;
        std::ifstream f(info->dlpi_name,std::ios::binary);Elf64_Ehdr eh{};
        if(!f.read(reinterpret_cast<char*>(&eh),sizeof(eh))||memcmp(eh.e_ident,ELFMAG,SELFMAG)||eh.e_ident[EI_CLASS]!=ELFCLASS64||eh.e_shentsize!=sizeof(Elf64_Shdr)||eh.e_shnum>4096)return 0;
        std::vector<Elf64_Shdr> sections(eh.e_shnum);
        f.seekg(eh.e_shoff);if(!f.read(reinterpret_cast<char*>(sections.data()),sections.size()*sizeof(Elf64_Shdr)))return 0;
        for(const auto& sec:sections){
            if(sec.sh_type!=SHT_DYNSYM||sec.sh_link>=sections.size()||sec.sh_entsize!=sizeof(Elf64_Sym)||sec.sh_size>16*1024*1024)continue;
            const auto& strings=sections[sec.sh_link];if(strings.sh_size>32*1024*1024)continue;
            std::vector<char> names(strings.sh_size);f.seekg(strings.sh_offset);if(!f.read(names.data(),names.size()))return 0;
            std::vector<Elf64_Sym> symbols(sec.sh_size/sizeof(Elf64_Sym));f.seekg(sec.sh_offset);
            if(!f.read(reinterpret_cast<char*>(symbols.data()),symbols.size()*sizeof(Elf64_Sym)))return 0;
            for(const auto& sym:symbols){
                if(sym.st_shndx==SHN_UNDEF||ELF64_ST_TYPE(sym.st_info)!=STT_FUNC||sym.st_name>=names.size())continue;
                const char* n=names.data()+sym.st_name;
                if(!memchr(n,0,names.size()-sym.st_name)||strcmp(n,q.name))continue;
                bool executable=false;for(int i=0;i<info->dlpi_phnum;i++){const auto& ph=info->dlpi_phdr[i];if(ph.p_type==PT_LOAD&&(ph.p_flags&PF_X)&&sym.st_value>=ph.p_vaddr&&sym.st_value-ph.p_vaddr<ph.p_memsz)executable=true;}
                if(executable)q.result=reinterpret_cast<void*>(info->dlpi_addr+sym.st_value);
                return q.result?1:0;
            }
        }return 0;
    },&search);
    return search.result;
}
jstring unicode(JNIEnv* env,const std::string& value){
    std::vector<jchar> chars;chars.reserve(value.size());
    for(size_t i=0;i<value.size();){
        unsigned char first=static_cast<unsigned char>(value[i++]);uint32_t cp=first;
        int rest=0;
        if(first>=0xc2&&first<=0xdf){cp=first&31;rest=1;}
        else if(first>=0xe0&&first<=0xef){cp=first&15;rest=2;}
        else if(first>=0xf0&&first<=0xf4){cp=first&7;rest=3;}
        else if(first>=0x80){cp='?';}
        for(int n=0;n<rest;n++){
            if(i>=value.size()||(static_cast<unsigned char>(value[i])&0xc0)!=0x80){cp='?';break;}
            cp=(cp<<6)|(static_cast<unsigned char>(value[i++])&0x3f);
        }
        if(cp>0x10ffff||(cp>=0xd800&&cp<=0xdfff))cp='?';
        if(cp<=0xffff)chars.push_back(static_cast<jchar>(cp));
        else {cp-=0x10000;chars.push_back(static_cast<jchar>(0xd800+(cp>>10)));
            chars.push_back(static_cast<jchar>(0xdc00+(cp&0x3ff)));}
    }
    return env->NewString(chars.data(),static_cast<jsize>(chars.size()));
}
jboolean crosshairAvailable(JNIEnv*,jclass){return state.crosshairAvailable()?JNI_TRUE:JNI_FALSE;}
void configure(JNIEnv* env,jclass,jintArray values) {
    if(!values||env->GetArrayLength(values)!=54) return;
    jint copy[54];env->GetIntArrayRegion(values,0,54,copy);
    if(!env->ExceptionCheck()) state.configure(copy);
}
jstring status(JNIEnv* env,jclass) {return env->NewStringUTF(state.status().c_str());}
jintArray hud(JNIEnv* env,jclass) {Hud value=state.readHud();jint items[5]={value.players,value.bots,value.hp,value.maxHp,value.ammo};
    jintArray result=env->NewIntArray(5);if(result)env->SetIntArrayRegion(result,0,5,items);return result;}
jobjectArray frame(JNIEnv* env,jclass) {
    RenderState data=state.renderState();
    const uint64_t now=nowMs();
    const bool fresh=data.frame.sampled&&now>=data.frame.sampled&&now-data.frame.sampled<500;
    const int flags=(fresh&&data.config.aim&&data.visual.fov?1:0)|(data.config.esp?2:0)|
        (data.visual.boxes?4:0)|(data.visual.skeleton?8:0)|(data.visual.arrows?16:0)|
        (data.visual.names?32:0)|(data.visual.distance?64:0)|(data.visual.hp?128:0);
    const size_t count=fresh&&data.enabled&&data.config.esp?std::min<size_t>(data.frame.targets.size(),160):0;
    std::vector<jfloat> numbers(8+40*count);
    numbers[0]=static_cast<jfloat>(data.frame.width);numbers[1]=static_cast<jfloat>(data.frame.height);
    numbers[2]=static_cast<jfloat>(data.config.fov);numbers[3]=static_cast<jfloat>(flags);
    numbers[4]=static_cast<jfloat>(count);numbers[5]=static_cast<jfloat>(data.visual.thickness);
    numbers[6]=static_cast<jfloat>(data.visual.color);numbers[7]=static_cast<jfloat>(data.config.espDistance);
    jclass stringClass=env->FindClass("java/lang/String");
    jclass objectClass=env->FindClass("java/lang/Object");
    if(!stringClass||!objectClass)return nullptr;
    jobjectArray names=env->NewObjectArray(static_cast<jsize>(count),stringClass,nullptr);
    if(!names)return nullptr;
    for(size_t i=0;i<count;i++){
        const Target& t=data.frame.targets[i];size_t at=8+i*40;
        numbers[at]=t.headX;numbers[at+1]=t.headY;numbers[at+2]=t.feetX;numbers[at+3]=t.feetY;
        numbers[at+4]=t.depth;numbers[at+5]=t.distance;numbers[at+6]=t.hp;
        numbers[at+7]=static_cast<jfloat>(t.kind);numbers[at+8]=t.bot?1.f:0.f;
        numbers[at+9]=t.sleeping?1.f:0.f;
        for(size_t b=0;b<10;b++){
            numbers[at+10+b*3]=t.bones[b].x;numbers[at+11+b*3]=t.bones[b].y;
            numbers[at+12+b*3]=t.bones[b].z;
        }
        std::string label=t.kind?t.name:t.sleeping?(t.name.empty()?"Спящий":t.name+" (Спящий)"):
            t.bot?(t.name.empty()?"Бот":t.name):(t.name.empty()?"Игрок":t.name);
        if(!t.kind&&data.visual.weapon&&!t.item.empty())label+=" · "+t.item;
        jstring name=unicode(env,label);
        env->SetObjectArrayElement(names,static_cast<jsize>(i),name);env->DeleteLocalRef(name);
    }
    jfloatArray values=env->NewFloatArray(static_cast<jsize>(numbers.size()));
    if(!values)return nullptr;
    env->SetFloatArrayRegion(values,0,static_cast<jsize>(numbers.size()),numbers.data());
    jobjectArray result=env->NewObjectArray(2,objectClass,nullptr);
    if(result){env->SetObjectArrayElement(result,0,values);env->SetObjectArrayElement(result,1,names);}
    env->DeleteLocalRef(values);env->DeleteLocalRef(names);
    state.rendererStatus("ready");
    return result;
}
void menuOpen(JNIEnv*,jclass,jboolean value) {state.menuOpen(value);}
void active(JNIEnv*,jclass,jboolean value) {state.active(value);}
jboolean freecam(JNIEnv*,jclass,jboolean value,jint movement,jfloat yaw,jfloat pitch) {return state.freecam(value,movement,yaw,pitch);}
jstring soundPath(JNIEnv* env,jclass){
    if(stagedSoundPath.empty()||access(stagedSoundPath.c_str(),R_OK)!=0)return nullptr;
    return env->NewStringUTF(stagedSoundPath.c_str());}
void soundReady(JNIEnv*,jclass,jboolean value){state.soundAvailable(value);}
jint consumeHits(JNIEnv*,jclass){return state.consumeHits();}
jint hitVolume(JNIEnv*,jclass){return state.hitVolume();}
jboolean autoFarm(JNIEnv*,jclass,jboolean value){return state.autoFarm(value);}
bool failed(JNIEnv* env,const char* step) {
    if(!env->ExceptionCheck()) return false;
    env->ExceptionDescribe();env->ExceptionClear();
    __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"ui: %s",step);return true;
}
}
bool installUi() {
    // dlopen injection does not invoke JNI_OnLoad: obtain the game's existing VM.
    using GetVMs=jint(*)(JavaVM**,jsize,jsize*);
    auto getVMs=reinterpret_cast<GetVMs>(dlsym(RTLD_DEFAULT,"JNI_GetCreatedJavaVMs"));
    if(!getVMs) {
        void* art=dlopen("libart.so",RTLD_NOW|RTLD_NOLOAD);
        if(art) {getVMs=reinterpret_cast<GetVMs>(dlsym(art,"JNI_GetCreatedJavaVMs"));dlclose(art);}
    }
    if(!getVMs)getVMs=reinterpret_cast<GetVMs>(artExport("JNI_GetCreatedJavaVMs"));
    JavaVM* vm=nullptr;jsize count=0;
    if(!getVMs||getVMs(&vm,1,&count)!=JNI_OK||count!=1||!vm) {
        __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"vm");return false;
    }
    JNIEnv* env=nullptr;
    if(vm->AttachCurrentThread(&env,nullptr)!=JNI_OK) {
        __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"att");return false;
    }
    bool success=false;
    // Local frame also bounds references during retries while the game starts.
    for(int attempt=0;attempt<100&&!success;attempt++) {
        if(env->PushLocalFrame(32)!=JNI_OK) break;
        auto run=[&]()->bool {
            jclass thread=env->FindClass("android/app/ActivityThread");
            if(failed(env,"ActivityThread")||!thread) return false;
            jmethodID current=env->GetStaticMethodID(thread,"currentApplication","()Landroid/app/Application;");
            if(failed(env,"currentApplication lookup")||!current) return false;
            jobject app=env->CallStaticObjectMethod(thread,current);
            if(failed(env,"currentApplication")||!app) return false;
            jclass context=env->FindClass("android/content/Context");
            jmethodID getLoader=env->GetMethodID(context,"getClassLoader","()Ljava/lang/ClassLoader;");
            if(failed(env,"getClassLoader lookup")||!getLoader) return false;
            jobject parent=env->CallObjectMethod(app,getLoader);
            if(failed(env,"getClassLoader")||!parent) return false;
            jclass loaderClass=env->FindClass("java/lang/ClassLoader");
            jmethodID load=env->GetMethodID(loaderClass,"loadClass","(Ljava/lang/String;)Ljava/lang/Class;");
            if(failed(env,"loadClass lookup")||!load) return false;
            jclass unity=static_cast<jclass>(env->CallObjectMethod(parent,load,env->NewStringUTF("com.unity3d.player.UnityPlayer")));
            if(failed(env,"UnityPlayer")||!unity) return false;
            jfieldID field=env->GetStaticFieldID(unity,"currentActivity","Landroid/app/Activity;");
            if(failed(env,"currentActivity lookup")||!field) return false;
            jobject activity=env->GetStaticObjectField(unity,field);
            if(failed(env,"currentActivity")||!activity) return false;
            // Manual mapping has no linker soinfo, so dladdr cannot locate the payload.
            // Find the DEX that the injector staged in the application's code cache.
            std::string dex=stagedDexPath(env,app);
            if(access(dex.c_str(),R_OK)!=0) {
                __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"dex");return false;
            }
            uiDexPath=dex;
            stagedSoundPath=dex;
            stagedSoundPath.replace(stagedSoundPath.size()-4,4,".ogg");
            jclass dexClass=env->FindClass("dalvik/system/DexClassLoader");
            jmethodID ctor=env->GetMethodID(dexClass,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/ClassLoader;)V");
            if(failed(env,"DexClassLoader lookup")||!ctor) return false;
            std::string optimized=dex.substr(0,dex.find_last_of('/'));
            jobject loader=env->NewObject(dexClass,ctor,env->NewStringUTF(dex.c_str()),
                env->NewStringUTF(optimized.c_str()),nullptr,parent);
            if(failed(env,"DexClassLoader")||!loader) return false;
            jclass bridge=static_cast<jclass>(env->CallObjectMethod(loader,load,env->NewStringUTF(BRAND_CLASS_BRIDGE)));
            if(failed(env,"b")||!bridge) return false;
            const JNINativeMethod methods[]={
                {const_cast<char*>("crosshairAvailable"),const_cast<char*>("()Z"),reinterpret_cast<void*>(crosshairAvailable)},
                {const_cast<char*>("configure"),const_cast<char*>("([I)V"),reinterpret_cast<void*>(configure)},
                {const_cast<char*>("status"),const_cast<char*>("()Ljava/lang/String;"),reinterpret_cast<void*>(status)},
                {const_cast<char*>("hud"),const_cast<char*>("()[I"),reinterpret_cast<void*>(hud)},
                {const_cast<char*>("frame"),const_cast<char*>("()[Ljava/lang/Object;"),reinterpret_cast<void*>(frame)},
                {const_cast<char*>("menuOpen"),const_cast<char*>("(Z)V"),reinterpret_cast<void*>(menuOpen)},
                {const_cast<char*>("active"),const_cast<char*>("(Z)V"),reinterpret_cast<void*>(active)},
                {const_cast<char*>("freecam"),const_cast<char*>("(ZIFF)Z"),reinterpret_cast<void*>(freecam)},
                {const_cast<char*>("soundPath"),const_cast<char*>("()Ljava/lang/String;"),reinterpret_cast<void*>(soundPath)},
                {const_cast<char*>("soundReady"),const_cast<char*>("(Z)V"),reinterpret_cast<void*>(soundReady)},
                {const_cast<char*>("consumeHits"),const_cast<char*>("()I"),reinterpret_cast<void*>(consumeHits)},
                {const_cast<char*>("hitVolume"),const_cast<char*>("()I"),reinterpret_cast<void*>(hitVolume)},
                {const_cast<char*>("autoFarm"),const_cast<char*>("(Z)Z"),reinterpret_cast<void*>(autoFarm)}};
            jint registration=env->RegisterNatives(bridge,methods,13);
            if(failed(env,"RegisterNatives")||registration!=JNI_OK) return false;
            jclass entry=static_cast<jclass>(env->CallObjectMethod(loader,load,env->NewStringUTF(BRAND_CLASS_ENTRY)));
            if(failed(env,"e")||!entry) return false;
            jmethodID install=env->GetStaticMethodID(entry,"install","(Landroid/app/Activity;)Z");
            if(failed(env,"install lookup")||!install) return false;
            jboolean attached=env->CallStaticBooleanMethod(entry,install,activity);
            return !failed(env,"install")&&attached==JNI_TRUE;
        };
        success=run();env->PopLocalFrame(nullptr);
        if(!success) usleep(200000);
    }
    vm->DetachCurrentThread();
    if(success) {
        const std::string marker=uiDexPath+".ui-ok";
        int fd=open(marker.c_str(),O_WRONLY|O_CREAT|O_TRUNC|O_CLOEXEC,0600);
        if(fd<0) {
            __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"UI marker: open failed");
            return false;
        }
        const char message[]="ready\n";
        const bool written=write(fd,message,sizeof(message)-1)==static_cast<ssize_t>(sizeof(message)-1);
        close(fd);
        if(!written) {
            __android_log_print(ANDROID_LOG_ERROR,BRAND_TAG,"UI marker: write failed");
            return false;
        }
    }
    return success;
}
}
