#ifndef DISPLAY_H
#define DISPLAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

void display_task(void* arg);
void set_theme(lv_color_t theme);

#ifdef __cplusplus
}
#endif

#endif