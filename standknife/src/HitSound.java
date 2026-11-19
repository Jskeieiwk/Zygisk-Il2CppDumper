package dev.cloud.standknife;

import android.media.AudioAttributes;
import android.media.SoundPool;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

// Hit and kill sounds. Each sound is synthesized once into a 16-bit mono WAV at full scale in the app cache, loaded into a
// SoundPool on the game (media) stream and played with volume = percent / 200, so 200% is full scale and 100% is half.
public final class HitSound {
    public static final int DING = 0, CLICK = 1, BELL = 2, POP = 3, COUNT = 4;
    private static final int RATE = 44100;
    private static SoundPool pool;
    private static final int[] ids = new int[COUNT];
    private static String loadedDir;

    private HitSound() {}

    // Prepares every sound (idempotent). Loading is asynchronous: a play() issued before it finishes is silently dropped.
    public static synchronized boolean prepare(String cacheDir) {
        if (pool != null && cacheDir.equals(loadedDir)) return true;
        release();
        try {
            AudioAttributes attributes = new AudioAttributes.Builder()
                    .setUsage(AudioAttributes.USAGE_GAME)
                    .setContentType(AudioAttributes.CONTENT_TYPE_SONIFICATION)
                    .build();
            pool = new SoundPool.Builder().setMaxStreams(6).setAudioAttributes(attributes).build();
            for (int kind = 0; kind < COUNT; kind++) {
                File file = new File(cacheDir, "cloud-hit-" + kind + ".wav");
                writeWav(file, synthesize(kind));
                ids[kind] = pool.load(file.getAbsolutePath(), 1);
            }
            loadedDir = cacheDir;
            return true;
        } catch (Exception error) {
            release();
            return false;
        }
    }

    // kind: DING..POP, percent: 50..200. Returns false when the pool is not prepared or the kind is unknown.
    public static synchronized boolean play(int kind, int percent) {
        if (pool == null || kind < 0 || kind >= COUNT || ids[kind] == 0) return false;
        float volume = Math.max(0.25f, Math.min(1f, percent / 200f));
        return pool.play(ids[kind], volume, volume, 1, 0, 1f) != 0;
    }

    public static synchronized void release() {
        if (pool != null) pool.release();
        pool = null;
        loadedDir = null;
        for (int i = 0; i < COUNT; i++) ids[i] = 0;
    }

    static float[] synthesize(int kind) {
        int length;
        float[] out;
        switch (kind) {
            case DING: {
                length = (int) (RATE * 0.35);
                out = new float[length];
                for (int i = 0; i < length; i++) {
                    double t = (double) i / RATE, envelope = Math.exp(-t * 14);
                    out[i] = (float) (envelope * (0.7 * Math.sin(2 * Math.PI * 1760 * t) + 0.3 * Math.sin(2 * Math.PI * 2640 * t)));
                }
                break;
            }
            case CLICK: {
                length = (int) (RATE * 0.03);
                out = new float[length];
                long seed = 0x2545F4914F6CDD1DL;
                for (int i = 0; i < length; i++) {
                    double t = (double) i / RATE, envelope = Math.exp(-t * 180);
                    seed ^= seed << 13; seed ^= seed >>> 7; seed ^= seed << 17;
                    double noise = ((seed >>> 11) / (double) (1L << 53)) * 2 - 1;
                    out[i] = (float) (envelope * (0.6 * Math.signum(Math.sin(2 * Math.PI * 3200 * t)) + 0.4 * noise));
                }
                break;
            }
            case BELL: {
                length = (int) (RATE * 0.8);
                out = new float[length];
                for (int i = 0; i < length; i++) {
                    double t = (double) i / RATE;
                    out[i] = (float) (0.55 * Math.exp(-t * 5) * Math.sin(2 * Math.PI * 880 * t)
                            + 0.3 * Math.exp(-t * 8) * Math.sin(2 * Math.PI * 880 * 2.76 * t)
                            + 0.15 * Math.exp(-t * 12) * Math.sin(2 * Math.PI * 880 * 5.4 * t));
                }
                break;
            }
            default: {
                length = (int) (RATE * 0.09);
                out = new float[length];
                double phase = 0;
                for (int i = 0; i < length; i++) {
                    double t = (double) i / RATE, frequency = 150 + 450 * Math.exp(-t * 40);
                    phase += 2 * Math.PI * frequency / RATE;
                    out[i] = (float) (Math.exp(-t * 30) * Math.sin(phase));
                }
                break;
            }
        }
        normalize(out);
        return out;
    }

    static void normalize(float[] samples) {
        float peak = 0;
        for (float sample : samples) peak = Math.max(peak, Math.abs(sample));
        if (peak <= 0) return;
        float gain = 0.98f / peak;
        for (int i = 0; i < samples.length; i++) samples[i] *= gain;
    }

    static byte[] wav(float[] samples) {
        int data = samples.length * 2;
        byte[] out = new byte[44 + data];
        putAscii(out, 0, "RIFF"); putInt(out, 4, 36 + data); putAscii(out, 8, "WAVE");
        putAscii(out, 12, "fmt "); putInt(out, 16, 16); putShort(out, 20, 1); putShort(out, 22, 1);
        putInt(out, 24, RATE); putInt(out, 28, RATE * 2); putShort(out, 32, 2); putShort(out, 34, 16);
        putAscii(out, 36, "data"); putInt(out, 40, data);
        for (int i = 0; i < samples.length; i++) {
            int value = Math.round(Math.max(-1f, Math.min(1f, samples[i])) * 32767);
            putShort(out, 44 + i * 2, value);
        }
        return out;
    }

    private static void writeWav(File file, float[] samples) throws IOException {
        FileOutputStream stream = new FileOutputStream(file);
        try { stream.write(wav(samples)); } finally { stream.close(); }
    }

    private static void putAscii(byte[] out, int at, String text) {
        for (int i = 0; i < text.length(); i++) out[at + i] = (byte) text.charAt(i);
    }

    private static void putInt(byte[] out, int at, int value) {
        out[at] = (byte) value; out[at + 1] = (byte) (value >> 8); out[at + 2] = (byte) (value >> 16); out[at + 3] = (byte) (value >> 24);
    }

    private static void putShort(byte[] out, int at, int value) {
        out[at] = (byte) value; out[at + 1] = (byte) (value >> 8);
    }
}
