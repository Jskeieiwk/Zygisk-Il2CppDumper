// StandKnife 3.3 ARM64. All addresses refer to the recovered dump.cs.
export function createVisualFeatures(context) {
  const { native, settings, transform, position, project, readManagedString, getLocalPlayer } = context;
  const colorType = ['float', 'float', 'float', 'float'];
  const matrixType = Array(16).fill('float');
  const fn = {};
  function call(name, rva, result, args) {
    if (!fn[name]) fn[name] = native(rva, result, args);
    return fn[name];
  }
  function report(name, error) {
    if (!errors.has(name)) console.log('CLOUD:' + name + ' ' + error);
    errors.add(name);
  }
  const errors = new Set(), strings = new Map(), roots = new Map();
  function root(object) {
    if (object.isNull()) return object;
    const key = object.toString();
    if (!roots.has(key)) roots.set(key, call('root', 0x9647044, 'pointer', ['pointer','int','pointer'])(object, 2, ptr(0)));
    return object;
  }
  function release(object) {
    const handle = roots.get(object.toString());
    if (!handle) return;
    const storage = Memory.alloc(Process.pointerSize);
    storage.writePointer(handle);
    call('unroot', 0x9647058, 'void', ['pointer','pointer'])(storage, ptr(0));
    roots.delete(object.toString());
  }
  function string(value) {
    if (!strings.has(value)) {
      const utf8 = Memory.allocUtf8String(value);
      const length = unescape(encodeURIComponent(value)).length;
      const result = call('string', 0x95103ec, 'pointer', ['pointer','int','int','pointer'])(utf8, 0, length, ptr(0));
      if (result.isNull()) throw Error('Cannot create managed string');
      strings.set(value, root(result));
    }
    return strings.get(value);
  }
  function live(object) {
    return !object.isNull() && call('live', 0xa78ebc4, 'bool', ['pointer','pointer'])(object, ptr(0));
  }
  function clone(object) {
    const result = call('clone', 0xa78f844, 'pointer', ['pointer','pointer'])(object, ptr(0));
    if (result.isNull()) throw Error('Unity clone returned null');
    return root(result);
  }
  function destroy(object) {
    try {
      if (live(object)) call('destroy', 0xa790098, 'void', ['pointer','pointer'])(object, ptr(0));
    } finally { release(object); }
  }
  function arrayPointers(array, limit = 16) {
    if (array.isNull()) return [];
    const count = array.add(0x18).readU64().toNumber();
    if (count < 0 || count > limit) return [];
    const values = [];
    for (let i = 0; i < count; i++) values.push(array.add(0x20+i*8).readPointer());
    return values;
  }
  function properties(owner) {
    const output = {};
    if (owner.isNull()) return output;
    const table = owner.add(0x48).readPointer();
    if (table.isNull()) return output;
    const getter=call('propertyItem',0x9a43158,'pointer',['pointer','pointer','pointer']);
    for(const name of ['money','ping','Ping','clan_tag','ClanTag']) {
      const object=getter(table,string(name),ptr(0));
      if(object.isNull())continue;
      if(name==='money'||name.toLowerCase()==='ping') {
        const value=object.add(0x10).readS32();
        if(value>=0&&value<=(name==='money'?1000000:10000))output[name.toLowerCase()]=value;
      }else{
        const value=readManagedString(object);
        if(value.length<=32)output[name.toLowerCase()]=value;
      }
    }
    return output;
  }
  const avatarCache = new Map();let nextAvatar=0;
  function avatar(owner) {
    if (owner.isNull()) return null;
    const id = owner.toString()+':'+owner.add(0x18).readS32(), now=Date.now(), cached=avatarCache.get(id);
    if(cached && now-cached.t<(cached.bytes?15000:3000))return cached.bytes;
    if(now<nextAvatar)return cached?cached.bytes:null;
    nextAvatar=now+400;
    avatarCache.set(id,{t:now,bytes:null});
    try {
      const sprite = call('avatar', 0x5f9f9cc, 'pointer', ['pointer','pointer'])(owner, ptr(0));
      if (sprite.isNull()) return null;
      const texture = call('texture', 0xa7a644c, 'pointer', ['pointer','pointer'])(sprite, ptr(0));
      if (texture.isNull()) return null;
      const bytes = call('png', 0xa7cfbd0, 'pointer', ['pointer','pointer'])(texture, ptr(0));
      if (bytes.isNull()) return null;
      const length = bytes.add(0x18).readU64().toNumber();
      if (length <= 0 || length > 1024*1024) return null;
      const rect=call('spriteRect',0xa7a60e4,colorType,['pointer','pointer'])(sprite,ptr(0));
      const height=call('textureHeight',0xa7526bc,'int',['pointer','pointer'])(texture,ptr(0));
      const crop={x:Math.round(rect[0]),y:Math.round(height-rect[1]-rect[3]),width:Math.round(rect[2]),height:Math.round(rect[3])};
      if(!Object.values(crop).every(Number.isFinite)||crop.width<=0||crop.height<=0)return null;
      const result = { id, crop, bytes:new Uint8Array(bytes.add(0x20).readByteArray(length)) };
      avatarCache.set(id, { t:now, bytes:result });
      if (avatarCache.size > 64) avatarCache.delete(avatarCache.keys().next().value);
      return result;
    } catch (error) {
      if(now<nextAvatar)return cached?cached.bytes:null;
    nextAvatar=now+400;
    avatarCache.set(id,{t:now,bytes:null}); report('avatar-error',error); return null;
    }
  }
  function addDetails(item, player, owner) {
    if (settings.Money || settings.Ping || settings['Clan Tag']) {
      try {
        const data = properties(owner);
        item.money = Number.isFinite(data.money) ? data.money : null;
        item.ping = Number.isFinite(data.ping) ? data.ping : null;
        item.clan = typeof data.clan_tag === 'string' ? data.clan_tag :
          (typeof data.clantag === 'string' ? data.clantag : '');
      } catch (error) { report('properties-error',error); }
    }
    if (settings['Show Avatar']) item.avatar = avatar(owner);
    if (settings['Bomb Flag']) {
      try {
        const weaponry = player.add(0xf0).readPointer();
        if (!weaponry.isNull()) {
          // WeaponryController.GetWeaponSlots() exposes every carried weapon.
          const slots = weaponry.add(0x60).readPointer(); // List<WeaponController>
          if (!slots.isNull()) {
            const array = slots.add(0x10).readPointer(), count=slots.add(0x18).readS32();
            if (!array.isNull() && count >= 0 && count <= 32) {
              item.bomb = false;
              for (let i=0;i<count;i++) {
                const weapon=array.add(0x20+i*8).readPointer();
                if (weapon.isNull()) continue;
                const parameters=weapon.add(0xb8).readPointer();
                if (!parameters.isNull() && parameters.add(0x18).readU8()===100) item.bomb=true;
              }
            }
          }
        }
      } catch (error) { report('bomb-flag-error',error); }
    }
  }

  let command = null, commandCamera = null, shader = null, shaderRetry = 0;
  const playerModels = new Map(), ghosts = [];
  function rgba(hex, alpha = 1) {
    return [parseInt(hex.slice(1,3),16)/255, parseInt(hex.slice(3,5),16)/255, parseInt(hex.slice(5,7),16)/255, alpha];
  }
  function setMaterial(material, tint, alpha) {
    if (!live(material)) return;
    const shade = settings['Shader Chams'] ? .7+.3*Math.sin(Date.now()/250) : 1;
    const value = rgba(tint,alpha); value[0]*=shade; value[1]*=shade; value[2]*=shade;
    call('materialColor',0xa747ce8,'void',['pointer','pointer',colorType,'pointer'])(material,string('_Color'),value,ptr(0));
    const setInt=call('materialInt',0xa74a130,'void',['pointer','pointer','int','pointer']);
    const properties = { '_ZTest':settings['Model Vis Only']?4:8, '_ZWrite':0, '_Cull':0,
      '_SrcBlend':5, '_DstBlend':10 };
    for (const [name, number] of Object.entries(properties)) setInt(material,string(name),number,ptr(0));
  }
  function rendererFor(player) {
    const group = player.add(0x30).readPointer(); // CharacterLodGroup
    return group.isNull() ? ptr(0) : group.add(0x38).readPointer();
  }
  function modelFor(player, key, tint, selectedRenderer=null) {
    const renderer=selectedRenderer||rendererFor(player);
    if (!live(renderer)) return null;
    let model=playerModels.get(key);
    if (model && !model.renderer.equals(renderer)) { removePlayer(key); model=null; }
    if (!model) {
      const original=call('sharedMaterials',0xa7458e4,'pointer',['pointer','pointer'])(renderer,ptr(0));
      const originals=arrayPointers(original,16);
      if (!originals.length || originals.some(original=>!live(original))) return null;
      const materials=[];
      try {
        for (const original of originals) {
          if (!live(original)) continue;
          const material=clone(original);
          materials.push(material);
          call('shaderSet',0xa747748,'void',['pointer','pointer','pointer'])(material,shader,ptr(0));
          call('queue',0xa748228,'void',['pointer','int','pointer'])(material,4000,ptr(0));
        }
      } catch(error) { for (const material of materials) destroy(material); throw error; }
      model={ renderer:root(renderer), materials, original:root(original), lastGhost:0, t:Date.now() };
      playerModels.set(key,model);
    }
    model.t=Date.now();
    for (const material of model.materials) setMaterial(material,tint,settings['Chams Opacity']/100);
    return model;
  }
  function removePlayer(key) {
    const model=playerModels.get(key);
    if (!model) return;
    if(command)call('clearCommand',0xa7b75c0,'void',['pointer','pointer'])(command,ptr(0));
    for (const material of model.materials) destroy(material);
    release(model.original); release(model.renderer); playerModels.delete(key);
  }
  function clearGhosts() {
    while (ghosts.length) {
      const ghost=ghosts.pop(); destroy(ghost.mesh); destroy(ghost.material);
    }
  }
  function detachCommand() {
    if (!command) return;
    try {
      if (commandCamera && live(commandCamera)) call('removeCommand',0xa72b674,'void',['pointer','int','pointer','pointer'])(commandCamera,20,command,ptr(0));
      call('commandDispose',0xa7bae74,'void',['pointer','pointer'])(command,ptr(0));
    } finally {
      if (commandCamera) release(commandCamera);
      release(command); command=null; commandCamera=null;
    }
  }
  function ensureCommand(camera) {
    if (command && commandCamera.equals(camera)) return true;
    detachCommand();
    const type=call('type',0x9823338,'pointer',['pointer','pointer'])(string('UnityEngine.Rendering.CommandBuffer, UnityEngine.CoreModule'),ptr(0));
    if (type.isNull()) throw Error('CommandBuffer type unavailable');
    command=root(call('activate',0x983f018,'pointer',['pointer','pointer'])(type,ptr(0)));
    if (command.isNull()) throw Error('CommandBuffer allocation failed');
    commandCamera=root(camera);
    call('addCommand',0xa72b4a0,'void',['pointer','int','pointer','pointer'])(camera,20,command,ptr(0));
    console.log('CLOUD:chams-command-ready'); return true;
  }
  function loadShader() {
    if (shader && live(shader)) return true;
    if (Date.now()<shaderRetry) return false;
    shaderRetry=Date.now()+10000;
    for (const name of ['Hidden/Internal-Colored','Unlit/Color','Sprites/Default']) {
      const candidate=call('shaderFind',0xa7467f0,'pointer',['pointer','pointer'])(string(name),ptr(0));
      if (!candidate.isNull()) { shader=root(candidate); console.log('CLOUD:chams-shader '+name); return true; }
    }
    report('chams-error','No compatible shader loaded'); return false;
  }
  function updateChams(camera, players, getTeam) {
    const playersActive=settings['Player ESP'] && (settings.Chams || settings['3D Model'] || settings['Shader Chams'] || settings['Ghost Chams']);
    const active=playersActive||settings['Grenade Glow'];
    if (!active) {
      detachCommand(); clearGhosts();
      for (const key of Array.from(playerModels.keys())) removePlayer(key);
      return;
    }
    try {
      if (!loadShader() || !ensureCommand(camera)) return;
      call('clearCommand',0xa7b75c0,'void',['pointer','pointer'])(command,ptr(0));
      const draw=call('drawRenderer',0xa7bb49c,'void',['pointer','pointer','pointer','int','int','pointer']);
      const now=Date.now(), cameraTransform=transform(camera,ptr(0));
      const cameraPosition=cameraTransform.isNull()?null:position(cameraTransform,ptr(0));
      for (const [key,tracked] of players) {
        if (now-tracked.t>250 || tracked.local) continue;
        const grenade=tracked.kind==='grenade';
        if(grenade?!settings['Grenade Glow']:!playersActive)continue;
        const teammate=getTeam()>0 && tracked.team===getTeam();
        if (settings['Team Filter'] && teammate) continue;
        try {
          if(cameraPosition) {
            const targetTransform=transform(tracked.player,ptr(0));
            if(targetTransform.isNull())continue;
            const targetPosition=position(targetTransform,ptr(0));
            if(Math.hypot(...targetPosition.map((value,i)=>value-cameraPosition[i]))>settings['Max Distance'])continue;
          }
          const tint=grenade?'#ffc365':teammate?settings['Team Color']:settings['Enemy Color'];
          const model=modelFor(tracked.player,key,tint,tracked.renderer);
          if (!model) continue;
          if (grenade || settings.Chams || settings['Shader Chams'] || settings['3D Model']) {
            const original=arrayPointers(model.original);
            for (let i=0;i<model.materials.length;i++) {
              // 3D Model preserves the model's own material when color chams are off.
              const material=!grenade && settings['3D Model'] && !settings.Chams && !settings['Shader Chams'] ? original[i] : model.materials[i];
              if (material && live(material)) draw(command,model.renderer,material,i,0,ptr(0));
            }
          }
          if (!grenade && settings['Ghost Chams'] && now-model.lastGhost>=250 && ghosts.length<32) {
            model.lastGhost=now;
            const source=call('sharedMesh',0xa74c5e0,'pointer',['pointer','pointer'])(model.renderer,ptr(0));
            if (!live(source)) continue;
            const mesh=clone(source);
            let material=null;
            try {
              call('bake',0xa74c8d8,'void',['pointer','pointer','bool','pointer'])(model.renderer,mesh,0,ptr(0));
              const matrix=call('matrix',0xa79fab4,matrixType,['pointer','pointer'])(transform(model.renderer,ptr(0)),ptr(0));
              material=clone(model.materials[0]);
              ghosts.push({mesh,material,matrix,t:now,tint});
            } catch(error) { destroy(mesh); if(material)destroy(material); throw error; }
          }
        } catch(error) { report('chams-player-error',error); }
      }
      if (!settings['Ghost Chams']) clearGhosts();
      for (let i=ghosts.length-1;i>=0;i--) {
        const ghost=ghosts[i], age=now-ghost.t;
        if (age>900) { destroy(ghost.mesh); destroy(ghost.material); ghosts.splice(i,1); continue; }
        setMaterial(ghost.material,ghost.tint,.35*(1-age/900));
        const count=call('subMeshes',0xa74e780,'int',['pointer','pointer'])(ghost.mesh,ptr(0));
        for (let sub=0;sub<Math.min(8,count);sub++) call('drawMesh',0xa7bb46c,'void',['pointer','pointer',matrixType,'pointer','int','int','pointer'])(command,ghost.mesh,ghost.matrix,ghost.material,sub,0,ptr(0));
      }
      for (const [key,model] of playerModels) if(now-model.t>500)removePlayer(key);
    } catch(error) {
      report('chams-error',error);
      if(command)try{call('clearCommand',0xa7b75c0,'void',['pointer','pointer'])(command,ptr(0));}catch(ignored){}
    }
  }

  const events=[], traces=[], hitAnimators=new Set(), killAnimators=new Set();
  let eventSequence=0, hitCandidate=null;
  function recordEvent(kind) {
    const now=Date.now();
    if (events.some(event=>event.kind===kind && now-event.t<40))return;
    events.push({id:++eventSequence,kind,t:now,target:hitCandidate && now-hitCandidate.t<300 ? hitCandidate.key : null});
    if(events.length>24)events.shift();
  }
  let scopeActive=false, sniperWeapon=false, scopeGroup=null, originalScopeAlpha=null;
  const eventListeners=new Map();
  function attachEvent(rva,callbacks,label){
    if(context.attachHook)return context.attachHook(rva,callbacks,label);
    if(eventListeners.has(label))return true;
    try{eventListeners.set(label,Interceptor.attach(context.base.add(rva),callbacks));return true;}
    catch(error){report('hook-unavailable '+label,error);return false;}
  }
  function installScope() {
    attachEvent(0x6929a84,{
      onEnter(args){
        this.view=args[0];
        if(scopeGroup && originalScopeAlpha!==null && live(scopeGroup)) {
          call('scopeAlphaSet',0xab5c670,'void',['pointer','float','pointer'])(scopeGroup,originalScopeAlpha,ptr(0));
          originalScopeAlpha=null;
        }
      },
      onLeave(){try{
        if(context.canRun&&!context.canRun()){scopeActive=false;return;}
        const selected=this.view.add(0x50).readPointer();
        if(!scopeGroup || !scopeGroup.equals(selected)) {
          if(scopeGroup)release(scopeGroup);
          scopeGroup=selected.isNull()?selected:root(selected);
        }
        if(live(scopeGroup)) {
          const alpha=call('scopeAlpha',0xab5c4fc,'float',['pointer','pointer'])(scopeGroup,ptr(0));
          scopeActive=alpha>.01;
          if(settings['Custom Scope'] && scopeActive) {
            originalScopeAlpha=alpha;
            call('scopeAlphaSet',0xab5c670,'void',['pointer','float','pointer'])(scopeGroup,0,ptr(0));
          }
        } else scopeActive=false;
        const local=getLocalPlayer();
        sniperWeapon=false;
        if(local && !local.isNull()){
          const weaponry=local.add(0xf0).readPointer();
          if(!weaponry.isNull()){
            const weapon=weaponry.add(0xa8).readPointer();
            if(!weapon.isNull()){
              const parameters=weapon.add(0xb8).readPointer();
              if(!parameters.isNull())sniperWeapon=[51,52,53,54].includes(parameters.add(0x18).readU8());
            }
          }
        }
      }catch(error){report('scope-error',error);}}
    },'scope-view');
  }
  function rememberHitView(view){
    if(view.isNull())return;
    const hit=view.add(0x40).readPointer(),kill=view.add(0x50).readPointer();
    if(!hit.isNull())hitAnimators.add(hit.toString());if(!kill.isNull())killAnimators.add(kill.toString());
  }
  function seedHitView(){
    let array=null;
    try{
      const type=call('hitViewType',0x9823338,'pointer',['pointer','pointer'])(string('Axlebolt.Standoff.Controls.HitMarkerView, Assembly-CSharp'),ptr(0));
      if(type.isNull())return;
      array=root(call('hitViews',0xa790358,'pointer',['pointer','pointer'])(type,ptr(0)));
      for(const view of arrayPointers(array,16))rememberHitView(view);
    }catch(error){report('hit-view-seed-error',error);}finally{if(array&&!array.isNull())release(array);}
  }
  function installHits(){
    seedHitView();
    // SetPlayerController supplies the animator references. UpdateView is not required.
    for(const rva of [0x39db71c])attachEvent(rva,{
      onEnter(args){this.view=args[0];},onLeave(){try{
        if(context.canRun&&!context.canRun())return;
        hitAnimators.clear();killAnimators.clear();rememberHitView(this.view);
      }catch(error){report('hit-animator-error',error);}}
    },'hit-view');
    for(const rva of [0xa708984,0xa7087f0])attachEvent(rva,{onEnter(args){
      if(context.canRun&&!context.canRun())return;
      if(hitAnimators.has(args[0].toString()))recordEvent('hit');
      if(killAnimators.has(args[0].toString()))recordEvent('kill');
    }},'animator-'+rva.toString(16));
    attachEvent(0x39dc0bc,{onEnter(args){try{
      const local=getLocalPlayer();if(!local || local.isNull())return;
      const localOwner=local.add(0xa8).readPointer(), event=args[1];
      if(event.isNull())return;
      const owners=[event.add(0x10).readPointer(),event.add(0x18).readPointer()];
      if(!owners.some(owner=>owner.equals(localOwner)))return;
      for(const [key,tracked] of context.trackedPlayers){
        const owner=tracked.player.add(0xa8).readPointer();
        if(!owner.equals(localOwner) && owners.some(value=>value.equals(owner))){hitCandidate={key,t:Date.now()};break;}
      }
    }catch(error){report('hit-event-error',error);}}},'hit-event');
  }
  function installTracers(){
    attachEvent(0x3af3bf0,{onEnter(args){this.tracer=args[0];},onLeave(){
      if((context.canRun&&!context.canRun())||!settings['Bullet Tracers'])return;
      try{
        const read=offset=>[0,4,8].map(i=>this.tracer.add(offset+i).readFloat());
        const start=read(0x28),end=read(0x34),length=Math.hypot(...start.map((v,i)=>v-end[i]));
        if(start.every(Number.isFinite)&&end.every(Number.isFinite)&&length>.1&&length<1000){
          traces.push({start,end,t:Date.now()});if(traces.length>32)traces.shift();
        }
      }catch(error){report('bullet-trace-error',error);}
    }},'bullet-tracer');
  }
  function screenFrame(camera, snapshot) {
    const now=Date.now();
    while(events.length && now-events[0].t>4000)events.shift();
    while(traces.length && now-traces[0].t>700)traces.shift();
    for(const event of events){
      if(!event.target)continue;
      const item=snapshot.get(event.target), previous=healthHistory.get(event.target);
      if(item && previous && item.health>=0 && previous.health>item.health && now-event.t<350){
        const anchor=item.bonePositions&&item.bonePositions[0]||[item.pos[0],item.pos[1]+1.7,item.pos[2]];
        event.damage=previous.health-item.health;event.name=item.name;
        event.point={x:item.x,y:item.y,sw:item.sw,sh:item.sh,world:anchor};
      }
    }
    for(const [key,item] of snapshot) if(item.health!==undefined){
      const previous=healthHistory.get(key);
      if(!previous || item.health!==previous.health)healthHistory.set(key,{health:item.health,t:now});
    }
    for(const [key,item]of healthHistory)if(now-item.t>5000)healthHistory.delete(key);
    const lines=[];
    if(settings['Bullet Tracers'])for(const trace of traces){
      const a=project(camera,trace.start),b=project(camera,trace.end);
      if(a&&b&&a[2]>0&&b[2]>0)lines.push({a,b,start:trace.start,end:trace.end,alpha:1-(now-trace.t)/700});
    }
    let recoil=null;
    try{
      const local=getLocalPlayer();
      if(local&&!local.isNull()){
        const aim=local.add(0x128).readPointer();
        if(settings['Check Recoil']&&!aim.isNull()){
          // Display is sourced from the live recoil getters' observations.
          recoil=context.getRecoil();
        }
      }
    }catch(error){report('recoil-display-error',error);}
    return {events:events.map(event=>({...event})),traces:lines,recoil,scopeActive,sniperWeapon};
  }
  const healthHistory=new Map();
  let hookKey='';
  function removeEvent(label){
    if(context.removeHook)context.removeHook(label);
    const listener=eventListeners.get(label);if(listener&&listener.detach)listener.detach();eventListeners.delete(label);
  }
  function releaseScope(){
    try{if(scopeGroup&&originalScopeAlpha!==null&&live(scopeGroup))call('scopeAlphaSet',0xab5c670,'void',['pointer','float','pointer'])(scopeGroup,originalScopeAlpha,ptr(0));}
    finally{if(scopeGroup)release(scopeGroup);scopeGroup=null;originalScopeAlpha=null;scopeActive=false;sniperWeapon=false;}
  }
  function syncHooks(){
    const active=!context.canRun||context.canRun();
    const scope=active&&!!(settings['Custom Scope']||settings['Sniper Crosshair']||settings['Auto Scope']||(settings['Aim Activation']===2&&(settings['Aim assistance']||settings['Silent Aim']||settings.Trigger||settings['Force Shot'])));
    const hits=active&&['Hit Logs','Hit Marker','Damage Marker','Kill Particles','Kill Flash','Hit Sound','Kill Sound'].some(key=>settings[key]);
    const tracers=active&&!!settings['Bullet Tracers'],key=[scope,hits,tracers].join(',');if(key===hookKey)return;hookKey=key;
    if(scope)installScope();else{releaseScope();removeEvent('scope-view');}
    if(hits)installHits();else for(const name of ['hit-view','animator-a708984','animator-a7087f0','hit-event'])removeEvent(name);
    if(tracers)installTracers();else removeEvent('bullet-tracer');
  }
  syncHooks();
  function suspend() {
    for(const name of ['scope-view','hit-view','animator-a708984','animator-a7087f0','hit-event','bullet-tracer'])removeEvent(name);
    hookKey='';
    releaseScope();

    try{detachCommand();}catch(error){report('command-suspend-error',error);}
    try{clearGhosts();}catch(error){report('ghost-suspend-error',error);}
    for(const key of Array.from(playerModels.keys()))try{removePlayer(key);}catch(error){report('model-suspend-error',error);}
    events.length=0;traces.length=0;healthHistory.clear();avatarCache.clear();
    hitAnimators.clear();killAnimators.clear();hitCandidate=null;scopeActive=false;
  }
  return {addDetails,updateChams,removePlayer,screenFrame,report,suspend,syncHooks};
}
