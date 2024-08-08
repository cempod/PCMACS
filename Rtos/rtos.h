#ifndef RTOS_H_
#define RTOS_H_

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t display_task_handle;
extern TaskHandle_t backlight_task_handle;

void threads_init(void);

#endif