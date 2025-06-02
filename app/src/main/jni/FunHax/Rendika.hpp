#pragma once
#include <map>
#include <string>
#include "Includes/Logger.h"
#include "Engine/Il2Cpp.h"

// ========== SISTEMA DECLARE_CLASS ==========
#define DECLARE_CLASS(className) \
namespace Class { \
    struct className { \
        static uintptr_t ResolveMethod(const char* methodName, int argsCount = -1, const char* assembly = "Assembly-CSharp", const char* namespaze = ""); \
        static uintptr_t ResolveProperty(const char* propName, bool isGetter = true, const char* assembly = "Assembly-CSharp", const char* namespaze = ""); \
    }; \
} \
uintptr_t Class::className::ResolveMethod(const char* methodName, int argsCount, const char* assembly, const char* namespaze) { \
    void* method = Il2CppGetMethodOffset(assembly, namespaze, #className, methodName, argsCount); \
    if (!method && namespaze[0] != '\0') { \
        method = Il2CppGetMethodOffset(assembly, "", #className, methodName, argsCount); \
    } \
    if (!method) { \
        LOGD("Método %s no encontrado en %s.%s", methodName, namespaze, #className); \
    } \
    return (uintptr_t)method; \
} \
uintptr_t Class::className::ResolveProperty(const char* propName, bool isGetter, const char* assembly, const char* namespaze) { \
    const char* prefix = isGetter ? "get_" : "set_"; \
    char fullName[256]; \
    snprintf(fullName, sizeof(fullName), "%s%s", prefix, propName); \
    return ResolveMethod(fullName, isGetter ? 0 : 1, assembly, namespaze); \
}

#define END_DECLARE() };

namespace Class {
    // Declaración de la clase MissionStatistics
    DECLARE_CLASS(MissionStatistics)
        static uintptr_t GetTotalXp;
    END_DECLARE()

    // Declaración de la clase ProjectileBullet
    DECLARE_CLASS(ProjectileBullet)
        static uintptr_t get_Damage;
    END_DECLARE()
}

// Hook para GetTotalXp
int (*old_GetTotalXp)(void *instance);
int GetTotalXpHook(void *instance) {
    if (instance != nullptr) {
        return 999999; // Valor alto de XP
    }
    return old_GetTotalXp(instance);
}

// Hook para get_Damage
float (*old_get_Damage)(void *instance);
float get_DamageHook(void *instance) {
    if (instance != nullptr) {
        return 100000.0f; // Daño muy alto
    }
    return old_get_Damage(instance);
}