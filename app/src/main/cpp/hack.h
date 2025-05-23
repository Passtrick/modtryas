#ifndef IL2CPPDUMPER_HACK_H
#define IL2CPPDUMPER_HACK_H

#include <stddef.h>

void hack_prepare(const char *game_data_dir, void *data, size_t length);

#if defined(__arm__) || defined(__aarch64__)
void InitDumper(void* vm, const char* game_data_dir);
#endif

#endif //IL2CPPDUMPER_HACK_H