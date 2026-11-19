// A performance/diagnostic preset, not a statement about anti-cheat detection.
export const heavyFeatures=['Chams','3D Model','Ghost Chams','Shader Chams','Grenade Glow','Show Avatar','Molotov Radius','Smoke Radius','Item ESP','Grenades','Off-screen Nades','Bomb Timer','Bullet Tracers','Kill Particles','Kill Flash','Liquid Glass','Silent Aim','Force Shot','Trigger','Auto Scope','Autowall','Autowall (Aim)','Auto Calibration','Knife Bot','Back Camera','Third Person','Viewmodel','Fog'];
export function applySafeMode(settings){
  if(!settings['Safe Mode'])return false;
  let changed=false;
  for(const key of heavyFeatures)if(settings[key]===true){settings[key]=false;changed=true;}
  return changed;
}
