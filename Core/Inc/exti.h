#ifndef EXTI_H
#define EXTI_H

#ifdef __cplusplus
extern "C" {
#endif

#define PWR_BTN_Pin LL_GPIO_PIN_10
#define PWR_BTN_GPIO_Port GPIOB

void exti_init(void);

#ifdef __cplusplus
}
#endif

#endif