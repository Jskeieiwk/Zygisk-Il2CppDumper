const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const hooks=new Map(),memory=new Map();let shots=0,rotation=[0,0,0],active=true,matchReady=false,generation=0;
class Pointer {
 constructor(value){this.value=BigInt(value);}
 add(offset){return new Pointer(this.value+BigInt(offset));}
 equals(other){return this.value===other.value;}
 isNull(){return this.value===0n;}
 or(other){return new Pointer(this.value|other.value);}
 and(other){return new Pointer(this.value&other.value);}
 toString(){return '0x'+this.value.toString(16);}
 readPointer(){return memory.get(this.toString())||new Pointer(0);}
 readS32(){return memory.get(this.toString());}
 writeS32(value){memory.set(this.toString(),value);}
 readByteArray(length){return memory.get(this.toString()).slice(0,length).buffer;}
 writeByteArray(value){memory.set(this.toString(),new Uint8Array(value).slice());}
 writeU8(value){memory.get(this.toString())[0]=value;}
}
const ptr=value=>new Pointer(value),local=ptr(1000),weapon=ptr(2000),aim=ptr(3000);
memory.set(weapon.add(0x20).toString(),local);memory.set(local.add(0x128).toString(),aim);
const settings={Trigger:true,'Trigger Delay':30,'Silent Aim':false};
let target={t:Date.now(),selected:{angles:[10,20,0]},crosshair:false,clear:true};
const context=vm.createContext({console,ptr,Date,Interceptor:{attach:(address,hook)=>{hooks.set(address.toString(),hook);return {detach:()=>hooks.delete(address.toString())};}}});
vm.runInContext(fs.readFileSync('assets/fire-control.js','utf8').replaceAll('export function','function').replaceAll('export const','const')+
 '\nglobalThis.api={decodeCommand,createFireCalibration,installFireControl,createClicker,createScopeCalibration,MEASURED_SCOPE_BYTES};',context);
const api=context.api;
assert.equal(api.decodeCommand(ptr(0x1122)),null);
const controls=api.installFireControl({base:ptr(0),settings,getLocalPlayer:()=>local,getAim:()=>target,active:()=>active,canRun:()=>matchReady,generation:()=>generation,
 native:rva=>({[0x42da568]:()=>shots,[0x5452708]:()=>rotation.slice(),[0x54519e4]:(_aim,value)=>{rotation=Array.from(value)}}[rva])});
controls.ensureInstalled();assert.equal(hooks.size,0,'Lobby must not install gameplay hooks');
matchReady=true;controls.status();assert.equal(hooks.size,0,'Reading fire status must never install gameplay hooks');
controls.ensureInstalled();
const hook=hooks.get(ptr(0x42e52cc).toString());
function command(raw){
 const call={},args=[weapon,ptr(raw)];hook.onEnter.call(call,args);
 const during=rotation.slice();if(!args[1].and(ptr(1)).isNull())shots++;
 hook.onLeave.call(call);return {args,during};
}
// The measured fire flag (byte 0) is ready at once: no own shots are needed before automatic fire.
assert.equal(controls.status().ready,true,'The measured fire flag is ready without shooting first');
let tick=Date.now()+1000;context.Date={now:()=>tick};
target={...target,t:tick,crosshair:true};
assert.equal(command(0).args[1].value,1n,'Trigger must inject the fire flag');
active=false;assert.equal(command(0).args[1].value,0n,'Menu pause must prevent automated fire');
active=true;
// A click: the flag stays set for 80 ms, then is released for at least the Trigger Delay (minimum 40 ms).
for(const at of [10,40,79]){tick+=at-(tick%1000===0?0:0);}
tick=Date.now()+5000;context.Date={now:()=>tick};target={...target,t:tick,crosshair:true};
const pressed=[];
for(let ms=0;ms<=300;ms+=10){tick=Date.now()+5000+ms;target.t=tick;pressed.push(command(0).args[1].value===1n?1:0);}
// 0..70 ms pressed (8 samples), released from 80 ms, pressed again at 80+40=120 ms... with Trigger Delay 30 the release lasts 40 ms
assert.deepEqual(pressed.slice(0,8),[1,1,1,1,1,1,1,1],'Held for the press window');
assert.equal(pressed[8],0,'Released after 80 ms');
assert.equal(pressed.slice(8,12).every(v=>v===0),true,'Released for at least 40 ms');
assert.equal(pressed[12],1,'Pressed again after the release window');
settings['Trigger Delay']=200;target={...target,crosshair:false};
for(let ms=0;ms<=200;ms+=10){tick=Date.now()+20000+ms;target.t=tick;command(0);}
target.crosshair=true;tick=Date.now()+20300;target.t=tick;
assert.equal(command(0).args[1].value,1n,'A new click starts once the release has lasted the Trigger Delay');
tick+=100;target.t=tick;assert.equal(command(0).args[1].value,0n,'and is released after the press window');
tick+=150;target.t=tick;assert.equal(command(0).args[1].value,0n,'Trigger Delay 200 ms keeps it released');
tick+=60;target.t=tick;assert.equal(command(0).args[1].value,1n,'then clicks again');
// Silent aim rotates only while a shot is actually fired, and restores the rotation.
target={...target,crosshair:false};settings['Silent Aim']=true;tick+=1000;target.t=tick;
assert.deepEqual(command(1).during,[10,20,0]);assert.deepEqual(rotation,[0,0,0],'Silent rotation must restore');
assert.deepEqual(command(0x100).during,[0,0,0],'Unrelated input must not change aim');
settings['Silent Aim']=false;
// Clicker alone
{
  const c=api.createClicker(80);
  assert.equal(c.update(true,0,30),true);assert.equal(c.update(false,50,30),true,'A started press is finished even if the target is lost');
  assert.equal(c.update(true,80,30),false);assert.equal(c.update(true,119,30),false);assert.equal(c.update(true,120,30),true);
}
context.Date=Date;settings['Trigger Delay']=30;
const inventory=ptr(5000),parameters=ptr(6000);
memory.set(local.add(0xf0).toString(),inventory);memory.set(inventory.add(0xa8).toString(),weapon);
memory.set(weapon.add(0xb8).toString(),parameters);
memory.set(parameters.add(0x1a4).toString(),10);memory.set(parameters.add(0x264).toString(),new Uint8Array(12).fill(7));
settings.Autowall=true;
const penetration=hooks.get(ptr(0x4136838).toString()),call={};
penetration.onEnter.call(call,[parameters]);
assert.equal(parameters.add(0x1a4).readS32(),30);
assert.equal(new Uint8Array(parameters.add(0x264).readByteArray(12))[0],0);
penetration.onLeave.call(call);
assert.equal(parameters.add(0x1a4).readS32(),10);
assert(new Uint8Array(parameters.add(0x264).readByteArray(12)).every(value=>value===7));
penetration.onEnter.call({},[ptr(9000)]);
assert.equal(parameters.add(0x1a4).readS32(),10);
settings['Knife Bot']=true;controls.ensureInstalled();
assert(controls.status().ready,'Adding the knife hook must preserve an existing fire calibration');
const knife=ptr(8000);memory.set(knife.add(0x20).toString(),local);
const knifeHook=hooks.get(ptr(0x5af1fc0).toString()),knifeCall={},knifeArgs=[knife,ptr(0)];
target={t:Date.now(),isKnife:true,selected:{angles:[5,10,0]},crosshair:false};
knifeHook.onEnter.call(knifeCall,knifeArgs);assert.equal(knifeArgs[1].value,1n);assert.deepEqual(rotation,[5,10,0]);
knifeHook.onLeave.call(knifeCall);assert.deepEqual(rotation,[0,0,0]);
const wrongArgs=[ptr(9000),ptr(0)];knifeHook.onEnter.call({},wrongArgs);assert.equal(wrongArgs[1].value,0n);
settings['Knife Bot']=false;controls.ensureInstalled();assert(!hooks.has(ptr(0x5af1fc0).toString()));
// Force Shot obeys the wall rule, and every automatic shot says why it was allowed.
{
  const logged=[],originalLog=console.log;console.log=message=>{if(!String(message).startsWith('CLOUD:trigger-click'))logged.push(String(message));};
  const saved={...settings};
  let clock=Date.now()+100000;context.Date={now:()=>clock};
  Object.assign(settings,{Trigger:false,'Silent Aim':false,'Force Shot':true,'Trigger Delay':1});
  const selected=reach=>({angles:[10,20,0],reach});
  const wallReach={wall:true,direct:false,walls:1,blocked:null};
  target={t:clock,selected:selected(wallReach),crosshair:false,clear:false};
  let result=command(0);
  assert.equal(result.args[1].value,0n,'A Force Shot target that failed the wall rule must not fire');
  assert.deepEqual(command(1).during,[0,0,0],'A blocked Force Shot target must not redirect a manual shot');
  assert.equal(logged.length,0,'Blocked frames log nothing');
  target={t:clock,selected:selected(wallReach),crosshair:false,clear:true};
  assert.equal(command(0).args[1].value,1n,'A Force Shot target that passed the wall rule fires');
  assert.deepEqual(logged,['CLOUD:auto-shot kind=force reach=through=1']);
  clock+=10;target.t=clock;assert.equal(command(0).args[1].value,1n);
  assert.equal(logged.length,1,'Automatic shot logs are rate limited to one per 400 ms');
  clock+=500;target={t:clock,selected:selected({wall:false,direct:true,walls:0,blocked:null}),crosshair:false,clear:true};
  command(0);assert.equal(logged.at(-1),'CLOUD:auto-shot kind=force reach=direct');
  // Plain Trigger fires from the real crosshair ray, so its log says so.
  Object.assign(settings,{'Force Shot':false,Trigger:true,Autowall:false});
  clock+=500;target={t:clock,selected:selected(null),crosshair:true,clear:false};
  assert.equal(command(0).args[1].value,1n);assert.equal(logged.at(-1),'CLOUD:auto-shot kind=trigger reach=crosshair-ray');
  // Silent Aim only redirects a shot the player fired, and only onto a target with a clear line.
  Object.assign(settings,{Trigger:false,'Silent Aim':true,'Force Shot':false});
  clock+=500;target={t:clock,selected:selected(null),crosshair:false,clear:false};
  assert.deepEqual(command(1).during,[0,0,0],'Silent Aim must not redirect a manual shot into a wall');
  target={t:clock,selected:selected(null),crosshair:false,clear:true};
  assert.deepEqual(command(1).during,[10,20,0],'Silent Aim redirects manual shots onto a visible target');
  console.log=originalLog;Object.assign(settings,saved);context.Date=Date;
}
controls.suspend();assert.equal(hooks.size,0,'Pausing aim must detach hot fire hooks');
assert.equal(controls.status().ready,true,'Pausing must preserve learned calibration');
controls.ensureInstalled();assert.equal(hooks.size,2,'Resuming aim must install the hooks once');
matchReady=false;generation++;controls.reset();assert.equal(hooks.size,0);assert.equal(controls.status().ready,true,'A reset returns to the measured fire flag, not to an untrained state');
matchReady=true;controls.ensureInstalled();assert.equal(hooks.size,2);assert.equal(controls.status().samples,3);

// Auto Scope: the scope byte is learned from the player's own openings, then pressed as a click when a sniper has a target.
{
  controls.reset();
  const logs=[],originalLog=console.log;console.log=message=>{logs.push(String(message));};
  let clock=Date.now()+900000;context.Date={now:()=>clock};
  const scope={active:false,sniper:true};
  const scopeSettings={'Auto Scope':true,Trigger:false,'Silent Aim':false,'Force Shot':false,'Auto Calibration':false,'Trigger Delay':30};
  const scoped=api.installFireControl({base:ptr(0),settings:scopeSettings,getLocalPlayer:()=>local,getAim:()=>target,active:()=>active,canRun:()=>matchReady,generation:()=>generation,
    getScope:()=>scope,native:rva=>({[0x42da568]:()=>shots,[0x5452708]:()=>rotation.slice(),[0x54519e4]:(_aim,value)=>{rotation=Array.from(value)}}[rva])});
  scoped.ensureInstalled();
  const scopeHook=hooks.get(ptr(0x42e52cc).toString());
  const run=(raw,advance=10)=>{clock+=advance;target={...target,t:clock,selected:{angles:[10,20,0]},crosshair:false,clear:false};
    const args=[weapon,ptr(raw)];scopeHook.onEnter.call({},args);scopeHook.onLeave.call({});return args[1].value;};
  // The measured scope byte (byte 1) is the starting point: no manual scoping is needed before the first automatic click.
  assert.equal(run(0),0x100n,'The measured scope byte is clicked without any manual scoping');
  assert(logs.some(line=>line==='CLOUD:scope-calibrated mask=0x0000000000000100 samples=3'),'The seeded byte is reported: '+logs.join('|'));
  run(0,40);run(0,100);run(0,2000);
  // Manual openings (the player presses byte 1 and the scope opens 200 ms later) confirm it and are logged; the fire byte is ignored.
  // The menu pause (active=false) keeps the module from clicking while the openings are simulated.
  active=false;
  for(let opening=0;opening<3;opening++){
    run(0x101,10);scope.active=false;run(0x100,10);run(0,190);scope.active=true;run(0,10);scope.active=false;run(0,2000);
  }
  active=true;run(0,3000);
  assert.equal(run(0),0x100n,'A closed scope with a sniper and a fresh target gets the scope click');
  assert.equal(run(0,40),0x100n,'The click is held for the press window');
  assert.equal(run(0,100),0n,'then released');
  scope.sniper=false;run(0,2000);assert.equal(run(0,600),0n,'Only sniper rifles are scoped');
  scope.sniper=true;active=false;assert.equal(run(0,600),0n,'The menu pause blocks the click');active=true;
  // Our own opening teaches nothing, and an open scope is left alone.
  scope.active=true;assert.equal(run(0,600),0n);scope.active=false;
  // A detector that lags: the scope shows 600 ms after the click. A second click would close it again, so there must be none.
  run(0,3000);assert.equal(run(0),0x100n,'The click starts');
  const lag=[];for(let ms=0;ms<600;ms+=10)lag.push(run(0,10)===0x100n?1:0);
  assert.equal(lag.slice(10).some(Boolean),false,'No second click while the first one is awaited (900 ms): '+lag.join(''));
  scope.active=true;run(0,10);
  assert(logs.some(line=>/^CLOUD:auto-scope-result opened=true afterMs=\d+$/.test(line)),'The delay until the scope was seen open is logged: '+logs.join('|'));
  scope.active=false;run(0,2000);
  // Two clicks without the scope opening: back off instead of toggling it forever (clicks are 900 ms apart).
  run(0,3000);const presses=[];
  for(let ms=0;ms<2800;ms+=10)presses.push(run(0,10)===0x100n?1:0);
  const clicks=presses.reduce((count,value,index)=>count+(value&&!presses[index-1]?1:0),0);
  assert.equal(clicks,2,'Exactly two attempts, then the module gives up: '+clicks);
  assert(logs.some(line=>line.startsWith('CLOUD:auto-scope-result opened=false')),'A click that did not open the scope is logged as such');
  assert(logs.some(line=>/^CLOUD:scope-sample n=4 bytes=010000 candidates=1$/.test(line)),'Each manual opening logs the bytes seen before it: '+logs.join('|'));
  assert(logs.some(line=>line.startsWith('CLOUD:auto-scope-gave-up')),'The back-off is logged');
  scoped.reset();console.log=originalLog;context.Date=Date;
}
// The seeded scope byte is checked by real openings: consistent ones keep it, an opening without it starts the learning from scratch.
{
  const calibration=api.createScopeCalibration(0,api.MEASURED_SCOPE_BYTES);
  assert.equal(calibration.state().mask,'0x0000000000000100');assert.equal(calibration.state().ready,true);
  calibration.observe([{t:0,bytes:[0,1,0,0,0,0]}],100);
  assert.equal(calibration.state().mask,'0x0000000000000100','An opening with byte 1 keeps the seeded byte');
  const other=api.createScopeCalibration(0,api.MEASURED_SCOPE_BYTES),history=[{t:0,bytes:[1,0,0,1,0,0]}];
  other.observe(history,100);assert.equal(other.state().ready,false,'An opening without byte 1 drops the seed and starts learning');
  other.observe(history,100);other.observe(history,100);
  assert.equal(other.state().mask,'0x0000000001000000','Three such openings learn byte 3');
  other.reset();assert.equal(other.state().mask,'0x0000000000000100','reset() returns to the measured byte');
  assert.equal(api.createScopeCalibration().state().ready,false,'Without a seed nothing is assumed');
}
console.log('Lobby guards, scene reset, fire calibration, trigger, silent and penetration restoration checks passed.');
