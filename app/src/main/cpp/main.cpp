#include <jni.h>
#include <string>
#include <unistd.h>
#include "hack.h"
#include "log.h"
#include <thread>

extern "C" JNIEXPORT void JNICALL
Java_com_perfare_il2cppdumper_MainActivity_dumpIl2Cpp(
    JNIEnv* env,
    jobject /* this */,
    jstring packageName,
    jstring dataDir) {
    
    const char* dataDirStr = env->GetStringUTFChars(dataDir, nullptr);
    if (!dataDirStr) {
        LOGE("Failed to get data directory string");
        return;
    }
    
    LOGI("Starting dump for data directory: %s", dataDirStr);
    
    // Verificar root (opcional, solo para logging)
    if (getuid() != 0) {
        LOGW("Not running as root, some features may not work");
    }
    
    // Iniciar el dump en un hilo separado
    std::thread dump_thread([dataDirStr]() {
        hack_prepare(dataDirStr);
    });
    dump_thread.detach();
    
    env->ReleaseStringUTFChars(dataDir, dataDirStr);
}

extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("IL2CPP Dumper APK loaded");
    return JNI_VERSION_1_6;
}