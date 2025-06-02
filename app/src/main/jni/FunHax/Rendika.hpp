#pragma once

namespace FunHax {
    // Declaramos como extern para que no sea inline
    extern int (*old_GetTotalXp)(void* instance);
    
    // La función hook puede ser inline
    inline int GetTotalXp(void* instance) {
        if (instance != nullptr) {
            return 150000;
        }
        return old_GetTotalXp(instance);
    }
}