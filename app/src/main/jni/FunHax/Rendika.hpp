#pragma once

//
// Created By RendikaRahardian | TG : FunHax
// 26 - Apr - 2024
//

int (*old_GetTotalXp)(void *instance);
int GetTotalXp(void *instance) {
    if (instance != NULL) {
        return 150000; // High XP value over 100k
    }
    return old_GetTotalXp(instance);
}