import {createEngine} from '../assets/engine.js';

export const worldFeatureNames=['Item ESP','Grenades','Off-screen Nades','Molotov Radius','Smoke Radius','Player Nades','Bomb Timer','Grenade Glow','Penetration'];
export function worldRing(center,radius,segments=32){
  if(!center||!center.every(Number.isFinite)||!Number.isFinite(radius)||radius<=0||radius>100)return [];
  return Array.from({length:segments+1},(_,index)=>{
    const angle=index*2*Math.PI/segments;
    return [center[0]+Math.cos(angle)*radius,center[1]+.05,center[2]+Math.sin(angle)*radius];
  });
}
const grenadeNames={91:'HE',92:'Smoke',93:'Flash',94:'Molotov',95:'Incendiary',97:'Molotov',99:'Snowball',191:'Atomic',192:'Fireball',193:'Darkball',194:'Holyball',195:'Thunderbolt'};
export function grenadeName(id){return grenadeNames[id]||'';}
export function validatedBombTime(now,planted,duration,rawDuration){
  if(![now,planted,duration,rawDuration].every(Number.isFinite)||duration<1||duration>180)return null;
  if(Math.abs(duration-rawDuration)>.01||planted<0||now<planted||now-planted>duration+1)return null;
  return Math.max(0,duration-(now-planted));
}
export function createWorldVisuals(context){
  const {native,settings,transform,position,project,readManagedString}=context;
  const engine=createEngine(native),groups=new Map(),errors=new Set(),rendererCache=new Map();
  let glowPlayers=new Map(),probeHit=null,probeReverse=null;
  const safeFloat=['int','int'];
  let previousScan=-Infinity,previousFlags='',timerFault=false,lastReport=-Infinity;
  const effectPlaying=new Map();
  const typeNames={
    items:'Axlebolt.Standoff.Inventory.Drop.WeaponDropController, Assembly-CSharp',
    grenades:'Axlebolt.Standoff.Inventory.Grenade.DroppedGrenadeController, Assembly-CSharp',
    effects:'Axlebolt.Standoff.Inventory.Grenade.GrenadeEffectController, Assembly-CSharp',
    bombs:'Axlebolt.Standoff.Inventory.Bomb.PlantedBombController, Assembly-CSharp'
  };
  // Finding these objects with Object.FindObjectsOfType freezes the game thread for 40-300 ms per scan (CLOUD:capture-slow ... worldScanMs).
  // When a lifecycle hook is available for a kind, its objects are registered as the game creates them and the scene is not scanned
  // periodically any more. Entries are pinned while registered and checked for native liveness (and for being active in the scene)
  // on every use, exactly like scanned objects. 'seed' kinds are scanned once when the feature is switched on (or after a reset),
  // because objects that already exist then never pass through the hook; effects are transient, so they are never seeded.
  // A kind without a working hook keeps the periodic scan as its fallback.
  const kinds={
    items:{type:typeNames.items,on:()=>settings['Item ESP'],cap:128,seed:true},
    grenades:{type:typeNames.grenades,on:()=>settings.Grenades||settings['Off-screen Nades']||settings['Grenade Glow'],cap:64,seed:true},
    effects:{type:typeNames.effects,on:()=>settings['Molotov Radius']||settings['Smoke Radius'],cap:64,seed:false,maxAge:90000},
    bombs:{type:typeNames.bombs,on:()=>settings['Bomb Timer'],cap:8,seed:true}
  };
  for(const kind of Object.values(kinds)){kind.hooked=false;kind.seeded=false;kind.registry=new Map();}
  let scanInterval=1500;
  function dropEntry(kind,key,entry){
    engine.release(entry.object);kind.registry.delete(key);
    const renderer=rendererCache.get('grenade:'+key);if(renderer){engine.release(renderer);rendererCache.delete('grenade:'+key);}
  }
  function trim(kind){while(kind.registry.size>kind.cap){const oldest=kind.registry.keys().next().value;dropEntry(kind,oldest,kind.registry.get(oldest));}}
  function noteObject(name,object){
    const kind=kinds[name];
    if(!kind||!object||object.isNull()||!kind.on())return;
    const key=object.toString(),entry=kind.registry.get(key),now=Date.now();
    if(entry){entry.t=now;return;}
    kind.registry.set(key,{object:engine.hold(object),t:now});
    if(kind.registry.size<=3||kind.registry.size%8===0)console.log('CLOUD:'+(name==='effects'?'effect-registered controllers=':'world-registered kind='+name+' count=')+kind.registry.size);
    trim(kind);
  }
  function noteEffect(object){noteObject('effects',object);}
  // A pooled object can stay alive but be switched off; it is skipped while inactive and shown again when reactivated.
  function activeInScene(object){
    try{
      const gameObject=engine.method(0xa77dd70,'pointer',['pointer','pointer'])(object,ptr(0));
      return gameObject.isNull()||!!engine.method(0xa784ac8,'bool',['pointer','pointer'])(gameObject,ptr(0));
    }catch(error){report('active-unavailable',error);return true;}
  }
  function registered(kind,now){
    const result=[];
    for(const [key,entry] of [...kind.registry]){
      let alive=false;
      try{alive=engine.live(entry.object);}catch(error){report('registry-live-error',error);}
      if(!alive||(kind.maxAge&&now-entry.t>kind.maxAge)){dropEntry(kind,key,entry);continue;}
      if(kind.maxAge||activeInScene(entry.object))result.push(entry.object);
    }
    return result;
  }
  function clearKind(kind){
    for(const [key,entry] of [...kind.registry])dropEntry(kind,key,entry);
    clearGroup(kind.type);kind.seeded=false;
  }
  function setHook(name,on){
    const kind=kinds[name];if(!kind)return;
    kind.hooked=!!on;clearKind(kind);
  }
  function setEffectHook(on){setHook('effects',on);}
  function report(label,error){if(!errors.has(label)){errors.add(label);console.log('CLOUD:world-'+label+' '+error);}}
  function clearGroup(name){
    const group=groups.get(name);if(group)for(const object of group)engine.release(object);
    groups.delete(name);
  }
  function scanGroup(name,enabled){
    clearGroup(name);if(!enabled)return;
    try{groups.set(name,engine.find(name,96));}catch(error){report('scan-error '+name,error);}
  }
  function seed(kind){
    try{
      const now=Date.now();
      for(const object of engine.find(kind.type,96)){
        const key=object.toString();
        if(kind.registry.has(key))engine.release(object);else kind.registry.set(key,{object,t:now});
      }
      trim(kind);
    }catch(error){report('seed-error '+kind.type,error);}
  }
  // Returns how long the scanning took in milliseconds, or 0 when none ran. Object.FindObjectsOfType walks the whole scene.
  function updateScan(now){
    const flags=worldFeatureNames.map(name=>!!settings[name]).join(',');
    const changed=flags!==previousFlags,due=changed||now-previousScan>=scanInterval;
    if(!due&&!Object.values(kinds).some(kind=>kind.hooked&&kind.seed&&!kind.seeded&&kind.on()))return 0;
    const began=Date.now();let periodic=false;
    if(due){previousFlags=flags;previousScan=now;}
    if(changed||(due&&!kinds.grenades.hooked)){for(const renderer of rendererCache.values())engine.release(renderer);rendererCache.clear();}
    for(const kind of Object.values(kinds)){
      if(!kind.on()){if(kind.registry.size||groups.has(kind.type)||kind.seeded)clearKind(kind);continue;}
      if(kind.hooked){if(kind.seed&&!kind.seeded){kind.seeded=true;seed(kind);}continue;}
      if(due){periodic=true;scanGroup(kind.type,true);}
    }
    const elapsed=Date.now()-began;
    // A periodic scan blocks the game thread: wait at least 50 times as long as the last one took (1.5 s to 12 s).
    if(periodic)scanInterval=Math.max(1500,Math.min(12000,elapsed*50));
    return elapsed;
  }
  function label(object,offset,fallback){
    const parameters=object.add(offset).readPointer();
    if(parameters.isNull())return fallback;
    const name=readManagedString(parameters.add(0x20).readPointer());
    return name?name.slice(0,40):fallback;
  }
  function objectPosition(object){
    const selected=transform(object,ptr(0));if(selected.isNull())return null;
    const pos=position(selected,ptr(0));return pos.every(Number.isFinite)?pos:null;
  }
  function bombTime(object){
    if(timerFault)return null;
    // Validate the safe-float decoder against the bomb's serialized duration.
    // Never substitute a guessed timer if its encoding/clock cannot be validated.
    const parameters=object.add(0x20).readPointer();if(parameters.isNull())return null;
    const durationPair=engine.method(0x5be4e34,safeFloat,['pointer','pointer'])(parameters,ptr(0));
    const decode=engine.method(0x5e84d48,'float',[safeFloat,'pointer']);
    const duration=decode(durationPair,ptr(0)),rawDuration=parameters.add(0x114).readFloat();
    if(!Number.isFinite(duration)||Math.abs(duration-rawDuration)>.01){timerFault=true;report('timer-unavailable','Safe-float validation failed');return null;}
    const planted=decode(engine.method(0x519d9e0,safeFloat,['pointer','pointer'])(object,ptr(0)),ptr(0));
    const now=engine.method(0xa799c08,'float',['pointer'])(ptr(0));
    return validatedBombTime(now,planted,duration,rawDuration);
  }
  function snapshot(camera){
    const output={objects:[],rings:[],bombs:[],t:Date.now()};glowPlayers=new Map();
    if(!worldFeatureNames.some(name=>settings[name])||(context.canRun&&!context.canRun())){
      for(const kind of Object.values(kinds))clearKind(kind);
      for(const name of [...groups.keys()])clearGroup(name);
      for(const renderer of rendererCache.values())engine.release(renderer);rendererCache.clear();
      previousFlags='';return output;
    }
    output.scanMs=updateScan(output.t);
    if(!settings.Penetration&&!Object.values(kinds).some(kind=>kind.registry.size)&&![...groups.values()].some(group=>group.length))return output;
    const cameraPos=objectPosition(camera);if(!cameraPos)return output;
    function visit(name,callback,list){for(const object of list||groups.get(name)||[])try{if(engine.live(object))callback(object);}catch(error){report('object-error '+name,error);}}
    function marker(object,name,kind){
      const pos=objectPosition(object);if(!pos)return;
      const distance=Math.hypot(...pos.map((value,index)=>value-cameraPos[index]));
      if(!Number.isFinite(distance)||distance>settings['Max Distance'])return;
      const point=project(camera,pos);if(point)output.objects.push({key:object.toString(),pos,point,distance,name,kind});
    }
    if(settings.Penetration)try{
      const vector=['float','float','float'];
      if(!probeHit){probeHit=Memory.alloc(0x100);probeReverse=Memory.alloc(0x100);}
      const forward=engine.method(0xa7a0a78,vector,['pointer','pointer'])(transform(camera,ptr(0)),ptr(0));
      const endpoint=cameraPos.map((value,index)=>value+forward[index]*settings['Aim Range']);
      const cast=engine.method(0xa8261c8,'bool',[vector,vector,'pointer','int','int','pointer']);
      const point=engine.method(0xa82b12c,vector,['pointer','pointer']),collider=engine.method(0xa82b000,'pointer',['pointer','pointer']);
      output.penetration={clear:!cast(cameraPos,endpoint,probeHit,-1,1,ptr(0)),thickness:null};
      if(!output.penetration.clear){
        const obstacle=collider(probeHit,ptr(0)),entry=point(probeHit,ptr(0));
        if(!obstacle.isNull()&&cast(endpoint,cameraPos,probeReverse,-1,1,ptr(0))&&collider(probeReverse,ptr(0)).equals(obstacle)){
          const exit=point(probeReverse,ptr(0)),thickness=Math.hypot(...entry.map((value,index)=>value-exit[index]));
          if(Number.isFinite(thickness)&&thickness<=settings['Aim Range'])output.penetration.thickness=thickness;
        }
      }
    }catch(error){report('penetration-error',error);}
    const listOf=name=>kinds[name].hooked?registered(kinds[name],output.t):undefined;
    visit(typeNames.items,object=>marker(object,label(object,0x78,'Weapon'),'item'),listOf('items'));
    visit(typeNames.grenades,object=>{
      const state=object.add(0x6c).readU8();if(state>1)return;
      if(settings['Grenade Glow']){
        const key='grenade:'+object.toString();
        let renderer=rendererCache.get(key);
        if(!renderer){
          renderer=engine.method(0xa77e310,'pointer',['pointer','pointer','bool','pointer'])(object,engine.type('UnityEngine.Renderer, UnityEngine.CoreModule'),0,ptr(0));
          if(engine.live(renderer))rendererCache.set(key,engine.hold(renderer));
        }
        if(renderer&&engine.live(renderer))glowPlayers.set(key,{player:object,renderer,kind:'grenade',local:false,team:0,t:output.t});
      }
      const id=object.add(0xc8).readU8();marker(object,grenadeName(id)||label(object,0x30,'Grenade'),'grenade');
    },listOf('grenades'));
    visit(typeNames.effects,object=>{
      const id=object.add(0x50).readU8();
      if(!(id===92&&settings['Smoke Radius'])&&!([94,95,97].includes(id)&&settings['Molotov Radius']))return;
      const parameters=object.add(0x38).readPointer(),particles=object.add(0x28).readPointer();
      if(parameters.isNull()||!engine.live(particles))return;
      // The controller object outlives its effect, so a ring is shown only while the effect's particle system is still playing
      // (ParticleSystem.get_isPlaying, RVA 0xA81E2F4 in the 3.3 dump). If the game cannot be asked, the ring behaves as before.
      let playing=true;
      try{playing=!!engine.method(0xa81e2f4,'bool',['pointer','pointer'])(particles,ptr(0));}
      catch(error){report('effect-playing-unavailable',error);}
      const key=object.toString();
      if(effectPlaying.get(key)!==playing){
        effectPlaying.set(key,playing);if(effectPlaying.size>64)effectPlaying.delete(effectPlaying.keys().next().value);
        console.log('CLOUD:effect id='+id+' playing='+playing);
      }
      if(!playing)return;
      const center=objectPosition(particles);if(!center)return;
      // The configured radius does not match what the player sees: molotov fire spreads wider and smoke is smaller than the ring.
      // Both are scaled by user settings in percent (defaults chosen from screenshots, adjustable in the menu).
      const scale=(id===92?settings['Smoke Radius Scale']:settings['Molotov Radius Scale'])/100;
      const radius=parameters.add(0x54).readFloat()*(Number.isFinite(scale)&&scale>0?scale:1);
      const worldPoints=worldRing(center,radius,16),points=worldPoints.map(point=>project(camera,point));
      if(points.length)output.rings.push({name:grenadeName(id),worldPoints,points,kind:id===92?'smoke':'fire'});
    },listOf('effects'));
    visit(typeNames.bombs,object=>{
      if(!engine.method(0x519d65c,'bool',['pointer','pointer'])(object,ptr(0))||
         engine.method(0x5198c84,'bool',['pointer','pointer'])(object,ptr(0))||
         engine.method(0x519b1d0,'bool',['pointer','pointer'])(object,ptr(0)))return;
      let seconds=null;try{seconds=bombTime(object);}catch(error){timerFault=true;report('timer-unavailable',error);}
      output.bombs.push({key:object.toString(),seconds});
      marker(object,'C4','bomb');
    },listOf('bombs'));
    if(output.t-lastReport>=15000){
      lastReport=output.t;console.log('CLOUD:world-frame objects='+output.objects.length+' radii='+output.rings.length+' glow='+glowPlayers.size+' bombs='+output.bombs.length+' timerValid='+output.bombs.some(bomb=>Number.isFinite(bomb.seconds)));
    }
    return output;
  }
  function inventory(player){
    if(!settings['Player Nades'])return [];
    try{
      const weapons=player.add(0xf0).readPointer();if(weapons.isNull())return [];
      const list=weapons.add(0x60).readPointer();if(list.isNull())return [];
      const count=list.add(0x18).readS32(),array=list.add(0x10).readPointer();
      if(count<0||count>32||array.isNull())return [];
      const result=[];
      for(let i=0;i<count;i++){
        const weapon=array.add(0x20+i*8).readPointer();if(weapon.isNull())continue;
        const parameters=weapon.add(0xb8).readPointer();if(parameters.isNull())continue;
        const name=grenadeName(parameters.add(0x18).readU8());if(name)result.push(name);
      }
      return result;
    }catch(error){report('inventory-error',error);return [];}
  }
  function reset(){for(const name of groups.keys())clearGroup(name);rendererCache.clear();glowPlayers.clear();effectPlaying.clear();for(const kind of Object.values(kinds)){kind.registry.clear();kind.seeded=false;}engine.reset();previousFlags='';previousScan=-Infinity;scanInterval=1500;timerFault=false;}
  return {snapshot,inventory,reset,glowPlayers:()=>glowPlayers,noteEffect,setEffectHook,noteObject,setHook};
}
