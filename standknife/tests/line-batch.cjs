const assert=require('node:assert/strict');
const fs=require('node:fs');
const vm=require('node:vm');
const context=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/line-batch.js','utf8').replace('export function','function')+';globalThis.createLineBatch=createLineBatch;',context);
const batch=context.createLineBatch();
for(let player=0;player<7;player++){
  const x=player*20;
  batch.box(-16777216,4,x,1,x+10,40,0);
  batch.box(0xffe9a8c5,2,x,1,x+10,40);
  for(let bone=0;bone<15;bone++)batch.add(0xffe9a8c5,2,x,bone,x+4,bone+1);
  batch.add(0xffe9a8c5,2,500,700,x+5,40);
}
batch.add(0xffe9a8c5,2,NaN,0,1,1);
const groups=batch.drain();
assert.equal(groups.length,2,'Seven players with one tint use two Canvas calls');
assert.equal(groups[0].layer,0,'Black box outlines render before color');
assert.equal(groups[0].points.length,7*4*4);
assert.equal(groups[1].points.length,7*(4+15+1)*4,'Boxes, skeletons, and snaplines share one color batch');
assert.deepEqual(Array.from(batch.drain()),[],'Batches clear after a draw');
console.log('Player line batching checks passed.');
