const assert = require('node:assert/strict');
const fs = require('node:fs');
const vm = require('node:vm');

let now = 1000;
let slowCapture=false;
let pan = 0;
let playerShift=0;
const floats=new Map();let allocated=0x900000;
const hooks = new Map(), nativeCalls={};
const cameraAddress = 0x200000;
const firstPlayer = 0x300000;
const secondPlayer = 0x400000;
class Pointer {
  constructor(value) { this.value = value; }
  add(value) { return new Pointer(this.value + value); }
  isNull() { return this.value === 0; }
  toString() { return String(this.value); }
  equals(other) { return this.value===other.value; }
  readPointer() { return new Pointer(0); }
  readU8() { return 1; }
  readFloat(){return floats.get(this.value)||0;}
}
function pointer(value) { return new Pointer(value); }
function storeMatrix(storage,values){values.forEach((v,i)=>floats.set(storage.value+i*4,v));}
const native = new Map([
  [0xa727e34, (_cam,storage)=>storeMatrix(storage,[1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1])],
  [0xa72800c, (_cam,storage)=>storeMatrix(storage,[2/1280,0,0,0,0,2/720,0,0,0,0,1,0,-1+pan/640,-1+100/360,0,1])],
  [0xa77dbf4, object => object],
  [0xa7a0030, object => object.value === cameraAddress ? [0,0,0] : [object.value === firstPlayer ? 10 : 20+playerShift,0,10]],
  [0xa7298e8, () => pointer(cameraAddress)],
  [0xa7291ac, (_camera, position) => [position[0] + pan, position[1] + 100, position[2]]],
  [0xa73b93c, () => 1280],
  [0xa73ba94, () => {if(slowCapture)now+=60;return 720;}],
  [0x3e03864,()=>1], [0xa7aefb8,()=>1], [0xa79a61c,()=>now]
]);
const context = vm.createContext({
  Process: { arch:'arm64', id:1, findRangeByAddress:() => ({protection:'r-x'}) },
  Interceptor: { attach:(address, handler) => hooks.set(address.value, handler) },
  NativeFunction:function(address) {
    const handler=native.get(address.value)||(()=>{throw Error('Unexpected native call '+address);});
    return (...args)=>{nativeCalls[address.value]=(nativeCalls[address.value]||0)+1;return handler(...args);};
  },
  Java:{ perform:() => {} },
  Memory:{alloc:()=>{allocated+=64;return pointer(allocated);}},
  __WATERMARK_FONTS__:{},
  __RENDER_DEX__:"",
  createFrameMeter:()=>({frame(){},value:()=>null}),
  createRawInput:()=>({update(){},reset(){}}),
  createCameraEffects:()=>({reset(){},dispose(){}}),
  createSceneEffects:()=>({update(){},reset(){}}),
  createAim:()=>({step(){},reset(){},needsUpdate:()=>false,status:()=>({})}),
  createVisualFeatures:()=>({suspend(){},addDetails(){},updateChams(){},removePlayer(){},screenFrame:()=>({events:[],traces:[]}),report:(name,error)=>{throw error;}}),
  Date:{ now:() => now },
  ptr:pointer,
  console,
  setInterval:() => 0
});
for(const name of ['aim-motion','performance','esp-projection','matrix-projection','esp-motion','engine','world-visuals','net-position'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function').replaceAll('export const','const'),context);
vm.runInContext(fs.readFileSync('assets/hooks.js','utf8').replaceAll('export function','function'),context);
vm.runInContext(fs.readFileSync('assets/session.js','utf8').replaceAll('export function','function'),context);
vm.runInContext(fs.readFileSync('assets/module.js','utf8').replace(/^import .*;\n/gm,'') + `
moduleBase=ptr(0);
settings.Boxes=true;
installEsp();
globalThis.snapshots=()=>Array.from(projected.values());
globalThis.setWorld=world=>{screenFrame.world=world;};
globalThis.worldSnapshot=()=>screenFrame.world;
globalThis.invalidations=0;
overlay={postInvalidateOnAnimation(){globalThis.invalidations++;},postInvalidate(){globalThis.invalidations++;}};
`,context);
function updatePlayer(value) {
  const handler=hooks.get(0x49ec32c), call={};
  handler.onEnter.call(call,[pointer(value)]);
  handler.onLeave.call(call);
}
function capture(camera=cameraAddress) { const hook=hooks.get(0xa72b920),call={};hook.onEnter.call(call,[pointer(camera)]);hook.onLeave.call(call); }
capture();
const emptyInvalidations=context.invalidations;
now+=50;capture();
assert.equal(context.invalidations,emptyInvalidations,'Static overlays without players must not redraw at 60 Hz');
now+=50;capture();
assert.equal(context.invalidations,emptyInvalidations+1,'Static overlays still refresh on the next 10 Hz data sample');
updatePlayer(firstPlayer);
updatePlayer(secondPlayer);
now+=100;capture();
assert.deepEqual(Array.from(context.snapshots(), item=>Math.round(item.x)),[10,20]);
// A camera turn must move both boxes on the very next frame, even without
// another player update. The previous 75ms per-player cache failed this.
now += 100;
pan = 200;
capture(0x500000); // A weapon/UI camera must never overwrite the world snapshot.
assert.deepEqual(Array.from(context.snapshots(),item=>Math.round(item.x)),[10,20]);
capture();
assert.deepEqual(Array.from(context.snapshots(), item=>Math.round(item.x)),[210,220]);
assert.equal(new Set(Array.from(context.snapshots(),item=>item.t)).size,1);
// A camera turn between 10 Hz player samples must move the whole ESP on
// the next 60 Hz render frame, without touching native player transforms.
const sampled=now,oldInvalidations=context.invalidations;
now+=17;pan+=80;
const oldTransforms=nativeCalls[0xa77dbf4]||0;
capture();
assert.deepEqual(Array.from(context.snapshots(),item=>Math.round(item.x)),[290,300]);
assert.equal((nativeCalls[0xa77dbf4]||0)-oldTransforms,3,'Camera and both live player origins must refresh on a projection frame');
assert.equal(context.invalidations,oldInvalidations+1,'The new projection must request an Android draw');
assert(now-sampled<100,'The reprojection must run before the next player-data sample');
pan-=80;
context.setWorld({t:now,sw:1280,sh:720,objects:[{pos:[5,0,10],point:[5+pan,100,1]}],rings:[{worldPoints:[[1,0,10],[2,0,10]],points:[[1+pan,100,1],[2+pan,100,1]]}]});
now+=17;pan+=40;capture();
assert.equal(Math.round(context.worldSnapshot().objects[0].point[0]),245,'World markers must follow the latest camera without a new scene scan');
assert.equal(Math.round(context.worldSnapshot().rings[0].points[1][0]),242,'World radius geometry must follow the latest camera');
pan-=40;
updatePlayer(secondPlayer);
// Returned objects must disappear immediately and cannot reappear next frame.
hooks.get(0x49ebb54).onEnter([pointer(firstPlayer)]);
now+=17;
capture();
assert.deepEqual(Array.from(context.snapshots(),item=>Math.round(item.x)),[220]);
now += 300;
capture();
assert.equal(context.snapshots().length,0);
// A sampling pass that blocks the game thread for 40 ms or more is reported with a per-phase breakdown.
{
  const lines=[],original=console.log;console.log=message=>{if(String(message).startsWith('CLOUD:capture-slow'))lines.push(String(message));else original(message);};
  slowCapture=true;now+=100;capture();slowCapture=false;now+=100;capture();
  console.log=original;
  assert.equal(lines.length,1,'Exactly the slow pass is reported: '+lines.join('|'));
  assert(/^CLOUD:capture-slow totalMs=\d+ players=\d+ effects=\d+ aim=\d+ world=\d+ worldScanMs=\d+ tracked=\d+ bones=\d+$/.test(lines[0]),lines[0]);
  assert(Number(/totalMs=(\d+)/.exec(lines[0])[1])>=60);
}
// Dormant data is reprojected from saved world positions without reading freed objects.
vm.runInContext("settings.Dormant=true;",context);
const diagnostics=[],originalLog=console.log;console.log=message=>{if(String(message).startsWith('CLOUD:player-'))diagnostics.push(String(message));else originalLog(message);};
updatePlayer(secondPlayer);now+=100;capture();
now+=300;pan+=50;capture();
console.log=originalLog;
// The moment an enemy stops being updated is logged once, with what the ESP last showed, so a frozen ESP can be explained from the log.
assert.deepEqual(diagnostics.map(line=>line.split(' ')[0]),['CLOUD:player-live','CLOUD:player-dormant'],'Each change is logged once, in order: '+diagnostics.join('|'));
assert(/^CLOUD:player-dormant key=\d+ silentMs=\d+ dormantSetting=true lastScreen=-?\d+,-?\d+ depth=-?[\d.]+ dist=[\d.]+ tracked=\d+$/.test(diagnostics[1]),diagnostics[1]);
assert.equal(context.snapshots()[0].dormant,true);
assert.equal(Math.round(context.snapshots()[0].x),270);
now+=2100;capture();
assert.equal(context.snapshots().length,0);
vm.runInContext('workBudget.reset();trackedPlayers.clear();worldRecords.clear();projected=new Map();settings.Dormant=false;',context);
now+=100;pan=0;playerShift=0;updatePlayer(secondPlayer);capture();
playerShift=1;now+=100;updatePlayer(secondPlayer);capture();
const sampleX=context.snapshots()[0].x;
now+=50;playerShift=1.5;capture();
assert(context.snapshots()[0].x>sampleX,'ESP must advance moving players between 10 Hz samples');
console.log('Frame synchronization, camera filtering, pool return and dormant-position checks passed.');

module.exports={
 reset(){playerShift=0;vm.runInContext("workBudget.reset();trackedPlayers.clear();worldRecords.clear();projected=new Map();settings.Dormant=false;settings.Boxes=true;",context);for(const key of Object.keys(nativeCalls))delete nativeCalls[key];},
 setTime(value){now=value;},updatePlayers(){updatePlayer(firstPlayer);updatePlayer(secondPlayer);},capture,
 calls:()=>({...nativeCalls}),clearCalls(){for(const key of Object.keys(nativeCalls))delete nativeCalls[key];},
 disable(){vm.runInContext('for(const key of Object.keys(settings))if(typeof settings[key]==="boolean")settings[key]=false;',context);}
};
