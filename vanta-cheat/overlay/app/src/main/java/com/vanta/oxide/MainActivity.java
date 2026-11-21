package com.vanta.oxide;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.provider.Settings;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.widget.Button;
import android.widget.ScrollView;
import android.widget.TextView;

import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // имя пакета игры HyperHug BR24 — скорректируем в рантайме через config/URL
    private static final String GAME_PACKAGE = "com.hyperhug.oxide";

    private TextView log;
    private TextView statusPill;
    private Button   startBtn;
    private Button   stopBtn;
    private Button   overlayBtn;
    private View     glow;

    private final Handler main = new Handler(Looper.getMainLooper());
    private volatile boolean running = false;

    @Override protected void onCreate(Bundle b) {
        super.onCreate(b);
        setContentView(R.layout.activity_main);

        log        = findViewById(R.id.log);
        statusPill = findViewById(R.id.status_pill);
        startBtn   = findViewById(R.id.btn_start);
        stopBtn    = findViewById(R.id.btn_stop);
        overlayBtn = findViewById(R.id.btn_overlay);
        glow       = findViewById(R.id.glow);

        startPulse(glow);

        TextView ver = findViewById(R.id.ver);
        ver.setText("v0.1 • Oxide 12034");

        startBtn.setOnClickListener(v -> new Thread(this::launch).start());
        stopBtn.setOnClickListener(v -> {
            running = false;
            stopService(new Intent(this, OverlayService.class));
            setStatus("stopped", 0xFFFF2E2E);
            append("overlay остановлен");
        });
        overlayBtn.setOnClickListener(v -> {
            if (!Settings.canDrawOverlays(this)) {
                startActivity(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                        Uri.parse("package:" + getPackageName())));
            } else {
                append("разрешение на оверлей уже дано");
            }
        });

        setStatus("ready", 0xFF888888);
        append("VANTA / Oxide external\n"
                + "device: " + Build.MODEL + " · Android " + Build.VERSION.RELEASE + "\n"
                + "arch: " + Build.SUPPORTED_ABIS[0]);
    }

    private void startPulse(View v) {
        AlphaAnimation a = new AlphaAnimation(0.35f, 1.0f);
        a.setDuration(1600);
        a.setRepeatCount(Animation.INFINITE);
        a.setRepeatMode(Animation.REVERSE);
        v.startAnimation(a);
    }

    private void setStatus(String txt, int color) {
        main.post(() -> {
            statusPill.setText(txt);
            statusPill.setTextColor(color);
        });
    }

    private void append(String s) {
        main.post(() -> {
            log.append(s + "\n");
            ScrollView sv = findViewById(R.id.log_scroll);
            if (sv != null) sv.post(() -> sv.fullScroll(ScrollView.FOCUS_DOWN));
        });
    }

    @SuppressLint("SetWorldReadable")
    private File extractAsset(String name) throws Exception {
        File out = new File(getFilesDir(), name);
        try (InputStream in = getAssets().open(name); FileOutputStream os = new FileOutputStream(out)) {
            byte[] buf = new byte[65536]; int n;
            while ((n = in.read(buf)) > 0) os.write(buf, 0, n);
        }
        out.setReadable(true, false);
        return out;
    }

    private void launch() {
        setStatus("checking", 0xFFFFC107);
        if (!Settings.canDrawOverlays(this)) {
            setStatus("нет overlay-прав", 0xFFFF2E2E);
            append("даю запрос прав на оверлей");
            main.post(() -> startActivity(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION,
                    Uri.parse("package:" + getPackageName()))));
            return;
        }

        append("ищу процесс " + GAME_PACKAGE);
        int pid = NativeBridge.findGamePid(GAME_PACKAGE);
        if (pid <= 0) {
            setStatus("game not running", 0xFFFF2E2E);
            append("игра не запущена — запусти " + GAME_PACKAGE + " и жми ещё раз");
            return;
        }
        append("нашёл pid=" + pid);

        // извлекаем helper из apkNativeLibraryDir (уже .so есть в /lib/<abi>/)
        String abi = Build.SUPPORTED_ABIS[0];
        File helperSo = new File(getApplicationInfo().nativeLibraryDir, "libvanta_helper.so");
        if (!helperSo.exists()) {
            setStatus("no helper so", 0xFFFF2E2E);
            append("libvanta_helper.so отсутствует для " + abi);
            return;
        }
        append("stage helper → /data/local/tmp/");
        String staged = NativeBridge.stageHelper(helperSo.getAbsolutePath(), "libvanta_helper.so");
        if (staged == null) {
            setStatus("stage fail", 0xFFFF2E2E);
            append("не смог положить .so в /data/local/tmp (нужен root?)");
            return;
        }
        append("staged: " + staged);

        setStatus("injecting", 0xFFFFC107);
        append("ptrace inject → pid " + pid);
        String r = NativeBridge.inject(pid, staged, "vanta_helper_start");
        append(r);
        if (!r.startsWith("OK")) {
            setStatus("inject failed", 0xFFFF2E2E);
            append("неудача инжекции — проверь root + разрешения SELinux/ptrace_scope");
            return;
        }

        append("стартую оверлей-сервис");
        startService(new Intent(this, OverlayService.class));
        running = true;
        setStatus("ACTIVE", 0xFF00E676);
    }
}
