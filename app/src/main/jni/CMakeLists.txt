cmake_minimum_required(VERSION 3.22.1)
project(ModMenu)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SYSTEM_VERSION 21)

# Flags de compilación
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -fpermissive -fno-rtti -fno-exceptions -Wno-error=c++11-narrowing -fms-extensions")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -fno-rtti -fno-exceptions -fpermissive")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections,--strip-all")

# Bibliotecas precompiladas
add_library(GlobalInject SHARED IMPORTED)
set_target_properties(GlobalInject PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/RootLib/libGlobalInject.so)

add_library(VirtualInject SHARED IMPORTED)
set_target_properties(VirtualInject PROPERTIES IMPORTED_LOCATION
    ${CMAKE_CURRENT_SOURCE_DIR}/RootLib/libVirtualInject.so)

# Directorios de inclusión
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Primera biblioteca: MyLibName
add_library(MyLibName SHARED
    Main.cpp
    SOCKET/client.cpp
)

target_link_libraries(MyLibName
    log
    android
    GLESv2
    GlobalInject
    VirtualInject
)

# Segunda biblioteca: LibServer
add_library(LibServer SHARED
    Server.cpp
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
    SOCKET/server.cpp
)

target_link_libraries(LibServer
    log
    android
    GLESv2
)