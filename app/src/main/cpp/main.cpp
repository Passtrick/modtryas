#include <jni.h>
#include <string>
#include "hack.h"
#include "log.h"
#include <thread>

extern "C" JNIEXPORT void JNICALL
Java_com_perfare_il2cppdumper_MainActivity_dumpIl2Cpp(
    JNIEnv* env,
    jobject /* this */,
    jstring dataDir) {
    
    const char* dataDirStr = env->GetStringUTFChars(dataDir, nullptr);
    if (!dataDirStr) {
        LOGE("Data directory string is null");
        return;
    }

    LOGI("Starting dump for: %s", dataDirStr);
    
    // Iniciar en un hilo separado
    std::thread([dataDirStr]() {
        hack_prepare(dataDirStr);
    }).detach();
    
    env->ReleaseStringUTFChars(dataDir, dataDirStr);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("IL2CPP Dumper initialized");
    return JNI_VERSION_1_6;
}