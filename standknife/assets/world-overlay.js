export function screenPoint(point,width,height,sourceWidth,sourceHeight){
  if(!point||!point.every(Number.isFinite)||sourceWidth<=0||sourceHeight<=0)return null;
  return {x:point[0]*width/sourceWidth,y:height-point[1]*height/sourceHeight,z:point[2]};
}
export function edgeArrow(point,width,height){
  const direction=point.z<0?-1:1;
  const angle=Math.atan2((point.y-height/2)*direction,(point.x-width/2)*direction);
  const radius=Math.min(width,height)*.39;
  return {x:width/2+Math.cos(angle)*radius,y:height/2+Math.sin(angle)*radius,angle};
}
export function drawWorldOverlay(context,canvas,world,width,height,unit){
  if(!world||Date.now()-world.t>350)return;
  const {settings,text,line,color}=context,font=settings['Text Size']*unit,stroke=settings['Line Width']*unit;
  const convert=point=>screenPoint(point,width,height,world.sw,world.sh);
  for(const ring of world.rings||[]){
    const tint=color(ring.kind==='fire'?'#ff9d55':'#a1b9cc');
    for(let i=1;i<ring.points.length;i++){
      const a=convert(ring.points[i-1]),b=convert(ring.points[i]);
      if(!a||!b||a.z<=0||b.z<=0)continue;
      if([a,b].some(p=>Math.abs(p.x)>width*8||Math.abs(p.y)>height*8))continue;
      line(canvas,a.x,a.y,b.x,b.y,tint,stroke);
    }
  }
  for(const object of world.objects||[]){
    const point=convert(object.point);if(!point)continue;
    const visible=point.z>0&&point.x>=0&&point.x<=width&&point.y>=0&&point.y<=height;
    const tint=color(object.kind==='grenade'?'#ffc365':object.kind==='bomb'?'#ff7777':'#badcff');
    if(!visible){
      if(object.kind!=='grenade'||!settings['Off-screen Nades'])continue;
      const arrow=edgeArrow(point,width,height);
      for(const sign of [-1,1])line(canvas,arrow.x,arrow.y,
        arrow.x-Math.cos(arrow.angle+sign*.55)*13*unit,
        arrow.y-Math.sin(arrow.angle+sign*.55)*13*unit,tint,stroke);
      text(canvas,object.name,arrow.x+6*unit,arrow.y,font,tint);
    }else{
      if(object.kind==='grenade'&&!settings.Grenades)continue;
      const size=4*unit;
      line(canvas,point.x-size,point.y,point.x+size,point.y,tint,stroke);
      line(canvas,point.x,point.y-size,point.x,point.y+size,tint,stroke);
      const label=object.name+' · '+Math.round(object.distance)+' м';
      text(canvas,label,Math.max(4*unit,Math.min(width-label.length*font*.55,point.x+7*unit)),
        Math.max(font,Math.min(height-font,point.y-5*unit)),font,tint);
    }
  }
  if(settings.Penetration&&world.penetration){
    const probe=world.penetration;
    const label=probe.clear?'Путь свободен':Number.isFinite(probe.thickness)?'Преграда: '+probe.thickness.toFixed(2)+' м':'Преграда: толщина не определена';
    text(canvas,label,width*.5-90*unit,height*.5+36*unit,font,color('#ffc365'));
  }
  if(settings['Bomb Timer'])(world.bombs||[]).forEach((bomb,index)=>{
    const label=Number.isFinite(bomb.seconds)?'C4: '+bomb.seconds.toFixed(1)+' с':'C4: таймер недоступен';
    text(canvas,label,width*.5-70*unit,30*unit+index*(font+6*unit),font,color('#ff7777'));
  });
}
