package com.cloudcrack.oxide.external;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.SystemClock;
import android.view.View;
import java.nio.charset.StandardCharsets;

final class EspView extends View {
    private float[][] world=new float[0][];
    private long worldTime;
    void world(String line){
        world=new float[0][];
        try{String[] values=line.split(" ");int count=Integer.parseInt(values[1]);if(count<0||count>2048||values.length!=2+count*4)return;
            float[][] parsed=new float[count][4];for(int i=0;i<count;i++)for(int j=0;j<4;j++){parsed[i][j]=Float.parseFloat(values[2+i*4+j]);if(!Float.isFinite(parsed[i][j]))return;}
            world=parsed;worldTime=SystemClock.uptimeMillis();
        }catch(RuntimeException ignored){}invalidate();
    }
    private String worldName(int kind){switch(kind){case 200:return "Машина";case 201:return "Вертолёт";case 202:return "Лодка";case 1:return "Медведь";case 2:return "Кабан";case 3:return "Олень";case 4:case 22:return "Заяц";case 5:return "Курица";case 6:return "Рыба";case 8:return "Дерево";case 9:return "Камень";case 10:return "Железо";case 11:return "Сера";case 25:return "Крыса";case 26:return "Волк";case 27:return "Акула";case 101:return "Военный ящик";case 102:return "Элитный ящик";case 103:return "Красный ящик";default:return "Ящик";}}
    private final Paint paint=new Paint(3);
    private boolean showFov;private int radius=100;
    void aimSettings(boolean enabled,int value){if(showFov!=enabled||radius!=value){showFov=enabled;radius=value;invalidate();}}
    private float[] view,projection;
    private String[] frame;
    private long matrixTime,frameTime,bonesTime;
    private float[][][] bones=new float[0][][];
    private static final int[][] LINKS={{0,1},{1,2},{2,3},{3,4},{2,5},{5,7},{7,9},{2,6},{6,8},{8,10},{0,11},{11,13},{13,15},{0,12},{12,14},{14,16}};
    void bones(String line){
        bones=new float[0][][];
        try{String[] values=line.split(" ");int count=Integer.parseInt(values[1]);if(count<0||count>32||values.length!=2+count*17*4)return;
            float[][][] parsed=new float[count][17][];int at=2;
            for(int i=0;i<count;i++)for(int j=0;j<17;j++){boolean valid=values[at].equals("1");float x=Float.parseFloat(values[at+1]),y=Float.parseFloat(values[at+2]),z=Float.parseFloat(values[at+3]);if(valid&&Float.isFinite(x)&&Float.isFinite(y)&&Float.isFinite(z))parsed[i][j]=new float[]{x,y,z};at+=4;}
            bones=parsed;bonesTime=SystemClock.uptimeMillis();
        }catch(RuntimeException ignored){}invalidate();
    }
    EspView(Context context){super(context);setImportantForAccessibility(IMPORTANT_FOR_ACCESSIBILITY_NO);}
    void matrix(String line){
        String[] values=line.split(" ");view=projection=null;
        if(values.length!=34||!values[1].equals("1")){invalidate();return;}
        try{
            float[] v=new float[16],p=new float[16];
            for(int i=0;i<16;i++){v[i]=Float.parseFloat(values[i+2]);p[i]=Float.parseFloat(values[i+18]);if(!Float.isFinite(v[i])||!Float.isFinite(p[i]))return;}
            view=v;projection=p;matrixTime=SystemClock.uptimeMillis();
        }catch(NumberFormatException ignored){}
        invalidate();
    }
    void frame(String[] values){frame=values;frameTime=SystemClock.uptimeMillis();invalidate();}
    private float[] multiply(float[] m,float x,float y,float z,float w){
        return new float[]{m[0]*x+m[4]*y+m[8]*z+m[12]*w,m[1]*x+m[5]*y+m[9]*z+m[13]*w,
            m[2]*x+m[6]*y+m[10]*z+m[14]*w,m[3]*x+m[7]*y+m[11]*z+m[15]*w};
    }
    private boolean inEspRange(float x,float y,float z){
        float ex=-(view[0]*view[12]+view[1]*view[13]+view[2]*view[14]),ey=-(view[4]*view[12]+view[5]*view[13]+view[6]*view[14]),ez=-(view[8]*view[12]+view[9]*view[13]+view[10]*view[14]);
        float dx=x-ex,dy=y-ey,dz=z-ez;return dx*dx+dy*dy+dz*dz<=90000;
    }
    private float[] screen(float x,float y,float z){
        float[] camera=multiply(view,x,y,z,1),clip=multiply(projection,camera[0],camera[1],camera[2],camera[3]);
        if(clip[3]<.05f)return null;
        float sx=(clip[0]/clip[3]+1)*getWidth()*.5f,sy=(1-clip[1]/clip[3])*getHeight()*.5f;
        return Float.isFinite(sx)&&Float.isFinite(sy)?new float[]{sx,sy}:null;
    }
    private String name(String hex){
        if(hex.equals("-")||hex.length()%2!=0||hex.length()>384)return "Игрок";
        byte[] bytes=new byte[hex.length()/2];
        for(int i=0;i<bytes.length;i++){int a=Character.digit(hex.charAt(i*2),16),b=Character.digit(hex.charAt(i*2+1),16);if(a<0||b<0)return "Игрок";bytes[i]=(byte)(a*16+b);}
        return new String(bytes,StandardCharsets.UTF_8);
    }
    @Override protected void onDraw(Canvas c){
        android.content.SharedPreferences cross=getContext().getSharedPreferences("visuals",0);
        if(cross.getBoolean("crosshair",false)){
            float radius=getContext().getSharedPreferences("aim",0).getInt("crossSize",8)*getResources().getDisplayMetrics().density;
            paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(1.5f*getResources().getDisplayMetrics().density);paint.setColor(getContext().getSharedPreferences("appearance",0).getInt("crossColor",0xff80f3df));
            float cx=getWidth()*.5f,cy=getHeight()*.5f;
            if(cross.getInt("shape",0)==0)c.drawCircle(cx,cy,radius,paint);
            else{c.save();c.translate(cx,cy);for(int arm=0;arm<4;arm++){c.drawLine(0,0,radius,0,paint);c.drawLine(radius,0,radius,-radius,paint);c.rotate(90);}c.restore();}
        }
        android.content.SharedPreferences aim=getContext().getSharedPreferences("aim",0);
        if(showFov&&!aim.getBoolean("hideFov",false)){
            paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(getResources().getDisplayMetrics().density);paint.setColor(getContext().getSharedPreferences("appearance",0).getInt("fovColor",0x9980f3df));
            float x=getWidth()*.5f,y=getHeight()*.5f;int shape=aim.getInt("fovShape",0);
            if(shape==1)c.drawRect(x-radius,y-radius,x+radius,y+radius,paint);
            else if(shape==2){android.graphics.Path path=new android.graphics.Path();path.moveTo(x,y-radius);path.lineTo(x+radius,y);path.lineTo(x,y+radius);path.lineTo(x-radius,y);path.close();c.drawPath(path,paint);}
            else c.drawCircle(x,y,radius,paint);
        }
        long now=SystemClock.uptimeMillis();
        if(view==null||projection==null||frame==null||now-matrixTime>1000||now-frameTime>1000)return;
        android.content.SharedPreferences settings=getContext().getSharedPreferences("visuals",0);
        boolean boxes=settings.getBoolean("boxes",true),names=settings.getBoolean("names",true),skeletons=settings.getBoolean("skeletons",true);
        float density=getResources().getDisplayMetrics().density;
        for(int at=7;at+6<frame.length;at+=7){try{
            float x=Float.parseFloat(frame[at]),y=Float.parseFloat(frame[at+1]),z=Float.parseFloat(frame[at+2]);
            if(!inEspRange(x,y,z))continue;
            float[] feet=screen(x,y,z),head=screen(x,y+1.8f,z);if(feet==null||head==null)continue;
            float height=feet[1]-head[1];if(height<3||height>getHeight()*2)continue;
            float width=height*.45f,left=head[0]-width/2,right=head[0]+width/2;
            if(right<0||left>getWidth()||feet[1]<0||head[1]>getHeight())continue;
            int color=frame[at+5].equals("1")?0xff80dd87:frame[at+4].equals("1")?0xffaaaaaa:0xff80f3df;
            if(boxes){paint.setStyle(Paint.Style.STROKE);paint.setColor(Color.BLACK);paint.setStrokeWidth(3*density);c.drawRect(left,head[1],right,feet[1],paint);
            paint.setColor(color);paint.setStrokeWidth(density);c.drawRect(left,head[1],right,feet[1],paint);}
            paint.setStyle(Paint.Style.FILL);paint.setTextSize(11*density);paint.setTextAlign(Paint.Align.CENTER);
            if(names){String label=name(frame[at+6]);paint.setColor(Color.BLACK);c.drawText(label,head[0]+1,head[1]-4*density+1,paint);paint.setColor(color);c.drawText(label,head[0],head[1]-4*density,paint);}
        }catch(NumberFormatException ignored){}}
        if(skeletons&&now-bonesTime<1000){
            paint.setColor(0xff80f3df);paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(1.2f*density);
            for(float[][] skeleton:bones)for(int[] link:LINKS){
                float[] a=skeleton[link[0]],b=skeleton[link[1]];if(a==null||b==null||!inEspRange(a[0],a[1],a[2])||!inEspRange(b[0],b[1],b[2]))continue;
                float[] aa=screen(a[0],a[1],a[2]),bb=screen(b[0],b[1],b[2]);if(aa==null||bb==null)continue;
                c.drawLine(aa[0],aa[1],bb[0],bb[1],paint);
            }
        }
        if(now-worldTime<2500){
            float ex=-(view[0]*view[12]+view[1]*view[13]+view[2]*view[14]),ey=-(view[4]*view[12]+view[5]*view[13]+view[6]*view[14]),ez=-(view[8]*view[12]+view[9]*view[13]+view[10]*view[14]);
            paint.setStyle(Paint.Style.FILL);paint.setTextSize(11*density);paint.setTextAlign(Paint.Align.CENTER);
            for(float[] object:world){int kind=(int)object[0];boolean ore=kind>=8&&kind<=11,vehicle=kind>=200,loot=kind>=100&&kind<200;
                if(!settings.getBoolean(vehicle?(kind==201?"helicopters":kind==202?"boats":"cars"):loot?"objects":ore?"ores":"animals",true))continue;
                float dx=object[1]-ex,dy=object[2]-ey,dz=object[3]-ez;float distance=(float)Math.sqrt(dx*dx+dy*dy+dz*dz);if(distance>300)continue;
                float[] point=screen(object[1],object[2],object[3]);if(point==null||point[0]<0||point[0]>getWidth()||point[1]<0||point[1]>getHeight())continue;
                String label=worldName(kind)+" ["+Math.round(distance)+" м]";paint.setColor(Color.BLACK);c.drawText(label,point[0]+1,point[1]+1,paint);
                paint.setColor(vehicle?0xffa9c6ff:loot?0xffffc580:ore?0xffe4df83:0xffa4e59a);c.drawText(label,point[0],point[1],paint);
            }
        }
        postInvalidateDelayed(100);
    }
}
