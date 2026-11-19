const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const memory=new Map(),handles=new Set(),calls=[];
let next=10000,dead=false,smoothing=.4;
class Pointer{
 constructor(value){this.value=value;}
 add(offset){return new Pointer(this.value+offset);}
 isNull(){return !this.value;}
 equals(other){return this.value===other.value;}
 toString(){return String(this.value);}
 readPointer(){return memory.get(this.value)||new Pointer(0);}
 writePointer(value){memory.set(this.value,value);}
}
const ptr=value=>new Pointer(value),allocate=()=>{next+=100;return ptr(next);},local=ptr(1),controls=ptr(2);
memory.set(controls.value+0x30,local);
function native(rva){return (...args)=>{
 switch(rva){
 case 0x384b910:return controls;
 case 0x502d194:return smoothing;
 case 0x5030890:smoothing=args[1];return;
 case 0xa78ebc4:return !args[0].isNull()&&!dead;
 case 0x95103ec:return allocate();
 case 0x9647044:{const result=allocate();handles.add(result.value);return result;}
 case 0x9647058:handles.delete(args[0].readPointer().value);return;
 case 0x3848d14:calls.push('disable');return;
 case 0x384a7fc:calls.push('enable');return;
 default:throw Error('Unexpected native '+rva.toString(16));
 }
};}
const context=vm.createContext({console,ptr,Process:{pointerSize:8},Memory:{alloc:allocate,allocUtf8String:allocate},apiContext:{native}});
for(const name of ['engine','auto-stop'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function'),context);
vm.runInContext('globalThis.api=createAutoStop(apiContext);',context);
assert.equal(context.api.active(),false);context.api.update(local,true);assert.equal(context.api.active(),true);context.api.update(local,true);assert.deepEqual(calls,['disable'],'Movement-disable requests must not churn each frame');
context.api.update(local,false);assert.equal(context.api.active(),false);assert.deepEqual(calls,['disable','enable']);
memory.set(controls.value+0x30,ptr(99));context.api.update(local,true);assert.equal(calls.length,2,'Never disable another player controller');
memory.set(controls.value+0x30,local);context.api.update(local,true);context.api.reset();assert.deepEqual(calls,['disable','enable','disable','enable']);
assert.equal(handles.size,0);
context.api.update(local,true);dead=true;context.api.reset();assert.equal(handles.size,0,'Destroyed controls must release managed roots without a native movement call');
console.log('Auto Stop request ownership, player filtering, release, destroyed objects and reset passed.');

dead=false;
const touch=ptr(50),area=ptr(60),rawSettings={'Raw Input':true};
memory.set(controls.value+0x38,touch);memory.set(touch.value+0x28,area);
context.rawContext={native,settings:rawSettings,getLocalPlayer:()=>local,canRun:()=>true};
vm.runInContext(fs.readFileSync('assets/raw-input.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function')+'\nglobalThis.raw=createRawInput(rawContext);',context);
context.raw.update();assert.equal(smoothing,0);rawSettings['Raw Input']=false;context.raw.update();
assert.equal(smoothing,.4);assert.equal(handles.size,0);
vm.runInContext(fs.readFileSync('assets/safe-mode.js','utf8').replaceAll('export function','function').replaceAll('export const','const')+'\nglobalThis.safe=applySafeMode;',context);
const preset={'Safe Mode':true,Chams:true,'Ghost Chams':true,Trigger:true,'Knife Bot':true,Boxes:true,'Aim assistance':true};
assert.equal(context.safe(preset),true);assert.equal(preset.Chams,false);assert.equal(preset.Trigger,false);assert.equal(preset['Knife Bot'],false);
assert.equal(preset.Boxes,true);assert.equal(preset['Aim assistance'],true);assert.equal(context.safe(preset),false);
console.log('Raw Input restoration and Safe Mode preset passed.');
