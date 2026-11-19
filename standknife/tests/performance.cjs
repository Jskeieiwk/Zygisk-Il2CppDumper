const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const context=vm.createContext({});
for(const name of ['aim-motion','performance'])vm.runInContext(fs.readFileSync('assets/'+name+'.js','utf8').replace(/^import .*;\n/gm,'').replaceAll('export function','function'),context);
vm.runInContext('globalThis.api={createWorkBudget,neededBones,hitboxBones,hitboxPoints};',context);
const budget=context.api.createWorkBudget();
for(let frame=0;frame<120;frame++){
 const now=Math.floor(frame*1000/60);budget.due('visual',now,100);budget.due('aim',now,1000/60);
}
assert.equal(budget.counts().visual,20);assert(budget.counts().aim>=118,'A 10 FPS overlay must not throttle the 60 Hz aim lane');
budget.due('visual',100000,100);assert(!budget.due('visual',100001,100),'A pause must not create catch-up bursts');
assert.equal(context.api.neededBones({'Aim assistance':true,'Aim Bone':0},false).length,1);
assert.equal(context.api.neededBones({'Player ESP':true,Boxes:true},true).length,1);
assert.deepEqual(Array.from(context.api.neededBones({'Player ESP':true,Boxes:true,'Aim assistance':true,'Hitbox Head':false,'Hitbox Body':true},true)),[0,2]);
// Hitboxes: any combination, nothing selected falls back to the head; multipoints add neighbours and derived points.
const {hitboxBones,hitboxPoints}=context.api;
assert.deepEqual(Array.from(hitboxBones({})),[0]);
assert.deepEqual(Array.from(hitboxBones({'Hitbox Head':false})),[0],'No hitbox selected means head');
assert.deepEqual(Array.from(hitboxBones({'Hitbox Head':true,'Hitbox Body':true,'Hitbox Legs':true})),[0,2,10,13]);
assert.deepEqual(Array.from(hitboxBones({'Hitbox Head':false,'Hitbox Legs':true,Multipoints:true})),[10,11,13,14]);
assert.deepEqual(Array.from(hitboxBones({'Hitbox Legs':true},true)),[2],'Knife always aims at the body');
const bones=Array(16).fill(null);bones[0]=[0,1.7,0];bones[1]=[0,1.5,0];bones[2]=[0,1.2,0];bones[3]=[0,0.9,0];bones[10]=[0.1,0.5,0];bones[13]=[-0.1,0.5,0];
const head=hitboxPoints(bones,{Multipoints:true});
assert.equal(head.length,3,'Head, neck and a crown point');assert(Math.abs(head[2].point[1]-1.82)<1e-9,'Crown is above the head: '+head[2].point);
const body=hitboxPoints(bones,{'Hitbox Head':false,'Hitbox Body':true,Multipoints:true});
assert.deepEqual(Array.from(body,p=>p.point[1]),[1.2,0.9,1.05]);
const legs=hitboxPoints(bones,{'Hitbox Head':false,'Hitbox Legs':true,Multipoints:true});
assert.equal(legs.length,2,'Missing leg bones are skipped');
bones[0]=[NaN,0,0];assert.equal(hitboxPoints(bones,{}).length,0,'Invalid bones are rejected');
assert.equal(context.api.neededBones({'Player ESP':true,Skeleton:true},true).length,16);
assert.equal(context.api.neededBones({'Player ESP':true,Nickname:true},true).length,0);
const fixture=require('./esp-frame-sync.cjs');
fixture.reset();
for(let frame=0;frame<60;frame++){
 fixture.setTime(10000+Math.floor(frame*1000/60));fixture.updatePlayers();fixture.capture();fixture.capture(0x500000);
}
const calls=fixture.calls();
assert((calls[0xa727e34]||0)>=50,'Camera matrices must refresh at render rate');
assert((calls[0xa7291ac]||0)<=2,'Verified matrix projection must avoid per-point native calls');
assert((calls[0xa77dbf4]||0)<=220,'Fresh origins must use at most one transform per player and projection frame');
assert((calls[0x3e03864]||0)<=21,'Session polling must be independent of extra/UI cameras');
assert((calls[0xa7298e8]||0)<=5,'Camera.main must be cached');
fixture.disable();fixture.clearCalls();
for(let frame=0;frame<60;frame++){fixture.setTime(12000+Math.floor(frame*1000/60));fixture.capture();}
assert.equal(fixture.calls()[0xa7291ac]||0,0);assert.equal(fixture.calls()[0xa7a0030]||0,0,'Idle overlays must not sample transforms');
console.log('60-frame simulation: '+(calls[0xa7291ac]||0)+' head/feet projections, '+(calls[0xa77dbf4]||0)+' transforms, '+(calls[0x3e03864]||0)+' session polls; idle projection/transform calls: 0.');
