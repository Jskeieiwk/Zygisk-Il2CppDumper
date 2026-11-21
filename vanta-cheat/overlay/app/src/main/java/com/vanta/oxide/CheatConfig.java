package com.vanta.oxide;

import android.content.Context;
import android.content.SharedPreferences;

/** Все настройки чита. Сохраняются в SharedPreferences. */
public class CheatConfig {
    public boolean espEnabled      = true;
    public boolean espBox          = true;
    public boolean espLine         = false;
    public boolean espName         = true;
    public boolean espHealth       = true;
    public boolean espDistance     = true;
    public boolean espSkeleton     = false;
    public int     espMaxDistance  = 300;
    public boolean teamCheck       = true;

    public boolean aimEnabled      = false;
    public float   aimFovPx        = 180f;
    public float   aimSmooth       = 0.35f;
    public float   aimDeadPx       = 4f;
    public boolean aimPreferHead   = true;
    public boolean aimFireOnly     = true;

    public int     colorAccent    = 0xFF7E00FF;   // индиго
    public int     colorEnemy     = 0xFFFF2E2E;
    public int     colorTeam      = 0xFF00E676;
    public int     colorText      = 0xFFFFFFFF;
    public int     colorBoxBg     = 0x8C0D1017;   // полупрозрачный тёмный

    public static CheatConfig load(Context c) {
        SharedPreferences p = c.getSharedPreferences("vanta", Context.MODE_PRIVATE);
        CheatConfig x = new CheatConfig();
        x.espEnabled   = p.getBoolean("espEnabled",   x.espEnabled);
        x.espBox       = p.getBoolean("espBox",       x.espBox);
        x.espLine      = p.getBoolean("espLine",      x.espLine);
        x.espName      = p.getBoolean("espName",      x.espName);
        x.espHealth    = p.getBoolean("espHealth",    x.espHealth);
        x.espDistance  = p.getBoolean("espDistance",  x.espDistance);
        x.espSkeleton  = p.getBoolean("espSkeleton",  x.espSkeleton);
        x.espMaxDistance = p.getInt("espMaxDistance", x.espMaxDistance);
        x.teamCheck    = p.getBoolean("teamCheck",    x.teamCheck);
        x.aimEnabled   = p.getBoolean("aimEnabled",   x.aimEnabled);
        x.aimFovPx     = p.getFloat("aimFovPx",       x.aimFovPx);
        x.aimSmooth    = p.getFloat("aimSmooth",      x.aimSmooth);
        x.aimDeadPx    = p.getFloat("aimDeadPx",      x.aimDeadPx);
        x.aimPreferHead = p.getBoolean("aimPreferHead", x.aimPreferHead);
        x.aimFireOnly  = p.getBoolean("aimFireOnly",  x.aimFireOnly);
        return x;
    }

    public void save(Context c) {
        SharedPreferences.Editor e = c.getSharedPreferences("vanta", Context.MODE_PRIVATE).edit();
        e.putBoolean("espEnabled",   espEnabled);
        e.putBoolean("espBox",       espBox);
        e.putBoolean("espLine",      espLine);
        e.putBoolean("espName",      espName);
        e.putBoolean("espHealth",    espHealth);
        e.putBoolean("espDistance",  espDistance);
        e.putBoolean("espSkeleton",  espSkeleton);
        e.putInt("espMaxDistance",   espMaxDistance);
        e.putBoolean("teamCheck",    teamCheck);
        e.putBoolean("aimEnabled",   aimEnabled);
        e.putFloat("aimFovPx",       aimFovPx);
        e.putFloat("aimSmooth",      aimSmooth);
        e.putFloat("aimDeadPx",      aimDeadPx);
        e.putBoolean("aimPreferHead", aimPreferHead);
        e.putBoolean("aimFireOnly",  aimFireOnly);
        e.apply();
    }
}
