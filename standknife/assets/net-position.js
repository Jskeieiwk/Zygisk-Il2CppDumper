// Position of an enemy the game's occlusion stopped moving. While a player is obstructed its transform stays where it was
// (the skeleton animates "running in place"), but MovementController (PlayerController+0x108) keeps network movement data:
// the latest snapshot (MovementController+0xB0, three Vector3 at 0x14/0x20/0x2C) and translation data (MovementController+0x98).
// Which of those vectors is the position is not known from the dump, so it is calibrated at runtime: while enemies are visible
// (not obstructed) every candidate is compared with the real transform position, and the first that matches is used afterwards.
// Measured in v0.33: translation+0x44 is a copy of the transform (it froze together with it), so only snapshot fields can be chosen;
// translation fields are still read for the diagnostic dump.
export const NET_CANDIDATES=[
  ['snapshot',0x14],['snapshot',0x20],['snapshot',0x2c],
  ['translation',0x1c],['translation',0x28],['translation',0x38],['translation',0x44],['translation',0x68]
];

const LIMIT=1e5;
const valid=value=>!!value&&value.length===3&&value.every(component=>Number.isFinite(component)&&Math.abs(component)<LIMIT)&&
  (value[0]!==0||value[1]!==0||value[2]!==0);
const distance=(a,b)=>Math.hypot(a[0]-b[0],a[1]-b[1],a[2]-b[2]);

// observe() is fed every sampled enemy; resolve() returns the network position for an obstructed one, or null.
export function createNetPosition({log=()=>{},minSamples=30,minRatio=0.9,matchDistance=0.75,maxShift=80,staleAfterMs=400,fastStaleMs=200,staleDistance=0.05,
  predictMs=1000,minSpeed=1,maxSpeed=7}={}){
  const stats=NET_CANDIDATES.map(()=>({samples:0,matches:0})),selectable=NET_CANDIDATES.map(([source])=>source==='snapshot');
  const lastDump=new Map(),moves=new Map();
  let chosen=-1,dumpLogs=0;
  function observe(pos,values,obstructed){
    if(chosen>=0||obstructed||!valid(pos)||!values)return;
    for(let i=0;i<NET_CANDIDATES.length;i++){
      const value=values[i];if(!valid(value))continue;
      stats[i].samples++;if(distance(value,pos)<matchDistance)stats[i].matches++;
    }
    let best=-1,bestRatio=0;
    for(let i=0;i<stats.length;i++){
      const {samples,matches}=stats[i];if(!selectable[i]||samples<minSamples)continue;
      const ratio=matches/samples;if(ratio>=minRatio&&ratio>bestRatio){best=i;bestRatio=ratio;}
    }
    if(best<0)return;
    chosen=best;
    log('CLOUD:net-pos-calibrated source='+NET_CANDIDATES[best][0]+' offset=0x'+NET_CANDIDATES[best][1].toString(16)+
      ' ratio='+bestRatio.toFixed(2)+' samples='+stats[best].samples+' all='+stats.map(item=>item.matches+'/'+item.samples).join(','));
  }
  const text=value=>valid(value)?value.map(v=>v.toFixed(2)).join(','):'-';
  // While an enemy is obstructed: every candidate next to the transform, once per 500 ms per player (at most 40 lines), so the log
  // shows whether any field keeps moving while the transform stands still.
  function dump(key,pos,values,now){
    if(dumpLogs>=40||now-(lastDump.get(key)||-Infinity)<500)return;
    lastDump.set(key,now);if(lastDump.size>64)lastDump.delete(lastDump.keys().next().value);
    dumpLogs++;
    log('CLOUD:net-pos-obstructed key='+key+' chosen='+chosen+' transform='+text(pos)+' candidates='+values.map(text).join(' | '));
  }
  function resolve(key,pos,values,obstructed,now=0){
    if(!obstructed||!values||!valid(pos))return null;
    dump(key,pos,values,now);
    if(chosen<0)return null;
    const value=values[chosen];
    if(!valid(value)||distance(value,pos)>maxShift)return null;
    return value;
  }
  // Measured in v0.34: the server stops sending an enemy it considers unseeable; the client then freezes the position and keeps
  // looping the last animation ("running in place"). track() detects that freeze for obstructed players and returns
  //   {stale:false}                                  - live data, draw normally
  //   {stale:true,frozenAt,predicted,predictedMs}    - no new data since frozenAt; predicted is the last position carried along
  //                                                    the last measured horizontal velocity for at most predictMs (null if slow)
  function track(key,pos,obstructed,now){
    if(!valid(pos))return {stale:false};
    const previous=moves.get(key);
    if(!previous||distance(previous.pos,pos)>staleDistance){
      let velocity=null;
      if(previous&&now>previous.t){
        const seconds=(now-previous.t)/1000;
        velocity=[(pos[0]-previous.pos[0])/seconds,0,(pos[2]-previous.pos[2])/seconds];
        const speed=Math.hypot(velocity[0],velocity[2]);
        if(!(speed>=minSpeed)||!(speed<=maxSpeed)||now-previous.t>500)velocity=null;
      }
      moves.set(key,{pos:pos.slice(),t:now,velocity});
      if(moves.size>64)moves.delete(moves.keys().next().value);
      return {stale:false};
    }
    const still=now-previous.t;
    // A runner that suddenly stops dead is detected sooner than a slow walker.
    if(!obstructed||still<(previous.velocity?fastStaleMs:staleAfterMs))return {stale:false};
    let predicted=null,predictedMs=0;
    if(previous.velocity){
      predictedMs=Math.min(still,predictMs);
      const seconds=predictedMs/1000;
      predicted=[pos[0]+previous.velocity[0]*seconds,pos[1],pos[2]+previous.velocity[2]*seconds];
    }
    return {stale:true,frozenAt:previous.t,predicted,predictedMs};
  }
  function forget(key){moves.delete(key);lastDump.delete(key);}
  return {observe,resolve,track,forget,chosen:()=>chosen};
}
