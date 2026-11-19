import {createHookSet} from '../assets/hooks.js';
import {createEngine} from '../assets/engine.js';

export function cameraOffset(origin,forward,distance,height){
  if(!origin.every(Number.isFinite)||!forward.every(Number.isFinite))return null;
  return origin.map((value,index)=>value-forward[index]*distance+(index===1?height:0));
}
const THIRD_PERSON_ARMS_SHIFT=50;
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
  // Third Person also shows the player's own body. All values below are from the 3.3 dump (script.json): PlayerController+0x30 is the
  // CharacterLodGroup (the third-person body), +0x38 of it the SkinnedMeshRenderer; CharacterLodGroup.SetMeshRendererEnabled 0x6812F1C,
  // SkinnedMeshLodGroup.get_RendererEnabled 0x3D53D04, Renderer.get_enabled 0xA744354, Component.get_gameObject 0xA77DD70,
  // GameObject.get_layer 0xA7844F0 / get_activeInHierarchy 0xA784AC8, Camera.get_cullingMask 0xA725FB0 / set_cullingMask 0xA726124.
  // NOT verified on a device: that the game hides the local body through this renderer switch (it may use the layer or an inactive
  // object instead). The CLOUD:third-person-body line prints what was found so the next log shows which one it is.
  // A native 'bool' argument is passed as 0 or 1: this Frida rejects a JS boolean with "expected an integer" (seen in the v0.41 device log).
  const bodyEnabled=native(0x3d53d04,'bool',['pointer','pointer']),setBodyEnabled=native(0x6812f1c,'void',['pointer','bool','pointer']);
  const meshEnabled=native(0xa744354,'bool',['pointer','pointer']),gameObjectOf=native(0xa77dd70,'pointer',['pointer','pointer']);
  const layerOf=native(0xa7844f0,'int',['pointer','pointer']),activeOf=native(0xa784ac8,'bool',['pointer','pointer']);
  const getMask=native(0xa725fb0,'int',['pointer','pointer']),setMask=native(0xa726124,'void',['pointer','int','pointer']);
  const hit=Memory.alloc(0x100),hooks=createHookSet(context.base,Interceptor);
  let saved=null,failures=0,bodyLogs=0,lastBodyState='';
  function report(error){if(failures++<3)console.log('CLOUD:camera-mode-error '+error);}
  function noteBody(state){
    if(state===lastBodyState||bodyLogs>=12)return;
    lastBodyState=state;bodyLogs++;console.log('CLOUD:third-person-body '+state);
  }
  // Switches the body renderer on for this render and makes sure the camera's culling mask contains the body's layer. The original
  // renderer state and mask are kept in `record.body` before anything is changed, so restore() can always undo it.
  function showBody(camera,player,record){
    if(!player||player.isNull()){noteBody('no-local-player');return;}
    const group=player.add(0x30).readPointer();
    if(group.isNull()||!engine.live(group)){noteBody('no-body-group');return;}
    const entry={group:engine.hold(group),wasEnabled:true};
    record.body=entry;
    entry.wasEnabled=!!bodyEnabled(group,ptr(0));
    setBodyEnabled(group,1,ptr(0));
    const mesh=group.add(0x38).readPointer();
    let layer=-1,active=null,meshOn=null,mask=null,maskHasLayer=null;
    if(!mesh.isNull()&&engine.live(mesh)){
      meshOn=!!meshEnabled(mesh,ptr(0));
      const object=gameObjectOf(mesh,ptr(0));
      if(!object.isNull()){layer=layerOf(object,ptr(0));active=!!activeOf(object,ptr(0));}
    }
    if(layer>=0&&layer<32){
      mask=getMask(camera,ptr(0));maskHasLayer=(mask&(1<<layer))!==0;
      if(!maskHasLayer){entry.camera=camera;entry.mask=mask;setMask(camera,mask|(1<<layer),ptr(0));}
    }
    noteBody('wasEnabled='+entry.wasEnabled+' mesh='+(mesh.isNull()?'null':'set')+' meshEnabled='+meshOn+' active='+active+' layer='+layer+
      ' cullingMask=0x'+(mask===null?'?':(mask>>>0).toString(16))+' cameraSawLayer='+maskHasLayer);
  }
  function restore(){
    const previous=saved;saved=null;if(!previous)return;
    try{if(engine.live(previous.transform)){
      setPosition(previous.transform,previous.position,ptr(0));setEuler(previous.transform,previous.euler,ptr(0));
    }}catch(error){report(error);}
    try{if(previous.arms&&engine.live(previous.arms))setLocal(previous.arms,previous.armsPosition,ptr(0));}
    catch(error){report(error);}
    try{
      const body=previous.body;
      if(body){
        if(engine.live(body.group))setBodyEnabled(body.group,body.wasEnabled?1:0,ptr(0));
        if(body.camera&&engine.live(body.camera))setMask(body.camera,body.mask,ptr(0));
      }
    }catch(error){report(error);}
    finally{
      engine.release(previous.transform);if(previous.arms)engine.release(previous.arms);
      if(previous.body)engine.release(previous.body.group);
    }
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
        try{showBody(camera,context.getLocalPlayer(),saved);}catch(error){noteBody('error '+error);}
      }
      if(settings['Back Camera'])setEuler(current,[euler[0],euler[1]+180,euler[2]],ptr(0));
      // In third person the first-person arms and weapon would hang in front of the camera: the arms group (PlayerController+0x48) is moved
      // THIRD_PERSON_ARMS_SHIFT metres down for the render and back afterwards, the same mechanism the Viewmodel offsets use.
      // NOT verified on a device that the weapon model hangs under this transform; the next log/screenshot shows whether it vanished.
      if(settings.Viewmodel||settings['Third Person']){
        const player=context.getLocalPlayer();
        if(player){
          const group=player.add(0x48).readPointer();
          if(!group.isNull()){
            const arms=transform(group,ptr(0));
            if(engine.live(arms)){
              const origin=getLocal(arms,ptr(0));
              if(origin.every(Number.isFinite)){
                saved.arms=engine.hold(arms);saved.armsPosition=origin;
                const shift=settings['Third Person']?[0,-THIRD_PERSON_ARMS_SHIFT,0]:['Viewmodel X','Viewmodel Y','Viewmodel Z'].map(key=>settings[key]);
                setLocal(arms,origin.map((value,index)=>value+shift[index]),ptr(0));
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
