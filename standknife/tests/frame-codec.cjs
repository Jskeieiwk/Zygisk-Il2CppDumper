// Packed overlay frames: round trip within the quantization step, hostile values, and size.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const context=vm.createContext({});
vm.runInContext(fs.readFileSync('assets/frame-codec.js','utf8').replaceAll('export const','const').replaceAll('export function','function')+
 '\nglobalThis.api={encodeFrame,POS_SCALE,SIZE_SCALE};',context);
const {encodeFrame,POS_SCALE,SIZE_SCALE}=context.api;
assert.equal(POS_SCALE,4);assert.equal(SIZE_SCALE,8);
// The Java side must use the same scales.
const java=fs.readFileSync('src/CanvasBatch.java','utf8');
assert(/static final float POS=4f,SIZE=8f;/.test(java),'CanvasBatch scales must match frame-codec.js');
// Same arithmetic as CanvasBatch.drawPacked.
function decode(text){
  return JSON.parse(text).map(c=>c[0]===1
    ?{kind:'lines',points:c[1].map(v=>v/POS_SCALE),width:c[2]/SIZE_SCALE,color:c[3]}
    :{kind:'text',text:c[1],x:c[2]/POS_SCALE,y:c[3]/POS_SCALE,size:c[4]/SIZE_SCALE,color:c[5]});
}
const source=[
  [1,[100.123456789,200.987654321,300.5,400.25],3.6,-16777216],
  [1,[0,0,2399.9,1079.9],2,0xff72baff|0],
  [2,'[tg] Nick "q"\\ 名前',912.4567,311.9999,26.0000001,-1]
];
const packed=encodeFrame(source);
const decoded=decode(packed);
assert.equal(decoded.length,3);
decoded[0].points.forEach((v,i)=>assert(Math.abs(v-source[0][1][i])<=1/POS_SCALE/2+1e-9));
assert(Math.abs(decoded[0].width-3.6)<=1/SIZE_SCALE/2+1e-9);
assert.equal(decoded[0].color,-16777216);assert.equal(decoded[1].color,0xff72baff|0);
assert.equal(decoded[2].text,'[tg] Nick "q"\\ 名前','Text must survive JSON escaping unchanged');
assert(Math.abs(decoded[2].x-912.4567)<=.125+1e-9&&Math.abs(decoded[2].y-311.9999)<=.125+1e-9&&Math.abs(decoded[2].size-26)<=.0625+1e-9);
// Packed numbers are integers (the cheap path in QuickJS and in org.json).
assert(JSON.parse(packed)[0][1].every(Number.isInteger)&&Number.isInteger(JSON.parse(packed)[2][2]));
// Non-finite values drop only their own primitive.
const hostile=encodeFrame([[1,[1,2,NaN,4],2,-1],[1,[1,2,3,4],Infinity,-1],[2,'ok',NaN,1,10,-1],[2,'ok',1,2,10,-1],[3,'unknown'],[1,[5,6,7,8],2,-1]]);
const kept=decode(hostile);
assert.deepEqual(kept.map(c=>c.kind),['text','lines'],'Only the valid primitives remain, in order');
assert.equal(kept[0].text,'ok');assert.deepEqual(kept[1].points,[5,6,7,8]);
assert.equal(encodeFrame([]),'[]');
// Rectangles, circles and avatars (kinds 3, 4, 5), scaled like CanvasBatch.drawPacked expects.
const shapes=JSON.parse(encodeFrame([[3,1,2.5,10,20.125,-1],[4,10,20,5,2,0xff72baff|0],[5,7,2,4,25]]));
assert.deepEqual(shapes,[[3,4,10,40,81,-1],[4,40,80,20,16,0xff72baff|0],[5,7,8,16,100]]);
// Hostile values drop only their own shape; an avatar id must be an integer.
const hostileShapes=JSON.parse(encodeFrame([[3,NaN,0,1,1,0],[4,1,2,Infinity,1,0],[5,1.5,0,0,1],[5,'a',0,0,1],[5,3,NaN,0,1],[3,0,0,1,1,5]]));
assert.deepEqual(hostileShapes,[[3,0,0,4,4,5]]);

// Size: a realistic frame of 5 players is far smaller than the float JSON it replaces.
const frame=[];
for(let player=0;player<5;player++){
  const points=[];for(let i=0;i<60;i++)points.push(Math.random()*2400+Math.random());
  frame.push([1,points,2.7,-16777216],[1,points,1.8,-1],[2,'Player '+player,Math.random()*2000,Math.random()*1000,26.31,-1]);
}
assert(encodeFrame(frame).length<JSON.stringify(frame).length*.5,'Packed frames must be less than half the float JSON size');
console.log('Frame codec round trip, hostile values and size checks passed.');
