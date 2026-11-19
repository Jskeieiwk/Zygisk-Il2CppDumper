// Keep native gameplay callbacks out of lobby previews and scene transitions.
export function createMatchSession() {
  let scene=null,present=false,frames=0,lastFrame=0,lastFrameId=null,generation=0;
  return {
    update(inGame,sceneHandle,now,frameId=now) {
      const changed=scene!==null&&scene!==sceneHandle;
      const leaving=present&&!inGame;
      const reset=changed||leaving;
      if(reset){generation++;frames=0;lastFrameId=null;}
      scene=sceneHandle;present=!!inGame;lastFrame=now;
      if(!present){frames=0;lastFrameId=null;}
      else if(lastFrameId!==frameId){frames++;lastFrameId=frameId;}
      return {reset,ready:present&&frames>=3,generation};
    },
    present(now){return present&&now-lastFrame<250;},
    ready(now){return present&&frames>=3&&now-lastFrame<250;},
    generation(){return generation;}
  };
}
