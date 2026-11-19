const assert=require('node:assert/strict'),vm=require('node:vm'),fs=require('node:fs');
const context=vm.createContext({console,Date,Math,installFireControl:()=>({ensureInstalled(){},reset(){},status:()=>({ready:true,samples:3})}),ptr:value=>new Pointer(value),Memory:{alloc:()=>new Pointer(999)}});
class Pointer {
  constructor(value){this.value=value;}
  add(offset){return new Pointer(this.value+offset);}
  equals(other){return this.value===other.value;}
  isNull(){return this.value===0;}
  readPointer(){return new Pointer(10000);}
}
for(const name of ['engine','auto-stop','aim-motion','wall-rules'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function'),context);
vm.runInContext(fs.readFileSync('assets/aim.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function')+'\nglobalThis.api={aimAngles,angularDistance,smoothAngles,createAim,createWallRules};',context);
const api=context.api;
assert(api.aimAngles([0,0,0],[0,0,10]).every(value=>Math.abs(value)<1e-9));
assert.equal(api.aimAngles([0,0,0],[10,0,0])[1],90);
assert(Math.abs(api.smoothAngles([0,179,0],[0,-179,0],.016,0)[1]+179)<1e-6);
const once=api.smoothAngles([0,0,0],[0,60,0],.02,100);
const twice=api.smoothAngles(api.smoothAngles([0,0,0],[0,60,0],.01,100),[0,60,0],.01,100);
assert(Math.abs(once[1]-twice[1])<1e-9);
let rotated=null,enabled=true,obstructed=0;
const target=new Pointer(2),local=new Pointer(1);
const settings={'Aim assistance':true,'Aim FOV':60,'Aim Range':150,'Aim Smoothing':0,'Aim Team Filter':true,'Aim Visible Only':false,'Aim Bone':0};
const records=new Map([['enemy',{t:Date.now(),team:2,health:100,bonePositions:[[10,0,10]]}]]);
const native=rva=>{
 const functions={
  [0x5452708]:()=>[0,0,0], [0x54519e4]:(_aim,rotation)=>{rotated=rotation},
  [0xa724984]:()=>60,[0xa8261c8]:()=>obstructed,[0xa82b000]:()=>new Pointer(10),[0xa7a4150]:()=>0
 };return functions[rva];
};
const engine=api.createAim({native,settings,records,tracked:new Map([['enemy',{player:target}]]),
 transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>enabled});
engine.step(local,new Pointer(3),1);assert.equal(rotated[1],45);
rotated=null;enabled=false;engine.step(local,new Pointer(3),1);assert.equal(rotated,null);
enabled=true;settings['Aim Visible Only']=true;obstructed=1;
engine.step(local,new Pointer(3),1);assert.equal(rotated,null);
obstructed=0;records.get('enemy').team=1;
engine.step(local,new Pointer(3),1);assert.equal(rotated,null);
console.log('Aim angles, wraparound, smoothing, activation, visibility and team filtering passed.');

let stopped=false;
context.stopTest={update:(_local,value)=>{stopped=value;},reset:()=>{stopped=false;},active:()=>stopped};
vm.runInContext('createAutoStop=()=>stopTest;',context);
settings['Aim assistance']=true;settings['Auto Stop']=true;settings['Aim Visible Only']=false;settings['Aim FOV']=60;enabled=true;obstructed=0;
const stopAim=api.createAim({native,settings,records,tracked:new Map([['enemy',{player:target,local:false}]]),
 transform:object=>object,position:()=>[0,0,0],getHealth:()=>100,active:()=>true});
records.get('enemy').team=2;records.get('enemy').t=Date.now();stopAim.step(local,new Pointer(3),1);
assert.equal(stopAim.needsUpdate(),true);
settings['Aim assistance']=false;stopAim.step(local,new Pointer(3),1);
assert.equal(stopped,false,'Disabling the last aim mode must release Auto Stop');
assert.equal(stopAim.needsUpdate(),false);
let idleHealthCalls=0;
const idleAim=api.createAim({native,settings,records:new Map(),tracked:new Map(),
 transform:object=>object,position:()=>[0,0,0],getHealth:()=>{idleHealthCalls++;return 100;},active:()=>true});
idleAim.step(local,new Pointer(3),1);
assert.equal(idleHealthCalls,0,'An empty market/lobby must skip aim target and physics work');
console.log('Aim/Auto Stop shutdown integration passed.');

// Walls: slabs across the camera->target line. Linecast behaves like Unity's: it reports the first face it enters and never a
// face of a slab its start point is inside. Nothing is measured in centimetres any more: a slab is passable (a breakable object or
// a player) or it is not, and the answer comes from the wall rules. Automatic fire needs a clear line unless Wallshot is on.
{
  let captured=null,slabs=[];
  const results=new Map();
  context.installFireControl=fireContext=>{captured=fireContext;return {ensureInstalled(){},reset(){},status:()=>({ready:true,samples:3})};};
  function cast(from,to,buffer){
    const dz=to[2]-from[2];let best=null;
    let id=0;
    slabs.forEach(([z0,z1],index)=>{
      if(from[2]>z0&&from[2]<z1)return;
      const face=dz>0?z0:z1;const t=(face-from[2])/dz;
      if(t>=0&&t<=1&&(best===null||t<best)){best=t;id=100+index;}
    });
    if(best===null){results.delete(String(buffer));return 0;}
    results.set(String(buffer),{point:from.map((v,i)=>v+(to[i]-v)*best),id});return 1;
  }
  // Slab 100+index belongs to the other player when its entry says so (third element 'player'); the rules answer for the rest.
  const wallNative=rva=>rva===0xa82b12c?buffer=>results.get(String(buffer)).point:rva===0xa82b000?buffer=>new Pointer(results.get(String(buffer)).id):
    rva===0xa8261c8?(from,to,buffer)=>cast(from,to,buffer):
    rva===0xa7a4150?(obstacle,root)=>{const slab=slabs[obstacle.value-100];return !!slab&&slab[2]==='player'&&root.value===9;}:native(rva);
  const verdicts=new Map();
  const wallRules={classify:collider=>{const slab=slabs[collider.value-100];return slab?verdicts.has(slab[2])?verdicts.get(slab[2]):null:null;},reset(){}};
  verdicts.set('breakable',true);verdicts.set('solid',false);
  const forceSettings={'Aim assistance':false,'Force Shot':true,'Silent Aim':false,Trigger:false,'Aim Visible Only':false,'Autowall (Aim)':false,Autowall:false,
    Wallshot:false,'Aim FOV':60,'Aim Range':150,'Aim Smoothing':0,'Aim Team Filter':true};
  const enemy=new Map([['enemy',{t:Date.now(),team:2,health:100,bonePositions:[[0,0,10]]}]]);
  const bystander=new Pointer(9);
  const tracked=new Map([['enemy',{player:new Pointer(2)}],['other',{player:bystander}]]);
  const wallContext={native:wallNative,wallRules,settings:forceSettings,records:enemy,tracked,
    transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>true};
  const engine=api.createAim(wallContext);
  // Each decision happens 150 ms later than the last one: a player found hidden is not re-checked for 100 ms (see HIDDEN_RECHECK_MS).
  let clock=1e6;context.Date={now:()=>clock};
  const decision=()=>{clock+=150;enemy.get('enemy').t=clock;engine.step(new Pointer(1),new Pointer(3),1);return captured.getAim();};
  slabs=[[4,4.2,'solid']];
  let state=decision();
  assert(state.selected,'Aim Visible Only=false still selects a target behind a wall');
  assert.equal(state.clear,false,'Without Wallshot a target behind a wall must not be fired at');
  slabs=[];state=decision();
  assert.equal(state.clear,true);assert.equal(state.selected.reach.direct,true,'A visible target is recorded as direct');
  // Wallshot is a plain switch: it passes breakable obstacles and refuses solid or unknown ones, whatever their thickness.
  forceSettings.Wallshot=true;
  slabs=[[4,4.2,'solid']];state=decision();assert.equal(state.clear,false,'A solid wall stops the shot even with Wallshot');
  assert.equal(state.selected.reach.blocked,'thick','A 20 cm wall is over the built-in 15 cm budget');
  slabs=[[4,4.2,'breakable']];state=decision();
  assert.equal(state.clear,true,'A breakable obstacle can be shot through');assert.equal(state.selected.reach.walls,1);
  slabs=[[4,6,'breakable']];state=decision();assert.equal(state.clear,true,'Thickness plays no role: a 2 m breakable obstacle is passable too');
  slabs=[[4,4.2,'breakable'],[6,6.25,'breakable']];state=decision();assert.equal(state.clear,true);assert.equal(state.selected.reach.walls,2);
  slabs=[[4,4.2,'breakable'],[6,6.25,'solid']];state=decision();assert.equal(state.clear,false,'One solid obstacle on the way is enough to refuse');
  slabs=[[4,4.2,'mystery']];state=decision();assert.equal(state.clear,false,'An unclassified obstacle counts as solid');
  assert.equal(state.selected.reach.blocked,'thick','An unclassified 20 cm obstacle is over the budget too');
  slabs=[[3,3.1,'breakable'],[4,4.1,'breakable'],[5,5.1,'breakable'],[6,6.1,'breakable'],[7,7.1,'breakable']];
  state=decision();assert.equal(state.clear,false,'The obstacle loop is bounded');
  slabs=[[4,4.2,'player']];state=decision();assert.equal(state.clear,true,'Another player is passable without asking the wall rules');
  slabs=[[4,4.1,'breakable'],[4.3,4.45,'breakable']];state=decision();assert.equal(state.clear,true,'Two separate breakable objects are fine');
  // Autowall is one button; any obstacle that is neither a player nor a known breakable counts as passable when it is at most 15 cm thick (built in).
  slabs=[[4,4.1,'solid']];state=decision();assert.equal(state.clear,true,'A 10 cm wall is within the built-in 15 cm');assert.equal(state.selected.reach.walls,1);
  slabs=[[4,4.3,'solid']];state=decision();assert.equal(state.clear,false,'A 30 cm wall is thicker than the budget');assert.equal(state.selected.reach.blocked,'thick');
  slabs=[[4,4.1,'solid'],[6,6.1,'solid']];state=decision();assert.equal(state.clear,false,'Two 10 cm walls add up to more than 15 cm');
  slabs=[[4,4.1,'mystery']];state=decision();assert.equal(state.clear,true,'An unclassified thin obstacle counts too');
  slabs=[[4,4.1,'solid'],[4.12,4.14,'solid']];state=decision();assert.equal(state.clear,false,'The exit must belong to the same wall: a second wall right behind it is not part of its thickness');
  slabs=[[4,4.1,'solid'],[6,6.05,'breakable']];state=decision();assert.equal(state.clear,true,'A breakable object does not use the thickness budget');
  wallContext.thinWall=0;   // test switch: rules only
  slabs=[[4,4.1,'solid']];state=decision();assert.equal(state.clear,false,'Without the thin-wall budget only players and breakable objects pass');
  slabs=[[4,4.1,'breakable']];state=decision();assert.equal(state.clear,true,'and breakable objects still pass');
  // What autowall let through is counted for the perf line: players, known breakable objects and thin walls separately.
  wallContext.thinWall=undefined;slabs=[[4,4.1,'solid']];decision();slabs=[[4,4.1,'breakable']];decision();slabs=[[4,4.2,'player']];decision();slabs=[[4,4.5,'solid']];decision();
  {const taken=engine.takeCost();
   assert(taken.passThin>=1&&taken.passBreakable>=1&&taken.passPlayer>=1&&taken.blockedThick>=1,'takeCost() separates thin walls, breakables, players and thick walls: '+JSON.stringify(taken));
   assert.equal(engine.takeCost().passThin,0,'and zeroes them');}
  slabs=[];
  // Silent Aim is gated the same way.
  forceSettings['Force Shot']=false;forceSettings['Silent Aim']=true;forceSettings.Wallshot=false;slabs=[[4,4.2,'breakable']];
  state=decision();assert.equal(state.clear,false);
  forceSettings.Wallshot=true;state=decision();assert.equal(state.clear,true);
  // The aim assist follows through breakable obstacles (Autowall (Aim)) and drops a target behind a solid one.
  forceSettings['Silent Aim']=false;forceSettings.Wallshot=false;forceSettings['Aim assistance']=true;forceSettings['Aim Visible Only']=true;forceSettings['Autowall (Aim)']=true;
  slabs=[[4,4.9,'solid']];state=decision();
  assert.equal(state.selected,null,'A target behind a solid wall is not selected');
  slabs=[[4,4.9,'breakable']];state=decision();assert(state.selected,'A target behind a breakable obstacle can be aimed at');
  slabs=[];
  // Rules that are not filled in yet (null) answer null for every obstacle: Autowall then equals the direct line.
  const unsetLog=[];
  const unset=api.createWallRules({engine:{},config:{build:'test',breakableType:null,getComponentInParent:null},log:m=>unsetLog.push(m)});
  assert.equal(unset.ready(),false);assert.equal(unset.classify(new Pointer(1)),null);assert.equal(unset.classify(new Pointer(1)),null);
  assert.equal(unsetLog.length,1,'The unset warning is logged once');
  // Filled in: the classifier asks the game for the component above the collider (GetComponentInParent), caches the answer and
  // logs the first thresholds. A failing type lookup or a throwing call answers null instead of raising.
  const floats=new Map([[0x4c,2.5],[0x48,1.25]]);
  class Component {constructor(v){this.value=v;}isNull(){return !this.value;}add(o){return {readFloat:()=>floats.get(o)};}toString(){return 'c'+this.value;}}
  let calls=0;const ruleLog=[];
  const rules=api.createWallRules({engine:{type:name=>({name}),method:(rva,ret,args)=>{assert.equal(rva,0xa77e4e0);assert.deepEqual(Array.from(args),['pointer','pointer','bool','pointer']);
      return (collider,type,inactive)=>{calls++;assert.equal(type.name,'T, A');assert.equal(inactive,1);return new Component(collider.value===7?55:0);};}},
    config:{build:'test',breakableType:'T, A',getComponentInParent:0xa77e4e0,minBreakOffset:0x4c,minCoeffOffset:0x48},log:m=>ruleLog.push(m)});
  const c7=new Pointer(7),c8=new Pointer(8);c7.toString=()=>'7';c8.toString=()=>'8';
  assert.equal(rules.ready(),true);assert.equal(rules.classify(c7),true);assert.equal(rules.classify(c8),false);
  assert.equal(rules.classify(c7),true);assert.equal(calls,2,'Verdicts are cached per collider');
  assert.deepEqual(ruleLog,['CLOUD:wall-rules breakable minBreak=2.500 minCoeff=1.250']);
  const failing=api.createWallRules({engine:{type:()=>{throw Error('Missing managed type T');},method(){}},config:{build:'t',breakableType:'T',getComponentInParent:1},log:()=>{}});
  assert.equal(failing.classify(c7),null,'A missing type answers unknown');
}
context.Date=Date;
console.log('Autowall without thickness, Wallshot gating and aim-assist wall rule passed.');

// Hitboxes: which point of a player the aim picks, what Multipoints and Hit Chance add.
{
  let captured=null,blocked=()=>false;
  context.installFireControl=fireContext=>{captured=fireContext;return {ensureInstalled(){},reset(){},status:()=>({ready:true,samples:3})};};
  const results=new Map();
  const hitNative=rva=>rva===0xa8261c8?(from,to,buffer)=>{if(!blocked(to)){return 0;}results.set(String(buffer),1);return 1;}:
    rva===0xa82b000?()=>new Pointer(500):rva===0xa82b12c?()=>[0,0,5]:rva===0xa7a4150?()=>false:native(rva);
  const bones=Array(16).fill(null);
  bones[0]=[0,1.7,10];bones[1]=[0,1.5,10];bones[2]=[0,1.2,10];bones[3]=[0,.9,10];
  bones[10]=[.1,.5,10];bones[11]=[.1,.1,10];bones[13]=[-.1,.5,10];bones[14]=[-.1,.1,10];
  const settings={'Aim assistance':true,'Aim FOV':90,'Aim Range':150,'Aim Smoothing':0,'Aim Team Filter':true,'Aim Visible Only':false,
    'Hitbox Head':true,'Hitbox Body':true,'Hitbox Legs':true,'Multipoint Scale':50,'Hitchance Percent':60};
  const records=new Map([['enemy',{t:Date.now(),team:2,health:100,bonePositions:bones}]]);
  const engine=api.createAim({native:hitNative,wallRules:{classify:()=>false,reset(){}},settings,records,tracked:new Map([['enemy',{player:new Pointer(2)}]]),
    transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>true});
  // Every choice is 150 ms after the previous one, so the 100 ms hidden-player memory never answers for a changed scene.
  let tick=2e6;context.Date={now:()=>tick};
  const choose=()=>{tick+=150;records.get('enemy').t=tick;engine.step(new Pointer(1),new Pointer(3),1);return captured.getAim().selected;};
  // The legs are the points closest to a crosshair at the horizon, which used to win whenever the whole body was ticked.
  settings['Hitbox Priority']=2;assert.equal(choose().part,'legs','Without a ranking the nearest point (the legs) wins');
  settings['Hitbox Priority']=0;assert.equal(choose().part,'head','Head first when it is in range');
  settings['Hitbox Priority']=1;assert.equal(choose().part,'body','Body first on request');
  settings['Hitbox All']=true;settings['Hitbox Head']=false;settings['Hitbox Body']=false;settings['Hitbox Legs']=false;
  settings['Hitbox Priority']=1;assert.equal(choose().part,'body','Hitbox All selects every part by itself');
  // A part is skipped only when none of its points is visible; the legs are the last resort, never the first choice.
  settings['Aim Visible Only']=true;settings['Hitbox Priority']=0;
  blocked=to=>to[1]>1.5;assert.equal(choose().part,'body','Head hidden: the body is next');
  blocked=to=>to[1]>.6;assert.equal(choose().part,'legs','Only the legs visible: the legs are used');
  blocked=()=>true;assert.equal(choose(),null,'Nothing visible: no target');
  blocked=()=>false;
  // Multipoint percent: the extra points follow the scale, and a visible edge point beats a covered centre.
  settings['Hitbox All']=false;settings['Hitbox Head']=true;settings.Multipoints=true;settings['Hitbox Priority']=0;
  settings['Multipoint Scale']=100;blocked=to=>Math.abs(to[0])<1e-9&&Math.abs(to[1]-1.7)<1e-9;
  const edge=choose();assert(edge&&edge.part==='head','A covered head centre falls back to an edge point of the head');
  assert(Math.hypot(edge.target[0],edge.target[1]-1.7,edge.target[2]-10)>0.01,'The chosen point is off-centre');
  blocked=()=>false;
  // Hit chance gates automatic fire only: the share of visible points of the target's full hitbox must reach the percentage.
  Object.assign(settings,{'Aim assistance':false,'Force Shot':true,Hitchance:true,'Aim Visible Only':false,'Hitbox All':false,'Hitbox Head':true,'Hitbox Body':false,'Hitbox Legs':false});
  settings['Hitchance Percent']=60;choose();assert.equal(captured.getAim().clear,true,'A fully visible target passes the hit chance');
  assert.equal(captured.getAim().hitchance.aim,100);
  blocked=to=>to[0]>.001;choose();                       // one of the seven head points (one side) is covered
  assert(Math.abs(captured.getAim().hitchance.aim-600/7)<1e-9,'6 of 7 head points are visible: '+captured.getAim().hitchance.aim);
  settings['Hitchance Percent']=90;choose();assert.equal(captured.getAim().clear,false,'85.7% is below a 90% hit chance');
  settings['Hitchance Percent']=80;choose();assert.equal(captured.getAim().clear,true,'85.7% meets an 80% hit chance');
  settings.Hitchance=false;settings['Hitchance Percent']=100;choose();assert.equal(captured.getAim().clear,true,'Hit chance off: no gating');
  // 360 degrees: 'Aim FOV' is a half angle, so 180 covers a target straight behind the camera and 90 does not.
  const behind=Array(16).fill(null);behind[0]=[0,1.7,-10];behind[1]=[0,1.5,-10];behind[2]=[0,1.2,-10];behind[3]=[0,.9,-10];
  records.get('enemy').bonePositions=behind;settings['Hitbox Head']=true;settings['Hitbox Body']=false;settings['Hitbox Legs']=false;
  settings.Multipoints=false;settings['Aim Visible Only']=false;
  settings['Aim FOV']=90;assert.equal(choose(),null,'A target behind the camera is outside a 90 degree half angle');
  settings['Aim FOV']=180;assert(choose(),'Aim FOV 180 (360 degrees) selects a target behind the camera');
}
context.Date=Date;
console.log('Hitbox ranking, hitbox-all, multipoint percent and hit chance gating passed.');

// Hidden-player memory: a player whose every point was blocked is skipped for 100 ms (cheap steps), re-checked afterwards, and
// re-checked at once when the camera or the player moved half a metre. A visible player is checked on every step.
{
  let casts=0,blockedNow=true,time=3e6;context.Date={now:()=>time};
  const nativeCount=rva=>rva===0xa8261c8?()=>{casts++;return blockedNow?1:0;}:rva===0xa82b000?()=>new Pointer(500):rva===0xa7a4150?()=>false:native(rva);
  const bones=Array(16).fill(null);bones[0]=[0,1.7,10];bones[1]=[0,1.5,10];bones[2]=[0,1.2,10];bones[3]=[0,.9,10];
  const memorySettings={'Aim assistance':true,'Aim FOV':180,'Aim Range':150,'Aim Smoothing':0,'Aim Team Filter':true,'Aim Visible Only':true,'Hitbox Head':true,'Hitbox Body':true,'Hitbox Legs':false,Multipoints:true,'Multipoint Scale':50};
  const memoryRecords=new Map([['enemy',{t:time,team:2,health:100,bonePositions:bones}]]);
  let cameraAt=[0,0,0];
  const memoryEngine=api.createAim({native:nativeCount,wallRules:{classify:()=>false,reset(){}},settings:memorySettings,records:memoryRecords,tracked:new Map([['enemy',{player:new Pointer(2)}]]),
    transform:value=>value,position:()=>cameraAt,getHealth:()=>100,active:()=>false});
  const stepAt=ms=>{time+=ms;memoryRecords.get('enemy').t=time;const before=casts;memoryEngine.step(new Pointer(1),new Pointer(3),1);return casts-before;};
  const first=stepAt(16);assert(first>=4,'A hidden player is checked point by point on the first step: '+first);
  assert.equal(stepAt(16),0,'Next step (16 ms): remembered as hidden, no casts');assert.equal(stepAt(16),0);assert.equal(stepAt(16),0);
  assert(stepAt(100)>0,'After 100 ms the player is checked again');
  assert.equal(stepAt(16),0,'and remembered again');
  cameraAt=[1,0,0];assert(stepAt(16)>0,'A camera that moved 1 m invalidates the memory');
  memoryRecords.get('enemy').bonePositions=bones.map(point=>point&&[point[0]+1,point[1],point[2]]);
  assert(stepAt(16)>0,'A player that moved 1 m invalidates the memory');
  // A visible player is never skipped, and being visible removes the memory.
  blockedNow=false;stepAt(200);let visible=stepAt(16);assert(visible>0,'A visible player is checked on every step');
  blockedNow=true;stepAt(200);assert.equal(stepAt(16),0);blockedNow=false;
  assert.equal(stepAt(110)>0,true,'A player who steps into view is found within the 100 ms memory');
  memoryEngine.reset();blockedNow=true;assert(stepAt(16)>0,'reset() clears the memory');
  // Candidates skipped because another player already scores better were never checked: they must not be remembered as hidden.
  {
    let nearBlocked=false;const pair=new Map(),paired=new Map();
    const point=(x)=>{const b=Array(16).fill(null);b[0]=[x,1.7,10];b[1]=[x,1.5,10];b[2]=[x,1.2,10];b[3]=[x,.9,10];return b;};
    pair.set('near',{t:time,team:2,health:100,bonePositions:point(0)});pair.set('far',{t:time,team:2,health:100,bonePositions:point(6)});
    paired.set('near',{player:new Pointer(2)});paired.set('far',{player:new Pointer(3)});
    const pairNative=rva=>rva===0xa8261c8?(from,to)=>(nearBlocked&&to[0]<3?1:0):rva===0xa82b000?()=>new Pointer(500):rva===0xa7a4150?()=>false:native(rva);
    const pairSettings={...memorySettings,Multipoints:false,'Hitbox Body':false};
    const pairEngine=api.createAim({native:pairNative,wallRules:{classify:()=>false,reset(){}},settings:pairSettings,records:pair,tracked:paired,
      transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>false});
    const pairStep=()=>{time+=16;for(const record of pair.values())record.t=time;pairEngine.step(new Pointer(1),new Pointer(3),1);};
    const readTarget=()=>pairEngine.status().target;
    pairStep();assert.equal(readTarget(),'near','The nearer visible player is chosen first');
    nearBlocked=true;pairStep();
    assert.equal(readTarget(),'far','When the first player is hidden the other one, skipped earlier by score, is checked at once');
  }
  // After the 100 ms memory only the best two points are probed; the full sweep returns after 400 ms. A player stepping out of cover
  // is found by the probe when a best point shows, otherwise by the next full sweep.
  {
    const castLog=[];let visibleAt=null;
    const probeNative=rva=>rva===0xa8261c8?(from,to)=>{castLog.push(to.slice());return visibleAt&&visibleAt.every((v,i)=>Math.abs(v-to[i])<1e-9)?0:1;}:rva===0xa82b000?()=>new Pointer(500):rva===0xa7a4150?()=>false:native(rva);
    const rec=new Map([['enemy',{t:time,team:2,health:100,bonePositions:bones}]]);
    const probeEngine=api.createAim({native:probeNative,wallRules:{classify:()=>false,reset(){}},settings:memorySettings,records:rec,tracked:new Map([['enemy',{player:new Pointer(2)}]]),
      transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>false});
    const stepProbe=ms=>{time+=ms;rec.get('enemy').t=time;const before=castLog.length;probeEngine.step(new Pointer(1),new Pointer(3),1);return castLog.length-before;};
    const sweep=stepProbe(16);assert(sweep>=4,'full sweep first: '+sweep);
    const best=castLog[0].slice(),last=castLog[sweep-1].slice();
    assert.equal(stepProbe(16),0,'inside the memory nothing is cast');
    assert.equal(stepProbe(100),2,'after 100 ms exactly the two best points are probed, not all '+sweep);
    assert.equal(probeEngine.status().target,null);
    assert.equal(stepProbe(16),0,'after a failed probe the player stays remembered as hidden');
    visibleAt=best;stepProbe(100);
    assert.equal(probeEngine.status().target,'enemy','A best point that becomes visible is found by the probe');
    visibleAt=null;stepProbe(16);   // blocked again: the memory was cleared by the pick, so this is a full sweep
    stepProbe(16);stepProbe(100);   // probe
    visibleAt=last;stepProbe(100);
    assert.equal(probeEngine.status().target,null,'A point beyond the probed ones is not found by a probe');
    assert.equal(stepProbe(400),sweep,'but the full sweep after 400 ms casts every point again');
    assert.equal(probeEngine.status().target,'enemy','and finds it');
    const taken=probeEngine.takeCost();
    assert(taken.steps>=8&&taken.casts>0&&taken.probes>=2&&taken.skipped>=2,'takeCost() reports what the steps did: '+JSON.stringify(taken));
    assert.equal(probeEngine.takeCost().steps,0,'and zeroes it');
  }
  context.Date=Date;
}
console.log('Hidden-player memory: skipped within 100 ms, re-checked after it, on camera/player movement and on reset passed.');
