import {createEngine} from '../assets/engine.js';
export function createRawInput(context){
  const engine=createEngine(context.native);
  const get=engine.method(0x502d194,'float',['pointer','pointer']),set=engine.method(0x5030890,'void',['pointer','float','pointer']);
  let saved=null;
  function reset(){
    const previous=saved;saved=null;
    try{if(previous&&engine.live(previous.area))set(previous.area,previous.smoothing,ptr(0));}
    finally{if(previous)engine.release(previous.area);engine.reset();}
  }
  function update(){
    if(!context.settings['Raw Input']||!context.canRun()){if(saved)reset();return;}
    const controls=engine.method(0x384b910,'pointer',['pointer'])(ptr(0)),local=context.getLocalPlayer();
    if(!local||!engine.live(controls)||!controls.add(0x30).readPointer().equals(local)){if(saved)reset();return;}
    const touch=controls.add(0x38).readPointer();if(touch.isNull())return;
    const area=touch.add(0x28).readPointer();if(!engine.live(area))return;
    if(saved&&saved.area.equals(area)){
      const current=get(area,ptr(0));if(Number.isFinite(current)&&current!==0){saved.smoothing=current;set(area,0,ptr(0));}
      return;
    }
    if(saved)reset();
    const smoothing=get(area,ptr(0));if(!Number.isFinite(smoothing))return;
    saved={area:engine.hold(area),smoothing};
    try{set(area,0,ptr(0));}catch(error){reset();throw error;}
  }
  return {update,reset};
}
