#include "gpio.h"
#include "rcc.h"
#include "stm32f4xx_ll_bus.h"

void
gpio_init(void) {


    LL_GPIO_InitTypeDef gpio_init = {0};
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    gpio_init.Pin = RST_Pin | CS_Pin | DC_Pin;
    gpio_init.Mode = LL_GPIO_MODE_OUTPUT;
    gpio_init.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    gpio_init.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    gpio_init.Alternate =  LL_GPIO_AF_0;
    LL_GPIO_Init(GPIOA, &gpio_init);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    gpio_init.Pin = LED_Pin;
    LL_GPIO_Init(GPIOC, &gpio_init);

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    gpio_init.Pin = PWR_TRIG_Pin;
    gpio_init.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    gpio_init.Pull = LL_GPIO_PULL_NO;
    LL_GPIO_Init(PWR_TRIG_GPIO_Port, &gpio_init);
    
    LL_GPIO_SetOutputPin(LED_GPIO_Port,LED_Pin);
    LL_GPIO_SetOutputPin(PWR_TRIG_GPIO_Port,PWR_TRIG_Pin);
}