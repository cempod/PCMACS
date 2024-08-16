#include "display.h"
#include "rtos.h"
#include "board.h"
#include "gpio.h"
#include "ST7789/st7789.h"
#include "lvgl/lvgl.h"
#include "display_interface.hpp"
#include <stdio.h>
#include "stm32f4xx_ll_rtc.h"
#include "stm32f4xx_ll_rcc.h"

void my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p);
static bool is_data_lost(uint32_t tick, uint32_t last_tick);

void 
vApplicationTickHook(void) {
lv_tick_inc(1);
}

void
display_task(void* arg) {
    display_init();
    lv_init();

    lv_display_t *display = lv_display_create(320, 170);
    static lv_color_t buf1[320 * 170 / 10];                        /*Declare a buffer for 1/10 screen size*/
    lv_display_set_buffers(display, buf1, NULL, sizeof(buf1),LV_DISP_RENDER_MODE_PARTIAL);  /*Initialize the display buffer.*/
    lv_display_set_flush_cb(display, my_disp_flush);

    interface_init();

    LoadMeter cpu_meter(-230,0,240);
    cpu_meter.set_rotation(305);
    cpu_meter.set_angles(20,90);
    cpu_meter.set_reverse(true);
    cpu_meter.set_load(0);
    cpu_meter.set_visibility(false);

    LoadMeter gpu_meter(230,0,240);
    gpu_meter.set_rotation(125);
    gpu_meter.set_angles(20,90);
    gpu_meter.set_reverse(false);
    gpu_meter.set_load(0);
    gpu_meter.set_visibility(false);

    lv_point_precise_t cpu_line_l_points[] = { {0, 0}, {23, 13},{58, 13}};
    LabelLine cpu_load_label_line(cpu_line_l_points,3);
    cpu_load_label_line.set_offsets(-80,53);
    cpu_load_label_line.set_visibility(false);

    lv_point_precise_t gpu_line_l_points[] = { {0, 13}, {35, 13},{58, 0}};
    LabelLine gpu_load_label_line(gpu_line_l_points,3);
    gpu_load_label_line.set_offsets(80,53);
    gpu_load_label_line.set_visibility(false);

    lv_point_precise_t cpu_temp_line_l_points[] = { {0, 10}, {0, 0},{22, 0}};
    LabelLine cpu_temp_label_line(cpu_temp_line_l_points,3);
    cpu_temp_label_line.set_offsets(-68,-43);
    cpu_temp_label_line.set_visibility(false);

    lv_point_precise_t gpu_temp_line_l_points[] = { {0, 0}, {22, 0},{22, 10}};
    LabelLine gpu_temp_label_line(gpu_temp_line_l_points,3);
    gpu_temp_label_line.set_offsets(68,-43);
    gpu_temp_label_line.set_visibility(false);
    
    Label temp_label(0,-49, &lv_font_montserrat_14);
    temp_label.set_text("Temperature");
    temp_label.set_visibility(false);

    Label load_label(0,59, &lv_font_montserrat_14);
    load_label.set_text("Load");
    load_label.set_visibility(false);

    Label cpu_temp_label(-75,0, &lv_font_montserrat_30);
    cpu_temp_label.set_text("-");
    cpu_temp_label.set_visibility(false);

    Label gpu_temp_label(75,0, &lv_font_montserrat_30);
    gpu_temp_label.set_text("-");
    gpu_temp_label.set_visibility(false);

    Label cpu_load_label(-69,50, &lv_font_montserrat_14);
    cpu_load_label.set_text("-");
    cpu_load_label.set_visibility(false);

    Label gpu_load_label(69,50, &lv_font_montserrat_14);
    gpu_load_label.set_text("-");
    gpu_load_label.set_visibility(false);

    Label cpu_label(-69,69, &lv_font_montserrat_14);
    cpu_label.set_text("CPU");
    cpu_label.set_visibility(false);

    Label gpu_label(69,69, &lv_font_montserrat_14);
    gpu_label.set_text("GPU");
    gpu_label.set_visibility(false);

    Label logo_label(0,0, &lv_font_montserrat_44);
    logo_label.set_text("PCMACS");
    logo_label.set_visibility(true);

    Label sub_logo_label(0,69, &lv_font_montserrat_14);
    sub_logo_label.set_text("PC Monitoring & Anti Cat System");
    sub_logo_label.set_visibility(true);

    xTaskNotify(backlight_task_handle, 100, eSetValueWithOverwrite);

    while (1) {
        static bool rtc_inited = false;
        if (!rtc_inited) {
            if (LL_RCC_LSE_IsReady() == 1) {
                rtc_inited = true;
            }
        }
        static uint32_t last_tick = 0;
        static uint32_t telemetry_notified_val=0;
        BaseType_t xResult = xTaskNotifyWait(pdFALSE, 0xFFFFFF, &telemetry_notified_val, pdMS_TO_TICKS(1));
        if (xResult == pdPASS) {
            char str[4];
            cpu_meter.set_load((uint8_t)(telemetry_notified_val>>16));
            cpu_meter.set_visibility(true);
            cpu_load_label.set_text("%i%%",(uint8_t)(telemetry_notified_val>>16));
            cpu_load_label.set_visibility(true);
            gpu_meter.set_load((uint8_t)(telemetry_notified_val>>24));
            gpu_meter.set_visibility(true);
            gpu_load_label.set_text("%i%%",(uint8_t)(telemetry_notified_val>>24));
            gpu_load_label.set_visibility(true);
            cpu_temp_label.set_text("%i°",(uint8_t)(telemetry_notified_val));
            cpu_temp_label.set_visibility(true);
            gpu_temp_label.set_text("%i°",(uint8_t)(telemetry_notified_val>>8));
            gpu_temp_label.set_visibility(true);
            cpu_load_label_line.set_visibility(true);
            cpu_temp_label_line.set_visibility(true);
            gpu_load_label_line.set_visibility(true);
            gpu_temp_label_line.set_visibility(true);
            load_label.set_visibility(true);
            temp_label.set_visibility(true);
            logo_label.set_visibility(false);
            sub_logo_label.set_visibility(false);
            last_tick = xTaskGetTickCount();
        }
        if (is_data_lost(xTaskGetTickCount(), last_tick)) {
            cpu_meter.set_visibility(false);
            cpu_load_label.set_visibility(false);
            gpu_meter.set_visibility(false);
            gpu_load_label.set_visibility(false);
            cpu_temp_label.set_visibility(false);
            gpu_temp_label.set_visibility(false);
            cpu_load_label_line.set_visibility(false);
            cpu_temp_label_line.set_visibility(false);
            gpu_load_label_line.set_visibility(false);
            gpu_temp_label_line.set_visibility(false);
            load_label.set_visibility(false);
            temp_label.set_visibility(false);
            if (rtc_inited) {
                sub_logo_label.set_visibility(false);
                logo_label.set_text("%02d:%02d",__LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetHour(RTC)),__LL_RTC_CONVERT_BCD2BIN(LL_RTC_TIME_GetMinute(RTC)));
            }
            logo_label.set_visibility(true);
        }
        taskENTER_CRITICAL();
        lv_timer_handler();
        taskEXIT_CRITICAL();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}

void 
my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p) {
    display_set_window(area->x1,area->y1,area->x2,area->y2);
    display_send_buffer(area->x2-area->x1+1,area->y2-area->y1+1, color_p);
    lv_display_flush_ready(disp); 
}

static bool 
is_data_lost(uint32_t tick, uint32_t last_tick) {
    if (tick >= last_tick) {
        if (pdTICKS_TO_MS(tick - last_tick) > 3000) {
            return true;
        }
    } else {
        if (pdTICKS_TO_MS(tick + (UINT32_MAX - last_tick)) > 3000) {
            return true;
        }
    }
    return false;
}