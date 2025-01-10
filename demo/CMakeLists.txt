cmake_minimum_required(VERSION 3.8)

project(TinyGL-Demo LANGUAGES C)

set(DEMO_LIST "01.draw")

foreach(DEMO ${DEMO_LIST})
    add_executable(${DEMO} ${DEMO}.c)
    target_link_libraries(${DEMO} PRIVATE TinyGL)

    if (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
        target_link_libraries(${DEMO} PUBLIC  "-s USE_GLFW=3" "-s ALLOW_MEMORY_GROWTH=1" "-s USE_WEBGL2=1")
        configure_file("${CMAKE_CURRENT_SOURCE_DIR}/index.html" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${DEMO}.html")
    endif (CMAKE_SYSTEM_NAME STREQUAL "Emscripten")

endforeach(DEMO ${DEMO_LIST})