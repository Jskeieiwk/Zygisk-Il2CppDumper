// Publishes one ESP frame per game-camera frame. Primary transport: shared memory (assets/shared-frame.js), which needs no
// Frida->Java call at all; the Java view reads it at every vsync. Fallback transport: one CanvasBatch.frame() call per frame.
// On the device a bridge call costs far more than the drawing, so nothing else crosses per frame. Everything the frame needs is
// injected so this can be tested without Frida.
export function createFramePublisher(deps){
  const {getOverlay,geometry,ensureSurface,refreshGeometry,render,encode,toJavaString,onCost,log,shared}=deps;
  const getDelayMs=deps.getDelayMs||(()=>0);
  // Fallback transport only: surface offset and size change rarely and Java verifies them on every frame.
  const refreshInterval=deps.refreshInterval||1500;
  let errors=0,javaStrings=false,phases={render:0,pack:0,send:0,frames:0};
  function call(overlay,geometryNow,text){
    const aligned=geometryNow.aligned;
    const argument=text===null||!javaStrings?text:toJavaString(text);
    return overlay.frame(geometryNow.canvasWidth,geometryNow.canvasHeight,aligned?geometryNow.x:0,aligned?geometryNow.y:0,
      aligned?geometryNow.width:0,aligned?geometryNow.height:0,argument);
  }
  function publishShared(){
    // The Java view republishes its geometry at every vsync, so there is nothing to poll.
    const surface=shared.geometry();
    if(!surface.valid||!(surface.width>0&&surface.height>0))return false;
    const aligned=surface.clipWidth>0&&surface.clipHeight>0;
    const width=aligned?surface.clipWidth:surface.width,height=aligned?surface.clipHeight:surface.height;
    const rendered=Date.now();
    const commands=render(width,height);
    const drawn=Date.now();
    const words=commands&&commands.length?shared.pack(commands):0;
    const packed=Date.now();
    shared.commit(words,getDelayMs());
    const finished=Date.now();
    phases.render+=drawn-rendered;phases.pack+=packed-drawn;phases.send+=finished-packed;phases.frames++;
    return true;
  }
  function publishCall(overlay,started){
    ensureSurface();
    if(!geometry.canvasWidth||started-geometry.t>=refreshInterval)refreshGeometry(Number(overlay.getWidth()),Number(overlay.getHeight()));
    if(!(geometry.canvasWidth>0&&geometry.canvasHeight>0))return false;
    const aligned=geometry.aligned;
    const width=aligned?geometry.width:geometry.canvasWidth,height=aligned?geometry.height:geometry.canvasHeight;
    const rendered=Date.now();
    const commands=render(width,height);
    const drawn=Date.now();
    const text=commands&&commands.length?encode(commands):null;
    const encoded=Date.now();
    let status;
    try{status=call(overlay,geometry,text);}
    catch(error){
      // A JS string may not be accepted where a java.lang.String is expected: retry once with an explicit Java string.
      if(javaStrings||text===null)throw error;
      javaStrings=true;
      try{status=call(overlay,geometry,text);}
      catch(second){javaStrings=false;throw second;}  // not a string-type problem: keep the cheaper plain-string path
      log('CLOUD:frame-string-fallback '+error);
    }
    const finished=Date.now();
    phases.render+=drawn-rendered;phases.pack+=encoded-drawn;phases.send+=finished-encoded;phases.frames++;
    if(Number(status)!==1){geometry.t=0;return false;}
    return true;
  }
  // Returns true when a frame was published. false means nothing was drawn this frame.
  function publish(){
    const overlay=getOverlay();
    if(!overlay)return false;
    const started=Date.now();
    try{
      if(shared){ensureSurface();return publishShared();}
      return publishCall(overlay,started);
    }catch(error){
      try{publish.clear();}catch(ignored){}
      if(errors++<8)log('CLOUD:picture-frame-error '+error);
      return false;
    }finally{
      onCost(Date.now()-started);
    }
  }
  // Removes whatever is on screen (a scene change, a failed frame).
  publish.clear=function(){
    if(shared){shared.commit(0);return;}
    const overlay=getOverlay();
    if(overlay)overlay.clearFrame();
  };
  // Average milliseconds per frame since the last call: where the frame time goes (JS rendering, packing, handing it over).
  publish.takePhases=function(){
    const frames=Math.max(1,phases.frames);
    const text='renderMs='+(phases.render/frames).toFixed(1)+' packMs='+(phases.pack/frames).toFixed(1)+' '+(shared?'writeMs=':'javaMs=')+(phases.send/frames).toFixed(1)+
      ' transport='+(shared?'shared-memory':'call');
    phases={render:0,pack:0,send:0,frames:0};
    return text;
  };
  return publish;
}
