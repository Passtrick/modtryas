#pragma once

namespace FunHax {
    extern int (*old_GetTotalXp)(void* instance);
    
    inline int GetTotalXp(void* instance) {
        if (instance != nullptr) {
            return 150000;
        }
        return old_GetTotalXp(instance);
    }
}