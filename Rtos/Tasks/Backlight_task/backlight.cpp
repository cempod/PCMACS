#include "backlight.h"
#include "rtos.h"
#include "pwm.h"

static bool need_some_sleep(uint32_t tick, uint32_t last_tick);

void
backlight_task(void* arg) {
    uint8_t step = 1;

    while (1) {
        static uint32_t last_tick = 0;
        static uint32_t brightness_notified_val;
        static uint8_t target_brightness = 0;
        static uint8_t current_brightness = 0;
        BaseType_t xResult = xTaskNotifyWait(pdFALSE, 0xFFFFFF, &brightness_notified_val, pdMS_TO_TICKS(1));
        if (xResult == pdPASS) {
            target_brightness = (uint8_t)brightness_notified_val;
            last_tick = xTaskGetTickCount();
        }
        if (target_brightness != current_brightness) {
            if (target_brightness > current_brightness) {
                if (target_brightness - current_brightness >= step) {
                    current_brightness += step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            if (target_brightness < current_brightness) {
                if (current_brightness - target_brightness >= step) {
                    current_brightness -= step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            set_pwm(current_brightness);
        }
        if (need_some_sleep(xTaskGetTickCount(), last_tick)) {
            target_brightness = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

static bool 
need_some_sleep(uint32_t tick, uint32_t last_tick) {
    if (tick >= last_tick) {
        if (pdTICKS_TO_MS(tick - last_tick) > 30000) {
            return true;
        }
    } else {
        if (pdTICKS_TO_MS(tick + (UINT32_MAX - last_tick)) > 30000) {
            return true;
        }
    }
    return false;
}