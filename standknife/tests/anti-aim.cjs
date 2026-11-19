const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const source=fs.readFileSync('assets/anti-aim.js','utf8').replaceAll('export function','function').replaceAll('export const','const');
const logs=[];
const context=vm.createContext({console,Date,ptr:v=>new Pointer(v),Math,Number});
class Pointer{
  constructor(value){this.value=value;}
  add(offset){return new Pointer(this.value+offset);}
  sub(other){return new Pointer(this.value-(other.value??other));}
  compare(other){return this.value-other.value;}
  equals(other){return this.value===other.value;}
  isNull(){return this.value===0;}
  toInt32(){return this.value|0;}
  readPointer(){return new Pointer(this.pointerValue||0);}
}
context.Pointer=Pointer;
vm.runInContext(source+';globalThis.api={antiAimAngles,wrapDegrees,clampNumber,createRotationProbe,createAntiAim,ANTI_AIM_CONFIG,AA_YAW_MODES,AA_PITCH_MODES};',context);
const {antiAimAngles,wrapDegrees,createRotationProbe,createAntiAim,ANTI_AIM_CONFIG}=context.api;
const near=(a,b,message)=>assert(Math.abs(a-b)<1e-9,message+': '+a+' vs '+b);
// Offset mode: the real yaw plus the offset, wrapped to [-180,180].
let out=antiAimAngles([10,170],{'AA Yaw Mode':0,'AA Yaw Offset':180,'AA Pitch Mode':0},0);
near(out[1],-10,'170 + 180 wraps to -10');near(out[0],10,'pitch kept when pitch mode is off');assert.equal(out[2],0);
// Pitch modes and the +-89 limit.
assert.equal(antiAimAngles([0,0],{'AA Pitch Mode':1},0)[0],89);assert.equal(antiAimAngles([0,0],{'AA Pitch Mode':2},0)[0],-89);
const flipA=antiAimAngles([0,0],{'AA Pitch Mode':3},0)[0],flipB=antiAimAngles([0,0],{'AA Pitch Mode':3},80)[0];
assert.equal(flipA,-flipB,'Pitch jitter alternates between +89 and -89');
// Jitter alternates around the offset by +-range every 80 ms.
const a=antiAimAngles([0,0],{'AA Yaw Mode':1,'AA Yaw Offset':180,'AA Jitter Range':30},0)[1],b=antiAimAngles([0,0],{'AA Yaw Mode':1,'AA Yaw Offset':180,'AA Jitter Range':30},80)[1];
near(wrapDegrees(a-b),60,'the two jitter sides are 2 x range apart');
// Spin ignores the real yaw and advances with time at the configured speed.
near(antiAimAngles([0,50],{'AA Yaw Mode':2,'AA Spin Speed':180},1000)[1],-180,'180 deg/s for 1 s is half a turn');
near(antiAimAngles([0,50],{'AA Yaw Mode':2,'AA Spin Speed':90},1000)[1],90,'90 deg/s for 1 s is a quarter turn');
// Unusable input is refused and out-of-range settings are clamped, not trusted.
assert.equal(antiAimAngles(null,{},0),null);assert.equal(antiAimAngles([NaN,0],{},0),null);assert.equal(antiAimAngles([0,0],{},NaN),null);
near(antiAimAngles([0,0],{'AA Yaw Mode':0,'AA Yaw Offset':9999},0)[1],wrapDegrees(180),'offset is clamped to 180');
assert.equal(antiAimAngles([0,0],{'AA Pitch Mode':1.9},0)[0],89,'a fractional mode index is truncated');
assert.equal(antiAimAngles([0,0],{'AA Pitch Mode':99},0)[0],89,'a mode above the list uses the last one');
// Without a measured sender the engine stays gated and hooks nothing.
assert.equal(ANTI_AIM_CONFIG.senderRva,null,'The sender is not measured yet and must stay null, not zero');
{
  const attached=[];
  const aa=createAntiAim({native:()=>()=>[0,0,0],settings:{'Anti-Aim':true},getLocalPlayer:()=>null,canRun:()=>true,generation:()=>1,
    attachHook:(rva,callbacks,label)=>{attached.push(label);return true;},removeHook(){},log:()=>{}});
  aa.sync();assert.equal(attached.length,0,'No hook while senderRva is null');assert.equal(aa.ready(),false);assert.equal(aa.gated(),true);
}
// With a sender RVA the real angles are replaced during the call and restored afterwards, only in the current generation.
{
  const calls=[];let generation=1;const aimPtr=new Pointer(0x5000);
  const local=new Pointer(0x4000);local.pointerValue=0;
  local.add=offset=>{const p=new Pointer(0x4000+offset);p.pointerValue=0x5000;return p;};
  let hook=null;const removed=[];
  const native=rva=>(...args)=>{
    if(rva===ANTI_AIM_CONFIG.getRotation)return [5,170,0];
    calls.push(args[1].slice());return undefined;
  };
  const config={...ANTI_AIM_CONFIG,senderRva:0x1234};
  const settings={'Anti-Aim':true,'AA Yaw Mode':0,'AA Yaw Offset':180,'AA Pitch Mode':0};
  const aa=createAntiAim({native,settings,getLocalPlayer:()=>local,canRun:()=>true,generation:()=>generation,config,
    attachHook:(rva,callbacks,label)=>{assert.equal(rva,0x1234);hook=callbacks;return true;},removeHook:label=>removed.push(label),log:()=>{}});
  aa.sync();assert.equal(aa.ready(),true);
  const state={};hook.onEnter.call(state,[]);
  assert.equal(calls.length,1);assert(Math.abs(calls[0][1]-(-10))<1e-9||Math.abs(wrapDegrees(calls[0][1]+10))<1e-9,'sender sees the replaced yaw');
  hook.onLeave.call(state);assert.deepEqual(calls[1],[5,170,0],'the real angles are restored after the call');
  // A new generation (match change) must not write a stale controller.
  const stale={};hook.onEnter.call(stale,[]);generation=2;const before=calls.length;hook.onLeave.call(stale);assert.equal(calls.length,before,'No restore across generations');
  // Switching the feature off removes the hook.
  settings['Anti-Aim']=false;aa.sync();assert.deepEqual(removed,['anti-aim-sender']);assert.equal(aa.ready(),false);
}
// Probe: counts callers of the local controller only, ignores calls from outside the module, and stops after its reports.
{
  const lines=[];const base=new Pointer(0x10000000);
  const local=new Pointer(0x4000);local.add=offset=>{const p=new Pointer(0x4000+offset);p.pointerValue=0x5000;return p;};
  const hooks=new Map(),removed=[];
  let t=1000;const realNow=Date.now;context.Date={now:()=>t};
  // the probe reads Date.now() from the vm context
  const probe=vm.runInContext('(function(ctx){return createRotationProbe(ctx);})',context)({base,getLocalPlayer:()=>local,canRun:()=>true,
    attachHook:(rva,callbacks,label)=>{hooks.set(label,callbacks);return true;},removeHook:label=>removed.push(label),log:line=>lines.push(line),windowMs:3000,reports:2});
  probe.sync(true);assert.equal(probe.running(),true);assert(lines[0].startsWith('CLOUD:aa-probe-started'));
  const fire=(label,controller,ret)=>hooks.get(label).onEnter.call({returnAddress:ret},[controller]);
  const mine=new Pointer(0x5000),someoneElse=new Pointer(0x6000);
  for(let i=0;i<30;i++)fire('aa-probe-get',mine,base.add(0x123456));
  for(let i=0;i<5;i++)fire('aa-probe-set',mine,base.add(0x222222));
  for(let i=0;i<9;i++)fire('aa-probe-get',someoneElse,base.add(0x999999));
  for(let i=0;i<4;i++)fire('aa-probe-get',mine,new Pointer(0x7f0000000000)); // our own call from Frida memory
  t+=3100;fire('aa-probe-get',mine,base.add(0x123456));
  const text=lines.join('\n');
  assert(/get caller=0x123456 calls=31/.test(text),'caller counted with the call that closed the window: '+text);
  assert(/set caller=0x222222 calls=5/.test(text));
  assert(!/999999/.test(text),'other controllers are not reported as callers');
  assert.equal(new Set(text.match(/get caller=0x[-0-9a-f]+/g)).size,1,'calls from outside the module add no caller of their own: '+text);
  t+=3100;fire('aa-probe-get',mine,base.add(0x123456));
  assert(lines.includes('CLOUD:aa-probe-done'),'The probe finishes after its reports');
  assert.deepEqual(removed.sort(),['aa-probe-get','aa-probe-set'],'and detaches both hooks');
  probe.sync(true);assert.equal(probe.running(),false,'A finished probe does not restart while the setting stays on');
  probe.sync(false);probe.sync(true);assert.equal(probe.running(),true,'Switching the setting off and on runs it again');
  context.Date=Date;
}
console.log('Anti-aim angles (offset/jitter/spin, pitch modes), gating without a sender, set-and-restore around the sender and the caller probe passed.');
