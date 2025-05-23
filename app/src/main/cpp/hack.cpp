// Copyright (c) 2020-2021 Perfare
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

#include "hack.h"
#include "il2cpp_dump.h"
#include "log.h"
#include "xdl.h"
#include <unistd.h>
#include <dlfcn.h>
#include <jni.h>
#include <thread>
#include <string>

void hack_start(const char *game_data_dir) {
    LOGI("hack_start invoked for game_data_dir: %s", game_data_dir ? game_data_dir : "null");
    if (!game_data_dir) {
        LOGE("game_data_dir is null in hack_start. Aborting.");
        return;
    }

    bool load = false;
    for (int i = 0; i < 10; i++) {
        void *handle = xdl_open("libil2cpp.so", 0);
        if (handle) {
            LOGI("libil2cpp.so loaded successfully at try %d. Handle: %p", i + 1, handle);
            load = true;
            il2cpp_api_init(handle);
            il2cpp_dump(game_data_dir);
            break;
        } else {
            LOGW("Failed to load libil2cpp.so at try %d. Waiting 1 second.", i + 1);
            sleep(1);
        }
    }
    
    if (!load) {
        LOGE("libil2cpp.so not found after 10 tries in thread %d.", gettid());
    }
}

std::string GetLibDir(JavaVM *vm) {
    if (!vm) {
        LOGE("JavaVM is null in GetLibDir");
        return {};
    }
    
    JNIEnv *env = nullptr;
    if (vm->AttachCurrentThread(&env, nullptr) != JNI_OK || !env) {
        LOGE("Failed to attach current thread to JavaVM");
        return {};
    }

    jclass activityThread = env->FindClass("android/app/ActivityThread");
    if (!activityThread) {
        LOGE("Failed to find ActivityThread class");
        return {};
    }

    jmethodID currentApplication = env->GetStaticMethodID(activityThread, "currentApplication", "()Landroid/app/Application;");
    if (!currentApplication) {
        LOGE("Failed to get currentApplication method");
        env->DeleteLocalRef(activityThread);
        return {};
    }

    jobject application = env->CallStaticObjectMethod(activityThread, currentApplication);
    if (!application) {
        LOGE("Failed to get application instance");
        env->DeleteLocalRef(activityThread);
        return {};
    }

    jclass applicationClass = env->GetObjectClass(application);
    jmethodID getAppInfo = env->GetMethodID(applicationClass, "getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
    if (!getAppInfo) {
        LOGE("Failed to get getApplicationInfo method");
        env->DeleteLocalRef(application);
        env->DeleteLocalRef(activityThread);
        return {};
    }

    jobject appInfo = env->CallObjectMethod(application, getAppInfo);
    if (!appInfo) {
        LOGE("Failed to get ApplicationInfo");
        env->DeleteLocalRef(application);
        env->DeleteLocalRef(activityThread);
        return {};
    }

    jclass appInfoClass = env->GetObjectClass(appInfo);
    jfieldID nativeLibDirField = env->GetFieldID(appInfoClass, "nativeLibraryDir", "Ljava/lang/String;");
    if (!nativeLibDirField) {
        LOGE("Failed to get nativeLibraryDir field");
        env->DeleteLocalRef(appInfo);
        env->DeleteLocalRef(application);
        env->DeleteLocalRef(activityThread);
        return {};
    }

    jstring libDir = (jstring)env->GetObjectField(appInfo, nativeLibDirField);
    const char *libDirStr = env->GetStringUTFChars(libDir, nullptr);
    std::string result(libDirStr);
    
    // Limpieza
    env->ReleaseStringUTFChars(libDir, libDirStr);
    env->DeleteLocalRef(libDir);
    env->DeleteLocalRef(appInfo);
    env->DeleteLocalRef(application);
    env->DeleteLocalRef(activityThread);
    
    return result;
}

void hack_prepare(const char *game_data_dir) {
    LOGI("hack_prepare started in thread: %d", gettid());
    if (!game_data_dir) {
        LOGE("game_data_dir is null in hack_prepare. Aborting.");
        return;
    }

    LOGI("Starting dump for: %s", game_data_dir);
    hack_start(game_data_dir);
    
    LOGI("hack_prepare finished for %s", game_data_dir);
}