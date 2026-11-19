import {createHookSet} from '../assets/hooks.js';
import {createEngine} from '../assets/engine.js';

export function cameraOffset(origin,forward,distance,height){
  if(!origin.every(Number.isFinite)||!forward.every(Number.isFinite))return null;
  return origin.map((value,index)=>value-forward[index]*distance+(index===1?height:0));
}
export function createCameraEffects(context){
  const {native,settings,transform,position}=context,engine=createEngine(native);
  const vector=['float','float','float'];
  const getEuler=native(0xa7a06f0,vector,['pointer','pointer']);
  const setEuler=native(0xa7a0764,'void',['pointer',vector,'pointer']);
  const getForward=native(0xa7a0a78,vector,['pointer','pointer']);
  const setPosition=native(0xa7a01ec,'void',['pointer',vector,'pointer']);
  const getLocal=native(0xa7a0398,vector,['pointer','pointer']);
  const setLocal=native(0xa7a0548,'void',['pointer',vector,'pointer']);
  const linecast=native(0xa8261c8,'bool',[vector,vector,'pointer','int','int','pointer']);
  const hitPoint=native(0xa82b12c,vector,['pointer','pointer']);
  const hit=Memory.alloc(0x100),hooks=createHookSet(context.base,Interceptor);
  let saved=null,failures=0;
  function report(error){if(failures++<3)console.log('CLOUD:camera-mode-error '+error);}
  function restore(){
    const previous=saved;saved=null;if(!previous)return;
    try{if(engine.live(previous.transform)){
      setPosition(previous.transform,previous.position,ptr(0));setEuler(previous.transform,previous.euler,ptr(0));
    }}catch(error){report(error);}
    try{if(previous.arms&&engine.live(previous.arms))setLocal(previous.arms,previous.armsPosition,ptr(0));}
    catch(error){report(error);}
    finally{engine.release(previous.transform);if(previous.arms)engine.release(previous.arms);}
  }
  function apply(camera){
    if(!(settings['Back Camera']||settings['Third Person']||settings.Viewmodel)||!context.canRun()){restore();return;}
    const selected=context.getCamera();if(!selected||selected.isNull()||!camera.equals(selected))return;
    restore();
    const current=transform(camera,ptr(0));if(!engine.live(current))return;
    const originalPosition=position(current,ptr(0)),euler=getEuler(current,ptr(0));
    if(!originalPosition.every(Number.isFinite)||!euler.every(Number.isFinite))return;
    saved={camera,transform:engine.hold(current),position:originalPosition,euler};
    try{
      if(settings['Third Person']){
        const desired=cameraOffset(originalPosition,getForward(current,ptr(0)),settings['Camera Distance'],settings['Camera Height']);
        if(desired){
          let destination=desired;
          if(linecast(originalPosition,desired,hit,-1,1,ptr(0))){
            const collision=hitPoint(hit,ptr(0)),length=Math.hypot(...collision.map((value,index)=>value-originalPosition[index]));
            if(collision.every(Number.isFinite)&&length>.05){
              const fraction=Math.max(0,(length-.12)/length);
              destination=collision.map((value,index)=>originalPosition[index]+(value-originalPosition[index])*fraction);
            }else destination=originalPosition;
          }
          setPosition(current,destination,ptr(0));
        }
      }
      if(settings['Back Camera'])setEuler(current,[euler[0],euler[1]+180,euler[2]],ptr(0));
      if(settings.Viewmodel){
        const player=context.getLocalPlayer();
        if(player){
          const group=player.add(0x48).readPointer();
          if(!group.isNull()){
            const arms=transform(group,ptr(0));
            if(engine.live(arms)){
              const origin=getLocal(arms,ptr(0));
              if(origin.every(Number.isFinite)){
                saved.arms=engine.hold(arms);saved.armsPosition=origin;
                setLocal(arms,origin.map((value,index)=>value+settings[['Viewmodel X','Viewmodel Y','Viewmodel Z'][index]]),ptr(0));
              }
            }
          }
        }
      }
    }catch(error){restore();throw error;}
  }
  try{
    hooks.attach(0xa72b848,{onEnter(args){this.camera=args[0];},onLeave(){
      try{apply(this.camera);}catch(error){report(error);}
    }},'camera-pre-cull-mode',true);
    hooks.attach(0xa72b9f8,{onEnter(args){this.camera=args[0];},onLeave(){
      if(saved&&this.camera.equals(saved.camera))restore();
    }},'camera-post-render-mode',true);
  }catch(error){hooks.detach();throw error;}
  // Only an observed world camera is changed. Its original pose is restored
  // after rendering, so input, aiming and network simulation use the original.
  return {reset:restore,dispose(){restore();hooks.detach();engine.reset();}};
}
