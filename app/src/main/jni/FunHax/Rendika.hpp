#pragma once
// Created By RendikaRahardian | TG : FunHax
// 26 - Apr - 2024

namespace FunHax {
    inline int (*old_GetTotalXp)(void* instance) = nullptr;  // Inicializado como nullptr
    
    inline int GetTotalXp(void* instance) {
        if (instance != nullptr) {
            return 150000; // High XP value
        }
        return old_GetTotalXp(instance); // Llama a la original si no hay instancia
    }
}