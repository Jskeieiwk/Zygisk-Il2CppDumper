package com.cloudcrack.oxide;

import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.LinearGradient;
import android.graphics.Shader;
import android.graphics.drawable.GradientDrawable;
import android.media.SoundPool;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;
import org.json.JSONObject;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;
import java.util.Map;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

public final class InternalEntry implements Application.ActivityLifecycleCallbacks {
    private static InternalEntry instance;
    private final Handler handler=new Handler(Looper.getMainLooper());
    private Activity activity;
    private FrameLayout root;
    private FrameLayout glass;
    private LinearLayout panel;
    private TextView counter;
    private TextView fcBind;
    private boolean fcRunning;
    private TextView avBind;
    private boolean avRunning;
    private SoundPool hitPool;
    private int hitClip;
    private boolean hitLoaded;
    private SharedPreferences prefs;
    private boolean english;
    private int page;
    private boolean preview;
    private static final int CYAN=0xff7ce6e4;
    private static final int WHITE=0xffe9f7fa;
    private static final int MUTED=0xffa5b8c3;

    private InternalEntry(Activity activity){this.activity=activity;this.prefs=activity.getSharedPreferences("oxide_internal_12034",0);english=prefs.getBoolean("english",false);}
    public static boolean install(Activity activity){
        CountDownLatch done=new CountDownLatch(1);boolean[] ok={false};
        activity.runOnUiThread(()->{try{
            if(instance==null){instance=new InternalEntry(activity);activity.getApplication().registerActivityLifecycleCallbacks(instance);}
            instance.attach(activity);ok[0]=instance.root!=null&&instance.root.getParent()!=null;
        }catch(Throwable e){android.util.Log.e("Oxide_Internal","UI attach failed",e);}finally{done.countDown();}});
        try{return done.await(5,TimeUnit.SECONDS)&&ok[0];}catch(InterruptedException e){Thread.currentThread().interrupt();return false;}
    }
    private int dp(float v){return (int)(v*activity.getResources().getDisplayMetrics().density+.5f);}
    private int accent(){
        float[] hsv=new float[3];Color.colorToHSV(readColor("menu",124,230,228),hsv);
        hsv[2]=Math.max(.68f,hsv[2]);return Color.HSVToColor(hsv);
    }
    private int theme(int color,boolean fill){
        if(Color.alpha(color)==0)return color;
        float[] hsv=new float[3];Color.colorToHSV(accent(),hsv);
        if(fill){hsv[1]*=.65f;hsv[2]=Math.max(Color.red(color),Math.max(Color.green(color),Color.blue(color)))/255f;}
        return Color.HSVToColor(Color.alpha(color),hsv);
    }
    private GradientDrawable bg(int fill,int stroke,int radius){
        fill=theme(fill,true);stroke=theme(stroke,false);
        GradientDrawable d=new GradientDrawable();d.setColor(fill);d.setCornerRadius(dp(radius));d.setStroke(dp(1),stroke);return d;
    }
    private TextView text(String s,int size,int color){TextView v=new TextView(activity);v.setText(s);v.setTextSize(size*.88f);v.setTextColor(color==CYAN?accent():color);v.setGravity(Gravity.CENTER_VERTICAL);return v;}
    private String tr(String ru,String en){return english?en:ru;}
    private void attach(Activity next){
        if(activity==next&&root!=null&&root.getParent()!=null)return;
        if(root!=null&&root.getParent() instanceof android.view.ViewGroup)((android.view.ViewGroup)root.getParent()).removeView(root);
        fcBind=null;fcRunning=false;InternalBridge.freecam(false,0,0,0);
        avBind=null;avRunning=false;InternalBridge.autoFarm(false);
        activity=next;prefs=activity.getSharedPreferences("oxide_internal_12034",0);
        prefs.edit().remove("esp_distance").apply();
        root=new FrameLayout(activity);root.setClickable(false);
        root.addView(new EspOverlay(activity),new FrameLayout.LayoutParams(-1,-1));
        root.addView(new CustomCrosshair(activity),new FrameLayout.LayoutParams(-1,-1));
        counter=text("Игроки -  |  Боты -",11,WHITE);counter.setGravity(Gravity.CENTER);
        counter.setPadding(dp(11),dp(4),dp(11),dp(4));counter.setBackground(bg(0xbd111b27,0x9bd3f2f6,16));
        FrameLayout.LayoutParams cp=new FrameLayout.LayoutParams(-2,-2,Gravity.TOP|Gravity.CENTER_HORIZONTAL);cp.topMargin=dp(7);root.addView(counter,cp);
        counter.setOnClickListener(v->{if(panel==null)open();else close();});
        activity.addContentView(root,new FrameLayout.LayoutParams(-1,-1));
        InternalBridge.active(true);sync();handler.removeCallbacks(hudTick);handler.post(hudTick);
        setupHitSound();handler.removeCallbacks(hitTick);handler.post(hitTick);
    }
    private final Runnable hudTick=new Runnable(){public void run(){
        if(root==null||root.getParent()==null)return;
        int[] h=InternalBridge.hud();
        if(h!=null&&h.length>=2)counter.setText(tr("Игроки ","Players ")+(h[0]<0?"-":h[0])+"  |  "+tr("Боты ","Bots ")+(h[1]<0?"-":h[1]));
        handler.postDelayed(this,300);
    }};
    private void setupHitSound(){
        if(hitPool!=null)return;
        String path=InternalBridge.soundPath();
        if(path==null||!new File(path).isFile())return;
        try{hitPool=new SoundPool.Builder().setMaxStreams(4).build();
            hitPool.setOnLoadCompleteListener((pool,sample,status)->{
                hitLoaded=status==0;InternalBridge.soundReady(hitLoaded);
            });
            hitClip=hitPool.load(path,1);
        }catch(Exception e){android.util.Log.e("Oxide_Internal","Rust hitsound load",e);}
    }
    private final Runnable hitTick=new Runnable(){public void run(){
        if(root==null||root.getParent()==null)return;
        int count=InternalBridge.consumeHits();
        if(hitLoaded&&hitPool!=null&&count>0){float volume=Math.min(1f,Math.max(.25f,InternalBridge.hitVolume()/200f));
            for(int i=0;i<Math.min(count,3);i++)hitPool.play(hitClip,volume,volume,1,0,1f);}
        handler.postDelayed(this,60);
    }};
    private void open(){
        if(panel!=null)return;
        InternalBridge.menuOpen(true);
        glass=new FrameLayout(activity);
        panel=new LinearLayout(activity);panel.setOrientation(LinearLayout.VERTICAL);
        panel.setPadding(dp(13),dp(10),dp(13),dp(10));panel.setBackground(bg(0xe0182633,0xa7a9e4e9,17));
        FrameLayout.LayoutParams p=new FrameLayout.LayoutParams(dp(440),dp(270),Gravity.CENTER);
        int w=activity.getResources().getDisplayMetrics().widthPixels;
        int h=activity.getResources().getDisplayMetrics().heightPixels;
        p.width=Math.min(dp(440),w-dp(20));p.height=Math.min(dp(270),h-dp(36));root.addView(glass,p);
        glass.addView(panel,new FrameLayout.LayoutParams(-1,-1));
        if(prefs.getBoolean("snow",true))glass.addView(new SnowLayer(activity),new FrameLayout.LayoutParams(-1,-1));
        build();
    }
    private void close(){if(panel==null)return;root.removeView(glass);glass=null;panel=null;InternalBridge.menuOpen(false);}
    private void build(){
        if(panel==null)return;panel.setBackground(bg(0xe0182633,0xa7a9e4e9,17));panel.removeAllViews();
        LinearLayout header=new LinearLayout(activity);header.setGravity(Gravity.CENTER_VERTICAL);panel.addView(header,new LinearLayout.LayoutParams(-1,dp(35)));
        TextView title=text("Cloud Space  ·  Oxide 12034",15,WHITE);title.setTypeface(null,1);header.addView(title,new LinearLayout.LayoutParams(0,-1,1));
        TextView close=text("✕",22,CYAN);close.setGravity(Gravity.CENTER);header.addView(close,new LinearLayout.LayoutParams(dp(34),-1));close.setOnClickListener(v->close());
        View line=new View(activity);line.setBackgroundColor(theme(0x6688c5cf,false));panel.addView(line,new LinearLayout.LayoutParams(-1,dp(1)));
        LinearLayout row=new LinearLayout(activity);panel.addView(row,new LinearLayout.LayoutParams(-1,0,1));
        LinearLayout nav=new LinearLayout(activity);nav.setOrientation(LinearLayout.VERTICAL);nav.setPadding(0,dp(8),dp(10),0);
        row.addView(nav,new LinearLayout.LayoutParams(Math.min(dp(104),glass.getLayoutParams().width/3),-1));
        ScrollView scroll=new ScrollView(activity);scroll.setFillViewport(true);row.addView(scroll,new LinearLayout.LayoutParams(0,-1,1));
        LinearLayout content=new LinearLayout(activity);content.setOrientation(LinearLayout.VERTICAL);content.setPadding(dp(8),dp(8),dp(3),dp(8));
        content.setBackground(bg(0x492d4350,0x6890c9d2,12));scroll.addView(content);
        String[] names={tr("Аимбот","Aimbot"),tr("Визуалы","Visuals"),tr("Прочее","Misc"),tr("Настройки","Settings")};
        for(int i=0;i<names.length;i++){final int id=i;TextView tab=text(names[i],13,i==page?CYAN:WHITE);
            tab.setPadding(dp(8),dp(8),0,dp(8));tab.setBackground(bg(i==page?0x5036727e:0x1f192c37,i==page?CYAN:0x0025303d,9));
            LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.bottomMargin=dp(5);nav.addView(tab,lp);
            tab.setOnClickListener(v->{page=id;build();});}
        if(page==0)aim(content);else if(page==1)visuals(content);else if(page==2)misc(content);else settings(content);
    }
    private void section(LinearLayout out,String label){TextView t=text(label,14,CYAN);t.setTypeface(null,1);t.setPadding(dp(2),dp(3),0,dp(7));out.addView(t);}
    private void toggle(LinearLayout out,String ru,String en,String key,boolean def){
        TextView v=text(tr(ru,en)+(prefs.getBoolean(key,def)?"   ✓":"   ○"),13,WHITE);
        v.setPadding(dp(10),dp(8),dp(6),dp(8));v.setBackground(bg(0x452b4551,0x6578aeb9,9));
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.bottomMargin=dp(6);out.addView(v,lp);
        v.setOnClickListener(w->{boolean on=!prefs.getBoolean(key,def);prefs.edit().putBoolean(key,on).apply();v.setText(tr(ru,en)+(on?"   ✓":"   ○"));sync();
            if(key.equals("snow")){close();open();}else if(key.equals("english"))build();});
    }
    private void slider(LinearLayout out,String ru,String en,String key,int min,int max,int def){
        int value=prefs.getInt(key,def);TextView name=text(tr(ru,en)+"  "+value,12,WHITE);out.addView(name);
        SeekBar bar=new SeekBar(activity);bar.setMax(max-min);bar.setProgress(Math.max(0,Math.min(max-min,value-min)));
        out.addView(bar,new LinearLayout.LayoutParams(-1,dp(27)));
        bar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener(){public void onProgressChanged(SeekBar b,int n,boolean user){
            if(user){int v=n+min;name.setText(tr(ru,en)+"  "+v);prefs.edit().putInt(key,v).apply();sync();}}
            public void onStartTrackingTouch(SeekBar b){} public void onStopTrackingTouch(SeekBar b){} });
    }
    private void aim(LinearLayout out){section(out,tr("Аим · память игры","Aim · game memory"));
        toggle(out,"Включить аим","Enable aim","aim",false);
        toggle(out,"Проверка видимости","Visibility check","visible",true);
        toggle(out,"Показать FOV","Show FOV","draw_fov",true);
        slider(out,"Радиус FOV","FOV radius","fov",20,600,170);
        slider(out,"Плавность","Smoothness","smooth",1,20,6);
        slider(out,"Дальность аима, м","Aim range, m","aim_distance",10,1000,200);
        out.addView(text(tr("Упреждение и траектория рассчитываются автоматически для поддерживаемого стрелкового оружия. Луки, ракеты и стрельба под водой пока не поддержаны.",
            "Automatic prediction for supported firearms. Bows, rockets and underwater shots are not yet supported."),11,MUTED));
    }
    private void visuals(LinearLayout out){
        section(out,tr("Кастомный прицел","Custom crosshair"));
        toggle(out,"Заменить штатный прицел","Replace game crosshair","custom_crosshair",false);
        final String[] styles={tr("Крест","Cross"),tr("Точка","Dot"),tr("Круг","Circle"),tr("Крест с точкой","Cross and dot")};
        TextView shape=text(tr("Форма: ","Shape: ")+styles[Math.max(0,Math.min(3,prefs.getInt("crosshair_style",0)))],12,CYAN);
        out.addView(shape,new LinearLayout.LayoutParams(-1,dp(32)));
        shape.setOnClickListener(v->{int next=(prefs.getInt("crosshair_style",0)+1)%4;prefs.edit().putInt("crosshair_style",next).apply();shape.setText(tr("Форма: ","Shape: ")+styles[next]);});
        colorControl(out,"Цвет прицела","Crosshair color","crosshair",124,230,228);
        slider(out,"Размер","Size","crosshair_size",2,24,7);
        slider(out,"Зазор","Gap","crosshair_gap",0,15,3);
        slider(out,"Толщина","Thickness","crosshair_width",1,5,2);
        section(out,tr("ESP игроков","Player ESP"));
        TextView sample=text(tr("Показать превью ESP","Show ESP preview"),12,CYAN);
        sample.setPadding(dp(8),dp(7),0,dp(7));out.addView(sample);
        sample.setOnClickListener(v->{preview=!preview;build();});
        if(preview)out.addView(new EspPreview(activity),new LinearLayout.LayoutParams(-1,dp(155)));
        toggle(out,"Включить ESP","Enable ESP","esp",false);
        toggle(out,"Игнорировать команду","Ignore teammates","ignore_teams",true);
        toggle(out,"Рамки","Boxes","esp_box",true);
        toggle(out,"Скелеты","Skeletons","esp_skeleton",true);
        toggle(out,"Стрелки у FOV","FOV arrows","esp_arrows",true);
        toggle(out,"Ники","Names","esp_names",true);
        toggle(out,"Дистанция","Distance","esp_distance_label",true);
        toggle(out,"Полоска HP","HP bar","esp_hp",true);
        toggle(out,"Название оружия","Weapon name","esp_weapon",true);
        toggle(out,"Спящие","Sleepers","esp_sleepers",true);
        TextView range=text(tr("Дальность ESP: до 300 м","ESP range: up to 300 m"),12,MUTED);out.addView(range);
        section(out,tr("Объекты и животные","Objects and animals"));
        toggle(out,"ESP руды и дерева","Ore and wood ESP","esp_ores",false);
        toggle(out,"ESP животных","Animal ESP","esp_animals",false);
        toggle(out,"ESP ящиков","Crate ESP","esp_objects",false);
        toggle(out,"Обычные ящики","Standard crates","crate_standard",true);
        toggle(out,"Военные ящики","Military crates","crate_military",true);
        toggle(out,"Элитные ящики","Elite crates","crate_elite",true);
        toggle(out,"Красные ящики","Red crates","crate_red",true);
    }
    private void misc(LinearLayout out){section(out,tr("Модули Oxide","Oxide modules"));
        toggle(out,"Фрикам · игровой джойстик","Freecam · game joystick","freecam",false);
        slider(out,"Скорость фрикама","Freecam speed","freecam_speed",2,50,12);
        toggle(out,"Автохил · бинт или аптечка","Auto heal · bandage or medkit","auto_heal",false);
        slider(out,"Порог здоровья, %","Health threshold, %","heal_threshold",1,99,50);
        toggle(out,"Автофарм · кнопка AV","Auto farm · AV button","auto_farm",false);
        String[] farmNames=english?new String[]{"Stone","Sulfur","Iron","Wood"}:new String[]{"Камень","Сера","Железо","Дерево"};
        int farmKind=Math.max(1,Math.min(4,prefs.getInt("farm_kind",1)));
        TextView farmTarget=text(tr("Цель автофарма: ","Auto farm target: ")+farmNames[farmKind-1],12,CYAN);
        farmTarget.setPadding(dp(9),dp(6),0,dp(8));out.addView(farmTarget);
        farmTarget.setOnClickListener(v->{int next=prefs.getInt("farm_kind",1)%4+1;
            prefs.edit().putInt("farm_kind",next).apply();farmTarget.setText(tr("Цель автофарма: ","Auto farm target: ")+farmNames[next-1]);sync();});
        toggle(out,"Цвет неба","Custom sky color","custom_sky",false);
        colorControl(out,"Цвет неба","Sky color","sky",110,160,220);
        toggle(out,"Чамсы игроков","Player chams","player_chams",false);
        colorControl(out,"Цвет чамсов игроков","Player chams color","cham",255,70,120);
        toggle(out,"Чамсы оружия","Weapon chams","weapon_chams",false);
        colorControl(out,"Цвет чамсов оружия","Weapon chams color","weapon",70,220,230);
        slider(out,"Видимость оружия, %","Weapon opacity, %","weapon_alpha",1,99,75);
        toggle(out,"Звук хэдшота Rust","Rust headshot sound","hit_sound",false);
        slider(out,"Громкость хэдшота, %","Headshot volume, %","hit_volume",50,200,100);
        toggle(out,"Пользовательский FOV камеры","Custom camera FOV","camera_fov_on",false);
        slider(out,"FOV камеры","Camera FOV","camera_fov",40,120,80);
        toggle(out,"FOV оружия","Weapon FOV","weapon_fov_on",false);
        slider(out,"Отдаление оружия","Weapon FOV","weapon_fov",40,120,85);
        TextView note=text(tr("Для фрикама включи модуль, затем нажми FC. Кнопку можно перетаскивать.",
            "Enable freecam, then tap FC. Drag the button to move it."),12,MUTED);out.addView(note);
        TextView status=text(InternalBridge.status(),11,CYAN);status.setPadding(0,dp(12),0,0);out.addView(status);
        status.postDelayed(new Runnable(){public void run(){if(!status.isAttachedToWindow())return;status.setText(InternalBridge.status());status.postDelayed(this,1000);}},1000);
    }
    private void settings(LinearLayout out){section(out,tr("Настройки","Settings"));
        toggle(out,"Английский язык","English language","english",false);
        toggle(out,"Снег в меню","Menu snow","snow",true);
        colorControl(out,"Цвет меню","Menu color","menu",124,230,228);
        section(out,tr("Конфигурации","Profiles"));
        for(int n=1;n<=3;n++){
            final int slot=n;LinearLayout row=new LinearLayout(activity);out.addView(row,new LinearLayout.LayoutParams(-1,dp(34)));
            TextView name=text(tr("Профиль ","Profile ")+n,11,WHITE);row.addView(name,new LinearLayout.LayoutParams(0,-1,1));
            TextView save=text(tr("Сохранить","Save"),11,CYAN);save.setPadding(dp(5),0,dp(8),0);row.addView(save);
            TextView load=text(tr("Загрузить","Load"),11,CYAN);load.setPadding(dp(5),0,0,0);row.addView(load);
            save.setOnClickListener(v->saveProfile(slot));load.setOnClickListener(v->loadProfile(slot));
        }
        section(out,tr("Файл конфигурации","Configuration file"));
        TextView export=text(tr("Экспортировать JSON","Export JSON"),12,CYAN);
        out.addView(export,new LinearLayout.LayoutParams(-1,dp(32)));export.setOnClickListener(v->exportConfig());
        TextView restore=text(tr("Импортировать JSON","Import JSON"),12,CYAN);
        out.addView(restore,new LinearLayout.LayoutParams(-1,dp(32)));restore.setOnClickListener(v->importConfig());
        File dir=activity.getExternalFilesDir(null);
        TextView note=text(dir==null?tr("Внешнее хранилище недоступно","External storage unavailable"):
            new File(dir,"Oxide_Internal_12034.json").getAbsolutePath(),10,MUTED);out.addView(note);
    }
    private void saveProfile(int slot){try{
        JSONObject data=configJson();
        prefs.edit().putString("profile_"+slot,data.toString()).apply();
        Toast.makeText(activity,tr("Профиль сохранён","Profile saved"),Toast.LENGTH_SHORT).show();
    }catch(Exception e){android.util.Log.e("Oxide_Internal","Save profile",e);}}
    private JSONObject configJson() throws Exception{
        JSONObject data=new JSONObject();for(Map.Entry<String,?> item:prefs.getAll().entrySet()){
            if(item.getKey().startsWith("profile_")||item.getKey().equals("esp_distance"))continue;
            Object value=item.getValue();if(value instanceof Boolean||value instanceof Integer)data.put(item.getKey(),value);
        }
        return data;
    }
    private void applyConfig(JSONObject data) throws Exception{
        SharedPreferences.Editor edit=prefs.edit();
        java.util.Iterator<String> keys=data.keys();while(keys.hasNext()){
            String key=keys.next();if(key.startsWith("profile_")||key.equals("esp_distance"))continue;Object value=data.get(key);
            if(value instanceof Boolean)edit.putBoolean(key,(Boolean)value);else if(value instanceof Integer)edit.putInt(key,(Integer)value);
        }
        edit.apply();sync();build();
    }
    private void loadProfile(int slot){try{
        String raw=prefs.getString("profile_"+slot,null);
        if(raw==null){Toast.makeText(activity,tr("Профиль пуст","Profile empty"),Toast.LENGTH_SHORT).show();return;}
        applyConfig(new JSONObject(raw));Toast.makeText(activity,tr("Профиль загружен","Profile loaded"),Toast.LENGTH_SHORT).show();
    }catch(Exception e){android.util.Log.e("Oxide_Internal","Load profile",e);}}
    private File configFile(){File dir=activity.getExternalFilesDir(null);return dir==null?null:new File(dir,"Oxide_Internal_12034.json");}
    private void exportConfig(){try{File file=configFile();if(file==null)throw new IllegalStateException("Storage unavailable");
        byte[] bytes=configJson().toString(2).getBytes(StandardCharsets.UTF_8);
        try(FileOutputStream out=new FileOutputStream(file)){out.write(bytes);}
        Toast.makeText(activity,tr("JSON сохранён","JSON exported"),Toast.LENGTH_SHORT).show();
    }catch(Exception e){android.util.Log.e("Oxide_Internal","Export config",e);Toast.makeText(activity,e.getMessage(),Toast.LENGTH_LONG).show();}}
    private void importConfig(){try{File file=configFile();if(file==null||!file.isFile()||file.length()>65536)throw new IllegalStateException("JSON unavailable");
        byte[] bytes=new byte[(int)file.length()];try(FileInputStream in=new FileInputStream(file)){int offset=0;
            while(offset<bytes.length){int n=in.read(bytes,offset,bytes.length-offset);if(n<0)throw new IllegalStateException("Truncated JSON");offset+=n;}}
        applyConfig(new JSONObject(new String(bytes,StandardCharsets.UTF_8)));
        Toast.makeText(activity,tr("JSON загружен","JSON imported"),Toast.LENGTH_SHORT).show();
    }catch(Exception e){android.util.Log.e("Oxide_Internal","Import config",e);Toast.makeText(activity,e.getMessage(),Toast.LENGTH_LONG).show();}}
    private int readColor(String prefix,int r,int g,int b){
        return Color.rgb(Math.max(0,Math.min(255,prefs.getInt(prefix+"_r",r))),
            Math.max(0,Math.min(255,prefs.getInt(prefix+"_g",g))),
            Math.max(0,Math.min(255,prefs.getInt(prefix+"_b",b))));
    }
    private void colorControl(LinearLayout out,String ru,String en,String prefix,int r,int g,int b){
        LinearLayout row=new LinearLayout(activity);row.setGravity(Gravity.CENTER_VERTICAL);
        row.setPadding(dp(9),dp(5),dp(9),dp(5));row.setBackground(bg(0x452b4551,0x6578aeb9,9));
        TextView label=text(tr(ru,en),12,WHITE);row.addView(label,new LinearLayout.LayoutParams(0,dp(30),1));
        View swatch=new View(activity);swatch.setBackgroundColor(readColor(prefix,r,g,b));row.addView(swatch,new LinearLayout.LayoutParams(dp(32),dp(24)));
        LinearLayout.LayoutParams lp=new LinearLayout.LayoutParams(-1,-2);lp.bottomMargin=dp(7);out.addView(row,lp);
        row.setOnClickListener(v->openColorPicker(tr(ru,en),prefix,r,g,b));
    }
    private void openColorPicker(String title,String prefix,int r,int g,int b){
        if(glass==null)return;
        final FrameLayout host=glass;
        LinearLayout card=new LinearLayout(activity);card.setOrientation(LinearLayout.VERTICAL);card.setClickable(true);
        card.setPadding(dp(12),dp(8),dp(12),dp(8));card.setBackground(bg(0xff182633,0xffa9e4e9,17));
        LinearLayout bar=new LinearLayout(activity);bar.setGravity(Gravity.CENTER_VERTICAL);card.addView(bar,new LinearLayout.LayoutParams(-1,dp(32)));
        bar.addView(text(title,14,WHITE),new LinearLayout.LayoutParams(0,-1,1));
        View swatch=new View(activity);bar.addView(swatch,new LinearLayout.LayoutParams(dp(42),dp(24)));
        ColorSurface surface=new ColorSurface(activity,readColor(prefix,r,g,b),swatch);
        card.addView(surface,new LinearLayout.LayoutParams(-1,0,1));
        LinearLayout buttons=new LinearLayout(activity);buttons.setGravity(Gravity.RIGHT);
        card.addView(buttons,new LinearLayout.LayoutParams(-1,dp(36)));
        TextView cancel=text(tr("Отмена","Cancel"),13,WHITE);cancel.setPadding(dp(15),0,dp(15),0);
        buttons.addView(cancel,new LinearLayout.LayoutParams(-2,-1));cancel.setOnClickListener(v->host.removeView(card));
        TextView done=text(tr("Применить","Apply"),13,CYAN);done.setPadding(dp(15),0,dp(15),0);
        buttons.addView(done,new LinearLayout.LayoutParams(-2,-1));done.setOnClickListener(v->{
            int color=surface.selected();prefs.edit().putInt(prefix+"_r",Color.red(color)).putInt(prefix+"_g",Color.green(color)).putInt(prefix+"_b",Color.blue(color)).apply();
            host.removeView(card);sync();build();
            if(counter!=null)counter.setBackground(bg(0xbd111b27,0x9bd3f2f6,16));
            if(fcBind!=null){fcBind.setTextColor(accent());fcBind.setBackground(bg(0xbd111b27,0x9bd3f2f6,16));}
            if(avBind!=null){avBind.setTextColor(accent());avBind.setBackground(bg(0xbd111b27,0x9bd3f2f6,16));}
        });
        host.addView(card,new FrameLayout.LayoutParams(-1,-1));
    }
    private final class ColorSurface extends View {
        private final Paint paint=new Paint(Paint.ANTI_ALIAS_FLAG);
        private final float[] hsv=new float[3];private final View swatch;
        private int drag;private float left,top,right,bottom,hueLeft,hueRight;
        ColorSurface(Context c,int color,View preview){super(c);Color.colorToHSV(color,hsv);swatch=preview;swatch.setBackgroundColor(color);setClickable(true);}
        int selected(){return Color.HSVToColor(hsv);}
        protected void onDraw(Canvas c){super.onDraw(c);
            left=dp(8);top=dp(8);right=Math.max(left+1,getWidth()-dp(54));bottom=Math.max(top+1,getHeight()-dp(8));
            hueLeft=right+dp(18);hueRight=getWidth()-dp(8);
            paint.setStyle(Paint.Style.FILL);
            int hue=Color.HSVToColor(new float[]{hsv[0],1,1});
            paint.setShader(new LinearGradient(left,0,right,0,Color.WHITE,hue,Shader.TileMode.CLAMP));c.drawRect(left,top,right,bottom,paint);
            paint.setShader(new LinearGradient(0,top,0,bottom,0x00000000,Color.BLACK,Shader.TileMode.CLAMP));c.drawRect(left,top,right,bottom,paint);
            paint.setShader(new LinearGradient(0,top,0,bottom,new int[]{Color.RED,Color.YELLOW,Color.GREEN,Color.CYAN,Color.BLUE,Color.MAGENTA,Color.RED},null,Shader.TileMode.CLAMP));
            c.drawRect(hueLeft,top,hueRight,bottom,paint);paint.setShader(null);
            paint.setStyle(Paint.Style.STROKE);paint.setStrokeWidth(dp(3));paint.setColor(Color.BLACK);
            float x=left+hsv[1]*(right-left),y=bottom-hsv[2]*(bottom-top);c.drawCircle(x,y,dp(5),paint);
            paint.setStrokeWidth(dp(1.5f));paint.setColor(Color.WHITE);c.drawCircle(x,y,dp(5),paint);
            float hy=top+hsv[0]/360f*(bottom-top);c.drawRect(hueLeft-dp(3),hy-dp(3),hueRight+dp(3),hy+dp(3),paint);
        }
        public boolean onTouchEvent(MotionEvent e){
            int action=e.getActionMasked();
            if(action==MotionEvent.ACTION_DOWN){drag=e.getX()>right+dp(8)?2:1;getParent().requestDisallowInterceptTouchEvent(true);}
            if(action==MotionEvent.ACTION_DOWN||action==MotionEvent.ACTION_MOVE||action==MotionEvent.ACTION_UP){
                if(drag==2)hsv[0]=Math.max(0,Math.min(359.99f,(e.getY()-top)/Math.max(1,bottom-top)*360));
                else if(drag==1){hsv[1]=Math.max(0,Math.min(1,(e.getX()-left)/Math.max(1,right-left)));hsv[2]=1-Math.max(0,Math.min(1,(e.getY()-top)/Math.max(1,bottom-top)));}
                swatch.setBackgroundColor(selected());invalidate();
            }
            if(action==MotionEvent.ACTION_UP||action==MotionEvent.ACTION_CANCEL){drag=0;getParent().requestDisallowInterceptTouchEvent(false);if(action==MotionEvent.ACTION_UP)performClick();}
            return true;
        }
        public boolean performClick(){super.performClick();return true;}
    }
    private static final class SnowLayer extends View {
        private final Paint paint=new Paint(Paint.ANTI_ALIAS_FLAG);
        private final android.graphics.Path clip=new android.graphics.Path();
        private final float density;
        SnowLayer(Context context){super(context);density=getResources().getDisplayMetrics().density;setClickable(false);paint.setStrokeCap(Paint.Cap.ROUND);}
        protected void onDraw(Canvas canvas){super.onDraw(canvas);
            int width=getWidth(),height=getHeight();if(width<1||height<1)return;
            float time=(SystemClock.uptimeMillis()%3600000)/1000f;
            canvas.save();clip.reset();clip.addRoundRect(0,0,width,height,17*density,17*density,android.graphics.Path.Direction.CW);canvas.clipPath(clip);
            paint.setStyle(Paint.Style.STROKE);paint.setColor(0xaddcebf8);paint.setStrokeWidth(Math.max(1,.65f*density));
            for(int i=0;i<30;i++){
                float size=(3+i%4)*density;
                float x=(i*137*density+(float)Math.sin(time*.55+i)*9*density)%width;
                float y=(i*73*density+time*(8+i%5*3)*density)%(height+size*2)-size;
                canvas.save();canvas.translate(x,y);canvas.rotate(time*(i%2==0?8:-7)+i*17);
                for(int arm=0;arm<6;arm++){
                    canvas.drawLine(0,0,0,-size,paint);
                    for(int branch=1;branch<=2;branch++){
                        float at=size*(.32f+branch*.21f),twig=size*.24f;
                        canvas.drawLine(0,-at,-twig,-at-twig,paint);canvas.drawLine(0,-at,twig,-at-twig,paint);
                    }
                    canvas.rotate(60);
                }
                canvas.restore();
            }
            canvas.restore();postInvalidateOnAnimation();
        }
    }
    private final class CustomCrosshair extends View {
        private final Paint paint=new Paint(Paint.ANTI_ALIAS_FLAG);
        CustomCrosshair(Context c){super(c);setClickable(false);}
        protected void onDraw(Canvas c){super.onDraw(c);
            if(prefs.getBoolean("custom_crosshair",false)&&InternalBridge.crosshairAvailable()){
                float cx=getWidth()*.5f,cy=getHeight()*.5f;
                float size=dp(Math.max(2,Math.min(24,prefs.getInt("crosshair_size",7))));
                float gap=dp(Math.max(0,Math.min(15,prefs.getInt("crosshair_gap",3))));
                float width=dp(Math.max(1,Math.min(5,prefs.getInt("crosshair_width",2))));
                int shape=Math.max(0,Math.min(3,prefs.getInt("crosshair_style",0)));
                for(int pass=0;pass<2;pass++){
                    paint.setColor(pass==0?0xbb000000:readColor("crosshair",124,230,228));
                    paint.setStrokeWidth(width+(pass==0?dp(2):0));paint.setStrokeCap(Paint.Cap.ROUND);
                    paint.setStyle(Paint.Style.STROKE);
                    if(shape==0||shape==3){
                        c.drawLine(cx-gap-size,cy,cx-gap,cy,paint);c.drawLine(cx+gap,cy,cx+gap+size,cy,paint);
                        c.drawLine(cx,cy-gap-size,cx,cy-gap,paint);c.drawLine(cx,cy+gap,cx,cy+gap+size,paint);
                    }
                    if(shape==2)c.drawCircle(cx,cy,size,paint);
                    if(shape==1||shape==3){paint.setStyle(Paint.Style.FILL);c.drawCircle(cx,cy,Math.max(width*.5f,dp(1))+(pass==0?dp(1):0),paint);}
                }
            }
            postInvalidateDelayed(33);
        }
    }
    private static final class EspOverlay extends View {
        private final Paint p=new Paint(3);
        private final android.graphics.Path arrow=new android.graphics.Path();
        private static final int[][] LINKS={{0,1},{1,2},{1,3},{3,4},{4,5},{1,6},{6,7},{7,8},{2,9}};
        EspOverlay(Context context){super(context);setClickable(false);}
        private int tint(int kind,int variant){
            if(kind==1)return 0xffffffff;if(kind==2)return 0xffffdc62;
            if(kind==3)return 0xffba835e;if(kind==4)return 0xffa2abb4;
            if(kind==5)return 0xff91d7a5;if(kind==6)return 0xffefb36d;
            if(kind==7)return 0xff8dc4ee;if(kind==8)return 0xffb687f1;
            if(kind==9)return 0xffff646b;
            return variant==1?0xfff05b68:variant==2?0xff77da90:CYAN;
        }
        private void stroke(int color,float width){p.setStyle(Paint.Style.STROKE);p.setStrokeWidth(width);p.setColor(color);}
        private void line(Canvas c,float a,float b,float x,float y){c.drawLine(a,b,x,y,p);}
        protected void onDraw(Canvas canvas){super.onDraw(canvas);
            Object[] packed=InternalBridge.frame();
            if(packed==null||packed.length!=2||!(packed[0] instanceof float[])||!(packed[1] instanceof String[]))return;
            float[] d=(float[])packed[0];String[] names=(String[])packed[1];if(d.length<8)return;
            float sx=d[0]>0?getWidth()/d[0]:1f,sy=d[1]>0?getHeight()/d[1]:1f;
            float cx=getWidth()*.5f,cy=getHeight()*.5f,radius=d[2]*sx;
            int flags=(int)d[3],count=Math.min(names.length,Math.min((int)d[4],(d.length-8)/40));
            float width=Math.max(1f,d[5]*sx);int variant=(int)d[6];
            if((flags&1)!=0){stroke(CYAN,Math.max(1f,width*.7f));canvas.drawCircle(cx,cy,radius,p);}
            if((flags&2)!=0)for(int i=0;i<count;i++){
                int at=8+i*40;float distance=d[at+5],depth=d[at+4];
                if(distance<=0||distance>d[7])continue;
                int kind=(int)d[at+7],color=tint(kind,variant);
                float hx=d[at]*sx,hy=getHeight()-d[at+1]*sy;
                float fx=d[at+2]*sx,fy=getHeight()-d[at+3]*sy;
                if(!Float.isFinite(hx)||!Float.isFinite(hy)||!Float.isFinite(fx)||!Float.isFinite(fy))continue;
                float x=(hx+fx)*.5f,top=Math.min(hy,fy),bottom=Math.max(hy,fy),height=bottom-top;
                float score=(float)Math.hypot(hx-cx,hy-cy);
                if(kind==0&&(flags&16)!=0&&(depth<=0||score>radius)){
                    float dx=x-cx,dy=(top+bottom)*.5f-cy;
                    if(depth<=0){dx=-dx;dy=-dy;}float length=(float)Math.hypot(dx,dy);
                    if(length>1){dx/=length;dy/=length;float rr=Math.min(radius+12*getResources().getDisplayMetrics().density,
                        Math.min(getWidth(),getHeight())*.5f-20);
                        float ax=cx+dx*rr,ay=cy+dy*rr;
                        p.setStyle(Paint.Style.FILL);p.setColor(color);
                        arrow.reset();
                        arrow.moveTo(ax+dx*10,ay+dy*10);
                        arrow.lineTo(ax-dx*6-dy*5,ay-dy*6+dx*5);
                        arrow.lineTo(ax-dx*2,ay-dy*2);
                        arrow.lineTo(ax-dx*6+dy*5,ay-dy*6-dx*5);arrow.close();canvas.drawPath(arrow,p);
                    }
                }
                if(depth<=0||x<0||x>getWidth()||bottom<0||top>getHeight())continue;
                stroke(color,width);
                if(height>=3&&(flags&4)!=0){float boxWidth=height*.32f,corner=Math.min(boxWidth,height)*.25f;
                    for(int side=0;side<2;side++)for(int vertical=0;vertical<2;vertical++){
                        float bx=x+(side==0?-boxWidth*.5f:boxWidth*.5f),by=vertical==0?top:bottom;
                        line(canvas,bx,by,bx+(side==0?corner:-corner),by);
                        line(canvas,bx,by,bx,by+(vertical==0?corner:-corner));
                    }
                }else if(height<3){p.setStyle(Paint.Style.FILL);canvas.drawCircle(x,top,2.5f,p);}
                if(kind==0&&(flags&8)!=0&&(int)d[at+9]==0){
                    for(int[] pair:LINKS){int a=at+10+pair[0]*3,b=at+10+pair[1]*3;
                        if(d[a+2]>0&&d[b+2]>0)line(canvas,d[a]*sx,getHeight()-d[a+1]*sy,
                            d[b]*sx,getHeight()-d[b+1]*sy);
                    }
                }
                if(kind==0&&(flags&128)!=0&&d[at+6]>=0&&height>=3){
                    float hp=Math.max(0,Math.min(1,d[at+6]));float bx=x-height*.16f-7;
                    p.setStyle(Paint.Style.FILL);p.setColor(0xaa111111);canvas.drawRect(bx,top,bx+4,bottom,p);
                    p.setColor(hp>.5f?0xff72db81:hp>.25f?0xffffc25a:0xfff15b68);
                    canvas.drawRect(bx,top+(1-hp)*height,bx+4,bottom,p);
                }
                String label=kind!=0||(flags&32)!=0?names[i]:"";
                if((flags&64)!=0)label+=(label.isEmpty()?"":" ")+"["+(int)distance+"м]";
                if(!label.isEmpty()){
                    p.setStyle(Paint.Style.FILL);p.setTextSize(13*getResources().getDisplayMetrics().scaledDensity);
                    float tx=x-p.measureText(label)*.5f,ty=top-6;
                    p.setColor(0xff071119);canvas.drawText(label,tx+1,ty+1,p);
                    p.setColor(kind==0?WHITE:color);canvas.drawText(label,tx,ty,p);
                }
            }
            postInvalidateDelayed(67);
        }
    }
    private static final class EspPreview extends View {
        private final Paint p=new Paint(3);
        EspPreview(Context context){super(context);}
        protected void onDraw(Canvas c){super.onDraw(c);float w=getWidth(),h=getHeight();
            p.setStyle(Paint.Style.STROKE);p.setStrokeWidth(2);p.setColor(CYAN);
            c.drawCircle(w*.5f,h*.55f,h*.39f,p);c.drawRect(w*.51f,h*.16f,w*.69f,h*.9f,p);
            c.drawLine(w*.6f,h*.2f,w*.6f,h*.38f,p);c.drawLine(w*.6f,h*.38f,w*.6f,h*.65f,p);
            c.drawLine(w*.6f,h*.4f,w*.53f,h*.55f,p);c.drawLine(w*.6f,h*.4f,w*.67f,h*.55f,p);
            c.drawLine(w*.6f,h*.65f,w*.54f,h*.84f,p);c.drawLine(w*.6f,h*.65f,w*.66f,h*.84f,p);
            p.setStyle(Paint.Style.FILL);p.setColor(0xff74dc82);c.drawRect(w*.48f,h*.17f,w*.49f,h*.89f,p);
            p.setColor(WHITE);p.setTextSize(25);c.drawText("Player [86m]",w*.43f,h*.14f,p);
            p.setColor(CYAN);c.drawText("›",w*.15f,h*.55f,p);
        }
    }
    private void sync(){
        english=prefs.getBoolean("english",false);
        int[] v=new int[54];v[0]=prefs.getBoolean("esp",false)?1:0;v[1]=prefs.getBoolean("aim",false)?1:0;
        v[2]=prefs.getInt("fov",170);v[3]=prefs.getBoolean("visible",true)?1:0;
        v[4]=prefs.getInt("smooth",6);v[5]=prefs.getInt("aim_distance",200);v[8]=300;
        v[9]=prefs.getBoolean("ignore_teams",true)?1:0;
        v[12]=prefs.getBoolean("draw_fov",true)?1:0;v[13]=prefs.getBoolean("esp_box",true)?1:0;
        v[14]=prefs.getBoolean("esp_skeleton",true)?1:0;
        v[15]=prefs.getBoolean("esp_arrows",true)?1:0;v[16]=prefs.getBoolean("esp_names",true)?1:0;
        v[18]=prefs.getBoolean("esp_distance_label",true)?1:0;v[19]=prefs.getBoolean("esp_hp",true)?1:0;
        v[20]=prefs.getBoolean("esp_weapon",true)?1:0;
        v[21]=2;v[23]=1000;v[24]=1000;v[28]=prefs.getBoolean("esp_sleepers",true)?1:0;
        v[25]=prefs.getBoolean("esp_ores",false)?1:0;v[26]=prefs.getBoolean("esp_animals",false)?1:0;
        v[27]=prefs.getBoolean("esp_objects",false)?1:0;
        v[11]=prefs.getBoolean("camera_fov_on",false)?prefs.getInt("camera_fov",80):0;
        v[10]=prefs.getBoolean("weapon_fov_on",false)?prefs.getInt("weapon_fov",85):0;
        v[29]=prefs.getInt("freecam_speed",12);
        v[30]=prefs.getBoolean("crate_standard",true)?1:0;
        v[31]=prefs.getBoolean("crate_military",true)?1:0;
        v[32]=prefs.getBoolean("crate_elite",true)?1:0;
        v[33]=prefs.getBoolean("crate_red",true)?1:0;
        v[34]=prefs.getBoolean("auto_heal",false)?1:0;
        v[35]=prefs.getInt("heal_threshold",50);
        v[36]=prefs.getBoolean("custom_sky",false)?1:0;
        v[37]=prefs.getInt("sky_r",110);v[38]=prefs.getInt("sky_g",160);v[39]=prefs.getInt("sky_b",220);
        v[40]=prefs.getBoolean("player_chams",false)?1:0;
        v[41]=prefs.getInt("cham_r",255);v[42]=prefs.getInt("cham_g",70);v[43]=prefs.getInt("cham_b",120);
        v[44]=prefs.getBoolean("weapon_chams",false)?1:0;
        v[45]=prefs.getInt("weapon_r",70);v[46]=prefs.getInt("weapon_g",220);v[47]=prefs.getInt("weapon_b",230);
        v[48]=prefs.getInt("weapon_alpha",75);
        v[49]=prefs.getBoolean("hit_sound",false)?1:0;v[50]=prefs.getInt("hit_volume",100);
        v[51]=prefs.getBoolean("auto_farm",false)?1:0;v[52]=prefs.getInt("farm_kind",1);
        v[53]=prefs.getBoolean("custom_crosshair",false)?1:0;
        InternalBridge.configure(v);
        syncFreecamBind();
        syncAutoFarmBind();
    }
    private void syncFreecamBind(){
        if(root==null)return;
        boolean show=prefs.getBoolean("freecam",false);
        if(!show){if(fcBind!=null){root.removeView(fcBind);fcBind=null;}if(fcRunning){InternalBridge.freecam(false,0,0,0);fcRunning=false;}return;}
        if(fcBind!=null)return;
        fcBind=text("FC",15,CYAN);fcBind.setGravity(Gravity.CENTER);
        fcBind.setBackground(bg(0xd51a2935,0x9b80e4e3,14));
        FrameLayout.LayoutParams p=new FrameLayout.LayoutParams(dp(54),dp(54),Gravity.TOP|Gravity.LEFT);
        p.leftMargin=prefs.getInt("fc_x",dp(20));p.topMargin=prefs.getInt("fc_y",dp(75));root.addView(fcBind,p);
        fcBind.setOnTouchListener(new View.OnTouchListener(){float downX,downY,startX,startY;boolean dragged;
            public boolean onTouch(View v,MotionEvent e){
                FrameLayout.LayoutParams pos=(FrameLayout.LayoutParams)v.getLayoutParams();
                if(e.getActionMasked()==MotionEvent.ACTION_DOWN){downX=e.getRawX();downY=e.getRawY();startX=pos.leftMargin;startY=pos.topMargin;dragged=false;return true;}
                if(e.getActionMasked()==MotionEvent.ACTION_MOVE){float dx=e.getRawX()-downX,dy=e.getRawY()-downY;
                    if(Math.abs(dx)+Math.abs(dy)>dp(8))dragged=true;
                    if(dragged){pos.leftMargin=Math.max(0,Math.min(root.getWidth()-v.getWidth(),(int)(startX+dx)));
                        pos.topMargin=Math.max(0,Math.min(root.getHeight()-v.getHeight(),(int)(startY+dy)));v.setLayoutParams(pos);}return true;}
                if(e.getActionMasked()==MotionEvent.ACTION_UP){
                    if(dragged)prefs.edit().putInt("fc_x",pos.leftMargin).putInt("fc_y",pos.topMargin).apply();
                    else{boolean next=InternalBridge.freecam(!fcRunning,0,0,0);fcRunning=next;
                        if(next&&avRunning){InternalBridge.autoFarm(false);avRunning=false;
                            if(avBind!=null)avBind.setBackground(bg(0xd51a2935,0x9b80e4e3,14));}
                        v.setBackground(bg(next?0xd42c6771:0xd51a2935,0x9b80e4e3,14));
                        if(!next)Toast.makeText(activity,tr("Фрикам выключен или недоступен","Freecam off or unavailable"),Toast.LENGTH_SHORT).show();}
                    return true;}return true;
            }});
    }
    private void syncAutoFarmBind(){
        if(root==null)return;
        if(!prefs.getBoolean("auto_farm",false)){
            if(avBind!=null){root.removeView(avBind);avBind=null;}
            if(avRunning){InternalBridge.autoFarm(false);avRunning=false;}return;
        }
        if(avBind!=null)return;
        avBind=text("AV",15,CYAN);avBind.setGravity(Gravity.CENTER);
        avBind.setBackground(bg(0xd51a2935,0x9b80e4e3,14));
        FrameLayout.LayoutParams p=new FrameLayout.LayoutParams(dp(54),dp(54),Gravity.TOP|Gravity.LEFT);
        p.leftMargin=prefs.getInt("av_x",dp(85));p.topMargin=prefs.getInt("av_y",dp(75));root.addView(avBind,p);
        avBind.setOnTouchListener(new View.OnTouchListener(){float downX,downY,startX,startY;boolean dragged;
            public boolean onTouch(View v,MotionEvent e){
                FrameLayout.LayoutParams pos=(FrameLayout.LayoutParams)v.getLayoutParams();
                if(e.getActionMasked()==MotionEvent.ACTION_DOWN){downX=e.getRawX();downY=e.getRawY();startX=pos.leftMargin;startY=pos.topMargin;dragged=false;return true;}
                if(e.getActionMasked()==MotionEvent.ACTION_MOVE){float dx=e.getRawX()-downX,dy=e.getRawY()-downY;
                    if(Math.abs(dx)+Math.abs(dy)>dp(8))dragged=true;
                    if(dragged){pos.leftMargin=Math.max(0,Math.min(root.getWidth()-v.getWidth(),(int)(startX+dx)));
                        pos.topMargin=Math.max(0,Math.min(root.getHeight()-v.getHeight(),(int)(startY+dy)));v.setLayoutParams(pos);}return true;}
                if(e.getActionMasked()==MotionEvent.ACTION_UP){
                    if(dragged)prefs.edit().putInt("av_x",pos.leftMargin).putInt("av_y",pos.topMargin).apply();
                    else{boolean next=InternalBridge.autoFarm(!avRunning);avRunning=next;
                        if(next&&fcRunning){InternalBridge.freecam(false,0,0,0);fcRunning=false;
                            if(fcBind!=null)fcBind.setBackground(bg(0xd51a2935,0x9b80e4e3,14));}
                        v.setBackground(bg(next?0xd42c6771:0xd51a2935,0x9b80e4e3,14));
                        if(!next)Toast.makeText(activity,tr("Автофарм выключен или недоступен","Auto farm off or unavailable"),Toast.LENGTH_SHORT).show();}
                    return true;}return true;
            }});
    }
    public void onActivityCreated(Activity a,Bundle b){if(a.getClass().getName().equals(activity.getClass().getName()))handler.post(()->attach(a));}
    public void onActivityStarted(Activity a){} public void onActivityResumed(Activity a){} public void onActivityPaused(Activity a){}
    public void onActivityStopped(Activity a){} public void onActivitySaveInstanceState(Activity a,Bundle b){}
    public void onActivityDestroyed(Activity a){if(a==activity){handler.removeCallbacks(hudTick);handler.removeCallbacks(hitTick);root=null;panel=null;}}
}
