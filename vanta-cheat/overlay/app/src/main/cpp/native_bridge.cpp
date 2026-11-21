// native_bridge.cpp — JNI мост для Java: инжект, snapshot shm, aim, W2S.
#include "shm_proto.h"
#include "shm_reader.h"
#include "uinput_aim.h"
#include "ptrace_injector.h"
#include "maps_util.h"

#include <cstddef>
#include <errno.h>
#include <jni.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include <android/log.h>

#define LOGN(fmt, ...) __android_log_print(ANDROID_LOG_INFO, "vanta-jni", fmt, ##__VA_ARGS__)

static vanta::ShmReader g_reader;

extern "C" {

JNIEXPORT jstring JNICALL
Java_com_vanta_oxide_NativeBridge_nativeHello(JNIEnv* env, jclass) {
    return env->NewStringUTF("vanta ready");
}

// возвращает pid процесса или -1
JNIEXPORT jint JNICALL
Java_com_vanta_oxide_NativeBridge_findGamePid(JNIEnv* env, jclass, jstring pkg) {
    const char* p = env->GetStringUTFChars(pkg, nullptr);
    pid_t pid = vanta::find_pid_by_package(p);
    env->ReleaseStringUTFChars(pkg, p);
    return pid;
}

// копирует asset-файл по пути src_abs в /data/local/tmp/<name> с правами 0644 и chown shell:shell если возможно
JNIEXPORT jstring JNICALL
Java_com_vanta_oxide_NativeBridge_stageHelper(JNIEnv* env, jclass, jstring srcAbs, jstring targetName) {
    const char* src = env->GetStringUTFChars(srcAbs, nullptr);
    const char* nm  = env->GetStringUTFChars(targetName, nullptr);
    std::string dst = std::string("/data/local/tmp/") + nm;

    int in = open(src, O_RDONLY);
    if (in < 0) { env->ReleaseStringUTFChars(srcAbs, src); env->ReleaseStringUTFChars(targetName, nm); return nullptr; }
    int out = open(dst.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out < 0) { close(in); env->ReleaseStringUTFChars(srcAbs, src); env->ReleaseStringUTFChars(targetName, nm); return nullptr; }
    char buf[8192]; ssize_t n;
    while ((n = read(in, buf, sizeof(buf))) > 0) write(out, buf, n);
    close(in); close(out);
    chmod(dst.c_str(), 0644);
    env->ReleaseStringUTFChars(srcAbs, src);
    env->ReleaseStringUTFChars(targetName, nm);
    return env->NewStringUTF(dst.c_str());
}

JNIEXPORT jstring JNICALL
Java_com_vanta_oxide_NativeBridge_inject(JNIEnv* env, jclass, jint pid, jstring soPath, jstring entry) {
    const char* so  = env->GetStringUTFChars(soPath, nullptr);
    const char* en  = env->GetStringUTFChars(entry, nullptr);
    auto r = vanta::inject_so((pid_t)pid, so, en);
    char buf[512];
    snprintf(buf, sizeof(buf),
             "%s code=%d handle=0x%lx sym=0x%lx msg=%s",
             r.success ? "OK" : "FAIL", r.error_code,
             (unsigned long)r.remote_handle, (unsigned long)r.remote_sym,
             r.message.c_str());
    env->ReleaseStringUTFChars(soPath, so);
    env->ReleaseStringUTFChars(entry, en);
    return env->NewStringUTF(buf);
}

JNIEXPORT jboolean JNICALL
Java_com_vanta_oxide_NativeBridge_openShm(JNIEnv*, jclass) {
    // helper даёт себе до 15 секунд подняться — overlay опрашивает
    for (int i = 0; i < 30; ++i) {
        if (g_reader.open()) return JNI_TRUE;
        usleep(500'000);
    }
    return JNI_FALSE;
}

JNIEXPORT void JNICALL
Java_com_vanta_oxide_NativeBridge_closeShm(JNIEnv*, jclass) {
    g_reader.close();
}

// возвращает ByteBuffer от shm (пустой при неудаче). Java читает через getter'ы.
JNIEXPORT jobject JNICALL
Java_com_vanta_oxide_NativeBridge_shmBuffer(JNIEnv* env, jclass) {
    if (!g_reader.ptr) return nullptr;
    return env->NewDirectByteBuffer(g_reader.ptr, sizeof(VantaShmHeader));
}

JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_shmSize(JNIEnv*, jclass) {
    return (jint)sizeof(VantaShmHeader);
}

JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_offsetPlayerCount(JNIEnv*, jclass) {
    return (jint)offsetof(VantaShmHeader, player_count);
}
JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_offsetLocalIdx(JNIEnv*, jclass) {
    return (jint)offsetof(VantaShmHeader, local_player_idx);
}
JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_offsetPlayers(JNIEnv*, jclass) {
    return (jint)offsetof(VantaShmHeader, players);
}
JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_offsetCamera(JNIEnv*, jclass) {
    return (jint)offsetof(VantaShmHeader, camera);
}
JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_sizeOfPlayer(JNIEnv*, jclass) {
    return (jint)sizeof(VantaPlayer);
}
JNIEXPORT jint JNICALL Java_com_vanta_oxide_NativeBridge_maxPlayers(JNIEnv*, jclass) {
    return VANTA_MAX_PLAYERS;
}

// ---- aim ----
JNIEXPORT jboolean JNICALL Java_com_vanta_oxide_NativeBridge_aimInit(JNIEnv*, jclass) {
    return vanta::aim_init() ? JNI_TRUE : JNI_FALSE;
}
JNIEXPORT void JNICALL Java_com_vanta_oxide_NativeBridge_aimConfig(JNIEnv*, jclass,
        jfloat fov, jfloat smooth, jfloat dead, jboolean head, jboolean fireOnly) {
    vanta::AimConfig c; c.fov_px = fov; c.smooth = smooth; c.deadzone_px = dead;
    c.prefer_head = head; c.lock_only_while_firing = fireOnly;
    vanta::aim_set_config(c);
}
JNIEXPORT void JNICALL Java_com_vanta_oxide_NativeBridge_aimTick(JNIEnv*, jclass,
        jint cx, jint cy, jint tx, jint ty, jboolean active) {
    vanta::aim_update(cx, cy, tx, ty, active == JNI_TRUE);
}
JNIEXPORT void JNICALL Java_com_vanta_oxide_NativeBridge_aimShutdown(JNIEnv*, jclass) {
    vanta::aim_shutdown();
}

} // extern C
