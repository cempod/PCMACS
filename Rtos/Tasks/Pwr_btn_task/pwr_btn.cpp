#include "pwr_btn.h"
#include "rtos.h"
#include "gpio.h"

void
pwr_btn_task(void* arg) {
    while (1) {
        static uint32_t btn_last_timestamp = 0;
        static uint32_t btn_notified_timestamp;
        BaseType_t xResult = xTaskNotifyWait(pdFALSE, 0xFFFFFF, &btn_notified_timestamp, pdMS_TO_TICKS(1));
        if (xResult == pdPASS) {
            if (pdTICKS_TO_MS(btn_notified_timestamp-btn_last_timestamp) <= 400) {
                LL_GPIO_ResetOutputPin(PWR_TRIG_GPIO_Port,PWR_TRIG_Pin);
                vTaskDelay(pdMS_TO_TICKS(250));
                LL_GPIO_SetOutputPin(PWR_TRIG_GPIO_Port,PWR_TRIG_Pin);
                btn_last_timestamp = 0;
            } else {
                btn_last_timestamp = btn_notified_timestamp;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}