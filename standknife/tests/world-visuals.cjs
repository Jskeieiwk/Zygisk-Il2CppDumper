const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const memory=new Map(),strings=new Map(),positions=new Map(),handles=new Map(),dead=new Set();
let next=0x100000,now=1000,gameTime=110,decodeWrong=false,matchReady=true;
class Pointer{
 constructor(value){this.value=value;}
 add(offset){return new Pointer(this.value+offset);}
 isNull(){return this.value===0;}
 equals(other){return this.value===other.value;}
 toString(){return String(this.value);}
 readPointer(){return memory.get(this.value)||new Pointer(0);}
 writePointer(value){memory.set(this.value,value);}
 readS32(){return memory.get(this.value)||0;}
 readU8(){return this.readS32();}
 readFloat(){return this.readS32();}
 readU64(){return {toNumber:()=>this.readS32()};}
}
const ptr=value=>new Pointer(value);
function allocate(){const result=ptr(next);next+=0x100;return result;}
function array(values){const result=allocate();memory.set(result.value+0x18,values.length);values.forEach((value,index)=>memory.set(result.value+0x20+index*8,value));return result;}
function parameter(name){const result=allocate(),text=allocate();strings.set(text.value,name);memory.set(result.value+0x20,text);return result;}
const camera=allocate(),item=allocate(),grenade=allocate(),effect=allocate(),particles=allocate(),bomb=allocate(),renderer=allocate();
const weaponParameter=parameter('AKR'),grenadeParameter=parameter('HE'),effectParameter=parameter('Smoke'),bombParameter=parameter('C4');
memory.set(item.value+0x78,weaponParameter);memory.set(grenade.value+0x30,grenadeParameter);
memory.set(grenade.value+0xc8,91);memory.set(grenade.value+0x6c,0);
memory.set(effect.value+0x50,92);memory.set(effect.value+0x38,effectParameter);memory.set(effect.value+0x28,particles);memory.set(effectParameter.value+0x54,5);
memory.set(bomb.value+0x20,bombParameter);memory.set(bombParameter.value+0x114,45);
positions.set(camera.value,[0,1,0]);positions.set(item.value,[10,0,10]);positions.set(grenade.value,[3,2,8]);positions.set(particles.value,[6,0,12]);positions.set(bomb.value,[1,0,10]);
const scene={WeaponDropController:[item],DroppedGrenadeController:[grenade],GrenadeEffectController:[effect],PlantedBombController:[bomb]};
let disposedBomb=false,probeMode=0,traceCalls=0,effectPlaying=true,playingThrows=false;
const scanCounts={};
function native(address){return (...args)=>{
 switch(address){
 case 0x95103ec:{const result=allocate();strings.set(result.value,strings.get(args[0].value));return result;}
 case 0x9823338:{const result=allocate();strings.set(result.value,strings.get(args[0].value));return result;}
 case 0x9647044:{const result=allocate();handles.set(result.value,args[0]);return result;}
 case 0x9647058:handles.delete(args[0].readPointer().value);return;
 case 0xa78ebc4:return !args[0].isNull()&&!dead.has(args[0].value);
 case 0xa790358:{const type=strings.get(args[0].value).split(',')[0].split('.').pop();scanCounts[type]=(scanCounts[type]||0)+1;return array(scene[type]||[]);}
 case 0xa77e310:return renderer;
 case 0xa81e2f4:if(playingThrows)throw Error('isPlaying unavailable');return effectPlaying;
 case 0x519d65c:return true;
 case 0x5198c84:return disposedBomb;
 case 0x519b1d0:return false;
 case 0x5be4e34:return [45,0];
 case 0x519d9e0:return [100,0];
 case 0x5e84d48:return decodeWrong?7:args[0][0];
 case 0xa799c08:return gameTime;
 case 0xa7a0a78:return [0,0,1];
 case 0xa8261c8:traceCalls++;return probeMode>0;
 case 0xa82b000:return ptr(probeMode===2&&traceCalls%2===0?999:998);
 case 0xa82b12c:return traceCalls%2===0?[0,1,2.5]:[0,1,2];
 default:throw Error('Unexpected native RVA '+address.toString(16));
 }
};}
const settings={'Item ESP':true,Grenades:true,'Off-screen Nades':true,'Smoke Radius':true,'Molotov Radius':false,'Player Nades':true,'Bomb Timer':true,'Grenade Glow':true,'Max Distance':300,'Smoke Radius Scale':100,'Molotov Radius Scale':100};
const context=vm.createContext({console,Date:{now:()=>now},ptr,Process:{pointerSize:8},
 Memory:{alloc:allocate,allocUtf8String:value=>{const p=allocate();strings.set(p.value,value);return p;}},
 apiContext:{native,settings,transform:object=>object,position:object=>positions.get(object.value)||[0,0,0],project:(_camera,point)=>[point[0],point[1],point[2]],readManagedString:p=>strings.get(p.value)||'',canRun:()=>matchReady}
});
for(const name of ['engine','world-visuals','world-overlay'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function').replaceAll('export const','const'),context);
vm.runInContext('globalThis.api=createWorldVisuals(apiContext);globalThis.math={worldRing,validatedBombTime,screenPoint,edgeArrow};',context);
let snapshot=context.api.snapshot(camera);
assert.equal(snapshot.objects.length,3);
assert.equal(snapshot.rings.length,1);assert.equal(snapshot.rings[0].points.length,17);
assert.equal(snapshot.bombs[0].seconds,35);
assert.equal(typeof snapshot.scanMs,'number','The scene scan time is reported so a slow scan can be found'); 
// Rings follow the effect: gone as soon as its particle system stops, back when it plays again.
const radiusOf=ring=>Math.hypot(ring.worldPoints[0][0]-6,ring.worldPoints[0][2]-12);
assert(Math.abs(radiusOf(snapshot.rings[0])-5)<1e-9,'Scale 100 percent keeps the configured radius');
effectPlaying=false;snapshot=context.api.snapshot(camera);
assert.equal(snapshot.rings.length,0,'A finished effect must not leave its radius on screen');
effectPlaying=true;snapshot=context.api.snapshot(camera);
assert.equal(snapshot.rings.length,1,'A playing effect shows its radius');
// Radius scale per kind, in percent: smoke (id 92 here) uses Smoke Radius Scale.
settings['Smoke Radius Scale']=55;snapshot=context.api.snapshot(camera);
assert(Math.abs(radiusOf(snapshot.rings[0])-5*.55)<1e-9,'Smoke radius scales down: '+radiusOf(snapshot.rings[0]));
settings['Smoke Radius Scale']=100;settings['Molotov Radius Scale']=300;snapshot=context.api.snapshot(camera);
assert(Math.abs(radiusOf(snapshot.rings[0])-5)<1e-9,'The molotov scale does not touch smoke');
// If the game cannot be asked whether the effect plays, the ring behaves as before.
playingThrows=true;effectPlaying=false;snapshot=context.api.snapshot(camera);
assert.equal(snapshot.rings.length,1,'Without isPlaying the ring stays visible (previous behavior)');
playingThrows=false;effectPlaying=true;
settings['Molotov Radius Scale']=100;
assert.equal(context.api.glowPlayers().size,1);
const held=handles.size;
for(let i=0;i<30;i++){now+=510;context.api.snapshot(camera);}
assert.equal(handles.size,held,'Scene scanning must not accumulate GC roots');
dead.add(grenade.value);snapshot=context.api.snapshot(camera);
assert(!snapshot.objects.some(item=>item.kind==='grenade'),'Destroyed/pool-returned grenades must disappear before the next scan');
assert.equal(context.api.glowPlayers().size,0);
disposedBomb=true;assert.equal(context.api.snapshot(camera).bombs.length,0);
disposedBomb=false;decodeWrong=true;assert.equal(context.api.snapshot(camera).bombs[0].seconds,null,'Invalid decoding must never create a guessed countdown');
const player=allocate(),inventory=allocate(),list=allocate(),weapon=allocate();
memory.set(player.value+0xf0,inventory);memory.set(inventory.value+0x60,list);
memory.set(list.value+0x18,1);memory.set(list.value+0x10,array([weapon]));memory.set(weapon.value+0xb8,grenadeParameter);memory.set(grenadeParameter.value+0x18,91);
assert.deepEqual(Array.from(context.api.inventory(player)),['HE']);
memory.set(list.value+0x18,999999);assert.equal(context.api.inventory(player).length,0);
settings.Penetration=true;settings['Aim Range']=150;traceCalls=0;probeMode=0;assert.equal(context.api.snapshot(camera).penetration.clear,true);
traceCalls=0;probeMode=1;assert.equal(context.api.snapshot(camera).penetration.thickness,.5);
traceCalls=0;probeMode=2;assert.equal(context.api.snapshot(camera).penetration.thickness,null,'Different entry/exit colliders must never produce a guessed thickness');
matchReady=false;assert.equal(context.api.snapshot(camera).objects.length,0);
context.api.reset();assert.equal(handles.size,0,'Leaving a scene must release every managed root');
// Effect registry: with the Play hook active the scene is never scanned for effects (that scan froze the game 45-300 ms every 1.5 s).
{
  matchReady=true;settings.Penetration=false;
  const before=scanCounts.GrenadeEffectController||0;
  context.api.setEffectHook(true);
  now+=3000;
  let s=context.api.snapshot(camera);
  assert.equal(s.rings.length,0,'Nothing is registered yet, so no ring');
  now+=3000;context.api.snapshot(camera);
  assert.equal(scanCounts.GrenadeEffectController||0,before,'The effect group is not scanned while the hook is active');
  context.api.noteEffect(effect);
  now+=200;s=context.api.snapshot(camera);
  assert.equal(s.rings.length,1,'A registered effect shows its ring');
  const roots=handles.size;context.api.noteEffect(effect);
  assert.equal(handles.size,roots,'Registering the same controller again pins it only once');
  effectPlaying=false;now+=200;s=context.api.snapshot(camera);
  assert.equal(s.rings.length,0,'A registered effect that stopped playing hides its ring');
  effectPlaying=true;
  dead.add(effect.value);now+=200;s=context.api.snapshot(camera);
  assert.equal(s.rings.length,0,'A destroyed controller disappears');
  assert.equal(handles.size,roots-1,'A destroyed controller is unpinned');
  dead.delete(effect.value);
  context.api.noteEffect(effect);now+=200;assert.equal(context.api.snapshot(camera).rings.length,1,'A Play registers the controller again');
  now+=91000;assert.equal(context.api.snapshot(camera).rings.length,0,'A controller that has not been played for 90 s is dropped');
  assert.equal(scanCounts.GrenadeEffectController||0,before,'Still no effect scans with the hook active');
  // Without the hook the scene scan is the fallback again.
  context.api.setEffectHook(false);now+=15000;context.api.snapshot(camera);
  assert(scanCounts.GrenadeEffectController>before,'Without the hook the scene scan is the fallback');
}
// Scan cost throttles the scan: the pause is 50 times the last scan's duration (1.5 s to 12 s).
{
  let tick=now;const clock={now:()=>tick};
  const slowContext=vm.createContext({console,Date:clock,ptr,Process:{pointerSize:8},Memory:context.Memory,apiContext:context.apiContext});
  for(const name of ['engine','world-visuals'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function').replaceAll('export const','const'),slowContext);
  vm.runInContext('globalThis.api=createWorldVisuals(apiContext);',slowContext);
  const countBefore=scanCounts.DroppedGrenadeController||0;
  // every scan advances the clock by 300 ms (a slow FindObjectsOfType)
  const original=slowContext.apiContext.native;
  slowContext.apiContext.native=address=>{const fn=original(address);return (...args)=>{if(address===0xa790358)tick+=300;return fn(...args);};};
  vm.runInContext('globalThis.api=createWorldVisuals(apiContext);',slowContext);
  matchReady=true;
  slowContext.api.snapshot(camera);const first=scanCounts.DroppedGrenadeController||0;
  tick+=2000;slowContext.api.snapshot(camera);assert.equal(scanCounts.DroppedGrenadeController||0,first,'A slow scan is not repeated after 1.5 s');
  tick+=5000;slowContext.api.snapshot(camera);assert.equal(scanCounts.DroppedGrenadeController||0,first,'Still waiting (about 8 s since the scan): four 300 ms scans mean a 12 s pause');
  tick+=5000;slowContext.api.snapshot(camera);assert(scanCounts.DroppedGrenadeController>first,'It is repeated once the pause (capped at 12 s) has passed');
}
assert.equal(context.math.validatedBombTime(110,120,45,45),null);
assert.equal(context.math.validatedBombTime(200,100,45,45),null);
assert.equal(context.math.worldRing([0,0,0],NaN).length,0);
assert.deepEqual({...context.math.screenPoint([1280,720,1],640,360,1280,720)},{x:640,y:0,z:1});
const calls=[];context.drawWorldOverlay({settings,text:(_c,label)=>calls.push(label),line(){},color:x=>x},{},{t:now,sw:100,sh:100,objects:[{kind:'grenade',point:[200,50,1],name:'HE',distance:10}],rings:[],bombs:[{seconds:null}]},100,100,1);
assert(calls.includes('HE'));assert(calls.includes('C4: таймер недоступен'));
console.log('World scanning, managed ownership, pool reuse, grenade glow/radii/inventory, safe bomb timing and projection passed.');
