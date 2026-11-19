// A batched frame must not call Canvas, Paint or Java at all. On the device every Frida->Java call costs far more than the
// drawing itself (players with avatars, circles and rectangles were drawn through the bridge on every frame).
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
const source=fs.readFileSync('assets/module.js','utf8');
const batchSource=source.slice(source.indexOf('  // Rectangles, circles and avatars also join the frame batch'),source.indexOf('  function text(canvas, value, x, y, size, tint) {'));
assert(batchSource.includes('function batchAvatar'),'module.js batch helpers were not found');

let bridgeCalls=0;const bridgeLog=[];
const touched=name=>(...args)=>{bridgeCalls++;bridgeLog.push(name);return {call:()=>{bridgeCalls++;bridgeLog.push(name+'.call');return null;}};};
const javaClass=()=>new Proxy({},{get:(_target,name)=>name==='$new'?touched('$new'):name==='TONE_PROP_ACK'||name==='TONE_PROP_BEEP'?{value:1}:{overload:touched('overload'),call:touched('call')}});
const forbidden=label=>new Proxy({},{get:(_target,name)=>{bridgeCalls++;bridgeLog.push(label+'.'+String(name));return ()=>{};}});

// ---- real module.js helpers: frame batch commands and the avatar registry
const registered=[];let setAvatarFails=false;
const moduleContext=vm.createContext({
  frameCommands:null,console,
  overlay:{setAvatar:(id,bytes,x,y,w,h)=>{if(setAvatarFails)throw Error('decode failed');registered.push({id,bytes:Array.from(bytes),x,y,w,h});}},
  Java:{array:(_type,values)=>values},Math,Array
});
vm.runInContext(batchSource+'\nglobalThis.helpers={batchFill,batchCircle,batchAvatar};',moduleContext);
const helpers=moduleContext.helpers;

// ---- real screen-overlay.js with the batch hooks wired like module.js wires them
const context=vm.createContext({Math,Date,console,Array});
vm.runInContext(fs.readFileSync('assets/screen-overlay.js','utf8').replaceAll('export function','function')+'\nglobalThis.createScreenRenderer=createScreenRenderer;',context);

const settings=Object.fromEntries(['Draw FOV','Kill Flash','Bullet Tracers','Hit Marker','Sniper Crosshair','Custom Scope','Kill Particles','Damage Marker','Hit Logs','Target HUD',
  'Check Recoil','Show Avatar','Money','Ping','Bomb Flag','Player Nades','Knife Bot'].map(name=>[name,true]));
Object.assign(settings,{'Enemy Color':'#efa8c5','Text Size':13,'Line Width':2,'Aim FOV':10,'Scope Radius':70,'Team Filter':false,'Hit Sound':false,'Kill Sound':false});
const commands=[];
const text=(canvas,value,x,y,size,tint)=>commands.push([2,String(value),x,y,size,tint|0]);
const line=(canvas,x1,y1,x2,y2,tint,width)=>commands.push([1,[x1,y1,x2,y2],width,tint|0]);
const wire=extra=>context.createScreenRenderer({
  Java:{use:()=>javaClass(),retain:x=>x,array:(_t,v)=>v},jstr:forbidden('jstr'),Paint:forbidden('Paint'),Style:forbidden('Style'),paint:forbidden('paint'),
  text,line,color:()=>-1,settings,getLocalTeam:()=>1,...extra
});
// The hooks are the real module.js helpers; they append to moduleContext.frameCommands.
const renderer=wire({batchFill:helpers.batchFill,batchCircle:helpers.batchCircle,batchAvatar:helpers.batchAvatar});
const frameCommands=moduleContext.frameCommands=[];

const now=Date.now();
const players=new Map(Array.from({length:5},(_,i)=>[i,{t:now,team:2,x:300+i*200,y:400,z:10,h:120,bw:50,sw:1280,sh:720,distance:20+i,health:90,maxHealth:100,name:'P'+i,weapon:'AKR',
  money:900,ping:30,bomb:i===0,grenades:['HE'],avatar:{id:'owner'+i,bytes:[1,2,200,255],crop:i%2?{x:0,y:0,width:4,height:4}:null}}]));
const frame={events:[{id:1,kind:'hit',t:now-50,damage:30,point:{x:100,y:100,sw:1280,sh:720},name:'P1'},{id:2,kind:'kill',t:now-100,damage:100,point:{x:120,y:90,sw:1280,sh:720},name:'P2'}],
  traces:[{a:[10,10],b:[200,200],alpha:.5}],sw:1280,sh:720,aim:{fov:60,fire:{ready:false,samples:1}},sniperWeapon:true,scopeActive:true,
  recoil:{vertical:1,horizontal:2,camera:3}};

function renderOnce(){
  commands.length=0;frameCommands.length=0;
  renderer.draw(null,frame,players,2400,1080,1.8);
  for(const item of players.values())renderer.playerExtras(null,item,100,200,60,120,1.8,23,-1);
}
renderOnce();
const kinds=new Set(frameCommands.map(command=>command[0]));
assert(kinds.has(3)&&kinds.has(4)&&kinds.has(5),'Rectangles, circles and avatars must all be batched: '+[...kinds]);
assert.equal(frameCommands.filter(command=>command[0]===5).length,5,'Every player avatar is a batch primitive');
assert.equal(registered.length,5,'Each avatar is registered with Java exactly once');
assert.deepEqual(registered[0].bytes,[1,2,-56,-1],'Avatar bytes are converted to signed bytes');
assert.deepEqual([registered[1].x,registered[1].y,registered[1].w,registered[1].h],[0,0,4,4],'Crop is passed to Java');
assert.deepEqual([registered[0].w,registered[0].h],[0,0],'No crop means the whole image');
const calls=bridgeCalls;
for(let i=0;i<50;i++)renderOnce();
assert.equal(bridgeCalls,calls,'Steady-state frames must make no Canvas, Paint or Java calls: '+bridgeLog.slice(calls).slice(0,6).join(','));
assert.equal(registered.length,5,'Avatars are not registered again while unchanged');
assert(commands.length>0,'Text and lines are still produced');

// A replaced avatar (new object for the same owner) is registered again under a new id; the old id is not reused.
const old=frameCommands.find(command=>command[0]===5)[1];
players.get(0).avatar={id:'owner0',bytes:[9,9],crop:null};
renderOnce();
assert.equal(registered.length,6);
assert.notEqual(registered.at(-1).id,old);

// A decode failure skips that avatar silently (logged once) and never touches Canvas.
setAvatarFails=true;
players.get(1).avatar={id:'owner1',bytes:[7],crop:null};
const before=frameCommands.length;
renderOnce();
assert(frameCommands.filter(command=>command[0]===5).length===4,'A failed avatar is skipped');
renderOnce();
assert.equal(bridgeCalls,calls,'A failed avatar must not fall back to direct Canvas calls');
setAvatarFails=false;

// Fallback (JavaScript renderer): without batch hooks the same code draws through the canvas. Only then are calls expected.
const direct=[];
const fallback=context.createScreenRenderer({
  Java:{use:()=>javaClass(),retain:x=>x,array:(_t,v)=>v},jstr:String,Paint:{},Style:{FILL:{value:1},STROKE:{value:2}},
  paint:{setStyle(){direct.push('style');},setColor(){direct.push('color');},setStrokeWidth(){direct.push('width');}},
  text:()=>{},line:()=>{},color:()=>-1,settings:{...settings,'Show Avatar':false,'Kill Flash':false,'Kill Particles':false,'Hit Logs':false,'Target HUD':false},getLocalTeam:()=>1
});
const canvas={drawCircle(){direct.push('circle');},drawRect:{overload:()=>({call:()=>direct.push('rect')})}};
fallback.draw(canvas,frame,players,2400,1080,1.8);
assert(direct.includes('circle'),'Without a batch the fallback still draws circles directly');

// module.js helper contract
moduleContext.frameCommands=null;
assert.equal(helpers.batchFill(1,2,3,4,5),false,'No batch, no batching');
assert.equal(helpers.batchCircle(1,2,3,4,5),false);
assert.equal(helpers.batchAvatar({id:'x',bytes:[1],crop:null},0,0,10),false);
moduleContext.frameCommands=[];moduleContext.overlay={};
assert.equal(helpers.batchAvatar({id:'y',bytes:[1],crop:null},0,0,10),false,'An overlay without setAvatar (JavaScript fallback View) is not batched');
console.log('A batched frame makes no Canvas/Paint/Java calls; avatars register once; failures and the fallback behave.');
