export function createScreenRenderer(context) {
  const {Java, jstr, Style, paint, text, line, color, settings} = context;
  const BitmapFactory=Java.use('android.graphics.BitmapFactory');
  const RectF=Java.use('android.graphics.RectF');
  const Rect=Java.use('android.graphics.Rect');
  const ToneGenerator=Java.use('android.media.ToneGenerator');
  const bitmaps=new Map(), heard=new Set();
  const avatarDestination=RectF.$new();
  let tone=null,soundPrepared=false;
  const getHitSound=context.getHitSound||(()=>null);
  // In a batched frame these append primitives to the frame instead of calling Canvas through the Frida bridge, and
  // return true. Without a batch (JavaScript fallback renderer) they return false and the direct Canvas code below runs.
  const batchFill=context.batchFill||(()=>false),batchCircle=context.batchCircle||(()=>false),batchAvatar=context.batchAvatar||(()=>false);
  function fill(canvas,left,top,right,bottom,tint) {
    if(batchFill(left,top,right,bottom,tint))return;
    paint.setStyle(Style.FILL.value);paint.setColor(tint);
    canvas.drawRect.overload('float','float','float','float','android.graphics.Paint')
      .call(canvas,left,top,right,bottom,paint);
  }
  function circle(canvas,x,y,radius,tint,width) {
    if(batchCircle(x,y,radius,tint,width))return;
    paint.setColor(tint);paint.setStrokeWidth(width);paint.setStyle(Style.STROKE.value);
    canvas.drawCircle(x,y,radius,paint);
  }
  function playerExtras(canvas,item,left,top,bw,bh,unit,font,tint) {
    if(settings['Show Avatar'] && item.avatar && !batchAvatar(item.avatar,left-25*unit-9*unit,top,25*unit)) {
      try {
        let cached=bitmaps.get(item.avatar.id);
        if(!cached || cached.source!==item.avatar) {
          if(cached){cached.bitmap.recycle();cached.bitmap.$dispose();if(cached.sourceRect)cached.sourceRect.$dispose();}
          const signed=Array.from(item.avatar.bytes,byte=>byte>127?byte-256:byte);
          const bytes=Java.array('byte',signed);
          const bitmap=BitmapFactory.decodeByteArray.overload('[B','int','int').call(BitmapFactory,bytes,0,signed.length);
          if(bitmap) {
            const crop=item.avatar.crop;
            const sourceRect=crop?Rect.$new(Math.max(0,crop.x),Math.max(0,crop.y),
              Math.min(bitmap.getWidth(),crop.x+crop.width),Math.min(bitmap.getHeight(),crop.y+crop.height)):null;
            cached={source:item.avatar,bitmap:Java.retain(bitmap),sourceRect};bitmaps.set(item.avatar.id,cached);
          } else cached=null;
          if(bitmaps.size>64) {
            const key=bitmaps.keys().next().value;
            const removed=bitmaps.get(key);removed.bitmap.recycle();removed.bitmap.$dispose();
            if(removed.sourceRect)removed.sourceRect.$dispose();bitmaps.delete(key);
          }
        }
        if(cached) {
          const side=25*unit;
          paint.setStyle(Style.FILL.value);paint.setColor(-1);
          avatarDestination.set.overload('float','float','float','float')
            .call(avatarDestination,left-side-9*unit,top,left-9*unit,top+side);
          canvas.drawBitmap.overload('android.graphics.Bitmap','android.graphics.Rect','android.graphics.RectF','android.graphics.Paint')
            .call(canvas,cached.bitmap,cached.sourceRect,avatarDestination,paint);
        }
      }catch(error){if(!avatarError){console.log('CLOUD:avatar-render-error '+error);avatarError=true;}}
    }
    const labels=[];
    if(settings.Money && Number.isFinite(item.money))labels.push('$'+item.money);
    if(settings.Ping && Number.isFinite(item.ping))labels.push(item.ping+' ms');
    if(settings['Bomb Flag'] && item.bomb)labels.push('C4');
    if(settings['Player Nades']&&item.grenades&&item.grenades.length)labels.push(item.grenades.join(' · '));
    if(item.dormant)labels.push(item.staleMs>0?(item.predicted?'~moving ':'last seen ')+(item.staleMs/1000).toFixed(1)+'s':'last position');
    labels.forEach((label,index)=>text(canvas,label,left+bw+5*unit,top+font*(index+1),font,tint));
  }
  let avatarError=false;
  function sound(events,now) {
    if(!settings['Hit Sound'] && !settings['Kill Sound']) { idle(); return; }
    for(const event of events) {
      if(heard.has(event.id) || now-event.t>300)continue;
      heard.add(event.id);
      if(heard.size>128)heard.delete(heard.values().next().value);
      const enabled=event.kind==='kill'?settings['Kill Sound']:settings['Hit Sound'];
      if(!enabled)continue;
      const kind=Math.max(0,Math.min(3,Math.round(Number(event.kind==='kill'?settings['Kill Sound Type']:settings['Hit Sound Type']))||0));
      const volume=Math.max(50,Math.min(200,Math.round(Number(settings['Hit Sound Volume']))||150));
      const synthesized=getHitSound();
      if(synthesized)try{
        if(!soundPrepared){soundPrepared=!!synthesized.sounds.prepare(jstr(synthesized.dir));console.log('CLOUD:hit-sound prepared='+soundPrepared);}
        if(soundPrepared&&synthesized.sounds.play(kind,volume))continue;
      }catch(error){if(!soundError){console.log('CLOUD:hit-sound-error '+error);soundError=true;}}
      // Fallback when the synthesized sounds are unavailable (or still loading): system tones at full tone volume.
      try {
        if(!tone)tone=Java.retain(ToneGenerator.$new(3,100));
        const id=event.kind==='kill'?ToneGenerator.TONE_PROP_ACK.value:ToneGenerator.TONE_PROP_BEEP.value;
        tone.startTone.overload('int','int').call(tone,id,event.kind==='kill'?110:45);
      }catch(error){if(!soundError){console.log('CLOUD:feedback-sound-error '+error);soundError=true;}}
    }
  }
  let soundError=false;
  function idle() {
    if(tone){tone.release();tone.$dispose();tone=null;}
  }
  function draw(canvas,frame,players,width,height,unit) {
    const now=Date.now(), events=frame.events||[], cx=width/2, cy=height/2;
    const tint=color(settings['Enemy Color']), font=settings['Text Size']*unit;
    const stroke=settings['Line Width']*unit;
    sound(events,now);
    if((settings['Knife Bot']||settings.Trigger||settings['Silent Aim']||settings['Force Shot'])&&frame.aim&&frame.aim.fire&&!frame.aim.fire.ready) {
      text(canvas,'Fire calibration: '+frame.aim.fire.samples+' shots — hold rifle fire without scope',14*unit,height-42*unit,font,-1);
    }
    if(settings['Draw FOV'] && frame.aim && frame.aim.fov>0 && frame.aim.fov<180) {
      const radius=height*.5*Math.tan(settings['Aim FOV']*Math.PI/180)/Math.tan(frame.aim.fov*Math.PI/360);
      circle(canvas,cx,cy,Math.min(width*2,radius),tint,unit);
    }
    const killed=events.filter(event=>event.kind==='kill' && now-event.t<900);
    if(settings['Kill Flash'] && killed.length) {
      const age=now-killed[killed.length-1].t;
      if(age<250)fill(canvas,0,0,width,height,(tint&0xffffff)|Math.round(45*(1-age/250))<<24);
    }
    if(settings['Bullet Tracers'] && frame.sw && frame.sh)for(const trace of frame.traces||[]) {
      const tintAlpha=(tint&0xffffff)|Math.round(255*trace.alpha)<<24;
      line(canvas,trace.a[0]*width/frame.sw,height-trace.a[1]*height/frame.sh,
        trace.b[0]*width/frame.sw,height-trace.b[1]*height/frame.sh,tintAlpha,stroke);
    }
    const recentHits=events.filter(event=>now-event.t<220);
    const hit=recentHits[recentHits.length-1];
    if(settings['Hit Marker'] && hit) {
      const inner=5*unit, outer=12*unit, hitColor=hit.kind==='kill'?tint:-1;
      for(const dx of [-1,1])for(const dy of [-1,1])line(canvas,cx+dx*inner,cy+dy*inner,cx+dx*outer,cy+dy*outer,hitColor,stroke);
    }
    if(settings['Sniper Crosshair'] && frame.sniperWeapon && !frame.scopeActive) {
      line(canvas,cx-8*unit,cy,cx+8*unit,cy,tint,stroke);
      line(canvas,cx,cy-8*unit,cx,cy+8*unit,tint,stroke);
    }
    if(settings['Custom Scope'] && frame.scopeActive) {
      const radius=settings['Scope Radius']*unit;
      circle(canvas,cx,cy,radius,tint,stroke);
      line(canvas,cx-radius-20*unit,cy,cx-6*unit,cy,tint,stroke);
      line(canvas,cx+6*unit,cy,cx+radius+20*unit,cy,tint,stroke);
      line(canvas,cx,cy-radius-20*unit,cx,cy-6*unit,tint,stroke);
      line(canvas,cx,cy+6*unit,cx,cy+radius+20*unit,tint,stroke);
    }
    if(settings['Kill Particles'])for(const event of killed) {
      const age=(now-event.t)/900;
      for(let i=0;i<18;i++) {
        const angle=i*Math.PI*2/18+(event.id%7)*.3;
        const radius=(30+90*age)*unit;
        const x=cx+Math.cos(angle)*radius, y=cy+Math.sin(angle)*radius+age*age*60*unit;
        fill(canvas,x,y,x+3*unit,y+3*unit,(tint&0xffffff)|Math.round(220*(1-age))<<24);
      }
    }
    if(settings['Damage Marker'])for(const event of events) {
      const age=now-event.t;
      if(age>1000 || !event.damage || !event.point)continue;
      const point=event.point;
      text(canvas,'−'+event.damage,point.x*width/point.sw,height-point.y*height/point.sh-age*.035*unit,font,tint);
    }
    if(settings['Hit Logs']) {
      const recent=events.filter(event=>now-event.t<3500).slice(-5);
      recent.forEach((event,index)=>{
        const caption=(event.kind==='kill'?'Kill':'Hit')+(event.name?' · '+event.name:'')+(event.damage?' · '+event.damage+' HP':'');
        const y=(36+index*22)*unit;
        fill(canvas,12*unit,y-font-3*unit,Math.min(width*.4,320*unit),y+5*unit,0xbb0a0d0c|0);
        text(canvas,caption,18*unit,y,font,event.kind==='kill'?tint:-1);
      });
    }
    if(settings['Target HUD']) {
      let selected=null, minimum=Infinity;
      for(const item of players.values()) {
        if(settings['Team Filter'] && context.getLocalTeam()>0 && item.team===context.getLocalTeam())continue;
        if(item.z<=0 || item.dormant || (item.health!==undefined && item.health<=0))continue;
        const x=item.x*width/item.sw,y=height-item.y*height/item.sh;
        const distance=Math.hypot(x-cx,y-cy);
        if(distance<minimum){minimum=distance;selected=item;}
      }
      if(selected && minimum<Math.min(width,height)*.45) {
        const left=cx-100*unit, top=height-100*unit, right=cx+100*unit;
        fill(canvas,left,top,right,top+70*unit,0xdd0a0d0c|0);
        text(canvas,(selected.name||'Player').slice(0,24),left+10*unit,top+22*unit,font,tint);
        text(canvas,(selected.weapon||'')+' · '+Math.round(selected.distance)+' m',left+10*unit,top+43*unit,font,-1);
        if(selected.maxHealth>0) {
          fill(canvas,left+10*unit,top+54*unit,right-10*unit,top+59*unit,0xff303735|0);
          fill(canvas,left+10*unit,top+54*unit,left+10*unit+180*unit*Math.max(0,Math.min(1,selected.health/selected.maxHealth)),top+59*unit,color('#73ed96'));
        }
      }
    }
    if(settings['Check Recoil'] && frame.recoil) {
      const value=frame.recoil;
      text(canvas,'Recoil V '+value.vertical.toFixed(2)+'  H '+value.horizontal.toFixed(2)+'  C '+value.camera.toFixed(2),14*unit,height-20*unit,font,-1);
    }
  }
  return {draw,playerExtras,idle};
}
