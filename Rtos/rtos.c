#include "rtos.h"
#include "display.h"

TaskHandle_t display_task_handle;

void
threads_init(void) {
    xTaskCreate(display_task, "display task", configMINIMAL_STACK_SIZE*10, NULL, configMAX_PRIORITIES - 1, &display_task_handle);
}