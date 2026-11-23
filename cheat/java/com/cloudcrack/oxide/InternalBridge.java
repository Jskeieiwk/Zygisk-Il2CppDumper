package com.cloudcrack.oxide;

public final class InternalBridge {
    private InternalBridge() {}
    public static native boolean crosshairAvailable();
    public static native void configure(int[] values);
    public static native String status();
    public static native int[] hud();
    public static native Object[] frame();
    public static native void menuOpen(boolean open);
    public static native void active(boolean active);
    public static native boolean freecam(boolean active,int movement,float yaw,float pitch);
    public static native String soundPath();
    public static native void soundReady(boolean ready);
    public static native int consumeHits();
    public static native int hitVolume();
    public static native boolean autoFarm(boolean active);
}
