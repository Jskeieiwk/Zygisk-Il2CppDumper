const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const context=vm.createContext({Math,Number});
vm.runInContext(fs.readFileSync('assets/watermark.js','utf8').replaceAll('export function','function')+
 '\nglobalThis.api={drawWatermark,watermarkLayout,createFrameMeter};',context);
const text=[],rectangles=[];
const painter={measure:(value,font,size)=>({width:value.length*size*.6,height:size}),
 text:(x,y,value,font,size,color)=>text.push({x,y,value,font,size,color}),
 rect:(x,y,width,height)=>rectangles.push({x,y,width,height}),line:()=>{}};
const box=context.api.drawWatermark(painter,{fps:60,time:'12:34:56'},1.15);
assert(text.some(item=>item.value==='Cloud'));
assert(!text.some(item=>item.value.toLowerCase().includes('menace')));
assert.equal(rectangles.length,2);
assert(Math.abs(box.height-34.5)<1e-6);
for(const item of text)assert(item.x>=0 && item.x<box.width);
const time=text.filter(item=>item.font==='numeric').slice(-8);
assert.equal(time.map(item=>item.value).join(''),'12:34:56');
assert.equal(time[5].color,'#969696');
const meter=context.api.createFrameMeter();
for(let i=0;i<=60;i++)meter.frame(1000+i*1000/60);
assert(Math.abs(meter.value(2000)-60)<.01);
assert.equal(meter.value(4000),null);
const source=fs.readFileSync('assets/module.js','utf8');
assert(!source.includes('now-last<330'));
assert(source.includes('setOnClickListener(WatermarkClick.$new())'));
assert(source.includes("console.log('CLOUD:watermark-ready')"));
console.log('Watermark brand, sizing, clock, FPS and menu entry checks passed.');
