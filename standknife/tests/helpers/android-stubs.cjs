// Shared Android stubs and a compile-and-run helper for the Java tests (CanvasBatch against minimal Android classes).
const fs=require('node:fs'),path=require('node:path'),os=require('node:os');
const {execFileSync}=require('node:child_process');
const stubSources={
 'android/content/Context.java':'package android.content; public class Context {}',
 'android/os/SystemClock.java':'package android.os; public class SystemClock {public static long now;public static long uptimeMillis(){return now;}}',
 'android/view/View.java':'package android.view; import android.content.Context;import android.graphics.Canvas;public class View {public int width=200,height=100,locX,locY;public View(Context c){}public void setWillNotDraw(boolean b){}public void postInvalidate(){}public int invalidations;public void invalidate(){invalidations++;}protected void onAttachedToWindow(){}protected void onDetachedFromWindow(){}public int getWidth(){return width;}public int getHeight(){return height;}public void getLocationOnScreen(int[] l){l[0]=locX;l[1]=locY;}protected void onDraw(Canvas c){}}',
 'android/graphics/Picture.java':'package android.graphics;public class Picture {public static Picture lastCreated;public boolean began,ended;public Canvas canvas=new Canvas();public Picture(){lastCreated=this;}public Canvas beginRecording(int w,int h){began=true;return canvas;}public void endRecording(){ended=true;}}',
 'android/graphics/Paint.java':'package android.graphics;public class Paint {public enum Style {FILL,STROKE}public Paint(int f){}public void setStyle(Style s){}public void setShadowLayer(float a,float b,float c,int d){}public float width,size;public int color;public void setStrokeWidth(float w){width=w;}public void setColor(int c){color=c;}public void setTextSize(float s){size=s;}}',
 'android/graphics/Bitmap.java':'package android.graphics;public class Bitmap {private final int w,h;public Bitmap(int w,int h){this.w=w;this.h=h;}public int getWidth(){return w;}public int getHeight(){return h;}}',
 'android/graphics/BitmapFactory.java':'package android.graphics;public class BitmapFactory {public static Bitmap decodeByteArray(byte[] d,int o,int l){return d[0]==0?null:new Bitmap(d[0],d[1]);}}',
 'android/graphics/Rect.java':'package android.graphics;public class Rect {public final int l,t,r,b;public Rect(int l,int t,int r,int b){this.l=l;this.t=t;this.r=r;this.b=b;}public String toString(){return "R("+l+","+t+","+r+","+b+")";}}',
 'android/graphics/RectF.java':'package android.graphics;public class RectF {public float l,t,r,b;public void set(float l,float t,float r,float b){this.l=l;this.t=t;this.r=r;this.b=b;}public String toString(){return "F("+l+","+t+","+r+","+b+")";}}',
 'android/graphics/Canvas.java':`package android.graphics;
public class Canvas {
  public Picture last;public int draws;public String ops="";
  public int save(){ops+="save;";return 1;}
  public void restore(){ops+="restore;";}
  public void restoreToCount(int level){ops+="restore;";}
  public void translate(float x,float y){ops+="translate("+x+","+y+");";}
  public void clipRect(float l,float t,float r,float b){ops+="clip("+l+","+t+","+r+","+b+");";}
  public void drawPicture(Picture p){last=p;draws++;}
  public void drawLines(float[] p,Paint a){ops+="lines"+java.util.Arrays.toString(p)+"w"+a.width+"c"+a.color+";";}
  public void drawLines(float[] p,int offset,int count,Paint a){ops+="lines"+java.util.Arrays.toString(java.util.Arrays.copyOfRange(p,offset,offset+count))+"w"+a.width+"c"+a.color+";";}
  public void drawText(String s,float x,float y,Paint p){ops+="text("+s+","+x+","+y+",size"+p.size+",c"+p.color+");";}
  public void drawText(char[] s,int index,int count,float x,float y,Paint p){drawText(new String(s,index,count),x,y,p);}
  public void drawRect(float l,float t,float r,float b,Paint p){ops+="rect("+l+","+t+","+r+","+b+",c"+p.color+");";}
  public void drawCircle(float x,float y,float r,Paint p){ops+="circle("+x+","+y+","+r+",w"+p.width+",c"+p.color+");";}
  public void drawBitmap(Bitmap b,Rect s,RectF d,Paint p){ops+="bitmap("+b.getWidth()+"x"+b.getHeight()+","+s+","+d+",c"+p.color+");";}
}`,
 // A real (minimal) JSON array parser: ints, strings with a backslash escape, nested arrays.
 'org/json/JSONArray.java':`package org.json;
import java.util.ArrayList;
public class JSONArray {
  public static int created;
  private final ArrayList<Object> items=new ArrayList<Object>();
  public JSONArray(String s){created++;parse(s,new int[]{0},this);}
  private JSONArray(){}
  private static void parse(String s,int[] at,JSONArray into){
    if(s.charAt(at[0])!='[')throw new IllegalArgumentException("not an array");
    at[0]++;
    while(s.charAt(at[0])!=']'){
      char c=s.charAt(at[0]);
      if(c==',')at[0]++;
      else if(c=='['){JSONArray inner=new JSONArray();parse(s,at,inner);into.items.add(inner);}
      else if(c=='"'){int j=at[0]+1;StringBuilder b=new StringBuilder();while(s.charAt(j)!='"'){if(s.charAt(j)==92)j++;b.append(s.charAt(j));j++;}at[0]=j+1;into.items.add(b.toString());}
      else{int j=at[0];while(s.charAt(j)!=','&&s.charAt(j)!=']')j++;into.items.add(Long.valueOf(s.substring(at[0],j)));at[0]=j;}
    }
    at[0]++;
  }
  public int length(){return items.size();}
  public JSONArray getJSONArray(int i){return (JSONArray)items.get(i);}
  public int getInt(int i){return ((Long)items.get(i)).intValue();}
  public double getDouble(int i){return ((Long)items.get(i)).doubleValue();}
  public String getString(int i){return (String)items.get(i);}
}`,
 'android/view/Choreographer.java':`package android.view;public class Choreographer {public interface FrameCallback {void doFrame(long frameTimeNanos);}private static final Choreographer instance=new Choreographer();public static Choreographer getInstance(){return instance;}public FrameCallback pending;public void postFrameCallback(FrameCallback c){pending=c;}}`
};
// Compiles stubSources, extraSources and src/CanvasBatch.java, then runs mainClass. Returns its stdout.
function runJava(extraSources,mainClass,args=[]){
  const dir=fs.mkdtempSync(path.join(os.tmpdir(),'cloud-picture-test-'));
  try{
    const files=[];
    for(const [name,source] of Object.entries({...stubSources,...extraSources})){
      const file=path.join(dir,name);fs.mkdirSync(path.dirname(file),{recursive:true});fs.writeFileSync(file,source);files.push(file);
    }
    files.push(path.resolve('src/CanvasBatch.java'));
    execFileSync('java',['-jar','tools/ecj.jar','-8','-proc:none','-nowarn','-d',dir,...files],{stdio:'pipe'});
    return execFileSync('java',['-cp',dir,mainClass,...args],{encoding:'utf8'});
  }finally{fs.rmSync(dir,{recursive:true,force:true});}
}
module.exports={stubSources,runJava};
