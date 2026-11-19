// Frame publisher: one Frida->Java call per frame, geometry refresh cadence, string fallback, failure rollback.
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
let now=1000;
const context=vm.createContext({Date:{now:()=>now},Number,Error});
vm.runInContext(fs.readFileSync('assets/overlay-frame.js','utf8').replaceAll('export function','function')+'\nglobalThis.api={createFramePublisher};',context);
const {createFramePublisher}=context.api;

function harness({layout={width:2400,height:1080},aligned=false,rejectJsStrings=false}={}){
  const calls=[],logs=[],costs=[];
  const overlay={
    size:{...layout},status:1,
    getWidth(){calls.push('getWidth');return this.size.width;},
    getHeight(){calls.push('getHeight');return this.size.height;},
    frame(w,h,x,y,cw,ch,commands){
      calls.push('frame');
      if(rejectJsStrings&&typeof commands==='string')throw new TypeError('argument types do not match');
      this.last={w,h,x,y,cw,ch,commands};
      return (w===this.size.width&&h===this.size.height)?this.status:0;
    },
    clearFrame(){calls.push('clearFrame');}
  };
  const geometry={t:0,canvasWidth:0,canvasHeight:0,width:0,height:0,x:0,y:0,aligned:false};
  const state={commands:null,renderError:null,rendered:[]};
  let refreshes=0,javaStrings=0;
  const publish=createFramePublisher({
    getOverlay:()=>overlay,geometry,ensureSurface(){calls.push('ensureSurface');},
    refreshGeometry(width,height){
      refreshes++;geometry.t=now;geometry.canvasWidth=width;geometry.canvasHeight=height;geometry.aligned=aligned;
      if(aligned){geometry.x=100;geometry.y=20;geometry.width=2000;geometry.height=1000;}
    },
    render(width,height){
      calls.push('render');state.rendered.push([width,height]);
      if(state.renderError)throw state.renderError;
      return state.commands;
    },
    encode:commands=>'ENC:'+JSON.stringify(commands),
    toJavaString:text=>{javaStrings++;return {javaString:text};},
    onCost:elapsed=>costs.push(elapsed),log:message=>logs.push(message)
  });
  return {publish,calls,logs,costs,overlay,geometry,state,stats:()=>({refreshes,javaStrings})};
}
const bridge=calls=>calls.filter(name=>['getWidth','getHeight','frame','clearFrame'].includes(name));

// Steady state: exactly one overlay call per frame; geometry is re-read only every 1500 ms.
{
  const h=harness();h.state.commands=[[1,[0,0,1,1],2,3]];
  assert.equal(h.publish(),true);
  assert.deepEqual(bridge(h.calls),['getWidth','getHeight','frame'],'The first frame reads the overlay size once');
  assert.equal(h.overlay.last.commands,'ENC:[[1,[0,0,1,1],2,3]]','Commands are passed as a plain JS string');
  assert.deepEqual([h.overlay.last.w,h.overlay.last.h,h.overlay.last.x,h.overlay.last.y,h.overlay.last.cw,h.overlay.last.ch],[2400,1080,0,0,0,0]);
  assert.deepEqual(h.state.rendered[0],[2400,1080]);
  h.calls.length=0;
  for(let frame=0;frame<100;frame++){now+=8;assert.equal(h.publish(),true);}
  assert.deepEqual(bridge(h.calls),Array(100).fill('frame'),'One hundred frames inside 1500 ms cost exactly one hundred bridge calls');
  assert.equal(h.stats().refreshes,1,'Geometry must not be re-read inside the interval');
  now+=1500;h.publish();
  assert.equal(h.stats().refreshes,2,'Geometry is re-read after the interval');
  assert.equal(h.stats().javaStrings,0,'No explicit Java string is created while JS strings are accepted');
  assert.equal(h.costs.length,102,'Every frame reports its cost');
  assert(/^renderMs=\d+\.\d packMs=\d+\.\d javaMs=\d+\.\d transport=call$/.test(h.publish.takePhases()),'Phase timings are reported for the telemetry line');
}
// Game-surface alignment: offset, clip and render size come from the surface, not the overlay.
{
  const h=harness({aligned:true});
  h.publish();
  assert.deepEqual([h.overlay.last.w,h.overlay.last.h,h.overlay.last.x,h.overlay.last.y,h.overlay.last.cw,h.overlay.last.ch],[2400,1080,100,20,2000,1000]);
  assert.deepEqual(h.state.rendered[0],[2000,1000]);
}
// Empty or missing primitives publish an empty frame without encoding anything.
{
  const h=harness();
  h.state.commands=null;h.publish();assert.equal(h.overlay.last.commands,null);
  h.state.commands=[];h.publish();assert.equal(h.overlay.last.commands,null);
}
// Java rejects stale geometry (returns 0): nothing is published, and the next frame re-reads the geometry.
{
  const h=harness();h.state.commands=[[2,'x',0,0,10,-1]];h.publish();
  now+=8;h.overlay.size={width:1200,height:540};
  h.calls.length=0;
  assert.equal(h.publish(),false,'A stale size must not count as published');
  assert.deepEqual(bridge(h.calls),['frame']);
  now+=8;h.calls.length=0;
  assert.equal(h.publish(),true,'The next frame adopts the new size');
  assert.deepEqual(bridge(h.calls),['getWidth','getHeight','frame']);
  assert.deepEqual(h.state.rendered.at(-1),[1200,540]);
}
// A view that is not laid out yet draws nothing and never calls frame().
{
  const h=harness({layout:{width:0,height:0}});
  assert.equal(h.publish(),false);
  assert(!h.calls.includes('frame'));
}
// Render failure: the old frame is cleared, nothing is called into Java, logging is bounded, and a later frame works.
{
  const h=harness();h.state.renderError=Error('boom');
  assert.equal(h.publish(),false);
  assert.deepEqual(bridge(h.calls).slice(-2),['getHeight','clearFrame']);
  assert(h.logs[0].startsWith('CLOUD:picture-frame-error')&&h.logs[0].includes('boom'));
  for(let i=0;i<20;i++){now+=8;h.publish();}
  assert.equal(h.logs.length,8,'Repeated failures must stop logging after eight lines');
  h.state.renderError=null;h.state.commands=[[2,'x',0,0,10,-1]];now+=8;
  assert.equal(h.publish(),true,'A frame after a failure must publish normally');
}
// A failing frame() (for example a JSON error in Java) also clears the old frame.
{
  const h=harness();h.state.commands=[[1,[0,0,1,1],2,3]];
  h.overlay.frame=function(){h.calls.push('frame');throw new Error('json');};
  assert.equal(h.publish(),false);
  assert.deepEqual(bridge(h.calls).slice(-2),['frame','clearFrame']);
  assert.equal(h.stats().javaStrings,1,'A string argument failure is retried once with a Java string before giving up');
  assert.equal(h.logs.filter(line=>line.startsWith('CLOUD:frame-string-fallback')).length,0,'A failure that the retry does not cure is not a string-type fallback');
  // The failure was not about strings, so the next frame goes back to plain JS strings.
  h.overlay.frame=function(w,h2,x,y,cw,ch,commands){h.calls.push('frame');this.last={commands};return 1;};
  h.calls.length=0;now+=8;assert.equal(h.publish(),true);
  assert.equal(typeof h.overlay.last.commands,'string');assert.equal(h.stats().javaStrings,1);
}
// If the bridge refuses JS strings, one retry with an explicit Java string succeeds and the choice is remembered.
{
  const h=harness({rejectJsStrings:true});h.state.commands=[[2,'x',0,0,10,-1]];
  assert.equal(h.publish(),true,'The retry publishes the frame');
  assert.equal(h.logs.length,1);assert(h.logs[0].startsWith('CLOUD:frame-string-fallback'));
  assert.deepEqual(h.overlay.last.commands,{javaString:'ENC:[[2,"x",0,0,10,-1]]'});
  h.calls.length=0;now+=8;
  assert.equal(h.publish(),true);
  assert.deepEqual(bridge(h.calls),['frame'],'Later frames use the Java string directly, without a failed attempt first');
  assert.equal(h.logs.length,1,'The fallback is logged once');
}
// Shared-memory transport: no overlay call at all per frame; geometry comes from the memory Java keeps current.
{
  const calls=[],written=[];
  const surface={valid:true,width:2400,height:1080,x:100,y:20,clipWidth:2000,clipHeight:1000};
  const delays=[];let delay=0;
  const shared={geometry:()=>({...surface}),pack(commands){calls.push('pack');return commands.length*6;},commit(words,delayMs){calls.push('commit');written.push(words);delays.push(delayMs);}};
  const overlay=new Proxy({},{get:(_target,name)=>()=>{calls.push('overlay.'+String(name));return 1;}});
  const rendered=[];
  const publish=createFramePublisher({getOverlay:()=>overlay,geometry:{},ensureSurface(){calls.push('ensureSurface');},refreshGeometry(){throw Error('must not poll geometry');},
    render:(width,height)=>{rendered.push([width,height]);return [[3,0,0,1,1,-1],[3,0,0,1,1,-1]];},encode(){throw Error('no JSON in this transport');},
    toJavaString(){throw Error('no Java strings in this transport');},shared,getDelayMs:()=>delay,onCost(){},log(message){throw Error(message);}});
  for(let frame=0;frame<100;frame++){now+=8;assert.equal(publish(),true);}
  assert(!calls.some(name=>name.startsWith('overlay.')),'Shared transport must not call the overlay per frame');
  assert.equal(calls.filter(name=>name==='commit').length,100);
  assert.deepEqual(rendered[0],[2000,1000],'The render size is the game surface (clip) size when aligned');
  assert.deepEqual(written.slice(0,2),[12,12]);
  assert.equal(delays[0],0);delay=42;publish();assert.equal(delays.at(-1),42,'The display delay is handed to Java with every frame');delay=0;
  // Unaligned: the whole overlay
  surface.clipWidth=0;surface.clipHeight=0;publish();assert.deepEqual(rendered.at(-1),[2400,1080]);
  // Java has not published geometry yet: nothing is rendered or written
  surface.valid=false;rendered.length=0;written.length=0;assert.equal(publish(),false);assert.equal(rendered.length+written.length,0);
  surface.valid=true;
  // No primitives still publish an (empty) frame so the old one disappears
  const empty=createFramePublisher({getOverlay:()=>overlay,geometry:{},ensureSurface(){},refreshGeometry(){},render:()=>[],encode(){},toJavaString(){},shared,onCost(){},log(){}});
  written.length=0;empty();assert.deepEqual(written,[0]);
  // clear() writes an empty frame instead of calling Java
  written.length=0;calls.length=0;publish.clear();assert.deepEqual(written,[0]);assert(!calls.some(name=>name.startsWith('overlay.')));
  assert(/ transport=shared-memory$/.test(publish.takePhases())&&/writeMs=/.test('writeMs='),'Telemetry names the transport');
  // A render failure clears the screen through the same transport
  const failing=createFramePublisher({getOverlay:()=>overlay,geometry:{},ensureSurface(){},refreshGeometry(){},render(){throw Error('boom');},encode(){},toJavaString(){},shared,onCost(){},log(){}});
  written.length=0;assert.equal(failing(),false);assert.deepEqual(written,[0],'A failed frame clears the screen via shared memory');
}
console.log('Frame publisher: one bridge call per frame, geometry cadence, alignment, stale geometry, string fallback and failure rollback passed.');
