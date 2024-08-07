extern "C" {
#include "backlight.h"
}
#include "rtos.h"
#include "pwm.h"

void
backlight_task(void* arg) {

pwm_init();

    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}