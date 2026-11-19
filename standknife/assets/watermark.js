export function watermarkLayout(painter, scale=1) {
  const s=Math.max(.5,Math.min(4,scale));
  const measure=(text,font,size)=>painter.measure(text,font,size*s);
  const brand=measure('Cloud','semibold',13), mark=measure('\uf0e7','brand',12);
  const gauge=measure('\uf625','icons',11), watch=measure('\uf017','icons',11);
  const label=measure('FPS','regular',9),digit=measure('0','numeric',11);
  const width=20*s+19*s+brand.width+40*s+2*s+gauge.width+6*s+4*digit.width+5*s+label.width+watch.width+7*s+8*digit.width+3*s;
  return {scale:s,width,height:30*s,brand,mark,gauge,watch,label,cell:digit.width};
}
export function drawWatermark(painter,data,scale=1) {
  const box=watermarkLayout(painter,scale),s=box.scale,cy=box.height/2;
  const primary='#eeeeee',muted='#969696';
  painter.rect(0,0,box.width,box.height,3*s,'#303030');
  painter.rect(s,s,box.width-2*s,box.height-2*s,2*s,'#101010');
  let x=10*s;
  function centered(value,font,size,tint,measured) {
    const m=measured||painter.measure(value,font,size*s);
    painter.text(x,cy-m.height/2,value,font,size*s,tint);
  }
  painter.text(x+(12*s-box.mark.width)/2,cy-box.mark.height/2,'\uf0e7','brand',12*s,primary);
  x+=19*s;centered('Cloud','semibold',13,primary,box.brand);x+=box.brand.width;
  function separator(){x+=10*s;painter.line(x+s/2,cy-5*s,x+s/2,cy+5*s,s,'#373737');x+=11*s;}
  function digits(value,dimSeconds=false){
    Array.from(value).forEach((letter,index)=>{
      const m=painter.measure(letter,'numeric',11*s);
      painter.text(x+(box.cell-m.width)/2,cy-m.height/2,letter,'numeric',11*s,dimSeconds&&index>=5?muted:primary);
      x+=box.cell;
    });
  }
  separator();centered('\uf625','icons',11,muted,box.gauge);x+=box.gauge.width+6*s;
  const fps=Number.isFinite(data.fps)?String(Math.max(0,Math.min(9999,Math.round(data.fps)))):'—';
  x+=(4-fps.length)*box.cell;digits(fps);x+=5*s;
  centered('FPS','regular',9,muted,box.label);x+=box.label.width;
  separator();centered('\uf017','icons',11,muted,box.watch);x+=box.watch.width+7*s;
  digits(/^([01]\d|2[0-3]):[0-5]\d:[0-5]\d$/.test(data.time)?data.time:'--:--:--',true);
  return box;
}
export function createFrameMeter() {
  let started=0,last=0,frames=0,fps=null;
  return {
    frame(now){
      if(!started || now-last>1500){started=now;frames=0;fps=null;}
      last=now;frames++;
      if(now-started>=1000){fps=(frames-1)*1000/(now-started);started=now;frames=1;}
    },
    value(now){return now-last<1500?fps:null;}
  };
}
