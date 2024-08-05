#include "board.h"
#include "rcc.h"
#include "gpio.h"
#include "spi.h"

void
board_init(void) {

    rcc_init();
    
    gpio_init();

    spi_config();

}