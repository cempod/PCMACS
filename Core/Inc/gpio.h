#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_ll_gpio.h"

#define LED_Pin LL_GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define RST_Pin LL_GPIO_PIN_2
#define RST_GPIO_Port GPIOA
#define DC_Pin LL_GPIO_PIN_3
#define DC_GPIO_Port GPIOA
#define CS_Pin LL_GPIO_PIN_4
#define CS_GPIO_Port GPIOA
#define BLK_Pin LL_GPIO_PIN_6
#define BLK_GPIO_Port GPIOA

void gpio_init(void);

#ifdef __cplusplus
}
#endif

#endif