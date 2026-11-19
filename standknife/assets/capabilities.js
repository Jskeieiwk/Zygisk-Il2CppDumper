export function featureAvailable(feature, ready, hooks) {
  if(['Safe Mode','Liquid Glass','Watermark','Hotkeys','Notifications','Accent Color'].includes(feature))return true;
  if (!ready) return false;
  if(['Back Camera','Third Person','Viewmodel'].includes(feature))return hooks['camera-effects']===true;
  if(feature==='Raw Input')return hooks['raw-input']===true;
  if(feature==='Fog')return hooks['scene-effects']===true;
  if(['Item ESP','Grenades','Off-screen Nades','Molotov Radius','Smoke Radius','Player Nades','Bomb Timer','Grenade Glow','Penetration'].includes(feature))return hooks['world-visuals']===true;
  if (feature === 'No Recoil' || feature === 'Check Recoil') {
    return ['vertical','horizontal','camera'].every(axis => hooks['recoil-' + axis] !== false);
  }
  if (feature === 'Custom Scope' || feature === 'Sniper Crosshair') return hooks['scope-view'] !== false;
  if (feature === 'Bullet Tracers') return hooks['bullet-tracer'] !== false;
  if (['Hit Logs','Hit Marker','Damage Marker','Kill Particles','Kill Flash','Hit Sound','Kill Sound'].includes(feature)) {
    return hooks['hit-view'] !== false && (hooks['animator-a708984'] !== false || hooks['animator-a7087f0'] !== false);
  }
  return true;
}
