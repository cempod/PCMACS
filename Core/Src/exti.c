#include "exti.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_system.h"
#include "rtos.h"

void PWR_BTN_Callback();

void
exti_init() {
    LL_EXTI_InitTypeDef exti_initstruct;

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
  
    LL_GPIO_SetPinMode(PWR_BTN_GPIO_Port, PWR_BTN_Pin, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(PWR_BTN_GPIO_Port, PWR_BTN_Pin, LL_GPIO_PULL_DOWN); 

    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTB, LL_SYSCFG_EXTI_LINE10);

    exti_initstruct.Line_0_31   = LL_EXTI_LINE_10;
    exti_initstruct.LineCommand = ENABLE;
    exti_initstruct.Mode        = LL_EXTI_MODE_IT;
    exti_initstruct.Trigger     = LL_EXTI_TRIGGER_RISING;

    LL_EXTI_Init(&exti_initstruct);
    
    NVIC_EnableIRQ(EXTI15_10_IRQn); 
    NVIC_SetPriority(EXTI15_10_IRQn, 5);
}

void 
EXTI15_10_IRQHandler(void) {
  if(LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_10) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_10);

    PWR_BTN_Callback(); 
  }
}

void
PWR_BTN_Callback() {
    static uint8_t brightness = 100;
    if(brightness==100) {
        brightness = 0;
    } else {
        brightness = 100;
    }
    static TickType_t last_tick = 0; 
    if(pdTICKS_TO_MS(xTaskGetTickCountFromISR() - last_tick) > 100) {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        xTaskNotifyFromISR(backlight_task_handle, brightness, eSetValueWithOverwrite, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
    last_tick = xTaskGetTickCountFromISR();
}