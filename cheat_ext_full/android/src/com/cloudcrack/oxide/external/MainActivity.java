package com.cloudcrack.oxide.external;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.view.Gravity;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

public final class MainActivity extends Activity {
    private TextView status;
    private final Handler handler=new Handler(Looper.getMainLooper());
    private boolean launching;
    private int dp(int n){return (int)(n*getResources().getDisplayMetrics().density+.5f);}
    private TextView label(String text,int size){
        TextView view=new TextView(this);view.setText(text);view.setTextSize(size);view.setTextColor(Color.WHITE);
        view.setPadding(0,dp(10),0,dp(10));return view;
    }
    @Override public void onCreate(Bundle state){
        super.onCreate(state);
        DiagnosticLog.install(this);
        DiagnosticLog.write(this,"MAIN opened");
        LinearLayout root=new LinearLayout(this);root.setOrientation(LinearLayout.VERTICAL);
        root.setPadding(dp(24),dp(30),dp(24),dp(20));root.setBackgroundColor(0xff101820);
        TextView title=label("Cloud Oxide External",24);title.setGravity(Gravity.CENTER);
        root.addView(title);
        status=label("Версия игры: Oxide 12034 ARM64. Нужны root и разрешение поверх других окон.",15);
        root.addView(status);
        Button grant=new Button(this);grant.setText("Разрешить поверх окон");
        grant.setOnClickListener((View v)->{
            Intent intent=new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,Uri.parse("package:"+getPackageName()));
            startActivity(intent);
        });root.addView(grant);
        Button start=new Button(this);start.setText("Запустить external");
        start.setOnClickListener((View v)->start());root.addView(start);
        Button log=new Button(this);log.setText("Скопировать журнал вылета");
        log.setOnClickListener((View v)->{
            String contents=DiagnosticLog.read(this);
            android.content.ClipboardManager clipboard=(android.content.ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
            clipboard.setPrimaryClip(android.content.ClipData.newPlainText("Oxide last run",contents));
            status.setText("Журнал скопирован. Последняя строка: "+contents.substring(Math.max(0,contents.lastIndexOf('\n',Math.max(0,contents.length()-2))+1)).trim());
        });root.addView(log);
        TextView note=label("Сейчас доступна проверка процесса и чтение списка игроков. Игровые функции требуют проверки адресов на устройстве.",13);
        root.addView(note);
        setContentView(root);
    }
    private void start(){
        if(!Settings.canDrawOverlays(this)){status.setText("Сначала разреши показ поверх окон.");return;}
        if(launching)return;
        launching=true;
        status.setText("Запрашиваю root. Подтверди запрос здесь, затем игра откроется сама.");
        try {
            startService(new Intent(this,OverlayService.class));
            waitForBackend(0);
        }catch(Exception error){launching=false;status.setText("Запуск: "+error.getMessage());}
    }
    private void waitForBackend(int attempt){
        if(OverlayService.backendReady){
            Intent game=getPackageManager().getLaunchIntentForPackage("com.catsbit.oxidesurvivalisland");
            if(game==null){launching=false;status.setText("Oxide не установлен.");return;}
            DiagnosticLog.write(this,"MAIN opening game");
            startActivity(game);return;
        }
        if(attempt>=40){
            launching=false;
            status.setText("Root backend не ответил за 20 секунд: "+OverlayService.backendMessage);
            return;
        }
        handler.postDelayed(()->waitForBackend(attempt+1),500);
    }
}
