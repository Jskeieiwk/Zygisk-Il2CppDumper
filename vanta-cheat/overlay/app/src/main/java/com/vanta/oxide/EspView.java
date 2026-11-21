package com.vanta.oxide;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.RectF;
import android.graphics.Typeface;
import android.view.Choreographer;
import android.view.View;

import java.nio.ByteBuffer;

/** Прозрачный оверлей, рисует ESP поверх игры. */
public class EspView extends View implements Choreographer.FrameCallback {

    private final Paint boxP  = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint bgP   = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint textP = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint hpBgP = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint hpP   = new Paint(Paint.ANTI_ALIAS_FLAG);
    private final Paint lineP = new Paint(Paint.ANTI_ALIAS_FLAG);

    private final ShmSnapshot snap = new ShmSnapshot();
    private final float[] sPos = new float[2];
    private final float[] sHead = new float[2];
    private final float[] sFoot = new float[2];
    private ByteBuffer shm;
    private CheatConfig cfg = new CheatConfig();

    private int    aimTargetX = -1, aimTargetY = -1;
    private boolean aimActive = false;

    public EspView(Context ctx) {
        super(ctx);
        setLayerType(LAYER_TYPE_HARDWARE, null);
        boxP.setStyle(Paint.Style.STROKE);
        boxP.setStrokeWidth(2.5f);
        lineP.setStrokeWidth(1.5f);
        textP.setTextSize(28f);
        textP.setTypeface(Typeface.create("sans-serif-medium", Typeface.NORMAL));
        hpBgP.setColor(0x80000000);
        bgP.setStyle(Paint.Style.FILL);
        Choreographer.getInstance().postFrameCallback(this);
    }

    public void setConfig(CheatConfig c) { this.cfg = c; }
    public void setShm(ByteBuffer b) { this.shm = b; }

    @Override
    public void doFrame(long nanos) {
        invalidate();
        Choreographer.getInstance().postFrameCallback(this);
    }

    @SuppressLint("DrawAllocation")
    @Override
    protected void onDraw(Canvas canvas) {
        canvas.drawColor(0, PorterDuff.Mode.CLEAR);
        if (!cfg.espEnabled || shm == null) return;
        if (!snap.read(shm)) return;
        int sw = getWidth(), sh = getHeight();
        if (sw == 0 || sh == 0) return;

        int cx = sw / 2, cy = sh / 2;
        float bestDist = Float.MAX_VALUE;
        aimTargetX = -1; aimTargetY = -1;
        aimActive  = false;

        for (int i = 0; i < snap.playerCount; ++i) {
            ShmSnapshot.Player p = snap.players[i];
            if (!p.alive() || p.local()) continue;
            if (p.distance > cfg.espMaxDistance) continue;

            // позиции ноги/головы в экране
            boolean okFoot = Projection.worldToScreenSimple(
                    p.px, p.py, p.pz,
                    snap.camX, snap.camY, snap.camZ,
                    snap.camFx, snap.camFy, snap.camFz,
                    snap.camFov > 1f ? snap.camFov : 60f,
                    sw, sh, sFoot);
            boolean okHead = Projection.worldToScreenSimple(
                    p.hx, p.hy, p.hz,
                    snap.camX, snap.camY, snap.camZ,
                    snap.camFx, snap.camFy, snap.camFz,
                    snap.camFov > 1f ? snap.camFov : 60f,
                    sw, sh, sHead);
            if (!okFoot && !okHead) continue;
            float footX = okFoot ? sFoot[0] : sHead[0];
            float footY = okFoot ? sFoot[1] : sHead[1] + 100;
            float headX = okHead ? sHead[0] : footX;
            float headY = okHead ? sHead[1] : footY - 100;
            float h = Math.abs(footY - headY);
            if (h < 10) h = 60;
            float w = h * 0.45f;
            float left = headX - w / 2f, right = headX + w / 2f;
            float top = headY, bottom = footY;

            int color = cfg.colorEnemy;
            if (cfg.espBox) {
                boxP.setColor(color);
                canvas.drawRect(left, top, right, bottom, boxP);
            }
            if (cfg.espHealth) {
                float frac = p.maxHealth > 0f ? Math.max(0f, Math.min(1f, p.health / p.maxHealth)) : 0f;
                float hpX = left - 6f;
                hpBgP.setColor(0x60000000);
                canvas.drawRect(hpX - 3f, top, hpX + 3f, bottom, hpBgP);
                int hpColor = (frac > 0.6f) ? 0xFF00E676 :
                              (frac > 0.3f) ? 0xFFFFC107 : 0xFFFF1744;
                hpP.setColor(hpColor);
                float hpY = bottom - (bottom - top) * frac;
                canvas.drawRect(hpX - 3f, hpY, hpX + 3f, bottom, hpP);
            }
            if (cfg.espName) {
                textP.setColor(cfg.colorText);
                String nick = p.nick.isEmpty() ? ("#" + (p.netId & 0xFFFF)) : p.nick;
                float tw = textP.measureText(nick);
                float tx = headX - tw / 2f;
                float ty = top - 8f;
                bgP.setColor(cfg.colorBoxBg);
                canvas.drawRoundRect(tx - 6, ty - 26, tx + tw + 6, ty + 6, 6, 6, bgP);
                canvas.drawText(nick, tx, ty, textP);
            }
            if (cfg.espDistance) {
                textP.setColor(0xFFCCCCCC);
                String d = ((int) p.distance) + "м";
                float tw = textP.measureText(d);
                canvas.drawText(d, headX - tw / 2f, bottom + 28f, textP);
            }
            if (cfg.espLine) {
                lineP.setColor(color);
                canvas.drawLine(cx, sh, headX, (headY + bottom) / 2f, lineP);
            }

            // aim target: ближайший к центру
            if (cfg.aimEnabled) {
                float tx = cfg.aimPreferHead ? headX : (headX);
                float ty = cfg.aimPreferHead ? headY + h * 0.08f : (top + bottom) * 0.5f;
                float ddx = tx - cx, ddy = ty - cy;
                float dd  = (float)Math.sqrt(ddx*ddx + ddy*ddy);
                if (dd < bestDist && dd < cfg.aimFovPx) {
                    bestDist = dd;
                    aimTargetX = (int)tx;
                    aimTargetY = (int)ty;
                    aimActive = true;
                }
            }
        }

        // aim-FOV круг
        if (cfg.aimEnabled) {
            lineP.setColor(cfg.colorAccent);
            lineP.setStrokeWidth(1.2f);
            canvas.save();
            float r = cfg.aimFovPx;
            canvas.drawCircle(cx, cy, r, lineP);
            canvas.restore();
        }
    }

    public int aimTargetX() { return aimTargetX; }
    public int aimTargetY() { return aimTargetY; }
    public boolean aimActive() { return aimActive; }
    public int screenCx() { return getWidth() / 2; }
    public int screenCy() { return getHeight() / 2; }
}
