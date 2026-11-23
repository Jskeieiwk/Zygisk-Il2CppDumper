#include "../native/ballistics.h"
#include <cassert>
#include <limits>
using namespace ballistic;
static void scenario(V delta,V motion,V gravity,float drag,float speed){
 V launch;float t=0;assert(intercept(delta,motion,gravity,drag,speed,launch,t));
 assert(std::abs(norm(launch)-speed)<.1f);
 V pos{},vel=launch;
 for(float elapsed=0;elapsed<t;){float dt=std::min(1.f/32,t-elapsed);if(dt<1e-6f)break;step(pos,vel,gravity,drag,dt);elapsed+=dt;}
 V target=add(delta,mul(motion,t));assert(norm(add(pos,mul(target,-1)))<.02f);
}
int main(){
 scenario({0,0,100},{0,0,0},{0,0,0},0,100);
 scenario({0,0,250},{25,0,0},{0,-9.81f,0},.08f,300);
 scenario({20,60,200},{-15,8,30},{0,-9.81f,0},.1f,300);
 scenario({0,0,60},{0,0,-10},{0,-9.81f,0},0,90);
 V analytic;float at=0;
 assert(intercept({0,0,100},{0,0,0},{0,0,0},0,100,analytic,at));assert(std::abs(at-1)<1e-4f);
 assert(intercept({0,0,100},{10,0,0},{0,0,0},0,100,analytic,at));assert(std::abs(at-100/std::sqrt(9900.f))<1e-4f);
 V pos{},vel{};for(int i=0;i<32;i++)step(pos,vel,{0,-10,0},0,1.f/32);
 assert(std::abs(vel.y+5)<1e-5f);assert(std::abs(pos.y+2.578125f)<1e-5f);
 V v;float t;assert(!intercept({0,0,100},{0,0,200},{0,0,0},0,100,v,t));
 assert(!intercept({0,0,100},{},{},0,0,v,t));
 assert(!intercept({std::numeric_limits<float>::quiet_NaN(),0,0},{},{},0,100,v,t));
}
