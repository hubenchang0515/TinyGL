cmake_minimum_required(VERSION 3.8)
project(TinyGL C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(TINYGL_USE_DEFAULT "Use default renderer" on)
option(TINYGL_BUILD_DEMO "Build Demo" on)

if(WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_link_options("$<$<AND:$<STREQUAL:$<C_COMPILER_ID>,MSVC>,$<STREQUAL:$<CONFIG>,Release>>:/SUBSYSTEM:windows;/ENTRY:mainCRTStartup>")
    add_link_options("$<$<AND:$<STREQUAL:$<C_COMPILER_ID>,GNU>,$<STREQUAL:$<CONFIG>,Release>>:-mwindows>")
endif()

add_subdirectory(src)
add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

if (TINYGL_BUILD_DEMO)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")
endif (TINYGL_BUILD_DEMO)

