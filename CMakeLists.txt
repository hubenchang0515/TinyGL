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

add_subdirectory(thirdparty EXCLUDE_FROM_ALL)

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/src" TINYGL_SRC)
add_library(${PROJECT_NAME} ${TINYGL_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad)

file(GLOB TINYGL_HDR "${CMAKE_CURRENT_SOURCE_DIR}/include/TinyGL/*.h")
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${TINYGL_HDR}")

if (TINYGL_USE_DEFAULT)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DTINYGL_USE_DEFAULT)
endif (TINYGL_USE_DEFAULT)

if (TINYGL_BUILD_DEMO)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/demo")
endif (TINYGL_BUILD_DEMO)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/TinyGL)