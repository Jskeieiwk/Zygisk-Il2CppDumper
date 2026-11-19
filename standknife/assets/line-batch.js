// Collect player geometry by paint, then cross the Frida/Java boundary once
// per paint instead of once per segment or player.
export function createLineBatch(){
  const groups=new Map();
  // Consecutive segments almost always share a style (a whole skeleton, a whole box), so the last group is reused
  // without building a key string.
  let lastGroup=null;
  function add(tint,width,x1,y1,x2,y2,layer=1){
    if(!(Number.isFinite(x1)&&Number.isFinite(y1)&&Number.isFinite(x2)&&Number.isFinite(y2)))return;
    let group=lastGroup;
    if(!group||group.tint!==tint||group.width!==width||group.layer!==layer){
      const key=layer+':'+tint+':'+width;
      group=groups.get(key);
      if(!group){group={tint,width,layer,points:[]};groups.set(key,group);}
      lastGroup=group;
    }
    group.points.push(x1,y1,x2,y2);
  }
  function box(tint,width,left,top,right,bottom,layer=1){
    add(tint,width,left,top,right,top,layer);
    add(tint,width,right,top,right,bottom,layer);
    add(tint,width,right,bottom,left,bottom,layer);
    add(tint,width,left,bottom,left,top,layer);
  }
  function drain(){
    const result=[...groups.values()].sort((a,b)=>a.layer-b.layer);
    groups.clear();lastGroup=null;return result;
  }
  return {add,box,drain};
}
