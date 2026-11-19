// Anti-aim: the angle other players and the server see is replaced while the game builds it; the player's own view is not touched.
//
// Conventions (taken from assets/aim.js: direction = [sin(yaw)cos(pitch), -sin(pitch), cos(yaw)cos(pitch)]): angles are degrees,
// array order is [pitch, yaw, roll], pitch > 0 looks down, yaw 0 looks along +Z and grows towards +X. Pitch is limited to +-89.
//
// What is measured and what is not (3.3 dump, libil2cpp.so sha256 45a634d2...2339):
//   measured  AimController.GetRotation RVA 0x5452708 and SetRotation RVA 0x54519E4 (script.json, already used by aim.js and
//             fire-control.js), the local AimController at PlayerController+0x128 (fire-control.js reads it the same way).
//   UNKNOWN   senderRva: the function that reads that rotation to build what is sent to the server. It is null, never 0, until it
//             is measured. While it is null the feature is gated (hooks['anti-aim-sender'] stays false) and nothing is hooked.
//   Finding it: switch on "AA Probe" in a match. The probe counts the callers of GetRotation (and SetRotation) for the local
//   AimController and prints them as CLOUD:aa-probe lines. The network writer runs at the send rate and reads the rotation without
//   writing it; the touch-look code is the SetRotation caller. Candidates are checked in ReClass/IDA: the function should
//   also touch the movement/command data. Put the confirmed RVA into ANTI_AIM_CONFIG.senderRva.
export const ANTI_AIM_CONFIG={
  build:'StandKnife 3.3 (libil2cpp.so sha256 45a634d2...2339)',
  getRotation:0x5452708,
  setRotation:0x54519e4,
  aimControllerOffset:0x128,
  senderRva:null,
  // libil2cpp.so is 190280984 bytes; a return address further than this from the module base is not game code.
  moduleLimit:0xc000000
};
export const AA_YAW_MODES=['Смещение','Джиттер','Вращение'];
export const AA_PITCH_MODES=['Без изменений','Вниз','Вверх','Джиттер'];
// Jitter flips between its two sides this often. Not calibrated against anything.
export const AA_JITTER_PERIOD_MS=80;
const finite=value=>Number.isFinite(value);
export function wrapDegrees(value){return ((value+180)%360+360)%360-180;}
export function clampNumber(value,minimum,maximum,fallback){const number=Number(value);return finite(number)?Math.max(minimum,Math.min(maximum,number)):fallback;}
// real: [pitch,yaw,roll] the game would send; now: milliseconds. Returns the angles to send, or null if the input is unusable.
export function antiAimAngles(real,settings,now){
  if(!real||real.length<2||!finite(real[0])||!finite(real[1])||!finite(now))return null;
  const side=Math.floor(now/AA_JITTER_PERIOD_MS)%2===0?1:-1;
  const offset=clampNumber(settings['AA Yaw Offset'],-180,180,180),range=clampNumber(settings['AA Jitter Range'],0,90,30);
  const speed=clampNumber(settings['AA Spin Speed'],30,720,180);
  const yawMode=clampNumber(settings['AA Yaw Mode'],0,AA_YAW_MODES.length-1,0)|0;
  const pitchMode=clampNumber(settings['AA Pitch Mode'],0,AA_PITCH_MODES.length-1,0)|0;
  let yaw=real[1];
  if(yawMode===0)yaw=real[1]+offset;
  else if(yawMode===1)yaw=real[1]+offset+side*range;
  else yaw=now/1000*speed;
  let pitch=real[0];
  if(pitchMode===1)pitch=89;else if(pitchMode===2)pitch=-89;else if(pitchMode===3)pitch=89*side;
  return [Math.max(-89,Math.min(89,pitch)),wrapDegrees(yaw),0];
}
// Counts which game functions call GetRotation/SetRotation on the local AimController. Cheap: one return address per call, and
// it detaches itself after `reports` reports (one every `windowMs`). Switch the setting off and on to run it again.
export function createRotationProbe(context){
  const {base,attachHook,removeHook,getLocalPlayer,canRun,log=console.log,config=ANTI_AIM_CONFIG,windowMs=3000,reports=5}=context;
  let running=false,finished=false,windowStart=0,sent=0,counts=new Map(),other=0;
  function controller(){
    const local=getLocalPlayer();if(!local||local.isNull())return null;
    const aim=local.add(config.aimControllerOffset).readPointer();return aim.isNull()?null:aim;
  }
  function flush(now){
    const seconds=(now-windowStart)/1000;sent++;
    const rows=[...counts].sort((a,b)=>b[1]-a[1]).slice(0,12);
    if(!rows.length)log('CLOUD:aa-probe window='+seconds.toFixed(1)+'s no calls for the local controller (other controllers: '+other+')');
    for(const [key,calls] of rows)log('CLOUD:aa-probe window='+seconds.toFixed(1)+'s '+key+' calls='+calls+' rate='+(calls/seconds).toFixed(1)+'/s');
    counts=new Map();other=0;windowStart=now;
    if(sent>=reports){stop();finished=true;log('CLOUD:aa-probe-done');}
  }
  function record(kind,args,returnAddress){
    const now=Date.now();
    if(!windowStart)windowStart=now;
    const local=controller();
    if(!local||!args[0].equals(local))other++;
    else{
      // Our own calls come from Frida's memory, far outside the module.
      if(returnAddress.compare(base)>=0&&returnAddress.compare(base.add(config.moduleLimit))<0){
        const key=kind+' caller=0x'+returnAddress.sub(base).toInt32().toString(16);counts.set(key,(counts.get(key)||0)+1);
      }
    }
    if(now-windowStart>=windowMs)flush(now);
  }
  function start(){
    if(running||finished)return;
    running=true;windowStart=0;sent=0;counts=new Map();other=0;
    const ok=attachHook(config.getRotation,{onEnter(args){try{record('get',args,this.returnAddress);}catch(error){}}},'aa-probe-get')&&
      attachHook(config.setRotation,{onEnter(args){try{record('set',args,this.returnAddress);}catch(error){}}},'aa-probe-set');
    if(!ok){stop();log('CLOUD:aa-probe-unavailable');}
    else log('CLOUD:aa-probe-started getRotation=0x'+config.getRotation.toString(16)+' setRotation=0x'+config.setRotation.toString(16));
  }
  function stop(){if(running){removeHook('aa-probe-get');removeHook('aa-probe-set');}running=false;}
  function sync(enabled){
    if(!enabled){stop();finished=false;return;}
    if(!canRun()){stop();return;}
    start();
  }
  return {sync,reset(){stop();finished=false;},running:()=>running,done:()=>finished};
}
// Writes the anti-aim angles into the local AimController while the sender function runs, then puts the real angles back
// (the same set-and-restore pattern silent aim uses around the fire command). Without a measured senderRva nothing is hooked.
export function createAntiAim(context){
  const {native,settings,getLocalPlayer,canRun,generation,attachHook,removeHook,log=console.log,config=ANTI_AIM_CONFIG}=context;
  const vector=['float','float','float'];
  const getRotation=native(config.getRotation,vector,['pointer','pointer']),setRotation=native(config.setRotation,'void',['pointer',vector,'pointer']);
  let installed=false,warnings=0;
  const gated=config.senderRva===null||config.senderRva===undefined;
  function detach(){if(installed){removeHook('anti-aim-sender');installed=false;}}
  function attach(){
    if(installed||gated)return;
    installed=attachHook(config.senderRva,{
      onEnter(args){
        this.changed=false;
        try{
          if(!settings['Anti-Aim']||!canRun())return;
          const local=getLocalPlayer();if(!local||local.isNull())return;
          const aim=local.add(config.aimControllerOffset).readPointer();if(aim.isNull())return;
          const real=getRotation(aim,ptr(0)),angles=antiAimAngles(real,settings,Date.now());if(!angles)return;
          this.aim=aim;this.real=real;this.generation=generation();this.changed=true;
          setRotation(aim,angles,ptr(0));
        }catch(error){if(warnings++<5)log('CLOUD:anti-aim-error '+error);}
      },
      onLeave(){
        if(!this.changed)return;
        try{if(this.generation===generation()&&canRun())setRotation(this.aim,this.real,ptr(0));}
        catch(error){if(warnings++<5)log('CLOUD:anti-aim-restore-error '+error);}
      }
    },'anti-aim-sender');
    log('CLOUD:anti-aim-hook '+(installed?'on':'unavailable'));
  }
  function sync(){
    if(!settings['Anti-Aim']||!canRun()){detach();return;}
    attach();
  }
  return {sync,reset:detach,ready:()=>!gated&&installed,gated:()=>gated};
}
