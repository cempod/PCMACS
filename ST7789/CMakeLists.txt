cmake_minimum_required(VERSION 3.22)

set(SCRS
    ${CMAKE_CURRENT_LIST_DIR}/st7789.c
)

add_library(st7789 INTERFACE)
target_sources(st7789 INTERFACE ${SCRS})
target_include_directories(st7789 INTERFACE 
    rootlib
)
target_compile_definitions(st7789 INTERFACE root)
target_link_libraries(st7789 INTERFACE
    rootlib
)