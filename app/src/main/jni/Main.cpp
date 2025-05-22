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
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "Menu/Setup.h"

static const auto targetLibName = OBFUSCATE("libil2cpp.so");

#include "Includes/Macros.h"

bool feature1, feature2, featureHookToggle, Health;
int sliderValue = 1, level = 0;
void *instanceBtn;

void (*AddMoneyExample)(void *instance, int amount);

bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && featureHookToggle) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_get_FloatExample)(void *instance);
float get_FloatExample(void *instance) {
    if (instance != NULL && sliderValue > 1) {
        return (float) sliderValue;
    }
    return old_get_FloatExample(instance);
}

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && level) {
        return (int) level;
    }
    return old_Level(instance);
}

void (*old_FunctionExample)(void *instance);
void FunctionExample(void *instance) {
    instanceBtn = instance;
    if (instance != NULL) {
        if (Health) {
            *(int *) ((uint64_t) instance + 0x48) = 999;
        }
    }
    return old_FunctionExample(instance);
}

void *hack_thread(void *) {
    LOGI(OBFUSCATE("pthread created"));

    const char *libName = OBFUSCATE("libil2cpp.so");
    do {
        sleep(1);
    } while (!isLibraryLoaded(libName));

    LOGI(OBFUSCATE("Library loaded successfully"));

#if defined(__aarch64__)
    HOOK_LIB("libil2cpp.so", "0x123456", FunctionExample, old_FunctionExample);
#else
    HOOK_LIB("libil2cpp.so", "0x123456", FunctionExample, old_FunctionExample);
#endif

    return NULL;
}

jobjectArray GetFeatureList(JNIEnv *env, jobject context) {
    jobjectArray ret;

    const char *features[] = {
            OBFUSCATE("Category_The Category"),
            OBFUSCATE("Toggle_The toggle"),
            OBFUSCATE("SeekBar_The slider_1_100"),
            OBFUSCATE("Button_The button"),
            OBFUSCATE("InputValue_Input number"),
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
    const char* feature_name = env->GetStringUTFChars(featName, 0);
    
    LOGD("Feature %d: %s | Value: %d | Enabled: %d", 
         featNum, feature_name, value, boolean);

    switch (featNum) {
        case 0:
            feature1 = boolean;
            break;
        case 1:
            if (value >= 1) {
                sliderValue = value;
            }
            break;
        case 2:
            featureHookToggle = boolean;
            break;
    }

    env->ReleaseStringUTFChars(featName, feature_name);
}

__attribute__((constructor))
void lib_main() {
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

int RegisterMenu(JNIEnv *env) {
    static JNINativeMethod methods[] = {
            {OBFUSCATE("Icon"), OBFUSCATE("()Ljava/lang/String;"), (void *) Icon},
            {OBFUSCATE("IconWebViewData"), OBFUSCATE("()Ljava/lang/String;"), (void *) IconWebViewData},
            {OBFUSCATE("IsGameLibLoaded"), OBFUSCATE("()Z"), (void *) isGameLibLoaded},
            {OBFUSCATE("Init"), OBFUSCATE("(Landroid/content/Context;Landroid/widget/TextView;Landroid/widget/TextView;)V"), (void *) Init},
            {OBFUSCATE("GetFeatureList"), OBFUSCATE("()[Ljava/lang/String;"), (void *) GetFeatureList},
    };

    jclass clazz = env->FindClass(OBFUSCATE("com/android/support/Menu"));
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
    if (RegisterMenu(env) != 0)
        return JNI_ERR;
    return JNI_VERSION_1_6;
}