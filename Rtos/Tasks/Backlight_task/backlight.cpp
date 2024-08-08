extern "C" {
#include "backlight.h"
}
#include "rtos.h"
#include "pwm.h"

void
backlight_task(void* arg) {

    uint8_t step = 1;
    while(1) {
        static uint32_t ulNotifiedValue;
        static uint8_t target_brightness = 0;
        static uint8_t current_brightness = 0;
        BaseType_t xResult = xTaskNotifyWait( pdFALSE, 0xFFFFFF, &ulNotifiedValue, pdMS_TO_TICKS(1));
        if( xResult == pdPASS ) {
            target_brightness = (uint8_t)ulNotifiedValue;
        }
        if(target_brightness!=current_brightness) {
            if(target_brightness>current_brightness) {
                if(target_brightness-current_brightness>=step) {
                    current_brightness+=step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            if(target_brightness<current_brightness) {
                if(current_brightness-target_brightness>=step) {
                    current_brightness-=step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            set_pwm(current_brightness);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}