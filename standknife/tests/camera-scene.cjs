const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const hooks=new Map(),memory=new Map(),handles=new Set(),positions=new Map(),eulers=new Map(),locals=new Map();
let armsOn=true,bodyOn=false,bodyLayer=8,bodyActive=true,maskValue=-257,maskWrites=0,bodyThrows=false,next=0x10000,blocked=false,ready=true,scene=1,fog=false,fogEnd=200,fogColor=[1,1,1,1];
class Pointer{
 constructor(value){this.value=value;}
 add(offset){return new Pointer(this.value+offset);}
 isNull(){return !this.value;}
 equals(other){return this.value===other.value;}
 toString(){return String(this.value);}
 readPointer(){return memory.get(this.value)||new Pointer(0);}
 writePointer(value){memory.set(this.value,value);}
}
const ptr=value=>new Pointer(value),allocate=()=>{next+=0x100;return ptr(next);};
const world=ptr(100),ui=ptr(200),arms=ptr(300),player=ptr(400);
memory.set(player.value+0x48,arms);
positions.set(world.value,[0,1,0]);eulers.set(world.value,[5,20,0]);locals.set(arms.value,[.1,.2,.3]);
function native(rva){return (...args)=>{
 switch(rva){
 case 0xa7a06f0:return eulers.get(args[0].value).slice();
 case 0xa7a0764:eulers.set(args[0].value,Array.from(args[1]));return;
 case 0xa7a0a78:return [0,0,1];
 case 0xa7a01ec:positions.set(args[0].value,Array.from(args[1]));return;
 case 0xa7a0398:return locals.get(args[0].value).slice();
 case 0xa7a0548:locals.set(args[0].value,Array.from(args[1]));return;
 case 0xa8261c8:return blocked;
 case 0xa82b12c:return [0,1,-.7];
 case 0xa78ebc4:return !args[0].isNull();
 case 0x3d53d04:if(bodyThrows)throw Error('body unavailable');return args[0].value===300?armsOn:bodyOn;
 case 0x4413668:if(bodyThrows)throw Error('body unavailable');if(typeof args[1]!=='number')throw Error('expected an integer');armsOn=!!args[1];return;
 case 0x6812f1c:if(bodyThrows)throw Error('body unavailable');if(typeof args[1]!=='number')throw Error('expected an integer');bodyOn=!!args[1];return;
 case 0xa744354:return true;
 case 0xa77dd70:return args[0];
 case 0xa7844f0:return bodyLayer;
 case 0xa784ac8:return bodyActive;
 case 0xa725fb0:return maskValue;
 case 0xa726124:maskWrites++;maskValue=args[1];return;
 case 0x9647044:{const result=allocate();handles.add(result.value);return result;}
 case 0x9647058:handles.delete(args[0].readPointer().value);return;
 case 0xa7458ec:return fog;
 case 0xa745a64:fog=!!args[0];return;
 case 0xa745d48:return fogEnd;
 case 0xa745eb0:fogEnd=args[0];return;
 case 0xa74603c:return fogColor.slice();
 case 0xa7461e0:fogColor=Array.from(args[0]);return;
 default:throw Error('Unknown native '+rva.toString(16));
 }
};}
const settings={'Third Person':true,'Back Camera':true,Viewmodel:true,'Camera Distance':2,'Camera Height':.25,
 'Viewmodel X':.15,'Viewmodel Y':-.1,'Viewmodel Z':.2,Fog:true,'Fog Distance':80,'Fog Color':'#78909c'};
const context=vm.createContext({console,ptr,Process:{pointerSize:8},Memory:{alloc:allocate},
 Interceptor:{attach:(address,callbacks)=>{hooks.set(address.value,callbacks);return {detach:()=>hooks.delete(address.value)};}},
 apiContext:{native,settings,base:ptr(0),transform:object=>object,position:object=>positions.get(object.value),getCamera:()=>world,getLocalPlayer:()=>player,canRun:()=>ready,scene:()=>scene}
});
for(const name of ['engine','hooks','camera-effects','scene-effects'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function'),context);
vm.runInContext('globalThis.camera=createCameraEffects(apiContext);globalThis.sceneEffects=createSceneEffects(apiContext);',context);
function callback(rva,camera){const handler=hooks.get(rva),call={};handler.onEnter.call(call,[camera]);handler.onLeave.call(call);}
callback(0xa72b848,world);
assert.deepEqual(positions.get(world.value),[0,1.25,-2]);
assert.deepEqual(eulers.get(world.value),[5,200,0]);
assert.deepEqual(locals.get(arms.value),[.25,.1,.5]);
callback(0xa72b848,ui);callback(0xa72b9f8,ui);
assert.deepEqual(positions.get(world.value),[0,1.25,-2],'An unrelated camera must not restore the active world camera');
callback(0xa72b9f8,world);
assert.deepEqual(positions.get(world.value),[0,1,0]);assert.deepEqual(eulers.get(world.value),[5,20,0]);
assert.deepEqual(locals.get(arms.value),[.1,.2,.3]);assert.equal(handles.size,0);
blocked=true;callback(0xa72b848,world);
assert(Math.abs(positions.get(world.value)[2]+.58)<1e-9,'Camera must stop before a wall');
ready=false;context.camera.reset();assert.deepEqual(positions.get(world.value),[0,1,0]);assert.equal(handles.size,0);
// Third Person also shows the local body: its renderer is switched on for the render and the camera must see its layer; both are undone.
{
  const group=allocate(),mesh=allocate();memory.set(player.value+0x30,group);memory.set(group.value+0x38,mesh);
  ready=true;blocked=false;bodyOn=false;bodyLayer=8;maskValue=-257;maskWrites=0;           // -257 = every layer except layer 8
  callback(0xa72b848,world);
  assert.equal(bodyOn,true,'The body renderer is on while the third-person camera renders');
  assert.equal(maskValue&(1<<8),1<<8,'The camera now sees the body layer');
  assert.equal(armsOn,false,'The first-person arms renderer is off while the third-person camera renders');
  assert.deepEqual(locals.get(arms.value),[.25,.1,.5],'Nothing is moved to hide them: the Viewmodel offsets still apply');
  callback(0xa72b9f8,world);
  assert.equal(armsOn,true,'and returns to the game state after rendering');
  assert.equal(bodyOn,false,'The renderer returns to the game state after rendering');
  assert.equal(maskValue,-257,'The culling mask returns to the original value');
  assert.equal(handles.size,0,'The body group is not left pinned');
  maskValue=-1;maskWrites=0;callback(0xa72b848,world);callback(0xa72b9f8,world);
  assert.equal(maskWrites,0,'A camera that already sees the layer is not touched');
  bodyOn=true;callback(0xa72b848,world);callback(0xa72b9f8,world);assert.equal(bodyOn,true,'A renderer that was already on stays on');
  // A body that cannot be reached must never break the camera itself.
  bodyOn=false;bodyThrows=true;callback(0xa72b848,world);
  assert.deepEqual(positions.get(world.value),[0,1.25,-2],'The camera still moves when the body natives fail');
  callback(0xa72b9f8,world);bodyThrows=false;
  assert.deepEqual(positions.get(world.value),[0,1,0]);assert.equal(handles.size,0);
  memory.delete(player.value+0x30);
}
ready=true;context.sceneEffects.update();assert.equal(fog,true);assert.equal(fogEnd,80);
settings.Fog=false;context.sceneEffects.update();assert.equal(fog,false);assert.equal(fogEnd,200);assert.deepEqual(fogColor,[1,1,1,1]);
settings.Fog=true;context.sceneEffects.update();scene=2;fog=false;fogEnd=900;fogColor=[.2,.3,.4,1];
context.sceneEffects.reset();assert.equal(fogEnd,900,'A scene reset must not overwrite the next scene with old fog values');
context.camera.dispose();assert.equal(hooks.size,0);assert.equal(handles.size,0);
console.log('Camera isolation, pose/viewmodel restoration, collision handling, hook cleanup and scene fog ownership passed.');
