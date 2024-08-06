#include "display.h"
#include "rtos.h"
#include "board.h"
#include "gpio.h"
#include "ST7789/st7789.h"
#include "lvgl/lvgl.h"
#include "display_interface.hpp"

void my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p);

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

    LoadMeter cpu_meter(-220,0,220);
    cpu_meter.set_rotation(305);
    cpu_meter.set_angles(20,90);
    cpu_meter.set_reverse(true);
    cpu_meter.set_load(15);

    LoadMeter gpu_meter(220,0,220);
    gpu_meter.set_rotation(125);
    gpu_meter.set_angles(20,90);
    gpu_meter.set_reverse(false);
    gpu_meter.set_load(78);

    while (1) {
        taskENTER_CRITICAL();
        lv_timer_handler();
        taskEXIT_CRITICAL();
    }
}

void 
my_disp_flush(lv_display_t * disp, const lv_area_t * area, uint8_t * color_p) {
    display_set_window(area->x1,area->y1,area->x2,area->y2);
    display_send_buffer(area->x2-area->x1+1,area->y2-area->y1+1, color_p);
    lv_display_flush_ready(disp); 
}