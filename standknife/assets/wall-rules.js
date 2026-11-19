// Which obstacles a bullet may pass is decided by the game's own rules, not by a thickness: v0.26 found in the 3.3 dump that
// penetration goes through players (PlayerHitbox keeps LossPenetrationPower) and through breakable objects (BreakableObjectBase
// with penetration thresholds), while ordinary map walls stop bullets. Autowall therefore needs one answer per obstacle:
// true (the bullet passes), false (it stops) or null (not known). Only true lets an automatic shot or the aim go through.
//
// Players are recognised by the aim code itself (it owns the tracked players). This file classifies everything else.
//
// WALL_RULES holds the measured game values. null means "not measured yet" and is never treated as zero: while a value is null
// the classifier answers null for every obstacle and Autowall behaves like a direct line plus players. To fill it in, search
// the 3.3 dump.cs (regenerated with libil2cpp-for-dumper.so + global-metadata.dat, see README_RU.txt of zusa99.zip) for:
//   breakableType        full name of the breakable-object component class, e.g. the class "BreakableObjectBase" with its
//                        namespace and assembly, in the form engine.type() takes: 'Namespace.Type, Assembly-CSharp'.
//   getComponentInParent RVA of UnityEngine.Component.GetComponentInParent(System.Type, bool) in UnityEngine.CoreModule
//                        (script.json ScriptMethod, name "UnityEngine.Component$$GetComponentInParent"); compare with the RVA of
//                        GetComponentInChildren(Type,bool) that world-visuals.js already calls (0xA77E310).
//   getComponentInParentMethodInfo   MethodInfo for the call, if the dump lists one for that overload; otherwise leave 0.
const WALL_RULES={
  build:'StandKnife 3.3 (zusa99.zip dump, 2026-11-17)',
  breakableType:null,
  getComponentInParent:null,
  // Penetration thresholds on BreakableObjectBase are not read: a breakable object counts as passable and the game decides
  // how much power it takes. Set to an object-field offset once measured to compare against the weapon's penetration power.
  thresholdOffset:null
};

export function wallRulesReady(config=WALL_RULES){
  return config.breakableType!==null&&config.getComponentInParent!==null;
}

// Classifier for one obstacle collider. 'engine' is the engine helper of the module (type lookup and method binding); results are
// cached per collider for the life of the session, because map colliders and breakable objects keep their identity.
export function createWallRules({engine,config=WALL_RULES,log=()=>{}}){
  const cache=new Map();
  let logged=false,getInParent=null,breakableType=null;
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
      if(!bind()){
        if(!logged){logged=true;log('CLOUD:wall-rules unset ('+config.build+'): only the direct line and players are passable');}
        return null;
      }
      const key=collider.toString();
      if(cache.has(key))return cache.get(key);
      let verdict=null;
      try{
        const found=getInParent(collider,breakableType,1,ptr(0));
        verdict=!found.isNull();
      }catch(error){log('CLOUD:wall-rules-error '+error);}
      if(verdict!==null)cache.set(key,verdict);
      return verdict;
    },
    reset(){cache.clear();}
  };
}
