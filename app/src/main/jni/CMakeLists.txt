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
    ${CMAKE_CURRENT_SOURCE_DIR}/Dobby
    ${CMAKE_CURRENT_SOURCE_DIR}/xDL
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory
    ${CMAKE_CURRENT_SOURCE_DIR}/Engine
)

# Agregar bibliotecas precompiladas
add_library(libdobby STATIC IMPORTED)
set_target_properties(libdobby PROPERTIES IMPORTED_LOCATION 
    ${CMAKE_CURRENT_SOURCE_DIR}/Dobby/libraries/${ANDROID_ABI}/libdobby.a)

add_library(libxdl STATIC IMPORTED)
set_target_properties(libxdl PROPERTIES IMPORTED_LOCATION 
    ${CMAKE_CURRENT_SOURCE_DIR}/xDL/libraries/${ANDROID_ABI}/libxdl.a)

# Agregar la biblioteca principal
add_library(MyLibName SHARED
    Main.cpp
    KittyMemory/KittyMemory.cpp
    KittyMemory/MemoryPatch.cpp
    KittyMemory/MemoryBackup.cpp
    KittyMemory/KittyUtils.cpp
    Engine/Il2Cpp.cpp
    Engine/Tools.cpp
)

# Vincular bibliotecas necesarias
target_link_libraries(MyLibName
    libdobby
    libxdl
    log
    android
    EGL
    GLESv2
)

# Ajustes de compilación
target_compile_options(MyLibName PRIVATE 
    -w
    -s
    -Wno-error=format-security
    -fvisibility=hidden
    -fpermissive
    -fexceptions
)

target_compile_options(MyLibName PRIVATE
    -Wno-error=c++11-narrowing
    -Wall
)

target_link_options(MyLibName PRIVATE
    -Wl,--gc-sections,--strip-all
)