const assert=require('node:assert/strict');
const fs=require('node:fs');
const vm=require('node:vm');
const memory=new Map(),hooks=new Map(),calls=[];
let next=0x100000,alpha=.8;
const objects=new Map(),dead=new Set();
class Pointer {
  constructor(value){this.value=value;}
  add(offset){return new Pointer(this.value+offset);}
  equals(other){return this.value===other.value;}
  isNull(){return this.value===0;}
  toString(){return String(this.value);}
  readPointer(){return memory.get(this.value)||new Pointer(0);}
  writePointer(value){memory.set(this.value,value);}
  readU64(){return {toNumber:()=>memory.get(this.value)||0};}
}
const ptr=value=>new Pointer(value);
function object(value){const p=ptr(next);next+=0x100;objects.set(p.value,value);return p;}
const renderer=object('renderer'),group=object('lod'),player=object('player');
const original=object('original material'),array=object('materials'),shader=object('shader');
const view=object('AimView'),scope=object('CanvasGroup');
memory.set(player.value+0x30,group);memory.set(group.value+0x38,renderer);
memory.set(array.value+0x18,1);memory.set(array.value+0x20,original);
memory.set(view.value+0x50,scope);
function native(address){return (...args)=>{
  calls.push({address,args});
  switch(address){
    case 0x95103ec:return object(objects.get(args[0].value));
    case 0x9647044:return object('handle');
    case 0x9647058:return;
    case 0xa78ebc4:return !args[0].isNull()&&!dead.has(args[0].value);
    case 0xa78f844:return object('clone');
    case 0xa790098:dead.add(args[0].value);return;
    case 0xa7467f0:return shader;
    case 0x9823338:return object('Type');
    case 0x983f018:return object('CommandBuffer');
    case 0xa7458e4:return array;
    case 0xa74c5e0:return original;
    case 0xa74c8d8:assert.equal(args[2],0,'Frida bool must receive an integer');return;
    case 0xa79fab4:return [1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1];
    case 0xa74e780:return 1;
    case 0xa7bb46c:return;
    case 0xab5c4fc:return alpha;
    case 0xab5c670:alpha=args[1];return;
    case 0xa747748:case 0xa748228:case 0xa747ce8:case 0xa74a130:
    case 0xa72b4a0:case 0xa72b674:case 0xa7bae74:case 0xa7b75c0:case 0xa7bb49c:return;
    default:throw Error('Unexpected native function '+address.toString(16));
  }
};}
const settings={'Player ESP':true,Chams:true,'3D Model':false,'Shader Chams':false,
  'Ghost Chams':false,'Chams Opacity':70,'Enemy Color':'#efa8c5','Team Color':'#72baff'};
const context=vm.createContext({
  console,Date,Map,Set,ptr,Process:{pointerSize:8},
  Memory:{alloc:()=>object('allocation'),allocUtf8String:value=>object(value)},
  Interceptor:{attach:(address,hook)=>{hooks.set(address.value,hook);return {detach:()=>hooks.delete(address.value)};}},
  settings,native,player,
  apiContext:{native,settings,base:ptr(0),transform:()=>ptr(0),position:()=>[0,0,0],project:()=>null,
    readManagedString:()=>'',getLocalPlayer:()=>null,trackedPlayers:new Map()}
});
vm.runInContext(fs.readFileSync('assets/visual-features.js','utf8').replace('export function','function')+
  '\nglobalThis.api=createVisualFeatures(apiContext);',context);
const players=new Map([['player',{player,local:false,team:1,t:Date.now()}]]);
context.api.updateChams(ptr(0x200000),players,()=>2);
assert.equal(calls.filter(call=>call.address===0xa7bb49c).length,1);
const clone=calls.find(call=>call.address===0xa747748).args[0];
settings.Chams=false;
context.api.updateChams(ptr(0x200000),players,()=>2);
assert(dead.has(clone.value),'Colored material clone must be destroyed on disable');
assert(!dead.has(original.value),'Original material must survive');
assert.equal(calls.filter(call=>call.address===0xa72b674).length,1,'Camera command buffer must detach');
assert.equal(calls.filter(call=>call.address===0xa7bae74).length,1,'Command buffer must dispose');
settings.Chams=true;settings['Ghost Chams']=true;
context.api.updateChams(ptr(0x200000),players,()=>2);
assert.equal(calls.filter(call=>call.address===0xa72b4a0).length,2,'Re-enable must create a fresh command buffer');
// Custom Scope restores the real HUD alpha before the next game update.
settings['Custom Scope']=true;context.api.syncHooks();
const scopeHook=hooks.get(0x6929a84),invocation={};
scopeHook.onEnter.call(invocation,[view]);scopeHook.onLeave.call(invocation);
assert.equal(alpha,0);
settings['Custom Scope']=false;context.api.syncHooks();
assert(!hooks.has(0x6929a84),'Disabled scope features must detach the hot HUD hook');
scopeHook.onEnter.call(invocation,[view]);scopeHook.onLeave.call(invocation);
assert.equal(alpha,.8);
context.api.suspend();settings['Player ESP']=false;settings.Chams=false;settings['Grenade Glow']=true;
const beforeGrenade=calls.filter(call=>call.address===0xa7bb49c).length;
context.api.updateChams(ptr(0x200000),new Map([['grenade',{player,renderer,kind:'grenade',local:false,team:0,t:Date.now()}]]),()=>2);
assert.equal(calls.filter(call=>call.address===0xa7bb49c).length,beforeGrenade+1,'Grenade glow must render independently of player chams');
settings['Grenade Glow']=false;context.api.updateChams(ptr(0x200000),new Map(),()=>2);
assert(!dead.has(original.value));
console.log('Material ownership, command buffer disposal, re-enable and scope restoration checks passed.');
