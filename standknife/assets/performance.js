export function createWorkBudget(){
  const deadlines=new Map(),counts=new Map();
  return {
    due(name,now,interval){
      const previous=deadlines.get(name);interval=Math.max(1,interval);
      if(previous!==undefined&&now+1<previous)return false;
      const next=previous===undefined?now+interval:previous+(Math.floor(Math.max(0,now-previous+1)/interval)+1)*interval;
      deadlines.set(name,next);counts.set(name,(counts.get(name)||0)+1);return true;
    },
    reset(){deadlines.clear();counts.clear();},
    counts(){return Object.fromEntries(counts);}
  };
}
export function playerWork(settings){
  const aim=!!(settings['Knife Bot']||settings['Aim assistance']||settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope']);
  const display=!!(settings['Player ESP']&&['Boxes','Skeleton','Health','Armor','Nickname','Weapons','Distance','Snaplines','OOF Arrows','Show Avatar','Money','Ping','Clan Tag','Bomb Flag','Player Nades','Dormant'].some(key=>settings[key]));
  const hud=['Target HUD','Damage Marker','Hit Logs'].some(key=>settings[key]);
  return {aim,display,hud};
}
import {aimBones} from '../assets/aim-motion.js';
export function neededBones(settings,visual,aimAllowed=true){
  const display=visual&&settings['Player ESP']?(settings.Skeleton?Array.from({length:16},(_,index)=>index):settings.Boxes?[0]:[]):[];
  if(!aimAllowed||!(settings['Knife Bot']||settings['Aim assistance']||settings['Silent Aim']||settings.Trigger||settings['Force Shot']||settings['Auto Scope']))return display;
  const aim=[...aimBones(settings),...(settings['Knife Bot']?aimBones(settings,true):[])];
  return [...new Set([...display,...aim])];
}
