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

# Directorios de inclusión global
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Unity
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Substrate
    ${CMAKE_CURRENT_SOURCE_DIR}/src/KittyMemory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Socket
)

# Biblioteca ejecutable: inject
add_executable(inject
    src/Inject/inject.cpp
    src/Inject/inject_main.cpp
)
target_link_libraries(inject
    dl
    log
)

# Primera biblioteca compartida: Client
add_library(Client SHARED
    src/Client.cpp
    src/Socket/SocketClient.cpp
)
target_link_libraries(Client
    m
    dl
    log
    GLESv2
)

# Segunda biblioteca compartida: musk
add_library(musk SHARED
    src/Server.cpp
    src/Substrate/hde64.c
    src/Substrate/SubstrateDebug.cpp
    src/Substrate/SubstrateHook.cpp
    src/Substrate/SubstratePosixMemory.cpp
    src/KittyMemory/KittyMemory.cpp
    src/KittyMemory/MemoryPatch.cpp
    src/KittyMemory/MemoryBackup.cpp
    src/KittyMemory/KittyUtils.cpp
    src/Socket/SocketServer.cpp
)

# Incluir archivos de encabezado Unity
target_include_directories(musk PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Unity
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