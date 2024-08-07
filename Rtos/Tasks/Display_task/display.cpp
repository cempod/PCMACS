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

    LoadMeter cpu_meter(-230,0,240);
    cpu_meter.set_rotation(305);
    cpu_meter.set_angles(20,90);
    cpu_meter.set_reverse(true);
    cpu_meter.set_load(100);

    LoadMeter gpu_meter(230,0,240);
    gpu_meter.set_rotation(125);
    gpu_meter.set_angles(20,90);
    gpu_meter.set_reverse(false);
    gpu_meter.set_load(100);

    lv_point_precise_t cpu_line_l_points[] = { {0, 0}, {23, 13},{58, 13}};
    LabelLine cpu_load_label_line(cpu_line_l_points,3);
    cpu_load_label_line.set_offsets(-80,53);

    lv_point_precise_t gpu_line_l_points[] = { {0, 13}, {35, 13},{58, 0}};
    LabelLine gpu_load_label_line(gpu_line_l_points,3);
    gpu_load_label_line.set_offsets(80,53);

    lv_point_precise_t cpu_temp_line_l_points[] = { {0, 10}, {0, 0},{22, 0}};
    LabelLine cpu_temp_label_line(cpu_temp_line_l_points,3);
    cpu_temp_label_line.set_offsets(-68,-43);

    lv_point_precise_t gpu_temp_line_l_points[] = { {0, 0}, {22, 0},{22, 10}};
    LabelLine gpu_temp_label_line(gpu_temp_line_l_points,3);
    gpu_temp_label_line.set_offsets(68,-43);
    
    Label temp_label(0,-49, &lv_font_montserrat_14);
    temp_label.set_text("Temperature");

    Label load_label(0,59, &lv_font_montserrat_14);
    load_label.set_text("Load");

    Label cpu_temp_label(-75,0, &lv_font_montserrat_30);
    cpu_temp_label.set_text("50°");

    Label gpu_temp_label(75,0, &lv_font_montserrat_30);
    gpu_temp_label.set_text("50°");

    Label cpu_load_label(-69,50, &lv_font_montserrat_14);
    cpu_load_label.set_text("100%");

    Label gpu_load_label(69,50, &lv_font_montserrat_14);
    gpu_load_label.set_text("100%");

    Label cpu_label(-69,69, &lv_font_montserrat_14);
    cpu_label.set_text("CPU");

    Label gpu_label(69,69, &lv_font_montserrat_14);
    gpu_label.set_text("GPU");

    while (1) {
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