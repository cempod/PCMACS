#include "pwr_btn.h"
#include "rtos.h"

void
pwr_btn_task(void* arg) {
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}