const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const ctx=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/matrix-projection.js','utf8').replace('export function','function')+';globalThis.projector=createMatrixProjector;',ctx);
const projection=[1,0,0,0,0,1,0,0,0,0,-1,-1,0,0,-.2,0];
const view=[1,0,0,0,0,1,0,0,0,0,-1,0,0,0,0,1];
let project=ctx.projector(view,projection,1280,720);
assert.deepEqual(Array.from(project([0,0,10])),[640,360,10]);
assert.equal(project([5,0,10])[0],960);
assert.equal(project([0,0,-10])[2],-10,'Behind-camera points retain negative depth');
assert.equal(project([0,0,0]),null,'Near-zero homogeneous divisor must not explode');
// A 90 degree camera rotation must transform the full world geometry,
// including bones away from the head/feet axis, with perspective.
const turned=[0,0,-1,0,0,1,0,0,-1,0,0,0,0,0,0,1];
project=ctx.projector(turned,projection,1280,720);
assert.deepEqual(Array.from(project([10,0,0])),[640,360,10]);
assert.equal(project([10,0,5])[0],320);
assert.equal(ctx.projector(Array(16).fill(NaN),projection,1280,720),null);
console.log('Perspective, camera rotation, behind-camera and near-plane checks passed.');
