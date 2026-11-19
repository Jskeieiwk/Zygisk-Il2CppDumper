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
  const engine=api.createAim({native:wallNative,wallRules,settings:forceSettings,records:enemy,tracked,
    transform:value=>value,position:()=>[0,0,0],getHealth:()=>100,active:()=>true});
  const decision=()=>{enemy.get('enemy').t=Date.now();engine.step(new Pointer(1),new Pointer(3),1);return captured.getAim();};
  slabs=[[4,4.2,'solid']];
  let state=decision();
  assert(state.selected,'Aim Visible Only=false still selects a target behind a wall');
  assert.equal(state.clear,false,'Without Wallshot a target behind a wall must not be fired at');
  slabs=[];state=decision();
  assert.equal(state.clear,true);assert.equal(state.selected.reach.direct,true,'A visible target is recorded as direct');
  // Wallshot is a plain switch: it passes breakable obstacles and refuses solid or unknown ones, whatever their thickness.
  forceSettings.Wallshot=true;
  slabs=[[4,4.2,'solid']];state=decision();assert.equal(state.clear,false,'A solid wall stops the shot even with Wallshot');
  assert.equal(state.selected.reach.blocked,'solid');
  slabs=[[4,4.2,'breakable']];state=decision();
  assert.equal(state.clear,true,'A breakable obstacle can be shot through');assert.equal(state.selected.reach.walls,1);
  slabs=[[4,6,'breakable']];state=decision();assert.equal(state.clear,true,'Thickness plays no role: a 2 m breakable obstacle is passable too');
  slabs=[[4,4.2,'breakable'],[6,6.25,'breakable']];state=decision();assert.equal(state.clear,true);assert.equal(state.selected.reach.walls,2);
  slabs=[[4,4.2,'breakable'],[6,6.25,'solid']];state=decision();assert.equal(state.clear,false,'One solid obstacle on the way is enough to refuse');
  slabs=[[4,4.2,'mystery']];state=decision();assert.equal(state.clear,false,'An unclassified obstacle counts as solid');
  assert.equal(state.selected.reach.blocked,'unknown');
  slabs=[[3,3.1,'breakable'],[4,4.1,'breakable'],[5,5.1,'breakable'],[6,6.1,'breakable'],[7,7.1,'breakable']];
  state=decision();assert.equal(state.clear,false,'The obstacle loop is bounded');
  slabs=[[4,4.2,'player']];state=decision();assert.equal(state.clear,true,'Another player is passable without asking the wall rules');
  slabs=[[4,4.1,'breakable'],[4.3,4.45,'breakable']];state=decision();assert.equal(state.clear,true,'Two separate breakable objects are fine');
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
  const choose=()=>{records.get('enemy').t=Date.now();engine.step(new Pointer(1),new Pointer(3),1);return captured.getAim().selected;};
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
console.log('Hitbox ranking, hitbox-all, multipoint percent and hit chance gating passed.');
