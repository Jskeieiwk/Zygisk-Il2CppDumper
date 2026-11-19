// Label widths: each (size, character) is measured through Java once; text that changes every frame costs no bridge calls.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const source=fs.readFileSync('assets/module.js','utf8');
const slice=source.slice(source.indexOf('  // Label widths are the sum of per-character widths.'),source.indexOf('  function color(value) {'));
assert(slice.includes('function measureText'),'measureText was not found');
let measured=[],sizeCalls=0;
const context=vm.createContext({
  textWidths:new Map(),String,Number,Map,
  setTextSize:()=>{sizeCalls++;},
  drawString:value=>value,
  textPaint:{measureText:{overload:()=>({call:(_paint,character)=>{measured.push(character);return character===' '?4:character==='m'?11:7;}})}}
});
vm.runInContext(slice+'\nglobalThis.measureText=measureText;',context);
const {measureText}=context;
assert.equal(measureText('12 m',26),7+7+4+11,'Width is the sum of character widths');
assert.deepEqual(measured,['1','2',' ','m'],'Each distinct character is measured once');
measured=[];
assert.equal(measureText('13 m',26),7+7+4+11);
assert.deepEqual(measured,['3'],'Only the new character reaches Java');
measured=[];
for(let meters=14;meters<400;meters++)measureText(meters+' m',26);
assert.deepEqual(measured,['4','5','6','7','8','9','0'],'A changing distance label measures each digit once, then never again');
measured=[];
for(let i=0;i<1000;i++)measureText('99 m',26);
assert.equal(measured.length,0,'A repeated label is a plain cache hit');
assert.equal(measureText('12 m',20),7+7+4+11);assert.equal(measured.length,4,'Another text size has its own table');
assert.equal(measureText('',26),0);
assert.equal(measureText('名',26),7,'Non-Latin characters are measured like any other');
console.log('Text width measurement: one Java call per new character, none for changing numbers.');
