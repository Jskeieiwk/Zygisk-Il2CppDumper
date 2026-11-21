package com.vanta.oxide;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/** JNI мост. Все методы — static. Загружается libvantabridge.so (JNI). */
public final class NativeBridge {
    static {
        System.loadLibrary("vantabridge");
    }
    private NativeBridge() {}

    // базовое
    public static native String nativeHello();

    // запуск
    public static native int    findGamePid(String pkg);
    public static native String stageHelper(String srcAbs, String targetName);
    public static native String inject(int pid, String soPath, String entry);

    // shm
    public static native boolean openShm();
    public static native void    closeShm();
    public static native ByteBuffer shmBuffer();
    public static native int     shmSize();
    public static native int     offsetPlayerCount();
    public static native int     offsetLocalIdx();
    public static native int     offsetPlayers();
    public static native int     offsetCamera();
    public static native int     sizeOfPlayer();
    public static native int     maxPlayers();

    // aim
    public static native boolean aimInit();
    public static native void    aimConfig(float fovPx, float smooth, float deadPx, boolean preferHead, boolean fireOnly);
    public static native void    aimTick(int cx, int cy, int tx, int ty, boolean active);
    public static native void    aimShutdown();

    // helpers java-side
    public static ByteBuffer getLE() {
        ByteBuffer b = shmBuffer();
        if (b != null) b.order(ByteOrder.LITTLE_ENDIAN);
        return b;
    }
}
