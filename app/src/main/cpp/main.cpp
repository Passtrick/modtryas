#include <jni.h>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include "hack.h"
#include "log.h"
#include "game.h"

extern "C" JNIEXPORT void JNICALL
Java_com_perfare_il2cppdumper_MainActivity_dumpIl2Cpp(
    JNIEnv* env,
    jobject /* this */,
    jstring packageName,
    jstring dataDir) {
    
    const char* pkg = env->GetStringUTFChars(packageName, nullptr);
    const char* dataDirStr = env->GetStringUTFChars(dataDir, nullptr);
    
    LOGI("Starting dump for package: %s", pkg);
    LOGI("Data directory: %s", dataDirStr);
    
    // Verificar root si es necesario
    if (getuid() != 0) {
        LOGW("Not running as root, some features may not work");
    }
    
    // Iniciar el dump en un hilo separado
    std::thread hack_thread(hack_prepare, dataDirStr, nullptr, 0);
    hack_thread.detach();
    
    env->ReleaseStringUTFChars(packageName, pkg);
    env->ReleaseStringUTFChars(dataDir, dataDirStr);
}