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

#define targetLibName enc("libil2cpp.so") //Created By : Rendika | TG : FunHax
#include "Includes/Macros.h"

bool InitFunHax = false;
uintptr_t libengine;

// Inicialización de variables estáticas (necesario para el sistema DECLARE_CLASS)
uintptr_t Class::MissionStatistics::GetTotalXp = 0;

void InitializeAllMethods() {
    LOGD("Iniciando resolución de métodos...");
    
    // MissionStatistics - Método GetTotalXp
    Class::MissionStatistics::GetTotalXp = Class::MissionStatistics::ResolveMethod("GetTotalXp", 0);
    
    if (Class::MissionStatistics::GetTotalXp) {
        LOGD("MissionStatistics::GetTotalXp resuelto correctamente: 0x%lx", Class::MissionStatistics::GetTotalXp);
    } else {
        LOGD("ERROR: No se pudo resolver MissionStatistics::GetTotalXp");
    }
    
    LOGD("Resolución de métodos completada.");
}

void *hack_thread(void *) {
    while (!libengine) {
        libengine = Tools::GetBaseAddress(targetLibName);
        sleep(1);
    }
    
    LOGD("Librería encontrada, iniciando Il2Cpp...");
    Il2CppAttach(targetLibName);
    sleep(1);
    
    // Inicialización dinámica de métodos
    InitializeAllMethods();
    
    // Hook manual para GetTotalXp
    if (Class::MissionStatistics::GetTotalXp) {
        HookFunction(Class::MissionStatistics::GetTotalXp, GetTotalXp, old_GetTotalXp);
        LOGD("Hook aplicado a GetTotalXp");
    } else {
        LOGD("No se pudo aplicar hook a GetTotalXp - método no encontrado");
    }
    
    LOGD("Inicialización de hacks completada");
    return NULL;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
        OBFUSCATE("Category_XP HACK"),
        OBFUSCATE("0_ButtonOnOff_High XP Gain"),
    };

    int Total_Feature = (sizeof features / sizeof features[0]);
    ret = (jobjectArray)
            env->NewObjectArray(Total_Feature, env->FindClass(OBFUSCATE("java/lang/String")),
                                env->NewStringUTF(""));

    for (int i = 0; i < Total_Feature; i++)
        env->SetObjectArrayElement(ret, i, env->NewStringUTF(features[i]));

    return (ret);
}

void Changes(JNIEnv *env, jclass clazz, jobject obj,
                                        jint featNum, jstring featName, jint value,
                                        jboolean boolean, jstring str) {

    LOGD(OBFUSCATE("Feature name: %d - %s | Value: = %d | Bool: = %d | Text: = %s"), featNum,
         env->GetStringUTFChars(featName, 0), value,
         boolean, str != NULL ? env->GetStringUTFChars(str, 0) : "");

    switch (featNum) {
        case 0:
            HighXP = boolean;
            if (boolean) {
                Toast(env, obj, enc("High XP Gain Active! - 150,000 XP"), ToastLength::LENGTH_SHORT);
                LOGD("High XP activado - retornará 150,000 XP");
            } else {
                Toast(env, obj, enc("High XP Gain Disabled"), ToastLength::LENGTH_SHORT);
                LOGD("High XP desactivado");
            }
            break;
    }
}

int RegisterMenu(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(Icon)},
            {OBFUSCATE("IconWebViewData"),  OBFUSCATE("()Ljava/lang/String;"), reinterpret_cast<void *>(IconWebViewData)},
            {OBFUSCATE("IsGameLibLoaded"),  OBFUSCATE("()Z"), reinterpret_cast<void *>(isGameLibLoaded)},
            {OBFUSCATE("Init"),  OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), reinterpret_cast<void *>(Init)},
            {OBFUSCATE("SettingsList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(SettingsList)},
            {OBFUSCATE("GetFeatureList"),  OBFUSCATE("()[Ljava/lang/String;"), reinterpret_cast<void *>(GetFeatureList)},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterPreferences(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("Changes"), OBFUSCATE("(Landroid/content/Context;ILjava/lang/String;IZLjava/lang/String;)V"), reinterpret_cast<void *>(Changes)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Preferences"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;
    return JNI_OK;
}

int RegisterMain(JNIEnv *env) {
    JNINativeMethod methods[] = {
            {OBFUSCATE("CheckOverlayPermission"), OBFUSCATE("(Landroid/content/Context;)V"), reinterpret_cast<void *>(CheckOverlayPermission)},
    };
    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Main"));
    if (!clazz)
        return JNI_ERR;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return JNI_ERR;

    return JNI_OK;
}

// Reemplaza la línea 179 y el área problemática en Main.cpp

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
    
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    if (RegisterPreferences(env) != 0)
        return JNI_ERR;
    if (RegisterMain(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}
// ← Asegúrate de que esta sea la última línea del archivo, sin } extra