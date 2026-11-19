// The per-frame math was rewritten to avoid allocations. It must stay bit-for-bit equal to the v0.23 reference.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
// ---- v0.23 reference implementations, verbatim in behavior
function referenceProjector(view,projection,width,height){
  if(!view||!projection||view.length!==16||projection.length!==16||
    !view.every(Number.isFinite)||!projection.every(Number.isFinite)||width<=0||height<=0)return null;
  return point=>{
    const [x,y,z]=point;
    const vx=view[0]*x+view[4]*y+view[8]*z+view[12];
    const vy=view[1]*x+view[5]*y+view[9]*z+view[13];
    const vz=view[2]*x+view[6]*y+view[10]*z+view[14];
    const vw=view[3]*x+view[7]*y+view[11]*z+view[15];
    const cx=projection[0]*vx+projection[4]*vy+projection[8]*vz+projection[12]*vw;
    const cy=projection[1]*vx+projection[5]*vy+projection[9]*vz+projection[13]*vw;
    const cw=projection[3]*vx+projection[7]*vy+projection[11]*vz+projection[15]*vw;
    if(!Number.isFinite(cw)||Math.abs(cw)<1e-6)return null;
    const result=[(cx/cw+1)*width*.5,(cy/cw+1)*height*.5,-vz];
    return result.every(Number.isFinite)?result:null;
  };
}
const referenceMoveBone=(point,anchor,origin)=>{
  if(!point||!anchor||!origin)return point;
  return point.map((value,index)=>value+origin[index]-anchor[index]);
};
function referenceLineBatch(){
  const groups=new Map();
  function add(tint,width,x1,y1,x2,y2,layer=1){
    if(![x1,y1,x2,y2].every(Number.isFinite))return;
    const key=layer+':'+tint+':'+width;
    let group=groups.get(key);
    if(!group){group={tint,width,layer,points:[]};groups.set(key,group);}
    group.points.push(x1,y1,x2,y2);
  }
  function box(tint,width,left,top,right,bottom,layer=1){
    add(tint,width,left,top,right,top,layer);add(tint,width,right,top,right,bottom,layer);
    add(tint,width,right,bottom,left,bottom,layer);add(tint,width,left,bottom,left,top,layer);
  }
  function drain(){const result=[...groups.values()].sort((a,b)=>a.layer-b.layer);groups.clear();return result;}
  return {add,box,drain};
}
// ---- current implementations
const context=vm.createContext({});
for(const name of ['matrix-projection','esp-motion','line-batch'])
  vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replaceAll('export function','function'),context);
vm.runInContext('globalThis.api={createMatrixProjector,moveBone,createLineBatch};',context);
const {createMatrixProjector,moveBone,createLineBatch}=context.api;
// ---- deterministic random inputs
let seed=123456789;const random=()=>(seed=(seed*1664525+1013904223)>>>0)/4294967296;
const pick=values=>values[Math.floor(random()*values.length)];
const number=()=>random()<.04?pick([NaN,Infinity,-Infinity,0,1e-9,-0,1e300]):(random()-.5)*pick([1,10,100,1000]);
const same=(a,b)=>Object.is(a,b)||(a===b);
function sameArray(a,b,label){
  assert.equal(a===null,b===null,label+' null mismatch');
  if(a===null)return;
  assert.equal(a.length,b.length,label+' length');
  for(let i=0;i<a.length;i++)assert(same(a[i],b[i]),label+' value '+i+': '+a[i]+' vs '+b[i]);
}
// matrix projector
for(let round=0;round<400;round++){
  const bad=random()<.08;
  const view=Array.from({length:16},number),projection=Array.from({length:16},number);
  if(!bad){view.forEach((v,i)=>{if(!Number.isFinite(v))view[i]=random();});projection.forEach((v,i)=>{if(!Number.isFinite(v))projection[i]=random();});}
  const width=pick([0,-5,1280,2400,720.5]),height=pick([0,720,1080,540.25]);
  const a=referenceProjector(view,projection,width,height),b=createMatrixProjector(view,projection,width,height);
  assert.equal(a===null,b===null,'projector construction');
  if(!a)continue;
  for(let n=0;n<200;n++){
    const point=[number(),number(),number()];
    sameArray(a(point),b(point),'project');
  }
}
// moveBone
for(let n=0;n<5000;n++){
  const point=random()<.05?null:[number(),number(),number()],anchor=random()<.05?null:[number(),number(),number()],origin=random()<.05?null:[number(),number(),number()];
  const a=referenceMoveBone(point,anchor,origin),b=moveBone(point,anchor,origin);
  if(!point||!anchor||!origin){assert.equal(a,b);continue;}
  sameArray(a,b,'moveBone');
}
// line batch: random interleavings of styles, boxes, layers and bad values
for(let round=0;round<300;round++){
  const a=referenceLineBatch(),b=createLineBatch();
  const styles=Array.from({length:4},()=>[pick([-1,-16777216,0xff72baff|0,123]),pick([1,2,3.6,4])]);
  const steps=Math.floor(random()*80);
  for(let s=0;s<steps;s++){
    const [tint,width]=pick(styles),layer=pick([0,1,1,1,2]);
    if(random()<.3){const l=number(),t=number(),r=number(),bt=number();a.box(tint,width,l,t,r,bt,layer);b.box(tint,width,l,t,r,bt,layer);}
    else{const v=[number(),number(),number(),number()];a.add(tint,width,...v,layer);b.add(tint,width,...v,layer);}
  }
  const ra=a.drain(),rb=b.drain();
  assert.equal(ra.length,rb.length,'group count');
  ra.forEach((group,i)=>{
    assert.equal(group.tint,rb[i].tint);assert.equal(group.width,rb[i].width);assert.equal(group.layer,rb[i].layer);
    sameArray(group.points,rb[i].points,'points');
  });
  // The batch is reusable after drain, with no stale last-group reference.
  const x=[1,2,3,4];a.add(7,2,...x);b.add(7,2,...x);
  const na=a.drain(),nb=b.drain();assert.equal(na.length,nb.length);sameArray(na[0].points,nb[0].points,'after drain');
}
console.log('Projector, moveBone and line batch match the v0.23 reference on random and hostile inputs.');
