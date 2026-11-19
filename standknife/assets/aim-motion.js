// Exact damped-spring integration avoids an FPS-dependent Euler approximation.
export function springAxis(current,target,velocity,elapsed,milliseconds,angular=false){
  const wrap=value=>((value+180)%360+360)%360-180;
  const offset=angular?wrap(current-target):current-target;
  const dt=Math.max(0,Math.min(.05,elapsed)),omega=4.6/(Math.max(80,milliseconds)/1000),damping=.65;
  const damped=omega*Math.sqrt(1-damping*damping),decay=Math.exp(-damping*omega*dt);
  const sine=Math.sin(damped*dt),cosine=Math.cos(damped*dt);
  const next=decay*(offset*cosine+(velocity+damping*omega*offset)*sine/damped);
  const speed=decay*(velocity*cosine-(damping*omega*velocity+omega*omega*offset)*sine/damped);
  const value=target+next;
  return {value:angular?wrap(value):value,velocity:speed};
}
export function createAimMotion(){
  let key=null,velocity=[0,0];
  return {
    reset(){key=null;velocity=[0,0];},
    apply(current,target,elapsed,duration,targetKey,settings,now){
      if(key!==targetKey){key=targetKey;velocity=[0,0];}
      let output=target.slice();
      if(settings.Overshoot){
        for(let axis=0;axis<2;axis++){
          const normalized=((current[axis]+180)%360+360)%360-180;
          const step=springAxis(normalized,target[axis],velocity[axis],elapsed,duration,axis===1);
          output[axis]=step.value;velocity[axis]=step.velocity;
        }
      }else velocity=[0,0];
      if(settings.Jitter){
        const strength=Math.max(0,Math.min(.5,Number(settings['Jitter Strength'])||0));
        const phase=now/1000*2*Math.PI*4;
        output[0]+=Math.sin(phase*.73)*strength;
        output[1]+=Math.sin(phase)*strength;
      }
      output[0]=Math.max(-89.5,Math.min(89.5,output[0]));
      output[1]=((output[1]+180)%360+360)%360-180;output[2]=0;
      return output;
    }
  };
}
// Bone indices follow boneOffsets in module.js (BipedMap): 0 Head, 1 Neck, 2 Spine2, 3 Hip, 10/11 left upper leg/leg,
// 13/14 right upper leg/leg. Hitboxes are chosen in the menu (any combination); none selected means head.
export function hitboxBones(settings,isKnife=false){
  if(isKnife)return [2];
  const multi=!!settings.Multipoints,out=[];
  const head=settings['Hitbox Head']!==false,body=!!settings['Hitbox Body'],legs=!!settings['Hitbox Legs'];
  if(head||(!body&&!legs))out.push(...(multi?[0,1]:[0]));
  if(body)out.push(...(multi?[2,3]:[2]));
  if(legs)out.push(...(multi?[10,11,13,14]:[10,13]));
  return out;
}
// Aim points for the selected hitboxes. With Multipoints the head also gets a point above the head bone (towards the crown),
// and the body a point between chest and hip, so a partly covered target still has a visible point.
export function hitboxPoints(bones,settings,isKnife=false){
  const ok=point=>point&&point.length===3&&point.every(Number.isFinite);
  const points=[];
  for(const index of hitboxBones(settings,isKnife)){const point=bones[index];if(ok(point))points.push({point,index});}
  if(settings.Multipoints&&!isKnife){
    const head=bones[0],neck=bones[1],chest=bones[2],hip=bones[3];
    if((settings['Hitbox Head']!==false||(!settings['Hitbox Body']&&!settings['Hitbox Legs']))&&ok(head)&&ok(neck))
      points.push({point:head.map((v,i)=>v+(v-neck[i])*0.6),index:0});
    if(settings['Hitbox Body']&&ok(chest)&&ok(hip))points.push({point:chest.map((v,i)=>(v+hip[i])/2),index:2});
  }
  return points;
}
export function targetPoints(bones,selected,multipoints){
  const indices=multipoints?[selected,0,1,2,3,4,7,10,13]:[selected];
  return [...new Set(indices)].map(index=>bones[index]).filter(point=>point&&point.every(Number.isFinite));
}

// ---------------------------------------------------------------------------------------------------------------------------
// Hitbox parts, multipoints and hit chance (v0.38). Pure functions: no game memory is touched here.
// Coordinates are Unity's (Y up, left-handed); every vector is [x,y,z] in metres.
// ---------------------------------------------------------------------------------------------------------------------------
// Bones per part, indices as in boneOffsets in module.js: 0 Head, 1 Neck, 2 Spine2, 3 Hip, 10/11 left thigh/shin, 13/14 right.
const PART_BONES={head:[0,1],body:[2,3],legs:[10,11,13,14]};
// UNCALIBRATED geometry: the game's hitbox sizes are not in the dump, so the extent of each part is estimated from bone
// distances. 'Multipoint Scale' (percent) shrinks or grows the offset of every extra point around the part's centre, which is
// how the player tunes it. Head radius = headRadiusPerNeckBone * |head bone - neck bone| (0.6 is the crown factor v0.37 used).
const HITBOX_GEOMETRY={headRadiusPerNeckBone:.6,headRadiusFallback:.1};
const finite=point=>!!point&&point.length===3&&point.every(Number.isFinite);
const sub=(a,b)=>[a[0]-b[0],a[1]-b[1],a[2]-b[2]],plus=(a,b)=>[a[0]+b[0],a[1]+b[1],a[2]+b[2]],times=(a,k)=>[a[0]*k,a[1]*k,a[2]*k];
const dot=(a,b)=>a[0]*b[0]+a[1]*b[1]+a[2]*b[2],norm=a=>Math.hypot(a[0],a[1],a[2]);
const cross=(a,b)=>[a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]];
const unit=a=>{const length=norm(a);return length>1e-6?times(a,1/length):null;};
const middle=(a,b)=>times(plus(a,b),.5);
// Parts selected in the menu. 'Hitbox All' (or all three ticked) means the whole body; nothing ticked means the head.
export function activeParts(settings){
  if(settings['Hitbox All'])return ['head','body','legs'];
  const head=settings['Hitbox Head']!==false,body=!!settings['Hitbox Body'],legs=!!settings['Hitbox Legs'];
  const parts=[];
  if(head||(!body&&!legs))parts.push('head');
  if(body)parts.push('body');
  if(legs)parts.push('legs');
  return parts;
}
// Rank of each part when a player offers points on several of them: lower is tried first and a worse rank is used only when no
// point of a better one is in range and visible. 'Hitbox Priority' 0: head, body, legs; 1: body, head, legs; 2: no ranking (the point
// closest to the crosshair wins, which is what made the aim drift to the legs when the whole body was ticked).
export function partRank(settings,part){
  const mode=Number(settings['Hitbox Priority'])||0;
  if(mode===2)return 0;
  const order=mode===1?['body','head','legs']:['head','body','legs'];
  return order.indexOf(part);
}
// Axes of the target built from bones only: up (hip to head), lateral (left thigh to right thigh, made perpendicular to up) and
// forward. The sign of forward is arbitrary because points are placed on both sides.
export function bodyFrame(bones){
  const top=finite(bones[0])?bones[0]:null,bottom=finite(bones[3])?bones[3]:finite(bones[2])?bones[2]:null;
  if(!top||!bottom)return null;
  const up=unit(sub(top,bottom));if(!up)return null;
  let lateral=null,hipHalfWidth=null;
  if(finite(bones[10])&&finite(bones[13])){
    const raw=sub(bones[13],bones[10]);hipHalfWidth=norm(raw)/2;
    lateral=unit(sub(raw,times(up,dot(raw,up))));
  }
  if(!lateral)lateral=unit(cross(up,[0,0,1]))||[1,0,0];
  const forward=unit(cross(lateral,up));
  return forward?{up,lateral,forward,hipHalfWidth}:null;
}
// Points of one part: the centre first (what Multipoints off aims at), then, with 'scale' in 0..1, extra points spread around it.
// Returns [{point,index,part,center}] and skips anything built from a missing or non-finite bone.
export function partPoints(bones,part,scale,extra=true){
  const out=[],frame=extra?bodyFrame(bones):null;
  const push=(point,index,center)=>{if(finite(point))out.push({point,index,part,center});};
  const s=Math.max(0,Math.min(1,scale));
  if(part==='head'){
    const head=bones[0],neck=bones[1];if(!finite(head))return out;
    push(head,0,true);
    if(!extra||!frame)return out;
    const radius=finite(neck)?HITBOX_GEOMETRY.headRadiusPerNeckBone*norm(sub(head,neck)):HITBOX_GEOMETRY.headRadiusFallback,r=radius*s;
    for(const axis of [frame.up,times(frame.up,-1),frame.lateral,times(frame.lateral,-1),frame.forward,times(frame.forward,-1)])push(plus(head,times(axis,r)),0,false);
  }else if(part==='body'){
    const chest=bones[2],hip=bones[3];if(!finite(chest))return out;
    push(chest,2,true);
    if(!extra||!finite(hip))return out;
    const mid=middle(chest,hip),half=times(sub(chest,hip),.5),side=frame?frame.lateral:null;
    const width=frame&&frame.hipHalfWidth?frame.hipHalfWidth:norm(half);
    push(mid,2,false);push(plus(mid,times(half,s)),2,false);push(sub(mid,times(half,s)),3,false);
    if(side){push(plus(mid,times(side,width*s)),2,false);push(sub(mid,times(side,width*s)),2,false);}
  }else if(part==='legs'){
    for(const [upper,lower] of [[10,11],[13,14]]){
      const a=bones[upper],b=bones[lower];if(!finite(a))continue;
      push(a,upper,true);
      if(!extra||!finite(b))continue;
      const mid=middle(a,b);
      push(mid,upper,false);push(plus(mid,times(sub(a,mid),s)),upper,false);push(plus(mid,times(sub(b,mid),s)),lower,false);
    }
  }
  return out;
}
// Candidates for the aim of one player: every point of every selected part, each with its part rank. The knife aims at the chest.
export function aimCandidates(bones,settings,isKnife=false){
  if(isKnife)return partPoints(bones,'body',0,false).map(item=>({...item,rank:0}));
  const scale=Math.max(10,Math.min(100,Number(settings['Multipoint Scale'])||50))/100;
  const out=[];
  for(const part of activeParts(settings))for(const item of partPoints(bones,part,scale,!!settings.Multipoints))out.push({...item,rank:partRank(settings,part)});
  return out;
}
// Bones the aim needs per frame: the centres of the selected parts, plus the neighbours the extra points are built from.
export function aimBones(settings,isKnife=false){
  if(isKnife)return [2];
  const out=new Set();
  const parts=activeParts(settings);
  for(const part of parts){
    for(const index of(settings.Multipoints||settings.Hitchance?PART_BONES[part]:part==='legs'?[10,13]:[PART_BONES[part][0]]))out.add(index);
  }
  if(settings.Multipoints||settings.Hitchance){out.add(0);out.add(10);out.add(13);}
  return [...out].sort((a,b)=>a-b);
}
// Hit chance in percent: for each selected part, the share of points of its full-size cloud (scale 100%) the caller can see
// ('visible' answers for one point); the best part counts. It measures how much of the target is exposed, not weapon spread.
export function hitChance(bones,settings,visible){
  let best=0;
  for(const part of activeParts(settings)){
    const cloud=partPoints(bones,part,1,true);if(!cloud.length)continue;
    let seen=0;for(const item of cloud)if(visible(item.point))seen++;
    best=Math.max(best,seen*100/cloud.length);
    if(best>=100)break;
  }
  return best;
}
