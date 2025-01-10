if (NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw")
endif (NOT CMAKE_SYSTEM_NAME STREQUAL "Emscripten")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake")
glad_add_library(glad STATIC REPRODUCIBLE API gles2=3.0 MERGE)