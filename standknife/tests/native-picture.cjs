// Exercise the real Java View (CanvasBatch) with minimal Android stubs and a real mini JSON parser.
// This does not substitute for GPU/dex testing on a device.
const {runJava}=require('./helpers/android-stubs.cjs');
const sources={
 'dev/cloud/standknife/PictureChecks.java':`package dev.cloud.standknife;
import android.graphics.*;import android.content.Context;import android.os.SystemClock;import android.view.View;import android.view.Choreographer;
import org.json.JSONArray;
public class PictureChecks {
static void check(boolean ok,String message){if(!ok)throw new AssertionError(message);}
static int[] rectAt(int n){return new int[]{3,n*4,0,n*4+40,40,-1};}
static String shownRect(CanvasBatch view){Canvas c=new Canvas();view.onDraw(c);int at=c.ops.indexOf("rect(");if(at<0)return "none";return c.ops.substring(at+5,c.ops.indexOf(",",at));}
static int stamp(int ageMs){return ((int)(System.currentTimeMillis()&0x7fffffffL))-ageMs;}
static void publish(java.nio.IntBuffer w,int sequence,int[] payload,int stamp){
  w.position(CanvasBatch.HEADER_WORDS);w.put(payload);
  w.put(CanvasBatch.W_LENGTH,payload.length);w.put(CanvasBatch.W_STAMP,stamp);
  w.put(CanvasBatch.W_MARKER,sequence^CanvasBatch.MAGIC);w.put(CanvasBatch.W_SEQ,sequence);
}
static int[] cat(int[]... parts){int total=0;for(int[] p:parts)total+=p.length;int[] all=new int[total];int at=0;for(int[] p:parts){System.arraycopy(p,0,all,at,p.length);at+=p.length;}return all;}
public static void main(String[] args)throws Exception{
CanvasBatch view=new CanvasBatch(new Context());Canvas canvas=new Canvas();
// Empty view, latest frame wins, expiry, clear, telemetry.
view.onDraw(canvas);check(canvas.draws==0,"Empty view draws");
Picture first=new Picture(),latest=new Picture();view.setFrame(first);view.setFrame(latest);
view.onDraw(canvas);check(canvas.last==latest&&canvas.draws==1,"Stale frame queue");
SystemClock.now=351;view.onDraw(canvas);check(canvas.draws==1,"Expired frame drawn");
view.setFrame(first);view.clearFrame();view.onDraw(canvas);check(canvas.draws==1,"Clear failed");
String stats=view.takeStats();check(stats.startsWith("draws=1 "),stats);
check(view.takeStats().startsWith("draws=0 "),"Stats not reset");

// frame(): size handshake. A mismatch draws nothing and publishes nothing.
check(view.frame(10,10,0,0,0,0,null)==0,"A size mismatch must return 0");
check(view.frame(0,0,0,0,0,0,null)==0,"A zero size must return 0");
SystemClock.now=1000;
check(view.frame(200,100,0,0,0,0,null)==1,"A matching empty frame is published");
check(Picture.lastCreated.began&&Picture.lastCreated.ended,"A published Picture must be closed");
check(Picture.lastCreated.canvas.ops.equals("save;translate(0.0,0.0);restore;"),"Empty frame ops: "+Picture.lastCreated.canvas.ops);
SystemClock.now=1040;view.onDraw(canvas);
String frameStats=view.takeStats();
check(frameStats.contains(" published=1 ")&&frameStats.contains("lagAvgMs=40.0")&&frameStats.contains("lagMaxMs=40"),frameStats);

// Offset and clip are applied in order; a zero clip means no clip.
check(view.frame(200,100,5,7,150,80,"[]")==1,"frame with clip");
check(Picture.lastCreated.canvas.ops.equals("save;translate(5.0,7.0);clip(0.0,0.0,150.0,80.0);restore;"),Picture.lastCreated.canvas.ops);
view.takeStats();

// The game surface: Java verifies its offset and size so JS does not poll them per frame.
View surface=new View(new Context());surface.width=150;surface.height=80;surface.locX=15;surface.locY=27;
view.setGameSurface(surface); // overlay itself sits at 10,20
view.locX=10;view.locY=20;
check(view.frame(200,100,5,7,150,80,null)==1,"A matching surface geometry is accepted");
check(view.frame(200,100,6,7,150,80,null)==0,"A moved surface must be rejected");
check(view.frame(200,100,5,8,150,80,null)==0,"A moved surface (y) must be rejected");
check(view.frame(200,100,5,7,151,80,null)==0,"A resized surface must be rejected");
check(view.frame(200,100,5,7,150,81,null)==0,"A resized surface (height) must be rejected");
check(view.frame(200,100,0,0,0,0,null)==1,"An unaligned frame (zero clip) skips the surface check");
check(view.takeStats().contains(" published=2 "),"Rejected frames must not be published");

// Packed primitives, in order: lines, text, rectangle, circle, avatar, unknown kind, unknown avatar id.
// Scales: positions 1/4 px, sizes 1/8 px.
view.setAvatar(1,new byte[]{64,32},0,0,0,0);
view.setAvatar(2,new byte[]{64,32},-5,-5,100,100); // crop is clamped to the bitmap
view.setAvatar(3,new byte[]{0,0},0,0,0,0);           // undecodable: ignored
view.frame(200,100,0,0,0,0,"[[1,[4,8,12,16],16,-1],[2,\\"Hi\\",40,80,104,-16777216],[3,4,8,40,80,-1],[4,40,80,20,16,3],[5,1,8,16,100],[5,2,8,16,100],[5,3,8,16,100],[9,1,2],[5,99,8,16,100]]");
String expected="save;translate(0.0,0.0);lines[1.0, 2.0, 3.0, 4.0]w2.0c-1;text(Hi,10.0,20.0,size13.0,c-16777216);"+
  "rect(1.0,2.0,10.0,20.0,c-1);circle(10.0,20.0,5.0,w2.0,c3);"+
  "bitmap(64x32,null,F(2.0,4.0,27.0,29.0),c-1);bitmap(64x32,R(0,0,64,32),F(2.0,4.0,27.0,29.0),c-1);restore;";
check(Picture.lastCreated.canvas.ops.equals(expected),"Packed decode: "+Picture.lastCreated.canvas.ops);
view.takeStats();

// A failing frame (bad JSON) is not published and its Picture is still closed.
Picture before=Picture.lastCreated;
boolean threw=false;
try{view.frame(200,100,0,0,0,0,"[[1,[1,2],");}catch(Exception | Error expectedFailure){threw=true;}
check(threw,"Malformed commands must fail the frame");
check(Picture.lastCreated!=before&&Picture.lastCreated.ended,"A failed frame must still close its Picture");
check(view.takeStats().contains(" published=0 "),"A failed frame must not be published");

// Avatar cache is bounded: the oldest entries go, the newest stay.
for(int id=100;id<200;id++)view.setAvatar(id,new byte[]{8,8},0,0,0,0);
view.frame(200,100,0,0,0,0,"[[5,100,0,0,4],[5,199,0,0,4]]");
String ops=Picture.lastCreated.canvas.ops;
int bitmaps=0;for(int at=ops.indexOf("bitmap(");at>=0;at=ops.indexOf("bitmap(",at+1))bitmaps++;
check(bitmaps==1,"Only the newest avatar remains (the evicted one is skipped): "+ops);
check(ops.contains("bitmap(8x8"),"The newest avatar is drawn: "+ops);
System.out.println("Java Picture frame handshake, surface check, packed primitives, avatar cache and failure rollback checks passed.");
// ---------------------------------------------------------------- shared-buffer transport
CanvasBatch live=new CanvasBatch(new Context());
View game=new View(new Context());game.width=150;game.height=80;game.locX=15;game.locY=27;live.locX=10;live.locY=20;
live.setGameSurface(game);live.setAvatar(1,new byte[]{64,32},0,0,0,0);
java.nio.IntBuffer w=live.sharedBuffer().asIntBuffer();
live.step();
check(w.get(16)==200&&w.get(17)==100&&w.get(18)==5&&w.get(19)==7&&w.get(20)==150&&w.get(21)==80&&w.get(22)==1,"Geometry is published to the script every vsync");
check(live.invalidations==0,"No frame yet, no redraw");
SystemClock.now=5000;
int[] rect={3,4,8,40,80,-1};
publish(w,2,rect,stamp(0));
live.step();
check(live.invalidations==1,"A new frame triggers a redraw");
Canvas shown2=new Canvas();live.onDraw(shown2);
check(shown2.ops.equals("save;translate(5.0,7.0);clip(0.0,0.0,150.0,80.0);rect(1.0,2.0,10.0,20.0,c-1);restore;"),"Shared frame ops: "+shown2.ops);
live.step();check(live.invalidations==1,"An unchanged sequence does not redraw");
// A frame in the middle of being written (odd sequence), a torn frame (marker from another frame) and a nonsense length are ignored.
publish(w,3,new int[]{3,0,0,4,4,-1},stamp(0));w.put(0,3);
live.step();check(live.invalidations==1,"An odd sequence is ignored");
publish(w,4,new int[]{3,0,0,4,4,-1},stamp(0));w.put(1,0x1234);
live.step();check(live.invalidations==1,"A frame whose marker does not match is ignored");
publish(w,6,new int[]{3,0,0,4,4,-1},stamp(0));w.put(2,CanvasBatch.CAPACITY_WORDS);
live.step();check(live.invalidations==1,"An absurd length is ignored");
shown2=new Canvas();live.onDraw(shown2);
check(shown2.ops.contains("rect(1.0,2.0,10.0,20.0"),"The previous good frame stays on screen after a bad one");
// Every primitive kind, in order; text goes through chars; an unknown kind ends the frame; a truncated primitive does not throw.
int[] everything=cat(new int[]{1,4,16,-1,4,8,12,16},new int[]{2,40,80,104,-16777216,2,72,105},new int[]{3,4,8,40,80,-1},new int[]{4,40,80,20,16,3},new int[]{5,1,8,16,100},new int[]{5,99,8,16,100},new int[]{99,1,2,3},new int[]{3,0,0,4,4,-1});
publish(w,8,everything,stamp(25));
live.step();
Canvas all=new Canvas();live.onDraw(all);
String expectedAll="save;translate(5.0,7.0);clip(0.0,0.0,150.0,80.0);lines[1.0, 2.0, 3.0, 4.0]w2.0c-1;text(Hi,10.0,20.0,size13.0,c-16777216);rect(1.0,2.0,10.0,20.0,c-1);circle(10.0,20.0,5.0,w2.0,c3);"+
  "bitmap(64x32,null,F(2.0,4.0,27.0,29.0),c-1);restore;";
check(all.ops.equals(expectedAll),"All kinds: "+all.ops);
String lagStats=live.takeStats();
check(lagStats.contains(" lagMaxMs=")&&Long.parseLong(lagStats.substring(lagStats.indexOf("lagMaxMs=")+9))>=25,"Lag is measured from the script's write time: "+lagStats);
publish(w,10,new int[]{1,100,16,-1,4,8},stamp(0)); // declares 100 coordinates but only 2 follow
live.step();
live.onDraw(new Canvas());
publish(w,12,new int[]{2,40,80,104,-1,500,72},stamp(0)); // declares 500 characters
live.step();
live.onDraw(new Canvas());
// Expiry: with no newer frame the overlay clears itself after 350 ms.
int redraws=live.invalidations;
SystemClock.now=5000+351;live.step();
check(live.invalidations==redraws+1,"An expired frame requests one clearing redraw");
Canvas blank=new Canvas();live.onDraw(blank);check(blank.ops.equals(""),"Nothing is drawn after expiry: "+blank.ops);
live.step();check(live.invalidations==redraws+1,"Expiry redraws once");
// The vsync loop: attached views poll every frame, detached views stop.
live.onAttachedToWindow();
check(Choreographer.getInstance().pending!=null,"Attaching starts the vsync loop");
android.view.Choreographer.FrameCallback loop=Choreographer.getInstance().pending;Choreographer.getInstance().pending=null;
loop.doFrame(0);
check(Choreographer.getInstance().pending==loop,"A running loop reposts itself");
live.onDetachedFromWindow();Choreographer.getInstance().pending=null;loop.doFrame(0);
check(Choreographer.getInstance().pending==null,"A detached view does not repost");
// ---------------------------------------------------------------- delayed display (matching the game image)
CanvasBatch held=new CanvasBatch(new Context());
java.nio.IntBuffer hw=held.sharedBuffer().asIntBuffer();
SystemClock.now=9000;
publish(hw,2,rectAt(1),stamp(100));held.step();
publish(hw,4,rectAt(2),stamp(50));held.step();
publish(hw,6,rectAt(3),stamp(5));held.step();
check(shownRect(held).equals("3.0"),"Delay 0 shows the newest frame: "+shownRect(held));
int shownChanges=held.invalidations;
hw.put(CanvasBatch.W_DELAY,30);held.step();
check(shownRect(held).equals("2.0"),"A 30 ms delay shows the newest frame that is at least 30 ms old: "+shownRect(held));
check(held.invalidations==shownChanges+1,"Choosing an older frame requests one redraw");
held.step();check(held.invalidations==shownChanges+1,"An unchanged choice does not redraw");
hw.put(CanvasBatch.W_DELAY,200);held.step();
check(shownRect(held).equals("1.0"),"When nothing is old enough yet the oldest frame is shown: "+shownRect(held));
hw.put(CanvasBatch.W_DELAY,0);held.step();
check(shownRect(held).equals("3.0"),"Delay 0 returns to the newest frame");
hw.put(CanvasBatch.W_DELAY,-5);held.step();check(shownRect(held).equals("3.0"),"A negative delay is treated as 0");
hw.put(CanvasBatch.W_DELAY,100000);held.step();check(shownRect(held).equals("1.0"),"An absurd delay is capped, not trusted");
// The history is a ring: old frames fall out and new ones keep working.
hw.put(CanvasBatch.W_DELAY,0);
for(int n=0;n<40;n++){publish(hw,8+2*n,rectAt(10+n),stamp(0));held.step();}
check(shownRect(held).equals("49.0"),"A long run of frames keeps showing the newest: "+shownRect(held));
hw.put(CanvasBatch.W_DELAY,60);
for(int n=0;n<3;n++){publish(hw,200+2*n,rectAt(60+n),stamp(0));held.step();}
check(shownRect(held).equals("41.0"),"With only young frames the oldest of the 12 kept frames is shown: "+shownRect(held));
// Expiry counts the delay: a held-back frame is not dropped while it is still within 350 ms + delay.
hw.put(CanvasBatch.W_DELAY,100);held.step();
SystemClock.now=9000+449;held.step();check(!shownRect(held).equals("none"),"A frame younger than 350 ms plus the delay is kept");
SystemClock.now=9000+451;held.step();check(shownRect(held).equals("none"),"A frame older than 350 ms plus the delay expires");
System.out.println("Java shared-buffer transport: geometry, new/duplicate/odd/torn/absurd frames, every primitive, expiry, lag and the vsync loop passed.");
}}`
};
process.stdout.write(runJava(sources,'dev.cloud.standknife.PictureChecks'));
