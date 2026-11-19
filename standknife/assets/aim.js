import {createAimMotion,aimCandidates,hitChance} from '../assets/aim-motion.js';
import {createEngine} from '../assets/engine.js';
import {createWallRules} from '../assets/wall-rules.js';
import {createAutoStop} from '../assets/auto-stop.js';
import {installFireControl} from '../assets/fire-control.js';
export function wrapAngle(value) { return ((value+180)%360+360)%360-180; }
export function aimAngles(origin,target) {
  const [x,y,z]=target.map((value,index)=>value-origin[index]);
  if(![x,y,z].every(Number.isFinite)||Math.hypot(x,y,z)<.001)return null;
  return [-Math.atan2(y,Math.hypot(x,z))*180/Math.PI,Math.atan2(x,z)*180/Math.PI,0];
}
export function angularDistance(current,target) {
  const p=current[0]*Math.PI/180,y=current[1]*Math.PI/180;
  const q=target[0]*Math.PI/180,z=target[1]*Math.PI/180;
  return Math.acos(Math.max(-1,Math.min(1,Math.sin(p)*Math.sin(q)+Math.cos(p)*Math.cos(q)*Math.cos(y-z))))*180/Math.PI;
}
export function smoothAngles(current,target,elapsed,milliseconds) {
  const alpha=milliseconds<=0?1:1-Math.exp(-Math.max(0,Math.min(.05,elapsed))*1000/milliseconds);
  return [Math.max(-89.5,Math.min(89.5,wrapAngle(current[0])+wrapAngle(target[0]-current[0])*alpha)),
    wrapAngle(current[1]+wrapAngle(target[1]-current[1])*alpha),0];
}
export function createAim(context) {
  const {native,settings,transform,position,records,tracked,getHealth,active}=context;
  const vector=['float','float','float'];
  const motion=createAimMotion(),stop=createAutoStop(context);
  const getRotation=native(0x5452708,vector,['pointer','pointer']);
  const setRotation=native(0x54519e4,'void',['pointer',vector,'pointer']);
  const linecast=native(0xa8261c8,'bool',[vector,vector,'pointer','int','int','pointer']);
  const collider=native(0xa82b000,'pointer',['pointer','pointer']);
  const childOf=native(0xa7a4150,'bool',['pointer','pointer','pointer']);
  const getFov=native(0xa724984,'float',['pointer','pointer']);
  const pointOfHit=native(0xa82b12c,vector,['pointer','pointer']);
  const hit=Memory.alloc(0x100),reverseHit=Memory.alloc(0x100);
  let fireState={t:0,selected:null,crosshair:false,clear:false};
  const fire=installFireControl({base:context.base,native,settings,getLocalPlayer:context.getLocalPlayer,getAim:()=>fireState,active:context.fireActive,canRun:context.canRun,generation:context.generation,getScope:context.getScope});
  // The last decision is kept so a selected target (and every automatic shot) can say why it was allowed.
  let evidence=null;
  // Line from the camera to the target point. Without wall: only a clear line (or the target's own colliders) counts.
  // With wall (Autowall/Wallshot) the line may cross obstacles the game lets bullets through: other players, and whatever the
  // wall rules classify as passable (breakable objects, see wall-rules.js). Nothing is measured in centimetres: an obstacle is
  // passable or it is not. An unknown obstacle counts as solid. MAX_OBSTACLES only bounds the loop.
  const MAX_OBSTACLES=4,PASS_EPSILON=.02;
  const rules=context.wallRules||createWallRules({engine:createEngine(native),log:message=>console.log(message)});
  function ownCollider(collider_,player){
    const obstacleTransform=transform(collider_,ptr(0)),root=transform(player,ptr(0));
    return !obstacleTransform.isNull()&&!root.isNull()&&childOf(obstacleTransform,root,ptr(0));
  }
  // Another tracked player's collider: bullets pass through players (PlayerHitbox keeps the power loss, see wall-rules.js).
  // The root transform of each player is read once per step, not once per obstacle.
  const rootCache=new Map();
  function playerCollider(collider_,except){
    const obstacleTransform=transform(collider_,ptr(0));
    if(obstacleTransform.isNull())return false;
    for(const [key,entry] of tracked){
      if(!entry||!entry.player||entry.player.equals(except))continue;
      let root=rootCache.get(key);
      if(root===undefined){root=transform(entry.player,ptr(0));rootCache.set(key,root);}
      if(!root.isNull()&&childOf(obstacleTransform,root,ptr(0)))return true;
    }
    return false;
  }
  // A player whose every candidate point was blocked is not checked again for HIDDEN_RECHECK_MS, unless the camera or the player
  // moved HIDDEN_MOVE metres. With a wide FOV, Multipoints and Autowall (Aim) a player behind a wall costs one cast (and, with
  // Autowall, several classifications) per point per step, about 740 native calls per step for five hidden players (counted in a
  // scratch profile, not timed). A player who steps into view is noticed within HIDDEN_RECHECK_MS; a visible one is checked every step.
  // After HIDDEN_RECHECK_MS only the PROBE_POINTS best points of a hidden player are cast (a player stepping out of cover shows its best
  // points first); the full sweep of every point is repeated every HIDDEN_FULL_MS. Measured on the device (v0.42 log): the aim step took
  // 5.7-7.3 ms on average at 18-37 fps, so at that frame rate a 100 ms memory covered only about three steps.
  const HIDDEN_RECHECK_MS=100,HIDDEN_FULL_MS=400,PROBE_POINTS=2,HIDDEN_MOVE=.5,hidden=new Map();
  // Counters for the perf line (CLOUD:perf aimCasts/aimReachMs ...): what one step really does, read and zeroed by takeCost().
  let cost={steps:0,casts:0,obstacles:0,skipped:0,probes:0,reachMs:0};
  const apart=(a,b)=>Math.hypot(a[0]-b[0],a[1]-b[1],a[2]-b[2]);
  function reaches(origin,target,player,wall) {
    const began=Date.now();
    try{return reachesLine(origin,target,player,wall);}finally{cost.reachMs+=Date.now()-began;}
  }
  function reachesLine(origin,target,player,wall) {
    evidence={wall:!!wall,direct:false,walls:0,blocked:null};
    let start=origin;
    for(let step=0;step<=MAX_OBSTACLES;step++){
      cost.casts++;
      if(!linecast(start,target,hit,-1,1,ptr(0))){evidence.direct=evidence.walls===0;return true;}
      cost.obstacles++;
      const obstacle=collider(hit,ptr(0));if(obstacle.isNull())return false;
      if(ownCollider(obstacle,player)){evidence.direct=evidence.walls===0;return true;}
      if(!wall){evidence.blocked='solid';return false;}
      const verdict=playerCollider(obstacle,player)?true:rules.classify(obstacle);
      if(verdict!==true){evidence.blocked=verdict===false?'solid':'unknown';return false;}
      const entry=pointOfHit(hit,ptr(0));
      const span=Math.hypot(...target.map((value,index)=>value-entry[index]));
      if(!(span>PASS_EPSILON))return false;
      // The next cast starts just inside the passable obstacle: a ray that starts inside a collider does not report it again.
      start=entry.map((value,index)=>value+(target[index]-entry[index])/span*PASS_EPSILON);
      evidence.walls++;
    }
    evidence.blocked='too many obstacles';
    return false;
  }
  let previous=0,locked=null,failed=0,lastReport=0,status={target:null,fov:60};
  function step(local,camera,team) {
    const now=Date.now(),elapsed=previous?Math.max(0,(now-previous)/1000):1/60;previous=now;
    status.target=null;fireState={t:now,selected:null,crosshair:false,clear:false};rootCache.clear();cost.steps++;
    if(context.canRun&&!context.canRun()){stop.update(local,false);motion.reset();return;}
    if(context.paused&&context.paused()){if(fire.suspend)fire.suspend();stop.update(local,false);motion.reset();return;}
    fire.ensureInstalled();
    if(records.size===0){locked=null;stop.update(local,false);motion.reset();return;}
    let isKnife=false;
    if(settings['Knife Bot'])try{
      const inventory=local.add(0xf0).readPointer(),weapon=inventory.isNull()?ptr(0):inventory.add(0xa8).readPointer();
      const parameters=weapon.isNull()?ptr(0):weapon.add(0xb8).readPointer();
      if(!parameters.isNull()){const id=parameters.add(0x18).readU8();isKnife=id>=70&&id<=89;}
    }catch(error){}
    fireState.isKnife=isKnife;
    if(!(isKnife||settings['Aim assistance']||settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope'])||camera.isNull()) {locked=null;stop.update(local,false);motion.reset();return;}
    let keepStopped=false;
    try {
      if(getHealth(local,ptr(0))<=0) {locked=null;return;}
      const aim=local.add(0x128).readPointer();if(aim.isNull())return;
      const cameraTransform=transform(camera,ptr(0));if(cameraTransform.isNull())return;
      const origin=position(cameraTransform,ptr(0)),current=getRotation(aim,ptr(0));
      if(!current.every(Number.isFinite))return;
      let selected=null,score=Infinity,rayTransform=null;
      if(settings.Trigger && context.fireActive()) {
        const pitch=current[0]*Math.PI/180,yaw=current[1]*Math.PI/180;
        const direction=[Math.sin(yaw)*Math.cos(pitch),-Math.sin(pitch),Math.cos(yaw)*Math.cos(pitch)];
        const endpoint=origin.map((value,index)=>value+direction[index]*settings['Aim Range']);
        if(linecast(origin,endpoint,hit,-1,1,ptr(0))) {
          const struck=collider(hit,ptr(0));
          if(!struck.isNull())rayTransform=transform(struck,ptr(0));
        }
      }
      const range=isKnife?settings['Knife Range']:settings['Aim Range'],fovLimit=isKnife?settings['Knife FOV']:settings['Aim FOV'];
      const wallAim=!isKnife&&(settings['Autowall (Aim)']||settings.Autowall);
      let crosshairKey=null;
      for(const [key,item]of records) {
        if(now-item.t>150)continue;
        const player=tracked.get(key);
        if(!player||player.local||player.player.equals(local))continue;
        if(settings['Aim Team Filter']&&team>0&&item.team===team)continue;
        const targetHealth=item.health===undefined?getHealth(player.player,ptr(0)):item.health;
        if(targetHealth<=0)continue;
        if(rayTransform && !rayTransform.isNull()) {
          const root=transform(player.player,ptr(0));
          if(!root.isNull() && childOf(rayTransform,root,ptr(0))){fireState.crosshair=true;crosshairKey=key;}
        }
        // Points of this player in range and inside the FOV, best part first, then closest to the crosshair. The first one
        // that passes the visibility rule is this player's aim point, so a player never offers a leg while a visible chest or
        // head is in range (rank), and the line checks run only for points that could still win.
        const candidates=[];
        for(const candidate of aimCandidates(item.bonePositions,settings,isKnife)){
          const distance=Math.hypot(...candidate.point.map((value,i)=>value-origin[i]));
          if(distance>range)continue;
          const angles=aimAngles(origin,candidate.point);if(!angles)continue;
          const angle=angularDistance(current,angles);
          if(angle>fovLimit*(settings['Sticky Aim']&&key===locked?1.15:1))continue;
          candidates.push({...candidate,distance,angles,angle});
        }
        candidates.sort((a,b)=>a.rank-b.rank||a.angle-b.angle);
        const needsLine=isKnife||settings['Aim Visible Only']||settings['Autowall (Aim)'],anchor=candidates.length?candidates[0].point:null;
        let probeOnly=false,memo=null;
        if(needsLine&&anchor){
          memo=hidden.get(key)||null;
          if(memo&&apart(memo.origin,origin)<HIDDEN_MOVE&&apart(memo.anchor,anchor)<HIDDEN_MOVE){
            if(now<memo.until){cost.skipped++;continue;}
            if(now<memo.full){probeOnly=true;cost.probes++;}
          }else memo=null;
        }
        let tried=0,picked=false;
        for(const candidate of candidates){
          if(probeOnly&&tried>=PROBE_POINTS)break;
          let value=settings['Aim Priority']===1?candidate.distance:settings['Aim Priority']===2?targetHealth:candidate.angle;
          if(settings['Sticky Aim']&&key===locked)value-=1000;
          if(value>=score)continue;
          let checked=null;
          if(needsLine){
            tried++;
            if(!reaches(origin,candidate.point,player.player,wallAim))continue;
            checked=evidence;
          }
          score=value;selected={key,angles:candidate.angles,target:candidate.point,player:player.player,item,part:candidate.part,reach:checked};
          picked=true;
          break;
        }
        if(needsLine&&anchor){
          if(picked)hidden.delete(key);
          else if(probeOnly){if(tried>0)memo.until=now+HIDDEN_RECHECK_MS;}   // probe found nothing: stay hidden until the next probe
          else if(tried>0&&tried>=candidates.length){
            if(hidden.size>64)hidden.clear();
            hidden.set(key,{until:now+HIDDEN_RECHECK_MS,full:now+HIDDEN_FULL_MS,origin,anchor});
          }else hidden.delete(key);
        }
      }
      if(!selected) {locked=null;motion.reset();return;}
      fireState.selected=selected;
      if(settings['Force Shot']||settings['Silent Aim']){
        // Shots are redirected or forced only onto a target with a clear line, or through passable obstacles when Wallshot is
        // on. Whether the game really lets the bullet through is decided by the game (see wall-rules.js).
        fireState.clear=reaches(origin,selected.target,selected.player,!!settings.Wallshot);
        selected.reach=evidence;
      }
      if(settings.Trigger && settings.Autowall && angularDistance(current,selected.angles)<.25 && reaches(origin,selected.target,selected.player,true)){fireState.crosshair=true;crosshairKey=selected.key;}
      // Hit chance gates automatic fire only: the share of the target's hitbox points (full size) the shot could reach.
      if(settings.Hitchance&&(fireState.clear||fireState.crosshair)){
        const need=settings['Hitchance Percent'];
        const wallShot=fireState.clear?!!settings.Wallshot:!!settings.Autowall;
        const chanceOf=key=>{
          const item=records.get(key),entry=tracked.get(key);
          if(!item||!entry)return 0;
          return hitChance(item.bonePositions,settings,point=>reaches(origin,point,entry.player,wallShot));
        };
        const percent={};
        if(fireState.clear){percent.aim=chanceOf(selected.key);if(percent.aim<need)fireState.clear=false;}
        if(fireState.crosshair&&crosshairKey!==null){percent.crosshair=crosshairKey===selected.key&&percent.aim!==undefined?percent.aim:chanceOf(crosshairKey);if(percent.crosshair<need)fireState.crosshair=false;}
        fireState.hitchance=percent;
      }
      status.target=selected.key;
      if(settings['Auto Stop']&&active())try{stop.update(local,true);keepStopped=true;}
      catch(error){if(failed++<5)console.log('CLOUD:auto-stop-error '+error);}
      if(!settings['Aim assistance']||settings['Silent Aim']||!active()){motion.reset();return;}
      let duration=settings['Aim Smoothing'];
      if(settings.Humanize)duration=Math.max(duration,80);
      const smoothed=smoothAngles(current,selected.angles,elapsed,duration);
      const output=motion.apply(current,settings.Overshoot?selected.angles:smoothed,elapsed,duration,selected.key,settings,now);
      setRotation(aim,output,ptr(0));locked=selected.key;status.target=selected.key;
      if(now-lastReport>10000) {
        lastReport=now;
        const readback=getRotation(aim,ptr(0));
        console.log('CLOUD:aim-write target='+selected.key+' wanted='+JSON.stringify(output)+' readback='+JSON.stringify(readback));
      }
    }catch(error){locked=null;if(failed++<5)console.log('CLOUD:aim-error '+error);}
    finally{if(!keepStopped)try{stop.update(local,false);}catch(error){if(failed++<5)console.log('CLOUD:auto-stop-error '+error);}}
  }
  function reset(){hidden.clear();cost={steps:0,casts:0,obstacles:0,skipped:0,probes:0,reachMs:0};rules.reset();try{stop.reset();}catch(error){if(failed++<5)console.log('CLOUD:auto-stop-reset-error '+error);}motion.reset();previous=0;locked=null;status.target=null;fireState={t:0,selected:null,crosshair:false,clear:false};fire.reset();}
  return {step,reset,takeCost(){const taken=cost;cost={steps:0,casts:0,obstacles:0,skipped:0,probes:0,reachMs:0};return taken;},needsUpdate:()=>stop.active()||!!(fire.needsCleanup&&fire.needsCleanup()),status:(camera)=>{
    if(camera&&!camera.isNull())try{status.fov=getFov(camera,ptr(0));}catch(error){}
    return {...status,fire:fire.status()};
  }};
}
