#include "board.h"
#include "rcc.h"
#include "gpio.h"
#include "spi.h"

void
board_init(void) {

    rcc_init();
    
    NVIC_SetPriorityGrouping(3U);
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

    gpio_init();

    spi_config();

}