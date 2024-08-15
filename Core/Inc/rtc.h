#ifndef RTC_H
#define RTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void rtc_init(uint8_t hour, uint8_t minute, uint8_t second);

#ifdef __cplusplus
}
#endif

#endif