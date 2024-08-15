#include "rtc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rtc.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_pwr.h"

void
rtc_init(uint8_t hour, uint8_t minute, uint8_t second) {
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    LL_PWR_EnableBkUpAccess();
    LL_RCC_ForceBackupDomainReset();
    LL_RCC_ReleaseBackupDomainReset();
    LL_RCC_LSE_Enable();
    while (LL_RCC_LSE_IsReady() != 1){ };
    LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
    LL_RCC_EnableRTC();
    LL_RTC_DisableWriteProtection(RTC);

    LL_RTC_EnableInitMode(RTC);
    while (LL_RTC_IsActiveFlag_INIT(RTC) != 1) {}
    LL_RTC_SetHourFormat(RTC, LL_RTC_HOURFORMAT_24HOUR);
    LL_RTC_SetAsynchPrescaler(RTC, 0x7F);
    LL_RTC_SetSynchPrescaler(RTC, 0x00FF);
    LL_RTC_TIME_Config(RTC, LL_RTC_HOURFORMAT_24HOUR, hour, minute, second);
    LL_RTC_TimeTypeDef time = {
        .Hours = hour,
        .Minutes = minute,
        .Seconds = second,
        .TimeFormat = LL_RTC_HOURFORMAT_24HOUR
    };
    LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BIN, &time);
    LL_RTC_DisableInitMode(RTC);
    LL_RTC_EnableWriteProtection(RTC);
}