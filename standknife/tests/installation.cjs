const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const memory=new Map(),revealed=[];
class Pointer {
  constructor(value){this.value=value;}
  add(offset){return new Pointer(this.value+offset);}
  isNull(){return !this.value;}
  equals(other){return this.value===other.value;}
  readPointer(){return new Pointer(memory.get(this.value)||0);}
  toString(){return '0x'+this.value.toString(16);}
}
function harness(failures,warm=true){
  const active=new Map(),messages=[];
  const context=vm.createContext({
    console:{log:message=>messages.push(message)},Date,ptr:value=>new Pointer(value),
    Process:{arch:'arm64',id:1,findRangeByAddress:()=>({protection:'r-x'})},
    Interceptor:{attach(address,callbacks){
      if(failures.has(address.value))throw Error('unable to intercept function at '+address);
      assert(!active.has(address.value),'Duplicate listener at '+address);
      active.set(address.value,callbacks);
      return {detach(){active.delete(address.value);}};
    }},
    NativeFunction:function(address){return (...args)=>{if(address.value===0x3f2a8e4){revealed.push(args);return;}throw Error('Installation must not invoke game methods');};},
    createAim:()=>({reset(){},step(){},status:()=>({})}),
    Memory:{alloc:()=>new Pointer(0x1000)},
    createFrameMeter:()=>({frame(){},value:()=>null}),
    Java:{perform(){},scheduleOnMainThread:callback=>callback()},
    __WATERMARK_FONTS__:{},__RENDER_DEX__:"",setInterval(){return 1;},clearInterval(){}
  });
  for(const name of ['aim-motion','performance','hooks','capabilities','session','engine','raw-input','world-visuals','camera-effects','scene-effects','visual-features','net-position','module']){
    vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function').replaceAll('export const','const'),context);
  }
  if(warm)vm.runInContext("settings['Hit Marker']=true;settings['Bullet Tracers']=true;settings['Check Recoil']=true;for(let i=1;i<=3;i++)matchSession.update(true,1,Date.now(),i);",context);
  vm.runInContext('moduleBase=ptr(0);globalThis.testApi={install,state:runtimeState,trackedPlayers,settings};',context);
  return {api:context.testApi,active,messages};
}
// Reproduce a rejected HUD hook: core tracking and aim must still become ready.
const optional=harness(new Set([0x39db71c,0x64037b8,0x3af3bf0]));
assert.equal(optional.api.install(),true);
assert(optional.active.has(0x49ec32c));
assert(optional.active.has(0xa72b920));
const state=optional.api.state();
assert.equal(state.ready,true);
assert.equal(state.capabilities['Aim assistance'],true);
assert.equal(state.capabilities.Boxes,true);
assert.equal(state.capabilities['No Recoil'],false);
assert.equal(state.capabilities['Hit Marker'],false);
assert.equal(state.capabilities['Bullet Tracers'],false);
assert(!optional.active.has(0x39db360),'Do not attach the redundant UpdateView hook that failed on the phone');
const count=optional.active.size;
optional.api.install();
assert.equal(optional.active.size,count);
// Failure near the end must detach every earlier listener and keep readiness false.
const failures=new Set([0x49f48e0]),critical=harness(failures);
assert.equal(critical.api.install(),false);
assert.equal(critical.api.state().ready,false);
assert.equal(critical.active.size,0);
assert(!critical.messages.some(message=>message==='CLOUD:il2cpp-ready'));
// A subsequent retry must install exactly one listener per method.
failures.clear();
assert.equal(critical.api.install(),true);
assert.equal(critical.api.state().ready,true);
assert(critical.messages.some(message=>message==='CLOUD:il2cpp-ready'));
const cameraFailure=harness(new Set([0xa72b9f8]));
assert.equal(cameraFailure.api.install(),true);
assert.equal(cameraFailure.api.state().capabilities['Third Person'],false);
assert(!cameraFailure.active.has(0xa72b848),'Partial camera mode hooks must roll back independently');
assert(cameraFailure.active.has(0xa72b920),'Core ESP must survive a camera mode failure');
console.log('Optional HUD/recoil failures, capability states, critical rollback, retries and duplicate prevention passed.');

const cold=harness(new Set(),false);assert.equal(cold.api.install(),true);
for(const rva of [0x6929a84,0xa708984,0xa7087f0,0x3af3bf0,0x6402be0,0x6403428,0x64037b8])assert(!cold.active.has(rva),'Unused hot hooks must not attach in the lobby');
console.log('Cold-start HUD, tracer and recoil hooks: 0.');

// Occlusion: an obstructed enemy is marked visible again; teammates, strangers and the setting being off are left alone.
{
  const h=harness(new Set());assert.equal(h.api.install(),true);
  assert(h.active.has(0x3f2a2b0)&&h.active.has(0x3f2a40c),'Occlusion hooks attach');
  h.api.settings['Player ESP']=true;h.api.settings.Boxes=true;assert.equal(h.api.settings['Reveal Occluded'],false,'Reveal is off by default');h.api.settings['Reveal Occluded']=true;
  const enemy=new Pointer(0x5000),mate=new Pointer(0x6000),enemyOccluder=0x5100,mateOccluder=0x6100;
  memory.set(0x5000+0xf8,enemyOccluder);memory.set(0x6000+0xf8,mateOccluder);
  h.api.trackedPlayers.set('enemy',{player:enemy,local:false,team:2,t:Date.now()});
  h.api.trackedPlayers.set('local',{player:mate,local:true,team:1,t:Date.now()});
  const obstructed=h.active.get(0x3f2a2b0),unobstructed=h.active.get(0x3f2a40c);
  const fire=(callbacks,occluder)=>{const context={};callbacks.onEnter.call(context,[new Pointer(occluder)]);if(callbacks.onLeave)callbacks.onLeave.call(context);};
  revealed.length=0;fire(obstructed,enemyOccluder);
  assert.equal(revealed.length,1,'The obstructed enemy is revealed once');
  assert.equal(revealed[0][0].value,enemyOccluder);assert.equal(revealed[0][1],1);
  fire(obstructed,mateOccluder);fire(obstructed,0x7700);
  assert.equal(revealed.length,1,'The local player and unknown occludees are not touched');
  fire(unobstructed,enemyOccluder);assert.equal(revealed.length,1,'Unobstructing is only logged');
  h.api.settings['Reveal Occluded']=false;fire(obstructed,enemyOccluder);
  assert.equal(h.messages.filter(m=>m.startsWith('CLOUD:occlusion obstructed key=enemy')).length,2,'Without reveal only state changes are logged');fire(obstructed,enemyOccluder);
  assert.equal(revealed.length,1,'With the setting off nothing is revealed');
  assert.equal(h.messages.filter(m=>m.startsWith('CLOUD:occlusion obstructed key=enemy')).length,2,'A repeated obstruction is not logged again');
  assert(h.messages.some(m=>m.startsWith('CLOUD:occlusion obstructed key=enemy')&&m.includes('reveal=true')));
  console.log('Occlusion reveal for enemies only passed.');
}
