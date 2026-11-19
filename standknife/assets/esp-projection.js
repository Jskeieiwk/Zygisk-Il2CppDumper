// Keep the skeleton attached to exact head/feet projections between full
// bone samples. Camera rotation is the dominant source of ESP displacement.
export function warpBones(bones,oldHead,oldFeet,newHead,newFeet){
  if(!bones||!oldHead||!oldFeet||!newHead||!newFeet)return null;
  const oldHeight=oldHead[1]-oldFeet[1],newHeight=newHead[1]-newFeet[1];
  if(!Number.isFinite(oldHeight)||!Number.isFinite(newHeight)||Math.abs(oldHeight)<2)return null;
  const scale=newHeight/oldHeight;
  if(!Number.isFinite(scale)||scale<.35||scale>2.85)return null;
  return bones.map(point=>point&&point.every(Number.isFinite)?[
    newHead[0]+(point[0]-oldHead[0])*scale,
    newHead[1]+(point[1]-oldHead[1])*scale,
    newHead[2]+point[2]-oldHead[2]
  ]:null);
}
