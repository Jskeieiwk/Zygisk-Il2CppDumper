package com.cloudcrack.oxide.external;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.LinearGradient;
import android.graphics.Path;
import android.graphics.Shader;
import android.graphics.drawable.GradientDrawable;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;

public final class OverlayService extends Service {
    static volatile boolean backendReady;
    static volatile String backendMessage="запуск";
    private WindowManager window;
    private TextView counter,status,details;
    private FrameLayout panel;
    
    private EspView esp;
    private boolean cameraReady;
    private Process backend;
    private final Handler handler=new Handler(Looper.getMainLooper());
    private boolean stopped;
    private int accent=0xff78dce8;
    private boolean snow=true;
    private int dp(int n){return (int)(n*getResources().getDisplayMetrics().density+.5f);}
    private GradientDrawable background(){
        GradientDrawable d=new GradientDrawable();d.setColor(0xe0202a36);d.setCornerRadius(dp(14));
        d.setStroke(dp(1),accent);return d;
    }
    private WindowManager.LayoutParams params(int width,int height,int gravity,int y){
        int type=Build.VERSION.SDK_INT>=26?WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY:WindowManager.LayoutParams.TYPE_PHONE;
        WindowManager.LayoutParams p=new WindowManager.LayoutParams(width,height,type,
            WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE|WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL,
            PixelFormat.TRANSLUCENT);
        p.gravity=gravity;p.y=y;return p;
    }
    @Override public void onCreate(){
        super.onCreate();
        DiagnosticLog.install(this);
        DiagnosticLog.write(this,"SERVICE create");
        healX=getSharedPreferences("farm",MODE_PRIVATE).getFloat("healX",-1);healY=getSharedPreferences("farm",MODE_PRIVATE).getFloat("healY",-1);healThreshold=getSharedPreferences("aim",MODE_PRIVATE).getInt("healThreshold",50);
        adsOnly=getSharedPreferences("aim",MODE_PRIVATE).getBoolean("adsOnly",false);
        english=getSharedPreferences("appearance",MODE_PRIVATE).getBoolean("english",false);
        farmStopEnemy=getSharedPreferences("farm",MODE_PRIVATE).getBoolean("stopEnemy",false);
        fireX=getSharedPreferences("farm",MODE_PRIVATE).getFloat("fireX",-1);fireY=getSharedPreferences("farm",MODE_PRIVATE).getFloat("fireY",-1);runX=getSharedPreferences("farm",MODE_PRIVATE).getFloat("runX",-1);runY=getSharedPreferences("farm",MODE_PRIVATE).getFloat("runY",-1);
        freeSpeed=Math.max(3,Math.min(20,getSharedPreferences("aim",MODE_PRIVATE).getInt("freeSpeed",6)));
        aimFov=getSharedPreferences("aim",MODE_PRIVATE).getInt("fov",100);aimSmooth=getSharedPreferences("aim",MODE_PRIVATE).getInt("smooth",3);
        accent=getSharedPreferences("appearance",MODE_PRIVATE).getInt("accent",accent);
        snow=getSharedPreferences("appearance",MODE_PRIVATE).getBoolean("snow",true);
        backendReady=false;backendMessage="запрос root";
        NotificationManager notifications=(NotificationManager)getSystemService(NOTIFICATION_SERVICE);
        if(Build.VERSION.SDK_INT>=26)notifications.createNotificationChannel(new NotificationChannel("oxide_ext","Oxide External",NotificationManager.IMPORTANCE_LOW));
        Notification.Builder builder=Build.VERSION.SDK_INT>=26?new Notification.Builder(this,"oxide_ext"):new Notification.Builder(this);
        startForeground(12034,builder.setContentTitle("Oxide External").setContentText("Проверка игрового процесса")
            .setSmallIcon(android.R.drawable.ic_menu_compass).build());
        window=(WindowManager)getSystemService(WINDOW_SERVICE);
        esp=new EspView(this);
        WindowManager.LayoutParams espParams=params(-1,-1,Gravity.TOP|Gravity.LEFT,0);
        espParams.flags|=WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE|WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN;
        window.addView(esp,espParams);
        counter=new TextView(this);counter.setText("Oxide external: запрос root");counter.setTextColor(Color.WHITE);
        counter.setTextSize(12);counter.setGravity(Gravity.CENTER);counter.setPadding(dp(12),dp(7),dp(12),dp(7));
        counter.setBackground(background());counter.setOnClickListener(v->toggle());
        window.addView(counter,params(-2,-2,Gravity.TOP|Gravity.CENTER_HORIZONTAL,dp(24)));
        handler.post(aimHeartbeat);
        launchBackend();
    }
    private volatile boolean healEnabled;
    private String matrixDiagnostic="MATRIX unseen";
    private String frameDiagnostic="FRAME unseen";
    private String worldDiagnostic="WORLD unseen";
    private boolean bindingSlot;
    private float healX=-1,healY=-1;
    private int healThreshold=50;
    private final java.util.LinkedHashMap<String,String> sceneDiagnostics=new java.util.LinkedHashMap<>();
    private void copySceneDiagnostics(){
        StringBuilder report=new StringBuilder("Oxide external v0.30 diagnostics\n").append(backendMessage).append('\n')
            .append(matrixDiagnostic).append('\n').append(frameDiagnostic).append('\n').append(worldDiagnostic).append('\n');
        for(String line:sceneDiagnostics.values())report.append(line).append('\n');
        android.content.ClipboardManager clipboard=(android.content.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
        clipboard.setPrimaryClip(android.content.ClipData.newPlainText("Oxide scene diagnostics",report.toString()));
        android.widget.Toast.makeText(this,english?"Diagnostics copied":"Диагностика скопирована",0).show();
    }
    private boolean adsOnly;
    private boolean english;
    private String colorKey="accent";
    private String translate(String value){
        if(!english)return value;
        String[][] words={{"Скопировать диагностику","Copy diagnostics"},{"Машины","Cars"},{"Вертолёты","Helicopters"},{"Лодки","Boats"},{"Транспорт","Vehicles"},{"Скрыть FOV","Hide FOV"},{"Цвет FOV","FOV color"},{"Форма FOV","FOV shape"},{"Квадрат","Square"},{"Ромб","Diamond"},{"В прицеле","Only while aiming"},{"Нажми на слот лечения","Tap the healing slot"},{"Нажми на кнопку огня","Tap the fire button"},{"Нажми на центр джойстика","Tap the joystick center"},{"Работает при закрытом меню. Плавное наведение в области центра экрана. Команда и спящие исключены. Баллистика включена для оружия с прочитанным профилем. ","Active with the menu closed. Smooth aiming near screen center. Teammates and sleepers excluded. Ballistics requires a readable weapon profile. "},{"Остановиться когда враг рядом","Stop when enemy is nearby"},{"Радиус FOV (px)","FOV radius (px)"},{"Скорость (м/с)","Speed (m/s)"},{"Остановить external","Stop external"},{"Объекты и ящики","Objects and crates"},{"Снег в меню","Menu snow"},{"Руда и деревья","Ores and trees"},{"Задать огонь","Set fire button"},{"Задать бег","Set joystick"},{"Цвет меню","Menu color"},{"Камера прочитана","Camera ready"},{"Ожидание камеры","Waiting for camera"},{"Оформление","Appearance"},{"Аимбот","Aimbot"},{"Визуалы","Visuals"},{"Прочее","Misc"},{"Настройки","Settings"},{"Наведение","Aim enabled"},{"Игроки","Players"},{"Рамки","Boxes"},{"Имена","Names"},{"Скелеты","Skeletons"},{"Животные","Animals"},{"Автофарм","Auto farm"},{"Камера","Camera"},{"Резкость","Sharpness"},{"Мир","World"},{"Прицел","Crosshair"},{"Круг","Circle"},{"Свастика","Swastika"},{"Размер","Size"},{"Цвет прицела","Crosshair color"},{"Автохил","Auto heal"},{"Задать слот","Set slot"},{"Порог HP (%)","HP threshold (%)"},{"Английский язык","English language"},{"Применить","Apply"},{"Отмена","Cancel"}};
        for(String[] pair:words)if(value.startsWith(pair[0]))return pair[1]+value.substring(pair[0].length());return value;
    }
    private volatile boolean farmEnabled;
    private boolean farmStopEnemy;
    private float fireX=-1,fireY=-1,runX=-1,runY=-1;
    private View bindingOverlay;
    private final java.util.concurrent.atomic.AtomicBoolean farmTouchBusy=new java.util.concurrent.atomic.AtomicBoolean();
    private void bindFarm(boolean fire){
        farmEnabled=false;writeAimState();if(panel!=null)toggle();
        TextView capture=text(bindingSlot?"Нажми на слот лечения":fire?"Нажми на кнопку огня":"Нажми на центр джойстика",18,Color.WHITE);
        capture.setGravity(Gravity.TOP|Gravity.CENTER_HORIZONTAL);capture.setPadding(0,dp(30),0,0);capture.setBackgroundColor(0x22000000);
        bindingOverlay=capture;WindowManager.LayoutParams layout=params(-1,-1,Gravity.TOP|Gravity.LEFT,0);layout.flags|=WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN;window.addView(capture,layout);
        capture.setOnTouchListener((v,event)->{
            if(event.getActionMasked()==MotionEvent.ACTION_UP){
                float x=Math.max(0,Math.min(.999f,event.getRawX()/getResources().getDisplayMetrics().widthPixels)),y=Math.max(0,Math.min(.999f,event.getRawY()/getResources().getDisplayMetrics().heightPixels));
                if(bindingSlot){healX=x;healY=y;getSharedPreferences("farm",MODE_PRIVATE).edit().putFloat("healX",x).putFloat("healY",y).apply();bindingSlot=false;}
                else{if(fire){fireX=x;fireY=y;}else{runX=x;runY=y;}

                getSharedPreferences("farm",MODE_PRIVATE).edit().putFloat(fire?"fireX":"runX",x).putFloat(fire?"fireY":"runY",y).apply();}
                window.removeView(capture);bindingOverlay=null;page=2;toggle();
            }
            return true;
        });
    }
    private void farmTouch(String action){
        boolean healing=action.equals("HEAL");
        if((healing?!healEnabled:!farmEnabled)||panel!=null||bindingOverlay!=null||freecamEnabled||stopped||!farmTouchBusy.compareAndSet(false,true))return;
        int width=getResources().getDisplayMetrics().widthPixels,height=getResources().getDisplayMetrics().heightPixels;
        int x=Math.round((healing?healX:action.equals("MOVE")?runX:fireX)*width),y=Math.round((healing?healY:action.equals("MOVE")?runY:fireY)*height);
        int endY=Math.max(0,y-dp(60));
        new Thread(()->{try{
            Process check=new ProcessBuilder("su","-c","dumpsys activity activities").redirectErrorStream(true).start();boolean game=false;
            try(BufferedReader in=new BufferedReader(new InputStreamReader(check.getInputStream()))){String line;while((line=in.readLine())!=null){if((line.contains("mResumedActivity")||line.contains("topResumedActivity"))&&line.contains("com.catsbit.oxidesurvivalisland"))game=true;}}
            check.waitFor();
            if(game&&(healing?healEnabled:farmEnabled)&&!stopped){String command=action.equals("MOVE")?"input touchscreen swipe "+x+" "+y+" "+x+" "+endY+" 500":"input touchscreen tap "+x+" "+y;
                if(healing)command="input touchscreen tap "+x+" "+y+"; sleep 0.15; input touchscreen tap "+x+" "+y;
                Process touch=new ProcessBuilder("su","-c",command).redirectErrorStream(true).start();try(BufferedReader in=new BufferedReader(new InputStreamReader(touch.getInputStream()))){while(in.readLine()!=null){}}touch.waitFor();}
        }catch(Exception error){handler.post(()->show("Автофарм: "+error.getMessage()));}finally{farmTouchBusy.set(false);}},"oxide-farm-touch").start();
    }
    private boolean aimEnabled,freecamEnabled;
    private LinearLayout freecamPad;
    private float freeX,freeY,freeZ,freeTurn;
    private int aimFov=100,aimSmooth=3,freeSpeed=6;
    private void writeAimState(){
        if(esp!=null)esp.aimSettings(aimEnabled,aimFov);
        try(java.io.FileOutputStream out=new java.io.FileOutputStream(new java.io.File(getFilesDir(),"aim.cfg"))){
            String value=(aimEnabled&&!freecamEnabled&&panel==null&&!stopped?"1":"0")+" "+(System.currentTimeMillis()/1000)+" "+aimFov+" "+aimSmooth+" "+(esp!=null&&esp.getWidth()>0?esp.getWidth():getResources().getDisplayMetrics().widthPixels)+" "+(esp!=null&&esp.getHeight()>0?esp.getHeight():getResources().getDisplayMetrics().heightPixels)+" "+(freecamEnabled&&!stopped?1:0)+" "+freeX+" "+freeY+" "+freeZ+" "+freeTurn+" "+freeSpeed+" "+(farmEnabled&&panel==null&&bindingOverlay==null&&!freecamEnabled&&!stopped?1:0)+" "+(farmStopEnemy?1:0)+" "+(healEnabled&&panel==null&&!stopped?1:0)+" "+healThreshold+" "+(adsOnly?1:0)+" "+getSharedPreferences("aim",MODE_PRIVATE).getInt("fovShape",0)+"\n";
            out.write(value.getBytes(StandardCharsets.UTF_8));
        }catch(java.io.IOException ignored){}
    }
    private final Runnable aimHeartbeat=new Runnable(){public void run(){if(stopped)return;writeAimState();handler.postDelayed(this,500);}};
    private void freecamButton(LinearLayout row,String label,int axis,float direction){
        TextView button=text(label,13,Color.WHITE);button.setGravity(Gravity.CENTER);button.setBackground(card(0xd0182633,accent,8));
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(0,dp(38),1);lp.setMargins(dp(2),dp(2),dp(2),dp(2));row.addView(button,lp);
        button.setOnTouchListener((v,event)->{
            int action=event.getActionMasked();float value;
            if(action==MotionEvent.ACTION_DOWN)value=direction;else if(action==MotionEvent.ACTION_UP||action==MotionEvent.ACTION_CANCEL)value=0;else return true;
            if(axis==0)freeX=value;else if(axis==1)freeY=value;else if(axis==2)freeZ=value;else freeTurn=value;
            writeAimState();return true;
        });
    }
    private void setFreecam(boolean active){
        freecamEnabled=active;freeX=freeY=freeZ=freeTurn=0;
        if(freecamPad!=null){window.removeView(freecamPad);freecamPad=null;}
        if(active){
            freecamPad=new LinearLayout(this);freecamPad.setOrientation(LinearLayout.VERTICAL);
            LinearLayout first=new LinearLayout(this),second=new LinearLayout(this);freecamPad.addView(first);freecamPad.addView(second);
            freecamButton(first,"Влево",0,-1);freecamButton(first,"Вперёд",2,1);freecamButton(first,"Вправо",0,1);freecamButton(first,"Вверх",1,1);
            freecamButton(second,"↶",3,-1);freecamButton(second,"Назад",2,-1);freecamButton(second,"↷",3,1);freecamButton(second,"Вниз",1,-1);
            TextView off=text("Freecam · выключить",12,accent);off.setGravity(Gravity.CENTER);off.setBackground(background());freecamPad.addView(off,new LinearLayout.LayoutParams(-1,dp(28)));off.setOnClickListener(v->{setFreecam(false);if(panel!=null)buildMenu();});
            window.addView(freecamPad,params(dp(300),-2,Gravity.BOTTOM|Gravity.LEFT,dp(12)));
        }
        writeAimState();
    }
    private int page=1;
    private LinearLayout menuBody;
    private TextView text(String value,int size,int color){TextView v=new TextView(this);v.setText(translate(value));v.setTextSize(size);v.setTextColor(color);v.setGravity(Gravity.CENTER_VERTICAL);return v;}
    private GradientDrawable card(int fill,int stroke,int radius){GradientDrawable d=new GradientDrawable();d.setColor(fill);d.setCornerRadius(dp(radius));d.setStroke(dp(1),stroke);return d;}
    private void toggle(){
        if(panel!=null){window.removeView(panel);panel=null;status=null;details=null;writeAimState();return;}
        panel=new FrameLayout(this);writeAimState();
        int width=Math.min(dp(440),getResources().getDisplayMetrics().widthPixels-dp(20));
        int height=Math.min(dp(270),getResources().getDisplayMetrics().heightPixels-dp(36));
        buildMenu();window.addView(panel,params(width,height,Gravity.CENTER,0));
    }
    private void action(LinearLayout out,String label,Runnable run){
        TextView v=text(label,13,Color.WHITE);v.setPadding(dp(10),dp(8),dp(6),dp(8));v.setBackground(card(0x452b4551,0x6578aeb9,9));
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.bottomMargin=dp(6);out.addView(v,lp);v.setOnClickListener(x->run.run());
    }
    private void section(LinearLayout out,String label){TextView v=text(label,14,accent);v.setTypeface(null,1);v.setPadding(dp(2),dp(3),0,dp(7));out.addView(v);}
    private void visualToggle(String label,String key){
        boolean value=getSharedPreferences("visuals",MODE_PRIVATE).getBoolean(key,!key.equals("crosshair"));
        action(menuBody,label+(value?"   ✓":"   ○"),()->{getSharedPreferences("visuals",MODE_PRIVATE).edit().putBoolean(key,!value).apply();esp.invalidate();buildMenu();});
    }
    private void aimSlider(String label,String key,int min,int max,int initial){
        TextView value=text(label+": "+initial,13,Color.WHITE);menuBody.addView(value);
        android.widget.SeekBar slider=new android.widget.SeekBar(this);slider.setMax(max-min);slider.setProgress(initial-min);menuBody.addView(slider,new LinearLayout.LayoutParams(-1,dp(36)));
        slider.setOnSeekBarChangeListener(new android.widget.SeekBar.OnSeekBarChangeListener(){
            public void onProgressChanged(android.widget.SeekBar bar,int progress,boolean user){if(!user)return;int number=min+progress;value.setText(translate(label+": "+number));if(key.equals("fov"))aimFov=number;else if(key.equals("freeSpeed"))freeSpeed=number;else if(key.equals("smooth"))aimSmooth=number;else if(key.equals("healThreshold"))healThreshold=number;getSharedPreferences("aim",MODE_PRIVATE).edit().putInt(key,number).apply();writeAimState();}
            public void onStartTrackingTouch(android.widget.SeekBar bar){}public void onStopTrackingTouch(android.widget.SeekBar bar){}
        });
    }
    private void buildMenu(){
        status=null;details=null;panel.removeAllViews();
        LinearLayout body=new LinearLayout(this);body.setOrientation(LinearLayout.VERTICAL);body.setPadding(dp(13),dp(10),dp(13),dp(10));
        body.setBackground(card(0xe0182633,accent,17));panel.addView(body,new FrameLayout.LayoutParams(-1,-1));
        LinearLayout header=new LinearLayout(this);header.setGravity(Gravity.CENTER_VERTICAL);body.addView(header,new LinearLayout.LayoutParams(-1,dp(35)));
        TextView title=text("Cloud Space  ·  Oxide 12034",15,Color.WHITE);title.setTypeface(null,1);header.addView(title,new LinearLayout.LayoutParams(0,-1,1));
        TextView close=text("✕",22,accent);close.setGravity(Gravity.CENTER);header.addView(close,new LinearLayout.LayoutParams(dp(34),-1));close.setOnClickListener(v->toggle());
        View divider=new View(this);divider.setBackgroundColor(accent);body.addView(divider,new LinearLayout.LayoutParams(-1,dp(1)));
        LinearLayout row=new LinearLayout(this);body.addView(row,new LinearLayout.LayoutParams(-1,0,1));
        LinearLayout nav=new LinearLayout(this);nav.setOrientation(LinearLayout.VERTICAL);nav.setPadding(0,dp(8),dp(10),0);row.addView(nav,new LinearLayout.LayoutParams(dp(104),-1));
        ScrollView scroll=new ScrollView(this);scroll.setFillViewport(true);row.addView(scroll,new LinearLayout.LayoutParams(0,-1,1));
        menuBody=new LinearLayout(this);menuBody.setOrientation(LinearLayout.VERTICAL);menuBody.setPadding(dp(8),dp(8),dp(3),dp(8));menuBody.setBackground(card(0x492d4350,0x6890c9d2,12));scroll.addView(menuBody);
        String[] names={"Аимбот","Визуалы","Прочее","Настройки"};
        for(int i=0;i<names.length;i++){final int id=i;TextView tab=text(names[i],13,i==page?accent:Color.WHITE);tab.setPadding(dp(8),dp(8),0,dp(8));tab.setBackground(card(i==page?0x5036727e:0x1f192c37,i==page?accent:0x0025303d,9));LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.bottomMargin=dp(5);nav.addView(tab,lp);tab.setOnClickListener(v->{page=id;buildMenu();});}
        if(page==0){section(menuBody,"Аимбот");action(menuBody,aimEnabled?"Наведение   ✓":"Наведение   ○",()->{aimEnabled=!aimEnabled;writeAimState();buildMenu();});action(menuBody,"В прицеле"+(adsOnly?"   ✓":"   ○"),()->{adsOnly=!adsOnly;getSharedPreferences("aim",MODE_PRIVATE).edit().putBoolean("adsOnly",adsOnly).apply();writeAimState();buildMenu();});aimSlider("Радиус FOV (px)","fov",10,300,aimFov);action(menuBody,"Скрыть FOV"+(getSharedPreferences("aim",MODE_PRIVATE).getBoolean("hideFov",false)?"   ✓":"   ○"),()->{boolean hide=getSharedPreferences("aim",MODE_PRIVATE).getBoolean("hideFov",false);getSharedPreferences("aim",MODE_PRIVATE).edit().putBoolean("hideFov",!hide).apply();esp.invalidate();buildMenu();});int fovShape=getSharedPreferences("aim",MODE_PRIVATE).getInt("fovShape",0);action(menuBody,translate("Форма FOV")+": "+translate(new String[]{"Круг","Квадрат","Ромб"}[fovShape]),()->{getSharedPreferences("aim",MODE_PRIVATE).edit().putInt("fovShape",(fovShape+1)%3).apply();writeAimState();esp.invalidate();buildMenu();});action(menuBody,"Цвет FOV",()->{colorKey="fovColor";openColorPicker();});aimSlider("Резкость","smooth",0,10,aimSmooth);TextView note=text("Работает при закрытом меню. Плавное наведение в области центра экрана. Команда и спящие исключены. Баллистика включена для оружия с прочитанным профилем. ",12,Color.WHITE);menuBody.addView(note);}
        else if(page==1){section(menuBody,"Визуалы");status=text(cameraReady?"Камера прочитана":"Ожидание камеры",12,accent);menuBody.addView(status);details=text(counter.getText().toString(),12,Color.WHITE);menuBody.addView(details);section(menuBody,"Игроки");visualToggle("Рамки","boxes");visualToggle("Имена","names");visualToggle("Скелеты","skeletons");section(menuBody,"Прицел");visualToggle("Прицел","crosshair");action(menuBody,getSharedPreferences("visuals",MODE_PRIVATE).getInt("shape",0)==0?"Круг":"Свастика",()->{int shape=1-getSharedPreferences("visuals",MODE_PRIVATE).getInt("shape",0);getSharedPreferences("visuals",MODE_PRIVATE).edit().putInt("shape",shape).apply();buildMenu();});aimSlider("Размер","crossSize",2,40,getSharedPreferences("aim",MODE_PRIVATE).getInt("crossSize",8));action(menuBody,"Цвет прицела",()->{colorKey="crossColor";openColorPicker();});section(menuBody,"Мир");visualToggle("Руда и деревья","ores");visualToggle("Объекты и ящики","objects");visualToggle("Животные","animals");section(menuBody,"Транспорт");visualToggle("Машины","cars");visualToggle("Вертолёты","helicopters");visualToggle("Лодки","boats");}
        else if(page==2){section(menuBody,"Камера");action(menuBody,freecamEnabled?"Freecam   ✓":"Freecam   ○",()->{setFreecam(!freecamEnabled);buildMenu();});aimSlider("Скорость (м/с)","freeSpeed",3,20,freeSpeed);section(menuBody,"Автофарм");action(menuBody,farmEnabled?"Автофарм   ✓":"Автофарм   ○",()->{if(fireX<0||fireY<0||runX<0||runY<0){android.widget.Toast.makeText(this,"Сначала задай огонь и бег",0).show();return;}farmEnabled=!farmEnabled;writeAimState();buildMenu();});action(menuBody,"Остановиться когда враг рядом"+(farmStopEnemy?"   ✓":"   ○"),()->{farmStopEnemy=!farmStopEnemy;getSharedPreferences("farm",MODE_PRIVATE).edit().putBoolean("stopEnemy",farmStopEnemy).apply();writeAimState();buildMenu();});action(menuBody,fireX>=0?"Задать огонь   ✓":"Задать огонь",()->bindFarm(true));action(menuBody,runX>=0?"Задать бег   ✓":"Задать бег",()->bindFarm(false));section(menuBody,"Автохил");action(menuBody,"Автохил"+(healEnabled?"   ✓":"   ○"),()->{if(healX<0){android.widget.Toast.makeText(this,"Сначала задай слот",0).show();return;}healEnabled=!healEnabled;writeAimState();buildMenu();});action(menuBody,"Задать слот"+(healX>=0?"   ✓":""),()->{healEnabled=false;bindingSlot=true;bindFarm(true);});aimSlider("Порог HP (%)","healThreshold",1,99,healThreshold);section(menuBody,"External");status=text(backendMessage,13,accent);menuBody.addView(status);action(menuBody,"Остановить external",()->stopSelf());}
        else{section(menuBody,"Оформление");action(menuBody,"Скопировать диагностику",()->copySceneDiagnostics());action(menuBody,"Цвет меню",()->{colorKey="accent";openColorPicker();});action(menuBody,"Английский язык"+(english?"   ✓":"   ○"),()->{english=!english;getSharedPreferences("appearance",MODE_PRIVATE).edit().putBoolean("english",english).apply();buildMenu();});action(menuBody,snow?"Снег в меню   ✓":"Снег в меню   ○",()->{snow=!snow;getSharedPreferences("appearance",MODE_PRIVATE).edit().putBoolean("snow",snow).apply();buildMenu();});}
        if(snow)panel.addView(new SnowLayer(),new FrameLayout.LayoutParams(-1,-1));
    }
    private void openColorPicker(){
        if(panel==null)return;
        LinearLayout card=new LinearLayout(this);card.setOrientation(LinearLayout.VERTICAL);card.setPadding(dp(12),dp(8),dp(12),dp(8));
        card.setBackground(background());
        TextView title=new TextView(this);title.setText(translate(colorKey.equals("accent")?"Цвет меню":colorKey.equals("fovColor")?"Цвет FOV":"Цвет прицела"));title.setTextColor(Color.WHITE);title.setTextSize(16);card.addView(title);
        int selectedColor=getSharedPreferences("appearance",MODE_PRIVATE).getInt(colorKey,accent);
        View preview=new View(this);preview.setBackgroundColor(selectedColor);card.addView(preview,new LinearLayout.LayoutParams(-1,dp(16)));
        ColorSurface picker=new ColorSurface(selectedColor,preview);card.addView(picker,new LinearLayout.LayoutParams(-1,0,1));
        LinearLayout actions=new LinearLayout(this);card.addView(actions);
        Button cancel=new Button(this);cancel.setText(translate("Отмена"));cancel.setOnClickListener(v->panel.removeView(card));actions.addView(cancel,new LinearLayout.LayoutParams(0,-2,1));
        Button apply=new Button(this);apply.setText(translate("Применить"));apply.setOnClickListener(v->{
            int chosen=picker.selected();getSharedPreferences("appearance",MODE_PRIVATE).edit().putInt(colorKey,chosen).apply();if(colorKey.equals("accent"))accent=chosen;
            toggle();toggle();counter.setBackground(background());
        });actions.addView(apply,new LinearLayout.LayoutParams(0,-2,1));
        panel.addView(card,new FrameLayout.LayoutParams(-1,-1));
    }
    private void show(String line){
        if(line.startsWith("RESOLVE ")){sceneDiagnostics.put("RESOLVE",line);return;}
        if(line.startsWith("AIM ")){sceneDiagnostics.put("AIM",line);return;}
        if(line.equals("HEAL")){farmTouch("HEAL");return;}
        if(line.equals("FARM STOP_ENEMY")){
            if(farmEnabled){farmEnabled=false;writeAimState();counter.setText("Автофарм остановлен: враг в 50 м");android.widget.Toast.makeText(this,"Автофарм остановлен: враг в радиусе 50 м",1).show();if(panel!=null)buildMenu();}return;
        }
        if(line.startsWith("FARM ")){farmTouch(line.substring(5));return;}
        if(line.startsWith("MATRIX ")){cameraReady=line.startsWith("MATRIX 1 ");matrixDiagnostic=cameraReady?"MATRIX valid":"MATRIX unavailable";if(esp!=null)esp.matrix(line);return;}
        if(line.startsWith("WORLD ")){String[] values=line.split(" ",3);worldDiagnostic=values.length>1?"WORLD objects="+values[1]:"WORLD malformed";if(esp!=null)esp.world(line);return;}
        if(line.startsWith("BONES ")){if(esp!=null)esp.bones(line);return;}
        if(line.startsWith("CAMERA "))return;
        if(line.startsWith("FRAME ")){
            String[] parts=line.split(" ");
            if(parts.length>=7){
                frameDiagnostic="FRAME players="+parts[2]+" local="+parts[3]+" overlay="+(esp!=null?esp.getWidth()+"x"+esp.getHeight():"unavailable");
                if(esp!=null)esp.frame(parts);
                backendReady=true;backendMessage="память прочитана";
                counter.setText("Игроки: "+parts[2]+" · external");
                if(status!=null)status.setText("PID "+parts[1]+" · "+(cameraReady?"камера прочитана · ESP":"ожидание камеры"));
                if(details!=null){
                    StringBuilder info=new StringBuilder("Объекты: ").append(Math.max(0,(parts.length-7)/7));
                    for(int i=0;i<Math.min(5,(parts.length-7)/7);i++){
                        int at=7+i*7;
                        String name=decodeName(parts[at+6]);
                        if(name.isEmpty())name="Игрок "+(i+1);
                        info.append('\n').append(name);
                        if(parts[at+4].equals("1"))info.append(" · спит");
                        if(parts[at+5].equals("1"))info.append(" · команда");
                    }
                    details.setText(info.toString());
                }
                
            }
        } else if(line.startsWith("STATUS ")){
            String code=line.equals("STATUS SEARCHING_PLAYERS")?"Ожидание игроков":line.equals("STATUS WAITING_WORLD")?"Ожидание мира":line.substring(7).replace('_',' ');
            backendMessage=code;
            if(line.equals("STATUS WAITING_GAME")||line.equals("STATUS WRONG_BUILD")||
               line.equals("STATUS SEARCHING_PLAYERS")||line.equals("STATUS WAITING_WORLD"))backendReady=true;
            counter.setText("Oxide: "+code);
            if(status!=null)status.setText(code);
        } else {
            backendMessage=line;
            counter.setText(line.length()>46?line.substring(0,46):line);
            if(status!=null)status.setText(line);
        }
    }
    private String decodeName(String hex){
        if(hex.equals("-")||hex.length()%2!=0||hex.length()>384)return "";
        byte[] bytes=new byte[hex.length()/2];
        for(int i=0;i<bytes.length;i++){
            int upper=Character.digit(hex.charAt(i*2),16),lower=Character.digit(hex.charAt(i*2+1),16);
            if(upper<0||lower<0)return "";
            bytes[i]=(byte)((upper<<4)|lower);
        }
        return new String(bytes,StandardCharsets.UTF_8);
    }
    private void launchBackend(){
        new Thread(()->{
            String binary=getApplicationInfo().nativeLibraryDir+"/libexternal.so";
            for(int variant=0;variant<2&&!stopped;variant++){
                try {
                    String command="exec "+binary+" --config "+getFilesDir().getAbsolutePath()+"/aim.cfg";
                    ProcessBuilder builder=variant==0?new ProcessBuilder("su","-c",command):new ProcessBuilder("su","0","sh","-c",command);
                    backend=builder.redirectErrorStream(true).start();
                    backend.getOutputStream().close();
                    try(BufferedReader in=new BufferedReader(new InputStreamReader(backend.getInputStream()))){
                        String line;while((line=in.readLine())!=null&&!stopped){
                            if(line.startsWith("STATUS ")||line.startsWith("RESOLVE ")||line.startsWith("AIM ")||line.startsWith("CAMERA "))DiagnosticLog.write(this,line);
                            final String message=line;handler.post(()->show(message));
                        }
                    }
                    int result=backend.waitFor();
                    DiagnosticLog.write(this,"BACKEND exit="+result+" variant="+variant);
                    if(result==0||stopped)return;
                }catch(Exception error){DiagnosticLog.write(this,"BACKEND exception="+error);final String message="root: "+error.getMessage();handler.post(()->show(message));}
            }
            handler.post(()->show("STATUS ROOT_OR_BACKEND_FAILED"));
        },"oxide-external-reader").start();
    }
    @Override public int onStartCommand(Intent intent,int flags,int id){return START_STICKY;}
    @Override public IBinder onBind(Intent intent){return null;}
    @Override public void onDestroy(){
        DiagnosticLog.write(this,"SERVICE destroy");
        farmEnabled=false;if(bindingOverlay!=null){window.removeView(bindingOverlay);bindingOverlay=null;}setFreecam(false);stopped=true;writeAimState();handler.removeCallbacks(aimHeartbeat);
        backendReady=false;
        final Process finishing=backend;
        if(finishing!=null)new Thread(()->{try{Thread.sleep(3000);}catch(InterruptedException ignored){}finishing.destroy();},"oxide-camera-restore").start();
        if(panel!=null)window.removeView(panel);
        if(counter!=null)window.removeView(counter);
        if(esp!=null)window.removeView(esp);
        super.onDestroy();
    }
    private final class ColorSurface extends View {
        private final Paint paint=new Paint(3);
        private final float[] hsv=new float[3];
        private final View preview;
        private int drag;
        private float left,top,right,bottom,hueLeft,hueRight;
        ColorSurface(int color,View preview){super(OverlayService.this);this.preview=preview;Color.colorToHSV(color,hsv);setClickable(true);}
        int selected(){return Color.HSVToColor(hsv);}
        @Override protected void onDraw(Canvas canvas){
            left=dp(8);top=dp(8);right=Math.max(left+1,getWidth()-dp(54));bottom=Math.max(top+1,getHeight()-dp(8));
            hueLeft=right+dp(18);hueRight=getWidth()-dp(8);
            paint.setStyle(Paint.Style.FILL);
            int hue=Color.HSVToColor(new float[]{hsv[0],1,1});
            paint.setShader(new LinearGradient(left,0,right,0,Color.WHITE,hue,Shader.TileMode.CLAMP));canvas.drawRect(left,top,right,bottom,paint);
            paint.setShader(new LinearGradient(0,top,0,bottom,0x00000000,Color.BLACK,Shader.TileMode.CLAMP));canvas.drawRect(left,top,right,bottom,paint);
            paint.setShader(new LinearGradient(0,top,0,bottom,new int[]{Color.RED,Color.YELLOW,Color.GREEN,Color.CYAN,Color.BLUE,Color.MAGENTA,Color.RED},null,Shader.TileMode.CLAMP));
            canvas.drawRect(hueLeft,top,hueRight,bottom,paint);paint.setShader(null);
            paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(dp(3));paint.setColor(Color.BLACK);
            float x=left+hsv[1]*(right-left),y=bottom-hsv[2]*(bottom-top);canvas.drawCircle(x,y,dp(5),paint);
            paint.setStrokeWidth(dp(2));paint.setColor(Color.WHITE);canvas.drawCircle(x,y,dp(5),paint);
            float hy=top+hsv[0]/360f*(bottom-top);canvas.drawRect(hueLeft-dp(3),hy-dp(3),hueRight+dp(3),hy+dp(3),paint);
        }
        @Override public boolean onTouchEvent(MotionEvent event){
            int action=event.getActionMasked();
            if(action==MotionEvent.ACTION_DOWN){drag=event.getX()>right+dp(8)?2:1;getParent().requestDisallowInterceptTouchEvent(true);}
            if(action==MotionEvent.ACTION_DOWN||action==MotionEvent.ACTION_MOVE||action==MotionEvent.ACTION_UP){
                if(drag==2)hsv[0]=Math.max(0,Math.min(359.99f,(event.getY()-top)/Math.max(1,bottom-top)*360));
                else if(drag==1){hsv[1]=Math.max(0,Math.min(1,(event.getX()-left)/Math.max(1,right-left)));hsv[2]=1-Math.max(0,Math.min(1,(event.getY()-top)/Math.max(1,bottom-top)));}
                preview.setBackgroundColor(selected());invalidate();
            }
            if(action==MotionEvent.ACTION_UP||action==MotionEvent.ACTION_CANCEL){drag=0;getParent().requestDisallowInterceptTouchEvent(false);if(action==MotionEvent.ACTION_UP)performClick();}
            return true;
        }
        @Override public boolean performClick(){super.performClick();return true;}
    }
    private final class SnowLayer extends View {
        private final Paint paint=new Paint(3);
        private final Path clip=new Path();
        private final Path[] flakes=new Path[4];
        private final float density=getResources().getDisplayMetrics().density;
        SnowLayer(){super(OverlayService.this);setClickable(false);paint.setStrokeCap(Paint.Cap.ROUND);
            for(int size=0;size<flakes.length;size++){
                Path shape=new Path();float radius=3+size;
                for(int arm=0;arm<6;arm++){
                    double angle=arm*Math.PI/3;
                    float endX=(float)(Math.sin(angle)*radius),endY=(float)(-Math.cos(angle)*radius);
                    shape.moveTo(0,0);shape.lineTo(endX,endY);
                    for(int branch=1;branch<=2;branch++){
                        float at=radius*(.32f+branch*.21f),twig=radius*.24f;
                        float baseX=(float)(Math.sin(angle)*at),baseY=(float)(-Math.cos(angle)*at);
                        for(int side=-1;side<=1;side+=2){
                            double a=angle+side*Math.PI/3;
                            shape.moveTo(baseX,baseY);
                            shape.lineTo(baseX+(float)(Math.sin(a)*twig),baseY-(float)(Math.cos(a)*twig));
                        }
                    }
                }
                flakes[size]=shape;
            }
        }
        @Override protected void onDraw(Canvas canvas){
            int width=getWidth(),height=getHeight();if(width<1||height<1)return;
            float time=(SystemClock.uptimeMillis()%3600000)/1000f;
            canvas.save();clip.reset();clip.addRoundRect(0,0,width,height,17*density,17*density,Path.Direction.CW);canvas.clipPath(clip);
            paint.setStyle(Paint.Style.STROKE);paint.setColor(0xaddcebf8);paint.setStrokeWidth(Math.max(1,.65f*density));
            for(int i=0;i<32;i++){
                float size=(3+i%4)*density;
                float x=(i*137*density+(float)Math.sin(time*.55+i)*9*density)%width;
                float y=(i*73*density+time*(8+i%5*3)*density)%(height+size*2)-size;
                canvas.save();canvas.translate(x,y);canvas.rotate(time*(i%2==0?8:-7)+i*17);canvas.scale(density,density);
                canvas.drawPath(flakes[i%4],paint);
                canvas.restore();
            }
            canvas.restore();postInvalidateDelayed(50);
        }
    }
    private final class RadarView extends View {
        private final Paint paint=new Paint(3);
        private float[] x=new float[0],z=new float[0];
        private int[] kind=new int[0];
        private boolean hasLocal;
        private float localX,localZ;
        RadarView(){super(OverlayService.this);}
        void setFrame(String[] values){
            try{hasLocal="1".equals(values[3]);localX=Float.parseFloat(values[4]);localZ=Float.parseFloat(values[6]);}
            catch(NumberFormatException ignored){hasLocal=false;}
            int count=Math.min(32,Math.max(0,(values.length-7)/7));
            float[] xx=new float[count],zz=new float[count];int[] types=new int[count];int valid=0;
            for(int i=0;i<count;i++){
                int at=7+i*7;
                try{xx[valid]=Float.parseFloat(values[at]);zz[valid]=Float.parseFloat(values[at+2]);
                    types[valid]=values[at+4].equals("1")?2:values[at+5].equals("1")?1:0;valid++;}
                catch(NumberFormatException ignored){}
            }
            x=new float[valid];z=new float[valid];kind=new int[valid];
            System.arraycopy(xx,0,x,0,valid);System.arraycopy(zz,0,z,0,valid);
            System.arraycopy(types,0,kind,0,valid);invalidate();
        }
        @Override protected void onDraw(Canvas canvas){
            super.onDraw(canvas);float w=getWidth(),h=getHeight();
            paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(dp(1));paint.setColor(0xff6a8b9c);
            canvas.drawRect(1,1,w-1,h-1,paint);canvas.drawLine(w/2,0,w/2,h,paint);canvas.drawLine(0,h/2,w,h/2,paint);
            if(hasLocal){paint.setStyle(Paint.Style.FILL);paint.setColor(0xffff8e8e);canvas.drawCircle(w/2,h/2,dp(4),paint);}
            if(x.length==0)return;
            float minX=x[0],maxX=x[0],minZ=z[0],maxZ=z[0];
            for(int i=1;i<x.length;i++){minX=Math.min(minX,x[i]);maxX=Math.max(maxX,x[i]);minZ=Math.min(minZ,z[i]);maxZ=Math.max(maxZ,z[i]);}
            float span=hasLocal?600:Math.max(30,Math.max(maxX-minX,maxZ-minZ));
            float cx=hasLocal?localX:(minX+maxX)/2,cz=hasLocal?localZ:(minZ+maxZ)/2;
            paint.setStyle(Paint.Style.FILL);
            for(int i=0;i<x.length;i++){
                if(Math.abs(x[i]-cx)>span/2||Math.abs(z[i]-cz)>span/2)continue;
                paint.setColor(kind[i]==2?0xffa8a8a8:kind[i]==1?0xff80dd87:0xff80f3df);
                canvas.drawCircle(w/2+(x[i]-cx)/span*(w-dp(20)),
                    h/2+(z[i]-cz)/span*(h-dp(20)),dp(3),paint);
            }
        }
    }
}
