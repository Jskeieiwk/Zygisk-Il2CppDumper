#include <limits>
#include "ballistics.h"
#include <unordered_map>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <elf.h>
#include <fcntl.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <thread>
#include <unordered_set>
#include <vector>

namespace {
constexpr char kPackage[]="com.catsbit.oxidesurvivalisland";
constexpr std::array<uint8_t,20> kBuildId={0x76,0xe4,0x7a,0x1a,0xdd,0xbd,0x7a,0xee,0x36,0x59,
    0x5c,0x8d,0xc2,0xbb,0x2f,0x7e,0xac,0x1f,0xfc,0x5e};
struct Map {uintptr_t start=0,end=0,offset=0;std::string perms,path;};
struct Vec3 {float x=0,y=0,z=0;};
struct PlayerSample {uintptr_t object=0;Vec3 position,velocity;float hp=-1;bool sleeping=false,teammate=false;std::string name;};

class ProcessMemory {
    pid_t pid_;
public:
    explicit ProcessMemory(pid_t pid):pid_(pid){}
    bool read(uintptr_t address,void* out,size_t size) const {
        if(!address||!out||!size)return false;
        auto* bytes=static_cast<uint8_t*>(out);size_t done=0;
        while(done<size){
            iovec local{bytes+done,size-done};
            iovec remote{reinterpret_cast<void*>(address+done),size-done};
            ssize_t n=process_vm_readv(pid_,&local,1,&remote,1,0);
            if(n<=0)return false;
            done+=static_cast<size_t>(n);
        }
        return true;
    }
    bool write(uintptr_t address,const void* data,size_t size) const {
        if(!address||!data||!size)return false;
        auto* bytes=static_cast<const uint8_t*>(data);size_t done=0;
        while(done<size){
            iovec local{const_cast<uint8_t*>(bytes+done),size-done};
            iovec remote{reinterpret_cast<void*>(address+done),size-done};
            ssize_t n=process_vm_writev(pid_,&local,1,&remote,1,0);
            if(n<=0)return false;
            done+=static_cast<size_t>(n);
        }
        return true;
    }
    template<typename T> bool get(uintptr_t address,T& value) const {return read(address,&value,sizeof(value));}
};

std::vector<Map> maps(pid_t pid) {
    std::vector<Map> result;
    std::ifstream file("/proc/"+std::to_string(pid)+"/maps");
    std::string line;
    while(std::getline(file,line)){
        unsigned long start=0,end=0,offset=0;char perms[8]{};int used=0;
        if(std::sscanf(line.c_str(),"%lx-%lx %7s %lx %*s %*s %n",&start,&end,perms,&offset,&used)!=4)continue;
        std::string path=line.substr(static_cast<size_t>(used));
        while(!path.empty()&&path.front()==' ')path.erase(path.begin());
        result.push_back({start,end,offset,perms,path});
    }
    return result;
}
bool readable(const std::vector<Map>& m,uintptr_t address,size_t size){
    if(!address||size>0x100000||address+size<address)return false;
    for(const auto& x:m)if(x.perms.find('r')!=std::string::npos&&address>=x.start&&address+size<=x.end)return true;
    return false;
}
pid_t findPid(){
    DIR* dir=opendir("/proc");if(!dir)return 0;
    pid_t found=0;dirent* entry;
    while((entry=readdir(dir))){
        char* end=nullptr;long number=std::strtol(entry->d_name,&end,10);
        if(!end||*end||number<=0)continue;
        std::ifstream cmd("/proc/"+std::to_string(number)+"/cmdline");
        std::string name;std::getline(cmd,name,'\0');
        if(name==kPackage){found=static_cast<pid_t>(number);break;}
    }
    closedir(dir);return found;
}
bool hasExpectedBuildId(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t& base){
    base=0;
    for(const auto& x:m){
        if(x.offset!=0||x.path.find("libil2cpp.so")==std::string::npos)continue;
        Elf64_Ehdr eh{};
        if(!pm.get(x.start,eh)||std::memcmp(eh.e_ident,ELFMAG,SELFMAG)||
           eh.e_ident[EI_CLASS]!=ELFCLASS64||eh.e_machine!=EM_AARCH64||
           eh.e_phnum>128||eh.e_phentsize!=sizeof(Elf64_Phdr))continue;
        std::vector<Elf64_Phdr> ph(eh.e_phnum);
        if(!pm.read(x.start+eh.e_phoff,ph.data(),ph.size()*sizeof(Elf64_Phdr)))continue;
        for(const auto& p:ph){
            if(p.p_type!=PT_NOTE||p.p_memsz>4096||p.p_memsz<sizeof(Elf64_Nhdr))continue;
            std::vector<uint8_t> note(p.p_memsz);
            if(!pm.read(x.start+p.p_vaddr,note.data(),note.size()))continue;
            for(size_t at=0;at+sizeof(Elf64_Nhdr)<=note.size();){
                Elf64_Nhdr nh{};std::memcpy(&nh,note.data()+at,sizeof(nh));
                size_t name=(nh.n_namesz+3u)&~size_t(3),desc=(nh.n_descsz+3u)&~size_t(3);
                size_t next=at+sizeof(nh)+name+desc;
                if(next>note.size()||next<=at)break;
                const uint8_t* n=note.data()+at+sizeof(nh);
                const uint8_t* d=n+name;
                if(nh.n_type==NT_GNU_BUILD_ID&&nh.n_namesz==4&&std::memcmp(n,"GNU",4)==0&&
                   nh.n_descsz==kBuildId.size()&&std::memcmp(d,kBuildId.data(),kBuildId.size())==0){
                    base=x.start;return true;
                }
                at=next;
            }
        }
    }
    return false;
}
std::unordered_set<uintptr_t> findTexts(const ProcessMemory& pm,const std::vector<Map>& m,const char* needle){
    std::unordered_set<uintptr_t> found;
    const size_t size=std::strlen(needle)+1;
    for(const auto& x:m){
        if(x.path.find("global-metadata.dat")==std::string::npos||x.perms.find('r')==std::string::npos)continue;
        std::vector<uint8_t> block(1024*1024+64);
        for(uintptr_t at=x.start;at<x.end;at+=1024*1024){
            size_t count=std::min<size_t>(block.size(),x.end-at);
            if(!pm.read(at,block.data(),count))continue;
            for(size_t i=0;i+size<=count;i++)
                if(std::memcmp(block.data()+i,needle,size)==0){found.insert(at+i);if(found.size()>=256)return found;}
        }
    }
    return found;
}
uintptr_t findClass(const ProcessMemory& pm,const std::vector<Map>& m,const char* className,const char* nameSpace){
    auto names=findTexts(pm,m,className);
    auto spaces=findTexts(pm,m,nameSpace);
    if(names.empty()||spaces.empty())return 0;
    size_t scanned=0;
    std::vector<uint8_t> block(1024*1024+16);
    for(const auto& x:m){
        if(x.perms.size()<2||x.perms[0]!='r'||x.perms[1]!='w'||
           x.path.find("[stack")!=std::string::npos)continue;
        if(scanned>1024ull*1024*1024)break;
        scanned+=x.end-x.start;
        for(uintptr_t at=x.start;at<x.end;at+=1024*1024){
            size_t count=std::min<size_t>(block.size(),x.end-at);
            if(!pm.read(at,block.data(),count))continue;
            for(size_t i=16;i+16<=count;i+=8){
                uint64_t a=0,b=0;
                std::memcpy(&a,block.data()+i,8);std::memcpy(&b,block.data()+i+8,8);
                if(names.count(a)&&spaces.count(b))return at+i-16;
            }
        }
    }
    return 0;
}
bool playerList(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t klass,uintptr_t& list){
    // Il2CppClass.static_fields is 0xb8 in this Unity/IL2CPP layout.
    // PlayerManager.clientPlayerList is +0x10 in the static fields block.
    uintptr_t fields=0;list=0;
    return readable(m,klass+0xb8,8)&&pm.get(klass+0xb8,fields)&&
           readable(m,fields+0x10,8)&&pm.get(fields+0x10,list)&&readable(m,list+0x10,16);
}
bool localPosition(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t controller,uintptr_t& player,Vec3& pos){
    uintptr_t fields=0;player=0;
    if(!readable(m,controller+0xb8,8)||!pm.get(controller+0xb8,fields)||
       !readable(m,fields+0x10,8)||!pm.get(fields+0x10,player)||
       !readable(m,player+0x228,sizeof(pos))||!pm.get(player+0x228,pos))return false;
    return std::isfinite(pos.x)&&std::isfinite(pos.y)&&std::isfinite(pos.z)&&
           std::abs(pos.x)<100000&&std::abs(pos.y)<100000&&std::abs(pos.z)<100000;
}
uintptr_t pointerAt(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t address){
    uintptr_t value=0;
    return readable(m,address,sizeof(value))&&pm.get(address,value)?value:0;
}
std::string managedString(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t object){
    int32_t length=0;
    if(!readable(m,object+0x10,4)||!pm.get(object+0x10,length)||length<1||length>48||
       !readable(m,object+0x14,static_cast<size_t>(length)*2))return {};
    std::array<uint16_t,48> chars{};
    if(!pm.read(object+0x14,chars.data(),static_cast<size_t>(length)*2))return {};
    std::string out;
    for(int i=0;i<length;i++){
        uint32_t cp=chars[i];
        if(cp>=0xd800&&cp<=0xdbff&&i+1<length&&chars[i+1]>=0xdc00&&chars[i+1]<=0xdfff)
            cp=0x10000+((cp-0xd800)<<10)+(chars[++i]-0xdc00);
        if(cp<0x80)out.push_back(static_cast<char>(cp));
        else if(cp<0x800){out.push_back(static_cast<char>(0xc0|(cp>>6)));out.push_back(static_cast<char>(0x80|(cp&63)));}
        else if(cp<0x10000){out.push_back(static_cast<char>(0xe0|(cp>>12)));out.push_back(static_cast<char>(0x80|((cp>>6)&63)));out.push_back(static_cast<char>(0x80|(cp&63)));}
        else {out.push_back(static_cast<char>(0xf0|(cp>>18)));out.push_back(static_cast<char>(0x80|((cp>>12)&63)));
            out.push_back(static_cast<char>(0x80|((cp>>6)&63)));out.push_back(static_cast<char>(0x80|(cp&63)));}
    }
    return out;
}
std::string playerName(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t player){
    uintptr_t label=pointerAt(pm,m,player+0x170);
    uintptr_t text=pointerAt(pm,m,label+0x38);
    std::string name=managedString(pm,m,pointerAt(pm,m,text+0xe0));
    if(name.empty())name=managedString(pm,m,pointerAt(pm,m,player+0x2e8));
    return name;
}

bool transformPosition(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t transform,Vec3& out){
    uintptr_t data=pointerAt(pm,m,transform+0x28);int32_t index=-1;
    if(!data||!pm.get(transform+0x30,index)||index<0||index>65535)return false;
    uintptr_t trs=pointerAt(pm,m,data+0x18),parents=pointerAt(pm,m,data+0x20);
    if(!trs||!parents)return false;
    struct TRS {float t[4],q[4],s[4];};
    TRS node{};int32_t parent=-1;
    if(!pm.get(trs+index*sizeof(TRS),node)||!pm.get(parents+index*4,parent))return false;
    out={node.t[0],node.t[1],node.t[2]};
    std::unordered_set<int32_t> visited;
    for(int depth=0;parent>=0;depth++){
        if(depth>=128||parent>65535||!visited.insert(parent).second||!pm.get(trs+parent*sizeof(TRS),node))return false;
        Vec3 v{out.x*node.s[0],out.y*node.s[1],out.z*node.s[2]};
        Vec3 u{node.q[0],node.q[1],node.q[2]};float w=node.q[3];
        Vec3 cross{u.y*v.z-u.z*v.y,u.z*v.x-u.x*v.z,u.x*v.y-u.y*v.x};
        Vec3 twice{2*cross.x,2*cross.y,2*cross.z};
        out={v.x+w*twice.x+u.y*twice.z-u.z*twice.y+node.t[0],
             v.y+w*twice.y+u.z*twice.x-u.x*twice.z+node.t[1],
             v.z+w*twice.z+u.x*twice.y-u.y*twice.x+node.t[2]};
        if(!pm.get(parents+parent*4,parent))return false;
    }
    return std::isfinite(out.x)&&std::isfinite(out.y)&&std::isfinite(out.z);
}
bool bonePosition(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t player,uintptr_t unity,int humanId,Vec3& out){
    uintptr_t managed=pointerAt(pm,m,player+0x1f0),anim=pointerAt(pm,m,managed+0x10);
    uintptr_t avatar=pointerAt(pm,m,anim+0x1a8),mapping=pointerAt(pm,m,unity+0x1880888);
    int32_t internal=-1,bone=-1;int64_t relative=0;
    if(!anim||!avatar||!mapping||!pm.get(mapping+humanId*4,internal)||internal<0||internal>24)return false;
    if(!pm.get(avatar+0x28,relative)||!relative)return false;
    uintptr_t human=avatar+0x28+relative;
    if(!pm.get(human+0x50+internal*4,bone)||bone<0||bone>65535)return false;
    if(!pm.get(avatar+0x38,relative)||!relative)return false;
    int32_t skeletonIndex=-1;
    if(!pm.get(avatar+0x38+relative+bone*4,skeletonIndex)||skeletonIndex<0||skeletonIndex>65535)return false;
    uintptr_t skeleton=pointerAt(pm,m,anim+0x1d0),transform=0;uint8_t direct=0;
    if(!skeleton||!pm.get(anim+0x5d5,direct))return false;
    if(direct){uintptr_t array=pointerAt(pm,m,skeleton+8);if(!array)return false;transform=pointerAt(pm,m,array+skeletonIndex*8);}
    else{
        uint64_t count=0;uintptr_t array=pointerAt(pm,m,skeleton+0x20);
        if(!array||!pm.get(skeleton+0x18,count)||count>4096)return false;
        for(uint64_t i=0;i<count;i++){int32_t id=-1;if(pm.get(array+i*16+8,id)&&id==skeletonIndex){transform=pointerAt(pm,m,array+i*16);break;}}
    }
    return transform&&transformPosition(pm,m,transform,out);
}

struct WorldObject {int kind=0;Vec3 position;};
std::vector<WorldObject> worldObjects(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t network){
    std::vector<WorldObject> out;
    uintptr_t fields=pointerAt(pm,m,network+0xb8),dictionary=pointerAt(pm,m,fields+0x30);
    uintptr_t entries=pointerAt(pm,m,dictionary+0x18);int32_t count=0;uint64_t capacity=0;
    if(!dictionary||!entries||!pm.get(dictionary+0x20,count)||count<0||count>65536||!pm.get(entries+0x18,capacity)||capacity<static_cast<uint32_t>(count)||capacity>65536)return out;
    struct Entry {uint32_t hash;int32_t next;uint32_t key,padding;uintptr_t value;};
    std::vector<Entry> buffer(count);if(count&&!pm.read(entries+0x20,buffer.data(),buffer.size()*sizeof(Entry)))return out;
    for(const auto& entry:buffer){
        uintptr_t identity=entry.value;if(!identity)continue;
        uintptr_t components=pointerAt(pm,m,identity+0x80);uint64_t length=0;
        if(!components||!pm.get(components+0x18,length)||length>64)continue;
        for(uint64_t i=0;i<length;i++){
            uintptr_t object=pointerAt(pm,m,components+0x20+i*8),klass=pointerAt(pm,m,object);
            bool resource=false,loot=false,vehicle=false,building=false,door=false;
            for(int depth=0;klass&&depth<12;depth++){
                uintptr_t address=pointerAt(pm,m,klass+0x10);char name[32]{};
                if(address&&pm.read(address,name,31)){
                    resource=std::strcmp(name,"MineableObject")==0;loot=std::strcmp(name,"LootObject")==0;vehicle=std::strcmp(name,"VehicleManager")==0;building=std::strcmp(name,"BuildingPiece")==0;door=std::strcmp(name,"Door")==0;
                    if(resource||loot||vehicle||building||door)break;
                }
                klass=pointerAt(pm,m,klass+0x58);
            }
            if(building||door)continue;
            if(!resource&&!loot&&!vehicle)continue;
            int kind=100;
            if(resource){if(!pm.get(object+0xd8,kind))continue;
                switch(kind){case 1:case 2:case 3:case 4:case 5:case 6:case 8:case 9:case 10:case 11:case 22:case 25:case 26:case 27:break;default:continue;}}
            else if(vehicle){
                if(pointerAt(pm,m,object+0x118))kind=201;
                else if(pointerAt(pm,m,object+0x120))kind=202;
                else kind=200;
            }
            else{
                std::string label=managedString(pm,m,pointerAt(pm,m,object+0xe0));
                if(label.find("elite")!=std::string::npos)kind=102;else if(label.find("military")!=std::string::npos||label.find("army")!=std::string::npos)kind=101;else if(label.find("red")!=std::string::npos)kind=103;
            }
            uintptr_t native=pointerAt(pm,m,object+0x10),go=pointerAt(pm,m,native+0x20);
            uintptr_t componentList=pointerAt(pm,m,go+0x20),transform=pointerAt(pm,m,componentList+8);
            Vec3 position{};
            if(transform&&transformPosition(pm,m,transform,position)&&std::abs(position.x)<100000&&std::abs(position.y)<100000&&std::abs(position.z)<100000){
                out.push_back({kind,position});break;
            }
        }
        if(out.size()>=2048)break;
    }
    return out;
}
struct MotionSample {Vec3 position,velocity;std::chrono::steady_clock::time_point at;};
std::unordered_map<uintptr_t,MotionSample> motion;
Vec3 sampleVelocity(uintptr_t object,Vec3 position){
    if(motion.size()>4096)motion.clear();
    auto now=std::chrono::steady_clock::now();auto found=motion.find(object);
    if(found==motion.end()){motion[object]={position,{},now};return {};}
    auto& old=found->second;float dt=std::chrono::duration<float>(now-old.at).count();
    Vec3 delta{position.x-old.position.x,position.y-old.position.y,position.z-old.position.z};
    float distance=std::sqrt(delta.x*delta.x+delta.y*delta.y+delta.z*delta.z);
    if(dt>1||distance>50){old={position,{},now};return {};}
    if(distance>.005f&&dt>.01f){Vec3 v{delta.x/dt,delta.y/dt,delta.z/dt};float speed=std::sqrt(v.x*v.x+v.y*v.y+v.z*v.z);old={position,speed<150?v:Vec3{},now};}
    if(dt>.5f)return {};
    return old.velocity;
}
std::vector<PlayerSample> positions(const ProcessMemory& pm,const std::vector<Map>& m,uintptr_t list,uintptr_t local){
    std::vector<PlayerSample> out;uintptr_t array=0;int32_t size=0;uint64_t capacity=0;
    std::string localTeam=managedString(pm,m,pointerAt(pm,m,local+0x2f0));
    if(!pm.get(list+0x10,array)||!pm.get(list+0x18,size)||size<0||size>256||
       !readable(m,array+0x18,8)||!pm.get(array+0x18,capacity)||capacity<static_cast<uint64_t>(size)||capacity>4096)return out;
    for(int i=0;i<size;i++){
        uintptr_t object=0;Vec3 pos{};
        if(!pm.get(array+0x20+i*8,object)||!readable(m,object+0x228,sizeof(pos))||
           !pm.get(object+0x228,pos))continue;
        if(!std::isfinite(pos.x)||!std::isfinite(pos.y)||!std::isfinite(pos.z)||
           std::abs(pos.x)>100000||std::abs(pos.y)>100000||std::abs(pos.z)>100000)continue;
        PlayerSample sample;sample.object=object;sample.position=pos;sample.velocity=sampleVelocity(object,pos);
        int32_t flags=0;
        if(readable(m,object+0x2c0,4)&&pm.get(object+0x2c0,flags))sample.sleeping=(flags&1)!=0;
        sample.name=playerName(pm,m,object);
        if(!localTeam.empty()){
            auto team=managedString(pm,m,pointerAt(pm,m,object+0x2f0));
            sample.teammate=!team.empty()&&team==localTeam;
        }
        out.push_back(std::move(sample));
    }
    return out;
}

struct BulletProfile {float speed=0,gravity=0,drag=0;};
bool bulletProfile(const ProcessMemory& pm,const std::vector<Map>& maps,uintptr_t local,BulletProfile& out){
    uintptr_t fp=pointerAt(pm,maps,local+0xd0),weapon=pointerAt(pm,maps,fp+0x58);
    uintptr_t klass=pointerAt(pm,maps,weapon),name=pointerAt(pm,maps,klass+0x10);char type[10]{};
    if(!name||!pm.read(name,type,10)||std::memcmp(type,"FPHitscan",10)!=0)return false;
    uintptr_t config=pointerAt(pm,maps,weapon+0x138),profile=pointerAt(pm,maps,config+0x60);
    return config&&profile&&pm.get(config+0x30,out.speed)&&pm.get(profile+0x10,out.gravity)&&pm.get(profile+0x14,out.drag)&&
        std::isfinite(out.speed)&&out.speed>=1&&out.speed<=10000&&std::isfinite(out.gravity)&&out.gravity>=0&&out.gravity<=1000&&
        std::isfinite(out.drag)&&out.drag>=0&&out.drag<=100;
}

struct FreeCamera {
    uintptr_t camera=0;pid_t pid=0;uint8_t originalFlag=1;
    std::array<float,16> original{};Vec3 position{};float yaw=0,pitch=0;
    std::chrono::steady_clock::time_point last{};
    void restore(const ProcessMemory& pm){
        if(camera){
            if(originalFlag==0)pm.write(camera+0x70,original.data(),sizeof(original));
            pm.write(camera+0x502,&originalFlag,1);
        }
        camera=0;
    }
    bool tick(const ProcessMemory& pm,pid_t target,uintptr_t current,bool valid,std::array<float,16>& view,const std::string& config){
        auto now=std::chrono::steady_clock::now();
        float dt=last.time_since_epoch().count()?std::clamp(std::chrono::duration<float>(now-last).count(),0.f,.1f):0;last=now;
        if(pid!=target){camera=0;pid=target;}
        int aim=0,fov=0,smooth=0,width=0,height=0,enabled=0;long long heartbeat=0;
        float x=0,y=0,z=0,turn=0,speed=6;
        std::ifstream input(config);input>>aim>>heartbeat>>fov>>smooth>>width>>height>>enabled>>x>>y>>z>>turn>>speed;
        auto wall=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        bool active=input&&enabled==1&&heartbeat<=wall+1&&wall-heartbeat<=2&&valid&&current;
        if(camera&&(!active||camera!=current))restore(pm);
        if(!active)return false;
        if(!camera){
            if(!pm.get(current+0x502,originalFlag)||originalFlag>1)return false;
            original=view;camera=current;
            position={-(view[0]*view[12]+view[1]*view[13]+view[2]*view[14]),
                      -(view[4]*view[12]+view[5]*view[13]+view[6]*view[14]),
                      -(view[8]*view[12]+view[9]*view[13]+view[10]*view[14])};
            yaw=std::atan2(-view[2],-view[10]);pitch=std::asin(std::clamp(-view[6],-1.f,1.f));
        }
        if(!std::isfinite(x)||!std::isfinite(y)||!std::isfinite(z)||!std::isfinite(turn)||!std::isfinite(speed)){restore(pm);return false;}
        yaw+=std::clamp(turn,-1.f,1.f)*dt*1.5f;speed=std::clamp(speed,3.f,20.f);
        Vec3 forward{std::sin(yaw)*std::cos(pitch),std::sin(pitch),std::cos(yaw)*std::cos(pitch)};
        Vec3 right{std::cos(yaw),0,-std::sin(yaw)};
        Vec3 up{-std::sin(yaw)*std::sin(pitch),std::cos(pitch),-std::cos(yaw)*std::sin(pitch)};
        position.x+=(right.x*std::clamp(x,-1.f,1.f)+forward.x*std::clamp(z,-1.f,1.f))*speed*dt;
        position.y+=(forward.y*std::clamp(z,-1.f,1.f)+std::clamp(y,-1.f,1.f))*speed*dt;
        position.z+=(right.z*std::clamp(x,-1.f,1.f)+forward.z*std::clamp(z,-1.f,1.f))*speed*dt;
        view={right.x,up.x,-forward.x,0,right.y,up.y,-forward.y,0,right.z,up.z,-forward.z,0,
              -(right.x*position.x+right.y*position.y+right.z*position.z),
              -(up.x*position.x+up.y*position.y+up.z*position.z),
              forward.x*position.x+forward.y*position.y+forward.z*position.z,1};
        uint8_t custom=0;
        if(!pm.write(camera+0x70,view.data(),sizeof(view))||!pm.write(camera+0x502,&custom,1)){restore(pm);return false;}
        return true;
    }
};
float angleDelta(float desired,float current){return std::remainder(desired-current,360.f);}
void aimTick(const ProcessMemory& pm,const std::vector<Map>& maps,uintptr_t local,
             const std::vector<PlayerSample>& players,const std::array<float,16>& view,
             const std::array<float,16>& projection,const std::string& config){
    static std::string lastAimState;
    static auto lastAimReport=std::chrono::steady_clock::time_point{};
    auto report=[&](const char* state){
        auto tick=std::chrono::steady_clock::now();
        if(lastAimState!=state||tick-lastAimReport>std::chrono::seconds(5)){
            lastAimState=state;lastAimReport=tick;std::printf("AIM %s\n",state);
        }
    };
    int enabled=0;long long heartbeat=0;std::ifstream settings(config);int fov=100,smooth=3,width=0,height=0;settings>>enabled>>heartbeat>>fov>>smooth>>width>>height;
    auto now=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if(!settings||enabled!=1||heartbeat>now+1||now-heartbeat>2)return;
    if(!local||width<1||height<1){report("waiting_local_player_or_screen");return;}
    fov=std::clamp(fov,10,300);smooth=std::clamp(smooth,0,10);
    uintptr_t look=pointerAt(pm,maps,local+0xb0);std::array<float,2> angles{};
    if(!look||!pm.get(look+0x4c,angles)||!std::isfinite(angles[0])||!std::isfinite(angles[1])){report("waiting_look");return;}
    int free=0,farm=0,stop=0,heal=0,threshold=0,adsOnly=0;float fx=0,fy=0,fz=0,turn=0,speed=0;
    settings>>free>>fx>>fy>>fz>>turn>>speed>>farm>>stop>>heal>>threshold>>adsOnly;
    int fovShape=0;settings>>fovShape;
    if(!settings)return;
    if(adsOnly){uintptr_t manager=pointerAt(pm,maps,local+0xd0);float amount=0;
        if(!manager||!pm.get(manager+0xb4,amount)||!std::isfinite(amount)||amount<.5f||amount>1.01f)return;}
    BulletProfile bullet{};if(!bulletProfile(pm,maps,local,bullet)){report("waiting_weapon_profile");return;}
    float best=std::numeric_limits<float>::infinity();Vec3 target{},velocity{};bool found=false;
    for(const auto& player:players){
        if(player.object==local||player.teammate||player.sleeping)continue;
        Vec3 point=player.position;point.y+=1.55f;
        float cx=view[0]*point.x+view[4]*point.y+view[8]*point.z+view[12];
        float cy=view[1]*point.x+view[5]*point.y+view[9]*point.z+view[13];
        float cz=view[2]*point.x+view[6]*point.y+view[10]*point.z+view[14];
        float cw=view[3]*point.x+view[7]*point.y+view[11]*point.z+view[15];
        float w=projection[3]*cx+projection[7]*cy+projection[11]*cz+projection[15]*cw;
        float distanceSquared=cx*cx+cy*cy+cz*cz;
        if(!std::isfinite(distanceSquared)||distanceSquared<.01f||distanceSquared>62500.f)continue;
        if(w<.1f)continue;
        float x=(projection[0]*cx+projection[4]*cy+projection[8]*cz+projection[12]*cw)/w;
        float y=(projection[1]*cx+projection[5]*cy+projection[9]*cz+projection[13]*cw)/w;
        float sx=x*width*.5f,sy=y*height*.5f;
        float score=sx*sx+sy*sy;
        bool inside=fovShape==1?std::max(std::abs(sx),std::abs(sy))<=fov:fovShape==2?std::abs(sx)+std::abs(sy)<=fov:score<=fov*fov;
        if(!inside||!std::isfinite(score)||score>=best)continue;
        best=score;target=point;velocity=player.velocity;found=true;
    }
    if(!found){report("no_target_in_fov");return;}
    // Inverse of an orthonormal Unity world-to-camera matrix.
    Vec3 eye{-(view[0]*view[12]+view[1]*view[13]+view[2]*view[14]),
             -(view[4]*view[12]+view[5]*view[13]+view[6]*view[14]),
             -(view[8]*view[12]+view[9]*view[13]+view[10]*view[14])};
    float dx=target.x-eye.x,dy=target.y-eye.y,dz=target.z-eye.z;
    ballistic::V launch{};float flight=0;
    if(!ballistic::intercept({dx,dy,dz},{velocity.x,velocity.y,velocity.z},{0,-bullet.gravity,0},bullet.drag,bullet.speed,launch,flight)){report("no_ballistic_solution");return;}
    dx=launch.x;dy=launch.y;dz=launch.z;
    constexpr float radToDeg=57.2957795131f;
    float pitch=-std::atan2(dy,std::hypot(dx,dz))*radToDeg,yaw=std::atan2(dx,dz)*radToDeg;
    float dp=angleDelta(pitch,angles[0]),dyaw=angleDelta(yaw,angles[1]);
    if(!std::isfinite(dp)||!std::isfinite(dyaw)||std::abs(dp)>90||std::abs(dyaw)>90)return;
    float correction=1.f/(1.f+smooth);
    angles[0]=std::clamp(angles[0]+dp*correction,-80.f,80.f);angles[1]+=dyaw*correction;
    // Same two managed fields written by MouseLook.wED (0x76af83c).
    report(pm.write(look+0x4c,angles.data(),sizeof(angles))?"write_ok":"write_failed");
}

bool farmTick(const ProcessMemory& pm,const std::vector<Map>& maps,uintptr_t local,const std::vector<PlayerSample>& players,const std::vector<WorldObject>& objects,
              const std::array<float,16>& view,const std::string& config){
    int aim=0,fov=0,smooth=0,width=0,height=0,free=0,enabled=0;long long heartbeat=0;float x=0,y=0,z=0,turn=0,speed=0;int stopNearEnemy=0;
    std::ifstream input(config);input>>aim>>heartbeat>>fov>>smooth>>width>>height>>free>>x>>y>>z>>turn>>speed>>enabled>>stopNearEnemy;
    auto now=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if(!input||!enabled||free||now-heartbeat>2||heartbeat>now+1||!local)return false;
    if(stopNearEnemy){
        Vec3 origin{};if(!pm.get(local+0x228,origin))return true;
        for(const auto& player:players){
            if(player.object==local||player.teammate)continue;
            float dx=player.position.x-origin.x,dy=player.position.y-origin.y,dz=player.position.z-origin.z;
            float distanceSquared=dx*dx+dy*dy+dz*dz;
            if(std::isfinite(distanceSquared)&&distanceSquared<=2500.f){std::puts("FARM STOP_ENEMY");return true;}
        }
    }
    uintptr_t fp=pointerAt(pm,maps,local+0xd0),weapon=pointerAt(pm,maps,fp+0x58),klass=pointerAt(pm,maps,weapon);bool tool=false;
    for(int depth=0;klass&&depth<8;depth++){
        char name[16]{};uintptr_t address=pointerAt(pm,maps,klass+0x10);
        if(address&&pm.read(address,name,15)&&std::strcmp(name,"FPTool")==0){tool=true;break;}
        klass=pointerAt(pm,maps,klass+0x58);
    }
    if(!tool)return true;
    Vec3 eye{-(view[0]*view[12]+view[1]*view[13]+view[2]*view[14]),-(view[4]*view[12]+view[5]*view[13]+view[6]*view[14]),-(view[8]*view[12]+view[9]*view[13]+view[10]*view[14])};
    float best=10000;Vec3 target{};bool found=false;
    for(const auto& object:objects){if(object.kind<8||object.kind>11)continue;
        float dx=object.position.x-eye.x,dy=object.position.y-eye.y,dz=object.position.z-eye.z,d=dx*dx+dz*dz;
        if(d<best&&std::abs(dy)<8){best=d;target=object.position;found=true;}
    }
    if(!found)return true;
    target.y+=.8f;float dx=target.x-eye.x,dy=target.y-eye.y,dz=target.z-eye.z;
    uintptr_t look=pointerAt(pm,maps,local+0xb0);std::array<float,2> current{};
    if(!look||!pm.get(look+0x4c,current)||!std::isfinite(current[0])||!std::isfinite(current[1]))return true;
    float pitch=-std::atan2(dy,std::hypot(dx,dz))*57.2957795f,yaw=std::atan2(dx,dz)*57.2957795f;
    float delta=angleDelta(yaw,current[1]);current[0]=std::clamp(pitch,-80.f,80.f);current[1]+=delta*.35f;
    if(!pm.write(look+0x4c,current.data(),sizeof(current)))return true;
    static auto actionAt=std::chrono::steady_clock::time_point{};
    auto tick=std::chrono::steady_clock::now();
    if(tick-actionAt>std::chrono::milliseconds(900)&&std::abs(delta)<15){
        actionAt=tick;std::puts(best>7.84f?"FARM MOVE":"FARM ATTACK");
    }
    return true;
}

void healTick(const ProcessMemory& pm,const std::vector<Map>& maps,uintptr_t local,const std::string& config){
    std::ifstream input(config);int aim,fov,smooth,w,h,free,farm,stop,enabled,threshold;long long heartbeat;float x,y,z,turn,speed;
    input>>aim>>heartbeat>>fov>>smooth>>w>>h>>free>>x>>y>>z>>turn>>speed>>farm>>stop>>enabled>>threshold;
    auto now=std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    if(!input||!enabled||!local||now-heartbeat>2||heartbeat>now+1)return;
    uintptr_t vitals=pointerAt(pm,maps,local+0x108),entity=pointerAt(pm,maps,vitals+0x68),health=pointerAt(pm,maps,entity+0x98);
    float max=0,current=0;
    if(!vitals||!health||!pm.get(vitals+0x88,max)||!pm.get(health+0x20,current)||!std::isfinite(max)||!std::isfinite(current)||max<=0||max>10000||current<=0||current>max)return;
    static long long lastHeal=0;
    if(current/max*100<=std::clamp(threshold,1,99)&&now-lastHeal>=8){lastHeal=now;std::puts("HEAL");}
}
int selfTest(){
    int channel[2];if(pipe(channel)!=0)return 1;
    pid_t child=fork();if(child<0)return 1;
    if(child==0){
        close(channel[0]);volatile uint64_t value=0x1122334455667788ULL;
        uintptr_t address=reinterpret_cast<uintptr_t>(&value);
        write(channel[1],&address,sizeof(address));close(channel[1]);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        _exit(value==0x8877665544332211ULL?0:2);
    }
    close(channel[1]);uintptr_t address=0;
    if(read(channel[0],&address,sizeof(address))!=sizeof(address))return 1;
    close(channel[0]);ProcessMemory pm(child);uint64_t observed=0;
    uint64_t replacement=0x8877665544332211ULL;
    bool readable=pm.get(address,observed);int readError=errno;
    bool writable=readable&&pm.write(address,&replacement,sizeof(replacement));int writeError=errno;
    bool okay=readable&&observed==0x1122334455667788ULL&&writable;
    int status=0;waitpid(child,&status,0);
    if(!okay||!WIFEXITED(status)||WEXITSTATUS(status)!=0)
        std::fprintf(stderr,"self-test read=%d value=%llx errno=%d write=%d errno=%d child=%d\n",
            readable,static_cast<unsigned long long>(observed),readError,writable,writeError,status);
    return okay&&WIFEXITED(status)&&WEXITSTATUS(status)==0?0:1;
}
}

int main(int argc,char** argv){
    setvbuf(stdout,nullptr,_IOLBF,0);
    if(argc==2&&std::strcmp(argv[1],"--self-test")==0){
        int result=selfTest();std::puts(result?"SELFTEST FAIL":"SELFTEST PASS");return result;
    }
    if(geteuid()!=0){std::puts("STATUS ROOT_REQUIRED");return 1;}
    std::puts("STATUS ROOT_GRANTED_SELFTEST");
    if(selfTest()!=0){std::puts("STATUS PROCESS_VM_UNAVAILABLE");return 1;}
    std::string aimConfig=argc==3&&std::strcmp(argv[1],"--config")==0?argv[2]:"";
    FreeCamera freeCamera;
    pid_t previous=0;uintptr_t klass=0,controller=0,network=0;
    std::vector<WorldObject> world;auto worldAt=std::chrono::steady_clock::time_point{};auto lastScan=std::chrono::steady_clock::time_point{};
    for(;;){
        pid_t pid=findPid();
        if(!pid){std::puts("STATUS WAITING_GAME");previous=0;klass=controller=network=0;world.clear();std::this_thread::sleep_for(std::chrono::seconds(1));continue;}
        if(pid!=previous){motion.clear();previous=pid;klass=controller=network=0;world.clear();lastScan={};}
        ProcessMemory pm(pid);auto m=maps(pid);uintptr_t base=0;
        // Build ID check is informational only: findClass is byte-pattern based
        // on name+namespace pointer pairs, so it works across minor game updates
        // without re-dumping. Emit BUILD_MISMATCH as a warning once per pid and
        // keep going — if the Il2Cpp layout really changed, findClass will
        // simply return 0 and STATUS SEARCHING_PLAYERS will remain.
        static uintptr_t lastBuildWarnPid=0;
        if(!hasExpectedBuildId(pm,m,base)&&lastBuildWarnPid!=static_cast<uintptr_t>(pid)){
            lastBuildWarnPid=static_cast<uintptr_t>(pid);
            std::puts("STATUS BUILD_MISMATCH (continuing with pattern-based resolve)");
        }
        if((!klass||!controller||!network)&&std::chrono::steady_clock::now()-lastScan>std::chrono::seconds(klass?30:5)){
            lastScan=std::chrono::steady_clock::now();
            if(!klass)klass=findClass(pm,m,"PlayerManager","Oxide");
            if(!controller)controller=findClass(pm,m,"GameControllerBase","Oxide");
            if(!network)network=findClass(pm,m,"NetworkClient","Mirror");
            std::printf("RESOLVE player=%d controller=%d network=%d\n",klass?1:0,controller?1:0,network?1:0);
        }
        if(!klass){std::puts("STATUS SEARCHING_PLAYERS");std::this_thread::sleep_for(std::chrono::milliseconds(750));continue;}
        uintptr_t list=0;
        if(!playerList(pm,m,klass,list)){freeCamera.restore(pm);std::puts("STATUS WAITING_WORLD");std::this_thread::sleep_for(std::chrono::milliseconds(750));continue;}
        Vec3 local{};uintptr_t localObject=0;
        bool hasLocal=controller&&localPosition(pm,m,controller,localObject,local);
        // Two independently declared managed references must agree before using
        // the native Unity camera. Matrix offsets are not part of dump.cs.
        uintptr_t fp=hasLocal?pointerAt(pm,m,localObject+0xd0):0;
        uintptr_t ray=hasLocal?pointerAt(pm,m,localObject+0xc8):0;
        uintptr_t fpCamera=fp?pointerAt(pm,m,fp+0x20):0;
        uintptr_t rayCamera=ray?pointerAt(pm,m,ray+0x30):0;
        uintptr_t nativeCamera=fpCamera&&fpCamera==rayCamera?pointerAt(pm,m,fpCamera+0x10):0;
        static uintptr_t previousCamera=0;
        if(nativeCamera!=previousCamera){
            previousCamera=nativeCamera;
            std::printf("CAMERA %d %d\n",hasLocal?1:0,nativeCamera?1:0);
        }
        std::array<float,16> view{},projection{};
        uintptr_t unityBase=0;
        for(const auto& mapping:m)if(mapping.path.find("libunity.so")!=std::string::npos&&mapping.offset==0){unityBase=mapping.start;break;}
        std::array<uint8_t,8> unityId{};
        const std::array<uint8_t,8> expectedUnityId={0xd0,0xa3,0x98,0xd6,0xe8,0xc5,0xd5,0x05};
        bool unityMatches=unityBase&&pm.read(unityBase+0x318,unityId.data(),unityId.size())&&unityId==expectedUnityId;
        bool matrices=unityMatches&&nativeCamera&&pm.read(nativeCamera+0x70,view.data(),sizeof(view))&&
            pm.read(nativeCamera+0xb0,projection.data(),sizeof(projection));
        if(matrices){
            for(float value:view)matrices=matrices&&std::isfinite(value);
            for(float value:projection)matrices=matrices&&std::isfinite(value);
            matrices=matrices&&std::abs(view[15]-1)<.05f&&std::abs(projection[0])>.01f&&std::abs(projection[5])>.01f;
        }
        bool freecamActive=freeCamera.tick(pm,pid,nativeCamera,matrices,view,aimConfig);
        std::printf("MATRIX %d",matrices?1:0);
        if(matrices){for(float value:view)std::printf(" %.8g",value);for(float value:projection)std::printf(" %.8g",value);}
        std::putchar('\n');
        if(unityMatches&&network&&std::chrono::steady_clock::now()-worldAt>std::chrono::milliseconds(800)){
            worldAt=std::chrono::steady_clock::now();world=worldObjects(pm,m,network);
            std::printf("WORLD %zu",world.size());for(const auto& object:world)std::printf(" %d %.4f %.4f %.4f",object.kind,object.position.x,object.position.y,object.position.z);std::putchar('\n');
        }
        auto points=positions(pm,m,list,hasLocal?localObject:0);
        if(hasLocal)healTick(pm,m,localObject,aimConfig);
        bool farming=matrices&&!freecamActive&&!aimConfig.empty()&&farmTick(pm,m,localObject,points,world,view,aimConfig);
        if(matrices&&!freecamActive&&!farming&&!aimConfig.empty())aimTick(pm,m,localObject,points,view,projection,aimConfig);
        std::printf("FRAME %d %zu %d %.1f %.1f %.1f",pid,points.size(),hasLocal?1:0,local.x,local.y,local.z);
        constexpr char hex[]="0123456789abcdef";
        for(size_t i=0;i<points.size()&&i<32;i++){
            const auto& p=points[i];
            std::printf(" %.1f %.1f %.1f %.2f %d %d ",p.position.x,p.position.y,p.position.z,p.hp,
                p.sleeping?1:0,p.teammate?1:0);
            if(p.name.empty())std::putchar('-');
            else for(unsigned char ch:p.name){std::putchar(hex[ch>>4]);std::putchar(hex[ch&15]);}
        }
        std::putchar('\n');
        // HumanBodyBones: hips, spine, chest, neck, head, arms and legs.
        constexpr int boneIds[]={0,7,8,9,10,11,12,13,14,15,16,1,2,3,4,5,6};
        static auto bonesAt=std::chrono::steady_clock::time_point{};
        bool updateBones=matrices&&std::chrono::steady_clock::now()-bonesAt>=std::chrono::milliseconds(100);
        if(updateBones){bonesAt=std::chrono::steady_clock::now();std::printf("BONES %zu",std::min<size_t>(points.size(),32));
        for(size_t i=0;i<points.size()&&i<32;i++)for(int bone:boneIds){
            Vec3 position{};bool valid=bonePosition(pm,m,points[i].object,unityBase,bone,position);
            Vec3 delta{position.x-points[i].position.x,position.y-points[i].position.y,position.z-points[i].position.z};
            valid=valid&&delta.x*delta.x+delta.y*delta.y+delta.z*delta.z<100;
            std::printf(" %d %.4f %.4f %.4f",valid?1:0,position.x,position.y,position.z);
        }
        std::putchar('\n');}
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}
