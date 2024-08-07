#include "pwm.h"
#include "gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_tim.h"

void
pwm_init(void) {
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    LL_GPIO_InitTypeDef gpio_init = {0};

    gpio_init.Pin = BLK_Pin;
    gpio_init.Mode = LL_GPIO_MODE_ALTERNATE;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init.OutputType = LL_GPIO_PULL_NO;
    gpio_init.Alternate =  LL_GPIO_AF_2;
    LL_GPIO_Init(GPIOA, &gpio_init);

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3); 

    LL_TIM_SetPrescaler(TIM3, 960-1);
                                            
    LL_TIM_EnableARRPreload(TIM3);

    LL_TIM_SetAutoReload(TIM3, 100-1);

    LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
  
    LL_TIM_OC_SetCompareCH1(TIM3, 100);
  
    LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);
  
    LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
    
    LL_TIM_EnableCounter(TIM3);

    LL_TIM_GenerateEvent_UPDATE(TIM3);
  
}