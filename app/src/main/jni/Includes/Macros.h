// thanks to shmoo and joeyjurjens for the usefull stuff under this comment.
#ifndef ANDROID_MOD_MENU_MACROS_H
#define ANDROID_MOD_MENU_MACROS_H

#define Assembly enc("Assembly-CSharp.dll")
#define UnityEngine enc("UnityEngine.dll")

//DefineHookWithOffset
#define FunHaxAddress(lib, offset, ptr, orig) Tools::Hook((void *)getAbsoluteAddress(OBFUSCATE(lib), string2Offset(OBFUSCATE(offset))), (void *)ptr, (void **)&orig)
#define HookFunction(addr, ptr, orig) Tools::Hook((void *)addr, (void *)ptr, (void **)&orig)
#define enc(str) OBFUSCATE(str)

#endif //ANDROID_MOD_MENU_MACROS_H
