#include "rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_cortex.h"

void
rcc_init(void) {
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);

    if (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_3) {
            while (1){}        
    }

    LL_RCC_HSE_Enable();

    while (LL_RCC_HSE_IsReady() != 1) {}

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 192, LL_RCC_PLLP_DIV_2);

    LL_RCC_PLL_ConfigDomain_48M(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_25, 192, LL_RCC_PLLQ_DIV_4);

    LL_RCC_PLL_Enable();

    while (LL_RCC_PLL_IsReady() != 1) {}

    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);

    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_2);

    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {}

    LL_Init1msTick(96000000);

    LL_SYSTICK_SetClkSource(LL_SYSTICK_CLKSOURCE_HCLK);

    LL_SetSystemCoreClock(96000000);
}