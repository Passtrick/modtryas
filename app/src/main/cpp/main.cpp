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
    
    LOGI("Starting dump for data directory: %s", dataDirStr);
    
    // Verificar root si es necesario
    if (getuid() != 0) {
        LOGW("Not running as root, some features may not work");
    }
    
    // Inicialización directa sin pasar por NativeBridge
    LOGI("Starting direct hack_prepare");
    hack_prepare(dataDirStr, nullptr, 0);
    
    env->ReleaseStringUTFChars(dataDir, dataDirStr);
}

// Función de inicialización para JNI
extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOGI("Main JNI_OnLoad called - APK version");
    return JNI_VERSION_1_6;
}