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

#include "Engine/Il2Cpp.h"
#include "Engine/Tools.h"

#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

#include "FunHax/Rendika.hpp"

#define targetLibName enc("libil2cpp.so")
#include "Includes/Macros.h"

bool InitFunHax = false;
bool HighDamageActive = false;
uintptr_t libengine;

void InitializeAllMethods() {
    // Inicializamos los métodos que necesitamos
    Class::MissionStatistics::GetTotalXp = Class::MissionStatistics::ResolveMethod("GetTotalXp");
    Class::ProjectileBullet::get_Damage = Class::ProjectileBullet::ResolveProperty("Damage");
    
    if (!Class::MissionStatistics::GetTotalXp) {
        LOGD(OBFUSCATE("Error: No se pudo encontrar GetTotalXp"));
    } else {
        LOGD(OBFUSCATE("GetTotalXp encontrado en: 0x%X"), Class::MissionStatistics::GetTotalXp);
    }
    
    if (!Class::ProjectileBullet::get_Damage) {
        LOGD(OBFUSCATE("Error: No se pudo encontrar get_Damage"));
    } else {
        LOGD(OBFUSCATE("get_Damage encontrado en: 0x%X"), Class::ProjectileBullet::get_Damage);
    }
}

void *hack_thread(void *) {
    while (!libengine) {
        libengine = Tools::GetBaseAddress(targetLibName);
        sleep(1);
    }
    
    LOGD(OBFUSCATE("Lib encontrada en: 0x%X"), libengine);
    
    Il2CppAttach(targetLibName);
    sleep(1);
    
    // Inicialización dinámica
    InitializeAllMethods();
    
    // Aplicamos los hooks si encontramos los métodos
    if (Class::MissionStatistics::GetTotalXp) {
        HookFunction(Class::MissionStatistics::GetTotalXp, GetTotalXpHook, old_GetTotalXp);
        LOGD(OBFUSCATE("Hook aplicado a GetTotalXp"));
    } else {
        LOGD(OBFUSCATE("No se pudo aplicar el hook a GetTotalXp"));
    }
    
    if (Class::ProjectileBullet::get_Damage) {
        HookFunction(Class::ProjectileBullet::get_Damage, get_DamageHook, old_get_Damage);
        LOGD(OBFUSCATE("Hook aplicado a get_Damage"));
    } else {
        LOGD(OBFUSCATE("No se pudo aplicar el hook a get_Damage"));
    }
    
    return NULL;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
        OBFUSCATE("Category_XP_HACK"),
        OBFUSCATE("0_ButtonOnOff_GetHighXP"),
        OBFUSCATE("Category_DAMAGE_HACK"),
        OBFUSCATE("1_ButtonOnOff_HighDamage")
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
            InitFunHax = boolean;
            if (boolean) {
                Toast(env, obj, enc("High XP Active!"), ToastLength::LENGTH_SHORT);
            }
            break;
            
        case 1:
            HighDamageActive = boolean;
            if (boolean) {
                Toast(env, obj, enc("High Damage Active!"), ToastLength::LENGTH_SHORT);
            }
            break;
    }
}

// ... (el resto de las funciones JNI/Java permanecen igual)
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