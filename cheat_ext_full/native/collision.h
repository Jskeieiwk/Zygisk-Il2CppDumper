#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <limits>
#include <numeric>
#include <vector>
namespace collision {
struct V {float x,y,z;float at(int axis)const{return axis==0?x:axis==1?y:z;}};
inline V sub(V a,V b){return {a.x-b.x,a.y-b.y,a.z-b.z};}
inline V cross(V a,V b){return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
inline float dot(V a,V b){return a.x*b.x+a.y*b.y+a.z*b.z;}
inline bool finite(V a){return std::isfinite(a.x)&&std::isfinite(a.y)&&std::isfinite(a.z);}
struct Triangle {V a,b,c;};
struct Bounds {V lo{INFINITY,INFINITY,INFINITY},hi{-INFINITY,-INFINITY,-INFINITY};
 void add(V p){lo={std::min(lo.x,p.x),std::min(lo.y,p.y),std::min(lo.z,p.z)};hi={std::max(hi.x,p.x),std::max(hi.y,p.y),std::max(hi.z,p.z)};}
 bool hit(V origin,V direction,float start,float end)const{
  for(int axis=0;axis<3;axis++){float d=direction.at(axis),o=origin.at(axis);if(std::abs(d)<1e-9f){if(o<lo.at(axis)||o>hi.at(axis))return false;continue;}float a=(lo.at(axis)-o)/d,b=(hi.at(axis)-o)/d;if(a>b)std::swap(a,b);start=std::max(start,a);end=std::min(end,b);if(start>end)return false;}return true;
 }
};
class Scene {
 struct Node {Bounds bounds;uint32_t first=0,count=0,left=0,right=0;};
 std::vector<Triangle> triangles;std::vector<Node> nodes;
 uint32_t build(uint32_t first,uint32_t count){
  uint32_t id=nodes.size();nodes.emplace_back();Bounds bounds,centers;
  for(uint32_t i=first;i<first+count;i++){const auto& t=triangles[i];bounds.add(t.a);bounds.add(t.b);bounds.add(t.c);centers.add({(t.a.x+t.b.x+t.c.x)/3,(t.a.y+t.b.y+t.c.y)/3,(t.a.z+t.b.z+t.c.z)/3});}
  nodes[id].bounds=bounds;if(count<=8){nodes[id].first=first;nodes[id].count=count;return id;}
  V extent=sub(centers.hi,centers.lo);int axis=extent.x>extent.y?0:1;if(extent.z>extent.at(axis))axis=2;
  uint32_t mid=first+count/2;std::nth_element(triangles.begin()+first,triangles.begin()+mid,triangles.begin()+first+count,[axis](const Triangle& a,const Triangle& b){return a.a.at(axis)+a.b.at(axis)+a.c.at(axis)<b.a.at(axis)+b.b.at(axis)+b.c.at(axis);});
  uint32_t left=build(first,mid-first),right=build(mid,first+count-mid);nodes[id].left=left;nodes[id].right=right;return id;
 }
 static bool hitTriangle(const Triangle& t,V origin,V direction,float low,float high){
  V e1=sub(t.b,t.a),e2=sub(t.c,t.a),p=cross(direction,e2);float det=dot(e1,p);if(std::abs(det)<1e-8f)return false;
  float inv=1/det;V v=sub(origin,t.a);float u=dot(v,p)*inv;if(u<0||u>1)return false;V q=cross(v,e1);float w=dot(direction,q)*inv;if(w<0||u+w>1)return false;float at=dot(e2,q)*inv;return at>=low&&at<=high;
 }
 bool query(uint32_t id,V origin,V direction,float low,float high)const{
  const Node& n=nodes[id];if(!n.bounds.hit(origin,direction,low,high))return false;
  if(n.count){for(uint32_t i=n.first;i<n.first+n.count;i++)if(hitTriangle(triangles[i],origin,direction,low,high))return true;return false;}
  return query(n.left,origin,direction,low,high)||query(n.right,origin,direction,low,high);
 }
public:
 bool append(const char* path){
  std::ifstream input(path,std::ios::binary);char magic[8]{};uint32_t count=0;input.read(magic,8);input.read(reinterpret_cast<char*>(&count),4);
  const std::array<char,8> expected={'O','C','C','T','R','I','1',0};if(!input||!std::equal(expected.begin(),expected.end(),magic)||count>4000000||triangles.size()+count>4000000)return false;
  std::vector<Triangle> incoming(count);input.read(reinterpret_cast<char*>(incoming.data()),count*sizeof(Triangle));if(!input||input.peek()!=std::char_traits<char>::eof())return false;
  for(const auto& t:incoming)if(!finite(t.a)||!finite(t.b)||!finite(t.c))return false;
  nodes.clear();triangles.insert(triangles.end(),incoming.begin(),incoming.end());return true;
 }
 void compile(){nodes.clear();if(!triangles.empty())build(0,triangles.size());}
 size_t count()const{return triangles.size();}
 // Returns obstruction only. A clear result is NOT proof of full visibility:
 // coverage of terrain alone excludes buildings, doors and dynamic colliders.
 bool blocked(V origin,V target,float originMargin=.05f,float targetMargin=.05f)const{
  if(nodes.empty()||!finite(origin)||!finite(target)||originMargin<0||targetMargin<0)return false;
  V direction=sub(target,origin);float length=std::sqrt(dot(direction,direction));if(length<=originMargin+targetMargin)return false;
  return query(0,origin,direction,originMargin/length,1-targetMargin/length);
 }
};
}
