#include "../native/collision.h"
#include <cassert>
#include <cstdio>
int main(){
 const char* path="/tmp/oxide-collision-fixture.tri";
 {std::ofstream f(path,std::ios::binary);f.write("OCCTRI1\0",8);uint32_t count=1;f.write(reinterpret_cast<char*>(&count),4);collision::Triangle t{{-1,-1,0},{1,-1,0},{0,1,0}};f.write(reinterpret_cast<char*>(&t),sizeof(t));}
 collision::Scene scene;assert(scene.append(path));assert(scene.count()==1);scene.compile();
 assert(scene.blocked({0,0,-1},{0,0,1}));assert(scene.blocked({0,0,1},{0,0,-1}));
 assert(!scene.blocked({2,2,-1},{2,2,1}));assert(!scene.blocked({0,0,-2},{0,0,-1}));
 assert(!scene.blocked({0,0,0},{0,0,1}));assert(!scene.blocked({0,0,-1},{0,0,0}));
 assert(!scene.blocked({0,0,-1},{0,0,-1}));std::remove(path);
}
