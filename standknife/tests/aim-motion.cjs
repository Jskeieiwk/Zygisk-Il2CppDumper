const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const context=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/aim-motion.js','utf8').replaceAll('export function','function')+
  '\nglobalThis.api={springAxis,createAimMotion,targetPoints,activeParts,partRank,bodyFrame,partPoints,aimCandidates,aimBones,hitChance};',context);
const {springAxis,createAimMotion,targetPoints,activeParts,partRank,bodyFrame,partPoints,aimCandidates,aimBones,hitChance}=context.api;
const whole=springAxis(0,30,0,.02,150);
const half=springAxis(0,30,0,.01,150),two=springAxis(half.value,30,half.velocity,.01,150);
assert(Math.abs(whole.value-two.value)<1e-10,'Spring integration must be independent of frame subdivision');
let current=0,speed=0,maximum=0;
for(let i=0;i<180;i++){const step=springAxis(current,30,speed,1/60,150);current=step.value;speed=step.velocity;maximum=Math.max(maximum,current);}
assert(maximum>30&&maximum<34,'Overshoot must cross and then settle on the target');
assert(Math.abs(current-30)<1e-6);
assert(Math.abs(springAxis(179,-179,0,.02,150,true).velocity)<100,'Yaw must use the short path through 180 degrees');
const motion=createAimMotion();
assert(Math.abs(motion.apply([350,0,0],[-10,0,0],.02,150,'pitch',{Overshoot:true},0)[0]+10)<1e-9,'Normalize unsigned Euler pitch before spring integration');
for(let now=0;now<10000;now+=17){
 const value=motion.apply([0,0,0],[0,0,0],.017,100,'enemy',{Jitter:true,'Jitter Strength':.1},now);
 assert(Math.abs(value[0])<=.1000001&&Math.abs(value[1])<=.1000001);
}
const bones=[[1,2,3],null,[2,3,4],[NaN,0,0]];
assert.equal(targetPoints(bones,0,false).length,1);
assert.equal(targetPoints(bones,0,true).length,2,'Multipoints must reject missing and invalid bones');
console.log('Spring convergence, bounded overshoot/jitter, yaw wraparound and multipoint validation passed.');

// Hitbox parts, multipoint percent and hit chance: pure geometry on a standing target (Y up).
const stand=Array(16).fill(null);
stand[0]=[0,1.7,0];stand[1]=[0,1.5,0];stand[2]=[0,1.2,0];stand[3]=[0,.9,0];stand[10]=[.1,.5,0];stand[11]=[.1,.1,0];stand[13]=[-.1,.5,0];stand[14]=[-.1,.1,0];
assert.deepEqual(Array.from(activeParts({})),['head'],'Nothing ticked means the head');
assert.deepEqual(Array.from(activeParts({'Hitbox Head':false,'Hitbox Legs':true})),['legs']);
assert.deepEqual(Array.from(activeParts({'Hitbox All':true,'Hitbox Head':false})),['head','body','legs'],'Hitbox All is the whole body whatever else is ticked');
assert.deepEqual([0,1,2].map(mode=>['head','body','legs'].map(part=>partRank({'Hitbox Priority':mode},part)).join('')),['012','102','000']);
const frame=bodyFrame(stand);
assert(Math.abs(frame.up[1]-1)<1e-9&&Math.abs(Math.abs(frame.lateral[0])-1)<1e-9&&Math.abs(Math.abs(frame.forward[2])-1)<1e-9,'Axes from bones: '+JSON.stringify(frame));
assert(Math.abs(frame.hipHalfWidth-.1)<1e-9);
assert.equal(bodyFrame(Array(16).fill(null)),null);
assert.equal(partPoints(stand,'head',.5,false).length,1,'Without Multipoints only the centre');
const dist=(a,b)=>Math.hypot(a[0]-b[0],a[1]-b[1],a[2]-b[2]);
const small=partPoints(stand,'head',.1,true),large=partPoints(stand,'head',1,true);
assert.equal(small.length,7);assert.equal(large.length,7);
assert.equal(large[0].center,true);
for(let i=1;i<7;i++){
  assert(Math.abs(dist(large[i].point,stand[0])-.6*.2)<1e-9,'Head ring radius at 100% = 0.6 * |head-neck|');
  assert(Math.abs(dist(small[i].point,stand[0])-.6*.2*.1)<1e-9,'The percent scales the ring');
}
const body=partPoints(stand,'body',1,true);
assert.equal(body.length,6);assert.deepEqual(Array.from(body[0].point),[0,1.2,0]);
assert(body.slice(1).every(item=>item.point.every(Number.isFinite)));
assert(partPoints(stand,'legs',1,true).length===8&&partPoints(stand,'legs',1,false).length===2);
// Candidates carry the part rank; the knife only sees the chest; invalid bones never produce a point.
const cand=aimCandidates(stand,{'Hitbox All':true,'Hitbox Priority':0});
assert.deepEqual(Array.from(new Set(cand.map(item=>item.part+item.rank))),['head0','body1','legs2']);
assert.equal(aimCandidates(stand,{},true).length,1);
const broken=stand.slice();broken[1]=[NaN,0,0];
assert.equal(partPoints(broken,'head',1,true).length,7,'A missing neck falls back to a constant head radius');
broken[0]=[NaN,0,0];assert.equal(partPoints(broken,'head',1,true).length,0);
assert.deepEqual(Array.from(aimBones({'Hitbox Head':false,'Hitbox Body':true})),[2]);
assert.deepEqual(Array.from(aimBones({'Hitbox All':true,Multipoints:true})),[0,1,2,3,10,11,13,14]);
assert.deepEqual(Array.from(aimBones({'Hitbox Head':false,'Hitbox Legs':true})),[10,13]);
// Hit chance: share of visible points of the best selected part, 0 when nothing is visible.
assert.equal(hitChance(stand,{},()=>true),100);assert.equal(hitChance(stand,{},()=>false),0);
assert(Math.abs(hitChance(stand,{},point=>point[0]<=.001)-600/7)<1e-9,'One of seven head points covered');
assert.equal(hitChance(stand,{'Hitbox All':true},point=>point[1]<1.0),100,'The best part counts: only the legs visible is a full-chance part');
console.log('Hitbox parts, ranking, multipoint percent scaling and hit chance geometry passed.');
