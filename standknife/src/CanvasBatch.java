package dev.cloud.standknife;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Picture;
import android.graphics.Rect;
import android.graphics.RectF;
import android.content.Context;
import android.view.Choreographer;
import android.view.View;
import android.os.SystemClock;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;
import java.util.LinkedHashMap;
import org.json.JSONArray;

/**
 * ESP overlay. A Frida->Java call costs far more than the drawing itself, so frames normally cross without any call:
 * the script writes packed integers into a direct ByteBuffer (sharedBuffer) and this view reads the newest frame on the UI
 * thread once per vsync (Choreographer) and draws it, using the freshest data available at that moment. frame() is the
 * fallback transport (one call per frame) for when the shared buffer cannot be used.
 */
public final class CanvasBatch extends View {
  // ---- shared buffer layout, in 32-bit words (native byte order)
  static final int HEADER_WORDS=32,CAPACITY_WORDS=1<<18,MAGIC=0x5EED5EED;
  static final int W_SEQ=0,W_MARKER=1,W_LENGTH=2,W_STAMP=3,W_SELFTEST=8,W_DELAY=9; // W_DELAY: milliseconds to hold frames back (script -> Java)
  static final int W_GEOMETRY=16; // Java -> script: width,height,x,y,clipWidth,clipHeight,valid
  private final ByteBuffer shared=ByteBuffer.allocateDirect(CAPACITY_WORDS*4).order(ByteOrder.nativeOrder());
  private final IntBuffer words=shared.asIntBuffer();
  private int[] staging=new int[4096];
  private int seenSequence;
  private boolean polling;
  // The overlay is drawn from a short history so it can be held back to match the game image, which reaches the screen a
  // frame or two after the camera callback that produced this overlay frame. Delay 0 always shows the newest frame.
  private static final int HISTORY=12;
  private final int[][] ring=new int[HISTORY][];
  private final int[] ringLength=new int[HISTORY],ringStamp=new int[HISTORY],ringSequence=new int[HISTORY];
  private final long[] ringArrived=new long[HISTORY];
  private int ringNext,ringCount;
  private int[] shown=new int[0];
  private int shownLength,shownSequence,shownStamp;
  private long shownArrived;
  private int shownDelay;
  // Overlay geometry relative to the game surface, recomputed every vsync and published to the script.
  private int geoX,geoY,geoWidth,geoHeight,geoClipWidth,geoClipHeight;
  private float[] scratchPoints=new float[256];
  private char[] scratchText=new char[256];

  // ---- fallback transport: Picture published by frame()
  // Named differently from the frame() method: Frida's wrapper renames a field that shares a method's name.
  private volatile Picture newestPicture;
  private volatile long frameTime;
  private long published,draws,drawNanos,maxNanos,lagTotal,lagMax;
  // The game's SurfaceView: geometry is derived from it here, so the script does not poll it.
  private volatile View surface;
  private final int[] surfacePosition=new int[2],selfPosition=new int[2];

  // Drawing tools. The UI thread (shared transport) and the game thread (frame() transport) each own a set.
  private static final class Pens {
    final Paint lines=new Paint(3),text=new Paint(3),solid=new Paint(3);final RectF destination=new RectF();
    Pens(){text.setStyle(Paint.Style.FILL);text.setShadowLayer(1.5f,1,1,0xff000000);solid.setStyle(Paint.Style.FILL);}
  }
  private final Pens uiPens=new Pens(),recordPens=new Pens();
  private static final Pens legacyPens=new Pens();

  // Player avatars decoded once and referenced from frames by id.
  private static final class Avatar {final Bitmap bitmap;final Rect source;Avatar(Bitmap b,Rect s){bitmap=b;source=s;}}
  private final LinkedHashMap<Integer,Avatar> avatars=new LinkedHashMap<Integer,Avatar>();

  public CanvasBatch(Context context){super(context);setWillNotDraw(false);}

  public ByteBuffer sharedBuffer(){return shared;}
  /** Reads back a word the script wrote, so it can confirm it addresses the same memory before relying on it. */
  public int sharedWord(int index){return words.get(index);}
  public void setGameSurface(View view){surface=view;}

  // ---------------------------------------------------------------- Picture transport (fallback)
  public void setFrame(Picture next){
    newestPicture=next;frameTime=SystemClock.uptimeMillis();
    synchronized(this){published++;}
    postInvalidate();
  }
  public void clearFrame(){newestPicture=null;postInvalidate();}

  /**
   * Records and publishes one frame (fallback transport). width/height are the overlay size the script last saw,
   * x/y/clipWidth/clipHeight the game surface relative to the overlay (a clip size of zero means no clip). Returns 0 and
   * draws nothing when any of them no longer match, so the caller can re-read them; returns 1 when the frame was published.
   */
  public int frame(int width,int height,float x,float y,float clipWidth,float clipHeight,String commands)throws Exception{
    if(width<=0||height<=0||getWidth()!=width||getHeight()!=height)return 0;
    View game=surface;
    if(game!=null&&clipWidth>0&&clipHeight>0){
      game.getLocationOnScreen(surfacePosition);getLocationOnScreen(selfPosition);
      if(surfacePosition[0]-selfPosition[0]!=(int)x||surfacePosition[1]-selfPosition[1]!=(int)y||
        game.getWidth()!=(int)clipWidth||game.getHeight()!=(int)clipHeight)return 0;
    }
    Picture next=new Picture();
    Canvas canvas=next.beginRecording(width,height);
    try{
      canvas.save();
      canvas.translate(x,y);
      if(clipWidth>0&&clipHeight>0)canvas.clipRect(0f,0f,clipWidth,clipHeight);
      if(commands!=null&&commands.length()>2)drawPacked(canvas,commands,recordPens);
      canvas.restore();
    }finally{next.endRecording();}
    setFrame(next);
    return 1;
  }

  // ---------------------------------------------------------------- shared-buffer transport
  @Override protected void onAttachedToWindow(){
    super.onAttachedToWindow();
    polling=true;
    Choreographer.getInstance().postFrameCallback(tick);
  }
  @Override protected void onDetachedFromWindow(){
    polling=false;
    super.onDetachedFromWindow();
  }
  private final Choreographer.FrameCallback tick=new Choreographer.FrameCallback(){
    @Override public void doFrame(long frameTimeNanos){
      if(!polling)return;
      step();
      Choreographer.getInstance().postFrameCallback(this);
    }
  };
  /** One vsync: publish geometry, take a newer frame if there is one, choose which frame to show, redraw when that changed. */
  void step(){
    publishGeometry();
    pull();
    if(select())invalidate();
  }
  /** Picks the newest frame that is at least the requested delay old (the oldest one while none is yet), or none once it has expired. */
  private boolean select(){
    int delay=Math.max(0,Math.min(200,words.get(W_DELAY)));
    int nowStamp=(int)(System.currentTimeMillis()&0x7fffffffL);
    int wanted=-1;
    for(int k=0;k<ringCount;k++){
      int index=(ringNext-1-k+HISTORY*2)%HISTORY;
      wanted=index; // ends up as the oldest frame when none is old enough
      if(delay==0||nowStamp-ringStamp[index]>=delay)break;
    }
    if(wanted>=0&&SystemClock.uptimeMillis()-ringArrived[wanted]>350+delay)wanted=-1;
    int sequence=wanted<0?0:ringSequence[wanted];
    shownDelay=delay;
    if(sequence==shownSequence)return false;
    shownSequence=sequence;
    if(wanted<0){shownLength=0;return true;}
    shown=ring[wanted];shownLength=ringLength[wanted];shownStamp=ringStamp[wanted];shownArrived=ringArrived[wanted];
    return true;
  }
  private void publishGeometry(){
    int width=getWidth(),height=getHeight();
    int x=0,y=0,clipWidth=0,clipHeight=0;
    View game=surface;
    if(game!=null&&game.getWidth()>0&&game.getHeight()>0){
      game.getLocationOnScreen(surfacePosition);getLocationOnScreen(selfPosition);
      x=surfacePosition[0]-selfPosition[0];y=surfacePosition[1]-selfPosition[1];
      clipWidth=game.getWidth();clipHeight=game.getHeight();
    }
    geoX=x;geoY=y;geoWidth=width;geoHeight=height;geoClipWidth=clipWidth;geoClipHeight=clipHeight;
    words.put(W_GEOMETRY,width);words.put(W_GEOMETRY+1,height);words.put(W_GEOMETRY+2,x);words.put(W_GEOMETRY+3,y);
    words.put(W_GEOMETRY+4,clipWidth);words.put(W_GEOMETRY+5,clipHeight);
    words.put(W_GEOMETRY+6,width>0&&height>0?1:0);
  }
  /** Copies the newest complete frame out of the shared buffer. A torn or incomplete frame is ignored (the previous one stays). */
  private boolean pull(){
    int sequence=words.get(W_SEQ);
    if(sequence==seenSequence||(sequence&1)!=0)return false;
    int length=words.get(W_LENGTH);
    if(length<0||length>CAPACITY_WORDS-HEADER_WORDS)return false;
    // Copy into a staging array first: a torn frame must not damage the frame that is currently on screen.
    if(staging.length<length)staging=new int[Math.max(length,staging.length*2)];
    words.position(HEADER_WORDS);
    words.get(staging,0,length);
    if(words.get(W_SEQ)!=sequence||words.get(W_MARKER)!=(sequence^MAGIC))return false;
    int slot=ringNext;
    if(ring[slot]==null||ring[slot].length<length)ring[slot]=new int[Math.max(length,1024)];
    System.arraycopy(staging,0,ring[slot],0,length);
    ringLength[slot]=length;ringStamp[slot]=words.get(W_STAMP);ringSequence[slot]=sequence;ringArrived[slot]=SystemClock.uptimeMillis();
    ringNext=(slot+1)%HISTORY;if(ringCount<HISTORY)ringCount++;
    seenSequence=sequence;
    return true;
  }

  @Override protected void onDraw(Canvas canvas){
    if(shownLength>0){
      long age=SystemClock.uptimeMillis()-shownArrived;
      if(age>350+shownDelay)return;
      long start=System.nanoTime();
      int level=canvas.save();
      try{
        if(geoClipWidth>0&&geoClipHeight>0){canvas.translate(geoX,geoY);canvas.clipRect(0f,0f,geoClipWidth,geoClipHeight);}
        drawInts(canvas,shown,shownLength,uiPens);
      }finally{canvas.restoreToCount(level);}
      long elapsed=System.nanoTime()-start;
      // Lag from the script writing the frame to this draw (wall clock, low 31 bits), plus the wait for the vsync that picked it up.
      long lag=Math.max(0,((int)(System.currentTimeMillis()&0x7fffffffL))-shownStamp);
      synchronized(this){draws++;published++;drawNanos+=elapsed;maxNanos=Math.max(maxNanos,elapsed);lagTotal+=lag;lagMax=Math.max(lagMax,lag);}
      return;
    }
    Picture current=newestPicture;
    long age=SystemClock.uptimeMillis()-frameTime;
    if(current==null||age>350)return;
    long start=System.nanoTime();
    canvas.drawPicture(current);
    long elapsed=System.nanoTime()-start;
    synchronized(this){
      draws++;drawNanos+=elapsed;maxNanos=Math.max(maxNanos,elapsed);
      lagTotal+=age;lagMax=Math.max(lagMax,age);
    }
  }
  /**
   * draws/avgMs/maxMs: time spent drawing one frame in onDraw (shared transport: decode and draw; fallback: Picture replay).
   * published: frames handed to the view. lagAvgMs/lagMaxMs: age of the frame at draw time (shared transport: from the
   * script's write, including the wait for the vsync and any deliberate delay), not including GPU/compositor time.
   */
  public synchronized String takeStats(){
    String result="draws="+draws+" avgMs="+(draws==0?0:drawNanos/1000000.0/draws)+" maxMs="+maxNanos/1000000.0+
      " published="+published+" lagAvgMs="+(draws==0?0:(double)lagTotal/draws)+" lagMaxMs="+lagMax;
    published=draws=drawNanos=maxNanos=lagTotal=lagMax=0;return result;
  }

  // ---------------------------------------------------------------- avatars
  /** Decodes and keeps an avatar. A zero crop size means the whole image. Bitmaps are never recycled: a frame in flight may still use them. */
  public void setAvatar(int id,byte[] data,int cropX,int cropY,int cropWidth,int cropHeight){
    Bitmap bitmap=BitmapFactory.decodeByteArray(data,0,data.length);
    if(bitmap==null)return;
    Rect source=null;
    if(cropWidth>0&&cropHeight>0)source=new Rect(Math.max(0,cropX),Math.max(0,cropY),Math.min(bitmap.getWidth(),cropX+cropWidth),Math.min(bitmap.getHeight(),cropY+cropHeight));
    synchronized(avatars){
      avatars.put(id,new Avatar(bitmap,source));
      while(avatars.size()>64)avatars.remove(avatars.keySet().iterator().next());
    }
  }
  private Avatar avatar(int id){synchronized(avatars){return avatars.get(id);}}

  // ---------------------------------------------------------------- drawing
  // Integer scales used by assets/frame-codec.js: positions in 1/POS pixel, stroke widths and text sizes in 1/SIZE pixel.
  static final float POS=4f,SIZE=8f;
  /**
   * Packed integer frame, primitives back to back:
   * 1 lines [1,n,strokeWidth,color,x1,y1,...] (n coordinates); 2 text [2,x,y,size,color,length,chars...];
   * 3 filled rectangle [3,left,top,right,bottom,color]; 4 stroked circle [4,x,y,radius,strokeWidth,color];
   * 5 avatar [5,id,left,top,side]. An unknown kind ends the frame (its length is unknown).
   */
  void drawInts(Canvas canvas,int[] data,int length,Pens pens){
    int i=0;
    while(i<length){
      int kind=data[i++];
      if(kind==1){
        if(i+3>length)return;
        int count=data[i++];float width=data[i++]/SIZE;int color=data[i++];
        if(count<0||i+count>length)return;
        if(scratchPoints.length<count)scratchPoints=new float[Math.max(count,scratchPoints.length*2)];
        for(int j=0;j<count;j++)scratchPoints[j]=data[i++]/POS;
        pens.lines.setStyle(Paint.Style.STROKE);pens.lines.setStrokeWidth(width);pens.lines.setColor(color);
        canvas.drawLines(scratchPoints,0,count,pens.lines);
      }else if(kind==2){
        if(i+5>length)return;
        float x=data[i++]/POS,y=data[i++]/POS,size=data[i++]/SIZE;int color=data[i++];int count=data[i++];
        if(count<0||i+count>length)return;
        if(scratchText.length<count)scratchText=new char[Math.max(count,scratchText.length*2)];
        for(int j=0;j<count;j++)scratchText[j]=(char)data[i++];
        pens.text.setTextSize(size);pens.text.setColor(color);
        canvas.drawText(scratchText,0,count,x,y,pens.text);
      }else if(kind==3){
        if(i+5>length)return;
        pens.solid.setColor(data[i+4]);
        canvas.drawRect(data[i]/POS,data[i+1]/POS,data[i+2]/POS,data[i+3]/POS,pens.solid);
        i+=5;
      }else if(kind==4){
        if(i+5>length)return;
        pens.lines.setStyle(Paint.Style.STROKE);pens.lines.setStrokeWidth(data[i+3]/SIZE);pens.lines.setColor(data[i+4]);
        canvas.drawCircle(data[i]/POS,data[i+1]/POS,data[i+2]/POS,pens.lines);
        i+=5;
      }else if(kind==5){
        if(i+4>length)return;
        Avatar avatar=avatar(data[i]);
        float left=data[i+1]/POS,top=data[i+2]/POS,side=data[i+3]/POS;
        i+=4;
        if(avatar==null)continue;
        pens.destination.set(left,top,left+side,top+side);
        pens.solid.setColor(0xffffffff);
        canvas.drawBitmap(avatar.bitmap,avatar.source,pens.destination,pens.solid);
      }else return;
    }
  }
  /** The same primitives as JSON (fallback transport): 1 [1,[x1,y1,...],width,color]; 2 [2,string,x,y,size,color]; 3, 4, 5 as above. */
  private void drawPacked(Canvas canvas,String encoded,Pens pens)throws Exception {
    JSONArray commands=new JSONArray(encoded);
    for(int i=0;i<commands.length();i++){
      JSONArray c=commands.getJSONArray(i);
      int kind=c.getInt(0);
      if(kind==1){
        JSONArray p=c.getJSONArray(1);float[] points=new float[p.length()];
        for(int j=0;j<points.length;j++)points[j]=p.getInt(j)/POS;
        pens.lines.setStyle(Paint.Style.STROKE);pens.lines.setStrokeWidth(c.getInt(2)/SIZE);pens.lines.setColor(c.getInt(3));
        canvas.drawLines(points,pens.lines);
      }else if(kind==2){
        pens.text.setTextSize(c.getInt(4)/SIZE);pens.text.setColor(c.getInt(5));
        canvas.drawText(c.getString(1),c.getInt(2)/POS,c.getInt(3)/POS,pens.text);
      }else if(kind==3){
        pens.solid.setColor(c.getInt(5));
        canvas.drawRect(c.getInt(1)/POS,c.getInt(2)/POS,c.getInt(3)/POS,c.getInt(4)/POS,pens.solid);
      }else if(kind==4){
        pens.lines.setStyle(Paint.Style.STROKE);pens.lines.setStrokeWidth(c.getInt(4)/SIZE);pens.lines.setColor(c.getInt(5));
        canvas.drawCircle(c.getInt(1)/POS,c.getInt(2)/POS,c.getInt(3)/POS,pens.lines);
      }else if(kind==5){
        Avatar avatar=avatar(c.getInt(1));
        if(avatar==null)continue;
        float left=c.getInt(2)/POS,top=c.getInt(3)/POS,side=c.getInt(4)/POS;
        pens.destination.set(left,top,left+side,top+side);
        pens.solid.setColor(0xffffffff);
        canvas.drawBitmap(avatar.bitmap,avatar.source,pens.destination,pens.solid);
      }
    }
  }
  /** Floating-point lines and text, used by the JavaScript fallback renderer. */
  public static void draw(Canvas canvas,String encoded)throws Exception {
    JSONArray commands=new JSONArray(encoded);
    for(int i=0;i<commands.length();i++){
      JSONArray c=commands.getJSONArray(i);
      if(c.getInt(0)==1){
        JSONArray p=c.getJSONArray(1);float[] points=new float[p.length()];
        for(int j=0;j<points.length;j++)points[j]=(float)p.getDouble(j);
        legacyPens.lines.setStyle(Paint.Style.STROKE);legacyPens.lines.setStrokeWidth((float)c.getDouble(2));legacyPens.lines.setColor(c.getInt(3));
        canvas.drawLines(points,legacyPens.lines);
      }else if(c.getInt(0)==2){
        legacyPens.text.setTextSize((float)c.getDouble(4));legacyPens.text.setColor(c.getInt(5));
        canvas.drawText(c.getString(1),(float)c.getDouble(2),(float)c.getDouble(3),legacyPens.text);
      }
    }
  }
}
