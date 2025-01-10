cmake_minimum_required(VERSION 3.8)

project(TinyGL-Demo LANGUAGES C)

set(DEMO_LIST "01.draw")

foreach(DEMO ${DEMO_LIST})
    add_executable(${DEMO} ${DEMO}.c)
    target_link_libraries(${DEMO} PRIVATE TinyGL)
endforeach(DEMO ${DEMO_LIST})