// Menu sliders, module defaults and numeric bounds for the new controls must agree.
const assert=require('node:assert/strict'),fs=require('node:fs');
const module_=fs.readFileSync('assets/module.js','utf8'),menu=fs.readFileSync('menu.html','utf8');
const controls={'Molotov Radius Scale':{min:25,max:400,step:5,value:200},'Smoke Radius Scale':{min:25,max:400,step:5,value:55},'ESP Sync Frames':{min:0,max:4,step:.25,value:0}};
for(const [key,expected] of Object.entries(controls)){
  const bounds=new RegExp("'"+key+"':\\[(-?[\\d.]+),(-?[\\d.]+)\\]").exec(module_);
  assert(bounds,key+' must be in numericSettings');
  assert.deepEqual([Number(bounds[1]),Number(bounds[2])],[expected.min,expected.max],key+' bounds');
  const initial=new RegExp("'"+key+"':\\s*([\\d.]+)").exec(module_);
  assert(initial&&Number(initial[1])===expected.value,key+' default in settings');
  assert(menu.includes('data-option="'+key+'"')||menu.includes("'"+key+"'"),key+' must have a menu control');
  // The slider's own range must not exceed what the module accepts.
  const slider=new RegExp("'"+key+"',[^\\]]*?,(-?[\\d.]+),(-?[\\d.]+),([\\d.]+),(-?[\\d.]+)\\]|data-option=\"ESP Sync Frames\" min=\"(-?[\\d.]+)\" max=\"(-?[\\d.]+)\" step=\"([\\d.]+)\"").exec(menu);
  assert(slider,key+' slider definition not found');
}
assert(/min="0" max="4" step="0.25"/.test(menu),'ESP Delay slider range');
// The delay converts frames to milliseconds with the current frame rate and is capped.
const body=/function espDelayMs\(\)\{[\s\S]*?\n\}/.exec(module_)[0];
const vm=require('node:vm');
let fps=50;
const context=vm.createContext({settings:{'ESP Sync Frames':1},gameFrameMeter:{value:()=>fps},Date,Math});
vm.runInContext(body+'\nglobalThis.espDelayMs=espDelayMs;',context);
assert.equal(context.espDelayMs(),20,'1 frame at 50 FPS is 20 ms');
context.settings['ESP Sync Frames']=2.5;assert.equal(context.espDelayMs(),50);
fps=null;assert.equal(context.espDelayMs(),42,'Unknown frame rate falls back to 60 FPS');
fps=2;assert.equal(context.espDelayMs(),42,'An implausible frame rate falls back too');
fps=1000;context.settings['ESP Sync Frames']=4;assert.equal(context.espDelayMs(),4);
context.settings['ESP Sync Frames']=0;assert.equal(context.espDelayMs(),0,'Zero disables the delay');
context.settings['ESP Sync Frames']=4;fps=6;assert.equal(context.espDelayMs(),200,'The delay is capped at 200 ms');
console.log('New menu controls, defaults, bounds and the frames-to-milliseconds delay conversion agree.');
