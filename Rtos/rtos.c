#include "rtos.h"
#include "display.h"
#include "backlight.h"
#include "pwr_btn.h"
#include "usb_cdc.h"

TaskHandle_t display_task_handle;
TaskHandle_t backlight_task_handle;
TaskHandle_t pwr_btn_task_handle;
TaskHandle_t usb_cdc_task_handle;

void
threads_init(void) {
    xTaskCreate(display_task, "display task", configMINIMAL_STACK_SIZE*5, NULL, configMAX_PRIORITIES - 1, &display_task_handle);
    xTaskCreate(backlight_task, "backlight task", configMINIMAL_STACK_SIZE*1, NULL, configMAX_PRIORITIES - 1, &backlight_task_handle);
    xTaskCreate(pwr_btn_task, "pwr btn task", configMINIMAL_STACK_SIZE*1, NULL, configMAX_PRIORITIES - 1, &pwr_btn_task_handle);
    xTaskCreate(usb_cdc_task, "usb cdc task", configMINIMAL_STACK_SIZE*2, NULL, configMAX_PRIORITIES - 1, &usb_cdc_task_handle);
}