#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>

#include "Includes/obfuscate.h"
#include "Includes/Logger.h"
#include "Includes/Utils.h"

#include "Struct/Vector3.h"
#include "Struct/Vector2.h"
#include "Struct/Rect.h"
#include "Struct/Quaternion.h"

#include "Engine/Il2Cpp.h"
#include "Engine/Tools.h"

#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

#include "FunHax/Rendika.hpp"

#define targetLibName enc("libil2cpp.so")
#include "Includes/Macros.h"

// Variables globales
bool InitFunHax = false;
uintptr_t libengine = 0;

// Definición de la variable del hook
int (*FunHax::old_GetTotalXp)(void* instance);

void *hack_thread(void *) {
    // Esperar carga de la librería
    while (!libengine) {
        libengine = Tools::GetBaseAddress(targetLibName);
        sleep(1);
    }
    
    // Inicializar Il2Cpp
    Il2CppAttach(targetLibName);
    sleep(1);
    
    // Obtener offset y aplicar hook
    uintptr_t getTotalXpOffset = (uintptr_t)Il2CppGetMethodOffset(Assembly, "", "MissionStatistics", enc("GetTotalXp"), 0);
    
    if (getTotalXpOffset != 0) {
        // SOLUCIÓN DEFINITIVA: Usar variable temporal para el hook
        void* original_ptr = nullptr;
        Tools::Hook((void*)getTotalXpOffset, (void*)FunHax::GetTotalXp, (void**)&original_ptr);
        FunHax::old_GetTotalXp = (int (*)(void*))original_ptr;
    }
    
    return nullptr;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
        OBFUSCATE("Category_TEST HACK"),
        OBFUSCATE("0_ButtonOnOff_High XP (150k)"),
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return ret;
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
             jint featNum, jstring featName, jint value,
             jboolean boolean, jstring str) {
    
    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    switch (featNum) {
        case 0:
            if (boolean) {
                Toast(env, obj, enc("High XP Active (150k)"), ToastLength::LENGTH_SHORT);
            }
            break;
    }
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void*>(Icon)},
        {OBFUSCATE("IconWebViewData"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void*>(IconWebViewData)},
        {OBFUSCATE("IsGameLibLoaded"), OBFUSCATE("()Z"), reinterpret_cast<void*>(isGameLibLoaded)},
        {OBFUSCATE("Init"), OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void*>(Init)},
        {OBFUSCATE("SettingsList"), OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void*>(SettingsList)},
        {OBFUSCATE("GetFeatureList"), OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void*>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz) return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0])) return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void*>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz) return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0]))) return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
        {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void*>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz) return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods)/sizeof(methods[0]))) return JNI_ERR;
    return JNI_OK;
}

extern "C" JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    
    pthread_t ptid;
    pthread_create(&ptid, nullptr, hack_thread, nullptr);
    
    if (RegisterMenu(env) != JNI_OK) return JNI_ERR;
    if (RegisterPreferences(env) != JNI_OK) return JNI_ERR;
    if (RegisterMain(env) != JNI_OK) return JNI_ERR;
    
    return JNI_VERSION_1_6;
}