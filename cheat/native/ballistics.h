#pragma once
#include <algorithm>
#include <cmath>
namespace ballistic {
struct V {float x=0,y=0,z=0;};
inline V add(V a,V b){return {a.x+b.x,a.y+b.y,a.z+b.z};}
inline V mul(V a,float b){return {a.x*b,a.y*b,a.z*b};}
inline float norm(V a){return std::sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}
inline bool finite(V a){return std::isfinite(a.x)&&std::isfinite(a.y)&&std::isfinite(a.z);}
// Air branch of Oxide.Utils.Combat.BallisticIntegrator.Step (12034):
// dt=1/32, drag clamp, gravity before drag, trapezoidal displacement AND velocity.
// The engine stores the mean velocity as the next state's velocity.
inline void step(V& position,V& velocity,V gravity,float drag,float dt){
    V next=mul(add(velocity,mul(gravity,dt)),std::clamp(1.f-drag*dt,0.f,1.f));
    velocity=mul(add(velocity,next),.5f);position=add(position,mul(velocity,dt));
}
struct Response {float a=0,b=0;};
inline Response response(float t,float drag){
    float va=1,vb=0;Response r;
    for(float elapsed=0;elapsed<t;){
        float dt=std::min(1.f/32,t-elapsed);if(dt<1e-6f)break;
        float d=std::clamp(1.f-drag*dt,0.f,1.f);
        va=.5f*(va+va*d);vb=.5f*(vb+(vb+dt)*d);
        r.a+=va*dt;r.b+=vb*dt;elapsed+=dt;
    }
    return r;
}
// Earliest reachable constant-velocity intercept, max eight seconds.
// Water transitions, collisions and future vehicle maneuvers are not predicted.
inline bool intercept(V delta,V targetVelocity,V gravity,float drag,float speed,V& launch,float& time){
    if(!finite(delta)||!finite(targetVelocity)||!finite(gravity)||!std::isfinite(drag)||drag<0||drag>100||!std::isfinite(speed)||speed<1||speed>10000)return false;
    auto required=[&](float t){auto r=response(t,drag);return mul(add(add(delta,mul(targetVelocity,t)),mul(gravity,-r.b)),1.f/std::max(1e-6f,r.a));};
    float previous=1e-4f,a=0,b=0,va=1,vb=0;
    const float dt=1.f/32,d=std::clamp(1.f-drag*dt,0.f,1.f);
    for(int i=1;i<=256;i++){
        va=.5f*(va+va*d);vb=.5f*(vb+(vb+dt)*d);a+=va*dt;b+=vb*dt;
        float t=i/32.f;V v=mul(add(add(delta,mul(targetVelocity,t)),mul(gravity,-b)),1.f/std::max(1e-6f,a));
        if(norm(v)<=speed){
            float low=previous,high=t;
            for(int j=0;j<24;j++){float mid=(low+high)*.5f;if(norm(required(mid))>speed)low=mid;else high=mid;}
            time=high;launch=required(time);return finite(launch);
        }
        previous=t;
    }
    return false;
}
}
