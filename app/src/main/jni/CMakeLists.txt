cmake_minimum_required(VERSION 3.22.1)
project(MyLibName)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Establecer la versión mínima del SDK para arm64-v8a
set(CMAKE_SYSTEM_VERSION 21)

# Directorios de inclusión
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory
    ${CMAKE_CURRENT_SOURCE_DIR}/Menu
    ${CMAKE_CURRENT_SOURCE_DIR}/And64InlineHook
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate
)

# Agregar la biblioteca
add_library(MyLibName SHARED
    Main.cpp
    Substrate/hde64.c
    Substrate/SubstrateDebug.cpp
    Substrate/SubstrateHook.cpp
    Substrate/SubstratePosixMemory.cpp
    Substrate/SymbolFinder.cpp
    KittyMemory/KittyMemory.cpp
    KittyMemory/MemoryPatch.cpp
    KittyMemory/MemoryBackup.cpp
    KittyMemory/KittyUtils.cpp
    And64InlineHook/And64InlineHook.cpp
)

# Vincular bibliotecas necesarias
target_link_libraries(MyLibName log)