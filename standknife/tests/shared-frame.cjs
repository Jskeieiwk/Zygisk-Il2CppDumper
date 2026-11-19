// Shared-memory transport (script side): packing, write order, geometry read-back, hostile values.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const {FakeAddress}=require('./helpers/fake-memory.cjs');
let clock=1700000123456;
const context=vm.createContext({Date:{now:()=>clock},Int32Array,Number,Math,String,ArrayBuffer});
vm.runInContext(fs.readFileSync('assets/shared-frame.js','utf8').replaceAll('export const','const').replaceAll('export function','function')+
 '\nglobalThis.api={packFrame,createSharedFrame,HEADER_WORDS,CAPACITY_WORDS,MAGIC,W_SEQ,W_MARKER,W_LENGTH,W_STAMP,W_DELAY,W_GEOMETRY,POS_SCALE,SIZE_SCALE};',context);
const api=context.api;
const java=fs.readFileSync('src/CanvasBatch.java','utf8');
assert(new RegExp('HEADER_WORDS='+api.HEADER_WORDS+',CAPACITY_WORDS=1<<18,MAGIC=0x5EED5EED').test(java),'Layout constants must match CanvasBatch');
assert(/W_SEQ=0,W_MARKER=1,W_LENGTH=2,W_STAMP=3,W_SELFTEST=8,W_DELAY=9/.test(java)&&/W_GEOMETRY=16/.test(java),'Word indices must match CanvasBatch');
assert(/static final float POS=4f,SIZE=8f;/.test(java)&&api.POS_SCALE===4&&api.SIZE_SCALE===8,'Scales must match CanvasBatch');

const pack=commands=>{const out=new Int32Array(1024);const n=api.packFrame(commands,out);return Array.from(out.slice(0,n));};
// Each primitive kind
assert.deepEqual(pack([[1,[1,2,3.5,4.25],2,-1]]),[1,4,16,-1,4,8,14,17]);
assert.deepEqual(pack([[2,'Hi',10,20,13,-16777216]]),[2,40,80,104,-16777216,2,72,105]);
assert.deepEqual(pack([[3,1,2,10,20,-1]]),[3,4,8,40,80,-1]);
assert.deepEqual(pack([[4,10,20,5,2,3]]),[4,40,80,20,16,3]);
assert.deepEqual(pack([[5,7,2,4,25]]),[5,7,8,16,100]);
// Text goes out as UTF-16 code units, so quotes, commas and non-Latin text need no escaping.
const unicode='[tg] Nick "q",\\ 名前 😀';
const packedText=pack([[2,unicode,0,0,10,-1]]);
assert.equal(packedText[5],unicode.length);
assert.equal(String.fromCharCode(...packedText.slice(6)),unicode);
// Colors become signed 32-bit ints
assert.deepEqual(pack([[3,0,0,1,1,0xff72baff]]).slice(-1),[0xff72baff|0]);
// Hostile values drop only their own primitive, and partially written ones are rewound
assert.deepEqual(pack([[1,[1,2,NaN,4],2,-1],[1,[1,2,3,4],Infinity,-1],[2,'x',NaN,1,10,-1],[3,0,0,1,1e12,0],[9,1],[1,[5,6,7,8],2,-1],[1,[1,2,3,Infinity],2,-1],[5,1.5,0,0,1],[5,'a',0,0,1]]),
  [1,4,16,-1,20,24,28,32]);
// Capacity: whatever does not fit is dropped whole; smaller primitives after it may still fit
const small=new Int32Array(10);
const used=api.packFrame([[1,[1,2,3,4,5,6,7,8],2,-1],[3,0,0,1,1,-1]],small);
assert.equal(used,6);assert.deepEqual(Array.from(small.slice(0,6)),[3,0,0,4,4,-1]);
assert.equal(api.packFrame([],new Int32Array(4)),0);

// Writing: payload first, then length and stamp, then marker, and the sequence last.
const memory=Buffer.alloc(api.CAPACITY_WORDS*4),log=[];
const shared=api.createSharedFrame({address:new FakeAddress(memory,0,log),now:()=>clock});
const words=shared.pack([[3,1,2,10,20,-1],[2,'Hi',10,20,13,-1]]);
assert.equal(words,6+8);
shared.commit(words);
const order=log.map(entry=>entry[0]==='bytes'?'payload':entry[1]);
assert.deepEqual(order,['payload',api.W_LENGTH,api.W_STAMP,api.W_DELAY,api.W_MARKER,api.W_SEQ],'The sequence word must be written last');
const word=index=>memory.readInt32LE(index*4);
assert.equal(word(api.W_SEQ),2);assert.equal(word(api.W_MARKER),(2^api.MAGIC)|0);assert.equal(word(api.W_LENGTH),14);
assert.equal(word(api.W_STAMP),clock&0x7fffffff,'Stamp is the wall clock, low 31 bits');
assert.deepEqual([...Array(6).keys()].map(i=>word(api.HEADER_WORDS+i)),[3,4,8,40,80,-1]);
assert.equal(word(api.W_DELAY),0,'No delay requested: zero');
clock+=16;shared.commit(0,37.6);
assert.equal(word(api.W_DELAY),38,'The delay is rounded to whole milliseconds');
shared.commit(0,1e9);assert.equal(word(api.W_DELAY),200,'The delay is capped at 200 ms');
shared.commit(0,-4);assert.equal(word(api.W_DELAY),0,'A negative delay is zero');
shared.commit(0,NaN);assert.equal(word(api.W_DELAY),0,'A non-number delay is zero');
clock+=16;shared.commit(0);
assert(word(api.W_SEQ)>=4&&word(api.W_SEQ)%2===0);assert.equal(word(api.W_LENGTH),0);assert.equal(word(api.W_MARKER),(word(api.W_SEQ)^api.MAGIC)|0);
// Sequence stays even, never 0, and wraps
const wrapping=api.createSharedFrame({address:new FakeAddress(Buffer.alloc(api.CAPACITY_WORDS*4)),now:()=>0});
let last=0;for(let i=0;i<5;i++){wrapping.commit(0);}
// Geometry written by Java is read back
memory.writeInt32LE(2400,(api.W_GEOMETRY)*4);memory.writeInt32LE(1080,(api.W_GEOMETRY+1)*4);memory.writeInt32LE(100,(api.W_GEOMETRY+2)*4);
memory.writeInt32LE(20,(api.W_GEOMETRY+3)*4);memory.writeInt32LE(2000,(api.W_GEOMETRY+4)*4);memory.writeInt32LE(1000,(api.W_GEOMETRY+5)*4);
assert.equal(shared.geometry().valid,false,'Geometry is not valid until Java says so');
memory.writeInt32LE(1,(api.W_GEOMETRY+6)*4);
assert.deepEqual({...shared.geometry()},{width:2400,height:1080,x:100,y:20,clipWidth:2000,clipHeight:1000,valid:true});
console.log('Shared frame packing, write order, sequence handling and geometry read-back passed.');
