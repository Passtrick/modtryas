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
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_CURRENT_SOURCE_DIR}/Unity
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory
    ${CMAKE_CURRENT_SOURCE_DIR}/Socket
)

# Biblioteca ejecutable: inject
add_executable(inject
    ${CMAKE_CURRENT_SOURCE_DIR}/Inject/inject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Inject/inject_main.cpp
)
target_link_libraries(inject
    dl
    log
)

# Primera biblioteca compartida: Client
add_library(Client SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Socket/SocketClient.cpp
)
target_link_libraries(Client
    m
    dl
    log
    GLESv2
)

# Segunda biblioteca compartida: musk
add_library(musk SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/Server.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate/hde64.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate/SubstrateDebug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate/SubstrateHook.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Substrate/SubstratePosixMemory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/KittyMemory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/MemoryPatch.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/MemoryBackup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/KittyMemory/KittyUtils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Socket/SocketServer.cpp
)

# Incluir archivos de encabezado Unity
target_include_directories(musk PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Unity
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