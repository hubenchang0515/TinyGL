add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glad/cmake")
glad_add_library(glad STATIC REPRODUCIBLE API gl:compatibility=4.0,gles1:common=1.0,gles2=3.0,glsc2=2.0 MERGE)