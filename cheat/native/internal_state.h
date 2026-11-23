#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <mutex>
#include <string>
#include <vector>

namespace internal {
inline uint64_t nowMs() {return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();}
struct Point {float x=0,y=0,z=0;};
struct Target {
    float headX=0,headY=0,feetX=0,feetY=0,depth=0,distance=0,hp=-1;
    std::array<Point,10> bones{};
    std::string item,name;
    bool bot=false,sleeping=false;
    unsigned kind=0;
};
struct Frame {int width=0,height=0;uint64_t sampled=0;std::vector<Target> targets;};
struct Hud {int players=-1,bots=-1,hp=-1,maxHp=-1,ammo=-1;uint64_t sampled=0;};
struct Config {
    bool customCrosshair=false;
    bool esp=false,aim=false;
    int fov=180;
    bool visible=true;
    int smooth=1,maxDistance=200,bone=0,mode=0,espDistance=300;
    bool noSpread=false,noRecoil=false,ballistics=false;
    bool silentAim=false,magicBullets=false,infiniteAmmo=false,espSleepers=true;
    int freecamSpeed=12;
    int cameraFov=0;
    int weaponFov=0;
    bool playerEsp=false,oreEsp=false,animalEsp=false,objectEsp=false;
    bool ignoreTeams=true;
    int crateMask=15;
    bool autoHeal=false;
    int healThreshold=50;
    bool customSky=false;
    int skyR=110,skyG=160,skyB=220;
    bool playerChams=false,weaponChams=false;
    int chamR=255,chamG=70,chamB=120;
    int weaponR=70,weaponG=220,weaponB=230,weaponAlpha=75;
    bool hitSound=false;
    int hitVolume=100;
    bool autoFarmFeature=false;
    int farmKind=1;
};
struct FreecamInput {bool enabled=false;int movement=0;float yaw=0,pitch=0;int speed=12;};
struct Visual {
    bool fov=true,boxes=true,skeleton=true,arrows=true,names=true,lines=false,distance=true,hp=true,weapon=true;
    int thickness=2,color=0;
    float density=1,textScale=1;
};
struct RenderState {Config config;Visual visual;Frame frame;bool enabled=false;};
// No pointers to IL2CPP objects leave the Unity thread. ESP is rendered in C++.
class State {
    std::mutex mutex;
    Config config;
    Visual visual;
    Frame frame;
    Hud hud;
    bool enabled=false,menu=false;
    Point shotPoint{};
    uint64_t shotSampled=0;
    bool shotValid=false;
    bool freecamEnabled=false;
    bool freecamAvailable=false;
    bool autoFarmAvailable=false;
    bool autoFarmRunning=false;
    bool soundReady=false;
    int pendingHits=0;
    int freecamMovement=0;
    float freecamYaw=0,freecamPitch=0;
    std::string renderer="ESP: waiting for Android overlay frame";
public:
    void configure(const int* v) {
        std::lock_guard<std::mutex> lock(mutex);
        config={};
        config.customCrosshair=v[53]!=0;
        config.aim=v[1]!=0;config.fov=std::clamp(v[2],20,1200);
        config.visible=v[3]!=0;config.smooth=std::clamp(v[4],1,20);
        config.maxDistance=std::clamp(v[5],10,1000);
        config.espDistance=300;
        config.espSleepers=v[28]!=0;config.freecamSpeed=std::clamp(v[29],2,50);
        config.cameraFov=std::clamp(v[11],0,120);
        config.weaponFov=std::clamp(v[10],0,120);
        config.playerEsp=v[0]!=0;config.oreEsp=v[25]!=0;config.animalEsp=v[26]!=0;config.objectEsp=v[27]!=0;
        config.esp=config.playerEsp||config.oreEsp||config.animalEsp||config.objectEsp;
        config.ignoreTeams=v[9]!=0;
        config.crateMask=(v[30]?1:0)|(v[31]?2:0)|(v[32]?4:0)|(v[33]?8:0);
        config.autoHeal=v[34]!=0;config.healThreshold=std::clamp(v[35],1,99);
        config.customSky=v[36]!=0;
        config.skyR=std::clamp(v[37],0,255);config.skyG=std::clamp(v[38],0,255);config.skyB=std::clamp(v[39],0,255);
        config.playerChams=v[40]!=0;config.chamR=std::clamp(v[41],0,255);
        config.chamG=std::clamp(v[42],0,255);config.chamB=std::clamp(v[43],0,255);
        config.weaponChams=v[44]!=0;config.weaponR=std::clamp(v[45],0,255);
        config.weaponG=std::clamp(v[46],0,255);config.weaponB=std::clamp(v[47],0,255);
        config.weaponAlpha=std::clamp(v[48],1,99);
        config.hitSound=v[49]!=0;config.hitVolume=std::clamp(v[50],50,200);
        config.autoFarmFeature=v[51]!=0;config.farmKind=std::clamp(v[52],1,4);
        if(!config.autoFarmFeature)autoFarmRunning=false;
        if(!config.esp)frame={};
        visual={v[12]!=0,v[13]!=0,v[14]!=0,v[15]!=0,v[16]!=0,v[17]!=0,v[18]!=0,v[19]!=0,v[20]!=0,
            std::clamp(v[21],1,5),std::clamp(v[22],0,2),std::clamp(v[23],500,6000)/1000.f,std::clamp(v[24],500,6000)/1000.f};
    }
    Config read() {
        std::lock_guard<std::mutex> lock(mutex);Config copy=config;
        if(!enabled){copy.esp=copy.aim=copy.noSpread=copy.noRecoil=false;
            copy.playerEsp=copy.oreEsp=copy.animalEsp=copy.objectEsp=false;
            copy.silentAim=copy.magicBullets=copy.infiniteAmmo=false;copy.autoHeal=copy.customSky=false;
            copy.customCrosshair=false;copy.playerChams=copy.weaponChams=false;copy.cameraFov=copy.weaponFov=0;copy.autoFarmFeature=false;}
        if(menu||freecamEnabled||autoFarmRunning)copy.aim=copy.silentAim=copy.magicBullets=false;
        return copy;
    }
    Visual readVisual() {std::lock_guard<std::mutex> lock(mutex);return visual;}
    void soundAvailable(bool value){std::lock_guard<std::mutex> lock(mutex);soundReady=value;}
    bool onHeadshot(){std::lock_guard<std::mutex> lock(mutex);
        if(!enabled||!soundReady||!config.hitSound)return false;
        pendingHits=std::min(pendingHits+1,6);return true;}
    int consumeHits(){std::lock_guard<std::mutex> lock(mutex);int result=pendingHits;pendingHits=0;return result;}
    int hitVolume(){std::lock_guard<std::mutex> lock(mutex);return config.hitVolume;}
    void freecamAvailableSet(bool value) {std::lock_guard<std::mutex> lock(mutex);freecamAvailable=value;}
    bool isFreecam() {std::lock_guard<std::mutex> lock(mutex);return freecamEnabled&&enabled;}
    void autoFarmAvailableSet(bool value){std::lock_guard<std::mutex> lock(mutex);autoFarmAvailable=value;}
    bool autoFarm(bool value){std::lock_guard<std::mutex> lock(mutex);
        autoFarmRunning=value&&enabled&&autoFarmAvailable&&config.autoFarmFeature;
        if(autoFarmRunning)freecamEnabled=false;return autoFarmRunning;}
    bool isAutoFarm(){std::lock_guard<std::mutex> lock(mutex);return autoFarmRunning&&enabled;}
    bool freecam(bool on,int movement,float yaw,float pitch) {
        std::lock_guard<std::mutex> lock(mutex);
        freecamEnabled=on&&enabled&&freecamAvailable;
        if(freecamEnabled)autoFarmRunning=false;
        freecamMovement=freecamEnabled?(movement&63):0;
        if(freecamEnabled){freecamYaw=std::clamp(freecamYaw+yaw,-360.f,360.f);
            freecamPitch=std::clamp(freecamPitch+pitch,-360.f,360.f);}
        else freecamYaw=freecamPitch=0;
        return freecamEnabled;
    }
    FreecamInput freecamInput() {std::lock_guard<std::mutex> lock(mutex);
        FreecamInput result{freecamEnabled,freecamMovement,freecamYaw,freecamPitch,config.freecamSpeed};
        freecamYaw=freecamPitch=0;return result;
    }
    RenderState renderState() {
        std::lock_guard<std::mutex> lock(mutex);
        RenderState result;result.config=config;result.visual=visual;result.enabled=enabled;
        result.frame.width=frame.width;result.frame.height=frame.height;result.frame.sampled=frame.sampled;
        if(enabled&&config.esp){size_t n=std::min<size_t>(frame.targets.size(),160);
            result.frame.targets.assign(frame.targets.begin(),frame.targets.begin()+n);}
        return result;
    }
    void active(bool value) {std::lock_guard<std::mutex> lock(mutex);enabled=value;if(!value){frame={};shotValid=false;freecamEnabled=false;freecamMovement=0;pendingHits=0;autoFarmRunning=false;}}
    void menuOpen(bool value) {std::lock_guard<std::mutex> lock(mutex);menu=value;if(value)shotValid=false;}
    void publishShot(Point point,uint64_t sampled) {std::lock_guard<std::mutex> lock(mutex);shotPoint=point;shotSampled=sampled;shotValid=true;}
    bool shot(Point& point,uint64_t now) {std::lock_guard<std::mutex> lock(mutex);
        if(!enabled||menu||!shotValid||now<shotSampled||now-shotSampled>150)return false;
        point=shotPoint;return true;
    }
    void clearShot() {std::lock_guard<std::mutex> lock(mutex);shotValid=false;}
    void publish(Frame value) {std::lock_guard<std::mutex> lock(mutex);if(enabled)frame=std::move(value);}
    void publishHud(Hud value) {std::lock_guard<std::mutex> lock(mutex);hud=value;}
    Hud readHud() {std::lock_guard<std::mutex> lock(mutex);
        if(!hud.sampled||nowMs()-hud.sampled>1500)return {};
        return hud;
    }
    void rendererStatus(std::string value) {std::lock_guard<std::mutex> lock(mutex);renderer=std::move(value);}
    std::string features="runtime pending world entry";
    bool crosshairBound=false;
    void crosshairAvailableSet(bool on){std::lock_guard<std::mutex> lock(mutex);crosshairBound=on;}
    bool crosshairAvailable(){std::lock_guard<std::mutex> lock(mutex);return crosshairBound&&enabled&&config.customCrosshair;}
    void featureStatus(std::string value) {std::lock_guard<std::mutex> lock(mutex);features=std::move(value);}
    std::string status() {std::lock_guard<std::mutex> lock(mutex);return renderer+"; "+features+"; targets="+std::to_string(frame.targets.size());}
};
inline State state;
bool installUi();
bool installRenderer();
}
