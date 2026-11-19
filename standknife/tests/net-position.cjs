// Network position of obstructed enemies: snapshot-only calibration, use only while obstructed, diagnostic dump, staleness.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const context=vm.createContext({Math,Number});
vm.runInContext(fs.readFileSync('assets/net-position.js','utf8').replaceAll('export function','function').replaceAll('export const','const')+
  '\nglobalThis.api={createNetPosition,NET_CANDIDATES};',context);
const {createNetPosition,NET_CANDIDATES}=context.api;
const n=NET_CANDIDATES.length,TRANSLATION_44=NET_CANDIDATES.findIndex(([s,o])=>s==='translation'&&o===0x44);
// snapshot+0x14 (index 0) carries the network position; translation+0x44 copies the transform, as measured on the device.
function values(pos,netPos=pos){const out=Array(n).fill(null);out[0]=netPos.slice();out[1]=[0.1,0,0.2];out[2]=[NaN,0,0];out[TRANSLATION_44]=pos.slice();return out;}
{
  const logs=[],net=createNetPosition({log:m=>logs.push(m)});
  const stale=[10,1,20];
  assert.equal(net.resolve('a',stale,values(stale),true,0),null,'Uncalibrated: nothing is substituted');
  assert(logs[0].startsWith('CLOUD:net-pos-obstructed key=a chosen=-1 transform=10.00,1.00,20.00 candidates=10.00,1.00,20.00 |'),logs[0]);
  for(let i=0;i<29;i++){const pos=[i,1,i*2];net.observe(pos,values(pos),false);}
  assert.equal(net.chosen(),-1,'Not before minSamples');
  for(let i=0;i<5;i++){const pos=[i,1,i];net.observe(pos,values(pos,[99,99,99]),true);}
  assert.equal(net.chosen(),-1,'Obstructed samples do not count');
  net.observe([3,1,3],values([3,1,3]),false);
  assert.equal(net.chosen(),0,'The snapshot field is chosen, never the translation copy of the transform');
  assert(logs.some(m=>m.startsWith('CLOUD:net-pos-calibrated source=snapshot offset=0x14 ratio=1.00')));
  const moved=[14,1,25];
  assert.deepEqual(net.resolve('a',stale,values(stale,moved),true,1000),moved,'Obstructed: the network position replaces the stale transform');
  assert.equal(net.resolve('a',stale,values(stale,moved),false,1000),null,'Visible players keep their transform');
  assert.equal(net.resolve('a',stale,values(stale,[500,1,500]),true,1000),null,'An implausible jump is rejected');
  assert.equal(net.resolve('a',stale,values(stale,[NaN,1,1]),true,1000),null,'Non-finite values are rejected');
  assert.equal(net.resolve('a',stale,null,true,1000),null,'Missing movement controller');
  const dumps=logs.filter(m=>m.startsWith('CLOUD:net-pos-obstructed key=a')).length;
  assert.equal(dumps,2,'The dump is rate-limited to one line per 500 ms per player');
}
// Only translation fields match: nothing is chosen (they follow the transform and freeze with it).
{
  const net=createNetPosition();
  for(let i=0;i<100;i++){const pos=[i,0,i];const v=values(pos,[i+9,0,i]);net.observe(pos,v,false);}
  assert.equal(net.chosen(),-1,'A translation-only match is not selectable');
}
// Freeze tracking: an obstructed player standing still is stale; a runner that stops dead is detected sooner and carried
// along its last velocity for at most one second; visible or moving again is live.
{
  const net=createNetPosition();
  assert.equal(net.track('k',[1,0,1],true,0).stale,false);
  assert.equal(net.track('k',[1,0,1.01],true,300).stale,false,'Not yet');
  const slow=net.track('k',[1,0,1.02],true,450);
  assert.equal(slow.stale,true,'Frozen for 450 ms while obstructed');assert.equal(slow.frozenAt,0);assert.equal(slow.predicted,null,'No velocity, no prediction');
  assert.equal(net.track('k',[1,0,1.02],false,600).stale,false,'Visible players are never stale');
  // running at 5 m/s along +x, sampled every 100 ms, then the data freezes
  const run=createNetPosition();
  for(let i=0;i<=5;i++)assert.equal(run.track('r',[i*0.5,2,0],true,i*100).stale,false);
  assert.equal(run.track('r',[2.5,2,0],true,650).stale,false,'150 ms still is not a freeze yet');
  const early=run.track('r',[2.5,2,0],true,700);
  assert.equal(early.stale,true,'A runner frozen for 200 ms is stale');
  assert.equal(early.frozenAt,500);
  assert(Math.abs(early.predicted[0]-3.5)<1e-9&&early.predicted[1]===2&&Math.abs(early.predicted[2])<1e-9,'Carried 200 ms at 5 m/s: '+early.predicted);
  const late=run.track('r',[2.5,2,0],true,4000);
  assert(Math.abs(late.predicted[0]-7.5)<1e-9,'Prediction stops after one second: '+late.predicted);
  assert.equal(late.predictedMs,1000);
  assert.equal(run.track('r',[9,2,0],true,4100).stale,false,'New data ends the freeze');
  // a teleport-sized step is not used as a velocity
  const jump=createNetPosition();
  jump.track('j',[0,0,0],true,0);jump.track('j',[3,0,0],true,100);
  const after=jump.track('j',[3,0,0],true,600);
  assert.equal(after.stale,true);assert.equal(after.predicted,null,'30 m/s is not a running speed');
  jump.forget('j');assert.equal(jump.track('j',[3,0,0],true,2000).stale,false,'Forgotten players start over');
}
console.log('Network position: snapshot-only calibration, obstructed-only substitution, dump rate limit and staleness passed.');
