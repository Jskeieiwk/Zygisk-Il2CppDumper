#pragma once

#include <android/log.h>

#define MS_TAG "MSCheat"
#define MS_LOGI(...) __android_log_print(ANDROID_LOG_INFO, MS_TAG, __VA_ARGS__)
#define MS_LOGW(...) __android_log_print(ANDROID_LOG_WARN, MS_TAG, __VA_ARGS__)
#define MS_LOGE(...) __android_log_print(ANDROID_LOG_ERROR, MS_TAG, __VA_ARGS__)
