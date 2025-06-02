#pragma once
#include <map>
#include <string>
#include "Includes/Logger.h"
#include "Engine/Il2Cpp.h"

#define DECLARE_CLASS(className) \
namespace Class { \
    struct className { \
        static uintptr_t ResolveMethod(const char* methodName, int argsCount = 0, const char* assembly = "Assembly-CSharp", const char* namespaze = "") { \
            void* method = Il2CppGetMethodOffset(assembly, namespaze, #className, methodName, argsCount); \
            if (!method && namespaze[0] != '\0') { \
                method = Il2CppGetMethodOffset(assembly, "", #className, methodName, argsCount); \
            } \
            if (!method) { \
                LOGD("Método %s no encontrado en %s.%s", methodName, namespaze, #className); \
            } \
            return (uintptr_t)method; \
        } \
        static uintptr_t ResolveProperty(const char* propName, bool isGetter = true, const char* assembly = "Assembly-CSharp", const char* namespaze = "") { \
            const char* prefix = isGetter ? "get_" : "set_"; \
            char fullName[256]; \
            snprintf(fullName, sizeof(fullName), "%s%s", prefix, propName); \
            return ResolveMethod(fullName, isGetter ? 0 : 1, assembly, namespaze); \
        }

#define END_DECLARE() };

DECLARE_CLASS(MissionStatistics)
    static uintptr_t GetTotalXp;
END_DECLARE()