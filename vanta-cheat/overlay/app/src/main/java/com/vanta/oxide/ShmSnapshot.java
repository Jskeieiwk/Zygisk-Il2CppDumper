package com.vanta.oxide;

import java.nio.ByteBuffer;

/** Декодер структуры VantaShmHeader на Java-стороне. Соответствует shm_proto.h. */
public final class ShmSnapshot {
    public static final int MAX_PLAYERS = 128;
    public static final int NICK_LEN    = 32;

    // layout VantaPlayer: 4+4+12+12+12+4+4+4+4+32 = 92 байта, выровнено до 96 (float[]-аlign 4)
    public static final int PLAYER_SIZE = 96;

    public static final int OFF_MAGIC            = 0;
    public static final int OFF_VERSION          = 4;
    public static final int OFF_SEQ              = 8;
    public static final int OFF_TIMESTAMP_NS     = 16;
    public static final int OFF_GAME_PID         = 24;
    public static final int OFF_LOCAL_IDX        = 28;
    public static final int OFF_PLAYER_COUNT     = 32;
    public static final int OFF_PAD              = 36;

    public static final int OFF_CAMERA_START     = 40;
    public static final int OFF_CAM_POS          = OFF_CAMERA_START + 0;
    public static final int OFF_CAM_FWD          = OFF_CAMERA_START + 12;
    public static final int OFF_CAM_VIEWPROJ     = OFF_CAMERA_START + 24;   // 16 floats
    public static final int OFF_CAM_FOV          = OFF_CAM_VIEWPROJ + 64;   // 24+64 = 88
    public static final int OFF_CAM_SCREEN_W     = OFF_CAM_FOV + 4;
    public static final int OFF_CAM_SCREEN_H     = OFF_CAM_SCREEN_W + 4;

    public static final int OFF_PLAYERS          = OFF_CAM_SCREEN_H + 4;

    public int playerCount;
    public int localIdx;
    public float camX, camY, camZ;
    public float camFx, camFy, camFz;
    public float camFov;
    public int screenW, screenH;
    public float[] viewProj = new float[16];

    public final Player[] players;
    public int alive;

    public ShmSnapshot() {
        players = new Player[MAX_PLAYERS];
        for (int i = 0; i < MAX_PLAYERS; ++i) players[i] = new Player();
    }

    public static final class Player {
        public int netId;
        public int flags;
        public float px, py, pz;
        public float hx, hy, hz;
        public float vx, vy, vz;
        public float health, maxHealth;
        public float distance;
        public int   teamId;
        public final byte[] nickBytes = new byte[NICK_LEN];
        public String nick = "";
        public boolean local() { return (flags & 0x02) != 0; }
        public boolean alive() { return (flags & 0x01) != 0; }
    }

    public boolean read(ByteBuffer b) {
        if (b == null) return false;
        long magic = b.getInt(0) & 0xFFFFFFFFL;
        if (magic != 0x56414E54L) return false;
        playerCount = Math.max(0, Math.min(MAX_PLAYERS, b.getInt(OFF_PLAYER_COUNT)));
        localIdx    = b.getInt(OFF_LOCAL_IDX);
        camX  = b.getFloat(OFF_CAM_POS);
        camY  = b.getFloat(OFF_CAM_POS + 4);
        camZ  = b.getFloat(OFF_CAM_POS + 8);
        camFx = b.getFloat(OFF_CAM_FWD);
        camFy = b.getFloat(OFF_CAM_FWD + 4);
        camFz = b.getFloat(OFF_CAM_FWD + 8);
        for (int i = 0; i < 16; ++i) viewProj[i] = b.getFloat(OFF_CAM_VIEWPROJ + i * 4);
        camFov   = b.getFloat(OFF_CAM_FOV);
        screenW  = b.getInt(OFF_CAM_SCREEN_W);
        screenH  = b.getInt(OFF_CAM_SCREEN_H);
        alive = 0;
        int base = OFF_PLAYERS;
        for (int i = 0; i < playerCount; ++i) {
            int o = base + i * PLAYER_SIZE;
            Player p = players[i];
            p.netId = b.getInt(o);
            p.flags = b.getInt(o + 4);
            p.px = b.getFloat(o + 8);
            p.py = b.getFloat(o + 12);
            p.pz = b.getFloat(o + 16);
            p.hx = b.getFloat(o + 20);
            p.hy = b.getFloat(o + 24);
            p.hz = b.getFloat(o + 28);
            p.vx = b.getFloat(o + 32);
            p.vy = b.getFloat(o + 36);
            p.vz = b.getFloat(o + 40);
            p.health    = b.getFloat(o + 44);
            p.maxHealth = b.getFloat(o + 48);
            p.distance  = b.getFloat(o + 52);
            p.teamId    = b.getInt(o + 56);
            b.position(o + 60);
            b.get(p.nickBytes, 0, NICK_LEN);
            int end = 0; while (end < NICK_LEN && p.nickBytes[end] != 0) ++end;
            p.nick = new String(p.nickBytes, 0, end);
            if (p.alive()) ++alive;
        }
        return true;
    }
}
