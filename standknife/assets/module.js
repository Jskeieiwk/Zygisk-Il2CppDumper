import {createRawInput} from '../assets/raw-input.js';
import {createMatrixProjector} from '../assets/matrix-projection.js';
import {estimateVelocity,moveBone} from '../assets/esp-motion.js';
import {createLineBatch} from '../assets/line-batch.js';
import {applySafeMode} from '../assets/safe-mode.js';
import {createWorkBudget,playerWork,neededBones} from '../assets/performance.js';
import {locateGameModule} from '../assets/module-locator.js';
import {createCameraEffects} from '../assets/camera-effects.js';
import {createSceneEffects} from '../assets/scene-effects.js';
import {createWorldVisuals,worldFeatureNames} from '../assets/world-visuals.js';
import {drawWorldOverlay} from '../assets/world-overlay.js';
import {featureAvailable} from '../assets/capabilities.js';
import {createAntiAim,createRotationProbe} from '../assets/anti-aim.js';
import {createHookSet} from '../assets/hooks.js';
import {createMatchSession} from '../assets/session.js';
import {drawWatermark,watermarkLayout,createFrameMeter} from '../assets/watermark.js';
import { createAim } from '../assets/aim.js';
import { createVisualFeatures } from '../assets/visual-features.js';
import { createScreenRenderer } from '../assets/screen-overlay.js';
import { createFramePublisher } from '../assets/overlay-frame.js';
import { encodeFrame } from '../assets/frame-codec.js';
import { createSharedFrame, CAPACITY_WORDS, W_SELFTEST } from '../assets/shared-frame.js';
import { createNetPosition, NET_CANDIDATES } from '../assets/net-position.js';
'use strict';
const watermarkFontData=__WATERMARK_FONTS__;
const renderDexData=__RENDER_DEX__;
const gameFrameMeter=createFrameMeter();
const matchSession=createMatchSession();
const workBudget=createWorkBudget();
const costPhases=['camera','draw','capture','reproject','aim'];
const frameCost={since:0};
for(const phase of costPhases)frameCost[phase]={calls:0,ms:0,max:0};
function phaseCost(phase){const stat=frameCost[phase];return (stat.ms/Math.max(1,stat.calls)).toFixed(1)+'/'+stat.max;}
// camera: whole game-camera callback. draw: composing one overlay frame (Picture path) or one JS onDraw (fallback).
// capture: 10 Hz player/world sampling. reproject: per-frame reprojection between samples. Times are ms, "average/maximum".
// Per-window aim telemetry: what one step does (casts, obstacle classifications, skipped/probed players, time inside reaches()) and
// which aim settings are on, so the next log shows the cost and its cause together.
const aimFlags=['Aim assistance','Trigger','Autowall','Autowall (Aim)','Force Shot','Silent Aim','Multipoints','Hitchance','Hitbox All','Aim Visible Only','Auto Scope'];
function aimCostText(){
  try{
    const c=aimEngine&&aimEngine.takeCost?aimEngine.takeCost():null;if(!c)return '';
    const steps=Math.max(1,c.steps),per=value=>(value/steps).toFixed(1);
    return ' aimCasts='+per(c.casts)+' aimObstacles='+per(c.obstacles)+' aimSkipped='+per(c.skipped)+' aimProbes='+per(c.probes)+' aimReachMs='+per(c.reachMs)+
      ' aimFov='+settings['Aim FOV']+' aimOn='+aimFlags.filter(key=>settings[key]).join(',');
  }catch(error){return '';}
}
function recordFrameCost(kind,elapsed){
  const now=Date.now();if(!frameCost.since)frameCost.since=now;
  const stat=frameCost[kind];stat.calls++;stat.ms+=elapsed;stat.max=Math.max(stat.max,elapsed);
  if(kind==='camera'&&now-frameCost.since>=10000){
    console.log('CLOUD:perf gameFps='+gameFrameMeter.value(now)+' cameraMs='+phaseCost('camera')+
      ' canvasMs='+phaseCost('draw')+
      ' frames='+frameCost.camera.calls+'/'+frameCost.draw.calls+' players='+projected.size+
      ' captureMs='+phaseCost('capture')+' reprojectMs='+phaseCost('reproject')+' aimMs='+phaseCost('aim')+' aimSteps='+frameCost.aim.calls+aimCostText());
    frameCost.since=now;
    for(const phase of costPhases){const stat=frameCost[phase];stat.calls=stat.ms=stat.max=0;}
  }
}
let moduleBase=null,ready=false,espReady=false,noRecoil=false,lastPage="players",tries=0,panel=null;
const settings = {
  'Silent Aim':false,'Trigger':false,'Autowall':false,'Autowall (Aim)':false,'Force Shot':false,'Auto Calibration':false,
  'Trigger Delay':150,
  'Knife Bot':false,'Knife Range':1.5,'Knife FOV':30,'Auto Stop':false,'Overshoot':false,'Jitter':false,'Multipoints':false,'Jitter Strength':.1,
  'Back Camera':false,'Third Person':false,'Viewmodel':false,'Camera Distance':2,'Camera Height':.25,'Viewmodel X':.15,'Viewmodel Y':-.1,'Viewmodel Z':.2,
  'Safe Mode':false,'Raw Input':false,'Penetration':false,'Liquid Glass':false,'Watermark':true,'Hotkeys':false,'Notifications':false,'Accent Color':'#e9a8c5',
  'Fog':false,'Fog Distance':80,'Fog Color':'#78909c',
  'Anti-Aim':false,'AA Probe':false,'AA Yaw Mode':0,'AA Yaw Offset':180,'AA Jitter Range':30,'AA Spin Speed':180,'AA Pitch Mode':0,
  'Wallshot':false,'Hitbox All':false,'Hitbox Head':true,'Hitbox Body':false,'Hitbox Legs':false,'Hitbox Priority':0,'Multipoint Scale':50,'Hitchance':false,'Hitchance Percent':60,'Auto Scope':false,
  'Hit Sound Type':0,'Kill Sound Type':2,'Hit Sound Volume':150,
  'Grenade Glow':false,'Item ESP':false,'Grenades':false,'Off-screen Nades':false,'Molotov Radius':false,'Smoke Radius':false,'Player Nades':false,'Bomb Timer':false,
  'Aim assistance':false, 'Draw FOV':false, 'Sticky Aim':false, 'Humanize':false,
  'Aim Team Filter':true, 'Aim Visible Only':true, 'Aim FOV':10, 'Aim Smoothing':100,
  'Aim Range':150, 'Aim Bone':0, 'Aim Activation':1, 'Aim Priority':0,
  'Player ESP': true, 'Boxes': false, 'Health': false, 'Armor': false,
  'Nickname': false, 'Weapons': false, 'Distance': false, 'Skeleton': false,
  'Snaplines': false, 'OOF Arrows': false, 'Team Filter': false,
  'Show Avatar': false,
  'Money': false,
  'Ping': false,
  'Clan Tag': false,
  'Bomb Flag': false,
  'Hit Logs': false,
  'Chams': false,
  '3D Model': false,
  'Model Vis Only': false,
  'Dormant': false,
  'Reveal Occluded':false,
  'Ghost Chams': false,
  'Shader Chams': false,
  'Hit Marker': false,
  'Sniper Crosshair': false,
  'Custom Scope': false,
  'Damage Marker': false,
  'Target HUD': false,
  'Check Recoil': false,
  'Bullet Tracers': false,
  'Kill Particles': false,
  'Kill Flash': false,
  'Hit Sound': false,
  'Kill Sound': false,
  'Text Size': 13, 'Scope Radius': 70, 'Chams Opacity': 70,
  // 'ESP Sync Frames' replaces 'ESP Delay Frames' (v0.28 saved a default of 1 that overrode the later default of 0); the new name starts at 0.
  'Molotov Radius Scale': 200, 'Smoke Radius Scale': 55, 'ESP Sync Frames': 0,
  'Max Distance': 300, 'Line Width': 2, 'Enemy Color': '#efa8c5', 'Team Color': '#72baff'
};
const supported = new Set([...Object.keys(settings), 'No Recoil']);
let localTeam = 0, localSeen = 0, preferences = null, localPlayer = null, extraVisuals = null, worldVisuals = null, cameraEffects = null, sceneEffects = null, rawInput = null, antiAim = null, rotationProbe = null;
let aimEngine=null, menuOpen=false, menuWeb=null;
let screenFrame = { events:[], traces:[] };
const recoilValues = { vertical:0, horizontal:0, camera:0 };
const worldRecords = new Map();
const numericSettings = { 'Molotov Radius Scale':[25,400], 'Smoke Radius Scale':[25,400], 'ESP Sync Frames':[0,4], 'Max Distance':[10,500], 'Line Width':[1,4], 'Text Size':[9,20], 'Scope Radius':[30,200], 'Chams Opacity':[10,100], 'Aim FOV':[1,180],'Hitbox Priority':[0,2],'AA Yaw Mode':[0,2],'AA Pitch Mode':[0,3],'AA Yaw Offset':[-180,180],'AA Jitter Range':[0,90],'AA Spin Speed':[30,720],'Multipoint Scale':[10,100],'Hitchance Percent':[1,100],'Hit Sound Type':[0,3],'Kill Sound Type':[0,3],'Hit Sound Volume':[50,200], 'Aim Smoothing':[0,500], 'Aim Range':[5,300], 'Aim Bone':[0,2], 'Aim Activation':[0,2], 'Aim Priority':[0,2], 'Trigger Delay':[1,1000], 'Jitter Strength':[0,.5], 'Camera Distance':[.5,5], 'Camera Height':[-1,2], 'Viewmodel X':[-1,1], 'Viewmodel Y':[-1,1], 'Viewmodel Z':[-1,1], 'Fog Distance':[5,300], 'Knife Range':[.5,3], 'Knife FOV':[5,90] };
function espEnabled() {
  if(worldFeatureNames.some(name=>settings[name])||['Back Camera','Third Person','Viewmodel','Fog','Raw Input','Anti-Aim','AA Probe'].some(name=>settings[name]))return true;
  if((antiAim&&antiAim.ready())||(rotationProbe&&rotationProbe.running()))return true;
  const players = settings['Player ESP'] && ['Boxes','Health','Armor','Nickname','Weapons',
    'Distance','Skeleton','Snaplines','OOF Arrows','Show Avatar','Money','Ping','Clan Tag',
    'Bomb Flag','Chams','3D Model','Ghost Chams','Shader Chams','Dormant'].some(key=>settings[key]);
  return settings['Knife Bot']||settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope']||settings['Auto Calibration']||settings.Autowall||settings['Autowall (Aim)']||settings['Aim assistance'] || settings['Draw FOV'] || players || ['Hit Logs','Hit Marker','Sniper Crosshair','Custom Scope','Damage Marker',
    'Target HUD','Check Recoil','Bullet Tracers','Kill Particles','Kill Flash','Hit Sound','Kill Sound'].some(key=>settings[key]);
}
// The overlay frame is composed in the game-camera callback, but the game image of that frame reaches the screen a frame or two
// later, so the boxes can run ahead of the models. Java holds overlay frames back by this many milliseconds (shared transport only).
// The setting is in game frames, so it follows the frame rate: delay = frames * current frame time.
function espDelayMs(){
  const frames=settings['ESP Sync Frames'];
  if(!(frames>0))return 0;
  const fps=gameFrameMeter.value(Date.now());
  return Math.max(0,Math.min(200,Math.round(frames*(fps>5?1000/fps:1000/60))));
}
function overlayNeedsDraw(){
  const work=playerWork(settings);
  return work.display||work.hud||
    ['Item ESP','Grenades','Off-screen Nades','Molotov Radius','Smoke Radius','Bomb Timer','Penetration'].some(key=>settings[key])||
    ['Draw FOV','Hit Marker','Sniper Crosshair','Custom Scope','Check Recoil','Bullet Tracers',
      'Kill Particles','Kill Flash','Hit Sound','Kill Sound','Knife Bot','Silent Aim','Trigger','Force Shot'].some(key=>settings[key]);
}
function overlayNeedsMotion(){
  if(projected.size)return true;
  if((screenFrame.events||[]).length||(screenFrame.traces||[]).length)return true;
  const world=screenFrame.world;
  return !!(world&&((world.objects||[]).length||(world.rings||[]).length));
}
function readManagedString(address) {
  if (address.isNull()) return '';
  const length = address.add(0x10).readS32();
  return length > 0 && length <= 128 ? address.add(0x14).readUtf16String(length) : '';
}
let projected=new Map();
let publishOverlayFrame=null,clearOverlayFrame=null;
const trackedPlayers = new Map(), playerDetails = new Map();let overlay=null,overlayActivityId=null,overlayActivity=null,espFailures=0,espCalls=0;
console.log('CLOUD:script-loaded arch='+Process.arch+' pid='+Process.id);
console.log('CLOUD:runtime='+(typeof Script!=='undefined'&&Script.runtime?Script.runtime:'unknown'));
function hookGetter(hooks,rva,fieldOffset,safeOffset,label){
  let failures=0,calls=0;const installed=hooks.attach(rva,{
    onEnter(args){if(!recoilReady||!matchSession.ready(Date.now())||(!noRecoil&&!settings['Check Recoil']))return;try{
      if(++calls===1)console.log('CLOUD:recoil-getter '+label+' calls='+calls);
      const obj=args[0];if(obj.isNull())return;
      this.field=obj.add(fieldOffset);this.safe=obj.add(safeOffset);
      this.oldValue=this.field.readFloat();
      if(Number.isFinite(this.oldValue))recoilValues[label]=this.oldValue;
      if(!noRecoil)return;
      this.oldSafe=this.safe.readByteArray(12);
      this.field.writeFloat(0);this.safe.writeU8(0);this.changed=true;
    }catch(e){if(failures++<2)console.log('CLOUD:hook-error '+label+' '+e)}},
    onLeave(){if(!this.changed)return;try{this.field.writeFloat(this.oldValue);this.safe.writeByteArray(this.oldSafe)}catch(e){if(failures++<2)console.log('CLOUD:restore-error '+label+' '+e)}}
  },'recoil-'+label);
  if(installed)console.log('CLOUD:hook '+label+' rva='+rva.toString(16));
}
let runtimeHooks=null,recoilReady=false,recoilHookKey='';
function syncRecoilHooks(hooks){
  const key=String((noRecoil||settings['Check Recoil'])&&matchSession.ready(Date.now()));if(key===recoilHookKey)return;recoilHookKey=key;
  if(key==='true'){
    hookGetter(hooks,0x6402be0,0x14,0x64,'vertical');
    hookGetter(hooks,0x6403428,0x10,0x70,'horizontal');
    hookGetter(hooks,0x64037b8,0x48,0x94,'camera');
    recoilReady=['vertical','horizontal','camera'].every(axis=>hooks.states()['recoil-'+axis]===true);
  }else{for(const axis of ['vertical','horizontal','camera'])hooks.remove('recoil-'+axis);recoilReady=false;}
  if(ready)updateMenuState();
}
function runtimeState(){
  const hooks={...(runtimeHooks?runtimeHooks.states():{}),'world-visuals':!!worldVisuals,'camera-effects':!!cameraEffects,'scene-effects':!!sceneEffects,'raw-input':!!rawInput,'anti-aim-gated':!antiAim||antiAim.gated()};
  return {ready,settings:{...settings,'No Recoil':noRecoil},capabilities:Object.fromEntries(Array.from(supported,key=>[key,featureAvailable(key,ready,hooks)]))};
}
function updateMenuState(){
  Java.scheduleOnMainThread(()=>{if(menuWeb)try{
    menuWeb.evaluateJavascript(jstr('window.setRuntimeState('+JSON.stringify(runtimeState())+')'),null);
  }catch(error){console.log('CLOUD:menu-status-error '+error);}});
}
function install(){
  if(ready)return true;
  if(!moduleBase)return false;
  const hooks=createHookSet(moduleBase,Interceptor);
  try {
    installEsp(hooks);
    recoilHookKey='';syncRecoilHooks(hooks);
    runtimeHooks=hooks;espReady=true;ready=true;
    recoilReady=(noRecoil||settings['Check Recoil'])&&['vertical','horizontal','camera'].every(axis=>hooks.states()['recoil-'+axis]===true);
    console.log('CLOUD:hook-status '+JSON.stringify(hooks.states()));
    console.log('CLOUD:il2cpp-ready');updateMenuState();
    Java.scheduleOnMainThread(()=>{if(overlay)overlay.postInvalidateOnAnimation();});
    return true;
  } catch(error) {
    hooks.detach();espReady=false;ready=false;recoilReady=false;
    if(aimEngine){aimEngine.reset();aimEngine=null;}
    if(extraVisuals){extraVisuals.suspend();extraVisuals=null;}
    if(worldVisuals){worldVisuals.reset();worldVisuals=null;}
    if(cameraEffects){cameraEffects.dispose();cameraEffects=null;}
    if(rawInput){rawInput.reset();rawInput=null;}
    if(antiAim){antiAim.reset();antiAim=null;}
    if(rotationProbe){rotationProbe.reset();rotationProbe=null;}
    if(sceneEffects){sceneEffects.reset();sceneEffects=null;}
    trackedPlayers.clear();playerDetails.clear();worldRecords.clear();projected=new Map();
    localPlayer=null;localSeen=0;localTeam=0;screenFrame={events:[],traces:[]};
    runtimeHooks=null;updateMenuState();
    console.log('CLOUD:module-not-ready '+error+'; retry scheduled');
    return false;
  }
}
// RVAs and field offsets below are from the recovered StandKnife 3.3 dump.
const boneOffsets = [0x20, 0x28, 0x40, 0x88, 0x50, 0x58, 0x60,
  0x70, 0x78, 0x80, 0x90, 0x98, 0xa0, 0xb0, 0xb8, 0xc0];
const boneEdges = [[0,1],[1,2],[2,3],[1,4],[4,5],[5,6],[1,7],[7,8],
  [8,9],[3,10],[10,11],[11,12],[3,13],[13,14],[14,15]];
function installEsp(hooks=createHookSet(moduleBase,Interceptor)) {
  let chamsWasActive=false;
  const vec = ['float', 'float', 'float'];
  function native(rva, result, arguments_) {
    const address = moduleBase.add(rva), range = Process.findRangeByAddress(address);
    if (!range || !range.protection.includes('x')) throw Error('Non-executable RVA ' + rva.toString(16));
    return new NativeFunction(address, result, arguments_);
  }
  const transform = native(0xa77dbf4, 'pointer', ['pointer','pointer']);
  const position = native(0xa7a0030, vec, ['pointer','pointer']);
  const camera = native(0xa7298e8, 'pointer', ['pointer']);
  const worldToScreen = native(0xa7291ac, vec, ['pointer',vec,'pointer']);
  const screenWidth = native(0xa73b93c, 'int', ['pointer']);
  const screenHeight = native(0xa73ba94, 'int', ['pointer']);
  // ObjectOccludee.SetObstructedVisible(bool) (RVA 0x3F2A8E4 in the 3.3 dump); the game's own occlusion calls OnObstructed (0x3F2A2B0)
  // and OnUnobstructed (0x3F2A40C) on each player's PlayerOcclusionController (PlayerController+0xF8).
  let setObstructedVisible=null;try{setObstructedVisible=native(0x3f2a8e4,'void',['pointer','bool','pointer']);}catch(error){console.log('CLOUD:occlusion-unavailable '+error);}
  const getHealth = native(0x49eb03c, 'int', ['pointer','pointer']);
  const getArmor = native(0x49ee530, 'int', ['pointer','pointer']);
  const getMaxHealth = native(0x49ecea0, 'int', ['pointer','pointer']);
  const getMaxArmor = native(0x49f18ec, 'int', ['pointer','pointer']);
  let matrixProject=null,matrixCamera=null,matrixAvailable=true,matrixChecked=false;
  let viewStorage=null,projectionStorage=null,readView=null,readProjection=null;
  function snapshotProjection(cam,sw,sh){
    matrixProject=null;
    if(!matrixAvailable)return;
    try{
      if(!viewStorage){
        viewStorage=Memory.alloc(64);projectionStorage=Memory.alloc(64);
        readView=native(0xa727e34,'void',['pointer','pointer','pointer']);
        readProjection=native(0xa72800c,'void',['pointer','pointer','pointer']);
      }
      readView(cam,viewStorage,ptr(0));readProjection(cam,projectionStorage,ptr(0));
      const read=storage=>Array.from({length:16},(_,i)=>storage.add(i*4).readFloat());
      matrixProject=createMatrixProjector(read(viewStorage),read(projectionStorage),sw,sh);
      if(!matrixCamera||!cam.equals(matrixCamera))matrixChecked=false;
      matrixCamera=cam;
    }catch(error){matrixAvailable=false;console.log('CLOUD:matrix-fallback '+error);}
  }
  function project(cam, point) {
    if(matrixProject&&matrixCamera&&cam.equals(matrixCamera)){
      const value=matrixProject(point);
      if(matrixChecked)return value;
      const reference=worldToScreen(cam,point,ptr(0));
      if(value&&value[2]>0&&reference.every(Number.isFinite)){
        if(Math.hypot(value[0]-reference[0],value[1]-reference[1])<=1&&Math.abs(value[2]-reference[2])<.1){
          matrixChecked=true;console.log('CLOUD:matrix-projection-verified');return value;
        }
        matrixAvailable=false;matrixProject=null;console.log('CLOUD:matrix-fallback projection mismatch');
      }
      return reference.every(Number.isFinite)?reference:null;
    }
    const value = worldToScreen(cam, point, ptr(0));
    return value.every(Number.isFinite) ? value : null;
  }
  const inGame=native(0x3e03864,'bool',['pointer']);
  const activeScene=native(0xa7aefb8,'int',['pointer']);
  const frameCount=native(0xa79a61c,'int',['pointer']);
  // Unity input is queried only when an aim target needs touch activation.
  // Intercepting Activity.dispatchTouchEvent stalls unrelated game UI scrolls.
  const getTouchCount=native(0xa819d9c,'int',['pointer']);
  function gameplayPlayer(){
    if(!matchSession.ready(Date.now())||!localPlayer||Date.now()-localSeen>250)return null;
    try{
      const main=localPlayer.add(0x68).readPointer();
      if(main.isNull()||!main.add(0x48).readPointer().equals(localPlayer))return null;
      if(localPlayer.add(0x148).readPointer().isNull())return null;
      return localPlayer;
    }catch(error){return null;}
  }
  function resetGameplay(){
    workBudget.reset();
    localPlayer=null;localTeam=0;localSeen=0;cachedCamera=null;cameraChecked=-Infinity;trackedPlayers.clear();playerDetails.clear();worldRecords.clear();projected=new Map();dormantSeen.clear();
    screenFrame={events:[],traces:[]};
    if(aimEngine)aimEngine.reset();
    if(extraVisuals)extraVisuals.suspend();
    chamsWasActive=false;
    if(runtimeHooks){recoilHookKey='';syncRecoilHooks(runtimeHooks);}
    if(worldVisuals)worldVisuals.reset();
    if(cameraEffects)cameraEffects.reset();
    if(rawInput)rawInput.reset();
    if(antiAim)antiAim.reset();
    if(rotationProbe)rotationProbe.reset();
    if(sceneEffects)sceneEffects.reset();
    if(clearOverlayFrame)clearOverlayFrame();else if(overlay)overlay.postInvalidateOnAnimation();
    console.log('CLOUD:gameplay-reset generation='+matchSession.generation());
  }
  extraVisuals=createVisualFeatures({ native, base:moduleBase, settings, transform, position, project,
    readManagedString, trackedPlayers, attachHook:(rva,callbacks,label)=>hooks.attach(rva,callbacks,label), removeHook:label=>hooks.remove(label), canRun:()=>matchSession.ready(Date.now()), getLocalPlayer:gameplayPlayer, getRecoil:()=>({...recoilValues}) });
  try{worldVisuals=createWorldVisuals({native,settings,transform,position,project,readManagedString,canRun:()=>matchSession.ready(Date.now())});}
  catch(error){worldVisuals=null;console.log('CLOUD:world-install-error '+error);}
  // GrenadeEffectController.Play (RVA 0x4D556A8 in the 3.3 dump) registers molotov/smoke effects as they start, which replaces the
  // scene scan that froze the game for 45-300 ms every 1.5 s. If the hook cannot be installed the scan remains as the fallback.
  if(worldVisuals&&worldVisuals.noteEffect){
    const installed=hooks.attach(0x4d556a8,{onEnter(args){try{worldVisuals.noteEffect(args[0]);}catch(error){}}},'effect-play');
    worldVisuals.setEffectHook(installed);
    console.log('CLOUD:effect-hook='+(installed?'on':'unavailable, scene scan fallback'));
  }
  // The same for items, dropped grenades and the planted bomb: lifecycle methods from the 3.3 dump (script.json) register the objects as the
  // game creates them. A kind with no installed hook keeps the periodic scene scan (worldScanMs 40-52 ms every ~2 s in the v0.38 log).
  //   DroppedGrenadeController.Awake 0x3B0AEEC, PlantedBombController.Awake 0x519E18C,
  //   WeaponDropController.PreInitialize 0x3BEF384 and .Initialize 0x3BF28D0 (the class has no Awake/OnEnable; whether either runs for
  //   every drop, including map-placed ones, is not verified on the device: objects that exist when the feature is switched on are found by one seed scan).
  if(worldVisuals&&worldVisuals.noteObject){
    const registry=[['grenades','grenade-awake',0x3b0aeec],['bombs','bomb-awake',0x519e18c],['items','drop-preinit',0x3bef384],['items','drop-init',0x3bf28d0]];
    const installedKinds=new Map();
    for(const [kind,label,rva] of registry){
      const installed=hooks.attach(rva,{onEnter(args){try{worldVisuals.noteObject(kind,args[0]);}catch(error){}}},label);
      installedKinds.set(kind,installedKinds.get(kind)||installed);
    }
    for(const [kind,installed] of installedKinds)worldVisuals.setHook(kind,installed);
    console.log('CLOUD:world-registry-hooks '+[...installedKinds].map(([kind,installed])=>kind+'='+(installed?'on':'scan-fallback')).join(' '));
  }
  aimEngine=createAim({native,settings,paused:()=>menuOpen,base:moduleBase,getLocalPlayer:gameplayPlayer,fireActive:()=>!menuOpen&&!!gameplayPlayer(),getScope:()=>({active:screenFrame.scopeActive===true,sniper:screenFrame.sniperWeapon===true}),canRun:()=>!!gameplayPlayer(),generation:()=>matchSession.generation(), transform,position,records:worldRecords,tracked:trackedPlayers,getHealth,
    active:()=>!menuOpen&&!!gameplayPlayer()&&(settings['Aim Activation']===0 || (settings['Aim Activation']===1?getTouchCount(ptr(0))>0:screenFrame.scopeActive===true))});
  try{cameraEffects=createCameraEffects({native,settings,base:moduleBase,transform,position,getCamera:worldCamera,getLocalPlayer:gameplayPlayer,canRun:()=>!!gameplayPlayer()});console.log('CLOUD:camera-mode-ready');}
  catch(error){cameraEffects=null;console.log('CLOUD:camera-mode-install-error '+error);}
  try{
    const attachHook=(rva,callbacks,label)=>hooks.attach(rva,callbacks,label),removeHook=label=>hooks.remove(label);
    antiAim=createAntiAim({native,settings,getLocalPlayer:gameplayPlayer,canRun:()=>!!gameplayPlayer()&&matchSession.ready(Date.now()),generation:()=>matchSession.generation(),attachHook,removeHook,log:message=>console.log(message)});
    rotationProbe=createRotationProbe({base:moduleBase,attachHook,removeHook,getLocalPlayer:gameplayPlayer,canRun:()=>!!gameplayPlayer()&&matchSession.ready(Date.now()),log:message=>console.log(message)});
    console.log('CLOUD:anti-aim-ready sender='+(antiAim.gated()?'unknown (gated)':'set'));
  }catch(error){antiAim=null;rotationProbe=null;console.log('CLOUD:anti-aim-install-error '+error);}
  try{rawInput=createRawInput({native,settings,getLocalPlayer:gameplayPlayer,canRun:()=>!!gameplayPlayer()});}
  catch(error){rawInput=null;console.log('CLOUD:raw-input-install-error '+error);}
  try{sceneEffects=createSceneEffects({native,settings,canRun:()=>matchSession.ready(Date.now()),scene:()=>activeScene(ptr(0))});}
  catch(error){sceneEffects=null;console.log('CLOUD:scene-install-error '+error);}
  hooks.attach(0x49ec32c, {
    onEnter(args) { this.player=args[0]; },
    onLeave() {
      if (!matchSession.present(Date.now())||this.player.isNull()||(!espEnabled()&&!(aimEngine&&aimEngine.needsUpdate()))) return;
      try {
        const player=this.player, owner=player.add(0xa8).readPointer();
        const local=!owner.isNull() && owner.add(0x28).readU8()===1;
        const team=player.add(0x133).readU8();
        if(local) { localPlayer=player; localTeam=team; localSeen=Date.now(); }
        trackedPlayers.set(player.toString(), { player, local, team, t:Date.now() });
        if(local && matchSession.ready(Date.now()) && workBudget.due('aim-step',Date.now(),1000/60) && (settings['Knife Bot']||settings['Aim assistance']||settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope']||settings['Auto Calibration']||settings.Autowall||settings['Autowall (Aim)']||aimEngine.needsUpdate())){const began=Date.now();try{aimEngine.step(player,worldCamera(),team);}finally{recordFrameCost('aim',Date.now()-began);}}
      } catch(error) { if(espFailures++<8)console.log('CLOUD:player-track-error '+error); }
    }
  },'player-update',true);
  // Enemies behind walls the game's occlusion treats as solid stop being updated, so the ESP loses them. Players that are
  // obstructed are marked visible again; every change is logged (at most 60 lines) so the effect can be checked on the device.
  let occlusionLogs=0,revealing=false;
  const obstructedPlayers=new Set(),netPosition=createNetPosition({log:message=>console.log(message)});
  function occludedPlayer(occluder){
    for(const [key,tracked] of trackedPlayers){
      if(tracked.local)continue;
      try{if(tracked.player.add(0xf8).readPointer().equals(occluder))return {key,tracked};}catch(error){}
    }
    return null;
  }
  if(setObstructedVisible){
    const noteOcclusion=(name,occluder)=>{
      if(revealing||!espEnabled()||occluder.isNull())return;
      const found=occludedPlayer(occluder);if(!found)return;
      const wasObstructed=obstructedPlayers.has(found.key);
      if(name==='obstructed')obstructedPlayers.add(found.key);else obstructedPlayers.delete(found.key);
      const reveal=name==='obstructed'&&settings['Reveal Occluded']===true;
      if((wasObstructed!==(name==='obstructed')||reveal)&&occlusionLogs++<60)console.log('CLOUD:occlusion '+name+' key='+found.key+' team='+found.tracked.team+' silentMs='+(Date.now()-found.tracked.t)+' reveal='+reveal);
      if(!reveal)return;
      revealing=true;
      try{setObstructedVisible(occluder,1,ptr(0));}catch(error){if(occlusionLogs++<60)console.log('CLOUD:occlusion-reveal-error '+error);}
      finally{revealing=false;}
    };
    hooks.attach(0x3f2a2b0,{onEnter(args){this.occluder=args[0];},onLeave(){try{noteOcclusion('obstructed',this.occluder);}catch(error){}}},'occlusion-obstructed');
    hooks.attach(0x3f2a40c,{onEnter(args){try{noteOcclusion('unobstructed',args[0]);}catch(error){}}},'occlusion-unobstructed');
  }
  // MovementController (PlayerController+0x108): network snapshot at +0xB0, translation data at +0x98 (see assets/net-position.js).
  function netCandidates(player){
    const movement=player.add(0x108).readPointer();if(movement.isNull())return null;
    const snapshot=movement.add(0xb0).readPointer(),translation=movement.add(0x98).readPointer();
    return NET_CANDIDATES.map(([source,offset])=>{
      const base=source==='snapshot'?snapshot:translation;if(base.isNull())return null;
      try{const at=base.add(offset);return [at.readFloat(),at.add(4).readFloat(),at.add(8).readFloat()];}catch(error){return null;}
    });
  }
  let cachedCamera=null,cameraChecked=-Infinity;
  function worldCamera() {
    if(localPlayer && Date.now()-localSeen<1000) {
      try {
        const main=localPlayer.add(0x68).readPointer(); // PlayerMainCamera
        if(!main.isNull()) {
          const selected=main.add(0x20).readPointer();
          if(!selected.isNull())return selected;
        }
      } catch(error) { extraVisuals.report('world-camera-error',error); }
    }
    const now=Date.now();
    if(!cachedCamera||now-cameraChecked>=250){cachedCamera=camera(ptr(0));cameraChecked=now;}
    return cachedCamera;
  }
  function details(player, owner, key, now) {
    const flags=['Health','Armor','Nickname','Weapons','Money','Ping','Clan Tag','Bomb Flag',
      'Show Avatar','Player Nades','Target HUD','Damage Marker','Hit Logs','Aim assistance','Trigger','Silent Aim','Force Shot','Auto Scope','Knife Bot'].map(key=>settings[key]).join(',');
    const cached=playerDetails.get(key);
    if(cached && now-cached.t<150 && cached.flags===flags)return cached;
    const item={t:now,flags,name:'',weapon:''};
    if(settings.Health || settings['Knife Bot'] || settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope']||settings['Aim assistance'] || settings['Target HUD'] || settings['Damage Marker'] || settings['Hit Logs']) {
      item.health=getHealth(player,ptr(0));item.maxHealth=getMaxHealth(player,ptr(0));
    }
    if(settings.Armor) {item.armor=getArmor(player,ptr(0));item.maxArmor=getMaxArmor(player,ptr(0));}
    if((settings.Nickname || settings['Target HUD'] || settings['Hit Logs']) && !owner.isNull())item.name=readManagedString(owner.add(0x20).readPointer());
    if(settings.Weapons || settings['Target HUD']) {
      const weaponry=player.add(0xf0).readPointer();
      if(!weaponry.isNull()) {
        const weapon=weaponry.add(0xa8).readPointer();
        if(!weapon.isNull()) {
          const parameters=weapon.add(0xb8).readPointer();
          if(!parameters.isNull())item.weapon=readManagedString(parameters.add(0x20).readPointer());
        }
      }
    }
    extraVisuals.addDetails(item,player,owner);
    if(worldVisuals&&settings['Player Nades'])item.grenades=worldVisuals.inventory(player);
    playerDetails.set(key,item);return item;
  }
  // Player positions are sampled at 10/30 Hz. Their saved world coordinates
  // are projected again for each rendered camera frame, without reading player objects.
  function reprojectPlayers(cam,now,sw,sh,cameraPos,exactBones=false){
    const next=new Map(),needs=playerWork(settings);
    if(!needs.display&&!needs.hud){projected=next;return next;}
    for(const [key,state] of worldRecords){
      const tracked=trackedPlayers.get(key);
      if(!tracked)continue;
      const dormant=now-tracked.t>250;
      if(dormant&&(!settings.Dormant||now-state.t>2000))continue;
      const friendly=localTeam>0&&state.team===localTeam;
      if(friendly&&(!needs.display||settings['Team Filter'])&&!needs.hud)continue;
      try{
        let origin=state.pos;
        if(!dormant&&!exactBones){
          const tr=transform(tracked.player,ptr(0));
          if(tr.isNull())continue;
          const current=position(tr,ptr(0));
          if(!current.every(Number.isFinite))continue;
          origin=current;
        }
        const distance=Math.hypot(origin[0]-cameraPos[0],origin[1]-cameraPos[1],origin[2]-cameraPos[2]);
        if(!Number.isFinite(distance)||distance<1||distance>settings['Max Distance'])continue;
        const feet=project(cam,origin);
        const bonePositions=state.bonePositions||[],boneAnchors=state.boneAnchors||[];
        function projectedBone(index){
          const bone=bonePositions[index];
          return bone?project(cam,moveBone(bone,boneAnchors[index],origin)):null;
        }
        const bones=new Array(16).fill(null);
        const boneHead=projectedBone(0);
        const anchorHead=boneHead||project(cam,[origin[0],origin[1]+1.7,origin[2]]);
        if(!anchorHead||!feet)continue;
        if(settings.Skeleton){
          bones[0]=boneHead;
          for(let index=1;index<16;index++)if(bonePositions[index])bones[index]=projectedBone(index);
        }else if(boneHead)bones[0]=boneHead;
        let head=bones[0]||anchorHead;
        let boxWidth=null,height=Math.abs(head[1]-feet[1]);
        if(settings.Skeleton){
          // Screen bounds of the bones in front of the camera, in one pass (no filter/map/spread per player per frame).
          let visible=0,minX=Infinity,maxX=-Infinity,minY=Infinity,maxY=-Infinity;
          for(let index=0;index<16;index++){
            const point=bones[index];
            if(!point||!(point[2]>0))continue;
            visible++;
            if(point[0]<minX)minX=point[0];
            if(point[0]>maxX)maxX=point[0];
            if(point[1]<minY)minY=point[1];
            if(point[1]>maxY)maxY=point[1];
          }
          if(visible>=8&&bones[0]&&bones[0][2]>0){
            const padding=Math.max(2,(maxY-minY)*.06);
            head=[(minX+maxX)/2,maxY+padding,bones[0][2]];
            boxWidth=Math.max(maxX-minX+padding*2,(maxY-minY)*.35);
            height=maxY-minY+padding*1.5;
          }
        }
        next.set(key,{...state,sw,sh,t:now,dormant:dormant||!!state.stale,staleMs:state.stale?now-state.frozenAt:0,distance,bones,anchorHead,anchorFeet:feet,
          x:head[0],y:head[1],z:head[2],h:height,bw:boxWidth});
      }catch(error){if(espFailures++<8)console.log('CLOUD:esp-projection-error '+error);}
    }
    projected=next;return next;
  }
  // Diagnostics for ESP that "stands still": an enemy is tracked only while the game calls its PlayerController.LateUpdate. When that
  // stops for 250 ms the enemy counts as dormant and the ESP shows its last position (or nothing). One line per change, at most 80.
  const dormantSeen=new Map();let dormantLogs=0,slowCaptures=0;
  function noteDormancy(key,dormant,silentMs){
    if((dormantSeen.get(key)||false)===dormant)return;
    dormantSeen.set(key,dormant);if(dormantSeen.size>64)dormantSeen.delete(dormantSeen.keys().next().value);
    if(dormantLogs++>=80)return;
    const shown=projected.get(key);
    console.log('CLOUD:player-'+(dormant?'dormant':'live')+' key='+key+' silentMs='+silentMs+' dormantSetting='+!!settings.Dormant+
      (shown?' lastScreen='+Math.round(shown.x)+','+Math.round(shown.y)+' depth='+Number(shown.z).toFixed(1)+' dist='+Number(shown.distance).toFixed(1):' notProjected')+
      ' tracked='+trackedPlayers.size);
  }
  function reprojectFrame(cam,now){
    const sw=screenFrame.sw,sh=screenFrame.sh;
    if(!sw||!sh)return;
    snapshotProjection(cam,sw,sh);
    let cameraPos=[0,0,0];
    if(playerWork(settings).display||playerWork(settings).hud){
      const cameraTransform=transform(cam,ptr(0));if(cameraTransform.isNull())return;
      cameraPos=position(cameraTransform,ptr(0));
      if(!cameraPos.every(Number.isFinite))return;
    }
    const next=reprojectPlayers(cam,now,sw,sh,cameraPos);
    let world=screenFrame.world;
    if(world){
      world={...world,t:now,sw,sh,
        objects:(world.objects||[]).map(item=>item.pos?{...item,point:project(cam,item.pos)}:item),
        rings:(world.rings||[]).map(ring=>ring.worldPoints?{...ring,points:ring.worldPoints.map(point=>project(cam,point))}:ring)};
    }
    const events=(screenFrame.events||[]).map(event=>{
      if(!event.point||!event.point.world)return event;
      const point=project(cam,event.point.world);
      return point?{...event,point:{...event.point,x:point[0],y:point[1],sw,sh}}:event;
    });
    const traces=(screenFrame.traces||[]).map(trace=>trace.start&&trace.end?
      {...trace,a:project(cam,trace.start),b:project(cam,trace.end)}:trace).filter(trace=>trace.a&&trace.b);
    screenFrame={...screenFrame,world,events,traces,sw,sh,t:now};
  }
  function captureFrame(cam,visual=true) {
    if(!espEnabled()) {projected=new Map();if(worldVisuals)worldVisuals.reset();screenFrame={events:[],traces:[]};return;}
    const now=Date.now(),needs=playerWork(settings),bonesNeeded=neededBones(settings,visual,!menuOpen);
    if(menuOpen)needs.aim=false;
    if(!needs.aim&&!needs.display&&!needs.hud){worldRecords.clear();}
    if(cam.isNull()) {projected=new Map();return;}
    const cameraTransform=transform(cam,ptr(0));
    if(cameraTransform.isNull()) {projected=new Map();return;}
    const cameraPos=position(cameraTransform,ptr(0));
    const began=Date.now();
    const sw=visual?screenWidth(ptr(0)):0,sh=visual?screenHeight(ptr(0)):0;
    if(visual&&(sw<=0 || sh<=0 || sw>10000 || sh>10000)) {projected=new Map();return;}
    if(visual)snapshotProjection(cam,sw,sh);
    if(needs.aim||needs.display||needs.hud)for(const [key,tracked]of trackedPlayers) {
      if(tracked.local)continue;
      const friendly=localTeam>0&&tracked.team===localTeam;
      if(friendly&&(!needs.display||settings['Team Filter'])&&(!needs.aim||settings['Aim Team Filter'])&&!needs.hud)continue;
      const dormant=now-tracked.t>250;
      noteDormancy(key,dormant,now-tracked.t);
      let state=worldRecords.get(key);
      if(dormant && (!settings.Dormant || !state || now-state.t>2000)) {
        trackedPlayers.delete(key);playerDetails.delete(key);worldRecords.delete(key);continue;
      }
      try {
        if(!dormant) {
          const player=tracked.player, owner=player.add(0xa8).readPointer();
          const tr=transform(player,ptr(0));if(tr.isNull())continue;
          let pos=position(tr,ptr(0)),shift=null,freeze={stale:false};
          if(espEnabled()){
            const obstructed=obstructedPlayers.has(key);
            try{
              const values=netCandidates(player);
              netPosition.observe(pos,values,obstructed);
              const net=netPosition.resolve(key,pos,values,obstructed,now);
              if(net){shift=[net[0]-pos[0],net[1]-pos[1],net[2]-pos[2]];pos=net;}
              freeze=netPosition.track(key,pos,obstructed,now);
              if(freeze.stale&&freeze.predicted){
                const predicted=freeze.predicted,extra=[predicted[0]-pos[0],predicted[1]-pos[1],predicted[2]-pos[2]];
                shift=shift?[shift[0]+extra[0],shift[1]+extra[1],shift[2]+extra[2]]:extra;pos=predicted;
              }
            }catch(error){if(espFailures++<8)console.log('CLOUD:net-pos-error '+error);}
          }
          const bonePositions=visual?Array(16).fill(null):(state&&state.bonePositions?state.bonePositions.slice():Array(16).fill(null));
          const boneAnchors=visual?Array(16).fill(null):(state&&state.boneAnchors?state.boneAnchors.slice():Array(16).fill(null));
          const distance=Math.hypot(...pos.map((value,index)=>value-cameraPos[index]));
          if(!Number.isFinite(distance)||distance>Math.max(needs.aim?settings['Aim Range']:0,needs.display?settings['Max Distance']:0,needs.hud?settings['Max Distance']:0))continue;
          const view=player.add(0x158).readPointer();
          if(!view.isNull()) {
            const map=view.add(0x48).readPointer();
            if(!map.isNull())for(const index of bonesNeeded) {
              const bone=map.add(boneOffsets[index]).readPointer();
              const bonePosition=bone.isNull()?null:position(bone,ptr(0));
              bonePositions[index]=bonePosition&&shift?[bonePosition[0]+shift[0],bonePosition[1]+shift[1],bonePosition[2]+shift[2]]:bonePosition;
              boneAnchors[index]=bone.isNull()?null:pos;
            }
          }
          state={...details(player,owner,key,now),t:now,pos,bonePositions,boneAnchors,
            velocity:freeze.stale?null:estimateVelocity(state&&state.pos,pos,state?now-state.t:0),team:tracked.team,
            stale:freeze.stale,frozenAt:freeze.stale?freeze.frozenAt:0,predicted:!!(freeze.stale&&freeze.predicted&&freeze.predictedMs<1000)};
          worldRecords.set(key,state);
        }
      }catch(error){if(espFailures++<8)console.log('CLOUD:esp-error '+error);}
    }
    if(!visual)return;
    const afterPlayers=Date.now();
    const next=reprojectPlayers(cam,now,sw,sh,cameraPos,true);
    let effects={events:[],traces:[]},aim={},world=null;
    try{effects=extraVisuals.screenFrame(cam,next);}catch(error){extraVisuals.report('hud-snapshot-error',error);}
    const afterEffects=Date.now();
    try{aim=aimEngine.status(cam);}catch(error){extraVisuals.report('aim-status-error',error);}
    const afterAim=Date.now();
    if(worldVisuals)try{world={...worldVisuals.snapshot(cam),sw,sh};}catch(error){extraVisuals.report('world-snapshot-error',error);}
    const finished=Date.now();
    // The game thread waits for this callback. A slow sampling pass freezes the whole game, so say where the time went.
    if(finished-began>=40&&slowCaptures++<400)console.log('CLOUD:capture-slow totalMs='+(finished-began)+' players='+(afterPlayers-began)+
      ' effects='+(afterEffects-afterPlayers)+' aim='+(afterAim-afterEffects)+' world='+(finished-afterAim)+
      ' worldScanMs='+((world&&world.scanMs)||0)+' tracked='+trackedPlayers.size+' bones='+bonesNeeded.length);
    screenFrame={...effects,aim,world,sw,sh,t:now};
    projected=next;
    if(++espCalls===1 || espCalls%1800===0)console.log('CLOUD:esp-world-camera-frame='+espCalls+' players='+next.size+' camera='+cam);
  }
  // These callbacks supply the camera actually being rendered, including its scoped FOV.
  hooks.attach(0xa72b920,{
    onEnter(args){this.camera=args[0];},
    onLeave(){const start=Date.now();let measured=false;try{
      const now=Date.now(),selected=worldCamera();
      if(selected.isNull()||!this.camera.equals(selected))return;
      gameFrameMeter.frame(now);
      if(workBudget.due('session',now,50)){
        const state=matchSession.update(!!inGame(ptr(0)),activeScene(ptr(0)),now,frameCount(ptr(0)));
        if(state.reset)resetGameplay();
      }
      if(!matchSession.ready(now))return;
      measured=true;
      const visual=workBudget.due('visual',now,100);
      const redraw=true; // Follow every selected game-camera frame.
      const draw=overlayNeedsDraw();
      const aiming=!menuOpen&&playerWork(settings).aim;
      if(visual||(aiming&&workBudget.due('aim-data',now,1000/30))){const began=Date.now();captureFrame(selected,visual);recordFrameCost('capture',Date.now()-began);}
      if(redraw&&!visual&&draw){const began=Date.now();reprojectFrame(selected,now);recordFrameCost('reproject',Date.now()-began);}
      if(visual){
        if(extraVisuals.syncHooks)extraVisuals.syncHooks();
        if(runtimeHooks)syncRecoilHooks(runtimeHooks);
        if(rawInput)try{rawInput.update();}catch(error){extraVisuals.report('raw-input-error',error);}
        if(antiAim)try{antiAim.sync();}catch(error){extraVisuals.report('anti-aim-error',error);}
        if(rotationProbe)try{rotationProbe.sync(!!settings['AA Probe']);}catch(error){extraVisuals.report('aa-probe-error',error);}
        if(sceneEffects)try{sceneEffects.update();}catch(error){extraVisuals.report('scene-effect-error',error);}
        const chamsActive=(settings['Player ESP']&&(settings.Chams||settings['3D Model']||
          settings['Shader Chams']||settings['Ghost Chams']))||settings['Grenade Glow'];
        if(chamsActive){
          extraVisuals.updateChams(selected,worldVisuals?new Map([...trackedPlayers,...worldVisuals.glowPlayers()]):trackedPlayers,()=>localTeam);
          chamsWasActive=true;
        }else if(chamsWasActive){
          extraVisuals.updateChams(selected,new Map(),()=>localTeam);
          chamsWasActive=false;
        }
      }
      if(draw&&overlay&&(visual||overlayNeedsMotion())){
        if(publishOverlayFrame)publishOverlayFrame();else overlay.postInvalidate();
      }
    }catch(error){extraVisuals.report('camera-effects-error',error);}
    finally{if(measured)recordFrameCost('camera',Date.now()-start);}}
  },'camera-pre-render',true);
  for(const rva of [0x49ebb54,0x49f48e0])hooks.attach(rva,{onEnter(args){
    const key=args[0].toString();
    if(localPlayer && localPlayer.equals(args[0])){
      if(aimEngine)aimEngine.reset();
      localPlayer=null;localTeam=0;localSeen=0;
    }
    trackedPlayers.delete(key);playerDetails.delete(key);worldRecords.delete(key);projected.delete(key);obstructedPlayers.delete(key);netPosition.forget(key);
    try{extraVisuals.removePlayer(key);}catch(error){extraVisuals.report('model-release-error',error);}
  }},'player-release-'+rva.toString(16),true);
  console.log('CLOUD:esp-hook-ready');console.log('CLOUD:esp-details-cap=10 projection=game-frame origins=live');
}
setInterval(() => {
  const now = Date.now();
  for (const [key, item] of projected) if (now-item.t > 500) projected.delete(key);
  for (const [key,item] of trackedPlayers) if (now-item.t>(settings.Dormant?2000:500)) {
    trackedPlayers.delete(key);playerDetails.delete(key);worldRecords.delete(key);projected.delete(key);
  }
  if(screenFrame.t&&now-screenFrame.t>350){screenFrame={events:[],traces:[]};projected=new Map();if(overlay)overlay.postInvalidateOnAnimation();}
  if (now-localSeen > 1000) localTeam = 0;
}, 500);
let scanning=false;
async function scanAndInstall(){
  if(scanning||ready)return;
  if(tries++>=24){clearInterval(timer);console.log('CLOUD:module-unavailable');return;}
  scanning=true;
  try{
    if(!moduleBase)moduleBase=await locateGameModule({Process,Memory,log:message=>console.log(message)});
    if(moduleBase&&install()){clearInterval(timer);console.log('CLOUD:scan-ended');}
  }catch(error){console.log('CLOUD:install-error '+error);}
  finally{scanning=false;}
}
const timer=setInterval(scanAndInstall,10000);
function jstr(s){return Java.use('java.lang.String').$new(String(s))}
Java.perform(()=>{
  const Activity=Java.use('android.app.Activity'),Dialog=Java.use('android.app.Dialog'),WebView=Java.use('android.webkit.WebView');
  const FrameLayout=Java.use('android.widget.FrameLayout'),LayoutParams=Java.use('android.widget.FrameLayout$LayoutParams'),View=Java.use('android.view.View'),ViewGroup=Java.use('android.view.ViewGroup'),Shape=Java.use('android.graphics.drawable.GradientDrawable');
  const Chrome=Java.registerClass({name:'dev.cloud.standknife.MenuChrome',superClass:Java.use('android.webkit.WebChromeClient'),methods:{onConsoleMessage:[{returnType:'boolean',argumentTypes:['android.webkit.ConsoleMessage'],implementation:function(message){
    const value=String(message.message());if(!value.startsWith('MENU:'))return false;
    try {
      const msg = JSON.parse(value.slice(5));
      if (msg.key === '__page' && /^(aim|behavior|players|visuals|scene|weapons|misc)$/.test(msg.value)) {
        lastPage = msg.value;
      } else if (supported.has(msg.key)) {
        if (msg.key === 'No Recoil') noRecoil = msg.value === true;
        else if (msg.key.endsWith('Color') && /^#[0-9a-f]{6}$/i.test(msg.value)) settings[msg.key] = msg.value;
        else if (numericSettings[msg.key]) {
          const [minimum,maximum]=numericSettings[msg.key];
          const number=Number(msg.value);
          settings[msg.key]=Number.isFinite(number)?Math.max(minimum,Math.min(maximum,number)):minimum;
        }
        else if (typeof settings[msg.key] === 'boolean') settings[msg.key] = msg.value === true;
        console.log('CLOUD:setting '+msg.key+'='+JSON.stringify(msg.value)+' ready='+espReady);
      }
      if(applySafeMode(settings)||msg.key==='Safe Mode'){updateMenuState();applyMenuAppearance();}
      if(msg.key==='Watermark'&&!settings.Watermark&&!settings.Hotkeys){settings.Hotkeys=true;updateMenuState();}
      if(msg.key==='Liquid Glass')applyMenuAppearance();
      if(watermarkView)watermarkView.setVisibility(settings.Watermark?0:8);
      if(settings.Notifications&&typeof msg.value==='boolean')Java.scheduleOnMainThread(()=>{
        if(overlayActivity)Java.use('android.widget.Toast').makeText.overload('android.content.Context','java.lang.CharSequence','int')
          .call(Java.use('android.widget.Toast'),overlayActivity,jstr(msg.key+': '+(msg.value?'вкл':'выкл')),0).show();
      });
      if (overlay) overlay.postInvalidateOnAnimation();
      if (preferences) preferences.edit().putString(jstr('settings'), jstr(JSON.stringify({ ...settings, 'No Recoil':noRecoil, __page:lastPage }))).apply();
    } catch(error) { console.log('CLOUD:menu-error '+error); }
    return true;
  }}]}});
  const Paint = Java.use('android.graphics.Paint');
  const Style = Java.use('android.graphics.Paint$Style');
  const Color = Java.use('android.graphics.Color');
  const paint = Paint.$new(3),textPaint=Paint.$new(3);
  let compiledCanvas=null,frameCommands=null,hitSound=null;
  // Picture path: renderEsp hands its batched primitives back instead of drawing them, so endFrame can draw them in the same Java call.
  let deferCommands=false,deferredCommands=null;
  function loadCompiledCanvas(activity){
    if(compiledCanvas)return;
    try{
      const File=Java.use('java.io.File'),Stream=Java.use('java.io.FileOutputStream'),Base64=Java.use('android.util.Base64');
      const file=File.$new(activity.getCacheDir(),jstr('cloud-canvas-v37.dex'));
      if(file.exists()&&!file.delete())throw Error('Cannot replace renderer dex');
      const out=Stream.$new(file);
      try{
        if(!file.setReadOnly())throw Error('Cannot mark renderer dex read-only');
        out.write.overload('[B').call(out,Base64.decode.overload('java.lang.String','int').call(Base64,jstr(renderDexData),0));
      }finally{out.close();}
      Java.openClassFile(String(file.getAbsolutePath())).load();
      compiledCanvas=Java.use('dev.cloud.standknife.CanvasBatch');
      try{hitSound={sounds:Java.use('dev.cloud.standknife.HitSound'),dir:String(activity.getCacheDir().getAbsolutePath())};}
      catch(error){hitSound=null;console.log('CLOUD:hit-sound-unavailable '+error);}
      console.log('CLOUD:compiled-canvas-ready');
    }catch(error){console.log('CLOUD:compiled-canvas-unavailable '+error);}
  }
  textPaint.setStyle(Style.FILL.value);
  textPaint.setShadowLayer(1.5,1,1,-16777216);
  const colorCache=new Map(),textCache=new Map(),textWidths=new Map();
  let textSize=NaN,textColor=null;
  function setTextSize(size){if(size!==textSize){textPaint.setTextSize(size);textSize=size;}}
  // Label widths are the sum of per-character widths. Each (size, character) pair is measured through Java once;
  // text that changes every frame (distances, health) then costs no bridge calls. Kerning is ignored, which only
  // affects label clamping and overlap avoidance.
  const charWidths=new Map();
  function measureChar(character,size){
    let table=charWidths.get(size);
    if(!table){table=new Map();charWidths.set(size,table);if(charWidths.size>8)charWidths.delete(charWidths.keys().next().value);}
    let width=table.get(character);
    if(width===undefined){
      setTextSize(size);
      width=Number(textPaint.measureText.overload('java.lang.String').call(textPaint,drawString(character)));
      table.set(character,width);
    }
    return width;
  }
  function measureText(value,size){
    const key=size+':'+value,cached=textWidths.get(key);
    if(cached!==undefined)return cached;
    const string=String(value);let width=0;
    for(let index=0;index<string.length;index++)width+=measureChar(string[index],size);
    textWidths.set(key,width);
    if(textWidths.size>256)textWidths.delete(textWidths.keys().next().value);
    return width;
  }
  function color(value) {
    if(colorCache.has(value))return colorCache.get(value);
    const parsed=Color.parseColor(jstr(value));
    colorCache.set(value,parsed);
    if(colorCache.size>32)colorCache.delete(colorCache.keys().next().value);
    return parsed;
  }
  function drawString(value){
    const key=String(value),cached=textCache.get(key);
    if(cached){textCache.delete(key);textCache.set(key,cached);return cached;}
    const result=Java.retain(jstr(key));textCache.set(key,result);
    if(textCache.size>128){const oldest=textCache.keys().next().value;textCache.get(oldest).$dispose();textCache.delete(oldest);}
    return result;
  }
  function line(canvas, x1, y1, x2, y2, tint, width) {
    if(frameCommands){frameCommands.push([1,[x1,y1,x2,y2],width,tint|0]);return;}
    paint.setColor(tint); paint.setStrokeWidth(width);
    canvas.drawLine(x1,y1,x2,y2,paint);
  }
  // Rectangles, circles and avatars also join the frame batch, so a frame needs no direct Canvas calls through the bridge.
  function batchFill(left,top,right,bottom,tint){
    if(!frameCommands)return false;
    frameCommands.push([3,left,top,right,bottom,tint|0]);return true;
  }
  function batchCircle(x,y,radius,tint,width){
    if(!frameCommands)return false;
    frameCommands.push([4,x,y,radius,width,tint|0]);return true;
  }
  // Avatars are decoded once in Java (CanvasBatch.setAvatar) and then drawn by id.
  const avatarIds=new Map();let nextAvatarId=1,avatarFailures=0;
  function batchAvatar(avatar,left,top,side){
    if(!frameCommands||!overlay||typeof overlay.setAvatar!=='function')return false;
    let entry=avatarIds.get(avatar.id);
    if(!entry||entry.source!==avatar){
      entry={id:0,source:avatar};
      try{
        const crop=avatar.crop,signed=Array.from(avatar.bytes,byte=>byte>127?byte-256:byte);
        overlay.setAvatar(nextAvatarId,Java.array('byte',signed),crop?Math.max(0,crop.x):0,crop?Math.max(0,crop.y):0,crop?crop.width:0,crop?crop.height:0);
        entry.id=nextAvatarId++;
      }catch(error){if(avatarFailures++<3)console.log('CLOUD:avatar-register-error '+error);}
      avatarIds.set(avatar.id,entry);
      if(avatarIds.size>64)avatarIds.delete(avatarIds.keys().next().value);
    }
    if(entry.id)frameCommands.push([5,entry.id,left,top,side]);
    return true;
  }
  function text(canvas, value, x, y, size, tint) {
    if(frameCommands){frameCommands.push([2,String(value),x,y,size,tint|0]);return;}
    setTextSize(size);
    if(tint!==textColor){textPaint.setColor(tint);textColor=tint;}
    canvas.drawText.overload('java.lang.String','float','float','android.graphics.Paint')
      .call(canvas,drawString(value),x,y,textPaint);
  }
  const screenRenderer=createScreenRenderer({Java,jstr,Paint,Style,paint,text,line,color,settings,batchFill,batchCircle,batchAvatar,getLocalTeam:()=>localTeam,getHitSound:()=>hitSound});
  let gameSurface=null;
  const surfacePosition=Java.array('int',[0,0]),overlayPosition=Java.array('int',[0,0]);
  const surfaceGeometry={t:0,canvasWidth:0,canvasHeight:0,width:0,height:0,x:0,y:0,aligned:false};
  const SurfaceView=Java.use('android.view.SurfaceView');
  function findGameSurface(view) {
    let selected=null,area=0;
    function visit(candidate) {
      if(SurfaceView.class.isInstance(candidate)) {
        const size=candidate.getWidth()*candidate.getHeight();
        if(size>area){selected=candidate;area=size;}
      }
      if(ViewGroup.class.isInstance(candidate)) {
        const group=Java.cast(candidate,ViewGroup);
        for(let index=0;index<group.getChildCount();index++)visit(group.getChildAt(index));
      }
    }
    visit(view);return selected;
  }
  function ensureGameSurface() {
    if(!gameSurface && overlayActivity) {
      const selected=findGameSurface(overlayActivity.getWindow().getDecorView());
      if(selected){
        gameSurface=Java.retain(selected);console.log('CLOUD:surface-aligned '+selected.getWidth()+'x'+selected.getHeight());
        if(overlay&&typeof overlay.setGameSurface==='function')overlay.setGameSurface(gameSurface);
        surfaceGeometry.t=0; // re-read the surface geometry on the very next frame
      }
    }
  }
  // Re-reads the game surface offset and size relative to the overlay. The caller decides when it is due.
  function refreshSurfaceGeometry(width,height) {
    surfaceGeometry.t=Date.now();surfaceGeometry.canvasWidth=width;surfaceGeometry.canvasHeight=height;
    surfaceGeometry.aligned=false;
    if(gameSurface){
      const sw=Number(gameSurface.getWidth()),sh=Number(gameSurface.getHeight());
      if(sw>0&&sh>0){
        gameSurface.getLocationOnScreen(surfacePosition);overlay.getLocationOnScreen(overlayPosition);
        surfaceGeometry.x=Number(surfacePosition[0])-Number(overlayPosition[0]);
        surfaceGeometry.y=Number(surfacePosition[1])-Number(overlayPosition[1]);
        surfaceGeometry.width=sw;surfaceGeometry.height=sh;surfaceGeometry.aligned=true;
      }
    }
  }
  // JavaScript fallback path (EspView.onDraw runs in Frida on the UI thread).
  function drawEsp(canvas) {
    if(!overlay)return;
    ensureGameSurface();
    const count=canvas.save();
    try {
      let width=Number(canvas.getWidth()),height=Number(canvas.getHeight());
      if(Date.now()-surfaceGeometry.t>=250||surfaceGeometry.canvasWidth!==width||surfaceGeometry.canvasHeight!==height)refreshSurfaceGeometry(width,height);
      if(surfaceGeometry.aligned){
        width=surfaceGeometry.width;height=surfaceGeometry.height;
        canvas.translate(surfaceGeometry.x,surfaceGeometry.y);
        canvas.clipRect.overload('int','int','int','int').call(canvas,0,0,width,height);
      }
      renderEsp(canvas,width,height);
    } finally {canvas.restoreToCount(count);}
  }
  // Picture path: renders into the canvas but returns the batched primitives to the caller.
  function renderEspDeferred(canvas,width,height) {
    deferCommands=true;deferredCommands=null;
    try{renderEsp(canvas,width,height);}
    finally{deferCommands=false;frameCommands=null;}
    const commands=deferredCommands;deferredCommands=null;
    return commands;
  }
  function renderEsp(canvas,width,height) {
    if (!espReady || !espEnabled()) {screenRenderer.idle();return;}
    const unit = Math.max(1, Math.min(width,height)/600), font = settings['Text Size']*unit;
    const now = Date.now(), enemyColor=color(settings['Enemy Color']), teamColor=color(settings['Team Color']);
    const labels=[];
    const lines=createLineBatch(),playerLabels=[];
    frameCommands=compiledCanvas?[]:null;
    function placeLabel(value,x,y,tint,direction) {
      const measured=measureText(value,font);
      const textWidth=Math.min(measured,width-12*unit), left=Math.max(6*unit,Math.min(width-textWidth-6*unit,x));
      let baseline=Math.max(font+2*unit,Math.min(height-3*unit,y));
      for(let attempt=0;attempt<6;attempt++) {
        const top=baseline-font-2*unit,bottom=baseline+3*unit;
        const overlaps=labels.some(rect=>left<rect.right && left+textWidth>rect.left && top<rect.bottom && bottom>rect.top);
        if(!overlaps)break;
        const next=baseline+direction*(font+4*unit);
        if(next<font+2*unit || next>height-3*unit)break;
        baseline=next;
      }
      labels.push({left,right:left+textWidth,top:baseline-font-2*unit,bottom:baseline+3*unit});
      text(canvas,value,left,baseline,font,tint);
    }
    screenRenderer.draw(canvas,screenFrame,projected,width,height,unit);
    drawWorldOverlay({settings,text,line,color},canvas,screenFrame.world,width,height,unit);
    if(settings['Player ESP'])for (const item of projected.values()) {
      if (now-item.t > 350 || item.distance > settings['Max Distance']) continue;
      const teammate = localTeam > 0 && item.team === localTeam;
      if (settings['Team Filter'] && teammate) continue;
      if (item.health !== undefined && item.health <= 0) continue;
      const rawTint = teammate ? teamColor : enemyColor;
      // Frozen behind a wall (no data from the server): fade from half to quarter opacity over 5 s.
      const fade = item.staleMs>0 ? Math.round(0x88-(0x88-0x40)*Math.min(1,item.staleMs/5000)) : 0x88;
      const tint = item.dormant ? ((rawTint & 0xffffff) | (fade<<24)) : rawTint;
      const scaleX = width/item.sw, scaleY = height/item.sh;
      const x = item.x*scaleX, top = height-item.y*scaleY;
      const bh = item.h*scaleY, bw=item.bw?item.bw*scaleX:bh*.46, left=x-bw/2, bottom=top+bh;
      const stroke = settings['Line Width']*unit;
      const onScreen = item.z > 0 && bh >= 4 && bh < height*2 && left+bw > 0 && left < width && bottom > 0 && top < height;
      if (!onScreen) {
        if (settings['OOF Arrows']) {
          const direction = item.z < 0 ? -1 : 1;
          const dx=(x-width/2)*direction, dy=(top-height/2)*direction;
          const angle=Math.atan2(dy,dx), radius=Math.min(width,height)*.4;
          const ax=width/2+Math.cos(angle)*radius, ay=height/2+Math.sin(angle)*radius;
          lines.add(tint,stroke,ax,ay,ax-Math.cos(angle-.55)*15*unit,ay-Math.sin(angle-.55)*15*unit);
          lines.add(tint,stroke,ax,ay,ax-Math.cos(angle+.55)*15*unit,ay-Math.sin(angle+.55)*15*unit);
        }
        continue;
      }
      if (settings.Boxes) {
        lines.box(-16777216,stroke+2,left,top,left+bw,bottom,0);
        lines.box(tint,stroke,left,top,left+bw,bottom);
      }
      if(settings.Skeleton) {
        for(const [a,b]of boneEdges) {
          const p=item.bones[a],q=item.bones[b];
          if(p && q && p[2]>0 && q[2]>0)lines.add(tint,stroke,p[0]*scaleX,height-p[1]*scaleY,q[0]*scaleX,height-q[1]*scaleY);
        }
      }
      if (settings.Snaplines) lines.add(tint,stroke,width/2,height,x,bottom);
      if (settings.Health && item.health >= 0 && item.maxHealth > 0) {
        const ratio=Math.max(0,Math.min(1,item.health/item.maxHealth)), bx=left-5*unit;
        lines.add(-16777216,4*unit,bx,top,bx,bottom,0);
        lines.add(color('#73ed96'),2*unit,bx,bottom,bx,bottom-bh*ratio);
        playerLabels.push(()=>text(canvas,String(item.health),bx-25*unit,top+font,font,-1));
      }
      if (settings.Armor && item.armor >= 0 && item.maxArmor > 0) {
        const ratio=Math.max(0,Math.min(1,item.armor/item.maxArmor));
        lines.add(-16777216,4*unit,left,bottom+4*unit,left+bw,bottom+4*unit,0);
        lines.add(color('#72baff'),2*unit,left,bottom+4*unit,left+bw*ratio,bottom+4*unit);
      }
      playerLabels.push(()=>{
        if (settings.Nickname && item.name) {
          const name=(settings['Clan Tag'] && item.clan?'['+item.clan+'] ':'')+item.name;
          placeLabel(name.slice(0,28),left,top-5*unit,tint,-1);
        } else if(settings['Clan Tag'] && item.clan)placeLabel('['+item.clan+']',left,top-5*unit,tint,-1);
        screenRenderer.playerExtras(canvas,item,left,top,bw,bh,unit,font,tint);
        const caption=[];
        if (settings.Weapons && item.weapon) caption.push(item.weapon);
        if (settings.Distance) caption.push(Math.round(item.distance)+' m');
        if(caption.length)placeLabel(caption.join(' · '),left,bottom+font+8*unit,-1,1);
      });
    }
    const batched=lines.drain();
    if(batched.length&&!frameCommands)paint.setStyle(Style.STROKE.value);
    for(const group of batched){
      if(frameCommands){frameCommands.push([1,group.points,group.width,group.tint|0]);continue;}
      paint.setColor(group.tint);paint.setStrokeWidth(group.width);
      canvas.drawLines.overload('[F','android.graphics.Paint').call(canvas,Java.array('float',group.points),paint);
    }
    for(const drawLabels of playerLabels)drawLabels();
    if(frameCommands){
      const commands=frameCommands;frameCommands=null;
      if(deferCommands){deferredCommands=commands;return;}
      try{compiledCanvas.draw(canvas,jstr(JSON.stringify(commands)));}
      catch(error){compiledCanvas=null;console.log('CLOUD:compiled-canvas-error '+error);}
    }
  }
  const EspView = Java.registerClass({
    name:'dev.cloud.standknife.EspCanvas', superClass:View,
    methods:{ $init:[{ returnType:'void', argumentTypes:['android.content.Context'], implementation:function(context) { this.$super.$init(context); } }], onDraw:[{ returnType:'void', argumentTypes:['android.graphics.Canvas'],
      implementation:function(canvas) {
        const start=Date.now();
        try { drawEsp(canvas); } catch(error) {
          if (espFailures++ < 8) console.log('CLOUD:esp-render-error '+error);
        }finally{frameCommands=null;if(espReady)recordFrameCost('draw',Date.now()-start);}
      }
    }] }
  });
  let watermarkView=null,watermarkFonts=null,watermarkScale=1,watermarkRestored=false;
  const watermarkPaint=Paint.$new(3);
  const Typeface=Java.use('android.graphics.Typeface');
  const ColorParser=Java.use('android.graphics.Color');
  const watermarkMeasures=new Map(),watermarkMetrics=new Map(),watermarkColors=new Map();
  function loadWatermarkFonts(a) {
    if(watermarkFonts)return;
    const File=Java.use('java.io.File'),Stream=Java.use('java.io.FileOutputStream'),Base64=Java.use('android.util.Base64');
    const directory=File.$new(a.getCacheDir(),jstr('cloud-watermark'));
    directory.mkdirs();
    const loaded={};
    for(const [name,encoded]of Object.entries(watermarkFontData))try{
      const file=File.$new(directory,jstr(name));
      if(!file.exists() || file.length()===0){
        const temporary=File.$new(directory,jstr(name+'.tmp')),output=Stream.$new(temporary);
        try{output.write.overload('[B').call(output,Base64.decode.overload('java.lang.String','int').call(Base64,jstr(encoded),0));}finally{output.close();}
        if(!temporary.renameTo(file))throw Error('Cannot save watermark font');
      }
      loaded[name]=Typeface.createFromFile.overload('java.lang.String').call(Typeface,file.getAbsolutePath());
    }catch(error){console.log('CLOUD:watermark-font-error '+name+' '+error);}
    const regular=loaded['Inter.ttf']||Typeface.DEFAULT.value;
    let semibold;
    try{semibold=Typeface.create.overload('android.graphics.Typeface','int','boolean').call(Typeface,regular,600,false);}
    catch(error){semibold=Typeface.create.overload('android.graphics.Typeface','int').call(Typeface,regular,1);}
    watermarkFonts={regular,semibold,
      numeric:loaded['JetBrainsMono.ttf']||Typeface.MONOSPACE.value,
      icons:loaded['fa-solid-900.ttf']||regular,brand:loaded['fa-brand-900.ttf']||regular};
  }
  function makeWatermarkPainter(canvas) {
    function font(name,size){watermarkPaint.setTypeface(watermarkFonts[name]);watermarkPaint.setTextSize(size);}
    function metrics(name,size){
      const key=name+':'+size,cached=watermarkMetrics.get(key);
      if(cached)return cached;
      font(name,size);
      const value=watermarkPaint.getFontMetrics();
      const result={ascent:Number(value.ascent.value),descent:Number(value.descent.value)};
      watermarkMetrics.set(key,result);return result;
    }
    function tint(value){
      if(!watermarkColors.has(value))watermarkColors.set(value,ColorParser.parseColor(drawString(value)));
      watermarkPaint.setColor(watermarkColors.get(value));
    }
    return {
      measure(value,name,size){
        const key=name+':'+size+':'+value,cached=watermarkMeasures.get(key);
        if(cached)return cached;
        font(name,size);const shape=metrics(name,size);
        const result={width:Number(watermarkPaint.measureText.overload('java.lang.String').call(watermarkPaint,drawString(value))),
          height:shape.descent-shape.ascent};
        watermarkMeasures.set(key,result);return result;
      },
      text(x,y,value,name,size,shade){font(name,size);tint(shade);watermarkPaint.setStyle(Style.FILL.value);
        const shape=metrics(name,size);
        canvas.drawText.overload('java.lang.String','float','float','android.graphics.Paint').call(canvas,drawString(value),x,y-shape.ascent,watermarkPaint);},
      rect(x,y,width,height,radius,shade){tint(shade);watermarkPaint.setStyle(Style.FILL.value);
        canvas.drawRoundRect.overload('float','float','float','float','float','float','android.graphics.Paint').call(canvas,x,y,x+width,y+height,radius,radius,watermarkPaint);},
      line(x1,y1,x2,y2,width,shade){tint(shade);watermarkPaint.setStrokeWidth(width);canvas.drawLine(x1,y1,x2,y2,watermarkPaint);}
    };
  }
  const WatermarkView=Java.registerClass({name:'dev.cloud.standknife.WatermarkView',superClass:View,methods:{
    $init:[{returnType:'void',argumentTypes:['android.content.Context'],implementation:function(context){this.$super.$init(context);}}],
    onDraw:[{returnType:'void',argumentTypes:['android.graphics.Canvas'],implementation:function(canvas){
      try{
        const date=new Date(),clock=[date.getHours(),date.getMinutes(),date.getSeconds()].map(value=>String(value).padStart(2,'0')).join(':');
        drawWatermark(makeWatermarkPainter(canvas),{fps:gameFrameMeter.value(Date.now()),time:clock},watermarkScale);
      }catch(error){console.log('CLOUD:watermark-draw-error '+error);}
      this.postInvalidateDelayed.overload('long').call(this,1000);
    }}]
  }});
  const WatermarkClick=Java.registerClass({name:'dev.cloud.standknife.WatermarkClick',implements:[Java.use('android.view.View$OnClickListener')],methods:{
    onClick:function(){if(overlayActivity && (!panel || !panel.isShowing()))show(overlayActivity);}
  }});
  function ensureWatermark(a) {
    if(watermarkView)return;
    loadWatermarkFonts(a);
    const metrics=a.getResources().getDisplayMetrics(),density=Number(metrics.density.value);
    watermarkScale=density*.98;
    let box=watermarkLayout(makeWatermarkPainter(null),watermarkScale);
    if(box.width>metrics.widthPixels.value*.9){watermarkScale*=metrics.widthPixels.value*.9/box.width;box=watermarkLayout(makeWatermarkPainter(null),watermarkScale);}
    const view=WatermarkView.$new(a),layout=LayoutParams.$new(Math.ceil(box.width),Math.ceil(box.height));
    layout.gravity.value=51;layout.leftMargin.value=0;layout.topMargin.value=0;
    view.setClickable(true);view.setFocusable(true);view.setContentDescription(jstr('Cloud — открыть меню'));
    view.setOnClickListener(WatermarkClick.$new());
    Java.cast(a.getWindow().getDecorView(),ViewGroup).addView(view,layout);
    watermarkView=Java.retain(view);view.setVisibility(settings.Watermark?0:8);console.log('CLOUD:watermark-ready');
  }
  function ensureOverlay(a) {
    const id=String(a.hashCode());
    if (overlay && overlayActivityId === id) {ensureWatermark(a);return;}
    if(watermarkView){
      const parent=watermarkView.getParent();if(parent)Java.cast(parent,ViewGroup).removeView(watermarkView);
      watermarkView.$dispose();watermarkView=null;
    }
    if (overlay) {
      const parent=overlay.getParent();
      if (parent) Java.cast(parent,ViewGroup).removeView(overlay);
      overlay.$dispose();
      if (overlayActivity) overlayActivity.$dispose();
    }
    if(gameSurface){gameSurface.$dispose();gameSurface=null;}
    preferences=a.getSharedPreferences(jstr('cloud-esp-v05'),0);
    try {
      const saved=JSON.parse(String(preferences.getString(jstr('settings'),jstr('{}'))));
      for (const key of Object.keys(settings)) {
        if (typeof saved[key] !== typeof settings[key]) continue;
        if (key.endsWith('Color') && !/^#[0-9a-f]{6}$/i.test(saved[key])) continue;
        if (typeof saved[key] === 'number' && !Number.isFinite(saved[key])) continue;
        settings[key]=saved[key];
      }
      for(const [key,[minimum,maximum]]of Object.entries(numericSettings))settings[key]=Math.max(minimum,Math.min(maximum,settings[key]));
      noRecoil=saved['No Recoil'] === true;
      if (/^(aim|behavior|players|visuals|scene|weapons|misc)$/.test(saved.__page)) lastPage=saved.__page;
    } catch(error) { console.log('CLOUD:config-load-error '+error); }
    applySafeMode(settings);
    if(!watermarkRestored){settings.Watermark=true;watermarkRestored=true;}
    loadCompiledCanvas(a);
    const root=Java.cast(a.getWindow().getDecorView(),ViewGroup);
    let view,nativeView=false;
    try{if(compiledCanvas){view=compiledCanvas.$new(a);nativeView=true;}}
    catch(error){console.log('CLOUD:picture-view-error '+error);}
    if(!view)view=EspView.$new(a);
    view.setClickable(false); view.setFocusable(false); view.setWillNotDraw(false);
    root.addView(view,LayoutParams.$new(-1,-1));
    overlay=Java.retain(view); overlayActivityId=id; overlayActivity=Java.retain(a);
    publishOverlayFrame=null;clearOverlayFrame=null;
    if(nativeView){
      let reportAt=0;
      // Preferred transport: the script writes packed integers straight into the view's direct ByteBuffer and the view
      // reads them at every vsync, so a frame needs no Frida->Java call. It is used only after the buffer address is
      // verified (plausible readable/writable range, and a word written here is read back by Java); otherwise the
      // one-call frame() transport is used.
      let sharedFrame=null;
      try{
        const address=Java.vm.getEnv().getDirectBufferAddress(overlay.sharedBuffer().$h);
        const range=address.isNull()?null:Process.findRangeByAddress(address);
        if(range&&range.protection.startsWith('rw')&&range.size-address.sub(range.base).toInt32()>=CAPACITY_WORDS*4){
          const candidate=createSharedFrame({address});
          candidate.word(W_SELFTEST).writeS32(0x1234abcd);
          const seen=Number(overlay.sharedWord(W_SELFTEST));
          candidate.word(W_SELFTEST).writeS32(0);
          if(seen===0x1234abcd){sharedFrame=candidate;console.log('CLOUD:shared-frame=on');}
          else console.log('CLOUD:shared-frame-unavailable self-test read '+seen);
        }else console.log('CLOUD:shared-frame-unavailable address '+address+' range '+(range?range.protection+' '+range.size:'none'));
      }catch(error){console.log('CLOUD:shared-frame-unavailable '+error);}
      const publish=createFramePublisher({
        getOverlay:()=>overlay,geometry:surfaceGeometry,ensureSurface:ensureGameSurface,refreshGeometry:refreshSurfaceGeometry,
        render:(width,height)=>renderEspDeferred(null,width,height),encode:encodeFrame,toJavaString:jstr,shared:sharedFrame,getDelayMs:espDelayMs,
        onCost:elapsed=>recordFrameCost('draw',elapsed),log:message=>console.log(message)
      });
      clearOverlayFrame=()=>publish.clear();
      publishOverlayFrame=()=>{
        publish();
        const now=Date.now();
        if(now-reportAt>=10000){
          if(reportAt)console.log('CLOUD:native-picture '+overlay.takeStats()+' '+publish.takePhases());
          reportAt=now;
        }
      };
      console.log('CLOUD:esp-renderer=native-picture');
    }else console.log('CLOUD:esp-renderer=javascript-fallback');
    overlay.postInvalidateOnAnimation();
    ensureWatermark(a);
    console.log('CLOUD:esp-overlay-ready');
  }
  const Dismiss=Java.registerClass({name:'dev.cloud.standknife.MenuDismiss',implements:[Java.use('android.content.DialogInterface$OnDismissListener')],methods:{onDismiss:function(){menuOpen=false;panel=null;if(menuWeb){menuWeb.$dispose();menuWeb=null;}}}});
  function applyMenuAppearance(){
    if(!panel||!menuWeb)return;
    const glass=settings['Liquid Glass'],window=panel.getWindow();
    menuWeb.setBackgroundColor(glass?0:-16446966);
    window.setBackgroundDrawable(Java.use('android.graphics.drawable.ColorDrawable').$new(glass?0:-16446966));
    window.setDimAmount(glass ? .2 : .5);
    if(Java.use('android.os.Build$VERSION').SDK_INT.value>=31)try{window.setBackgroundBlurRadius(glass?40:0);}
    catch(error){console.log('CLOUD:window-blur-unavailable '+error);}
  }
  function show(a){try{
    menuOpen=true;
    ensureOverlay(a);
    const d=Dialog.$new(a),web=WebView.$new(a);panel=d;d.requestWindowFeature(1);
    web.getSettings().setJavaScriptEnabled(true);web.setWebChromeClient(Chrome.$new());web.setBackgroundColor(-16446966);
    const html=__MENU_HTML__.replace('<script>', '<script>window.menuInitial='+JSON.stringify({...settings,'No Recoil':noRecoil})+';window.menuInitialPage='+JSON.stringify(lastPage)+';window.menuRuntime='+JSON.stringify(runtimeState())+';<'+ '/script><script>');
    menuWeb=Java.retain(web);
    web.loadDataWithBaseURL.overload('java.lang.String','java.lang.String','java.lang.String','java.lang.String','java.lang.String').call(web,jstr('https://cloud.invalid/'),jstr(html),jstr('text/html'),jstr('UTF-8'),null);
    d.setContentView(web);d.setCanceledOnTouchOutside(true);d.setOnDismissListener(Dismiss.$new());d.show();
    const w=d.getWindow(),metrics=a.getResources().getDisplayMetrics();w.setBackgroundDrawable(Java.use('android.graphics.drawable.ColorDrawable').$new(-16446966));
    const width=Math.floor(metrics.widthPixels.value*.84);
    const height=Math.floor(Math.min(metrics.heightPixels.value*.84, width*.64));
    w.setLayout(width,height);applyMenuAppearance();
    console.log('CLOUD:menu-visible');
  }catch(e){menuOpen=false;console.log('CLOUD:menu-error '+e)}}
  const dispatchKey=Activity.dispatchKeyEvent.overload('android.view.KeyEvent');
  dispatchKey.implementation=function(event){
    if(settings.Hotkeys&&event.getKeyCode()===25&&overlayActivity){
      if(event.getAction()===1){if(panel&&panel.isShowing())panel.dismiss();else show(overlayActivity);}
      return true;
    }
    return dispatchKey.call(this,event);
  };
  const dialogKey=Dialog.dispatchKeyEvent.overload('android.view.KeyEvent');
  dialogKey.implementation=function(event){
    if(settings.Hotkeys&&event.getKeyCode()===25&&panel&&this.equals(panel)){
      if(event.getAction()===1)this.dismiss();
      return true;
    }
    return dialogKey.call(this,event);
  };
  function attachWatermark(a){try{if(!findGameSurface(a.getWindow().getDecorView()))return;ensureOverlay(a);}catch(error){console.log('CLOUD:watermark-attach-error '+error);}}
  const resume=Activity.onResume.overload();
  resume.implementation=function(){resume.call(this);const current=Java.retain(this);Java.scheduleOnMainThread(()=>{try{attachWatermark(current);}finally{current.$dispose();}});};
  const focus=Activity.onWindowFocusChanged.overload('boolean');
  focus.implementation=function(hasFocus){focus.call(this,hasFocus);if(hasFocus){
    const current=Java.retain(this);Java.scheduleOnMainThread(()=>{try{attachWatermark(current);}finally{current.$dispose();}});
  }};
  Java.scheduleOnMainThread(()=>{try{
    const records=Java.use('android.app.ActivityThread').currentActivityThread().mActivities.value.values().toArray();
    for(let i=0;i<records.length;i++){
      const record=Java.cast(records[i],Java.use('android.app.ActivityThread$ActivityClientRecord'));
      const current=Java.cast(record.activity.value,Activity);
      if(!current.isFinishing() && current.hasWindowFocus()){attachWatermark(current);break;}
    }
  }catch(error){console.log('CLOUD:watermark-initial-attach-error '+error);}});
  console.log('CLOUD:menu-ready');
});
