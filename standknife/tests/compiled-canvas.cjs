const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const source=fs.readFileSync('assets/module.js','utf8');
const render=source.slice(source.indexOf('  function renderEsp('),source.indexOf('  const EspView ='));
const text=source.slice(source.indexOf('  function text(canvas,'),source.indexOf('  const screenRenderer='));
let submissions=[];
const context=vm.createContext({
 espReady:true,espEnabled:()=>true,Date,localTeam:1,
 settings:{'Player ESP':true,Boxes:true,Skeleton:true,Health:true,Nickname:true,Weapons:true,Distance:true,'Max Distance':300,'Text Size':13,'Line Width':2},
 projected:new Map(Array.from({length:7},(_,i)=>[i,{t:Date.now(),distance:10,team:2,sw:1280,sh:720,x:100+i*140,y:500,z:10,h:120,health:100,maxHealth:100,name:'Player '+i,weapon:'AKR',bones:[[100,500,10],[100,450,10]]}])),
 screenFrame:{},boneEdges:[[0,1]],color:()=>-1,measureText:value=>value.length*8,line(){},
 frameCommands:null,deferCommands:false,deferredCommands:null,compiledCanvas:{draw:(_canvas,value)=>submissions.push(JSON.parse(value))},jstr:String,
 screenRenderer:{draw(){},playerExtras(){},idle(){}},drawWorldOverlay(){},console,
 paint:{setStyle(){throw Error('Compiled frame must not call Paint through Frida');}},Style:{STROKE:{value:0}}
});
vm.runInContext(fs.readFileSync('assets/line-batch.js','utf8').replace('export function','function'),context);
vm.runInContext(text+render+';renderEsp({},1280,720);',context);
assert.equal(submissions.length,1,'Seven players must use one compiled draw submission');
assert.equal(submissions[0].filter(c=>c[0]===2).length,21,'Health, name and weapon/distance captions must remain');
assert(submissions[0].some(c=>c[0]===1&&c[1].length>7*16),'Boxes and skeletons retain their geometry');
assert(submissions[0].every(c=>c[0]===1||c[0]===2));
assert.equal(context.frameCommands,null);
// Picture path: the same primitives are handed back to the caller instead of crossing the bridge.
const direct=submissions[0];
submissions=[];context.deferCommands=true;
vm.runInContext('renderEsp({},1280,720);',context);
assert.equal(submissions.length,0,'A deferred frame must not call the static draw bridge');
assert.deepEqual(JSON.parse(JSON.stringify(context.deferredCommands)),direct,'Deferred primitives must equal the directly drawn ones');
assert.equal(context.frameCommands,null);
// The wrapper used by the Picture path: returns the primitives, and a failing render must not leave a half-built batch behind.
vm.runInContext(source.slice(source.indexOf('  function renderEspDeferred('),source.indexOf('  function renderEsp(')),context);
context.deferCommands=false;
const returned=vm.runInContext('renderEspDeferred({},1280,720)',context);
assert.deepEqual(JSON.parse(JSON.stringify(returned)),direct,'renderEspDeferred must return the same primitives');
assert.equal(context.deferCommands,false);assert.equal(context.deferredCommands,null);
context.screenRenderer.draw=()=>{throw Error('draw failed');};
assert.throws(()=>vm.runInContext('renderEspDeferred({},1280,720)',context),/draw failed/);
assert.equal(context.frameCommands,null,'A failed render must clear the half-built batch');
assert.equal(context.deferCommands,false,'A failed render must leave deferral off');
console.log('Compiled Canvas frame batching and label/geometry preservation passed.');
