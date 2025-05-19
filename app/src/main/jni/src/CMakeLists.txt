cmake_minimum_required(VERSION 3.22.1)
project(ModMenu)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SYSTEM_VERSION 21)

# Forzar compilación para 32 bits
set(ANDROID_ABI "armeabi-v7a")
set(CMAKE_ANDROID_ARCH_ABI "armeabi-v7a")
set(CMAKE_ANDROID_ARM_MODE ON)

# Flags de compilación comunes
set(COMMON_FLAGS "-DDEBUG -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} -Werror -s -fpermissive -fno-rtti -fno-exceptions -Wno-error=c++11-narrowing -fms-extensions")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} -fno-rtti -fno-exceptions -fpermissive")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections,--strip-all")

# Definir el directorio base del proyecto
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Directorios de inclusión global
include_directories(
    ${PROJECT_ROOT}
    ${PROJECT_ROOT}/Includes
    ${PROJECT_ROOT}/Unity
    ${PROJECT_ROOT}/Substrate
    ${PROJECT_ROOT}/KittyMemory
    ${PROJECT_ROOT}/Socket
)

# Biblioteca ejecutable: inject
add_executable(inject
    ${PROJECT_ROOT}/Inject/inject.cpp
    ${PROJECT_ROOT}/Inject/inject_main.cpp
)
target_link_libraries(inject
    dl
    log
)

# Primera biblioteca compartida: Client
add_library(Client SHARED
    ${PROJECT_ROOT}/Client.cpp
    ${PROJECT_ROOT}/Socket/SocketClient.cpp
)
target_include_directories(Client PRIVATE
    ${PROJECT_ROOT}
)
target_link_libraries(Client
    m
    dl
    log
    GLESv2
)

# Segunda biblioteca compartida: musk
add_library(musk SHARED
    ${PROJECT_ROOT}/Server.cpp
    ${PROJECT_ROOT}/Substrate/hde64.c
    ${PROJECT_ROOT}/Substrate/SubstrateDebug.cpp
    ${PROJECT_ROOT}/Substrate/SubstrateHook.cpp
    ${PROJECT_ROOT}/Substrate/SubstratePosixMemory.cpp
    ${PROJECT_ROOT}/KittyMemory/KittyMemory.cpp
    ${PROJECT_ROOT}/KittyMemory/MemoryPatch.cpp
    ${PROJECT_ROOT}/KittyMemory/MemoryBackup.cpp
    ${PROJECT_ROOT}/KittyMemory/KittyUtils.cpp
    ${PROJECT_ROOT}/Socket/SocketServer.cpp
)

target_include_directories(musk PRIVATE
    ${PROJECT_ROOT}
    ${PROJECT_ROOT}/Unity
)

target_link_libraries(musk
    m
    dl
    log
    GLESv2
)

# Asegurar que los archivos de encabezado Unity se incluyan correctamente
set_target_properties(musk PROPERTIES
    COMPILE_DEFINITIONS "UNITY_HEADERS_INCLUDED"
)

# Configuración adicional para debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(inject PRIVATE DEBUG)
    target_compile_definitions(Client PRIVATE DEBUG)
    target_compile_definitions(musk PRIVATE DEBUG)
endif()