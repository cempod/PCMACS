cmake_minimum_required(VERSION 3.22)

set(SCRS
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_adc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_crc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_dac.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_dma.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_dma2d.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_exti.c
    #${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_fmc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_fmpi2c.c
    #${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_fsmc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_i2c.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_lptim.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_pwr.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_rcc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_rng.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_rtc.c
    #${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_sdmmc.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_spi.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_tim.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_usart.c
    #${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_usb.c
    ${CMAKE_CURRENT_LIST_DIR}/Src/stm32f4xx_ll_utils.c
)

add_library(LL_Drivers INTERFACE)
target_sources(LL_Drivers INTERFACE ${SCRS})
target_include_directories(LL_Drivers INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/Inc
    rootlib
)
target_compile_definitions(LL_Drivers INTERFACE rootlib)
target_link_libraries(LL_Drivers INTERFACE
    rootlib
)