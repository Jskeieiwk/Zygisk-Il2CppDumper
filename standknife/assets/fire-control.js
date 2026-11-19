export function decodeCommand(value) {
  const hex=value.toString().replace(/^0x/,'').padStart(16,'0');
  const bytes=Array.from({length:6},(_,i)=>parseInt(hex.slice(14-i*2,16-i*2),16));
  return bytes.every(value=>value===0||value===1)?bytes:null;
}
// The fire flag was measured as byte 0 (mask 0x01) in every device log since v0.24, so the calibration starts from it and
// automatic fire works without the player shooting first. Real shots still refine it: a shot without that byte switches back
// to learning from scratch.
export const MEASURED_FIRE_BYTES=[1,0,0,0,0,0];
export function createFireCalibration(seed=MEASURED_FIRE_BYTES) {
  let common=seed?seed.slice():null,samples=seed?3:0;
  return {
    observe(bytes,shots){
      if(!bytes||shots<=0||!bytes.some(Boolean))return;
      const next=common?common.map((value,index)=>value&&bytes[index]?1:0):bytes.slice();
      if(!next.some(Boolean)){common=bytes.slice();samples=1;}
      else{common=next;samples++;}
    },
    reset(){common=seed?seed.slice():null;samples=seed?3:0;},
    state(){
      const indices=common?common.flatMap((value,index)=>value?[index]:[]):[];
      const ready=samples>=3&&indices.length===1;
      const mask=ready?'0x'+Array.from({length:8},(_,i)=>i===indices[0]?'01':'00').reverse().join(''):null;
      return {ready,samples,mask};
    }
  };
}
// Automatic fire as a real click: the flag is held for pressMs, then released for at least releaseMs (the Trigger Delay), so
// semi-automatic and bolt-action weapons (AWM, SSG) see a press and a release instead of a single-frame flag.
export function createClicker(pressMs=80){
  let pressStart=-Infinity,releasedAt=-Infinity;
  return {
    // wanted: the trigger condition holds now. Returns true while the fire flag must be set.
    update(wanted,now,releaseMs){
      if(now-pressStart<pressMs)return true;
      if(pressStart>releasedAt)releasedAt=pressStart+pressMs;
      if(wanted&&now-releasedAt>=Math.max(releaseMs,40)){pressStart=now;return true;}
      return false;
    },
    pressing:now=>now-pressStart<pressMs,
    reset(){pressStart=-Infinity;releasedAt=-Infinity;}
  };
}
// The command is six 0/1 bytes. Byte 0 is the fire flag (measured). The byte that presses the scope button is not known, so it
// is learned like the fire flag: every time the player's own scope opens, the bytes that were set in the commands seen shortly
// before it are intersected with the earlier openings. After three openings with exactly one common byte (never the fire byte)
// that byte is the scope button. The player scopes in by hand three times with a sniper rifle; nothing is assumed beyond that.
export const SCOPE_WINDOW_MS=500;
export function createScopeCalibration(fireIndex=0){
  let common=null,samples=0;
  return {
    // history: [{t,bytes}] of recent commands; opened: time the scope was seen opening.
    observe(history,opened){
      const seen=[0,0,0,0,0,0];
      for(const entry of history)if(opened-entry.t>=0&&opened-entry.t<=SCOPE_WINDOW_MS)entry.bytes.forEach((value,index)=>{if(value&&index!==fireIndex)seen[index]=1;});
      if(!seen.some(Boolean))return;
      const next=common?common.map((value,index)=>value&&seen[index]?1:0):seen;
      if(!next.some(Boolean)){common=seen;samples=1;}else{common=next;samples++;}
    },
    reset(){common=null;samples=0;},
    state(){
      const indices=common?common.flatMap((value,index)=>value?[index]:[]):[];
      const ready=samples>=3&&indices.length===1;
      const mask=ready?'0x'+Array.from({length:8},(_,i)=>i===indices[0]?'01':'00').reverse().join(''):null;
      return {ready,samples,candidates:indices,mask};
    }
  };
}
// Penetration power applied while Autowall is on: the game's own value times this factor (it was the 'Wall Power' slider,
// default 3, until v0.37). Not tuned against any wall; the game still decides what a bullet can pass.
export const WALL_POWER_SCALE=3;
export function installFireControl(context) {
  const {base,native,settings,getLocalPlayer,getAim,active}=context;
  const calibration=createFireCalibration(),shotId=native(0x42da568,'int',['pointer','pointer']);
  const getRotation=native(0x5452708,['float','float','float'],['pointer','pointer']);
  const setRotation=native(0x54519e4,'void',['pointer',['float','float','float'],'pointer']);
  let warnings=0,lastTrigger=0,lastKnife=0,reported=false,hookKey='',shotLogs=0,lastShotLog=0,clickLogs=0;
  const clicker=createClicker(),scopeClicker=createClicker(),scopeCalibration=createScopeCalibration();
  let commandHistory=[],scopeWasOpen=false,scopeAttempts=0,scopeBackoffUntil=0,scopeLogs=0,scopeReported=false,lastScopeWanted=0;
  const getScope=context.getScope||(()=>null);
  // One click is followed for 350 ms: how many shots the game counted for it, with which weapon, its penetration power
  // (WeaponParameters+0x1A4, the value Autowall scales) and the wall the shot was aimed through.
  let pendingClick=null,silentLogs=0,lastSilentLog=0;
  function weaponInfo(weapon){
    try{const parameters=weapon.add(0xb8).readPointer();if(!parameters.isNull())return {id:parameters.add(0x18).readU8(),power:parameters.add(0x1a4).readS32()};}
    catch(error){}
    return {id:-1,power:-1};
  }
  function reachText(aim){
    const reach=aim&&aim.selected&&aim.selected.reach;
    return reach?(reach.direct?'direct':'through='+reach.walls):'crosshair';
  }
  function finishClick(now,force=false){
    if(!pendingClick||(!force&&now-pendingClick.at<350))return;
    const click=pendingClick;pendingClick=null;
    try{console.log('CLOUD:trigger-click weapon='+click.id+' power='+click.power+' shots='+(shotId(click.weapon,ptr(0))-click.before)+' reach='+click.reach);}
    catch(error){}
  }
  // One line per automatic shot (at most 80 per session, one per 400 ms) saying why it was allowed.
  function logShot(kind,aim){
    const now=Date.now();if(shotLogs>=80||now-lastShotLog<400)return;
    shotLogs++;lastShotLog=now;
    const reach=aim.selected&&aim.selected.reach;
    const text=reach?(reach.direct?'direct':'through='+reach.walls):
      (kind==='trigger'&&!settings.Autowall?'crosshair-ray':'unchecked');
    const chance=aim.hitchance?' hitchance='+JSON.stringify(aim.hitchance):'';
    console.log('CLOUD:auto-shot kind='+kind+' reach='+text+chance);
  }
  const canRun=context.canRun||(()=>false),generation=context.generation||(()=>0);
  let listeners=[];
  function enabled(){return settings['Knife Bot']||settings.Trigger||settings['Force Shot']||settings['Silent Aim']||settings['Auto Scope']||settings['Auto Calibration']||settings.Autowall||settings['Autowall (Aim)'];}
  function ensureInstalled(){
    if(!enabled()||!canRun()){if(listeners.length)reset();return;}
    const key=String(!!settings['Knife Bot']);if(listeners.length&&key===hookKey)return;
    if(listeners.length)reset(false);
    try{installHooks();hookKey=key;console.log('CLOUD:fire-hooks-active generation='+generation());}
    catch(error){reset();if(warnings++<5)console.log('CLOUD:fire-hooks-error '+error);}
  }
  function reset(clearCalibration=true){
    for(const listener of listeners)listener.detach();
    if(listeners.length)console.log('CLOUD:fire-hooks-suspended');
    listeners=[];if(clearCalibration){calibration.reset();scopeCalibration.reset();scopeReported=false;}lastTrigger=0;lastKnife=0;reported=false;hookKey='';clicker.reset();scopeClicker.reset();commandHistory=[];scopeWasOpen=false;scopeAttempts=0;scopeBackoffUntil=0;pendingClick=null;
  }
  // Auto Scope: learn the scope byte from the player's own scope openings, then press it (as a click, not a held flag) when a
  // sniper rifle is in hand, the scope is closed and the aim has a fresh target. Two clicks without the scope opening mean the
  // learned byte is not the scope button (or the scope is a toggle that lagged): the module backs off for 1.5 s and logs it.
  function handleScope(args,bytes){
    const now=Date.now(),scope=getScope();
    commandHistory.push({t:now,bytes});
    while(commandHistory.length&&now-commandHistory[0].t>SCOPE_WINDOW_MS*2)commandHistory.shift();
    if(!scope)return false;
    if(scope.active&&!scopeWasOpen){
      // Openings caused by our own click do not teach anything.
      if(!scopeClicker.pressing(now)&&now-lastScopeWanted>SCOPE_WINDOW_MS)scopeCalibration.observe(commandHistory,now);
      scopeAttempts=0;
    }
    scopeWasOpen=!!scope.active;
    const learned=scopeCalibration.state();
    if(learned.ready&&!scopeReported){scopeReported=true;console.log('CLOUD:scope-calibrated mask='+learned.mask+' samples='+learned.samples);}
    const aim=getAim();
    const wanted=learned.ready&&active()&&scope.sniper&&!scope.active&&!!aim&&!!aim.selected&&now-aim.t<=150&&now>=scopeBackoffUntil;
    if(wanted)lastScopeWanted=now;
    const pressing=scopeClicker.pressing(now);
    if(wanted&&!pressing&&scopeAttempts>=2){scopeBackoffUntil=now+1500;scopeAttempts=0;
      if(scopeLogs++<30)console.log('CLOUD:auto-scope-gave-up mask='+learned.mask+' (the scope did not open after 2 clicks)');return false;}
    const starting=wanted&&!pressing;
    if(scopeClicker.update(wanted,now,500)){
      args[1]=args[1].or(ptr(learned.mask));
      if(starting){scopeAttempts++;if(scopeLogs++<30)console.log('CLOUD:auto-scope click n='+scopeAttempts);}
      return true;
    }
    return false;
  }
  function installHooks(){
  function relevant(){return settings['Knife Bot']||settings.Trigger||settings['Force Shot']||settings['Silent Aim']||settings['Auto Scope']||settings['Auto Calibration'];}
  listeners.push(Interceptor.attach(base.add(0x42e52cc),{
    onEnter(args){
      this.changed=false;
      if(!relevant()||!canRun())return;
      this.generation=generation();
      try{
        const local=getLocalPlayer();if(!local||local.isNull()||!args[0].add(0x20).readPointer().equals(local))return;
        const bytes=decodeCommand(args[1]);if(!bytes)return;
        this.weapon=args[0];this.bytes=bytes;this.training=!calibration.state().ready;
        if(settings['Auto Scope'])this.scopeInjected=handleScope(args,bytes);
        if(this.training)this.before=shotId(this.weapon,ptr(0));
        const trained=calibration.state(),aim=getAim(),now=Date.now();
        if(!trained.ready||!active()||!aim||now-aim.t>150)return;
        // Force Shot and Silent Aim only act on a target with a clear line to it (aim.clear); a wall in between means no shot.
        const forced=!!(settings['Force Shot']&&aim.selected&&aim.clear);
        const auto=settings['Force Shot']?forced:settings.Trigger&&aim.crosshair;
        finishClick(now);
        const starting=auto&&!clicker.pressing(now);
        if(clicker.update(!!auto,now,settings['Trigger Delay'])){
          args[1]=args[1].or(ptr(trained.mask));this.injected=true;
          if(starting){lastTrigger=now;logShot(settings['Force Shot']?'force':'trigger',aim);
            if(clickLogs<40&&!pendingClick){clickLogs++;const info=weaponInfo(this.weapon);
              pendingClick={weapon:this.weapon,at:now,before:shotId(this.weapon,ptr(0)),id:info.id,power:info.power,reach:reachText(aim)};}}
        }
        const firing=!args[1].and(ptr(trained.mask)).isNull();
        if(firing && aim.selected && ((settings['Silent Aim']&&aim.clear)||forced)){
          this.controller=local.add(0x128).readPointer();
          if(!this.controller.isNull()){
            this.oldRotation=getRotation(this.controller,ptr(0));this.changed=true;
            setRotation(this.controller,aim.selected.angles,ptr(0));
            if(!this.injected&&silentLogs<40&&now-lastSilentLog>=400){silentLogs++;lastSilentLog=now;
              const info=weaponInfo(this.weapon);console.log('CLOUD:silent-shot weapon='+info.id+' power='+info.power+' reach='+reachText(aim));}
          }
        }
      }catch(error){if(warnings++<5)console.log('CLOUD:fire-control-error '+error);}
    },
    onLeave(){
      try{
        if(this.generation!==generation()||!canRun())return;
        if(this.changed)setRotation(this.controller,this.oldRotation,ptr(0));
        if(this.training&&this.weapon&&!this.injected){
          const after=shotId(this.weapon,ptr(0));calibration.observe(this.bytes,Math.max(0,after-this.before));
          const state=calibration.state();
          if(state.ready&&!reported){reported=true;console.log('CLOUD:fire-calibrated mask='+state.mask+' samples='+state.samples);}
        }
      }catch(error){if(warnings++<5)console.log('CLOUD:fire-restore-error '+error);}
    }
  }));
  if(settings['Knife Bot'])listeners.push(Interceptor.attach(base.add(0x5af1fc0),{
    onEnter(args){
      if(!canRun()||!active())return;
      try{
        const local=getLocalPlayer(),aim=getAim(),state=calibration.state(),now=Date.now();
        if(!local||!args[0].add(0x20).readPointer().equals(local)||!state.ready||!aim||!aim.isKnife||!aim.selected||now-aim.t>150)return;
        if(now-lastKnife<Math.max(150,settings['Trigger Delay']))return;
        if(!decodeCommand(args[1]))return;
        args[1]=args[1].or(ptr(state.mask));lastKnife=now;
        this.controller=local.add(0x128).readPointer();if(this.controller.isNull())return;
        this.generation=generation();this.old=getRotation(this.controller,ptr(0));this.changed=true;
        setRotation(this.controller,aim.selected.angles,ptr(0));
      }catch(error){if(warnings++<5)console.log('CLOUD:knife-error '+error);}
    },
    onLeave(){if(this.changed&&this.generation===generation()&&canRun())try{setRotation(this.controller,this.old,ptr(0));}catch(error){if(warnings++<5)console.log('CLOUD:knife-restore-error '+error);}}
  }));
  listeners.push(Interceptor.attach(base.add(0x4136838),{
    onEnter(args){
      if(!canRun()||(!settings.Autowall&&!settings['Autowall (Aim)']))return;
      this.generation=generation();
      try{
        const local=getLocalPlayer();if(!local||local.isNull())return;
        const inventory=local.add(0xf0).readPointer();if(inventory.isNull())return;
        const weapon=inventory.add(0xa8).readPointer();if(weapon.isNull())return;
        const parameters=weapon.add(0xb8).readPointer();if(!parameters.equals(args[0]))return;
        const power=parameters.add(0x1a4),old=power.readS32();
        if(old<=0||old>10000)return;
        this.power=power;this.old=old;this.safe=parameters.add(0x264);this.oldSafe=this.safe.readByteArray(12);this.changed=true;
        power.writeS32(Math.min(10000,Math.round(old*WALL_POWER_SCALE)));this.safe.writeU8(0);
      }catch(error){if(warnings++<5)console.log('CLOUD:penetration-error '+error);}
    },
    onLeave(){if(this.changed&&this.generation===generation()&&canRun())try{this.power.writeS32(this.old);this.safe.writeByteArray(this.oldSafe);}catch(error){if(warnings++<5)console.log('CLOUD:penetration-restore-error '+error);}}
  }));
  }
  return {reset,suspend:()=>{if(listeners.length)reset(false);},ensureInstalled,
    needsCleanup:()=>listeners.length>0&&!enabled(),status:()=>calibration.state()};
}
