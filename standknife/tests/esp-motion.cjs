const assert=require('node:assert/strict');
const fs=require('node:fs');
const vm=require('node:vm');
const context=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/esp-motion.js','utf8').replaceAll('export function','function')+
  ';globalThis.api={estimateVelocity,predictOrigin,moveBone};',context);
const {estimateVelocity,predictOrigin,moveBone}=context.api;
const velocity=estimateVelocity([0,0,0],[1,0,0],100);
assert.deepEqual(Array.from(velocity),[10,0,0]);
const state={pos:[1,0,0],velocity,t:1000};
assert.equal(predictOrigin(state,1050)[0],1.5,'Moving player follows the next camera frame');
assert.equal(predictOrigin(state,1200)[0],1.8,'Prediction is capped at 80 ms');
assert.equal(predictOrigin({...state,dormant:true},1050)[0],1,'Dormant marker remains still');
assert.deepEqual(Array.from(moveBone([1,2,3],[0,0,0],[1.5,0,0])),[2.5,2,3]);
assert.deepEqual(Array.from(estimateVelocity([0,0,0],[100,0,0],100)),[0,0,0],
  'Teleport must not produce an ESP overshoot');
assert.deepEqual(Array.from(estimateVelocity([0,0,0],[1,0,0],500)),[0,0,0],
  'A stale sample must not be extrapolated');
console.log('ESP motion prediction, teleport and stale-sample checks passed.');
