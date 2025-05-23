cmake_minimum_required(VERSION 3.18.1)

# Forzar modo Release si no está definido
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message("Build type: ${CMAKE_BUILD_TYPE}")

project(il2cppdumper)

# Configuración estándar de compilación
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Flags de optimización agresiva para Release
set(COMMON_FLAGS "-Werror=format -fdata-sections -ffunction-sections -fvisibility=hidden -fvisibility-inlines-hidden")
set(C_FLAGS "${COMMON_FLAGS} -O3 -flto")
set(CXX_FLAGS "${COMMON_FLAGS} -O3 -flto -fno-exceptions -fno-rtti")

# Flags del linker para reducir tamaño
set(LINKER_FLAGS "-Wl,--gc-sections -Wl,--strip-all -Wl,--hash-style=both")

# Aplicar flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")

# Incluir directorios
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/xdl/include
)

# Fuentes
aux_source_directory(xdl xdl-src)

add_library(il2cppdumper SHARED
    main.cpp
    hack.cpp
    il2cpp_dump.cpp
    ${xdl-src}
)

target_link_libraries(il2cppdumper log)

# Stripping adicional para reducir tamaño
add_custom_command(TARGET il2cppdumper POST_BUILD
    COMMAND ${CMAKE_STRIP} --strip-all --remove-section=.comment "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libil2cppdumper.so"
    COMMENT "Stripping final binary"
)