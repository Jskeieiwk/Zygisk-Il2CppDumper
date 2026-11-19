import {createEngine} from '../assets/engine.js';
export function createAutoStop(context){
  const engine=createEngine(context.native);
  let controls=null,owner=null;
  function release(){
    if(controls)try{
      if(engine.live(controls))engine.method(0x384a7fc,'void',['pointer','pointer','pointer'])(controls,owner,ptr(0));
    }finally{engine.release(controls);controls=null;}
  }
  function update(local,stop){
    if(!stop){release();return;}
    const selected=engine.method(0x384b910,'pointer',['pointer'])(ptr(0));
    if(!engine.live(selected)||!selected.add(0x30).readPointer().equals(local)){release();return;}
    if(controls&&controls.equals(selected))return;
    release();
    if(!owner)owner=engine.string('Cloud.AutoStop');
    controls=engine.hold(selected);
    try{engine.method(0x3848d14,'void',['pointer','pointer','pointer'])(controls,owner,ptr(0));}
    catch(error){release();throw error;}
  }
  function reset(){try{release();}finally{engine.reset();owner=null;}}
  return {update,reset,active:()=>!!controls};
}
