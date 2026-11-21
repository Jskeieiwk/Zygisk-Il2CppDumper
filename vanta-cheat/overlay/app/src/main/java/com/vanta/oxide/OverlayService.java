package com.vanta.oxide;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.graphics.PixelFormat;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import java.nio.ByteBuffer;

public class OverlayService extends Service {

    private WindowManager wm;
    private EspView esp;
    private View menu;
    private CheatConfig cfg;
    private final Handler h = new Handler(Looper.getMainLooper());
    private Runnable aimLoop;

    @Override public IBinder onBind(Intent i) { return null; }

    @Override public void onCreate() {
        super.onCreate();
        makeForeground();
        wm = (WindowManager) getSystemService(Context.WINDOW_SERVICE);
        cfg = CheatConfig.load(this);

        // ESP оверлей: full screen, не ловит касания
        esp = new EspView(this);
        LayoutParams espLp = new LayoutParams(
                LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT,
                overlayType(),
                LayoutParams.FLAG_NOT_FOCUSABLE
                        | LayoutParams.FLAG_NOT_TOUCHABLE
                        | LayoutParams.FLAG_LAYOUT_IN_SCREEN
                        | LayoutParams.FLAG_LAYOUT_NO_LIMITS,
                PixelFormat.TRANSLUCENT);
        espLp.gravity = Gravity.TOP | Gravity.START;
        esp.setConfig(cfg);
        wm.addView(esp, espLp);

        // открываем shm
        if (NativeBridge.openShm()) {
            ByteBuffer b = NativeBridge.getLE();
            esp.setShm(b);
        }

        // меню
        menu = LayoutInflater.from(this).inflate(R.layout.overlay_menu, null);
        LayoutParams menuLp = new LayoutParams(
                dp(300), LayoutParams.WRAP_CONTENT,
                overlayType(),
                LayoutParams.FLAG_NOT_FOCUSABLE
                        | LayoutParams.FLAG_LAYOUT_IN_SCREEN
                        | LayoutParams.FLAG_LAYOUT_NO_LIMITS,
                PixelFormat.TRANSLUCENT);
        menuLp.gravity = Gravity.TOP | Gravity.START;
        menuLp.x = 40; menuLp.y = 120;
        wm.addView(menu, menuLp);
        bindMenu(menuLp);

        // aim loop
        NativeBridge.aimInit();
        pushAim();
        aimLoop = new Runnable() {
            @Override public void run() {
                if (cfg.aimEnabled) {
                    NativeBridge.aimTick(esp.screenCx(), esp.screenCy(),
                            esp.aimTargetX(), esp.aimTargetY(),
                            esp.aimActive());
                } else {
                    NativeBridge.aimTick(0,0,0,0,false);
                }
                h.postDelayed(this, 8);
            }
        };
        h.post(aimLoop);
    }

    private void pushAim() {
        NativeBridge.aimConfig(cfg.aimFovPx, cfg.aimSmooth, cfg.aimDeadPx,
                cfg.aimPreferHead, cfg.aimFireOnly);
    }

    @SuppressWarnings("ClickableViewAccessibility")
    private void bindMenu(LayoutParams lp) {
        // drag handle
        View header = menu.findViewById(R.id.menu_header);
        final int[] start = new int[4];
        header.setOnTouchListener((v, e) -> {
            switch (e.getActionMasked()) {
                case MotionEvent.ACTION_DOWN:
                    start[0] = lp.x; start[1] = lp.y;
                    start[2] = (int) e.getRawX(); start[3] = (int) e.getRawY();
                    return true;
                case MotionEvent.ACTION_MOVE:
                    lp.x = start[0] + (int)(e.getRawX() - start[2]);
                    lp.y = start[1] + (int)(e.getRawY() - start[3]);
                    wm.updateViewLayout(menu, lp);
                    return true;
            }
            return false;
        });

        ImageButton closeBtn = menu.findViewById(R.id.menu_close);
        closeBtn.setOnClickListener(v -> stopSelf());

        bindCheck(R.id.chk_esp,       () -> cfg.espEnabled,   v -> cfg.espEnabled = v);
        bindCheck(R.id.chk_esp_box,   () -> cfg.espBox,       v -> cfg.espBox = v);
        bindCheck(R.id.chk_esp_line,  () -> cfg.espLine,      v -> cfg.espLine = v);
        bindCheck(R.id.chk_esp_name,  () -> cfg.espName,      v -> cfg.espName = v);
        bindCheck(R.id.chk_esp_hp,    () -> cfg.espHealth,    v -> cfg.espHealth = v);
        bindCheck(R.id.chk_esp_dist,  () -> cfg.espDistance,  v -> cfg.espDistance = v);
        bindCheck(R.id.chk_team,      () -> cfg.teamCheck,    v -> cfg.teamCheck = v);
        bindCheck(R.id.chk_aim,       () -> cfg.aimEnabled,   v -> { cfg.aimEnabled = v; pushAim(); });
        bindCheck(R.id.chk_aim_head,  () -> cfg.aimPreferHead,v -> { cfg.aimPreferHead = v; pushAim(); });
        bindCheck(R.id.chk_aim_fire,  () -> cfg.aimFireOnly,  v -> { cfg.aimFireOnly = v; pushAim(); });

        bindSlider(R.id.seek_dist, R.id.lbl_dist,   50, 500, (int) cfg.espMaxDistance, (v) -> cfg.espMaxDistance = v, "дистанция", "м");
        bindSliderF(R.id.seek_fov, R.id.lbl_fov,    30f, 500f, cfg.aimFovPx,   (v) -> { cfg.aimFovPx = v; pushAim(); }, "FOV", "px");
        bindSliderF(R.id.seek_smooth, R.id.lbl_smooth, 0.05f, 1f, cfg.aimSmooth, (v) -> { cfg.aimSmooth = v; pushAim(); }, "плавность", "");
    }

    interface BoolGetter { boolean get(); }
    interface BoolSetter { void set(boolean v); }
    interface IntSetter { void set(int v); }
    interface FloatSetter { void set(float v); }

    private void bindCheck(int id, BoolGetter g, BoolSetter s) {
        CheckBox cb = menu.findViewById(id);
        if (cb == null) return;
        cb.setChecked(g.get());
        cb.setOnCheckedChangeListener((v, c) -> { s.set(c); cfg.save(this); esp.setConfig(cfg); });
    }

    private void bindSlider(int sid, int lid, int min, int max, int cur, IntSetter s, String label, String unit) {
        SeekBar sb = menu.findViewById(sid);
        TextView tv = menu.findViewById(lid);
        if (sb == null) return;
        sb.setMax(max - min);
        sb.setProgress(cur - min);
        tv.setText(label + ": " + cur + unit);
        sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar s2, int p, boolean b) {
                int v = p + min; tv.setText(label + ": " + v + unit); s.set(v);
            }
            @Override public void onStartTrackingTouch(SeekBar s2) {}
            @Override public void onStopTrackingTouch(SeekBar s2) { cfg.save(OverlayService.this); }
        });
    }
    private void bindSliderF(int sid, int lid, float min, float max, float cur, FloatSetter s, String label, String unit) {
        SeekBar sb = menu.findViewById(sid);
        TextView tv = menu.findViewById(lid);
        if (sb == null) return;
        final int STEPS = 1000;
        sb.setMax(STEPS);
        sb.setProgress((int)((cur - min) / (max - min) * STEPS));
        tv.setText(String.format("%s: %.2f%s", label, cur, unit));
        sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override public void onProgressChanged(SeekBar s2, int p, boolean b) {
                float v = min + (max - min) * p / (float)STEPS;
                tv.setText(String.format("%s: %.2f%s", label, v, unit));
                s.set(v);
            }
            @Override public void onStartTrackingTouch(SeekBar s2) {}
            @Override public void onStopTrackingTouch(SeekBar s2) { cfg.save(OverlayService.this); }
        });
    }

    private int overlayType() {
        return Build.VERSION.SDK_INT >= 26
                ? LayoutParams.TYPE_APPLICATION_OVERLAY
                : LayoutParams.TYPE_PHONE;
    }
    private int dp(int v) { return (int)(v * getResources().getDisplayMetrics().density + 0.5f); }

    private void makeForeground() {
        if (Build.VERSION.SDK_INT >= 26) {
            NotificationChannel ch = new NotificationChannel("vanta", "VANTA",
                    NotificationManager.IMPORTANCE_LOW);
            ((NotificationManager)getSystemService(NOTIFICATION_SERVICE)).createNotificationChannel(ch);
            Notification n = new Notification.Builder(this, "vanta")
                    .setContentTitle("VANTA").setContentText("overlay активен")
                    .setSmallIcon(R.mipmap.ic_launcher).build();
            startForeground(1, n);
        }
    }

    @Override public void onDestroy() {
        if (aimLoop != null) h.removeCallbacks(aimLoop);
        NativeBridge.aimShutdown();
        if (esp != null && esp.isAttachedToWindow()) wm.removeView(esp);
        if (menu != null && menu.isAttachedToWindow()) wm.removeView(menu);
        NativeBridge.closeShm();
        super.onDestroy();
    }
}
