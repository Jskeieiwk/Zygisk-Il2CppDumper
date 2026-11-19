const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const moduleBase=0x10000000,registration=moduleBase+0xae4fe48;
const counts=new Map([[0,0x5fae],[16,0x3c16],[32,0x1548e],[48,0x10e59],[64,0x1db5d],[80,0x5d05],[96,0x5d05]]);
class Pointer{
 constructor(value){this.value=value;}
 add(value){return new Pointer(this.value+value);}
 sub(value){return new Pointer(this.value-value);}
 toString(){return String(this.value);}
 readU64(){return {toNumber:()=>counts.get(this.value-registration)||0};}
}
const data={base:new Pointer(registration-0x100000+40),size:0x300000,protection:'r--'};
const executable={base:new Pointer(moduleBase),size:0x8000000,protection:'r-x'},calls=[];
const context=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/module-locator.js','utf8').replace('export async function','async function')+'\nglobalThis.locate=locateGameModule;',context);
(async()=>{
 const base=await context.locate({Process:{arch:'arm64',enumerateRanges:()=>[executable,data],findRangeByAddress:address=>address.value===moduleBase+0x6402be0?{protection:'r-x'}:null},Memory:{
  scanSync(){throw Error('Synchronous scans must never run');},
  scan(base,size,pattern,callbacks){calls.push({base,size,pattern});queueMicrotask(()=>{
    if(registration>=base.value&&registration+104<=base.value+size)callbacks.onMatch(new Pointer(registration));
    callbacks.onComplete();
  });}
 },log(){}});
 assert.equal(base.value,moduleBase);assert.equal(calls.length,1,'Registration spanning a chunk boundary must be found without scanning executable pages');
 assert.equal(calls[0].base.value,data.base.value);assert(calls[0].size<=0x100000+104);
 assert(calls[0].pattern.includes('16 3c 00 00'));
 console.log('Asynchronous data-first lookup, duplicate range elimination, chunk overlap and registration validation passed.');
})().catch(error=>{console.error(error);process.exitCode=1;});
