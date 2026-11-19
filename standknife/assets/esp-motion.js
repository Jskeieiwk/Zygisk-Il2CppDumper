// Advance recent player samples during the 10 Hz data interval. Teleports,
// invalid positions and stale entities are never extrapolated.
export function estimateVelocity(previous,next,elapsedMs,maximumSpeed=25){
  if(!previous||!next||elapsedMs<15||elapsedMs>300||
      !previous.every(Number.isFinite)||!next.every(Number.isFinite))return [0,0,0];
  const velocity=next.map((value,index)=>(value-previous[index])*1000/elapsedMs);
  return Math.hypot(...velocity)<=maximumSpeed?velocity:[0,0,0];
}
export function predictOrigin(state,now,horizonMs=80){
  const pos=state.pos,velocity=state.velocity;
  if(!pos||!pos.every(Number.isFinite)||state.dormant||!velocity||
      !velocity.every(Number.isFinite))return pos;
  const elapsed=Math.max(0,Math.min(horizonMs,now-state.t))/1000;
  return pos.map((value,index)=>value+velocity[index]*elapsed);
}
export function moveBone(point,anchor,origin){
  if(!point||!anchor||!origin)return point;
  return [point[0]+origin[0]-anchor[0],point[1]+origin[1]-anchor[1],point[2]+origin[2]-anchor[2]];
}
