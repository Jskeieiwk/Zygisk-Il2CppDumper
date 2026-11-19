// Which obstacles a bullet may pass is decided by the game's own rules, not by a thickness: v0.26 found in the 3.3 dump that
// penetration goes through players (PlayerHitbox keeps LossPenetrationPower) and through breakable objects (BreakableObjectBase
// with penetration thresholds), while ordinary map walls stop bullets. Autowall therefore needs one answer per obstacle:
// true (the bullet passes), false (it stops) or null (not known). Only true lets an automatic shot or the aim go through.
//
// Players are recognised by the aim code itself (it owns the tracked players). This file classifies everything else.
//
// WALL_RULES holds game values measured from the 3.3 dump (dump.cs / script.json from Cloud-project-v23.tar.gz.enc, built from
// the libil2cpp.so with SHA-256 45a634d2...2339). A value that is not measured is null, never 0: while one is null the classifier
// answers null for every obstacle and Autowall behaves like a direct line plus players.
//   breakableType         dump.cs line 317347: namespace Axlebolt.Standoff.Game.BreakableObject, class BreakableObjectBase
//                         (TypeDefIndex 3857, Assembly-CSharp), in the form engine.type() takes.
//   getComponentInParent  script.json ScriptMethod "UnityEngine.Component$$GetComponentInParent" (Type t, bool includeInactive,
//                         MethodInfo): RVA 0xA77E4E0. Same signature shape as GetComponentInChildren 0xA77E310 used elsewhere.
//   minBreakOffset/minCoeffOffset  BreakableObjectBase fields _minBreakPenetrationValue (float, 0x4C) and
//                         _minPenetrationValueForCoeff (float, 0x48). They are only logged (see classify): how they compare with
//                         the weapon's penetration power (WeaponParameters+0x1A4) is not known, so nothing is decided by them.
// Not verified in a match: that every bullet-stopping-but-breakable object has this component above its collider.
const WALL_RULES={
  build:'StandKnife 3.3 (libil2cpp.so sha256 45a634d2...2339)',
  breakableType:'Axlebolt.Standoff.Game.BreakableObject.BreakableObjectBase, Assembly-CSharp',
  getComponentInParent:0xa77e4e0,
  minBreakOffset:0x4c,
  minCoeffOffset:0x48
};

export function wallRulesReady(config=WALL_RULES){
  return config.breakableType!==null&&config.getComponentInParent!==null;
}

// Classifier for one obstacle collider. 'engine' is the engine helper of the module (type lookup and method binding); results are
// cached per collider for the life of the session, because map colliders and breakable objects keep their identity.
export function createWallRules({engine,config=WALL_RULES,log=()=>{}}){
  const cache=new Map();
  let logged=false,getInParent=null,breakableType=null,thresholdLogs=0;
  function bind(){
    if(getInParent)return true;
    if(!wallRulesReady(config))return false;
    breakableType=engine.type(config.breakableType);
    getInParent=engine.method(config.getComponentInParent,'pointer',['pointer','pointer','bool','pointer']);
    return true;
  }
  return {
    ready:()=>wallRulesReady(config),
    // true: breakable (the bullet can pass), false: solid, null: classifier unavailable or the lookup failed.
    classify(collider){
      let bound=false;
      try{bound=bind();}catch(error){if(!logged){logged=true;log('CLOUD:wall-rules-error '+error);}return null;}
      if(!bound){
        if(!logged){logged=true;log('CLOUD:wall-rules unset ('+config.build+'): only the direct line and players are passable');}
        return null;
      }
      const key=collider.toString();
      if(cache.has(key))return cache.get(key);
      let verdict=null;
      try{
        const found=getInParent(collider,breakableType,1,ptr(0));
        verdict=!found.isNull();
        // Evidence for later tuning: the thresholds of the first breakable objects met (at most 40 lines per session).
        if(verdict&&thresholdLogs<40&&config.minBreakOffset!==null&&config.minCoeffOffset!==null){
          thresholdLogs++;
          log('CLOUD:wall-rules breakable minBreak='+found.add(config.minBreakOffset).readFloat().toFixed(3)+
            ' minCoeff='+found.add(config.minCoeffOffset).readFloat().toFixed(3));
        }
      }catch(error){log('CLOUD:wall-rules-error '+error);}
      if(verdict!==null)cache.set(key,verdict);
      return verdict;
    },
    reset(){cache.clear();thresholdLogs=0;}
  };
}
