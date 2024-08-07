#include "rtos.h"
#include "display.h"
#include "backlight.h"

TaskHandle_t display_task_handle;
TaskHandle_t backlight_task_handle;

void
threads_init(void) {
    xTaskCreate(display_task, "display task", configMINIMAL_STACK_SIZE*10, NULL, configMAX_PRIORITIES - 2, &display_task_handle);
    xTaskCreate(backlight_task, "backlight task", configMINIMAL_STACK_SIZE*2, NULL, configMAX_PRIORITIES - 1, &backlight_task_handle);
}