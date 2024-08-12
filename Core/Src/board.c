#include "board.h"
#include "rcc.h"
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
#include "exti.h"
#include "usb.h"

void
board_init(void) {

    rcc_init();
    
    NVIC_SetPriorityGrouping(3U);
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

    gpio_init();

    spi_init();

    pwm_init();

    exti_init();

    usb_init();

}