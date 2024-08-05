cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
 
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
 
# Add you project name
string(REGEX MATCH "[^\/]+$" BUFF_FOR_PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR})
project(${BUFF_FOR_PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

# read Makefile for parsing
file(READ ${CMAKE_SOURCE_DIR}/Makefile MAKEFILE_BUFF)
 
# parsing for cortex kernel name
string(REGEX MATCH "-mcpu=[^\n]*" MCPU ${MAKEFILE_BUFF})
string(REGEX MATCH "[^=]*$" MCPU ${MCPU})

message(STATUS "Detected ${MCPU} kernel")

#add_compile_definitions(ARM_MATH_CM4;ARM_MATH_MATRIX_CHECK;ARM_MATH_ROUNDING)
if(${MCPU} STREQUAL "cortex-m3" OR ${MCPU} STREQUAL "cortex-m0" OR ${MCPU} STREQUAL "cortex-m0+")
    add_compile_options(-mfloat-abi=soft )
    add_link_options(-mfloat-abi=soft )
    message(STATUS "Using software float")
else()
    string(REGEX MATCH "-mfloat-abi=[^\n]*" MFLOAT_ABI ${MAKEFILE_BUFF})
    string(REGEX MATCH "[^=]*$" MFLOAT_ABI ${MFLOAT_ABI})

    if(${MFLOAT_ABI} STREQUAL "hard")
        string(REGEX MATCH "-mfpu=[^\n]*" MFPU ${MAKEFILE_BUFF})
        string(REGEX MATCH "[^=]*$" MFPU ${MFPU})

        add_compile_options(-mfloat-abi=${MFLOAT_ABI} -mfpu=${MFPU})
        add_link_options(-mfloat-abi=${MFLOAT_ABI} -mfpu=${MFPU})

        message(STATUS "Using ${MFLOAT_ABI} float with ${MFPU}")
    else()
        add_compile_options(-mfloat-abi=soft )
        add_link_options(-mfloat-abi=soft )
    
        message(STATUS "Using software float")
    endif()
endif()

add_compile_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
add_compile_options(-ffunction-sections -fdata-sections -fno-common -fmessage-length=0)
 
# Uncomment to mitigate c++17 absolute addresses warnings
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-register")
 
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    message(STATUS "Maximum optimization for speed")
    add_compile_options(-Ofast)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
    message(STATUS "Maximum optimization for speed, debug info included")
    add_compile_options(-Ofast -g)
elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
    message(STATUS "Maximum optimization for size")
    add_compile_options(-Os)
else ()
    message(STATUS "Minimal optimization, debug info included")
    add_compile_options(-Og)
endif ()
 
string(REGEX MATCHALL "-I[^\ \n]*" INCLUDE_DIRS_RAW ${MAKEFILE_BUFF})

# parsing for include dir
string(REGEX MATCHALL "-I[^\ \n]*" INCLUDE_DIRS_RAW ${MAKEFILE_BUFF})
foreach(INCLUDE_DIR ${INCLUDE_DIRS_RAW})
    string(REPLACE "-I" "${CMAKE_SOURCE_DIR}/" INCLUDE_DIR ${INCLUDE_DIR})
    string(REPLACE ";" "\n" INCLUDE_DIR ${INCLUDE_DIR})
    list(APPEND INCLUDE_DIRS ${INCLUDE_DIR})
endforeach()

# Add Include directories
include_directories(
    ${INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Rtos
    ${CMAKE_CURRENT_SOURCE_DIR}/Rtos/Tasks/Display_task
    )

# parsing for definitions
string(REGEX MATCHALL "-D[^\ \n]*" DEFINITIONS_PARSE ${MAKEFILE_BUFF})
add_definitions(${DEFINITIONS_PARSE})
 
file(STRINGS ${CMAKE_SOURCE_DIR}/Makefile MAKEFILE_BUFF)
foreach(A ${MAKEFILE_BUFF})
    if (A MATCHES "C_SOURCES =[^\n]*")
        string(REGEX MATCH "  .+$" A ${A})
        string(REGEX MATCHALL "[^ ]+" A ${A})
        set(SOURCE_FILES_BUF ${A})
    endif()
endforeach()

file(GLOB STARTUP "startup_*.s")
message(STATUS "Found startup file - ${STARTUP}")

# Add you source file
file(GLOB SOURCES
    ${SOURCE_FILES_BUF}
    ${STARTUP}
    "${CMAKE_SOURCE_DIR}/Rtos/*.c"
    "${CMAKE_SOURCE_DIR}/Rtos/Tasks/Display_task/*.c"
)
 
# Add lincer file
file(GLOB LINKER_SCRIPT "STM32*.ld")
message(STATUS "Found linker script - ${LINKER_SCRIPT}")
 
# this options for C++
add_link_options(-specs=nano.specs -specs=nosys.specs -lc -lm -lnosys)
add_link_options(-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)
add_link_options(-mcpu=${MCPU} -mthumb -mthumb-interwork)
add_link_options(-T ${LINKER_SCRIPT})
 
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

add_library(rootlib INTERFACE)
target_include_directories(rootlib INTERFACE ${CMAKE_SOURCE_DIR})
target_compile_definitions(rootlib INTERFACE ${DEFINES})

add_subdirectory(${CMAKE_SOURCE_DIR}/ST7789)
add_subdirectory(${CMAKE_SOURCE_DIR}/lvgl)

target_link_libraries(${PROJECT_NAME}.elf
    st7789
    lvgl
)


add_library(freertos_config INTERFACE)
target_include_directories(freertos_config SYSTEM
    INTERFACE
        ${CMAKE_SOURCE_DIR}/core/inc)
target_compile_definitions(freertos_config
    INTERFACE
        projCOVERAGE_TEST=0
)

set( FREERTOS_HEAP "4" CACHE STRING "" FORCE)
# Select the cross-compile PORT
set(FREERTOS_PORT "GCC_ARM_CM4F" CACHE STRING "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel)

target_link_libraries(${PROJECT_NAME}.elf
    freertos_kernel
)

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
 
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")